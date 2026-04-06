# طبقه‌بندی یک تصویر - Wio Terminal

در این بخش از درس، تصویر گرفته‌شده توسط دوربین را به سرویس Custom Vision ارسال می‌کنید تا آن را طبقه‌بندی کند.

## طبقه‌بندی یک تصویر

سرویس Custom Vision دارای یک API REST است که می‌توانید از Wio Terminal برای طبقه‌بندی تصاویر به آن فراخوانی کنید. این API REST از طریق یک اتصال HTTPS - یک اتصال امن HTTP - قابل دسترسی است.

هنگام تعامل با نقاط پایانی HTTPS، کد کلاینت باید گواهی کلید عمومی را از سروری که به آن دسترسی دارد درخواست کند و از آن برای رمزگذاری ترافیکی که ارسال می‌کند استفاده کند. مرورگر وب شما این کار را به‌صورت خودکار انجام می‌دهد، اما میکروکنترلرها این قابلیت را ندارند. شما باید این گواهی را به‌صورت دستی درخواست کرده و از آن برای ایجاد یک اتصال امن به API REST استفاده کنید. این گواهی‌ها تغییر نمی‌کنند، بنابراین وقتی یک گواهی دارید، می‌توانید آن را به‌صورت سخت‌افزاری در برنامه خود کدنویسی کنید.

این گواهی‌ها شامل کلیدهای عمومی هستند و نیازی به نگهداری امن ندارند. می‌توانید از آن‌ها در کد منبع خود استفاده کنید و آن‌ها را به‌صورت عمومی در مکان‌هایی مانند GitHub به اشتراک بگذارید.

### وظیفه - تنظیم یک کلاینت SSL

1. اگر پروژه اپلیکیشن `fruit-quality-detector` باز نیست، آن را باز کنید.

