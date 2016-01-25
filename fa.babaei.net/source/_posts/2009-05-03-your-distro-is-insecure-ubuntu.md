---
layout: post
title: "Your Distro is Insecure: Ubuntu"
date: 2009-05-03 00:00
comments: false
sharing: true
footer: true
tags:
- GNU
- Linux
- Security
- Ubuntu
---

### <center>توزیع شما نا امن است: اوبونتو</center> ###

<!-- more -->

<div style="font-style: oblique;">
<br />
مقاله ی حاضر پیش از این در شماره ی ۲.۵ مجله ی Snoop – اردیبهشت ماه ۱۳۸۸ – به چاپ رسیده است.
<br />
یادآور می شویم مقاله حاضر حاصل ترجمه کامل مقاله ای از Ronald McCarty تحت عنوان Your Distro is Insecure: Ubuntu است که در تاریخ ۱۳ آوریل ۲۰۰۹ در وب سایت linux-mag.com انتشار یافته است. 
<br /><br /><br />
</div>


توزیع شما نا امن است: اوبونتو

<pre>
برنامه نصب اوبونتو نسخه سرور یکی از ساده ترین و تمیزترین برنامه های نصب در
میان سایر توزیع های لینوکس است. با این وجود٬ در بسیاری از موارد٬ طراحان آن تصمیم به
قربانی نمودن امنیت در ازای سادگی استفاده نموده اند. نتیجه؟ بصورت پیش فرض یک نسخه
تازه نصب شده اوبونتو ایمن نیست.

Ronald McCarty
دوشنبه ۱۳ آوریل ۲۰۰۹
</pre>


در طول سالیان گذشته٬ بسیاری از توزیع های لینوکس در جهت بهبود فرآیند نصب به منظور در اختیار نهادن هرچه بیشتر سیستم عامل آزاد و رایگان لینوکس برای افراد بیشتر متمرکز شده اند. هدف با شکوهی است٬ با این حال٬ زمانی که قصد ساده تر نمودن همه چیز را در محاسبات داشته باشیم٬ راه حل معمول تصمیم گیری در پاسخ به تعدادی از تصمیمات و اختیارات کاربر بصورت پیش فرض می باشد که خود باعث می شود برنامه نصب ناآزموده (شاید هم آزموده) لینوکس را در معرض خطر قرار دهیم.

متاسفانه٬ بسیاری از توزیع های لینوکس جهت نصب دست به انتخاب تعدادی از تصمیمات امنیتی اشتباه و مفتضح می زنند. اغلب مواقع این اعمال از آنجائی که این تفکر رایج است: “چون از لینوکس استفاده می نمائیم٬ پس ایمن است.” توسط مدیر سیستم نادیده گرفته می شوند. که البته به زودی مشاهده می نمائیم٬ که اینگونه نیست.

در این مقاله نگاهی به اوبونتو سرور نسخه ۸.۱۰ می نمائیم. روش کار بدین ترتیب است که مشخص بنمائیم آیا نصب ما به اندازه کافی در زمینه های زیر ایمن می باشد یا خیر:

- احراز هویت (Identity)
- تائید اعتبار (Authentication)
- مجوز (Authorization)

احراز هویت کلید دسترسی به منابع محاسباتی می باشد. برای بسیاری از سرویس های داخلی احراز هویت اطلاعات محرمانه بایستی به آنهائی محدود باشد که به اطلاعات نیاز دارند. به عنوان نمونه این به محض تعیین هویت کاربر اتفاق می افتد. جهت تشخیص هویت کاربر بایستی بوسیله تائید اعتبار (کلمات عبور) آن را بررسی و تائید نمود.

تائید اعتبار کلیدی است که امنیت سیستم را تضمین می نماید. از آنجائی که امنیت بوسیله احراز هویت یک کاربر حاصل می شود با استفاده از یک تائید اعتبار ضعیف به سرعت آن را از دست می دهید. گاه کاربران می توانند علت تائید اعتبار ضعیف باشند (برای مثال به اشتراک گذاشتن یا از دست دادن کلمات عبور)٬ اما در این مقاله به بررسی ضعف از دیدگاه سیستم می پردازیم.

در نهایت٬ مجوز لازمه تضمین این نکته است که منابع درخور (کافی و نه بیشتر) در اختیار کاربر قرار گرفته اند. این روش اجازه اعمال مدیریت پیشرفته را بر روی منابع خاصی از سرور می دهد. برای مثال٬ پوشه ها٬ چاپگرها و غیره.

### دستاویز٬ دستاویز ###

