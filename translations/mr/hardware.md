# हार्डवेअर

IoT मधील **T** म्हणजे **थिंग्स**, ज्याचा अर्थ आहे की हे उपकरणे आपल्या आजूबाजूच्या जगाशी संवाद साधतात. प्रत्येक प्रकल्प विद्यार्थ्यांसाठी आणि हौशींसाठी उपलब्ध असलेल्या वास्तविक हार्डवेअरवर आधारित आहे. वैयक्तिक आवड, प्रोग्रामिंग भाषा ज्ञान किंवा प्राधान्य, शिकण्याची उद्दिष्टे आणि उपलब्धता यावर आधारित IoT हार्डवेअरचे दोन पर्याय आहेत. ज्यांना हार्डवेअर उपलब्ध नाही किंवा खरेदी करण्यापूर्वी अधिक शिकायचे आहे त्यांच्यासाठी 'व्हर्च्युअल हार्डवेअर' पर्याय देखील दिला आहे.

> 💁 तुम्हाला असाइनमेंट पूर्ण करण्यासाठी IoT हार्डवेअर खरेदी करण्याची गरज नाही. तुम्ही सर्वकाही व्हर्च्युअल IoT हार्डवेअर वापरून करू शकता.

भौतिक हार्डवेअर पर्यायांमध्ये Arduino किंवा Raspberry Pi आहेत. प्रत्येक प्लॅटफॉर्मचे स्वतःचे फायदे आणि तोटे आहेत, आणि हे सर्व सुरुवातीच्या धड्यांपैकी एका मध्ये समाविष्ट केले आहेत. जर तुम्ही हार्डवेअर प्लॅटफॉर्म निवडले नसेल, तर तुम्ही [पहिल्या प्रकल्पाचा दुसरा धडा](./1-getting-started/lessons/2-deeper-dive/README.md) पाहून तुम्हाला शिकण्यात सर्वाधिक रस असलेल्या हार्डवेअर प्लॅटफॉर्मचा निर्णय घेऊ शकता.

विशिष्ट हार्डवेअर निवडले गेले आहे जेणेकरून धडे आणि असाइनमेंट्सची गुंतागुंत कमी होईल. इतर हार्डवेअर कार्य करू शकते, परंतु अतिरिक्त हार्डवेअरशिवाय तुमच्या उपकरणावर सर्व असाइनमेंट्स समर्थित असतील याची हमी आम्ही देऊ शकत नाही. उदाहरणार्थ, बऱ्याच Arduino उपकरणांमध्ये WiFi नसते, जे क्लाउडशी कनेक्ट होण्यासाठी आवश्यक आहे - Wio टर्मिनल निवडले गेले कारण त्यात WiFi अंगभूत आहे.

तुम्हाला काही तांत्रिक नसलेली वस्तू देखील लागतील, जसे की माती किंवा कुंडीत लावलेले झाड, आणि फळे किंवा भाज्या.

## किट्स खरेदी करा

![Seeed Studios लोगो](../../translated_images/mr/seeed-logo.74732b6b482b6e8e.webp)

Seeed Studios ने सर्व हार्डवेअर सोप्या पद्धतीने खरेदी करण्यासाठी किट्स उपलब्ध करून दिल्या आहेत:

### Arduino - Wio टर्मिनल

**[Seeed आणि Microsoft सोबत IoT शिकण्यासाठी - Wio टर्मिनल स्टार्टर किट](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)**

[![Wio टर्मिनल हार्डवेअर किट](../../translated_images/mr/wio-hardware-kit.4c70c48b85e4283a.webp)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)

### Raspberry Pi

**[Seeed आणि Microsoft सोबत IoT शिकण्यासाठी - Raspberry Pi 4 स्टार्टर किट](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)**

[![Raspberry Pi टर्मिनल हार्डवेअर किट](../../translated_images/mr/pi-hardware-kit.26dbadaedb7dd44c.webp)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)

## Arduino

Arduino साठी सर्व डिव्हाइस कोड C++ मध्ये आहे. सर्व असाइनमेंट्स पूर्ण करण्यासाठी तुम्हाला खालील गोष्टी लागतील:

### Arduino हार्डवेअर

