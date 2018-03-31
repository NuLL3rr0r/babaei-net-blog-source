+++
title = "nano, Syntax Highlighting"
slug = "nano-syntax-highlighting"
date = 2013-02-17T01:27:00Z
tags = [ "Console", "FreeBSD", "Funtoo", "Gentoo", "GNU", "Linux", "nano", "Terminal", "Unix" ]
#template = "post.html"
+++

[GNU nano](http://www.nano-editor.org/) is my favorite text editor while I'm on console. Although, it doesn't offer syntax highlighting by default, it comes with a decent set of syntax highlighting files. Usually, these files are exist in __/usr/local/share/nano__ or __/usr/share/nano__, depending on your distro's preference. You can enable syntax highlighting for your prefered language(s) by including related file(s) with __.nanorc__ extension in your __~/.nanorc__ file.

{% codeblock(description="~/.nanorc - FreeBSD", lang="sh") %}
include "/usr/local/share/nano/asm.nanorc"
include "/usr/local/share/nano/awk.nanorc"
include "/usr/local/share/nano/c.nanorc"
include "/usr/local/share/nano/cmake.nanorc"
include "/usr/local/share/nano/css.nanorc"
include "/usr/local/share/nano/debian.nanorc"
include "/usr/local/share/nano/fortran.nanorc"
include "/usr/local/share/nano/gentoo.nanorc"
include "/usr/local/share/nano/groff.nanorc"
include "/usr/local/share/nano/html.nanorc"
include "/usr/local/share/nano/java.nanorc"
include "/usr/local/share/nano/makefile.nanorc"
include "/usr/local/share/nano/man.nanorc"
include "/usr/local/share/nano/mgp.nanorc"
include "/usr/local/share/nano/mutt.nanorc"
include "/usr/local/share/nano/nanorc.nanorc"
include "/usr/local/share/nano/objc.nanorc"
include "/usr/local/share/nano/ocaml.nanorc"
include "/usr/local/share/nano/patch.nanorc"
include "/usr/local/share/nano/perl.nanorc"
include "/usr/local/share/nano/php.nanorc"
include "/usr/local/share/nano/pov.nanorc"
include "/usr/local/share/nano/python.nanorc"
include "/usr/local/share/nano/ruby.nanorc"
include "/usr/local/share/nano/sh.nanorc"
include "/usr/local/share/nano/tcl.nanorc"
include "/usr/local/share/nano/tex.nanorc"
include "/usr/local/share/nano/xml.nanorc"
{% end %}

{% codeblock(description="~/.nanorc - Funtoo or Gentoo", lang="sh") %}
include "/usr/share/nano/asm.nanorc"
include "/usr/share/nano/awk.nanorc"
include "/usr/share/nano/c.nanorc"
include "/usr/share/nano/cmake.nanorc"
include "/usr/share/nano/css.nanorc"
include "/usr/share/nano/debian.nanorc"
include "/usr/share/nano/fortran.nanorc"
include "/usr/share/nano/gentoo.nanorc"
include "/usr/share/nano/groff.nanorc"
include "/usr/share/nano/html.nanorc"
include "/usr/share/nano/java.nanorc"
include "/usr/share/nano/makefile.nanorc"
include "/usr/share/nano/man.nanorc"
include "/usr/share/nano/mgp.nanorc"
include "/usr/share/nano/mutt.nanorc"
include "/usr/share/nano/nanorc.nanorc"
include "/usr/share/nano/objc.nanorc"
include "/usr/share/nano/ocaml.nanorc"
include "/usr/share/nano/patch.nanorc"
include "/usr/share/nano/perl.nanorc"
include "/usr/share/nano/php.nanorc"
include "/usr/share/nano/pov.nanorc"
include "/usr/share/nano/python.nanorc"
include "/usr/share/nano/ruby.nanorc"
include "/usr/share/nano/sh.nanorc"
include "/usr/share/nano/tcl.nanorc"
include "/usr/share/nano/tex.nanorc"
include "/usr/share/nano/xml.nanorc"
{% end %}

Note: If the file doesn't exist, you should create it first:

```sh
$ touch ~/.nanorc
```

<!-- more -->

<br/>

**UPDATE:** I usually get the list of all <code>.nanorc</code> files on my system and write them to my <code>~/.nanorc</code> using the following one liner set of commands. It should work on both <code>bash</code> and <code>csh</code>. Moreover, [it disables text-wrapping](/blog/2013/02/17/nano-do-not-wrap-text/) which you can enable by cutting it off from the begging of it. _Just be warned it generates a new <code>~/.nanorc</code> file for the current user and wipes out all of your old settings._

{% codeblock(description="*BSD", lang="sh") %}
$ printf 'set nowrap\n\n' > ~/.nanorc && find /usr/local/share/nano/ -iname '*.nanorc' | xargs printf 'include "%s"\n' >> ~/.nanorc && cat ~/.nanorc
{% end %}

{% codeblock(description="GNU/Linux", lang="sh") %}
$ printf 'set nowrap\n\n' > ~/.nanorc && find /usr/share/nano/ -iname '*.nanorc' | xargs printf 'include "%s"\n' >> ~/.nanorc && cat ~/.nanorc
{% end %}

<br/>

### Related Articles ###

[nano, Do not wrap text](/blog/2013/02/17/nano-do-not-wrap-text/)  
[Colors Talk: A Colorful Terminal / Console](/blog/2013/03/03/colors-talk-a-colorful-terminal-console/)

