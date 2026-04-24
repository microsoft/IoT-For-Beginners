### ازور AI Foundry کمیونٹی میں شامل ہوں

اگر آپ AI ایپس بنانے کے دوران پھنس جاتے ہیں یا کوئی سوالات ہیں، تو MCP کے بارے میں بات چیت میں ساتھی سیکھنے والوں اور تجربہ کار ڈیویلپرز سے رابطہ کریں۔ یہ ایک معاون کمیونٹی ہے جہاں سوالات کا خیرمقدم کیا جاتا ہے اور علم کو آزادانہ طور پر شیئر کیا جاتا ہے۔

اگر آپ کے پاس پروڈکٹ کے بارے میں تاثرات یا غلطیاں ہیں تو:

ان وسائل کو استعمال کرنے کے لیے یہ اقدامات کریں:  
1. **ریپوزیٹری فورک کریں**: کلک کریں  
2. **ریپوزیٹری کلون کریں**: `git clone https://github.com/microsoft/IoT-For-Beginners.git`  
3. **مائیکروسافٹ Foundry Discord میں شامل ہوں اور ماہرین و ساتھی ڈیویلپرز سے ملیں**  

### 🌐 متعدد زبانوں کی حمایت

#### گِٹ ہب ایکشن کے ذریعے سپورٹ کی جاتی ہے (خودکار اور ہمیشہ تازہ ترین)

# IoT برائے شروعاتی - ایک نصاب

مائیکروسافٹ کے ازور کلاؤڈ عہدیدار 12 ہفتوں پر محیط، 24 اسباق پر مشتمل ایک نصاب پیش کرتے ہیں جو IoT کی بنیادی باتوں کے بارے میں ہے۔ ہر سبق میں قبل اور بعد کی کوئزز، سبق مکمل کرنے کی تحریری ہدایات، حل، اسائنمنٹ اور مزید شامل ہیں۔ ہمارا پروجیکٹ پر مبنی طریقہء تعلیم آپ کو تعمیر کے دوران سیکھنے کا موقع دیتا ہے، جو نئے ہنر سیکھنے کا ایک مؤثر طریقہ ہے۔

یہ پروجیکٹس کھانے کے سفر کو کھیت سے دسترخوان تک کور کرتے ہیں۔ اس میں زراعت، لاجسٹکس، مینوفیکچرنگ، ریٹیل اور صارف شامل ہیں — یہ سب IoT ڈیوائسز کے لیے معروف صنعتیں ہیں۔

**ہمارے مصنفین [Jen Fox]، [Jen Looper]، [Jim Bennett] اور ہمارے اسکیچنوٹ آرٹسٹ [Nitya Narasimhan] کا شکریہ۔**

**اسی طرح ہمارے [Microsoft Learn Student Ambassadors] کی ٹیم کا بھی شکریہ جنہوں نے اس نصاب کا جائزہ لیا اور اس کا ترجمہ کیا — [Aditya Garg]، [Anurag Sharma]، [Arpita Das]، [Aryan Jain]، [Bhavesh Suneja]، [Faith Hunja]، [Lateefah Bello]، [Manvi Jha]، [Mireille Tan]، [Mohammad Iftekher (Iftu) Ebne Jalal]، [Mohammad Zulfikar]، [Priyanshu Srivastav]، [Thanmai Gowducheruvu]، اور [Zina Kamel]۔**

ٹیم سے ملیں!

> 🎥 پراجیکٹ کے بارے میں ویڈیو دیکھنے کے لیے اوپر دی گئی تصویر پر کلک کریں!

> **اساتذہ**، ہم نے [یہاں کچھ تجاویز شامل کی ہیں](for-teachers.md) کہ نصاب کو کیسے استعمال کیا جائے۔ اگر آپ اپنے اسباق خود بنانا چاہتے ہیں تو ہم نے [سبق کے ٹیمپلیٹ](lesson-template/README.md) بھی فراہم کیے ہیں۔

