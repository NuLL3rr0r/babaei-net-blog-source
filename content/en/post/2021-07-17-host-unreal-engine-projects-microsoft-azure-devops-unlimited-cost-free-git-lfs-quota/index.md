+++
title = "Host Unreal Engine 4 projects on Microsoft Azure DevOPS with unlimited cost-free Git LFS quota"
slug = "host-unreal-engine-projects-microsoft-azure-devops-unlimited-cost-free-git-lfs-quota"
date = 2021-07-17T16:12:00+02:00
tags = [ "Azure", "Azure DevOPS", "Bash", "C", "C++", "Clang", "Cross-platform", "csh", "Epic Games", "Game Development", "Game Programming", "gamedev", "Git", "Git Large File Storage", "Git LFS", "indiedev", "Linux", "LLVM", "Microsoft", "MSVC", "Perforce", "SCM", "sh", "Shell Scripting", "Subversion", "SVN", "UDK", "UE4", "Unreal Engine", "UnrealScript", "VC++", "Visual C++", "Visual Stuio", "Windows" ]
toc = true
+++

{{< figure src="/blog/host-unreal-engine-projects-microsoft-azure-devops-unlimited-cost-free-git-lfs-quota/unreal-engine-microsoft-azure-devops-git-lfs.webp" alt="Host Unreal Engine 4 projects on Microsoft Azure DevOPS with unlimited cost free Git LFS quota" caption="Host Unreal Engine 4 projects on Microsoft Azure DevOPS with unlimited cost free Git LFS quota" >}}

**UPDATE 1 [2021/07/25]**: _It seems that Git LFS is able to resume your pushes after a network failure. At least it's like that on Microsoft Azure DevOPS. So, it should be totally redundant to divide huge commits into smaller ones. How have I noticed this? Today, I pushed a huge single commit (around 53GBs) and it failed at 39GB due to a connection error without me noticing it for some time. A few hours later, when I made another attempt by issuing the push command again, it picked up and resumed the push at 39GB, which was really exciting._

**UPDATE 2 [2021/07/25]**: _After pushing the repository to Azure DevOPS, if you find your self stuck in git pull without doing anything, the following command will fix the consecutive pulls:_

{{< highlight sh >}}
$ git pull origin master
{{< /highlight >}}

<hr />

Among the gamedev industry, it's a well-known fact that Unreal Engine projects sizes have always been huge and a pain to manage properly. And it becomes more painful by the day as your project moves forward and grows in size. Some even keep the Engine source and its monstrous binary dependencies inside their source control management software. In case you are a AAA game development company or you are working for one, there's probably some system in place with an unlimited quota to take care of that. But, for most of us indie devs, or individual hobbyists, it seems there are not lots of affordable options, especially that your team is scattered across the globe.

There are plenty of costly solutions to keep UE4 projects under source control; ranging from maintaining a local physical server or renting a VPS with plenty of space on the cloud, equipped with a self-hosted Git, SVN, or Perforce, to use cloud SCM providers such as GitHub, GitLab, BitBucket, or Perforce. Since I prefer cloud SCM providers and Git + Git LFS (which also supports file locking), let's take a look at some popular ones such as GitHub and GitLab.

GitHub for one, provides data packs, but the free offering is far from enough for collaborative UE4 projects:

{{< blockquote author="github.com" link="https://docs.github.com/en/billing/managing-billing-for-git-large-file-storage/about-billing-for-git-large-file-storage" title="About billing for Git Large File Storage" >}}
Every account using Git Large File Storage receives 1 GB of free storage and 1 GB a month of free bandwidth. If the bandwidth and storage quotas are not enough, you can choose to purchase an additional quota for Git LFS. Unused bandwidth doesn't roll over month-to-month.

...

Additional storage and bandwidth is offered in a single data pack. One data pack costs $5 per month, and provides a monthly quota of 50 GB for bandwidth and 50 GB for storage. You can purchase as many data packs as you need. For example, if you need 150 GB of storage, you'd buy three data packs.
{{< /blockquote >}}

For GitLab, although the initial generous <code>10GB</code> repository size is way beyond the <code>1GB</code> repository size offer by GitHub, the LFS pricing is insanely high:

{{< blockquote author="gilab.com" link="https://about.gitlab.com/pricing/licensing-faq/#about-supplemental-storage" title="Licensing and subscription FAQ, About Supplemental Storage" >}}
1. Additional repository storage for a namespace (group or personal) is sold in annual subscriptions of $60 USD/year in increments of 10GB. This storage accounts for the size calculated from Repositories, which includes the git repository itself and any LFS objects.

