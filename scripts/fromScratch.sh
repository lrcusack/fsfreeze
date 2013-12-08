make oldconfig
make clean
make -j2 bzImage
make modules
make modules_install
make install
