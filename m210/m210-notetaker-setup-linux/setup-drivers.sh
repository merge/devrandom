#!/bin/bash

if [ $# -ne 1 ]
then
	echo "Usage:"
	echo "./setup-drivers.sh USERNAME"
	exit 0
fi

user=$1
echo "Welcome to the M210 drivers setup script..."
echo "WARNING: this script requires root privileges!"

# Compilation of the drivers
make > /dev/null
echo "M210 drivers compiled."

# Creation and copying of the necessary files for the drivers
driversDirectory="/home/"$user"/"$user"/M210Office/drivers"
mkdir -p $driversDirectory
echo "Directories created."
cp -af erase.sh $driversDirectory
cp -af get.sh $driversDirectory
cp -af m210drivers $driversDirectory
chown $user":"$user -R $driversDirectory
cp -af 50-m210.rules /etc/udev/rules.d
echo "All files were copied."

# m210 group creation and adding the current 
groupadd -f m210
echo "m210 group created."
usermod -a -G m210 $user
udevadm control --reload-rules
echo "User "$user" added to m210 group and udev rules applied."

make mrproper > /dev/null
echo "M210 drivers successfully installed."
