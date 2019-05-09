+++
title = "My Reddit Wallpaper Downloader Script"
slug = "my-reddit-wallpaper-downloader-script"
date = 2019-05-08T01:01:00+02:00
tags = [ "FLOSS", "FOSS", "FreeBSD", "Funtoo", "Gentoo", "GNU", "i3", "i3wm", "Linux", "Unix" ]
toc = true
+++

{{< figure src="/blog/my-reddit-wallpaper-downloader-script/i3wm-gruvbox-color-scheme-reddit-wallpaper.jpg" alt="My i3wm setup with amazing gruvbox color scheme and a wallpaper from Reddit" caption="i3wm setup with amazing gruvbox color scheme and a wallpaper from Reddit" >}}

**Update [2019/05/08]**: Many people have been asking for the wallpaper in the above screenshot. It is from [System Failure II, oil on canvas, 31x43” on r/Art](https://www.reddit.com/r/Art/comments/aqeq16/system_failure_ii_oil_on_canvas_31x43/).

Well, I am really fascinated by [Reddit](https://www.reddit.com/) art and [genuine creative ideas such as Scrolller](https://scrolller.com/art) which [was made possible thanks to gazillions of art pieces scattered throughout various art subreddits](https://www.reddit.com/r/web_design/comments/6eoa78/i_made_a_simple_website_filled_with_random_nsfw/). I am also fascinated by [Unix philosophy](https://en.wikipedia.org/wiki/Unix_philosophy) and have been a *nix enthusiast for as long as I can remember. In addition to all this, the discovery of [r/unixporn](https://www.reddit.com/r/unixporn/) - realizing I am not the only one who cares about aesthetics of their Unix box - was a huge blow for me; to the point that studying the GitHub dotfiles posted along the screenshots on r/unixporn by fellow nix-enthusiast redditors felt like a day to day hubby for me.

All the while, I had a successful experiment with writing [a complex piece of real-world software in pure Bash with an amazingly wide range of features for around 3.5K lines of code](https://github.com/NuLL3rr0r/omnibackup). The real excitement came when it made to [the official FreeBSD Ports Tree](https://www.freebsd.org/cgi/ports.cgi?query=omnibackup&stype=all). In spite of the fact that many people find Bash syntax annoyingly ugly and unmaintainable and [often wonder why do people still write shell scripts by asking it on Quora](https://www.quora.com/Why-do-people-still-write-shell-scripts), since MS-DOS 6.22 era, I did develop a certain love–hate relationship with shell scripting languages such as Batch Files, Bash, etc. Thus, still [I do automate almost everything with these ancient technologies](https://gitlab.com/SeditiousGames/GodsOfDeceit/tree/master/Scripts).

So, here is my [fully-configurable wallpaper changer software written in bash which automagically fetches and display wallpapers from your favorite subs](https://github.com/NuLL3rr0r/reddit-wallpaper). It has been powering and brightening up my i3wm setup for the past eight months which led me to the conclusion that it deserves a proper introduction.

<!--more-->

## Requirements and Dependencies

Taking a look [at the source code](#obtaining-the-source-code) reveals the necessitas for running the script successfully:

{{< highlight bash >}}
readonly BASENAME="basename"
readonly CALLER="caller"
readonly CUT=$(which cut 2>/dev/null)z
readonly CURL=$(which curl 2>/dev/null)
readonly DATE=$(which date 2>/dev/null)
readonly ECHO="echo"
readonly ECHO_FMT="echo -e"
readonly ESETROOT=$(which esetroot 2>/dev/null)
readonly FEH=$(which feh 2>/dev/null)
readonly FIREFOX=$(which firefox 2>/dev/null)
readonly HSETROOT=$(which hsetroot 2>/dev/null)
readonly JQ=$(which jq 2>/dev/null)
readonly LOGGER="logger"
readonly PERL=$(which perl 2>/dev/null)
readonly PRINT="print"
readonly REV=$(which rev 2>/dev/null)
readonly TR=$(which tr 2>/dev/null)
readonly XSETROOT=$(which xsetroot 2>/dev/null)
{{< /highlight >}}

Most of the dependencies in this list are either internal shell commands or are already present on a nix system such as *BSDs or common GNU/Linux systems. Otherwise, it must be installed from your distro's package manager. The ones that may not be present by default are <code>curl</code>, <code>feh</code>, and <code>jq</code>. Between <code>esetroot</code>, <code>hsetroot</code> and <code>xsetroot</code> only one of them is required since they could be used interchangeably. Firefox is not a hard-dependency and can be avoided at cost of a warning:

{{< highlight sh >}}
[WARNING] 288 Firefox executable not found!
[WARNING] 290 Setting Firefox version string to: Mozilla Firefox 66.0
{{< /highlight >}}

Firefox is being used to fake the user agent while downloading meta data or actual images from Reddit. If the script won't be able to find it, it sets the version number to the latest version of Firefox which at the time of this writing is: <code>Mozilla Firefox 66.0</code>.

## Usage Syntax

Before running the script, please note that it must has the executable permission set on it. If not, in order to grant executable permission for all users:

{{< highlight sh >}}
$ chmod a+x /path/to/reddit-wallpaper.sh
{{< /highlight >}}

Or, only the current user (the user who owns the file):

{{< highlight sh >}}
$ chmod u+x /path/to/reddit-wallpaper.sh
{{< /highlight >}}

Or, the users under the group who owns the file:

{{< highlight sh >}}
$ chmod g+x /path/to/reddit-wallpaper.sh
{{< /highlight >}}

Getting away from the basics, one can simply run the script by issuing the following command and it will download and set a wallpaper from Reddit for you, since it assumes some defaults in case it's not given the required arguments:

{{< highlight sh >}}
$ /path/to/reddit-wallpaper.sh

[INFO] 304 Run 'reddit-wallpaper.sh -h' for more information on available options.
[INFO] 306 Setting user agent to 'Mozilla/5.0 (X11; Linux x86_64; rv:66.0) Gecko/20100101 Firefox/66.0'...
[INFO] 310 Downloading meta file 'https://www.reddit.com/r/Art+ArtPorn+Cinemagraphs+ExposurePorn+Graffiti+ImaginaryLandscapes+itookapicture+ImaginaryBehemoths+ImaginaryCharacters+ImaginaryLandscapes+ImaginaryLeviathans+ImaginaryMindscapes+ImaginaryMonsters+ImaginaryTechnology/hot.json'...
[INFO] 381 Found a wallpaper on 'r/Art+ArtPorn+Cinemagraphs+ExposurePorn+Graffiti+ImaginaryLandscapes+itookapicture+ImaginaryBehemoths+ImaginaryCharacters+ImaginaryLandscapes+ImaginaryLeviathans+ImaginaryMindscapes+ImaginaryMonsters+ImaginaryTechnology' at 'https://cdnb.artstation.com/p/assets/images/images/017/756/697/large/jon-juarez-caramanchada3-800.jpg'!
[INFO] 382 Fetching 'https://cdnb.artstation.com/p/assets/images/images/017/756/697/large/jon-juarez-caramanchada3-800.jpg'...
[INFO] 392 Setting desktop background color to '#282828'...
[INFO] 402 Using 'https://cdnb.artstation.com/p/assets/images/images/017/756/697/large/jon-juarez-caramanchada3-800.jpg' as the desktop wallpaper...
[INFO] 412 Done!
[INFO] 413 Hope you enjoy it :)
{{< /highlight >}}

So far so good! Now, the correct usage syntax for the script is as follows:

```
Correct usage:

    reddit-wallpaper.sh -h | [-r {r/subreddit}] [-s {sorty by}] [-n] [-b {background color}] [-f 'feh args']

    -h: shows this usage note

    -r: subreddit name or names prefixed with r/ and combined by a + sign (e.g. r/Art or r/Art+ArtPorn; default: r/Art+ArtPorn+Cinemagraphs+ExposurePorn+Graffiti+ImaginaryLandscapes+itookapicture+ImaginaryBehemoths+ImaginaryCharacters+ImaginaryLandscapes+ImaginaryLeviathans+ImaginaryMindscapes+ImaginaryMonsters+ImaginaryTechnology)

    -s: reddit sort algorithm (e.g. hot, new, controversial, top, rising; default: hot)

    -n: allow nsfw wallpapers (no nsfw wallpaper is allowed by default, unless this flag is passed)

    -b: hex rgb color in 'ffffff' format (default: 282828)

    -f: feh arguments to pass; run 'man feh' for a list of available options (default: --no-fehbg --image-bg black --bg-max)
```

One can always get this information by utilizing <code>-h</code> option:

{{< highlight sh >}}
$ /path/to/reddit-wallpaper.sh -h
{{< /highlight >}}

Here is the detailed explanation for the rest of the options:

* <code>-r</code>: A typical sub-reddit url looks like <code>https://reddit.com/r/SomeCoolSubRedditA</code> or <code>https://reddit.com/r/SomeCoolSubRedditB</code>. If one desires, they may mix-up or simply join various subs by concatenating them; e.g., <code>https://reddit.com/r/SomeCoolSubRedditA+SomeCoolSubRedditB+SomeCoolSubRedditC</code>. This is one of the coolest features unique to Reddit among the social media. In the <code>-r</code> parameter the user should specify the name of the sub-reddit prefixed with <code>r/</code> without the <code>https://reddit.com/</code> part of the URL; e.g. <code>r/SomeCoolSubRedditA</code> or <code>r/SomeCoolSubRedditA+SomeCoolSubRedditB+SomeCoolSubRedditC</code>. For starters, one can take a look at the script's source code which provides a list consisting of some of the best subreddits in various categories such as <code>Animals</code>, <code>Art</code>, <code>Food</code>, <code>Imaginary</code>, <code>Man-made</code>, and <code>Nature</code>. By default the script uses everything under the <code>Art</code> category. If one desires to find more subreddits they could navigate to [Scrolller](https://scrolller.com/) and after clicking the gear icon on the top-right corner, reveal the category information by enabling the <code>Category info</code> option which not only lists the top subreddits but also provides a list of sub-reddits in various sub-categories for the chosen category. There is also a [NSFW (Not Safe For Work) category on Scrolller](https://scrolller.com/nsfw) which is not included in the script since many are not comfortable with it

* <code>-s</code>: Specifies the Reddit's sort algorithm for the chosen subreddit(s). The valid values for this parameter are <code>hot</code>, <code>new</code>, <code>controversial</code>, <code>top</code>, and <code>rising</code>. Reddit's default is <code>hot</code>. So, if not specified by the user, the script chooses <code>hot</code> as the default for for <code>-s</code> parameter. This is important since the script chooses the first wallpaper from the sorted list. As an example, if someone goes with <code>top</code> option, the wallpaper they get may not change for days or even months, even if they run the script one million times. Or, if the <code>new</code> option is chosen you may get a different wallpaper on each run of the script as it fetches the latest uploaded images by redditors, but it might not be much of an interesting image.

```
readonly SUBREDDIT_CATEGORY_ANIMALS="AnimalsBeingBros+AnimalsBeingDerps+AnimalsBeingJerks+aww+Eyebleach+likeus+rarepuppers"
readonly SUBREDDIT_CATEGORY_ART="Art+ArtPorn+Cinemagraphs+ExposurePorn+Graffiti+ImaginaryLandscapes+itookapicture"
readonly SUBREDDIT_CATEGORY_FOOD="Breadit+eatsandwiches+food+FoodPorn+grilledcheese+Pizza+slowcooking"
readonly SUBREDDIT_CATEGORY_IMAGINARY="ImaginaryBehemoths+ImaginaryCharacters+ImaginaryLandscapes+ImaginaryLeviathans+ImaginaryMindscapes+ImaginaryMonsters+ImaginaryTechnology"
readonly SUBREDDIT_CATEGORY_MAN_MADE="AbandonedPorn+carporn+CityPorn+CozyPlaces+DesignPorn+powerwashingporn+RoomPorn"
readonly SUBREDDIT_CATEGORY_NATURE="chemicalreactiongifs+EarthPorn+MacroPorn+physicsgifs+spaceporn+waterporn+WeatherGifs"
```

* <code>-n</code>: The script won't download any <code>NSFW (Not Safe For Work)</code> image by default unless this flag is passed in the parameter list.

* <code>-b</code>: Specifies the background color so in case that the downloaded image size does not match your screen size exactly, the extra space around the picture is going to be filled with this color instead. This parameter expects a color in HEX RGB format without the <code>#</code> character. For example, for red or magenta color one could pass <code>ff0000</code>, or <code>ff00ff</code> respectively.

* <code>-f</code> Anything passed as this parameter's value will be directly passed to <code>feh</code>. <code>feh</code> is an amazing tool with a lot of features. It also supports multi-display setups. As a sane default which works in both single and multi-head setups, the script passes along <code>--no-fehbg --image-bg black --bg-max</code> arguments to <code>feh</code> by default if this parameter is not specified. For more information, consult [the feh man page](https://linux.die.net/man/1/feh) by entering the following command:

{{< highlight sh >}}
$ man feh
{{< /highlight >}}

For the convenience of description, the following example tries to fetch the most recent picture submitted to any of <code>r/Art</code>, <code>r/ImaginaryLandscapes</code>, <code>r/ImaginaryMonsters</code>, or <code>r/itookapicture</code> subs. It does not care if it is safe for work or not (e.g. containing nudity, violence, ...). It fills the extra space around the wallpaper to black if there are any. And, finally it tells <code>feh</code> to not write a <code>~/.fehbg</code> file and center the wallpaper on the background. Notice that we did wrap <code>feh</code> parameters in a pair of double quotes, otherwise the script stops with an error complaining about the invalid options it was given.

{{< highlight sh >}}
$ /path/to/reddit-wallpaper.sh \
    -r r/Art+ImaginaryLandscapes+ImaginaryMonsters+itookapicture \
    -s new \
    -n \
    -b "000000" \
    -f "--no-fehbg --bg-center"

[INFO] 308 Run 'reddit-wallpaper.sh -h' for more information on available options.
[INFO] 310 Setting user agent to 'Mozilla/5.0 (X11; Linux x86_64; rv:66.0) Gecko/20100101 Firefox/66.0'...
[INFO] 314 Downloading meta file 'https://www.reddit.com/r/Art+ImaginaryLandscapes+ImaginaryMonsters+itookapicture/new.json'...
[INFO] 385 Found a wallpaper on 'r/Art+ImaginaryLandscapes+ImaginaryMonsters+itookapicture' at 'https://i.redd.it/w38h6jmwa1x21.jpg'!
[INFO] 386 Fetching 'https://i.redd.it/w38h6jmwa1x21.jpg'...
[INFO] 396 Setting desktop background color to '#000000'...
[INFO] 406 Using 'https://i.redd.it/w38h6jmwa1x21.jpg' as the desktop wallpaper...
[INFO] 416 Done!
[INFO] 417 Hope you enjoy it :)
{{< /highlight >}}

## Running through a Cron Job

I have already wrote [a guide on how to properly add a cron job on *nix systems](https://crontab.guru/), so I won't go through this in details. Fire up the <code>crontab</code> file in your favorite editor by issuing:

{{< highlight sh >}}
$ sudo -u user -g group -H crontab -e
{{< /highlight >}}

In my case, the user and group for my account is <code>mamadou</code>; so it would be:

{{< highlight sh >}}
$ sudo -u mamadou -g mamadou -H crontab -e
{{< /highlight >}}

I am running the script every <code>4</code> hours:

{{< highlight cron >}}
# At minute 0 past every 4th hour
0   */4   *   *   *   export DISPLAY=:0; /path/to/reddit-wallpaper.sh > /dev/null 2>&1
{{< /highlight >}}

If you are not familiar with the <code>crontab</code> syntax, [crontab.guru is a great visual aid](https://crontab.guru/).

Note that the <code>export DISPLAY=:0;</code> part before calling the script is mandatory since we are going to run our script through a cron job. If one forgets to export the correct display before running the script from the crontab, they will get the following error:

```
Cannot open X display!
```

On another note, due to the fact that this script is designed to run as a cron job, in addition to <code>stdout</code> and <code>stderr</code>, the scripts logs are getting passed through to the system's log file. On my Gentoo or FreeBSD instances this file is located at <code>/var/log/messages</code>. This is a sample system log output taken from the example in the previous section:

{{< highlight sh >}}
$ tail -f /var/log/messages

May  8 20:57:44 mamadou-pc REDDIT-WALLPAPER: INFO 308 Run 'reddit-wallpaper.sh -h' for more information on available options.
May  8 20:57:44 mamadou-pc REDDIT-WALLPAPER: INFO 310 Setting user agent to 'Mozilla/5.0 (X11; Linux x86_64; rv:66.0) Gecko/20100101 Firefox/66.0'...
May  8 20:57:44 mamadou-pc REDDIT-WALLPAPER: INFO 314 Downloading meta file 'https://www.reddit.com/r/Art+ImaginaryLandscapes+ImaginaryMonsters+itookapicture/new.json'...
May  8 20:57:45 mamadou-pc REDDIT-WALLPAPER: INFO 385 Found a wallpaper on 'r/Art+ImaginaryLandscapes+ImaginaryMonsters+itookapicture' at 'https://i.redd.it/w38h6jmwa1x21.jpg'!
May  8 20:57:45 mamadou-pc REDDIT-WALLPAPER: INFO 386 Fetching 'https://i.redd.it/w38h6jmwa1x21.jpg'...
May  8 20:57:47 mamadou-pc REDDIT-WALLPAPER: INFO 396 Setting desktop background color to '#000000'...
May  8 20:57:47 mamadou-pc REDDIT-WALLPAPER: INFO 406 Using 'https://i.redd.it/w38h6jmwa1x21.jpg' as the desktop wallpaper...
May  8 20:57:47 mamadou-pc REDDIT-WALLPAPER: INFO 416 Done!
May  8 20:57:47 mamadou-pc REDDIT-WALLPAPER: INFO 417 Hope you enjoy it :)
{{< /highlight >}}

## Wallpaper Cache Location

When the scripts finds and fetches an image from Reddit successfully it saves the wallpaper in the wallpaper cache located inside the user's home directory located at <code>~/.cache/reddit_wallpapers</code> in the <code>YEAR-MONTH-DAY-HOUR-MINUTE-SECONDS.EXTENSION</code> format; e.g. <code>2019-05-08-04-00-01.jpg</code>. For obvious reasons this cache grows over time, thus, one should take care of cleaning it up manually, themselves.

In the future releases, I may add various clean up options and strategies, but for the time being I am happy with keeping the cache and removing it by hand after making a copy whenever I have to.

## Obtaining the Source Code

The source code is available on both [GitHub](https://github.com/NuLL3rr0r/reddit-wallpaper/) and [GitLab](https://gitlab.com/NuLL3rr0r/reddit-wallpaper/) for the sake of convenience. In order to download the source code using <code>curl</code>, <code>aria2</code>, <code>wget</code> directly:

{{< highlight sh >}}
# GitHub
$ curl -fLo /path/to/reddit-wallpaper.sh \
    --create-dirs \
    https://raw.githubusercontent.com/NuLL3rr0r/reddit-wallpaper/master/reddit-wallpaper.sh

# GitLab
$ curl -fLo /path/to/reddit-wallpaper.sh\
    --create-dirs \
    https://gitlab.com/NuLL3rr0r/reddit-wallpaper/raw/master/reddit-wallpaper.sh
{{< /highlight >}}

It is also possible to obtain the whole repository by cloning it from <code>git</code>:

{{< highlight sh >}}
# GitHub
$ git clone \
    https://github.com/NuLL3rr0r/reddit-wallpaper.git \
    /path/to/clone/reddit-wallpaper

# GitLab
$ git clone \
    https://gitlab.com/NuLL3rr0r/reddit-wallpaper.git \
    /path/to/clone/reddit-wallpaper
{{< /highlight >}}

Lastly, for the sake of convenience, it can be copy-pasted directly from here, which is strongly discouraged due to [Pastejacking Exploitation Technique](https://github.com/dxa4481/Pastejacking):

{{< codeblock lang="bash" title="reddit-wallpaper.sh" >}}
#!/usr/bin/env bash

#  (The MIT License)
#
#  Copyright (c) 2018 - 2019 Mamadou Babaei
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

readonly FMT_OFF='\e[0m'
readonly FMT_INFO='\e[1;32m'
readonly FMT_WARN='\e[1;33m'
readonly FMT_ERR='\e[1;91m'
readonly FMT_FATAL='\e[1;31m'

readonly LOG_INFO="INFO"
readonly LOG_WARN="WARNING"
readonly LOG_ERR="ERROR"
readonly LOG_FATAL="FATAL"

readonly E_TRUE="true"
readonly E_FALSE="false"

readonly BASENAME="basename"
readonly CALLER="caller"
readonly CUT=$(which cut 2>/dev/null)
readonly CURL=$(which curl 2>/dev/null)
readonly DATE=$(which date 2>/dev/null)
readonly ECHO="echo"
readonly ECHO_FMT="echo -e"
readonly ESETROOT=$(which esetroot 2>/dev/null)
readonly FEH=$(which feh 2>/dev/null)
readonly FIREFOX=$(which firefox 2>/dev/null)
readonly HSETROOT=$(which hsetroot 2>/dev/null)
readonly JQ=$(which jq 2>/dev/null)
readonly LOGGER="logger"
readonly PERL=$(which perl 2>/dev/null)
readonly PRINT="print"
readonly REV=$(which rev 2>/dev/null)
readonly TR=$(which tr 2>/dev/null)
readonly XSETROOT=$(which xsetroot 2>/dev/null)

if [[ -n "${ESETROOT}" ]] ;
then
    readonly SETROOT=${ESETROOT}
elif [[ -n "${HSETROOT}" ]] ;
then
    readonly SETROOT=${HSETROOT}
elif [[ -n "${XSETROOT}" ]] ;
then
    readonly SETROOT=${XSETROOT}
fi

readonly SCRIPT="${BASH_SOURCE[0]}"
readonly SCRIPT_NAME="$(${BASENAME} -- "${SCRIPT}")"
readonly SYSLOG_TAG="$(${BASENAME} -- "${SCRIPT}" | ${TR} '[:lower:]' '[:upper:]' | ${REV} | ${CUT} -d "." -f2- | ${REV})"

readonly SUBREDDIT_CATEGORY_ANIMALS="AnimalsBeingBros+AnimalsBeingDerps+AnimalsBeingJerks+aww+Eyebleach+likeus+rarepuppers"
readonly SUBREDDIT_CATEGORY_ART="Art+ArtPorn+Cinemagraphs+ExposurePorn+Graffiti+ImaginaryLandscapes+itookapicture"
readonly SUBREDDIT_CATEGORY_FOOD="Breadit+eatsandwiches+food+FoodPorn+grilledcheese+Pizza+slowcooking"
readonly SUBREDDIT_CATEGORY_IMAGINARY="ImaginaryBehemoths+ImaginaryCharacters+ImaginaryLandscapes+ImaginaryLeviathans+ImaginaryMindscapes+ImaginaryMonsters+ImaginaryTechnology"
readonly SUBREDDIT_CATEGORY_MAN_MADE="AbandonedPorn+carporn+CityPorn+CozyPlaces+DesignPorn+powerwashingporn+RoomPorn"
readonly SUBREDDIT_CATEGORY_NATURE="chemicalreactiongifs+EarthPorn+MacroPorn+physicsgifs+spaceporn+waterporn+WeatherGifs"

readonly DEFAULT_SUBREDDIT="r/${SUBREDDIT_CATEGORY_ART}+${SUBREDDIT_CATEGORY_IMAGINARY}"
readonly DEFAULT_SORT_BY="hot"
readonly DEFAULT_IS_NSFW_OK="${E_FALSE}"
readonly DEFAULT_BACKGROUND_COLOR="282828"
readonly DEFAULT_FEH_ARGS="--no-fehbg --image-bg black --bg-max"

readonly DEFAULT_FIREFOX_VERSION_STRING="Mozilla Firefox 66.0"

readonly LOCAL_WALLPAPER_DIR="${HOME}/.cache/reddit_wallpapers/"
readonly LOCAL_WALLPAPER_NAME="$(${DATE} +%Y-%m-%d-%H-%M-%S)"

function usage() {
    readonly local message="${1}"

    ${ECHO}

    if [[ -n "${message}" ]] ;
    then
        err "${message}${FMT_OFF}"
        ${ECHO}
    fi

    ${ECHO_FMT} "${FMT_INFO}Correct usage:${FMT_OFF}"
    ${ECHO}
    ${ECHO_FMT} "    ${FMT_INFO}${SCRIPT_NAME} -h | [-r {r/subreddit}] [-s {sorty by}] [-n] [-b {background color}] [-f 'feh args']${FMT_OFF}"
    ${ECHO}
    ${ECHO_FMT} "    ${FMT_INFO}-h: shows this usage note"
    ${ECHO}
    ${ECHO_FMT} "    ${FMT_INFO}-r: subreddit name or names prefixed with r/ and combined by a + sign (e.g. r/Art or r/Art+ArtPorn; default: ${DEFAULT_SUBREDDIT})${FMT_OFF}"
    ${ECHO}
    ${ECHO_FMT} "    ${FMT_INFO}-s: reddit sort algorithm (e.g. hot, new, controversial, top, rising; default: ${DEFAULT_SORT_BY})${FMT_OFF}"
    ${ECHO}
    ${ECHO_FMT} "    ${FMT_INFO}-n: allow nsfw wallpapers (no nsfw wallpaper is allowed by default, unless this flag is passed)${FMT_OFF}"
    ${ECHO}
    ${ECHO_FMT} "    ${FMT_INFO}-b: hex rgb color in 'ffffff' format (default: ${DEFAULT_BACKGROUND_COLOR})${FMT_OFF}"
    ${ECHO}
    ${ECHO_FMT} "    ${FMT_INFO}-f: feh arguments to pass; run 'man feh' for a list of available options (default: ${DEFAULT_FEH_ARGS})${FMT_OFF}"
    ${ECHO}

    if [[ -n "${message}" ]] ;
    then
        exit 1
    else
        exit 0
    fi
}

function log()
{
    local log_type=$1; shift
    local line=$1; shift
    local fmt=$1; shift

    if [[ -n "$1" && -n "$@" ]] ;
    then
        ${ECHO_FMT} "${fmt}[${log_type}] ${line} $@${FMT_OFF}"
        ${LOGGER} -t "${SYSLOG_TAG}" "${log_type} ${line} $@"
    else
        ${ECHO_FMT} "${FMT_WARN}[${LOG_WARN}] ${line} A null log detected!${FMT_OFF}"
        ${LOGGER} -t "${SYSLOG_TAG}" "${LOG_WARN} ${line} A null log detected!"
    fi 
}

function info()
{
    local line=$( "${ECHO}" $( "${CALLER}" 0 ) | "${CUT}" -d " " -f1 )

    log "${LOG_INFO}" "${line}" "$FMT_INFO" "$@"
}

function warn()
{
    local line=$( "${ECHO}" $( "${CALLER}" 0 ) | "${CUT}" -d " " -f1 )

    log "${LOG_WARN}" "${line}" "${FMT_WARN}" "$@"
}

function err()
{
    local line=$( "${ECHO}" $( "${CALLER}" 0 ) | "${CUT}" -d " " -f1 )

    log "${LOG_ERR}" "${line}" "${FMT_ERR}" "$@"
}

function fatal()
{
    local line=$( "${ECHO}" $( "${CALLER}" 0 ) | "${CUT}" -d " " -f1 )

    log "${LOG_FATAL}" "${line}" "${FMT_FATAL}" "$@"

    exit 1
}

if [[ -z "${CUT}" ]] ;
then
    fatal "Could not find command cut!"
fi

if [[ -z "${CURL}" ]] ;
then
    fatal "Could not find command curl!"
fi

if [[ -z "${DATE}" ]] ;
then
    fatal "Could not find command date!"
fi

if [[ -z "${FEH}" ]] ;
then
    fatal "Could not find command feh!"
fi

if [[ -z "${JQ}" ]] ;
then
    fatal "Could not find command jq!"
fi

if [[ -z "${PERL}" ]] ;
then
    fatal "Could not find command perl!"
fi

if [[ -z "${REV}" ]] ;
then
    fatal "Could not find command rev!"
fi

if [[ -z "${SETROOT}" ]] ;
then
    fatal "Could not find any setroot command!"
fi

if [[ -z "${TR}" ]] ;
then
    fatal "Could not find command tr!"
fi

while getopts ":h :r: :s: :n :b: :f:" ARG;
do
    case ${ARG} in
        h)
            usage
            ;;
        r)
            SUBREDDIT=${OPTARG}
            ;;
        s)
            SORT_BY=${OPTARG}
            ;;
        n)
            IS_NSFW_OK="${E_TRUE}"
            ;;
        b)
            BACKGROUND_COLOR="#${OPTARG}"
            ;;
        f)
            FEH_ARGS="${OPTARG}"
            ;;
        \?)
            usage "Invalid option: '-${OPTARG}'!"
        ;;
    esac
