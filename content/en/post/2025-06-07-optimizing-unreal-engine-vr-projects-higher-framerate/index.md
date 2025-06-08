+++
title = "Optimizing Unreal Engine VR Projects for Higher Framerates (Meta Quest, HTC VIVE, FFR, ETFR, NVIDIA DLSS, AMD FSR, and Intel XeSS Tips Included!)"
slug = "optimizing-unreal-engine-vr-projects-higher-framerate"
date = 2025-06-07T07:08:00+02:00
tags = [ "AMD", "Android", "Blueprint", "DLSS", "Epic Games", "ETFR", "Frame Generation", "FFR", "FSR", "Game Development", "Game Programming", "gamedev", "HTC VIVE", "Intel", "Meta Quest", "NVIDIA", "Oculus", "Oculus Quest", "OpenXR", "Optimization", "PCVR", "UDK", "UE4", "UE5", "Unreal Engine", "UnrealScript", "Upscaling", "Virtual Reality", "VR", "Windows", "XeSS", "XR" ]
toc = true
draft = true
+++

{{< figure src="/blog/optimizing-unreal-engine-vr-projects-higher-framerate/optimizing-unreal-engine-vr-projects-higher-framerate.webp" alt="Optimizing Unreal Engine VR Projects for Higher Framerates (Meta Quest, HTC VIVE, FFR, ETFR, NVIDIA DLSS, AMD FSR, and Intel XeSS Tips Included!)" caption="Optimizing Unreal Engine VR Projects for Higher Framerates (Meta Quest, HTC VIVE, FFR, ETFR, NVIDIA DLSS, AMD FSR, and Intel XeSS Tips Included!)" >}}

Ever felt like your VR project is running so slow it could be a snail's day job? 🐌 Or maybe your framerate is auditioning for a role in The Matrix—dodging bullets, but also every performance standard? 😅

Well, today, we're fixing that! I’ll show you how to take your Unreal Engine VR game from ‘meh’ to chef’s kiss smooth. Although enhancing the performance and framerate of Unreal Engine VR applications, whether running in standalone mode (Android mobile) or PCVR mode (PC streaming), can feel daunting, especially when dealing with varying project requirements, this guide breaks down practical and easy-to-implement strategies that deliver noticeable results with minimal hassle, helping you achieve smoother gameplay.

So, let’s get started before that snail finishes its coffee break!

<!--more-->

## English Video Tutorials

- The video tutorial:

<br/>

## Proof: Optimized VR Project with 120+ FPS on Cinematic Quality Level

{{< twitter mamadou_gamedev 1809991716843434228 >}}

### Enhanced Visuals and Boosted Performance Utilizing NVIDIA DLSS

{{< youtube VDKGxixvQU0 >}}

## Converting Non-VR Projects to Immersive VR

To convert a non-VR project into an immersive VR experience, the first step is to enable the `Start in VR` option in your project settings:

![Project Settings - Description - Start in VR](project-description-start-in-vr.webp "Project Settings - Description - Start in VR")

## PCVR Mode

Here are some crucial guidelines that you might consider adjusting to optimize performance in PCVR mode.

### Enhancing Meta Quest Link Graphics Settings

The default refresh rate is set at `72 Hz` when streaming from a PC to Meta Quest devices. However, you can increase this up to `120 Hz`, which enhances the refresh rate and reduces the rendering resolution, potentially improving performance. Follow these steps to adjust refresh rate:

1. Open the **Meta Quest Link** app and go to the `Devices` tab.

![Meta Quest Link - Devices](meta-quest-link-devices.webp "Meta Quest Link - Devices")

2. Select the device you want to adjust the refresh rate for.

![Meta Quest Link - Selected device](meta-quest-link-device-selected.webp "Meta Quest Link - Selected device")

3. In the device settings, navigate to the `Advanced` section and click on `Graphics Preferences`.

![Meta Quest Link - Device advanced graphics preferences](meta-quest-link-device-advanced-graphics-preferences.webp "Meta Quest Link - Device advanced graphics preferences")

4. Select your preferred refresh rate, such as `120 Hz`. Once selected, click `OK` to confirm, and the Meta Quest Link app will automatically restart to apply the changes.

![Meta Quest Link - Setting the device refresh rate](meta-quest-link-device-advanced-graphics-preferences-refresh-rate.webp "Meta Quest Link - Setting the device refresh rate")

5. After the Meta Quest Link app restarts, revisit the `Devices` tab, select your device, and verify the refresh rate setting in `Advanced > Graphics Preferences`.

![Meta Quest Link - 120 Hz refresh rate](meta-quest-link-device-advanced-graphics-preferences-refresh-rate-120hz.webp "Meta Quest Link - 120 Hz refresh rate")

6. Next, open your Unreal Engine project and go to `Project Settings` to fine-tune your project’s framerate. Under `Engine > General Settings > Framerate`, adjust and experiment with the framerate settings to suit your project's specific needs.

![Meta Quest Link - Framerate settings for the Unreal project](project-rendering-settings-framerate.webp "Meta Quest Link - Framerate settings for the Unreal project")

## Standalone Mode (Mobile)

Optimizing performance for mobile platforms requires careful attention to specific settings. Here are some essential adjustments to maximize performance and efficiency for mobile devices.

The good news is that Unreal Engine 5 has continued to evolve rapidly in terms of mobile rendering, VR support, and performance optimization, with each minor release bringing noticable performance improvements, especially in the two latest releases, `5.5` and `5.6`, which you'll benefit from for free.

![Unreal Engine 5 - Mobile Rendering](unreal-engine-mobile-rendering.gif "Unreal Engine 5 - Mobile Rendering")

<br />

{{< blockquote author="Unreal Engine 5.5 Release Notes - Mobile Renderer" link="https://dev.epicgames.com/documentation/en-us/unreal-engine/unreal-engine-5.5-release-notes#mobilerenderer" >}}
**Mobile Renderer**

Unreal Engine 5.5 brings several new features to the mobile renderer:

- Forward mode now supports d-buffer decals, rect lights, capsule shadows and point light shadows
- Runtime automatic PSO precaching, which offers an alternative to the manual PSO gathering workflow
- Screen-space Reflections
{{< /blockquote >}}

{{< blockquote author="Unreal Engine 5.5 Release Notes - Mobile Forward and Desktop Forward feature parity" link="https://dev.epicgames.com/documentation/en-us/unreal-engine/unreal-engine-5.5-release-notes#mobileforwardanddesktopforwardfeatureparity" >}}
**Mobile Forward and Desktop Forward feature parity**

