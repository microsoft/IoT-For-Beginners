<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "b2e0a965723082b068f735aec0faf3f6",
  "translation_date": "2025-08-25T18:13:10+00:00",
  "source_file": "3-transport/lessons/2-store-location-data/assignment.md",
  "language_code": "hi"
}
-->
# फ़ंक्शन बाइंडिंग की जांच करें

## निर्देश

फ़ंक्शन बाइंडिंग आपके कोड को `main` फ़ंक्शन से blobs को blob स्टोरेज में सेव करने की अनुमति देती है। Azure Storage अकाउंट, संग्रह और अन्य विवरण `function.json` फ़ाइल में कॉन्फ़िगर किए जाते हैं।

Azure या अन्य Microsoft तकनीकों के साथ काम करते समय, जानकारी का सबसे अच्छा स्रोत [Microsoft दस्तावेज़ docs.com पर](https://docs.microsoft.com/?WT.mc_id=academic-17441-jabenn) होता है। इस असाइनमेंट में आपको Azure Functions बाइंडिंग दस्तावेज़ पढ़ने की आवश्यकता होगी ताकि आप आउटपुट बाइंडिंग सेटअप करना सीख सकें।

शुरू करने के लिए कुछ पेज हैं:

* [Azure Functions ट्रिगर्स और बाइंडिंग की अवधारणाएँ](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python)
* [Azure Blob स्टोरेज बाइंडिंग्स के लिए Azure Functions का अवलोकन](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob?WT.mc_id=academic-17441-jabenn)
* [Azure Blob स्टोरेज आउटपुट बाइंडिंग के लिए Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob-output?WT.mc_id=academic-17441-jabenn&tabs=python)

## मूल्यांकन मानदंड

| मानदंड | उत्कृष्ट | पर्याप्त | सुधार की आवश्यकता |
| -------- | --------- | -------- | ----------------- |
| Blob स्टोरेज आउटपुट बाइंडिंग को कॉन्फ़िगर करें | आउटपुट बाइंडिंग को कॉन्फ़िगर करने, blob को रिटर्न करने और उसे blob स्टोरेज में सफलतापूर्वक सेव करने में सक्षम था | आउटपुट बाइंडिंग को कॉन्फ़िगर करने या blob को रिटर्न करने में सक्षम था लेकिन उसे blob स्टोरेज में सफलतापूर्वक सेव करने में असमर्थ था | आउटपुट बाइंडिंग को कॉन्फ़िगर करने में असमर्थ था |

**अस्वीकरण**:  
यह दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) का उपयोग करके अनुवादित किया गया है। जबकि हम सटीकता सुनिश्चित करने का प्रयास करते हैं, कृपया ध्यान दें कि स्वचालित अनुवाद में त्रुटियां या अशुद्धियां हो सकती हैं। मूल भाषा में उपलब्ध मूल दस्तावेज़ को प्रामाणिक स्रोत माना जाना चाहिए। महत्वपूर्ण जानकारी के लिए, पेशेवर मानव अनुवाद की सिफारिश की जाती है। इस अनुवाद के उपयोग से उत्पन्न किसी भी गलतफहमी या गलत व्याख्या के लिए हम उत्तरदायी नहीं हैं।