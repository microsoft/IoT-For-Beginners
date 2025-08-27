<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "fbbcf96a9b63ccd661db98bbf854bb06",
  "translation_date": "2025-08-27T14:50:08+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-decode.md",
  "language_code": "mr"
}
-->
# GPS डेटा डिकोड करा - Wio Terminal

या धड्याच्या भागात, तुम्ही Wio Terminal द्वारे GPS सेन्सरकडून वाचलेल्या NMEA संदेशांचे डिकोडिंग कराल आणि अक्षांश व रेखांश काढून घेणार.

## GPS डेटा डिकोड करा

जेव्हा कच्चा NMEA डेटा सिरियल पोर्टवरून वाचला जातो, तेव्हा तो ओपन सोर्स NMEA लायब्ररी वापरून डिकोड केला जाऊ शकतो.

### कार्य - GPS डेटा डिकोड करा

डिव्हाइस प्रोग्राम करा जेणेकरून GPS डेटा डिकोड करता येईल.

1. `gps-sensor` अ‍ॅप प्रोजेक्ट उघडा, जर ते आधीच उघडले नसेल.

1. प्रोजेक्टच्या `platformio.ini` फाइलमध्ये [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus) लायब्ररीसाठी लायब्ररी डिपेंडन्सी जोडा. या लायब्ररीमध्ये NMEA डेटा डिकोड करण्यासाठी कोड आहे.

    ```ini
    lib_deps =
        mikalhart/TinyGPSPlus @ 1.0.2
    ```

1. `main.cpp` मध्ये, TinyGPSPlus लायब्ररीसाठी एक `include` निर्देश जोडा:

    ```cpp
    #include <TinyGPS++.h>
    ```

1. `Serial3` च्या घोषणेनंतर, NMEA वाक्ये प्रक्रिया करण्यासाठी TinyGPSPlus ऑब्जेक्ट घोषित करा:

    ```cpp
    TinyGPSPlus gps;
    ```

1. `printGPSData` फंक्शनची सामग्री खालीलप्रमाणे बदला:

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

    हा कोड UART सिरियल पोर्टमधून पुढील कॅरेक्टर `gps` NMEA डिकोडरमध्ये वाचतो. प्रत्येक कॅरेक्टरनंतर, डिकोडरने वैध वाक्य वाचले आहे का ते तपासते, आणि नंतर वैध लोकेशन वाचले आहे का ते तपासते. जर लोकेशन वैध असेल, तर ते सिरियल मॉनिटरवर पाठवते, तसेच या फिक्ससाठी योगदान दिलेल्या उपग्रहांची संख्या देखील पाठवते.

1. कोड तयार करा आणि Wio Terminal वर अपलोड करा.

1. अपलोड झाल्यानंतर, तुम्ही सिरियल मॉनिटर वापरून GPS लोकेशन डेटा पाहू शकता.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 तुम्ही हा कोड [code-gps-decode/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/wio-terminal) फोल्डरमध्ये शोधू शकता.

😀 तुमचा GPS सेन्सर प्रोग्राम डेटा डिकोडिंगसह यशस्वी झाला!

---

**अस्वीकरण**:  
हा दस्तऐवज [Co-op Translator](https://github.com/Azure/co-op-translator) या एआय भाषांतर सेवेचा वापर करून भाषांतरित करण्यात आला आहे. आम्ही अचूकतेसाठी प्रयत्नशील असलो तरी कृपया लक्षात घ्या की स्वयंचलित भाषांतरांमध्ये त्रुटी किंवा अचूकतेचा अभाव असू शकतो. मूळ भाषेतील दस्तऐवज हा अधिकृत स्रोत मानला जावा. महत्त्वाच्या माहितीसाठी व्यावसायिक मानवी भाषांतराची शिफारस केली जाते. या भाषांतराचा वापर केल्यामुळे उद्भवणाऱ्या कोणत्याही गैरसमज किंवा चुकीच्या अर्थासाठी आम्ही जबाबदार राहणार नाही.