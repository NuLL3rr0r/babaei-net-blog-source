+++
title = "How to disable HP Proliant ML350p Gen8 P420i RAID controller, enable HBA mode (a.k.a. pass-through), and perform a FreeBSD root on ZFS installation"
slug = "disable-hp-proliant-ml350p-gen8-p420i-raid-controller-enable-hba-mode-pass-through-perform-freebsd-root-zfs-installation"
date = 2021-11-10T18:33:00+01:00
tags = [ "FOSS", "FLOSS", "FreeBSD", "GNU", "Hardware", "HP", "Proliant", "Linux", "Self-hosted", "Server", "Unix", "ZFS" ]
toc = true
draft = true
+++

I recently purchased a second-hand HP Proliant ML350p Gen8 in order to be used as a home server and to my disappointment realized I won't be able to disable the hardware RAID that comes with this model, at least at first glance. Well, there is a way to do that, which is supported by HP themselves. And, this is how to do it the easy way!

But, before we proceed any further, you might ask why do I need to disable the hardware RAID? The answer is because I need to install ZFS. There is already plenty of documentation why installing ZFS on a hardware RAID is a terrible idea. Thus, I won't go over that since it's not the focus of this article.

Again, before we go any further there's a catch you should know about. If you'd enable HBA-mode, the server won't be able to boot from any disk connected in HBA mode to the controller! You should consider this before converting to HBA mode. In case you need to perform a FreeBSD/Linux root on ZFS installation through this controller there are two solutions:

__1.__ Installing in hardware RAID mode, but making each disk a <code>RAID-0</code> array consisting of only one disk. For example, if you've got <code>8</code> disks, you'll end up with <code>8</code> <code>RAID-0</code> arrays. Then you'd perform a ZFS installation and your operating system boots as expected. Though this is not recommended and if you'd proceed with this approach, it renders the rest of this post useless.

__2.__ HP Proliant ML350p provides an SD-Card slot, which can be used to install a full system, which is not recommended due to the wear and tear effect of SDCards with each write-operation on them. In addition to that, this storage type is costly and slow. For example, a <code>SanDisk SDXC Extreme Pro 256GB</code>, which provides a write speed of <code>90MB/s</code> and read speed of <code>170MB/s</code>, costs around <code>€99,99</code> where I live. With today's standards, this is not fast at all or even good enough, especially on a server. I was also able to find a <code>Sandisk CF Express Extreme Pro 512GB type B</code>, with a write speed of <code>800MB/s</code> and a read speed of <code>1500MB/s</code>. It only costs <code>€629,-</code>, which costs an arm and leg to buy!

So, then! What's the solution one might ask? We are going to install only <code>/boot</code> partition on the internal SD Card. Note, that placing only a bootloader such as GRUB, rEFInd or other similar tools won't work as they won't be able to see the boot drive anyway! So, the only solution is to put the boot partition on the SDCard. This way, the system only reads it one time at boot and it does not even have to be an expensive SD-Card.

So, let's begin!

<!--more-->

## Switching to HBA mode

Before performing this procedure, I highly recommend to update your server's firmware to the latest version, or else this might not work!

In order to switch the P420i RAID controller on HP Proliant ML350p Gen8:

