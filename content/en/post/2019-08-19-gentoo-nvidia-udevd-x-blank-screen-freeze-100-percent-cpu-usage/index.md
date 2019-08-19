+++
title = "A workaround for udevd 100% cpu usage and blank screen freeze on Gentoo GNU/Linux with recent NVIDIA drivers"
slug = "gentoo-nvidia-udevd-x-blank-screen-freeze-100-percent-cpu-usage"
date = 2019-08-19T02:37:00+02:00
tags = [ "FOSS", "FLOSS", "Funtoo", "Gentoo", "GNU", "Linux", "Unix" ]
+++

A few months back due to various changes in how [Funtoo](https://www.funtoo.org/) is being managed, I migrated back from Funtoo to [Gentoo](https://www.gentoo.org/) after almost a decade. After some time I realized my laptop randomly gets stuck on a blank screen and freezes just right before my login manager ([SDDM](https://github.com/sddm/sddm)) starts. I noticed the hard-disk LED is blinking and the system is actually not freezed and probably is working and stuck on something. Checking the system or Xorg logs did not reveal anything unusual.

I even [posted my issue](https://forums.gentoo.org/viewtopic-t-1096286-start-0.html) on the [Gentoo Forums](https://forums.gentoo.org/) and when I thought the issue is gone I marked it as <code>SOLVED</code> (well, I don't turn off this laptop or reboot too much). But, the problem came back and hunted me over again.

Finally, I decided to install [JuiceSSH](https://juicessh.com/) on my phone since I do not have access to another PC for the time being. When it did freeze, I did <code>ssh</code> into my Gentoo installation and noticed <code>udevd</code>'s CPU usage is at <code>100%</code>. I looked up the forums to see if someone else having this issue or not. I cannot recall where on the forums I saw it, but it seems this was a known issue to some users with recent [NVIDIA drivers](https://www.nvidia.com/Download/index.aspx) and someone suggested blacklisting the NVIDIA drivers, so the kernel won't load them at boot time as it is going to be loaded by X later on.

Well, I did the following changes in order to blacklist the NVIDIA modules, so the kernel won't load them at boot itme:

{{< codeblock title="/etc/modprobe.d/blacklist.conf" line_numbers="true" >}}
blacklist nvidia
blacklist nvidia_drm
blacklist nvidia_modeset
blacklist nvidia_uvm
{{</ codeblock >}}

And, viola! It has been a month without any issues so far. It did solve the issue for me, once and for all. Hope it helps someone with a similar issue until this bug is officially fixed.

<!--more-->
