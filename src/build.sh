#!/bin/bash

#Vars 
BUILD_DIR=$HOME/squash
KERNEL_VERSION=5.16.7
VERSION=1.3

#Setup 
cd $BUILD_DIR
echo "Building MCOS"
echo "Making temp folder"
mkdir -pv $BUILD_DIR/temp
cd temp

#initrd
echo "Building initramfs"
echo "Mounting Virtual Filesystems"
mkdir -pv initrd
cd $BUILD_DIR
sudo mount --bind /dev $BUILD_DIR/squashfs-root/dev
sudo mount --bind /proc $BUILD_DIR/squashfs-root/proc
sudo mount --bind /sys $BUILD_DIR/squashfs-root/sys
sudo chroot $BUILD_DIR/squashfs-root /bin/bash -c "su - -c 'mkinitramfs $KERNEL_VERSION'"
sudo cp $BUILD_DIR/squashfs-root/root/initrd.img-$KERNEL_VERSION $BUILD_DIR/temp/initrd/
sudo rm $BUILD_DIR/squashfs-root/root/initrd.img-$KERNEL_VERSION

#Apps 
echo "Building Starter"
mkdir -pv $BUILD_DIR/temp/apps/
cd $BUILD_DIR/mcos-app/final-$VERSION
gcc $( pkg-config --cflags gtk4 ) -o $BUILD_DIR/temp/apps/savewarn savewarn.c $( pkg-config --libs gtk4)
gcc $( pkg-config --cflags gtk4 ) -o $BUILD_DIR/temp/apps/mcstarter main.c $( pkg-config --libs gtk4)
cp save.sh $BUILD_DIR/temp/apps/syssave
echo "Copying to BIN!"
sudo cp $BUILD_DIR/temp/apps/* $BUILD_DIR/squashfs-root/usr/bin
# gcc $( pkg-config --cflags gtk4 ) -o injector injector.c $( pkg-config --libs gtk4)

#Squashfs 
echo "Building Squashfs"
cd $BUILD_DIR
sudo umount squashfs-root/dev
sudo umount squashfs-root/proc
sudo umount squashfs-root/sys
mkdir -pv $BUILD_DIR/temp/squash
sudo mksquashfs squashfs-root/ $BUILD_DIR/temp/squash/mcos$VERSION.squashfs

#Iso Prep
echo "Isolinux..."
mkdir -pv $BUILD_DIR/temp/final
sudo cp -r $BUILD_DIR/iso/isolinux $BUILD_DIR/temp/final


#Boot Folder
echo "Creating and building boot folder"
mkdir -pv $BUILD_DIR/temp/final/boot
mkdir -pv $BUILD_DIR/temp/final/boot/grub
mkdir -pv $BUILD_DIR/temp/final/mod
mkdir -pv $BUILD_DIR/temp/final/unmod
mkdir -pv $BUILD_DIR/temp/final/buffer
sudo cp $BUILD_DIR/temp/squash/mcos$VERSION.squashfs $BUILD_DIR/temp/final/boot/mc.squashfs
sudo cp $BUILD_DIR/temp/initrd/initrd.img-$KERNEL_VERSION $BUILD_DIR/temp/final/boot
sudo cp $BUILD_DIR/squashfs-root/boot/grub/grub.cfg $BUILD_DIR/temp/final/boot/grub
sudo cp $BUILD_DIR/squashfs-root/boot/vmlinuz-$KERNEL_VERSION $BUILD_DIR/temp/final/boot

#Building ISO
echo "Building ISO"
cd $BUILD_DIR/temp/final
sudo xorriso -as mkisofs \
 -o mcos.iso \
 -b isolinux/isolinux.bin \
 -c isolinux/boot.cat \
 -boot-load-size 4 \
 -no-emul-boot \
 -boot-info-table \
 -isohybrid-mbr /usr/lib/ISOLINUX/isohdpfx.bin -partition_offset 16 \
 -isohybrid-gpt-basdat -J -R -D -A mcos -V mcos .
#Building IMG
#cd $BUILD_DIR/temp
#mkdir -pv img
#cd img
#cp $BUILD_DIR/base.img $BUILD_DIR/temp/img/mcos.img
#sudo losetup --offset $((512*2048)) --sizelimit $((512*4403200)) --show --find $BUILD_DIR/temp/img/mcos.img
#sudo losetup --offset $((512*4405248)) --sizelimit $((512*1843200)) --show --find $BUILD_DIR/temp/img/mcos.img
#sleep 2
#sudo mkfs.ext4 /dev/loop0
#sudo mkfs.vfat /dev/loop1
#sudo mount /dev/loop0 /mnt
#sudo cp -r $BUILD_DIR/temp/final/* /mnt
#sudo grub-install --target=i386-pc --boot-directory=/mnt/boot --removable $BUILD_DIR/temp/img/mcos.img
#sudo sync 
#sudo umount /mnt
#Done
echo "Done"
echo "Launching VM"
sudo qemu-system-x86_64 -cdrom $BUILD_DIR/temp/final/mcos.iso -m 4096 -smp cores=4,threads=2 -machine q35,accel=kvm -cpu IvyBridge -vga cirrus

