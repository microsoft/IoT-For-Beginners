<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "59263d094f20b302053888cd236880c3",
  "translation_date": "2025-08-27T11:05:50+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp.md",
  "language_code": "ne"
}
-->
# तापक्रम मापन गर्नुहोस् - Wio Terminal

यस पाठको यस भागमा, तपाईं आफ्नो Wio Terminal मा तापक्रम सेन्सर थप्नुहुनेछ र यसबाट तापक्रम मानहरू पढ्नुहुनेछ।

## हार्डवेयर

Wio Terminal लाई तापक्रम सेन्सर चाहिन्छ।

तपाईंले प्रयोग गर्ने सेन्सर [DHT11 आर्द्रता र तापक्रम सेन्सर](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html) हो, जसले दुई सेन्सरलाई एउटै प्याकेजमा संयोजन गर्दछ। यो धेरै लोकप्रिय छ, र धेरै व्यावसायिक रूपमा उपलब्ध सेन्सरहरूले तापक्रम, आर्द्रता, र कहिलेकाहीं वायुमण्डलीय दबाबलाई संयोजन गर्छन्। तापक्रम सेन्सर कम्पोनेन्ट एक नेगेटिभ तापक्रम गुणांक (NTC) थर्मिस्टर हो, जसको प्रतिरोध तापक्रम बढ्दै जाँदा घट्छ।

यो डिजिटल सेन्सर हो, त्यसैले यसमा एक अनबोर्ड ADC छ जसले तापक्रम र आर्द्रता डाटा समावेश गर्ने डिजिटल संकेत सिर्जना गर्दछ, जुन माइक्रोकन्ट्रोलरले पढ्न सक्छ।

### तापक्रम सेन्सर जडान गर्नुहोस्

Grove तापक्रम सेन्सरलाई Wio Terminal को डिजिटल पोर्टमा जडान गर्न सकिन्छ।

#### कार्य - तापक्रम सेन्सर जडान गर्नुहोस्

तापक्रम सेन्सर जडान गर्नुहोस्।

![A grove temperature sensor](../../../../../translated_images/grove-dht11.07f8eafceee170043efbb53e1d15722bd4e00fbaa9ff74290b57e9f66eb82c17.ne.png)

1. Grove केबलको एउटा छेउ आर्द्रता र तापक्रम सेन्सरको सॉकेटमा राख्नुहोस्। यो केवल एक तरिकाले मात्र जडान गर्न सकिन्छ।

1. Wio Terminal लाई तपाईंको कम्प्युटर वा अन्य पावर सप्लाईबाट डिस्कनेक्ट गरेर, Grove केबलको अर्को छेउलाई Wio Terminal को स्क्रिन हेर्दा दायाँपट्टि रहेको Grove सॉकेटमा जडान गर्नुहोस्। यो पावर बटनबाट सबैभन्दा टाढा रहेको सॉकेट हो।

![The grove temperature sensor connected to the right hand socket](../../../../../translated_images/wio-temperature-sensor.2934928f38c7f79a68d24879d2c8986c78244696f931e2e33c293f426ecdc0ad.ne.png)

## तापक्रम सेन्सर प्रोग्राम गर्नुहोस्

अब Wio Terminal लाई जडान गरिएको तापक्रम सेन्सर प्रयोग गर्न प्रोग्राम गर्न सकिन्छ।

### कार्य - तापक्रम सेन्सर प्रोग्राम गर्नुहोस्

डिभाइस प्रोग्राम गर्नुहोस्।

1. PlatformIO प्रयोग गरेर नयाँ Wio Terminal प्रोजेक्ट सिर्जना गर्नुहोस्। यस प्रोजेक्टलाई `temperature-sensor` नाम दिनुहोस्। `setup` फङ्सनमा सिरियल पोर्ट कन्फिगर गर्न कोड थप्नुहोस्।

    > ⚠️ तपाईं [प्रोजेक्ट 1, पाठ 1 मा PlatformIO प्रोजेक्ट सिर्जना गर्ने निर्देशनहरू](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project) हेर्न सक्नुहुन्छ।

