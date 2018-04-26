+++
title = "طراحی و بكارگیری كیبورد فارسی مستقل از سیستم عامل"
slug = "cross-platform-persian-keyboard"
date = 2008-02-08T00:00:00+03:30
tags = [ ".NET", ".NET Framework", "C#", "Cross Platform", "Mono", "Persian", "Windows" ]
aliases = [ "/blog/2008/02/08/cross-platform-persian-keyboard/" ]
+++

#### چكیده ####

در  این مقاله اقدام به طراحی و پیاده سازی كیبورد فارسی مستقل از سیستم عامل با قابلیت به كارگیری به صورت مجزا برای هر یك از آیتم های فرم موردنظر می پردازیم.

همچنین كد موردنظر به صورت تابعی جهت بكارگیری آسان تر ارائه خواهد شد.

<!--more-->

#### مقدمه ####

با وجود ارائه استانداردهای بین المللی مانند یونیكد و بكارگیری آن ها در تمامی سیستم عامل های مدرن هنوز هم نرم افزار های زیادی وجود دارند كه با متون غیر لاتین و بخصوص زبان هائی مانند عربی و مشتقات آن مانند فارسی سازگار نمی باشند.

البته هدف از نگارش مقاله حاضر راهكاری جهت سازگار نمودن سایر برنامه ها با زبان فارسی نیست؛ بلكه طراحی نرم افزارهائی می باشد كه قابلیت استفاده از كیبورد فارسی را حتی در صورتی كه سیستم عامل قادر به تایپ متون فارسی نباشد، داشته باشند. البته در صورت پشتیبانی سیستم عامل، باز هم دلیل دیگری جهت استفاده از تابع مذكور وجود خواهد داشت و آن تایپ مستقیم فارسی در یك عنصر خاص از فرم، مانند یك كادر متن، بدون تغییر زبان توسط كاربر می باشد.

در ادامه از زبان C# و پلاتفرم .NET جهت طراحی تابع مورد نظر استفاده می نمائیم.

#### شرح پروژه ####

بسیار خب. برای شروع كار قبل از هر چیز اقدام به اجرای پروژه نمونه نمائید[^1]. دقت نمائید كه Solution پروژه در Visual Studio 2008[^2] ایجاد شده است بنابراین برای باز نمودن Solution پروژه حتما به این نسخه از نرم افزار مذكور نیاز خواهید داشت. البته برای اجرای فایل نمونه كافیست .NET Framework 2.0[^3] و یا بالاتر در سیستم نصب باشد. در ضمن كدی كه در ادامه خواهد آمد با تمامی نسخه های .NET و Visual Studio .NET سازگار می باشد. چنانچه از نسخه های پائین تر Visual Studio استفاده می نمائید كافیست فایل PersianKeyboard.cs را كه حاوی یك NameSpace و كلاسی به همین نام می باشد را به پروژه ای در نسخه مورد نظر خود اضافه نمایند. همچنین كد مذكور می تواند به عنوان یك كتابخانه و یا كامپوننت نیز به بكار گرفته شود.

با توجه به اینكه كد پروژه تماما در VS 2K8[^4] نوشته و كامپایل شده است، ممكن است پرسشی بدین شكل در ذهن شما شكل گرفته باشد: "چگونه است كه با وجود استفاده از VS 2K8، فایل نمونه به جای اجرا در .NET FX 3.5 در .NET FX 2.0 اجرا می شود؟" در پاسخ به این پرسش ذكر این نكته الزامی است كه مایكروسافت اقدام به ارائه قابلیتی جدید به نام Targeting در VS 2K8 جهت كامپایل برنامه مقصد در .NET FX 2.0, 3.0, 3.5 نموده است. قابل ذكر است در VS 2K5 هم با نصب یك افزودنی تحت عنوان MSBee[^5] – قابل دریافت از مایكروسافت – می توان .NET FX 1.1 را مورد هدف قرار داد.

در هر صورت اقدام به اجرای فایل نمونه می نمائیم. در صورت نصب .NET FX و اجرای موفقیت آمیز فایل نمونه با پنجره ای مشابه آنچه كه در تصویر شماره 1 آمده است مواجه خواهید شد.

{{< figure src="/blog/cross-platform-persian-keyboard/cross-platform-persian-keyboard.jpg" alt="تصویر شماره 1 - شمای كلی برنامه نمونه" caption="تصویر شماره 1 - شمای كلی برنامه نمونه" >}}

بدون اینكه اقدام به تغییر زبان نمائید شروع به تایپ كلماتی در هر دو كادر Persian و English نمائید. مشاهده می نمائید كه كادر بالائی به صورت خودكار فارسی و كادر پائین بصورت خودكار انگلیسی تایپ می نماید. حال زبان را به فارسی یا هر زبان دیگری تغییر داده و مجددا در كادر Persian اقدام به تایپ نمائید بازهم مشاهده می نمائید كه متون بصورت فارسی وارد می شوند.

