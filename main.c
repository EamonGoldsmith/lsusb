#include <stdio.h>
#include <libusb.h>

void display_version(void)
{
	const struct libusb_version* version;
	version = libusb_get_version();

	printf("%i.%i, %s\n",
			version->major, version->minor,
			version->describe
			);
}

int main(int argc, char* argv[])
{
	struct libusb_context* ctx = NULL;
	int err = libusb_init(&ctx); 
	if (err != 0) {
		fprintf(stderr, "failed: %s\n", libusb_strerror(err));
		return 1;
	}

	display_version();

	libusb_device** device_list = NULL;
	size_t num_devices = libusb_get_device_list(ctx, &device_list);
	printf("number of devices: %li\n", num_devices);


	//free all devices
	libusb_free_device_list(device_list, num_devices);

	libusb_exit(ctx);
	return 0;
}
