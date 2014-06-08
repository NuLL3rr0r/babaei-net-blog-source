---
layout: post
title: "Secure File Download"
date: 2007-12-15 00:00
comments: false
sharing: true
footer: true
categories:
- .NET
- .NET Framework
- ASP.NET
- C#
- FreeBSD
- GNU
- HTML
- Linux
- Mono
- Perl
- Security
- Unix
---

### <center>ساخت لینك های دانلود متفاوت برای كاربران سایت</center> ###

#### چكیده ####

در  این مقاله به بررسی و ارائه راهكاری جهت تولید لینك های اختصاصی دانلود فایل برای هر كاربر – آنهم بصورت موقتی و یك بار مصرف – در یك وب سایت می پردازیم. این لینك ها به صورت مستقیم نبوده ولی توسط هر مرورگر یا نرم افزار مدیریت دانلودی قابل دانلود می باشند.

در این مقاله از Perl و ASP.NET بهمراه C# استفاده خواهیم نمود. دلیل این انتخاب تسلط نگارنده بر زبان های فوق می باشد.

بدیهی است این مفاهیم در اكثر زبان های تحت سرور یكسان بوده و برای انتقال كد به سایر زبان ها كافی است با مفاهیم كار با فایل ها و تنظیم پاسخ های سرور به مرورگر یا كلاینت آشنائی داشته باشید.
 
<!-- more -->

<div style="font-style: oblique;">
<br />
هشدار!!
<br />
به جهت تسهیل فرآیند آموزش، نکته امنیتی مهمی در نگارش کدهای تشریح شده در این مقاله رعایت نشده است. بنابراین، یک نفوذگر ماهر اجازه دریافت فایل های حساس داخل سرور را خواهد داشت. به عنوان راهکار، در انتهای مقاله و در فایل سورس کامل، نسخه ای امن از کد Perl گنجانده شده است. امن نمودن کد ASP.NET بر اساس نمونه کد Perl به عهده مخاطب گذاره شده است.
<br /><br /><br />
</div>

#### مقدمه ####

اگر در حال توسعه نوعی از سیستم های تجارت الكترونیك می باشید كه فایل های قابل دانلود عرضه می كنند، ممكن است با این مسئله مواجه شده باشید: "چگونه می توانم در مقابل سرقت از فایل هایم مراقبت نمایم؟". اغلب مسئله مربوط به پرداخت مبلغی نمی باشد. برای مثال سایت های بسیاری فایل های مفید را به صورت رایگان عرضه می نمایند. تنها چیزی كه آن ها می خواهند این است كه فرد دانلود كننده ی فایل، برخی مشخصات فردی را وارد نموده یا فرمی را جهت بایگانی و اطلاع مدیر سایت پر نمایند. چنین مواقعی عموما مردم نمی خواهند این كار را انجام دهند و آن ها راهی را جهت دور زدن امنیت وب سرور طلب می نمایند.

در این سناریو مسئله اصلی اینست كه، در واقع هیچ تفاوتی نمی كند كه شما چگونه به آن بنگرید. در نهایت شما لینكی از فایل قابل دانلود را در اختیار كاربران قرار خواهید داد. زمانی كه شخصی لینك دانلود را بدست آورد او می تواند آن را به دوستان یا همكارانش ارائه نماید، پس از آن هر كسی بسادگی می تواند تمام ویژگی ها و خصوصیات امنیتی ایجاد شده توسط شما را دور زده و اقدام به دانلود مستقیم فایل نماید. اگر كاربری از لینك نهائی فایل قابل دانلود آگاهی داشته باشد هیچ یك از ویژگی های امنیتی كه شما در نظر گرفته اید ارزشی نخواهد داشت. به شخصه سایت هائی را دیده ام كه اقدامات قابل توجهی جهت مخفی نمودن لینك دانلود انجام داده اند (شامل ماسك كردن لینك دانلود توسط نمایش متنی در ناحیه وضعیت مرورگر در زمانی كه كاربری بر روی لینك اشاره می نماید). View Source یا خاموش نمودن اجرای جاوا اسكریپت در مرورگر تمام پیشگیری های امنیتی شما را دور خواهد زد.

مسئله بر این حقیقت استوار است كه فایل قابل دانلود شما (خواه یك فایل .pdf، .doc، .zip یا حتی یك فایل .exe باشد) راهی برای تصمیم گیری در مورد بكار انداختن یا نیانداختن خود ندارد. شما نمی توانید استدلالی را در این نوع فایل ها جهت عرضه یا عدم عرضه ی خودشان در هر حالتی را بیافزائید.

یكی از راه های جایگزین این است كه امنیت سیستمی را برای پوشه ای كه فایل ها یتان در آن قرار دارند در نظر بگیرید. به هر حال این راه حل پذیرفتی نیست، چرا كه شما نیاز خواهید داشت برای هر ثبت نام، یك حساب كاربری سیستم (یا ویندوز) را تعریف نمائید؛ سپس برای هر كاربر، نام كاربری و كلمه ی عبورش را ارسال نمائید. آنگاه، پس از یك بار دانلود فایل توسط كاربران اقدام به حذف حساب كاربری آن ها نمائید. این راه حل برای مدیران سرورها مانند یك كابوس است (چرا كه باعث هموار شدن انتشار مشكلات و مسائل امنیتی بزرگتری خواهند شد). و اگر شما سایت تان را بر روی یك ISP دیگر میزبانی می نمائید، بسیار دور از انتظار خواهد بود كه آن ها به شما اجازه ی ساخت و یا حذف حساب های كاربری را بر روی سیستم شان بدهند.

راه حل ساده ای كه در ادامه می آید به شما اجازه خواهد داد تا اقدام به مسدود نمودن این حفره امنیتی با ذخیره نمودن فایل قابل دانلود در خارج از وب سایت نمائید و سپس آن فایل را مستقیما از صفحه ی وب بكار گیرید. به عبارت دیگر، شما به فایل MyFileServer.aspx لینك می دهید و فایل MyPdfDownload.pdf را دریافت می كنید، برای مثال، بدون هیچ گونه لینك واقعی به MyPdfDownload.pdf، آن را از هرجای وب سایت تان كه خواستید قابل عرضه سازید.

#### تشریح كدها ####

استفاده از كدها بسیار راحت می باشد. دقت نمائید كه تمامی فایل های پروژه در پوشه ی SecureFileDownload قرار دارد[^1] – هم كدهای مربوط به Perl و هم كدهای مربوط به ASP.NET – كه خود شامل چهار پوشه به شرح ذیل می باشد:

- پوشه ی cgi-lib جهت ماژول های Perl كه در برنامه از آن ها استفاده شده است.
- پوشه ی files جهت نگهداری فایل های قابل دانلود
- پوشه ی list جهت ثبت كد شناسائی مربوط به كاربران
- پوشه ی www كه كدهای Perl و ASP.NET در آن جا قرار گرفته است تا در URL قابل آدرس دهی باشند.

دقت نمائید كه كد Perl به صورت 99% با سرور های UNIX و یا Linux هماهنگ می باشد [احتمالا نیازمند تغییر كوچكی در تابع ارسال ایمیل برای معرفی نرم افزار مربوط به ارسال ایمیل در سرور می باشد]، البته جهت هماهنگی آن با سرورهای Windows نیاز به تغییر كامل كد تابع مربوط به ارسال ایمیل می باشد. همچنین كد ASP.NET بدون هیچ مشكلی در سرورهای Windows و سایر سرورها مانند Unix یا Mac OS X، Linux و Solaris كه Mono[^2]  بر روی آن ها نصب باشد اجرا خواهد شد. سرور های ویندوز نیازمند .NET Framework 2.0 می باشند، چنانچه از نسخ پائین تر آن استفاده می نمائید بایستی تغییراتی در تابع ارسال ایمیل ایجاد كنید.

