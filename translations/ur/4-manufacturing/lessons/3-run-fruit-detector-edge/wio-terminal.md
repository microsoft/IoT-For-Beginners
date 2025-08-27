<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "48ac21ec80329c930db7b84bd6b592ec",
  "translation_date": "2025-08-26T22:03:30+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/wio-terminal.md",
  "language_code": "ur"
}
-->
# IoT Edge پر مبنی امیج کلاسفائر کا استعمال کرتے ہوئے تصویر کو پہچانیں - Wio Terminal

اس سبق کے اس حصے میں، آپ IoT Edge ڈیوائس پر چلنے والے امیج کلاسفائر کا استعمال کریں گے۔

## IoT Edge کلاسفائر کا استعمال کریں

IoT ڈیوائس کو IoT Edge امیج کلاسفائر استعمال کرنے کے لیے ری ڈائریکٹ کیا جا سکتا ہے۔ امیج کلاسفائر کے لیے URL `http://<IP address or name>/image` ہے، جہاں `<IP address or name>` کو IoT Edge چلانے والے کمپیوٹر کے IP ایڈریس یا میزبان نام سے تبدیل کریں۔

### کام - IoT Edge کلاسفائر کا استعمال کریں

1. اگر `fruit-quality-detector` ایپ پروجیکٹ پہلے سے کھلا نہیں ہے تو اسے کھولیں۔

1. امیج کلاسفائر ایک REST API کے طور پر HTTP استعمال کرتے ہوئے چل رہا ہے، HTTPS نہیں، لہذا کال کو صرف HTTP کالز کے ساتھ کام کرنے والے WiFi کلائنٹ کی ضرورت ہوگی۔ اس کا مطلب ہے کہ سرٹیفکیٹ کی ضرورت نہیں ہے۔ `config.h` فائل سے `CERTIFICATE` کو حذف کریں۔

1. `config.h` فائل میں پیش گوئی کے URL کو نئے URL میں اپ ڈیٹ کرنے کی ضرورت ہے۔ آپ `PREDICTION_KEY` کو بھی حذف کر سکتے ہیں کیونکہ اس کی ضرورت نہیں ہے۔

    ```cpp
    const char *PREDICTION_URL = "<URL>";
    ```

    `<URL>` کو اپنے کلاسفائر کے URL سے تبدیل کریں۔

1. `main.cpp` میں، WiFi Client Secure کے لیے شامل کرنے والے ڈائریکٹو کو معیاری HTTP ورژن درآمد کرنے کے لیے تبدیل کریں:

    ```cpp
    #include <WiFiClient.h>
    ```

1. `WiFiClient` کے اعلان کو HTTP ورژن میں تبدیل کریں:

    ```cpp
    WiFiClient client;
    ```

1. WiFi کلائنٹ پر سرٹیفکیٹ سیٹ کرنے والی لائن کو منتخب کریں۔ `connectWiFi` فنکشن سے `client.setCACert(CERTIFICATE);` لائن کو حذف کریں۔

1. `classifyImage` فنکشن میں، ہیڈر میں پیش گوئی کی کلید سیٹ کرنے والی لائن `httpClient.addHeader("Prediction-Key", PREDICTION_KEY);` کو حذف کریں۔

1. اپنا کوڈ اپ لوڈ کریں اور چلائیں۔ کیمرے کو کسی پھل کی طرف اشارہ کریں اور C بٹن دبائیں۔ آپ سیریل مانیٹر میں آؤٹ پٹ دیکھیں گے:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 آپ اس کوڈ کو [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/wio-terminal) فولڈر میں تلاش کر سکتے ہیں۔

😀 آپ کا پھل کے معیار کا کلاسفائر پروگرام کامیاب رہا!

---

**ڈسکلیمر**:  
یہ دستاویز AI ترجمہ سروس [Co-op Translator](https://github.com/Azure/co-op-translator) کا استعمال کرتے ہوئے ترجمہ کی گئی ہے۔ ہم درستگی کے لیے کوشش کرتے ہیں، لیکن براہ کرم آگاہ رہیں کہ خودکار ترجمے میں غلطیاں یا غیر درستیاں ہو سکتی ہیں۔ اصل دستاویز کو اس کی اصل زبان میں مستند ذریعہ سمجھا جانا چاہیے۔ اہم معلومات کے لیے، پیشہ ور انسانی ترجمہ کی سفارش کی جاتی ہے۔ ہم اس ترجمے کے استعمال سے پیدا ہونے والی کسی بھی غلط فہمی یا غلط تشریح کے ذمہ دار نہیں ہیں۔