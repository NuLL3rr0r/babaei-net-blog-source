+++
title = "How to Build and Integrate Crypto++ into Unreal Engine 4 Games"
slug = "how-to-build-and-integrate-cryptopp-into-unreal-engine-4-games"
date = 2018-05-03T17:21:00+04:30
tags = [ "C", "C++", "CPP", "Clang", "Cross-platform", "Crypto++", "Cryptography", "Epic Games", "Game Development", "Game Programming", "gamedev", "indiedev", "Linux", "LLVM", "MSVC", "UDK", "UE4", "Unreal Engine", "UnrealScript", "VC++", "Visual C++", "Visual Stuio", "Windows" ]
draft = true
+++

Since the documentation on how to build and integrate third-party C++ libraries into [Unreal Engine 4](https://www.unrealengine.com/) is apparently sparse at best, I decided to document and share my experiences with libraries that we use in our day to day development pipeline using UE4. Hopefully, I have prior first-hand experience with building and integrating various C++ libraries into a couple of [UDK](https://www.unrealengine.com/en-US/previous-versions) games using a technique called [DLLBind](https://api.unrealengine.com/udk/Three/DLLBind.html) which came in really handy when I first started integrating the same libraries into UE4.

So, here is a how-to on [Crypto++ -- a free and open source C++ class library of cryptographic algorithms and schemes --](https://www.cryptopp.com/) integration into Unreal Engine 4 as part of a how-to series on methods and workarounds for building and integrating various C++ libraries into UE4.

<!--more-->
