# हार्डवेयर

IoT में **T** का मतलब **थिंग्स** है, जो उन डिवाइसों को दर्शाता है जो हमारे आसपास की दुनिया के साथ इंटरैक्ट करते हैं। प्रत्येक प्रोजेक्ट छात्रों और शौक़ीन लोगों के लिए उपलब्ध वास्तविक हार्डवेयर पर आधारित है। हमारे पास IoT हार्डवेयर के दो विकल्प हैं, जो व्यक्तिगत पसंद, प्रोग्रामिंग भाषा के ज्ञान या प्राथमिकताओं, सीखने के उद्देश्यों और उपलब्धता पर निर्भर करते हैं। हमने 'वर्चुअल हार्डवेयर' का एक संस्करण भी प्रदान किया है, जो उन लोगों के लिए है जिनके पास हार्डवेयर तक पहुंच नहीं है या जो खरीदारी करने से पहले अधिक सीखना चाहते हैं।

> 💁 असाइनमेंट पूरा करने के लिए आपको कोई IoT हार्डवेयर खरीदने की आवश्यकता नहीं है। आप सब कुछ वर्चुअल IoT हार्डवेयर का उपयोग करके कर सकते हैं।

भौतिक हार्डवेयर विकल्प Arduino या Raspberry Pi हैं। प्रत्येक प्लेटफ़ॉर्म के अपने फायदे और नुकसान हैं, और इन्हें शुरुआती पाठों में कवर किया गया है। यदि आपने अभी तक हार्डवेयर प्लेटफ़ॉर्म तय नहीं किया है, तो आप [पहले प्रोजेक्ट के दूसरे पाठ](./1-getting-started/lessons/2-deeper-dive/README.md) की समीक्षा कर सकते हैं ताकि यह तय कर सकें कि आप किस हार्डवेयर प्लेटफ़ॉर्म को सीखने में सबसे अधिक रुचि रखते हैं।

विशिष्ट हार्डवेयर को पाठों और असाइनमेंट की जटिलता को कम करने के लिए चुना गया है। हालांकि अन्य हार्डवेयर काम कर सकते हैं, हम यह गारंटी नहीं दे सकते कि आपके डिवाइस पर सभी असाइनमेंट अतिरिक्त हार्डवेयर के बिना समर्थित होंगे। उदाहरण के लिए, कई Arduino डिवाइसों में WiFi नहीं होता, जो क्लाउड से कनेक्ट करने के लिए आवश्यक है - Wio टर्मिनल को इसलिए चुना गया क्योंकि इसमें WiFi बिल्ट-इन है।

आपको कुछ गैर-तकनीकी वस्तुओं की भी आवश्यकता होगी, जैसे मिट्टी या गमले का पौधा, और फल या सब्जियां।

## किट खरीदें

![Seeed Studios का लोगो](../../translated_images/hi/seeed-logo.74732b6b482b6e8e.webp)

Seeed Studios ने बहुत ही उदारता से सभी हार्डवेयर को आसान खरीदारी किट के रूप में उपलब्ध कराया है:

### Arduino - Wio टर्मिनल

**[Seeed और Microsoft के साथ शुरुआती IoT - Wio टर्मिनल स्टार्टर किट](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)**

[![Wio टर्मिनल हार्डवेयर किट](../../translated_images/hi/wio-hardware-kit.4c70c48b85e4283a.webp)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)

### Raspberry Pi

**[Seeed और Microsoft के साथ शुरुआती IoT - Raspberry Pi 4 स्टार्टर किट](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)**

[![Raspberry Pi टर्मिनल हार्डवेयर किट](../../translated_images/hi/pi-hardware-kit.26dbadaedb7dd44c.webp)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)

## Arduino

Arduino के लिए सभी डिवाइस कोड C++ में हैं। सभी असाइनमेंट पूरा करने के लिए आपको निम्नलिखित की आवश्यकता होगी:

### Arduino हार्डवेयर

