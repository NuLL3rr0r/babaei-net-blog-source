+++
title = "امنیت سایبری ۱۰۱ ویژه فعالان حقوق بشر، فعالان مدنی، فعالان سیاسی، روزنامه نگاران و براندازان: جعل ایمیل چیست و نهادهای امنیتی جمهوری اسلامی چگونه با آن نخبگان و فعالان سیاسی اپوزیسیون را هدف قرار می‌دهند؟"
slug = "cybersecurity-101-islamic-republic-email-spoofing-targeting-opposition-political-elites-activists"
date = 2019-07-25T14:15:52+02:00
tags = [ "Barandazan", "Cybersecurity", "Email Spoofing", "Gmail", "Google", "Iran", "Islamic Republic Of Iran", "Security", "Spoofing" ]
toc = true
draft = true
+++

{{< figure src="/blog/cybersecurity-101-islamic-republic-email-spoofing-targeting-opposition-political-elites-activists/cybersecurity-101-islamic-republic-email-spoofing-targeting-opposition-political-elites-activists.png" alt="جعل ایمیل چیست و نهادهای امنیتی جمهوری اسلامی چگونه با آن نخبگان و فعالان سیاسی اپوزیسیون را هدف قرار می‌دهند؟" title="جعل ایمیل چیست و نهادهای امنیتی جمهوری اسلامی چگونه با آن نخبگان و فعالان سیاسی اپوزیسیون را هدف قرار می‌دهند؟" >}}

