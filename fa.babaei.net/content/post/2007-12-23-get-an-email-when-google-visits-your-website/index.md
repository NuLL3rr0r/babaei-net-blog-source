+++
title = "چه زماني گوگل به وب سايت شما سركشي مي كند"
slug = "get-an-email-when-google-visits-your-website"
date = 2007-12-23T20:49:00Z
tags = [ ".NET", ".NET Framework", "ASP.NET", "C#", "FreeBSD", "GNU", "Google", "HTML", "Linux", "Mono", "Perl", "Unix" ]
aliases = [ "/blog/2007/12/23/get-an-email-when-google-visits-your-website/" ]
+++

#### چكیده ####

در اين مقاله شاهد تحليل نحوه ي سركشي گوگل به يك وب سايت جهت استخراج اطلاعاتي مانند صفحه ي درخواست شده توسط گوگل، تشخيص اينكه صفحه در كدام سرور گوگل ذخيره شده است به علاوه ي زمان دسترسي گوگل به آن صفحه خواهيم بود.

همچنين اين اطلاعات با ارسال ايميلي در اختيار مدير وب سايت قرار خواهد گرفت.

<!--more-->

#### مقدمه ####

شايد به عنوان مدير يك وب سايت اين سوال برايتان مطرح باشد: "چگونه مي توان بر دسترسي گوگل به صفحات يك وب سايت نظارت داشت؟". به هر حال اكثر مواقع ايده درخور توجهي بدين منظور وجود ندارد (بسيار خب؛ از Google Webmaster tools[^1] به عنوان موثرترين پاسخ موجود صرفنظر مي كنيم! شكي نيست كه اين سرويس ابزارهاي مفيد و قدرتمندي را در جهت شناساندن هرچه صحيح تر وب سايت ها به گوگل در اختيار مديران آن ها قرار خواهد داد. اما كاستي هائي در اين سرويس نهفته است كه در ادامه بدان خواهيم پرداخت.).

در ادامه فرآيند ايجاد سرويسي كاملا سفارشي به منظور نظارت بر سركشي گوگل به تك تك صفحات يك وب سايت را بررسي مي نمائيم. اين سرويس داراي شرايط ذيل مي باشد:

- تشخيص صفحه ي درخواست شده توسط گوگل – اين قابليت در GWt پشتيباني مي شود –
- شناسائي سروري كه در نهايت صفحه موردنظر گوگل جهت استفاده هاي بعدي در آن ذخيره خواهد شد (در واقع كدام سرور گوگل صفحه شما را ذخيره مي نمايد) – اين قابليت در GWt پشتيباني نمي شود –
- تشخيص تاريخ و ساعتي كه گوگل به صفحه مراجعه نموده است – GWt فقط تاريخ را در اختيارتان قرار مي دهد –
- در جريان قرار دادن مدير وب سايت توسط ارسال ايميل – اين قابليت به هيچ وجه در GWt پشتيباني نمي شود، به اين دليل كه اگر قرار بود گوگل، مديران وب سايت ها را توسط ايميل در جريان قرار دهد بايستي از يك Spammer در طول روز بيشتر فعاليت داشته باشد! –

البته در اين جا خاطر نشان مي شود كه مي توان اطلاعات كشف شده را در يك فايل گزارشات، فايل XML و يا پايگاه داده ها جهت ايجاد گزارشات جامع و استفاده هاي بعدي ذخيره نمود. بدليل پيچيده شدن مطلب از آن صرفنظر مي نمائيم.

#### تشريح مسئله و راه حل آن ####

بسيار خب، چگونه مي توان دست به شناسائي بازديدكنندگان وب سايت ها زد؟ آيا تا به حال به اين موضوع فكر كرده ايد؟

راه حل بسيار ساده است؛ زماني كه يك در خواست HTTP از طرف بازديد كننده وب سايت – خواه يك مرورگر وب پيشرفته مانند Firefox باشد، يا يك مروگر متني مانند Lynx، يا حتي يك روبوت يا جستجو گر وب باشد – مطرح مي شود به همراه درخواست، جهت دريافت صفحه ي وب بايستي اقدام به ارسال اطلاعاتي جهت معرفي خود به وب سرور بنمايد در غير اينصورت وب سرور هيچگونه اطلاعاتي را در اختيار او قرار نخواهد داد.

و اما اين اطلاعات دريافتي چگونه توسط صفحه وبي كه در وب سرور اجرا خواهد شد، قابل دسترسي مي باشد؟ واقعيت اين است كه اين اطلاعات در فضائي با عنوان متغيرهاي محيطي[^2] وب سرور دخيره خواهند شد، و توسط هر برنامه ائي كه در وب سرور اجرا مي شود قابل دسترسي مي باشند. بسيار خب جهت كسب اطلاعات، كافي است دست به شناسائي و استفاده از اين متغيرهاي محيطي بزنيم.

#### كسب اطلاعات راجع به بازديد كننده وب سايت ####

