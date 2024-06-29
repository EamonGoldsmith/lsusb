#!/bin/sh

lsusb: main.c
	$(CC) *.c -lc -lusb -o lsusb
