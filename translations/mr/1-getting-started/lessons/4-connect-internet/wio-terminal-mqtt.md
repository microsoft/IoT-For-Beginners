<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d6faf0e8d3c2d6d20c0aef2a305dab18",
  "translation_date": "2025-08-27T12:33:04+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md",
  "language_code": "mr"
}
-->
# इंटरनेटद्वारे तुमच्या नाईटलाइटचे नियंत्रण करा - Wio Terminal

IoT डिव्हाइसला *test.mosquitto.org* शी MQTT च्या माध्यमातून संवाद साधण्यासाठी कोड करणे आवश्यक आहे, ज्यामुळे लाईट सेन्सर वाचनासह टेलिमेट्री मूल्ये पाठवता येतील आणि LED नियंत्रित करण्यासाठी कमांड्स प्राप्त करता येतील.

या धड्याच्या या भागात, तुम्ही तुमच्या Wio Terminal ला MQTT ब्रोकरसह कनेक्ट कराल.

## WiFi आणि MQTT Arduino लायब्ररी इंस्टॉल करा

MQTT ब्रोकरसह संवाद साधण्यासाठी, Wio Terminal मधील WiFi चिप वापरण्यासाठी आणि MQTT शी संवाद साधण्यासाठी काही Arduino लायब्ररी इंस्टॉल करणे आवश्यक आहे. Arduino डिव्हाइससाठी विकसित करताना, तुम्ही ओपन-सोर्स कोड असलेल्या आणि विविध क्षमतांची अंमलबजावणी करणाऱ्या लायब्ररींचा मोठ्या प्रमाणावर वापर करू शकता. Seeed ने Wio Terminal साठी लायब्ररी प्रकाशित केल्या आहेत, ज्यामुळे ते WiFi वर संवाद साधू शकते. इतर विकसकांनी MQTT ब्रोकर्सशी संवाद साधण्यासाठी लायब्ररी प्रकाशित केल्या आहेत, आणि तुम्ही तुमच्या डिव्हाइससह या लायब्ररींचा वापर कराल.

या लायब्ररी सोर्स कोड स्वरूपात दिल्या जातात, ज्या PlatformIO मध्ये स्वयंचलितपणे आयात केल्या जाऊ शकतात आणि तुमच्या डिव्हाइससाठी संकलित केल्या जाऊ शकतात. यामुळे, Arduino लायब्ररी कोणत्याही डिव्हाइसवर कार्य करतील, जोपर्यंत त्या लायब्ररीला आवश्यक असलेले विशिष्ट हार्डवेअर त्या डिव्हाइसवर उपलब्ध आहे. काही लायब्ररी, जसे की Seeed WiFi लायब्ररी, विशिष्ट हार्डवेअरसाठीच असतात.

लायब्ररी जागतिक स्तरावर इंस्टॉल केल्या जाऊ शकतात आणि आवश्यक असल्यास संकलित केल्या जाऊ शकतात, किंवा विशिष्ट प्रकल्पात इंस्टॉल केल्या जाऊ शकतात. या असाइनमेंटसाठी, लायब्ररी प्रकल्पात इंस्टॉल केल्या जातील.

