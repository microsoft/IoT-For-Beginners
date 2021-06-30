# Text to speech - Raspberry Pi

In this part of the lesson, you will write code to convert text to speech using the speech service.

## Convert text to speech using the speech service

The text can be sent to the speech service using the REST API to get speech as an audio file that can be played back on your IoT device. When requesting speech, you need to provide the voice to use as speech can be generated using a variety of different voices.

Each language supports a range of different voices, and you can make a REST request against the speech service to get the list of supported voices for each language.

### Task - get a voice

1. Open the `smart-timer` project in VS Code.

1. Add the following code above the `say` function to request the list of voices for a language:

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

    This code defines a function called `get_voice` that uses the speech service to get a list of voices. It then finds the first voice that matches the language that is being used.

    This function is then called to store the first voice, and the voice name is printed to the console. This voice can be requested once and the value used for every call to convert text to speech.

    > 💁 You can get the full list of supported voices from the [Language and voice support documentation on Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). If you want to use a specific voice, then you can remove this function and hard code the voice to the voice name from this documentation. For example:
    >
    > ```python
    > voice = 'hi-IN-SwaraNeural'
    > ```

### Task - convert text to speech

1. Below this, define a constant for the audio format to be retrieved from the speech services. When you request audio, you can do it in a range of different formats.

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'
    ```

    The format you can use depends on your hardware. If you get `Invalid sample rate` errors when playing the audio then change this to another value. You can find the list of supported values in the [Text to speech REST API documentation on Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/rest-text-to-speech?WT.mc_id=academic-17441-jabenn#audio-outputs). You will need to use `riff` format audio, and the values to try are `riff-16khz-16bit-mono-pcm`, `riff-24khz-16bit-mono-pcm` and `riff-48khz-16bit-mono-pcm`.

1. Below this, declare a function called `get_speech` that will convert the text to speech using the speech service REST API:

    ```python
    def get_speech(text):
    ```

1. In the `get_speech` function, define the URL to call and the headers to pass:

    ```python
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    ```

    This set the headers to use a generated access token, set the content to SSML and define the audio format needed.

1. Below this, define the SSML to send to the REST API:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

    This SSML sets the language and the voice to use, along with the text to convert.

1. Finally, add code in this function to make the REST request and return the binary audio data:

    ```python
    response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    return io.BytesIO(response.content)
    ```

### Task - play the audio

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

    This code uses a PyAudio stream, the same as capturing audio. The difference here is the stream is set as an output stream, and data is read from the audio data and pushed to the stream.

    Rather than hard coding the stream details such as the sample rate, it is read from the audio data.

1. Replace the contents of the `say` function to the following:

    ```python
    speech = get_speech(text)
    play_speech(speech)
    ```

    This code converts the text to speech as binary audio data, and plays the audio.

1. Run the app, and ensure the function app is also running. Set some timers, and you will hear a spoken response saying that your timer has been set, then another spoken response when the timer is complete.

    If you get `Invalid sample rate` errors, change the `playback_format` as described above.

> 💁 You can find this code in the [code-spoken-response/pi](code-spoken-response/pi) folder.

😀 Your timer program was a success!
