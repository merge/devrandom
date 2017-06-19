# Thinkpad X220 Debian Stretch Setup Notes

## General Setup I use for different Laptops as well

### Tap to click and TwoFinger Tap to Right click
As long as the Xorg synaptics driver is used, edit
`/usr/share/X11/xorg.conf.d/70-synaptics.conf` and add the following options to
the touchpad catchall entry:

    Option "TapButton1" "1"
    Option "TapButton2" "3"



# Thinkpad X220 product 42916Z9 serial R9N52CE
* serial number from `lshw`
* [Lenovo BIOS image](https://github.com/merge/specs/raw/master/x220/R9N52CE_orig_flash.bin)
* Winbond W25Q64.V 8MB chip

## BIOS flashing internally
see [the coreboot wiki for X220](https://www.coreboot.org/Board:lenovo/x220).
`flashrom -p internal:laptop=force_I_want_a_brick` works, when Linux is started with
the `iomem=relaxed` commandline option. Put it /etc/default/grub to have it permanently.

This weakens security and should only be used for flashing.

## coreboot with SeaBIOS payload
Maximum compatibility - nonfree graphics initialisation

### building
see [the coreboot wiki](https://www.coreboot.org/Build_HOWTO)
* git master from 2017-06-16: [coreboot config](https://github.com/merge/specs/blob/master/x220/coreboot_R9N52CE_seabios.config)
* put the 3 flashregions into `3rdparty/blobs/mainboard/lenovo/x220` as
 * descriptor.bin
 * me.bin
 * gbe.bin
* put the `vga-8086-0106.bin` file into coreboot's root directory

### latest build (June 2017)
[download](https://github.com/merge/specs/raw/master/x220/R9N52CE_coreboot_seabios.rom)

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

## coreboot with GRUB payload (work in progress)
Compatible with Linux only - free graphics initialisation

### building
see [the coreboot wiki](https://www.coreboot.org/Build_HOWTO)
* git master from 2017-XX-XX: [coreboot config](https://github.com/merge/specs/blob/master/x220/coreboot_R9N52CE_grub.config)
* put the 3 flashregions into `3rdparty/blobs/mainboard/lenovo/x220` as
 * descriptor.bin
 * me.bin
 * gbe.bin

### latest build
TODO

### suspend to RAM on closing lid
TODO (most probably the same)

### GRUB usage
TODO test using only GRUB's config as-is, but from coreboot's GRUB

#### install Debian without grub (?)
TODO

* how to update grub config (installing a new kernel)
* hard-coded paths where grub.cfg has to reside