* [Wio टर्मिनल](https://www.seeedstudio.com/Wio-Terminal-p-4509.html)
* *वैकल्पिक* - USB-C केबल या USB-A से USB-C एडाप्टर। Wio टर्मिनल में USB-C पोर्ट है और यह USB-C से USB-A केबल के साथ आता है। यदि आपके पीसी या मैक में केवल USB-C पोर्ट हैं, तो आपको USB-C केबल या USB-A से USB-C एडाप्टर की आवश्यकता होगी।

### Arduino के लिए विशिष्ट सेंसर और एक्टुएटर्स

ये Wio टर्मिनल Arduino डिवाइस के लिए विशिष्ट हैं और Raspberry Pi के लिए प्रासंगिक नहीं हैं।

* [ArduCam Mini 2MP Plus - OV2640](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/)
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)
* [ब्रेडबोर्ड जम्पर वायर](https://www.seeedstudio.com/Breadboard-Jumper-Wire-Pack-241mm-200mm-160mm-117m-p-234.html)
* हेडफ़ोन या अन्य स्पीकर 3.5mm जैक के साथ, या JST स्पीकर जैसे:
  * [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
* 16GB या उससे कम की microSD कार्ड, साथ ही एक कनेक्टर ताकि आप SD कार्ड को अपने कंप्यूटर के साथ उपयोग कर सकें यदि आपके पास बिल्ट-इन नहीं है। **NOTE** - Wio टर्मिनल केवल 16GB तक के SD कार्ड को सपोर्ट करता है, यह उच्च क्षमता वाले कार्ड को सपोर्ट नहीं करता।

## Raspberry Pi

Raspberry Pi के लिए सभी डिवाइस कोड Python में हैं। सभी असाइनमेंट पूरा करने के लिए आपको निम्नलिखित की आवश्यकता होगी:

### Raspberry Pi हार्डवेयर

* [Raspberry Pi](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/)
  > 💁 Pi 2B और उसके बाद के संस्करण इन पाठों में असाइनमेंट के साथ काम करेंगे। यदि आप Pi पर सीधे VS Code चलाने की योजना बना रहे हैं, तो 2GB या उससे अधिक RAM वाला Pi 4 आवश्यक है। यदि आप Pi को रिमोट एक्सेस करने जा रहे हैं, तो कोई भी Pi 2B और उसके बाद का संस्करण काम करेगा।
* microSD कार्ड (आप Raspberry Pi किट प्राप्त कर सकते हैं जो microSD कार्ड के साथ आते हैं), साथ ही एक कनेक्टर ताकि आप SD कार्ड को अपने कंप्यूटर के साथ उपयोग कर सकें यदि आपके पास बिल्ट-इन नहीं है।
* USB पावर सप्लाई (आप Raspberry Pi 4 किट प्राप्त कर सकते हैं जो पावर सप्लाई के साथ आते हैं)। यदि आप Raspberry Pi 4 का उपयोग कर रहे हैं तो आपको USB-C पावर सप्लाई की आवश्यकता होगी, पहले के डिवाइसों के लिए micro-USB पावर सप्लाई की आवश्यकता होगी।

### Raspberry Pi के लिए विशिष्ट सेंसर और एक्टुएटर्स

ये Raspberry Pi के लिए विशिष्ट हैं और Arduino डिवाइस के लिए प्रासंगिक नहीं हैं।

* [Grove Pi बेस हैट](https://www.seeedstudio.com/Grove-Base-Hat-for-Raspberry-Pi.html)
* [Raspberry Pi कैमरा मॉड्यूल](https://www.raspberrypi.org/products/camera-module-v2/)
* माइक्रोफोन और स्पीकर:

  निम्नलिखित में से एक का उपयोग करें (या समकक्ष):
  * कोई भी USB माइक्रोफोन और कोई भी USB स्पीकर, या 3.5mm जैक केबल वाला स्पीकर, या HDMI ऑडियो आउटपुट का उपयोग करें यदि आपका Raspberry Pi स्पीकर वाले मॉनिटर या टीवी से जुड़ा है
  * बिल्ट-इन माइक्रोफोन वाला कोई भी USB हेडसेट
  * [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) के साथ
    * हेडफ़ोन या अन्य स्पीकर 3.5mm जैक के साथ, या JST स्पीकर जैसे:
    * [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
  * [USB स्पीकरफोन](https://www.amazon.com/USB-Speakerphone-Conference-Business-Microphones/dp/B07Q3D7F8S/ref=sr_1_1?dchild=1&keywords=m0&qid=1614647389&sr=8-1)
* [Grove लाइट सेंसर](https://www.seeedstudio.com/Grove-Light-Sensor-v1-2-LS06-S-phototransistor.html)
* [Grove बटन](https://www.seeedstudio.com/Grove-Button.html)

## सेंसर और एक्टुएटर्स

अधिकांश सेंसर और एक्टुएटर्स Arduino और Raspberry Pi दोनों लर्निंग पाथ्स में उपयोग किए जाते हैं:

* [Grove LED](https://www.seeedstudio.com/Grove-LED-Pack-p-4364.html) x 2
* [Grove ह्यूमिडिटी और टेम्परेचर सेंसर](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html)
* [Grove कैपेसिटिव सॉइल मॉइश्चर सेंसर](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html)
* [Grove रिले](https://www.seeedstudio.com/Grove-Relay.html)
* [Grove GPS (Air530)](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html)
* [Grove टाइम ऑफ फ्लाइट डिस्टेंस सेंसर](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html)

## वैकल्पिक हार्डवेयर

स्वचालित सिंचाई पर आधारित पाठ रिले का उपयोग करके काम करते हैं। एक विकल्प के रूप में, आप इस रिले को USB द्वारा संचालित पानी के पंप से कनेक्ट कर सकते हैं, नीचे सूचीबद्ध हार्डवेयर का उपयोग करके।

* [6V पानी का पंप](https://www.seeedstudio.com/6V-Mini-Water-Pump-p-1945.html)
* [USB टर्मिनल](https://www.adafruit.com/product/3628)
* सिलिकॉन पाइप
* लाल और काले तार
* छोटा फ्लैट-हेड स्क्रूड्राइवर

## वर्चुअल हार्डवेयर

वर्चुअल हार्डवेयर मार्ग सेंसर और एक्टुएटर्स के लिए सिमुलेटर प्रदान करेगा, जो Python में लागू किए गए हैं। आपके हार्डवेयर की उपलब्धता के आधार पर, आप इसे अपने सामान्य विकास डिवाइस, जैसे Mac, PC, या Raspberry Pi पर चला सकते हैं और केवल उस हार्डवेयर का सिमुलेशन कर सकते हैं जो आपके पास नहीं है। उदाहरण के लिए, यदि आपके पास Raspberry Pi कैमरा है लेकिन Grove सेंसर नहीं हैं, तो आप अपने Pi पर वर्चुअल डिवाइस कोड चला सकते हैं और Grove सेंसर का सिमुलेशन कर सकते हैं, लेकिन भौतिक कैमरा का उपयोग कर सकते हैं।

वर्चुअल हार्डवेयर [CounterFit प्रोजेक्ट](https://github.com/CounterFit-IoT/CounterFit) का उपयोग करेगा।

इन पाठों को पूरा करने के लिए आपके पास एक वेब कैमरा, माइक्रोफोन और ऑडियो आउटपुट जैसे स्पीकर या हेडफ़ोन होना चाहिए। ये बिल्ट-इन या बाहरी हो सकते हैं, और इन्हें आपके ऑपरेटिंग सिस्टम के साथ काम करने और सभी एप्लिकेशन से उपयोग के लिए कॉन्फ़िगर किया जाना चाहिए।

**अस्वीकरण**:  
यह दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) का उपयोग करके अनुवादित किया गया है। जबकि हम सटीकता सुनिश्चित करने का प्रयास करते हैं, कृपया ध्यान दें कि स्वचालित अनुवाद में त्रुटियां या अशुद्धियां हो सकती हैं। मूल भाषा में उपलब्ध मूल दस्तावेज़ को प्रामाणिक स्रोत माना जाना चाहिए। महत्वपूर्ण जानकारी के लिए, पेशेवर मानव अनुवाद की सिफारिश की जाती है। इस अनुवाद के उपयोग से उत्पन्न किसी भी गलतफहमी या गलत व्याख्या के लिए हम उत्तरदायी नहीं हैं।