<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "bbb5aa34221fe129dd3ce4d9ec33831a",
  "translation_date": "2026-01-07T03:39:09+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/pi-translate-speech.md",
  "language_code": "kn"
}
-->
# ಭಾಷಾಂತರಿಸಿ - ರಾಸ್ಪೆರಿ ಪೈ

ಪಾಠದ ಈ ಭಾಗದಲ್ಲಿ, ನಿಮಗೆ ಭಾಷಾಂತರಕರ ಸೇವೆಯನ್ನು ಬಳಸಿಕೊಂಡು ಪಠ್ಯವನ್ನು ಭಾಷಾಂತರಿಸುವ ಕೋಡ್ ಬರೆಯಬೇಕಾಗಿದೆ.

## ಭಾಷಾಂತರಕರ ಸೇವೆಯನ್ನು ಬಳಸಿ ಪಠ್ಯವನ್ನು ಮಾತಿಯಾಗಿ ಪರಿವರ್ತಿಸುವುದು

ಮಾತು ಸೇವೆಯ REST API ನೇರ ಭಾಷಾಂತರಗಳನ್ನು ಬೆಂಬಲಿಸುವುದಿಲ್ಲ, ಬದಲಿಗೆ ನೀವು ಮಾತಿನಿಂದ ಪಠ್ಯಕ್ಕೆ ಸೇವೆಯಿಂದ ಉತ್ಪಾದಿತ ಪಠ್ಯ ಮತ್ತು ಮಾತಿಸಿದ ಪ್ರತಿಕ್ರಿಯೆಯ ಪಠ್ಯವನ್ನು ಭಾಷಾಂತರಿಸಲು ಭಾಷಾಂತರಕರ ಸೇವೆಯನ್ನು ಬಳಸಬಹುದು. ಈ ಸೇವೆಗೆ ಪಠ್ಯವನ್ನು ಭಾಷಾಂತರಿಸಲು ನೀವು REST API ಬಳಸಬಹುದು.

### ಕಾರ್ಯ - ಪಠ್ಯವನ್ನು ಭಾಷಾಂತರಿಸಲು ಭಾಷಾಂತರಕರ ಸಂಸಾಧನವನ್ನು ಬಳಸುವುದು

