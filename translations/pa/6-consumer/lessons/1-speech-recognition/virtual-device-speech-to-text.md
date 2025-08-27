<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c0550b254b9ba2539baf1e6bb5fc05f8",
  "translation_date": "2025-08-27T14:10:56+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/virtual-device-speech-to-text.md",
  "language_code": "pa"
}
-->
# ਸਪੀਚ ਤੋਂ ਟੈਕਸਟ - ਵਰਚੁਅਲ IoT ਡਿਵਾਈਸ

ਇਸ ਪਾਠ ਦੇ ਇਸ ਹਿੱਸੇ ਵਿੱਚ, ਤੁਸੀਂ ਮਾਈਕ੍ਰੋਫੋਨ ਤੋਂ ਕੈਪਚਰ ਕੀਤੇ ਗਏ ਸਪੀਚ ਨੂੰ ਸਪੀਚ ਸਰਵਿਸ ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਟੈਕਸਟ ਵਿੱਚ ਬਦਲਣ ਲਈ ਕੋਡ ਲਿਖੋਗੇ।

## ਸਪੀਚ ਨੂੰ ਟੈਕਸਟ ਵਿੱਚ ਬਦਲੋ

Windows, Linux, ਅਤੇ macOS 'ਤੇ, ਸਪੀਚ ਸਰਵਿਸਜ਼ Python SDK ਦੀ ਵਰਤੋਂ ਕੀਤੀ ਜਾ ਸਕਦੀ ਹੈ ਤੁਹਾਡੇ ਮਾਈਕ੍ਰੋਫੋਨ ਨੂੰ ਸੁਣਨ ਲਈ ਅਤੇ ਕਿਸੇ ਵੀ ਸਪੀਚ ਨੂੰ ਜੋ ਪਤਾ ਲੱਗਦਾ ਹੈ, ਟੈਕਸਟ ਵਿੱਚ ਬਦਲਣ ਲਈ। ਇਹ ਲਗਾਤਾਰ ਸੁਣਦਾ ਹੈ, ਆਡੀਓ ਲੈਵਲ ਦਾ ਪਤਾ ਲਗਾਉਂਦਾ ਹੈ ਅਤੇ ਸਪੀਚ ਨੂੰ ਟੈਕਸਟ ਵਿੱਚ ਬਦਲਣ ਲਈ ਭੇਜਦਾ ਹੈ ਜਦੋਂ ਆਡੀਓ ਲੈਵਲ ਘਟਦਾ ਹੈ, ਜਿਵੇਂ ਕਿ ਸਪੀਚ ਦੇ ਇੱਕ ਬਲਾਕ ਦੇ ਅੰਤ 'ਤੇ।

### ਟਾਸਕ - ਸਪੀਚ ਨੂੰ ਟੈਕਸਟ ਵਿੱਚ ਬਦਲੋ

1. ਆਪਣੇ ਕੰਪਿਊਟਰ 'ਤੇ `smart-timer` ਨਾਮਕ ਫੋਲਡਰ ਵਿੱਚ ਇੱਕ ਨਵਾਂ Python ਐਪ ਬਣਾਓ ਜਿਸ ਵਿੱਚ ਇੱਕ ਫਾਈਲ `app.py` ਹੋਵੇ ਅਤੇ ਇੱਕ Python ਵਰਚੁਅਲ ਇਨਵਾਇਰਨਮੈਂਟ ਹੋਵੇ।

