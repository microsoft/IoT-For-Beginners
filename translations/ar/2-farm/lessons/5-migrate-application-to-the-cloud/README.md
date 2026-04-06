# نقل منطق تطبيقك إلى السحابة

![رسم توضيحي لهذه الدرس](../../../../../translated_images/ar/lesson-9.dfe99c8e891f48e1.webp)

> رسم توضيحي من [نيتيا ناراسيمهان](https://github.com/nitya). انقر على الصورة لعرض نسخة أكبر.

تم تقديم هذا الدرس كجزء من [مشروع إنترنت الأشياء للمبتدئين - سلسلة الزراعة الرقمية](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) من [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn).

[![تحكم في جهاز إنترنت الأشياء الخاص بك باستخدام كود بدون خادم](https://img.youtube.com/vi/VVZDcs5u1_I/0.jpg)](https://youtu.be/VVZDcs5u1_I)

## اختبار ما قبل المحاضرة

[اختبار ما قبل المحاضرة](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/17)

## المقدمة

في الدرس السابق، تعلمت كيفية توصيل جهاز مراقبة رطوبة التربة الخاص بالنباتات والتحكم في المرحل بخدمة إنترنت الأشياء المستندة إلى السحابة. الخطوة التالية هي نقل الكود الخادمي الذي يتحكم في توقيت المرحل إلى السحابة. في هذا الدرس، ستتعلم كيفية القيام بذلك باستخدام الوظائف بدون خادم.

في هذا الدرس سنتناول:

* [ما هي الوظائف بدون خادم؟](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [إنشاء تطبيق بدون خادم](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [إنشاء مشغل حدث IoT Hub](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [إرسال طلبات الطرق المباشرة من الكود بدون خادم](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [نشر الكود بدون خادم إلى السحابة](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)

## ما هي الوظائف بدون خادم؟

الوظائف بدون خادم، أو الحوسبة بدون خادم، تتضمن إنشاء كتل صغيرة من الكود يتم تشغيلها في السحابة استجابة لأنواع مختلفة من الأحداث. عندما يحدث الحدث، يتم تشغيل الكود الخاص بك ويتم تمرير بيانات حول الحدث إليه. يمكن أن تأتي هذه الأحداث من أشياء متعددة، بما في ذلك طلبات الويب، الرسائل الموضوعة في قائمة انتظار، تغييرات البيانات في قاعدة بيانات، أو الرسائل المرسلة إلى خدمة إنترنت الأشياء من أجهزة إنترنت الأشياء.

![الأحداث المرسلة من خدمة إنترنت الأشياء إلى خدمة بدون خادم، تتم معالجتها جميعًا في نفس الوقت بواسطة وظائف متعددة](../../../../../translated_images/ar/iot-messages-to-serverless.0194da1cc0732bb7.webp)

> 💁 إذا كنت قد استخدمت مشغلات قواعد البيانات من قبل، يمكنك التفكير في هذا على أنه نفس الشيء، حيث يتم تشغيل الكود بواسطة حدث مثل إدخال صف.

![عندما يتم إرسال العديد من الأحداث في نفس الوقت، تقوم الخدمة بدون خادم بالتوسع لتشغيلها جميعًا في نفس الوقت](../../../../../translated_images/ar/serverless-scaling.f8c769adf0413fd1.webp)

يتم تشغيل الكود الخاص بك فقط عندما يحدث الحدث، ولا يتم الاحتفاظ بالكود الخاص بك قيد التشغيل في أوقات أخرى. عندما يحدث الحدث، يتم تحميل الكود الخاص بك وتشغيله. هذا يجعل الوظائف بدون خادم قابلة للتوسع بشكل كبير - إذا حدثت العديد من الأحداث في نفس الوقت، يمكن لموفر السحابة تشغيل الوظيفة الخاصة بك بقدر ما تحتاج في نفس الوقت عبر أي خوادم متاحة لديهم. الجانب السلبي لهذا هو أنه إذا كنت بحاجة إلى مشاركة المعلومات بين الأحداث، يجب عليك حفظها في مكان ما مثل قاعدة بيانات بدلاً من تخزينها في الذاكرة.

يتم كتابة الكود الخاص بك كدالة تأخذ تفاصيل حول الحدث كمعامل. يمكنك استخدام مجموعة واسعة من لغات البرمجة لكتابة هذه الوظائف بدون خادم.

> 🎓 تُعرف الوظائف بدون خادم أيضًا باسم "الوظائف كخدمة" (FaaS) حيث يتم تنفيذ كل مشغل حدث كدالة في الكود.

على الرغم من الاسم، فإن الوظائف بدون خادم تستخدم بالفعل خوادم. التسمية تعني أنك كمطور لا تهتم بالخوادم اللازمة لتشغيل الكود الخاص بك، كل ما تهتم به هو أن الكود الخاص بك يتم تشغيله استجابة لحدث. يوفر موفر السحابة *بيئة تشغيل بدون خادم* تدير تخصيص الخوادم، الشبكات، التخزين، وحدة المعالجة المركزية، الذاكرة وكل شيء آخر مطلوب لتشغيل الكود الخاص بك. هذا النموذج يعني أنك لا تدفع لكل خادم للخدمة، حيث لا يوجد خادم. بدلاً من ذلك، تدفع مقابل الوقت الذي يتم فيه تشغيل الكود الخاص بك، وكمية الذاكرة المستخدمة.

> 💰 الوظائف بدون خادم هي واحدة من أرخص الطرق لتشغيل الكود في السحابة. على سبيل المثال، في وقت كتابة هذا النص، يسمح أحد موفري السحابة لجميع الوظائف بدون خادم الخاصة بك بالتنفيذ مليون مرة شهريًا قبل أن يبدأوا في فرض رسوم عليك، وبعد ذلك يفرضون 0.20 دولار أمريكي لكل مليون تنفيذ. عندما لا يتم تشغيل الكود الخاص بك، لا تدفع شيئًا.

كمطور إنترنت الأشياء، فإن نموذج الوظائف بدون خادم مثالي. يمكنك كتابة دالة يتم استدعاؤها استجابة للرسائل المرسلة من أي جهاز إنترنت الأشياء متصل بخدمة إنترنت الأشياء المستضافة في السحابة. الكود الخاص بك سيتعامل مع جميع الرسائل المرسلة، ولكنه سيعمل فقط عند الحاجة.

✅ ألقِ نظرة على الكود الذي كتبته ككود خادمي يستمع للرسائل عبر MQTT. كيف يمكن أن يعمل هذا في السحابة باستخدام الوظائف بدون خادم؟ كيف تعتقد أن الكود قد يحتاج إلى التغيير لدعم الحوسبة بدون خادم؟

> 💁 نموذج الوظائف بدون خادم ينتقل إلى خدمات سحابية أخرى بالإضافة إلى تشغيل الكود. على سبيل المثال، قواعد البيانات بدون خادم متوفرة في السحابة باستخدام نموذج تسعير بدون خادم حيث تدفع لكل طلب يتم إجراؤه ضد قاعدة البيانات، مثل استعلام أو إدخال، عادةً باستخدام تسعير يعتمد على مقدار العمل المطلوب لخدمة الطلب. على سبيل المثال، استعلام بسيط عن صف واحد باستخدام مفتاح أساسي سيكلف أقل من عملية معقدة تنضم إلى العديد من الجداول وتعيد آلاف الصفوف.

## إنشاء تطبيق بدون خادم

خدمة الحوسبة بدون خادم من مايكروسوفت تُعرف باسم Azure Functions.

![شعار Azure Functions](../../../../../translated_images/ar/azure-functions-logo.1cfc8e3204c9c44a.webp)

الفيديو القصير أدناه يقدم نظرة عامة على Azure Functions:

[![فيديو نظرة عامة على Azure Functions](https://img.youtube.com/vi/8-jz5f_JyEQ/0.jpg)](https://www.youtube.com/watch?v=8-jz5f_JyEQ)

> 🎥 انقر على الصورة أعلاه لمشاهدة الفيديو

✅ خذ لحظة للبحث وقراءة نظرة عامة على Azure Functions في [وثائق Microsoft Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-overview?WT.mc_id=academic-17441-jabenn).

لإنشاء Azure Functions، تبدأ بتطبيق Azure Functions بلغة البرمجة التي تختارها. يدعم Azure Functions بشكل افتراضي Python، JavaScript، TypeScript، C#، F#، Java، وPowerShell. في هذا الدرس، ستتعلم كيفية كتابة تطبيق Azure Functions باستخدام Python.

> 💁 يدعم Azure Functions أيضًا معالجات مخصصة بحيث يمكنك كتابة الوظائف بأي لغة تدعم طلبات HTTP، بما في ذلك اللغات القديمة مثل COBOL.

تتكون تطبيقات الوظائف من واحد أو أكثر من *المشغلات* - وهي وظائف تستجيب للأحداث. يمكنك أن تحتوي على مشغلات متعددة داخل تطبيق الوظائف الواحد، تشترك جميعها في نفس الإعدادات. على سبيل المثال، في ملف الإعدادات الخاص بتطبيق الوظائف، يمكنك وضع تفاصيل الاتصال بـ IoT Hub الخاص بك، ويمكن لجميع الوظائف في التطبيق استخدام هذا الاتصال للاستماع إلى الأحداث.

### المهمة - تثبيت أدوات Azure Functions

> في وقت كتابة هذا النص، أدوات كود Azure Functions ليست مدعومة بالكامل على أجهزة Apple Silicon مع مشاريع Python. ستحتاج إلى استخدام جهاز Mac بمعالج Intel، أو جهاز كمبيوتر يعمل بنظام Windows، أو جهاز كمبيوتر يعمل بنظام Linux بدلاً من ذلك.

إحدى الميزات الرائعة لـ Azure Functions هي أنه يمكنك تشغيلها محليًا. نفس بيئة التشغيل المستخدمة في السحابة يمكن تشغيلها على جهاز الكمبيوتر الخاص بك، مما يسمح لك بكتابة كود يستجيب لرسائل إنترنت الأشياء وتشغيله محليًا. يمكنك حتى تصحيح الكود الخاص بك أثناء معالجة الأحداث. بمجرد أن تكون راضيًا عن الكود الخاص بك، يمكن نشره إلى السحابة.

أدوات Azure Functions متوفرة كواجهة سطر أوامر (CLI)، تُعرف باسم Azure Functions Core Tools.

1. قم بتثبيت أدوات Azure Functions Core Tools باتباع التعليمات الموجودة في [وثائق Azure Functions Core Tools](https://docs.microsoft.com/azure/azure-functions/functions-run-local?WT.mc_id=academic-17441-jabenn).

2. قم بتثبيت إضافة Azure Functions لـ VS Code. توفر هذه الإضافة دعمًا لإنشاء وتصحيح ونشر وظائف Azure. راجع [وثائق إضافة Azure Functions](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-azuretools.vscode-azurefunctions) للحصول على تعليمات حول تثبيت هذه الإضافة في VS Code.

عندما تقوم بنشر تطبيق Azure Functions الخاص بك إلى السحابة، فإنه يحتاج إلى استخدام كمية صغيرة من التخزين السحابي لتخزين أشياء مثل ملفات التطبيق وملفات السجل. عندما تقوم بتشغيل تطبيق الوظائف الخاص بك محليًا، لا يزال يتعين عليك الاتصال بالتخزين السحابي، ولكن بدلاً من استخدام التخزين السحابي الفعلي، يمكنك استخدام محاكي تخزين يسمى [Azurite](https://github.com/Azure/Azurite). يعمل هذا المحاكي محليًا ولكنه يتصرف مثل التخزين السحابي.

> 🎓 في Azure، التخزين الذي تستخدمه Azure Functions هو حساب تخزين Azure. يمكن لهذه الحسابات تخزين الملفات، الكتل، البيانات في الجداول أو البيانات في قوائم الانتظار. يمكنك مشاركة حساب تخزين واحد بين العديد من التطبيقات، مثل تطبيق وظائف وتطبيق ويب.

1. Azurite هو تطبيق Node.js، لذا ستحتاج إلى تثبيت Node.js. يمكنك العثور على تعليمات التنزيل والتثبيت على [موقع Node.js](https://nodejs.org/). إذا كنت تستخدم جهاز Mac، يمكنك أيضًا تثبيته من [Homebrew](https://formulae.brew.sh/formula/node).

2. قم بتثبيت Azurite باستخدام الأمر التالي (`npm` هو أداة يتم تثبيتها عند تثبيت Node.js):

    ```sh
    npm install -g azurite
    ```

3. قم بإنشاء مجلد يسمى `azurite` ليستخدمه Azurite لتخزين البيانات:

    ```sh
    mkdir azurite
    ```

4. قم بتشغيل Azurite، مع تمرير هذا المجلد الجديد:

    ```sh
    azurite --location azurite
    ```

    سيبدأ محاكي التخزين Azurite وسيكون جاهزًا لاتصال بيئة التشغيل المحلية للوظائف.

    ```output
    ➜  ~ azurite --location azurite  
    Azurite Blob service is starting at http://127.0.0.1:10000
    Azurite Blob service is successfully listening at http://127.0.0.1:10000
    Azurite Queue service is starting at http://127.0.0.1:10001
    Azurite Queue service is successfully listening at http://127.0.0.1:10001
    Azurite Table service is starting at http://127.0.0.1:10002
    Azurite Table service is successfully listening at http://127.0.0.1:10002
    ```

### المهمة - إنشاء مشروع Azure Functions

يمكن استخدام CLI الخاص بـ Azure Functions لإنشاء تطبيق وظائف جديد.

1. قم بإنشاء مجلد لتطبيق الوظائف الخاص بك وانتقل إليه. قم بتسميته `soil-moisture-trigger`:

    ```sh
    mkdir soil-moisture-trigger
    cd soil-moisture-trigger
    ```

2. قم بإنشاء بيئة افتراضية لـ Python داخل هذا المجلد:

    ```sh
    python3 -m venv .venv
    ```

3. قم بتفعيل البيئة الافتراضية:

    * على Windows:
        * إذا كنت تستخدم Command Prompt، أو Command Prompt من خلال Windows Terminal، قم بتشغيل:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * إذا كنت تستخدم PowerShell، قم بتشغيل:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

    * على macOS أو Linux، قم بتشغيل:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 يجب تشغيل هذه الأوامر من نفس الموقع الذي قمت فيه بتشغيل الأمر لإنشاء البيئة الافتراضية. لن تحتاج أبدًا إلى الانتقال إلى مجلد `.venv`، يجب عليك دائمًا تشغيل أمر التفعيل وأي أوامر لتثبيت الحزم أو تشغيل الكود من المجلد الذي كنت فيه عند إنشاء البيئة الافتراضية.

4. قم بتشغيل الأمر التالي لإنشاء تطبيق وظائف داخل هذا المجلد:

    ```sh
    func init --worker-runtime python soil-moisture-trigger
    ```

    سيؤدي هذا إلى إنشاء ثلاثة ملفات داخل المجلد الحالي:

    * `host.json` - هذا المستند JSON يحتوي على إعدادات تطبيق الوظائف الخاص بك. لن تحتاج إلى تعديل هذه الإعدادات.
    * `local.settings.json` - هذا المستند JSON يحتوي على الإعدادات التي سيستخدمها التطبيق عند التشغيل محليًا، مثل سلاسل الاتصال بـ IoT Hub. هذه الإعدادات محلية فقط، ولا ينبغي إضافتها إلى التحكم في الشيفرة المصدرية. عندما تقوم بنشر التطبيق إلى السحابة، لن يتم نشر هذه الإعدادات، بدلاً من ذلك سيتم تحميل الإعدادات الخاصة بك من إعدادات التطبيق. سيتم تغطية هذا لاحقًا في هذا الدرس.
    * `requirements.txt` - هذا هو [ملف متطلبات Pip](https://pip.p
> ⚠️ إذا ظهرت لك إشعار جدار الحماية، امنح الوصول لأن تطبيق `func` يحتاج إلى القدرة على القراءة والكتابة على شبكتك.
> ⚠️ إذا كنت تستخدم macOS، قد تظهر تحذيرات في المخرجات:
>
> ```output
    > (.venv) ➜  soil-moisture-trigger func start
    > Found Python version 3.9.1 (python3).
    >
    > Azure Functions Core Tools
    > Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    > Function Runtime Version: 3.0.15417.0
    >
    > [2021-06-16T08:18:28.315Z] Cannot create directory for shared memory usage: /dev/shm/AzureFunctions
    > [2021-06-16T08:18:28.316Z] System.IO.FileSystem: Access to the path '/dev/shm/AzureFunctions' is denied. Operation not permitted.
    > [2021-06-16T08:18:30.361Z] No job functions found.
    > ```
>
> يمكنك تجاهل هذه التحذيرات طالما أن تطبيق Functions يعمل بشكل صحيح ويعرض الوظائف الجارية. كما هو مذكور في [هذا السؤال على Microsoft Docs Q&A](https://docs.microsoft.com/answers/questions/396617/azure-functions-core-tools-error-osx-devshmazurefu.html?WT.mc_id=academic-17441-jabenn)، يمكن تجاهلها.

1. أوقف تشغيل تطبيق Functions بالضغط على `ctrl+c`.

1. افتح المجلد الحالي في VS Code، إما عن طريق فتح VS Code ثم فتح هذا المجلد، أو عن طريق تشغيل الأمر التالي:

    ```sh
    code .
    ```

    سيكتشف VS Code مشروع Functions الخاص بك ويعرض إشعارًا يقول:

    ```output
    Detected an Azure Functions Project in folder "soil-moisture-trigger" that may have been created outside of
    VS Code. Initialize for optimal use with VS Code?
    ```

    ![الإشعار](../../../../../translated_images/ar/vscode-azure-functions-init-notification.bd19b49229963edb.webp)

    اختر **Yes** من هذا الإشعار.

1. تأكد من أن البيئة الافتراضية لـ Python تعمل في الطرفية داخل VS Code. قم بإنهائها وأعد تشغيلها إذا لزم الأمر.

## إنشاء مشغل حدث IoT Hub

تطبيق Functions هو الإطار الخارجي لكودك الخالي من الخوادم. للرد على أحداث IoT Hub، يمكنك إضافة مشغل IoT Hub إلى هذا التطبيق. يحتاج هذا المشغل إلى الاتصال بتدفق الرسائل المرسلة إلى IoT Hub والرد عليها. للحصول على هذا التدفق من الرسائل، يجب أن يتصل المشغل بنقطة النهاية المتوافقة مع Event Hub الخاصة بـ IoT Hub.

يعتمد IoT Hub على خدمة Azure أخرى تُسمى Azure Event Hubs. Event Hubs هي خدمة تتيح إرسال واستقبال الرسائل، بينما يضيف IoT Hub ميزات إضافية للأجهزة المتصلة بالإنترنت. طريقة الاتصال لقراءة الرسائل من IoT Hub هي نفسها كما لو كنت تستخدم Event Hubs.

✅ قم ببعض البحث: اقرأ نظرة عامة على Event Hubs في [وثائق Azure Event Hubs](https://docs.microsoft.com/azure/event-hubs/event-hubs-about?WT.mc_id=academic-17441-jabenn). كيف تقارن الميزات الأساسية مع IoT Hub؟

لكي يتصل جهاز IoT بـ IoT Hub، يجب أن يستخدم مفتاحًا سريًا يضمن أن الأجهزة المصرح لها فقط يمكنها الاتصال. ينطبق نفس الأمر عند الاتصال لقراءة الرسائل، حيث سيحتاج كودك إلى سلسلة اتصال تحتوي على مفتاح سري، بالإضافة إلى تفاصيل IoT Hub.

> 💁 سلسلة الاتصال الافتراضية التي تحصل عليها تحتوي على أذونات **iothubowner**، مما يمنح أي كود يستخدمها أذونات كاملة على IoT Hub. من الأفضل أن تتصل بأقل مستوى من الأذونات المطلوبة. سيتم تغطية هذا في الدرس التالي.

بمجرد أن يتصل المشغل، سيتم استدعاء الكود داخل الوظيفة لكل رسالة يتم إرسالها إلى IoT Hub، بغض النظر عن الجهاز الذي أرسلها. سيتم تمرير الرسالة إلى المشغل كمعامل.

### المهمة - الحصول على سلسلة اتصال نقطة النهاية المتوافقة مع Event Hub

1. من الطرفية في VS Code، قم بتشغيل الأمر التالي للحصول على سلسلة الاتصال لنقطة النهاية المتوافقة مع Event Hub الخاصة بـ IoT Hub:

    ```sh
    az iot hub connection-string show --default-eventhub \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    استبدل `<hub_name>` باسم IoT Hub الذي استخدمته.

1. في VS Code، افتح ملف `local.settings.json`. أضف القيمة الإضافية التالية داخل قسم `Values`:

    ```json
    "IOT_HUB_CONNECTION_STRING": "<connection string>"
    ```

    استبدل `<connection string>` بالقيمة من الخطوة السابقة. ستحتاج إلى إضافة فاصلة بعد السطر السابق لجعل هذا JSON صالحًا.

### المهمة - إنشاء مشغل حدث

أنت الآن جاهز لإنشاء مشغل الحدث.

1. من الطرفية في VS Code، قم بتشغيل الأمر التالي من داخل مجلد `soil-moisture-trigger`:

    ```sh
    func new --name iot-hub-trigger --template "Azure Event Hub trigger"
    ```

    سيؤدي هذا إلى إنشاء وظيفة جديدة تُسمى `iot-hub-trigger`. سيتصل المشغل بنقطة النهاية المتوافقة مع Event Hub على IoT Hub، لذا يمكنك استخدام مشغل Event Hub. لا يوجد مشغل محدد لـ IoT Hub.

سيتم إنشاء مجلد داخل مجلد `soil-moisture-trigger` يُسمى `iot-hub-trigger` يحتوي على هذه الوظيفة. سيحتوي هذا المجلد على الملفات التالية:

* `__init__.py` - هذا هو ملف كود Python الذي يحتوي على المشغل، باستخدام تسمية ملفات Python القياسية لتحويل هذا المجلد إلى وحدة Python.

    سيحتوي هذا الملف على الكود التالي:

    ```python
    import logging

    import azure.functions as func


    def main(event: func.EventHubEvent):
        logging.info('Python EventHub trigger processed an event: %s',
                    event.get_body().decode('utf-8'))
    ```

    جوهر المشغل هو وظيفة `main`. يتم استدعاء هذه الوظيفة مع الأحداث من IoT Hub. تحتوي هذه الوظيفة على معامل يُسمى `event` يحتوي على `EventHubEvent`. في كل مرة يتم فيها إرسال رسالة إلى IoT Hub، يتم استدعاء هذه الوظيفة وتمرير تلك الرسالة كـ `event`، إلى جانب الخصائص التي تشبه التعليقات التوضيحية التي رأيتها في الدرس السابق.

    جوهر هذه الوظيفة يقوم بتسجيل الحدث.

* `function.json` - يحتوي هذا الملف على تكوين المشغل. التكوين الرئيسي موجود في قسم يُسمى `bindings`. الربط هو المصطلح المستخدم لوصف الاتصال بين Azure Functions والخدمات الأخرى في Azure. تحتوي هذه الوظيفة على ربط إدخال إلى Event Hub - حيث تتصل بـ Event Hub وتتلقى البيانات.

    > 💁 يمكنك أيضًا الحصول على روابط إخراج بحيث يتم إرسال مخرجات الوظيفة إلى خدمة أخرى. على سبيل المثال، يمكنك إضافة ربط إخراج إلى قاعدة بيانات وإرجاع حدث IoT Hub من الوظيفة، وسيتم إدخاله تلقائيًا في قاعدة البيانات.

    ✅ قم ببعض البحث: اقرأ عن الروابط في [وثائق مفاهيم المشغلات والروابط في Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python).

    يتضمن قسم `bindings` تكوين الربط. القيم ذات الأهمية هي:

  * `"type": "eventHubTrigger"` - يشير هذا إلى أن الوظيفة تحتاج إلى الاستماع إلى الأحداث من Event Hub
  * `"name": "events"` - هذا هو اسم المعامل المستخدم لأحداث Event Hub. يتطابق هذا مع اسم المعامل في وظيفة `main` في كود Python.
  * `"direction": "in"` - هذا هو ربط إدخال، حيث تأتي البيانات من Event Hub إلى الوظيفة
  * `"connection": ""` - يحدد هذا اسم الإعداد لقراءة سلسلة الاتصال منه. عند التشغيل محليًا، سيقرأ هذا الإعداد من ملف `local.settings.json`.

    > 💁 لا يمكن تخزين سلسلة الاتصال في ملف `function.json`، بل يجب قراءتها من الإعدادات. هذا لمنعك من كشف سلسلة الاتصال عن طريق الخطأ.

1. بسبب [خطأ في قالب Azure Functions](https://github.com/Azure/azure-functions-templates/issues/1250)، يحتوي ملف `function.json` على قيمة غير صحيحة لحقل `cardinality`. قم بتحديث هذا الحقل من `many` إلى `one`:

    ```json
    "cardinality": "one",
    ```

1. قم بتحديث قيمة `"connection"` في ملف `function.json` للإشارة إلى القيمة الجديدة التي أضفتها إلى ملف `local.settings.json`:

    ```json
    "connection": "IOT_HUB_CONNECTION_STRING",
    ```

    > 💁 تذكر - يجب أن تشير هذه القيمة إلى الإعداد، وليس أن تحتوي على سلسلة الاتصال الفعلية.

1. تحتوي سلسلة الاتصال على قيمة `eventHubName`، لذا يجب مسح القيمة الخاصة بها في ملف `function.json`. قم بتحديث هذه القيمة إلى سلسلة فارغة:

    ```json
    "eventHubName": "",
    ```

### المهمة - تشغيل مشغل الحدث

1. تأكد من أنك لا تقوم بتشغيل مراقب أحداث IoT Hub. إذا كان هذا يعمل في نفس الوقت مع تطبيق Functions، فلن يتمكن تطبيق Functions من الاتصال واستهلاك الأحداث.

    > 💁 يمكن لتطبيقات متعددة الاتصال بنقاط نهاية IoT Hub باستخدام *مجموعات مستهلكين* مختلفة. سيتم تغطية هذه في درس لاحق.

1. لتشغيل تطبيق Functions، قم بتشغيل الأمر التالي من الطرفية في VS Code:

    ```sh
    func start
    ```

    سيبدأ تطبيق Functions، وسيكتشف وظيفة `iot-hub-trigger`. بعد ذلك، سيعالج أي أحداث تم إرسالها بالفعل إلى IoT Hub خلال اليوم الماضي.

    ```output
    (.venv) ➜  soil-moisture-trigger func start
    Found Python version 3.9.1 (python3).
    
    Azure Functions Core Tools
    Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    Function Runtime Version: 3.0.15417.0
    
    Functions:
    
            iot-hub-trigger: eventHubTrigger
    
    For detailed output, run func with --verbose flag.
    [2021-05-05T02:44:07.517Z] Worker process started and initialized.
    [2021-05-05T02:44:09.202Z] Executing 'Functions.iot-hub-trigger' (Reason='(null)', Id=802803a5-eae9-4401-a1f4-176631456ce4)
    [2021-05-05T02:44:09.205Z] Trigger Details: PartitionId: 0, Offset: 1011240-1011632, EnqueueTimeUtc: 2021-05-04T19:04:04.2030000Z-2021-05-04T19:04:04.3900000Z, SequenceNumber: 2546-2547, Count: 2
    [2021-05-05T02:44:09.352Z] Python EventHub trigger processed an event: {"soil_moisture":628}
    [2021-05-05T02:44:09.354Z] Python EventHub trigger processed an event: {"soil_moisture":624}
    [2021-05-05T02:44:09.395Z] Executed 'Functions.iot-hub-trigger' (Succeeded, Id=802803a5-eae9-4401-a1f4-176631456ce4, Duration=245ms)
    ```

    سيتم إحاطة كل استدعاء للوظيفة بكتلة `Executing 'Functions.iot-hub-trigger'`/`Executed 'Functions.iot-hub-trigger'` في المخرجات، بحيث يمكنك معرفة عدد الرسائل التي تمت معالجتها في كل استدعاء للوظيفة.

1. تأكد من أن جهاز IoT الخاص بك يعمل. سترى رسائل جديدة عن رطوبة التربة تظهر في تطبيق Functions.

1. أوقف وأعد تشغيل تطبيق Functions. سترى أنه لن يعالج الرسائل السابقة مرة أخرى، بل سيعالج الرسائل الجديدة فقط.

> 💁 يدعم VS Code أيضًا تصحيح الأخطاء في وظائفك. يمكنك تعيين نقاط توقف بالنقر على الحافة بجانب بداية كل سطر من الكود، أو وضع المؤشر على سطر الكود واختيار *Run -> Toggle breakpoint*، أو الضغط على `F9`. يمكنك تشغيل المصحح باختيار *Run -> Start debugging*، أو الضغط على `F5`، أو اختيار لوحة *Run and debug* واختيار زر **Start debugging**. من خلال القيام بذلك، يمكنك رؤية تفاصيل الأحداث التي تتم معالجتها.

#### استكشاف الأخطاء وإصلاحها

* إذا حصلت على الخطأ التالي:

    ```output
    The listener for function 'Functions.iot-hub-trigger' was unable to start. Microsoft.WindowsAzure.Storage: Connection refused. System.Net.Http: Connection refused. System.Private.CoreLib: Connection refused.
    ```

    تحقق من أن Azurite يعمل وأنك قمت بتعيين `AzureWebJobsStorage` في ملف `local.settings.json` إلى `UseDevelopmentStorage=true`.

* إذا حصلت على الخطأ التالي:

    ```output
    System.Private.CoreLib: Exception while executing function: Functions.iot-hub-trigger. System.Private.CoreLib: Result: Failure Exception: AttributeError: 'list' object has no attribute 'get_body'
    ```

    تحقق من أنك قمت بتعيين `cardinality` في ملف `function.json` إلى `one`.

* إذا حصلت على الخطأ التالي:

    ```output
    Azure.Messaging.EventHubs: The path to an Event Hub may be specified as part of the connection string or as a separate value, but not both.  Please verify that your connection string does not have the `EntityPath` token if you are passing an explicit Event Hub name. (Parameter 'connectionString').
    ```

    تحقق من أنك قمت بتعيين `eventHubName` في ملف `function.json` إلى سلسلة فارغة.

## إرسال طلبات طريقة مباشرة من الكود الخالي من الخوادم

حتى الآن، يستمع تطبيق Functions الخاص بك إلى الرسائل من IoT Hub باستخدام نقطة النهاية المتوافقة مع Event Hub. الآن تحتاج إلى إرسال أوامر إلى جهاز IoT. يتم ذلك باستخدام اتصال مختلف بـ IoT Hub عبر *مدير السجل*. مدير السجل هو أداة تتيح لك رؤية الأجهزة المسجلة مع IoT Hub، والتواصل مع تلك الأجهزة عن طريق إرسال رسائل من السحابة إلى الجهاز، أو طلبات طريقة مباشرة، أو تحديث التوأم الرقمي للجهاز. يمكنك أيضًا استخدامه لتسجيل أو تحديث أو حذف أجهزة IoT من IoT Hub.

للاتصال بمدير السجل، تحتاج إلى سلسلة اتصال.

### المهمة - الحصول على سلسلة اتصال مدير السجل

1. للحصول على سلسلة الاتصال، قم بتشغيل الأمر التالي:

    ```sh
    az iot hub connection-string show --policy-name service \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    استبدل `<hub_name>` باسم IoT Hub الذي استخدمته.

    يتم طلب سلسلة الاتصال لسياسة *ServiceConnect* باستخدام المعامل `--policy-name service`. عند طلب سلسلة اتصال، يمكنك تحديد الأذونات التي ستسمح بها سلسلة الاتصال هذه. سياسة ServiceConnect تسمح لكودك بالاتصال وإرسال الرسائل إلى أجهزة IoT.

    ✅ قم ببعض البحث: اقرأ عن السياسات المختلفة في [وثائق أذونات IoT Hub](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-security#iot-hub-permissions?WT.mc_id=academic-17441-jabenn)

1. في VS Code، افتح ملف `local.settings.json`. أضف القيمة الإضافية التالية داخل قسم `Values`:

    ```json
    "REGISTRY_MANAGER_CONNECTION_STRING": "<connection string>"
    ```

    استبدل `<connection string>` بالقيمة من الخطوة السابقة. ستحتاج إلى إضافة فاصلة بعد السطر السابق لجعل هذا JSON صالحًا.

### المهمة - إرسال طلب طريقة مباشرة إلى جهاز

1. يتوفر SDK الخاص بمدير السجل عبر حزمة Pip. أضف السطر التالي إلى ملف `requirements.txt` لإضافة الاعتماد على هذه الحزمة:

    ```sh
    azure-iot-hub
    ```

1. تأكد من أن الطرفية في VS Code تحتوي على البيئة الافتراضية مفعّلة، وقم بتشغيل الأمر التالي لتثبيت حزم Pip:

    ```sh
    pip install -r requirements.txt
    ```

1. أضف الواردات التالية إلى ملف `__init__.py`:

    ```python
    import json
    import os
    from azure.iot.hub import IoTHubRegistryManager
    from azure.iot.hub.models import CloudToDeviceMethod
    ```

    هذا يستورد بعض مكتبات النظام، بالإضافة إلى المكتبات للتفاعل مع مدير السجل وإرسال طلبات الطريقة المباشرة.

1. قم بإزالة الكود من داخل طريقة `main`، ولكن احتفظ بالطريقة نفسها.

1. في طريقة `main`، أضف الكود التالي:

    ```python
    body = json.loads(event.get_body().decode('utf-8'))
    device_id = event.iothub_metadata['connection-device-id']

    logging.info(f'Received message: {body} from {device_id}')
    ```

    يقوم هذا الكود باستخراج محتوى الحدث الذي يحتوي على رسالة JSON المرسلة بواسطة جهاز IoT.

    ثم يحصل على معرف الجهاز من التعليقات التوضيحية المرسلة مع الرسالة. يحتوي محتوى الحدث على الرسالة المرسلة كتليمتر، بينما يحتوي القاموس `iothub_metadata` على الخصائص التي يحددها IoT Hub مثل معرف الجهاز المرسل، ووقت إرسال الرسالة.

    يتم بعد ذلك تسجيل هذه المعلومات. سترى هذا التسجيل في الطرفية عند تشغيل تطبيق Functions محليًا.

1. أسفل هذا، أضف الكود التالي:

    ```python
    soil_moisture = body['soil_moisture']

    if soil_moisture > 450:
        direct_method = CloudToDeviceMethod(method_name='relay_on', payload='{}')
    else:
        direct_method = CloudToDeviceMethod(method_name='relay_off', payload='{}')
    ```

    يقوم هذا الكود بالحصول على مستوى رطوبة التربة من الرسالة. ثم يتحقق من مستوى الرطوبة، وبناءً على القيمة، ينشئ فئة مساعدة لطلب الطريقة المباشرة لطريقة `relay_on` أو `relay_off`. لا يحتاج طلب الطريقة إلى حمولة، لذا يتم إرسال مستند JSON فارغ.

1. أسفل هذا أضف الكود التالي:

    ```python
    logging.info(f'Sending direct method request for {direct_method.method_name} for device {device_id}')

    registry_manager_connection_string = os.environ['REGISTRY_MANAGER_CONNECTION_STRING']
    registry_manager = IoTHubRegistryManager(registry_manager_connection_string)
    ```
يتم تحميل `REGISTRY_MANAGER_CONNECTION_STRING` من ملف `local.settings.json`. القيم الموجودة في هذا الملف تصبح متاحة كمتغيرات بيئية، ويمكن قراءتها باستخدام وظيفة `os.environ`، وهي وظيفة تُرجع قاموسًا يحتوي على جميع المتغيرات البيئية.

> 💁 عندما يتم نشر هذا الكود إلى السحابة، سيتم تعيين القيم الموجودة في ملف `local.settings.json` كإعدادات للتطبيق (*Application Settings*)، ويمكن قراءتها من المتغيرات البيئية.

بعد ذلك، يقوم الكود بإنشاء نسخة من فئة المساعد Registry Manager باستخدام سلسلة الاتصال.

1. أضف الكود التالي:

    ```python
    registry_manager.invoke_device_method(device_id, direct_method)

    logging.info('Direct method request sent!')
    ```

    يخبر هذا الكود مدير السجل بإرسال طلب الطريقة المباشرة إلى الجهاز الذي أرسل البيانات.

    > 💁 في الإصدارات السابقة من التطبيق التي أنشأتها في الدروس السابقة باستخدام MQTT، كانت أوامر التحكم في الترحيل تُرسل إلى جميع الأجهزة. كان الكود يفترض أن لديك جهازًا واحدًا فقط. هذا الإصدار من الكود يرسل طلب الطريقة إلى جهاز واحد فقط، لذا سيعمل إذا كان لديك إعدادات متعددة لأجهزة استشعار الرطوبة والترحيل، حيث يتم إرسال طلب الطريقة المباشرة إلى الجهاز الصحيح.

1. قم بتشغيل تطبيق Functions، وتأكد من أن جهاز IoT الخاص بك يرسل البيانات. سترى الرسائل يتم معالجتها وطلبات الطريقة المباشرة يتم إرسالها. قم بتحريك مستشعر رطوبة التربة داخل وخارج التربة لترى القيم تتغير والترحيل يعمل ويتوقف.

> 💁 يمكنك العثور على هذا الكود في مجلد [code/functions](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud/code/functions).

## نشر الكود بدون خادم إلى السحابة

الكود يعمل الآن محليًا، والخطوة التالية هي نشر تطبيق Functions إلى السحابة.

### المهمة - إنشاء موارد السحابة

يحتاج تطبيق Functions الخاص بك إلى أن يتم نشره إلى مورد Functions App في Azure، داخل مجموعة الموارد التي أنشأتها لـ IoT Hub. ستحتاج أيضًا إلى إنشاء حساب تخزين في Azure ليحل محل المحاكي الذي يعمل محليًا.

1. قم بتشغيل الأمر التالي لإنشاء حساب تخزين:

    ```sh
    az storage account create --resource-group soil-moisture-sensor \
                              --sku Standard_LRS \
                              --name <storage_name> 
    ```

    استبدل `<storage_name>` باسم لحساب التخزين الخاص بك. يجب أن يكون هذا الاسم فريدًا عالميًا لأنه يشكل جزءًا من عنوان URL المستخدم للوصول إلى حساب التخزين. يمكنك استخدام الأحرف الصغيرة والأرقام فقط لهذا الاسم، ولا يُسمح بأي أحرف أخرى، وهو محدود بـ 24 حرفًا. استخدم شيئًا مثل `sms` وأضف معرفًا فريدًا في النهاية، مثل بعض الكلمات العشوائية أو اسمك.

    الخيار `--sku Standard_LRS` يحدد فئة التسعير، حيث يتم اختيار أقل تكلفة لحساب عام. لا توجد فئة مجانية للتخزين، وتدفع مقابل ما تستخدمه. التكاليف منخفضة نسبيًا، حيث أن أغلى تخزين أقل من 0.05 دولار أمريكي شهريًا لكل جيجابايت مخزن.

    ✅ اقرأ المزيد عن التسعير على [صفحة تسعير حساب تخزين Azure](https://azure.microsoft.com/pricing/details/storage/?WT.mc_id=academic-17441-jabenn)

1. قم بتشغيل الأمر التالي لإنشاء تطبيق Functions:

    ```sh
    az functionapp create --resource-group soil-moisture-sensor \
                          --runtime python \
                          --functions-version 3 \
                          --os-type Linux \
                          --consumption-plan-location <location> \
                          --storage-account <storage_name> \
                          --name <functions_app_name>
    ```

    استبدل `<location>` بالموقع الذي استخدمته عند إنشاء مجموعة الموارد في الدرس السابق.

    استبدل `<storage_name>` باسم حساب التخزين الذي أنشأته في الخطوة السابقة.

    استبدل `<functions_app_name>` باسم فريد لتطبيق Functions الخاص بك. يجب أن يكون هذا الاسم فريدًا عالميًا لأنه يشكل جزءًا من عنوان URL الذي يمكن استخدامه للوصول إلى تطبيق Functions. استخدم شيئًا مثل `soil-moisture-sensor-` وأضف معرفًا فريدًا في النهاية، مثل بعض الكلمات العشوائية أو اسمك.

    الخيار `--functions-version 3` يحدد إصدار Azure Functions الذي سيتم استخدامه. الإصدار 3 هو أحدث إصدار.

    الخيار `--os-type Linux` يخبر بيئة تشغيل Functions باستخدام Linux كنظام تشغيل لاستضافة هذه الوظائف. يمكن استضافة الوظائف على Linux أو Windows، اعتمادًا على لغة البرمجة المستخدمة. تطبيقات Python مدعومة فقط على Linux.

### المهمة - تحميل إعدادات التطبيق

عندما قمت بتطوير تطبيق Functions الخاص بك، قمت بتخزين بعض الإعدادات في ملف `local.settings.json` لسلاسل الاتصال الخاصة بـ IoT Hub. يجب كتابة هذه الإعدادات إلى إعدادات التطبيق في تطبيق Functions في Azure حتى يتمكن الكود من استخدامها.

> 🎓 ملف `local.settings.json` مخصص لإعدادات التطوير المحلي فقط، ولا يجب أن يتم إدخاله في التحكم في مصدر الكود، مثل GitHub. عند النشر إلى السحابة، يتم استخدام إعدادات التطبيق. إعدادات التطبيق هي أزواج مفتاح/قيمة مستضافة في السحابة ويتم قراءتها من المتغيرات البيئية إما في الكود الخاص بك أو بواسطة بيئة التشغيل عند توصيل الكود بـ IoT Hub.

1. قم بتشغيل الأمر التالي لتعيين إعداد `IOT_HUB_CONNECTION_STRING` في إعدادات تطبيق Functions:

    ```sh
    az functionapp config appsettings set --resource-group soil-moisture-sensor \
                                          --name <functions_app_name> \
                                          --settings "IOT_HUB_CONNECTION_STRING=<connection string>"
    ```

    استبدل `<functions_app_name>` بالاسم الذي استخدمته لتطبيق Functions الخاص بك.

    استبدل `<connection string>` بالقيمة الخاصة بـ `IOT_HUB_CONNECTION_STRING` من ملف `local.settings.json` الخاص بك.

1. كرر الخطوة أعلاه، ولكن قم بتعيين قيمة `REGISTRY_MANAGER_CONNECTION_STRING` إلى القيمة المقابلة من ملف `local.settings.json` الخاص بك.

عند تشغيل هذه الأوامر، ستظهر قائمة بجميع إعدادات التطبيق لتطبيق الوظائف. يمكنك استخدام هذه القائمة للتحقق من أن القيم تم تعيينها بشكل صحيح.

> 💁 سترى قيمة تم تعيينها بالفعل لـ `AzureWebJobsStorage`. في ملف `local.settings.json` الخاص بك، تم تعيين هذه القيمة لاستخدام محاكي التخزين المحلي. عند إنشاء تطبيق Functions، يتم تمرير حساب التخزين كمعامل، ويتم تعيينه تلقائيًا في هذا الإعداد.

### المهمة - نشر تطبيق Functions الخاص بك إلى السحابة

الآن بعد أن أصبح تطبيق Functions جاهزًا، يمكن نشر الكود الخاص بك.

1. قم بتشغيل الأمر التالي من نافذة VS Code لنشر تطبيق Functions الخاص بك:

    ```sh
    func azure functionapp publish <functions_app_name>
    ```

    استبدل `<functions_app_name>` بالاسم الذي استخدمته لتطبيق Functions الخاص بك.

سيتم تجميع الكود وإرساله إلى تطبيق Functions، حيث سيتم نشره وتشغيله. سيكون هناك الكثير من المخرجات في وحدة التحكم، تنتهي بتأكيد النشر وقائمة الوظائف المنشورة. في هذه الحالة، ستحتوي القائمة فقط على المشغل.

```output
Deployment successful.
Remote build succeeded!
Syncing triggers...
Functions in soil-moisture-sensor:
    iot-hub-trigger - [eventHubTrigger]
```

تأكد من أن جهاز IoT الخاص بك يعمل. قم بتغيير مستويات الرطوبة عن طريق ضبط رطوبة التربة أو تحريك المستشعر داخل وخارج التربة. سترى الترحيل يعمل ويتوقف مع تغير رطوبة التربة.

---

## 🚀 التحدي

في الدرس السابق، قمت بإدارة توقيت الترحيل عن طريق إلغاء الاشتراك من رسائل MQTT أثناء تشغيل الترحيل، ولمدة قصيرة بعد إيقافه. لا يمكنك استخدام هذه الطريقة هنا - لا يمكنك إلغاء الاشتراك من مشغل IoT Hub الخاص بك.

فكر في طرق مختلفة يمكنك استخدامها للتعامل مع هذا في تطبيق Functions الخاص بك.

## اختبار ما بعد المحاضرة

[اختبار ما بعد المحاضرة](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/18)

## المراجعة والدراسة الذاتية

* اقرأ عن الحوسبة بدون خادم على [صفحة الحوسبة بدون خادم على ويكيبيديا](https://wikipedia.org/wiki/Serverless_computing)
* اقرأ عن استخدام الحوسبة بدون خادم في Azure بما في ذلك المزيد من الأمثلة في [مدونة Azure: الحوسبة بدون خادم لاحتياجات IoT الخاصة بك](https://azure.microsoft.com/blog/go-serverless-for-your-iot-needs/?WT.mc_id=academic-17441-jabenn)
* تعلم المزيد عن Azure Functions على [قناة Azure Functions على YouTube](https://www.youtube.com/c/AzureFunctions)

## الواجب

[إضافة التحكم اليدوي في الترحيل](assignment.md)

---

**إخلاء المسؤولية**:  
تم ترجمة هذا المستند باستخدام خدمة الترجمة بالذكاء الاصطناعي [Co-op Translator](https://github.com/Azure/co-op-translator). بينما نسعى لتحقيق الدقة، يرجى العلم أن الترجمات الآلية قد تحتوي على أخطاء أو عدم دقة. يجب اعتبار المستند الأصلي بلغته الأصلية المصدر الرسمي. للحصول على معلومات حاسمة، يُوصى بالاستعانة بترجمة بشرية احترافية. نحن غير مسؤولين عن أي سوء فهم أو تفسيرات خاطئة تنشأ عن استخدام هذه الترجمة.