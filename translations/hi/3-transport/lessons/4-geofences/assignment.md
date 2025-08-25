<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5cb65a6ec4387ed177e145347e8e308e",
  "translation_date": "2025-08-25T18:02:09+00:00",
  "source_file": "3-transport/lessons/4-geofences/assignment.md",
  "language_code": "hi"
}
-->
# Twilio का उपयोग करके सूचनाएं भेजें

## निर्देश

अब तक आपके कोड में आपने केवल जियोफेंस की दूरी को लॉग किया है। इस असाइनमेंट में आपको एक सूचना जोड़नी होगी, चाहे वह टेक्स्ट संदेश हो या ईमेल, जब GPS निर्देशांक जियोफेंस के अंदर हों।

Azure Functions में कई विकल्प हैं, जिनमें तृतीय-पक्ष सेवाएं जैसे Twilio, एक संचार प्लेटफ़ॉर्म, शामिल हैं।

* [Twilio.com](https://www.twilio.com) पर एक मुफ्त खाता बनाएं।
* [Microsoft docs Twilio binding for Azure Functions page](https://docs.microsoft.com/azure/azure-functions/functions-bindings-twilio?WT.mc_id=academic-17441-jabenn&tabs=python) पर Twilio SMS को Azure Functions से जोड़ने के बारे में दस्तावेज़ पढ़ें।
* [Microsoft docs Azure Functions SendGrid bindings page](https://docs.microsoft.com/azure/azure-functions/functions-bindings-sendgrid?WT.mc_id=academic-17441-jabenn&tabs=python) पर Twilio SendGrid को ईमेल भेजने के लिए Azure Functions से जोड़ने के बारे में दस्तावेज़ पढ़ें।
* अपने Functions ऐप में बाइंडिंग जोड़ें ताकि GPS निर्देशांक जियोफेंस के अंदर या बाहर होने पर सूचित किया जा सके - दोनों पर नहीं।

## मूल्यांकन मानदंड

| मानदंड | उत्कृष्ट | पर्याप्त | सुधार की आवश्यकता |
| -------- | --------- | -------- | ----------------- |
| Functions बाइंडिंग को कॉन्फ़िगर करना और ईमेल या SMS प्राप्त करना | Functions बाइंडिंग को कॉन्फ़िगर करने और जियोफेंस के अंदर या बाहर होने पर ईमेल या SMS प्राप्त करने में सक्षम था, लेकिन दोनों पर नहीं | बाइंडिंग को कॉन्फ़िगर करने में सक्षम था लेकिन ईमेल या SMS भेजने में असमर्थ था, या केवल तब भेजने में सक्षम था जब निर्देशांक दोनों अंदर और बाहर थे | बाइंडिंग को कॉन्फ़िगर करने और ईमेल या SMS भेजने में असमर्थ था |

**अस्वीकरण**:  
यह दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) का उपयोग करके अनुवादित किया गया है। जबकि हम सटीकता सुनिश्चित करने का प्रयास करते हैं, कृपया ध्यान दें कि स्वचालित अनुवाद में त्रुटियां या अशुद्धियां हो सकती हैं। मूल भाषा में उपलब्ध मूल दस्तावेज़ को प्रामाणिक स्रोत माना जाना चाहिए। महत्वपूर्ण जानकारी के लिए, पेशेवर मानव अनुवाद की सिफारिश की जाती है। इस अनुवाद के उपयोग से उत्पन्न किसी भी गलतफहमी या गलत व्याख्या के लिए हम उत्तरदायी नहीं हैं।