The Mobile Forward renderer is receiving feature updates and performance improvements with the objective of becoming the recommended renderer for PC VR once it reaches feature parity with the legacy Desktop Forward Renderer. In 5.5 we implemented support for the following features:

- Moveable Point/Spot-light IES Textures
- Capsule Direct Shadows
- Decals
- Rectangular Lights
- Volumetric Fog
- Niagara Particle Lights
- Moveable Point Light Shadows (only supported with d3d and not Vulkan)
{{< /blockquote >}}

{{< blockquote author="Unreal Engine 5.5 Release Notes - Mobile Rendering" link="https://dev.epicgames.com/documentation/en-us/unreal-engine/unreal-engine-5.5-release-notes#mobilerendering" >}}
**Mobile Rendering**

**Bug Fix**:

- Correctly change between Mobile Forward and Mobile Deferred, taking into account r.Mobile.AllowDeferredShadingOpenGL cvar
{{< /blockquote >}}

{{< blockquote author="Unreal Engine 5.5 Release Notes - Mobile Forward" link="https://dev.epicgames.com/documentation/en-us/unreal-engine/unreal-engine-5.5-release-notes#mobileforward" >}}
**Mobile Forward**

**New**:

- Added IES Textures in Mobile Forward Renderer
- Added movable point lights dynamic shadows in mobile forward renderer. Requires r.Mobile.EnableMovablePointLightsShadows=1 and r.Mobile.SupportGPUScene=True.
- Added rect light support to mobile forward renderer. Requires r.Mobile.Forward.RenderRectLightsAsSpotLights=0.
- Added capsule direct shadows to mobile forward renderer. Requires r.Mobile.EnableCapsuleShadows=1 and r.Mobile.EnableCapsuleDirectShadows=1.

**Bug Fix**:

- Fix depth prepass disabling MSAA.
{{< /blockquote >}}


{{< blockquote author="Unreal Engine 5.6 Release Notes - Mobile Rendering" link="https://dev.epicgames.com/documentation/en-us/unreal-engine/unreal-engine-5-6-release-notes#mobilerendering" >}}
**Mobile Rendering**

We improved the Mobile Renderer performance and feature set with Unreal Engine 5.6, notably:

- We added support for skylight real time capture.
- GPUScene received optimizations and we added skinned mesh support.
- We added the Experimental Multipass deferred mode (cvar) for Android Vulkan, providing for shadow and screenspace techniques without depth prepass.
- We added the Experimental Distance Field Ambient Occlusion (cvar).
{{< /blockquote >}}

{{< blockquote author="Unreal Engine 5.6 Release Notes - Mobile Rendering" link="https://dev.epicgames.com/documentation/en-us/unreal-engine/unreal-engine-5-6-release-notes#mobilerendering-2" >}}
**Mobile Rendering**

New:

- Add ReplaceTonemapper BlendLocation to the Mobile PostProcess
- Enable LightGrid Debug for Mobile Keep Light Grid Debug disabled for Preview and D3D ES31 because of FXC restriction
- Use R8G8B8_UNORM where supported When r.Mobile.SceneColorFormat=3 use R8G8B8_UNORM if supported and alpha is not needed
- For everyone else use R8G8B8_UNORM in tonemapping if supported and alpha is not needed
- Make ASTC_RGB_HDR on IOS/Android default to ASTC_RGB if ASTC HDR is not supported instead of RGBA16F
- Mobile/Desktop PostFX parity. PostProcessMaterialAfterTonemapping after FXAA. Drive-by cleanup of unused bLastPass.
- Add Bloom to ReplaceTonemapper Mobile
- Allow some ISceneViewExtension postprocess delegates to extend mobile postprocessing
- Mobile DFAO implementation Mobile Deferred MultiPass has its own DFAO generation renderpass, samples the DFAO texture and composites it with other AO like SSAO Mobile Forward and Deferred Single Pass will modulate the DFAO result into the SSAO texture and sample it.

Bug Fix:

- Don't apply AerialPerspective to Translucent Materials on Mobile when r.Mobile.PixelFogQuality is 0
- Force FullPrecision for Mobile DOF shaders
- Skip the last transition for memory less texture.
- Wrong type used in Velocity pass shaders on Opengl Windows
- Fix hair (voxel) shadow causing incorrect shadow causing incorrect light transmission from thin diffuse surface.
- Fix metallic properties not making it into the shader path for mobile materials. The conditions around IsNonmetal are invalid as they only consider input connections but not constant scalar values. In either case, the constant value could be modified at runtime. Moreover, the optimization from this path was limited to a lerp and a multiplication operation.
- Fixed strange stripes on the screen when using gtao on mobile.
- Resolve thread timing issue that was causing invalid Scene texture config. Move TaskDatas.VisibilityTaskData->Finish(); to precede IsMobileSeparateTranslucencyActive calls as it depends on results from TaskDatas.VisibilityTaskData, namely SetupMeshPasses and the collection of DynamicMeshRelevance data.
- Fixed shader compilation for SM5 on tvOS

Deprecated:

- Remove the mobile PixelProjectReflection because we have the mobile SSR.

**Mobile Lighting**

New:

- Added a Map Check warning when static lights are present in the scene but disabled due to Lumen.

Bug Fix:

- Fix OIT crash on platform not supporting R16uint format for UAV write.

**Mobile Materials**

New:

- Disable normal output for GBuffer decals on mobile deferred.
{{< /blockquote >}}

{{< blockquote author="Unreal Engine 5.6 Release Notes - Mobile Rendering" link="https://dev.epicgames.com/documentation/en-us/unreal-engine/unreal-engine-5-6-release-notes#mobilerendering-3" >}}
**Mobile Rendering**

**Mobile Materials**

API Change:

1. Mobile deferred uses octahedral encoding for normals which can't blend.
{{< /blockquote >}}

### Generic Rendering Settings

**Forward Shading**: Enable Forward Shading for improved efficiency. It’s optimized for mobile platforms.

![Standalone Mode (Mobile) - Rendering Settings - Forward Shading](project-rendering-settings-forward-renderer-shading.webp "Standalone Mode (Mobile) - Rendering Settings - Forward Shading")

