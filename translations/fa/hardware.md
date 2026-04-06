# سخت‌افزار

**T** در IoT به معنای **اشیا** است و به دستگاه‌هایی اشاره دارد که با دنیای اطراف ما تعامل دارند. هر پروژه بر اساس سخت‌افزار واقعی طراحی شده است که برای دانش‌آموزان و علاقه‌مندان در دسترس است. ما دو گزینه سخت‌افزار IoT داریم که می‌توانید بر اساس ترجیحات شخصی، دانش یا علاقه به زبان برنامه‌نویسی، اهداف یادگیری و دسترسی انتخاب کنید. همچنین نسخه‌ای از سخت‌افزار مجازی برای کسانی که به سخت‌افزار دسترسی ندارند یا می‌خواهند قبل از خرید اطلاعات بیشتری کسب کنند، ارائه شده است.

> 💁 برای انجام تکالیف نیازی به خرید سخت‌افزار IoT ندارید. می‌توانید همه چیز را با استفاده از سخت‌افزار مجازی انجام دهید.

گزینه‌های سخت‌افزار فیزیکی شامل Arduino یا Raspberry Pi هستند. هر پلتفرم مزایا و معایب خاص خود را دارد که در یکی از درس‌های اولیه پوشش داده شده است. اگر هنوز تصمیم نگرفته‌اید که از کدام پلتفرم سخت‌افزاری استفاده کنید، می‌توانید [درس دوم از پروژه اول](./1-getting-started/lessons/2-deeper-dive/README.md) را مرور کنید تا تصمیم بگیرید کدام پلتفرم سخت‌افزاری برای یادگیری شما جذاب‌تر است.

سخت‌افزار خاصی که انتخاب شده است، برای کاهش پیچیدگی درس‌ها و تکالیف طراحی شده است. اگرچه ممکن است سخت‌افزارهای دیگر نیز کار کنند، اما نمی‌توانیم تضمین کنیم که همه تکالیف بدون سخت‌افزار اضافی روی دستگاه شما پشتیبانی شوند. به عنوان مثال، بسیاری از دستگاه‌های Arduino فاقد WiFi هستند که برای اتصال به فضای ابری لازم است - ترمینال Wio انتخاب شده است زیرا WiFi داخلی دارد.

همچنین به چند مورد غیر فنی مانند خاک یا یک گلدان گیاه و میوه یا سبزیجات نیاز خواهید داشت.

## خرید کیت‌ها

![لوگوی Seeed Studios](../../translated_images/fa/seeed-logo.74732b6b482b6e8e.webp)

Seeed Studios به‌طور سخاوتمندانه‌ای تمام سخت‌افزارها را به صورت کیت‌های آسان برای خرید در دسترس قرار داده است:

### Arduino - Wio Terminal

**[IoT برای مبتدیان با Seeed و Microsoft - کیت شروع Wio Terminal](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)**

[![کیت سخت‌افزاری Wio Terminal](../../translated_images/fa/wio-hardware-kit.4c70c48b85e4283a.webp)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)

### Raspberry Pi

**[IoT برای مبتدیان با Seeed و Microsoft - کیت شروع Raspberry Pi 4](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)**

[![کیت سخت‌افزاری Raspberry Pi Terminal](../../translated_images/fa/pi-hardware-kit.26dbadaedb7dd44c.webp)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)

## Arduino

تمام کدهای دستگاه برای Arduino به زبان C++ نوشته شده‌اند. برای تکمیل تمام تکالیف به موارد زیر نیاز خواهید داشت:

### سخت‌افزار Arduino

* [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html)
* *اختیاری* - کابل USB-C یا آداپتور USB-A به USB-C. ترمینال Wio دارای یک پورت USB-C است و با یک کابل USB-C به USB-A ارائه می‌شود. اگر رایانه شخصی یا مک شما فقط پورت USB-C دارد، به یک کابل USB-C یا آداپتور USB-A به USB-C نیاز خواهید داشت.

### حسگرها و عملگرهای خاص Arduino

این موارد مختص استفاده از دستگاه Arduino Wio Terminal هستند و برای استفاده از Raspberry Pi مرتبط نیستند.

