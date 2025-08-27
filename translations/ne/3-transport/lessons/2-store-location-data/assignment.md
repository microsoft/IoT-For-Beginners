<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "b2e0a965723082b068f735aec0faf3f6",
  "translation_date": "2025-08-27T15:05:03+00:00",
  "source_file": "3-transport/lessons/2-store-location-data/assignment.md",
  "language_code": "ne"
}
-->
# फङ्क्सन बाइन्डिङहरू अनुसन्धान गर्नुहोस्

## निर्देशनहरू

फङ्क्सन बाइन्डिङहरूले तपाईंको कोडलाई `main` फङ्क्सनबाट ब्लबहरू फर्काएर ब्लब स्टोरेजमा सुरक्षित गर्न अनुमति दिन्छ। Azure Storage खाता, संग्रह र अन्य विवरणहरू `function.json` फाइलमा कन्फिगर गरिन्छ।

Azure वा अन्य Microsoft प्रविधिहरूसँग काम गर्दा, जानकारीको सबैभन्दा राम्रो स्रोत [Microsoft को दस्तावेज docs.com मा](https://docs.microsoft.com/?WT.mc_id=academic-17441-jabenn) हो। यस असाइनमेन्टमा तपाईंले Azure Functions बाइन्डिङ दस्तावेज पढ्न आवश्यक छ ताकि आउटपुट बाइन्डिङ सेटअप गर्न सकियोस्।

सुरु गर्न हेर्नुपर्ने केही पृष्ठहरू:

* [Azure Functions ट्रिगर र बाइन्डिङ अवधारणाहरू](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python)
* [Azure Functions को लागि Azure Blob स्टोरेज बाइन्डिङहरूको अवलोकन](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob?WT.mc_id=academic-17441-jabenn)
* [Azure Functions को लागि Azure Blob स्टोरेज आउटपुट बाइन्डिङ](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob-output?WT.mc_id=academic-17441-jabenn&tabs=python)

## मूल्यांकन मापदण्ड

| मापदण्ड | उत्कृष्ट | पर्याप्त | सुधार आवश्यक |
| -------- | --------- | -------- | ----------------- |
| ब्लब स्टोरेज आउटपुट बाइन्डिङ कन्फिगर गर्नुहोस् | आउटपुट बाइन्डिङ कन्फिगर गर्न, ब्लब फर्काउन र ब्लब स्टोरेजमा सफलतापूर्वक सुरक्षित गर्न सक्षम भयो | आउटपुट बाइन्डिङ कन्फिगर गर्न वा ब्लब फर्काउन सक्षम भयो तर ब्लब स्टोरेजमा सफलतापूर्वक सुरक्षित गर्न असमर्थ भयो | आउटपुट बाइन्डिङ कन्फिगर गर्न असमर्थ भयो |

---

**अस्वीकरण**:  
यो दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) प्रयोग गरेर अनुवाद गरिएको छ। हामी शुद्धताको लागि प्रयास गर्छौं, तर कृपया ध्यान दिनुहोस् कि स्वचालित अनुवादमा त्रुटिहरू वा अशुद्धताहरू हुन सक्छ। यसको मूल भाषा मा रहेको मूल दस्तावेज़लाई आधिकारिक स्रोत मानिनुपर्छ। महत्वपूर्ण जानकारीको लागि, व्यावसायिक मानव अनुवाद सिफारिस गरिन्छ। यस अनुवादको प्रयोगबाट उत्पन्न हुने कुनै पनि गलतफहमी वा गलत व्याख्याको लागि हामी जिम्मेवार हुने छैनौं।