<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7e9f05bdc50a40fd924b1d66934471bf",
  "translation_date": "2025-08-26T22:10:58+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/virtual-device-proximity.md",
  "language_code": "ur"
}
-->
# قربت کا پتہ لگائیں - ورچوئل IoT ہارڈویئر

اس سبق کے اس حصے میں، آپ اپنے ورچوئل IoT ڈیوائس میں ایک قربت سینسر شامل کریں گے اور اس سے فاصلہ پڑھیں گے۔

## ہارڈویئر

ورچوئل IoT ڈیوائس ایک سیمولیٹڈ ڈسٹنس سینسر استعمال کرے گا۔

ایک فزیکل IoT ڈیوائس میں، آپ فاصلے کا پتہ لگانے کے لیے لیزر رینجنگ ماڈیول کے ساتھ ایک سینسر استعمال کریں گے۔

### CounterFit میں ڈسٹنس سینسر شامل کریں

ورچوئل ڈسٹنس سینسر استعمال کرنے کے لیے، آپ کو CounterFit ایپ میں ایک سینسر شامل کرنا ہوگا۔

#### کام - CounterFit میں ڈسٹنس سینسر شامل کریں

CounterFit ایپ میں ڈسٹنس سینسر شامل کریں۔

1. VS Code میں `fruit-quality-detector` کوڈ کھولیں اور یقینی بنائیں کہ ورچوئل ماحول فعال ہے۔

1. ایک اضافی Pip پیکج انسٹال کریں تاکہ ایک CounterFit shim انسٹال کیا جا سکے جو فاصلے کے سینسرز سے بات کر سکے، [rpi-vl53l0x Pip پیکج](https://pypi.org/project/rpi-vl53l0x/) کو سیمولیٹ کرتے ہوئے، جو ایک Python پیکج ہے جو [VL53L0X ٹائم آف فلائٹ ڈسٹنس سینسر](https://wiki.seeedstudio.com/Grove-Time_of_Flight_Distance_Sensor-VL53L0X/) کے ساتھ تعامل کرتا ہے۔ یقینی بنائیں کہ آپ یہ ورچوئل ماحول کے ساتھ فعال ٹرمینل سے انسٹال کر رہے ہیں۔

    ```sh
    pip install counterfit-shims-rpi-vl53l0x
    ```

1. یقینی بنائیں کہ CounterFit ویب ایپ چل رہی ہے۔

1. ایک ڈسٹنس سینسر بنائیں:

    1. *Sensors* پین میں *Create sensor* باکس میں، *Sensor type* ڈراپ ڈاؤن کریں اور *Distance* منتخب کریں۔

    1. *Units* کو `Millimeter` پر چھوڑ دیں۔

    1. یہ سینسر ایک I²C سینسر ہے، اس لیے ایڈریس کو `0x29` پر سیٹ کریں۔ اگر آپ نے ایک فزیکل VL53L0X سینسر استعمال کیا ہوتا تو یہ ایڈریس ہارڈ کوڈڈ ہوتا۔

    1. ڈسٹنس سینسر بنانے کے لیے **Add** بٹن منتخب کریں۔

    ![ڈسٹنس سینسر کی سیٹنگز](../../../../../translated_images/counterfit-create-distance-sensor.967c9fb98f27888d95920c9784d004c972490eb71f70397fe13bd70a79a879a3.ur.png)

    ڈسٹنس سینسر بنایا جائے گا اور سینسرز کی فہرست میں ظاہر ہوگا۔

    ![ڈسٹنس سینسر بنایا گیا](../../../../../translated_images/counterfit-distance-sensor.079eefeeea0b68afc36431ce8fcbe2f09a7e4916ed1cd5cb30e696db53bc18fa.ur.png)

## ڈسٹنس سینسر کو پروگرام کریں

ورچوئل IoT ڈیوائس اب سیمولیٹڈ ڈسٹنس سینسر استعمال کرنے کے لیے پروگرام کیا جا سکتا ہے۔

### کام - ٹائم آف فلائٹ سینسر کو پروگرام کریں

1. `fruit-quality-detector` پروجیکٹ میں ایک نئی فائل بنائیں جس کا نام `distance-sensor.py` ہو۔

    > 💁 متعدد IoT ڈیوائسز کو سیمولیٹ کرنے کا ایک آسان طریقہ یہ ہے کہ ہر ایک کو ایک مختلف Python فائل میں کریں، پھر انہیں ایک ہی وقت میں چلائیں۔

1. CounterFit کے ساتھ کنکشن شروع کرنے کے لیے درج ذیل کوڈ شامل کریں:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. اس کے نیچے درج ذیل کوڈ شامل کریں:

    ```python
    import time
    
    from counterfit_shims_rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    یہ VL53L0X ٹائم آف فلائٹ سینسر کے لیے سینسر لائبریری shim کو امپورٹ کرتا ہے۔

1. اس کے نیچے، سینسر تک رسائی کے لیے درج ذیل کوڈ شامل کریں:

    ```python
    distance_sensor = VL53L0X()
    distance_sensor.begin()
    ```

    یہ کوڈ ایک ڈسٹنس سینسر ڈکلیئر کرتا ہے، پھر سینسر کو شروع کرتا ہے۔

1. آخر میں، فاصلے پڑھنے کے لیے ایک لامتناہی لوپ شامل کریں:

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    یہ کوڈ سینسر سے پڑھنے کے لیے ایک ویلیو کے تیار ہونے کا انتظار کرتا ہے، پھر اسے کنسول میں پرنٹ کرتا ہے۔

1. اس کوڈ کو چلائیں۔

    > 💁 یاد رکھیں کہ اس فائل کا نام `distance-sensor.py` ہے! یقینی بنائیں کہ اسے Python کے ذریعے چلائیں، نہ کہ `app.py`۔

1. آپ کنسول میں فاصلے کی پیمائش دیکھیں گے۔ CounterFit میں ویلیو تبدیل کریں تاکہ یہ ویلیو تبدیل ہو، یا رینڈم ویلیوز استعمال کریں۔

    ```output
    (.venv) ➜  fruit-quality-detector python distance-sensor.py 
    Distance = 37 mm
    Distance = 42 mm
    Distance = 29 mm
    ```

> 💁 آپ یہ کوڈ [code-proximity/virtual-iot-device](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/virtual-iot-device) فولڈر میں تلاش کر سکتے ہیں۔

😀 آپ کا قربت سینسر پروگرام کامیاب رہا!

---

**ڈسکلیمر**:  
یہ دستاویز AI ترجمہ سروس [Co-op Translator](https://github.com/Azure/co-op-translator) کا استعمال کرتے ہوئے ترجمہ کی گئی ہے۔ ہم درستگی کے لیے کوشش کرتے ہیں، لیکن براہ کرم آگاہ رہیں کہ خودکار ترجمے میں غلطیاں یا غیر درستیاں ہو سکتی ہیں۔ اصل دستاویز کو اس کی اصل زبان میں مستند ذریعہ سمجھا جانا چاہیے۔ اہم معلومات کے لیے، پیشہ ور انسانی ترجمہ کی سفارش کی جاتی ہے۔ ہم اس ترجمے کے استعمال سے پیدا ہونے والی کسی بھی غلط فہمی یا غلط تشریح کے ذمہ دار نہیں ہیں۔