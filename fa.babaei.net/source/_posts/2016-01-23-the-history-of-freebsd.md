---
title: "The History of FreeBSD"
date: 2016-01-23 13:25:06
tags:
  - FLOSS
  - FreeBSD
  - GNU
  - LINUX
  - Open Source
  - UNIX
---

<div class="post-title-fa">تاریخچه FreeBSD</div>

[{% img post-image /blog/2016/01/23/the-history-of-freebsd/evolution-of-unix-and-unix-like-systems.png 1959 1306 "'نمودار سیر تکاملی سیستم عامل های Unix و شبه Unix'" "'نمودار سیر تکاملی سیستم عامل های Unix و شبه Unix'" %}](/blog/2016/01/23/the-history-of-freebsd/evolution-of-unix-and-unix-like-systems.png)
<span class="post-image-title">نمودار سیر تکاملی سیستم عامل های یونیکس و شبه یونیکس - منبع تصویر: [ویکی پدیا](https://en.wikipedia.org/wiki/File:Unix_history-simple.svg)</span>

اگر از یک سیستم عامل آزاد و کد باز استفاده می نمائید، به احتمال قریب به یقین مبتنی بر [گنو](https://www.gnu.org/) و [هسته لینوکس](https://www.kernel.org/) می باشد. اما باید بدانید این پلتفرم های کد باز و آزاد نه تنها اولین نرم افزارها در نوع خود نبوده، حتی حرفه ای ترین و یا موفق ترین نرم افزارهای کد باز تجاری شده در نوع خود نیز محسوب نخواهند شد. در هر سه این موارد [Berkeley Software Distribution یا به اختصار BSD](https://en.wikipedia.org/wiki/Berkeley_Software_Distribution)  از [GNU/Linux](http://www.gnu.org/gnu/linux-and-gnu.en.html)  پیشی می گیرد. حال سوال اصلی اینجاست که چرا BSD در [اکوسیستم نرم افزارهای آزاد](https://en.wikipedia.org/wiki/Free_and_open-source_software) به حاشیه رانده شده است، در حالی که توزیع های مختلف GNU/Linux گوی سبقت را از آن ربوده اند؟

در سه قسمت اول از سری آموزش های FreeBSD در ابتدا به تاریخچه آن خواهیم پرداخت. در [قسمت دوم](/blog/2016/01/27/what-is-freebsd-an-overview-of-freebsd-operating-system/) اقدام به بررسی ماهیت و ویژگی های آن نموده و با ساختار و مفاهیم آن آشنا خواهیم شد. و در نهایت در قسمت سوم آن را با GNU/Linux مقایسه می نماییم. پس از این سه قسمت در مقالات بعدی اقدام به نصب و راه اندازی FreeBSD جهت استفاده در Server به همراه نصب سرویس های مختلف از جمله Web Server, FTP Server, Mail Server, DNS Server و ... جهت استفاده در محیط های Production می نمائیم. در کنار آن به نصب و پیکربندی FreeBSD در Desktop جهت Web Browsing, Multimedia و ... خواهیم پرداخت. همچنین اقدام به توضیح مفاهیم یونیکس از ابتدا می نمائیم. در ادامه این مقاله به قسمت اول، تاریخچه FreeBSD خواهیم پرداخت.

<!-- more -->


<br />

### فهرست ###

* [BSD](#bsd-history)
* [GNU/Linux](#gnu-linux)
* [FreeBSD](#freebsd-history)
* [دلایل عدم اقبال عموم به BSD](#lack-of-public-interest-in-bsd)
* [میراث BSD](#bsd-legacy)
* [منابع](#references)


<br />
<a name="bsd-history"></a>

### BSD ###

درک BSD نیازمند کاوش تاریخچه آن و بازگشت به عقب تا مبدا آن یعنی [UNIX](http://www.unix.org/) می باشد. سیستم عاملی که اولین بار در سال 1969 توسط [AT&T Bell Labs](https://en.wikipedia.org/wiki/Bell_Labs) منتشر شد. در سال 1969 [Ken Thompson](https://en.wikipedia.org/wiki/Ken_Thompson) و [Denise Ritchie](https://en.wikipedia.org/wiki/Dennis_Ritchie)  کار را بر روی سیستم عاملی بی نام که بعدها UNIX  نامیده شد در AT&T Bell Labs آغاز نمودند. در ابتدا این سیستم عامل بر روی یک [DEC PDP-7](https://en.wikipedia.org/wiki/PDP-7) که یک مینی کامپیوتر بود توسعه و اجرا می شد. برای قریب یک دهه توسعه UNIX [تحت نام هائی که با عدد شناخته می شد](https://en.wikipedia.org/wiki/List_of_Unix_systems) در [AT&T](https://www.att.com/) انجام می گرفت. V4 (1974) به شکل کامل در [C](https://en.wikipedia.org/wiki/C_%28programming_language%29)  بازنویسی شد که گام بزرگی جهت پرتابل نمودن این سیستم عامل در دستگاه های مختلف تلقی می شد. V6 (1975) اولین نسخه از این سیستم عامل بود که در خارج از [Bell Labs](http://www.belllabs.com/)  در دسترس قرار گرفت و اولین UNIX در [دانشگاه برکلی](http://www.berkeley.edu/)  بر مبنای آن توسعه داده شد. در آغاز BSD حیات خود را به عنوان گونه ای از UNIX توسط گروهی از دانشجویان در دانشگاه برکلی کالیفرنیا که در آغاز توسط [Bill Joy](https://en.wikipedia.org/wiki/Bill_Joy) –   موسس شرکت [Sun Microsystems](https://en.wikipedia.org/wiki/Sun_Microsystems)  که بعدها توسط [Oracle](https://www.oracle.com/)  خریداری شد - رهبری می شدند آغاز کرد.

Bell Labs همچنان کار بر روی UNIX تا دهه 80 میلادی را ادامه داد. با تصمیم AT&T مبنی بر تجاری سازی UNIX تقاضا برای عرضه نسخه ای رایگان و آزاد از UNIX بدون پرداخت حق لیسانس سنگین آن بالا گرفت. از آنجا که بخش عمده ای از کدهای BSD UNIX را کدهای AT&T UNIX تشکیل می داد تمامی استفاده کنندگان BSD می بایست حق لیسانس استفاده از آن را به AT&T پرداخت می نمودند. در نتیجه برنامه نویسان دانشگاه برکلی به منظور جدا نمودن کد خود از AT&T تلاش بی وقفه ای جهت توسعه و عرضه سیستم عاملی مشابه UNIX را آغاز نمودند. با عرضه BSD 4.2 در 1984 دانشگاه ها و شرکت های بسیاری اقدام به مهاجرت به آن نمودند تا آنجا که UNIX BSD پس از UNIX اصلی به عنوان دومین UNIX مورد استفاده تلقی می شد. حتی برخی از قابلیت های آن به [نسخه SVR4 سیستم عامل UNIX](https://en.wikipedia.org/wiki/UNIX_System_V#SVR4) راه یافت.

تلاش ها تا سال 1991 و عرضه نسخه Networking Release 2 یا به اختصار Net/2 از BSD ادامه یافت. برخلاف نسخه قبلی Net/1 (1989)  و نسخ پیش از آن که فقط برخی قابلیت ها مانند TCP/IP, Virtual Memory و Unix File System را به کد UNIX اصلی اضافه کرده بود و یک سیستم عامل کاملا آزاد محسوب نمی شد این نسخه یک سیستم عامل شبه یونیکس کامل بود که فقط 6 فایل سورس از Kernel اصلی UNIX را به همراه داشت. در واقع پس از عرضه Net/1 به پیشنهاد [Keith Bostic](https://en.wikipedia.org/wiki/Keith_Bostic)  بسیاری از بخش ها و ابزارهای کمکی AT&T از نو بازنویسی و با کد جدید جایگزین شد. به عنوان نمونه[vi](https://en.wikipedia.org/wiki/Vi)   که مبتی بر [ed](https://en.wikipedia.org/wiki/Ed_%28text_editor%29 )  در نسخه اصلی UNIX بود با [nvi یا new vi](https://en.wikipedia.org/wiki/Nvi)  جایگزین شد. پس از عرضه Net/2 در کمتر از 6 ماه [William Jolitz - که با نام Bill Jolitz هم شناخته می شود -](https://en.wikipedia.org/wiki/William_Jolitz)  به همراه همسرش [Lynne Jolitz](https://en.wikipedia.org/wiki/Lynne_Jolitz)  شش فایل ذکر شده را بازنویسی و جایگزین نموده، سپس BSD را به میکرو پروسسورهای خانواده [Intel 80386](https://en.wikipedia.org/wiki/Intel_80386) پورت نمودند. آن ها این نسخه را [386BSD](http://www.386bsd.org/)  نامیده و آن را بر روی FTP در دسترس همگان قرار دادند.

از آنجائی که Net/2 BSD تحت لیسانس بسیار دست و دلبازانه ای عرضه می شد و به همگان اجازه استفاده، مطالعه، تغییر و حتی ایجاد یک سیستم عامل جدید بر اساس سورس کدش را می داد به یقین اولین سیستم عامل Open Source متن باز محسوب می شود. با وجود این که در آن زمان عبارت Open Source وجود نداشت و Net/2 هیچگاه مورد تائید [Free Software Foundation یا به اختصار FSF (بنیاد نرم افزارهای آزاد)](http://www.fsf.org/)  قرار نگرفت این سیستم عامل هنوز هم یک گام رو به جلوی بزرگ برای جامعه نرم افزارهای آزاد محسوب می شد چرا که ثابت نمود توسعه نسخه ای آزاد از UNIX امکان پذیر است.


<br />
<a name="gnu-linux"></a>

### GNU/Linux ###

البته BSD تنها تلاش جهت توسعه و عرضه یک UNIX آزاد نبود. [Richard Stallman](https://en.wikipedia.org/wiki/Richard_Stallman)  در سال 1983  در [انستیتو تکنولوژی دانشگاه Massachusetts یا به اختصارMIT](http://mit.edu/)، پروژه [GNU](http://www.gnu.org/) را معرفی و در سال 1984 کار بر روی آن را آغاز نمود. GNU مخفف عبارت GNU’s Not UNIX می باشد. تا اوایل دهه 90 میلادی بخش عمده ای از این سیستم عامل آزاد تحت نظارت FSF که Stallman موسس آن بود شامل [GNU C Library](https://www.gnu.org/software/libc/) همچنین [Bourne Again Shell یا به اختصار BASH](https://www.gnu.org/software/bash/) و [GNU C Compiler یا به اختصار GCC](https://gcc.gnu.org/) می شد با موفقیت توسعه داده شد، جز یک بخش آن: کرنل. در اوایل دهه 90 میلادی کار بر روی [GNU Hurd](https://www.gnu.org/software/hurd/)  که هسته این سیستم عامل بود آغاز شد. از آنجا که با تصمیم Stallman معماری هسته این سیستم عامل [Microkernel](https://www.gnu.org/software/hurd/faq/multiserver_microkernel.html)  در نظر گرفته شد توسعه آن به دلیل پیچیدگی های فراوان با سرعت بسیار پائینی صورت می گرفت.

در پائیز سال 1991 در دانشگاه Helsinki فنلاند دانشجوئی به نام [Linus Torvalds](https://en.wikipedia.org/wiki/Linus_Torvalds) با الهام از سیستم عاملی به نام [MINIX](http://www.minix3.org/) که[Andrew S. Tanenbaum](https://en.wikipedia.org/wiki/Andrew_S._Tanenbaum) جهت آموزش مفاهیم سیستم عامل به دانشجویان در کتاب خود، توسعه داده بود، کار توسعه هسته Linux را آغاز نمود. این نسخه از MINIX شامل 12,000 خط کد C بود و برای کامپیوترهای شخصی [IBM](http://www.ibm.com/) توسعه داده شده بود. در نهایت رویای Stallman با قرار گرفتن هسته Linux در کنار GNU به واقعیت پیوست و در سال 1994  نسخه 1.0 از Linux منتشر شد. بسیاری این سیستم عامل را به نام Linux می شناسند، هرچند از آن جا که Linux فقط یک هسته است [ترجیح Stallman این است که این سیستم عامل GNU/Linux نامیده شود.](http://www.gnu.org/gnu/linux-and-gnu.en.html)


<br />
<a name="freebsd-history"></a>

### FreeBSD ###

از آنجائی که توسعه 386BSD بسیار کند پیش می رفت، گروهی از کاربران آن از جمله Nate Williams, Rod Grimes و [Jordan Hubbard](https://en.wikipedia.org/wiki/Jordan_Hubbard) تصمیم به ایجاد سیستم عامل دیگری بر اساس کد 4.3BSD-Lite (Net/2) (که توسط دانشگاه برکلی ارایه شده بود) به همراه بهبودهائی که از طریق 386BSD حاصل شده بود نمودند. همچنین این سیستم عامل بخش هائی از پروژه GNU که توسط FSF ارایه شده بود را به همراه داشت. نام [FreeBSD](https://www.freebsd.org/) توسط David Greenman پیشنهاد شد. Hubbard جهت منتشر نمودن این سیستم عامل به سراغ کمپانی [Walnut Creek CDROM](https://en.wikipedia.org/wiki/Walnut_Creek_CDROM) رفت. سرانجام FreeBSD 1.0 در نوامبر 1993 منتشر شد. این کمپانی علاوه بر انتشار FreeBSD بر روی CD برای افرادی که به اینترنت دسترسی نداشتند، یک دستگاه کامپیوتر قدرتمند و یک خط اینترنت پرسرعت را در اختیار پروژه قرار داد. تا سال 1997، FreeBSD موفق ترین محصول این کمپانی شناخته شد. در سال 2000 این کمپانی با [BSDI]( https://en.wikipedia.org/wiki/Berkeley_Software_Design) که خود توسط یکی از کلیدی ترین چهره های دنیای اینترنت [Rick Adams](https://en.wikipedia.org/wiki/Rick_Adams_(Internet_pioneer))  و چهره های کلیدی دنیای BSD از گروه [Computer Systems Research Group یا به اختصار CSRG](https://en.wikipedia.org/wiki/Berkeley_Software_Design) شامل [Marshall Kirk McKusick](https://en.wikipedia.org/wiki/Marshall_Kirk_McKusick), Keith Bostic, [Mike Karels](https://en.wikipedia.org/wiki/Michael_J._Karels), Bill Jolitz و Donn Seeley می شد، تلفیق شد. در سال 2001 تمامی متعلقات نرم افزاری BSDI شامل FreeBSD, [Slackware Linux]( http://www.slackware.com/) و [BSD/OS]( https://en.wikipedia.org/wiki/BSD/OS) توسط شرکت [Wind River Systems](https://en.wikipedia.org/wiki/Wind_River_Systems) خریداری شد و مابقی شرکت با تمرکز بر سخت افزار به [iXsystems](https://en.wikipedia.org/wiki/IXsystems) تغییر نام داد. پس از آن Wind River Systems به پشتیبانی از Slackware Linux خاتمه داد در حالیکه بخش FreeBSD به عنوان یک واحد مستقل تحت نام [FreeBSD Mall, Inc.]( https://www.freebsdmall.com/) به کار خود ادامه داد. تا به امروز iXsystems و FreeBSD Mall از اصلی ترین حامیان FreeBSD محسوب می شوند.

پس از اولین نسخه موفقیت آمیز از FreeBSD، نسخه 1.1 این سیستم عامل در ماه مه 1994 عرضه شد. به دلیل مسایل حقوقی که در ادامه بدان خواهیم پرداخت، آخرین نسخه از FreeBSD 1.x تحت عنوان 1.1.5.1 در جولای همان سال عرضه و کار بر روی آن متوقف شد. سپس کار بر روی 4.4BSD-Lite که عاری از کد Net/2 و مسایل حقوقی بود آغاز گشت. با توجه به مسایل حقوقی، تیم CSRG دانشگاه برکلی مجبور به حذف بخش های عمده ای از Net/2 در نسخه 4.4BSD-Lite به خصوص پورت Intel آن شده بود که باعث می شد این نسخه از BSD حتی قابل Boot شدن هم نباشد. تا نوامبر همان سال تیم FreeBSD موفق به انتقال به این نسخه از BSD گشت و در نهایت در دسامبر 1994 نسخه 2.0  این سیستم عامل عرضه شد. به دلیل  مشکلاتی که در این نسخه از FreeBSD وجود داشت در ژوئن 1995 نسخه پایداری از آن تحت عنوان FreeBSD 2.0.5 عرضه شد.

از آن زمان تا کنون به شکل مستمر نسخه های FreeBSD یکی پس از دیگری، با افزایش پایداری، سرعت و قابلیت های جدید عرضه می شود. آخرین نسخه از این سیستم عامل در زمان این نوشتار 10.2  می باشد. انتظار می رود بزودی و در سال جاری [مطابق برنامه](https://www.freebsd.org/releases/11.0R/schedule.html)، نسخه 11.0  این سیستم عامل عرضه شود.

شایان ذکر است که از سال 2001 به بعد پروژه FreeBSD تحت نظر The FreeBSD Foundation[ یا بنیاد FreeBSD](https://www.freebsdfoundation.org/) اداره می شود.


<br />
<a name="lack-of-public-interest-in-bsd"></a>

### دلایل عدم اقبال عموم به BSD ###

خب! سوال اصلی اینجاست که اگر BSD Net/2 اولین سیستم عامل کدباز بود، پس چرا فرصت درخشش در نزد عموم نصیب GNU/Linux شد؟ دلایل این موضوع را می توان در موارد ذیل خلاصه نمود:

* مسایل حقوقی: مدل Source Code Licensing شرکت AT&T به سایر شرکت ها در ازای پرداخت حق لیسانس، اجازه ساخت سیستم عامل مبنی بر UNIX خود را با برند اختصاصی می داد (از آن جمله [Microsoft Xenix](https://en.wikipedia.org/wiki/Xenix) که بعدها به [SCO](https://en.wikipedia.org/wiki/Santa_Cruz_Operation)  فروخته شد، [SunOS](https://en.wikipedia.org/wiki/SunOS)  که بعدها مبنای [Solaris](https://en.wikipedia.org/wiki/Solaris_%28operating_system%29)  قرار گرفت، [AIX شرکت IBM](https://en.wikipedia.org/wiki/IBM_AIX )  و [HP-UX](https://en.wikipedia.org/wiki/HP-UX)). در ابتدای دهه 90 میلادی [Unix System Laboratories یا به اختصار USL](https://en.wikipedia.org/wiki/Unix_System_Laboratories)  که زیر مجموعه ای از Bell Labs بود پس از تلفیق با بخش دیگری از این شرکت با نام UNIX Software Operation مسئولیت توسعه و لیسانس نمودن UNIX را به عهده گرفت. بعدها این شرکت مستقلا زیرمجموعه AT&T شد. پس از این اتفاق در دعوای حقوقی که [USL vs BSDI](https://en.wikipedia.org/wiki/UNIX_System_Laboratories,_Inc._v._Berkeley_Software_Design,_Inc.) شناخته می شود این کمپانی شرکت [Berkeley Software Design, Inc.](https://en.wikipedia.org/wiki/Berkeley_Software_Design)  به همراه [هیات امنای دانشگاه برکلی](https://en.wikipedia.org/wiki/Regents_of_the_University_of_California) را با ادعای زیرپا نهادن حقوق مالکیت مادی و معنوی USL مورد تعقیب قضائی قرار داد. در سال 1992 دادگاه بسیاری از موارد را نامعتبر دانسته و در مقابل دانشگاه کالیفرنیا دعوای حقوقی دیگری را علیه USL مطرح می نماید که باعث به درازا کشیده شدن مسایل حقوقی می شود. پس از خرید USL توسط [Novell](https://en.wikipedia.org/wiki/Novell) در سال 1993، سرانجام در یک سری از مذاکرات دوستانه مسایل حقوقی تا اوایل سال 1994 حل و فصل می شود. متاسفانه مجموعه این مسایل حقوقی سر نوشت این سیستم عامل را در نگاه بسیاری تیره و تار جلوه می داد. لازم به ذکر است که Linux هم مسایل حقوقی مشابهی را در سال های ابتدائی 2000 تجربه می نماید که در سال 2007 به نفع GNU/Linux خاتمه می یابد. Santa Cruz Operation یا به اختصار SCO - که بخش تجاری UNIX را در سال 1995  از Novell خریداری می نماید - شکایات متعددی را برعلیه توزیع کنندگان عمده تجاری GNU/Linux (شامل IBM و Novell) و چند شرکت استفاده کننده GNU/Linux مطرح می نماید. این در حالی است که Novell در زمان فروش تجارت UNIX به SCO تمامی حقوق UNIX را به کنسرسیوم [X/Open](https://en.wikipedia.org/wiki/X/Open)  که در سال 1996 پس از تلفیق با [Open Software Foundation](https://en.wikipedia.org/wiki/Open_Software_Foundation)  با نام [The Open Group](http://www.opengroup.org/)  شناخته می شود، منتقل می نماید.
* لیسانس: یکی از دلایل عدم علاقه بسیاری از برنامه نویسان و [hacker ها](https://stallman.org/articles/on-hacking.html) به BSD، [لیسانس بسیار دست و دلبازانه آن](https://en.wikipedia.org/wiki/BSD_licenses) است. بگذارید این را با مثالی بیان کنم. فرض کنید شما دو فرزند دارید. در حالیکه که دیگر فرزند شما حضور ندارد، یک جعبه شکلات به فرزندتان می دهید. شما به فرزندتان گوشزد می نمائید که دقیقا نیمی از شکلات ها را به برادر یا خواهرش بدهد. در این جا فرزند شما هیچ حق انتخابی ندارد و شما به عنوان کسی که شکلات را به او می دهد تصمیم گیرنده هستید. این لیسانس دقیقا GNU/Linux یا همان [GPL (GNU General Public License)](https://en.wikipedia.org/wiki/GNU_General_Public_License) است. در این حالت شما باید تمامی حقوق مورد استفاده خود را به کاربر بعدی بدهید. حال فرض کنید به جای حالت قبلی به فرزندتان می گوئید که می تواند هر میزان شکلات که خواست برای خودش بردارد و مابقی آن را به برادر یا خواهرش بدهد یا اینکه اصلا هیچ شکلاتی به او ندهد و تمامی را برای خودش بردارد. در واقع حق انتخاب با اوست و شما دست او را باز می گذارید. این همان لیسانس BSD است (و البته لیسانس های مشابه مانند [MIT](https://en.wikipedia.org/wiki/MIT_License), [zlib](https://en.wikipedia.org/wiki/Zlib_License) و ...). شما می توانید حقوق مورد استفاده خود را به کاربر بعدی بدهید یا خیر. با وجود این که هر دوی این لیسانس ها 4 حق _استفاده_، _مطالعه_، _تغییر_ و  _توزیع مجدد_ کد را به کاربران می دهند تفاوت این دو در این است که GPL از _کد_ محافظت می نماید در مقابل BSD که انتخاب را در دست توسعه دهنده بعدی قرار می دهد. BSD به مزاق کمپانی هائی که نگران Source Code های محصولاتشان هستند خوش می آید و GPL به مزاق هکرها، که باز بودن و شفافیت را ترجیح می دهند. برای نمونه [شرکت Microsoft](https://www.microsoft.com/) کد TCP/IP Stack سیستم عامل [Windows](https://en.wikipedia.org/wiki/Microsoft_Windows) خود و برخی از ابزارهای خط فرمان آن را از BSD برداشته است. و یا [شرکت Apple](http://www.apple.com/) که بخش عمده ای از کد هسته سیستم عامل های  [iOS](https://en.wikipedia.org/wiki/IOS) و [Mac OS X](https://en.wikipedia.org/wiki/OS_X) را مدیون سیستم عامل کد باز [Darwin](https://en.wikipedia.org/wiki/Darwin_%28operating_system%29) است که آن هم به نوبه خود از BSD قرض گرفته است. اگر کد BSD بر اساس لیسانس GPL عرضه می شد این شرکت ها مجبور به انتشار سورس کد های محصولات خود مطابق با پیش نیازهای GPL بودند. در مقابل این لیسانس دست و دلبازانه، [بخشی از سرمایه توسعه FreeBSD توسط همین کمپانی ها تامین می شود](https://www.freebsdfoundation.org/donate/sponsors). برای مثال [سرویس WhatsApp](http://www.wired.com/2015/10/whatsapps-co-founder-on-how-the-iconoclastic-app-got-huge/) که [در سال 2014 مبلغ 1 میلیون دلار را به این پروژه کمک کرد](http://freebsdfoundation.blogspot.com/2014/11/freebsd-foundation-announces-generous.html).  البته نکته قابل توجه این است که حتی اگر WhatsApp از یک سیستم عامل با لیسانس GPL هم استفاده می نمود نیازی به انتشار سورس کدهای سرویسش نبود چرا که آن ها کد آن سیستم عامل را به کاربر دیگری نمی فروشند. بلکه مطابق قوانین GPL فقط از آن استفاده نموده اند (مطابق قوانین GPL شما فقط در زمان استفاده از حق چهارم که توزیع می باشد بایستی تمامی حقوق رو به کاربر بعدی بدهید).
* مدل توسعه: به شکل سنتی مدل توسعه BSD آنچه که [Eric S. Raymond](https://en.wikipedia.org/wiki/Eric_S._Raymond)  افسانه ای در کتاب خود [The Cathedral and the Bazaar](https://en.wikipedia.org/wiki/The_Cathedral_and_the_Bazaar)  مدل Cathedral می نامد، می باشد. کار توسعه BSD توسط یک تیم آکادمیک و حرفه ای اما کوچک و متمرکز از توسعه دهندگان که استاد برنامه نویسی می باشند، انجام می شود. این در حالیست که Linux توسط Linus Torvalds به شکل غیر متمرکز، با همکاری شبکه ای از برنامه نویسان بدون ساختار مشخص در سرتاسر اینترنت که تنها نیازمندی جهت تائید صلاحیتشان قابلیت به ثمر رساندن وظیفه محول شده می باشد توسعه می یابد. این چیزی است که Raymond مدل Bazaar می نامد. هر چند که کد هسته سیستم عامل های خانواده BSD بسیار تمیزتر و خواناتر از Linux می باشد، اما برگ برنده Linux که منجر به نوآوری سریع آن در سال های آغازین توسعه و در نتیجه شهرت آن شده است دقیقا همین مدل توسعه می باشد. مدل  توسعه بسیار کارائی که خانواده BSD هیچ وقت به چشم ندیده است. چیزی که Linus Torvalds بر حسب اتفاق کشف نمود. جالب آنکه مدل توسعه GNU هم در 15 سال اول توسعه اش به مانند BSD همان مدل Cathedral بوده است.


<br />
<a name="bsd-legacy"></a>

### میراث BSD ###

البته با به شهرت رسیدن Linux در اواسط دهه 90  میلادی، [BSD  هیچ گاه منقرض](http://lists.freebsd.org/pipermail/freebsd-questions/2003-July/012219.html) نشد. در مقابل سیستم عامل های متعددی از جمله [FreeBSD](https://www.freebsd.org), [OpenBSD](http://www.openbsd.org/), [NetBSD](https://www.netbsd.org/), [DragonFly BSD](https://www.dragonflybsd.org/), [PC-BSD](http://www.pcbsd.org/), [GhostBSD](http://www.ghostbsd.org/), [MidnightBSD](http://www.midnightbsd.org/), [PureDarwin](http://www.puredarwin.org/)  و ... با انجمن ها و گروه های کاربری محدود، اما مشتاق و سرزنده به حیات خود ادامه می دهند. حتی محصولات متعددی مانند  [FreeNAS](http://www.freenas.org/), [pfSense](https://www.pfsense.org/), [BSD Router Project](http://bsdrp.net/), [m0n0wall](http://m0n0.ch/wall/index.php)   و ... به شکل مستمر براساس آن ها توسعه داده می شود. از آن جالب تر این که Distro های خوش نام دنیای Linux مانند [Debian](https://www.debian.org/) یا [Gentoo](https://www.gentoo.org/)  اقدام به عرضه همزمان توزیع های خود با هسته BSD به جای Linux هم نموده اند. از قبیل: [Debian GNU/kFreeBSD](https://www.debian.org/ports/kfreebsd-gnu/), [Gentoo/FreeBSD](https://wiki.gentoo.org/wiki/Gentoo_FreeBSD), [Gentoo/NetBSD](https://wiki.gentoo.org/wiki/Project:NetBSD), [Gentoo/OpenBSD](https://wiki.gentoo.org/wiki/Project:OpenBSD), [Gentoo/DragonFlyBSD](https://github.com/naota/gentoo-dragonflybsd)  و ...

شایان ذکر است  که سیستم [Ports](https://www.freebsd.org/ports/) سیستم عامل FreeBSD [منبع الهام](http://www.funtoo.org/Making_the_Distribution,_Part_3) [Daniel Robbins](https://en.wikipedia.org/wiki/Daniel_Robbins_%28computer_programmer%29)  خالق توزیع های  Gentoo و [Funtoo](http://www.funtoo.org/Welcome) در جهت ساخت [Package Manager سیستم عامل Gentoo به نام Portage](https://en.wikipedia.org/wiki/Portage_%28software%29) بوده است.

چنانچه سیستم عامل، محصولات و سرویس های کد بسته مانند Mac OS X, iOS, Windows, [Sony PlayStation 3](https://en.wikipedia.org/wiki/PlayStation_3), [Sony PlayStation 4](https://en.wikipedia.org/wiki/PlayStation_4), [Juniper Junos](https://en.wikipedia.org/wiki/Junos), [Netflix](https://www.netflix.com/), [WhatsApp](https://www.whatsapp.com/), [Yahoo](https://www.yahoo.com/), [Netcraft](http://www.netcraft.com/), [Rambler](http://www.rambler.ru/), [Yandex](http://www.yandex.ru/) و ... هم در نظر گرفته شوند [کدهای BSD]( https://en.wikipedia.org/wiki/List_of_products_based_on_FreeBSD)  به همان میزان که Linux و [Android]( https://en.wikipedia.org/wiki/Android_%28operating_system%29)  در حال استفاده هستند [بی نام و نشان در حال انجام وظیفه بر روی میلیاردها سرویس و دستگاه]( https://www.freebsd.org/doc/handbook/nutshell.html) می باشند.

اگر [Linux در زمان خود قابل به رندر فیلم تایتانیک بوده]( http://www.linuxjournal.com/article/2494) است، [رندر فیلم ماتریکس هم با کمک FreeBSD مسیر شده](https://www.freebsd.org/news/press-rel-1.html) است.

در واقع تنها تفاوت در مدل توسعه، لیسانس و مقداری بخت و اقبال، سرنوشت هر یک از این سیستم عامل ها را به شکل دیگری رقم زده است. در پایان، اما نکته اصلی و حائز اهمیت آزاد بودن این پلتفرم ها می باشد که هر یک به عنوان نقطه قوت خود بر آن می بالند.

[در مقاله بعدی به تشریح ماهیت، مفاهیم، ویژگی ها و اهداف FreeBSD خواهیم پرداخت](http://127.0.0.1:13001/blog/2016/01/29/what-is-freebsd-an-overview-of-freebsd-operating-system/).


<br />
<a name="references"></a>

### منابع ###

* [Open Sources: Voices from the Open Source Revolution](http://www.oreilly.com/openbook/opensources/book/kirkmck.html)
* [Open Source History: Why Didn't BSD Beat Out GNU and Linux](http://thevarguy.com/open-source-application-software-companies/062615/open-source-history-why-didnt-bsd-beat-out-gnu-and-linux)
* [A Quick History of UNIX](http://www.albion.com/security/intro-2.html)
* [About the FreeBSD Project](https://www.freebsd.org/doc/handbook/history.html)
* [FreeBSD Mall, Company History]( https://www.freebsdmall.com/cgi-bin/fm/history.html)
* [Linux Today - Report from Comdex--Walnut Creek CDROM, FreeBSD and Slackware](http://www.linuxtoday.com/infrastructure/1998112000105OP)


<br />

### مقالات مرتبط ###

* [FreeBSD چیست؟ یک نمای کلی از سیستم عامل FreeBSD](/blog/2016/01/29/what-is-freebsd-an-overview-of-freebsd-operating-system/)

