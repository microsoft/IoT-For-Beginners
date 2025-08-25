<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "606f3af1c78e3741e48ce77c31cea626",
  "translation_date": "2025-08-25T17:47:14+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/pi-text-to-speech.md",
  "language_code": "hi"
}
-->
# टेक्स्ट टू स्पीच - रास्पबेरी पाई

इस पाठ के इस भाग में, आप कोड लिखेंगे जो टेक्स्ट को स्पीच में बदलने के लिए स्पीच सर्विस का उपयोग करता है।

## स्पीच सर्विस का उपयोग करके टेक्स्ट को स्पीच में बदलें

टेक्स्ट को REST API का उपयोग करके स्पीच सर्विस को भेजा जा सकता है ताकि इसे ऑडियो फाइल के रूप में प्राप्त किया जा सके, जिसे आपके IoT डिवाइस पर चलाया जा सकता है। स्पीच का अनुरोध करते समय, आपको उपयोग करने के लिए वॉयस प्रदान करनी होगी क्योंकि स्पीच विभिन्न प्रकार की आवाज़ों का उपयोग करके उत्पन्न की जा सकती है।

प्रत्येक भाषा विभिन्न प्रकार की आवाज़ों का समर्थन करती है, और आप स्पीच सर्विस के खिलाफ REST अनुरोध कर सकते हैं ताकि प्रत्येक भाषा के लिए समर्थित आवाज़ों की सूची प्राप्त की जा सके।

### कार्य - एक वॉयस प्राप्त करें

1. VS Code में `smart-timer` प्रोजेक्ट खोलें।

1. भाषा के लिए आवाज़ों की सूची का अनुरोध करने के लिए `say` फ़ंक्शन के ऊपर निम्नलिखित कोड जोड़ें:

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

    यह कोड एक फ़ंक्शन `get_voice` को परिभाषित करता है जो स्पीच सर्विस का उपयोग करके आवाज़ों की सूची प्राप्त करता है। यह उस भाषा से मेल खाने वाली पहली आवाज़ को ढूंढता है जो उपयोग की जा रही है।

    इसके बाद इस फ़ंक्शन को पहली आवाज़ को स्टोर करने के लिए कॉल किया जाता है, और आवाज़ का नाम कंसोल में प्रिंट किया जाता है। इस आवाज़ को एक बार अनुरोध किया जा सकता है और टेक्स्ट को स्पीच में बदलने के लिए हर कॉल के लिए इसका उपयोग किया जा सकता है।

    > 💁 आप Microsoft Docs पर [Language and voice support documentation](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech) से समर्थित आवाज़ों की पूरी सूची प्राप्त कर सकते हैं। यदि आप किसी विशेष आवाज़ का उपयोग करना चाहते हैं, तो आप इस फ़ंक्शन को हटा सकते हैं और इस दस्तावेज़ से आवाज़ के नाम को हार्ड कोड कर सकते हैं। उदाहरण के लिए:
    >
    > ```python
    > voice = 'hi-IN-SwaraNeural'
    > ```

### कार्य - टेक्स्ट को स्पीच में बदलें

