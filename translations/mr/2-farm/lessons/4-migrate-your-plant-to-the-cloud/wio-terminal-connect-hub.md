<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "28320305a35ea3bc59c41fe146a2e6ed",
  "translation_date": "2025-08-27T12:04:42+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/wio-terminal-connect-hub.md",
  "language_code": "mr"
}
-->
# तुमचा IoT डिव्हाइस क्लाउडशी कनेक्ट करा - Wio Terminal

या धड्याच्या या भागात, तुम्ही तुमचा Wio Terminal IoT Hub शी कनेक्ट कराल, टेलिमेट्री पाठवण्यासाठी आणि कमांड्स प्राप्त करण्यासाठी.

## तुमचा डिव्हाइस IoT Hub शी कनेक्ट करा

पुढील पायरी म्हणजे तुमचा डिव्हाइस IoT Hub शी कनेक्ट करणे.

### कार्य - IoT Hub शी कनेक्ट करा

1. VS Code मध्ये `soil-moisture-sensor` प्रोजेक्ट उघडा.

1. `platformio.ini` फाइल उघडा. `knolleary/PubSubClient` लायब्ररी डिपेंडन्सी काढून टाका. ही सार्वजनिक MQTT ब्रोकर्सशी कनेक्ट होण्यासाठी वापरली जात होती, पण IoT Hub शी कनेक्ट होण्यासाठी गरजेची नाही.

1. खालील लायब्ररी डिपेंडन्सी जोडा:

    ```ini
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    arduino-libraries/AzureIoTHub @ 1.6.0
    azure/AzureIoTUtility @ 1.6.1
    azure/AzureIoTProtocol_MQTT @ 1.6.0
    azure/AzureIoTProtocol_HTTP @ 1.6.0
    azure/AzureIoTSocket_WiFi @ 1.0.2
    ```

    `Seeed Arduino RTC` लायब्ररी Wio Terminal मधील रिअल-टाइम क्लॉकशी संवाद साधण्यासाठी कोड पुरवते, जो वेळ ट्रॅक करण्यासाठी वापरला जातो. उर्वरित लायब्ररी तुमच्या IoT डिव्हाइसला IoT Hub शी कनेक्ट होण्यास परवानगी देतात.

1. `platformio.ini` फाइलच्या शेवटी खालील जोडा:

    ```ini
    build_flags =
        -DDONT_USE_UPLOADTOBLOB
    ```

    हे एक कंपायलर फ्लॅग सेट करते, जे Arduino IoT Hub कोड कॉम्पाइल करताना आवश्यक आहे.

1. `config.h` हेडर फाइल उघडा. सर्व MQTT सेटिंग्ज काढून टाका आणि डिव्हाइस कनेक्शन स्ट्रिंगसाठी खालील स्थिरांक जोडा:

    ```cpp
    // IoT Hub settings
    const char *CONNECTION_STRING = "<connection string>";
    ```

    `<connection string>` च्या जागी तुम्ही आधी कॉपी केलेला तुमच्या डिव्हाइसचा कनेक्शन स्ट्रिंग टाका.

