<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "288aebb0c59f7be1d2719b8f9660a313",
  "translation_date": "2025-08-27T10:53:28+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/wio-terminal-proximity.md",
  "language_code": "ne"
}
-->
# नजिकको दूरी पत्ता लगाउनुहोस् - Wio Terminal

यस पाठको यस भागमा, तपाईं आफ्नो Wio Terminal मा एक proximity sensor थप्नुहुनेछ र यसबाट दूरी पढ्नुहुनेछ।

## हार्डवेयर

Wio Terminal लाई एक proximity sensor चाहिन्छ।

तपाईंले प्रयोग गर्ने सेन्सर [Grove Time of Flight distance sensor](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html) हो। यो सेन्सरले लेजर रेंजिङ मोड्युल प्रयोग गरेर दूरी पत्ता लगाउँछ। यो सेन्सरको दायरा 10mm देखि 2000mm (1cm - 2m) सम्म छ, र यसले उक्त दायरामा दूरीलाई धेरै सही रूपमा रिपोर्ट गर्दछ। 1000mm भन्दा माथिको दूरीलाई 8109mm को रूपमा रिपोर्ट गरिन्छ।

लेजर रेंजफाइन्डर सेन्सरको पछाडि छ, Grove सॉकेटको विपरीत पक्षमा।

यो एक I²C सेन्सर हो।

### टाइम अफ फ्लाइट सेन्सर जडान गर्नुहोस्

Grove टाइम अफ फ्लाइट सेन्सरलाई Wio Terminal मा जडान गर्न सकिन्छ।

#### कार्य - टाइम अफ फ्लाइट सेन्सर जडान गर्नुहोस्

टाइम अफ फ्लाइट सेन्सर जडान गर्नुहोस्।

![एक Grove टाइम अफ फ्लाइट सेन्सर](../../../../../translated_images/grove-time-of-flight-sensor.d82ff2165bfded9f485de54d8d07195a6270a602696825fca19f629ddfe94e86.ne.png)

1. Grove केबलको एक छेउ टाइम अफ फ्लाइट सेन्सरको सॉकेटमा हाल्नुहोस्। यो केवल एक तरिकामा मात्र जडान हुन्छ।

1. Wio Terminal लाई तपाईंको कम्प्युटर वा अन्य पावर सप्लाईबाट डिस्कनेक्ट गरेर, Grove केबलको अर्को छेउलाई Wio Terminal को स्क्रिनतर्फ हेर्दा बायाँतर्फको Grove सॉकेटमा जडान गर्नुहोस्। यो सॉकेट पावर बटनको नजिक छ। यो डिजिटल र I²C सॉकेट हो।

![Grove टाइम अफ फ्लाइट सेन्सर बायाँ सॉकेटमा जडान गरिएको](../../../../../translated_images/wio-time-of-flight-sensor.c4c182131d2ea73df67febd004dc0313d271013d016be9c47e7da4d77c6c20a8.ne.png)

1. अब तपाईं Wio Terminal लाई आफ्नो कम्प्युटरमा जडान गर्न सक्नुहुन्छ।

## टाइम अफ फ्लाइट सेन्सर प्रोग्राम गर्नुहोस्

अब Wio Terminal लाई जडान गरिएको टाइम अफ फ्लाइट सेन्सर प्रयोग गर्न प्रोग्राम गर्न सकिन्छ।

### कार्य - टाइम अफ फ्लाइट सेन्सर प्रोग्राम गर्नुहोस्

1. PlatformIO प्रयोग गरेर नयाँ Wio Terminal प्रोजेक्ट बनाउनुहोस्। यस प्रोजेक्टलाई `distance-sensor` नाम दिनुहोस्। `setup` फङ्सनमा सीरियल पोर्ट कन्फिगर गर्न कोड थप्नुहोस्।

