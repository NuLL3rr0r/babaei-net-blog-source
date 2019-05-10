+++
title = "Keep Crashing Daemons Running on FreeBSD"
slug = "keep-crashing-daemons-running-on-freebsd"
date = 2019-05-09T19:27:37+02:00
tags = [ "FOSS", "FLOSS", "FreeBSD", "Unix" ]
toc = true
draft = true
+++

Amidst all the chaos in the current stage of my life, I don't know exactly what got into me that I thought it was a good idea to perform a major upgrade on a production FreeBSD server from <code>11.2-RELENG</code> to <code>12.0-RELENG</code>, when I even did not have enough time to go through <code>/usr/src/UPDATING</code> thoroughly or consult [the Release Notes](https://www.freebsd.org/releases/12.0R/relnotes.html) or [the Errata](https://www.freebsd.org/releases/12.0R/errata.html) properly; let alone [hitting some esoteric changes which technically crippled my mail server](https://forums.freebsd.org/threads/mailserver-stops-working-after-a-few-days-after-12-releng-upgrade.70640/), when I realized it has been over a week that I haven't been receiving any new emails.

At first, I did not take it seriously. Just rebooted the server and prayed to the gods that it won't happen again. It was a quick fix and it seemed to work. Until, after a few days I noticed that it happened again. This time I prayed to the gods - both the old ones and the new ones - even harder and rebuilt every install ports all over again in order to make sure I did not miss anything. I went for another reboot and, ops! There it was again, laughing at me. Thus, losing all faith in the gods, which led me to [take up responsibility and investigate more on this or ask the experts on the FreeBSD forums](https://forums.freebsd.org/threads/mailserver-stops-working-after-a-few-days-after-12-releng-upgrade.70640/).

