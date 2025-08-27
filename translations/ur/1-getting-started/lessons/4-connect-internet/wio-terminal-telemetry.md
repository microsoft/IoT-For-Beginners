<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4bcc29fe2b65e56eada83d2476279227",
  "translation_date": "2025-08-26T23:17:45+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md",
  "language_code": "ur"
}
-->
# اپنی نائٹ لائٹ کو انٹرنیٹ کے ذریعے کنٹرول کریں - Wio Terminal

اس سبق کے اس حصے میں، آپ اپنے Wio Terminal سے روشنی کی سطح کے ساتھ ٹیلیمیٹری MQTT بروکر کو بھیجیں گے۔

## JSON Arduino لائبریریاں انسٹال کریں

MQTT کے ذریعے پیغامات بھیجنے کا ایک مقبول طریقہ JSON کا استعمال ہے۔ JSON کے لیے ایک Arduino لائبریری موجود ہے جو JSON دستاویزات کو پڑھنے اور لکھنے کو آسان بناتی ہے۔

### کام

Arduino JSON لائبریری انسٹال کریں۔

1. VS Code میں نائٹ لائٹ پروجیکٹ کھولیں۔

1. `platformio.ini` فائل میں `lib_deps` فہرست میں درج ذیل کو ایک اضافی لائن کے طور پر شامل کریں:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    یہ [ArduinoJson](https://arduinojson.org)، ایک Arduino JSON لائبریری کو درآمد کرتا ہے۔

## ٹیلیمیٹری شائع کریں

اگلا مرحلہ ٹیلیمیٹری کے ساتھ ایک JSON دستاویز بنانا اور اسے MQTT بروکر کو بھیجنا ہے۔

### کام - ٹیلیمیٹری شائع کریں

MQTT بروکر کو ٹیلیمیٹری شائع کریں۔

1. `config.h` فائل کے آخر میں درج ذیل کوڈ شامل کریں تاکہ MQTT بروکر کے لیے ٹیلیمیٹری ٹاپک کا نام متعین کیا جا سکے:

    ```cpp
    const string CLIENT_TELEMETRY_TOPIC = ID + "/telemetry";
    ```

    `CLIENT_TELEMETRY_TOPIC` وہ ٹاپک ہے جس پر ڈیوائس روشنی کی سطح کو شائع کرے گا۔

1. `main.cpp` فائل کھولیں۔

1. فائل کے اوپر درج ذیل `#include` ہدایت شامل کریں:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. `loop` فنکشن کے اندر، `delay` سے بالکل پہلے درج ذیل کوڈ شامل کریں:

    ```cpp
    int light = analogRead(WIO_LIGHT);

    DynamicJsonDocument doc(1024);
    doc["light"] = light;

    string telemetry;
    serializeJson(doc, telemetry);

    Serial.print("Sending telemetry ");
    Serial.println(telemetry.c_str());

    client.publish(CLIENT_TELEMETRY_TOPIC.c_str(), telemetry.c_str());
    ```

    یہ کوڈ روشنی کی سطح کو پڑھتا ہے اور ArduinoJson کا استعمال کرتے ہوئے اس سطح کے ساتھ ایک JSON دستاویز بناتا ہے۔ پھر اسے ایک سٹرنگ میں سیریلائز کیا جاتا ہے اور MQTT کلائنٹ کے ذریعے ٹیلیمیٹری MQTT ٹاپک پر شائع کیا جاتا ہے۔

1. کوڈ کو اپنے Wio Terminal پر اپ لوڈ کریں، اور سیریل مانیٹر کا استعمال کرتے ہوئے دیکھیں کہ روشنی کی سطح MQTT بروکر کو بھیجی جا رہی ہے۔

    ```output
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"light":652}
    Sending telemetry {"light":612}
    Sending telemetry {"light":583}
    ```

> 💁 آپ اس کوڈ کو [code-telemetry/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/wio-terminal) فولڈر میں تلاش کر سکتے ہیں۔

😀 آپ نے کامیابی سے اپنے ڈیوائس سے ٹیلیمیٹری بھیج دی ہے۔

---

**ڈسکلیمر**:  
یہ دستاویز AI ترجمہ سروس [Co-op Translator](https://github.com/Azure/co-op-translator) کا استعمال کرتے ہوئے ترجمہ کی گئی ہے۔ ہم درستگی کے لیے کوشش کرتے ہیں، لیکن براہ کرم آگاہ رہیں کہ خودکار ترجمے میں غلطیاں یا غیر درستیاں ہو سکتی ہیں۔ اصل دستاویز کو اس کی اصل زبان میں مستند ذریعہ سمجھا جانا چاہیے۔ اہم معلومات کے لیے، پیشہ ور انسانی ترجمہ کی سفارش کی جاتی ہے۔ ہم اس ترجمے کے استعمال سے پیدا ہونے والی کسی بھی غلط فہمی یا غلط تشریح کے ذمہ دار نہیں ہیں۔