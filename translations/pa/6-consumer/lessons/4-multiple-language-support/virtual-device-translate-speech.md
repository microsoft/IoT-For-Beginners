# ਭਾਸ਼ਾ ਅਨੁਵਾਦ - ਵਰਚੁਅਲ IoT ਡਿਵਾਈਸ

ਇਸ ਪਾਠ ਦੇ ਇਸ ਹਿੱਸੇ ਵਿੱਚ, ਤੁਸੀਂ ਕੋਡ ਲਿਖੋਗੇ ਜੋ ਭਾਸ਼ਾ ਸੇਵਾ ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਭਾਸ਼ਣ ਨੂੰ ਟੈਕਸਟ ਵਿੱਚ ਬਦਲਣ ਸਮੇਂ ਅਨੁਵਾਦ ਕਰੇਗਾ, ਫਿਰ ਟੈਕਸਟ ਨੂੰ ਅਨੁਵਾਦਕ ਸੇਵਾ ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਅਨੁਵਾਦ ਕਰੇਗਾ ਅਤੇ ਬੋਲਣ ਵਾਲਾ ਜਵਾਬ ਤਿਆਰ ਕਰੇਗਾ।

## ਭਾਸ਼ਾ ਸੇਵਾ ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਭਾਸ਼ਣ ਦਾ ਅਨੁਵਾਦ ਕਰੋ

ਭਾਸ਼ਾ ਸੇਵਾ ਭਾਸ਼ਣ ਨੂੰ ਸਿਰਫ਼ ਉਸੇ ਭਾਸ਼ਾ ਵਿੱਚ ਟੈਕਸਟ ਵਿੱਚ ਬਦਲਣ ਲਈ ਹੀ ਨਹੀਂ, ਸਗੋਂ ਨਤੀਜੇ ਨੂੰ ਹੋਰ ਭਾਸ਼ਾਵਾਂ ਵਿੱਚ ਅਨੁਵਾਦ ਕਰਨ ਲਈ ਵੀ ਵਰਤੀ ਜਾ ਸਕਦੀ ਹੈ।

### ਕੰਮ - ਭਾਸ਼ਾ ਸੇਵਾ ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਭਾਸ਼ਣ ਦਾ ਅਨੁਵਾਦ ਕਰੋ

1. `smart-timer` ਪ੍ਰੋਜੈਕਟ ਨੂੰ VS Code ਵਿੱਚ ਖੋਲ੍ਹੋ ਅਤੇ ਯਕੀਨੀ ਬਣਾਓ ਕਿ ਵਰਚੁਅਲ ਵਾਤਾਵਰਣ ਟਰਮੀਨਲ ਵਿੱਚ ਲੋਡ ਹੈ।

1. ਮੌਜੂਦਾ ਇਮਪੋਰਟਾਂ ਦੇ ਹੇਠਾਂ ਹੇਠਾਂ ਦਿੱਤੇ ਇਮਪੋਰਟ ਸਟੇਟਮੈਂਟਸ ਸ਼ਾਮਲ ਕਰੋ:

    ```python
    from azure.cognitiveservices import speech
    from azure.cognitiveservices.speech.translation import SpeechTranslationConfig, TranslationRecognizer
    import requests
    ```

    ਇਹ ਕਲਾਸਾਂ ਨੂੰ ਅਨੁਵਾਦ ਕਰਨ ਲਈ ਇਮਪੋਰਟ ਕਰਦਾ ਹੈ, ਅਤੇ ਇੱਕ `requests` ਲਾਇਬ੍ਰੇਰੀ ਜੋ ਇਸ ਪਾਠ ਵਿੱਚ ਬਾਅਦ ਵਿੱਚ ਅਨੁਵਾਦਕ ਸੇਵਾ ਨੂੰ ਕਾਲ ਕਰਨ ਲਈ ਵਰਤੀ ਜਾਵੇਗੀ।

