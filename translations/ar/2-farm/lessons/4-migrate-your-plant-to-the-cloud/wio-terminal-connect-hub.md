<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "28320305a35ea3bc59c41fe146a2e6ed",
  "translation_date": "2025-08-26T23:00:53+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/wio-terminal-connect-hub.md",
  "language_code": "ar"
}
-->
# قم بتوصيل جهاز إنترنت الأشياء الخاص بك بالسحابة - Wio Terminal

في هذا الجزء من الدرس، ستقوم بتوصيل Wio Terminal الخاص بك بـ IoT Hub لإرسال البيانات واستقبال الأوامر.

## توصيل جهازك بـ IoT Hub

الخطوة التالية هي توصيل جهازك بـ IoT Hub.

### المهمة - الاتصال بـ IoT Hub

1. افتح مشروع `soil-moisture-sensor` في VS Code.

1. افتح ملف `platformio.ini`. قم بإزالة تبعية مكتبة `knolleary/PubSubClient`. كانت هذه المكتبة تُستخدم للاتصال بوسيط MQTT العام، ولم تعد ضرورية للاتصال بـ IoT Hub.

1. أضف تبعيات المكتبة التالية:

    ```ini
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    arduino-libraries/AzureIoTHub @ 1.6.0
    azure/AzureIoTUtility @ 1.6.1
    azure/AzureIoTProtocol_MQTT @ 1.6.0
    azure/AzureIoTProtocol_HTTP @ 1.6.0
    azure/AzureIoTSocket_WiFi @ 1.0.2
    ```

    توفر مكتبة `Seeed Arduino RTC` الكود للتفاعل مع ساعة الوقت الحقيقي في Wio Terminal، والتي تُستخدم لتتبع الوقت. تسمح المكتبات الأخرى لجهاز إنترنت الأشياء الخاص بك بالاتصال بـ IoT Hub.

1. أضف ما يلي إلى نهاية ملف `platformio.ini`:

    ```ini
    build_flags =
        -DDONT_USE_UPLOADTOBLOB
    ```

    هذا يحدد علامة المترجم المطلوبة عند ترجمة كود Arduino IoT Hub.

1. افتح ملف الرأس `config.h`. قم بإزالة جميع إعدادات MQTT وأضف الثابت التالي لسلسلة اتصال الجهاز:

    ```cpp
    // IoT Hub settings
    const char *CONNECTION_STRING = "<connection string>";
    ```

    استبدل `<connection string>` بسلسلة الاتصال الخاصة بجهازك التي نسختها سابقًا.

