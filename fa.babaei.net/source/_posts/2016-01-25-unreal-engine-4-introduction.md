---
title: "Unreal Engine 4: Introduction"
date: 2016-01-25 02:01:41
tags:
  - Blueprints
  - Cross-platform
  - Epic
  - FLOSS
  - gamedev
  - Game Development
  - Game Programming
  - indiedev
  - Kismet
  - Open Source
  - UDK
  - UE4
  - Unreal Engine
  - UnrealScript
---

<div class="post-title-fa">مقدمه ای بر موتور ساخت بازی Unreal Engine 4</div>

[{% img post-image /blog/2016/01/25/unreal-engine-4-introduction/unreal-engine-4.png 601 201 "'صفحه بارگذاری Unreal Engine 4 Editor'" "'صفحه بارگذاری Unreal Engine 4 Editor'" %}](/blog/2016/01/25/unreal-engine-4-introduction/unreal-engine-4.png)
<span class="post-image-title">صفحه بارگذاری Unreal Engine 4 Editor</span>

علیرغم حضور نام های بزرگی مانند [CryEngine](http://cryengine.com/) از شرکت [Crytek](http://www.crytek.com/) و سایرین در دنیای بازی، بدون شک [Unreal Engine](http://unrealengine.com/) موفق ترین موتور بازی سازی [AAA](https://en.wikipedia.org/wiki/AAA_%28video_game_industry%29) تا به امروز می باشد.  با ظهور مارکت های جدیدی مانند [Valve Steam](http://store.steampowered.com/), [Apple App Store](https://www.apple.com/appstore), [Google Play](https://play.google.com/) و سایر بازارهای از این دست در دنیای بازی های کامپیوتری، فرصت های بسیاری جهت درخشش [توسعه دهندگان مستقل](https://en.wikipedia.org/wiki/Independent_video_game_development) در دنیای بازهای کامپیوتری ایجاد شد. قطعا یکی از عوامل موفقیت توسعه دهندگان مستقل در این بازارهای نوظهور موتور بازی سازی [Unity](http://www.unity3d.com/) بود که برای چند سال سلطان بی چون و چرای دنیای Indie بود. این موتور بازی سازی بدلیل سهولت یادگیری و استفاده، همچنین قابلیت تولید خروجی برای پلتفرم های مختلف شامل دسکتاپ، موبایل و کنسول در ازای پرداخت مبلغی نسبتا معقول، داشتن فروشگاه Asset که باعث کاهش هزینه توسعه بازی ها توسط توسعه دهندگان می شد، از محبوب ترین موتورهای بازی سازی نزد تولیدکنندگان مستقل می باشد. لذا شرکت [Epic](http://www.epicgames.com/) سازنده موتور بازی سازی Unreal Engine ابتدا با عرضه [UDK](http://www.unrealengine.com/udk/) که بر اساس موتور Unreal Engine 3 توسعه داده شده بود و سپس باز نمودن و عرضه کد Unreal Engine 4 بر روی [GitHub](https://github.com/) که قبلا با مبلغ بسیار گزافی فقط در اختیار آنهائی که این شرکت Licensees می نامید قرار داشت، گام بزرگی به سوی تسخیر بخشی از بازار بازی های مستقل نهاد.

در این سری از مقالات به آموزش ساخت بازی با استفاده از Unreal Engine 4 برای پلتفرم های مختلف Destkop, Mobile و Web خواهیم پرداخت. در اولین مقاله از این سری، به شناخت Unreal Engine 4، مختصری تاریخچه و توضیح مفاهیم آن می پردازیم.

جهت دنبال نمودن این دوره آموزشی نیازی به هیچگونه آشنائی مقدماتی با ساخت بازی های کامپیوتری نخواهد بود.

<!-- more -->


<br />

### فهرست ###

* [تاریخچه](#history)
* [پلتفرم های مورد پشتیبانی](#supported-platforms)
* [زبان برنامه نویسی](#programming-language)
* [Unreal Editor](#ue4-editor)
* [محیط توسعه](#ide)
* [Unreal Tournament](#unreal-tournament)


<br />
<a name="history"></a>

### تاریخچه ###

Unreal Engine حیات خود را به عنوان موتور مورد استفاده بازی [Unreal](https://en.wikipedia.org/wiki/Unreal) جهت رقابت با بازی [Quake II](https://en.wikipedia.org/wiki/Quake_II) که از موتور بازی سازی [id Tech 2 - که با نام Quake II Engine هم شناخته می شود -](https://en.wikipedia.org/wiki/Quake_II_engine) تولید شرکت [id Software](https://en.wikipedia.org/wiki/Id_Software)، استفاده می نمود آغاز کرد. یکی از موسسان شرکت id Software برنامه نویس افسانه ای [John Carmack](https://en.wikipedia.org/wiki/John_Carmack) می باشد که به خاطر نوآوری های او در صنعت بازی های کامپیوتری از سوی بسیاری پدر بازی های مدرن کامپیوتری شناخته می شود. از ویژگی های برجسته او دفاع از نرم افزارهای آزاد می باشد. Id Software با عناوینی چون Commander Keen, Wolfenstien, Doom, Quake و اخیرا Rage از تاثیرگذارترین کمپانی های این صنعت می باشد. بازی Unreal در مقابل Quake، موتور Unreal Engine در مقابل id Tech و [Tim Sweeney](https://en.wikipedia.org/wiki/Tim_Sweeney_%28game_developer%29) خالق Unreal Engine، یکی از موسسین و مدیرعامل فعلی Epic Games در مقابل John Carmack بخش قابل توجهی از گذشته صنعت بازی های کامپیوتری می باشد! هر چند که Carmack بعدها شرکت idTech را در آگوست 2013 جهت کار بر روی [Oculus Rift](https://www.oculus.com/en-us/rift/) که خود بعدها به تصاحب Facebook درآمد ترک نمود.

از زمان عرضه اولین نسخه از Unreal Engine در سال 1998 نسخ دیگری از این Game Engine در سال های بعد یکی پس از دیگری شامل Unreal Engine 2 در سال 2002 (که بعدها با یک آپدیت به نام Unreal Engine 2.5 عرضه شد) و Unreal Engine 3 در سال 2004 عرضه شدند. در ابتدا Unreal Engine 3 پلتفرم های Windows, Xbox 360 و PlayStation 3 را پشتیبانی می نمود که بعدها و در سال 2010 پشتیبانی از Android و iOS هم بدان اضافه شد. همچنین در سال 2011 پشتیبانی از Mac OS X سپس Adobe Flash Player 11 به این موتور اضافه شد. در نهایت در سال 2012 پشتیبانی از Windows RT به آن اضافه شد.

با وجود آنکه استفاده از Unreal Engine 3 برای [Modder ها](https://en.wikipedia.org/wiki/Mod_%28video_gaming%29) در دسترس و رایگان بود، تولید و فروش بازی توسط Unreal Engine 3 فقط در دسترس کمپانی هایی که لیسانس آن را خریداری کرده بودند قرار داشت. نکته قابل توجه قیمت گزاف این موتور بازی بود (طبق شنیده ها 750 هزار دلار که بسته به نوع Game متغیر بود و امکان داشت تا چندین میلیون دلار هزینه بردارد). با این وجود، در نوامبر 2009 کمپانی Epic نسخه ای از [کیت توسعه](https://en.wikipedia.org/wiki/Software_development_kit) این موتور بازی را تحت عنوان Unreal Development Kit یا به اختصار UDK جهت استفاده عموم منتشر نمود. سپس در دسامبر 2010 پشتیبانی از iOS به آن اضافه شد. این SDK در نهایت از ساخت بازی برای پلتفرم های Windows, Mac OS X و iOS پشتیبانی می نمود.

نقطه قوت UDK لیسانس بسیار معقول آن بود که آن را تبدیل به گزینه مناسبی برای کمپانی های با بودجه محدود می نمود. کمپانی هائی کوچک که ایده ساخت بازی های Next-Gen را در سر می پروراندند. برای استفاده از UDK بایستی ابتدا 99 دلار را پرداخت نموده و پس از آنکه سود خالص حاصله از درآمد شما بیش از 5,000 دلار می شد پس از کسر 5,000 دلار اولیه 25 درصد از آن را به کمپانی Epic بابت حق Royalty پرداخت می نمودید. بعدها مبلغ اولیه معاف از Royalty به 50,000 دلار افزایش پیدا کرد که بازهم هرچه بیشتر UDK را به عنوان گزینه معقول تری برای بازیسازان جلوه می داد. استفاده از UDK جهت امور آموزشی کاملا رایگان بود اما شما حق ساخت هیچگونه نرم افزار یا بازی Open Source توسط آن را نداشتید.

Unreal Engine 4 که از این پس آن را UE4 می نامیم، از سال 2003 در دست توسعه بوده است. عمده توسعه این Engine تا سال 2008 توسط خالق اصلی Unreal Engine و مدیرعامل Epic یعنی Tom Sweeney انجام گرفته است. در فوریه 2012 و در خلال [کنفرانس توسعه دهندگان بازی](https://en.wikipedia.org/wiki/Game_Developers_Conference) برای اولین بار به شکل خصوصی و محدود از UE4 پرده برداری شد که به فاصله کوتاهی پس از آن در ژوئن 2012 به صورت عمومی معرفی شد. در سال 2014 اعلام شد که این موتور بازی از [نسل هشتم کنسول های بازی](https://en.wikipedia.org/wiki/History_of_video_game_consoles_(eighth_generation))، PC و دستگاه های اندرویدی مبتنی بر [Nvidia Tegra K1](https://en.wikipedia.org/wiki/Tegra#Tegra_K1) پشتیبانی می نماید. در حال حاضر که آخرین نسخه پایدار این موتور 4.10.2 می باشد، بصورت کامل از Windows, Linux, Mac OS X, SteamOS, Xbox One, PlayStation 4, Android, iOS و HTML5 پشتیبانی می نماید. همچنین [VR](https://en.wikipedia.org/wiki/Virtual_reality) و سخت افزارهای آن به خوبی در UE4 پشتیبانی می شود.

در مارس 2014 در خلال رخداد Game Developers Conference، کمپانی Epic به شکل غیرمنتظره ای مدل مالی جدیدی را جهت عرضه UE4 معرفی نمود آنچنان که این خبر دنیای بازی های کامپیوتری را به لرزه درآورد.  Source Code کامل UE4 به همراه تمامی ابزارهای آن بر روی GitHub عرضه گذشت. همچنین جهت دریافت سورس کد کامل و ساخت بازی برای Platform های Windows, Mac OS X, Android و iOS بایستی ماهیانه 19 دلار به Epic پرداخت می نمودید به همراه 5 درصد حق Royalty از سود نهائی بازی یا محصول نرم افزاری که براساس آن عرضه می شد. در سپتامبر همان سال Epic اقدام به راه اندازی Unreal Engine Marketplace نمود که به خریداران حق لیسانس UE4 اجازه خرید و فروش Asset های آماده جهت استفاده در ساخت بازی ها را می داد. در همان ماه UE4 به شکل کاملا رایگان به مدارس، دانشگاه ها و سایر مراکز آموزشی جهت امور آموزشی، ساخت بازی،  هنر، معماری، شبیه سازی و ... توسط دانشجویان عرضه شد. Epic حتی پا را از این فراتر گذاشت و در فوریه 2015 برنامه ای به نام Unreal Dev Grants را با بودجه ای 5 میلیون دلاری جهت سرمایه گذاری بلاعوض در پروژه های ساخته شده با UE4 و تشویق برنامه نویسان به استفاده از آن تخصیص داد. یکسال پس از معرفی مدل مالی جدید، در مارس 2015 استفاده از UE4 و تمامی بروزرسانی های آن برای همگان بدون پرداخت هزینه ماهیانه، تا سقف درآمد 3000 دلار رایگان اعلام شد. در مدل نهائی پس از 3000 دلار سود خالص برای هر محصول در هر فصل، بایستی مبلغ 5 درصد Royalty به شرکت Epic پرداخت شود.

در ژوئن 2015 اعلام شد که Unreal Editor یه شکل Native قابلیت اجرا بر روی GNU/Linux را دارد. البته در حال حاضر هیچگونه باینری برای GNU/Linux عرضه نمی شود و بایستی سورس کد آن پس از دریافت از GitHub توسط کاربر نهائی Compile شود. شایان ذکر است که علیرغم Open Source بودن UE4، لیسانس آن از نوع [EULA](https://en.wikipedia.org/wiki/End-user_license_agreement) می باشد. [این لیسانس و محدودیت های آن را می تواند از اینجا مطالعه فرمائید](https://www.unrealengine.com/eula).


<br />
<a name="supported-platforms"></a>

### پلتفرم های مورد پشتیبانی ###

با UE4 می توانید پلتفرم های عمده دسکتاپ شامل Windows, Mac OS X و Linux را هدف قرار دهید. همچنین UE4 از پلتفرم های اصلی موبایل شامل Android و iOS پشتیبانی می نماید. پشتیبانی از وب در UE4 از طریق HTML5 و کیت توسعه [Emscripten](https://github.com/kripken/emscripten)  صورت می پذیرد.

جهت پشتیبانی از کنسول های بازی PlayStation 4 و Xbox One نیازی به پرداخت هزینه اضافه نمی باشد. اما، به Kit توسعه و ابزارهای آن از سوی Sony و Microsoft نیاز خواهید داشت.

UE4 از Virtual Reality یا به اختصار VR بر روی [SteamVR/HTC Vive](https://en.wikipedia.org/wiki/HTC_Vive), [Morpheus](https://en.wikipedia.org/wiki/PlayStation_VR), [Oculus Rift](https://en.wikipedia.org/wiki/Oculus_Rift), [Gear VR](https://en.wikipedia.org/wiki/Samsung_Gear_VR) و سایر دستگاه های از این دست پشتیبانی می نماید.

به این دلیل که [SteamOS](https://en.wikipedia.org/wiki/SteamOS) شرکت [Valve](https://en.wikipedia.org/wiki/Valve_Corporation) بر اساس [لینوکس دبیان](https://en.wikipedia.org/wiki/Debian) توسعه یافته است، به خوبی توسط UE4 پشتیبانی می شود.


<br />
<a name="programming-language"></a>

### زبان برنامه نویسی ###

به شکل سنتی، زبان اسکریپت نویسی UnrealScript تا پیش از UE4، زبان اصلی برنامه نویسی [GamePlay](https://en.wikipedia.org/wiki/Gameplay) در تمامی نسخ آنریل انجین بوده است. گاها ممکن است از این زبان به نام UScript نام برده شود. UnrealScript به عنوان یک زبان سطح بالا مانند [زبان برنامه نویسی Java](https://en.wikipedia.org/wiki/Java_(programming_language)) یک زبان برنامه نویسی [شی گرا](https://en.wikipedia.org/wiki/Object-oriented) می باشد که از [ارث بری چندگانه](https://en.wikipedia.org/wiki/Multiple_inheritance) پشتیبانی نمی نماید و نام فایل ها بایستی مترادف نام کلاس درون آن ها باشد. برخلاف جاوا از Object Wrappers برای Primative Type ها پشتیبانی نمی نماید. [Interface ها](https://en.wikipedia.org/wiki/Interface_%28computing%29) فقط در Unreal Engine 3 به بعد و چند بازی انگشت شمار که بر اساس Unreal Engine 2 توسعه داده شده اند دیده می شوند. این زبان اسکریپت نویسی از [بارگذاری عملگرها](https://en.wikipedia.org/wiki/Operator_overloading) پشتیبانی می نماید اما قابلیت [بارگذاری متد ها](https://en.wikipedia.org/wiki/Method_overloading) را ندارد (نگران [واژه های فنی](https://simple.wikipedia.org/wiki/Computer_jargon) مطرح شده نباشید بعدها در صورت لزوم در جای خود توضیح داده خواهند شد). در مارچ 2014 اعلام شد که در Unreal Engine 4 زبان برنامه نویسی C++ جایگزین UnrealScript در UE4 خواهد شد. [بنابر اعلام Epic Games به دلیل آنکه UnrealScript یک زبان مفسری می باشد کارائی آن 20 برابر کمتر از C++ می باشد](https://udn.epicgames.com/Three/UnrealScriptFoundations.html#UnrealScript%20Programming%20Strategy).

با معرفی Unreal Engine 4 از سوی Epic، زبان بصری Blueprints به عنوان جایگزینی برای زبان مشابه دیگر اما محدودی به نام Kismet در Unreal Engine 3 معرفی شد. مزیت این زبان، یادگیری سریع آن توسط افراد غیربرنامه نویس مانند Artist ها می باشد که به آن ها توانائی ساخت بازی بدون نیاز به برنامه نویس را خواهد داد. همچنین برنامه نویسان می توانند از Blueprints جهت ساخت سریع Prototype یا نمونه اولیه بازی هایشان با صرف کمترین زمان ممکن استفاده نمایند. بزرگترین مزیت Blueprints ویژگی Live Debugging آن به علاوه زمان توسعه سریع و کوتاه می باشد که در اکثر موارد آن را تبدیل به گزینه مناسبی در مقابل C++ می نماید. [این زبان بصری 10 برابر از C++ کندتر می باشد.](https://forums.unrealengine.com/showthread.php?3035-New-Twitch-livestream-with-Fortnite-developers-Thursday-April-17&p=19464&viewfull=1#post19464)

در طول این سری آموزشی از هر دو زبان C++ و Blueprints استفاده می نمائیم. همزمان با این سری به آموزش C++ در پست های جداگانه به زبان ساده خواهیم پرداخت. یادگیری C++ جهت دنبال نمودن این دوره الزامی نخواهد بود اما به شما کمک می نماید تا حداکثر کارائی را از UE4 برداشت نمایید. در واقع علیرغم سرعت اجرای پایین تر Blueprints در بسیاری از موارد کارائی آن بیش از حد نیاز می باشد.


<br />
<a name="ue4-editor"></a>

### Unreal Editor ###

این ابزار قدرتمند امکان ساخت ویرایش دنیای مجازی بازی و مراحل آن را به شکل بصری در اختیار شما خواهد گذارد. از طریق آن می توانید از مناظر پیچیده تا ساختمان ها و اشیا داخل بازی را ایجاد کنید. Editor آنریل انجین از بخش های ذیل تشکیل شده است:

* Level Editor: این ابزار، Editor اصلی جهت ساخت مراحل بازیتان می باشد. به بیان ساده اینجا جائی است که فضای بازی را بوسیله افزودن Actor ها، Geomery ها، کدهای Blueptints، سیستم Particle و یا هر چیزی که می خواهید در آن باشد تعریف می نمائید. به صورت پیش فرض پس از ایجاد یک پروژه جدید، آن پروژه در Level Editor باز می شود.
* Material Editor: این ابزار جائی است که شما می توانید بافت هائی را – مانند سنگ، شیشه، چوب و ... - جهت اعمال بر حجم ها و سطوح سه بعدی ساخته یا ویرایش نمائید تا شکل بصری آن ها را کنترل کنید. برای مثال شما می توانید با استفاده از این ابزار بافت گِل را ایجاد نموده و آن را بر روی کف خیابان ها یا کوه های داخل بازی اعمال نمائید تا سطح آنها گِلی به نظر برسد.
* Blueprint Editor: با استفاده از این ابزار به شکل کاملا بصری قادر به ویرایش و یا کار با Blueprint هایتان خواهید بود، Asset هائی ویژه که به شما توانائی ایجاد انواع جدید Actor و کنترل روند و خدادهای بازی را می دهند، بدون حتی یک خط کد نویسی در C++.
* Behavior Tree Editor: در داخل این ابزار شما توانائی ایجاد و تعیین [هوش مصنوعی  یا AI](https://en.wikipedia.org/wiki/Artificial_intelligence) را از طریق یک سیستم بصری مبتنی بر Node (درست مانند Blueprints) برای Actor های داخل مراحل خود خواهید داشت (که می تواند هر تعداد رفتار را برای دشمنان، کاراکترهای [NPC](https://en.wikipedia.org/wiki/Non-player_character)، خودروها و ... شامل شود).
* Persona Editor: مجموعه ای از ابزارها جهت ویرایش انیمیشن در UE4 می باشد که برای ویرایش Skeleton Asset ها، Skeletal Mesh ها، Animation Blueprint ها و انواع دیگر Asset های انیمیشن به کار می رود. غالب (اگر نه تمامی) کار انیمیشن شما در UE4 در این Editor اتفاق می افتد.
* Cascade Editor: در UE4 تمامی Cascade Particle System ها داخل این ابزار ویرایش می شوند که یک محیط مجتمع ویرایشگر ماژولار افکت های ذرات است (مانند: انفجار، آتش، گرد و خاک، باران و ...). Cascade مشاهده آنی و بلادرنگ تغییرات را به همراه ویرایش ماژولار جلوه ها، فراهم می آورد.
* UMG UI Editor: یک ابزار بصری ساخت [رابط کاربری یا UI](https://en.wikipedia.org/wiki/Artificial_intelligence) می باشد که می توان از آن برای ساخت عناصر رابط کاربری مانند [In-game HUD](https://en.wikipedia.org/wiki/HUD_%28video_gaming%29)، منوها و سایر عناصر گرافیکی مربوط به رابط کاربری که می خواهید به کاربر نشان دهید، استفاده نمود.
* Matinee Editor: اساس آن ترک های انیمیشن ویژه ای هستند که می توانید درون آن ها [Keyframe](https://en.wikipedia.org/wiki/Key_frame) هایتان را برای تعیین خصوصیات خاصی از Actor های درون مراحل، بگنجانید. با استفاده از آن می توانید دست به خلق سینماتیک های داخل بازی، رخدادهای Dynamic مربط به Gameplay یا حتی Animate نمودن خصوصیات Actor ها به مرور زمان نمائید (مثلا تغییر روشنائی یک نور).
* Sound Cue Editor: چگونگی پخش صدا در UE4 داخل Sound Cue ها تعریف می شود که توسط این Editor ویرایش می شوند. در آن می توانید چند Asset صدا را با یکدیگر ترکیب نموده و آن صدای واحد ترکیب شده را در قالب یک Sound Cue ذخیره نمائید.
* Paper2D Sprite Editor: قابلیت ساخت و ویرایش هر فریم جداگانه از Sprite های Paper 2D (که در واقع راهی ساده و سریع جهت ساخت انیمیشن های دوبعدی در UE4 هستند) را فراهم می آورد.
* Paper2D Flipbook Editor: با استفاده از آن می توانید انیمیشن های دوبعدی درست کنید که Flipbook نامیده می شود. این اتفاق با تعیین نمودن یک رشته از Sprite ها در قالب تعداد مشخصی Keyframe در Paper 2D Flipbook میسر می شود که با ورق خوردن هر فریم یک انیمیشن ساخته می شود. بهترین راه جهت درک Flipbook ها تصور انیمیشن های سنتی و قدیمی هستند که با دست طراحی می شدند.
* Physics Asset Tool Editor: که به اختصار PhAT هم نامیده می شود در جهت ساخت Asset های فیزیک به منظور استفاده در Skeletal Mesh ها به کار می رود. در آن به سادگی می توان بدون هیچ پیش زمینه ای یک [Ragdoll](https://en.wikipedia.org/wiki/Ragdoll_physics) ساخته و یا با استفاده از ابزارهای خودکار Physic Body ها و Physics Constraint ها را ایجاد نمود.
* Static Mesh Editor: با استفاده از این ابزار می توان اقدام به نمایش ظاهر، [برخورد](https://en.wikipedia.org/wiki/Collision_%28computer_science%29) و [UV](https://en.wikipedia.org/wiki/UV_mapping) ها نموده، همچنین خصوصیات Static Mesh ها را دستکاری نمود. علاوه بر آن در این Editor می توان تنظیمات [LOD یا Level of Detail](https://en.wikipedia.org/wiki/Level_of_detail) را برای Static Mesh Asset ها تعیین نمود.
* Media Player Editor: این Editor شما را قادر به تعریف فایل های چندرسانه ای و یا URL ها جهت پخش در UE4 می سازد. با وجود آنکه لزوما یک Editor محسوب نمی شود (به این جهت که امکان ویرایش فایل های چندرسانه ای را به شما نمی دهد) اجازه تعیین اینکه فایل یا URL شما چگونه پخش شود را به شما خواهد داد. از قبیل: Auto-playing, Play Rate یا Looping. همچنین می توانید با استفاده از آن اطلاعات مربوط به Media خود را مشاهده نمائید.علاوه بر آن، اجازه پخش فایل یا URL تان را به شما خواهد داد.

<br />
در زمان مناسب با هریک از این Editor ها و مفاهیم مطرح شده آن ها آشنا خواهیم شد.
<br />


<br />
<a name="ide"></a>

### محیط توسعه ###

چنانچه از Blueprints Visual Scripting یا کدنویسی بصری استفاده نمائید تمام کد نویسی شما در محیط Unreal Editor انجام خواهد شد و نیاز به هیچ ابزار دیگری نخواهد بود.

در صورت انتخاب C++ به عنوان زبان اصلی توسعه در UE4، بسته به پلتفرمی که به عنوان پلتفرم توسعه انتخاب نموده اید [IDE](https://en.wikipedia.org/wiki/Integrated_development_environment) مقصد متفاوت خواهد بود.


* محیط رسمی مورد پشتیبانی جهت توسعه در پلتفرم ویندوز [Microsoft Visual Studio](https://en.wikipedia.org/wiki/Microsoft_Visual_Studio) می باشد. تا نسخه 4.10.2 که آخرین نسخه پایدار فعلی است، بهتر است از Visual Studio 2013 Update 5 استفاده نمائید ([ابتدا اعلام شد که این نسخه با Visual Studio 2015 Update 1 سازگار نمی باشد اما بعدا اعلام شد که مشکلی وجود نداشته است](https://forums.unrealengine.com/showthread.php?96897-4-10-2-Hotfix-Released)). از آن جهت که مایکروسافت به اجبار تمامی توسعه دهندگان ویندوز را به ارتقا هرچه سریعتر به نسخه 2015 آن تشویق می نماید، در نسخه سری UE 4.11 و بالاتر، نسخه رسمی مورد پشتیبانی، Visual Studio 2015 با Update 1 و یا بالاتر می باشد. طبق گفته Epic از نسخه 4.11  به بعد پشتیبانی از Visual Studio 2013 منسوخ شد.
* در محیط Mac OS X همانطور که انتظار می رود محیط رسمی توسعه فقط [Apple Xcode](https://en.wikipedia.org/wiki/Xcode) می باشد.
* در محیط Linux روش پیشنهادی [Coss-Compile](https://en.wikipedia.org/wiki/Cross_compiler) از ویندوز برای لینوکس می باشد (در حال حاضر Coss-Compile از Mac OS X مقدور نمی باشد). اما می توان اقدام به تولید [Unix Makefile](https://en.wikipedia.org/wiki/Makefile) یا [CMakeLists.txt](https://en.wikipedia.org/wiki/CMake) نموده سپس با استفاده از یکی از IDE های [Qt Creator](https://en.wikipedia.org/wiki/Qt_Creator) یا [KDevelop](https://en.wikipedia.org/wiki/KDevelop) 4.6+ یا هر IDE با پشتیبانی از یکی از روش های فوق، اقدام به باز نمودن پروژه نمود. چناچه از KDevelop استفاده نمائید نیاز به حداقل 3 تا 4 گیگابایت رم خواهد بود. همچنین نیازمندی های مورد نیاز شامل [Mono](https://en.wikipedia.org/wiki/Mono_%28software%29) 3.x به علاوه Compiler [زبان C#](https://en.wikipedia.org/wiki/C_Sharp_%28programming_language%29) و کتابخانه های [.NET](https://en.wikipedia.org/wiki/.NET_Framework) نسخه 4.0، کامپایلر [Clang](https://en.wikipedia.org/wiki/Clang) 3.3.x تا 3.6.x بجز 3.5.x، کتابخانه [Qt](https://en.wikipedia.org/wiki/Qt_%28software%29) 4 یا 5  و یا [GTK](https://en.wikipedia.org/wiki/GTK%2B).


<br />
<a name="unreal-tournament"></a>

### Unreal Tournament ###

همزمان با [عرضه کد های UE4 از سوی Epic بر روی  GitHub](https://github.com/EpicGames/UnrealEngine)، یک [Repository](https://en.wikipedia.org/wiki/Software_repository) دیگر جهت [توسعه نسخه بعدی Unreal Tournament](https://en.wikipedia.org/wiki/Unreal_Tournament) بر [روی اکانت GitHub این شرکت](https://github.com/EpicGames/) ایجاد و کار بر روی آن بر اساس UE4 شروع شد. تاریخچه کامل توسعه آن به همراه تمامی منابع و Asset های مورد استفاده، برای همگان قابل رویت می باشد که آن را تبدیل به یک منبع آموزشی فوق العاده جهت استفاده افرادی که تمایل به مشاهده چگونگی ساخت بازی های بزرگ دارند، می نماید. به مانند کد UE4، شما حتی قابلیت اعمال تغییر بر روی کد آن و عرضه تغییرات خود به Epic را خواهید شد که ممکن است از سوی آن ها پذیرفته شود. Epic اعلام نموده که لزوما این Repository و محتویات آن، در ساخت Unreal Tournament بعدی مورد استفاده قرار نخواهد گرفت!

<br />
در ادامه این سری آموزشی، ابتدا به نحوه ی نصب، پیکربندی و راه اندازی UE4 با استفاده از Epic Games Launcher و یا دریافت و کامپایل از سورس کد به همراه تمامی پیش نیاز ها و ابزارهای آن خواهیم پرداخت. پس از آن قادر خواهیم بود توسعه بازی در محیط UE4 را به همراه هم تجربه نمائیم.
