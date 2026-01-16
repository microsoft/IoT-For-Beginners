<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d6faf0e8d3c2d6d20c0aef2a305dab18",
  "translation_date": "2025-08-27T12:33:37+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md",
  "language_code": "ne"
}
-->
# आफ्नो नाइटलाइटलाई इन्टरनेटबाट नियन्त्रण गर्नुहोस् - Wio Terminal

IoT उपकरणलाई *test.mosquitto.org* सँग MQTT प्रयोग गरेर टेलिमेट्री मानहरू पठाउन र LED नियन्त्रण गर्न आदेशहरू प्राप्त गर्न कोड गर्न आवश्यक छ।

यस पाठको यस भागमा, तपाईं आफ्नो Wio Terminal लाई MQTT ब्रोकरसँग जडान गर्नुहुनेछ।

## WiFi र MQTT Arduino लाइब्रेरीहरू स्थापना गर्नुहोस्

MQTT ब्रोकरसँग संवाद गर्न, तपाईंले Wio Terminal मा WiFi चिप प्रयोग गर्न र MQTT सँग संवाद गर्न केही Arduino लाइब्रेरीहरू स्थापना गर्न आवश्यक छ। Arduino उपकरणहरूको लागि विकास गर्दा, तपाईंले खुला स्रोत कोड समावेश गर्ने र धेरै प्रकारका क्षमताहरू कार्यान्वयन गर्ने लाइब्रेरीहरूको विस्तृत दायरा प्रयोग गर्न सक्नुहुन्छ। Seeed ले Wio Terminal का लागि लाइब्रेरीहरू प्रकाशित गर्दछ जसले यसलाई WiFi मार्फत संवाद गर्न अनुमति दिन्छ। अन्य विकासकर्ताहरूले MQTT ब्रोकरहरूसँग संवाद गर्न लाइब्रेरीहरू प्रकाशित गरेका छन्, र तपाईं यी लाइब्रेरीहरू आफ्नो उपकरणसँग प्रयोग गर्नुहुनेछ।

यी लाइब्रेरीहरू स्रोत कोडको रूपमा उपलब्ध छन्, जसलाई PlatformIO मा स्वचालित रूपमा आयात गर्न र तपाईंको उपकरणको लागि कम्पाइल गर्न सकिन्छ। यसरी, Arduino लाइब्रेरीहरू कुनै पनि उपकरणमा काम गर्नेछन् जसले Arduino फ्रेमवर्कलाई समर्थन गर्दछ, यदि उपकरणसँग उक्त लाइब्रेरीले आवश्यक पर्ने विशिष्ट हार्डवेयर छ भने। केही लाइब्रेरीहरू, जस्तै Seeed WiFi लाइब्रेरीहरू, निश्चित हार्डवेयरका लागि विशिष्ट हुन्छन्।

लाइब्रेरीहरू विश्वव्यापी रूपमा स्थापना गर्न सकिन्छ र आवश्यक परेमा कम्पाइल गर्न सकिन्छ, वा विशिष्ट प्रोजेक्टमा। यस कार्यको लागि, लाइब्रेरीहरू प्रोजेक्टमा स्थापना गरिनेछ।