بین طرفداران لینوکس (و سازندگان سیستم عامل بر روی پلتفرم انتخابی آنان) رایج است که بسیاری از تصمیماتی که در توسعه یک برنامه نصب تاثیر گذار می باشد را به طرز توجیه پذیر کنار بگذارند. بیشترین دلیل ذکر شده برای فقدان امنیت بر اساس ایده ای است که بیان می دارد که امنیت و سادگی استفاده دو مقوله کاملا جداگانه از یکدیگر هستند. این مقاله نشان می دهد که چگونه و چه زمانی تصمیمات امنیتی اشتباه توسط برنامه های نصب اتخاذ می شود؛ به علاوه این که چگونه می توانید با اتخاذ یک راه حل ایمن و استوار این مسائل را برطرف نمائید.

دلیل عمده دیگری که برای فقدان امنیت ذکر می شود این است که یک توزیع در حقیقت چیزی بیش از یک مجموعه نرم افزار نیست و بسته های جداگانه بایستی توسط توسعه دهندگان آن ایمن شوند نه توزیع کننده آن نسخه از لینوکس.

این گونه توجیه عادات بد با عادات بدتر روال بسیار ضعیف و پستی است. اگر توزیع از طرف  کاربر تصمیم گیرنده است٬ بنابراین بایستی تصمیمات استوار و قابل اطمینانی بگیرد و تصمیم گیری را بر عهده توسعه دهندگان بسته ها نگذارد. (در واقع٬ توزیع بایستی به کمک جامعه توسعه دهندگان آمده و توسعه دهنده را از معادله خارج نموده٬ و هرگونه ریسک امنیتی که مربوط به آن یا کاربرانش باشد را شناسائی نماید.)

### امنیت در زمان نصب ###

بیائید با یک نصب جدید از ابونتو سرور نسخه ۸.۱۰ شروع نمائیم.

یکی از اولین ریسک های امنیتی که در حین نصب اوبونتو سریعا در ذهن نمایان می شود٬ خوانا نمودن شاخه home برای همگان می باشد: “The contents of your home directory will normally be visible to all users on the system” (یعنی: محتویات شاخه home شما در حالت عادی برای تمامی کاربران بر روی سیتم قابل رویت است) همان طور که در شکل ۱ نمایش داده شده است٬ “تنظیم نام های کاربری و کلمات عبور”.
 
<center>تصویر ۱: تنظیم نام های کاربری و کلمات عبور</center>
{% img post-image /blog/2009/05/03/your-distro-is-insecure-ubuntu/2009-05-03-your-distro-is-insecure-ubuntu_001.jpg 603 313 "'تصویر ۱: تنظیم نام های کاربری و کلمات عبور'" "'تصویر ۱: تنظیم نام های کاربری و کلمات عبور'" %}

آیا مجوزهای دسترسی به صورت پیش فرض باز هستند؟ ترجیجا به طرز پیچیده وعجیب و غریبی٬ از آن جا که پوشه به طرز وسیعی باز است٬ برنامه نصب سعی می کند با کدگذاری نمودن یک پوشه خصوصی حفره را پوشانده و برطرف نماید!

نگاهی دقیقتر به مجوزهای دسترسی تائید می نماید که فایل ها توسط همگان قابل دسترسی و خواندن است:

<div style="direction: ltr; text-align: left;">
<pre>
drwxr-xr-x 2 rmccarty rmccarty 4096 2009-04-13 09:40 rmccarty
</pre>
</div>
  
به علاوه٬ اطلاعات هر کاربر جدیدی که در آینده با دستور useradd ساخته شود به سبب این ورودی در فایل /etc/adduser.conf، برای همگان قابل خواندن است:

<div style="direction: ltr; text-align: left;">
<pre>
DIR_MODE=0755
</pre>
</div>

ادامه می دهیم٬ در مرحله انتخاب نرم افزارها٬ به صورت پیش فرض آیتم های زیر برای نصب انتخاب هستند:

<div style="direction: ltr; text-align: left;">
<pre>
DNS Server, LAMP server, mail server, OpenSSH server, and the Virtual Machine host
</pre>
</div>

که در واقع این ها نمونه هائی هستند که به طور معمول توسط تنظیمات پیش فرض اوبونتو نسخه سرور نصب می شوند.

به محض این که نصب انجام شد٬ برنامه نصب تقاضای تغییر کلمه عبور برای کاربر root بسته mysql را دارد. این بسیار عالی است چرا که mysql بصورت پیش فرض بدون کلمه عبوری برای کاربر root نصب می شود (root تحت کنترل mysql است٬ نه کاربر root سیستم). متاسفانه٬ برنامه نصب به کاربر اجازه می دهد تا کلمه عبور را خالی گذارده و از آن عبور نماید به جای این که او را مجبور به ورود پسورد کند. برنامه نصب حتی هیچ گونه قانونی را برای در نظر گرفتن حداقل طول کلمه عبور و یا غیره به اجرا نمی گذارد. نمونه ای دیگر که نقض امنیت را انتخاب می کند.

