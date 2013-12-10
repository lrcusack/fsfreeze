#!/bin/bash
dmesg -c
#ls > /freezer/one/two/three/junk.txt
#ls > /freezer/one/two/in.txt
#ls > /freezer/one/trunk.txt
ls > /freezer/junk.txt
echo "waited properly"
ls > /freezer/in.txt
echo "waited again"
ls > /freezer/trunk.txt
echo "-------------results---------------"
dmesg
