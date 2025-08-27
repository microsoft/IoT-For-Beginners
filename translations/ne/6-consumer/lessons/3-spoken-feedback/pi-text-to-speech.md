<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "606f3af1c78e3741e48ce77c31cea626",
  "translation_date": "2025-08-27T13:53:49+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/pi-text-to-speech.md",
  "language_code": "ne"
}
-->
# टेक्स्टलाई आवाजमा रूपान्तरण गर्नुहोस् - रास्पबेरी पाई

यस पाठको यस भागमा, तपाईंले स्पीच सेवा प्रयोग गरेर टेक्स्टलाई आवाजमा रूपान्तरण गर्ने कोड लेख्नुहुनेछ।

## स्पीच सेवा प्रयोग गरेर टेक्स्टलाई आवाजमा रूपान्तरण गर्नुहोस्

तपाईं टेक्स्टलाई स्पीच सेवामा REST API मार्फत पठाउन सक्नुहुन्छ, जसले आवाजलाई अडियो फाइलको रूपमा प्रदान गर्छ, जुन तपाईंको IoT उपकरणमा प्ले गर्न सकिन्छ। स्पीच अनुरोध गर्दा, तपाईंले प्रयोग गर्नुपर्ने आवाज प्रदान गर्नुपर्छ, किनभने विभिन्न प्रकारका आवाजहरू प्रयोग गरेर स्पीच उत्पन्न गर्न सकिन्छ।

प्रत्येक भाषाले विभिन्न आवाजहरूको दायरा समर्थन गर्दछ, र तपाईं स्पीच सेवामा REST अनुरोध गरेर प्रत्येक भाषाका लागि समर्थित आवाजहरूको सूची प्राप्त गर्न सक्नुहुन्छ।

### कार्य - आवाज प्राप्त गर्नुहोस्

1. VS Code मा `smart-timer` प्रोजेक्ट खोल्नुहोस्।

1. भाषाको लागि आवाजहरूको सूची अनुरोध गर्न `say` फङ्क्सनको माथि निम्न कोड थप्नुहोस्:

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

    यो कोडले `get_voice` नामक फङ्क्सन परिभाषित गर्छ, जसले स्पीच सेवाको प्रयोग गरेर आवाजहरूको सूची प्राप्त गर्छ। त्यसपछि यो फङ्क्सनले प्रयोग भइरहेको भाषासँग मेल खाने पहिलो आवाज फेला पार्छ।

    यो फङ्क्सनलाई पहिलो आवाज भण्डारण गर्न बोलाइन्छ, र आवाजको नाम कन्सोलमा प्रिन्ट गरिन्छ। यो आवाज एकपटक अनुरोध गर्न सकिन्छ, र टेक्स्टलाई आवाजमा रूपान्तरण गर्न प्रत्येक कलको लागि यसको मान प्रयोग गर्न सकिन्छ।

    > 💁 तपाईं समर्थित आवाजहरूको पूर्ण सूची [Microsoft Docs मा भाषा र आवाज समर्थन दस्तावेज](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech) बाट प्राप्त गर्न सक्नुहुन्छ। यदि तपाईं विशेष आवाज प्रयोग गर्न चाहनुहुन्छ भने, तपाईं यो फङ्क्सन हटाएर दस्तावेजबाट आवाजको नाम हार्ड कोड गर्न सक्नुहुन्छ। उदाहरणका लागि:
    >
    > ```python
    > voice = 'hi-IN-SwaraNeural'
    > ```

### कार्य - टेक्स्टलाई आवाजमा रूपान्तरण गर्नुहोस्

