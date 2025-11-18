<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d620a470d9dd8614d99824832978360a",
  "translation_date": "2025-11-18T19:21:20+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/virtual-device-translate-speech.md",
  "language_code": "pcm"
}
-->
# Translate speech - Virtual IoT Device

For dis part of di lesson, you go write code wey go translate wetin person talk wen e dey convert am to text wit di speech service, den translate di text wit di Translator service before e go generate di spoken response.

## Use di speech service to translate wetin person talk

Di speech service fit take wetin person talk and no just convert am to text for di same language, but e fit also translate di output go oda languages.

### Task - use di speech service to translate wetin person talk

1. Open di `smart-timer` project for VS Code, and make sure say di virtual environment dey load for di terminal.

1. Add di import statements wey dey below di existing imports:

    ```python
    from azure.cognitiveservices import speech
    from azure.cognitiveservices.speech.translation import SpeechTranslationConfig, TranslationRecognizer
    import requests
    ```

    Dis one go import di classes wey dem dey use to translate wetin person talk, and di `requests` library wey dem go use to make call to di Translator service later for dis lesson.

1. Your smart timer go get 2 languages set - di language of di server wey dem use train LUIS (di same language dem dey use build di messages wey dem dey talk to di user), and di language wey di user dey talk. Update di `language` variable to be di language wey di user go dey talk, and add new variable wey dem call `server_language` for di language wey dem use train LUIS:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    Replace `<user language>` wit di locale name for di language wey you go dey talk, like `fr-FR` for French, or `zn-HK` for Cantonese.

    Replace `<server language>` wit di locale name for di language wey dem use train LUIS.

    You fit find list of di supported languages and dia locale names for di [Language and voice support documentation on Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 If you no sabi talk plenty languages, you fit use service like [Bing Translate](https://www.bing.com/translator) or [Google Translate](https://translate.google.com) to translate from di language wey you sabi to di language wey you choose. Dis services fit play audio of di translated text. But make you know say di speech recognizer go ignore some audio output from your device, so you fit need another device to play di translated text.
    >
    > Example, if you train LUIS for English, but you wan use French as di user language, you fit translate sentences like "set a 2 minute and 27 second timer" from English go French wit Bing Translate, den use di **Listen translation** button to talk di translation into your microphone.
    >
    > ![Di listen translation button for Bing translate](../../../../../translated_images/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.pcm.png)

1. Replace di `recognizer_config` and `recognizer` declarations wit dis one:

    ```python
    translation_config = SpeechTranslationConfig(subscription=speech_api_key,
                                                 region=location,
                                                 speech_recognition_language=language,
                                                 target_languages=(language, server_language))
    
    recognizer = TranslationRecognizer(translation_config=translation_config)
    ```

    Dis one go create translation config to recognize wetin person talk for di user language, and create translations for di user and server language. E go use dis config to create translation recognizer - speech recognizer wey fit translate di output of di speech recognition into plenty languages.

    > 💁 Di original language need to dey specified for di `target_languages`, if not you no go get any translations.

1. Update di `recognized` function, replace di whole content of di function wit dis one:

    ```python
    if args.result.reason == speech.ResultReason.TranslatedSpeech:
        language_match = next(l for l in args.result.translations if server_language.lower().startswith(l.lower()))
        text = args.result.translations[language_match]
        if (len(text) > 0):
            print(f'Translated text: {text}')
    
            message = Message(json.dumps({ 'speech': text }))
            device_client.send_message(message)
    ```

    Dis code dey check if di recognized event fire because dem translate di speech (dis event fit fire for oda times, like wen dem recognize di speech but dem no translate am). If dem translate di speech, e go find di translation for di `args.result.translations` dictionary wey match di server language.

    Di `args.result.translations` dictionary dey use di language part of di locale setting, no be di whole setting. Example, if you request translation into `fr-FR` for French, di dictionary go get entry for `fr`, no be `fr-FR`.

    Di translated text go then dey send go di IoT Hub.

1. Run dis code to test di translations. Make sure say your function app dey run, and request timer for di user language, either by talking dat language yourself, or using translation app.

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    ```

## Translate text wit di translator service

Di speech service no dey support translation of text back to speech, instead you fit use di Translator service to translate di text. Dis service get REST API wey you fit use to translate di text.

### Task - use di translator resource to translate text

1. Add di translator API key below di `speech_api_key`:

    ```python
    translator_api_key = '<key>'
    ```

    Replace `<key>` wit di API key for your translator service resource.

1. Above di `say` function, define `translate_text` function wey go translate text from di server language go di user language:

    ```python
    def translate_text(text):
    ```

1. Inside dis function, define di URL and headers for di REST API call:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    Di URL for dis API no dey location specific, instead di location dey pass as header. Di API key dey use directly, so e no be like di speech service wey you need to get access token from di token issuer API.

1. Below dis, define di parameters and body for di call:

    ```python
    params = {
        'from': server_language,
        'to': language
    }

    body = [{
        'text' : text
    }]
    ```

    Di `params` dey define di parameters wey dem go pass to di API call, passing di from and to languages. Dis call go translate text for di `from` language go di `to` language.

    Di `body` dey contain di text wey dem go translate. E be array, as plenty blocks of text fit dey translated for di same call.

1. Make di call to di REST API, and get di response:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    Di response wey go come back na JSON array, wit one item wey get di translations. Dis item get array for translations of all di items wey dem pass for di body.

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

1. Return di `test` property from di first translation from di first item for di array:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. Update di `say` function to translate di text wey dem go talk before di SSML dey generate:

    ```python
    print('Original:', text)
    text = translate_text(text)
    print('Translated:', text)
    ```

    Dis code dey also print di original and translated versions of di text for di console.

1. Run your code. Make sure say your function app dey run, and request timer for di user language, either by talking dat language yourself, or using translation app.

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

    > 💁 Because of di different ways wey people dey talk something for different languages, you fit get translations wey dey small different from di examples wey you give LUIS. If dis one happen, add more examples to LUIS, retrain am, then re-publish di model.

> 💁 You fit find dis code for di [code/virtual-iot-device](../../../../../6-consumer/lessons/4-multiple-language-support/code/virtual-iot-device) folder.

😀 Your multilingual timer program na success!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Disclaimer**:  
Dis dokyument don translate am wit AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). Even as we dey try make sure say e correct, abeg make you sabi say machine translation fit get mistake or no dey accurate well. Di original dokyument for im native language na di main correct source. For important information, e good make you use professional human translation. We no go fit take blame for any misunderstanding or wrong interpretation wey fit happen because you use dis translation.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->