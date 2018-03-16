
## RPi 3 Setup
* `enable_uart=1` and `dtparam=spi=on` in /boot/config.txt
* `spi_bcm2835` and `spidev` in /etc/modules
* Wifi data in /etc/wpa_supplicant/wpa_supplicant.conf
* install `libftdi1 libftdi-dev libusb-dev libpci-dev subversion build-essential pciutils usbutils zlib1g-dev`
* `svn co svn://flashrom.org/flashrom/trunk flashrom` build and install

## Hardware
* RPi with UART cable
* Pomona SOIC8 5250 Clip + fem. jumper wires

		   Edge of pi (furthest from you)
		 L                                                             CS
		 E                                                             |
		 F +--------------------------------------------------------------------------------------------------------+
		 T |    x    x    x    x    x    x    x    x    x    x    x    x    x    x    x    x    x    x    x    x    |
		   |    x    x    x    x    x    x    x    x    x    x    x    x    x    x    x    x    x    x    x    x    |
		 E +--------------------------------------------^----^----^----^---------------------------------------^----+
		 D                                              |    |    |    |                                       |
		 G                                             3.3V  MOSI MISO |                                      GND
		 E                                           (VCC)            CLK
		   Body of Pi (closest to you)

#### X220 / X230
	Screen (furthest from you)
		     __
	  MOSI  5 --|  |-- 4  GND
	   CLK  6 --|  |-- 3  N/C
	   N/C  7 --|  |-- 2  MISO
	   VCC  8 --|__|-- 1  CS

	   Edge (closest to you)


## extracting VGA BIOS option ROM
Use [UEFITool](https://github.com/LongSoft/UEFITool), open the image, Search for
text "VGA Compatible BIOS" (uncheck unicode)

Double clicking the matching line in the "Messages" section should select the
appropriate RAW section. From the menu select "Action -> Section -> Extract Body...".

run fcode-utils' `romheaders` on it to check the IDs.


## Flashing X220
Some things taken from [https://www.coreboot.org/Board:lenovo/x220](https://www.coreboot.org/Board:lenovo/x220):

Check connection by reading 2 times and comparing

     sudo flashrom -p linux_spi:dev=/dev/spidev0.0 -r flash01.bin
     sudo flashrom -p linux_spi:dev=/dev/spidev0.0 -r flash02.bin

For building coreboot, besides the VGA Option ROM, we need the extracted
`descriptor.bin`, `me.bin` and `gbe.bin` in
`3rdparty/blobs/mainboard/lenovo/x220`. after building a coreboot
image, write:

     sudo flashrom -p linux_spi:dev=/dev/spidev0.0 -w coreboot.rom


## Flashing X230
Some things taken from [https://www.coreboot.org/Board:lenovo/x230](https://www.coreboot.org/Board:lenovo/x230):

There are 2 ICs. The bios and thus coreboot resides in the 4MB one.
Read it 2 times as usual, check that they match. If the file is 8M,
you're flashing wrong chip, connect to the 4 MB one. In case flashrom
needs you to select a chip, here's some data I came accross:

* model: XXX / serial: XXX / 4 MB chip: MX25L3206E (8 MB chip: EN25QH64)

Read the 4MB flash image twice and compare:

     flashrom -p linux_spi:dev=/dev/spidev0.0,spispeed=128 -r top01.rom
     flashrom -p linux_spi:dev=/dev/spidev0.0,spispeed=128 -r top02.rom

Extract the UEFI VGA Option ROM and build a coreboot image. Fake IFD...
without bte, me or descriptor binaries can be built.
Coreboot creates a 12 MB image but the BIOS is in the 4 MB chip and we only
need to flash the top 4M for coreboot.

     dd of=top.rom bs=1M if=build/coreboot.rom skip=8
     flashrom -p linux_spi:dev=/dev/spidev0.0,spispeed=128 -w top.rom

Now we swith to the 8 MB one. This is where the Intel Management Engine firmware
resides. We remove it using `me_cleaner` and unlock the image descriptor in
order to be able to flash internally from now on.

     flashrom -p linux_spi:dev=/dev/spidev0.0,spispeed=128 -c "MX25L3206E/MX25L3208E" -r ifdmegbe.rom
     ./me_cleaner.py -O ifdmegbe_meclean.rom ifdmegbe.rom
     ifdtool -u ifdmegbe_meclean.rom
     flashrom -p linux_spi:dev=/dev/spidev0.0,spispeed=128 -c "MX25L3206E/MX25L3208E" -w ifdmegbe_meclean.rom.new
