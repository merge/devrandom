#!/bin/bash
# apt install gcc-arm-linux-gnueabihf

export ARCH=arm
export CROSS_COMPILE=arm-linux-gnueabihf-
make bep3_defconfig
make
