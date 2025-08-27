<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "93d352de36526b8990e41dd538100324",
  "translation_date": "2025-08-27T00:31:27+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-microphone.md",
  "language_code": "ar"
}
-->
# إعداد الميكروفون ومكبرات الصوت - Wio Terminal

في هذا الجزء من الدرس، ستقوم بإضافة مكبرات صوت إلى Wio Terminal الخاص بك. يحتوي Wio Terminal بالفعل على ميكروفون مدمج يمكن استخدامه لالتقاط الصوت.

## الأجهزة

يحتوي Wio Terminal بالفعل على ميكروفون مدمج يمكن استخدامه لالتقاط الصوت للتعرف على الكلام.

![الميكروفون في Wio Terminal](../../../../../translated_images/wio-mic.3f8c843dbe8ad917424037a93e3d25c62634add00a04dd8e091317b5a7a90088.ar.png)

لإضافة مكبر صوت، يمكنك استخدام [ReSpeaker 2-Mics Pi Hat](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html). هذه لوحة خارجية تحتوي على ميكروفونين MEMS، بالإضافة إلى موصل مكبر صوت ومقبس سماعات.

![ReSpeaker 2-Mics Pi Hat](../../../../../translated_images/respeaker.f5d19d1c6b14ab1676d24ac2764e64fac5339046ae07be8b45ce07633d61b79b.ar.png)

ستحتاج إلى إضافة سماعات رأس، أو مكبر صوت بمنفذ 3.5 ملم، أو مكبر صوت بمنفذ JST مثل [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html).

لتوصيل ReSpeaker 2-Mics Pi Hat، ستحتاج إلى كابلات توصيل 40 دبوس (تُعرف أيضًا بكابلات ذكر-ذكر).