1. يعتمد الاتصال بـ IoT Hub على رمز مميز يعتمد على الوقت. هذا يعني أن جهاز إنترنت الأشياء يحتاج إلى معرفة الوقت الحالي. على عكس أنظمة التشغيل مثل Windows أو macOS أو Linux، لا تقوم المتحكمات الدقيقة بمزامنة الوقت الحالي تلقائيًا عبر الإنترنت. لذلك ستحتاج إلى إضافة كود للحصول على الوقت الحالي من [NTP](https://wikipedia.org/wiki/Network_Time_Protocol). بمجرد استرداد الوقت، يمكن تخزينه في ساعة الوقت الحقيقي في Wio Terminal، مما يسمح بطلب الوقت الصحيح لاحقًا، بشرط ألا يفقد الجهاز الطاقة. أضف ملفًا جديدًا يسمى `ntp.h` بالكود التالي:

    ```cpp
    #pragma once
    
    #include "DateTime.h"
    #include <time.h>
    #include "samd/NTPClientAz.h"
    #include <sys/time.h>

    static void initTime()
    {
        WiFiUDP _udp;
        time_t epochTime = (time_t)-1;
        NTPClientAz ntpClient;

        ntpClient.begin();

        while (true)
        {
            epochTime = ntpClient.getEpochTime("0.pool.ntp.org");

            if (epochTime == (time_t)-1)
            {
                Serial.println("Fetching NTP epoch time failed! Waiting 2 seconds to retry.");
                delay(2000);
            }
            else
            {
                Serial.print("Fetched NTP epoch time is: ");

                char buff[32];
                sprintf(buff, "%.f", difftime(epochTime, (time_t)0));
                Serial.println(buff);
                break;
            }
        }

        ntpClient.end();

        struct timeval tv;
        tv.tv_sec = epochTime;
        tv.tv_usec = 0;

        settimeofday(&tv, NULL);
    }
    ```

    تفاصيل هذا الكود خارج نطاق هذا الدرس. يقوم بتعريف وظيفة تسمى `initTime` التي تحصل على الوقت الحالي من خادم NTP وتستخدمه لضبط الساعة على Wio Terminal.

1. افتح ملف `main.cpp` وقم بإزالة جميع كود MQTT، بما في ذلك ملف الرأس `PubSubClient.h`، وتعريف متغير `PubSubClient`، وطرق `reconnectMQTTClient` و `createMQTTClient`، وأي استدعاءات لهذه المتغيرات والطرق. يجب أن يحتوي هذا الملف فقط على الكود الخاص بالاتصال بشبكة WiFi، والحصول على رطوبة التربة، وإنشاء مستند JSON بها.

1. أضف توجيهات `#include` التالية إلى أعلى ملف `main.cpp` لتضمين ملفات الرأس الخاصة بمكتبات IoT Hub ولضبط الوقت:

    ```cpp
    #include <AzureIoTHub.h>
    #include <AzureIoTProtocol_MQTT.h>
    #include <iothubtransportmqtt.h>
    #include "ntp.h"
    ```

1. أضف الاستدعاء التالي إلى نهاية وظيفة `setup` لضبط الوقت الحالي:

    ```cpp
    initTime();
    ```

1. أضف تعريف المتغير التالي إلى أعلى الملف، مباشرةً أسفل توجيهات التضمين:

    ```cpp
    IOTHUB_DEVICE_CLIENT_LL_HANDLE _device_ll_handle;
    ```

    هذا يعرّف `IOTHUB_DEVICE_CLIENT_LL_HANDLE`، وهو مقبض اتصال بـ IoT Hub.

1. أسفل هذا، أضف الكود التالي:

    ```cpp
    static void connectionStatusCallback(IOTHUB_CLIENT_CONNECTION_STATUS result, IOTHUB_CLIENT_CONNECTION_STATUS_REASON reason, void *user_context)
    {
        if (result == IOTHUB_CLIENT_CONNECTION_AUTHENTICATED)
        {
            Serial.println("The device client is connected to iothub");
        }
        else
        {
            Serial.println("The device client has been disconnected");
        }
    }
    ```

    هذا يعرّف وظيفة رد نداء يتم استدعاؤها عندما يتغير حالة الاتصال بـ IoT Hub، مثل الاتصال أو الانفصال. يتم إرسال الحالة إلى منفذ التسلسل.

1. أسفل هذا، أضف وظيفة للاتصال بـ IoT Hub:

    ```cpp
    void connectIoTHub()
    {
        IoTHub_Init();
    
        _device_ll_handle = IoTHubDeviceClient_LL_CreateFromConnectionString(CONNECTION_STRING, MQTT_Protocol);
        
        if (_device_ll_handle == NULL)
        {
            Serial.println("Failure creating Iothub device. Hint: Check your connection string.");
            return;
        }
    
        IoTHubDeviceClient_LL_SetConnectionStatusCallback(_device_ll_handle, connectionStatusCallback, NULL);
    }
    ```

    يقوم هذا الكود بتهيئة كود مكتبة IoT Hub، ثم ينشئ اتصالًا باستخدام سلسلة الاتصال في ملف الرأس `config.h`. يعتمد هذا الاتصال على MQTT. إذا فشل الاتصال، يتم إرسال ذلك إلى منفذ التسلسل - إذا رأيت هذا في الإخراج، تحقق من سلسلة الاتصال. وأخيرًا يتم إعداد رد نداء حالة الاتصال.

1. قم باستدعاء هذه الوظيفة في وظيفة `setup` أسفل استدعاء `initTime`:

    ```cpp
    connectIoTHub();
    ```

1. تمامًا مثل عميل MQTT، يعمل هذا الكود على خيط واحد لذا يحتاج إلى وقت لمعالجة الرسائل التي يتم إرسالها من وإلى IoT Hub. أضف ما يلي إلى أعلى وظيفة `loop` للقيام بذلك:

    ```cpp
    IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
    ```

1. قم ببناء ورفع هذا الكود. سترى الاتصال في شاشة التسلسل:

    ```output
    Connecting to WiFi..
    Connected!
    Fetched NTP epoch time is: 1619983687
    Sending telemetry {"soil_moisture":391}
    The device client is connected to iothub
    ```

    في الإخراج يمكنك رؤية وقت NTP يتم استرداده، يليه اتصال عميل الجهاز. قد يستغرق الاتصال بضع ثوانٍ، لذا قد ترى رطوبة التربة في الإخراج أثناء اتصال الجهاز.

    > 💁 يمكنك تحويل وقت UNIX الخاص بـ NTP إلى نسخة أكثر قابلية للقراءة باستخدام موقع ويب مثل [unixtimestamp.com](https://www.unixtimestamp.com)

## إرسال البيانات

الآن بعد أن تم توصيل جهازك، يمكنك إرسال البيانات إلى IoT Hub بدلاً من وسيط MQTT.

### المهمة - إرسال البيانات

1. أضف الوظيفة التالية أعلى وظيفة `setup`:

    ```cpp
    void sendTelemetry(const char *telemetry)
    {
        IOTHUB_MESSAGE_HANDLE message_handle = IoTHubMessage_CreateFromString(telemetry);
        IoTHubDeviceClient_LL_SendEventAsync(_device_ll_handle, message_handle, NULL, NULL);
        IoTHubMessage_Destroy(message_handle);
    }
    ```

    يقوم هذا الكود بإنشاء رسالة IoT Hub من سلسلة يتم تمريرها كمعامل، ويرسلها إلى IoT Hub، ثم ينظف كائن الرسالة.

1. قم باستدعاء هذا الكود في وظيفة `loop`، مباشرةً بعد السطر الذي يتم فيه إرسال البيانات إلى منفذ التسلسل:

    ```cpp
    sendTelemetry(telemetry.c_str());
    ```

## معالجة الأوامر

يحتاج جهازك إلى معالجة أمر من كود الخادم للتحكم في المرحل. يتم إرسال هذا كطلب طريقة مباشرة.

### المهمة - معالجة طلب طريقة مباشرة

1. أضف الكود التالي قبل وظيفة `connectIoTHub`:

    ```cpp
    int directMethodCallback(const char *method_name, const unsigned char *payload, size_t size, unsigned char **response, size_t *response_size, void *userContextCallback)
    {
        Serial.printf("Direct method received %s\r\n", method_name);
    
        if (strcmp(method_name, "relay_on") == 0)
        {
            digitalWrite(PIN_WIRE_SCL, HIGH);
        }
        else if (strcmp(method_name, "relay_off") == 0)
        {
            digitalWrite(PIN_WIRE_SCL, LOW);
        }
    }
    ```

    يقوم هذا الكود بتعريف وظيفة رد نداء يمكن لمكتبة IoT Hub استدعاؤها عند تلقي طلب طريقة مباشرة. يتم إرسال الطريقة المطلوبة في معامل `method_name`. تطبع هذه الوظيفة الطريقة المستدعاة إلى منفذ التسلسل، ثم تقوم بتشغيل المرحل أو إيقافه بناءً على اسم الطريقة.

    > 💁 يمكن أيضًا تنفيذ ذلك في طلب طريقة مباشرة واحدة، حيث يتم تمرير الحالة المطلوبة للمرحل في حمولة يمكن تمريرها مع طلب الطريقة وتكون متاحة من معامل `payload`.

1. أضف الكود التالي إلى نهاية وظيفة `directMethodCallback`:

    ```cpp
    char resultBuff[16];
    sprintf(resultBuff, "{\"Result\":\"\"}");
    *response_size = strlen(resultBuff);
    *response = (unsigned char *)malloc(*response_size);
    memcpy(*response, resultBuff, *response_size);

    return IOTHUB_CLIENT_OK;
    ```

    تحتاج طلبات الطريقة المباشرة إلى استجابة، والاستجابة تكون في جزئين - استجابة كنص ورمز إرجاع. يقوم هذا الكود بإنشاء نتيجة كوثيقة JSON التالية:

    ```JSON
    {
        "Result": ""
    }
    ```

    يتم نسخ هذا بعد ذلك إلى معامل `response`، ويتم ضبط حجم هذه الاستجابة في معامل `response_size`. ثم يقوم هذا الكود بإرجاع `IOTHUB_CLIENT_OK` لإظهار أن الطريقة تمت معالجتها بشكل صحيح.

1. قم بتوصيل رد النداء عن طريق إضافة ما يلي إلى نهاية وظيفة `connectIoTHub`:

    ```cpp
    IoTHubClient_LL_SetDeviceMethodCallback(_device_ll_handle, directMethodCallback, NULL);
    ```

1. ستقوم وظيفة `loop` باستدعاء وظيفة `IoTHubDeviceClient_LL_DoWork` لمعالجة الأحداث المرسلة من IoT Hub. يتم استدعاء هذه الوظيفة فقط كل 10 ثوانٍ بسبب `delay`، مما يعني أن الطرق المباشرة تتم معالجتها فقط كل 10 ثوانٍ. لجعل هذا أكثر كفاءة، يمكن تنفيذ التأخير لمدة 10 ثوانٍ كعدة تأخيرات قصيرة، مع استدعاء `IoTHubDeviceClient_LL_DoWork` في كل مرة. للقيام بذلك، أضف الكود التالي أعلى وظيفة `loop`:

    ```cpp
    void work_delay(int delay_time)
    {
        int current = 0;
        do
        {
            IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
            delay(100);
            current += 100;
        } while (current < delay_time);
    }
    ```

    سيقوم هذا الكود بالتكرار بشكل متكرر، مستدعيًا `IoTHubDeviceClient_LL_DoWork` ومؤخرًا لمدة 100 مللي ثانية في كل مرة. سيقوم بذلك بقدر ما هو مطلوب للتأخير للمدة الزمنية المحددة في معامل `delay_time`. هذا يعني أن الجهاز ينتظر بحد أقصى 100 مللي ثانية لمعالجة طلبات الطريقة المباشرة.

1. في وظيفة `loop`، قم بإزالة استدعاء `IoTHubDeviceClient_LL_DoWork`، واستبدل استدعاء `delay(10000)` بما يلي لاستدعاء هذه الوظيفة الجديدة:

    ```cpp
    work_delay(10000);
    ```

> 💁 يمكنك العثور على هذا الكود في مجلد [code/wio-terminal](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/wio-terminal).

😀 برنامج مستشعر رطوبة التربة الخاص بك متصل بـ IoT Hub!

---

**إخلاء المسؤولية**:  
تم ترجمة هذا المستند باستخدام خدمة الترجمة بالذكاء الاصطناعي [Co-op Translator](https://github.com/Azure/co-op-translator). بينما نسعى لتحقيق الدقة، يرجى العلم أن الترجمات الآلية قد تحتوي على أخطاء أو معلومات غير دقيقة. يجب اعتبار المستند الأصلي بلغته الأصلية المصدر الموثوق. للحصول على معلومات حاسمة، يُوصى بالاستعانة بترجمة بشرية احترافية. نحن غير مسؤولين عن أي سوء فهم أو تفسيرات خاطئة تنشأ عن استخدام هذه الترجمة.