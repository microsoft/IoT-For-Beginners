<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "af249a24d4fe4f4de4806adbc3bc9d86",
  "translation_date": "2025-08-27T14:23:38+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-speech-to-text.md",
  "language_code": "pa"
}
-->
# ਸਪੀਚ ਤੋਂ ਟੈਕਸਟ - ਰਾਸਪਬੈਰੀ ਪਾਈ

ਇਸ ਪਾਠ ਦੇ ਇਸ ਹਿੱਸੇ ਵਿੱਚ, ਤੁਸੀਂ ਕੋਡ ਲਿਖੋਗੇ ਜੋ ਕੈਪਚਰ ਕੀਤੇ ਗਏ ਆਡੀਓ ਵਿੱਚ ਬੋਲੀ ਨੂੰ ਟੈਕਸਟ ਵਿੱਚ ਬਦਲਣ ਲਈ ਸਪੀਚ ਸਰਵਿਸ ਦੀ ਵਰਤੋਂ ਕਰੇਗਾ।

## ਆਡੀਓ ਨੂੰ ਸਪੀਚ ਸਰਵਿਸ ਨੂੰ ਭੇਜੋ

ਆਡੀਓ ਨੂੰ ਸਪੀਚ ਸਰਵਿਸ ਨੂੰ REST API ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਭੇਜਿਆ ਜਾ ਸਕਦਾ ਹੈ। ਸਪੀਚ ਸਰਵਿਸ ਦੀ ਵਰਤੋਂ ਕਰਨ ਲਈ, ਸਭ ਤੋਂ ਪਹਿਲਾਂ ਤੁਹਾਨੂੰ ਇੱਕ ਐਕਸੈਸ ਟੋਕਨ ਦੀ ਬੇਨਤੀ ਕਰਨੀ ਪਵੇਗੀ, ਫਿਰ ਉਸ ਟੋਕਨ ਦੀ ਵਰਤੋਂ ਕਰਕੇ REST API ਤੱਕ ਪਹੁੰਚ ਕੀਤੀ ਜਾ ਸਕਦੀ ਹੈ। ਇਹ ਐਕਸੈਸ ਟੋਕਨ 10 ਮਿੰਟਾਂ ਬਾਅਦ ਮਿਆਦ ਪੂਰੀ ਕਰ ਲੈਂਦੇ ਹਨ, ਇਸ ਲਈ ਤੁਹਾਡੇ ਕੋਡ ਨੂੰ ਇਹ ਯਕੀਨੀ ਬਣਾਉਣ ਲਈ ਨਿਯਮਿਤ ਤੌਰ 'ਤੇ ਇਹਨਾਂ ਦੀ ਬੇਨਤੀ ਕਰਨੀ ਚਾਹੀਦੀ ਹੈ ਕਿ ਇਹ ਹਮੇਸ਼ਾ ਅਪਡੇਟ ਰਹੇ।

### ਕੰਮ - ਐਕਸੈਸ ਟੋਕਨ ਪ੍ਰਾਪਤ ਕਰੋ

1. ਆਪਣੇ Pi 'ਤੇ `smart-timer` ਪ੍ਰੋਜੈਕਟ ਖੋਲ੍ਹੋ।

1. `play_audio` ਫੰਕਸ਼ਨ ਨੂੰ ਹਟਾਓ। ਇਹ ਹੁਣ ਲੋੜੀਂਦਾ ਨਹੀਂ ਹੈ ਕਿਉਂਕਿ ਤੁਸੀਂ ਨਹੀਂ ਚਾਹੁੰਦੇ ਕਿ ਸਮਾਰਟ ਟਾਈਮਰ ਤੁਹਾਡੇ ਕਹੇ ਨੂੰ ਦੁਹਰਾਏ।

1. `app.py` ਫਾਈਲ ਦੇ ਸਿਰੇ 'ਤੇ ਹੇਠਾਂ ਦਿੱਤਾ ਗਿਆ ਇਮਪੋਰਟ ਸ਼ਾਮਲ ਕਰੋ:

    ```python
    import requests
    ```

