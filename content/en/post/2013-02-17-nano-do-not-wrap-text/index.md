+++
title = "nano, Do Not Wrap Text"
slug = "nano-do-not-wrap-text"
date = 2013-02-17T01:13:00+03:30
tags = [ "Console", "FLOSS", "FOSS", "FreeBSD", "Funtoo", "Gentoo", "GNU", "Linux", "nano", "Terminal", "Unix" ]
aliases = [ "/blog/2013/02/17/nano-do-not-wrap-text/" ]
+++

[GNU nano](http://www.nano-editor.org/) is my favorite text editor while I'm on console. However, there's one thing about nano which annoys me: _automatic text wrapping!_

Hopefully, there are two simple ways to overcome this. By using either __-w__ command-line argument, or __set nowrap__ configuration command within the file __~/.nanorc__.

**1.** The temporary solution by using __-w__ command-line argument, which should be used each time you run nano:

{{< highlight sh >}}
$ nano -w /path/to/file
{{</ highlight >}}

**2.** The permanent solution by setting off automatic text wrapping using the configuration command __set nowrap__, in the __~/.nanorc__ file:

{{< codeblock title="~/.nanorc" line_numbers="true" >}}
set nowrap
{{< /codeblock >}}

Note: If the file doesn't exist, you should create it first:

{{< highlight sh >}}
$ touch ~/.nanorc
{{</ highlight >}}

<!--more-->
