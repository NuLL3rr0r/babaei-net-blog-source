---
layout: post
title: "nano, Do not wrap text"
date: 2013-02-17 01:13
comments: true
tags:
- Console
- FreeBSD
- Funtoo
- Gentoo
- GNU
- Linux
- nano
- Terminal
- Unix
---

[GNU nano](http://www.nano-editor.org/) is my favorite text editor while I'm on console. However, there's one thing about nano which annoys me: _automatic text wrapping!_

Hopefully, there are two simple ways to overcome this. By using either __-w__ command-line argument, or __set nowrap__ configuration command within the file __~/.nanorc__.

**1.** The temporary solution by using __-w__ command-line argument, which should be used each time you run nano:

{% codeblock lang:sh %}
$ nano -w /path/to/file
{% endcodeblock %}

**2.** The permanent solution by setting off automatic text wrapping using the configuration command __set nowrap__, in the __~/.nanorc__ file:

{% codeblock ~/.nanorc lang:sh %}
set nowrap
{% endcodeblock %}

Note: If the file doesn't exist, you should create it first:

{% codeblock lang:sh %}
$ touch ~/.nanorc
{% endcodeblock %}

<!-- more -->

<br/>

### Related Articles ###

[nano, Syntax Highlighting](/blog/2013/02/17/nano-syntax-highlighting/)  
[Colors Talk: A Colorful Terminal / Console](/blog/2013/03/03/colors-talk-a-colorful-terminal-console/)

