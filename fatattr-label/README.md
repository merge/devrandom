# fatattr-label
Linux tool `fatattr-label` to change a __mounted__ FAT filesystem partition's
label while it is being used. Want a USB Stick's name to be writeable?
Then this might be for you.

### What's different from `fatlabel`?
[dosfstools](https://github.com/dosfstools/dosfstools)' `fatlabel` program writes
this label too, so what's the difference?

Yes, it does. But only when the partition is __unmounted__ or just being
created. `fatattr-label` simply makes the label writeable while the partition
is being used.

### How to build
`make`

### How to use
Run `./fatattr-label` without parameters to see how to use it. This should
look like so

	Usage: ./fatattr-label mountpath [new_label]

	Example to change a label: fatattr-label MOUNTPOINT LABEL
	Example to print a label to the kernel log: fatattr-label MOUNTPOINT

	The following filesystems are mounted:

The ouput of `df -T -h` is shown, listing all currently mounted filesystems,
their types and mountpoints. `vfat`, `msdos` and `fat` types are supported.

To make this tool available, of course just put it in your `PATH` environment.

### Linux support
This tool is using the following ioctl interface that is *not* part of mainline
Linux as of now:

    #define VFAT_IOCTL_SET_LABEL _IOW('r', 0x14, __u32)

FAT12, FAT16 and FAT32 are supported, on 32bit and 64bit systems. You need to
apply the patch in the linux-patches directory and build your kernel... but:

As you can see, you also need a password and run `ccdecrypt 0001-...`. I wrote
this as part of the [eudyptula challenge](http://eudyptula-challenge.org/)
and unfortunately can't just publish them.

If you are overly interested in having support for this now, feel free to
[contact me](mailto:martink@posteo.de).
