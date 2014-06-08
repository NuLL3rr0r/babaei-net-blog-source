---
layout: post
title: "How to Build Boost on Windows"
date: 2013-03-25 00:49
comments: true
categories:
- Boost
- C
- C++
- G++
- GCC
- GNU
- MinGW
- MSVC
- Qt
- Qt Creator
- VC++
- Visual C++
- Visual Studio
- Windows
---

Nowadays, there are plenty of good reasons to include [the Boost libraries](http://www.boost.org/) in every day-to-day C++ project, with any scale. Some of these reasons are:

* Works well with the C++ Standard Library
* Works on almost any modern operating system
* The latest release (1.53.0) contains 122 individual libraries
* Many of Boost's founders are on the C++ standards committee
* The new C++11 Standard includes several Boost libraries
* Boost license allows both commercial and non-commercial use

In this article, we're going through building the __Boost__ libraries on __Microsoft Windows__ platform using both [MinGW](http://www.mingw.org/) and __Visual C++__ compilers. Moreover, we'll cover all the steps, tips and tricks required to build and use the static and dynamic variants of the __Boost__ libraries. Also, we'll learn to build __Boost__ with [ICU](http://site.icu-project.org/), [MPI](http://www.mcs.anl.gov/research/projects/mpi/) and [Python](http://www.python.org/) support. And, finally we'll learn how to build the 64-bit version of __Boost__ libraries.

<!-- more -->

[Prerequisites](#Prerequisites)  
[MinGW Builds](#MinGWBuilds)  
[Microsoft Visual C++ Builds](#MSVCBuilds)  
[ICU Support](#ICUSupport)  
[MPI Support](#MPISupport)  
[Python Support](#PythonSupport)  
[x64 Version](#x64Version)  
[Qt Creator](#QtCreator)  
[CMake](#CMake)  


### Prerequisites ###

In order to compile the __Boost__ libraries, the first thing you need is [a supported compiler by Boost project](http://www.boost.org/doc/libs/1_53_0/libs/msm/doc/HTML/ch04s03.html). All the instructions given in this writting have been tested and confirmed to work with Visual C++ 2010 and 2012, and all MinGW variants such as [official MinGW installer](http://www.mingw.org/), [MinGW-w65](http://mingw-w64.sourceforge.net/), [TDM-GCC](http://tdm-gcc.tdragon.net/) and [MinGW-builds](http://sourceforge.net/projects/mingwbuilds/).

Before we proceed any further, you should grab a copy of [Boost source code](http://www.boost.org/users/download/). At the time of this writing the latest version is [1.53.0](http://sourceforge.net/projects/boost/files/boost/1.53.0/).

__Note:__ The __.7z__ and __.zip__ archives has __Windows__ line endings, whereas the __.tar.bz2__ and __.tar.gz__ archives has __Unix__ line endings.


### MinGW Builds ###

In the __Windows Command Prompt__ navigate to the Boost source tree, and then run the following commands:

{% codeblock %}
cd .\tools\build\v2\engine\
.\build.bat mingw
move .\bin.ntx86\bjam.exe ..\..\..\..\
cd ..\..\..\..\
mkdir .\build
{% endcodeblock %}

This set of commands builds the bjam utility and now we are able to build the Boost libraries.

It's possible to see the available options and libraries by issuing the following commands:

{% codeblock %}
bjam --help
bjam --show-libraries
{% endcodeblock %}


The following

{% codeblock %}
bjam toolset=gcc --build-type=minimal --build-dir=".\build" --prefix="\Path\To\Install\Boost" install
{% endcodeblock %}


### Visual C++ Builds ###




move .\bin.ntx86_64\bjam.exe ..\..\..\..\