After messing around with it, it turned out that the culprit is <code>clamav-clamd</code> service crashing without any apparent reason. According to [this Stack Exchange answer](https://unix.stackexchange.com/a/278110):

{{< blockquote author="vk5tu" link="https://unix.stackexchange.com/a/278110" title="How to reduce ClamAV memory usage?" >}}
ClamAV holds the search strings using the classic string (Boyer Moore) and regular expression (Aho Corasick) algorithms. Being algorithms from the 1970s they are extemely memory efficient.

The problem is the huge number of virus signatures. This leads to the algorithms' datastructures growing quite large.

You can't send those datastructures to swap, as there are no parts of the algorithms' datastructures accessed less often than other parts. If you do force pages of them to swap disk, then they'll be referenced moments later and just swap straight back in. (Technically we say "the random access of the datastructure forces the entire datastructure to be in the process's working set of memory".)

The datastructures are needed if you are scanning from the command line or scanning from a daemon.

You can't use just a portion of the virus signatures, as you don't get to choose which viruses you will be sent, and thus can't tell which signatures you will need.
{{< /blockquote >}}

I guess due to some arcane changes in <code>12.0-RELEASE</code>, FreeBSD kills memory hogs such as <code>clamav-clamd</code> daemon (don't take my word for it. it is just a poor man's guess). I even tried to [lower the memory usage](https://forum.directadmin.com/showthread.php?t=55146) without much of a success. At the end, there were not too many choices or workarounds around the corner:

<code>A</code>. Pray to the gods that it go away by itself, which I deemed impractical

<code>B</code>. Put aside laziness, and replace <code>security/clamsmtp</code> with <code>security/amavisd-new</code> in order to be able to [run ClamAV on-demand which has its own pros and cons](ClamAV)

<code>C</code>. Write a quick POSIX-shell script to scan for a running <code>clamav-clamd</code> process using <code>ps aux | grep clamd</code>, set it up as a cron job with X-minute(s) interval, and then start the server if it cannot be found running

For the sake of slothfulness, I opted to go with option <code>C</code>. As a consequence, I came up with a generic simple script that is able to not only monitor and restart the <code>clamav-clamd</code> service but also is able to keep any other crashing services running on FreeBSD.

<!--more-->

## Requirements and Dependencies

Taking a look [at the source code](#obtaining-the-source-code) reveals the necessitas for running the script successfully:

{{< highlight bash >}}
readonly BASENAME="basename"
readonly CUT="/usr/bin/cut"
readonly ECHO="echo -e"
readonly GREP="/usr/bin/grep"
readonly LOGGER="/usr/bin/logger"
readonly PS="/bin/ps"
readonly REV="/usr/bin/rev"
readonly TR="/usr/bin/tr"
{{< /highlight >}}

All the dependencies in this list are either internal shell commands or are already present in the FreeBSD base system. So, for running the script, nothing extra is required.

## Usage Syntax

## Running through a Cron Job

I have already wrote [a guide on how to properly add a cron job on *nix systems](https://crontab.guru/), so I won't go through this in details. Fire up the root's <code>crontab</code> file in your favorite editor by issuing:

{{< highlight sh >}}
$ sudo -u root -g root -H crontab -e
{{< /highlight >}}

I prefer to detect a crash as immediately as possible and then restart the service instantaneously. Therefore, I am running the script every <code>1</code> minute:

{{< highlight cron >}}
*   *   *   *   *   /usr/local/cron-scripts/daemon-keeper.sh -e "/usr/local/sbin/clamd" -s "clamav-clamd" -s "dovecot"
{{< /highlight >}}

If you are not familiar with the <code>crontab</code> syntax, [crontab.guru is a great visual aid](https://crontab.guru/).

On another note, due to the fact that this script is designed to run as a cron job, in addition to <code>stdout</code> and <code>stderr</code>, the scripts logs are getting passed through to the system's log file. On FreeBSD this file is located at <code>/var/log/messages</code>. This portion of the system log output is the result of the script running as a cron job:

{{< highlight sh >}}
$ tail -f /var/log/messages
May  9 20:49:00 3rr0r DAEMON-KEEPER[75509]: WARNING '/usr/local/sbin/clamd' is not running!
May  9 20:49:00 3rr0r DAEMON-KEEPER[78503]: INFO Stopping the service 'clamav-clamd'...
May  9 20:49:00 3rr0r DAEMON-KEEPER[11358]: ERROR Failed to stop the 'clamav-clamd' service!
May  9 20:49:00 3rr0r DAEMON-KEEPER[13204]: INFO Starting the service 'clamav-clamd'...
May  9 20:49:58 3rr0r DAEMON-KEEPER[34208]: INFO The 'clamav-clamd' service has been started successfully!
May  9 20:49:58 3rr0r DAEMON-KEEPER[36552]: INFO Stopping the service 'dovecot'...
May  9 20:49:59 3rr0r DAEMON-KEEPER[32672]: INFO The 'dovecot' service has been stopped successfully!
May  9 20:49:59 3rr0r DAEMON-KEEPER[36849]: INFO Starting the service 'dovecot'...
May  9 20:49:59 3rr0r DAEMON-KEEPER[2973]: INFO The 'dovecot' service has been started successfully!
May  9 20:50:00 3rr0r DAEMON-KEEPER[89081]: INFO '/usr/local/sbin/clamd' is running!
May  9 20:50:00 3rr0r DAEMON-KEEPER[94832]: INFO No action is required!
{{< /highlight >}}

## How it Works

Do not let <code>~200</code> lines of shell script code fool you. In fact, there is only one line of code (broken into multiple lines for the purpose of readability) in the script that does all the work:

{{< highlight sh >}}
readonly DAEMON_PROCESS_COUNT=$(${PS} aux \
    | ${GREP} -v "${GREP}" \
    | ${GREP} -v "${SCRIPT}" \
    | ${GREP} -c "${DAEMON}")
{{< /highlight >}}

Technically what it does is, listing all the running processes from all the users on the system, then looking for the target daemon it leaves out all the other processes, afterwards counting the number of running processes. If the dameon is not running, then the process counts is simply zero. As simple as that.

Leaving out the <code>${GREP} -v "${SCRIPT}"</code> part (we will be attending this one in a moment) and the variable assignment, it will be basically translated to something similar to:

{{< highlight sh >}}
$ ps aux | grep -v grep | grep -c /usr/local/sbin/clamd
{{< /highlight >}}

If <code>clamd</code> is running, the result of running the above command would be a number bigger than zero; otherwise, it would be zero. Well, let's break it down brick by brick:

{{< highlight sh >}}
$ ps aux

# SORRY!
# I WON'T BE SHARING THE OUTPUT OF THIS COMMAND AS IT IS TOO DANGEROUS SINCE
# ONE CAN GET TO KNOW WHAT EXACTLY I AM RUNNING ON THIS SERVER FOR A POTENTIAL
# EXPLOIT.
# INSTEAD, IF YOU WOULD LIKE TO, YOU CAN RUN IT ON YOUR OWN *NIX DISTRO, AND
# SEE FOR YOURSELF WHAT IT DOES.
{{< /highlight >}}

What does <code>pas aux</code> is essentially do, shows all the processes for all users (for our purpose the <code>ax</code> flags would suffice and the <code>u</code> can be omitted, nonetheless as a habit I keep it). Now try the following:

{{< highlight sh >}}
$ ps aux | grep /usr/local/sbin/clamd

clam      26199   0.0 23.7  747944 323252  -  Is   20:51     0:00.58 /usr/local/sbin/clamd
root      34001   0.0  0.2   11492   2768  0  S+   22:27     0:00.00 grep /usr/local/sbin/clamd
{{< /highlight >}}

In case <code>clamd</code> is running, it returns the above results. If <code>clamd</code> is not running (e.g. crashed or has not been started yet):

{{< highlight sh >}}
$ ps aux | grep /usr/local/sbin/clamd

root      34001   0.0  0.2   11492   2768  0  S+   22:27     0:00.00 grep /usr/local/sbin/clamd
{{< /highlight >}}

So, always the grep command gets counted as one line since it is a running process at the moment the output of <code>ps aux</code> from the left side of pipe is getting piped to the second part of the command. Using one more pipe we try to eliminate any <code>grep</code> processes from the results before feeding the output to the last <code>grep</code>. This is what <code>grep -v grep</code> does in the following command</code>. So, if it finds the clamd process it returns the following output, or else nothing at all (which signifies the daemon is not running):

{{< highlight sh >}}
$ ps aux | grep -v grep | grep /usr/local/sbin/clamd

clam      26199   0.0 23.7  747944 323252  -  Is   20:51     0:00.58 /usr/local/sbin/clamd
{{< /highlight >}}

As a final note, when we run the script as a cron job, there is one more thing that has to be taken care of. The <code>${GREP} -v "${SCRIPT}"</code> part. Remember the cron job from the previous section?

{{< highlight cron >}}
# At every minute
*   *   *   *   *   /usr/local/cron-scripts/daemon-keeper.sh -e "/usr/local/sbin/clamd" -s "clamav-clamd" -s "dovecot"
{{< /highlight >}}

When we run the script from a cron job, if you haven't noticed by now, we pass the <code>/usr/local/sbin/clamd</code> to the script and it is considered a running process when the output is caught by <code>grep</code> always adding one more line to the output. So we have to eliminate it like so, or the script thinks the process is running due to count being at least <code>1</code> all the times:

{{< highlight sh >}}
$ ps aux | grep -v grep \
    | grep -v "/usr/local/cron-scripts/daemon-keeper.sh" \
    | grep "/usr/local/sbin/clamd"
{{< /highlight >}}
I

## Obtaining the Source Code

The source code is available on both [GitHub](https://github.com/NuLL3rr0r/freebsd-daemon-keeper/) and [GitLab](https://gitlab.com/NuLL3rr0r/freebsd-daemon-keeper/) for the sake of convenience. In order to download the source code using <code>fetch</code>, <code>curl</code>, <code>aria2</code>, <code>wget</code> directly:

{{< highlight sh >}}
# GitHub
$ curl -fLo /path/to/daemon-keeper.sh \
    --create-dirs \
    https://raw.githubusercontent.com/NuLL3rr0r/freebsd-daemon-keeper/master/daemon-keeper.sh

# GitLab
$ curl -fLo /path/to/daemon-keeper.sh\
    --create-dirs \
    https://gitlab.com/NuLL3rr0r/freebsd-daemon-keeper/raw/master/daemon-keeper.sh
{{< /highlight >}}

It is also possible to obtain the whole repository by cloning it from <code>git</code>:

{{< highlight sh >}}
# GitHub
$ git clone \
    https://github.com/NuLL3rr0r/freebsd-daemon-keeper.git \
    /path/to/clone/freebsd-daemon-keeper

# GitLab
$ git clone \
    https://gitlab.com/NuLL3rr0r/freebsd-daemon-keeper.git \
    /path/to/clone/freebsd-daemon-keeper
{{< /highlight >}}

Lastly, for the sake of convenience, it can be copy-pasted directly from here, which is strongly discouraged due to [Pastejacking Exploitation Technique](https://github.com/dxa4481/Pastejacking):

{{< codeblock lang="sh" title="daemon-keeper.sh" line_numbers="true" >}}
#!/usr/bin/env sh

#  (The MIT License)
#
#  Copyright (c) 2019 Mamadou Babaei
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


set +e

readonly BASENAME="basename"
readonly CUT="/usr/bin/cut"
readonly ECHO="echo -e"
readonly GREP="/usr/bin/grep"
readonly LOGGER="/usr/bin/logger"
readonly PS="/bin/ps"
readonly REV="/usr/bin/rev"
readonly TR="/usr/bin/tr"

readonly FMT_OFF='\e[0m'
readonly FMT_INFO='\e[1;32m'
readonly FMT_WARN='\e[1;33m'
readonly FMT_ERR='\e[1;91m'
readonly FMT_FATAL='\e[1;31m'

readonly LOG_INFO="INFO"
readonly LOG_WARN="WARNING"
readonly LOG_ERR="ERROR"
readonly LOG_FATAL="FATAL"

readonly SCRIPT="$0"
readonly SCRIPT_NAME="$(${BASENAME} -- "${SCRIPT}")"
readonly SYSLOG_TAG="$(${BASENAME} -- "${SCRIPT}" \
    | ${TR} '[:lower:]' '[:upper:]' \
    | ${REV} \
    | ${CUT} -d "." -f2- \
    | ${REV})"

usage()
{
    ${ECHO}
    ${ECHO} "${FMT_INFO}Correct usage:${FMT_OFF}"
    ${ECHO}
    ${ECHO} "    ${FMT_INFO}${SCRIPT_NAME} -e {executable full path} -s {service name to (re)start} [-s {another service name to (re)start}] [... even more -s and service names to (re)start]${FMT_OFF}"
    ${ECHO}

    exit 1
}

log()
{
    log_type=$1; shift
    fmt=$1; shift

    if [ -n "$1" -a -n "$@" ] ;
    then
        ${ECHO} "${fmt}[${log_type}] $@${FMT_OFF}"
        ${LOGGER} -t "${SYSLOG_TAG}" "${log_type} $@"
    fi 
}

info()
{
    log "${LOG_INFO}" "${FMT_INFO}" "$@"
}

warn()
{
    log "${LOG_WARN}" "${FMT_WARN}" "$@"
}

err()
{
    log "${LOG_ERR}" "${FMT_ERR}" "$@"
}

fatal()
{
    log "${LOG_FATAL}" "${FMT_FATAL}" "$@"
    exit 1
}

restart_service()
{
    service_name="$1"

    info "Stopping the service '${service_name}'..."
    service ${service_name} stop > /dev/null 2>&1

    if [ "$?" -eq 0 ] ;
    then
        info "The '${service_name}' service has been stopped successfully!"
    else
        err "Failed to stop the '${service_name}' service!"
    fi

    info "Starting the service '${service_name}'..."
    service ${service_name} start > /dev/null 2>&1

    if [ "$?" -eq 0 ] ;
    then
        info "The '${service_name}' service has been started successfully!"
    else
        err "Failed to start the '${service_name}' service!"
    fi
}

if [ "$#" -eq 0 ] ;
then
    usage
fi

SERVICE_COUNT=0

while getopts ":e: :s:" ARG ;
do
    case ${ARG} in
        e)
            if [ -z "${OPTARG}" ] ;
            then
                err "Missing executable ${OPTARG}!"
                usage
            fi

            if [ ! -f "${OPTARG}" ] ;
            then
                fatal "The executable '${OPTARG}' does not exist!"
            fi

            readonly DAEMON="${OPTARG}"
            ;;
        s)
            if [ ! -f "/usr/etc/rc.d/${OPTARG}" \
                -a ! -f "/usr/local/etc/rc.d/${OPTARG}" ] ;
            then
                fatal "No such a service exists: '${OPTARG}'!"
            fi

            SERVICE_COUNT=$((SERVICE_COUNT+1))
            ;;
        \?)
            err "Invalid option: -${OPTARG}!"
            usage
        ;;
    esac
done

if [ "${SERVICE_COUNT}" -eq 0 ] ;
then
    err "At least one service name is required!"
    usage
fi

readonly DAEMON_PROCESS_COUNT=$(${PS} aux \
    | ${GREP} -v "${GREP}" \
    | ${GREP} -v "${SCRIPT}" \
    | ${GREP} -c "${DAEMON}")

if [ "${DAEMON_PROCESS_COUNT}" -lt 1 ] ;
then
    warn "'${DAEMON}' is not running!"

    OPTIND=1
    while getopts ":e: :s:" ARG ;
    do
        case ${ARG} in
            s)
                restart_service "${OPTARG}"
                ;;
            \?)
            ;;
        esac
    done
else
    info "'${DAEMON}' is running!"
    info "No action is required!"
fi
{{< /codeblock >}}