#### طراحی و پیاده سازی كیبورد فارسی[^6] ####

بسیار خب، قبل از هر چیز اقدام به ایجاد پروژه جدیدی در ویژوال استودیو از نوع Windows Forms Application نمائید.  پس از ایجاد فرم ویندوز، از جعبه ابزار اقدام به درج یك كادر متن بر روی فرم نمائید. بسیار خب؛ پروژه را با كلید F5 اجرا نموده سپس در كادر متنی اقدام به تایپ متن نمائید. مشاهده می كنید كه اطلاعات با زبان پیش فرض سیستم عامل تان (احتمالا انگلیسی) در كادر متنی ظاهر می شود. آنگاه برنامه را بسته و به محیط ویژوال استودیو بازگردید. خب، تا اینجای كار هیجانی در ایجاد و اجرای پروژه وجود نداشت!

 و اما اولین ایده ای كه ممكن است برای تشخیص كلید فشرده شده به ذهن شما برسد چیست؟ فكر می كنم اكثر افراد استفاده از رخداد TextChanged كادر متنی را توصیه نمایند. اما همانطور كه از نام رخداد پیداست واقعیت این است كه ابتدا متن ورودی توسط كاربر در كادر متنی ظاهر شده و سپس برنامه كنترل رخداد را بدست خواهد گرفت. پس انتظار نداشته باشید كاربران با منظره خوشایندی روبرو شوند، چرا كه با تایپ هر حرف كاربر ابتدا حرف الفبای لاتین را می بیند سپس در رخداد TextChanged مقدار كاركتر ورودی چك می شود و آنگاه كلید لاتین به كلید معادل فارسی بدل می شود.
 
پس چاره چیست؟ بهترین راه حلی كه به نظر می رسد این است كه قبل از نمایش كاراكتر مورد نظر، كنترل برنامه را بدست بگیریم، سپس از نمایش كاراكتر لاتین جلوگیری نمائیم. در واقع عمل هندلینگ كادر متنی را بصورت دستی انجام دهیم. بدین منظور بهترین گزینه ای كه متناسب با عملیات تشریح شده به نظر می رسد رخداد KeyPress می باشد. این رخداد در زمان فشردن كلید و قبل از نمایش آن در كادر متن به وقوع می پیوندد. سپس در كد مربوط به رخداد می توان هندلیگ كادر متنی را بصورت دستی انجام داد این عمل باعث می شود كنترل نمایش كاراكترها و تراز مكان نما از روال عادی خود خارج شود.

بسیار خب. كادر متنی را انتخاب نمائید. سپس در پنل Properties بر روی گزینه Events (به شكل صاعقه) كلیك نمائید تا رخداد های مرتبط با آن نمایش داده شوند. به دنبال رخداد KeyPress جستجو نمائید. چنانچه در حالت Categorized قرار دارید در طبقه Key می توانید آن را پیدا نمائید در غیر اینصورت بر اساس حروف الفبا جستجو نمائید.

بسیار خب، بر روی رخداد KeyPress دابل كلیك نمائید. در ادامه وارد قسمت كد نویسی فرم خواهید شد. با عمل دابل كلیك، شما باعث خلق تابعی به شكل زیر شده اید:

{{< highlight csharp >}}
private void textBox1_KeyPress(object sender, KeyPressEventArgs e)
{

}
{{< /highlight >}}

بسیار خب ما سه حرف از صفحه كلید را به عنوان نمونه جهت فارسی نویسی انتخاب می نمائیم. این سه حرف شامل كلیدهای H, T, M خواهند بود كه به ترتیب معادل با ‘ا’، ‘ف’، ‘ئ’، و در حالتی كه كلید Shift را فشرده اید معادل با ‘آ’، ‘،’، ‘ء’، می باشند. پس در ادامه كدهای زیر را درون تابع جدید تایپ نمائید:

{{< highlight csharp >}}
private void textBox1_KeyPress(object sender, KeyPressEventArgs e)
{
    int pos = textBox1.SelectionStart;
    e.Handled = true;

    switch (e.KeyChar.ToString().ToUpper())
    {
        case "H":
            textBox1.Text += "\u0627";
            break;
        case "M":
            textBox1.Text += "\u0626";
            break;
        case "T":
            textBox1.Text += "\u0641";
            break;
        default:
            e.Handled = false;
            break;
    }

    textBox1.Select(pos + 1, 0);
}
{{< /highlight >}}

در ابتدای تابع متغیری به نام pos جهت بدست آوردن و نگهداری موقعیت فعلی اشاره گر در كادر متن تعریف نموده ایم. این بدان دلیل است كه در زمان عمل هندلینگ به صورت دستی، اشاره گر به ابتدای كادر متنی باز می گردد و قادر به حذف حروف جدید وارد شده با كلید BackSpace نخواهید بود. پس در ادامه هندلینگ كادر متنی را بدست می گیریم:

