<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "48ac21ec80329c930db7b84bd6b592ec",
  "translation_date": "2025-08-25T21:09:16+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/wio-terminal.md",
  "language_code": "fa"
}
-->
# طبقه‌بندی یک تصویر با استفاده از یک طبقه‌بند تصویر مبتنی بر IoT Edge - Wio Terminal

در این بخش از درس، از طبقه‌بند تصویر که روی دستگاه IoT Edge اجرا می‌شود استفاده خواهید کرد.

## استفاده از طبقه‌بند IoT Edge

دستگاه IoT می‌تواند برای استفاده از طبقه‌بند تصویر IoT Edge هدایت شود. آدرس URL برای طبقه‌بند تصویر به صورت `http://<IP address or name>/image` است، که در آن `<IP address or name>` باید با آدرس IP یا نام میزبان کامپیوتری که IoT Edge روی آن اجرا می‌شود جایگزین شود.

### وظیفه - استفاده از طبقه‌بند IoT Edge

1. پروژه اپلیکیشن `fruit-quality-detector` را باز کنید، اگر قبلاً باز نشده است.

1. طبقه‌بند تصویر به عنوان یک API REST با استفاده از HTTP اجرا می‌شود، نه HTTPS، بنابراین فراخوانی باید از یک کلاینت WiFi استفاده کند که فقط با فراخوانی‌های HTTP کار می‌کند. این به این معناست که گواهی‌نامه مورد نیاز نیست. `CERTIFICATE` را از فایل `config.h` حذف کنید.

1. آدرس URL پیش‌بینی در فایل `config.h` باید به آدرس جدید به‌روزرسانی شود. همچنین می‌توانید `PREDICTION_KEY` را حذف کنید زیرا نیازی به آن نیست.

    ```cpp
    const char *PREDICTION_URL = "<URL>";
    ```

    `<URL>` را با آدرس URL طبقه‌بند خود جایگزین کنید.

1. در فایل `main.cpp`، دستور include برای WiFi Client Secure را تغییر دهید تا نسخه استاندارد HTTP را وارد کند:

    ```cpp
    #include <WiFiClient.h>
    ```

1. اعلان `WiFiClient` را به نسخه HTTP تغییر دهید:

    ```cpp
    WiFiClient client;
    ```

1. خطی که گواهی‌نامه را روی کلاینت WiFi تنظیم می‌کند انتخاب کنید. خط `client.setCACert(CERTIFICATE);` را از تابع `connectWiFi` حذف کنید.

1. در تابع `classifyImage`، خط `httpClient.addHeader("Prediction-Key", PREDICTION_KEY);` که کلید پیش‌بینی را در هدر تنظیم می‌کند حذف کنید.

1. کد خود را آپلود و اجرا کنید. دوربین را به سمت میوه‌ای بگیرید و دکمه C را فشار دهید. خروجی را در مانیتور سریال مشاهده خواهید کرد:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 می‌توانید این کد را در پوشه [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/wio-terminal) پیدا کنید.

😀 برنامه طبقه‌بند کیفیت میوه شما موفقیت‌آمیز بود!

**سلب مسئولیت**:  
این سند با استفاده از سرویس ترجمه هوش مصنوعی [Co-op Translator](https://github.com/Azure/co-op-translator) ترجمه شده است. در حالی که ما تلاش می‌کنیم دقت را حفظ کنیم، لطفاً توجه داشته باشید که ترجمه‌های خودکار ممکن است شامل خطاها یا نادرستی‌ها باشند. سند اصلی به زبان اصلی آن باید به عنوان منبع معتبر در نظر گرفته شود. برای اطلاعات حساس، ترجمه حرفه‌ای انسانی توصیه می‌شود. ما هیچ مسئولیتی در قبال سوء تفاهم‌ها یا تفسیرهای نادرست ناشی از استفاده از این ترجمه نداریم.