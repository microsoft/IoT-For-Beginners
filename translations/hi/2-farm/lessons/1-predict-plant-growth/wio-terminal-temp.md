<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "59263d094f20b302053888cd236880c3",
  "translation_date": "2025-08-25T16:46:17+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp.md",
  "language_code": "hi"
}
-->
# तापमान मापें - Wio Terminal

इस पाठ के इस भाग में, आप अपने Wio Terminal में एक तापमान सेंसर जोड़ेंगे और उससे तापमान के मान पढ़ेंगे।

## हार्डवेयर

Wio Terminal को एक तापमान सेंसर की आवश्यकता है।

आप जो सेंसर उपयोग करेंगे वह [DHT11 ह्यूमिडिटी और तापमान सेंसर](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html) है, जो एक पैकेज में 2 सेंसर को जोड़ता है। यह काफी लोकप्रिय है, और कई व्यावसायिक रूप से उपलब्ध सेंसर तापमान, आर्द्रता और कभी-कभी वायुमंडलीय दबाव को जोड़ते हैं। तापमान सेंसर घटक एक नेगेटिव टेम्परेचर कोएफिशिएंट (NTC) थर्मिस्टर है, एक ऐसा थर्मिस्टर जिसमें तापमान बढ़ने पर प्रतिरोध घटता है।

यह एक डिजिटल सेंसर है, इसलिए इसमें एक ऑनबोर्ड ADC है जो एक डिजिटल सिग्नल बनाता है जिसमें तापमान और आर्द्रता डेटा होता है जिसे माइक्रोकंट्रोलर पढ़ सकता है।

### तापमान सेंसर को कनेक्ट करें

Grove तापमान सेंसर को Wio Terminal के डिजिटल पोर्ट से जोड़ा जा सकता है।

#### कार्य - तापमान सेंसर को कनेक्ट करें

तापमान सेंसर को कनेक्ट करें।

![एक Grove तापमान सेंसर](../../../../../translated_images/grove-dht11.07f8eafceee170043efbb53e1d15722bd4e00fbaa9ff74290b57e9f66eb82c17.hi.png)

1. Grove केबल के एक सिरे को ह्यूमिडिटी और तापमान सेंसर के सॉकेट में डालें। यह केवल एक ही दिशा में जाएगा।

1. Wio Terminal को अपने कंप्यूटर या अन्य पावर सप्लाई से डिस्कनेक्ट करें, और Grove केबल के दूसरे सिरे को Wio Terminal के स्क्रीन की ओर देखते हुए दाईं ओर के Grove सॉकेट में कनेक्ट करें। यह सॉकेट पावर बटन से सबसे दूर है।

![Grove तापमान सेंसर को दाईं ओर के सॉकेट से जोड़ा गया है](../../../../../translated_images/wio-temperature-sensor.2934928f38c7f79a68d24879d2c8986c78244696f931e2e33c293f426ecdc0ad.hi.png)

## तापमान सेंसर को प्रोग्राम करें

अब Wio Terminal को जोड़े गए तापमान सेंसर का उपयोग करने के लिए प्रोग्राम किया जा सकता है।

### कार्य - तापमान सेंसर को प्रोग्राम करें

डिवाइस को प्रोग्राम करें।

1. PlatformIO का उपयोग करके एक नया Wio Terminal प्रोजेक्ट बनाएं। इस प्रोजेक्ट का नाम `temperature-sensor` रखें। `setup` फंक्शन में सीरियल पोर्ट को कॉन्फ़िगर करने के लिए कोड जोड़ें।

    > ⚠️ यदि आवश्यक हो, तो [प्रोजेक्ट 1, पाठ 1 में PlatformIO प्रोजेक्ट बनाने के निर्देश देखें](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project)।