دیروز [توییتی](https://web.archive.org/web/20190725144354/https://twitter.com/Mostafaa_Azizi/status/1154011314936832001) با مضمون ذیل توسط آقای [مصطفا عزیزی](https://twitter.com/Mostafaa_Azizi)،  نویسنده، فیلم‌نامه‌نویس، طراح و تهیه‌کننده‌ی برنامه‌های تلویزیونی منتشر شد که ظاهرا ایمیلی از طرف ایشان برای آقای [سعید حسین‌پور](https://twitter.com/saeidpar)، عضو [شبکه فرشگرد](https://iranrevival.com/) ارسال شده است:

{{< figure src="/blog/cybersecurity-101-islamic-republic-email-spoofing-targeting-opposition-political-elites-activists/tweet-spoofed-email-by-islamic-republic-mostafa-azizi-saeid-hosseinpour.png" alt="توییت آقای مصطفا عزیزی در باره ایمیل جعل شده ارسالی به آقای سعید حسین‌پور" title="توییت آقای مصطفا عزیزی در باره ایمیل جعل شده ارسالی به آقای سعید حسین‌پور" >}}

متخصیین امنیت، این نوع حملات سایبری را [Email Spoofing](https://en.wikipedia.org/wiki/Email_spoofing) یا [جعل ایمیل](https://fa.wikipedia.org/wiki/%D8%B1%D8%A7%DB%8C%D8%A7%D9%86%D8%A7%D9%85%D9%87%E2%80%8C%D9%86%DA%AF%D8%A7%D8%B1%DB%8C_%D9%85%D8%AA%D9%82%D9%84%D8%A8%D8%A7%D9%86%D9%87) می‌نامند. در پاره‌ای از مواقع این ایمیل‌ها در حجم انبوه به منظور انجام حملات [Phishing](https://en.wikipedia.org/wiki/Phishing) یا [فیشینگ](https://fa.wikipedia.org/wiki/%D9%81%DB%8C%D8%B4%DB%8C%D9%86%DA%AF) به شکل [اسپم یا هرزنامه](https://fa.wikipedia.org/wiki/%D9%87%D8%B1%D8%B2%D9%86%D8%A7%D9%85%D9%87) ارسال می‌شود. اما در موارد دیگر این حملات به صورت هدفمند و برنامه‌ریزی شده جهت هک نمودن فعالان و نخبگان سیاسی مخالف رژیم جمهوری اسلامی انجام می‌شود. نکته‌ای که باید مدنظر داشت این است که در محتوای ایمیل فوق نه تنها یک لینک، بلکه دو لینک گنجانده شده است که بسته به تنظیمات نرم‌افزار ایمیل‌خوان ممکن است تنها با باز نمودن ایمیل و بدون کلیک کردن بر روی هر گونه لینکی هک شوید!

در ادامه این مطلب به چگونگی انجام این حملات و بهترین شیوه پیشگری و مقابله با آن‌ها خواهیم پرداخت.

<!--more-->

## سلب مسئولیت

شما با ادامه مطالعه این مطلب، موافقت کامل خود با این توافق نامه را اعلام می‌نمایید: 

{{< blockquote author="ممدوو بابائی" link="https://fa.babaei.net" title="لیسانس مطالب منتشر شده در وب سایت" >}}
تمامی محتویات این وب سایت تحت مجوز <a rel="license" href="https://creativecommons.org/licenses/by-sa/3.0/deed.fa" target="_blank">(CC BY-SA 3.0) Creative Commons Attribution-ShareAlike 3.0 Unported License</a> منتشر شده است. همچنین، تمامی سورس کدهای منتشر شده در این وب سایت تحت لیسانس <a rel="license" href="http://opensource.org/licenses/MIT" target="_blank">MIT License</a> منتشر شده است، مگر آن که به صراحت ذکر شده باشد. تمامی محتویات ارائه شده صرفا جنبه آموزشی و اطلاعاتی داشته و فاقد هرگونه ضمانت، تعهد یا شرایطی از هر نوع می باشد. بایستی توجه نمود که اطلاعات عرضه شده حتی ممکن است دقیق و یا بروز نباشد. هرگونه اطمینان به و یا استفاده از محتویات یا منابع منتشر شده در این وب سایت با مسئولیت مخاطب بوده و نگارنده یا نگارندگان هیچ گونه مسئولیتی در مورد عواقب آن را نخواهند پذیرفت.
{{< /blockquote >}}

## ایمیل اسپوفینگ چیست؟

ایمیل اسپوفینگ روشی جهت ارسال ایمیل است که در آن آدرس فرستنده ایمیل به منظور مقاصد مختلف، جعل می‌شود. دلیل عمده این امر آن است که پروتکل‌های متداول ایمیل هیچ‌گونه مکانیسم استانداردی جهت احراز هویت ارسال کننده نیاندیشیده‌اند و هر سرویس‌دهنده ایمیل، خود روش خاصی در برخورد با این مسئله را پیش می‌گیرد.

## آیا با وجود شیوع این نوع حملات، واقعا راهکاری برای مقابله با آن‌ها اندیشیده نشده است؟

پروتکل‌ها و روش‌های متعددی نظیر [SPF](https://en.wikipedia.org/wiki/Sender_Policy_Framework)، [Sender ID](https://en.wikipedia.org/wiki/Sender_ID)، [DKIM](https://en.wikipedia.org/wiki/DomainKeys_Identified_Mail) و [DMARC](https://en.wikipedia.org/wiki/DMARC) جهت مبارزه با ایمیل اسپوفینگ توسعه داده شده‌اند که جهت افزایش امنیت می‌توان تمامی آن‌ها را مجزا یا با یکدیگر به شکل همزمان به کار گرفت. متاسفانه علیرغم کارآمد بودن این پروتکل‌ها، به دلیل توسعه مستقل این استانداردها از پروتکل‌های اصلی و متداول ایمیل، هنوز بخش عمده سرویس‌‌دهنده‌های ایمیل این پروتکل‌ها و روش‌ها را پیاده سازی ننموده‌اند.

## ایمیل اسپوفینگ چگونه انجام می‌شود؟

حملات ایمیل اسپوفینگ معمولا به دو روش انجام می‌شود:

{{< codeblock lang="plain" >}}
$ telnet localhost smtp

Trying ::1...
telnet: connect to address ::1: Connection refused
Trying 127.0.0.1...
Connected to mail.example.org.
Escape character is '^]'.
220 mail.example.org ESMTP Postfix
HELO google.com
250 mail.example.org
mail from: sender@example.org
250 2.1.0 Ok
rcpt to: recipient@example.org
250 2.1.5 Ok
data
354 End data with <CR><LF>.<CR><LF>
Subject: Hello from Mamadou

Hey, what's up?

We should meet up for a coffee this week.

Your friend,
Mamadou
.
250 2.0.0 Ok: queued as D844C161902
quit
221 2.0.0 Bye
Connection closed by foreign host.
{{</ codeblock >}}





