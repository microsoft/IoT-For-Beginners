<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "af249a24d4fe4f4de4806adbc3bc9d86",
  "translation_date": "2025-08-27T14:22:54+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-speech-to-text.md",
  "language_code": "mr"
}
-->
# भाषण ते मजकूर - रास्पबेरी पाय

या धड्याच्या या भागात, तुम्ही कॅप्चर केलेल्या ऑडिओमधील भाषण मजकूरात रूपांतरित करण्यासाठी भाषण सेवेसाठी कोड लिहाल.

## ऑडिओ भाषण सेवेला पाठवा

ऑडिओ REST API चा वापर करून भाषण सेवेला पाठवता येतो. भाषण सेवा वापरण्यासाठी, प्रथम तुम्हाला प्रवेश टोकनची विनंती करावी लागेल, आणि नंतर त्या टोकनचा वापर REST API साठी करावा लागेल. हे प्रवेश टोकन 10 मिनिटांनंतर कालबाह्य होतात, त्यामुळे तुमच्या कोडने नियमितपणे टोकनची विनंती केली पाहिजे जेणेकरून ते नेहमी अद्ययावत राहतील.

### कार्य - प्रवेश टोकन मिळवा

1. तुमच्या पायवरील `smart-timer` प्रकल्प उघडा.

1. `play_audio` फंक्शन काढून टाका. हे आता गरजेचे नाही कारण तुम्हाला स्मार्ट टाइमरने तुम्ही काय म्हटले ते परत ऐकवायचे नाही.

1. `app.py` फाईलच्या शीर्षस्थानी खालील आयात जोडा:

    ```python
    import requests
    ```

1. `while True` लूपच्या वर खालील कोड जोडा, भाषण सेवेसाठी काही सेटिंग्ज घोषित करण्यासाठी:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'
    ```

    `<key>` ला तुमच्या भाषण सेवा स्त्रोतासाठी API कीने बदला. `<location>` ला तुम्ही भाषण सेवा स्त्रोत तयार करताना वापरलेल्या स्थानाने बदला.

    `<language>` ला तुम्ही ज्या भाषेत बोलणार आहात त्या भाषेच्या स्थानिक नावाने बदला, उदाहरणार्थ इंग्रजीसाठी `en-GB`, किंवा कॅन्टोनीजसाठी `zn-HK`. तुम्ही समर्थित भाषांची आणि त्यांच्या स्थानिक नावांची यादी [Microsoft Docs वरील भाषा आणि आवाज समर्थन दस्तऐवज](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) मध्ये पाहू शकता.

1. याखाली, प्रवेश टोकन मिळवण्यासाठी खालील फंक्शन जोडा:

    ```python
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_api_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    हे टोकन जारी करणाऱ्या एन्डपॉइंटला कॉल करते, API की हेडर म्हणून पास करते. हा कॉल प्रवेश टोकन परत करतो, जे भाषण सेवांना कॉल करण्यासाठी वापरले जाऊ शकते.

1. याखाली, REST API चा वापर करून कॅप्चर केलेल्या ऑडिओमधील भाषण मजकूरात रूपांतरित करण्यासाठी फंक्शन घोषित करा:

    ```python
    def convert_speech_to_text(buffer):
    ```

1. या फंक्शनच्या आत, REST API URL आणि हेडर्स सेट करा:

    ```python
    url = f'https://{location}.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1'

    headers = {
        'Authorization': 'Bearer ' + get_access_token(),
        'Content-Type': f'audio/wav; codecs=audio/pcm; samplerate={rate}',
        'Accept': 'application/json;text/xml'
    }

    params = {
        'language': language
    }
    ```

    हे भाषण सेवा स्त्रोताच्या स्थानाचा वापर करून URL तयार करते. नंतर हेडर्समध्ये `get_access_token` फंक्शनमधून मिळालेल्या प्रवेश टोकनसह ऑडिओ कॅप्चर करण्यासाठी वापरलेला सॅम्पल रेट भरतो. शेवटी, ऑडिओमधील भाषेचा समावेश असलेल्या URL सह काही पॅरामीटर्स परिभाषित करतो.

1. याखाली, REST API कॉल करण्यासाठी आणि मजकूर परत मिळवण्यासाठी खालील कोड जोडा:

    ```python
    response = requests.post(url, headers=headers, params=params, data=buffer)
    response_json = response.json()

    if response_json['RecognitionStatus'] == 'Success':
        return response_json['DisplayText']
    else:
        return ''
    ```

    हे URL कॉल करते आणि प्रतिसादात आलेल्या JSON मूल्याचे डिकोडिंग करते. प्रतिसादातील `RecognitionStatus` मूल्य हे कॉल भाषण मजकूरात यशस्वीरित्या रूपांतरित करू शकले का हे दर्शवते, आणि जर ते `Success` असेल तर मजकूर फंक्शनमधून परत केला जातो, अन्यथा रिकामी स्ट्रिंग परत केली जाते.

1. `while True:` लूपच्या वर, भाषण ते मजकूर सेवेमधून परत आलेल्या मजकूरावर प्रक्रिया करण्यासाठी फंक्शन परिभाषित करा. हे फंक्शन सध्या फक्त मजकूर कन्सोलवर प्रिंट करेल.

    ```python
    def process_text(text):
        print(text)
    ```

1. शेवटी, `while True` लूपमधील `play_audio` कॉल `convert_speech_to_text` फंक्शनने बदला, आणि मजकूर `process_text` फंक्शनला पास करा:

    ```python
    text = convert_speech_to_text(buffer)
    process_text(text)
    ```

1. कोड चालवा. बटण दाबा आणि मायक्रोफोनमध्ये बोला. तुम्ही बोलून झाल्यावर बटण सोडा, आणि ऑडिओ मजकूरात रूपांतरित होईल आणि कन्सोलवर प्रिंट होईल.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Hello world.
    Welcome to IoT for beginners.
    ```

    वेगवेगळ्या प्रकारच्या वाक्यांचा प्रयत्न करा, तसेच ज्या वाक्यांमध्ये शब्दांचे उच्चार सारखे असतात पण अर्थ वेगळे असतात अशा वाक्यांचा प्रयत्न करा. उदाहरणार्थ, जर तुम्ही इंग्रजीत बोलत असाल, तर 'I want to buy two bananas and an apple too' असे म्हणा, आणि ते कसे योग्य to, two आणि too वापरते हे लक्षात घ्या, फक्त आवाजावर आधारित नाही तर शब्दाच्या संदर्भावर आधारित.

> 💁 तुम्हाला हा कोड [code-speech-to-text/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/pi) फोल्डरमध्ये सापडेल.

😀 तुमचा भाषण ते मजकूर प्रोग्राम यशस्वी झाला!

---

**अस्वीकरण**:  
हा दस्तऐवज AI भाषांतर सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) चा वापर करून भाषांतरित करण्यात आला आहे. आम्ही अचूकतेसाठी प्रयत्नशील असलो तरी, कृपया लक्षात घ्या की स्वयंचलित भाषांतरांमध्ये त्रुटी किंवा अचूकतेचा अभाव असू शकतो. मूळ भाषेतील दस्तऐवज हा अधिकृत स्रोत मानला जावा. महत्त्वाच्या माहितीसाठी व्यावसायिक मानवी भाषांतराची शिफारस केली जाते. या भाषांतराचा वापर केल्यामुळे उद्भवणाऱ्या कोणत्याही गैरसमज किंवा चुकीच्या अर्थासाठी आम्ही जबाबदार राहणार नाही.