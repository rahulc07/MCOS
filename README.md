# Minecraft OS

## Intro
Are you tired of all the ram and CPU that windows, Mac OS X or even Linux is using?

Well you have come to the right place, this is the OS That ONLY Runs Minecraft!

## Why?
I and many other people have been trying to get MC to run on the lowest end hardware for a decade.  From Raspberry Pi's to school computers that are beaten by a machine that is over 15 years old. 

However, recently I have hit a road block, even arch is not light enough to run MC on some devices.

This OS uses less than a 150 MB of ram at idle and final (installed) size should be less than 2 GB.  Of course you could just run it off of USB

## HOW?
This OS Is based of Linux From Scratch 11.  From there basically everything not strictly required to run the X window manager, SOWM and the OFFICIAL MC launcher is stripped.  Leaving a compact system that is not bogged down by updates or constant internet pinging.

## Why not Gentoo or Hummingbird or OpenBSD???????

Gentoo and OpenBSD and other things all have the same problem.  They have a package manager, there is no such thing as LFS with a package manager.  For example, on gentoo I have to build the entire chain and unless specified use EVERY dependency, and install ALL of the docs, which I cannot delete later.  Binary based distributions unlike Gentoo have no way to do this.  Also I specialized the OS WITHOUT building specifically for my Hardware, meaning it will run great on any device, unlike if I was just to package gentoo.  A great example of this in MCOS is the fact I did not even touch Doxygen (A document compilier for basically everything).  This saves over 4 GB of space.  OpenBSD also is less compatible and doesn't even have proper support for the UHD 630 in my system (video drivers are required to run MC)  And I can transfer it too any system and it will boot and stil run great.  ALL of the other init systems or bootloaders or network daeomons also make the system less stable and require more dependencies and space, which is unacceptable.

# Contributions
Thanks to https://github.com/portablemc/portablemc, 95% of the code for the Offline Launcher comes from this (Stripped of course).

If you want to contribute to the project feel free to reach out 
## Demo (In a VM,real hardware is working!)
[![Watch the video](https://i.imgur.com/vKb2F1B.png)](https://youtu.be/mRYNaloFvSg)


## Download and Things to be Done
Downloads will come once I have time to package the OS into an iso (Initramfs with isolinux is complicated lol), initial release will be x86_64 ONLY

#### Things to do
 - IMG Build with saving functionality
 - ISO With EFI Support (Still in beta)
 - Further Stripping
 - Battery Optimizations
 - VPN Compatibility for bypassing blocks
