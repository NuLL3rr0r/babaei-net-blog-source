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

Since most of us can't afford to keep our servers in an underground bunker, the least little thing that could have been done in order to keep their threat exposure at rock-bottom is protecting them by running a combination of a firewall and an intrusion prevention system or IPS (a.k.a intrusion detection and prevention systems or IDPS). Surely that alone proved insufficient and other security measures and best practices should be considered too.

This blog post covers setting up a basic secure and stateful [IPFW](https://www.freebsd.org/doc/handbook/firewalls-ipfw.html) firewall on [FreeBSD](https://www.freebsd.org/) along with [Sshguard](http://www.sshguard.net/) by [iXsystems Inc](https://www.ixsystems.com/) as intrusion prevention system.

<!-- more -->

<br />

### IPFW ###

Traditionally FreeBSD has three firewalls built into its base system: [PF](http://www.openbsd.org/faq/pf/), IPFW, and [IPFILTER](www.phildev.net/ipf/), also known as IPF. In my estimation, IPFW would be the natural choice on FreeBSD if we set aside the pros and cons of each. In contrast to the other two, IPFW was originally written for FreeBSD and its main development platform - if we do not consider the [DragonFly](https://www.dragonflybsd.org/)'s fork - is still FreeBSD. This means the latest features are always available on FreeBSD. On the contrary, this is not true for PF or IPF on FreeBSD. So, that's why I chose to go with IPFW.

Before I begin I have to mention that this guide was written for <code>FreeBSD 10.1-RELEASE</code> and it may not work with older releases. I cannot verify this since all my servers are running <code>FreeBSD 10.1-RELEASE</code> at the time of writing.

OK, in order to configure our firewall we have to modify <code>/etc/rc.conf</code>. First, you shoud make sure no other firewall is running by looking for <code>pf_enable="YES"</code> or <code>ipfilter_enable="YES"</code> inside <code>/etc/rc.conf</code>. If you have any of them you shoud disable them by either setting their value to <code>"NO"</code> or remvoing them completely. After that we can enable and configure our firewall inside <code>/etc/rc.conf</code>:

{% codeblock /etc/rc.conf lang:sh %}
firewall_enable="YES"
firewall_quiet="YES"
firewall_type="workstation"
firewall_myservices="11011 domain http https imap imaps pop3 pop3s smtp smtps"
firewall_allowservices="any"
firewall_logdeny="YES"
{% endcodeblock %}

I'm not going verbose except for <code>firewall_myservices</code> which requires explanation. If you would like to play with these options and you are on a SSH sesssion, please be wary of the fact that even the slightest change in the above setup may drop the connection, therefore, effectively lock you out of the server. For example <code>firewall_quiet="NO"</code> alone is enough for such a scenario. So, please take a look at [FreeBSD Handbook](https://www.freebsd.org/doc/handbook/firewalls-ipfw.html) or [/etc/rc.conf man page](https://www.freebsd.org/cgi/man.cgi?query=rc.conf&sektion=5) before any modification in case you are not sure what you're doing. I also highly recommend [this great article by Digital Ocean](https://www.digitalocean.com/community/tutorials/recommended-steps-for-new-freebsd-10-1-servers) which did a good job of summing it all up in a novice-friendly way.

By default the above setup blocks all inbound connections on all ports for both TCP and UDP. <code>firewall_myservices</code> is a whiht-space separated list of TCP ports. So, you have to address a specific port here if you have an obligation to allow inbound TCP connection for that port. You must have noticed by now, instead of specifying port numbers I mentioned them by name in the <code>firewall_myservices</code> list. It's possible to either use port numbers or address a port by name if a known or standard service uses that specific port.

For example, let's say you are running <code>dns/bind910</code> on your server and you know it's listening for dns quries on port 53. You can search for the port name which FreeBSD recognizes by looking up the port number inside <code>/etc/services</code>.

{% codeblock lang:sh %}
$ cat /etc/services | grep -w "53"
domain		 53/tcp	   #Domain Name Server
domain		 53/udp	   #Domain Name Server
{% endcodeblock %}

In the above example the port name for both TCP and UDP is <code>domain</code>. Now, let's consider another example: You are running a mail server and instead of specifying the port name or protocol you would like to directly use port numbers in <code>firewall_myservices</code> list. So, we do the exact opposite for our outgoing server:

{% codeblock lang:sh %}
$ cat /etc/services | grep -w "smtp"
smtp		 25/tcp	   mail		#Simple Mail Transfer
smtp		 25/udp	   mail		#Simple Mail Transfer
smtps		465/tcp	   #smtp protocol over TLS/SSL (was ssmtp)
smtps		465/udp	   #smtp protocol over TLS/SSL (was ssmtp)
{% endcodeblock %}

As you can see the equal port numbers are 25 and 465. Depending on how you did configured your mail server (e.g. 25 for PLAIN and STARTTLS, 465 for TLS/SSL) you can pick one or both 25 and 465.

As you may have noticed already, I did mixed numbers and names in the <code>firewall_myservices</code> list. That's becuase I used a non-defualt port instead of 22 for <code>ssh</code>. It is perfectly fine to mix numbers and names in the list.

Now it's time to start the firewall by running the following command:

{% codeblock lang:sh %}
$ service ipfw start
{% endcodeblock %}

After starting the firewall you can always check the current rules by using the following command:

{% codeblock lang:sh %}
$ ipfw list
{% endcodeblock %}

Now, you may ask there is one little issue with configuring IPFW through <code>firewall_myservices</code>. This list is TCP only and there is no way to configure UDP ports through <code>/etc/rc.conf</code>. OK, we address that by extending the configuration using our own script without touching any files from base system which is the proper way to do so. If you take a look at <code>/etc/rc.firewall</code> script, you'll find out how FreeBSD applies <code>firewall_*</code> configuration. So, we adopt the same approach by writing our own script. Therefore, in the first step, we create and put the following script inside <code>/usr/local/etc/</code>:

{% codeblock /usr/local/etc/rc.firewall lang:sh %}
#!/bin/sh

#  (The MIT License)
#
#  Copyright (c) 2013 Mohammad S. Babaei
#
#  Permission is hereby granted, free of charge, to any person obtaining a copy
#  of this software and associated documentation files (the "Software"), to deal
#  in the Software without restriction, including without limitation the rights
#  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#  copies of the Software, and to permit persons to whom the Software is
#  furnished to do so, subject to the following conditions:
#
#  The above copyright notice and this permission notice shall be included in
#  all copies or substantial portions of the Software.
#
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
#  THE SOFTWARE.


. /etc/rc.subr

load_rc_config firewall

fw_add="/sbin/ipfw -q add"

case ${1} in
quietstart)
        for i in ${firewall_allowservices} ; 
        do
            for j in ${firewall_myservices_tcp} ;
            do
                ${fw_add} pass tcp from ${i} to me ${j}
            done
        done

        for i in ${firewall_allowservices} ;
        do
            for j in ${firewall_myservices_udp} ;
            do
                ${fw_add} pass udp from ${i} to me ${j}
            done
        done
    ;;
quietstop)
    ;;
*)
    echo "Warning: unknown parameter '${1}'"
    ;;
