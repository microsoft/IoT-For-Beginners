<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3dce18fab38adf93ff30b8c221b1eec5",
  "translation_date": "2025-08-26T21:25:49+00:00",
  "source_file": "hardware.md",
  "language_code": "ur"
}
-->
# ہارڈویئر

IoT میں **T** کا مطلب **چیزیں** ہے، اور یہ ان آلات کی طرف اشارہ کرتا ہے جو ہمارے ارد گرد کی دنیا کے ساتھ تعامل کرتے ہیں۔ ہر پروجیکٹ حقیقی دنیا کے ہارڈویئر پر مبنی ہے جو طلباء اور شوقین افراد کے لیے دستیاب ہے۔ ہمارے پاس IoT ہارڈویئر کے دو انتخاب ہیں، جو ذاتی ترجیحات، پروگرامنگ زبان کے علم یا ترجیحات، سیکھنے کے اہداف اور دستیابی پر منحصر ہیں۔ ہم نے ان لوگوں کے لیے 'ورچوئل ہارڈویئر' ورژن بھی فراہم کیا ہے جن کے پاس ہارڈویئر تک رسائی نہیں ہے یا جو خریداری سے پہلے مزید سیکھنا چاہتے ہیں۔

> 💁 آپ کو اسائنمنٹس مکمل کرنے کے لیے کوئی IoT ہارڈویئر خریدنے کی ضرورت نہیں ہے۔ آپ سب کچھ ورچوئل IoT ہارڈویئر کے ذریعے کر سکتے ہیں۔

فزیکل ہارڈویئر کے انتخاب میں Arduino یا Raspberry Pi شامل ہیں۔ ہر پلیٹ فارم کے اپنے فوائد اور نقصانات ہیں، اور یہ سب ابتدائی اسباق میں شامل کیے گئے ہیں۔ اگر آپ نے ابھی تک ہارڈویئر پلیٹ فارم کا انتخاب نہیں کیا ہے، تو آپ [پہلے پروجیکٹ کے دوسرے سبق](./1-getting-started/lessons/2-deeper-dive/README.md) کا جائزہ لے سکتے ہیں تاکہ یہ فیصلہ کریں کہ آپ کس ہارڈویئر پلیٹ فارم میں دلچسپی رکھتے ہیں۔

خصوصی ہارڈویئر کا انتخاب اسباق اور اسائنمنٹس کی پیچیدگی کو کم کرنے کے لیے کیا گیا ہے۔ اگرچہ دیگر ہارڈویئر بھی کام کر سکتے ہیں، ہم اس بات کی ضمانت نہیں دے سکتے کہ تمام اسائنمنٹس آپ کے آلے پر اضافی ہارڈویئر کے بغیر سپورٹ ہوں گے۔ مثال کے طور پر، بہت سے Arduino آلات میں WiFi نہیں ہوتا، جو کلاؤڈ سے جڑنے کے لیے ضروری ہے - Wio ٹرمینل کا انتخاب اس لیے کیا گیا کیونکہ اس میں WiFi بلٹ ان ہے۔

آپ کو کچھ غیر تکنیکی اشیاء کی بھی ضرورت ہوگی، جیسے مٹی یا گملے کا پودا، اور پھل یا سبزیاں۔

## کٹس خریدیں

![Seeed Studios کا لوگو](../../translated_images/ur/seeed-logo.74732b6b482b6e8e.webp)

Seeed Studios نے بہت مہربانی سے تمام ہارڈویئر کو آسانی سے خریدنے کے لیے کٹس کی شکل میں دستیاب کر دیا ہے:

### Arduino - Wio ٹرمینل

**[Seeed اور Microsoft کے ساتھ ابتدائی IoT - Wio ٹرمینل اسٹارٹر کٹ](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)**

[![Wio ٹرمینل ہارڈویئر کٹ](../../translated_images/ur/wio-hardware-kit.4c70c48b85e4283a.webp)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)

### Raspberry Pi

**[Seeed اور Microsoft کے ساتھ ابتدائی IoT - Raspberry Pi 4 اسٹارٹر کٹ](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)**

[![Raspberry Pi ٹرمینل ہارڈویئر کٹ](../../translated_images/ur/pi-hardware-kit.26dbadaedb7dd44c73b0131d5d68ea29472ed0a9744f90d5866c6d82f2d16380.png)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)

## Arduino

Arduino کے لیے تمام ڈیوائس کوڈ C++ میں ہیں۔ تمام اسائنمنٹس مکمل کرنے کے لیے آپ کو درج ذیل کی ضرورت ہوگی:

### Arduino ہارڈویئر

