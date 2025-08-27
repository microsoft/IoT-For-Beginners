<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7966848a1f870e4c42edb4db67b13c57",
  "translation_date": "2025-08-27T13:59:47+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/virtual-device-text-to-speech.md",
  "language_code": "mr"
}
-->
# टेक्स्ट टू स्पीच - व्हर्च्युअल IoT डिव्हाइस

या धड्याच्या या भागात, तुम्ही स्पीच सर्व्हिसचा वापर करून टेक्स्टला स्पीचमध्ये रूपांतरित करण्यासाठी कोड लिहाल.

## टेक्स्टला स्पीचमध्ये रूपांतरित करा

तुम्ही मागील धड्यात टेक्स्टमध्ये स्पीच रूपांतरित करण्यासाठी वापरलेले स्पीच सर्व्हिसेस SDK, टेक्स्टला पुन्हा स्पीचमध्ये रूपांतरित करण्यासाठीही वापरले जाऊ शकते. स्पीचची विनंती करताना, तुम्हाला वापरण्यासाठी आवाज प्रदान करावा लागतो, कारण विविध प्रकारच्या आवाजांचा वापर करून स्पीच तयार केले जाऊ शकते.

प्रत्येक भाषेसाठी विविध आवाज उपलब्ध असतात, आणि तुम्ही स्पीच सर्व्हिसेस SDK मधून प्रत्येक भाषेसाठी समर्थित आवाजांची यादी मिळवू शकता.

### कार्य - टेक्स्टला स्पीचमध्ये रूपांतरित करा

1. VS Code मध्ये `smart-timer` प्रकल्प उघडा आणि टर्मिनलमध्ये व्हर्च्युअल एन्व्हायर्नमेंट लोड केले आहे याची खात्री करा.

1. `azure.cognitiveservices.speech` पॅकेजमधून `SpeechSynthesizer` आयात करा आणि ते विद्यमान आयातांमध्ये जोडा:

    ```python
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer, SpeechSynthesizer
    ```

1. `say` फंक्शनच्या वर, स्पीच सिंथेसायझरसाठी वापरण्यासाठी एक स्पीच कॉन्फिगरेशन तयार करा:

    ```python
    speech_config = SpeechConfig(subscription=speech_api_key,
                                 region=location)
    speech_config.speech_synthesis_language = language
    speech_synthesizer = SpeechSynthesizer(speech_config=speech_config)
    ```

    हे त्याच API की, लोकेशन आणि भाषेचा वापर करते जे recognizer ने वापरले होते.

1. याखाली, आवाज मिळवण्यासाठी आणि तो स्पीच कॉन्फिगरेशनवर सेट करण्यासाठी खालील कोड जोडा:

    ```python
    voices = speech_synthesizer.get_voices_async().get().voices
    first_voice = next(x for x in voices if x.locale.lower() == language.lower())
    speech_config.speech_synthesis_voice_name = first_voice.short_name
    ```

    हे सर्व उपलब्ध आवाजांची यादी मिळवते, नंतर वापरल्या जाणाऱ्या भाषेशी जुळणारा पहिला आवाज शोधते.

    > 💁 तुम्ही Microsoft Docs वरील [भाषा आणि आवाज समर्थन दस्तऐवज](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech) मधून समर्थित आवाजांची संपूर्ण यादी मिळवू शकता. जर तुम्हाला विशिष्ट आवाज वापरायचा असेल, तर तुम्ही ही फंक्शन काढून टाकू शकता आणि या दस्तऐवजातील आवाजाचे नाव हार्ड कोड करू शकता. उदाहरणार्थ:
    >
    > ```python
    > speech_config.speech_synthesis_voice_name = 'hi-IN-SwaraNeural'
    > ```

1. `say` फंक्शनच्या सामग्रीला SSML तयार करण्यासाठी अपडेट करा:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{first_voice.short_name}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

1. याखाली, स्पीच रेकग्निशन थांबवा, SSML वाचा, आणि नंतर पुन्हा रेकग्निशन सुरू करा:

    ```python
    recognizer.stop_continuous_recognition()
    speech_synthesizer.speak_ssml(ssml)
    recognizer.start_continuous_recognition()
    ```

    टेक्स्ट बोलले जात असताना रेकग्निशन थांबवले जाते, जेणेकरून टाइमर सुरू झाल्याची घोषणा ओळखली जाणार नाही, LUIS कडे पाठवली जाणार नाही आणि कदाचित नवीन टाइमर सेट करण्याची विनंती म्हणून व्याख्या केली जाणार नाही.

    > 💁 तुम्ही हे तपासण्यासाठी रेकग्निशन थांबवण्याच्या आणि पुन्हा सुरू करण्याच्या ओळींवर टिप्पणी करून पाहू शकता. एक टाइमर सेट करा, आणि तुम्हाला कदाचित असे आढळेल की घोषणा नवीन टाइमर सेट करते, ज्यामुळे नवीन घोषणा होते, आणि त्यामुळे नवीन टाइमर सेट होतो, आणि हे चक्र सतत चालू राहते!

1. अॅप चालवा, आणि फंक्शन अॅप देखील चालू असल्याची खात्री करा. काही टाइमर सेट करा, आणि तुम्हाला तुमचा टाइमर सेट झाल्याचे सांगणारा आवाज ऐकू येईल, आणि नंतर टाइमर पूर्ण झाल्यावर आणखी एक आवाज ऐकू येईल.

> 💁 तुम्हाला हा कोड [code-spoken-response/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/virtual-iot-device) फोल्डरमध्ये सापडेल.

😀 तुमचा टाइमर प्रोग्राम यशस्वी झाला!

---

**अस्वीकरण**:  
हा दस्तऐवज AI भाषांतर सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) वापरून भाषांतरित करण्यात आला आहे. आम्ही अचूकतेसाठी प्रयत्नशील असलो तरी कृपया लक्षात ठेवा की स्वयंचलित भाषांतरांमध्ये त्रुटी किंवा अचूकतेचा अभाव असू शकतो. मूळ भाषेतील दस्तऐवज हा अधिकृत स्रोत मानला जावा. महत्त्वाच्या माहितीसाठी व्यावसायिक मानवी भाषांतराची शिफारस केली जाते. या भाषांतराचा वापर करून उद्भवलेल्या कोणत्याही गैरसमज किंवा चुकीच्या अर्थासाठी आम्ही जबाबदार राहणार नाही.