![Standalone Mode (Mobile) - Rendering Settings - Mobile Shading](project-rendering-settings-mobile-shading.webp "Standalone Mode (Mobile) - Rendering Settings - Mobile Shading")

**Mobile HDR**: Disable this option to conserve resources. HDR can have a significant performance impact, especially on lower-end devices.

![Standalone Mode (Mobile) - Rendering Settings - VR](project-rendering-settings-vr-mobile-hdr.webp "Standalone Mode (Mobile) - Rendering Settings - VR")

**Instanced Stereo**: Activate this setting to streamline rendering by reducing the workload for VR applications, where two slightly different images are needed for each eye.

![Standalone Mode (Mobile) - Rendering Settings - Instanced Stereo](project-rendering-settings-vr-instanced-stereo.webp "Standalone Mode (Mobile) - Rendering Settings - Instanced Stereo")

**Mobile Multi-View**: Enable this feature for optimized VR rendering on mobile devices, especially when using platforms like Google Daydream or Samsung Gear VR.

![Standalone Mode (Mobile) - Rendering Settings - Mobile Multi-View](project-rendering-settings-vr-mobile-multi-view.webp "Standalone Mode (Mobile) - Rendering Settings - Mobile Multi-View")

**Mobile Anti-Aliasing Method**: Choose `FXAA (Fast Approximate Anti-Aliasing)` or `MSAA (Multisample Anti-Aliasing)` for smoother visuals. `MSAA` offers better quality with minimal performance impact.

![Standalone Mode (Mobile) - Rendering Settings - Mobile Anti-Aliasing Method](project-rendering-settings-mobile-anti-aliasing-method.webp "Standalone Mode (Mobile) - Rendering Settings - Mobile Anti-Aliasing Method")

**Reflection Capture Resolution**: Lower the resolution (e.g., `128` or `256`) to save memory.

![Standalone Mode (Mobile) - Rendering Settings - Reflection Capture Resolution](project-rendering-settings-reflections-reflection-capture-resolution.webp "Standalone Mode (Mobile) - Rendering Settings - Reflection Capture Resolution")

### Texture Settings

