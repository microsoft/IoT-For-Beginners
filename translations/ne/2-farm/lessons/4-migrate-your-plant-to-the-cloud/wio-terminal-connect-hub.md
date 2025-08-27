<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "28320305a35ea3bc59c41fe146a2e6ed",
  "translation_date": "2025-08-27T12:05:15+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/wio-terminal-connect-hub.md",
  "language_code": "ne"
}
-->
# आफ्नो IoT उपकरणलाई क्लाउडसँग जडान गर्नुहोस् - Wio Terminal

यस पाठको यस भागमा, तपाईं आफ्नो Wio Terminal लाई IoT Hub सँग जडान गर्नुहुनेछ, टेलिमेट्री पठाउन र आदेशहरू प्राप्त गर्न।

## आफ्नो उपकरणलाई IoT Hub सँग जडान गर्नुहोस्

अर्को चरण भनेको आफ्नो उपकरणलाई IoT Hub सँग जडान गर्नु हो।

### कार्य - IoT Hub सँग जडान गर्नुहोस्

1. VS Code मा `soil-moisture-sensor` प्रोजेक्ट खोल्नुहोस्।

1. `platformio.ini` फाइल खोल्नुहोस्। `knolleary/PubSubClient` लाइब्रेरी निर्भरता हटाउनुहोस्। यो सार्वजनिक MQTT ब्रोकरसँग जडान गर्न प्रयोग गरिएको थियो, र IoT Hub सँग जडान गर्न आवश्यक छैन।

1. तलका लाइब्रेरी निर्भरता थप्नुहोस्:

    ```ini
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    arduino-libraries/AzureIoTHub @ 1.6.0
    azure/AzureIoTUtility @ 1.6.1
    azure/AzureIoTProtocol_MQTT @ 1.6.0
    azure/AzureIoTProtocol_HTTP @ 1.6.0
    azure/AzureIoTSocket_WiFi @ 1.0.2
    ```

    `Seeed Arduino RTC` लाइब्रेरीले Wio Terminal मा वास्तविक समय घडीसँग अन्तरक्रिया गर्न कोड प्रदान गर्दछ, जुन समय ट्र्याक गर्न प्रयोग गरिन्छ। बाँकी लाइब्रेरीहरूले तपाईंको IoT उपकरणलाई IoT Hub सँग जडान गर्न अनुमति दिन्छ।

1. `platformio.ini` फाइलको तलमा निम्न थप्नुहोस्:

    ```ini
    build_flags =
        -DDONT_USE_UPLOADTOBLOB
    ```

    यो कम्पाइलर फ्ल्याग सेट गर्दछ जुन Arduino IoT Hub कोड कम्पाइल गर्दा आवश्यक हुन्छ।

1. `config.h` हेडर फाइल खोल्नुहोस्। सबै MQTT सेटिङहरू हटाउनुहोस् र उपकरण कनेक्शन स्ट्रिङको लागि निम्न स्थिरांक थप्नुहोस्:

    ```cpp
    // IoT Hub settings
    const char *CONNECTION_STRING = "<connection string>";
    ```

    `<connection string>` लाई तपाईंले पहिले प्रतिलिपि गरेको उपकरणको कनेक्शन स्ट्रिङले प्रतिस्थापन गर्नुहोस्।

