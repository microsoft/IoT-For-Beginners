<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "606f3af1c78e3741e48ce77c31cea626",
  "translation_date": "2025-08-28T19:20:19+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/pi-text-to-speech.md",
  "language_code": "en"
}
-->
# Text to Speech - Raspberry Pi

In this part of the lesson, you will write code to convert text into speech using the speech service.

## Convert Text to Speech Using the Speech Service

You can send text to the speech service via the REST API to receive speech as an audio file, which can then be played on your IoT device. When requesting speech, you need to specify the voice to use, as speech can be generated with a variety of voices.

Each language supports a range of voices, and you can make a REST request to the speech service to retrieve the list of supported voices for each language.

### Task - Retrieve a Voice

1. Open the `smart-timer` project in VS Code.

1. Add the following code above the `say` function to request the list of voices for a specific language:

    ```python
    def get_voice():
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/voices/list'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token()
        }
    
        response = requests.get(url, headers=headers)
        voices_json = json.loads(response.text)
    
        first_voice = next(x for x in voices_json if x['Locale'].lower() == language.lower() and x['VoiceType'] == 'Neural')
        return first_voice['ShortName']
    
    voice = get_voice()
    print(f'Using voice {voice}')
    ```

    This code defines a function called `get_voice` that uses the speech service to retrieve a list of voices. It then finds the first voice that matches the language being used.

    This function is called to store the first voice, and the voice name is printed to the console. You can request this voice once and reuse the value for every call to convert text to speech.

    > 💁 You can find the full list of supported voices in the [Language and Voice Support documentation on Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). If you want to use a specific voice, you can remove this function and hard-code the voice name from the documentation. For example:
    >
    > ```python
    > voice = 'hi-IN-SwaraNeural'
    > ```

### Task - Convert Text to Speech

1. Below this, define a constant for the audio format to be retrieved from the speech service. When requesting audio, you can choose from a variety of formats.

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'
    ```

    The format you use depends on your hardware. If you encounter `Invalid sample rate` errors when playing the audio, try changing this to another value. You can find the list of supported values in the [Text to Speech REST API documentation on Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/rest-text-to-speech?WT.mc_id=academic-17441-jabenn#audio-outputs). You will need to use `riff` format audio, and the values to try are `riff-16khz-16bit-mono-pcm`, `riff-24khz-16bit-mono-pcm`, and `riff-48khz-16bit-mono-pcm`.

1. Below this, declare a function called `get_speech` that will convert text to speech using the speech service REST API:

    ```python
    def get_speech(text):
    ```

1. In the `get_speech` function, define the URL to call and the headers to include:

    ```python
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    ```

    This sets the headers to use a generated access token, specifies the content as SSML, and defines the desired audio format.

1. Below this, define the SSML to send to the REST API:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

    This SSML specifies the language and voice to use, along with the text to convert.

1. Finally, add code in this function to make the REST request and return the binary audio data:

    ```python
    response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    return io.BytesIO(response.content)
    ```

### Task - Play the Audio

1. Below the `get_speech` function, define a new function to play the audio returned by the REST API call:

    ```python
    def play_speech(speech):
    ```

1. The `speech` passed to this function will be the binary audio data returned from the REST API. Use the following code to open this as a wave file and pass it to PyAudio to play the audio:

    ```python
    def play_speech(speech):
        with wave.open(speech, 'rb') as wave_file:
            stream = audio.open(format=audio.get_format_from_width(wave_file.getsampwidth()),
                                channels=wave_file.getnchannels(),
                                rate=wave_file.getframerate(),
                                output_device_index=speaker_card_number,
                                output=True)

            data = wave_file.readframes(4096)

            while len(data) > 0:
                stream.write(data)
                data = wave_file.readframes(4096)

            stream.stop_stream()
            stream.close()
    ```

    This code uses a PyAudio stream, similar to capturing audio. The difference here is that the stream is set as an output stream, and data is read from the audio data and sent to the stream.

    Instead of hard-coding the stream details, such as the sample rate, these are read from the audio data.

1. Replace the contents of the `say` function with the following:

    ```python
    speech = get_speech(text)
    play_speech(speech)
    ```

    This code converts the text to speech as binary audio data and plays the audio.

1. Run the app, ensuring the function app is also running. Set some timers, and you will hear a spoken response confirming that your timer has been set, followed by another spoken response when the timer completes.

    If you encounter `Invalid sample rate` errors, adjust the `playback_format` as described above.

> 💁 You can find this code in the [code-spoken-response/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/pi) folder.

😀 Your timer program is a success!

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we aim for accuracy, please note that automated translations may include errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is advised. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.