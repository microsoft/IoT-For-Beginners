<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "606f3af1c78e3741e48ce77c31cea626",
  "translation_date": "2025-08-27T13:54:08+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/pi-text-to-speech.md",
  "language_code": "pa"
}
-->
# ਟੈਕਸਟ ਤੋਂ ਬੋਲਣ - ਰਾਸਪਬੈਰੀ ਪਾਈ

ਇਸ ਪਾਠ ਦੇ ਇਸ ਹਿੱਸੇ ਵਿੱਚ, ਤੁਸੀਂ ਟੈਕਸਟ ਨੂੰ ਬੋਲਣ ਵਿੱਚ ਤਬਦੀਲ ਕਰਨ ਲਈ ਕੋਡ ਲਿਖੋਗੇ ਜੋ ਸਪੀਚ ਸਰਵਿਸ ਦੀ ਵਰਤੋਂ ਕਰਦਾ ਹੈ।

## ਸਪੀਚ ਸਰਵਿਸ ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਟੈਕਸਟ ਨੂੰ ਬੋਲਣ ਵਿੱਚ ਤਬਦੀਲ ਕਰੋ

ਟੈਕਸਟ ਨੂੰ REST API ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਸਪੀਚ ਸਰਵਿਸ ਨੂੰ ਭੇਜਿਆ ਜਾ ਸਕਦਾ ਹੈ ਤਾਂ ਜੋ ਆਡੀਓ ਫਾਈਲ ਦੇ ਰੂਪ ਵਿੱਚ ਸਪੀਚ ਪ੍ਰਾਪਤ ਕੀਤਾ ਜਾ ਸਕੇ, ਜਿਸਨੂੰ ਤੁਹਾਡੇ IoT ਡਿਵਾਈਸ 'ਤੇ ਚਲਾਇਆ ਜਾ ਸਕਦਾ ਹੈ। ਸਪੀਚ ਦੀ ਬੇਨਤੀ ਕਰਦੇ ਸਮੇਂ, ਤੁਹਾਨੂੰ ਵਰਤਣ ਲਈ ਆਵਾਜ਼ ਪ੍ਰਦਾਨ ਕਰਨੀ ਪਵੇਗੀ ਕਿਉਂਕਿ ਸਪੀਚ ਵੱਖ-ਵੱਖ ਆਵਾਜ਼ਾਂ ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਤਿਆਰ ਕੀਤਾ ਜਾ ਸਕਦਾ ਹੈ।

ਹਰ ਭਾਸ਼ਾ ਵੱਖ-ਵੱਖ ਆਵਾਜ਼ਾਂ ਦਾ ਸਮਰਥਨ ਕਰਦੀ ਹੈ, ਅਤੇ ਤੁਸੀਂ ਸਪੀਚ ਸਰਵਿਸ ਦੇ ਖਿਲਾਫ REST ਬੇਨਤੀ ਕਰਕੇ ਹਰ ਭਾਸ਼ਾ ਲਈ ਸਮਰਥਿਤ ਆਵਾਜ਼ਾਂ ਦੀ ਸੂਚੀ ਪ੍ਰਾਪਤ ਕਰ ਸਕਦੇ ਹੋ।

### ਕੰਮ - ਇੱਕ ਆਵਾਜ਼ ਪ੍ਰਾਪਤ ਕਰੋ

1. VS Code ਵਿੱਚ `smart-timer` ਪ੍ਰੋਜੈਕਟ ਖੋਲ੍ਹੋ।

