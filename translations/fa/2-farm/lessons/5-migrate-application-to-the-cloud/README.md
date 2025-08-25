<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5f2d2f4a5a023c93ab34a0cc5b47c0c4",
  "translation_date": "2025-08-25T21:32:18+00:00",
  "source_file": "2-farm/lessons/5-migrate-application-to-the-cloud/README.md",
  "language_code": "fa"
}
-->
# انتقال منطق برنامه به فضای ابری

![نمای کلی درس به صورت اسکچ‌نوت](../../../../../translated_images/lesson-9.dfe99c8e891f48e179724520da9f5794392cf9a625079281ccdcbf09bd85e1b6.fa.jpg)

> اسکچ‌نوت توسط [نیتیا ناراسیمهان](https://github.com/nitya). برای مشاهده نسخه بزرگ‌تر روی تصویر کلیک کنید.

این درس به عنوان بخشی از [پروژه IoT برای مبتدیان - سری کشاورزی دیجیتال](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) از [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn) تدریس شده است.

[![کنترل دستگاه IoT خود با کد بدون سرور](https://img.youtube.com/vi/VVZDcs5u1_I/0.jpg)](https://youtu.be/VVZDcs5u1_I)

## آزمون پیش از درس

[آزمون پیش از درس](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/17)

## مقدمه

در درس قبلی، یاد گرفتید که چگونه نظارت بر رطوبت خاک گیاه و کنترل رله را به یک سرویس IoT مبتنی بر ابر متصل کنید. گام بعدی انتقال کد سرور که زمان‌بندی رله را کنترل می‌کند به فضای ابری است. در این درس یاد می‌گیرید که چگونه این کار را با استفاده از توابع بدون سرور انجام دهید.

در این درس به موارد زیر خواهیم پرداخت:

* [بدون سرور چیست؟](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [ایجاد یک برنامه بدون سرور](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [ایجاد یک تریگر رویداد IoT Hub](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [ارسال درخواست‌های متد مستقیم از کد بدون سرور](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [استقرار کد بدون سرور در فضای ابری](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)

## بدون سرور چیست؟

بدون سرور، یا محاسبات بدون سرور، شامل ایجاد بلوک‌های کوچک کدی است که در پاسخ به انواع مختلف رویدادها در فضای ابری اجرا می‌شوند. وقتی رویدادی رخ می‌دهد، کد شما اجرا شده و داده‌های مربوط به رویداد به آن ارسال می‌شود. این رویدادها می‌توانند از منابع مختلفی باشند، از جمله درخواست‌های وب، پیام‌های قرار داده شده در صف، تغییرات داده در یک پایگاه داده، یا پیام‌های ارسال شده به یک سرویس IoT توسط دستگاه‌های IoT.

![رویدادهایی که از یک سرویس IoT به یک سرویس بدون سرور ارسال می‌شوند و همگی به طور همزمان توسط چندین تابع پردازش می‌شوند](../../../../../translated_images/iot-messages-to-serverless.0194da1cc0732bb7d0f823aed3fce54735c6b1ad3bf36089804d8aaefc0a774f.fa.png)

> 💁 اگر قبلاً از تریگرهای پایگاه داده استفاده کرده‌اید، می‌توانید این را مشابه همان بدانید، کدی که با یک رویداد مانند درج یک ردیف فعال می‌شود.

![وقتی رویدادهای زیادی به طور همزمان ارسال می‌شوند، سرویس بدون سرور مقیاس‌پذیری می‌کند تا همه آنها را به طور همزمان اجرا کند](../../../../../translated_images/serverless-scaling.f8c769adf0413fd17be1af4f07ff63016b347e2ff869be6c4abb211f9e93909d.fa.png)

کد شما فقط زمانی اجرا می‌شود که رویدادی رخ دهد و در زمان‌های دیگر فعال نیست. این باعث می‌شود بدون سرور بسیار مقیاس‌پذیر باشد - اگر رویدادهای زیادی به طور همزمان رخ دهند، ارائه‌دهنده ابر می‌تواند تابع شما را به تعداد دفعات مورد نیاز به طور همزمان اجرا کند. نقطه ضعف این مدل این است که اگر نیاز به اشتراک‌گذاری اطلاعات بین رویدادها داشته باشید، باید آن را در جایی مانند پایگاه داده ذخیره کنید و نمی‌توانید آن را در حافظه نگه دارید.

کد شما به صورت یک تابع نوشته می‌شود که جزئیات رویداد را به عنوان یک پارامتر دریافت می‌کند. شما می‌توانید از طیف گسترده‌ای از زبان‌های برنامه‌نویسی برای نوشتن این توابع بدون سرور استفاده کنید.

> 🎓 بدون سرور همچنین به عنوان "توابع به عنوان سرویس" (FaaS) شناخته می‌شود، زیرا هر تریگر رویداد به عنوان یک تابع در کد پیاده‌سازی می‌شود.

با وجود نام آن، بدون سرور در واقع از سرورها استفاده می‌کند. این نام‌گذاری به این دلیل است که شما به عنوان یک توسعه‌دهنده نیازی به نگرانی درباره سرورهای مورد نیاز برای اجرای کد خود ندارید، تنها چیزی که برای شما مهم است این است که کد شما در پاسخ به یک رویداد اجرا شود. ارائه‌دهنده ابر یک *زمان اجرای بدون سرور* دارد که مدیریت تخصیص سرورها، شبکه، ذخیره‌سازی، CPU، حافظه و هر چیز دیگری که برای اجرای کد شما لازم است را بر عهده دارد. این مدل به این معنی است که شما نمی‌توانید به ازای هر سرور هزینه پرداخت کنید، زیرا سروری وجود ندارد. در عوض، شما برای زمانی که کد شما اجرا می‌شود و مقدار حافظه استفاده شده هزینه پرداخت می‌کنید.

> 💰 بدون سرور یکی از ارزان‌ترین روش‌ها برای اجرای کد در فضای ابری است. به عنوان مثال، در زمان نگارش این متن، یک ارائه‌دهنده ابر اجازه می‌دهد تمام توابع بدون سرور شما در مجموع ۱,۰۰۰,۰۰۰ بار در ماه اجرا شوند قبل از اینکه هزینه‌ای دریافت شود، و پس از آن برای هر ۱,۰۰۰,۰۰۰ اجرا ۰.۲۰ دلار آمریکا هزینه دریافت می‌کند. وقتی کد شما اجرا نمی‌شود، هزینه‌ای پرداخت نمی‌کنید.

برای یک توسعه‌دهنده IoT، مدل بدون سرور ایده‌آل است. شما می‌توانید تابعی بنویسید که در پاسخ به پیام‌های ارسال شده از هر دستگاه IoT متصل به سرویس IoT میزبانی شده در ابر فراخوانی شود. کد شما تمام پیام‌های ارسال شده را مدیریت می‌کند، اما فقط زمانی که لازم باشد اجرا می‌شود.

✅ به کدی که به عنوان کد سرور برای گوش دادن به پیام‌ها از طریق MQTT نوشته‌اید نگاهی بیندازید. چگونه ممکن است این کد در فضای ابری با استفاده از بدون سرور اجرا شود؟ فکر می‌کنید کد چگونه باید تغییر کند تا از محاسبات بدون سرور پشتیبانی کند؟

> 💁 مدل بدون سرور در حال گسترش به سایر خدمات ابری نیز هست، علاوه بر اجرای کد. به عنوان مثال، پایگاه داده‌های بدون سرور در فضای ابری با مدل قیمت‌گذاری بدون سرور در دسترس هستند، جایی که شما به ازای هر درخواست انجام شده علیه پایگاه داده هزینه پرداخت می‌کنید، مانند یک کوئری یا درج، معمولاً با قیمت‌گذاری بر اساس میزان کاری که برای انجام درخواست انجام می‌شود. به عنوان مثال، یک انتخاب ساده از یک ردیف بر اساس کلید اصلی هزینه کمتری نسبت به یک عملیات پیچیده که چندین جدول را به هم متصل می‌کند و هزاران ردیف را بازمی‌گرداند خواهد داشت.

## ایجاد یک برنامه بدون سرور

سرویس محاسبات بدون سرور مایکروسافت به نام Azure Functions شناخته می‌شود.

![لوگوی Azure Functions](../../../../../translated_images/azure-functions-logo.1cfc8e3204c9c44aaf80fcf406fc8544d80d7f00f8d3e8ed6fed764563e17564.fa.png)

ویدئوی کوتاه زیر نمای کلی از Azure Functions ارائه می‌دهد:

[![ویدئوی نمای کلی Azure Functions](https://img.youtube.com/vi/8-jz5f_JyEQ/0.jpg)](https://www.youtube.com/watch?v=8-jz5f_JyEQ)

> 🎥 برای مشاهده ویدئو روی تصویر بالا کلیک کنید.

✅ لحظه‌ای وقت بگذارید و نمای کلی Azure Functions را در [مستندات Microsoft Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-overview?WT.mc_id=academic-17441-jabenn) مطالعه کنید.

برای نوشتن Azure Functions، شما با یک برنامه Azure Functions در زبان مورد نظر خود شروع می‌کنید. Azure Functions به صورت پیش‌فرض از زبان‌های Python، JavaScript، TypeScript، C#، F#، Java و Powershell پشتیبانی می‌کند. در این درس یاد می‌گیرید که چگونه یک برنامه Azure Functions را با استفاده از Python بنویسید.

> 💁 Azure Functions همچنین از هندلرهای سفارشی پشتیبانی می‌کند، بنابراین می‌توانید توابع خود را در هر زبانی که از درخواست‌های HTTP پشتیبانی می‌کند بنویسید، از جمله زبان‌های قدیمی‌تر مانند COBOL.

برنامه‌های توابع شامل یک یا چند *تریگر* هستند - توابعی که به رویدادها پاسخ می‌دهند. شما می‌توانید چندین تریگر در یک برنامه توابع داشته باشید که همگی تنظیمات مشترکی را به اشتراک می‌گذارند. به عنوان مثال، در فایل تنظیمات برنامه توابع خود می‌توانید جزئیات اتصال IoT Hub خود را داشته باشید و تمام توابع در برنامه می‌توانند از این برای اتصال و گوش دادن به رویدادها استفاده کنند.

### وظیفه - نصب ابزارهای Azure Functions

> در زمان نگارش این متن، ابزارهای کدنویسی Azure Functions به طور کامل بر روی Apple Silicon با پروژه‌های Python کار نمی‌کنند. شما باید از یک مک مبتنی بر Intel، کامپیوتر ویندوزی یا کامپیوتر لینوکس استفاده کنید.

یکی از ویژگی‌های عالی Azure Functions این است که می‌توانید آنها را به صورت محلی اجرا کنید. همان زمان اجرایی که در فضای ابری استفاده می‌شود می‌تواند روی کامپیوتر شما اجرا شود و به شما امکان می‌دهد کدی بنویسید که به پیام‌های IoT پاسخ دهد و آن را به صورت محلی اجرا کنید. شما حتی می‌توانید کد خود را هنگام مدیریت رویدادها اشکال‌زدایی کنید. هنگامی که از کد خود راضی شدید، می‌توانید آن را در فضای ابری مستقر کنید.

ابزارهای Azure Functions به صورت یک CLI در دسترس هستند که به عنوان Azure Functions Core Tools شناخته می‌شود.

1. ابزارهای اصلی Azure Functions را با دنبال کردن دستورالعمل‌های موجود در [مستندات Azure Functions Core Tools](https://docs.microsoft.com/azure/azure-functions/functions-run-local?WT.mc_id=academic-17441-jabenn) نصب کنید.

1. افزونه Azure Functions را برای VS Code نصب کنید. این افزونه از ایجاد، اشکال‌زدایی و استقرار توابع Azure پشتیبانی می‌کند. به [مستندات افزونه Azure Functions](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-azuretools.vscode-azurefunctions) مراجعه کنید تا دستورالعمل‌های نصب این افزونه در VS Code را مشاهده کنید.

هنگامی که برنامه Azure Functions خود را در فضای ابری مستقر می‌کنید، نیاز به استفاده از مقدار کمی فضای ذخیره‌سازی ابری برای ذخیره مواردی مانند فایل‌های برنامه و فایل‌های گزارش دارد. وقتی برنامه توابع خود را به صورت محلی اجرا می‌کنید، همچنان نیاز به اتصال به فضای ذخیره‌سازی ابری دارید، اما به جای استفاده از فضای ذخیره‌سازی واقعی ابری، می‌توانید از یک شبیه‌ساز ذخیره‌سازی به نام [Azurite](https://github.com/Azure/Azurite) استفاده کنید. این شبیه‌ساز به صورت محلی اجرا می‌شود اما مانند فضای ذخیره‌سازی ابری عمل می‌کند.

> 🎓 در Azure، فضای ذخیره‌سازی که Azure Functions استفاده می‌کند یک حساب ذخیره‌سازی Azure است. این حساب‌ها می‌توانند فایل‌ها، بلو‌ب‌ها، داده‌ها در جداول یا داده‌ها در صف‌ها را ذخیره کنند. شما می‌توانید یک حساب ذخیره‌سازی را بین چندین برنامه به اشتراک بگذارید، مانند یک برنامه توابع و یک برنامه وب.

1. Azurite یک برنامه Node.js است، بنابراین باید Node.js را نصب کنید. می‌توانید دستورالعمل‌های دانلود و نصب را در [وب‌سایت Node.js](https://nodejs.org/) پیدا کنید. اگر از مک استفاده می‌کنید، می‌توانید آن را از [Homebrew](https://formulae.brew.sh/formula/node) نیز نصب کنید.

1. Azurite را با استفاده از دستور زیر نصب کنید (`npm` ابزاری است که هنگام نصب Node.js نصب می‌شود):

    ```sh
    npm install -g azurite
    ```

1. یک پوشه به نام `azurite` برای Azurite ایجاد کنید تا داده‌ها را در آن ذخیره کند:

    ```sh
    mkdir azurite
    ```

1. Azurite را اجرا کنید و این پوشه جدید را به آن بدهید:

    ```sh
    azurite --location azurite
    ```

    شبیه‌ساز ذخیره‌سازی Azurite راه‌اندازی شده و آماده اتصال زمان اجرای محلی توابع خواهد بود.

    ```output
    ➜  ~ azurite --location azurite  
    Azurite Blob service is starting at http://127.0.0.1:10000
    Azurite Blob service is successfully listening at http://127.0.0.1:10000
    Azurite Queue service is starting at http://127.0.0.1:10001
    Azurite Queue service is successfully listening at http://127.0.0.1:10001
    Azurite Table service is starting at http://127.0.0.1:10002
    Azurite Table service is successfully listening at http://127.0.0.1:10002
    ```

### وظیفه - ایجاد یک پروژه Azure Functions

CLI Azure Functions می‌تواند برای ایجاد یک برنامه توابع جدید استفاده شود.

1. یک پوشه برای برنامه توابع خود ایجاد کنید و به آن بروید. نام آن را `soil-moisture-trigger` بگذارید:

    ```sh
    mkdir soil-moisture-trigger
    cd soil-moisture-trigger
    ```

1. یک محیط مجازی Python در این پوشه ایجاد کنید:

    ```sh
    python3 -m venv .venv
    ```

1. محیط مجازی را فعال کنید:

    * در ویندوز:
        * اگر از Command Prompt یا Command Prompt از طریق Windows Terminal استفاده می‌کنید، دستور زیر را اجرا کنید:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * اگر از PowerShell استفاده می‌کنید، دستور زیر را اجرا کنید:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

    * در macOS یا Linux، دستور زیر را اجرا کنید:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 این دستورات باید از همان مکانی که دستور ایجاد محیط مجازی را اجرا کردید اجرا شوند. شما هرگز نیازی به رفتن به پوشه `.venv` ندارید، همیشه باید دستور فعال‌سازی و هر دستوری برای نصب بسته‌ها یا اجرای کد را از پوشه‌ای که محیط مجازی را در آن ایجاد کردید اجرا کنید.

1. دستور زیر را برای ایجاد یک برنامه توابع در این پوشه اجرا کنید:

    ```sh
    func init --worker-runtime python soil-moisture-trigger
    ```

    این دستور سه فایل در پوشه فعلی ایجاد می‌کند:

    * `host.json` - این سند JSON شامل تنظیمات برنامه توابع شما است. نیازی به تغییر این تنظیمات نخواهید داشت.
    * `local.settings.json` - این سند JSON شامل تنظیماتی است که برنامه شما هنگام اجرای محلی استفاده می‌کند، مانند رشته‌های اتصال برای IoT Hub. این تنظیمات فقط محلی هستند و نباید به کنترل کد منبع اضافه شوند. هنگامی که برنامه در فضای ابری مستقر می‌شود، این تنظیمات مستقر نمی‌شوند و به جای آن تنظیمات شما از تنظیمات برنامه بارگذاری می‌شوند. این موضوع در ادامه این درس پوشش داده خواهد شد.
    * `requirements.txt` - این یک [فایل نیازمندی‌های Pip](https://pip.pypa.io/en/stable/user_guide/#requirements-files) است که شامل بسته‌های Pip مورد نیاز برای اجرای برنامه توابع شما است.

1. فایل `local.settings.json` دارای تنظیماتی برای حساب ذخیره‌سازی است که برنامه توابع استفاده خواهد کرد. این مقدار به صورت پیش‌فرض خالی است، بنابراین باید تنظیم شود. برای اتصال به شبیه‌ساز ذخیره‌سازی محلی Azurite، این مقدار را به مقدار زیر تنظیم کنید:

    ```json
    "AzureWebJobsStorage": "UseDevelopmentStorage=true",
    ```

1. بسته‌های Pip لازم را با استفاده از فایل نیازمندی‌ها نصب کنید:

    ```sh
    pip install -r requirements.txt
    ```

    > 💁 بسته‌های Pip مورد نیاز باید در این فایل باشند، تا زمانی که برنامه توابع در فضای ابری مستقر شود، زمان اجرا بتواند بسته‌های صحیح را نصب کند.

1. برای آزمایش اینکه همه چیز به درستی کار می‌کند، می‌توانید زمان اجرای توابع را شروع کنید. دستور زیر را برای این کار اجرا کنید:

    ```sh
    func start
    ```

    خواهید دید که زمان اجرا شروع می‌شود و گزارش می‌دهد که هیچ تابع شغلی (تریگر) پیدا نکرده است.

    ```output
    (.venv) ➜  soil-moisture-trigger func start
    Found Python version 3.9.1 (python3).
    
    Azure Functions Core Tools
    Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    Function Runtime Version: 3.0.15417.0
    
    [2021-05-05T01:24:46.795Z] No job functions found.
    ```
> ⚠️ اگر اعلان فایروال دریافت کردید، دسترسی را تأیید کنید زیرا برنامه `func` نیاز دارد که بتواند به شبکه شما بخواند و بنویسد.
> ⚠️ اگر از macOS استفاده می‌کنید، ممکن است هشدارهایی در خروجی مشاهده کنید:
>
> ```output
    > (.venv) ➜  soil-moisture-trigger func start
    > Found Python version 3.9.1 (python3).
    >
    > Azure Functions Core Tools
    > Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    > Function Runtime Version: 3.0.15417.0
    >
    > [2021-06-16T08:18:28.315Z] Cannot create directory for shared memory usage: /dev/shm/AzureFunctions
    > [2021-06-16T08:18:28.316Z] System.IO.FileSystem: Access to the path '/dev/shm/AzureFunctions' is denied. Operation not permitted.
    > [2021-06-16T08:18:30.361Z] No job functions found.
    > ```
>
> می‌توانید این هشدارها را نادیده بگیرید، به شرطی که برنامه Functions به درستی اجرا شود و لیست توابع در حال اجرا را نمایش دهد. همان‌طور که در [این پرسش در Microsoft Docs Q&A](https://docs.microsoft.com/answers/questions/396617/azure-functions-core-tools-error-osx-devshmazurefu.html?WT.mc_id=academic-17441-jabenn) ذکر شده است، این هشدارها قابل چشم‌پوشی هستند.

1. برنامه Functions را با فشار دادن `ctrl+c` متوقف کنید.

1. پوشه فعلی را در VS Code باز کنید، یا با باز کردن VS Code و سپس باز کردن این پوشه، یا با اجرای دستور زیر:

    ```sh
    code .
    ```

    VS Code پروژه Functions شما را شناسایی کرده و یک اعلان نمایش می‌دهد که می‌گوید:

    ```output
    Detected an Azure Functions Project in folder "soil-moisture-trigger" that may have been created outside of
    VS Code. Initialize for optimal use with VS Code?
    ```

    ![اعلان](../../../../../translated_images/vscode-azure-functions-init-notification.bd19b49229963edb5311fb3a79445ea469424759d2917ee2f2eb6f92d65d5086.fa.png)

    گزینه **Yes** را از این اعلان انتخاب کنید.

1. مطمئن شوید که محیط مجازی Python در ترمینال VS Code اجرا شده است. در صورت نیاز آن را متوقف کرده و دوباره راه‌اندازی کنید.

## ایجاد یک محرک رویداد IoT Hub

برنامه Functions پوسته‌ای برای کد بدون سرور شما است. برای پاسخ به رویدادهای IoT Hub، می‌توانید یک محرک IoT Hub به این برنامه اضافه کنید. این محرک باید به جریان پیام‌هایی که به IoT Hub ارسال می‌شوند متصل شود و به آن‌ها پاسخ دهد. برای دریافت این جریان پیام‌ها، محرک شما باید به *نقطه پایانی سازگار با Event Hub* در IoT Hub متصل شود.

IoT Hub بر اساس یک سرویس دیگر Azure به نام Azure Event Hubs ساخته شده است. Event Hubs سرویسی است که به شما امکان ارسال و دریافت پیام‌ها را می‌دهد، و IoT Hub این قابلیت را برای دستگاه‌های IoT گسترش می‌دهد. روش اتصال برای خواندن پیام‌ها از IoT Hub مشابه روش استفاده از Event Hubs است.

✅ تحقیق کنید: نمای کلی Event Hubs را در [مستندات Azure Event Hubs](https://docs.microsoft.com/azure/event-hubs/event-hubs-about?WT.mc_id=academic-17441-jabenn) بخوانید. ویژگی‌های اصلی چگونه با IoT Hub مقایسه می‌شوند؟

برای اینکه یک دستگاه IoT به IoT Hub متصل شود، باید از یک کلید مخفی استفاده کند که اطمینان حاصل کند فقط دستگاه‌های مجاز می‌توانند متصل شوند. همین امر هنگام اتصال برای خواندن پیام‌ها نیز صدق می‌کند؛ کد شما به یک رشته اتصال نیاز دارد که شامل یک کلید مخفی و جزئیات IoT Hub باشد.

> 💁 رشته اتصال پیش‌فرضی که دریافت می‌کنید دارای مجوزهای **iothubowner** است، که به هر کدی که از آن استفاده کند مجوز کامل در IoT Hub می‌دهد. ایده‌آل این است که با پایین‌ترین سطح مجوزهای مورد نیاز متصل شوید. این موضوع در درس بعدی پوشش داده خواهد شد.

پس از اتصال محرک، کد داخل تابع برای هر پیام ارسال شده به IoT Hub، صرف نظر از اینکه کدام دستگاه آن را ارسال کرده است، فراخوانی می‌شود. پیام به عنوان یک پارامتر به محرک ارسال می‌شود.

### وظیفه - دریافت رشته اتصال نقطه پایانی سازگار با Event Hub

1. از ترمینال VS Code دستور زیر را اجرا کنید تا رشته اتصال برای نقطه پایانی سازگار با Event Hub در IoT Hub دریافت شود:

    ```sh
    az iot hub connection-string show --default-eventhub \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    `<hub_name>` را با نامی که برای IoT Hub خود استفاده کرده‌اید جایگزین کنید.

1. در VS Code، فایل `local.settings.json` را باز کنید. مقدار زیر را در بخش `Values` اضافه کنید:

    ```json
    "IOT_HUB_CONNECTION_STRING": "<connection string>"
    ```

    `<connection string>` را با مقدار مرحله قبل جایگزین کنید. برای معتبر بودن JSON، باید بعد از خط بالا یک کاما اضافه کنید.

### وظیفه - ایجاد یک محرک رویداد

اکنون آماده ایجاد محرک رویداد هستید.

1. از ترمینال VS Code دستور زیر را از داخل پوشه `soil-moisture-trigger` اجرا کنید:

    ```sh
    func new --name iot-hub-trigger --template "Azure Event Hub trigger"
    ```

    این دستور یک تابع جدید به نام `iot-hub-trigger` ایجاد می‌کند. این محرک به نقطه پایانی سازگار با Event Hub در IoT Hub متصل می‌شود، بنابراین می‌توانید از یک محرک Event Hub استفاده کنید. محرک خاصی برای IoT Hub وجود ندارد.

این دستور یک پوشه داخل پوشه `soil-moisture-trigger` به نام `iot-hub-trigger` ایجاد می‌کند که شامل این تابع است. این پوشه فایل‌های زیر را در خود دارد:

* `__init__.py` - این فایل کد Python است که شامل محرک است و از نام‌گذاری استاندارد فایل‌های Python برای تبدیل این پوشه به یک ماژول Python استفاده می‌کند.

    این فایل شامل کد زیر خواهد بود:

    ```python
    import logging

    import azure.functions as func


    def main(event: func.EventHubEvent):
        logging.info('Python EventHub trigger processed an event: %s',
                    event.get_body().decode('utf-8'))
    ```

    هسته محرک تابع `main` است. این تابع با رویدادهای IoT Hub فراخوانی می‌شود. این تابع یک پارامتر به نام `event` دارد که شامل یک `EventHubEvent` است. هر بار که پیامی به IoT Hub ارسال می‌شود، این تابع فراخوانی شده و پیام به عنوان `event` همراه با ویژگی‌هایی که مشابه توضیحات درس قبلی هستند، ارسال می‌شود.

    هسته این تابع رویداد را ثبت می‌کند.

* `function.json` - این فایل شامل تنظیمات محرک است. تنظیمات اصلی در بخشی به نام `bindings` قرار دارد. یک binding به معنای اتصال بین Azure Functions و سایر سرویس‌های Azure است. این تابع یک binding ورودی به یک Event Hub دارد - به Event Hub متصل شده و داده دریافت می‌کند.

    > 💁 شما همچنین می‌توانید binding‌های خروجی داشته باشید تا خروجی یک تابع به سرویس دیگری ارسال شود. به عنوان مثال، می‌توانید یک binding خروجی به یک پایگاه داده اضافه کنید و رویداد IoT Hub را از تابع بازگردانید، و به طور خودکار در پایگاه داده درج شود.

    ✅ تحقیق کنید: درباره binding‌ها در [مستندات مفاهیم محرک‌ها و binding‌های Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python) مطالعه کنید.

    بخش `bindings` شامل تنظیمات binding است. مقادیر مهم عبارتند از:

  * `"type": "eventHubTrigger"` - این مقدار به تابع می‌گوید که باید به رویدادهای Event Hub گوش دهد.
  * `"name": "events"` - این نام پارامتر برای رویدادهای Event Hub است. این مقدار با نام پارامتر در تابع `main` در کد Python مطابقت دارد.
  * `"direction": "in"` - این یک binding ورودی است، داده از Event Hub وارد تابع می‌شود.
  * `"connection": ""` - این مقدار نام تنظیماتی را تعریف می‌کند که رشته اتصال از آن خوانده می‌شود. هنگام اجرای محلی، این تنظیم از فایل `local.settings.json` خوانده می‌شود.

    > 💁 رشته اتصال نمی‌تواند در فایل `function.json` ذخیره شود، بلکه باید از تنظیمات خوانده شود. این کار برای جلوگیری از افشای تصادفی رشته اتصال انجام می‌شود.

1. به دلیل [یک باگ در قالب Azure Functions](https://github.com/Azure/azure-functions-templates/issues/1250)، مقدار `cardinality` در فایل `function.json` اشتباه است. این مقدار را از `many` به `one` تغییر دهید:

    ```json
    "cardinality": "one",
    ```

1. مقدار `"connection"` در فایل `function.json` را به مقدار جدیدی که به فایل `local.settings.json` اضافه کرده‌اید، به‌روزرسانی کنید:

    ```json
    "connection": "IOT_HUB_CONNECTION_STRING",
    ```

    > 💁 به یاد داشته باشید - این مقدار باید به تنظیمات اشاره کند، نه اینکه رشته اتصال واقعی را شامل شود.

1. رشته اتصال شامل مقدار `eventHubName` است، بنابراین مقدار این فیلد در فایل `function.json` باید خالی شود. این مقدار را به یک رشته خالی به‌روزرسانی کنید:

    ```json
    "eventHubName": "",
    ```

### وظیفه - اجرای محرک رویداد

1. مطمئن شوید که مانیتور رویداد IoT Hub اجرا نمی‌شود. اگر این برنامه همزمان با برنامه Functions اجرا شود، برنامه Functions نمی‌تواند متصل شده و رویدادها را مصرف کند.

    > 💁 چندین برنامه می‌توانند با استفاده از *گروه‌های مصرف‌کننده* مختلف به نقاط پایانی IoT Hub متصل شوند. این موضوع در درس بعدی پوشش داده خواهد شد.

1. برای اجرای برنامه Functions، دستور زیر را از ترمینال VS Code اجرا کنید:

    ```sh
    func start
    ```

    برنامه Functions راه‌اندازی شده و تابع `iot-hub-trigger` را شناسایی می‌کند. سپس هر رویدادی که در روز گذشته به IoT Hub ارسال شده باشد را پردازش می‌کند.

    ```output
    (.venv) ➜  soil-moisture-trigger func start
    Found Python version 3.9.1 (python3).
    
    Azure Functions Core Tools
    Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    Function Runtime Version: 3.0.15417.0
    
    Functions:
    
            iot-hub-trigger: eventHubTrigger
    
    For detailed output, run func with --verbose flag.
    [2021-05-05T02:44:07.517Z] Worker process started and initialized.
    [2021-05-05T02:44:09.202Z] Executing 'Functions.iot-hub-trigger' (Reason='(null)', Id=802803a5-eae9-4401-a1f4-176631456ce4)
    [2021-05-05T02:44:09.205Z] Trigger Details: PartitionId: 0, Offset: 1011240-1011632, EnqueueTimeUtc: 2021-05-04T19:04:04.2030000Z-2021-05-04T19:04:04.3900000Z, SequenceNumber: 2546-2547, Count: 2
    [2021-05-05T02:44:09.352Z] Python EventHub trigger processed an event: {"soil_moisture":628}
    [2021-05-05T02:44:09.354Z] Python EventHub trigger processed an event: {"soil_moisture":624}
    [2021-05-05T02:44:09.395Z] Executed 'Functions.iot-hub-trigger' (Succeeded, Id=802803a5-eae9-4401-a1f4-176631456ce4, Duration=245ms)
    ```

    هر فراخوانی به تابع با یک بلوک `Executing 'Functions.iot-hub-trigger'`/`Executed 'Functions.iot-hub-trigger'` در خروجی احاطه شده است، بنابراین می‌توانید ببینید که در هر فراخوانی تابع چند پیام پردازش شده است.

1. مطمئن شوید که دستگاه IoT شما اجرا می‌شود. پیام‌های جدید رطوبت خاک را در برنامه Functions مشاهده خواهید کرد.

1. برنامه Functions را متوقف کرده و دوباره راه‌اندازی کنید. خواهید دید که پیام‌های قبلی دوباره پردازش نمی‌شوند و فقط پیام‌های جدید پردازش می‌شوند.

> 💁 VS Code همچنین از اشکال‌زدایی توابع شما پشتیبانی می‌کند. می‌توانید نقاط توقف را با کلیک روی حاشیه کنار شروع هر خط کد، یا قرار دادن نشانگر روی یک خط کد و انتخاب *Run -> Toggle breakpoint*، یا فشار دادن `F9` تنظیم کنید. می‌توانید اشکال‌زدایی را با انتخاب *Run -> Start debugging*، فشار دادن `F5`، یا انتخاب پنل *Run and debug* و انتخاب دکمه **Start debugging** راه‌اندازی کنید. با این کار می‌توانید جزئیات رویدادهای پردازش شده را مشاهده کنید.

#### رفع اشکال

* اگر خطای زیر را دریافت کردید:

    ```output
    The listener for function 'Functions.iot-hub-trigger' was unable to start. Microsoft.WindowsAzure.Storage: Connection refused. System.Net.Http: Connection refused. System.Private.CoreLib: Connection refused.
    ```

    بررسی کنید که Azurite اجرا شده و مقدار `AzureWebJobsStorage` در فایل `local.settings.json` به `UseDevelopmentStorage=true` تنظیم شده باشد.

* اگر خطای زیر را دریافت کردید:

    ```output
    System.Private.CoreLib: Exception while executing function: Functions.iot-hub-trigger. System.Private.CoreLib: Result: Failure Exception: AttributeError: 'list' object has no attribute 'get_body'
    ```

    بررسی کنید که مقدار `cardinality` در فایل `function.json` به `one` تنظیم شده باشد.

* اگر خطای زیر را دریافت کردید:

    ```output
    Azure.Messaging.EventHubs: The path to an Event Hub may be specified as part of the connection string or as a separate value, but not both.  Please verify that your connection string does not have the `EntityPath` token if you are passing an explicit Event Hub name. (Parameter 'connectionString').
    ```

    بررسی کنید که مقدار `eventHubName` در فایل `function.json` به یک رشته خالی تنظیم شده باشد.

## ارسال درخواست‌های روش مستقیم از کد بدون سرور

تا اینجا برنامه Functions شما پیام‌ها را از IoT Hub با استفاده از نقطه پایانی سازگار با Event Hub دریافت می‌کند. اکنون باید دستورات را به دستگاه IoT ارسال کنید. این کار با استفاده از یک اتصال متفاوت به IoT Hub از طریق *Registry Manager* انجام می‌شود. Registry Manager ابزاری است که به شما امکان می‌دهد ببینید چه دستگاه‌هایی در IoT Hub ثبت شده‌اند و با آن‌ها ارتباط برقرار کنید، از جمله ارسال پیام‌های cloud-to-device، درخواست‌های روش مستقیم یا به‌روزرسانی دستگاه twin. همچنین می‌توانید از آن برای ثبت، به‌روزرسانی یا حذف دستگاه‌های IoT از IoT Hub استفاده کنید.

برای اتصال به Registry Manager، به یک رشته اتصال نیاز دارید.

### وظیفه - دریافت رشته اتصال Registry Manager

1. برای دریافت رشته اتصال، دستور زیر را اجرا کنید:

    ```sh
    az iot hub connection-string show --policy-name service \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    `<hub_name>` را با نامی که برای IoT Hub خود استفاده کرده‌اید جایگزین کنید.

    رشته اتصال برای سیاست *ServiceConnect* با استفاده از پارامتر `--policy-name service` درخواست می‌شود. هنگام درخواست رشته اتصال، می‌توانید مشخص کنید که این رشته اتصال چه مجوزهایی را اجازه می‌دهد. سیاست ServiceConnect به کد شما اجازه می‌دهد متصل شده و پیام‌ها را به دستگاه‌های IoT ارسال کند.

    ✅ تحقیق کنید: درباره سیاست‌های مختلف در [مستندات مجوزهای IoT Hub](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-security#iot-hub-permissions?WT.mc_id=academic-17441-jabenn) مطالعه کنید.

1. در VS Code، فایل `local.settings.json` را باز کنید. مقدار زیر را در بخش `Values` اضافه کنید:

    ```json
    "REGISTRY_MANAGER_CONNECTION_STRING": "<connection string>"
    ```

    `<connection string>` را با مقدار مرحله قبل جایگزین کنید. برای معتبر بودن JSON، باید بعد از خط بالا یک کاما اضافه کنید.

### وظیفه - ارسال درخواست روش مستقیم به یک دستگاه

1. SDK برای Registry Manager از طریق یک بسته Pip در دسترس است. خط زیر را به فایل `requirements.txt` اضافه کنید تا وابستگی به این بسته اضافه شود:

    ```sh
    azure-iot-hub
    ```

1. مطمئن شوید که ترمینال VS Code محیط مجازی را فعال کرده است و دستور زیر را برای نصب بسته‌های Pip اجرا کنید:

    ```sh
    pip install -r requirements.txt
    ```

1. واردات زیر را به فایل `__init__.py` اضافه کنید:

    ```python
    import json
    import os
    from azure.iot.hub import IoTHubRegistryManager
    from azure.iot.hub.models import CloudToDeviceMethod
    ```

    این واردات شامل برخی کتابخانه‌های سیستمی و همچنین کتابخانه‌هایی برای تعامل با Registry Manager و ارسال درخواست‌های روش مستقیم است.

1. کد داخل متد `main` را حذف کنید، اما خود متد را نگه دارید.

1. کد زیر را به متد `main` اضافه کنید:

    ```python
    body = json.loads(event.get_body().decode('utf-8'))
    device_id = event.iothub_metadata['connection-device-id']

    logging.info(f'Received message: {body} from {device_id}')
    ```

    این کد بدنه رویداد را استخراج می‌کند که شامل پیام JSON ارسال شده توسط دستگاه IoT است.

    سپس شناسه دستگاه را از توضیحات ارسال شده با پیام دریافت می‌کند. بدنه رویداد شامل پیام ارسال شده به عنوان telemetry است، و دیکشنری `iothub_metadata` شامل ویژگی‌هایی است که توسط IoT Hub تنظیم شده‌اند، مانند شناسه دستگاه فرستنده و زمان ارسال پیام.

    این اطلاعات سپس ثبت می‌شود. این ثبت در ترمینال هنگام اجرای برنامه Functions به صورت محلی قابل مشاهده خواهد بود.

1. کد زیر را در زیر این بخش اضافه کنید:

    ```python
    soil_moisture = body['soil_moisture']

    if soil_moisture > 450:
        direct_method = CloudToDeviceMethod(method_name='relay_on', payload='{}')
    else:
        direct_method = CloudToDeviceMethod(method_name='relay_off', payload='{}')
    ```

    این کد رطوبت خاک را از پیام دریافت می‌کند. سپس رطوبت خاک را بررسی کرده و بسته به مقدار آن، یک کلاس کمکی برای درخواست روش مستقیم برای روش‌های `relay_on` یا `relay_off` ایجاد می‌کند. درخواست روش نیازی به payload ندارد، بنابراین یک سند JSON خالی ارسال می‌شود.

1. کد زیر را در زیر این بخش اضافه کنید:

    ```python
    logging.info(f'Sending direct method request for {direct_method.method_name} for device {device_id}')

    registry_manager_connection_string = os.environ['REGISTRY_MANAGER_CONNECTION_STRING']
    registry_manager = IoTHubRegistryManager(registry_manager_connection_string)
    ```
این کد `REGISTRY_MANAGER_CONNECTION_STRING` را از فایل `local.settings.json` بارگذاری می‌کند. مقادیر موجود در این فایل به عنوان متغیرهای محیطی در دسترس قرار می‌گیرند و می‌توان آن‌ها را با استفاده از تابع `os.environ` خواند، تابعی که یک دیکشنری از تمام متغیرهای محیطی را برمی‌گرداند.

💁 وقتی این کد در فضای ابری مستقر شود، مقادیر موجود در فایل `local.settings.json` به عنوان *تنظیمات برنامه* تنظیم می‌شوند و می‌توان آن‌ها را از متغیرهای محیطی خواند.

سپس کد یک نمونه از کلاس کمکی Registry Manager را با استفاده از رشته اتصال ایجاد می‌کند.

1. کد زیر را اضافه کنید:

    ```python
    registry_manager.invoke_device_method(device_id, direct_method)

    logging.info('Direct method request sent!')
    ```

این کد به مدیر رجیستری می‌گوید که درخواست روش مستقیم را به دستگاهی که داده‌های تله‌متری ارسال کرده است، ارسال کند.

💁 در نسخه‌های قبلی برنامه که در درس‌های قبلی با استفاده از MQTT ایجاد کردید، دستورات کنترل رله به همه دستگاه‌ها ارسال می‌شد. کد فرض می‌کرد که فقط یک دستگاه دارید. این نسخه از کد درخواست روش را به یک دستگاه ارسال می‌کند، بنابراین اگر چندین مجموعه از حسگرهای رطوبت و رله داشته باشید، درخواست روش مستقیم مناسب را به دستگاه مناسب ارسال می‌کند.

1. برنامه Functions را اجرا کنید و مطمئن شوید که دستگاه IoT شما در حال ارسال داده است. پیام‌ها پردازش شده و درخواست‌های روش مستقیم ارسال خواهند شد. حسگر رطوبت خاک را داخل و خارج خاک حرکت دهید تا تغییر مقادیر و روشن و خاموش شدن رله را مشاهده کنید.

💁 می‌توانید این کد را در پوشه [code/functions](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud/code/functions) پیدا کنید.

## استقرار کد بدون سرور در فضای ابری

کد شما اکنون به صورت محلی کار می‌کند، بنابراین مرحله بعدی استقرار برنامه Functions در فضای ابری است.

### وظیفه - ایجاد منابع ابری

برنامه Functions شما باید در یک منبع Functions App در Azure مستقر شود که در داخل گروه منابعی که برای IoT Hub خود ایجاد کرده‌اید قرار دارد. همچنین به یک حساب ذخیره‌سازی در Azure نیاز دارید تا جایگزین حساب شبیه‌سازی شده‌ای شود که به صورت محلی اجرا می‌کنید.

1. دستور زیر را برای ایجاد یک حساب ذخیره‌سازی اجرا کنید:

    ```sh
    az storage account create --resource-group soil-moisture-sensor \
                              --sku Standard_LRS \
                              --name <storage_name> 
    ```

    `<storage_name>` را با یک نام برای حساب ذخیره‌سازی خود جایگزین کنید. این نام باید به صورت جهانی منحصر به فرد باشد زیرا بخشی از URL مورد استفاده برای دسترسی به حساب ذخیره‌سازی را تشکیل می‌دهد. فقط می‌توانید از حروف کوچک و اعداد برای این نام استفاده کنید، هیچ کاراکتر دیگری مجاز نیست و محدود به 24 کاراکتر است. از چیزی مانند `sms` استفاده کنید و یک شناسه منحصر به فرد به انتهای آن اضافه کنید، مانند چند کلمه تصادفی یا نام خود.

    گزینه `--sku Standard_LRS` سطح قیمت‌گذاری را انتخاب می‌کند و کم‌هزینه‌ترین حساب عمومی را انتخاب می‌کند. هیچ سطح رایگانی برای ذخیره‌سازی وجود ندارد و شما برای آنچه استفاده می‌کنید هزینه پرداخت می‌کنید. هزینه‌ها نسبتاً پایین هستند، با گران‌ترین ذخیره‌سازی کمتر از 0.05 دلار آمریکا در ماه به ازای هر گیگابایت ذخیره شده.

    ✅ درباره قیمت‌گذاری در صفحه [قیمت‌گذاری حساب ذخیره‌سازی Azure](https://azure.microsoft.com/pricing/details/storage/?WT.mc_id=academic-17441-jabenn) مطالعه کنید.

1. دستور زیر را برای ایجاد یک Function App اجرا کنید:

    ```sh
    az functionapp create --resource-group soil-moisture-sensor \
                          --runtime python \
                          --functions-version 3 \
                          --os-type Linux \
                          --consumption-plan-location <location> \
                          --storage-account <storage_name> \
                          --name <functions_app_name>
    ```

    `<location>` را با مکانی که هنگام ایجاد گروه منابع در درس قبلی استفاده کردید جایگزین کنید.

    `<storage_name>` را با نام حساب ذخیره‌سازی که در مرحله قبلی ایجاد کردید جایگزین کنید.

    `<functions_app_name>` را با یک نام منحصر به فرد برای Function App خود جایگزین کنید. این نام باید به صورت جهانی منحصر به فرد باشد زیرا بخشی از URL مورد استفاده برای دسترسی به Function App را تشکیل می‌دهد. از چیزی مانند `soil-moisture-sensor-` استفاده کنید و یک شناسه منحصر به فرد به انتهای آن اضافه کنید، مانند چند کلمه تصادفی یا نام خود.

    گزینه `--functions-version 3` نسخه Azure Functions را برای استفاده تنظیم می‌کند. نسخه 3 جدیدترین نسخه است.

    گزینه `--os-type Linux` به محیط اجرایی Functions می‌گوید که از لینوکس به عنوان سیستم‌عامل برای میزبانی این توابع استفاده کند. توابع می‌توانند بر روی لینوکس یا ویندوز میزبانی شوند، بسته به زبان برنامه‌نویسی مورد استفاده. برنامه‌های پایتون فقط بر روی لینوکس پشتیبانی می‌شوند.

### وظیفه - آپلود تنظیمات برنامه

هنگامی که برنامه Functions خود را توسعه دادید، برخی تنظیمات را در فایل `local.settings.json` برای رشته‌های اتصال IoT Hub ذخیره کردید. این تنظیمات باید به تنظیمات برنامه در Function App شما در Azure نوشته شوند تا بتوانند توسط کد شما استفاده شوند.

🎓 فایل `local.settings.json` فقط برای تنظیمات توسعه محلی است و نباید در کنترل کد منبع، مانند GitHub، بررسی شود. هنگامی که در فضای ابری مستقر می‌شود، از تنظیمات برنامه استفاده می‌شود. تنظیمات برنامه جفت‌های کلید/مقدار هستند که در فضای ابری میزبانی می‌شوند و از متغیرهای محیطی یا در کد شما یا توسط محیط اجرایی هنگام اتصال کد شما به IoT Hub خوانده می‌شوند.

1. دستور زیر را برای تنظیم مقدار `IOT_HUB_CONNECTION_STRING` در تنظیمات برنامه Function App اجرا کنید:

    ```sh
    az functionapp config appsettings set --resource-group soil-moisture-sensor \
                                          --name <functions_app_name> \
                                          --settings "IOT_HUB_CONNECTION_STRING=<connection string>"
    ```

    `<functions_app_name>` را با نامی که برای Function App خود استفاده کردید جایگزین کنید.

    `<connection string>` را با مقدار `IOT_HUB_CONNECTION_STRING` از فایل `local.settings.json` خود جایگزین کنید.

1. مرحله بالا را تکرار کنید، اما مقدار `REGISTRY_MANAGER_CONNECTION_STRING` را به مقدار مربوطه از فایل `local.settings.json` خود تنظیم کنید.

هنگامی که این دستورات را اجرا می‌کنید، لیستی از تمام تنظیمات برنامه برای Function App نیز خروجی داده می‌شود. می‌توانید از این لیست برای بررسی اینکه مقادیر شما به درستی تنظیم شده‌اند استفاده کنید.

💁 شما یک مقدار از پیش تنظیم شده برای `AzureWebJobsStorage` خواهید دید. در فایل `local.settings.json` شما، این مقدار برای استفاده از شبیه‌ساز ذخیره‌سازی محلی تنظیم شده بود. هنگامی که Function App را ایجاد کردید، حساب ذخیره‌سازی را به عنوان یک پارامتر ارسال کردید و این مقدار به طور خودکار در این تنظیم تنظیم می‌شود.

### وظیفه - استقرار Function App خود در فضای ابری

اکنون که Function App آماده است، کد شما می‌تواند مستقر شود.

1. دستور زیر را از ترمینال VS Code برای انتشار Function App خود اجرا کنید:

    ```sh
    func azure functionapp publish <functions_app_name>
    ```

    `<functions_app_name>` را با نامی که برای Function App خود استفاده کردید جایگزین کنید.

کد بسته‌بندی شده و به Function App ارسال می‌شود، جایی که مستقر و شروع می‌شود. خروجی کنسول زیادی وجود خواهد داشت که با تأیید استقرار و لیستی از توابع مستقر شده پایان می‌یابد. در این مورد لیست فقط شامل trigger خواهد بود.

```output
Deployment successful.
Remote build succeeded!
Syncing triggers...
Functions in soil-moisture-sensor:
    iot-hub-trigger - [eventHubTrigger]
```

مطمئن شوید که دستگاه IoT شما در حال اجرا است. سطح رطوبت را با تنظیم رطوبت خاک یا حرکت دادن حسگر داخل و خارج خاک تغییر دهید. خواهید دید که رله با تغییر رطوبت خاک روشن و خاموش می‌شود.

---

## 🚀 چالش

در درس قبلی، زمان‌بندی برای رله را با لغو اشتراک از پیام‌های MQTT در حالی که رله روشن بود و برای مدت کوتاهی پس از خاموش شدن آن مدیریت کردید. نمی‌توانید از این روش در اینجا استفاده کنید - نمی‌توانید trigger IoT Hub خود را لغو اشتراک کنید.

به روش‌های مختلفی فکر کنید که می‌توانید این موضوع را در Function App خود مدیریت کنید.

## آزمون پس از درس

[آزمون پس از درس](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/18)

## مرور و مطالعه شخصی

* درباره محاسبات بدون سرور در صفحه [محاسبات بدون سرور در ویکی‌پدیا](https://wikipedia.org/wiki/Serverless_computing) مطالعه کنید.
* درباره استفاده از بدون سرور در Azure و برخی مثال‌های بیشتر در پست وبلاگ [Go serverless for your IoT needs Azure](https://azure.microsoft.com/blog/go-serverless-for-your-iot-needs/?WT.mc_id=academic-17441-jabenn) مطالعه کنید.
* درباره Azure Functions بیشتر بیاموزید در [کانال یوتیوب Azure Functions](https://www.youtube.com/c/AzureFunctions).

## تکلیف

[افزودن کنترل دستی رله](assignment.md)

**سلب مسئولیت**:  
این سند با استفاده از سرویس ترجمه هوش مصنوعی [Co-op Translator](https://github.com/Azure/co-op-translator) ترجمه شده است. در حالی که ما تلاش می‌کنیم دقت را حفظ کنیم، لطفاً توجه داشته باشید که ترجمه‌های خودکار ممکن است شامل خطاها یا نادرستی‌ها باشند. سند اصلی به زبان اصلی آن باید به عنوان منبع معتبر در نظر گرفته شود. برای اطلاعات حساس، توصیه می‌شود از ترجمه حرفه‌ای انسانی استفاده کنید. ما هیچ مسئولیتی در قبال سوء تفاهم‌ها یا تفسیرهای نادرست ناشی از استفاده از این ترجمه نداریم.