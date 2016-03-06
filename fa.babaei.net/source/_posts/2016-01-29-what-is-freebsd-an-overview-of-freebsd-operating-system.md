---
title: "What is FreeBSD? An Overview of FreeBSD Operating System"
date: 2016-01-29 04:25:36
tags:
  - FLOSS
  - FreeBSD
  - GNU
  - LINUX
  - Open Source
  - UNIX
---

<div class="post-title-fa">FreeBSD چیست؟ یک نمای کلی از سیستم عامل FreeBSD</div>
    
[{% img post-image /blog/2016/01/29/what-is-freebsd-an-overview-of-freebsd-operating-system/beastie-the-bsd-daemon-mascot.png 990 612 "'Beastie The BSD Daemon / Mascot'" "'Beastie The BSD Daemon / Mascot'" %}](/blog/2016/01/29/what-is-freebsd-an-overview-of-freebsd-operating-system/beastie-the-bsd-daemon-mascot.png)
<div style="direction: ltr;"><span class="post-image-title">'Beastie' The BSD Daemon / Mascot (a near homophone of the letters B-S-D pronounced slurred together)</span></div>

__FreeBSD چیست؟__ پاسخ کوتاه: [FreeBSD](https://www.freebsd.org/) یک سیستم عامل مدرن و پیشرفته جهت استفاده در سرورها، کامپیوترهای شخصی، لپ تاپ ها و دستگاه های Embedded به همراه [پشتیبانی از پلتفرم های گسترده](https://www.freebsd.org/platforms/) می باشد که توسط هواداران آن به شکل داوطلبانه برای بیش از سه دهه در دست توسعه بوده است. قابلیت های پیشرفته آن در زمینه شبکه، امنیت و ذخیره سازی، آن را به انتخاب اول برخی از پرترافیک ترین وب سایت ها، همچنین دستگاه ها و سیستم های فراگیر شبکه (فایروال ها و روترها) و ذخیره سازی داده (NAS/SAN) نموده است. این سیستم عامل توسط کمپانی ها، [ISP](https://en.wikipedia.org/wiki/Internet_service_provider) ها، دانشگاه ها، موسسات تحقیقاتی، دانشجویان، دانش آموزان و کاربران خانگی در سراسر دنیا به منظور کار و امور تحقیقاتی مورد استفاده قرار می گیرد.

در دومین مقاله [از سری آموزشی FreeBSD](/blog/2016/01/23/the-history-of-freebsd)، در قالب دسته ای از پرسش و پاسخ با ماهیت، برخی مفاهیم، ویژگی ها و اهداف FreeBSD آشنا خواهیم شد.

<!-- more -->


<br />

### فهرست ###

* [BSD چیست؟](#what-is-bsd)
* [آیا BSD یک UNIX واقعی است؟](#is-bsd-a-real-unix)
* [چرا BSD در نزد عموم شناخته شده نیست؟](#why-bsd-is-not-better-known)
* [هدف پروژه FreeBSD چیست؟](#what-is-the-goal-of-freebsd-project)
* [آیا لیسانس FreeBSD محدودیتی هم دارد؟](#does-the-freebsd-license-have-any-restrictions)
* [آیا FreeBSD می تواند جایگزین سیستم عامل فعلی من باشد؟](#can-freebsd-replace-my-current-operating-system)
* [چرا FreeBSD نامیده می شود؟](#why-is-it-called-freebsd)
* [چه تفاوت هائی میان سیستم عامل های FreeBSD, NetBSD, OpenBSD و سایر نسخ کد باز BSD وجود دارد؟](#what-are-the-differences-between-freebsd-and-netbsd-openbsd-and-other-open-source-bsd-operating-systems)
* [آخرین نسخه FreeBSD کدام است؟](#what-is-the-latest-version-of-freebsd)
* [FreeBSD-CURRENT چیست؟](#what-is-freebsd-current)
* [هدف از FreeBSD-STABLE چیست؟](#what-is-the-stable-freebsd-concept)
* [چه زمانی نسخ Release از FreeBSD عرضه می شوند؟](#when-are-freebsd-releases-made)
* [چه تعداد نرم افزار قابل اجرا بر روی FreeBSD در دسترس است؟](#how-many-softwares-are-available-for-freebsd)
* [آیا FreeBSD مانند GNU/Linux نرم افزار مدیریت بسته هم دارد؟](#does-freebsd-has-any-package-manager-like-its-counterpart-gnu-linux)
* [چه کسی یا کسانی عهده دار FreeBSD هستند؟](#who-is-responsible-for-freebsd)
* [از کجا می توانم FreeBSD را دریافت نمایم؟](#where-can-i-get-freebsd)
* [چگونه می توانم به پایگاه داده گزارش اشکالات دسترسی داشته باشم؟](#how-can-i-access-the-problem-report-database)
* [آیا منابع آموزشی کافی برای FreeBSD وجود دارد؟ در این صورت از کجا می توان آن ها را تهیه نمود؟](#is-there-enough-learning-resources-for-freebsd-if-so-where-to-get-them)
* [چیز دیگری هست که باید بدانم؟](#what-else-should-i-know)


<br />
<a name="what-is-bsd"></a>

### BSD چیست؟ ###

[BSD سرنام عبارت Berkeley Software Distribution](https://en.wikipedia.org/wiki/Berkeley_Software_Distribution) می باشد و به توزیع های منشعب شده از سورس کدی که در اصل در [دانشگاه برکلی کالیفرنیا](https://en.wikipedia.org/wiki/University_of_California,_Berkeley) توسعه یافته، اتلاق می شود. این سورس کد در آغاز تنها ضمیمه ای بر روی کد سیستم عامل [AT&T Research UNIX](https://en.wikipedia.org/wiki/Research_Unix) بود. در حال حاضر چندین سیستم عامل بر اساس نسخه ای از این کد، که تحت عنوان [BSD-4.4-Lite](https://en.wikipedia.org/wiki/Berkeley_Software_Distribution#4.4BSD_and_descendants)  شناخته می شود، در دسترس قرار دارند. علاوه بر آن، این سیستم عامل ها بخش هائی از کد سایر پروژه های کدباز را شامل می شوند، که مهم ترین آن ها [GNU](https://en.wikipedia.org/wiki/GNU) می باشد. بصورت کلی این سیستم عامل ها شامل بخش های ذیل می باشند:

* The BSD Kernel یا هسته BSD که [Process Scheduling](https://en.wikipedia.org/wiki/Scheduling_%28computing%29), [Memory Management](https://en.wikipedia.org/wiki/Memory_management), [Symmetric Multi-Processing (SMP)](https://en.wikipedia.org/wiki/Symmetric_multiprocessing), [Device Drivers](https://en.wikipedia.org/wiki/Device_driver) و ... را فراهم می آورد. برخلاف توزیع های مبتنی بر هسته [Linux](https://en.wikipedia.org/wiki/Linux) که همگی از یک [Kernel](https://en.wikipedia.org/wiki/Kernel) استفاده می نمایند، چندین هسته متفاوت BSD، هر کدام با ویژگی ها و توانائی های خاص خود در دسترس می باشد.
* [The BSD C Library](https://en.wikipedia.org/wiki/C_standard_library#BSD_libc)، یا کتابخانه BSD C، که API اصلی سیستم را فراهم می آورد. کد این کتابخانه بر اساس کد Berkeley می باشد نه [کد پروژه GNU](https://en.wikipedia.org/wiki/GNU_C_Library).
* ابزارهای کمکی از قبیل [Shell](https://en.wikipedia.org/wiki/Shell_%28computing%29)، ابزارهای کمکی فایل، [Compiler](https://en.wikipedia.org/wiki/Compiler) ها و [Linker](https://en.wikipedia.org/wiki/Linker_%28computing%29) ها که برخی از آن ها از پروژه GNU منشعب شده اند و برخی دیگر خیر.
* [The X Window System](https://en.wikipedia.org/wiki/X_Window_System)، که مسئولیت گرافیک را عهده دار می باشد. سیستم X Window مورد استفاده در اکثر نسخه های BSD توسط پروژه [X.Org](https://en.wikipedia.org/wiki/X.Org_Foundation) فراهم می شود. FreeBSD به کاربر اجازه انتخاب [محیط های متعدد Desktop](https://en.wikipedia.org/wiki/Desktop_environment) را می دهد. از آن جمله، می توان به [Gnome](https://en.wikipedia.org/wiki/Gnome), [KDE](https://en.wikipedia.org/wiki/KDE_Software_Compilation), [Xfce](https://en.wikipedia.org/wiki/Xfce), [LXDE](https://en.wikipedia.org/wiki/LXDE), [Enlightenment](https://en.wikipedia.org/wiki/Enlightenment_%28software%29) و حتی [Window Manager](https://en.wikipedia.org/wiki/Window_manager) های بسیار سبک مانند [Openbox](https://en.wikipedia.org/wiki/Openbox), [Fluxbox](https://en.wikipedia.org/wiki/Fluxbox) و [Awesome](https://en.wikipedia.org/wiki/Awesome_%28window_manager%29) اشاره نمود. همچنین [PC-BSD](https://en.wikipedia.org/wiki/PC-BSD) محیط دسکتاپ مینیمال خود به نام [Lumina DE](https://blog.pcbsd.org/2014/04/quick-lumina-desktop-faq/) را براساس [Qt](https://en.wikipedia.org/wiki/Qt_(software)) و Fluxbox توسعه داده است که بر روی FreeBSD هم اجرا می شود.
* در نهایت بسیاری برنامه و ابزارهای دیگر.


<br />
<a name="is-bsd-a-real-unix"></a>

### آیا BSD یک UNIX واقعی است؟ ###

سیستم عامل های BSD نسخه های کپی برداری شده از UNIX نیستند. در واقع آن ها منشعب شده از AT&T Research UNIX می باشند که نیای UNIX مدرن نسخه [System V](https://en.wikipedia.org/wiki/UNIX_System_V) هم می باشد. شاید باعث سورپرایز شما شود، که اگر [AT&T](https://en.wikipedia.org/wiki/AT%26T) هیچ وقت سورس کد خود را در قالب کدباز ارایه ننموده است، چطور همچین چیزی ممکن است؟

بله این درست است که AT&T UNIX هیچ وقت [Open Source](https://en.wikipedia.org/wiki/Open_source) نبوده است و با توجه به در نظر گرفتن کپی رایت، قطعا BSD یونیکس محسوب نمی شود؛ اما، از سوی دیگر AT&T بخشی از سورس کد خود را از منابع دیگر، به ویژه [Computer Sciences Research Group (CSRG)](https://en.wikipedia.org/wiki/Computer_Systems_Research_Group) از دانشگاه برکلی کالیفرنیا گرفته است. از سال 1976، گروه CSRG شروع به انتشار کد خود بر روی [Tape](https://en.wikipedia.org/wiki/Tape_drive) تحت عنوان Berkeley Software Distribution یا BSD نمود.

در آغاز نسخه های BSD چیزی بیش از برنامه های کاربری بر روی UNIX نبود، تا این که آن ها موفق به عقد قراردادی با [Defense Advanced Research Projects Agency (DARPA)](https://en.wikipedia.org/wiki/DARPA) جهت به روزرسانی پروتکل های ارتباطی بر روی شبکه آن ها به نام [ARPANET](https://en.wikipedia.org/wiki/ARPANET) شدند. این پروتکل های جدید به عنوان پرتکل های اینترنت، و بعدها [TCP/IP](https://en.wikipedia.org/wiki/Internet_protocol_suite) شناخته شدند. کد اولین نسخه از TCP/IP که به صورت گسترده ای منتشر شد، بخشی از [BSD-4.2](https://en.wikipedia.org/wiki/Berkeley_Software_Distribution#4.2BSD) منتشرشده به سال 1982  بود.

در سال های 1980 تعدادی از کمپانی های سازنده [کامپیوترهای Workstation](https://en.wikipedia.org/wiki/Workstation) به سرعت پدیدار شدند که اکثر آن ها به جای توسعه سیستم عامل خود، روی به استفاده از UNIX تحت برند خود و دریافت لیسانس UNIX از AT&T آوردند. به طور خاص، [Sun Microsystems](https://en.wikipedia.org/wiki/Sun_Microsystems) تحت لیسانس UNIX نسخه ای از آن را براساس BSD-4.2 با نام تجاری [SunOS](https://en.wikipedia.org/wiki/SunOS) عرضه نمود. زمانی که AT&T شروع به فروش UNIX به شکل تجاری نمود، این امر را با نسخه ای حداقلی تحت نام [System III](https://en.wikipedia.org/wiki/UNIX_System_III) آغاز نمود که سریعا با System IV جایگزین شد. کد نسخه بعدی، System V عاری از کد شبکه بود، بنابراین سایر UNIX ها روی به استفاده از کد BSD شامل TCP/IP و حتی ابزارهای کمکی مانند [csh shell](https://en.wikipedia.org/wiki/C_shell) و [vi editor](https://en.wikipedia.org/wiki/Vi) آوردند. در مجموع این بهبودها تحت عنوان Berkeley Extensions شناخته می شد.

تمامی Tape های منتشر شده توسط BSD شامل کد AT&T هم می شد، بنابراین جهت استفاده نیاز به لیسانس نمودن آن تحت UNIX Source License از AT&T بود. تا 1990 بودجه CSRG ته کشید و ناچارا به انتهای کار خود نزدیک می شد. عده ای از افراد گروه تصمیم به عرضه کد BSD که Open Source بود، بدون کد بسته AT&T نمودند. این اتفاق بالاخره با انتشار [Networking Tape 2](https://en.wikipedia.org/wiki/Berkeley_Software_Distribution#Net.2F2_and_legal_troubles) که معمولا با نام Net/2 شناخته می شود، میسر شد. Net/2 یک سیستم عامل کامل نبود؛ در واقع 20 درصد از کد هسته آن ناقص بود. یکی از اعضای CSRG، به نام [William F. Jolitz](https://en.wikipedia.org/wiki/William_Jolitz) به همراه همسر خود [Lynne Jolitz](https://en.wikipedia.org/wiki/Lynne_Jolitz)، مابقی کد را نوشته و آن را تحت نام [386BSD](https://en.wikipedia.org/wiki/386BSD) در اوایل 1992  منتشر نمودند. در همین زمان گروه دیگری از اعضای سابق CSRG شرکتی تحت عنوان [Berkeley Software Design Inc. (BSDI)](https://en.wikipedia.org/wiki/Berkeley_Software_Design) را تاسیس نمودند و نسخه ای بتا از سیستم عاملی کدبسته تحت عنوان [BSD/386](https://en.wikipedia.org/wiki/BSD/OS) منتشر می نمایند که بر اساس همان سورس کدی بود که پایه 386BSD را تشکیل می داد. این سیستم عامل بعدها به BSD/OS تغییرنام یافت.

386BSD هیچگاه یک سیستم عامل پایدار نشد. اما در سال 1993، از خاکستر آن دو سیستم عامل دیگر به نام های FreeBSD و [NetBSD](https://en.wikipedia.org/wiki/NetBSD) سربرآوردند. در اصل، هردوی این سیستم عامل ها به خاطر کندی پیشرفت 386BSD از آن منشعب شدند. افراد پشت پروژه NetBSD ابتدای همان سال پروژه خود را آغاز نمودند در حالیکه اولین نسخه از FreeBSD تا پایان همان سال به طول انجامید. در نهایت، به دلیل تفاوت زیاد کدهای توسعه یافته در هر دو پروژه، امکان تلفیق آن ها هیچگاه میسر نشد. علاوه بر آن هر کدام از این پروژه ها اهداف خاص خود را دنبال می نموند که مانع از این امر می شد. در سال 1996، سیستم عامل [OpenBSD](https://en.wikipedia.org/wiki/OpenBSD) از NetBSD منشعب شد و در سال 2003 پروژه [DragonFly BSD](https://en.wikipedia.org/wiki/DragonFly_BSD) از FreeBSD.


<br />
<a name="why-bsd-is-not-better-known"></a>

### چرا BSD در نزد عموم شناخته شده نیست؟ ###

بنا به دلایل متعددی، BSD نسبتا ناشناخته است:

* توسعه دهندگان BSD عمدتا علاقه بیشتری به نوشتن و بهبود کدهای خود دارند تا مارکت نمودن آن.
* عمده شهرت Linux ریشه در فاکتورهایی خارج از پروژه لینوکس دارد، مانند رسانه ها و شرکت هائی که به هدف ارایه سرویس های لینوکس تاسیس شده اند. تا همین اواخر BSD ها چنین هوادارانی را به خود ندیده بودند.
* به طور معمول توسعه دهندگان BSD به دلیل زمینه آکادمیک، افراد خبره تری نسبت به همکارانشان در Linux هستند که باعث می شود علاقه کمتری به ساده تر نمودن استفاده از آن، از خود نشان دهند. تازه کارها معمولا با Linux راحت تر هستند.
* در سال 1992  شرکت AT&T کمپانی BSDI توسعه دهنده BSD/386 را با طرح دعوای حقوقی مبنی بر این که شامل کدهای AT&T می باشد، مورد تعقیب قضائی قرار داد. این قضیه در خارج از دادگاه در سال 1994 حل و فصل شد، اما، شبح دعوای قضائی مانع از نزدیک شدن عموم به آن می شد. در سال 2000 مقاله ای بر روی وب منتشر شد که مدعی می شد این قضیه اخیرا به شکل کامل حل و فصل شده است.

پیامد آن دعوای حقوقی، تصریح نکته ای در مورد نام BSD بود: در سال های دهه 80، BSD به نام BSD UNIX شناخته می شد که با حذف آخرین ردپاهای کد AT&T از BSD، این سیستم عامل حق استفاده از نام UNIX به شکل رسمی را از دست داد. برای مثال در عناوین کتاب ها: از The 4.3BSD UNIX® Operating System به The 4.4BSD Operating System تغییر یافت.


<br />
<a name="what-is-the-goal-of-freebsd-project"></a>

### هدف پروژه FreeBSD چیست؟ ###

هدف FreeBSD ارائه سیستم عاملی همه منظوره، پایدار، سریع با کارائی بالا، سادگی استفاده به هر منظوری، عاری از هرگونه قید و شرط می باشد. معمولا انتخاب اول سرویس دهنده های وب در میان سایر BSD هاست که اتفاقا [ از بیشترین میزان استفاده در میان BSD ها برخوردار می باشد](https://en.wikipedia.org/wiki/Comparison_of_BSD_operating_systems#Popularity).


<br />
<a name="does-the-freebsd-license-have-any-restrictions"></a>

### آیا لیسانس FreeBSD محدودیتی هم دارد؟ ###

بله. این محدودیت ها شامل چگونگی استفاده از کدهای آن نمی باشد، بلکه این محدودیت ها نحوه برخورد با پروژه FreeBSD را مشخص می سازد. [این لیسانس](http://www.freebsd.org/copyright/freebsd-license.html) و محدودیت های آن را می توان به شرح ذیل خلاصه نمود:

* شما نباید ادعا کنید که کدهای آن را نوشته اید.
* چنانچه در صورت استفاده از کدهای FreeBSD با مشکلی مواجه شدید حق پیگیری قضائی و طرح دعوا را نخواهید داشت. در واقع مسئولیت استفاده از آن با شما خواهد بود و بایستی آن را کاملا بپذیرید.
* چنانچه اقدام به توزیع مجدد سورس کد نمائید، حق حذف نمودن License آن از فایل های Source و یا تغییرش را نخواهید داشت. همچنین در توزیع Binary خود موظف به نمایش اعلان Copyright آن خواهید بود.

علاوه بر آن به دلیل استفاده FreeBSD از بخش هائی از پروژه GNU، قسمت هائی از کد آن مبتنی بر لیسانس های GNU [GPL](https://en.wikipedia.org/wiki/GNU_General_Public_License) / [LGPL](https://en.wikipedia.org/wiki/GNU_Lesser_General_Public_License) می باشد که می بایستی مطابق با محدودیت های آن ها عمل شود. به عنوان مثال استفاده از کدهای مبتنی بر GPL / LGPL در نرم افزارهای کد بسته محدودیت هائی را شامل می شود که ممکن است منجر به پیگیری قضائی از سوی نویسنده اصلی آن پروژه ها شود. البته پروژه FreeBSD در تلاش است تا هرچه بیشتر کدهای مبتنی بر لیسانس های GPL / LGPL را با کد تحت لیسانس BSD یا مشابه آن جایگزین نماید. برای مثال پس از تغییر لیسانس [GNU Toolchain](https://en.wikipedia.org/wiki/GNU_toolchain) از [GPLv2](https://en.wikipedia.org/wiki/GNU_General_Public_License#Version_2) به [GPLv3](https://en.wikipedia.org/wiki/GNU_General_Public_License#Version_3)، به دلیل محدودیت های بیشتر آن، با [LLVM](https://en.wikipedia.org/wiki/LLVM) که لیسانس دست و دلبازانه تری دارد، جایگزین شد.


<br />
<a name="can-freebsd-replace-my-current-operating-system"></a>

### آیا FreeBSD می تواند جایگزین سیستم عامل فعلی من باشد؟ ###

برای بسیاری از افراد، بله. اجازه بدهید مقداری توضیح دهم.

بر خلاف تصور رایج، اکثر افراد از سیستم عامل استفاده نمی نمایند. آن ها از اپلیکیشن ها استفاده می نمایند. این اپلیکیشن ها هستند که از سیستم عامل استفاده می نمایند. طراحی FreeBSD به گونه ای بوده است که قادر باشد محیطی پایدار به همراه قابلیت های متنوعی را برای برنامه ها محیا کند. این سیستم عامل از نرم افزارهای متنوع و گوناگونی شامل مرورگرهای وب، مجموعه های آفیس، ایمیل خوان ها، نرم افزارهای گرافیکی، محیط های برنامه نویسی، سرورهای شبکه و خیلی چیزهای دیگر پشتیبانی می نماید. مدیریت این نرم افزارها از طریق [Ports Collection](https://www.freebsd.org/ports/) انجام می شود.

اگر برنامه ای فقط برای یک سیستم عامل خاص در دسترس باشد، یقینا آن سیستم عامل را نمی توان جایگزین نمود. اما، احتمال آنکه نرم افزار مشابهی بر روی FreeBSD وجود داشته باشد بالاست. فرقی نمی کنه که به عنوان یک سرور محلی در شرکت، سرور اینترنتی و یا یک کامپیوتر در شبکه، از آن استفاده نمائید، FreeBSD به احتمال بسیار زیاد تمام کارهائی که شما می خواهید را نه تنها به خوبی انجام خواهد داد، بلکه می تواند گزینه ای با قابلیت اعتماد بالا باشد. بسیاری از کاربران شامل مبتدی تا مدیران با تجربه شبکه در سرتاسر دنیا، از FreeBSD به عنوان تنها سیستم عامل دسکتاپ استفاده می نمایند.

کاربرانی که از یک سیستم عامل شبه UNIX به FreeBSD مهاجرت می نمایند تشابهات بسیاری را در آن خواهند یافت. کاربرانی که از Windows یا Mac OS X قصد مهاجرت به FreeBSD را دارند، شاید بهتر باشد دیگر توزیع های تحت دسکتاپ مبتنی بر FreeBSD مانند PC-BSD و یا [GhostBSD](https://en.wikipedia.org/wiki/GhostBSD) را امتحان نمایند. کاربرانی که UNIX یا سیستم های مشابه آن را تجربه ننموده اند احتمالا نیازمند یادگیری کارها به روش UNIX خواهند بود.


<br />
<a name="why-is-it-called-freebsd"></a>

### چرا FreeBSD نامیده می شود؟ ###
* می تواند به رایگان استفاده شود، حتی توسط کاربران تجاری.
* سورس کد کامل سیستم عامل با کمترین محدودیت های ممکن در نحوه استفاده از آن، به شکل آزادانه در دسترس می باشد. حتی اگر قصد تغییر آن را برای مقاصد تجاری یا غیر تجاری داشته باشید.
* هر کسی می تواند بهبودها یا رفع اشکالات خود را با رعایت پیش نیازها و قوانین آن به سورس کد اصلی FreeBSD اضافه نماید.

قابل ذکر است که کلمه Free به دو معنا می باشد: اول "بدون هیچ بهائی"، دوم "هر کاری که می خواهید بکنید". البته بجز یک یا دو کار که شما با کد آن نمی توانید بکنید؛ مثلا ادعا کنید آن را نوشته اید، به معنای واقعی کلمه می توانید هر کاری که می خواهید بکنید.


<br />
<a name="what-are-the-differences-between-freebsd-and-netbsd-openbsd-and-other-open-source-bsd-operating-systems"></a>

### چه تفاوت هائی میان سیستم عامل های FreeBSD, NetBSD, OpenBSD و سایر نسخ کد باز BSD وجود دارد؟ ###

[James Howard](https://jameshoward.us/) توضیحات دقیق و بسیار خوبی راجع به تاریخچه و تفاوت های هر یک از این پروژه ها به نام [The BSD Family Tree](http://www.freebsdworld.gr/freebsd/bsd-family-tree.html) به رشته تحریر درآورده است که پاسخ جامع این سوال را در خود دارد. برخی از اطلاعات آن دیگر به روز نیست؛ اما مثلا قسمت تاریخچه آن کاملا دقیق است.

حتی امروزه، هنوز هم اکثر BSD ها با یکدیگر به تبادل Patch و Code می پردازند، چرا که تمامی آن ها از یک تبار و ریشه اند. اهداف FreeBSD را بالاتر شرح دادیم. به اختصار، هدف از طراحی دیگر BSD ها را عنوان می نمائیم:

* NetBSD به لطف داشتن خواناترین و تمیزترین کد Kernel در میان تمامی سیستم عامل های کدباز، اعم از BSD و غیر آن، هدفش پرتابل بودن مابین تمامی پلتفرم های ممکن سخت افزاری است. حتی لطیفه ای در میان جامعه کد باز رواج دارد به این شرح که: کد NetBSD توانائی اجرا بر روی دستگاه های Toaster را هم دارد. [البته در واقعیت، این موضوع بیشتر از یک لطیفه است و به لطف آن یک Toaster نه نتها می تواند موسیقی پخش کند، بلکه می تواند مجهز به وب سرور Apache، مفسرPHP و ویرایشگر vi هم باشد](https://www.embeddedarm.com/software/arm-netbsd-toaster.php). این سیستم عامل حتی در [ماموریت های فضائی NASA در ایستگاه فضائی بین اللملی](http://www.netbsd.org/gallery/research.html#sams-ii) و یا [پیاده سازی TCP در شبکه ای از ماهواره ها](http://www.netbsd.org/gallery/research.html#tcp_sat_nasa) هم مورد استفاده قرار گرفته است. معمولا بهترین گزینه برای اجرا بر روی کامپیوترهای قدیمی و یا ضعیف می باشد.
* OpenBSD که بی شک ایمن ترین سیستم عامل دنیاست، بالاتر از هر چیزی هدفش امنیت سیستم عامل است. [به خصوص اینکه توسعه دهنده اصلی آن کانادائی است - با پدر و مادری از آفریقای جنوبی و هلند - نه آمریکائی](https://en.wikipedia.org/wiki/Global_surveillance_disclosures_%282013%E2%80%93present%29). به دلیل بهره گیری از قوانین سخت و شدیدی مانند [Code Review](https://en.wikipedia.org/wiki/Code_review) های منظم که بر این پروژه حاکم است از زمان آغاز این پروژه تا کنون (بیش از 19 سال) فقط 2 [آسیب پذیری امنیتی](https://en.wikipedia.org/wiki/Exploit_%28computer_security%29) امنیتی آن هم از نوع Remote، نه Local - که خطرناک تر می باشد – در [نصب پیش فرض این سیستم عامل](https://en.wikipedia.org/wiki/OpenBSD#Slogan) کشف شده است. تمامی این مسایل آن را به گزینه جدی جهت استفاده در سازمان های نیازمند امنیت بالا نظیر بانک ها، بازارهای بورس و دپارتمان های مهم نظامی و دولتی و ... تبدیل نموده است. این سیستم عامل به خاطر مسایل و مشکلات خالق آن [Theo de Raadt](https://en.wikipedia.org/wiki/Theo_de_Raadt) که روزگاری یکی از توسعه دهندگان NetBSD بود، با سایر اعضای تیم NetBSD، در سال 1996 از کد آن منشعب شد. سپس توسط DARPA که از زیر مجموعه های وزارت دفاع آمریکا می باشد Fund شده که در سال 2003 به دلیل انتقادهای de Raadt از جنگ عراق در یک روزنامه کانادائی تمام حمایت های مالی آن از سوی این سازمان قطع می گردد. پیامدهای این مسئله تا بدان جا پیش می رود که DARPA حمایت و کمک هایش به سایر BSD ها و پروژه های زیر مجموعه آن ها را قطع می نماید. OpenBSD در میان تمامی سیستم عامل های کدباز، بیشترین و بهترین پشتیبانی از انواع سخت افزار WiFi را دارد. همچنین مکانیزم راه اندازی WiFi در آن ساده ترین و راحت ترین در نوع خود می باشد. دلیل آن متقاعد نمودن کمپانی های سازنده WiFi که اکثر تایوانی می باشند، جهت Open Source نمودن درایورهایشان، توسط de Raadt می باشد (البته او می گوید که Intel و Broadcom هیچ گاه متقاعد نشدند) که باعث تعلق جایزه [Award for the Advancement of Free Software](https://en.wikipedia.org/wiki/Award_for_the_Advancement_of_Free_Software) به او از سوی [بنیاد نرم افزارهای آزاد](https://en.wikipedia.org/wiki/Free_Software_Foundation) در سال 2004 شد. شایان ذکر است که [تیم OpenBSD متولی پروژهای متعددی می باشد](http://www.openbsd.org/innovations.html) که در سایر پروژه های کدباز مانند GNU/Linux و Android یا کد بسته، مثلا iOS و Mac OS X و .... استفاده می شود. FreeBSD برخی از آن ها مانند [OpenSSH](https://en.wikipedia.org/wiki/OpenSSH) و [pf](https://en.wikipedia.org/wiki/PF_%28firewall%29) را قرض گرفته است. از دیگر نمونه های قابل ذکر [LibreSSL](https://en.wikipedia.org/wiki/LibreSSL) است که پس از [آسیب پذیری خونریزی قلبی و پیامدهای آن](https://en.wikipedia.org/wiki/Heartbleed) در نرم افزار [OpenSSL](https://en.wikipedia.org/wiki/OpenSSL) ، توسط این تیم از آن منشعب شده است؛ چنانکه فقط در هفته اول 90,000 خط از کدهای آن پاک سازی و دور ریخته شد.
* DragonFly BSD که از FreeBSD نسخه 4.8 منشعب شده است [قابلیت و ویژگی های جالب مختص به خودش را توسعه داده است](https://www.dragonflybsd.org/features/)، که برخی از آن ها عبارتند از سیستم فایل های [HAMMER و HAMMER2](https://en.wikipedia.org/wiki/HAMMER)، همچنین پشتیبانی از vkernels در حالت user-mode. هدف این سیستم عامل [کارائی بالا و Scale شدن از یک Node در شبکه تا یک کلاستر عظیم، به لطف معماری مبتنی بر SMP](https://www.dragonflybsd.org/performance/) آن می باشد. معماری آن طوری بنا شده است که به سادگی قابل فهم، نگهداری و توسعه باشد. به طور سنتی، برخلاف لینوکس، BSD ها پشتیبانی بسیار خوبی را از سیستم فایل [ZFS](https://en.wikipedia.org/wiki/ZFS) به عمل می آورند. HAMMER و HAMMER2 جهت رقابت مستقیم با ZFS توسط Matthew Dillon خالق DragonFly BSD خلق شده اند.
* PC-BSD: نسخه ای از FreeBSD است که جهت استفاده در Desktop بهینه سازی و بهبود یافته است با این تفاوت که به جای - سیستم فایل سنتی BSD یعنی - [UFS2](https://en.wikipedia.org/wiki/Unix_File_System) از ZFS به عنوان File System استفاده می نماید. در واقع راه اندازی ZFS به خصوص برای تازه کارها کار نسبتا دشواری می باشد که با نصب این سیستم عامل به صورت خودکار انجام می شود. ذکر این نکته ضروری می نماید که نسخه سرور این سیستم عامل [TrueOS](http://www.pcbsd.org/development/moretrueos/) نام دارد. همچنین بنا به مشکلاتی که توسعه دهندگان عمده محیط های دسکتاپ در زمان انتقال خود از [HAL](https://en.wikipedia.org/wiki/HAL_%28software%29) به [udev](https://en.wikipedia.org/wiki/Udev) برای خانواده BSD به وجود آوردند، توسعه دهندگان PC-BSD تصمیم به ساخت یک Desktop مینیمال برای خانواده BSD به نام Lumina، تحت لیسانس BSD نمودند. این دسکتاپ به جای استفاده از HAL و udev از شهروند درجه یک FreeBSD به نام [devd](https://www.freebsd.org/cgi/man.cgi?devd%288%29) که به طور خاص برای آن ایجاد شده است، استفاده می نماید.
* GhostBSD: درست مانند PC-BSD کاربران Desktop را هدف قرار داده است، با این تفاوت که پروژه کوچکتر و جوان تری می باشد.


<br />
<a name="what-is-the-latest-version-of-freebsd"></a>

### آخرین نسخه FreeBSD کدام است؟ ###

در طول توسعه FreeBSD در هر نقطه ای از زمان، ممکن است [Branch](https://en.wikipedia.org/wiki/Branching_%28version_control%29) های موازی متعددی از آن در دسترس باشد. برای مثال نسخه های Release سری <code>10.x</code>  از Branch ی به نام <code>10-STABLE</code> ساخته می شوند و نسخه های  Release سری <code>9.x</code> از Brnach ی دیگر به نام <code>9-STABLE</code>.

تا زمان انتشار نسخه <code>9.0</code>، سری <code>9.x</code>  به عنوان <code>-STABLE</code> شناخته می شد. اما از زمان عرضه سری <code>11.x</code>، سری <code>9.x</code> عنوان Extended Support را یدک می کشد، که تنها به روزرسانی های مربوط به ایرادات بزرگ، مانند آسیب پذیری های امنیتی را دریافت می نماید.

نسخه <code>10.2</code> آخرین Release از برنچ <code>10-STABLE</code> می باشد که در آگوست 2015 منتشر شده است. نسخه <code>9.3</code> آخرین Release از برنچ <code>9-STABLE</code> می باشد که در جولای 2014 منتشر شده است.

نسخه های Release هر چند ماه یکبار عرضه می شوند. با وجود آن که می توان با دنبال نمودن نسخه های Source از FreeBSD، سیستم عامل را کاملا به روز نگه داشت (سه سوال بعد را ببینید)، این امر پشتکار و تعهد فراوانی را می طلبد؛ چرا که نسخ سورس دائما در حال به روزرسانی هستند.

اطلاعات بیشتر راجع به نسخه های Release سیستم عامل FreeBSD را می توان از صفحات [Release Engineering page](http://www.freebsd.org/releng/index.html#release-build) و [release(7)](http://www.freebsd.org/cgi/man.cgi?query=release&sektion=7) کسب نمود.


<br />
<a name="what-is-freebsd-current"></a>

### FreeBSD-CURRENT چیست؟ ###

[FreeBSD-CURRENT](https://www.freebsd.org/doc/en_US.ISO8859-1/books/handbook/current-stable.html#current) نسخه همیشه در دست توسعه این سیستم عامل است که در زمان مقتضی تبدیل به <code>FreeBSD-STABLE</code> خواهد شد. بنابراین، این نسخه بیشتر مورد علاقه توسعه دهندگان، گیک ها و علاقمندان سینه چاک آن ست.

این Branch به هیچ وجه به کاربران مبتدی که با FreeBSD آشنائی ندارند توصیه نمی شود. به دلیل آنکه این Branch بیشتر میدان آزمایش است میزان تغییرات گاها سریع بوده و احتمال وجود خطاهای برنامه نویسی در آن زیاد است. انتظار می رود افرادی که از این Branch استفاده می نمایند توانائی آنالیز، خطایابی و گزارش مشکلات را داشته باشند.
به صورت مداوم نسخه هایی به نام [Snapshot](https://www.freebsd.org/snapshots/) از روی وضعیت فعلی Branch های <code>-CURRENT</code> و <code>-STABLE</code> ساخته می شوند. هدف از انتشار هر یک از این Snapshot ها موارد ذیل می باشد:

* جهت تست نمودن آخرین نسخه قابل نصب.
* جهت مهیا نمودن نسخه ای از آن برای افرادی که علیرغم علاقه به اجرا نمودن آخرین نسخه های <code>-CURRENT</code> و <code>-STABLE</code>  زمان و یا پهنای باند کافی جهت دنبال نمودن هر روزه تغییرات را ندارند.
* جهت ارجاع به کدی که باعث ایجاد اشکالات و خطاهای عمده شده است (هر چند که [Subversion](https://en.wikipedia.org/wiki/Apache_Subversion) معمولا از بروز چنین اشکالات وحشتناکی جلوگیری نموده و در صورت لزوم قابلیت بازگشت به کدهای قبلی را فراهم می آورد).
* جهت اطمینان از اینکه تمامی ویژگی ها و رفع اشکالات جدید که نیاز به تست دارند توسط حداکثر تست کننده های بالقوه تست شده اند.

هیچ گونه تضمینی مبنی بر این که نسخ ارایه شده بر اساس <code>-CURRENT</code> به اصطلاح از Production Quality یا کیفیت تولید در محیط های کاری برخوردار باشند، وجود ندارد. لذا اگر نیاز به یک سیستم پایدار و کاملا تست شده دارید فقط از نسخه های Release استفاده نمائید.

نسخه های Snapshot رسمی برای تمام Branch های فعال در دست توسعه، [به شکل منظم ساخته شده و مستقیما در دسترس قرار می گیرند](https://www.freebsd.org/snapshots/).


<br />
<a name="what-is-the-stable-freebsd-concept"></a>

### هدف از FreeBSD-STABLE چیست؟ ###

زمانی که <code>FreeBSD 2.0.5</code> عرضه شد، توسعه FreeBSD به دو شاخه تقسیم شد. یکی از آن ها <code>-STABLE</code> و دیگری <code>-CURRENT</code> نامیده شد. [FreeBSD-STABLE](https://www.freebsd.org/doc/en_US.ISO8859-1/books/handbook/current-stable.html#stable) یک Branch دائما در حال توسعه است که نسخه های اصلی Release از روی آن ساخته می شوند. تغییرات با گام کندتری در این Branch اعمال می شوند آن هم با این فرض که این تغییرات ابتدا به خوبی در <code>-CURRENT</code> تست شده اند. گرچه، در هر زمانی، ممکن است <code>FreeBSD-STABLE</code> برای استفاده عموم مناسب یا نامناسب باشد. دلیل آن این است که گاها ممکن است اشکالاتی در آن نمایان شود که در <code>-CURRENT</code> از دید پنهان مانده است. کاربرانی که علاقه یا منابع کافی جهت تست را ندارند بایستی از آخرین نسخ Release استفاده نمایند.

در مقابل <code>-CURRENT</code> مانند خط ممتدی است که از نسخه <code>2.0</code> شروع شده و به نسخه <code>10.2</code> رسیده؛ که همچنان ادامه می یابد. جهت کسب اطلاعات بیشتر در مورد Branch ها، قسمت [FreeBSD Release Engineering: Creating the Release Branch](https://www.freebsd.org/doc/en_US.ISO8859-1/articles/releng/release-proc.html#rel-branch) از مستندات رسمی FreeBSD را ببینید. وضعیت Branch ها و زمانبندی مربوط به نسخه های Release در صفحه [Release Engineering Information](http://www.freebsd.org/releng) در دسترس می باشد.

در حال حاضر،<code>10.2-STABLE</code>  فعال ترین Branch در دست توسعه از <code>-STABLE</code> می باشد. آخرین نسخه Release  انتشار یافته از <code>10.2-STABLE</code> نسخه <code>10.2-RELEASE</code> می باشد که در آگوست 2015 در دسترس قرار گرفته است. همچنین<code>11-CURRENT</code>  فعال ترین Branch در دست توسعه از <code>-CURRENT</code> می باشد که نسل بعدی FreeBSD را هدف قرار داده است.


<br />
<a name="when-are-freebsd-releases-made"></a>

### چه زمانی نسخ Release از FreeBSD عرضه می شوند؟ ###

[تیم مهندسی توسعه FreeBSD](mailto:re@FreeBSD.org) به طور میانگین هر 18 ماه یکبار دست به انتشار نسخ اصلی (Major) و هر 8 ماه یکبار نسخ فرعی (Minor) می زند. تاریخ های انتشار از پیش کاملا مشخص و اعلام می شوند تا هر یک از تیم های در حال کار بر روی FreeBSD زمانبندی خود جهت خاتمه توسعه و سپس تست آن را انجام دهد. جهت اطمینان از این که ویژگی های جدید اضافه شده پایداری سیستم را در معرض خطر قرار نمی دهد، به هر انتشار یک مدت زمان تست اضافه می شود. در واقع بسیاری از کاربران این احتیاط را جزو بهترین های FreeBSD می دانند، هرچند که منتظر ماندن برای رسیدن ویژگی های جدید به <code>-STABLE</code> ممکن است کمی خسته کننده باشد.

اطلاعات بیشتر در مورد پروسه انتشار نسخ Release شامل برنامه زمانی نسخه Release بعدی را می توانید از صفحه [Release Engineering](http://www.freebsd.org/releng/index.html) در وب سایت FreeBSD مطالعه نمائید.

برای افرادی که اهل ماجراجوئی هستند و نمی توانند تا زمان انتشار نسخه بعد منتظر بمانند - همانطور که قبلا توضیح داده شد – [نسخه های Binary به شکل هفتگی](https://www.freebsd.org/snapshots/) در دسترس می باشد.


<br />
<a name="how-many-softwares-are-available-for-freebsd"></a>

### چه تعداد نرم افزار قابل اجرا بر روی FreeBSD در دسترس است؟ ###

با استناد به [رابط کاربری تحت وب سیستم Ports](https://www.freebsd.org/ports/)، در حال حاضر تعداد __25,674__ عدد برنامه به شکل رسمی از سوی پروژه FreeBSD به منظور اجرا بر روی این سیستم عامل عرضه می شود، که باعث شده این سیستم عامل در میان تمامی BSD ها بیشترین میزان برنامه را داشته باشد.

علاوه بر آن اغلب نرم افزارهائی که بر روی GNU/Linux اجرا می شوند می توانند توسط یک [Compatibility Layer](https://en.wikipedia.org/wiki/Compatibility_layer) که FreeBSD ارایه می نماید، بر روی آن اجرا شوند؛ حتی اگر آن ها کد بسته و یا به شکل باینری باشند (مانند Flash, Nero, Skype, Opera و ...). نکته اینجاست که این لایه عمل [شبیه سازی](https://en.wikipedia.org/wiki/Emulator) را انجام نمی دهد. بلکه، به دلیل پیاده سازه رابط [System Call](https://en.wikipedia.org/wiki/System_call) هسته Linux در هسته FreeBSD، [فایل های اجرائی](https://en.wikipedia.org/wiki/Executable) و [کتابخانه های](https://en.wikipedia.org/wiki/Shared_libraries) Linux در این سیستم عامل مانند خود برنامه های FreeBSD شهروند درجه یک حساب می شوند. علاوه بر آن FreeBSD لایه های مشابهی را جهت اجرای برنامه های چندین سیستم شبه UNIX دیگر مانند BSD/OS و [SVR4](https://en.wikipedia.org/wiki/Shared_libraries) فراهم می آورد. اما در میان کاربران مرسوم است که آن برنامه ها را بر روی خود FreeBSD کامپایل و اجرا کنند.

لازم به ذکر است که به دلیل عدم شبیه سازی، نه تنها تفاوت چشمگیری در اجرای برنامه های باینری Linux در این سیستم عامل مشاهده نمی شود، بلکه برخی از برنامه ها مانند Flash نسبت به اجرای آن بر روی لینوکس، حتی سریعتر هم اجرا می شوند. گرچه، ممکن است برخی از برنامه های باینری لینوکس در FreeBSD اصلا اجرا نشوند و یا ناقص اجرا شوند. از نسخه FreeBSD 7.0 تا کنون حداکثر System Call های مربوط به نسخه 2.6.18 لینوکس اجرا می شود. همچنین این لایه سازگاری فقط مختص برنامه های 32 بیت می باشد، هرچند که تلاش هائی جهت پشتیبانی از نسخ 64 بیت صورت گرفته است.

علاوه بر لینوکس اجرای [برنامه های 32 بیتی Windows](https://wiki.freebsd.org/i386-Wine) هم از طریق [Wine](https://wiki.freebsd.org/Wine) بر روی FreeBSD نسخه x86 میسر می باشد. نسخه های 64 بیتی ممکن است کار کنند اما در حال حاضر رسما پشتیبانی نمی شوند.

FreeBSD با پیاده سازی بخشی از رابط های [NDIS](https://en.wikipedia.org/wiki/Network_Driver_Interface_Specification) در هسته خود قابلیت اجرا نمودن درایورهای مختص ویندوز برای کارت های شبکه و WiFi را میسر نموده است.


<br />
<a name="does-freebsd-has-any-package-manager-like-its-counterpart-gnu-linux"></a>

### آیا FreeBSD مانند GNU/Linux نرم افزار مدیریت بسته هم دارد؟ ###

نام آن [Ports Collection](https://www.freebsd.org/ports/) می باشد که به اختصار آن را Ports می نامند. Ports روش بسیار ساده و کارائی را به همراه ابزارهای مختلفی جهت مدیریت، کامپایل و نصب برنامه ها ارائه می نماید. هر یک از برنامه های قابل نصب در سیستم Ports یک Port نامیده می شود. این سیستم به شما اجازه تعیین این که چه قابلیت هائی از یک برنامه کامپایل و نصب شوند را می دهد، که در نوع خود بی نظیر است. تصور کنید که قابلیت هائی را که نمی خواهید خاموش می کنید: 1. باعث کم شدن حجم باینری ها، در نتیجه بارگذاری سریعتر، در نهایت اجرای سریعتر آن ها خواهد شد. 2. کد کمتر یعنی آسیب پذیری کمتر در نتیجه امنیت بیشتر! علاوه بر آن ها Ports به شما قابلیت بهینه سازی کد کامپایل شده برای CPU تان را خواهد داد که در دیستروهای باینری تقریبا غیرممکن می نماید.

در صورت نیاز می توان با ابزار دیگری تحت عنوان [pkgng](https://www.freebsd.org/doc/handbook/pkgng-intro.html) اقدام به نصب نسخ Binary از برنامه ها نمود. این ابزار بصورت رسمی ابتدا در نسخه 10 این سیستم عامل معرفی شد، هرچند که در نسخه 9 نیز استفاده از آن میسر می باشد.

لازم به ذکر است که سیستم [Portage](https://en.wikipedia.org/wiki/Portage_(software)) در لینوکس های [Gentoo](https://en.wikipedia.org/wiki/Gentoo_Linux) و [Funtoo](https://en.wikipedia.org/wiki/Funtoo_Linux) از Ports [کپی برداری](http://www.funtoo.org/Making_the_Distribution,_Part_3) شده اند. همچنین [نرم افزار مدیریت بسته NetBSD به نام pkgsrc](https://en.wikipedia.org/wiki/Pkgsrc)  و مجموعه [Ports در OpenBSD](https://en.wikipedia.org/wiki/Ports_collection#OpenBSD_ports) ریشه در همین [Package Manager](https://en.wikipedia.org/wiki/Package_Manager) دارند.


<br />
<a name="who-is-responsible-for-freebsd"></a>

### چه کسی یا کسانی عهده دار FreeBSD هستند؟ ###

تمامی تصمیمات مهم در مورد پروژه FreeBSD، مانند مسیر کلی آن و اینکه چه کسانی حق اضافه نمودن کد به کد اصلی آن را دارند توسط یک تیم 9 نفره که تیم هسته یا Core نامیده می شود، گرفته می شود. یک تیم بزرگتر هم متشکل از 350 نفر به نام Committers وجود دارند که حق مستقیم اعمال تغییرات بر روی کد اصلی FreeBSD را دارند. گرچه، بیشتر تغییرات غیرحیاتی از پیش در Mailing Lists مورد بحث و گفتگو قرار گرفته و هیچ محدودیتی برای افراد دیگر برای شرکت در آن در نظر گرفته نمی شود.


<br />
<a name="where-can-i-get-freebsd"></a>

### از کجا می توانم FreeBSD را دریافت نمایم؟ ###

تمامی نسخه های قابل توجه FreeBSD از طریق [anonymous FTP](https://en.wikipedia.org/wiki/File_Transfer_Protocol#Anonymous_FTP) در [سایت FTP پروژه FreeBSD](ftp://ftp.freebsd.org/pub/FreeBSD/) در دسترس می باشد:

* آخرین نسخه Release از <code>10-STABLE</code> که <code>10.2-RELEASE</code> می باشد از [پوشه 10.2-RELEASE](ftp://ftp.freebsd.org/pub/FreeBSD/releases/i386/i386/10.2-RELEASE/) قابل دسترسی می باشد.
* [نسخه های Snapshot](https://www.freebsd.org/snapshots/) برای <code>-CURRENT</code> و <code>-STABLE</code> که به منظور استفاده توسعه دهندگان و تست کنندگان عرضه می شوند، به شکل ماهانه ساخته شوند.
* آخرین نسخه Release از <code>9-Relase</code>  که <code>9.3-RELEASE</code> می باشد از پوشه [9.3-RELEASE](ftp://ftp.freebsd.org/pub/FreeBSD/releases/i386/9.3-RELEASE/) قابل دسترسی می باشد.

اطلاعات لازم جهت دریافت نمودن نسخه های CD, DVD و سایر رسانه ها مانند حافظه های Flash در [این قسمت از Handbook فری بی اس دی](https://www.freebsd.org/doc/en_US.ISO8859-1/books/handbook/mirrors.html) ارائه می شود.


<br />
<a name="how-can-i-access-the-problem-report-database"></a>

### چگونه می توانم به پایگاه داده گزارش اشکالات دسترسی داشته باشم؟ ###

پایگاه داده Problem Report یا به اختصار PR برای تمامی تغییرات درخواست شده از سوی کاربران [جهت جست و جو از اینجا قابل دسترس می باشد](https://bugs.freebsd.org/search/).  از طریق [رابط کاربری تحت وب ارسال PR](https://www.freebsd.org/support/bugreports.html) می توان اقدام به ارسال گزارش ایرادات، توسط مرورگرهای وب نمود.

قبل از ارسال هرگونه PR بهتر است مقاله [Writing FreeBSD Problem Reports](https://www.freebsd.org/doc/en_US.ISO8859-1/articles/problem-reports/article.html) را در رابطه با چگونگی نوشتن یک PR خوب، مطالعه نمود.


<br />
<a name="is-there-enough-learning-resources-for-freebsd-if-so-where-to-get-them"></a>

### آیا منابع آموزشی کافی برای FreeBSD وجود دارد؟ در این صورت از کجا می توان آن ها را تهیه نمود؟ ###

بله! خوشبختانه FreeBSD کاملترین راهنما در میان تمامی سیستم عامل های کدباز را دارد. تفاوتی نمی کند که دنبال مطالب ساده باشید یا مفاهیم و مستندات پیشرفته، [Handbook](https://www.freebsd.org/doc/handbook/) آن تقریبا شما را از هر منبع دیگری بی نیاز می سازد. همچنین [نسخه ی رسمی PDF این کتابچه راهنما](ftp://ftp.freebsd.org/pub/FreeBSD/doc/en/books/handbook/book.pdf.zip) که مرتبا به روزرسانی می شود به [چندین زبان مختلف](ftp://ftp.freebsd.org/pub/FreeBSD/doc/) در دسترس می باشد.

شایان ذکر است که Handbook های دیگری برای [Porter](https://www.freebsd.org/doc/en/books/porters-handbook/) ها، و [Committer](https://www.freebsd.org/doc/en/articles/committers-guide/article.html) ها در دسترس می باشد. این نکته نشان از حجم بالای مستندسازی و ارزش آن در پروژه FreeBSD دارد.

قطعا به عنوان یک فرد تازه وارد چیزهای زیادی باید بیآموزید و یا سوالات زیادی ذهن شما را به خود مشغول خواهد نمود. باور داشته بشید یا نه، با دنبال نمودن این Handbook ها به یک استاد تمام معنا در FreeBSD تبدیل خواهید شد. برای مثال نگارنده این مطلب، فقط با دنبال نمودن این Handbook، سیستم عامل FreeBSD را آموخته و در منزل، محیط کار و یا به عنوان سرور جهت راه اندازی این وب سایت به کار بسته است. علاوه بر آن با مطالعه Handbook مختص Porter ها، یک کتابخانه Cross-Database به نام [CppDB](http://cppcms.com/sql/cppdb/) را [به این سیستم عامل Port نموده است](https://www.freebsd.org/cgi/ports.cgi?query=cppdb&stype=name). در واقع، مثلا به منظور پورت نمودن نرم افزار اطلاعات دسته اولی وجود دارند که در هیچ منبع یا کتابی غیر از [راهنما](https://www.freebsd.org/doc/en/books/porters-handbook/dads-avoiding-linuxisms.html) یا [مستندات](https://wiki.freebsd.org/AvoidingLinuxisms) آن یافت نمی شوند. دلیل تاکید من بر Handbook فری بی اس دی به عنوان مرجع همین است.


<br />
<a name="what-else-should-i-know"></a>

###  چیز دیگری هست که باید بدانم؟ ###

FAQ حاضر فقط به منظور پاسخ به سوالات افراد تازه وارد به دنیای BSD و البته به طور خاص FreeBSD تهیه شده است. لذا از معرفی مفاهیم پیشرفته دیگری که مختص FreeBSD می باشد (مانند [Jails](https://en.wikipedia.org/wiki/FreeBSD_jail) که از نسخه 4 به بعد برای سال ها در FreeBSD حضور داشته که بعدها توسط [LXC](https://en.wikipedia.org/wiki/LXC) و [Docker](https://en.wikipedia.org/wiki/Docker_(software)) به لینوکس معرفی شد) پرهیز نمودیم. در زمان مقتضی به هریک از این مفاهیم و تکنولوژی ها خواهیم پرداخت.

جهت دریافت کمک، می توانید با عضویت در [انجمن بسیار صمیمی و دوستانه FreeBSD](https://forums.freebsd.org/)، اقدام به رفع مشکلات خود نمائید. از آنجا که با حرفه ای ها طرف هستید، بهتر است پیش از طرح سوال خود [این مطلب را مطالعه نمائید](http://www.catb.org/~esr/faqs/smart-questions.html).

[چنانچه قسمت اول از این سری مقالات](/blog/2016/01/23/the-history-of-freebsd) را مطالعه ننموده اید، توصیه می شود که آن را مطالعه نمائید. پس از مقاله بعدی که به اختصار به مقایسه GNU/Linux و FreeBSD خواهد پرداخت، در سلسله ای از مقالات، به نصب و پیکربندی این سیستم عامل و سرویس های آن، از مبتدی تا پیشرفته خواهیم پرداخت.


<br />

### منابع ###

* [Explaining BSD](https://www.freebsd.org/doc/en/articles/explaining-bsd/article.html)
* [The FreeBSD Handbook / Introduction](https://www.freebsd.org/doc/faq/introduction.html)


<br />

### مقالات مرتبط ###

* [تاریخچه FreeBSD](/blog/2016/01/23/the-history-of-freebsd/)
* [FreeBSD یا Linux مسئله این است؟](/blog/2016/03/07/freebsd-vs-linux/)