1. ਭਾਸ਼ਾ ਲਈ ਆਵਾਜ਼ਾਂ ਦੀ ਸੂਚੀ ਦੀ ਬੇਨਤੀ ਕਰਨ ਲਈ `say` ਫੰਕਸ਼ਨ ਦੇ ਉੱਪਰ ਹੇਠਾਂ ਦਿੱਤਾ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ:

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

    ਇਹ ਕੋਡ `get_voice` ਨਾਮਕ ਇੱਕ ਫੰਕਸ਼ਨ ਨੂੰ ਪਰਿਭਾਸ਼ਿਤ ਕਰਦਾ ਹੈ ਜੋ ਸਪੀਚ ਸਰਵਿਸ ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਆਵਾਜ਼ਾਂ ਦੀ ਸੂਚੀ ਪ੍ਰਾਪਤ ਕਰਦਾ ਹੈ। ਇਹ ਫਿਰ ਪਹਿਲੀ ਆਵਾਜ਼ ਨੂੰ ਲੱਭਦਾ ਹੈ ਜੋ ਵਰਤ ਰਹੀ ਭਾਸ਼ਾ ਨਾਲ ਮੇਲ ਖਾਂਦੀ ਹੈ।

    ਇਹ ਫੰਕਸ਼ਨ ਫਿਰ ਪਹਿਲੀ ਆਵਾਜ਼ ਨੂੰ ਸਟੋਰ ਕਰਨ ਲਈ ਕਾਲ ਕੀਤਾ ਜਾਂਦਾ ਹੈ, ਅਤੇ ਆਵਾਜ਼ ਦਾ ਨਾਮ ਕੰਸੋਲ ਵਿੱਚ ਪ੍ਰਿੰਟ ਕੀਤਾ ਜਾਂਦਾ ਹੈ। ਇਹ ਆਵਾਜ਼ ਇੱਕ ਵਾਰ ਬੇਨਤੀ ਕੀਤੀ ਜਾ ਸਕਦੀ ਹੈ ਅਤੇ ਟੈਕਸਟ ਨੂੰ ਸਪੀਚ ਵਿੱਚ ਤਬਦੀਲ ਕਰਨ ਲਈ ਹਰ ਕਾਲ ਲਈ ਇਸਦੀ ਵੈਲਿਊ ਦੀ ਵਰਤੋਂ ਕੀਤੀ ਜਾ ਸਕਦੀ ਹੈ।

    > 💁 ਤੁਸੀਂ Microsoft Docs 'ਤੇ [Language and voice support documentation](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech) ਤੋਂ ਸਮਰਥਿਤ ਆਵਾਜ਼ਾਂ ਦੀ ਪੂਰੀ ਸੂਚੀ ਪ੍ਰਾਪਤ ਕਰ ਸਕਦੇ ਹੋ। ਜੇ ਤੁਸੀਂ ਕਿਸੇ ਵਿਸ਼ੇਸ਼ ਆਵਾਜ਼ ਦੀ ਵਰਤੋਂ ਕਰਨੀ ਚਾਹੁੰਦੇ ਹੋ, ਤਾਂ ਤੁਸੀਂ ਇਸ ਫੰਕਸ਼ਨ ਨੂੰ ਹਟਾ ਸਕਦੇ ਹੋ ਅਤੇ ਇਸ ਡੌਕੂਮੈਂਟੇਸ਼ਨ ਤੋਂ ਆਵਾਜ਼ ਦੇ ਨਾਮ ਨੂੰ ਹਾਰਡ ਕੋਡ ਕਰ ਸਕਦੇ ਹੋ। ਉਦਾਹਰਨ ਲਈ:
    >
    > ```python
    > voice = 'hi-IN-SwaraNeural'
    > ```

### ਕੰਮ - ਟੈਕਸਟ ਨੂੰ ਸਪੀਚ ਵਿੱਚ ਤਬਦੀਲ ਕਰੋ

