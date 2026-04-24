# आपल्या फळ शोधकाला एजवर चालवा

![या धड्याचा एक स्केच नोट आढावा](../../../../../translated_images/mr/lesson-17.bc333c3c35ba8e42.webp)

> स्केच नोट [नित्या नरसिंहन](https://github.com/nitya) यांनी तयार केले. मोठ्या आवृत्तीसाठी प्रतिमेवर क्लिक करा.

या व्हिडिओमध्ये IoT उपकरणांवर इमेज क्लासिफायर चालवण्याचा आढावा दिला आहे, जो या धड्यात समाविष्ट आहे.

[![Azure IoT Edge वर Custom Vision AI](https://img.youtube.com/vi/_K5fqGLO8us/0.jpg)](https://www.youtube.com/watch?v=_K5fqGLO8us)

## व्याख्यानपूर्व प्रश्नमंजुषा

[व्याख्यानपूर्व प्रश्नमंजुषा](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/33)

## परिचय

मागील धड्यात तुम्ही तुमच्या इमेज क्लासिफायरचा वापर करून पिकलेली आणि न पिकलेली फळे वर्गीकृत केलीत, ज्यासाठी IoT उपकरणाच्या कॅमेऱ्याने कॅप्चर केलेली प्रतिमा इंटरनेटद्वारे क्लाउड सेवेकडे पाठवली होती. या प्रक्रिया वेळखाऊ, खर्चिक असू शकतात आणि तुम्ही वापरत असलेल्या प्रतिमा डेटाच्या प्रकारावर अवलंबून गोपनीयतेचे मुद्दे निर्माण होऊ शकतात.

या धड्यात तुम्ही एजवर मशीन लर्निंग (ML) मॉडेल्स कसे चालवायचे ते शिकाल - म्हणजेच क्लाउडऐवजी तुमच्या स्वतःच्या नेटवर्कवर चालणाऱ्या IoT उपकरणांवर. तुम्ही एज कम्प्युटिंग विरुद्ध क्लाउड कम्प्युटिंगचे फायदे आणि तोटे, तुमचे AI मॉडेल एजवर कसे डिप्लॉय करायचे, आणि IoT उपकरणातून त्याला कसे ऍक्सेस करायचे हे शिकाल.

या धड्यात आपण शिकणार आहोत:

* [एज कम्प्युटिंग](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Azure IoT Edge](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [IoT Edge उपकरण नोंदणी](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [IoT Edge उपकरण सेटअप](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [तुमचे मॉडेल निर्यात करा](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [तैनातीसाठी कंटेनर तयार करा](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [तुमचा कंटेनर तैनात करा](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [तुमचे IoT Edge उपकरण वापरा](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)

## एज कम्प्युटिंग

एज कम्प्युटिंग म्हणजे IoT डेटा जिथे तयार होतो तिथेच शक्य तितक्या जवळ संगणकीय प्रक्रिया करणे. क्लाउडमध्ये ही प्रक्रिया करण्याऐवजी, ती क्लाउडच्या एजवर - म्हणजे तुमच्या अंतर्गत नेटवर्कवर हलवली जाते.

![क्लाउडमधील इंटरनेट सेवा आणि स्थानिक नेटवर्कवरील IoT उपकरणे दर्शवणारे आर्किटेक्चर डायग्राम](../../../../../translated_images/mr/cloud-without-edge.b4da641f6022c95e.webp)

आतापर्यंतच्या धड्यांमध्ये, तुमची उपकरणे डेटा गोळा करत होती आणि तो क्लाउडमध्ये विश्लेषणासाठी पाठवत होती, जिथे सर्व्हरलेस फंक्शन्स किंवा AI मॉडेल्स चालवले जात होते.

![IoT उपकरणे स्थानिक नेटवर्कवर एज उपकरणांशी जोडलेली आणि ती एज उपकरणे क्लाउडशी जोडलेली दर्शवणारे आर्किटेक्चर डायग्राम](../../../../../translated_images/mr/cloud-with-edge.1e26462c62c126fe.webp)

एज कम्प्युटिंगमध्ये क्लाउडमधील काही सेवा काढून त्या IoT उपकरणांच्या नेटवर्कवर चालणाऱ्या संगणकांवर हलवल्या जातात, आणि केवळ आवश्यक असल्यास क्लाउडशी संवाद साधला जातो. उदाहरणार्थ, तुम्ही एज उपकरणांवर AI मॉडेल्स चालवून फळे पिकलेली आहेत की नाहीत हे तपासू शकता, आणि केवळ विश्लेषणात्मक डेटा क्लाउडमध्ये पाठवू शकता, जसे की पिकलेल्या आणि न पिकलेल्या फळांची संख्या.

✅ विचार करा: आतापर्यंत तुम्ही तयार केलेल्या IoT ऍप्लिकेशन्सपैकी कोणते भाग एजवर हलवता येतील?

### फायदे

एज कम्प्युटिंगचे फायदे:

1. **वेग** - एज कम्प्युटिंग वेळेच्या दृष्टीने संवेदनशील डेटासाठी आदर्श आहे, कारण क्रिया उपकरणाच्या नेटवर्कवरच केल्या जातात, इंटरनेटवर कॉल करण्याऐवजी. यामुळे वेग वाढतो, कारण अंतर्गत नेटवर्क इंटरनेट कनेक्शनपेक्षा खूप जलद असते, आणि डेटा कमी अंतर प्रवास करतो.

    > 💁 जरी इंटरनेट कनेक्शनसाठी ऑप्टिकल केबल्सचा वापर केला जात असला तरी डेटा क्लाउड प्रदात्यांपर्यंत पोहोचण्यासाठी वेळ घेतो. उदाहरणार्थ, जर तुम्ही युरोपमधून अमेरिकेतील क्लाउड सेवेकडे डेटा पाठवत असाल, तर डेटा अटलांटिक पार करण्यासाठी किमान 28ms लागतात, आणि यामध्ये डेटा ट्रान्समिशन, सिग्नल रूपांतरण, आणि क्लाउडपर्यंत पोहोचण्याचा वेळ धरलेला नाही.

    एज कम्प्युटिंगमध्ये कमी नेटवर्क ट्रॅफिक लागतो, ज्यामुळे इंटरनेट कनेक्शनवरील मर्यादित बँडविड्थमुळे डेटा मंदावण्याचा धोका कमी होतो.

1. **दूरस्थ प्रवेशयोग्यता** - एज कम्प्युटिंग मर्यादित किंवा अनुपलब्ध कनेक्टिव्हिटी असताना, किंवा कनेक्टिव्हिटी सतत वापरण्यासाठी खूप महाग असताना कार्य करते. उदाहरणार्थ, आपत्तीग्रस्त भागांमध्ये किंवा विकसनशील देशांमध्ये.

1. **कमी खर्च** - डेटा गोळा करणे, साठवणे, विश्लेषण करणे, आणि क्रिया ट्रिगर करणे एज उपकरणांवर केल्याने क्लाउड सेवांचा वापर कमी होतो, ज्यामुळे IoT ऍप्लिकेशनचा एकूण खर्च कमी होतो. अलीकडेच एज कम्प्युटिंगसाठी डिझाइन केलेल्या उपकरणांची वाढ झाली आहे, जसे की [NVIDIA चा Jetson Nano](https://developer.nvidia.com/embedded/jetson-nano-developer-kit), जे $100 पेक्षा कमी किमतीत GPU-आधारित हार्डवेअर वापरून AI वर्कलोड चालवू शकते.

1. **गोपनीयता आणि सुरक्षा** - एज कम्प्युटिंगमध्ये डेटा तुमच्या नेटवर्कवर राहतो आणि क्लाउडमध्ये अपलोड केला जात नाही. संवेदनशील आणि वैयक्तिकरित्या ओळखण्यायोग्य माहितीच्या बाबतीत हे अधिक पसंतीस पात्र आहे, कारण डेटा विश्लेषणानंतर साठवण्याची गरज नसते, ज्यामुळे डेटा लीक होण्याचा धोका खूप कमी होतो. उदाहरणे: वैद्यकीय डेटा आणि सुरक्षा कॅमेऱ्यांचे फुटेज.

1. **असुरक्षित उपकरणे हाताळणे** - जर तुमच्याकडे ज्ञात सुरक्षा दोष असलेली उपकरणे असतील जी तुम्हाला थेट नेटवर्क किंवा इंटरनेटशी जोडायची नसतील, तर तुम्ही त्यांना वेगळ्या नेटवर्कला IoT Edge गेटवे उपकरणाशी जोडू शकता. हे एज उपकरण तुमच्या विस्तृत नेटवर्कशी किंवा इंटरनेटशी कनेक्शन ठेवून डेटा प्रवाह व्यवस्थापित करू शकते.

1. **असंगत उपकरणांसाठी समर्थन** - जर तुमच्याकडे IoT Hub शी कनेक्ट होऊ न शकणारी उपकरणे असतील, जसे की फक्त HTTP कनेक्शन वापरणारी उपकरणे किंवा फक्त Bluetooth असलेली उपकरणे, तर तुम्ही IoT Edge उपकरण गेटवे म्हणून वापरू शकता, IoT Hub कडे संदेश फॉरवर्ड करण्यासाठी.

✅ संशोधन करा: एज कम्प्युटिंगचे आणखी कोणते फायदे असू शकतात?

### तोटे

एज कम्प्युटिंगचे तोटे, जिथे क्लाउड अधिक चांगला पर्याय ठरतो:

1. **स्केल आणि लवचिकता** - क्लाउड कम्प्युटिंग नेटवर्क आणि डेटा गरजेनुसार रिअल-टाइममध्ये संसाधने वाढवते किंवा कमी करते. अधिक एज संगणक जोडण्यासाठी मॅन्युअली उपकरणे जोडावी लागतात.

1. **विश्वसनीयता आणि लवचिकता** - क्लाउड कम्प्युटिंग अनेक ठिकाणी अनेक सर्व्हर पुरवते, जे पुनर्प्राप्ती आणि आपत्ती व्यवस्थापनासाठी उपयुक्त असते. एजवर समान पातळीची लवचिकता मिळवण्यासाठी मोठ्या गुंतवणुकीची आणि कॉन्फिगरेशनची गरज असते.

1. **देखभाल** - क्लाउड सेवा प्रदाते सिस्टम देखभाल आणि अद्यतने पुरवतात.

✅ संशोधन करा: एज कम्प्युटिंगचे आणखी कोणते तोटे असू शकतात?

तोटे म्हणजे क्लाउडचा वापर करण्याच्या फायद्यांचे उलट आहेत - तुम्हाला ही उपकरणे स्वतः तयार आणि व्यवस्थापित करावी लागतात, क्लाउड प्रदात्यांच्या कौशल्यावर आणि स्केलवर अवलंबून न राहता.

काही जोखमी एज कम्प्युटिंगच्या स्वरूपामुळे कमी होतात. उदाहरणार्थ, जर तुमच्याकडे फॅक्टरीमध्ये चालणारे एज उपकरण असेल जे यंत्रसामग्रीकडून डेटा गोळा करत असेल, तर काही आपत्ती व्यवस्थापन परिस्थितींचा विचार करण्याची गरज नाही. जर फॅक्टरीला वीजपुरवठा खंडित झाला, तर एज उपकरणासाठी बॅकअपची गरज नाही, कारण डेटा तयार करणारी यंत्रसामग्रीही वीजविहीन असेल.

IoT प्रणालींसाठी, तुम्हाला क्लाउड आणि एज कम्प्युटिंगचा एकत्रित वापर करायचा असेल, प्रणालीच्या गरजांनुसार, ग्राहकांच्या गरजांनुसार, आणि देखभाल करणाऱ्यांच्या गरजांनुसार.

## Azure IoT Edge

![Azure IoT Edge लोगो](../../../../../translated_images/mr/azure-iot-edge-logo.c1c076749b5cba2e.webp)

Azure IoT Edge ही एक सेवा आहे जी तुम्हाला क्लाउडमधील वर्कलोड्स एजवर हलवण्यास मदत करू शकते. तुम्ही एका उपकरणाला एज उपकरण म्हणून सेट अप करता, आणि क्लाउडमधून त्या एज उपकरणावर कोड डिप्लॉय करू शकता. यामुळे क्लाउड आणि एजच्या क्षमतांचा एकत्रित वापर करता येतो.

> 🎓 *वर्कलोड्स* म्हणजे अशा कोणत्याही सेवांसाठी वापरला जाणारा शब्द, ज्या काही प्रकारचे काम करतात, जसे की AI मॉडेल्स, ऍप्लिकेशन्स, किंवा सर्व्हरलेस फंक्शन्स.

उदाहरणार्थ, तुम्ही क्लाउडमध्ये इमेज क्लासिफायर ट्रेन करू शकता, आणि नंतर क्लाउडमधून एज उपकरणावर डिप्लॉय करू शकता. तुमचे IoT उपकरण प्रतिमा एज उपकरणाकडे वर्गीकरणासाठी पाठवेल, इंटरनेटवर पाठवण्याऐवजी. जर तुम्हाला मॉडेलची नवीन आवृत्ती डिप्लॉय करायची असेल, तर तुम्ही क्लाउडमध्ये ट्रेन करू शकता आणि IoT Edge चा वापर करून एज उपकरणावर नवीन आवृत्ती अपडेट करू शकता.

> 🎓 IoT Edge वर डिप्लॉय केलेले सॉफ्टवेअर *मॉड्यूल्स* म्हणून ओळखले जाते. डिफॉल्टनुसार IoT Edge IoT Hub शी संवाद साधणारी मॉड्यूल्स चालवते, जसे की `edgeAgent` आणि `edgeHub` मॉड्यूल्स. जेव्हा तुम्ही इमेज क्लासिफायर डिप्लॉय करता, तेव्हा ते एक अतिरिक्त मॉड्यूल म्हणून डिप्लॉय केले जाते.

IoT Edge IoT Hub मध्ये अंगभूत आहे, त्यामुळे तुम्ही IoT उपकरणे व्यवस्थापित करण्यासाठी वापरत असलेल्या त्याच सेवेद्वारे एज उपकरणे व्यवस्थापित करू शकता, तीच सुरक्षा पातळी राखून.

IoT Edge कोड *कंटेनर्स* मधून चालवते - स्वतंत्र ऍप्लिकेशन्स जे तुमच्या संगणकावरील इतर ऍप्लिकेशन्सपासून वेगळे चालवले जातात. कंटेनर चालवताना ते तुमच्या संगणकामध्ये एक स्वतंत्र संगणकासारखे कार्य करते, ज्यामध्ये त्याचे स्वतःचे सॉफ्टवेअर, सेवा, आणि ऍप्लिकेशन्स चालतात. बहुतेक वेळा कंटेनर्सना तुमच्या संगणकावरील काहीही ऍक्सेस करता येत नाही, जोपर्यंत तुम्ही एखादी गोष्ट, जसे की फोल्डर, शेअर करण्याचा निर्णय घेत नाही. कंटेनर नंतर उघडलेल्या पोर्टद्वारे सेवा प्रदान करतो, ज्याला तुम्ही कनेक्ट करू शकता किंवा तुमच्या नेटवर्कवर उघड करू शकता.

![वेब विनंती कंटेनरकडे पुनर्निर्देशित केली जात आहे](../../../../../translated_images/mr/container-web-browser.4ee81dd4f0d8838c.webp)

उदाहरणार्थ, तुम्ही पोर्ट 80 वर चालणारी वेबसाइट असलेला कंटेनर तयार करू शकता, जो HTTP साठी डिफॉल्ट पोर्ट आहे, आणि नंतर तो तुमच्या संगणकावरही पोर्ट 80 वर उघड करू शकता.

✅ संशोधन करा: कंटेनर्स आणि Docker किंवा Moby सारख्या सेवांबद्दल वाचा.

तुम्ही Custom Vision चा वापर करून इमेज क्लासिफायर डाउनलोड करू शकता आणि त्यांना कंटेनर्स म्हणून डिप्लॉय करू शकता, थेट उपकरणावर चालवण्यासाठी किंवा IoT Edge च्या माध्यमातून डिप्लॉय करण्यासाठी. एकदा ते कंटेनरमध्ये चालू झाल्यावर, त्यांना क्लाउड आवृत्तीप्रमाणेच REST API चा वापर करून ऍक्सेस करता येते, परंतु एज उपकरणावर चालणाऱ्या कंटेनरच्या एन्डपॉइंटकडे निर्देशित करून.

## IoT Edge उपकरण नोंदणी

IoT Edge उपकरण वापरण्यासाठी, त्याला IoT Hub मध्ये नोंदणी करावी लागते.

### कार्य - IoT Edge उपकरण नोंदणी करा

1. `fruit-quality-detector` संसाधन गटात IoT Hub तयार करा. त्याला `fruit-quality-detector` वर आधारित एक अद्वितीय नाव द्या.

1. तुमच्या IoT Hub मध्ये `fruit-quality-detector-edge` नावाचे IoT Edge उपकरण नोंदणी करा. हे करण्यासाठी वापरला जाणारा आदेश एज नसलेल्या उपकरणासाठी वापरल्या जाणाऱ्या आदेशासारखाच आहे, फक्त तुम्हाला `--edge-enabled` फ्लॅग पास करावा लागतो.

    ```sh
    az iot hub device-identity create --edge-enabled \
                                      --device-id fruit-quality-detector-edge \
                                      --hub-name <hub_name>
    ```

    `<hub_name>` च्या जागी तुमच्या IoT Hub चे नाव द्या.

1. खालील आदेश वापरून तुमच्या उपकरणासाठी कनेक्शन स्ट्रिंग मिळवा:

    ```sh
    az iot hub device-identity connection-string show --device-id fruit-quality-detector-edge \
                                                      --output table \
                                                      --hub-name <hub_name>
    ```

    `<hub_name>` च्या जागी तुमच्या IoT Hub चे नाव द्या.

    आउटपुटमध्ये दाखवलेला कनेक्शन स्ट्रिंग कॉपी करा.

## IoT Edge उपकरण सेटअप

एकदा तुम्ही तुमच्या IoT Hub मध्ये एज उपकरणाची नोंदणी केली की, तुम्ही एज उपकरण सेटअप करू शकता.

### कार्य - IoT Edge Runtime इंस्टॉल करा आणि सुरू करा

**IoT Edge Runtime फक्त Linux कंटेनर्स चालवते.** हे Linux वर चालवता येते, किंवा Windows वर Linux Virtual Machines चा वापर करून.

* जर तुम्ही तुमच्या IoT उपकरणासाठी Raspberry Pi वापरत असाल, तर हे Linux ची समर्थित आवृत्ती चालवते आणि IoT Edge Runtime होस्ट करू शकते. IoT Edge इंस्टॉल करण्यासाठी आणि कनेक्शन स्ट्रिंग सेट करण्यासाठी [Microsoft Docs वरील Azure IoT Edge साठी Linux मार्गदर्शक](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge?WT.mc_id=academic-17441-jabenn) अनुसरा.

    > 💁 लक्षात ठेवा, Raspberry Pi OS हा Debian Linux चा एक प्रकार आहे.

* जर तुम्ही Raspberry Pi वापरत नसाल, पण तुमच्याकडे Linux संगणक असेल, तर तुम्ही IoT Edge Runtime चालवू शकता. IoT Edge इंस्टॉल करण्यासाठी आणि कनेक्शन स्ट्रिंग सेट करण्यासाठी [Microsoft Docs वरील Azure IoT Edge साठी Linux मार्गदर्शक](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge?WT.mc_id=academic-17441-jabenn) अनुसरा.

* जर तुम्ही Windows वापरत असाल, तर तुम्ही Linux Virtual Machine मध्ये IoT Edge Runtime इंस्टॉल करू शकता. [Microsoft Docs वरील Windows उपकरणावर तुमचे पहिले IoT Edge मॉड्यूल डिप्लॉय करा क्विकस्टार्ट](https://docs.microsoft.com/azure/iot-edge/quickstart?WT.mc_id=academic-17441-jabenn#install-and-start-the-iot-edge-runtime) च्या *IoT Edge Runtime इंस्टॉल करा आणि सुरू करा* विभागाचे अनुसरण करा. *मॉड्यूल डिप्लॉय करा* विभागापर्यंत पोहोचल्यावर थांबा.

* जर तुम्ही macOS वापरत असाल, तर तुम्ही IoT Edge उपकरणासाठी क्लाउडमध्ये एक Virtual Machine (VM) तयार करू शकता. हे असे संगणक आहेत जे तुम्ही क्लाउडमध्ये तयार करू शकता आणि इंटरनेटद्वारे ऍक्सेस करू शकता. IoT Edge इंस्टॉल केलेला Linux VM तयार करण्यासाठी [IoT Edge चालवणारा Virtual Machine तयार करा मार्गदर्शक](vm-iotedge.md) अनुसरा.

## तुमचे मॉडेल निर्यात करा

एजवर क्लासिफायर चालवण्यासाठी, ते Custom Vision मधून निर्यात करणे आवश्यक आहे. Custom Vision दोन प्रकारची मॉडेल्स तयार करू शकते - स्टँडर्ड मॉडेल्स आणि कॉम्पॅक्ट मॉडेल्स. कॉम्पॅक्ट मॉडेल्स विविध तंत्रांचा वापर करून मॉडेलचा आकार कमी करतात, ज्यामुळे ते IoT उपकरणांवर डाउनलोड आणि डिप्लॉय करण्यासाठी योग्य बनते.

जेव्हा तुम्ह
1. [CustomVision.ai](https://customvision.ai) पोर्टल उघडा आणि साइन इन करा, जर आधीपासून उघडले नसेल. त्यानंतर तुमचा `fruit-quality-detector` प्रकल्प उघडा.

1. **Settings** बटण निवडा (⚙ चिन्ह).

1. *Domains* यादीतून *Food (compact)* निवडा.

1. *Export Capabilities* अंतर्गत, *Basic platforms (Tensorflow, CoreML, ONNX, ...)* निवडले आहे याची खात्री करा.

1. Settings पृष्ठाच्या तळाशी **Save Changes** निवडा.

1. **Train** बटण वापरून मॉडेल पुन्हा प्रशिक्षित करा, *Quick training* निवडून.

### कार्य - तुमचे मॉडेल निर्यात करा

मॉडेल प्रशिक्षित झाल्यानंतर, ते कंटेनर म्हणून निर्यात करणे आवश्यक आहे.

1. **Performance** टॅब निवडा आणि कॉम्पॅक्ट डोमेन वापरून प्रशिक्षित केलेली तुमची नवीनतम आवृत्ती शोधा.

1. वरच्या बाजूला **Export** बटण निवडा.

1. **DockerFile** निवडा, नंतर तुमच्या एज डिव्हाइसशी जुळणारी आवृत्ती निवडा:

    * जर तुम्ही Linux संगणक, Windows संगणक किंवा Virtual Machine वर IoT Edge चालवत असाल, तर *Linux* आवृत्ती निवडा.
    * जर तुम्ही Raspberry Pi वर IoT Edge चालवत असाल, तर *ARM (Raspberry Pi 3)* आवृत्ती निवडा.

    
> 🎓 Docker हे कंटेनर व्यवस्थापनासाठी सर्वात लोकप्रिय साधनांपैकी एक आहे, आणि DockerFile हे कंटेनर कसे सेट करायचे याबद्दलच्या सूचनांचा संच आहे.

1. संबंधित फाइल्स तयार करण्यासाठी **Export** निवडा, नंतर त्या झिप फाईलमध्ये डाउनलोड करण्यासाठी **Download** निवडा.

1. फाइल्स तुमच्या संगणकावर जतन करा आणि फोल्डर अनझिप करा.

## तुमच्या कंटेनरची तैनातीसाठी तयारी करा

![कंटेनर तयार केले जातात, नंतर कंटेनर रजिस्ट्रीवर ढकलले जातात, आणि IoT Edge वापरून एज डिव्हाइसवर तैनात केले जातात](../../../../../translated_images/mr/container-edge-flow.c246050dd60ceefd.webp)

तुमचे मॉडेल डाउनलोड केल्यानंतर, ते कंटेनरमध्ये तयार करणे आवश्यक आहे, नंतर कंटेनर रजिस्ट्रीवर ढकलले जाते - एक ऑनलाइन स्थान जिथे तुम्ही कंटेनर संग्रहित करू शकता. IoT Edge नंतर रजिस्ट्रीमधून कंटेनर डाउनलोड करू शकते आणि ते तुमच्या डिव्हाइसवर ढकलू शकते.

![Azure Container Registry लोगो](../../../../../translated_images/mr/azure-container-registry-logo.09494206991d4b29.webp)

या धड्यासाठी तुम्ही वापरणार असलेली कंटेनर रजिस्ट्री म्हणजे Azure Container Registry. ही विनामूल्य सेवा नाही, त्यामुळे पैसे वाचवण्यासाठी तुम्ही पूर्ण केल्यानंतर तुमचा प्रकल्प [स्वच्छ करा](../../../clean-up.md).

> 💁 Azure Container Registry वापरण्याचा खर्च [Azure Container Registry किंमत पृष्ठावर](https://azure.microsoft.com/pricing/details/container-registry/?WT.mc_id=academic-17441-jabenn) पाहू शकता.

### कार्य - Docker स्थापित करा

क्लासिफायर तयार आणि तैनात करण्यासाठी, तुम्हाला [Docker](https://www.docker.com/) स्थापित करावे लागेल.

जर तुम्ही IoT Edge स्थापित केलेल्या डिव्हाइसपेक्षा वेगळ्या डिव्हाइसवरून तुमचा कंटेनर तयार करण्याची योजना आखत असाल, तरच तुम्हाला हे करावे लागेल - IoT Edge स्थापित करण्याचा भाग म्हणून, Docker तुमच्यासाठी स्थापित केले जाते.

1. जर तुम्ही IoT Edge डिव्हाइसपेक्षा वेगळ्या डिव्हाइसवर Docker कंटेनर तयार करत असाल, तर [Docker install page](https://www.docker.com/products/docker-desktop) वरील Docker Desktop किंवा Docker engine स्थापित करण्याच्या सूचनांचे अनुसरण करा. स्थापना पूर्ण झाल्यानंतर ते चालू असल्याची खात्री करा.

### कार्य - कंटेनर रजिस्ट्री संसाधन तयार करा

1. Azure Container Registry संसाधन तयार करण्यासाठी तुमच्या टर्मिनल किंवा कमांड प्रॉम्प्टवरून खालील आदेश चालवा:

    ```sh
    az acr create --resource-group fruit-quality-detector \
                  --sku Basic \
                  --name <Container registry name>
    ```

    `<Container registry name>` हे नाव अक्षरे आणि संख्या वापरून अद्वितीय ठेवा. `fruitqualitydetector` वर आधारित ठेवा. हे नाव कंटेनर रजिस्ट्रीमध्ये प्रवेश करण्यासाठी URL चा भाग बनते, त्यामुळे ते जागतिक स्तरावर अद्वितीय असणे आवश्यक आहे.

1. खालील आदेश वापरून Azure Container Registry मध्ये लॉग इन करा:

    ```sh
    az acr login --name <Container registry name>
    ```

    `<Container registry name>` मध्ये तुमच्या कंटेनर रजिस्ट्रीचे नाव ठेवा.

1. कंटेनर रजिस्ट्रीला अॅडमिन मोडमध्ये सेट करा जेणेकरून तुम्ही पासवर्ड तयार करू शकता:

    ```sh
    az acr update --admin-enabled true \
                 --name <Container registry name>
    ```

    `<Container registry name>` मध्ये तुमच्या कंटेनर रजिस्ट्रीचे नाव ठेवा.

1. कंटेनर रजिस्ट्रीसाठी पासवर्ड तयार करण्यासाठी खालील आदेश वापरा:

    ```sh
     az acr credential renew --password-name password \
                             --output table \
                             --name <Container registry name>
    ```

    `<Container registry name>` मध्ये तुमच्या कंटेनर रजिस्ट्रीचे नाव ठेवा.

    `PASSWORD` चे मूल्य कॉपी करा, कारण तुम्हाला नंतर याची गरज भासेल.

### कार्य - तुमचा कंटेनर तयार करा

Custom Vision कडून तुम्ही जे डाउनलोड केले ते DockerFile होते, ज्यामध्ये कंटेनर कसे तयार करायचे याबद्दलच्या सूचनांचा समावेश आहे, तसेच तुमच्या कस्टम व्हिजन मॉडेलसाठी होस्टिंगसाठी कंटेनरमध्ये चालवले जाणारे अॅप्लिकेशन कोड आणि REST API देखील आहे. Docker वापरून DockerFile वरून टॅग केलेला कंटेनर तयार करा, नंतर तो कंटेनर रजिस्ट्रीवर ढकलून द्या.

> 🎓 कंटेनरना टॅग दिले जाते जे त्यांचे नाव आणि आवृत्ती परिभाषित करते. जेव्हा तुम्हाला कंटेनर अपडेट करायचा असेल तेव्हा तुम्ही त्याच टॅगसह नवीन आवृत्ती तयार करू शकता.

1. तुमचे टर्मिनल किंवा कमांड प्रॉम्प्ट उघडा आणि Custom Vision कडून डाउनलोड केलेल्या अनझिप केलेल्या मॉडेलवर जा.

1. खालील आदेश चालवा:

    ```sh
    docker build --platform <platform> -t <Container registry name>.azurecr.io/classifier:v1 .
    ```

    `<platform>` मध्ये कंटेनर चालवले जाणारे प्लॅटफॉर्म ठेवा. जर तुम्ही IoT Edge Raspberry Pi वर चालवत असाल, तर `linux/armhf` ठेवा, अन्यथा `linux/amd64` ठेवा.

    > 💁 जर तुम्ही IoT Edge चालवणाऱ्या डिव्हाइसवरून हा आदेश चालवत असाल, जसे की तुमच्या Raspberry Pi वरून चालवत असाल, तर `--platform <platform>` भाग वगळू शकता कारण ते सध्याच्या प्लॅटफॉर्मवर डीफॉल्ट असते.

    `<Container registry name>` मध्ये तुमच्या कंटेनर रजिस्ट्रीचे नाव ठेवा.

    > 💁 जर तुम्ही Linux किंवा Raspberry Pi OS वर चालवत असाल, तर हा आदेश चालवण्यासाठी तुम्हाला `sudo` वापरावे लागेल.

    Docker इमेज तयार करेल, आवश्यक सॉफ्टवेअर कॉन्फिगर करेल. इमेज नंतर `classifier:v1` म्हणून टॅग केली जाईल.

    ```output
    ➜  d4ccc45da0bb478bad287128e1274c3c.DockerFile.Linux docker build --platform linux/amd64 -t  fruitqualitydetectorjimb.azurecr.io/classifier:v1 .
    [+] Building 102.4s (11/11) FINISHED
     => [internal] load build definition from Dockerfile
     => => transferring dockerfile: 131B
     => [internal] load .dockerignore
     => => transferring context: 2B
     => [internal] load metadata for docker.io/library/python:3.7-slim
     => [internal] load build context
     => => transferring context: 905B
     => [1/6] FROM docker.io/library/python:3.7-slim@sha256:b21b91c9618e951a8cbca5b696424fa5e820800a88b7e7afd66bba0441a764d6
     => => resolve docker.io/library/python:3.7-slim@sha256:b21b91c9618e951a8cbca5b696424fa5e820800a88b7e7afd66bba0441a764d6
     => => sha256:b4d181a07f8025e00e0cb28f1cc14613da2ce26450b80c54aea537fa93cf3bda 27.15MB / 27.15MB
     => => sha256:de8ecf497b753094723ccf9cea8a46076e7cb845f333df99a6f4f397c93c6ea9 2.77MB / 2.77MB
     => => sha256:707b80804672b7c5d8f21e37c8396f319151e1298d976186b4f3b76ead9f10c8 10.06MB / 10.06MB
     => => sha256:b21b91c9618e951a8cbca5b696424fa5e820800a88b7e7afd66bba0441a764d6 1.86kB / 1.86kB
     => => sha256:44073386687709c437586676b572ff45128ff1f1570153c2f727140d4a9accad 1.37kB / 1.37kB
     => => sha256:3d94f0f2ca798607808b771a7766f47ae62a26f820e871dd488baeccc69838d1 8.31kB / 8.31kB
     => => sha256:283715715396fd56d0e90355125fd4ec57b4f0773f306fcd5fa353b998beeb41 233B / 233B
     => => sha256:8353afd48f6b84c3603ea49d204bdcf2a1daada15f5d6cad9cc916e186610a9f 2.64MB / 2.64MB
     => => extracting sha256:b4d181a07f8025e00e0cb28f1cc14613da2ce26450b80c54aea537fa93cf3bda
     => => extracting sha256:de8ecf497b753094723ccf9cea8a46076e7cb845f333df99a6f4f397c93c6ea9
     => => extracting sha256:707b80804672b7c5d8f21e37c8396f319151e1298d976186b4f3b76ead9f10c8
     => => extracting sha256:283715715396fd56d0e90355125fd4ec57b4f0773f306fcd5fa353b998beeb41
     => => extracting sha256:8353afd48f6b84c3603ea49d204bdcf2a1daada15f5d6cad9cc916e186610a9f
     => [2/6] RUN pip install -U pip
     => [3/6] RUN pip install --no-cache-dir numpy~=1.17.5 tensorflow~=2.0.2 flask~=1.1.2 pillow~=7.2.0
     => [4/6] RUN pip install --no-cache-dir mscviplib==2.200731.16
     => [5/6] COPY app /app
     => [6/6] WORKDIR /app
     => exporting to image
     => => exporting layers
     => => writing image sha256:1846b6f134431f78507ba7c079358ed66d944c0e185ab53428276bd822400386
     => => naming to fruitqualitydetectorjimb.azurecr.io/classifier:v1
    ```

### कार्य - तुमचा कंटेनर कंटेनर रजिस्ट्रीवर ढकलणे

1. खालील आदेश वापरून तुमचा कंटेनर कंटेनर रजिस्ट्रीवर ढकला:

    ```sh
    docker push <Container registry name>.azurecr.io/classifier:v1
    ```

    `<Container registry name>` मध्ये तुमच्या कंटेनर रजिस्ट्रीचे नाव ठेवा.

    > 💁 जर तुम्ही Linux चालवत असाल, तर हा आदेश चालवण्यासाठी तुम्हाला `sudo` वापरावे लागेल.

    कंटेनर कंटेनर रजिस्ट्रीवर ढकलला जाईल.

    ```output
    ➜  d4ccc45da0bb478bad287128e1274c3c.DockerFile.Linux docker push fruitqualitydetectorjimb.azurecr.io/classifier:v1
    The push refers to repository [fruitqualitydetectorjimb.azurecr.io/classifier]
    5f70bf18a086: Pushed 
    8a1ba9294a22: Pushed 
    56cf27184a76: Pushed 
    b32154f3f5dd: Pushed 
    36103e9a3104: Pushed 
    e2abb3cacca0: Pushed 
    4213fd357bbe: Pushed 
    7ea163ba4dce: Pushed 
    537313a13d90: Pushed 
    764055ebc9a7: Pushed 
    v1: digest: sha256:ea7894652e610de83a5a9e429618e763b8904284253f4fa0c9f65f0df3a5ded8 size: 2423
    ```

1. पुष्टी करण्यासाठी, खालील आदेश वापरून रजिस्ट्रीतील कंटेनर यादीत पहा:

    ```sh
    az acr repository list --output table \
                           --name <Container registry name> 
    ```

    `<Container registry name>` मध्ये तुमच्या कंटेनर रजिस्ट्रीचे नाव ठेवा.

    ```output
    ➜  d4ccc45da0bb478bad287128e1274c3c.DockerFile.Linux az acr repository list --name fruitqualitydetectorjimb --output table
    Result
    ----------
    classifier
    ```

    तुम्हाला आउटपुटमध्ये तुमचा क्लासिफायर दिसेल.

## तुमचा कंटेनर तैनात करा

तुमचा कंटेनर आता IoT Edge डिव्हाइसवर तैनात केला जाऊ शकतो. तैनातीसाठी तुम्हाला एक तैनाती मॅनिफेस्ट तयार करणे आवश्यक आहे - एक JSON दस्तऐवज जो एज डिव्हाइसवर तैनात होणाऱ्या मॉड्यूल्सची यादी करतो.

### कार्य - तैनाती मॅनिफेस्ट तयार करा

1. तुमच्या संगणकावर `deployment.json` नावाची नवीन फाईल तयार करा.

1. या फाईलमध्ये खालील जोडा:

    ```json
    {
        "content": {
            "modulesContent": {
                "$edgeAgent": {
                    "properties.desired": {
                        "schemaVersion": "1.1",
                        "runtime": {
                            "type": "docker",
                            "settings": {
                                "minDockerVersion": "v1.25",
                                "loggingOptions": "",
                                "registryCredentials": {
                                    "ClassifierRegistry": {
                                        "username": "<Container registry name>",
                                        "password": "<Container registry password>",
                                        "address": "<Container registry name>.azurecr.io"
                                      }
                                }
                            }
                        },
                        "systemModules": {
                            "edgeAgent": {
                                "type": "docker",
                                "settings": {
                                    "image": "mcr.microsoft.com/azureiotedge-agent:1.1",
                                    "createOptions": "{}"
                                }
                            },
                            "edgeHub": {
                                "type": "docker",
                                "status": "running",
                                "restartPolicy": "always",
                                "settings": {
                                    "image": "mcr.microsoft.com/azureiotedge-hub:1.1",
                                    "createOptions": "{\"HostConfig\":{\"PortBindings\":{\"5671/tcp\":[{\"HostPort\":\"5671\"}],\"8883/tcp\":[{\"HostPort\":\"8883\"}],\"443/tcp\":[{\"HostPort\":\"443\"}]}}}"
                                }
                            }
                        },
                        "modules": {
                            "ImageClassifier": {
                                "version": "1.0",
                                "type": "docker",
                                "status": "running",
                                "restartPolicy": "always",
                                "settings": {
                                    "image": "<Container registry name>.azurecr.io/classifier:v1",
                                    "createOptions": "{\"ExposedPorts\": {\"80/tcp\": {}},\"HostConfig\": {\"PortBindings\": {\"80/tcp\": [{\"HostPort\": \"80\"}]}}}"
                                }
                            }
                        }
                    }
                },
                "$edgeHub": {
                    "properties.desired": {
                        "schemaVersion": "1.1",
                        "routes": {
                            "upstream": "FROM /messages/* INTO $upstream"
                        },
                        "storeAndForwardConfiguration": {
                            "timeToLiveSecs": 7200
                        }
                    }
                }
            }
        }
    }
    ```

    > 💁 तुम्ही ही फाईल [code-deployment/deployment](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-deployment/deployment) फोल्डरमध्ये शोधू शकता.

    `<Container registry name>` च्या तीन उदाहरणे तुमच्या कंटेनर रजिस्ट्रीच्या नावाने बदला. एक `ImageClassifier` मॉड्यूल विभागात आहे, तर उर्वरित दोन `registryCredentials` विभागात आहेत.

    `registryCredentials` विभागातील `<Container registry password>` ला तुमच्या कंटेनर रजिस्ट्रीच्या पासवर्डने बदला.

1. तुमच्या तैनाती मॅनिफेस्ट असलेल्या फोल्डरमधून खालील आदेश चालवा:

    ```sh
    az iot edge set-modules --device-id fruit-quality-detector-edge \
                            --content deployment.json \
                            --hub-name <hub_name>
    ```

    `<hub_name>` मध्ये तुमच्या IoT Hub चे नाव ठेवा.

    इमेज क्लासिफायर मॉड्यूल एज डिव्हाइसवर तैनात केले जाईल.

### कार्य - क्लासिफायर चालू आहे याची खात्री करा

1. IoT Edge डिव्हाइसशी कनेक्ट करा:

    * जर तुम्ही IoT Edge चालवण्यासाठी Raspberry Pi वापरत असाल, तर तुमच्या टर्मिनलमधून ssh वापरून कनेक्ट करा किंवा VS Code मध्ये रिमोट SSH सत्राद्वारे कनेक्ट करा.
    * जर तुम्ही Windows वर Linux कंटेनरमध्ये IoT Edge चालवत असाल, तर [यशस्वी कॉन्फिगरेशन सत्यापित करण्याच्या मार्गदर्शक](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge-on-windows?WT.mc_id=academic-17441-jabenn&view=iotedge-2018-06&tabs=powershell#verify-successful-configuration) मधील चरणांचे अनुसरण करा.
    * जर तुम्ही IoT Edge व्हर्च्युअल मशीनवर चालवत असाल, तर तुम्ही VM तयार करताना सेट केलेल्या `adminUsername` आणि `password` वापरून SSH करू शकता, आणि IP पत्ता किंवा DNS नाव वापरून:

        ```sh
        ssh <adminUsername>@<IP address>
        ```

        किंवा:

        ```sh
        ssh <adminUsername>@<DNS Name>
        ```

        संकेतशब्द विचारल्यावर प्रविष्ट करा.

1. एकदा कनेक्ट झाल्यावर, IoT Edge मॉड्यूल्सची यादी मिळवण्यासाठी खालील आदेश चालवा:

    ```sh
    iotedge list
    ```

    > 💁 तुम्हाला हा आदेश `sudo` सह चालवावा लागू शकतो.

    तुम्हाला चालू असलेली मॉड्यूल्स दिसतील:

    ```output
    jim@fruit-quality-detector-jimb:~$ iotedge list
    NAME             STATUS           DESCRIPTION      CONFIG
    ImageClassifier  running          Up 42 minutes    fruitqualitydetectorjimb.azurecr.io/classifier:v1
    edgeAgent        running          Up 42 minutes    mcr.microsoft.com/azureiotedge-agent:1.1
    edgeHub          running          Up 42 minutes    mcr.microsoft.com/azureiotedge-hub:1.1
    ```

1. इमेज क्लासिफायर मॉड्यूलसाठी लॉग तपासा:

    ```sh
    iotedge logs ImageClassifier
    ```

    > 💁 तुम्हाला हा आदेश `sudo` सह चालवावा लागू शकतो.

    ```output
    jim@fruit-quality-detector-jimb:~$ iotedge logs ImageClassifier
    2021-07-05 20:30:15.387144: I tensorflow/core/platform/cpu_feature_guard.cc:142] Your CPU supports instructions that this TensorFlow binary was not compiled to use: AVX2 FMA
    2021-07-05 20:30:15.392185: I tensorflow/core/platform/profile_utils/cpu_utils.cc:94] CPU Frequency: 2394450000 Hz
    2021-07-05 20:30:15.392712: I tensorflow/compiler/xla/service/service.cc:168] XLA service 0x55ed9ac83470 executing computations on platform Host. Devices:
    2021-07-05 20:30:15.392806: I tensorflow/compiler/xla/service/service.cc:175]   StreamExecutor device (0): Host, Default Version
    Loading model...Success!
    Loading labels...2 found. Success!
     * Serving Flask app "app" (lazy loading)
     * Environment: production
       WARNING: This is a development server. Do not use it in a production deployment.
       Use a production WSGI server instead.
     * Debug mode: off
     * Running on http://0.0.0.0:80/ (Press CTRL+C to quit)
    ```

### कार्य - इमेज क्लासिफायरची चाचणी करा

1. तुम्ही CURL वापरून इमेज क्लासिफायरची चाचणी करू शकता, IoT Edge एजंट चालवणाऱ्या संगणकाचा IP पत्ता किंवा होस्ट नाव वापरून. IP पत्ता शोधा:

    * जर तुम्ही IoT Edge चालवणाऱ्या त्याच मशीनवर असाल, तर होस्ट नाव म्हणून `localhost` वापरू शकता.
    * जर तुम्ही VM वापरत असाल, तर VM चा IP पत्ता किंवा DNS नाव वापरू शकता.
    * अन्यथा, IoT Edge चालवणाऱ्या मशीनचा IP पत्ता मिळवा:
      * Windows 10 वर, [तुमचा IP पत्ता शोधा मार्गदर्शक](https://support.microsoft.com/windows/find-your-ip-address-f21a9bbc-c582-55cd-35e0-73431160a1b9?WT.mc_id=academic-17441-jabenn) अनुसरा.
      * macOS वर, [Mac वर तुमचा IP पत्ता कसा शोधायचा मार्गदर्शक](https://www.hellotech.com/guide/for/how-to-find-ip-address-on-mac) अनुसरा.
      * Linux वर, [Linux मध्ये तुमचा IP पत्ता कसा शोधायचा मार्गदर्शक](https://opensource.com/article/18/5/how-find-ip-address-linux) मधील खाजगी IP पत्ता शोधण्याचा विभाग अनुसरा.

1. स्थानिक फाईलसह कंटेनरची चाचणी करण्यासाठी खालील curl आदेश चालवा:

    ```sh
    curl --location \
         --request POST 'http://<IP address or name>/image' \
         --header 'Content-Type: image/png' \
         --data-binary '@<file_Name>' 
    ```

    `<IP address or name>` मध्ये IoT Edge चालवणाऱ्या संगणकाचा IP पत्ता किंवा होस्ट नाव ठेवा. `<file_Name>` मध्ये चाचणीसाठी फाईलचे नाव ठेवा.

    तुम्हाला आउटपुटमध्ये अंदाज परिणाम दिसतील:

    ```output
    {
        "created": "2021-07-05T21:44:39.573181",
        "id": "",
        "iteration": "",
        "predictions": [
            {
                "boundingBox": null,
                "probability": 0.9995615482330322,
                "tagId": "",
                "tagName": "ripe"
            },
            {
                "boundingBox": null,
                "probability": 0.0004384400090202689,
                "tagId": "",
                "tagName": "unripe"
            }
        ],
        "project": ""
    }
    ```

    > 💁 येथे अंदाज की प्रदान करण्याची गरज नाही, कारण हे Azure संसाधन वापरत नाही. त्याऐवजी अंतर्गत नेटवर्कवरील अंतर्गत सुरक्षा गरजांवर आधारित सुरक्षा कॉन्फिगर केली जाईल, सार्वजनिक एंडपॉइंट आणि API कीवर अवलंबून न राहता.

## तुमचे IoT Edge डिव्हाइस वापरा

आता तुमचा इमेज क्लासिफायर IoT Edge डिव्हाइसवर तैनात झाला आहे, तुम्ही तो तुमच्या IoT डिव्हाइसवरून वापरू शकता.

### कार्य - तुमचे IoT Edge डिव्हाइस वापरा

IoT Edge क्लासिफायर वापरून इमेजेस वर्गीकृत करण्यासाठी संबंधित मार्गदर्शक पूर्ण करा:

* [Arduino - Wio Terminal](wio-terminal.md)
* [Single-board computer - Raspberry Pi/Virtual IoT device](single-board-computer.md)

### मॉडेल पुन्हा प्रशिक्षण

IoT Edge वर इमेज क्लासिफायर चालवण्याचे एक नुकसान म्हणजे ते तुमच्या Custom Vision प्रकल्पाशी जोडलेले नाही. Custom Vision मधील **Predictions** टॅबमध्ये तुम्हाला Edge-आधारित क्लासिफायर वापरून वर्गीकृत केलेली इमेजेस दिसणार नाहीत.

हे अपेक्षित वर्तन आहे - इमेजेस वर्गीकरणासाठी क्लाउडवर पाठवल्या जात नाहीत, त्यामुळे त्या क्लाउडमध्ये उपलब्ध असणार नाहीत. IoT Edge वापरण्याचा एक फायदा म्हणजे गोपनीयता, याची खात्री करणे की इमेजेस तुमच्या नेटवर्कच्या बाहेर जात नाहीत, दुसरा फायदा म्हणजे ऑफलाइन काम करण्याची क्षमता, त्यामुळे डिव्हाइसला इंटरनेट कनेक्शन नसताना इमेजेस अपलोड करण्यावर अवलंबून राहण्याची गरज नाही. नुकसान म्हणजे तुमचे मॉडेल सुधारित करणे - तुम्हाला इमेजेस संग्रहित करण्याचा दुसरा मार्ग अंमलात आणावा लागेल, ज्यांना सुधारण्यासाठी आणि इमेज क्लासिफायर पुन्हा प्रशिक्षित करण्यासाठी मॅन्युअली पुनर्वर्गीकृत केले जाऊ शकते.

✅ क्लासिफायर पुन्हा प्रशिक्षित करण्यासाठी इमेजेस अपलोड करण्याचे मार्ग विचार करा.

---

## 🚀 आव्हान

एज डिव्हाइसवर AI मॉडेल चालवणे क्लाउडपेक्षा जलद असू शकते - नेटवर्क हॉप लहान असतो. ते हळू देखील असू शकते कारण मॉडेल चालवणारे हार्डवेअर क्लाउडइतके शक्तिशाली नसते.

तुमच्या एज डिव्हाइसवर कॉल क्लाउडपेक्षा जलद आहे की हळू आहे हे तपासा? फरक किंवा फरक नसण्याचे कारण स्पष्ट करण्यासाठी विचार करा. एजवर AI मॉडेल्स जलद चालवण्यासाठी विशेष हार्डवेअर वापरण्याचे मार्ग संशोधन करा.

## व्याख्यानानंतरची क्विझ

[व्याख्यानानंतरची क्विझ](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/34)

## पुनरावलोकन आणि स्व-अभ्यास

* कंटेनर्सबद्दल अधिक वाचा [OS-level virtualization page on Wikipedia](https://wikipedia.org/wiki/OS-level_virtualization)
* 5G कसे एज कंप्युटिंगचा विस्तार करण्यात मदत करू शकते यावर भर देऊन एज कंप्युटिंगबद्दल अधिक वाचा [एज कंप्युटिंग म्हणजे काय आणि त्याचा महत्त्व काय आहे? NetworkWorld वरचा लेख](https://www.networkworld.com/article/3224893/what-is-edge-computing-and-how-its-changing-the-network.html)
* IoT Edge मध्ये AI सेवा चालवण्याबद्दल अधिक जाणून घ्या [Azure IoT Edge वापरून एजवर तयार केलेल्या AI सेवेसह भाषा ओळख कशी करावी याबद्दल Microsoft Channel9 वर Learn Live च्या एपिसोडमध्ये](https://channel9.msdn.com/Shows/Learn-Live/Sharpen-Your-AI-Edge-Skills-Episode-4-Learn-How-to-Use-Azure-IoT-Edge-on-a-Pre-Built-AI-Service-on-t?WT.mc_id=academic-17441-jabenn)

## असाइनमेंट

[एजवर इतर सेवा चालवा](assignment.md)

---

**अस्वीकरण**:  
हा दस्तऐवज AI भाषांतर सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) वापरून भाषांतरित करण्यात आला आहे. आम्ही अचूकतेसाठी प्रयत्नशील असलो तरी कृपया लक्षात ठेवा की स्वयंचलित भाषांतरांमध्ये त्रुटी किंवा अचूकतेचा अभाव असू शकतो. मूळ भाषेतील दस्तऐवज हा अधिकृत स्रोत मानला जावा. महत्त्वाच्या माहितीसाठी व्यावसायिक मानवी भाषांतराची शिफारस केली जाते. या भाषांतराचा वापर करून उद्भवलेल्या कोणत्याही गैरसमज किंवा चुकीच्या अर्थासाठी आम्ही जबाबदार राहणार नाही.