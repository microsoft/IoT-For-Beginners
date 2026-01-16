<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d620a470d9dd8614d99824832978360a",
  "translation_date": "2026-01-07T03:45:07+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/virtual-device-translate-speech.md",
  "language_code": "kn"
}
-->
# ಭಾಷಾಂತರಿಸಿ ಮಾತನಾಡಿ - ವರ್ಚುವಲ್ ಐಒಟಿ ಸಾಧನ

ಪಾಠದ ಈ ಭಾಗದಲ್ಲಿ, ನೀವು ಭಾಷಾಂತರ ಸೇವೆಯನ್ನು ಬಳಸುವುದರ ಮೂಲಕ ಭಾಷಾಂತರಿಸುವಾಗ ಮಾತನ್ನು ಪಠ್ಯಕ್ಕೆ ಪರಿವರ್ತಿಸುವ ಕೋಡ್ ಬರೆಯುತ್ತೀರಿ, ನಂತರ ಪಠ್ಯವನ್ನು ಅನುವಾದಕ ಸೇವೆ ಬಳಸಿಕೊಂಡು ಭಾಷಾಂತರಿಸಿ ಮಾತೃಭಾಷೆಯ ಉತ್ತರ ರಚಿಸುವಿರಿ.

## ಮಾತುಕತೆ ಸೇವೆಯನ್ನು ಬಳಸಿ ಭಾಷಾಂತರಿಸಿ ಮಾತನಾಡಿ

ಮಾತುಕತೆ ಸೇವೆ ಮಾತನ್ನು ತೆಗೆದುಕೊಂಡು ಅದನ್ನು ಅದೇ ಭಾಷೆಯಲ್ಲಿ ಪಠ್ಯಕ್ಕೆ ಪರಿವರ್ತಿಸುವುದಲ್ಲದೆ, ಅದರ ಔಟ್ಪುಟ್ ಅನ್ನು ಬೇರೆ ಭಾಷೆಗಳಿಗೆ ಅನುವಾದಿಸಬಹುದು.

### ಕಾರ್ಯ - ಮಾತುಕತೆ ಸೇವೆಯನ್ನು ಬಳಸಿ ಮಾತನಾಡಿ ಭಾಷಾಂತರಿಸಿ

1. VS ಕೋಡ್‌ನಲ್ಲಿ `smart-timer` ಪ್ರಾಜೆಕ್ಟ್ ಅನ್ನು ತೆರೆಯಿರಿ ಮತ್ತು ಟರ್ಮಿನಲ್‌ನಲ್ಲಿ ವರ್ಚುವಲ್ ವಾತಾವರಣ ಲೋಡ್ ಆಗಿದೆಯೇ ಪರಿಶೀಲಿಸಿ.

1. ಈಗಿನ ಇಂಪೋರ್ಟ್‌ಗಳ ಕೆಳಗೆ ಕೆಳಗಿನ ಇಂಪೋರ್ಟ್ ಹೇಳಿಕೆಗಳನ್ನು ಸೇರಿಸಿ:

    ```python
    from azure.cognitiveservices import speech
    from azure.cognitiveservices.speech.translation import SpeechTranslationConfig, TranslationRecognizer
    import requests
    ```

    ಇದು ಭಾಷಾಂತರಿಸುವ ಮಾತುಗಳನ್ನು ಬಳಸಲು ಕ್ಲಾಸ್‌ಗಳನ್ನು ಮತ್ತು ನಂತರ ಈ ಪಾಠದಲ್ಲಿ ಅನುವಾದಕ ಸೇವೆಗೆ ಕರೆದೊಯ್ಯಲು ಬಳಸುವ `requests` ಲೈಬ್ರರಿ ಅನ್ನು ಇಂಪೋರ್ಟ್ ಮಾಡುತ್ತದೆ.

