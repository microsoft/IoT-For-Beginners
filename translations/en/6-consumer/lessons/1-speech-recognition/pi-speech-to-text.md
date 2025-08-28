<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "af249a24d4fe4f4de4806adbc3bc9d86",
  "translation_date": "2025-08-28T19:27:17+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-speech-to-text.md",
  "language_code": "en"
}
-->
# Speech to text - Raspberry Pi

In this part of the lesson, you will write code to convert speech from the captured audio into text using the speech service.

## Send the audio to the speech service

The audio can be sent to the speech service using the REST API. To use the speech service, you first need to request an access token, then use that token to access the REST API. These access tokens expire after 10 minutes, so your code should request them regularly to ensure they remain valid.

### Task - Get an access token

1. Open the `smart-timer` project on your Pi.

1. Remove the `play_audio` function. This is no longer needed since you don’t want the smart timer to repeat back what you said.

1. Add the following import to the top of the `app.py` file:

    ```python
    import requests
    ```

1. Add the following code above the `while True` loop to declare some settings for the speech service:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'
    ```

    Replace `<key>` with the API key for your speech service resource. Replace `<location>` with the location you used when you created the speech service resource.

    Replace `<language>` with the locale name for the language you will be speaking in, for example, `en-GB` for English or `zn-HK` for Cantonese. You can find a list of supported languages and their locale names in the [Language and voice support documentation on Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

1. Below this, add the following function to get an access token:

    ```python
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_api_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    This calls a token-issuing endpoint, passing the API key as a header. The call returns an access token that can be used to call the speech services.

1. Below this, declare a function to convert speech from the captured audio into text using the REST API:

    ```python
    def convert_speech_to_text(buffer):
    ```

1. Inside this function, set up the REST API URL and headers:

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

    This builds a URL using the location of the speech services resource. It then populates the headers with the access token from the `get_access_token` function, as well as the sample rate used to capture the audio. Finally, it defines some parameters to be passed with the URL, including the language of the audio.

1. Below this, add the following code to call the REST API and retrieve the text:

    ```python
    response = requests.post(url, headers=headers, params=params, data=buffer)
    response_json = response.json()

    if response_json['RecognitionStatus'] == 'Success':
        return response_json['DisplayText']
    else:
        return ''
    ```

    This calls the URL and decodes the JSON value returned in the response. The `RecognitionStatus` value in the response indicates whether the call successfully converted speech into text. If the status is `Success`, the text is returned from the function; otherwise, an empty string is returned.

1. Above the `while True:` loop, define a function to process the text returned from the speech-to-text service. For now, this function will simply print the text to the console.

    ```python
    def process_text(text):
        print(text)
    ```

1. Finally, replace the call to `play_audio` in the `while True` loop with a call to the `convert_speech_to_text` function, passing the text to the `process_text` function:

    ```python
    text = convert_speech_to_text(buffer)
    process_text(text)
    ```

1. Run the code. Press the button and speak into the microphone. Release the button when you are done, and the audio will be converted to text and printed to the console.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Hello world.
    Welcome to IoT for beginners.
    ```

    Try different types of sentences, including sentences where words sound the same but have different meanings. For example, if you are speaking in English, say, "I want to buy two bananas and an apple too," and notice how it uses the correct "to," "two," and "too" based on the context of the sentence, not just the sound of the words.

> 💁 You can find this code in the [code-speech-to-text/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/pi) folder.

😀 Your speech-to-text program was a success!

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we aim for accuracy, please note that automated translations may include errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is advised. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.