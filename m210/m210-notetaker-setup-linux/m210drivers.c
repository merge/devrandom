#include "m210drivers.h"

/**
 * This function initializes the drivers.
 */
int init() {
	int r;
	r = libusb_init(NULL);
	if(r != SUCCESS) return r;
	if(DEBUG) printf("libUSB initialized correctly\n");
	return SUCCESS;
}

/**
 * This function deinitializes the drivers. The allocated memory is freed.
 */
int deinit() {
	libusb_exit(NULL);
	if(DEBUG) printf("libUSB deinitialized correctly\n");
	return SUCCESS;
}

/**
 * Used to find the Pegasus NoteTaker hardware connected through USB.
 *
 * @post if the device is found, then device_handle is initialized with data
 * 	 associated with the device
 * @return SUCCESS if the device is found, otherwise a negative error code
 */
int search_device(int open, libusb_device_handle **device_handle) {
	libusb_device **devices_list;
	libusb_device *device;
	DEVICE_DESCRIPTOR device_descriptor;
	int r, i, found;
	i = 0;
	r = libusb_get_device_list(NULL, &devices_list);
	found = 0;
	if(DEBUG) printf("Searching for Pegasus NoteTaker hardware...\n");
	
	while((device = devices_list[i++]) != NULL) {
		r = libusb_get_device_descriptor(device, &device_descriptor);
		if(r != SUCCESS) return r;
		if(device_descriptor.idVendor == 0x0e20 && device_descriptor.idProduct == 0x0101) {
			found = 1;
			if(DEBUG) printf("Pegasus NoteTaker found (at bus %d, device %d)...\n",
						libusb_get_bus_number(device), libusb_get_device_address(device));
			if(open) {
				r = libusb_open(device, device_handle);
				if(r != SUCCESS) return r;
				if(DEBUG) printf("Pegasus NoteTaker handle taken...\n");
			}
			break;
		}
	}
	libusb_free_device_list(devices_list, 1);
	if(!found) {
		if(DEBUG) printf("Pegasus NoteTaker not found...\n");
		return DEVICE_NOT_FOUND;
	} else {
		return SUCCESS;
	}
}

/**
 * The close_device function closes the device_handle.
 */
int close_device(libusb_device_handle *device_handle) {
	libusb_close(device_handle);
	if(DEBUG) printf("Pegasus NoteTaker handle closed...\n");
	return SUCCESS;
}

/**
 * LIBUSB/Linux specific
 *
 * To detach the device from the kernel. A device is automatically attached
 * to the Linux kernel with compatible drivers (USB HID). However, in order
 * to gain full access to the device, it is required to detach it from the
 * kernel.
 *
 * @see attach_kernel
 */
int detach_kernel(libusb_device_handle *device_handle) {
	int r;
	r = libusb_detach_kernel_driver(device_handle, 0);
	if(r != SUCCESS) return r;
	r = libusb_detach_kernel_driver(device_handle, 1);
	if(r != SUCCESS) return r;
	if(DEBUG) printf("Pegasus NoteTaker detached from kernel...\n");
	return SUCCESS;
}

/**
 * LIBUSB/Linux specific
 *
 * To attach the device to the kernel. When a device is detached from the
 * Linux kernel by the drivers, it is no longer accessible to the kernel.
 * To give back the device to the kernel, it is required to attach the
 * device back to the kernel.
 *
 * @see detach_kernel
 */
int attach_kernel(libusb_device_handle *device_handle) {
	int r;
	r = libusb_attach_kernel_driver(device_handle, 0);
	if(r != SUCCESS) return r;
	r = libusb_attach_kernel_driver(device_handle, 1);
	if(r != SUCCESS) return r;
	if(DEBUG) printf("Pegasus NoteTaker attached in kernel...\n");
	return SUCCESS;
}

/**
 * To claim the USB interface 'interface'. This operation is required before
 * some other operations. Please refer to the USB and USB HID specifications
 * for more information about the protocols.
 *
 * @see put_interface
 */
