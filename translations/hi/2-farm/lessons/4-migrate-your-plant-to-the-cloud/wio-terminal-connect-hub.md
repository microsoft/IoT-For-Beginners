<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "28320305a35ea3bc59c41fe146a2e6ed",
  "translation_date": "2025-08-25T17:07:54+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/wio-terminal-connect-hub.md",
  "language_code": "hi"
}
-->
# अपने IoT डिवाइस को क्लाउड से कनेक्ट करें - Wio Terminal

इस पाठ के इस भाग में, आप अपने Wio Terminal को IoT Hub से कनेक्ट करेंगे, ताकि टेलीमेट्री भेज सकें और कमांड प्राप्त कर सकें।

## अपने डिवाइस को IoT Hub से कनेक्ट करें

अगला कदम है अपने डिवाइस को IoT Hub से कनेक्ट करना।

### कार्य - IoT Hub से कनेक्ट करें

1. VS Code में `soil-moisture-sensor` प्रोजेक्ट खोलें।

1. `platformio.ini` फाइल खोलें। `knolleary/PubSubClient` लाइब्रेरी डिपेंडेंसी को हटा दें। यह पब्लिक MQTT ब्रॉकर से कनेक्ट करने के लिए उपयोग की जाती थी, और IoT Hub से कनेक्ट करने के लिए आवश्यक नहीं है।

1. निम्नलिखित लाइब्रेरी डिपेंडेंसी जोड़ें:

    ```ini
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    arduino-libraries/AzureIoTHub @ 1.6.0
    azure/AzureIoTUtility @ 1.6.1
    azure/AzureIoTProtocol_MQTT @ 1.6.0
    azure/AzureIoTProtocol_HTTP @ 1.6.0
    azure/AzureIoTSocket_WiFi @ 1.0.2
    ```

    `Seeed Arduino RTC` लाइब्रेरी Wio Terminal में रियल-टाइम क्लॉक के साथ इंटरैक्ट करने के लिए कोड प्रदान करती है, जिसका उपयोग समय को ट्रैक करने के लिए किया जाता है। बाकी लाइब्रेरी आपके IoT डिवाइस को IoT Hub से कनेक्ट करने की अनुमति देती हैं।

1. `platformio.ini` फाइल के अंत में निम्नलिखित जोड़ें:

    ```ini
    build_flags =
        -DDONT_USE_UPLOADTOBLOB
    ```

    यह एक कंपाइलर फ्लैग सेट करता है जो Arduino IoT Hub कोड को कंपाइल करते समय आवश्यक होता है।

1. `config.h` हेडर फाइल खोलें। सभी MQTT सेटिंग्स को हटा दें और डिवाइस कनेक्शन स्ट्रिंग के लिए निम्नलिखित कॉन्स्टेंट जोड़ें:

    ```cpp
    // IoT Hub settings
    const char *CONNECTION_STRING = "<connection string>";
    ```

    `<connection string>` को उस कनेक्शन स्ट्रिंग से बदलें जिसे आपने पहले कॉपी किया था।

