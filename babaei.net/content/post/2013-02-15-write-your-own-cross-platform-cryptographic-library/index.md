+++
title = "Write Your Own Cross-Platform Cryptographic Library"
slug = "write-your-own-cross-platform-cryptographic-library"
date = 2013-02-15T08:11:00+03:30
tags = [ "C", "C++", "Clang", "CMake", "Cross-platform", "Crypto++", "Cryptography", "FreeBSD", "G++", "GCC", "GNU", "iOS", "Linux", "Mac OS X", "MSVC", "QMake", "Qt Creator", "Security", "Unix", "VC++", "Visual C++", "Visual Studio", "Windows" ]
aliases = [ "/blog/2013/02/15/write-your-own-cross-platform-cryptographic-library/" ]
+++

Previously I've described [the process of building Crypto++ on both FreeBSD and Windows using the GCC, MinGW and VC++ compilers](/blog/how-to-build-cpp-cryptographic-library-cryptopp/).

Now, we want to develop our own cross-platform cryptographic wrapper library around Crypto++. I've already uploaded the full source code to [GitHub](http://github.com). You can find the link to the code on GitHub at the end of this article.

Before you proceed, you have to build the Crypto++ library as I mentioned earlier [here](/blog/how-to-build-cpp-cryptographic-library-cryptopp/).

<!--more-->

### API ###

I'm not going through the details and I won't describe the code that I've written for this blog post. The code itself should be very legible, therefore I'll leave this task up to you. But I'm going to represent the API, and the way of using it.

Please keep in mind that this is a simple class, which serves a learning porpuse. So, I've avoided making it more complex. Please feel free to adapt it according to your own taste.

**1.** Every new project, should add the __crypto.cpp__ and __crypto.hpp__ files.

**2.** After including __crypto.hpp__ where you need it, the namspace and class __BabaeiNet::Crypto__ will be added to the scope. Of course, feel free to adjust these names to whatever you like.

