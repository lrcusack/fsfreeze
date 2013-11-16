#!/bin/bash

rmmod mod_write
#rm /dev/osqueue
make all
insmod mod_write.ko
lsmod | grep mod_write
dmesg | grep mod_write
#make device