done

if [[ -z ${SUBREDDIT} ]] ;
then
    SUBREDDIT=${DEFAULT_SUBREDDIT}
fi

readonly SUBREDDIT_REGEX="^r\/([a-zA-Z0-9_+]+)$"

if [[ ! "${SUBREDDIT}" =~ ${SUBREDDIT_REGEX} ]] ;
then
    fatal "Invalid subreddit name! use r/subreddit or r/subreddit1+subreddit2 format!"
fi

if [[ -z ${SORT_BY} ]] ;
then
    SORT_BY=${DEFAULT_SORT_BY}
fi

if [[ "${SORT_BY}" != "hot"
        && "${SORT_BY}" != "new"
        && "${SORT_BY}" != "controversial"
        && "${SORT_BY}" != "top"
        && "${SORT_BY}" != "rising" ]] ;
then
    fatal "Invalid reddit sort algorithm!"
fi

if [[ -z ${IS_NSFW_OK} ]] ;
then
    NSFW_OK=${DEFAULT_IS_NSFW_OK}
fi

if [[ -z ${BACKGROUND_COLOR} ]] ;
then
    BACKGROUND_COLOR="#${DEFAULT_BACKGROUND_COLOR}"
fi

readonly BACKGROUND_COLOR_REGEX="^#([0-9a-f]{6})$"

