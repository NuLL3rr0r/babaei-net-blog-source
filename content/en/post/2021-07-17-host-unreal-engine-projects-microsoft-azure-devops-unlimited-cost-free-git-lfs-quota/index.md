+++
title = "Host Unreal Engine 4 projects on Microsoft Azure DevOPS with unlimited cost free Git LFS quota"
slug = "host-unreal-engine-projects-microsoft-azure-devops-unlimited-cost-free-git-lfs-quota"
date = 2021-07-17T16:12:00+02:00
tags = [ "Azure", "Azure DevOPS", "Bash", "C", "C++", "Clang", "Cross-platform", "csh", "Epic Games", "Game Development", "Game Programming", "gamedev", "Git", "Git Large File Storage", "Git LFS", "indiedev", "Linux", "LLVM", "Microsoft", "MSVC", "Perforce", "SCM", "sh", "Shell Scripting", "Subversion", "SVN", "UDK", "UE4", "Unreal Engine", "UnrealScript", "VC++", "Visual C++", "Visual Stuio", "Windows" ]
draft = true
+++

{{< figure src="/blog/host-unreal-engine-projects-microsoft-azure-devops-unlimited-cost-free-git-lfs-quota/unreal-engine-microsoft-azure-devops-git-lfs.webp" alt="Host Unreal Engine 4 projects on Microsoft Azure DevOPS with unlimited cost free Git LFS quota" caption="Host Unreal Engine 4 projects on Microsoft Azure DevOPS with unlimited cost free Git LFS quota" >}}

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

Well, before this all get you disappointed, let's hear the good news from Microsoft Azure DevOPS team:

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

__2__. The maximum push size is limited to <code>5GB</code> at a time. The <code>5GB</code> limit is only for files in the actual repository and it won't affect LFS objects. Thus, there are no limits for LFS objects' pushes. Despite that, if your internet connection is not stable, you could divide your files into multiple commits and push them separately. For example, the initial git dependencies for UE <code>4.27</code> is around <code>40GB</code> spanned across <code>~70,000</code> files. Instead of commiting and pushing a <code>40GB</code> chunk all at once, one could divide that into multiple commits and push those commits one by one using the following command:

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

OK, after getting ourselves familiarized with all the limits, if you deem this solution a worthy one for managing UE4 projects along with the engine source in the same repository, in the rest of this blog post I'm going to share my experiences and a script to keep the engine updated with ease using a Git + LFS setup.

__4__. Last but not least, there is an issue with the Microsoft implementation of LFS, which rejects large LFS objects and spits out a bunch of HTTP <code>413</code> and <code>503</code> errors at the end of your <code>git push</code>. It happened to me when I was pushing <code>40GB</code> of UE4 binary dependencies. The weird thing was I tried twice and both times it took a few good hours till the end of the push operation and based on measuring the bandwidth usage, the LFS upload size appeared to be more than the actual upload size. According to some answers on [this GitHub issue](https://github.com/MicrosoftDocs/azure-devops-docs/issues/4179) and [this Microsoft developer community question](https://developercommunity.visualstudio.com/t/git-lfs-push-got-413-error/867488) it seems the solution is running the following command inside the root of your local repository, before any git pull/push operations:

{{< highlight sh >}}
$ git config http.version HTTP/1.1
{{< /highlight >}}

Well, not only it did the trick and worked like a charm, but also the push time on the following git push dropped dramatically to <code>30</code> minutes for that hefty <code>40GB</code> UE4 binary dependencies.

<!--more-->