بسيار خب؛ قبل از اينكه به سراغ كدهاي تشخيص مرورگرها و روبوت ها توسط متغيرهاي محيطي برويم، مي خواهيم با عملكرد مرورگرها جهت معرفي خود به سرور آشنا شويم. براي اين كار از فايل index.html واقع در پوشه ي GoolgebotDetector استفاده مي نمائيم.[^3]

در اين فايل كدي به زبان JavaScript بشرح ذيل قرار دارد:

{{< highlight html >}}
<script type="text/javascript">
    for (i in navigator)
        document.write(i + ": " + navigator[i] + "<br />");
</script>
{{< /highlight >}}

توجه داشته باشيد كه اين كد در سمت Client اجرا خواهد شد و مستقيما از مرورگر اطلاعات موردنظر را استخراج مي نمايند. به هر حال در صورت اجراي آن، احتمالا با چيزي شبيه به آنچه كه در ادامه خواهد آمد مواجه خواهيد شد:

```
platform: Win32
appCodeName: Mozilla
appName: Netscape
appVersion: 5.0 (Windows; en-US)
language: en-US
mimeTypes: [object MimeTypeArray]
oscpu: Windows NT 6.0
vendor:
vendorSub:
product: Gecko
productSub: 20071127
plugins: [object PluginArray]
securityPolicy:
userAgent: Mozilla/5.0 (Windows; U; Windows NT 6.0; en-US; rv:1.8.1.11) Gecko/20071127 Firefox/2.0.0.11
cookieEnabled: true
onLine: true
javaEnabled: function javaEnabled() { [native code] }
taintEnabled: function taintEnabled() { [native code] }
buildID: 2007112718
preference: function preference() { [native code] }
registerContentHandler: function registerContentHandler() { [native code] }
registerProtocolHandler: function registerProtocolHandler() { [native code] }
```

در واقع اين ها اطلاعاتي است كه در ساختار DOM[^4] مرورگر وجود دارد و با JavaScript اقدام به استخراج آن نموديم. اما سوال اينجاست كه آيا مرورگر جهت بازديد هر صفحه تمامي اين اطلاعات را به وب سرور ارائه مي نمايند؟ قطعا پاسخي جز ‘خير’ براي آن وجود ندارد. تنها چيزي كه مرورگر براي وب سرور همراه با درخواست دريافت صفحه ارسال مي نمايد مقدار پارامتر userAgent مي باشد كه در خروجي مثال بالا مشاهده نموديد. اجازه دهيد مقدار اين پارامتر را در مرورگرهاي مختلف بررسي كنيم:

|                                                                                                                                                           |                    |
|:----------------------------------------------------------------------------------------------------------------------------------------------------------|:-------------------|
| Mozilla/5.0 (Windows; U; Windows NT 6.0; en-US; rv:1.8.1.11) Gecko/20071127 Firefox/2.0.0.11                                                              | Firefox            |
| Mozilla/5.0 (Windows; U; Windows NT 6.0; en-US) AppleWebKit/523.12.9 (KHTML, like Gecko) Version/3.0 Safari/523.12.9                                      | Safari             |
| Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 6.0; Avant Browser; SLCC1; .NET CLR 2.0.50727; Media Center PC 5.0; .NET CLR 3.0.04506; .NET CLR 3.5.21022) | Internet Explorer  |
| Opera/9.24 (Windows NT 6.0; U; en)                                                                                                                        | Opera              |
| Mozilla/5.0 (Windows; U; Windows NT 6.0; en-US; rv:1.8.1.11) Gecko/20071206 Firefox/2.0.0.11 Flock/1.0.3                                                  | Flock              |
| Mozilla/5.0 (Windows; U; Windows NT 6.0; en-US; rv:1.8.1.10pre) Gecko/20071127 Firefox/2.0.0.10 Navigator/9.0.0.4                                         | Netscape Navigator |
| Mozilla/5.0 (Windows; U; Windows NT 6.0; en-US; rv:1.8.1.11) Gecko/20071128 SeaMonkey/1.1.7                                                               | SeaMonkey          |
| Mozilla/5.0 (Windows; U; Windows NT 6.0; en-US; rv:1.7.13) Gecko/20060414                                                                                 | Mozilla            |
| Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 6.0; Avant Browser; SLCC1; .NET CLR 2.0.50727; Media Center PC 5.0; .NET CLR 3.0.04506; .NET CLR 3.5.21022) | Deepnet Explorer   |
| Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 6.0; Avant Browser; SLCC1; .NET CLR 2.0.50727; Media Center PC 5.0; .NET CLR 3.0.04506; .NET CLR 3.5.21022) | Avant Browser      |
| Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 6.0; Avant Browser; SLCC1; .NET CLR 2.0.50727; Media Center PC 5.0; .NET CLR 3.0.04506; .NET CLR            | Maxthon            |

<br />

