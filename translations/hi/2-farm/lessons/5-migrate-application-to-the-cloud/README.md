# अपनी एप्लिकेशन लॉजिक को क्लाउड में माइग्रेट करें

![इस पाठ का स्केच नोट](../../../../../translated_images/hi/lesson-9.dfe99c8e891f48e1.webp)

> स्केच नोट [नित्या नरसिम्हन](https://github.com/nitya) द्वारा। बड़े संस्करण के लिए छवि पर क्लिक करें।

यह पाठ [IoT for Beginners Project 2 - Digital Agriculture series](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) के हिस्से के रूप में [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn) से सिखाया गया था।

[![अपने IoT डिवाइस को सर्वरलेस कोड से नियंत्रित करें](https://img.youtube.com/vi/VVZDcs5u1_I/0.jpg)](https://youtu.be/VVZDcs5u1_I)

## प्री-लेक्चर क्विज़

[प्री-लेक्चर क्विज़](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/17)

## परिचय

पिछले पाठ में, आपने सीखा कि अपने पौधों की मिट्टी की नमी की निगरानी और रिले नियंत्रण को क्लाउड-आधारित IoT सेवा से कैसे जोड़ा जाए। अगला कदम उस सर्वर कोड को क्लाउड में स्थानांतरित करना है जो रिले के समय को नियंत्रित करता है। इस पाठ में, आप सीखेंगे कि इसे सर्वरलेस फंक्शन्स का उपयोग करके कैसे करना है।

इस पाठ में हम निम्नलिखित विषयों को कवर करेंगे:

* [सर्वरलेस क्या है?](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [एक सर्वरलेस एप्लिकेशन बनाएं](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [IoT हब इवेंट ट्रिगर बनाएं](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [सर्वरलेस कोड से डायरेक्ट मेथड रिक्वेस्ट भेजें](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [अपने सर्वरलेस कोड को क्लाउड में डिप्लॉय करें](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)

## सर्वरलेस क्या है?

सर्वरलेस, या सर्वरलेस कंप्यूटिंग, छोटे कोड ब्लॉक्स बनाने का तरीका है जो विभिन्न प्रकार की घटनाओं के जवाब में क्लाउड में चलते हैं। जब घटना होती है, तो आपका कोड चलता है और घटना के बारे में डेटा प्राप्त करता है। ये घटनाएं कई स्रोतों से हो सकती हैं, जैसे वेब अनुरोध, किसी कतार में डाले गए संदेश, डेटाबेस में डेटा में परिवर्तन, या IoT डिवाइस द्वारा IoT सेवा को भेजे गए संदेश।

![IoT सेवा से सर्वरलेस सेवा तक भेजे जा रहे संदेश, जो एक साथ कई फंक्शन्स द्वारा संसाधित किए जा रहे हैं](../../../../../translated_images/hi/iot-messages-to-serverless.0194da1cc0732bb7.webp)

> 💁 यदि आपने पहले डेटाबेस ट्रिगर्स का उपयोग किया है, तो इसे उसी तरह समझ सकते हैं, जैसे कोड किसी घटना जैसे कि पंक्ति डालने पर ट्रिगर होता है।

![जब कई घटनाएं एक साथ भेजी जाती हैं, तो सर्वरलेस सेवा उन्हें एक साथ चलाने के लिए स्केल करती है](../../../../../translated_images/hi/serverless-scaling.f8c769adf0413fd1.webp)

आपका कोड केवल तब चलता है जब घटना होती है, अन्य समय में आपका कोड सक्रिय नहीं रहता। घटना होती है, आपका कोड लोड होता है और चलता है। यह सर्वरलेस को बहुत स्केलेबल बनाता है - यदि कई घटनाएं एक साथ होती हैं, तो क्लाउड प्रदाता आपके फंक्शन को जितनी बार जरूरत हो उतनी बार एक साथ चलाने के लिए स्केल कर सकता है। इसका नुकसान यह है कि यदि आपको घटनाओं के बीच जानकारी साझा करनी है, तो आपको इसे मेमोरी में स्टोर करने के बजाय किसी डेटाबेस में सहेजना होगा।

आपका कोड एक फंक्शन के रूप में लिखा जाता है जो घटना के विवरण को एक पैरामीटर के रूप में लेता है। आप इन सर्वरलेस फंक्शन्स को लिखने के लिए कई प्रोग्रामिंग भाषाओं का उपयोग कर सकते हैं।

> 🎓 सर्वरलेस को फंक्शन्स ऐज़ ए सर्विस (FaaS) भी कहा जाता है क्योंकि प्रत्येक इवेंट ट्रिगर को कोड में एक फंक्शन के रूप में लागू किया जाता है।

नाम के बावजूद, सर्वरलेस वास्तव में सर्वर का उपयोग करता है। नामकरण इसलिए है क्योंकि एक डेवलपर के रूप में आपको अपने कोड को चलाने के लिए आवश्यक सर्वरों की परवाह नहीं होती, आपको केवल यह परवाह होती है कि आपका कोड घटना के जवाब में चले। क्लाउड प्रदाता के पास एक सर्वरलेस *रनटाइम* होता है जो सर्वर, नेटवर्किंग, स्टोरेज, CPU, मेमोरी और आपके कोड को चलाने के लिए आवश्यक अन्य सभी चीजों को प्रबंधित करता है। इस मॉडल का मतलब है कि आप सेवा के लिए प्रति सर्वर भुगतान नहीं कर सकते, क्योंकि कोई सर्वर नहीं है। इसके बजाय आप अपने कोड के चलने के समय और उपयोग की गई मेमोरी के लिए भुगतान करते हैं।

> 💰 सर्वरलेस क्लाउड में कोड चलाने के सबसे सस्ते तरीकों में से एक है। उदाहरण के लिए, लेखन के समय, एक क्लाउड प्रदाता आपके सभी सर्वरलेस फंक्शन्स को एक महीने में संयुक्त रूप से 1,000,000 बार चलाने की अनुमति देता है, उसके बाद वे प्रत्येक 1,000,000 निष्पादन के लिए US$0.20 चार्ज करते हैं। जब आपका कोड नहीं चल रहा होता है, तो आप भुगतान नहीं करते।

IoT डेवलपर के रूप में, सर्वरलेस मॉडल आदर्श है। आप एक फंक्शन लिख सकते हैं जो किसी भी IoT डिवाइस द्वारा आपके क्लाउड-होस्टेड IoT सेवा को भेजे गए संदेशों के जवाब में कॉल किया जाता है। आपका कोड सभी भेजे गए संदेशों को संभालेगा, लेकिन केवल तब चलेगा जब जरूरत हो।

✅ उस कोड को देखें जो आपने MQTT पर संदेशों को सुनने के लिए सर्वर कोड के रूप में लिखा था। यह क्लाउड में सर्वरलेस का उपयोग करके कैसे चल सकता है? आपको लगता है कि कोड को सर्वरलेस कंप्यूटिंग का समर्थन करने के लिए कैसे बदला जा सकता है?

> 💁 सर्वरलेस मॉडल अन्य क्लाउड सेवाओं में भी जा रहा है, कोड चलाने के अलावा। उदाहरण के लिए, क्लाउड में सर्वरलेस डेटाबेस उपलब्ध हैं जो सर्वरलेस प्राइसिंग मॉडल का उपयोग करते हैं, जहां आप डेटाबेस के खिलाफ किए गए प्रत्येक अनुरोध के लिए भुगतान करते हैं, जैसे कि क्वेरी या इनसर्ट। आमतौर पर यह मूल्य निर्धारण इस बात पर आधारित होता है कि अनुरोध को सेवा देने के लिए कितना काम किया गया। उदाहरण के लिए, एक प्राथमिक कुंजी के खिलाफ एक पंक्ति का चयन एक जटिल ऑपरेशन की तुलना में कम खर्च होगा जो कई तालिकाओं को जोड़ता है और हजारों पंक्तियों को लौटाता है।

## एक सर्वरलेस एप्लिकेशन बनाएं

Microsoft का सर्वरलेस कंप्यूटिंग सेवा Azure Functions कहलाती है।

![Azure Functions का लोगो](../../../../../translated_images/hi/azure-functions-logo.1cfc8e3204c9c44a.webp)

नीचे दिया गया छोटा वीडियो Azure Functions का अवलोकन प्रदान करता है:

[![Azure Functions अवलोकन वीडियो](https://img.youtube.com/vi/8-jz5f_JyEQ/0.jpg)](https://www.youtube.com/watch?v=8-jz5f_JyEQ)

> 🎥 ऊपर दी गई छवि पर क्लिक करें वीडियो देखने के लिए।

✅ कुछ समय निकालें और [Microsoft Azure Functions दस्तावेज़](https://docs.microsoft.com/azure/azure-functions/functions-overview?WT.mc_id=academic-17441-jabenn) में Azure Functions का अवलोकन पढ़ें।

Azure Functions लिखने के लिए, आप अपनी पसंद की भाषा में Azure Functions ऐप से शुरू करते हैं। Azure Functions Python, JavaScript, TypeScript, C#, F#, Java, और Powershell को सपोर्ट करता है। इस पाठ में, आप Python में Azure Functions ऐप लिखना सीखेंगे।

> 💁 Azure Functions कस्टम हैंडलर्स को भी सपोर्ट करता है, जिससे आप अपने फंक्शन्स को किसी भी भाषा में लिख सकते हैं जो HTTP अनुरोधों का समर्थन करती है, जिसमें COBOL जैसी पुरानी भाषाएं भी शामिल हैं।

Functions ऐप्स में एक या अधिक *ट्रिगर्स* होते हैं - फंक्शन्स जो घटनाओं के जवाब में चलते हैं। आप एक Functions ऐप में कई ट्रिगर्स रख सकते हैं, जो सभी सामान्य कॉन्फ़िगरेशन साझा करते हैं। उदाहरण के लिए, आपके Functions ऐप के कॉन्फ़िगरेशन फ़ाइल में आपके IoT हब का कनेक्शन विवरण हो सकता है, और ऐप के सभी फंक्शन्स इसका उपयोग करके कनेक्ट और घटनाओं को सुन सकते हैं।

### कार्य - Azure Functions टूलिंग इंस्टॉल करें

> लेखन के समय, Azure Functions कोड टूल्स Apple Silicon पर Python प्रोजेक्ट्स के साथ पूरी तरह से काम नहीं कर रहे हैं। आपको इसके बजाय Intel-आधारित Mac, Windows PC, या Linux PC का उपयोग करना होगा।

Azure Functions की एक बड़ी विशेषता यह है कि आप उन्हें लोकली चला सकते हैं। वही रनटाइम जो क्लाउड में उपयोग किया जाता है, आपके कंप्यूटर पर चल सकता है, जिससे आप कोड लिख सकते हैं जो IoT संदेशों का जवाब देता है और इसे लोकली चला सकते हैं। आप घटनाओं को संभालते समय अपने कोड को डिबग भी कर सकते हैं। एक बार जब आप अपने कोड से संतुष्ट हो जाते हैं, तो इसे क्लाउड में डिप्लॉय किया जा सकता है।

Azure Functions टूलिंग CLI के रूप में उपलब्ध है, जिसे Azure Functions Core Tools कहा जाता है।

1. [Azure Functions Core Tools दस्तावेज़](https://docs.microsoft.com/azure/azure-functions/functions-run-local?WT.mc_id=academic-17441-jabenn) पर दिए गए निर्देशों का पालन करके Azure Functions कोर टूल्स इंस्टॉल करें।

1. VS Code के लिए Azure Functions एक्सटेंशन इंस्टॉल करें। यह एक्सटेंशन Azure Functions बनाने, डिबग करने और डिप्लॉय करने के लिए समर्थन प्रदान करता है। [Azure Functions एक्सटेंशन दस्तावेज़](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-azuretools.vscode-azurefunctions) में दिए गए निर्देशों का पालन करके इसे VS Code में इंस्टॉल करें।

जब आप अपने Azure Functions ऐप को क्लाउड में डिप्लॉय करते हैं, तो इसे एप्लिकेशन फ़ाइलों और लॉग फ़ाइलों जैसी चीजों को स्टोर करने के लिए थोड़ी मात्रा में क्लाउड स्टोरेज का उपयोग करना होता है। जब आप अपने Functions ऐप को लोकली चलाते हैं, तो आपको क्लाउड स्टोरेज से कनेक्ट करना होता है, लेकिन वास्तविक क्लाउड स्टोरेज का उपयोग करने के बजाय, आप एक स्टोरेज एमुलेटर का उपयोग कर सकते हैं जिसे [Azurite](https://github.com/Azure/Azurite) कहा जाता है। यह लोकली चलता है लेकिन क्लाउड स्टोरेज की तरह काम करता है।

> 🎓 Azure में, Azure Functions द्वारा उपयोग किया जाने वाला स्टोरेज एक Azure Storage Account होता है। ये खाते फ़ाइलें, ब्लॉब्स, तालिकाओं में डेटा या कतारों में डेटा स्टोर कर सकते हैं। आप एक स्टोरेज अकाउंट को कई ऐप्स के बीच साझा कर सकते हैं, जैसे कि एक Functions ऐप और एक वेब ऐप।

1. Azurite एक Node.js ऐप है, इसलिए आपको Node.js इंस्टॉल करना होगा। आप [Node.js वेबसाइट](https://nodejs.org/) पर डाउनलोड और इंस्टॉल निर्देश पा सकते हैं। यदि आप Mac का उपयोग कर रहे हैं, तो आप इसे [Homebrew](https://formulae.brew.sh/formula/node) से भी इंस्टॉल कर सकते हैं।

1. निम्नलिखित कमांड का उपयोग करके Azurite इंस्टॉल करें (`npm` एक टूल है जो Node.js इंस्टॉल करते समय इंस्टॉल होता है):

    ```sh
    npm install -g azurite
    ```

1. Azurite के लिए डेटा स्टोर करने के लिए `azurite` नामक एक फ़ोल्डर बनाएं:

    ```sh
    mkdir azurite
    ```

1. Azurite चलाएं, इसे इस नए फ़ोल्डर को पास करते हुए:

    ```sh
    azurite --location azurite
    ```

    Azurite स्टोरेज एमुलेटर लॉन्च होगा और लोकल Functions रनटाइम से कनेक्ट करने के लिए तैयार होगा।

    ```output
    ➜  ~ azurite --location azurite  
    Azurite Blob service is starting at http://127.0.0.1:10000
    Azurite Blob service is successfully listening at http://127.0.0.1:10000
    Azurite Queue service is starting at http://127.0.0.1:10001
    Azurite Queue service is successfully listening at http://127.0.0.1:10001
    Azurite Table service is starting at http://127.0.0.1:10002
    Azurite Table service is successfully listening at http://127.0.0.1:10002
    ```

### कार्य - एक Azure Functions प्रोजेक्ट बनाएं

Azure Functions CLI का उपयोग करके एक नया Functions ऐप बनाया जा सकता है।

1. अपने Functions ऐप के लिए एक फ़ोल्डर बनाएं और उसमें जाएं। इसे `soil-moisture-trigger` नाम दें:

    ```sh
    mkdir soil-moisture-trigger
    cd soil-moisture-trigger
    ```

1. इस फ़ोल्डर के अंदर एक Python वर्चुअल एनवायरनमेंट बनाएं:

    ```sh
    python3 -m venv .venv
    ```

1. वर्चुअल एनवायरनमेंट को सक्रिय करें:

    * Windows पर:
        * यदि आप Command Prompt या Windows Terminal के माध्यम से Command Prompt का उपयोग कर रहे हैं, तो निम्नलिखित चलाएं:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * यदि आप PowerShell का उपयोग कर रहे हैं, तो निम्नलिखित चलाएं:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

    * macOS या Linux पर, निम्नलिखित चलाएं:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 ये कमांड उसी स्थान से चलाए जाने चाहिए जहां आपने वर्चुअल एनवायरनमेंट बनाने का कमांड चलाया था। आपको `.venv` फ़ोल्डर में कभी भी नेविगेट करने की आवश्यकता नहीं होगी, आपको हमेशा सक्रिय करने का कमांड और पैकेज इंस्टॉल करने या कोड चलाने के लिए कमांड उसी फ़ोल्डर से चलाना चाहिए जहां आपने वर्चुअल एनवायरनमेंट बनाया था।

1. इस फ़ोल्डर में Functions ऐप बनाने के लिए निम्नलिखित कमांड चलाएं:

    ```sh
    func init --worker-runtime python soil-moisture-trigger
    ```

    यह वर्तमान फ़ोल्डर के अंदर तीन फ़ाइलें बनाएगा:

    * `host.json` - यह JSON दस्तावेज़ आपके Functions ऐप के लिए सेटिंग्स को शामिल करता है। आपको इन सेटिंग्स को संशोधित करने की आवश्यकता नहीं होगी।
    * `local.settings.json` - यह JSON दस्तावेज़ आपके ऐप द्वारा लोकली चलाए जाने पर उपयोग की जाने वाली सेटिंग्स को शामिल करता है, जैसे कि आपके IoT हब के लिए कनेक्शन स्ट्रिंग्स। ये सेटिंग्स केवल लोकल हैं और इन्हें सोर्स कोड कंट्रोल में नहीं जोड़ा जाना चाहिए। जब आप ऐप को क्लाउड में डिप्लॉय करते हैं, तो ये सेटिंग्स डिप्लॉय नहीं होतीं, बल्कि आपकी सेटिंग्स एप्लिकेशन सेटिंग्स से लोड होती हैं। इसे इस पाठ में बाद में कवर किया जाएगा।
    * `requirements.txt` - यह एक [Pip requirements फ़ाइल](https://pip.pypa.io/en/stable/user_guide/#requirements-files) है जो आपके Functions ऐप को चलाने के लिए आवश्यक Pip पैकेजों को शामिल करती है।

1. `local.settings.json` फ़ाइल में उस स्टोरेज अकाउंट के लिए एक सेटिंग होती है जिसे Functions ऐप उपयोग करेगा। यह डिफ़ॉल्ट रूप से खाली सेटिंग होती है, इसलिए इसे सेट करने की आवश्यकता होती है। Azurite लोकल स्टोरेज एमुलेटर से कनेक्ट करने के लिए, इस मान को निम्नलिखित पर सेट करें:

    ```json
    "AzureWebJobsStorage": "UseDevelopmentStorage=true",
    ```

1. आवश्यक Pip पैकेजों को requirements फ़ाइल का उपयोग करके इंस्टॉल करें:

    ```sh
    pip install -r requirements.txt
    ```

    > 💁 आवश्यक Pip पैकेजों को इस फ़ाइल में होना चाहिए, ताकि जब Functions ऐप को क्लाउड में डिप्लॉय किया जाए, तो रनटाइम सुनिश्चित कर सके कि यह सही पैकेज इंस्टॉल करता है।

1. यह सुनिश्चित करने के लिए कि सब कुछ सही ढंग से काम कर रहा है, आप Functions रनटाइम शुरू कर सकते हैं। इसे शुरू करने के लिए निम्नलिखित कमांड चलाएं:

    ```sh
    func start
    ```

    आप देखेंगे कि रनटाइम शुरू होता है और रिपोर्ट करता है कि उसे कोई जॉब फंक्शन्स (ट्रिगर्स) नहीं मिले हैं।

    ```output
    (.venv) ➜  soil-moisture-trigger func start
    Found Python version 3.9.1 (python3).
    
    Azure Functions Core Tools
    Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    Function Runtime Version: 3.0.15417.0
    
    [2021-05-05T01:24:46.795Z] No job functions found.
    ```
> ⚠️ यदि आपको फ़ायरवॉल नोटिफिकेशन मिलता है, तो एक्सेस की अनुमति दें क्योंकि `func` एप्लिकेशन को आपके नेटवर्क पर पढ़ने और लिखने की आवश्यकता होती है।
> ⚠️ यदि आप macOS का उपयोग कर रहे हैं, तो आउटपुट में चेतावनियां हो सकती हैं:
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
> जब तक Functions ऐप सही तरीके से शुरू हो और चल रहे फंक्शन्स को सूचीबद्ध करे, आप इन्हें अनदेखा कर सकते हैं। जैसा कि [Microsoft Docs Q&A पर इस प्रश्न](https://docs.microsoft.com/answers/questions/396617/azure-functions-core-tools-error-osx-devshmazurefu.html?WT.mc_id=academic-17441-jabenn) में उल्लेख किया गया है, इसे अनदेखा किया जा सकता है।

1. `ctrl+c` दबाकर Functions ऐप को बंद करें।

1. वर्तमान फ़ोल्डर को VS Code में खोलें, या तो VS Code खोलकर इस फ़ोल्डर को खोलें, या निम्नलिखित कमांड चलाकर:

    ```sh
    code .
    ```

    VS Code आपके Functions प्रोजेक्ट का पता लगाएगा और एक नोटिफिकेशन दिखाएगा जिसमें लिखा होगा:

    ```output
    Detected an Azure Functions Project in folder "soil-moisture-trigger" that may have been created outside of
    VS Code. Initialize for optimal use with VS Code?
    ```

    ![नोटिफिकेशन](../../../../../translated_images/hi/vscode-azure-functions-init-notification.bd19b49229963edb.webp)

    इस नोटिफिकेशन से **Yes** चुनें।

1. सुनिश्चित करें कि VS Code टर्मिनल में Python वर्चुअल एनवायरनमेंट चल रहा है। यदि आवश्यक हो तो इसे समाप्त करें और पुनः प्रारंभ करें।

## IoT Hub इवेंट ट्रिगर बनाएं

Functions ऐप आपके सर्वरलेस कोड का शेल है। IoT Hub इवेंट्स का जवाब देने के लिए, आप इस ऐप में एक IoT Hub ट्रिगर जोड़ सकते हैं। यह ट्रिगर उन संदेशों की स्ट्रीम से कनेक्ट करने की आवश्यकता है जो IoT Hub को भेजे जाते हैं और उनका जवाब देते हैं। इन संदेशों की स्ट्रीम प्राप्त करने के लिए, आपके ट्रिगर को IoT Hubs के *इवेंट हब संगत एंडपॉइंट* से कनेक्ट करना होगा।

IoT Hub एक अन्य Azure सेवा, Azure Event Hubs, पर आधारित है। Event Hubs एक सेवा है जो आपको संदेश भेजने और प्राप्त करने की अनुमति देती है, और IoT Hub इसे IoT डिवाइसों के लिए सुविधाओं के साथ विस्तारित करता है। IoT Hub से संदेश पढ़ने के लिए कनेक्ट करने का तरीका वही है जैसा आप Event Hubs का उपयोग करते समय करेंगे।

✅ थोड़ा शोध करें: [Azure Event Hubs दस्तावेज़](https://docs.microsoft.com/azure/event-hubs/event-hubs-about?WT.mc_id=academic-17441-jabenn) में Event Hubs का अवलोकन पढ़ें। इसकी बुनियादी सुविधाओं की तुलना IoT Hub से कैसे होती है?

IoT डिवाइस को IoT Hub से कनेक्ट करने के लिए, इसे एक गुप्त कुंजी का उपयोग करना होगा जो सुनिश्चित करता है कि केवल अनुमत डिवाइस ही कनेक्ट कर सकते हैं। यही बात संदेश पढ़ने के लिए कनेक्ट करने पर भी लागू होती है; आपके कोड को एक कनेक्शन स्ट्रिंग की आवश्यकता होगी जिसमें एक गुप्त कुंजी और IoT Hub का विवरण शामिल होगा।

> 💁 आपको जो डिफ़ॉल्ट कनेक्शन स्ट्रिंग मिलती है उसमें **iothubowner** अनुमतियां होती हैं, जो इसे उपयोग करने वाले किसी भी कोड को IoT Hub पर पूर्ण अनुमतियां देती हैं। आदर्श रूप से, आपको केवल आवश्यक न्यूनतम स्तर की अनुमतियों के साथ कनेक्ट करना चाहिए। इसे अगले पाठ में कवर किया जाएगा।

एक बार जब आपका ट्रिगर कनेक्ट हो जाता है, तो IoT Hub को भेजे गए प्रत्येक संदेश के लिए फ़ंक्शन के अंदर का कोड कॉल किया जाएगा, चाहे वह संदेश किस डिवाइस ने भेजा हो। ट्रिगर को संदेश एक पैरामीटर के रूप में पास किया जाएगा।

### कार्य - इवेंट हब संगत एंडपॉइंट कनेक्शन स्ट्रिंग प्राप्त करें

1. VS Code टर्मिनल से निम्नलिखित कमांड चलाएं ताकि IoT Hubs इवेंट हब संगत एंडपॉइंट के लिए कनेक्शन स्ट्रिंग प्राप्त हो:

    ```sh
    az iot hub connection-string show --default-eventhub \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    `<hub_name>` को अपने IoT Hub के नाम से बदलें।

1. VS Code में `local.settings.json` फ़ाइल खोलें। `Values` सेक्शन के अंदर निम्नलिखित अतिरिक्त मान जोड़ें:

    ```json
    "IOT_HUB_CONNECTION_STRING": "<connection string>"
    ```

    `<connection string>` को पिछले चरण से प्राप्त मान से बदलें। इसे वैध JSON बनाने के लिए ऊपर की पंक्ति के बाद एक कॉमा जोड़ना होगा।

### कार्य - इवेंट ट्रिगर बनाएं

अब आप इवेंट ट्रिगर बनाने के लिए तैयार हैं।

1. VS Code टर्मिनल से `soil-moisture-trigger` फ़ोल्डर के अंदर निम्नलिखित कमांड चलाएं:

    ```sh
    func new --name iot-hub-trigger --template "Azure Event Hub trigger"
    ```

    यह एक नया फ़ंक्शन बनाएगा जिसका नाम `iot-hub-trigger` होगा। ट्रिगर IoT Hub पर इवेंट हब संगत एंडपॉइंट से कनेक्ट करेगा, ताकि आप इवेंट हब ट्रिगर का उपयोग कर सकें। IoT Hub के लिए कोई विशिष्ट ट्रिगर नहीं है।

यह `soil-moisture-trigger` फ़ोल्डर के अंदर एक फ़ोल्डर बनाएगा जिसका नाम `iot-hub-trigger` होगा, जिसमें यह फ़ंक्शन होगा। इस फ़ोल्डर में निम्नलिखित फाइलें होंगी:

* `__init__.py` - यह Python कोड फ़ाइल है जिसमें ट्रिगर होता है, और यह फ़ोल्डर को Python मॉड्यूल में बदलने के लिए मानक Python फ़ाइल नाम कन्वेंशन का उपयोग करता है।

    इस फ़ाइल में निम्नलिखित कोड होगा:

    ```python
    import logging

    import azure.functions as func


    def main(event: func.EventHubEvent):
        logging.info('Python EventHub trigger processed an event: %s',
                    event.get_body().decode('utf-8'))
    ```

    ट्रिगर का मुख्य भाग `main` फ़ंक्शन है। यह फ़ंक्शन IoT Hub से आने वाले इवेंट्स के साथ कॉल किया जाता है। इस फ़ंक्शन में `event` नामक एक पैरामीटर होता है जो एक `EventHubEvent` होता है। हर बार जब IoT Hub को संदेश भेजा जाता है, तो यह फ़ंक्शन उस संदेश को `event` के रूप में पास करता है, साथ ही उन गुणों के साथ जो आपने पिछले पाठ में एनोटेशन के रूप में देखे थे।

    इस फ़ंक्शन का मुख्य भाग इवेंट को लॉग करता है।

* `function.json` - इसमें ट्रिगर के लिए कॉन्फ़िगरेशन होता है। मुख्य कॉन्फ़िगरेशन `bindings` नामक सेक्शन में होता है। बाइंडिंग Azure Functions और अन्य Azure सेवाओं के बीच कनेक्शन के लिए शब्द है। इस फ़ंक्शन में इवेंट हब के लिए एक इनपुट बाइंडिंग है - यह इवेंट हब से कनेक्ट होता है और डेटा प्राप्त करता है।

    > 💁 आप आउटपुट बाइंडिंग भी जोड़ सकते हैं ताकि फ़ंक्शन का आउटपुट किसी अन्य सेवा को भेजा जा सके। उदाहरण के लिए, आप डेटाबेस के लिए एक आउटपुट बाइंडिंग जोड़ सकते हैं और IoT Hub इवेंट को फ़ंक्शन से वापस कर सकते हैं, और यह स्वचालित रूप से डेटाबेस में सम्मिलित हो जाएगा।

    ✅ थोड़ा शोध करें: [Azure Functions ट्रिगर्स और बाइंडिंग्स अवधारणाओं](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python) दस्तावेज़ में बाइंडिंग्स के बारे में पढ़ें।

    `bindings` सेक्शन में बाइंडिंग के लिए कॉन्फ़िगरेशन शामिल है। रुचि के मान हैं:

  * `"type": "eventHubTrigger"` - यह फ़ंक्शन को बताता है कि इसे Event Hub से इवेंट्स सुनने की आवश्यकता है।
  * `"name": "events"` - यह Event Hub इवेंट्स के लिए उपयोग करने के लिए पैरामीटर नाम है। यह Python कोड में `main` फ़ंक्शन में पैरामीटर नाम से मेल खाता है।
  * `"direction": "in"` - यह एक इनपुट बाइंडिंग है, इवेंट हब से डेटा फ़ंक्शन में आता है।
  * `"connection": ""` - यह परिभाषित करता है कि कनेक्शन स्ट्रिंग को पढ़ने के लिए किस सेटिंग का उपयोग करना है। स्थानीय रूप से चलाने पर, यह `local.settings.json` फ़ाइल से इस सेटिंग को पढ़ेगा।

    > 💁 कनेक्शन स्ट्रिंग को `function.json` फ़ाइल में संग्रहीत नहीं किया जा सकता है, इसे सेटिंग्स से पढ़ा जाना चाहिए। ऐसा इसलिए है ताकि आप गलती से अपनी कनेक्शन स्ट्रिंग को उजागर न करें।

1. [Azure Functions टेम्पलेट में एक बग](https://github.com/Azure/azure-functions-templates/issues/1250) के कारण, `function.json` में `cardinality` फ़ील्ड के लिए एक गलत मान है। इस फ़ील्ड को `many` से `one` में अपडेट करें:

    ```json
    "cardinality": "one",
    ```

1. `function.json` फ़ाइल में `"connection"` के मान को अपडेट करें ताकि यह `local.settings.json` फ़ाइल में जोड़े गए नए मान की ओर इशारा करे:

    ```json
    "connection": "IOT_HUB_CONNECTION_STRING",
    ```

    > 💁 याद रखें - इसे सेटिंग की ओर इशारा करना चाहिए, इसमें वास्तविक कनेक्शन स्ट्रिंग नहीं होनी चाहिए।

1. कनेक्शन स्ट्रिंग में `eventHubName` मान होता है, इसलिए `function.json` फ़ाइल में इसके लिए मान को खाली करना होगा। इस मान को खाली स्ट्रिंग में अपडेट करें:

    ```json
    "eventHubName": "",
    ```

### कार्य - इवेंट ट्रिगर चलाएं

1. सुनिश्चित करें कि आप IoT Hub इवेंट मॉनिटर नहीं चला रहे हैं। यदि यह Functions ऐप के साथ एक ही समय में चल रहा है, तो Functions ऐप कनेक्ट नहीं कर पाएगा और इवेंट्स का उपभोग नहीं कर पाएगा।

    > 💁 कई ऐप्स IoT Hub एंडपॉइंट्स से विभिन्न *कंज्यूमर ग्रुप्स* का उपयोग करके कनेक्ट कर सकते हैं। इन्हें बाद के पाठ में कवर किया जाएगा।

1. Functions ऐप चलाने के लिए, VS Code टर्मिनल से निम्नलिखित कमांड चलाएं:

    ```sh
    func start
    ```

    Functions ऐप शुरू हो जाएगा, और `iot-hub-trigger` फ़ंक्शन का पता लगाएगा। यह पिछले दिन में IoT Hub को भेजे गए किसी भी इवेंट को प्रोसेस करेगा।

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

    प्रत्येक फ़ंक्शन कॉल के लिए आउटपुट में `Executing 'Functions.iot-hub-trigger'`/`Executed 'Functions.iot-hub-trigger'` ब्लॉक होगा, ताकि आप देख सकें कि प्रत्येक फ़ंक्शन कॉल में कितने संदेश प्रोसेस किए गए।

1. सुनिश्चित करें कि आपका IoT डिवाइस चल रहा है। आप Functions ऐप में नए मिट्टी की नमी के संदेश देखेंगे।

1. Functions ऐप को बंद करें और पुनः प्रारंभ करें। आप देखेंगे कि यह पिछले संदेशों को फिर से प्रोसेस नहीं करेगा, यह केवल नए संदेशों को प्रोसेस करेगा।

> 💁 VS Code आपके Functions को डिबग करने का समर्थन करता है। आप कोड की प्रत्येक पंक्ति की शुरुआत में क्लिक करके ब्रेक पॉइंट सेट कर सकते हैं, या कोड की एक पंक्ति पर कर्सर रखकर *Run -> Toggle breakpoint* चुन सकते हैं, या `F9` दबा सकते हैं। आप *Run -> Start debugging* चुनकर, `F5` दबाकर, या *Run and debug* पैन का चयन करके और **Start debugging** बटन चुनकर डिबगर लॉन्च कर सकते हैं। ऐसा करके आप प्रोसेस किए जा रहे इवेंट्स का विवरण देख सकते हैं।

#### समस्या निवारण

* यदि आपको निम्नलिखित त्रुटि मिलती है:

    ```output
    The listener for function 'Functions.iot-hub-trigger' was unable to start. Microsoft.WindowsAzure.Storage: Connection refused. System.Net.Http: Connection refused. System.Private.CoreLib: Connection refused.
    ```

    जांचें कि Azurite चल रहा है और आपने `local.settings.json` फ़ाइल में `AzureWebJobsStorage` को `UseDevelopmentStorage=true` पर सेट किया है।

* यदि आपको निम्नलिखित त्रुटि मिलती है:

    ```output
    System.Private.CoreLib: Exception while executing function: Functions.iot-hub-trigger. System.Private.CoreLib: Result: Failure Exception: AttributeError: 'list' object has no attribute 'get_body'
    ```

    जांचें कि आपने `function.json` फ़ाइल में `cardinality` को `one` पर सेट किया है।

* यदि आपको निम्नलिखित त्रुटि मिलती है:

    ```output
    Azure.Messaging.EventHubs: The path to an Event Hub may be specified as part of the connection string or as a separate value, but not both.  Please verify that your connection string does not have the `EntityPath` token if you are passing an explicit Event Hub name. (Parameter 'connectionString').
    ```

    जांचें कि आपने `function.json` फ़ाइल में `eventHubName` को खाली स्ट्रिंग पर सेट किया है।

## सर्वरलेस कोड से डायरेक्ट मेथड रिक्वेस्ट भेजें

अब तक आपका Functions ऐप Event Hub संगत एंडपॉइंट का उपयोग करके IoT Hub से संदेश सुन रहा है। अब आपको IoT डिवाइस को कमांड भेजने की आवश्यकता है। यह IoT Hub से *Registry Manager* के माध्यम से एक अलग कनेक्शन का उपयोग करके किया जाता है। Registry Manager एक उपकरण है जो आपको IoT Hub के साथ पंजीकृत डिवाइसों को देखने और उन डिवाइसों के साथ संवाद करने की अनुमति देता है। आप इसे क्लाउड से डिवाइस संदेश भेजने, डायरेक्ट मेथड रिक्वेस्ट भेजने, या डिवाइस ट्विन को अपडेट करने के लिए उपयोग कर सकते हैं। आप इसका उपयोग IoT Hub से IoT डिवाइसों को पंजीकृत करने, अपडेट करने या हटाने के लिए भी कर सकते हैं।

Registry Manager से कनेक्ट करने के लिए, आपको एक कनेक्शन स्ट्रिंग की आवश्यकता होगी।

### कार्य - Registry Manager कनेक्शन स्ट्रिंग प्राप्त करें

1. कनेक्शन स्ट्रिंग प्राप्त करने के लिए, निम्नलिखित कमांड चलाएं:

    ```sh
    az iot hub connection-string show --policy-name service \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    `<hub_name>` को अपने IoT Hub के नाम से बदलें।

    कनेक्शन स्ट्रिंग *ServiceConnect* पॉलिसी के लिए `--policy-name service` पैरामीटर का उपयोग करके अनुरोध की जाती है। जब आप कनेक्शन स्ट्रिंग का अनुरोध करते हैं, तो आप निर्दिष्ट कर सकते हैं कि वह कनेक्शन स्ट्रिंग किन अनुमतियों की अनुमति देगा। ServiceConnect पॉलिसी आपके कोड को कनेक्ट करने और IoT डिवाइसों को संदेश भेजने की अनुमति देती है।

    ✅ थोड़ा शोध करें: [IoT Hub अनुमतियां दस्तावेज़](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-security#iot-hub-permissions?WT.mc_id=academic-17441-jabenn) में विभिन्न पॉलिसियों के बारे में पढ़ें।

1. VS Code में `local.settings.json` फ़ाइल खोलें। `Values` सेक्शन के अंदर निम्नलिखित अतिरिक्त मान जोड़ें:

    ```json
    "REGISTRY_MANAGER_CONNECTION_STRING": "<connection string>"
    ```

    `<connection string>` को पिछले चरण से प्राप्त मान से बदलें। इसे वैध JSON बनाने के लिए ऊपर की पंक्ति के बाद एक कॉमा जोड़ना होगा।

### कार्य - डिवाइस को डायरेक्ट मेथड रिक्वेस्ट भेजें

1. Registry Manager के लिए SDK एक Pip पैकेज के माध्यम से उपलब्ध है। इस पैकेज पर निर्भरता जोड़ने के लिए `requirements.txt` फ़ाइल में निम्नलिखित पंक्ति जोड़ें:

    ```sh
    azure-iot-hub
    ```

1. सुनिश्चित करें कि VS Code टर्मिनल में वर्चुअल एनवायरनमेंट सक्रिय है, और Pip पैकेज इंस्टॉल करने के लिए निम्नलिखित कमांड चलाएं:

    ```sh
    pip install -r requirements.txt
    ```

1. `__init__.py` फ़ाइल में निम्नलिखित इम्पोर्ट्स जोड़ें:

    ```python
    import json
    import os
    from azure.iot.hub import IoTHubRegistryManager
    from azure.iot.hub.models import CloudToDeviceMethod
    ```

    यह कुछ सिस्टम लाइब्रेरीज़ के साथ-साथ Registry Manager के साथ संवाद करने और डायरेक्ट मेथड रिक्वेस्ट भेजने के लिए लाइब्रेरीज़ को इम्पोर्ट करता है।

1. `main` मेथड के अंदर का कोड हटा दें, लेकिन मेथड को बनाए रखें।

1. `main` मेथड में निम्नलिखित कोड जोड़ें:

    ```python
    body = json.loads(event.get_body().decode('utf-8'))
    device_id = event.iothub_metadata['connection-device-id']

    logging.info(f'Received message: {body} from {device_id}')
    ```

    यह कोड इवेंट के बॉडी को निकालता है जिसमें IoT डिवाइस द्वारा भेजा गया JSON संदेश होता है।

    फिर यह संदेश के साथ पास किए गए एनोटेशन से डिवाइस ID प्राप्त करता है। इवेंट का बॉडी भेजा गया टेलीमेट्री संदेश होता है, और `iothub_metadata` डिक्शनरी में IoT Hub द्वारा सेट किए गए गुण होते हैं जैसे कि भेजने वाले डिवाइस का ID और संदेश भेजे जाने का समय।

    यह जानकारी लॉग की जाती है। जब आप Functions ऐप को स्थानीय रूप से चलाते हैं तो आप टर्मिनल में यह लॉगिंग देखेंगे।

1. इसके नीचे निम्नलिखित कोड जोड़ें:

    ```python
    soil_moisture = body['soil_moisture']

    if soil_moisture > 450:
        direct_method = CloudToDeviceMethod(method_name='relay_on', payload='{}')
    else:
        direct_method = CloudToDeviceMethod(method_name='relay_off', payload='{}')
    ```

    यह कोड संदेश से मिट्टी की नमी प्राप्त करता है। फिर मिट्टी की नमी की जांच करता है, और मान के आधार पर `relay_on` या `relay_off` डायरेक्ट मेथड रिक्वेस्ट के लिए एक हेल्पर क्लास बनाता है। मेथड रिक्वेस्ट को किसी पेलोड की आवश्यकता नहीं होती है, इसलिए एक खाली JSON दस्तावेज़ भेजा जाता है।

1. इसके नीचे निम्नलिखित कोड जोड़ें:

    ```python
    logging.info(f'Sending direct method request for {direct_method.method_name} for device {device_id}')

    registry_manager_connection_string = os.environ['REGISTRY_MANAGER_CONNECTION_STRING']
    registry_manager = IoTHubRegistryManager(registry_manager_connection_string)
    ```
यह कोड `local.settings.json` फ़ाइल से `REGISTRY_MANAGER_CONNECTION_STRING` को लोड करता है। इस फ़ाइल में मौजूद मान पर्यावरण चर के रूप में उपलब्ध होते हैं, और इन्हें `os.environ` फ़ंक्शन का उपयोग करके पढ़ा जा सकता है, जो सभी पर्यावरण चर का एक डिक्शनरी लौटाता है।

> 💁 जब यह कोड क्लाउड में डिप्लॉय किया जाता है, तो `local.settings.json` फ़ाइल में मौजूद मान *Application Settings* के रूप में सेट किए जाते हैं, और इन्हें पर्यावरण चर से पढ़ा जा सकता है।

इसके बाद कोड कनेक्शन स्ट्रिंग का उपयोग करके Registry Manager हेल्पर क्लास का एक इंस्टेंस बनाता है।

1. इसके नीचे निम्नलिखित कोड जोड़ें:

    ```python
    registry_manager.invoke_device_method(device_id, direct_method)

    logging.info('Direct method request sent!')
    ```

    यह कोड रजिस्ट्री मैनेजर को उस डिवाइस को डायरेक्ट मेथड रिक्वेस्ट भेजने के लिए कहता है जिसने टेलीमेट्री भेजी है।

    > 💁 पहले के पाठों में आपने MQTT का उपयोग करके जो ऐप बनाए थे, उनमें रिले कंट्रोल कमांड सभी डिवाइसों को भेजे जाते थे। कोड ने यह मान लिया था कि आपके पास केवल एक डिवाइस होगा। इस संस्करण में कोड एक ही डिवाइस को मेथड रिक्वेस्ट भेजता है, इसलिए यह कई सेटअप्स के साथ काम करेगा, जैसे कि नमी सेंसर और रिले, और सही डिवाइस को सही डायरेक्ट मेथड रिक्वेस्ट भेजेगा।

1. Functions ऐप चलाएं और सुनिश्चित करें कि आपका IoT डिवाइस डेटा भेज रहा है। आप देखेंगे कि संदेश प्रोसेस हो रहे हैं और डायरेक्ट मेथड रिक्वेस्ट भेजे जा रहे हैं। मिट्टी में नमी सेंसर को अंदर और बाहर ले जाकर मान बदलते हुए देखें और रिले को चालू और बंद होते हुए देखें।

> 💁 आप इस कोड को [code/functions](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud/code/functions) फ़ोल्डर में पा सकते हैं।

## अपने सर्वरलेस कोड को क्लाउड में डिप्लॉय करें

आपका कोड अब लोकल पर काम कर रहा है, तो अगला कदम Functions ऐप को क्लाउड में डिप्लॉय करना है।

### कार्य - क्लाउड संसाधन बनाएं

आपके Functions ऐप को Azure में Functions App संसाधन में डिप्लॉय करने की आवश्यकता है, जो आपके IoT Hub के लिए बनाए गए Resource Group के अंदर होगा। आपको Azure में एक Storage Account भी बनाना होगा ताकि लोकल पर चल रहे इम्यूलेटेड स्टोरेज को बदला जा सके।

1. स्टोरेज अकाउंट बनाने के लिए निम्नलिखित कमांड चलाएं:

    ```sh
    az storage account create --resource-group soil-moisture-sensor \
                              --sku Standard_LRS \
                              --name <storage_name> 
    ```

    `<storage_name>` को अपने स्टोरेज अकाउंट के लिए एक नाम से बदलें। यह नाम वैश्विक रूप से अद्वितीय होना चाहिए क्योंकि यह स्टोरेज अकाउंट तक पहुंचने के लिए उपयोग किए जाने वाले URL का हिस्सा बनता है। इस नाम में केवल छोटे अक्षर और संख्याएं उपयोग की जा सकती हैं, कोई अन्य वर्ण नहीं, और यह 24 वर्णों तक सीमित है। कुछ ऐसा उपयोग करें जैसे `sms` और अंत में एक अद्वितीय पहचानकर्ता जोड़ें, जैसे कुछ रैंडम शब्द या आपका नाम।

    `--sku Standard_LRS` मूल्य निर्धारण स्तर का चयन करता है, जो सबसे कम लागत वाले सामान्य-उद्देश्य वाले अकाउंट को चुनता है। स्टोरेज का कोई मुफ्त स्तर नहीं है, और आप जो उपयोग करते हैं उसके लिए भुगतान करते हैं। लागत अपेक्षाकृत कम है, सबसे महंगा स्टोरेज प्रति गीगाबाइट प्रति माह US$0.05 से कम है।

    ✅ मूल्य निर्धारण के बारे में [Azure Storage Account pricing page](https://azure.microsoft.com/pricing/details/storage/?WT.mc_id=academic-17441-jabenn) पर पढ़ें।

1. एक Function App बनाने के लिए निम्नलिखित कमांड चलाएं:

    ```sh
    az functionapp create --resource-group soil-moisture-sensor \
                          --runtime python \
                          --functions-version 3 \
                          --os-type Linux \
                          --consumption-plan-location <location> \
                          --storage-account <storage_name> \
                          --name <functions_app_name>
    ```

    `<location>` को उस स्थान से बदलें जिसे आपने पिछले पाठ में Resource Group बनाते समय उपयोग किया था।

    `<storage_name>` को उस स्टोरेज अकाउंट के नाम से बदलें जिसे आपने पिछले चरण में बनाया था।

    `<functions_app_name>` को अपने Functions App के लिए एक अद्वितीय नाम से बदलें। यह नाम वैश्विक रूप से अद्वितीय होना चाहिए क्योंकि यह Functions App तक पहुंचने के लिए उपयोग किए जाने वाले URL का हिस्सा बनता है। कुछ ऐसा उपयोग करें जैसे `soil-moisture-sensor-` और अंत में एक अद्वितीय पहचानकर्ता जोड़ें, जैसे कुछ रैंडम शब्द या आपका नाम।

    `--functions-version 3` विकल्प Azure Functions के संस्करण को सेट करता है। संस्करण 3 नवीनतम संस्करण है।

    `--os-type Linux` Functions रनटाइम को इन फंक्शन्स को होस्ट करने के लिए Linux का उपयोग करने के लिए कहता है। Functions को Linux या Windows पर होस्ट किया जा सकता है, उपयोग किए गए प्रोग्रामिंग भाषा के आधार पर। Python ऐप्स केवल Linux पर समर्थित हैं।

### कार्य - अपने एप्लिकेशन सेटिंग्स अपलोड करें

जब आपने अपने Functions App को विकसित किया, तो आपने IoT Hub के लिए कनेक्शन स्ट्रिंग्स के लिए `local.settings.json` फ़ाइल में कुछ सेटिंग्स संग्रहीत कीं। इन्हें Azure में आपके Functions App में Application Settings में लिखा जाना चाहिए ताकि आपका कोड इन्हें उपयोग कर सके।

> 🎓 `local.settings.json` फ़ाइल केवल लोकल विकास सेटिंग्स के लिए है, और इन्हें स्रोत कोड नियंत्रण, जैसे GitHub, में चेक-इन नहीं किया जाना चाहिए। जब क्लाउड में डिप्लॉय किया जाता है, तो Application Settings का उपयोग किया जाता है। Application Settings क्लाउड में होस्ट किए गए key/value जोड़े हैं और इन्हें पर्यावरण चर से पढ़ा जाता है, या तो आपके कोड में या रनटाइम द्वारा जब आपका कोड IoT Hub से कनेक्ट होता है।

1. Functions App Application Settings में `IOT_HUB_CONNECTION_STRING` सेटिंग सेट करने के लिए निम्नलिखित कमांड चलाएं:

    ```sh
    az functionapp config appsettings set --resource-group soil-moisture-sensor \
                                          --name <functions_app_name> \
                                          --settings "IOT_HUB_CONNECTION_STRING=<connection string>"
    ```

    `<functions_app_name>` को उस नाम से बदलें जिसे आपने अपने Functions App के लिए उपयोग किया था।

    `<connection string>` को अपने `local.settings.json` फ़ाइल से `IOT_HUB_CONNECTION_STRING` के मान से बदलें।

1. ऊपर दिए गए चरण को दोहराएं, लेकिन `REGISTRY_MANAGER_CONNECTION_STRING` के मान को `local.settings.json` फ़ाइल से संबंधित मान से सेट करें।

जब आप ये कमांड चलाते हैं, तो वे Functions App के लिए सभी Application Settings की सूची भी आउटपुट करेंगे। आप इसका उपयोग यह जांचने के लिए कर सकते हैं कि आपके मान सही तरीके से सेट किए गए हैं।

> 💁 आप देखेंगे कि `AzureWebJobsStorage` के लिए पहले से ही एक मान सेट है। आपके `local.settings.json` फ़ाइल में, इसे लोकल स्टोरेज इम्यूलेटर का उपयोग करने के लिए सेट किया गया था। जब आपने Functions App बनाया, तो आपने स्टोरेज अकाउंट को एक पैरामीटर के रूप में पास किया, और यह इस सेटिंग में स्वचालित रूप से सेट हो गया।

### कार्य - अपने Functions App को क्लाउड में डिप्लॉय करें

अब जब Functions App तैयार है, तो आपका कोड डिप्लॉय किया जा सकता है।

1. अपने Functions App को प्रकाशित करने के लिए VS Code टर्मिनल से निम्नलिखित कमांड चलाएं:

    ```sh
    func azure functionapp publish <functions_app_name>
    ```

    `<functions_app_name>` को उस नाम से बदलें जिसे आपने अपने Functions App के लिए उपयोग किया था।

कोड को पैक किया जाएगा और Functions App को भेजा जाएगा, जहां इसे डिप्लॉय और शुरू किया जाएगा। बहुत सारे कंसोल आउटपुट होंगे, जो डिप्लॉयमेंट की पुष्टि और डिप्लॉय किए गए फंक्शन्स की सूची के साथ समाप्त होंगे। इस मामले में सूची में केवल ट्रिगर शामिल होगा।

```output
Deployment successful.
Remote build succeeded!
Syncing triggers...
Functions in soil-moisture-sensor:
    iot-hub-trigger - [eventHubTrigger]
```

सुनिश्चित करें कि आपका IoT डिवाइस चल रहा है। मिट्टी की नमी को समायोजित करके नमी स्तर बदलें, या सेंसर को मिट्टी के अंदर और बाहर ले जाएं। आप देखेंगे कि मिट्टी की नमी बदलते ही रिले चालू और बंद हो रहा है।

---

## 🚀 चुनौती

पिछले पाठ में, आपने रिले के लिए टाइमिंग को प्रबंधित किया था, जब रिले चालू था और थोड़ी देर बाद बंद हो गया था, तो MQTT संदेशों से अनसब्सक्राइब करके। आप यहां इस विधि का उपयोग नहीं कर सकते - आप अपने IoT Hub ट्रिगर को अनसब्सक्राइब नहीं कर सकते।

सोचें कि आप अपने Functions App में इसे संभालने के लिए अलग-अलग तरीकों का उपयोग कैसे कर सकते हैं।

## पोस्ट-लेक्चर क्विज़

[पोस्ट-लेक्चर क्विज़](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/18)

## समीक्षा और स्व-अध्ययन

* [Serverless Computing page on Wikipedia](https://wikipedia.org/wiki/Serverless_computing) पर सर्वरलेस कंप्यूटिंग के बारे में पढ़ें।
* Azure में सर्वरलेस का उपयोग करने के बारे में और अधिक उदाहरणों सहित [Go serverless for your IoT needs Azure blog post](https://azure.microsoft.com/blog/go-serverless-for-your-iot-needs/?WT.mc_id=academic-17441-jabenn) पर पढ़ें।
* [Azure Functions YouTube channel](https://www.youtube.com/c/AzureFunctions) पर Azure Functions के बारे में अधिक जानें।

## असाइनमेंट

[मैनुअल रिले नियंत्रण जोड़ें](assignment.md)

**अस्वीकरण**:  
यह दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) का उपयोग करके अनुवादित किया गया है। जबकि हम सटीकता सुनिश्चित करने का प्रयास करते हैं, कृपया ध्यान दें कि स्वचालित अनुवाद में त्रुटियां या अशुद्धियां हो सकती हैं। मूल भाषा में उपलब्ध मूल दस्तावेज़ को प्रामाणिक स्रोत माना जाना चाहिए। महत्वपूर्ण जानकारी के लिए, पेशेवर मानव अनुवाद की सिफारिश की जाती है। इस अनुवाद के उपयोग से उत्पन्न किसी भी गलतफहमी या गलत व्याख्या के लिए हम उत्तरदायी नहीं हैं।