1. IoT Hub से कनेक्शन एक समय-आधारित टोकन का उपयोग करता है। इसका मतलब है कि IoT डिवाइस को वर्तमान समय जानना आवश्यक है। Windows, macOS या Linux जैसे ऑपरेटिंग सिस्टम के विपरीत, माइक्रोकंट्रोलर इंटरनेट पर स्वचालित रूप से वर्तमान समय को सिंक्रोनाइज़ नहीं करते। इसका मतलब है कि आपको [NTP](https://wikipedia.org/wiki/Network_Time_Protocol) सर्वर से वर्तमान समय प्राप्त करने के लिए कोड जोड़ना होगा। एक बार समय प्राप्त हो जाने के बाद, इसे Wio Terminal में रियल-टाइम क्लॉक में संग्रहीत किया जा सकता है, जिससे सही समय को बाद में अनुरोध किया जा सकता है, बशर्ते डिवाइस पावर न खोए। `ntp.h` नामक एक नई फाइल बनाएं और निम्नलिखित कोड जोड़ें:

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

    इस कोड का विवरण इस पाठ के दायरे से बाहर है। यह एक `initTime` नामक फ़ंक्शन को परिभाषित करता है जो NTP सर्वर से वर्तमान समय प्राप्त करता है और इसे Wio Terminal पर क्लॉक सेट करने के लिए उपयोग करता है।

1. `main.cpp` फाइल खोलें और सभी MQTT कोड को हटा दें, जिसमें `PubSubClient.h` हेडर फाइल, `PubSubClient` वेरिएबल की घोषणा, `reconnectMQTTClient` और `createMQTTClient` मेथड्स, और इन वेरिएबल्स और मेथड्स के किसी भी कॉल शामिल हैं। इस फाइल में केवल WiFi से कनेक्ट करने, मिट्टी की नमी प्राप्त करने और इसके साथ एक JSON डॉक्यूमेंट बनाने का कोड होना चाहिए।

1. `main.cpp` फाइल के शीर्ष पर निम्नलिखित `#include` निर्देश जोड़ें ताकि IoT Hub लाइब्रेरी और समय सेट करने के लिए हेडर फाइल्स को शामिल किया जा सके:

    ```cpp
    #include <AzureIoTHub.h>
    #include <AzureIoTProtocol_MQTT.h>
    #include <iothubtransportmqtt.h>
    #include "ntp.h"
    ```

1. `setup` फ़ंक्शन के अंत में निम्नलिखित कॉल जोड़ें ताकि वर्तमान समय सेट किया जा सके:

    ```cpp
    initTime();
    ```

1. फाइल के शीर्ष पर, `include` निर्देशों के ठीक नीचे निम्नलिखित वेरिएबल घोषणा जोड़ें:

    ```cpp
    IOTHUB_DEVICE_CLIENT_LL_HANDLE _device_ll_handle;
    ```

    यह एक `IOTHUB_DEVICE_CLIENT_LL_HANDLE` घोषित करता है, जो IoT Hub से कनेक्शन का एक हैंडल है।

1. इसके नीचे निम्नलिखित कोड जोड़ें:

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

    यह एक कॉलबैक फ़ंक्शन घोषित करता है जिसे IoT Hub से कनेक्शन की स्थिति बदलने पर कॉल किया जाएगा, जैसे कनेक्ट करना या डिस्कनेक्ट करना। स्थिति को सीरियल पोर्ट पर भेजा जाता है।

1. इसके नीचे IoT Hub से कनेक्ट करने के लिए एक फ़ंक्शन जोड़ें:

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

    यह कोड IoT Hub लाइब्रेरी को इनिशियलाइज़ करता है, फिर `config.h` हेडर फाइल में कनेक्शन स्ट्रिंग का उपयोग करके एक कनेक्शन बनाता है। यह कनेक्शन MQTT पर आधारित है। यदि कनेक्शन विफल होता है, तो इसे सीरियल पोर्ट पर भेजा जाता है - यदि आप इसे आउटपुट में देखते हैं, तो कनेक्शन स्ट्रिंग की जांच करें। अंत में, कनेक्शन स्थिति कॉलबैक सेट किया जाता है।

1. `setup` फ़ंक्शन में इस फ़ंक्शन को `initTime` कॉल के नीचे कॉल करें:

    ```cpp
    connectIoTHub();
    ```

1. ठीक उसी तरह जैसे MQTT क्लाइंट के साथ, यह कोड एक सिंगल थ्रेड पर चलता है, इसलिए हब द्वारा भेजे गए और हब को भेजे गए संदेशों को प्रोसेस करने के लिए समय चाहिए। इसे करने के लिए, `loop` फ़ंक्शन के शीर्ष पर निम्नलिखित जोड़ें:

    ```cpp
    IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
    ```

1. इस कोड को बिल्ड और अपलोड करें। आप सीरियल मॉनिटर में कनेक्शन देखेंगे:

    ```output
    Connecting to WiFi..
    Connected!
    Fetched NTP epoch time is: 1619983687
    Sending telemetry {"soil_moisture":391}
    The device client is connected to iothub
    ```

    आउटपुट में आप देख सकते हैं कि NTP समय प्राप्त किया जा रहा है, उसके बाद डिवाइस क्लाइंट कनेक्ट हो रहा है। कनेक्ट होने में कुछ सेकंड लग सकते हैं, इसलिए आप आउटपुट में डिवाइस के कनेक्ट होने के दौरान मिट्टी की नमी देख सकते हैं।

    > 💁 आप NTP के UNIX समय को अधिक पठनीय संस्करण में बदलने के लिए [unixtimestamp.com](https://www.unixtimestamp.com) जैसी वेबसाइट का उपयोग कर सकते हैं।

## टेलीमेट्री भेजें

अब जब आपका डिवाइस कनेक्ट हो गया है, तो आप MQTT ब्रॉकर के बजाय IoT Hub को टेलीमेट्री भेज सकते हैं।

### कार्य - टेलीमेट्री भेजें

1. `setup` फ़ंक्शन के ऊपर निम्नलिखित फ़ंक्शन जोड़ें:

    ```cpp
    void sendTelemetry(const char *telemetry)
    {
        IOTHUB_MESSAGE_HANDLE message_handle = IoTHubMessage_CreateFromString(telemetry);
        IoTHubDeviceClient_LL_SendEventAsync(_device_ll_handle, message_handle, NULL, NULL);
        IoTHubMessage_Destroy(message_handle);
    }
    ```

    यह कोड एक स्ट्रिंग से IoT Hub संदेश बनाता है जिसे पैरामीटर के रूप में पास किया गया है, इसे हब पर भेजता है, फिर संदेश ऑब्जेक्ट को साफ करता है।

1. इस कोड को `loop` फ़ंक्शन में कॉल करें, ठीक उस लाइन के बाद जहां टेलीमेट्री सीरियल पोर्ट पर भेजी जाती है:

    ```cpp
    sendTelemetry(telemetry.c_str());
    ```

## कमांड हैंडल करें

आपके डिवाइस को रिले को नियंत्रित करने के लिए सर्वर कोड से एक कमांड हैंडल करने की आवश्यकता है। इसे एक डायरेक्ट मेथड रिक्वेस्ट के रूप में भेजा जाता है।

## कार्य - डायरेक्ट मेथड रिक्वेस्ट हैंडल करें

1. `connectIoTHub` फ़ंक्शन से पहले निम्नलिखित कोड जोड़ें:

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

    यह कोड एक कॉलबैक मेथड परिभाषित करता है जिसे IoT Hub लाइब्रेरी डायरेक्ट मेथड रिक्वेस्ट प्राप्त होने पर कॉल कर सकती है। अनुरोधित मेथड `method_name` पैरामीटर में भेजा जाता है। यह फ़ंक्शन सीरियल पोर्ट पर कॉल किए गए मेथड को प्रिंट करता है, फिर मेथड नाम के आधार पर रिले को चालू या बंद करता है।

    > 💁 इसे एक सिंगल डायरेक्ट मेथड रिक्वेस्ट में भी लागू किया जा सकता है, जिसमें रिले की इच्छित स्थिति को एक पेलोड में पास किया जा सकता है जिसे मेथड रिक्वेस्ट के साथ पास किया जा सकता है और `payload` पैरामीटर से उपलब्ध कराया जा सकता है।

1. `directMethodCallback` फ़ंक्शन के अंत में निम्नलिखित कोड जोड़ें:

    ```cpp
    char resultBuff[16];
    sprintf(resultBuff, "{\"Result\":\"\"}");
    *response_size = strlen(resultBuff);
    *response = (unsigned char *)malloc(*response_size);
    memcpy(*response, resultBuff, *response_size);

    return IOTHUB_CLIENT_OK;
    ```

    डायरेक्ट मेथड रिक्वेस्ट को एक प्रतिक्रिया की आवश्यकता होती है, और प्रतिक्रिया दो भागों में होती है - एक टेक्स्ट के रूप में प्रतिक्रिया और एक रिटर्न कोड। यह कोड निम्नलिखित JSON डॉक्यूमेंट के रूप में एक परिणाम बनाएगा:

    ```JSON
    {
        "Result": ""
    }
    ```

    इसे `response` पैरामीटर में कॉपी किया जाता है, और इस प्रतिक्रिया का आकार `response_size` पैरामीटर में सेट किया जाता है। यह कोड फिर `IOTHUB_CLIENT_OK` लौटाता है ताकि दिखाया जा सके कि मेथड को सही तरीके से हैंडल किया गया।

1. इस कॉलबैक को `connectIoTHub` फ़ंक्शन के अंत में वायर करें:

    ```cpp
    IoTHubClient_LL_SetDeviceMethodCallback(_device_ll_handle, directMethodCallback, NULL);
    ```

1. `loop` फ़ंक्शन `IoTHubDeviceClient_LL_DoWork` फ़ंक्शन को IoT Hub द्वारा भेजे गए इवेंट्स को प्रोसेस करने के लिए कॉल करेगा। इसे `delay` के कारण केवल हर 10 सेकंड में कॉल किया जाता है, जिसका मतलब है कि डायरेक्ट मेथड केवल हर 10 सेकंड में प्रोसेस किए जाते हैं। इसे अधिक कुशल बनाने के लिए, 10 सेकंड की देरी को कई छोटी देरी के रूप में लागू किया जा सकता है, हर बार `IoTHubDeviceClient_LL_DoWork` को कॉल करते हुए। ऐसा करने के लिए, `loop` फ़ंक्शन के ऊपर निम्नलिखित कोड जोड़ें:

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

    यह कोड बार-बार लूप करेगा, `IoTHubDeviceClient_LL_DoWork` को कॉल करेगा और हर बार 100ms के लिए देरी करेगा। यह जितनी बार आवश्यक हो उतनी बार ऐसा करेगा ताकि `delay_time` पैरामीटर में दिए गए समय के लिए देरी की जा सके। इसका मतलब है कि डिवाइस डायरेक्ट मेथड रिक्वेस्ट को प्रोसेस करने के लिए अधिकतम 100ms तक इंतजार कर रहा है।

1. `loop` फ़ंक्शन में, `IoTHubDeviceClient_LL_DoWork` को कॉल करने को हटा दें, और `delay(10000)` कॉल को निम्नलिखित से बदलें ताकि इस नए फ़ंक्शन को कॉल किया जा सके:

    ```cpp
    work_delay(10000);
    ```

> 💁 आप इस कोड को [code/wio-terminal](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/wio-terminal) फोल्डर में पा सकते हैं।

😀 आपका मिट्टी की नमी सेंसर प्रोग्राम आपके IoT Hub से कनेक्ट हो गया है!

**अस्वीकरण**:  
यह दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) का उपयोग करके अनुवादित किया गया है। जबकि हम सटीकता सुनिश्चित करने का प्रयास करते हैं, कृपया ध्यान दें कि स्वचालित अनुवाद में त्रुटियां या अशुद्धियां हो सकती हैं। मूल भाषा में उपलब्ध मूल दस्तावेज़ को प्रामाणिक स्रोत माना जाना चाहिए। महत्वपूर्ण जानकारी के लिए, पेशेवर मानव अनुवाद की सिफारिश की जाती है। इस अनुवाद के उपयोग से उत्पन्न किसी भी गलतफहमी या गलत व्याख्या के लिए हम उत्तरदायी नहीं हैं।