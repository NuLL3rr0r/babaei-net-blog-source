+++
title = "Colors Talk: A Colorful Terminal / Console"
slug = "colors-talk-a-colorful-terminal-console"
date = 2013-03-03T05:10:00Z
tags = [ "Bash", "Console", "csh", "FreeBSD", "Funtoo", "Gentoo", "GNOME", "GNU", "KDE", "Linux", "LXDE", "nano", "sh", "Terminal", "Unix", "XFCE" ]
#template = "post.html"
+++

If you've ever used a __GNU__ [Gentoo](http://www.gentoo.org/) or [Funtoo](http://www.funtoo.org/wiki/Welcome) __Linux__ variant, or a live version of any of them, you may have noticed their eye-catching colorful terminal or console. Whether you're on a virtual console or one of __KDE__, __GNOME__, __XFCE__, __LXDE__ terminal apps.

{{ img(src="/colors-talk-a-colorful-terminal-console/colors-talk-a-colorful-terminal-console-1.jpg", href="/colors-talk-a-colorful-terminal-console/colors-talk-a-colorful-terminal-console-1.jpg", description="A Colorful Xfce4 Terminal on FreeBSD (Bash)", width=825, height=509) }}

{{ img(src="/colors-talk-a-colorful-terminal-console/colors-talk-a-colorful-terminal-console-2.jpg", href="/colors-talk-a-colorful-terminal-console/colors-talk-a-colorful-terminal-console-2.jpg", description="The default Xfce4 Terminal on FreeBSD (sh csh)", width=825, height=509) }}

When I've migrated from __Funtoo__ to [FreeBSD](http://www.freebsd.org), the one thing that I've missed so badly was its colorful terminal. The nice thing about these colors is taht they always give you some valuable hints, e.g., currently you're __root__ user or a regular user, the file is a symlink (Symbolic link), executable or just a regular file.

Well, it's pretty easy to have your own colorful terminal or console, once you've found out how __Gentoo__ and __Funtoo__ did that. Fortunately, it works on __*BSD__ and all other __Linux__ distros as well. So, stay with me and I'll describe the process in the following.

<!-- more -->

OK! before we continue, let's say we have the user __babaei__ and the defualt __root__ account on our distro which we want to enable the colorful terminal or console for.

**1.** Before we proceed any further, we need to ensure that if we have __Bash__ installed:

{% codeblock lang:sh %}
$ bash --version
{% endcodeblock %}

If you already have __Bash__ installed , you should see something similar to the following on the command output:

<pre>
GNU bash, version 4.2.42(0)-release (i386-portbld-freebsd9.1)
Copyright (C) 2011 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later &lt;http://gnu.org/licenses/gpl.html&gt;

This is free software; you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
</pre>

If you don't have __Bash__ installed, you can install it from [Ports](http://www.freebsd.org/ports/) on __FreeBSD__ easily:

{% codeblock lang:sh %}
$ cd /usr/ports/shells/bash
$ make config-recursive
$ make install clean
{% endcodeblock %}

**2.** Create or replace both __~/.bashrc__ and __~/.dir_colors__ files with the following content, for both __babaei__ and __root__ users:

{% codeblock ~/.bashrc lang:sh %}
# /etc/bash/bashrc
#
# This file is sourced by all *interactive* bash shells on startup,
# including some apparently interactive shells such as scp and rcp
# that can't tolerate any output.  So make sure this doesn't display
# anything or bad things will happen !


# Test for an interactive shell.  There is no need to set anything
# past this point for scp and rcp, and it's important to refrain from
# outputting anything in those cases.

if [[ $- != *i* ]] ; then
	# Shell is non-interactive.  Be done now!
	return
fi

# Bash won't get SIGWINCH if another process is in the foreground.
# Enable checkwinsize so that bash will check the terminal size when
# it regains control.  #65623
# http://cnswww.cns.cwru.edu/~chet/bash/FAQ (E11)
shopt -s checkwinsize

# Enable history appending instead of overwriting.  #139609
shopt -s histappend