* [Wio टर्मिनल](https://www.seeedstudio.com/Wio-Terminal-p-4509.html)
* *पर्यायी* - USB-C केबल किंवा USB-A ते USB-C अडॅप्टर. Wio टर्मिनलमध्ये USB-C पोर्ट आहे आणि USB-C ते USB-A केबलसह येतो. जर तुमच्या PC किंवा Mac मध्ये फक्त USB-C पोर्ट्स असतील तर तुम्हाला USB-C केबल किंवा USB-A ते USB-C अडॅप्टर लागेल.

### Arduino साठी विशिष्ट सेन्सर्स आणि अ‍ॅक्ट्युएटर्स

हे Wio टर्मिनल Arduino डिव्हाइससाठी विशिष्ट आहेत आणि Raspberry Pi वापरण्यासाठी संबंधित नाहीत.

* [ArduCam Mini 2MP Plus - OV2640](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/)
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)
* [ब्रेडबोर्ड जम्पर वायर](https://www.seeedstudio.com/Breadboard-Jumper-Wire-Pack-241mm-200mm-160mm-117m-p-234.html)
* हेडफोन किंवा 3.5mm जॅक असलेला दुसरा स्पीकर, किंवा JST स्पीकर जसे:
  * [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
* microSD कार्ड 16GB किंवा कमी, तसेच तुमच्या संगणकासोबत SD कार्ड वापरण्यासाठी कनेक्टर जर तुमच्याकडे अंगभूत नसेल. **NOTE** - Wio टर्मिनल फक्त 16GB पर्यंत SD कार्ड्सला समर्थन देते, त्याहून जास्त क्षमता समर्थित नाही.

## Raspberry Pi

Raspberry Pi साठी सर्व डिव्हाइस कोड Python मध्ये आहे. सर्व असाइनमेंट्स पूर्ण करण्यासाठी तुम्हाला खालील गोष्टी लागतील:

### Raspberry Pi हार्डवेअर

* [Raspberry Pi](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/)
  > 💁 Pi 2B आणि त्याहून पुढील आवृत्त्या या धड्यांमधील असाइनमेंट्ससाठी कार्य करतील. जर तुम्ही VS Code थेट Pi वर चालवण्याचा विचार करत असाल, तर Pi 4 मध्ये 2GB किंवा त्याहून अधिक RAM आवश्यक आहे. जर तुम्ही Pi ला दूरस्थपणे प्रवेश करत असाल तर कोणताही Pi 2B आणि त्याहून पुढील आवृत्त्या कार्य करतील.
* microSD कार्ड (Raspberry Pi किट्समध्ये microSD कार्डसह येऊ शकते), तसेच तुमच्या संगणकासोबत SD कार्ड वापरण्यासाठी कनेक्टर जर तुमच्याकडे अंगभूत नसेल.
* USB पॉवर सप्लाय (Raspberry Pi 4 किट्स USB पॉवर सप्लायसह येऊ शकते). जर तुम्ही Raspberry Pi 4 वापरत असाल तर तुम्हाला USB-C पॉवर सप्लाय लागेल, तर आधीच्या उपकरणांसाठी micro-USB पॉवर सप्लाय लागेल.

### Raspberry Pi साठी विशिष्ट सेन्सर्स आणि अ‍ॅक्ट्युएटर्स

हे Raspberry Pi वापरण्यासाठी विशिष्ट आहेत आणि Arduino डिव्हाइससाठी संबंधित नाहीत.

* [Grove Pi बेस हॅट](https://www.seeedstudio.com/Grove-Base-Hat-for-Raspberry-Pi.html)
* [Raspberry Pi कॅमेरा मॉड्यूल](https://www.raspberrypi.org/products/camera-module-v2/)
* मायक्रोफोन आणि स्पीकर:

  खालीलपैकी एक वापरा (किंवा समतुल्य):
  * कोणताही USB मायक्रोफोन आणि कोणताही USB स्पीकर, किंवा 3.5mm जॅक केबलसह स्पीकर, किंवा HDMI ऑडिओ आउटपुट वापरणे जर तुमचा Raspberry Pi मॉनिटर किंवा TV स्पीकर्ससह जोडलेला असेल
  * अंगभूत मायक्रोफोनसह कोणताही USB हेडसेट
  * [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) सह
    * हेडफोन किंवा 3.5mm जॅक असलेला दुसरा स्पीकर, किंवा JST स्पीकर जसे:
    * [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
  * [USB स्पीकरफोन](https://www.amazon.com/USB-Speakerphone-Conference-Business-Microphones/dp/B07Q3D7F8S/ref=sr_1_1?dchild=1&keywords=m0&qid=1614647389&sr=8-1)
* [Grove लाइट सेन्सर](https://www.seeedstudio.com/Grove-Light-Sensor-v1-2-LS06-S-phototransistor.html)
* [Grove बटण](https://www.seeedstudio.com/Grove-Button.html)

## सेन्सर्स आणि अ‍ॅक्ट्युएटर्स

ज्यांची आवश्यकता आहे त्यातील बहुतेक सेन्सर्स आणि अ‍ॅक्ट्युएटर्स Arduino आणि Raspberry Pi शिकण्याच्या मार्गांसाठी वापरले जातात:

* [Grove LED](https://www.seeedstudio.com/Grove-LED-Pack-p-4364.html) x 2
* [Grove आर्द्रता आणि तापमान सेन्सर](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html)
* [Grove कॅपेसिटिव माती आर्द्रता सेन्सर](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html)
* [Grove रिले](https://www.seeedstudio.com/Grove-Relay.html)
* [Grove GPS (Air530)](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html)
* [Grove टाइम ऑफ फ्लाइट डिस्टन्स सेन्सर](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html)

## पर्यायी हार्डवेअर

स्वयंचलित पाणी देण्याच्या धड्यांमध्ये रिले वापरून काम केले जाते. पर्याय म्हणून, तुम्ही खाली दिलेल्या हार्डवेअरचा वापर करून USB द्वारे चालवलेल्या वॉटर पंपला या रिलेशी जोडू शकता.

* [6V वॉटर पंप](https://www.seeedstudio.com/6V-Mini-Water-Pump-p-1945.html)
* [USB टर्मिनल](https://www.adafruit.com/product/3628)
* सिलिकॉन पाईप्स
* लाल आणि काळ्या वायर
* लहान फ्लॅट-हेड स्क्रूड्रायव्हर

## व्हर्च्युअल हार्डवेअर

व्हर्च्युअल हार्डवेअर मार्ग सेन्सर्स आणि अ‍ॅक्ट्युएटर्ससाठी सिम्युलेटर प्रदान करेल, जे Python मध्ये अंमलात आणले जातील. तुमच्या हार्डवेअर उपलब्धतेनुसार, तुम्ही हे तुमच्या सामान्य विकास उपकरणावर चालवू शकता, जसे की Mac, PC, किंवा Raspberry Pi वर चालवू शकता आणि तुमच्याकडे नसलेल्या हार्डवेअरचे फक्त सिम्युलेशन करू शकता. उदाहरणार्थ, जर तुमच्याकडे Raspberry Pi कॅमेरा असेल पण Grove सेन्सर्स नसतील, तर तुम्ही तुमच्या Pi वर व्हर्च्युअल डिव्हाइस कोड चालवू शकता आणि Grove सेन्सर्सचे सिम्युलेशन करू शकता, पण भौतिक कॅमेरा वापरू शकता.

व्हर्च्युअल हार्डवेअर [CounterFit प्रकल्प](https://github.com/CounterFit-IoT/CounterFit) वापरेल.

हे धडे पूर्ण करण्यासाठी तुम्हाला वेब कॅम, मायक्रोफोन आणि ऑडिओ आउटपुट जसे स्पीकर्स किंवा हेडफोन लागतील. हे अंगभूत किंवा बाह्य असू शकतात, आणि तुमच्या ऑपरेटिंग सिस्टमसह कार्य करण्यासाठी कॉन्फिगर केलेले असणे आवश्यक आहे आणि सर्व अनुप्रयोगांसाठी उपलब्ध असणे आवश्यक आहे.

---

**अस्वीकरण**:  
हा दस्तऐवज AI भाषांतर सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) वापरून भाषांतरित करण्यात आला आहे. आम्ही अचूकतेसाठी प्रयत्नशील असलो तरी, कृपया लक्षात ठेवा की स्वयंचलित भाषांतरांमध्ये त्रुटी किंवा अचूकतेचा अभाव असू शकतो. मूळ भाषेतील दस्तऐवज हा अधिकृत स्रोत मानला जावा. महत्त्वाच्या माहितीसाठी व्यावसायिक मानवी भाषांतराची शिफारस केली जाते. या भाषांतराचा वापर करून निर्माण होणाऱ्या कोणत्याही गैरसमज किंवा चुकीच्या अर्थासाठी आम्ही जबाबदार राहणार नाही.