1. فایل هدر `config.h` را باز کنید و کد زیر را اضافه کنید:

    ```cpp
    const char *CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "MIIF8zCCBNugAwIBAgIQAueRcfuAIek/4tmDg0xQwDANBgkqhkiG9w0BAQwFADBh\r\n"
        "MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\r\n"
        "d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBH\r\n"
        "MjAeFw0yMDA3MjkxMjMwMDBaFw0yNDA2MjcyMzU5NTlaMFkxCzAJBgNVBAYTAlVT\r\n"
        "MR4wHAYDVQQKExVNaWNyb3NvZnQgQ29ycG9yYXRpb24xKjAoBgNVBAMTIU1pY3Jv\r\n"
        "c29mdCBBenVyZSBUTFMgSXNzdWluZyBDQSAwNjCCAiIwDQYJKoZIhvcNAQEBBQAD\r\n"
        "ggIPADCCAgoCggIBALVGARl56bx3KBUSGuPc4H5uoNFkFH4e7pvTCxRi4j/+z+Xb\r\n"
        "wjEz+5CipDOqjx9/jWjskL5dk7PaQkzItidsAAnDCW1leZBOIi68Lff1bjTeZgMY\r\n"
        "iwdRd3Y39b/lcGpiuP2d23W95YHkMMT8IlWosYIX0f4kYb62rphyfnAjYb/4Od99\r\n"
        "ThnhlAxGtfvSbXcBVIKCYfZgqRvV+5lReUnd1aNjRYVzPOoifgSx2fRyy1+pO1Uz\r\n"
        "aMMNnIOE71bVYW0A1hr19w7kOb0KkJXoALTDDj1ukUEDqQuBfBxReL5mXiu1O7WG\r\n"
        "0vltg0VZ/SZzctBsdBlx1BkmWYBW261KZgBivrql5ELTKKd8qgtHcLQA5fl6JB0Q\r\n"
        "gs5XDaWehN86Gps5JW8ArjGtjcWAIP+X8CQaWfaCnuRm6Bk/03PQWhgdi84qwA0s\r\n"
        "sRfFJwHUPTNSnE8EiGVk2frt0u8PG1pwSQsFuNJfcYIHEv1vOzP7uEOuDydsmCjh\r\n"
        "lxuoK2n5/2aVR3BMTu+p4+gl8alXoBycyLmj3J/PUgqD8SL5fTCUegGsdia/Sa60\r\n"
        "N2oV7vQ17wjMN+LXa2rjj/b4ZlZgXVojDmAjDwIRdDUujQu0RVsJqFLMzSIHpp2C\r\n"
        "Zp7mIoLrySay2YYBu7SiNwL95X6He2kS8eefBBHjzwW/9FxGqry57i71c2cDAgMB\r\n"
        "AAGjggGtMIIBqTAdBgNVHQ4EFgQU1cFnOsKjnfR3UltZEjgp5lVou6UwHwYDVR0j\r\n"
        "BBgwFoAUTiJUIBiV5uNu5g/6+rkS7QYXjzkwDgYDVR0PAQH/BAQDAgGGMB0GA1Ud\r\n"
        "JQQWMBQGCCsGAQUFBwMBBggrBgEFBQcDAjASBgNVHRMBAf8ECDAGAQH/AgEAMHYG\r\n"
        "CCsGAQUFBwEBBGowaDAkBggrBgEFBQcwAYYYaHR0cDovL29jc3AuZGlnaWNlcnQu\r\n"
        "Y29tMEAGCCsGAQUFBzAChjRodHRwOi8vY2FjZXJ0cy5kaWdpY2VydC5jb20vRGln\r\n"
        "aUNlcnRHbG9iYWxSb290RzIuY3J0MHsGA1UdHwR0MHIwN6A1oDOGMWh0dHA6Ly9j\r\n"
        "cmwzLmRpZ2ljZXJ0LmNvbS9EaWdpQ2VydEdsb2JhbFJvb3RHMi5jcmwwN6A1oDOG\r\n"
        "MWh0dHA6Ly9jcmw0LmRpZ2ljZXJ0LmNvbS9EaWdpQ2VydEdsb2JhbFJvb3RHMi5j\r\n"
        "cmwwHQYDVR0gBBYwFDAIBgZngQwBAgEwCAYGZ4EMAQICMBAGCSsGAQQBgjcVAQQD\r\n"
        "AgEAMA0GCSqGSIb3DQEBDAUAA4IBAQB2oWc93fB8esci/8esixj++N22meiGDjgF\r\n"
        "+rA2LUK5IOQOgcUSTGKSqF9lYfAxPjrqPjDCUPHCURv+26ad5P/BYtXtbmtxJWu+\r\n"
        "cS5BhMDPPeG3oPZwXRHBJFAkY4O4AF7RIAAUW6EzDflUoDHKv83zOiPfYGcpHc9s\r\n"
        "kxAInCedk7QSgXvMARjjOqdakor21DTmNIUotxo8kHv5hwRlGhBJwps6fEVi1Bt0\r\n"
        "trpM/3wYxlr473WSPUFZPgP1j519kLpWOJ8z09wxay+Br29irPcBYv0GMXlHqThy\r\n"
        "8y4m/HyTQeI2IMvMrQnwqPpY+rLIXyviI2vLoI+4xKE4Rn38ZZ8m\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

    این گواهی *Microsoft Azure DigiCert Global Root G2* است - یکی از گواهی‌هایی که به‌صورت جهانی توسط بسیاری از سرویس‌های Azure استفاده می‌شود.

    > 💁 برای مشاهده اینکه این گواهی مورد استفاده است، دستور زیر را در macOS یا Linux اجرا کنید. اگر از ویندوز استفاده می‌کنید، می‌توانید این دستور را با استفاده از [Windows Subsystem for Linux (WSL)](https://docs.microsoft.com/windows/wsl/?WT.mc_id=academic-17441-jabenn) اجرا کنید:
    >
    > ```sh
    > openssl s_client -showcerts -verify 5 -connect api.cognitive.microsoft.com:443
    > ```
    >
    > خروجی گواهی DigiCert Global Root G2 را لیست خواهد کرد.

1. فایل `main.cpp` را باز کنید و دستور include زیر را اضافه کنید:

    ```cpp
    #include <WiFiClientSecure.h>
    ```

1. زیر دستورات include، یک نمونه از `WifiClientSecure` تعریف کنید:

    ```cpp
    WiFiClientSecure client;
    ```

    این کلاس شامل کدی برای ارتباط با نقاط پایانی وب از طریق HTTPS است.

1. در متد `connectWiFi`، `WiFiClientSecure` را تنظیم کنید تا از گواهی DigiCert Global Root G2 استفاده کند:

    ```cpp
    client.setCACert(CERTIFICATE);
    ```

### وظیفه - طبقه‌بندی یک تصویر

1. خط زیر را به‌عنوان یک خط اضافی به لیست `lib_deps` در فایل `platformio.ini` اضافه کنید:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    این خط [ArduinoJson](https://arduinojson.org)، یک کتابخانه JSON برای Arduino را وارد می‌کند و برای رمزگشایی پاسخ JSON از API REST استفاده خواهد شد.

1. در `config.h`، ثابت‌هایی برای URL پیش‌بینی و کلید از سرویس Custom Vision اضافه کنید:

    ```cpp
    const char *PREDICTION_URL = "<PREDICTION_URL>";
    const char *PREDICTION_KEY = "<PREDICTION_KEY>";
    ```

    `<PREDICTION_URL>` را با URL پیش‌بینی از Custom Vision جایگزین کنید. `<PREDICTION_KEY>` را با کلید پیش‌بینی جایگزین کنید.

1. در `main.cpp`، یک دستور include برای کتابخانه ArduinoJson اضافه کنید:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. تابع زیر را به `main.cpp`، بالای تابع `buttonPressed` اضافه کنید:

    ```cpp
    void classifyImage(byte *buffer, uint32_t length)
    {
        HTTPClient httpClient;
        httpClient.begin(client, PREDICTION_URL);
        httpClient.addHeader("Content-Type", "application/octet-stream");
        httpClient.addHeader("Prediction-Key", PREDICTION_KEY);
    
        int httpResponseCode = httpClient.POST(buffer, length);
    
        if (httpResponseCode == 200)
        {
            String result = httpClient.getString();
    
            DynamicJsonDocument doc(1024);
            deserializeJson(doc, result.c_str());
    
            JsonObject obj = doc.as<JsonObject>();
            JsonArray predictions = obj["predictions"].as<JsonArray>();
    
            for(JsonVariant prediction : predictions) 
            {
                String tag = prediction["tagName"].as<String>();
                float probability = prediction["probability"].as<float>();
    
                char buff[32];
                sprintf(buff, "%s:\t%.2f%%", tag.c_str(), probability * 100.0);
                Serial.println(buff);
            }
        }
    
        httpClient.end();
    }
    ```

    این کد با تعریف یک `HTTPClient` شروع می‌شود - کلاسی که شامل متدهایی برای تعامل با API‌های REST است. سپس کلاینت را با استفاده از نمونه `WiFiClientSecure` که با کلید عمومی Azure تنظیم شده است، به URL پیش‌بینی متصل می‌کند.

    پس از اتصال، هدرهایی ارسال می‌شود - اطلاعاتی درباره درخواست آینده که قرار است علیه API REST انجام شود. هدر `Content-Type` نشان می‌دهد که فراخوانی API داده‌های باینری خام ارسال خواهد کرد، و هدر `Prediction-Key` کلید پیش‌بینی Custom Vision را ارسال می‌کند.

    سپس یک درخواست POST به کلاینت HTTP ارسال می‌شود و یک آرایه بایتی آپلود می‌شود. این آرایه شامل تصویر JPEG گرفته‌شده از دوربین است که هنگام فراخوانی این تابع ارسال می‌شود.

    > 💁 درخواست‌های POST برای ارسال داده و دریافت پاسخ استفاده می‌شوند. انواع دیگری از درخواست‌ها مانند درخواست‌های GET وجود دارند که برای بازیابی داده‌ها استفاده می‌شوند. مرورگر وب شما از درخواست‌های GET برای بارگذاری صفحات وب استفاده می‌کند.

    درخواست POST یک کد وضعیت پاسخ بازمی‌گرداند. این کدها مقادیر تعریف‌شده‌ای هستند، که 200 به معنای **OK** است - درخواست POST موفقیت‌آمیز بود.

    > 💁 می‌توانید تمام کدهای وضعیت پاسخ را در [صفحه لیست کدهای وضعیت HTTP در ویکی‌پدیا](https://wikipedia.org/wiki/List_of_HTTP_status_codes) مشاهده کنید.

    اگر کد 200 بازگردانده شود، نتیجه از کلاینت HTTP خوانده می‌شود. این یک پاسخ متنی از API REST با نتایج پیش‌بینی به‌صورت یک سند JSON است. JSON به فرمت زیر است:

    ```jSON
    {
        "id":"45d614d3-7d6f-47e9-8fa2-04f237366a16",
        "project":"135607e5-efac-4855-8afb-c93af3380531",
        "iteration":"04f1c1fa-11ec-4e59-bb23-4c7aca353665",
        "created":"2021-06-10T17:58:58.959Z",
        "predictions":[
            {
                "probability":0.5582016,
                "tagId":"05a432ea-9718-4098-b14f-5f0688149d64",
                "tagName":"ripe"
            },
            {
                "probability":0.44179836,
                "tagId":"bb091037-16e5-418e-a9ea-31c6a2920f17",
                "tagName":"unripe"
            }
        ]
    }
    ```

    بخش مهم اینجا آرایه `predictions` است. این آرایه شامل پیش‌بینی‌ها است، با یک ورودی برای هر برچسب که شامل نام برچسب و احتمال آن است. احتمالات بازگردانده‌شده اعداد اعشاری بین 0 تا 1 هستند، که 0 به معنای 0% احتمال تطابق با برچسب و 1 به معنای 100% احتمال است.

    > 💁 طبقه‌بندی‌کننده‌های تصویر درصدها را برای تمام برچسب‌هایی که استفاده شده‌اند بازمی‌گردانند. هر برچسب یک احتمال دارد که تصویر با آن برچسب مطابقت داشته باشد.

    این JSON رمزگشایی می‌شود و احتمالات هر برچسب به مانیتور سریال ارسال می‌شود.

1. در تابع `buttonPressed`، کدی که در SD کارت ذخیره می‌شود را با یک فراخوانی به `classifyImage` جایگزین کنید، یا آن را بعد از نوشتن تصویر اضافه کنید، اما **قبل از** حذف بافر:

    ```cpp
    classifyImage(buffer, length);
    ```

    > 💁 اگر کدی که در SD کارت ذخیره می‌شود را جایگزین کنید، می‌توانید کد خود را با حذف توابع `setupSDCard` و `saveToSDCard` تمیز کنید.

1. کد خود را آپلود و اجرا کنید. دوربین را به سمت یک میوه بگیرید و دکمه C را فشار دهید. خروجی را در مانیتور سریال مشاهده خواهید کرد:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

    شما می‌توانید تصویری که گرفته شده و این مقادیر را در تب **Predictions** در Custom Vision مشاهده کنید.

    ![یک موز در Custom Vision پیش‌بینی شده به‌عنوان رسیده با 56.8% و نارس با 43.1%](../../../../../translated_images/fa/custom-vision-banana-prediction.30cdff4e1d72db5d.webp)

> 💁 می‌توانید این کد را در پوشه [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/wio-terminal) پیدا کنید.

😀 برنامه طبقه‌بندی کیفیت میوه شما موفقیت‌آمیز بود!

**سلب مسئولیت**:  
این سند با استفاده از سرویس ترجمه هوش مصنوعی [Co-op Translator](https://github.com/Azure/co-op-translator) ترجمه شده است. در حالی که ما تلاش می‌کنیم دقت را حفظ کنیم، لطفاً توجه داشته باشید که ترجمه‌های خودکار ممکن است شامل خطاها یا نادرستی‌ها باشند. سند اصلی به زبان اصلی آن باید به عنوان منبع معتبر در نظر گرفته شود. برای اطلاعات حساس، توصیه می‌شود از ترجمه حرفه‌ای انسانی استفاده کنید. ما مسئولیتی در قبال سوء تفاهم‌ها یا تفسیرهای نادرست ناشی از استفاده از این ترجمه نداریم.