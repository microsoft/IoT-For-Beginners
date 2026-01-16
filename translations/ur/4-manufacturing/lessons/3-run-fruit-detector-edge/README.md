<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2625af24587465c5547ae33d6cc000a5",
  "translation_date": "2025-08-26T21:58:25+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/README.md",
  "language_code": "ur"
}
-->
# اپنے پھل کا ڈیٹیکٹر ایج پر چلائیں

![اس سبق کا خاکہ](../../../../../translated_images/ur/lesson-17.bc333c3c35ba8e42cce666cfffa82b915f787f455bd94e006aea2b6f2722421a.jpg)

> خاکہ [نیتیا نرسمہن](https://github.com/nitya) کی طرف سے۔ بڑی تصویر دیکھنے کے لیے تصویر پر کلک کریں۔

یہ ویڈیو IoT ڈیوائسز پر امیج کلاسیفائرز چلانے کا جائزہ پیش کرتی ہے، جو اس سبق میں شامل موضوع ہے۔

[![Azure IoT Edge پر Custom Vision AI](https://img.youtube.com/vi/_K5fqGLO8us/0.jpg)](https://www.youtube.com/watch?v=_K5fqGLO8us)

## لیکچر سے پہلے کا کوئز

[لیکچر سے پہلے کا کوئز](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/33)

## تعارف

پچھلے سبق میں آپ نے اپنے امیج کلاسیفائر کا استعمال کرتے ہوئے پکے اور کچے پھلوں کی شناخت کی، اور IoT ڈیوائس کے کیمرے سے لی گئی تصویر کو انٹرنیٹ کے ذریعے کلاؤڈ سروس پر بھیجا۔ یہ کالز وقت لیتی ہیں، پیسے خرچ کرتی ہیں، اور آپ کے استعمال کردہ امیج ڈیٹا کی نوعیت کے مطابق، پرائیویسی کے مسائل پیدا کر سکتی ہیں۔

اس سبق میں آپ سیکھیں گے کہ مشین لرننگ (ML) ماڈلز کو ایج پر کیسے چلایا جائے - یعنی کلاؤڈ کے بجائے آپ کے اپنے نیٹ ورک پر چلنے والے IoT ڈیوائسز پر۔ آپ ایج کمپیوٹنگ کے فوائد اور نقصانات، AI ماڈل کو ایج پر ڈیپلائے کرنے کا طریقہ، اور IoT ڈیوائس سے اس تک رسائی حاصل کرنے کا طریقہ سیکھیں گے۔

اس سبق میں ہم درج ذیل موضوعات کا احاطہ کریں گے:

* [ایج کمپیوٹنگ](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Azure IoT Edge](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [IoT Edge ڈیوائس رجسٹر کریں](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [IoT Edge ڈیوائس سیٹ اپ کریں](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [اپنا ماڈل ایکسپورٹ کریں](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [ڈیپلائےمنٹ کے لیے اپنے کنٹینر کو تیار کریں](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [اپنا کنٹینر ڈیپلائے کریں](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [اپنے IoT Edge ڈیوائس کا استعمال کریں](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)

## ایج کمپیوٹنگ

ایج کمپیوٹنگ کا مطلب ہے کہ IoT ڈیٹا کو اس جگہ کے قریب ترین کمپیوٹرز پر پروسیس کیا جائے جہاں ڈیٹا پیدا ہوتا ہے۔ اس پروسیسنگ کو کلاؤڈ میں کرنے کے بجائے، اسے کلاؤڈ کے ایج پر منتقل کیا جاتا ہے - یعنی آپ کے اندرونی نیٹ ورک پر۔

![ایک آرکیٹیکچر ڈایاگرام جو کلاؤڈ میں انٹرنیٹ سروسز اور لوکل نیٹ ورک پر IoT ڈیوائسز کو دکھاتا ہے](../../../../../translated_images/ur/cloud-without-edge.b4da641f6022c95ed6b91fde8b5323abd2f94e0d52073ad54172ae8f5dac90e9.png)

اب تک کے اسباق میں، آپ نے ڈیٹا جمع کرنے والے ڈیوائسز کو کلاؤڈ میں بھیجتے ہوئے دیکھا ہے تاکہ وہاں تجزیہ کیا جا سکے، اور کلاؤڈ میں سرور لیس فنکشنز یا AI ماڈلز چلائے جا سکیں۔

![ایک آرکیٹیکچر ڈایاگرام جو لوکل نیٹ ورک پر IoT ڈیوائسز کو ایج ڈیوائسز سے جوڑتا ہے، اور وہ ایج ڈیوائسز کلاؤڈ سے جڑتی ہیں](../../../../../translated_images/ur/cloud-with-edge.1e26462c62c126fe150bd15a5714ddf0be599f09bacbad08b85be02b76ea1ae1.png)

ایج کمپیوٹنگ میں کلاؤڈ سروسز کو کلاؤڈ سے ہٹا کر ان کمپیوٹرز پر منتقل کیا جاتا ہے جو IoT ڈیوائسز کے ساتھ ایک ہی نیٹ ورک پر چل رہے ہیں، اور صرف ضرورت پڑنے پر کلاؤڈ سے رابطہ کرتے ہیں۔ مثال کے طور پر، آپ ایج ڈیوائسز پر AI ماڈلز چلا سکتے ہیں تاکہ پھلوں کی پختگی کا تجزیہ کیا جا سکے، اور صرف تجزیاتی ڈیٹا کلاؤڈ کو بھیج سکتے ہیں، جیسے کہ پکے اور کچے پھلوں کی تعداد۔

✅ ان IoT ایپلیکیشنز کے بارے میں سوچیں جو آپ نے اب تک بنائی ہیں۔ ان میں سے کون سے حصے ایج پر منتقل کیے جا سکتے ہیں؟

### فوائد

ایج کمپیوٹنگ کے فوائد درج ذیل ہیں:

1. **رفتار** - ایج کمپیوٹنگ وقت کے حساس ڈیٹا کے لیے مثالی ہے کیونکہ کارروائیاں ڈیوائس کے نیٹ ورک پر ہی کی جاتی ہیں، بجائے اس کے کہ انٹرنیٹ کے ذریعے کالز کی جائیں۔ اندرونی نیٹ ورک انٹرنیٹ کنیکشنز کے مقابلے میں زیادہ تیز رفتار ہو سکتے ہیں، اور ڈیٹا کو کم فاصلے پر سفر کرنا پڑتا ہے۔

    > 💁 اگرچہ انٹرنیٹ کنیکشنز کے لیے آپٹیکل کیبلز استعمال کیے جاتے ہیں جو ڈیٹا کو روشنی کی رفتار سے سفر کرنے دیتے ہیں، ڈیٹا کو کلاؤڈ پرووائیڈرز تک پہنچنے میں وقت لگ سکتا ہے۔ مثال کے طور پر، اگر آپ یورپ سے ڈیٹا امریکہ میں کلاؤڈ سروسز کو بھیج رہے ہیں، تو آپٹیکل کیبل کے ذریعے بحر اوقیانوس عبور کرنے میں کم از کم 28 ملی سیکنڈ لگتے ہیں، اور یہ وقت ڈیٹا کو کیبل تک پہنچانے، الیکٹریکل سگنلز کو روشنی میں تبدیل کرنے اور دوسری طرف دوبارہ الیکٹریکل سگنلز میں تبدیل کرنے کے وقت کو نظر انداز کرتا ہے۔

    ایج کمپیوٹنگ کم نیٹ ورک ٹریفک کی ضرورت ہوتی ہے، جس سے انٹرنیٹ کنیکشن کی محدود بینڈوڈتھ پر بھیڑ کی وجہ سے ڈیٹا کے سست ہونے کا خطرہ کم ہو جاتا ہے۔

1. **دور دراز رسائی** - ایج کمپیوٹنگ اس وقت کام کرتی ہے جب آپ کے پاس محدود یا کوئی کنیکٹیویٹی نہ ہو، یا کنیکٹیویٹی مسلسل استعمال کرنے کے لیے بہت مہنگی ہو۔ مثال کے طور پر، انسانی امدادی آفات کے علاقوں میں جہاں انفراسٹرکچر محدود ہے، یا ترقی پذیر ممالک میں۔

1. **کم لاگت** - ڈیٹا جمع کرنے، ذخیرہ کرنے، تجزیہ کرنے، اور ایج ڈیوائس پر کارروائی کرنے سے کلاؤڈ سروسز کا استعمال کم ہو جاتا ہے، جس سے آپ کی IoT ایپلیکیشن کی مجموعی لاگت کم ہو سکتی ہے۔ حالیہ دنوں میں ایج کمپیوٹنگ کے لیے ڈیزائن کیے گئے ڈیوائسز میں اضافہ ہوا ہے، جیسے کہ [NVIDIA کا Jetson Nano](https://developer.nvidia.com/embedded/jetson-nano-developer-kit)، جو GPU پر مبنی ہارڈویئر کا استعمال کرتے ہوئے AI ورک لوڈز کو US$100 سے کم قیمت والے ڈیوائسز پر چلا سکتا ہے۔

1. **پرائیویسی اور سیکیورٹی** - ایج کمپیوٹنگ کے ساتھ، ڈیٹا آپ کے نیٹ ورک پر رہتا ہے اور کلاؤڈ پر اپلوڈ نہیں ہوتا۔ یہ حساس اور ذاتی طور پر قابل شناخت معلومات کے لیے اکثر ترجیح دی جاتی ہے، خاص طور پر کیونکہ ڈیٹا کو تجزیہ کے بعد ذخیرہ کرنے کی ضرورت نہیں ہوتی، جس سے ڈیٹا لیک ہونے کا خطرہ بہت کم ہو جاتا ہے۔ مثالوں میں طبی ڈیٹا اور سیکیورٹی کیمرہ فوٹیج شامل ہیں۔

1. **غیر محفوظ ڈیوائسز کا انتظام** - اگر آپ کے پاس ایسے ڈیوائسز ہیں جن میں معلوم سیکیورٹی خامیاں ہیں اور آپ انہیں اپنے نیٹ ورک یا انٹرنیٹ سے براہ راست جوڑنا نہیں چاہتے، تو آپ انہیں ایک الگ نیٹ ورک پر ایک گیٹ وے IoT Edge ڈیوائس سے جوڑ سکتے ہیں۔ یہ ایج ڈیوائس پھر آپ کے وسیع نیٹ ورک یا انٹرنیٹ سے بھی جڑ سکتا ہے، اور ڈیٹا کے بہاؤ کو آگے پیچھے منظم کر سکتا ہے۔

1. **غیر مطابقت پذیر ڈیوائسز کے لیے سپورٹ** - اگر آپ کے پاس ایسے ڈیوائسز ہیں جو IoT Hub سے جڑ نہیں سکتے، جیسے کہ وہ ڈیوائسز جو صرف HTTP کنیکشنز کے ذریعے جڑ سکتے ہیں یا وہ ڈیوائسز جن کے پاس صرف بلوٹوتھ کنیکشن ہے، تو آپ IoT Edge ڈیوائس کو گیٹ وے ڈیوائس کے طور پر استعمال کر سکتے ہیں، جو پیغامات کو IoT Hub تک پہنچاتا ہے۔

✅ تحقیق کریں: ایج کمپیوٹنگ کے اور کون سے فوائد ہو سکتے ہیں؟

### نقصانات

ایج کمپیوٹنگ کے نقصانات ہیں، جہاں کلاؤڈ ایک ترجیحی آپشن ہو سکتا ہے:

1. **پیمائش اور لچک** - کلاؤڈ کمپیوٹنگ نیٹ ورک اور ڈیٹا کی ضروریات کے مطابق حقیقی وقت میں وسائل کو بڑھا یا کم کر سکتی ہے۔ مزید ایج کمپیوٹرز شامل کرنے کے لیے دستی طور پر مزید ڈیوائسز شامل کرنا پڑتا ہے۔

1. **قابل اعتماد اور لچکدار** - کلاؤڈ کمپیوٹنگ متعدد سرورز فراہم کرتی ہے، اکثر متعدد مقامات پر، ریڈنڈنسی اور آفات سے بحالی کے لیے۔ ایج پر اسی سطح کی ریڈنڈنسی حاصل کرنے کے لیے بڑے سرمایہ کاری اور بہت زیادہ کنفیگریشن کام کی ضرورت ہوتی ہے۔

1. **نگہداشت** - کلاؤڈ سروس پرووائیڈرز سسٹم کی نگہداشت اور اپڈیٹس فراہم کرتے ہیں۔

✅ تحقیق کریں: ایج کمپیوٹنگ کے اور کون سے نقصانات ہو سکتے ہیں؟

نقصانات کلاؤڈ کے فوائد کے بالکل برعکس ہیں - آپ کو ان ڈیوائسز کو خود بنانا اور منظم کرنا پڑتا ہے، بجائے اس کے کہ کلاؤڈ پرووائیڈرز کی مہارت اور پیمائش پر انحصار کریں۔

کچھ خطرات ایج کمپیوٹنگ کی نوعیت کی وجہ سے کم ہو جاتے ہیں۔ مثال کے طور پر، اگر آپ کے پاس ایک ایج ڈیوائس فیکٹری میں چل رہا ہے جو مشینری سے ڈیٹا جمع کر رہا ہے، تو آپ کو کچھ آفات سے بحالی کے منظرناموں کے بارے میں سوچنے کی ضرورت نہیں ہے۔ اگر فیکٹری کی بجلی چلی جاتی ہے تو آپ کو بیک اپ ایج ڈیوائس کی ضرورت نہیں ہوتی کیونکہ وہ مشینیں جو ڈیٹا پیدا کرتی ہیں، جسے ایج ڈیوائس پروسیس کرتا ہے، بھی بجلی کے بغیر ہوں گی۔

IoT سسٹمز کے لیے، آپ اکثر کلاؤڈ اور ایج کمپیوٹنگ کا امتزاج چاہتے ہیں، ہر سروس کو سسٹم، اس کے صارفین، اور اس کے منتظمین کی ضروریات کے مطابق استعمال کرتے ہوئے۔

## Azure IoT Edge

![Azure IoT Edge کا لوگو](../../../../../translated_images/ur/azure-iot-edge-logo.c1c076749b5cba2e8755262fadc2f19ca1146b948d76990b1229199ac2292d79.png)

Azure IoT Edge ایک سروس ہے جو آپ کو ورک لوڈز کو کلاؤڈ سے ایج پر منتقل کرنے میں مدد دیتی ہے۔ آپ ایک ڈیوائس کو ایج ڈیوائس کے طور پر سیٹ اپ کرتے ہیں، اور کلاؤڈ سے اس ایج ڈیوائس پر کوڈ ڈیپلائے کر سکتے ہیں۔ یہ آپ کو کلاؤڈ اور ایج کی صلاحیتوں کو ملانے کی اجازت دیتا ہے۔

> 🎓 *ورک لوڈز* کسی بھی سروس کے لیے استعمال ہونے والی اصطلاح ہے جو کسی قسم کا کام کرتی ہے، جیسے کہ AI ماڈلز، ایپلیکیشنز، یا سرور لیس فنکشنز۔

مثال کے طور پر، آپ کلاؤڈ میں ایک امیج کلاسیفائر کو ٹرین کر سکتے ہیں، پھر کلاؤڈ سے اسے ایج ڈیوائس پر ڈیپلائے کر سکتے ہیں۔ آپ کا IoT ڈیوائس پھر امیجز کو کلاسیفیکیشن کے لیے ایج ڈیوائس پر بھیجتا ہے، بجائے اس کے کہ امیجز کو انٹرنیٹ کے ذریعے بھیجا جائے۔ اگر آپ کو ماڈل کا نیا ورژن ڈیپلائے کرنے کی ضرورت ہو، تو آپ اسے کلاؤڈ میں ٹرین کر سکتے ہیں اور IoT Edge کا استعمال کرتے ہوئے ایج ڈیوائس پر ماڈل کو اپڈیٹ کر سکتے ہیں۔

> 🎓 وہ سافٹ ویئر جو IoT Edge پر ڈیپلائے کیا جاتا ہے اسے *ماڈیولز* کہا جاتا ہے۔ ڈیفالٹ طور پر IoT Edge ایسے ماڈیولز چلاتا ہے جو IoT Hub کے ساتھ بات چیت کرتے ہیں، جیسے کہ `edgeAgent` اور `edgeHub` ماڈیولز۔ جب آپ ایک امیج کلاسیفائر ڈیپلائے کرتے ہیں، تو یہ ایک اضافی ماڈیول کے طور پر ڈیپلائے کیا جاتا ہے۔

IoT Edge IoT Hub میں بنایا گیا ہے، لہذا آپ ایج ڈیوائسز کو اسی سروس کا استعمال کرتے ہوئے منظم کر سکتے ہیں جو آپ IoT ڈیوائسز کو منظم کرنے کے لیے استعمال کرتے ہیں، اسی سطح کی سیکیورٹی کے ساتھ۔

IoT Edge کو *کنٹینرز* سے کوڈ چلانے کے لیے استعمال کیا جاتا ہے - خود مختار ایپلیکیشنز جو آپ کے کمپیوٹر پر موجود دیگر ایپلیکیشنز سے الگ تھلگ چلائی جاتی ہیں۔ جب آپ ایک کنٹینر چلاتے ہیں، تو یہ آپ کے کمپیوٹر کے اندر ایک الگ کمپیوٹر کی طرح کام کرتا ہے، جس میں اپنا سافٹ ویئر، سروسز، اور ایپلیکیشنز چل رہی ہوتی ہیں۔ زیادہ تر وقت کنٹینرز آپ کے کمپیوٹر پر کسی چیز تک رسائی حاصل نہیں کر سکتے جب تک کہ آپ کسی چیز کو، جیسے کہ ایک فولڈر، کنٹینر کے ساتھ شیئر کرنے کا انتخاب نہ کریں۔ کنٹینر پھر ایک کھلے پورٹ کے ذریعے سروسز کو ظاہر کرتا ہے جس سے آپ جڑ سکتے ہیں یا اپنے نیٹ ورک پر ظاہر کر سکتے ہیں۔

![ایک ویب درخواست کو کنٹینر کی طرف ری ڈائریکٹ کیا جا رہا ہے](../../../../../translated_images/ur/container-web-browser.4ee81dd4f0d8838ce622b2a0d600b6a4322b5d4fe43159facd87b7b34f84d66a.png)

مثال کے طور پر، آپ کے پاس ایک کنٹینر ہو سکتا ہے جس میں ایک ویب سائٹ پورٹ 80 پر چل رہی ہو، جو ڈیفالٹ HTTP پورٹ ہے، اور آپ اسے اپنے کمپیوٹر سے بھی پورٹ 80 پر ظاہر کر سکتے ہیں۔

✅ تحقیق کریں: کنٹینرز اور Docker یا Moby جیسی سروسز کے بارے میں پڑھیں۔

آپ Custom Vision کا استعمال کرتے ہوئے امیج کلاسیفائرز کو ڈاؤنلوڈ کر سکتے ہیں اور انہیں کنٹینرز کے طور پر ڈیپلائے کر سکتے ہیں، یا تو براہ راست ڈیوائس پر چلانے کے لیے یا IoT Edge کے ذریعے ڈیپلائے کرنے کے لیے۔ ایک بار جب وہ کنٹینر میں چل رہے ہوں، تو انہیں اسی REST API کا استعمال کرتے ہوئے رسائی حاصل کی جا سکتی ہے جو کلاؤڈ ورژن کے لیے استعمال ہوتی ہے، لیکن ایج ڈیوائس پر چلنے والے کنٹینر کی طرف اشارہ کرتے ہوئے۔

## IoT Edge ڈیوائس رجسٹر کریں

IoT Edge ڈیوائس استعمال کرنے کے لیے، اسے IoT Hub میں رجسٹر کرنا ضروری ہے۔

### کام - IoT Edge ڈیوائس رجسٹر کریں

1. `fruit-quality-detector` ریسورس گروپ میں ایک IoT Hub بنائیں۔ اسے `fruit-quality-detector` پر مبنی ایک منفرد نام دیں۔

1. اپنے IoT Hub میں `fruit-quality-detector-edge` نامی ایک IoT Edge ڈیوائس رجسٹر کریں۔ یہ کمانڈ ایک غیر ایج ڈیوائس رجسٹر کرنے کے لیے استعمال ہونے والے کمانڈ سے ملتی جلتی ہے، سوائے اس کے کہ آپ `--edge-enabled` فلیگ پاس کرتے ہیں۔

    ```sh
    az iot hub device-identity create --edge-enabled \
                                      --device-id fruit-quality-detector-edge \
                                      --hub-name <hub_name>
    ```

    `<hub_name>` کو اپنے IoT Hub کے نام سے تبدیل کریں۔

1. اپنے ڈیوائس کے لیے کنکشن اسٹرنگ حاصل کرنے کے لیے درج ذیل کمانڈ استعمال کریں:

    ```sh
    az iot hub device-identity connection-string show --device-id fruit-quality-detector-edge \
                                                      --output table \
                                                      --hub-name <hub_name>
    ```

    `<hub_name>` کو اپنے IoT Hub کے نام سے تبدیل کریں۔

    آؤٹ پٹ میں دکھائی گئی کنکشن اسٹرنگ کی ایک کاپی لے لیں۔

## IoT Edge ڈیوائس سیٹ اپ کریں

ایک بار جب آپ نے اپنے IoT Hub میں ایج ڈیوائس رجسٹریشن بنا لی، تو آپ ایج ڈیوائس سیٹ اپ کر سکتے ہیں۔

### کام - IoT Edge رن ٹائم انسٹال کریں اور شروع کریں

**IoT Edge رن ٹائم صرف لینکس کنٹینرز چلاتا ہے۔** یہ لینکس پر چلایا جا سکتا ہے، یا ونڈوز پر لینکس ورچوئل مشینز کا استعمال کرتے ہوئے۔

* اگر آپ Raspberry Pi کو اپنے IoT ڈیوائس کے طور پر استعمال کر رہے ہیں، تو یہ لینکس کا ایک سپورٹ شدہ ورژن چلاتا ہے اور IoT Edge رن ٹائم کی میزبانی کر سکتا ہے۔ [Microsoft Docs پر لینکس کے لیے Azure IoT Edge انسٹال کرنے کی گائیڈ](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge?WT.mc_id=academic-17441-jabenn) کو فالو کریں تاکہ IoT Edge انسٹال کریں اور کنکشن اسٹرنگ سیٹ کریں۔

    > 💁 یاد رکھیں، Raspberry Pi OS Debian لینکس کا ایک ورژن ہے۔

* اگر آپ Raspberry Pi استعمال نہیں کر رہے ہیں، لیکن آپ کے پاس ایک لینکس کمپیوٹر ہے، تو آپ IoT Edge رن ٹائم چلا سکتے ہیں۔ [Microsoft Docs پر لینکس کے لیے Azure IoT Edge انسٹال کرنے کی گائیڈ](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge?WT.mc_id=academic-17441-jabenn) کو فالو کریں تاکہ IoT Edge انسٹال کریں اور کنکشن اسٹرنگ سیٹ کریں۔

* اگر آپ ونڈوز استعمال کر رہے ہیں، تو آپ لینکس ورچوئل مشین میں IoT Edge رن ٹائم انسٹال کر سکتے ہیں۔ [Microsoft Docs پر ونڈوز ڈیوائس پر IoT Edge ماڈیول ڈیپلائے کرنے کے لیے کوئیک اسٹارٹ](https://docs.microsoft.com/azure/iot-edge/quickstart?WT.mc_id=academic-17441-jabenn#install-and-start-the-iot-edge-runtime) کے *Install and start the IoT
1. [CustomVision.ai](https://customvision.ai) پر Custom Vision پورٹل لانچ کریں اور سائن ان کریں اگر آپ نے پہلے سے اسے کھولا نہیں ہے۔ پھر اپنے `fruit-quality-detector` پروجیکٹ کو کھولیں۔

1. **Settings** بٹن (⚙ آئیکن) کو منتخب کریں۔

1. *Domains* کی فہرست میں، *Food (compact)* کو منتخب کریں۔

1. *Export Capabilities* کے تحت، یقینی بنائیں کہ *Basic platforms (Tensorflow, CoreML, ONNX, ...)* منتخب ہے۔

1. Settings صفحے کے نیچے **Save Changes** کو منتخب کریں۔

1. ماڈل کو **Train** بٹن کے ذریعے دوبارہ تربیت دیں، اور *Quick training* کو منتخب کریں۔

### کام - اپنے ماڈل کو ایکسپورٹ کریں

جب ماڈل تربیت یافتہ ہو جائے، تو اسے ایک کنٹینر کے طور پر ایکسپورٹ کرنے کی ضرورت ہوگی۔

1. **Performance** ٹیب کو منتخب کریں، اور اپنی تازہ ترین iteration کو تلاش کریں جو compact domain استعمال کرتے ہوئے تربیت یافتہ تھی۔

1. اوپر **Export** بٹن کو منتخب کریں۔

1. **DockerFile** کو منتخب کریں، پھر ایک ورژن منتخب کریں جو آپ کے edge device سے مطابقت رکھتا ہو:

    * اگر آپ IoT Edge کو لینکس کمپیوٹر، ونڈوز کمپیوٹر یا ورچوئل مشین پر چلا رہے ہیں، تو *Linux* ورژن منتخب کریں۔
    * اگر آپ IoT Edge کو Raspberry Pi پر چلا رہے ہیں، تو *ARM (Raspberry Pi 3)* ورژن منتخب کریں۔

> 🎓 Docker کنٹینرز کو منظم کرنے کے لیے سب سے زیادہ مقبول ٹولز میں سے ایک ہے، اور DockerFile کنٹینر کو سیٹ اپ کرنے کے لیے ہدایات کا ایک مجموعہ ہے۔

1. **Export** کو منتخب کریں تاکہ Custom Vision متعلقہ فائلیں بنائے، پھر **Download** کو منتخب کریں تاکہ انہیں zip فائل میں ڈاؤنلوڈ کریں۔

1. فائلوں کو اپنے کمپیوٹر پر محفوظ کریں، پھر فولڈر کو ان زپ کریں۔

## اپنے کنٹینر کو تعیناتی کے لیے تیار کریں

![کنٹینرز بنائے جاتے ہیں، پھر کنٹینر رجسٹری میں دھکیلے جاتے ہیں، پھر IoT Edge کے ذریعے edge device پر تعینات کیے جاتے ہیں](../../../../../translated_images/ur/container-edge-flow.c246050dd60ceefdb6ace026a4ce5c6aa4112bb5898ae23fbb2ab4be29ae3e1b.png)

جب آپ نے اپنا ماڈل ڈاؤنلوڈ کر لیا ہو، تو اسے ایک کنٹینر میں بنایا جانا چاہیے، پھر ایک کنٹینر رجسٹری میں دھکیلا جانا چاہیے - ایک آن لائن مقام جہاں آپ کنٹینرز کو ذخیرہ کر سکتے ہیں۔ IoT Edge پھر رجسٹری سے کنٹینر کو ڈاؤنلوڈ کر سکتا ہے اور اسے آپ کے ڈیوائس پر دھکیل سکتا ہے۔

![Azure Container Registry کا لوگو](../../../../../translated_images/ur/azure-container-registry-logo.09494206991d4b295025ebff7d4e2900325e527a59184ffbc8464b6ab59654be.png)

اس سبق کے لیے آپ جو کنٹینر رجسٹری استعمال کریں گے وہ Azure Container Registry ہے۔ یہ ایک مفت سروس نہیں ہے، لہذا پیسے بچانے کے لیے یقینی بنائیں کہ آپ [اپنے پروجیکٹ کو صاف کریں](../../../clean-up.md) جب آپ کام ختم کر لیں۔

> 💁 آپ Azure Container Registry استعمال کرنے کے اخراجات [Azure Container Registry pricing page](https://azure.microsoft.com/pricing/details/container-registry/?WT.mc_id=academic-17441-jabenn) پر دیکھ سکتے ہیں۔

### کام - Docker انسٹال کریں

classifier کو بنانے اور تعینات کرنے کے لیے، آپ کو [Docker](https://www.docker.com/) انسٹال کرنے کی ضرورت ہو سکتی ہے۔

آپ کو صرف اس وقت ایسا کرنے کی ضرورت ہوگی اگر آپ اپنے کنٹینر کو اس ڈیوائس سے مختلف ڈیوائس پر بنانا چاہتے ہیں جس پر آپ نے IoT Edge انسٹال کیا ہے - IoT Edge انسٹال کرنے کے حصے کے طور پر، Docker آپ کے لیے انسٹال کیا جاتا ہے۔

1. اگر آپ Docker کنٹینر کو اپنے IoT Edge ڈیوائس سے مختلف ڈیوائس پر بنا رہے ہیں، تو [Docker install page](https://www.docker.com/products/docker-desktop) پر Docker Desktop یا Docker engine انسٹال کرنے کی ہدایات پر عمل کریں۔ انسٹالیشن کے بعد یقینی بنائیں کہ یہ چل رہا ہے۔

### کام - کنٹینر رجسٹری ریسورس بنائیں

1. اپنے ٹرمینل یا کمانڈ پرامپٹ سے درج ذیل کمانڈ چلائیں تاکہ Azure Container Registry ریسورس بنائیں:

    ```sh
    az acr create --resource-group fruit-quality-detector \
                  --sku Basic \
                  --name <Container registry name>
    ```

    `<Container registry name>` کو اپنے کنٹینر رجسٹری کے لیے ایک منفرد نام سے تبدیل کریں، صرف حروف اور نمبروں کا استعمال کریں۔ اسے `fruitqualitydetector` کے ارد گرد بنائیں۔ یہ نام کنٹینر رجسٹری تک رسائی کے URL کا حصہ بن جاتا ہے، لہذا یہ عالمی طور پر منفرد ہونا چاہیے۔

1. درج ذیل کمانڈ کے ساتھ Azure Container Registry میں لاگ ان کریں:

    ```sh
    az acr login --name <Container registry name>
    ```

    `<Container registry name>` کو اپنے کنٹینر رجسٹری کے نام سے تبدیل کریں۔

1. کنٹینر رجسٹری کو ایڈمن موڈ میں سیٹ کریں تاکہ آپ پاس ورڈ جنریٹ کر سکیں، درج ذیل کمانڈ کے ساتھ:

    ```sh
    az acr update --admin-enabled true \
                 --name <Container registry name>
    ```

    `<Container registry name>` کو اپنے کنٹینر رجسٹری کے نام سے تبدیل کریں۔

1. درج ذیل کمانڈ کے ساتھ اپنے کنٹینر رجسٹری کے لیے پاس ورڈز جنریٹ کریں:

    ```sh
     az acr credential renew --password-name password \
                             --output table \
                             --name <Container registry name>
    ```

    `<Container registry name>` کو اپنے کنٹینر رجسٹری کے نام سے تبدیل کریں۔

    `PASSWORD` کی ویلیو کاپی کریں، کیونکہ آپ کو یہ بعد میں ضرورت ہوگی۔

### کام - اپنے کنٹینر کو بنائیں

جو آپ نے Custom Vision سے ڈاؤنلوڈ کیا وہ ایک DockerFile تھا جس میں کنٹینر کو بنانے کے لیے ہدایات شامل تھیں، ساتھ ہی ایپلیکیشن کوڈ جو کنٹینر کے اندر چلایا جائے گا تاکہ آپ کے Custom Vision ماڈل کو ہوسٹ کیا جا سکے، اور ایک REST API جسے کال کیا جا سکے۔ آپ Docker کا استعمال کرتے ہوئے DockerFile سے ایک ٹیگ شدہ کنٹینر بنا سکتے ہیں، پھر اسے اپنی کنٹینر رجسٹری میں دھکیل سکتے ہیں۔

> 🎓 کنٹینرز کو ایک ٹیگ دیا جاتا ہے جو ان کے نام اور ورژن کو بیان کرتا ہے۔ جب آپ کو کنٹینر کو اپ ڈیٹ کرنے کی ضرورت ہو تو آپ اسے اسی ٹیگ کے ساتھ لیکن ایک نئے ورژن کے ساتھ بنا سکتے ہیں۔

1. اپنے ٹرمینل یا کمانڈ پرامپٹ کو کھولیں اور Custom Vision سے ڈاؤنلوڈ کیے گئے ان زپ شدہ ماڈل پر جائیں۔

1. درج ذیل کمانڈ چلائیں تاکہ امیج کو بنائیں اور ٹیگ کریں:

    ```sh
    docker build --platform <platform> -t <Container registry name>.azurecr.io/classifier:v1 .
    ```

    `<platform>` کو اس پلیٹ فارم سے تبدیل کریں جس پر یہ کنٹینر چلایا جائے گا۔ اگر آپ IoT Edge کو Raspberry Pi پر چلا رہے ہیں، تو اسے `linux/armhf` پر سیٹ کریں، ورنہ اسے `linux/amd64` پر سیٹ کریں۔

    > 💁 اگر آپ یہ کمانڈ اس ڈیوائس سے چلا رہے ہیں جس پر آپ IoT Edge چلا رہے ہیں، جیسے کہ Raspberry Pi سے، تو آپ `--platform <platform>` حصہ کو چھوڑ سکتے ہیں کیونکہ یہ ڈیفالٹ طور پر موجودہ پلیٹ فارم پر سیٹ ہوتا ہے۔

    `<Container registry name>` کو اپنے کنٹینر رجسٹری کے نام سے تبدیل کریں۔

    > 💁 اگر آپ لینکس یا Raspberry Pi OS پر چل رہے ہیں تو آپ کو یہ کمانڈ چلانے کے لیے `sudo` استعمال کرنے کی ضرورت ہو سکتی ہے۔

    Docker امیج کو بنائے گا، تمام ضروری سافٹ ویئر کو کنفیگر کرے گا۔ امیج کو پھر `classifier:v1` کے طور پر ٹیگ کیا جائے گا۔

    ```output
    ➜  d4ccc45da0bb478bad287128e1274c3c.DockerFile.Linux docker build --platform linux/amd64 -t  fruitqualitydetectorjimb.azurecr.io/classifier:v1 .
    [+] Building 102.4s (11/11) FINISHED
     => [internal] load build definition from Dockerfile
     => => transferring dockerfile: 131B
     => [internal] load .dockerignore
     => => transferring context: 2B
     => [internal] load metadata for docker.io/library/python:3.7-slim
     => [internal] load build context
     => => transferring context: 905B
     => [1/6] FROM docker.io/library/python:3.7-slim@sha256:b21b91c9618e951a8cbca5b696424fa5e820800a88b7e7afd66bba0441a764d6
     => => resolve docker.io/library/python:3.7-slim@sha256:b21b91c9618e951a8cbca5b696424fa5e820800a88b7e7afd66bba0441a764d6
     => => sha256:b4d181a07f8025e00e0cb28f1cc14613da2ce26450b80c54aea537fa93cf3bda 27.15MB / 27.15MB
     => => sha256:de8ecf497b753094723ccf9cea8a46076e7cb845f333df99a6f4f397c93c6ea9 2.77MB / 2.77MB
     => => sha256:707b80804672b7c5d8f21e37c8396f319151e1298d976186b4f3b76ead9f10c8 10.06MB / 10.06MB
     => => sha256:b21b91c9618e951a8cbca5b696424fa5e820800a88b7e7afd66bba0441a764d6 1.86kB / 1.86kB
     => => sha256:44073386687709c437586676b572ff45128ff1f1570153c2f727140d4a9accad 1.37kB / 1.37kB
     => => sha256:3d94f0f2ca798607808b771a7766f47ae62a26f820e871dd488baeccc69838d1 8.31kB / 8.31kB
     => => sha256:283715715396fd56d0e90355125fd4ec57b4f0773f306fcd5fa353b998beeb41 233B / 233B
     => => sha256:8353afd48f6b84c3603ea49d204bdcf2a1daada15f5d6cad9cc916e186610a9f 2.64MB / 2.64MB
     => => extracting sha256:b4d181a07f8025e00e0cb28f1cc14613da2ce26450b80c54aea537fa93cf3bda
     => => extracting sha256:de8ecf497b753094723ccf9cea8a46076e7cb845f333df99a6f4f397c93c6ea9
     => => extracting sha256:707b80804672b7c5d8f21e37c8396f319151e1298d976186b4f3b76ead9f10c8
     => => extracting sha256:283715715396fd56d0e90355125fd4ec57b4f0773f306fcd5fa353b998beeb41
     => => extracting sha256:8353afd48f6b84c3603ea49d204bdcf2a1daada15f5d6cad9cc916e186610a9f
     => [2/6] RUN pip install -U pip
     => [3/6] RUN pip install --no-cache-dir numpy~=1.17.5 tensorflow~=2.0.2 flask~=1.1.2 pillow~=7.2.0
     => [4/6] RUN pip install --no-cache-dir mscviplib==2.200731.16
     => [5/6] COPY app /app
     => [6/6] WORKDIR /app
     => exporting to image
     => => exporting layers
     => => writing image sha256:1846b6f134431f78507ba7c079358ed66d944c0e185ab53428276bd822400386
     => => naming to fruitqualitydetectorjimb.azurecr.io/classifier:v1
    ```

### کام - اپنے کنٹینر کو اپنی کنٹینر رجسٹری میں دھکیلیں

1. درج ذیل کمانڈ کا استعمال کرتے ہوئے اپنے کنٹینر کو اپنی کنٹینر رجسٹری میں دھکیلیں:

    ```sh
    docker push <Container registry name>.azurecr.io/classifier:v1
    ```

    `<Container registry name>` کو اپنے کنٹینر رجسٹری کے نام سے تبدیل کریں۔

    > 💁 اگر آپ لینکس پر چل رہے ہیں تو آپ کو یہ کمانڈ چلانے کے لیے `sudo` استعمال کرنے کی ضرورت ہو سکتی ہے۔

    کنٹینر کو کنٹینر رجسٹری میں دھکیل دیا جائے گا۔

    ```output
    ➜  d4ccc45da0bb478bad287128e1274c3c.DockerFile.Linux docker push fruitqualitydetectorjimb.azurecr.io/classifier:v1
    The push refers to repository [fruitqualitydetectorjimb.azurecr.io/classifier]
    5f70bf18a086: Pushed 
    8a1ba9294a22: Pushed 
    56cf27184a76: Pushed 
    b32154f3f5dd: Pushed 
    36103e9a3104: Pushed 
    e2abb3cacca0: Pushed 
    4213fd357bbe: Pushed 
    7ea163ba4dce: Pushed 
    537313a13d90: Pushed 
    764055ebc9a7: Pushed 
    v1: digest: sha256:ea7894652e610de83a5a9e429618e763b8904284253f4fa0c9f65f0df3a5ded8 size: 2423
    ```

1. دھکیلنے کی تصدیق کرنے کے لیے، آپ درج ذیل کمانڈ کے ساتھ اپنی رجسٹری میں کنٹینرز کی فہرست دیکھ سکتے ہیں:

    ```sh
    az acr repository list --output table \
                           --name <Container registry name> 
    ```

    `<Container registry name>` کو اپنے کنٹینر رجسٹری کے نام سے تبدیل کریں۔

    ```output
    ➜  d4ccc45da0bb478bad287128e1274c3c.DockerFile.Linux az acr repository list --name fruitqualitydetectorjimb --output table
    Result
    ----------
    classifier
    ```

    آپ اپنی classifier کو آؤٹ پٹ میں درج دیکھیں گے۔

## اپنے کنٹینر کو تعینات کریں

آپ کا کنٹینر اب آپ کے IoT Edge ڈیوائس پر تعینات کیا جا سکتا ہے۔ تعینات کرنے کے لیے آپ کو ایک deployment manifest کی وضاحت کرنی ہوگی - ایک JSON دستاویز جو edge device پر تعینات کیے جانے والے modules کی فہرست دیتی ہے۔

### کام - deployment manifest بنائیں

1. اپنے کمپیوٹر پر کہیں ایک نئی فائل بنائیں جس کا نام `deployment.json` ہو۔

1. اس فائل میں درج ذیل شامل کریں:

    ```json
    {
        "content": {
            "modulesContent": {
                "$edgeAgent": {
                    "properties.desired": {
                        "schemaVersion": "1.1",
                        "runtime": {
                            "type": "docker",
                            "settings": {
                                "minDockerVersion": "v1.25",
                                "loggingOptions": "",
                                "registryCredentials": {
                                    "ClassifierRegistry": {
                                        "username": "<Container registry name>",
                                        "password": "<Container registry password>",
                                        "address": "<Container registry name>.azurecr.io"
                                      }
                                }
                            }
                        },
                        "systemModules": {
                            "edgeAgent": {
                                "type": "docker",
                                "settings": {
                                    "image": "mcr.microsoft.com/azureiotedge-agent:1.1",
                                    "createOptions": "{}"
                                }
                            },
                            "edgeHub": {
                                "type": "docker",
                                "status": "running",
                                "restartPolicy": "always",
                                "settings": {
                                    "image": "mcr.microsoft.com/azureiotedge-hub:1.1",
                                    "createOptions": "{\"HostConfig\":{\"PortBindings\":{\"5671/tcp\":[{\"HostPort\":\"5671\"}],\"8883/tcp\":[{\"HostPort\":\"8883\"}],\"443/tcp\":[{\"HostPort\":\"443\"}]}}}"
                                }
                            }
                        },
                        "modules": {
                            "ImageClassifier": {
                                "version": "1.0",
                                "type": "docker",
                                "status": "running",
                                "restartPolicy": "always",
                                "settings": {
                                    "image": "<Container registry name>.azurecr.io/classifier:v1",
                                    "createOptions": "{\"ExposedPorts\": {\"80/tcp\": {}},\"HostConfig\": {\"PortBindings\": {\"80/tcp\": [{\"HostPort\": \"80\"}]}}}"
                                }
                            }
                        }
                    }
                },
                "$edgeHub": {
                    "properties.desired": {
                        "schemaVersion": "1.1",
                        "routes": {
                            "upstream": "FROM /messages/* INTO $upstream"
                        },
                        "storeAndForwardConfiguration": {
                            "timeToLiveSecs": 7200
                        }
                    }
                }
            }
        }
    }
    ```

    > 💁 آپ اس فائل کو [code-deployment/deployment](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-deployment/deployment) فولڈر میں تلاش کر سکتے ہیں۔

    `<Container registry name>` کے تین instances کو اپنے کنٹینر رجسٹری کے نام سے تبدیل کریں۔ ایک `ImageClassifier` module سیکشن میں ہے، اور دیگر دو `registryCredentials` سیکشن میں ہیں۔

    `registryCredentials` سیکشن میں `<Container registry password>` کو اپنے کنٹینر رجسٹری پاس ورڈ سے تبدیل کریں۔

1. اپنی deployment manifest کو شامل کرنے والے فولڈر سے درج ذیل کمانڈ چلائیں:

    ```sh
    az iot edge set-modules --device-id fruit-quality-detector-edge \
                            --content deployment.json \
                            --hub-name <hub_name>
    ```

    `<hub_name>` کو اپنے IoT Hub کے نام سے تبدیل کریں۔

    امیج classifier module آپ کے edge device پر تعینات کیا جائے گا۔

### کام - classifier کے چلنے کی تصدیق کریں

1. IoT edge device سے جڑیں:

    * اگر آپ Raspberry Pi کا استعمال کرتے ہوئے IoT Edge چلا رہے ہیں، تو ssh کے ذریعے اپنے ٹرمینل سے جڑیں، یا VS Code میں ایک remote SSH سیشن کے ذریعے جڑیں۔
    * اگر آپ IoT Edge کو لینکس کنٹینر میں ونڈوز پر چلا رہے ہیں، تو [verify successful configuration guide](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge-on-windows?WT.mc_id=academic-17441-jabenn&view=iotedge-2018-06&tabs=powershell#verify-successful-configuration) میں دیے گئے مراحل پر عمل کریں تاکہ IoT Edge ڈیوائس سے جڑ سکیں۔
    * اگر آپ IoT Edge کو ورچوئل مشین پر چلا رہے ہیں، تو آپ مشین میں ssh کر سکتے ہیں، `adminUsername` اور `password` کا استعمال کرتے ہوئے جو آپ نے VM بناتے وقت سیٹ کیا تھا، اور IP ایڈریس یا DNS نام کا استعمال کرتے ہوئے:

        ```sh
        ssh <adminUsername>@<IP address>
        ```

        یا:

        ```sh
        ssh <adminUsername>@<DNS Name>
        ```

        جب پاس ورڈ پوچھا جائے تو اسے درج کریں۔

1. ایک بار جب آپ جڑ جائیں، تو IoT Edge modules کی فہرست حاصل کرنے کے لیے درج ذیل کمانڈ چلائیں:

    ```sh
    iotedge list
    ```

    > 💁 آپ کو یہ کمانڈ `sudo` کے ساتھ چلانے کی ضرورت ہو سکتی ہے۔

    آپ چلنے والے modules دیکھیں گے:

    ```output
    jim@fruit-quality-detector-jimb:~$ iotedge list
    NAME             STATUS           DESCRIPTION      CONFIG
    ImageClassifier  running          Up 42 minutes    fruitqualitydetectorjimb.azurecr.io/classifier:v1
    edgeAgent        running          Up 42 minutes    mcr.microsoft.com/azureiotedge-agent:1.1
    edgeHub          running          Up 42 minutes    mcr.microsoft.com/azureiotedge-hub:1.1
    ```

1. Image classifier module کے logs چیک کریں درج ذیل کمانڈ کے ساتھ:

    ```sh
    iotedge logs ImageClassifier
    ```

    > 💁 آپ کو یہ کمانڈ `sudo` کے ساتھ چلانے کی ضرورت ہو سکتی ہے۔

    ```output
    jim@fruit-quality-detector-jimb:~$ iotedge logs ImageClassifier
    2021-07-05 20:30:15.387144: I tensorflow/core/platform/cpu_feature_guard.cc:142] Your CPU supports instructions that this TensorFlow binary was not compiled to use: AVX2 FMA
    2021-07-05 20:30:15.392185: I tensorflow/core/platform/profile_utils/cpu_utils.cc:94] CPU Frequency: 2394450000 Hz
    2021-07-05 20:30:15.392712: I tensorflow/compiler/xla/service/service.cc:168] XLA service 0x55ed9ac83470 executing computations on platform Host. Devices:
    2021-07-05 20:30:15.392806: I tensorflow/compiler/xla/service/service.cc:175]   StreamExecutor device (0): Host, Default Version
    Loading model...Success!
    Loading labels...2 found. Success!
     * Serving Flask app "app" (lazy loading)
     * Environment: production
       WARNING: This is a development server. Do not use it in a production deployment.
       Use a production WSGI server instead.
     * Debug mode: off
     * Running on http://0.0.0.0:80/ (Press CTRL+C to quit)
    ```

### کام - image classifier کو ٹیسٹ کریں

1. آپ CURL کا استعمال کرتے ہوئے image classifier کو IoT Edge agent چلانے والے کمپیوٹر کے IP ایڈریس یا host name کے ذریعے ٹیسٹ کر سکتے ہیں۔ IP ایڈریس تلاش کریں:

    * اگر آپ اسی مشین پر ہیں جس پر IoT Edge چل رہا ہے، تو آپ `localhost` کو host name کے طور پر استعمال کر سکتے ہیں۔
    * اگر آپ VM استعمال کر رہے ہیں، تو آپ VM کے IP ایڈریس یا DNS نام کو استعمال کر سکتے ہیں۔
    * ورنہ آپ IoT Edge چلانے والے کمپیوٹر کا IP ایڈریس حاصل کر سکتے ہیں:
      * ونڈوز 10 پر، [find your IP address guide](https://support.microsoft.com/windows/find-your-ip-address-f21a9bbc-c582-55cd-35e0-73431160a1b9?WT.mc_id=academic-17441-jabenn) پر عمل کریں۔
      * macOS پر، [how to find you IP address on a Mac guide](https://www.hellotech.com/guide/for/how-to-find-ip-address-on-mac) پر عمل کریں۔
      * لینکس پر، [how to find your IP address in Linux guide](https://opensource.com/article/18/5/how-find-ip-address-linux) میں private IP ایڈریس تلاش کرنے کے سیکشن پر عمل کریں۔

1. آپ درج ذیل curl کمانڈ چلا کر کنٹینر کو ایک لوکل فائل کے ساتھ ٹیسٹ کر سکتے ہیں:

    ```sh
    curl --location \
         --request POST 'http://<IP address or name>/image' \
         --header 'Content-Type: image/png' \
         --data-binary '@<file_Name>' 
    ```

    `<IP address or name>` کو IoT Edge چلانے والے کمپیوٹر کے IP ایڈریس یا host name سے تبدیل کریں۔ `<file_Name>` کو ٹیسٹ کرنے کے لیے فائل کے نام سے تبدیل کریں۔

    آپ آؤٹ پٹ میں prediction results دیکھیں گے:

    ```output
    {
        "created": "2021-07-05T21:44:39.573181",
        "id": "",
        "iteration": "",
        "predictions": [
            {
                "boundingBox": null,
                "probability": 0.9995615482330322,
                "tagId": "",
                "tagName": "ripe"
            },
            {
                "boundingBox": null,
                "probability": 0.0004384400090202689,
                "tagId": "",
                "tagName": "unripe"
            }
        ],
        "project": ""
    }
    ```

    > 💁 یہاں prediction key فراہم کرنے کی ضرورت نہیں ہے، کیونکہ یہ Azure resource استعمال نہیں کر رہا ہے۔ اس کے بجائے سیکیورٹی کو اندرونی نیٹ ورک پر اندرونی سیکیورٹی ضروریات کے مطابق کنفیگر کیا جائے گا، بجائے اس کے کہ ایک public endpoint اور API key پر انحصار کیا جائے۔

## اپنے IoT Edge ڈیوائس کا استعمال کریں

اب جب کہ آپ کا Image Classifier IoT Edge ڈیوائس پر تعینات ہو گیا ہے، آپ اسے اپنے IoT ڈیوائس سے استعمال کر سکتے ہیں۔

### کام - اپنے IoT Edge ڈیوائس کا استعمال کریں

IoT Edge classifier کا استعمال کرتے ہوئے تصاویر کو classify کرنے کے لیے متعلقہ گائیڈ پر عمل کریں:

* [Arduino - Wio Terminal](wio-terminal.md)
* [Single-board computer - Raspberry Pi/Virtual IoT device](single-board-computer.md)

### ماڈل کی دوبارہ تربیت

IoT Edge پر چلنے والے image classifiers کے ایک نقصانات میں سے ایک یہ ہے کہ وہ آپ کے Custom Vision پروجیکٹ سے منسلک نہیں ہیں۔ اگر آپ Custom Vision میں **Predictions** ٹیب کو دیکھیں گے تو آپ کو وہ تصاویر نظر نہیں آئیں گی جو Edge-based classifier کا استعمال کرتے ہوئے classify کی گئی تھیں۔

یہ متوقع رویہ ہے - تصاویر کو classification کے لیے کلاؤڈ میں نہیں بھیجا جاتا، لہذا وہ کلاؤڈ میں دستیاب نہیں ہوں گی۔ IoT Edge کا استعمال کرنے کے فوائد میں سے ایک پرائیویسی ہے، یہ یقینی بنانا کہ تصاویر آپ کے نیٹ ورک سے باہر نہ جائیں، دوسرا آف لائن کام کرنے کی صلاحیت ہے، لہذا جب ڈیوائس کے پاس انٹرنیٹ کنکشن نہ ہو تو تصاویر اپ لوڈ کرنے پر انحصار نہ کریں۔ نقصان ماڈل کو بہتر بنانا ہے - آپ کو تصاویر کو دستی طور پر دوبارہ classify کرنے کے لیے ذخیرہ کرنے کا دوسرا طریقہ نافذ کرنا ہوگا تاکہ image classifier کو بہتر بنایا جا سکے اور دوبارہ تربیت دی جا سکے۔

✅ classifier کو دوبارہ تربیت دینے کے لیے تصاویر اپ لوڈ کرنے کے طریقوں کے بارے میں سوچیں۔

---

## 🚀 چیلنج

Edge devices پر AI ماڈلز چلانا کلاؤڈ کے مقابلے میں تیز ہو سکتا ہے - نیٹ ورک hop چھوٹا ہوتا ہے۔ یہ سست بھی ہو سکتے ہیں کیونکہ ماڈل چلانے والا ہارڈویئر کلاؤڈ کے مقابلے میں اتنا طاقتور نہیں ہو سکتا۔

کچھ timings کریں اور موازنہ کریں کہ آیا آپ کے edge device پر کال کلاؤڈ پر کال کے مقابلے میں تیز یا سست ہے؟ فرق کی وضاحت کرنے کے لیے وجوہات کے بارے میں سوچیں، یا فرق کی کمی کی وضاحت کریں۔ Edge پر AI ماڈلز کو تیز تر چلانے کے طریقوں پر تحقیق کریں، خاص طور پر specialized hardware کا استعمال کرتے ہوئے۔

## لیکچر کے بعد کوئز

[لیکچر کے بعد کوئز](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/34)

## جائزہ اور خود مطالعہ

* کنٹینرز کے بارے میں مزید پڑھیں [OS-level virtualization page on Wikipedia](https://wikipedia.org/wiki/OS-level_virtualization) پر۔
* ایج کمپیوٹنگ کے بارے میں مزید پڑھیں، خاص طور پر یہ کہ 5G ایج کمپیوٹنگ کو کیسے بڑھا سکتا ہے، [ایج کمپیوٹنگ کیا ہے اور یہ کیوں اہم ہے؟ نیٹ ورک ورلڈ کے آرٹیکل](https://www.networkworld.com/article/3224893/what-is-edge-computing-and-how-its-changing-the-network.html) میں۔

* IoT Edge میں AI سروسز چلانے کے بارے میں مزید جانیں، [ایج پر پہلے سے تیار شدہ AI سروس کو استعمال کرتے ہوئے زبان کی شناخت کرنے کے لیے Azure IoT Edge استعمال کرنے کا طریقہ سیکھیں، Microsoft Channel9 پر Learn Live کے ایپیسوڈ](https://channel9.msdn.com/Shows/Learn-Live/Sharpen-Your-AI-Edge-Skills-Episode-4-Learn-How-to-Use-Azure-IoT-Edge-on-a-Pre-Built-AI-Service-on-t?WT.mc_id=academic-17441-jabenn) دیکھ کر۔

## اسائنمنٹ

[ایج پر دیگر سروسز چلائیں](assignment.md)

---

**ڈسکلیمر**:  
یہ دستاویز AI ترجمہ سروس [Co-op Translator](https://github.com/Azure/co-op-translator) کا استعمال کرتے ہوئے ترجمہ کی گئی ہے۔ ہم درستگی کے لیے کوشش کرتے ہیں، لیکن براہ کرم آگاہ رہیں کہ خودکار ترجمے میں غلطیاں یا غیر درستیاں ہو سکتی ہیں۔ اصل دستاویز کو اس کی اصل زبان میں مستند ذریعہ سمجھا جانا چاہیے۔ اہم معلومات کے لیے، پیشہ ور انسانی ترجمہ کی سفارش کی جاتی ہے۔ ہم اس ترجمے کے استعمال سے پیدا ہونے والی کسی بھی غلط فہمی یا غلط تشریح کے ذمہ دار نہیں ہیں۔