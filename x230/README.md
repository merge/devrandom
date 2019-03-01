## General Setup I use for different Laptops as well

| Keys | Function |
| --- | --- |
| Enter | Startup Interrupt Menu |
| ESC | to Resume normal startup |
| F1 | to Enter the BIOS Setup Utility |
| F10 | to diagnose hardware |
| F11 | to recover your system |
| F12 | Boot menu |

### Tap to click and TwoFinger Tap to Right click
As long as the Xorg synaptics driver is used, edit
`/usr/share/X11/xorg.conf.d/70-synaptics.conf` and add the following options to
the touchpad catchall entry:

    Option "TapButton1" "1"
    Option "TapButton2" "3"


### BFQ block scheduler
* `IOSCHED_BFQ=y`
* check via `cat /sys/block/sda/queue/scheduler`

### GRUB kernels list and settings
in `/etc/default/grub` add

     GRUB_CMDLINE_LINUX="iomem=relaxed fsck.repair=yes scsi_mod.use_blk_mq=1"
     GRUB_DISABLE_SUBMENU=y
     GRUB_RECORDFAIL_TIMEOUT=1


### SATA power management
have `SATA_MOBILE_LPM_POLICY` configured `3` and make sure
`link_power_management_policy` in libata sysfs `/sys/class/scsi_host/host*/`
reads `med_power_with_dipm`

### optional power saving
* `BT_HCIBTUSB_AUTOSUSPEND`
* `SND_HDA_POWER_SAVE_DEFAULT 1`


### Heads setup
* mount-usb (load usb drivers)
* gpg --card-edit --homedir .gnupg/
TODO

### X220 Debian 9: suspend to RAM on closing lid
Ideally systemd's defaults would just work. For me they don't, so we disable them
according to [the Debian wiki](https://wiki.debian.org/Suspend):

    systemctl mask sleep.target suspend.target hibernate.target hybrid-sleep.target

And edit the line in `/etc/systemd/logind.conf`:

    HandleLidSwitch=ignore

And we use pm-utils instead: `apt-get install pm-utils`

We create `/etc/pm/config.d/40-coreboot-compat` and put in
`ADD_PARAMETERS="--quirk-reset-brightness --quirk-vbe-post --quirk-vbestate-restor --quirk-vbemode-restore"`
and pm-suspend should now work.

Now use `acpid` systemd service and create `/etc/acpi/events/lid` containing

    event=button/lid
    action=/etc/acpi/lid.sh

and the corresponding lid.sh containing

    #!/bin/bash
    # if launched through a lid event and lid is open, do nothing
    grep -q closed /proc/acpi/button/lid/LID/state
    if [ $? = 0 ]
    then
    	pm-suspend
    fi

