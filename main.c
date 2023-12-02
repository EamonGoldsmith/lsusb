#include <stdio.h>
#include <libusb.h>

static void print_devices(libusb_device** device_list)
{
	libusb_device* dev;
	int i = 0, j = 0;
	uint8_t path[8];

	while ((dev = device_list[i++]) != NULL) {
		struct libusb_device_descriptor desc;
		int r = libusb_get_device_descriptor(dev, &desc);
		if (r < 0) {
			fprintf(stderr, "failed to get descriptor\n");
			return;
		}

		printf("%04x:%04x (bus %d, device %d)",
				desc.idVendor, desc.idProduct,
				libusb_get_bus_number(dev),
				libusb_get_device_address(dev));

		r = libusb_get_port_numbers(dev, path, sizeof(path));
		if (r > 0) {
			printf(" path: %d", path[0]);
			for (j = 1; j < r; j++) {
				printf(".%d", path[j]);
			}
		}
		printf("\n");
	}
}

int main(int argc, char* argv[])
{
	struct libusb_context* ctx;
	int err = libusb_init(&ctx); 
	if (err != 0) {
		fprintf(stderr, "failed: %s\n", libusb_strerror(err));
		return 1;
	}

	const struct libusb_version* version;
	version = libusb_get_version();

	printf("%i.%i, %s\n", version->major, version->minor, version->describe);

	libusb_device** device_list = NULL;
	size_t num_devices = libusb_get_device_list(ctx, &device_list);

	if (num_devices < 0) {
		fprintf(stderr, "failed: %s\n", libusb_strerror(num_devices));
		libusb_exit(ctx);
		return 1;
	} else if (num_devices == 0) {
		// nothing to do
		printf("no usb devices connected\n");
		libusb_exit(ctx);
		return 0;
	} else {
		print_devices(device_list);
	}

	//free all devices
	libusb_free_device_list(device_list, num_devices);

	libusb_exit(ctx);
	return 0;
}
