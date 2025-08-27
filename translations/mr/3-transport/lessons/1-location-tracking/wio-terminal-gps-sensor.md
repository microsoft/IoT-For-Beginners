<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "da6ae0a795cf06be33d23ca5b8493fc8",
  "translation_date": "2025-08-27T14:37:05+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-sensor.md",
  "language_code": "mr"
}
-->
# GPS डेटा वाचा - Wio Terminal

या धड्याच्या या भागात, तुम्ही Wio Terminal ला GPS सेन्सर जोडाल आणि त्यातून डेटा वाचाल.

## हार्डवेअर

Wio Terminal ला GPS सेन्सरची आवश्यकता आहे.

तुम्ही वापरणार असलेला सेन्सर [Grove GPS Air530 सेन्सर](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html) आहे. हा सेन्सर अनेक GPS प्रणालींशी जोडला जाऊ शकतो, ज्यामुळे जलद आणि अचूक डेटा मिळतो. हा सेन्सर दोन भागांपासून बनलेला आहे - सेन्सरची मुख्य इलेक्ट्रॉनिक्स आणि एक बाह्य अँटेना, जो उपग्रहांकडून रेडिओ लहरी पकडण्यासाठी पातळ वायरने जोडलेला आहे.

हा UART सेन्सर आहे, त्यामुळे तो GPS डेटा UART वरून पाठवतो.

### GPS सेन्सर कनेक्ट करा

Grove GPS सेन्सर Wio Terminal शी जोडला जाऊ शकतो.

#### कार्य - GPS सेन्सर कनेक्ट करा

GPS सेन्सर कनेक्ट करा.

![Grove GPS सेन्सर](../../../../../translated_images/grove-gps-sensor.247943bf69b03f0d1820ef6ed10c587f9b650e8db55b936851c92412180bd3e2.mr.png)

1. Grove केबलचा एक टोक GPS सेन्सरवरील सॉकेटमध्ये घाला. ती फक्त एका दिशेनेच जाईल.

1. Wio Terminal तुमच्या संगणकापासून किंवा इतर पॉवर सप्लायपासून डिस्कनेक्ट केलेला असताना, Grove केबलचा दुसरा टोक Wio Terminal च्या स्क्रीनकडे पाहताना डाव्या बाजूच्या Grove सॉकेटमध्ये कनेक्ट करा. हा सॉकेट पॉवर बटणाच्या जवळ आहे.

    ![डाव्या सॉकेटला जोडलेला Grove GPS सेन्सर](../../../../../translated_images/wio-gps-sensor.19fd52b81ce58095d5deb3d4e5a1fdd88818d76569b00b1f0d740c92dc986525.mr.png)

1. GPS सेन्सर अशा प्रकारे ठेवा की जोडलेल्या अँटेना ला आकाश दिसेल - शक्यतो उघड्या खिडकीजवळ किंवा बाहेर. अँटेना समोर काहीही नसल्यास सिग्नल अधिक स्पष्ट मिळतो.

1. आता तुम्ही Wio Terminal तुमच्या संगणकाशी कनेक्ट करू शकता.

1. GPS सेन्सरमध्ये 2 LEDs आहेत - एक निळा LED जो डेटा प्रसारित होताना फ्लॅश होतो, आणि एक हिरवा LED जो उपग्रहांकडून डेटा प्राप्त होताना प्रत्येक सेकंदाला फ्लॅश होतो. Wio Terminal पॉवर केल्यानंतर निळा LED फ्लॅश होत असल्याची खात्री करा. काही मिनिटांनंतर हिरवा LED फ्लॅश होईल - जर तसे झाले नाही, तर तुम्हाला अँटेना पुन्हा ठेवल्याची गरज असू शकते.

## GPS सेन्सर प्रोग्राम करा

आता Wio Terminal ला जोडलेल्या GPS सेन्सरसाठी प्रोग्राम केले जाऊ शकते.

### कार्य - GPS सेन्सर प्रोग्राम करा

डिव्हाइस प्रोग्राम करा.

1. PlatformIO वापरून एक नवीन Wio Terminal प्रोजेक्ट तयार करा. या प्रोजेक्टचे नाव `gps-sensor` ठेवा. `setup` फंक्शनमध्ये सीरियल पोर्ट कॉन्फिगर करण्यासाठी कोड जोडा.

