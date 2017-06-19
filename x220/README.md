# Thinkpad X220 Debian Stretch Setup Notes

## General Setup I use for different Laptops as well

### Tap to click and TwoFinger Tap to Right click
As long as the Xorg synaptics driver is used, edit
`/usr/share/X11/xorg.conf.d/70-synaptics.conf` and add the following options to
the touchpad catchall entry:

    Option "TapButton1" "1"
    Option "TapButton2" "3"

### Two Finger scrolling
Ok by default in Debian Stretch

# product 42916Z9 serial R9N52CE
* serial number from `lshw`
* [Lenovo BIOS image](https://github.com/merge/specs/raw/master/x220/flash_original_R9N52CE.bin)
* Winbond W25Q64.V 8MB chip

## BIOS flashing internally
`flashrom -p internal:laptop=force_I_want_a_brick` works, when Linux is started with
the `iomem=relaxed` commandline option. Put it /etc/default/grub to have it permanently.
Only tried reading. No further tests so far.

This weakens security and should only be used for flashing.

## coreboot with SeaBIOS payload
* git master from 2017-06-16: [coreboot config](https://github.com/merge/specs/blob/master/x220/coreboot_R9N52CE_seabios.config)

### suspend to RAM on closing lid
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

### display in bootloader
N/A

## coreboot with GRUB payload
* git master from 2017-XX-XX: coreboot config

### suspend to RAM on closing lid

### display in bootloader
OK because coreboot framebuffer
