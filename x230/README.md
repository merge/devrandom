## ram rom images
dump

	cat bottom.rom top.rom > firmware.rom

split

	dd of=top.rom bs=1M if=build/coreboot.rom skip=8
	dd of=bottom.rom bs=1M if=build/coreboot.rom count=8


## kernel and sys conf
apply all this as it may be dependent on each other
### BFQ block scheduler
see the [docs](https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/tree/Documentation/block/bfq-iosched.txt)
* `IOSCHED_BFQ=y`
* `cat /sys/block/sda/queue/scheduler`
* `echo bfq > /sys/block/sda/queue/scheduler`

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


## X230 Lenovo BIOS keys

| Keys | Function |
| --- | --- |
| Enter | Startup Interrupt Menu |
| ESC | to Resume normal startup |
| F1 | to Enter the BIOS Setup Utility |
| F10 | to diagnose hardware |
| F11 | to recover your system |
| F12 | Boot menu |

