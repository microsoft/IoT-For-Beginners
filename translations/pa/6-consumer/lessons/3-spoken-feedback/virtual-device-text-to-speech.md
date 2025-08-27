<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7966848a1f870e4c42edb4db67b13c57",
  "translation_date": "2025-08-27T14:00:18+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/virtual-device-text-to-speech.md",
  "language_code": "pa"
}
-->
# ਟੈਕਸਟ ਤੋਂ ਬੋਲਣ ਤੱਕ - ਵਰਚੁਅਲ IoT ਡਿਵਾਈਸ

ਇਸ ਪਾਠ ਦੇ ਇਸ ਹਿੱਸੇ ਵਿੱਚ, ਤੁਸੀਂ ਟੈਕਸਟ ਨੂੰ ਬੋਲਣ ਵਿੱਚ ਬਦਲਣ ਲਈ ਕੋਡ ਲਿਖੋਗੇ ਜੋ ਕਿ ਬੋਲਣ ਸੇਵਾ ਦੀ ਵਰਤੋਂ ਕਰਦਾ ਹੈ।

## ਟੈਕਸਟ ਨੂੰ ਬੋਲਣ ਵਿੱਚ ਬਦਲੋ

ਪਿਛਲੇ ਪਾਠ ਵਿੱਚ ਤੁਸੀਂ ਜੋ ਬੋਲਣ ਸੇਵਾਵਾਂ SDK ਬੋਲਣ ਨੂੰ ਟੈਕਸਟ ਵਿੱਚ ਬਦਲਣ ਲਈ ਵਰਤੀ ਸੀ, ਉਸੇ SDK ਦੀ ਵਰਤੋਂ ਟੈਕਸਟ ਨੂੰ ਵਾਪਸ ਬੋਲਣ ਵਿੱਚ ਬਦਲਣ ਲਈ ਕੀਤੀ ਜਾ ਸਕਦੀ ਹੈ। ਬੋਲਣ ਦੀ ਬੇਨਤੀ ਕਰਦੇ ਸਮੇਂ, ਤੁਹਾਨੂੰ ਉਹ ਆਵਾਜ਼ ਪ੍ਰਦਾਨ ਕਰਨੀ ਪਵੇਗੀ ਜੋ ਵਰਤਣੀ ਹੈ, ਕਿਉਂਕਿ ਬੋਲਣ ਵੱਖ-ਵੱਖ ਆਵਾਜ਼ਾਂ ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਤਿਆਰ ਕੀਤਾ ਜਾ ਸਕਦਾ ਹੈ।

ਹਰ ਭਾਸ਼ਾ ਵੱਖ-ਵੱਖ ਆਵਾਜ਼ਾਂ ਦਾ ਸਮਰਥਨ ਕਰਦੀ ਹੈ, ਅਤੇ ਤੁਸੀਂ ਹਰ ਭਾਸ਼ਾ ਲਈ ਸਮਰਥਿਤ ਆਵਾਜ਼ਾਂ ਦੀ ਸੂਚੀ ਬੋਲਣ ਸੇਵਾਵਾਂ SDK ਤੋਂ ਪ੍ਰਾਪਤ ਕਰ ਸਕਦੇ ਹੋ।

### ਕੰਮ - ਟੈਕਸਟ ਨੂੰ ਬੋਲਣ ਵਿੱਚ ਬਦਲੋ

1. `smart-timer` ਪ੍ਰੋਜੈਕਟ ਨੂੰ VS Code ਵਿੱਚ ਖੋਲ੍ਹੋ, ਅਤੇ ਯਕੀਨੀ ਬਣਾਓ ਕਿ ਵਰਚੁਅਲ ਵਾਤਾਵਰਣ ਟਰਮੀਨਲ ਵਿੱਚ ਲੋਡ ਹੈ।

1. `azure.cognitiveservices.speech` ਪੈਕੇਜ ਤੋਂ `SpeechSynthesizer` ਨੂੰ ਮੌਜੂਦਾ ਇੰਪੋਰਟਸ ਵਿੱਚ ਸ਼ਾਮਲ ਕਰਕੇ ਇੰਪੋਰਟ ਕਰੋ:

    ```python
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer, SpeechSynthesizer
    ```

1. `say` ਫੰਕਸ਼ਨ ਤੋਂ ਉੱਪਰ, ਬੋਲਣ ਸਿੰਥਸਾਈਜ਼ਰ ਨਾਲ ਵਰਤਣ ਲਈ ਇੱਕ ਬੋਲਣ ਸੰਰਚਨਾ ਬਣਾਓ:

    ```python
    speech_config = SpeechConfig(subscription=speech_api_key,
                                 region=location)
    speech_config.speech_synthesis_language = language
    speech_synthesizer = SpeechSynthesizer(speech_config=speech_config)
    ```

    ਇਹ ਉਹੀ API ਕੁੰਜੀ, ਸਥਾਨ ਅਤੇ ਭਾਸ਼ਾ ਦੀ ਵਰਤੋਂ ਕਰਦਾ ਹੈ ਜੋ ਪਛਾਣਕਰਤਾ ਦੁਆਰਾ ਵਰਤੀ ਗਈ ਸੀ।

