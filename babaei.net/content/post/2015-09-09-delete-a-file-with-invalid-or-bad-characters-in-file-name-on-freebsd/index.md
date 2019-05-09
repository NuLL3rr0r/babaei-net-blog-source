+++
title = "Delete a File With Invalid or Bad Characters in File Name on FreeBSD"
slug = "delete-a-file-with-invalid-or-bad-characters-in-file-name-on-freebsd"
date = 2015-09-09T12:54:08+04:30
tags = [ "FLOSS", "FOSS", "FreeBSD", "Unix" ]
aliases = [ "/blog/2015/09/09/delete-a-file-with-invalid-or-bad-characters-in-file-name-on-freebsd/" ]
+++

There once was a time when I did the following inside my home directory:

```
$ wget "some-url" -O "output-file.mp4"
```

I clearly remember copying the output file name from a web page. Unfortunately, the copied text has a new line at the beginning of it and I didn't notice that. That's because the <code>newline</code> or <code>carriage return</code> characters are control characters and have no visual representation. Anyway, when I listed files inside my home directory I noticed a strange file name on my list:

```
$ ls
?output-file.mp4
```

<!--more-->

I tried the following to remove the file without any success:

```
$ rm "?output-file.mp4"
rm: ?output-file.mp4: No such file or directory

$ rm \?output-file.mp4
rm: ?output-file.mp4: No such file or directory

$ rm ./?output-file.mp4
rm: ./?output-file.mp4: No such file or directory

$ rm *.mp4
rm: *.mp4: No such file or directory
```

When I tried auto-completion by pressing <code>Tab</code> key a few times on <code>csh</code> it showed the file name as:

```
output-file.mp4
```

On the other hand <code>bash</code> showed the following name:

```
    ^Joutput-file.mp4
```

I tried the above <code>rm</code> command with <code>^J</code> instead of <code>?</code> with no luck.

In the next step, I tried:

```
$ man rm
```

Then I came across <code>-i</code> flag inside <code>rm</code> man page:

{{< blockquote author="FreeBSD Man Pages" link="http://www.freebsd.org/cgi/man.cgi?query=rm&apropos=0&sektion=0&manpath=FreeBSD+10.2-RELEASE&format=html" title="rm" >}}
-i      Request confirmation before attempting to remove each file,
        regardless of the file's permissions, or whether or not the stan-
        dard input device is a terminal. The -i option overrides any
        previous -f options.
{{< /blockquote >}}

So, I gave <code>rm -i</code> a go after changing to my home directory:

```
$ cd ~
$ rm -i *
remove
output-file.mp4 ? y
remove some-other-file ? ^C
```

As it can be seen in the output, <code>rm</code> now considers the file and even prints the newline character in the output. So I entered <code>y</code> and it deleted the file with bad name. For, the other files on the list I simply pressed <code>Ctrl+C</code> to exit the list completely (Note: if Ctrl+C won't work for you, try <code>Ctrl+Z</code> or <code>Ctrl+D</code>).

I also found an interesting <code>--</code> flag through my journey inside <code>rm</code> man page which may come handy one day:

{{< blockquote author="FreeBSD Man Pages" link="http://www.freebsd.org/cgi/man.cgi?query=rm&apropos=0&sektion=0&manpath=FreeBSD+10.2-RELEASE&format=html" title="rm" >}}
The rm command uses getopt(3) to parse its arguments, which allows to
accept the `--' option which will cause it to stop processing flag
options at that point. This will allow the removal of file names that
begin with a dash (`-'). For example:

rm -- -filename

The same behavior can be obtained by using an absolute or relative path
reference. For example:

rm /home/user/-filename
rm ./-filename
{{< /blockquote >}}