if [[ ! "${BACKGROUND_COLOR}" =~ ${BACKGROUND_COLOR_REGEX} ]] ;
then
    fatal "Invalid background color format! the only accepted format is 'ffffff'!"
fi

if [[ -z ${FEH_ARGS} ]] ;
then
    FEH_ARGS=${DEFAULT_FEH_ARGS}
fi

if [[ -z "${FIREFOX}" ]] ;
then
    warn "Firefox executable not found!"
    readonly FIREFOX_VERSION_STRING="${DEFAULT_FIREFOX_VERSION_STRING}"
    warn "Setting Firefox version string to: ${FIREFOX_VERSION_STRING}"
else
    readonly FIREFOX_VERSION_STRING=$(${FIREFOX} -version)
fi

readonly FIREFOX_VERSION_NUMBER=$(${ECHO} "${FIREFOX_VERSION_STRING}" | ${PERL} -nle "m/[-+]?([0-9]*\.[0-9]+|[0-9]+)/; ${PRINT} \$1")
readonly FIREFOX_USER_AGENET="Mozilla/5.0 (X11; Linux x86_64; rv:${FIREFOX_VERSION_NUMBER}) Gecko/20100101 Firefox/${FIREFOX_VERSION_NUMBER}"

info "Run '${SCRIPT_NAME} -h' for more information on available options."

