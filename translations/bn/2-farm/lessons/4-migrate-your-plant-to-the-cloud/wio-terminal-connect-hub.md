<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "28320305a35ea3bc59c41fe146a2e6ed",
  "translation_date": "2025-08-27T12:03:52+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/wio-terminal-connect-hub.md",
  "language_code": "bn"
}
-->
# আপনার IoT ডিভাইসকে ক্লাউডের সাথে সংযুক্ত করুন - Wio Terminal

এই পাঠের এই অংশে, আপনি আপনার Wio Terminal-কে IoT Hub-এর সাথে সংযুক্ত করবেন, টেলিমেট্রি পাঠানোর এবং কমান্ড গ্রহণ করার জন্য।

## আপনার ডিভাইসকে IoT Hub-এর সাথে সংযুক্ত করুন

পরবর্তী ধাপটি হলো আপনার ডিভাইসকে IoT Hub-এর সাথে সংযুক্ত করা।

### কাজ - IoT Hub-এর সাথে সংযুক্ত করুন

1. VS Code-এ `soil-moisture-sensor` প্রকল্পটি খুলুন।

1. `platformio.ini` ফাইলটি খুলুন। `knolleary/PubSubClient` লাইব্রেরি ডিপেনডেন্সি সরিয়ে ফেলুন। এটি পাবলিক MQTT ব্রোকারের সাথে সংযোগ করার জন্য ব্যবহৃত হয়েছিল, এবং IoT Hub-এর সাথে সংযোগ করার জন্য এটি প্রয়োজন নেই।

1. নিম্নলিখিত লাইব্রেরি ডিপেনডেন্সি যোগ করুন:

    ```ini
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    arduino-libraries/AzureIoTHub @ 1.6.0
    azure/AzureIoTUtility @ 1.6.1
    azure/AzureIoTProtocol_MQTT @ 1.6.0
    azure/AzureIoTProtocol_HTTP @ 1.6.0
    azure/AzureIoTSocket_WiFi @ 1.0.2
    ```

    `Seeed Arduino RTC` লাইব্রেরি Wio Terminal-এ একটি রিয়েল-টাইম ক্লকের সাথে ইন্টারঅ্যাক্ট করার কোড প্রদান করে, যা সময় ট্র্যাক করার জন্য ব্যবহৃত হয়। বাকি লাইব্রেরিগুলি আপনার IoT ডিভাইসকে IoT Hub-এর সাথে সংযুক্ত করতে সাহায্য করে।

1. `platformio.ini` ফাইলের নিচে নিম্নলিখিত যোগ করুন:

    ```ini
    build_flags =
        -DDONT_USE_UPLOADTOBLOB
    ```

    এটি একটি কম্পাইলার ফ্ল্যাগ সেট করে যা Arduino IoT Hub কোড কম্পাইল করার সময় প্রয়োজন।

1. `config.h` হেডার ফাইলটি খুলুন। সমস্ত MQTT সেটিংস সরিয়ে ফেলুন এবং ডিভাইস সংযোগ স্ট্রিং-এর জন্য নিম্নলিখিত কনস্ট্যান্ট যোগ করুন:

    ```cpp
    // IoT Hub settings
    const char *CONNECTION_STRING = "<connection string>";
    ```

    `<connection string>`-এর জায়গায় আপনার ডিভাইসের সংযোগ স্ট্রিংটি বসান যা আপনি আগে কপি করেছিলেন।

