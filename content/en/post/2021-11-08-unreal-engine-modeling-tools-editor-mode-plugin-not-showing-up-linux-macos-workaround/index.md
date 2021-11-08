+++
title = "A quick workaround for Unreal Engine Modeling Tools Editor Mode plugin not showing up on Linux and macOS"
slug = "unreal-engine-modeling-tools-editor-mode-plugin-not-showing-up-linux-macos-workaround"
date = 2021-11-08T01:10:00+01:00
tags = [ "C", "C++", "Epic Games", "Game Development", "Game Programming", "gamedev", "GNU", "Linux", "macOS", "Qt Creator", "UDK", "UE4", "UE5", "Unreal Engine", "UnrealScript", "Windows", "ZFS" ]
toc = true
+++

**UPDATE 1 [2021/07/25]**: _For whitelisting macOS one could simply add <code>Mac</code> to <code>PlatformAllowList</code> inside the <code>.uplugin</code> file. e.g._:

{{< codeblock lang="sh" title="Whitelisting Linux inside ModelingToolsEditorMode.uplugin" >}}
	"Modules": [
		{
			"Name": "ModelingToolsEditorMode",
			"Type": "Editor",
			"LoadingPhase": "Default",
			"PlatformAllowList": [ "Win64", "Linux", "Mac" ]
		}
	],
{{< /codeblock >}}

<hr />