* [Wio ٹرمینل](https://www.seeedstudio.com/Wio-Terminal-p-4509.html)
* *اختیاری* - USB-C کیبل یا USB-A سے USB-C اڈاپٹر۔ Wio ٹرمینل میں USB-C پورٹ ہے اور یہ USB-C سے USB-A کیبل کے ساتھ آتا ہے۔ اگر آپ کے PC یا Mac میں صرف USB-C پورٹس ہیں تو آپ کو USB-C کیبل یا USB-A سے USB-C اڈاپٹر کی ضرورت ہوگی۔

### Arduino کے مخصوص سینسرز اور ایکچویٹرز

یہ Wio ٹرمینل Arduino ڈیوائس کے لیے مخصوص ہیں اور Raspberry Pi کے لیے متعلقہ نہیں ہیں۔

* [ArduCam Mini 2MP Plus - OV2640](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/)
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)
* [بریڈ بورڈ جمپر وائرز](https://www.seeedstudio.com/Breadboard-Jumper-Wire-Pack-241mm-200mm-160mm-117m-p-234.html)
* ہیڈ فون یا دیگر اسپیکر 3.5mm جیک کے ساتھ، یا JST اسپیکر جیسے:
  * [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
* microSD کارڈ 16GB یا اس سے کم، اور ایک کنیکٹر تاکہ آپ SD کارڈ کو اپنے کمپیوٹر کے ساتھ استعمال کر سکیں اگر آپ کے پاس بلٹ ان نہیں ہے۔ **نوٹ** - Wio ٹرمینل صرف 16GB تک کے SD کارڈز کو سپورٹ کرتا ہے، اس سے زیادہ صلاحیت والے کارڈز کو سپورٹ نہیں کرتا۔

## Raspberry Pi

Raspberry Pi کے لیے تمام ڈیوائس کوڈ Python میں ہیں۔ تمام اسائنمنٹس مکمل کرنے کے لیے آپ کو درج ذیل کی ضرورت ہوگی:

### Raspberry Pi ہارڈویئر

* [Raspberry Pi](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/)
  > 💁 Pi 2B اور اس کے بعد کے ورژنز ان اسباق میں دی گئی اسائنمنٹس کے ساتھ کام کریں گے۔ اگر آپ Raspberry Pi پر براہ راست VS Code چلانے کا ارادہ رکھتے ہیں، تو 2GB یا اس سے زیادہ RAM کے ساتھ Pi 4 کی ضرورت ہوگی۔ اگر آپ Pi کو ریموٹلی ایکسیس کریں گے تو کوئی بھی Pi 2B اور اس کے بعد کے ورژنز کام کریں گے۔
* microSD کارڈ (آپ Raspberry Pi کٹس حاصل کر سکتے ہیں جو microSD کارڈ کے ساتھ آتی ہیں)، اور ایک کنیکٹر تاکہ آپ SD کارڈ کو اپنے کمپیوٹر کے ساتھ استعمال کر سکیں اگر آپ کے پاس بلٹ ان نہیں ہے۔
* USB پاور سپلائی (آپ Raspberry Pi 4 کٹس حاصل کر سکتے ہیں جو پاور سپلائی کے ساتھ آتی ہیں)۔ اگر آپ Raspberry Pi 4 استعمال کر رہے ہیں تو آپ کو USB-C پاور سپلائی کی ضرورت ہوگی، اور پہلے کے آلات کے لیے micro-USB پاور سپلائی کی ضرورت ہوگی۔

### Raspberry Pi کے مخصوص سینسرز اور ایکچویٹرز

یہ Raspberry Pi کے لیے مخصوص ہیں اور Arduino ڈیوائس کے لیے متعلقہ نہیں ہیں۔

* [Grove Pi بیس ہیٹ](https://www.seeedstudio.com/Grove-Base-Hat-for-Raspberry-Pi.html)
* [Raspberry Pi کیمرہ ماڈیول](https://www.raspberrypi.org/products/camera-module-v2/)
* مائیکروفون اور اسپیکر:

  درج ذیل میں سے کوئی ایک استعمال کریں (یا اس کے مساوی):
  * کوئی بھی USB مائیکروفون اور کوئی بھی USB اسپیکر، یا 3.5mm جیک کیبل کے ساتھ اسپیکر، یا HDMI آڈیو آؤٹ پٹ کا استعمال کریں اگر آپ کا Raspberry Pi اسپیکرز کے ساتھ مانیٹر یا TV سے جڑا ہوا ہے۔
  * کوئی بھی USB ہیڈسیٹ جس میں بلٹ ان مائیکروفون ہو۔
  * [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) کے ساتھ:
    * ہیڈ فون یا دیگر اسپیکر 3.5mm جیک کے ساتھ، یا JST اسپیکر جیسے:
    * [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
  * [USB اسپیکر فون](https://www.amazon.com/USB-Speakerphone-Conference-Business-Microphones/dp/B07Q3D7F8S/ref=sr_1_1?dchild=1&keywords=m0&qid=1614647389&sr=8-1)
* [Grove لائٹ سینسر](https://www.seeedstudio.com/Grove-Light-Sensor-v1-2-LS06-S-phototransistor.html)
* [Grove بٹن](https://www.seeedstudio.com/Grove-Button.html)

## سینسرز اور ایکچویٹرز

زیادہ تر سینسرز اور ایکچویٹرز جو ضروری ہیں وہ Arduino اور Raspberry Pi دونوں لرننگ راستوں میں استعمال ہوتے ہیں:

* [Grove LED](https://www.seeedstudio.com/Grove-LED-Pack-p-4364.html) x 2
* [Grove نمی اور درجہ حرارت سینسر](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html)
* [Grove کیپیسٹیو مٹی نمی سینسر](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html)
* [Grove ریلے](https://www.seeedstudio.com/Grove-Relay.html)
* [Grove GPS (Air530)](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html)
* [Grove وقت کی پرواز کا فاصلہ سینسر](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html)

## اختیاری ہارڈویئر

خودکار پانی دینے کے اسباق ریلے کا استعمال کرتے ہوئے کام کرتے ہیں۔ ایک آپشن کے طور پر، آپ اس ریلے کو USB سے چلنے والے واٹر پمپ سے جوڑ سکتے ہیں، درج ذیل ہارڈویئر کا استعمال کرتے ہوئے:

* [6V واٹر پمپ](https://www.seeedstudio.com/6V-Mini-Water-Pump-p-1945.html)
* [USB ٹرمینل](https://www.adafruit.com/product/3628)
* سلیکون پائپ
* سرخ اور سیاہ تاریں
* چھوٹا فلیٹ ہیڈ سکریو ڈرایور

## ورچوئل ہارڈویئر

ورچوئل ہارڈویئر راستہ سینسرز اور ایکچویٹرز کے لیے سیمولیٹرز فراہم کرے گا، جو Python میں نافذ کیے گئے ہیں۔ آپ کے ہارڈویئر کی دستیابی پر منحصر ہے، آپ اسے اپنے عام ڈویلپمنٹ ڈیوائس، جیسے Mac، PC، یا Raspberry Pi پر چلا سکتے ہیں اور صرف وہ ہارڈویئر سیمولیٹ کر سکتے ہیں جو آپ کے پاس نہیں ہے۔ مثال کے طور پر، اگر آپ کے پاس Raspberry Pi کیمرہ ہے لیکن Grove سینسرز نہیں ہیں، تو آپ اپنے Pi پر ورچوئل ڈیوائس کوڈ چلا سکتے ہیں اور Grove سینسرز کو سیمولیٹ کر سکتے ہیں، لیکن فزیکل کیمرہ استعمال کر سکتے ہیں۔

ورچوئل ہارڈویئر [CounterFit پروجیکٹ](https://github.com/CounterFit-IoT/CounterFit) کا استعمال کرے گا۔

ان اسباق کو مکمل کرنے کے لیے آپ کے پاس ویب کیم، مائیکروفون، اور آڈیو آؤٹ پٹ جیسے اسپیکرز یا ہیڈ فون ہونے چاہئیں۔ یہ بلٹ ان یا ایکسٹرنل ہو سکتے ہیں، اور انہیں آپریٹنگ سسٹم کے ساتھ کام کرنے کے لیے کنفیگر کیا جانا چاہیے اور تمام ایپلیکیشنز کے لیے دستیاب ہونا چاہیے۔

---

**ڈسکلیمر**:  
یہ دستاویز AI ترجمہ سروس [Co-op Translator](https://github.com/Azure/co-op-translator) کا استعمال کرتے ہوئے ترجمہ کی گئی ہے۔ ہم درستگی کے لیے کوشش کرتے ہیں، لیکن براہ کرم آگاہ رہیں کہ خودکار ترجمے میں غلطیاں یا غیر درستیاں ہو سکتی ہیں۔ اصل دستاویز کو اس کی اصل زبان میں مستند ذریعہ سمجھا جانا چاہیے۔ اہم معلومات کے لیے، پیشہ ور انسانی ترجمہ کی سفارش کی جاتی ہے۔ ہم اس ترجمے کے استعمال سے پیدا ہونے والی کسی بھی غلط فہمی یا غلط تشریح کے ذمہ دار نہیں ہیں۔