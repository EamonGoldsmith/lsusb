
This is a simple C program to list USB devices in FreeBSD.

In the future I'd like to add the human readable name for each device but this is good enough.

If not licence is found this code is under GPLv3

usage:
```sh
$ doas ./lsusb
Password:
initialisation produced: LIBUSB_SUCCESS
4 devices found
0000:0000 (/dev/usb/1.1) error on speed
0000:0000 (/dev/usb/0.1) error on speed
046d:c246 (/dev/usb/1.2) full (12MBs)
0a12:0001 (/dev/usb/0.2) full (12MBs)
$ 
```