__1.__ Download [the latest version of SystemRescue](https://www.system-rescue.org/Download/). At the time of this writing, it's <code>8.05</code>.

__2.__ Create a USB bootable from the downloaded iso. On Microsoft Windows, one could use [Rufus](https://rufus.ie/en/). Or, the cross-platform free USB flash tool for Microsoft Windows, macOS, and Linux, [balenaEtcher](https://www.balena.io/etcher/).

__3.__ Before starting SystemRescue from the USB drive, make sure to delete all the RAID configurations on the controller by pressing F8 at boot time. This is mandatory! And, make sure to make a backup of everything for obvious reasons, otherwise, your data will be wiped!

__4.__ After booting SystemRescue you could type <code>startx</code> in order to start a neat and clean Xfce session. This is optional in case you'd prefer a graphical environment or a web browser. Instead, you could do everything from the initial terminal SystemRescue boots to.

__5.__ Initialize Pacman package manager, by issuing the following command:

{{< codeblock lang="sh" title="Initializing Pacman" >}}
$ Pacman -Sy
{{< /codeblock >}}

__6.__ Install the required dependencies for preparing and installing HP Smart Storage Admin CLI, <code>ssacli</code>:

{{< codeblock lang="sh" title="Installing the dependencies" >}}
$ sudo pacman -S --needed base-devel git wget yajl
{{< /codeblock >}}

__7.__ Enable the <code>nobody</code> user by changing login shell from <code>/usr/bin/nologin</code> to <code>/bin/bash</code> in the <code>/etc/passwd</code> in your favorite editor; e.g. <code>vim</code>, <code>nano</code>, etc. Just be careful with your modifications as this file is very sensitive. Although in case you mess up, you can simply reboot and your changes are reset to default since it's a live cd. We need to run the <code>makepkg</code> command as a non-root user, otherwise, it refuses to work. Since user <code>nobody</code> is disabled we need to enable it first, otherwise it results in <code>This account is currently not available</code> error.

__8.__ Get [the package description file for HP ssacli from AUR](https://aur.archlinux.org/packages/ssacli/) and prepare the package:

{{< codeblock lang="sh" title="Downloading and preparing ssacli package" >}}
$ cd /var/tmp
$ su nobody -c 'git clone https://aur.archlinux.org/ssacli.git'
$ cd ssacli
$ su nobody -c 'makepkg -si'
{{< /codeblock >}}

It may complain, about <code>sudo</code> at the end, but do not worry!

__9.__ It's time to copy the prepared <code>ssacli</code> package to the system:

{{< codeblock lang="sh" title="Manually installing ssacli package" >}}
$ cp -vr pkg/ssacli/opt /
$ cp -vr pkg/ssacli/usr/share /usr/
$ cp -vr pkg/ssacli/usr/bin/* /usr/bin/
$ rehash
{{< /codeblock >}}


__10.__ Finally, it's time to enable the HBA mode (pass-through) for the P420i controller:

{{< codeblock lang="sh" title="Enabling HBA mode" >}}
$ ssacli controller slot=0 modify hbamode=on
{{< /codeblock >}}

You can re-enable hardware RAID and disable HBA mode at any time by starting over from step <code>1</code> and only set <code>hbamode=off</code> instead of <code>hbamode=on</code>.

__11.__ Confirm the HBA mode has been enabled:

{{< codeblock lang="sh" title="Verifying HBA mode" >}}
$ ssacli controller slot=0 show | grep -i hba

   HBA Mode Enabled: True
{{< /codeblock >}}

In case, you need to check more information about the controller, omit the part begging with the pipe character <code>|</code>:

{{< codeblock lang="sh" title="Showing P420i controller information" >}}
$ ssacli controller slot=0 show

Smart Array P420i in Slot 0 (Embedded)
   Bus Interface: PCI
   Slot: 0
   Serial Number: 001438028080D00
   Cache Serial Number: PBKUC0BRH5OALM
   RAID 6 (ADG) Status: Enabled
   Controller Status: OK
   Hardware Revision: B
   Firmware Version: 8.32-0
   Firmware Supports Online Firmware Activation: False
   Cache Board Present: True
   Cache Status: Not Configured
   Total Cache Size: 1.0
   Total Cache Memory Available: 0.8
   Cache Backup Power Source: Capacitors
   Battery/Capacitor Count: 1
   Battery/Capacitor Status: OK
   Controller Temperature (C): 39
   Cache Module Temperature (C): 24
   Capacitor Temperature  (C): 25
   Number of Ports: 2 Internal only
   Driver Name: hpsa
   Driver Version: 3.4.20
   HBA Mode Enabled: True
   PCI Address (Domain:Bus:Device.Function): 0000:03:00.0
   Port Max Phy Rate Limiting Supported: False
   Host Serial Number: CZ23510556
   Sanitize Erase Supported: False
   Primary Boot Volume: Unknown (600508B1001CFFA55942D7A0BE8219D9)
   Secondary Boot Volume: None
{{< /codeblock >}}

__12.__ We're done! Reboot the server:

{{< codeblock lang="sh" title="Rebooting the server" >}}
$ reboot
{{< /codeblock >}}


## Installing FreeBSD

In order to perform a FreeBSD root on ZFS installation on the P420i RAID controller bundled with HP Proliant ML350p Gen8 in HBA mode:

__1.__ Download [a recent version of FreeBSD](https://www.freebsd.org/where/). At the time of this writing, it could be <code>13.0</code>, <code>12.2</code>, or even the upcoming <code>12.3</code>. It would be best to download the <code>.img</code> or <code>.img.xz</code> (requires extraction), as it's easier to make a bootable USB driver from.

__2.__ Create a USB bootable from the downloaded image. On Microsoft Windows, one could use [Win32 Disk Imager](https://sourceforge.net/projects/win32diskimager/). Or, in case you are on macOS, Linux, or even FreeBSD, the disk dump utility, <code>dd</code> command comes in handy (replace <code>X</code> with your USB flash drive identifier, could be figured out by using <code>fdisk</code> utility):

{{< codeblock lang="sh" title="Preparing FreeBSD bootable USB" >}}
$ sudo fdisk -l
$ sudo dd if=FreeBSD-13.0-RELEASE-amd64-memstick.img of=/dev/sdX bs=8M
{{< /codeblock >}}

__3.__ Install FreeBSD as you'd usually do, use <code>Auto (ZFS) Guided Root-on-ZFS</code> option in order to perform the installation on your ZFS RAID level of choice. Remember to keep track of your <code>HP iLO Internal SD-CARD</code> disk number in the <code>ZFS Configuration</code> dialog. In my case with the first <code>8</code> disks, <code>da0</code> to <code>da7</code> will be actual SAS disks, the last one <code>da9</code> is the USB flash drive used to boot the installer, and finally, the penultimate one <code>da8</code> is the internal SD-Card (note that the order of the internal SD-Card and the installer USB drive could change, and this is not a general rule). So, for the rest of this post, I'd be using that. When done with the installation, DO NOT REBOOT YET!

__4.__ After the installation is finished, the FreeBSD Installer will ask for any final manual modifications. So, choose <code>Yes</code> here in order to drop into a terminal. If you don't do this, you're installation simply won't boot.

__5.__ Since there might already be some data or partitions on the internal SD-Card, in my case <code>da8</code>, we are going to force destroy everything first:

{{< codeblock lang="sh" title="Destroying all partitions on the internal SD-Card" >}}
$ gpart destroy -F da8

da8 destroyed
{{< /codeblock >}}

__5.__ Then, create a GPT partition table on the internal SD-Card:

{{< codeblock lang="sh" title="Creating a GPT partition" >}}
$ gpart create -s GPT da8

da8 created
{{< /codeblock >}}

__6.__ Proceed to create a <code>freebsd-boot</code> partition. According to <code>gpart</code> manpage:

{{< blockquote author="The FreeBSD Project" link="https://www.freebsd.org/cgi/man.cgi?gpart(8)" title="FreeBSD System Manager's Manual - GPART(8)" >}}
We then create a dedicatedfreebsd-boot partition to hold the second-
stage bootloader,which will loadthe FreeBSD kernel and modules from a
UFS or ZFSfilesystem.  This partition must be larger thanthe bootstrap
code (either /boot/gptbootfor UFSor /boot/gptzfsboot forZFS), but
smaller than 545 kB since the first-stage loader will loadthe entire
partition into memory during boot,regardless of how much data it actu-
ally contains.  Wecreate a 472-block (236kB) boot partition at offset
40, which is the size of the partition table (34 blocks or17 kB) rounded
upto the nearest 4 kB boundary.
{{< /blockquote >}}

Thus, issue the following command:

{{< codeblock lang="sh" title="Creating a boot partition" >}}
$ gpart add -b 40 -s 472 -t freebsd-boot da8

da8p1 added
{{< /codeblock >}}

__7.__ Now, it's time to install the FreeBSD loader on the newly created partition and a protective MBR on the internal SD-Card:

{{< codeblock lang="sh" title="Installing the loader and a protective MBR" >}}
$ gpart bootcode -b /boot/pmbr -p /boot/gptzfsboot -i 1 da8

partcode written to da8p1
bootcode written to da8
{{< /codeblock >}}

__8.__ After this, we need a ZFS partition on the internal SD-Card:

{{< codeblock lang="sh" title="Adding a ZFS partition" >}}
$ gpart add -t freebsd-zfs da8

da8p2 added
{{< /codeblock >}}

__9.__ Time to create a ZFS pool on the newly created partition, in my case <code>da8p2</code>, and mount it:

{{< codeblock lang="sh" title="Creating and mounting a zpool" >}}
$ zpool create -o altroot=/mnt zboot /dev/da8p2
{{< /codeblock >}}

__10.__ According to <code>gptzfsboot</code> manpage:

{{< blockquote author="The FreeBSD Project" link="https://www.freebsd.org/cgi/man.cgi?query=gptzfsboot&sektion=8" title="FreeBSD System Manager's Manual - GPTZFSBOOT(8)" >}}
If /boot.config or /boot/config is present in
the boot filesystem, boot options are read from it in the same way as
boot(8).
{{< /blockquote >}}

So, we are going to instruct <code>gptzfsboot</code> to boot from our newly installed FreeBSD zpool <code>zroot/ROOT/default</code> by creating the <code>boot.config</code> file:

{{< codeblock lang="sh" title="Guiding gptzfsboot to boot from the zroot" >}}
$ echo "zfs:zroot/ROOT/default:" > /mnt/zboot/boot.config

$ cat /mnt/zboot/boot.config

zfs:zroot/ROOT/default:
{{< /codeblock >}}

__11.__ And, finally export the boot pool on the internal SD-Card and reboot:

{{< codeblock lang="sh" title="Guiding gptzfsboot to boot from the zroot" >}}
$ export zboot
$ reboot
{{< /codeblock >}}

Done :)
