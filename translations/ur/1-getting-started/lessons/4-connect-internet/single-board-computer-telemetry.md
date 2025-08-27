<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1226517aae5f5b6f904434670394c688",
  "translation_date": "2025-08-26T23:10:21+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md",
  "language_code": "ur"
}
-->
# انٹرنیٹ کے ذریعے اپنی نائٹ لائٹ کو کنٹرول کریں - ورچوئل IoT ہارڈویئر اور راسپبیری پائی

اس سبق کے اس حصے میں، آپ اپنے راسپبیری پائی یا ورچوئل IoT ڈیوائس سے روشنی کی سطح کے ساتھ ٹیلیمیٹری کو ایک MQTT بروکر پر بھیجیں گے۔

## ٹیلیمیٹری شائع کریں

اگلا مرحلہ یہ ہے کہ ٹیلیمیٹری کے ساتھ ایک JSON دستاویز بنائیں اور اسے MQTT بروکر پر بھیجیں۔

### کام

ٹیلیمیٹری کو MQTT بروکر پر شائع کریں۔

1. نائٹ لائٹ پروجیکٹ کو VS Code میں کھولیں۔

1. اگر آپ ورچوئل IoT ڈیوائس استعمال کر رہے ہیں، تو یقینی بنائیں کہ ٹرمینل ورچوئل ماحول چلا رہا ہے۔ اگر آپ راسپبیری پائی استعمال کر رہے ہیں تو آپ ورچوئل ماحول استعمال نہیں کریں گے۔

1. `app.py` فائل کے شروع میں درج ذیل درآمد شامل کریں:

    ```python
    import json
    ```

    `json` لائبریری ٹیلیمیٹری کو JSON دستاویز کے طور پر انکوڈ کرنے کے لیے استعمال ہوتی ہے۔

1. `client_name` کے اعلان کے بعد درج ذیل شامل کریں:

    ```python
    client_telemetry_topic = id + '/telemetry'
    ```

    `client_telemetry_topic` وہ MQTT موضوع ہے جس پر ڈیوائس روشنی کی سطح کو شائع کرے گا۔

1. فائل کے آخر میں `while True:` لوپ کے مواد کو درج ذیل سے تبدیل کریں:

    ```python
    while True:
        light = light_sensor.light
        telemetry = json.dumps({'light' : light})

        print("Sending telemetry ", telemetry)
    
        mqtt_client.publish(client_telemetry_topic, telemetry)
    
        time.sleep(5)
    ```

    یہ کوڈ روشنی کی سطح کو JSON دستاویز میں پیک کرتا ہے اور اسے MQTT بروکر پر شائع کرتا ہے۔ پھر یہ پیغامات بھیجنے کی تعدد کو کم کرنے کے لیے وقفہ لیتا ہے۔

1. کوڈ کو اسی طرح چلائیں جیسے آپ نے اسائنمنٹ کے پچھلے حصے سے کوڈ چلایا تھا۔ اگر آپ ورچوئل IoT ڈیوائس استعمال کر رہے ہیں، تو یقینی بنائیں کہ CounterFit ایپ چل رہی ہے اور روشنی کے سینسر اور LED کو درست پنز پر بنایا گیا ہے۔

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Sending telemetry  {"light": 0}
    Sending telemetry  {"light": 0}
    ```

> 💁 آپ اس کوڈ کو [code-telemetry/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/virtual-device) فولڈر یا [code-telemetry/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/pi) فولڈر میں تلاش کر سکتے ہیں۔

😀 آپ نے کامیابی سے اپنے ڈیوائس سے ٹیلیمیٹری بھیج دی ہے۔

---

**ڈسکلیمر**:  
یہ دستاویز AI ترجمہ سروس [Co-op Translator](https://github.com/Azure/co-op-translator) کا استعمال کرتے ہوئے ترجمہ کی گئی ہے۔ ہم درستگی کے لیے کوشش کرتے ہیں، لیکن براہ کرم آگاہ رہیں کہ خودکار ترجمے میں غلطیاں یا غیر درستیاں ہو سکتی ہیں۔ اصل دستاویز کو اس کی اصل زبان میں مستند ذریعہ سمجھا جانا چاہیے۔ اہم معلومات کے لیے، پیشہ ور انسانی ترجمہ کی سفارش کی جاتی ہے۔ ہم اس ترجمے کے استعمال سے پیدا ہونے والی کسی بھی غلط فہمی یا غلط تشریح کے ذمہ دار نہیں ہیں۔