نكته ي قابل توجه در جدول بالا اين است كه پارامتر userAgent هر مرورگر بخوبي نماياننده ي مشخصات مرورگر مانند نام، نسخه و نسل آن، حتي نام و نسخه سيستم عامل، به علاوه زبان پيش فرض سيستم مي باشد. همچنين در مرورگري مانند IE نسخه .NET Framework مورد استفاده در سيستم كاربر نيز نمايان مي شود. نكته ديگري كه شايان ذكر مي باشد اين است كه تمامي مرورگرهاي مدرن امروزي بر اساس HTML Rendering Engine به چهار دسته كلي تقسيم مي شوند:

- Gecko
- MSIE
- KHTML
- Opera

اين بدان معناست كه يك صفحه ي وب در مرورگرهاي هم نسل، اكثر اوقات به شكل كاملا يكسان رويت خواهند شد.

توجه داشته باشيد برخي مرورگرها برخي مواقع خود را مرورگر ديگري اعلام مي نمايند اين ممكن است بدين دليل باشد كه كد منبع اين مرورگرها يكسان باشد مانند Flock و Netscape Navigator كه بر اساس كد Firefox توسعه داده شده اند و يا مانند Opera كه به دلايلي خاص تا قبل از نسخه 9، خود را Internet Explorer معرفي مي نمايد – البته اين مرورگر در نسخ بسيار قديمي تر خود در واقع فقط پوسته اي براي IE بوده است –. به عنوان مثالي ديگر Google در سرويس Gmail خود از مروگر Konqueror بدليل ضعف در پشتيباني از شي پايه AJXA تحت عنوان XMLHTTPRequest، پشتيباني نمي نمايد. توسعه دهندگان اين مرورگر در نسخ جديدتر آن كلمه like Gecko را به userAgent آن اضافه نموده اند تا از فيلتري كه شركت Google براي اين دسته از مرورگرها در نظر گرفته است عبور نمايند.[^5]

در هر صورت آنچه كه واضح است اين است كه هر بازديدكننده از وب سايت بايستي خود را به وب سرور معرفي نمايد. ديديم كه مرورگرها اين كار را توسط پارامتر userAgent در ساختار DOM خود انجام مي دهند. گوگل هم براي دستيابي به صفحات وب سايت ها از نرم افزاري تحت عنوان Googlebot استفاده مي نمايد. در واقع Googlebot يك مرورگر متني است و اين نرم افزار قابليت اجراي جاوا اسكريپت و يا دستورات CSS، همچنين نمايش تصاوير را نخواهد داشت. جهت درك اين موضوع مي توانيد صفحات وب سايتان را توسط يك مرورگر متني مانند Lynx[^6] مرور نمائيد. اين عمل مزيت هائي بدنبال خواهد داشت. ممكن است صفحات وب شما توسط AJAX – از پايگاه داده ها – بارگذاري شوند و يا كدهاي CSS و جاوا اسكريپت موجود در صفحات در موتورهاي جستجو ظاهر شوند. توسط اين مرورگر متني مي توانيد رفتار گوگل را با وب سايتان مشاهده نمائيد و تكنيك هائي را جهت رفع اين مسائل بكار گيريد.

به هر حال آنچه كه مسلم است Googlebot نيز داراي يك userAgent مي باشد. و هم اكنون شما با آگاهي از مقادير آن مي توانيد پيش دستي كرده و به گوگل خوش آمد بگوئيد!

اطلاعاتي كه در Googlebot userAgent يافت مي شوند به قرار زير مي باشد:

```
Mozilla/5.0 (compatible; Googlebot/2.1; +http://www.google.com/bot.html)
```

البته شما با JavaScript قادر به بدست آوردن اطلاعات فوق نخواهيد بود، بلكه قبل از ارسال پاسخ به سوي مرورگر، در وب سرور قادر به چك كردن اطلاعات ذخيره شده در متغيرهاي محيطي، جهت شناسائي نوع مرورگر خواهيد بود.

### بدست آوردن متغيرهاي محيطي ###

بسيار خب؛ بهتر است دست بكار شويم. در سرورهاي Windows مي توانيد از كد ASP.NET – تحت عنوان index.aspx – و در سرورهاي Linux مي توانيد از كد Perl – تحت عنوان index.pl – استفاده نمائيد. لازم بذكر است كه كد index.aspx نيازمند اسكريپت واقع در index.cs كه به زبان C# مي باشد، است. ميزان خوانائي كدها به دليل اين تفكيك در كد ASP.NET بسيار بالا مي باشد؛ چرا كه كدهاي HTML در فايل index.aspx و بخش عمده ي كدهاي C# در فايل index.cs قرار دارد.

در Perl/CGI يك متغير از نوع Hash، تحت عنوان %ENV مسئول نگهداري متغيرهاي محيطي مي باشد و در ASP.NET شي Request.ServerVariables اين عمل را انجام مي دهد.

در كد index.pl خطوط زير را جستجو نمائيد:

{{< highlight perl >}}
my $result;
$result = qq(<table border="0" cellpadding="10">);
foreach (keys %ENV) {
    $result .= qq(<tr valign="top">);
    $result .= qq(<td>);
    $result .= qq(<strong>$_</strong>:);
    $result .= qq(</td>);
    $result .= qq(<td>);
    $result .= qq(<em>$ENV{$_}</em>);
    $result .= qq(</td>);
    $result .= qq(</tr>);
}
$result .= qq(</table>);
print "$result";
{{< /highlight >}}

