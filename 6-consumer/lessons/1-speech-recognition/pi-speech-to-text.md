# Speech to text - Raspberry Pi

In this part of the lesson, you will write code to convert speech in the captured audio to text using the speech service.

## Send the audio to the speech service

The audio can be sent to the speech service using the REST API. To use the speech service, first you need to request an access token, then use that token to access the REST API. These access tokens expire after 10 minutes, so your code should request them on a regular basis to ensure they are always up to date.

### Task - get an access token

1. Open the `smart-timer` project on your Pi.

1. Remove the `play_audio` function. This is no longer needed as you don't want a smart timer to repeat back to you what you said.

1. Add the following imports to the top of the `app.py` file:

    ```python
    import requests
    import json
    ```

1. Add the following code above the `while True` loop to declare some settings for the speech service:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'
    ```

    Replace `<key>` with the API key for your speech service resource. Replace `<location>` with the location you used when you created the speech service resource.

    Replace `<language>` with the locale name for language you will be speaking in, for example `en-GB` for English, or `zn-HK` for Cantonese. You can find a list of the supported languages and their locale names in the [Language and voice support documentation on Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

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

    This calls a token issuing endpoint, passing the API key as a header. This call returns an access token that can be used to call the speech services.

1. Below this, declare a function to convert speech in the captured audio to text using the REST API:

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

    This builds a URL using the location of the speech services resource. It then populates the headers with the access token from the `get_access_token` function, as well as the sample rate used to capture the audio. Finally it defines some parameters to be passed with the URL containing the language in the audio.

1. Below this, add the following code to call the REST API and get back the text:

    ```python
    response = requests.post(url, headers=headers, params=params, data=buffer)
    response_json = json.loads(response.text)

    if response_json['RecognitionStatus'] == 'Success':
        return response_json['DisplayText']
    else:
        return ''
    ```

    This calls the URL and decodes the JSON value that comes in the response. The `RecognitionStatus` value in the response indicates if the call was able to extract speech into text successfully, and if this is `Success` then the text is returned from the function, otherwise an empty string is returned.

1. Finally replace the call to `play_audio` in the `while True` loop with a call to the `convert_speech_to_text` function, as well as printing the text to the console:

    ```python
    text = convert_speech_to_text(buffer)
    print(text)
    ```

1. Run the code. Press the button and speak into the microphone. Release the button when you are done, and the audio will be converted to text and printed to the console.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Hello world.
    Welcome to IoT for beginners.
    ```

    Try different types of sentences, along with sentences where words sound the same but have different meanings. For example, if you are speaking in English, say 'I want to buy two bananas and an apple too', and notice how it will use the correct to, two and too based on the context of the word, not just it's sound.

> 💁 You can find this code in the [code-speech-to-text/pi](code-speech-to-text/pi) folder.

😀 Your speech to text program was a success!
