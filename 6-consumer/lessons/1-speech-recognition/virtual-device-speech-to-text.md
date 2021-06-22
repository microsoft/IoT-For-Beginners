# Speech to text - Virtual IoT device

In this part of the lesson, you will write code to convert speech captured from your microphone to text using the speech service.

## Convert speech to text

On Windows, Linux, and macOS, the speech services Python SDK can be used to listen to your microphone and convert any speech that is detected to text. It will listen continuously, detecting the audio levels and sending the speech for conversion to text when the audio level drops, such as at the end of a block of speech.

### Task - convert speech to text

1. Create a new Python app on your computer in a folder called `smart-timer` with a single file called `app.py` and a Python virtual environment.

1. Install the Pip package for the speech services. Make sure you are installing this from a terminal with the virtual environment activated.

    ```sh
    pip install azure-cognitiveservices-speech
    ```

    > ⚠️ If you get the following error:
    >
    > ```output
    > ERROR: Could not find a version that satisfies the requirement azure-cognitiveservices-speech (from versions: none)
    > ERROR: No matching distribution found for azure-cognitiveservices-speech
    > ```
    >
    > You will need to update Pip. Do this with the following command, then try to install the package again
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. Add the following imports to the `app,py` file:

    ```python
    import time
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer
    ```

    This imports some classes used to recognize speech.

1. Add the following code to declare some configuration:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'

    recognizer_config = SpeechConfig(subscription=speech_api_key,
                                     region=location,
                                     speech_recognition_language=language)
    ```

    Replace `<key>` with the API key for your speech service. Replace `<location>` with the location you used when you created the speech service resource.

    Replace `<language>` with the locale name for language you will be speaking in, for example `en-GB` for English, or `zn-HK` for Cantonese. You can find a list of the supported languages and their locale names in the [Language and voice support documentation on Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    This configuration is then used to create a `SpeechConfig` object that will be used to configure the speech services.

1. Add the following code to create a speech recognizer:

    ```python
    recognizer = SpeechRecognizer(speech_config=recognizer_config)
    ```

1. The speech recognizer runs on a background thread, listening for audio and converting any speech in it to text. You can get the text using a callback function - a function you define and pass to the recognizer. Every time speech is detected, the callback is called. Add the following code to define a callback that prints the text to the console, and pass this callback to the recognizer:

    ```python
    def recognized(args):
        print(args.result.text)
    
    recognizer.recognized.connect(recognized)
    ```

1. The recognizer only starts listening when you explicitly start it. Add the following code to start the recognition. This runs in the background, so your application will also need an infinite loop that sleeps to keep the application running.

    ```python
    recognizer.start_continuous_recognition()

    while True:
        time.sleep(1)
    ```

1. Run this app. Speak into your microphone and the audio converted to text will be output to the console.

    ```output
    (.venv) ➜  smart-timer python3 app.py
    Hello world.
    Welcome to IoT for beginners.
    ```

    Try different types of sentences, along with sentences where words sound the same but have different meanings. For example, if you are speaking in English, say 'I want to buy two bananas and an apple too', and notice how it will use the correct to, two and too based on the context of the word, not just it's sound.

> 💁 You can find this code in the [code-speech-to-text/virtual-iot-device](code-speech-to-text/virtual-iot-device) folder.

😀 Your speech to text program was a success!