و در كد index.aspx خطوط زير را جستجو نمائيد:

{{< highlight csharp >}}
<%
    string[] server = Request.ServerVariables.AllKeys;

    System.Text.StringBuilder str = new StringBuilder();
    str.Append("<table border=\"0\" cellpadding=\"10\">");

    foreach (string i in server)
    {
        str.Append("<tr valign=\"top\">");
        str.Append("<td>");
        str.Append("<strong>" + i + "</strong>" + ":");
        str.Append("</td>");
        str.Append("<td>");
        str.Append("<em>" + Request.ServerVariables[i] + "</em>");
        str.Append("</td>");
        str.Append("</tr>");
    }

    str.Append("</table>");
    Response.Write(str);
%>
{{< /highlight >}}

هر دو كد عمل يكساني را انجام مي دهند و آن چاپ متغيرهاي محيطي به همراه مقاديرشان، بصورت منظم و قالب بندي شده در صفحه ي وب مي باشد. بسيار خب، دست بكار شويد و كدها را در محيط وب سرور اجرا نمائيد.

حاصل اجراي كدها شگفت انگيز خواهد بود، در حال حاضر شما بسياري از اطلاعات مربوط به سرور را در اختيار داريد. نكته اي كه بايستي در نظر گرفت اينست كه اين اطلاعات در وب سرورهاي مختلف و از سروري به سرور ديگر متفاوت مي باشند، پس در استفاده از آن ها هشيار باشيد.

اين مسئله گاه پيچيده تر نيز مي نمايد. براي مثال، علاوه بر اين كه اين متغيرهاي محيطي از سروري به سرور ديگر متفاوت هستند، گاه تنظيم آن ها به نحوه دسترسي به خود اسكريپت نيز بستگي دارد. فرضا متغير محيطي CONTENT_LENGTH تنها زماني تنظيم مي گردد كه از روش POST براي ارسال اطلاعات به سرور استفاده مي شود. و يا متغير محيطي HTTP_REFERER تنها زماني تنظيم مي گردد كه اسكريپت توسط كيلك بر روي يك لينك و يا دكمه submit اجرا شده باشد.

در نهايت توجه داشته باشيد كه متغيرهاي محيطي تماما با حروف بزرگ به همراه كاراكتر underline به عنوان جدا كننده به كار مي روند.

### تشريح كد ASP.NET ###

كد ASP.NET همان طور كه قبلا اشاره شد به دو بخش تفكيك شده است.

- index.aspx جهت كدهاي HTML و محتويات صفحه
- index.cs جهت درج و اجراي كد  C#

در ادامه به تشريح كد index.cs خواهيم پرداخت.

قبل از هرچيزي با اعلان using، اقدام به وارد نمودن فضاهاي نامي System، System.Net.Mail و System.Text مي نمائيم. توجه داشته باشيد بدليل استفاده از System.Net.Mail كد حاضر تنها در سرورهائي اجرا خواهد شد كه با .NET Framework نسخه 2.0 و يا بالاتر سازگار باشند.

جهت اجراي كدها در هر بار اجراي صفحه بايستي آن ها را در رخداد Page_Load() صفحه قرار دارد.

ابتدا اقدام به تعريف متغيرهاي اساسي برنامه و كسب مقادير مورد نياز برنامه از متغيرهاي محيطي مي نمائيم. براي اين كار متغيري به نام browser تعريف مي نمائيم و با استفاده از متغير محيطي HTTP_USER_AGENT اطلاعات مرورگر را بدست مي آوريم. سپس با استفاده از متغير محيطي REMOTE_ADDR آدرس IP بازديدكننده صفحه را بدست خواهيم آورد. در نهايت قصد بدست آوردن آدرس صفحه ي درخواست شده را داريم. اين صفحه ممكن است به شكل http://www.somedomain.com/example.aspx و يا http://www.somedomain.com/example.aspx?req=test&id=1 درخواست شده باشد. بنابراين نيازمند تركيب چند متغير محيطي مي باشيم. با استفاده از HTTP_HOST نام دامين، با استفاده از URL نام صفحه ي موردنظر، همچنين با استفاده از QUERY_STRING پارامترهاي ارسالي توسط متد GET را بدست خواهيم آورد، آنگاه تركيب آن ها را در متغيري با عنوان url ذخيره مي نمائيم.

{{< highlight csharp >}}
string browser = Request.ServerVariables["HTTP_USER_AGENT"];
string ip = Request.ServerVariables["REMOTE_ADDR"];
string url = String.Concat("http://", Request.ServerVariables["HTTP_HOST"], Request.ServerVariables["URL"], "?", Request.ServerVariables["QUERY_STRING"]);
/*
* if IIS 7.0
* string url = String.Concat("http://", Request.ServerVariables["HTTP_HOST"], Request.ServerVariables["HTTP_URL"]);
*/
{{< /highlight >}}

