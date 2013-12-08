make
insmod chardev.ko
mknod /dev/freeze c 253 0
./tester
dmesg
