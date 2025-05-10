+++
title = "Rust Devs Think We’re Hopeless; Let’s Prove Them Wrong (with C++ Memory Leaks)!"
slug = "rust-devs-think-we-are-hopeless-lets-prove-them-wrong-with-cpp-memory-leaks"
date = 2025-05-10T15:26:00+02:00
tags = [ "Borrow Checker", "C", "C++", "CPP", "Cybersecurity", "Debugging", "Memory Leaks", "MSVC", "Programming", "Rust", "Security", "System Programming", "VC++", "Visual C++", "Visual Stuio", "Valgrind", "Vulnerability", "Windows" ]
toc = true
+++

{{< figure src="/blog/rust-devs-think-we-are-hopeless-lets-prove-them-wrong-with-cpp-memory-leaks/rust-devs-think-we-are-hopeless-lets-prove-them-wrong-with-cpp-memory-leaks.webp" alt="Rust Devs Think We’re Hopeless; Let’s Prove Them Wrong (with C++ Memory Leaks)!" caption="Rust Devs Think We’re Hopeless; Let’s Prove Them Wrong (with C++ Memory Leaks)!" >}}

When Rust developers think of us C++ folks, they picture a cursed bloodline — generational trauma passed down from `malloc` to `free`. To them, every line of C++ we write is like playing Russian Roulette — except all six chambers are loaded with undefined behavior.

They look at us like we’re hopeless. Like we’re one dangling pointer away from therapy. But you know what? We don’t need a compiler nanny. No borrow checker. No lifetimes. No ownership models. No black magic. Not even Valgrind is required. Just raw pointers, raw determination, and a bit of questionable sanity.

So in this video, I’m going to show you how to hunt down memory leaks like you were born with a pointer in one hand and a debugger in the other.

If that sounds unreasonably dangerous — and incredibly fun — smash that subscribe button, and let’s dive into the deep end of the heap.

<!--more-->

## Video Tutorial

{{< youtube mmUAdCzrdmQ >}}

<br/>

## An Intentional Simple C++ Memory Leak Demonstration

{{< codeblock lang="cpp" title="leak.cpp" line_numbers="true" >}}
/**
* @file
* @author  Mamadou Babaei <info@babaei.net>
* @version 0.1.0
*
* @section LICENSE
*
* (The MIT License)
*
* Copyright (c) 2025 Mamadou Babaei
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*
* @section DESCRIPTION
*
* An intentional simple C++ memory leak demonstration.
*/

#include <atomic>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <thread>

static constexpr int32_t PASSWORD_LENGTH = 1024 * 1024;
static constexpr std::chrono::milliseconds INTERVAL_MILLISECONDS{1};

std::string GeneratePassword(std::size_t length) {
    const std::string charset{
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
    };

    const std::size_t maxIndex = charset.size();
    std::string result(length, '\0');

    for (std::size_t i = 0; i < length; ++i) {
        result[i] = charset[rand() % maxIndex];
    }

    return result;
}

int32_t main() {
    std::srand(static_cast<uint32_t>(std::time(nullptr)));
    std::atomic<bool> stop{false};

    std::thread inputThread([&stop]() {
        std::cin.get();
        stop = true;
        });

    while (!stop) {
        std::string* password{new std::string(GeneratePassword(PASSWORD_LENGTH))};
    
        std::cout
            << "Generated password:"
            << "\n"
            << *password
            << "\n\n"
            << "Press the 'Enter' key to interrupt!"
            << std::endl;

        std::this_thread::sleep_for(INTERVAL_MILLISECONDS);
    }

    inputThread.join();
    std::cout << "'Enter' key detected! Will stop!" << std::endl;

    return 0;
}
{{</ codeblock >}}

<br />

## A _CrtDumpMemoryLeaks Demonstration

{{< codeblock lang="cpp" title="leak.cpp" line_numbers="true" >}}
/**
* @file
* @author  Mamadou Babaei <info@babaei.net>
* @version 0.1.0
*
* @section LICENSE
*
* (The MIT License)
*
* Copyright (c) 2025 Mamadou Babaei
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*
* @section DESCRIPTION
*
* A _CrtDumpMemoryLeaks demonstration.
*/

#define MEMORY_LEAK_TRACKER 1

#if MEMORY_LEAK_TRACKER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#define DEBUG_NEW new (_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif  /* MEMORY_LEAK_TRACKER */

#include <atomic>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <thread>

static constexpr int32_t PASSWORD_LENGTH = 64;
static constexpr std::chrono::milliseconds INTERVAL_MILLISECONDS{1000};

std::string GeneratePassword(std::size_t length) {
    const std::string charset{
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
    };

    const std::size_t maxIndex = charset.size();
    std::string result(length, '\0');

    for (std::size_t i = 0; i < length; ++i) {
        result[i] = charset[rand() % maxIndex];
    }

    return result;
}

