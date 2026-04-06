# ਭਾਸ਼ਾ ਅਨੁਵਾਦ - ਰਾਸਪਬੇਰੀ ਪਾਈ

ਇਸ ਪਾਠ ਦੇ ਇਸ ਹਿੱਸੇ ਵਿੱਚ, ਤੁਸੀਂ ਅਨੁਵਾਦਕ ਸੇਵਾ ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਟੈਕਸਟ ਅਨੁਵਾਦ ਕਰਨ ਲਈ ਕੋਡ ਲਿਖੋਗੇ।

## ਅਨੁਵਾਦਕ ਸੇਵਾ ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਟੈਕਸਟ ਨੂੰ ਭਾਸ਼ਣ ਵਿੱਚ ਬਦਲੋ

ਸਪੀਚ ਸੇਵਾ REST API ਸਿੱਧੇ ਅਨੁਵਾਦਾਂ ਦਾ ਸਮਰਥਨ ਨਹੀਂ ਕਰਦੀ, ਇਸ ਦੀ ਬਜਾਏ ਤੁਸੀਂ ਸਪੀਚ ਤੋਂ ਟੈਕਸਟ ਸੇਵਾ ਦੁਆਰਾ ਜਨਰੇਟ ਕੀਤੇ ਟੈਕਸਟ ਅਤੇ ਬੋਲਣ ਵਾਲੇ ਜਵਾਬ ਦੇ ਟੈਕਸਟ ਨੂੰ ਅਨੁਵਾਦ ਕਰਨ ਲਈ ਅਨੁਵਾਦਕ ਸੇਵਾ ਦੀ ਵਰਤੋਂ ਕਰ ਸਕਦੇ ਹੋ। ਇਸ ਸੇਵਾ ਵਿੱਚ REST API ਹੈ ਜਿਸਦੀ ਵਰਤੋਂ ਤੁਸੀਂ ਟੈਕਸਟ ਅਨੁਵਾਦ ਕਰਨ ਲਈ ਕਰ ਸਕਦੇ ਹੋ।

### ਕੰਮ - ਅਨੁਵਾਦਕ ਸਰੋਤ ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਟੈਕਸਟ ਅਨੁਵਾਦ ਕਰੋ

