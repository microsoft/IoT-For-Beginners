<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "50151d9f9dce2801348a93880ef16d86",
  "translation_date": "2025-08-26T22:04:09+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/single-board-computer.md",
  "language_code": "ur"
}
-->
# آئی او ٹی ایج پر مبنی امیج کلاسفائر کے ذریعے تصویر کی درجہ بندی کریں - ورچوئل آئی او ٹی ہارڈویئر اور راسپبیری پائی

اس سبق کے اس حصے میں، آپ آئی او ٹی ایج ڈیوائس پر چلنے والے امیج کلاسفائر کا استعمال کریں گے۔

## آئی او ٹی ایج کلاسفائر کا استعمال کریں

آئی او ٹی ڈیوائس کو آئی او ٹی ایج امیج کلاسفائر استعمال کرنے کے لیے ری ڈائریکٹ کیا جا سکتا ہے۔ امیج کلاسفائر کے لیے یو آر ایل `http://<IP address or name>/image` ہے، جہاں `<IP address or name>` کو آئی او ٹی ایج چلانے والے کمپیوٹر کے آئی پی ایڈریس یا ہوسٹ نام سے تبدیل کریں۔

کاسٹم وژن کے لیے پائتھون لائبریری صرف کلاؤڈ پر ہوسٹ کیے گئے ماڈلز کے ساتھ کام کرتی ہے، آئی او ٹی ایج پر ہوسٹ کیے گئے ماڈلز کے ساتھ نہیں۔ اس کا مطلب ہے کہ آپ کو کلاسفائر کو کال کرنے کے لیے REST API استعمال کرنا ہوگا۔

### کام - آئی او ٹی ایج کلاسفائر کا استعمال کریں

1. اگر `fruit-quality-detector` پروجیکٹ پہلے سے کھلا نہیں ہے تو اسے وی ایس کوڈ میں کھولیں۔ اگر آپ ورچوئل آئی او ٹی ڈیوائس استعمال کر رہے ہیں، تو یقینی بنائیں کہ ورچوئل ماحول فعال ہے۔

1. `app.py` فائل کھولیں، اور `azure.cognitiveservices.vision.customvision.prediction` اور `msrest.authentication` سے درآمدی بیانات کو ہٹا دیں۔

1. فائل کے اوپر درج ذیل درآمد شامل کریں:

    ```python
    import requests
    ```

1. تصویر کو فائل میں محفوظ کرنے کے بعد، `image_file.write(image.read())` سے لے کر فائل کے آخر تک تمام کوڈ کو حذف کریں۔

1. فائل کے آخر میں درج ذیل کوڈ شامل کریں:

    ```python
    prediction_url = '<URL>'
    headers = {
        'Content-Type' : 'application/octet-stream'
    }
    image.seek(0)
    response = requests.post(prediction_url, headers=headers, data=image)
    results = response.json()
    
    for prediction in results['predictions']:
        print(f'{prediction["tagName"]}:\t{prediction["probability"] * 100:.2f}%')
    ```

    `<URL>` کو اپنے کلاسفائر کے یو آر ایل سے تبدیل کریں۔

    یہ کوڈ کلاسفائر کو REST POST درخواست بھیجتا ہے، جس میں تصویر درخواست کے جسم کے طور پر بھیجی جاتی ہے۔ نتائج JSON کے طور پر واپس آتے ہیں، اور یہ ڈی کوڈ ہو کر امکانات کو پرنٹ کرتا ہے۔

1. اپنا کوڈ چلائیں، اپنے کیمرے کو کچھ پھلوں کی طرف اشارہ کریں، یا مناسب تصویر سیٹ کریں، یا اگر ورچوئل آئی او ٹی ہارڈویئر استعمال کر رہے ہیں تو اپنے ویب کیم پر پھل دکھائیں۔ آپ کنسول میں آؤٹ پٹ دیکھیں گے:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 آپ یہ کوڈ [code-classify/pi](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/pi) یا [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/virtual-iot-device) فولڈر میں تلاش کر سکتے ہیں۔

😀 آپ کا پھل معیار کلاسفائر پروگرام کامیاب رہا!

---

**ڈسکلیمر**:  
یہ دستاویز AI ترجمہ سروس [Co-op Translator](https://github.com/Azure/co-op-translator) کا استعمال کرتے ہوئے ترجمہ کی گئی ہے۔ ہم درستگی کے لیے کوشش کرتے ہیں، لیکن براہ کرم آگاہ رہیں کہ خودکار ترجمے میں غلطیاں یا غیر درستیاں ہو سکتی ہیں۔ اصل دستاویز کو اس کی اصل زبان میں مستند ذریعہ سمجھا جانا چاہیے۔ اہم معلومات کے لیے، پیشہ ور انسانی ترجمہ کی سفارش کی جاتی ہے۔ ہم اس ترجمے کے استعمال سے پیدا ہونے والی کسی بھی غلط فہمی یا غلط تشریح کے ذمہ دار نہیں ہیں۔