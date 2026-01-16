<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d620a470d9dd8614d99824832978360a",
  "translation_date": "2025-08-28T19:33:20+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/virtual-device-translate-speech.md",
  "language_code": "en"
}
-->
# Translate speech - Virtual IoT Device

In this part of the lesson, you will write code to translate speech into text using the speech service, then translate the text using the Translator service before generating a spoken response.

## Use the speech service to translate speech

The speech service can process speech and not only convert it into text in the same language but also translate the output into other languages.

### Task - use the speech service to translate speech

1. Open the `smart-timer` project in VS Code, and ensure the virtual environment is activated in the terminal.

1. Add the following import statements below the existing imports:

    ```python
    from azure.cognitiveservices import speech
    from azure.cognitiveservices.speech.translation import SpeechTranslationConfig, TranslationRecognizer
    import requests
    ```

    These imports include classes used for speech translation and the `requests` library, which will be used later in this lesson to make a call to the Translator service.

1. Your smart timer will have two languages set: the language of the server used to train LUIS (this same language is also used to build the messages spoken to the user) and the language spoken by the user. Update the `language` variable to reflect the language spoken by the user, and add a new variable called `server_language` for the language used to train LUIS:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    Replace `<user language>` with the locale name for the language you will be speaking, such as `fr-FR` for French or `zn-HK` for Cantonese.

    Replace `<server language>` with the locale name for the language used to train LUIS.

    You can find a list of supported languages and their locale names in the [Language and voice support documentation on Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 If you don't speak multiple languages, you can use a service like [Bing Translate](https://www.bing.com/translator) or [Google Translate](https://translate.google.com) to translate from your preferred language into another language. These services can also play audio of the translated text. Note that the speech recognizer may ignore some audio output from your device, so you might need to use an additional device to play the translated text.
    >
    > For example, if you train LUIS in English but want to use French as the user language, you can translate sentences like "set a 2 minute and 27 second timer" from English into French using Bing Translate, then use the **Listen translation** button to speak the translation into your microphone.
    >
    > ![The listen translation button on Bing translate](../../../../../translated_images/en/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. Replace the `recognizer_config` and `recognizer` declarations with the following:

    ```python
    translation_config = SpeechTranslationConfig(subscription=speech_api_key,
                                                 region=location,
                                                 speech_recognition_language=language,
                                                 target_languages=(language, server_language))
    
    recognizer = TranslationRecognizer(translation_config=translation_config)
    ```

    This creates a translation configuration to recognize speech in the user language and generate translations in both the user and server languages. It then uses this configuration to create a translation recognizer—a speech recognizer that can translate the output of speech recognition into multiple languages.

    > 💁 The original language must be included in the `target_languages`; otherwise, no translations will be generated.

1. Update the `recognized` function by replacing its entire contents with the following:

    ```python
    if args.result.reason == speech.ResultReason.TranslatedSpeech:
        language_match = next(l for l in args.result.translations if server_language.lower().startswith(l.lower()))
        text = args.result.translations[language_match]
        if (len(text) > 0):
            print(f'Translated text: {text}')
    
            message = Message(json.dumps({ 'speech': text }))
            device_client.send_message(message)
    ```

    This code checks whether the recognized event was triggered because speech was translated (this event can also be triggered when speech is recognized but not translated). If the speech was translated, it retrieves the translation from the `args.result.translations` dictionary that matches the server language.

    The `args.result.translations` dictionary uses the language part of the locale setting as its key, not the full setting. For example, if you request a translation into `fr-FR` for French, the dictionary will contain an entry for `fr`, not `fr-FR`.

    The translated text is then sent to the IoT Hub.

1. Run this code to test the translations. Ensure your function app is running, and request a timer in the user language, either by speaking that language yourself or using a translation app.

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    ```

## Translate text using the translator service

The speech service does not support translating text back into speech. Instead, you can use the Translator service to translate the text. This service provides a REST API for text translation.

### Task - use the translator resource to translate text

1. Add the Translator API key below the `speech_api_key`:

    ```python
    translator_api_key = '<key>'
    ```

    Replace `<key>` with the API key for your Translator service resource.

1. Above the `say` function, define a `translate_text` function to translate text from the server language to the user language:

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

    The URL for this API is not location-specific; instead, the location is passed as a header. The API key is used directly, so unlike the speech service, there is no need to obtain an access token from the token issuer API.

1. Below this, define the parameters and body for the call:

    ```python
    params = {
        'from': server_language,
        'to': language
    }

    body = [{
        'text' : text
    }]
    ```

    The `params` specify the parameters for the API call, including the source (`from`) and target (`to`) languages. This call translates text from the `from` language into the `to` language.

    The `body` contains the text to be translated. It is an array, as multiple blocks of text can be translated in a single call.

1. Make the REST API call and retrieve the response:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    The response is a JSON array containing one item with the translations. This item includes an array of translations for all the text blocks passed in the body.

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

1. Return the `text` property from the first translation in the first item of the array:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. Update the `say` function to translate the text before generating the SSML:

    ```python
    print('Original:', text)
    text = translate_text(text)
    print('Translated:', text)
    ```

    This code also prints both the original and translated versions of the text to the console.

1. Run your code. Ensure your function app is running, and request a timer in the user language, either by speaking that language yourself or using a translation app.

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

    > 💁 Different languages may express the same idea in slightly different ways, so the translations might not match the examples you provided to LUIS exactly. If this happens, add more examples to LUIS, retrain the model, and re-publish it.

> 💁 You can find this code in the [code/virtual-iot-device](../../../../../6-consumer/lessons/4-multiple-language-support/code/virtual-iot-device) folder.

😀 Your multilingual timer program was a success!

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we aim for accuracy, please note that automated translations may include errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is advised. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.