**Enable Virtual Texture Support**: Turn this setting off for better performance. See the [Virtual Texturing documentation](https://dev.epicgames.com/documentation/en-us/unreal-engine/virtual-texturing-in-unreal-engine) for more details.

![Standalone Mode (Mobile) - Rendering Settings - Enable Virtual Texture Support](project-rendering-settings-virtual-textures-enable-virtual-texture-support.webp "Standalone Mode (Mobile) - Rendering Settings - Enable Virtual Texture Support")

**Texture Streaming**: Enable texture streaming to load textures progressively, reducing memory usage. See the [Texture Streaming documentation](https://dev.epicgames.com/documentation/en-us/unreal-engine/texture-streaming-in-unreal-engine) for more details.

![Standalone Mode (Mobile) - Rendering Settings - Texture Streaming](project-rendering-settings-textures-texture-streaming.webp "Standalone Mode (Mobile) - Rendering Settings - Texture Streaming")

**Texture Quality**: Adjust to `Medium` or `Low`, depending on the capabilities of the target device.

**Texture Compression**: Use `ASTC` compression for Android devices to ensure optimized texture performance.

### Lighting Settings

**Static Lighting**: Use static lighting instead of dynamic lighting to save processing power.

**Lightmap Resolution**: Opt for lower lightmap resolutions (e.g., `32` or `64`) to minimize memory usage.

**Dynamic Shadows**: Disable or reduce dynamic shadows. If necessary, use `Cascaded Shadow Maps (CSM)` with reduced resolution and range.

**Distance Field Shadows/Ambient Occlusion**: Turn these features off as they are resource-intensive.

![Standalone Mode (Mobile) - Rendering Settings - Ambient Occlusion](project-rendering-settings-default-ambient-occlusion.webp "Standalone Mode (Mobile) - Rendering Settings - Ambient Occlusion")

### Post-Processing Settings

**Bloom, Lens Flares, and Auto Exposure**: Minimize or disable these effects to save resources.

![Standalone Mode (Mobile) - Rendering Settings - Bloom](project-rendering-settings-default-bloom.webp "Standalone Mode (Mobile) - Rendering Settings - Bloom")

![Standalone Mode (Mobile) - Rendering Settings - Lens Flares](project-rendering-settings-default-lens-flares.webp "Standalone Mode (Mobile) - Rendering Settings - Lens Flares")

![Standalone Mode (Mobile) - Rendering Settings - Auto Exposure](project-rendering-settings-default-auto-exposure.webp "Standalone Mode (Mobile) - Rendering Settings - Auto Exposure")

**Screen Space Reflections**: Turn this off to reduce performance strain.

**Motion Blur**: Disable to conserve processing power.

![Standalone Mode (Mobile) - Rendering Settings - Motion Blur](project-rendering-settings-default-motion-blur.webp "Standalone Mode (Mobile) - Rendering Settings - Motion Blur")

### Materials and Shaders

**Material Complexity**: Simplify materials by minimizing instructions and limiting textures or shader nodes.

**Specular Highlights**: Reduce or disable to optimize performance.

**LOD (Level of Detail) Models**: Ensure models have LODs configured, reducing polygon count for distant objects.

### Level of Detail (LOD) Settings

**Mesh LODs**: Configure all meshes with appropriate LODs to reduce polygons as objects move further away.

**Screen Size**: Adjust LOD screen size settings to ensure efficient transitions for mobile devices.

### Engine Scalability Settings

**Resolution Scale**: Lower the scale (e.g., `70%` or `80%`) for a balance of quality and performance.

**View Distance**: Set to Medium or Low to reduce detail rendered at long distances.

**Shadows**: Lower or disable shadow quality to improve performance.

**Textures**: Adjust to Medium or Low depending on the device’s capability.

**Effects**: Minimize effects to conserve resources.

_**NOTE**_: In PCVR mode, Unreal Engine typically defaults the Engine Scalability Settings profile to `Epic`. However, when deploying to Standalone mode (Android), it switches to a custom profile. For more details, refer to [Game User Settings and Engine Scalability Settings](#game-user-settings-and-engine-scalability-settings).

### Physics and Collision

**Physics Simulation**: Limit physics calculations where possible to save resources.

**Collision Complexity**: Use simple collision meshes instead of complex ones.

### Audio Settings

**Sample Rate**: Lower the sample rate to reduce memory and processing load.

**Number of Audio Channels**: Restrict the number of channels to optimize CPU usage.

### Rendering API

**Vulkan vs OpenGL ES**: Test both APIs on your target device. Vulkan typically offers better performance but may not be supported universally.

### Culling

Unreal Engine utilizes [several types of culling mechanisms to optimize rendering](https://dev.epicgames.com/documentation/en-us/unreal-engine/visibility-and-occlusion-culling-in-unreal-engine#precomputedvisibility) by avoiding unnecessary calculations for objects that are not visible or relevant. Here’s an overview of the primary culling types and other specialized techniques offered by Unreal Engione to ensure optimal rendering performance based on the order they are applied (the order depends on their cost):

[**Distance Culling**](https://dev.epicgames.com/documentation/en-us/unreal-engine/visibility-and-occlusion-culling-in-unreal-engine#distance): Distance culling methods, such as [Per-Actor Instance](https://dev.epicgames.com/documentation/en-us/unreal-engine/visibility-and-occlusion-culling-in-unreal-engine#per-actorinstance) (individual draw distance settings per Actor) and [Cull Distance Volumes](https://dev.epicgames.com/documentation/en-us/unreal-engine/visibility-and-occlusion-culling-in-unreal-engine#culldistancevolumes) (arrays of sizes and distances for large levels), control whether Actors are rendered based on their distance from the camera, optimizing performance by not rendering Actors that are too far away.

[**View Frustum Culling**](https://dev.epicgames.com/documentation/en-us/unreal-engine/visibility-and-occlusion-culling-in-unreal-engine#viewfrustum): Avoids rendering objects outside the camera's view frustum (the visible area of the camera). Only objects within this space, defined by the camera's field of view (FOV) and bounded by near and far clipping planes, are processed for rendering. Objects outside are ignored to save processing time. This feature is enabled by default.

[**Precomputed Visibility Culling**](https://dev.epicgames.com/documentation/en-us/unreal-engine/precomputed-visibility-volumes-in-unreal-engine): Precomputed Visibility Volumes store the visibility state of non-movable Actors in cells above shadow-casting surfaces. Generated offline during lighting builds, this method is ideal for small to medium-sized levels and works well on lower-end hardware and mobile devices. It trades expensive rendering thread costs for more manageable runtime memory usage, offering better performance flexibility on constrained systems.

[**Dynamic Occlusion Culling**](https://dev.epicgames.com/documentation/en-us/unreal-engine/visibility-and-occlusion-culling-in-unreal-engine#dynamicocclusion): Occlusion culling hides objects blocked by other objects within the camera's view, improving performance in dense scenes. It offers several methods ([Hardware Occlusion Queries](https://dev.epicgames.com/documentation/en-us/unreal-engine/visibility-and-occlusion-culling-in-unreal-engine#hardwareocclusionqueries), [Hierarchical Z-Buffer Occlusion](https://dev.epicgames.com/documentation/en-us/unreal-engine/visibility-and-occlusion-culling-in-unreal-engine#hierarchicalz-bufferocclusion), and [Round Robin Occlusion for VR](https://dev.epicgames.com/documentation/en-us/unreal-engine/visibility-and-occlusion-culling-in-unreal-engine#roundrobinocclusionforvr)) to track visibility states of Actors within the view frustum, issuing GPU or CPU queries to determine if objects are occluded.

Hardware Occlusion Queries are enabled by default and supported on platforms with **OpenGL ES 3.1** or higher (**iOS**) or **Vulkan** (**Android**), including some high-end mobile devices. To ensure occlusion culling skips rendering objects blocked by others, you can enable or adjust the following methods:

- **Hardware Occlusion Queries**: Enable this in `Project Settings > Rendering > Culling` by checking `Occlusion Culling`, or set the `r.AllowOcclusionQueries` console variable to `1` in the device config file.

![Standalone Mode (Mobile) - Rendering Settings - Occlusion Culling](project-rendering-settings-culling-occlusion.webp "Standalone Mode (Mobile) - Rendering Settings - Occlusion Culling")

- **Hierarchical Z-Buffer Occlusion**: Enable HZB by setting the `r.HZBOcclusion` console variable to `1`.

- **Round Robin Occlusion for VR**: Activate this for VR in the `.ini` config file, or at runtime using the `vr.RoundRobinOcclusion` console variable set to `1`.

__NOTE__: Additional culling options, such as **Light Culling**, **Volumetric Fog Culling**, and **Custom Code-driven Culling Rules** can be tweaked and fine-tuned in Unreal Engine for optimal performance.

__NOTE__: Unreal Engine provides various console commands for inspecting culling, including the [stat initviews](https://dev.epicgames.com/documentation/en-us/unreal-engine/visibility-and-occlusion-culling-in-unreal-engine#performancestatistics), [FreezeRendering](https://dev.epicgames.com/documentation/en-us/unreal-engine/visibility-and-occlusion-culling-in-unreal-engine#freezingrenderingofthescene), and [r.VisualizeOccludedPrimitives](https://dev.epicgames.com/documentation/en-us/unreal-engine/visibility-and-occlusion-culling-in-unreal-engine#visualizingoccludedactors) commands.

## Additional Optimization Measures

### Meta XR Plugin

The [Meta XR Unreal Engine Plugin](https://developers.meta.com/horizon/downloads/package/unreal-engine-5-integration/) includes a built-in **Project Setup Tool** to help optimize Unreal Engine projects for VR.

![Meta XR Plugin - Project Setup Tool](meta-xr-plugin-project-setup-tool.webp "Meta XR Plugin - Project Setup Tool")

Once opened, the tool displays all tweakable project settings across multiple tabs, regardless of their optimization status. It categorizes these settings into four sections: **Required Rules**, **Recommended Rules**, **Applied Rules**, and **Ignored Rules**.

![Meta XR Plugin - Project Setup Tool (Unoptimized Settings - All Quest Tab)](meta-xr-plugin-project-setup-tool-unoptimized-all-quest.webp "Meta XR Plugin - Project Setup Tool (Unoptimized Settings - All Quest Tab)")

![Meta XR Plugin - Project Setup Tool (Unoptimized Settings - PC Link Tab)](meta-xr-plugin-project-setup-tool-unoptimized-pc-link.webp "Meta XR Plugin - Project Setup Tool (Unoptimized Settings - PC Link Tab)")

![Meta XR Plugin - Project Setup Tool (Unoptimized Settings - Quest 3 Tab)](meta-xr-plugin-project-setup-tool-unoptimized-quest-3.webp "Meta XR Plugin - Project Setup Tool (Unoptimized Settings - Quest 3 Tab)")

![Meta XR Plugin - Project Setup Tool (Unoptimized Settings - Quest Pro Tab)](meta-xr-plugin-project-setup-tool-unoptimized-quest-pro.webp "Meta XR Plugin - Project Setup Tool (Unoptimized Settings - Quest Pro Tab)")

![Meta XR Plugin - Project Setup Tool (Unoptimized Settings - The Quest 2 Tab)](meta-xr-plugin-project-setup-tool-unoptimized-quest-2.webp "Meta XR Plugin - Project Setup Tool (Unoptimized Settings - The Quest 2 Tab)")

You can apply the required or recommended rules individually by clicking the `Apply` button next to each rule, or apply all rules in a section by using the `Apply All` button. Multiple presses of the `Apply All` button may be necessary to ensure all rules are applied. After applying the rules, the tool will prompt you to restart the editor for the changes to take effect.

![Meta XR Plugin - Project Setup Tool (Apply All and Restart Editor Prompt)](meta-xr-plugin-project-setup-tool-apply-all-restart-editor-prompt.webp "Meta XR Plugin - Project Setup Tool (Apply All and Restart Editor Prompt)")

After restarting, verify that all the rules in the Project Setup Tool across all tabs are applied. Occasionally, some rules may not take effect across the editor restarts, requiring you to repeat the process and restart the editor multiple times to correctly apply the changes.

![Meta XR Plugin - Project Setup Tool (Optimized Settings)](meta-xr-plugin-project-setup-tool-optimized-settings-applied.webp "Meta XR Plugin - Project Setup Tool (Optimized Settings)")

#### FFR

Consider utilizing [Fixed Foveated Rendering (FFR)](https://developers.meta.com/horizon/documentation/unreal/unreal-ffr/) which is a rendering technique used in virtual reality (VR) and augmented reality (AR) applications to optimize performance by reducing the graphical detail in the peripheral areas of the display, where the user is less likely to notice a loss in quality. The center of the view, where the user focuses the most, is rendered at full resolution, while the edges are rendered at a lower resolution. FFR is particularly effective in VR to increase frame rates and reduce the computational load on the GPU, enabling smoother experiences on hardware with limited performance capabilities. This technique is "fixed" because the high-resolution focus area does not adapt to where the user is looking.

Devices that support **FFR** include standalone VR headsets like the Meta Quest 2, Meta Quest Pro, and Quest 3, as well as tethered headsets like HTC Vive and Valve Index when paired with compatible GPUs.

#### ETFR

Consider utilizing [Eye-Tracked Foveated Rendering (ETFR)](https://developers.meta.com/horizon/documentation/unreal/unreal-eye-tracked-foveated-rendering/) which is an advanced rendering method that dynamically adjusts the resolution and graphical detail of a scene based on the user's gaze, as detected by eye-tracking technology. The area where the user is looking is rendered at the highest quality, while the rest of the scene is rendered at progressively lower resolutions. By concentrating computational resources on the exact area of focus, ETFR significantly reduces the GPU workload, enabling higher frame rates and improved performance, even for graphically intensive applications. ETFR is particularly beneficial in VR and AR environments, where it enhances realism and immersion while allowing developers to push hardware capabilities further.

![Meta XR Plugin - Eye-Tracked Foveated Rendering (ETFR) - Credits: Meta XR Documentation](meta-xr-plugin-eye-tracked-foveated-rendering-etfr.gif "Meta XR Plugin - Eye-Tracked Foveated Rendering (ETFR) - Credits: Meta XR Documentation")

Devices that support **ETFR** include VR headsets with integrated eye-tracking, such as the Meta Quest Pro, PlayStation VR2, and high-end models like the Varjo Aero and HTC Vive Pro Eye.

### HTC VIVE OpenXR Plugin

Headsets such as the HTC VIVE Focus 3 and Focus Vision feature larger framebuffers, higher eye-buffer resolutions, wider fields of view (FOV), and different refresh rates compared to HMDs like the Meta Quest series. As a result, performance may vary when running the same content across these devices.

#### Setting a Custom Pixel Density

If performance on the Focus 3 or Focus Vision is lower than on the Quest, it is recommended to adjust the **Pixel Density** to approximately `0.8` (or another value suited to your content). This reduces the eye-buffer resolution to match the Quest 2, improving FPS:

![HTC VIVE OpenXR Plugin - Setting a custom pixel density](htc-vive-openxr-plugin-set-pixel-density.webp "HTC VIVE OpenXR Plugin - Setting a custom pixel density")

#### Setting a Lower Refresh Rate

The [HTC Vive OpenXR Unreal Engine Plugin](https://developer.vive.com/resources/openxr/unreal/unreal-tutorials/viveppenxrplugininstallation/) provides various Blueprint functions to query supported refresh rates and adjust the current refresh rate according to your requirements:

![HTC VIVE OpenXR Plugin - ViveOpenXR plugin refresh rate Blueprint functions](htc-vive-openxr-plugin-refresh-rate-blueprint-functions.webp "HTC VIVE OpenXR Plugin - ViveOpenXR plugin refresh rate Blueprint functions")

However, before making these adjustments, you must enable the relevant settings by navigating to `Edit > Project Settings > Plugins > Vive OpenXR` and ensuring the `Enable Display Refresh Rate` option is checked. This option enables support for the OpenXR extension `XR_FB_display_refresh_rate`, allowing your application to dynamically adjust the display refresh rate to enhance user experience. Please note that you need to restart the engine after changing this setting for the changes to take effect.

![HTC VIVE OpenXR Plugin - Enable Display Refresh Rate Editor Restart Prompt](htc-vive-openxr-plugin-enable-display-refresh-rate-editor-restart-prompt.webp "HTC VIVE OpenXR Plugin - Enable Display Refresh Rate Editor Restart Prompt")

To query all available display refresh rates, use the Blueprint function `Enumerate Display Refresh Rates`:

![HTC VIVE OpenXR Plugin - Enumerating the available display refresh rates](htc-vive-openxr-plugin-enumerate-display-refresh-rates.webp "HTC VIVE OpenXR Plugin - Enumerating the available display refresh rates")

Currently, most devices return `75.0` and `90.0` Hz as available options.

To change the current display refresh rate, use the Blueprint function `Request Display Refresh Rate`:

![HTC VIVE OpenXR Plugin - Changing the current display refresh rate](htc-vive-openxr-plugin-request-display-refresh-rate.webp "HTC VIVE OpenXR Plugin - Changing the current display refresh rate")

To obtain the current display refresh rate, use the Blueprint function `Get Display Refresh Rate`:

![HTC VIVE OpenXR Plugin - Obtaining the current display refresh rate](htc-vive-openxr-plugin-get-display-refresh-rate.webp "HTC VIVE OpenXR Plugin - Obtaining the current display refresh rate")

If you need additional performance from your HTC VIVE HMD in standalone mode, consider lowering the target refresh rate from `90 Hz` to `75 Hz`. This adjustment can reduce GPU workload and enhance stability while maintaining an acceptable experience.

#### Optimal Rendering Settings

As a last resort, consider adding the following rendering settings to your project's `DefaultEngine.ini` under the `/Script/Engine.RendererSettings` section. Experiment with these settings to achieve your desired performance:

```ini
[/Script/Engine.RendererSettings]
r.Mobile.DisableVertexFog=True
r.Mobile.AllowDitheredLODTransition=False
r.Mobile.AllowSoftwareOcclusion=False
r.Mobile.VirtualTextures=False
r.DiscardUnusedQuality=False
r.AllowOcclusionQueries=True
r.MinScreenRadiusForLights=0.030000
r.MinScreenRadiusForDepthPrepass=0.030000
r.MinScreenRadiusForCSMDepth=0.010000
r.PrecomputedVisibilityWarning=False
r.TextureStreaming=True
Compat.UseDXT5NormalMaps=False
r.VirtualTextures=False
r.VirtualTexturedLightmaps=False
r.VT.TileSize=128
r.VT.TileBorderSize=4
r.vt.FeedbackFactor=16
r.VT.EnableCompressZlib=True
r.VT.EnableCompressCrunch=False
r.ClearCoatNormal=False
r.ReflectionCaptureResolution=128
r.ReflectionEnvironmentLightmapMixBasedOnRoughness=True
r.ForwardShading=True
r.VertexFoggingForOpaque=True
r.AllowStaticLighting=True
r.NormalMapsForStaticLighting=False
r.GenerateMeshDistanceFields=False
r.DistanceFieldBuild.EightBit=False
r.GenerateLandscapeGIData=False
r.DistanceFieldBuild.Compress=False
r.TessellationAdaptivePixelsPerTriangle=48.000000
r.SeparateTranslucency=True
r.TranslucentSortPolicy=0
TranslucentSortAxis=(X=0.000000,Y=-1.000000,Z=0.000000)
r.CustomDepth=1
r.CustomDepthTemporalAAJitter=True
r.PostProcessing.PropagateAlpha=2
r.DefaultFeature.Bloom=False
r.DefaultFeature.AmbientOcclusion=False
r.DefaultFeature.AmbientOcclusionStaticFraction=True
r.DefaultFeature.AutoExposure=False
r.DefaultFeature.AutoExposure.Method=0
r.DefaultFeature.AutoExposure.Bias=1.000000
r.DefaultFeature.AutoExposure.ExtendDefaultLuminanceRange=True
r.EyeAdaptation.EditorOnly=False
r.DefaultFeature.MotionBlur=False
r.DefaultFeature.LensFlare=False
r.TemporalAA.Upsampling=False
r.SSGI.Enable=False
r.AntiAliasingMethod=3
r.DefaultFeature.LightUnits=1
r.DefaultBackBufferPixelFormat=4
r.Shadow.UnbuiltPreviewInGame=True
r.StencilForLODDither=False
r.EarlyZPass=3
r.EarlyZPassOnlyMaterialMasking=False
r.DBuffer=True
r.ClearSceneMethod=1
r.VelocityOutputPass=0
r.Velocity.EnableVertexDeformation=0
r.SelectiveBasePassOutputs=False
bDefaultParticleCutouts=False
fx.GPUSimulationTextureSizeX=1024
fx.GPUSimulationTextureSizeY=1024
r.AllowGlobalClipPlane=False
r.GBufferFormat=1
r.MorphTarget.Mode=True
r.GPUCrashDebugging=False
vr.InstancedStereo=True
r.MobileHDR=False
vr.MobileMultiView=True
r.Mobile.UseHWsRGBEncoding=True
vr.RoundRobinOcclusion=False
vr.ODSCapture=False
r.MeshStreaming=False
r.WireframeCullThreshold=5.000000
r.RayTracing=False
r.RayTracing.UseTextureLod=False
r.SupportStationarySkylight=True
r.SupportLowQualityLightmaps=True
r.SupportPointLightWholeSceneShadows=True
r.SupportAtmosphericFog=True
r.SupportSkyAtmosphere=True
r.SupportSkyAtmosphereAffectsHeightFog=False
r.SkinCache.CompileShaders=False
r.SkinCache.DefaultBehavior=1
r.SkinCache.SceneMemoryLimitInMB=128.000000
r.Mobile.EnableStaticAndCSMShadowReceivers=True
r.Mobile.EnableMovableLightCSMShaderCulling=True
r.Mobile.AllowDistanceFieldShadows=True
r.Mobile.AllowMovableDirectionalLights=True
r.MobileNumDynamicPointLights=4
r.MobileDynamicPointLightsUseStaticBranch=True
r.Mobile.EnableMovableSpotlights=False
r.Mobile.EnableMovableSpotlightsShadow=False
r.GPUSkin.Support16BitBoneIndex=False
r.GPUSkin.Limit2BoneInfluences=False
r.SupportDepthOnlyIndexBuffers=True
r.SupportReversedIndexBuffers=True
r.LightPropagationVolume=False
r.Mobile.AmbientOcclusion=False
r.GPUSkin.UnlimitedBoneInfluences=False
r.GPUSkin.UnlimitedBoneInfluencesThreshold=8
r.Mobile.PlanarReflectionMode=0
bStreamSkeletalMeshLODs=(Default=False,PerPlatform=())
bDiscardSkeletalMeshOptionalLODs=(Default=False,PerPlatform=())
VisualizeCalibrationColorMaterialPath=None
VisualizeCalibrationCustomMaterialPath=None
VisualizeCalibrationGrayscaleMaterialPath=None
r.Mobile.AntiAliasing=3
r.Mobile.FloatPrecisionMode=2
r.OpenGL.ForceDXC=0
r.DynamicGlobalIlluminationMethod=1
r.ReflectionMethod=1
r.Shadow.Virtual.Enable=0
r.Lumen.TranslucencyReflections.FrontLayer.EnableForProject=False
```

### Game User Settings and Engine Scalability Settings

Unreal Engine offers predefined graphics quality profiles called [**Engine Scalability Settings**](https://dev.epicgames.com/documentation/en-us/unreal-engine/scalability-in-unreal-engine) to help you optimize performance effortlessly. These settings can be modified directly in the Unreal Editor through the Settings menu on the toolbar or dynamically during runtime using code. Importantly, these settings are universal—changes made in the Unreal Editor affect the game in PIE (Play In Editor) mode, while adjustments via code also influence the editor itself.

The available engine scalability levels are `Low`, `Medium`, `High`, `Epic`, and `Cinematic`. When setting the Engine Scalability Level through the Unreal Editor, you can create a `Custom` Engine Scalability Level by configuring individual quality settings as well. Additionally, you can let Unreal Engine determine the optimal settings by performing a hardware benchmark via the `Auto` button.

![Game User Settings and Engine Scalability Settings - Unreal Editor Engine Scalability Settings](unreal-editor-engine-scalability-settings.webp "Game User Settings and Engine Scalability Settings - Unreal Editor Engine Scalability Settings")

In Unreal Engine, you can specify the Engine Scalability Level using C++ or the Blueprint function `Set Overall Scalability Level`. You can also retrieve the current level with the `Get Overall Scalability Level` function.

![Game User Settings and Engine Scalability Settings - Overall Scalability Level](engine-scalability-settings-overall-level-blueprints.webp "Game User Settings and Engine Scalability Settings - Overall Scalability Level")

The `Get Overall Scalability Level` function returns the following numerical values to indicate the current scalability level:

- `-1`: Indicates the current Engine Scalability Level is set to `Custom`.
- `0`: Indicates the current Engine Scalability Level is set to `Low`.
- `1`: Indicates the current Engine Scalability Level is set to `Medium`.
- `2`: Indicates the current Engine Scalability Level is set to `High`.
- `3`: Indicates the current Engine Scalability Level is set to `Epic`.
- `4`: Indicates the current Engine Scalability Level is set to `Cinematic`.

The `Set Overall Scalability Level` function takes a `Value` parameter of type `Integer`, which defines the desired scalability level as follows:

- `0`: Sets the Engine Scalability Level to `Low`.
- `1`: Sets the Engine Scalability Level to `Medium`.
- `2`: Sets the Engine Scalability Level to `High`.
- `3`: Sets the Engine Scalability Level to `Epic`.
- `4`: Sets the Engine Scalability Level to `Cinematic`.

![Game User Settings and Engine Scalability Settings - Set Overall Scalability Level](engine-scalability-settings-overall-level-value-blueprints.webp "Game User Settings and Engine Scalability Settings - Set Overall Scalability Level")

Just like the Unreal Editor or C++, you can configure custom scalability levels in Blueprint by individually adjusting each relevant setting. This can be done using the corresponding Blueprint functions in the `Settings` actions category of the Blueprint Editor's context menu.

![Game User Settings and Engine Scalability Settings - Indiviual Quality Levels Set Functions](engine-scalability-settings-individual-quality-levels-1-blueprints.webp "Game User Settings and Engine Scalability Settings - Indiviual Quality Levels Set Functions")

![Game User Settings and Engine Scalability Settings - Indiviual Quality Levels Set Functions](engine-scalability-settings-individual-quality-levels-2-blueprints.webp "Game User Settings and Engine Scalability Settings - Indiviual Quality Levels Set Functions")

In fact, examining the C++ source code for the `SetFromSingleQualityLevel` function—used by the `Set Overall Scalability Level` Blueprint function—reveals that it calls the individual quality settings functions. This occurs when you select a scalability level in the Unreal Editor or set it through Blueprint code.

![Game User Settings and Engine Scalability Settings - SetFromSingleQualityLevel C++ Implementation](engine-scalability-settings-set-from-single-quality-level-cpp-source-code.webp "Game User Settings and Engine Scalability Settings - SetFromSingleQualityLevel C++ Implementation")

We can use the following Blueprints to bind keys `1` to `5` to switch between scalability levels from `Low` to `Cinematic`:

![Game User Settings and Engine Scalability Settings - Bind Key 1 to Set Engine Scalability Level to Low](engine-scalability-settings-set-low-blueprints.webp "Game User Settings and Engine Scalability Settings - Bind Key 1 to Set Engine Scalability Level to Low")

![Game User Settings and Engine Scalability Settings - Bind Key 2 to Set Engine Scalability Level to Medium](engine-scalability-settings-set-medium-blueprints.webp "Game User Settings and Engine Scalability Settings - Bind Key 2 to Set Engine Scalability Level to Medium")

![Game User Settings and Engine Scalability Settings - Bind Key 3 to Set Engine Scalability Level to High](engine-scalability-settings-set-high-blueprints.webp "Game User Settings and Engine Scalability Settings - Bind Key 3 to Set Engine Scalability Level to High")

![Game User Settings and Engine Scalability Settings - Bind Key 4 to Set Engine Scalability Level to Epic](engine-scalability-settings-set-epic-blueprints.webp "Game User Settings and Engine Scalability Settings - Bind Key 4 to Set Engine Scalability Level to Epic")

![Game User Settings and Engine Scalability Settings - Bind Key 5 to Set Engine Scalability Level to Cinematic](engine-scalability-settings-set-cinematic-blueprints.webp "Game User Settings and Engine Scalability Settings - Bind Key 5 to Set Engine Scalability Level to Cinematic")

We can also use the following Blueprints to bind key `0` to perform a hardware benchmark and determine the optimal scalability level automatically:

![Game User Settings and Engine Scalability Settings - Bind Key 0 to Perform Hardware Benchmark and Auto Determine the Optimal Engine Scalability Level"](engine-scalability-settings-hardware-benchmark-blueprints.webp "Game User Settings and Engine Scalability Settings - Bind Key 0 to Perform Hardware Benchmark and Auto Determine the Optimal Engine Scalability Level")

It’s possible to simplify the above Blueprints by converting the above code into a Blueprint function, for example, `Set Engine Scalability Level`:

![Game User Settings and Engine Scalability Settings - Set Engine Scalability Level Blueprint Function Implementation (Overview)](engine-scalability-settings-set-level-blueprint-function-implementation-overview.webp "Game User Settings and Engine Scalability Settings - Set Engine Scalability Level Blueprint Function Implementation (Overview)")

Also, in order to utilize the above function and avoid memorizing numerical values instead of scalability level names, we can define an `EngineScalabilitySettings` enumeration in Unreal Engine with the following enum names mapped to the following numerical values:

- `Low`: Evaluates to `0`.
- `Medium`: Evaluates to `1`.
- `High`: Evaluates to `2`.
- `Epic`: Evaluates to `3`.
- `Cinematic`: Evaluates to `4`.
- `Custom`: Evaluates to `5`.
- `Auto`: Evaluates to `6`.

![Game User Settings and Engine Scalability Settings - EngineScalabilitySettings Enum](engine-scalability-settings-custom-enumeration.webp "Game User Settings and Engine Scalability Settings - EngineScalabilitySettings Enum")

In any case, you can see the implementation of `Set Engine Scalability Level` in more detail in the following screenshots:

![Game User Settings and Engine Scalability Settings - Set Engine Scalability Level Blueprint Function Implementation (Game User Settings Validation and Switch on EngineScalabilitySettings Enum)](engine-scalability-settings-set-level-blueprint-function-implementation-validate-game-user-settings.webp "Game User Settings and Engine Scalability Settings - Set Engine Scalability Level Blueprint Function Implementation (Game User Settings Validation and Switch on EngineScalabilitySettings Enum)")

![Game User Settings and Engine Scalability Settings - Set Engine Scalability Level Blueprint Function Implementation (Switch on EngineScalabilitySettings Enum and Applying Engine Scalability Settings)](engine-scalability-settings-set-level-blueprint-function-implementation-switch-apply.webp "Game User Settings and Engine Scalability Settings - Set Engine Scalability Level Blueprint Function Implementation (Switch on EngineScalabilitySettings Enum and Applying Engine Scalability Settings)")

![Game User Settings and Engine Scalability Settings - Set Engine Scalability Level Blueprint Function Implementation (Hardware Benchmarking)](engine-scalability-settings-set-level-blueprint-function-implementation-perform-hardware-benchmark.webp "Game User Settings and Engine Scalability Settings - Set Engine Scalability Level Blueprint Function Implementation (Hardware Benchmarking)")

Now using the above `Set Engine Scalability Level` function and `EngineScalabilitySettings` enum, the simplified Blueprint code for performing the hardware benchmark or setting the engine scalability levels looks like this:

![Game User Settings and Engine Scalability Settings - Simplified Blueprint Code for Binding Keys 0 to 5 to Perform Hardware Benchmark or Setting Engine Scalability Levels](engine-scalability-settings-set-simplified-blueprints.webp "Game User Settings and Engine Scalability Settings - Simplified Blueprint Code for Binding Keys 0 to 5 to Perform Hardware Benchmark or Setting Engine Scalability Levels")

In a similar fashion, we can define a `Get Engine Scalability Level` function, which can be used to retrieve the name of the current engine scalability level instead of the numerical values:

![Game User Settings and Engine Scalability Settings - Get Engine Scalability Level Blueprint Function Implementation](engine-scalability-settings-get-level-blueprint-function-implementation.webp "Game User Settings and Engine Scalability Settings - Get Engine Scalability Level Blueprint Function Implementation")

And then we can utilize it like this to print the engine scalability level name on screen and inside the engine logs:

![Game User Settings and Engine Scalability Settings - Printing the Engine Scalability Level Name on Screen and Inside the Engine Logs](engine-scalability-settings-get-level-blueprints.webp "Game User Settings and Engine Scalability Settings - Printing the Engine Scalability Level Name on Screen and Inside the Engine Logs")

Even better, we can implement a 3D Blueprint Widget using the following Blueprint implementation to display the current Engine Scalability Level and the real-time FPS on a widget inside our level:

![Game User Settings and Engine Scalability Settings - The Engine Scalability Level and FPS 3D Widget Implementation](engine-scalability-settings-framerate-blueprint-widget-implementation.webp "Game User Settings and Engine Scalability Settings - The Engine Scalability Level and FPS 3D Widget Implementation")

### NVIDIA DLSS

Consider utilizing [NVIDIA Deep Learning Super Sampling (DLSS)](https://developer.nvidia.com/rtx/dlss/get-started) which is a technology developed by NVIDIA that leverages artificial intelligence (AI) to upscale lower-resolution images into higher-resolution visuals in real-time while maintaining or enhancing visual fidelity. Using dedicated Tensor Cores on NVIDIA's RTX GPUs, DLSS employs deep neural networks to reconstruct images with detail and sharpness that rivals native rendering. This process reduces the computational load on the GPU, allowing for higher frame rates without significant sacrifices in visual quality. DLSS is exclusive to NVIDIA hardware, specifically GeForce RTX cards starting from the RTX 2000 series and newer.

### AMD FSR

Consider utilizing [AMD FidelityFX Super Resolution (FSR)](https://gpuopen.com/learn/ue-fsr3/) which is AMD's upscaling technology designed to boost frame rates by rendering games at a lower resolution and upscaling them to a higher resolution using a spatial or temporal upscaling algorithm. Unlike NVIDIA DLSS, FSR does not require specialized AI hardware, making it compatible with a broader range of GPUs, including AMD Radeon GPUs (from RX 400 series and newer), select NVIDIA GPUs (GeForce GTX 10 series and newer), and even some integrated GPUs. This wide compatibility is due to its hardware-agnostic nature, enabling developers to implement FSR across a wide array of platforms.

### Intel XeSS

Consider utilizing [Intel Xe Super Sampling (XeSS)](https://github.com/GameTechDev/XeSSUnrealPlugin) which is Intel's AI-based upscaling technology that improves gaming performance and visual quality by rendering games at a lower resolution and then upscaling to a higher resolution using advanced machine learning algorithms. XeSS reconstructs high-quality images with enhanced detail, sharpness, and temporal stability, providing visuals comparable to native resolution while boosting frame rates. Designed for a wide range of hardware, XeSS works best on Intel GPUs equipped with Xe Matrix Extensions (XMX) AI acceleration, such as the Intel Arc GPUs. Additionally, XeSS supports other hardware, including non-Intel GPUs like AMD and NVIDIA, by using DP4a instructions, ensuring broader compatibility across various systems.