# Change the window title of X terminals 
case ${TERM} in
	xterm*|rxvt*|Eterm|aterm|kterm|gnome*|interix)
		PROMPT_COMMAND='echo -ne "\033]0;${USER}@${HOSTNAME%%.*}:${PWD/$HOME/~}\007"'
		;;
	screen)
		PROMPT_COMMAND='echo -ne "\033_${USER}@${HOSTNAME%%.*}:${PWD/$HOME/~}\033\\"'
		;;
esac

use_color=false

# Set colorful PS1 only on colorful terminals.
# dircolors --print-database uses its own built-in database
# instead of using /etc/DIR_COLORS.  Try to use the external file
# first to take advantage of user additions.  Use internal bash
# globbing instead of external grep binary.
safe_term=${TERM//[^[:alnum:]]/?}   # sanitize TERM
match_lhs=""
[[ -f ~/.dir_colors   ]] && match_lhs="${match_lhs}$(<~/.dir_colors)"
[[ -f /etc/DIR_COLORS ]] && match_lhs="${match_lhs}$(</etc/DIR_COLORS)"
[[ -z ${match_lhs}    ]] \
	&& type -P dircolors >/dev/null \
	&& match_lhs=$(dircolors --print-database)
[[ $'\n'${match_lhs} == *$'\n'"TERM "${safe_term}* ]] && use_color=true

if ${use_color} ; then
	# Enable colors for ls, etc.  Prefer ~/.dir_colors #64489
	if type -P dircolors >/dev/null ; then
		if [[ -f ~/.dir_colors ]] ; then
			eval $(dircolors -b ~/.dir_colors)
		elif [[ -f /etc/DIR_COLORS ]] ; then
			eval $(dircolors -b /etc/DIR_COLORS)
		fi
	fi

	if [[ ${EUID} == 0 ]] ; then
		PS1='\[\033[01;31m\]\h\[\033[01;34m\] \W \$\[\033[00m\] '
	else
		PS1='\[\033[01;32m\]\u@\h\[\033[01;34m\] \w \$\[\033[00m\] '
	fi

	CLICOLOR="YES";    export CLICOLOR
	LSCOLORS="ExGxFxdxCxDxDxhbadExEx";    export LSCOLORS
	#alias ls='ls --color=auto'
	#alias grep='grep --colour=auto'
else
	if [[ ${EUID} == 0 ]] ; then
		# show root@ when we don't have colors
		PS1='\u@\h \W \$ '
	else
		PS1='\u@\h \w \$ '
	fi
fi

# Try to keep environment pollution down, EPA loves us.
unset use_color safe_term match_lhs
{% endcodeblock %}

{% codeblock ~/.dir_colors lang:sh %}
########
# Configuration file for dircolors, a utility to help you set the
# LS_COLORS environment variable used by GNU ls with the --color option.
#
# You can copy this file to .dir_colors in your $HOME directory to override
# the system defaults.

# Below, there should be one TERM entry for each termtype that is colorizable
TERM ansi
TERM color-xterm
TERM con132x25
TERM con132x30
TERM con132x43
TERM con132x60
TERM con80x25
TERM con80x28
TERM con80x30
TERM con80x43
TERM con80x50
TERM con80x60
TERM cons25
TERM console
TERM cygwin
TERM dtterm
TERM Eterm
TERM gnome
TERM konsole
TERM kterm
TERM linux
TERM linux-c
TERM mach-color
TERM putty
TERM rxvt
TERM rxvt-cygwin
TERM rxvt-cygwin-native
TERM rxvt-unicode
TERM screen
TERM screen-bce
TERM screen-w
TERM screen.linux
TERM vt100
TERM xterm
TERM xterm-256color
TERM xterm-color
TERM xterm-debian

# Below are the color init strings for the basic file types. A color init
# string consists of one or more of the following numeric codes:
# Attribute codes:
# 00=none 01=bold 04=underscore 05=blink 07=reverse 08=concealed
# Text color codes:
# 30=black 31=red 32=green 33=yellow 34=blue 35=magenta 36=cyan 37=white
# Background color codes:
# 40=black 41=red 42=green 43=yellow 44=blue 45=magenta 46=cyan 47=white
NORMAL 00           # global default, although everything should be something.
FILE 00             # normal file
DIR 01;34           # directory
LINK 01;36          # symbolic link.  (If you set this to 'target' instead of a
                    # numerical value, the color will match the file pointed to)
FIFO 40;33          # pipe
SOCK 01;35          # socket
DOOR 01;35          # door
BLK 40;33;01        # block device driver
CHR 40;33;01        # character device driver
ORPHAN 01;05;37;41  # orphaned syminks
MISSING 01;05;37;41 # ... and the files they point to

# This is for files with execute permission:
EXEC 01;32

# List any file extensions like '.gz' or '.tar' that you would like ls
# to colorize below. Put the extension, a space, and the color init string.
# (and any comments you want to add after a '#')

.cmd 01;32 # executables (bright green)
.exe 01;32
.com 01;32
.btm 01;32
.bat 01;32
.sh  01;32
.csh 01;32

.tar 01;31 # archives / compressed (bright red)
.tgz 01;31
.arj 01;31
.taz 01;31
.lzh 01;31
.zip 01;31
.z   01;31
.Z   01;31
.gz  01;31
.bz2 01;31
.bz  01;31
.tbz2 01;31
.tz  01;31
.deb 01;31
.rpm 01;31
.rar 01;31		# app-arch/rar
.ace 01;31		# app-arch/unace
.zoo 01;31		# app-arch/zoo
.cpio 01;31		# app-arch/cpio
.7z  01;31		# app-arch/p7zip
.rz  01;31		# app-arch/rzip

.jpg 01;35 # image formats
.jpeg 01;35
.gif 01;35
.bmp 01;35
.ppm 01;35
.tga 01;35
.xbm 01;35
.xpm 01;35
.tif 01;35
.tiff 01;35
.png 01;35
.mng 01;35
.xcf 01;35
.pcx 01;35
.mpg 01;35
.mpeg 01;35
.m2v 01;35  # MPEG-2 Video only
.avi 01;35
.mkv 01;35  # Matroska (http://matroska.org/)
.ogm 01;35  # Ogg Media File
.mp4 01;35  # "Offical" container for MPEG-4
.m4v 01;35  # MPEG-4 Video only
.mp4v 01;35 # MPEG-4 Video only
.mov 01;35  # Quicktime (http://developer.apple.com/qa/qtw/qtw99.html)
.qt 01;35   # Quicktime (http://developer.apple.com/qa/qtw/qtw99.html)
.wmv 01;35  # Windows Media Video
.asf 01;35  # Advanced Systems Format (contains Windows Media Video)
.rm 01;35   # Real Media
.rmvb 01;35 # Real Media Variable Bitrate
.flc 01;35  # AutoDesk Animator
.fli 01;35  # AutoDesk Animator
.gl 01;35
.dl 01;35

.pdf 00;32 # Document files
.ps 00;32
.txt 00;32
.patch 00;32
.diff 00;32
.log 00;32
.tex 00;32
.doc 00;32

.mp3 00;36 # Audio files
.wav 00;36
.mid 00;36
.midi 00;36
.au 00;36
.ogg 00;36
.flac 00;36
.aac 00;36
{% endcodeblock %}

**Note:** I've borrowed these files from a __Funtoo__ installation with a little modification.

**3.** Finally, you need to make __Bash__ the defualt shell on your system for both __babaei__ and __root__ users:

{% codeblock lang:sh %}
$ chsh -s /usr/local/bin/bash babaei
$ chsh -s /usr/local/bin/bash root
{% endcodeblock %}

**Note:** On __*BSD__ operating systems usually the path to __bash__ executable is __/usr/local/bin/bash__, due to not being part of the base system. Anyway, it may be different on different __Linux__ distributions, e.g., __/usr/bin/bash__ or __/bin/bash__.

**4.** You need to run a new instance of __Bash__ to see the results (e.g. by logging in on a virtual console, opening a new terminal window or tab, or running the command __bash__).


<br/>

### Related Articles ###

[nano, Do not wrap text](/blog/2013/02/17/nano-do-not-wrap-text/)  
[nano, Syntax Highlighting](/blog/2013/02/17/nano-syntax-highlighting/)
