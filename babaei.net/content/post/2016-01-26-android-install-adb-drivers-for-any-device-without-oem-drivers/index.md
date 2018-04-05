+++
title = "Android: Install ADB drivers for any device without OEM drivers"
slug = "android-install-adb-drivers-for-any-device-without-oem-drivers"
date = 2016-01-26T03:38:37Z
tags = [ "ADB", "Android", "Nexus 5", "Nexus 7", "Windows" ]
+++

{{< figure src="/blog/android-install-adb-drivers-for-any-device-without-oem-drivers/android-robot.png" alt="Figure 1. Android Robot" caption="Figure 1. Android Robot" >}}

Well, I started my _Android_ development on a [Samsung I9100 Galaxy S II](http://www.gsmarena.com/samsung_i9100_galaxy_s_ii-3621.php). I never had any trouble getting ADB to work on _Microsoft Windows_ since I had the drivers from Samsung which was already installed due to my previous [Cyanogenmod](http://www.cyanogenmod.org/) installation process. Afterwards, I received a [Nexus 7](http://www.gsmarena.com/asus_google_nexus_7-4850.php) and a bit latter a [Nexus 5](http://www.gsmarena.com/lg_nexus_5-5705.php) which became my primary development device of choice. _Google_ did a good job by providing ADB drivers for All Nexus devices inside the SDK or as a [small separate download on Android Developers website](http://developer.android.com/sdk/win-usb.html) which was very easy to install. The trouble began when my development process involved testing my applications and games on devices other than Nexus ones I had. For some manufacturers I was never able to find the drivers. Finding the correct driver for each device was a huge pain until I found a solution that became a remedy for all my troubles getting ADB to work with any Android device, even without the OEM drivers. It even became my preferred alternative to manufacturer's provided ADB drivers for all my other devices till this day, since I hate the bloat-ware and useless crap they provide along with their drivers which is inevitable to install anyway.

In the rest of this post I'm going to share my easy solution with you:

<!--more-->

_1_. First you have to download [Google USB driver](http://developer.android.com/sdk/win-usb.html) which is a small download around __8 MB__ in size and extract it somewhere. If you have the Android SDK installed it usually resides inside <code>&lt;sdk root&gt;\extras\google\usb_driver\\</code>. So, you do not have to download it separately in that case.

{{< figure src="/blog/android-install-adb-drivers-for-any-device-without-oem-drivers/google-usb-driver-android-sdk.png" alt="Figure 2. The Android SDK Manager with the Google USB Driver selected" caption="Figure 2. The Android SDK Manager with the Google USB Driver selected" >}}

_2_. Now, you have to find your device's hardware ID. In order to do that, the first step involves turning on _Android Debugging_ on your device. On some devices it is known as _ADB Debugging_, _USB Debugging_ or something similar. On your Android device, go to _Settings > Developer Options_ and you should find it there, then check it. If you do not have _Developer Options_ inside _Settings_, you must go to _Settings > About Phone_ and tap on _Build Number_ __7__ times repeatedly. A pop-up should appear and tell you that you have enabled developer options. Now, go back to _Settings_ and you will find it there right before _About Phone_.

_3_. Then, connect your device to your Windows PC and on your PC go to _Control Panel > Device Manager_. You will find your device with a yellow exclamation mark. As an example, on one of my devices it's _'TP9.7-1500DC'_ and on the other one it's _'IdeaTab S6000'_ or simply _'Android'_ for another device (check Figure 3. below). Right click on your Android device name with yellow exclamation mark and click _Properties_. A window with a few tabs will appear. Go to the _Details_ tab and inside _Property_ combo box look for _Hardware Ids_ and select it. You will find the _Hardware Ids_ inside the _Value_ section below the _Property_ combo box that you've just used to find the IDs (Figure 4.). Now, right click on one of the IDs inside the _Value_ box and hit _Select All_ to select all the _Hardware Ids_. After selecting all the IDs, once more right click on one of the selected IDs and choose _Copy_. You've just got all the _Hardware Ids_ for your Android device.

{{< figure src="/blog/android-install-adb-drivers-for-any-device-without-oem-drivers/device-manager-unknown-android-device.png" alt="Figure 3. Unknown Android device with a yellow exclamation mark inside Windows Device Manager" caption="Figure 3. Unknown Android device with a yellow exclamation mark inside Windows Device Manager" >}}

{{< figure src="/blog/android-install-adb-drivers-for-any-device-without-oem-drivers/android-device-hardware-ids.png" alt="Figure 4. Extracted Hardware Ids for unknown Android device from Windows Device Manager" caption="Figure 4. Extracted Hardware Ids for unknown Android device from Windows Device Manager" >}}

Here is a list of some of my devices with their _Hardware Ids_:

{{< codeblock lang="" title="Example Hardware Ids" plain="true" >}}
;Nexus 4
USB\VID_18D1&PID_4EE2&REV_0228&MI_01
USB\VID_18D1&PID_4EE2&MI_01

;Motorola Moto G
USB\VID_22B8&PID_2E76&REV_0228&MI_02
USB\VID_22B8&PID_2E76&MI_02
;Motorola Networking Interface
USB\VID_22B8&PID_2E82&REV_0228&MI_01
USB\VID_22B8&PID_2E82&MI_01

;i.onik TP9.7-1500DC Retina
USB\VID_2207&PID_0006&REV_0222
USB\VID_2207&PID_0006

;Sony Xperia M Dual C2005
USB\VID_0FCE&PID_519B&REV_0228&MI_01
USB\VID_0FCE&PID_519B&MI_01

;Lenovo IdeaTab S6000-H
USB\VID_17EF&PID_75E2&REV_0255&MI_01
USB\VID_17EF&PID_75E2&MI_01

;Samsung Galaxy S4 GT-I9500
USB\VID_04E8&PID_6860&REV_0400&ADB
USB\VID_04E8&PID_6860&ADB
USB\SAMSUNG_MOBILE&ADB
USB\SAMSUNG_MOBILE&MI_03
USB\Vid_04E8&Pid_6860&MI_03
USB\Vid_04E8&Pid_6860&Class_FF&SubClass_42&Prot_01
USB\SAMSUNG_MOBILE&Class_FF&SubClass_42&Prot_01

;Samsung Galaxy S4-mini GT-I9190
USB\VID_04E8&PID_6860&REV_0400&ADB
USB\VID_04E8&PID_6860&ADB
USB\SAMSUNG_MOBILE&ADB
USB\SAMSUNG_MOBILE&MI_01
USB\Vid_04E8&Pid_6860&MI_01
USB\Vid_04E8&Pid_6860&Class_FF&SubClass_42&Prot_01
USB\SAMSUNG_MOBILE&Class_FF&SubClass_42&Prot_01

;HUAWEI G610-U20
USB\VID_12D1&PID_1038&REV_0255&MI_01
USB\VID_12D1&PID_1038&MI_01

;HUAWEI U8950-1
USB\VID_12D1&PID_1038&REV_0231&MI_01
USB\VID_12D1&PID_1038&MI_01

;Samsung Note 10.1 SM-P6012
USB\VID_04E8&PID_6860&REV_0400&ADB
USB\VID_04E8&PID_6860&ADB
USB\SAMSUNG_MOBILE&ADB
USB\SAMSUNG_MOBILE&MI_03
USB\Vid_04E8&Pid_6860&MI_03
USB\Vid_04E8&Pid_6860&Class_FF&SubClass_42&Prot_01
USB\SAMSUNG_MOBILE&Class_FF&SubClass_42&Prot_01

;HTC Desire 616 dual sim Android Phone
USB\VID_0BB4&PID_0EDD&REV_0216&MI_01
USB\VID_0BB4&PID_0EDD&MI_01
{{< /codeblock >}}

_4_. In this step make a copy of your Google USB Driver that you've just downloaded or took from your Android SDK folder. There must be a file named _android_winusb.inf_ inside that folder. Open that up inside your favorite text editor. It utilizes [Windows INF format](https://en.wikipedia.org/wiki/INF_file). An untouched copy of that file looks like this:

{{< codeblock lang="inf" title="android_winusb.inf" >}}
;
; Android WinUsb driver installation.
;
[Version]
Signature           = "$Windows NT$"
Class               = AndroidUsbDeviceClass
ClassGuid           = {3F966BD9-FA04-4ec5-991C-D326973B5128}
Provider            = %ProviderName%
DriverVer           = 08/28/2014,11.0.0000.00000
CatalogFile.NTx86   = androidwinusb86.cat
CatalogFile.NTamd64 = androidwinusba64.cat

[ClassInstall32]
Addreg = AndroidWinUsbClassReg

[AndroidWinUsbClassReg]
HKR,,,0,%ClassName%
HKR,,Icon,,-1


[Manufacturer]
%ProviderName% = Google, NTx86, NTamd64


[Google.NTx86]

;Google Nexus One
%SingleAdbInterface%        = USB_Install, USB\VID_18D1&PID_0D02
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_0D02&MI_01
%SingleAdbInterface%        = USB_Install, USB\VID_18D1&PID_4E11
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_4E12&MI_01

;Google Nexus S
%SingleAdbInterface%        = USB_Install, USB\VID_18D1&PID_4E21
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_4E22&MI_01
%SingleAdbInterface%        = USB_Install, USB\VID_18D1&PID_4E23
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_4E24&MI_01

;Google Nexus 7
%SingleBootLoaderInterface% = USB_Install, USB\VID_18D1&PID_4E40
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_4E42&MI_01
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_4E44&MI_01

;Google Nexus Q
%SingleBootLoaderInterface% = USB_Install, USB\VID_18D1&PID_2C10
%SingleAdbInterface%        = USB_Install, USB\VID_18D1&PID_2C11

;Google Nexus (generic)
%SingleBootLoaderInterface% = USB_Install, USB\VID_18D1&PID_4EE0
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_4EE2&MI_01
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_4EE4&MI_02
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_4EE6&MI_01
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_4EE7

;Google Glass
%SingleAdbInterface%        = USB_Install, USB\VID_18D1&PID_9001
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_9001&MI_01

;Project Tango (generic)
%SingleBootLoaderInterface% = USB_Install, USB\VID_18D1&PID_4D00
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_4D02&MI_01
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_4D04&MI_02
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_4D06&MI_01
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_4D07


[Google.NTamd64]

;Google Nexus One
%SingleAdbInterface%        = USB_Install, USB\VID_18D1&PID_0D02
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_0D02&MI_01
%SingleAdbInterface%        = USB_Install, USB\VID_18D1&PID_4E11
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_4E12&MI_01

;Google Nexus S
%SingleAdbInterface%        = USB_Install, USB\VID_18D1&PID_4E21
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_4E22&MI_01
%SingleAdbInterface%        = USB_Install, USB\VID_18D1&PID_4E23
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_4E24&MI_01

;Google Nexus 7
%SingleBootLoaderInterface% = USB_Install, USB\VID_18D1&PID_4E40
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_4E42&MI_01
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_4E44&MI_01

;Google Nexus Q
%SingleBootLoaderInterface% = USB_Install, USB\VID_18D1&PID_2C10
%SingleAdbInterface%        = USB_Install, USB\VID_18D1&PID_2C11

;Google Nexus (generic)
%SingleBootLoaderInterface% = USB_Install, USB\VID_18D1&PID_4EE0
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_4EE2&MI_01
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_4EE4&MI_02
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_4EE6&MI_01
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_4EE7

;Google Glass
%SingleAdbInterface%        = USB_Install, USB\VID_18D1&PID_9001
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_9001&MI_01

;Project Tango (generic)
%SingleBootLoaderInterface% = USB_Install, USB\VID_18D1&PID_4D00
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_4D02&MI_01
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_4D04&MI_02
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_4D06&MI_01
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_4D07


[USB_Install]
Include = winusb.inf
Needs   = WINUSB.NT

[USB_Install.Services]
Include     = winusb.inf
AddService  = WinUSB,0x00000002,WinUSB_ServiceInstall

[WinUSB_ServiceInstall]
DisplayName     = %WinUSB_SvcDesc%
ServiceType     = 1
StartType       = 3
ErrorControl    = 1
ServiceBinary   = %12%\WinUSB.sys

[USB_Install.Wdf]
KmdfService = WINUSB, WinUSB_Install

[WinUSB_Install]
KmdfLibraryVersion  = 1.9

[USB_Install.HW]
AddReg  = Dev_AddReg

[Dev_AddReg]
HKR,,DeviceInterfaceGUIDs,0x10000,"{F72FE0D4-CBCB-407d-8814-9ED673D0DD6B}"

[USB_Install.CoInstallers]
AddReg    = CoInstallers_AddReg
CopyFiles = CoInstallers_CopyFiles

[CoInstallers_AddReg]
HKR,,CoInstallers32,0x00010000,"WdfCoInstaller01009.dll,WdfCoInstaller","WinUSBCoInstaller2.dll"

[CoInstallers_CopyFiles]
WinUSBCoInstaller2.dll
WdfCoInstaller01009.dll

[DestinationDirs]
CoInstallers_CopyFiles=11

[SourceDisksNames]
1 = %DISK_NAME%,,,\i386
2 = %DISK_NAME%,,,\amd64

[SourceDisksFiles.x86]
WinUSBCoInstaller2.dll  = 1
WdfCoInstaller01009.dll = 1

[SourceDisksFiles.amd64]
WinUSBCoInstaller2.dll  = 2
WdfCoInstaller01009.dll = 2

[Strings]
ProviderName                = "Google, Inc."
SingleAdbInterface          = "Android ADB Interface"
CompositeAdbInterface       = "Android Composite ADB Interface"
SingleBootLoaderInterface   = "Android Bootloader Interface"
WinUSB_SvcDesc              = "Android USB Driver"
DISK_NAME                   = "Android WinUsb installation disk"
ClassName                   = "Android Device"
{{< /codeblock >}}

_5_. Look for _&#91;Google.NTx86&#93;_ and _&#91;Google.NTamd64&#93;_ sections inside the file. Remember the _Hardware Ids_ that we have just copied to clipboard? We have to add them to the end of these sections to be able to install the driver on both x86 and x64 versions of Windows. But the point is, you cannot simply paste them here. For each line of hardware ID we've got, we have to add _'%CompositeAdbInterface%     = USB_Install, '_ at the beginning of them. Optionally you can add comments starting with a semicolon _';'_ character for each device. OK, if this is all confusing, considering my previously provided list of _Hardware Ids_, the modified file looks like this (I'm sure it's self-explanatory if you look for my comments and compare them to both the original file and the list of _Hardware Ids_):

{{< codeblock lang="inf" title="android_winusb.inf" >}}
;
; Android WinUsb driver installation.
;
[Version]
Signature           = "$Windows NT$"
Class               = AndroidUsbDeviceClass
ClassGuid           = {3F966BD9-FA04-4ec5-991C-D326973B5128}
Provider            = %ProviderName%
DriverVer           = 08/28/2014,11.0.0000.00000
CatalogFile.NTx86   = androidwinusb86.cat
CatalogFile.NTamd64 = androidwinusba64.cat

[ClassInstall32]
Addreg = AndroidWinUsbClassReg

[AndroidWinUsbClassReg]
HKR,,,0,%ClassName%
HKR,,Icon,,-1


[Manufacturer]
%ProviderName% = Google, NTx86, NTamd64


[Google.NTx86]

;Google Nexus One
%SingleAdbInterface%        = USB_Install, USB\VID_18D1&PID_0D02
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_0D02&MI_01
%SingleAdbInterface%        = USB_Install, USB\VID_18D1&PID_4E11
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_4E12&MI_01

;Google Nexus S
%SingleAdbInterface%        = USB_Install, USB\VID_18D1&PID_4E21
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_4E22&MI_01
%SingleAdbInterface%        = USB_Install, USB\VID_18D1&PID_4E23
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_4E24&MI_01

;Google Nexus 7
%SingleBootLoaderInterface% = USB_Install, USB\VID_18D1&PID_4E40
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_4E42&MI_01
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_4E44&MI_01

;Google Nexus Q
%SingleBootLoaderInterface% = USB_Install, USB\VID_18D1&PID_2C10
%SingleAdbInterface%        = USB_Install, USB\VID_18D1&PID_2C11

;Google Nexus (generic)
%SingleBootLoaderInterface% = USB_Install, USB\VID_18D1&PID_4EE0
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_4EE2&MI_01
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_4EE4&MI_02
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_4EE6&MI_01
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_4EE7

;Google Glass
%SingleAdbInterface%        = USB_Install, USB\VID_18D1&PID_9001
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_9001&MI_01

;Project Tango (generic)
%SingleBootLoaderInterface% = USB_Install, USB\VID_18D1&PID_4D00
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_4D02&MI_01
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_4D04&MI_02
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_4D06&MI_01
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_4D07

;
; MY DEVICES HARDWARE IDS / X86 / START
;

;Nexus 4
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_4EE2&REV_0228&MI_01
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_4EE2&MI_01

;Motorola Moto G
%CompositeAdbInterface%     = USB_Install, USB\VID_22B8&PID_2E76&REV_0228&MI_02
%CompositeAdbInterface%     = USB_Install, USB\VID_22B8&PID_2E76&MI_02
;Motorola Networking Interface
%CompositeAdbInterface%     = USB_Install, USB\VID_22B8&PID_2E82&REV_0228&MI_01
%CompositeAdbInterface%     = USB_Install, USB\VID_22B8&PID_2E82&MI_01

;i.onik TP9.7-1500DC Retina
%CompositeAdbInterface%     = USB_Install, USB\VID_2207&PID_0006&REV_0222
%CompositeAdbInterface%     = USB_Install, USB\VID_2207&PID_0006

;Sony Xperia M Dual C2005
%CompositeAdbInterface%     = USB_Install, USB\VID_0FCE&PID_519B&REV_0228&MI_01
%CompositeAdbInterface%     = USB_Install, USB\VID_0FCE&PID_519B&MI_01

;Lenovo IdeaTab S6000-H
%CompositeAdbInterface%     = USB_Install, USB\VID_17EF&PID_75E2&REV_0255&MI_01
%CompositeAdbInterface%     = USB_Install, USB\VID_17EF&PID_75E2&MI_01

;Samsung Galaxy Note Edge
;SAMSUNG_Android
%CompositeAdbInterface%     = USB_Install, USB\VID_04E8&PID_6860&REV_0400&MI_03
%CompositeAdbInterface%     = USB_Install, USB\VID_04E8&PID_6860&MI_03
;CDC Serial
%CompositeAdbInterface%     = USB_Install, USB\VID_04E8&PID_6860&REV_0400&MI_01
%CompositeAdbInterface%     = USB_Install, USB\VID_04E8&PID_6860&MI_01

;Samsung Galaxy S4 GT-I9500
%CompositeAdbInterface%     = USB_Install, USB\VID_04E8&PID_6860&REV_0400&ADB
%CompositeAdbInterface%     = USB_Install, USB\VID_04E8&PID_6860&ADB
%CompositeAdbInterface%     = USB_Install, USB\SAMSUNG_MOBILE&ADB
%CompositeAdbInterface%     = USB_Install, USB\SAMSUNG_MOBILE&MI_03
%CompositeAdbInterface%     = USB_Install, USB\Vid_04E8&Pid_6860&MI_03
%CompositeAdbInterface%     = USB_Install, USB\Vid_04E8&Pid_6860&Class_FF&SubClass_42&Prot_01
%CompositeAdbInterface%     = USB_Install, USB\SAMSUNG_MOBILE&Class_FF&SubClass_42&Prot_01

;Samsung Galaxy S4-mini GT-I9190
%CompositeAdbInterface%     = USB_Install, USB\VID_04E8&PID_6860&REV_0400&ADB
%CompositeAdbInterface%     = USB_Install, USB\VID_04E8&PID_6860&ADB
%CompositeAdbInterface%     = USB_Install, USB\SAMSUNG_MOBILE&ADB
%CompositeAdbInterface%     = USB_Install, USB\SAMSUNG_MOBILE&MI_01
%CompositeAdbInterface%     = USB_Install, USB\Vid_04E8&Pid_6860&MI_01
%CompositeAdbInterface%     = USB_Install, USB\Vid_04E8&Pid_6860&Class_FF&SubClass_42&Prot_01
%CompositeAdbInterface%     = USB_Install, USB\SAMSUNG_MOBILE&Class_FF&SubClass_42&Prot_01

;HUAWEI G610-U20
%CompositeAdbInterface%     = USB_Install, USB\VID_12D1&PID_1038&REV_0255&MI_01
%CompositeAdbInterface%     = USB_Install, USB\VID_12D1&PID_1038&MI_01

;HUAWEI U8950-1
%CompositeAdbInterface%     = USB_Install, USB\VID_12D1&PID_1038&REV_0231&MI_01
%CompositeAdbInterface%     = USB_Install, USB\VID_12D1&PID_1038&MI_01

;Samsung Note 10.1 SM-P6012
%CompositeAdbInterface%     = USB_Install, USB\VID_04E8&PID_6860&REV_0400&ADB
%CompositeAdbInterface%     = USB_Install, USB\VID_04E8&PID_6860&ADB
%CompositeAdbInterface%     = USB_Install, USB\SAMSUNG_MOBILE&ADB
%CompositeAdbInterface%     = USB_Install, USB\SAMSUNG_MOBILE&MI_03
%CompositeAdbInterface%     = USB_Install, USB\Vid_04E8&Pid_6860&MI_03
%CompositeAdbInterface%     = USB_Install, USB\Vid_04E8&Pid_6860&Class_FF&SubClass_42&Prot_01
%CompositeAdbInterface%     = USB_Install, USB\SAMSUNG_MOBILE&Class_FF&SubClass_42&Prot_01

;HTC Desire 616 dual sim Android Phone
%CompositeAdbInterface%     = USB_Install, USB\VID_0BB4&PID_0EDD&REV_0216&MI_01
%CompositeAdbInterface%     = USB_Install, USB\VID_0BB4&PID_0EDD&MI_01

;
; MY DEVICES HARDWARE IDS / X86 / END
;


[Google.NTamd64]

;Google Nexus One
%SingleAdbInterface%        = USB_Install, USB\VID_18D1&PID_0D02
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_0D02&MI_01
%SingleAdbInterface%        = USB_Install, USB\VID_18D1&PID_4E11
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_4E12&MI_01

;Google Nexus S
%SingleAdbInterface%        = USB_Install, USB\VID_18D1&PID_4E21
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_4E22&MI_01
%SingleAdbInterface%        = USB_Install, USB\VID_18D1&PID_4E23
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_4E24&MI_01

;Google Nexus 7
%SingleBootLoaderInterface% = USB_Install, USB\VID_18D1&PID_4E40
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_4E42&MI_01
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_4E44&MI_01

;Google Nexus Q
%SingleBootLoaderInterface% = USB_Install, USB\VID_18D1&PID_2C10
%SingleAdbInterface%        = USB_Install, USB\VID_18D1&PID_2C11

;Google Nexus (generic)
%SingleBootLoaderInterface% = USB_Install, USB\VID_18D1&PID_4EE0
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_4EE2&MI_01
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_4EE4&MI_02
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_4EE6&MI_01
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_4EE7

;Google Glass
%SingleAdbInterface%        = USB_Install, USB\VID_18D1&PID_9001
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_9001&MI_01

;Project Tango (generic)
%SingleBootLoaderInterface% = USB_Install, USB\VID_18D1&PID_4D00
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_4D02&MI_01
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_4D04&MI_02
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_4D06&MI_01
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_4D07

;
; MY DEVICES HARDWARE IDS / X64 / START
;

;Nexus 4
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_4EE2&REV_0228&MI_01
%CompositeAdbInterface%     = USB_Install, USB\VID_18D1&PID_4EE2&MI_01

;Motorola Moto G
%CompositeAdbInterface%     = USB_Install, USB\VID_22B8&PID_2E76&REV_0228&MI_02
%CompositeAdbInterface%     = USB_Install, USB\VID_22B8&PID_2E76&MI_02
;Motorola Networking Interface
%CompositeAdbInterface%     = USB_Install, USB\VID_22B8&PID_2E82&REV_0228&MI_01
%CompositeAdbInterface%     = USB_Install, USB\VID_22B8&PID_2E82&MI_01

;i.onik TP9.7-1500DC Retina
%CompositeAdbInterface%     = USB_Install, USB\VID_2207&PID_0006&REV_0222
%CompositeAdbInterface%     = USB_Install, USB\VID_2207&PID_0006

;Sony Xperia M Dual C2005
%CompositeAdbInterface%     = USB_Install, USB\VID_0FCE&PID_519B&REV_0228&MI_01
%CompositeAdbInterface%     = USB_Install, USB\VID_0FCE&PID_519B&MI_01

;Lenovo IdeaTab S6000-H
%CompositeAdbInterface%     = USB_Install, USB\VID_17EF&PID_75E2&REV_0255&MI_01
%CompositeAdbInterface%     = USB_Install, USB\VID_17EF&PID_75E2&MI_01

;Samsung Galaxy Note Edge
;SAMSUNG_Android
%CompositeAdbInterface%     = USB_Install, USB\VID_04E8&PID_6860&REV_0400&MI_03
%CompositeAdbInterface%     = USB_Install, USB\VID_04E8&PID_6860&MI_03
;CDC Serial
%CompositeAdbInterface%     = USB_Install, USB\VID_04E8&PID_6860&REV_0400&MI_01
%CompositeAdbInterface%     = USB_Install, USB\VID_04E8&PID_6860&MI_01

;Samsung Galaxy S4 GT-I9500
%CompositeAdbInterface%     = USB_Install, USB\VID_04E8&PID_6860&REV_0400&ADB
%CompositeAdbInterface%     = USB_Install, USB\VID_04E8&PID_6860&ADB
%CompositeAdbInterface%     = USB_Install, USB\SAMSUNG_MOBILE&ADB
%CompositeAdbInterface%     = USB_Install, USB\SAMSUNG_MOBILE&MI_03
%CompositeAdbInterface%     = USB_Install, USB\Vid_04E8&Pid_6860&MI_03
%CompositeAdbInterface%     = USB_Install, USB\Vid_04E8&Pid_6860&Class_FF&SubClass_42&Prot_01
%CompositeAdbInterface%     = USB_Install, USB\SAMSUNG_MOBILE&Class_FF&SubClass_42&Prot_01

;Samsung Galaxy S4-mini GT-I9190
%CompositeAdbInterface%     = USB_Install, USB\VID_04E8&PID_6860&REV_0400&ADB
%CompositeAdbInterface%     = USB_Install, USB\VID_04E8&PID_6860&ADB
%CompositeAdbInterface%     = USB_Install, USB\SAMSUNG_MOBILE&ADB
%CompositeAdbInterface%     = USB_Install, USB\SAMSUNG_MOBILE&MI_01
%CompositeAdbInterface%     = USB_Install, USB\Vid_04E8&Pid_6860&MI_01
%CompositeAdbInterface%     = USB_Install, USB\Vid_04E8&Pid_6860&Class_FF&SubClass_42&Prot_01
%CompositeAdbInterface%     = USB_Install, USB\SAMSUNG_MOBILE&Class_FF&SubClass_42&Prot_01

;HUAWEI G610-U20
%CompositeAdbInterface%     = USB_Install, USB\VID_12D1&PID_1038&REV_0255&MI_01
%CompositeAdbInterface%     = USB_Install, USB\VID_12D1&PID_1038&MI_01

;HUAWEI U8950-1
%CompositeAdbInterface%     = USB_Install, USB\VID_12D1&PID_1038&REV_0231&MI_01
%CompositeAdbInterface%     = USB_Install, USB\VID_12D1&PID_1038&MI_01

;Samsung Note 10.1 SM-P6012
%CompositeAdbInterface%     = USB_Install, USB\VID_04E8&PID_6860&REV_0400&ADB
%CompositeAdbInterface%     = USB_Install, USB\VID_04E8&PID_6860&ADB
%CompositeAdbInterface%     = USB_Install, USB\SAMSUNG_MOBILE&ADB
%CompositeAdbInterface%     = USB_Install, USB\SAMSUNG_MOBILE&MI_03
%CompositeAdbInterface%     = USB_Install, USB\Vid_04E8&Pid_6860&MI_03
%CompositeAdbInterface%     = USB_Install, USB\Vid_04E8&Pid_6860&Class_FF&SubClass_42&Prot_01
%CompositeAdbInterface%     = USB_Install, USB\SAMSUNG_MOBILE&Class_FF&SubClass_42&Prot_01

;HTC Desire 616 dual sim Android Phone
%CompositeAdbInterface%     = USB_Install, USB\VID_0BB4&PID_0EDD&REV_0216&MI_01
%CompositeAdbInterface%     = USB_Install, USB\VID_0BB4&PID_0EDD&MI_01

;
; MY DEVICES HARDWARE IDS / X64 / END
;


[USB_Install]
Include = winusb.inf
Needs   = WINUSB.NT

[USB_Install.Services]
Include     = winusb.inf
AddService  = WinUSB,0x00000002,WinUSB_ServiceInstall

[WinUSB_ServiceInstall]
DisplayName     = %WinUSB_SvcDesc%
ServiceType     = 1
StartType       = 3
ErrorControl    = 1
ServiceBinary   = %12%\WinUSB.sys

[USB_Install.Wdf]
KmdfService = WINUSB, WinUSB_Install

[WinUSB_Install]
KmdfLibraryVersion  = 1.9

[USB_Install.HW]
AddReg  = Dev_AddReg

[Dev_AddReg]
HKR,,DeviceInterfaceGUIDs,0x10000,"{F72FE0D4-CBCB-407d-8814-9ED673D0DD6B}"

[USB_Install.CoInstallers]
AddReg    = CoInstallers_AddReg
CopyFiles = CoInstallers_CopyFiles

[CoInstallers_AddReg]
HKR,,CoInstallers32,0x00010000,"WdfCoInstaller01009.dll,WdfCoInstaller","WinUSBCoInstaller2.dll"

[CoInstallers_CopyFiles]
WinUSBCoInstaller2.dll
WdfCoInstaller01009.dll

[DestinationDirs]
CoInstallers_CopyFiles=11

[SourceDisksNames]
1 = %DISK_NAME%,,,\i386
2 = %DISK_NAME%,,,\amd64

[SourceDisksFiles.x86]
WinUSBCoInstaller2.dll  = 1
WdfCoInstaller01009.dll = 1

[SourceDisksFiles.amd64]
WinUSBCoInstaller2.dll  = 2
WdfCoInstaller01009.dll = 2

[Strings]
ProviderName                = "Google, Inc."
SingleAdbInterface          = "Android ADB Interface"
CompositeAdbInterface       = "Android Composite ADB Interface"
SingleBootLoaderInterface   = "Android Bootloader Interface"
WinUSB_SvcDesc              = "Android USB Driver"
DISK_NAME                   = "Android WinUsb installation disk"
ClassName                   = "Android Device"
{{< /codeblock >}}

_6_. Now we are good to go. With _Settings > Developer Options > Android Debugging_ checked and your device still connected, go back to your _Control Panel > Device Manager_ on your PC and right click on your Android device name with the yellow exclamation mark, then choose _Update Driver Software..._ and follow the on-screen instructions. It will ask for your driver's location and you must provide it with the modified driver's directory. If you've done everything right, Windows should be able to detect the device and warn you with the following window (Figure 5.):

{{< figure src="/blog/android-install-adb-drivers-for-any-device-without-oem-drivers/windows-security-warning.png" alt="Figure 5. Windows Security: Windows can't verify the publisher of this driver software" caption="Figure 5. Windows Security: Windows can't verify the publisher of this driver software" >}}

_7_. This happens because by comparing the hash of the file, Windows knows that the file has changed. And since these changes are not from Google, for security reasons, it warns the user. We know we changed that file, right? So, proceed with the installation by hitting the _Install this driver software anyway_ button. Note on Windows 8, 8.1 and probably 10, due to stricter security policies you won't be able to install the modified driver, even though you have chose _Install this driver software anyway_ option. We will come to that later, and I'll show you a way to bypass that too.

_8_. Once more check _Control Panel > Device Manager_ to see if the driver installation was successful (Figure 6.).

{{< figure src="/blog/android-install-adb-drivers-for-any-device-without-oem-drivers/device-manager-recognized-adb-device.png" alt="Figure 6. Device Manager: Successfully recognized ADB driver" caption="Figure 6. Device Manager: Successfully recognized ADB driver" >}}

_9_. The last step is to verify whether ADB recognizes the Android device or not, using <code>adb devices</code> command (Figure 7.):

{{< figure src="/blog/android-install-adb-drivers-for-any-device-without-oem-drivers/adb-recognized-device-cmd.png" alt="Figure 7. Recognized device by ADB inside the command line" caption="Figure 7. Recognized device by ADB inside the command line" >}}

__Windows 8 / 8.1 / 10 instructions__: OK, if you are on Windows 8 or newer versions of Windows, disable _Driver Signature Enforcement_ before installing the modified driver by following these steps (note that it requires a reboot on your PC):

Step 1: Press <code>WIN_KEY+C</code> to open the Charm menu or by moving your mouse courser to the lower right edge of the screen and then click the gear icon also known as _Settings_:

{{< figure src="/blog/android-install-adb-drivers-for-any-device-without-oem-drivers/windows-disable-driver-signature-enforcement-01.png" alt="Figure 8. Disabling driver signature enforcement on Microsoft Windows - step 1" caption="Figure 8. Disabling driver signature enforcement on Microsoft Windows - step 1" >}}

Step 2: Select _Change PC Settings_:

{{< figure src="/blog/android-install-adb-drivers-for-any-device-without-oem-drivers/windows-disable-driver-signature-enforcement-02.png" alt="Figure 9. Disabling driver signature enforcement on Microsoft Windows - step 2" caption="Figure 9. Disabling driver signature enforcement on Microsoft Windows - step 2" >}}

Step 3: Select _Update and Recovery_:

{{< figure src="/blog/android-install-adb-drivers-for-any-device-without-oem-drivers/windows-disable-driver-signature-enforcement-03.png" alt="Figure 10. Disabling driver signature enforcement on Microsoft Windows - step 3" caption="Figure 10. Disabling driver signature enforcement on Microsoft Windows - step 3" >}}

Step 4: Select _Recovery_, then _Restart now_ in the _Advanced startup_ section:

{{< figure src="/blog/android-install-adb-drivers-for-any-device-without-oem-drivers/windows-disable-driver-signature-enforcement-04.png" alt="Figure 11. Disabling driver signature enforcement on Microsoft Windows - step 4" caption="Figure 11. Disabling driver signature enforcement on Microsoft Windows - step 4" >}}

Step 5: Click on _Troubleshoot_ button:

{{< figure src="/blog/android-install-adb-drivers-for-any-device-without-oem-drivers/windows-disable-driver-signature-enforcement-05.png" alt="Figure 12. Disabling driver signature enforcement on Microsoft Windows - step 5" caption="Figure 12. Disabling driver signature enforcement on Microsoft Windows - step 5" >}}

Step 6: Click on _Advanced options_ button:

{{< figure src="/blog/android-install-adb-drivers-for-any-device-without-oem-drivers/windows-disable-driver-signature-enforcement-06.png" alt="Figure 13. Disabling driver signature enforcement on Microsoft Windows - step 6" caption="Figure 13. Disabling driver signature enforcement on Microsoft Windows - step 6" >}}

Step 7: Click on _Startup Settings_ button:

{{< figure src="/blog/android-install-adb-drivers-for-any-device-without-oem-drivers/windows-disable-driver-signature-enforcement-07.png" alt="Figure 14. Disabling driver signature enforcement on Microsoft Windows - step 7" caption="Figure 14. Disabling driver signature enforcement on Microsoft Windows - step 7" >}}

Step 8: Click on _Restart_ button to reboot your PC:

{{< figure src="/blog/android-install-adb-drivers-for-any-device-without-oem-drivers/windows-disable-driver-signature-enforcement-08.png" alt="Figure 15. Disabling driver signature enforcement on Microsoft Windows - step 8" caption="Figure 15. Disabling driver signature enforcement on Microsoft Windows - step 8" >}}

Step 9: After rebooting your PC you will see the following screen. Press <code>F7</code> on your keyboard to boot with _Driver Signature Enforcement_ feature disabled:

{{< figure src="/blog/android-install-adb-drivers-for-any-device-without-oem-drivers/windows-disable-driver-signature-enforcement-09.png" alt="Figure 16. Disabling driver signature enforcement on Microsoft Windows - step 9" caption="Figure 16. Disabling driver signature enforcement on Microsoft Windows - step 9" >}}

Step 10: Go to _Control Panel > Device Manager_ and proceed to the driver installation as described in the main driver installation process, steps __6__ to __9__ (where you'll get the Windows Security warning, Figure 5.). Please note that after rebooting your PC, _Driver Signature Enforcement_ will be enabled again. So, you don't have to enable it manually.

