<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "606f3af1c78e3741e48ce77c31cea626",
  "translation_date": "2025-11-18T19:15:05+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/pi-text-to-speech.md",
  "language_code": "pcm"
}
-->
# Text to speech - Raspberry Pi

For dis part of di lesson, you go write code wey go change text to speech using di speech service.

## Change text to speech using di speech service

You fit send di text go di speech service using di REST API to get speech as audio file wey you fit play for your IoT device. Wen you dey request speech, you go need provide di voice wey you wan use because speech fit dey generate with different voices.

Each language get different voices wey e support, and you fit make REST request to di speech service to get di list of voices wey dey available for each language.

### Task - get voice

1. Open di `smart-timer` project for VS Code.

1. Add dis code above di `say` function to request di list of voices for one language:

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

    Dis code dey define one function wey dem call `get_voice` wey dey use di speech service to get list of voices. E go then find di first voice wey match di language wey you dey use.

    Dis function go then dey call to store di first voice, and di voice name go show for di console. You fit request dis voice once and use di value for every call to change text to speech.

    > 💁 You fit get di full list of voices wey dem support from di [Language and voice support documentation for Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). If you wan use one specific voice, you fit remove dis function and just put di voice name from di documentation. Example:
    >
    > ```python
    > voice = 'hi-IN-SwaraNeural'
    > ```

### Task - change text to speech

1. After dis, define one constant for di audio format wey you go collect from di speech services. Wen you dey request audio, you fit do am for different formats.

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'
    ```

    Di format wey you fit use go depend on your hardware. If you dey get `Invalid sample rate` errors wen you dey play di audio, change am to another value. You fit find di list of values wey dem support for di [Text to speech REST API documentation for Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/rest-text-to-speech?WT.mc_id=academic-17441-jabenn#audio-outputs). You go need use `riff` format audio, and di values wey you fit try na `riff-16khz-16bit-mono-pcm`, `riff-24khz-16bit-mono-pcm` and `riff-48khz-16bit-mono-pcm`.

1. After dis, declare one function wey dem call `get_speech` wey go change di text to speech using di speech service REST API:

    ```python
    def get_speech(text):
    ```

1. For di `get_speech` function, define di URL wey you go call and di headers wey you go pass:

    ```python
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    ```

    Dis one dey set di headers to use one generated access token, set di content to SSML and define di audio format wey you need.

1. After dis, define di SSML wey you go send go di REST API:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

    Dis SSML dey set di language and di voice wey you go use, plus di text wey you wan change.

1. Finally, add code for dis function to make di REST request and return di binary audio data:

    ```python
    response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    return io.BytesIO(response.content)
    ```

### Task - play di audio

1. After di `get_speech` function, define one new function to play di audio wey di REST API call return:

    ```python
    def play_speech(speech):
    ```

1. Di `speech` wey you pass go dis function na di binary audio data wey di REST API return. Use dis code to open am as wave file and pass am to PyAudio to play di audio:

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

    Dis code dey use PyAudio stream, di same way wey e dey capture audio. Di difference na say di stream dey set as output stream, and data dey read from di audio data and e dey push go di stream.

    Instead of hard coding di stream details like di sample rate, e dey read am from di audio data.

1. Change di contents of di `say` function to dis one:

    ```python
    speech = get_speech(text)
    play_speech(speech)
    ```

    Dis code dey change di text to speech as binary audio data, and e dey play di audio.

1. Run di app, and make sure say di function app dey run too. Set some timers, and you go hear one voice wey go talk say your timer don set, then another voice wey go talk wen di timer don finish.

    If you dey get `Invalid sample rate` errors, change di `playback_format` as we don talk before.

> 💁 You fit find dis code for di [code-spoken-response/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/pi) folder.

😀 Your timer program don work well!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Disclaimer**:  
Dis dokyument don bin translet wit AI translet service [Co-op Translator](https://github.com/Azure/co-op-translator). Even as we dey try make am correct, abeg make you sabi say AI translet fit get mistake or no dey accurate well. Di original dokyument for im native language na di one wey you go take as di correct source. For important mata, e good make you use professional human translet. We no go fit take blame for any misunderstanding or wrong interpretation wey fit happen because you use dis translet.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->