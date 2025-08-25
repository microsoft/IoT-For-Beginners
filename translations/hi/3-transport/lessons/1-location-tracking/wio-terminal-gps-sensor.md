<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "da6ae0a795cf06be33d23ca5b8493fc8",
  "translation_date": "2025-08-25T18:02:28+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-sensor.md",
  "language_code": "hi"
}
-->
# GPS डेटा पढ़ें - Wio Terminal

इस पाठ के इस भाग में, आप अपने Wio Terminal में एक GPS सेंसर जोड़ेंगे और उससे मान पढ़ेंगे।

## हार्डवेयर

Wio Terminal को एक GPS सेंसर की आवश्यकता है।

आप जो सेंसर उपयोग करेंगे वह [Grove GPS Air530 सेंसर](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html) है। यह सेंसर कई GPS सिस्टम्स से जुड़ सकता है ताकि तेज़ और सटीक डेटा प्राप्त किया जा सके। सेंसर दो भागों से बना है - सेंसर के मुख्य इलेक्ट्रॉनिक्स और एक बाहरी एंटीना जो पतले तार से जुड़ा होता है ताकि सैटेलाइट्स से रेडियो तरंगें प्राप्त की जा सकें।

यह एक UART सेंसर है, जो UART के माध्यम से GPS डेटा भेजता है।

### GPS सेंसर को कनेक्ट करें

Grove GPS सेंसर को Wio Terminal से जोड़ा जा सकता है।

#### कार्य - GPS सेंसर को कनेक्ट करें

GPS सेंसर को कनेक्ट करें।

![एक Grove GPS सेंसर](../../../../../translated_images/grove-gps-sensor.247943bf69b03f0d1820ef6ed10c587f9b650e8db55b936851c92412180bd3e2.hi.png)

1. Grove केबल का एक सिरा GPS सेंसर के सॉकेट में डालें। यह केवल एक ही दिशा में जाएगा।

1. Wio Terminal को आपके कंप्यूटर या अन्य पावर सप्लाई से डिस्कनेक्ट करके, Grove केबल का दूसरा सिरा Wio Terminal के स्क्रीन की ओर देखते हुए बाएं तरफ के Grove सॉकेट में कनेक्ट करें। यह सॉकेट पावर बटन के सबसे करीब है।

    ![बाएं सॉकेट में कनेक्ट किया गया Grove GPS सेंसर](../../../../../translated_images/wio-gps-sensor.19fd52b81ce58095d5deb3d4e5a1fdd88818d76569b00b1f0d740c92dc986525.hi.png)

1. GPS सेंसर को इस तरह से रखें कि जुड़ा हुआ एंटीना आकाश को देख सके - आदर्श रूप से एक खुले खिड़की के पास या बाहर। एंटीना के रास्ते में कुछ भी न होने पर सिग्नल अधिक स्पष्ट रूप से प्राप्त होता है।

1. अब आप Wio Terminal को अपने कंप्यूटर से कनेक्ट कर सकते हैं।

1. GPS सेंसर में 2 LEDs होती हैं - एक नीली LED जो डेटा ट्रांसमिट होने पर चमकती है, और एक हरी LED जो सैटेलाइट्स से डेटा प्राप्त करने पर हर सेकंड चमकती है। सुनिश्चित करें कि Wio Terminal को पावर देने पर नीली LED चमक रही हो। कुछ मिनटों के बाद हरी LED चमकने लगेगी - अगर ऐसा नहीं होता है, तो आपको एंटीना को पुनः स्थिति में रखना पड़ सकता है।

## GPS सेंसर को प्रोग्राम करें

अब Wio Terminal को जुड़े हुए GPS सेंसर का उपयोग करने के लिए प्रोग्राम किया जा सकता है।

### कार्य - GPS सेंसर को प्रोग्राम करें

डिवाइस को प्रोग्राम करें।

1. PlatformIO का उपयोग करके एक नया Wio Terminal प्रोजेक्ट बनाएं। इस प्रोजेक्ट का नाम `gps-sensor` रखें। `setup` फंक्शन में सीरियल पोर्ट को कॉन्फ़िगर करने के लिए कोड जोड़ें।

