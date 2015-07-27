title: 'FreeBSD: Block Brute-force Attacks Using Sshguard and IPFW Firewall'
date: 2015-07-28 00:23:00
tags:
- Brute-force
- Firewall
- FreeBSD
- GNU
- IPFW
- Linux
- Security
- SSH
- Unix
- Vulnerability
---

There is an old saying that the only safe computer is one that's disconnected from the network, turned off, and locked in an underground bunker—and even then you can't be sure!

Since most of us can't afford to keep our servers in an underground bunker, the least little thing that could have been done in order to keep their threat exposure at rock-bottom is protecting them by running a firewall and an intrusion prevention system or IPS (a.k.a intrusion detection and prevention systems or IDPS). Surely that alone proved insufficient and other security measures and best practices should be considered too.

This blog post covers setting up a basic secure and stateful [IPFW](https://www.freebsd.org/doc/handbook/firewalls-ipfw.html) firewall on [FreeBSD](https://www.freebsd.org/) along with [Sshguard](http://www.sshguard.net/) as intrusion prevention system.

<!-- more -->

<br />

### IPFW ###

Traditionally FreeBSD has three firewalls built into its base system: [PF](http://www.openbsd.org/faq/pf/), IPFW, and [IPFILTER](www.phildev.net/ipf/), also known as IPF. In my estimation, IPFW would be the natural choice on FreeBSD if we set aside the pros and cons of each. In contrast to the other two, IPFW was originally written for FreeBSD and its main development platform - if we do not consider the [DragonFly](https://www.dragonflybsd.org/)'s fork - is still FreeBSD. This means the latest features are always available on FreeBSD. On the contrary, this is not true for PF or IPF on FreeBSD. So, that's why I chose to go with IPFW.

Before I begin I have to mention that this guide was written for <code>FreeBSD 10.1-RELEASE</code> and it may not work with older releases. I cannot verify this since all my servers are running FreeBSD 10.1 at the time of writing. 

OK, in order to configure our firewall we have to modify <code>/etc/rc.conf</code>. First, you shoud make sure no other firewall is running. Look if you have <code>pf_enable="YES"</code> or <code>ipfilter_enable="YES"</code> inside <code>/etc/rc.conf</code>. If you have any of them you shoud disable them by either setting their value to <code>"NO"</code> or remvoing them completely.

{% codeblock /etc/rc.conf lang:sh %}
firewall_enable="YES"
firewall_quiet="YES"
firewall_type="workstation"
firewall_myservices="domain http https imap imaps pop3 pop3s smtp smtps ssh"
firewall_allowservices="any"
firewall_logdeny="YES"
{% endcodeblock %}

I'm not going verbose except for <code>firewall_myservices</code> which requires explanation. If you would like to play with these options and you are on a SSH sesssion please be wary of the fact that even the slighest change in the above setup may effectively lock you out of the server. For example <code>firewall_quiet="NO"</code> is enough for such a scenario. So, please take a look at [FreeBSD Handbook](https://www.freebsd.org/doc/handbook/firewalls-ipfw.html) or [/etc/rc.conf man page](https://www.freebsd.org/cgi/man.cgi?query=rc.conf&sektion=5) before any modification in case you are not sure what you're doing. I also highly recommend [this great article by Digital Ocean](https://www.digitalocean.com/community/tutorials/recommended-steps-for-new-freebsd-10-1-servers) which did a good job of summing it all up. 

By default the above setup blocks all inbound connections on all ports for both TCP and UDP. <code>firewall_myservices</code> is a whiht-space separated list of ports. So, you have to address a specific port here if you want to allow inbound connection for that port. As you have noticed by now, instead of specifying port numbers I mentioned them by name in the <code>firewall_myservices</code> list. It's possible to either use port number or if a known or standard service uses that port address it by name instead.


