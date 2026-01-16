<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d6faf0e8d3c2d6d20c0aef2a305dab18",
  "translation_date": "2025-08-25T17:18:12+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md",
  "language_code": "hi"
}
-->
# इंटरनेट के जरिए अपनी नाइटलाइट को नियंत्रित करें - Wio Terminal

IoT डिवाइस को *test.mosquitto.org* के साथ MQTT का उपयोग करके टेलीमेट्री डेटा भेजने और लाइट सेंसर रीडिंग के साथ LED को नियंत्रित करने के लिए कमांड प्राप्त करने के लिए कोड किया जाना चाहिए।

इस पाठ के इस भाग में, आप अपने Wio Terminal को एक MQTT ब्रोकर्स से कनेक्ट करेंगे।

## WiFi और MQTT Arduino लाइब्रेरी इंस्टॉल करें

MQTT ब्रोकर्स के साथ संवाद करने के लिए, आपको कुछ Arduino लाइब्रेरी इंस्टॉल करनी होंगी ताकि Wio Terminal के WiFi चिप का उपयोग किया जा सके और MQTT के साथ संवाद किया जा सके। Arduino डिवाइसों के लिए विकास करते समय, आप कई प्रकार की लाइब्रेरी का उपयोग कर सकते हैं, जो ओपन-सोर्स कोड प्रदान करती हैं और कई क्षमताओं को लागू करती हैं। Seeed Wio Terminal के लिए लाइब्रेरी प्रकाशित करता है, जो इसे WiFi के जरिए संवाद करने की अनुमति देती हैं। अन्य डेवलपर्स ने MQTT ब्रोकर्स के साथ संवाद करने के लिए लाइब्रेरी प्रकाशित की हैं, और आप अपने डिवाइस के साथ इनका उपयोग करेंगे।

ये लाइब्रेरी सोर्स कोड के रूप में प्रदान की जाती हैं, जिन्हें PlatformIO में स्वचालित रूप से आयात किया जा सकता है और आपके डिवाइस के लिए संकलित किया जा सकता है। इस तरह Arduino लाइब्रेरी किसी भी डिवाइस पर काम करेंगी जो Arduino फ्रेमवर्क का समर्थन करती है, बशर्ते कि डिवाइस में उस लाइब्रेरी द्वारा आवश्यक कोई विशिष्ट हार्डवेयर हो। कुछ लाइब्रेरी, जैसे Seeed WiFi लाइब्रेरी, कुछ हार्डवेयर के लिए विशिष्ट होती हैं।

लाइब्रेरी को वैश्विक रूप से इंस्टॉल किया जा सकता है और आवश्यकता पड़ने पर संकलित किया जा सकता है, या किसी विशिष्ट प्रोजेक्ट में। इस असाइनमेंट के लिए, लाइब्रेरी प्रोजेक्ट में इंस्टॉल की जाएंगी।

