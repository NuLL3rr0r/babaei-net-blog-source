---
layout: post
title: "Book Review: Application Development with Qt Creator - Second Edition"
date: 2014-12-29 04:27:20 +0330
comments: true
categories:
- Android
- Book Review
- C
- C++
- Clang
- CMake
- Cross-platform
- FreeBSD
- G++
- GCC
- GNU
- iOS
- Linux
- Mac OS X
- MSVC
- QMake
- Qt Creator
- Unix
- VC++
- Visual C++
- Visual Studio
- Windows
---

Almost three weeks ago I received a review request from one of the _[Packt Publishing](http://www.packtpub.com/)_ staffs to review _[Application Development with Qt Creator, 2nd Edition](http://www.packtpub.com/application-development/application-development-qt-creator-2nd-edition)_ written by _[Ray Rischpater](http://www.lothlorien.com/dove/)_ which has been recently published by Packt Publishing. Since I've been developing cross platform [Qt](http://qt-project.org/) (cute, often mispronounced as Q-T cue-tee) applications from Qt 4 era back in 2008 -- when Qt Creator was not around yet and the project was running by Trolltech at the time -- and a handful of Qt Quick mobile applications over the past two years, I consider myself eligible enough to write a brief review on it. So, I was provided with a review copy and after reading it cover to cover, my thoughts on the book are as follows.

<center>Application Development with Qt Creator, 2nd Edition</center>

[{% img imgCenter /blog/2014/12/27/book-review-application-development-with-qt-creator-second-edition/2014-12-27-book-review-application-development-with-qt-creator-second-edition__001.jpg 372 480 'Application Development with Qt Creator, 2nd Edition (by Ray Rischpater, Packt Publishing)' 'Application Development with Qt Creator, 2nd Edition (by Ray Rischpater, Packt Publishing)' %}](/blog/2014/12/27/book-review-application-development-with-qt-creator-second-edition/2014-12-27-book-review-application-development-with-qt-creator-second-edition__001.jpg)

<!-- more -->

If you have just started your C++ development career or you are a C++ developer who is not familiar with Qt at all or just trying it out, this book contains enough to get you up and running with Qt 5 and Qt Quick 2 (a.k.a QML).

Do not let the title fool you! It's not just about Qt Creator as it covers a wide range of topics in only 13 chapters and 264 pages. As any introductory book, you will get a gentle introduction to Qt application development, from downloading and setting up the environment up to developing multi-lingual desktop and mobile applications. 

You may find all the contents of this book scattered on the Qt wiki or forums but it won't be as organized and clean as the way this book was written. It covers the following topics:

* Installing and setting up the necessary development tools such as Qt framework, Qt Creator IDE, GDB and CDB debuggers, Valgrind, Android SDK and NDK, JDK and Apache Ant
* Build, debug, profile and optimize your applications
* Detect memory leaks before releasing your application
* VCS integration (Version Control Systems)
* Coding style configuration
* .pro file settings and building projects from command line
* Creating re-usable C++ libraries and linking against them
* Signal and Slot mechanisms
* Using Qt Designer for fast UI prototyping and development
* Traditional Qt Widgets and state of the art Qt Quick (QML) UI development
* Creating custom C++ widgets and QML components
* C++ and Qt Quick integration
* Using 2D drawing API in C++
* MVC programming
* Showing web contents in your application
* Network and HTTP access from your application
* Multi-threading, Mutex and Semaphore basics
* Parsing XML
* Multimedia, audio and video playback
* Capturing photos using Camera
* Localizing your applications using Qt Linguist
* Using mobile sensors such as GPS, accelerometer, gyroscope, ambient light, and magnetometer
* Developing mobile applications on Android

Of course, there are a few things which have been left out such as SQL and database access from both C++ and Qt Quick, and, Qt Quick Controls and Styling. But, once you are get up and running, believe me, learning those stuffs would be a piece of cake.

In addition to that, in chapter thirteen of the book the author uses QtQuick2ApplicationViewer which is odd to me since it was more of a hack and has been deprecated in favor of _QQmlApplicationEngine_. In my estimation, it might have been inherited from the 1st edition of the book since it was the default code snippet for _main.cpp_ file of the project upon creating a new application on older Qt Creators.

Despite the fact that I'm not new to Qt but I also found a few tips and tricks worthy -- that I didn't know before -- in the book which made the effort of reading it worthwhile. For sure, this will be one of those books that I'm going to keep as my teaching material in my C++/Qt classes due to it's well organized and solid structure which makes the learning curve of Qt shorter and painless for novices and newcomers.

