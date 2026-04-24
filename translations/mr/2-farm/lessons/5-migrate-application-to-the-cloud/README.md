# आपले अनुप्रयोग लॉजिक क्लाउडमध्ये स्थलांतरित करा

![या धड्याचा स्केच नोट आढावा](../../../../../translated_images/mr/lesson-9.dfe99c8e891f48e1.webp)

> स्केच नोट [नित्य नरसिंहन](https://github.com/nitya) यांनी तयार केले. मोठ्या आवृत्तीसाठी प्रतिमेवर क्लिक करा.

हा धडा [IoT for Beginners Project 2 - Digital Agriculture series](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) चा भाग म्हणून [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn) कडून शिकवला गेला.

[![आपल्या IoT डिव्हाइसला सर्व्हरलेस कोडसह नियंत्रित करा](https://img.youtube.com/vi/VVZDcs5u1_I/0.jpg)](https://youtu.be/VVZDcs5u1_I)

## पूर्व-व्याख्यान प्रश्नमंजुषा

[पूर्व-व्याख्यान प्रश्नमंजुषा](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/17)

## परिचय

मागील धड्यात, आपण आपल्या वनस्पतीच्या मातीतील आर्द्रता निरीक्षण आणि रिले नियंत्रण क्लाउड-आधारित IoT सेवेशी कसे जोडायचे ते शिकले. पुढील पायरी म्हणजे रिलेच्या वेळेचे नियंत्रण करणारा सर्व्हर कोड क्लाउडमध्ये हलवणे. या धड्यात आपण सर्व्हरलेस फंक्शन्स वापरून हे कसे करायचे ते शिकाल.

या धड्यात आपण शिकणार आहात:

* [सर्व्हरलेस म्हणजे काय?](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [सर्व्हरलेस अनुप्रयोग तयार करा](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [IoT Hub इव्हेंट ट्रिगर तयार करा](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [सर्व्हरलेस कोडमधून थेट पद्धतीच्या विनंत्या पाठवा](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [आपला सर्व्हरलेस कोड क्लाउडमध्ये तैनात करा](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)

## सर्व्हरलेस म्हणजे काय?

सर्व्हरलेस, किंवा सर्व्हरलेस संगणन, यामध्ये लहान कोड ब्लॉक्स तयार करणे समाविष्ट आहे जे विविध प्रकारच्या घटनांवर प्रतिसाद म्हणून क्लाउडमध्ये चालवले जातात. जेव्हा घटना घडते तेव्हा आपला कोड चालतो आणि त्या घटनेबद्दल डेटा दिला जातो. या घटना वेगवेगळ्या गोष्टींमधून येऊ शकतात, जसे की वेब विनंत्या, संदेश एका रांगेत ठेवणे, डेटाबेसमधील डेटामध्ये बदल, किंवा IoT डिव्हाइसद्वारे IoT सेवेला पाठवलेले संदेश.

![IoT सेवेमधून सर्व्हरलेस सेवेला पाठवले जाणारे संदेश, एकाच वेळी अनेक फंक्शन्सद्वारे प्रक्रिया केली जात आहे](../../../../../translated_images/mr/iot-messages-to-serverless.0194da1cc0732bb7.webp)

> 💁 जर तुम्ही पूर्वी डेटाबेस ट्रिगर्स वापरले असतील, तर तुम्ही याला त्याचप्रमाणे विचार करू शकता, जिथे कोड एखाद्या घटनेने ट्रिगर केला जातो, जसे की एखाद्या पंक्तीची नोंद करणे.

![जेव्हा अनेक घटना एकाच वेळी पाठवल्या जातात, तेव्हा सर्व्हरलेस सेवा त्या सर्वांना एकाच वेळी चालवण्यासाठी स्केल करते](../../../../../translated_images/mr/serverless-scaling.f8c769adf0413fd1.webp)

आपला कोड फक्त घटना घडल्यावर चालतो, इतर वेळी आपला कोड जिवंत ठेवण्यासाठी काहीही नाही. घटना घडते, आपला कोड लोड होतो आणि चालतो. यामुळे सर्व्हरलेस अत्यंत स्केलेबल बनते - जर अनेक घटना एकाच वेळी घडल्या, तर क्लाउड प्रदाता आपले फंक्शन जितक्या वेळा आवश्यक असेल तितक्या वेळा चालवू शकतो, त्यांच्या उपलब्ध सर्व्हर्सवर. याचा तोटा असा आहे की जर तुम्हाला घटनांमध्ये माहिती सामायिक करायची असेल, तर तुम्हाला ती मेमरीमध्ये साठवण्याऐवजी डेटाबेससारख्या ठिकाणी साठवावी लागेल.

आपला कोड एका फंक्शन म्हणून लिहिला जातो जो घटनेबद्दल तपशील पॅरामीटर म्हणून घेतो. आपण या सर्व्हरलेस फंक्शन्स लिहिण्यासाठी अनेक प्रोग्रामिंग भाषा वापरू शकता.

> 🎓 सर्व्हरलेसला फंक्शन्स अ‍ॅज अ सर्व्हिस (FaaS) असेही संबोधले जाते कारण प्रत्येक इव्हेंट ट्रिगर कोडमध्ये फंक्शन म्हणून अंमलात आणला जातो.

नाव असूनही, सर्व्हरलेस प्रत्यक्षात सर्व्हर्स वापरते. हे नाव असे आहे कारण तुम्ही एक विकसक म्हणून आपला कोड चालवण्यासाठी आवश्यक असलेल्या सर्व्हर्सबद्दल काळजी करत नाही, तुम्हाला फक्त एवढेच महत्त्वाचे आहे की आपला कोड एखाद्या घटनेला प्रतिसाद म्हणून चालतो. क्लाउड प्रदात्याकडे सर्व्हरलेस *रनटाइम* असते जे सर्व्हर्स, नेटवर्किंग, स्टोरेज, CPU, मेमरी आणि आपला कोड चालवण्यासाठी आवश्यक असलेल्या इतर सर्व गोष्टींचे व्यवस्थापन करते. या मॉडेलचा अर्थ असा आहे की तुम्ही सेवा वापरण्यासाठी प्रति सर्व्हर पैसे देऊ शकत नाही, कारण तेथे कोणताही सर्व्हर नाही. त्याऐवजी तुम्ही तुमचा कोड चालत असलेल्या वेळेसाठी आणि वापरलेल्या मेमरीच्या प्रमाणासाठी पैसे देता.

> 💰 सर्व्हरलेस हा क्लाउडमध्ये कोड चालवण्याचा सर्वात स्वस्त मार्ग आहे. उदाहरणार्थ, लेखनाच्या वेळी, एक क्लाउड प्रदाता आपले सर्व सर्व्हरलेस फंक्शन्स एकत्रितपणे महिन्यात 1,000,000 वेळा चालवू देतो, त्यानंतर ते US$0.20 प्रति 1,000,000 कार्यान्वयनासाठी शुल्क आकारतात. जेव्हा आपला कोड चालत नाही, तेव्हा तुम्ही पैसे देत नाही.

IoT विकसक म्हणून, सर्व्हरलेस मॉडेल आदर्श आहे. तुम्ही एक फंक्शन लिहू शकता जे क्लाउड-होस्ट केलेल्या IoT सेवेशी जोडलेल्या कोणत्याही IoT डिव्हाइसद्वारे पाठवलेल्या संदेशांना प्रतिसाद म्हणून कॉल केले जाते. आपला कोड पाठवलेले सर्व संदेश हाताळेल, परंतु फक्त आवश्यक तेव्हा चालू असेल.

✅ तुम्ही MQTT वर संदेश ऐकण्यासाठी सर्व्हर कोड म्हणून लिहिलेला कोड पुन्हा पहा. हे सर्व्हरलेस वापरून क्लाउडमध्ये कसे चालेल? सर्व्हरलेस संगणनासाठी समर्थन देण्यासाठी कोड कसा बदलला जाऊ शकतो असे तुम्हाला वाटते?

> 💁 सर्व्हरलेस मॉडेल कोड चालवण्याव्यतिरिक्त इतर क्लाउड सेवांमध्ये हलत आहे. उदाहरणार्थ, क्लाउडमध्ये सर्व्हरलेस डेटाबेस उपलब्ध आहेत जे सर्व्हरलेस किंमतीच्या मॉडेलचा वापर करतात जिथे तुम्ही डेटाबेसवर केलेल्या प्रत्येक विनंतीसाठी पैसे देता, जसे की क्वेरी किंवा इन्सर्ट, सहसा विनंती पूर्ण करण्यासाठी किती काम केले जाते यावर आधारित किंमतीचा वापर करून. उदाहरणार्थ, प्राथमिक कीवर एका पंक्तीची निवड एका पंक्तीच्या तुलनेत कमी खर्चिक असेल ज्यामध्ये अनेक टेबल्स जोडणे आणि हजारो पंक्ती परत करणे समाविष्ट आहे.

## सर्व्हरलेस अनुप्रयोग तयार करा

Microsoft कडून सर्व्हरलेस संगणन सेवा Azure Functions म्हणून ओळखली जाते.

![Azure Functions लोगो](../../../../../translated_images/mr/azure-functions-logo.1cfc8e3204c9c44a.webp)

खालील लघु व्हिडिओमध्ये Azure Functions चे आढावा दिला आहे.

[![Azure Functions आढावा व्हिडिओ](https://img.youtube.com/vi/8-jz5f_JyEQ/0.jpg)](https://www.youtube.com/watch?v=8-jz5f_JyEQ)

> 🎥 वरच्या प्रतिमेवर क्लिक करून व्हिडिओ पहा.

✅ थोडा वेळ घ्या आणि Azure Functions च्या [Microsoft Azure Functions दस्तऐवज](https://docs.microsoft.com/azure/azure-functions/functions-overview?WT.mc_id=academic-17441-jabenn) मध्ये आढावा वाचा.

Azure Functions लिहिण्यासाठी, तुम्ही तुमच्या पसंतीच्या भाषेत Azure Functions अ‍ॅपसह सुरुवात करता. Azure Functions Python, JavaScript, TypeScript, C#, F#, Java, आणि Powershell ला समर्थन देते. या धड्यात तुम्ही Python मध्ये Azure Functions अ‍ॅप कसे लिहायचे ते शिकाल.

> 💁 Azure Functions कस्टम हँडलर्सला देखील समर्थन देते त्यामुळे तुम्ही HTTP विनंत्यांना समर्थन देणाऱ्या कोणत्याही भाषेत तुमचे फंक्शन्स लिहू शकता, ज्यामध्ये COBOL सारख्या जुन्या भाषांचा समावेश आहे.

Functions अ‍ॅप्समध्ये एक किंवा अधिक *ट्रिगर्स* असतात - घटना प्रतिसाद देणारे फंक्शन्स. तुम्ही एका Functions अ‍ॅपमध्ये अनेक ट्रिगर्स असू शकता, जे सर्व सामान्य कॉन्फिगरेशन सामायिक करतात. उदाहरणार्थ, तुमच्या Functions अ‍ॅपसाठी कॉन्फिगरेशन फाइलमध्ये तुमच्या IoT Hub चे कनेक्शन तपशील असू शकतात आणि अ‍ॅपमधील सर्व फंक्शन्स हे कनेक्ट करण्यासाठी आणि घटनांसाठी ऐकण्यासाठी वापरू शकतात.

### कार्य - Azure Functions टूलिंग स्थापित करा

> लेखनाच्या वेळी, Azure Functions कोड टूल्स Python प्रकल्पांसह Apple Silicon वर पूर्णपणे कार्यरत नाहीत. तुम्हाला Intel-आधारित Mac, Windows PC, किंवा Linux PC वापरावा लागेल.

Azure Functions चे एक उत्तम वैशिष्ट्य म्हणजे तुम्ही ते स्थानिक पातळीवर चालवू शकता. क्लाउडमध्ये वापरलेला तोच रनटाइम तुमच्या संगणकावर चालवता येतो, ज्यामुळे तुम्ही IoT संदेशांना प्रतिसाद देणारा कोड लिहू शकता आणि तो स्थानिक पातळीवर चालवू शकता. तुम्ही घटना हाताळताना तुमचा कोड डीबग देखील करू शकता. एकदा तुम्ही तुमच्या कोडवर समाधानी झाल्यावर, तो क्लाउडमध्ये तैनात केला जाऊ शकतो.

Azure Functions टूलिंग CLI म्हणून उपलब्ध आहे, ज्याला Azure Functions Core Tools म्हणतात.

1. Azure Functions Core Tools स्थापित करण्यासाठी [Azure Functions Core Tools दस्तऐवज](https://docs.microsoft.com/azure/azure-functions/functions-run-local?WT.mc_id=academic-17441-jabenn) मधील सूचनांचे अनुसरण करा.

1. VS Code साठी Azure Functions विस्तार स्थापित करा. हा विस्तार Azure Functions तयार करणे, डीबग करणे आणि तैनात करणे यासाठी समर्थन प्रदान करतो. VS Code मध्ये हा विस्तार स्थापित करण्याच्या सूचनांसाठी [Azure Functions विस्तार दस्तऐवज](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-azuretools.vscode-azurefunctions) पहा.

जेव्हा तुम्ही तुमचे Azure Functions अ‍ॅप क्लाउडमध्ये तैनात करता, तेव्हा त्याला अनुप्रयोग फाइल्स आणि लॉग फाइल्ससारख्या गोष्टी संग्रहित करण्यासाठी थोडी क्लाउड स्टोरेज वापरण्याची आवश्यकता असते. जेव्हा तुम्ही तुमचे Functions अ‍ॅप स्थानिक पातळीवर चालवता, तेव्हा तुम्हाला क्लाउड स्टोरेजशी कनेक्ट करणे आवश्यक आहे, परंतु वास्तविक क्लाउड स्टोरेज वापरण्याऐवजी, तुम्ही [Azurite](https://github.com/Azure/Azurite) नावाचा स्टोरेज एम्युलेटर वापरू शकता. हे स्थानिक पातळीवर चालते परंतु क्लाउड स्टोरेजसारखे कार्य करते.

> 🎓 Azure मध्ये, Azure Functions वापरत असलेले स्टोरेज हे Azure Storage Account आहे. या खात्यांमध्ये फाइल्स, ब्लॉब्स, टेबल्समधील डेटा किंवा रांगेतील डेटा संग्रहित केला जाऊ शकतो. तुम्ही अनेक अ‍ॅप्समध्ये एक स्टोरेज खाते सामायिक करू शकता, जसे की Functions अ‍ॅप आणि वेब अ‍ॅप.

1. Azurite हे Node.js अ‍ॅप आहे, त्यामुळे तुम्हाला Node.js स्थापित करावे लागेल. तुम्ही [Node.js वेबसाइट](https://nodejs.org/) वर डाउनलोड आणि स्थापना सूचनांचा शोध घेऊ शकता. जर तुम्ही Mac वापरत असाल, तर तुम्ही ते [Homebrew](https://formulae.brew.sh/formula/node) वरून देखील स्थापित करू शकता.

1. खालील आदेश वापरून Azurite स्थापित करा (`npm` हे Node.js स्थापित करताना स्थापित होणारे एक साधन आहे):

    ```sh
    npm install -g azurite
    ```

1. Azurite साठी डेटा संग्रहित करण्यासाठी `azurite` नावाचा फोल्डर तयार करा:

    ```sh
    mkdir azurite
    ```

1. Azurite चालवा, या नवीन फोल्डरला पास करत:

    ```sh
    azurite --location azurite
    ```

    Azurite स्टोरेज एम्युलेटर लॉन्च होईल आणि स्थानिक Functions रनटाइम कनेक्ट करण्यासाठी तयार असेल.

    ```output
    ➜  ~ azurite --location azurite  
    Azurite Blob service is starting at http://127.0.0.1:10000
    Azurite Blob service is successfully listening at http://127.0.0.1:10000
    Azurite Queue service is starting at http://127.0.0.1:10001
    Azurite Queue service is successfully listening at http://127.0.0.1:10001
    Azurite Table service is starting at http://127.0.0.1:10002
    Azurite Table service is successfully listening at http://127.0.0.1:10002
    ```

### कार्य - Azure Functions प्रकल्प तयार करा

Azure Functions CLI नवीन Functions अ‍ॅप तयार करण्यासाठी वापरले जाऊ शकते.

1. तुमच्या Functions अ‍ॅपसाठी एक फोल्डर तयार करा आणि त्यात जा. त्याला `soil-moisture-trigger` असे नाव द्या.

    ```sh
    mkdir soil-moisture-trigger
    cd soil-moisture-trigger
    ```

1. या फोल्डरमध्ये Python व्हर्च्युअल एन्व्हायर्नमेंट तयार करा:

    ```sh
    python3 -m venv .venv
    ```

1. व्हर्च्युअल एन्व्हायर्नमेंट सक्रिय करा:

    * Windows वर:
        * जर तुम्ही Command Prompt किंवा Windows Terminal मधून Command Prompt वापरत असाल, तर चालवा:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * जर तुम्ही PowerShell वापरत असाल, तर चालवा:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

    * macOS किंवा Linux वर, चालवा:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 हे आदेश तुम्ही व्हर्च्युअल एन्व्हायर्नमेंट तयार केलेल्या ठिकाणाहून चालवले पाहिजेत. तुम्हाला `.venv` फोल्डरमध्ये कधीही जावे लागणार नाही, तुम्ही नेहमी सक्रिय आदेश आणि पॅकेजेस स्थापित करण्यासाठी किंवा कोड चालवण्यासाठी आदेश चालवले पाहिजेत त्या ठिकाणाहून जेव्हा तुम्ही व्हर्च्युअल एन्व्हायर्नमेंट तयार केले होते.

1. या फोल्डरमध्ये Functions अ‍ॅप तयार करण्यासाठी खालील आदेश चालवा:

    ```sh
    func init --worker-runtime python soil-moisture-trigger
    ```

    यामुळे वर्तमान फोल्डरमध्ये तीन फाइल्स तयार होतील:

    * `host.json` - ही JSON दस्तऐवज तुमच्या Functions अ‍ॅपसाठी सेटिंग्ज समाविष्ट करते. तुम्हाला या सेटिंग्ज बदलण्याची आवश्यकता नाही.
    * `local.settings.json` - ही JSON दस्तऐवज तुमचे अ‍ॅप स्थानिक पातळीवर चालवताना वापरले जाणारे सेटिंग्ज समाविष्ट करते, जसे की तुमच्या IoT Hub साठी कनेक्शन स्ट्रिंग्ज. ही सेटिंग्ज स्थानिक आहेत आणि स्रोत कोड नियंत्रणात जोडल्या जाऊ नयेत. जेव्हा तुम्ही अ‍ॅप क्लाउडमध्ये तैनात करता, तेव्हा ही सेटिंग्ज तैनात केल्या जात नाहीत, त्याऐवजी तुमच्या सेटिंग्ज अनुप्रयोग सेटिंग्जमधून लोड केल्या जातात. हे नंतर या धड्यात कव्हर केले जाईल.
    * `requirements.txt` - ही [Pip requirements फाइल](https://pip.pypa.io/en/stable/user_guide/#requirements-files) आहे जी तुमच्या Functions अ‍ॅप चालवण्यासाठी आवश्यक Pip पॅकेजेस समाविष्ट करते.

1. `local.settings.json` फाइलमध्ये Functions अ‍ॅप वापरणाऱ्या स्टोरेज अकाउंटसाठी सेटिंग आहे. हे डीफॉल्ट सेटिंग रिकामे आहे, त्यामुळे ते सेट करणे आवश्यक आहे. Azurite स्थानिक स्टोरेज एम्युलेटरशी कनेक्ट करण्यासाठी, ही किंमत खालीलप्रमाणे सेट करा:

    ```json
    "AzureWebJobsStorage": "UseDevelopmentStorage=true",
    ```

1. आवश्यक Pip पॅकेजेस `requirements.txt` फाइल वापरून स्थापित करा:

    ```sh
    pip install -r requirements.txt
    ```

    > 💁 आवश्यक Pip पॅकेजेस या फाइलमध्ये असणे आवश्यक आहे, जेणेकरून जेव्हा Functions अ‍ॅप क्लाउडमध्ये तैनात केला जातो, तेव्हा रनटाइम योग्य पॅकेजेस स्थापित करतो याची खात्री करू शकतो.

1. सर्व काही योग्य प्रकारे कार्य करत आहे की नाही हे तपासण्यासाठी, तुम्ही Functions रनटाइम सुरू करू शकता. हे करण्यासाठी खालील आदेश चालवा:

    ```sh
    func start
    ```

    तुम्हाला रनटाइम सुरू होताना दिसेल आणि ते कोणतेही जॉब फंक्शन्स (ट्रिगर्स) सापडले नाहीत असे रिपोर्ट करेल.

    ```output
    (.venv) ➜  soil-moisture-trigger func start
    Found Python version 3.9.1 (python3).
    
    Azure Functions Core Tools
    Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    Function Runtime Version: 3.0.15417.0
    
    [2021-05-05T01:24:46.795Z] No job functions found.
    ```
> ⚠️ जर तुम्हाला फायरवॉल सूचना मिळाली, तर प्रवेश मंजूर करा कारण `func` अनुप्रयोगाला तुमच्या नेटवर्कवर वाचन आणि लेखन करण्याची आवश्यकता आहे.
> ⚠️ जर तुम्ही macOS वापरत असाल, तर आउटपुटमध्ये काही चेतावणी दिसू शकतात:
>
> ```output
    > (.venv) ➜  soil-moisture-trigger func start
    > Found Python version 3.9.1 (python3).
    >
    > Azure Functions Core Tools
    > Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    > Function Runtime Version: 3.0.15417.0
    >
    > [2021-06-16T08:18:28.315Z] Cannot create directory for shared memory usage: /dev/shm/AzureFunctions
    > [2021-06-16T08:18:28.316Z] System.IO.FileSystem: Access to the path '/dev/shm/AzureFunctions' is denied. Operation not permitted.
    > [2021-06-16T08:18:30.361Z] No job functions found.
    > ```
>
> जर Functions अ‍ॅप योग्य प्रकारे सुरू होत असेल आणि चालू असलेल्या फंक्शन्सची यादी दाखवत असेल, तर तुम्ही या चेतावणींकडे दुर्लक्ष करू शकता. [Microsoft Docs Q&A वरच्या या प्रश्नात](https://docs.microsoft.com/answers/questions/396617/azure-functions-core-tools-error-osx-devshmazurefu.html?WT.mc_id=academic-17441-jabenn) नमूद केल्याप्रमाणे, याकडे दुर्लक्ष करणे योग्य आहे.

1. `ctrl+c` दाबून Functions अ‍ॅप थांबवा.

1. VS Code मध्ये सध्याचा फोल्डर उघडा, VS Code उघडून हा फोल्डर उघडा किंवा खालील कमांड चालवा:

    ```sh
    code .
    ```

    VS Code तुमचा Functions प्रोजेक्ट ओळखेल आणि एक सूचना दाखवेल:

    ```output
    Detected an Azure Functions Project in folder "soil-moisture-trigger" that may have been created outside of
    VS Code. Initialize for optimal use with VS Code?
    ```

    ![सूचना](../../../../../translated_images/mr/vscode-azure-functions-init-notification.bd19b49229963edb.webp)

    या सूचनेतून **Yes** निवडा.

1. VS Code टर्मिनलमध्ये Python virtual environment चालू असल्याची खात्री करा. गरज असल्यास ते थांबवा आणि पुन्हा सुरू करा.

## IoT Hub इव्हेंट ट्रिगर तयार करा

Functions अ‍ॅप हे तुमच्या serverless कोडचे शेल आहे. IoT Hub इव्हेंट्सला प्रतिसाद देण्यासाठी, तुम्ही या अ‍ॅपमध्ये IoT Hub ट्रिगर जोडू शकता. हा ट्रिगर IoT Hub कडे पाठवलेल्या संदेशांच्या प्रवाहाशी कनेक्ट होतो आणि त्यांना प्रतिसाद देतो. हा संदेश प्रवाह मिळवण्यासाठी, तुमच्या ट्रिगरला IoT Hub च्या *event hub compatible endpoint* शी कनेक्ट करावे लागेल.

IoT Hub हे Azure Event Hubs नावाच्या दुसऱ्या Azure सेवेसाठी आधारित आहे. Event Hubs ही सेवा संदेश पाठवण्यासाठी आणि प्राप्त करण्यासाठी वापरली जाते, IoT Hub यामध्ये IoT devices साठी अतिरिक्त वैशिष्ट्ये जोडते. IoT Hub मधून संदेश वाचण्यासाठी कनेक्ट करण्याचा मार्ग Event Hubs वापरत असाल तर तसाच आहे.

✅ संशोधन करा: [Azure Event Hubs दस्तऐवज](https://docs.microsoft.com/azure/event-hubs/event-hubs-about?WT.mc_id=academic-17441-jabenn) मध्ये Event Hubs चा आढावा वाचा. मूलभूत वैशिष्ट्ये IoT Hub शी कशी तुलना करतात?

IoT डिव्हाइसला IoT Hub शी कनेक्ट होण्यासाठी एक गुप्त की वापरावी लागते, ज्यामुळे फक्त परवानगी असलेल्या डिव्हाइसला कनेक्ट करता येते. संदेश वाचण्यासाठी कनेक्ट करताना देखील हेच लागू होते, तुमच्या कोडला गुप्त की असलेली कनेक्शन स्ट्रिंग आवश्यक आहे, ज्यामध्ये IoT Hub च्या तपशीलांचा समावेश आहे.

> 💁 तुम्हाला मिळणारी default connection string मध्ये **iothubowner** परवानग्या असतात, ज्यामुळे ती वापरणाऱ्या कोणत्याही कोडला IoT Hub वर पूर्ण परवानग्या मिळतात. आदर्शतः तुम्ही आवश्यक असलेल्या किमान परवानग्यांसह कनेक्ट केले पाहिजे. हे पुढील धड्यात कव्हर केले जाईल.

एकदा तुमचा ट्रिगर कनेक्ट झाल्यावर, IoT Hub कडे पाठवलेल्या प्रत्येक संदेशासाठी फंक्शनमधील कोड कॉल केला जाईल, डिव्हाइस कोणतेही असो. ट्रिगरला संदेश एक पॅरामीटर म्हणून दिला जाईल.

### कार्य - Event Hub compatible endpoint कनेक्शन स्ट्रिंग मिळवा

1. VS Code टर्मिनलमधून खालील कमांड चालवा, ज्यामुळे IoT Hub च्या Event Hub compatible endpoint साठी कनेक्शन स्ट्रिंग मिळेल:

    ```sh
    az iot hub connection-string show --default-eventhub \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    `<hub_name>` ला तुमच्या IoT Hub साठी वापरलेल्या नावाने बदला.

1. VS Code मध्ये `local.settings.json` फाइल उघडा. `Values` विभागात खालील अतिरिक्त मूल्य जोडा:

    ```json
    "IOT_HUB_CONNECTION_STRING": "<connection string>"
    ```

    `<connection string>` ला मागील टप्प्यातून मिळालेल्या मूल्याने बदला. हे वैध JSON बनवण्यासाठी वरच्या ओळीच्या शेवटी एक अल्पविराम जोडावा लागेल.

### कार्य - इव्हेंट ट्रिगर तयार करा

आता तुम्ही इव्हेंट ट्रिगर तयार करण्यासाठी तयार आहात.

1. VS Code टर्मिनलमधून `soil-moisture-trigger` फोल्डरमध्ये खालील कमांड चालवा:

    ```sh
    func new --name iot-hub-trigger --template "Azure Event Hub trigger"
    ```

    यामुळे `iot-hub-trigger` नावाचे नवीन Function तयार होईल. ट्रिगर IoT Hub च्या Event Hub compatible endpoint शी कनेक्ट होईल, त्यामुळे तुम्ही Event Hub ट्रिगर वापरू शकता. IoT Hub साठी विशिष्ट ट्रिगर नाही.

यामुळे `soil-moisture-trigger` फोल्डरमध्ये `iot-hub-trigger` नावाचा फोल्डर तयार होईल, ज्यामध्ये खालील फाइल्स असतील:

* `__init__.py` - ही Python कोड फाइल आहे ज्यामध्ये ट्रिगर आहे, Python मॉड्यूलमध्ये फोल्डर बदलण्यासाठी मानक Python फाइल नावाचा वापर केला जातो.

    या फाइलमध्ये खालील कोड असेल:

    ```python
    import logging

    import azure.functions as func


    def main(event: func.EventHubEvent):
        logging.info('Python EventHub trigger processed an event: %s',
                    event.get_body().decode('utf-8'))
    ```

    ट्रिगरचा मुख्य भाग `main` फंक्शन आहे. IoT Hub मधून इव्हेंट्ससह हे फंक्शन कॉल केले जाते. या फंक्शनमध्ये `event` नावाचा पॅरामीटर आहे, ज्यामध्ये `EventHubEvent` असतो. IoT Hub कडे प्रत्येक संदेश पाठवला जातो तेव्हा, हे फंक्शन `event` म्हणून संदेशासह कॉल केले जाते, तसेच मागील धड्यात पाहिलेल्या annotations प्रमाणे गुणधर्मांसह.

    या फंक्शनचा मुख्य भाग इव्हेंट लॉग करतो.

* `function.json` - यात ट्रिगरसाठी कॉन्फिगरेशन आहे. मुख्य कॉन्फिगरेशन `bindings` नावाच्या विभागात आहे. Binding म्हणजे Azure Functions आणि इतर Azure सेवांमधील कनेक्शनसाठी वापरले जाणारे टर्म आहे. या फंक्शनमध्ये Event Hub शी कनेक्ट होण्यासाठी एक input binding आहे आणि डेटा प्राप्त केला जातो.

    > 💁 तुम्ही output bindings देखील ठेवू शकता, ज्यामुळे फंक्शनचा आउटपुट दुसऱ्या सेवेला पाठवला जातो. उदाहरणार्थ, तुम्ही डेटाबेससाठी output binding जोडू शकता आणि IoT Hub इव्हेंट फंक्शनमधून परत करू शकता, ज्यामुळे तो डेटाबेसमध्ये आपोआप समाविष्ट होईल.

    ✅ संशोधन करा: [Azure Functions triggers and bindings concepts दस्तऐवज](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python) मध्ये bindings बद्दल वाचा.

    `bindings` विभागात binding साठी कॉन्फिगरेशन समाविष्ट आहे. महत्त्वाच्या मूल्ये खालीलप्रमाणे आहेत:

  * `"type": "eventHubTrigger"` - यामुळे फंक्शनला Event Hub मधून इव्हेंट्स ऐकण्याची आवश्यकता असल्याचे सांगितले जाते.
  * `"name": "events"` - Event Hub इव्हेंट्ससाठी वापरण्यासाठी पॅरामीटरचे नाव. Python कोडमधील `main` फंक्शनमधील पॅरामीटर नावाशी हे जुळते.
  * `"direction": "in"` - हे एक input binding आहे, Event Hub मधून डेटा फंक्शनमध्ये येतो.
  * `"connection": ""` - हे सेटिंगमधून कनेक्शन स्ट्रिंग वाचण्यासाठी सेटिंगचे नाव परिभाषित करते. स्थानिकपणे चालवताना, हे `local.settings.json` फाइलमधून हे सेटिंग वाचेल.

    > 💁 कनेक्शन स्ट्रिंग `function.json` फाइलमध्ये संग्रहित केली जाऊ शकत नाही, ती सेटिंगमधून वाचली पाहिजे. यामुळे तुमची कनेक्शन स्ट्रिंग चुकून उघड होण्यापासून रोखली जाते.

1. [Azure Functions template मधील बग](https://github.com/Azure/azure-functions-templates/issues/1250) मुळे, `function.json` मध्ये `cardinality` फील्डसाठी चुकीचे मूल्य आहे. या फील्डचे मूल्य `many` वरून `one` मध्ये अपडेट करा:

    ```json
    "cardinality": "one",
    ```

1. `function.json` फाइलमधील `"connection"` चे मूल्य `local.settings.json` फाइलमध्ये जोडलेल्या नवीन मूल्याकडे निर्देश करण्यासाठी अपडेट करा:

    ```json
    "connection": "IOT_HUB_CONNECTION_STRING",
    ```

    > 💁 लक्षात ठेवा - हे सेटिंगकडे निर्देश करणे आवश्यक आहे, प्रत्यक्ष कनेक्शन स्ट्रिंग समाविष्ट करू नका.

1. कनेक्शन स्ट्रिंगमध्ये `eventHubName` मूल्य समाविष्ट आहे, त्यामुळे `function.json` फाइलमधील या मूल्यासाठी रिकामी स्ट्रिंग ठेवणे आवश्यक आहे. या मूल्याला रिकामी स्ट्रिंगमध्ये अपडेट करा:

    ```json
    "eventHubName": "",
    ```

### कार्य - इव्हेंट ट्रिगर चालवा

1. IoT Hub इव्हेंट मॉनिटर चालू नसल्याची खात्री करा. जर हे Functions अ‍ॅपसोबत चालू असेल, तर Functions अ‍ॅप कनेक्ट होऊ शकणार नाही आणि इव्हेंट्स वापरू शकणार नाही.

    > 💁 अनेक अ‍ॅप्स IoT Hub endpoints शी वेगवेगळ्या *consumer groups* वापरून कनेक्ट होऊ शकतात. हे पुढील धड्यात कव्हर केले जाईल.

1. Functions अ‍ॅप चालवण्यासाठी, VS Code टर्मिनलमधून खालील कमांड चालवा:

    ```sh
    func start
    ```

    Functions अ‍ॅप सुरू होईल आणि `iot-hub-trigger` फंक्शन शोधेल. त्यानंतर IoT Hub कडे मागील दिवसात पाठवलेल्या इव्हेंट्स प्रक्रिया करेल.

    ```output
    (.venv) ➜  soil-moisture-trigger func start
    Found Python version 3.9.1 (python3).
    
    Azure Functions Core Tools
    Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    Function Runtime Version: 3.0.15417.0
    
    Functions:
    
            iot-hub-trigger: eventHubTrigger
    
    For detailed output, run func with --verbose flag.
    [2021-05-05T02:44:07.517Z] Worker process started and initialized.
    [2021-05-05T02:44:09.202Z] Executing 'Functions.iot-hub-trigger' (Reason='(null)', Id=802803a5-eae9-4401-a1f4-176631456ce4)
    [2021-05-05T02:44:09.205Z] Trigger Details: PartitionId: 0, Offset: 1011240-1011632, EnqueueTimeUtc: 2021-05-04T19:04:04.2030000Z-2021-05-04T19:04:04.3900000Z, SequenceNumber: 2546-2547, Count: 2
    [2021-05-05T02:44:09.352Z] Python EventHub trigger processed an event: {"soil_moisture":628}
    [2021-05-05T02:44:09.354Z] Python EventHub trigger processed an event: {"soil_moisture":624}
    [2021-05-05T02:44:09.395Z] Executed 'Functions.iot-hub-trigger' (Succeeded, Id=802803a5-eae9-4401-a1f4-176631456ce4, Duration=245ms)
    ```

    प्रत्येक फंक्शन कॉल `Executing 'Functions.iot-hub-trigger'`/`Executed 'Functions.iot-hub-trigger'` ब्लॉकमध्ये आउटपुटमध्ये दिसेल, त्यामुळे प्रत्येक फंक्शन कॉलमध्ये किती संदेश प्रक्रिया झाले हे तुम्हाला दिसेल.

1. तुमचे IoT डिव्हाइस चालू असल्याची खात्री करा. तुम्हाला Functions अ‍ॅपमध्ये नवीन soil moisture संदेश दिसतील.

1. Functions अ‍ॅप थांबवा आणि पुन्हा सुरू करा. तुम्हाला दिसेल की ते मागील संदेश पुन्हा प्रक्रिया करणार नाही, फक्त नवीन संदेश प्रक्रिया करेल.

> 💁 VS Code तुमच्या Functions साठी debugging देखील सपोर्ट करते. तुम्ही कोडच्या प्रत्येक ओळीच्या सुरुवातीला क्लिक करून, किंवा कोडच्या ओळीवर कर्सर ठेवून *Run -> Toggle breakpoint* निवडून, किंवा `F9` दाबून break points सेट करू शकता. तुम्ही *Run -> Start debugging* निवडून, `F5` दाबून, किंवा *Run and debug* पॅन निवडून **Start debugging** बटण निवडून debugger सुरू करू शकता. असे केल्याने तुम्ही प्रक्रिया होत असलेल्या इव्हेंट्सचे तपशील पाहू शकता.

#### समस्या सोडवणे

* जर तुम्हाला खालील त्रुटी मिळाली:

    ```output
    The listener for function 'Functions.iot-hub-trigger' was unable to start. Microsoft.WindowsAzure.Storage: Connection refused. System.Net.Http: Connection refused. System.Private.CoreLib: Connection refused.
    ```

    Azurite चालू आहे आणि तुम्ही `local.settings.json` फाइलमध्ये `AzureWebJobsStorage` `UseDevelopmentStorage=true` सेट केले आहे याची खात्री करा.

* जर तुम्हाला खालील त्रुटी मिळाली:

    ```output
    System.Private.CoreLib: Exception while executing function: Functions.iot-hub-trigger. System.Private.CoreLib: Result: Failure Exception: AttributeError: 'list' object has no attribute 'get_body'
    ```

    तुम्ही `function.json` फाइलमध्ये `cardinality` `one` मध्ये सेट केले आहे याची खात्री करा.

* जर तुम्हाला खालील त्रुटी मिळाली:

    ```output
    Azure.Messaging.EventHubs: The path to an Event Hub may be specified as part of the connection string or as a separate value, but not both.  Please verify that your connection string does not have the `EntityPath` token if you are passing an explicit Event Hub name. (Parameter 'connectionString').
    ```

    तुम्ही `function.json` फाइलमध्ये `eventHubName` रिकामी स्ट्रिंगमध्ये सेट केली आहे याची खात्री करा.

## serverless कोडमधून थेट पद्धतीने विनंत्या पाठवा

आत्तापर्यंत तुमचे Functions अ‍ॅप Event Hub compatible endpoint वापरून IoT Hub मधून संदेश ऐकत आहे. आता तुम्हाला IoT डिव्हाइसला कमांड्स पाठवायच्या आहेत. हे IoT Hub शी *Registry Manager* वापरून वेगळ्या कनेक्शनद्वारे केले जाते. Registry Manager हे एक साधन आहे जे तुम्हाला IoT Hub मध्ये नोंदणीकृत डिव्हाइस पाहण्याची आणि cloud-to-device संदेश, थेट पद्धतीने विनंत्या पाठवून किंवा device twin अपडेट करून त्या डिव्हाइसशी संवाद साधण्याची परवानगी देते. तुम्ही IoT Hub मधून डिव्हाइस नोंदणी, अपडेट किंवा हटवण्यासाठी देखील याचा वापर करू शकता.

Registry Manager शी कनेक्ट करण्यासाठी तुम्हाला कनेक्शन स्ट्रिंग आवश्यक आहे.

### कार्य - Registry Manager कनेक्शन स्ट्रिंग मिळवा

1. कनेक्शन स्ट्रिंग मिळवण्यासाठी, खालील कमांड चालवा:

    ```sh
    az iot hub connection-string show --policy-name service \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    `<hub_name>` ला तुमच्या IoT Hub साठी वापरलेल्या नावाने बदला.

    कनेक्शन स्ट्रिंग *ServiceConnect* धोरणासाठी `--policy-name service` पॅरामीटर वापरून विनंती केली जाते. तुम्ही कनेक्शन स्ट्रिंग विनंती करता तेव्हा, तुम्ही त्या कनेक्शन स्ट्रिंगला कोणत्या परवानग्या परवानगी देतील हे निर्दिष्ट करू शकता. ServiceConnect धोरण तुमच्या कोडला IoT डिव्हाइसशी कनेक्ट होऊन संदेश पाठवण्याची परवानगी देते.

    ✅ संशोधन करा: [IoT Hub permissions दस्तऐवज](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-security#iot-hub-permissions?WT.mc_id=academic-17441-jabenn) मध्ये वेगवेगळ्या धोरणांबद्दल वाचा.

1. VS Code मध्ये `local.settings.json` फाइल उघडा. `Values` विभागात खालील अतिरिक्त मूल्य जोडा:

    ```json
    "REGISTRY_MANAGER_CONNECTION_STRING": "<connection string>"
    ```

    `<connection string>` ला मागील टप्प्यातून मिळालेल्या मूल्याने बदला. हे वैध JSON बनवण्यासाठी वरच्या ओळीच्या शेवटी एक अल्पविराम जोडावा लागेल.

### कार्य - डिव्हाइसला थेट पद्धतीने विनंती पाठवा

1. Registry Manager साठी SDK Pip पॅकेजद्वारे उपलब्ध आहे. `requirements.txt` फाइलमध्ये खालील ओळ जोडा:

    ```sh
    azure-iot-hub
    ```

1. VS Code टर्मिनलमध्ये virtual environment सक्रिय असल्याची खात्री करा आणि Pip पॅकेजेस इंस्टॉल करण्यासाठी खालील कमांड चालवा:

    ```sh
    pip install -r requirements.txt
    ```

1. `__init__.py` फाइलमध्ये खालील imports जोडा:

    ```python
    import json
    import os
    from azure.iot.hub import IoTHubRegistryManager
    from azure.iot.hub.models import CloudToDeviceMethod
    ```

    यामध्ये काही सिस्टम लायब्ररी तसेच Registry Manager शी संवाद साधण्यासाठी आणि थेट पद्धतीने विनंती पाठवण्यासाठी लायब्ररी समाविष्ट आहेत.

1. `main` पद्धतीतील कोड काढा, पण पद्धत ठेवा.

1. `main` पद्धतीमध्ये खालील कोड जोडा:

    ```python
    body = json.loads(event.get_body().decode('utf-8'))
    device_id = event.iothub_metadata['connection-device-id']

    logging.info(f'Received message: {body} from {device_id}')
    ```

    हा कोड इव्हेंटचा body काढतो, ज्यामध्ये IoT डिव्हाइसद्वारे पाठवलेला JSON संदेश असतो.

    त्यानंतर इव्हेंटसोबत दिलेल्या annotations मधून डिव्हाइस ID मिळवतो. इव्हेंटचा body टेलिमेट्री म्हणून पाठवलेला संदेश असतो, `iothub_metadata` डिक्शनरीमध्ये IoT Hub ने सेट केलेल्या गुणधर्मांचा समावेश असतो, जसे की पाठवणाऱ्या डिव्हाइसचा ID आणि संदेश पाठवण्याचा वेळ.

    ही माहिती नंतर लॉग केली जाते. तुम्ही Functions अ‍ॅप स्थानिकपणे चालवताना टर्मिनलमध्ये हे लॉगिंग पाहू शकता.

1. याखाली खालील कोड जोडा:

    ```python
    soil_moisture = body['soil_moisture']

    if soil_moisture > 450:
        direct_method = CloudToDeviceMethod(method_name='relay_on', payload='{}')
    else:
        direct_method = CloudToDeviceMethod(method_name='relay_off', payload='{}')
    ```

    हा कोड संदेशातून soil moisture मिळवतो. त्यानंतर soil moisture तपासतो आणि मूल्यावर आधारित `relay_on` किंवा `relay_off` थेट पद्धतीसाठी विनंती तयार करतो. विनंतीला payload आवश्यक नसते, त्यामुळे रिकामी JSON डॉक्युमेंट पाठवले जाते.

1. याखाली खालील कोड जोडा:

    ```python
    logging.info(f'Sending direct method request for {direct_method.method_name} for device {device_id}')

    registry_manager_connection_string = os.environ['REGISTRY_MANAGER_CONNECTION_STRING']
    registry_manager = IoTHubRegistryManager(registry_manager_connection_string)
    ```
हा कोड `local.settings.json` फाइलमधून `REGISTRY_MANAGER_CONNECTION_STRING` लोड करतो. या फाइलमधील मूल्ये पर्यावरणीय व्हेरिएबल्स म्हणून उपलब्ध करून दिली जातात, आणि `os.environ` फंक्शन वापरून वाचली जाऊ शकतात, जे सर्व पर्यावरणीय व्हेरिएबल्सचे डिक्शनरी परत करते.

> 💁 जेव्हा हा कोड क्लाउडवर डिप्लॉय केला जातो, तेव्हा `local.settings.json` फाइलमधील मूल्ये *Application Settings* म्हणून सेट केली जातात, आणि पर्यावरणीय व्हेरिएबल्समधून वाचली जाऊ शकतात.

यानंतर कोड कनेक्शन स्ट्रिंग वापरून Registry Manager हेल्पर क्लासचे एक उदाहरण तयार करतो.

1. याखाली खालील कोड जोडा:

    ```python
    registry_manager.invoke_device_method(device_id, direct_method)

    logging.info('Direct method request sent!')
    ```

    हा कोड रजिस्ट्रि मॅनेजरला टेलिमेट्री पाठवणाऱ्या डिव्हाइसला डायरेक्ट मेथड रिक्वेस्ट पाठवण्यास सांगतो.

    > 💁 तुम्ही पूर्वीच्या धड्यांमध्ये MQTT वापरून तयार केलेल्या अॅपच्या आवृत्त्यांमध्ये, रिले कंट्रोल कमांड्स सर्व डिव्हाइसला पाठवले जात होते. कोडने गृहीत धरले होते की तुमच्याकडे फक्त एकच डिव्हाइस असेल. या कोडच्या आवृत्तीत मेथड रिक्वेस्ट एका डिव्हाइसला पाठवली जाते, त्यामुळे जर तुमच्याकडे अनेक सेटअप्स असतील तर योग्य डायरेक्ट मेथड रिक्वेस्ट योग्य डिव्हाइसला पाठवली जाईल.

1. Functions अॅप चालवा आणि खात्री करा की तुमचे IoT डिव्हाइस डेटा पाठवत आहे. तुम्हाला संदेश प्रक्रिया होताना आणि डायरेक्ट मेथड रिक्वेस्ट पाठवली जाताना दिसेल. मातीतील ओलावा सेन्सर मातीमध्ये आणि बाहेर हलवा, मूल्ये बदलताना आणि रिले चालू/बंद होताना पाहा.

> 💁 तुम्ही हा कोड [code/functions](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud/code/functions) फोल्डरमध्ये शोधू शकता.

## तुमचा सर्व्हरलेस कोड क्लाउडवर डिप्लॉय करा

तुमचा कोड आता स्थानिक पातळीवर कार्यरत आहे, त्यामुळे पुढील पायरी म्हणजे Functions अॅप क्लाउडवर डिप्लॉय करणे.

### कार्य - क्लाउड संसाधने तयार करा

तुमचे Functions अॅप Azure मधील Functions अॅप संसाधनावर डिप्लॉय करणे आवश्यक आहे, जे तुम्ही तुमच्या IoT Hub साठी तयार केलेल्या Resource Group मध्ये राहील. तुम्हाला Azure मध्ये एक Storage Account देखील तयार करणे आवश्यक आहे, जे तुम्ही स्थानिक पातळीवर चालवलेल्या एम्युलेटेड स्टोरेजची जागा घेईल.

1. स्टोरेज अकाउंट तयार करण्यासाठी खालील कमांड चालवा:

    ```sh
    az storage account create --resource-group soil-moisture-sensor \
                              --sku Standard_LRS \
                              --name <storage_name> 
    ```

    `<storage_name>` च्या जागी तुमच्या स्टोरेज अकाउंटसाठी नाव द्या. हे नाव जागतिक स्तरावर अद्वितीय असणे आवश्यक आहे कारण ते स्टोरेज अकाउंटमध्ये प्रवेश करण्यासाठी वापरल्या जाणाऱ्या URL चा भाग बनते. तुम्ही फक्त लहान अक्षरे आणि अंक वापरू शकता, इतर कोणतेही वर्ण नाहीत, आणि हे 24 वर्णांपर्यंत मर्यादित आहे. `sms` सारखे काहीतरी वापरा आणि शेवटी काही अद्वितीय ओळखकर्ता जोडा, जसे की काही रँडम शब्द किंवा तुमचे नाव.

    `--sku Standard_LRS` किंमत स्तर निवडतो, सर्वात कमी खर्चाचा सामान्य-उद्देश अकाउंट निवडतो. स्टोरेजसाठी मोफत स्तर नाही, आणि तुम्ही जे वापरता त्यासाठी पैसे देता. खर्च तुलनेने कमी आहेत, सर्वात महाग स्टोरेज प्रति गिगाबाइट साठवलेल्या प्रति महिन्याला US$0.05 पेक्षा कमी आहे.

    ✅ किंमतीबद्दल [Azure Storage Account pricing page](https://azure.microsoft.com/pricing/details/storage/?WT.mc_id=academic-17441-jabenn) वर वाचा.

1. Functions अॅप तयार करण्यासाठी खालील कमांड चालवा:

    ```sh
    az functionapp create --resource-group soil-moisture-sensor \
                          --runtime python \
                          --functions-version 3 \
                          --os-type Linux \
                          --consumption-plan-location <location> \
                          --storage-account <storage_name> \
                          --name <functions_app_name>
    ```

    `<location>` च्या जागी तुम्ही मागील धड्यात Resource Group तयार करताना वापरलेले स्थान द्या.

    `<storage_name>` च्या जागी तुम्ही मागील पायरीत तयार केलेल्या स्टोरेज अकाउंटचे नाव द्या.

    `<functions_app_name>` च्या जागी तुमच्या Functions अॅपसाठी अद्वितीय नाव द्या. हे नाव जागतिक स्तरावर अद्वितीय असणे आवश्यक आहे कारण ते Functions अॅपमध्ये प्रवेश करण्यासाठी वापरल्या जाणाऱ्या URL चा भाग बनते. `soil-moisture-sensor-` सारखे काहीतरी वापरा आणि शेवटी काही अद्वितीय ओळखकर्ता जोडा, जसे की काही रँडम शब्द किंवा तुमचे नाव.

    `--functions-version 3` पर्याय Azure Functions चा आवृत्ती सेट करतो. आवृत्ती 3 ही नवीनतम आवृत्ती आहे.

    `--os-type Linux` Functions runtime ला Linux OS वापरण्यास सांगते. Functions Linux किंवा Windows वर होस्ट केले जाऊ शकतात, वापरल्या जाणाऱ्या प्रोग्रामिंग भाषेवर अवलंबून. Python अॅप्स फक्त Linux वर समर्थित आहेत.

### कार्य - तुमची अॅप्लिकेशन सेटिंग्ज अपलोड करा

तुम्ही तुमचे Functions अॅप विकसित करताना, तुमच्या IoT Hub साठी कनेक्शन स्ट्रिंग्जसाठी `local.settings.json` फाइलमध्ये काही सेटिंग्ज संग्रहित केल्या. या सेटिंग्ज Azure मधील Application Settings मध्ये लिहिणे आवश्यक आहे जेणेकरून तुमच्या कोडद्वारे वापरता येतील.

> 🎓 `local.settings.json` फाइल फक्त स्थानिक विकास सेटिंग्जसाठी आहे, आणि ती GitHub सारख्या स्रोत कोड कंट्रोलमध्ये तपासली जाऊ नये. क्लाउडवर डिप्लॉय केल्यावर, Application Settings वापरल्या जातात. Application Settings हे की/मूल्य जोड्या आहेत, क्लाउडमध्ये होस्ट केल्या जातात आणि पर्यावरणीय व्हेरिएबल्समधून वाचल्या जातात, तुमच्या कोडमध्ये किंवा IoT Hub शी कनेक्ट करताना runtime द्वारे.

1. Functions अॅप Application Settings मध्ये `IOT_HUB_CONNECTION_STRING` सेटिंग सेट करण्यासाठी खालील कमांड चालवा:

    ```sh
    az functionapp config appsettings set --resource-group soil-moisture-sensor \
                                          --name <functions_app_name> \
                                          --settings "IOT_HUB_CONNECTION_STRING=<connection string>"
    ```

    `<functions_app_name>` च्या जागी तुम्ही तुमच्या Functions अॅपसाठी वापरलेले नाव द्या.

    `<connection string>` च्या जागी तुमच्या `local.settings.json` फाइलमधील `IOT_HUB_CONNECTION_STRING` चे मूल्य द्या.

1. वरच्या पायरीची पुनरावृत्ती करा, पण `REGISTRY_MANAGER_CONNECTION_STRING` चे मूल्य `local.settings.json` फाइलमधील संबंधित मूल्यावर सेट करा.

जेव्हा तुम्ही हे कमांड चालवता, तेव्हा ते Functions अॅपसाठी सर्व Application Settings ची यादी देखील आउटपुट करतील. तुम्ही तुमची मूल्ये योग्यरित्या सेट केली आहेत की नाही हे तपासण्यासाठी याचा वापर करू शकता.

> 💁 तुम्हाला `AzureWebJobsStorage` साठी आधीच सेट केलेले मूल्य दिसेल. तुमच्या `local.settings.json` फाइलमध्ये, हे स्थानिक स्टोरेज एम्युलेटर वापरण्यासाठी सेट केले होते. जेव्हा तुम्ही Functions अॅप तयार केले, तेव्हा तुम्ही स्टोरेज अकाउंट पॅरामीटर म्हणून पास केले, आणि हे सेटिंगमध्ये स्वयंचलितपणे सेट केले जाते.

### कार्य - तुमचे Functions अॅप क्लाउडवर डिप्लॉय करा

आता Functions अॅप तयार आहे, तुमचा कोड डिप्लॉय केला जाऊ शकतो.

1. तुमच्या Functions अॅपला प्रकाशित करण्यासाठी VS Code टर्मिनलमधून खालील कमांड चालवा:

    ```sh
    func azure functionapp publish <functions_app_name>
    ```

    `<functions_app_name>` च्या जागी तुम्ही तुमच्या Functions अॅपसाठी वापरलेले नाव द्या.

कोड पॅकेज केला जाईल आणि Functions अॅपला पाठवला जाईल, जिथे तो डिप्लॉय आणि सुरू केला जाईल. बरेच कन्सोल आउटपुट असेल, डिप्लॉयमेंटची पुष्टी आणि डिप्लॉय केलेल्या फंक्शन्सची यादी समाप्त होईल. या प्रकरणात यादीमध्ये फक्त ट्रिगर असेल.

```output
Deployment successful.
Remote build succeeded!
Syncing triggers...
Functions in soil-moisture-sensor:
    iot-hub-trigger - [eventHubTrigger]
```

तुमचे IoT डिव्हाइस चालू असल्याची खात्री करा. मातीतील ओलावा बदलण्यासाठी मातीतील ओलावा समायोजित करा, किंवा सेन्सर मातीमध्ये आणि बाहेर हलवा. तुम्हाला मातीतील ओलावा बदलल्यावर रिले चालू/बंद होताना दिसेल.

---

## 🚀 आव्हान

मागील धड्यात, तुम्ही रिलेसाठी टाइमिंग व्यवस्थापित केले होते, रिले चालू असताना आणि बंद झाल्यानंतर थोड्या वेळाने MQTT संदेशांमधून अनसबस्क्राइब करून. तुम्ही येथे ही पद्धत वापरू शकत नाही - तुम्ही तुमच्या IoT Hub ट्रिगरला अनसबस्क्राइब करू शकत नाही.

तुमच्या Functions अॅपमध्ये हे हाताळण्यासाठी तुम्ही वेगवेगळ्या पद्धतींचा विचार करू शकता.

## धड्यानंतरचा क्विझ

[धड्यानंतरचा क्विझ](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/18)

## पुनरावलोकन आणि स्व-अभ्यास

* [Serverless Computing page on Wikipedia](https://wikipedia.org/wiki/Serverless_computing) वर सर्व्हरलेस कंप्युटिंगबद्दल वाचा.
* Azure मध्ये सर्व्हरलेस वापरण्याबद्दल वाचा, ज्यामध्ये [Go serverless for your IoT needs Azure blog post](https://azure.microsoft.com/blog/go-serverless-for-your-iot-needs/?WT.mc_id=academic-17441-jabenn) वर आणखी काही उदाहरणे आहेत.
* [Azure Functions YouTube channel](https://www.youtube.com/c/AzureFunctions) वर Azure Functions बद्दल अधिक जाणून घ्या.

## असाइनमेंट

[मॅन्युअल रिले कंट्रोल जोडा](assignment.md)

---

**अस्वीकरण**:  
हा दस्तऐवज AI भाषांतर सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) चा वापर करून भाषांतरित करण्यात आला आहे. आम्ही अचूकतेसाठी प्रयत्नशील असलो तरी, कृपया लक्षात घ्या की स्वयंचलित भाषांतरांमध्ये त्रुटी किंवा अचूकतेचा अभाव असू शकतो. मूळ भाषेतील दस्तऐवज हा अधिकृत स्रोत मानला जावा. महत्त्वाच्या माहितीसाठी व्यावसायिक मानवी भाषांतराची शिफारस केली जाते. या भाषांतराचा वापर केल्यामुळे उद्भवणाऱ्या कोणत्याही गैरसमज किंवा चुकीच्या अर्थासाठी आम्ही जबाबदार राहणार नाही.