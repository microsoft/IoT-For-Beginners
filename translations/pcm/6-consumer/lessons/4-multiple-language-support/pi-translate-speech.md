<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "bbb5aa34221fe129dd3ce4d9ec33831a",
  "translation_date": "2025-11-18T19:22:19+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/pi-translate-speech.md",
  "language_code": "pcm"
}
-->
# Translate speech - Raspberry Pi

For dis part of di lesson, you go write code wey go translate text using di translator service.

## Change text to speech using di translator service

Di speech service REST API no dey support direct translations, but you fit use di Translator service to translate di text wey di speech to text service generate, and di text wey di spoken response get. Dis service get REST API wey you fit use to translate di text.

### Task - use di translator resource to translate text

1. Your smart timer go get 2 languages set - di language of di server wey dem use train LUIS (di same language dem use build di messages wey go talk to di user), and di language wey di user dey speak. Update di `language` variable to be di language wey di user go dey speak, and add new variable wey dem call `server_language` for di language wey dem use train LUIS:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    Change `<user language>` to di locale name for di language wey you go dey speak, like `fr-FR` for French, or `zn-HK` for Cantonese.

    Change `<server language>` to di locale name for di language wey dem use train LUIS.

    You fit find list of di supported languages and dia locale names for di [Language and voice support documentation on Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 If you no sabi speak plenty languages, you fit use service like [Bing Translate](https://www.bing.com/translator) or [Google Translate](https://translate.google.com) to translate from di language wey you sabi to di language wey you choose. Dis services fit play audio of di translated text.
    >
    > Example, if you train LUIS for English, but you wan use French as di user language, you fit translate sentences like "set a 2 minute and 27 second timer" from English go French using Bing Translate, then use di **Listen translation** button to talk di translation into your microphone.
    >
    > ![Di listen translation button for Bing translate](../../../../../translated_images/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.pcm.png)

1. Add di translator API key under di `speech_api_key`:

    ```python
    translator_api_key = '<key>'
    ```

    Change `<key>` to di API key for your translator service resource.

1. For di top of di `say` function, define one `translate_text` function wey go translate text from di server language go di user language:

    ```python
    def translate_text(text, from_language, to_language):
    ```

    Di from and to languages go dey pass to dis function - your app go need convert from user language go server language when e dey recognize speech, and from server language go user language when e dey provide spoken feedback.

1. Inside dis function, define di URL and headers for di REST API call:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    Di URL for dis API no dey location specific, instead di location dey pass as header. Di API key dey use directly, so e no be like di speech service wey need to get access token from di token issuer API.

1. Under dis, define di parameters and body for di call:

    ```python
    params = {
        'from': from_language,
        'to': to_language
    }

    body = [{
        'text' : text
    }]
    ```

    Di `params` dey define di parameters wey go pass to di API call, e dey pass di from and to languages. Dis call go translate text for di `from` language go di `to` language.

    Di `body` dey contain di text wey dem wan translate. E be array, as e fit translate plenty blocks of text for di same call.

1. Make di call to di REST API, and get di response:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    Di response wey go come back na JSON array, wey get one item wey contain di translations. Dis item get array for translations of all di items wey dem pass for di body.

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

1. Return di `test` property from di first translation from di first item for di array:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. Update di `while True` loop to translate di text from di call to `convert_speech_to_text` from di user language go di server language:

    ```python
    if len(text) > 0:
        print('Original:', text)
        text = translate_text(text, language, server_language)
        print('Translated:', text)

        message = Message(json.dumps({ 'speech': text }))
        device_client.send_message(message)
    ```

    Dis code dey also print di original and translated versions of di text for di console.

1. Update di `say` function to translate di text wey e go talk from di server language go di user language:

    ```python
    def say(text):
        print('Original:', text)
        text = translate_text(text, server_language, language)
        print('Translated:', text)
        speech = get_speech(text)
        play_speech(speech)
    ```

    Dis code dey also print di original and translated versions of di text for di console.

1. Run your code. Make sure say your function app dey run, and request timer for di user language, either by speaking dat language yourself, or using translation app.

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

    > 💁 Because of di different ways wey people dey take talk something for different languages, you fit get translations wey dey small different from di examples wey you give LUIS. If e be like dat, add more examples to LUIS, retrain then re-publish di model.

> 💁 You fit find dis code for di [code/pi](../../../../../6-consumer/lessons/4-multiple-language-support/code/pi) folder.

😀 Your multilingual timer program work well!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Disclaimer**:  
Dis dokyument don use AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator) do di translation. Even as we dey try make am correct, abeg make you sabi say machine translation fit get mistake or no dey accurate well. Di original dokyument wey dey for di native language na di main source wey you go trust. For important mata, e good make professional human translation dey use. We no go fit take blame for any misunderstanding or wrong interpretation wey fit happen because you use dis translation.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->