1. ਤੁਹਾਡੇ ਸਮਾਰਟ ਟਾਈਮਰ ਵਿੱਚ 2 ਭਾਸ਼ਾਵਾਂ ਸੈਟ ਕੀਤੀਆਂ ਜਾਣਗੀਆਂ - ਸਰਵਰ ਦੀ ਭਾਸ਼ਾ ਜਿਸਨੂੰ LUIS ਨੂੰ ਟ੍ਰੇਨ ਕਰਨ ਲਈ ਵਰਤਿਆ ਗਿਆ ਸੀ (ਇਹੀ ਭਾਸ਼ਾ ਉਪਭੋਗਤਾ ਨਾਲ ਗੱਲ ਕਰਨ ਲਈ ਸੁਨੇਹੇ ਬਣਾਉਣ ਲਈ ਵੀ ਵਰਤੀ ਜਾਂਦੀ ਹੈ), ਅਤੇ ਉਪਭੋਗਤਾ ਦੁਆਰਾ ਬੋਲੀ ਜਾਣ ਵਾਲੀ ਭਾਸ਼ਾ। `language` ਵੈਰੀਏਬਲ ਨੂੰ ਅਪਡੇਟ ਕਰੋ ਜੋ ਉਪਭੋਗਤਾ ਦੁਆਰਾ ਬੋਲੀ ਜਾਣ ਵਾਲੀ ਭਾਸ਼ਾ ਹੋਵੇਗੀ, ਅਤੇ `server_language` ਨਾਮਕ ਇੱਕ ਨਵਾਂ ਵੈਰੀਏਬਲ ਸ਼ਾਮਲ ਕਰੋ ਜੋ LUIS ਨੂੰ ਟ੍ਰੇਨ ਕਰਨ ਲਈ ਵਰਤੀ ਗਈ ਭਾਸ਼ਾ ਹੋਵੇਗੀ:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    `<user language>` ਨੂੰ ਉਸ ਭਾਸ਼ਾ ਦੇ ਲੋਕੇਲ ਨਾਮ ਨਾਲ ਬਦਲੋ ਜਿਸ ਵਿੱਚ ਤੁਸੀਂ ਬੋਲ ਰਹੇ ਹੋ, ਉਦਾਹਰਨ ਲਈ `fr-FR` ਫਰੈਂਚ ਲਈ, ਜਾਂ `zn-HK` ਕੈਂਟੋਨੀਜ਼ ਲਈ।

    `<server language>` ਨੂੰ LUIS ਨੂੰ ਟ੍ਰੇਨ ਕਰਨ ਲਈ ਵਰਤੀ ਗਈ ਭਾਸ਼ਾ ਦੇ ਲੋਕੇਲ ਨਾਮ ਨਾਲ ਬਦਲੋ।

    ਤੁਸੀਂ Microsoft Docs ਦੇ [Language and voice support documentation](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) ਵਿੱਚ ਸਮਰਥਿਤ ਭਾਸ਼ਾਵਾਂ ਅਤੇ ਉਨ੍ਹਾਂ ਦੇ ਲੋਕੇਲ ਨਾਮਾਂ ਦੀ ਸੂਚੀ ਲੱਭ ਸਕਦੇ ਹੋ।

    > 💁 ਜੇਕਰ ਤੁਸੀਂ ਕਈ ਭਾਸ਼ਾਵਾਂ ਨਹੀਂ ਬੋਲਦੇ, ਤਾਂ ਤੁਸੀਂ [Bing Translate](https://www.bing.com/translator) ਜਾਂ [Google Translate](https://translate.google.com) ਵਰਗੇ ਸੇਵਾਵਾਂ ਦੀ ਵਰਤੋਂ ਕਰ ਸਕਦੇ ਹੋ ਆਪਣੀ ਪਸੰਦੀਦਾ ਭਾਸ਼ਾ ਤੋਂ ਕਿਸੇ ਹੋਰ ਭਾਸ਼ਾ ਵਿੱਚ ਅਨੁਵਾਦ ਕਰਨ ਲਈ। ਇਹ ਸੇਵਾਵਾਂ ਅਨੁਵਾਦ ਕੀਤੇ ਟੈਕਸਟ ਦਾ ਆਡੀਓ ਚਲਾਉਣ ਦੀ ਸਮਰਥਾ ਰੱਖਦੀਆਂ ਹਨ। ਧਿਆਨ ਦਿਓ ਕਿ ਭਾਸ਼ਾ ਪਛਾਣਕਰਤਾ ਤੁਹਾਡੇ ਡਿਵਾਈਸ ਤੋਂ ਕੁਝ ਆਡੀਓ ਆਉਟਪੁੱਟ ਨੂੰ ਅਣਡਿੱਠਾ ਕਰ ਸਕਦਾ ਹੈ, ਇਸ ਲਈ ਤੁਹਾਨੂੰ ਅਨੁਵਾਦ ਕੀਤੇ ਟੈਕਸਟ ਨੂੰ ਚਲਾਉਣ ਲਈ ਇੱਕ ਵਾਧੂ ਡਿਵਾਈਸ ਦੀ ਲੋੜ ਹੋ ਸਕਦੀ ਹੈ।
    >
    > ਉਦਾਹਰਨ ਲਈ, ਜੇ ਤੁਸੀਂ LUIS ਨੂੰ ਅੰਗਰੇਜ਼ੀ ਵਿੱਚ ਟ੍ਰੇਨ ਕਰਦੇ ਹੋ, ਪਰ ਉਪਭੋਗਤਾ ਭਾਸ਼ਾ ਵਜੋਂ ਫਰੈਂਚ ਦੀ ਵਰਤੋਂ ਕਰਨਾ ਚਾਹੁੰਦੇ ਹੋ, ਤਾਂ ਤੁਸੀਂ "set a 2 minute and 27 second timer" ਵਰਗੇ ਵਾਕਾਂਸ਼ਾਂ ਨੂੰ Bing Translate ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਅੰਗਰੇਜ਼ੀ ਤੋਂ ਫਰੈਂਚ ਵਿੱਚ ਅਨੁਵਾਦ ਕਰ ਸਕਦੇ ਹੋ, ਫਿਰ **Listen translation** ਬਟਨ ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਅਨੁਵਾਦ ਨੂੰ ਆਪਣੇ ਮਾਈਕਰੋਫੋਨ ਵਿੱਚ ਬੋਲ ਸਕਦੇ ਹੋ।
    >
    > ![Bing Translate 'Listen translation' ਬਟਨ](../../../../../translated_images/pa/bing-translate.348aa796d6efe2a9.webp)

1. `recognizer_config` ਅਤੇ `recognizer` ਡਿਕਲੇਰੇਸ਼ਨ ਨੂੰ ਹੇਠਾਂ ਦਿੱਤੇ ਨਾਲ ਬਦਲੋ:

    ```python
    translation_config = SpeechTranslationConfig(subscription=speech_api_key,
                                                 region=location,
                                                 speech_recognition_language=language,
                                                 target_languages=(language, server_language))
    
    recognizer = TranslationRecognizer(translation_config=translation_config)
    ```

    ਇਹ ਇੱਕ ਅਨੁਵਾਦ ਕਨਫਿਗ ਬਣਾਉਂਦਾ ਹੈ ਜੋ ਉਪਭੋਗਤਾ ਦੀ ਭਾਸ਼ਾ ਵਿੱਚ ਭਾਸ਼ਣ ਨੂੰ ਪਛਾਣਦਾ ਹੈ, ਅਤੇ ਉਪਭੋਗਤਾ ਅਤੇ ਸਰਵਰ ਭਾਸ਼ਾ ਵਿੱਚ ਅਨੁਵਾਦ ਬਣਾਉਂਦਾ ਹੈ। ਫਿਰ ਇਹ ਇਸ ਕਨਫਿਗ ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਇੱਕ ਅਨੁਵਾਦਕ ਪਛਾਣਕਰਤਾ ਬਣਾਉਂਦਾ ਹੈ - ਇੱਕ ਭਾਸ਼ਾ ਪਛਾਣਕਰਤਾ ਜੋ ਭਾਸ਼ਾ ਪਛਾਣ ਦੇ ਨਤੀਜੇ ਨੂੰ ਕਈ ਭਾਸ਼ਾਵਾਂ ਵਿੱਚ ਅਨੁਵਾਦ ਕਰ ਸਕਦਾ ਹੈ।

    > 💁 ਅਸਲ ਭਾਸ਼ਾ ਨੂੰ `target_languages` ਵਿੱਚ ਦਰਸਾਇਆ ਜਾਣਾ ਜ਼ਰੂਰੀ ਹੈ, ਨਹੀਂ ਤਾਂ ਤੁਹਾਨੂੰ ਕੋਈ ਅਨੁਵਾਦ ਨਹੀਂ ਮਿਲੇਗਾ।

1. `recognized` ਫੰਕਸ਼ਨ ਨੂੰ ਅਪਡੇਟ ਕਰੋ, ਫੰਕਸ਼ਨ ਦੀ ਸਾਰੀ ਸਮੱਗਰੀ ਨੂੰ ਹੇਠਾਂ ਦਿੱਤੇ ਨਾਲ ਬਦਲੋ:

    ```python
    if args.result.reason == speech.ResultReason.TranslatedSpeech:
        language_match = next(l for l in args.result.translations if server_language.lower().startswith(l.lower()))
        text = args.result.translations[language_match]
        if (len(text) > 0):
            print(f'Translated text: {text}')
    
            message = Message(json.dumps({ 'speech': text }))
            device_client.send_message(message)
    ```

    ਇਹ ਕੋਡ ਜਾਂਚਦਾ ਹੈ ਕਿ ਕੀ ਪਛਾਣੀ ਗਈ ਘਟਨਾ ਭਾਸ਼ਾ ਅਨੁਵਾਦ ਹੋਣ ਕਾਰਨ ਚਲਾਈ ਗਈ ਸੀ (ਇਹ ਘਟਨਾ ਹੋਰ ਸਮੇਂ ਵੀ ਚਲਾਈ ਜਾ ਸਕਦੀ ਹੈ, ਜਿਵੇਂ ਕਿ ਜਦੋਂ ਭਾਸ਼ਾ ਪਛਾਣੀ ਜਾਂਦੀ ਹੈ ਪਰ ਅਨੁਵਾਦ ਨਹੀਂ ਹੁੰਦਾ)। ਜੇਕਰ ਭਾਸ਼ਾ ਅਨੁਵਾਦ ਕੀਤੀ ਗਈ ਸੀ, ਤਾਂ ਇਹ `args.result.translations` ਡਿਕਸ਼ਨਰੀ ਵਿੱਚ ਅਨੁਵਾਦ ਲੱਭਦਾ ਹੈ ਜੋ ਸਰਵਰ ਭਾਸ਼ਾ ਨਾਲ ਮੇਲ ਖਾਂਦਾ ਹੈ।

    `args.result.translations` ਡਿਕਸ਼ਨਰੀ ਲੋਕੇਲ ਸੈਟਿੰਗ ਦੇ ਪੂਰੇ ਸੈਟਿੰਗ ਦੇ ਬਦਲੇ ਭਾਸ਼ਾ ਦੇ ਹਿੱਸੇ 'ਤੇ ਅਧਾਰਿਤ ਹੈ। ਉਦਾਹਰਨ ਲਈ, ਜੇਕਰ ਤੁਸੀਂ ਫਰੈਂਚ ਲਈ `fr-FR` ਵਿੱਚ ਅਨੁਵਾਦ ਦੀ ਬੇਨਤੀ ਕਰਦੇ ਹੋ, ਤਾਂ ਡਿਕਸ਼ਨਰੀ ਵਿੱਚ `fr` ਲਈ ਇੱਕ ਐਂਟਰੀ ਹੋਵੇਗੀ, ਨਾ ਕਿ `fr-FR`।

    ਅਨੁਵਾਦ ਕੀਤੇ ਟੈਕਸਟ ਨੂੰ ਫਿਰ IoT Hub ਨੂੰ ਭੇਜਿਆ ਜਾਂਦਾ ਹੈ।

1. ਇਸ ਕੋਡ ਨੂੰ ਚਲਾਓ ਅਤੇ ਅਨੁਵਾਦਾਂ ਦੀ ਜਾਂਚ ਕਰੋ। ਯਕੀਨੀ ਬਣਾਓ ਕਿ ਤੁਹਾਡਾ ਫੰਕਸ਼ਨ ਐਪ ਚਲ ਰਿਹਾ ਹੈ, ਅਤੇ ਉਪਭੋਗਤਾ ਦੀ ਭਾਸ਼ਾ ਵਿੱਚ ਟਾਈਮਰ ਦੀ ਬੇਨਤੀ ਕਰੋ, ਜਾਂ ਤਾਂ ਉਹ ਭਾਸ਼ਾ ਖੁਦ ਬੋਲ ਕੇ, ਜਾਂ ਅਨੁਵਾਦਕ ਐਪ ਦੀ ਵਰਤੋਂ ਕਰਕੇ।

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    ```

## ਅਨੁਵਾਦਕ ਸੇਵਾ ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਟੈਕਸਟ ਦਾ ਅਨੁਵਾਦ ਕਰੋ

ਭਾਸ਼ਾ ਸੇਵਾ ਟੈਕਸਟ ਨੂੰ ਵਾਪਸ ਭਾਸ਼ਣ ਵਿੱਚ ਅਨੁਵਾਦ ਕਰਨ ਦਾ ਸਮਰਥਨ ਨਹੀਂ ਕਰਦੀ, ਇਸਦੇ ਬਦਲੇ ਤੁਸੀਂ ਟੈਕਸਟ ਦਾ ਅਨੁਵਾਦ ਕਰਨ ਲਈ ਅਨੁਵਾਦਕ ਸੇਵਾ ਦੀ ਵਰਤੋਂ ਕਰ ਸਕਦੇ ਹੋ। ਇਸ ਸੇਵਾ ਵਿੱਚ ਇੱਕ REST API ਹੈ ਜਿਸਦੀ ਤੁਸੀਂ ਵਰਤੋਂ ਕਰ ਸਕਦੇ ਹੋ।

### ਕੰਮ - ਅਨੁਵਾਦਕ ਸਰੋਤ ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਟੈਕਸਟ ਦਾ ਅਨੁਵਾਦ ਕਰੋ

1. `speech_api_key` ਦੇ ਹੇਠਾਂ ਅਨੁਵਾਦਕ API ਕੁੰਜੀ ਸ਼ਾਮਲ ਕਰੋ:

    ```python
    translator_api_key = '<key>'
    ```

    `<key>` ਨੂੰ ਤੁਹਾਡੇ ਅਨੁਵਾਦਕ ਸੇਵਾ ਸਰੋਤ ਲਈ API ਕੁੰਜੀ ਨਾਲ ਬਦਲੋ।

1. `say` ਫੰਕਸ਼ਨ ਦੇ ਉੱਪਰ ਇੱਕ `translate_text` ਫੰਕਸ਼ਨ ਡਿਫਾਈਨ ਕਰੋ ਜੋ ਟੈਕਸਟ ਨੂੰ ਸਰਵਰ ਭਾਸ਼ਾ ਤੋਂ ਉਪਭੋਗਤਾ ਭਾਸ਼ਾ ਵਿੱਚ ਅਨੁਵਾਦ ਕਰੇਗਾ:

    ```python
    def translate_text(text):
    ```

1. ਇਸ ਫੰਕਸ਼ਨ ਦੇ ਅੰਦਰ, REST API ਕਾਲ ਲਈ URL ਅਤੇ ਹੈਡਰਜ਼ ਡਿਫਾਈਨ ਕਰੋ:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    ਇਸ API ਲਈ URL ਸਥਾਨ-ਵਿਸ਼ੇਸ਼ ਨਹੀਂ ਹੈ, ਇਸਦੇ ਬਦਲੇ ਸਥਾਨ ਨੂੰ ਹੈਡਰ ਵਜੋਂ ਪਾਸ ਕੀਤਾ ਜਾਂਦਾ ਹੈ। API ਕੁੰਜੀ ਨੂੰ ਸਿੱਧੇ ਹੀ ਵਰਤਿਆ ਜਾਂਦਾ ਹੈ, ਇਸ ਲਈ ਭਾਸ਼ਾ ਸੇਵਾ ਦੇ ਵਾਂਗ ਟੋਕਨ ਜਾਰੀ ਕਰਨ ਵਾਲੇ API ਤੋਂ ਐਕਸੈਸ ਟੋਕਨ ਪ੍ਰਾਪਤ ਕਰਨ ਦੀ ਲੋੜ ਨਹੀਂ ਹੈ।

1. ਇਸ ਦੇ ਹੇਠਾਂ ਕਾਲ ਲਈ ਪੈਰਾਮੀਟਰ ਅਤੇ ਬਾਡੀ ਡਿਫਾਈਨ ਕਰੋ:

    ```python
    params = {
        'from': server_language,
        'to': language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` API ਕਾਲ ਨੂੰ ਪਾਸ ਕਰਨ ਲਈ ਪੈਰਾਮੀਟਰ ਨੂੰ ਡਿਫਾਈਨ ਕਰਦਾ ਹੈ, `from` ਅਤੇ `to` ਭਾਸ਼ਾਵਾਂ ਨੂੰ ਪਾਸ ਕਰਦਾ ਹੈ। ਇਹ ਕਾਲ `from` ਭਾਸ਼ਾ ਵਿੱਚ ਟੈਕਸਟ ਨੂੰ `to` ਭਾਸ਼ਾ ਵਿੱਚ ਅਨੁਵਾਦ ਕਰੇਗੀ।

    `body` ਅਨੁਵਾਦ ਕਰਨ ਲਈ ਟੈਕਸਟ ਨੂੰ ਸ਼ਾਮਲ ਕਰਦਾ ਹੈ। ਇਹ ਇੱਕ ਐਰੇ ਹੈ, ਕਿਉਂਕਿ ਇੱਕੋ ਕਾਲ ਵਿੱਚ ਕਈ ਟੈਕਸਟ ਬਲਾਕਾਂ ਦਾ ਅਨੁਵਾਦ ਕੀਤਾ ਜਾ ਸਕਦਾ ਹੈ।

1. REST API ਨੂੰ ਕਾਲ ਕਰੋ ਅਤੇ ਜਵਾਬ ਪ੍ਰਾਪਤ ਕਰੋ:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    ਵਾਪਸ ਆਉਣ ਵਾਲਾ ਜਵਾਬ ਇੱਕ JSON ਐਰੇ ਹੈ, ਜਿਸ ਵਿੱਚ ਇੱਕ ਆਈਟਮ ਹੁੰਦੀ ਹੈ ਜੋ ਅਨੁਵਾਦਾਂ ਨੂੰ ਸ਼ਾਮਲ ਕਰਦੀ ਹੈ। ਇਸ ਆਈਟਮ ਵਿੱਚ ਬਾਡੀ ਵਿੱਚ ਪਾਸ ਕੀਤੇ ਸਾਰੇ ਆਈਟਮਾਂ ਦੇ ਅਨੁਵਾਦਾਂ ਲਈ ਇੱਕ ਐਰੇ ਹੁੰਦੀ ਹੈ।

    ```json
    [
        {
            "translations": [
                {
                    "text": "Chronométrant votre minuterie de 2 minutes 27 secondes.",
                    "to": "fr"
                }
            ]
        }
    ]
    ```

1. ਐਰੇ ਵਿੱਚ ਪਹਿਲੇ ਆਈਟਮ ਤੋਂ ਪਹਿਲੇ ਅਨੁਵਾਦ ਤੋਂ `test` ਪ੍ਰਾਪਰਟੀ ਨੂੰ ਵਾਪਸ ਕਰੋ:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. SSML ਤਿਆਰ ਕਰਨ ਤੋਂ ਪਹਿਲਾਂ `say` ਫੰਕਸ਼ਨ ਨੂੰ ਕਹਿਣ ਲਈ ਟੈਕਸਟ ਦਾ ਅਨੁਵਾਦ ਕਰਨ ਲਈ ਅਪਡੇਟ ਕਰੋ:

    ```python
    print('Original:', text)
    text = translate_text(text)
    print('Translated:', text)
    ```

    ਇਹ ਕੋਡ ਮੂਲ ਅਤੇ ਅਨੁਵਾਦ ਕੀਤੇ ਟੈਕਸਟ ਦੇ ਵਰਜਨ ਨੂੰ ਕੰਸੋਲ ਵਿੱਚ ਪ੍ਰਿੰਟ ਕਰਦਾ ਹੈ।

1. ਆਪਣਾ ਕੋਡ ਚਲਾਓ। ਯਕੀਨੀ ਬਣਾਓ ਕਿ ਤੁਹਾਡਾ ਫੰਕਸ਼ਨ ਐਪ ਚਲ ਰਿਹਾ ਹੈ, ਅਤੇ ਉਪਭੋਗਤਾ ਦੀ ਭਾਸ਼ਾ ਵਿੱਚ ਟਾਈਮਰ ਦੀ ਬੇਨਤੀ ਕਰੋ, ਜਾਂ ਤਾਂ ਉਹ ਭਾਸ਼ਾ ਖੁਦ ਬੋਲ ਕੇ, ਜਾਂ ਅਨੁਵਾਦਕ ਐਪ ਦੀ ਵਰਤੋਂ ਕਰਕੇ।

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    Original: 2 minute 27 second timer started.
    Translated: 2 minute 27 seconde minute a commencé.
    Original: Times up on your 2 minute 27 second timer.
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

    > 💁 ਵੱਖ-ਵੱਖ ਭਾਸ਼ਾਵਾਂ ਵਿੱਚ ਕੁਝ ਕਹਿਣ ਦੇ ਵੱਖ-ਵੱਖ ਤਰੀਕਿਆਂ ਦੇ ਕਾਰਨ, ਤੁਹਾਨੂੰ ਅਨੁਵਾਦ ਮਿਲ ਸਕਦੇ ਹਨ ਜੋ LUIS ਨੂੰ ਦਿੱਤੇ ਉਦਾਹਰਨਾਂ ਤੋਂ ਥੋੜੇ ਵੱਖਰੇ ਹਨ। ਜੇਕਰ ਇਹ ਹੋਵੇ, ਤਾਂ LUIS ਵਿੱਚ ਹੋਰ ਉਦਾਹਰਨ ਸ਼ਾਮਲ ਕਰੋ, ਫਿਰ ਮਾਡਲ ਨੂੰ ਦੁਬਾਰਾ ਟ੍ਰੇਨ ਅਤੇ ਪਬਲਿਸ਼ ਕਰੋ।

> 💁 ਤੁਸੀਂ ਇਹ ਕੋਡ [code/virtual-iot-device](../../../../../6-consumer/lessons/4-multiple-language-support/code/virtual-iot-device) ਫੋਲਡਰ ਵਿੱਚ ਲੱਭ ਸਕਦੇ ਹੋ।

😀 ਤੁਹਾਡਾ ਬਹੁਭਾਸ਼ੀਕ ਟਾਈਮਰ ਪ੍ਰੋਗਰਾਮ ਸਫਲ ਰਿਹਾ!

---

**ਅਸਵੀਕਰਤੀ**:  
ਇਹ ਦਸਤਾਵੇਜ਼ AI ਅਨੁਵਾਦ ਸੇਵਾ [Co-op Translator](https://github.com/Azure/co-op-translator) ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਅਨੁਵਾਦ ਕੀਤਾ ਗਿਆ ਹੈ। ਜਦੋਂ ਕਿ ਅਸੀਂ ਸਹੀ ਹੋਣ ਦੀ ਕੋਸ਼ਿਸ਼ ਕਰਦੇ ਹਾਂ, ਕਿਰਪਾ ਕਰਕੇ ਧਿਆਨ ਦਿਓ ਕਿ ਸਵੈਚਾਲਿਤ ਅਨੁਵਾਦਾਂ ਵਿੱਚ ਗਲਤੀਆਂ ਜਾਂ ਅਸੁਚੀਤਤਾਵਾਂ ਹੋ ਸਕਦੀਆਂ ਹਨ। ਇਸ ਦੀ ਮੂਲ ਭਾਸ਼ਾ ਵਿੱਚ ਮੂਲ ਦਸਤਾਵੇਜ਼ ਨੂੰ ਅਧਿਕਾਰਤ ਸਰੋਤ ਮੰਨਿਆ ਜਾਣਾ ਚਾਹੀਦਾ ਹੈ। ਮਹੱਤਵਪੂਰਨ ਜਾਣਕਾਰੀ ਲਈ, ਪੇਸ਼ੇਵਰ ਮਨੁੱਖੀ ਅਨੁਵਾਦ ਦੀ ਸਿਫਾਰਸ਼ ਕੀਤੀ ਜਾਂਦੀ ਹੈ। ਇਸ ਅਨੁਵਾਦ ਦੀ ਵਰਤੋਂ ਤੋਂ ਪੈਦਾ ਹੋਣ ਵਾਲੇ ਕਿਸੇ ਵੀ ਗਲਤ ਫਹਿਮੀ ਜਾਂ ਗਲਤ ਵਿਆਖਿਆ ਲਈ ਅਸੀਂ ਜ਼ਿੰਮੇਵਾਰ ਨਹੀਂ ਹਾਂ।