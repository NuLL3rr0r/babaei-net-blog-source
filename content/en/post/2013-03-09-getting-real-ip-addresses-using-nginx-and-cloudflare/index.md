+++
title = "Getting real IP addresses using Nginx and CloudFlare"
slug = "getting-real-ip-addresses-using-nginx-and-cloudflare"
date = 2013-03-09T01:35:00+03:30
tags = [ "AWK", "Bash", "CloudFlare", "Cron", "csh", "FLOSS", "FOSS", "FreeBSD", "Funtoo", "Gentoo", "GNU", "Linux", "Nginx", "sh", "Shell Scripting", "Unix" ]
toc = true
aliases = [ "/blog/2013/03/09/getting-real-ip-addresses-using-nginx-and-cloudflare/" ]
+++

**[Update]**: Thanks to [digitaltoast](https://github.com/digitaltoast) for informing me about the missing <s>real_ip_header CF-Connecting-IP;</s> from the script and providing [a patch](https://github.com/NuLL3rr0r/babaei.net/pull/1) for it.

OK, I suppose you know what [CloudFlare](http://www.cloudflare.com/) is, and are familiar with [Nginx](http://nginx.org/) configuration process, before we proceed any further. Just in case you don't know, __CloudFlare__ offers free and commercial, cloud-based services to help secure and accelerate websites. The thing is, I'm really satisfied with the services they offer except a repellent issue about logging the real IP address of your website's visitors. Since __CloudFlare__ acts as a reverse proxy, all connections come from __CloudFlare__'s IP addresses, not the real visitors anymore. Anyway, using __Nginx__ there's a simple workaround for this issue, which I'll describe in the rest of this post.

<!--more-->

## HttpRealipModule

Well, to achieve over goal we have to first build __Nginx__ with [HttpRealipModule](http://wiki.nginx.org/HttpRealipModule) support. I'll describe three methods to build __Nginx__ with __RealIP__ module support on [FreeBSD](http://www.freebsd.org), [Funtoo](http://www.funtoo.org) or [Gentoo](http://www.gentoo.org) [GNU](http://www.gnu.org)/[Linux](https://www.kernel.org) variants and any other distros.


## Building from Ports on FreeBSD

In fact, building and installing __Nginx__ from [Ports](http://www.freebsd.org/ports/) is very easy and straightforward. Just issue the following commands:

{{< highlight sh >}}
$ cd /usr/ports/www/nginx
$ make config
{{</ highlight >}}

You have to find and choose __HTTP_REALIP__ by hitting __Spacebar__ on your keyboard in the opening configuration window:

```
[*] HTTP_REALIP           Enable http_realip module
```

By issuing the following command __Nginx__ will be built and installed by __Ports__.

{{< highlight sh >}}
$ make install clean
{{</ highlight >}}


## Building from Portage on Funtoo / Gentoo

To build and install __Nginx__ with __RealIP__ support from __Portage__ on __Gentoo__ or __Funtoo__ we have to first touch the __make.conf__ file with the following content. Just add the __realip__ keyword to __NGINX_MODULES_HTTP__:

{{< codeblock lang="sh" title="/etc/make.conf" line_numbers="true" >}}
# nginx
NGINX_MODULES_HTTP="some other modules ... realip"
{{< /codeblock >}}

Start the building and installation process by using the __emerge__ command:

{{< highlight sh >}}
$ emerge -avt www-servers/nginx
{{</ highlight >}}

You should see the __realip__ keyword without "-" sign in the __NGINX_MODULES_HTTP__ on the __emerge__ command output:

```
Calculating dependencies... done!
[ebuild   R    ] www-servers/nginx-1.x.x  USE="some use flags -some -disbaled -use -flags" NGIN
X_MODULES_HTTP="some other modules ... realip ... -some -disbaled -modules" NGINX_MODULES_MAIL=
"some modules -some -disbaled -modules"
```


## Building from Source

By following the instructions given below, it is easy to build __Nginx__ from source with __RealIP__ module support on any other distro. Because the __RealIP__ module won't build by default, you need to enable it with the configuration option __with-http_realip_module__.

{{< highlight sh >}}
$ wget http://nginx.org/download/nginx-1.x.x.tar.gz
$ tar xvzf nginx-1.x.x.tar.gz
$ cd nginx-1.x.x
$ ./configure --with-http_realip_module
$ make
$ make install
{{</ highlight >}}


## Nginx Configuration

After building __Nginx__ with __RealIP__ support enabled, now it's time to configure our vhosts in order to enable real visitors IP logging. I assume you've configured your vhosts and __Nginx__ installation already.

You need to first fetch __CloudFlare__'s [IPv4](https://www.cloudflare.com/ips-v4) and [IPv6](https://www.cloudflare.com/ips-v6) IP Ranges. You should consider, this list changes from time to time. So, it's vital to fetch and synchronize them with your own list on regular basis. However, it's possible to write an automated update script to accomplish this task. Therefore, I'll provide one at the end of the article.

Let's say we've chosen __/usr/local/www/nginx__ as __Ngix__ default host root. So, we put each vhost in its own directory at __/usr/local/www__. And, also put the vhost configurations inside the **/usr/local/www/_vhosts** directory. In addition to that, we create an **_include** directory at **/usr/local/www** for sharing CloudFlare settings among our vhosts.

{{< highlight sh >}}
$ mkdir -p /usr/local/www/_include/
{{</ highlight >}}

Anyway, our CloudFlare configuration file at **/usr/local/www/_include/cloudflare** looks like this:

{{< codeblock lang="nginx" title="/usr/local/www/_include/cloudflare" line_numbers="true" >}}
# CloudFlare
# https://www.cloudflare.com/ips-v4
# https://www.cloudflare.com/ips-v6
set_real_ip_from 204.93.240.0/24;
set_real_ip_from 204.93.177.0/24;
set_real_ip_from 199.27.128.0/21;
set_real_ip_from 173.245.48.0/20;
set_real_ip_from 103.21.244.0/22;
set_real_ip_from 103.22.200.0/22;
set_real_ip_from 103.31.4.0/22;
set_real_ip_from 141.101.64.0/18;
set_real_ip_from 108.162.192.0/18;
set_real_ip_from 190.93.240.0/20;
set_real_ip_from 188.114.96.0/20;
set_real_ip_from 197.234.240.0/22;
set_real_ip_from 198.41.128.0/17;
set_real_ip_from 2400:cb00::/32;
set_real_ip_from 2606:4700::/32;
set_real_ip_from 2803:f800::/32;
set_real_ip_from 2405:b500::/32;
set_real_ip_from 2405:8100::/32;
real_ip_header CF-Connecting-IP;
{{< /codeblock >}}

Finally, you can enable __RealIP__ for each vhost by including the **/usr/local/www/_include/cloudflare** file:

{{< codeblock lang="nginx" title="/usr/local/www/_vhosts/example.com" line_numbers="true" >}}
server {
    server_name  example.com;
    rewrite ^(.*) http://www.example.com$1 permanent;

    # CloudFlare
    include /usr/local/www/_include/cloudflare;
}

server {
    listen  80;
    server_name   www.example.com;

    root           /usr/local/www/example.com/www/;

    # CloudFlare
    include /usr/local/www/_include/cloudflare;
}

server {
    listen         80;
    server_name    sub.example.com;
 
    root           /usr/local/www/example.com/www-sub/;

    # CloudFlare
    include /usr/local/www/_include/cloudflare;
}
{{< /codeblock >}}


## Automated CloudFlare IP Ranges Update

You have to first create the **/usr/local/www/_cron** directory:

{{< highlight sh >}}
$ mkdir -p /usr/local/www/_cron
{{</ highlight >}}

Then, put the __cloudflare-ip-ranges-updater.sh__ file with the provided contents inside the **/usr/local/www/_cron** directory. The major prerequisites for this script to run correctly are [AWK](http://cm.bell-labs.com/cm/cs/awkbook/) and [FreeBSD fetch](<http://www.freebsd.org/cgi/man.cgi?fetch(1)>) or [GNU Wget](http://www.gnu.org/software/wget/). Also, you may need to change the __shebang__ line or script variables such as **CLOUDFLARE_IP_RANGES_FILE_PATH**, **WWW_GROUP** and **WWW_USER** according to your OS requirements.

{{< codeblock lang="sh" title="/usr/local/www/_cron/cloudflare-ip-ranges-updater.sh" line_numbers="true" >}}
#!/bin/sh

#  (The MIT License)
#
#  Copyright (c) 2013 Mamadou Babaei
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


CLOUDFLARE_IP_RANGES_FILE_PATH="/usr/local/www/_include/cloudflare"
WWW_GROUP="www"
WWW_USER="www"

CLOUDFLARE_IPSV4_REMOTE_FILE="https://www.cloudflare.com/ips-v4"
CLOUDFLARE_IPSV6_REMOTE_FILE="https://www.cloudflare.com/ips-v6"
CLOUDFLARE_IPSV4_LOCAL_FILE="/var/tmp/cloudflare-ips-v4"
CLOUDFLARE_IPSV6_LOCAL_FILE="/var/tmp/cloudflare-ips-v6"

if [ -f /usr/bin/fetch ];
then
    fetch $CLOUDFLARE_IPSV4_REMOTE_FILE --no-verify-hostname --no-verify-peer -o $CLOUDFLARE_IPSV4_LOCAL_FILE --quiet
    fetch $CLOUDFLARE_IPSV6_REMOTE_FILE --no-verify-hostname --no-verify-peer -o $CLOUDFLARE_IPSV6_LOCAL_FILE --quiet
else
    wget -q $CLOUDFLARE_IPSV4_REMOTE_FILE -O $CLOUDFLARE_IPSV4_LOCAL_FILE --no-check-certificate
    wget -q $CLOUDFLARE_IPSV6_REMOTE_FILE -O $CLOUDFLARE_IPSV6_LOCAL_FILE --no-check-certificate
fi

echo "# CloudFlare IP Ranges" > $CLOUDFLARE_IP_RANGES_FILE_PATH
echo "# Generated at $(date) by $0" >> $CLOUDFLARE_IP_RANGES_FILE_PATH
echo "" >> $CLOUDFLARE_IP_RANGES_FILE_PATH
awk '{ print "set_real_ip_from " $0 ";" }' $CLOUDFLARE_IPSV4_LOCAL_FILE >> $CLOUDFLARE_IP_RANGES_FILE_PATH
awk '{ print "set_real_ip_from " $0 ";" }' $CLOUDFLARE_IPSV6_LOCAL_FILE >> $CLOUDFLARE_IP_RANGES_FILE_PATH
echo "real_ip_header CF-Connecting-IP;" >> $CLOUDFLARE_IP_RANGES_FILE_PATH
echo "" >> $CLOUDFLARE_IP_RANGES_FILE_PATH

chown $WWW_USER:$WWW_GROUP $CLOUDFLARE_IP_RANGES_FILE_PATH

rm -rf $CLOUDFLARE_IPSV4_LOCAL_FILE
rm -rf $CLOUDFLARE_IPSV6_LOCAL_FILE
{{< /codeblock >}}

After that, set the script file's permissions to executable by all users:

{{< highlight sh >}}
$ chmod a+x /usr/local/www/_cron/cloudflare-ip-ranges-updater.sh
{{</ highlight >}}

Now, you may want to test the script by issuing the following set of commands:

{{< highlight sh >}}
$ /usr/local/www/_cron/cloudflare-ip-ranges-updater.sh
$ cat /usr/local/www/_include/cloudflare
{{</ highlight >}}

The output must be something like this:

{{< codeblock lang="nginx" title="/usr/local/www/_include/cloudflare" line_numbers="true" >}}
# CloudFlare IP Ranges
# Generated at Sat Mar  9 00:15:58 UTC 2013 by /usr/local/www/_cron/cloudflare-ip-ranges-updater.sh

set_real_ip_from 204.93.240.0/24;
set_real_ip_from 204.93.177.0/24;
set_real_ip_from 199.27.128.0/21;
set_real_ip_from 173.245.48.0/20;
set_real_ip_from 103.21.244.0/22;
set_real_ip_from 103.22.200.0/22;
set_real_ip_from 103.31.4.0/22;
set_real_ip_from 141.101.64.0/18;
set_real_ip_from 108.162.192.0/18;
set_real_ip_from 190.93.240.0/20;
set_real_ip_from 188.114.96.0/20;
set_real_ip_from 197.234.240.0/22;
set_real_ip_from 198.41.128.0/17;
set_real_ip_from 2400:cb00::/32;
set_real_ip_from 2606:4700::/32;
set_real_ip_from 2803:f800::/32;
set_real_ip_from 2405:b500::/32;
set_real_ip_from 2405:8100::/32;
real_ip_header CF-Connecting-IP;
{{</ codeblock >}}

If you want to update the CloudFlare IP Ranges every 24:00 hours as root user you should add the following at the end of your [system's crontab file](/blog/the-proper-way-of-adding-a-cron-job/):

{{< highlight sh >}}
$ sudo crontab -e -u root
{{</ highlight >}}

{{< codeblock lang="sh" title="sudo crontab -e -u root" line_numbers="true" >}}
# CloudFlare IP Ranges Automatic Update
# Every 24:00 hours at 04:00am UTC
00      04      *       *       *       root    /usr/local/www/_cron/cloudflare-ip-ranges-updater.sh >/dev/null 2>&1
{{< /codeblock >}}

It's also possible to set time intervals weekly or several times a month, a day or even hours:

{{< codeblock lang="sh" title="'sudo crontab -e -u root' other time interval samples" line_numbers="true" >}}
# Every 30 minutes
*/30     *       *       *       *       root    /usr/local/www/_cron/cloudflare-ip-ranges-updater.sh >/dev/null 2>&1
# or
# Every 7 days at 02:30am UTC
30      02      1,8,15,22,28    *       root    /usr/local/www/_cron/cloudflare-ip-ranges-updater.sh >/dev/null 2>&1
{{< /codeblock >}}

In order to verify your crontab entry:

{{< highlight sh >}}
$ sudo crontab -l -u root
{{</ highlight >}}

Finally, if necessary restart the __cron__ service:

{{< highlight sh >}}
$ service cron restart
{{</ highlight >}}

## Source Code

[Check out the source code on GitLab](https://gitlab.com/NuLL3rr0r/babaei.net/tree/master/2013-03-09-getting-real-ip-addresses-using-nginx-and-cloudflare)

[Check out the source code on GitHub](https://github.com/NuLL3rr0r/babaei.net/tree/master/2013-03-09-getting-real-ip-addresses-using-nginx-and-cloudflare)
