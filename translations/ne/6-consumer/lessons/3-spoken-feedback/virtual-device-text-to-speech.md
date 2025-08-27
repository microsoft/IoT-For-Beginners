<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7966848a1f870e4c42edb4db67b13c57",
  "translation_date": "2025-08-27T14:00:03+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/virtual-device-text-to-speech.md",
  "language_code": "ne"
}
-->
# पाठलाई आवाजमा रूपान्तरण - भर्चुअल IoT उपकरण

यस पाठको यस भागमा, तपाईंले पाठलाई आवाजमा रूपान्तरण गर्नको लागि स्पीच सेवा प्रयोग गर्दै कोड लेख्नु हुनेछ।

## पाठलाई आवाजमा रूपान्तरण गर्नुहोस्

पछिल्लो पाठमा तपाईंले स्पीचलाई पाठमा रूपान्तरण गर्न प्रयोग गरेको स्पीच सेवाको SDK लाई पाठलाई पुनः आवाजमा रूपान्तरण गर्न पनि प्रयोग गर्न सकिन्छ। आवाजको अनुरोध गर्दा, तपाईंले प्रयोग गर्न चाहिएको आवाज प्रदान गर्नुपर्छ, किनभने विभिन्न प्रकारका आवाजहरू प्रयोग गरेर आवाज उत्पन्न गर्न सकिन्छ।

प्रत्येक भाषाले विभिन्न प्रकारका आवाजहरूको समर्थन गर्दछ, र तपाईं स्पीच सेवाको SDK बाट प्रत्येक भाषाका लागि समर्थित आवाजहरूको सूची प्राप्त गर्न सक्नुहुन्छ।

### कार्य - पाठलाई आवाजमा रूपान्तरण गर्नुहोस्

1. VS Code मा `smart-timer` प्रोजेक्ट खोल्नुहोस्, र टर्मिनलमा भर्चुअल वातावरण लोड भएको सुनिश्चित गर्नुहोस्।

1. `azure.cognitiveservices.speech` प्याकेजबाट `SpeechSynthesizer` लाई आयात गर्नुहोस् र यसलाई पहिले नै भएका आयातहरूमा थप्नुहोस्:

    ```python
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer, SpeechSynthesizer
    ```

1. `say` फङ्सनको माथि, स्पीच सिंथेसाइजरसँग प्रयोग गर्न स्पीच कन्फिगरेसन बनाउनुहोस्:

    ```python
    speech_config = SpeechConfig(subscription=speech_api_key,
                                 region=location)
    speech_config.speech_synthesis_language = language
    speech_synthesizer = SpeechSynthesizer(speech_config=speech_config)
    ```

    यसले पहिचानकर्ताले प्रयोग गरेको समान API कुञ्जी, स्थान र भाषा प्रयोग गर्दछ।

1. यसको तल, आवाज प्राप्त गर्न र स्पीच कन्फिगमा सेट गर्न निम्न कोड थप्नुहोस्:

    ```python
    voices = speech_synthesizer.get_voices_async().get().voices
    first_voice = next(x for x in voices if x.locale.lower() == language.lower())
    speech_config.speech_synthesis_voice_name = first_voice.short_name
    ```

    यसले उपलब्ध सबै आवाजहरूको सूची प्राप्त गर्दछ, त्यसपछि प्रयोग भइरहेको भाषासँग मेल खाने पहिलो आवाज फेला पार्छ।

    > 💁 तपाईं समर्थित आवाजहरूको पूर्ण सूची [Microsoft Docs मा भाषा र आवाज समर्थनको दस्तावेज](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech) बाट प्राप्त गर्न सक्नुहुन्छ। यदि तपाईं विशेष आवाज प्रयोग गर्न चाहनुहुन्छ भने, तपाईं यस फङ्सनलाई हटाएर यो दस्तावेजबाट आवाजको नामलाई हार्ड कोड गर्न सक्नुहुन्छ। उदाहरणका लागि:
    >
    > ```python
    > speech_config.speech_synthesis_voice_name = 'hi-IN-SwaraNeural'
    > ```

1. `say` फङ्सनको सामग्रीलाई SSML उत्पन्न गर्न अद्यावधिक गर्नुहोस्:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{first_voice.short_name}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

1. यसको तल, स्पीच पहिचान रोक्नुहोस्, SSML बोल्नुहोस्, त्यसपछि पहिचान पुनः सुरु गर्नुहोस्:

    ```python
    recognizer.stop_continuous_recognition()
    speech_synthesizer.speak_ssml(ssml)
    recognizer.start_continuous_recognition()
    ```

    जब पाठ बोलिन्छ, स्पीच पहिचान रोकिएको हुन्छ ताकि टाइमर सुरु भएको घोषणा पहिचान नगरियोस्, LUIS मा पठाइयोस्, र सम्भवतः नयाँ टाइमर सेट गर्न अनुरोधको रूपमा व्याख्या नगरियोस्।

    > 💁 तपाईं यसलाई परीक्षण गर्न सक्नुहुन्छ पहिचान रोक्न र पुनः सुरु गर्नका लागि लाइनहरूलाई कमेन्ट गरेर। एउटा टाइमर सेट गर्नुहोस्, र तपाईंले पाउन सक्नुहुन्छ कि घोषणाले नयाँ टाइमर सेट गर्दछ, जसले नयाँ घोषणा गराउँछ, र यसरी अनन्त चक्र चलिरहन्छ!

1. एप चलाउनुहोस्, र सुनिश्चित गर्नुहोस् कि फङ्सन एप पनि चलिरहेको छ। केही टाइमरहरू सेट गर्नुहोस्, र तपाईंले सुन्नुहुनेछ कि तपाईंको टाइमर सेट भएको छ भन्ने बोलेको प्रतिक्रिया, त्यसपछि टाइमर पूरा भएपछि अर्को बोलेको प्रतिक्रिया।

> 💁 तपाईं यो कोड [code-spoken-response/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/virtual-iot-device) फोल्डरमा पाउन सक्नुहुन्छ।

😀 तपाईंको टाइमर प्रोग्राम सफल भयो!

---

**अस्वीकरण**:  
यो दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) प्रयोग गरी अनुवाद गरिएको हो। हामी यथासम्भव सटीकता सुनिश्चित गर्न प्रयास गर्छौं, तर कृपया ध्यान दिनुहोस् कि स्वचालित अनुवादहरूमा त्रुटि वा अशुद्धता हुन सक्छ। यसको मूल भाषामा रहेको मूल दस्तावेज़लाई आधिकारिक स्रोत मानिनुपर्छ। महत्त्वपूर्ण जानकारीका लागि, व्यावसायिक मानव अनुवाद सिफारिस गरिन्छ। यस अनुवादको प्रयोगबाट उत्पन्न हुने कुनै पनि गलतफहमी वा गलत व्याख्याका लागि हामी जिम्मेवार हुने छैनौं।