1. ਇਸ ਤੋਂ ਹੇਠਾਂ, ਇੱਕ ਆਵਾਜ਼ ਪ੍ਰਾਪਤ ਕਰਨ ਅਤੇ ਇਸਨੂੰ ਬੋਲਣ ਸੰਰਚਨਾ 'ਤੇ ਸੈਟ ਕਰਨ ਲਈ ਹੇਠਾਂ ਦਿੱਤਾ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ:

    ```python
    voices = speech_synthesizer.get_voices_async().get().voices
    first_voice = next(x for x in voices if x.locale.lower() == language.lower())
    speech_config.speech_synthesis_voice_name = first_voice.short_name
    ```

    ਇਹ ਸਾਰੀਆਂ ਉਪਲਬਧ ਆਵਾਜ਼ਾਂ ਦੀ ਸੂਚੀ ਪ੍ਰਾਪਤ ਕਰਦਾ ਹੈ, ਫਿਰ ਉਹ ਪਹਿਲੀ ਆਵਾਜ਼ ਲੱਭਦਾ ਹੈ ਜੋ ਵਰਤੀ ਜਾ ਰਹੀ ਭਾਸ਼ਾ ਨਾਲ ਮੇਲ ਖਾਂਦੀ ਹੈ।

    > 💁 ਤੁਸੀਂ ਮਾਈਕਰੋਸਾਫਟ ਡੌਕਸ 'ਤੇ [ਭਾਸ਼ਾ ਅਤੇ ਆਵਾਜ਼ ਸਮਰਥਨ ਦਸਤਾਵੇਜ਼](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech) ਤੋਂ ਸਮਰਥਿਤ ਆਵਾਜ਼ਾਂ ਦੀ ਪੂਰੀ ਸੂਚੀ ਪ੍ਰਾਪਤ ਕਰ ਸਕਦੇ ਹੋ। ਜੇ ਤੁਸੀਂ ਕਿਸੇ ਖਾਸ ਆਵਾਜ਼ ਦੀ ਵਰਤੋਂ ਕਰਨੀ ਚਾਹੁੰਦੇ ਹੋ, ਤਾਂ ਤੁਸੀਂ ਇਸ ਫੰਕਸ਼ਨ ਨੂੰ ਹਟਾ ਸਕਦੇ ਹੋ ਅਤੇ ਦਸਤਾਵੇਜ਼ ਵਿੱਚ ਦਿੱਤੇ ਆਵਾਜ਼ ਦੇ ਨਾਮ ਨਾਲ ਆਵਾਜ਼ ਨੂੰ ਹਾਰਡ ਕੋਡ ਕਰ ਸਕਦੇ ਹੋ। ਉਦਾਹਰਣ ਲਈ:
    >
    > ```python
    > speech_config.speech_synthesis_voice_name = 'hi-IN-SwaraNeural'
    > ```

1. `say` ਫੰਕਸ਼ਨ ਦੀ ਸਮੱਗਰੀ ਨੂੰ SSML ਤਿਆਰ ਕਰਨ ਲਈ ਅਪਡੇਟ ਕਰੋ:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{first_voice.short_name}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

1. ਇਸ ਤੋਂ ਹੇਠਾਂ, ਬੋਲਣ ਪਛਾਣ ਨੂੰ ਰੋਕੋ, SSML ਬੋਲੋ, ਫਿਰ ਪਛਾਣ ਨੂੰ ਮੁੜ ਸ਼ੁਰੂ ਕਰੋ:

    ```python
    recognizer.stop_continuous_recognition()
    speech_synthesizer.speak_ssml(ssml)
    recognizer.start_continuous_recognition()
    ```

    ਪਛਾਣ ਨੂੰ ਰੋਕਿਆ ਜਾਂਦਾ ਹੈ ਜਦੋਂ ਟੈਕਸਟ ਬੋਲਿਆ ਜਾ ਰਿਹਾ ਹੋਵੇ ਤਾਂ ਜੋ ਟਾਈਮਰ ਸ਼ੁਰੂ ਹੋਣ ਦੀ ਘੋਸ਼ਣਾ ਪਛਾਣੀ ਨਾ ਜਾਵੇ, LUIS ਨੂੰ ਭੇਜੀ ਨਾ ਜਾਵੇ ਅਤੇ ਸੰਭਵ ਤੌਰ 'ਤੇ ਇਸਨੂੰ ਨਵਾਂ ਟਾਈਮਰ ਸੈਟ ਕਰਨ ਦੀ ਬੇਨਤੀ ਵਜੋਂ ਵਿਆਖਿਆ ਨਾ ਕੀਤਾ ਜਾਵੇ।

    > 💁 ਤੁਸੀਂ ਪਛਾਣ ਨੂੰ ਰੋਕਣ ਅਤੇ ਮੁੜ ਸ਼ੁਰੂ ਕਰਨ ਵਾਲੀਆਂ ਲਾਈਨਾਂ ਨੂੰ ਕਮੈਂਟ ਕਰਕੇ ਇਸਨੂੰ ਟੈਸਟ ਕਰ ਸਕਦੇ ਹੋ। ਇੱਕ ਟਾਈਮਰ ਸੈਟ ਕਰੋ, ਅਤੇ ਤੁਸੀਂ ਦੇਖ ਸਕਦੇ ਹੋ ਕਿ ਘੋਸ਼ਣਾ ਇੱਕ ਨਵਾਂ ਟਾਈਮਰ ਸੈਟ ਕਰਦੀ ਹੈ, ਜੋ ਇੱਕ ਨਵੀਂ ਘੋਸ਼ਣਾ ਕਰਦਾ ਹੈ, ਜੋ ਇੱਕ ਨਵਾਂ ਟਾਈਮਰ ਸੈਟ ਕਰਦਾ ਹੈ, ਅਤੇ ਇਹ ਸਦਾ ਲਈ ਚਲਦਾ ਰਹਿੰਦਾ ਹੈ!