esac
{% endcodeblock %}

Then we have to fix the permissions to make it executable by anyone:

{% codeblock lang:sh %}
chmod u-w,ugo+x /usr/local/etc/rc.d/firewall.local
{% endcodeblock %}

Finally we have to enable our own configuration for TCP and UDP ports inside <code>/etc/rc.conf</code>:

{% codeblock /etc/rc.conf lang:sh %}
firewall_enable="YES"
firewall_quiet="YES"
firewall_type="workstation"
#firewall_myservices="11011 domain http https imap imaps pop3 pop3s smtp smtps"
firewall_allowservices="any"
firewall_logdeny="YES"
firewall_coscripts="/usr/local/etc/rc.d/firewall.local"
firewall_myservices_tcp="11011 domain http https imap imaps pop3 pop3s smtp smtps"
firewall_myservices_udp="domain"
{% endcodeblock %}

Then it's time to restart IPFW firewall and check whether our script did its job properlly or not:

{% codeblock lang:sh %}
$ service ipfw restart
$ ipfw list
{% endcodeblock %}

Note that we leave alone <code>firewall_myservices</code> despite the fact that it's still functional. For the sake of clarity we choose to use our own <code>firewall_myservices_tcp</code> and avoid using or mixing it with <code>firewall_myservices</code>.


Last but not least, a recommended best practice is putting a limit on the logging of denials per IP address. This will prevent a single, persistent user to fill up your logs. To do so we should adjust <code>net.inet.ip.fw.verbose_limit</code> by issuing the following command:

{% codeblock lang:sh %}
$ sudo sysctl net.inet.ip.fw.verbose_limit=5
{% endcodeblock %}

This adjusts the number of logs per IP to 5. In order to make that permanent for future reboots of your server we should add it to <code>/etc/sysctl.conf</code>:

{% codeblock /etc/sysctl.conf lang:sh %}
net.inet.ip.fw.verbose_limit=5
{% endcodeblock %}


### Sshguard ###

