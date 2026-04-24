# मातीतील आर्द्रता मोजा - Wio Terminal

या धड्याच्या भागात, तुम्ही Wio Terminal मध्ये एक capacitive मातीतील आर्द्रता सेन्सर जोडाल आणि त्यातून मूल्ये वाचाल.

## हार्डवेअर

Wio Terminal साठी एक capacitive मातीतील आर्द्रता सेन्सर आवश्यक आहे.

तुम्ही वापरणार असलेला सेन्सर [Capacitive Soil Moisture Sensor](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html) आहे, जो मातीतील आर्द्रता मोजतो. तो मातीच्या capacitance शोधतो, जी मालमत्ता मातीतील आर्द्रता बदलल्यावर बदलते. मातीतील आर्द्रता वाढल्यावर व्होल्टेज कमी होते.

हा एक analog सेन्सर आहे, जो Wio Terminal च्या analog पिन्सला जोडतो आणि ऑनबोर्ड ADC वापरून 0-1,023 पर्यंत मूल्य तयार करतो.

### मातीतील आर्द्रता सेन्सर जोडा

Grove मातीतील आर्द्रता सेन्सर Wio Terminal च्या कॉन्फिगर करण्यायोग्य analog/digital पोर्टला जोडता येतो.

#### कार्य - मातीतील आर्द्रता सेन्सर जोडा

मातीतील आर्द्रता सेन्सर जोडा.

![Grove मातीतील आर्द्रता सेन्सर](../../../../../translated_images/mr/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78b.webp)

1. Grove केबलचा एक टोक मातीतील आर्द्रता सेन्सरच्या सॉकेटमध्ये घाला. ती फक्त एका बाजूने जाईल.

1. Wio Terminal तुमच्या संगणकापासून किंवा इतर पॉवर सप्लायपासून डिस्कनेक्ट केलेला असताना, Grove केबलचे दुसरे टोक Wio Terminal च्या स्क्रीनकडे पाहताना उजव्या बाजूच्या Grove सॉकेटमध्ये जोडा. हे पॉवर बटणापासून सर्वात दूर असलेले सॉकेट आहे.

![Grove मातीतील आर्द्रता सेन्सर उजव्या सॉकेटला जोडलेला](../../../../../translated_images/mr/wio-soil-moisture-sensor.46919b61c3f6cb74.webp)

1. मातीतील आर्द्रता सेन्सर मातीमध्ये घाला. त्यावर 'highest position line' आहे - सेन्सरवर पांढऱ्या रंगाची रेषा. सेन्सर त्या रेषेपर्यंत पण त्यापलीकडे नाही असे घाला.

![मातीतील आर्द्रता सेन्सर मातीमध्ये](../../../../../translated_images/mr/soil-moisture-sensor-in-soil.bfad91002bda5e96.webp)

1. आता तुम्ही Wio Terminal तुमच्या संगणकाला जोडू शकता.

## मातीतील आर्द्रता सेन्सर प्रोग्राम करा

आता Wio Terminal जोडलेल्या मातीतील आर्द्रता सेन्सर वापरण्यासाठी प्रोग्राम केला जाऊ शकतो.

### कार्य - मातीतील आर्द्रता सेन्सर प्रोग्राम करा

डिव्हाइस प्रोग्राम करा.

1. PlatformIO वापरून एक नवीन Wio Terminal प्रोजेक्ट तयार करा. या प्रोजेक्टचे नाव `soil-moisture-sensor` ठेवा. `setup` फंक्शनमध्ये serial पोर्ट कॉन्फिगर करण्यासाठी कोड जोडा.

    > ⚠️ [प्रोजेक्ट 1, धडा 1 मधील PlatformIO प्रोजेक्ट तयार करण्याच्या सूचना आवश्यक असल्यास पाहा](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project).

1. या सेन्सरसाठी कोणतेही लायब्ररी नाही, त्यामुळे तुम्ही analog पिनवरून Arduino च्या [`analogRead`](https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/) फंक्शन वापरून वाचू शकता. analog पिन इनपुटसाठी कॉन्फिगर करा जेणेकरून त्यावरून मूल्ये वाचता येतील. `setup` फंक्शनमध्ये खालील कोड जोडा.

    ```cpp
    pinMode(A0, INPUT);
    ```

    हे `A0` पिन, जो analog/digital पिन आहे, इनपुट पिन म्हणून सेट करते ज्यावरून व्होल्टेज वाचता येईल.

1. `loop` फंक्शनमध्ये खालील कोड जोडा जेणेकरून या पिनवरून व्होल्टेज वाचता येईल:

    ```cpp
    int soil_moisture = analogRead(A0);
    ```

1. या कोडखाली खालील कोड जोडा जेणेकरून मूल्य serial पोर्टवर प्रिंट करता येईल:

    ```cpp
    Serial.print("Soil Moisture: ");
    Serial.println(soil_moisture);
    ```

1. शेवटी 10 सेकंदाचा delay जोडा:

    ```cpp
    delay(10000);
    ```

1. कोड तयार करा आणि Wio Terminal वर अपलोड करा.

    > ⚠️ [प्रोजेक्ट 1, धडा 1 मधील PlatformIO प्रोजेक्ट तयार करण्याच्या सूचना आवश्यक असल्यास पाहा](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app).

1. एकदा अपलोड झाल्यावर, तुम्ही serial monitor वापरून मातीतील आर्द्रता पाहू शकता. मातीमध्ये पाणी घाला किंवा सेन्सर मातीमधून काढा आणि मूल्य बदलताना पाहा.

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

    वरील उदाहरण output मध्ये, तुम्ही पाणी घातल्यावर व्होल्टेज कमी होताना पाहू शकता.

> 💁 तुम्ही हा कोड [code/wio-terminal](../../../../../2-farm/lessons/2-detect-soil-moisture/code/wio-terminal) फोल्डरमध्ये शोधू शकता.

😀 तुमचा मातीतील आर्द्रता सेन्सर प्रोग्राम यशस्वी झाला!

---

**अस्वीकरण**:  
हा दस्तऐवज AI भाषांतर सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) वापरून भाषांतरित करण्यात आला आहे. आम्ही अचूकतेसाठी प्रयत्नशील असलो तरी, कृपया लक्षात ठेवा की स्वयंचलित भाषांतरांमध्ये त्रुटी किंवा अचूकतेचा अभाव असू शकतो. मूळ भाषेतील दस्तऐवज हा अधिकृत स्रोत मानला जावा. महत्त्वाच्या माहितीसाठी, व्यावसायिक मानवी भाषांतराची शिफारस केली जाते. या भाषांतराचा वापर करून उद्भवलेल्या कोणत्याही गैरसमज किंवा चुकीच्या अर्थासाठी आम्ही जबाबदार राहणार नाही.