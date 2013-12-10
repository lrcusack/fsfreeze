#!/bin/bash

#code to set up kernel
#goes here

#make directories if they don't exist
mkdir /freezer
mkdir /freezer_restore

#set up chardev
cd waitqueues
./out.sh
make clean
make
./in.sh
cd ..

#set up and run userspace helper
cd userspace_helper
make
./helper

