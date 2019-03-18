+++
title = "دور زدن فیلترینگ و دسترسی آزاد به تلگرام"
slug = "circumvent-telegram-censorship"
date = 2019-03-17T09:15:36+01:00
tags = [ "Censorship", "REST", "RESTful", "Telegram", "WebSocket" ]
toc = true
+++

{{< figure src="/blog/circumvent-telegram-censorship/telegram-logo.png" alt="تلگرام" >}}

 حاج آقا عندالموءمنین می فرمایند: "[فی الواقع](https://twitter.com/hashtag/%D9%81%DB%8C_%D8%A7%D9%84%D9%88%D8%A7%D9%82%D8%B9?src=hash)، به تعداد آدم‌ها راه هست برای دور زدن فیلترینگ تلگرام."

به دلیل فیلترینگ و اختلالاتی که بهار گذشته در دسترسی به تلگرام ایجاد شد، متاسفانه زندگی حرفه ای و شخصی بسیاری از کاربران آن در ایران با مشکلات عدیده ای مواجه شد. به شخصه به این دلیل که از تلگرام به منظور یادگیری و کار استفاده می نمودم، گاها نیاز داشتم که از فایل های صوتی و تصویری آموزش زبان گرفته تا مستندات و فایل های مربوط به پروژه هائی که در آن ها مشارکت داشتم را با استفاده از این سرویس دریافت و یا ارسال نمایم. از طرفی، سرعت بسیار پائین آپلود در اکثر سرویس دهنده های اینترنت و همچنین اختلال در کار قندشکن ها (می بخشید اشتباه لپی شد؛ فیلترشکن ها) هم مزید بر افت چند برابری سرعت شده بود تا آنجائی که خیلی از مواقع به هیچ وجه امکان ارسال حتی فایل های کم حجم هم وجود نداشت، چه رسد به فایل های حجیم صوتی یا تصویری.