البته همانطور كه از توضيحات درون كدها به نظر مي رسد، چنانچه از IIS7.0 به عنوان وب سرور استفاده نمائيد اين مراحل اندكي ساده تر مي نمايند. در اين مورد شما با استفاده از HTTP_URL، قادر به بدست آوردن صفحه درخواست شده همراه با پارامترهاي ارسالي خواهيد بود. همچنين برخي مواقع روش هاي جايگزيني جهت طي نمودن فرآيندي خاص موجود مي باشد. براي مثال مي توان به جاي استفاده از HTTP_HOST از SERVER_NAME، به جاي URL از PATH_INFO و يا SCRIPT_NAME استفاده نمود.

در خطوط بعدي برنامه اقدام به بدست آوردن زمان فعلي سرور مي نمائيم:

{{< highlight csharp >}}
DateTime dt = DateTime.Now;
string date = dt.ToString();
{{< /highlight >}}

در نهايت ادامه اجراي كدها منوط به وجود كلمه ي Googlebot در رشته ي بدست آمده در متغير browser مي باشد:

{{< highlight csharp >}}
if (browser.Contains("Googlebot"))
{
    // some code
}
{{< /highlight >}}

چنانچه در رشته ي browser مقدار Googlebot موجود باشد، شك نكنيد كه در حال حاضر صفحه ي وب شما ميزبان موتور جستجوي گوگل است در غير اينصورت روال اجراي برنامه به فايل index.aspx باز مي گردد و متعاقبا محتويات صفحه به سوي مرورگر ارسال خواهد شد.

چنانچه حضور Googlebot تشخيص داده شد، نوبت به مطلع نمودن مدير وب سايت از طريق ارسال ايميل مي رسد. ابتدا متغير هاي to، from، subject را از نوع رشته به ترتيب جهت ذخيره دريافت كننده، فرستنده و موضوع نامه تعريف و مقدار دهي مي نمائيم. سپس متغير body را بصورت يك كپي از كلاس StringBuilder تعريف مي نمائيم. مي خواهيم قالب نامه به صورت كدهاي HTML باشد، بنابراين شروع به توليد آن مي كنيم:

{{< highlight csharp >}}
string to = "adminid@somedomain.com";
string from = "someid@somedomain.com";
string subject = "Googlebot Deteced";

StringBuilder body = new StringBuilder();

body.Append("<br /><br /><br /><strong>Page Crawled By Googlebot</strong>");
body.Append("<br /><blockquote>{0}</blockquote>");

body.Append("<br /><br /><strong>By Google Server At</strong>");
body.Append("<br /><blockquote>{1}</blockquote>");

body.Append("<br /><br /><strong>Crawl Date</strong>");
body.Append("<br /><blockquote>{2}</blockquote>");
{{< /highlight >}}

دقت نمائيد كه در نهايت Place Holder هاي {0}، {1} و {2} به ترتيب با متغيرهاي url، ip و date جايگزين خواهند شد.

{{< highlight csharp >}}
string msgBody = String.Format(body.ToString(), url, ip, date);
{{< /highlight >}}

متغير msgBody متن نهائي نامه ارسالي خواهد بود. بسيار خب، بايستي مقدمات ارسال ايميل را فراهم نمود. پيش از انجام هر كاري جهت جلوگيري از Crash نمودن اجراي صفحه با استفاده از ساختار try – catch – finally اقدام به كنترل  و مديريت خطاها مي نمائيم. بسته به نوع خطائي كه پيش مي آيد مي توان قسمت catch را جهت انجام تمهيداتي در نظر گرفت. و در پايان از قسمت finally براي اجراي دستوراتي خاص چه در زمان موفقيت برنامه، چه در زمان ايجاد خطا استفاده نمود.

{{< highlight csharp >}}
try
{
    // Send Mail Section
}
catch (FormatException ex)
{
    // TODO: some statements
}
catch (SmtpException ex)
{
    // TODO: some statements
}
catch (Exception ex)
{
    // TODO: some statements
}
finally
{
    // TODO: some statements
}
{{< /highlight >}}

بسيار خب مي پردازيم به ارسال ايميل؛ در نظر داشته باشيد جهت ارسال ايميل در دنياي .NET شما نيازمند حق دسترسي به يك سرور SMTP مي باشيد. معمولا با خريد host، يك سرور SMTP در اختيار شما قرار خواهد گرفت. در هر صورت جهت يكپارچگي و كاربردي بودن كد تحت هر شرايطي – حتي در localhost – مي توان از يك اكانت Gmail بهره جست. پس قبل از ادامه، به فكر تهيه ي يك Gmail Account[^7] باشيد، در غير اينصورت قسمت پاياني كد قابل اجرا نخواهد بود (البته مزيت ديگر استفاده از Gmail اينست كه يك كپي از نامه هاي ارسالي توسط برنامه، در پوشه Sent اكانت مورد استفاده، آرشيو خواهد شد).