1. ਸਪੀਚ ਸਰਵਿਸਜ਼ ਲਈ Pip ਪੈਕੇਜ ਇੰਸਟਾਲ ਕਰੋ। ਯਕੀਨੀ ਬਣਾਓ ਕਿ ਤੁਸੀਂ ਇਹ ਵਰਚੁਅਲ ਇਨਵਾਇਰਨਮੈਂਟ ਐਕਟੀਵੇਟ ਕੀਤੇ ਹੋਏ ਟਰਮੀਨਲ ਤੋਂ ਇੰਸਟਾਲ ਕਰ ਰਹੇ ਹੋ।

    ```sh
    pip install azure-cognitiveservices-speech
    ```

    > ⚠️ ਜੇ ਤੁਹਾਨੂੰ ਹੇਠਾਂ ਦਿੱਤਾ ਗਲਤੀ ਸੁਨੇਹਾ ਮਿਲਦਾ ਹੈ:
    >
    > ```output
    > ERROR: Could not find a version that satisfies the requirement azure-cognitiveservices-speech (from versions: none)
    > ERROR: No matching distribution found for azure-cognitiveservices-speech
    > ```
    >
    > ਤੁਹਾਨੂੰ Pip ਨੂੰ ਅਪਡੇਟ ਕਰਨ ਦੀ ਲੋੜ ਹੋਵੇਗੀ। ਇਹ ਹੇਠਾਂ ਦਿੱਤੇ ਕਮਾਂਡ ਨਾਲ ਕਰੋ, ਫਿਰ ਪੈਕੇਜ ਨੂੰ ਦੁਬਾਰਾ ਇੰਸਟਾਲ ਕਰਨ ਦੀ ਕੋਸ਼ਿਸ਼ ਕਰੋ:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. `app.py` ਫਾਈਲ ਵਿੱਚ ਹੇਠਾਂ ਦਿੱਤੇ ਇੰਪੋਰਟਸ ਸ਼ਾਮਲ ਕਰੋ:

    ```python
    import requests
    import time
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer
    ```

    ਇਹ ਕੁਝ ਕਲਾਸਾਂ ਨੂੰ ਇੰਪੋਰਟ ਕਰਦਾ ਹੈ ਜੋ ਸਪੀਚ ਨੂੰ ਪਛਾਣਣ ਲਈ ਵਰਤੀ ਜਾਂਦੀਆਂ ਹਨ।