2. When adding storage to an existing subscription, you will be charged the prorated amount for the remaining term of your subscription. (ex. If your subscription ends in 6 months and you buy storage, you will be charge for 6 months of the storage subscription, i.e. $30 USD)
{{< /blockquote >}}

Well, before this all get you disappointed, let's hear the good news from the Microsoft Azure DevOPS team:

{{< blockquote author="microsoft.com" link="https://docs.microsoft.com/en-us/azure/devops/repos/git/limits?view=azure-devops" title="Git limits" >}}
In uncommon circumstances, repositories may be larger than 10GB. For instance, the Windows repository is at least 300GB. For that reason, we do not have a hard block in place. If your repository grows beyond 10GB, consider using Git-LFS, Scalar, or Azure Artifacts to refactor your development artifacts.
{{< /blockquote >}}

Before we proceed any further, there are some catches to consider about Microsoft Azure DevOPS:

__1__. The maximum Git repository size is <code>10GB</code>, which considering that we keep binary assets and huge files in LFS, is way beyond any project's actual needs. For Git LFS it seems that [Microsoft since at least 2015 has been providing unlimited free storage](https://devblogs.microsoft.com/devops/announcing-git-lfs-on-all-vso-git-repos/). For comparison, the engine source code for <code>4.27</code> is <code>1.4GB</code>, which in turn when it's getting committed to the git repo becomes less than <code>230MB</code>:

{{< highlight sh >}}
$ cd /path/to/ue4.27/source

$ du -h
1.4G	.

$ git init
$ git add .
$ git commit -m "add unreal engine 4.27 source code"

$ git count-objects -vH

count: 97545
size: 900.25 MiB
in-pack: 110815
packs: 1
size-pack: 227.80 MiB
prune-packable: 97545
garbage: 0
size-garbage: 0 bytes
{{< /highlight >}}

__2__. The maximum push size is limited to <code>5GB</code> at a time. The <code>5GB</code> limit is only for files in the actual repository and it won't affect LFS objects. Thus, there are no limits for LFS objects' pushes. Despite that, if your internet connection is not stable, you could divide your files into multiple commits and push them separately. For example, the initial git dependencies for UE <code>4.27</code> is around <code>40GB</code> spanned across <code>~70,000</code> files. Instead of committing and pushing a <code>40GB</code> chunk all at once, one could divide that into multiple commits and push those commits one by one using the following command:

{{< highlight sh >}}
$ git rev-list --reverse master \
    | ruby -ne 'i ||= 0; i += 1; puts $_ if i % 1 == 0' \
    | xargs -I{} git push origin +{}:refs/heads/master
{{< /highlight >}}

__3__. Sadly, at the moment Azure DevOPS does not support LFS over SSH. So, you are bound to git push/pull over https, which for some might be annoying. Especially, that it keeps asking for the https token <code>3</code> consecutive times on any push or pull!

{{< blockquote author="microsoft.com" link="https://docs.microsoft.com/en-us/azure/devops/repos/git/use-ssh-keys-to-authenticate?view=azure-devops" title="Use SSH key authentication" >}}
Q: I'm using Git LFS with Azure DevOps Services and I get errors when pulling files tracked by Git LFS.

A: Azure DevOps Services currently doesn't support LFS over SSH. Use HTTPS to connect to repos with Git LFS tracked files.
{{< /blockquote >}}