{{< highlight csharp >}}
using (MailMessage msg = new MailMessage(from, to, subject, msgBody))
{
    msg.BodyEncoding = Encoding.UTF8;
    msg.SubjectEncoding = Encoding.UTF8;
    msg.IsBodyHtml = true;
    msg.Priority = MailPriority.High;

    SmtpClient smtp = new SmtpClient("smtp.gmail.com", 587);
    smtp.Credentials = new System.Net.NetworkCredential("yourid@gmail.com", "pw");
    smtp.EnableSsl = true;
    smtp.Send(msg);
}
{{< /highlight >}}

دقت نمائيد كه در شرايط معمول از پورت شماره 25 جهت ارسال ايميل استفاده مي شود. اما در Gmail مي توانيد از يكي از پورت هاي 587 و يا 465 استفاده نمائيد.

در پايان فراموش نكنيد به جاي yourid@gmail.com، اكانت Gmail تان  و به جاي pw، كلمه ي عبور آن را وارد نمائيد.


### تشريح كد PERL ###

با توجه به تشريح كامل كد ASP.NET، به نظر مي رسد كد PERL نيازمند توضيحات مفصل نمي باشد. بزرگترين تفاوت موجود در حال حاضر بهينه بودن كد ASP.NET جهت اجرا در وب سرور IIS و بهينه بودن كد Perl به منظور اجرا در وب سرور Apache مي باشد.

در كد Perl جهت بدست آوردن نام صفحه درخواستي از SCRIPT_NAME استفاده مي شود. اما مي توان از REQUEST_URI جهت بدست آوردن نام صفحه به همراه پارامترهاي ارسالي با متد GET استفاده نمود.

{{< highlight perl >}}
my $browser = $ENV{'HTTP_USER_AGENT'};
my $ip = $ENV{'REMOTE_ADDR'};
my $url = "http://" . $ENV{'HTTP_HOST'} . $ENV{'REQUEST_URI'};
my $date = localtime(time);
{{< /highlight >}}

سپس اقدام به جستجو در رشته $browser به دنبال Googlebot مي نمائيم و در صورت تائيد، كد مربوط به ارسال ايميل به سوي مدير وب سايت، اجرا مي شود. در غير اينصورت صفحه روال عادي خود را طي خواهد نمود.

{{< highlight perl >}}
if ($browser =~ m/Googlebot/) {
    my $to = qq("Admin Name" <adminid\@somedomain.com>);
    my $from =  qq("Your Name" <someid\@somedomain.com>);
    my $subject =  "Googlebot Deteced";
    my $body;

    $body .= "<br /><br /><br /><strong>Page Crawled By Googlebot</strong>";
    $body .= "<br /><blockquote>$url</blockquote>";
    $body .= "<br /><br /><strong>By Google Server At</strong>";
    $body .= "<br /><blockquote>$ip</blockquote>";
    $body .= "<br /><br /><strong>Crawl Date</strong>";
    $body .= "<br /><blockquote>$date</blockquote>";

    open (MAIL, "|/usr/lib/sendmail -t");

    print MAIL "To: $to\n";
    print MAIL "From: $from\n";
    print MAIL "Subject: $subject\n";
    print MAIL "Content-type: text/html; charset=utf-8\n\n";
    print MAIL "$body";

    close(MAIL);
}
{{< /highlight >}}

تنها نكته اي كه بايستي در مورد كد Perl خاطر نشان شد اينست كه ممكن است مسير برنامه ارسال ايميل در سرور مورد نظر شما با آنچه كه در كد Perl آمده است متفاوت باشد كه بايستي اقدام به ويرايش آن نمائيد.

{{< highlight perl >}}
|/usr/lib/sendmail -t
{{< /highlight >}}

#### جمع بندی ####

نكته اي كه  مستلزم يادآوري است، اينست كه كد حاضر تنها در صفحاتي قابل اجرا خواهد بود كه در آن درج شده باشد. البته هم در Perl و هم در ASP.NET روشهائي به منظور به اشتراك گذاشتن كدها در ميان ساير صفحات موجود مي باشد كه تشريح آن ها جز طولاني تر و پيچيده تر شدن مطلب حاضر نتيجه اي در بر نخواهد داشت.

يادآور مي شويم، كد حاضر تنها نمونه اي از تشخيص مرورگرها و موتورهاي جستجو مي باشد. كاركرد اين كدها به موارد ياد شده در اين مقاله محدود نمي باشد. براي مثال وب سايت نگارنده (در زمان تهیه این مقاله) از تكنولوژي Ajax استفاده مي نمايد. كه همين موضع باعث ايجاد مسائلي بر سر راه موتورهاي جستجو جهت پيدا نمودن ساير صفحات وب سايت خواهد بود. اما با تكنيكي مشابه صفحات با تركيب و چيدمان خاصي جداي از آنچه كاربران سايت مشاهده مي نمايند در اختيار موتورهاي جستجو قرار مي گيرد.

به هرحال، در نظر داشته باشيد که: «خلاقيت؛ شرط اول، جهت ورود به دنياي وب مي باشد.»


