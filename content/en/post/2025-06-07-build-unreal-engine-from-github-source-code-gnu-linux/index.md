+++
title = "Building Unreal Engine 5.6 From the GitHub Source Code on GNU/Linux"
slug = "build-unreal-engine-from-github-source-code-gnu-linux"
date = 2025-06-07T07:49:00+02:00
tags = [ "Android", "Epic Games", "Game Development", "Game Programming", "gamedev", "Git", "GitHub", "Java", "JDK", "Linux", "MSVC", "UDK", "UE4", "UE5", "Unreal Engine", "UnrealScript", "Visual Studio", "Windows" ]
toc = true
+++

{{< figure src="/blog/build-unreal-engine-from-github-source-code-gnu-linux/build-unreal-engine-from-github-source-code-gnu-linux.webp" alt="Building Unreal Engine 5.6 from the GitHub Source Code" caption="Building Unreal Engine 5.6 from the GitHub Source Code" >}}

Alright, I’m back with another video.

If you caught the [last one on building Unreal Engine 5.6 from source on Windows](/blog/build-unreal-engine-from-github-source-code-microsof-windows/), you already know the drill. As promised—this is the GNU/Linux edition.

We’re doing it the Linux way this time: clean, efficient, and just a bit different. Let’s dive in.

<!--more-->

## Video Tutorial

{{< youtube  >}}

<br/>

## Prerequisites

