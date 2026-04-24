### Azure AI Foundry Community में शामिल हों

अगर आप फंस गए हैं या AI ऐप्स बनाने के बारे में कोई प्रश्न हैं। MCP के बारे में चर्चा में साथी शिक्षार्थियों और अनुभवी डेवलपर्स से जुड़ें। यह एक सहायक समुदाय है जहाँ प्रश्नों का स्वागत है और ज्ञान स्वतंत्र रूप से साझा किया जाता है।

यदि आपके पास उत्पाद प्रतिक्रिया या निर्माण के दौरान त्रुटियाँ हैं तो यहाँ जाएँ:

इन संसाधनों का उपयोग शुरू करने के लिए इन चरणों का पालन करें:
1. **रिपॉजिटरी को फोर्क करें**: क्लिक करें [![GitHub forks](https://img.shields.io/github/forks/microsoft/IoT-For-Beginners.svg?style=social&label=Fork)](https://GitHub.com/microsoft/IoT-For-Beginners/fork)
2. **रिपॉजिटरी को क्लोन करें**:   `git clone https://github.com/microsoft/IoT-For-Beginners.git`
3. [**Microsoft Foundry Discord में शामिल हों और विशेषज्ञों तथा अन्य डेवलपर्स से मिलें**](https://discord.com/invite/ByRwuEEgH4)


### 🌐 बहुभाषी समर्थन

#### GitHub Action के माध्यम से समर्थित (स्वचालित और हमेशा अद्यतित)

> **स्थानीय रूप से क्लोन करना पसंद है?**
>
> इस रिपॉजिटरी में 50+ भाषा अनुवाद शामिल हैं जो डाउनलोड आकार को काफी बढ़ाते हैं। बिना अनुवाद के क्लोन करने के लिए sparse checkout का उपयोग करें:
>
> **Bash / macOS / Linux:**
> ```bash
> git clone --filter=blob:none --sparse https://github.com/microsoft/IoT-For-Beginners.git
> cd IoT-For-Beginners
> git sparse-checkout set --no-cone '/*' '!translations' '!translated_images'
> ```
>
> **CMD (Windows):**
> ```cmd
> git clone --filter=blob:none --sparse https://github.com/microsoft/IoT-For-Beginners.git
> cd IoT-For-Beginners
> git sparse-checkout set --no-cone "/*" "!translations" "!translated_images"
> ```
>
> यह आपको तेज़ डाउनलोड के साथ कोर्स पूरा करने के लिए सभी आवश्यक चीजें देता है।

# प्रारंभिक लोगों के लिए IoT - एक पाठ्यक्रम

Microsoft में Azure Cloud Advocates IoT मूल बातें के बारे में 12 सप्ताह, 24-लेसन का पाठ्यक्रम प्रदान करने में प्रसन्न हैं। प्रत्येक पाठ में पूर्व और पश्चात क्विज़, पाठ पूरा करने के लिए लिखित निर्देश, एक समाधान, एक असाइनमेंट और बहुत कुछ शामिल है। हमारी परियोजना-आधारित शिक्षाशास्त्र आपको निर्माण करते हुए सीखने की अनुमति देती है, जो नई क्षमताओं के 'अटके' रहने के लिए एक सिद्ध तरीका है।

परियोजनाएं खेत से लेकर मेज तक भोजन की यात्रा को कवर करती हैं। इसमें खेती, लॉजिस्टिक्स, निर्माण, खुदरा और उपभोक्ता शामिल हैं - IoT डिवाइसेस के लिए सभी लोकप्रिय उद्योग क्षेत्र।

> स्केचनोट [Nitya Narasimhan](https://github.com/nitya) द्वारा। बड़ी प्रति के लिए छवि पर क्लिक करें।

**हमारे लेखकों [Jen Fox](https://github.com/jenfoxbot), [Jen Looper](https://github.com/jlooper), [Jim Bennett](https://github.com/jimbobbennett), और हमारे स्केचनोट कलाकार [Nitya Narasimhan](https://github.com/nitya) को हार्दिक धन्यवाद।**

**धन्यवाद हमारी टीम [Microsoft Learn Student Ambassadors](https://studentambassadors.microsoft.com?WT.mc_id=academic-17441-jabenn) को जिन्होंने इस पाठ्यक्रम की समीक्षा और अनुवाद किया - [Aditya Garg](https://github.com/AdityaGarg00), [Anurag Sharma](https://github.com/Anurag-0-1-A), [Arpita Das](https://github.com/Arpiiitaaa), [Aryan Jain](https://www.linkedin.com/in/aryan-jain-47a4a1145/), [Bhavesh Suneja](https://github.com/EliteWarrior315), [Faith Hunja](https://faithhunja.github.io/), [Lateefah Bello](https://www.linkedin.com/in/lateefah-bello/), [Manvi Jha](https://github.com/Severus-Matthew), [Mireille Tan](https://www.linkedin.com/in/mireille-tan-a4834819a/), [Mohammad Iftekher (Iftu) Ebne Jalal](https://github.com/Iftu119), [Mohammad Zulfikar](https://github.com/mohzulfikar), [Priyanshu Srivastav](https://www.linkedin.com/in/priyanshu-srivastav-b067241ba), [Thanmai Gowducheruvu](https://github.com/innovation-platform), और [Zina Kamel](https://www.linkedin.com/in/zina-kamel/).**

टीम से मिलें!

**Gif द्वारा** [Mohit Jaisal](https://linkedin.com/in/mohitjaisal)

> 🎥 इस परियोजना के बारे में वीडियो के लिए ऊपर की छवि पर क्लिक करें!

> **शिक्षक**, इस पाठ्यक्रम का उपयोग कैसे करें इसके लिए हमने [कुछ सुझाव](for-teachers.md) शामिल किए हैं। यदि आप अपनी स्वयं की कक्षाएं बनाना चाहते हैं, तो हमने एक [पाठ टेम्पलेट](lesson-template/README.md) भी शामिल किया है।

> **[छात्रों](https://aka.ms/student-page)**, इस पाठ्यक्रम को अपने आप इस्तेमाल करने के लिए, पूरी रिपॉजिटरी को फोर्क करें और पूर्व-कक्षा क्विज़ के साथ शुरू करके व्यायामों को ख़ुद पूरा करें, फिर व्याख्यान पढ़ें और बाकी गतिविधियाँ करें। समाधान कोड की नकल करने के बजाय पाठ समझकर परियोजनाओं को बनाने की कोशिश करें; हालांकि वह कोड प्रत्येक परियोजना-उन्मुख सबक के /solutions फ़ोल्डर में उपलब्ध है। एक और विचार यह हो सकता है कि दोस्तों के साथ एक अध्ययन समूह बनाएं और सामग्री को साथ में देखें। आगे अध्ययन के लिए, हम [Microsoft Learn](https://docs.microsoft.com/users/jimbobbennett/collections/ke2ehd351jopwr?WT.mc_id=academic-17441-jabenn) की सिफारिश करते हैं।

इस कोर्स का वीडियो अवलोकन देखने के लिए, यह वीडियो देखें:

> 🎥 इस परियोजना के बारे में वीडियो के लिए ऊपर की छवि पर क्लिक करें!

## शिक्षाशास्त्र

इस पाठ्यक्रम का निर्माण करते समय हमने दो शिक्षाशास्त्रीय सिद्धांत चुने हैं: यह सुनिश्चित करना कि यह परियोजना-आधारित हो और इसमें अक्सर क्विज़ शामिल हों। इस श्रृंखला के अंत तक, छात्र एक पौधे की निगरानी और पानी देने वाली प्रणाली, एक वाहन ट्रैकर, एक स्मार्ट फैक्ट्री सेटअप जो भोजन को ट्रैक और जांचती है, और एक आवाज़-नियंत्रित कुकिंग टाइमर बनाएंगे, और वे इंटरनेट ऑफ थिंग्स के मूल बातें सीखेंगे जिसमें डिवाइस कोड लिखना, क्लाउड से कनेक्ट करना, टेलीमेट्री का विश्लेषण करना और एज पर AI चलाना शामिल है।

सामग्री को परियोजनाओं से मेल खाने के साथ सुनिश्चित करने से छात्रों के लिए प्रक्रिया अधिक आकर्षक होती है और अवधारणाओं को बनाए रखने में वृद्धि होती है।

इसके अतिरिक्त, कक्षा से पहले एक कम जोखिम वाला क्विज़ छात्र के सीखने के इरादे को सेट करता है, जबकि कक्षा के बाद दूसरा क्विज़ अतिरिक्त अवधारण सुनिश्चित करता है। यह पाठ्यक्रम लचीला और मजेदार बनाने के लिए डिज़ाइन किया गया है और इसे पूरी तरह या आंशिक रूप से लिया जा सकता है। परियोजनाएं छोटी शुरू होती हैं और 12 सप्ताह की अवधि के अंत तक जटिल हो जाती हैं।

प्रत्येक परियोजना वास्तविक दुनिया के हार्डवेयर पर आधारित होती है जो छात्रों और शौकीनों के लिए उपलब्ध है। प्रत्येक परियोजना विशिष्ट परियोजना डोमेन में एक नज़र डालती है, प्रासंगिक पृष्ठभूमि ज्ञान प्रदान करती है। सफल डेवलपर बनने के लिए यह समझना मददगार होता है कि आप किस डोमेन में समस्या हल कर रहे हैं, यह पृष्ठभूमि ज्ञान छात्रों को उनके IoT समाधानों और सीख को वास्तविक दुनिया की समस्या के संदर्भ में सोचने में सक्षम बनाता है जिसे उनसे IoT डेवलपर के रूप में हल करने के लिए कहा जा सकता है। छात्र जो समाधान वे बना रहे हैं उसका 'क्यों' सीखते हैं, और अंतिम उपयोगकर्ता की प्रशंसा प्राप्त करते हैं।

## हार्डवेयर
हमारे पास परियोजनाओं के लिए उपयोग करने के लिए दो IoT हार्डवेयर विकल्प हैं जो व्यक्तिगत पसंद, प्रोग्रामिंग भाषा ज्ञान या प्राथमिकताओं, सीखने के उद्देश्य और उपलब्धता पर निर्भर करते हैं। जिनके पास हार्डवेयर नहीं है, या खरीदारी के लिए प्रतिबद्ध होने से पहले अधिक सीखना चाहते हैं, उनके लिए हमने 'वर्चुअल हार्डवेयर' संस्करण भी प्रदान किया है। आप अधिक पढ़ सकते हैं और एक 'शॉपिंग लिस्ट' [हार्डवेयर पृष्ठ](./hardware.md) पर पा सकते हैं, जिसमें हमारे मित्र Seeed Studio से पूर्ण किट खरीदने के लिंक भी शामिल हैं।

> 💁 हमारे [आचरण संहिता](CODE_OF_CONDUCT.md), [योगदान](CONTRIBUTING.md), और [अनुवाद](..) दिशानिर्देश देखें। हम आपके रचनात्मक फीडबैक का स्वागत करते हैं!
>
> 🔧 किसी समस्या का सामना कर रहे हैं? आम समस्याओं के समाधान के लिए हमारा [समस्या निवारण गाइड](TROUBLESHOOTING.md) देखें।

## प्रत्येक पाठ में शामिल हैं:

- स्केचनोट
- वैकल्पिक पूरक वीडियो
- पूर्व-पाठ वार्मअप क्विज़
- लिखित पाठ
- परियोजना-आधारित पाठों के लिए, परियोजना को बनाने के लिए कदम-दर-कदम मार्गदर्शिकाएँ
- ज्ञान जांच
- एक चुनौती
- पूरक पठन सामग्री
- असाइनमेंट
- [पाठ के बाद क्विज़](https://ff-quizzes.netlify.app/en/)

> **क्विज़ के बारे में एक नोट**: सभी क्विज़ क़्विज़-ऐप फ़ोल्डर में संग्रहीत हैं, तीन प्रश्नों वाले कुल 48 क्विज़ के लिए। वे पाठों के भीतर लिंक किए गए हैं लेकिन क्विज़ ऐप को स्थानीय रूप से चलाया जा सकता है या Azure पर डिप्लॉय किया जा सकता है; `quiz-app` फ़ोल्डर में दिए निर्देशों का पालन करें। इन्हें धीरे-धीरे स्थानीयकृत किया जा रहा है।

## पाठ

|       |              परियोजना का नाम              |                       सिखाए गए अवधारणाएं                       | सीखने के उद्देश्य                                                                                                                                                 |                                                        लिंक्ड पाठ                                                         |
| :---: | :------------------------------------: | :---------------------------------------------------------: | ------------------------------------------------------------------------------------------------------------------------------------------------------------------- | :--------------------------------------------------------------------------------------------------------------------------: |
|  01   | [शुरुआत करना](./1-getting-started/README.md) |                     IoT का परिचय                     | IoT के मूल सिद्धांतों और IoT समाधानों के मूलभूत निर्माण खंडों जैसे सेंसर और क्लाउड सेवाओं को सीखें जबकि आप अपना पहला IoT डिवाइस स्थापित कर रहे हैं |                      [IoT का परिचय](./1-getting-started/lessons/1-introduction-to-iot/README.md)                      |
|  02   | [शुरुआत करना](./1-getting-started/README.md) |                   IoT में गहराई से ज्ञान                    | IoT सिस्टम के घटकों के साथ-साथ माइक्रोकंट्रोलर और सिंगल-बोर्ड कंप्यूटर्स के बारे में और जानें                                                            |                        [IoT में गहराई से ज्ञान](./1-getting-started/lessons/2-deeper-dive/README.md)                         |
|  03   | [शुरुआत करना](./1-getting-started/README.md) | भौतिक दुनिया के साथ सेंसर और एक्टुएटर्स द्वारा इंटरैक्ट करें | भौतिक दुनिया से डेटा एकत्र करने के लिए सेंसर और फीडबैक भेजने के लिए एक्टुएटर्स के बारे में जानें, जबकि आप एक नाईटलाइट बनाते हैं                                           | [सेंसर और एक्टुएटर्स के साथ भौतिक दुनिया के साथ इंटरैक्ट करें](./1-getting-started/lessons/3-sensors-and-actuators/README.md) |
|  04   | [शुरुआत करना](./1-getting-started/README.md) |             अपने डिवाइस को इंटरनेट से जोड़ें             | एक IoT डिवाइस को इंटरनेट से जोड़ने के बारे में जानें ताकि संदेश भेजने और प्राप्त करने के लिए अपने नाईटलाइट को MQTT ब्रोकर्स से कनेक्ट करें                               |               [अपने डिवाइस को इंटरनेट से जोड़ें](./1-getting-started/lessons/4-connect-internet/README.md)                |
|  05   |            [फार्म](./2-farm/README.md)            |                    पौधे की वृद्धि का अनुमान लगाएं                     | तापमान डेटा का उपयोग करके पौधे की वृद्धि की भविष्यवाणी कैसे की जाती है, जो एक IoT डिवाइस द्वारा कैप्चर किया गया है                                                                                  |                          [पौधे की वृद्धि का अनुमान लगाएं](./2-farm/lessons/1-predict-plant-growth/README.md)                           |
|  06   |            [फार्म](./2-farm/README.md)            |                    मिट्टी की नमी का पता लगाएं                     | मिट्टी की नमी का पता लगाने और मिट्टी की नमी सेंसर को कैलिब्रेट करने का तरीका सीखें                                                                                              |                          [मिट्टी की नमी का पता लगाएं](./2-farm/lessons/2-detect-soil-moisture/README.md)                           |
|  07   |            [फार्म](./2-farm/README.md)            |                  स्वचालित पौधों को पानी देना                   | रिले और MQTT का उपयोग करके पानी देने को स्वचालित और समयबद्ध करने का तरीका जानें                                                                                                      |                      [स्वचालित पौधों को पानी देना](./2-farm/lessons/3-automated-plant-watering/README.md)                       |
|  08   |            [फार्म](./2-farm/README.md)            |               अपने पौधे को क्लाउड में स्थानांतरित करें               | क्लाउड और क्लाउड-होस्टेड IoT सेवाओं के बारे में जानें और कैसे अपने पौधे को सार्वजनिक MQTT ब्रोकर्स की बजाय इनमें से किसी एक से कनेक्ट करें                                   |               [अपने पौधे को क्लाउड में स्थानांतरित करें](./2-farm/lessons/4-migrate-your-plant-to-the-cloud/README.md)                |
|  09   |            [फार्म](./2-farm/README.md)            |         अपने एप्लिकेशन लॉजिक को क्लाउड में स्थानांतरित करें         | जानें कि आप कैसे क्लाउड में एप्लिकेशन लॉजिक लिख सकते हैं जो IoT संदेशों पर प्रतिक्रिया देता है                                                                          |         [अपने एप्लिकेशन लॉजिक को क्लाउड में स्थानांतरित करें](./2-farm/lessons/5-migrate-application-to-the-cloud/README.md)         |
|  10   |            [फार्म](./2-farm/README.md)            |                   अपने पौधे को सुरक्षित रखें                    | IoT के साथ सुरक्षा के बारे में जानें और कैसे कुंजी और प्रमाणपत्रों के साथ अपने पौधे को सुरक्षित रखें                                                                          |                        [अपने पौधे को सुरक्षित रखें](./2-farm/lessons/6-keep-your-plant-secure/README.md)                         |
|  11   |       [ट्रांसपोर्ट](./3-transport/README.md)       |                      स्थान ट्रैकिंग                      | IoT उपकरणों के लिए GPS स्थान ट्रैकिंग के बारे में जानें                                                                                                                   |                           [स्थान ट्रैकिंग](./3-transport/lessons/1-location-tracking/README.md)                           |
|  12   |       [ट्रांसपोर्ट](./3-transport/README.md)       |                     स्थान डेटा संग्रहित करें                     | बाद में विश्लेषण या विज़ुअलाइजेशन के लिए IoT डेटा कैसे स्टोर करें                                                                                                      |                         [स्थान डेटा संग्रहित करें](./3-transport/lessons/2-store-location-data/README.md)                         |
|  13   |       [ट्रांसपोर्ट](./3-transport/README.md)       |                   स्थान डेटा का विज़ुअलाइज़ेशन                   | नक्शे पर स्थान डेटा का विज़ुअलाइज़ेशन कैसे किया जाता है, और नक्शे 3D वास्तविक दुनिया को 2D में कैसे दर्शाते हैं इसके बारे में जानें                                                            |                     [स्थान डेटा का विज़ुअलाइज़ेशन](./3-transport/lessons/3-visualize-location-data/README.md)                     |
|  14   |       [ट्रांसपोर्ट](./3-transport/README.md)       |                          भू-सीमाएं                          | भू-सीमाओं के बारे में जानें, और कैसे वे आपूर्ति श्रृंखला में गाड़ियों के अपने गंतव्य के करीब होने पर अलर्ट करने के लिए उपयोग की जा सकती हैं                                           |                                   [भू-सीमाएं](./3-transport/lessons/4-geofences/README.md)                                   |
|  15   |   [मैन्युफैक्चरिंग](./4-manufacturing/README.md)   |               फल गुणवत्ता डिटेक्टर को प्रशिक्षित करें                | क्लाउड में एक इमेज क्लासिफायर प्रशिक्षित करने के बारे में जानें जो फल की गुणवत्ता का पता लगाता है                                                                                       |                 [फल गुणवत्ता डिटेक्टर को प्रशिक्षित करें](./4-manufacturing/lessons/1-train-fruit-detector/README.md)                 |
|  16   |   [मैन्युफैक्चरिंग](./4-manufacturing/README.md)   |           IoT डिवाइस से फल की गुणवत्ता जांचें            | अपने IoT डिवाइस से अपने फल गुणवत्ता डिटेक्टर का उपयोग कैसे करें इसके बारे में जानें                                                                                                    |           [IoT डिवाइस से फल की गुणवत्ता जांचें](./4-manufacturing/lessons/2-check-fruit-from-device/README.md)            |
|  17   |   [मैन्युफैक्चरिंग](./4-manufacturing/README.md)   |             एज पर अपना फल डिटेक्टर चलाएं             | अपने IoT डिवाइस पर एज पर अपने फल डिटेक्टर को चलाने के बारे में जानें                                                                                                |             [एज पर अपना फल डिटेक्टर चलाएं](./4-manufacturing/lessons/3-run-fruit-detector-edge/README.md)             |
|  18   |   [मैन्युफैक्चरिंग](./4-manufacturing/README.md)   |        सेंसर से फल गुणवत्ता डिटेक्शन ट्रिगर करें        | सेंसर से फ्रूट क्वालिटी डिटेक्शन ट्रिगर करने के बारे में सीखें                                                                                                        |        [सेंसर से फ्रूट क्वालिटी डिटेक्शन ट्रिगर करें](./4-manufacturing/lessons/4-trigger-fruit-detector/README.md)         |
|  19   |          [रिटेल](./5-retail/README.md)          |                   स्टॉक डिटेक्टर को प्रशिक्षित करें                    | वस्तु पहचान का उपयोग करके दुकान में स्टॉक गिनने के लिए स्टॉक डिटेक्टर को प्रशिक्षित करने का तरीका सीखें                                                                                |                        [स्टॉक डिटेक्टर को प्रशिक्षित करें](./5-retail/lessons/1-train-stock-detector/README.md)                         |
|  20   |          [रिटेल](./5-retail/README.md)          |               IoT डिवाइस से स्टॉक की जांच करें                | वस्तु पहचान मॉडल का उपयोग करके IoT डिवाइस से स्टॉक की जांच कैसे करें                                                                                         |                     [IoT डिवाइस से स्टॉक की जांच करें](./5-retail/lessons/2-check-stock-device/README.md)                      |
|  21   |        [कंज्यूमर](./6-consumer/README.md)        |             IoT डिवाइस से भाषण पहचान             | IoT डिवाइस से भाषण पहचान करना सीखें ताकि एक स्मार्ट टाइमर बनाया जा सके                                                                                             |                  [IoT डिवाइस से भाषण पहचान](./6-consumer/lessons/1-speech-recognition/README.md)                  |
|  22   |        [कंज्यूमर](./6-consumer/README.md)        |                     भाषा को समझना                     | IoT डिवाइस को बोली गई वाक्यों को समझने का तरीका जानें                                                                                                           |                        [भाषा को समझना](./6-consumer/lessons/2-language-understanding/README.md)                        |
|  23   |        [कंज्यूमर](./6-consumer/README.md)        |           टाइमर सेट करें और बोले हुए फीडबैक दें           | IoT डिवाइस पर टाइमर सेट करने और जब टाइमर सेट हो और पूरा हो जाए तो बोले हुए फीडबैक देने का तरीका सीखें                                                    |                 [टाइमर सेट करें और बोले हुए फीडबैक दें](./6-consumer/lessons/3-spoken-feedback/README.md)                  |
|  24   |        [कंज्यूमर](./6-consumer/README.md)        |                 कई भाषाओं का समर्थन करें                  | कई भाषाओं का समर्थन कैसे करें, दोनों बोली जाने वाली और आपके स्मार्ट टाइमर से आने वाली प्रतिक्रियाएं                                                               |                   [कई भाषाओं का समर्थन करें](./6-consumer/lessons/4-multiple-language-support/README.md)                   |

## ऑफ़लाइन एक्सेस

आप इस दस्तावेज़ को ऑफ़लाइन उर्फ़ कर सकते हैं [Docsify](https://docsify.js.org/#/) का उपयोग करके। इस रिपॉजिटरी को फोर्क करें, [Docsify इंस्टॉल करें](https://docsify.js.org/#/quickstart) अपनी स्थानीय मशीन पर, और फिर इस रिपॉजिटरी के रूट फ़ोल्डर में `docsify serve` टाइप करें। वेबसाइट आपके लोकलहोस्ट पर पोर्ट 3000 पर सेवा प्रदान करेगी: `localhost:3000`।

## क्विज़

धन्यवाद सामुदायिक सदस्यों का जो प्रत्येक अध्याय पर आपकी जानकारी का परीक्षण करने वाला इंटरैक्टिव क्विज़ होस्ट करते हैं। आप अपनी जानकारी [यहाँ](https://ff-quizzes.netlify.app/en/) पर टेस्ट कर सकते हैं।

### PDF

यदि आवश्यक हो तो आप ऑफ़लाइन एक्सेस के लिए इस सामग्री का PDF बना सकते हैं। ऐसा करने के लिए, सुनिश्चित करें कि आपके पास [npm इंस्टॉल है](https://docs.npmjs.com/downloading-and-installing-node-js-and-npm) और फिर इस रिपॉजिटरी के रूट फ़ोल्डर में निम्न कमांड चलाएं:

```sh
npm i
npm run convert
```

### स्लाइड्स

कुछ पाठों के लिए स्लाइड डेक [slides](../../slides) फ़ोल्डर में उपलब्ध हैं।

## अन्य पाठ्यक्रम

हमारी टीम अन्य पाठ्यक्रम भी बनाती है! देखें:

<!-- CO-OP TRANSLATOR OTHER COURSES START -->
### LangChain
[![LangChain4j for Beginners](https://img.shields.io/badge/LangChain4j%20for%20Beginners-22C55E?style=for-the-badge&&labelColor=E5E7EB&color=0553D6)](https://aka.ms/langchain4j-for-beginners)
[![LangChain.js for Beginners](https://img.shields.io/badge/LangChain.js%20for%20Beginners-22C55E?style=for-the-badge&labelColor=E5E7EB&color=0553D6)](https://aka.ms/langchainjs-for-beginners?WT.mc_id=m365-94501-dwahlin)
[![LangChain for Beginners](https://img.shields.io/badge/LangChain%20for%20Beginners-22C55E?style=for-the-badge&labelColor=E5E7EB&color=0553D6)](https://github.com/microsoft/langchain-for-beginners?WT.mc_id=m365-94501-dwahlin)
---

### Azure / Edge / MCP / Agents
[![AZD for Beginners](https://img.shields.io/badge/AZD%20for%20Beginners-0078D4?style=for-the-badge&labelColor=E5E7EB&color=0078D4)](https://github.com/microsoft/AZD-for-beginners?WT.mc_id=academic-105485-koreyst)
[![Edge AI for Beginners](https://img.shields.io/badge/Edge%20AI%20for%20Beginners-00B8E4?style=for-the-badge&labelColor=E5E7EB&color=00B8E4)](https://github.com/microsoft/edgeai-for-beginners?WT.mc_id=academic-105485-koreyst)
[![MCP for Beginners](https://img.shields.io/badge/MCP%20for%20Beginners-009688?style=for-the-badge&labelColor=E5E7EB&color=009688)](https://github.com/microsoft/mcp-for-beginners?WT.mc_id=academic-105485-koreyst)
[![AI Agents for Beginners](https://img.shields.io/badge/AI%20Agents%20for%20Beginners-00C49A?style=for-the-badge&labelColor=E5E7EB&color=00C49A)](https://github.com/microsoft/ai-agents-for-beginners?WT.mc_id=academic-105485-koreyst)

---
 
### जनरेटिव एआई श्रृंखला
[![Generative AI for Beginners](https://img.shields.io/badge/Generative%20AI%20for%20Beginners-8B5CF6?style=for-the-badge&labelColor=E5E7EB&color=8B5CF6)](https://github.com/microsoft/generative-ai-for-beginners?WT.mc_id=academic-105485-koreyst)
[![Generative AI (.NET)](https://img.shields.io/badge/Generative%20AI%20(.NET)-9333EA?style=for-the-badge&labelColor=E5E7EB&color=9333EA)](https://github.com/microsoft/Generative-AI-for-beginners-dotnet?WT.mc_id=academic-105485-koreyst)
[![Generative AI (Java)](https://img.shields.io/badge/Generative%20AI%20(Java)-C084FC?style=for-the-badge&labelColor=E5E7EB&color=C084FC)](https://github.com/microsoft/generative-ai-for-beginners-java?WT.mc_id=academic-105485-koreyst)
[![Generative AI (JavaScript)](https://img.shields.io/badge/Generative%20AI%20(JavaScript)-E879F9?style=for-the-badge&labelColor=E5E7EB&color=E879F9)](https://github.com/microsoft/generative-ai-with-javascript?WT.mc_id=academic-105485-koreyst)

---
 
### कोर लर्निंग
[![ML for Beginners](https://img.shields.io/badge/ML%20for%20Beginners-22C55E?style=for-the-badge&labelColor=E5E7EB&color=22C55E)](https://aka.ms/ml-beginners?WT.mc_id=academic-105485-koreyst)
[![Data Science for Beginners](https://img.shields.io/badge/Data%20Science%20for%20Beginners-84CC16?style=for-the-badge&labelColor=E5E7EB&color=84CC16)](https://aka.ms/datascience-beginners?WT.mc_id=academic-105485-koreyst)
[![AI for Beginners](https://img.shields.io/badge/AI%20for%20Beginners-A3E635?style=for-the-badge&labelColor=E5E7EB&color=A3E635)](https://aka.ms/ai-beginners?WT.mc_id=academic-105485-koreyst)
[![Cybersecurity for Beginners](https://img.shields.io/badge/Cybersecurity%20for%20Beginners-F97316?style=for-the-badge&labelColor=E5E7EB&color=F97316)](https://github.com/microsoft/Security-101?WT.mc_id=academic-96948-sayoung)
[![Web Dev for Beginners](https://img.shields.io/badge/Web%20Dev%20for%20Beginners-EC4899?style=for-the-badge&labelColor=E5E7EB&color=EC4899)](https://aka.ms/webdev-beginners?WT.mc_id=academic-105485-koreyst)
[![IoT for Beginners](https://img.shields.io/badge/IoT%20for%20Beginners-14B8A6?style=for-the-badge&labelColor=E5E7EB&color=14B8A6)](https://aka.ms/iot-beginners?WT.mc_id=academic-105485-koreyst)
[![XR Development for Beginners](https://img.shields.io/badge/XR%20Development%20for%20Beginners-38BDF8?style=for-the-badge&labelColor=E5E7EB&color=38BDF8)](https://github.com/microsoft/xr-development-for-beginners?WT.mc_id=academic-105485-koreyst)

---
 
### कोपाइलट श्रृंखला
[![Copilot for AI Paired Programming](https://img.shields.io/badge/Copilot%20for%20AI%20Paired%20Programming-FACC15?style=for-the-badge&labelColor=E5E7EB&color=FACC15)](https://aka.ms/GitHubCopilotAI?WT.mc_id=academic-105485-koreyst)
[![Copilot for C#/.NET](https://img.shields.io/badge/Copilot%20for%20C%23/.NET-FBBF24?style=for-the-badge&labelColor=E5E7EB&color=FBBF24)](https://github.com/microsoft/mastering-github-copilot-for-dotnet-csharp-developers?WT.mc_id=academic-105485-koreyst)
[![Copilot Adventure](https://img.shields.io/badge/Copilot%20Adventure-FDE68A?style=for-the-badge&labelColor=E5E7EB&color=FDE68A)](https://github.com/microsoft/CopilotAdventures?WT.mc_id=academic-105485-koreyst)
<!-- CO-OP TRANSLATOR OTHER COURSES END -->

## छवि श्रेय

आप इस पाठ्यक्रम में उपयोग की गई सभी छवियों के श्रेय [Attributions](./attributions.md) में आवश्यकतानुसार पा सकते हैं।

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**डिस्क्लेमर**:  
इस दस्तावेज़ का अनुवाद AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) का उपयोग करके किया गया है। जबकि हम सटीकता के लिए प्रयासरत हैं, कृपया ध्यान दें कि स्वचालित अनुवादों में त्रुटियाँ या अक्षमताएँ हो सकती हैं। मूल दस्तावेज़ जिसकी भाषा में लिखा गया है, उसे अधिकारिक स्रोत माना जाना चाहिए। संवेदनशील जानकारी के लिए पेशेवर मानव अनुवाद की सलाह दी जाती है। इस अनुवाद के उपयोग से उत्पन्न किसी भी गलतफहमी या गलत व्याख्या के लिए हम जिम्मेदार नहीं हैं।
<!-- CO-OP TRANSLATOR DISCLAIMER END -->