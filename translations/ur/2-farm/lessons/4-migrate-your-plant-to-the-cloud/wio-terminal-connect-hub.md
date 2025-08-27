<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "28320305a35ea3bc59c41fe146a2e6ed",
  "translation_date": "2025-08-26T23:01:14+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/wio-terminal-connect-hub.md",
  "language_code": "ur"
}
-->
# اپنے IoT ڈیوائس کو کلاؤڈ سے جوڑیں - Wio Terminal

اس سبق کے اس حصے میں، آپ اپنے Wio Terminal کو IoT Hub سے جوڑیں گے تاکہ ٹیلیمیٹری بھیج سکیں اور کمانڈز وصول کر سکیں۔

## اپنے ڈیوائس کو IoT Hub سے جوڑیں

اگلا مرحلہ یہ ہے کہ اپنے ڈیوائس کو IoT Hub سے جوڑیں۔

### کام - IoT Hub سے جڑیں

1. VS Code میں `soil-moisture-sensor` پروجیکٹ کھولیں۔

1. `platformio.ini` فائل کھولیں۔ `knolleary/PubSubClient` لائبریری کی ڈیپینڈنسی کو ہٹا دیں۔ یہ پبلک MQTT بروکر سے جڑنے کے لیے استعمال کی گئی تھی، اور IoT Hub سے جڑنے کے لیے ضروری نہیں ہے۔

1. درج ذیل لائبریری ڈیپینڈنسیز شامل کریں:

    ```ini
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    arduino-libraries/AzureIoTHub @ 1.6.0
    azure/AzureIoTUtility @ 1.6.1
    azure/AzureIoTProtocol_MQTT @ 1.6.0
    azure/AzureIoTProtocol_HTTP @ 1.6.0
    azure/AzureIoTSocket_WiFi @ 1.0.2
    ```

    `Seeed Arduino RTC` لائبریری Wio Terminal میں ریئل ٹائم کلاک کے ساتھ تعامل کے لیے کوڈ فراہم کرتی ہے، جو وقت کو ٹریک کرنے کے لیے استعمال ہوتی ہے۔ باقی لائبریریاں آپ کے IoT ڈیوائس کو IoT Hub سے جڑنے کی اجازت دیتی ہیں۔

1. `platformio.ini` فائل کے آخر میں درج ذیل شامل کریں:

    ```ini
    build_flags =
        -DDONT_USE_UPLOADTOBLOB
    ```

    یہ ایک کمپائلر فلیگ سیٹ کرتا ہے جو Arduino IoT Hub کوڈ کو کمپائل کرتے وقت ضروری ہے۔

1. `config.h` ہیڈر فائل کھولیں۔ تمام MQTT سیٹنگز کو ہٹا دیں اور ڈیوائس کنکشن اسٹرنگ کے لیے درج ذیل کانسٹنٹ شامل کریں:

    ```cpp
    // IoT Hub settings
    const char *CONNECTION_STRING = "<connection string>";
    ```

    `<connection string>` کو اس کنکشن اسٹرنگ سے تبدیل کریں جو آپ نے پہلے کاپی کی تھی۔

