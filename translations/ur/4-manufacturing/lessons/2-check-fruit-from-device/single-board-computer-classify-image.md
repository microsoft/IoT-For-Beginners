<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "e5896207b304ce1abaf065b8acc0cc79",
  "translation_date": "2025-08-26T21:50:22+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/single-board-computer-classify-image.md",
  "language_code": "ur"
}
-->
# تصویر کو درجہ بندی کریں - ورچوئل IoT ہارڈویئر اور راسپبیری پائی

اس سبق کے اس حصے میں، آپ کیمرے سے لی گئی تصویر کو کسٹم وژن سروس پر بھیجیں گے تاکہ اسے درجہ بندی کیا جا سکے۔

## تصاویر کو کسٹم وژن پر بھیجیں

کسٹم وژن سروس کے پاس ایک Python SDK موجود ہے جسے آپ تصاویر کی درجہ بندی کے لیے استعمال کر سکتے ہیں۔

### کام - تصاویر کو کسٹم وژن پر بھیجیں

1. `fruit-quality-detector` فولڈر کو VS Code میں کھولیں۔ اگر آپ ورچوئل IoT ڈیوائس استعمال کر رہے ہیں، تو یقینی بنائیں کہ ورچوئل ماحول ٹرمینل میں چل رہا ہے۔

1. کسٹم وژن پر تصاویر بھیجنے کے لیے Python SDK ایک Pip پیکج کے طور پر دستیاب ہے۔ اسے درج ذیل کمانڈ کے ذریعے انسٹال کریں:

    ```sh
    pip3 install azure-cognitiveservices-vision-customvision
    ```

1. `app.py` فائل کے اوپر درج ذیل درآمدی بیانات شامل کریں:

    ```python
    from msrest.authentication import ApiKeyCredentials
    from azure.cognitiveservices.vision.customvision.prediction import CustomVisionPredictionClient
    ```

    یہ کسٹم وژن لائبریریوں سے کچھ ماڈیولز لاتے ہیں، ایک پیش گوئی کی کلید کے ساتھ تصدیق کرنے کے لیے، اور ایک پیش گوئی کلائنٹ کلاس فراہم کرنے کے لیے جو کسٹم وژن کو کال کر سکتا ہے۔

1. فائل کے آخر میں درج ذیل کوڈ شامل کریں:

    ```python
    prediction_url = '<prediction_url>'
    prediction_key = '<prediction key>'
    ```

    `<prediction_url>` کو اس URL سے تبدیل کریں جو آپ نے اس سبق کے پہلے حصے میں *Prediction URL* ڈائیلاگ سے کاپی کیا تھا۔ `<prediction key>` کو اسی ڈائیلاگ سے کاپی کی گئی پیش گوئی کی کلید سے تبدیل کریں۔

1. *Prediction URL* ڈائیلاگ کے ذریعے فراہم کردہ پیش گوئی URL کو REST اینڈ پوائنٹ کو براہ راست کال کرنے کے لیے ڈیزائن کیا گیا ہے۔ Python SDK URL کے مختلف حصوں کو مختلف جگہوں پر استعمال کرتا ہے۔ درج ذیل کوڈ شامل کریں تاکہ اس URL کو مطلوبہ حصوں میں تقسیم کیا جا سکے:

    ```python
    parts = prediction_url.split('/')
    endpoint = 'https://' + parts[2]
    project_id = parts[6]
    iteration_name = parts[9]
    ```

    یہ URL کو تقسیم کرتا ہے، `https://<location>.api.cognitive.microsoft.com` کا اینڈ پوائنٹ، پروجیکٹ ID، اور شائع شدہ تکرار کا نام نکالتا ہے۔

1. پیش گوئی کرنے کے لیے ایک پیش گوئی کرنے والا آبجیکٹ درج ذیل کوڈ کے ساتھ بنائیں:

    ```python
    prediction_credentials = ApiKeyCredentials(in_headers={"Prediction-key": prediction_key})
    predictor = CustomVisionPredictionClient(endpoint, prediction_credentials)
    ```

    `prediction_credentials` پیش گوئی کی کلید کو لپیٹتے ہیں۔ یہ پھر اینڈ پوائنٹ کی طرف اشارہ کرنے والے پیش گوئی کلائنٹ آبجیکٹ بنانے کے لیے استعمال ہوتے ہیں۔

1. تصویر کو کسٹم وژن پر درج ذیل کوڈ کے ذریعے بھیجیں:

    ```python
    image.seek(0)
    results = predictor.classify_image(project_id, iteration_name, image)
    ```

    یہ تصویر کو شروع میں واپس لے جاتا ہے، پھر اسے پیش گوئی کلائنٹ کو بھیجتا ہے۔

1. آخر میں، نتائج کو درج ذیل کوڈ کے ساتھ دکھائیں:

    ```python
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    یہ تمام پیش گوئیوں کے ذریعے لوپ کرے گا جو واپس کی گئی ہیں اور انہیں ٹرمینل پر دکھائے گا۔ واپس کی گئی احتمالات 0-1 کے فلوٹنگ پوائنٹ نمبرز ہیں، جہاں 0 کا مطلب ہے کہ ٹیگ سے میل کھانے کا 0% امکان ہے، اور 1 کا مطلب ہے کہ 100% امکان ہے۔

    > 💁 تصویر کے درجہ بندی کرنے والے تمام ٹیگز کے لیے فیصد واپس کریں گے جو استعمال کیے گئے ہیں۔ ہر ٹیگ کے لیے ایک احتمال ہوگا کہ تصویر اس ٹیگ سے میل کھاتی ہے۔

1. اپنا کوڈ چلائیں، کیمرے کو کچھ پھلوں کی طرف اشارہ کرتے ہوئے، یا مناسب تصویر سیٹ، یا ورچوئل IoT ہارڈویئر استعمال کرتے ہوئے ویب کیم پر نظر آنے والے پھلوں کے ساتھ۔ آپ کنسول میں آؤٹ پٹ دیکھ سکیں گے:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

    آپ لی گئی تصویر اور یہ اقدار **Predictions** ٹیب میں کسٹم وژن میں دیکھ سکیں گے۔

    ![کسٹم وژن میں ایک کیلا، 56.8% پر پکا ہوا اور 43.1% پر کچا ہونے کی پیش گوئی کی گئی](../../../../../translated_images/ur/custom-vision-banana-prediction.30cdff4e1d72db5d9a0be0193790a47c2b387da034e12dc1314dd57ca2131b59.png)

> 💁 آپ اس کوڈ کو [code-classify/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/pi) یا [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/virtual-iot-device) فولڈر میں تلاش کر سکتے ہیں۔

😀 آپ کا پھل معیار درجہ بندی کرنے والا پروگرام کامیاب رہا!

---

**ڈسکلیمر**:  
یہ دستاویز AI ترجمہ سروس [Co-op Translator](https://github.com/Azure/co-op-translator) کا استعمال کرتے ہوئے ترجمہ کی گئی ہے۔ ہم درستگی کے لیے کوشش کرتے ہیں، لیکن براہ کرم آگاہ رہیں کہ خودکار ترجمے میں غلطیاں یا غیر درستیاں ہو سکتی ہیں۔ اصل دستاویز کو اس کی اصل زبان میں مستند ذریعہ سمجھا جانا چاہیے۔ اہم معلومات کے لیے، پیشہ ور انسانی ترجمہ کی سفارش کی جاتی ہے۔ ہم اس ترجمے کے استعمال سے پیدا ہونے والی کسی بھی غلط فہمی یا غلط تشریح کے ذمہ دار نہیں ہیں۔