**3.** Before going further, you may want to set the KEY and IV (Initialization Vector) in the crypto.cpp file using [this nice HEX/ASCII converter](http://www.dolcevie.com/js/converter.html) and your favorite editor's replace dialog,

**4.** Our __Crypto__ class has 3 simple static functions, and the return type for all of them is Boolean.

{{< highlight cpp >}}
static bool Encrypt(const std::string &plainText, std::string &out_encodedText, std::string &out_error);
static bool Decrypt(const std::string &cipherText, std::string &out_recoveredText, std::string &out_error);
static bool GenerateHash(const std::string &text, std::string &out_digest, std::string &out_error);
{{< /highlight >}}

If something goes wrong, the returned value should be __false__. Then you may find the __out_error__ variable useful which you've already passed to the function. You'll find the reason for failure by looking at this variable. Of course we could've simply thrown an exception, but in my opinion, in this case it doesn't make sense.

The __Encrypt__ and __Decrypt__ functions are using __AES (Advanced Encryption Standard / originally called Rijndael)__. And the __GenerateHash__ function is using __SHA-1__ for cryptographic hash generation.

This is the full example of what we've discussed so far:

{{< codeblock lang="cpp" title="main.cpp" >}}
///  (The MIT License)
///
///  Copyright (c) 2013 Mamadou Babaei
///
///  Permission is hereby granted, free of charge, to any person obtaining a copy
///  of this software and associated documentation files (the "Software"), to deal
///  in the Software without restriction, including without limitation the rights
///  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
///  copies of the Software, and to permit persons to whom the Software is
///  furnished to do so, subject to the following conditions:
///
///  The above copyright notice and this permission notice shall be included in
///  all copies or substantial portions of the Software.
///
///  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
///  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
///  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
///  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
///  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
///  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
///  THE SOFTWARE.



#include <iostream>
#include <string>
#include "crypto.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using namespace BabaeiNet;

const string pangram = "The quick brown fox jumps over the lazy dog.";

int main()
{
    string err;

    cout << endl;

    string encrypted;
    if (Crypto::Encrypt(pangram, encrypted, err)) {
        cout << "Original :  " << pangram
             << endl
             << "AES      :  " << encrypted
             << endl;
    } else {
        cout << "Encryption error :  " << err
             << endl;
    }

    cout << endl;

    string decrypted;
    if (Crypto::Decrypt(encrypted, decrypted, err)) {
        cout << "AES      :  " << encrypted
             << endl
             << "Original :  " << decrypted
             << endl;
    } else {
        cout << "Decryption error :  " << err
             << endl;
    }

    cout << endl;

    string sha1;
    if (Crypto::GenerateHash(pangram, sha1, err)) {
        cout << "Original :  " << pangram
             << endl
             << "SHA-1    :  " << sha1
             << endl;
    } else {
        cout << "Hash generation error :  " << err
             << endl;
    }


    cout << endl << "Press enter to exit, please." << endl;
    cin.get();

    return 0;
}
{{< /codeblock >}}

And this is the identical output of running the above program:

```
Original :  The quick brown fox jumps over the lazy dog.
AES      :  A5EC91437CB6E857E08F1875CDF89A2AAD7D9F4B4A8FCFC6E163C6FD29417D30ED627C25E14D34BE7D47D819F11AE88D

AES      :  A5EC91437CB6E857E08F1875CDF89A2AAD7D9F4B4A8FCFC6E163C6FD29417D30ED627C25E14D34BE7D47D819F11AE88D
Original :  The quick brown fox jumps over the lazy dog.

Original :  The quick brown fox jumps over the lazy dog.
SHA-1    :  408D94384216F890FF7A0C3528E8BED1E0B01621

Press enter to exit, please.
```


### Building and Running on FreeBSD / *nix ###

I suppose you've already built the library the way that I've described for FreeBSD. So, I wrote a small CMake script which consists of 3 files, to take care of building the release version of the example application and our Crypto library:

{{< codeblock lang="cmake" title="_src.cmake" >}}
#  (The MIT License)
#
#  Copyright (c) 2013 Mamadou Babaei
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



SET ( CRYPTOTEST_SOURCE_FILES
    main.cpp
    crypto.cpp
)
{{< /codeblock >}}

{{< codeblock lang="cmake" title="dep-config.cmake" >}}
#  (The MIT License)
#
#  Copyright (c) 2013 Mamadou Babaei
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



SET ( CRYPTOPP_FIND_REQUIRED TRUE )



### Crypto++ ###

FIND_PATH ( CRYPTOPP_INCLUDE_DIR NAMES cryptopp PATHS /usr/include/ /usr/local/include/ )
FIND_LIBRARY ( CRYPTOPP_LIBRARY NAMES cryptopp PATHS /usr/lib /usr/local/lib )

IF ( CRYPTOPP_INCLUDE_DIR AND CRYPTOPP_LIBRARY )
    SET ( CRYPTOPP_FOUND TRUE )
ENDIF ( CRYPTOPP_INCLUDE_DIR AND CRYPTOPP_LIBRARY )


IF ( CRYPTOPP_FOUND )
    SET ( DEP_FOUND TRUE )
    IF ( NOT CRYPTOPP_FIND_QUIETLY )
        MESSAGE ( STATUS "Found Crypto++:" )
        MESSAGE ( STATUS "  (Headers)       ${CRYPTOPP_INCLUDE_DIR}" )
        MESSAGE ( STATUS "  (Library)       ${CRYPTOPP_LIBRARY}" )
    ENDIF ( NOT CRYPTOPP_FIND_QUIETLY )
ELSE ( CRYPTOPP_FOUND )
    SET ( DEP_FOUND FALSE )
    IF ( CRYPTOPP_FIND_REQUIRED )
        MESSAGE ( FATAL_ERROR "Could not find Crypto++" )
    ENDIF ( CRYPTOPP_FIND_REQUIRED )
ENDIF ( CRYPTOPP_FOUND )
{{< /codeblock >}}

{{< codeblock lang="cmake" title="CMakeLists.txt" >}}
#  (The MIT License)
#
#  Copyright (c) 2013 Mamadou Babaei
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



CMAKE_MINIMUM_REQUIRED ( VERSION 2.8 FATAL_ERROR )
PROJECT ( CRYPTOTEST )

SET ( dep_DIR ${CRYPTOTEST_SOURCE_DIR} )
SET ( CMAKE_INSTALL_PREFIX "${CRYPTOTEST_SOURCE_DIR}/release/" )


SET ( CXX_FLAGS_WARN_LEVEL "-Wall -Wextra -Wno-unused-parameter" )
SET ( CXX_FLAGS_ISO_CPP "-pedantic" )
SET ( CXX_FLAGS_USE_PIPE "-pipe" )
SET ( CXX_FLAGS_OPT "-O2 -march=native -mtune=native" )
SET ( CXX_FLAGS_OMIT_FP "-fomit-frame-pointer" )
SET ( CXX_FLAGS_SIZE_OPT "-ffunction-sections -fdata-sections" )
SET ( CXX_FLAGS_THREADS "-pthread" )
SET ( LD_FLAGS_SIZE_OPT "-Wl,--gc-sections" )

SET ( CMAKE_CXX_FLAGS "${CXX_FLAGS_WARN_LEVEL} ${CXX_FLAGS_ISO_CPP} ${CXX_FLAGS_USE_PIPE} ${CXX_FLAGS_OPT} ${CXX_FLAGS_OMIT_FP} ${CXX_FLAGS_SIZE_OPT} ${CXX_FLAGS_THREADS}" )
SET ( CMAKE_EXE_LINKER_FLAGS "${LD_FLAGS_SIZE_OPT}" )


FIND_PACKAGE ( dep )

IF ( DEP_FOUND )
    INCLUDE_DIRECTORIES ( ${CRYPTOPP_INCLUDE_DIR} )
    LINK_DIRECTORIES ( ${CRYPTOPP_LIBRARY} )

    INCLUDE ( _src.cmake )
    
    SET ( CRYPTOTEST_BIN "CryptoTest" )

    ADD_EXECUTABLE ( ${CRYPTOTEST_BIN} ${CRYPTOTEST_SOURCE_FILES} )

    TARGET_LINK_LIBRARIES (
        ${CRYPTOTEST_BIN}
        ${CRYPTOPP_LIBRARY}
    )

    ADD_CUSTOM_COMMAND ( TARGET ${CRYPTOTEST_BIN}
        POST_BUILD
        COMMAND strip ${CRYPTOTEST_BIN}
        COMMAND strip -R.comment ${CRYPTOTEST_BIN}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )

    INSTALL ( FILES
        "${CMAKE_CURRENT_BINARY_DIR}/${CRYPTOTEST_BIN}"
        DESTINATION "${CMAKE_INSTALL_PREFIX}"
        PERMISSIONS
        OWNER_READ OWNER_WRITE OWNER_EXECUTE
        GROUP_READ GROUP_EXECUTE
        WORLD_READ WORLD_EXECUTE
    )
    
ENDIF ( DEP_FOUND )
{{< /codeblock >}}


**1.** To build the project change the current path to the source code directory that you've just downloaded, then run the following command:

```
$ mkdir build && cd build
```

**2.** If you've built Crypto++ with GCC 4.4+ (e.g. 4.6), then issue something like the following command:

```
$ cmake -DCMAKE_C_COMPILER=/usr/local/bin/gcc46 -DCMAKE_CXX_COMPILER=/usr/local/bin/g++46 ../
```

Otherwise:

```
$ cmake ../
```

If it all goes well, you'll see something like this:

```
-- The C compiler identification is GNU 4.6.4
-- The CXX compiler identification is GNU 4.6.4
-- Check for working C compiler: /usr/local/bin/gcc46
-- Check for working C compiler: /usr/local/bin/gcc46 -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working CXX compiler: /usr/local/bin/g++46
-- Check for working CXX compiler: /usr/local/bin/g++46 -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Found Crypto++:
--   (Headers)       /usr/local/include
--   (Library)       /usr/local/lib/libcryptopp.a
-- Configuring done
-- Generating done
-- Build files have been written to: /home/babaei/Desktop/crypto/build
```

**3.** To start the build process, enter the following command:

```
$ make install
```

**4.** Now you should have a copy of __CryptoTest__ executable in the __release__ directory of your source directory. There's also another one in the current directory (temporary __build__ directory) which is identical to the other one in the __release__ directory.


### Building and Running on Qt Creator using VC++ compiler ###

I suppose you've already built the static version of Crypto++, the way that I've described on Windows and MSVC compiler. And, you've already put debug/release versions in {source directory}/win_deps/lib and header files in {source directory}/win_deps/include/cryptopp.

**1.** The only thing along with __main.cpp__ (Exmple application), __crypto.hpp__ and __crypto.cpp__ that you need, in order to build the project is a __qmake__ __.pro__ file with the correct settings:

{{< codeblock lang="make" title="CryptoTest.pro" >}}
#  (The MIT License)
#
#  Copyright (c) 2013 Mamadou Babaei
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



TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS_DEBUG += -MTd
QMAKE_CXXFLAGS_RELEASE += -MT

# Used to reduce the size of the header files and speed up compilation.
# Excludes things like cryptography, DDE, RPC, the Windows Shell and Winsock.
DEFINES += WIN32_LEAN_AND_MEAN

INCLUDEPATH += $$PWD/./win_deps/include
DEPENDPATH += $$PWD/./win_deps/include
LIBS += -L$$PWD/./win_deps/lib

win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/./win_deps/lib -lcryptlib_d
else:win32:CONFIG(release, debug|release): LIBS += -L$$PWD/./win_deps/lib -lcryptlib

SOURCES += main.cpp\
        crypto.cpp

HEADERS  += crypto.hpp
{{< /codeblock >}}

**2.** Open up the CryptoTest.pro file in Qt Creator, then build and run both debug/release versions of your application. Peace of cake! Isn't it?


### Microsoft Visual C++ ###

As for __Qt Creator + VC++__ (previous section), I suppose you have the dependencies in your __win_deps__ directory already.

1. I put a project file named __CryptoTest.vcxproj__ without a solution file, which I've tested on both VC++ 2010 and VC++ 2012. The moment you open it up with Visual Studio for the first time and hit the __Save All__ button, you can have your solution file. I did this because I wanted you to be able to open the project file in the older versions of Visual C++.

2. You can simply hit F5 to run the application.

3. The build settings that I've changed for the project to build properly, are these (Right-click on the project name in the Solution Explorer window, and then from the opened context-menu select Properties):

```
Debug:
    Configuration Properties > C/C++ > General > $(ProjectDir)\win_deps\include
    Configuration Properties > C/C++ > Preprocessor > Runtime Library > WIN32_LEAN_AND_MEAN
    Configuration Properties > C/C++ > Code Generation > Runtime Library > Multi-threaded Debug (/MTd)
    Configuration Properties > Linker > General > Addition Library Directories > $(ProjectDir)\win_deps\lib
    Configuration Properties > C/C++ > Additional Dependecies > cryptlib_d.lib

Release:
    Configuration Properties > C/C++ > General > $(ProjectDir)\win_deps\include
    Configuration Properties > C/C++ > Preprocessor > Runtime Library > WIN32_LEAN_AND_MEAN
    Configuration Properties > C/C++ > Code Generation > Runtime Library > Multi-threaded (/MT)
    Configuration Properties > Linker > General > Addition Library Directories > $(ProjectDir)\win_deps\lib
    Configuration Properties > C/C++ > Additional Dependecies > cryptlib.lib
```


<br/>

### Related Articles ###

[How to build C++ cryptographic library, Crypto++](/blog/how-to-build-cpp-cryptographic-library-cryptopp/)


<br/>

### Source Code ###

[Check out the source code on GitLab](https://gitlab.com/NuLL3rr0r/babaei.net/tree/master/2013-02-15-write-your-own-cross-platform-cryptographic-library)

[Check out the source code on GitHub](https://github.com/NuLL3rr0r/babaei.net/tree/master/2013-02-15-write-your-own-cross-platform-cryptographic-library)

{{< codeblock lang="cpp" title="crypto.hpp" >}}
///  (The MIT License)
///
///  Copyright (c) 2013 Mamadou Babaei
///
///  Permission is hereby granted, free of charge, to any person obtaining a copy
///  of this software and associated documentation files (the "Software"), to deal
///  in the Software without restriction, including without limitation the rights
///  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
///  copies of the Software, and to permit persons to whom the Software is
///  furnished to do so, subject to the following conditions:
///
///  The above copyright notice and this permission notice shall be included in
///  all copies or substantial portions of the Software.
///
///  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
///  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
///  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
///  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
///  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
///  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
///  THE SOFTWARE.



#ifndef CRYPTO_HPP
#define CRYPTO_HPP


#include <string>

namespace BabaeiNet {
    class Crypto;
}

class BabaeiNet::Crypto
{
private:
	static const std::string UNKNOWN_ERROR;

    static unsigned char m_key[];
    static unsigned char m_iv[];

public:
    static bool Encrypt(const std::string &plainText, std::string &out_encodedText, std::string &out_error);
    static bool Decrypt(const std::string &cipherText, std::string &out_recoveredText, std::string &out_error);
    static bool GenerateHash(const std::string &text, std::string &out_digest, std::string &out_error);
};


#endif /* CRYPTO_HPP */
{{< /codeblock >}}

{{< codeblock lang="cpp" title="crypto.cpp" >}}
///  (The MIT License)
///
///  Copyright (c) 2013 Mamadou Babaei
///
///  Permission is hereby granted, free of charge, to any person obtaining a copy
///  of this software and associated documentation files (the "Software"), to deal
///  in the Software without restriction, including without limitation the rights
///  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
///  copies of the Software, and to permit persons to whom the Software is
///  furnished to do so, subject to the following conditions:
///
///  The above copyright notice and this permission notice shall be included in
///  all copies or substantial portions of the Software.
///
///  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
///  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
///  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
///  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
///  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
///  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
///  THE SOFTWARE.



#include <stdexcept>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif /* defined(_WIN32) || defined(_WIN64) */

#include <cryptopp/aes.h>
#include <cryptopp/ccm.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <cryptopp/sha.h>
#include "crypto.hpp"


using namespace std;
using namespace CryptoPP;
using namespace BabaeiNet;


const string Crypto::UNKNOWN_ERROR = "Unknown error!";

/*
* Use this nice HEX/ASCII converter and your editor's replace dialog,
* to create your own Key and IV.
* http://www.dolcevie.com/js/converter.html
*/

unsigned char Crypto::m_key[] = {
    0x60, 0x4e, 0x75, 0x4c, 0x4c, 0x33, 0x72, 0x72, 0x30, 0x72, 0x2f, 0x2e, 0x3f, 0x4b, 0x33, 0x59
}; // `NuLL3rr0r/.?K3Y

unsigned char Crypto::m_iv[] = {
    0x4d, 0x53, 0x2d, 0x42, 0x41, 0x42, 0x41, 0x45, 0x49, 0x2d, 0x69, 0x76, 0x2f, 0x2e, 0x3f, 0x71
}; // MS-BABAEI-iv/.?q


bool Crypto::Encrypt(const string &plainText, string &out_encodedText,
                     string &out_error)
{
    try {
        string cipher;

        CBC_Mode<AES>::Encryption enc;
        enc.SetKeyWithIV(m_key, sizeof(m_key), m_iv, sizeof(m_iv));

        cipher.clear();
        StringSource(plainText, true,
                     new StreamTransformationFilter(enc, new StringSink(cipher)));

        out_encodedText.clear();
        StringSource(cipher, true, new HexEncoder(new StringSink(out_encodedText)));

        return true;
    }

    catch (CryptoPP::Exception &ex) {
        out_error.assign(ex.what());
    }

    catch (std::exception &ex) {
        out_error.assign(ex.what());
    }

    catch (...) {
        out_error.assign(UNKNOWN_ERROR);
    }

    return false;
}


bool Crypto::Decrypt(const string &cipherText, string &out_recoveredText,
                     string &out_error)
{
    try {
        string cipher;

        CBC_Mode<AES>::Decryption dec;
        dec.SetKeyWithIV(m_key, sizeof(m_key), m_iv, sizeof(m_iv));

        cipher.clear();
        StringSource(cipherText, true, new HexDecoder(new StringSink(cipher)));

        out_recoveredText.clear();
        StringSource s(cipher, true,
                       new StreamTransformationFilter(dec, new StringSink(out_recoveredText)));

        return true;
    }

    catch (CryptoPP::Exception &ex) {
        out_error.assign(ex.what());
    }

    catch (std::exception &ex) {
        out_error.assign(ex.what());
    }

    catch (...) {
        out_error.assign(UNKNOWN_ERROR);
    }

    return false;
}


bool Crypto::GenerateHash(const string &text, string &out_digest, string &out_error)
{
    try {
        SHA1 hash;

        out_digest.clear();
        StringSource(text, true,
                     new HashFilter(hash, new HexEncoder(new StringSink(out_digest))));

        return true;
    }

    catch (CryptoPP::Exception &ex) {
        out_error.assign(ex.what());
    }

    catch (std::exception &ex) {
        out_error.assign(ex.what());
    }

    catch (...) {
        out_error.assign(UNKNOWN_ERROR);
    }

    return false;
}
{{< /codeblock >}}
