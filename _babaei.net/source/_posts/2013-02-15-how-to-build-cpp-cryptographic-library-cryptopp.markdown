---
layout: post
title: "How to build C++ cryptographic library, Crypto++"
date: 2013-02-15 03:50
comments: true
categories:
- C
- C++
- Clang
- Cross-platform
- Crypto++
- Cryptography
- FreeBSD
- G++
- GCC
- GNU
- iOS
- Linux
- Mac OS X
- MSVC
- Security
- Unix
- VC++
- Visual C++
- Visual Studio
- Windows
---

[Crypto++](http://www.cryptopp.com/) is an awesome free and open source C++ class library of cryptographic algorithms and schemes which fully supports 32-bit and 64-bit architectures for many major operating systems, including FreeBSD, Linux, Solaris, Windows, Mac OS X and iOS. Currently, Crypto++ officially supports the following compilers:

- MSVC 6.0 - 2010
- GCC 3.3 - 4.5
- C++Builder 2010
- Intel C++ Compiler 9 - 11.1
- Sun Studio 12u1, Express 11/08, Express 06/10

The latest version at the time of this writing is 5.6.1.

In spite of the power that Crypto++ offers, building and using it can be a little bit tricky. In the following we will describe the process of building Crypto++ on both FreeBSD and Windows using the GCC, MinGW and VC++ compilers.

<!-- more -->

[How do I build Crypto++ on FreeBSD?](#CryptoFreeBSD)  
[How do I build Crypto++ using MinGW on Microsoft Windows?](#CryptoMinGW)  
[How do I build Crypto++ dynamically on Microsoft Windows and Visual C++?](#CryptoMSVCDynamic)  
[How do I build Crypto++ statically on Microsoft Windows and Visual C++?](#CryptoMSVCStatic)  
[How do I build 64-bit version on Microsoft Windows and Visual C++?](#CryptoMSVC64)  
[How do I build FIPS compliant version of Crypto++?](#CryptoFIPS)  

<br />
<a name="CryptoFreeBSD"></a>

### How do I build Crypto++ on FreeBSD? ###

Before we start building Crypto++ on FreeBSD, I have to warn about a bug which has been [discovered](http://forums.freebsd.org/showthread.php?t=23535) and [reported](http://gcc.gnu.org/bugzilla/show_bug.cgi?id=54741) by me that affects FreeBSD PCs with AVX enabled CPUs.

For the first time, the AVX FPU extension kernel support appeared in FreeBSD 9.1-STABLE. And, while still there's no release version of GCC out with the patch which disables the AVX if it isn't supported; So you should follow the instructions carefully if you have older versions of FreeBSD with GCC 4.4+, or simply use a recent snapshot of your favorite GCC version.

**1.** I prefer to install Crypto++ from FreeBSD ports. So:

{% codeblock lang:sh %}
$ cd /usr/ports/security/cryptopp/
$ make config
{% endcodeblock %}

I usually build Crypto++ with these options:

<pre>
[ ] DEBUG    Install debug symbols
[ ] DOCS     Build and/or install documentation
[*] GCC46    Build with GCC 4.6+
[*] STATIC   Build static version only (no shared libs)
[*] THREADS  Threading support
</pre>

If the bug affects you (FreeBSD < 9.1+, having older versions or snapshots of GCC 4.4+ enabled as default compiler), first you should uncheck __GCC46__ option, then disable the [newer version of GCC](http://www.freebsd.org/doc/en/articles/custom-gcc/article.html) for Crypto++ in your __/etc/make.conf__ beforehand.

{% codeblock %}
.if !empty(.CURDIR:M/usr/ports/*) && exists(/usr/local/bin/gcc46)
.if empty(.CURDIR:M/usr/ports/security/cryptopp*)
CC=gcc46 
CXX=g++46
CPP=cpp46
.endif
.endif
{% endcodeblock %}

**2.** Build and install Crypto++ by issuing the following command:

{% codeblock lang:sh %}
$ make install clean
{% endcodeblock %}

_Note: If you are affected by the above bug, you should pay attention to the g++ options which are applied by Ports at this step. You should use the same options to build your own code with Crypto++._


<br />
<a name="CryptoMinGW"></a>

### How do I build Crypto++ using MinGW on Microsoft Windows? ###

There is an [awesome step by step how-to, on building Crypto++ using MinGW](https://sites.google.com/site/ievgensychov/cryptopp).

Also, there is [an easier solution which I found on Qt Centre forums that relies on qmake](http://www.qtcentre.org/threads/28809-Compiling-amp-using-Crypto-with-mingw-version-of-Qt). Therefore, you should have Qt installed to build the library. Please note that the built library using this method does not need Qt libraries in order to function properly. We only need qmake to generate the approperiate makefiles in order to be able to build Crypto++ on MinGW and Windows platform.

**1.** Open an instance of __cmd.exe__ and navigate to the extracted source directory of Crypto++ (e.g. cryptopp561).

**2.** Then run the following commands:
{% codeblock lang:sh %}
erase /f GNUmakefile
qmake -project
{% endcodeblock %}

**3.** Now there should be a file named __CURRENT_DIRECTORY.pro__ (e.g. cryptopp561.pro) which is generate by the previous qmake command. Open the generated __.pro__ file in your favorite editor and make the following changes:
{% codeblock lang:sh %}
#TEMPLATE = app
#TARGET = cryptopp561
#INCLUDEPATH += .

TEMPLATE = lib
TARGET = cryptopp
INCLUDEPATH += .
CONFIG -= qt
LIBS += -lws2_32
{% endcodeblock %}

**4.** Open __fipstest.cpp__ and replace every __'OutputDebugString'__ with __'OutputDebugStringA'__.

**5.** Finally, generate the proper makefiles and build the library by using the following commands:
{% codeblock lang:sh %}
qmake
mingw32-make all -j<NUMBER_OF_YOUR_CPU_CORES + 1>
{% endcodeblock %}

**6.** Copy the following __.dll (shared)__ and __.a (static)__ files, generated for both debug and release variants to __YOUR_COMPILER_LINK_PATH__.
<pre>
CRYPTOPP_SOURCE_DIRECTORY/debug/cryptopp.dll
CRYPTOPP_SOURCE_DIRECTORY/debug/libcryptopp.a
CRYPTOPP_SOURCE_DIRECTORY/release/cryptopp.dll
CRYPTOPP_SOURCE_DIRECTORY/release/libcryptopp.a
</pre>

**7.** Copy __CRYPTOPP_SOURCE_DIRECTORY/*.h__ files to __YOUR_COMPILER_INCLUDE_PATH/cryptopp/__ in order to be able to include Crypto++ headers from your own code.


<br />
<a name="CryptoMSVCDynamic"></a>

### How to build Crypto++ dynamically on Microsoft Windows and Visual C++? ###

Here is a [comprehensive awesome tutorial on compiling and integrating Crypto++ into the Microsoft Visual C++ environment](http://www.codeproject.com/Articles/16388/Compiling-and-Integrating-Crypto-into-the-Microsof) which covers everything about Crypto++ on Windows and MSVC compiler.

_Note: Default project file for building the dynamic version which ships with Crypto++ uses static linking (/MT or /MTd). This is so wrong, and it should be /MD or /MDd. Despite the fact that dynamic version builds just fine, you will end up in plenty of ambiguous linker errors when linking your own code against the dynamic version of Crypto++. The reason is that your are linking against different versions of the run-time libraries. So, do not mix static and dynamic versions of the run-time libraries._

{% blockquote MSDN http://msdn.microsoft.com/en-us/library/2kzt1wy3(v=vs.110).aspx /MD, /MT, /LD (Use Run-Time Library) %}
All modules passed to a given invocation of the linker must have been compiled with the same run-time library compiler option (/MD, /MT, /LD).
{% endblockquote %}


<br />
<a name="CryptoMSVCStatic"></a>

### How do I build Crypto++ statically on Microsoft Windows and Visual C++? ###

**1.** Grab a copy of [the latest source release of Crypto++](http://www.cryptopp.com/#download) and extract it somewhere.

**2.** Open up __cryptest.sln__ in VC++ IDE

**3.** There are 4 projects in the solution, and the only one that we need to build static version of Crypto++ is the __cryptlib__ project. So, right click on the __cryptlib__ project and ensure that you have the following settings for the project in both Debug and Release build modes:

<pre>
Debug:
    Configuration Properties > General > Target Name > $(ProjectName)_d
    Configuration Properties > General > Configuration Type > Static library (.lib)
    Configuration Properties > C/C++ > Code Generation > Runtime Library > Multi-threaded Debug (/MTd)
    Configuration Properties > C/C++ > Output Files > Program Database File Name > $(OutDir)$(ProjectName)_d.pdb

Release:
    Configuration Properties > General > Target Name > $(ProjectName)
    Configuration Properties > General > Configuration Type > Static library (.lib)
    Configuration Properties > C/C++ > Code Generation > Runtime Library > Multi-threaded (/MT)
    Configuration Properties > C/C++ > Output Files > Program Database File Name > $(OutDir)$(ProjectName).pdb
</pre>

**4.** Now build the __cryptlib__ project in both Debug and Release build modes. If everything goes smoothly, grab these files and copy them to your lib folder:

<pre>
Debug:
    {Crypto++ Source Directory}\Win32\Output\Debug\cryptlib_d.lib
    {Crypto++ Source Directory}\Win32\Output\Debug\cryptlib_d.pdb
    
Release:
    {Crypto++ Source Directory}\Win32\Output\Release\cryptlib.lib
    {Crypto++ Source Directory}\Win32\Output\Release\cryptlib.pdb
</pre>

**5.** Last but not least, copy all the __*.h__ files from the extracted Crypto++ source directory to __{your own include directory}/cryptopp__.

_Note: When you're using static builds with VC++ on Windows you should always include __Windows.h__ before Crypto++ headers, or else, you'll have difficulties._

{% codeblock lang:cpp %}
#if defined(WIN32)
#include <windows.h>
#endif

#include <cryptopp/aes.h>
#include <cryptopp/ccm.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <cryptopp/sha.h>
{% endcodeblock %}


<br />
<a name="CryptoMSVC64"></a>

### How do I build 64-bit version on Microsoft Windows and Visual C++? ###

Again, here is a [comprehensive awesome tutorial on compiling and integrating Crypto++ into the Microsoft Visual C++ environment](http://www.codeproject.com/Articles/16388/Compiling-and-Integrating-Crypto-into-the-Microsof) which covers everything about Crypto++ on Windows and MSVC compiler.


<br />
<a name="CryptoFIPS"></a>

### How do I build FIPS compliant version of Crypto++? ###

You can't! You cannot build the Crypto++ DLL and claim it's FIPS compliant. The FIPS DLL must be used in binary form as distributed by the author, even though we have the source code and can build the same binary. For more information on FIPS 140-2 Conformance see [here](http://www.codeproject.com/Articles/16388/Compiling-and-Integrating-Crypto-into-the-Microsof) and [here](http://www.cryptopp.com/#fips).


<br/>

### Related Articles ###

[Write your own cross-platform cryptographic library](/blog/2013/02/15/write-your-own-cross-platform-cryptographic-library/)

