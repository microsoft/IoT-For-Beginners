<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d6faf0e8d3c2d6d20c0aef2a305dab18",
  "translation_date": "2025-08-26T23:19:42+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md",
  "language_code": "ar"
}
-->
# التحكم في ضوء الليل عبر الإنترنت - Wio Terminal

يحتاج جهاز إنترنت الأشياء إلى البرمجة للتواصل مع *test.mosquitto.org* باستخدام MQTT لإرسال قيم القياس عن بعد مع قراءة مستشعر الضوء، واستقبال الأوامر للتحكم في LED.

في هذا الجزء من الدرس، ستقوم بتوصيل Wio Terminal بخادم MQTT.

## تثبيت مكتبات WiFi وMQTT الخاصة بـ Arduino

للتواصل مع خادم MQTT، تحتاج إلى تثبيت بعض مكتبات Arduino لاستخدام شريحة WiFi في Wio Terminal، والتواصل مع MQTT. عند تطوير أجهزة Arduino، يمكنك استخدام مجموعة واسعة من المكتبات التي تحتوي على كود مفتوح المصدر وتوفر مجموعة كبيرة من الإمكانيات. تنشر Seeed مكتبات لـ Wio Terminal تسمح له بالتواصل عبر WiFi. كما نشر مطورون آخرون مكتبات للتواصل مع خوادم MQTT، وستستخدم هذه المكتبات مع جهازك.

تُقدم هذه المكتبات ككود مصدر يمكن استيراده تلقائيًا إلى PlatformIO وتجميعه لجهازك. بهذه الطريقة، ستعمل مكتبات Arduino على أي جهاز يدعم إطار عمل Arduino، بشرط أن يحتوي الجهاز على أي أجهزة محددة تحتاجها تلك المكتبة. بعض المكتبات، مثل مكتبات Seeed WiFi، تكون مخصصة لأجهزة معينة.

يمكن تثبيت المكتبات عالميًا وتجميعها إذا لزم الأمر، أو داخل مشروع معين. في هذه المهمة، سيتم تثبيت المكتبات داخل المشروع.