1. IoT Hub शी कनेक्शनसाठी वेळ-आधारित टोकन वापरले जाते. याचा अर्थ IoT डिव्हाइसला वर्तमान वेळ माहित असणे आवश्यक आहे. Windows, macOS किंवा Linux सारख्या ऑपरेटिंग सिस्टम्सप्रमाणे, मायक्रोकंट्रोलर्स इंटरनेटवरून आपोआप वर्तमान वेळ सिंक्रोनाइझ करत नाहीत. याचा अर्थ तुम्हाला [NTP](https://wikipedia.org/wiki/Network_Time_Protocol) सर्व्हरकडून वर्तमान वेळ मिळवण्यासाठी कोड जोडावा लागेल. वेळ मिळाल्यानंतर, तो Wio Terminal मधील रिअल-टाइम क्लॉकमध्ये साठवला जाऊ शकतो, ज्यामुळे डिव्हाइसने पॉवर गमावली नाही असे गृहीत धरून भविष्यात योग्य वेळ मिळवता येईल. `ntp.h` नावाची नवीन फाइल तयार करा आणि त्यात खालील कोड जोडा:

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

    या कोडचा तपशील या धड्याच्या कक्षेबाहेर आहे. हा `initTime` नावाचा फंक्शन परिभाषित करतो, जो NTP सर्व्हरकडून वर्तमान वेळ मिळवतो आणि Wio Terminal वरील क्लॉक सेट करण्यासाठी वापरतो.

1. `main.cpp` फाइल उघडा आणि सर्व MQTT कोड काढून टाका, ज्यामध्ये `PubSubClient.h` हेडर फाइल, `PubSubClient` व्हेरिएबलची घोषणा, `reconnectMQTTClient` आणि `createMQTTClient` पद्धती, तसेच या व्हेरिएबल्स आणि पद्धतींना केलेले कॉल्स समाविष्ट आहेत. या फाइलमध्ये फक्त WiFi शी कनेक्ट होण्यासाठी, मातीतील ओलावा मिळवण्यासाठी आणि त्यासह JSON डॉक्युमेंट तयार करण्यासाठी कोड असावा.

1. IoT Hub लायब्ररींसाठी आणि वेळ सेट करण्यासाठी हेडर फाइल्स समाविष्ट करण्यासाठी `main.cpp` फाइलच्या शीर्षस्थानी खालील `#include` निर्देश जोडा:

    ```cpp
    #include <AzureIoTHub.h>
    #include <AzureIoTProtocol_MQTT.h>
    #include <iothubtransportmqtt.h>
    #include "ntp.h"
    ```

1. वर्तमान वेळ सेट करण्यासाठी `setup` फंक्शनच्या शेवटी खालील कॉल जोडा:

    ```cpp
    initTime();
    ```

1. फाइलच्या शीर्षस्थानी, `include` निर्देशांच्या खालील व्हेरिएबल घोषणा जोडा:

    ```cpp
    IOTHUB_DEVICE_CLIENT_LL_HANDLE _device_ll_handle;
    ```

    हे `IOTHUB_DEVICE_CLIENT_LL_HANDLE` घोषित करते, जे IoT Hub शी कनेक्शनसाठी हँडल आहे.

1. याखाली, खालील कोड जोडा:

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

    हे एक कॉलबॅक फंक्शन घोषित करते, जेव्हा IoT Hub शी कनेक्शनची स्थिती बदलते, जसे की कनेक्ट होणे किंवा डिस्कनेक्ट होणे, तेव्हा कॉल केले जाते. स्थिती सिरीयल पोर्टवर पाठवली जाते.

1. याखाली, IoT Hub शी कनेक्ट होण्यासाठी एक फंक्शन जोडा:

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

    हा कोड IoT Hub लायब्ररी कोड प्रारंभ करतो, नंतर `config.h` हेडर फाइलमधील कनेक्शन स्ट्रिंग वापरून कनेक्शन तयार करतो. हे कनेक्शन MQTT वर आधारित आहे. जर कनेक्शन अयशस्वी झाले, तर ते सिरीयल पोर्टवर पाठवले जाते - जर तुम्हाला आउटपुटमध्ये हे दिसले, तर कनेक्शन स्ट्रिंग तपासा. शेवटी, कनेक्शन स्थिती कॉलबॅक सेट केला जातो.

1. `setup` फंक्शनमध्ये `initTime` कॉलच्या खाली हे फंक्शन कॉल करा:

    ```cpp
    connectIoTHub();
    ```

1. MQTT क्लायंटप्रमाणेच, हा कोड एका सिंगल थ्रेडवर चालतो, त्यामुळे हबद्वारे पाठवलेले आणि हबला पाठवलेले संदेश प्रक्रिया करण्यासाठी वेळ आवश्यक आहे. `loop` फंक्शनच्या शीर्षस्थानी खालील जोडा:

    ```cpp
    IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
    ```

1. हा कोड बिल्ड आणि अपलोड करा. तुम्हाला सिरीयल मॉनिटरमध्ये कनेक्शन दिसेल:

    ```output
    Connecting to WiFi..
    Connected!
    Fetched NTP epoch time is: 1619983687
    Sending telemetry {"soil_moisture":391}
    The device client is connected to iothub
    ```

    आउटपुटमध्ये तुम्ही NTP वेळ मिळवताना पाहू शकता, त्यानंतर डिव्हाइस क्लायंट कनेक्ट होत आहे. कनेक्ट होण्यासाठी काही सेकंद लागू शकतात, त्यामुळे डिव्हाइस कनेक्ट होत असताना तुम्हाला आउटपुटमध्ये मातीतील ओलावा दिसू शकतो.

    > 💁 तुम्ही NTP साठी UNIX वेळ अधिक वाचनीय स्वरूपात [unixtimestamp.com](https://www.unixtimestamp.com) सारख्या वेबसाइटचा वापर करून रूपांतरित करू शकता.

## टेलिमेट्री पाठवा

आता तुमचा डिव्हाइस कनेक्ट झाला आहे, तुम्ही MQTT ब्रोकर्सऐवजी IoT Hub ला टेलिमेट्री पाठवू शकता.

### कार्य - टेलिमेट्री पाठवा

1. `setup` फंक्शनच्या वर खालील फंक्शन जोडा:

    ```cpp
    void sendTelemetry(const char *telemetry)
    {
        IOTHUB_MESSAGE_HANDLE message_handle = IoTHubMessage_CreateFromString(telemetry);
        IoTHubDeviceClient_LL_SendEventAsync(_device_ll_handle, message_handle, NULL, NULL);
        IoTHubMessage_Destroy(message_handle);
    }
    ```

    हा कोड पास केलेल्या स्ट्रिंगमधून IoT Hub संदेश तयार करतो, तो हबला पाठवतो आणि नंतर संदेश ऑब्जेक्ट साफ करतो.

1. `loop` फंक्शनमध्ये, टेलिमेट्री सिरीयल पोर्टवर पाठवल्यानंतर लगेच हा कोड कॉल करा:

    ```cpp
    sendTelemetry(telemetry.c_str());
    ```

## कमांड्स हाताळा

तुमच्या डिव्हाइसला रिले नियंत्रित करण्यासाठी सर्व्हर कोडमधून आलेला कमांड हाताळणे आवश्यक आहे. हे डायरेक्ट मेथड रिक्वेस्ट म्हणून पाठवले जाते.

### कार्य - डायरेक्ट मेथड रिक्वेस्ट हाताळा

1. `connectIoTHub` फंक्शनच्या आधी खालील कोड जोडा:

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

    हा कोड एक कॉलबॅक पद्धत परिभाषित करतो, जी IoT Hub लायब्ररीला डायरेक्ट मेथड रिक्वेस्ट प्राप्त झाल्यावर कॉल करू देते. रिक्वेस्ट केलेली पद्धत `method_name` पॅरामीटरमध्ये पाठवली जाते. ही फंक्शन सिरीयल पोर्टवर कॉल केलेली पद्धत प्रिंट करते, नंतर पद्धत नावानुसार रिले चालू किंवा बंद करते.

    > 💁 हे एका सिंगल डायरेक्ट मेथड रिक्वेस्टमध्ये देखील अंमलात आणले जाऊ शकते, ज्यामध्ये रिलेची इच्छित स्थिती रिक्वेस्टसह पाठवली जाऊ शकते आणि ती `payload` पॅरामीटरमधून उपलब्ध असते.

1. `directMethodCallback` फंक्शनच्या शेवटी खालील कोड जोडा:

    ```cpp
    char resultBuff[16];
    sprintf(resultBuff, "{\"Result\":\"\"}");
    *response_size = strlen(resultBuff);
    *response = (unsigned char *)malloc(*response_size);
    memcpy(*response, resultBuff, *response_size);

    return IOTHUB_CLIENT_OK;
    ```

    डायरेक्ट मेथड रिक्वेस्टला प्रतिसाद आवश्यक असतो, आणि प्रतिसाद दोन भागांमध्ये असतो - मजकूर स्वरूपात प्रतिसाद आणि रिटर्न कोड. हा कोड खालील JSON डॉक्युमेंट तयार करतो:

    ```JSON
    {
        "Result": ""
    }
    ```

    नंतर हा `response` पॅरामीटरमध्ये कॉपी केला जातो, आणि या प्रतिसादाचा आकार `response_size` पॅरामीटरमध्ये सेट केला जातो. हा कोड नंतर `IOTHUB_CLIENT_OK` परत करतो, जेणेकरून पद्धत योग्यरित्या हाताळली गेली हे दाखवले जाईल.

1. `connectIoTHub` फंक्शनच्या शेवटी खालील कोड जोडा:

    ```cpp
    IoTHubClient_LL_SetDeviceMethodCallback(_device_ll_handle, directMethodCallback, NULL);
    ```

1. `loop` फंक्शन `IoTHubDeviceClient_LL_DoWork` फंक्शनला IoT Hub ने पाठवलेल्या इव्हेंट्स प्रक्रिया करण्यासाठी कॉल करेल. `delay` मुळे हे फक्त प्रत्येक 10 सेकंदांनी कॉल केले जाते, याचा अर्थ डायरेक्ट मेथड्स फक्त प्रत्येक 10 सेकंदांनी प्रक्रिया केल्या जातात. हे अधिक कार्यक्षम बनवण्यासाठी, 10 सेकंदांचा `delay` अनेक लहान `delay` मध्ये अंमलात आणला जाऊ शकतो, प्रत्येक वेळी `IoTHubDeviceClient_LL_DoWork` कॉल करून. हे करण्यासाठी, `loop` फंक्शनच्या वर खालील कोड जोडा:

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

    हा कोड वारंवार लूप करतो, `IoTHubDeviceClient_LL_DoWork` कॉल करतो आणि प्रत्येक वेळी 100ms साठी `delay` करतो. दिलेल्या `delay_time` पॅरामीटरसाठी विलंब करण्यासाठी आवश्यक तितक्या वेळा हे करतो. याचा अर्थ डिव्हाइस डायरेक्ट मेथड रिक्वेस्ट प्रक्रिया करण्यासाठी जास्तीत जास्त 100ms प्रतीक्षा करत आहे.

1. `loop` फंक्शनमध्ये, `IoTHubDeviceClient_LL_DoWork` कॉल काढा, आणि `delay(10000)` कॉल खालील कोडने बदला:

    ```cpp
    work_delay(10000);
    ```

> 💁 तुम्हाला हा कोड [code/wio-terminal](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/wio-terminal) फोल्डरमध्ये सापडेल.

😀 तुमचा मातीतील ओलावा सेन्सर प्रोग्राम IoT Hub शी कनेक्ट झाला आहे!

---

**अस्वीकरण**:  
हा दस्तऐवज AI भाषांतर सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) चा वापर करून भाषांतरित करण्यात आला आहे. आम्ही अचूकतेसाठी प्रयत्नशील असलो तरी कृपया लक्षात ठेवा की स्वयंचलित भाषांतरांमध्ये त्रुटी किंवा अचूकतेचा अभाव असू शकतो. मूळ भाषेतील दस्तऐवज हा अधिकृत स्रोत मानला जावा. महत्त्वाच्या माहितीसाठी व्यावसायिक मानवी भाषांतराची शिफारस केली जाते. या भाषांतराचा वापर करून उद्भवलेल्या कोणत्याही गैरसमज किंवा चुकीच्या अर्थासाठी आम्ही जबाबदार राहणार नाही.