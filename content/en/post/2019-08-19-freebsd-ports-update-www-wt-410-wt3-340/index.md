+++
title = "The long awaited FreeBSD www/wt and www/wt3 ports updates"
slug = "freebsd-ports-update-www-wt-410-wt3-340"
date = 2019-08-19T01:49:00+02:00
tags = [ "C", "C++", "CPP", "FOSS", "FLOSS", "FreeBSD", "FreeBSD Ports", "Ports", "Unix", "Witty", "Wt" ]
+++

For those who don't know, I maintain [various official FreeBSD ports](https://www.freebsd.org/cgi/ports.cgi?query=info%40babaei.net&stype=maintainer&sektion=all) and for almost 18 months [my submitted updates](https://bugs.freebsd.org/bugzilla/show_bug.cgi?id=226160) to [www/wt](https://www.webtoolkit.eu/wt) has been stuck due to lack of a review. Hopefully, tonight it has been committed to the official [FreeBSD Ports](https://www.freebsd.org/ports/) tree and has been divided into two ports:

1. [www/wt](https://svnweb.freebsd.org/ports/head/www/wt/) for following the <code>4.x</code> releases
2. [www/wt3](https://svnweb.freebsd.org/ports/head/www/wt3/) for following the <code>3.x</code> releases

Although [Wt Webtoolkit 4.x](https://web.archive.org/web/20190819001517/https://www.webtoolkit.eu/wt/news/2017/09/19/wt_4_0_0_is_here_) is a significant update which brings in more modern C++ and performance improvements (read more about the changes between releases [on their archive](https://web.archive.org/web/20190819001524/https://www.webtoolkit.eu/wt/news/all)), I haven't migrated any project to the <code>4.x</code> release yet. I guess the <code>3.x</code> releases will live on for the time being and any project using them should be fine for some time.

<!--more-->
