
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

## RPi 3 Setup
* `enable_uart=1` and `dtparam=spi=on` in /boot/config.txt
* `spi_bcm2835` and `spidev` in /etc/modules
* Wifi data in /etc/wpa_supplicant/wpa_supplicant.conf
* install `libftdi1 libftdi-dev libusb-dev libpci-dev subversion build-essential pciutils usbutils zlib1g-dev`
* `svn co svn://flashrom.org/flashrom/trunk flashrom` build and install

## X220
	Screen (furthest from you)
		     __
	  MOSI  5 --|  |-- 4  GND
	   CLK  6 --|  |-- 3  N/C
	   N/C  7 --|  |-- 2  MISO
	   VCC  8 --|__|-- 1  CS

	   Edge (closest to you)

## X230
should be the same. verify with the datasheet if you have problems.


## Flashing X220
Some things taken from [https://www.coreboot.org/Board:lenovo/x220](https://www.coreboot.org/Board:lenovo/x220):

Check connection by reading 2 times and comparing

     sudo flashrom -p linux_spi:dev=/dev/spidev0.0 -r flash01.bin

### externally
     sudo flashrom -p linux_spi:dev=/dev/spidev0.0 -w coreboot.rom

### internally
While coreboot is already running and having `iomem=relaxed` on the kernel commandline:

     flashrom -p internal:laptop=force_I_want_a_brick -w coreboot.rom


## Flashing X230
Some things taken from [https://www.coreboot.org/Board:lenovo/x230](https://www.coreboot.org/Board:lenovo/x230):

There are 2 ICs. The bios and thus coreboot resides in the 4MB one.
Read it 2 times as usual, check that they match. If the file is 8M,
you're flashing wrong chip, connect to the 4 MB one. In case flashrom
needs you to select a chip, here's some data I came accross:

* model: XXX / serial: XXX / 4 MB chip: MX25L3206E (8 MB chip: EN25QH64)

Coreboot creates a 12 MB image but the BIOS is in the 4 MB chip and we only
need to flash the top 4M for coreboot.

     dd of=top.rom bs=1M if=build/coreboot.rom skip=8
     flashrom -p linux_spi:dev=/dev/spidev0.0 -w top.rom

Now we swith to the 8 MB one. This is where the Intel Management Engine firmware
resides. We remove it using `me_cleaner` and unlock the image descriptor in
order to be able to flash internally from now on.

     flashrom -p linux_spi:dev=/dev/spidev0.0 -r ifdmegbe.rom
     ./me_cleaner.py -O ifdmegbe_meclean.rom ifdmegbe.rom
     ifdtool -u ifdmegbe_meclean.rom
     flashrom -p linux_spi:dev=/dev/spidev0.0 -w ifdmegbe_meclean.rom.new


### internally
TODO test

While coreboot is already running and having `iomem=relaxed` on the kernel commandline:

To only update coreboot, we create a layout file, `x230-layout.txt`:

     0x00000000:0x007fffff ifdmegbe
     0x00800000:0x00bfffff bios

we create the 4MB coreboot bios file like we did before:

     dd of=top.rom bs=1M if=build/coreboot.rom skip=8
     flashrom -p internal --layout x230-layout.txt --image bios build/coreboot.rom

