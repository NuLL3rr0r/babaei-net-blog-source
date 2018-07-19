+++
title = "How to Run Multiplayer Call of Duty 4: Modern Warefare (ProMod) using Wine on GNU/Linux"
slug = "how-to-run-multiplayer-call-of-duty-modern-warfare-promod-using-wine-on-gnu-linux"
date = 2018-07-18T18:39:00+04:30
tags = [ "COD4", "Emulation", "Games", "GNU", "Linux", "Multiplayer", "ProMod", "VMWare", "Wine" ]
draft = true
+++

{{< figure src="/blog/how-to-run-multiplayer-call-of-duty-modern-warfare-promod-using-wine-on-gnu-linux/call-of-duty-modern-warfare.jpg" alt="Call of Duty 4: Modern Warfare" caption="Call of Duty 4: Modern Warfare" >}}

Well, I haven't played a multiplayer game in ages until recently, when my cool boss announced regular playtimes for all the employees in our company as a group activity in order to put the fun back work. Since I'm a die-hard [COD4](https://www.callofduty.com/) fan and I used to play [ProMod](https://promod.github.io/) heavily with colleagues and friends, I proposed Call of Duty 4: ProMod which happened to be favored by everybody; except there was one issue: everyone uses Microsoft Windows while I'm developing [UE4](https://unrealengine.com/) games on a single-boot [Funtoo Linux](https://funtoo.org/) system.

Natrutally, my first attemp was running it inside a Windows 7 virtual machine under [VMWare Workstation for Linux](https://www.vmware.com/products/workstation-pro.html) which supports up to Direct3D 10 (the exact API used by COD4). Sadly, the experience was very poor and painful with lots of unbearable stuttering on my decent hardware. Thus, the last resort was running it under [Wine](https://www.winehq.org/) which I used to happily run many Windows applications and games under it for many years. Though, throughout the years I replaced almost every Windows application with an equivalent or an alternative Linux application, until I gradually stopped using it. In the meanwhile, I also distanced myself from traditional desktop environments such as [GNOME](https://www.gnome.org/), [KDE](https://www.kde.org/), [Xfce](https://xfce.org/), and [LXDE](https://lxde.org/), while experimenting with various window managers specially [i3wm](https://i3wm.org/), which caught my attention for many good reasons. So, I made up my mind and aliented myself from desktop environments once and for all.

Running a fully-fledged game engine such as [Unreal Engine 4](https://unrealengine.com/), I expected COD4, Wine, and i3 combination to work fine out of the box as it would under any other DE. Well, it turned out that I was too simple minded about running a fullscreen game such as COD4 under Wine/i3wm. Hopefully, [as Wine FAQ states the workaround is super easy](https://wiki.winehq.org/FAQ#How_do_I_get_Wine_to_launch_an_application_in_a_virtual_desktop.3F).

Here is the full guide on running COD4 v1.7 with ProMod on GNU/Linux.

<!--more-->

Before we proceed any further, let me make this clear that running COD4 under Wine requires disabling [PunkBuster](https://www.evenbalance.com/). If you don't have any idea what the heck is that, it's a computer program that is designed to detect software used for cheating in online games by scanning the memory contents of the local machine. Due to numerous technical complexities, it won't run under Wine and I'm sure it never will. Although, there is an official version of PunkBuster available for Linux, I don't think it would be possible to make COD4 and the native Linux PunkBuster work together (to be honest, I haven't tried it and don't have any idea if it works).

Note that there are two downsides to turning PunkBuster off:

1. If you are not running the server on your lan and instead connect to a server with turned PunkBuster turned on (running under Windows obviously), any COD4 client without PunkBuster -- including Wine instances -- will get kicked from that server automatically as soon as they connect. So, in order for this to work the PunkBuster on the server should be disabled.

2. Anyone could easily run aimbots or other cheating software which often is not desired in multiplayer environments.

OK, now we have cleared that, let's get back to our topic. As I mentioned I'm running Funtoo (a variant of [Gentoo Linux](https://gentoo.org/), run by Daniel Robbins, creator of Gentoo). So, if you follow this guide and you are running a different distro, you need to know how to install packages on your Linux distribution.

The first requisite that needs to be present on your system is Wine. To my knowledge it is not installed by default in any Linux distribution I'm aware of. Gentoo and accordingly Funtoo provide various Wine ebuilds (kind of synonymous to packages on other distros) in order to allow running multiple variants of Wine with different patchsets in parallel. e.g:

* app-emulation/wine-any: Free implementation of Windows(tm) on Unix, with optional external patchsets
* app-emulation/wine-d3d9: Free implementation of Windows(tm) on Unix, with Gallium Nine patchset
* app-emulation/wine-staging: Free implementation of Windows(tm) on Unix, with Wine-Staging patchset
* app-emulation/wine-vanilla: Free implementation of Windows(tm) on Unix, without external patchsets

On Gentoo or Funtoo, management of the default Wine installation will be handled with an eselect module. So, we are going to use the default install along the eselect module as the preferred method in this blog post. As you may now, Gentoo/Funtoo build packages from source by providing a feature called [USE flags](https://www.gentoo.org/support/use-flags/) which allows users to turn various features of a specific package on or off. USE flags can be switched on or off globally (for all packages) or individually (per package). I'm going to use app-emulation/wine-vanilla and turn on various USE flags (although the default USE flags should run COD4 just fine).

OK, let's turn on Direct3D 12 support using Vulkan (not necessary for running COD4, this step can be skipped) for app-emulation/wine-vanilla package by modifying <code>/etc/portage/package.use</code>:

{{< codeblock lang="" title="/etc/portage/package.use" >}}
# Wine
app-emulation/wine-vanilla vkd3d vulkan
{{< /codeblock >}}

If you need to turn a feature off you need to add a minus sign before the USE flags; e.g, turning on Direct3D 12 and Vulkan support while turning off Mono/.NET runtime support:

{{< codeblock lang="" title="/etc/portage/package.use" >}}
# Wine
app-emulation/wine-vanilla -mono vkd3d vulkan
{{< /codeblock >}}

A detailed list of supported USE flags and their descriptions can be found [here](https://www.gentoo.org/support/use-flags/).

Now, let's install the required packages:

```
$ emerge -atuv virtual/wine app-eselect/eselect-wine

These are the packages that would be merged, in reverse order:

Calculating dependencies... done!
[ebuild  N     ] virtual/wine-0-r6::nokit  USE="-d3d9 -staging" ABI_X86="32 (64)" 0 KiB
[ebuild  N     ]  app-emulation/wine-vanilla-3.11:3.11::nokit  USE="X alsa cups fontconfig gecko jpeg lcms mono mp3 ncurses nls opengl perl png realtime run-exes ssl threads truetype udev udisks v4l vkd3d vulkan xcomposite xml -capi -custom-cflags -dos -gphoto2 -gsm -gssapi -gstreamer -kerberos -ldap -netapi -odbc -openal -opencl -osmesa -oss -pcap -prelink -pulseaudio -samba -scanner -sdl (-selinux) {-test} -xinerama" ABI_X86="32 (64) (-x32)" LINGUAS="en en_US fa -ar -bg -ca -cs -da -de -el -eo -es -fi -fr -he -hi -hr -hu -it -ja -ko -lt -ml -nb_NO -nl -or -pa -pl -pt_BR -pt_PT -rm -ro -ru -sk -sl -sr_RS@cyrillic -sr_RS@latin -sv -te -th -tr -uk -wa -zh_CN -zh_TW" 0 KiB
[ebuild  N     ]   app-emulation/vkd3d-1.0::nokit  USE="-spirv-tools" ABI_X86="32 (64) (-x32)" 452 KiB
[nomerge       ] x11-wm/i3-4.14.1::desktop-kit  USE="-debug -doc {-test}" 
[ebuild   R    ]  x11-libs/xcb-util-cursor-0.1.3-r1::xorg-kit  USE="-doc -static-libs {-test}" ABI_X86="32* (64) (-x32)" 0 KiB
[ebuild   R    ]   x11-libs/xcb-util-image-0.4.0::xorg-kit  USE="-doc -static-libs {-test}" ABI_X86="32* (64) (-x32)" 0 KiB
[ebuild   R    ]    x11-libs/xcb-util-0.4.0::xorg-kit  USE="-doc -static-libs {-test}" ABI_X86="32* (64) (-x32)" 0 KiB
[nomerge       ] app-emulation/wine-vanilla-3.11:3.11::nokit  USE="X alsa cups fontconfig gecko jpeg lcms mono mp3 ncurses nls opengl perl png realtime run-exes ssl threads truetype udev udisks v4l vkd3d vulkan xcomposite xml -capi -custom-cflags -dos -gphoto2 -gsm -gssapi -gstreamer -kerberos -ldap -netapi -odbc -openal -opencl -osmesa -oss -pcap -prelink -pulseaudio -samba -scanner -sdl (-selinux) {-test} -xinerama" ABI_X86="32 (64) (-x32)" LINGUAS="en en_US fa -ar -bg -ca -cs -da -de -el -eo -es -fi -fr -he -hi -hr -hu -it -ja -ko -lt -ml -nb_NO -nl -or -pa -pl -pt_BR -pt_PT -rm -ro -ru -sk -sl -sr_RS@cyrillic -sr_RS@latin -sv -te -th -tr -uk -wa -zh_CN -zh_TW" 
[ebuild  N     ]  app-emulation/wine-desktop-common-20150204::nokit  0 KiB
[ebuild  N     ]   app-eselect/eselect-wine-1.1::core-kit  0 KiB
[nomerge       ] app-emulation/vkd3d-1.0::nokit  USE="-spirv-tools" ABI_X86="32 (64) (-x32)" 
[ebuild  N     ]  dev-util/vulkan-headers-1.1.77.0-r1::dev-kit  449 KiB
[ebuild  N     ]  dev-util/spirv-headers-1.3.1_pre20180710::dev-kit  275 KiB
[ebuild  N     ]  media-libs/vulkan-loader-1.1.70.0-r1::xorg-kit  USE="X -demos -layers -wayland" ABI_X86="32 (64) (-x32)" 4,012 KiB
[nomerge       ] app-emulation/wine-vanilla-3.11:3.11::nokit  USE="X alsa cups fontconfig gecko jpeg lcms mono mp3 ncurses nls opengl perl png realtime run-exes ssl threads truetype udev udisks v4l vkd3d vulkan xcomposite xml -capi -custom-cflags -dos -gphoto2 -gsm -gssapi -gstreamer -kerberos -ldap -netapi -odbc -openal -opencl -osmesa -oss -pcap -prelink -pulseaudio -samba -scanner -sdl (-selinux) {-test} -xinerama" ABI_X86="32 (64) (-x32)" LINGUAS="en en_US fa -ar -bg -ca -cs -da -de -el -eo -es -fi -fr -he -hi -hr -hu -it -ja -ko -lt -ml -nb_NO -nl -or -pa -pl -pt_BR -pt_PT -rm -ro -ru -sk -sl -sr_RS@cyrillic -sr_RS@latin -sv -te -th -tr -uk -wa -zh_CN -zh_TW" 
[ebuild  N     ]  media-sound/mpg123-1.25.7::media-kit  USE="alsa ipv6 (-altivec) (-coreaudio) -int-quality -jack -nas -oss -portaudio -pulseaudio -sdl" ABI_X86="32 (64) (-x32)" CPU_FLAGS_X86="sse (-3dnow) (-3dnowext) (-mmx)" 0 KiB
[ebuild  N     ]   app-eselect/eselect-mpg123-0.1::core-kit  0 KiB
[ebuild  N     ]  dev-perl/XML-Simple-2.220.0::perl-kit  USE="{-test}" 0 KiB
[ebuild  N     ]   dev-perl/XML-SAX-Expat-0.510.0::perl-kit  USE="{-test}" 0 KiB
[nomerge       ] app-emulation/virtualbox-5.2.12::nokit  USE="alsa opengl pam python qt5 sdk udev -debug -doc -headless -java -libressl -lvm -pax_kernel -pulseaudio -vboxwebsrv -vnc" PYTHON_TARGETS="python2_7" 
[nomerge       ]  dev-qt/qtx11extras-5.9.4:5/5.9::kde-kit  USE="-debug {-test}" 
[nomerge       ]   dev-qt/qtgui-5.9.4-r3:5/5.9::kde-kit  USE="dbus gif jpeg libinput png udev xcb -accessibility -debug -egl -eglfs -evdev -gles2 -ibus {-test} -tslib -tuio -vnc" 
[ebuild   R    ]    x11-libs/xcb-util-renderutil-0.3.9-r1::xorg-kit  USE="-doc -static-libs {-test}" ABI_X86="32* (64) (-x32)" 0 KiB
[ebuild   R    ]    x11-libs/xcb-util-wm-0.4.1-r1::xorg-kit  USE="-doc -static-libs {-test}" ABI_X86="32* (64) (-x32)" 0 KiB
[ebuild   R    ]    x11-libs/xcb-util-keysyms-0.4.0::xorg-kit  USE="-doc -static-libs {-test}" ABI_X86="32* (64) (-x32)" 0 KiB
[nomerge       ] dev-perl/XML-Simple-2.220.0::perl-kit  USE="{-test}" 
[ebuild  N     ]  virtual/perl-Storable-2.560.0-r2::perl-kit  0 KiB
[nomerge       ] app-emulation/wine-vanilla-3.11:3.11::nokit  USE="X alsa cups fontconfig gecko jpeg lcms mono mp3 ncurses nls opengl perl png realtime run-exes ssl threads truetype udev udisks v4l vkd3d vulkan xcomposite xml -capi -custom-cflags -dos -gphoto2 -gsm -gssapi -gstreamer -kerberos -ldap -netapi -odbc -openal -opencl -osmesa -oss -pcap -prelink -pulseaudio -samba -scanner -sdl (-selinux) {-test} -xinerama" ABI_X86="32 (64) (-x32)" LINGUAS="en en_US fa -ar -bg -ca -cs -da -de -el -eo -es -fi -fr -he -hi -hr -hu -it -ja -ko -lt -ml -nb_NO -nl -or -pa -pl -pt_BR -pt_PT -rm -ro -ru -sk -sl -sr_RS@cyrillic -sr_RS@latin -sv -te -th -tr -uk -wa -zh_CN -zh_TW" 
[ebuild  N     ]  app-emulation/wine-mono-4.7.1:4.7.1::nokit  0 KiB
[ebuild  N     ]  app-emulation/wine-gecko-2.47-r1:2.47::nokit  ABI_X86="32 (64)" 0 KiB
[blocks B      ] <=media-libs/vulkan-loader-1.1.70.0-r999 ("<=media-libs/vulkan-loader-1.1.70.0-r999" is blocking dev-util/vulkan-headers-1.1.77.0-r1)

Total: 21 packages (15 new, 6 reinstalls), Size of downloads: 5,186 KiB
Conflict: 1 block (1 unsatisfied)

 * Error: The above package list contains packages which cannot be
 * installed at the same time on the same system.

  media-libs/vulkan-loader-1.1.70.0-r1:0/0::xorg-kit, ebuild scheduled for merge pulled in by
    media-libs/vulkan-loader[abi_x86_32(-)?,abi_x86_64(-)?,abi_x86_x32(-)?,abi_mips_n32(-)?,abi_mips_n64(-)?,abi_mips_o32(-)?,abi_ppc_32(-)?,abi_ppc_64(-)?,abi_s390_32(-)?,abi_s390_64(-)?,X] (media-libs/vulkan-loader[abi_x86_32(-),abi_x86_64(-),X]) required by app-emulation/vkd3d-1.0:0/0::nokit, ebuild scheduled for merge
    media-libs/vulkan-loader[abi_x86_32(-)?,abi_x86_64(-)?,abi_x86_x32(-)?,abi_mips_n32(-)?,abi_mips_n64(-)?,abi_mips_o32(-)?,abi_ppc_32(-)?,abi_ppc_64(-)?,abi_s390_32(-)?,abi_s390_64(-)?] (media-libs/vulkan-loader[abi_x86_32(-),abi_x86_64(-)]) required by app-emulation/wine-vanilla-3.11:3.11/3.11::nokit, ebuild scheduled for merge

  dev-util/vulkan-headers-1.1.77.0-r1:0/0::dev-kit, ebuild scheduled for merge pulled in by
    dev-util/vulkan-headers required by app-emulation/vkd3d-1.0:0/0::nokit, ebuild scheduled for merge


For more information about Blocked Packages, please refer to the following
section of the Gentoo Linux x86 Handbook (architecture is irrelevant):

https://wiki.gentoo.org/wiki/Handbook:X86/Working/Portage#Blocked_packages


The following USE changes are necessary to proceed:
 (see "package.use" in the portage(5) man page for more details)
# required by x11-libs/xcb-util-0.4.0::xorg-kit
# required by app-emulation/vkd3d-1.0::nokit
# required by app-emulation/wine-vanilla-3.11::nokit[vkd3d]
# required by virtual/wine-0-r6::nokit
# required by virtual/wine (argument)
>=x11-libs/xcb-util-wm-0.4.1-r1 abi_x86_32
# required by app-emulation/wine-vanilla-3.11::nokit[vulkan]
# required by virtual/wine-0-r6::nokit
# required by virtual/wine (argument)
>=media-libs/vulkan-loader-1.1.70.0-r1 abi_x86_32
# required by x11-libs/xcb-util-0.4.0::xorg-kit
# required by app-emulation/vkd3d-1.0::nokit
# required by app-emulation/wine-vanilla-3.11::nokit[vkd3d]
# required by virtual/wine-0-r6::nokit
# required by virtual/wine (argument)
>=x11-libs/xcb-util-renderutil-0.3.9-r1 abi_x86_32
# required by x11-libs/xcb-util-0.4.0::xorg-kit
# required by app-emulation/vkd3d-1.0::nokit
# required by app-emulation/wine-vanilla-3.11::nokit[vkd3d]
# required by virtual/wine-0-r6::nokit
# required by virtual/wine (argument)
>=x11-libs/xcb-util-cursor-0.1.3-r1 abi_x86_32
# required by x11-libs/xcb-util-0.4.0::xorg-kit
# required by app-emulation/vkd3d-1.0::nokit
# required by app-emulation/wine-vanilla-3.11::nokit[vkd3d]
# required by virtual/wine-0-r6::nokit
# required by virtual/wine (argument)
>=x11-libs/xcb-util-image-0.4.0 abi_x86_32
# required by x11-libs/xcb-util-0.4.0::xorg-kit
# required by app-emulation/vkd3d-1.0::nokit
# required by app-emulation/wine-vanilla-3.11::nokit[vkd3d]
# required by virtual/wine-0-r6::nokit
# required by virtual/wine (argument)
>=x11-libs/xcb-util-keysyms-0.4.0 abi_x86_32
# required by app-emulation/wine-vanilla-3.11::nokit[vkd3d]
# required by virtual/wine-0-r6::nokit
# required by virtual/wine (argument)
>=app-emulation/vkd3d-1.0 abi_x86_32
# required by x11-libs/xcb-util-image-0.4.0::xorg-kit
# required by x11-libs/xcb-util-cursor-0.1.3-r1::xorg-kit
# required by x11-wm/i3-4.14.1::desktop-kit
# required by @selected
# required by @world (argument)
>=x11-libs/xcb-util-0.4.0 abi_x86_32

Would you like to add these changes to your config files? [Yes/No] y

Autounmask changes successfully written.

 * IMPORTANT: config file '/etc/portage/package.use' needs updating.
 * See the CONFIGURATION FILES and CONFIGURATION FILES UPDATE TOOLS
 * sections of the emerge man page to learn how to update config files.

 * In order to avoid wasting time, backtracking has terminated early
 * due to the above autounmask change(s). The --autounmask-backtrack=y
 * option can be used to force further backtracking, but there is no
 * guarantee that it will produce a solution.
```

As it can be seen there is an error due to two conflicting packages which cannot be installed at the same time. Just choose <code>y</code> and then run <code>etc-update</code> so that the conflict should get resolved automatically:

```
$ etc-update

Scanning Configuration files...
The following is the list of files which need updating, each
configuration file is followed by a list of possible replacement files.
1) /etc/portage/package.use (1)
Please select a file to edit by entering the corresponding number.
              (don't use -3, -5, -7 or -9 if you're unsure what to do)
              (-1 to exit) (-3 to auto merge all files)
                           (-5 to auto-merge AND not use 'mv -i')
                           (-7 to discard all updates)
                           (-9 to discard all updates AND not use 'rm -i'): -3
Replacing /etc/portage/package.use with /etc/portage/._cfg0000_package.use
mv: overwrite ‘/etc/portage/package.use’? y
Exiting: Nothing left to do; exiting. :)
```

OK, let's try another go after merging the required changes using <code>etc-update</code>:

```
$ emerge -atuv virtual/wine app-eselect/eselect-wine

These are the packages that would be merged, in reverse order:

Calculating dependencies... done!
[ebuild  N     ] virtual/wine-0-r6::nokit  USE="-d3d9 -staging" ABI_X86="32 (64)" 0 KiB
[ebuild  N     ]  app-emulation/wine-vanilla-3.11:3.11::nokit  USE="X alsa cups fontconfig gecko jpeg lcms mono mp3 ncurses nls opengl perl png realtime run-exes ssl threads truetype udev udisks v4l vkd3d vulkan xcomposite xml -capi -custom-cflags -dos -gphoto2 -gsm -gssapi -gstreamer -kerberos -ldap -netapi -odbc -openal -opencl -osmesa -oss -pcap -prelink -pulseaudio -samba -scanner -sdl (-selinux) {-test} -xinerama" ABI_X86="32 (64) (-x32)" LINGUAS="en en_US fa -ar -bg -ca -cs -da -de -el -eo -es -fi -fr -he -hi -hr -hu -it -ja -ko -lt -ml -nb_NO -nl -or -pa -pl -pt_BR -pt_PT -rm -ro -ru -sk -sl -sr_RS@cyrillic -sr_RS@latin -sv -te -th -tr -uk -wa -zh_CN -zh_TW" 0 KiB
[ebuild  N     ]   app-emulation/vkd3d-1.0::nokit  USE="-spirv-tools" ABI_X86="32 (64) (-x32)" 452 KiB
[nomerge       ] x11-wm/i3-4.14.1::desktop-kit  USE="-debug -doc {-test}" 
[ebuild   R    ]  x11-libs/xcb-util-cursor-0.1.3-r1::xorg-kit  USE="-doc -static-libs {-test}" ABI_X86="32* (64) (-x32)" 0 KiB
[ebuild   R    ]   x11-libs/xcb-util-image-0.4.0::xorg-kit  USE="-doc -static-libs {-test}" ABI_X86="32* (64) (-x32)" 0 KiB
[ebuild   R    ]    x11-libs/xcb-util-0.4.0::xorg-kit  USE="-doc -static-libs {-test}" ABI_X86="32* (64) (-x32)" 0 KiB
[nomerge       ] app-emulation/wine-vanilla-3.11:3.11::nokit  USE="X alsa cups fontconfig gecko jpeg lcms mono mp3 ncurses nls opengl perl png realtime run-exes ssl threads truetype udev udisks v4l vkd3d vulkan xcomposite xml -capi -custom-cflags -dos -gphoto2 -gsm -gssapi -gstreamer -kerberos -ldap -netapi -odbc -openal -opencl -osmesa -oss -pcap -prelink -pulseaudio -samba -scanner -sdl (-selinux) {-test} -xinerama" ABI_X86="32 (64) (-x32)" LINGUAS="en en_US fa -ar -bg -ca -cs -da -de -el -eo -es -fi -fr -he -hi -hr -hu -it -ja -ko -lt -ml -nb_NO -nl -or -pa -pl -pt_BR -pt_PT -rm -ro -ru -sk -sl -sr_RS@cyrillic -sr_RS@latin -sv -te -th -tr -uk -wa -zh_CN -zh_TW" 
[ebuild  N     ]  app-emulation/wine-desktop-common-20150204::nokit  0 KiB
[ebuild  N     ]   app-eselect/eselect-wine-1.1::core-kit  0 KiB
[nomerge       ] app-emulation/vkd3d-1.0::nokit  USE="-spirv-tools" ABI_X86="32 (64) (-x32)" 
[ebuild  N     ]  dev-util/spirv-headers-1.3.1_pre20180710::dev-kit  275 KiB
[ebuild  N     ]  media-libs/vulkan-loader-1.1.70.0-r1::xorg-kit  USE="X -demos -layers -wayland" ABI_X86="32 (64) (-x32)" 4,012 KiB
[nomerge       ] app-emulation/wine-vanilla-3.11:3.11::nokit  USE="X alsa cups fontconfig gecko jpeg lcms mono mp3 ncurses nls opengl perl png realtime run-exes ssl threads truetype udev udisks v4l vkd3d vulkan xcomposite xml -capi -custom-cflags -dos -gphoto2 -gsm -gssapi -gstreamer -kerberos -ldap -netapi -odbc -openal -opencl -osmesa -oss -pcap -prelink -pulseaudio -samba -scanner -sdl (-selinux) {-test} -xinerama" ABI_X86="32 (64) (-x32)" LINGUAS="en en_US fa -ar -bg -ca -cs -da -de -el -eo -es -fi -fr -he -hi -hr -hu -it -ja -ko -lt -ml -nb_NO -nl -or -pa -pl -pt_BR -pt_PT -rm -ro -ru -sk -sl -sr_RS@cyrillic -sr_RS@latin -sv -te -th -tr -uk -wa -zh_CN -zh_TW" 
[ebuild  N     ]  media-sound/mpg123-1.25.7::media-kit  USE="alsa ipv6 (-altivec) (-coreaudio) -int-quality -jack -nas -oss -portaudio -pulseaudio -sdl" ABI_X86="32 (64) (-x32)" CPU_FLAGS_X86="sse (-3dnow) (-3dnowext) (-mmx)" 0 KiB
[ebuild  N     ]   app-eselect/eselect-mpg123-0.1::core-kit  0 KiB
[ebuild  N     ]  dev-perl/XML-Simple-2.220.0::perl-kit  USE="{-test}" 0 KiB
[ebuild  N     ]   dev-perl/XML-SAX-Expat-0.510.0::perl-kit  USE="{-test}" 0 KiB
[nomerge       ] app-emulation/virtualbox-5.2.12::nokit  USE="alsa opengl pam python qt5 sdk udev -debug -doc -headless -java -libressl -lvm -pax_kernel -pulseaudio -vboxwebsrv -vnc" PYTHON_TARGETS="python2_7" 
[nomerge       ]  dev-qt/qtx11extras-5.9.4:5/5.9::kde-kit  USE="-debug {-test}" 
[nomerge       ]   dev-qt/qtgui-5.9.4-r3:5/5.9::kde-kit  USE="dbus gif jpeg libinput png udev xcb -accessibility -debug -egl -eglfs -evdev -gles2 -ibus {-test} -tslib -tuio -vnc" 
[ebuild   R    ]    x11-libs/xcb-util-renderutil-0.3.9-r1::xorg-kit  USE="-doc -static-libs {-test}" ABI_X86="32* (64) (-x32)" 0 KiB
[ebuild   R    ]    x11-libs/xcb-util-wm-0.4.1-r1::xorg-kit  USE="-doc -static-libs {-test}" ABI_X86="32* (64) (-x32)" 0 KiB
[ebuild   R    ]    x11-libs/xcb-util-keysyms-0.4.0::xorg-kit  USE="-doc -static-libs {-test}" ABI_X86="32* (64) (-x32)" 0 KiB
[nomerge       ] dev-perl/XML-Simple-2.220.0::perl-kit  USE="{-test}" 
[ebuild  N     ]  virtual/perl-Storable-2.560.0-r2::perl-kit  0 KiB
[nomerge       ] app-emulation/wine-vanilla-3.11:3.11::nokit  USE="X alsa cups fontconfig gecko jpeg lcms mono mp3 ncurses nls opengl perl png realtime run-exes ssl threads truetype udev udisks v4l vkd3d vulkan xcomposite xml -capi -custom-cflags -dos -gphoto2 -gsm -gssapi -gstreamer -kerberos -ldap -netapi -odbc -openal -opencl -osmesa -oss -pcap -prelink -pulseaudio -samba -scanner -sdl (-selinux) {-test} -xinerama" ABI_X86="32 (64) (-x32)" LINGUAS="en en_US fa -ar -bg -ca -cs -da -de -el -eo -es -fi -fr -he -hi -hr -hu -it -ja -ko -lt -ml -nb_NO -nl -or -pa -pl -pt_BR -pt_PT -rm -ro -ru -sk -sl -sr_RS@cyrillic -sr_RS@latin -sv -te -th -tr -uk -wa -zh_CN -zh_TW" 
[ebuild  N     ]  app-emulation/wine-mono-4.7.1:4.7.1::nokit  0 KiB
[ebuild  N     ]  app-emulation/wine-gecko-2.47-r1:2.47::nokit  ABI_X86="32 (64)" 0 KiB

Total: 20 packages (14 new, 6 reinstalls), Size of downloads: 4,737 KiB

Would you like to merge these packages? [Yes/No] y
>>> Verifying ebuild manifests
>>> Running pre-merge checks for app-emulation/wine-vanilla-3.11
>>> Emerging (1 of 20) app-emulation/wine-gecko-2.47-r1::nokit
>>> Installing (1 of 20) app-emulation/wine-gecko-2.47-r1::nokit
>>> Emerging (2 of 20) app-emulation/wine-mono-4.7.1::nokit
>>> Installing (2 of 20) app-emulation/wine-mono-4.7.1::nokit
>>> Emerging (3 of 20) virtual/perl-Storable-2.560.0-r2::perl-kit
>>> Installing (3 of 20) virtual/perl-Storable-2.560.0-r2::perl-kit
>>> Emerging (4 of 20) x11-libs/xcb-util-keysyms-0.4.0::xorg-kit
>>> Installing (4 of 20) x11-libs/xcb-util-keysyms-0.4.0::xorg-kit
>>> Emerging (5 of 20) x11-libs/xcb-util-wm-0.4.1-r1::xorg-kit
>>> Installing (5 of 20) x11-libs/xcb-util-wm-0.4.1-r1::xorg-kit
>>> Emerging (6 of 20) x11-libs/xcb-util-renderutil-0.3.9-r1::xorg-kit
>>> Installing (6 of 20) x11-libs/xcb-util-renderutil-0.3.9-r1::xorg-kit
>>> Emerging (7 of 20) dev-perl/XML-SAX-Expat-0.510.0::perl-kit
>>> Installing (7 of 20) dev-perl/XML-SAX-Expat-0.510.0::perl-kit
>>> Emerging (8 of 20) app-eselect/eselect-mpg123-0.1::core-kit
>>> Installing (8 of 20) app-eselect/eselect-mpg123-0.1::core-kit
>>> Emerging (9 of 20) dev-perl/XML-Simple-2.220.0::perl-kit
>>> Installing (9 of 20) dev-perl/XML-Simple-2.220.0::perl-kit
>>> Emerging (10 of 20) media-sound/mpg123-1.25.7::media-kit
>>> Installing (10 of 20) media-sound/mpg123-1.25.7::media-kit
>>> Emerging (11 of 20) media-libs/vulkan-loader-1.1.70.0-r1::xorg-kit
>>> Installing (11 of 20) media-libs/vulkan-loader-1.1.70.0-r1::xorg-kit
>>> Emerging (12 of 20) dev-util/spirv-headers-1.3.1_pre20180710::dev-kit
>>> Installing (12 of 20) dev-util/spirv-headers-1.3.1_pre20180710::dev-kit
>>> Emerging (13 of 20) app-eselect/eselect-wine-1.1::core-kit
>>> Installing (13 of 20) app-eselect/eselect-wine-1.1::core-kit
>>> Emerging (14 of 20) x11-libs/xcb-util-0.4.0::xorg-kit
>>> Recording app-eselect/eselect-wine in "world" favorites file...
>>> Installing (14 of 20) x11-libs/xcb-util-0.4.0::xorg-kit
>>> Emerging (15 of 20) app-emulation/wine-desktop-common-20150204::nokit
>>> Installing (15 of 20) app-emulation/wine-desktop-common-20150204::nokit
>>> Emerging (16 of 20) x11-libs/xcb-util-image-0.4.0::xorg-kit
>>> Installing (16 of 20) x11-libs/xcb-util-image-0.4.0::xorg-kit
>>> Emerging (17 of 20) x11-libs/xcb-util-cursor-0.1.3-r1::xorg-kit
>>> Installing (17 of 20) x11-libs/xcb-util-cursor-0.1.3-r1::xorg-kit
>>> Emerging (18 of 20) app-emulation/vkd3d-1.0::nokit
>>> Installing (18 of 20) app-emulation/vkd3d-1.0::nokit
>>> Emerging (19 of 20) app-emulation/wine-vanilla-3.11::nokit
>>> Installing (19 of 20) app-emulation/wine-vanilla-3.11::nokit
>>> Emerging (20 of 20) virtual/wine-0-r6::nokit
>>> Installing (20 of 20) virtual/wine-0-r6::nokit
>>> Recording virtual/wine in "world" favorites file...
>>> Jobs: 20 of 20 complete                         Load avg: 3.2, 11.5, 12.1
>>> Auto-cleaning packages...

>>> No outdated packages were found on your system.

 * GNU info directory index is up-to-date.
```

All good! Now we have all the required packages in order to run COD4 under Wine.

Note that the installed Wine packages could be uninstalled at any time by running:

```
$ emerge -C virtual/wine app-eselect/eselect-wine
$ emerge --depclean
```

OK, time to see if eselect picks up Wine module and lists our Wine installation:

```
$ eselect wine list

Available wine versions:
  [1]   wine-vanilla-3.11 *
```

If you have installed multiple Wine installations, you can set one as the active working Wine using (replace 1 with the number or name of the desired variant listed by the previous command):

```
$ eselect wine set 1
```

For a list of available eselect options run:

```
$ eselect wine help

Manage active wine version
Usage: eselect wine <action> <options>

Standard actions:
  help                      Display help text
  usage                     Display usage information
  version                   Display version information

Extra actions:
  deregister <target>       Deregister a package with the eselect module (Internal use only)
    --vanilla                 Deregister a package with vanilla
    --staging                 Deregister a package with staging
    --d3d9                    Deregister a package with d3d9
    --any                     Deregister a package with any
    --force                   Forcibly remove a package
    target                    A fully qualified variant e.g.
                               wine-1.9.23, wine-vanilla-2.0, or wine-staging-2.1.1
  list                      List available wine versions
    --vanilla                 List the available 'wine-vanilla'
    --staging                 List the available 'wine-staging'
    --d3d9                    List the available 'wine-d3d9'
    --any                     List the available 'wine-any'
  register <target>         Register a new package with the eselect module (Internal use only)
    --vanilla                 Register a new package with vanilla
    --staging                 Register a new package with staging
    --d3d9                    Register a new package with d3d9
    --any                     Register a new package with any
    target                    A fully qualified variant e.g.
                               wine-1.9.23, wine-vanilla-2.0, or wine-staging-2.1.1
  set <target>              Set a new wine version
    --vanilla                 Set only the 'wine-vanilla' symlinks
    --staging                 Set only the 'wine-staging' symlinks
    --d3d9                    Set only the 'wine-d3d9' symlinks
    --any                     Set only the 'wine-any' symlinks
    target                    Target name or number (from 'list' action)
  show                      Show the active wine version
    --vanilla                 Show the active 'wine-vanilla'
    --staging                 Show the active 'wine-staging'
    --d3d9                    Show the active 'wine-d3d9'
    --any                     Show the active 'wine-any'
  unset                     Remove wine symlinks
    --vanilla                 Remove the 'wine-vanilla' symlinks
    --staging                 Remove the 'wine-staging' symlinks
    --d3d9                    Remove the 'wine-d3d9' symlinks
    --any                     Remove the 'wine-any' symlinks
    --all                     Unset active wine and all variants
  update                    Set highest version installed active
    --vanilla                 Update the 'wine-vanilla' symlinks
    --staging                 Update the 'wine-staging' symlinks
    --d3d9                    Update the 'wine-d3d9' symlinks
    --any                     Update the 'wine-any' symlinks
    --all                     Update main active wine and all variants
    --if-unset                Reuse currently selected version if it appears valid
```

So far so good; with all the requisites out of the way, it's time to install COD4.
