+++
title = "How to Run Multiplayer Call of Duty 4: Modern Warfare (Promod LIVE) using Wine on GNU/Linux"
slug = "how-to-run-multiplayer-call-of-duty-modern-warfare-promod-live-using-wine-on-gnu-linux"
date = 2018-07-29T18:39:00+04:30
tags = [ "COD4", "Emulation", "FLOSS", "FOSS", "Games", "GNU", "Linux", "Multiplayer", "Promod", "Promod LIVE", "UE4", "Unreal Engine", "VMWare", "Wine" ]
+++

{{< figure src="/blog/how-to-run-multiplayer-call-of-duty-modern-warfare-promod-live-using-wine-on-gnu-linux/call-of-duty-modern-warfare.webp" alt="Call of Duty 4: Modern Warfare" caption="Call of Duty 4: Modern Warfare" >}}

Well, I haven't played a multiplayer game in ages until recently, when my cool boss announced regular playtimes for all the employees in our company as a group activity in order to put the fun back into work. Since I'm a die-hard [COD4](https://www.callofduty.com/) fan and I used to play [Promod LIVE](https://promod.github.io/) heavily with colleagues and friends, I proposed Call of Duty 4: Promod LIVE 220 which happened to be favored by everybody; except there was one issue: everyone uses Microsoft Windows while I'm developing [UE4](https://unrealengine.com/) games on a single-boot [Funtoo Linux](https://funtoo.org/) system.

Naturally, my first attempt was running it inside a Windows 7 virtual machine under [VMWare Workstation for Linux](https://www.vmware.com/products/workstation-pro.html) which supports up to Direct3D 10 (the exact API used by COD4). Sadly, the experience was very poor and painful with lots of unbearable stuttering on my decent hardware. Thus, the last resort was running it under [Wine](https://www.winehq.org/), which I used to happily run many Windows applications and games under it for many years. Though, throughout those years I replaced almost every Windows application with an equivalent or an alternative Linux application until I gradually stopped using it. In the meanwhile, I also distanced myself from traditional desktop environments such as [GNOME](https://www.gnome.org/), [KDE](https://www.kde.org/), [Xfce](https://xfce.org/), and [LXDE](https://lxde.org/), while experimenting with various window managers specially [i3wm](https://i3wm.org/), which caught my attention for many good reasons. So, in the end I made up my mind and alienated myself from desktop environments once and for all.

Running a fully-fledged game engine such as [Unreal Engine 4](https://unrealengine.com/), I expected COD4, Wine, and i3 combination to work fine out of the box as it would under any other DE. Well, it turned out that I was too simple-minded about running a fullscreen game such as COD4 under Wine/i3wm. Hopefully, [as the Wine FAQ states the workaround is super easy](https://wiki.winehq.org/FAQ#How_do_I_get_Wine_to_launch_an_application_in_a_virtual_desktop.3F).

Here is the full guide on running COD4 v1.7 with Promod LIVE 2.20 on GNU/Linux.

<!--more-->

Before we proceed any further, let me make this clear that running COD4 under Wine requires disabling [PunkBuster](https://www.evenbalance.com/) (some mods don't care about PunkBuster, but Promod Live does). If you don't have any idea what the heck is that, it's a computer program that is designed to detect software used for cheating in online games by scanning the memory contents of the local machine. Due to numerous technical complexities, it won't run under Wine and I'm sure it never will. Although there is an official version of PunkBuster available for Linux, I don't think it would be possible to make COD4 and the native Linux PunkBuster work together (to be honest, I haven't tried it and don't have any clue if it works).

Note that there are two downsides to turning PunkBuster off:

1. If you are not running the server on your LAN and instead connect to a server with PunkBuster turned on (running under Windows obviously), any COD4 client without PunkBuster -- including Wine instances -- will get kicked from that server automatically as soon as they connect. So, in order for this to work the PunkBuster on the server should be disabled.

2. Anyone could easily run aimbots or other cheating software which often is not desired in a multiplayer environment.

OK, now we have cleared that, let's get back to our topic. As I mentioned I'm running Funtoo (a variant of [Gentoo Linux](https://gentoo.org/), run by Daniel Robbins, creator of Gentoo and its ex-Chief Architect). So, if you follow this guide and are running a different distro, you need to know how to install packages on your Linux distribution.

The first requisite that needs to be present on your system is Wine. To my knowledge, it is not installed by default on any Linux distribution that I'm aware of. Gentoo and accordingly Funtoo provide various Wine ebuilds (kind of synonymous to packages on other distros) in order to allow running multiple variants of Wine with different patchsets in parallel. e.g:

* <code>app-emulation/wine-any</code>: Free implementation of Windows(tm) on Unix, with optional external patchsets
* <code>app-emulation/wine-d3d9</code>: Free implementation of Windows(tm) on Unix, with Gallium Nine patchset
* <code>app-emulation/wine-staging</code>: Free implementation of Windows(tm) on Unix, with Wine-Staging patchset
* <code>app-emulation/wine-vanilla</code>: Free implementation of Windows(tm) on Unix, without external patchsets

On Gentoo or Funtoo, management of the default Wine installation will be handled with an <code>eselect</code> module. So, we are going to use the default install along the eselect module as the preferred method in this blog post. As you may now, Gentoo/Funtoo build packages from source by providing a feature called [USE flags](https://www.gentoo.org/support/use-flags/) which allows users to turn various features of a specific package on or off. USE flags can be switched on or off globally (for all packages) or individually (per package). I'm going to use <code>app-emulation/wine-vanilla</code> and turn on various USE flags (although the default USE flags should run COD4 just fine).

OK, let's turn on Direct3D 12 support using Vulkan (not necessary for running COD4, this step can be skipped) for <code>app-emulation/wine-vanilla</code> package by modifying <code>/etc/portage/package.use</code>:

{{< codeblock lang="" title="/etc/portage/package.use" line_numbers="true" >}}
# Wine
app-emulation/wine-vanilla vkd3d vulkan
{{< /codeblock >}}

If you need to turn a feature off you need to add a minus sign before the USE flags; e.g, turning on Direct3D 12 and Vulkan support while turning off Mono/.NET runtime support:

{{< codeblock lang="" title="/etc/portage/package.use" line_numbers="true" >}}
# Wine
app-emulation/wine-vanilla -mono vkd3d vulkan
{{< /codeblock >}}

A detailed list of supported USE flags and their descriptions can be found [here](https://www.gentoo.org/support/use-flags/).

Now, let's install the required packages:

{{< highlight sh >}}
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
{{</ highlight >}}

As it can be seen there is an error due to two conflicting packages which cannot be installed at the same time. Just choose <code>y</code> and then run <code>etc-update</code> so that the conflict should get resolved automatically:

{{< highlight sh >}}
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
{{</ highlight >}}

OK, let's try another go after merging the required changes using <code>etc-update</code>:

{{< highlight sh >}}
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
{{</ highlight >}}

All good! Now we have all the required packages in order to run COD4 under Wine.

Note that the installed Wine packages could be uninstalled at any time by running:

{{< highlight sh >}}
$ emerge -C virtual/wine app-eselect/eselect-wine
$ emerge --depclean
{{</ highlight >}}

OK, time to see if eselect picks up Wine module and lists our Wine installation:

{{< highlight sh >}}
$ eselect wine list

Available wine versions:
  [1]   wine-vanilla-3.11 *
{{</ highlight >}}

In the above commands output -- in spite of the fact that we only have one variant of Wine installed -- the Wine variant with the star sign on the right side is the the active Wine. If you have installed multiple Wine installations, you can set one of them as the active working Wine using (replace 1 with the number or name of the desired variant listed by the previous command):

{{< highlight sh >}}
$ eselect wine set 1
{{</ highlight >}}

For a list of available eselect options run:

{{< highlight sh >}}
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
{{</ highlight >}}

So far so good; with all the requisites in place, it's time to install COD4. Since, I prefer to keep things simple we are going to use a Windows machine or a VM to install Call of Duty 4: Modern Warfare. You may try to install it under Wine (to be honest I'm not even sure if its going to work or not). Thus, my preference is to install it on a Windows installation along with all the latest patches and updates and then move it to my Linux-powered machine.

So, let's continue with the following instructions on a Windows installation:

__Step 1__: On Microsoft Windows, install COD4 to a short path without any extra spaces or any exotic character in the folder name (e.g. <code>C:\COD4</code>) using the serial number you've got. Keep or write down the serial number somewhere safe as we are going to need it later.

__Step 2__: Download [the latest CoD4 Revive Kit from r/CoD4Promod](https://www.reddit.com/r/CoD4Promod/comments/6doxj6/cod4_revive_kit_download/) (at the time of this writing v2.0) and extract it somewhere.

__Step 3__: Navigate to the root of the extracted directory and form there install <code>Call of Duty 4 - Revive Kit\1. Getting Started\1. Patches\Call of Duty 4 Modern Warfare - v1.6 Patch.exe</code>.

__Step 4__: From the root of the extracted directory, install <code>Call of Duty 4 - Revive Kit\1. Getting Started\1. Patches\Call of Duty 4 Modern Warfare - v1.7 Patch.exe</code>.

__Step 5__: The other steps such as <code>2. Enable Stereo Mix</code> (fixes a Windows crash with various Realtek sound cards) and <code>3. Punkbuster Update Files [2017]</code> (we won't enable PunkBuster anyway, remember?) are unnecessary to follow. So, it is totally safe to ignore them; unless your are going to redistribute the installation to other Windows machines.

__Step 6__: Move the installed COD4 directory to your Linux machine.

__Step 7__: We can obtain Promod LIVE from <code>Call of Duty 4 - Revive Kit\2. Extras\Pro Mod Live v2.20</code> (I'm not sure which variant is that, but I guess it's the <code>EU</code> one) or from [the official website](https://promod.github.io/). The official website provides two variants: <code>Promod LIVE V2.20 EU</code> and <code>Promod LIVE V2.20 NE</code>. According to [the official GitHub repo](https://github.com/promod/promod4):

{{< blockquote author="promod" link="https://github.com/promod/promod4" title="What's the difference between the EU and NE version of Promod?" >}}
Q: What's the difference between the EU and NE version of Promod?
A: The NE version of Promod has rate and cl_maxpackets settings unlocked and radar does not display enemy indicators while shooting. NE stands for Non-Europe.
{{< /blockquote >}}

If you don't have any idea what does that even mean, just stick to the EU variant for a starter.

If you go with the version provided by Call of Duty 4 Revive Kit, copy over <code>Call of Duty 4 - Revive Kit\2. Extras\Pro Mod Live v2.20\pml220</code> and put it inside the <code>Mods</code> directory inside the root of your COD4 installation (e.g. <code>C:\COD4\Mods</code>, now you have <code>C:\COD4\Mods\pml220</code>). Otherwise, if you choose to go with the official website, on a Linux termnianl you would do this:

For the <code>EU</code> variant:

{{< highlight sh >}}
$ aria2c -s 16 -x 16 https://promod.github.io/releases/promodlive220_eu.zip
$ mkdir /var/tmp/promod-temp/
$ unzip promodlive220_eu.zip -d /var/tmp/promod-temp/
$ mv /var/tmp/promod-temp/pml220 /path/to/COD4/Mods/
$ rm -rf /var/tmp/promod-temp
{{</ highlight >}}

Or, the <code>NE</code> variant:

{{< highlight sh >}}
$ aria2c -s 16 -x 16 https://promod.github.io/releases/promodlive220_ne.zip
$ mkdir /var/tmp/promod-temp/
$ unzip promodlive220_ne.zip -d /var/tmp/promod-temp/
$ mv /var/tmp/promod-temp/pml220_ne /path/to/COD4/Mods/
$ rm -rf /var/tmp/promod-temp
{{</ highlight >}}

_Note 1_: I use <code>aria2c</code> as my download manager. If you don't have it use <code>wget</code> instead.

_Note 2_: Since the directory names differ from each other for <code>EU</code> and <code>NE</code> variants, it's possible to install both mods simultaneously.

__Step 8__: On Microsoft Windows, I would use a batch script like this to start the server with PunkBuster turned on:

{{< codeblock lang="bat" title="server.cmd" line_numbers="true" >}}
@echo off

iw3mp.exe +set dedicated 0 +set net_ip localhost +set net_port 28960 +set sv_punkbuster 1 +set fs_game mods/pml220 +set promod_mode match +set rcon_password some-random-password
{{< /codeblock >}}

Alternatively, if I'm going to turn off PunkBuster:

{{< codeblock lang="bat" title="server.cmd" line_numbers="true" >}}
@echo off

iw3mp.exe +set dedicated 0 +set net_ip localhost +set net_port 28960 +set sv_punkbuster 0 +set fs_game mods/pml220 +set promod_mode match_pb +set rcon_password some-random-password
{{< /codeblock >}}

Notice <code>+set sv_punkbuster 0</code> or <code>+set sv_punkbuster 1</code> which disables or enables PunkBuster. You may have noticed for <code>+set sv_punkbuster 1</code> I did <code>+set promod_mode match</code> while for <code>+set sv_punkbuster 0</code> I also did <code>+set promod_mode match_pb</code>. If we simply <code>set sv_punkbuster</code> to 0 in order to disable PunkBuster but won't change the <code>promod_mode</code> value accordingly, we are going to get "Server Violation: Punkbuster Disabled" warning on the screen every other second while playing the game. You shoud add <code>_pb</code> to <code>promod_mode</code> values when PunkBuster is disabled (e.g. <code>promod_mode match</code> becomes <code>promod_mode match_pb</code>, or <code>promod_mode lan</code> becomes <code>promod_mode lan_pb</code>, and so on).

As an extra note, we use <code>+set fs_game mods/pml220</code> for activating the <code>EU</code> variant of Promod Live or <code>+set fs_game mods/pml220_ne</code> for activating the <code>NE</code> variant. For security reasons, you may also want to replace some-random-password with your desired password inside the <code>+set rcon_password some-random-password</code> part.

Well, time to create a shell script with similar settings in order to launch <code>iw3mp.exe</code> under Wine. Note that simply launching <code>iw3mp.exe</code> inside i3wm causes trouble, as soon as it goes fullscreen. The workaround suggested by Wine FAQ is to run the game inside a virtual desktop. Therefore:

{{< codeblock lang="sh" title="server.sh" line_numbers="true" >}}
#!/usr/bin/env sh

wine explorer /desktop=COD4,2560x1440 iw3mp.exe +set dedicated 0 +set net_ip localhost +set net_port 28960 +set sv_punkbuster 0 +set fs_game mods/pml220 +set promod_mode match_pb +set rcon_password some-random-password
{{< /codeblock >}}

Consider that I use <code>/desktop=COD4,2560x1440</code> since my monitor's native resolution is QHD. You have to replace the <code>2560x1440</code> part with any supported resolution on your monitor. On Linux you can acquire your monitor's supported resolutions using (you need to run it inside a X session):

```
$ xrandr -q

Screen 0: minimum 8 x 8, current 2560 x 1440, maximum 32767 x 32767
DVI-D-0 disconnected primary (normal left inverted right x axis y axis)
HDMI-0 disconnected (normal left inverted right x axis y axis)
HDMI-1 disconnected (normal left inverted right x axis y axis)
DP-0 connected 2560x1440+0+0 (normal left inverted right x axis y axis) 600mm x 340mm
   2560x1440     59.95*+
   1920x1080     60.00    59.94    50.00  
   1680x1050     59.95  
   1600x1200     60.00  
   1440x900      59.89  
   1280x1024     75.02    60.02  
   1280x960      60.00  
   1280x800      59.81  
   1280x720      60.00    59.94    50.00  
   1152x864      75.00  
   1024x768      75.03    70.07    60.00  
   800x600       75.00    72.19    60.32    56.25  
   720x576       50.00  
   720x480       59.94  
   640x480       75.00    72.81    59.94    59.93  
   624x464       59.95  
DP-1 disconnected (normal left inverted right x axis y axis)
DP-2 disconnected (normal left inverted right x axis y axis)
DP-3 disconnected (normal left inverted right x axis y axis)
```
In case you are not going to run a server and just want to connect and play on another server:

{{< codeblock lang="sh" title="iw3mp.sh" line_numbers="true" >}}
#!/usr/bin/env sh

wine explorer /desktop=COD4,2560x1440 iw3mp.exe
{{< /codeblock >}}

__Step 9__: Set the executable permission on the shell scripts for the current user:

{{< highlight sh >}}
$ chmod u+x server.sh
$ chmod u+x iw3mp.sh
{{</ highlight >}}

Alternatively, you can make it executable by all users:

{{< highlight sh >}}
$ chmod a+x server.sh
$ chmod a+x iw3mp.sh
{{</ highlight >}}

__Step 10__: Despite the fact that we are ready to launch the COD4 multiplayer executable, we have another step to take before running the executable under Wine or we are going to experience issues due to invalid multiplayer key codes.

COD4 and its installer write their key code inside the Windows registry. So, we have to create and execute a <code>.reg</code> file in order to write our key code into Wine's registry. Normally, under Windows this is not an issue as the installer does this for us.

Create the following file somewhere on your hard drive:

{{< codeblock lang="" title="cod4.reg" line_numbers="true" >}}
Windows Registry Editor Version 5.00

; x86 Windows
[HKEY_LOCAL_MACHINE\SOFTWARE\Activision\Call of Duty 4]
"codkey"="XXXXXXXXXXXXXXXXXXXX"

; x64 Windows
[HKEY_LOCAL_MACHINE\SOFTWARE\Wow6432Node\Activision\Call of Duty 4]
"codkey"="XXXXXXXXXXXXXXXXXXXX"
{{< /codeblock >}}

The format for COD4 key codes are <code>XXXX-XXXX-XXXX-XXXX-XXXX</code>. Before assigning it to <code>codkey</code> variable in the above file, we have to transform it to <code>XXXXXXXXXXXXXXXXXXXX</code> by removing the dash characters. Also note that COD4 writes the key code in different places inside the registry depending on the Windows variant, whether it is 64-bit or 32-bit. COD4 detects Wine environment on my system as a 32-bit Windows installation. But, to stay safe and keep things simple let's use both variables as it only takes up a few more bytes inside your registry.

__Step 11__: Fire up a terminal and run the following:

{{< highlight sh >}}
$ wine start regedit cod4.reg
{{</ highlight >}}

__Step 12__: Congratulations! If you have followed the instructions correctly, you will have a working i3wm + Wine + COD4 + Promod Live 220 setup which should work on par with Windows. Let's try it!

For running the client and connecting to another server, simply run:

{{< highlight sh >}}
$ cd /path/to/COD4 && ./iw3mp.sh
{{</ highlight >}}

For running as server:

{{< highlight sh >}}
$ cd /path/to/COD4 && ./server.sh
{{</ highlight >}}

__Step 13__: If it fires up successfully, after the initial splash screen, a window which will ask for a profile name appears on the screen. This is one time only, and on the next run you should be directed to the game's main menu.

In order to connect to another Promod Live server, go to Join Game and from top/center part of the screen set Source to Local, then Game Mode to All, and finally, don't forget to set Mods to Yes by clicking on Filter Servers which is set to No by default. Click on Refresh List button multiple times and the server(s) will appear if there are any on your local network.

Alternatively, if you are going to run the server as well as playing the game, from the main menu choose Start New Server. Then, set your desired options and choose a map to start. After your server starts, you will be in Strat Mode. You will see it written on the upper right-hand side of the screen which means you are in the Nadetraining mode. You can verify this by throwing a grenade. If you fly along with the grenade to see where it hits, you are in Nadetraining mode. Now, in order to start the actual match mode (it doesn't make any difference if anyone has already joined the server or not), press the <code>`</code> tilde key on your keyboard (usually located on the top side of <code>Tab</code> key and to the left of <code>1</code> key) for the game console to show up on the screen. Type the following command and hit the <code>Enter</code> key on your keyboard; the match should restart in Standard Match mode by sending everyone present in the map to the Choose Team screen (anyone who hasn't joined yet, could join the game at this stage or even later in the middle of the game):

{{< highlight sh >}}
> /promod_mode match_pb
{{</ highlight >}}

Notic the <code>/</code> sign at the begining and the space between <code>/promod_mode</code> and <code>match_pb</code> parts of the command.

On another note, in order to reduce typing in the midst of playing, you can always access the already typed commands by pressing the tilde button and then the up arrow afterward for quick access to the previous commands; so that you can reduce your amount of typing. This only works while the game is still open. If you exit the game and run it later on, those typed commands will be gone from the commands history.

After choosing your team and your weapons of choice you will be spawned on the map alongside your teammates. The Strat Mode text on the right top corner should have been replaced by Match Standard PB: OFF, which shows that everything has been set up correctly and everybody is good to go. A few lines beneath that you should see Status and its value Not Ready in red. By pressing <code>F</code> key you can change that to Ready in green color. The first time <code>F</code> is pressed, a dialog will appear which offers you a chance to record your gameplay. You can either choose to record or cancel it as it is optional.

Furthermore, by holding down the <code>TAB</code> key you can see who has joined or joining the game. Who is ready or not, in order to remind them to press the <code>F</code> key (quite a challenge, believe me!). In addition to that, you can type messages which anyone on both sides can see by pressing the tilde key, typing your message, and then hitting the <code>Enter</code> key.

In the end, if you need to redistribute your installation to other machines, first remove <code>COD4/players</code> directory (COD4 keeps user profiles and their settings inside that directory, so removing it equals a fresh install) and then compress it using:

{{< highlight sh >}}
$ cd /COD4/installation/parent/directory
$ tar cvf COD4.tar COD4
{{</ highlight >}}

And then on the target machine:

{{< highlight sh >}}
$ tar xvf COD4.tar -C /path/to/extract/it
{{</ highlight >}}

I hope this guide covered most if not everything to get you up and running.

Enjoy! :)
