#!/bin/bash

echo "Warning this will not work on VENTOY or Optical media, if you have these
press Alt+q now to quit, otherwise just wait"
sleep 3
echo "Checking if media is writable"
sudo echo "test" > /mnt/mod/test
if cat /mnt/mod/test | grep -q 'test'; then 
    echo "Drive is Writable, continuing..."
    rm /mnt/mod/test
    echo "Copying Files"
    mkdir -pv /mnt/mod/home/mcos
    cp -rv /changes/home/mcos/.minecraft /mnt/mod/home/mcos/
    echo "Disabling Temp Write Cache, this might take a long time"
    sudo echo 1 > /proc/sys/vm/drop_caches
else
    echo "Drive is NOT Writable, exiting"
    sleep 1
    exit 
fi