int get_interface(libusb_device_handle *device_handle, int interface) {
	int r;
	r = libusb_claim_interface(device_handle, interface);
	if(r != SUCCESS) return r;
	if(DEBUG) printf("Claimed and got interface %d...\n", interface);
	return SUCCESS;
}

/**
 * This function releases a claimed interface.
 *
 * @see get_interface
 */
int put_interface(libusb_device_handle *device_handle, int interface) {
	int r;
	r = libusb_release_interface(device_handle, interface);
	if(r != SUCCESS) return r;
	if(DEBUG) printf("Release and put interface %d...\n", interface);
	return SUCCESS;
}

/**
 * The erase_memory function provides one the most important feature of the
 * drivers: the ability to empty the device's memory.
 */
int erase_memory(libusb_device_handle *device_handle) {
	int r, er;
	unsigned char buffer[3] = {ERASE_MEMORY_CMD};
	er = sizeof(buffer);

	r = libusb_control_transfer(device_handle, CONTROL_OUT, HID_SET_REPORT, ZERO, ZERO, buffer, er, USB_TIMEOUT);
	if(r != er) return r;
	if(DEBUG) printf("Pegasus NoteTaker's memory erased...\n");
	return SUCCESS;
}

/**
 * This is the implementation of the read version operation defined by the M210
 * protocol.
 */
int read_version(libusb_device_handle *device_handle) {
	int r, er, received;
	unsigned char buffer[3] = {READ_VERSION_CMD}, received_data[MAX_PACKET_SIZE];
	memset(received_data, 0, sizeof(received_data));
	er = sizeof(buffer);

	// PART 1 - Sending the command to the device
	r = libusb_control_transfer(device_handle, CONTROL_OUT, HID_SET_REPORT, ZERO, ZERO, buffer, er, USB_TIMEOUT);
	printf("DEBUG:%d\n", r);
	if(r != er) return r;
	r = get_interface(device_handle, 0);
	if(r != SUCCESS) return r;
	er = sizeof(received_data); // expected device's answer is 11 bytes long

	// PART 2 - Waiting an interrupt from the device when it is ready
	r = libusb_interrupt_transfer(device_handle, ENDPOINT_1_INTERRUPT, received_data, er, &received, USB_TIMEOUT);
	if(r != SUCCESS) return r;
	r = put_interface(device_handle, 0);
	if(r != SUCCESS) return r;

	if(DEBUG) {
		for(r = 0; r < 11; r++) printf("B#%d:%02x|", r, received_data[r]);
		printf("\n");
	}
	if(DEBUG) printf("Pegasus NoteTaker's version is read.\n");
	return SUCCESS;
}

/**
 * This utility function prints the raw contents of data_packets.
 */
int print_raw_notes(DATA_PACKET *data_packets, int packets) {
	int i, bytes;
	unsigned char *raw_data, *raw_data_ptr;
	printf("=========================== NOTES\n");
	printf("packets#:[%d]\n", packets);
	bytes = MAX_PACKET_PAYLOAD * packets;
	raw_data = (unsigned char *) calloc(bytes, sizeof(unsigned char));
	raw_data_ptr = raw_data;
	for(i = 0; i < packets; i++) {
		if(memcpy(raw_data_ptr, data_packets[i].data, MAX_PACKET_PAYLOAD) == NULL) return MEMORY_ERROR;
		raw_data_ptr += MAX_PACKET_PAYLOAD;
	}
	for(i = 0; i < bytes; i++) {
		printf("Raw:[%02x]\n", raw_data[i]);
	}
	printf("==================== END OF NOTES\n");
	free(raw_data);
}

/**
 * The get_notes function is the most important function of these drivers. It
 * allows to get the notes from the Mobile NoteTaker device.
 *
 * @pre file_name is the path to the raw output file (set to NULL if unwanted)
 * @post file_name contains the raw data present on the device's memory
 * 	 is asked, otherwise the information is only printed to the stdio
 */