> 💁 إذا كنت مرتاحًا مع اللحام، يمكنك استخدام [40 Pin Raspberry Pi Hat Adapter Board For Wio Terminal](https://www.seeedstudio.com/40-Pin-Raspberry-Pi-Hat-Adapter-Board-For-Wio-Terminal-p-4730.html) لتوصيل ReSpeaker.

ستحتاج أيضًا إلى بطاقة SD لتنزيل وتشغيل الصوت. يدعم Wio Terminal بطاقات SD حتى حجم 16 جيجابايت، ويجب أن تكون مهيأة بنظام ملفات FAT32 أو exFAT.

### المهمة - توصيل ReSpeaker Pi Hat

1. مع إيقاف تشغيل Wio Terminal، قم بتوصيل ReSpeaker 2-Mics Pi Hat بـ Wio Terminal باستخدام كابلات التوصيل ومآخذ GPIO الموجودة في الجزء الخلفي من Wio Terminal:

    يجب توصيل الدبابيس بهذه الطريقة:

    ![مخطط الدبابيس](../../../../../translated_images/wio-respeaker-wiring-0.767f80aa6508103880d256cdf99ee7219e190db257c7261e4aec219759dc67b9.ar.png)

1. ضع ReSpeaker وWio Terminal بحيث تكون مآخذ GPIO مواجهة للأعلى وعلى الجانب الأيسر.

1. ابدأ من المقبس الموجود في أعلى يسار مقبس GPIO على ReSpeaker. قم بتوصيل كابل توصيل من المقبس العلوي الأيسر لـ ReSpeaker إلى المقبس العلوي الأيسر لـ Wio Terminal.

1. كرر هذه العملية على طول مآخذ GPIO الموجودة على الجانب الأيسر. تأكد من أن الدبابيس مثبتة بإحكام.

    ![ReSpeaker مع الدبابيس اليسرى متصلة بالدبابيس اليسرى لـ Wio Terminal](../../../../../translated_images/wio-respeaker-wiring-1.8d894727f2ba24004824ee5e06b83b6d10952550003a3efb603182121521b0ef.ar.png)

    ![ReSpeaker مع الدبابيس اليسرى متصلة بالدبابيس اليسرى لـ Wio Terminal](../../../../../translated_images/wio-respeaker-wiring-2.329e1cbd306e754f8ffe56f9294794f4a8fa123860d76067a79e9ea385d1bf56.ar.png)

    > 💁 إذا كانت كابلات التوصيل متصلة في شرائط، احتفظ بها معًا - فهذا يسهل التأكد من أنك قمت بتوصيل جميع الكابلات بالترتيب.

1. كرر العملية باستخدام مآخذ GPIO اليمنى على ReSpeaker وWio Terminal. يجب أن تمر هذه الكابلات حول الكابلات الموجودة بالفعل.

    ![ReSpeaker مع الدبابيس اليمنى متصلة بالدبابيس اليمنى لـ Wio Terminal](../../../../../translated_images/wio-respeaker-wiring-3.75b0be447e2fa9307a6a954f9ae8a71b77e39ada6a5ef1a059d341dc850fd90c.ar.png)

    ![ReSpeaker مع الدبابيس اليمنى متصلة بالدبابيس اليمنى لـ Wio Terminal](../../../../../translated_images/wio-respeaker-wiring-4.aa9cd434d8779437de720cba2719d83992413caed1b620b6148f6c8924889afb.ar.png)

    > 💁 إذا كانت كابلات التوصيل متصلة في شرائط، قم بتقسيمها إلى شريطين. مرر كل شريط على جانب من الكابلات الموجودة.

    > 💁 يمكنك استخدام شريط لاصق لتثبيت الدبابيس في كتلة للمساعدة في منع خروج أي منها أثناء التوصيل.
    >
    > ![الدبابيس مثبتة بشريط لاصق](../../../../../translated_images/wio-respeaker-wiring-5.af117c20acf622f3cd656ccd8f4053f8845d6aaa3af164d24cb7dbd54a4bb470.ar.png)

1. ستحتاج إلى إضافة مكبر صوت.

    * إذا كنت تستخدم مكبر صوت بكابل JST، قم بتوصيله بمنفذ JST على ReSpeaker.

      ![مكبر صوت متصل بـ ReSpeaker بكابل JST](../../../../../translated_images/respeaker-jst-speaker.a441d177809df9458041a2012dd336dbb22c00a5c9642647109d2940a50d6fcc.ar.png)

    * إذا كنت تستخدم مكبر صوت بمنفذ 3.5 ملم أو سماعات رأس، أدخلها في مقبس 3.5 ملم.

      ![مكبر صوت متصل بـ ReSpeaker عبر مقبس 3.5 ملم](../../../../../translated_images/respeaker-35mm-speaker.ad79ef4f128c7751f0abf854869b6b779c90c12ae3e48909944a7e48aeee3c7e.ar.png)

### المهمة - إعداد بطاقة SD

1. قم بتوصيل بطاقة SD بجهاز الكمبيوتر الخاص بك باستخدام قارئ خارجي إذا لم يكن لديك منفذ بطاقة SD.

1. قم بتهيئة بطاقة SD باستخدام الأداة المناسبة على جهاز الكمبيوتر الخاص بك، مع التأكد من استخدام نظام ملفات FAT32 أو exFAT.

1. أدخل بطاقة SD في منفذ بطاقة SD الموجود على الجانب الأيسر من Wio Terminal، أسفل زر التشغيل. تأكد من أن البطاقة دخلت بالكامل ونقرت في مكانها - قد تحتاج إلى أداة رفيعة أو بطاقة SD أخرى للمساعدة في دفعها بالكامل.

    ![إدخال بطاقة SD في منفذ بطاقة SD أسفل مفتاح التشغيل](../../../../../translated_images/wio-sd-card.acdcbe322fa4ee7f8f9c8cc015b3263964bb26ab5c7e25b41747988cc5280d64.ar.png)

    > 💁 لإخراج بطاقة SD، تحتاج إلى دفعها قليلاً وستخرج. ستحتاج إلى أداة رفيعة للقيام بذلك مثل مفك مسطح الرأس أو بطاقة SD أخرى.

---

**إخلاء المسؤولية**:  
تم ترجمة هذا المستند باستخدام خدمة الترجمة بالذكاء الاصطناعي [Co-op Translator](https://github.com/Azure/co-op-translator). بينما نسعى لتحقيق الدقة، يرجى العلم أن الترجمات الآلية قد تحتوي على أخطاء أو عدم دقة. يجب اعتبار المستند الأصلي بلغته الأصلية المصدر الرسمي. للحصول على معلومات حاسمة، يُوصى بالاستعانة بترجمة بشرية احترافية. نحن غير مسؤولين عن أي سوء فهم أو تفسيرات خاطئة ناتجة عن استخدام هذه الترجمة.