{{< highlight csharp >}}
int pos = textBox1.SelectionStart;
e.Handled = true;
{{< /highlight >}}

دقت نمائید در صورتی كه اجازه دهیم هندلینگ بصورت خودكار انجام شود علاوه بر كاراكتر فارسی، كاراكتر انگلیسی نیز وارد خواهد شد. بنابراین از هندلینگ بصورت خودكار اجتناب نمائید. قبل از ادامه بهتر است نگاهی به ورودی های تابع جدید بیاندازیم:

{{< highlight csharp >}}
private void textBox1_KeyPress(object sender, KeyPressEventArgs e)
{{< /highlight >}}

یكی از ورودی های تابع پارامتر e می باشد كه از نوع KeyPressEventArgs تعریف شده است. در زمان فشردن كلیدی توسط كاربر و اجرای تابع مربوط به رخداد، متغیر e، كلید فشرده شده توسط كاربر را به تابع می فرستد. در این لحظه شما قادر به تشخیص كلید فشرده شده خواهید بود. بنابراین توسط یك شرط Switch/Case به دنبال كلید های مورد نظر خواهیم بود.

{{< highlight csharp >}}
switch (e.KeyChar.ToString().ToUpper())
{
    case "H":
        textBox1.Text += "\u0627";
        break;
    case "M":
        textBox1.Text += "\u0626";
        break;
    case "T":
        extBox1.Text += "\u0641";
        break;
    default:
        e.Handled = false;
    break;
}
{{< /highlight >}}

همانطور كه مشاهده می نمائید متغیر e داری خصوصیتی به نام KeyChar از نوع داده char می باشد. كه توسط متد ToString() و سپس ToUpper()، ابتدا به داده رشته ای و سپس به حروف بزرگ تبدیل شده است. این عمل بدین جهت صورت گرفته است كه در صورت روشن و یا خاموش بودن CapsLock باز هم بتوان فشرده شدن كلیدها را تشخیص داد. سپس در هریك از حالات( case)، رشته ذخیره شده داخل كادر متنی textBox1 را به علاوه ی یك كاراكتر یونیكد كه همان كاراكتر معادل فارسی است نموده ایم.

{{< highlight csharp >}}
case "H":
    textBox1.Text += "\u0627";
    break;
{{< /highlight >}}

برای مثال برای كاراكتر H كد یونیكد 0627 كه كد حرف ‘ا’ فارسی در جدول یونیكد[^7] می باشد را وارد نموده ایم. با هر بار وارد شدن H بجای نمایش آن، حرف ‘ا’ نمایش داده خواهد شد. توجه داشته باشید در زبان C# برای ذخیره و یا نمایش یك كاراكتر یونیكد در یك رشته بایستی از فرمت \uXXXX استفاده نمائیدكه به جای هر علامت X یك عدد در مبنای Hex قرار می گیرد. برای مثال كد كاراكتر ‘ا’ در مبنای 10 عدد 1575 معادل با 0627  در مبنای Hex می باشد. كه در C# به شكل \u0627 بیان می شود. دقت نمائید كه كدها بصورت چهار رقمی وارد می شوند برای مثال 627 به شكل 0627 وارد شده است.

بسیار خب. در ادامه ساختار Switch/Case بخش default برای سایر كلیدها در نظر گرفته شده است. این بدان دلیل است كه چنانچه كلیدی غیر از كلید های مورد نظر وارد شود بایستی هندلینگ به حالت نرمال باز گردد چرا كه در غیر اینصورت كاراكتر مورد نظر چاپ نخواهد شد. همچنین هندلینگ دستی باعث مختل شدن كلیدهای كنترلی نظیر كلید BackSpace یا Del خواهد شد كه در این بخش به منظور اجتناب از این مسئله، هندلینگ به حالت خودكار باز می گردد:

{{< highlight csharp >}}
default:
    e.Handled = false;
    break;
{{< /highlight >}}

در پایان اقدام به تعیین مكان درست اشاره گر بر اساس متغیر pos می نمائیم:

{{< highlight csharp >}}
textBox1.Select(pos + 1, 0);
{{< /highlight >}}

حال پروژه را با فشردن كلید F5 اجرا نمائید. یكی از كلیدهای موردنظر را امتحان نمائید، حال كلید دیگری را بفشارید. مراقب باشید استفاده از كلید BackSpace را فراموش نكنید.

بسیار خب همه ی موارد بدرستی اجرا می شوند. حال كلید Shift را فشرده و همزمان یكی از كلیدهای فارسی شده را بفشارید اما مشاهده می نمائید كه كلید Shift تاثیر گذار نمی باشد. بنابراین بایستی كد مربوطه اصلاح شود. برای اینكار برنامه را بسته و به محیط ویژوال استودیو باز گردید.

