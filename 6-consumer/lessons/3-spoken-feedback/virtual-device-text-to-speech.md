# Text to speech - Virtual IoT device

In this part of the lesson, you will write code to convert text to speech using the speech service.

## Convert text to speech

The speech services SDK that you used in the last lesson to convert speech to text can be used to convert text back to speech. When requesting speech, you need to provide the voice to use as speech can be generated using a variety of different voices.

Each language supports a range of different voices, and you can get the list of supported voices for each language from the speech services SDK.

### Task - convert text to speech

1. Open the `smart-timer` project in VS Code, and ensure the virtual environment is loaded in the terminal.

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

    This uses the same API key, location and language that was used by the recognizer.

1. Below this, add the following code to get a voice and set it on the speech config:

    ```python
    voices = speech_synthesizer.get_voices_async().get().voices
    first_voice = next(x for x in voices if x.locale.lower() == language.lower())
    speech_config.speech_synthesis_voice_name = first_voice.short_name
    ```

    This retrieves a list of all the available voices, then finds the first voice that matches the language that is being used.

    > 💁 You can get the full list of supported voices from the [Language and voice support documentation on Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). If you want to use a specific voice, then you can remove this function and hard code the voice to the voice name from this documentation. For example:
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

1. Below this, stop the speech recognition, speak the SSML, then start the recognition again:

    ```python
    recognizer.stop_continuous_recognition()
    speech_synthesizer.speak_ssml(ssml)
    recognizer.start_continuous_recognition()
    ```

    The recognition is stopped whilst the text is spoken to avoid the announcement of the timer starting being detected, sent to LUIS and possibly interpreted as a request to set a new timer.

    > 💁 You can test this out by commenting out the lines to stop and restart the recognition. Set one timer, and you may find the announcement sets a new timer, which causes a new announcement, leading to a new timer, and so on for ever!

1. Run the app, and ensure the function app is also running. Set some timers, and you will hear a spoken response saying that your timer has been set, then another spoken response when the timer is complete.

> 💁 You can find this code in the [code-spoken-response/virtual-iot-device](code-spoken-response/virtual-iot-device) folder.

😀 Your timer program was a success!
