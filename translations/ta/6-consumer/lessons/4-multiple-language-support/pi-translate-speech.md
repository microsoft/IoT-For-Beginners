# பேச்சை மொழிபெயர்க்கவும் - ராஸ்பெர்ரி பை

இந்த பாடத்தின் இந்த பகுதியில், மொழிபெயர்ப்பாளர் சேவையைப் பயன்படுத்தி உரையை மொழிபெயர்க்கும் குறியீட்டை நீங்கள் எழுதுவீர்கள்.

## மொழிபெயர்ப்பாளர் சேவையைப் பயன்படுத்தி உரையை பேச்சாக மாற்றவும்

Speech service REST API நேரடி மொழிபெயர்ப்புகளை ஆதரிக்காது, அதற்கு பதிலாக, Speech to Text சேவையால் உருவாக்கப்பட்ட உரையையும், பேசப்பட்ட பதிலின் உரையையும் மொழிபெயர்க்க Translator சேவையை நீங்கள் பயன்படுத்தலாம். இந்த சேவைக்கு நீங்கள் உரையை மொழிபெயர்க்க REST API ஐ பயன்படுத்தலாம்.

### பணிகள் - உரையை மொழிபெயர்க்க Translator resource ஐ பயன்படுத்தவும்

1. உங்கள் ஸ்மார்ட் டைமரில் 2 மொழிகள் அமைக்கப்படும் - LUIS ஐ பயிற்சி செய்ய பயன்படுத்தப்பட்ட சர்வரின் மொழி (அதே மொழி பயனருடன் பேசுவதற்கான செய்திகளை உருவாக்கவும் பயன்படுத்தப்படுகிறது), மற்றும் பயனர் பேசும் மொழி. `language` மாறியை பயனர் பேசும் மொழியாக மாற்றவும், மேலும் LUIS ஐ பயிற்சி செய்ய பயன்படுத்தப்பட்ட மொழிக்கான புதிய மாறியை `server_language` என சேர்க்கவும்:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

   `<user language>` ஐ நீங்கள் பேசும் மொழிக்கான லொகேல் பெயருடன் மாற்றவும், உதாரணமாக பிரெஞ்சுக்கான `fr-FR`, அல்லது கான்டோனீஸுக்கான `zn-HK`.

   `<server language>` ஐ LUIS ஐ பயிற்சி செய்ய பயன்படுத்தப்பட்ட மொழிக்கான லொகேல் பெயருடன் மாற்றவும்.

   ஆதரிக்கப்படும் மொழிகள் மற்றும் அவற்றின் லொகேல் பெயர்களின் பட்டியலை [Microsoft docs இல் உள்ள மொழி மற்றும் குரல் ஆதரவு ஆவணத்தில்](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) காணலாம்.

   > 💁 நீங்கள் பல மொழிகளைப் பேச முடியாவிட்டால், உங்கள் விருப்பமான மொழியிலிருந்து மற்றொரு மொழிக்கு மொழிபெயர்க்க [Bing Translate](https://www.bing.com/translator) அல்லது [Google Translate](https://translate.google.com) போன்ற சேவையைப் பயன்படுத்தலாம். இந்த சேவைகள் பின்னர் மொழிபெயர்க்கப்பட்ட உரையின் ஆடியோவை இயக்க முடியும்.
   >
   > உதாரணமாக, நீங்கள் LUIS ஐ ஆங்கிலத்தில் பயிற்சி செய்தால், ஆனால் பிரெஞ்சை பயனர் மொழியாகப் பயன்படுத்த விரும்பினால், "set a 2 minute and 27 second timer" போன்ற வாக்கியங்களை ஆங்கிலத்திலிருந்து பிரெஞ்சுக்குத் மொழிபெயர்க்க Bing Translate ஐப் பயன்படுத்தலாம், பின்னர் **Listen translation** பொத்தானை பயன்படுத்தி மொழிபெயர்ப்பை உங்கள் மைக்ரோஃபோனில் பேசவும்.
   >
   > ![Bing Translate இல் Listen translation பொத்தான்](../../../../../translated_images/ta/bing-translate.348aa796d6efe2a9.webp)

1. `speech_api_key` க்கு கீழே translator API key ஐ சேர்க்கவும்:

    ```python
    translator_api_key = '<key>'
    ```

   `<key>` ஐ உங்கள் translator service resource க்கான API key உடன் மாற்றவும்.

1. `say` செயல்பாட்டிற்கு மேலே, server language இலிருந்து user language க்கு உரையை மொழிபெயர்க்கும் `translate_text` செயல்பாட்டை வரையறுக்கவும்:

    ```python
    def translate_text(text, from_language, to_language):
    ```

   இந்த செயல்பாட்டிற்கு இருந்து மற்றும் to மொழிகள் அனுப்பப்படுகின்றன - உங்கள் செயலி பேச்சை அடையாளம் காணும்போது user language இலிருந்து server language க்கு மாற்ற வேண்டும், மற்றும் பேசப்பட்ட பதில்களை வழங்கும்போது server language இலிருந்து user language க்கு மாற்ற வேண்டும்.

1. இந்த செயல்பாட்டுக்குள், REST API அழைப்புக்கான URL மற்றும் headers ஐ வரையறுக்கவும்:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

   இந்த API க்கான URL இடம் சார்ந்ததாக இல்லை, அதற்கு பதிலாக இடம் header ஆக அனுப்பப்படுகிறது. API key நேரடியாக பயன்படுத்தப்படுகிறது, எனவே பேச்சு சேவையைப் போல token issuer API இலிருந்து access token ஐப் பெற தேவையில்லை.

1. இதற்குக் கீழே அழைப்புக்கான parameters மற்றும் body ஐ வரையறுக்கவும்:

    ```python
    params = {
        'from': from_language,
        'to': to_language
    }

    body = [{
        'text' : text
    }]
    ```

   `params` API அழைப்புக்கு அனுப்ப வேண்டிய அளவுரைகளை வரையறுக்கிறது, இருந்து மற்றும் to மொழிகளை அனுப்புகிறது. இந்த அழைப்பு `from` மொழியில் உள்ள உரையை `to` மொழிக்கு மொழிபெயர்க்கும்.

   `body` மொழிபெயர்க்க வேண்டிய உரையை கொண்டுள்ளது. இது ஒரு வரிசையாகும், ஏனெனில் ஒரே அழைப்பில் பல உரை தொகுதிகள் மொழிபெயர்க்கப்படலாம்.

1. REST API ஐ அழைக்கவும், மற்றும் பதிலைப் பெறவும்:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

   திரும்ப வரும் பதில் ஒரு JSON வரிசையாகும், இதில் மொழிபெயர்ப்புகளை கொண்ட ஒரு உருப்படி உள்ளது. இந்த உருப்படியில் body இல் அனுப்பப்பட்ட அனைத்து உருப்படிகளின் மொழிபெயர்ப்புகளுக்கான ஒரு வரிசை உள்ளது.

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

1. வரிசையில் முதல் உருப்படியில் இருந்து முதல் மொழிபெயர்ப்பின் `test` பண்பை திருப்பவும்:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. `while True` மடக்குவடிவத்தைப் புதுப்பித்து, user language இலிருந்து server language க்கு `convert_speech_to_text` அழைப்பிலிருந்து உரையை மொழிபெயர்க்கவும்:

    ```python
    if len(text) > 0:
        print('Original:', text)
        text = translate_text(text, language, server_language)
        print('Translated:', text)

        message = Message(json.dumps({ 'speech': text }))
        device_client.send_message(message)
    ```

   இந்த குறியீடு console இல் உரையின் அசல் மற்றும் மொழிபெயர்க்கப்பட்ட பதிப்புகளை அச்சிடுகிறது.

1. `say` செயல்பாட்டை புதுப்பித்து, server language இலிருந்து user language க்கு உரையை மொழிபெயர்க்கவும்:

    ```python
    def say(text):
        print('Original:', text)
        text = translate_text(text, server_language, language)
        print('Translated:', text)
        speech = get_speech(text)
        play_speech(speech)
    ```

   இந்த குறியீடு console இல் உரையின் அசல் மற்றும் மொழிபெயர்க்கப்பட்ட பதிப்புகளை அச்சிடுகிறது.

1. உங்கள் குறியீட்டை இயக்கவும். உங்கள் function app இயங்குகிறதா என்பதை உறுதிசெய்யவும், மற்றும் user language இல் ஒரு டைமரை கோரவும், உங்களே அந்த மொழியில் பேசுவதன் மூலம் அல்லது ஒரு மொழிபெயர்ப்பு செயலியைப் பயன்படுத்துவதன் மூலம்.

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

   > 💁 வெவ்வேறு மொழிகளில் ஏதாவது ஒன்றைச் சொல்லும் விதம் மாறுபடுவதால், நீங்கள் LUIS க்கு கொடுத்த உதாரணங்களுடன் ஒத்துப்போகாத மொழிபெயர்ப்புகளைப் பெறலாம். இது நடந்தால், LUIS க்கு மேலும் உதாரணங்களைச் சேர்க்கவும், மீண்டும் பயிற்சி செய்து மாடலை மீண்டும் வெளியிடவும்.

> 💁 இந்த குறியீட்டை [code/pi](../../../../../6-consumer/lessons/4-multiple-language-support/code/pi) கோப்புறையில் காணலாம்.

😀 உங்கள் பன்மொழி டைமர் திட்டம் வெற்றிகரமாக முடிந்தது!

---

**குறிப்பு**:  
இந்த ஆவணம் [Co-op Translator](https://github.com/Azure/co-op-translator) என்ற AI மொழிபெயர்ப்பு சேவையைப் பயன்படுத்தி மொழிபெயர்க்கப்பட்டுள்ளது. நாங்கள் துல்லியத்திற்காக முயற்சிக்கிறோம், ஆனால் தானியங்கி மொழிபெயர்ப்புகளில் பிழைகள் அல்லது தவறான தகவல்கள் இருக்கக்கூடும் என்பதை தயவுசெய்து கவனத்தில் கொள்ளுங்கள். அதன் தாய்மொழியில் உள்ள மூல ஆவணம் அதிகாரப்பூர்வ ஆதாரமாக கருதப்பட வேண்டும். முக்கியமான தகவல்களுக்கு, தொழில்முறை மனித மொழிபெயர்ப்பு பரிந்துரைக்கப்படுகிறது. இந்த மொழிபெயர்ப்பைப் பயன்படுத்துவதால் ஏற்படும் எந்த தவறான புரிதல்கள் அல்லது தவறான விளக்கங்களுக்கு நாங்கள் பொறுப்பல்ல.