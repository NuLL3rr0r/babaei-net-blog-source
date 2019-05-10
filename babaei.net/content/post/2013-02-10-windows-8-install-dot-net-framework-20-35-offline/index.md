+++
title = "Windows 8, Install .NET Framework 2.0 - 3.5 Offline"
slug = "windows-8-install-dot-net-framework-20-35-offline"
date = 2013-02-10T17:31:00+03:30
tags = [ "C#", ".NET", ".NET Framework", "Mono", "Windows" ]
aliases = [ "/blog/2013/02/10/windows-8-install-dot-net-framework-20-35-offline/" ]
+++

Well, I've failed to install .NET Framework 2.0/3.5 in Windows 8 using Program and Features in Control Panel, which I need for an older project I've done long ago. But I came across an easy solution which did the trick.

In Windows Command Prompt (cmd.exe) or Run dialog, enter the following command and hit Enter:

{{< highlight cmd >}}
> Dism /online /enable-feature /featurename:NetFx3 /All /Source:x:\sources\sxs /LimitAccess
{{< /highlight >}}

Replace **x:** with path of your Windows 8 installation DVD.

- _**Note**: You have to run cmd.exe as Administrator in order for this to work!_

<!--more-->