1. `while True` ਲੂਪ ਤੋਂ ਉੱਪਰ ਹੇਠਾਂ ਦਿੱਤਾ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ ਤਾਂ ਜੋ ਸਪੀਚ ਸਰਵਿਸ ਲਈ ਕੁਝ ਸੈਟਿੰਗਜ਼ ਡਿਕਲੇਅਰ ਕੀਤੀਆਂ ਜਾ ਸਕਣ:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'
    ```

    `<key>` ਨੂੰ ਆਪਣੇ ਸਪੀਚ ਸਰਵਿਸ ਰਿਸੋਰਸ ਲਈ API ਕੁੰਜੀ ਨਾਲ ਬਦਲੋ। `<location>` ਨੂੰ ਉਸ ਸਥਾਨ ਨਾਲ ਬਦਲੋ ਜੋ ਤੁਸੀਂ ਸਪੀਚ ਸਰਵਿਸ ਰਿਸੋਰਸ ਬਣਾਉਣ ਵੇਲੇ ਵਰਤਿਆ ਸੀ।

    `<language>` ਨੂੰ ਉਸ ਭਾਸ਼ਾ ਦੇ ਲੋਕੇਲ ਨਾਮ ਨਾਲ ਬਦਲੋ ਜਿਸ ਵਿੱਚ ਤੁਸੀਂ ਬੋਲ ਰਹੇ ਹੋ, ਉਦਾਹਰਨ ਲਈ ਅੰਗਰੇਜ਼ੀ ਲਈ `en-GB`, ਜਾਂ ਕੈਂਟੋਨੀਜ਼ ਲਈ `zn-HK`। ਤੁਸੀਂ ਮਾਈਕਰੋਸਾਫਟ ਡੌਕਸ 'ਤੇ [Language and voice support documentation](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) ਵਿੱਚ ਸਮਰਥਿਤ ਭਾਸ਼ਾਵਾਂ ਅਤੇ ਉਨ੍ਹਾਂ ਦੇ ਲੋਕੇਲ ਨਾਮਾਂ ਦੀ ਸੂਚੀ ਲੱਭ ਸਕਦੇ ਹੋ।

1. ਇਸ ਤੋਂ ਹੇਠਾਂ, ਐਕਸੈਸ ਟੋਕਨ ਪ੍ਰਾਪਤ ਕਰਨ ਲਈ ਹੇਠਾਂ ਦਿੱਤਾ ਫੰਕਸ਼ਨ ਸ਼ਾਮਲ ਕਰੋ:

    ```python
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_api_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    ਇਹ ਇੱਕ ਟੋਕਨ ਜਾਰੀ ਕਰਨ ਵਾਲੇ ਐਂਡਪੌਇੰਟ ਨੂੰ ਕਾਲ ਕਰਦਾ ਹੈ, API ਕੁੰਜੀ ਨੂੰ ਹੈਡਰ ਵਜੋਂ ਭੇਜਦਾ ਹੈ। ਇਹ ਕਾਲ ਇੱਕ ਐਕਸੈਸ ਟੋਕਨ ਵਾਪਸ ਕਰਦੀ ਹੈ ਜੋ ਸਪੀਚ ਸਰਵਿਸ ਨੂੰ ਕਾਲ ਕਰਨ ਲਈ ਵਰਤੀ ਜਾ ਸਕਦੀ ਹੈ।

1. ਇਸ ਤੋਂ ਹੇਠਾਂ, ਕੈਪਚਰ ਕੀਤੇ ਗਏ ਆਡੀਓ ਵਿੱਚ ਬੋਲੀ ਨੂੰ REST API ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਟੈਕਸਟ ਵਿੱਚ ਬਦਲਣ ਲਈ ਇੱਕ ਫੰਕਸ਼ਨ ਡਿਕਲੇਅਰ ਕਰੋ:

    ```python
    def convert_speech_to_text(buffer):
    ```

1. ਇਸ ਫੰਕਸ਼ਨ ਦੇ ਅੰਦਰ, REST API URL ਅਤੇ ਹੈਡਰ ਸੈਟ ਕਰੋ:

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

    ਇਹ ਸਪੀਚ ਸਰਵਿਸ ਰਿਸੋਰਸ ਦੇ ਸਥਾਨ ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਇੱਕ URL ਬਣਾਉਂਦਾ ਹੈ। ਫਿਰ ਇਹ `get_access_token` ਫੰਕਸ਼ਨ ਤੋਂ ਐਕਸੈਸ ਟੋਕਨ ਨਾਲ ਹੈਡਰ ਭਰਦਾ ਹੈ, ਨਾਲ ਹੀ ਆਡੀਓ ਕੈਪਚਰ ਕਰਨ ਲਈ ਵਰਤੇ ਗਏ ਸੈਂਪਲ ਰੇਟ ਨਾਲ। ਆਖਿਰ ਵਿੱਚ, ਇਹ URL ਨਾਲ ਭਾਸ਼ਾ ਵਾਲੇ ਆਡੀਓ ਦੇ ਪੈਰਾਮੀਟਰ ਪਰਿਭਾਸ਼ਿਤ ਕਰਦਾ ਹੈ।

