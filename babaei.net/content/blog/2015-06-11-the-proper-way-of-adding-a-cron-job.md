+++
title = "The Proper Way of Adding a Cron Job"
slug = "the-proper-way-of-adding-a-cron-job"
date = "2015-06-11T16:37:18Z"
tags = [ "FreeBSD", "GNU", "Linux", "Unix" ]
#template = "post.html"
+++

Until not so long ago, to add my own cron jobs I always had the habit of modifying <code>/etc/crontab</code> on my [FreeBSD](https://www.freebsd.org/) system [which turned out to be wrong](https://www.freebsd.org/doc/handbook/configtuning-cron.html). In simple words, there are two types of crontab files:

- __System crontab__ which should not be altered due to the troubles it cause during FreeBSD upgrades
- __User crontab__ which has one less column than the system crontab file

<!-- more -->

So, I found out that the proper way it should be done is using [crontab uitlity](https://www.freebsd.org/cgi/man.cgi?crontab%285%29) as it follows:

To create a crontab for current user:

    $ crontab -e

To create a crontab for a specific user (e.g. <code>babaei</code>):

    $ crontab -e -u babaei

This should create the user crontab files inside <code>/var/cron/tabs/</code> (e.g. <code>/var/cron/tabs/babaei</code>) and open up your system's default text editor which in my case is [nano](http://www.nano-editor.org/). It is better to avoid modifying these files directly and always modify them through <code>crontab -e</code> since you don't have to restart the <code>cron</code> service manually this way. By the way, <code>-e</code> stands for editor mode.

This is a typical <code>root</code> user crontab file I use on one of my production servers (as you can see there is no who column since it's useless in user's own crontab file format):

{% codeblock lang:sh %}
SHELL=/bin/sh
PATH=/sbin:/bin:/usr/sbin:/usr/bin:/usr/local/sbin:/usr/local/bin
MAILTO=""

# Order of crontab fields
# minute    hour    mday    month   wday    command

# At Boot
@reboot     /root/.cron/spawn-gitlab.sh
@reboot     /root/.cron/spawn-trac-instances.sh

# Automatic daily backup
@daily      /root/.cron/backup.sh

# Agilo for trac
# Every 15 minutes
*/15       *       *       *       *        /root/.cron/resync-trac-repos.sh

# CloudFlare IP Ranges Automatic Update
# Every 24:00 hours at 01:00am UTC
00      01      *       *       *       /root/.cron/cloudflare-ip-range-updater.sh

# GeoIP updater
# every 7 days at 00:30am UTC
30      00      1,8,15,22,28    *       *       /root/.cron/geoupdater
{% endcodeblock %}

To list the cron jobs in the crontab for the current user at any time, use the following command:

    $ crontab -l

Or for a specefic user you can try this one (e.g. <code>babaei</code>):

    $ crontab -l -u babaei

As you can see I added a few environment variables to the beginning of my crontab file. This is due to the fact that your cron scripts may not run properly due to executable path issues (e.g. you forgot to use absolute paths for commands you called in your scripts, so it won't be able to find those commands you used in your scripts). If you want to test whether your scripts run properly or not, you should replicate the environment that would be used to run your scripts by testing them with a limited set of environment variables set by cron:

    $ env -i SHELL=/bin/sh PATH=/sbin:/bin:/usr/sbin:/usr/bin:/usr/local/sbin:/usr/local/bin HOME=/root LOGNAME=Charlie /path/to/your/scriptname.sh

To see what these variables such as <code>HOME</code>, <code>LOGNAME</code>, <code>MAIL</code>, <code>PATH</code> and <code>SHELL</code> do, please refer to [crontab's manpage or documentation](http://crontab.org/).

I almost forgot to mention that, there is another common pitfall when you are going to run your script or binary executables through a crontab. And that is, they should have executable permission which can be achieved by one of the following commands:

Make it executable for the owner of the file:

    $ chmod u+x /path/to/your/executable

Make it executable for everyone:

    chmod a+x /path/to/your/executable


