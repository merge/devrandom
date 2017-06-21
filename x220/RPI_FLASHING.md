
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
Check connection by reading 2 times and comparing

### externally
`sudo flashrom -p linux_spi:dev=/dev/spidev0.0 -r flash01.bin`

### internally
While coreboot is already running and having `iomem=relaxed` on the kernel commandline.

`flashrom -p internal:laptop=force_I_want_a_brick <-r/-w> file.rom`


## Flashing X230
Some things taken from [https://www.coreboot.org/Board:lenovo/x230](https://www.coreboot.org/Board:lenovo/x230):

There are 2 ICs. The bios and thus coreboot resides in the 4MB one.
Read it 2 times as usual, check that they match. If the file is 8M,
you're flashing wrong chip, connect to the 4MB one.

For coreboot we only need to flash the top 4M.

     dd of=top.rom bs=1M if=build/coreboot.rom skip=8
     flashrom -p linux_spi:dev=/dev/spidev0.0 -w top.rom


You can flash both two chips. Now we swith to the 8MB one. What we do is
* run `me_cleaner.py`
* unlock to enable internal flashing


     flashrom -p linux_spi:dev=/dev/spidev0.0 -r ifdmegbe.rom
     ifdtool -x ifdmegbe.rom
     ./me_cleaner.py flashregion_2_intel_me.bin
     ifdtool -i ME:./flashregion_2_intel_me.bin ifdmegbe.rom
     ifdtool -u ifdmegbe.rom.new
     mv ifdmegbe.rom.new ifdmegbe.rom
     flashrom -p linux_spi:dev=/dev/spidev0.0 -w ifdmegbe.rom


### internally
To only update coreboot, we create a layout file, `x230-layout.txt`:

     0x00000000:0x007fffff ifdmegbe
     0x00800000:0x00bfffff bios

we create the 4MB coreboot bios file like we did before:

     dd of=top.rom bs=1M if=build/coreboot.rom skip=8

and flash it:

     flashrom -p internal --layout x230-layout.txt --image bios build/coreboot.rom