1. `main.cpp` फाईलच्या शीर्षस्थानी खालील include directive जोडा. हे डाव्या बाजूच्या Grove पोर्टसाठी UART कॉन्फिगर करण्यासाठी फंक्शन्स असलेली हेडर फाईल समाविष्ट करते.

    ```cpp
    #include <wiring_private.h>
    ```

1. याखाली, UART पोर्टसाठी सीरियल पोर्ट कनेक्शन डिक्लेअर करण्यासाठी खालील कोड जोडा:

    ```cpp
    static Uart Serial3(&sercom3, PIN_WIRE_SCL, PIN_WIRE_SDA, SERCOM_RX_PAD_1, UART_TX_PAD_0);
    ```

1. काही अंतर्गत सिग्नल हँडलर्स या सीरियल पोर्टकडे रीडायरेक्ट करण्यासाठी कोड जोडणे आवश्यक आहे. `Serial3` डिक्लेरेशनच्या खालील कोड जोडा:

    ```cpp
    void SERCOM3_0_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_1_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_2_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_3_Handler()
    {
        Serial3.IrqHandler();
    }
    ```

1. `setup` फंक्शनमध्ये, जिथे `Serial` पोर्ट कॉन्फिगर केला आहे, तिथे UART सीरियल पोर्ट कॉन्फिगर करण्यासाठी खालील कोड जोडा:

    ```cpp
    Serial3.begin(9600);

    while (!Serial3)
        ; // Wait for Serial3 to be ready

    delay(1000);
    ```

1. या कोडखाली, `setup` फंक्शनमध्ये, Grove पिन सीरियल पोर्टशी कनेक्ट करण्यासाठी खालील कोड जोडा:

    ```cpp
    pinPeripheral(PIN_WIRE_SCL, PIO_SERCOM_ALT);
    ```

1. `loop` फंक्शनच्या आधी खालील फंक्शन जोडा, जे GPS डेटा सीरियल मॉनिटरवर पाठवते:

    ```cpp
    void printGPSData()
    {
        Serial.println(Serial3.readStringUntil('\n'));
    }
    ```

1. `loop` फंक्शनमध्ये, UART सीरियल पोर्टवरून वाचण्यासाठी आणि सीरियल मॉनिटरवर आउटपुट प्रिंट करण्यासाठी खालील कोड जोडा:

    ```cpp
    while (Serial3.available() > 0)
    {
        printGPSData();
    }
    
    delay(1000);
    ```

    हा कोड UART सीरियल पोर्टवरून वाचतो. `readStringUntil` फंक्शन टर्मिनेटर कॅरेक्टरपर्यंत वाचतो, या प्रकरणात नवीन ओळ. हे संपूर्ण NMEA वाक्य वाचेल (NMEA वाक्ये नवीन ओळ कॅरेक्टरने समाप्त होतात). UART सीरियल पोर्टवरून डेटा वाचता येत असताना, तो वाचला जातो आणि `printGPSData` फंक्शनद्वारे सीरियल मॉनिटरवर पाठवला जातो. एकदा डेटा वाचणे थांबले की, `loop` 1 सेकंद (1,000ms) थांबतो.

1. कोड तयार करा आणि Wio Terminal वर अपलोड करा.

1. अपलोड झाल्यानंतर, सीरियल मॉनिटर वापरून GPS डेटा मॉनिटर करू शकता.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GPGSA,A,1,,,,,,,,,,,,,,,*1E
    $BDGSA,A,1,,,,,,,,,,,,,,,*0F
    $GPGSV,1,1,00*79
    $BDGSV,1,1,00*68
    ```

> 💁 तुम्हाला हा कोड [code-gps/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps/wio-terminal) फोल्डरमध्ये सापडेल.

😀 तुमचा GPS सेन्सर प्रोग्राम यशस्वी झाला!

---

**अस्वीकरण**:  
हा दस्तऐवज AI भाषांतर सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) चा वापर करून भाषांतरित करण्यात आला आहे. आम्ही अचूकतेसाठी प्रयत्नशील असलो तरी, कृपया लक्षात घ्या की स्वयंचलित भाषांतरांमध्ये त्रुटी किंवा अचूकतेचा अभाव असू शकतो. मूळ भाषेतील मूळ दस्तऐवज हा अधिकृत स्रोत मानला जावा. महत्त्वाच्या माहितीसाठी व्यावसायिक मानवी भाषांतराची शिफारस केली जाते. या भाषांतराचा वापर केल्यामुळे उद्भवणाऱ्या कोणत्याही गैरसमज किंवा चुकीच्या अर्थासाठी आम्ही जबाबदार राहणार नाही.