1. Seeed Grove आर्द्रता र तापक्रम सेन्सर लाइब्रेरीको लागि प्रोजेक्टको `platformio.ini` फाइलमा लाइब्रेरी निर्भरता थप्नुहोस्:

    ```ini
    lib_deps =
        seeed-studio/Grove Temperature And Humidity Sensor @ 1.0.1
    ```

    > ⚠️ तपाईं [प्रोजेक्ट 1, पाठ 4 मा PlatformIO प्रोजेक्टमा लाइब्रेरीहरू थप्ने निर्देशनहरू](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md#install-the-wifi-and-mqtt-arduino-libraries) हेर्न सक्नुहुन्छ।

1. फाइलको माथि, पहिले नै रहेको `#include <Arduino.h>` को तल निम्न `#include` निर्देशहरू थप्नुहोस्:

    ```cpp
    #include <DHT.h>
    #include <SPI.h>
    ```

    यसले सेन्सरसँग अन्तरक्रिया गर्न आवश्यक फाइलहरू आयात गर्दछ। `DHT.h` हेडर फाइलले सेन्सरको लागि कोड समावेश गर्दछ, र `SPI.h` हेडर थप्दा एप्लिकेसन कम्पाइल गर्दा सेन्सरसँग कुरा गर्न आवश्यक कोड लिंक गरिन्छ।

1. `setup` फङ्सन अघि, DHT सेन्सर घोषणा गर्नुहोस्:

    ```cpp
    DHT dht(D0, DHT11);
    ```

    यसले **D**igital **H**umidity र **T**emperature सेन्सरलाई व्यवस्थापन गर्ने `DHT` क्लासको एक उदाहरण घोषणा गर्दछ। यो `D0` पोर्टमा जडान गरिएको छ, Wio Terminal को दायाँपट्टि रहेको Grove सॉकेट। दोस्रो प्यारामिटरले प्रयोग भइरहेको सेन्सर *DHT11* सेन्सर हो भनेर कोडलाई बताउँछ - तपाईंले प्रयोग गरिरहेको लाइब्रेरीले यस सेन्सरका अन्य भेरियन्टहरूलाई समर्थन गर्दछ।

1. `setup` फङ्सनमा, सिरियल कनेक्शन सेटअप गर्न कोड थप्नुहोस्:

    ```cpp
    void setup()
    {
        Serial.begin(9600);
    
        while (!Serial)
            ; // Wait for Serial to be ready
    
        delay(1000);
    }
    ```

1. `setup` फङ्सनको अन्त्यमा, अन्तिम `delay` पछि, DHT सेन्सर सुरु गर्न कल थप्नुहोस्:

    ```cpp
    dht.begin();
    ```

1. `loop` फङ्सनमा, सेन्सरलाई कल गर्न र सिरियल पोर्टमा तापक्रम प्रिन्ट गर्न कोड थप्नुहोस्:

    ```cpp
    void loop()
    {
        float temp_hum_val[2] = {0};
        dht.readTempAndHumidity(temp_hum_val);
        Serial.print("Temperature: ");
        Serial.print(temp_hum_val[1]);
        Serial.println ("°C");
    
        delay(10000);
    }
    ```

    यस कोडले 2 फ्लोट्सको खाली एरे घोषणा गर्दछ, र यसलाई `DHT` उदाहरणमा `readTempAndHumidity` कलमा पास गर्दछ। यस कलले एरेलाई 2 मानहरूद्वारा भरिन्छ - आर्द्रता एरेको 0th आइटममा जान्छ (C++ एरेहरू 0-आधारित हुन्छन्, त्यसैले 0th आइटम एरेको 'पहिलो' आइटम हो), र तापक्रम 1st आइटममा जान्छ।

    तापक्रम एरेको 1st आइटमबाट पढिन्छ, र सिरियल पोर्टमा प्रिन्ट गरिन्छ।

    > 🇺🇸 तापक्रम सेल्सियसमा पढिन्छ। अमेरिकाका लागि, यसलाई फारेनहाइटमा रूपान्तरण गर्न, पढिएको सेल्सियस मानलाई 5 ले भाग गर्नुहोस्, त्यसपछि 9 ले गुणा गर्नुहोस्, त्यसपछि 32 थप्नुहोस्। उदाहरणका लागि, 20°C को तापक्रम पढाइ ((20/5)*9) + 32 = 68°F हुन्छ।

1. कोडलाई Wio Terminal मा निर्माण र अपलोड गर्नुहोस्।

    > ⚠️ तपाईं [प्रोजेक्ट 1, पाठ 1 मा PlatformIO प्रोजेक्ट सिर्जना गर्ने निर्देशनहरू](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app) हेर्न सक्नुहुन्छ।

1. अपलोड गरेपछि, सिरियल मोनिटर प्रयोग गरेर तापक्रम अनुगमन गर्न सक्नुहुन्छ:

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Temperature: 25.00°C
    Temperature: 25.00°C
    Temperature: 25.00°C
    Temperature: 24.00°C
    ```

> 💁 तपाईं यो कोड [code-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/wio-terminal) फोल्डरमा पाउन सक्नुहुन्छ।

😀 तपाईंको तापक्रम सेन्सर प्रोग्राम सफल भयो!

---

**अस्वीकरण**:  
यो दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) प्रयोग गरी अनुवाद गरिएको हो। हामी यथासम्भव सटीकता सुनिश्चित गर्न प्रयास गर्छौं, तर कृपया ध्यान दिनुहोस् कि स्वचालित अनुवादहरूमा त्रुटि वा अशुद्धता हुन सक्छ। यसको मूल भाषामा रहेको मूल दस्तावेज़लाई आधिकारिक स्रोत मानिनुपर्छ। महत्त्वपूर्ण जानकारीका लागि, व्यावसायिक मानव अनुवाद सिफारिस गरिन्छ। यस अनुवादको प्रयोगबाट उत्पन्न हुने कुनै पनि गलतफहमी वा गलत व्याख्याका लागि हामी जिम्मेवार हुने छैनौं।  