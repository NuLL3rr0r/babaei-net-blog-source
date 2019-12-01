+++
title = "امنیت سایبری ۱۰۱ ویژه فعالان حقوق بشر، فعالان مدنی، فعالان سیاسی، روزنامه نگاران و براندازان: سرور VPN بسیار امن ShadowsocksR مبتنی بر سیستم‌عامل FreeBSD"
slug = "cybersecurity-101-secure-shadowsocksr-freebsd-vpn-server"
date = 2019-11-30T10:40:00+02:00
tags = [ "Censorship", "Cybersecurity", "FLOSS", "FreeBSD", "GNU", "LINUX", "Open Source", "Security", "ShadowsocksR", "UNIX", "VPN" ]
toc = true
draft = true
+++

در این مطلب به چگونگی راه‌اندازی سرور VPN بسیار امن با استفاده از [ShadowsocksR](https://github.com/shadowsocksrr) و سیستم‌عامل [FreeBSD](https://www.freebsd.org/) به زبان ساده خواهیم پرداخت. همچنین نحوه Hardening یا سخت‌سازی آن را جهت افزایش ضریب ایمنی خواهیم آموخت. به منظور افزایش راندمان و کارایی حداکثری آن، نحوه Perfromance Tuning یا تنظیم کارایی Network Stack سیستم‌عامل FreeBSD را خواهیم آموخت. دلیل انتخاب سیستم عامل FreeBSD، امنیت بسیار بالا، سادگی استفاده، پایداری بی نظیر آن، و در نهایت تسلط نگارنده این مطلب بدلیل [توسعه، پورت، و نگهداری چندین نرم افزار به عنوان بخشی از مجموعه پورت های رسمی FreeBSD](https://www.freebsd.org/cgi/ports.cgi?query=info%40babaei.net&stype=maintainer&sektion=all) می باشد.

در مقام مقایسه، تعداد آسیب‌پذیری‌های سیستم‌عامل‌های مختلف از سال ۱۹۹۹ تاکنون (مدت ۲۰ سال): [FreeBSD تعداد ۳۴۸ مورد](https://www.cvedetails.com/product/7/?q=Freebsd)، [Red Hat Enterprise Linux تعداد ۶۶۱ مورد](https://www.cvedetails.com/product/78/Redhat-Enterprise-Linux.html?vendor_id=25)، [Linux Kernel تعداد ۲۳۳۳ مورد](https://www.cvedetails.com/product/47/Linux-Linux-Kernel.html?vendor_id=33)، [Debian Linux تعداد ۳۰۵۷ مورد](https://www.cvedetails.com/product/36/?q=Debian+Linux)، [Ubuntu Linux از سال ۲۰۰۵ تعداد ۲۰۰۷ مورد](https://www.cvedetails.com/product/20550/Canonical-Ubuntu-Linux.html?vendor_id=4781) و در نهایت [Microsoft Windows 10 از سال ۲۰۱۵ تعداد ۱۱۱۱ مورد](https://www.cvedetails.com/product/32238/?q=Windows+10) آسیب‌پذیری را ثبت نمو‌ده‌اند. فراموش نشود این سیستم‌عامل آنقدر قابل اتکا می‌باشد که Netflix با کمک آن یک‌چهارم ترافیک اینترنت را به خود اختصاص داده است یا شرکت WhatsApp توانسته است به کمک آن بر روی هر سرور به ۲ میلیون کاربر خدمات دهد. ناگفته نماند که شرکت Sony سیستم‌عامل PlayStation های ۳ و ۴ را مبتنی بر FreeBSD توسعه داده است.

در ابتدای این مطلب آموزشی نحوه دریافت سرور رایگان ۵ ماهه از یکی از معتبرترین سرویس‌دهنده‌های سرور مجازی یا VPS به نام [UpCloud](https://upcloud.com/) را خواهیم آموخت.

این سرور VPN قابلیت ارائه و فراهم نمودن فیلترشکن امن برای سیستم‌عامل‌های موبایل Android و iOS و همچنین سیستم‌عامل‌های دسکتاپ نظیر Microsoft Windows, macOS, GNU/Linux و در نهایت سیستم‌عامل‌های خانواده BSD از جمله FreeBSD, NetBSD, OpenBSD, TrueOS, DragonFlyBSD و ... را خواهد داشت.

از نقطه نظر دانش فنی به منظور دنبال نمودن این راهنمای ویدیویی، تنها پیش‌نیاز، آشنایی متوسط کاربر به استفاده از یکی از سیستم‌عامل‌های ویندوز یا مک و استفاده از اینترنت می‌باشد.

پیش از ادامه مطلب، به منظور مطالعه بیشتر و آشنایی با سیستم عامل FreeBSD، مطالعه مقالات ذیل به قلم نگارنده این مطلب شدیدا توصیه می‌شود:

* [تاریخچه FreeBSD](/blog/the-history-of-freebsd/)
* [FreeBSD چیست؟ یک نمای کلی از سیستم عامل FreeBSD](/blog/what-is-freebsd-an-overview-of-freebsd-operating-system/)
* [FreeBSD یا Linux مسئله این است؟](/blog/freebsd-vs-linux/)

**نکته**: لطفا توجه داشته باشید که مطلبی که در ادامه می‌آید، چکیده آموزش ویدیویی فوق می‌باشد. بنابراین توضیحات اصلی در داخل ویدیوی آموزشی همراه با این مطلب می‌باشد و پیش از خواندن ادامه مطلب، شما را دعوت به مشاهده ویدیوی فوق می‌نمایم.

<!--more-->

## سلب مسئولیت

شما با ادامه مطالعه این مطلب، موافقت کامل خود با این توافق نامه را اعلام می‌نمایید:

{{< blockquote author="ممدوو بابائی" link="https://fa.babaei.net" title="لیسانس مطالب منتشر شده در وب سایت" >}}
تمامی محتویات این وب سایت تحت مجوز <a rel="license" href="https://creativecommons.org/licenses/by-sa/3.0/deed.fa" target="_blank">(CC BY-SA 3.0) Creative Commons Attribution-ShareAlike 3.0 Unported License</a> منتشر شده است. همچنین، تمامی سورس کدهای منتشر شده در این وب سایت تحت لیسانس <a rel="license" href="http://opensource.org/licenses/MIT" target="_blank">MIT License</a> منتشر شده است، مگر آن که به صراحت ذکر شده باشد. تمامی محتویات ارائه شده صرفا جنبه آموزشی و اطلاعاتی داشته و فاقد هرگونه ضمانت، تعهد یا شرایطی از هر نوع می باشد. بایستی توجه نمود که اطلاعات عرضه شده حتی ممکن است دقیق و یا بروز نباشد. هرگونه اطمینان به و یا استفاده از محتویات یا منابع منتشر شده در این وب سایت با مسئولیت مخاطب بوده و نگارنده یا نگارندگان هیچ گونه مسئولیتی در مورد عواقب آن را نخواهند پذیرفت.
{{< /blockquote >}}

## ثبت نام و کد هدیه ۲۵ دلاری سرویس UpCloud

به منظور برخورداری از ۲۵ دلار شارژ رایگان معادل با ۵ ماه اجاره یک سرور مجازی ۵ دلاری (مناسب برای حداقل ۲۰ کاربر) در زمان ثبت نام از کد <code>A5X7BK</code> استفاده نمایید. به عنوان یک جایگزین با استفاده از [این لینک به منظور ثبت نام در سرویس UpCloud به شکل خودکار از هدیه ۲۵ دلاری بهره‌منده شوید](https://upcloud.com/signup/?promo=A5X7BK). با این هدیه، بسته به میزان مصرف می‌توانید برای تعداد حداقل ۲۰ کاربر به مدت ۵ ماه و یا ۱۰۰ کاربر به مدت ۱ ماه VPN کاملا امن رایگان تهیه نمایید.

لطفا توجه داشته باشید که:

* به منظور ثبت‌نام در این سرویس نیاز به ورود اطلاعات کارت اعتباری خود خواهید داشت.
* در زمان ثبت نام هیچ‌گونه مبلغی از حساب شما کسر نخواهد شد. اما به منظور تایید اطلاعات کارت اعتباری شما یک تراکنش یک‌دلاری انجام می‌شود که سریعا به حساب شما بازگردانده خواهد شد.
* پس از ثبت نام ۲۵ دلار هدیه از سوی UpCloud دریافت خواهید نمود.
* حساب کاربری شما در سرویس UpCloud در حالت آزمایشی یا Trial Mode قرار خواهد گرفت که محدودیت‌هایی از جمله غیرفعال بودن برخی از گزینه‌ها را در پی خواهد داشت.
* پس از پرداخت حداقل ۱۰ دلار، حساب از حالت Trial Mode یا آزمایشی خارج شده و برای مثال اگر ۱۰ دلار پرداخت نموده باشید حساب شما دارای ۳۵ دلار اعتبار خواهد بود.
* عزیزانی که به دلیل سکونت در داخل ایران از داشتن کارت اعتباری محروم هستند به عنوان راهکار می‌توانند از طریق اقوام و آشنایان خود یا از طریق سرویس‌های [پرداخت آنلاین ارزی](https://www.google.com/search?q=پرداخت+آنلاین+ارزی) اقدام به تهیه این سرویس نمایند.
* در غیر اینصورت می‌توانید از [سرویس دهنده‌های داخلی سرور مجازی](http://www.webhostingtalk.ir/forumdisplay.php?f=15) که کمابیش مکانیزم مشابهی دارند استفاده نمایید. همچنین [می‌توانید جهت تهیه سرور مجازی با ریال درخواست خود را در میان سرویس‌دهندگان داخلی به مناقصه بگذارید](http://www.webhostingtalk.ir/forumdisplay.php?f=13).

## تایید اعمال تنظیمات Reverse DNS Name

در سیستم‌عامل‌ ویندوز برای IPv4 با ابزار <code>ping</code>:

{{< codeblock lang="cmd" >}}
> ping -a xxx.xxx.xxx.xxx
{{< /codeblock >}}
در سیستم‌عامل‌ ویندوز برای IPv6 با ابزار <code>ping</code>:

{{< codeblock lang="cmd" >}}
> ping -6 -a xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx
{{< /codeblock >}}

در سیستم‌عامل‌ ویندوز برای IPv4 با ابزار <code>nslookup</code>:

{{< codeblock lang="cmd" >}}
> nslookup xxx.xxx.xxx.xxx
{{< /codeblock >}}
در سیستم‌عامل‌ ویندوز برای IPv6 با ابزار <code>nslookup</code>:

{{< codeblock lang="cmd" >}}
> nslookup xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx
{{< /codeblock >}}

در سیستم‌عامل‌های یونیکس و شبه‌یونیکس نظیر macOS، گنو/لینوکس، *BSD و ... برای IPv4 با ابزار <code>host</code>:

{{< codeblock lang="sh" >}}
$ host xxx.xxx.xxx.xxx
{{< /codeblock >}}

در سیستم‌عامل‌های یونیکس و شبه‌یونیکس نظیر macOS، گنو/لینوکس، *BSD و ... برای IPv6 با ابزار <code>host</code>:

{{< codeblock lang="sh" >}}
$ host xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx
{{< /codeblock >}}

در سیستم‌عامل‌های یونیکس و شبه‌یونیکس برای IPv4 با ابزار <code>dig</code>:

{{< codeblock lang="sh" >}}
$ dig +noall +answer +short -x xxx.xxx.xxx.xxx
{{< /codeblock >}}

در سیستم‌عامل‌های یونیکس و شبه‌یونیکس برای IPv6 با ابزار <code>dig</code>:

{{< codeblock lang="sh" >}}
$ dig +noall +answer +short -x xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx
{{< /codeblock >}}

در سیستم‌عامل‌های یونیکس و شبه‌یونیکس برای IPv6 با ابزار <code>drill</code>:

{{< codeblock lang="sh" >}}
$ drill -x xxx.xxx.xxx.xxx | grep PTR | tail -r | head -n 1 | cut -d '	' -f5
{{< /codeblock >}}
در سیستم‌عامل‌های یونیکس و شبه‌یونیکس برای IPv6 با ابزار <code>drill</code>:

{{< codeblock lang="sh" >}}
$ drill -x xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx | grep PTR | tail -r | head -n 1 | cut -d '	' -f5
{{< /codeblock >}}

## ورود به سرور مجازی با استفاده از SSH

اسکریپت ورود خودکار به سرور از طریق پروتکل SSH برای سیستم‌عامل ویندوز با استفاده از [KiTTY](https://github.com/cyd01/KiTTY/):

{{< codeblock lang="cmd" title="kitty-ssh.cmd" line_numbers="true" >}}
@echo off

REM (The MIT License)
REM
REM Copyright (c) 2019 Mamadou Babaei
REM
REM Permission is hereby granted, free of charge, to any person obtaining a copy
REM of this software and associated documentation files (the "Software"), to deal
REM in the Software without restriction, including without limitation the rights
REM to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
REM copies of the Software, and to permit persons to whom the Software is
REM furnished to do so, subject to the following conditions:
REM
REM The above copyright notice and this permission notice shall be included in
REM all copies or substantial portions of the Software.
REM
REM THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
REM IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
REM FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
REM AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
REM LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
REM OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
REM THE SOFTWARE.

set REMOTE_SSH_HOST=xxx.xxx.xxx.xxx
set REMOTE_SSH_PORT=22
set REMOTE_SSH_USER=mamadou
set REMOTE_SSH_PASSWORD=
set LOCAL_SOCKS5_PORT=8080
set PRIVATE_SSH_KEY=

cd %~dp0

echo.
echo kitty -C -D %LOCAL_SOCKS5_PORT% -P %REMOTE_SSH_PORT% %REMOTE_SSH_USER%@%REMOTE_SSH_HOST%
echo.

IF [%PRIVATE_SSH_KEY%] == [] (goto PASSWORD_AUTH) else (goto PUBLIC_KEY_AUTH)

:PUBLIC_KEY_AUTH
kitty.exe -C -D %LOCAL_SOCKS5_PORT% -P %REMOTE_SSH_PORT% %REMOTE_SSH_USER%@%REMOTE_SSH_HOST% -i %PRIVATE_SSH_KEY%
goto EOF

:PASSWORD_AUTH
IF [%REMOTE_SSH_PASSWORD%] == [] (goto MANUAL_PASSWORD_AUTH) else (goto AUTO_PASSWORD_AUTH)

:AUTO_PASSWORD_AUTH
kitty.exe -C -D %LOCAL_SOCKS5_PORT% -P %REMOTE_SSH_PORT% %REMOTE_SSH_USER%@%REMOTE_SSH_HOST% -pw %REMOTE_SSH_PASSWORD%
goto EOF

:MANUAL_PASSWORD_AUTH
kitty.exe -C -D %LOCAL_SOCKS5_PORT% -P %REMOTE_SSH_PORT% %REMOTE_SSH_USER%@%REMOTE_SSH_HOST%
goto EOF

:EOF
%comspec% /k
{{< /codeblock >}}

لازم به ذکر است که با تغییر <code>kitty.exe</code> به <code>putty.exe</code> در اسکریپت فوق می‌توان KiTTY را با [PuTTY](https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html) جایگزین نمود.

در سیستم‌عامل‌های یونیکس و شبه‌یونیکس نظیر macOS، گنو/لینوکس، *BSD و ... و یا سیستم‌عامل ویندوز با استفاده از مجموعه ابزارهای [Git Bash](https://git-scm.com/downloads):

{{< codeblock lang="sh" title="اجرا در کلاینت" >}}
$ ssh mamadou@xxx.xxx.xxx.xxx
{{< /codeblock >}}

## SSH Tunneling فیلترشکن امن و قابل اتکا اما کند

جهت انجام تنظیمات Socks5 می‌توانید افزونه‌های [FoxyProxy Standard برای مرورگر فایرفاکس](https://addons.mozilla.org/en-US/firefox/addon/foxyproxy-standard/) و [FoxyProxy Standard برای کروم](https://chrome.google.com/webstore/detail/foxyproxy-standard/gcknhkkoolaabfmlnjonogaaifnjlfnp?hl=en) را نصب نمایید.

به منظور انجام SSH Tunneling در سیستم‌عامل ویندوز کافیست مقدار متغیر <code>LOCAL_SOCKS5_PORT</code> را در فایل اسکریپت <code>kitty-ssh.cmd</code> تنظیم نموده و اجرا نمایید.

انجام SSH Tunneling در سیستم‌عامل اندروید امکان‌پذیر می‌باشد اما به دلیل نیاز به روت بودن دستگاه و جلوگیری از پیچیدگی مطلب از آن صرف‌نظر می‌نماییم.

در سیستم‌عامل‌های یونیکس و شبه‌یونیکس نظیر macOS، گنو/لینوکس، *BSD و ... و یا سیستم‌عامل ویندوز با استفاده از مجموعه ابزارهای [Git Bash](https://git-scm.com/downloads):

{{< codeblock lang="sh" title="اجرا در کلاینت" >}}
$ ssh -D 8080 mamadou@xxx.xxx.xxx.xxx
{{< /codeblock >}}

## بروز‌رسانی سرور به آخرین نسخه FreeBSD

جهت دریافت و نصب آخرین وصله‌های امنیتی:

{{< codeblock lang="sh" title="اجرا در سرور به عنوان مدیر" >}}
$ freebsd-update fetch install
{{< /codeblock >}}

پس از دریافت و اعمال آخرین وصله‌های امنیتی، با یکی از دستورات ذیل، بایستی اقدام به راه‌اندازی مجدد سرور نمود:

{{< codeblock lang="sh" title="اجرا در سرور به عنوان مدیر" >}}
$ shutdown -r now
{{< /codeblock >}}

یا:

{{< codeblock lang="sh" title="اجرا در سرور به عنوان مدیر" >}}
$ reboot
{{< /codeblock >}}

پس از راه‌اندازی مجدد سرور و ورود با SSH، با دستور ذیل می‌توان از اعمال موفقیت‌آمیز بروزرسانی اطمینان حاصل نمود:

{{< codeblock lang="sh" title="اجرا در سرور به عنوان کاربر یا مدیر" >}}
$ uname -a
FreeBSD mamadou-vm 12.0-RELEASE-p9 FreeBSD 12.0-RELEASE-p9 GENERIC  amd64
{{< /codeblock >}}

در اینجا قسمت <code>-p9</code> در کنار نسخه FreeBSD یعنی <code>12.0-RELEASE-p9</code> حاکی از نسخه آخرین وصله امنیتی نصب شده می‌باشد. چنانچه مجددا دستور <code>freebsd-update</code> را اجرا نمایید این ابزار به شما خاطر نشان خواهد شد که بروزرسانی جدیدی وجود ندارد:

{{< codeblock lang="sh" title="اجرا در سرور به عنوان مدیر" >}}
$ freebsd-update fetch install
No updates needed to update system to 12.0-RELEASE-p12.
No updates are available to install.
{{< /codeblock >}}

توجه داشته باشید در پاره‌ای از مواقع جهت بروزرسانی موفقیت‌آمیز، لازم است این دستور چندبار اجرا شود. در اینصورت این نکته توسط <code>freebsd-update</code> به شما گوشزد خواهد شد.

چنانچه نیاز به بروزرسانی FreeBSD به نسخه Minor یا Major بعدی باشد، ابزار <code>freebsd-update</code> شما را با نمایش هشداری مطلع می‌سازد:

{{< codeblock lang="plaintext" title="اعلان مربوط به منسوخ شدن نسخه فعلی" >}}
WARNING: FreeBSD 12.0-RELEASE is approaching its End-of-Life date.
It is strongly recommended that you upgrade to a newer
release within the next 2 months.
{{< /codeblock >}}

در اینصورت جهت دریافت بروزرسانی عمده برای مثال به آخرین نسخه FreeBSD در زمان نگارش این مطلب یعنی <code>12.1-RELEASE</code>:

{{< codeblock lang="sh" title="اجرا در سرور به عنوان مدیر" >}}
$ freebsd-update -r 12.1-RELEASE upgrade
{{< /codeblock >}}

توجه نمایید که دستور فوق تنها بروزرسانی را دریافت نموده و هنوز آن را اعمال ننموده است. جهت اعمال آن:

{{< codeblock lang="sh" title="اجرا در سرور به عنوان مدیر" >}}
$ freebsd-update install
{{< /codeblock >}}

پس از اعمال بروزرسانی‌ها، زمان راه‌اندازی مجدد سرور فرا رسیده است:

{{< codeblock lang="sh" title="اجرا در سرور به عنوان مدیر" >}}
$ shutdown -r now
{{< /codeblock >}}

پس از راه‌اندازی مجدد، جهت تکمیل پروسه بروزرسانی سیستم‌عامل، نیار به اجرای مجدد <code>freebsd-update</code> می‌باشد:

{{< codeblock lang="sh" title="اجرا در سرور به عنوان مدیر" >}}
$ freebsd-update install
{{< /codeblock >}}

پس از هر بروزرسانی به عمده به نسخه‌های Major و در پاره مواقع Minor نیاز خواهید داشت که بسته‌های نصب شده را با دستورات ذیل بروزرسانی نمایید. توجه داشته باشید که: ۱. درحال حاضر بدلیل اینکه هیچ بسته‌ای توسط ما نصب نشده است، اجرای این دستورات غیرضروری به نظر می‌رسد؛ پس می‌توان از اجرای آن‌ها صرف‌نظر نمود. ۲. این دستور‌العمل فقط برای مواقعی است که شما صرفا از بسته‌های به اصطلاح باینری استفاده می‌نمایید؛ برای نرم‌افزارهایی که از سیستم Ports کامپایل و نصب می‌شوند بایستی دستورالعمل دیگری را اجرا نمود.

{{< codeblock lang="sh" title="اجرا در سرور به عنوان مدیر" >}}
$ pkg-static upgrade -f
$ pkg upgrade
{{< /codeblock >}}

در پایان، جهت حذف فایل‌های قدیمی از سرور نیار به اجرای مجدد <code>freebsd-update</code> می‌باشد:

{{< codeblock lang="sh" title="اجرا در سرور به عنوان مدیر" >}}
$ freebsd-update install
{{< /codeblock >}}

**نکته**: به خاطر داشته باشید در صورت مواجهه با مشکل در هر مرحله‌ای از پروسه بروزرسانی، می‌توانید سرور را به نسخه قبلی FreeBSD بازگردانید:

{{< codeblock lang="sh" title="اجرا در سرور به عنوان مدیر" >}}
$ freebsd-update rollback
{{< /codeblock >}}

## نصب و راه‌اندازی pkgng

در سیستم‌عامل امکان نصب بسته‌ها به دو صورت باینری و کامپایل از سورس وجود دارد. در این سیستم‌عامل ابزار <code>pkgng</code> به عنوان Package Manager برای مدیریت بسته‌ها به شکل باینری در دسترس می‌باشد. این ابزار به صورت پیش‌فرض در این سیستم‌عامل تعبیه نشده است. بنابراین جهت نصب آن دستور ذیل را به عنوان مدیر سیستم صادر نمایید:

{{< codeblock lang="sh" title="اجرا در سرور به عنوان مدیر" >}}
$ pkg
The package management tool is not yet installed on your system.
Do you want to fetch and install it now? [y/N]:
{{< /codeblock >}}

که پس از اجرای آن، FreeBSD از شما خواهد پرسید که آیا تمایل به نصب <code>pkgng</code> دارید یا خیر.

## ویرایشگر متن پیش‌فرض

ویرایشگر متن پیش‌فرض در سیستم‌عامل  FreeBSD ویرایشگر <code>nvi</code> می باشد که با دستور <code>vi</code> اجرا می‌شود. این ویرایشگر بصورت پیش‌فرض در حالتی تحت عنوان Command Mode اجرا می‌شود که ممکن است برای افرادی که با ویرایشگر‌های متنی مانند Notepad آشنایی دارند بسیار عجیب به نظر برسد. هر چند این ویرایشگر در حالت Insert Mode خود کاملا مانند ویرایشگر‌های متنی دیگر نظیر Notepad کار می‌کند بسیاری از کاربران مبتدی را در ابتدای آشنایی با آن با چالش‌های بسیار جدی مواجه می‌سازد. بعنوان مثال هرکس که این ویرایشگر را بدون آگاهی قبلی یک‌بار اجرا نموده باشد بخوبی می‌داند که خروج از آن و بازگشت به محیط خط فرمان برای یک کاربر مبتدی بدون دریافت کمک از یک فرد آشنا به آن تقریبا غیرممکن است!

**نکته**: در صورتیکه در این ویرایشگر گیر افتادید، ابتدا کلید <code>ESC</code> را بفشارید. سپس تایپ نمایید <code>:q!</code> و کلید <code>Enter</code> یا <code>Return</code> را بفشارید.

به هر صورت چنانچه کار با ویرایشگر متنی <code>vi</code> را دشوار یافتید، به شما ویرایشگر <code>nano</code> را پیشنهاد می‌نمایم. برای دریافت و نصب آن دستور ذیل را صادر نمایید:

{{< codeblock lang="sh" title="اجرا در سرور به عنوان مدیر" >}}
$ pkg install editors/nano
$ rehash
{{< /codeblock >}}

برخی دستورات این ویرایشگر متنی:

* <code>Ctrl + X</code>: خروج از ویرایشگر؛ چنانچه فایل باز را ذخیر ننموده باشید این ویرایشگر از شما خواهد پرسید که آیا مایل به ذخیره تغییرات ایجاد شده هستید یا خیر
* <code>Ctrl + O</code>: ذخیره فایل جاری
* <code>Ctrl + R</code>: باز نمودن یک فایل با تایپ مسیر آن
* <code>Ctrl + W</code>: جستجو در فایل
* <code>Ctrl + \\</code>: جستجو و جایگزین نمودن یک کلمه یا عبارت
* <code>Ctrl + K</code>: عمل Cut نمودن متن
* <code>Ctrl + U</code>: عمل Paste یا UnCut نمودن متن
* <code>Alt + U</code> و یا به شکل غیرهمزمان <code>ESC</code> و سپس <code>U</code>: عمل Undo
* <code>Alt + E</code> و یا به شکل غیرهمزمان <code>ESC</code> و سپس <code>E</code>: عمل Redo
* <code>Ctrl + G</code>: راهنما

**نکته**: ویرایشگر <code>nano</code> بصورت پیش‌فرض اقدام به شکستن خطوط طولانی‌تر از عرض صفحه یا به اصطلاح فنی آن Wrap نمودن آن می‌نماید. این عمل در هنگام کار با فایل‌های تنظیمات FreeBSD یا سایر نرم‌افزارها بسیار خطرناک است و باعث ایجاد اختلال در عملکرد آن‌ها می‌شود. اگر می‌خواهید این قابلیت را فقط در زمان ویرایش یک فایل بخصوص خاموش نمایید، می‌توانید از سوییچ یا پارامتر <code>-w</code> استفاده نمایید:

{{< codeblock lang="sh" title="nano: Do Not Wrap Text!" >}}
$ nano -w /path/to/some/file
{{< /codeblock >}}

درصورت تمایل می‌توانید این قابلیت را برای یک کاربر خاص با ویرایش فایل <code>~/.nanorc</code> و یا بصورت پیش‌فرض تمامی کاربران سیستم با ویرایش <code>/usr/local/etc/nanorc</code> و افزودن عبارت ذیل غیرفعال نمایید:

{{< codeblock lang="plaintext" title="~/.nanorc - nano: Do Not Wrap Text!" >}}
set nowrap
{{< /codeblock >}}

کاربران پیشرفته‌تر می‌توانند از سایر ویرایشگر‌های مورد علاقه خود بهرمنده شوند. برای مثال بشخصه ویرایشگر NeoVim را بر هر دو ویرایشگر <code>vi</code> و <code>nano</code> ترجیح می‌دهم:

{{< codeblock lang="sh" title="اجرا در سرور به عنوان مدیر" >}}
$ pkg install editors/neovim
$ rehash
{{< /codeblock >}}

اگر قصد استفاده از ویرایشگری غیر از ویرایشگر پیش‌فرض یعنی <code>vi</code> را دارید، بایستی متغیرهای محیطی Shell خود نظیر <code>EDITOR</code> و <code>VISUAL</code> را تغییر دهید. FreeBSD بصورت پیش‌فرض برای کاربر مدیر سیستم یا همان <code>root</code> از <code>tcsh</code> و سایر کاربران از <code>sh</code> که با Bourne shell سازگار می‌باشد استفاده می‌نماید. در ادامه به فایل‌هایی که بدین منظور بایستی ویرایش شوند اشاره خواهیم نمود. چنانچه از Shell دیگری نظیر <code>bash</code>، <code>zsh</code> و ... استفاده می‌نمایید بایستی مقادیر این متغیرها را در فایل متناسب با آن تغییر دهید.

برای ویرایشگر <code>nano</code> مقدار مناسب <code>/usr/local/bin/nano</code> بوده و برای ویرایشگر NeoVim مقدار <code>/usr/local/bin/nvim</code> می‌باشد. به عنوان نمونه، جهت تنظیم NeoVim به عنوان ویرایشگر پیش‌فرض سیستم:

{{< codeblock lang="sh" title="~/.cshrc - به عنوان کاربر و مدیر سیستم" >}}
setenv  EDITOR  /usr/local/bin/nvim
{{< /codeblock >}}

{{< codeblock lang="sh" title="~/.mailrc - به عنوان کاربر" >}}
set EDITOR=/usr/local/bin/nvim
set VISUAL=/usr/local/bin/nvim
{{< /codeblock >}}

{{< codeblock lang="sh" title="~/.profile - به عنوان کاربر" >}}
EDITOR=/usr/local/bin/nvim;     export EDITOR
{{< /codeblock >}}

در نهایت به عنوان مدیر سیستم فایل <code>/etc/profile</code> را با ویرایشگر دلخواه پیش‌فرض تنظیم می‌نماییم:

{{< codeblock lang="sh" title="/etc/profile - مدیر سیستم" >}}
EDITOR="/usr/local/bin/nvim"; export EDITOR
{{< /codeblock >}}

## سخت نمودن SSH

احتمالا تنها مقداری که نیاز به تنظیم آن در فایل تنظیمات سرور SSH خواهید داشت <code>Port</code> خواهد بود که در مثال ذیل با مقدار پیش‌فرض یعنی <code>22</code> تنظیم شده است:

{{< codeblock lang="sh" title="/etc/ssh/sshd_config" >}}
Port 22
Protocol 2
HostKey /etc/ssh/ssh_host_rsa_key
HostKey /etc/ssh/ssh_host_ed25519_key
PermitRootLogin no
PasswordAuthentication no
PermitEmptyPasswords no
KexAlgorithms curve25519-sha256@libssh.org,diffie-hellman-group-exchange-sha256
Ciphers chacha20-poly1305@openssh.com,aes256-gcm@openssh.com,aes128-gcm@openssh.com,aes256-ctr,aes192-ctr,aes128-ctr
MACs hmac-sha2-512-etm@openssh.com,hmac-sha2-256-etm@openssh.com,umac-128-etm@openssh.com,hmac-sha2-512,hmac-sha2-256,umac-128@openssh.com
{{< /codeblock >}}

این تنظیمات را به انتهای فایل کلاینت SSH اضافه نمایید:

{{< codeblock lang="sh" title="/etc/ssh/ssh_config" >}}
HashKnownHosts yes
Host github.com
    MACs hmac-sha2-512-etm@openssh.com,hmac-sha2-256-etm@openssh.com,hmac-sha2-512
Host gitlab.com
    MACs hmac-sha2-512-etm@openssh.com,hmac-sha2-256-etm@openssh.com,hmac-sha2-512
Host *
  ConnectTimeout 30
  KexAlgorithms curve25519-sha256@libssh.org,diffie-hellman-group-exchange-sha256
  MACs hmac-sha2-512-etm@openssh.com,hmac-sha2-256-etm@openssh.com,umac-128-etm@openssh.com,hmac-sha2-512,hmac-sha2-256,umac-128@openssh.com
  Ciphers chacha20-poly1305@openssh.com,aes256-gcm@openssh.com,aes128-gcm@openssh.com,aes256-ctr,aes192-ctr,aes128-ctr
  ServerAliveInterval 10
  ControlMaster auto
  ControlPersist yes
  ControlPath ~/.ssh/socket-%r@%h:%p
{{< /codeblock >}}

{{< codeblock lang="sh" title="اجرا در سرور به عنوان مدیر" >}}
$ service sshd restart
{{< /codeblock >}}

## سخت‌تر نمودن SSH ورود با کلید عمومی به جای کلمه عبور

در ویندوز، با استفاده از KiTTY یا PuTTY پس از ورود به سرور:

{{< codeblock lang="sh" title="اجرا در سرور به عنوان کاربر" >}}
$ mkdir -p ~/.ssh
{{< /codeblock >}}

سپس کلید عمومی را با استفاده از <code>vi</code>، <code>nano</code> و یا هر ویرایشگر متن دیگر به فایل <code>~/.ssh/authorized_keys</code> بیافزایید.

در سیستم‌عامل‌های یونیکس یا شبه‌یونیکس:

{{< codeblock lang="sh" title="اجرا در کلاینت" >}}
$ ssh-keygen -t rsa -b 4096 -C "mamadouinbox@babaei.net"
$ cat ~/.ssh/id_rsa.pub | ssh -p 22 mamadou@xxx.xxx.xxx.xxx 'mkdir -p ~/.ssh && cat >> ~/.ssh/authorized_keys'
{{< /codeblock >}}

پس از ورود کلمه عبور به صورت خودکار پوشه و فایل موردنظر برای شما در سرور ایجاد خواهد شد.

{{< codeblock lang="sh" title="/etc/ssh/sshd_config" >}}
ChallengeResponseAuthentication no
UsePAM no
{{< /codeblock >}}

{{< codeblock lang="sh" title="اجرا در سرور به عنوان مدیر" >}}
$ service sshd restart
{{< /codeblock >}}

{{< codeblock lang="sh" title="اجرا در کلاینت" >}}
$ ssh -p 22 mamadou@xxx.xxx.xxx.xxx -o PubkeyAuthentication=no
mamadou@xxx.xxx.xxx.xxx: Permission denied (publickey).
{{< /codeblock >}}

## تنظیم DNS Cache با استفاده از سرویس unbound

{{< codeblock lang="sh" title="اجرا در سرور به عنوان مدیر" >}}
service local_unbound onestart
local-unbound-setup 1.1.1.1 1.0.0.1 2606:4700:4700::1111 2606:4700:4700::1001
{{< /codeblock >}}

{{< codeblock lang="sh" title="اجرا در سرور به عنوان مدیر" >}}
$ cat /etc/resolv.conf
# Generated by resolvconf
# nameserver 94.237.127.9
# nameserver 94.237.40.9

nameserver 127.0.0.1
options edns0

$ cat /etc/unbound/forward.conf
# This file was generated by local-unbound-setup.
# Modifications will be overwritten.
forward-zone:
	name: .
	forward-addr: 1.1.1.1
	forward-addr: 1.0.0.1
	forward-addr: 2606:4700:4700::1111
	forward-addr: 2606:4700:4700::1001
{{< /codeblock >}}

{{< codeblock lang="sh" title="" >}}
$ chflags schg /etc/resolv.conf
$ chflags schg /etc/unbound/forward.conf
{{< /codeblock >}}

{{< codeblock lang="sh" title="" >}}
$ rm -f /etc/resolv.conf
$ cat  /etc/resolv.conf
$ rm -f /etc/unbound/forward.conf
$ cat  /etc/unbound/forward.conf
{{< /codeblock >}}

{{< codeblock lang="sh" title="" >}}
$ chflags noschg /etc/resolv.conf
$ chflags noschg /etc/unbound/forward.conf
{{< /codeblock >}}

## تنظیمات عمومی

{{< codeblock lang="sh" title="/etc/rc.conf" >}}
# keymap
keymap="us"

# crash dumps
# Set dumpdev to "AUTO" to enable crash dumps, "NO" to disable
dumpdev="NO"

# cpu freq. scaling
powerd_enable="NO"

# ps2 mouse on console
moused_enable="NO"

# sendmail
sendmail_enable="NONE"
sendmail_submit_enable="NO"
sendmail_outbound_enable="NO"
sendmail_msp_queue_enable="NO"

# ftpd
ftpd_enable="NO"

# auto /tmp clean-up
clear_tmp_enable="YES"
clear_tmp_X="YES"

# remote host logging
syslogd_flags="-ss"

# hostname
hostname="mamadou-vps"

# local_unbound
local_unbound_enable="YES"

# networking
ifconfig_vtnet0="DHCP"
ifconfig_vtnet1="DHCP"
ifconfig_vtnet2_ipv6="inet6 accept_rtadv"
rtsold_enable="YES"

# ntpd
ntpd_enable="YES"
ntpd_sync_on_start="YES"

# sshd
sshd_enable="YES"
{{< /codeblock >}}

{{< codeblock lang="sh" title="/etc/sysctl.conf" >}}
# coredump
kern.coredump=0
{{< /codeblock >}}

{{< codeblock lang="sh" title="اجرا در سرور به عنوان مدیر" >}}
$ sysctl kern.coredump=0
kern.coredump: 1 -> 0
{{< /codeblock >}}

{{< codeblock lang="sh" title="اجرا در سرور به عنوان مدیر" >}}
$ service netif restart
$ service routing restart
$ service hostname restart
{{< /codeblock >}}

{{< codeblock lang="sh" title="اجرا در سرور به عنوان مدیر" >}}
$ ping xxx.xxx.xxx.xxx
$ ping6 xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx
{{< /codeblock >}}

## سخت‌تر نمودن FreeBSD

{{< codeblock lang="sh" title="/boot/loader.conf" >}}
# hardening
security.bsd.allow_destructive_dtrace=0
{{< /codeblock >}}

{{< codeblock lang="sh" title="/etc/sysctl.conf" >}}
# hardening
security.bsd.see_other_uids=0
security.bsd.see_other_gids=0
security.bsd.see_jail_proc=0
security.bsd.unprivileged_read_msgbuf=0
security.bsd.unprivileged_proc_debug=0
kern.randompid=1
security.bsd.stack_guard_page=1
{{< /codeblock >}}

{{< codeblock lang="sh" title="اجرا در سرور به عنوان مدیر" >}}
$ sysctl security.bsd.see_other_uids=0
security.bsd.see_other_uids: 1 -> 0

$ sysctl security.bsd.see_other_gids=0
security.bsd.see_other_gids: 1 -> 0

$ sysctl security.bsd.see_jail_proc=0
security.bsd.see_jail_proc: 1 -> 0

$ sysctl security.bsd.unprivileged_read_msgbuf=0
security.bsd.unprivileged_read_msgbuf: 1 -> 0

$ sysctl security.bsd.unprivileged_proc_debug=0
security.bsd.unprivileged_proc_debug: 1 -> 0

$ sysctl kern.randompid=1
kern.randompid: 0 -> 563

$ sysctl security.bsd.stack_guard_page=1
security.bsd.stack_guard_page: 1 -> 1
{{< /codeblock >}}

## سخت‌تر نمودن سیستم در مقابل حملات Denial of Service

{{< codeblock lang="sh" title="/etc/sysctl.conf" >}}
# SYN flood DoS attack protection
net.inet.tcp.syncookies=1
{{< /codeblock >}}

{{< codeblock lang="sh" title="اجرا در سرور به عنوان مدیر" >}}
$ sysctl net.inet.tcp.syncookies=1
net.inet.tcp.syncookies: 1 -> 1
{{< /codeblock >}}

## فعال‌سازی و تنظیم دیوار آتش

{{< codeblock lang="sh" title="/usr/local/etc/rc.firewall" >}}
#!/usr/bin/env sh

#  (The MIT License)
#
#  Copyright (c) 2015 - 2019 Mamadou Babaei
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


. /etc/rc.subr

load_rc_config firewall

fw_add="/sbin/ipfw -q add"

if [ -z "${firewall_myservices_rules_id_start}" ] ;
then
    firewall_myservices_rules_id_start=56000
fi

if [ -z "${firewall_myservices_rules_id_step}" ] ;
then
    firewall_myservices_rules_id_step=10
fi

case ${1} in
quietstart)
        rule_id=${firewall_myservices_rules_id_start}

        for i in ${firewall_allowservices} ;
        do
            for j in ${firewall_myservices_tcp} ;
            do
                ${fw_add} ${rule_id} pass tcp from ${i} to me ${j}
                rule_id=`expr $rule_id + ${firewall_myservices_rules_id_step}`
            done
        done

        for i in ${firewall_allowservices} ;
        do
            for j in ${firewall_myservices_udp} ;
            do
                ${fw_add} ${rule_id} pass udp from ${i} to me ${j}
                rule_id=`expr $rule_id + ${firewall_myservices_rules_id_step}`
            done
        done
    ;;
quietstop)
    ;;
*)
    echo "Error: unknown parameter '${1}'"
    ;;
esac
{{< /codeblock >}}

{{< codeblock lang="sh" title="اجرا در سرور به عنوان مدیر" >}}
$ chmod u-w,ugo+x /usr/local/etc/rc.firewall
{{< /codeblock >}}

{{< codeblock lang="sh" title="/etc/rc.conf" >}}
# ipfw
firewall_enable="YES"
firewall_quiet="YES"
firewall_type="workstation"
firewall_allowservices="any"
firewall_logdeny="YES"
firewall_coscripts="/usr/local/etc/rc.firewall"
firewall_myservices_rules_id_start="56000"
firewall_myservices_rules_id_step="10"
firewall_myservices_tcp="22 443"
firewall_myservices_udp="443"
{{< /codeblock >}}

{{< codeblock lang="sh" title="/etc/sysctl.conf" >}}
# ipfw
net.inet.ip.fw.verbose_limit=5
{{< /codeblock >}}

{{< codeblock lang="sh" title="اجرا در سرور به عنوان مدیر" >}}
$ service ipfw restart
{{< /codeblock >}}

{{< codeblock lang="sh" title="اجرا در سرور به عنوان مدیر" >}}
$ sysctl net.inet.ip.fw.verbose_limit=5
net.inet.ip.fw.verbose_limit: 0 -> 5
{{< /codeblock >}}

## فعال‌سازی و تنظیم سیستم تشخیص و پیشگیری از نفوذ SSHGuard

{{< codeblock lang="sh" title="" >}}
$ pkg install security/sshguard
{{< /codeblock >}}

{{< codeblock lang="sh" title="/etc/rc.conf" >}}
# sshgaurd
sshguard_enable="YES"
sshguard_pidfile="/var/run/sshguard.pid"
sshguard_watch_logs="/var/log/auth.log:/var/log/maillog"
sshguard_blacklist="30:/var/db/sshguard/blacklist.db"
sshguard_sshguard_danger_thresh="30"
sshguard_release_interval="120"
sshguard_reset_interval="1800"
sshguard_whitelistfile="/usr/local/etc/sshguard.whitelist"
sshguard_flags=""
{{< /codeblock >}}

{{< codeblock lang="sh" title="اجرا در سرور به عنوان مدیر" >}}
$ service sshguard start
{{< /codeblock >}}

نکته‌ای که ذکر آن حائز اهمیت به نظر می‌رسد این است که در FreeBSD امکان استفاده و پیکربندی سایر نرم‌افزارهای IDS و IPS نظیر <code>security/ossec-hids-local</code>, <code>security/suricata</code>, <code>security/snort</code>, <code>security/chkrootkit</code>, <code>security/revealrk</code>, <code>security/rkhunter</code> و ... به منظور افزایش حداکثری ضریب امنیت وجود دارد و امکان نصب و پیکربندی آن‌ها در این مطلب وجود داشت، اما برای کاربرد در سرور مدنظر ما که کاربردش تنها یک سرویس VPN و سرور SSH می‌باشد، کمی بیش از حد به نظر می‌رسد. لذا در اینجا به ذکر نام آن‌ها بسنده می‌نمایم.



## فعاال سازی TCP Fast Open

{{< codeblock lang="sh" title="/etc/sysctl.conf" >}}
# tcp fast open (TFO)
net.inet.tcp.fastopen.client_enable=1
net.inet.tcp.fastopen.server_enable=1
{{< /codeblock >}}

{{< codeblock lang="sh" title="اجرا در سرور به عنوان مدیر" >}}
$ sysctl net.inet.tcp.fastopen.client_enable=1
net.inet.tcp.fastopen.client_enable: 1 -> 1

$ sysctl net.inet.tcp.fastopen.server_enable=1
net.inet.tcp.fastopen.server_enable: 0 -> 1
{{< /codeblock >}}

## بهینه‌سازی و تنظیم محدودیت های هسته سیستم‌عامل

{{< codeblock lang="sh" title="اجرا در سرور به عنوان مدیر" >}}
$ ulimit -a
cpu time               (seconds, -t)  unlimited
file size           (512-blocks, -f)  unlimited
data seg size           (kbytes, -d)  33554432
stack size              (kbytes, -s)  524288
core file size      (512-blocks, -c)  unlimited
max memory size         (kbytes, -m)  unlimited
locked memory           (kbytes, -l)  unlimited
max user processes              (-u)  5734
open files                      (-n)  28377
virtual mem size        (kbytes, -v)  unlimited
swap limit              (kbytes, -w)  unlimited
socket buffer size       (bytes, -b)  unlimited
pseudo-terminals                (-p)  unlimited
kqueues                         (-k)  unlimited
umtx shared locks               (-o)  unlimited

$ ulimit -n
28377

$ ulimit -Hn
28377

$ ulimit -Sn
28377
{{< /codeblock >}}

{{< codeblock lang="sh" title="/boot/loader.conf" >}}
# kernel limits
kern.maxfiles="51200"
kern.maxfilesperproc="51200"
{{< /codeblock >}}

{{< codeblock lang="sh" title="اجرا در سرور به عنوان مدیر" >}}
$ reboot
{{< /codeblock >}}

{{< codeblock lang="sh" title="اجرا در سرور به عنوان مدیر" >}}
$ ulimit -a
cpu time               (seconds, -t)  unlimited
file size           (512-blocks, -f)  unlimited
data seg size           (kbytes, -d)  33554432
stack size              (kbytes, -s)  524288
core file size      (512-blocks, -c)  unlimited
max memory size         (kbytes, -m)  unlimited
locked memory           (kbytes, -l)  unlimited
max user processes              (-u)  5734
open files                      (-n)  51200
virtual mem size        (kbytes, -v)  unlimited
swap limit              (kbytes, -w)  unlimited
socket buffer size       (bytes, -b)  unlimited
pseudo-terminals                (-p)  unlimited
kqueues                         (-k)  unlimited
umtx shared locks               (-o)  unlimited

$ ulimit -n
51200

$ ulimit -Hn
51200

$ ulimit -Sn
51200
{{< /codeblock >}}

## نصب پیش‌نیازهای دریافت و اجرای ShadowsocksR

{{< codeblock lang="sh" title="اجرا در سرور به عنوان مدیر" >}}
$ pkg install security/ca_root_nss devel/git dns/c-ares devel/libev devel/py-typing devel/py-typing-extensions lang/python math/py-pybloom security/libsodium security/py-m2crypto security/mbedtls
{{< /codeblock >}}

{{< codeblock lang="sh" title="اجرا در سرور به عنوان مدیر" >}}
$ pkg autoremove
$ rm -f /var/cache/pkg/*
{{< /codeblock >}}

## دریافت و پیکربندی ShadowsocksR

{{< codeblock lang="sh" title="اجرا در سرور به عنوان مدیر" >}}
$ cd /usr/local/
$ git clone https://github.com/shadowsocksrr/shadowsocksr.git
$ cd shadowsocksr
$ sh initcfg.sh
{{< /codeblock >}}

{{< codeblock lang="json" title="/usr/local/shadowsocksr/config.json" >}}
{
    "server": "xxx.xxx.xxx.xxx",
    "server_ipv6": "xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx",
    "server_port": 443,
    "local_address": "127.0.0.1",
    "local_port": 1443,

    "password": "#IranProtests",
    "method": "chacha20",
    "protocol": "auth_sha1_v4_compatible",
    "protocol_param": "",
    "obfs": "http_simple_compatible",
    "obfs_param": "",
    "speed_limit_per_con": 0,
    "speed_limit_per_user": 0,

    "additional_ports" : {}, // only works under multi-user mode
    "additional_ports_only" : false, // only works under multi-user mode
    "timeout": 120,
    "udp_timeout": 60,
    "dns_ipv6": true,
    "connect_verbose_info": 0,
    "redirect": "",
    "fast_open": true
}
{{< /codeblock >}}

{{< codeblock lang="sh" title="اجرا در سرور به عنوان مدیر" >}}
$ chmod 400 /usr/local/shadowsocksr/config.json
{{< /codeblock >}}

{{< codeblock lang="sh" title="/usr/local/shadowsocksr/cron.sh" >}}
#!/bin/sh
cd /usr/local/shadowsocksr/shadowsocks && python ./server.py -c ../config.json &
{{< /codeblock >}}

{{< codeblock lang="sh" title="اجرا در سرور به عنوان مدیر" >}}
chmod a+x /usr/local/shadowsocksr/cron.sh
{{< /codeblock >}}

{{< codeblock lang="sh" title="crontab -e -u root" >}}
SHELL=/bin/sh
PATH=/sbin:/bin:/usr/sbin:/usr/bin:/usr/local/sbin:/usr/local/bin
MAILTO=""

# shadowsocksr
@reboot root    /usr/local/shadowsocksr/cron.sh
{{< /codeblock >}}

{{< codeblock lang="sh" title="اجرا در سرور به عنوان مدیر" >}}
$ crontab -l -u root
{{< /codeblock >}}

{{< codeblock lang="sh" title="اجرا در سرور به عنوان مدیر" >}}
$ reboot
{{< /codeblock >}}

## سیستم را بروز نگه دارید!

{{< codeblock lang="sh" title="crontab -e -u root" >}}
# fetch and notify root for system's security patches
@daily  root    /usr/sbin/freebsd-update cron
{{< /codeblock >}}

{{< codeblock lang="sh" title="اجرا در سرور به عنوان مدیر" >}}
$ crontab -l -u root
{{< /codeblock >}}

{{< codeblock lang="sh" title="اجرا در سرور به عنوان مدیر" >}}
$ pkg audit
pkg: vulnxml file (null) does not exist. Try running 'pkg audit -F' first

$ pkg audit -F
Fetching vuln.xml.bz2: 100%  821 KiB 841.0kB/s    00:01    
0 problem(s) in 0 installed package(s) found.

$  pkg audit
0 problem(s) in 0 installed package(s) found.
{{< /codeblock >}}

{{< codeblock lang="sh" title="اجرا در سرور به عنوان مدیر" >}}
$ pkg update
$ pkg upgrade
{{< /codeblock >}}

{{< codeblock lang="sh" title="اجرا در سرور به عنوان مدیر" >}}
$ cd /usr/local/shadowsocksr
$ git pull
{{< /codeblock >}}

## نصب کلاینت در Microsoft Windows

در سیستم‌عامل Windows می‌توانید [shadowsocksrr/shadowsocksr-csharp](https://github.com/shadowsocksrr/shadowsocksr-csharp/releases) را نصب و پیکربندی نمایید. پس از گشودن فایل فشرده این نرم‌افزار با دو فایل اجرایی مواجه خواهید شد که هر دوی آن‌ها یک نرم‌افزار یکسان می‌باشند و در کارایی تفاوتی ندارند. تنها تفاوت این دو نرم‌افزار این است که یکی از آن‌ها جهت اجرا شدن نیازمند نصب [Microsoft .Net Framework 2.0](https://www.microsoft.com/en-us/download/details.aspx?id=1639) و دیگری نیازمند نصب [Microsoft .Net Framework 4.0](https://dotnet.microsoft.com/download/dotnet-framework/net40) می‌باشد.

## نصب کلاینت در Android

در سیستم‌عامل Android می‌توانید [shadowsocksrr/shadowsocksr-android](https://github.com/shadowsocksrr/shadowsocksr-android/releases) را نصب و پیکربندی نمایید.

## نصب کلاینت در iOS

در سیستم‌عامل iOS می‌توانید اپلیکیشن [Potatso Lite](https://apps.apple.com/us/app/potatso-lite/id1239860606) را نصب و پیکربندی نمایید که به خوبی از ShadowsocksR پشتیبانی نموده و با آن سازگار می‌باشد.

## نصب کلاینت در macOS

در سیستم‌عامل macOS می‌توانید [ShadowsocksR-Live/ssrMac](https://github.com/ShadowsocksR-Live/ssrMac/releases) را نصب و پیکربندی نمایید.

## نصب کلاینت در GNU/Linux یا سایر سیستم‌عامل‌های یونیکس یا شبه‌یونیکس

{{< codeblock lang="sh" title="اجرا در کلاینت" >}}
$ cd /opt/
$ sudo git clone https://github.com/shadowsocksrr/shadowsocksr.git
{{< /codeblock >}}

{{< codeblock lang="json" title="/opt/shadowsocksr/shadowsocks/shadowsocks-1443.json" >}}
{
    "server": "xxx.xxx.xxx.xxx",
    "server_ipv6": "xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx",
    "server_port": 443,
    "local_address": "127.0.0.1",
    "local_port": 1443,

    "password": "#IranProtests",
    "method": "chacha20",
    "protocol": "auth_sha1_v4_compatible",
    "protocol_param": "",
    "obfs": "http_simple_compatible",
    "obfs_param": "",
    "speed_limit_per_con": 0,
    "speed_limit_per_user": 0,

    "additional_ports" : {}, // only works under multi-user mode
    "additional_ports_only" : false, // only works under multi-user mode
    "timeout": 120,
    "udp_timeout": 60,
    "dns_ipv6": true,
    "connect_verbose_info": 0,
    "redirect": "",
    "fast_open": true
}
{{< /codeblock >}}

{{< codeblock lang="sh" title="اجرا در کلاینت" >}}
$ sudo chmod 0400 /opt/shadowsocksr/shadowsocks/shadowsocks-1443.json
{{< /codeblock >}}

{{< codeblock lang="json" title="/etc/local.d/ShadowsocksR-1443.start" >}}
#!/bin/sh
cd /opt/shadowsocksr/shadowsocks && python ./local.py -c ./shadowsocks-1443.json &
{{< /codeblock >}}


{{< codeblock lang="sh" title="/etc/proxychains.conf" >}}
strict_chain
quiet_mode
proxy_dns
tcp_read_time_out 15000
tcp_connect_time_out 8000
[ProxyList]
socks5 127.0.0.1 1443
{{< /codeblock >}}

**نکته**: <code>proxychains</code> به ترتیب زیر فایل تنظیمات را جستجو می‌نماید:

۱. فایل مشخص شده در متغیر محیطی <code>PROXYCHAINS_CONF_FILE</code> یا پارامتر مشخص شده برای سوییچ <code>-f</code>

۲. در مسیر جاری <code>./proxychains.conf</code>

۳. در مسیر <code>$(HOME)/.proxychains/proxychains.conf</code>

۴. در مسیر <code>$(sysconfdir)/proxychains.conf</code>؛ برای مثال در عمده توزیع‌های گنو/لینوکس <code>/etc/proxychains.conf</code> و در فری‌بی‌اس‌دی <code>/usr/local/etc/proxychains.conf</code>
