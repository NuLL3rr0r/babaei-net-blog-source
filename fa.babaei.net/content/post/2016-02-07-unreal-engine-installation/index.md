+++
title = "آموزش نحوه ی نصب Unreal Engine 4"
slug = "unreal-engine-installation"
date = 2016-02-07T17:27:57+03:30
tags = [ "Epic", "gamedev", "Game Development", "Game Programming", "indiedev", "UE4", "Unreal Engine" ]
aliases = [ "/blog/2016/02/07/unreal-engine-installation/" ]
+++

{{< figure src="/blog/unreal-engine-installation/unreal-engine-4-a-boy-and-his-kite.jpg" alt="A Boy and His Kite" caption="A Boy and His Kite" link="https://www.youtube.com/watch?v=JNgsbNvkNjE" >}}

[قبلا در مقاله ای مفصل به شرح تاریخچه Unreal Engine پرداخته و سپس با برخی از مفاهیم و کلیات آن آشنا شدیم](/blog/2016/01/25/unreal-engine-4-introduction/). حال نوبت به نصب آن می رسد. نصب این Game Engine و ابزارهای آن بسیار ساده می باشد. اما، دلایلی همچون: نصب آنلاین، فایل های حجیم، دسترسی کند برخی از کاربران به اینترنت و در نهایت تحریم های بین اللملی، ممکن است برخی از کاربران ایرانی را جهت دریافت این نرم افزار با مشکل مواجه کند. لذا علاوه بر نصب UE4، اقدام به ارایه راهکاری مناسب و کم هزینه جهت دریافت آن در چنین شرایطی می نمائیم.

در پایان این مقاله، قادر به انجام موارد ذیل خواهید بود:

* ساخت یک حساب کاربری نزد شرکت Epic Games (البته اگر در حال حاضر چنین حساب کاربری ندارید)
* دریافت و راه اندازی برنامه نصب به نام Epic Game Launcher
* ورود به Epic Game Launcher با حساب کاربری تان
* نصب Unreal Engine
* اجرای Unreal Engine

<!--more-->


<br />

### فهرست ###

