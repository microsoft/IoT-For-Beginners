<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3ac42e284a7222c0e83d2d43231a364f",
  "translation_date": "2025-08-25T21:46:55+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/single-board-computer-connect-hub.md",
  "language_code": "fa"
}
-->
# اتصال دستگاه IoT شما به ابر - سخت‌افزار مجازی IoT و Raspberry Pi

در این بخش از درس، دستگاه IoT مجازی یا Raspberry Pi خود را به IoT Hub متصل می‌کنید تا داده‌های تله‌متری ارسال کرده و دستورات دریافت کنید.

## اتصال دستگاه به IoT Hub

گام بعدی اتصال دستگاه شما به IoT Hub است.

### وظیفه - اتصال به IoT Hub

1. پوشه `soil-moisture-sensor` را در VS Code باز کنید. اگر از یک دستگاه IoT مجازی استفاده می‌کنید، مطمئن شوید که محیط مجازی در ترمینال در حال اجرا است.

1. چند بسته اضافی Pip نصب کنید:

    ```sh
    pip3 install azure-iot-device
    ```

    کتابخانه `azure-iot-device` برای ارتباط با IoT Hub شما استفاده می‌شود.

1. واردات زیر را به بالای فایل `app.py`، زیر واردات موجود اضافه کنید:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse
    ```

    این کد SDK را برای ارتباط با IoT Hub شما وارد می‌کند.

1. خط `import paho.mqtt.client as mqtt` را حذف کنید زیرا دیگر به این کتابخانه نیازی نیست. تمام کدهای MQTT شامل نام موضوعات، تمام کدهایی که از `mqtt_client` استفاده می‌کنند و `handle_command` را حذف کنید. حلقه `while True:` را نگه دارید، فقط خط `mqtt_client.publish` را از این حلقه حذف کنید.

1. کد زیر را زیر دستورات واردات اضافه کنید:

    ```python
    connection_string = "<connection string>"
    ```

    `<connection string>` را با رشته اتصال که قبلاً در این درس برای دستگاه بازیابی کرده‌اید جایگزین کنید.

    > 💁 این بهترین روش نیست. رشته‌های اتصال هرگز نباید در کد منبع ذخیره شوند، زیرا ممکن است در کنترل نسخه کد بررسی شده و توسط هر کسی پیدا شوند. ما اینجا برای ساده‌سازی این کار را انجام می‌دهیم. ایده‌آل این است که از چیزی مانند یک متغیر محیطی و ابزاری مانند [`python-dotenv`](https://pypi.org/project/python-dotenv/) استفاده کنید. در درس آینده بیشتر در این مورد یاد خواهید گرفت.

1. زیر این کد، کد زیر را اضافه کنید تا یک شیء client دستگاه ایجاد کنید که بتواند با IoT Hub ارتباط برقرار کند و آن را متصل کنید:

    ```python
    device_client = IoTHubDeviceClient.create_from_connection_string(connection_string)

    print('Connecting')
    device_client.connect()
    print('Connected')
    ```

1. این کد را اجرا کنید. خواهید دید که دستگاه شما متصل می‌شود.

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Connecting
    Connected
    Soil moisture: 379
    ```

## ارسال تله‌متری

اکنون که دستگاه شما متصل است، می‌توانید داده‌های تله‌متری را به جای MQTT broker به IoT Hub ارسال کنید.

### وظیفه - ارسال تله‌متری

1. کد زیر را داخل حلقه `while True`، درست قبل از sleep اضافه کنید:

    ```python
    message = Message(json.dumps({ 'soil_moisture': soil_moisture }))
    device_client.send_message(message)
    ```

    این کد یک `Message` از IoT Hub ایجاد می‌کند که شامل خوانش رطوبت خاک به صورت یک رشته JSON است و سپس آن را به عنوان یک پیام دستگاه به ابر به IoT Hub ارسال می‌کند.

## مدیریت دستورات

دستگاه شما باید دستوری از کد سرور برای کنترل رله دریافت کند. این دستور به عنوان یک درخواست روش مستقیم ارسال می‌شود.

## وظیفه - مدیریت یک درخواست روش مستقیم

1. کد زیر را قبل از حلقه `while True` اضافه کنید:

    ```python
    def handle_method_request(request):
        print("Direct method received - ", request.name)
    
        if request.name == "relay_on":
            relay.on()
        elif request.name == "relay_off":
            relay.off()    
    ```

    این کد یک متد به نام `handle_method_request` تعریف می‌کند که وقتی یک روش مستقیم توسط IoT Hub فراخوانی می‌شود، اجرا می‌شود. هر روش مستقیم یک نام دارد و این کد انتظار دارد که یک روش به نام `relay_on` برای روشن کردن رله و `relay_off` برای خاموش کردن رله وجود داشته باشد.

    > 💁 این کار همچنین می‌تواند در یک درخواست روش مستقیم واحد پیاده‌سازی شود، به طوری که حالت مورد نظر رله در یک payload ارسال شود که می‌تواند با درخواست روش ارسال شده و از شیء `request` در دسترس باشد.

1. روش‌های مستقیم نیاز به یک پاسخ دارند تا به کد فراخوان بگویند که درخواست آن‌ها پردازش شده است. کد زیر را در انتهای تابع `handle_method_request` اضافه کنید تا یک پاسخ به درخواست ایجاد کند:

    ```python
    method_response = MethodResponse.create_from_method_request(request, 200)
    device_client.send_method_response(method_response)
    ```

    این کد یک پاسخ به درخواست روش مستقیم با کد وضعیت HTTP 200 ارسال می‌کند و آن را به IoT Hub بازمی‌گرداند.

1. کد زیر را زیر تعریف این تابع اضافه کنید:

    ```python
    device_client.on_method_request_received = handle_method_request
    ```

    این کد به کلاینت IoT Hub می‌گوید که وقتی یک روش مستقیم فراخوانی می‌شود، تابع `handle_method_request` را اجرا کند.

> 💁 می‌توانید این کد را در پوشه [code/pi](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/pi) یا [code/virtual-device](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/virtual-device) پیدا کنید.

😀 برنامه حسگر رطوبت خاک شما به IoT Hub متصل شد!

**سلب مسئولیت**:  
این سند با استفاده از سرویس ترجمه هوش مصنوعی [Co-op Translator](https://github.com/Azure/co-op-translator) ترجمه شده است. در حالی که ما تلاش می‌کنیم دقت را حفظ کنیم، لطفاً توجه داشته باشید که ترجمه‌های خودکار ممکن است حاوی خطاها یا نادرستی‌هایی باشند. سند اصلی به زبان اصلی آن باید به عنوان منبع معتبر در نظر گرفته شود. برای اطلاعات حساس، ترجمه حرفه‌ای انسانی توصیه می‌شود. ما هیچ مسئولیتی در قبال سوءتفاهم‌ها یا تفسیرهای نادرست ناشی از استفاده از این ترجمه نداریم.