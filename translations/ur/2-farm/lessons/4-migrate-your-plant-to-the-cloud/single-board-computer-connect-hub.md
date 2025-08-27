<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3ac42e284a7222c0e83d2d43231a364f",
  "translation_date": "2025-08-26T22:59:53+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/single-board-computer-connect-hub.md",
  "language_code": "ur"
}
-->
# اپنے IoT ڈیوائس کو کلاؤڈ سے جوڑیں - ورچوئل IoT ہارڈویئر اور راسپبیری پائی

اس سبق کے اس حصے میں، آپ اپنے ورچوئل IoT ڈیوائس یا راسپبیری پائی کو اپنے IoT ہب سے جوڑیں گے تاکہ ٹیلیمیٹری بھیج سکیں اور کمانڈز وصول کر سکیں۔

## اپنے ڈیوائس کو IoT ہب سے جوڑیں

اگلا مرحلہ یہ ہے کہ اپنے ڈیوائس کو IoT ہب سے جوڑیں۔

### کام - IoT ہب سے جڑیں

1. VS کوڈ میں `soil-moisture-sensor` فولڈر کھولیں۔ اگر آپ ورچوئل IoT ڈیوائس استعمال کر رہے ہیں تو یقینی بنائیں کہ ٹرمینل میں ورچوئل ماحول چل رہا ہو۔

1. کچھ اضافی Pip پیکجز انسٹال کریں:

    ```sh
    pip3 install azure-iot-device
    ```

    `azure-iot-device` ایک لائبریری ہے جو آپ کے IoT ہب سے بات چیت کرنے کے لیے استعمال ہوتی ہے۔

1. درج ذیل امپورٹس کو `app.py` فائل کے اوپر موجودہ امپورٹس کے نیچے شامل کریں:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse
    ```

    یہ کوڈ آپ کے IoT ہب سے بات چیت کرنے کے لیے SDK کو امپورٹ کرتا ہے۔

1. `import paho.mqtt.client as mqtt` لائن کو ہٹا دیں کیونکہ اب اس لائبریری کی ضرورت نہیں ہے۔ تمام MQTT کوڈ کو ہٹا دیں، بشمول ٹاپک کے نام، وہ تمام کوڈ جو `mqtt_client` استعمال کرتا ہے اور `handle_command`۔ `while True:` لوپ کو برقرار رکھیں، بس اس لوپ سے `mqtt_client.publish` لائن کو حذف کر دیں۔

1. امپورٹ اسٹیٹمنٹس کے نیچے درج ذیل کوڈ شامل کریں:

    ```python
    connection_string = "<connection string>"
    ```

    `<connection string>` کو اس کنکشن اسٹرنگ سے تبدیل کریں جو آپ نے اس سبق کے پہلے حصے میں ڈیوائس کے لیے حاصل کی تھی۔

    > 💁 یہ بہترین عمل نہیں ہے۔ کنکشن اسٹرنگز کو کبھی بھی سورس کوڈ میں محفوظ نہیں کرنا چاہیے، کیونکہ یہ سورس کوڈ کنٹرول میں چیک ہو سکتی ہیں اور کسی کے ذریعے بھی دیکھی جا سکتی ہیں۔ ہم یہاں سادگی کے لیے ایسا کر رہے ہیں۔ مثالی طور پر، آپ کو کسی ماحول کے متغیر اور [`python-dotenv`](https://pypi.org/project/python-dotenv/) جیسے ٹول کا استعمال کرنا چاہیے۔ آپ اس کے بارے میں ایک آنے والے سبق میں مزید سیکھیں گے۔

1. اس کوڈ کے نیچے، درج ذیل شامل کریں تاکہ ایک ڈیوائس کلائنٹ آبجیکٹ بنایا جا سکے جو IoT ہب سے بات چیت کر سکے، اور اسے جوڑیں:

    ```python
    device_client = IoTHubDeviceClient.create_from_connection_string(connection_string)

    print('Connecting')
    device_client.connect()
    print('Connected')
    ```

1. اس کوڈ کو چلائیں۔ آپ دیکھیں گے کہ آپ کا ڈیوائس جڑ گیا ہے۔

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Connecting
    Connected
    Soil moisture: 379
    ```

## ٹیلیمیٹری بھیجیں

اب جب کہ آپ کا ڈیوائس جڑ چکا ہے، آپ MQTT بروکر کے بجائے IoT ہب کو ٹیلیمیٹری بھیج سکتے ہیں۔

### کام - ٹیلیمیٹری بھیجیں

