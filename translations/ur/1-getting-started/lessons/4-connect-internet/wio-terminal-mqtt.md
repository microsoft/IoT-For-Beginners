<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d6faf0e8d3c2d6d20c0aef2a305dab18",
  "translation_date": "2025-08-26T23:20:01+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md",
  "language_code": "ur"
}
-->
# اپنی نائٹ لائٹ کو انٹرنیٹ کے ذریعے کنٹرول کریں - Wio Terminal

IoT ڈیوائس کو *test.mosquitto.org* کے ساتھ MQTT کے ذریعے بات چیت کرنے کے لیے کوڈ کیا جانا چاہیے تاکہ روشنی کے سینسر کی ریڈنگ کے ساتھ ٹیلیمیٹری ویلیوز بھیج سکے اور LED کو کنٹرول کرنے کے لیے کمانڈز وصول کر سکے۔

اس سبق کے اس حصے میں، آپ اپنے Wio Terminal کو MQTT بروکر سے جوڑیں گے۔

## WiFi اور MQTT Arduino لائبریریاں انسٹال کریں

MQTT بروکر کے ساتھ بات چیت کرنے کے لیے، آپ کو کچھ Arduino لائبریریاں انسٹال کرنے کی ضرورت ہوگی تاکہ Wio Terminal میں موجود WiFi چپ کا استعمال کیا جا سکے اور MQTT کے ساتھ بات چیت کی جا سکے۔ Arduino ڈیوائسز کے لیے ترقی کرتے وقت، آپ وسیع پیمانے پر لائبریریاں استعمال کر سکتے ہیں جو اوپن سورس کوڈ پر مشتمل ہوتی ہیں اور بے شمار صلاحیتوں کو نافذ کرتی ہیں۔ Seeed نے Wio Terminal کے لیے لائبریریاں شائع کی ہیں جو اسے WiFi کے ذریعے بات چیت کرنے کی اجازت دیتی ہیں۔ دیگر ڈویلپرز نے MQTT بروکرز کے ساتھ بات چیت کرنے کے لیے لائبریریاں شائع کی ہیں، اور آپ ان کا استعمال اپنے ڈیوائس کے ساتھ کریں گے۔

یہ لائبریریاں سورس کوڈ کے طور پر فراہم کی جاتی ہیں جنہیں PlatformIO میں خودکار طور پر درآمد کیا جا سکتا ہے اور آپ کے ڈیوائس کے لیے کمپائل کیا جا سکتا ہے۔ اس طرح Arduino لائبریریاں کسی بھی ڈیوائس پر کام کریں گی جو Arduino فریم ورک کو سپورٹ کرتی ہے، بشرطیکہ ڈیوائس میں اس لائبریری کے لیے ضروری مخصوص ہارڈویئر موجود ہو۔ کچھ لائبریریاں، جیسے Seeed WiFi لائبریریاں، مخصوص ہارڈویئر کے لیے مخصوص ہوتی ہیں۔

لائبریریاں عالمی سطح پر انسٹال کی جا سکتی ہیں اور ضرورت پڑنے پر کمپائل کی جا سکتی ہیں، یا کسی مخصوص پروجیکٹ میں۔ اس اسائنمنٹ کے لیے، لائبریریاں پروجیکٹ میں انسٹال کی جائیں گی۔

