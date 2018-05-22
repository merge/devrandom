
## RPi 3 Setup
* `enable_uart=1` and `dtparam=spi=on` in /boot/config.txt
* `spi_bcm2835` and `spidev` in /etc/modules

## extracting VGA BIOS option ROM
Use [UEFITool](https://github.com/LongSoft/UEFITool), open the image, Search for
text "VGA Compatible BIOS" (uncheck unicode)

Double clicking the matching line in the "Messages" section should select the
appropriate RAW section. From the menu select "Action -> Section -> Extract Body...".

run fcode-utils' `romheaders` on it to check the IDs.

## copying to RPi


                (convert)
        host$ uuencode <tarball> <tarball>.ascii > <tarball>.ascii
                (transfer)
        rpi$ cat > <tarball>.ascii
        host$ pv <tarball>.ascii > /dev/ttyUSBX
                (wait)
        rpi$ (CTRL-D)
                (convert back)
        rpi$ uudecode -o <tarball> <tarball>.ascii
                (verify)
        host$ sha1sum <tarball>
        rpi$ sha1sum <tarball>


## Flashing X230
4m:

     dd of=top.rom bs=1M if=build/coreboot.rom skip=8
     flashrom -p linux_spi:dev=/dev/spidev0.0,spispeed=128 -w top.rom


8m:


     flashrom -p linux_spi:dev=/dev/spidev0.0,spispeed=128 -c "MX25L3206E/MX25L3208E" -r ifdmegbe.rom
     ./me_cleaner.py -O ifdmegbe_meclean.rom ifdmegbe.rom
     ifdtool -u ifdmegbe_meclean.rom
     flashrom -p linux_spi:dev=/dev/spidev0.0,spispeed=128 -c "MX25L3206E/MX25L3208E" -w ifdmegbe_meclean.rom.new

