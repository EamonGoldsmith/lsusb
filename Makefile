#!/bin/sh

lsusb: main.c
	$(CC) main.c -lc -lusb -o lsusb