1. ನಿಮ್ಮ ಸ್ಮಾರ್ಟ್ тайಮರ್‌ನಲ್ಲಿರೋ ಎರಡು ಭಾಷೆಗಳು ಇರುತ್ತವೆ - LUIS ತರಬೇತಿಗೆ ಬಳಸುವ ಸರ್ವರ್‌ ಭಾಷೆ (ಆದಂತೆ ಬಳಕೆದಾರರೊಂದಿಗೆ ಮಾತನಾಡಲು ಸಂದೇಶಗಳನ್ನು ರಚಿಸಲು ಕೂಡ ಅದೇ ಭಾಷೆಯನ್ನು ಬಳಸಲಾಗುತ್ತದೆ), ಮತ್ತು ಬಳಕೆದಾರರು ಮಾತಾಡುವ ಭಾಷೆ. `language` चरವನ್ನು ಬಳಕೆದಾರರು ಮಾತಾಡುವ ಭಾಷೆಗೆ ನವೀಕರಿಸಿ, ಮತ್ತು LUIS ತರಬೇತಿಗೆ ಬಳಸುವ ಭಾಷೆಗೆ `server_language` ಎಂಬ ಹೊಸ चरವನ್ನು ಸೇರಿಸಿ:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    `<user language>`ನ್ನು ನೀವು ಮಾತಾಡಲಿರುವ ಭಾಷೆಯ ಸ್ಥಳೀಯ ಮುಖ್ಯಶಬ್ದದಿಂದ ಬದಲಿಸಿ, ಉದಾಹರಣೆಗೆ ಫ್ರೆಂಚ್ ಗಾಗಿ `fr-FR` ಅಥವಾ ಕಾಂಟೋನೀಸ್ ಗಾಗಿ `zn-HK`.

    `<server language>`ನ್ನು LUIS ತರಬೇತಿಗೆ ಬಳಸುವ ಭಾಷೆಯ ಸ್ಥಳೀಯ ಮುಖ್ಯಶಬ್ದದಿಂದ ಬದಲಿಸಿ.

    ನೀವು ಬೆಂಬಲಿತ ಭಾಷೆಗಳ ಮತ್ತು ಅವುಗಳ ಸ್ಥಳೀಯ ಹೆಸರಿನ ಪಟ್ಟಿಯನ್ನು [Language and voice support documentation on Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) ನಲ್ಲಿ ಕಾಣಬಹುದು.

    > 💁 ನೀವು ಬಹುಭಾಷಿ ಮಾತನಾಡದಿದ್ದರೆ, ನಿಮ್ಮ ಇಷ್ಟದ ಭಾಷೆಯಲ್ಲಿಂದ ಇಚ್ಛಿತ ಭಾಷೆಗೆ ಅನುವಾದ ಮಾಡಲು [Bing Translate](https://www.bing.com/translator) ಅಥವಾ [Google Translate](https://translate.google.com) ಹಾಗು ಸೇವೆಗಳನ್ನು ಬಳಸಬಹುದು. ಈ ಸೇವೆಗಳು ಅನುವಾದಿಸಲಾದ ಪಠ್ಯದ ಧ್ವನಿಯನ್ನು ನಿರ್ವಹಿಸುತ್ತವೆ. ಆದರೆ ಸ್ಪೀಚ್ ರಿಕಾಗ್ನೈಜರ್ ನಿಮ್ಮ ಸಾಧನದ ಕೆಲವು ಧ್ವನಿಯನ್ನು ಗಮನಿಸದು, ಆದಕಾರಣ ನೀವು ಅನುವಾದಿತ ಪಠ್ಯವನ್ನು ಕೇಳಿಸಲು ಮತ್ತೊಂದು ಸಾಧನವನ್ನು ಬಳಸಬೇಕಾಗಬಹುದು.
    >
    > ಉದಾಹರಣೆಗೆ, ನೀವು LUIS ಅನ್ನು ಇಂಗ್ಲಿಷ್ ನಲ್ಲಿ ತರಬೇತಿದೆಯಾದರೂ, ಬಳಕೆದಾರ ಭಾಷೆಯಾಗಿಯೂ ಫ್ರೆಂಚ್ ಬಳಸಬೇಕಾದರೆ, "set a 2 minute and 27 second timer" ಎಂಬ ವಾಕ್ಯವನ್ನು ಇಂಗ್ಲಿಷ್ ನಿಂದ ಫ್ರೆಂಚ್ ಗೆ Bing Translate ಬಳಸಿ ಅನುವಾದಿಸಿ, ನಂತರ **Listen translation** ಬಟನ್ ಬಳಸಿ ಅನುವಾದಿತ ಆಡಿಯೋವನ್ನು ಮೈಕ್ರೋಫೋನ್ ನಲ್ಲಿ ಹೇಳಬಹುದಾಗಿದೆ.
    >
    > ![Bing translate上的听译按钮](../../../../../translated_images/kn/bing-translate.348aa796d6efe2a9.png)

1. `recognizer_config` ಮತ್ತು `recognizer` ಘೋಷಣೆಗಳನ್ನು ಕೆಳಗಿನಂತೆ ಬದಲಿಸಿ:

    ```python
    translation_config = SpeechTranslationConfig(subscription=speech_api_key,
                                                 region=location,
                                                 speech_recognition_language=language,
                                                 target_languages=(language, server_language))
    
    recognizer = TranslationRecognizer(translation_config=translation_config)
    ```

    ಇದು ಬಳಕೆದಾರ ಭಾಷೆಯಲ್ಲಿ ಮಾತು ಗುರುತಿಸಲು ಹಾಗೂ ಬಳಕೆದಾರ ಮತ್ತು ಸರ್ವರ್ ಭಾಷೆಯಲ್ಲಿ ಭಾಷಾಂತರಗಳನ್ನು ರಚಿಸುವ ಅನುವಾದ ಸಂರಚನೆಯನ್ನು ಸೃಷ್ಟಿಸುತ್ತದೆ. ಆಮೇಲೆ ಈ ಸಂರಚನೆಯನ್ನು ಬಳಸಿಕೊಂಡು ಅನುವಾದ ಗುರುತಿಸುವ ಯಂತ್ರವನ್ನು ರಚಿಸುತ್ತದೆ - ಒಂದು ಮಾತು ಗುರುತಿಸುವ ಯಂತ್ರವು ಮಾತನಾಡಿದ ಭಾಷೆಯನ್ನು ವಿವಿಧ ಭಾಷೆಗಳಲ್ಲಿ ಅನುವಾದಿಸುತ್ತದೆ.

    > 💁 ಮೂಲ ಭಾಷೆಯನ್ನು `target_languages` ನಲ್ಲಿ ನಿರ್ದಿಷ್ಟ ಮಾಡಬೇಕು, ಇಲ್ಲದಿದ್ದರೆ ಯಾವುದೇ ಅನುವಾದಗಳಿಲ್ಲ.

1. `recognized` ಫಂಕ್ಷನ್ ನೊಳಗೆ ಸಂಪೂರ್ಣವಾದ ವಿಷಯವನ್ನು ಕೆಳಗಿನದರಿಂದ ಬದಲಿಸಿ:

    ```python
    if args.result.reason == speech.ResultReason.TranslatedSpeech:
        language_match = next(l for l in args.result.translations if server_language.lower().startswith(l.lower()))
        text = args.result.translations[language_match]
        if (len(text) > 0):
            print(f'Translated text: {text}')
    
            message = Message(json.dumps({ 'speech': text }))
            device_client.send_message(message)
    ```

    ಈ ಕೋಡ್ ಒಪ್ಪ groove(event) fires because speech was translated ಎಂದು ಪರಿಶೀಲಿಸುವುದು (ಈ ಕಾರ್ಯವಿಧಾನ ಇತರ ಸಂದರ್ಭಗಳಲ್ಲಿಯೂ ಚಾಲನೆಗೊಳ್ಳಬಹುದು, ಉದಾಹರಣೆಗೆ ಮಾತು ಗುರುತಿಸಲಾಯಿತು ಆದರೆ ಭಾಷಾಂತರಿಸಲಿಲ್ಲ). ಮಾತು ಭಾಷಾಂತರಿತವಾಗಿದ್ದರೆ, `args.result.translations` ನ ಡಿಕ್ಷನರಿಯಲ್ಲಿನ ಸರ್ವರ್ ಭಾಷೆಗೆ ಹೊಂದಿಕೆಯಾಗುವ ಭಾಷಾಂತರವನ್ನು ಹುಡುಕುತ್ತದೆ.

    `args.result.translations` ಡಿಕ್ಷನರಿ ಸ್ಥಳೀಯ ಸೆಟ್ಟಿಗಿನ ಭಾಷೆಯ ಭಾಗದ ಮೇರೆಗೆ ಕೀಲಿಮಣೆ ಮಾಡಲ್ಪಟ್ಟಿದೆ, ಸಂಪೂರ್ಣ ಸೆಟ್ಟಿಗով ಅಲ್ಲ. ಉದಾಹರಣೆಗೆ, ನೀವು `fr-FR` ಕನ್ನಡಿಗೆ ಅನುವಾದವನ್ನು ಕೇಳಿದಲ್ಲಿ, ಡಕ್ಷಿಣರಿಯಲ್ಲಿ `fr` ಪ್ರವೇಶವಿದೆ, `fr-FR` ಅಲ್ಲ.

    ಅನುವಾದಿತ ಪಠ್ಯವನ್ನು ನಂತರ IoT ಹಬ್ ಗೆ ಕಳುಹಿಸಲಾಗುತ್ತದೆ.

1. ಈ ಕೋಡ್ ಅನ್ನು ಚಾಲನೆಯಲ್ಲಿಡಿ ಮತ್ತು ಭಾಷಾಂತರಗಳನ್ನು ಪರೀಕ್ಷಿಸಿ. ನಿಮ್ಮ ಫಂಕ್ಷನ್ ಅಪ್ಲಿಕೇಶನ್ ಚಾಲನೆಗಿರುವುದನ್ನು ಖಚಿತಪಡಿಸಿ ಮತ್ತು ಬಳಕೆದಾರ ಭಾಷೆಯಲ್ಲಿ ಟೈಮರ್ ಕೇಳಿ, ಸ್ವತಃ ಆ ಭಾಷೆಯಲ್ಲಿ ಮಾತಾಡಿ ಅಥವಾ ಅನುವಾದ ಅಪ್ಲಿಕೇಶನ್ ಬಳಸಿಕೊಳ್ಳಿ.

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    ```

## ಅನುವಾದಕ ಸೇವೆಯನ್ನು ಬಳಸಿ ಪಠ್ಯವನ್ನು ಭಾಷಾಂತರಿಸಿ

ಮಾತುಕತೆ ಸೇವೆ ಪಠ್ಯವನ್ನು ಧ್ವನಿಗೆ ಹಿಂದಿರುಗಿಸಿ ಭಾಷಾಂತರಿಸುವುದನ್ನು ಬೆಂಬಲಿಸುವುದಿಲ್ಲ, ಬದಲಿಗೆ ನೀವು Translator ಸೇವೆಯನ್ನು ಬಳಸಬಹುದು. ಈ ಸೇವೆಗೆ REST API ಇದೆ, ಅದನ್ನು ಬಳಸಿ ಪಠ್ಯವನ್ನು ಭಾಷಾಂತರಿಸಬಹುದು.

### ಕಾರ್ಯ - ಅನುವಾದಕ ಸಂಪನ್ಮೂಲವನ್ನು ಬಳಸಿ ಪಠ್ಯ ಭಾಷಾಂತರಿಸುವುದು

1. `speech_api_key` ಕೆಳಗೆ Translator API ಕೀ ಸೇರಿಸಿ:

    ```python
    translator_api_key = '<key>'
    ```

    `<key>` ಅನ್ನು ನಿಮ್ಮ ಅನುವಾದಕ ಸೇವೆಯ API ಕೀಯಿಂದ ಬದಲಿಸಿ.

1. `say` ಫಂಕ್ಷನ್‌ಗಿಂತ ಮೇಲಿನಲ್ಲಿ, ಸರ್ವರ್ ಭಾಷೆಯಿಂದ ಬಳಕೆದಾರ ಭಾಷೆಗೆ ಪಠ್ಯವನ್ನು ಭಾಷಾಂತರಿಸುವ `translate_text` ಫಂಕ್ಷನ್ ಅನ್ನು ವ್ಯಾಖ್ಯಾನಿಸಿ:

    ```python
    def translate_text(text):
    ```

1. ಈ ಫಂಕ್ಷನ್ ಒಳಗೆ, REST API ಕರೆಗಾಗಿ URL ಮತ್ತು ಹೆಡರ್‌ಗಳನ್ನು ವ್ಯಾಖ್ಯಾನಿಸಿ:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    ಈ API ಯ URL ಸ್ಥಳಿಗತ ಅಲ್ಲ, ಸ್ಥಳವನ್ನು ಹೆಡರ್ ಮೂಲಕ ಪಾಸ್ ಮಾಡಲಾಗಿದೆ. API ಕೀ ನೇರವಾಗಿ ಬಳಸಿ, ಆದಕಾರಣ ಸ್ಪೀಚ್ ಸೇವೆಯಂತೆ ಟೋಕನ್ ઈಸೂअर API ಯಿಂದ ಪ್ರವೇಶ ಟೋಕನ್ ಪಡೆಯಬೇಕಾಗಿಲ್ಲ.

1. ಕೆಳಗೆ, ಕರೆಗಾಗಿ ಪರಿಮಾಣಗಳು ಮತ್ತು ದೇಹವನ್ನು ವ್ಯಾಖ್ಯಾನಿಸಿ:

    ```python
    params = {
        'from': server_language,
        'to': language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` API ಕರೆಗೆ ಪಾಸ್ ಮಾಡುವ ಪರಿಮಾಣಗಳಾಗಿದ್ದು, ಮೂಲ ಮತ್ತು ಗಮ್ಯ ಭಾಷೆಗಳನ್ನು ಪಾಸ್ ಮಾಡುತ್ತದೆ. ಈ ಕರೆ ಮೂಲ ಭಾಷೆಯ ಪಠ್ಯವನ್ನು ಗಮ್ಯ ಭಾಷೆಗೆ ಭಾಷಾಂತರಿಸುತ್ತದೆ.

    `body` ಭಾಷಾಂತರ ಮಾಡುವ ಪಠ್ಯವನ್ನು ಹೊಂದಿದೆ. ಇದು ಸರಣಿಯಾಗಿದ್ದು, ಒಂದೇ ಕರೆ ನಲ್ಲಿ ಹಲವಾರು ಪಠ್ಯ ಬ್ಲಾಕ್ಗಳನ್ನು ಭಾಷಾಂತರಿಸಬಹುದು.

1. REST API ಗೆ ಕರೆ ಮಾಡಿ ಮತ್ತು ಪ್ರತಿಕ್ರಿಯೆಯನ್ನು ಪಡೆಯಿರಿ:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    ಶೀಘ್ರವಾಗಿ ಬರುವ ಪ್ರತಿಕ್ರಿಯೆಯು JSON ಸರಣಿಯಾಗಿದ್ದು, ಒಂದು ಐಟಂ ಭಾಸೆಯಲ್ಲಿ ಅನುವಾದಗಳ ಜೊತೆ ಇದೆ. ಈ ಐಟಮ್ ದೇಹಕ್ಕೆ ಹಿಂತೆಗೆದ ಎಲ್ಲ ಐಟಂಗಳ ಅನುವಾದಗಳ ಸರಣಿಯನ್ನು ಹೊಂದಿದೆ.

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

1. ಸರಣಿಯ ಮೊದಲ ಐಟಂಮೇಲೆ ಮೊದಲ ಅನುವಾದದಿಂದ `text` ಪ್ರಾಪರ್ಟಿಯನ್ನು ಹಿಂದಿರುಗಿಸಿ:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. SSML ರಚನೆಯ ಮೊದಲು ಹೇಳುವ ಪಠ್ಯವನ್ನು ಅನುವಾದಿಸಲು `say` ಫಂಕ್ಷನ್ ಅನ್ನು ನವೀಕರಿಸಿ:

    ```python
    print('Original:', text)
    text = translate_text(text)
    print('Translated:', text)
    ```

    ಈ ಕೋಡ್ ಮೂಲ ಮತ್ತು ಅನುವಾದಿತ ಪಠ್ಯಗಳನ್ನು ಕನ್ಸೋಲ್ ನಲ್ಲಿ ಮುದ್ರಿಸುತ್ತದೆ.

1. ನಿಮ್ಮ ಕೋಡ್ ಆಪ್ತ ಮಾಡಿ. ನಿಮ್ಮ ಫಂಕ್ಷನ್ ಅಪ್ಲಿಕೇಶನ್ ಚಾಲನೆಗಿರುವುದನ್ನು ಖಚಿತಪಡಿಸಿ ಮತ್ತು ಬಳಕೆದಾರ ಭಾಷೆಯಲ್ಲಿ ಟೈಮರ್ ಕೇಳಿ, ಸ್ವತಃ ಆ ಭಾಷೆಯಲ್ಲಿ ಮಾತಾಡಿ ಅಥವಾ ಅನುವಾದ ಅಪ್ಲಿಕೇಶನ್ ಬಳಸಿ.

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

    > 💁 ವಿವಿಧ ಭಾಷೆಗಳಲ್ಲಿ ಒಂದೇ ವಿಷಯವನ್ನು ಹೇಳುವ ವಿಧಗಳಲ್ಲಿ ವ್ಯತ್ಯಾಸಗಳಿರುವುದರಿಂದ, ನೀವು ನೀಡಿದ ಉದಾಹರಣೆಗಳಿಗಿಂತ ಭಿನ್ನ ಅನುವಾದಗಳು ಬರುತ್ತವೆ. ಈ ಸಂದರ್ಭದಲ್ಲಿ LUIS ಗೆ ಹೆಚ್ಚಿನ ಉದಾಹರಣೆಗಳನ್ನು ಸೇರಿಸಿ, ಮರುತರಬೇತಿ ನೀಡಿ ಮತ್ತು ಮಾದರಿಯನ್ನು ಮರುಪ್ರಕಾಶನ ಮಾಡಿ.

> 💁 ನೀವು ಈ ಕೋಡ್ ಅನ್ನು [code/virtual-iot-device](../../../../../6-consumer/lessons/4-multiple-language-support/code/virtual-iot-device) ಫೋಲ್ಡರ್‌ನಲ್ಲಿ ಕಾಣಬಹುದು.

😀 ನಿಮ್ಮ ಬಹುಭಾಷಿ ಟೈಮರ್ ಪ್ರೋಗ್ರಾಂ ಯಶಸ್ವಿಯಾಗಿದೆ!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**ತಗ್ಗುಮಣೆ**:  
ಈ ದಾಖಲೆ AI ಅನುವಾದ ಸೇವೆ [Co-op Translator](https://github.com/Azure/co-op-translator) ಬಳಸಿ ಅನುವಾದಿಸಲಾಗಿದೆ. ನಾವು ನಿಖರತೆಗೆ ಪ್ರಯತ್ನಿಸುತ್ತಿದ್ದರೂ, ಸ್ವಯಂಚಾಲಿತ ಅನುವಾದಗಳಲ್ಲಿ ತಪ್ಪುಗಳು ಅಥವಾ ಅಸತ್ಯತೆಗಳು ಇರಬಹುದು ಎಂದು ದಯವಿಟ್ಟು ಗಮನಿಸಿ. ಮೂಲ ಭಾಷೆಯಲ್ಲಿರುವ ಮೂಲ ದಾಖಲೆ ಅನ್ನು ಅಧಿಕೃತ ಮೂಲವೆಂದು ಪರಿಗಣಿಸಬೇಕು. ಪ್ರಮುಖ ಮಾಹಿತಿಗಾಗಿ ವೃತ್ತಿಪರ ಮಾನವ ಅನುವಾದವನ್ನು ಶಿಫಾರಸು ಮಾಡಲಾಗುತ್ತದೆ. ಈ ಅನುವಾದ ಬಳಕೆಯಿಂದ ಉಂಟಾಗುವ ಯಾವುದೇ ಹಿನ್ನಿಳಿಕೆಗಳು ಅಥವಾ ತಪ್ಪು ಅರ್ಥಮಾಡಿಕೋಳಲು ಸಂಬಂಧಿಸಿದ ಬಾಧ್ಯತೆ ನಮ್ಮದಾಗಿರದು.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->