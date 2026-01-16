<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a4f0c166010e31fd7b6ca20bc88dec6d",
  "translation_date": "2025-08-27T13:10:23+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md",
  "language_code": "mr"
}
-->
# Wio Terminal

[Seeed Studios चा Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html) हा Arduino-सुसंगत मायक्रोकंट्रोलर आहे, ज्यामध्ये WiFi, काही सेन्सर्स आणि अ‍ॅक्ट्युएटर्स अंगभूत आहेत. तसेच, [Grove](https://www.seeedstudio.com/category/Grove-c-1003.html) नावाच्या हार्डवेअर इकोसिस्टमचा वापर करून अधिक सेन्सर्स आणि अ‍ॅक्ट्युएटर्स जोडण्यासाठी पोर्ट्स उपलब्ध आहेत.

![Seeed Studios चा Wio Terminal](../../../../../translated_images/mr/wio-terminal.b8299ee16587db9a.png)

## सेटअप

तुमच्या Wio Terminal चा वापर करण्यासाठी, तुम्हाला तुमच्या संगणकावर काही मोफत सॉफ्टवेअर इन्स्टॉल करावे लागेल. तसेच, Wio Terminal ला WiFi शी कनेक्ट करण्यापूर्वी त्याचे फर्मवेअर अपडेट करणे आवश्यक आहे.

### कार्य - सेटअप

आवश्यक सॉफ्टवेअर इन्स्टॉल करा आणि फर्मवेअर अपडेट करा.

1. Visual Studio Code (VS Code) इन्स्टॉल करा. हे संपादक तुम्ही C/C++ मध्ये तुमचा डिव्हाइस कोड लिहिण्यासाठी वापरणार आहात. VS Code इन्स्टॉल करण्यासाठी [VS Code दस्तऐवज](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) पहा.

    > 💁 Arduino डेव्हलपमेंटसाठी आणखी एक लोकप्रिय IDE म्हणजे [Arduino IDE](https://www.arduino.cc/en/software). जर तुम्हाला आधीच या टूलची सवय असेल, तर तुम्ही VS Code आणि PlatformIO च्या ऐवजी याचा वापर करू शकता. मात्र, या धड्यांमध्ये VS Code चा वापर करून दिलेल्या सूचना असतील.

1. VS Code PlatformIO विस्तार इन्स्टॉल करा. हा VS Code साठी एक विस्तार आहे, जो C/C++ मध्ये मायक्रोकंट्रोलर्स प्रोग्राम करण्यासाठी उपयुक्त आहे. VS Code मध्ये हा विस्तार कसा इन्स्टॉल करायचा यासाठी [PlatformIO विस्तार दस्तऐवज](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=platformio.platformio-ide) पहा. हा विस्तार Microsoft C/C++ विस्तारावर अवलंबून आहे, जो PlatformIO इन्स्टॉल करताना आपोआप इन्स्टॉल होतो.

1. तुमचा Wio Terminal तुमच्या संगणकाला जोडा. Wio Terminal च्या खालच्या बाजूला USB-C पोर्ट आहे, जो USB पोर्टद्वारे संगणकाला जोडला जातो. Wio Terminal सोबत USB-C ते USB-A केबल येते. जर तुमच्या संगणकावर फक्त USB-C पोर्ट्स असतील, तर तुम्हाला USB-C केबल किंवा USB-A ते USB-C अडॅप्टरची गरज भासेल.

1. [Wio Terminal Wiki WiFi Overview दस्तऐवज](https://wiki.seeedstudio.com/Wio-Terminal-Network-Overview/) मधील सूचना पाळा आणि तुमचा Wio Terminal सेटअप करा व फर्मवेअर अपडेट करा.

## Hello World

नवीन प्रोग्रामिंग भाषा किंवा तंत्रज्ञान सुरू करताना पारंपरिकपणे 'Hello World' अ‍ॅप्लिकेशन तयार केले जाते - एक लहान अ‍ॅप्लिकेशन जे `"Hello World"` सारखा मजकूर आउटपुट करते, ज्यामुळे सर्व टूल्स योग्यरित्या कॉन्फिगर झाले आहेत हे सुनिश्चित होते.

Wio Terminal साठी Hello World अ‍ॅप्लिकेशन तुम्हाला Visual Studio Code, PlatformIO आणि मायक्रोकंट्रोलर डेव्हलपमेंटसाठी सेटअप योग्यरित्या झाले आहे याची खात्री देईल.

### PlatformIO प्रोजेक्ट तयार करा

पहिल्या टप्प्यात, Wio Terminal साठी PlatformIO कॉन्फिगर केलेला नवीन प्रोजेक्ट तयार करा.

#### कार्य - PlatformIO प्रोजेक्ट तयार करा

PlatformIO प्रोजेक्ट तयार करा.

1. Wio Terminal तुमच्या संगणकाला जोडा

1. VS Code सुरू करा

1. PlatformIO आयकॉन साइड मेनू बारवर दिसेल:

    ![Platform IO मेनू पर्याय](../../../../../translated_images/mr/vscode-platformio-menu.297be26b9733e5c4.png)

    हा मेनू आयटम निवडा, नंतर *PIO Home -> Open* निवडा

    ![Platform IO ओपन पर्याय](../../../../../translated_images/mr/vscode-platformio-home-open.3f9a41bfd3f4da1c.png)

1. वेलकम स्क्रीनवरून **+ New Project** बटण निवडा

    ![नवीन प्रोजेक्ट बटण](../../../../../translated_images/mr/vscode-platformio-welcome-new-button.ba6fc8a4c7b78cc8.png)

1. *Project Wizard* मध्ये प्रोजेक्ट कॉन्फिगर करा:

    1. तुमच्या प्रोजेक्टचे नाव `nightlight` ठेवा

    1. *Board* ड्रॉपडाउनमधून `WIO` टाइप करा, बोर्ड्स फिल्टर करा आणि *Seeeduino Wio Terminal* निवडा

    1. *Framework* `Arduino` म्हणून ठेवा

    1. *Use default location* चेकबॉक्स चेक केलेला ठेवा किंवा अनचेक करून प्रोजेक्टसाठी स्थान निवडा

    1. **Finish** बटण निवडा

    ![पूर्ण प्रोजेक्ट विजार्ड](../../../../../translated_images/mr/vscode-platformio-nightlight-project-wizard.5c64db4da6037420.png)

    PlatformIO ला Wio Terminal साठी कोड कंपाइल करण्यासाठी आवश्यक घटक डाउनलोड करावे लागतील आणि तुमचा प्रोजेक्ट तयार करावा लागेल. यासाठी काही मिनिटे लागू शकतात.

### PlatformIO प्रोजेक्ट तपासा

VS Code एक्सप्लोररमध्ये PlatformIO विजार्डने तयार केलेल्या फोल्डर्स आणि फाइल्स दिसतील.

#### फोल्डर्स

* `.pio` - या फोल्डरमध्ये PlatformIO साठी आवश्यक तात्पुरती डेटा असतो, जसे की लायब्ररी किंवा कंपाइल केलेला कोड. हा फोल्डर डिलीट केल्यास आपोआप पुन्हा तयार होतो, आणि जर तुम्ही तुमचा प्रोजेक्ट GitHub सारख्या साइट्सवर शेअर करत असाल, तर हा फोल्डर सोर्स कोड कंट्रोलमध्ये जोडण्याची गरज नाही.
* `.vscode` - या फोल्डरमध्ये PlatformIO आणि VS Code साठी वापरलेली कॉन्फिगरेशन असते. हा फोल्डर डिलीट केल्यास आपोआप पुन्हा तयार होतो, आणि जर तुम्ही तुमचा प्रोजेक्ट GitHub सारख्या साइट्सवर शेअर करत असाल, तर हा फोल्डर सोर्स कोड कंट्रोलमध्ये जोडण्याची गरज नाही.
* `include` - या फोल्डरमध्ये बाह्य हेडर फाइल्स असतात, ज्या तुमच्या कोडमध्ये अतिरिक्त लायब्ररी जोडण्यासाठी आवश्यक असतात. या धड्यांमध्ये तुम्ही हा फोल्डर वापरणार नाही.
* `lib` - या फोल्डरमध्ये बाह्य लायब्ररी असतात, ज्या तुमच्या कोडमधून कॉल केल्या जातात. या धड्यांमध्ये तुम्ही हा फोल्डर वापरणार नाही.
* `src` - या फोल्डरमध्ये तुमच्या अ‍ॅप्लिकेशनसाठी मुख्य सोर्स कोड असतो. सुरुवातीला, यात एकच फाइल असेल - `main.cpp`.
* `test` - या फोल्डरमध्ये तुमच्या कोडसाठी युनिट टेस्ट्स ठेवता येतात.

#### फाइल्स

* `main.cpp` - `src` फोल्डरमधील ही फाइल तुमच्या अ‍ॅप्लिकेशनसाठी एंट्री पॉइंट आहे. ही फाइल उघडा, आणि यात खालील कोड असेल:

    ```cpp
    #include <Arduino.h>
    
    void setup() {
      // put your setup code here, to run once:
    }
    
    void loop() {
      // put your main code here, to run repeatedly:
    }
    ```

    डिव्हाइस सुरू झाल्यावर, Arduino फ्रेमवर्क `setup` फंक्शन एकदाच चालवते, आणि नंतर `loop` फंक्शन सतत चालवत राहते, जोपर्यंत डिव्हाइस बंद होत नाही.

* `.gitignore` - ही फाइल Git सोर्स कोड कंट्रोलमध्ये जोडताना दुर्लक्षित करावयाच्या फाइल्स आणि डिरेक्टरीजची यादी देते, जसे GitHub वर अपलोड करताना.

* `platformio.ini` - ही फाइल तुमच्या डिव्हाइस आणि अ‍ॅपसाठी कॉन्फिगरेशन ठेवते. ही फाइल उघडा, आणि यात खालील कोड असेल:

    ```ini
    [env:seeed_wio_terminal]
    platform = atmelsam
    board = seeed_wio_terminal
    framework = arduino
    ```

    `[env:seeed_wio_terminal]` विभाग Wio Terminal साठी कॉन्फिगरेशन ठेवतो. तुमच्या कोडसाठी अनेक `env` विभाग असू शकतात, ज्यामुळे तुमचा कोड अनेक बोर्ड्ससाठी कंपाइल होऊ शकतो.

    इतर मूल्ये प्रोजेक्ट विजार्डमधील कॉन्फिगरेशनशी जुळतात:

  * `platform = atmelsam` Wio Terminal च्या हार्डवेअरला परिभाषित करते (ATSAMD51-आधारित मायक्रोकंट्रोलर)
  * `board = seeed_wio_terminal` मायक्रोकंट्रोलर बोर्डचा प्रकार परिभाषित करते (Wio Terminal)
  * `framework = arduino` प्रोजेक्ट Arduino फ्रेमवर्क वापरत असल्याचे परिभाषित करते.

### Hello World अ‍ॅप लिहा

आता तुम्ही Hello World अ‍ॅप लिहिण्यासाठी तयार आहात.

#### कार्य - Hello World अ‍ॅप लिहा

Hello World अ‍ॅप लिहा.

1. VS Code मध्ये `main.cpp` फाइल उघडा

1. कोड खालीलप्रमाणे बदला:

    ```cpp
    #include <Arduino.h>

    void setup()
    {
        Serial.begin(9600);

        while (!Serial)
            ; // Wait for Serial to be ready
    
        delay(1000);
    }
    
    void loop()
    {
        Serial.println("Hello World");
        delay(5000);
    }
    ```

    `setup` फंक्शन सीरियल पोर्टशी कनेक्शन सुरू करते - या प्रकरणात, USB पोर्ट जो Wio Terminal ला तुमच्या संगणकाशी जोडतो. पॅरामीटर `9600` हा [baud rate](https://wikipedia.org/wiki/Symbol_rate) (सिंबॉल रेट) किंवा सीरियल पोर्टवर डेटा पाठवण्याचा वेग आहे, जो सेकंदाला बिट्समध्ये मोजला जातो. ही सेटिंग 9,600 बिट्स (0s आणि 1s) प्रति सेकंद पाठवते. त्यानंतर, सीरियल पोर्ट तयार होईपर्यंत थांबते.

    `loop` फंक्शन सीरियल पोर्टवर `Hello World!` मजकूर पाठवते, ज्यामध्ये `Hello World!` अक्षरे आणि नवीन ओळ अक्षर असते. त्यानंतर, 5,000 मिलिसेकंद किंवा 5 सेकंद झोपते. `loop` संपल्यानंतर, तो पुन्हा चालतो, आणि पुन्हा, जोपर्यंत मायक्रोकंट्रोलर चालू असतो.

1. तुमचा Wio Terminal अपलोड मोडमध्ये ठेवा. डिव्हाइसवर नवीन कोड अपलोड करताना तुम्हाला हे प्रत्येक वेळी करावे लागेल:

    1. पॉवर स्विच दोनदा पटकन खाली खेचा - तो प्रत्येक वेळी ऑन स्थितीत परत येईल.

    1. USB पोर्टच्या उजव्या बाजूला असलेला निळा स्टेटस LED तपासा. तो हलक्या प्रकाशात चमकत असेल.
    
    [![Wio Terminal ला अपलोड मोडमध्ये कसे ठेवायचे याचा व्हिडिओ](https://img.youtube.com/vi/LeKU_7zLRrQ/0.jpg)](https://youtu.be/LeKU_7zLRrQ)
    
    हे कसे करायचे याचा व्हिडिओ पाहण्यासाठी वरील प्रतिमेवर क्लिक करा.

1. कोड Wio Terminal वर बिल्ड आणि अपलोड करा

    1. VS Code कमांड पॅलेट उघडा

    1. `PlatformIO Upload` टाइप करा, अपलोड पर्याय शोधा, आणि *PlatformIO: Upload* निवडा

        ![PlatformIO अपलोड पर्याय कमांड पॅलेटमध्ये](../../../../../translated_images/mr/vscode-platformio-upload-command-palette.9e0f49cf80d1f1c3.png)

        PlatformIO आवश्यक असल्यास कोड आपोआप बिल्ड करेल आणि नंतर अपलोड करेल.

    1. कोड कंपाइल होईल आणि Wio Terminal वर अपलोड होईल

        > 💁 जर तुम्ही macOS वापरत असाल, तर *DISK NOT EJECTED PROPERLY* बद्दल सूचना दिसेल. कारण Wio Terminal फ्लॅशिंग प्रक्रियेचा भाग म्हणून ड्राइव्ह म्हणून माउंट केला जातो, आणि संकलित कोड डिव्हाइसवर लिहिले जाताना डिस्कनेक्ट होतो. तुम्ही ही सूचना दुर्लक्षित करू शकता.

    ⚠️ जर तुम्हाला अपलोड पोर्ट उपलब्ध नसल्याबद्दल त्रुटी मिळाल्या, तर प्रथम खात्री करा की Wio Terminal तुमच्या संगणकाशी जोडलेला आहे, स्क्रीनच्या डाव्या बाजूला असलेल्या स्विचचा वापर करून चालू आहे, आणि अपलोड मोडमध्ये सेट केलेला आहे. खालचा हिरवा दिवा चालू असावा, आणि निळा दिवा हलक्या प्रकाशात चमकत असावा. जर तुम्हाला अजूनही त्रुटी मिळाल्या, तर ऑन/ऑफ स्विच दोनदा पटकन खाली खेचा, Wio Terminal ला अपलोड मोडमध्ये जबरदस्तीने ठेवा आणि पुन्हा अपलोड करण्याचा प्रयत्न करा.

PlatformIO मध्ये एक Serial Monitor आहे, जो Wio Terminal कडून USB केबलद्वारे पाठवलेला डेटा मॉनिटर करू शकतो. यामुळे `Serial.println("Hello World");` कमांडने पाठवलेला डेटा मॉनिटर करता येतो.

1. VS Code कमांड पॅलेट उघडा

1. `PlatformIO Serial` टाइप करा, Serial Monitor पर्याय शोधा, आणि *PlatformIO: Serial Monitor* निवडा

    ![PlatformIO Serial Monitor पर्याय कमांड पॅलेटमध्ये](../../../../../translated_images/mr/vscode-platformio-serial-monitor-command-palette.b348ec841b8a1c14.png)

    एक नवीन टर्मिनल उघडेल, आणि सीरियल पोर्टवरून पाठवलेला डेटा या टर्मिनलमध्ये प्रवाहित होईल:

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Hello World
    Hello World
    ```

    `Hello World` प्रत्येक 5 सेकंदांनी सीरियल मॉनिटरवर प्रिंट होईल.

> 💁 तुम्हाला हा कोड [code/wio-terminal](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/wio-terminal) फोल्डरमध्ये सापडेल.

😀 तुमचा 'Hello World' प्रोग्राम यशस्वी झाला!

---

**अस्वीकरण**:  
हा दस्तऐवज AI भाषांतर सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) वापरून भाषांतरित करण्यात आला आहे. आम्ही अचूकतेसाठी प्रयत्नशील असलो तरी कृपया लक्षात ठेवा की स्वयंचलित भाषांतरांमध्ये त्रुटी किंवा अचूकतेचा अभाव असू शकतो. मूळ भाषेतील दस्तऐवज हा अधिकृत स्रोत मानला जावा. महत्त्वाच्या माहितीसाठी व्यावसायिक मानवी भाषांतराची शिफारस केली जाते. या भाषांतराचा वापर करून उद्भवलेल्या कोणत्याही गैरसमज किंवा चुकीच्या अर्थासाठी आम्ही जबाबदार राहणार नाही.