int32_t main() {
#if MEMORY_LEAK_TRACKER
    int dbgFlags = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
    dbgFlags |= _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF;
    _CrtSetDbgFlag(dbgFlags);

    // Only track one allocation per run!
    // e.g. allocation number that causes leaks:
    //_CrtSetBreakAlloc(162);
#endif  /* MEMORY_LEAK_TRACKER */

    std::srand(static_cast<uint32_t>(std::time(nullptr)));
    std::atomic<bool> stop{false};

    std::thread inputThread([&stop]() {
        std::cin.get();
        stop = true;
        });

    while (!stop) {
        std::string* password{new std::string(GeneratePassword(PASSWORD_LENGTH))};
    
        std::cout
            << "Generated password:"
            << "\n"
            << *password
            << "\n\n"
            << "Press the 'Enter' key to interrupt!"
            << std::endl;

        std::this_thread::sleep_for(INTERVAL_MILLISECONDS);
    }

    inputThread.join();
    std::cout << "'Enter' key detected! Will stop!" << std::endl;

#if MEMORY_LEAK_TRACKER
    _CrtDumpMemoryLeaks();
#endif  /* MEMORY_LEAK_TRACKER */

    return 0;
}
{{</ codeblock >}}

<br />

## 🧸 ELI5: Explain Like I'm Five

{{< highlight cpp >}}
#define MEMORY_LEAK_TRACKER 1

#if MEMORY_LEAK_TRACKER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#define DEBUG_NEW new (_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif  /* MEMORY_LEAK_TRACKER */
{{< /highlight >}}

Imagine we’re building LEGO houses, and we sometimes forget to clean up the bricks afterward. This code says: “Hey, let’s turn on a LEGO brick tracker!”

It adds a magic camera (`<crtdbg.h>`) that watches where we drop bricks. And when we use `new` to build something, it secretly adds **who** built it and **where** in the code. So if we forget to clean up, we’ll know exactly **who made the mess** and **where**.

💡 **Technical Explanation**:

- `#define _CRTDBG_MAP_ALLOC`: Replaces calls to `malloc`, `calloc`, `realloc`, and `free` with debug versions that track source file and line number.
- `#include <crtdbg.h>`: Gives access to Microsoft's debug heap and leak-checking functions (only available on Windows with MSVC in debug builds).
- The `#define new DEBUG_NEW` trick: Replaces every usage of `new` with a debug version that logs the file and line where the allocation happened. This makes it possible to pinpoint **exactly where a leak originated**.

**tl;dr;** `DEBUG_NEW` and `_CRTDBG_MAP_ALLOC` tracks `new`/`malloc` calls with file and line information.

---

{{< highlight cpp >}}
int32_t main() {
#if MEMORY_LEAK_TRACKER
    int dbgFlags = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
    dbgFlags |= _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF;
    _CrtSetDbgFlag(dbgFlags);

    // Only track one allocation per run!
    // e.g. allocation number that causes leaks:
    //_CrtSetBreakAlloc(162);
#endif  /* MEMORY_LEAK_TRACKER */
{{< /highlight >}}

This part tells the camera **what to look for**. It turns on its “leak detector goggles” so it can see every piece of memory we forgot to put away.

And that `_CrtSetBreakAlloc(162);` line? That’s like saying: “When you see the **162nd LEGO block**, pause everything! I want to look at that one under a microscope.”

💡 **Technical Explanation**:

- `_CrtSetDbgFlag(...)`: Sets runtime flags to enable memory leak tracking and automatic leak reporting at program exit.
- `DBG_ALLOC_MEM_DF`: Tells the debug heap to keep track of memory allocations.
- `DBG_LEAK_CHECK_DF`: Automatically calls `_CrtDumpMemoryLeaks()` when `main()` exits.
- `_CrtSetBreakAlloc(162)`: Sets a **breakpoint on the 162nd allocation** (as counted internally by the CRT heap). When hit, Visual Studio will pause execution so you can inspect the allocation causing issues. You can comment this line out unless you're trying to isolate a specific leak in a large program.

**tl;dr;** `_CrtSetDbgFlag(...)` enables runtime heap tracking and leak reports; `_CrtSetBreakAlloc(N)` lets you break on a specific allocation number.

---

{{< highlight cpp >}}
#if MEMORY_LEAK_TRACKER
    _CrtDumpMemoryLeaks();
#endif  /* MEMORY_LEAK_TRACKER */

    return 0;
}
{{< /highlight >}}

At the very end, we tell the camera: “Okay, show me everything we forgot to clean up.”

It dumps out a report saying, “Hey! You left a brick at line `42`! And another one at line `57`!”

💡 **Technical Explanation**:

- Manually triggers a leak report right before program shutdown.
- This is **optional** if you already enabled `_CRTDBG_LEAK_CHECK_DF` — the CRT will dump leaks automatically.
- But calling it manually gives you control over when the leak dump happens (e.g., before global/static destruction).

**tl;dr;** `_CrtDumpMemoryLeaks()` manually prints out leak information with pointer and size.