__4__. Last but not least, there is an issue with the Microsoft implementation of LFS, which rejects large LFS objects and spits out a bunch of HTTP <code>413</code> and <code>503</code> errors at the end of your <code>git push</code>. It happened to me when I was pushing <code>40GB</code> of UE4 binary dependencies. The weird thing was I tried twice and both times it took a few good hours till the end of the push operation and based on measuring the bandwidth usage, the LFS upload size appeared to be more than the actual upload size. According to some answers on [this GitHub issue](https://github.com/MicrosoftDocs/azure-devops-docs/issues/4179) and [this Microsoft developer community question](https://developercommunity.visualstudio.com/t/git-lfs-push-got-413-error/867488), it seems the solution is running the following command inside the root of your local repository, before any git pull/push operations:

{{< highlight sh >}}
$ git config http.version HTTP/1.1
{{< /highlight >}}

Well, not only it did the trick and worked like a charm, but also the push time on the following git push dropped dramatically to <code>30</code> minutes for that hefty <code>40GB</code> UE4 binary dependencies.

OK, after getting ourselves familiarized with all the limits, if you deem this solution a worthy one for managing UE4 projects along with the engine source in the same repository, in the rest of this blog post I'm going to share my experiences and a script to keep the engine updated with ease using a Git + LFS setup.

<!--more-->

## OK! Let's get started

OK, in this tutorial I assume we are going to create a new project from scratch. Migration is a similar story if one learns how to set up a Git LFS repository from scratch. We briefly go over that at the end.

In the rest of this tutorial, I will name the new project <code>MamadouArchives</code>.

## Requirements

The script that I am going to represent in this tutorial is a Bash shell script and runs on Linux. I haven't tested it on Git Bash for Windows. It may work on macOS or Microsoft Windows or not. In fact, you don't even need this script for following this tutorial. It could all be done manually, or it could be automated using your favorite automation scripting language once you know what are you doing.

In order to effectively follow this tutorial and use the script, you may need the following:

* Bash
* Git + LFS
* [rsync](https://rsync.samba.org/)
* A github account correctly setup with access to [Unreal Engine's repository on Epic's official GitHub account](https://github.com/EpicGames/UnrealEngine)
* A [Microsoft Azure DevOPS](https://azure.microsoft.com/en-us/services/devops/) account

## The directory structure

```
MamadouArchives (the project name containing the engine source + binary dependencies + the actual UE4 project)
  │
  ├── .git/ (Git metadata and objects database directory)
  │     │
  │     └── *
  │
  ├── Engine/
  │     │
  │     └── *
  │
  ├── FeaturePacks/
  │     │
  │     └── *
  │
  ├── MamadouArchives/ (your actual UE4 project sits here)
  │     │
  │     ├── Config/
  │     │     │
  │     │     └── *
  │     │
  │     ├── Content/
  │     │     │
  │     │     └── *
  │     │
  │     ├── Plugins/
  │     │     │
  │     │     └── *
  │     │
  │     ├── Source/
  │     │     │
  │     │     └── *
  │     │
  │     ├── .gitignore (your project's .gitignore, which overrides the the engine one)
  │     │
  │     ├── MamadouArchives.uproject
  │     │
  │     └── README.md
  │
  ├── Samples/
  │     │
  │     └── *
  │
  ├── Templates/
  │     │
  │     └── *
  │
  ├── .editorconfig
  │
  ├── .gitattributes (used by Git LFS to keep track of the LFS objects)
  │
  ├── .gitignore
  │
  ├── .tgitconfig
  │
  ├── .ue4dependencies
  │
  ├── cpp.hint
  │
  ├── GenerateProjectFiles.bat
  │
  ├── GenerateProjectFiles.command
  │
  ├── GenerateProjectFiles.sh
  │
  ├── LICENSE.md
  │
  ├── README.md
  │
  ├── Setup.bat
  │
  ├── Setup.command
  │
  ├── Setup.sh
  │
  ├── UE4Games.uprojectdirs (scanned by UnrealBuildTool in order to find projects)
  │
  └── UpdateEngine.sh (the engine update script from this tutorial)
```

## Three copies of the Engine

OK, in order to keep things less complex and as easy as we could, we need three copies of the engine (I use the actual paths on my computer):

* <code>/opt/UnrealEngine</code>: the untouched engine source from Epic Games GitHub account which tracks the Unreal Engine development.
* <code>~/dev/MamadouArchives</code>: the actual engine and project directory I build and work with daily. One should never ever run the engine update script from this directory, or there may be hazardous effects ¯\\\_(ツ)_/¯. See the next one for more details.
* <code>~/dev/MamadouArchives-Sync</code>: due to using <code>rsync</code> since the script has destructive effects on any uncommitted changes, or is cleaning up the engine builds, we use this intermediary copy of our project which tracks our project's development. We run the engine update script only from this directory and git pull/push this repository in order to keep it in sync with the actual project <code>/dev/MamadouArchives</code>.

__Note__: Running the engine update script gives you the following warning before actually doing anything. It's safe until you press <code>y</code>. And, by default the answer is no:

{{< highlight plain >}}
WARNING: RUNNING THIS SCRIPT MAY HAVE DESTRUCTIVE EFFECTS
ON THIS REPOSITORY!

MAKE A BACKUP FIRST, BEFORE YOU PROCEED ANY FURTHER!

Are you sure? [y/N] 
{{< /highlight >}}

## The UE4 update script

Here is the aforementioned engine update script we are going to use in a moment. Just remember we have to modify a few variables later on.

{{< codeblock lang="bash" title="UpdateEngine.sh" line_numbers="true" >}}
#!/usr/bin/env bash

#  Author: Mamadou Babaei <info@babaei.net>
#
#  (The MIT License)
#
#  Copyright (c) 2019 - 2021 Mamadou Babaei
#  Copyright (c) 2021 @mamadou_archive
#  Copyright (c) 2019 - 2021 @Barandazstorm
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

set -e

readonly UPSTREAM_ENGINE_DIR="/opt/UnrealEngine"
readonly PROJECT_DIR_NAME="MamadouArchives"
readonly UPDATE_SCRIPT_NAME="$(basename "$0")"
readonly PROJECT_ENGINE_DIR="$(dirname $(realpath "$0"))"
readonly GIT_ATTRIBUTES_FILE_NAME=".gitattributes"
readonly GIT_IGNORE_FILE_NAME=".gitignore"
readonly PROJECT_ENGINE_GIT_ATTRIBUTES_FILE="${PROJECT_ENGINE_DIR}/${GIT_ATTRIBUTES_FILE_NAME}"
readonly UPSTREAM_ENGINE_GIT_IGNORE_FILE="${UPSTREAM_ENGINE_DIR}/${GIT_IGNORE_FILE_NAME}"
readonly PROJECT_ENGINE_SOURCE_CHANGELIST_GIT_ADD_SCRIPT="/tmp/${PROJECT_DIR_NAME}-engine-source-changelist-git-add.sh"
readonly PROJECT_ENGINE_DEPS_GIT_FORCE_ADD_SCRIPT="/tmp/${PROJECT_DIR_NAME}-engine-deps-git-force-add.sh"

function displayWarning() {
    echo ""
    echo "WARNING: RUNNING THIS SCRIPT MAY HAVE DESTRUCTIVE EFFECTS"
    echo "ON THIS REPOSITORY!"
    echo ""
    echo "MAKE A BACKUP FIRST, BEFORE YOU PROCEED ANY FURTHER!"
    echo ""

    read -p "Are you sure? [y/N] " -n 1 -r

    echo ""
    echo ""

    if [[ ! $REPLY =~ ^[Yy]$ ]] ;
    then
        echo "Aborted!"

        [[ "$0" = "$BASH_SOURCE" ]] && exit 1 || return 1
    fi

    update
}

function update() {
    echo "Cleaning up the upstream engine '${UPSTREAM_ENGINE_DIR}'..." \
        && echo "" \
        && cd "${UPSTREAM_ENGINE_DIR}" \
        && git rm --cached -r . \
        && git clean -dfx \
        && git reset --hard \
        && echo "" \
        && echo "Updating the upstream engine '${UPSTREAM_ENGINE_DIR}'..." \
        && echo "" \
        && cd "${UPSTREAM_ENGINE_DIR}" \
        && git pull \
        && bash Setup.sh \
        && echo "" \
        && echo "Syncing the ${PROJECT_DIR_NAME}'s engine '${PROJECT_ENGINE_DIR}' with upstream '${UPSTREAM_ENGINE_DIR}'..." \
        && echo "" \
        && cd "${UPSTREAM_ENGINE_DIR}" \
        && rsync -avze --delete \
            --exclude=".git" \
            --exclude="UE4Games.uprojectdirs" \
            --exclude="${UPDATE_SCRIPT_NAME}" \
            --exclude="${PROJECT_DIR_NAME}" \
            "${UPSTREAM_ENGINE_DIR}/" "${PROJECT_ENGINE_DIR}/" \
        && echo "" \
        && echo "Extracting the engine's source changelist from '${PROJECT_ENGINE_DIR}'..." \
        && echo "" \
        && cd "${PROJECT_ENGINE_DIR}" \
        && git diff --name-only -z | xargs -0 -I % echo "printf 'git add -f \"%\"\n'" | sh > "${PROJECT_ENGINE_SOURCE_CHANGELIST_GIT_ADD_SCRIPT}" \
        && chmod a+x "${PROJECT_ENGINE_SOURCE_CHANGELIST_GIT_ADD_SCRIPT}" \
        && echo "" \
        && echo "Staging the engine's source changes inside '${PROJECT_ENGINE_DIR}'..." \
        && echo "" \
        && cd "${PROJECT_ENGINE_DIR}" \
        && "${PROJECT_ENGINE_SOURCE_CHANGELIST_GIT_ADD_SCRIPT}" \
        && echo "" \
        && echo "Extracting the engine's git dependencies list from '${UPSTREAM_ENGINE_DIR}'..." \
        && echo "" \
        && cd "${PROJECT_ENGINE_DIR}" \
        && echo "# UE4 Git Dependencies" >> "${PROJECT_ENGINE_GIT_ATTRIBUTES_FILE}" \
        && cd "${UPSTREAM_ENGINE_DIR}" \
        && rm -f "${UPSTREAM_ENGINE_GIT_IGNORE_FILE}" \
        && git ls-files -z -o --exclude-standard | xargs -0 -I % echo "printf '\"%\" filter=lfs diff=lfs merge=lfs -text\n'" | sh >> "${PROJECT_ENGINE_GIT_ATTRIBUTES_FILE}" \
        && echo "#/usr/bin/env bash" > "${PROJECT_ENGINE_DEPS_GIT_FORCE_ADD_SCRIPT}" \
        && git ls-files -z -o --exclude-standard | xargs -0 -I % echo "printf 'git add -f \"%\"\n'" | sh >> "${PROJECT_ENGINE_DEPS_GIT_FORCE_ADD_SCRIPT}" \
        && chmod a+x "${PROJECT_ENGINE_DEPS_GIT_FORCE_ADD_SCRIPT}" \
        && cd "${UPSTREAM_ENGINE_DIR}" \
        && git checkout "${GIT_IGNORE_FILE_NAME}" \
        && echo "" \
        && echo "Staging the engine's git dependencies inside '${PROJECT_ENGINE_DIR}'..." \
        && echo "" \
        && cd "${PROJECT_ENGINE_DIR}" \
        && "${PROJECT_ENGINE_DEPS_GIT_FORCE_ADD_SCRIPT}" \
        && git add -f "${GIT_ATTRIBUTES_FILE_NAME}" \
        && echo "" \
        && echo "Done!" \
        && echo ""
}

displayWarning
{{< /codeblock >}}

## The steps

__1__. Clone the Unreal Engine source code from the official GitHub repository. Here we check out the <code>4.27</code> branch:

{{< highlight sh >}}
$ git clone git@github.com:EpicGames/UnrealEngine.git -b 4.27 /opt/UnrealEngine
{{< /highlight >}}

__2__. Create your project's git repository on Microsoft Azure DevOPS and generate your https access token.

__3__. Prepare the initial intermediary local git repository we are going to use for syncing the engine source code with upstream:

{{< highlight sh >}}
$ rsync -avze --delete \
    --exclude='.git' \
    /opt/UnrealEngine/ ~/dev/MamadouArchives-Sync/
{{< /highlight >}}

__WARNING__: Never run this command ever again after this step!

__4__. Initialize your project's git repository, commit the engine source, and push it to Microsoft Azure DevOPS. As we mentioned earlier we have to use <code>https</code> instead of <code>ssh</code> and you might be asked for password <code>3</code> times:

{{< highlight sh >}}
$ cd ~/dev/MamadouArchives-Sync/
$ git init
$ git remote add origin https://SOME-ORGANIZATION@dev.azure.com/SOME-ORGANIZATION/MamadouArchives/_git/MamadouArchives
$ git add -f .
$ git commit -m "add unreal engine 4.27 source code"
$ git push -u origin --all
{{< /highlight >}}

__Note__: In case one needs to store their git credentials on their computer they could simply do:

{{< highlight sh >}}
$ git config credential.helper store
{{< /highlight >}}

This will add the following to <code>.git/config</code>:

{{< highlight sh >}}
[credential]
	helper = store
{{< /highlight >}}

Upon your next pull/push, after typing your password once, it will be saved in plain text inside <code>~/.git-credentials</code> in the following format:

{{< highlight sh >}}
https://SOME-ORGANIZATION:PASSWORD@dev.azure.com
{{< /highlight >}}

__WARNING__: Although the permission for this file is set to <code>0600</code> by Git, which means only the owner can read/write it. This is not a recommended approach for saving Git credentials, at all! Any malicious program running by the user owning <code>~/.git-credentials</code> could steal your Git credentials.

{{< highlight sh >}}
$ ls -lah ~/.git-credentials
-rw------- 1 mamadou mamadou 88 Jul 17 09:18 /home/mamadou/.git-credentials
{{< /highlight >}}

There are better ways to store Git credentials, but, it is out of the scope of this article.

__5__. Add the script from the previous section to the root of the repository, and modify the following variables with your project directory name inside the root directory and the Epic Game's untouched engine source path:

{{< codeblock lang="bash" title="Updating UpdateEngine.sh Important Variables" line_numbers="false" >}}
readonly UPSTREAM_ENGINE_DIR="/opt/UnrealEngine"
readonly PROJECT_DIR_NAME="MamadouArchives"
{{< /codeblock >}}

For example in the above, Epic Game's untouched engine source code is inside <code>/opt/UnrealEngine</code> on my computer. For the project's directory name I am going to create my project inside <code>~/dev/MamadouArchives-Sync/</code> with the name <code>MamadouArchives</code>. So, it will be located here on my computer: <code>~/dev/MamadouArchives-Sync/MamadouArchives</code>.

__6__. Make the script executable, then stage, commit, and push the script to the remote repository on Microsoft Azure DevOPS:

{{< highlight sh >}}
$ chmod a+x UpdateEngine.sh
$ git add UpdateEngine.sh
$ git commit -m "add the engine update script"
$ git push
{{< /highlight >}}

__7__. Prepare and initialize Git LFS for our repository. And do not forget to run the <code>HTTP/1.1</code> fix for large LFS objects on the repository:

{{< highlight sh >}}
$ git lfs install
$ git config http.version HTTP/1.1
{{< /highlight >}}

This will add the following to <code>.git/config</code>:

{{< highlight sh >}}
[http]
	version = HTTP/1.1
{{< /highlight >}}

__8__. Now, in order to fetch the engine's binary dependencies, run the script by issuing either:

{{< highlight sh >}}
$ cd ~/dev/MamadouArchives-Sync/
$ ./UpdateEngine.sh
{{< /highlight >}}

Or (because the script is aware of how to find its repository path, one code safely run it like this):

{{< highlight sh >}}
$ ~/dev/MamadouArchives-Sync/UpdateEngine.sh
{{< /highlight >}}

__9__. It may take a long time for the script to finish. If everything goes fine, we can commit and push the engine's binary dependencies. Note that the script does not so automatically because I prefer to review it before committing or pushing it. But, the script stage the retrieved new or updated files for you automatically. So:

{{< highlight sh >}}
$ git status           # in order to see the changes
$ git lfs ls-files -s  # in order to list LFS tracked files with size
$ git lfs track        # another way to list LFS tracked files
$ git commit -m "add unreal engine 4.27 binary dependencies"
$ git push
{{< /highlight >}}

__10__. Form now on, you can always follow steps <code>#8</code> <code>#9</code> in order to keep your engine updated.

__11__. Create a UE4 project with the desired name, in my case <code>MamadouArchives</code>, or copy over an already existing project (without the <code>.git</code> directory if it's already hosted on git) into your newly created repository. e.g. <code>~/dev/MamadouArchives-Sync/</code>.

__12__. Now, it's time to adjust Git LFS for our project. In order to touch less engine files, we are not going to touch the engine's <code>.gitattributes</code> located at <code>~/dev/MamadouArchives-Sync/.gitattributes</code>. Instead, we could override this file by creating the exact same file in our project's directory, e.g. <code>~/dev/MamadouArchives-Sync/MamadouArchives/.gitattributes</code>. If you are going to do so, keep in mind that from now on you must avoid tracking files by running <code>git lfs track "pattern or file path"</code> in the engine directory <code>~/dev/MamadouArchives-Sync</code>, because it will probably get truncated by the engine update script in consecutive runs. Thus, etither run this command in the project directory <code>~/dev/MamadouArchives-Sync/MamadouArchives</code> or it's subdirectories, and after that by issuing <code>cat ~/dev/MamadouArchives-Sync/MamadouArchives/.gitattributes</code> always make sure your pattern is being tracked. Or, you code modify <code>~/dev/MamadouArchives-Sync/MamadouArchives/.gitattributes</code> directly. Here is a sample <code>.gitattributes</code>, which overrides or adds to engine's <code>.gitattributes</code>:

{{< codeblock lang="bash" title="~/dev/MamadouArchives-Sync/MamadouArchives/.gitattributes" line_numbers="true" >}}
# Keep CRLF out of the repository
* text=auto eol=lf

# In case the git binary/text auto-detection algorithm fails, in order to avoid
# line-ending normalization, treat these files as binary no matter what
*.{uasset,umap,3ds,fbx,flac,gif,jif,jiff,jpe,jpeg,jpg,m4a,mp3,mp4,ogg,png,psd,ttf,wav,webp,xcf} binary

# LFS: UE4 file types
*.uasset filter=lfs diff=lfs merge=lfs -text
*.umap filter=lfs diff=lfs merge=lfs -text

# LFS: raw content types
*.3ds filter=lfs diff=lfs merge=lfs -text
*.fbx filter=lfs diff=lfs merge=lfs -text
*.flac filter=lfs diff=lfs merge=lfs -text
*.gif filter=lfs diff=lfs merge=lfs -text
*.jif filter=lfs diff=lfs merge=lfs -text
*.jiff filter=lfs diff=lfs merge=lfs -text
*.jpe filter=lfs diff=lfs merge=lfs -text
*.jpeg filter=lfs diff=lfs merge=lfs -text
*.jpg filter=lfs diff=lfs merge=lfs -text
*.m4a filter=lfs diff=lfs merge=lfs -text
*.mp3 filter=lfs diff=lfs merge=lfs -text
*.mp4 filter=lfs diff=lfs merge=lfs -text
*.ogg filter=lfs diff=lfs merge=lfs -text
*.png filter=lfs diff=lfs merge=lfs -text
*.psd filter=lfs diff=lfs merge=lfs -text
*.ttf filter=lfs diff=lfs merge=lfs -text
*.wav filter=lfs diff=lfs merge=lfs -text
*.webp filter=lfs diff=lfs merge=lfs -text
*.xcf filter=lfs diff=lfs merge=lfs -text

# LFS: everything under Content/
Content/**/* filter=lfs diff=lfs merge=lfs -text

# LFS: every asset source under RawContent/
RawContent/**/* filter=lfs diff=lfs merge=lfs -text

# LFS: all third-party libraries
ThirdParty/**/* filter=lfs diff=lfs merge=lfs -text
{{< /codeblock >}}

<br />
After adjusting the <code>.gitattributes</code> file according to your needs, you could also override UE4's <code>.gitignore</code> rules, by creating your own one inside the project's directory for your project's specific needs:

{{< codeblock lang="bash" title="~/dev/MamadouArchives-Sync/MamadouArchives/.gitignore" line_numbers="true" >}}
# Annoying windows files
[Dd]esktop.ini
Thumbs.db

# Explcitly ignore Mac DS_Store files, regardless of where they are
.DS_Store

# Visual Studio settings directory
.vs/

# Visual Studio Code settings directory
.vscode/

# Visual Studio database file
*.VC.db

# Qt Creator
.qmake.stash
*.autosave
*.pro.user
*.pro.user.*
CMakeLists.txt.user
CMakeLists.txt.user.*

# Ignore CLion directory
.idea/

# Compiled Object files
*.slo
*.lo
*.o
*.obj

# Precompiled Headers
*.gch
*.pch

# Compiled Dynamic libraries
*.so
*.dylib
*.dll

# Fortran module files
*.mod

# Compiled Static libraries
*.lai
*.la
*.a
*.lib

# Executables
*.exe
*.out
*.app
*.ipa

# These project files can be generated by the engine
*.xcodeproj
*.xcworkspace
*.sln
*.suo
*.opensdf
*.sdf
*.VC.db
*.VC.opendb
.idea/
.kdev4/
.vscode/
*.code-workspace
*.kdev4
*.pro
*.workspace
*CodeCompletionFolders.txt
*CodeLitePreProcessor.txt
*Config.pri
*Defines.pri
*Header.pri
*Includes.pri
*Source.pri
CMakeLists.txt
Makefile
!ThirdParty/**/CMakeLists.txt
!ThirdParty/**/Makefile

# Precompiled Assets
SourceArt/**/*.png
SourceArt/**/*.tga

# Binary Files
Binaries/*
Plugins/*/Binaries/*

# Builds
Build/*

# Whitelist PakBlacklist-<BuildConfiguration>.txt files
!Build/*/
Build/*/**
!Build/*/PakBlacklist*.txt

# Don't ignore icon files in Build
!Build/**/*.ico

# Built data for maps
*_BuiltData.uasset

# Configuration files generated by the Editor
Saved/*

# Compiled source files for the engine to use
Intermediate/*
Plugins/*/Intermediate/*

# Cache files for the editor to use
DerivedDataCache/*

# Misc
.ignore
{{< /codeblock >}}

<br />
__13__. Check whether GitLFS is keeping track of those files and then stage, commit, and push the adjusted <code>.gitattributes</code> file to Microsoft Azure DevOPS:

{{< highlight sh >}}
$ git add .gitattributes
$ git commit -m "track even more lfs objects"
$ git push
{{< /highlight >}}

__14__. Well done! Now, we need to take one more step in order to enable the engine to pick up our project automatically at the time of generating the project files and building the engine, so that our project is going to be built along with the engine. Open the <code>UE4Games.uprojectdirs</code> file in the root of our repository:

{{< codeblock lang="bash" title="UE4Games.uprojectdirs" line_numbers="true" >}}
; These folders will be searched 1 level deep in order to find projects
; UnrealBuildTool will store the following information:
; - Project name
; - Location of project
; - Whether it has code or not
; - TargetNames contains at the project location
;
./
Engine/Source/
{{< /codeblock >}}

<br />
And add your project's directory name with a trailing <code>/</code> character to the last line of this file:

{{< codeblock lang="bash" title="UE4Games.uprojectdirs" line_numbers="true" >}}
; These folders will be searched 1 level deep in order to find projects
; UnrealBuildTool will store the following information:
; - Project name
; - Location of project
; - Whether it has code or not
; - TargetNames contains at the project location
;
./
Engine/Source/
MamadouArchives/
{{< /codeblock >}}

<br />
__15__. Let's make the previous step's change permanent by staging, committing, and then pushing it to Microsoft Azure DevOPS:

{{< highlight sh >}}
$ git add -f UE4Games.uprojectdirs
$ git commit -m "add MamadouArchives to UE4Games.uprojectdirs"
$ git push
{{< /highlight >}}

__Note__: Adding the <code>-f</code> or <code>--force</code> parameter to <code>git add</code> is helpful when a file such as <code>UE4Games.uprojectdirs</code> is being ignored by one of the engine's <code>.gitignore</code>'s files, but you want to track it nontheless.

__16__. Well, congratulations! Now we have everything set up. You can make a copy of the intermediary <code>~/dev/MamadouArchives-Sync/</code> in order to start your development:

{{< highlight sh >}}
$ cp -vr ~/dev/MamadouArchives-Sync ~/dev/MamadouArchives
{{< /highlight >}}

Or, you could clone a completely new copy of it from Microsoft Azure DevOPS:

{{< highlight sh >}}
$ git clone https://SOME-ORGANIZATION@dev.azure.com/SOME-ORGANIZATION/MamadouArchives/_git/MamadouArchives ~/dev/MamadouArchives
{{< /highlight >}}

__17__. Now you can head to <code>~/dev/MamadouArchives</code> and run <code>GenerateProjectFiles.sh</code> for GNU/Linux,  <code>GenerateProjectFiles.bat</code> for Windows,  <code>GenerateProjectFiles.command</code> for macOS, in order to generate the project files for your platform or toolchain of choice and build the engine and your project with it.

__18__. On both GNU/Linux and Microsoft Windows, sometimes the ShaderCompileWorker fails to build. You may notice this at build time or when running the engine with an error similar to the following:


```
Couldn't launch /home/mamadou/dev/MamadouArchives/Engine/Binaries/Linux/ShaderCompileWorker! Make sure you build ShaderCompileWorker.
make ShaderCompileWorker
```

The solution is to find the ShaderCompileWorker project inside Microsoft Visual Studio's solution explorer and build it. Or, on GNU/Linux open up a terminal, navigate to the engine's directory and issue the <code>make</code> command:

{{< highlight sh >}}
$ cd ~/dev/MamadouArchives
$ make ShaderCompileWorker
{{< /highlight >}}

__19__. If everything went fine until this step, you can directly open your project inside the engine by issuing the following command or making it a script file in your project's engine root directory and then run that:

{{< highlight sh >}}
$ cd ~/dev/MamadouArchives
$ ./Engine/Binaries/Linux/UE4Editor "./MamadouArchives/MamadouArchives.uproject"
{{< /highlight >}}

__Note__: In some cases depending on your build type, the name of the UE4 editor or its parameter may require adjustments:

{{< highlight sh >}}
$ cd ~/dev/MamadouArchives
$ /home/mamadou/dev/Animus/Engine/Binaries/Linux/UE4Editor-Linux-DebugGame "./MamadouArchives/MamadouArchives.uproject" -vulkan -debug
{{< /highlight >}}

__20__. Lastly, in case you need the useful file locking feature for LFS objects, it could be enabled by running the following command:

{{< highlight sh >}}
$ git config lfs.https://SOME-ORGANIZATION@dev.azure.com/SOME-ORGANIZATION/MamadouArchives/_git/MamadouArchives.git/info/lfs.locksverify true
{{< /highlight >}}

This will add the following to <code>.git/config</code>

{{< highlight sh >}}
[lfs "lfs.https://SOME-ORGANIZATION@dev.azure.com/SOME-ORGANIZATION/MamadouArchives/_git/MamadouArchives.git/info/lfs"]
	locksverify = true
{{< /highlight >}}

## Migrating an existing repository

After setting up your current repository for LFS as we have explained in this tutorial, in case you need your git history, it could be as easy as running a command like this:

{{< highlight sh >}}
$ git lfs migrate import --everything --include="*.uasset,*.umap"
{{< /highlight >}}

Adjust the <code>--include</code> according to your project's specific needs.

## Final thoughts

Despite the shortcomings of Git in handling binary files, it's my SCM of choice for game development over currently available solutions such as SVN or Perforce. In the past, I used to heavily relying on nested [Git Submodules](https://git-scm.com/book/en/v2/Git-Tools-Submodules) in order to divide UE4 git projects' repositories into smaller repositories and keep the history clean. Since I've found Microsoft Azure DevOPS, life has never been easier with UE4 project maintenance under git.