✅ يمكنك معرفة المزيد عن إدارة المكتبات وكيفية العثور على المكتبات وتثبيتها في [وثائق مكتبة PlatformIO](https://docs.platformio.org/en/latest/librarymanager/index.html).

### المهمة - تثبيت مكتبات WiFi وMQTT الخاصة بـ Arduino

قم بتثبيت مكتبات Arduino.

1. افتح مشروع ضوء الليل في VS Code.

1. أضف ما يلي إلى نهاية ملف `platformio.ini`:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
        seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
        seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    ```

    هذا يستورد مكتبات Seeed WiFi. تشير صيغة `@ <number>` إلى رقم إصدار معين للمكتبة.

    > 💁 يمكنك إزالة `@ <number>` لاستخدام أحدث إصدار من المكتبات دائمًا، ولكن لا توجد ضمانات بأن الإصدارات الأحدث ستعمل مع الكود أدناه. تم اختبار الكود هنا مع هذا الإصدار من المكتبات.

    هذا كل ما تحتاجه لإضافة المكتبات. في المرة القادمة التي يقوم فيها PlatformIO ببناء المشروع، سيقوم بتنزيل الكود المصدر لهذه المكتبات وتجميعه داخل مشروعك.

1. أضف ما يلي إلى `lib_deps`:

    ```ini
    knolleary/PubSubClient @ 2.8
    ```

    هذا يستورد [PubSubClient](https://github.com/knolleary/pubsubclient)، وهو عميل MQTT لـ Arduino.

## الاتصال بشبكة WiFi

يمكن الآن توصيل Wio Terminal بشبكة WiFi.

### المهمة - الاتصال بشبكة WiFi

قم بتوصيل Wio Terminal بشبكة WiFi.

1. أنشئ ملفًا جديدًا في مجلد `src` يسمى `config.h`. يمكنك القيام بذلك عن طريق تحديد مجلد `src`، أو ملف `main.cpp` بداخله، واختيار زر **ملف جديد** من المستكشف. يظهر هذا الزر فقط عندما يكون المؤشر فوق المستكشف.

    ![زر الملف الجديد](../../../../../translated_images/ar/vscode-new-file-button.182702340fe6723c.png)

1. أضف الكود التالي إلى هذا الملف لتعريف الثوابت الخاصة ببيانات اعتماد شبكة WiFi:

    ```cpp
    #pragma once

    #include <string>
    
    using namespace std;
    
    // WiFi credentials
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    ```

    استبدل `<SSID>` باسم شبكة WiFi الخاصة بك. استبدل `<PASSWORD>` بكلمة مرور شبكة WiFi الخاصة بك.

1. افتح ملف `main.cpp`.

1. أضف توجيهات `#include` التالية إلى أعلى الملف:

    ```cpp
    #include <PubSubClient.h>
    #include <rpcWiFi.h>
    #include <SPI.h>
    
    #include "config.h"
    ```

    هذا يتضمن ملفات الرأس للمكتبات التي أضفتها سابقًا، بالإضافة إلى ملف رأس التكوين. هذه الملفات الرأس ضرورية لإخبار PlatformIO بجلب الكود من المكتبات. بدون تضمين هذه الملفات الرأس بشكل صريح، لن يتم تجميع بعض الكود وستظهر أخطاء في المترجم.

1. أضف الكود التالي أعلى وظيفة `setup`:

    ```cpp
    void connectWiFi()
    {
        while (WiFi.status() != WL_CONNECTED)
        {
            Serial.println("Connecting to WiFi..");
            WiFi.begin(SSID, PASSWORD);
            delay(500);
        }
    
        Serial.println("Connected!");
    }
    ```

    يقوم هذا الكود بالتكرار أثناء عدم اتصال الجهاز بشبكة WiFi، ويحاول الاتصال باستخدام اسم الشبكة وكلمة المرور من ملف رأس التكوين.

1. أضف استدعاء لهذه الوظيفة في نهاية وظيفة `setup`، بعد تكوين الدبابيس.

    ```cpp
    connectWiFi();
    ```

1. قم برفع هذا الكود إلى جهازك للتحقق من أن اتصال WiFi يعمل. يجب أن ترى ذلك في شاشة المراقبة التسلسلية.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    ```

## الاتصال بـ MQTT

بمجرد اتصال Wio Terminal بشبكة WiFi، يمكنه الاتصال بخادم MQTT.

### المهمة - الاتصال بـ MQTT

قم بالاتصال بخادم MQTT.

1. أضف الكود التالي إلى نهاية ملف `config.h` لتعريف تفاصيل الاتصال بخادم MQTT:

    ```cpp
    // MQTT settings
    const string ID = "<ID>";
    
    const string BROKER = "test.mosquitto.org";
    const string CLIENT_NAME = ID + "nightlight_client";
    ```

    استبدل `<ID>` بمعرف فريد سيتم استخدامه كاسم عميل الجهاز، ولاحقًا للمواضيع التي ينشرها هذا الجهاز ويشترك فيها. خادم *test.mosquitto.org* عام ويستخدمه العديد من الأشخاص، بما في ذلك طلاب آخرين يعملون على هذا التمرين. يضمن وجود اسم عميل MQTT فريد وأسماء مواضيع فريدة أن الكود الخاص بك لن يتعارض مع أي شخص آخر. ستحتاج أيضًا إلى هذا المعرف عند إنشاء كود الخادم لاحقًا في هذا التمرين.

    > 💁 يمكنك استخدام موقع مثل [GUIDGen](https://www.guidgen.com) لإنشاء معرف فريد.

    `BROKER` هو عنوان URL لخادم MQTT.

    `CLIENT_NAME` هو اسم فريد لهذا العميل MQTT على الخادم.

1. افتح ملف `main.cpp`، وأضف الكود التالي أسفل وظيفة `connectWiFi` وأعلى وظيفة `setup`:

    ```cpp
    WiFiClient wioClient;
    PubSubClient client(wioClient);
    ```

    يقوم هذا الكود بإنشاء عميل WiFi باستخدام مكتبات WiFi الخاصة بـ Wio Terminal ويستخدمه لإنشاء عميل MQTT.

1. أسفل هذا الكود، أضف ما يلي:

    ```cpp
    void reconnectMQTTClient()
    {
        while (!client.connected())
        {
            Serial.print("Attempting MQTT connection...");
    
            if (client.connect(CLIENT_NAME.c_str()))
            {
                Serial.println("connected");
            }
            else
            {
                Serial.print("Retying in 5 seconds - failed, rc=");
                Serial.println(client.state());
                
                delay(5000);
            }
        }
    }
    ```

    تختبر هذه الوظيفة الاتصال بخادم MQTT وتعيد الاتصال إذا لم يكن متصلًا. تقوم بالتكرار طوال الوقت الذي لا يكون فيه متصلًا وتحاول الاتصال باستخدام اسم العميل الفريد المحدد في ملف رأس التكوين.

    إذا فشل الاتصال، فإنه يعيد المحاولة بعد 5 ثوانٍ.

1. أضف الكود التالي أسفل وظيفة `reconnectMQTTClient`:

    ```cpp
    void createMQTTClient()
    {
        client.setServer(BROKER.c_str(), 1883);
        reconnectMQTTClient();
    }
    ```

    يقوم هذا الكود بتعيين خادم MQTT للعميل، بالإضافة إلى إعداد رد الاتصال عند استلام رسالة. ثم يحاول الاتصال بالخادم.

1. قم باستدعاء وظيفة `createMQTTClient` في وظيفة `setup` بعد اتصال WiFi.

1. استبدل وظيفة `loop` بالكامل بما يلي:

    ```cpp
    void loop()
    {
        reconnectMQTTClient();
        client.loop();
    
        delay(2000);
    }
    ```

    يبدأ هذا الكود بإعادة الاتصال بخادم MQTT. يمكن قطع هذه الاتصالات بسهولة، لذا من المفيد التحقق بانتظام وإعادة الاتصال إذا لزم الأمر. ثم يستدعي طريقة `loop` على عميل MQTT لمعالجة أي رسائل واردة على الموضوع المشترك فيه. هذا التطبيق أحادي الخيط، لذا لا يمكن استقبال الرسائل على خيط خلفي، وبالتالي يجب تخصيص وقت على الخيط الرئيسي لمعالجة أي رسائل تنتظر على اتصال الشبكة.

    أخيرًا، يضمن تأخير لمدة ثانيتين عدم إرسال مستويات الضوء بشكل متكرر جدًا ويقلل من استهلاك الطاقة للجهاز.

1. قم برفع الكود إلى جهاز Wio Terminal، واستخدم شاشة المراقبة التسلسلية لرؤية الجهاز يتصل بشبكة WiFi وMQTT.

    ```output
    > Executing task: platformio device monitor <
    
    source /Users/jimbennett/GitHub/IoT-For-Beginners/1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal/nightlight/.venv/bin/activate
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    ```

> 💁 يمكنك العثور على هذا الكود في مجلد [code-mqtt/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal).

😀 لقد نجحت في توصيل جهازك بخادم MQTT.

---

**إخلاء المسؤولية**:  
تم ترجمة هذا المستند باستخدام خدمة الترجمة بالذكاء الاصطناعي [Co-op Translator](https://github.com/Azure/co-op-translator). بينما نسعى لتحقيق الدقة، يرجى العلم أن الترجمات الآلية قد تحتوي على أخطاء أو معلومات غير دقيقة. يجب اعتبار المستند الأصلي بلغته الأصلية المصدر الرسمي. للحصول على معلومات حاسمة، يُوصى بالاستعانة بترجمة بشرية احترافية. نحن غير مسؤولين عن أي سوء فهم أو تفسيرات خاطئة تنشأ عن استخدام هذه الترجمة.