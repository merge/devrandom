#!/bin/bash

if [ $# -ne 1 ]
then
	echo "Usage:"
	echo "./setup-m210office.sh USERNAME"
	exit 0
fi

user=$1

usrBinDirectory="/usr/bin"
optDirectory="/opt/M210Office"
echo "Welcome to the M210 Office setup script..."
echo "WARNING: this script requires root privileges!"

# Creation and copying of the necessary files for the drivers
m210Directory="/home/"$user"/"$user"/M210Office"
mkdir -p $m210Directory
chown $user":"$user -R $m210Directory
mkdir -p $optDirectory
echo "Directories created."
cp -af M210_Office.jar $optDirectory
cp -af lib $optDirectory
cp -af m210office $usrBinDirectory
echo "All files were copied."
echo "M210 Office successfully installed."
