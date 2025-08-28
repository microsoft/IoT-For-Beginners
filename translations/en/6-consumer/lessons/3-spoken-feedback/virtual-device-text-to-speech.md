<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7966848a1f870e4c42edb4db67b13c57",
  "translation_date": "2025-08-28T19:17:31+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/virtual-device-text-to-speech.md",
  "language_code": "en"
}
-->
# Text to speech - Virtual IoT device

In this part of the lesson, you will write code to convert text into speech using the speech service.

## Convert text to speech

The speech services SDK, which you used in the previous lesson to convert speech into text, can also be used to convert text back into speech. When generating speech, you need to specify the voice to use, as speech can be created using various voices.

Each language supports a range of voices, and you can retrieve the list of supported voices for each language through the speech services SDK.

### Task - convert text to speech

1. Open the `smart-timer` project in VS Code, and make sure the virtual environment is activated in the terminal.

1. Import the `SpeechSynthesizer` from the `azure.cognitiveservices.speech` package by adding it to the existing imports:

    ```python
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer, SpeechSynthesizer
    ```

1. Above the `say` function, create a speech configuration to use with the speech synthesizer:

    ```python
    speech_config = SpeechConfig(subscription=speech_api_key,
                                 region=location)
    speech_config.speech_synthesis_language = language
    speech_synthesizer = SpeechSynthesizer(speech_config=speech_config)
    ```

    This uses the same API key, location, and language that were used by the recognizer.

1. Below this, add the following code to select a voice and set it on the speech configuration:

    ```python
    voices = speech_synthesizer.get_voices_async().get().voices
    first_voice = next(x for x in voices if x.locale.lower() == language.lower())
    speech_config.speech_synthesis_voice_name = first_voice.short_name
    ```

    This retrieves a list of all available voices and selects the first voice that matches the language being used.

    > 💁 You can find the complete list of supported voices in the [Language and voice support documentation on Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). If you want to use a specific voice, you can remove this function and directly set the voice name from the documentation. For example:
    >
    > ```python
    > speech_config.speech_synthesis_voice_name = 'hi-IN-SwaraNeural'
    > ```

1. Update the contents of the `say` function to generate SSML for the response:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{first_voice.short_name}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

1. Below this, stop the speech recognition, speak the SSML, and then restart the recognition:

    ```python
    recognizer.stop_continuous_recognition()
    speech_synthesizer.speak_ssml(ssml)
    recognizer.start_continuous_recognition()
    ```

    Speech recognition is paused while the text is spoken to prevent the announcement of the timer starting from being detected, sent to LUIS, and potentially interpreted as a request to set a new timer.

    > 💁 You can test this by commenting out the lines that stop and restart recognition. Set one timer, and you might notice that the announcement triggers a new timer, which leads to another announcement, causing yet another timer, and so on indefinitely!

1. Run the app, ensuring the function app is also running. Set some timers, and you will hear a spoken response confirming that your timer has been set, followed by another spoken response when the timer finishes.

> 💁 You can find this code in the [code-spoken-response/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/virtual-iot-device) folder.

😀 Your timer program was a success!

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we aim for accuracy, please note that automated translations may include errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is advised. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.