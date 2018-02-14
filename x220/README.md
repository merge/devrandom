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


### GRUB kernels list and settings
in `/etc/default/grub` add

     GRUB_CMDLINE_LINUX="i915.enable_fbc=0 iomem=relaxed"
     GRUB_DISABLE_SUBMENU=y


### SATA power management
have `SATA_MOBILE_LPM_POLICY` configured `3` and make sure
`link_power_management_policy` in libata sysfs reads `med_power_with_dipm`



# Thinkpad X220 product 42916Z9 serial R9N52CE
* serial number from `lshw`
* [Lenovo BIOS image](https://github.com/merge/specs/raw/master/x220/R9N52CE_orig_flash.bin)
* Winbond W25Q64.V 8MB chip

## BIOS flashing internally
Start Linux with the `iomem=relaxed` commandline option. Put it /etc/default/grub
to have it permanently. This weakens security and should only be used for flashing.

     flashrom -p internal:laptop=force_I_want_a_brick -w coreboot.rom

## coreboot with SeaBIOS payload

see [the coreboot wiki](https://www.coreboot.org/Build_HOWTO)
* git master from 2017-11-27: [coreboot config](https://github.com/merge/specs/blob/master/x220/coreboot_R9N52CE_seabios.config)
* put the 3 flashregions into `3rdparty/blobs/mainboard/lenovo/x220` as
 * descriptor.bin
 * me.bin
 * gbe.bin
* put the `pci8086,0106.rom` file into coreboot's root directory

### Debian 9: suspend to RAM on closing lid
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






# Thinkpad X230
Building coreboot can be done with fake IFD... No binaries except for the VGA Option ROM
needed. We only flash the lower 4MB after all.

## BIOS flashing internally
While coreboot is already running and having `iomem=relaxed` on the kernel commandline:

To only update coreboot, we create a layout file, `x230-layout.txt`:

     0x00000000:0x007fffff ifdmegbe
     0x00800000:0x00bfffff bios

and can use a 12MiB coreboot image to only write the bios part:

     flashrom -p internal --layout x230-layout.txt --image bios build/coreboot.rom


## coreboot with SeaBIOS payload

see [the coreboot wiki](https://www.coreboot.org/Build_HOWTO)
* latest test [coreboot config](X230_NEW_coreboot_seabios.config)
* put the extracted video bios binary in coreboot's top level directory
