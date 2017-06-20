
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

## Flashing X220
Check connection by reading 2 times and comparing

### externally
`sudo flashrom -p linux_spi:dev=/dev/spidev0.0 -r flash01.bin`

### internally
While coreboot is already running and having `iomem=relaxed` on the kernel commandline.

`flashrom -p internal:laptop=force_I_want_a_brick <-r/-w> file.rom`