1. `while True` لوپ کے اندر درج ذیل کوڈ شامل کریں، نیند سے بالکل پہلے:

    ```python
    message = Message(json.dumps({ 'soil_moisture': soil_moisture }))
    device_client.send_message(message)
    ```

    یہ کوڈ ایک IoT ہب `Message` بناتا ہے جس میں مٹی کی نمی کی ریڈنگ ایک JSON اسٹرنگ کے طور پر شامل ہوتی ہے، پھر اسے IoT ہب کو ایک ڈیوائس سے کلاؤڈ میسج کے طور پر بھیجتا ہے۔

## کمانڈز کو ہینڈل کریں

آپ کے ڈیوائس کو سرور کوڈ سے ایک کمانڈ ہینڈل کرنے کی ضرورت ہے تاکہ ریلے کو کنٹرول کیا جا سکے۔ یہ ایک ڈائریکٹ میتھڈ ریکویسٹ کے طور پر بھیجا جاتا ہے۔

## کام - ایک ڈائریکٹ میتھڈ ریکویسٹ کو ہینڈل کریں

1. `while True` لوپ سے پہلے درج ذیل کوڈ شامل کریں:

    ```python
    def handle_method_request(request):
        print("Direct method received - ", request.name)
    
        if request.name == "relay_on":
            relay.on()
        elif request.name == "relay_off":
            relay.off()    
    ```

    یہ ایک میتھڈ، `handle_method_request`، کو ڈیفائن کرتا ہے جو اس وقت کال کیا جائے گا جب IoT ہب کی طرف سے ایک ڈائریکٹ میتھڈ کال کیا جائے گا۔ ہر ڈائریکٹ میتھڈ کا ایک نام ہوتا ہے، اور یہ کوڈ ایک میتھڈ کی توقع کرتا ہے جسے `relay_on` کہا جاتا ہے تاکہ ریلے کو آن کرے، اور `relay_off` تاکہ ریلے کو آف کرے۔

    > 💁 یہ ایک ہی ڈائریکٹ میتھڈ ریکویسٹ میں بھی نافذ کیا جا سکتا ہے، جس میں ریلے کی مطلوبہ حالت کو ایک پے لوڈ میں پاس کیا جا سکتا ہے جو میتھڈ ریکویسٹ کے ساتھ پاس کیا جا سکتا ہے اور `request` آبجیکٹ سے دستیاب ہو سکتا ہے۔

1. ڈائریکٹ میتھڈز کو ایک ریسپانس کی ضرورت ہوتی ہے تاکہ کال کرنے والے کوڈ کو بتایا جا سکے کہ انہیں ہینڈل کر لیا گیا ہے۔ `handle_method_request` فنکشن کے آخر میں درج ذیل کوڈ شامل کریں تاکہ ریکویسٹ کا ریسپانس بنایا جا سکے:

    ```python
    method_response = MethodResponse.create_from_method_request(request, 200)
    device_client.send_method_response(method_response)
    ```

    یہ کوڈ ڈائریکٹ میتھڈ ریکویسٹ کا ریسپانس بھیجتا ہے جس میں HTTP اسٹیٹس کوڈ 200 ہوتا ہے، اور اسے IoT ہب کو واپس بھیجتا ہے۔

1. اس فنکشن کی تعریف کے نیچے درج ذیل کوڈ شامل کریں:

    ```python
    device_client.on_method_request_received = handle_method_request
    ```

    یہ کوڈ IoT ہب کلائنٹ کو بتاتا ہے کہ جب ایک ڈائریکٹ میتھڈ کال کیا جائے تو `handle_method_request` فنکشن کو کال کریں۔

> 💁 آپ اس کوڈ کو [code/pi](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/pi) یا [code/virtual-device](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/virtual-device) فولڈر میں تلاش کر سکتے ہیں۔

😀 آپ کا مٹی کی نمی کا سینسر پروگرام آپ کے IoT ہب سے جڑ چکا ہے!

---

**ڈسکلیمر**:  
یہ دستاویز AI ترجمہ سروس [Co-op Translator](https://github.com/Azure/co-op-translator) کا استعمال کرتے ہوئے ترجمہ کی گئی ہے۔ ہم درستگی کے لیے کوشش کرتے ہیں، لیکن براہ کرم آگاہ رہیں کہ خودکار ترجمے میں غلطیاں یا غیر درستیاں ہو سکتی ہیں۔ اصل دستاویز کو اس کی اصل زبان میں مستند ذریعہ سمجھا جانا چاہیے۔ اہم معلومات کے لیے، پیشہ ور انسانی ترجمہ کی سفارش کی جاتی ہے۔ ہم اس ترجمے کے استعمال سے پیدا ہونے والی کسی بھی غلط فہمی یا غلط تشریح کے ذمہ دار نہیں ہیں۔