با وجود این که پیش از این هیچ آشنائی قبلی با طراحی و پیاده سازی بات های تلگرام نداشتم (جز این که احتمالا تلگرام برای دسترسی عمومی به سرویس خود یک API به شکل RESTful یا WebSocket عرضه نموده)، در همان بازه زمانی با بررسی مستندات رسمی تلگرام، خوشبختانه خیلی سریع و در عرض یکی دو ساعت موفق شدم راهی را برای فائق آمدن بر مشکلات یاد شده پیدا کنم: ایجاد و برنامه نویسی یک بات که بتوان با افزودن به گروه های مورد نظر بدون نیاز به قندشکن و نرم افزارهای مشابه فایل ها را محدود به حداکثر سرعت آپلود، ارسال نمود. فی الواقع اصلا فکر نمی کردم ایجاد بات و استفاده از API تلگرام تا بدین حد ساده باشد. [این مطلب را هم قصد داشتم در همان زمان منتشر کنم](https://github.com/NuLL3rr0r/babaei-net-blog-source/commit/00fec16e67dc051c354d50ea5dbb410865848621) تا شاید برای اکثر افراد مفید واقع شود که متاسفانه به دلایلی همچون مشغله زیاد تا این لحظه اتفاق نیافتاد. این بات به خوبی جوابش را پس داده و پس از ماه ها استفاده هنوز هم قابل اتکا بوده و به خوبی کار می کند.

{{< figure src="/blog/circumvent-telegram-censorship/real-world-sos-use-case-tweet.png" alt="ارسال پیام توسط دود با استفاده از روش سرخ پوست ها جهت دور زدن فیلترینگ تلگرام" caption="ارسال پیام توسط دود با استفاده از روش سرخ پوست ها جهت دور زدن فیلترینگ تلگرام" >}}

در ادامه این مطلب نه تنها نحوه ایجاد چنین ابزاری را خواهیم آموخت، بلکه کد این ابزار جهت استفاده در اختیار شما قرار می گیرد تا بدون نیاز به دانش برنامه نویسی بتوانید آن را راه اندازی کنید. با وجود به اشتراک گذاشتن تمامی کدها، از آنجائی که ممکن است برخی از افراد تمایلی به یادگیری نحوه کد نویسی بات ها در تلگرام نداشته باشند، از توضیح کد خودداری نموده تا ارائه مطلب برای طیف بیشتری از افراد ساده و قابل درک بماند. البته این به آن معنی نیست که هیچ گونه دانشی جهت راه اندازی این بات نیاز نخواهد بود. در واقع فرض بر این است که مخاطب این راهنما، یک کاربر متوسط کامیپوتر خواهد بود.

بسیار خب! و اما پیش نیازها:

<div style="direction: rtl !important; margin: 2.0em 0;">
    <table class="table table-striped table-hover">
        <tr>
            <th style="text-align: right; width: 50%;">
                مدت زمان
            </th>
            <td style="text-align: right; width: 50%;">
                ۳۰ دقیقه
            </td>
        </tr>
        <tr>
            <th style="text-align: right; width: 50%;">
                سطح مطلب
            </th>
            <td style="text-align: right; width: 50%;">
                گروه سنی الف :smile:
            </td>
        </tr>
        <tr>
            <th style="text-align: right; width: 50%;">
                زیرساخت
            </th>
            <td style="text-align: right; width: 50%;">
                سرور فیزیکی یا مجازی، و یا دسترسی به فضای میزبانی وب با دسترسی به اینترنت آزاد
            </td>
        </tr>
        <tr>
            <th style="text-align: right; width: 50%;">
                دانش نرم افزاری
            </th>
            <td style="text-align: right; width: 50%;">
                نصب، پیکربندی و راه اندازی وب سرور (تنها برای سرور فیزیکی یا مجازی، در صورت اجاره هاست نیاز نیست)
                <br />
                <br />
                اختیاری: آشنائی مقدماتی با یک زبان برنامه نویسی سمت سرور. مثلا PHP؛ به خصوص اگر قصد توسعه کد بات به منظور افزودن قابلیت های بیشتر را دارید
            </td>
        </tr>
    </table>

<p style="text-align: center;">
    پیش نیازها
</p>
</div>

در پایان، اضافه کنم که هر چند من دکمه ای دارم به نام C++ که تمامی کت و شلوارهایم را با آن ست می کنم :blush:، تا بدان جا که [برنامه نویسی وب و بک اند را هم با C++ انجام میدهم](https://github.com/NuLL3rr0r/blog-subscription-service)، اما چون دنبال کردن مطلب برای مخاطبین به سرعت سخت می شود، و علاوه بر این ها نمی توان در هاست های اشتراکی از C++ استفاده نمود، با وجود این که تا پیش از این با PHP آشنائی نداشتم، بات مورد نظر را به دلایل پرواضح و مبرهنی که اشاره شد، در این مطلب با PHP طراحی و پیاده سازی می نمائیم.

<!--more-->

## ایجاد بات و انجام تنظیمات آن

۱. ابتدا در نرم افزار تلگرام (تفاوتی میان نسخه PC، موبایل یا وب وجود ندارد) با استفاده از قابلیت جستجو BotFather را پیدا نمائید.

{{< figure src="/blog/circumvent-telegram-censorship/telegram-bot-father-search.png" alt="یافتن BotFather در تلگرام" caption="یافتن BotFather در تلگرام" >}}

۲. BotFather ابزار رسمی تلگرام برای ساخت و مدیریت بات ها می باشد. چنانچه قبلا از این بات استفاده ننموده اید، با اطلاعات ذیل مواجه خواهید شد. جهت شروع استفاده بر روی دکمه استارت کلیک یا تپ نمائید.

{{< figure src="/blog/circumvent-telegram-censorship/telegram-bot-father-start.png" alt="شروع استفاده از BotFather" caption="شروع استفاده از BotFather" >}}

۳. همانطور که در تصویر بالا مشاهده می کنید. برای ایجاد یک بات جدید به دستور newbot احتیاج داریم. بر روی این دستور کلیک نموده یا آن را تایپ و سپس ارسال نمائید. پس از ارسال این دستور BotFather از شما می خواهد نامی را برای بات خود تعیین نمائید (فارسی یا انگلیسی تفاوتی ندارد و حق استفاده از هر کاراکتری را دارید، در واقع این نامی است که نمایش داده می شود و با نام کاربری متفاوت است)؛ و پس از آن نام کاربری مورد نظر برای بات را (فقط کاراکتر های A تا Z، کوچک یا بزرگ تفاوتی ندارد؛ اعداد ۰ تا ۹؛ و در نهایت کاراکتر Underscore. دقت نمائید که حق استفاده از کاراکتر فاصله را ندارید).

{{< figure src="/blog/circumvent-telegram-censorship/telegram-bot-father-newbot.png" alt="دستور newbot" caption="دستور newbot" >}}

همانطور که در تصویر فوق مشاهده می شود، مهمترین چیزی که پس از تکمیل دستور newbot در اختیار شما قرار می گیرد HTTP API Access Token می باشد. که در مثال ما <code>766664963:AAHPXGLPzdGXrtMiqL1bGbQwglhsjDJEafI</code> می باشد. در واقع هر فردی که این Access Token را در اختیار داشته باشد می تواند کنترل بات را به دست بگیرد. پس، آن را در جای امنی نگهداری و با هیچ کس به اشتراک نگذارید.

۴. سپس جهت درج توضیحات تکمیلی برای بات مورد نظرتان، دستور setdescription را وارد نمائید. چنانچه می خواهید سایر کاربران تلگرام از انگیزه و کاربرد بات شما مطلع شوند از دستور setabouttext استفاده نمائید. اگر بیش از یک بات در اختیار دارید، پس از ارسال هریک از دستورات فوق BotFather از شما می خواهد که بات مورد نظرتان را جهت افزودن توضیحات تکمیلی انتخاب نمائید.

{{< figure src="/blog/circumvent-telegram-censorship/telegram-bot-father-setdescription-setabouttext.png" alt="دستورات setdescription و setabouttext" caption="دستورات setdescription و setabouttext" >}}

۵. در نهایت جهت تعیین تصویر کاربری برای باتی که ایجاد نموده اید، از دستور setuserpic استفاده نمائید. مانند دستورات قبلی چنانچه بیش از یک بات در اختیار دارید، ابتدا بات جدید را انتخاب و سپس تصویری را از گالری یا هارد درایو کامپیوترتان انتخاب و آپلود نمائید.

{{< figure src="/blog/circumvent-telegram-censorship/telegram-bot-father-setuserpic.png" alt="دستور setuserpic" caption="دستور setuserpic" >}}

۶. در ادامه، نیاز داریم که مطمئن شویم بات جدید قابلیت افزوده شدن به گروه ها را دارد. بدین منظور دستور setjoingroups را صادر می نمائیم.

{{< figure src="/blog/circumvent-telegram-censorship/telegram-bot-father-setjoingroups.png" alt="دستور setjoingroups" caption="دستور setjoingroups" >}}

۷. در مرحله آخر با استفاده از دستور setprivacy به بات جدید اجازه دسترسی به پیام های داخل گروه را خواهیم داد. از این به بعد هر پیام جدیدی که توسط اعضای گروه ارسال شود به بات اطلاع داده شده و مخابره خواهد شد. چنانچه فقط قصد ارسال فایل، تصویر، ویدیو یا پیام را دارید و قصد خواندن پیام ها توسط بات را ندارید می توانید وضعیت Privacy را در حالت Enabled قرار دهید. در این حالت، کماکان قابلیت افزودن بات به گروه ها و ارسال هر گونه فایل یا پیامی را خواهید داشت، اما بات فقط زمانی به محتوای پیام ها دسترسی خواهد داشت که پیام با کاراکتر <code>/</code> شروع شده باشد یا اینکه یکی از اعضای گروه در پیام مربوطه نام بات را با استفاده از <code>@</code> به اصطلاح ذکر یا Mention نماید. جهت تکمیل این مقاله آموزشی ما این قابلیت را در وضعیت Disabled قرار می دهیم تا بات بدون محدودیت به تمامی پیام ها دسترسی داشته باشد.

{{< figure src="/blog/circumvent-telegram-censorship/telegram-bot-father-setprivacy.png" alt="دستور setprivacy" caption="دستور setprivacy" >}}

بسیار عالی! هم اکنون بات ما آماده افزوده شدن به گروه های تلگرام می باشد.

## نحوه افزودن بات به گروه مورد نظر

افزودن بات به گروه های تلگرام مانند افزودن یک کاربر عادی از طریق کادر Add Members صورت می گیرد. به این منظور نام کاربری بات را بدون فاصله پس از کاراکتر <code>@</code> در کادر جستجو وارد نمائید. ممکن است پیدا کردن بات چند لحظه ای زمان ببرد، پس صبور باشید.

{{< figure src="/blog/circumvent-telegram-censorship/telegram-add-bot-to-group.png" alt="افزودن بات به یک گروه تلگرام از طریق کادر Add Members" caption="افزودن بات به یک گروه تلگرام از طریق کادر Add Members" >}}

با افزودن بات به گروه از طریق دکمه INVITE، پیام افزوده شدن موفقیت آمیز بات به گروه توسط تلگرام به شما اعلام می شود:

{{< figure src="/blog/circumvent-telegram-censorship/telegram-add-bot-to-group-confirmation-log.png" alt="افزوده شدن موفقیت آمیز بات به گروه" caption="افزوده شدن موفقیت آمیز بات به گروه" >}}

علاوه بر این، پس از افزودن بات در قسمت اطلاعات گروه می توانید بات را در میان اعضای گروه مشاهده نمائید. همچنین در تلگرام اندروید یا Telegram X می توان سطح دسترسی بات به پیام ها را مشاهده نمود:

{{< figure src="/blog/circumvent-telegram-censorship/telegram-desktop-group-info.png" alt="صفحه اطلاعات گروه پس از افزودن بات در تلگرام نسخه دسکتاپ" caption="صفحه اطلاعات گروه پس از افزودن بات در تلگرام نسخه دسکتاپ" >}}

{{< figure src="/blog/circumvent-telegram-censorship/telegram-x-android-group-info.png" alt="صفحه اطلاعات گروه پس از افزودن بات در تلگرام X نسخه اندروید" caption="صفحه اطلاعات گروه پس از افزودن بات در تلگرام X نسخه اندروید" >}}

{{< figure src="/blog/circumvent-telegram-censorship/telegram-android-group-info.png" alt="صفحه اطلاعات گروه پس از افزودن بات در تلگرام نسخه اندروید" caption="صفحه اطلاعات گروه پس از افزودن بات در تلگرام نسخه اندروید" >}}

در نظر داشته باشید که بات دوم با نام Le bot uploader در تمامی تصاویر بالا یک بات مجزاست که قبلا در گروه اضافه شده و ربطی به بات فعلی ندارد. در یک گروه محدودیتی برای افزودن بات های متعدد، جز حداکثر تعداد اعضا وجود ندارد.

در بخش بعدی کد مورد نیاز جهت استفاده از بات و نحوه تنظیم آن در اختیار شما قرار می گیرد.

## دریافت کد بات

چنانچه از گیت استفاده می نمائید، با دستور ذیل کد کل کامل را از GitHub یا GitLab دریافت نمائید:

{{< codeblock lang="bash" title="دریافت از گیت هاب" >}}
$ git clone https://github.com/NuLL3rr0r/telegram-seditious-bot.git
{{< /codeblock >}}

{{< codeblock lang="bash" title="دریافت از گیت لب" >}}
git clone https://gitlab.com/NuLL3rr0r/telegram-seditious-bot.git
{{< /codeblock >}}

در غیر اینصورت با مراجعه به [Repository گیت هاب](https://github.com/NuLL3rr0r/telegram-seditious-bot) و یا [Repository گیت لب](https://gitlab.com/NuLL3rr0r/telegram-seditious-bot) اقدام به دریافت سورس کد بات در قالب یک فایل فشرده (فرمت zip برای GitHub و یا یکی از فرمت های zip, tar, tar.gz, tar.bz2 برای GitLab) نمائید:

{{< figure src="/blog/circumvent-telegram-censorship/telegram-seditious-bot-github-source-code.png" alt="دریافت فایل فشرده سورس کد Telegram Seditious Bot از GitHub" caption="دریافت فایل فشرده سورس کد Telegram Seditious Bot از GitHub" >}}

{{< figure src="/blog/circumvent-telegram-censorship/telegram-seditious-bot-gitlab-source-code.png" alt="دریافت فایل فشرده سورس کد Telegram Seditious Bot از GitLab" caption="دریافت فایل فشرده سورس کد Telegram Seditious Bot از GitLab" >}}

پس از دانلود، فایل را از حالت فشرده خارج سازید. در بخش بعدی نحوه تنظیم بات و افزودن آن به گروه های تلگرام را خواهیم آموخت.

## انجام تنظیمات کد و اتصال آن به بات تگرام

جهت اجرای کد بات نیازمند [مفسر زبان PHP](https://php.net/) می باشیم. کد ارائه شده در این مطلب به خوبی در نسخ 7.2 و 7.3 این مفسر اجرا، تست شده و کار می کند. جهت اجرای این کد به یک محیط LAMP (مخفف [Linux](https://kernel.org) / [Apache](https://apache.org) / [MySQL](https://mysql.com) or [MariaDB](https://mariadb.org) / PHP) یا LEMP / LNMP (مخفف Linux / [Nginx](https://nginx.org) / MySQL or MariaDB / PHP) نیاز دارید. در یک کامیپوتر شخصی ویندوز و یا سرورهای ویندوزی می توانید از [EasyPHP](https://easyphp.org/) استفاده نمائید. از آنجائی که نگارنده [توسعه دهنده و مسئول نگهداری چندین Port رسمی سیستم عامل FreeBSD](https://freebsd.org/cgi/ports.cgi?query=info%40babaei.net&stype=maintainer) می باشد، Stack مورد علاقه نگارنده FEMP (مخفف [FreeBSD](https://freebsd.org) / Nginx / MySQL or MariaDB / PHP) می باشد؛ در نتیجه، کد اصلی بر روی این محیط توسعه داده شده است و بر روی این Stack نیز به خوبی کار می کند.

 علاوه بر دسترسی به مفسر PHP، دیگر نیازمندی کد بات جهت اجرا، دسترسی به سرور اصلی تلگرام می باشد. بنابراین بایستی کد بات را بر روی یک سرور واقعی یا مجازی در خارج از ایران آپلود نمائید. با این کار علاوه بر دسترسی به سرور اصلی تلگرام، امکان استفاده از این بات را برای افرادی غیر از خودتان مهیا می سازید. انتخاب دیگر، استفاده از Host های اشتراکی می باشد که قابلیت پشتیبانی از PHP را دارند که هم ارزان قیمت و قابل دسترس بوده و هم استفاده از آن ها به دلیل رابط کاربری مبتنی بر نرم افزارهای مدیریت سایت و سرور مانند [CPanel](https://cpanel.net/) بسیار ساده می باشد. علاوه بر این ها، امکان استفاده از فضاهای رایگان مانند [GitHub Pages](https://pages.github.com/) که علاوه بر ترافیک نامحدود، برخورداری از گواهینامه رایگان SSL، آدرس اینترنتی به شکل Subdomain، قابلیت اتصال به دامین اختصاصی خودتان را فراهم می کند نیز وجود دارد. البته در نظر داشته باشید که سرویس GitHub Pages از PHP پشتیبانی نمی نماید. با این وجود می توان تمامی قابلیت های ارائه شده در این مقاله را با استفاده از Static HTML و [تگ form](https://www.w3schools.com/tags/tag_form.asp) فراهم نمود. اما توجه داشته باشید که این امر مستلزم افزودن HTTP API Access Token به آدرس API تلگرام در قسمت action فرم HTML می باشد که باعث لو رفتن آن و کنترل بات شما توسط دیگران می شود.

 انتخاب شما هر چه که باشد، بایستی فایل های سورس کد دریافتی در مرحله قبل را، به پوشه ریشه وب سرور یا Web Server Root Directory منتقل نمائید. در ادامه فرض بر این است که این پوشه در سرور در آدرس <code>/path/to/telegram-seditious-bot</code> قرار دارد و دامین ما جهت تعامل با بات از طریق رابط کاربری مبتنی بر وب <code>https://telegram.babaei.net</code> می باشد.

بسیار خب، پس از آپلود به وب سرور، فایل <code>config.php</code> را در برنامه ویرایشگر خود باز نمائید:

{{< codeblock lang="bash" title="config.php" >}}
<!--
  (The MIT License)

  Copyright (c) 2018 - 2019 Mamadou Babaei

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
-->

<?php
    /* User-configurable settings */
    $botToken      = "766664963:AAHPXGLPzdGXrtMiqL1bGbQwglhsjDJEafI";
    $botName       = "Seditious Bot";
    $chatId        = "-277738700";
    $chatName      = "Barandazan";
    $fetchInterval = 120;

    /* Do not touch this! Unless you know what you're doing. */
    $api = "https://api.telegram.org/bot".$botToken;
?>
{{< /codeblock >}}

همانطور که مشاهده می نمائید، تنظیمات بات در این قسمت انجام می پذیرد.

* <code>$botToken</code>: در این قسمت مقدار HTTP API Access Token که در مراحل قبل از طریق BotFather به دست آوردیم را وارد می نمائیم.
* <code>$botName</code>: نام بات جهت نمایش در رابط کاربری وب در این قسمت وارد می شود.
* <code>$chatId</code>: شناسه گروه مورد نظری که بات به آن افزوده شده است در این قسمت وارد می شود. در ادامه نحوه استخراج این شناسه را خواهیم آموخت. دقت نمائید که شناسه چت هائی که بات در آن حضور دارد یک عدد مثبت می باشد در حالیکه برای گروه ها این عدد منفی می باشد.
* <code>$chatName</code>: نام گروه مورد نظر جهت نمایش در رابط کاربری وب در این قسمت وارد می شود.
* <code>$fetchInterval</code>: بر حسب ثانیه؛ مدت زمانی که بایستی پس از سپری شدن به صورت خودکار آخرین پیام های گروه مجددا از سرور تلگرام بارگزاری شود را تعیین می کند. به صورت پیش فرض این زمان ۲ دقیقه می باشد.

در بخش بعدی نحوه استخراج شناسه گروه را جهت درج در متغیر <code>$chatId</code> خواهیم آموخت.

## نحوه استخراج شناسه گروه

پس از افزودن بات به گروه مورد نظر، می توان از طریق API تلگرام از آخرین پیام هایی که بات دریافت نموده است مطلع شد. شناسه گروه همراه با پیام های دریافتی از طریق API قابل دسترس می باشد. قالب دسترسی به آخرین پیام ها از طریق REST API تلگرام به شرح ذیل می باشد:
{{< highlight plaintext >}}
https://api.telegram.org/bot{HTTP_API_ACCESS_TOKEN}/getUpdates
{{< /highlight >}}

در این قالب، قسمت <code>{HTTP_API_ACCESS_TOKEN}</code> با HTTP API Access Token برای باتی که در این آموزش ساخته ایم یعنی <code>766664963:AAHPXGLPzdGXrtMiqL1bGbQwglhsjDJEafI</code>، جایگزین می شود:

{{< highlight plaintext >}}
https://api.telegram.org/bot766664963:AAHPXGLPzdGXrtMiqL1bGbQwglhsjDJEafI/getUpdates
{{< /highlight >}}

این آدرس را می توان در یک Web Browser مانند Firefox یا Chrome یا هر مرورگر وب دیگری وارد نمود. پاسخ این Query از سرور تلگرام در قالب JSON به شما بازگشت داده خواهد شد:

{{< highlight json >}}
{"ok":true,"result":[]}
{{< /highlight >}}

در صورتی که مانند مثال بالا کلید result به شکل خالی به شما بازگشت داده شد، به این معنی است که Bot هنوز پیامی از سوی تلگرام دریافت ننموده است. لذا نیاز است تا در گروهی که بات را به آن افزوده اید پیامی را ارسال نمائید. اجازه دهید یک پیام Hello, World! را در گروه تلگرام مورد نظر توسط یکی از اعضا ارسال نمائیم و مجددا آدرس فوق را در مرورگر وب خود وارد نمائیم:

{{< highlight json >}}
{"ok":true,"result":[{"update_id":807119542,
"message":{"message_id":2,"from":{"id":61625693,"is_bot":false,"first_name":"Mamadou","username":"NuLL3rr0r"},"chat":{"id":-277738700,"title":"Barandazan","type":"group","all_members_are_administrators":true},"date":1552859599,"text":"Hello, World!"}}]}
{{< /highlight >}}

به نظر می رسد که بات کار می کند! به منظور بهینه سازی مصرف پهنای باند، سرور تلگرام پاسخ های بازگشتی را با از بین بردن فضاهای خالی شامل Space, Tab, NewLine، به اصطلاح Uglify می نماید که خوانائی آن برای انسان را پائین می آورد. خوشبختانه، مرورگر فایرفاکس اطلاعات برگشتی از سرور تلگرام به شکل JSON را تشخیص داده و از طریق یک رابط کاربری مناسب، اطلاعات را در قالبی که برای آدمیزاد خوانا باشد در اختیارتان قرار می دهد:

{{< figure src="/blog/circumvent-telegram-censorship/telegram-api-get-updates-result.png" alt="رابط کاربری فایرفاکس برای اطلاعات JSON با خوانائی بهتر" caption="رابط کاربری فایرفاکس برای اطلاعات JSON با خوانائی بهتر" >}}

اگر به فایرفاکس دسترسی ندارید یا مرورگر شما JSON بازگشتی را به شکل Uglify شده نمایش می دهد می توانید عبارت JSON Beautifier را در موتور جستجوی خود وارد نمائید. با استفاده از ابزارهای رایگان آنلاین جهت Beautify نمودن JSON می توان اطلاعات فوق را به شکل ذیل با خوانائی بیشتر مطالعه نمود:

{{< highlight json >}}
{
  "ok": true,
  "result": [
    {
      "update_id": 807119542,
      "message": {
        "message_id": 2,
        "from": {
          "id": 61625693,
          "is_bot": false,
          "first_name": "Mamadou",
          "username": "NuLL3rr0r"
        },
        "chat": {
          "id": -277738700,
          "title": "Barandazan",
          "type": "group",
          "all_members_are_administrators": true
        },
        "date": 1552859599,
        "text": "Hello, World!"
      }
    }
  ]
}
{{< /highlight >}}

در مثال فوق مقدار <code>.result[0].chat.id</code> یعنی <code>-277738700</code> شناسه گروه مورد نظر ما می باشد. همانطور که قبلا اشاره شد، شناسه گروه های قابل دسترس برای بات یک عدد منفی می باشد در حالیکه برای چت هایی که با بات صورت می گیرد این مقدار یک عدد مثبت می باشد.

مقدار بدست آمده را در مقابل متغیر <code>$chatId</code> در فایل <code>config.php</code> وارد نمائید. به نظر می رسد که همه چیز جهت استفاده از بات آماده باشد.

## نحوه استفاده از رابط کاربری مبتنی بر وب جهت ارسال محتوا به تلگرام توسط بات

بسیار عالی، چنانچه بات جدید را به گروه مورد نظر افزوده باشید و تمامی تنظیمات به درستی انجام شده باشد، پس از مراجعه به آدرس اینترنتی که برای رابط کاربری مبتنی بر وب بات در نظر گرفته اید (در مثال ما <code>https://telegram.babaei.net</code>)، با صفحه ذیل مواجه خواهید شد:

{{< figure src="/blog/circumvent-telegram-censorship/telegram-bot-webui-tools.png" alt="رابط کاربری مبتنی بر وب بات تلگرام" caption="رابط کاربری مبتنی بر وب بات تلگرام" >}}

این رابط کاربری شامل ۳ ابزار می باشد. یکی از این ابزارها به شما قابلیت مشاهده آخرین پیام های موجود در گروه مورد نظرتان را می دهد:

{{< figure src="/blog/circumvent-telegram-censorship/telegram-bot-webui-latest-messages-p1.png" alt="مشاهده آخرین پیام ها با قابلیت پشتیبانی از زبان فارسی، چیدمان راست به چپ و ایموجی" caption="مشاهده آخرین پیام ها با قابلیت پشتیبانی از زبان فارسی، چیدمان راست به چپ و ایموجی" >}}

{{< figure src="/blog/circumvent-telegram-censorship/telegram-bot-webui-latest-messages-p2.png" alt="مشاهده عنوان فایل های مستندات، صوتی و تصویری ارسال شده" caption="مشاهده عنوان فایل های مستندات، صوتی و تصویری ارسال شده" >}}

{{< figure src="/blog/circumvent-telegram-censorship/telegram-bot-webui-latest-messages-p3.png" alt="نمایش پاسخ ها و پیام های فوروارد شده" caption="نمایش پاسخ ها و پیام های فوروارد شده" >}}

همانطور که در تصاویر فوق مشاهده می شود، قابلیت مشاهده تصاویر و پخش فایل های صوتی تصویری یا دریافت مستندات به دلیل نیاز به کد نویسی بیشتر در رابط کاربری تحت وب گنجانده نشده است. علاوه بر آن، مشخص نیست که کدام پاسخ در جواب به کدام پیام بوده است. توجه داشته باشید که این به معنی آن نیست که امکان افزودن این قابلیت ها وجود ندارد؛ بلکه، تمامی اطلاعات مورد نیاز در پاسخ بازگشتی از سوی سرور تلگرام برای افزودن قابلیت های فوق وجود دارد. تنها بایستی زمان بیشتری صرف نموده و این اطلاعات را از JSON بازگشتی استخراج نموده و در رابط کاربری نمایش داد که از حوصله نگارنده خارج بوده است. هر فردی با مختصری دانش برنامه نویسی و صرف زمان مناسب قادر به افزودن ویژگی های فوق خواهد بود.

ابزار بعدی، ابزار ارسال پیام می باشد. با این ابزار قادر به ارسال پیام به گروه مورد نظر به زبان فارسی یا هر زبان دیگری خواهید بود:

{{< figure src="/blog/circumvent-telegram-censorship/telegram-bot-webui-latest-send-message.png" alt="امکان ارسال پیام با قابلیت پشتیبانی از زبان فارسی" caption="امکان ارسال پیام با قابلیت پشتیبانی از زبان فارسی" >}}

پس از ارسال موفقیت آمیز پیام، اعلان ارسال موفقیت آمیز پیام به شما نمایش داده خواهد شد:

{{< figure src="/blog/circumvent-telegram-censorship/telegram-bot-webui-latest-send-message-success.png" alt="اعلان ارسال موفقیت آمیز پیام" caption="اعلان ارسال موفقیت آمیز پیام" >}}

و در نهایت ابزار ارسال فایل مستندات، عکس، صوتی و تصویری با قابلیت درج عنوان به زبان فارسی یا هر زبان دیگر:

{{< figure src="/blog/circumvent-telegram-censorship/telegram-bot-webui-latest-send-video.png" alt="ارسال فایل مستندات، عکس، صوتی و تصویری با قابلیت درج عنوان به زبان فارسی" caption="ارسال فایل مستندات، عکس، صوتی و تصویری با قابلیت درج عنوان به زبان فارسی" >}}

پس از انتخاب نوع فایل، مسیر فایل از هارد کامپیوترتان و درج عنوان، چنانچه فایل با موفقیت ارسال شود با اعلان ذیل مواجه خواهید شد:

{{< figure src="/blog/circumvent-telegram-censorship/telegram-bot-webui-latest-send-video-success.png" alt="اعلان ارسال موفقیت آمیز فایل مستندات، عکس، صوتی و تصویری" caption="اعلان ارسال موفقیت آمیز فایل مستندات، عکس، صوتی و تصویری" >}}

در ادامه نمونه پیام و فایل ارسالی از رابط کاربری مبتنی بر وب توسط بات را درون نرم افزار تلگرام مشاهده می نمائید:

{{< figure src="/blog/circumvent-telegram-censorship/telegram-bot-webui-sent-content.png" alt="نمونه پیام و فایل ارسالی از رابط کاربری مبتنی بر وب توسط بات به تلگرام" caption="نمونه پیام و فایل ارسالی از رابط کاربری مبتنی بر وب توسط بات به تلگرام" >}}

## ایمن سازی رابط کاربری مبتنی بر وب

از آن جائی که رابط کاربری مبتنی بر وب را بر روی وب قرار می دهید هر کسی امکان دسترسی به آن را خواهد داشت. به منظور جلوگیری از این امر، می توانید از ماژول Auth وب سرور خود استفاده نمائید. برای مثال در وب سرور Nginx این ماژول [HTTP Basic authentication یا به اختصار auth_basic](https://docs.nginx.com/nginx/admin-guide/security-controls/configuring-http-basic-authentication/) نام دارد. اگر قصد Authentication, Authorization, and Accounting یا به اختصار AAA (بخوانید Triple A) پیشرفته را دارید می توانید از ماژول [nginx-ldap-auth](https://github.com/nginxinc/nginx-ldap-auth) استفاده نمائید. در انتهای مقاله در قسمت [تنظیمات نمونه nginx برای کاربران پیشرفته](#تنظیمات-نمونه-nginx-برای-کاربران-پیشرفته)، نمونه تنظیمات Nginx جهت استفاده از ماژول auth_basic عرضه شده است.

نکته دیگری که بایستی بدان اشاره نمود عدم استفاده از Plain HTTP (پروتکل http://) می باشد. در این حالت چون داده ها در حالت به اصطلاح Plaintext یا Cleartext به شکل رمزنگاری نشده دریافت و ارسال می شود، هر فرد یا سازمانی (مثلا ISP شما) که میان شما و سرور قرار دارد می تواند تمامی داده های ارسالی یا دریافتی شما از جمله نام کاربری، کلمات عبور، چت ها و غیره را با کمترین زحمت ممکن استخراج و مطالعه کند. بنابراین استفاده از گواهینامه SSL معتبر و پروتکل https:// را فراموش ننمائید. خوشبختانه [Let's Encrypt](https://letsencrypt.org/) امکان دریافت گواهینامه معتبر SSL به شکل کاملا رایگان را فراهم می سازد.

چنانچه قصد عرضه رابط کاربری خود به صورت عمومی جهت استفاده سایرین را دارید، بهتر است از Captcha جهت جلوگیری از اسپم توسط بات های مبتنی بر وب استفاده نمائید. خوشبختانه PHP امکان استفاده از Captcha را به سادگی مهیا می سازد. جهت استفاده از Captcha دو انتخاب عالی وجود دارد:

* [Securimage PHP Captcha](https://www.phpcaptcha.org/documentation/quickstart-guide/) که افزودن آن به اپلیکیشن های PHP بسیار ساده می باشد.
* کتابخانه PHP [Google reCAPTCHA](https://github.com/google/recaptcha) که [امکان افزودن سرویس reCAPTCHA شرکت گوگل را به سادگی](https://developers.google.com/recaptcha/old/docs/php) در اختیار شما قرار می دهد.

## تنظیمات نمونه nginx برای کاربران پیشرفته

در ادامه می توانید نمونه تنظیمات nginx برای کاربران پیشرفته با پشتیبانی از SSL سخت و ایمن تر شده، محافظت در مقابل حملات DDoS، احراز هویت، Static Resource Caching و فشرده سازی جهت بهبود مصرف پهنای باند را مشاهده نمائید.

{{< highlight plaintext >}}
server {
    server_tokens   off;

    listen      443 ssl http2;
    listen      [::]:443 ssl http2;
    server_name telegram.babaei.net;

    error_log   /path/to/telegram.babaei.net-error.log;
    access_log  /path/to/telegram.babaei.net-access.log;

    # Hardened SSL
    ssl                         on;
    ssl_dhparam                 /path/to/ssl-dhparam.pem;
    ssl_protocols               TLSv1 TLSv1.1 TLSv1.2;
    ssl_prefer_server_ciphers   on;
    ssl_ciphers                 "EECDH+AESGCM:EDH+AESGCM:AES256+EECDH:AES256+EDH";
    ssl_ecdh_curve              secp384r1;
    ssl_session_cache           shared:SSL:10m;
    ssl_session_timeout         1h;
    ssl_session_tickets         off;
    ssl_stapling                on;
    ssl_stapling_verify         on;
    resolver                    127.0.0.1 [::1]:5353 valid=300s;
    resolver_timeout            5s;
    # Hardened SSL Headers
    add_header                  Strict-Transport-Security "max-age=31536000; includeSubDomains; preload";
    add_header                  X-Frame-Options SAMEORIGIN;
    add_header                  X-Content-Type-Options nosniff;
    add_header                  X-XSS-Protection "1; mode=block";
    # SSL Certificate
    ssl_certificate             /path/to/ssl-certificate.pem;
    ssl_certificate_key         /path/to/ssl-certificate-key.pem;
    ssl_trusted_certificate     /path/to/ssl-trusted-certificate.pem;

    root            /path/to/telegram-seditious-bot;
    index           index.html index.php;
    fastcgi_index   index.php;

    # Message size limit
    client_max_body_size    50m;
    client_body_buffer_size 128k;

    # Remove the http proxy header to address HTTPoxy vulnerability
    fastcgi_param HTTP_PROXY    "";

    location ~ ^.+\.php$ {
        fastcgi_pass    unix:/path/to/php-fpm.socket;
        fastcgi_param   SCRIPT_FILENAME  /path/to/telegram-seditious-bot$fastcgi_script_name;
        include         fastcgi_params;

        # Remove the http proxy header to address HTTPoxy vulnerability
        fastcgi_param HTTP_PROXY    "";
    }

    # Custom Error Pages
    error_page  400             /custom-error-pages/400.html;
    error_page  401             /custom-error-pages/401.html;
    error_page  403             /custom-error-pages/403.html;
    error_page  404             /custom-error-pages/404.html;
    error_page  500 502 503 504 /custom-error-pages/5xx.html;

    location ^~ /custom-error-pages/ {
        auth_basic  off;
        alias       /path/to/custom-error-pages/;
    }

    # Anti-DDoS
    limit_conn  conn_limit_per_ip           100;
    limit_req   zone=request_limit_per_i    burst=100   nodelay;

    # Compression
    gzip                on;
    gzip_vary           on;
    gzip_http_version   1.1;
    gzip_comp_level     4;
    gzip_min_length     1024;
    gzip_buffers 32     4k;
    gzip_proxied        expired no-cache no-store private auth;
    gzip_types
        text/css
        text/plain
        text/xml
        application/atom+xml
        application/javascript
        application/json
        application/rss+xml
        application/xhtml+xml
        image/svg+xml;

    # Static Resource Caching
    location ~* \.(?:html?|xml|json)$ {
        expires         -1;
        log_not_found   off;
    }
    location ~* \.(?:rss|atom)$ {
        expires         1h;
        log_not_found   off;
        add_header      Pragma public;
        add_header      Cache-Control "public, must-revalidate, proxy-revalidate";
    }
    location ~* \.(?:css|js)$ {
        expires         1M;
        log_not_found   off;
        add_header      Pragma public;
        add_header      Cache-Control "public, must-revalidate, proxy-revalidate";
    }
    location ~* \.(?:png|jpg|jpeg|gif|ico|cur|gz|svgz|mp4|ogg|ogv|webm|htc)$ {
        expires         1y;
        log_not_found   off;
        add_header      Pragma public;
        add_header      Cache-Control "public, must-revalidate, proxy-revalidate";
    }
    location ~* \.(eot|svg|ttf|woff|woff2)$ {
        expires         1y;
        log_not_found   off;
        add_header      Pragma public;
        add_header      Cache-Control "public, must-revalidate, proxy-revalidate";
    }
    # case insensitive browser cache for static files
    # this is the same list as cloudflare plus extras
    location ~* \.(7z|ai|bmp|bz2|class|css|csv|docx?|ejs|eot|eps|flv|gif|gz|html?|ico|jar|jpe?g|js|json|lzh|m4a|m4v|midi?|mov|mp3|mp4|pdf|pict|pls|png|pptx?|ps|psd|rar|rss|rtf|svgz?|swf|tar|tiff?|ttf|txt|wav|webp|woff|xlsx?|zip)$ {
        expires     max;
        add_header  Pragma public;
        add_header  Cache-Control "public, must-revalidate, proxy-revalidate";
    }

    # Authentication
    auth_basic              "Restricted";
    auth_basic_user_file    /path/to/password-file;
}
{{< /highlight >}}

## محدودیت ها، بهبود و ارتقا بات

کد بات عرضه شده در این مقاله صرفا جنبه آموزشی داشته و با حداقل امکانات به عنوان به اصطلاح Proof of Concept عرضه شده است. قطعا امکان افزودن ویژگی ها و قابلیت های زیادی وجود خواهد داشت و به راحتی می توانید آن را برای نیازهای خود سفارشی سازی نمائید. علاوه بر این ها، در حال حاضر بات های تلگرام محدود به ارسال فایل تا حجم حداکثر ۵۰ مگابایت می باشند. این محدودیت توسط تلگرام بر روی بات ها اعمال شده، مگر آنکه از API کلاینت های تلگرام استفاده نمائید که مستلزم نوشتن یک تلگرام مستقل خواهد بود :wink:.