1. ನಿಮ್ಮ ಸ್ಮಾರ್ಟ್ ಟೈಮರ್‌ಗೆ 2 ಭಾಷೆಗಳು ಹೊಂದಿಸಲಾಗುತ್ತವೆ - LUIS ಅನ್ನು ತರಬೇತು ನೀಡಲು ಬಳಸಿದ ಸರ್ವರ್ ಭಾಷೆ (ಅದೇ ಭಾಷೆ ಬಳಕೆದಾರನಿಗೆ ಮಾತಾಡಲು ಸಂದೇಶಗಳನ್ನು ನಿರ್ಮಿಸಲು ಸಹ ಬಳಕೆಯಾಗುತ್ತದೆ), ಮತ್ತು ಬಳಕೆದಾರನು ಮಾತನಾಡುವ ಭಾಷೆ. ಬಳಕೆದಾರನು ಮಾತನಾಡಲಿರುವ ಭಾಷೆಯನ್ನು ಸೂಚಿಸಲು `language` ವೇರಿಯಬಲ್ ಅನ್ನು ನವೀಕರಿಸಿ, ಮತ್ತು LUIS ತರಬೇತಿಗೆ ಬಳಸಲಾದ ಭಾಷೆಯಿಗಾಗಿ `server_language` ಎಂಬ ಹೊಸ ವ್ಯತ್ಯಾಸವನ್ನು ಸೇರಿಸಿ:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    `<user language>`ನ್ನು ನೀವು ಮಾತನಾಡಲಿರುವ ಭಾಷೆಯ ಸ್ಥಳಿಯtel ಹೆಸರು ಮೂಲಕ ಬದಲಾಯಿಸಿ, ಉದಾಹರಣೆಗೆ ಫ್ರೆಂಚ್‌ಗೆ `fr-FR`, ಅಥವಾ ಕ್ಯಾಂಟೋನೀಸ್‌ಗೆ `zn-HK`.

    `<server language>` ಅನ್ನು LUIS ತರಬೇತಿಗೆ ಬಳಸಲಾದ ಭಾಷೆಯ ಸ್ಥಳಿಯtel ಹೆಸರಿನಿಂದ ಬದಲಾಯಿಸಿ.

    Microsoft ಡಾಕ್ಸ್‌ನ [ಭಾಷೆ ಮತ್ತು ಧ್ವನಿ ಬೆಂಬಲದ ದಾಖಲೆಗಳಲ್ಲಿ](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) ಬೆಂಬಲಿತ ಭಾಷೆಗಳು ಮತ್ತು ಅವುಗಳ ಸ್ಥಳಿಯtel ಹೆಸರುಗಳ ಪಟ್ಟಿ ಇದೆ.

    > 💁 ನೀವು ಅನೇಕ ಭಾಷೆಗಳನ್ನು ಮಾತನಾಡದಲ್ಲದಿದ್ದರೆ, ನಿಮ್ಮ ಪ್ರಿಯ ಭಾಷೆಯಿಂದ ಇಚ್ಛಿತ ಭಾಷೆಗೆ ಭಾಷಾಂತರಿಸಲು [Bing Translate](https://www.bing.com/translator) ಅಥವಾ [Google Translate](https://translate.google.com)ದಂತಹ ಸೇವೆಗಳನ್ನು ಬಳಸಬಹುದು. ಈ ಸೇವೆಗಳು ನಂತರ ಭಾಷಾಂತರಿತ ಪಠ್ಯದ ಧ್ವನಿಯನ್ನು ನಡಿಸುತ್ತವೆ.
    >
    > ಉದಾಹರಣೆಗೆ, ನೀವು LUIS ಅನ್ನು ಇಂಗ್ಲಿಷ್‌ನಲ್ಲಿ ತರಬೇತು ನೀಡಿದಿದ್ದರೆ, ಆದರೆ ಬಳಕೆದಾರ ಭಾಷೆಯಾಗಿ ಫ್ರೆಂಚ್ ಅನ್ನು ಬಳಸಲು ಬಯಸಿದರೆ, ನೀವು "set a 2 minute and 27 second timer" ಎಂಬ ವಾಕ್ಯವನ್ನು ಇಂಗ್ಲಿಷ್‌ನಿಂದ ಫ್ರೆಂಚ್‌ಗೆ Bing Translate ಬಳಸಿ ಭಾಷಾಂತರಿಸಿ, ನಂತರ **Listen translation** ಬಟನ್ ಬಳಸಿ ಆ ಭಾಷಾಂತರವನ್ನು ನಿಮ್ಮ ಮೈಕ್ರೋಫೋನಿಗೆ ಹೇಳಬಹುದು.
    >
    > ![Bing translate ಮೇಲಿನ listen translation ಬಟನ್](../../../../../translated_images/kn/bing-translate.348aa796d6efe2a9.png)

1. `speech_api_key` ಕೆಳಗೆ ನಿಮ್ಮ ಭಾಷಾಂತರಕರ API ಕೀ ಅನ್ನು ಸೇರಿಸಿ:

    ```python
    translator_api_key = '<key>'
    ```

    `<key>` ಅನ್ನು ನಿಮ್ಮ ಭಾಷಾಂತರಕರ ಸೇವೆಯ API ಕೀ ನೊಂದಿಗೆ ಬದಲಾಯಿಸಿ.

1. `say` ಫಂಕ್ಷನ್‌ಗೆ م  ಮುನ್ನ, ಸರ್ವರ್ ಭಾಷೆಯಿಂದ ಬಳಕೆದಾರ ಭಾಷೆಗೆ ಪಠ್ಯವನ್ನು ಭಾಷಾಂತರಿಸುವ `translate_text` ಫಂಕ್ಷನ್ ಅನ್ನು ವ್ಯಾಖ್ಯಾನಿಸಿ:

    ```python
    def translate_text(text, from_language, to_language):
    ```

    ಈ ಫಂಕ್ಷನ್ಗೆ from ಮತ್ತು to ಭಾಷೆಗಳನ್ನಾ ಪಾಸ್ಸ್ ಮಾಡಲಾಗುತ್ತದೆ - ನಿಮ್ಮ ಅಪ್ಲಿಕೇಶನ್ ಮತೆತೆಯನ್ನು ಗುರುತಿಸುವಾಗ ಬಳಕೆದಾರ ಭಾಷೆಯಿಂದ ಸರ್ವರ್ ಭಾಷೆಗೆ ಮತ್ತು ಮಾತಿನ ಪ್ರತಿಕ್ರಿಯೆ ನೀಡುವಾಗ ಸರ್ವರ್ ಭಾಷೆಯಿಂದ ಬಳಕೆದಾರ ಭಾಷೆಗೆ ಪರಿವರ್ತಿಸುವ ಅಗತ್ಯವಿರುತ್ತದೆ.

1. ಈ ಫಂಕ್ಷನ್ ಒಳಗೆ REST API ಕರೆಗಾಗಿ URL ಮತ್ತು ಹেডರ್ಸ್ ಅನ್ನು ವ್ಯಾಖ್ಯಾನಿಸಿ:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    ಈ API ಗೆ URL ಸ್ಥಳ специфಿಕ್ ಅಲ್ಲ, ಬದಲಾಗಿ ಸ್ಥಳವು ಹೆಡ್ಡರ್ ನಲ್ಲಿ ಪಾಸಾಗುತ್ತದೆ. API ಕೀ ನೇರವಾಗಿ ಬಳಕೆಯಾಗುತ್ತದೆ, ಆದ್ದರಿಂದ ಸ್ಪೀಚ್ ಸೇವೆಯಂತೆ ಟೋಕನ್ ಬಿಡುಗಡೆದಾರ API ಯಿಂದ ಪ್ರವೇಶ ಟೋಕನ್ ಪಡೆಯಬೇಕಾಗಿಲ್ಲ.

1. ಕೆಳಗೆ ಕರೆಗಾಗಿ ಪರಿಮಿತಿಗಳು ಮತ್ತು ದೇಹವನ್ನು ವ್ಯಾಖ್ಯಾನಿಸಿ:

    ```python
    params = {
        'from': from_language,
        'to': to_language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` API ಕರೆಯಲ್ಲಿಗೆ from ಮತ್ತು to ಭಾಷೆಗಳನ್ನು ಪಾಸಾಗುತ್ತದೆ. ಈ ಕರೆ `from` ಭಾಷೆಯ ಪಠ್ಯವನ್ನು `to` ಭಾಷೆಗೆ ಭಾಷಾಂತರಿಸುತ್ತದೆ.

    `body` ಭಾಷಾಂತರಗೊಳ್ಳುವ ಪಠ್ಯವನ್ನು ಹೊಂದಿದೆ. ಇದು ಅರೆ, ಏಕೆಂದರೆ ಒಂದೇ ಕರೆಗಳಲ್ಲಿ ಹಲವಾರು ಪಠ್ಯದ ಬ್ಲಾಕ್‌ಗಳನ್ನು ಭಾಷಾಂತರಿಸಬಹುದು.

1. REST API ಅನ್ನು ಕರೆ ಮಾಡಿ, ಮತ್ತು ಪ್ರತಿಕ್ರಿಯೆಯನ್ನು ಪಡೆಯಿರಿ:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    ಬರುವ ಪ್ರತಿಕ್ರಿಯೆ ಒಂದು JSON ಅರೆ ಆಗಿದ್ದು, ಇದರಲ್ಲಿ ಒಬ್ಬಐಟಮ್ ಇರುತ್ತದೆ ಮತ್ತು ಅದು ಬಹು ಭಾಷಾಂತರಗಳನ್ನು ಹೊಂದಿರುವ ಅರೆ ಹೊಂದಿದೆ, ಇದು ದೇಹದಲ್ಲಿ ಪಾಸಾದ ಎಲ್ಲಾ ಐಟಂಗಳ ಭಾಷಾಂತರಗಳನ್ನೊಳಗೊಂಡಿದೆ.

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

1. ಅರೆ ಮೊದಲನೆಯ ಐಟಮನಿಂದ ಮೊದಲನೆಯ ಭಾಷಾಂತರದ `text` ಗುಣಲಕ್ಷಣವನ್ನು ಮರಳಿ ನೀಡಿರಿ:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. `while True` ಲೂಪ್ನಲ್ಲಿ `convert_speech_to_text` ಕರೆದಿಂದ ಬಂದ ಪಠ್ಯವನ್ನು ಬಳಕೆದಾರ ಭಾಷೆಯಿಂದ ಸರ್ವರ್ ಭಾಷೆಗೆ ಭಾಷಾಂತರಿಸುವಂತೆ ನವೀಕರಿಸಿ:

    ```python
    if len(text) > 0:
        print('Original:', text)
        text = translate_text(text, language, server_language)
        print('Translated:', text)

        message = Message(json.dumps({ 'speech': text }))
        device_client.send_message(message)
    ```

    ಈ ಕೋಡ್ ಮೂಲ ಮತ್ತು ಭಾಷಾಂತರಿಸಲಾದ ಪಠ್ಯವನ್ನು ಕಾನ್ಸೋಲ್‌ಗೂ ಪ್ರಿಂಟ್ ಮಾಡುತ್ತದೆ.

1. `say` ಫಂಕ್ಷನ್ನನ್ನು ನವೀಕರಿಸಿ, ಹೇಳಬೇಕಾದ ಪಠ್ಯವನ್ನು ಸರ್ವರ್ ಭಾಷೆಯಿಂದ ಬಳಕೆದಾರ ಭಾಷೆಗೆ ಭಾಷಾಂತರಿಸುವಂತೆ ಮಾಡಿರಿ:

    ```python
    def say(text):
        print('Original:', text)
        text = translate_text(text, server_language, language)
        print('Translated:', text)
        speech = get_speech(text)
        play_speech(speech)
    ```

    ಈ ಕೋಡ್ ಮೂಲ ಮತ್ತು ಭಾಷಾಂತರಿಸಲಾದ ಪಠ್ಯವನ್ನು ಕಾನ್ಸೋಲ್‌ನಲ್ಲಿ ಕೂಡಾ ಮುದ್ರಿಸುತ್ತದೆ.

1. ನಿಮ್ಮ ಕೋಡ್ ಅನ್ನು ಚಾಲನೆ ಮಾಡಿ. ನಿಮ್ಮ ಫಂಕ್ಷನ್ ಅಪ್ಲಿಕೇಶನ್ ಚಾಲನೆಯಲ್ಲಿದೆ ಎಂದು ಖಚಿತಪಡಿಸಿ, ಮತ್ತು ಬಳಕೆದಾರ ಭಾಷೆಯಲ್ಲಿ ಟೈಮರ್ ಕೇಳಿ, ನೀವು ಆ ಭಾಷೆಯಲ್ಲಿ ಮಾತನಾಡೋ ಅಥವಾ ಭಾಷಾಂತರ ಅಪ್ಲಿಕೇಶನ್ ಬಳಸಿ ಕೇಳಬಹುದು.

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

    > 💁 ವಿಭಿನ್ನ ಭಾಷೆಗಳಲ್ಲಿ ಒಂದೇ ವಿಷಯವನ್ನು ಹೇಳುವ ವಿಭಿನ್ನ ರೀತಿಗಳ ಕಾರಣ, ನೀವು LUIS ಗೆ ನೀಡಿದ ಉದಾಹರಣೆಗಿಂತ ಸ್ವಲ್ಪ ತಾರತಮ್ಯವಾಗಿರುವ ಭಾಷಾಂತರಗಳನ್ನು ಪಡೆಯಬಹುದು. ಹೀಗಿದ್ದರೆ, LUIS ಗೆ ಇನ್ನಷ್ಟು ಉದಾಹರಣೆಗಳನ್ನು ಸೇರಿಸಿ, ಮರುವಿಧಾನ ಮಾಡಿ ನಂತರ ಮತ್ತೆ ಮಾದರಿಯನ್ನು ಪ್ರಕಟಿಸಿ.

> 💁 ಈ ಕೋಡ್ ಅನ್ನು ನೀವು [code/pi](../../../../../6-consumer/lessons/4-multiple-language-support/code/pi) ಫೋಲ್ಡರ್‌ನಲ್ಲಿ ಕಾಣಬಹುದು.

😀 ನಿಮ್ಮ ಬಹುಭಾಷಾ ಟೈಮರ್ ಕಾರ್ಯಕ್ರಮ ಯಶಸ್ವಿಯಾಯಿತು!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**ಕಡೆಬಾಣಿ**:
ಈ ದಸ್ತಾವೇಜು [Co-op Translator](https://github.com/Azure/co-op-translator) ಎಂಬ AI ಭಾಷಾಂತರ ಸೇವೆಯನ್ನು ಬಳಸಿ ಭಾಷಾಂತರಿಸಲಾಗಿದೆ. ನಾವು ಶ್ರೇಷ್ಠತೆಗಾಗಿ ಪ್ರಯತ್ನಿಸುತ್ತಿದ್ದರೂ, ಸ್ವಯಂಚಾಲಿತ ಭಾಷಾಂತರದಲ್ಲಿ ತಪ್ಪುಗಳು ಅಥವಾ ಅೌಪಚಾರಿಕತೆಗಳಿದ್ದುಕೊಳ್ಳುವ ಸಾಧ್ಯತೆ ಇದ್ದಾರೆ ಎಂದು ದಯವಿಟ್ಟು ಗಮನಿಸಿ. ಮೂಲ ದಸ್ತಾವೇಜಿನ ನಾಡಿನ ಭಾಷೆಯನ್ನು ಪ್ರಾಮಾಣಿಕ ಮೂಲ ಎಂದು ಪರಿಗಣಿಸಬೇಕು. ಗಂಭೀರ್ ಮಾಹಿತಿಗಾಗಿ ವೃತ್ತಿಪರ ಮಾನವ ಭಾಷಾಂತರವನ್ನು ಶಿಫಾರಸು ಮಾಡಲಾಗುತ್ತದೆ. ಈ ಭಾಷಾಂತರ ಬಳಕೆಯಿಂದ ಉಂಟಾಗುವ ಯಾವುದೇ ತಪ್ಪು ಪರಿಭಾಷೆಗಳಿಗೆ ಅಥವಾ ತಪ್ಪು ಅರ್ಥಮಾಡಿಕೊಳ್ಲುವುದಕ್ಕಾಗಿಯೂ ನಾವು ಜವಾಬ್ದಾರಿಯಲ್ಲ.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->