- **Unreal Engine has a voracious appetite for storage space**—the bare minimum requirement for building the current version of the engine from source is, more or less, **around `500 GB` of free space**. For a smoother experience and room to grow, I strongly recommend **`1 TB` or more of fast NVMe storage**.
- [Git](https://git-scm.com/downloads).
- Optional: Android Studio, Android SDK, Android NDK, and Java Development Kit (JDK). [See below](#build-with-android-support-optional).

## Build with Android Support (Optional)

If you need to add Android support to your custom build of Unreal Engine, make sure to set up the Android build environment before setting up the engine, generating the project file, and starting the build process.

To do so, [follow this tutorial](/blog/deploy-unreal-engine-projects-android-meta-quest-standalone-mode/), particularly the sections below:

- [00:08:03 - 00:25:53 Prerequisites (Android Studio)](https://www.youtube.com/watch?v=EClbEbNcl4k&t=483s)
- [00:25:54 - 00:27:13 Prerequisites (JDK)](https://www.youtube.com/watch?v=EClbEbNcl4k&t=1554s)
- [00:27:14 - 00:32:47 Prerequisites (SetupAndroid.bat)](https://www.youtube.com/watch?v=EClbEbNcl4k&t=1634s)

### Quick and Dirty Unreal Engine Android Prerequisites Setup on GNU/Linux

First, setup the required environment variables. Here's are example environment variables to setup Unreal Engine 5.6 for Android development:

{{< highlight zsh >}}
# Unreal Engine Android Development
export ANDROID_HOME="/opt/android/sdk"
export JAVA_HOME="/opt/openjdk-bin-21"
export NDK_ROOT="${ANDROID_HOME}/sdk/ndk/25.1.8937393"
export NDKROOT="${NDK_ROOT}"
export STUDIO_PATH="${HOME}/android-studio"
export STUDIO_SDK_PATH="${ANDROID_HOME}"
export PATH="${ANDROID_HOME}/cmdline-tools/latest/bin:${PATH}"
export PATH="${ANDROID_HOME}/platform-tools:${PATH}"
export PATH="${NDK_ROOT}:${PATH}"
export PATH="${JAVA_HOME}/bin:${PATH}"
{{< /highlight >}}

You can export these to the current shell, or add them to your shell's configuration (or startup) file (e.g., `.zshrc`, `.bashrc`, etc.) to ensure they persist across reboots.

You can force the current shell to reload your shell configuration file using `source ~/.your-shell-configuration-file`. In my case:

{{< highlight zsh >}}
$ source ~/.zprofile
{{< /highlight >}}

Furthermore, some shells such as ZSH require you to run the `rehash` command in order to be able to pick up binaries from the newly added directories to the `${PATH}` environment variable:
{{< highlight zsh >}}
$ rehash
{{< /highlight >}}

To verify whether our environment variables are in effects or not, we could either use `echo` or a compination of `env` and `grep` commands:

{{< highlight zsh >}}
$ env | grep ANDROID_HOME
$ env | grep JAVA_HOME
$ echo ${PATH}
{{< /highlight >}}

#### Setting up a Temporary Download Directory

Now, it's time to setup a temporary download directory:

{{< highlight zsh >}}
$ mkdir -p /tmp/android-setup
$ /tmp/android-setup
{{< /highlight >}}

See [Unreal Engine 5.6 Android Development Requirements](https://dev.epicgames.com/documentation/en-us/unreal-engine/android-development-requirements-for-unreal-engine?application_version=5.6) and [Unreal Engine 5.6 Android Development Requirements](https://dev.epicgames.com/documentation/en-us/unreal-engine/android-development-requirements-for-unreal-engine?application_version=5.5) for more information.

#### Downloading and Extracting Java Development Kit (JDK)

If you are developing using UE `5.6` or newer, grab the latest Java Development Kit (JDK) 21 using the following command, and adjust the `JAVA_HOME` environment variable accordingly (e.g. `export JAVA_HOME="/opt/jdk-21.0.7"`):

{{< highlight zsh >}}
$ aria2c -s16 -x16 \
    https://download.oracle.com/java/21/latest/jdk-21_linux-x64_bin.tar.gz
$ sudo tar xvzf jdk-21_linux-x64_bin.tar.gz -C /opt
$ ls -ahl /opt/
{{< /highlight >}}

If you are developing using UE `5.5` or earlier versions, grab the latest publicly available Java Development Kit (JDK) 17 using the following command, and adjust the `JAVA_HOME` environment variable accordingly (e.g. `export JAVA_HOME="/opt/jdk-17.0.12"`):

{{< highlight zsh >}}
$ aria2c -s16 -x16 \
    https://download.oracle.com/java/17/archive/jdk-17.0.12_linux-x64_bin.tar.gz
$ sudo tar xvzf jdk-17.0.12_linux-x64_bin.tar.gz -C /opt
$ ls -ahl /opt/
{{< /highlight >}}

Since JDK `17.0.12` is the latest publicly JDK `17` available that does not require a sign in on Oracle's webiste, if you need a newer version you can grab it from [this repository](https://github.com/adoptium/temurin17-binaries). Adjust the `JAVA_HOME` environment variable accordingly (e.g. `export JAVA_HOME="/opt/jdk-17.0.15+6"`):

{{< highlight zsh >}}
$ aria2c -s16 -x16 \
    https://github.com/adoptium/temurin17-binaries/releases/download/jdk-17.0.15%2B6/OpenJDK17U-jdk_x64_linux_hotspot_17.0.15_6.tar.gz
$ sudo tar xvzf OpenJDK17U-jdk_x64_linux_hotspot_17.0.15_6.tar.gz -C /opt
$ ls -ahl /opt/
{{< /highlight >}}

It's also possible to use the OpenJDK package provided by your GNU/Linux distribution. In my case, on Gentoo:

{{< highlight zsh >}}
# UE 5.6 and newer
# Installed to /opt/openjdk-bin-21 as a symlink to /opt/openjdk-bin-21.0.7_p6
$ emerge -atuv '=dev-java/openjdk-bin-21.0.7_p6'

# UE 5.5 and earlier
# Installed to /opt/openjdk-bin-17 as a symlink to /opt/openjdk-bin-17.0.15_p6
$  emerge -atuv '=dev-java/openjdk-bin-17.0.15_p6'

# Verify it
$ ls -ahl /opt/
{{< /highlight >}}

#### Downloading and Extracting Android Studio

To download and extract Android Studio Koala `2024.1.2`, run:

{{< highlight zsh >}}
$ aria2c -s16 -x16 \
    https://redirector.gvt1.com/edgedl/android/studio/ide-zips/2024.1.2.13/android-studio-2024.1.2.13-linux.tar.gz
$ tar xvzf android-studio-2024.1.2.13-linux.tar.gz -C "${HOME}"
$ ls -ahl ~/android-studio
{{< /highlight >}}

#### Downloading and Installing Required Android SDK Components

First, we have to download and extract Android Command-Line Tools:

{{< highlight zsh >}}
$ cd /tmp/android-setup
$ aria2c -s16 -x16 https://dl.google.com/android/repository/commandlinetools-linux-11076708_latest.zip
$ unzip commandlinetools-linux-11076708_latest.zip
{{< /highlight >}}

After this create the Android home directory:

{{< highlight zsh >}}
$ mkdir -p "${ANDROID_HOME}"
{{< /highlight >}}

In my case, since I choose `/opt` and I don't have the sufficient privileges to create a directory I need to create the directory as the `root` user and change the owner of the directory to my own user:

{{< highlight zsh >}}
$ sudo mkdir -p "${ANDROID_HOME}"
$ sudo chown -R mamadou:mamadou "${ANDROID_HOME}"
{{< /highlight >}}

Then, we have to accept all Android SDK licenses:

{{< highlight zsh >}}
$ yes | ./cmdline-tools/bin/sdkmanager --sdk_root="${ANDROID_HOME}" --licenses
{{< /highlight >}}

Then rather than the temporary `sdkmanager` I've downloaded I would like to install the latest version to my `${ANDROID_HOME}` and for the rest of the installation use that one instead:

{{< highlight zsh >}}
$ ./cmdline-tools/bin/sdkmanager --sdk_root="${ANDROID_HOME}" 'cmdline-tools;latest'
$ rehash
{{< /highlight >}}

It's time to finalize the installation with all the remaining required Android SDK components from Unreal's [`Engine/Extras/Android/SetupAndroid.sh`](https://github.com/EpicGames/UnrealEngine/blob/5.6/Engine/Extras/Android/SetupAndroid.sh) script for `5.6`:

{{< highlight zsh >}}
$ sdkmanager \
    "platform-tools" \
    "platforms;android-34" \
    "build-tools;34.0.0" \
    "cmake;3.22.1" \
    "ndk;25.1.8937393"
{{< /highlight >}}

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

## Cloning the Source Code from GitHub

To clone Unreal Engine 5.6 source code from GitHub:

{{< highlight zsh >}}
$ cd /some/path/
$ git clone git@github.com:EpicGames/UnrealEngine.git -b 5.6 UnrealEngine
{{< /highlight >}}

Since I use ZFS datasets for my Unreal Engine's installation with specific ZFS settings and optimizations, I already have my `/opt/UnrealEngine` and `/opt/UnrealEngine/.git` directories in place:

{{< highlight zsh >}}
$ zfs list

zroot/opt/UnrealEngine             33.5G   531G  1.59G  /opt/UnrealEngine
zroot/opt/UnrealEngine/.git        31.9G   531G  31.9G  /opt/UnrealEngine/.git
{{< /highlight >}}

As a result, the above Git command will fail for me. In that case, I can run the following to clone the source code with Git:

{{< highlight zsh >}}
$ sudo chown -R mamadou:mamadou /opt/UnrealEngine
$ cd /opt/UnrealEngine
$ git init
$ git remote add -t \* -f origin git@github.com:EpicGames/UnrealEngine.git
$ git checkout 5.6
{{< /highlight >}}

## Ensuring a Healthy Android SDK Installation

To verify if your Android SDK installation is healthy and working properly:

{{< highlight zsh >}}
$ cd /opt/UnrealEngine/Engine/Extras/Android
$ ./SetupAndroid.sh

Android Studio Path: /home/mamadou/android-studio
Android Studio SDK Path: /opt/android/sdk
grep: /home/mamadou/.bashrc: No such file or directory
[=======================================] 100% Computing updates...

Success!
{{< /highlight >}}

## Building Unreal Engine from Source

In order to build Unreal Engine we have to first download all the required binary blobs and [Epic Native Toolchain](https://dev.epicgames.com/documentation/en-us/unreal-engine/linux-development-requirements-for-unreal-engine#version-history). To perform this step, we only have to run the `Setup.sh` script located inside the root directory of Unreal Engine's source code:

{{< highlight zsh >}}
$ cd /opt/UnrealEngine
$ ./Setup.sh
{{< /highlight >}}

Once the Git dependencies are downloaded, you can generate the `Makefile` to build Unreal Engine using:

{{< highlight zsh >}}
$ bash GenerateProjectFiles.sh
{{< /highlight >}}

The above command generates all kinds of project files for various IDEs or build systems. If you'd like to generate the project files only for GNU Make, which is much faster than generating all supported project file formats:

{{< highlight zsh >}}
$ bash GenerateProjectFiles.sh -makefile
{{< /highlight >}}

In order to start the build process and build everything with the `Development` profile, invoke:

{{< highlight zsh >}}
$ make
{{< /highlight >}}

It's also possible to build a specific target, e.g.:

{{< highlight zsh >}}
# Build UnrealEditor
$ make UnrealEditor

# Build ShaderCompileWorker
$ make ShaderCompileWorker
{{< /highlight >}}

Also, you can choose your build profile as well, for example instead of building Unreal Editor using the `Development` profile, one can invoke the following to build Edtior using the `DebugGame` profile:

{{< highlight zsh >}}
$ make UnrealEditor-Linux-DebugGame
{{< /highlight >}}

If you need to cleanup all binaries and rebuild everything:

{{< highlight zsh >}}
make ARGS="-clean"
{{< /highlight >}}

Altenatively you can, which also cleans up the generated project files and Git dependencies (`WARNING`: destructive Git command!). You need to re-run the `Setup.sh` and `GenerateProjectFiles.sh` scripts again.

{{< highlight zsh >}}
# WARNING: destructive Git command!
$ git clean -dfx && git reset --hard && git checkout .
{{< /highlight >}}

### Dealing With Intel Implicit SPMD Program Compiler (ISPC) Errors

Since UE `5.5` release I've been encountering errors like the following when I build Unreal Engine from source on my Gentoo instance:

{{< highlight plain >}}
[215/4841] Compile Module.Chaos.10.cpp
In file included from /opt/UnrealEngine/Engine/Intermediate/Build/Linux/x64/UnrealEditor/Development/Chaos/Module.Chaos.10.cpp:8:
/opt/UnrealEngine/Engine/Source/Runtime/Experimental/Chaos/Private/Chaos/Joint/PBDJointSolverGaussSeidel.cpp:11:10: fatal error: 'PBDJointSolverGaussSeidel.ispc.generated.h' file not found
   11 | #include "PBDJointSolverGaussSeidel.ispc.generated.h"
      |          ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
1 error generated.
{{< /highlight >}}

It seems this does not occur on every distribution and is related to Intel Implicit SPMD Program Compiler.

This one is easy to solve:

1. Do not interrupt the build and let it go on until it fails:

{{< highlight plain >}}
Trace written to file /opt/UnrealEngine/Engine/Programs/UnrealBuildTool/Log.uba with size 645.2kb
Total time in Unreal Build Accelerator local executor: 1675.70 seconds

Result: Failed (OtherCompilationError)
Total execution time: 1683.45 seconds
make: *** [Makefile:9097: UnrealEditor-Linux-Development] Error 6
{{< /highlight >}}

2. Once the build stops re-invoke the `make` command and this time it will succeed.

{{< highlight plain >}}
Trace written to file /opt/UnrealEngine/Engine/Programs/UnrealBuildTool/Log.uba with size 54.8kb
Total time in Unreal Build Accelerator local executor: 142.17 seconds

Result: Succeeded
Total execution time: 145.17 seconds
{{< /highlight >}}

Somehow the ISPC generated headers are not available on the first invokation of the `make` command, possibly due to a timing issue in Unreal Header Tool or Unreal Build Tool, while it's available when the `make` is invoked the second time. Hence, the build succeeds on the second attempt.

As an alternative workaround, disabling `bCompileISPC` UBT option by adding the following inside your Game and Editor’s `.Target.cs` file might work:

{{< highlight csharp >}}
// Disable Intel Implicit SPMD Program Compiler forced by UE 5.5 on Linux.
bCompileISPC = false;
{{< /highlight >}}

### Shader Compilation Issues and Editor Crash

Older versions of UE had a known bug where the `ShaderCompileWorker` binary were not being built thus causing the Unreal Enditor to crash during the first start up. The workaround was to build that separately once the Unreal Engine build process is done by invoking the following command inside the Unreal Engine's source folder:

{{< highlight zsh >}}
$ make ShaderCompileWorker
{{< /highlight >}}

## Running Unreal Editor on Linux

To launch the Unreal Editor, navigate to the Engine’s source directory and run:

{{< highlight zsh >}}
$ ./Engine/Binaries/Linux/UnrealEditor
{{< /highlight >}}

On your first run, the editor will need to compile a large number of shaders, which can take some time. It may take a while to get past the splash screen before the editor window appears.

Grab a coffee and give yourself a well-earned pat on the back — you’ve just built Unreal Engine from source on GNU/Linux!
