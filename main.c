#include <stdio.h>
#include <libusb.h>
#include <string.h>

const struct libusb_version *version;
libusb_context *ctx;

#define MAX_PATH 20

const char* speed_string(uint8_t s)
{
	switch(s)
	{
		case LIBUSB_SPEED_UNKNOWN:
			return "unkown speed";
		case LIBUSB_SPEED_LOW:
			return "low (1.5MBs)";
		case LIBUSB_SPEED_FULL:
			return "full (12MBs)";
		case LIBUSB_SPEED_HIGH:
			return "high (480MBs)";
		default:
			return "error on speed";
	}
}

int main(int argc, char* argv[])
{
	// get the library version
	if ((version = libusb_get_version()) == NULL) {
		printf("failed getting library version\n");
		return 1;
	}
	
	// initialise
	int err = libusb_init(&ctx);
	if (err != 0) {
		printf("failed to get library context\n");
		return 1;
	}
	printf("initialisation produced: %s\n", libusb_error_name(err));

	// create device list
	libusb_device **list;
	size_t ndevs = libusb_get_device_list(ctx, &list);

	printf("%zu devices found\n", ndevs);

	for (size_t i = 0; i < ndevs; i++) {
		struct libusb_device* d = list[i];
		struct libusb_device_descriptor desc;
		int err = libusb_get_device_descriptor(d, &desc);
		if (err > 0) {
			printf("failed to get the device path: %s\n",
					libusb_error_name(err));
			continue;
		}

		printf("%04x:%04x (/dev/usb/%d.%d) %s\n",
				desc.idVendor,
				desc.idProduct,
				libusb_get_bus_number(d),
				libusb_get_device_address(d),
				speed_string(libusb_get_device_speed(d)));
	}
	
	// destroy device list in list
	libusb_free_device_list(list, 1);

	libusb_exit(ctx);

	return 0;
}