و اما چگونه می توان از فشرده شدن كلید Shift مطلع شد؟ بهترین پاسخ برای این سوال استفاده از رخداد PreviewKeyDown می باشد. اما قبل از این كه به سراغ این رخداد برویم اجازه دهید یك متغیر سراسری از نوع bool تعریف نمائیم. از این متغیر جهت تعیین و تشخیص فشرده شدن كلید Shift استفاده می نمائیم.

{{< highlight csharp >}}
private bool shift = false;
{{< /highlight >}}

بسیار خب در فرم اصلی در حالت Design، كادر متن را انتخاب نمائید. سپس در پنل Properties رخداد PreviewKeyDown را انتخاب نمائید. این رخداد همانند رخداد KeyPress در حالت Categorized در دسته Key جای خواهد گرفت. در هر صورت بر روی PreviewKeyDown دابل كلیك نمائید. تا با تابع جدیدی به شكل ذیل مواجه شوید:

{{< highlight csharp >}}
private void textBox1_PreviewKeyDown(object sender, PreviewKeyDownEventArgs e)
{

}
{{< /highlight >}}

در این حالت پارامتر e از نوع PreviewKeyDownEventArgs خواهد بود. این متغیر پارامترهای مختلفی نظیر كد كلیدهای فشرده شده و یا وضعیت كلیدهای كنترلی نظیر Shift را به تابع خواهد فرستاد. كد تابع را به شكل زیر اصلاح نمائید:

{{< highlight csharp >}}
shift = e.Shift;
{{< /highlight >}}

همانطور كه مشاهده می نمائید این متغیر وضعیت كلید Shift را نگهداری می نماید. در ادامه جهت بررسی وضعیت كلید Shift نیازمند اعمال تغییراتی در تابع مربوط به رخداد KeyPress می باشیم:

{{< highlight csharp >}}
private void textBox1_KeyPress(object sender, KeyPressEventArgs e)
{
    int pos = textBox1.SelectionStart;
    e.Handled = true;

    if (!shift)
    {
        switch (e.KeyChar.ToString().ToUpper())
        {
            case "H":
                textBox1.Text += "\u0627";
                break;
            case "M":
                textBox1.Text += "\u0626";
                break;
            case "T":
                textBox1.Text += "\u0641";
                break;
            default:
                e.Handled = false;
                break;
        }
    }
    else
    {
        switch (e.KeyChar.ToString().ToUpper())
        {
            case "H":
                textBox1.Text += "\u0622";
                break;
            case "M":
                textBox1.Text += "\u0621";
                break;
            case "T":
                textBox1.Text += "\u060C";
                break;
            default:
                e.Handled = false;
                break;
        }
        shift = false;
    }

    textBox1.Select(pos + 1, 0);
}
{{< /highlight >}}

همانطور كه مشاهده می نمائید برای حالتی كه كلید Shift فشرده شده است یك دستور switch و در حالت عكس آن دستور switch دیگری به كار برده شده است. در كد تابع حاضر زمانی كه كلید Shift فشرده شده است دستورات قسمت else اجرا می شوند كه در این حالت از كدهای یونیكد مربوطه برای هر كلید استفاده شده است. شكل كلی:

{{< highlight csharp >}}
if (!shift)
{
    // H -> ا
    // M -> ئ
    // T -> ف
}
else
{
    // H -> آ
    // M -> ء
    // T -> ،
    shift = false;
}
{{< /highlight >}}

همانطور كه مشاهده می نمائید قسمت if مربوط به حالت عادی صفحه كلید و قسمت else مربوط به حالتی است كه كلید shift همراه با كاراكتر موردنظر فشرده شده است. در این قسمت تنها دستور اضافه ای كه موجود می باشد مربوط به متغیر shift است كه هر بار به مقدار false باز می گردد.

بسیار خوب، تبریك می گوئیم؛ صفحه كلید فارسی شما آماده است. پروژه را اجرا نموده و تمامی حالات را امتحان نمائید.

نكته ای كه بایستی در نظر داشت این است كه كد حاضر تنها برای اجرا بر روی یك كادر متن بهینه شده است اما در پروژه کامل در انتهای مقاله فایلی تحت عنوان PersianKeyboard.cs ارائه شده است كه كیبورد فارسی را بصورت كامل شبیه سازی می نماید. از ویژگی های این كلاس فراخوانی و استفاده آسان می باشد، برای مثال با فراخوانی یك تابع می توان یك كادر متن را فارسی نمود. همچنین از دیگر قابلیت های آن تعیین تایپ اعداد بصورت عربی و یا فارسی بصورت دلخواه می باشد.

در مبحث بعدی نحوه بكارگیری آن را به زبانی ساده خواهیم آموخت.

### چگونگی بكارگیری كلاس PersianKeyboard ###

جهت بكارگیری تابع PersianKeyboard مراحل ذیل را دنبال نمائید:

1: در ویژوال استودیو ابتدا پروژه جدیدی از نوع Windows Forms Application ایجاد نمائید.

