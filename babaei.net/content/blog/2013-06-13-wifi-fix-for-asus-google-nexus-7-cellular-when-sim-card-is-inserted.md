+++
title = "Wifi Fix For Asus Google Nexus 7 Cellular, When SIM-Card Is Inserted"
slug = "wifi-fix-for-asus-google-nexus-7-cellular-when-sim-card-is-inserted"
date = 2013-06-13T03:39:00Z
tags = [ "Android", "Nexus 7" ]
#template = "post.html"
+++

As a Nexus 7 tablet user I've been struggling with my Nexus 7 WiFi from the moment that I've owned it. It was originally released with Android 4.2.0 installed. Nonetheless, Android 4.2.1 and 4.2.2 didn't get me anywhere with the WiFi issue. In fact, you may have suffered from this issue, and are already familiar with. After inserting a SIM-Card into the device, Android asks to restart the device. However, after rebooting you will notice the WiFi module won't work. No matter how hard you try it won't see any WiFi network while keeps saying "WPS failed. Please try again in a few minutes". Even tried an open unencrypted WiFi without any luck. In fact, the only solution that worked for me was removing the SIM-Card completely and do a factory reset.

Also as you may have noticed, it's been quiet some time since [an issue has been opened on Google Code around this issue on Nexus 4, Nexus 7 and Nexus 10 devices](http://code.google.com/p/android/issues/detail?id=40065). Unfortunately, it seems that Google doesn't care about this issue at all, and they closed the issue while ago. Even worse, they won't allow comments any more (At the time of this writing there are 1223 comments on the issue which shows how serious the situation is).

Anyway, if you're one of the sufferers from this issue, still there may be some good news for you. It appears that the root of all evil is inserting a non-U.S. SIM-Card on your device. Hopefully, I suddenly came across an Android application called [WiFi Fix for Android 4.x](http://www.fardjad.com/android/wifix/) by [Fardjad Davari](http://www.fardjad.com/), which completely solved the problem for me. It's been a week since I tried this application and found no more issue with my WiFi.

In fact, the process is very easy and straightforward to follow. Here is what worked for me on [Nexus 7 with latest CyanogenMod 10.1 nightly builds](http://get.cm/?device=tilapia) (It may work on Nexus 4 or Nexus 10, too):

<!-- more -->

**Note:** In order to make this work, you need a [rooted device](http://en.wikipedia.org/wiki/Android_rooting). Also, this process doesn't need factory reset.

**1.** Turn off the WiFi.  
**2.** Remove the SIM-Card.  
**3.** Reboot the tablet.  
**4.** Install [WiFix Manager](http://www.fardjad.com/android/wifix/wifixmanager.apk).  
**5.** Run WiFix Manager.  
**6.** Tap "Install WiFix".  
**7.** If Superuser asks for permission give it permanent permission by choosing "Remember choice forever".  
**8.** Now, WiFix Manager asks for reboot. So, tap "Yes" and reboot.  
**9.** After reboot, turn on the WiFi.  
**10.** Now you should have a working WiFi.  
**11.** Again, turn off the WiFi.  
**12.** Insert the SIM-Card again.  
**13.** Reboot your device.  
**14.** After reboot your turn on the WiFi once more.  
**15.** Right now, WiFi should work as normal and preferred over HSPA+/3G connection by default whenever an authenticated WiFi network is available.  

**Note:** From now on, whenever after rebooting the device if the WiFi disappears again, do the following:

**1.** Always, turn off WiFi before reboot or power off.  
**2.** Always, after reboot wait until your device picks up the HSPA+/3G signal.  
**3.** Then, turn on the WiFi.  
**4.** Now you should have a working WiFi.  

I hope it solves the issue with your Nexus device's WiFi. If you believe you've found any bug or issue, please send a support request via email to the [original developer](http://www.fardjad.com/).

