The first patch implements the ioctl() call

    #define VFAT_IOCTL_SET_LABEL _IOW('r', 0x14, __u32)

The second patch is optional. It makes this feature configurable.

These patches should apply to virtually any version of Linux. Until I
can publish them, they are encrypted with a password, using
[ccrypt](http://ccrypt.sourceforge.net/).
