+++
title = "Gregorian / Jalali (a.k.a Persian Calendar) Date Conversion in C++ using boost::locale"
slug = "gregorian-jalali-persian-calendar-date-conversion-cpp-boost-locale"
date = 2020-02-25T00:27:00+01:00
tags = [ "C", "C++", "Clang", "Cross-platform", "FreeBSD", "G++", "GCC", "Linux", "LLVM", "macOS", "MSVC", "VC++", "Visual C++", "Visual Stuio", "Windows", "XCode" ]
+++

Well, anyone who has ever developed a C++ game or application with Gregorian to Jalali date conversion (or, vice versa) requirement is well aware of the hurdles of doing such a task. I, for one,  have been maintaining my own cross-platform C++ library for almost two decades now, with occasional bugs coming up from time to time.

Recently, I have been playing with [boost::locale](https://www.boost.org/doc/libs/1_72_0/libs/locale/doc/html/index.html) (developed by [Artyom Beilis](http://cppcms.com/cv.pdf) and contributed to [Boost project](https://www.boost.org/)) a bit more in order to utilize it in a personal project called [Barandazstorm](https://twitter.com/Barandazstorm), a home-grown social media analysis tool. Browsing [the docs](https://www.boost.org/doc/libs/1_72_0/libs/locale/doc/html/dates_times_timezones.html), I noticed the following example which does not even compile on my compiler:

{{< codeblock lang="cpp" title="boost::locale Gregorian to Hebrew date conversion example" line_numbers="true" >}}
using namespace boost::locale;
using namespace boost::locale::period;
generator gen;
// Create locales with Hebrew and Gregorian (default) calendars.
std::locale l_hebrew=gen("en_US.UTF-8@calendar=hebrew");
std::locale l_gregorian=gen("en_US.UTF-8");
// Create a Gregorian date from fields
date_time greg(year(2010) + february() + day(5),l_gregorian);
// Assign a time point taken from the Gregorian date to date_time with
// the Hebrew calendar
date_time heb(greg.time(),l_hebrew);
// Now we can query the year.
std::cout << "Hebrew year is " << heb / year << std::endl;
{{</ codeblock >}}

<br />

So, I tried to make a guess and replaced the <code>en_US.UTF-8@calendar=hebrew</code> part with <code>en_US.UTF-8@calendar=jalali</code> which didn't work. But, on the second try replacing that with <code>en_US.UTF-8@calendar=persian</code> actually worked! Which is sheer delight; due to the fact that now I found a solution to convert dates between both calendars as efortless as techonologies such as .NET in C++:

{{< codeblock lang="cpp" title="Two-way Gregorian / Jalali date conversion using boost::locale" line_numbers="true" >}}
/**
* @file
* @author  Mamadou Babaei <info@babaei.net>
* @version 0.1.0
*
* @section LICENSE
*
* (The MIT License)
*
* Copyright (c) 2020 Mamadou Babaei
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
* Two-way Gregorian / Jalali date conversion using boost::locale example
*/

#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <boost/locale.hpp>

void from_gregorian_to_jalali()
{
    boost::locale::generator generator;

    std::locale locale_gregorian = generator("en_US.UTF-8");
    std::locale locale_jalali = generator("en_US.UTF-8@calendar=persian");

    boost::locale::date_time gregorian(
            boost::locale::period::year(2020)
            + boost::locale::period::february()
            + boost::locale::period::day(25),
            locale_gregorian);

    boost::locale::date_time jalali(gregorian.time(), locale_jalali);

    std::cout << "Persian date is " << jalali / boost::locale::period::year()
            << "/" << std::setfill('0') << std::setw(2)
            << (jalali / boost::locale::period::month()) + 1
            << "/" << std::setfill('0') << std::setw(2)
            << jalali / boost::locale::period::day()
            << "." << std::endl;
}

void from_jalali_to_gregorian()
{
    boost::locale::generator generator;

    std::locale locale_gregorian = generator("en_US.UTF-8");
    std::locale locale_jalali = generator("en_US.UTF-8@calendar=persian");

    boost::locale::date_time jalali(
            boost::locale::period::year(1398)
            + boost::locale::period::month(11)
            + boost::locale::period::day(06),
            locale_jalali);

    boost::locale::date_time gregorian(jalali.time(), locale_gregorian);

    std::cout << "Gregorian date is " << gregorian / boost::locale::period::year()
            << "/" << std::setfill('0') << std::setw(2)
            << (gregorian / boost::locale::period::month()) + 1
            << "/" << std::setfill('0') << std::setw(2)
            << gregorian / boost::locale::period::day()
            << "." << std::endl;
}

int main()
{
    from_gregorian_to_jalali();
    from_jalali_to_gregorian();

    return EXIT_SUCCESS;
}
{{</ codeblock >}}

<br />

On a side note, for the above code to work your boost::locale libraries has to be built with [ICU](http://site.icu-project.org/) support; otherwise boost::locale throws an exception. On most Linux or BSD distros this is the default when you install Boost libraries from your distro's package manager. On Windows, it requires a bit of effort if you are trying to build Boost binaries yourself, which is another story for another time.

I did test the above code on FreeBSD, Linux, and Microsoft Windows, using MSVC, GCC, LLVM/Clang, and MinGW, and it's working as expected on all of these platforms.

<!--more-->