1. प्रोजेक्ट के `platformio.ini` फाइल में Seeed Grove Humidity और Temperature सेंसर लाइब्रेरी के लिए एक लाइब्रेरी डिपेंडेंसी जोड़ें:

    ```ini
    lib_deps =
        seeed-studio/Grove Temperature And Humidity Sensor @ 1.0.1
    ```

    > ⚠️ यदि आवश्यक हो, तो [प्रोजेक्ट 1, पाठ 4 में PlatformIO प्रोजेक्ट में लाइब्रेरी जोड़ने के निर्देश देखें](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md#install-the-wifi-and-mqtt-arduino-libraries)।

1. फाइल के शीर्ष पर, मौजूदा `#include <Arduino.h>` के नीचे निम्नलिखित `#include` निर्देश जोड़ें:

    ```cpp
    #include <DHT.h>
    #include <SPI.h>
    ```

    यह सेंसर के साथ इंटरैक्ट करने के लिए आवश्यक फाइलें आयात करता है। `DHT.h` हेडर फाइल सेंसर के लिए कोड को शामिल करती है, और `SPI.h` हेडर जोड़ने से यह सुनिश्चित होता है कि सेंसर से बात करने के लिए आवश्यक कोड ऐप को संकलित करते समय लिंक हो।

1. `setup` फंक्शन से पहले, DHT सेंसर को डिक्लेयर करें:

    ```cpp
    DHT dht(D0, DHT11);
    ```

    यह `DHT` क्लास का एक इंस्टेंस डिक्लेयर करता है जो **D**igital **H**umidity और **T**emperature सेंसर को मैनेज करता है। यह `D0` पोर्ट से जुड़ा है, जो Wio Terminal पर दाईं ओर का Grove सॉकेट है। दूसरा पैरामीटर कोड को बताता है कि उपयोग किया जा रहा सेंसर *DHT11* सेंसर है - आप जो लाइब्रेरी उपयोग कर रहे हैं वह इस सेंसर के अन्य वेरिएंट को भी सपोर्ट करती है।

1. `setup` फंक्शन में, सीरियल कनेक्शन सेट करने के लिए कोड जोड़ें:

    ```cpp
    void setup()
    {
        Serial.begin(9600);
    
        while (!Serial)
            ; // Wait for Serial to be ready
    
        delay(1000);
    }
    ```

1. `setup` फंक्शन के अंत में, अंतिम `delay` के बाद, DHT सेंसर को शुरू करने के लिए एक कॉल जोड़ें:

    ```cpp
    dht.begin();
    ```

1. `loop` फंक्शन में, सेंसर को कॉल करने और सीरियल पोर्ट पर तापमान प्रिंट करने के लिए कोड जोड़ें:

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

    यह कोड 2 फ्लोट्स का एक खाली ऐरे डिक्लेयर करता है, और इसे `DHT` इंस्टेंस पर `readTempAndHumidity` कॉल में पास करता है। यह कॉल ऐरे को 2 मानों से भरता है - आर्द्रता ऐरे के 0वें आइटम में जाती है (याद रखें कि C++ में ऐरे 0-आधारित होते हैं, इसलिए 0वां आइटम ऐरे का 'पहला' आइटम होता है), और तापमान 1वें आइटम में जाता है।

    तापमान को ऐरे के 1वें आइटम से पढ़ा जाता है और सीरियल पोर्ट पर प्रिंट किया जाता है।

    > 🇺🇸 तापमान को सेल्सियस में पढ़ा जाता है। अमेरिकियों के लिए, इसे फ़ारेनहाइट में बदलने के लिए, पढ़े गए सेल्सियस मान को 5 से विभाजित करें, फिर 9 से गुणा करें, फिर 32 जोड़ें। उदाहरण के लिए, 20°C का तापमान ((20/5)*9) + 32 = 68°F बन जाता है।

1. कोड को Wio Terminal पर बिल्ड और अपलोड करें।

    > ⚠️ यदि आवश्यक हो, तो [प्रोजेक्ट 1, पाठ 1 में PlatformIO प्रोजेक्ट बनाने के निर्देश देखें](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app)।

1. अपलोड हो जाने के बाद, आप सीरियल मॉनिटर का उपयोग करके तापमान की निगरानी कर सकते हैं:

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

> 💁 आप इस कोड को [code-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/wio-terminal) फोल्डर में पा सकते हैं।

😀 आपका तापमान सेंसर प्रोग्राम सफल रहा!

**अस्वीकरण**:  
यह दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) का उपयोग करके अनुवादित किया गया है। जबकि हम सटीकता सुनिश्चित करने का प्रयास करते हैं, कृपया ध्यान दें कि स्वचालित अनुवाद में त्रुटियां या अशुद्धियां हो सकती हैं। मूल दस्तावेज़, जो इसकी मूल भाषा में है, को प्रामाणिक स्रोत माना जाना चाहिए। महत्वपूर्ण जानकारी के लिए, पेशेवर मानव अनुवाद की सिफारिश की जाती है। इस अनुवाद के उपयोग से उत्पन्न किसी भी गलतफहमी या गलत व्याख्या के लिए हम जिम्मेदार नहीं हैं।