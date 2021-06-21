# Translate speech - Virtual IoT Device

In this part of the lesson, you will write code to translate speech when converting to text using the speech service, then translate text using the Translator service before generating a spoken response.

## Use the speech service to translate speech

The speech service can take speech and not only convert to text in the same language, but also translate the output to other languages.

### Task - use the speech service to translate speech

1. Open the `smart-timer` project in VS Code, and ensure the virtual environment is loaded in the terminal.

1. Add the following import statements below the existing imports:

    ```python
    from azure.cognitiveservices import speech
    from azure.cognitiveservices.speech.translation import SpeechTranslationConfig, TranslationRecognizer
    import requests
    ```

    This imports classes used to translate speech, and a `requests` library that will be used to make a call to the Translator service later in this lesson.

1. Your smart timer will have 2 languages set - the language of the server that was used to train LUIS, and the language spoken by the user. Update the `language` variable to be the language that will be spoken by the used, and add a new variable called `server_language` for the language used to train LUIS:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    Replace `<user language>` with the locale name for language you will be speaking in, for example `fr-FR` for French, or `zn-HK` for Cantonese.

    Replace `<server language>` with the locale name for language used to train LUIS.

    You can find a list of the supported languages and their locale names in the [Language and voice support documentation on Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 If you don't speak multiple languages you can use a service like [Bing Translate](https://www.bing.com/translator) or [Google Translate](https://translate.google.com) to translate from your preferred language to a language of your choice. These services can then play audio of the translated text. Be aware that the speech recognizer will ignore some audio output from your device, so you may need to use an additional device to play the translated text.
    >
    > For example, if you train LUIS in English, but want to use French as the user language, you can translate sentences like "set a 2 minute and 27 second timer" from English into French using Bing Translate, then use the **Listen translation** button to speak the translation into your microphone.
    >
    > ![The listen translation button on Bing translate](../../../images/bing-translate.png)

1. Replace the `recognizer_config` and `recognizer` declarations with the following:

    ```python
    translation_config = SpeechTranslationConfig(subscription=speech_api_key,
                                                 region=location,
                                                 speech_recognition_language=language,
                                                 target_languages=(language, server_language))
    
    recognizer = TranslationRecognizer(translation_config=translation_config)
    ```

    This creates a translation config to recognize speech in the user language, and create translations in the user and server language. It then uses this config to create a translation recognizer - a speech recognizer that can translate the output of the speech recognition into multiple languages.

    > 💁 The original language needs to be specified in the `target_languages`, otherwise you won't get any translations.

1. Update the `recognized` function, replacing the entire contents of the function with the following:

    ```python
    if args.result.reason == speech.ResultReason.TranslatedSpeech:
        language_match = next(l for l in args.result.translations if server_language.lower().startswith(l.lower()))
        text = args.result.translations[language_match]
        if (len(text) > 0):
            print(f'Translated text: {text}')
    
            message = Message(json.dumps({ 'speech': text }))
            device_client.send_message(message)
    ```

    This code checks to see if the recognized event was fired because speech was translated (this event can fire at other times, such as when the speech is recognized but not translated). If the speech was translated, it finds the translation in the `args.result.translations` dictionary that matches the server language.

    The `args.result.translations` dictionary is keyed off the language part of the locale setting, not the whole setting. For example, if you request a translation into `fr-FR` for French, the dictionary will contain an entry for `fr`, not `fr-FR`.

    The translated text is then sent to the IoT Hub.

1. Run this code to test the translations. Ensure your function app is running, and request a timer in the user language, either by speaking that language yourself, or using a translation app.

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    ```

## Translate text using the translator service

The speech service doesn't support translation pf text back to speech, instead you can use the Translator service to translate the text. This service has a REST API you can use to translate the text.

### Task - use the translator resource to translate text

1. Add the translator API key below the `speech_api_key`:

    ```python
    translator_api_key = '<key>'
    ```

    Replace `<key>` with the API key for your translator service resource.

1. Above the `say` function, define a `translate_text` function that will translate text from the server language to the user language:

    ```python
    def translate_text(text):
    ```

1. Inside this function, define the URL and headers for the REST API call:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    The URL for this API is not location specific, instead the location is passed in as a header. The API key is used directly, so unlike the speech service there is no need to get an access token from the token issuer API.

1. Below this define the parameters and body for the call:

    ```python
    params = {
        'from': server_language,
        'to': language
    }

    body = [{
        'text' : text
    }]
    ```

    The `params` defines the parameters to pass to the API call, passing the from and to languages. This call will translate text in the `from` language into the `to` language.

    The `body` contains the text to translate. This is an array, as multiple blocks of text can be translated in the same call.

1. Make the call the REST API, and get the response:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    The response that comes back is a JSON array, with one item that contains the translations. This item has an array for translations of all the items passed in the body.

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

1. Return the `test` property from the first translation from the first item in the array:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. Update the `say` function to translate the text to say before the SSML is generated:

    ```python
    print('Original:', text)
    text = translate_text(text)
    print('Translated:', text)
    ```

    This code also prints the original and translated versions of the text to the console.

1. Run your code. Ensure your function app is running, and request a timer in the user language, either by speaking that language yourself, or using a translation app.

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

    > 💁 Due to the different ways of saying something in different languages, you may get translations that are slightly different to the examples you gave LUIS. If this is the case, add more examples to LUIS, retrain then re-publish the model.

> 💁 You can find this code in the [code/virtual-iot-device](code/virtual-iot-device) folder.

😀 Your multi-lingual timer program was a success!