1. ਇਸ ਤੋਂ ਹੇਠਾਂ, REST API ਨੂੰ ਕਾਲ ਕਰਨ ਅਤੇ ਟੈਕਸਟ ਵਾਪਸ ਪ੍ਰਾਪਤ ਕਰਨ ਲਈ ਹੇਠਾਂ ਦਿੱਤਾ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ:

    ```python
    response = requests.post(url, headers=headers, params=params, data=buffer)
    response_json = response.json()

    if response_json['RecognitionStatus'] == 'Success':
        return response_json['DisplayText']
    else:
        return ''
    ```

    ਇਹ URL ਨੂੰ ਕਾਲ ਕਰਦਾ ਹੈ ਅਤੇ ਜਵਾਬ ਵਿੱਚ ਆਉਣ ਵਾਲੇ JSON ਮੁੱਲ ਨੂੰ ਡਿਕੋਡ ਕਰਦਾ ਹੈ। ਜਵਾਬ ਵਿੱਚ `RecognitionStatus` ਮੁੱਲ ਦਰਸਾਉਂਦਾ ਹੈ ਕਿ ਕਾਲ ਸਫਲਤਾਪੂਰਵਕ ਬੋਲੀ ਨੂੰ ਟੈਕਸਟ ਵਿੱਚ ਬਦਲ ਸਕੀ ਹੈ ਜਾਂ ਨਹੀਂ, ਅਤੇ ਜੇ ਇਹ `Success` ਹੈ ਤਾਂ ਫੰਕਸ਼ਨ ਤੋਂ ਟੈਕਸਟ ਵਾਪਸ ਕੀਤਾ ਜਾਂਦਾ ਹੈ, ਨਹੀਂ ਤਾਂ ਖਾਲੀ ਸਤਰ ਵਾਪਸ ਕੀਤੀ ਜਾਂਦੀ ਹੈ।

1. `while True:` ਲੂਪ ਤੋਂ ਉੱਪਰ, ਸਪੀਚ ਤੋਂ ਟੈਕਸਟ ਸਰਵਿਸ ਤੋਂ ਵਾਪਸ ਆਏ ਟੈਕਸਟ ਨੂੰ ਪ੍ਰੋਸੈਸ ਕਰਨ ਲਈ ਇੱਕ ਫੰਕਸ਼ਨ ਡਿਫਾਈਨ ਕਰੋ। ਇਹ ਫੰਕਸ਼ਨ ਇਸ ਵੇਲੇ ਸਿਰਫ ਟੈਕਸਟ ਨੂੰ ਕੰਸੋਲ 'ਤੇ ਪ੍ਰਿੰਟ ਕਰੇਗਾ।

    ```python
    def process_text(text):
        print(text)
    ```

1. ਆਖਿਰ ਵਿੱਚ, `while True` ਲੂਪ ਵਿੱਚ `play_audio` ਨੂੰ ਕਾਲ ਕਰਨ ਦੀ ਥਾਂ `convert_speech_to_text` ਫੰਕਸ਼ਨ ਨੂੰ ਕਾਲ ਕਰੋ, ਅਤੇ ਟੈਕਸਟ ਨੂੰ `process_text` ਫੰਕਸ਼ਨ ਵਿੱਚ ਭੇਜੋ:

    ```python
    text = convert_speech_to_text(buffer)
    process_text(text)
    ```

