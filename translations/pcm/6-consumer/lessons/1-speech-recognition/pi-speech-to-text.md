<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "af249a24d4fe4f4de4806adbc3bc9d86",
  "translation_date": "2025-11-18T19:27:30+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-speech-to-text.md",
  "language_code": "pcm"
}
-->
# Speech to text - Raspberry Pi

For dis part of di lesson, you go write code wey go change di speech wey dey di audio wey you capture to text using di speech service.

## Send di audio go di speech service

You fit send di audio go di speech service using di REST API. To use di speech service, first you go need request access token, then use dat token take access di REST API. Dis access tokens dey expire after 10 minutes, so your code suppose dey request dem regularly to make sure say dem dey always up to date.

### Task - get access token

1. Open di `smart-timer` project for your Pi.

1. Comot di `play_audio` function. You no need am again because you no want make di smart timer dey repeat wetin you talk.

1. Add dis import for di top of di `app.py` file:

    ```python
    import requests
    ```

1. Add dis code above di `while True` loop to set some settings for di speech service:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'
    ```

    Change `<key>` to di API key for your speech service resource. Change `<location>` to di location wey you use when you create di speech service resource.

    Change `<language>` to di locale name for di language wey you go dey speak, like `en-GB` for English, or `zn-HK` for Cantonese. You fit find list of di supported languages and dia locale names for di [Language and voice support documentation on Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

1. Under dis one, add dis function to get access token:

    ```python
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_api_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    Dis one dey call di token issuing endpoint, e dey pass di API key as header. Di call go return access token wey you fit use call di speech services.

1. Under dis one, declare function wey go change di speech wey dey di audio wey you capture to text using di REST API:

    ```python
    def convert_speech_to_text(buffer):
    ```

1. Inside dis function, set up di REST API URL and headers:

    ```python
    url = f'https://{location}.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1'

    headers = {
        'Authorization': 'Bearer ' + get_access_token(),
        'Content-Type': f'audio/wav; codecs=audio/pcm; samplerate={rate}',
        'Accept': 'application/json;text/xml'
    }

    params = {
        'language': language
    }
    ```

    Dis one dey build URL using di location of di speech services resource. E go then put di headers with di access token wey come from di `get_access_token` function, plus di sample rate wey dem use capture di audio. Finally, e go define some parameters wey go follow di URL wey dey contain di language wey dey di audio.

1. Under dis one, add dis code to call di REST API and get di text back:

    ```python
    response = requests.post(url, headers=headers, params=params, data=buffer)
    response_json = response.json()

    if response_json['RecognitionStatus'] == 'Success':
        return response_json['DisplayText']
    else:
        return ''
    ```

    Dis one dey call di URL and decode di JSON value wey dey di response. Di `RecognitionStatus` value wey dey di response go show if di call fit change di speech to text well, and if e be `Success`, di text go return from di function, but if e no be `Success`, e go return empty string.

1. Above di `while True:` loop, define function wey go process di text wey di speech to text service return. Dis function go just print di text for di console for now.

    ```python
    def process_text(text):
        print(text)
    ```

1. Finally, change di call to `play_audio` for di `while True` loop to call di `convert_speech_to_text` function, and pass di text to di `process_text` function:

    ```python
    text = convert_speech_to_text(buffer)
    process_text(text)
    ```

1. Run di code. Press di button and talk for di microphone. Release di button when you don finish, and di audio go change to text and e go print for di console.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Hello world.
    Welcome to IoT for beginners.
    ```

    Try different types of sentences, plus sentences wey words dey sound alike but get different meanings. For example, if you dey speak English, talk 'I want to buy two bananas and an apple too', and notice how e go use di correct to, two and too based on di context of di word, no be just di sound.

> 💁 You fit find dis code for di [code-speech-to-text/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/pi) folder.

😀 Your speech to text program work well!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Disclaimer**:  
Dis dokyument don use AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator) do di translation. Even as we dey try make am accurate, abeg sabi say automated translations fit get mistake or no dey correct well. Di original dokyument for im native language na di main source wey you go fit trust. For important information, e better make professional human translation dey use. We no go fit take blame for any misunderstanding or wrong interpretation wey fit happen because you use dis translation.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->