1. इसके नीचे, स्पीच सर्विस से ऑडियो प्रारूप को प्राप्त करने के लिए एक स्थिरांक परिभाषित करें। जब आप ऑडियो का अनुरोध करते हैं, तो आप इसे विभिन्न प्रारूपों में प्राप्त कर सकते हैं।

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'
    ```

    आप किस प्रारूप का उपयोग कर सकते हैं, यह आपके हार्डवेयर पर निर्भर करता है। यदि ऑडियो चलाते समय आपको `Invalid sample rate` त्रुटियां मिलती हैं, तो इसे किसी अन्य मान में बदलें। समर्थित मानों की सूची आप Microsoft Docs पर [Text to speech REST API documentation](https://docs.microsoft.com/azure/cognitive-services/speech-service/rest-text-to-speech?WT.mc_id=academic-17441-jabenn#audio-outputs) में पा सकते हैं। आपको `riff` प्रारूप ऑडियो का उपयोग करना होगा, और प्रयास करने के लिए मान हैं `riff-16khz-16bit-mono-pcm`, `riff-24khz-16bit-mono-pcm` और `riff-48khz-16bit-mono-pcm`।

1. इसके नीचे, एक फ़ंक्शन `get_speech` घोषित करें जो स्पीच सर्विस REST API का उपयोग करके टेक्स्ट को स्पीच में बदल देगा:

    ```python
    def get_speech(text):
    ```

1. `get_speech` फ़ंक्शन में, कॉल करने के लिए URL और पास करने के लिए हेडर्स को परिभाषित करें:

    ```python
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    ```

    यह हेडर्स को एक जनरेटेड एक्सेस टोकन का उपयोग करने के लिए सेट करता है, सामग्री को SSML में सेट करता है और आवश्यक ऑडियो प्रारूप को परिभाषित करता है।

1. इसके नीचे, REST API को भेजने के लिए SSML को परिभाषित करें:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

    यह SSML भाषा और उपयोग करने के लिए आवाज़ को सेट करता है, साथ ही बदलने के लिए टेक्स्ट को भी।

1. अंत में, इस फ़ंक्शन में REST अनुरोध करने और बाइनरी ऑडियो डेटा को वापस करने के लिए कोड जोड़ें:

    ```python
    response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    return io.BytesIO(response.content)
    ```

### कार्य - ऑडियो चलाएं

1. `get_speech` फ़ंक्शन के नीचे, REST API कॉल द्वारा लौटाए गए ऑडियो को चलाने के लिए एक नया फ़ंक्शन परिभाषित करें:

    ```python
    def play_speech(speech):
    ```

1. इस फ़ंक्शन को पास किया गया `speech` REST API द्वारा लौटाया गया बाइनरी ऑडियो डेटा होगा। इसे वेव फाइल के रूप में खोलने और PyAudio का उपयोग करके ऑडियो चलाने के लिए निम्नलिखित कोड का उपयोग करें:

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

    यह कोड PyAudio स्ट्रीम का उपयोग करता है, जैसे ऑडियो कैप्चर करना। यहां अंतर यह है कि स्ट्रीम को आउटपुट स्ट्रीम के रूप में सेट किया गया है, और ऑडियो डेटा से डेटा पढ़ा जाता है और स्ट्रीम में भेजा जाता है।

    स्ट्रीम विवरण जैसे सैंपल रेट को हार्ड कोड करने के बजाय, इसे ऑडियो डेटा से पढ़ा जाता है।

1. `say` फ़ंक्शन की सामग्री को निम्नलिखित में बदलें:

    ```python
    speech = get_speech(text)
    play_speech(speech)
    ```

    यह कोड टेक्स्ट को बाइनरी ऑडियो डेटा के रूप में स्पीच में बदलता है, और ऑडियो चलाता है।

1. ऐप चलाएं, और सुनिश्चित करें कि फ़ंक्शन ऐप भी चल रहा है। कुछ टाइमर सेट करें, और आप सुनेंगे कि आपका टाइमर सेट हो गया है, फिर टाइमर पूरा होने पर एक और स्पीच प्रतिक्रिया सुनाई देगी।

    यदि आपको `Invalid sample rate` त्रुटियां मिलती हैं, तो ऊपर वर्णित अनुसार `playback_format` बदलें।

> 💁 आप इस कोड को [code-spoken-response/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/pi) फ़ोल्डर में पा सकते हैं।

😀 आपका टाइमर प्रोग्राम सफल रहा!

**अस्वीकरण**:  
यह दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) का उपयोग करके अनुवादित किया गया है। जबकि हम सटीकता सुनिश्चित करने का प्रयास करते हैं, कृपया ध्यान दें कि स्वचालित अनुवाद में त्रुटियां या अशुद्धियां हो सकती हैं। मूल भाषा में उपलब्ध मूल दस्तावेज़ को आधिकारिक स्रोत माना जाना चाहिए। महत्वपूर्ण जानकारी के लिए, पेशेवर मानव अनुवाद की सिफारिश की जाती है। इस अनुवाद के उपयोग से उत्पन्न किसी भी गलतफहमी या गलत व्याख्या के लिए हम जिम्मेदार नहीं हैं।