int get_notes(libusb_device_handle *device_handle, const char *file_name) {
	DATA_PACKET *data_packets;
	int r, er, received, packets, i, j;
	unsigned char buffer[3] = {UPLOAD_REQUEST_CMD}, received_data[MAX_PACKET_SIZE], buffer2[3] = {ACK_MSG};
	memset(received_data, 0, sizeof(received_data));
	er = sizeof(buffer);
	
	r = libusb_set_configuration(device_handle, 1);
	if(r != SUCCESS) return r;
	
	r = get_interface(device_handle, 0);
	if(r != SUCCESS) return r;
	
	// M210 PROTOCOL START, PART 1
	r = libusb_control_transfer(device_handle, CONTROL_OUT, HID_SET_REPORT, ZERO, ZERO, buffer, er, USB_TIMEOUT);
	if(r != er) return r;
	
	if(DEBUG) printf("Notes downloading part 1 finished.\n");
	
	// PART 2
	er = sizeof(received_data);
	r = libusb_interrupt_transfer(device_handle, ENDPOINT_1_INTERRUPT, received_data, er, &received, USB_TIMEOUT);
	
	if(DEBUG) printf("OK:%d %d\n", r, received);
	if(r == TIMEOUT_ERROR && received == 0) { // no note available
		r = put_interface(device_handle, 0);
		if(r != SUCCESS) return r;
		if(DEBUG) printf("Pegasus NoteTaker is empty.\n");
		return SUCCESS;
	}
	if(r != SUCCESS) return r;
	if(er != received) return r;
	if(DEBUG) {
		for(r = 0; r < 9; r++) printf("B#%d:%02x|", r, received_data[r]);
		printf("\n");
	}
	packets = (received_data[5] << 8) + received_data[6];
	if(DEBUG) printf("Number of bytes %04xh (%dd).\n", packets, packets);
	if(DEBUG) printf("Notes downloading part 2 finished.\n");
	
	// PART 3
	er = sizeof(buffer2);
	r = libusb_control_transfer(device_handle, CONTROL_OUT, HID_SET_REPORT, ZERO, ZERO, buffer2, er, USB_TIMEOUT);
	if(r != er) return r;
	if(DEBUG) printf("Notes downloading part 3 finished.\n");
	
	// PART 4
	data_packets = (DATA_PACKET *) calloc(MAX_PACKETS, sizeof(DATA_PACKET));
	if(data_packets == NULL) return NOT_ENOUGH_MEMORY;
	for(i = 0; i < packets; i++) {
		r = libusb_interrupt_transfer(device_handle, ENDPOINT_1_INTERRUPT, received_data, MAX_PACKET_SIZE, &received, USB_TIMEOUT);
		if(r != SUCCESS) return r;
		data_packets[i].number = (received_data[0] << 8) + received_data[1];
		// loop starting at j = 2 because the two first bytes of received_data (0x00, 0x00) are ignored 
		for(j = 2; j < MAX_PACKET_SIZE; j++) {
			data_packets[i].data[j-2] = received_data[j];
		}
		if(DEBUG) printf("Packet #%d with data [%s] received.\n", data_packets[i].number, data_packets[i].data);
	}
	// checking the ordering of the packets
	for(i = 0; i < packets; i++) {
		if(data_packets[i].number != i+1) {
			if(DEBUG) printf("Mismatching numbers... %d != %d at pckt#%d\n", data_packets[i].number, i+1, packets);
			return USB_TRANSMISSION_ERROR;
		}
	}
	if(DEBUG) printf("Notes downloading part 4 finished.\n");
	
	// PART 5
	er = sizeof(buffer2);
	r = libusb_control_transfer(device_handle, CONTROL_OUT, HID_SET_REPORT, ZERO, ZERO, buffer2, er, USB_TIMEOUT);
	if(r != er) return r;
	// M210 PROTOCOL END
	
	r = put_interface(device_handle, 0);
	if(r != SUCCESS) return r;
	if(DEBUG) printf("Notes downloading part 5 finished.\n");
	if(DEBUG) print_raw_notes(data_packets, packets);
	if(DEBUG) printf("Pegasus NoteTaker's notes successfully retrieved.\n");
	if(file_name != NULL) {
		r = saveAs(file_name, data_packets, packets);
		if(r != SUCCESS) return r;
	}
	free(data_packets);
	return SUCCESS;
}