2: در Solution Explorer، بر روی نام پروژه كلیك راست نموده و از منوی باز شده گزینه Existing Item… واقع در منوی Add را انتخاب نمائید. سپس فایل PersianKeyboard.cs را انتخاب نموده و به پروژه اضافه نمائید.[^8]

3: در Solution Explorer بر روی Form1.cs كلیك راست نموده و بر روی گزینه ی View Code كلیك نمائید. با این عمل وارد كدهای مربوط به فرم پروژه خواهید شد.

4: سپس در ناحیه using واقع در ابتدای كد و پس از آخرین اعلان using كد ذیل را وارد نمائید:

{{< highlight csharp >}}
using CrossPlatformKeyboard;
{{< /highlight >}}

5: آنگاه، پیش از تابع سازنده كلاس Form1 كد زیر را وارد نمائید:

{{< highlight csharp >}}
PersianKeyboard kb = new PersianKeyboard();
{{< /highlight >}}

6: كلاس حاضر بصورت پیش فرض از اعداد عربی به جای اعداد فارسی استفاده می نماید. چنانچه قصد استفاده از اعداد فارسی را دارید، در تابع سازنده كلاس Form1 و پس از InitializeComponent(); كد زیر را درج نمائید:

{{< highlight csharp >}}
kb.usePersianNums = true;
{{< /highlight >}}

7: در Solution Explorer بر روی Form1.cs كلیك راست نموده و بر روی گزینه ی View Designer كلیك نمائید.

8: سپس از Toolbox بر روی فرمی كه تحت عنوان Form1 ظاهر شده است یك كادر متن قرار دهید.

9: كادر متنی را انتخاب و آنگاه وارد پنل Properties شوید. چنانچه قادر به پیدا نمودن این پنل نمی باشید بر روی كادر متنی كلیك راست نموده و ازمنوی ظاهر شده گزینه Properties را انتخاب نمائید.

10: در پنل Properties جهت مشاهده رخدادهای مربوط به كادر متنی بر روی علامت صاعقه تحت عنوان Events كلیك نمائید.

11: در ادامه بر روی رخداد PreviewKeyDown دابل كلیك نمائید.

12: در تابع جدید كد ذیل را وارد نمائید:

{{< highlight csharp >}}
kb.shiftPressed = e.Shift;
{{< /highlight >}}

13: مجددا مطابق آنچه كه قبلا گفته شد در حالت Design بر روی رخداد KeyPress مربوط به كادر متن دابل كلیك نمائید.

14: آنگاه در تابع جدید كد ذیل را درج نمائید:

{{< highlight csharp >}}
kb.TransformInputChar(txtPersian, e);
{{< /highlight >}}

15: چنانچه مراحل قبل را بدرستی انجام داده اید، كدهای واقع در Form1 شبیه به آنچه كه در ذیل می آید به نظر می رسد:

{{< highlight csharp >}}
/// <summary>
///   (The MIT License)
///   
///   Copyright (c) 2008 Mohammad S. Babaei
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
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using CrossPlatformKeyboard; // Not necessary in this case, because the namespace of project is the same as the namespace of PersianKeyboard.cs

namespace CrossPlatformKeyboard
{
    public partial class Form1 : Form
    {
        PersianKeyboard kb = new PersianKeyboard();

        public Form1()
        {
            InitializeComponent();

            kb.usePersianNums = false;
        }

        private void txtPersian_PreviewKeyDown(object sender, PreviewKeyDownEventArgs e)
        {
            kb.shiftPressed = e.Shift;
        }

        private void txtPersian_KeyPress(object sender, KeyPressEventArgs e)
        {
            kb.TransformInputChar(txtPersian, e);
        }
    }
}
{{< /highlight >}}

16: بسیار خب. با زدن كلید F5 پروژه را اجرا نمائید.

#### جمع بندی ####

كد تشریح شده در این مقاله بسیاری از ویژگی های موردنظر جهت طراحی یك كیبورد اختصاصی جدای از سیستم عامل را فراهم می سازد. دقت داشته باشید كد حاضر را می توان در سایر زبان های برنامه نویسی كه از .NET پشتیبانی می نمایند نیز به كار گرفت. برای این كار كافیست آنرا در قالب یك پروژه Class Library و یا یك Windows Forms Control Library نیز كامپایل نمائید.

اما یادآوری این نكته كه آیا كد حاضر در صفحات ASP.NET قابل استفاده می باشد یا خیر نیز خالی از لطف نمی باشد. متاسفانه كدهای حاضر را نمی توان در یك ASP.NET Web Application بكار گرفت. تنها راه حلی كه برای آن به نظر می رسد استفاده از زبان JavaScript است، كه البته مقداری فرآیند كار را پیچیده تر می نماید.


