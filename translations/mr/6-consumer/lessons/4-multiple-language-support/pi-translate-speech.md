# भाषणाचे भाषांतर - रास्पबेरी पाय

या धड्याच्या या भागात, तुम्ही भाषांतर सेवा वापरून मजकूराचे भाषांतर करण्यासाठी कोड लिहाल.

## भाषांतर सेवा वापरून मजकूराचे भाषणात रूपांतर करा

स्पीच सेवा REST API थेट भाषांतरांना समर्थन देत नाही, त्याऐवजी तुम्ही स्पीच टू टेक्स्ट सेवेद्वारे तयार केलेल्या मजकूराचे आणि बोलल्या गेलेल्या प्रतिसादाच्या मजकूराचे भाषांतर करण्यासाठी Translator सेवा वापरू शकता. या सेवेसाठी REST API उपलब्ध आहे, ज्याचा वापर तुम्ही मजकूराचे भाषांतर करण्यासाठी करू शकता.

### कार्य - भाषांतर संसाधन वापरून मजकूराचे भाषांतर करा

1. तुमच्या स्मार्ट टाइमरमध्ये 2 भाषा सेट केल्या जातील - LUIS प्रशिक्षणासाठी वापरलेली सर्व्हरची भाषा (हीच भाषा वापरून वापरकर्त्याशी संवाद साधण्यासाठी संदेश तयार केले जातात) आणि वापरकर्त्याने बोललेली भाषा. `language` व्हेरिएबलला वापरकर्त्याने बोलली जाणारी भाषा सेट करा आणि LUIS प्रशिक्षणासाठी वापरलेल्या भाषेसाठी `server_language` नावाचा नवीन व्हेरिएबल जोडा:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    `<user language>` च्या जागी तुम्ही बोलणार असलेल्या भाषेचे स्थानिक नाव ठेवा, उदाहरणार्थ फ्रेंचसाठी `fr-FR`, किंवा कॅन्टोनीजसाठी `zn-HK`.

    `<server language>` च्या जागी LUIS प्रशिक्षणासाठी वापरलेल्या भाषेचे स्थानिक नाव ठेवा.

    समर्थित भाषांची आणि त्यांच्या स्थानिक नावांची यादी [Microsoft Docs वरील भाषा आणि आवाज समर्थन दस्तऐवज](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) येथे मिळू शकते.

    > 💁 जर तुम्हाला अनेक भाषा बोलता येत नसतील, तर [Bing Translate](https://www.bing.com/translator) किंवा [Google Translate](https://translate.google.com) सारख्या सेवांचा वापर करून तुमच्या पसंतीच्या भाषेतून दुसऱ्या भाषेत भाषांतर करू शकता. या सेवा भाषांतरित मजकूराचे ऑडिओ देखील प्ले करू शकतात.
    >
    > उदाहरणार्थ, जर तुम्ही LUIS इंग्रजीत प्रशिक्षण दिले असेल, पण वापरकर्ता भाषा म्हणून फ्रेंच वापरायची असेल, तर "set a 2 minute and 27 second timer" हे वाक्य Bing Translate वापरून इंग्रजीतून फ्रेंचमध्ये भाषांतरित करा, आणि नंतर **Listen translation** बटण वापरून भाषांतर तुमच्या मायक्रोफोनमध्ये बोला.
    >
    > ![Bing Translate वरील Listen translation बटण](../../../../../translated_images/mr/bing-translate.348aa796d6efe2a9.webp)

1. `speech_api_key` च्या खाली Translator API की जोडा:

    ```python
    translator_api_key = '<key>'
    ```

    `<key>` च्या जागी तुमच्या Translator सेवा संसाधनासाठी API की ठेवा.

1. `say` फंक्शनच्या वर, `translate_text` नावाचे फंक्शन परिभाषित करा, जे सर्व्हर भाषेतून वापरकर्ता भाषेत मजकूराचे भाषांतर करेल:

    ```python
    def translate_text(text, from_language, to_language):
    ```

    या फंक्शनमध्ये `from` आणि `to` भाषा पास केल्या जातात - तुमच्या अॅपला भाषण ओळखताना वापरकर्ता भाषेतून सर्व्हर भाषेत रूपांतर करायचे आहे, आणि बोलल्या गेलेल्या प्रतिसादासाठी सर्व्हर भाषेतून वापरकर्ता भाषेत रूपांतर करायचे आहे.

1. या फंक्शनमध्ये REST API कॉलसाठी URL आणि हेडर्स परिभाषित करा:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    या API साठी URL स्थान-विशिष्ट नाही, त्याऐवजी स्थान हेडरमध्ये पास केले जाते. API की थेट वापरली जाते, त्यामुळे स्पीच सेवेसारखे टोकन जारी करणाऱ्या API कडून प्रवेश टोकन मिळवण्याची गरज नाही.

1. याखाली कॉलसाठी पॅरामीटर्स आणि बॉडी परिभाषित करा:

    ```python
    params = {
        'from': from_language,
        'to': to_language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` मध्ये API कॉलसाठी पास होणारे पॅरामीटर्स परिभाषित केले जातात, ज्यामध्ये `from` आणि `to` भाषा पास केल्या जातात. हा कॉल `from` भाषेतील मजकूर `to` भाषेत भाषांतरित करतो.

    `body` मध्ये भाषांतर करण्यासाठीचा मजकूर असतो. हे एक अॅरे आहे, कारण एका कॉलमध्ये अनेक मजकूर ब्लॉक्सचे भाषांतर केले जाऊ शकते.

1. REST API कॉल करा आणि प्रतिसाद मिळवा:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    परत आलेला प्रतिसाद JSON अॅरे स्वरूपात असतो, ज्यामध्ये एक आयटम असतो जो भाषांतरित मजकूर ठेवतो. या आयटममध्ये बॉडीमध्ये पास केलेल्या सर्व आयटम्सच्या भाषांतरांसाठी एक अॅरे असते.

    ```json
    [
        {
            "translations": [
                {
                    "text": "Set a 2 minute 27 second timer.",
                    "to": "en"
                }
            ]
        }
    ]
    ```

1. अॅरेमधील पहिल्या आयटममधील पहिल्या भाषांतरातील `text` प्रॉपर्टी परत करा:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. `while True` लूप अपडेट करा, ज्यामध्ये वापरकर्त्याच्या भाषेतून `convert_speech_to_text` कॉलद्वारे मिळालेल्या मजकूराचे सर्व्हर भाषेत भाषांतर केले जाईल:

    ```python
    if len(text) > 0:
        print('Original:', text)
        text = translate_text(text, language, server_language)
        print('Translated:', text)

        message = Message(json.dumps({ 'speech': text }))
        device_client.send_message(message)
    ```

    हा कोड मूळ आणि भाषांतरित मजकूर कन्सोलवर प्रिंट करतो.

1. `say` फंक्शन अपडेट करा, ज्यामध्ये सर्व्हर भाषेतून वापरकर्ता भाषेत भाषांतरित मजकूर बोलला जाईल:

    ```python
    def say(text):
        print('Original:', text)
        text = translate_text(text, server_language, language)
        print('Translated:', text)
        speech = get_speech(text)
        play_speech(speech)
    ```

    हा कोड मूळ आणि भाषांतरित मजकूर कन्सोलवर प्रिंट करतो.

1. तुमचा कोड चालवा. सुनिश्चित करा की तुमचे फंक्शन अॅप चालू आहे, आणि वापरकर्ता भाषेत टाइमरची विनंती करा, स्वतः ती भाषा बोलून किंवा भाषांतर अॅप वापरून.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py
    Connecting
    Connected
    Using voice fr-FR-DeniseNeural
    Original: Définir une minuterie de 2 minutes et 27 secondes.
    Translated: Set a timer of 2 minutes and 27 seconds.
    Original: 2 minute 27 second timer started.
    Translated: 2 minute 27 seconde minute a commencé.
    Original: Times up on your 2 minute 27 second timer.
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

    > 💁 वेगवेगळ्या भाषांमध्ये काहीतरी सांगण्याच्या पद्धती वेगळ्या असल्यामुळे, तुम्हाला LUIS ला दिलेल्या उदाहरणांपेक्षा थोडे वेगळे भाषांतर मिळू शकते. जर असे झाले, तर LUIS मध्ये अधिक उदाहरणे जोडा, पुन्हा प्रशिक्षण द्या आणि मॉडेल पुन्हा प्रकाशित करा.

> 💁 तुम्हाला हा कोड [code/pi](../../../../../6-consumer/lessons/4-multiple-language-support/code/pi) फोल्डरमध्ये सापडेल.

😀 तुमचा बहुभाषिक टाइमर प्रोग्राम यशस्वी झाला!

---

**अस्वीकरण**:  
हा दस्तऐवज AI भाषांतर सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) वापरून भाषांतरित करण्यात आला आहे. आम्ही अचूकतेसाठी प्रयत्नशील असलो तरी कृपया लक्षात ठेवा की स्वयंचलित भाषांतरांमध्ये त्रुटी किंवा अचूकतेचा अभाव असू शकतो. मूळ भाषेतील दस्तऐवज हा अधिकृत स्रोत मानला जावा. महत्त्वाच्या माहितीसाठी व्यावसायिक मानवी भाषांतराची शिफारस केली जाते. या भाषांतराचा वापर करून निर्माण होणाऱ्या कोणत्याही गैरसमज किंवा चुकीच्या अर्थासाठी आम्ही जबाबदार राहणार नाही.