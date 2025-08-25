<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7966848a1f870e4c42edb4db67b13c57",
  "translation_date": "2025-08-25T17:49:36+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/virtual-device-text-to-speech.md",
  "language_code": "hi"
}
-->
# टेक्स्ट से स्पीच - वर्चुअल IoT डिवाइस

इस पाठ के इस भाग में, आप टेक्स्ट को स्पीच में बदलने के लिए स्पीच सर्विस का उपयोग करके कोड लिखेंगे।

## टेक्स्ट को स्पीच में बदलें

स्पीच सर्विस SDK, जिसे आपने पिछले पाठ में स्पीच को टेक्स्ट में बदलने के लिए उपयोग किया था, टेक्स्ट को वापस स्पीच में बदलने के लिए भी उपयोग किया जा सकता है। जब आप स्पीच का अनुरोध करते हैं, तो आपको उपयोग करने के लिए वॉयस प्रदान करनी होती है क्योंकि स्पीच विभिन्न प्रकार की आवाज़ों का उपयोग करके उत्पन्न की जा सकती है।

प्रत्येक भाषा कई अलग-अलग आवाज़ों का समर्थन करती है, और आप स्पीच सर्विस SDK से प्रत्येक भाषा के लिए समर्थित आवाज़ों की सूची प्राप्त कर सकते हैं।

### कार्य - टेक्स्ट को स्पीच में बदलें

1. VS Code में `smart-timer` प्रोजेक्ट खोलें और सुनिश्चित करें कि टर्मिनल में वर्चुअल एनवायरनमेंट लोड हो गया है।

1. `azure.cognitiveservices.speech` पैकेज से `SpeechSynthesizer` को मौजूदा इम्पोर्ट्स में जोड़कर इम्पोर्ट करें:

    ```python
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer, SpeechSynthesizer
    ```

1. `say` फंक्शन के ऊपर, स्पीच सिंथेसाइज़र के साथ उपयोग करने के लिए एक स्पीच कॉन्फ़िगरेशन बनाएं:

    ```python
    speech_config = SpeechConfig(subscription=speech_api_key,
                                 region=location)
    speech_config.speech_synthesis_language = language
    speech_synthesizer = SpeechSynthesizer(speech_config=speech_config)
    ```

    यह वही API कुंजी, स्थान और भाषा का उपयोग करता है जो पहले पहचानकर्ता द्वारा उपयोग किया गया था।

1. इसके नीचे, एक वॉयस प्राप्त करने और इसे स्पीच कॉन्फ़िग पर सेट करने के लिए निम्न कोड जोड़ें:

    ```python
    voices = speech_synthesizer.get_voices_async().get().voices
    first_voice = next(x for x in voices if x.locale.lower() == language.lower())
    speech_config.speech_synthesis_voice_name = first_voice.short_name
    ```

    यह सभी उपलब्ध आवाज़ों की सूची प्राप्त करता है, फिर उस भाषा से मेल खाने वाली पहली आवाज़ को ढूंढता है जिसका उपयोग किया जा रहा है।

    > 💁 आप Microsoft Docs पर [Language and voice support documentation](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech) से समर्थित आवाज़ों की पूरी सूची प्राप्त कर सकते हैं। यदि आप किसी विशेष आवाज़ का उपयोग करना चाहते हैं, तो आप इस फंक्शन को हटा सकते हैं और इस दस्तावेज़ से वॉयस नाम को हार्ड कोड कर सकते हैं। उदाहरण के लिए:
    >
    > ```python
    > speech_config.speech_synthesis_voice_name = 'hi-IN-SwaraNeural'
    > ```

1. `say` फंक्शन की सामग्री को अपडेट करें ताकि प्रतिक्रिया के लिए SSML उत्पन्न किया जा सके:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{first_voice.short_name}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

1. इसके नीचे, स्पीच रिकग्निशन को रोकें, SSML को बोलें, फिर रिकग्निशन को फिर से शुरू करें:

    ```python
    recognizer.stop_continuous_recognition()
    speech_synthesizer.speak_ssml(ssml)
    recognizer.start_continuous_recognition()
    ```

    जब टेक्स्ट बोला जा रहा हो, तो टाइमर शुरू होने की घोषणा को डिटेक्ट होने से बचाने के लिए रिकग्निशन को रोका जाता है। ऐसा न करने पर यह LUIS को भेजा जा सकता है और संभवतः इसे नए टाइमर सेट करने के अनुरोध के रूप में व्याख्या किया जा सकता है।

    > 💁 आप इसे आज़मा सकते हैं कि रिकग्निशन को रोकने और फिर से शुरू करने वाली लाइनों को कमेंट करके। एक टाइमर सेट करें, और आप देख सकते हैं कि घोषणा एक नया टाइमर सेट करती है, जो एक नई घोषणा का कारण बनती है, जिससे एक नया टाइमर सेट होता है, और यह प्रक्रिया अनंत तक चलती रहती है!

1. ऐप चलाएं और सुनिश्चित करें कि फंक्शन ऐप भी चल रहा है। कुछ टाइमर सेट करें, और आप सुनेंगे कि आपका टाइमर सेट हो गया है, फिर जब टाइमर पूरा हो जाएगा तो एक और बोली गई प्रतिक्रिया सुनाई देगी।

> 💁 आप इस कोड को [code-spoken-response/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/virtual-iot-device) फोल्डर में पा सकते हैं।

😀 आपका टाइमर प्रोग्राम सफल रहा!

**अस्वीकरण**:  
यह दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) का उपयोग करके अनुवादित किया गया है। जबकि हम सटीकता सुनिश्चित करने का प्रयास करते हैं, कृपया ध्यान दें कि स्वचालित अनुवाद में त्रुटियां या अशुद्धियां हो सकती हैं। मूल भाषा में उपलब्ध मूल दस्तावेज़ को आधिकारिक स्रोत माना जाना चाहिए। महत्वपूर्ण जानकारी के लिए, पेशेवर मानव अनुवाद की सिफारिश की जाती है। इस अनुवाद के उपयोग से उत्पन्न किसी भी गलतफहमी या गलत व्याख्या के लिए हम जिम्मेदार नहीं हैं।