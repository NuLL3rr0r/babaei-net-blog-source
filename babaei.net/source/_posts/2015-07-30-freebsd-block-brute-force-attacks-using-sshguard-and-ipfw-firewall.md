title: 'FreeBSD: Block Brute-force Attacks Using Sshguard and IPFW Firewall'
date: 2015-07-30 19:56:00
tags:
- Brute-force
- Firewall
- FreeBSD
- GNU
- IPF
- IPFILTER
- IPFW
- Linux
- PF
- Security
- SSH
- Unix
- Vulnerability
---

There is an old saying that the only safe computer is one that's disconnected from the network, turned off, and locked in an underground bunker—and even then you can't be sure!

Since most of us can't afford to keep our servers in an underground bunker, the least little thing that could have been done in order to keep their threat exposure at rock-bottom is protecting them by running a combination of a firewall and an intrusion prevention system or IPS (a.k.a intrusion detection and prevention systems or IDPS). Surely, that alone proved insufficient and other security measures and best practices should also be considered.

This blog post covers setting up a basic secure and stateful [IPFW](https://www.freebsd.org/doc/handbook/firewalls-ipfw.html) firewall on [FreeBSD](https://www.freebsd.org/) along with [Sshguard](http://www.sshguard.net/) by [iXsystems Inc](https://www.ixsystems.com/) as intrusion prevention system.

<!-- more -->

<br />

[IPFW](#IPFW)  
[Sshguard](#Sshguard)  
[Unban](#Unban)  
[Sshguard Won't Start](#SshguardWontStart)  
[Source Code](#SourceCode)  


<br />
<a name="IPFW"></a>

### IPFW ###

Traditionally FreeBSD has three firewalls built into its base system: [PF](http://www.openbsd.org/faq/pf/), IPFW, and [IPFILTER](www.phildev.net/ipf/), also known as IPF. In my estimation, IPFW would be the natural choice on FreeBSD if we set aside the pros and cons of each. In contrast to the other two, IPFW was originally written for FreeBSD and its main development platform - if we do not count the [DragonFly](https://www.dragonflybsd.org/)'s fork - is still FreeBSD. This means that the latest features are always available on FreeBSD. On the contrary, this is not true for PF or IPF on FreeBSD. So, that's why I chose to go with IPFW.

Before I begin, I have to mention that this guide was written for <code>FreeBSD 10.1-RELEASE</code> and <code>10-STABLE</code>, and it may not work with older releases. I cannot verify this since all my servers and workstations are either running <code>FreeBSD 10.1-RELEASE</code> or <code>10-STABLE</code> at the time of writing. So, you are on your own if you are trying this on an older release.

OK, in order to configure our firewall we have to modify <code>/etc/rc.conf</code>. First, you should make sure no other firewall is running by looking for <code>pf_enable="YES"</code> or <code>ipfilter_enable="YES"</code> inside <code>/etc/rc.conf</code>. If you have any of them, you should disable them by either setting their value to <code>"NO"</code> or removing them completely. After that we can enable and configure our IPFW firewall inside <code>/etc/rc.conf</code>:

{% codeblock /etc/rc.conf lang:sh %}
firewall_enable="YES"
firewall_quiet="YES"
firewall_type="workstation"
firewall_myservices="11011 domain http https imap imaps pop3 pop3s smtp smtps"
firewall_allowservices="any"
firewall_logdeny="YES"
{% endcodeblock %}

I'm not going verbose except for <code>firewall_myservices</code> which requires explanation. If you would like to play with these options and you are on a SSH session, please be wary of the fact that even the slightest change in the above setup may drop the connection, therefore, close the session and effectively lock you out of the server. For example <code>firewall_quiet="NO"</code> alone is enough for such a scenario. So, please take a look at [FreeBSD Handbook](https://www.freebsd.org/doc/handbook/firewalls-ipfw.html) or [/etc/rc.conf man page](https://www.freebsd.org/cgi/man.cgi?query=rc.conf&sektion=5) before any modification in case you are not sure what you're doing. I also highly recommend [this great article by Digital Ocean](https://www.digitalocean.com/community/tutorials/recommended-steps-for-new-freebsd-10-1-servers) which did a good job of summing it all up in a novice-friendly way.

By default the above setup blocks all inbound connections on all ports for both TCP and UDP. <code>firewall_myservices</code> is a white-space separated list of TCP ports. So, you have to address a specific port here if you have an obligation to allow inbound TCP connection for that port. You must have noticed by now, instead of specifying port numbers I mentioned them by name in the <code>firewall_myservices</code> list. It's possible to either use port numbers or address a port by name if a known or standard service uses that specific port.

For example, let's say you are running <code>dns/bind910</code> on your server and you know it's listening for dns queries on port <code>53</code>. You can search for the port name which FreeBSD recognizes by looking up the port number inside <code>/etc/services</code>.

    $ cat /etc/services | grep -w "53"
    domain		 53/tcp	   #Domain Name Server
    domain		 53/udp	   #Domain Name Server

In the above example the port name for both TCP and UDP is <code>domain</code>. Now, let's consider another example: You are running a mail server and instead of specifying the port name or protocol you would like to directly use port numbers in <code>firewall_myservices</code> list. So, we do the exact opposite for our outgoing server:

    $ cat /etc/services | grep -w "smtp"
    smtp		 25/tcp	   mail		#Simple Mail Transfer
    smtp		 25/udp	   mail		#Simple Mail Transfer
    smtps		465/tcp	   #smtp protocol over TLS/SSL (was ssmtp)
    smtps		465/udp	   #smtp protocol over TLS/SSL (was ssmtp)

As you can see the equal port numbers are <code>25</code> and <code>465</code>. Depending on how you did configured your mail server (e.g. <code>25</code> for PLAIN and STARTTLS, <code>465</code> for TLS/SSL) you can pick one or both <code>25</code> and <code>465</code>.

As you may have noticed already, I did mixed numbers and names in the <code>firewall_myservices</code> list. That's because I used a non-default port instead of <code>22</code> for SSH. It is perfectly fine to mix-up numbers and names in the list.

Now it's time to start the firewall by running the following command:

    $ service ipfw start

After starting the firewall you can always check the current rules by using the following command:

    $ ipfw list

Now, you may ask there is one little issue with configuring IPFW through <code>firewall_myservices</code>. This list is TCP only and there is no way to configure UDP ports through <code>/etc/rc.conf</code>. OK, we address that by extending the default configuration through our own script without touching any files from the base system which is the proper way to do so. If you take a look at <code>/etc/rc.firewall</code> script, I'm sure you'll figure out how FreeBSD applies <code>firewall_*</code> options. So, we adopt the same approach by writing our own script. Therefore, we create and put the following script inside <code>/usr/local/etc/</code> in the first step:

{% codeblock /usr/local/etc/rc.firewall lang:sh %}
#!/bin/sh

#  (The MIT License)
#
#  Copyright (c) 2015 Mohammad S. Babaei
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
    echo "Error: unknown parameter '${1}'"
    ;;
esac
{% endcodeblock %}

Then we have to fix its permissions to make it read-only and executable by anyone:

    $ chmod u-w,ugo+x /usr/local/etc/rc.firewall

In the end, we have to apply our own configuration for both TCP and UDP ports inside <code>/etc/rc.conf</code>:

{% codeblock /etc/rc.conf lang:sh %}
firewall_enable="YES"
firewall_quiet="YES"
firewall_type="workstation"
#firewall_myservices="11011 domain http https imap imaps pop3 pop3s smtp smtps"
firewall_allowservices="any"
firewall_logdeny="YES"
firewall_coscripts="/usr/local/etc/rc.firewall"
firewall_myservices_tcp="11011 domain http https imap imaps pop3 pop3s smtp smtps"
firewall_myservices_udp="domain"
{% endcodeblock %}

Then it's time to restart IPFW firewall and check whether our script did its job properly or not:

    $ service ipfw restart
    $ ipfw list

<code>firewall_myservices_tcp</code> and <code>firewall_myservices_tcp</code> are our own extended options. Note that we'll leave alone <code>firewall_myservices</code> despite the fact that it's still functional. For the sake of clarity we choose to use our own <code>firewall_myservices_tcp</code> and avoid using or mixing it with <code>firewall_myservices</code>. So, from now on we abandon <code>firewall_myservices</code>.

Last but not least, a recommended best practice is putting a limit on the logging of denials per IP address. This will prevent a single, persistent user to fill up our logs. To do so we should adjust <code>net.inet.ip.fw.verbose_limit</code> by issuing the following command:

    $ sysctl net.inet.ip.fw.verbose_limit=5

This adjusts the number of logs per IP to <code>5</code>. In order to make that permanent and apply it on future reboots we should add it to <code>/etc/sysctl.conf</code>:

{% codeblock /etc/sysctl.conf lang:sh %}
net.inet.ip.fw.verbose_limit=5
{% endcodeblock %}


<br />
<a name="Sshguard"></a>

### Sshguard ###

Do not let the name fool you. Sshguard protects many services out of the box, including but not limited to: [OpenSSH](http://openssh.org/), [Sendmail](http://www.sendmail.org/), [Exim](http://www.exim.org/), [Dovecot](http://www.dovecot.org/), [Cucipop](http://freecode.com/projects/cucipop/), [UW IMAP](http://www.washington.edu/imap/), [vsftpd](https://security.appspot.com/vsftpd.html), [ProFTPD](http://www.proftpd.org/), [Pure-FTPd](http://www.pureftpd.org/project/pure-ftpd) and [FreeBSD ftpd](https://www.freebsd.org/doc/en/books/handbook/network-ftp.html).

{% blockquote Sshguard home page http://www.sshguard.net/ What is sshguard? %}
Sshguard monitors servers from their logging activity. When logs convey that someone is doing a Bad Thing, sshguard reacts by blocking he/she/it for a bit. Sshguard has a touchy personality: when a naughty tyke insists disturbing your host, it reacts firmer and firmer.

Sshguard supports many services out of the box, recognizes several log formats, and can operate many firewall systems. Many users appreciate its ease of use, compatibility and feature richness.
{% endblockquote %}

Currently, [FreeBSD Ports](https://www.freebsd.org/ports/) provides five variants of Sshguard:

* <code>security/sshguard</code> Protects your host from brute force attacks against ssh and other services.
* <code>security/sshguard-ipfilter</code> Utilizes IPF to protect your host from brute force attacks against ssh and other services
* <code>security/sshguard-ipfw</code> Utilizes IPFW to protect your host from brute force attacks against ssh and other services
* <code>security/sshguard-null</code> Do-nothing backend for applying detection but not prevention.
* <code>security/sshguard-pf</code> Utilizes PF to protect your host from brute force attacks against ssh and other services.

So, we choose <code>security/sshguard-ipfw</code> since we just setup up an IPFW firewall. To install Sshguard for IPFW from Ports collection:

    $ cd /usr/ports/security/sshguard-ipfw/
    $ make config-recursive
    $ make install clean

Or if you are using [pkgng](https://www.freebsd.org/doc/handbook/pkgng-intro.html) instead of Ports:

    $ pkg install security/sshguard-ipfw

Finally, to enable Sshguard for a typical usage we have to modify our <code>/etc/r.conf</code> as follows:

{% codeblock /etc/rc.conf lang:sh %}
sshguard_enable="YES"
{% endcodeblock %}

But, Sshguard on FreeBSD gives you more options to tweak. The valid options are:

* <code>sshguard_enable</code> [BOOLEAN, DEFAULT: <code>NO</code>]: Set it to <code>YES</code> to enable sshguard.
* <code>sshguard_pidfile</code> [STRING, OPTION: <code>-i</code>, DEFAULT: <code>/var/run/sshguard.pid</code>]: Path to PID file.
* <code>sshguard_watch_logs</code> [STRING, DEFAULT: <code>/var/log/auth.log:/var/log/maillog</code>]: Colon splitted list of logs to watch.
* <code>sshguard_blacklist</code> [STRING, OPTION: <code>-b</code>, DEFAULT: <code>40:/var/db/sshguard/blacklist.db</code>]: <code>[threshold:]/path/to/blacklist</code>.
* <code>sshguard_safety_thresh</code> [INTEGER, OPTION: <code>-a</code>, DEFAULT: <code>40</code>]: Safety threshold.
* <code>sshguard_pardon_min_interval</code> [INTEGER, OPTION: <code>-p</code>, DEFAULT: <code>420</code>]: Minimum pardon interval in seconds.
* <code>sshguard_prescribe_interval</code> [INTEGER, OPTION: <code>-s</code>, DEFAULT: <code>1200</code>]: Prescribe interval in seconds.
* <code>sshguard_whitelistfile</code> [STRING, OPTION: <code>-w</code>, DEFAULT: <code>/usr/local/etc/sshguard.whitelist</code>]: Path to the whitelist.
* <code>sshguard_flags</code> [STRING]: Set additional command line arguments.

Please note that some of the above options directly map to their command line options. So, it won't do any harm to consult the manual page [sshguard(8)](https://www.freebsd.org/cgi/man.cgi?query=sshguard&apropos=0&sektion=8&manpath=FreeBSD+10.1-RELEASE+and+Ports&arch=default&format=html) for detailed information.

Anyway, let's start Sshguard:

    $ service sshguard start

Now, we can test our setup from another machine with different IP to see if it works. I did tried it without any luck. Unfortunately, it did not worked as expected since IPFW runs a first-match-win policy. This is due to the fact that the rules generated by Sshguard has lower priority than the ones generated by our script that we wrote earlier. According to [the official documentation of Sshguard](http://www.sshguard.net/docs/setup/firewall/ipfw/), it adds blocking rules with IDs from 55000 to 55050 by default:

{% blockquote Sshguard official documentation http://www.sshguard.net/docs/setup/firewall/ipfw/ Set up IPFW firewall - Adjusting passing rule priority %}
With IPFW, sshguard adds blocking rules with IDs from 55000 to 55050 by default. If a pass rule appears before these, it is applied because IPFW runs a first-match-win policy.

If you have an allow policy higher than 55050 in your IPFW chain, move it to a lower priority.
{% endblockquote %}

So we have to modify our own script to adapt to the new situation:

{% codeblock /usr/local/etc/rc.firewall lang:sh %}
#!/bin/sh

#  (The MIT License)
#
#  Copyright (c) 2015 Mohammad S. Babaei
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

if [ -z "${firewall_myservices_rules_id_start}" ] ;
then
    firewall_myservices_rules_id_start=56000
fi

if [ -z "${firewall_myservices_rules_id_step}" ] ;
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
    echo "Error: unknown parameter '${1}'"
    ;;
esac
{% endcodeblock %}

So, we added <code>firewall_myservices_rules_id_start</code> and <code>firewall_myservices_rules_id_step</code> as a way to control the ID assignment of the rules. Now our final configuration for IPFW + Sshguard looks like this one:

{% codeblock /etc/rc.conf lang:sh %}
firewall_enable="YES"
firewall_quiet="YES"
firewall_type="workstation"
firewall_allowservices="any"
firewall_logdeny="YES"
firewall_coscripts="/usr/local/etc/rc.firewall"
firewall_myservices_rules_id_start="56000"
firewall_myservices_rules_id_step="10"
firewall_myservices_tcp="11011 domain http https imap imaps pop3 pop3s smtp smtps"
firewall_myservices_udp="domain"

sshguard_enable="YES"
sshguard_pidfile="/var/run/sshguard.pid"
sshguard_watch_logs="/var/log/auth.log:/var/log/maillog"
sshguard_blacklist="40:/var/db/sshguard/blacklist.db"
sshguard_safety_thresh="40"
sshguard_pardon_min_interval="420"
sshguard_prescribe_interval="1200"
sshguard_whitelistfile="/usr/local/etc/sshguard.whitelist"
sshguard_flags=""
{% endcodeblock %}

After making the final modification we have to restart IPFW once more and check out the rules:

    $ service ipfw restart
    $ ipfw list

From now on, our rules IDs for ports specified in both <code>${firewall_myservices_tcp}</code> and <code>${firewall_myservices_udp}</code> should start from 56000 with a 10 step gap in between. e.g. 56000, 56010, 56020....

Ultimately, at anytime you can check the blocked IP's by issuing the following command:

    $ ipfw list | awk '{ if ( $1 >= 55000 && $1 <= 55050 ) print $5 }'

Or directly checking the blacklist file:

    $ cat /var/db/sshguard/blacklist.db


<br />
<a name="Unban"></a>

### Unban ###

If you or some other host get banned, you can wait to get unbanned automatically or use the following set of instructions:

First check if you are banned by Sshguard:

    $ ipfw list | awk '{ if ( $1 >= 55000 && $1 <= 55050 ) print $5 }'

Or

    $ cat /var/db/sshguard/blacklist.db

If the answer is positive, the are two more steps that you should take to get unbanned. First you have to remove the host from Sshguard blacklist database, e.g. <code>/var/db/sshguard/blacklist.db</code> if you are using the default option. Let's say we would like to unblock the penultimate IP in the following database which is <code>192.168.10.101</code>:

    $ cat /var/db/sshguard/blacklist.db
    # SSHGuard blacklist file ( http://www.sshguard.net/ ).
    # Format of entries: BLACKLIST_TIMESTAMP|SERVICE|ADDRESS_TYPE|ADDRESS
    1437762353|100|4|10.12.0.4
    1437850200|100|4|192.168.10.17
    1437893500|260|4|10.10.0.18
    1437903401|260|4|10.10.0.23
    1437997365|100|4|192.168.10.101
    1438253201|260|4|10.10.0.17
    $ sed -i '' '/192.168.10.101/ d' /var/db/sshguard/blacklist.db

The next step involves removing the related rule from IPFW:

    $ ipfw list | grep "192.168.10.101"
    55037 deny ip from 192.168.10.101 to me
    $ ipfw -q delete deny ip from 192.168.10.101 to me

Or simply delete the rule using its ID:

    $ ipfw list | grep "192.168.10.101"
    55037 deny ip from 192.168.10.101 to me
    $ ipfw -q delete 55037


<br />
<a name="SshguardWontStart"></a>

### Sshguard Won't Start ###

Remove both PID file and blacklist file, then start Sshguard service again:

    $ rm /var/run/sshguard.pid /var/db/sshguard/blacklist.db
    $ service sshguard start


<br />
<a name="SourceCode"></a>

### Source Code ###

[Full source code on GitLab](https://gitlab.com/NuLL3rr0r/babaei.net/tree/master/2015-07-30-freebsd-block-brute-force-attacks-using-sshguard-and-ipfw-firewall)

[Full source code on GitHub](https://github.com/NuLL3rr0r/babaei.net/tree/master/2015-07-30-freebsd-block-brute-force-attacks-using-sshguard-and-ipfw-firewall)


