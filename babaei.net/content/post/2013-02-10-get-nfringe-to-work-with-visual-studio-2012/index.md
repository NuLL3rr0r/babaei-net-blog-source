+++
title = "Get nFringe to Work with Visual Studio 2012"
slug = "get-nfringe-to-work-with-visual-studio-2012"
date = 2013-02-10T17:53:00+03:30
tags = [ "Epic Games", "Game Development", "Game Programming", "nFringe", "UDK", "UE", "Unreal Engine" "UnrealScript", "Visual Stuio", "Windows" ]
aliases = [ "/blog/2013/02/10/get-nfringe-to-work-with-visual-studio-2012/" ]
+++

As you've noticed there's still no official support for Microsoft Visual Studio 2012 in recent Pixel Mine nFringe releases. While ago I came across [an awesome forum post at Epic Games Forums]( http://forums.epicgames.com/threads/874296-debug-Unreal-Script-error-at-vs2011?p=30795357&viewfull=1#post30795357) which describs a simple process of getting nFringe to work with VS2012. Since then I've used it in my day to day development tasks and I had no difficulties at all using it. And damn, it's pretty stable despite the fact that not officially supported by Pixel Mine. Even nFringe version 1.1 which I've tested is playing nice with VS2012.

The only prerequisite that you need is your previous VS2010 + nFringe installation to obtain some files from it. Once you've acquired these files you don't need VS2010 or nFringe installer for further installations.

**1.** Open Windows Command Prompt (cmd.exe) and run the following commands:

```
> xcopy /E "C:\Program Files (x86)\Microsoft Visual Studio 10.0\Common7\IDE\Extensions\Pixel Mine" "C:\Program Files (x86)\Microsoft Visual Studio 11.0\Common7\IDE\Extensions\"
> xcopy /E "C:\Program Files (x86)\Microsoft Visual Studio 10.0\UnrealScript" "C:\Program Files (x86)\Microsoft Visual Studio 11.0\"
```

**2.** Open up **extension.vsixmanifest** in Notepad or your favorite editor and change **VisualStudio Version** to **11** (Note: In the following path change **1.1** with your nfringe version, e.g. 1.2).

```
> notepad "C:\Program Files (x86)\Microsoft Visual Studio 11.0\Common7\IDE\Extensions\Pixel Mine nFringe (UnrealScript)\1.1\extension.vsixmanifest"
```

{{< codeblock lang="xml" title="extension.vsixmanifest" >}}
    <InstalledByMsi>true</InstalledByMsi>
    <SupportedProducts>
      <VisualStudio Version="11.0">
{{< /codeblock >}}

**3.** Run the following command to register nFringe extension in Visual Studio 2012:

```
> "C:\Program Files (x86)\Microsoft Visual Studio 11.0\Common7\IDE\devenv.exe" /setup
```

**4.** Finally, you need to re-validate your nFringe license in VS2012.

Happy coding ;)

<!--more-->