1. प्रोजेक्टको `platformio.ini` फाइलमा Seeed Grove टाइम अफ फ्लाइट डिस्टेन्स सेन्सर लाइब्रेरीको निर्भरता थप्नुहोस्:

    ```ini
    lib_deps =
        seeed-studio/Grove Ranging sensor - VL53L0X @ ^1.1.1
    ```

1. `main.cpp` मा, पहिले नै भएका include निर्देशहरू तल निम्न कोड थप्नुहोस् ताकि टाइम अफ फ्लाइट सेन्सरसँग अन्तरक्रिया गर्न `Seeed_vl53l0x` क्लासको एक instance घोषणा गर्न सकियोस्:

    ```cpp
    #include "Seeed_vl53l0x.h"
    
    Seeed_vl53l0x VL53L0X;
    ```

1. `setup` फङ्सनको अन्त्यमा निम्न कोड थप्नुहोस् ताकि सेन्सरलाई इनिशियलाइज गर्न सकियोस्:

    ```cpp
    VL53L0X.VL53L0X_common_init();
    VL53L0X.VL53L0X_high_accuracy_ranging_init();
    ```

1. `loop` फङ्सनमा, सेन्सरबाट मान पढ्नुहोस्:

    ```cpp
    VL53L0X_RangingMeasurementData_t RangingMeasurementData;
    memset(&RangingMeasurementData, 0, sizeof(VL53L0X_RangingMeasurementData_t));

    VL53L0X.PerformSingleRangingMeasurement(&RangingMeasurementData);
    ```

    यो कोडले डेटा संरचना इनिशियलाइज गर्छ ताकि यसमा डेटा पढ्न सकियोस्, त्यसपछि यसलाई `PerformSingleRangingMeasurement` मेथडमा पास गरिन्छ जहाँ यो दूरी मापनले भरिन्छ।

1. यसको तल, दूरी मापनलाई लेख्नुहोस्, त्यसपछि 1 सेकेन्डको लागि ढिलाइ गर्नुहोस्:

    ```cpp
    Serial.print("Distance = ");
    Serial.print(RangingMeasurementData.RangeMilliMeter);
    Serial.println(" mm");

    delay(1000);
    ```

1. यो कोड निर्माण, अपलोड र चलाउनुहोस्। तपाईं सीरियल मोनिटरमा दूरी मापन देख्न सक्नुहुन्छ। सेन्सर नजिक वस्तुहरू राख्नुहोस् र तपाईं दूरी मापन देख्नुहुनेछ:

    ```output
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    रेंजफाइन्डर सेन्सरको पछाडि छ, त्यसैले दूरी मापन गर्दा सही पक्ष प्रयोग गर्न निश्चित गर्नुहोस्।

    ![टाइम अफ फ्लाइट सेन्सरको पछाडि रेंजफाइन्डरले केरा तर्फ इशारा गर्दै](../../../../../translated_images/time-of-flight-banana.079921ad8b1496e4525dc26b4cdc71a076407aba3e72ba113ba2e38febae92c5.ne.png)

> 💁 तपाईं यो कोड [code-proximity/wio-terminal](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/wio-terminal) फोल्डरमा पाउन सक्नुहुन्छ।

😀 तपाईंको proximity sensor प्रोग्राम सफल भयो!

---

**अस्वीकरण**:  
यो दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) प्रयोग गरेर अनुवाद गरिएको छ। हामी शुद्धताको लागि प्रयास गर्छौं, तर कृपया ध्यान दिनुहोस् कि स्वचालित अनुवादहरूमा त्रुटि वा अशुद्धता हुन सक्छ। यसको मूल भाषा मा रहेको मूल दस्तावेज़लाई आधिकारिक स्रोत मानिनुपर्छ। महत्वपूर्ण जानकारीको लागि, व्यावसायिक मानव अनुवाद सिफारिस गरिन्छ। यस अनुवादको प्रयोगबाट उत्पन्न हुने कुनै पनि गलतफहमी वा गलत व्याख्याको लागि हामी जिम्मेवार हुने छैनौं।