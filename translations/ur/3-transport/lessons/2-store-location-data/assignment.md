<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "b2e0a965723082b068f735aec0faf3f6",
  "translation_date": "2025-08-27T01:03:18+00:00",
  "source_file": "3-transport/lessons/2-store-location-data/assignment.md",
  "language_code": "ur"
}
-->
# فنکشن بائنڈنگز کی تحقیق کریں

## ہدایات

فنکشن بائنڈنگز آپ کے کوڈ کو اس قابل بناتی ہیں کہ وہ `main` فنکشن سے بلاگز کو بلاگ اسٹوریج میں محفوظ کر سکے۔ Azure اسٹوریج اکاؤنٹ، کلیکشن اور دیگر تفصیلات `function.json` فائل میں ترتیب دی جاتی ہیں۔

Azure یا دیگر Microsoft ٹیکنالوجیز کے ساتھ کام کرتے وقت، معلومات کا بہترین ذریعہ [Microsoft کی دستاویزات docs.com پر](https://docs.microsoft.com/?WT.mc_id=academic-17441-jabenn) ہے۔ اس اسائنمنٹ میں آپ کو Azure Functions بائنڈنگ دستاویزات پڑھنی ہوں گی تاکہ یہ معلوم ہو سکے کہ آؤٹ پٹ بائنڈنگ کو کیسے ترتیب دیا جائے۔

شروع کرنے کے لیے کچھ صفحات یہ ہیں:

* [Azure Functions ٹرگرز اور بائنڈنگز کے تصورات](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python)
* [Azure Blob اسٹوریج بائنڈنگز کے لیے Azure Functions کا جائزہ](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob?WT.mc_id=academic-17441-jabenn)
* [Azure Blob اسٹوریج آؤٹ پٹ بائنڈنگ کے لیے Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob-output?WT.mc_id=academic-17441-jabenn&tabs=python)

## معیار

| معیار | بہترین | مناسب | بہتری کی ضرورت ہے |
| ------ | ------- | ------ | ---------------- |
| بلاگ اسٹوریج آؤٹ پٹ بائنڈنگ کو ترتیب دینا | آؤٹ پٹ بائنڈنگ کو ترتیب دینے، بلاگ کو واپس کرنے اور اسے بلاگ اسٹوریج میں کامیابی سے محفوظ کرنے کے قابل تھا | آؤٹ پٹ بائنڈنگ کو ترتیب دینے یا بلاگ کو واپس کرنے کے قابل تھا لیکن اسے بلاگ اسٹوریج میں کامیابی سے محفوظ کرنے میں ناکام رہا | آؤٹ پٹ بائنڈنگ کو ترتیب دینے میں ناکام رہا |

---

**ڈسکلیمر**:  
یہ دستاویز AI ترجمہ سروس [Co-op Translator](https://github.com/Azure/co-op-translator) کا استعمال کرتے ہوئے ترجمہ کی گئی ہے۔ ہم درستگی کے لیے کوشش کرتے ہیں، لیکن براہ کرم آگاہ رہیں کہ خودکار ترجمے میں غلطیاں یا غیر درستیاں ہو سکتی ہیں۔ اصل دستاویز کو اس کی اصل زبان میں مستند ذریعہ سمجھا جانا چاہیے۔ اہم معلومات کے لیے، پیشہ ور انسانی ترجمہ کی سفارش کی جاتی ہے۔ ہم اس ترجمے کے استعمال سے پیدا ہونے والی کسی بھی غلط فہمی یا غلط تشریح کے ذمہ دار نہیں ہیں۔