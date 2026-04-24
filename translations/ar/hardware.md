# الأجهزة

الحرف **T** في إنترنت الأشياء (IoT) يشير إلى **الأشياء**، وهي الأجهزة التي تتفاعل مع العالم من حولنا. كل مشروع يعتمد على أجهزة حقيقية متوفرة للطلاب والهواة. لدينا خياران من أجهزة إنترنت الأشياء يمكن استخدامها بناءً على التفضيلات الشخصية، معرفة لغة البرمجة أو التفضيلات، أهداف التعلم، وتوفر الأجهزة. كما قمنا بتوفير نسخة "أجهزة افتراضية" لأولئك الذين ليس لديهم وصول إلى الأجهزة، أو يرغبون في التعرف أكثر قبل الالتزام بالشراء.

> 💁 لا تحتاج إلى شراء أي أجهزة إنترنت الأشياء لإكمال المهام. يمكنك القيام بكل شيء باستخدام أجهزة إنترنت الأشياء الافتراضية.

خيارات الأجهزة المادية هي Arduino أو Raspberry Pi. لكل منصة مزايا وعيوب، ويتم تغطية هذه الأمور في أحد الدروس الأولية. إذا لم تكن قد قررت بعد أي منصة أجهزة ستستخدمها، يمكنك مراجعة [الدرس الثاني من المشروع الأول](./1-getting-started/lessons/2-deeper-dive/README.md) لتحديد أي منصة أجهزة تفضل تعلمها.

تم اختيار الأجهزة المحددة لتقليل تعقيد الدروس والمهام. على الرغم من أن الأجهزة الأخرى قد تعمل، لا يمكننا ضمان أن جميع المهام ستكون مدعومة على جهازك دون أجهزة إضافية. على سبيل المثال، العديد من أجهزة Arduino لا تحتوي على WiFi، وهو مطلوب للاتصال بالسحابة - تم اختيار Wio Terminal لأنه يحتوي على WiFi مدمج.

ستحتاج أيضًا إلى بعض العناصر غير التقنية، مثل التربة أو نبات في وعاء، والفواكه أو الخضروات.

## شراء المجموعات

![شعار Seeed Studios](../../translated_images/ar/seeed-logo.74732b6b482b6e8e.webp)

قامت Seeed Studios بتوفير جميع الأجهزة كمجموعات سهلة الشراء:

### Arduino - Wio Terminal

**[إنترنت الأشياء للمبتدئين مع Seeed وMicrosoft - مجموعة البداية لـ Wio Terminal](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)**

[![مجموعة أجهزة Wio Terminal](../../translated_images/ar/wio-hardware-kit.4c70c48b85e4283a.webp)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)

### Raspberry Pi

**[إنترنت الأشياء للمبتدئين مع Seeed وMicrosoft - مجموعة البداية لـ Raspberry Pi 4](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)**

[![مجموعة أجهزة Raspberry Pi Terminal](../../translated_images/ar/pi-hardware-kit.26dbadaedb7dd44c.webp)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)

## Arduino

كل كود الجهاز الخاص بـ Arduino مكتوب بلغة C++. لإكمال جميع المهام ستحتاج إلى ما يلي:

### أجهزة Arduino

* [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html)
* *اختياري* - كابل USB-C أو محول USB-A إلى USB-C. يحتوي Wio Terminal على منفذ USB-C ويأتي مع كابل USB-C إلى USB-A. إذا كان جهاز الكمبيوتر أو Mac الخاص بك يحتوي فقط على منافذ USB-C، ستحتاج إلى كابل USB-C أو محول USB-A إلى USB-C.

### حساسات ومشغلات خاصة بـ Arduino

هذه خاصة باستخدام جهاز Arduino Wio Terminal، وليست ذات صلة باستخدام Raspberry Pi.