1. ਕੁਝ ਕਨਫਿਗਰੇਸ਼ਨ ਡਿਕਲੇਅਰ ਕਰਨ ਲਈ ਹੇਠਾਂ ਦਿੱਤਾ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'

    recognizer_config = SpeechConfig(subscription=speech_api_key,
                                     region=location,
                                     speech_recognition_language=language)
    ```

    `<key>` ਨੂੰ ਤੁਹਾਡੇ ਸਪੀਚ ਸਰਵਿਸ ਲਈ API ਕੁੰਜੀ ਨਾਲ ਬਦਲੋ। `<location>` ਨੂੰ ਉਸ ਸਥਾਨ ਨਾਲ ਬਦਲੋ ਜੋ ਤੁਸੀਂ ਸਪੀਚ ਸਰਵਿਸ ਰਿਸੋਰਸ ਬਣਾਉਣ ਵੇਲੇ ਵਰਤਿਆ ਸੀ।

    `<language>` ਨੂੰ ਉਸ ਭਾਸ਼ਾ ਦੇ ਲੋਕੇਲ ਨਾਮ ਨਾਲ ਬਦਲੋ ਜਿਸ ਵਿੱਚ ਤੁਸੀਂ ਬੋਲ ਰਹੇ ਹੋ, ਉਦਾਹਰਣ ਲਈ `en-GB` ਅੰਗਰੇਜ਼ੀ ਲਈ, ਜਾਂ `zn-HK` ਕੈਂਟੋਨੀਜ਼ ਲਈ। ਤੁਸੀਂ ਸਹਾਇਕ ਭਾਸ਼ਾਵਾਂ ਅਤੇ ਉਨ੍ਹਾਂ ਦੇ ਲੋਕੇਲ ਨਾਮਾਂ ਦੀ ਸੂਚੀ [Microsoft Docs 'ਤੇ ਭਾਸ਼ਾ ਅਤੇ ਆਵਾਜ਼ ਸਹਾਇਤਾ ਦਸਤਾਵੇਜ਼](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) ਵਿੱਚ ਲੱਭ ਸਕਦੇ ਹੋ।

    ਇਹ ਕਨਫਿਗਰੇਸ਼ਨ ਇੱਕ `SpeechConfig` ਆਬਜੈਕਟ ਬਣਾਉਣ ਲਈ ਵਰਤੀ ਜਾਂਦੀ ਹੈ ਜੋ ਸਪੀਚ ਸਰਵਿਸਜ਼ ਨੂੰ ਕਨਫਿਗਰ ਕਰਨ ਲਈ ਵਰਤੀ ਜਾਵੇਗੀ।

1. ਸਪੀਚ ਰਿਕਗਨਾਈਜ਼ਰ ਬਣਾਉਣ ਲਈ ਹੇਠਾਂ ਦਿੱਤਾ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ:

    ```python
    recognizer = SpeechRecognizer(speech_config=recognizer_config)
    ```

1. ਸਪੀਚ ਰਿਕਗਨਾਈਜ਼ਰ ਇੱਕ ਬੈਕਗ੍ਰਾਊਂਡ ਥ੍ਰੈਡ 'ਤੇ ਚਲਦਾ ਹੈ, ਆਡੀਓ ਸੁਣਦਾ ਹੈ ਅਤੇ ਇਸ ਵਿੱਚ ਮੌਜੂਦ ਸਪੀਚ ਨੂੰ ਟੈਕਸਟ ਵਿੱਚ ਬਦਲਦਾ ਹੈ। ਤੁਸੀਂ ਟੈਕਸਟ ਨੂੰ ਇੱਕ ਕਾਲਬੈਕ ਫੰਕਸ਼ਨ ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਪ੍ਰਾਪਤ ਕਰ ਸਕਦੇ ਹੋ - ਇੱਕ ਫੰਕਸ਼ਨ ਜੋ ਤੁਸੀਂ ਪਰਿਭਾਸ਼ਿਤ ਕਰਦੇ ਹੋ ਅਤੇ ਰਿਕਗਨਾਈਜ਼ਰ ਨੂੰ ਪਾਸ ਕਰਦੇ ਹੋ। ਹਰ ਵਾਰ ਜਦੋਂ ਸਪੀਚ ਪਤਾ ਲੱਗਦਾ ਹੈ, ਕਾਲਬੈਕ ਨੂੰ ਕਾਲ ਕੀਤਾ ਜਾਂਦਾ ਹੈ। ਹੇਠਾਂ ਦਿੱਤਾ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ ਕਾਲਬੈਕ ਨੂੰ ਪਰਿਭਾਸ਼ਿਤ ਕਰਨ ਲਈ, ਅਤੇ ਇਸ ਕਾਲਬੈਕ ਨੂੰ ਰਿਕਗਨਾਈਜ਼ਰ ਨੂੰ ਪਾਸ ਕਰਨ ਲਈ, ਨਾਲ ਹੀ ਟੈਕਸਟ ਨੂੰ ਪ੍ਰੋਸੈਸ ਕਰਨ ਲਈ ਇੱਕ ਫੰਕਸ਼ਨ ਪਰਿਭਾਸ਼ਿਤ ਕਰਨ ਲਈ, ਜੋ ਟੈਕਸਟ ਨੂੰ ਕਨਸੋਲ 'ਤੇ ਲਿਖਦਾ ਹੈ:

    ```python
    def process_text(text):
        print(text)

    def recognized(args):
        process_text(args.result.text)
    
    recognizer.recognized.connect(recognized)
    ```

1. ਰਿਕਗਨਾਈਜ਼ਰ ਸਿਰਫ਼ ਤਦ ਹੀ ਸੁਣਨਾ ਸ਼ੁਰੂ ਕਰਦਾ ਹੈ ਜਦੋਂ ਤੁਸੀਂ ਇਸਨੂੰ ਸਪਸ਼ਟ ਤੌਰ 'ਤੇ ਸ਼ੁਰੂ ਕਰਦੇ ਹੋ। ਸੁਣਨ ਸ਼ੁਰੂ ਕਰਨ ਲਈ ਹੇਠਾਂ ਦਿੱਤਾ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ। ਇਹ ਬੈਕਗ੍ਰਾਊਂਡ ਵਿੱਚ ਚਲਦਾ ਹੈ, ਇਸ ਲਈ ਤੁਹਾਡੇ ਐਪਲੀਕੇਸ਼ਨ ਨੂੰ ਇੱਕ ਅਨੰਤ ਲੂਪ ਦੀ ਵੀ ਲੋੜ ਹੋਵੇਗੀ ਜੋ ਐਪਲੀਕੇਸ਼ਨ ਨੂੰ ਚਲਾਉਣ ਲਈ ਸੌਂਦਾ ਰਹੇ।

    ```python
    recognizer.start_continuous_recognition()

    while True:
        time.sleep(1)
    ```

1. ਇਸ ਐਪ ਨੂੰ ਚਲਾਓ। ਆਪਣੇ ਮਾਈਕ੍ਰੋਫੋਨ ਵਿੱਚ ਬੋਲੋ ਅਤੇ ਆਡੀਓ ਜੋ ਟੈਕਸਟ ਵਿੱਚ ਬਦਲਿਆ ਗਿਆ ਹੈ, ਕਨਸੋਲ 'ਤੇ ਆਉਟਪੁਟ ਹੋਵੇਗਾ।

    ```output
    (.venv) ➜  smart-timer python3 app.py
    Hello world.
    Welcome to IoT for beginners.
    ```

    ਵੱਖ-ਵੱਖ ਕਿਸਮਾਂ ਦੇ ਵਾਕ ਬੋਲ ਕੇ ਦੇਖੋ, ਨਾਲ ਹੀ ਉਹ ਵਾਕ ਜਿੱਥੇ ਸ਼ਬਦ ਇੱਕੋ ਜਿਹੇ ਲੱਗਦੇ ਹਨ ਪਰ ਉਨ੍ਹਾਂ ਦੇ ਅਰਥ ਵੱਖਰੇ ਹੁੰਦੇ ਹਨ। ਉਦਾਹਰਣ ਲਈ, ਜੇ ਤੁਸੀਂ ਅੰਗਰੇਜ਼ੀ ਵਿੱਚ ਬੋਲ ਰਹੇ ਹੋ, ਤਾਂ ਕਹੋ 'I want to buy two bananas and an apple too', ਅਤੇ ਧਿਆਨ ਦਿਓ ਕਿ ਇਹ ਸਹੀ to, two ਅਤੇ too ਨੂੰ ਕਿਵੇਂ ਵਰਤਦਾ ਹੈ ਸ਼ਬਦ ਦੇ ਸੰਦਰਭ ਦੇ ਆਧਾਰ 'ਤੇ, ਸਿਰਫ਼ ਇਸ ਦੀ ਆਵਾਜ਼ ਦੇ ਆਧਾਰ 'ਤੇ ਨਹੀਂ।

> 💁 ਤੁਸੀਂ ਇਹ ਕੋਡ [code-speech-to-text/virtual-iot-device](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/virtual-iot-device) ਫੋਲਡਰ ਵਿੱਚ ਲੱਭ ਸਕਦੇ ਹੋ।

😀 ਤੁਹਾਡਾ ਸਪੀਚ ਤੋਂ ਟੈਕਸਟ ਪ੍ਰੋਗਰਾਮ ਸਫਲ ਰਿਹਾ!

---

**ਅਸਵੀਕਰਤੀ**:  
ਇਹ ਦਸਤਾਵੇਜ਼ AI ਅਨੁਵਾਦ ਸੇਵਾ [Co-op Translator](https://github.com/Azure/co-op-translator) ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਅਨੁਵਾਦ ਕੀਤਾ ਗਿਆ ਹੈ। ਹਾਲਾਂਕਿ ਅਸੀਂ ਸਹੀਅਤ ਲਈ ਯਤਨਸ਼ੀਲ ਹਾਂ, ਕਿਰਪਾ ਕਰਕੇ ਧਿਆਨ ਦਿਓ ਕਿ ਸਵੈਚਾਲਿਤ ਅਨੁਵਾਦਾਂ ਵਿੱਚ ਗਲਤੀਆਂ ਜਾਂ ਅਸੁਚਤਤਾਵਾਂ ਹੋ ਸਕਦੀਆਂ ਹਨ। ਮੂਲ ਦਸਤਾਵੇਜ਼, ਜੋ ਇਸਦੀ ਮੂਲ ਭਾਸ਼ਾ ਵਿੱਚ ਹੈ, ਨੂੰ ਅਧਿਕਾਰਤ ਸਰੋਤ ਮੰਨਿਆ ਜਾਣਾ ਚਾਹੀਦਾ ਹੈ। ਮਹੱਤਵਪੂਰਨ ਜਾਣਕਾਰੀ ਲਈ, ਪੇਸ਼ੇਵਰ ਮਨੁੱਖੀ ਅਨੁਵਾਦ ਦੀ ਸਿਫਾਰਸ਼ ਕੀਤੀ ਜਾਂਦੀ ਹੈ। ਇਸ ਅਨੁਵਾਦ ਦੀ ਵਰਤੋਂ ਤੋਂ ਪੈਦਾ ਹੋਣ ਵਾਲੇ ਕਿਸੇ ਵੀ ਗਲਤਫਹਿਮੀ ਜਾਂ ਗਲਤ ਵਿਆਖਿਆ ਲਈ ਅਸੀਂ ਜ਼ਿੰਮੇਵਾਰ ਨਹੀਂ ਹਾਂ।