✅ लायब्ररी व्यवस्थापनाबद्दल अधिक जाणून घेण्यासाठी आणि लायब्ररी कशा शोधायच्या व इंस्टॉल करायच्या याबद्दल [PlatformIO लायब्ररी दस्तऐवज](https://docs.platformio.org/en/latest/librarymanager/index.html) वाचा.

### कार्य - WiFi आणि MQTT Arduino लायब्ररी इंस्टॉल करा

Arduino लायब्ररी इंस्टॉल करा.

1. VS Code मध्ये नाईटलाइट प्रकल्प उघडा.

1. `platformio.ini` फाइलच्या शेवटी खालील कोड जोडा:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
        seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
        seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    ```

    हे Seeed WiFi लायब्ररी आयात करते. `@ <number>` सिंटॅक्स लायब्ररीच्या विशिष्ट आवृत्ती क्रमांकाचा संदर्भ देते.

    > 💁 तुम्ही `@ <number>` काढून टाकू शकता जेणेकरून लायब्ररींच्या नेहमीच्या नवीनतम आवृत्त्या वापरल्या जातील, परंतु नंतरच्या आवृत्त्या खालील कोडसह कार्य करतील याची हमी नाही. येथे दिलेला कोड या लायब्ररींच्या या आवृत्तीसह चाचणी केली आहे.

    लायब्ररी जोडण्यासाठी तुम्हाला एवढेच करावे लागेल. पुढच्या वेळी PlatformIO प्रकल्प तयार करेल, तेव्हा या लायब्ररींसाठी सोर्स कोड डाउनलोड होईल आणि तुमच्या प्रकल्पात संकलित होईल.

1. `lib_deps` मध्ये खालील कोड जोडा:

    ```ini
    knolleary/PubSubClient @ 2.8
    ```

    हे [PubSubClient](https://github.com/knolleary/pubsubclient), एक Arduino MQTT क्लायंट आयात करते.

## WiFi शी कनेक्ट करा

आता Wio Terminal ला WiFi शी कनेक्ट करता येईल.

### कार्य - WiFi शी कनेक्ट करा

Wio Terminal ला WiFi शी कनेक्ट करा.

1. `src` फोल्डरमध्ये `config.h` नावाची नवीन फाइल तयार करा. तुम्ही हे `src` फोल्डर निवडून किंवा त्यातील `main.cpp` फाइल निवडून, आणि एक्सप्लोररमधील **नवीन फाइल** बटण निवडून करू शकता. हे बटण फक्त तेव्हा दिसते जेव्हा तुमचा कर्सर एक्सप्लोररवर असतो.

    ![नवीन फाइल बटण](../../../../../translated_images/mr/vscode-new-file-button.182702340fe6723c.png)

1. तुमच्या WiFi क्रेडेन्शियल्ससाठी कॉन्स्टंट्स परिभाषित करण्यासाठी या फाइलमध्ये खालील कोड जोडा:

    ```cpp
    #pragma once

    #include <string>
    
    using namespace std;
    
    // WiFi credentials
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    ```

    `<SSID>` च्या जागी तुमच्या WiFi चे SSID टाका. `<PASSWORD>` च्या जागी तुमचा WiFi पासवर्ड टाका.

1. `main.cpp` फाइल उघडा.

1. फाइलच्या शीर्षस्थानी खालील `#include` निर्देश जोडा:

    ```cpp
    #include <PubSubClient.h>
    #include <rpcWiFi.h>
    #include <SPI.h>
    
    #include "config.h"
    ```

    हे तुम्ही आधी जोडलेल्या लायब्ररींसाठी हेडर फाइल्स समाविष्ट करते, तसेच config हेडर फाइल देखील. या हेडर फाइल्स आवश्यक आहेत जेणेकरून PlatformIO लायब्ररीमधील कोड आणेल. हेडर फाइल्स स्पष्टपणे समाविष्ट केल्या नाहीत तर काही कोड संकलित होणार नाही आणि तुम्हाला कंपाइलर त्रुटी मिळतील.

1. `setup` फंक्शनच्या वर खालील कोड जोडा:

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

    हा कोड डिव्हाइस WiFi शी कनेक्ट होईपर्यंत लूप करतो आणि config हेडर फाइलमधील SSID आणि पासवर्ड वापरून कनेक्ट करण्याचा प्रयत्न करतो.

1. पिन्स कॉन्फिगर केल्यानंतर `setup` फंक्शनच्या तळाशी या फंक्शनला कॉल जोडा.

    ```cpp
    connectWiFi();
    ```

1. WiFi कनेक्शन कार्यरत आहे का ते तपासण्यासाठी हा कोड तुमच्या डिव्हाइसवर अपलोड करा. तुम्हाला सीरियल मॉनिटरमध्ये हे दिसेल.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    ```

## MQTT शी कनेक्ट करा

Wio Terminal WiFi शी कनेक्ट झाल्यानंतर, तो MQTT ब्रोकरसह कनेक्ट होऊ शकतो.

### कार्य - MQTT शी कनेक्ट करा

MQTT ब्रोकरसह कनेक्ट करा.

1. MQTT ब्रोकरसाठी कनेक्शन तपशील परिभाषित करण्यासाठी `config.h` फाइलच्या तळाशी खालील कोड जोडा:

    ```cpp
    // MQTT settings
    const string ID = "<ID>";
    
    const string BROKER = "test.mosquitto.org";
    const string CLIENT_NAME = ID + "nightlight_client";
    ```

    `<ID>` च्या जागी एक अद्वितीय ID टाका, जे या डिव्हाइस क्लायंटचे नाव म्हणून वापरले जाईल, आणि नंतर या डिव्हाइसने प्रकाशित आणि सदस्यता घेतलेल्या विषयांसाठी वापरले जाईल. *test.mosquitto.org* ब्रोकर सार्वजनिक आहे आणि अनेक लोक, यासह इतर विद्यार्थी, या असाइनमेंटद्वारे वापरतात. एक अद्वितीय MQTT क्लायंट नाव आणि विषयांची नावे सुनिश्चित करतात की तुमचा कोड इतर कोणाच्याही कोडशी टकराव होणार नाही. तुम्हाला हे ID नंतर या असाइनमेंटमध्ये सर्व्हर कोड तयार करताना देखील आवश्यक असेल.

    > 💁 तुम्ही [GUIDGen](https://www.guidgen.com) सारख्या वेबसाइटचा वापर करून एक अद्वितीय ID तयार करू शकता.

    `BROKER` हा MQTT ब्रोकरचा URL आहे.

    `CLIENT_NAME` हा ब्रोकरवरील या MQTT क्लायंटसाठी एक अद्वितीय नाव आहे.

1. `main.cpp` फाइल उघडा, आणि `connectWiFi` फंक्शनच्या खाली आणि `setup` फंक्शनच्या वर खालील कोड जोडा:

    ```cpp
    WiFiClient wioClient;
    PubSubClient client(wioClient);
    ```

    हा कोड Wio Terminal WiFi लायब्ररी वापरून WiFi क्लायंट तयार करतो आणि त्याचा वापर करून MQTT क्लायंट तयार करतो.

1. या कोडच्या खाली खालील कोड जोडा:

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

    हा फंक्शन MQTT ब्रोकरसह कनेक्शन तपासतो आणि कनेक्ट नसेल तर पुन्हा कनेक्ट करतो. तो लूप करतो आणि कनेक्ट होईपर्यंत प्रयत्न करतो, आणि config हेडर फाइलमध्ये परिभाषित केलेल्या अद्वितीय क्लायंट नावाचा वापर करतो.

    जर कनेक्शन अयशस्वी झाले, तर 5 सेकंदांनंतर पुन्हा प्रयत्न करतो.

1. `reconnectMQTTClient` फंक्शनच्या खाली खालील कोड जोडा:

    ```cpp
    void createMQTTClient()
    {
        client.setServer(BROKER.c_str(), 1883);
        reconnectMQTTClient();
    }
    ```

    हा कोड क्लायंटसाठी MQTT ब्रोकर सेट करतो, तसेच संदेश प्राप्त झाल्यावर कॉलबॅक सेट करतो. नंतर तो ब्रोकरसह कनेक्ट करण्याचा प्रयत्न करतो.

1. WiFi कनेक्ट झाल्यानंतर `setup` फंक्शनमध्ये `createMQTTClient` फंक्शनला कॉल करा.

1. `loop` फंक्शन पूर्णपणे खालील कोडने बदला:

    ```cpp
    void loop()
    {
        reconnectMQTTClient();
        client.loop();
    
        delay(2000);
    }
    ```

    हा कोड MQTT ब्रोकरसह पुन्हा कनेक्ट करतो. ही कनेक्शन्स सहज तुटू शकतात, त्यामुळे नियमितपणे तपासणे आणि आवश्यक असल्यास पुन्हा कनेक्ट करणे फायदेशीर ठरते. नंतर तो MQTT क्लायंटवरील `loop` पद्धतीला कॉल करतो, जे सदस्यता घेतलेल्या विषयावर येणारे कोणतेही संदेश प्रक्रिया करते. हे अॅप सिंगल-थ्रेडेड आहे, त्यामुळे संदेश बॅकग्राउंड थ्रेडवर प्राप्त होऊ शकत नाहीत, म्हणून मुख्य थ्रेडवर नेटवर्क कनेक्शनवरील प्रतीक्षेत असलेल्या संदेशांची प्रक्रिया करण्यासाठी वेळ दिला पाहिजे.

    शेवटी, 2 सेकंदांचा विलंब सुनिश्चित करतो की प्रकाश पातळी खूप वारंवार पाठवली जात नाही आणि डिव्हाइसचा ऊर्जा वापर कमी होतो.

1. कोड तुमच्या Wio Terminal वर अपलोड करा, आणि डिव्हाइस WiFi आणि MQTT शी कनेक्ट होत असल्याचे पाहण्यासाठी सीरियल मॉनिटर वापरा.

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

> 💁 तुम्हाला हा कोड [code-mqtt/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal) फोल्डरमध्ये सापडेल.

😀 तुम्ही तुमचे डिव्हाइस यशस्वीरित्या MQTT ब्रोकरसह कनेक्ट केले आहे.

---

**अस्वीकरण**:  
हा दस्तऐवज AI भाषांतर सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) वापरून भाषांतरित करण्यात आला आहे. आम्ही अचूकतेसाठी प्रयत्नशील असलो तरी, कृपया लक्षात ठेवा की स्वयंचलित भाषांतरांमध्ये त्रुटी किंवा अचूकतेचा अभाव असू शकतो. मूळ भाषेतील दस्तऐवज हा अधिकृत स्रोत मानला जावा. महत्त्वाच्या माहितीसाठी व्यावसायिक मानवी भाषांतराची शिफारस केली जाते. या भाषांतराचा वापर करून उद्भवलेल्या कोणत्याही गैरसमज किंवा चुकीच्या अर्थासाठी आम्ही जबाबदार राहणार नाही.