info "Setting user agent to '${FIREFOX_USER_AGENET}'..."

readonly JSON_URL="https://www.reddit.com/${SUBREDDIT}/${SORT_BY}.json"

info "Downloading meta file '${JSON_URL}'..."

readonly JSON_CONTENT=$(${CURL} -A "${FIREFOX_USER_AGENET}" -sSL ${JSON_URL})
RC=$?

if [[ $RC -ne 0 ]] ;
then
    fatal "Subreddit meta file download has failed!"
fi

readarray JSON_POSTS <<< "$(${ECHO} "${JSON_CONTENT}" | ${JQ} --compact-output '.data.children[]')"
RCS=(${PIPESTATUS[*]})

if [[ ${RCS[0]} -ne 0 || ${RCS[1]} -ne 0 ]] ;
then
    fatal "Failed to parse the subreddit's meta file!"
fi

readonly URL_REGEX="^(https?://)?(([0-9a-z_!~*'().&=+$%-]+: )?[0-9a-z_!~*'().&=+$%-]+@)?(([0-9]{1,3}\\.){3}[0-9]{1,3}|([0-9a-z_!~*'()-]+\\.)*([0-9a-z][0-9a-z-]{0,61})?[0-9a-z]\\.[a-z]{2,6})(:[0-9]{1,4})?((/?)|(/[0-9a-z_!~*'().;?:@&=+$,%#-]+)+/?)\\.(png|apng|jpg|jpeg|jpe|jif|jfif|jfi|gif|tiff|tif)$"

