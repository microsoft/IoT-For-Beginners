<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "b2e0a965723082b068f735aec0faf3f6",
  "translation_date": "2025-08-27T15:04:53+00:00",
  "source_file": "3-transport/lessons/2-store-location-data/assignment.md",
  "language_code": "mr"
}
-->
# फंक्शन बाइंडिंग तपासणे

## सूचना

फंक्शन बाइंडिंग्स तुमच्या कोडला `main` फंक्शनमधून blobs परत करून blob storage मध्ये सेव्ह करण्याची परवानगी देतात. Azure Storage खाते, संग्रह आणि इतर तपशील `function.json` फाइलमध्ये कॉन्फिगर केले जातात.

Azure किंवा इतर Microsoft तंत्रज्ञानासोबत काम करताना, माहितीचा सर्वोत्तम स्रोत [Microsoft च्या दस्तऐवज docs.com वर](https://docs.microsoft.com/?WT.mc_id=academic-17441-jabenn) आहे. या असाइनमेंटमध्ये तुम्हाला Azure Functions बाइंडिंग दस्तऐवज वाचून आउटपुट बाइंडिंग कसे सेट करायचे ते शोधावे लागेल.

सुरुवात करण्यासाठी पाहण्यायोग्य काही पृष्ठे:

* [Azure Functions ट्रिगर्स आणि बाइंडिंग्स संकल्पना](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python)
* [Azure Blob storage बाइंडिंग्ससाठी Azure Functions आढावा](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob?WT.mc_id=academic-17441-jabenn)
* [Azure Blob storage आउटपुट बाइंडिंगसाठी Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob-output?WT.mc_id=academic-17441-jabenn&tabs=python)

## मूल्यांकन निकष

| निकष | उत्कृष्ट | समाधानकारक | सुधारणा आवश्यक |
| -------- | --------- | -------- | ----------------- |
| Blob storage आउटपुट बाइंडिंग कॉन्फिगर करा | आउटपुट बाइंडिंग कॉन्फिगर करण्यात यशस्वी, blob परत केला आणि तो blob storage मध्ये यशस्वीरित्या सेव्ह केला | आउटपुट बाइंडिंग कॉन्फिगर करण्यात यशस्वी, किंवा blob परत केला पण तो blob storage मध्ये सेव्ह करण्यात अयशस्वी | आउटपुट बाइंडिंग कॉन्फिगर करण्यात अयशस्वी |

---

**अस्वीकरण**:  
हा दस्तऐवज AI भाषांतर सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) चा वापर करून भाषांतरित करण्यात आला आहे. आम्ही अचूकतेसाठी प्रयत्नशील असलो तरी, कृपया लक्षात घ्या की स्वयंचलित भाषांतरांमध्ये त्रुटी किंवा अचूकतेचा अभाव असू शकतो. मूळ भाषेतील मूळ दस्तऐवज हा अधिकृत स्रोत मानला जावा. महत्त्वाच्या माहितीसाठी, व्यावसायिक मानवी भाषांतराची शिफारस केली जाते. या भाषांतराचा वापर केल्यामुळे उद्भवणाऱ्या कोणत्याही गैरसमज किंवा चुकीच्या अर्थासाठी आम्ही जबाबदार राहणार नाही.