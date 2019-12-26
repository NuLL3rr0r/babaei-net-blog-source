+++
title = "امنیت سایبری ۱۰۱ ویژه فعالان حقوق بشر، فعالان مدنی، فعالان سیاسی، روزنامه نگاران و براندازان: راهنمای نحوه عبور از فیلترینگ سنگین اینترنت در زمان اعتراضات در ایران با استفاده از تکنیک Domain Fronting و نرم‌افزارهای Tor و meek"
slug = "cybersecurity-101-domain-fronting-bypass-iran-internet-shutdown-using-tor-meek-pluggable-transport"
date = 2019-12-26T16:24:00+01:00
tags = [ "Censorship", "Cybersecurity", "FLOSS", "FreeBSD", "GNU", "LINUX", "meek", "Open Source", "Pluggable Transport", "Proxy", "Security", "Tor", "UNIX", "VPN" ]
toc = true
+++

{{< youtube XdENi20AjAY >}}

در این راهنمای تصویری به نحوه عبور از فیلترینگ سنگین اینترنت در زمان اعتراضات در ایران با استفاده از [تکنیک Domain Fronting](/blog/cybersecurity-101-domain-fronting/) و نرم‌افزارهای Tor و meek خواهیم پرداخت.

لینک منابع و دریافت نرم‌افزارهای مورد نیاز در ادامه مطلب.

* [پرسش و پاسخ در توییتر]()

* [مشاهده در اینستاگرام]()

* [مشاهده در تلگرام + تمامی فایل‌های موردنیاز برای نصب و راه‌اندازی در ویندوز و اندروید]()

<!--more-->

## سلب مسئولیت

شما با ادامه مطالعه این مطلب، موافقت کامل خود با این توافق نامه را اعلام می‌نمایید:

{{< blockquote author="ممدوو بابائی" link="https://fa.babaei.net" title="لیسانس مطالب منتشر شده در وب سایت" >}}
تمامی محتویات این وب سایت تحت مجوز <a rel="license" href="https://creativecommons.org/licenses/by-sa/3.0/deed.fa" target="_blank">(CC BY-SA 3.0) Creative Commons Attribution-ShareAlike 3.0 Unported License</a> منتشر شده است. همچنین، تمامی سورس کدهای منتشر شده در این وب سایت تحت لیسانس <a rel="license" href="http://opensource.org/licenses/MIT" target="_blank">MIT License</a> منتشر شده است، مگر آن که به صراحت ذکر شده باشد. تمامی محتویات ارائه شده صرفا جنبه آموزشی و اطلاعاتی داشته و فاقد هرگونه ضمانت، تعهد یا شرایطی از هر نوع می باشد. بایستی توجه نمود که اطلاعات عرضه شده حتی ممکن است دقیق و یا بروز نباشد. هرگونه اطمینان به و یا استفاده از محتویات یا منابع منتشر شده در این وب سایت با مسئولیت مخاطب بوده و نگارنده یا نگارندگان هیچ گونه مسئولیتی در مورد عواقب آن را نخواهند پذیرفت.
{{< /blockquote >}}

## لینک‌های دریافت

* [دریافت Tor برای سیستم‌عامل ویندوز](https://www.torproject.org/download/)

* [دریافت باینری ۳۲ و ۶۴ بیتی meek برای ویندوز](https://github.com/NuLL3rr0r/meek-iranprotests/releases)

* [دریافت مستقیم Tor Browser برای اندروید از وب‌سایت پروژه Tor](https://www.torproject.org/download/#android)

* [دریافت Tor Browser برای اندروید از گوگل پلی](https://play.google.com/store/apps/details?id=org.torproject.torbrowser&hl=en)