1. IoT Hub-এর সাথে সংযোগ একটি সময়-ভিত্তিক টোকেন ব্যবহার করে। এর মানে হলো IoT ডিভাইসকে বর্তমান সময় জানতে হবে। Windows, macOS বা Linux-এর মতো অপারেটিং সিস্টেমের বিপরীতে, মাইক্রোকন্ট্রোলার স্বয়ংক্রিয়ভাবে ইন্টারনেটের মাধ্যমে বর্তমান সময় সিঙ্ক্রোনাইজ করে না। এর মানে হলো আপনাকে একটি [NTP](https://wikipedia.org/wiki/Network_Time_Protocol) সার্ভার থেকে বর্তমান সময় পাওয়ার জন্য কোড যোগ করতে হবে। একবার সময় পাওয়া গেলে, এটি Wio Terminal-এর রিয়েল-টাইম ক্লকে সংরক্ষণ করা যেতে পারে, যা ডিভাইস পাওয়ার হারালে সঠিক সময় পুনরায় অনুরোধ করার অনুমতি দেয়। `ntp.h` নামে একটি নতুন ফাইল তৈরি করুন এবং নিম্নলিখিত কোড যোগ করুন:

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

    এই কোডের বিস্তারিত এই পাঠের আওতার বাইরে। এটি একটি `initTime` নামক ফাংশন সংজ্ঞায়িত করে যা একটি NTP সার্ভার থেকে বর্তমান সময় পায় এবং Wio Terminal-এর ক্লক সেট করতে এটি ব্যবহার করে।

1. `main.cpp` ফাইলটি খুলুন এবং সমস্ত MQTT কোড সরিয়ে ফেলুন, যার মধ্যে রয়েছে `PubSubClient.h` হেডার ফাইল, `PubSubClient` ভেরিয়েবল ডিক্লারেশন, `reconnectMQTTClient` এবং `createMQTTClient` মেথড, এবং এই ভেরিয়েবল এবং মেথডগুলির কোনো কল। এই ফাইলটি শুধুমাত্র WiFi-তে সংযোগ করার, মাটি আর্দ্রতা পাওয়ার এবং এটি একটি JSON ডকুমেন্টে তৈরি করার কোড ধারণ করবে।

1. `main.cpp` ফাইলের শীর্ষে নিম্নলিখিত `#include` ডিরেক্টিভ যোগ করুন IoT Hub লাইব্রেরি এবং সময় সেট করার জন্য হেডার ফাইল অন্তর্ভুক্ত করতে:

    ```cpp
    #include <AzureIoTHub.h>
    #include <AzureIoTProtocol_MQTT.h>
    #include <iothubtransportmqtt.h>
    #include "ntp.h"
    ```

1. `setup` ফাংশনের শেষে নিম্নলিখিত কল যোগ করুন বর্তমান সময় সেট করার জন্য:

    ```cpp
    initTime();
    ```

1. ফাইলের শীর্ষে, অন্তর্ভুক্ত ডিরেক্টিভগুলির ঠিক নিচে নিম্নলিখিত ভেরিয়েবল ডিক্লারেশন যোগ করুন:

    ```cpp
    IOTHUB_DEVICE_CLIENT_LL_HANDLE _device_ll_handle;
    ```

    এটি একটি `IOTHUB_DEVICE_CLIENT_LL_HANDLE` ঘোষণা করে, যা IoT Hub-এর সাথে সংযোগের একটি হ্যান্ডেল।

1. এর নিচে নিম্নলিখিত কোড যোগ করুন:

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

    এটি একটি কলব্যাক ফাংশন ঘোষণা করে যা IoT Hub-এর সাথে সংযোগের স্ট্যাটাস পরিবর্তন হলে, যেমন সংযোগ বা সংযোগ বিচ্ছিন্ন হলে, কল করা হবে। স্ট্যাটাসটি সিরিয়াল পোর্টে পাঠানো হয়।

1. এর নিচে IoT Hub-এর সাথে সংযোগ করার জন্য একটি ফাংশন যোগ করুন:

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

    এই কোডটি IoT Hub লাইব্রেরি কোড ইনিশিয়ালাইজ করে, তারপর `config.h` হেডার ফাইলের সংযোগ স্ট্রিং ব্যবহার করে একটি সংযোগ তৈরি করে। এই সংযোগটি MQTT-এর উপর ভিত্তি করে। যদি সংযোগ ব্যর্থ হয়, এটি সিরিয়াল পোর্টে পাঠানো হয় - যদি আপনি আউটপুটে এটি দেখেন, সংযোগ স্ট্রিংটি পরীক্ষা করুন। অবশেষে সংযোগ স্ট্যাটাস কলব্যাক সেট আপ করা হয়।

1. `setup` ফাংশনে `initTime` কলের নিচে এই ফাংশনটি কল করুন:

    ```cpp
    connectIoTHub();
    ```

1. MQTT ক্লায়েন্টের মতো, এই কোডটি একটি একক থ্রেডে চলে, তাই হাব দ্বারা পাঠানো এবং হাবে পাঠানো বার্তাগুলি প্রক্রিয়া করার জন্য সময় প্রয়োজন। `loop` ফাংশনের শীর্ষে নিম্নলিখিত যোগ করুন এটি করার জন্য:

    ```cpp
    IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
    ```

1. এই কোডটি বিল্ড এবং আপলোড করুন। আপনি সিরিয়াল মনিটরে সংযোগ দেখতে পাবেন:

    ```output
    Connecting to WiFi..
    Connected!
    Fetched NTP epoch time is: 1619983687
    Sending telemetry {"soil_moisture":391}
    The device client is connected to iothub
    ```

    আউটপুটে আপনি NTP সময় ফেচ করা এবং তারপর ডিভাইস ক্লায়েন্ট সংযোগ করতে দেখতে পাবেন। সংযোগ করতে কয়েক সেকেন্ড সময় লাগতে পারে, তাই ডিভাইস সংযোগ করার সময় আপনি আউটপুটে মাটি আর্দ্রতা দেখতে পারেন।

    > 💁 আপনি NTP-এর UNIX সময়কে একটি আরও পাঠযোগ্য সংস্করণে রূপান্তর করতে পারেন [unixtimestamp.com](https://www.unixtimestamp.com)-এর মতো একটি ওয়েবসাইট ব্যবহার করে।

## টেলিমেট্রি পাঠান

এখন আপনার ডিভাইস সংযুক্ত হয়েছে, আপনি MQTT ব্রোকারের পরিবর্তে IoT Hub-এ টেলিমেট্রি পাঠাতে পারেন।

### কাজ - টেলিমেট্রি পাঠান

1. `setup` ফাংশনের উপরে নিম্নলিখিত ফাংশন যোগ করুন:

    ```cpp
    void sendTelemetry(const char *telemetry)
    {
        IOTHUB_MESSAGE_HANDLE message_handle = IoTHubMessage_CreateFromString(telemetry);
        IoTHubDeviceClient_LL_SendEventAsync(_device_ll_handle, message_handle, NULL, NULL);
        IoTHubMessage_Destroy(message_handle);
    }
    ```

    এই কোডটি একটি IoT Hub বার্তা তৈরি করে একটি প্যারামিটার হিসেবে পাস করা স্ট্রিং থেকে, এটি হাবে পাঠায়, তারপর বার্তা অবজেক্টটি পরিষ্কার করে।

1. `loop` ফাংশনে এই কোডটি কল করুন, টেলিমেট্রি সিরিয়াল পোর্টে পাঠানোর লাইনের ঠিক পরে:

    ```cpp
    sendTelemetry(telemetry.c_str());
    ```

## কমান্ড হ্যান্ডল করুন

আপনার ডিভাইসকে সার্ভার কোড থেকে একটি কমান্ড হ্যান্ডল করতে হবে রিলে নিয়ন্ত্রণ করার জন্য। এটি একটি ডিরেক্ট মেথড অনুরোধ হিসেবে পাঠানো হয়।

### কাজ - একটি ডিরেক্ট মেথড অনুরোধ হ্যান্ডল করুন

1. `connectIoTHub` ফাংশনের আগে নিম্নলিখিত কোড যোগ করুন:

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

    এই কোডটি একটি কলব্যাক মেথড সংজ্ঞায়িত করে যা IoT Hub লাইব্রেরি একটি ডিরেক্ট মেথড অনুরোধ পাওয়ার সময় কল করতে পারে। অনুরোধ করা মেথডটি `method_name` প্যারামিটারে পাঠানো হয়। এই ফাংশনটি সিরিয়াল পোর্টে কল করা মেথডটি প্রিন্ট করে, তারপর মেথড নামের উপর ভিত্তি করে রিলে চালু বা বন্ধ করে।

    > 💁 এটি একটি একক ডিরেক্ট মেথড অনুরোধে বাস্তবায়িত হতে পারে, যেখানে রিলের কাঙ্ক্ষিত অবস্থাটি একটি পে-লোডে পাস করা হয় যা মেথড অনুরোধের সাথে পাস করা যায় এবং `payload` প্যারামিটার থেকে পাওয়া যায়।

1. `directMethodCallback` ফাংশনের শেষে নিম্নলিখিত কোড যোগ করুন:

    ```cpp
    char resultBuff[16];
    sprintf(resultBuff, "{\"Result\":\"\"}");
    *response_size = strlen(resultBuff);
    *response = (unsigned char *)malloc(*response_size);
    memcpy(*response, resultBuff, *response_size);

    return IOTHUB_CLIENT_OK;
    ```

    ডিরেক্ট মেথড অনুরোধগুলির একটি প্রতিক্রিয়া প্রয়োজন, এবং প্রতিক্রিয়া দুটি অংশে থাকে - একটি টেক্সট হিসেবে প্রতিক্রিয়া এবং একটি রিটার্ন কোড। এই কোডটি নিম্নলিখিত JSON ডকুমেন্ট হিসেবে একটি রেজাল্ট তৈরি করবে:

    ```JSON
    {
        "Result": ""
    }
    ```

    এটি তারপর `response` প্যারামিটারে কপি করা হয়, এবং এই প্রতিক্রিয়ার আকার `response_size` প্যারামিটারে সেট করা হয়। এই কোডটি তারপর `IOTHUB_CLIENT_OK` রিটার্ন করে দেখানোর জন্য যে মেথডটি সঠিকভাবে হ্যান্ডল করা হয়েছে।

1. কলব্যাকটি সংযুক্ত করতে `connectIoTHub` ফাংশনের শেষে নিম্নলিখিত যোগ করুন:

    ```cpp
    IoTHubClient_LL_SetDeviceMethodCallback(_device_ll_handle, directMethodCallback, NULL);
    ```

1. `loop` ফাংশনটি `IoTHubDeviceClient_LL_DoWork` ফাংশন কল করবে IoT Hub দ্বারা পাঠানো ইভেন্টগুলি প্রক্রিয়া করার জন্য। এটি `delay` এর কারণে শুধুমাত্র প্রতি 10 সেকেন্ডে কল করা হয়, যার মানে ডিরেক্ট মেথডগুলি শুধুমাত্র প্রতি 10 সেকেন্ডে প্রক্রিয়া করা হয়। এটি আরও কার্যকর করতে, 10 সেকেন্ডের বিলম্বটি অনেক ছোট বিলম্বে বাস্তবায়িত হতে পারে, প্রতিবার `IoTHubDeviceClient_LL_DoWork` কল করে। এটি করতে, `loop` ফাংশনের উপরে নিম্নলিখিত কোড যোগ করুন:

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

    এই কোডটি বারবার লুপ করবে, `IoTHubDeviceClient_LL_DoWork` কল করবে এবং প্রতিবার 100ms বিলম্ব করবে। এটি যতবার প্রয়োজন ততবার করবে `delay_time` প্যারামিটারে দেওয়া সময় বিলম্ব করার জন্য। এর মানে হলো ডিভাইসটি ডিরেক্ট মেথড অনুরোধ প্রক্রিয়া করার জন্য সর্বাধিক 100ms অপেক্ষা করছে।

1. `loop` ফাংশনে `IoTHubDeviceClient_LL_DoWork` কলটি সরিয়ে ফেলুন এবং `delay(10000)` কলটি নিম্নলিখিত দিয়ে প্রতিস্থাপন করুন এই নতুন ফাংশনটি কল করতে:

    ```cpp
    work_delay(10000);
    ```

> 💁 আপনি এই কোডটি [code/wio-terminal](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/wio-terminal) ফোল্ডারে খুঁজে পেতে পারেন।

😀 আপনার মাটি আর্দ্রতা সেন্সর প্রোগ্রামটি IoT Hub-এর সাথে সংযুক্ত হয়েছে!

---

**অস্বীকৃতি**:  
এই নথিটি AI অনুবাদ পরিষেবা [Co-op Translator](https://github.com/Azure/co-op-translator) ব্যবহার করে অনুবাদ করা হয়েছে। আমরা যথাসম্ভব সঠিকতার জন্য চেষ্টা করি, তবে অনুগ্রহ করে মনে রাখবেন যে স্বয়ংক্রিয় অনুবাদে ত্রুটি বা অসঙ্গতি থাকতে পারে। মূল ভাষায় থাকা নথিটিকে প্রামাণিক উৎস হিসেবে বিবেচনা করা উচিত। গুরুত্বপূর্ণ তথ্যের জন্য, পেশাদার মানব অনুবাদ সুপারিশ করা হয়। এই অনুবাদ ব্যবহারের ফলে কোনো ভুল বোঝাবুঝি বা ভুল ব্যাখ্যা হলে আমরা দায়বদ্ধ থাকব না।