1. IoT Hub سے جڑنے کے لیے وقت پر مبنی ٹوکن استعمال ہوتا ہے۔ اس کا مطلب ہے کہ IoT ڈیوائس کو موجودہ وقت معلوم ہونا چاہیے۔ ونڈوز، macOS یا لینکس جیسے آپریٹنگ سسٹمز کے برعکس، مائیکرو کنٹرولرز خود بخود انٹرنیٹ کے ذریعے موجودہ وقت کو ہم آہنگ نہیں کرتے۔ اس کا مطلب ہے کہ آپ کو کوڈ شامل کرنا ہوگا تاکہ موجودہ وقت [NTP](https://wikipedia.org/wiki/Network_Time_Protocol) سرور سے حاصل کیا جا سکے۔ ایک بار وقت حاصل ہو جائے، اسے Wio Terminal میں ریئل ٹائم کلاک میں محفوظ کیا جا سکتا ہے، جس سے بعد میں درست وقت کی درخواست کی جا سکتی ہے، بشرطیکہ ڈیوائس پاور نہ کھوئے۔ `ntp.h` نامی ایک نئی فائل بنائیں اور درج ذیل کوڈ شامل کریں:

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

    اس کوڈ کی تفصیلات اس سبق کے دائرہ کار سے باہر ہیں۔ یہ ایک فنکشن `initTime` کو ڈیفائن کرتا ہے جو موجودہ وقت کو NTP سرور سے حاصل کرتا ہے اور اسے Wio Terminal کے کلاک پر سیٹ کرتا ہے۔

1. `main.cpp` فائل کھولیں اور تمام MQTT کوڈ کو ہٹا دیں، بشمول `PubSubClient.h` ہیڈر فائل، `PubSubClient` ویریبل کا اعلان، `reconnectMQTTClient` اور `createMQTTClient` میتھڈز، اور ان ویریبلز اور میتھڈز کے کسی بھی کالز کو۔ اس فائل میں صرف WiFi سے جڑنے، مٹی کی نمی حاصل کرنے اور اس کے ساتھ JSON ڈاکیومنٹ بنانے کا کوڈ ہونا چاہیے۔

1. `main.cpp` فائل کے اوپر درج ذیل `#include` ڈائریکٹیوز شامل کریں تاکہ IoT Hub لائبریریوں اور وقت سیٹ کرنے کے لیے ہیڈر فائلز شامل کی جا سکیں:

    ```cpp
    #include <AzureIoTHub.h>
    #include <AzureIoTProtocol_MQTT.h>
    #include <iothubtransportmqtt.h>
    #include "ntp.h"
    ```

1. `setup` فنکشن کے آخر میں درج ذیل کال شامل کریں تاکہ موجودہ وقت سیٹ کیا جا سکے:

    ```cpp
    initTime();
    ```

1. فائل کے اوپر، انکلوڈ ڈائریکٹیوز کے نیچے درج ذیل ویریبل اعلان شامل کریں:

    ```cpp
    IOTHUB_DEVICE_CLIENT_LL_HANDLE _device_ll_handle;
    ```

    یہ ایک `IOTHUB_DEVICE_CLIENT_LL_HANDLE` کو ڈیکلئر کرتا ہے، جو IoT Hub سے کنکشن کے لیے ایک ہینڈل ہے۔

1. اس کے نیچے درج ذیل کوڈ شامل کریں:

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

    یہ ایک کال بیک فنکشن کو ڈیکلئر کرتا ہے جو IoT Hub سے کنکشن کی اسٹیٹس میں تبدیلی پر کال کیا جائے گا، جیسے کنیکٹ یا ڈس کنیکٹ ہونا۔ اسٹیٹس سیریل پورٹ پر بھیجا جاتا ہے۔

1. اس کے نیچے IoT Hub سے جڑنے کے لیے ایک فنکشن شامل کریں:

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

    یہ کوڈ IoT Hub لائبریری کو انیشیئلائز کرتا ہے، پھر `config.h` ہیڈر فائل میں موجود کنکشن اسٹرنگ کا استعمال کرتے ہوئے کنکشن بناتا ہے۔ یہ کنکشن MQTT پر مبنی ہے۔ اگر کنکشن ناکام ہو جائے، تو یہ سیریل پورٹ پر بھیجا جاتا ہے - اگر آپ آؤٹ پٹ میں یہ دیکھیں، تو کنکشن اسٹرنگ چیک کریں۔ آخر میں کنکشن اسٹیٹس کال بیک سیٹ اپ کیا جاتا ہے۔

1. `setup` فنکشن میں `initTime` کال کے نیچے اس فنکشن کو کال کریں:

    ```cpp
    connectIoTHub();
    ```

1. MQTT کلائنٹ کی طرح، یہ کوڈ ایک سنگل تھریڈ پر چلتا ہے، اس لیے ہب کے ذریعے بھیجے گئے پیغامات کو پروسیس کرنے اور ہب کو بھیجے گئے پیغامات کو پروسیس کرنے کے لیے وقت درکار ہوتا ہے۔ `loop` فنکشن کے اوپر درج ذیل شامل کریں تاکہ یہ کام کیا جا سکے:

    ```cpp
    IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
    ```

1. اس کوڈ کو بلڈ اور اپلوڈ کریں۔ آپ سیریل مانیٹر میں کنکشن دیکھیں گے:

    ```output
    Connecting to WiFi..
    Connected!
    Fetched NTP epoch time is: 1619983687
    Sending telemetry {"soil_moisture":391}
    The device client is connected to iothub
    ```

    آؤٹ پٹ میں آپ NTP وقت کو حاصل ہوتے ہوئے دیکھ سکتے ہیں، اس کے بعد ڈیوائس کلائنٹ کنیکٹ ہوتا ہے۔ کنیکٹ ہونے میں چند سیکنڈ لگ سکتے ہیں، اس لیے آپ آؤٹ پٹ میں مٹی کی نمی دیکھ سکتے ہیں جب تک کہ ڈیوائس کنیکٹ ہو رہا ہو۔

    > 💁 آپ NTP کے UNIX وقت کو زیادہ قابلِ مطالعہ ورژن میں تبدیل کرنے کے لیے [unixtimestamp.com](https://www.unixtimestamp.com) جیسی ویب سائٹ استعمال کر سکتے ہیں۔

## ٹیلیمیٹری بھیجیں

اب جب کہ آپ کا ڈیوائس کنیکٹ ہو چکا ہے، آپ MQTT بروکر کے بجائے IoT Hub کو ٹیلیمیٹری بھیج سکتے ہیں۔

### کام - ٹیلیمیٹری بھیجیں

1. `setup` فنکشن کے اوپر درج ذیل فنکشن شامل کریں:

    ```cpp
    void sendTelemetry(const char *telemetry)
    {
        IOTHUB_MESSAGE_HANDLE message_handle = IoTHubMessage_CreateFromString(telemetry);
        IoTHubDeviceClient_LL_SendEventAsync(_device_ll_handle, message_handle, NULL, NULL);
        IoTHubMessage_Destroy(message_handle);
    }
    ```

    یہ کوڈ ایک IoT Hub میسج بناتا ہے جو ایک پیرامیٹر کے طور پر پاس کی گئی اسٹرنگ سے ہوتا ہے، اسے ہب کو بھیجتا ہے، پھر میسج آبجیکٹ کو صاف کرتا ہے۔

1. `loop` فنکشن میں، ٹیلیمیٹری کو سیریل پورٹ پر بھیجنے والی لائن کے فوراً بعد اس کوڈ کو کال کریں:

    ```cpp
    sendTelemetry(telemetry.c_str());
    ```

## کمانڈز کو ہینڈل کریں

آپ کے ڈیوائس کو سرور کوڈ سے ایک کمانڈ ہینڈل کرنے کی ضرورت ہے تاکہ ریلے کو کنٹرول کیا جا سکے۔ یہ ایک ڈائریکٹ میتھڈ ریکویسٹ کے طور پر بھیجا جاتا ہے۔

### کام - ڈائریکٹ میتھڈ ریکویسٹ کو ہینڈل کریں

1. `connectIoTHub` فنکشن سے پہلے درج ذیل کوڈ شامل کریں:

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

    یہ کوڈ ایک کال بیک میتھڈ ڈیفائن کرتا ہے جسے IoT Hub لائبریری اس وقت کال کر سکتی ہے جب اسے ڈائریکٹ میتھڈ ریکویسٹ موصول ہو۔ ریکویسٹ کی گئی میتھڈ `method_name` پیرامیٹر میں بھیجی جاتی ہے۔ یہ فنکشن سیریل پورٹ پر کال کی گئی میتھڈ کو پرنٹ کرتا ہے، پھر میتھڈ نام کے مطابق ریلے کو آن یا آف کرتا ہے۔

    > 💁 یہ ایک سنگل ڈائریکٹ میتھڈ ریکویسٹ میں بھی نافذ کیا جا سکتا ہے، مطلوبہ ریلے کی حالت کو ایک پے لوڈ میں پاس کرتے ہوئے جو میتھڈ ریکویسٹ کے ساتھ پاس کیا جا سکتا ہے اور `payload` پیرامیٹر سے دستیاب ہو سکتا ہے۔

1. `directMethodCallback` فنکشن کے آخر میں درج ذیل کوڈ شامل کریں:

    ```cpp
    char resultBuff[16];
    sprintf(resultBuff, "{\"Result\":\"\"}");
    *response_size = strlen(resultBuff);
    *response = (unsigned char *)malloc(*response_size);
    memcpy(*response, resultBuff, *response_size);

    return IOTHUB_CLIENT_OK;
    ```

    ڈائریکٹ میتھڈ ریکویسٹز کو ایک ریسپانس کی ضرورت ہوتی ہے، اور ریسپانس دو حصوں میں ہوتا ہے - ایک ٹیکسٹ کے طور پر ریسپانس، اور ایک ریٹرن کوڈ۔ یہ کوڈ درج ذیل JSON ڈاکیومنٹ کے طور پر ایک رزلٹ بنائے گا:

    ```JSON
    {
        "Result": ""
    }
    ```

    یہ پھر `response` پیرامیٹر میں کاپی کیا جاتا ہے، اور اس ریسپانس کا سائز `response_size` پیرامیٹر میں سیٹ کیا جاتا ہے۔ یہ کوڈ پھر `IOTHUB_CLIENT_OK` ریٹرن کرتا ہے تاکہ ظاہر ہو کہ میتھڈ کو صحیح طریقے سے ہینڈل کیا گیا۔

1. کال بیک کو وائر اپ کرنے کے لیے درج ذیل کو `connectIoTHub` فنکشن کے آخر میں شامل کریں:

    ```cpp
    IoTHubClient_LL_SetDeviceMethodCallback(_device_ll_handle, directMethodCallback, NULL);
    ```

1. `loop` فنکشن `IoTHubDeviceClient_LL_DoWork` فنکشن کو IoT Hub کے ذریعے بھیجے گئے ایونٹس کو پروسیس کرنے کے لیے کال کرے گا۔ یہ صرف ہر 10 سیکنڈ کے بعد `delay` کی وجہ سے کال کیا جاتا ہے، جس کا مطلب ہے کہ ڈائریکٹ میتھڈز صرف ہر 10 سیکنڈ کے بعد پروسیس ہوتی ہیں۔ اسے زیادہ موثر بنانے کے لیے، 10 سیکنڈ کی تاخیر کو کئی چھوٹی تاخیرات کے طور پر نافذ کیا جا سکتا ہے، ہر بار `IoTHubDeviceClient_LL_DoWork` کو کال کرتے ہوئے۔ ایسا کرنے کے لیے، درج ذیل کو `loop` فنکشن کے اوپر شامل کریں:

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

    یہ کوڈ بار بار لوپ کرے گا، `IoTHubDeviceClient_LL_DoWork` کو کال کرے گا اور ہر بار 100ms کے لیے تاخیر کرے گا۔ یہ جتنی بار ضرورت ہو اتنی بار کرے گا تاکہ دی گئی `delay_time` پیرامیٹر کے لیے تاخیر کی جا سکے۔ اس کا مطلب ہے کہ ڈیوائس زیادہ سے زیادہ 100ms کے لیے ڈائریکٹ میتھڈ ریکویسٹز کو پروسیس کرنے کے لیے انتظار کر رہا ہے۔

1. `loop` فنکشن میں، `IoTHubDeviceClient_LL_DoWork` کال کو ہٹا دیں، اور `delay(10000)` کال کو درج ذیل سے تبدیل کریں تاکہ اس نئے فنکشن کو کال کیا جا سکے:

    ```cpp
    work_delay(10000);
    ```

> 💁 آپ اس کوڈ کو [code/wio-terminal](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/wio-terminal) فولڈر میں تلاش کر سکتے ہیں۔

😀 آپ کا مٹی کی نمی سینسر پروگرام IoT Hub سے جڑ گیا ہے!

---

**ڈسکلیمر**:  
یہ دستاویز AI ترجمہ سروس [Co-op Translator](https://github.com/Azure/co-op-translator) کا استعمال کرتے ہوئے ترجمہ کی گئی ہے۔ ہم درستگی کے لیے کوشش کرتے ہیں، لیکن براہ کرم آگاہ رہیں کہ خودکار ترجمے میں غلطیاں یا غیر درستیاں ہو سکتی ہیں۔ اصل دستاویز کو اس کی اصل زبان میں مستند ذریعہ سمجھا جانا چاہیے۔ اہم معلومات کے لیے، پیشہ ور انسانی ترجمہ کی سفارش کی جاتی ہے۔ ہم اس ترجمے کے استعمال سے پیدا ہونے والی کسی بھی غلط فہمی یا غلط تشریح کے ذمہ دار نہیں ہیں۔