I've been trying to enable and make use of [UE5's Modeling Tools Editor Mode Plugin](https://www.unrealengine.com/en-US/tech-blog/unreal-engine-5-s-modeling-mode-takes-shape) inside the editor built from <code>ue5-main</code> and <code>5.0</code> and struggled to some extent. According to Epic Games, this should suffice:

{{< blockquote author="Russell Paul from Unreal Engine's blog" link="https://www.unrealengine.com/en-US/tech-blog/unreal-engine-5-s-modeling-mode-takes-shape" title="Unreal Engine 5’s modeling mode takes shape" >}}
If you are starting up a new project, the modeling mode plugin may need to be turned on. From the Plugins window, enable the Modeling Tools Editor Mode Plugin and restart Unreal Engine.
{{< /blockquote >}}

So, I did enable the plugin from inside the editor:

{{< figure src="/blog/unreal-engine-modeling-tools-editor-mode-plugin-not-showing-up-linux-macos-workaround/enabling-unreal-engine-modeling-tools-editor-mode-plugin.webp" alt="Enabling Unreal Engine Modeling Tools Editor Mode plugin" caption="Enabling Unreal Engine Modeling Tools Editor Mode Plugin" >}}

To no avail and I was never able to find it inside the UE5 editor:

{{< figure src="/blog/unreal-engine-modeling-tools-editor-mode-plugin-not-showing-up-linux-macos-workaround/unreal-engine-modeling-tools-editor-mode-plugin-not-showing-up-linux-macos.webp" alt="Unreal Engine Modeling Tools Editor Mode plugin not showing up after being enabled" caption="Unreal Engine Modeling Tools Editor Mode plugin not showing up after being enabled" >}}

Despite that, I was able to figure out what's wrong. Here's how I fixed it on Linux and it's an easy fix. It probably works on macOS, too. Though I have no idea why Epic Games has disabled it on non-Windows platforms in spite of the fact that it works just fine.

<!--more-->

I investigated the <code>.uplugin</code> file for the Modeling Tools Editor Mode plugin, and figured only Windows has been whitelisted by Epic Games:

{{< highlight sh >}}
$ cat Engine/Plugins/Editor/ModelingToolsEditorMode/ModelingToolsEditorMode.uplugin

{
	"FileVersion": 3,
	"Version": 1,
	"VersionName": "0.1",
	"FriendlyName": "Modeling Tools Editor Mode",
	"Description": "Modeling Tools Mode includes a suite of interactive tools for creating and editing meshes in the Editor",
	"Category": "Editor",
	"CreatedBy": "Epic Games, Inc.",
	"CreatedByURL": "http://epicgames.com",
	"DocsURL": "",
	"MarketplaceURL": "",
	"SupportURL": "",
	"CanContainContent": true,
	"IsBetaVersion": true,
	"Installed": false,
	"Modules": [
		{
			"Name": "ModelingToolsEditorMode",
			"Type": "Editor",
			"LoadingPhase": "Default",
			"PlatformAllowList": [ "Win64" ]
		}
	],
	"Plugins": [
		{
			"Name": "MeshModelingToolset",
			"Enabled": true,
			"TargetAllowList": [ "Editor" ]
		},
		{
			"Name": "MeshModelingToolsetExp",
			"Enabled": true,
			"TargetAllowList": [ "Editor" ]
		},
		{
			"Name": "MeshLODToolset",
			"Enabled": true,
			"TargetAllowList": [ "Editor" ]
		},
		{
			"Name": "StylusInput",
			"Enabled": true
		}
	]
}
{{< /highlight >}}

So, as an experiment I tried to whitelist Linux by editing the following section inside the <code>.uplugin</code> file:

{{< codeblock lang="sh" title="Whitelisting Linux inside ModelingToolsEditorMode.uplugin" >}}
	"Modules": [
		{
			"Name": "ModelingToolsEditorMode",
			"Type": "Editor",
			"LoadingPhase": "Default",
			"PlatformAllowList": [ "Win64", "Linux" ]
		}
	],
{{< /codeblock >}}

And tried to build and re-run the Editor inside Qt Creator, which failed with the following error:

{{< codeblock lang="sh" title="Modeling Tools Editor Mode plugin build failure due to a reckless case-sensitive include error" >}}
bash /home/mamadou/dev/MamadouArchives/Engine/Build/BatchFiles/Linux/Build.sh MamadouArchivesEditor Linux DebugGame 
Setting up bundled DotNet SDK
Microsoft (R) Build Engine version 16.7.0-preview-20360-03+188921e2f for .NET
Copyright (C) Microsoft Corporation. All rights reserved.


Build succeeded.
    0 Warning(s)
    0 Error(s)

Time Elapsed 00:00:01.98
Running command : dotnet Engine/Binaries/DotNET/UnrealBuildTool/UnrealBuildTool.dll MamadouArchivesEditor Linux DebugGame
Log file: /home/mamadou/dev/MamadouArchives/Engine/Programs/UnrealBuildTool/Log.txt
Linux using Manual SDK v19_clang-11.0.1-centos7
Using 'git status' to determine working set for adaptive non-unity build (/home/mamadou/dev/MamadouArchives).
Invalidating makefile for MamadouArchivesEditor (ModelingToolsEditorMode.uplugin modified)
Invalidating makefile for UnrealHeaderTool (ModelingToolsEditorMode.uplugin modified)
Parsing headers for MamadouArchivesEditor
  Running UnrealHeaderTool "/home/mamadou/dev/MamadouArchives/MamadouArchives/MamadouArchives.uproject" "/home/mamadou/dev/MamadouArchives/MamadouArchives/Intermediate/Build/Linux/B4D820EA/MamadouArchivesEditor/DebugGame/MamadouArchivesEditor.uhtmanifest" -LogCmds="loginit warning, logexit warning, logdatabase error" -Unattended -WarningsAsErrors -abslog="/home/mamadou/dev/MamadouArchives/Engine/Programs/UnrealBuildTool/Log_UHT.txt"
Reflection code generated for MamadouArchivesEditor in 3.3097077 seconds
Building MamadouArchivesEditor...
Determining max actions to execute in parallel (8 physical cores, 8 logical cores)
  Executing up to 8 processes, one per physical core
Building 18 actions with 8 processes...
[1/18] Compile Module.GeometryFlowMeshProcessingEditor.cpp
[2/18] Compile Module.MeshLODToolset.cpp
In file included from /home/mamadou/dev/MamadouArchives/Engine/Plugins/Experimental/MeshLODToolset/Intermediate/Build/Linux/B4D820EA/UnrealEditor/Development/MeshLODToolset/Module.MeshLODToolset.cpp:3:
/home/mamadou/dev/MamadouArchives/Engine/Plugins/Experimental/MeshLODToolset/Source/MeshLODToolset/Private/Graphs/GenerateStaticMeshLODProcess.cpp:26:10: fatal error: 'UObject/Metadata.h' file not found
#include "UObject/Metadata.h"
         ^~~~~~~~~~~~~~~~~~~~
1 error generated.
[3/18] Compile Module.ModelingComponentsEditorOnly.gen.cpp
[4/18] Compile Module.ModelingOperatorsEditorOnly.gen.cpp
[5/18] Compile Module.MeshModelingToolsEditorOnly.gen.cpp
[6/18] Compile Module.MeshLODToolset.gen.cpp
[7/18] Compile Module.ModelingComponentsEditorOnly.cpp
[8/18] Compile Module.ModelingToolsEditorMode.gen.cpp
[9/18] Link (lld) libUnrealEditor-ModelingComponentsEditorOnly.so
[10/18] Compile Module.ModelingOperatorsEditorOnly.cpp
[11/18] Link (lld) libUnrealEditor-ModelingOperatorsEditorOnly.so
[12/18] Link (lld) libUnrealEditor-GeometryFlowMeshProcessingEditor.so
[13/18] Compile Module.MeshModelingToolsEditorOnly.cpp
[14/18] Link (lld) libUnrealEditor-MeshModelingToolsEditorOnly.so
[15/18] Compile Module.ModelingToolsEditorMode.cpp
make: *** [Makefile:73865: MamadouArchivesEditor-Linux-DebugGame] Error 6
00:41:35: The process "/usr/bin/make" exited with code 2.
Error while building/deploying project UE5 (kit: MamadouArchives Bundled Toolchain)
The kit MamadouArchives Bundled Toolchain has configuration issues which might be the root cause for this problem.
When executing step "Make"
00:41:35: Elapsed time: 01:44.
{{< /codeblock >}}

The issue is <code>UObject/Metadata.h</code> file does not exist on case-sensitive filesytems (I'm using ZFS) or operating systems such as GNU/Linux. The correct file name is <code>"UObject/MetaData.h"</code>. Thus changing that from:

{{< codeblock lang="cpp" title="Engine/Plugins/Experimental/MeshLODToolset/Source/MeshLODToolset/Private/Graphs/GenerateStaticMeshLODProcess.cpp" >}}
#include "UObject/Metadata.h"
{{< /codeblock >}}

To:

{{< codeblock lang="cpp" title="Engine/Plugins/Experimental/MeshLODToolset/Source/MeshLODToolset/Private/Graphs/GenerateStaticMeshLODProcess.cpp" >}}
#include "UObject/MetaData.h"
{{< /codeblock >}}

Fixed the build issue. I Fired up the editor and I was able to immediately spot the Modeling Mode inside the UE5 editor:

{{< figure src="/blog/unreal-engine-modeling-tools-editor-mode-plugin-not-showing-up-linux-macos-workaround/unreal-engine-modeling-tools-editor-mode-plugin-linux.webp" alt="Unreal Engine Modeling Tools Editor Mode plugin on GNU/Linux" caption="Unreal Engine Modeling Tools Editor Mode plugin on GNU/Linux" >}}

And, it works flawlessly on Linux just as advertised by Epic Games!

This is the <code>git diff</code> of all the required changes in order to fix the issue:

{{< codeblock lang="sh" title="git diff" >}}
diff --git a/Engine/Plugins/Editor/ModelingToolsEditorMode/ModelingToolsEditorMode.uplugin b/Engine/Plugins/Editor/ModelingToolsEditorMode/ModelingToolsEditorMode.uplugin
index 13fa092e0..226722232 100644
--- a/Engine/Plugins/Editor/ModelingToolsEditorMode/ModelingToolsEditorMode.uplugin
+++ b/Engine/Plugins/Editor/ModelingToolsEditorMode/ModelingToolsEditorMode.uplugin
@@ -18,7 +18,7 @@
 			"Name": "ModelingToolsEditorMode",
 			"Type": "Editor",
 			"LoadingPhase": "Default",
-			"PlatformAllowList": [ "Win64" ]
+			"PlatformAllowList": [ "Win64", "Linux" ]
 		}
 	],
 	"Plugins": [
diff --git a/Engine/Plugins/Experimental/MeshLODToolset/Source/MeshLODToolset/Private/Graphs/GenerateStaticMeshLODProcess.cpp b/Engine/Plugins/Experimental/MeshLODToolset/Source/MeshLODToolset/Private/Graphs/GenerateStaticMeshLODProcess.cpp
index 594977f2f..be7e51faf 100644
--- a/Engine/Plugins/Experimental/MeshLODToolset/Source/MeshLODToolset/Private/Graphs/GenerateStaticMeshLODProcess.cpp
+++ b/Engine/Plugins/Experimental/MeshLODToolset/Source/MeshLODToolset/Private/Graphs/GenerateStaticMeshLODProcess.cpp
@@ -23,7 +23,7 @@
 #include "AssetRegistryModule.h"
 #include "IAssetTools.h"
 #include "FileHelpers.h"
-#include "UObject/Metadata.h"
+#include "UObject/MetaData.h"
 
 #include "Engine/Engine.h"
 #include "Editor.h"
{{< /codeblock >}}
