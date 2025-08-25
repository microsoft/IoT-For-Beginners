<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "fbbcf96a9b63ccd661db98bbf854bb06",
  "translation_date": "2025-08-25T18:07:25+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-decode.md",
  "language_code": "hi"
}
-->
# GPS डेटा डिकोड करें - Wio Terminal

इस पाठ के इस भाग में, आप Wio Terminal द्वारा GPS सेंसर से पढ़े गए NMEA संदेशों को डिकोड करेंगे और अक्षांश और देशांतर निकालेंगे।

## GPS डेटा डिकोड करें

एक बार जब कच्चा NMEA डेटा सीरियल पोर्ट से पढ़ लिया जाता है, तो इसे एक ओपन सोर्स NMEA लाइब्रेरी का उपयोग करके डिकोड किया जा सकता है।

### कार्य - GPS डेटा डिकोड करें

डिवाइस को GPS डेटा डिकोड करने के लिए प्रोग्राम करें।

1. यदि `gps-sensor` ऐप प्रोजेक्ट पहले से खुला नहीं है, तो इसे खोलें।

1. प्रोजेक्ट के `platformio.ini` फाइल में [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus) लाइब्रेरी के लिए एक लाइब्रेरी डिपेंडेंसी जोड़ें। इस लाइब्रेरी में NMEA डेटा डिकोड करने के लिए कोड है।

    ```ini
    lib_deps =
        mikalhart/TinyGPSPlus @ 1.0.2
    ```

1. `main.cpp` में, TinyGPSPlus लाइब्रेरी के लिए एक include निर्देश जोड़ें:

    ```cpp
    #include <TinyGPS++.h>
    ```

1. `Serial3` की घोषणा के नीचे, NMEA वाक्यों को प्रोसेस करने के लिए एक TinyGPSPlus ऑब्जेक्ट घोषित करें:

    ```cpp
    TinyGPSPlus gps;
    ```

1. `printGPSData` फ़ंक्शन की सामग्री को निम्नलिखित में बदलें:

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

    यह कोड UART सीरियल पोर्ट से अगला कैरेक्टर `gps` NMEA डिकोडर में पढ़ता है। प्रत्येक कैरेक्टर के बाद, यह जांचता है कि डिकोडर ने एक वैध वाक्य पढ़ा है या नहीं, फिर यह जांचता है कि क्या उसने एक वैध स्थान पढ़ा है। यदि स्थान वैध है, तो यह इसे सीरियल मॉनिटर पर भेजता है, साथ ही उन उपग्रहों की संख्या के साथ जिन्होंने इस फिक्स में योगदान दिया।

1. कोड को Wio Terminal पर बिल्ड और अपलोड करें।

1. अपलोड हो जाने के बाद, आप सीरियल मॉनिटर का उपयोग करके GPS स्थान डेटा की निगरानी कर सकते हैं।

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 आप इस कोड को [code-gps-decode/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/wio-terminal) फ़ोल्डर में पा सकते हैं।

😀 आपका GPS सेंसर प्रोग्राम डेटा डिकोडिंग के साथ सफल रहा!

**अस्वीकरण**:  
यह दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) का उपयोग करके अनुवादित किया गया है। जबकि हम सटीकता सुनिश्चित करने का प्रयास करते हैं, कृपया ध्यान दें कि स्वचालित अनुवाद में त्रुटियां या अशुद्धियां हो सकती हैं। मूल भाषा में उपलब्ध मूल दस्तावेज़ को प्रामाणिक स्रोत माना जाना चाहिए। महत्वपूर्ण जानकारी के लिए, पेशेवर मानव अनुवाद की सिफारिश की जाती है। इस अनुवाद के उपयोग से उत्पन्न किसी भी गलतफहमी या गलत व्याख्या के लिए हम उत्तरदायी नहीं हैं।