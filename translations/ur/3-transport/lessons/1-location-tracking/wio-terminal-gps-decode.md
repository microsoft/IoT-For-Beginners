<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "fbbcf96a9b63ccd661db98bbf854bb06",
  "translation_date": "2025-08-27T00:51:59+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-decode.md",
  "language_code": "ur"
}
-->
# GPS ڈیٹا کو ڈی کوڈ کریں - Wio Terminal

اس سبق کے اس حصے میں، آپ Wio Terminal کے GPS سینسر سے پڑھے گئے NMEA پیغامات کو ڈی کوڈ کریں گے اور عرض البلد اور طول البلد نکالیں گے۔

## GPS ڈیٹا کو ڈی کوڈ کریں

جب خام NMEA ڈیٹا سیریل پورٹ سے پڑھا جائے، تو اسے ایک اوپن سورس NMEA لائبریری کا استعمال کرتے ہوئے ڈی کوڈ کیا جا سکتا ہے۔

### کام - GPS ڈیٹا کو ڈی کوڈ کریں

ڈوائس کو GPS ڈیٹا کو ڈی کوڈ کرنے کے لیے پروگرام کریں۔

1. اگر `gps-sensor` ایپ پروجیکٹ پہلے سے کھلا نہیں ہے تو اسے کھولیں۔

1. پروجیکٹ کے `platformio.ini` فائل میں [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus) لائبریری کے لیے ایک لائبریری ڈیپینڈنسی شامل کریں۔ اس لائبریری میں NMEA ڈیٹا کو ڈی کوڈ کرنے کے لیے کوڈ موجود ہے۔

    ```ini
    lib_deps =
        mikalhart/TinyGPSPlus @ 1.0.2
    ```

1. `main.cpp` میں، TinyGPSPlus لائبریری کے لیے ایک include directive شامل کریں:

    ```cpp
    #include <TinyGPS++.h>
    ```

1. `Serial3` کے اعلان کے نیچے، NMEA جملوں کو پروسیس کرنے کے لیے ایک TinyGPSPlus آبجیکٹ کا اعلان کریں:

    ```cpp
    TinyGPSPlus gps;
    ```

1. `printGPSData` فنکشن کے مواد کو درج ذیل میں تبدیل کریں:

    ```cpp
    if (gps.encode(Serial3.read()))
    {
        if (gps.location.isValid())
        {
            Serial.print(gps.location.lat(), 6);
            Serial.print(F(","));
            Serial.print(gps.location.lng(), 6);
            Serial.print(" - from ");
            Serial.print(gps.satellites.value());
            Serial.println(" satellites");
        }
    }
    ```

    یہ کوڈ UART سیریل پورٹ سے اگلا کریکٹر `gps` NMEA ڈیکوڈر میں پڑھتا ہے۔ ہر کریکٹر کے بعد، یہ چیک کرے گا کہ آیا ڈیکوڈر نے ایک درست جملہ پڑھا ہے، پھر یہ چیک کرے گا کہ آیا اس نے ایک درست مقام پڑھا ہے۔ اگر مقام درست ہے، تو یہ اسے سیریل مانیٹر پر بھیجے گا، ساتھ ہی ان سیٹلائٹس کی تعداد کے ساتھ جو اس فکس میں شامل تھے۔

1. کوڈ کو Wio Terminal پر بنائیں اور اپلوڈ کریں۔

1. اپلوڈ ہونے کے بعد، آپ سیریل مانیٹر کا استعمال کرتے ہوئے GPS مقام کے ڈیٹا کی نگرانی کر سکتے ہیں۔

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 آپ اس کوڈ کو [code-gps-decode/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/wio-terminal) فولڈر میں تلاش کر سکتے ہیں۔

😀 آپ کا GPS سینسر پروگرام ڈیٹا کو ڈی کوڈ کرنے کے ساتھ کامیاب رہا!

---

**ڈسکلیمر**:  
یہ دستاویز AI ترجمہ سروس [Co-op Translator](https://github.com/Azure/co-op-translator) کا استعمال کرتے ہوئے ترجمہ کی گئی ہے۔ ہم درستگی کے لیے کوشش کرتے ہیں، لیکن براہ کرم آگاہ رہیں کہ خودکار ترجمے میں غلطیاں یا غیر درستیاں ہو سکتی ہیں۔ اصل دستاویز کو اس کی اصل زبان میں مستند ذریعہ سمجھا جانا چاہیے۔ اہم معلومات کے لیے، پیشہ ور انسانی ترجمہ کی سفارش کی جاتی ہے۔ ہم اس ترجمے کے استعمال سے پیدا ہونے والی کسی بھی غلط فہمی یا غلط تشریح کے ذمہ دار نہیں ہیں۔