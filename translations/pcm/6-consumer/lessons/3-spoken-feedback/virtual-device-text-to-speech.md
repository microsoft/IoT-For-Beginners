<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7966848a1f870e4c42edb4db67b13c57",
  "translation_date": "2025-11-18T19:16:59+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/virtual-device-text-to-speech.md",
  "language_code": "pcm"
}
-->
# Text to speech - Virtual IoT device

For dis part of di lesson, you go write code wey go change text to speech using di speech service.

## Change text to speech

Di speech services SDK wey you use for di last lesson to change speech to text fit also change text back to speech. Wen you dey request speech, you go need provide di voice wey you wan use because speech fit dey generated with different voices.

Each language get different voices wey e support, and you fit get di list of di voices wey each language support from di speech services SDK.

### Task - change text to speech

1. Open di `smart-timer` project for VS Code, and make sure say di virtual environment dey loaded for di terminal.

1. Import di `SpeechSynthesizer` from di `azure.cognitiveservices.speech` package by adding am to di imports wey dey already:

    ```python
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer, SpeechSynthesizer
    ```

1. For di top of di `say` function, create one speech configuration wey go work with di speech synthesizer:

    ```python
    speech_config = SpeechConfig(subscription=speech_api_key,
                                 region=location)
    speech_config.speech_synthesis_language = language
    speech_synthesizer = SpeechSynthesizer(speech_config=speech_config)
    ```

    Dis one dey use di same API key, location and language wey di recognizer dey use.

1. For di bottom of dis one, add di code wey dey below to get one voice and set am for di speech config:

    ```python
    voices = speech_synthesizer.get_voices_async().get().voices
    first_voice = next(x for x in voices if x.locale.lower() == language.lower())
    speech_config.speech_synthesis_voice_name = first_voice.short_name
    ```

    Dis one dey collect list of all di available voices, then e go find di first voice wey match di language wey dem dey use.

    > 💁 You fit get di full list of di voices wey dem support from di [Language and voice support documentation on Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). If you wan use one specific voice, you fit remove dis function and just put di voice name from di documentation. Example:
    >
    > ```python
    > speech_config.speech_synthesis_voice_name = 'hi-IN-SwaraNeural'
    > ```

1. Update wetin dey inside di `say` function to generate SSML for di response:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{first_voice.short_name}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

1. For di bottom of dis one, stop di speech recognition, talk di SSML, then start di recognition again:

    ```python
    recognizer.stop_continuous_recognition()
    speech_synthesizer.speak_ssml(ssml)
    recognizer.start_continuous_recognition()
    ```

    Di recognition dey stop while di text dey spoken so dat di announcement of di timer wey dey start no go dey detected, sent to LUIS and fit dey interpreted as request to set new timer.

    > 💁 You fit test dis one by commenting out di lines wey dey stop and restart di recognition. Set one timer, and you fit notice say di announcement go set new timer, wey go cause new announcement, wey go lead to new timer, and e go continue like dat forever!

1. Run di app, and make sure say di function app dey run too. Set some timers, and you go hear spoken response wey go talk say your timer don set, then another spoken response wen di timer don complete.

> 💁 You fit find dis code for di [code-spoken-response/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/virtual-iot-device) folder.

😀 Your timer program na success!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Disclaimer**:  
Dis dokyument don use AI transle-shon service [Co-op Translator](https://github.com/Azure/co-op-translator) do di transle-shon. Even as we dey try make di transle-shon correct, abeg make you sabi say AI transle-shon fit get mistake or no dey accurate well. Di original dokyument for im native language na di one wey you go take as di correct source. For any important mata, e good make you use professional human transle-shon. We no go fit take blame for any misunderstanding or wrong interpretation wey fit happen because you use dis transle-shon.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->