برای این نقایص امنیتی اوبونتو نمره A- را دریافت می دارد. در کارنامه برای نقص امنیتی مربوط به مجوز به سادگی نمره A را دریافت می نماید. در ازای نصب ساده تر باعث دسترسی و خوانا بودن فایل های کاربران توسط همگان می شود اما واگذاری ضعف و نهادن آن بر عهده مدیر سیستم و یا کاربر سادگی استفاده نمی باشد٬ می باشد؟

### بعد از نصب – شبکه ###

یکی از سریع ترین راه ها برای هکرها جهت دسترسی به سیستم ها استفاده از سرویس هائی است که به خوبی مستند سازی و یا درک نشده اند. زمانی که سیستمی در محیط کار و تولید قرار دارد٬ معمولا اتفاق می افتد که به طور ناخواسته سیستم سنگین شود٬ بنابراین ریسک های اضافی تولید خواهند شد که به سرویس هائی مربوط هستند که هرگز استفاده نخواهند شد.

اوبونتو اجازه انتخاب مجموعه نرم افزارهائی را می دهد که مدیر سیستم قصد استفاده از آن ها را دارد. با این وجود٬ نگاهی عمیق تر به نسخه محدود شده netstat سرویس هائی را نشان می دهد که اصلا نیاز نیستند یا توسط مدیر سیستم درخواست نشده اند:

<div style="direction: ltr; text-align: left;">
<pre>
root@sparky:~# netstat -l
Active Internet connections (only servers)
Proto Recv-Q Send-Q Local Address Foreign Address State
tcp 0 0 *:pop3 *:* LISTEN
tcp 0 0 *:imap2 *:* LISTEN
udp 0 0 *:bootps *:*
udp 0 0 *:bootpc *:*
</pre>
</div>

جالب است! دو ورودی اول: The Post Office Protocol Version 3 (pop3) و The Internet Message Access Protocol Version 2 (imap2) نصب شده و در حال اجرا می باشند با وجود اینکه اوبونتو در حال حاضر نسخه های ایمن تری از آن ها را نصب شده و دارا می باشد. هر دوی این دو پروتکل قدیمی سال ها پیش جهت همکاری و ارتباط با برنامه های قدیمی ایمیل نیاز بودند٬ اما در حال حاضر عمده نرم افزارهای ایمیل از نسخ جدیدتر و ایمن تر آن استفاده می نمایند. (بزرگترین مسئله با این سرویس های قدیمی مسئله کشف متن کلمات عبور می باشد٬ به هرحال سرورهای POP2 در مقابل مصالحه root آسیب پذیر می باشند.)

ورودی های bootps و bootpc جهت فراهم نمودن آدرس دهی پویا بوسیله پروتکل های BOOTP و DHCP بکار می روند. این سرویس ها به صورت پیش فرض حتی با وجود استفاده از آدرس دهی ایستا نیز فعال می باشند٬ و با نصب نسخه سرور استفاده می شوند. حتی اگرهم قصد فراهم نمودن سرویس های DHCP در شبکه را داشته باشید٬ این گزینه به عنوان بخشی از رویه نصب در دسترس نخواهد بود و در زیر مجموعه گزینه DNS در زمان نصب مخفی خواهد بود.

وجود و اجرای این سرویس های غیرمجاز رتبه اوبونتو را تا حد B برای مجوز در کارنامه کاهش می دهد.

### نام های کاربری – کلید ورود به قلمرو پادشاهی ###

دسترسی راه دور با مدیریت سست شناسه کاربری ترکیب شده است که خوراک است برای ایجاد فاجعه. کلید داشتن یک سیستم مدیریت شناسه امن محدود کردن سیستم برای دسته ای از نیازهای ضرروری است و نه صدور اجازه دسترسی به خط فرمان از راه دور برای آن حساب های کاربری.

بررسی حساب های کاربری سیستمی اوبونتو نتیجه ای مشابه آنچه که درذیل می آید را نمایان می سازد:  

