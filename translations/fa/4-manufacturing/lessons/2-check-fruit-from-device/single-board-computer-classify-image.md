# طبقه‌بندی یک تصویر - سخت‌افزار مجازی IoT و رزبری پای

در این بخش از درس، تصویر گرفته‌شده توسط دوربین را به سرویس Custom Vision ارسال می‌کنید تا طبقه‌بندی شود.

## ارسال تصاویر به Custom Vision

سرویس Custom Vision یک SDK پایتون دارد که می‌توانید از آن برای طبقه‌بندی تصاویر استفاده کنید.

### وظیفه - ارسال تصاویر به Custom Vision

1. پوشه `fruit-quality-detector` را در VS Code باز کنید. اگر از یک دستگاه مجازی IoT استفاده می‌کنید، مطمئن شوید که محیط مجازی در ترمینال در حال اجرا است.

1. SDK پایتون برای ارسال تصاویر به Custom Vision به‌صورت یک بسته Pip در دسترس است. آن را با دستور زیر نصب کنید:

    ```sh
    pip3 install azure-cognitiveservices-vision-customvision
    ```

1. دستورات import زیر را به بالای فایل `app.py` اضافه کنید:

    ```python
    from msrest.authentication import ApiKeyCredentials
    from azure.cognitiveservices.vision.customvision.prediction import CustomVisionPredictionClient
    ```

    این دستورات برخی از ماژول‌های کتابخانه‌های Custom Vision را وارد می‌کنند، یکی برای احراز هویت با کلید پیش‌بینی و دیگری برای ارائه یک کلاس کلاینت پیش‌بینی که می‌تواند Custom Vision را فراخوانی کند.

1. کد زیر را به انتهای فایل اضافه کنید:

    ```python
    prediction_url = '<prediction_url>'
    prediction_key = '<prediction key>'
    ```

    `<prediction_url>` را با URL‌ای که قبلاً از دیالوگ *Prediction URL* کپی کرده‌اید جایگزین کنید. `<prediction key>` را نیز با کلید پیش‌بینی که از همان دیالوگ کپی کرده‌اید جایگزین کنید.

1. URL پیش‌بینی که توسط دیالوگ *Prediction URL* ارائه شده است، برای استفاده مستقیم در فراخوانی نقطه پایانی REST طراحی شده است. SDK پایتون از بخش‌های مختلف این URL در مکان‌های مختلف استفاده می‌کند. کد زیر را اضافه کنید تا این URL به بخش‌های موردنیاز تقسیم شود:

    ```python
    parts = prediction_url.split('/')
    endpoint = 'https://' + parts[2]
    project_id = parts[6]
    iteration_name = parts[9]
    ```

    این کد URL را تقسیم می‌کند و نقطه پایانی `https://<location>.api.cognitive.microsoft.com`، شناسه پروژه و نام نسخه منتشرشده را استخراج می‌کند.

1. یک شیء پیش‌بینی‌کننده برای انجام پیش‌بینی با کد زیر ایجاد کنید:

    ```python
    prediction_credentials = ApiKeyCredentials(in_headers={"Prediction-key": prediction_key})
    predictor = CustomVisionPredictionClient(endpoint, prediction_credentials)
    ```

    `prediction_credentials` کلید پیش‌بینی را در بر می‌گیرد. سپس از این کلید برای ایجاد یک شیء کلاینت پیش‌بینی که به نقطه پایانی اشاره می‌کند استفاده می‌شود.

1. تصویر را با استفاده از کد زیر به Custom Vision ارسال کنید:

    ```python
    image.seek(0)
    results = predictor.classify_image(project_id, iteration_name, image)
    ```

    این کد تصویر را به ابتدای آن بازمی‌گرداند و سپس آن را به کلاینت پیش‌بینی ارسال می‌کند.

1. در نهایت، نتایج را با کد زیر نمایش دهید:

    ```python
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    این کد از میان تمام پیش‌بینی‌های بازگشتی حلقه می‌زند و آن‌ها را در ترمینال نمایش می‌دهد. احتمال‌های بازگشتی اعداد اعشاری بین 0 تا 1 هستند، که 0 نشان‌دهنده 0% احتمال تطابق با برچسب و 1 نشان‌دهنده 100% احتمال است.

    > 💁 طبقه‌بندی‌کننده‌های تصویر درصدهای مربوط به تمام برچسب‌هایی که استفاده شده‌اند را بازمی‌گردانند. هر برچسب یک احتمال دارد که نشان می‌دهد تصویر با آن برچسب تطابق دارد.

1. کد خود را اجرا کنید، در حالی که دوربین شما به سمت میوه‌ای، یا مجموعه‌ای مناسب از تصاویر، یا میوه‌ای که در وب‌کم شما قابل مشاهده است (اگر از سخت‌افزار مجازی IoT استفاده می‌کنید) اشاره می‌کند. خروجی را در کنسول مشاهده خواهید کرد:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

    شما می‌توانید تصویری که گرفته شده است را ببینید و این مقادیر را در تب **Predictions** در Custom Vision مشاهده کنید.

    ![یک موز در Custom Vision که با احتمال 56.8% رسیده و با احتمال 43.1% نارس پیش‌بینی شده است](../../../../../translated_images/fa/custom-vision-banana-prediction.30cdff4e1d72db5d.webp)

> 💁 می‌توانید این کد را در پوشه [code-classify/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/pi) یا [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/virtual-iot-device) پیدا کنید.

😀 برنامه طبقه‌بندی کیفیت میوه شما موفقیت‌آمیز بود!

**سلب مسئولیت**:  
این سند با استفاده از سرویس ترجمه هوش مصنوعی [Co-op Translator](https://github.com/Azure/co-op-translator) ترجمه شده است. در حالی که ما تلاش می‌کنیم دقت را حفظ کنیم، لطفاً توجه داشته باشید که ترجمه‌های خودکار ممکن است شامل خطاها یا نادرستی‌ها باشند. سند اصلی به زبان اصلی آن باید به عنوان منبع معتبر در نظر گرفته شود. برای اطلاعات حساس، توصیه می‌شود از ترجمه حرفه‌ای انسانی استفاده کنید. ما مسئولیتی در قبال سوء تفاهم‌ها یا تفسیرهای نادرست ناشی از استفاده از این ترجمه نداریم.