/**
 * This function saves the data_packets into file_name.
 */
int saveAs(const char *file_name, DATA_PACKET *data_packets, int packets) {
	int i, bytes;
	unsigned char *raw_data, *raw_data_ptr;
	FILE *notes;
	bytes = MAX_PACKET_PAYLOAD * packets;
	notes = fopen(file_name, "w");
	if(notes == NULL) return FILE_IO_ERROR;
	raw_data = (unsigned char *) calloc(bytes, sizeof(unsigned char));
	raw_data_ptr = raw_data;
	for(i = 0; i < packets; i++) {
		if(memcpy(raw_data_ptr, data_packets[i].data, MAX_PACKET_PAYLOAD) == NULL) return MEMORY_ERROR;
		raw_data_ptr += MAX_PACKET_PAYLOAD;
	}
	for(i = 0; i < bytes; i++) {
		if(fprintf(notes, "%02x\n", raw_data[i]) < 0) return PRINT_ERROR;
	}
	if(fclose(notes) != SUCCESS) return FILE_IO_ERROR;
	free(raw_data);
	return SUCCESS;
}

/**
 * Implementation of the set operation mode command of the M210 protocol.
 */
int set_operation_mode(libusb_device_handle *device_handle, int notetaker_led, int pen_mode) {
	int r, er;
	unsigned char buffer[6] = {SET_OPERATION_MODE_CMD, notetaker_led, pen_mode};
	er = sizeof(buffer);

	r = libusb_control_transfer(device_handle, CONTROL_OUT, HID_SET_REPORT, ZERO, ZERO, buffer, er, USB_TIMEOUT);
	if(r != er) return r;
	if(DEBUG) printf("Pegasus NoteTaker's operation mode set (to led %04x, mode %04x)\n",
		notetaker_led, pen_mode);
	return SUCCESS;
}

/**
 * Implementation of the set scale and orientation command of the M210 protocol.
 */
int set_scale_and_orientation(libusb_device_handle *device_handle, int notetaker_area_scale, int notetaker_orientation) {
	int r, er;
	unsigned char buffer[6] = {SET_SCALE_AND_ORIENTATION_CMD, notetaker_area_scale, notetaker_orientation};
	er = sizeof(buffer);

	r = libusb_control_transfer(device_handle, CONTROL_OUT, HID_SET_REPORT, ZERO, ZERO, buffer, er, USB_TIMEOUT);
	if(r != er) return r;
	if(DEBUG) printf("Pegasus NoteTaker's scale and orientation set (to scale %04x, orientation %04x)\n",
		notetaker_area_scale, notetaker_orientation);
	return SUCCESS;
}

/**
 * LIBUSB implementation test function.
 */
int test(libusb_device_handle *device_handle) {
	int notetaker_led, pen_mode, notetaker_orientation, notetaker_area_scale;

	notetaker_led = NOTETAKER_LED_MOUSE;
	pen_mode = PEN_MODE_TABLET;
	notetaker_area_scale = NOTETAKER_AREA_SCALE_BIG;
	notetaker_orientation = NOTETAKER_ORIENTATION_TOP;

	if(get_notes(device_handle, NULL) != SUCCESS) return EXIT_FAILURE;
	if(read_version(device_handle) != SUCCESS) return EXIT_FAILURE;
	if(erase_memory(device_handle) != SUCCESS) return EXIT_FAILURE;
	if(set_operation_mode(device_handle, notetaker_led, pen_mode) != SUCCESS) return EXIT_FAILURE;
	if(set_scale_and_orientation(device_handle, notetaker_area_scale, notetaker_orientation) != SUCCESS) return EXIT_FAILURE;

	return SUCCESS;
}

