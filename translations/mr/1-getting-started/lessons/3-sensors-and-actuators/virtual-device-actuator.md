<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9c640f93263fd9adbfda920739e09feb",
  "translation_date": "2025-08-27T12:48:58+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/virtual-device-actuator.md",
  "language_code": "mr"
}
-->
# नाईटलाइट तयार करा - व्हर्च्युअल IoT हार्डवेअर

या धड्याच्या या भागात, तुम्ही तुमच्या व्हर्च्युअल IoT डिव्हाइसला एक LED जोडाल आणि त्याचा वापर करून नाईटलाइट तयार कराल.

## व्हर्च्युअल हार्डवेअर

नाईटलाइटसाठी CounterFit अॅपमध्ये तयार केलेला एक actuator आवश्यक आहे.

हा actuator म्हणजे **LED**. एका भौतिक IoT डिव्हाइसमध्ये, तो एक [प्रकाश उत्सर्जित करणारा डायोड](https://wikipedia.org/wiki/Light-emitting_diode) असेल, जो त्यामधून विद्युत प्रवाह गेल्यावर प्रकाश उत्सर्जित करतो. हा एक डिजिटल actuator आहे ज्याला दोन स्थिती असतात - चालू (on) आणि बंद (off). 1 मूल्य पाठवल्यास LED चालू होतो, आणि 0 पाठवल्यास बंद होतो.

नाईटलाइट लॉजिकचे स्यूडो-कोड खालीलप्रमाणे आहे:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### CounterFit मध्ये actuator जोडा

व्हर्च्युअल LED वापरण्यासाठी, तुम्हाला तो CounterFit अॅपमध्ये जोडावा लागेल.

#### कार्य - CounterFit मध्ये actuator जोडा

CounterFit अॅपमध्ये LED जोडा.

1. या असाइनमेंटच्या मागील भागातून CounterFit वेब अॅप चालू असल्याची खात्री करा. जर ते चालू नसेल, तर ते सुरू करा आणि लाइट सेन्सर पुन्हा जोडा.

1. LED तयार करा:

    1. *Actuator* पॅनमधील *Create actuator* बॉक्समध्ये, *Actuator type* ड्रॉपडाउन करा आणि *LED* निवडा.

    1. *Pin* ला *5* वर सेट करा.

    1. **Add** बटण निवडा, जेणेकरून Pin 5 वर LED तयार होईल.

    ![LED सेटिंग्ज](../../../../../translated_images/counterfit-create-led.ba9db1c9b8c622a635d6dfae5cdc4e70c2b250635bd4f0601c6cf0bd22b7ba46.mr.png)

    LED तयार होईल आणि actuator यादीत दिसेल.

    ![तयार केलेला LED](../../../../../translated_images/counterfit-led.c0ab02de6d256ad84d9bad4d67a7faa709f0ea83e410cfe9b5561ef0cef30b1c.mr.png)

    LED तयार झाल्यावर, तुम्ही *Color* पिकर वापरून त्याचा रंग बदलू शकता. रंग निवडल्यानंतर **Set** बटण निवडा.

### नाईटलाइट प्रोग्राम करा

आता CounterFit लाइट सेन्सर आणि LED वापरून नाईटलाइट प्रोग्राम केला जाऊ शकतो.

#### कार्य - नाईटलाइट प्रोग्राम करा

नाईटलाइट प्रोग्राम करा.

1. या असाइनमेंटच्या मागील भागात तयार केलेला नाईटलाइट प्रोजेक्ट VS Code मध्ये उघडा. टर्मिनल बंद करा आणि पुन्हा तयार करा, जेणेकरून ते व्हर्च्युअल एन्व्हायर्नमेंट वापरून चालेल.

1. `app.py` फाइल उघडा.

1. आवश्यक लायब्ररी आयात करण्यासाठी `app.py` फाइलमध्ये खालील कोड जोडा. हा कोड इतर `import` ओळींच्या खाली जोडा.

    ```python
    from counterfit_shims_grove.grove_led import GroveLed
    ```

    `from counterfit_shims_grove.grove_led import GroveLed` ही ओळ CounterFit Grove shim Python लायब्ररीमधून `GroveLed` आयात करते. या लायब्ररीमध्ये CounterFit अॅपमध्ये तयार केलेल्या LED शी संवाद साधण्यासाठी कोड आहे.

1. `light_sensor` डिक्लरेशननंतर खालील कोड जोडा, ज्यामुळे LED व्यवस्थापित करणाऱ्या वर्गाचे उदाहरण तयार होईल:

    ```python
    led = GroveLed(5)
    ```

    `led = GroveLed(5)` ही ओळ `GroveLed` वर्गाचे उदाहरण तयार करते, जे Pin **5** शी जोडलेले आहे - CounterFit Grove Pin ज्यावर LED जोडलेला आहे.

1. `while` लूपच्या आत, `time.sleep` च्या आधी, लाइट लेव्हल तपासण्यासाठी आणि LED चालू किंवा बंद करण्यासाठी एक चेक जोडा:

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    हा कोड `light` मूल्य तपासतो. जर हे 300 पेक्षा कमी असेल, तर `GroveLed` वर्गाच्या `on` पद्धतीला कॉल करतो, ज्यामुळे LED चालू होतो. जर लाइट मूल्य 300 किंवा त्याहून जास्त असेल, तर `off` पद्धतीला कॉल करतो, ज्यामुळे LED बंद होतो.

    > 💁 हा कोड `print('Light level:', light)` ओळीच्या समान स्तरावर इंडेंट केलेला असावा, जेणेकरून तो `while` लूपच्या आत असेल!

1. VS Code टर्मिनलमधून, तुमचा Python अॅप चालवण्यासाठी खालील कमांड चालवा:

    ```sh
    python3 app.py
    ```

    लाइट मूल्ये कन्सोलवर आउटपुट होतील.

    ```output
    (.venv) ➜  GroveTest python3 app.py 
    Light level: 143
    Light level: 244
    Light level: 246
    Light level: 253
    ```

1. *Value* किंवा *Random* सेटिंग्ज बदला, जेणेकरून लाइट लेव्हल 300 च्या वर आणि खाली जाईल. LED चालू आणि बंद होईल.

![CounterFit अॅपमधील LED लाइट लेव्हल बदलल्यावर चालू आणि बंद होत आहे](../../../../../images/virtual-device-running-assignment-1-1.gif)

> 💁 तुम्हाला हा कोड [code-actuator/virtual-device](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/virtual-device) फोल्डरमध्ये सापडेल.

😀 तुमचा नाईटलाइट प्रोग्राम यशस्वी झाला!

---

**अस्वीकरण**:  
हा दस्तऐवज AI भाषांतर सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) वापरून भाषांतरित करण्यात आला आहे. आम्ही अचूकतेसाठी प्रयत्नशील असलो तरी कृपया लक्षात ठेवा की स्वयंचलित भाषांतरांमध्ये त्रुटी किंवा अचूकतेचा अभाव असू शकतो. मूळ भाषेतील दस्तऐवज हा अधिकृत स्रोत मानला जावा. महत्त्वाच्या माहितीसाठी व्यावसायिक मानवी भाषांतराची शिफारस केली जाते. या भाषांतराचा वापर करून निर्माण होणाऱ्या कोणत्याही गैरसमज किंवा चुकीच्या अर्थासाठी आम्ही जबाबदार राहणार नाही.