Currently, [FreeBSD Ports](https://www.freebsd.org/ports/) provides five variants of Sshguard:

* <code>security/sshguard</code> :  Protects your host from brute force attacks against ssh and other services.
* <code>security/sshguard-ipfilter</code> :  Utilizes IPF to protect from brute force attacks against ssh and other services
* <code>security/sshguard-ipfw</code> :  Utilizes IPFW to protect your host from brute force attacks against ssh and other services
* <code>security/sshguard-null</code> :  Do-nothing backend for applying detection but not prevention.
* <code>security/sshguard-pf</code> :  Utilizes PF to protect from brute force attacks against ssh and other services.

So, we choose <code>security/sshguard-ipfw</code> since we just setup up an IPFW firewall. To install Sshguard for IPFW from Ports collection:

{% codeblock /etc/sysctl.conf lang:sh %}
$ cd /usr/ports/security/sshguard-ipfw/
$ make config-recursive
$ make install clean
{% endcodeblock %}

Or if you are using [pkgng](https://www.freebsd.org/doc/handbook/pkgng-intro.html) instead of Ports:

{% codeblock /etc/sysctl.conf lang:sh %}
$ pkg install security/sshguard-ipfw
{% endcodeblock %}

To enable Sshguard we have to modify our <code>/etc/r.conf</code>:

{% codeblock /etc/rc.conf lang:sh %}
sshguard_enable="YES"
sshguard_safety_thresh="40"
sshguard_pardon_min_interval="420"
sshguard_prescribe_interval="1200"
sshguard_watch_logs="/var/log/auth.log:/var/log/maillog"
sshguard_blacklist="40:/var/db/sshguard/blacklist.db"
sshguard_whitelistfile="/usr/local/etc/sshguard.whitelist"
{% endcodeblock %}

* <code>sshguard_enable</code> [BOOLEAN, DEFAULT: "NO"] :  
* <code>sshguard_pidfile</code> [STRING, DEFAULT: "/var/run/sshguard.pid"] :  
* <code>sshguard_watch_logs</code> [STRING, DEFAULT: "/var/log/auth.log:/var/log/maillog"] :  
* <code>sshguard_blacklist</code> [STRING, DEFAULT: "40:/var/db/sshguard/blacklist.db"] :  
* <code>sshguard_safety_thresh</code> [INTEGER, DEFAULT: "40"] :  
* <code>sshguard_pardon_min_interval</code> [INTEGER, DEFAULT: "420"] :  
* <code>sshguard_prescribe_interval</code> [INTEGER, DEFAULT: "1200"] :  
* <code>sshguard_whitelistfile</code> [STRING, DEFAULT: "/usr/local/etc/sshguard.whitelist"] :  
* <code>sshguard_flags</code> [STRING] :  


{% codeblock /usr/local/etc/rc.d/firewall.local lang:sh %}
#!/bin/sh

. /etc/rc.subr

load_rc_config firewall

fw_add="/sbin/ipfw -q add"

if [ -z "${firewall_myservices_rules_id_start}" ];
then
    firewall_myservices_rules_id_start=56000
fi

if [ -z "${firewall_myservices_rules_id_step}" ];
then
    firewall_myservices_rules_id_step=10
fi

case ${1} in
quietstart)
        rule_id=${firewall_myservices_rules_id_start}

        for i in ${firewall_allowservices} ;
        do
            for j in ${firewall_myservices_tcp} ;
            do
                ${fw_add} ${rule_id} pass tcp from ${i} to me ${j}
                rule_id=`expr $rule_id + ${firewall_myservices_rules_id_step}`
            done
        done

        for i in ${firewall_allowservices} ;
        do
            for j in ${firewall_myservices_udp} ;
            do
                ${fw_add} ${rule_id} pass udp from ${i} to me ${j}
                rule_id=`expr $rule_id + ${firewall_myservices_rules_id_step}`
            done
        done
    ;;
quietstop)
    ;;
*)
    echo "Warning: unknown parameter '${1}'"
    ;;
esac
{% endcodeblock %}


{% codeblock /etc/rc.conf lang:sh %}
firewall_enable="YES"
firewall_quiet="YES"
firewall_type="workstation"
firewall_allowservices="any"
firewall_logdeny="YES"
firewall_coscripts="/usr/local/etc/rc.d/firewall.local"
firewall_myservices_rules_id_start="56000"
firewall_myservices_rules_id_step="10"
firewall_myservices_tcp="11011 domain http https imap imaps pop3 pop3s smtp smtps"
firewall_myservices_udp="domain"

sshguard_enable="YES"
sshguard_safety_thresh="40"
sshguard_pardon_min_interval="420"
sshguard_prescribe_interval="1200"
sshguard_watch_logs="/var/log/auth.log:/var/log/maillog"
sshguard_blacklist="40:/var/db/sshguard/blacklist.db"
sshguard_whitelistfile="/usr/local/etc/sshguard.whitelist"
{% endcodeblock %}

### Unban ###