* [ArduCam Mini 2MP Plus - OV2640](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/)
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)
* [أسلاك توصيل Breadboard](https://www.seeedstudio.com/Breadboard-Jumper-Wire-Pack-241mm-200mm-160mm-117m-p-234.html)
* سماعات رأس أو مكبر صوت آخر بمنفذ 3.5mm، أو مكبر صوت JST مثل:
  * [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
* بطاقة microSD بسعة 16GB أو أقل، مع موصل لاستخدام بطاقة SD مع جهاز الكمبيوتر إذا لم يكن لديك واحد مدمج. **ملاحظة** - يدعم Wio Terminal بطاقات SD حتى 16GB فقط، ولا يدعم السعات الأعلى.

## Raspberry Pi

كل كود الجهاز الخاص بـ Raspberry Pi مكتوب بلغة Python. لإكمال جميع المهام ستحتاج إلى ما يلي:

### أجهزة Raspberry Pi

* [Raspberry Pi](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/)
  > 💁 الإصدارات من Pi 2B وما فوق يجب أن تعمل مع المهام في هذه الدروس. إذا كنت تخطط لتشغيل VS Code مباشرة على Pi، فستحتاج إلى Pi 4 بسعة 2GB أو أكثر من ذاكرة الوصول العشوائي. إذا كنت ستصل إلى Pi عن بُعد، فإن أي Pi 2B وما فوق سيعمل.
* بطاقة microSD (يمكنك الحصول على مجموعات Raspberry Pi التي تأتي مع بطاقة microSD)، مع موصل لاستخدام بطاقة SD مع جهاز الكمبيوتر إذا لم يكن لديك واحد مدمج.
* مصدر طاقة USB (يمكنك الحصول على مجموعات Raspberry Pi 4 التي تأتي مع مصدر طاقة). إذا كنت تستخدم Raspberry Pi 4، ستحتاج إلى مصدر طاقة USB-C، أما الأجهزة السابقة فتحتاج إلى مصدر طاقة micro-USB.

### حساسات ومشغلات خاصة بـ Raspberry Pi

هذه خاصة باستخدام Raspberry Pi، وليست ذات صلة باستخدام جهاز Arduino.

* [Grove Pi base hat](https://www.seeedstudio.com/Grove-Base-Hat-for-Raspberry-Pi.html)
* [وحدة كاميرا Raspberry Pi](https://www.raspberrypi.org/products/camera-module-v2/)
* ميكروفون ومكبر صوت:

  استخدم أحد الخيارات التالية (أو ما يعادلها):
  * أي ميكروفون USB مع أي مكبر صوت USB، أو مكبر صوت بمنفذ كابل 3.5mm، أو استخدام إخراج الصوت عبر HDMI إذا كان Raspberry Pi متصلًا بشاشة أو تلفاز يحتوي على مكبرات صوت
  * أي سماعة USB تحتوي على ميكروفون مدمج
  * [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) مع
    * سماعات رأس أو مكبر صوت آخر بمنفذ 3.5mm، أو مكبر صوت JST مثل:
    * [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
  * [USB Speakerphone](https://www.amazon.com/USB-Speakerphone-Conference-Business-Microphones/dp/B07Q3D7F8S/ref=sr_1_1?dchild=1&keywords=m0&qid=1614647389&sr=8-1)
* [حساس الضوء Grove](https://www.seeedstudio.com/Grove-Light-Sensor-v1-2-LS06-S-phototransistor.html)
* [زر Grove](https://www.seeedstudio.com/Grove-Button.html)

## الحساسات والمشغلات

معظم الحساسات والمشغلات المطلوبة تُستخدم في مسارات التعلم لكل من Arduino وRaspberry Pi:

* [Grove LED](https://www.seeedstudio.com/Grove-LED-Pack-p-4364.html) x 2
* [حساس الرطوبة ودرجة الحرارة Grove](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html)
* [حساس رطوبة التربة السعوي Grove](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html)
* [Grove Relay](https://www.seeedstudio.com/Grove-Relay.html)
* [Grove GPS (Air530)](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html)
* [حساس قياس المسافة Grove Time of Flight](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html)

## الأجهزة الاختيارية

الدروس المتعلقة بالري الآلي تعمل باستخدام الريليه. كخيار، يمكنك توصيل هذا الريليه بمضخة مياه تعمل عبر USB باستخدام الأجهزة المدرجة أدناه.

* [مضخة مياه 6V](https://www.seeedstudio.com/6V-Mini-Water-Pump-p-1945.html)
* [منفذ USB](https://www.adafruit.com/product/3628)
* أنابيب سيليكون
* أسلاك حمراء وسوداء
* مفك صغير مسطح الرأس

## الأجهزة الافتراضية

المسار الخاص بالأجهزة الافتراضية يوفر محاكيات للحساسات والمشغلات، يتم تنفيذها بلغة Python. بناءً على توفر الأجهزة لديك، يمكنك تشغيل هذا على جهاز التطوير العادي الخاص بك، مثل Mac أو PC، أو تشغيله على Raspberry Pi ومحاكاة فقط الأجهزة التي لا تمتلكها. على سبيل المثال، إذا كان لديك كاميرا Raspberry Pi ولكن ليس لديك حساسات Grove، ستتمكن من تشغيل كود الجهاز الافتراضي على Pi ومحاكاة حساسات Grove، ولكن استخدام كاميرا فعلية.

الأجهزة الافتراضية ستستخدم مشروع [CounterFit](https://github.com/CounterFit-IoT/CounterFit).

لإكمال هذه الدروس ستحتاج إلى كاميرا ويب، ميكروفون، ومخرج صوت مثل مكبرات الصوت أو سماعات الرأس. يمكن أن تكون هذه الأجهزة مدمجة أو خارجية، ويجب أن تكون مُعدة للعمل مع نظام التشغيل الخاص بك ومتاحة للاستخدام من جميع التطبيقات.

---

**إخلاء المسؤولية**:  
تم ترجمة هذا المستند باستخدام خدمة الترجمة بالذكاء الاصطناعي [Co-op Translator](https://github.com/Azure/co-op-translator). بينما نسعى لتحقيق الدقة، يرجى العلم أن الترجمات الآلية قد تحتوي على أخطاء أو معلومات غير دقيقة. يجب اعتبار المستند الأصلي بلغته الأصلية المصدر الرسمي. للحصول على معلومات حاسمة، يُوصى بالاستعانة بترجمة بشرية احترافية. نحن غير مسؤولين عن أي سوء فهم أو تفسيرات خاطئة تنشأ عن استخدام هذه الترجمة.