> **[طلباء](https://aka.ms/student-page)**، اس نصاب کو خود استعمال کرنے کے لیے، پوری ریپو کو فورک کریں اور مشقیں خود مکمل کریں، شروع کریں قبل از لیکچر کوئز سے، پھر لیکچر پڑھیں اور باقی سرگرمیاں کریں۔ کوشش کریں کہ پروجیکٹس کی تخلیق سبق کو سمجھ کر کریں نہ کہ حل کا کوڈ صرف نقل کریں؛ یہ کوڈ ہر پروجیکٹ پر مبنی سبق کے /solutions فولڈر میں دستیاب ہے۔ ایک اور خیال یہ ہے کہ ایک مطالعے کا گروپ بنائیں اور مواد ایک ساتھ پڑھیں۔ مزید مطالعے کے لیے ہم [Microsoft Learn] کی سفارش کرتے ہیں۔

## تعلیم کا طریقہ کار

ہم نے اس نصاب کی تشکیل میں دو بنیادی اصول اپنائے ہیں: اسے پروجیکٹ پر مبنی بنانا اور بار بار کوئزز شامل کرنا۔ اس سلسلے کے اختتام تک، طلباء ایک پودے کی نگرانی اور پانی دینے کا نظام، ایک گاڑی ٹریکر، خوراک چیک کرنے والی اسمارٹ فیکٹری، اور آواز سے کنٹرول ہونے والا ککنگ ٹائمر بنا چکے ہوں گے، اور IoT کی بنیادی باتیں جان جائیں گے جیسے ڈیوائس کوڈ لکھنا، کلاؤڈ سے کنکٹ ہونا، ٹیلی میٹری کا تجزیہ کرنا اور ایج پر AI چلانا۔

پروجیکٹ کے مطابق مواد طلباء کے لیے زیادہ پرکشش اور یاد رہنے کے قابل بناتا ہے۔

اس کے علاوہ، کلاس سے پہلے ایک کم اہمیت کی کوئز طلباء کو موضوع سیکھنے کے جذبے میں لاتی ہے، اور کلاس کے بعد ایک اور کوئز معلومات کو مزید یاد رہنے میں مدد دیتا ہے۔ یہ نصاب لچکدار اور مزیدار ہے اور پورے یا جزوی طور پر پڑھا جا سکتا ہے۔ پروجیکٹس چھوٹے سے شروع ہوکر 12 ہفتوں کے اختتام تک پیچیدہ ہوتے جاتے ہیں۔

ہر پروجیکٹ حقیقی دنیا کی ہارڈویئر پر مبنی ہے جو طلباء اور شوقین حضرات کے لیے دستیاب ہے۔ ہر پروجیکٹ مخصوص دائرہ کار کو دیکھتا ہے اور متعلقہ پس منظر کا علم فراہم کرتا ہے۔ ایک کامیاب ڈیولپر بننے کے لیے یہ سمجھنا فائدہ مند ہے کہ آپ جس دائرہ کار میں مسئلہ حل کر رہے ہیں، وہ کیا ہے، اور پس منظر کا علم طلباء کو اپنے IoT حل اور سیکھنے کو حقیقی دنیا کے مسائل کے تناظر میں سوچنے میں مدد دیتا ہے۔ طلباء وہ 'کیوں' سیکھتے ہیں جو وہ بنا رہے ہیں، اور آخری صارف کی قدردانی حاصل کرتے ہیں۔

## ہارڈویئر
ہمارے پاس پروجیکٹس کے لیے دو قسم کی IoT ہارڈویئر استعمال کرنے کے انتخاب موجود ہیں جو ذاتی پسند، پروگرامنگ زبان کی معلومات یا ترجیحات، سیکھنے کے مقاصد اور دستیابی پر منحصر ہیں۔ ہم نے ان لوگوں کے لیے 'ورچوئل ہارڈویئر' ورژن بھی فراہم کیا ہے جن کے پاس ہارڈویئر تک رسائی نہیں ہے، یا وہ خریداری سے پہلے مزید سیکھنا چاہتے ہیں۔ آپ مزید پڑھ سکتے ہیں اور [ہارڈویئر صفحہ](./hardware.md) پر 'خریداری کی فہرست' بھی حاصل کر سکتے ہیں، جس میں ہمارے دوست Seeed Studio سے مکمل کٹس خریدنے کے لنکس بھی شامل ہیں۔

> 💁 ہمارے [کوڈ آف کنڈکٹ](CODE_OF_CONDUCT.md)، [تعاون](CONTRIBUTING.md)، اور [ترجمے](..) کے رہنما خطوط دریافت کریں۔ ہم آپ کی تعمیری رائے کے خیرمقدم کرتے ہیں!
>
> 🔧 مسائل درپیش ہیں؟ عام مشکلات کے حل کے لیے ہمارا [مسائل حل کرنے کی گائیڈ](TROUBLESHOOTING.md) ملاحظہ کریں۔

## ہر سبق میں شامل ہیں:

- سکیچ نوٹ  
- اختیاری اضافی ویڈیو  
- پیشگی سبق کا وارم اپ کوئز  
- تحریری سبق  
- پروجیکٹ بیسڈ اسباق کے لیے منصوبے کے بنانے کے مرحلہ وار رہنما  
- معلومات کی جانچ  
- ایک چیلنج  
- اضافی مطالعہ  
- اسباق کے بعد کوئز [post-lesson quiz](https://ff-quizzes.netlify.app/en/)

> **کوئزز کے بارے میں ایک نوٹ**: تمام کوئزز کوئز-ایپ فولڈر میں شامل ہیں، جن میں کل 48 کوئزز ہیں، ہر ایک میں تین سوالات۔ یہ اسباق کے اندر سے لنک کیے گئے ہیں لیکن کوئز ایپ کو مقامی طور پر چلایا جا سکتا ہے یا Azure پر تعینات کیا جا سکتا ہے؛ `quiz-app` فولڈر میں ہدایات پر عمل کریں۔ انہیں بتدریج مقامی زبانوں میں تبدیل کیا جا رہا ہے۔

## اسباق

|       |              پروجیکٹ کا نام                  |                       سکھائے گئے تصورات                        | تعلیمی مقاصد                                                                                                                                                          |                                                        متعلقہ سبق                                                        |
| :---: | :------------------------------------------: | :------------------------------------------------------------: | --------------------------------------------------------------------------------------------------------------------------------------------------------------------- | :---------------------------------------------------------------------------------------------------------------------: |
|  01   | [شروع کرنا](./1-getting-started/README.md) |                     IoT کا تعارف                             | IoT کے بنیادی اصول سیکھیں اور IoT حل کے بنیادی اجزاء جیسے سینسرز اور کلاؤڈ سروسز کو جانیں جبکہ آپ اپنا پہلا IoT ڈیوائس سیٹ کر رہے ہوں                            |                      [IoT کا تعارف](./1-getting-started/lessons/1-introduction-to-iot/README.md)                      |
|  02   | [شروع کرنا](./1-getting-started/README.md) |                   IoT میں گہری نظر                          | IoT سسٹم کے اجزاء، مائیکروکنٹرولرز اور سنگل بورڈ کمپیوٹرز کے بارے میں مزید جانیں                                                                                     |                        [IoT میں گہری نظر](./1-getting-started/lessons/2-deeper-dive/README.md)                         |
|  03   | [شروع کرنا](./1-getting-started/README.md) | سینسرز اور ایکچیویٹرز کے ساتھ جسمانی دنیا کے ساتھ تعامل      | جسمانی دنیا سے ڈیٹا اکٹھا کرنے کے لیے سینسرز اور فیڈ بیک بھیجنے کے لیے ایکٹیویٹرز کے بارے میں جانیں، جبکہ آپ ایک نائٹ لائٹ بنا رہے ہوں                             | [سینسرز اور ایکچیویٹرز کے ساتھ جسمانی دنیا کے ساتھ تعامل](./1-getting-started/lessons/3-sensors-and-actuators/README.md) |
|  04   | [شروع کرنا](./1-getting-started/README.md) |             اپنے ڈیوائس کو انٹرنیٹ سے جوڑیں                   | IoT ڈیوائس کو انٹرنیٹ سے جوڑنے کے بارے میں جانیں تاکہ پیغامات بھیج سکیں اور وصول کر سکیں، اپنے نائٹ لائٹ کو MQTT بروکر سے جوڑیں                                      |               [اپنے ڈیوائس کو انٹرنیٹ سے جوڑیں](./1-getting-started/lessons/4-connect-internet/README.md)                |
|  05   |            [فارم](./2-farm/README.md)            |                    پودوں کی نمو کی پیشگوئی                     | IoT ڈیوائس کے ذریعے حاصل کیے گئے درجہ حرارت کے ڈیٹا کی مدد سے پودوں کی نمو کی پیشگوئی کرنا سیکھیں                                                                     |                          [پودوں کی نمو کی پیشگوئی](./2-farm/lessons/1-predict-plant-growth/README.md)                           |
|  06   |            [فارم](./2-farm/README.md)            |                    مٹی کی نمی کا پتہ لگانا                     | مٹی کی نمی کا پتہ لگانے کے طریقے اور مٹی کی نمی کے سینسر کی کیلibration کرنا سیکھیں                                                                                   |                          [مٹی کی نمی کا پتہ لگانا](./2-farm/lessons/2-detect-soil-moisture/README.md)                           |
|  07   |            [فارم](./2-farm/README.md)            |                  خودکار پودوں کو پانی دینا                   | ریلے اور MQTT کا استعمال کرتے ہوئے خودکار اور وقت کے مطابق پانی دینے کا طریقہ سیکھیں                                                                                |                      [خودکار پودوں کو پانی دینا](./2-farm/lessons/3-automated-plant-watering/README.md)                       |
|  08   |            [فارم](./2-farm/README.md)            |               اپنے پودے کو کلاؤڈ میں منتقل کرنا               | کلاؤڈ اور کلاؤڈ پر مبنی IoT سروسز کے بارے میں جانیں اور اپنے پودے کو ان میں سے کسی ایک سے جوڑیں بجائے کسی پبلک MQTT بروکر کے                                        |               [اپنے پودے کو کلاؤڈ میں منتقل کریں](./2-farm/lessons/4-migrate-your-plant-to-the-cloud/README.md)                |
|  09   |            [فارم](./2-farm/README.md)            |         اپنی ایپلیکیشن لاجک کو کلاؤڈ میں منتقل کریں           | IoT پیغامات کا جواب دینے کے لیے کلاؤڈ میں ایپلیکیشن لاجک لکھنے کے طریقے جانیں                                                                                        |         [اپنی ایپلیکیشن لاجک کو کلاؤڈ میں منتقل کریں](./2-farm/lessons/5-migrate-application-to-the-cloud/README.md)         |
|  10   |            [فارم](./2-farm/README.md)            |                   اپنے پودے کو محفوظ رکھیں                   | IoT کی سیکورٹی اور اپنی نباتات کو چابیاں اور سرٹیفیکیٹس کے ساتھ محفوظ رکھنے کے طریقے سیکھیں                                                                           |                        [اپنے پودے کو محفوظ رکھیں](./2-farm/lessons/6-keep-your-plant-secure/README.md)                         |
|  11   |       [ٹرانسپورٹ](./3-transport/README.md)       |                      مقام کی نگرانی                          | IoT ڈیوائسز کے لیے GPS مقام کی نگرانی کے بارے میں جانیں                                                                                                              |                           [مقام کی نگرانی](./3-transport/lessons/1-location-tracking/README.md)                           |
|  12   |       [ٹرانسپورٹ](./3-transport/README.md)       |                     مقام کا ڈیٹا محفوظ کریں                   | IoT ڈیٹا کو بعد میں دیکھنے یا تجزیہ کرنے کے لیے محفوظ کرنے کے طریقے جانیں                                                                                            |                         [مقام کا ڈیٹا محفوظ کریں](./3-transport/lessons/2-store-location-data/README.md)                         |
|  13   |       [ٹرانسپورٹ](./3-transport/README.md)       |                   مقام کے ڈیٹا کی بصری شکل بنائیں             | نقشے پر مقام کے ڈیٹا کی نمائش اور نقشے کیسے حقیقی 3D دنیا کی دو جہتی نمائندگی کرتے ہیں کے بارے میں جانیں                                                            |                     [مقام کے ڈیٹا کی بصری شکل](./3-transport/lessons/3-visualize-location-data/README.md)                     |
|  14   |       [ٹرانسپورٹ](./3-transport/README.md)       |                          جیو فینسز                           | جیو فینسز کے بارے میں جانیں، اور یہ کیسے سپلائی چین میں گاڑیوں کے اپنے منزل کے قریب ہونے پر الرٹ کر سکتے ہیں                                                        |                                   [جیو فینسز](./3-transport/lessons/4-geofences/README.md)                                   |
|  15   |   [مینوفیکچرنگ](./4-manufacturing/README.md)   |               پھل کی معیار کا پتہ لگانے والا ٹرین کریں        | کلاؤڈ میں ایک امیج کلاسیفائر ٹرین کرنے کے بارے میں جانیں تاکہ پھل کی معیار کا پتہ لگا سکے                                                                             |                 [پھل کی معیار کا پتہ لگانے والا ٹرین کریں](./4-manufacturing/lessons/1-train-fruit-detector/README.md)                 |
|  16   |   [مینوفیکچرنگ](./4-manufacturing/README.md)   |           IoT ڈیوائس سے پھل کی معیار چیک کریں                | اپنے پھل کی معیار کے پتہ لگانے والے آلے کو IoT ڈیوائس سے استعمال کرنے کے بارے میں جانیں                                                                               |           [IoT ڈیوائس سے پھل کی معیار چیک کریں](./4-manufacturing/lessons/2-check-fruit-from-device/README.md)            |
|  17   |   [مینوفیکچرنگ](./4-manufacturing/README.md)   |             اپنے پھل کی ڈیٹیکٹر کو ایج پر چلائیں               | IoT ڈیوائس پر ایج پر اپنے پھل کی ڈیٹیکٹر کو چلانے کے بارے میں جانیں                                                                                                 |             [اپنے پھل کی ڈیٹیکٹر کو ایج پر چلائیں](./4-manufacturing/lessons/3-run-fruit-detector-edge/README.md)             |
|  18   |   [مینوفیکچرنگ](./4-manufacturing/README.md)   |        سینسر سے پھل کی معیار کی شناخت کو چالو کریں            | سینسر سے پھل کی معیار کی شناخت کو چالو کرنے کے بارے میں جانیں                                                                                                        |        [سینسر سے پھل کی معیار کی شناخت کو چالو کریں](./4-manufacturing/lessons/4-trigger-fruit-detector/README.md)         |
|  19   |          [ریٹیل](./5-retail/README.md)          |                   اسٹاک ڈیٹیکٹر کو تربیت دیں                  | شاپ میں اسٹاک گننے کے لیے آبجیکٹ ڈیٹیکشن کا استعمال کرتے ہوئے اسٹاک ڈیٹیکٹر کو تربیت دیں                                                                               |                        [اسٹاک ڈیٹیکٹر کو تربیت دیں](./5-retail/lessons/1-train-stock-detector/README.md)                         |
|  20   |          [ریٹیل](./5-retail/README.md)          |               IoT ڈیوائس سے اسٹاک چیک کریں                    | آبجیکٹ ڈیٹیکشن ماڈل کا استعمال کرتے ہوئے IoT ڈیوائس سے اسٹاک چیک کرنے کے طریقے جانیں                                                                               |                     [IoT ڈیوائس سے اسٹاک چیک کریں](./5-retail/lessons/2-check-stock-device/README.md)                      |
|  21   |        [کنسومر](./6-consumer/README.md)        |             IoT ڈیوائس سے تقریر کو پہچانیں                    | IoT ڈیوائس سے تقریر کو پہچان کر ایک سمارٹ ٹائمر بنانے کے بارے میں جانیں                                                                                            |                  [IoT ڈیوائس سے تقریر کو پہچانیں](./6-consumer/lessons/1-speech-recognition/README.md)                  |
|  22   |        [کنسومر](./6-consumer/README.md)        |                     زبان کو سمجھیں                          | IoT ڈیوائس کو بولے گئے جملوں کو سمجھنے کے بارے میں جانیں                                                                                                           |                        [زبان کو سمجھیں](./6-consumer/lessons/2-language-understanding/README.md)                        |
|  23   |        [کنسومر](./6-consumer/README.md)        |           ٹائمر سیٹ کریں اور زبانی فیڈ بیک دیں              | IoT ڈیوائس پر ٹائمر سیٹ کرنے اور زبانی فیڈ بیک دینے کا طریقہ سیکھیں کہ کب ٹائمر سیٹ ہے اور کب ختم ہوتا ہے                                                            |                 [ٹائمر سیٹ کریں اور زبانی فیڈ بیک دیں](./6-consumer/lessons/3-spoken-feedback/README.md)                  |
|  24   |        [کنسومر](./6-consumer/README.md)        |                 کئی زبانوں کی حمایت کریں                     | کئی زبانوں کی حمایت کرنا سیکھیں، یعنی بولی جانے والی اور آپ کے سمارٹ ٹائمر کی طرف سے دی گئی جوابات دونوں                                                                |                   [کئی زبانوں کی حمایت کریں](./6-consumer/lessons/4-multiple-language-support/README.md)                   |

## آف لائن رسائی

آپ اس دستاویزات کو [Docsify](https://docsify.js.org/#/) استعمال کرکے آف لائن چلا سکتے ہیں۔ اس ریپو کو فورک کریں، اپنے لوکل مشین پر [Docsify انسٹال کریں](https://docsify.js.org/#/quickstart)، اور پھر اس ریپو کے روٹ فولڈر میں `docsify serve` ٹائپ کریں۔ ویب سائٹ آپ کے لوکل ہوسٹ پر پورٹ 3000 پر دستیاب ہوگی: `localhost:3000`۔

## کوئز

کمیونٹی کا شکریہ جو انٹرایکٹو کوئز کی میزبانی کرتی ہے جو ہر باب پر آپ کے علم کو پرکھتی ہے۔ آپ یہاں اپنا علم آزما سکتے ہیں [here](https://ff-quizzes.netlify.app/en/) 

### پی ڈی ایف

اگر ضرورت ہو تو آپ اس مواد کا پی ڈی ایف بنوا سکتے ہیں تاکہ آف لائن رسائی حاصل ہو سکے۔ ایسا کرنے کے لیے یقینی بنائیں کہ آپ کے پاس [npm انسٹال ہے](https://docs.npmjs.com/downloading-and-installing-node-js-and-npm) اور اس ریپو کے روٹ فولڈر میں درج ذیل کمانڈز چلائیں:

```sh
npm i
npm run convert
```

### سلائیڈز

ناولائے کچھ اسباق کے لیے سلائیڈ ڈیکس [slides](../../slides) فولڈر میں موجود ہیں۔

## دیگر نصاب

ہماری ٹیم دیگر نصاب بھی تیار کرتی ہے! ملاحظہ کریں:

<!-- CO-OP TRANSLATOR OTHER COURSES START -->
### LangChain
[![LangChain4j for Beginners](https://img.shields.io/badge/LangChain4j%20for%20Beginners-22C55E?style=for-the-badge&&labelColor=E5E7EB&color=0553D6)](https://aka.ms/langchain4j-for-beginners)
[![LangChain.js for Beginners](https://img.shields.io/badge/LangChain.js%20for%20Beginners-22C55E?style=for-the-badge&labelColor=E5E7EB&color=0553D6)](https://aka.ms/langchainjs-for-beginners?WT.mc_id=m365-94501-dwahlin)
[![LangChain for Beginners](https://img.shields.io/badge/LangChain%20for%20Beginners-22C55E?style=for-the-badge&labelColor=E5E7EB&color=0553D6)](https://github.com/microsoft/langchain-for-beginners?WT.mc_id=m365-94501-dwahlin)
---

### Azure / Edge / MCP / Agents
[![AZD for Beginners](https://img.shields.io/badge/AZD%20for%20Beginners-0078D4?style=for-the-badge&labelColor=E5E7EB&color=0078D4)](https://github.com/microsoft/AZD-for-beginners?WT.mc_id=academic-105485-koreyst)
[![ابتدائیوں کے لیے ایج AI](https://img.shields.io/badge/Edge%20AI%20for%20Beginners-00B8E4?style=for-the-badge&labelColor=E5E7EB&color=00B8E4)](https://github.com/microsoft/edgeai-for-beginners?WT.mc_id=academic-105485-koreyst)
[![ابتدائیوں کے لیے MCP](https://img.shields.io/badge/MCP%20for%20Beginners-009688?style=for-the-badge&labelColor=E5E7EB&color=009688)](https://github.com/microsoft/mcp-for-beginners?WT.mc_id=academic-105485-koreyst)
[![ابتدائیوں کے لیے AI ایجنٹس](https://img.shields.io/badge/AI%20Agents%20for%20Beginners-00C49A?style=for-the-badge&labelColor=E5E7EB&color=00C49A)](https://github.com/microsoft/ai-agents-for-beginners?WT.mc_id=academic-105485-koreyst)

---

### جنریٹو AI سیریز
[![ابتدائیوں کے لیے جنریٹو AI](https://img.shields.io/badge/Generative%20AI%20for%20Beginners-8B5CF6?style=for-the-badge&labelColor=E5E7EB&color=8B5CF6)](https://github.com/microsoft/generative-ai-for-beginners?WT.mc_id=academic-105485-koreyst)
[![جنریٹو AI (.NET)](https://img.shields.io/badge/Generative%20AI%20(.NET)-9333EA?style=for-the-badge&labelColor=E5E7EB&color=9333EA)](https://github.com/microsoft/Generative-AI-for-beginners-dotnet?WT.mc_id=academic-105485-koreyst)
[![جنریٹو AI (جاوا)](https://img.shields.io/badge/Generative%20AI%20(Java)-C084FC?style=for-the-badge&labelColor=E5E7EB&color=C084FC)](https://github.com/microsoft/generative-ai-for-beginners-java?WT.mc_id=academic-105485-koreyst)
[![جنریٹو AI (جاوا سکرپٹ)](https://img.shields.io/badge/Generative%20AI%20(JavaScript)-E879F9?style=for-the-badge&labelColor=E5E7EB&color=E879F9)](https://github.com/microsoft/generative-ai-with-javascript?WT.mc_id=academic-105485-koreyst)

---

### بنیادی تعلیم
[![ابتدائیوں کے لیے مشین لرننگ](https://img.shields.io/badge/ML%20for%20Beginners-22C55E?style=for-the-badge&labelColor=E5E7EB&color=22C55E)](https://aka.ms/ml-beginners?WT.mc_id=academic-105485-koreyst)
[![ابتدائیوں کے لیے ڈیٹا سائنس](https://img.shields.io/badge/Data%20Science%20for%20Beginners-84CC16?style=for-the-badge&labelColor=E5E7EB&color=84CC16)](https://aka.ms/datascience-beginners?WT.mc_id=academic-105485-koreyst)
[![ابتدائیوں کے لیے AI](https://img.shields.io/badge/AI%20for%20Beginners-A3E635?style=for-the-badge&labelColor=E5E7EB&color=A3E635)](https://aka.ms/ai-beginners?WT.mc_id=academic-105485-koreyst)
[![ابتدائیوں کے لیے سائبرسیکیورٹی](https://img.shields.io/badge/Cybersecurity%20for%20Beginners-F97316?style=for-the-badge&labelColor=E5E7EB&color=F97316)](https://github.com/microsoft/Security-101?WT.mc_id=academic-96948-sayoung)
[![ابتدائیوں کے لیے ویب ڈیولپمنٹ](https://img.shields.io/badge/Web%20Dev%20for%20Beginners-EC4899?style=for-the-badge&labelColor=E5E7EB&color=EC4899)](https://aka.ms/webdev-beginners?WT.mc_id=academic-105485-koreyst)
[![ابتدائیوں کے لیے IoT](https://img.shields.io/badge/IoT%20for%20Beginners-14B8A6?style=for-the-badge&labelColor=E5E7EB&color=14B8A6)](https://aka.ms/iot-beginners?WT.mc_id=academic-105485-koreyst)
[![ابتدائیوں کے لیے XR ڈیولپمنٹ](https://img.shields.io/badge/XR%20Development%20for%20Beginners-38BDF8?style=for-the-badge&labelColor=E5E7EB&color=38BDF8)](https://github.com/microsoft/xr-development-for-beginners?WT.mc_id=academic-105485-koreyst)

---

### کوپائلٹ سیریز
[![AI پئیرڈ پروگرامنگ کے لیے کوپائلٹ](https://img.shields.io/badge/Copilot%20for%20AI%20Paired%20Programming-FACC15?style=for-the-badge&labelColor=E5E7EB&color=FACC15)](https://aka.ms/GitHubCopilotAI?WT.mc_id=academic-105485-koreyst)
[![C#/.NET کے لیے کوپائلٹ](https://img.shields.io/badge/Copilot%20for%20C%23/.NET-FBBF24?style=for-the-badge&labelColor=E5E7EB&color=FBBF24)](https://github.com/microsoft/mastering-github-copilot-for-dotnet-csharp-developers?WT.mc_id=academic-105485-koreyst)
[![کوپائلٹ ایڈونچر](https://img.shields.io/badge/Copilot%20Adventure-FDE68A?style=for-the-badge&labelColor=E5E7EB&color=FDE68A)](https://github.com/microsoft/CopilotAdventures?WT.mc_id=academic-105485-koreyst)
<!-- CO-OP TRANSLATOR OTHER COURSES END -->

## تصویری حوالے

آپ اس نصاب میں استعمال ہونے والی تمام تصاویر کے حوالے [Attributions](./attributions.md) میں جہاں ضروری ہوں وہاں تلاش کر سکتے ہیں۔

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**معذرت**:
اس دستاویز کا ترجمہ AI ترجمہ سروس [Co-op Translator](https://github.com/Azure/co-op-translator) کا استعمال کرتے ہوئے کیا گیا ہے۔ اگرچہ ہم درستگی کے لئے کوشاں ہیں، براہ کرم آگاہ رہیں کہ خودکار تراجم میں غلطیاں یا ناقصیاں ہو سکتی ہیں۔ اصل دستاویز اپنی مادری زبان میں معتبر ماخذ سمجھی جانی چاہئے۔ اہم معلومات کے لیے، پیشہ ور انسانی ترجمہ کی سفارش کی جاتی ہے۔ ہم اس ترجمہ کے استعمال سے پیدا ہونے والی کسی بھی غلط فہمی یا غلط تفہیم کے لیے ذمہ دار نہیں ہیں۔
<!-- CO-OP TRANSLATOR DISCLAIMER END -->