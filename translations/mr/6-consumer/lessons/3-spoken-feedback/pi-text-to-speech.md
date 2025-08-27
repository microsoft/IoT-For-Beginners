<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "606f3af1c78e3741e48ce77c31cea626",
  "translation_date": "2025-08-27T13:53:26+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/pi-text-to-speech.md",
  "language_code": "mr"
}
-->
# टेक्स्ट टू स्पीच - रास्पबेरी पाय

या धड्याच्या या भागात, तुम्ही स्पीच सर्व्हिस वापरून टेक्स्टला स्पीचमध्ये रूपांतरित करण्यासाठी कोड लिहाल.

## स्पीच सर्व्हिस वापरून टेक्स्टला स्पीचमध्ये रूपांतरित करा

टेक्स्ट स्पीच सर्व्हिसकडे REST API च्या माध्यमातून पाठवले जाऊ शकते, ज्यामुळे ऑडिओ फाईल स्वरूपात स्पीच मिळते आणि ती तुमच्या IoT डिव्हाइसवर प्ले केली जाऊ शकते. स्पीचची विनंती करताना, तुम्हाला वापरण्यासाठी व्हॉइस प्रदान करणे आवश्यक आहे, कारण विविध प्रकारच्या आवाजांचा वापर करून स्पीच तयार केली जाऊ शकते.

प्रत्येक भाषेसाठी विविध आवाज उपलब्ध आहेत, आणि तुम्ही स्पीच सर्व्हिसकडे REST विनंती करून प्रत्येक भाषेसाठी समर्थित आवाजांची यादी मिळवू शकता.

### टास्क - आवाज मिळवा

1. VS Code मध्ये `smart-timer` प्रोजेक्ट उघडा.

1. भाषेसाठी आवाजांची यादी मिळवण्यासाठी `say` फंक्शनच्या वर खालील कोड जोडा:

    ```python
    def get_voice():
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/voices/list'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token()
        }
    
        response = requests.get(url, headers=headers)
        voices_json = json.loads(response.text)
    
        first_voice = next(x for x in voices_json if x['Locale'].lower() == language.lower() and x['VoiceType'] == 'Neural')
        return first_voice['ShortName']
    
    voice = get_voice()
    print(f'Using voice {voice}')
    ```

    हा कोड `get_voice` नावाची फंक्शन परिभाषित करतो, जी स्पीच सर्व्हिसचा वापर करून आवाजांची यादी मिळवते. त्यानंतर ती वापरल्या जाणाऱ्या भाषेशी जुळणारा पहिला आवाज शोधते.

    ही फंक्शन कॉल केली जाते आणि पहिला आवाज स्टोअर केला जातो, तसेच आवाजाचे नाव कन्सोलवर प्रिंट केले जाते. हा आवाज एकदाच विनंती करून प्रत्येक टेक्स्ट टू स्पीच कॉलसाठी वापरला जाऊ शकतो.

    > 💁 तुम्ही [Microsoft Docs वरील भाषा आणि आवाज समर्थन दस्तऐवज](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech) वरून समर्थित आवाजांची संपूर्ण यादी मिळवू शकता. जर तुम्हाला विशिष्ट आवाज वापरायचा असेल, तर तुम्ही ही फंक्शन काढून टाकू शकता आणि या दस्तऐवजातील आवाजाचे नाव हार्ड कोड करू शकता. उदाहरणार्थ:
    >
    > ```python
    > voice = 'hi-IN-SwaraNeural'
    > ```

### टास्क - टेक्स्टला स्पीचमध्ये रूपांतरित करा