* [پیش نیازهای نصب و اجرای Unreal Engine 4](#ue4-prerequisites)
    * [سخت افزار پیشنهادی](#recommended-hardware)
    * [حداقل پیش نیازهای نرم افزاری](#minimum-software-requirements)
        * [نیازمندی های اجرای UE4](#minimum-software-requirements-for-running-the-engine)
        * [نیازمندی های توسعه با UE4](#minimum-software-requirements-for-developing-with-the-engine)
* [نکاتی پیش از نصب](#notes-before-you-begin)
* [نصب](#ue4-installation)
    * [ایجاد حساب کاربری Epic](#creating-an-epic-account)
    * [دریافت و اجرای برنامه نصب](#downloading-and-running-the-installer)
        * [Windows](#downloading-and-running-the-installer-windows)
        * [Mac OS X](#downloading-and-running-the-installer-mac-os-x)
        * [GNU/Linux](#downloading-and-running-the-installer-gnu-linux)
    * [ورود به Epic Games Launcher](#signing-into-the-epic-launcher)
    * [نصب Unreal Engine](#installing-unreal-engine)
* [اجرای Unreal Engine](#launching-unreal-engine)
* [راه حل مشکلات کندی اینترنت و تحریم ها](#windows-vps)


<br />
<a name="ue4-prerequisites"></a>

### پیش نیازهای نصب و اجرای Unreal Engine 4 ###

جهت اجرا و یا توسعه بازی های مبتنی بر Unreal Engine 4 و یا اجرای Editor آن، نیاز به پیش نیازهای سخت افزاری و نرم افزاری خاصی می باشد که در ادامه بدان خواهیم پرداخت.


<br />
<a name="recommended-hardware"></a>

#### سخت افزار پیشنهادی ####

سخت افزار پیشنهادی جهت اجرای Unreal Engine به شرح ذیل می باشد:

<div style="direction: ltr !important;">
    <table class="table table-striped table-hover">
        <tr>
            <th></th>
            <th>
                Windows
            </th>
            <th>
                Mac OS X
            </th>
            <th>
                GNU/Linux
            </th>
        </tr>
        <tr>
            <th>
                Operating System
            </th>
            <td>
                Windows 7/8 64-bit
            </td>
            <td>
                Mac OS X 10.9.2
            </td>
            <td>
                Ubuntu 15.04
            </td>
        </tr>
        <tr>
            <th>
                Processor
            </th>
            <td>
                Quad-core Intel or AMD, 2.5 GHz or faster
            </td>
            <td>
                Quad-core Intel, 2.5 GHz or faster
            </td>
            <td>
                Quad-core Intel or AMD, 2.5 GHz or faster
            </td>
        </tr>
        <tr>
            <th>
                Memory
            </th>
            <td>
                8 GB RAM
            </td>
            <td>
                8 GB RAM
            </td>
            <td>
                16 GB RAM
            </td>
        </tr>
        <tr>
            <th>
                Video Card
            </th>
            <td>
                DirectX 11 compatible graphics card
            </td>
            <td>
                DirectX 11 compatible graphics card
            </td>
            <td>
                NVIDIA GeForce 470 GTX or higher with latest NVidia binary drivers
            </td>
        </tr>
    </table>
</div>


<br />
<a name="minimum-software-requirements"></a>

#### حداقل پیش نیازهای نرم افزاری ####

این لیست به دو بخش تقسیم می شود: اجرای Engine و توسعه با Engine.


<br />
<a name="minimum-software-requirements-for-running-the-engine"></a>

##### نیازمندی های اجرای UE4 #####

لیست ذیل شامل حداقل نیازمندی ها جهت اجرای Engine و یا Editor می باشد:

<div style="direction: ltr !important;">
    <table class="table table-striped table-hover">
        <tr>
            <th></th>
            <th>
                Windows
            </th>
            <th>
                Mac OS X
            </th>
            <th>
                GNU/Linux
            </th>
        </tr>
        <tr>
            <th>
                Operating System
            </th>
            <td>
                Windows 7/8 64-bit
            </td>
            <td>
                Mac OS X 10.9.2+
            </td>
            <td>
                Any reasonable new Linux distro (CentOS 6.x being the oldest tested)
            </td>
        </tr>
        <tr>
            <th>
                DirectX Runtime
            </th>
            <td>
                DirectX End-User Runtimes (June 2010)
            </td>
            <td>
                N/A
            </td>
            <td>
                N/A
            </td>
        </tr>
        <tr>
            <th>
                Kernel Version
            </th>
            <td>
                N/A
            </td>
            <td>
                N/A
            </td>
            <td>
                kernel 2.6.32 or newer
            </td>
        </tr>
        <tr>
            <th>
                Additional Dependencies
            </th>
            <td>
                -
            </td>
            <td>
                -
            </td>
            <td>
                glibc 2.12.2 or newer
            </td>
        </tr>
    </table>
</div>


<br />
<a name="minimum-software-requirements-for-developing-with-the-engine"></a>

##### نیازمندی های توسعه با UE4 #####
نیازمندی های توسعه با Unreal Engine 4 به شرح ذیل می باشد:

<div style="direction: ltr !important;">
    <table class="table table-striped table-hover">
        <tr>
            <th></th>
            <th>
                Windows
            </th>
            <th>
                Mac OS X
            </th>
            <th>
                GNU/Linux
            </th>
        </tr>
        <tr>
            <th>
                IDE
            </th>
            <td>
                Visual Studio 2015 Professional or Community<br />
                Visual Studio 2013 Ultimate, Professional or Community (will be deprecated with 4.11.0 release)
            </td>
            <td>
                Xcode 5.0+
            </td>
            <td>
                QtCreator 3.1+ or KDevelop 4.6+
            </td>
        </tr>
        <tr>
            <th>
                Compiler
            </th>
            <td>
                Visual C++
            </td>
            <td>
                Clang
            </td>
            <td>
                Clang 3.5.x or 3.6.x
            </td>
        </tr>
        <tr>
            <th>
                Build System 
            </th>
            <td>
                -
            </td>
            <td>
                -
            </td>
            <td>
                CMake 2.8+
            </td>
        </tr>
    </table>
</div>


<br />
<a name="notes-before-you-begin"></a>

### نکاتی پیش از نصب ###

با توجه به تحریم های بین المللی، در تمامی مراحل این آموزش فرض بر این است که شما به هیچ وجه از IP ایران استفاده نمی نمائید. در غیر اینصورت امکان طی نمودن هیچ یک از این مراحل وجود نخواهد داشت.

فرآیند کلی نصب به اینصورت خواهد بود که ابتدا یک حساب کاربری Epic Games ایجاد می نمائیم. سپس اقدام به دریافت Epic Games Launcher که برنامه نصب Unreal Engine 4 می باشد، می نمائیم. توسط حساب کاربری ایجاد شده می توان وارد Epic Games Launcher شد. Epic Game Launcher امکان دریافت و نصب UE4 به همراه به روزرسانی آن را فراهم می آورد.

{{< figure src="/blog/unreal-engine-installation/installation-goal.jpg" alt="تصویر 1. Epic Games Launcher" caption="تصویر 1. Epic Games Launcher" >}}

__توجه__: چنانچه پیش از این مراحل تهیه حساب کاربری را طی نموده اید، می توانید مستقیما به بخش [دریافت و اجرای برنامه نصب](#downloading-and-running-the-installer) مراجعه نمائید.


<br />
<a name="ue4-installation"></a>

### نصب ###

نصب UE4 شامل چندین مرحله می باشد که در ادامه بدان می پردازیم.

<br />
<a name="creating-an-epic-account"></a>

#### ایجاد حساب کاربری Epic ####

جهت نصب Epic Games Launcher، به یک حساب کاربری Epic Games نیاز خواهید داشت.

1. ابتدا به وب سایت [UnrealEngine.com](https://www.unrealengine.com/) مراجعه نمائید.
2. بر روی دکمه Get Unreal کلیک نمائید (تصویر 2.).

{{< figure src="/blog/unreal-engine-installation/unreal-website.jpg" alt="تصویر 2. وب سایت Unreal Engine" caption="تصویر 2. وب سایت Unreal Engine" >}}

3. پس از آن فرم Join the Community را با مشخصات و ایمیل خود پر نموده، سپس بر روی دکمه Sign Up کلیک نمائید (تصویر 3.).

{{< figure src="/blog/unreal-engine-installation/signup-screen.jpg" alt="تصویر 3. صفحه ایجاد حساب کاربری" caption="تصویر 3. صفحه ایجاد حساب کاربری" >}}

__توجه__: توصیه می شود پیش از ثبت نام [شرایط استفاده از خدمات Epic Games](http://epicgames.com/tos) را مطالعه نمائید.
</pre>

4. پیش از کلیک بر روی دکمه Accept شرایط استفاده از Unreal Engine را مطالعه نمائید (تصویر 4.).

{{< figure src="/blog/unreal-engine-installation/eula.jpg" alt="تصویر 4. توافقنامه مجوز کاربر نهایی یا EULA" caption="تصویر 4. توافقنامه مجوز کاربر نهایی یا EULA" >}}

__توجه__: در صورت بروز سوالات بیشتر در مورد EULA و چگونگی شرایط استفاده آن به [قسمت پرسش و پاسخ آن در وب سایت Unreal Engine](https://www.unrealengine.com/faq#legal) مراجعه نمائید.
</pre>

شایان ذکر است که این حساب کاربری علاوه بر Epic Games Launcher، در [انجمن Unreal Engine](https://forums.unrealengine.com/) هم معتبر و قابل استفاده بوده و توسط آن می توان به این انجمن نیز دسترسی داشت.

<br />
<a name="downloading-and-running-the-installer"></a>

#### دریافت و اجرای برنامه نصب ####

با داشتن یک حساب کاربری معتبر Epic Games، قادر به دریافت برنامه نصب به نام Epic Games Launcher خواهید بود.


<br />
<a name="downloading-and-running-the-installer-windows"></a>

##### Windows #####

1. با کلیک بر روی دکمه دانلود اقدام به دریافت برنامه نصب نمائید.

{{< figure src="/blog/unreal-engine-installation/download-screen.jpg" alt="تصویر 5. صفحه دریافت Epic Games Launcher" caption="تصویر 5. صفحه دریافت Epic Games Launcher" >}}

2. پس از دریافت کامل فایل، برنامه نصب را اجرا نمائید.

{{< figure src="/blog/unreal-engine-installation/run-installer.jpg" alt="تصویر 6. اجرای برنامه نصب" caption="تصویر 6. اجرای برنامه نصب" >}}

3. پس از ظاهر شدن پنجره Epic Games Launcher Setup بر روی دکمه Install کلیک نمائید.

{{< figure src="/blog/unreal-engine-installation/run-epic-launcher-setup.jpg" alt="تصویر 7. برنامه نصب Epic Games Launcher" caption="تصویر 7. برنامه نصب Epic Games Launcher" >}}


<br />
<a name="downloading-and-running-the-installer-mac-os-x"></a>

##### Mac OS X #####

1. با کلیک بر روی دکمه دانلود اقدام به دریافت برنامه نصب نمائید (تصویر 5.).
2. بر روی فایل دریافت شده با نام <code>EpicGamesLauncher.dmg</code> دابل کلیک نمائید تا محتویات آن در پنجره Finder نمایش داده شود.
3. آیکن Epic Games Launcher را به داخل پوشه Applications درگ نمائید.

{{< figure src="/blog/unreal-engine-installation/install-epic-laucher-mac.jpg" alt="تصویر 8. برنامه نصب Epic Games Launcher در سیستم عامل Mac OS X" caption="تصویر 8. برنامه نصب Epic Games Launcher در سیستم عامل Mac OS X" >}}


<br />
<a name="downloading-and-running-the-installer-gnu-linux"></a>

##### GNU/Linux #####

متاسفانه در حال حاضر برنامه نصب Unreal Engine برای گنو لینوکس به شکل باینری عرضه نمی شود.

__نکته__: در حال حاضر کاربران GNU/Linux می توانند با استفاده از [سورس کد Unreal Engine بر روی GitHub](https://github.com/EpicGames/UnrealEngine) اقدام به کامپایل و نصب آن نمایند. در مقاله ای دیگر به این موضوع خواهیم پرداخت.


<br />
<a name="signing-into-the-epic-launcher"></a>

#### ورود به Epic Games Launcher ####

پس از آنکه برنامه نصب،  Epic Games Launcher بر روی دستگاه شما نصب نمود، با اجرا نمودن آن و سپس استفاده از اطلاعات حساب کاربری خود به داخل Epic Games Launcher لاگین نمائید.

{{< figure src="/blog/unreal-engine-installation/epic-sign-in.jpg" alt="تصویر 9. ورود به حساب کاربری Epic از داخل Launcher" caption="تصویر 9. ورود به حساب کاربری Epic از داخل Launcher" >}}


<br />
<a name="installing-unreal-engine"></a>

#### نصب Unreal Engine ####

بسیار خب، اکنون پس از ورود به Epic Games Launcher شما قادر به نصب UE4 خواهید بود.

<pre style="direction: rtl; text-align: justify; word-break: keep-all; white-space: pre-wrap;">
فضای مورد نیاز

به ازای هر نسخه ای از Unreal Engine که - به شکل باینری - توسط Epic Games Launcher در سیستم شما نصب می شود، به 8 گیگابایت فضا نیاز خواهید داشت.

پیش از نصب UE4 از داشتن فضای کافی بر روی هارد دیسک خود اطمینان حاصل نمائید.
</pre>

1. در صفحه بارگذاری Epics Game Launcher بر روی زبانه Unreal Engine کلیک نمائید.

{{< figure src="/blog/unreal-engine-installation/launcher-load-screen.jpg" alt="تصویر 10. صفحه بارگذاری Epic Games Launcher" caption="تصویر 10. صفحه بارگذاری Epic Games Launcher" >}}

2. سپس بر روی دکمه Install Engine جهت نصب آخرین نسخه از Unreal Engine، کلیک نمائید.

{{< figure src="/blog/unreal-engine-installation/install-engine.jpg" alt="تصویر 11. نصب Engine" caption="تصویر 11. نصب Engine" >}}

3. پیش از کلیک بر روی دکمه Accept، شرایط استفاده از Unreal Engine را مطالعه نمائید.

{{< figure src="/blog/unreal-engine-installation/accept-eula-launcher.jpg" alt="تصویر 12. قبول توافقنامه مجوز نهایی کاربر" caption="تصویر 12. قبول توافقنامه مجوز نهایی کاربر" >}}

4. در صورت دسترسی به اینترنت با پهنای باند قابل قبول، نصب UE4 ممکن است چندین دقیقه تا چندین ساعت به طول بیانجامد. در صورتی که پهنای باند اینترنت شما قابل توجه نمی باشد استفاده از [روشی که در انتهای این مقاله شرح داده شده](#windows-vps) است، توصیه می شود.

{{< figure src="/blog/unreal-engine-installation/downloading-engine.jpg" alt="تصویر 13. دریافت Engine" caption="تصویر 13. دریافت Engine" >}}


<br />
<a name="launching-unreal-engine"></a>

### اجرای Unreal Engine ###

پس از آنکه Unreal Engine توسط Epic Games Launcher با موفقیت دریافت شد، با کلیک بر روی دکمه Launch می توانید UE4 را اجرا نمائید.

{{< figure src="/blog/unreal-engine-installation/launch-ue4.jpg" alt="تصویر 14. اجرای UE4" caption="تصویر 14. اجرای UE4" >}}

تبریکات صمیمانه مرا پذیرا باشید! شما آموختید که:

* یک حساب کاربری Epic Games ایجاد کنید
* برنامه نصب به نام Epic Games Launcher را دریافت و اجرا نمائید
* با استفاده از حساب کاربری خود وارد Epic Games Launcher شوید
* Unreal Engine را نصب نمائید
* Unreal Engine را اجرا نمائید



<br />
<a name="windows-vps"></a>

### راه حل مشکلات کندی اینترنت و تحریم ها ###

جهت غلبه بر مسایلی از این دست راه های متفاوت زیادی وجود دارد. اما Foolproof ترین راه ممکن خرید یک سرور مجازی ویندوزی (Windows VPS) می باشد. جهت اتصال به سرور های ویندوزی می توان از <code>mstsc</code> که به همراه Microsoft Windows عرضه می شود، استفاده نمود. کافیست پنجره Run را با فشردن کلید میانبر <code>Windows+R</code>  بر روی صفجه کلید، باز نموده و دستور <code>mstsc</code> را تایپ و اجرا نمود (تصویر 15.):

{{< figure src="/blog/unreal-engine-installation/run-mstsc.png" alt="تصویر 15. اجرای mstsc" caption="تصویر 15. اجرای mstsc" >}}
[{% img post-image  427 235 "'تصویر 15. اجرای mstsc'" "'تصویر 15. اجرای mstsc'" %}](/blog/unreal-engine-installation/run-mstsc.png)

معمولا پس از تهیه یک سرور مجازی ویندوز، آدرس IP سرور و یا نام Domain به همراه یک نام کاربری و کلمه عبور در اختیار شما قرار می گیرد. با اجرا نمودن <code>mstsc</code> کادری مشابه تصویر 16. باز می شود. جهت اتصال، در کادر Computer نام Domain و یا IP مورد نظر را تایپ نموده و کلید Connect را بفشارید. پس از آن در صورت اتصال موفقیت آمیز اولیه با سرور مجازی، این برنامه با نمایش کادر دیگری از شما نام کاربری و کلمه عبور را می طلبد. شایان ذکر است که علاوه بر ویندوز، نرم افزارهای مشابهی برای سیستم عامل های FreeBSD, GNU/Linux و Mac OS X بدین منظور عرضه می شوند.

{{< figure src="/blog/unreal-engine-installation/remote-desktop-connection.png" alt="تصویر 16. اتصال به سرور مجازی راه دور از طریق Remote Desktop Connection" caption="تصویر 16. اتصال به سرور مجازی راه دور از طریق Remote Desktop Connection" >}}

با وارد نمودن اطلاعات صحیح و برقراری ارتباط موفقیت آمیز با سرور مجازی، درست مانند کامپیوتر دسکتاپ خود می توانید از محیط دسکتاپ آن استفاده نمائید. چنانچه سرور مجازی با مشخصات مناسب (به خصوص دارای پورت گیگابیتی) تهیه نمایید قادر به دریافت و نصب UE4 فقط در عرض چند دقیقه خواهید بود. پس از آن می توانید با فشرده نمودن پوشه نصب شده Unreal Engine 4 بر روی سرور، با استفاده از نرم افزارهای FTP و یا راه اندازی یک وب سرور ساده مانند [Nginx](http://nginx.org/) فایل فشرده شده را به راحتی به کامپیوتر خود انتقال دهید.

بهای یک VPS ویندوز سرور 2008 و یا 2012 بسته به مشخصات آن می تواند از 15 تا 150 هزار تومان در ماه متغییر باشد. با یک جستجوی ساده در موتورهای جستجو و یا مراجعه به انجمن هائی مانند [وب هاستینگ تاک](http://www.webhostingtalk.ir/)، می توان سرویس های متفاوتی را با قیمت های درخور یافت نمود.

لازم به ذکر است که اگر قصد توسعه بازی های مبتنی بر Android با UE4 را داشته باشید به [مجموعه کیت توسعه نرم افزار  NVPack از سوی شرکت NVidia](https://developer.nvidia.com/codeworks-android) نیاز خواهید داشت (در مقاله ای دیگر نصب و راه اندازی آن جهت توسعه Game های مبتنی بر Android را به تفصیل شرح خواهیم داد) که متاسفانه دسترسی به این کیت توسعه هم برای کاربران ایرانی مسدود شده است. لذا جهت توسعه بازی با استفاده از Unreal Engine 4 و NVPack، برای اکثر کاربران ایرانی استفاده از یک VPS ویندوزی تقریبا اجتناب ناپذیر می نماید.

<br />

در مقاله بعدی به روش دیگر نصب UE4 که شامل دریافت سورس کد آن از GitHub و کامپایل نمودن از سورس می باشد، می پردازیم.


<br />

### منابع ###

* [Unreal Engine 4 Hardware & Software Specifications](https://docs.unrealengine.com/latest/INT/GettingStarted/RecommendedSpecifications/index.html)
* [Installing Unreal Engine](https://docs.unrealengine.com/latest/INT/GettingStarted/Installation/index.html)


<br />

### مقالات مرتبط ###

* [مقدمه ای بر موتور ساخت بازی Unreal Engine 4](/blog/2016/01/25/unreal-engine-4-introduction/)
