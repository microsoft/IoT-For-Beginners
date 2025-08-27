<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "fbbcf96a9b63ccd661db98bbf854bb06",
  "translation_date": "2025-08-27T14:50:19+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-decode.md",
  "language_code": "ne"
}
-->
# GPS डेटा डिकोड गर्नुहोस् - Wio Terminal

यस पाठको यस भागमा, तपाईं Wio Terminal द्वारा GPS सेन्सरबाट पढिएको NMEA सन्देशहरू डिकोड गर्नुहुनेछ, र अक्षांश र देशान्तर निकाल्नुहुनेछ।

## GPS डेटा डिकोड गर्नुहोस्

जब कच्चा NMEA डेटा सिरियल पोर्टबाट पढिन्छ, यसलाई खुला स्रोत NMEA लाइब्रेरी प्रयोग गरेर डिकोड गर्न सकिन्छ।

### कार्य - GPS डेटा डिकोड गर्नुहोस्

डिभाइसलाई GPS डेटा डिकोड गर्न प्रोग्राम गर्नुहोस्।

1. यदि `gps-sensor` एप परियोजना खुला छैन भने यसलाई खोल्नुहोस्।

1. परियोजनाको `platformio.ini` फाइलमा [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus) लाइब्रेरीको निर्भरता थप्नुहोस्। यस लाइब्रेरीमा NMEA डेटा डिकोड गर्ने कोड छ।

    ```ini
    lib_deps =
        mikalhart/TinyGPSPlus @ 1.0.2
    ```

1. `main.cpp` मा, TinyGPSPlus लाइब्रेरीको लागि एक समावेश निर्देशन थप्नुहोस्:

    ```cpp
    #include <TinyGPS++.h>
    ```

1. `Serial3` को घोषणाको तल, NMEA वाक्यहरू प्रक्रिया गर्न TinyGPSPlus वस्तु घोषणा गर्नुहोस्:

    ```cpp
    TinyGPSPlus gps;
    ```

1. `printGPSData` फंक्शनको सामग्रीलाई निम्नमा परिवर्तन गर्नुहोस्:

    ```cpp
    if (gps.encode(Serial3.read()))
    {
        if (gps.location.isValid())
        {
            Serial.print(gps.location.lat(), 6);
            Serial.print(F(","));
            Serial.print(gps.location.lng(), 6);
            Serial.print(" - from ");
            Serial.print(gps.satellites.value());
            Serial.println(" satellites");
        }
    }
    ```

    यो कोडले UART सिरियल पोर्टबाट अर्को क्यारेक्टरलाई `gps` NMEA डिकोडरमा पढ्छ। प्रत्येक क्यारेक्टर पछि, यो जाँच गर्नेछ कि डिकोडरले मान्य वाक्य पढेको छ कि छैन, त्यसपछि यो जाँच गर्नेछ कि मान्य स्थान पढेको छ कि छैन। यदि स्थान मान्य छ भने, यो सिरियल मोनिटरमा पठाउँछ, साथमा यस फिक्समा योगदान गर्ने उपग्रहहरूको संख्या।

1. कोडलाई Wio Terminal मा निर्माण र अपलोड गर्नुहोस्।

1. अपलोड भएपछि, तपाईं सिरियल मोनिटर प्रयोग गरेर GPS स्थान डेटा अनुगमन गर्न सक्नुहुन्छ।

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 तपाईं यो कोड [code-gps-decode/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/wio-terminal) फोल्डरमा फेला पार्न सक्नुहुन्छ।

😀 तपाईंको GPS सेन्सर प्रोग्राम डेटा डिकोडिङको साथ सफल भयो!

---

**अस्वीकरण**:  
यो दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) प्रयोग गरेर अनुवाद गरिएको छ। हामी शुद्धताको लागि प्रयास गर्छौं, तर कृपया ध्यान दिनुहोस् कि स्वचालित अनुवादमा त्रुटिहरू वा अशुद्धताहरू हुन सक्छ। यसको मूल भाषा मा रहेको मूल दस्तावेज़लाई आधिकारिक स्रोत मानिनुपर्छ। महत्वपूर्ण जानकारीको लागि, व्यावसायिक मानव अनुवाद सिफारिस गरिन्छ। यस अनुवादको प्रयोगबाट उत्पन्न हुने कुनै पनि गलतफहमी वा गलत व्याख्याको लागि हामी जिम्मेवार हुने छैनौं।