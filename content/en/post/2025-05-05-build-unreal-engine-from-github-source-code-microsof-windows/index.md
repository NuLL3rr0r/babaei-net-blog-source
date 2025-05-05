+++
title = "Building Unreal Engine 5.6 From the GitHub Source Code on Microsoft Windows"
slug = "build-unreal-engine-from-github-source-code-microsof-windows"
date = 2025-05-05T15:38:00+02:00
tags = [ "Android", "Epic Games", "Game Development", "Game Programming", "gamedev", "Git", "GitHub", "Linux", "MSVC", "UDK", "UE4", "UE5", "Unreal Engine", "UnrealScript", "Visual Studio", "Windows" ]
toc = true
draft = true
+++

{{< figure src="/blog/build-unreal-engine-from-github-source-code-microsof-windows/build-unreal-engine-from-github-source-code-microsof-windows.webp" alt="Building Unreal Engine 5.6 from the GitHub Source Code" caption="Building Unreal Engine 5.6 from the GitHub Source Code" >}}

Alright... I’m back.
Yes, I know—I vanished for a while. But just like the upcoming Unreal Engine `5.6` release, I’ve been quietly cooking in the shadows. And now… we’re both making a comeback.

Today’s tutorial is all about how to build Unreal Engine `5.6` from source—on Windows. That’s right, `5.6` isn’t officially out yet, but we’re not waiting around. If you’re impatient like me—or just curious to see what Epic’s brewing before the rest of the world—this video is for you.

Now, some of you patient folks out there might be thinking:
“Why bother? Can’t I just wait for the release?”
Fair question. But here’s the deal—I work for a company that publishes Unreal Engine plugins on the Fab Store. And they want their plugin ready on day zero when the new engine drops. The catch? Epic only allows you to submit plugins once the final version is officially released. So to stay ahead of the curve, we grab the source early, build it, test it, and make sure everything works before launch day.

And hey, if you’re on Linux—don’t worry—I’ve got a separate video coming soon. Just not today. Because building on Linux is like dating in your forties… not complicated, exactly—just different.

We’ll be diving into more Unreal Engine `5.6` goodness over the coming months, so buckle up, hit that subscribe button, and let’s get nerdy.

<!--more-->

## Video Tutorial

{{< youtube  >}}

<br/>

## Prerequisites

- **Unreal Engine has a voracious appetite for storage space**—the bare minimum requirement for building the current version of the engine from source is more or less **around `500 GB` of free space**. For a smoother experience and room to grow, I strongly recommend **`1 TB` or more of fast NVMe storage**.
- [Git Bash for Windows](https://git-scm.com/downloads)
- [Microsoft Visual Studio Community 2022](https://visualstudio.microsoft.com/vs/community/)

## Microsot Visual Studio Installer Configuration File

This is the [Microsot Visual Studio Installer configuration file](visual-studio-2022.vsconfig) that automatically selects and installs all the required components needed to build Unreal Engine `5.6`.

## Build with Android Support (Optional)

If you need to add Android support to your custom build of Unreal Engine, make sure to set up the Android build environment before setting up the engine, generating the project file, and starting the build process.

To do so, [follow this tutorial](/blog/deploy-unreal-engine-projects-android-meta-quest-standalone-mode/), particularly the sections below:

- [00:08:03 - 00:25:53 Prerequisites (Android Studio)](https://www.youtube.com/watch?v=EClbEbNcl4k&t=483s)
- [00:25:54 - 00:27:13 Prerequisites (JDK)](https://www.youtube.com/watch?v=EClbEbNcl4k&t=1554s)
- [00:27:14 - 00:32:47 Prerequisites (SetupAndroid.bat)](https://www.youtube.com/watch?v=EClbEbNcl4k&t=1634s)

## Accessing Unreal Engine Source Code on GitHub

To get started with building Unreal Engine from source, you'll first need access to the official source code on GitHub. Follow the steps below, as outlined by the Unreal Engine official documentation:

{{< blockquote author="Epic Developer Community" link="https://dev.epicgames.com/documentation/en-us/unreal-engine/downloading-source-code-in-unreal-engine#accessingunrealenginesourcecodeongithub" >}}

### Accessing Unreal Engine Source Code on GitHub

Unreal Engine includes full access to the complete C++ source code, so you can study, customize, extend, and debug the entire Unreal Engine, and complete your project without obstruction.

Our source code repository on GitHub is continually updated as we develop features in our own mainline, so you don’t even have to wait for the next product release to get your hands on the very latest code.

To access Unreal Engine source code, do the following:

1. Navigate to [GitHub](https://github.com/) and sign up for an account.

2. Sign in to [UnrealEngine.com](https://www.unrealengine.com/) with your verified Epic Games account. To open your [account](https://accounts.unrealengine.com/) dashboard, hover over your username, and select Personal from the drop-down menu.

3. With your account dashboard open, select the Connections tab from the sidebar. Select the Accounts tab, and then select the Connect button below the GitHub icon.

4. If you have not already signed the Unreal Engine End User License Agreement, you will need to read through its terms and select the check box, then select Link Account. If you are signed out of your GitHub account, you will be directed to GitHub to sign in after clicking the Link Account button.

5. To complete the OAuth App Authorization process, click the Authorize EpicGames button. You can learn more about this process in [GitHub’s overview on Authorizing OAuth Apps](https://docs.github.com/en/apps/oauth-apps/using-oauth-apps/authorizing-oauth-apps).

6. GitHub will send an email inviting you to join the `@EpicGames` organization on GitHub. You must select the Join `@EpicGames` button in this email within seven days to complete the GitHub and Epic Games account linking process.

Upon completion, you will receive an email from Epic Games verifying that your GitHub and Epic Games accounts were successfully linked. If you don’t receive a confirmation email, or if your account is experiencing problems, get help from [Customer Service](https://www.epicgames.com/site/customer-service). You are now ready to get started by going to our [GitHub page](https://github.com/EpicGames/UnrealEngine) (login required) to download the full source code.
{{< /blockquote >}}