✅ तपाईं [PlatformIO लाइब्रेरी डकुमेन्टेसन](https://docs.platformio.org/en/latest/librarymanager/index.html) मा लाइब्रेरी व्यवस्थापन र कसरी लाइब्रेरीहरू फेला पार्ने र स्थापना गर्ने बारे थप जान्न सक्नुहुन्छ।

### कार्य - WiFi र MQTT Arduino लाइब्रेरीहरू स्थापना गर्नुहोस्

Arduino लाइब्रेरीहरू स्थापना गर्नुहोस्।

1. VS Code मा नाइटलाइट प्रोजेक्ट खोल्नुहोस्।

1. `platformio.ini` फाइलको अन्त्यमा निम्न थप्नुहोस्:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
        seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
        seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    ```

    यसले Seeed WiFi लाइब्रेरीहरू आयात गर्दछ। `@ <number>` सिन्ट्याक्सले लाइब्रेरीको विशिष्ट संस्करणलाई जनाउँछ।

    > 💁 तपाईं `@ <number>` हटाएर सधैं लाइब्रेरीहरूको नवीनतम संस्करण प्रयोग गर्न सक्नुहुन्छ, तर पछिल्ला संस्करणहरूले तलको कोडसँग काम गर्ने ग्यारेन्टी हुँदैन। यहाँको कोडले लाइब्रेरीहरूको यस संस्करणसँग परीक्षण गरिएको छ।

    लाइब्रेरीहरू थप्नका लागि तपाईंले यत्ति मात्र गर्नुपर्छ। अर्को पटक PlatformIO ले प्रोजेक्ट निर्माण गर्दा, यसले यी लाइब्रेरीहरूको स्रोत कोड डाउनलोड गर्नेछ र यसलाई तपाईंको प्रोजेक्टमा कम्पाइल गर्नेछ।

1. `lib_deps` मा निम्न थप्नुहोस्:

    ```ini
    knolleary/PubSubClient @ 2.8
    ```

    यसले [PubSubClient](https://github.com/knolleary/pubsubclient), एक Arduino MQTT क्लाइन्ट आयात गर्दछ।

## WiFi सँग जडान गर्नुहोस्

अब Wio Terminal लाई WiFi सँग जडान गर्न सकिन्छ।

### कार्य - WiFi सँग जडान गर्नुहोस्

Wio Terminal लाई WiFi सँग जडान गर्नुहोस्।

1. `src` फोल्डरमा `config.h` नामको नयाँ फाइल बनाउनुहोस्। तपाईं यो `src` फोल्डर चयन गरेर, वा भित्रको `main.cpp` फाइल चयन गरेर, र एक्सप्लोररबाट **New file** बटन चयन गरेर गर्न सक्नुहुन्छ। यो बटन केवल तपाईंको कर्सर एक्सप्लोररमा हुँदा मात्र देखिन्छ।

    ![नयाँ फाइल बटन](../../../../../translated_images/ne/vscode-new-file-button.182702340fe6723c.png)

1. आफ्नो WiFi क्रेडेन्सियलहरूको लागि स्थिरांक परिभाषित गर्न यो फाइलमा निम्न कोड थप्नुहोस्:

    ```cpp
    #pragma once

    #include <string>
    
    using namespace std;
    
    // WiFi credentials
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    ```

    `<SSID>` लाई तपाईंको WiFi को SSID ले प्रतिस्थापन गर्नुहोस्। `<PASSWORD>` लाई तपाईंको WiFi पासवर्डले प्रतिस्थापन गर्नुहोस्।

1. `main.cpp` फाइल खोल्नुहोस्।

1. फाइलको माथि निम्न `#include` निर्देशनहरू थप्नुहोस्:

    ```cpp
    #include <PubSubClient.h>
    #include <rpcWiFi.h>
    #include <SPI.h>
    
    #include "config.h"
    ```

    यसले तपाईंले पहिले थपेका लाइब्रेरीहरूको हेडर फाइलहरू, साथै कन्फिग हेडर फाइल समावेश गर्दछ। यी हेडर फाइलहरू PlatformIO लाई लाइब्रेरीहरूको कोड ल्याउन भन्न आवश्यक छ। यी हेडर फाइलहरू स्पष्ट रूपमा समावेश नगरेसम्म, केही कोड कम्पाइल गरिने छैन र तपाईंलाई कम्पाइलर त्रुटिहरू प्राप्त हुनेछ।

1. `setup` फङ्सनको माथि निम्न कोड थप्नुहोस्:

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

    यो कोडले उपकरण WiFi सँग जडान नभएसम्म लुप गर्छ, र कन्फिग हेडर फाइलबाट SSID र पासवर्ड प्रयोग गरेर जडान प्रयास गर्छ।

1. पिनहरू कन्फिगर गरेपछि `setup` फङ्सनको तल यस फङ्सनलाई कल गर्नुहोस्।

    ```cpp
    connectWiFi();
    ```

1. WiFi जडान काम गरिरहेको छ कि छैन जाँच्न यो कोड तपाईंको उपकरणमा अपलोड गर्नुहोस्। तपाईंले यो सिरियल मोनिटरमा देख्नुहुनेछ।

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    ```

## MQTT सँग जडान गर्नुहोस्

Wio Terminal WiFi सँग जडान भएपछि, यो MQTT ब्रोकरसँग जडान गर्न सक्छ।

### कार्य - MQTT सँग जडान गर्नुहोस्

MQTT ब्रोकरसँग जडान गर्नुहोस्।

1. MQTT ब्रोकरको जडान विवरण परिभाषित गर्न `config.h` फाइलको अन्त्यमा निम्न कोड थप्नुहोस्:

    ```cpp
    // MQTT settings
    const string ID = "<ID>";
    
    const string BROKER = "test.mosquitto.org";
    const string CLIENT_NAME = ID + "nightlight_client";
    ```

    `<ID>` लाई एक अद्वितीय ID ले प्रतिस्थापन गर्नुहोस्, जुन यो उपकरण क्लाइन्टको नामको रूपमा प्रयोग हुनेछ, र पछि यस उपकरणले प्रकाशित र सदस्यता लिने विषयहरूको लागि। *test.mosquitto.org* ब्रोकर सार्वजनिक छ र धेरै व्यक्तिहरू, यस कार्यमा काम गरिरहेका अन्य विद्यार्थीहरू समेत, द्वारा प्रयोग गरिन्छ। अद्वितीय MQTT क्लाइन्ट नाम र विषय नामहरूले तपाईंको कोड अरू कसैको कोडसँग टकराउने छैन भन्ने सुनिश्चित गर्दछ। तपाईंले यो ID यस कार्यको पछि सर्भर कोड सिर्जना गर्दा पनि आवश्यक पर्न सक्छ।

    > 💁 तपाईं [GUIDGen](https://www.guidgen.com) जस्तो वेबसाइट प्रयोग गरेर अद्वितीय ID सिर्जना गर्न सक्नुहुन्छ।

    `BROKER` भनेको MQTT ब्रोकरको URL हो।

    `CLIENT_NAME` भनेको ब्रोकरमा यो MQTT क्लाइन्टको अद्वितीय नाम हो।

1. `main.cpp` फाइल खोल्नुहोस्, र `connectWiFi` फङ्सनको तल र `setup` फङ्सनको माथि निम्न कोड थप्नुहोस्:

    ```cpp
    WiFiClient wioClient;
    PubSubClient client(wioClient);
    ```

    यो कोडले Wio Terminal WiFi लाइब्रेरीहरू प्रयोग गरेर WiFi क्लाइन्ट सिर्जना गर्छ र यसलाई प्रयोग गरेर MQTT क्लाइन्ट बनाउँछ।

1. यस कोडको तल निम्न थप्नुहोस्:

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

    यो फङ्सनले MQTT ब्रोकरसँग जडान परीक्षण गर्छ र जडान नभएमा पुन: जडान गर्छ। यो जडान नभएसम्म लुप गर्छ र कन्फिग हेडर फाइलमा परिभाषित अद्वितीय क्लाइन्ट नाम प्रयोग गरेर जडान प्रयास गर्छ।

    यदि जडान असफल भयो भने, यो ५ सेकेन्डपछि पुन: प्रयास गर्छ।

1. `reconnectMQTTClient` फङ्सनको तल निम्न कोड थप्नुहोस्:

    ```cpp
    void createMQTTClient()
    {
        client.setServer(BROKER.c_str(), 1883);
        reconnectMQTTClient();
    }
    ```

    यो कोडले क्लाइन्टको लागि MQTT ब्रोकर सेट गर्छ, साथै सन्देश प्राप्त हुँदा कल हुने क्यालब्याक सेट गर्छ। त्यसपछि यो ब्रोकरसँग जडान प्रयास गर्छ।

1. WiFi जडान भएपछि `setup` फङ्सनमा `createMQTTClient` फङ्सनलाई कल गर्नुहोस्।

1. `loop` फङ्सनलाई निम्न कोडले पूर्ण रूपमा प्रतिस्थापन गर्नुहोस्:

    ```cpp
    void loop()
    {
        reconnectMQTTClient();
        client.loop();
    
        delay(2000);
    }
    ```

    यो कोडले MQTT ब्रोकरसँग पुन: जडान गरेर सुरु गर्छ। यी जडानहरू सजिलै टुट्न सक्छन्, त्यसैले नियमित रूपमा जाँच गर्नु र आवश्यक परेमा पुन: जडान गर्नु उचित हुन्छ। त्यसपछि यो MQTT क्लाइन्टमा `loop` मेथडलाई कल गर्छ, जसले सदस्यता लिएको विषयमा आउने कुनै पनि सन्देशहरू प्रशोधन गर्छ। यो एप एकल-थ्रेडेड हो, त्यसैले सन्देशहरू पृष्ठभूमि थ्रेडमा प्राप्त गर्न सकिँदैन, त्यसैले मुख्य थ्रेडमा नेटवर्क जडानमा पर्खिरहेका सन्देशहरू प्रशोधन गर्न समय छुट्याउन आवश्यक छ।

    अन्तमा, २ सेकेन्डको ढिलाइले प्रकाश स्तरहरू धेरै पटक पठाउनबाट रोक्छ र उपकरणको पावर खपत घटाउँछ।

1. कोडलाई आफ्नो Wio Terminal मा अपलोड गर्नुहोस्, र सिरियल मोनिटर प्रयोग गरेर उपकरण WiFi र MQTT सँग जडान भएको हेर्नुहोस्।

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

> 💁 तपाईं यो कोड [code-mqtt/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal) फोल्डरमा फेला पार्न सक्नुहुन्छ।

😀 तपाईंले आफ्नो उपकरणलाई सफलतापूर्वक MQTT ब्रोकरसँग जडान गर्नुभयो।

---

**अस्वीकरण**:  
यो दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) प्रयोग गरेर अनुवाद गरिएको छ। हामी शुद्धताको लागि प्रयास गर्छौं, तर कृपया ध्यान दिनुहोस् कि स्वचालित अनुवादमा त्रुटिहरू वा अशुद्धताहरू हुन सक्छ। यसको मूल भाषा मा रहेको मूल दस्तावेज़लाई आधिकारिक स्रोत मानिनुपर्छ। महत्वपूर्ण जानकारीको लागि, व्यावसायिक मानव अनुवाद सिफारिस गरिन्छ। यस अनुवादको प्रयोगबाट उत्पन्न हुने कुनै पनि गलतफहमी वा गलत व्याख्याको लागि हामी जिम्मेवार हुने छैनौं।