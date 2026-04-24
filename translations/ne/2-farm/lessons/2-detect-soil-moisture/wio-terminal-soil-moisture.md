# माटोको चिस्यान मापन गर्नुहोस् - Wio Terminal

यस पाठको यस भागमा, तपाईं Wio Terminal मा एक capacitive माटोको चिस्यान सेन्सर थप्नुहुनेछ, र यसबाट मानहरू पढ्नुहुनेछ।

## हार्डवेयर

Wio Terminal लाई एक capacitive माटोको चिस्यान सेन्सर चाहिन्छ।

तपाईंले प्रयोग गर्ने सेन्सर [Capacitive Soil Moisture Sensor](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html) हो, जसले माटोको चिस्यान मापन गर्दछ माटोको capacitance पत्ता लगाएर। यो गुण माटोको चिस्यान परिवर्तन हुँदा परिवर्तन हुन्छ। माटोको चिस्यान बढ्दै जाँदा, भोल्टेज घट्छ।

यो एक एनालग सेन्सर हो, त्यसैले यो Wio Terminal को एनालग पिनमा जडान हुन्छ, जसले ०-१,०२३ को मान सिर्जना गर्नको लागि अनबोर्ड ADC प्रयोग गर्दछ।

### माटोको चिस्यान सेन्सर जडान गर्नुहोस्

Grove माटोको चिस्यान सेन्सर Wio Terminal को कन्फिगरेबल एनालग/डिजिटल पोर्टमा जडान गर्न सकिन्छ।

#### कार्य - माटोको चिस्यान सेन्सर जडान गर्नुहोस्

माटोको चिस्यान सेन्सर जडान गर्नुहोस्।

![एक Grove माटोको चिस्यान सेन्सर](../../../../../translated_images/ne/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78b.webp)

1. Grove केबलको एक छेउ माटोको चिस्यान सेन्सरको सॉकेटमा हाल्नुहोस्। यो केवल एक तरिकामा मात्र जडान हुन्छ।

1. Wio Terminal लाई तपाईंको कम्प्युटर वा अन्य पावर सप्लाईबाट डिस्कनेक्ट गरेर, Grove केबलको अर्को छेउ Wio Terminal को स्क्रिन हेर्दा दायाँपट्टि रहेको Grove सॉकेटमा जडान गर्नुहोस्। यो सॉकेट पावर बटनबाट सबैभन्दा टाढा रहेको छ।

![Grove माटोको चिस्यान सेन्सर दायाँपट्टि रहेको सॉकेटमा जडान गरिएको](../../../../../translated_images/ne/wio-soil-moisture-sensor.46919b61c3f6cb74.webp)

1. माटोको चिस्यान सेन्सरलाई माटोमा हाल्नुहोस्। यसमा 'सबभन्दा माथिल्लो स्थान रेखा' छ - सेन्सरमा सेतो रेखा। सेन्सरलाई यस रेखासम्म तर यसलाई पार नगरी हाल्नुहोस्।

![माटोमा Grove माटोको चिस्यान सेन्सर](../../../../../translated_images/ne/soil-moisture-sensor-in-soil.bfad91002bda5e96.webp)

1. अब तपाईं Wio Terminal लाई तपाईंको कम्प्युटरमा जडान गर्न सक्नुहुन्छ।

## माटोको चिस्यान सेन्सर प्रोग्राम गर्नुहोस्

अब Wio Terminal लाई जडान गरिएको माटोको चिस्यान सेन्सर प्रयोग गर्न प्रोग्राम गर्न सकिन्छ।

### कार्य - माटोको चिस्यान सेन्सर प्रोग्राम गर्नुहोस्

डिभाइस प्रोग्राम गर्नुहोस्।

1. PlatformIO प्रयोग गरेर नयाँ Wio Terminal प्रोजेक्ट सिर्जना गर्नुहोस्। यस प्रोजेक्टलाई `soil-moisture-sensor` नाम दिनुहोस्। `setup` फङ्सनमा सिरियल पोर्ट कन्फिगर गर्न कोड थप्नुहोस्।

    > ⚠️ तपाईं [प्रोजेक्ट १, पाठ १ मा PlatformIO प्रोजेक्ट सिर्जना गर्ने निर्देशनहरू](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project) आवश्यक परेमा हेर्न सक्नुहुन्छ।

1. यस सेन्सरको लागि कुनै लाइब्रेरी छैन, तर तपाईं एनालग पिनबाट मान पढ्न Arduino को [`analogRead`](https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/) फङ्सन प्रयोग गर्न सक्नुहुन्छ। सुरुमा एनालग पिनलाई इनपुटको लागि कन्फिगर गर्नुहोस् ताकि यसबाट मानहरू पढ्न सकियोस्। `setup` फङ्सनमा निम्न कोड थप्नुहोस्।

    ```cpp
    pinMode(A0, INPUT);
    ```

    यसले `A0` पिनलाई, एनालग/डिजिटल पिनलाई, इनपुट पिनको रूपमा सेट गर्दछ जसबाट भोल्टेज पढ्न सकिन्छ।

1. `loop` फङ्सनमा निम्न कोड थप्नुहोस् ताकि यस पिनबाट भोल्टेज पढ्न सकियोस्:

    ```cpp
    int soil_moisture = analogRead(A0);
    ```

1. यस कोडको तल निम्न कोड थप्नुहोस् ताकि मानलाई सिरियल पोर्टमा प्रिन्ट गर्न सकियोस्:

    ```cpp
    Serial.print("Soil Moisture: ");
    Serial.println(soil_moisture);
    ```

1. अन्त्यमा १० सेकेन्डको ढिलाइ थप्नुहोस्:

    ```cpp
    delay(10000);
    ```

1. कोडलाई Wio Terminal मा निर्माण र अपलोड गर्नुहोस्।

    > ⚠️ तपाईं [प्रोजेक्ट १, पाठ १ मा PlatformIO प्रोजेक्ट सिर्जना गर्ने निर्देशनहरू](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app) आवश्यक परेमा हेर्न सक्नुहुन्छ।

1. अपलोड भएपछि, तपाईं सिरियल मोनिटर प्रयोग गरेर माटोको चिस्यान अनुगमन गर्न सक्नुहुन्छ। माटोमा पानी थप्नुहोस्, वा सेन्सरलाई माटोबाट हटाउनुहोस्, र मान परिवर्तन भएको हेर्नुहोस्।

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

    माथिको उदाहरण आउटपुटमा, तपाईंले पानी थप्दा भोल्टेज घटेको देख्न सक्नुहुन्छ।

> 💁 तपाईं यो कोड [code/wio-terminal](../../../../../2-farm/lessons/2-detect-soil-moisture/code/wio-terminal) फोल्डरमा पाउन सक्नुहुन्छ।

😀 तपाईंको माटोको चिस्यान सेन्सर प्रोग्राम सफल भयो!

---

**अस्वीकरण**:  
यो दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) प्रयोग गरेर अनुवाद गरिएको हो। हामी शुद्धताको लागि प्रयास गर्छौं, तर कृपया ध्यान दिनुहोस् कि स्वचालित अनुवादमा त्रुटिहरू वा अशुद्धताहरू हुन सक्छ। यसको मूल भाषा मा रहेको मूल दस्तावेज़लाई आधिकारिक स्रोत मानिनुपर्छ। महत्वपूर्ण जानकारीको लागि, व्यावसायिक मानव अनुवाद सिफारिस गरिन्छ। यस अनुवादको प्रयोगबाट उत्पन्न हुने कुनै पनि गलतफहमी वा गलत व्याख्याको लागि हामी जिम्मेवार हुने छैनौं।