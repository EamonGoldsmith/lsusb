#!/bin/sh

lsusb: main.c
	$(CC) main.c -lusb -o lsusb
