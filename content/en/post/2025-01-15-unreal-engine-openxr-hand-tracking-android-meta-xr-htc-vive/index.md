+++
title = "Unreal Engine OpenXR Hand-Tracking on Android with Meta XR (Quest 3S/3/Pro/2) and HTC VIVE OpenXR (Focus Vision/XR Elite/Focus 3) Plugins"
slug = "unreal-engine-openxr-hand-tracking-android-meta-xr-htc-vive"
date = 2025-01-15T12:12:00+01:00
tags = [ "Android", "Epic Games", "Game Development", "Game Programming", "gamedev", "HTC VIVE", "Meta Quest", "Oculus", "Oculus Quest", "OpenXR", "PCVR", "UDK", "UE4", "UE5", "Unreal Engine", "UnrealScript", "Virtual Reality", "VR", "Windows", "XR" ]
toc = true
draft = true
+++

{{< figure src="/blog/unreal-engine-openxr-hand-tracking-android-meta-xr-htc-vive/unreal-engine-openxr-hand-tracking-android-meta-xr-htc-vive.webp" alt="Unreal Engine OpenXR Hand-Tracking on Android with Meta XR (Quest 3S/3/2) and HTC VIVE OpenXR (Focus Vision/XR Elite/Focus 3) Plugins" caption="Unreal Engine OpenXR Hand-Tracking on Android with Meta XR (Quest 3S/3/2) and HTC VIVE OpenXR (Focus Vision/XR Elite/Focus 3) Plugins" >}}

Hey everyone! Welcome back to the channel! In the last tutorial, we tackled deploying Unreal Engine projects to Android and Meta Quest in standalone mode—because who doesn’t love the thrill of watching their code actually work on a headset? But if you caught that episode, you’ll remember I dropped a little plot twist: Unreal Engine’s built-in OpenXR plugin... yeah, it’s like that friend who shows up at your party and forgets to bring their own hand-tracking support for Android. Awkward, right?

Well, today, we’re fixing that. We’re making sure the hand-tracking projects we developed together earlier in this series, have non-broken, fully functional hand-tracking and play nice on your Meta Quest and HTC Vive HMDs in standalone mode. Whether you’re team Meta or team HTC, I’ve got you covered.

Let’s jump right in and get the hand-tracking working exactly the way it’s supposed to!

<!--more-->

## Video Tutorial

{{< youtube BWd3MwtfTJE >}}

<br/>

# Plugins

- Get [Meta XR Unreal Engine 5 Integration Plugin](https://developers.meta.com/horizon/downloads/package/unreal-engine-5-integration/).
- Get [HTC VIVE OpenXR Unreal Engine Plugin](https://developer.vive.com/resources/openxr/unreal/unreal-download/latest/).

## Patched Meta XR Unreal Engine 5 Integration v71.0 for UE 5.5

- Get it on [Microsoft Azure DevOps](https://dev.azure.com/NuLL3rr0r/_git/meta-xr-unreal-engine-integration-patched).
- Get it on [GitLab](https://gitlab.com/NuLL3rr0r/meta-xr-unreal-engine-integration-patched).