FOUND_A_SUITABLE_WALLPAPER="${E_FALSE}"

for post in "${JSON_POSTS[@]}" ;
do
    if [[ "${IS_NSFW_OK}" != "${E_TRUE}" ]] ;
    then
        IS_OVER_18_POST=$(${ECHO} "${post}" | ${JQ} --compact-output '.data.over_18')
        RCS=(${PIPESTATUS[*]})

        if [[ ${RCS[0]} -ne 0 || ${RCS[1]} -ne 0 ]] ;
        then
            fatal "Failed to parse the subreddit's meta file!"
        fi

        if [[ "${IS_OVER_18_POST}" == "${E_TRUE}" ]] ;
        then
            continue
        fi
    fi

    WALLPAPER_URL=$(${ECHO} "${post}" | ${JQ} --raw-output '.data.url')
    RCS=(${PIPESTATUS[*]})

    if [[ ${RCS[0]} -ne 0 || ${RCS[1]} -ne 0 ]] ;
    then
        fatal "Failed to parse the subreddit's meta file!"
    fi

    if [[ ! "${WALLPAPER_URL}" =~ ${URL_REGEX} ]] ;
    then
        continue
    fi

    WALLPAPER_EXTENSION="${WALLPAPER_URL##*.}"

    if [[ -z "${WALLPAPER_EXTENSION}" ]] ;
    then
        continue
    fi

    FOUND_A_SUITABLE_WALLPAPER="${E_TRUE}"
    break;
