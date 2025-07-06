+++
title = "Unreal Engine 5.6 Android Packaging & APK Build Tutorial | Meta Quest & HTC VIVE Standalone"
slug = "unreal-engine-android-packaging-apk-build-tutorial-meta-quest-htc-vive-standalone"
date = 2025-07-06T18:20:00+02:00
tags = [ "ADB", "Android", "Blueprint", "Epic Games", "Game Development", "Game Programming", "gamedev", "Hand-tracking", "HTC VIVE", "HTC VIVE Focus 3", "HTC VIVE Focus Vision", "HTC VIVE OpenXR Plugin", "HTC VIVE XR Elite", "Java", "JDK", "Meta Quest", "Meta Quest 2", "Meta Quest Pro", "Meta Quest 3", "Meta Quest 3S", "Meta XR Plugin", "Oculus", "Oculus Quest", "Oculus XR", "OpenXR", "PCVR", "Standalone", "UDK", "UE4", "UE5", "Unreal Engine", "UnrealScript", "Virtual Reality", "VR", "Windows", "XR", "XR_EXT_hand_tracking" ]
toc = "true"
draft = "true"
+++

{{< figure src="/blog/unreal-engine-android-packaging-apk-build-tutorial-meta-quest-htc-vive-standalone/unreal-engine-android-packaging-apk-build-tutorial-meta-quest-htc-vive-standalone.webp" alt="Unreal Engine 5.6 Android Packaging & APK Build Tutorial | Meta Quest & HTC VIVE Standalone" caption="Unreal Engine 5.6 Android Packaging & APK Build Tutorial | Meta Quest & HTC VIVE Standalone" >}}

Let's cut the noise. You want quick, clean, and painless Unreal Engine APK builds and packaging? You're in the right place.

A while back, I released two videos: one on [deploying Unreal Engine projects to Android and Meta Quest](/blog/deploy-unreal-engine-projects-android-meta-quest-standalone-mode/), and another on [enabling proper hand-tracking using the Meta XR Plugin and HTC VIVE OpenXR plugins](/blog/unreal-engine-openxr-hand-tracking-android-meta-xr-htc-vive/). I also tackled a frustrating issue on HTC VIVE devices, where APKs were launching as 2D apps instead of immersive VR experiences.

That first video blew up; it became one of my best-performing uploads to this date, with tons of positive feedback. But one thing stood out in the comments: Unreal developers everywhere are struggling to set up the Android development environment and package APKs correctly.

So, back by demand, and with something even better, welcome to the Ultimate Guide for deploying Unreal Engine projects to Android standalone-mode.

This video combines everything from the previous tutorials; refined, updated, and streamlined. And to make things even easier, I've just open-sourced a brand-new one-click installer that sets up your entire Android development environment for Unreal Engine automagically. It downloads, installs, and configures Android Studio, SDK, NDK, and JDK, so you don't have to lift even a finger.

Whether you're building for Meta Quest or HTC VIVE, this guide takes you from zero to packaged APK, with full VR support, working hand-tracking, and seamless integration of both Meta XR and HTC VIVE OpenXR plugins.

Let's dive in.

<!--more-->

## The Video Tutorial

{{< youtube  >}}

## Unreal Engine Android Development Environment One-Click Installer

Get the installer's source code on:

- [GitHub](https://github.com/NuLL3rr0r/unreal-android-installer)
- [GitLab](https://gitlab.com/NuLL3rr0r/unreal-android-installer)

## Microsot Visual Studio Installer Configuration File

This is the [Microsot Visual Studio Installer configuration file](visual-studio-2022.vsconfig) that automatically selects and installs all the required components needed by various versions of Unreal Engine including `5.6`.

## Plugins

- [Meta XR Unreal Engine 5 Integration Plugin](https://developers.meta.com/horizon/downloads/package/unreal-engine-5-integration/).
- [HTC VIVE OpenXR Unreal Engine Plugin](https://developer.vive.com/resources/openxr/unreal/unreal-download/latest/).

## Manual Android Development Environment Setup

Prefer to set things up manually instead of using the one-click installer provided in this tutorial? No problem.

You can [follow the detailed steps from the previous tutorial](/blog/deploy-unreal-engine-projects-android-meta-quest-standalone-mode/), which walks through the entire process. The key sections to focus on are:

- [00:08:03 - 00:25:53 Prerequisites (Android Studio)](https://www.youtube.com/watch?v=EClbEbNcl4k&t=483s)
- [00:25:54 - 00:27:13 Prerequisites (JDK)](https://www.youtube.com/watch?v=EClbEbNcl4k&t=1554s)
- [00:27:14 - 00:32:47 Prerequisites (SetupAndroid.bat)](https://www.youtube.com/watch?v=EClbEbNcl4k&t=1634s)

## Android Project Settings

### UE 5.6 Android Project Settings

#### UE 5.6 SetupAndroid.bat

{{< codeblock lang="cmd" title="Engine/Extras/Android/SetupAndroid.bat" >}}
rem hardcoded versions for compatibility with non-Turnkey manual running
if "%PLATFORMS_VERSION%" == "" SET PLATFORMS_VERSION=android-34
if "%BUILDTOOLS_VERSION%" == "" SET BUILDTOOLS_VERSION=34.0.0
if "%CMAKE_VERSION%" == "" SET CMAKE_VERSION=3.22.1
if "%NDK_VERSION%" == "" SET NDK_VERSION=25.1.8937393
{{< /codeblock >}}

<br />

#### UE 5.6 Android Development Requirements

{{< blockquote author="Epic Developer Community - UE 5.6 Android Development Requirements - Current SDK Information" link="https://dev.epicgames.com/documentation/en-us/unreal-engine/android-development-requirements-for-unreal-engine?application_version=5.6" >}}
```
⚠️ Since August 31, 2024, Google Play Store requires apps to target Android 14, which requires API level 34. To publish new apps on the Google Play Store, you must update to UE 5.4.4 or newer for target SDK 34 support. Apps built with previous versions of UE will no longer submit successfully. 

For more information, see the Android documentation on Google Play's target API level requirement.
```

- Current UE Version: 5.6
- Android Studio Version: Koala 2024.1.2 August 29, 2024
- Android SDK:
  - Recommended: SDK 34
  - Minimum for compilation: SDK 34
  - Default target SDK for shipping on devices: 34
  - Minimum install SDK level: 26
```
ℹ️ Different stores have their own target SDK minimum requirements, which may differ from that mentioned above.
```
- NDK Version:  r25b
- Build-tools: 34.0.0
- Java runtime: OpenJDK 21.0.3 2024-04-16
- AGDE v23.2.91+ required for AGDE debugging. 
{{< /blockquote >}}

### UE 5.5 Android Project Settings

#### UE 5.5 SetupAndroid.bat

{{< codeblock lang="cmd" title="Engine/Extras/Android/SetupAndroid.bat" >}}
rem hardcoded versions for compatibility with non-Turnkey manual running
if "%PLATFORMS_VERSION%" == "" SET PLATFORMS_VERSION=android-34
if "%BUILDTOOLS_VERSION%" == "" SET BUILDTOOLS_VERSION=34.0.0
if "%CMAKE_VERSION%" == "" SET CMAKE_VERSION=3.22.1
if "%NDK_VERSION%" == "" SET NDK_VERSION=25.1.8937393
{{< /codeblock >}}

<br />

#### UE 5.5 Android Development Requirements

{{< blockquote author="Epic Developer Community - UE 5.5 Android Development Requirements - Current SDK Information" link="https://dev.epicgames.com/documentation/en-us/unreal-engine/android-development-requirements-for-unreal-engine?application_version=5.5" >}}
```
⚠️ After August 31, 2024, Google Play Store requires apps to target Android 14, which requires API level 34. To publish new apps on the Google Play Store after this date, you must update to UE 5.4.4 or newer for target SDK 34 support. Apps built with previous versions of UE will no longer submit successfully. For more information, see the Android documentation on Google Play's target API level requirement.
```

- Current UE Version: 5.5
- Android Studio Version: Koala 2024.1.2 August 29, 2024
- Android SDK:
  - Recommended: SDK 34
  - Minimum for compilation: SDK 34
  - Default target SDK for shipping on devices: 34
  - Minimum install SDK level: 26
```
Different stores have their own target SDK minimum requirements, which may differ from that mentioned above.
```
- NDK Version: r25b
- Build-tools: 34.0.0
- Java runtime: OpenJDK 17.0.6 2023-01-17
- AGDE v23.1.82+ required for AGDE debugging.
{{< /blockquote >}}

### UE 5.4 Android Project Settings

#### UE 5.4 SetupAndroid.bat

{{< codeblock lang="cmd" title="Engine/Extras/Android/SetupAndroid.bat" >}}
rem hardcoded versions for compatibility with non-Turnkey manual running
if "%PLATFORMS_VERSION%" == "" SET PLATFORMS_VERSION=android-33
if "%BUILDTOOLS_VERSION%" == "" SET BUILDTOOLS_VERSION=33.0.1
if "%CMAKE_VERSION%" == "" SET CMAKE_VERSION=3.22.1
if "%NDK_VERSION%" == "" SET NDK_VERSION=25.1.8937393
{{< /codeblock >}}

<br />

#### UE 5.4 Android Development Requirements

{{< blockquote author="Epic Developer Community - UE 5.4 Android Development Requirements - Current SDK Information" link="https://dev.epicgames.com/documentation/en-us/unreal-engine/android-development-requirements-for-unreal-engine?application_version=5.4" >}}
```
⚠️ After August 31, 2024, Google Play Store requires apps to target Android 14, which requires API level 34. To publish new apps on the Google Play Store after this date, you must update to UE 5.4.4 for target SDK 34 support. Apps built with previous versions of UE will no longer submit successfully. For more information, see the Android documentation on Google Play's target API level requirement.
```

- Current UE Version: 5.4.4
- Android Studio Version: Flamingo 2022.2.1 Patch 2 May 24, 2023
- Android SDK:
  - Recommended: SDK 34
  - Minimum for compilation: SDK 34
  - Minimum SDK for shipping on devices: 26
```
Different stores have their own target SDK minimum requirements, which may differ from that mentioned above.
```
- NDK Version: r25b
- Build-tools: 34.0.0
- Java runtime: OpenJDK 17.0.6 2023-01-17
- AGDE v23.1.82+ required for AGDE debugging.
{{< /blockquote >}}