/**
 * The main is used to use, test and debug the library.
 */
int main(int argc, char **argv) {
	libusb_device_handle *device_handle;
	if(argc != 2) {
		printf("Usage:\n\tm210drivers <mode>\n\t\twhere mode is 'get', 'erase' or 'test'\n");
	} else {
		// initialization of the drivers
		if(init() != SUCCESS) return EXIT_FAILURE;
		if(search_device(1, &device_handle) != SUCCESS) return EXIT_FAILURE;
		if(detach_kernel(device_handle) != SUCCESS) return EXIT_FAILURE;

		if(strcmp(argv[1], "test") == 0) {
			if(test(device_handle) != SUCCESS) return EXIT_FAILURE;
		} else if(strcmp(argv[1], "get") == 0) {
			if(get_notes(device_handle, "raw.note") < SUCCESS) return EXIT_FAILURE;
		} else if(strcmp(argv[1], "erase") == 0) {
			if(erase_memory(device_handle) != SUCCESS) return EXIT_FAILURE;
		} else if(strcmp(argv[1], "read") == 0) {
			if(read_version(device_handle) != SUCCESS) return EXIT_FAILURE;
		} else {
			return EXIT_FAILURE;
		}
		
		// deinitialization of the drivers
		if(libusb_reset_device(device_handle) != SUCCESS) return EXIT_FAILURE;
		if(attach_kernel(device_handle) != SUCCESS) return EXIT_FAILURE;
		if(close_device(device_handle) != SUCCESS) return EXIT_FAILURE;
		if(deinit() != SUCCESS) return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

/**
 * This DEBUG function serves private testing purposes (for a future implementation
 * of the XY mode).
 */
int receiveXYmode(libusb_device_handle *device_handle) {
	int r, er, received;
	unsigned char received_data[6];
	memset(received_data, 0, sizeof(received_data));
	er = sizeof(received_data);
	r = set_operation_mode(device_handle, NOTETAKER_LED_MOUSE, PEN_MODE_XY);
	if(r != SUCCESS) return r;
	r = get_interface(device_handle, 0);
	if(r != SUCCESS) return r;
	while(1) {
		er = sizeof(received_data);
		r = libusb_interrupt_transfer(device_handle, ENDPOINT_1_INTERRUPT, received_data, er, &received, USB_TIMEOUT);
		if(DEBUG) {
			for(r = 0; r < 6; r++) printf("XY#%d:%02x|", r, received_data[r]);
			printf("\n");
		}
	}
	r = put_interface(device_handle, 0);
	if(r != SUCCESS) return r;
	return SUCCESS;
}

/**
 * This DEBUG function serves private testing purposes (for a future implementation
 * of the Tablet mode).
 */
int receiveTmode(libusb_device_handle *device_handle) {
	int r, er, received;
	unsigned char received_data[8];
	memset(received_data, 0, sizeof(received_data));
	er = sizeof(received_data);
	r = set_operation_mode(device_handle, NOTETAKER_LED_PEN, PEN_MODE_TABLET);
	if(r != SUCCESS) return r;
	r = set_scale_and_orientation(device_handle, NOTETAKER_AREA_SCALE_BIG, NOTETAKER_ORIENTATION_TOP);
	if(r != SUCCESS) return r;
	r = get_interface(device_handle, 0);
	if(r != SUCCESS) return r;
	while(1) {
		er = sizeof(received_data);
		r = libusb_interrupt_transfer(device_handle, ENDPOINT_2_INTERRUPT, received_data, er, &received, USB_TIMEOUT);
		if(DEBUG) {
			for(r = 0; r < 8; r++) printf("XY#%d:%02x|", r, received_data[r]);
			printf("\n");
		}
	}
	r = put_interface(device_handle, 0);
	if(r != SUCCESS) return r;
	return SUCCESS;
}

