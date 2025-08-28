<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c0550b254b9ba2539baf1e6bb5fc05f8",
  "translation_date": "2025-08-28T19:25:32+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/virtual-device-speech-to-text.md",
  "language_code": "en"
}
-->
# Speech to text - Virtual IoT device

In this part of the lesson, you will write code to convert speech captured from your microphone into text using the speech service.

## Convert speech to text

On Windows, Linux, and macOS, the Python SDK for speech services can be used to listen to your microphone and convert detected speech into text. It listens continuously, monitoring audio levels and sending speech for conversion to text when the audio level drops, such as at the end of a spoken phrase.

### Task - convert speech to text

1. Create a new Python app on your computer in a folder named `smart-timer` with a single file called `app.py` and a Python virtual environment.

1. Install the Pip package for the speech services. Ensure you are installing this from a terminal with the virtual environment activated.

    ```sh
    pip install azure-cognitiveservices-speech
    ```

    > ⚠️ If you encounter the following error:
    >
    > ```output
    > ERROR: Could not find a version that satisfies the requirement azure-cognitiveservices-speech (from versions: none)
    > ERROR: No matching distribution found for azure-cognitiveservices-speech
    > ```
    >
    > You will need to update Pip. Use the following command to update it, then try installing the package again:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. Add the following imports to the `app.py` file:

    ```python
    import requests
    import time
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer
    ```

    These imports include classes used for speech recognition.

1. Add the following code to declare some configuration:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'

    recognizer_config = SpeechConfig(subscription=speech_api_key,
                                     region=location,
                                     speech_recognition_language=language)
    ```

    Replace `<key>` with the API key for your speech service. Replace `<location>` with the region you selected when creating the speech service resource.

    Replace `<language>` with the locale name for the language you will be speaking, such as `en-GB` for English or `zn-HK` for Cantonese. You can find a list of supported languages and their locale names in the [Language and voice support documentation on Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    This configuration is used to create a `SpeechConfig` object that configures the speech services.

1. Add the following code to create a speech recognizer:

    ```python
    recognizer = SpeechRecognizer(speech_config=recognizer_config)
    ```

1. The speech recognizer operates on a background thread, listening for audio and converting detected speech into text. You can retrieve the text using a callback function—a function you define and pass to the recognizer. Each time speech is detected, the callback is triggered. Add the following code to define a callback, pass it to the recognizer, and define a function to process the text by writing it to the console:

    ```python
    def process_text(text):
        print(text)

    def recognized(args):
        process_text(args.result.text)
    
    recognizer.recognized.connect(recognized)
    ```

1. The recognizer only begins listening when explicitly started. Add the following code to start the recognition process. This runs in the background, so your application will also need an infinite loop that sleeps to keep the application running.

    ```python
    recognizer.start_continuous_recognition()

    while True:
        time.sleep(1)
    ```

1. Run this app. Speak into your microphone, and the audio converted to text will be displayed in the console.

    ```output
    (.venv) ➜  smart-timer python3 app.py
    Hello world.
    Welcome to IoT for beginners.
    ```

    Experiment with different types of sentences, including sentences where words sound the same but have different meanings. For example, if you are speaking in English, say "I want to buy two bananas and an apple too," and observe how it correctly uses "to," "two," and "too" based on the context of the sentence, not just the sound.

> 💁 You can find this code in the [code-speech-to-text/virtual-iot-device](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/virtual-iot-device) folder.

😀 Your speech-to-text program was a success!

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we aim for accuracy, please note that automated translations may include errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is advised. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.