[دریافت سورس کد کامل از GitLab](https://gitlab.com/NuLL3rr0r/babaei.net/tree/master/2007-12-23-get-an-email-when-google-visited-your-website)

[دریافت سورس کد کامل از GitHub](https://github.com/NuLL3rr0r/babaei.net/tree/master/2007-12-23-get-an-email-when-google-visited-your-website)


{{< codeblock lang="html" title="index.html" >}}
<!--
  (The MIT License)

  Copyright (c) 2007 Mohammad S. Babaei

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
<title>Browser Detection Using DOM</title>
</head>

<body>
<script type="text/javascript">
    for (i in navigator)
        document.write(i + ": " + navigator[i] + "<br />");
</script>
</body>
</html>
{{< /codeblock >}}

{{< codeblock lang="perl" title="index.pl" >}}
#!/usr/bin/perl

#  (The MIT License)
#
#  Copyright (c) 2007 Mohammad S. Babaei
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

my $browser = $ENV{'HTTP_USER_AGENT'};
my $ip = $ENV{'REMOTE_ADDR'};
my $url = "http://" . $ENV{'HTTP_HOST'} . $ENV{'REQUEST_URI'};
my $date = localtime(time);

if ($browser =~ m/Googlebot/) {
    my $to = qq("Admin Name" <adminid\@somedomain.com>);
    my $from =  qq("Your Name" <someid\@somedomain.com>);
    my $subject =  "Googlebot Deteced";
    my $body;

    $body .= "<br /><br /><br /><strong>Page Crawled By Googlebot</strong>";
    $body .= "<br /><blockquote>$url</blockquote>";
    $body .= "<br /><br /><strong>By Google Server At</strong>";
    $body .= "<br /><blockquote>$ip</blockquote>";
    $body .= "<br /><br /><strong>Crawl Date</strong>";
    $body .= "<br /><blockquote>$date</blockquote>";

    open (MAIL, "|/usr/lib/sendmail -t");

    print MAIL "To: $to\n";
    print MAIL "From: $from\n";
    print MAIL "Subject: $subject\n";
    print MAIL "Content-type: text/html; charset=utf-8\n\n";
    print MAIL "$body";

    close(MAIL);
}

print "Content-Type: text/html; charset=utf-8\n\n";

print "<html>";
print "<head>";
print qq(<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />);
print "<title>Googlebot Listener</title>";
print "</head>";
print "<body>";
print "<h2>Hello Googlebot</h2>";
print qq(<p><strong><em>When googlebot comes (if it does!) to pages that contains this code, you get an e-mail sent to the address you specify.</strong></em></p>
);
print "<br /><br />";
print "<h2>Server Variables</h2>";
print "<blockquote>";

my $result;

$result = qq(<table border="0" cellpadding="10">);

foreach (keys %ENV) {
    $result .= qq(<tr valign="top">);
    $result .= qq(<td>);
    $result .= qq(<strong>$_</strong>:);
    $result .= qq(</td>);
    $result .= qq(<td>);
    $result .= qq(<em>$ENV{$_}</em>);
    $result .= qq(</td>);
    $result .= qq(</tr>);
}

$result .= qq(</table>);

print "$result";

print "</blockquote>";
print "</body>";
print "</html>";
{{< /codeblock >}}

{{< codeblock lang="csharp" title="index.aspx" >}}
<!--
  (The MIT License)

  Copyright (c) 2007 Mohammad S. Babaei

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


<%@ Page Language="C#" AutoEventWireup="true" CodeFile="index.cs" Inherits="GooglebotDetector" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>Googlebot Listener</title>
</head>
<body>
<h2>Hello Googlebot</h2>
<p><strong><em>When googlebot comes (if it does!) to pages that contains this code, you get an e-mail sent to the address you specify.</strong></em></p>
<br /><br />
<h2>Server Variables</h2>
<blockquote>
<%
    string[] server = Request.ServerVariables.AllKeys;
    System.Text.StringBuilder str = new StringBuilder();

    str.Append("<table border=\"0\" cellpadding=\"10\">");

    foreach (string i in server)
    {
        str.Append("<tr valign=\"top\">");
        str.Append("<td>");
        str.Append("<strong>" + i + "</strong>" + ":");
        str.Append("</td>");
        str.Append("<td>");
        str.Append("<em>" + Request.ServerVariables[i] + "</em>");
        str.Append("</td>");
        str.Append("</tr>");
    }

    str.Append("</table>");

    Response.Write(str);
%>
</blockquote>
</body>
</html>
{{< /codeblock >}}

{{< codeblock lang="csharp" title="index.cs" >}}
/// <summary>
///   (The MIT License)
///
///   Copyright (c) 2007 Mohammad S. Babaei
///
///   Permission is hereby granted, free of charge, to any person obtaining a copy
///   of this software and associated documentation files (the "Software"), to deal
///   in the Software without restriction, including without limitation the rights
///   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
///   copies of the Software, and to permit persons to whom the Software is
///   furnished to do so, subject to the following conditions:
///
///   The above copyright notice and this permission notice shall be included in
///   all copies or substantial portions of the Software.
///
///   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
///   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
///   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
///   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
///   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
///   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
///   THE SOFTWARE.
/// </summary>


using System;
using System.Net.Mail;
using System.Text;

public partial class GooglebotDetector : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {
        string browser = Request.ServerVariables["HTTP_USER_AGENT"];
        string ip = Request.ServerVariables["REMOTE_ADDR"];
        string url = String.Concat("http://", Request.ServerVariables["HTTP_HOST"], Request.ServerVariables["URL"], "?", Request.ServerVariables["QUERY_STRING"]);
        /*
         * if IIS 7.0
         * string url = String.Concat("http://", Request.ServerVariables["HTTP_HOST"], Request.ServerVariables["HTTP_URL"]);
        */
        DateTime dt = DateTime.Now;
        string date = dt.ToString();

        if (browser.Contains("Googlebot"))
        {
            string to = "adminid@somedomain.com";
            string from = "someid@somedomain.com";
            string subject = "Googlebot Deteced";

            StringBuilder body = new StringBuilder();

            body.Append("<br /><br /><br /><strong>Page Crawled By Googlebot</strong>");
            body.Append("<br /><blockquote>{0}</blockquote>");

            body.Append("<br /><br /><strong>By Google Server At</strong>");
            body.Append("<br /><blockquote>{1}</blockquote>");

            body.Append("<br /><br /><strong>Crawl Date</strong>");
            body.Append("<br /><blockquote>{2}</blockquote>");

            string msgBody = String.Format(body.ToString(), url, ip, date);

            try
            {
                using (MailMessage msg = new MailMessage(from, to, subject, msgBody))
                {
                    msg.BodyEncoding = Encoding.UTF8;
                    msg.SubjectEncoding = Encoding.UTF8;
                    msg.IsBodyHtml = true;
                    msg.Priority = MailPriority.High;

                    SmtpClient smtp = new SmtpClient("smtp.gmail.com", 587);
                    smtp.Credentials = new System.Net.NetworkCredential("yourid@gmail.com", "pw");
                    smtp.EnableSsl = true;
                    smtp.Send(msg);
                }
            }
            catch (FormatException ex)
            {
                // TODO: some statements
            }
            catch (SmtpException ex)
            {
                // TODO: some statements
            }
            catch (Exception ex)
            {
                // TODO: some statements
            }
            finally
            {
                // TODO: some statements
            }
        }
    }
}
{{< /codeblock >}}


#### منابع و ماخذ ####

<pre>
<a href="http://www.scriptygoddess.com/archives/2003/07/16/get-an-email-when-google-visits/" target="_blank">http://www.scriptygoddess.com/archives/2003/07/16/get-an-email-when-google-visits/</a>
<a href="http://www.codeproject.com/KB/cs/SendMailUsingGmailAccount.aspx" target="_blank">http://www.codeproject.com/KB/cs/SendMailUsingGmailAccount.aspx</a>
<a href="http://www.google.com/webmasters/tools/" target="_blank">http://www.google.com/webmasters/tools/</a>
<a href="http://www.w3c.org/" target="_blank">http://www.w3c.org/</a>
<a href="http://lynx.browser.org/" target="_blank">http://lynx.browser.org/</a>
<a href="https://mail.google.com/" target="_blank">https://mail.google.com/</a>
</pre>


[^1]: [http://www.google.com/webmasters/tools/](http://www.google.com/webmasters/tools/)

[^2]: Environment Variables

[^3]: تمامی كدهای استفاده شده در این مقاله در انتهای مطلب در قالب یک فایل فشرده قابل دریافت می باشد.

[^4]: Document Object Model – مشخصه ي كنسرسيوم جهاني وب ([http://www.w3c.org/](http://www.w3c.org/)) كه ساختار اسناد XML و HTML ديناميك را به روشي توصيه مي كند كه به وسيله ي مرورگر وب بتوان با آن ها كار كرد. در مدل شي سند – به اختصار DOM – ، هر سندي نه همچون مجموعه اي از لغات دنباله دار، بلكه به عنوان نوعي ساختار منطقي تعريف مي شود. DOM ابزاري است مورد استفاده براي تعريف سندي به شكل سلسله مراتبي و شبه درختي، و متشكل از گره هائي است كه در آن هر سندي يك شي مستقل بوده و شامل اشياي فرعي ديگري مانند تصاوير، لينك ها، لنگرگاه ها و ... است. برنامه ها و اسكريپت ها توسط DOM به اين اشيا دسترسي مي يابند تا جنبه هايي مانند ظاهر و رفتار آن ها را تغيير دهند. DOM وسيله اي براي افزودن عمق و همچنين فعل و انفعال به صفحات ايستاي وب است.

[^5]: فراموش نكنيد خود شما نيز توسط تكنيك هائي قادر به اعمال تغييراتي در شي userAgent براي هر مرورگري مي باشيد.

[^6]: [http://lynx.browser.org/](http://lynx.browser.org/)

[^7]: [https://mail.google.com/](https://mail.google.com/)
