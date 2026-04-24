# मिट्टी की नमी मापें - Wio Terminal

इस पाठ के इस भाग में, आप अपने Wio Terminal में एक कैपेसिटिव मिट्टी नमी सेंसर जोड़ेंगे और इससे मान पढ़ेंगे।

## हार्डवेयर

Wio Terminal को एक कैपेसिटिव मिट्टी नमी सेंसर की आवश्यकता है।

आप जो सेंसर उपयोग करेंगे वह है [Capacitive Soil Moisture Sensor](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html), जो मिट्टी की नमी को मापता है मिट्टी की कैपेसिटेंस का पता लगाकर। यह एक गुण है जो मिट्टी की नमी के बदलने पर बदलता है। जैसे-जैसे मिट्टी की नमी बढ़ती है, वोल्टेज घटता है।

यह एक एनालॉग सेंसर है, इसलिए यह Wio Terminal के एनालॉग पिन से जुड़ता है और ऑनबोर्ड ADC का उपयोग करके 0-1,023 के बीच एक मान उत्पन्न करता है।

### मिट्टी नमी सेंसर को कनेक्ट करें

Grove मिट्टी नमी सेंसर को Wio Terminal के कॉन्फ़िगर करने योग्य एनालॉग/डिजिटल पोर्ट से जोड़ा जा सकता है।

#### कार्य - मिट्टी नमी सेंसर को कनेक्ट करें

मिट्टी नमी सेंसर को कनेक्ट करें।

![Grove मिट्टी नमी सेंसर](../../../../../translated_images/hi/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78b.webp)

1. Grove केबल के एक सिरे को मिट्टी नमी सेंसर के सॉकेट में डालें। यह केवल एक ही दिशा में जाएगा।

1. Wio Terminal को अपने कंप्यूटर या अन्य पावर स्रोत से डिस्कनेक्ट करके रखें, और Grove केबल के दूसरे सिरे को Wio Terminal के स्क्रीन की ओर देखते हुए दाईं ओर के Grove सॉकेट में कनेक्ट करें। यह सॉकेट पावर बटन से सबसे दूर है।

![Grove मिट्टी नमी सेंसर दाएं सॉकेट से जुड़ा हुआ](../../../../../translated_images/hi/wio-soil-moisture-sensor.46919b61c3f6cb74.webp)

1. मिट्टी नमी सेंसर को मिट्टी में डालें। इसमें एक 'उच्चतम स्थिति रेखा' होती है - सेंसर पर एक सफेद रेखा। सेंसर को इस रेखा तक डालें लेकिन इसे पार न करें।

![मिट्टी में Grove मिट्टी नमी सेंसर](../../../../../translated_images/hi/soil-moisture-sensor-in-soil.bfad91002bda5e96.webp)

1. अब आप Wio Terminal को अपने कंप्यूटर से कनेक्ट कर सकते हैं।

## मिट्टी नमी सेंसर को प्रोग्राम करें

अब Wio Terminal को जुड़े हुए मिट्टी नमी सेंसर का उपयोग करने के लिए प्रोग्राम किया जा सकता है।

### कार्य - मिट्टी नमी सेंसर को प्रोग्राम करें

डिवाइस को प्रोग्राम करें।

1. PlatformIO का उपयोग करके एक नया Wio Terminal प्रोजेक्ट बनाएं। इस प्रोजेक्ट का नाम `soil-moisture-sensor` रखें। `setup` फ़ंक्शन में सीरियल पोर्ट को कॉन्फ़िगर करने के लिए कोड जोड़ें।

    > ⚠️ यदि आवश्यक हो, तो [प्रोजेक्ट 1, पाठ 1 में PlatformIO प्रोजेक्ट बनाने के निर्देश देखें](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project)।

1. इस सेंसर के लिए कोई लाइब्रेरी उपलब्ध नहीं है, इसके बजाय आप एनालॉग पिन से मान पढ़ने के लिए Arduino के अंतर्निहित [`analogRead`](https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/) फ़ंक्शन का उपयोग कर सकते हैं। सबसे पहले, एनालॉग पिन को इनपुट के लिए कॉन्फ़िगर करें ताकि इससे मान पढ़े जा सकें। इसे `setup` फ़ंक्शन में निम्नलिखित कोड जोड़कर करें:

    ```cpp
    pinMode(A0, INPUT);
    ```

    यह `A0` पिन, जो कि संयुक्त एनालॉग/डिजिटल पिन है, को एक इनपुट पिन के रूप में सेट करता है जिससे वोल्टेज पढ़ा जा सके।

1. `loop` फ़ंक्शन में निम्नलिखित कोड जोड़ें ताकि इस पिन से वोल्टेज पढ़ा जा सके:

    ```cpp
    int soil_moisture = analogRead(A0);
    ```

1. इस कोड के नीचे, सीरियल पोर्ट पर मान प्रिंट करने के लिए निम्नलिखित कोड जोड़ें:

    ```cpp
    Serial.print("Soil Moisture: ");
    Serial.println(soil_moisture);
    ```

1. अंत में, 10 सेकंड की देरी जोड़ें:

    ```cpp
    delay(10000);
    ```

1. कोड को Wio Terminal पर बिल्ड और अपलोड करें।

    > ⚠️ यदि आवश्यक हो, तो [प्रोजेक्ट 1, पाठ 1 में PlatformIO प्रोजेक्ट बनाने के निर्देश देखें](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app)।

1. अपलोड हो जाने के बाद, आप सीरियल मॉनिटर का उपयोग करके मिट्टी की नमी की निगरानी कर सकते हैं। मिट्टी में पानी डालें, या सेंसर को मिट्टी से हटा दें, और मान बदलते हुए देखें।

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Soil Moisture: 526
    Soil Moisture: 529
    Soil Moisture: 521
    Soil Moisture: 494
    Soil Moisture: 454
    Soil Moisture: 456
    Soil Moisture: 395
    Soil Moisture: 388
    Soil Moisture: 394
    Soil Moisture: 391
    ```

    ऊपर दिए गए उदाहरण आउटपुट में, आप देख सकते हैं कि पानी डालने पर वोल्टेज कैसे गिरता है।

> 💁 आप इस कोड को [code/wio-terminal](../../../../../2-farm/lessons/2-detect-soil-moisture/code/wio-terminal) फ़ोल्डर में पा सकते हैं।

😀 आपका मिट्टी नमी सेंसर प्रोग्राम सफल रहा!

**अस्वीकरण**:  
यह दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) का उपयोग करके अनुवादित किया गया है। जबकि हम सटीकता सुनिश्चित करने का प्रयास करते हैं, कृपया ध्यान दें कि स्वचालित अनुवाद में त्रुटियां या अशुद्धियां हो सकती हैं। मूल भाषा में उपलब्ध मूल दस्तावेज़ को आधिकारिक स्रोत माना जाना चाहिए। महत्वपूर्ण जानकारी के लिए, पेशेवर मानव अनुवाद की सिफारिश की जाती है। इस अनुवाद के उपयोग से उत्पन्न किसी भी गलतफहमी या गलत व्याख्या के लिए हम जिम्मेदार नहीं हैं।