✅ आप लाइब्रेरी प्रबंधन और लाइब्रेरी खोजने और इंस्टॉल करने के बारे में अधिक जानकारी [PlatformIO लाइब्रेरी डाक्यूमेंटेशन](https://docs.platformio.org/en/latest/librarymanager/index.html) में प्राप्त कर सकते हैं।

### कार्य - WiFi और MQTT Arduino लाइब्रेरी इंस्टॉल करें

Arduino लाइब्रेरी इंस्टॉल करें।

1. VS Code में नाइटलाइट प्रोजेक्ट खोलें।

1. `platformio.ini` फाइल के अंत में निम्नलिखित जोड़ें:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
        seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
        seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    ```

    यह Seeed WiFi लाइब्रेरी आयात करता है। `@ <number>` सिंटैक्स लाइब्रेरी के एक विशिष्ट संस्करण संख्या को संदर्भित करता है।

    > 💁 आप लाइब्रेरी के नवीनतम संस्करण का उपयोग करने के लिए `@ <number>` हटा सकते हैं, लेकिन यह गारंटी नहीं है कि बाद के संस्करण नीचे दिए गए कोड के साथ काम करेंगे। यहां दिया गया कोड इस संस्करण के साथ परीक्षण किया गया है।

    लाइब्रेरी जोड़ने के लिए आपको बस इतना ही करना है। अगली बार जब PlatformIO प्रोजेक्ट को बनाएगा, तो यह इन लाइब्रेरी के लिए सोर्स कोड डाउनलोड करेगा और इसे आपके प्रोजेक्ट में संकलित करेगा।

1. `lib_deps` में निम्नलिखित जोड़ें:

    ```ini
    knolleary/PubSubClient @ 2.8
    ```

    यह [PubSubClient](https://github.com/knolleary/pubsubclient), एक Arduino MQTT क्लाइंट आयात करता है।

## WiFi से कनेक्ट करें

अब Wio Terminal को WiFi से कनेक्ट किया जा सकता है।

### कार्य - WiFi से कनेक्ट करें

Wio Terminal को WiFi से कनेक्ट करें।

1. `src` फोल्डर में `config.h` नामक एक नई फाइल बनाएं। आप ऐसा `src` फोल्डर या उसके अंदर `main.cpp` फाइल का चयन करके और एक्सप्लोरर से **New file** बटन का चयन करके कर सकते हैं। यह बटन केवल तब दिखाई देता है जब आपका कर्सर एक्सप्लोरर पर होता है।

    ![नया फाइल बटन](../../../../../translated_images/hi/vscode-new-file-button.182702340fe6723c.png)

1. इस फाइल में अपने WiFi क्रेडेंशियल्स के लिए कॉन्स्टेंट्स को परिभाषित करने के लिए निम्नलिखित कोड जोड़ें:

    ```cpp
    #pragma once

    #include <string>
    
    using namespace std;
    
    // WiFi credentials
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    ```

    `<SSID>` को अपने WiFi के SSID से बदलें। `<PASSWORD>` को अपने WiFi पासवर्ड से बदलें।

1. `main.cpp` फाइल खोलें।

1. फाइल के शीर्ष पर निम्नलिखित `#include` निर्देश जोड़ें:

    ```cpp
    #include <PubSubClient.h>
    #include <rpcWiFi.h>
    #include <SPI.h>
    
    #include "config.h"
    ```

    यह उन लाइब्रेरी के हेडर फाइल्स को शामिल करता है जिन्हें आपने पहले जोड़ा था, साथ ही कॉन्फ़िग हेडर फाइल को भी। ये हेडर फाइल्स PlatformIO को लाइब्रेरी से कोड लाने के लिए आवश्यक हैं। इन हेडर फाइल्स को स्पष्ट रूप से शामिल किए बिना, कुछ कोड संकलित नहीं होगा और आपको कंपाइलर त्रुटियां मिलेंगी।

1. `setup` फंक्शन के ऊपर निम्नलिखित कोड जोड़ें:

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

    यह कोड तब तक लूप करता है जब तक डिवाइस WiFi से कनेक्ट नहीं हो जाता, और SSID और पासवर्ड का उपयोग करके कनेक्ट करने की कोशिश करता है।

1. पिन्स को कॉन्फ़िगर करने के बाद `setup` फंक्शन के नीचे इस फंक्शन को कॉल करें:

    ```cpp
    connectWiFi();
    ```

1. इस कोड को अपने डिवाइस पर अपलोड करें और जांचें कि WiFi कनेक्शन काम कर रहा है। आपको सीरियल मॉनिटर में यह देखना चाहिए:

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    ```

## MQTT से कनेक्ट करें

WiFi से कनेक्ट होने के बाद, Wio Terminal MQTT ब्रोकर्स से कनेक्ट हो सकता है।

### कार्य - MQTT से कनेक्ट करें

MQTT ब्रोकर्स से कनेक्ट करें।

1. MQTT ब्रोकर्स के कनेक्शन विवरण को परिभाषित करने के लिए `config.h` फाइल के अंत में निम्नलिखित कोड जोड़ें:

    ```cpp
    // MQTT settings
    const string ID = "<ID>";
    
    const string BROKER = "test.mosquitto.org";
    const string CLIENT_NAME = ID + "nightlight_client";
    ```

    `<ID>` को एक यूनिक ID से बदलें, जो इस डिवाइस क्लाइंट का नाम होगा और बाद में उन टॉपिक्स के लिए उपयोग किया जाएगा जिन्हें यह डिवाइस प्रकाशित और सब्सक्राइब करेगा। *test.mosquitto.org* ब्रोकर्स सार्वजनिक है और कई लोग इसका उपयोग करते हैं, जिनमें इस असाइनमेंट पर काम कर रहे अन्य छात्र भी शामिल हैं। एक यूनिक MQTT क्लाइंट नाम और टॉपिक नाम सुनिश्चित करता है कि आपका कोड किसी और के कोड से टकराएगा नहीं। आपको इस ID की आवश्यकता बाद में सर्वर कोड बनाते समय भी होगी।

    > 💁 आप [GUIDGen](https://www.guidgen.com) जैसी वेबसाइट का उपयोग करके एक यूनिक ID जनरेट कर सकते हैं।

    `BROKER` MQTT ब्रोकर्स का URL है।

    `CLIENT_NAME` इस MQTT क्लाइंट का ब्रोकर्स पर एक यूनिक नाम है।

1. `main.cpp` फाइल खोलें, और `connectWiFi` फंक्शन के नीचे और `setup` फंक्शन के ऊपर निम्नलिखित कोड जोड़ें:

    ```cpp
    WiFiClient wioClient;
    PubSubClient client(wioClient);
    ```

    यह कोड Wio Terminal WiFi लाइब्रेरी का उपयोग करके एक WiFi क्लाइंट बनाता है और इसका उपयोग एक MQTT क्लाइंट बनाने के लिए करता है।

1. इस कोड के नीचे निम्नलिखित जोड़ें:

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

    यह फंक्शन MQTT ब्रोकर्स से कनेक्शन का परीक्षण करता है और यदि कनेक्टेड नहीं है तो फिर से कनेक्ट करता है। यह तब तक लूप करता है जब तक यह कनेक्ट नहीं हो जाता और कॉन्फ़िग हेडर फाइल में परिभाषित यूनिक क्लाइंट नाम का उपयोग करके कनेक्ट करने का प्रयास करता है।

    यदि कनेक्शन विफल हो जाता है, तो यह 5 सेकंड बाद फिर से प्रयास करता है।

1. `reconnectMQTTClient` फंक्शन के नीचे निम्नलिखित कोड जोड़ें:

    ```cpp
    void createMQTTClient()
    {
        client.setServer(BROKER.c_str(), 1883);
        reconnectMQTTClient();
    }
    ```

    यह कोड क्लाइंट के लिए MQTT ब्रोकर्स सेट करता है, साथ ही एक कॉलबैक सेट करता है जब कोई संदेश प्राप्त होता है। फिर यह ब्रोकर्स से कनेक्ट करने का प्रयास करता है।

1. WiFi कनेक्ट होने के बाद `setup` फंक्शन में `createMQTTClient` फंक्शन को कॉल करें।

1. पूरे `loop` फंक्शन को निम्नलिखित से बदलें:

    ```cpp
    void loop()
    {
        reconnectMQTTClient();
        client.loop();
    
        delay(2000);
    }
    ```

    यह कोड MQTT ब्रोकर्स से फिर से कनेक्ट करता है। ये कनेक्शन आसानी से टूट सकते हैं, इसलिए नियमित रूप से जांचना और आवश्यकता पड़ने पर फिर से कनेक्ट करना उचित है। फिर यह MQTT क्लाइंट पर `loop` मेथड को कॉल करता है ताकि किसी भी संदेश को प्रोसेस किया जा सके जो सब्सक्राइब किए गए टॉपिक पर आ रहे हैं। यह ऐप सिंगल-थ्रेडेड है, इसलिए संदेश बैकग्राउंड थ्रेड पर प्राप्त नहीं किए जा सकते, इसलिए मुख्य थ्रेड पर नेटवर्क कनेक्शन पर प्रतीक्षा कर रहे किसी भी संदेश को प्रोसेस करने के लिए समय आवंटित करना आवश्यक है।

    अंत में, 2 सेकंड की देरी सुनिश्चित करती है कि लाइट लेवल बहुत बार नहीं भेजे जाते और डिवाइस की पावर खपत कम हो जाती है।

1. कोड को अपने Wio Terminal पर अपलोड करें, और डिवाइस को WiFi और MQTT से कनेक्ट होते हुए देखने के लिए सीरियल मॉनिटर का उपयोग करें।

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

> 💁 आप इस कोड को [code-mqtt/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal) फोल्डर में पा सकते हैं।

😀 आपने सफलतापूर्वक अपने डिवाइस को एक MQTT ब्रोकर्स से कनेक्ट कर लिया है।

**अस्वीकरण**:  
यह दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) का उपयोग करके अनुवादित किया गया है। जबकि हम सटीकता सुनिश्चित करने का प्रयास करते हैं, कृपया ध्यान दें कि स्वचालित अनुवाद में त्रुटियां या अशुद्धियां हो सकती हैं। मूल भाषा में उपलब्ध मूल दस्तावेज़ को आधिकारिक स्रोत माना जाना चाहिए। महत्वपूर्ण जानकारी के लिए, पेशेवर मानव अनुवाद की सिफारिश की जाती है। इस अनुवाद के उपयोग से उत्पन्न किसी भी गलतफहमी या गलत व्याख्या के लिए हम जिम्मेदार नहीं हैं।