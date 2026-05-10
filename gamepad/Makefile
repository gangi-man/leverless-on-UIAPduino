all : flash

TARGET:=uiapduino_leverless

ADDITIONAL_C_FILES+=../rv003usb/rv003usb/rv003usb.S ../rv003usb/rv003usb/rv003usb.c gamepad.c
EXTRA_CFLAGS:=-I../rv003usb/lib -I../rv003usb/rv003usb

TARGET_MCU?=CH32V003
include ../rv003usb/ch32fun/ch32fun/ch32fun.mk

flash : cv_flash
clean : cv_clean