1. ਕੋਡ ਚਲਾਓ। ਬਟਨ ਦਬਾਓ ਅਤੇ ਮਾਈਕਰੋਫੋਨ ਵਿੱਚ ਬੋਲੋ। ਜਦੋਂ ਤੁਸੀਂ ਖਤਮ ਕਰ ਲਓ, ਬਟਨ ਛੱਡ ਦਿਓ, ਅਤੇ ਆਡੀਓ ਟੈਕਸਟ ਵਿੱਚ ਬਦਲਿਆ ਜਾਵੇਗਾ ਅਤੇ ਕੰਸੋਲ 'ਤੇ ਪ੍ਰਿੰਟ ਹੋਵੇਗਾ।

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Hello world.
    Welcome to IoT for beginners.
    ```

    ਵੱਖ-ਵੱਖ ਕਿਸਮਾਂ ਦੇ ਵਾਕ ਬੋਲ ਕੇ ਦੇਖੋ, ਨਾਲ ਹੀ ਉਹ ਵਾਕ ਜਿੱਥੇ ਸ਼ਬਦ ਇੱਕੋ ਜਿਹੇ ਲੱਗਦੇ ਹਨ ਪਰ ਉਨ੍ਹਾਂ ਦੇ ਅਰਥ ਵੱਖਰੇ ਹੁੰਦੇ ਹਨ। ਉਦਾਹਰਨ ਲਈ, ਜੇ ਤੁਸੀਂ ਅੰਗਰੇਜ਼ੀ ਵਿੱਚ ਬੋਲ ਰਹੇ ਹੋ, ਤਾਂ ਕਹੋ 'I want to buy two bananas and an apple too', ਅਤੇ ਧਿਆਨ ਦਿਓ ਕਿ ਇਹ ਸਹੀ ਤੌਰ 'ਤੇ to, two ਅਤੇ too ਨੂੰ ਸੰਦਰਭ ਦੇ ਅਧਾਰ 'ਤੇ ਵਰਤਦਾ ਹੈ, ਸਿਰਫ਼ ਉਨ੍ਹਾਂ ਦੀ ਆਵਾਜ਼ ਦੇ ਅਧਾਰ 'ਤੇ ਨਹੀਂ।

> 💁 ਤੁਸੀਂ ਇਹ ਕੋਡ [code-speech-to-text/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/pi) ਫੋਲਡਰ ਵਿੱਚ ਲੱਭ ਸਕਦੇ ਹੋ।

😀 ਤੁਹਾਡਾ ਸਪੀਚ ਤੋਂ ਟੈਕਸਟ ਪ੍ਰੋਗਰਾਮ ਸਫਲ ਰਿਹਾ!

---

**ਅਸਵੀਕਰਤੀ**:  
ਇਹ ਦਸਤਾਵੇਜ਼ AI ਅਨੁਵਾਦ ਸੇਵਾ [Co-op Translator](https://github.com/Azure/co-op-translator) ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਅਨੁਵਾਦ ਕੀਤਾ ਗਿਆ ਹੈ। ਜਦੋਂ ਕਿ ਅਸੀਂ ਸਹੀ ਹੋਣ ਦੀ ਕੋਸ਼ਿਸ਼ ਕਰਦੇ ਹਾਂ, ਕਿਰਪਾ ਕਰਕੇ ਧਿਆਨ ਵਿੱਚ ਰੱਖੋ ਕਿ ਸਵੈਚਾਲਿਤ ਅਨੁਵਾਦਾਂ ਵਿੱਚ ਗਲਤੀਆਂ ਜਾਂ ਅਸੁਚੀਤਤਾਵਾਂ ਹੋ ਸਕਦੀਆਂ ਹਨ। ਇਸ ਦੀ ਮੂਲ ਭਾਸ਼ਾ ਵਿੱਚ ਮੂਲ ਦਸਤਾਵੇਜ਼ ਨੂੰ ਅਧਿਕਾਰਤ ਸਰੋਤ ਮੰਨਿਆ ਜਾਣਾ ਚਾਹੀਦਾ ਹੈ। ਮਹੱਤਵਪੂਰਨ ਜਾਣਕਾਰੀ ਲਈ, ਪੇਸ਼ੇਵਰ ਮਨੁੱਖੀ ਅਨੁਵਾਦ ਦੀ ਸਿਫਾਰਸ਼ ਕੀਤੀ ਜਾਂਦੀ ਹੈ। ਇਸ ਅਨੁਵਾਦ ਦੀ ਵਰਤੋਂ ਤੋਂ ਪੈਦਾ ਹੋਣ ਵਾਲੇ ਕਿਸੇ ਵੀ ਗਲਤਫਹਿਮੀ ਜਾਂ ਗਲਤ ਵਿਆਖਿਆ ਲਈ ਅਸੀਂ ਜ਼ਿੰਮੇਵਾਰ ਨਹੀਂ ਹਾਂ।