1. ਇਸ ਤੋਂ ਹੇਠਾਂ, ਸਪੀਚ ਸਰਵਿਸ ਤੋਂ ਪ੍ਰਾਪਤ ਕੀਤੇ ਜਾਣ ਵਾਲੇ ਆਡੀਓ ਫਾਰਮੈਟ ਲਈ ਇੱਕ ਕਾਂਸਟੈਂਟ ਪਰਿਭਾਸ਼ਿਤ ਕਰੋ। ਜਦੋਂ ਤੁਸੀਂ ਆਡੀਓ ਦੀ ਬੇਨਤੀ ਕਰਦੇ ਹੋ, ਤਾਂ ਤੁਸੀਂ ਇਸਨੂੰ ਵੱਖ-ਵੱਖ ਫਾਰਮੈਟਾਂ ਵਿੱਚ ਕਰ ਸਕਦੇ ਹੋ।

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'
    ```

    ਤੁਹਾਡੇ ਹਾਰਡਵੇਅਰ 'ਤੇ ਨਿਰਭਰ ਕਰਦਾ ਹੈ ਕਿ ਤੁਸੀਂ ਕਿਹੜਾ ਫਾਰਮੈਟ ਵਰਤ ਸਕਦੇ ਹੋ। ਜੇ ਤੁਹਾਨੂੰ ਆਡੀਓ ਚਲਾਉਣ ਸਮੇਂ `Invalid sample rate` ਐਰਰ ਮਿਲਦੇ ਹਨ, ਤਾਂ ਇਸਨੂੰ ਕਿਸੇ ਹੋਰ ਵੈਲਿਊ ਵਿੱਚ ਬਦਲੋ। ਤੁਸੀਂ Microsoft Docs 'ਤੇ [Text to speech REST API documentation](https://docs.microsoft.com/azure/cognitive-services/speech-service/rest-text-to-speech?WT.mc_id=academic-17441-jabenn#audio-outputs) ਵਿੱਚ ਸਮਰਥਿਤ ਵੈਲਿਊਜ਼ ਦੀ ਸੂਚੀ ਪ੍ਰਾਪਤ ਕਰ ਸਕਦੇ ਹੋ। ਤੁਹਾਨੂੰ `riff` ਫਾਰਮੈਟ ਆਡੀਓ ਦੀ ਵਰਤੋਂ ਕਰਨ ਦੀ ਲੋੜ ਹੋਵੇਗੀ, ਅਤੇ ਕੋਸ਼ਿਸ਼ ਕਰਨ ਲਈ ਵੈਲਿਊਜ਼ ਹਨ `riff-16khz-16bit-mono-pcm`, `riff-24khz-16bit-mono-pcm` ਅਤੇ `riff-48khz-16bit-mono-pcm`।

1. ਇਸ ਤੋਂ ਹੇਠਾਂ, `get_speech` ਨਾਮਕ ਇੱਕ ਫੰਕਸ਼ਨ ਘੋਸ਼ਿਤ ਕਰੋ ਜੋ ਸਪੀਚ ਸਰਵਿਸ REST API ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਟੈਕਸਟ ਨੂੰ ਸਪੀਚ ਵਿੱਚ ਤਬਦੀਲ ਕਰੇਗਾ:

    ```python
    def get_speech(text):
    ```

1. `get_speech` ਫੰਕਸ਼ਨ ਵਿੱਚ, ਕਾਲ ਕਰਨ ਲਈ URL ਅਤੇ ਪਾਸ ਕਰਨ ਲਈ ਹੈਡਰ ਪਰਿਭਾਸ਼ਿਤ ਕਰੋ:

    ```python
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    ```

    ਇਹ ਹੈਡਰ ਨੂੰ ਇੱਕ ਜਨਰੇਟ ਕੀਤੇ ਐਕਸੈਸ ਟੋਕਨ ਦੀ ਵਰਤੋਂ ਕਰਨ ਲਈ ਸੈਟ ਕਰਦਾ ਹੈ, ਸਮੱਗਰੀ ਨੂੰ SSML ਵਿੱਚ ਸੈਟ ਕਰਦਾ ਹੈ ਅਤੇ ਲੋੜੀਂਦੇ ਆਡੀਓ ਫਾਰਮੈਟ ਨੂੰ ਪਰਿਭਾਸ਼ਿਤ ਕਰਦਾ ਹੈ।

1. ਇਸ ਤੋਂ ਹੇਠਾਂ, REST API ਨੂੰ ਭੇਜਣ ਲਈ SSML ਪਰਿਭਾਸ਼ਿਤ ਕਰੋ:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

    ਇਹ SSML ਭਾਸ਼ਾ ਅਤੇ ਵਰਤਣ ਲਈ ਆਵਾਜ਼ ਨੂੰ ਸੈਟ ਕਰਦਾ ਹੈ, ਨਾਲ ਹੀ ਤਬਦੀਲ ਕਰਨ ਲਈ ਟੈਕਸਟ।

1. ਆਖਿਰ ਵਿੱਚ, ਇਸ ਫੰਕਸ਼ਨ ਵਿੱਚ REST ਬੇਨਤੀ ਕਰਨ ਅਤੇ ਬਾਈਨਰੀ ਆਡੀਓ ਡੇਟਾ ਵਾਪਸ ਕਰਨ ਲਈ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ:

    ```python
    response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    return io.BytesIO(response.content)
    ```

### ਕੰਮ - ਆਡੀਓ ਚਲਾਓ

1. `get_speech` ਫੰਕਸ਼ਨ ਦੇ ਹੇਠਾਂ, REST API ਕਾਲ ਦੁਆਰਾ ਵਾਪਸ ਕੀਤੇ ਆਡੀਓ ਨੂੰ ਚਲਾਉਣ ਲਈ ਇੱਕ ਨਵਾਂ ਫੰਕਸ਼ਨ ਪਰਿਭਾਸ਼ਿਤ ਕਰੋ:

    ```python
    def play_speech(speech):
    ```

1. ਇਸ ਫੰਕਸ਼ਨ ਨੂੰ ਦਿੱਤਾ `speech` REST API ਤੋਂ ਵਾਪਸ ਕੀਤੇ ਬਾਈਨਰੀ ਆਡੀਓ ਡੇਟਾ ਹੋਵੇਗਾ। ਇਸਨੂੰ ਇੱਕ ਵੇਵ ਫਾਈਲ ਵਜੋਂ ਖੋਲ੍ਹਣ ਅਤੇ PyAudio ਨੂੰ ਆਡੀਓ ਚਲਾਉਣ ਲਈ ਹੇਠਾਂ ਦਿੱਤੇ ਕੋਡ ਦੀ ਵਰਤੋਂ ਕਰੋ:

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

    ਇਹ ਕੋਡ PyAudio ਸਟ੍ਰੀਮ ਦੀ ਵਰਤੋਂ ਕਰਦਾ ਹੈ, ਜਿਵੇਂ ਆਡੀਓ ਕੈਪਚਰ ਕਰਦੇ ਸਮੇਂ। ਫਰਕ ਇਹ ਹੈ ਕਿ ਸਟ੍ਰੀਮ ਨੂੰ ਆਉਟਪੁੱਟ ਸਟ੍ਰੀਮ ਵਜੋਂ ਸੈਟ ਕੀਤਾ ਜਾਂਦਾ ਹੈ, ਅਤੇ ਆਡੀਓ ਡੇਟਾ ਤੋਂ ਡੇਟਾ ਪੜ੍ਹਿਆ ਜਾਂਦਾ ਹੈ ਅਤੇ ਸਟ੍ਰੀਮ ਵਿੱਚ ਧੱਕਿਆ ਜਾਂਦਾ ਹੈ।

    ਸਟ੍ਰੀਮ ਵੇਰਵੇ ਜਿਵੇਂ ਸੈਂਪਲ ਰੇਟ ਨੂੰ ਹਾਰਡ ਕੋਡ ਕਰਨ ਦੀ ਬਜਾਏ, ਇਹ ਆਡੀਓ ਡੇਟਾ ਤੋਂ ਪੜ੍ਹਿਆ ਜਾਂਦਾ ਹੈ।

1. `say` ਫੰਕਸ਼ਨ ਦੀ ਸਮੱਗਰੀ ਨੂੰ ਹੇਠਾਂ ਦਿੱਤੇ ਨਾਲ ਬਦਲੋ:

    ```python
    speech = get_speech(text)
    play_speech(speech)
    ```

    ਇਹ ਕੋਡ ਟੈਕਸਟ ਨੂੰ ਸਪੀਚ ਵਜੋਂ ਬਾਈਨਰੀ ਆਡੀਓ ਡੇਟਾ ਵਿੱਚ ਤਬਦੀਲ ਕਰਦਾ ਹੈ, ਅਤੇ ਆਡੀਓ ਚਲਾਉਂਦਾ ਹੈ।

1. ਐਪ ਚਲਾਓ, ਅਤੇ ਯਕੀਨੀ ਬਣਾਓ ਕਿ ਫੰਕਸ਼ਨ ਐਪ ਵੀ ਚਲ ਰਹੀ ਹੈ। ਕੁਝ ਟਾਈਮਰ ਸੈਟ ਕਰੋ, ਅਤੇ ਤੁਸੀਂ ਇੱਕ ਬੋਲੀ ਗਈ ਪ੍ਰਤੀਕ੍ਰਿਆ ਸੁਣੋਗੇ ਜੋ ਕਹੇਗੀ ਕਿ ਤੁਹਾਡਾ ਟਾਈਮਰ ਸੈਟ ਕੀਤਾ ਗਿਆ ਹੈ, ਫਿਰ ਟਾਈਮਰ ਪੂਰਾ ਹੋਣ 'ਤੇ ਇੱਕ ਹੋਰ ਬੋਲੀ ਗਈ ਪ੍ਰਤੀਕ੍ਰਿਆ।

    ਜੇ ਤੁਹਾਨੂੰ `Invalid sample rate` ਐਰਰ ਮਿਲਦੇ ਹਨ, ਤਾਂ `playback_format` ਨੂੰ ਉਪਰੋਕਤ ਵਰਣਨ ਅਨੁਸਾਰ ਬਦਲੋ।

> 💁 ਤੁਸੀਂ ਇਹ ਕੋਡ [code-spoken-response/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/pi) ਫੋਲਡਰ ਵਿੱਚ ਪ੍ਰਾਪਤ ਕਰ ਸਕਦੇ ਹੋ।

😀 ਤੁਹਾਡਾ ਟਾਈਮਰ ਪ੍ਰੋਗਰਾਮ ਸਫਲ ਰਿਹਾ!

---

**ਅਸਵੀਕਰਤੀ**:  
ਇਹ ਦਸਤਾਵੇਜ਼ AI ਅਨੁਵਾਦ ਸੇਵਾ [Co-op Translator](https://github.com/Azure/co-op-translator) ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਅਨੁਵਾਦ ਕੀਤਾ ਗਿਆ ਹੈ। ਜਦੋਂ ਕਿ ਅਸੀਂ ਸਹੀਤਾ ਲਈ ਯਤਨਸ਼ੀਲ ਹਾਂ, ਕਿਰਪਾ ਕਰਕੇ ਧਿਆਨ ਦਿਓ ਕਿ ਸਵੈਚਾਲਿਤ ਅਨੁਵਾਦਾਂ ਵਿੱਚ ਗਲਤੀਆਂ ਜਾਂ ਅਸੁਚਨਾਵਾਂ ਹੋ ਸਕਦੀਆਂ ਹਨ। ਮੂਲ ਦਸਤਾਵੇਜ਼ ਨੂੰ ਇਸਦੀ ਮੂਲ ਭਾਸ਼ਾ ਵਿੱਚ ਅਧਿਕਾਰਤ ਸਰੋਤ ਮੰਨਿਆ ਜਾਣਾ ਚਾਹੀਦਾ ਹੈ। ਮਹੱਤਵਪੂਰਨ ਜਾਣਕਾਰੀ ਲਈ, ਪੇਸ਼ੇਵਰ ਮਨੁੱਖੀ ਅਨੁਵਾਦ ਦੀ ਸਿਫਾਰਸ਼ ਕੀਤੀ ਜਾਂਦੀ ਹੈ। ਇਸ ਅਨੁਵਾਦ ਦੀ ਵਰਤੋਂ ਤੋਂ ਪੈਦਾ ਹੋਣ ਵਾਲੇ ਕਿਸੇ ਵੀ ਗਲਤਫਹਿਮੀ ਜਾਂ ਗਲਤ ਵਿਆਖਿਆ ਲਈ ਅਸੀਂ ਜ਼ਿੰਮੇਵਾਰ ਨਹੀਂ ਹਾਂ।