<div style="direction: ltr; text-align: left;">
<pre>
daemon:x:1:1:daemon:/usr/sbin:/bin/sh
bin:x:2:2:bin:/bin:/bin/sh
sys:x:3:3:sys:/dev:/bin/sh
games:x:5:60:games:/usr/games:/bin/sh
man:x:6:12:man:/var/cache/man:/bin/sh
lp:x:7:7:lp:/var/spool/lpd:/bin/sh
mail:x:8:8:mail:/var/mail:/bin/sh
news:x:9:9:news:/var/spool/news:/bin/sh
uucp:x:10:10:uucp:/var/spool/uucp:/bin/sh
proxy:x:13:13:proxy:/bin:/bin/sh
www-data:x:33:33:www-data:/var/www:/bin/sh
backup:x:34:34:backup:/var/backups:/bin/sh
list:x:38:38:Mailing List Manager:/var/list:/bin/sh
irc:x:39:39:ircd:/var/run/ircd:/bin/sh
gnats:x:41:41:Gnats Bug-Reporting System (admin):/var/lib/gnats:/bin/sh
nobody:x:65534:65534:nobody:/nonexistent:/bin/sh
libuuid:x:100:101::/var/lib/libuuid:/bin/sh
sshd:x:107:65534::/var/run/sshd:/usr/sbin/nologin
</pre>
</div>

به استثنا sshd، همه حساب های کاربری سیستمی به همراه قابلیت دسترسی تعاملی به خط فرمان از طریق یک جلسه کاری عرضه شده اند. خب٬ بنابراین زمانی که یکی از آن حساب های کاربری در حال مصالحه تعاملی از راه دور می باشد حاصل آن بسیار شبیه نتایج است. برای مثال٬ یک بارگذاری اضافه در بافر برای برخی از پروسه های پست الکترونیکی می تواند بر روی یکی از کاربران مرتبط با پست التکرونیکی (از قبیل mail, news,uucp و غیره) اثر گذار بوده و توانائی فراهم نمودن دسترسی راه دور به سیستم از طریق خط فرمان را خواهد داشت. اوبونتو بایستی این حساب های کاربری را با گزینه nologin و احتمالا /bin/false علامت گذاری نماید.

مسئله نگران کننده دیگر این حقیقت است که شناسه های کاربری وجود دارند که به دلیل در استفاده بودن توسط پروسه نصب آشکار نخواهند شد. برای مثال٬ حتی با وجود عدم انتخاب سرور چاپگر٬ هنوز هم کاربر lp وجود داشته و فعال خواهد بود. حساب های کاربری مظنون دیگر news, uucp, list, irc می باشند.

بحث هائی پیرامون استاندارد سازی شناسه های کاربری مستقل از انواع توزیع ها مطرح شده اند که مهمتر از عدم گنجاندن شناسه های کاربری می نماید. برای مثال٬ uucp همیشه بایستی دارای UID شماره ۱۰ باشد. این مقدار یک استاندارد است؛ با وجود این روش ایمن تر می تواند با گنجاندن هوش و آگاهی در برنامه های مدیریت بسته یا passwd بکار گرفته شود. و یا٬ یک انتخاب ساده تر٬ ایجاد شناسه ها و سپس غیرفعال نمودن آن ها در جهت جلوگیری از اختصاص عدد UID به شناسه کاربری دیگر.

در حالی که که روش اوبونتو غیر معمول نمی نمایاند٬ مدیریت احراز هویت در توزیعی که بازار توزیع های سرور را نشانه گرفته است بایستی مستحکم تر باشد. بنابراین یک A- تضمینی برای مدیریت احراز هویت استاندارد می باشد.

#### جمع بندی ####

اوبونتو دارای یکی از تمیزترین و ساده ترین برنامه های نصب در میان توزیع های لینوکس می باشد؛ با این وجود٬ طراحان آن تصمیم به نادیده انگاشتن امنیت در پاره ای از موارد که شرح آن گذشت گرفته اند. هرچند این مسائل در بسیاری موارد پس از نصب قابل مرتفع سازی می باشد٬ یک نصب جدید بصورت پیش فرض به هیچ وجه ایمن نیست.

<pre>
Ronald McCarty یک حرفه ای در زمینه سیستم/شبکه و نویسنده ای freelance
می باشد. Ron تحصیلات دوره لیسانس را در زمینه CIS در دانشگاه Mary Land به پایان
رسانده و مدرک ارشد خود را از دانشگاه Capella دریافت نموده است. Ron یکی از
موسسان <a href="http://yournetguard.com/" target="_blank">Your Net Guard (www.YourNetGuard.com)</a> می باشد. کمپانی که در زمینه
زیرسازی IT به صورت تخصصی فعالیت می نماید. اوقات فراغت او به همراه بهترین دوست و
همسرش٬ Claudia٬ و دو فرزندشان سپری می شود. دسترسی به Ron از طریق
atmccarty@mcwrite.net میسر می باشد.
</pre>
 
 
#### منابع و ماخذ ####

<div style="direction: ltr; text-align: left;">
<pre>
Part1 :  <a href="http://www.linux-mag.com/id/7297/" target="_blank">http://www.linux-mag.com/id/7297/</a>
Part2 :  <a href="http://www.linux-mag.com/id/7297/2/" target="_blank">http://www.linux-mag.com/id/7297/2/</a>
</pre>
</div>