* [ArduCam Mini 2MP Plus - OV2640](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/)
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)
* [سیم‌های جامپر بردبورد](https://www.seeedstudio.com/Breadboard-Jumper-Wire-Pack-241mm-200mm-160mm-117m-p-234.html)
* هدفون یا بلندگوی دیگر با جک 3.5 میلی‌متری، یا بلندگوی JST مانند:
  * [بلندگوی محصور مونو - 2 وات 6 اهم](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
* کارت microSD با ظرفیت 16 گیگابایت یا کمتر، به همراه یک کانکتور برای استفاده از کارت SD با رایانه شما در صورتی که کارت‌خوان داخلی ندارید. **توجه** - ترمینال Wio فقط از کارت‌های SD تا ظرفیت 16 گیگابایت پشتیبانی می‌کند و ظرفیت‌های بالاتر را پشتیبانی نمی‌کند.

## Raspberry Pi

تمام کدهای دستگاه برای Raspberry Pi به زبان Python نوشته شده‌اند. برای تکمیل تمام تکالیف به موارد زیر نیاز خواهید داشت:

### سخت‌افزار Raspberry Pi

* [Raspberry Pi](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/)
  > 💁 نسخه‌های Pi 2B و بالاتر باید با تکالیف این درس‌ها کار کنند. اگر قصد دارید VS Code را مستقیماً روی Pi اجرا کنید، به یک Pi 4 با 2 گیگابایت یا بیشتر RAM نیاز دارید. اگر قصد دارید از راه دور به Pi دسترسی داشته باشید، هر Pi 2B و بالاتر کار خواهد کرد.
* کارت microSD (می‌توانید کیت‌های Raspberry Pi را که شامل کارت microSD هستند تهیه کنید)، به همراه یک کانکتور برای استفاده از کارت SD با رایانه شما در صورتی که کارت‌خوان داخلی ندارید.
* منبع تغذیه USB (می‌توانید کیت‌های Raspberry Pi 4 را که شامل منبع تغذیه هستند تهیه کنید). اگر از Raspberry Pi 4 استفاده می‌کنید، به منبع تغذیه USB-C نیاز دارید، دستگاه‌های قدیمی‌تر به منبع تغذیه micro-USB نیاز دارند.

### حسگرها و عملگرهای خاص Raspberry Pi

این موارد مختص استفاده از Raspberry Pi هستند و برای استفاده از دستگاه Arduino مرتبط نیستند.

* [Grove Pi base hat](https://www.seeedstudio.com/Grove-Base-Hat-for-Raspberry-Pi.html)
* [ماژول دوربین Raspberry Pi](https://www.raspberrypi.org/products/camera-module-v2/)
* میکروفون و بلندگو:

  از یکی از موارد زیر (یا معادل آن‌ها) استفاده کنید:
  * هر میکروفون USB با هر بلندگوی USB، یا بلندگو با کابل جک 3.5 میلی‌متری، یا استفاده از خروجی صوتی HDMI اگر Raspberry Pi شما به مانیتور یا تلویزیون با بلندگو متصل است.
  * هر هدست USB با میکروفون داخلی
  * [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) به همراه
    * هدفون یا بلندگوی دیگر با جک 3.5 میلی‌متری، یا بلندگوی JST مانند:
    * [بلندگوی محصور مونو - 2 وات 6 اهم](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
  * [اسپیکرفون USB](https://www.amazon.com/USB-Speakerphone-Conference-Business-Microphones/dp/B07Q3D7F8S/ref=sr_1_1?dchild=1&keywords=m0&qid=1614647389&sr=8-1)
* [حسگر نور Grove](https://www.seeedstudio.com/Grove-Light-Sensor-v1-2-LS06-S-phototransistor.html)
* [دکمه Grove](https://www.seeedstudio.com/Grove-Button.html)

## حسگرها و عملگرها

بیشتر حسگرها و عملگرهای مورد نیاز در مسیرهای یادگیری Arduino و Raspberry Pi استفاده می‌شوند:

* [LED Grove](https://www.seeedstudio.com/Grove-LED-Pack-p-4364.html) x 2
* [حسگر رطوبت و دما Grove](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html)
* [حسگر رطوبت خاک خازنی Grove](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html)
* [رله Grove](https://www.seeedstudio.com/Grove-Relay.html)
* [GPS Grove (Air530)](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html)
* [حسگر فاصله زمانی پرواز Grove](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html)

## سخت‌افزار اختیاری

درس‌های مربوط به آبیاری خودکار با استفاده از یک رله کار می‌کنند. به عنوان یک گزینه، می‌توانید این رله را به یک پمپ آب که با USB تغذیه می‌شود متصل کنید و از سخت‌افزار زیر استفاده کنید:

* [پمپ آب 6 ولت](https://www.seeedstudio.com/6V-Mini-Water-Pump-p-1945.html)
* [ترمینال USB](https://www.adafruit.com/product/3628)
* لوله‌های سیلیکونی
* سیم‌های قرمز و مشکی
* پیچ‌گوشتی کوچک تخت

## سخت‌افزار مجازی

مسیر سخت‌افزار مجازی شبیه‌سازهایی برای حسگرها و عملگرها ارائه می‌دهد که در Python پیاده‌سازی شده‌اند. بسته به دسترسی شما به سخت‌افزار، می‌توانید این شبیه‌سازها را روی دستگاه توسعه عادی خود، مانند مک یا رایانه شخصی، اجرا کنید یا آن را روی Raspberry Pi اجرا کرده و فقط سخت‌افزاری که ندارید شبیه‌سازی کنید. به عنوان مثال، اگر دوربین Raspberry Pi دارید اما حسگرهای Grove را ندارید، می‌توانید کد دستگاه مجازی را روی Pi خود اجرا کنید و حسگرهای Grove را شبیه‌سازی کنید، اما از دوربین فیزیکی استفاده کنید.

سخت‌افزار مجازی از [پروژه CounterFit](https://github.com/CounterFit-IoT/CounterFit) استفاده خواهد کرد.

برای تکمیل این درس‌ها، باید یک وب‌کم، میکروفون و خروجی صوتی مانند بلندگو یا هدفون داشته باشید. این موارد می‌توانند داخلی یا خارجی باشند و باید با سیستم‌عامل شما پیکربندی شوند و برای استفاده در تمام برنامه‌ها در دسترس باشند.

**سلب مسئولیت**:  
این سند با استفاده از سرویس ترجمه هوش مصنوعی [Co-op Translator](https://github.com/Azure/co-op-translator) ترجمه شده است. در حالی که ما تلاش می‌کنیم دقت را حفظ کنیم، لطفاً توجه داشته باشید که ترجمه‌های خودکار ممکن است شامل خطاها یا نادرستی‌ها باشند. سند اصلی به زبان اصلی آن باید به عنوان منبع معتبر در نظر گرفته شود. برای اطلاعات حساس، توصیه می‌شود از ترجمه حرفه‌ای انسانی استفاده کنید. ما مسئولیتی در قبال سوء تفاهم‌ها یا تفسیرهای نادرست ناشی از استفاده از این ترجمه نداریم.