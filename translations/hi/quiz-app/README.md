<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2a459ea9177fb0508ca96068ae1009d2",
  "translation_date": "2025-08-25T18:13:54+00:00",
  "source_file": "quiz-app/README.md",
  "language_code": "hi"
}
-->
# क्विज़

ये क्विज़ IoT फॉर बिगिनर्स पाठ्यक्रम के लिए प्री- और पोस्ट-लेक्चर क्विज़ हैं, जो https://aka.ms/iot-beginners पर उपलब्ध है।

## प्रोजेक्ट सेटअप

```
npm install
```

### विकास के लिए कंपाइल और हॉट-रीलोड करता है

```
npm run serve
```

### प्रोडक्शन के लिए कंपाइल और मिनिफाई करता है

```
npm run build
```

### फाइलों को लिंट और फिक्स करता है

```
npm run lint
```

### कॉन्फ़िगरेशन को कस्टमाइज़ करें

[कॉन्फ़िगरेशन संदर्भ](https://cli.vuejs.org/config/) देखें।

श्रेय: इस क्विज़ ऐप के मूल संस्करण के लिए धन्यवाद: https://github.com/arpan45/simple-quiz-vue

## Azure पर डिप्लॉय करना

यहां एक चरण-दर-चरण गाइड है जो आपको शुरुआत करने में मदद करेगा:

1. GitHub रिपॉजिटरी को फोर्क करें  
सुनिश्चित करें कि आपका स्टैटिक वेब ऐप कोड आपके GitHub रिपॉजिटरी में है। इस रिपॉजिटरी को फोर्क करें।

2. एक Azure स्टैटिक वेब ऐप बनाएं  
- एक [Azure खाता](http://azure.microsoft.com) बनाएं।  
- [Azure पोर्टल](https://portal.azure.com) पर जाएं।  
- "Create a resource" पर क्लिक करें और "Static Web App" खोजें।  
- "Create" पर क्लिक करें।  

3. स्टैटिक वेब ऐप को कॉन्फ़िगर करें  
- **बेसिक्स:**  
  - सब्सक्रिप्शन: अपना Azure सब्सक्रिप्शन चुनें।  
  - रिसोर्स ग्रुप: एक नया रिसोर्स ग्रुप बनाएं या मौजूदा का उपयोग करें।  
  - नाम: अपने स्टैटिक वेब ऐप के लिए एक नाम प्रदान करें।  
  - क्षेत्र: अपने उपयोगकर्ताओं के सबसे नजदीकी क्षेत्र का चयन करें।  

- #### डिप्लॉयमेंट विवरण:  
  - स्रोत: "GitHub" चुनें।  
  - GitHub खाता: Azure को आपके GitHub खाते तक पहुंचने के लिए अधिकृत करें।  
  - संगठन: अपना GitHub संगठन चुनें।  
  - रिपॉजिटरी: वह रिपॉजिटरी चुनें जिसमें आपका स्टैटिक वेब ऐप है।  
  - ब्रांच: वह ब्रांच चुनें जिससे आप डिप्लॉय करना चाहते हैं।  

- #### बिल्ड विवरण:  
  - बिल्ड प्रीसेट्स: वह फ्रेमवर्क चुनें जिससे आपका ऐप बनाया गया है (जैसे React, Angular, Vue, आदि)।  
  - ऐप लोकेशन: वह फोल्डर निर्दिष्ट करें जिसमें आपका ऐप कोड है (जैसे, / यदि यह रूट में है)।  
  - API लोकेशन: यदि आपके पास API है, तो उसका स्थान निर्दिष्ट करें (वैकल्पिक)।  
  - आउटपुट लोकेशन: वह फोल्डर निर्दिष्ट करें जहां बिल्ड आउटपुट उत्पन्न होता है (जैसे, build या dist)।  

4. समीक्षा करें और बनाएं  
अपनी सेटिंग्स की समीक्षा करें और "Create" पर क्लिक करें। Azure आवश्यक संसाधनों को सेट करेगा और आपके रिपॉजिटरी में एक GitHub Actions वर्कफ़्लो बनाएगा।  

5. GitHub Actions वर्कफ़्लो  
Azure स्वचालित रूप से आपके रिपॉजिटरी में एक GitHub Actions वर्कफ़्लो फाइल बनाएगा (.github/workflows/azure-static-web-apps-<name>.yml)। यह वर्कफ़्लो बिल्ड और डिप्लॉयमेंट प्रक्रिया को संभालेगा।  

6. डिप्लॉयमेंट की निगरानी करें  
अपने GitHub रिपॉजिटरी के "Actions" टैब पर जाएं।  
आपको एक वर्कफ़्लो चलते हुए दिखाई देगा। यह वर्कफ़्लो आपके स्टैटिक वेब ऐप को Azure पर बिल्ड और डिप्लॉय करेगा।  
जैसे ही वर्कफ़्लो पूरा होता है, आपका ऐप प्रदान किए गए Azure URL पर लाइव हो जाएगा।  

### उदाहरण वर्कफ़्लो फाइल

यहां GitHub Actions वर्कफ़्लो फाइल का एक उदाहरण दिया गया है:  
name: Azure Static Web Apps CI/CD  
```
on:
  push:
    branches:
      - main
  pull_request:
    types: [opened, synchronize, reopened, closed]
    branches:
      - main

jobs:
  build_and_deploy_job:
    runs-on: ubuntu-latest
    name: Build and Deploy Job
    steps:
      - uses: actions/checkout@v2
      - name: Build And Deploy
        id: builddeploy
        uses: Azure/static-web-apps-deploy@v1
        with:
          azure_static_web_apps_api_token: ${{ secrets.AZURE_STATIC_WEB_APPS_API_TOKEN }}
          repo_token: ${{ secrets.GITHUB_TOKEN }}
          action: "upload"
          app_location: "quiz-app" #App source code path
          api_location: ""API source code path optional
          output_location: "dist" #Built app content directory - optional
```

### अतिरिक्त संसाधन  
- [Azure Static Web Apps डाक्यूमेंटेशन](https://learn.microsoft.com/azure/static-web-apps/getting-started)  
- [GitHub Actions डाक्यूमेंटेशन](https://docs.github.com/actions/use-cases-and-examples/deploying/deploying-to-azure-static-web-app)  

**अस्वीकरण**:  
यह दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) का उपयोग करके अनुवादित किया गया है। जबकि हम सटीकता के लिए प्रयासरत हैं, कृपया ध्यान दें कि स्वचालित अनुवाद में त्रुटियां या अशुद्धियां हो सकती हैं। मूल भाषा में उपलब्ध मूल दस्तावेज़ को प्रामाणिक स्रोत माना जाना चाहिए। महत्वपूर्ण जानकारी के लिए, पेशेवर मानव अनुवाद की सिफारिश की जाती है। इस अनुवाद के उपयोग से उत्पन्न किसी भी गलतफहमी या गलत व्याख्या के लिए हम उत्तरदायी नहीं हैं।