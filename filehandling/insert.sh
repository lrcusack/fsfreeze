make
insmod chardev.ko
mknod /dev/filename_holder c 253 0
./tester
dmesg
