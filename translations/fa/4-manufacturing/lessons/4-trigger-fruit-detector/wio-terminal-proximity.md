# تشخیص نزدیکی - Wio Terminal

در این بخش از درس، شما یک حسگر نزدیکی به Wio Terminal خود اضافه می‌کنید و فاصله را از آن می‌خوانید.

## سخت‌افزار

Wio Terminal به یک حسگر نزدیکی نیاز دارد.

حسگری که استفاده می‌کنید یک [حسگر فاصله Grove Time of Flight](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html) است. این حسگر از یک ماژول اندازه‌گیری لیزری برای تشخیص فاصله استفاده می‌کند. این حسگر دارای محدوده‌ای از 10 میلی‌متر تا 2000 میلی‌متر (1 سانتی‌متر - 2 متر) است و مقادیر را در این محدوده با دقت نسبتاً خوبی گزارش می‌دهد. فاصله‌های بالای 1000 میلی‌متر به صورت 8109 میلی‌متر گزارش می‌شوند.

محدوده‌یاب لیزری در پشت حسگر قرار دارد، در سمت مخالف سوکت Grove.

این یک سوکت I  
C است.

### اتصال حسگر Time of Flight

حسگر Grove Time of Flight می‌تواند به Wio Terminal متصل شود.

#### وظیفه - اتصال حسگر Time of Flight

حسگر Time of Flight را متصل کنید.

![یک حسگر Grove Time of Flight](../../../../../translated_images/fa/grove-time-of-flight-sensor.d82ff2165bfded9f.webp)

1. یک سر کابل Grove را به سوکت روی حسگر Time of Flight وارد کنید. این کابل فقط از یک جهت وارد می‌شود.

1. با قطع اتصال Wio Terminal از کامپیوتر یا منبع تغذیه دیگر، سر دیگر کابل Grove را به سوکت Grove سمت چپ Wio Terminal متصل کنید. این سوکت نزدیک‌ترین سوکت به دکمه پاور است. این یک سوکت ترکیبی دیجیتال و I  
C است.

![حسگر Grove Time of Flight متصل به سوکت سمت چپ](../../../../../translated_images/fa/wio-time-of-flight-sensor.c4c182131d2ea73d.webp)

1. اکنون می‌توانید Wio Terminal را به کامپیوتر خود متصل کنید.

## برنامه‌نویسی حسگر Time of Flight

اکنون می‌توانید Wio Terminal را برای استفاده از حسگر Time of Flight متصل شده برنامه‌نویسی کنید.

### وظیفه - برنامه‌نویسی حسگر Time of Flight

1. یک پروژه جدید Wio Terminal با استفاده از PlatformIO ایجاد کنید. این پروژه را `distance-sensor` بنامید. کدی در تابع `setup` اضافه کنید تا پورت سریال را پیکربندی کند.

1. یک وابستگی کتابخانه برای کتابخانه حسگر فاصله Seeed Grove Time of Flight به فایل `platformio.ini` پروژه اضافه کنید:

    ```ini
    lib_deps =
        seeed-studio/Grove Ranging sensor - VL53L0X @ ^1.1.1
    ```

1. در `main.cpp`، کد زیر را زیر دستورات موجود `include` اضافه کنید تا یک نمونه از کلاس `Seeed_vl53l0x` برای تعامل با حسگر Time of Flight اعلام کنید:

    ```cpp
    #include "Seeed_vl53l0x.h"
    
    Seeed_vl53l0x VL53L0X;
    ```

1. کد زیر را به انتهای تابع `setup` اضافه کنید تا حسگر را مقداردهی اولیه کنید:

    ```cpp
    VL53L0X.VL53L0X_common_init();
    VL53L0X.VL53L0X_high_accuracy_ranging_init();
    ```

1. در تابع `loop`، یک مقدار از حسگر بخوانید:

    ```cpp
    VL53L0X_RangingMeasurementData_t RangingMeasurementData;
    memset(&RangingMeasurementData, 0, sizeof(VL53L0X_RangingMeasurementData_t));

    VL53L0X.PerformSingleRangingMeasurement(&RangingMeasurementData);
    ```

    این کد یک ساختار داده را برای خواندن داده‌ها مقداردهی اولیه می‌کند، سپس آن را به متد `PerformSingleRangingMeasurement` می‌فرستد تا با اندازه‌گیری فاصله پر شود.

1. زیر این کد، مقدار اندازه‌گیری فاصله را بنویسید، سپس به مدت 1 ثانیه تأخیر ایجاد کنید:

    ```cpp
    Serial.print("Distance = ");
    Serial.print(RangingMeasurementData.RangeMilliMeter);
    Serial.println(" mm");

    delay(1000);
    ```

1. این کد را بسازید، آپلود کنید و اجرا کنید. شما می‌توانید اندازه‌گیری‌های فاصله را با مانیتور سریال مشاهده کنید. اشیاء را نزدیک حسگر قرار دهید و اندازه‌گیری فاصله را مشاهده خواهید کرد:

    ```output
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    محدوده‌یاب در پشت حسگر قرار دارد، بنابراین هنگام اندازه‌گیری فاصله از سمت درست استفاده کنید.

    ![محدوده‌یاب در پشت حسگر Time of Flight که به سمت یک موز اشاره می‌کند](../../../../../translated_images/fa/time-of-flight-banana.079921ad8b1496e4.webp)

> 💁 می‌توانید این کد را در پوشه [code-proximity/wio-terminal](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/wio-terminal) پیدا کنید.

😀 برنامه حسگر نزدیکی شما موفقیت‌آمیز بود!

**سلب مسئولیت**:  
این سند با استفاده از سرویس ترجمه هوش مصنوعی [Co-op Translator](https://github.com/Azure/co-op-translator) ترجمه شده است. در حالی که ما تلاش می‌کنیم دقت را حفظ کنیم، لطفاً توجه داشته باشید که ترجمه‌های خودکار ممکن است شامل خطاها یا نادرستی‌ها باشند. سند اصلی به زبان اصلی آن باید به عنوان منبع معتبر در نظر گرفته شود. برای اطلاعات حساس، ترجمه حرفه‌ای انسانی توصیه می‌شود. ما مسئولیتی در قبال سوء تفاهم‌ها یا تفسیرهای نادرست ناشی از استفاده از این ترجمه نداریم.