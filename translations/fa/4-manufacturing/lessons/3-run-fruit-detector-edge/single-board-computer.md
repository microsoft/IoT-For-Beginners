<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "50151d9f9dce2801348a93880ef16d86",
  "translation_date": "2025-08-25T21:09:46+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/single-board-computer.md",
  "language_code": "fa"
}
-->
# طبقه‌بندی یک تصویر با استفاده از یک طبقه‌بند تصویر مبتنی بر IoT Edge - سخت‌افزار مجازی IoT و رزبری پای

در این بخش از درس، از طبقه‌بند تصویر که روی دستگاه IoT Edge اجرا می‌شود استفاده خواهید کرد.

## استفاده از طبقه‌بند IoT Edge

دستگاه IoT می‌تواند برای استفاده از طبقه‌بند تصویر IoT Edge هدایت شود. آدرس URL برای طبقه‌بند تصویر به صورت `http://<IP address or name>/image` است، که در آن `<IP address or name>` باید با آدرس IP یا نام میزبان کامپیوتری که IoT Edge روی آن اجرا می‌شود جایگزین شود.

کتابخانه پایتون برای Custom Vision فقط با مدل‌های میزبانی‌شده در فضای ابری کار می‌کند و با مدل‌های میزبانی‌شده روی IoT Edge سازگار نیست. به همین دلیل، باید از REST API برای فراخوانی طبقه‌بند استفاده کنید.

### وظیفه - استفاده از طبقه‌بند IoT Edge

1. پروژه `fruit-quality-detector` را در VS Code باز کنید، اگر قبلاً باز نشده است. اگر از یک دستگاه مجازی IoT استفاده می‌کنید، مطمئن شوید که محیط مجازی فعال است.

1. فایل `app.py` را باز کنید و دستورات import مربوط به `azure.cognitiveservices.vision.customvision.prediction` و `msrest.authentication` را حذف کنید.

1. دستور import زیر را به بالای فایل اضافه کنید:

    ```python
    import requests
    ```

1. تمام کدها را بعد از ذخیره شدن تصویر در یک فایل، از `image_file.write(image.read())` تا انتهای فایل حذف کنید.

1. کد زیر را به انتهای فایل اضافه کنید:

    ```python
    prediction_url = '<URL>'
    headers = {
        'Content-Type' : 'application/octet-stream'
    }
    image.seek(0)
    response = requests.post(prediction_url, headers=headers, data=image)
    results = response.json()
    
    for prediction in results['predictions']:
        print(f'{prediction["tagName"]}:\t{prediction["probability"] * 100:.2f}%')
    ```

    `<URL>` را با آدرس URL طبقه‌بند خود جایگزین کنید.

    این کد یک درخواست REST POST به طبقه‌بند ارسال می‌کند و تصویر را به عنوان بدنه درخواست ارسال می‌کند. نتایج به صورت JSON بازمی‌گردند و این نتایج رمزگشایی شده و احتمالات چاپ می‌شوند.

1. کد خود را اجرا کنید، در حالی که دوربین شما به سمت میوه‌ای نشانه رفته است، یا از یک مجموعه تصویر مناسب استفاده کنید، یا اگر از سخت‌افزار مجازی IoT استفاده می‌کنید، میوه‌ای که در وب‌کم شما قابل مشاهده است. خروجی را در کنسول مشاهده خواهید کرد:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 می‌توانید این کد را در پوشه [code-classify/pi](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/pi) یا [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/virtual-iot-device) پیدا کنید.

😀 برنامه طبقه‌بند کیفیت میوه شما موفقیت‌آمیز بود!

**سلب مسئولیت**:  
این سند با استفاده از سرویس ترجمه هوش مصنوعی [Co-op Translator](https://github.com/Azure/co-op-translator) ترجمه شده است. در حالی که ما تلاش می‌کنیم دقت را حفظ کنیم، لطفاً توجه داشته باشید که ترجمه‌های خودکار ممکن است شامل خطاها یا نادرستی‌ها باشند. سند اصلی به زبان اصلی آن باید به عنوان منبع معتبر در نظر گرفته شود. برای اطلاعات حساس، توصیه می‌شود از ترجمه حرفه‌ای انسانی استفاده کنید. ما مسئولیتی در قبال سوء تفاهم‌ها یا تفسیرهای نادرست ناشی از استفاده از این ترجمه نداریم.