1. ਐਪ ਚਲਾਓ, ਅਤੇ ਯਕੀਨੀ ਬਣਾਓ ਕਿ ਫੰਕਸ਼ਨ ਐਪ ਵੀ ਚਲ ਰਹੀ ਹੈ। ਕੁਝ ਟਾਈਮਰ ਸੈਟ ਕਰੋ, ਅਤੇ ਤੁਸੀਂ ਇੱਕ ਬੋਲੀ ਗਈ ਪ੍ਰਤੀਕ੍ਰਿਆ ਸੁਣੋਗੇ ਜੋ ਕਹੇਗੀ ਕਿ ਤੁਹਾਡਾ ਟਾਈਮਰ ਸੈਟ ਕੀਤਾ ਗਿਆ ਹੈ, ਫਿਰ ਇੱਕ ਹੋਰ ਬੋਲੀ ਗਈ ਪ੍ਰਤੀਕ੍ਰਿਆ ਜਦੋਂ ਟਾਈਮਰ ਪੂਰਾ ਹੋ ਜਾਵੇਗਾ।

> 💁 ਤੁਸੀਂ ਇਹ ਕੋਡ [code-spoken-response/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/virtual-iot-device) ਫੋਲਡਰ ਵਿੱਚ ਲੱਭ ਸਕਦੇ ਹੋ।

😀 ਤੁਹਾਡਾ ਟਾਈਮਰ ਪ੍ਰੋਗਰਾਮ ਸਫਲ ਰਿਹਾ!

---

**ਅਸਵੀਕਰਤੀ**:  
ਇਹ ਦਸਤਾਵੇਜ਼ AI ਅਨੁਵਾਦ ਸੇਵਾ [Co-op Translator](https://github.com/Azure/co-op-translator) ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਅਨੁਵਾਦ ਕੀਤਾ ਗਿਆ ਹੈ। ਜਦੋਂ ਕਿ ਅਸੀਂ ਸਹੀ ਹੋਣ ਦੀ ਕੋਸ਼ਿਸ਼ ਕਰਦੇ ਹਾਂ, ਕਿਰਪਾ ਕਰਕੇ ਧਿਆਨ ਦਿਓ ਕਿ ਸਵੈਚਾਲਿਤ ਅਨੁਵਾਦਾਂ ਵਿੱਚ ਗਲਤੀਆਂ ਜਾਂ ਅਸੁਚਤਤਾਵਾਂ ਹੋ ਸਕਦੀਆਂ ਹਨ। ਮੂਲ ਦਸਤਾਵੇਜ਼ ਨੂੰ ਇਸਦੀ ਮੂਲ ਭਾਸ਼ਾ ਵਿੱਚ ਅਧਿਕਾਰਤ ਸਰੋਤ ਮੰਨਿਆ ਜਾਣਾ ਚਾਹੀਦਾ ਹੈ। ਮਹੱਤਵਪੂਰਨ ਜਾਣਕਾਰੀ ਲਈ, ਪੇਸ਼ੇਵਰ ਮਨੁੱਖੀ ਅਨੁਵਾਦ ਦੀ ਸਿਫਾਰਸ਼ ਕੀਤੀ ਜਾਂਦੀ ਹੈ। ਇਸ ਅਨੁਵਾਦ ਦੀ ਵਰਤੋਂ ਤੋਂ ਪੈਦਾ ਹੋਣ ਵਾਲੇ ਕਿਸੇ ਵੀ ਗਲਤ ਫਹਿਮੀ ਜਾਂ ਗਲਤ ਵਿਆਖਿਆ ਲਈ ਅਸੀਂ ਜ਼ਿੰਮੇਵਾਰ ਨਹੀਂ ਹਾਂ।