1. याखाली, स्पीच सर्व्हिसेसकडून ऑडिओ फॉरमॅट परिभाषित करण्यासाठी एक कॉन्स्टंट डिफाइन करा. ऑडिओची विनंती करताना, तुम्ही विविध फॉरमॅट्समध्ये करू शकता.

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'
    ```

    तुम्ही कोणता फॉरमॅट वापरू शकता हे तुमच्या हार्डवेअरवर अवलंबून आहे. जर तुम्हाला ऑडिओ प्ले करताना `Invalid sample rate` त्रुटी मिळाल्या, तर हे दुसऱ्या मूल्यावर बदला. तुम्ही समर्थित मूल्यांची यादी [Text to speech REST API documentation on Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/rest-text-to-speech?WT.mc_id=academic-17441-jabenn#audio-outputs) वर पाहू शकता. तुम्हाला `riff` फॉरमॅट ऑडिओ वापरावा लागेल, आणि प्रयत्न करण्यासाठी मूल्ये आहेत `riff-16khz-16bit-mono-pcm`, `riff-24khz-16bit-mono-pcm` आणि `riff-48khz-16bit-mono-pcm`.

1. याखाली, `get_speech` नावाची फंक्शन डिक्लेअर करा, जी स्पीच सर्व्हिस REST API वापरून टेक्स्टला स्पीचमध्ये रूपांतरित करेल:

    ```python
    def get_speech(text):
    ```

1. `get_speech` फंक्शनमध्ये, कॉल करण्यासाठी URL आणि पास करण्यासाठी हेडर्स परिभाषित करा:

    ```python
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    ```

    हे हेडर्स जनरेट केलेल्या ऍक्सेस टोकनचा वापर करण्यासाठी सेट करते, सामग्री SSML म्हणून सेट करते आणि आवश्यक ऑडिओ फॉरमॅट परिभाषित करते.

1. याखाली, REST API ला पाठवण्यासाठी SSML परिभाषित करा:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

    हे SSML भाषा आणि वापरण्यासाठी आवाज सेट करते, तसेच रूपांतरित करण्यासाठी टेक्स्ट सेट करते.

1. शेवटी, या फंक्शनमध्ये REST विनंती करण्यासाठी आणि बायनरी ऑडिओ डेटा परत करण्यासाठी कोड जोडा:

    ```python
    response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    return io.BytesIO(response.content)
    ```

### टास्क - ऑडिओ प्ले करा

1. `get_speech` फंक्शनच्या खाली, REST API कॉलद्वारे परत आलेला ऑडिओ प्ले करण्यासाठी नवीन फंक्शन परिभाषित करा:

    ```python
    def play_speech(speech):
    ```

1. या फंक्शनला दिलेला `speech` हा REST API कडून परत आलेला बायनरी ऑडिओ डेटा असेल. खालील कोड वापरून हे वेव्ह फाईल म्हणून उघडा आणि PyAudio च्या माध्यमातून ऑडिओ प्ले करा:

    ```python
    def play_speech(speech):
        with wave.open(speech, 'rb') as wave_file:
            stream = audio.open(format=audio.get_format_from_width(wave_file.getsampwidth()),
                                channels=wave_file.getnchannels(),
                                rate=wave_file.getframerate(),
                                output_device_index=speaker_card_number,
                                output=True)

            data = wave_file.readframes(4096)

            while len(data) > 0:
                stream.write(data)
                data = wave_file.readframes(4096)

            stream.stop_stream()
            stream.close()
    ```

    हा कोड PyAudio स्ट्रीम वापरतो, जसे ऑडिओ कॅप्चर करताना वापरले जाते. फरक इतकाच आहे की येथे स्ट्रीम आउटपुट स्ट्रीम म्हणून सेट केला जातो, आणि ऑडिओ डेटामधून डेटा वाचला जातो आणि स्ट्रीमला पुश केला जातो.

    स्ट्रीम तपशील जसे की सॅम्पल रेट हार्ड कोड करण्याऐवजी, तो ऑडिओ डेटामधून वाचला जातो.

1. `say` फंक्शनची सामग्री खालीलप्रमाणे बदला:

    ```python
    speech = get_speech(text)
    play_speech(speech)
    ```

    हा कोड टेक्स्टला बायनरी ऑडिओ डेटामध्ये रूपांतरित करतो आणि ऑडिओ प्ले करतो.

1. अॅप चालवा, आणि फंक्शन अॅप देखील चालू असल्याची खात्री करा. काही टाइमर्स सेट करा, आणि तुम्हाला तुमचा टाइमर सेट झाल्याचे सांगणारा आवाज ऐकू येईल, आणि नंतर टाइमर पूर्ण झाल्यावर आणखी एक आवाज ऐकू येईल.

    जर तुम्हाला `Invalid sample rate` त्रुटी मिळाल्या, तर वरीलप्रमाणे `playback_format` बदला.

> 💁 तुम्ही हा कोड [code-spoken-response/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/pi) फोल्डरमध्ये शोधू शकता.

😀 तुमचा टाइमर प्रोग्राम यशस्वी झाला!

---

**अस्वीकरण**:  
हा दस्तऐवज AI भाषांतर सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) वापरून भाषांतरित करण्यात आला आहे. आम्ही अचूकतेसाठी प्रयत्नशील असलो तरी कृपया लक्षात ठेवा की स्वयंचलित भाषांतरांमध्ये त्रुटी किंवा अचूकतेचा अभाव असू शकतो. मूळ भाषेतील दस्तऐवज हा अधिकृत स्रोत मानला जावा. महत्त्वाच्या माहितीसाठी व्यावसायिक मानवी भाषांतराची शिफारस केली जाते. या भाषांतराचा वापर करून उद्भवलेल्या कोणत्याही गैरसमज किंवा चुकीच्या अर्थासाठी आम्ही जबाबदार राहणार नाही.