[دریافت سورس کد کامل از GitLab](https://gitlab.com/NuLL3rr0r/babaei.net/tree/master/2008-02-08-cross-platform-persian-keyboard)

[دریافت سورس کد کامل از GitHub](https://github.com/NuLL3rr0r/babaei.net/tree/master/2008-02-08-cross-platform-persian-keyboard)


{{< codeblock lang="csharp" title="PersianKeyboard" >}}
/// <summary>
///   (The MIT License)
///   
///   Copyright (c) 2008 Mohammad S. Babaei
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
using System.Windows.Forms;

namespace CrossPlatformKeyboard
{
    public class PersianKeyboard
    {
        public bool shiftPressed = false;
        public bool usePersianNums = false;

        public PersianKeyboard()
        {

        }

        public void TransformInputChar(TextBox textBox, KeyPressEventArgs e)
        {
            int pos = textBox.SelectionStart;
            e.Handled = true;

            if (!shiftPressed)
            {
                #region Normal Keys

                switch (e.KeyChar.ToString().ToUpper())
                {
                    case "'":   //  گ
                        textBox.Text = textBox.Text.Insert(pos, "\u06AF");
                        break;
                    case ",":   //  و
                        textBox.Text = textBox.Text.Insert(pos, "\u0648");
                        break;
                    case ";":   //  ك
                        textBox.Text = textBox.Text.Insert(pos, "\u0643");
                        break;
                    case "A":   //  ش
                        textBox.Text = textBox.Text.Insert(pos, "\u0634");
                        break;
                    case "B":   //  ذ
                        textBox.Text = textBox.Text.Insert(pos, "\u0630");
                        break;
                    case "C":   //  ز
                        textBox.Text = textBox.Text.Insert(pos, "\u0632");
                        break;
                    case "D":   //  ی
                        textBox.Text = textBox.Text.Insert(pos, "\u064A");
                        break;
                    case "E":   //  ث
                        textBox.Text = textBox.Text.Insert(pos, "\u062B");
                        break;
                    case "F":   //  ب
                        textBox.Text = textBox.Text.Insert(pos, "\u0628");
                        break;
                    case "G":   //  ل
                        textBox.Text = textBox.Text.Insert(pos, "\u0644");
                        break;
                    case "H":   //  ا
                        textBox.Text = textBox.Text.Insert(pos, "\u0627");
                        break;
                    case "I":   //  ه
                        textBox.Text = textBox.Text.Insert(pos, "\u0647");
                        break;
                    case "J":   //  ت
                        textBox.Text = textBox.Text.Insert(pos, "\u062A");
                        break;
                    case "K":   //  ن
                        textBox.Text = textBox.Text.Insert(pos, "\u0646");
                        break;
                    case "L":   //  م
                        textBox.Text = textBox.Text.Insert(pos, "\u0645");
                        break;
                    case "M":   //  ئ
                        textBox.Text = textBox.Text.Insert(pos, "\u0626");
                        break;
                    case "N":   //  د
                        textBox.Text = textBox.Text.Insert(pos, "\u062F");
                        break;
                    case "O":   //  خ
                        textBox.Text = textBox.Text.Insert(pos, "\u062E");
                        break;
                    case "P":   //  ح
                        textBox.Text = textBox.Text.Insert(pos, "\u062D");
                        break;
                    case "Q":   //  ض
                        textBox.Text = textBox.Text.Insert(pos, "\u0636");
                        break;
                    case "R":   //  ق
                        textBox.Text = textBox.Text.Insert(pos, "\u0642");
                        break;
                    case "S":   //  س
                        textBox.Text = textBox.Text.Insert(pos, "\u0633");
                        break;
                    case "T":   //  ف
                        textBox.Text = textBox.Text.Insert(pos, "\u0641");
                        break;
                    case "U":   //  ع
                        textBox.Text = textBox.Text.Insert(pos, "\u0639");
                        break;
                    case "V":   //  ر
                        textBox.Text = textBox.Text.Insert(pos, "\u0631");
                        break;
                    case "W":   //  ص
                        textBox.Text = textBox.Text.Insert(pos, "\u0635");
                        break;
                    case "X":   //  ط
                        textBox.Text = textBox.Text.Insert(pos, "\u0637");
                        break;
                    case "Y":   //  غ
                        textBox.Text = textBox.Text.Insert(pos, "\u063A");
                        break;
                    case "Z":   //  ظ
                        textBox.Text = textBox.Text.Insert(pos, "\u0638");
                        break;
                    case "[":   //  ج
                        textBox.Text = textBox.Text.Insert(pos, "\u062C");
                        break;
                    case "\\":   // ژ
                        // or use
                        // case @"\":
                        textBox.Text = textBox.Text.Insert(pos, "\u0698");
                        break;
                    case "]":   //  چ
                        textBox.Text = textBox.Text.Insert(pos, "\u0686");
                        break;
                    case "`":   //  پ
                        textBox.Text = textBox.Text.Insert(pos, "\u067E");
                        break;
                    case "0":   //  ٠ | ۰
                        textBox.Text = textBox.Text.Insert(pos, !usePersianNums ? "\u0660" : "\u06F0");
                        break;
                    case "1":   //  ١ | ۱
                        textBox.Text = textBox.Text.Insert(pos, !usePersianNums ? "\u0661" : "\u06F1");
                        break;
                    case "2":   //  ٢ | ۲
                        textBox.Text = textBox.Text.Insert(pos, !usePersianNums ? "\u0662" : "\u06F2");
                        break;
                    case "3":   //  ٣ | ۳
                        textBox.Text = textBox.Text.Insert(pos, !usePersianNums ? "\u0663" : "\u06F3");
                        break;
                    case "4":   //  ٤ | ۴
                        textBox.Text = textBox.Text.Insert(pos, !usePersianNums ? "\u0664" : "\u06F4");
                        break;
                    case "5":   //  ٥ | ۵
                        textBox.Text = textBox.Text.Insert(pos, !usePersianNums ? "\u0665" : "\u06F5");
                        break;
                    case "6":   //  ٦ | ۶
                        textBox.Text = textBox.Text.Insert(pos, !usePersianNums ? "\u0666" : "\u06F6");
                        break;
                    case "7":   //  ٧ | ۷
                        textBox.Text = textBox.Text.Insert(pos, !usePersianNums ? "\u0667" : "\u06F7");
                        break;
                    case "8":   //  ٨ | ۸
                        textBox.Text = textBox.Text.Insert(pos, !usePersianNums ? "\u0668" : "\u06F8");
                        break;
                    case "9":   //  ٩ | ۹
                        textBox.Text = textBox.Text.Insert(pos, !usePersianNums ? "\u0669" : "\u06F9");
                        break;
                    default:
                        e.Handled = false;
                        break;
                }

                #endregion
            }
            else
            {
                #region Mixed Keys with Shift

                switch (e.KeyChar.ToString().ToUpper())
                {
                    case ",":   //  ؤ
                        textBox.Text = textBox.Text.Insert(pos, "\u0624");
                        break;
                    case "/":   //  ؟
                        textBox.Text = textBox.Text.Insert(pos, "\u061F");
                        break;
                    case "A":   //   ََ
                        textBox.Text = textBox.Text.Insert(pos, "\u064E");
                        break;
                    case "B":   //  إ
                        textBox.Text = textBox.Text.Insert(pos, "\u0625");
                        break;
                    case "C":   //  Nothing
                        break;
                    case "D":   //   ِِ
                        textBox.Text = textBox.Text.Insert(pos, "\u0650");
                        break;
                    case "E":   //   ٍٍ
                        textBox.Text = textBox.Text.Insert(pos, "\u064D");
                        break;
                    case "F":   //   ّّ
                        textBox.Text = textBox.Text.Insert(pos, "\u0651");
                        break;
                    case "G":   //   ْْ
                        textBox.Text = textBox.Text.Insert(pos, "\u0652");
                        break;
                    case "H":   //  آ
                        textBox.Text = textBox.Text.Insert(pos, "\u0622");
                        break;
                    case "I":   //  ة
                        textBox.Text = textBox.Text.Insert(pos, "\u0629");
                        break;
                    case "J":   //  ـ
                        textBox.Text = textBox.Text.Insert(pos, "\u0640");
                        break;
                    case "K":   //  »
                        textBox.Text = textBox.Text.Insert(pos, "\u00BB");
                        break;
                    case "L":   //  «
                        textBox.Text = textBox.Text.Insert(pos, "\u00AB");
                        break;
                    case "M":   //  ء
                        textBox.Text = textBox.Text.Insert(pos, "\u0621");
                        break;
                    case "N":   //  أ
                        textBox.Text = textBox.Text.Insert(pos, "\u0623");
                        break;
                    case "O":   //  ×
                        textBox.Text = textBox.Text.Insert(pos, "\u00D7");
                        break;
                    case "P":   //  ÷
                        textBox.Text = textBox.Text.Insert(pos, "\u00F7");
                        break;
                    case "Q":   //   ًً
                        textBox.Text = textBox.Text.Insert(pos, "\u064b");
                        break;
                    case "R":   //  Nothing
                        break;
                    case "S":   //   ُُ
                        textBox.Text = textBox.Text.Insert(pos, "\u064F");
                        break;
                    case "T":   //  ،
                        textBox.Text = textBox.Text.Insert(pos, "\u060C");
                        break;
                    case "U":   //  Nothing
                        break;
                    case "V":   //  ی
                        textBox.Text = textBox.Text.Insert(pos, "\u06CC");
                        break;
                    case "W":   //   ٌٌ
                        textBox.Text = textBox.Text.Insert(pos, "\u064C");
                        break;
                    case "X":   //  ]
                        textBox.Text = textBox.Text.Insert(pos, "\u005D");
                        break;
                    case "Y":   //  ؛
                        textBox.Text = textBox.Text.Insert(pos, "\u061B");
                        break;
                    case "Z":   //  [
                        textBox.Text = textBox.Text.Insert(pos, "\u005B");
                        break;
                    case "[":   //  {
                        textBox.Text = textBox.Text.Insert(pos, "\u007B");
                        break;
                    case "]":   //  }
                        textBox.Text = textBox.Text.Insert(pos, "\u007D");
                        break;
                    case "`":   //  ى
                        textBox.Text = textBox.Text.Insert(pos, "\u0060");
                        break;
                    default:
                        e.Handled = false;
                        break;
                }
                shiftPressed = false;

                #endregion
            }

            if (e.Handled)
                textBox.Select(pos + 1, 0);
        }

    }
}
{{< /codeblock >}}


#### منابع و ماخذ ####

<pre>
<a href="http://msdn2.microsoft.com/en-us/vstudio/default.aspx" target="_blank">http://msdn2.microsoft.com/en-us/vstudio/default.aspx</a>
<a href="http://www.codeplex.com/Wiki/View.aspx?ProjectName=MSBee" target="_blank">http://www.codeplex.com/Wiki/View.aspx?ProjectName=MSBee</a>
<a href="http://www.codeplex.com/MSBee/Release/ProjectReleases.aspx" target="_blank">http://www.codeplex.com/MSBee/Release/ProjectReleases.aspx</a>
<a href="http://www.microsoft.com/Downloads/details.aspx?FamilyID=e0d0776f-25c4-444a-a6b9-71d06826f5b4&displaylang=e" target="_blank">http://www.microsoft.com/Downloads/details.aspx?FamilyID=e0d0776f-25c4-444a-a6b9-71d06826f5b4&displaylang=e</a>
<a href="http://msdn2.microsoft.com/en-us/vs2005/aa718347.aspx" target="_blank">http://msdn2.microsoft.com/en-us/vs2005/aa718347.aspx</a>
</pre>


[^1]: تمامی فایل ها و كدهای استفاده شده در این مقاله در انتهای مطلب در قالب یک فایل فشرده قابل دریافت می باشد. نام فایل نمونه demo.exe واقع در پوشه ی "CrossPlatformPersianKeyboard" می باشد.

[^2]: در ادامه به جای این واژه از VS 2K8 استفاده می نمائیم.

[^3]: در ادامه به جای این واژه از .NET FX استفاده می نمائیم.

[^4]: [http://msdn2.microsoft.com/en-us/vstudio/default.aspx](http://msdn2.microsoft.com/en-us/vstudio/default.aspx)

[^5]: <div style="direction: rtl;">MSBuild Extras - Toolkit for .NET 1.1 "MSBee"  - جهت دریافت و نصب آخرین نسخه آن به همراه توضیحات و مستندات مربوطه، به آدرس های ذیل مراجعه نمائید:<br /><br /></div><div style="direction: ltr; text-align:left;"><a href="http://www.codeplex.com/Wiki/View.aspx?ProjectName=MSBee">http://www.codeplex.com/Wiki/View.aspx?ProjectName=MSBee</a><br /><a href="http://www.codeplex.com/MSBee/Release/ProjectReleases.aspx">http://www.codeplex.com/MSBee/Release/ProjectReleases.aspx</a><br /><a href="http://www.microsoft.com/Downloads/details.aspx?FamilyID=e0d0776f-25c4-444a-a6b9-71d06826f5b4&displaylang=e">http://www.microsoft.com/Downloads/details.aspx?FamilyID=e0d0776f-25c4-444a-a6b9-71d06826f5b4&displaylang=e</a><br /><a href="http://msdn2.microsoft.com/en-us/vs2005/aa718347.aspx">http://msdn2.microsoft.com/en-us/vs2005/aa718347.aspx</a><br /></div>

[^6]: چنانچه علاقه ای به تشریح كدها نداشته و فقط قصد استفاده از كدها بصورت آماده را دارید به مبحث بعدی مراجعه نمائید.

[^7]:  <div style="direction: rtl;">جهت دریافت و یا مشاهده این جدول كافیست به یكی از آدرس های ذیل مراجعه نمائید:<br /><br /></div><div style="direction: ltr; text-align:left;"><a href="http://fr.wikipedia.org/wiki/Table_des_caract%C3%A8res_Unicode_(0000-0FFF)">http://fr.wikipedia.org/wiki/Table_des_caract%C3%A8res_Unicode_(0000-0FFF)</a><br /><a href="http://unicode.coeurlumiere.com/">http://unicode.coeurlumiere.com/</a><br /><a href="http://unicode.org/charts/">http://unicode.org/charts/</a><br /><a href="http://jrgraphix.net/research/unicode_blocks.php?block=12">http://jrgraphix.net/research/unicode_blocks.php?block=12</a><br /></div>

[^8]: این فایل در پوشه مربوط به پروژه نمونه، قرار دارد.