گفتیم كه پوشه ی SecureFileDownload شامل چهار پوشه می باشد. دقت نمائید كه پوشه ی www كه در پوشه ی SecureFileDownload قرار دارد پوشه ی root می باشد نه خود SecureFileDownload. در واقع در وب سرور شما نیازی به پوشه ی SecureFileDownload ندارید و احتمالا نام پوشه ی root در وب سرور با نام www نیز متفاوت می باشد (پوشه ی root پوشه ای است كه نام فایل های آن پس از URL سایت شما قرار گرفته و قابل دانلود می باشند برای مثال در Plesk نام این پوشه httpdocs و در CPanel نام آن www می باشد). در حالت local چه برای اجرای كد Perl و چه برای اجرای كد ASP.NET بایستی در نرم افزار وب سرور پوشه www به عنوان یك Application یا Virtual Directory معرفی شده باشد در غیر اینصورت به دلیل اشتباه در مسیر دهی نسبی باعث دریافت خطاهای مربوط به كار با پوشه ها و فایل ها خواهد شد.

همچنین كد Perl به همراه پوشه های cgi-lib، files و list بایستی داری Permissions شماره 755  در سرورهای UNIX یا Linux باشد. برای سرورهای ویندوز بایستی پوشه های cgi-lib، files و lib برای كاربر Everyone دارای Full Control Permissions باشند.

در پایان به عنوان یك نكته ی حساس در نظر داشته باشید كه كاراكتر انتهای خطوط در فایل های متنی در Windows با Unix و Linux، همچنین Mac متفاوت می باشد. در صورتی كه كد Perl شما در Windows نوشته شده است و در Unix یا Linux اقدام به اجرای آن نمائید معمولا به دلیل مورد ذكر شده با خطا مواجه خواهید شد. برای جلوگیری از این امر كافی است از نرم افزارهائی مانند Dreamweaver[^3] و یا TextPad كه قابلیت ذخیره فایل برای انواع سیستم عامل را دارند استفاده نمائید. چنانچه از CPanel استفاده می نمائید كافی است یكبار فایل را در File Manager / Editor  باز نموده و مجددا ذخیره نمائید.

در نهایت دقت نمائید كه پوشه www، وب سایت ما محسوب شده و سایر پوشه ها به همراه فایل قابل دانلود خارج از وب سایت – یعنی همان پوشه www –  قرار دارند. و قرار است به جای آدرس مستقیم به فایل قابل دانلود (به دلیل اینكه خارج از وب سایت است قابل آدرس دهی در پروتكل HTTP نیست) به فایل Perl یا ASP.NET آدرس می دهیم و در نهایت آن ها مانند یك فایل قابل دانلود عمل می نمایند.

#### درك عملكرد پروژه ####

بسیار خب، پیش از تشریح سایر كدها بهتر است یك بار اقدام به آزمایش كلی كدها و پروژه نمائید. برای این منظور با توجه به موارد ذكر شده در قسمت قبل اقدام به تست پروژه در حالت local و یا در وب سرور نمائید.

ابتدا به صفحه ی securedown.html مراجعه نمائید. در این صفحه شما با دو فرم مواجه خواهید شد كه به شما اعلام می نمایند جهت دریافت فایلی تحت عنوان test.zip ناگزیر به وارد نمودن آدرس ایمیل خود می باشید– یك فرم برای كار با كد Perl و دیگری برای كار با كد ASP.NET – . تفاوتی نخواهد داشت كه كدام فرم را انتخاب نمائید. در حال حاضر شما به عنوان كاربر جهت دریافت فایل كافیست دو مرحله را سپری نمائید:

1.	وارد نمودن آدرس ایمیل خود در یكی از فرم ها و زدن كلید Enter
2.	وارد شدن به ایمیل تان و سپس كلیك بر روی لینك دانلود.

البته در حال حاضر احتمالا قادر به تست پروژه نمی باشید چرا كه نیازمند اعمال تغییرات كوچكی در كدها می باشید. این تغییرات در ادامه ذكر خواهند شد.

#### تشریح كد HTML ####

در كد HTML دو تگ Form وجود دارد كه از آنها برای ارسال اطلاعات ورودی كاربر به سرور استفاده می شود. از فرم اول جهت ارسال اطلاعات به اسكریپت securedown.pl و از فرم دوم برای ارسال اطلاعات به اسكریپت securedown.aspx استفاده می شود.

{% codeblock lang:html %}
<form action="securedown.pl" method="get">
    <input type="hidden" name="filename" value="test.zip" />
    Email: <input type="text" name="mail" />
    &nbsp;<input type="submit" value="Download" /><br /><br />
</form>
<form action="securedown.aspx" method="get">
    <input type="hidden" name="filename" value="test.zip" />
    Email: <input type="text" name="mail" />
    &nbsp;<input type="submit" value="Download" /><br /><br />
</form>
{% endcodeblock %}

در اینجا دو نكته ی كلیدی نهفته است كه لازم است بدان اشاره شود. مورد اول اینكه برای هر ورودی به سرور بایستی همان نامی كه در سرور در نظر گرفته شده است در تگ های input نیز به كار گرفته شود. برای مثال filename و mail هم در كد Perl - param(‘filename’) -  و هم در كد ASP.NET  - Request.QueryString[“filename”] -  به همان نام به كار گرفته شده اند. دوم اینكه ما نمی خواهیم كاربر در انتخاب نام فایل مورد نظر جهت ارسال به سرور نقشی داشته باشد. اما، به هر جهت بایستی نام فایل مورد نظر همراه با ایمیل كاربر به سرور ارسال شود. به منظور حل این مسئله كافیست نوع فیلد input برای filename از نوع hidden انتخاب شود. بنابراین دیگر كاربر قادر به مشاهده مقدار filename و تغییر آن در صفحه نخواهد بود و بدون توجه به این موضوع، خود باعث ارسال آن به سرور خواهد بود.

#### تشریح كد Perl ####

در ابتدا با درج Shebang line مفسر Perl را معرفی نموده سپس در اولین خط برنامه خود را مستلزم تعریف متغیرها قبل از استفاده از آن ها می نمائیم. در نهایت اقدام به فراخوانی ماژول CGI.pm می نمائیم و پس از آن به مفسر اجازه نمایش خطاها در مرورگر را خواهیم داد.

{% codeblock lang:perl %}
/!#usr/bin/perl
use strict;
use CGI ':standard';
use CGI::Carp 'fatalsToBrowser';
{% endcodeblock %}

سپس به دلیل اینكه قصد استفاده از ماژول های غیر استاندارد Perl را داریم به مفسر اعلان می كنیم كه از پوشه ی cgi-lib جهت یافتن ماژول های غیر استاندارد استفاده نماید. آنگاه ماژول های مربوطه را معرفی می نمائیم. هدف استفاده از این ماژول ها تولید یك رشته تصادفی می باشد.

{% codeblock lang:perl %}
use lib "../cgi-lib";
use String;
use String::Random;
{% endcodeblock %}