✅ آپ لائبریری مینجمنٹ کے بارے میں مزید جان سکتے ہیں اور لائبریریوں کو تلاش کرنے اور انسٹال کرنے کا طریقہ [PlatformIO لائبریری دستاویزات](https://docs.platformio.org/en/latest/librarymanager/index.html) میں دیکھ سکتے ہیں۔

### کام - WiFi اور MQTT Arduino لائبریریاں انسٹال کریں

Arduino لائبریریاں انسٹال کریں۔

1. VS Code میں نائٹ لائٹ پروجیکٹ کھولیں۔

1. `platformio.ini` فائل کے آخر میں درج ذیل شامل کریں:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
        seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
        seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    ```

    یہ Seeed WiFi لائبریریاں درآمد کرتا ہے۔ `@ <number>` نحو لائبریری کے مخصوص ورژن نمبر کی طرف اشارہ کرتا ہے۔

    > 💁 آپ `@ <number>` کو ہٹا سکتے ہیں تاکہ ہمیشہ لائبریریوں کے تازہ ترین ورژن استعمال کیے جا سکیں، لیکن اس بات کی کوئی ضمانت نہیں ہے کہ بعد کے ورژن نیچے دیے گئے کوڈ کے ساتھ کام کریں گے۔ یہاں موجود کوڈ کو ان لائبریریوں کے اس ورژن کے ساتھ آزمایا گیا ہے۔

    لائبریریوں کو شامل کرنے کے لیے آپ کو بس یہی کرنا ہے۔ اگلی بار جب PlatformIO پروجیکٹ کو بنائے گا، یہ ان لائبریریوں کے سورس کوڈ کو ڈاؤن لوڈ کرے گا اور اسے آپ کے پروجیکٹ میں کمپائل کرے گا۔

1. `lib_deps` میں درج ذیل شامل کریں:

    ```ini
    knolleary/PubSubClient @ 2.8
    ```

    یہ [PubSubClient](https://github.com/knolleary/pubsubclient)، ایک Arduino MQTT کلائنٹ درآمد کرتا ہے۔

## WiFi سے جڑیں

اب Wio Terminal کو WiFi سے جوڑا جا سکتا ہے۔

### کام - WiFi سے جڑیں

Wio Terminal کو WiFi سے جوڑیں۔

1. `src` فولڈر میں ایک نئی فائل بنائیں جس کا نام `config.h` ہو۔ آپ یہ `src` فولڈر یا اس کے اندر موجود `main.cpp` فائل کو منتخب کر کے اور ایکسپلورر سے **New file** بٹن منتخب کر کے کر سکتے ہیں۔ یہ بٹن صرف اس وقت ظاہر ہوتا ہے جب آپ کا کرسر ایکسپلورر پر ہو۔

    ![نئی فائل کا بٹن](../../../../../translated_images/ur/vscode-new-file-button.182702340fe6723c.png)

1. اس فائل میں درج ذیل کوڈ شامل کریں تاکہ آپ کے WiFi کی اسناد کے لیے مستقلات کی وضاحت کی جا سکے:

    ```cpp
    #pragma once

    #include <string>
    
    using namespace std;
    
    // WiFi credentials
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    ```

    `<SSID>` کو اپنے WiFi کے SSID سے تبدیل کریں۔ `<PASSWORD>` کو اپنے WiFi پاس ورڈ سے تبدیل کریں۔

1. `main.cpp` فائل کھولیں۔

1. فائل کے اوپر درج ذیل `#include` ہدایات شامل کریں:

    ```cpp
    #include <PubSubClient.h>
    #include <rpcWiFi.h>
    #include <SPI.h>
    
    #include "config.h"
    ```

    یہ ان لائبریریوں کے ہیڈر فائلز شامل کرتا ہے جو آپ نے پہلے شامل کی تھیں، ساتھ ہی config ہیڈر فائل بھی۔ یہ ہیڈر فائلز PlatformIO کو لائبریریوں سے کوڈ لانے کے لیے بتانے کے لیے ضروری ہیں۔ ان ہیڈر فائلز کو واضح طور پر شامل کیے بغیر، کچھ کوڈ کمپائل نہیں کیا جائے گا اور آپ کو کمپائلر کی غلطیاں ملیں گی۔

1. `setup` فنکشن کے اوپر درج ذیل کوڈ شامل کریں:

    ```cpp
    void connectWiFi()
    {
        while (WiFi.status() != WL_CONNECTED)
        {
            Serial.println("Connecting to WiFi..");
            WiFi.begin(SSID, PASSWORD);
            delay(500);
        }
    
        Serial.println("Connected!");
    }
    ```

    یہ کوڈ اس وقت تک لوپ کرتا ہے جب تک کہ ڈیوائس WiFi سے منسلک نہ ہو، اور config ہیڈر فائل سے SSID اور پاس ورڈ کا استعمال کرتے ہوئے کنکشن کی کوشش کرتا ہے۔

1. پنز کو کنفیگر کرنے کے بعد، `setup` فنکشن کے نیچے اس فنکشن کو کال کریں۔

    ```cpp
    connectWiFi();
    ```

1. اس کوڈ کو اپنے ڈیوائس پر اپ لوڈ کریں تاکہ WiFi کنکشن کام کر رہا ہو۔ آپ کو یہ سیریل مانیٹر میں نظر آنا چاہیے۔

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    ```

## MQTT سے جڑیں

ایک بار جب Wio Terminal WiFi سے جڑ جائے، تو یہ MQTT بروکر سے جڑ سکتا ہے۔

### کام - MQTT سے جڑیں

MQTT بروکر سے جڑیں۔

1. MQTT بروکر کے کنکشن کی تفصیلات کی وضاحت کے لیے `config.h` فائل کے آخر میں درج ذیل کوڈ شامل کریں:

    ```cpp
    // MQTT settings
    const string ID = "<ID>";
    
    const string BROKER = "test.mosquitto.org";
    const string CLIENT_NAME = ID + "nightlight_client";
    ```

    `<ID>` کو ایک منفرد ID سے تبدیل کریں جو اس ڈیوائس کلائنٹ کے نام کے طور پر استعمال ہوگا، اور بعد میں ان موضوعات کے لیے جو یہ ڈیوائس شائع اور سبسکرائب کرے گا۔ *test.mosquitto.org* بروکر عوامی ہے اور بہت سے لوگ استعمال کرتے ہیں، بشمول دیگر طلباء جو اس اسائنمنٹ پر کام کر رہے ہیں۔ ایک منفرد MQTT کلائنٹ نام اور موضوع کے نام رکھنے سے آپ کے کوڈ کے کسی اور کے کوڈ کے ساتھ ٹکرانے کا امکان ختم ہو جاتا ہے۔ آپ کو یہ ID اسائنمنٹ کے بعد کے حصے میں سرور کوڈ بناتے وقت بھی درکار ہوگی۔

    > 💁 آپ [GUIDGen](https://www.guidgen.com) جیسی ویب سائٹ استعمال کر سکتے ہیں تاکہ ایک منفرد ID تیار کی جا سکے۔

    `BROKER` MQTT بروکر کا URL ہے۔

    `CLIENT_NAME` اس MQTT کلائنٹ کے لیے بروکر پر ایک منفرد نام ہے۔

1. `main.cpp` فائل کھولیں، اور `connectWiFi` فنکشن کے نیچے اور `setup` فنکشن کے اوپر درج ذیل کوڈ شامل کریں:

    ```cpp
    WiFiClient wioClient;
    PubSubClient client(wioClient);
    ```

    یہ کوڈ Wio Terminal WiFi لائبریریوں کا استعمال کرتے ہوئے ایک WiFi کلائنٹ بناتا ہے اور اسے MQTT کلائنٹ بنانے کے لیے استعمال کرتا ہے۔

1. اس کوڈ کے نیچے درج ذیل شامل کریں:

    ```cpp
    void reconnectMQTTClient()
    {
        while (!client.connected())
        {
            Serial.print("Attempting MQTT connection...");
    
            if (client.connect(CLIENT_NAME.c_str()))
            {
                Serial.println("connected");
            }
            else
            {
                Serial.print("Retying in 5 seconds - failed, rc=");
                Serial.println(client.state());
                
                delay(5000);
            }
        }
    }
    ```

    یہ فنکشن MQTT بروکر کے ساتھ کنکشن کی جانچ کرتا ہے اور اگر کنکشن نہ ہو تو دوبارہ کنیکٹ کرتا ہے۔ یہ اس وقت تک لوپ کرتا ہے جب تک کہ کنکشن نہ ہو اور منفرد کلائنٹ نام کا استعمال کرتے ہوئے کنکشن کی کوشش کرتا ہے جو config ہیڈر فائل میں بیان کیا گیا ہے۔

    اگر کنکشن ناکام ہو جائے، تو یہ 5 سیکنڈ کے بعد دوبارہ کوشش کرتا ہے۔

1. `reconnectMQTTClient` فنکشن کے نیچے درج ذیل کوڈ شامل کریں:

    ```cpp
    void createMQTTClient()
    {
        client.setServer(BROKER.c_str(), 1883);
        reconnectMQTTClient();
    }
    ```

    یہ کوڈ کلائنٹ کے لیے MQTT بروکر سیٹ کرتا ہے، ساتھ ہی ایک کال بیک سیٹ کرتا ہے جب کوئی پیغام موصول ہوتا ہے۔ پھر یہ بروکر سے جڑنے کی کوشش کرتا ہے۔

1. WiFi کے کنیکٹ ہونے کے بعد `setup` فنکشن میں `createMQTTClient` فنکشن کو کال کریں۔

1. `loop` فنکشن کو مکمل طور پر درج ذیل سے تبدیل کریں:

    ```cpp
    void loop()
    {
        reconnectMQTTClient();
        client.loop();
    
        delay(2000);
    }
    ```

    یہ کوڈ MQTT بروکر سے دوبارہ کنیکٹ کرنے سے شروع ہوتا ہے۔ یہ کنیکشن آسانی سے ٹوٹ سکتے ہیں، اس لیے باقاعدگی سے چیک کرنا اور ضرورت پڑنے پر دوبارہ کنیکٹ کرنا فائدہ مند ہے۔ پھر یہ MQTT کلائنٹ کے `loop` میتھڈ کو کال کرتا ہے تاکہ کسی بھی پیغامات کو پروسیس کیا جا سکے جو سبسکرائب کیے گئے موضوع پر آ رہے ہیں۔ یہ ایپ سنگل تھریڈڈ ہے، اس لیے پیغامات کو بیک گراؤنڈ تھریڈ پر موصول نہیں کیا جا سکتا، اس لیے نیٹ ورک کنیکشن پر انتظار کرنے والے کسی بھی پیغامات کو پروسیس کرنے کے لیے مین تھریڈ پر وقت مختص کرنا ضروری ہے۔

    آخر میں، 2 سیکنڈ کی تاخیر یقینی بناتی ہے کہ روشنی کی سطحیں بہت زیادہ بار نہ بھیجی جائیں اور ڈیوائس کی پاور کنزمپشن کم ہو۔

1. کوڈ کو اپنے Wio Terminal پر اپ لوڈ کریں، اور سیریل مانیٹر کا استعمال کرتے ہوئے ڈیوائس کو WiFi اور MQTT سے جڑتے ہوئے دیکھیں۔

    ```output
    > Executing task: platformio device monitor <
    
    source /Users/jimbennett/GitHub/IoT-For-Beginners/1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal/nightlight/.venv/bin/activate
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    ```

> 💁 آپ اس کوڈ کو [code-mqtt/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal) فولڈر میں تلاش کر سکتے ہیں۔

😀 آپ نے کامیابی سے اپنے ڈیوائس کو MQTT بروکر سے جوڑ لیا ہے۔

---

**ڈسکلیمر**:  
یہ دستاویز AI ترجمہ سروس [Co-op Translator](https://github.com/Azure/co-op-translator) کا استعمال کرتے ہوئے ترجمہ کی گئی ہے۔ ہم درستگی کے لیے کوشش کرتے ہیں، لیکن براہ کرم آگاہ رہیں کہ خودکار ترجمے میں غلطیاں یا غیر درستیاں ہو سکتی ہیں۔ اصل دستاویز کو اس کی اصل زبان میں مستند ذریعہ سمجھا جانا چاہیے۔ اہم معلومات کے لیے، پیشہ ور انسانی ترجمہ کی سفارش کی جاتی ہے۔ ہم اس ترجمے کے استعمال سے پیدا ہونے والی کسی بھی غلط فہمی یا غلط تشریح کے ذمہ دار نہیں ہیں۔