1. यसको तल, स्पीच सेवाबाट प्राप्त गर्नुपर्ने अडियो फर्म्याटको लागि एक स्थिरांक परिभाषित गर्नुहोस्। अडियो अनुरोध गर्दा, तपाईं विभिन्न फर्म्याटहरूमा गर्न सक्नुहुन्छ।

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'
    ```

    तपाईंले प्रयोग गर्न सक्ने फर्म्याट तपाईंको हार्डवेयरमा निर्भर गर्दछ। यदि अडियो प्ले गर्दा तपाईंलाई `Invalid sample rate` त्रुटिहरू प्राप्त हुन्छ भने यसलाई अर्को मानमा परिवर्तन गर्नुहोस्। समर्थित मानहरूको सूची [Text to speech REST API documentation on Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/rest-text-to-speech?WT.mc_id=academic-17441-jabenn#audio-outputs) मा फेला पार्न सकिन्छ। तपाईंले `riff` फर्म्याट अडियो प्रयोग गर्नुपर्नेछ, र प्रयास गर्नुपर्ने मानहरू `riff-16khz-16bit-mono-pcm`, `riff-24khz-16bit-mono-pcm` र `riff-48khz-16bit-mono-pcm` हुन्।

1. यसको तल, `get_speech` नामक फङ्क्सन घोषणा गर्नुहोस्, जसले स्पीच सेवा REST API प्रयोग गरेर टेक्स्टलाई आवाजमा रूपान्तरण गर्नेछ:

    ```python
    def get_speech(text):
    ```

1. `get_speech` फङ्क्सनमा, कल गर्नुपर्ने URL र पास गर्नुपर्ने हेडरहरू परिभाषित गर्नुहोस्:

    ```python
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    ```

    यसले हेडरहरू सेट गर्छ, जसले उत्पन्न गरिएको एक्सेस टोकन प्रयोग गर्छ, सामग्रीलाई SSML मा सेट गर्छ, र आवश्यक अडियो फर्म्याट परिभाषित गर्छ।

1. यसको तल, REST API मा पठाउनुपर्ने SSML परिभाषित गर्नुहोस्:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

    यो SSML ले प्रयोग गर्नुपर्ने भाषा र आवाज सेट गर्छ, साथै रूपान्तरण गर्नुपर्ने टेक्स्ट पनि।

1. अन्ततः, यस फङ्क्सनमा REST अनुरोध गर्न र बाइनरी अडियो डेटा फर्काउन कोड थप्नुहोस्:

    ```python
    response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    return io.BytesIO(response.content)
    ```

### कार्य - अडियो प्ले गर्नुहोस्

1. `get_speech` फङ्क्सनको तल, REST API कलबाट फर्काइएको अडियो प्ले गर्न नयाँ फङ्क्सन परिभाषित गर्नुहोस्:

    ```python
    def play_speech(speech):
    ```

1. यस फङ्क्सनमा पास गरिएको `speech` REST API बाट फर्काइएको बाइनरी अडियो डेटा हुनेछ। यसलाई वेभ फाइलको रूपमा खोल्न र PyAudio मार्फत अडियो प्ले गर्न निम्न कोड प्रयोग गर्नुहोस्:

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

    यो कोडले PyAudio स्ट्रिम प्रयोग गर्छ, जसले अडियो क्याप्चर गर्ने जस्तै काम गर्छ। यहाँ फरक के छ भने स्ट्रिमलाई आउटपुट स्ट्रिमको रूपमा सेट गरिएको छ, र अडियो डेटा बाट पढेर स्ट्रिममा पठाइन्छ।

    स्ट्रिम विवरणहरू जस्तै स्याम्पल रेट हार्ड कोड गर्ने सट्टा, यो अडियो डेटा बाट पढिन्छ।

1. `say` फङ्क्सनको सामग्रीलाई निम्नमा परिवर्तन गर्नुहोस्:

    ```python
    speech = get_speech(text)
    play_speech(speech)
    ```

    यो कोडले टेक्स्टलाई बाइनरी अडियो डेटा रूपमा रूपान्तरण गर्छ, र अडियो प्ले गर्छ।

1. एप चलाउनुहोस्, र सुनिश्चित गर्नुहोस् कि फङ्क्सन एप पनि चलिरहेको छ। केही टाइमर सेट गर्नुहोस्, र तपाईंले सुन्नुहुनेछ कि तपाईंको टाइमर सेट भएको छ भन्ने बोलेको प्रतिक्रिया, त्यसपछि टाइमर पूरा हुँदा अर्को बोलेको प्रतिक्रिया।

    यदि तपाईंलाई `Invalid sample rate` त्रुटिहरू प्राप्त हुन्छ भने, माथि वर्णन गरिएको अनुसार `playback_format` परिवर्तन गर्नुहोस्।

> 💁 तपाईं यो कोड [code-spoken-response/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/pi) फोल्डरमा फेला पार्न सक्नुहुन्छ।

😀 तपाईंको टाइमर प्रोग्राम सफल भयो!

---

**अस्वीकरण**:  
यो दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) प्रयोग गरेर अनुवाद गरिएको छ। हामी शुद्धताको लागि प्रयास गर्छौं, तर कृपया ध्यान दिनुहोस् कि स्वचालित अनुवादमा त्रुटिहरू वा अशुद्धताहरू हुन सक्छ। यसको मूल भाषा मा रहेको मूल दस्तावेज़लाई आधिकारिक स्रोत मानिनुपर्छ। महत्वपूर्ण जानकारीको लागि, व्यावसायिक मानव अनुवाद सिफारिस गरिन्छ। यस अनुवादको प्रयोगबाट उत्पन्न हुने कुनै पनि गलतफहमी वा गलत व्याख्याको लागि हामी जिम्मेवार हुने छैनौं।