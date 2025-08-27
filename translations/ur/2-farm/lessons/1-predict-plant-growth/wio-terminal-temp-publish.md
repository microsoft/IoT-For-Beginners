<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "df28cd649cd892bcce034e064913b2f3",
  "translation_date": "2025-08-26T22:18:50+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp-publish.md",
  "language_code": "ur"
}
-->
# وائیو ٹرمینل - درجہ حرارت شائع کریں

اس سبق کے اس حصے میں، آپ MQTT کے ذریعے وائیو ٹرمینل سے معلوم کیے گئے درجہ حرارت کے اعداد و شمار شائع کریں گے تاکہ بعد میں GDD کا حساب لگانے کے لیے ان کا استعمال کیا جا سکے۔

## درجہ حرارت شائع کریں

جب درجہ حرارت معلوم کر لیا جائے، تو اسے MQTT کے ذریعے کسی 'سرور' کوڈ پر شائع کیا جا سکتا ہے جو ان اعداد و شمار کو پڑھے گا اور انہیں GDD کے حساب کے لیے محفوظ کرے گا۔ مائیکرو کنٹرولرز انٹرنیٹ سے وقت نہیں پڑھتے اور نہ ہی باکس سے باہر ریئل ٹائم کلاک کے ذریعے وقت کو ٹریک کرتے ہیں، اس کے لیے ڈیوائس کو پروگرام کرنا پڑتا ہے، بشرطیکہ اس کے پاس ضروری ہارڈویئر موجود ہو۔

اس سبق کو آسان بنانے کے لیے، سینسر کے ڈیٹا کے ساتھ وقت نہیں بھیجا جائے گا، بلکہ جب سرور کوڈ پیغامات وصول کرے گا تو وہ بعد میں وقت شامل کر سکتا ہے۔

### کام

ڈیوائس کو درجہ حرارت کے ڈیٹا کو شائع کرنے کے لیے پروگرام کریں۔

1. `temperature-sensor` وائیو ٹرمینل پروجیکٹ کھولیں۔

1. وہی اقدامات دہرائیں جو آپ نے سبق 4 میں MQTT سے جڑنے اور ٹیلی میٹری بھیجنے کے لیے کیے تھے۔ آپ وہی عوامی Mosquitto بروکر استعمال کریں گے۔

    ان اقدامات میں شامل ہیں:

    - `.ini` فائل میں Seeed WiFi اور MQTT لائبریریاں شامل کریں
    - WiFi سے جڑنے کے لیے کنفیگریشن فائل اور کوڈ شامل کریں
    - MQTT بروکر سے جڑنے کے لیے کوڈ شامل کریں
    - ٹیلی میٹری شائع کرنے کے لیے کوڈ شامل کریں

    > ⚠️ اگر ضرورت ہو تو [MQTT سے جڑنے کی ہدایات](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md) اور [ٹیلی میٹری بھیجنے کی ہدایات](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md) سبق 4 سے دیکھیں۔

1. یقینی بنائیں کہ `config.h` ہیڈر فائل میں `CLIENT_NAME` اس پروجیکٹ کی عکاسی کرتا ہے:

    ```cpp
    const string CLIENT_NAME = ID + "temperature_sensor_client";
    ```

1. ٹیلی میٹری کے لیے، روشنی کی قدر بھیجنے کے بجائے، DHT سینسر سے پڑھی گئی درجہ حرارت کی قدر کو JSON دستاویز میں `temperature` نامی پراپرٹی کے طور پر بھیجیں۔ اس کے لیے `main.cpp` میں `loop` فنکشن کو تبدیل کریں:

    ```cpp
    float temp_hum_val[2] = {0};
    dht.readTempAndHumidity(temp_hum_val);

    DynamicJsonDocument doc(1024);
    doc["temperature"] = temp_hum_val[1];
    ```

1. درجہ حرارت کی قدر کو بار بار پڑھنے کی ضرورت نہیں ہے - یہ مختصر وقت میں زیادہ تبدیل نہیں ہوگا، اس لیے `loop` فنکشن میں `delay` کو 10 منٹ پر سیٹ کریں:

    ```cpp
    delay(10 * 60 * 1000);
    ```

    > 💁 `delay` فنکشن وقت کو ملی سیکنڈز میں لیتا ہے، اس لیے اسے پڑھنے میں آسانی کے لیے قدر کو ایک حساب کے نتیجے کے طور پر پاس کیا جاتا ہے۔ 1,000ms ایک سیکنڈ میں، 60 سیکنڈ ایک منٹ میں، اس لیے 10 x (60 سیکنڈ ایک منٹ میں) x (1000ms ایک سیکنڈ میں) 10 منٹ کی تاخیر دیتا ہے۔

1. اسے اپنے وائیو ٹرمینل پر اپ لوڈ کریں، اور سیریل مانیٹر کا استعمال کرتے ہوئے دیکھیں کہ درجہ حرارت MQTT بروکر کو بھیجا جا رہا ہے۔

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"temperature":25}
    Sending telemetry {"temperature":25}
    ```

> 💁 آپ اس کوڈ کو [code-publish-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/wio-terminal) فولڈر میں تلاش کر سکتے ہیں۔

😀 آپ نے کامیابی کے ساتھ اپنے ڈیوائس سے درجہ حرارت کو ٹیلی میٹری کے طور پر شائع کر دیا ہے۔

---

**ڈسکلیمر**:  
یہ دستاویز AI ترجمہ سروس [Co-op Translator](https://github.com/Azure/co-op-translator) کا استعمال کرتے ہوئے ترجمہ کی گئی ہے۔ ہم درستگی کے لیے کوشش کرتے ہیں، لیکن براہ کرم آگاہ رہیں کہ خودکار ترجمے میں غلطیاں یا غیر درستیاں ہو سکتی ہیں۔ اصل دستاویز کو اس کی اصل زبان میں مستند ذریعہ سمجھا جانا چاہیے۔ اہم معلومات کے لیے، پیشہ ور انسانی ترجمہ کی سفارش کی جاتی ہے۔ ہم اس ترجمے کے استعمال سے پیدا ہونے والی کسی بھی غلط فہمی یا غلط تشریح کے ذمہ دار نہیں ہیں۔