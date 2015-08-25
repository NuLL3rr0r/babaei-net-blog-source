title: 'Happy 24th Birthday: A Linux Kernel Panic At Hometown'
date: 2015-08-25 21:00:00
tags:
- Crash
- FLOSS
- FreeBSD
- GNU
- Kernel Panic
- Linux
- Unix
---

[{% img post-image /blog/2015/08/25/happy-24th-birthday-a-linux-kernel-panic-at-hometown/2015-08-25-happy-24th-birthday-a-linux-kernel-panic-at-hometown__001.jpg 540 480 'A Linux kernel panic on tram 7B at its hometown, Helsinki (Click to enlarge)' 'A Linux kernel panic on tram 7B at its hometown, Helsinki (Click to enlarge)' %}](/blog/2015/08/25/happy-24th-birthday-a-linux-kernel-panic-at-hometown/2015-08-25-happy-24th-birthday-a-linux-kernel-panic-at-hometown__001_hq.jpg)
<span class="post-image-title">A Linux kernel panic on tram 7B at its hometown, Helsinki (Click to enlarge)</span>

Undeniably, flaming has been around since the dawn of the Internet age. And even worse, it has been on the rise ever since. Gazillions of flame wars on websites such as [Slashdot](http://slashdot.org) or [Reddit](https://www.reddit.com/) surely is enough proof, the greatest of which is the perennial debates between users of competing operating systems. 

No doubt I'm a [FLOSS](https://en.wikipedia.org/wiki/Free_and_open-source_software) enthusiast and advocate who considers free/libre/azad software superior to the proprietary ones, by all means possible. But like all software, the FLOSS ones have some shortcomings, too. So, the point is no one-hundred percent reliable software exists on this planet which means open source software may also suffer from bugs or security flaws as proprietary software do.

Today is [Linux kernel](https://www.kernel.org/) birthday and many FLOSS enthusiast and advocates around the globe are going to celebrate it. I'm a diehard [FreeBSD](https://www.freebsd.org/) fan, but it won't stop me from celebrating Linux birthday. In fact, I still use [GNU](https://www.gnu.org/home.en.html)/Linux for building native C/C++ libraries using [Android NDK](https://developer.android.com/tools/sdk/ndk/) on a [Slackware](http://www.slackware.com/) machine. In addition to that, I used to be a heavy [Funtoo](http://www.funtoo.org/) / [Gentoo](https://www.gentoo.org/) user. The thing is, I appreciate the tools I use, no matter what. So, I'm going to celebrate Linux birthday by telling you a story. A story that made an unforgettable trip even more memorable. Here's the story of a GNU/Linux system in production which crashed in its hometown, Helsinki, Finland.

<!-- more -->

Last year I was in Helsinki from November 17 through November 21 for the [Slush conference](http://www.slush.org/). At the end of the first day of the conference on November 18, back from [Messukeskus, Expo and Convention Center Helsinki](http://www.messukeskus.com/en/) located in the district of [Pasila](https://en.wikipedia.org/wiki/Pasila) -- where the conference was held -- I took the tram back to my hotel at [Katajanokka](https://en.wikipedia.org/wiki/Katajanokka) district. All those trams in Helsinki equipped with an onboard infotainment display behind the driver's cabin which was showing weather and other stuffs that I cannot recall right now (left side of the post image). Immediately, upon boarding the tram [a nice crash on the tram's onboard infotainment display](https://twitter.com/NuLL3rr0r/status/534796458546196480/photo/1) caught my eyes (the post image, right). At first I was doubtful about it. "A kernel panic?" I asked myself. I've never seen such a thing in a public place before (maybe I wasn't lucky enough). So, I approached the screen to verify what I was seeing was for real. Yep, confirmed that was a kernel panic! Inside the picture you can find the kernel panic with its actual stack trace.

At the time, in addition to [tweeting about it](https://twitter.com/NuLL3rr0r/status/534796458546196480/photo/1) I sent the pictures to [Iranian blogger Jadi](https://twitter.com/jadi) who [writes about both freedom of speech and software](https://twitter.com/radiojadi). That's because at that moment the first thing came to my mind was reading [a post from him about a Linux crash on Turkish Airlines a few days back which was in charge for seat-back screens](http://jadi.net/2014/11/linux-crash/) (The actual image is in the post itself). He did publish [the photos I've taken in another post](http://jadi.net/2014/11/linux-crash-2/) later.

But, it's too soon to label FLOSS operating systems as unreliable. I recall reading his [first post in the series a few months back which shows a familiar Microsoft Windows blue screen of death at Stockholm Airport](http://jadi.net/2014/08/stockholm-windows-crash/) (which one? it's not mentioned there). Actually, I've never seen a Windows crash at a public place for myself, except a million year ago when I was still a teenager, I saw a Windows XP desktop on an ATM device. The application was crashed but not the OS itself.

Regarding Mac OS X, I doubt anyone in the industry builds a business on OS X. When I mean production or industry, I mean: [launching a Space Shuttle](http://www.linuxjournal.com/article/2186), [powering International Space Station or the a humanoid robot in space](http://www.extremetech.com/extreme/155392-international-space-station-switches-from-windows-to-linux-for-improved-reliability), [rendering The Matrix](https://www.freebsd.org/news/press-rel-1.html) or [Titanic](http://www.linuxjournal.com/article/2494). Not to mention Apple's echo system is even more restricted and worse than Microsoft. So, when there's no Apple system in service, therefore, there is no crash.

Aside from the choice of operating system, consider [a computer that controls air traffic](http://www.reuters.com/article/2014/05/12/us-airtraffic-bug-exclusive-idUSBREA4B02320140512). It's quite peculiar how we rely too much on computers, either it's a trivial or serious business. Some may argue the fault is ours and it's the programmer or some other company to blame instead of the computers themselves. In my estimation, in either case it doesn't matter since a kernel panic is a kernel panic or a design flaw is a design flaw. They all lead to failure one way or another and when you are screwed, in the end the results are the same. But, I'm sure of one thing: _two many eyeballs on the code are better than few_. That's one reason among many why I prefer FLOSS software over the proprietary ones. So, happy birthday Linux.

I would like to know how much you rely on your operating system of choice? I hoped I didn't ignite another flame war. :-)

