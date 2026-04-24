# आफ्नो एप्लिकेसनको तर्कलाई क्लाउडमा सार्नुहोस्

![यस पाठको स्केच नोट](../../../../../translated_images/ne/lesson-9.dfe99c8e891f48e1.webp)

> स्केच नोट [नित्या नरसिम्हन](https://github.com/nitya) द्वारा। ठूलो संस्करणको लागि तस्बिरमा क्लिक गर्नुहोस्।

यो पाठ [IoT for Beginners Project 2 - Digital Agriculture series](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) अन्तर्गत [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn) बाट सिकाइएको थियो।

[![तपाईंको IoT उपकरणलाई serverless कोडले नियन्त्रण गर्नुहोस्](https://img.youtube.com/vi/VVZDcs5u1_I/0.jpg)](https://youtu.be/VVZDcs5u1_I)

## पाठ अघि क्विज

[पाठ अघि क्विज](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/17)

## परिचय

अघिल्लो पाठमा, तपाईंले आफ्नो बिरुवाको माटोको चिस्यान अनुगमन र रिले नियन्त्रणलाई क्लाउड-आधारित IoT सेवासँग कसरी जडान गर्ने भनेर सिक्नुभयो। अर्को चरण भनेको रिलेको समय नियन्त्रण गर्ने सर्भर कोडलाई क्लाउडमा सार्नु हो। यस पाठमा, तपाईंले serverless functions प्रयोग गरेर यो कसरी गर्ने भनेर सिक्नुहुनेछ।

यस पाठमा हामी निम्न विषयहरू समेट्नेछौं:

* [Serverless के हो?](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Serverless एप्लिकेसन बनाउनुहोस्](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [IoT Hub इभेन्ट ट्रिगर बनाउनुहोस्](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Serverless कोडबाट प्रत्यक्ष विधि अनुरोधहरू पठाउनुहोस्](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [तपाईंको serverless कोडलाई क्लाउडमा डिप्लोय गर्नुहोस्](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)

## Serverless के हो?

Serverless, वा serverless computing, भनेको साना कोड ब्लकहरू बनाउनु हो, जुन विभिन्न प्रकारका घटनाहरूको प्रतिक्रियामा क्लाउडमा चल्छ। जब घटना हुन्छ, तपाईंको कोड चल्छ, र यसलाई घटनाको बारेमा डेटा पास गरिन्छ। यी घटनाहरू वेब अनुरोधहरू, कतारमा राखिएका सन्देशहरू, डाटाबेसमा भएका परिवर्तनहरू, वा IoT उपकरणहरूले IoT सेवामा पठाएका सन्देशहरू जस्ता धेरै चीजहरूबाट हुन सक्छन्।

![IoT सेवाबाट serverless सेवामा पठाइएका घटनाहरू, सबै एकै समयमा धेरै functions द्वारा प्रशोधन भइरहेको](../../../../../translated_images/ne/iot-messages-to-serverless.0194da1cc0732bb7.webp)

> 💁 यदि तपाईंले पहिले डाटाबेस ट्रिगरहरू प्रयोग गर्नुभएको छ भने, तपाईं यसलाई त्यस्तै सोच्न सक्नुहुन्छ, कोड कुनै घटनाले ट्रिगर गर्दा चल्छ, जस्तै पङ्क्ति थप्दा।

![जब धेरै घटनाहरू एकै समयमा पठाइन्छ, serverless सेवा स्केल हुन्छ र सबैलाई एकै समयमा चलाउँछ](../../../../../translated_images/ne/serverless-scaling.f8c769adf0413fd1.webp)

तपाईंको कोड केवल घटना हुँदा मात्र चल्छ, अन्य समयमा तपाईंको कोड सक्रिय हुँदैन। घटना हुन्छ, तपाईंको कोड लोड हुन्छ र चल्छ। यसले serverless लाई धेरै स्केलेबल बनाउँछ - यदि धेरै घटनाहरू एकै समयमा हुन्छन् भने, क्लाउड प्रदायकले तपाईंको function लाई आवश्यकताअनुसार धेरै पटक चलाउन सक्छ। यसको नकारात्मक पक्ष भनेको यदि तपाईंले घटनाहरू बीच जानकारी साझा गर्न आवश्यक छ भने, तपाईंले यसलाई मेमोरीमा भण्डारण गर्नुको सट्टा डाटाबेसमा सुरक्षित गर्नुपर्ने हुन्छ।

तपाईंको कोड एउटा function को रूपमा लेखिन्छ, जसले घटनाको विवरणलाई एउटा प्यारामिटरको रूपमा लिन्छ। यी serverless functions लेख्न तपाईंले धेरै प्रकारका प्रोग्रामिङ भाषाहरू प्रयोग गर्न सक्नुहुन्छ।

> 🎓 Serverless लाई Functions as a Service (FaaS) पनि भनिन्छ, किनभने प्रत्येक इभेन्ट ट्रिगरलाई कोडमा function को रूपमा कार्यान्वयन गरिन्छ।

नामले संकेत गरे पनि, serverless ले वास्तवमा सर्भरहरू प्रयोग गर्छ। नामाकरण यसकारण गरिएको हो कि तपाईं, एक विकासकर्ता, तपाईंको कोड चलाउन आवश्यक सर्भरहरूको बारेमा चिन्ता गर्नुहुन्न, तपाईंलाई केवल यो थाहा छ कि तपाईंको कोड घटना हुँदा चल्छ। क्लाउड प्रदायकसँग serverless *runtime* हुन्छ, जसले सर्भरहरू, नेटवर्किङ, भण्डारण, CPU, मेमोरी र तपाईंको कोड चलाउन आवश्यक सबै कुरा व्यवस्थापन गर्छ। यस मोडेलले तपाईंलाई सर्भरको आधारमा शुल्क तिर्न अनुमति दिँदैन, किनभने यहाँ कुनै सर्भर छैन। यसको सट्टा, तपाईंको कोड चलिरहेको समय र प्रयोग गरिएको मेमोरीको आधारमा शुल्क लाग्छ।

> 💰 Serverless क्लाउडमा कोड चलाउने सबैभन्दा सस्तो तरिकामध्ये एक हो। उदाहरणका लागि, लेख्ने समयमा, एक क्लाउड प्रदायकले तपाईंको सबै serverless functions लाई महिनामा 1,000,000 पटक चलाउन अनुमति दिन्छ, त्यसपछि मात्र शुल्क लाग्छ, र त्यसपछि प्रत्येक 1,000,000 कार्यान्वयनको लागि US$0.20 चार्ज गर्छ। जब तपाईंको कोड चलिरहेको हुँदैन, तपाईंले शुल्क तिर्नु पर्दैन।

IoT विकासकर्ताको रूपमा, serverless मोडेल आदर्श हो। तपाईंले function लेख्न सक्नुहुन्छ, जुन तपाईंको क्लाउड-होस्ट गरिएको IoT सेवामा जडान भएका कुनै पनि IoT उपकरणबाट पठाइएका सन्देशहरूको प्रतिक्रियामा बोलाइन्छ। तपाईंको कोडले पठाइएका सबै सन्देशहरूलाई ह्यान्डल गर्नेछ, तर आवश्यक पर्दा मात्र चल्नेछ।

✅ तपाईंले MQTT मार्फत सन्देशहरू सुन्ने server कोड लेख्नुभएको कोडलाई फिर्ता हेर्नुहोस्। यो serverless प्रयोग गरेर क्लाउडमा कसरी चल्न सक्छ? serverless computing समर्थन गर्न कोडलाई कसरी परिवर्तन गर्न सकिन्छ जस्तो लाग्छ?

> 💁 Serverless मोडेल अन्य क्लाउड सेवाहरूमा पनि विस्तार भइरहेको छ, कोड चलाउनु बाहेक। उदाहरणका लागि, serverless डाटाबेसहरू क्लाउडमा उपलब्ध छन्, जसले serverless मूल्य निर्धारण मोडेल प्रयोग गर्छन्, जहाँ तपाईंले डाटाबेसमा गरिएको अनुरोधहरूको आधारमा शुल्क तिर्नुहुन्छ, जस्तै क्वेरी वा इनसर्ट। उदाहरणका लागि, प्राथमिक कुञ्जीको विरुद्धमा एउटा पङ्क्ति चयन गर्दा जटिल अपरेसनको तुलनामा कम लागत लाग्छ, जसले धेरै तालिकाहरूलाई जोड्छ र हजारौं पङ्क्तिहरू फिर्ता गर्छ।

## Serverless एप्लिकेसन बनाउनुहोस्

Microsoft को serverless computing सेवा Azure Functions हो।

![Azure Functions को लोगो](../../../../../translated_images/ne/azure-functions-logo.1cfc8e3204c9c44a.webp)

तलको छोटो भिडियोमा Azure Functions को बारेमा एक झलक छ।

[![Azure Functions को झलक भिडियो](https://img.youtube.com/vi/8-jz5f_JyEQ/0.jpg)](https://www.youtube.com/watch?v=8-jz5f_JyEQ)

> 🎥 माथिको तस्बिरमा क्लिक गरेर भिडियो हेर्नुहोस्।

✅ केही समय लिनुहोस् र [Microsoft Azure Functions को दस्तावेज](https://docs.microsoft.com/azure/azure-functions/functions-overview?WT.mc_id=academic-17441-jabenn) मा Azure Functions को झलक पढ्नुहोस्।

Azure Functions लेख्न, तपाईंले आफ्नो रोजाइको भाषामा Azure Functions एप सुरु गर्नुहुन्छ। Azure Functions ले Python, JavaScript, TypeScript, C#, F#, Java, र Powershell लाई समर्थन गर्दछ। यस पाठमा, तपाईंले Python मा Azure Functions एप लेख्न सिक्नुहुनेछ।

> 💁 Azure Functions ले कस्टम ह्यान्डलरहरूलाई पनि समर्थन गर्दछ, जसले HTTP अनुरोधहरूलाई समर्थन गर्ने कुनै पनि भाषामा तपाईंको functions लेख्न अनुमति दिन्छ, पुराना भाषाहरू जस्तै COBOL समेत।

Functions एपहरूमा एक वा बढी *triggers* हुन्छन् - functions जसले घटनाहरूको प्रतिक्रियामा काम गर्छन्। तपाईंको Functions एपमा धेरै triggers हुन सक्छन्, जसले साझा कन्फिगरेसन प्रयोग गर्छन्। उदाहरणका लागि, तपाईंको Functions एपको कन्फिगरेसन फाइलमा तपाईंको IoT Hub को जडान विवरणहरू हुन सक्छन्, र एपका सबै functions ले यसलाई जडान गर्न र घटनाहरू सुन्न प्रयोग गर्न सक्छन्।

### कार्य - Azure Functions उपकरण स्थापना गर्नुहोस्

> लेख्ने समयमा, Azure Functions कोड उपकरणहरू Python प्रोजेक्टहरूसँग Apple Silicon मा पूर्ण रूपमा काम गरिरहेका छैनन्। तपाईंले Intel-आधारित Mac, Windows PC, वा Linux PC प्रयोग गर्नुपर्नेछ।

Azure Functions को एक उत्कृष्ट विशेषता भनेको तपाईंले यसलाई स्थानीय रूपमा चलाउन सक्नुहुन्छ। क्लाउडमा प्रयोग हुने उस्तै runtime तपाईंको कम्प्युटरमा चलाउन सकिन्छ, जसले तपाईंलाई IoT सन्देशहरूको प्रतिक्रियामा कोड लेख्न र स्थानीय रूपमा चलाउन अनुमति दिन्छ। तपाईंले घटनाहरू ह्यान्डल गर्दा आफ्नो कोड डिबग पनि गर्न सक्नुहुन्छ। जब तपाईं आफ्नो कोडसँग सन्तुष्ट हुनुहुन्छ, यसलाई क्लाउडमा डिप्लोय गर्न सकिन्छ।

Azure Functions उपकरण CLI को रूपमा उपलब्ध छ, जसलाई Azure Functions Core Tools भनिन्छ।

1. [Azure Functions Core Tools को दस्तावेज](https://docs.microsoft.com/azure/azure-functions/functions-run-local?WT.mc_id=academic-17441-jabenn) मा दिइएका निर्देशनहरू पालना गरेर Azure Functions कोर उपकरणहरू स्थापना गर्नुहोस्।

1. VS Code का लागि Azure Functions विस्तार स्थापना गर्नुहोस्। यो विस्तारले Azure functions सिर्जना, डिबग र डिप्लोय गर्न समर्थन प्रदान गर्दछ। [Azure Functions विस्तारको दस्तावेज](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-azuretools.vscode-azurefunctions) मा VS Code मा यो विस्तार स्थापना गर्ने निर्देशनहरू हेर्नुहोस्।

जब तपाईं आफ्नो Azure Functions एपलाई क्लाउडमा डिप्लोय गर्नुहुन्छ, यसले एप्लिकेसन फाइलहरू र लग फाइलहरू जस्ता चीजहरू भण्डारण गर्न सानो मात्रामा क्लाउड भण्डारण प्रयोग गर्न आवश्यक छ। जब तपाईं आफ्नो Functions एपलाई स्थानीय रूपमा चलाउनुहुन्छ, तपाईंले अझै पनि क्लाउड भण्डारणमा जडान गर्न आवश्यक छ, तर वास्तविक क्लाउड भण्डारण प्रयोग गर्नुको सट्टा, तपाईंले [Azurite](https://github.com/Azure/Azurite) नामक भण्डारण इम्युलेटर प्रयोग गर्न सक्नुहुन्छ। यो स्थानीय रूपमा चल्छ तर क्लाउड भण्डारण जस्तै व्यवहार गर्छ।

> 🎓 Azure मा, Azure Functions ले प्रयोग गर्ने भण्डारण Azure Storage Account हो। यी खाताहरूले फाइलहरू, ब्लबहरू, तालिकाहरूमा डेटा, वा कतारमा डेटा भण्डारण गर्न सक्छन्। तपाईंले धेरै एपहरू, जस्तै Functions एप र वेब एप, बीचमा एउटै भण्डारण खाता साझा गर्न सक्नुहुन्छ।

1. Azurite एक Node.js एप हो, त्यसैले तपाईंले Node.js स्थापना गर्नुपर्नेछ। [Node.js वेबसाइट](https://nodejs.org/) मा डाउनलोड र स्थापना निर्देशनहरू फेला पार्न सक्नुहुन्छ। यदि तपाईं Mac प्रयोग गर्दै हुनुहुन्छ भने, तपाईंले यसलाई [Homebrew](https://formulae.brew.sh/formula/node) बाट पनि स्थापना गर्न सक्नुहुन्छ।

1. निम्न आदेश प्रयोग गरेर Azurite स्थापना गर्नुहोस् (`npm` Node.js स्थापना गर्दा स्थापना हुने उपकरण हो):

    ```sh
    npm install -g azurite
    ```

1. Azurite लाई डेटा भण्डारण गर्न प्रयोग गर्न `azurite` नामक फोल्डर बनाउनुहोस्:

    ```sh
    mkdir azurite
    ```

1. Azurite चलाउनुहोस्, यस नयाँ फोल्डरलाई पास गर्दै:

    ```sh
    azurite --location azurite
    ```

    Azurite भण्डारण इम्युलेटर सुरु हुनेछ र स्थानीय Functions runtime जडान गर्न तयार हुनेछ।

    ```output
    ➜  ~ azurite --location azurite  
    Azurite Blob service is starting at http://127.0.0.1:10000
    Azurite Blob service is successfully listening at http://127.0.0.1:10000
    Azurite Queue service is starting at http://127.0.0.1:10001
    Azurite Queue service is successfully listening at http://127.0.0.1:10001
    Azurite Table service is starting at http://127.0.0.1:10002
    Azurite Table service is successfully listening at http://127.0.0.1:10002
    ```

### कार्य - Azure Functions प्रोजेक्ट बनाउनुहोस्

Azure Functions CLI लाई नयाँ Functions एप बनाउन प्रयोग गर्न सकिन्छ।

1. आफ्नो Functions एपको लागि फोल्डर बनाउनुहोस् र यसमा जानुहोस्। यसलाई `soil-moisture-trigger` नाम दिनुहोस्:

    ```sh
    mkdir soil-moisture-trigger
    cd soil-moisture-trigger
    ```

1. यस फोल्डरभित्र Python भर्चुअल वातावरण बनाउनुहोस्:

    ```sh
    python3 -m venv .venv
    ```

1. भर्चुअल वातावरण सक्रिय गर्नुहोस्:

    * Windows मा:
        * यदि तपाईं Command Prompt, वा Windows Terminal मार्फत Command Prompt प्रयोग गर्दै हुनुहुन्छ भने, निम्न आदेश चलाउनुहोस्:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * यदि तपाईं PowerShell प्रयोग गर्दै हुनुहुन्छ भने, निम्न आदेश चलाउनुहोस्:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

    * macOS वा Linux मा, निम्न आदेश चलाउनुहोस्:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 यी आदेशहरू तपाईंले भर्चुअल वातावरण बनाएको स्थानबाट चलाउनुपर्छ। तपाईंले `.venv` फोल्डरमा कहिल्यै जानु पर्दैन, तपाईंले सधैं सक्रिय आदेश र प्याकेजहरू स्थापना गर्न वा कोड चलाउन आदेशहरू चलाउनु पर्ने फोल्डरबाट चलाउनुहोस्।

1. निम्न आदेश चलाएर यस फोल्डरमा Functions एप बनाउनुहोस्:

    ```sh
    func init --worker-runtime python soil-moisture-trigger
    ```

    यसले हालको फोल्डरभित्र तीन फाइलहरू बनाउनेछ:

    * `host.json` - यो JSON दस्तावेजले तपाईंको Functions एपका सेटिङहरू समावेश गर्दछ। तपाईंलाई यी सेटिङहरू परिमार्जन गर्न आवश्यक पर्दैन।
    * `local.settings.json` - यो JSON दस्तावेजले तपाईंको एपले स्थानीय रूपमा चल्दा प्रयोग गर्ने सेटिङहरू समावेश गर्दछ, जस्तै तपाईंको IoT Hub का लागि जडान स्ट्रिङहरू। यी सेटिङहरू स्थानीय मात्र हुन्, र स्रोत कोड नियन्त्रणमा थपिनु हुँदैन। जब तपाईं एपलाई क्लाउडमा डिप्लोय गर्नुहुन्छ, यी सेटिङहरू डिप्लोय हुँदैनन्, यसको सट्टा तपाईंका सेटिङहरू एप्लिकेसन सेटिङहरूबाट लोड हुन्छन्। यो पाठमा पछि यो कभर गरिनेछ।
    * `requirements.txt` - यो [Pip requirements फाइल](https://pip.pypa.io/en/stable/user_guide/#requirements-files) हो, जसले तपाईंको Functions एप चलाउन आवश्यक Pip प्याकेजहरू समावेश गर्दछ।

1. `local.settings.json` फाइलमा Functions एपले प्रयोग गर्ने भण्डारण खाताको लागि सेटिङ छ। यो डिफल्ट रूपमा खाली सेटिङमा हुन्छ, त्यसैले यसलाई सेट गर्न आवश्यक छ। Azurite स्थानीय भण्डारण इम्युलेटरमा जडान गर्न, यो मानलाई निम्नमा सेट गर्नुहोस्:

    ```json
    "AzureWebJobsStorage": "UseDevelopmentStorage=true",
    ```

1. आवश्यक Pip प्याकेजहरू requirements फाइल प्रयोग गरेर स्थापना गर्नुहोस्:

    ```sh
    pip install -r requirements.txt
    ```

    > 💁 आवश्यक Pip प्याकेजहरू यो फाइलमा हुनुपर्छ, ताकि जब Functions एप क्लाउडमा डिप्लोय हुन्छ, runtime ले सही प्याकेजहरू स्थापना गर्न सुनिश्चित गर्न सक्छ।

1. सबै कुरा सही रूपमा काम गरिरहेको छ कि छैन परीक्षण गर्न, तपाईं Functions runtime सुरु गर्न सक्नुहुन्छ। यो गर्न निम्न आदेश चलाउनुहोस्:

    ```sh
    func start
    ```

    तपाईंले runtime सुरु भएको देख्नुहुनेछ र यसले कुनै पनि job functions (triggers) फेला पारेन भनेर रिपोर्ट गर्नेछ।

    ```output
    (.venv) ➜  soil-moisture-trigger func start
    Found Python version 3.9.1 (python3).
    
    Azure Functions Core Tools
    Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    Function Runtime Version: 3.0.15417.0
    
    [2021-05-05T01:24:46.795Z] No job functions found.
    ```
> ⚠️ यदि तपाईंलाई फायरवाल सूचना प्राप्त हुन्छ, पहुँच अनुमति दिनुहोस् किनभने `func` एप्लिकेशनले तपाईंको नेटवर्कमा पढ्न र लेख्न सक्षम हुन आवश्यक छ।
> ⚠️ यदि तपाईं macOS प्रयोग गर्दै हुनुहुन्छ भने, आउटपुटमा चेतावनीहरू देखिन सक्छ:
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
> जबसम्म Functions एप सही रूपमा सुरु हुन्छ र चलिरहेको functions देखाउँछ, यी चेतावनीहरूलाई बेवास्ता गर्न सकिन्छ। [Microsoft Docs Q&A मा यो प्रश्न](https://docs.microsoft.com/answers/questions/396617/azure-functions-core-tools-error-osx-devshmazurefu.html?WT.mc_id=academic-17441-jabenn) अनुसार, यसलाई बेवास्ता गर्न सकिन्छ।

1. `ctrl+c` थिचेर Functions एप बन्द गर्नुहोस्।

1. हालको फोल्डरलाई VS Code मा खोल्नुहोस्। यो VS Code खोलेर फोल्डर खोल्ने वा निम्न कमाण्ड चलाएर गर्न सकिन्छ:

    ```sh
    code .
    ```

    VS Code ले तपाईंको Functions प्रोजेक्ट पत्ता लगाउनेछ र निम्न सूचना देखाउनेछ:

    ```output
    Detected an Azure Functions Project in folder "soil-moisture-trigger" that may have been created outside of
    VS Code. Initialize for optimal use with VS Code?
    ```

    ![सूचना](../../../../../translated_images/ne/vscode-azure-functions-init-notification.bd19b49229963edb.webp)

    यस सूचनाबाट **Yes** चयन गर्नुहोस्।

1. सुनिश्चित गर्नुहोस् कि Python भर्चुअल वातावरण VS Code टर्मिनलमा चलिरहेको छ। आवश्यक परेमा यसलाई बन्द गरेर पुनः सुरु गर्नुहोस्।

## IoT Hub इभेन्ट ट्रिगर सिर्जना गर्नुहोस्

Functions एप तपाईंको serverless कोडको खोल हो। IoT Hub इभेन्टहरूमा प्रतिक्रिया दिन, तपाईं यस एपमा IoT Hub ट्रिगर थप्न सक्नुहुन्छ। यो ट्रिगरले IoT Hub मा पठाइएका सन्देशहरूको स्ट्रिममा जडान गर्न र तिनीहरूमा प्रतिक्रिया दिन आवश्यक छ। सन्देशहरूको यो स्ट्रिम प्राप्त गर्न, तपाईंको ट्रिगरले IoT Hub को *event hub compatible endpoint* मा जडान गर्न आवश्यक छ।

IoT Hub अर्को Azure सेवा Azure Event Hubs मा आधारित छ। Event Hubs एक सेवा हो जसले सन्देशहरू पठाउन र प्राप्त गर्न अनुमति दिन्छ। IoT Hub ले IoT उपकरणहरूको लागि सुविधाहरू थप्न यसलाई विस्तार गर्दछ। IoT Hub बाट सन्देशहरू पढ्न जडान गर्ने तरिका Event Hubs प्रयोग गर्दा जस्तै हो।

✅ अनुसन्धान गर्नुहोस्: [Azure Event Hubs डकुमेन्टेशन](https://docs.microsoft.com/azure/event-hubs/event-hubs-about?WT.mc_id=academic-17441-jabenn) मा Event Hubs को अवलोकन पढ्नुहोस्। आधारभूत सुविधाहरू IoT Hub सँग कसरी तुलना हुन्छन्?

IoT उपकरणले IoT Hub मा जडान गर्न, यसले गोप्य कुञ्जी प्रयोग गर्नुपर्छ जसले सुनिश्चित गर्दछ कि केवल अनुमति प्राप्त उपकरणहरूले जडान गर्न सक्छ। सन्देशहरू पढ्न जडान गर्दा पनि यही लागू हुन्छ। तपाईंको कोडलाई गोप्य कुञ्जी सहितको जडान स्ट्रिङ चाहिन्छ, साथै IoT Hub को विवरण।

> 💁 तपाईंले प्राप्त गर्ने डिफल्ट जडान स्ट्रिङमा **iothubowner** अनुमति हुन्छ, जसले यसलाई प्रयोग गर्ने कुनै पनि कोडलाई IoT Hub मा पूर्ण अनुमति दिन्छ। आदर्श रूपमा, तपाईंले आवश्यक न्यूनतम स्तरको अनुमति प्रयोग गरेर जडान गर्नुपर्छ। यो अर्को पाठमा समेटिनेछ।

एकपटक तपाईंको ट्रिगर जडान भएपछि, IoT Hub मा पठाइएका प्रत्येक सन्देशको लागि फङ्क्सन भित्रको कोडलाई कल गरिनेछ, चाहे कुन उपकरणले पठाएको हो। ट्रिगरले सन्देशलाई प्यारामिटरको रूपमा पास गर्नेछ।

### कार्य - Event Hub compatible endpoint जडान स्ट्रिङ प्राप्त गर्नुहोस्

1. VS Code टर्मिनलबाट निम्न कमाण्ड चलाउनुहोस् ताकि IoT Hub को Event Hub compatible endpoint को जडान स्ट्रिङ प्राप्त गर्न सकियोस्:

    ```sh
    az iot hub connection-string show --default-eventhub \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    `<hub_name>` लाई तपाईंले IoT Hub को लागि प्रयोग गरेको नामले प्रतिस्थापन गर्नुहोस्।

1. VS Code मा `local.settings.json` फाइल खोल्नुहोस्। `Values` सेक्सन भित्र निम्न थप मान थप्नुहोस्:

    ```json
    "IOT_HUB_CONNECTION_STRING": "<connection string>"
    ```

    `<connection string>` लाई अघिल्लो चरणबाट प्राप्त मानले प्रतिस्थापन गर्नुहोस्। यो मान्य JSON बनाउन माथिल्लो लाइन पछि अल्पविराम थप्न आवश्यक हुनेछ।

### कार्य - इभेन्ट ट्रिगर सिर्जना गर्नुहोस्

अब तपाईं इभेन्ट ट्रिगर सिर्जना गर्न तयार हुनुहुन्छ।

1. VS Code टर्मिनलबाट `soil-moisture-trigger` फोल्डर भित्र निम्न कमाण्ड चलाउनुहोस्:

    ```sh
    func new --name iot-hub-trigger --template "Azure Event Hub trigger"
    ```

    यसले `iot-hub-trigger` नामक नयाँ Function सिर्जना गर्दछ। ट्रिगर IoT Hub मा Event Hub compatible endpoint मा जडान हुनेछ, ताकि तपाईं Event Hub ट्रिगर प्रयोग गर्न सक्नुहुन्छ। IoT Hub को लागि कुनै विशिष्ट ट्रिगर छैन।

यसले `soil-moisture-trigger` फोल्डर भित्र `iot-hub-trigger` नामक फोल्डर सिर्जना गर्नेछ जसमा निम्न फाइलहरू समावेश हुनेछ:

* `__init__.py` - यो Python कोड फाइल हो जसमा ट्रिगर समावेश छ। यो फोल्डरलाई Python मोड्युलमा परिणत गर्न मानक Python फाइल नाम कन्वेन्सन प्रयोग गरिएको छ।

    यो फाइलमा निम्न कोड समावेश हुनेछ:

    ```python
    import logging

    import azure.functions as func


    def main(event: func.EventHubEvent):
        logging.info('Python EventHub trigger processed an event: %s',
                    event.get_body().decode('utf-8'))
    ```

    ट्रिगरको मुख्य भाग `main` फङ्क्सन हो। IoT Hub बाट इभेन्टहरू प्राप्त गर्दा यो फङ्क्सन कल गरिन्छ। यस फङ्क्सनमा `event` नामक प्यारामिटर हुन्छ जसले `EventHubEvent` समावेश गर्दछ। IoT Hub मा सन्देश पठाइएपछि, यो फङ्क्सन `event` को रूपमा सन्देश पास गर्दै कल गरिन्छ, साथै अघिल्लो पाठमा देखिएका एनोटेसनहरू जस्तै गुणहरू।

    यो फङ्क्सनको मुख्य भागले इभेन्टलाई लग गर्दछ।

* `function.json` - यसमा ट्रिगरको कन्फिगरेसन समावेश छ। मुख्य कन्फिगरेसन `bindings` नामक सेक्सनमा छ। Binding Azure Functions र अन्य Azure सेवाहरू बीचको जडानको लागि प्रयोग गरिने शब्द हो। यो फङ्क्सनमा Event Hub मा इनपुट बाइन्डिङ छ - यो Event Hub मा जडान गर्दछ र डेटा प्राप्त गर्दछ।

    > 💁 तपाईं आउटपुट बाइन्डिङ पनि थप्न सक्नुहुन्छ ताकि फङ्क्सनको आउटपुट अर्को सेवामा पठाइयोस्। उदाहरणका लागि, तपाईं डेटाबेसमा आउटपुट बाइन्डिङ थप्न सक्नुहुन्छ र IoT Hub इभेन्टलाई फङ्क्सनबाट फर्काउन सक्नुहुन्छ, र यो स्वतः डेटाबेसमा समावेश हुनेछ।

    ✅ अनुसन्धान गर्नुहोस्: [Azure Functions ट्रिगर र बाइन्डिङ अवधारणाहरू](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python) डकुमेन्टेशनमा बाइन्डिङको बारेमा पढ्नुहोस्।

    `bindings` सेक्सनमा बाइन्डिङको कन्फिगरेसन समावेश छ। चासोका मानहरू हुन्:

  * `"type": "eventHubTrigger"` - यसले फङ्क्सनलाई Event Hub बाट इभेन्टहरू सुन्न आवश्यक छ भनी बताउँछ।
  * `"name": "events"` - यो Event Hub इभेन्टहरूको लागि प्रयोग गर्नुपर्ने प्यारामिटर नाम हो। यो Python कोडमा `main` फङ्क्सनको प्यारामिटर नामसँग मेल खान्छ।
  * `"direction": "in"` - यो इनपुट बाइन्डिङ हो, Event Hub बाट डेटा फङ्क्सनमा आउँछ।
  * `"connection": ""` - यो जडान स्ट्रिङ पढ्न सेटिङको नाम परिभाषित गर्दछ। स्थानीय रूपमा चलाउँदा, यो सेटिङ `local.settings.json` फाइलबाट पढ्नेछ।

    > 💁 जडान स्ट्रिङ `function.json` फाइलमा भण्डारण गर्न सकिँदैन, यसलाई सेटिङबाट पढ्नुपर्छ। यो तपाईंले आफ्नो जडान स्ट्रिङ अनायासै सार्वजनिक गर्नबाट रोक्नको लागि हो।

1. Azure Functions टेम्प्लेटमा [एक बग](https://github.com/Azure/azure-functions-templates/issues/1250) को कारण, `function.json` मा `cardinality` फिल्डको मान गलत छ। यसलाई `many` बाट `one` मा अपडेट गर्नुहोस्:

    ```json
    "cardinality": "one",
    ```

1. `function.json` फाइलमा `"connection"` को मानलाई `local.settings.json` फाइलमा थपिएको नयाँ मानमा पोइन्ट गर्न अपडेट गर्नुहोस्:

    ```json
    "connection": "IOT_HUB_CONNECTION_STRING",
    ```

    > 💁 याद गर्नुहोस् - यसले सेटिङमा पोइन्ट गर्नुपर्छ, वास्तविक जडान स्ट्रिङ समावेश गर्नुपर्दैन।

1. जडान स्ट्रिङमा `eventHubName` मान समावेश छ, त्यसैले `function.json` फाइलमा यसको मान खाली स्ट्रिङमा अपडेट गर्न आवश्यक छ:

    ```json
    "eventHubName": "",
    ```

### कार्य - इभेन्ट ट्रिगर चलाउनुहोस्

1. सुनिश्चित गर्नुहोस् कि तपाईं IoT Hub इभेन्ट मोनिटर चलाइरहनुभएको छैन। यदि यो Functions एपसँगै चलिरहेको छ भने, Functions एप जडान गर्न र इभेन्टहरू उपभोग गर्न सक्षम हुनेछैन।

    > 💁 धेरै एप्स IoT Hub endpoints मा विभिन्न *consumer groups* प्रयोग गरेर जडान गर्न सक्छन्। यी अर्को पाठमा समेटिनेछन्।

1. Functions एप चलाउन, VS Code टर्मिनलबाट निम्न कमाण्ड चलाउनुहोस्:

    ```sh
    func start
    ```

    Functions एप सुरु हुनेछ, र `iot-hub-trigger` फङ्क्सन पत्ता लगाउनेछ। यसले IoT Hub मा अघिल्लो दिनमा पठाइएका कुनै पनि इभेन्टहरू प्रक्रिया गर्नेछ।

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

    प्रत्येक फङ्क्सन कल `Executing 'Functions.iot-hub-trigger'`/`Executed 'Functions.iot-hub-trigger'` ब्लकमा घेरिएको हुनेछ, ताकि प्रत्येक फङ्क्सन कलमा कति सन्देशहरू प्रक्रिया गरियो भनेर देख्न सकियोस्।

1. सुनिश्चित गर्नुहोस् कि तपाईंको IoT उपकरण चलिरहेको छ। तपाईं Functions एपमा नयाँ माटोको चिस्यान सन्देशहरू देख्नुहुनेछ।

1. Functions एप बन्द गरेर पुनः सुरु गर्नुहोस्। तपाईं देख्नुहुनेछ कि यसले अघिल्लो सन्देशहरू पुनः प्रक्रिया गर्नेछैन, केवल नयाँ सन्देशहरू प्रक्रिया गर्नेछ।

> 💁 VS Code ले तपाईंको Functions को डिबगिङलाई पनि समर्थन गर्दछ। तपाईं प्रत्येक लाइनको सुरुवातमा क्लिक गरेर, वा कोडको लाइनमा कर्सर राखेर *Run -> Toggle breakpoint* चयन गरेर, वा `F9` थिचेर ब्रेक पोइन्ट सेट गर्न सक्नुहुन्छ। तपाईं *Run -> Start debugging* चयन गरेर, `F5` थिचेर, वा *Run and debug* प्यान चयन गरेर र **Start debugging** बटन चयन गरेर डिबगर सुरु गर्न सक्नुहुन्छ। यसले तपाईंलाई प्रक्रिया गरिएका इभेन्टहरूको विवरण हेर्न अनुमति दिन्छ।

#### समस्या समाधान

* यदि तपाईंलाई निम्न त्रुटि प्राप्त हुन्छ:

    ```output
    The listener for function 'Functions.iot-hub-trigger' was unable to start. Microsoft.WindowsAzure.Storage: Connection refused. System.Net.Http: Connection refused. System.Private.CoreLib: Connection refused.
    ```

    सुनिश्चित गर्नुहोस् कि Azurite चलिरहेको छ र तपाईंले `local.settings.json` फाइलमा `AzureWebJobsStorage` लाई `UseDevelopmentStorage=true` सेट गर्नुभएको छ।

* यदि तपाईंलाई निम्न त्रुटि प्राप्त हुन्छ:

    ```output
    System.Private.CoreLib: Exception while executing function: Functions.iot-hub-trigger. System.Private.CoreLib: Result: Failure Exception: AttributeError: 'list' object has no attribute 'get_body'
    ```

    सुनिश्चित गर्नुहोस् कि तपाईंले `function.json` फाइलमा `cardinality` लाई `one` मा सेट गर्नुभएको छ।

* यदि तपाईंलाई निम्न त्रुटि प्राप्त हुन्छ:

    ```output
    Azure.Messaging.EventHubs: The path to an Event Hub may be specified as part of the connection string or as a separate value, but not both.  Please verify that your connection string does not have the `EntityPath` token if you are passing an explicit Event Hub name. (Parameter 'connectionString').
    ```

    सुनिश्चित गर्नुहोस् कि तपाईंले `function.json` फाइलमा `eventHubName` लाई खाली स्ट्रिङमा सेट गर्नुभएको छ।

## Serverless कोडबाट प्रत्यक्ष विधि अनुरोधहरू पठाउनुहोस्

अहिलेसम्म तपाईंको Functions एपले Event Hub compatible endpoint प्रयोग गरेर IoT Hub बाट सन्देशहरू सुन्दैछ। अब तपाईंले IoT उपकरणमा आदेशहरू पठाउन आवश्यक छ। यो IoT Hub मा *Registry Manager* मार्फत जडान गरेर गरिन्छ। Registry Manager एक उपकरण हो जसले तपाईंलाई IoT Hub मा दर्ता भएका उपकरणहरू हेर्न र ती उपकरणहरूसँग क्लाउडबाट उपकरणमा सन्देशहरू पठाएर, प्रत्यक्ष विधि अनुरोधहरू पठाएर वा उपकरण ट्विन अपडेट गरेर संवाद गर्न अनुमति दिन्छ। तपाईं यसलाई IoT Hub बाट उपकरणहरू दर्ता गर्न, अपडेट गर्न वा मेटाउन पनि प्रयोग गर्न सक्नुहुन्छ।

Registry Manager मा जडान गर्न, तपाईंलाई जडान स्ट्रिङ चाहिन्छ।

### कार्य - Registry Manager जडान स्ट्रिङ प्राप्त गर्नुहोस्

1. जडान स्ट्रिङ प्राप्त गर्न, निम्न कमाण्ड चलाउनुहोस्:

    ```sh
    az iot hub connection-string show --policy-name service \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    `<hub_name>` लाई तपाईंले IoT Hub को लागि प्रयोग गरेको नामले प्रतिस्थापन गर्नुहोस्।

    जडान स्ट्रिङ *ServiceConnect* नीति को लागि `--policy-name service` प्यारामिटर प्रयोग गरेर अनुरोध गरिएको छ। जब तपाईं जडान स्ट्रिङ अनुरोध गर्नुहुन्छ, तपाईंले निर्दिष्ट गर्न सक्नुहुन्छ कि उक्त जडान स्ट्रिङले के अनुमति दिनेछ। ServiceConnect नीतिले तपाईंको कोडलाई IoT उपकरणहरूसँग जडान गर्न र सन्देशहरू पठाउन अनुमति दिन्छ।

    ✅ अनुसन्धान गर्नुहोस्: [IoT Hub अनुमति डकुमेन्टेशन](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-security#iot-hub-permissions?WT.mc_id=academic-17441-jabenn) मा विभिन्न नीतिहरूको बारेमा पढ्नुहोस्।

1. VS Code मा `local.settings.json` फाइल खोल्नुहोस्। `Values` सेक्सन भित्र निम्न थप मान थप्नुहोस्:

    ```json
    "REGISTRY_MANAGER_CONNECTION_STRING": "<connection string>"
    ```

    `<connection string>` लाई अघिल्लो चरणबाट प्राप्त मानले प्रतिस्थापन गर्नुहोस्। यो मान्य JSON बनाउन माथिल्लो लाइन पछि अल्पविराम थप्न आवश्यक हुनेछ।

### कार्य - उपकरणमा प्रत्यक्ष विधि अनुरोध पठाउनुहोस्

1. Registry Manager को लागि SDK Pip प्याकेज मार्फत उपलब्ध छ। `requirements.txt` फाइलमा निम्न लाइन थप्नुहोस् ताकि यस प्याकेजमा निर्भरता थप्न सकियोस्:

    ```sh
    azure-iot-hub
    ```

1. सुनिश्चित गर्नुहोस् कि VS Code टर्मिनलमा भर्चुअल वातावरण सक्रिय छ, र Pip प्याकेजहरू स्थापना गर्न निम्न कमाण्ड चलाउनुहोस्:

    ```sh
    pip install -r requirements.txt
    ```

1. `__init__.py` फाइलमा निम्न इम्पोर्टहरू थप्नुहोस्:

    ```python
    import json
    import os
    from azure.iot.hub import IoTHubRegistryManager
    from azure.iot.hub.models import CloudToDeviceMethod
    ```

    यसले केही प्रणाली पुस्तकालयहरू, साथै Registry Manager सँग अन्तरक्रिया गर्न र प्रत्यक्ष विधि अनुरोधहरू पठाउन पुस्तकालयहरू आयात गर्दछ।

1. `main` विधि भित्रको कोड हटाउनुहोस्, तर विधि आफैं राख्नुहोस्।

1. `main` विधिमा निम्न कोड थप्नुहोस्:

    ```python
    body = json.loads(event.get_body().decode('utf-8'))
    device_id = event.iothub_metadata['connection-device-id']

    logging.info(f'Received message: {body} from {device_id}')
    ```

    यस कोडले इभेन्टको शरीरलाई निकाल्छ जसले IoT उपकरणले पठाएको JSON सन्देश समावेश गर्दछ।

    त्यसपछि यो सन्देशसँग पास गरिएका एनोटेसनहरूबाट उपकरण ID प्राप्त गर्दछ। इभेन्टको शरीरले टेलिमेट्रीको रूपमा पठाइएको सन्देश समावेश गर्दछ, `iothub_metadata` डिक्सनरीले IoT Hub द्वारा सेट गरिएका गुणहरू समावेश गर्दछ जस्तै पठाउने उपकरणको ID र सन्देश पठाइएको समय।

    यो जानकारी लग गरिन्छ। तपाईंले Functions एप स्थानीय रूपमा चलाउँदा यो लगिङ टर्मिनलमा देख्नुहुनेछ।

1. यसको तल निम्न कोड थप्नुहोस्:

    ```python
    soil_moisture = body['soil_moisture']

    if soil_moisture > 450:
        direct_method = CloudToDeviceMethod(method_name='relay_on', payload='{}')
    else:
        direct_method = CloudToDeviceMethod(method_name='relay_off', payload='{}')
    ```

    यस कोडले सन्देशबाट माटोको चिस्यान प्राप्त गर्दछ। त्यसपछि यो माटोको चिस्यान जाँच गर्दछ, र मानको आधारमा `relay_on` वा `relay_off` प्रत्यक्ष विधि अनुरोधको लागि सहायक वर्ग सिर्जना गर्दछ। विधि अनुरोधलाई पेलोड आवश्यक छैन, त्यसैले खाली JSON डकुमेन्ट पठाइन्छ।

1. यसको तल निम्न कोड थप्नुहोस्:

    ```python
    logging.info(f'Sending direct method request for {direct_method.method_name} for device {device_id}')

    registry_manager_connection_string = os.environ['REGISTRY_MANAGER_CONNECTION_STRING']
    registry_manager = IoTHubRegistryManager(registry_manager_connection_string)
    ```
यो कोडले `local.settings.json` फाइलबाट `REGISTRY_MANAGER_CONNECTION_STRING` लोड गर्दछ। यस फाइलका मानहरू वातावरणीय चरहरूका रूपमा उपलब्ध गराइन्छन्, र यीलाई `os.environ` फंक्शन प्रयोग गरेर पढ्न सकिन्छ, जुन सबै वातावरणीय चरहरूको डिक्सनरी फर्काउँछ।

> 💁 जब यो कोड क्लाउडमा डिप्लोय गरिन्छ, `local.settings.json` फाइलका मानहरू *Application Settings* का रूपमा सेट गरिन्छ, र यीलाई वातावरणीय चरहरूबाट पढ्न सकिन्छ।

त्यसपछि कोडले कनेक्शन स्ट्रिङ प्रयोग गरेर Registry Manager हेल्पर क्लासको एउटा उदाहरण सिर्जना गर्दछ।

1. यसपछि तलको कोड थप्नुहोस्:

    ```python
    registry_manager.invoke_device_method(device_id, direct_method)

    logging.info('Direct method request sent!')
    ```

    यो कोडले रजिस्ट्री म्यानेजरलाई टेलिमेट्री पठाउने उपकरणमा डाइरेक्ट मेथड अनुरोध पठाउन भन्छ।

    > 💁 पहिलेका पाठहरूमा तपाईंले MQTT प्रयोग गरेर बनाएको एपको संस्करणहरूमा, रिले नियन्त्रण आदेशहरू सबै उपकरणहरूमा पठाइन्थ्यो। कोडले मान्थ्यो कि तपाईंसँग केवल एउटा उपकरण हुनेछ। यो संस्करणको कोडले मेथड अनुरोधलाई एकल उपकरणमा पठाउँछ, त्यसैले यदि तपाईंसँग धेरै सेटअपहरू छन् भने यो सही उपकरणमा सही डाइरेक्ट मेथड अनुरोध पठाउन काम गर्दछ।

1. Functions एप चलाउनुहोस्, र सुनिश्चित गर्नुहोस् कि तपाईंको IoT उपकरणले डेटा पठाइरहेको छ। तपाईंले सन्देशहरू प्रशोधन भइरहेको र डाइरेक्ट मेथड अनुरोधहरू पठाइएको देख्नुहुनेछ। माटोको नमी सेन्सरलाई माटोभित्र र बाहिर सारेर मानहरू परिवर्तन भएको र रिले अन र अफ भएको देख्नुहोस्।

> 💁 तपाईं यो कोड [code/functions](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud/code/functions) फोल्डरमा पाउन सक्नुहुन्छ।

## आफ्नो सर्वरलेस कोड क्लाउडमा डिप्लोय गर्नुहोस्

तपाईंको कोड अहिले स्थानीय रूपमा काम गरिरहेको छ, त्यसैले अर्को चरण Functions App लाई क्लाउडमा डिप्लोय गर्नु हो।

### कार्य - क्लाउड स्रोतहरू सिर्जना गर्नुहोस्

तपाईंको Functions एपलाई Azure मा Functions App स्रोतमा डिप्लोय गर्न आवश्यक छ, जुन तपाईंले आफ्नो IoT Hub का लागि सिर्जना गरेको Resource Group भित्र हुनेछ। तपाईंलाई Azure मा एक Storage Account पनि आवश्यक छ, जसले तपाईंले स्थानीय रूपमा चलाएको इम्युलेटेड स्टोरेजलाई प्रतिस्थापन गर्नेछ।

1. Storage Account सिर्जना गर्न तलको कमाण्ड चलाउनुहोस्:

    ```sh
    az storage account create --resource-group soil-moisture-sensor \
                              --sku Standard_LRS \
                              --name <storage_name> 
    ```

    `<storage_name>` लाई तपाईंको Storage Account को नामले प्रतिस्थापन गर्नुहोस्। यो नाम विश्वव्यापी रूपमा अद्वितीय हुनुपर्छ किनभने यो Storage Account पहुँच गर्न प्रयोग गरिने URL को भाग बनाउँछ। तपाईंले केवल साना अक्षर र अंकहरू प्रयोग गर्न सक्नुहुन्छ, अन्य कुनै पनि अक्षरहरू प्रयोग गर्न सकिँदैन, र यो 24 अक्षरमा सीमित छ। `sms` जस्तो केही प्रयोग गर्नुहोस् र अन्त्यमा केही अनौठो शब्दहरू वा तपाईंको नाम थप्नुहोस्।

    `--sku Standard_LRS` ले मूल्य निर्धारण स्तर चयन गर्दछ, सबैभन्दा कम लागतको सामान्य उद्देश्य खाता चयन गर्दै। स्टोरेजको कुनै नि:शुल्क स्तर छैन, र तपाईंले प्रयोग गरेकोको लागि तिर्नुहुन्छ। लागतहरू तुलनात्मक रूपमा कम छन्, सबैभन्दा महँगो स्टोरेज प्रति गिगाबाइट प्रति महिना US$0.05 भन्दा कम छ।

    ✅ मूल्य निर्धारणको बारेमा [Azure Storage Account pricing page](https://azure.microsoft.com/pricing/details/storage/?WT.mc_id=academic-17441-jabenn) मा पढ्नुहोस्।

1. Function App सिर्जना गर्न तलको कमाण्ड चलाउनुहोस्:

    ```sh
    az functionapp create --resource-group soil-moisture-sensor \
                          --runtime python \
                          --functions-version 3 \
                          --os-type Linux \
                          --consumption-plan-location <location> \
                          --storage-account <storage_name> \
                          --name <functions_app_name>
    ```

    `<location>` लाई तपाईंले Resource Group सिर्जना गर्दा प्रयोग गरेको स्थानले प्रतिस्थापन गर्नुहोस्।

    `<storage_name>` लाई तपाईंले पहिले सिर्जना गरेको Storage Account को नामले प्रतिस्थापन गर्नुहोस्।

    `<functions_app_name>` लाई तपाईंको Functions App को लागि अद्वितीय नामले प्रतिस्थापन गर्नुहोस्। यो नाम विश्वव्यापी रूपमा अद्वितीय हुनुपर्छ किनभने यो Functions App पहुँच गर्न प्रयोग गरिने URL को भाग बनाउँछ। `soil-moisture-sensor-` जस्तो केही प्रयोग गर्नुहोस् र अन्त्यमा केही अनौठो शब्दहरू वा तपाईंको नाम थप्नुहोस्।

    `--functions-version 3` विकल्पले Azure Functions को संस्करण सेट गर्दछ। संस्करण 3 नवीनतम संस्करण हो।

    `--os-type Linux` ले Functions रनटाइमलाई यी Functions होस्ट गर्नको लागि Linux प्रयोग गर्न भन्छ। Functions लाई Linux वा Windows मा होस्ट गर्न सकिन्छ, प्रयोग गरिएको प्रोग्रामिङ भाषाको आधारमा। Python एपहरू केवल Linux मा समर्थित छन्।

### कार्य - तपाईंको एप्लिकेशन सेटिङहरू अपलोड गर्नुहोस्

जब तपाईंले आफ्नो Functions App विकास गर्नुभयो, तपाईंले `local.settings.json` फाइलमा IoT Hub का लागि कनेक्शन स्ट्रिङहरूका सेटिङहरू भण्डारण गर्नुभयो। यी सेटिङहरू Azure मा तपाईंको Functions App मा Application Settings मा लेख्न आवश्यक छ ताकि तपाईंको कोडले तिनीहरूलाई प्रयोग गर्न सकून्।

> 🎓 `local.settings.json` फाइल केवल स्थानीय विकास सेटिङहरूको लागि हो, र यीलाई GitHub जस्ता स्रोत कोड नियन्त्रणमा जाँच गर्नु हुँदैन। क्लाउडमा डिप्लोय गर्दा, Application Settings प्रयोग गरिन्छ। Application Settings क्लाउडमा होस्ट गरिएका key/value जोडीहरू हुन्, र वातावरणीय चरहरूबाट पढिन्छन्, चाहे तपाईंको कोडमा होस् वा IoT Hub सँग तपाईंको कोडलाई जडान गर्दा रनटाइमले।

1. Functions App Application Settings मा `IOT_HUB_CONNECTION_STRING` सेटिङ सेट गर्न तलको कमाण्ड चलाउनुहोस्:

    ```sh
    az functionapp config appsettings set --resource-group soil-moisture-sensor \
                                          --name <functions_app_name> \
                                          --settings "IOT_HUB_CONNECTION_STRING=<connection string>"
    ```

    `<functions_app_name>` लाई तपाईंले आफ्नो Functions App को लागि प्रयोग गरेको नामले प्रतिस्थापन गर्नुहोस्।

    `<connection string>` लाई तपाईंको `local.settings.json` फाइलबाट `IOT_HUB_CONNECTION_STRING` को मानले प्रतिस्थापन गर्नुहोस्।

1. माथिको चरण दोहोर्याउनुहोस्, तर `REGISTRY_MANAGER_CONNECTION_STRING` को मानलाई `local.settings.json` फाइलबाट सोही मानले सेट गर्नुहोस्।

जब तपाईं यी कमाण्डहरू चलाउनुहुन्छ, तिनीहरूले Functions App का सबै Application Settings को सूची पनि आउटपुट गर्नेछन्। तपाईं यसलाई तपाईंका मानहरू सही रूपमा सेट गरिएको छ कि छैन भनेर जाँच गर्न प्रयोग गर्न सक्नुहुन्छ।

> 💁 तपाईंले `AzureWebJobsStorage` को लागि पहिले नै सेट गरिएको मान देख्नुहुनेछ। तपाईंको `local.settings.json` फाइलमा, यो स्थानीय स्टोरेज इम्युलेटर प्रयोग गर्न सेट गरिएको थियो। जब तपाईंले Functions App सिर्जना गर्नुभयो, तपाईंले स्टोरेज अकाउन्टलाई एक प्यारामिटरको रूपमा पास गर्नुभयो, र यो सेटिङमा स्वतः सेट गरिन्छ।

### कार्य - तपाईंको Functions App क्लाउडमा डिप्लोय गर्नुहोस्

अब Functions App तयार छ, तपाईंको कोड डिप्लोय गर्न सकिन्छ।

1. VS Code टर्मिनलबाट तलको कमाण्ड चलाएर तपाईंको Functions App प्रकाशित गर्नुहोस्:

    ```sh
    func azure functionapp publish <functions_app_name>
    ```

    `<functions_app_name>` लाई तपाईंले आफ्नो Functions App को लागि प्रयोग गरेको नामले प्रतिस्थापन गर्नुहोस्।

कोडलाई प्याकेज गरिनेछ र Functions App मा पठाइनेछ, जहाँ यो डिप्लोय गरिनेछ र सुरु गरिनेछ। धेरै कन्सोल आउटपुट हुनेछ, जसको अन्त्यमा डिप्लोयको पुष्टि र डिप्लोय गरिएका Functions को सूची हुनेछ। यस अवस्थामा सूचीमा केवल ट्रिगर समावेश हुनेछ।

```output
Deployment successful.
Remote build succeeded!
Syncing triggers...
Functions in soil-moisture-sensor:
    iot-hub-trigger - [eventHubTrigger]
```

तपाईंको IoT उपकरण चलिरहेको छ भनेर सुनिश्चित गर्नुहोस्। माटोको नमी स्तर परिवर्तन गर्न माटोको नमी सेन्सरलाई माटोभित्र र बाहिर सार्नुहोस्। तपाईंले माटोको नमी परिवर्तन हुँदा रिले अन र अफ भएको देख्नुहुनेछ।

---

## 🚀 चुनौती

अघिल्लो पाठमा, तपाईंले रिलेको समय व्यवस्थापन MQTT सन्देशहरूबाट अनसब्स्क्राइब गरेर गर्नुभएको थियो, रिले अन हुँदा र अफ भएको केही समयपछि। तपाईं यहाँ यो विधि प्रयोग गर्न सक्नुहुन्न - तपाईं आफ्नो IoT Hub ट्रिगरलाई अनसब्स्क्राइब गर्न सक्नुहुन्न।

तपाईंको Functions App मा यसलाई व्यवस्थापन गर्न सक्ने विभिन्न तरिकाहरूको बारेमा सोच्नुहोस्।

## पोस्ट-लेक्चर क्विज

[पोस्ट-लेक्चर क्विज](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/18)

## समीक्षा र आत्म अध्ययन

* [Serverless Computing page on Wikipedia](https://wikipedia.org/wiki/Serverless_computing) मा सर्वरलेस कम्प्युटिङको बारेमा पढ्नुहोस्।
* Azure मा सर्वरलेस प्रयोग गर्ने बारेमा पढ्नुहोस्, जसमा केही थप उदाहरणहरू [Go serverless for your IoT needs Azure blog post](https://azure.microsoft.com/blog/go-serverless-for-your-iot-needs/?WT.mc_id=academic-17441-jabenn) मा छन्।
* [Azure Functions YouTube channel](https://www.youtube.com/c/AzureFunctions) मा Azure Functions को बारेमा थप जान्नुहोस्।

## असाइनमेन्ट

[म्यानुअल रिले नियन्त्रण थप्नुहोस्](assignment.md)

---

**अस्वीकरण**:  
यो दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) प्रयोग गरेर अनुवाद गरिएको छ। हामी शुद्धताको लागि प्रयास गर्छौं, तर कृपया ध्यान दिनुहोस् कि स्वचालित अनुवादहरूमा त्रुटि वा अशुद्धता हुन सक्छ। यसको मूल भाषा मा रहेको मूल दस्तावेज़लाई आधिकारिक स्रोत मानिनुपर्छ। महत्वपूर्ण जानकारीको लागि, व्यावसायिक मानव अनुवाद सिफारिस गरिन्छ। यस अनुवादको प्रयोगबाट उत्पन्न हुने कुनै पनि गलतफहमी वा गलत व्याख्याको लागि हामी जिम्मेवार हुने छैनौं।