سپس اقدام به جمع آوری داده های رسیده از فرم HTML توسط تابع param و اختصاص آن به متغیرهای مربوطه می نمائیم. این پارامترها شامل نام فایل قابل دانلود، آدرس ایمیل كاربر و كد شناسائی او می باشد. در خطوط بعدی متغیری برای نگهداری مسیر نسبی فایل قابل دانلود كه در پوشه files می باشد و متغیر دیگری جهت دستیابی به لیست كدهای كاربری كه در یك فایل متنی با نام list.txt در پوشه ی list قرار دارد تعریف می كنیم. در پایان متغیری كه نوع MIME[^4] سند را به مرورگر معرفی می نماید به كار خواهیم گرفت. دقت نمائید كه حتما قبل از چاپ هر گونه مقداری در مرورگر بایستی مقدار این متغیر یك بار جهت اعلان نوع سند چاپ شود.

{% codeblock lang:perl %}
my $fileName = param('filename');
my $mail = param('mail');
my $uid = param('uid');
my $filePath = "../files/" . $fileName;
my $regList = "../list/list.txt";
my $httpHeader = "Content-Type: text/html; charset=utf-8\n\n";
{% endcodeblock %}

در مرحله ی بعد از صحت داده های ورودی از طرف كاربر اطمینان حاصل می نمائیم. این عمل را به منظور جلوگیری از حملات XSS توسط هكرها انجام می دهیم. چنانچه هر نوع حمله ای از این نوع انجام شود، فرد خاطی با پیام " Alice is not in Wonderland." مواجه خواهد شد و برنامه از كار باز خواهد ایستاد. این عمل با استفاده از تابع دست ساز FoundXSS[^5] كه در انتهای برنامه قرار دارد میسر خواهد شد.

{% codeblock lang:perl %}
if (FoundXSS($fileName)) {
    print $httpHeader;
    print qq(<br /><center><h3>Alice is not in Wonderland.</h3></center>);
    exit;
}
{% endcodeblock %}

دقت نمائید كه صفحه ی Perl ما بایستی دو بار اجرا شود:
1.	دریافت نام فایل و ایمیل كاربر و تولید كد شناسائی و ثبت آن درlist.txt. سپس ارسال لینك دانلود به آدرس ایمیل او.
2.	دریافت نام فایل و كد شناسائی كاربر سپس در صورت معتبر بودن ارائه فایل به او.
در ابتدای برنامه سه متغیر برای جمع آوری اطلاعات تعریف نمودیم. در مرحله اول به مقادیر متغیر های $filename و $mail و در مرحله بعد به مقادیر متغیرهای $fileName و $uid نیاز داریم.

ادامه برنامه در شرط سه مرحله ای كه در ذیل می آید تداوم پیدا می كند:

{% codeblock lang:perl %}
if ($fileName ne '' and $mail ne '') {
    #step 1
}
elsif ($fileName ne '' and $uid ne '') {
    #step 2
}
else {
    #Error parsing parameters
}
{% endcodeblock %}

در صورتی كه متغیرهای $fileName و $mail دارای مقدار باشد متوجه مرحله ی اول خواهیم بود – دقت كنید كه در صورت برقراری شرط دیگر مقدار متغیر uid در روند برنامه تاثیر گذار نخواهد بود؛ بنابراین از چك كردن مقدار آن صرف نظر خواهیم نمود – چنانچه خلاف این امر واقع بود مقادیر متغیرهای $fileName و $uid را چك می نمائیم. اگر هر دو دارای مقدار باشند آنگاه مرحله ی دوم اتفاق خواهد افتاد – همان وضعیت قبلی در این جا برای $mail برقرار است –. و چنانچه هیچ كدام از شروط رخ نداد قطعا تركیب مقادیر ورودی نامعتبر می باشد و كاربر از این امر مطلع خواهد شد سپس برنامه پایان خواهد یافت.

#### شرح مرحله اول ####

ابتدا نوع اعلان سند در مرورگر را HTML تعیین می كنیم.

{% codeblock lang:perl %}
print $httpHeader;
{% endcodeblock %}

سپس  با شرط دو مرحله ای زیر روبرو می شویم:

{% codeblock lang:perl %}
if (-e $filePath) {
    .
    .
    .
}
else {
    #The server can’t find the file
}
{% endcodeblock %}

ابتدا صحت موجودیت فایل مورد نظر كاربر را در شاخه ی files سرور بررسی می نمائیم. سپس اگر وجود فایل تائید شد برنامه ادامه پیدا می كند. در غیر اینصورت كاربر با پیامی متوجه موضوع می شود و برنامه خاتمه می یابد.

در ادامه فایل مربوط به كدهای شناسائی كه همان list.txt می باشد را باز می نمائیم و تمام خطوط فایل را می خوانیم و در آرایه @lines می ریزیم. چنانچه خطائی رخ دهد با تابع Error كاربر را مطلع می نمائیم و از برنامه خارج می شویم. در ادامه فایل را می بندیم. دقت نمائید كه چنانچه چندین كاربر به صورت همزمان قصد دسترسی به یك فایل را داشته باشند مسائلی كه باعث بروز خطا خواهد شد بروز می نماید بنابراین با تابع flock در حالتی كه فایل را می خوانیم با مقدار 1 در حالت اشتراكی و در زمان نوشتن با مقدار 2 در حالت انحصاری قرار می گیریم.

{% codeblock lang:perl %}
open (REG, "<:utf8", $regList) || Error ("find", "the registeration information");
flock (REG, 1);
my @lines = <REG>;
close(REG);
{% endcodeblock %}

سپس با تابع join تمامی خانه های آرایه را جهت بررسی در متغیر اسكالر $list می ریزیم. آنگاه وارد حلقه ای نامتناهی خواهیم شد. سپس متغیر $uid را برابر مقدار بازگشتی از تابع دست ساز UidGen قرار می دهیم. از این تابع جهت تولید رشته ای تصادفی به طول x كه در اینجا 30 فرض شده است استفاده می كنیم. این رشته تصادفی كد شناسائی كاربر خواهد بود. در ادامه درون متغیر $list كه شامل لیست كد شناسائی سایر كاربران خواهد بود به دنبال كد شناسائی تولید شده در مرحله قبل جستجو می نمائیم. این امر به این دلیل صورت می گیرد تا از وجود كدهای شناسائی تكراری جلوگیری شود – هر چند این احتمال بسیار ناچیز است –. در پایان چنانچه مورد تكراری وجود نداشت به اجرای حلقه خاتمه می دهیم.

{% codeblock lang:perl %}
my $list = join("", @lines);
while (1) {
    $uid = UidGen(30);
    my $isDup = $list =~ m/$uid/;
    if ($isDup == 0) {
        last;
    }
}
{% endcodeblock %}

در ادامه فایل list.txt كه شامل لیست كدهای شناسائی است را در حالت append و انحصاری باز نموده كد شناسائی جدید را به انتهای فایل به همراه یك كاراكتر خط جدید اضافه نموده و فایل را می بندیم.

{% codeblock lang:perl %}
open (REG, ">>:utf8", $regList) || Error ("register", "your mail address");
flock (REG, 2);
print REG qq($uid\n);
close (REG);
{% endcodeblock %}

سپس لینك دانلود جدید ویژه ی كاربر جاری را به سبك زیر تولید می نمائیم.

<div style="direction: ltr; text-align: left;">
<pre>
http://www.نام دامین مورد نظر شما.دامنه/securedown.pl?filename=نام فایل مورد نظر&uid=كد شناسائی كاربر
</pre>
</div>

