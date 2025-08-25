<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1226517aae5f5b6f904434670394c688",
  "translation_date": "2025-08-25T21:54:54+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md",
  "language_code": "fa"
}
-->
# کنترل چراغ خواب از طریق اینترنت - سخت‌افزار مجازی IoT و رزبری پای

در این بخش از درس، شما داده‌های تله‌متری شامل سطح نور را از رزبری پای یا دستگاه مجازی IoT خود به یک MQTT broker ارسال خواهید کرد.

## ارسال تله‌متری

گام بعدی ایجاد یک سند JSON با داده‌های تله‌متری و ارسال آن به MQTT broker است.

### وظیفه

داده‌های تله‌متری را به MQTT broker ارسال کنید.

1. پروژه چراغ خواب را در VS Code باز کنید.

1. اگر از یک دستگاه مجازی IoT استفاده می‌کنید، مطمئن شوید که ترمینال در حال اجرای محیط مجازی است. اگر از رزبری پای استفاده می‌کنید، نیازی به استفاده از محیط مجازی ندارید.

1. وارد کردن زیر را به ابتدای فایل `app.py` اضافه کنید:

    ```python
    import json
    ```

    کتابخانه `json` برای کدگذاری داده‌های تله‌متری به عنوان یک سند JSON استفاده می‌شود.

1. عبارت زیر را بعد از تعریف `client_name` اضافه کنید:

    ```python
    client_telemetry_topic = id + '/telemetry'
    ```

    متغیر `client_telemetry_topic` موضوع MQTT است که دستگاه سطح نور را به آن ارسال خواهد کرد.

1. محتوای حلقه `while True:` در انتهای فایل را با کد زیر جایگزین کنید:

    ```python
    while True:
        light = light_sensor.light
        telemetry = json.dumps({'light' : light})

        print("Sending telemetry ", telemetry)
    
        mqtt_client.publish(client_telemetry_topic, telemetry)
    
        time.sleep(5)
    ```

    این کد سطح نور را در یک سند JSON بسته‌بندی کرده و آن را به MQTT broker ارسال می‌کند. سپس برای کاهش فرکانس ارسال پیام‌ها، برنامه را متوقف می‌کند.

1. کد را به همان روشی که در بخش قبلی تمرین اجرا کردید، اجرا کنید. اگر از یک دستگاه مجازی IoT استفاده می‌کنید، مطمئن شوید که برنامه CounterFit در حال اجرا است و حسگر نور و LED روی پین‌های صحیح ایجاد شده‌اند.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Sending telemetry  {"light": 0}
    Sending telemetry  {"light": 0}
    ```

> 💁 می‌توانید این کد را در پوشه [code-telemetry/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/virtual-device) یا پوشه [code-telemetry/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/pi) پیدا کنید.

😀 شما با موفقیت داده‌های تله‌متری را از دستگاه خود ارسال کردید.

**سلب مسئولیت**:  
این سند با استفاده از سرویس ترجمه هوش مصنوعی [Co-op Translator](https://github.com/Azure/co-op-translator) ترجمه شده است. در حالی که ما تلاش می‌کنیم دقت را حفظ کنیم، لطفاً توجه داشته باشید که ترجمه‌های خودکار ممکن است شامل خطاها یا نادرستی‌ها باشند. سند اصلی به زبان اصلی آن باید به عنوان منبع معتبر در نظر گرفته شود. برای اطلاعات حساس، توصیه می‌شود از ترجمه حرفه‌ای انسانی استفاده کنید. ما مسئولیتی در قبال سوء تفاهم‌ها یا تفسیرهای نادرست ناشی از استفاده از این ترجمه نداریم.