1. ਤੁਹਾਡੇ ਸਮਾਰਟ ਟਾਈਮਰ ਵਿੱਚ 2 ਭਾਸ਼ਾਵਾਂ ਸੈਟ ਕੀਤੀਆਂ ਜਾਣਗੀਆਂ - ਸਰਵਰ ਦੀ ਭਾਸ਼ਾ ਜਿਸਦਾ LUIS ਨੂੰ ਟ੍ਰੇਨ ਕਰਨ ਲਈ ਵਰਤੋਂ ਕੀਤੀ ਗਈ ਸੀ (ਇਹੀ ਭਾਸ਼ਾ ਯੂਜ਼ਰ ਨਾਲ ਗੱਲ ਕਰਨ ਲਈ ਸੁਨੇਹੇ ਬਣਾਉਣ ਲਈ ਵੀ ਵਰਤੀ ਜਾਂਦੀ ਹੈ), ਅਤੇ ਯੂਜ਼ਰ ਦੁਆਰਾ ਬੋਲੀ ਜਾਣ ਵਾਲੀ ਭਾਸ਼ਾ। `language` ਵੈਰੀਏਬਲ ਨੂੰ ਅਪਡੇਟ ਕਰੋ ਤਾਂ ਜੋ ਇਹ ਯੂਜ਼ਰ ਦੁਆਰਾ ਬੋਲੀ ਜਾਣ ਵਾਲੀ ਭਾਸ਼ਾ ਹੋਵੇ, ਅਤੇ `server_language` ਨਾਮਕ ਇੱਕ ਨਵਾਂ ਵੈਰੀਏਬਲ ਸ਼ਾਮਲ ਕਰੋ ਜੋ LUIS ਨੂੰ ਟ੍ਰੇਨ ਕਰਨ ਲਈ ਵਰਤੀ ਗਈ ਭਾਸ਼ਾ ਹੋਵੇ:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    `<user language>` ਨੂੰ ਉਸ ਭਾਸ਼ਾ ਦੇ ਲੋਕੇਲ ਨਾਮ ਨਾਲ ਬਦਲੋ ਜਿਸ ਵਿੱਚ ਤੁਸੀਂ ਬੋਲ ਰਹੇ ਹੋਵੋਗੇ, ਉਦਾਹਰਨ ਲਈ `fr-FR` ਫਰੈਂਚ ਲਈ, ਜਾਂ `zn-HK` ਕੈਂਟੋਨੀਜ਼ ਲਈ।

    `<server language>` ਨੂੰ LUIS ਨੂੰ ਟ੍ਰੇਨ ਕਰਨ ਲਈ ਵਰਤੀ ਗਈ ਭਾਸ਼ਾ ਦੇ ਲੋਕੇਲ ਨਾਮ ਨਾਲ ਬਦਲੋ।

    ਤੁਸੀਂ Microsoft Docs ਦੇ [Language and voice support documentation](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) ਵਿੱਚ ਸਮਰਥਿਤ ਭਾਸ਼ਾਵਾਂ ਅਤੇ ਉਨ੍ਹਾਂ ਦੇ ਲੋਕੇਲ ਨਾਮਾਂ ਦੀ ਸੂਚੀ ਲੱਭ ਸਕਦੇ ਹੋ।

    > 💁 ਜੇਕਰ ਤੁਸੀਂ ਕਈ ਭਾਸ਼ਾਵਾਂ ਨਹੀਂ ਬੋਲਦੇ, ਤਾਂ ਤੁਸੀਂ [Bing Translate](https://www.bing.com/translator) ਜਾਂ [Google Translate](https://translate.google.com) ਵਰਗੇ ਸੇਵਾਵਾਂ ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਆਪਣੀ ਪਸੰਦੀਦਾ ਭਾਸ਼ਾ ਤੋਂ ਕਿਸੇ ਹੋਰ ਭਾਸ਼ਾ ਵਿੱਚ ਅਨੁਵਾਦ ਕਰ ਸਕਦੇ ਹੋ। ਇਹ ਸੇਵਾਵਾਂ ਅਨੁਵਾਦ ਕੀਤੇ ਟੈਕਸਟ ਦਾ ਆਡੀਓ ਚਲਾਉਣ ਦੀ ਸਮਰਥਾ ਰੱਖਦੀਆਂ ਹਨ।
    >
    > ਉਦਾਹਰਨ ਲਈ, ਜੇਕਰ ਤੁਸੀਂ LUIS ਨੂੰ ਅੰਗਰੇਜ਼ੀ ਵਿੱਚ ਟ੍ਰੇਨ ਕਰਦੇ ਹੋ, ਪਰ ਯੂਜ਼ਰ ਭਾਸ਼ਾ ਵਜੋਂ ਫਰੈਂਚ ਦੀ ਵਰਤੋਂ ਕਰਨਾ ਚਾਹੁੰਦੇ ਹੋ, ਤਾਂ ਤੁਸੀਂ "set a 2 minute and 27 second timer" ਵਰਗੇ ਵਾਕਾਂਸ਼ਾਂ ਨੂੰ Bing Translate ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਅੰਗਰੇਜ਼ੀ ਤੋਂ ਫਰੈਂਚ ਵਿੱਚ ਅਨੁਵਾਦ ਕਰ ਸਕਦੇ ਹੋ, ਫਿਰ **Listen translation** ਬਟਨ ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਅਨੁਵਾਦ ਨੂੰ ਆਪਣੇ ਮਾਈਕਰੋਫੋਨ ਵਿੱਚ ਬੋਲ ਸਕਦੇ ਹੋ।
    >
    > ![Bing Translate 'Listen translation' ਬਟਨ](../../../../../translated_images/pa/bing-translate.348aa796d6efe2a9.webp)

1. `speech_api_key` ਦੇ ਹੇਠਾਂ ਅਨੁਵਾਦਕ API ਕੁੰਜੀ ਸ਼ਾਮਲ ਕਰੋ:

    ```python
    translator_api_key = '<key>'
    ```

    `<key>` ਨੂੰ ਤੁਹਾਡੇ ਅਨੁਵਾਦਕ ਸੇਵਾ ਸਰੋਤ ਲਈ API ਕੁੰਜੀ ਨਾਲ ਬਦਲੋ।

1. `say` ਫੰਕਸ਼ਨ ਤੋਂ ਉੱਪਰ, ਇੱਕ `translate_text` ਫੰਕਸ਼ਨ ਪਰਿਭਾਸ਼ਿਤ ਕਰੋ ਜੋ ਸਰਵਰ ਭਾਸ਼ਾ ਤੋਂ ਯੂਜ਼ਰ ਭਾਸ਼ਾ ਵਿੱਚ ਟੈਕਸਟ ਅਨੁਵਾਦ ਕਰੇਗਾ:

    ```python
    def translate_text(text, from_language, to_language):
    ```

    ਇਸ ਫੰਕਸ਼ਨ ਵਿੱਚ `from` ਅਤੇ `to` ਭਾਸ਼ਾਵਾਂ ਪਾਸ ਕੀਤੀਆਂ ਜਾਂਦੀਆਂ ਹਨ - ਤੁਹਾਡੇ ਐਪ ਨੂੰ ਸਪੀਚ ਪਛਾਣਣ ਸਮੇਂ ਯੂਜ਼ਰ ਭਾਸ਼ਾ ਤੋਂ ਸਰਵਰ ਭਾਸ਼ਾ ਵਿੱਚ ਬਦਲਣਾ ਹੋਵੇਗਾ, ਅਤੇ ਬੋਲਣ ਵਾਲੇ ਫੀਡਬੈਕ ਦੇ ਸਮੇਂ ਸਰਵਰ ਭਾਸ਼ਾ ਤੋਂ ਯੂਜ਼ਰ ਭਾਸ਼ਾ ਵਿੱਚ ਬਦਲਣਾ ਹੋਵੇਗਾ।

1. ਇਸ ਫੰਕਸ਼ਨ ਦੇ ਅੰਦਰ, REST API ਕਾਲ ਲਈ URL ਅਤੇ ਹੈਡਰ ਪਰਿਭਾਸ਼ਿਤ ਕਰੋ:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    ਇਸ API ਲਈ URL ਸਥਾਨ-ਵਿਸ਼ੇਸ਼ ਨਹੀਂ ਹੈ, ਇਸਦੀ ਬਜਾਏ ਸਥਾਨ ਹੈਡਰ ਵਜੋਂ ਪਾਸ ਕੀਤਾ ਜਾਂਦਾ ਹੈ। API ਕੁੰਜੀ ਸਿੱਧੇ ਵਰਤੀ ਜਾਂਦੀ ਹੈ, ਇਸ ਲਈ ਸਪੀਚ ਸੇਵਾ ਦੇ ਵਿਰੁੱਧ ਟੋਕਨ ਜਨਰੇਟਰ API ਤੋਂ ਐਕਸੈਸ ਟੋਕਨ ਪ੍ਰਾਪਤ ਕਰਨ ਦੀ ਜ਼ਰੂਰਤ ਨਹੀਂ ਹੈ।

1. ਇਸ ਦੇ ਹੇਠਾਂ ਕਾਲ ਲਈ ਪੈਰਾਮੀਟਰ ਅਤੇ ਬਾਡੀ ਪਰਿਭਾਸ਼ਿਤ ਕਰੋ:

    ```python
    params = {
        'from': from_language,
        'to': to_language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` API ਕਾਲ ਨੂੰ ਪਾਸ ਕਰਨ ਲਈ ਪੈਰਾਮੀਟਰ ਪਰਿਭਾਸ਼ਿਤ ਕਰਦਾ ਹੈ, `from` ਅਤੇ `to` ਭਾਸ਼ਾਵਾਂ ਪਾਸ ਕਰਦਾ ਹੈ। ਇਹ ਕਾਲ `from` ਭਾਸ਼ਾ ਵਿੱਚ ਟੈਕਸਟ ਨੂੰ `to` ਭਾਸ਼ਾ ਵਿੱਚ ਅਨੁਵਾਦ ਕਰੇਗਾ।

    `body` ਵਿੱਚ ਅਨੁਵਾਦ ਕਰਨ ਲਈ ਟੈਕਸਟ ਹੁੰਦਾ ਹੈ। ਇਹ ਇੱਕ ਐਰੇ ਹੈ, ਕਿਉਂਕਿ ਇੱਕੋ ਕਾਲ ਵਿੱਚ ਕਈ ਟੈਕਸਟ ਬਲਾਕਾਂ ਦਾ ਅਨੁਵਾਦ ਕੀਤਾ ਜਾ ਸਕਦਾ ਹੈ।

1. REST API ਕਾਲ ਕਰੋ, ਅਤੇ ਜਵਾਬ ਪ੍ਰਾਪਤ ਕਰੋ:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    ਵਾਪਸ ਆਉਣ ਵਾਲਾ ਜਵਾਬ ਇੱਕ JSON ਐਰੇ ਹੈ, ਜਿਸ ਵਿੱਚ ਇੱਕ ਆਈਟਮ ਹੁੰਦੀ ਹੈ ਜੋ ਅਨੁਵਾਦਾਂ ਨੂੰ ਸ਼ਾਮਲ ਕਰਦੀ ਹੈ। ਇਸ ਆਈਟਮ ਵਿੱਚ ਸਾਰੇ ਆਈਟਮਾਂ ਦੇ ਅਨੁਵਾਦਾਂ ਲਈ ਇੱਕ ਐਰੇ ਹੁੰਦੀ ਹੈ ਜੋ ਬਾਡੀ ਵਿੱਚ ਪਾਸ ਕੀਤੀਆਂ ਗਈਆਂ ਹਨ।

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

1. ਐਰੇ ਵਿੱਚ ਪਹਿਲੇ ਆਈਟਮ ਤੋਂ ਪਹਿਲੇ ਅਨੁਵਾਦ ਤੋਂ `test` ਪ੍ਰਾਪਰਟੀ ਵਾਪਸ ਕਰੋ:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. `while True` ਲੂਪ ਨੂੰ ਅਪਡੇਟ ਕਰੋ ਤਾਂ ਜੋ `convert_speech_to_text` ਕਾਲ ਤੋਂ ਟੈਕਸਟ ਨੂੰ ਯੂਜ਼ਰ ਭਾਸ਼ਾ ਤੋਂ ਸਰਵਰ ਭਾਸ਼ਾ ਵਿੱਚ ਅਨੁਵਾਦ ਕਰੇ:

    ```python
    if len(text) > 0:
        print('Original:', text)
        text = translate_text(text, language, server_language)
        print('Translated:', text)

        message = Message(json.dumps({ 'speech': text }))
        device_client.send_message(message)
    ```

    ਇਹ ਕੋਡ ਟੈਕਸਟ ਦੇ ਮੂਲ ਅਤੇ ਅਨੁਵਾਦਿਤ ਵਰਜਨ ਨੂੰ ਕੰਸੋਲ ਵਿੱਚ ਪ੍ਰਿੰਟ ਕਰਦਾ ਹੈ।

1. `say` ਫੰਕਸ਼ਨ ਨੂੰ ਅਪਡੇਟ ਕਰੋ ਤਾਂ ਜੋ ਸਰਵਰ ਭਾਸ਼ਾ ਤੋਂ ਯੂਜ਼ਰ ਭਾਸ਼ਾ ਵਿੱਚ ਕਹਿਣ ਵਾਲੇ ਟੈਕਸਟ ਨੂੰ ਅਨੁਵਾਦ ਕਰੇ:

    ```python
    def say(text):
        print('Original:', text)
        text = translate_text(text, server_language, language)
        print('Translated:', text)
        speech = get_speech(text)
        play_speech(speech)
    ```

    ਇਹ ਕੋਡ ਟੈਕਸਟ ਦੇ ਮੂਲ ਅਤੇ ਅਨੁਵਾਦਿਤ ਵਰਜਨ ਨੂੰ ਕੰਸੋਲ ਵਿੱਚ ਪ੍ਰਿੰਟ ਕਰਦਾ ਹੈ।

1. ਆਪਣਾ ਕੋਡ ਚਲਾਓ। ਯਕੀਨੀ ਬਣਾਓ ਕਿ ਤੁਹਾਡਾ ਫੰਕਸ਼ਨ ਐਪ ਚਲ ਰਿਹਾ ਹੈ, ਅਤੇ ਯੂਜ਼ਰ ਭਾਸ਼ਾ ਵਿੱਚ ਟਾਈਮਰ ਦੀ ਬੇਨਤੀ ਕਰੋ, ਚਾਹੇ ਉਹ ਭਾਸ਼ਾ ਤੁਸੀਂ ਖੁਦ ਬੋਲ ਰਹੇ ਹੋ, ਜਾਂ ਅਨੁਵਾਦ ਐਪ ਦੀ ਵਰਤੋਂ ਕਰ ਰਹੇ ਹੋ।

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

    > 💁 ਵੱਖ-ਵੱਖ ਭਾਸ਼ਾਵਾਂ ਵਿੱਚ ਕੁਝ ਕਹਿਣ ਦੇ ਵੱਖ-ਵੱਖ ਤਰੀਕਿਆਂ ਦੇ ਕਾਰਨ, ਤੁਹਾਨੂੰ ਅਨੁਵਾਦਾਂ ਮਿਲ ਸਕਦੇ ਹਨ ਜੋ LUIS ਨੂੰ ਦਿੱਤੇ ਉਦਾਹਰਨਾਂ ਤੋਂ ਥੋੜੇ ਵੱਖਰੇ ਹਨ। ਜੇਕਰ ਇਹ ਹੋਵੇ, ਤਾਂ LUIS ਵਿੱਚ ਹੋਰ ਉਦਾਹਰਨ ਸ਼ਾਮਲ ਕਰੋ, ਮੁੜ ਟ੍ਰੇਨ ਕਰੋ ਅਤੇ ਮਾਡਲ ਨੂੰ ਮੁੜ-ਪ੍ਰਕਾਸ਼ਿਤ ਕਰੋ।

> 💁 ਤੁਸੀਂ ਇਹ ਕੋਡ [code/pi](../../../../../6-consumer/lessons/4-multiple-language-support/code/pi) ਫੋਲਡਰ ਵਿੱਚ ਲੱਭ ਸਕਦੇ ਹੋ।

😀 ਤੁਹਾਡਾ ਬਹੁਭਾਸ਼ੀਕ ਟਾਈਮਰ ਪ੍ਰੋਗਰਾਮ ਸਫਲ ਰਿਹਾ!

---

**ਅਸਵੀਕਾਰਨਾ**:  
ਇਹ ਦਸਤਾਵੇਜ਼ AI ਅਨੁਵਾਦ ਸੇਵਾ [Co-op Translator](https://github.com/Azure/co-op-translator) ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਅਨੁਵਾਦ ਕੀਤਾ ਗਿਆ ਹੈ। ਹਾਲਾਂਕਿ ਅਸੀਂ ਸਹੀਅਤ ਲਈ ਯਤਨਸ਼ੀਲ ਹਾਂ, ਕਿਰਪਾ ਕਰਕੇ ਧਿਆਨ ਦਿਓ ਕਿ ਸਵੈਚਾਲਿਤ ਅਨੁਵਾਦਾਂ ਵਿੱਚ ਗਲਤੀਆਂ ਜਾਂ ਅਸੁਚੀਤਤਾਵਾਂ ਹੋ ਸਕਦੀਆਂ ਹਨ। ਮੂਲ ਦਸਤਾਵੇਜ਼, ਜੋ ਇਸਦੀ ਮੂਲ ਭਾਸ਼ਾ ਵਿੱਚ ਹੈ, ਨੂੰ ਅਧਿਕਾਰਤ ਸਰੋਤ ਮੰਨਿਆ ਜਾਣਾ ਚਾਹੀਦਾ ਹੈ। ਮਹੱਤਵਪੂਰਨ ਜਾਣਕਾਰੀ ਲਈ, ਪੇਸ਼ੇਵਰ ਮਨੁੱਖੀ ਅਨੁਵਾਦ ਦੀ ਸਿਫਾਰਸ਼ ਕੀਤੀ ਜਾਂਦੀ ਹੈ। ਇਸ ਅਨੁਵਾਦ ਦੀ ਵਰਤੋਂ ਤੋਂ ਪੈਦਾ ਹੋਣ ਵਾਲੇ ਕਿਸੇ ਵੀ ਗਲਤਫਹਿਮੀ ਜਾਂ ਗਲਤ ਵਿਆਖਿਆ ਲਈ ਅਸੀਂ ਜ਼ਿੰਮੇਵਾਰ ਨਹੀਂ ਹਾਂ।