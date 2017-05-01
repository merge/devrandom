#ifndef __M210DRIVERS_H__
#define __DRIVERS_H__

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <libusb-1.0/libusb.h>

#define CONTROL_IN			(LIBUSB_REQUEST_TYPE_VENDOR | LIBUSB_ENDPOINT_IN)
#define CONTROL_OUT			(LIBUSB_REQUEST_TYPE_VENDOR | LIBUSB_ENDPOINT_OUT)
#define ENDPOINT_1_INTERRUPT		(1 | LIBUSB_ENDPOINT_IN)
#define ENDPOINT_2_INTERRUPT		(2 | LIBUSB_ENDPOINT_IN)
#define HID_GET_REPORT			0x01
#define HID_SET_REPORT			0x09
#define HID_REPORT_OUTPUT		0x02
#define MAX_PACKET_SIZE			64
#define MAX_PACKET_PAYLOAD		62
#define MAX_PACKETS			10000
#define USB_TIMEOUT			2000

#define ERASE_MEMORY_CMD		0x02, 0x01, 0xb0
#define READ_VERSION_CMD		0x02, 0x01, 0x95
#define UPLOAD_REQUEST_CMD		0x02, 0x01, 0xb5
#define ACK_MSG				0x02, 0x01, 0xb6
#define SET_OPERATION_MODE_CMD		0x02, 0x04, 0x80, 0xb5
#define SET_SCALE_AND_ORIENTATION_CMD	0x02, 0x04, 0x80, 0xb6

#define NOTETAKER_AREA_SCALE_BIG	0x00
#define NOTETAKER_AREA_SCALE_MEDIUM	0x04
#define NOTETAKER_AREA_SCALE_SMALL	0x09
#define NOTETAKER_ORIENTATION_TOP	0x00
#define NOTETAKER_ORIENTATION_LEFT	0x01
#define NOTETAKER_ORIENTATION_RIGHT	0x02
#define NOTETAKER_LED_NC		0x00
#define NOTETAKER_LED_PEN		0x01
#define NOTETAKER_LED_MOUSE		0x02
#define PEN_MODE_NC			0x00
#define PEN_MODE_XY			0x01
#define PEN_MODE_TABLET			0x02

#define DEBUG				1
#define SUCCESS				0
#define GENERIC_ERROR			-1
#define TIMEOUT_ERROR			LIBUSB_ERROR_TIMEOUT
#define MAX_RETRY			1
#define ZERO				0x00

#define DEVICE_NOT_FOUND		-100
#define NOT_ENOUGH_MEMORY		-101
#define USB_TRANSMISSION_ERROR		-102
#define MEMORY_ERROR			-103
#define PRINT_ERROR			-104
#define FILE_IO_ERROR			-105

struct data_packet {
	unsigned short number;
	unsigned char data[MAX_PACKET_PAYLOAD];
};
typedef struct data_packet DATA_PACKET;
typedef	struct libusb_device_descriptor DEVICE_DESCRIPTOR;

int test();
int init();
int deinit();
int search_device(int open, libusb_device_handle **device_handle);
int close_device(libusb_device_handle *device_handle);
int detach_kernel(libusb_device_handle *device_handle);
int attach_kernel(libusb_device_handle *device_handle);
int clear_endpoints(libusb_device_handle *device_handle);
int get_interface(libusb_device_handle *device_handle, int interface);
int put_interface(libusb_device_handle *device_handle, int interface);
int erase_memory(libusb_device_handle *device_handle);
int set_operation_mode(libusb_device_handle *device_handle, int notetaker_led, int pen_mode);
int set_scale_and_orientation(libusb_device_handle *device_handle, int notetaker_area_scale, int notetaker_orientation);
int read_version(libusb_device_handle *device_handle);
int get_notes(libusb_device_handle *device_handle, const char *file_name);
int print_raw_notes(DATA_PACKET *data_packets, int packets);
int saveAs(const char *file_name, DATA_PACKET *data_packets, int packets);

#endif
