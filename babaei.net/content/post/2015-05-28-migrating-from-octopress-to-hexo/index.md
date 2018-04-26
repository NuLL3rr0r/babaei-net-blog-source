+++
title = "Migrating From Octopress To Hexo"
slug = "migrating-from-octopress-to-hexo"
date = 2015-05-28T01:44:00+04:30
tags = [ "Hexo", "Octopress" ]
aliases = [ "/blog/2015/05/28/migrating-from-octopress-to-hexo/" ]
+++

Well, I was living a happy life with _[Octopress 2.x](https://github.com/imathis/octopress)_ despite the fact that I didn't do much blogging in the past couple of years. Moreover, in my estimation [Octopress](http://octopress.org/) still should be considered as one of the greatest blogging platforms among [its peers](https://www.staticgen.com/) and I really got nothing against it. But, I see a few shortcomings which made me looking for alternatives (and some of these still affects [the 3.x version of Octopress](https://github.com/octopress/octopress)):

<!--more-->

* Being very slow on page generation specially when I enable UTF-8 encoding for [my other blog in Farsi](http://fa.babaei.net/). Even building and installing _[Ruby/GSL](http://rb-gsl.rubyforge.org/)_ on my FreeBSD machine did not made any difference (I was not able to build it on windows since it relies on GCC). Sorry, I prefer FreeBSD over GNU/Linux.

* There is no easy way of fully running it on FreeBSD without too much hassle. Since I'm a heavy and long time FreeBSD user this is not acceptable for me to use a GNU/Linux, Mac or Windows machine, just for the sake of writing a blog post. As an example, due to [an issue with one of its Ruby dependencies](https://github.com/guard/listen/issues/220) which is not supporting FreeBSD officially, I was not able to run <code>rake watch</code>.

* Lack of [a promising WYSIWYG markdown editor as the one that _Hexo_ have](https://github.com/jaredly/hexo-admin). Although it's not working on [Hexo 3.x](http://hexo.io/), yet.

* Very slow development pace. Just to name a few examples I have to mention that it's been almost a month since [the stable 3.x release of Octopress](https://github.com/octopress/octopress/releases) but still there's no documentation available on its official home page. And of course [a 3 year gap between 2.x and 3.x releases](https://github.com/imathis/octopress/releases). Another one is, I've been waiting for 2.1 release of Octopress for ages and it never came.

There are so many good things about Hexo. But, above them all [the easy Octopress migration with zero effort](http://hexo.io/docs/migration.html#Octopress). It's just a matter of moving all your post files from Octopress <code>source/_posts</code> directory to Hexo <code>source/_posts</code> directory. And hell yeah Hexo generator is blazingly fast.

__Update (2016/01/11)__: Great news! I just noticed [Jared Forsyth](http://jaredly.github.io/) ([@jaredforsyth](http://twitter.com/jaredforsyth)) has released v1.x of [hexo-admin](https://github.com/jaredly/hexo-admin) a few months ago which works on 3.x branch of Hexo. I'm writing this update from hexo-admin panel using [v1.1.1](https://github.com/jaredly/hexo-admin/releases) of the plug-in which works flawlessly. Awesome work, Jared.