1. IoT Hub सँगको जडान समय-आधारित टोकन प्रयोग गर्दछ। यसको मतलब IoT उपकरणले हालको समय थाहा पाउन आवश्यक छ। Windows, macOS वा Linux जस्ता अपरेटिङ सिस्टमहरू जस्तो, माइक्रोकन्ट्रोलरहरूले इन्टरनेटमार्फत स्वतः हालको समय समक्रमण गर्दैनन्। यसको मतलब तपाईंले [NTP](https://wikipedia.org/wiki/Network_Time_Protocol) सर्भरबाट हालको समय प्राप्त गर्न कोड थप्न आवश्यक छ। एकपटक समय प्राप्त भएपछि, यसलाई Wio Terminal मा वास्तविक समय घडीमा भण्डारण गर्न सकिन्छ, जसले उपकरणले पावर गुमाएको छैन भने सही समय पछि अनुरोध गर्न अनुमति दिन्छ। `ntp.h` नामक नयाँ फाइल निम्न कोडसँग थप्नुहोस्:

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

    यस कोडको विवरण यस पाठको दायराभन्दा बाहिर छ। यसले `initTime` नामक एक फंक्शन परिभाषित गर्दछ जसले NTP सर्भरबाट हालको समय प्राप्त गर्दछ र Wio Terminal मा घडी सेट गर्न प्रयोग गर्दछ।

1. `main.cpp` फाइल खोल्नुहोस् र सबै MQTT कोड हटाउनुहोस्, जसमा `PubSubClient.h` हेडर फाइल, `PubSubClient` भेरिएबलको घोषणा, `reconnectMQTTClient` र `createMQTTClient` मेथडहरू, र यी भेरिएबलहरू र मेथडहरूमा कुनै पनि कलहरू समावेश छन्। यो फाइलमा केवल WiFi सँग जडान गर्न, माटोको चिसोपन प्राप्त गर्न र यससँग JSON डकुमेन्ट सिर्जना गर्न कोड समावेश गर्नुपर्छ।

1. IoT Hub लाइब्रेरीहरू र समय सेट गर्न हेडर फाइलहरू समावेश गर्न `main.cpp` फाइलको माथि निम्न `#include` निर्देशनहरू थप्नुहोस्:

    ```cpp
    #include <AzureIoTHub.h>
    #include <AzureIoTProtocol_MQTT.h>
    #include <iothubtransportmqtt.h>
    #include "ntp.h"
    ```

1. हालको समय सेट गर्न `setup` फंक्शनको अन्त्यमा निम्न कल थप्नुहोस्:

    ```cpp
    initTime();
    ```

1. फाइलको माथि, समावेश निर्देशनहरूको ठीक तल, निम्न भेरिएबल घोषणा थप्नुहोस्:

    ```cpp
    IOTHUB_DEVICE_CLIENT_LL_HANDLE _device_ll_handle;
    ```

    यसले `IOTHUB_DEVICE_CLIENT_LL_HANDLE` घोषणा गर्दछ, IoT Hub सँगको जडानको लागि ह्यान्डल।

1. यसको तल, निम्न कोड थप्नुहोस्:

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

    यसले एक क्यालब्याक फंक्शन घोषणा गर्दछ जुन IoT Hub सँगको जडानको स्थिति परिवर्तन हुँदा, जस्तै जडान वा डिस्कनेक्ट हुँदा, कल गरिन्छ। स्थिति सिरियल पोर्टमा पठाइन्छ।

1. यसको तल, IoT Hub सँग जडान गर्न फंक्शन थप्नुहोस्:

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

    यो कोडले IoT Hub लाइब्रेरी कोडलाई इनिसियलाइज गर्दछ, त्यसपछि `config.h` हेडर फाइलमा कनेक्शन स्ट्रिङ प्रयोग गरेर जडान सिर्जना गर्दछ। यो जडान MQTT मा आधारित छ। यदि जडान असफल हुन्छ भने, यो सिरियल पोर्टमा पठाइन्छ - यदि तपाईंले यो आउटपुटमा देख्नुभयो भने, कनेक्शन स्ट्रिङ जाँच गर्नुहोस्। अन्ततः कनेक्शन स्थिति क्यालब्याक सेटअप गरिन्छ।

1. `setup` फंक्शनमा `initTime` कलको तल यो फंक्शन कल गर्नुहोस्:

    ```cpp
    connectIoTHub();
    ```

1. MQTT क्लाइन्टको जस्तै, यो कोड एकल थ्रेडमा चल्छ त्यसैले हबले पठाएको सन्देशहरू र हबमा पठाइएका सन्देशहरू प्रशोधन गर्न समय चाहिन्छ। `loop` फंक्शनको माथि निम्न थप्नुहोस्:

    ```cpp
    IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
    ```

1. यो कोड निर्माण र अपलोड गर्नुहोस्। तपाईं सिरियल मोनिटरमा जडान देख्नुहुनेछ:

    ```output
    Connecting to WiFi..
    Connected!
    Fetched NTP epoch time is: 1619983687
    Sending telemetry {"soil_moisture":391}
    The device client is connected to iothub
    ```

    आउटपुटमा तपाईंले NTP समय प्राप्त भइरहेको देख्न सक्नुहुन्छ, त्यसपछि उपकरण क्लाइन्ट जडान भइरहेको देख्न सक्नुहुन्छ। जडान गर्न केही सेकेन्ड लाग्न सक्छ, त्यसैले उपकरण जडान भइरहेको बेला तपाईंले आउटपुटमा माटोको चिसोपन देख्न सक्नुहुन्छ।

    > 💁 तपाईं NTP को UNIX समयलाई [unixtimestamp.com](https://www.unixtimestamp.com) जस्ता वेबसाइट प्रयोग गरेर पढ्न मिल्ने संस्करणमा रूपान्तरण गर्न सक्नुहुन्छ।

## टेलिमेट्री पठाउनुहोस्

अब तपाईंको उपकरण जडान भएको छ, तपाईं MQTT ब्रोकरको सट्टा IoT Hub मा टेलिमेट्री पठाउन सक्नुहुन्छ।

### कार्य - टेलिमेट्री पठाउनुहोस्

1. `setup` फंक्शनको माथि निम्न फंक्शन थप्नुहोस्:

    ```cpp
    void sendTelemetry(const char *telemetry)
    {
        IOTHUB_MESSAGE_HANDLE message_handle = IoTHubMessage_CreateFromString(telemetry);
        IoTHubDeviceClient_LL_SendEventAsync(_device_ll_handle, message_handle, NULL, NULL);
        IoTHubMessage_Destroy(message_handle);
    }
    ```

    यो कोडले पास गरिएको स्ट्रिङबाट IoT Hub सन्देश सिर्जना गर्दछ, यसलाई हबमा पठाउँछ, त्यसपछि सन्देश वस्तु सफा गर्दछ।

1. सिरियल पोर्टमा टेलिमेट्री पठाउने लाइनको ठीक पछि `loop` फंक्शनमा यो कोड कल गर्नुहोस्:

    ```cpp
    sendTelemetry(telemetry.c_str());
    ```

## आदेशहरू ह्यान्डल गर्नुहोस्

तपाईंको उपकरणले रिले नियन्त्रण गर्न सर्वर कोडबाट आदेश ह्यान्डल गर्न आवश्यक छ। यो प्रत्यक्ष विधि अनुरोधको रूपमा पठाइन्छ।

## कार्य - प्रत्यक्ष विधि अनुरोध ह्यान्डल गर्नुहोस्

1. `connectIoTHub` फंक्शनको अघि निम्न कोड थप्नुहोस्:

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

    यो कोडले क्यालब्याक मेथड परिभाषित गर्दछ जुन IoT Hub लाइब्रेरीले प्रत्यक्ष विधि अनुरोध प्राप्त गर्दा कल गर्न सक्छ। अनुरोध गरिएको विधि `method_name` प्यारामिटरमा पठाइन्छ। यो फंक्शनले सिरियल पोर्टमा कल गरिएको विधि प्रिन्ट गर्दछ, त्यसपछि विधि नामको आधारमा रिले अन वा अफ गर्दछ।

    > 💁 यो एकल प्रत्यक्ष विधि अनुरोधमा पनि कार्यान्वयन गर्न सकिन्छ, रिलेको इच्छित अवस्था अनुरोधको साथ पास गर्न सकिने पेलोडमा पास गर्दै, जुन `payload` प्यारामिटरबाट उपलब्ध हुन्छ।

1. `directMethodCallback` फंक्शनको अन्त्यमा निम्न कोड थप्नुहोस्:

    ```cpp
    char resultBuff[16];
    sprintf(resultBuff, "{\"Result\":\"\"}");
    *response_size = strlen(resultBuff);
    *response = (unsigned char *)malloc(*response_size);
    memcpy(*response, resultBuff, *response_size);

    return IOTHUB_CLIENT_OK;
    ```

    प्रत्यक्ष विधि अनुरोधहरूलाई प्रतिक्रिया आवश्यक छ, र प्रतिक्रिया दुई भागमा हुन्छ - पाठको रूपमा प्रतिक्रिया, र रिटर्न कोड। यो कोडले निम्न JSON डकुमेन्टको रूपमा परिणाम सिर्जना गर्दछ:

    ```JSON
    {
        "Result": ""
    }
    ```

    यो त्यसपछि `response` प्यारामिटरमा प्रतिलिपि गरिन्छ, र यो प्रतिक्रियाको आकार `response_size` प्यारामिटरमा सेट गरिन्छ। यो कोडले विधि सही रूपमा ह्यान्डल गरिएको देखाउन `IOTHUB_CLIENT_OK` फर्काउँछ।

1. क्यालब्याकलाई जडान गर्न `connectIoTHub` फंक्शनको अन्त्यमा निम्न थप्नुहोस्:

    ```cpp
    IoTHubClient_LL_SetDeviceMethodCallback(_device_ll_handle, directMethodCallback, NULL);
    ```

1. `loop` फंक्शनले IoT Hub द्वारा पठाइएका घटनाहरू प्रशोधन गर्न `IoTHubDeviceClient_LL_DoWork` फंक्शन कल गर्नेछ। यो केवल `delay` को कारणले प्रत्येक 10 सेकेन्डमा कल गरिन्छ, जसको मतलब प्रत्यक्ष विधिहरू केवल प्रत्येक 10 सेकेन्डमा प्रशोधित हुन्छन्। यसलाई अझ कुशल बनाउन, 10 सेकेन्डको ढिलाइलाई धेरै छोटो ढिलाइको रूपमा कार्यान्वयन गर्न सकिन्छ, प्रत्येक पटक `IoTHubDeviceClient_LL_DoWork` कल गर्दै। यसलाई गर्न `loop` फंक्शनको माथि निम्न कोड थप्नुहोस्:

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

    यो कोडले बारम्बार लूप गर्नेछ, `IoTHubDeviceClient_LL_DoWork` कल गर्नेछ र प्रत्येक पटक 100ms को लागि ढिलाइ गर्नेछ। यो `delay_time` प्यारामिटरमा दिइएको समयको लागि ढिलाइ गर्न आवश्यक जति पटक यो गर्नेछ। यसको मतलब उपकरणले प्रत्यक्ष विधि अनुरोध प्रशोधन गर्न 100ms भन्दा बढी कुर्नु पर्दैन।

1. `loop` फंक्शनमा, `IoTHubDeviceClient_LL_DoWork` कल हटाउनुहोस्, र `delay(10000)` कललाई निम्नसँग प्रतिस्थापन गर्नुहोस्:

    ```cpp
    work_delay(10000);
    ```

> 💁 तपाईं यो कोड [code/wio-terminal](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/wio-terminal) फोल्डरमा फेला पार्न सक्नुहुन्छ।

😀 तपाईंको माटोको चिसोपन सेन्सर प्रोग्राम IoT Hub सँग जडान भएको छ!

---

**अस्वीकरण**:  
यो दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) प्रयोग गरेर अनुवाद गरिएको छ। हामी शुद्धताको लागि प्रयास गर्छौं, तर कृपया ध्यान दिनुहोस् कि स्वचालित अनुवादमा त्रुटिहरू वा अशुद्धताहरू हुन सक्छ। यसको मूल भाषा मा रहेको मूल दस्तावेज़लाई आधिकारिक स्रोत मानिनुपर्छ। महत्वपूर्ण जानकारीको लागि, व्यावसायिक मानव अनुवाद सिफारिस गरिन्छ। यस अनुवादको प्रयोगबाट उत्पन्न हुने कुनै पनि गलतफहमी वा गलत व्याख्याको लागि हामी जिम्मेवार हुने छैनौं।