done

if [[ "${FOUND_A_SUITABLE_WALLPAPER}" != "${E_TRUE}" ]] ;
then
    fatal "Could not find a suitable wallpaper on '${SUBREDDIT}'!"
fi

readonly LOCAL_WALLPAPER_PATH="${LOCAL_WALLPAPER_DIR}/${LOCAL_WALLPAPER_NAME}.${WALLPAPER_EXTENSION}"

info "Found a wallpaper on '${SUBREDDIT}' at '${WALLPAPER_URL}'!"
info "Fetching '${WALLPAPER_URL}'..."

${CURL} -fLo "${LOCAL_WALLPAPER_PATH}" --create-dirs ${WALLPAPER_URL} > /dev/null 2>&1
RC=$?

if [[ $RC -ne 0 ]] ;
then
    fatal "Failed to fetch the wallpaper file from '${WALLPAPER_URL}'!"
fi

info "Setting desktop background color to '${BACKGROUND_COLOR}'..."

${SETROOT} -solid "${BACKGROUND_COLOR}" > /dev/null 2>&1 &
RC=$?

if [[ $RC -ne 0 ]] ;
then
    fatal "Failed to set the background color to '${BACKGROUND_COLOR}'!"
fi

info "Using '${WALLPAPER_URL}' as the desktop wallpaper..."

${FEH} ${FEH_ARGS} "${LOCAL_WALLPAPER_PATH}" > /dev/null 2>&1 &
RC=$?

if [[ $RC -ne 0 ]] ;
then
    fatal "Failed to apply '${LOCAL_WALLPAPER_PATH}' as the desktop background image!"
fi

info "Done!"
info "Hope you enjoy it :)"
{{< /codeblock >}}
