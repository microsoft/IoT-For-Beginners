# تشغيل كاشف الفواكه على الحافة

![نظرة عامة على هذا الدرس](../../../../../translated_images/ar/lesson-17.bc333c3c35ba8e42.webp)

> رسم توضيحي بواسطة [نيتيا ناراسيمهان](https://github.com/nitya). انقر على الصورة للحصول على نسخة أكبر.

يقدم هذا الفيديو نظرة عامة حول تشغيل مصنفات الصور على أجهزة إنترنت الأشياء، وهو الموضوع الذي يتم تغطيته في هذا الدرس.

[![Custom Vision AI على Azure IoT Edge](https://img.youtube.com/vi/_K5fqGLO8us/0.jpg)](https://www.youtube.com/watch?v=_K5fqGLO8us)

## اختبار ما قبل المحاضرة

[اختبار ما قبل المحاضرة](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/33)

## المقدمة

في الدرس السابق، استخدمت مصنف الصور الخاص بك لتصنيف الفواكه الناضجة وغير الناضجة، حيث أرسلت صورة تم التقاطها بواسطة الكاميرا على جهاز إنترنت الأشياء الخاص بك عبر الإنترنت إلى خدمة سحابية. هذه العمليات تستغرق وقتًا، وتكلف مالًا، وبناءً على نوع بيانات الصور التي تستخدمها، قد تكون لها تداعيات على الخصوصية.

في هذا الدرس، ستتعلم كيفية تشغيل نماذج التعلم الآلي (ML) على الحافة - على أجهزة إنترنت الأشياء التي تعمل على شبكتك الخاصة بدلاً من السحابة. ستتعرف على فوائد ومساوئ الحوسبة الطرفية مقارنة بالحوسبة السحابية، وكيفية نشر نموذج الذكاء الاصطناعي الخاص بك على الحافة، وكيفية الوصول إليه من جهاز إنترنت الأشياء الخاص بك.

في هذا الدرس سنغطي:

* [الحوسبة الطرفية](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Azure IoT Edge](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [تسجيل جهاز IoT Edge](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [إعداد جهاز IoT Edge](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [تصدير النموذج الخاص بك](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [تحضير الحاوية للنشر](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [نشر الحاوية](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [استخدام جهاز IoT Edge الخاص بك](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)

## الحوسبة الطرفية

الحوسبة الطرفية تتضمن وجود أجهزة كمبيوتر تقوم بمعالجة بيانات إنترنت الأشياء بالقرب قدر الإمكان من المكان الذي يتم فيه إنشاء البيانات. بدلاً من أن تتم هذه المعالجة في السحابة، يتم نقلها إلى حافة السحابة - شبكتك الداخلية.

![مخطط معماري يظهر خدمات الإنترنت في السحابة وأجهزة إنترنت الأشياء على شبكة محلية](../../../../../translated_images/ar/cloud-without-edge.b4da641f6022c95e.webp)

في الدروس السابقة، كانت لديك أجهزة تجمع البيانات وترسلها إلى السحابة لتحليلها، حيث يتم تشغيل وظائف بدون خادم أو نماذج ذكاء اصطناعي في السحابة.

![مخطط معماري يظهر أجهزة إنترنت الأشياء على شبكة محلية تتصل بأجهزة الحافة، وهذه الأجهزة تتصل بالسحابة](../../../../../translated_images/ar/cloud-with-edge.1e26462c62c126fe.webp)

الحوسبة الطرفية تتضمن نقل بعض خدمات السحابة إلى أجهزة كمبيوتر تعمل على نفس الشبكة مثل أجهزة إنترنت الأشياء، مع التواصل مع السحابة فقط عند الحاجة. على سبيل المثال، يمكنك تشغيل نماذج ذكاء اصطناعي على أجهزة الحافة لتحليل نضج الفواكه، وإرسال التحليلات فقط إلى السحابة، مثل عدد الفواكه الناضجة مقابل غير الناضجة.

✅ فكر في تطبيقات إنترنت الأشياء التي قمت ببنائها حتى الآن. أي أجزاء منها يمكن نقلها إلى الحافة؟

### الفوائد

فوائد الحوسبة الطرفية تشمل:

1. **السرعة** - الحوسبة الطرفية مثالية للبيانات الحساسة للوقت حيث يتم تنفيذ الإجراءات على نفس الشبكة مثل الجهاز، بدلاً من إجراء مكالمات عبر الإنترنت. هذا يتيح سرعات أعلى حيث يمكن للشبكات الداخلية أن تعمل بسرعات أعلى بكثير من اتصالات الإنترنت، مع انتقال البيانات لمسافات أقصر.

    > 💁 على الرغم من استخدام الكابلات الضوئية لاتصالات الإنترنت التي تسمح للبيانات بالانتقال بسرعة الضوء، إلا أن البيانات قد تستغرق وقتًا للانتقال حول العالم إلى مقدمي الخدمات السحابية. على سبيل المثال، إذا كنت ترسل بيانات من أوروبا إلى خدمات السحابة في الولايات المتحدة، فإن الأمر يستغرق على الأقل 28 مللي ثانية لعبور المحيط الأطلسي عبر كابل ضوئي، وهذا دون احتساب الوقت اللازم لنقل البيانات إلى الكابل، وتحويل الإشارات من كهربائية إلى ضوئية والعكس في الطرف الآخر، ثم من الكابل الضوئي إلى مقدم الخدمة السحابية.

    الحوسبة الطرفية تتطلب أيضًا حركة مرور أقل على الشبكة، مما يقلل من خطر تباطؤ البيانات بسبب الازدحام على النطاق الترددي المحدود المتاح لاتصال الإنترنت.

1. **الوصول عن بعد** - الحوسبة الطرفية تعمل عندما تكون لديك اتصال محدود أو معدوم، أو عندما يكون الاتصال مكلفًا جدًا للاستخدام بشكل مستمر. على سبيل المثال، عند العمل في مناطق الكوارث الإنسانية حيث تكون البنية التحتية محدودة، أو في الدول النامية.

1. **خفض التكاليف** - جمع البيانات وتخزينها وتحليلها وتنفيذ الإجراءات على جهاز الحافة يقلل من استخدام الخدمات السحابية، مما يمكن أن يقلل من التكلفة الإجمالية لتطبيق إنترنت الأشياء الخاص بك. هناك زيادة حديثة في الأجهزة المصممة للحوسبة الطرفية، مثل لوحات تسريع الذكاء الاصطناعي مثل [Jetson Nano من NVIDIA](https://developer.nvidia.com/embedded/jetson-nano-developer-kit)، التي يمكنها تشغيل أعباء عمل الذكاء الاصطناعي باستخدام أجهزة تعتمد على GPU على أجهزة تكلف أقل من 100 دولار أمريكي.

1. **الخصوصية والأمان** - مع الحوسبة الطرفية، تبقى البيانات على شبكتك ولا يتم تحميلها إلى السحابة. هذا غالبًا ما يكون مفضلًا للبيانات الحساسة والمعلومات الشخصية، خاصة لأن البيانات لا تحتاج إلى أن يتم تخزينها بعد تحليلها، مما يقلل بشكل كبير من خطر تسرب البيانات. أمثلة تشمل البيانات الطبية ولقطات كاميرات الأمان.

1. **التعامل مع الأجهزة غير الآمنة** - إذا كانت لديك أجهزة بها عيوب أمنية معروفة ولا تريد توصيلها مباشرة بشبكتك أو الإنترنت، يمكنك توصيلها بشبكة منفصلة إلى جهاز بوابة IoT Edge. يمكن لهذا الجهاز الطرفي أيضًا أن يكون لديه اتصال بشبكتك الأوسع أو الإنترنت، وإدارة تدفقات البيانات ذهابًا وإيابًا.

1. **دعم الأجهزة غير المتوافقة** - إذا كانت لديك أجهزة لا يمكنها الاتصال بـ IoT Hub، مثل الأجهزة التي يمكنها الاتصال فقط باستخدام اتصالات HTTP أو الأجهزة التي لديها فقط بلوتوث للاتصال، يمكنك استخدام جهاز IoT Edge كجهاز بوابة، يقوم بإعادة توجيه الرسائل إلى IoT Hub.

✅ قم ببعض البحث: ما الفوائد الأخرى التي قد تكون موجودة للحوسبة الطرفية؟

### العيوب

هناك عيوب للحوسبة الطرفية، حيث قد تكون السحابة خيارًا مفضلًا:

1. **التوسع والمرونة** - الحوسبة السحابية يمكنها التكيف مع احتياجات الشبكة والبيانات في الوقت الفعلي عن طريق إضافة أو تقليل الخوادم والموارد الأخرى. لإضافة المزيد من أجهزة الحافة يتطلب إضافة أجهزة يدويًا.

1. **الاعتمادية والمرونة** - الحوسبة السحابية توفر خوادم متعددة غالبًا في مواقع متعددة للتكرار واستعادة الكوارث. للحصول على نفس مستوى التكرار على الحافة يتطلب استثمارات كبيرة والكثير من العمل في الإعداد.

1. **الصيانة** - مقدمو الخدمات السحابية يقدمون صيانة النظام والتحديثات.

✅ قم ببعض البحث: ما العيوب الأخرى التي قد تكون موجودة للحوسبة الطرفية؟

العيوب هي في الأساس عكس فوائد استخدام السحابة - عليك بناء وإدارة هذه الأجهزة بنفسك، بدلاً من الاعتماد على خبرة وحجم مقدمي الخدمات السحابية.

بعض المخاطر يتم تخفيفها بطبيعة الحوسبة الطرفية نفسها. على سبيل المثال، إذا كان لديك جهاز طرفي يعمل في مصنع يجمع البيانات من الآلات، فلا تحتاج إلى التفكير في بعض سيناريوهات استعادة الكوارث. إذا انقطعت الكهرباء عن المصنع، فلن تحتاج إلى جهاز طرفي احتياطي لأن الآلات التي تولد البيانات التي يعالجها الجهاز الطرفي ستكون أيضًا بدون كهرباء.

بالنسبة لأنظمة إنترنت الأشياء، غالبًا ما ترغب في مزيج من الحوسبة السحابية والطرفية، مستفيدًا من كل خدمة بناءً على احتياجات النظام، عملائه، وصيانته.

## Azure IoT Edge

![شعار Azure IoT Edge](../../../../../translated_images/ar/azure-iot-edge-logo.c1c076749b5cba2e.webp)

Azure IoT Edge هو خدمة يمكن أن تساعدك في نقل أعباء العمل من السحابة إلى الحافة. يمكنك إعداد جهاز كجهاز طرفي، ومن السحابة يمكنك نشر التعليمات البرمجية إلى هذا الجهاز الطرفي. هذا يسمح لك بمزج قدرات السحابة والحافة.

> 🎓 *أعباء العمل* هو مصطلح لأي خدمة تقوم بنوع من العمل، مثل نماذج الذكاء الاصطناعي، التطبيقات، أو الوظائف بدون خادم.

على سبيل المثال، يمكنك تدريب مصنف صور في السحابة، ثم من السحابة نشره إلى جهاز طرفي. جهاز إنترنت الأشياء الخاص بك يرسل الصور إلى الجهاز الطرفي للتصنيف، بدلاً من إرسال الصور عبر الإنترنت. إذا كنت بحاجة إلى نشر نسخة جديدة من النموذج، يمكنك تدريبه في السحابة واستخدام IoT Edge لتحديث النموذج على الجهاز الطرفي إلى النسخة الجديدة.

> 🎓 البرمجيات التي يتم نشرها إلى IoT Edge تُعرف باسم *الوحدات*. بشكل افتراضي، IoT Edge يشغل وحدات تتواصل مع IoT Hub، مثل وحدات `edgeAgent` و`edgeHub`. عندما تقوم بنشر مصنف صور، يتم نشره كوحدة إضافية.

IoT Edge مدمج في IoT Hub، لذا يمكنك إدارة الأجهزة الطرفية باستخدام نفس الخدمة التي تستخدمها لإدارة أجهزة إنترنت الأشياء، بنفس مستوى الأمان.

IoT Edge يشغل التعليمات البرمجية من *الحاويات* - تطبيقات مستقلة يتم تشغيلها بمعزل عن باقي التطبيقات على جهاز الكمبيوتر الخاص بك. عندما تقوم بتشغيل حاوية، فإنها تعمل كجهاز كمبيوتر منفصل يعمل داخل جهاز الكمبيوتر الخاص بك، مع برمجياته وخدماته وتطبيقاته الخاصة. معظم الوقت، لا يمكن للحاويات الوصول إلى أي شيء على جهاز الكمبيوتر الخاص بك إلا إذا اخترت مشاركة أشياء مثل مجلد مع الحاوية. الحاوية بعد ذلك تعرض الخدمات عبر منفذ مفتوح يمكنك الاتصال به أو عرضه على شبكتك.

![طلب ويب يتم إعادة توجيهه إلى حاوية](../../../../../translated_images/ar/container-web-browser.4ee81dd4f0d8838c.webp)

على سبيل المثال، يمكنك أن تكون لديك حاوية بها موقع ويب يعمل على المنفذ 80، وهو المنفذ الافتراضي لـ HTTP، ويمكنك بعد ذلك عرضه من جهاز الكمبيوتر الخاص بك أيضًا على المنفذ 80.

✅ قم ببعض البحث: اقرأ عن الحاويات والخدمات مثل Docker أو Moby.

يمكنك استخدام Custom Vision لتنزيل مصنفات الصور ونشرها كحاويات، إما تشغيلها مباشرة على جهاز أو نشرها عبر IoT Edge. بمجرد تشغيلها في حاوية، يمكن الوصول إليها باستخدام نفس واجهة برمجة التطبيقات REST مثل النسخة السحابية، ولكن مع نقطة النهاية تشير إلى الجهاز الطرفي الذي يشغل الحاوية.

## تسجيل جهاز IoT Edge

لاستخدام جهاز IoT Edge، يجب تسجيله في IoT Hub.

### المهمة - تسجيل جهاز IoT Edge

1. قم بإنشاء IoT Hub في مجموعة الموارد `fruit-quality-detector`. امنحه اسمًا فريدًا يعتمد على `fruit-quality-detector`.

1. قم بتسجيل جهاز IoT Edge يسمى `fruit-quality-detector-edge` في IoT Hub الخاص بك. الأمر للقيام بذلك مشابه للأمر المستخدم لتسجيل جهاز غير طرفي، باستثناء أنك تمرر العلامة `--edge-enabled`.

    ```sh
    az iot hub device-identity create --edge-enabled \
                                      --device-id fruit-quality-detector-edge \
                                      --hub-name <hub_name>
    ```

    استبدل `<hub_name>` باسم IoT Hub الخاص بك.

1. احصل على سلسلة الاتصال لجهازك باستخدام الأمر التالي:

    ```sh
    az iot hub device-identity connection-string show --device-id fruit-quality-detector-edge \
                                                      --output table \
                                                      --hub-name <hub_name>
    ```

    استبدل `<hub_name>` باسم IoT Hub الخاص بك.

    خذ نسخة من سلسلة الاتصال التي تظهر في الإخراج.

## إعداد جهاز IoT Edge

بمجرد إنشاء تسجيل الجهاز الطرفي في IoT Hub الخاص بك، يمكنك إعداد الجهاز الطرفي.

### المهمة - تثبيت وتشغيل وقت تشغيل IoT Edge

**وقت تشغيل IoT Edge يشغل فقط حاويات Linux.** يمكن تشغيله على Linux، أو على Windows باستخدام الأجهزة الافتراضية Linux.

* إذا كنت تستخدم Raspberry Pi كجهاز إنترنت الأشياء الخاص بك، فإنه يشغل نسخة مدعومة من Linux ويمكنه استضافة وقت تشغيل IoT Edge. اتبع [دليل تثبيت Azure IoT Edge لـ Linux على مستندات Microsoft](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge?WT.mc_id=academic-17441-jabenn) لتثبيت IoT Edge وإعداد سلسلة الاتصال.

    > 💁 تذكر، نظام تشغيل Raspberry Pi هو نسخة من Debian Linux.

* إذا كنت لا تستخدم Raspberry Pi، ولكن لديك جهاز كمبيوتر يعمل بنظام Linux، يمكنك تشغيل وقت تشغيل IoT Edge. اتبع [دليل تثبيت Azure IoT Edge لـ Linux على مستندات Microsoft](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge?WT.mc_id=academic-17441-jabenn) لتثبيت IoT Edge وإعداد سلسلة الاتصال.

* إذا كنت تستخدم Windows، يمكنك تثبيت وقت تشغيل IoT Edge في جهاز افتراضي Linux باتباع [قسم تثبيت وتشغيل وقت تشغيل IoT Edge من دليل البدء السريع لنشر أول وحدة IoT Edge على جهاز Windows على مستندات Microsoft](https://docs.microsoft.com/azure/iot-edge/quickstart?WT.mc_id=academic-17441-jabenn#install-and-start-the-iot-edge-runtime). يمكنك التوقف عندما تصل إلى قسم *نشر وحدة*.

* إذا كنت تستخدم macOS، يمكنك إنشاء جهاز افتراضي (VM) في السحابة لاستخدامه كجهاز IoT Edge الخاص بك. هذه أجهزة كمبيوتر يمكنك إنشاؤها في السحابة والوصول إليها عبر الإنترنت. يمكنك إنشاء جهاز افتراضي Linux يحتوي على IoT Edge مثبت. اتبع [دليل إنشاء جهاز افتراضي يشغل IoT Edge](vm-iotedge.md) للحصول على التعليمات حول كيفية القيام بذلك.

## تصدير النموذج الخاص بك

لتشغيل المصنف على الحافة، يجب تصديره من Custom Vision. يمكن لـ Custom Vision إنشاء نوعين من النماذج - النماذج القياسية والنماذج المدمجة. النماذج المدمجة تستخدم تقنيات مختلفة لتقليل حجم النموذج، مما يجعله صغيرًا بما يكفي ليتم تنزيله ونشره على أجهزة إنترنت الأشياء.

عندما قمت بإنشاء مصنف الصور، استخدمت مجال *الطعام*، وهو نسخة من النموذج محسنة للتدريب على صور الطعام. في Custom Vision، يمكنك تغيير مجال مشروعك، باستخدام بيانات التدريب الخاصة بك لتدريب نموذج جديد بالمجال الجديد. جميع المجالات المدعومة بواسطة Custom Vision متوفرة كنسخ قياسية ومدمجة.

### المهمة - تدريب النموذج الخاص بك باستخدام مجال الطعام (المدمج)
1. افتح بوابة Custom Vision على [CustomVision.ai](https://customvision.ai) وقم بتسجيل الدخول إذا لم تكن قد فتحتها بالفعل. ثم افتح مشروعك `fruit-quality-detector`.

1. اختر زر **الإعدادات** (رمز ⚙).

1. في قائمة *Domains*، اختر *Food (compact)*.

1. تحت *Export Capabilities*، تأكد من اختيار *Basic platforms (Tensorflow, CoreML, ONNX, ...)*.

1. في أسفل صفحة الإعدادات، اختر **حفظ التغييرات**.

1. أعد تدريب النموذج باستخدام زر **Train**، واختر *Quick training*.

### المهمة - تصدير النموذج الخاص بك

بمجرد تدريب النموذج، يجب تصديره كحاوية.

1. اختر علامة التبويب **Performance**، وابحث عن أحدث تكرار تم تدريبه باستخدام المجال المضغوط.

1. اختر زر **Export** في الأعلى.

1. اختر **DockerFile**، ثم اختر الإصدار الذي يتناسب مع جهاز الحافة الخاص بك:

    * إذا كنت تستخدم IoT Edge على جهاز كمبيوتر يعمل بنظام Linux أو Windows أو جهاز افتراضي، اختر إصدار *Linux*.
    * إذا كنت تستخدم IoT Edge على Raspberry Pi، اختر إصدار *ARM (Raspberry Pi 3)*.

> 🎓 Docker هو أحد الأدوات الأكثر شهرة لإدارة الحاويات، وDockerFile هو مجموعة من التعليمات حول كيفية إعداد الحاوية.

1. اختر **Export** ليقوم Custom Vision بإنشاء الملفات ذات الصلة، ثم **Download** لتنزيلها في ملف مضغوط.

1. احفظ الملفات على جهاز الكمبيوتر الخاص بك، ثم فك ضغط المجلد.

## إعداد الحاوية للنشر

![الحاويات تُبنى ثم تُدفع إلى سجل الحاويات، ثم تُنشر من سجل الحاويات إلى جهاز الحافة باستخدام IoT Edge](../../../../../translated_images/ar/container-edge-flow.c246050dd60ceefd.webp)

بمجرد تنزيل النموذج الخاص بك، يجب بناؤه في حاوية، ثم دفعه إلى سجل الحاويات - وهو موقع عبر الإنترنت حيث يمكنك تخزين الحاويات. يمكن لـ IoT Edge بعد ذلك تنزيل الحاوية من السجل ودفعها إلى جهازك.

![شعار Azure Container Registry](../../../../../translated_images/ar/azure-container-registry-logo.09494206991d4b29.webp)

سجل الحاويات الذي ستستخدمه في هذا الدرس هو Azure Container Registry. هذه ليست خدمة مجانية، لذا لتوفير المال تأكد من [تنظيف مشروعك](../../../clean-up.md) بمجرد الانتهاء.

> 💁 يمكنك الاطلاع على تكاليف استخدام Azure Container Registry في [صفحة تسعير Azure Container Registry](https://azure.microsoft.com/pricing/details/container-registry/?WT.mc_id=academic-17441-jabenn).

### المهمة - تثبيت Docker

لبناء ونشر المصنف، قد تحتاج إلى تثبيت [Docker](https://www.docker.com/).

ستحتاج إلى القيام بذلك فقط إذا كنت تخطط لبناء الحاوية من جهاز مختلف عن الجهاز الذي قمت بتثبيت IoT Edge عليه - كجزء من تثبيت IoT Edge، يتم تثبيت Docker تلقائيًا.

1. إذا كنت تبني الحاوية على جهاز مختلف عن جهاز IoT Edge الخاص بك، اتبع تعليمات تثبيت Docker على [صفحة تثبيت Docker](https://www.docker.com/products/docker-desktop) لتثبيت Docker Desktop أو محرك Docker. تأكد من تشغيله بعد التثبيت.

### المهمة - إنشاء مورد سجل الحاويات

1. قم بتشغيل الأمر التالي من Terminal أو موجه الأوامر لإنشاء مورد سجل الحاويات في Azure:

    ```sh
    az acr create --resource-group fruit-quality-detector \
                  --sku Basic \
                  --name <Container registry name>
    ```

    استبدل `<Container registry name>` باسم فريد لسجل الحاويات الخاص بك، باستخدام الأحرف والأرقام فقط. اجعل الاسم مستندًا إلى `fruitqualitydetector`. يصبح هذا الاسم جزءًا من عنوان URL للوصول إلى سجل الحاويات، لذا يجب أن يكون فريدًا عالميًا.

1. قم بتسجيل الدخول إلى سجل الحاويات في Azure باستخدام الأمر التالي:

    ```sh
    az acr login --name <Container registry name>
    ```

    استبدل `<Container registry name>` بالاسم الذي استخدمته لسجل الحاويات الخاص بك.

1. قم بتفعيل وضع المسؤول لسجل الحاويات الخاص بك لتتمكن من إنشاء كلمة مرور باستخدام الأمر التالي:

    ```sh
    az acr update --admin-enabled true \
                 --name <Container registry name>
    ```

    استبدل `<Container registry name>` بالاسم الذي استخدمته لسجل الحاويات الخاص بك.

1. قم بإنشاء كلمات مرور لسجل الحاويات الخاص بك باستخدام الأمر التالي:

    ```sh
     az acr credential renew --password-name password \
                             --output table \
                             --name <Container registry name>
    ```

    استبدل `<Container registry name>` بالاسم الذي استخدمته لسجل الحاويات الخاص بك.

    قم بنسخ قيمة `PASSWORD`، حيث ستحتاج إليها لاحقًا.

### المهمة - بناء الحاوية الخاصة بك

ما قمت بتنزيله من Custom Vision هو DockerFile يحتوي على تعليمات حول كيفية بناء الحاوية، إلى جانب كود التطبيق الذي سيتم تشغيله داخل الحاوية لاستضافة نموذج الرؤية المخصص الخاص بك، مع واجهة REST API لاستدعائه. يمكنك استخدام Docker لبناء حاوية مميزة من DockerFile، ثم دفعها إلى سجل الحاويات الخاص بك.

> 🎓 يتم إعطاء الحاويات علامة تحدد اسمًا وإصدارًا لها. عندما تحتاج إلى تحديث حاوية، يمكنك بناؤها بنفس العلامة ولكن بإصدار أحدث.

1. افتح Terminal أو موجه الأوامر وانتقل إلى النموذج الذي تم فك ضغطه والذي قمت بتنزيله من Custom Vision.

1. قم بتشغيل الأمر التالي لبناء الصورة ووضع علامة عليها:

    ```sh
    docker build --platform <platform> -t <Container registry name>.azurecr.io/classifier:v1 .
    ```

    استبدل `<platform>` بالمنصة التي ستعمل عليها هذه الحاوية. إذا كنت تستخدم IoT Edge على Raspberry Pi، قم بتعيين هذا إلى `linux/armhf`، وإلا قم بتعيينه إلى `linux/amd64`.

    > 💁 إذا كنت تقوم بتشغيل هذا الأمر من الجهاز الذي تقوم بتشغيل IoT Edge منه، مثل تشغيله من Raspberry Pi، يمكنك حذف الجزء `--platform <platform>` حيث يتم افتراض المنصة الحالية.

    استبدل `<Container registry name>` بالاسم الذي استخدمته لسجل الحاويات الخاص بك.

    > 💁 إذا كنت تعمل على Linux أو Raspberry Pi OS، قد تحتاج إلى استخدام `sudo` لتشغيل هذا الأمر.

    سيقوم Docker ببناء الصورة، وتكوين جميع البرامج اللازمة. سيتم بعد ذلك وضع علامة على الصورة كـ `classifier:v1`.

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

### المهمة - دفع الحاوية إلى سجل الحاويات الخاص بك

1. استخدم الأمر التالي لدفع الحاوية إلى سجل الحاويات الخاص بك:

    ```sh
    docker push <Container registry name>.azurecr.io/classifier:v1
    ```

    استبدل `<Container registry name>` بالاسم الذي استخدمته لسجل الحاويات الخاص بك.

    > 💁 إذا كنت تعمل على Linux، قد تحتاج إلى استخدام `sudo` لتشغيل هذا الأمر.

    سيتم دفع الحاوية إلى سجل الحاويات.

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

1. للتحقق من الدفع، يمكنك عرض قائمة الحاويات في السجل الخاص بك باستخدام الأمر التالي:

    ```sh
    az acr repository list --output table \
                           --name <Container registry name> 
    ```

    استبدل `<Container registry name>` بالاسم الذي استخدمته لسجل الحاويات الخاص بك.

    ```output
    ➜  d4ccc45da0bb478bad287128e1274c3c.DockerFile.Linux az acr repository list --name fruitqualitydetectorjimb --output table
    Result
    ----------
    classifier
    ```

    سترى المصنف الخاص بك مدرجًا في الإخراج.

## نشر الحاوية الخاصة بك

يمكن الآن نشر الحاوية الخاصة بك إلى جهاز IoT Edge الخاص بك. للنشر، تحتاج إلى تعريف ملف نشر - وهو مستند JSON يسرد الوحدات التي سيتم نشرها إلى جهاز الحافة.

### المهمة - إنشاء ملف النشر

1. قم بإنشاء ملف جديد يسمى `deployment.json` في مكان ما على جهاز الكمبيوتر الخاص بك.

1. أضف ما يلي إلى هذا الملف:

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

    > 💁 يمكنك العثور على هذا الملف في مجلد [code-deployment/deployment](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-deployment/deployment).

    استبدل الثلاثة أمثلة لـ `<Container registry name>` بالاسم الذي استخدمته لسجل الحاويات الخاص بك. أحدها في قسم `ImageClassifier`، والآخران في قسم `registryCredentials`.

    استبدل `<Container registry password>` في قسم `registryCredentials` بكلمة مرور سجل الحاويات الخاص بك.

1. من المجلد الذي يحتوي على ملف النشر الخاص بك، قم بتشغيل الأمر التالي:

    ```sh
    az iot edge set-modules --device-id fruit-quality-detector-edge \
                            --content deployment.json \
                            --hub-name <hub_name>
    ```

    استبدل `<hub_name>` باسم IoT Hub الخاص بك.

    سيتم نشر وحدة المصنف إلى جهاز الحافة الخاص بك.

### المهمة - التحقق من تشغيل المصنف

1. قم بالاتصال بجهاز IoT Edge:

    * إذا كنت تستخدم Raspberry Pi لتشغيل IoT Edge، قم بالاتصال باستخدام ssh إما من Terminal الخاص بك، أو عبر جلسة SSH عن بُعد في VS Code.
    * إذا كنت تقوم بتشغيل IoT Edge في حاوية Linux على Windows، اتبع الخطوات في [دليل التحقق من التكوين الناجح](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge-on-windows?WT.mc_id=academic-17441-jabenn&view=iotedge-2018-06&tabs=powershell#verify-successful-configuration) للاتصال بجهاز IoT Edge.
    * إذا كنت تقوم بتشغيل IoT Edge على جهاز افتراضي، يمكنك SSH إلى الجهاز باستخدام `adminUsername` و`password` الذي قمت بتعيينه عند إنشاء الجهاز الافتراضي، واستخدام إما عنوان IP أو اسم DNS:

        ```sh
        ssh <adminUsername>@<IP address>
        ```

        أو:

        ```sh
        ssh <adminUsername>@<DNS Name>
        ```

        أدخل كلمة المرور الخاصة بك عند الطلب.

1. بمجرد الاتصال، قم بتشغيل الأمر التالي للحصول على قائمة وحدات IoT Edge:

    ```sh
    iotedge list
    ```

    > 💁 قد تحتاج إلى تشغيل هذا الأمر باستخدام `sudo`.

    سترى الوحدات النمطية قيد التشغيل:

    ```output
    jim@fruit-quality-detector-jimb:~$ iotedge list
    NAME             STATUS           DESCRIPTION      CONFIG
    ImageClassifier  running          Up 42 minutes    fruitqualitydetectorjimb.azurecr.io/classifier:v1
    edgeAgent        running          Up 42 minutes    mcr.microsoft.com/azureiotedge-agent:1.1
    edgeHub          running          Up 42 minutes    mcr.microsoft.com/azureiotedge-hub:1.1
    ```

1. تحقق من السجلات لوحدة المصنف باستخدام الأمر التالي:

    ```sh
    iotedge logs ImageClassifier
    ```

    > 💁 قد تحتاج إلى تشغيل هذا الأمر باستخدام `sudo`.

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

### المهمة - اختبار المصنف

1. يمكنك استخدام CURL لاختبار المصنف باستخدام عنوان IP أو اسم المضيف للجهاز الذي يقوم بتشغيل وكيل IoT Edge. ابحث عن عنوان IP:

    * إذا كنت على نفس الجهاز الذي يعمل عليه IoT Edge، يمكنك استخدام `localhost` كاسم المضيف.
    * إذا كنت تستخدم جهاز افتراضي، يمكنك استخدام إما عنوان IP أو اسم DNS للجهاز الافتراضي.
    * خلاف ذلك، يمكنك الحصول على عنوان IP للجهاز الذي يعمل عليه IoT Edge:
      * على Windows 10، اتبع [دليل العثور على عنوان IP الخاص بك](https://support.microsoft.com/windows/find-your-ip-address-f21a9bbc-c582-55cd-35e0-73431160a1b9?WT.mc_id=academic-17441-jabenn).
      * على macOS، اتبع [كيفية العثور على عنوان IP الخاص بك على Mac](https://www.hellotech.com/guide/for/how-to-find-ip-address-on-mac).
      * على Linux، اتبع القسم الخاص بالعثور على عنوان IP الخاص بك في [كيفية العثور على عنوان IP الخاص بك في Linux](https://opensource.com/article/18/5/how-find-ip-address-linux).

1. يمكنك اختبار الحاوية باستخدام ملف محلي عن طريق تشغيل أمر CURL التالي:

    ```sh
    curl --location \
         --request POST 'http://<IP address or name>/image' \
         --header 'Content-Type: image/png' \
         --data-binary '@<file_Name>' 
    ```

    استبدل `<IP address or name>` بعنوان IP أو اسم المضيف للجهاز الذي يقوم بتشغيل IoT Edge. استبدل `<file_Name>` باسم الملف للاختبار.

    سترى نتائج التنبؤ في الإخراج:

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

    > 💁 لا حاجة لتوفير مفتاح التنبؤ هنا، حيث لا يتم استخدام مورد Azure. بدلاً من ذلك، يتم تكوين الأمان على الشبكة الداخلية بناءً على احتياجات الأمان الداخلية، بدلاً من الاعتماد على نقطة نهاية عامة ومفتاح API.

## استخدام جهاز IoT Edge الخاص بك

الآن بعد أن تم نشر المصنف الخاص بك إلى جهاز IoT Edge، يمكنك استخدامه من جهاز IoT الخاص بك.

### المهمة - استخدام جهاز IoT Edge الخاص بك

اعمل من خلال الدليل المناسب لتصنيف الصور باستخدام مصنف IoT Edge:

* [Arduino - Wio Terminal](wio-terminal.md)
* [كمبيوتر أحادي اللوحة - Raspberry Pi/جهاز IoT افتراضي](single-board-computer.md)

### إعادة تدريب النموذج

أحد العيوب لتشغيل مصنفات الصور على IoT Edge هو أنها غير متصلة بمشروع Custom Vision الخاص بك. إذا نظرت إلى علامة التبويب **Predictions** في Custom Vision، لن ترى الصور التي تم تصنيفها باستخدام المصنف المستند إلى Edge.

هذا هو السلوك المتوقع - الصور لا تُرسل إلى السحابة للتصنيف، لذا لن تكون متاحة في السحابة. أحد المزايا لاستخدام IoT Edge هو الخصوصية، مما يضمن أن الصور لا تغادر شبكتك، ميزة أخرى هي القدرة على العمل دون اتصال، لذا لا حاجة لتحميل الصور عندما لا يكون الجهاز متصلًا بالإنترنت. العيب هو تحسين النموذج الخاص بك - ستحتاج إلى تنفيذ طريقة أخرى لتخزين الصور التي يمكن إعادة تصنيفها يدويًا لتحسين وإعادة تدريب المصنف.

✅ فكر في طرق لتحميل الصور لإعادة تدريب المصنف.

---

## 🚀 التحدي

تشغيل نماذج الذكاء الاصطناعي على أجهزة الحافة يمكن أن يكون أسرع من السحابة - القفزة الشبكية أقصر. يمكن أن تكون أيضًا أبطأ حيث أن الأجهزة التي تشغل النموذج قد لا تكون قوية مثل السحابة.

قم ببعض القياسات وقارن إذا كانت المكالمة إلى جهاز الحافة الخاص بك أسرع أو أبطأ من المكالمة إلى السحابة؟ فكر في أسباب تشرح الفرق، أو عدم وجود فرق. ابحث عن طرق لتشغيل نماذج الذكاء الاصطناعي بشكل أسرع على الحافة باستخدام أجهزة متخصصة.

## اختبار ما بعد المحاضرة

[اختبار ما بعد المحاضرة](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/34)

## المراجعة والدراسة الذاتية

* اقرأ المزيد عن الحاويات على [صفحة الافتراضية على مستوى نظام التشغيل في ويكيبيديا](https://wikipedia.org/wiki/OS-level_virtualization).
* اقرأ المزيد عن الحوسبة الطرفية، مع التركيز على كيفية مساهمة تقنية 5G في توسيع نطاق الحوسبة الطرفية في [مقال "ما هي الحوسبة الطرفية ولماذا هي مهمة؟" على موقع NetworkWorld](https://www.networkworld.com/article/3224893/what-is-edge-computing-and-how-its-changing-the-network.html)
* تعرف على المزيد حول تشغيل خدمات الذكاء الاصطناعي في IoT Edge من خلال مشاهدة [حلقة "تعلم كيفية استخدام Azure IoT Edge على خدمة ذكاء اصطناعي جاهزة على الطرف للكشف عن اللغة" من برنامج Learn Live على قناة Microsoft Channel9](https://channel9.msdn.com/Shows/Learn-Live/Sharpen-Your-AI-Edge-Skills-Episode-4-Learn-How-to-Use-Azure-IoT-Edge-on-a-Pre-Built-AI-Service-on-t?WT.mc_id=academic-17441-jabenn)

## المهمة

[تشغيل خدمات أخرى على الطرف](assignment.md)

---

**إخلاء المسؤولية**:  
تم ترجمة هذا المستند باستخدام خدمة الترجمة بالذكاء الاصطناعي [Co-op Translator](https://github.com/Azure/co-op-translator). بينما نسعى لتحقيق الدقة، يرجى العلم أن الترجمات الآلية قد تحتوي على أخطاء أو معلومات غير دقيقة. يجب اعتبار المستند الأصلي بلغته الأصلية المصدر الرسمي. للحصول على معلومات حاسمة، يُوصى بالاستعانة بترجمة بشرية احترافية. نحن غير مسؤولين عن أي سوء فهم أو تفسيرات خاطئة ناتجة عن استخدام هذه الترجمة.