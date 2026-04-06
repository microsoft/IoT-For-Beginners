# فراخوانی آشکارساز اشیاء از دستگاه IoT - Wio Terminal

پس از انتشار آشکارساز اشیاء، می‌توانید آن را از دستگاه IoT خود استفاده کنید.

## کپی کردن پروژه طبقه‌بندی تصویر

بخش عمده‌ای از آشکارساز موجودی شما مشابه طبقه‌بندی تصویری است که در درس قبلی ایجاد کردید.

### وظیفه - کپی کردن پروژه طبقه‌بندی تصویر

1. دوربین ArduCam خود را به Wio Terminal متصل کنید، با دنبال کردن مراحل [درس ۲ از پروژه تولید](../../../4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md#task---connect-the-camera).

    ممکن است بخواهید دوربین را در یک موقعیت ثابت قرار دهید، برای مثال، با آویزان کردن کابل روی یک جعبه یا قوطی، یا چسباندن دوربین به یک جعبه با نوار چسب دوطرفه.

1. یک پروژه جدید Wio Terminal با استفاده از PlatformIO ایجاد کنید. این پروژه را `stock-counter` نام‌گذاری کنید.

1. مراحل [درس ۲ از پروژه تولید](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) را برای گرفتن تصاویر از دوربین تکرار کنید.

1. مراحل [درس ۲ از پروژه تولید](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) را برای فراخوانی طبقه‌بندی تصویر تکرار کنید. بخش عمده‌ای از این کد برای آشکارسازی اشیاء مجدداً استفاده خواهد شد.

## تغییر کد از طبقه‌بندی‌کننده به آشکارساز تصویر

کدی که برای طبقه‌بندی تصاویر استفاده کردید بسیار مشابه کدی است که برای آشکارسازی اشیاء استفاده می‌شود. تفاوت اصلی در URL است که از Custom Vision دریافت کردید و نتایج فراخوانی.

### وظیفه - تغییر کد از طبقه‌بندی‌کننده به آشکارساز تصویر

1. دستور include زیر را به بالای فایل `main.cpp` اضافه کنید:

    ```cpp
    #include <vector>
    ```

1. تابع `classifyImage` را به `detectStock` تغییر نام دهید، هم نام تابع و هم فراخوانی آن در تابع `buttonPressed`.

1. بالای تابع `detectStock`، یک آستانه برای فیلتر کردن هرگونه آشکارسازی با احتمال پایین اعلام کنید:

    ```cpp
    const float threshold = 0.3f;
    ```

    برخلاف طبقه‌بندی‌کننده تصویر که فقط یک نتیجه برای هر برچسب بازمی‌گرداند، آشکارساز اشیاء چندین نتیجه بازمی‌گرداند، بنابراین هر نتیجه با احتمال پایین باید فیلتر شود.

1. بالای تابع `detectStock`، یک تابع برای پردازش پیش‌بینی‌ها اعلام کنید:

    ```cpp
    void processPredictions(std::vector<JsonVariant> &predictions)
    {
        for(JsonVariant prediction : predictions)
        {
            String tag = prediction["tagName"].as<String>();
            float probability = prediction["probability"].as<float>();
    
            char buff[32];
            sprintf(buff, "%s:\t%.2f%%", tag.c_str(), probability * 100.0);
            Serial.println(buff);
        }
    }
    ```

    این تابع لیستی از پیش‌بینی‌ها را دریافت کرده و آنها را در مانیتور سریال چاپ می‌کند.

1. در تابع `detectStock`، محتوای حلقه `for` که پیش‌بینی‌ها را مرور می‌کند با موارد زیر جایگزین کنید:

    ```cpp
    std::vector<JsonVariant> passed_predictions;

    for(JsonVariant prediction : predictions) 
    {
        float probability = prediction["probability"].as<float>();
        if (probability > threshold)
        {
            passed_predictions.push_back(prediction);
        }
    }

    processPredictions(passed_predictions);
    ```

    این حلقه پیش‌بینی‌ها را مرور کرده و احتمال آنها را با آستانه مقایسه می‌کند. تمام پیش‌بینی‌هایی که احتمال بالاتر از آستانه دارند به یک `list` اضافه شده و به تابع `processPredictions` ارسال می‌شوند.

1. کد خود را آپلود و اجرا کنید. دوربین را به سمت اشیاء روی یک قفسه بگیرید و دکمه C را فشار دهید. خروجی را در مانیتور سریال مشاهده خواهید کرد:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 17416
    tomato paste:   35.84%
    tomato paste:   35.87%
    tomato paste:   34.11%
    tomato paste:   35.16%
    ```

    > 💁 ممکن است نیاز باشد مقدار `threshold` را برای تصاویر خود تنظیم کنید.

    شما قادر خواهید بود تصویری که گرفته شده و این مقادیر را در تب **Predictions** در Custom Vision مشاهده کنید.

    ![4 قوطی رب گوجه‌فرنگی روی یک قفسه با پیش‌بینی‌هایی برای 4 آشکارسازی با درصدهای 35.8%، 33.5%، 25.7% و 16.6%](../../../../../translated_images/fa/custom-vision-stock-prediction.942266ab1bcca341.webp)

> 💁 می‌توانید این کد را در پوشه [code-detect/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-detect/wio-terminal) پیدا کنید.

😀 برنامه شمارنده موجودی شما موفقیت‌آمیز بود!

**سلب مسئولیت**:  
این سند با استفاده از سرویس ترجمه هوش مصنوعی [Co-op Translator](https://github.com/Azure/co-op-translator) ترجمه شده است. در حالی که ما تلاش می‌کنیم دقت را حفظ کنیم، لطفاً توجه داشته باشید که ترجمه‌های خودکار ممکن است شامل خطاها یا نادرستی‌ها باشند. سند اصلی به زبان اصلی آن باید به عنوان منبع معتبر در نظر گرفته شود. برای اطلاعات حساس، توصیه می‌شود از ترجمه حرفه‌ای انسانی استفاده کنید. ما مسئولیتی در قبال سوء تفاهم‌ها یا تفسیرهای نادرست ناشی از استفاده از این ترجمه نداریم.