{% codeblock lang:perl %}
my $link = qq(http://www.somedomain.com/securedown.pl?filename=$fileName&uid=$uid);
{% endcodeblock %}

در نهایت با استفاده از تابع دست ساز SendMail لینك دانلود را به آدرس ایمیل كاربر ارسال می كنیم و پیغامی با این مضمون كه لینك دانلود به آدرس شما ارسال شده است را چاپ می نمائیم. دقت نمائید كه در qq("Your Name" <someid\@somedomain.com>)  و جود علامت \ قبل از@ ضروری می باشد. در این  جا مرحله اول خاتمه می یابد و اجرائی شدن مرحله دوم منوط به پیگیری كاربر می باشد.

{% codeblock lang:perl %}
SendMail($mail, qq("Your Name" <someid\@somedomain.com>), "Download Link", qq(<strong>Download Link:<strong><br/>$link));
print qq(<br /><center><h3>Thanks for your registration<br/>The download link sent to your inbox<br/>Just follow it...</h3></center>);
exit;
{% endcodeblock %}

#### شرح مرحله دوم ####

بسیار خب. فرض می كنیم كاربر وارد ایمیل خود شده است و بر روی آدرس دانلود كلیك نموده است. اكنون نوبت قسمت دوم برنامه است تا وارد عمل شود.

قبل از اینكه به تشریح ادامه كد بپردازیم بایستی مطلبی را خاطر نشان شویم و آن این است كه هر فایلی كه در مرورگر به نمایش در می آید دارای یك نوع MIME می باشد. این دقیقا همان چیزی است كه ما بدان نیاز داریم. برای مثال ما متغیری به عنوان $httpHeader در ابتدای برنامه با مقدار زیر تعریف نمودیم. 

{% codeblock lang:perl %}
Content-Type: text/html; charset=utf-8\n\n
{% endcodeblock %}

سپس پیش از نمایش هرگونه پیامی در مرورگر اقدام به چاپ مقدار متغیر می نمودیم تا مرورگر متوجه شود كه قرار است یك صفحه HTML را نمایش دهد. سپس اقدام به چاپ نمودن متون و تگ های HTML می نمودیم.

شاید تا به حال با صفحات وبی برخورد كرده باشید كه به جای نمایش هرگونه اطلاعاتی یك تصویر یا فایل pdf و ... را به شما نمایش دهند. برای مثال:

<div style="direction: ltr; text-align: left;">
<pre>
http://www.somedomain.com/showpic.aspx?id=zUm/.t13v43
</pre>
</div>

كه به جای نمایش هرگونه صفحه ی وب به شما یك تصویر را نمایش می دهد. برنامه نویس این صفحه به جای اینكه نوع MIME را text/html قرار دهد ممكن است آن را چیزی مانند image/jpeg و یا application/pdf در نظر بگیرد.[^6]

بسیار خب آن چه كه ما نیاز داریم این است:

{% codeblock lang:perl %}
print qq(Content-Disposition: attachment; filename="نام فایل");
print qq(Content-Type: application/octet-stream\n\n);
{% endcodeblock %}

و اما آغاز مرحله ی دوم با خواندن فایل list.txt و قرار دادن خطوط فایل در آرایه @lines همراه است. در این مرحله جهت نمایش پیغام های خطا از تابع دست ساز ErrorH به جای Error استفاده شده است؛ دلیل آن در ادامه تشریح خواهد شد.

{% codeblock lang:perl %}
open (REG, "<:utf8", $regList) || ErrorH ("find", "the registeration information");
flock (REG, 1);
my @lines = <REG>;
close(REG);
{% endcodeblock %}

سپس به بررسی تمامی خطوطی كه درون آرایه @lines ذخیره شده اند و مقایسه آن با $uid خواهیم پرداخت تا از صحت ثبت نام كاربر مطمئن شویم.

{% codeblock lang:perl %}
my $isReg = 0;
foreach (@lines) {
    if ($_ =~ m/$uid/) {
        $isReg = 1;
        last;
    }
}
if (!$isReg) {
    print $httpHeader;
    print qq(<br /><center><h3>You're not registered</h3></center>);
    exit;
}
{% endcodeblock %}

در ادامه صحت وجود فایل را تعیین می نمائیم.

{% codeblock lang:perl %}
if (-e $filePath) {
    .
    .
    .
}
else {
    ErrorH('find', $fileName);
}
{% endcodeblock %}

پس از تائید، فایل مورد نظر كاربر را باز نموده و با استفاده از تابع binmode() خروجی را به صورت باینری جهت خواندن تنظیم می نمائیم.

{% codeblock lang:perl %}
open (FILE, $filePath) || ErrorH ("open", "$fileName");
flock (FILE, 1);
binmode(FILE);
binmode(STDOUT);
{% endcodeblock %}

سپس اقدام به تنظیم نوع سند برای مرورگر یا نرم افزار مدیریت دانلود نموده ایم.

{% codeblock lang:perl %}
my $cgi = new CGI;
print $cgi->header( -type => 'application/octet-stream', -attachment => qq($fileName) );
{% endcodeblock %}

البته می توانید از روش جایگزین زیر استفاده نمائید.

{% codeblock lang:perl %}
print qq(Content-Disposition: attachment; filename="$fileName ");
print qq(Content-Type: application/octet-stream\n\n);
{% endcodeblock %}

دقت كنید كه میزان سازگاری روش اول بسیار بیشتر می باشد.

در نهایت متغیری با نام $buffer جهت نگهداری محتویات فایل در حافظه ساخته ایم. سپس با استفاده از یك حلقه در هربار اجرای حلقه 100KB از فایل را خوانده و به سمت كلاینت ارسال می كنیم. و این عمل تا آخرین بایت ادامه می یابد.

{% codeblock lang:perl %}
my $buffer;
while (read(FILE, $buffer, 100 * 2**10)) {
    print STDOUT $buffer;
}
close(FILE);
{% endcodeblock %}

سرانجام اقدام به باز نمودن فایل list.txt در حالت رونویسی نموده ایم. هدف از این عمل خذف كد شناسائی كاربر می باشد چرا كه دیگر با وجود دریافت فایل توسط كاربر نیازی به كد شناسائی نمی باشد. این عمل باعث می شود تا لینك دانلود حالت یك بار مصرف به خود گرفته و هر كاربر را مجبور به ثبت نام نماید. دقت كنید كه پس از آن كه فایل توسط كاربر دریافت شد مقابل تابع open() هیچ نوع دستوری برای مواجه با خطا قرار نگرفته است چرا كه در صورت بروز خطا باعث خرابی فایل دریافت شده توسط كاربر می شود.

{% codeblock lang:perl %}
open (REG, ">:utf8", $regList);
flock (REG, 2);
foreach(@lines) {
    $_ =~ s/$uid\n//;
    print REG $_;
}
close (REG);
{% endcodeblock %}

بسیار خوب تبریك می گوئیم، فایل توسط كاربر دریافت شد بدون اینكه روشی برای دور زدن آن وجود داشته باشد – البته فراموش نفرمائید كه كاربر گرامی هم اكنون فایل مورد نظر را در اختیار دارند و امكان به اشتراك گذاشتن فایل با دیگران را دارند –.

#### تشریح توابع دست ساز ####

در این قسمت به اختصار عملكرد توابع دست ساز مورد استفاده در برنامه كه در انتهای كد آمده اند مورد تشریح قرار می گیرد. بدیهی است تشریح كد توابع در این مقاله نمی گنجد.

FoundXSS(): از این تابع جهت بررسی حملات XSS استفاده می شود و وجود آن ضروری می باشد. البته این تابع بسیار ابتدائی است، اما در اكثر موارد جوابگو است.
شكل كلی:

{% codeblock lang:perl %}
FoundXSS(var1, var2, …);
{% endcodeblock %}

مقادیر بازگشتی:

- 1: در صورت تائید وجود حمله
- 0: در صورت سالم و بی خطر بودن مقادیر ورودی

UidGen(): از این تابع جهت تولید رشته ای تصادفی با طول مورد نظر استفاده می شود.
شكل كلی:

{% codeblock lang:perl %}
UidGen(Length);
{% endcodeblock %}

مقدار بازگشتی: رشته ای به طول پارامتر Length

SendMail(): این تابع جهت ارسال لینك دانلود به آدرس ایمیل كاربر به كار می رود. دقت نماید با توجه به تنظیمات وب سرور شما ممكن است این كد نیاز به تغییراتی داشته باشد. برای مثال اگر از سرور ویندوز استفاده نمائید بایستی كد این تابع تماما تغییر نماید. چنانچه از سایر سرورها استفاده می نمائید بایستی مسیر نرم افزار ارسال ایمیل را در كد تابع، در خط زیر تعیین نمائید.

فرم فعلی:

{% codeblock lang:perl %}
open (MAIL, "|/usr/lib/sendmail -t") || Error('open', 'mail program');
{% endcodeblock %}

تغییر به شكل:

{% codeblock lang:perl %}
open (MAIL, "|Path/to/sendmail -t") || Error('open', 'mail program');
{% endcodeblock %}

شكل كلی:

{% codeblock lang:perl %}
SendMail(to, from, subject, body);
{% endcodeblock %}

مقادیر بازگشتی:

- 1: در صورت ارسال موفقیت آمیز پیام
- 0: در صورت بروز خطا

شرح پارامترها:

مقدار پارامتر from می تواند به شكل yourid@somedomain.com و یا به شكل “Your Name” <yourid@somedomain.com> باشد. همچنین پارامتر body می تواند به صورت متن ساده یا كدهای HTML ارسال شود.

Error(): از این تابع برای نمایش پیغام های خطا و خروج از برنامه استفاده می شود.

شكل كلی:

{% codeblock lang:perl %}
Error('act', 'object')
{% endcodeblock %}

<div style="direction: ltr; text-align: left;">
<pre>
Result: The server can't <strike>act</strike> the <strike>object</strike>: <strike>Cause</strike>.
</pre>
</div>

مثال:

{% codeblock lang:perl %}
Error('open', 'mail program');
{% endcodeblock %}

<div style="direction: ltr; text-align: left;">
<pre>
Result: The server can't <strike>open</strike> the <strike>mail program</strike>: <strike>The system cannot find the path specified</strike>.
</pre>
</div>

ErrorH(): این تابع همانند تابع Error() عمل می نمایند با این تفاوت كه ابتدا اقدام به معرفی نوع سند خروجی به مرورگر می نماید. در واقع HTTP Header را تنظیم می نماید سپس پیغام خطا را نمایش می دهد.

#### تشریح كد ASP.NET ####

تشریح كامل كد ASP.NET در اینجا میسر نمی باشد، به این دلیل كه مفاهیم كاملا یكسان می باشد و شما در صورت آشنائی مختصری با دنیای .NET قطعا قادر به استفاده از آن خواهید بود. در ادامه فقط به بررسی تفاوت ها و شرح نكات كلیدی خواهیم پرداخت.

برای اجرای كد ASP.NET اولین چیزی كه بایستی بدان توجه نمائید این است كه كدهای ASP.NET می توانند لابلای كدهای HTML یا در یك فایل كناری بصورت جداگانه درج شوند. كه روش دوم معمولا جهت انجام پروژه های بزرگ و یا به همراه استفاده از Visual Studio كاربرد دارد. ما از روش اول به دلیل احتیاج كمتر به یكسری ملزومات خاص استفاده می نمائیم. چنانچه روش دوم را می پسندید تنها كاری كه انجام می دهید منتقل نمودن كدهای میان علائم &lt;% %&gt; به رخداد Page_Load() صفحه خواهد بود. البته بدیهی است اعلان نوع صفحه در خط آغازین و تگ &lt;script&gt; نیز حذف خواهند شد. همچنین بجای Import Namespace از using استفاده می نمائید.

دقت نمائید كه در Perl با استفاده از تابع param اقدام به جمع آوری اطلاعات فرم می نمودیم اما در اینجا از Request.QueryString[“Form Variable”] بدین منظور استفاده می كنیم. برای مثال:

{% codeblock lang:csharp %}
string fileName = Request.QueryString["filename"];
{% endcodeblock %}

همچنین در Perl‌ از مسیر دهی نسبی[^7] استفاده می كنیم. در ASP.NET بهتر است با روش مسیر دهی مطلق[^8] كار كنیم. از آنجا كه نمی دانیم مقصد نهائی كدهای ما در سرور كجاست، توسط كدنویسی اقدام به یافتن مسیر جاری سرور می كنیم و در نهایت چك می كنیم مسیر به علامت \ ختم شده است یا نه، اگر به علامت \ ختم نشده بود این علامت جهت استفاده های بعدی اضافه می گردد.

{% codeblock lang:csharp %}
string path = Server.MapPath("~");
path += path.EndsWith("\\") ? string.Empty : "\\";
{% endcodeblock %}

می تواند به شكل زیر باشد:

{% codeblock lang:csharp %}
string path = Server.MapPath("~");
path += path.EndsWith(@"\") ? string.Empty : @"\";
{% endcodeblock %}

در نهایت با اجرای خط بعدی از برنامه آدرس پوشه بالاتر نیز یافت می شود:

{% codeblock lang:csharp %}
string parent = path.Substring(0, path.LastIndexOf("\\", path.Length - 2) + 1);
{% endcodeblock %}

در حال حاضر شما به هیچ وجه قادر به استفاده از كد نمی باشید. مگر اینكه كد مربوط به تابع SendMail() را ویرایش نمائید. دقت نمائید در كلاس های پیش فرض .NET برای ارسال ایمیل ناگزیر به معرفی یك سرور SMTP خواهید بود. بدلیل اینكه این سرورها از شما طلب نام كاربری و كلمه ی عبور می نمایند عملا قادر به استفاده از سرورهای SMTP دیگران نخواهید بود – یكی از این دلایل جلوگیری از مسائل مربوط به Spamming می باشد – البته معمولا با خرید هاست به شما یك سرور SMTP نیز ارائه خواهد شد. در هر صورت بدلیل سعی در یكپارچگی و قابل جا جائی نمودن كدها از account های سرویس مشهور Gmail[^9] استفاده می نمائیم.  این سرویس به شما اجازه ارسال ایمیل با استفاده از سرور SMTP خود را به شرط داشتن یك Google Account كه سرویس Gmail برای آن در دسترس باشد خواهد داد. با مراجعه به وب سایت Gmail می توانید از مزایای آن برخوردار شوید.

بسیار خوب توابع ما در كد ASP.NET میان تگ های زیر قرار دارد:

{% codeblock lang:csharp %}
<script type="text/C#" runat="server">
    // Functions Go Here 
</script>
{% endcodeblock %}

كد مربوط به تابع SendMail() را بیابید. سپس به دنبال قطعه كد زیر جستجو كنید:

{% codeblock lang:csharp %}
smtp.Credentials = new System.Net.NetworkCredential("some.id@gmail.com", "pw");
{% endcodeblock %}

كافیست به جای some.id@gmail.com آدرس ایمیل Gmail تان را وارد نموده و به جای pw كلمه ی عبور آن را وارد نمائید. تبریك می گوئیم؛ در حال حاضر كد كاملا قابل استفاده است. در ضمن این روش این مزیت را دارد كه نسخه ای از نامه ی ارسالی در لیست نامه های ارسالی Gmail قرار خواهد گرفت. از این مورد می توان جهت گزارش گیری بهره برد.

چنانچه از .NET نگارش 1.0  و یا 1.1 استفاده می نمائید، مجبور به تغییر كامل كد این تابع می باشید. و به دنبال آن به جای Namespace، System.Net.Mail بایستی از System.Web.Mail استفاده نمائید.

سایر قسمت های كد، عملیات های عمومی در .NET می باشد و احتیاج به توضیحات خاصی نخواهد داشت.

#### شفاف سازی ####

ویندوز XP داری برخی تنظیمات امنیتی می باشد كه ممكن است باعث ایجاد مسائلی در برخی از ویژگی های دانلود فایل در مرورگرها شود. احتمالا شما نیاز داشته باشید برخی دستورالعمل ها را برای افرادی كه از XP استفاده می نمایند، جهت راهنمائی تهیه نمائید. این چیز مختصری است و تا اندازه ای به تجربه آن ها برای هر بار دریافت فایل از وب بستگی دارد. به همان اندازه كه كاربران به تنظیمات و پیش فرض های XP خو گرفته اند، بایستی اقدام به كمتر نمودن تماس های پشتیبانی نمایند. 

**سوالات متداول برای وب سایت هائی كه از كدهای این مقاله استفاده می نمایند**

پرسش: من نمی توانم اسنادی را از سایت دریافت نمایم. زمانی كه بر روی دكمه دریافت كلیك می نمایم، صفحه ای بازشده و سریعا ناپدید می شود. چرا نمی توانم فایلی را دریافت نمایم؟

پاسخ: احتمالا شما از ویندوز XP استفاده می نمائید، كه با تنظیمات پیش فرض اش از دریافت خودكار سند جلوگیری می نماید. تنها راهی كه برای این مسئله وجود دارد غیر فعال نمودن تنظیمات پیش فرض XP برای مرورگر و اجازه دریافت اسناد به صورت خودكار می باشد:
- در مرورگر IE تان، بر روی Tools و سپس Internet Options كلیك نمائید.
- به زبانه Security مراجعه نمائید، آنگاه بر روی دكمه Custome Level كلیك نمائید.
- در قسمت Downloads از لیست، به دنبال Automatic prompting for file downloads جستجو نمائید و بروی Enable كلیك كنید.
- بر روی OK كلیك كنید.

#### جمع بندی ####

امیدورایم كد پیشنهادی تمامی مباحث مربوطه را به درستی معرفی و تشریح نموده باشد. متاسفانه امكان شرح كدها در سایر زبان ها در مقاله ای محدود امكان پذیر نمی باشد. دقت نمائید كه ما فقط دست به تشریح مفاهیم مربوطه زدیم و از هرگونه توضیحات جامع و بلند در مورد دستورات خودداری نمودیم و در نهایت به شرح مختصری از توابع بدون بررسی كد های آن ها بسنده نمودیم. فرآیند مقاله ایجاب می نمود تا از توضیحات اضافی خودداری كنیم و فقط كدهای دخیل در فرآیند پروژه مورد بررسی قرار گیرد. از نظر دسته بندی نیز این مقاله در سطح متوسط و بالاتر قرار می گیرد.

دلیل انتخاب زبان Perl – با توجه به این كه نگارنده تسلط بیشتری بر زبان C# دارد – این بوده است كه در این زبان مسائل بسیار بهتر تشریح می شوند – با توجه به اینكه یادگیری مفاهیم .NET نیازمند صرف وقت كافی می باشد – و قطعا در تعداد مخاطبان مقاله تاثیر گذار بوده است.  قطعا كد C# دارای ارجحیت هائی بر كد Perl می باشد. با توجه به اینكه این زبان Strong-Type و Case Sensetive می باشد تجربه آن جهت برنامه نویسی ساخت یافته توصیه می شود.


[دریافت سورس کد کامل از GitHub](https://github.com/NuLL3rr0r/babaei.net/tree/master/2007-12-15-secure-file-download)

[دریافت سورس کد کامل](2007-12-15-secure-file-download.7z)


{% codeblock securedown.html lang:html %}
<!--
  (The MIT License)

  Copyright (c) 2007 M.S. Babaei

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
-->


<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>Secure File Download</title>
</head>

<body>
    <center>
        <h3>
            Secure File Download<br />
            Using Perl or ASP.NET (C#)<br />
            And The Other Server Side Languages<br />
            <br /><br />
            <hr />
            Using Perl Script<br /><br />
            To download you must register<br /><br />
            <form action="securedown.pl" method="get">
                <input type="hidden" name="filename" value="test.zip" />
                Email: <input type="text" name="mail" />
                &nbsp;<input type="submit" value="Download" /><br /><br />
            </form>
            File you requested: test.zip<br /><br />
            <br /><br />
            <hr />
            Using ASP.NET(C#) Script<br /><br />
            To download you must register<br /><br />
            <form action="securedown.aspx" method="get">
                <input type="hidden" name="filename" value="test.zip" />
                Email: <input type="text" name="mail" />
                &nbsp;<input type="submit" value="Download" /><br /><br />
            </form>
            File you requested: test.zip<br /><br />
        </h3>
    </center>
</body>
</html>
{% endcodeblock %}

{% codeblock securedown.pl lang:perl %}
#!/usr/bin/perl

#  (The MIT License)
#
#  Copyright (c) 2007 M.S. Babaei
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


use strict;
use CGI ':standard';
use CGI::Carp 'fatalsToBrowser';

use lib "../cgi-lib";
use String;
use String::Random;

my $fileName = param('filename');
my $mail = param('mail');
my $uid = param('uid');

my $filePath = "../files/" . $fileName;
my $regList = "../list/list.txt";

my $httpHeader = "Content-Type: text/html; charset=utf-8\n\n";


if (FoundXSS($fileName)) {
    print $httpHeader;
    print qq(<br /><center><h3>Alice is not in Wonderland.</h3></center>);
    exit;
}

if ($fileName ne '' and $mail ne '') {
    print $httpHeader;

    if (-e $filePath) {
        open (REG, "<:utf8", $regList) || Error ("register", "your mail address");
        flock (REG, 1);
        my @lines = <REG>;
        close(REG);

        my $list = join("", @lines);

        while (1) {
            $uid = UidGen(30);
            my $isDup = $list =~ m/$uid/;
            if ($isDup == 0) {
                last;
            }
        }
                
        open (REG, ">>:utf8", $regList) || Error ("register", "your mail address");
        flock (REG, 2);
        print REG qq($uid\n);
        close (REG);    
    
        my $link = qq(http://www.somedomain.com/securedown.pl?filename=$fileName&uid=$uid);
    
        SendMail($mail, qq("Your Name" <someid\@somedomain.com>), "Download Link", qq(<strong>Download Link:<strong><br/>$link));
        print qq(<br /><center><h3>Thanks for your registration<br/>The download link sent to your inbox<br/>Just follow it...</h3></center>);
        exit;
     }
     else {
        Error('find', $fileName);
     }
}
elsif ($fileName ne '' and $uid ne '') {
    open (REG, "<:utf8", $regList) || ErrorH ("find", "the registeration information");
    flock (REG, 1);
    my @lines = <REG>;
    close(REG);
    
    my $isReg = 0;
    
    foreach (@lines) {
        if ($_ =~ m/$uid/) {
            $isReg = 1;
            last;
        }
    }
    
    if (!$isReg) {
        print $httpHeader;
        print qq(<br /><center><h3>You're not registered</h3></center>);
        exit;
    }

    if (-e $filePath) {
        open (FILE, $filePath) || ErrorH ("open", "$fileName");
        flock (FILE, 1);

        binmode(FILE);
        binmode(STDOUT);

        my $cgi = new CGI;
        print $cgi->header( -type => 'application/octet-stream', -attachment => qq($fileName) );

        my $buffer;
    
        while (read(FILE, $buffer, 100 * 2**10)) {
            print STDOUT $buffer;
        }
        
        close(FILE);

        open (REG, ">:utf8", $regList);
        flock (REG, 2);
        foreach(@lines) {
            $_ =~ s/$uid\n//;
            print REG $_;
        }
        close (REG);
    }
    else {
        ErrorH ('find', $fileName);
    }
}
else {
    print $httpHeader;
    print qq(<br /><center><h3>Error Parsing Parameters</h3></center>);
}

sub SendMail {
    my $to = $_[0];
    my $from =  $_[1];
    my $subject =  $_[2];
    my $body =  $_[3];
    
    open (MAIL, "|/usr/lib/sendmail -t") || Error('open', 'mail program');

    print MAIL "To: $to\n";
    print MAIL "From: $from\n";
    print MAIL "Subject: $subject\n";
    print MAIL "Content-type: text/html; charset=utf-8\n\n";
    print MAIL "$body";

    close(MAIL);
        
    return 1;
}

sub UidGen {
    my $pattern;
    
    for (my $i = 0; $i < $_[0]; $i++) {
        $pattern .= "s";
    }
    
    my $rnd = new String::Random;
    my $key = $rnd->randpattern($pattern);
    return $key;
}

sub FoundXSS {
    foreach (@_) {
        if ($_ =~ /[<>]/) {
            return 1;
        }
    }
    
    return 0;
}

sub Error {
    print qq(<br /><center><h3>The server cant $_[0] the $_[1]: $!\n</h3></center>);
    exit;
}

sub ErrorH {
    print $httpHeader;
    print qq(<br /><center><h3>The server can't $_[0] the $_[1]: $!\n</h3></center>);
    exit;
}
{% endcodeblock %}

{% codeblock securedown.aspx lang:csharp %}
<!--
  (The MIT License)

  Copyright (c) 2007 M.S. Babaei

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
-->


<%@ Page Language="C#" ContentType="text/html" ResponseEncoding="utf-8" %>
<%@ Import Namespace="System.Net.Mail" %>
<%@ Import Namespace="System.IO" %>

<script type="text/C#" runat="server">
    private string UidGen(int len)
    {
        Random rnd = new Random();
        String id = string.Empty;
        int min = 0, max = 0;

        for (int i = 0; i < len; i++)
        {
            switch (rnd.Next(3))
            {
                case 0:
                    min = 48;
                    max = 58;
                    break;
                case 1:
                    min = 65;
                    max = 91;
                    break;
                case 2:
                    min = 97;
                    max = 123;
                    break;
                default:
                    break;
            }
            id = String.Concat(id, Convert.ToChar(rnd.Next(min, max)));
        }

        return id;
    }

    private bool SendMail(string to, string from, string subject, string body)
    {
        try
        {
            using (MailMessage msg = new MailMessage(from, to, subject, body))
            {
                msg.BodyEncoding = Encoding.UTF8;
                msg.SubjectEncoding = Encoding.UTF8;
                msg.IsBodyHtml = true;
                msg.Priority = MailPriority.High;
                
                SmtpClient smtp = new SmtpClient("smtp.gmail.com", 587);
                smtp.Credentials = new System.Net.NetworkCredential("some.id@gmail.com", "pw");
                smtp.EnableSsl = true;
                smtp.Send(msg);
            }
        }
        catch (FormatException ex)
        {
            Error(ex.Message);
            return false;
        }
        catch (SmtpException ex)
        {
            Error(ex.Message);
            return false;
        }
        finally
        {
        }

        return true;
    }
    
    private void Error(string err)
    {
        Response.Write(err);
    }
</script>

<%
    string fileName = Request.QueryString["filename"];
    string mail = Request.QueryString["mail"];
    string uid = Request.QueryString["uid"];
        
    string path = Server.MapPath("~");
    path += path.EndsWith("\\") ? string.Empty : "\\";
    string parent = path.Substring(0, path.LastIndexOf("\\", path.Length - 2) + 1);
    string filePath = parent + "files\\" + fileName;
    string regList = parent + "list\\" + "list.txt";
    string regTemp = parent + "list\\" + "temp.txt";
    
    
    if (fileName != string.Empty && fileName != null && mail != string.Empty && mail != null)
    {
        if (File.Exists(filePath))
        {
            try
            {
                using (StreamReader sr = new StreamReader(regList))
                {
                    while (true)
                    {
                        uid = UidGen(30);
                        bool isDup = false;
                        while (sr.Peek() >= 0)
                        {
                            if (sr.ReadLine().IndexOf(uid) > -1)
                            {
                                isDup = true;
                            }
                        }
                        if (!isDup)
                        {
                            break;
                        }
                    }
                }
                
                using (StreamWriter sw = new StreamWriter(regList, true, Encoding.UTF8))
                {
                    sw.WriteLine(uid);
                }

                string link = String.Format("http://www.somedomain.com/securedown.pl?filename={0}&uid={1}", fileName, uid);
                
                if (SendMail(mail, "someid@somedomain.com", "Download Link", "<strong>Download Link:<strong><br/>" + link))
                    Response.Write("<br /><center><h3>Thanks for your registration<br/>The download link sent to your inbox<br/>Just follow it...</h3></center>");
            }
            catch (Exception ex)
            {
                Error(ex.Message);
            }
            finally
            {
            }
        }
        else
        {
            Error("File not found: " + fileName);
        }
    }
    else if (fileName != string.Empty && fileName != null && uid != string.Empty && uid != null)
    {
        try
        {
            bool isReg = false;

            string list = string.Empty;
            
            using (StreamReader sr = new StreamReader(regList))
            {
                while (sr.Peek() >= 0)
                {
                    string line = sr.ReadLine();
                    if (line.IndexOf(uid) > -1)
                    {
                        line = string.Empty;
                        isReg = true;
                    }
                    else
                        list += (line + " ");
                }
                sr.Close();
            }

            if (isReg)
            {
                if (File.Exists(filePath))
                {
                    int fileSize = (int)new FileInfo(filePath).Length;
                    byte[] buffer = new byte[fileSize];

                    using (FileStream fs = new FileStream(filePath, FileMode.Open))
                    {
                        fs.Read(buffer, 0, fileSize);
                    }

                    Response.AddHeader("Content-Disposition", "attachment; filename=" + fileName);
                    Response.ContentType = "application/octet-stream";
                    Response.BinaryWrite(buffer);
                    
                    string[] lineList = list.Split(' ');

                    using (StreamWriter sw = new StreamWriter(regTemp, false, Encoding.UTF8))
                    {
                        foreach (string i in lineList)
                        {
                            if (i != string.Empty)
                                sw.WriteLine(i);
                        }
                        sw.Flush();
                        sw.Close();
                    }

                    File.Delete(regList);
                    File.Move(regTemp, regList);

                    Response.End();
                }
                else
                    Error("<br /><center><h3>File not found: " + fileName + "</h3></center>");
            }
            else
                Error("<br /><center><h3>You're not registered</h3></center>");
        }
        catch (Exception ex)
        {
            Error(ex.Message);
        }
        finally
        {
        }
    }
    else
    {
        Response.Write("<br /><center><h3>Error Parsing Parameters</h3></center>");
    }    
%>
{% endcodeblock %}

{% codeblock securedown-patched.pl lang:perl %}
#!/usr/bin/perl

#  (The MIT License)
#
#  Copyright (c) 2007 M.S. Babaei
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


use strict;
use CGI ':standard';
use CGI::Carp 'fatalsToBrowser';

use lib "../cgi-lib";
use String;
use String::Random;

my %mag = ('no1' => 'example1.pdf', 'no2' => 'example2.pdf', 'no3' => 'example3.pdf');

my $magID = param('magid');
my $mail = param('mail');
my $uid = param('uid');

my $fileName = "";

foreach (keys %mag) {
    if ($_ eq $magID) {
        $fileName = $mag{$_};
        last;
    }
}

my $filePath = "../files/" . $fileName;
my $regList = "../list/list.txt";

my $fileName = param('filename');
my $httpHeader = "Content-Type: text/html; charset=utf-8\n\n";


if (FoundXSS($fileName)) {
    print $httpHeader;
    print qq(<br /><center><h3>Alice is not in Wonderland.</h3></center>);
    exit;
}

if ($fileName ne '' and $mail ne '') {
    print $httpHeader;

    if (-e $filePath) {
        open (REG, "<:utf8", $regList) || Error ("register", "your mail address");
        flock (REG, 1);
        my @lines = <REG>;
        close(REG);

        my $list = join("", @lines);

        while (1) {
            $uid = UidGen(30);
            my $isDup = $list =~ m/$uid/;
            if ($isDup == 0) {
                last;
            }
        }
                
        open (REG, ">>:utf8", $regList) || Error ("register", "your mail address");
        flock (REG, 2);
        print REG qq($uid\n);
        close (REG);    
    
        my $link = qq(http://www.somedomain.com/securedown.pl?filename=$fileName&uid=$uid);
    
        SendMail($mail, qq("Your Name" <someid\@somedomain.com>), "Download Link", qq(<strong>Download Link:<strong><br/>$link));
        print qq(<br /><center><h3>Thanks for your registration<br/>The download link sent to your inbox<br/>Just follow it...</h3></center>);
        exit;
     }
     else {
        Error('find', $fileName);
     }
}
elsif ($fileName ne '' and $uid ne '') {
    open (REG, "<:utf8", $regList) || ErrorH ("find", "the registeration information");
    flock (REG, 1);
    my @lines = <REG>;
    close(REG);
    
    my $isReg = 0;
    
    foreach (@lines) {
        if ($_ =~ m/$uid/) {
            $isReg = 1;
            last;
        }
    }
    
    if (!$isReg) {
        print $httpHeader;
        print qq(<br /><center><h3>You're not registered</h3></center>);
        exit;
    }

    if (-e $filePath) {
        open (FILE, $filePath) || ErrorH ("open", "$fileName");
        flock (FILE, 1);

        binmode(FILE);
        binmode(STDOUT);

        my $cgi = new CGI;
        print $cgi->header( -type => 'application/octet-stream', -attachment => qq($fileName) );

        my $buffer;
    
        while (read(FILE, $buffer, 100 * 2**10)) {
            print STDOUT $buffer;
        }
        
        close(FILE);

        open (REG, ">:utf8", $regList);
        flock (REG, 2);
        foreach(@lines) {
            $_ =~ s/$uid\n//;
            print REG $_;
        }
        close (REG);
    }
    else {
        ErrorH ('find', $fileName);
    }
}
else {
    print $httpHeader;
    print qq(<br /><center><h3>Error Parsing Parameters</h3></center>);
}

sub SendMail {
    my $to = $_[0];
    my $from =  $_[1];
    my $subject =  $_[2];
    my $body =  $_[3];
    
    open (MAIL, "|/usr/lib/sendmail -t") || Error('open', 'mail program');

    print MAIL "To: $to\n";
    print MAIL "From: $from\n";
    print MAIL "Subject: $subject\n";
    print MAIL "Content-type: text/html; charset=utf-8\n\n";
    print MAIL "$body";

    close(MAIL);
        
    return 1;
}

sub UidGen {
    my $pattern;
    
    for (my $i = 0; $i < $_[0]; $i++) {
        $pattern .= "s";
    }
    
    my $rnd = new String::Random;
    my $key = $rnd->randpattern($pattern);
    return $key;
}

sub FoundXSS {
    foreach (@_) {
        if ($_ =~ /[<>]/) {
            return 1;
        }
    }
    
    return 0;
}

sub Error {
    print qq(<br /><center><h3>The server cant $_[0] the $_[1]: $!\n</h3></center>);
    exit;
}

sub ErrorH {
    print $httpHeader;
    print qq(<br /><center><h3>The server can't $_[0] the $_[1]: $!\n</h3></center>);
    exit;
}
{% endcodeblock %}


#### منابع و ماخذ ####

<div style="direction: ltr; text-align: left;">
<pre>
<a href="http://www.codeproject.com/KB/aspnet/SecureFileDownload.aspx" target="_blank">http://www.codeproject.com/KB/aspnet/SecureFileDownload.aspx</a>
<a href="http://www.codeproject.com/KB/cs/SendMailUsingGmailAccount.aspx" target="_blank">http://www.codeproject.com/KB/cs/SendMailUsingGmailAccount.aspx</a>
<a href="http://www.mono-project.com/" target="_blank">http://www.mono-project.com/</a>
<a href="http://www.webmaster-toolkit.com/mime-types.shtml" target="_blank">http://www.webmaster-toolkit.com/mime-types.shtml</a>
<a href="https://mail.google.com/" target="_blank">https://mail.google.com/</a>
</pre>
</div>


[^1]: تمامی كدهای استفاده شده در این مقاله در انتهای مطلب در قالب یک فایل فشرده قابل دریافت می باشد.

[^2]:  نرم افزاری Open Source جهت اجرای نرم افزارهای Desktop و Web تحت تكنولوژی .NET در سیستم عامل های Mac OS X, UNIX, Linux, Solaris و Windows به نشانی [http://www.mono-project.com/](http://www.mono-project.com/)، كه توسط Novell پشتیبانی می شود.

[^3]: Edit / Preferences / Code Format / Line Break Type  - البته دقت نمائید كه این تنظیم برای تمامی فایل هائی كه پس از این ایجاد می شوند تاثیر گذار خواهد بود.

[^4]: Multipurpose Internet Mail Extensions - اعلان نوع سند كه آن را به مرورگر معرفی می نماید.

[^5]: شرح تمامي توابع دست ساز در ادامه خواهد آمد.

[^6]: براي ديدن ليست كاملي از اين MIME ها به آدرس [http://www.webmaster-toolkit.com/mime-types.shtml](http://www.webmaster-toolkit.com/mime-types.shtml) مراجعه نمائيد.

[^7]: Relative

[^8]: Absolute

[^9]: اين سرويس از اوائل فوريه 2007 بدون دعوت نامه قابل دسترس مي باشد. جهت دريافت يك اكانت Gmail مي توانيد به آدرس [https://mail.google.com/](https://mail.google.com/) مراجعه نمائيد.