1. `main.cpp` फाइल के शीर्ष पर निम्नलिखित include निर्देश जोड़ें। यह एक हेडर फाइल को शामिल करता है जिसमें UART के लिए बाएं Grove पोर्ट को कॉन्फ़िगर करने के लिए फंक्शन होते हैं।

    ```cpp
    #include <wiring_private.h>
    ```

1. इसके नीचे, UART पोर्ट के लिए सीरियल पोर्ट कनेक्शन घोषित करने के लिए निम्नलिखित कोड जोड़ें:

    ```cpp
    static Uart Serial3(&sercom3, PIN_WIRE_SCL, PIN_WIRE_SDA, SERCOM_RX_PAD_1, UART_TX_PAD_0);
    ```

1. आपको कुछ आंतरिक सिग्नल हैंडलर्स को इस सीरियल पोर्ट पर रीडायरेक्ट करने के लिए कोड जोड़ने की आवश्यकता है। `Serial3` घोषणा के नीचे निम्नलिखित कोड जोड़ें:

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

1. `setup` फंक्शन में, जहां `Serial` पोर्ट कॉन्फ़िगर किया गया है, UART सीरियल पोर्ट को निम्नलिखित कोड के साथ कॉन्फ़िगर करें:

    ```cpp
    Serial3.begin(9600);

    while (!Serial3)
        ; // Wait for Serial3 to be ready

    delay(1000);
    ```

1. `setup` फंक्शन में इस कोड के नीचे, Grove पिन को सीरियल पोर्ट से कनेक्ट करने के लिए निम्नलिखित कोड जोड़ें:

    ```cpp
    pinPeripheral(PIN_WIRE_SCL, PIO_SERCOM_ALT);
    ```

1. `loop` फंक्शन से पहले निम्नलिखित फंक्शन जोड़ें ताकि GPS डेटा को सीरियल मॉनिटर पर भेजा जा सके:

    ```cpp
    void printGPSData()
    {
        Serial.println(Serial3.readStringUntil('\n'));
    }
    ```

1. `loop` फंक्शन में, UART सीरियल पोर्ट से डेटा पढ़ने और इसे सीरियल मॉनिटर पर प्रिंट करने के लिए निम्नलिखित कोड जोड़ें:

    ```cpp
    while (Serial3.available() > 0)
    {
        printGPSData();
    }
    
    delay(1000);
    ```

    यह कोड UART सीरियल पोर्ट से डेटा पढ़ता है। `readStringUntil` फंक्शन एक टर्मिनेटर कैरेक्टर तक पढ़ता है, इस मामले में एक नई लाइन। यह एक पूरा NMEA वाक्य पढ़ेगा (NMEA वाक्य नई लाइन कैरेक्टर के साथ समाप्त होते हैं)। जब तक UART सीरियल पोर्ट से डेटा पढ़ा जा सकता है, इसे पढ़ा जाता है और `printGPSData` फंक्शन के माध्यम से सीरियल मॉनिटर पर भेजा जाता है। जब और डेटा पढ़ा नहीं जा सकता, तो `loop` 1 सेकंड (1,000ms) के लिए देरी करता है।

1. कोड को Wio Terminal पर बिल्ड और अपलोड करें।

1. अपलोड करने के बाद, आप सीरियल मॉनिटर का उपयोग करके GPS डेटा की निगरानी कर सकते हैं।

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

> 💁 आप इस कोड को [code-gps/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps/wio-terminal) फोल्डर में पा सकते हैं।

😀 आपका GPS सेंसर प्रोग्राम सफल रहा!

**अस्वीकरण**:  
यह दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) का उपयोग करके अनुवादित किया गया है। जबकि हम सटीकता सुनिश्चित करने का प्रयास करते हैं, कृपया ध्यान दें कि स्वचालित अनुवाद में त्रुटियां या अशुद्धियां हो सकती हैं। मूल भाषा में उपलब्ध मूल दस्तावेज़ को प्रामाणिक स्रोत माना जाना चाहिए। महत्वपूर्ण जानकारी के लिए, पेशेवर मानव अनुवाद की सिफारिश की जाती है। इस अनुवाद के उपयोग से उत्पन्न किसी भी गलतफहमी या गलत व्याख्या के लिए हम उत्तरदायी नहीं हैं।