<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c0550b254b9ba2539baf1e6bb5fc05f8",
  "translation_date": "2025-11-18T19:28:49+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/virtual-device-speech-to-text.md",
  "language_code": "pcm"
}
-->
# Tok to text - Virtual IoT device

For dis part of di lesson, you go write code wey go change tok wey microphone capture to text using di speech service.

## Change tok to text

For Windows, Linux, and macOS, di speech services Python SDK fit dey use to listen to your microphone and change any tok wey e detect to text. E go dey listen steady, dey check di audio level and send di tok for conversion to text when di audio level go down, like when person finish one block of tok.

### Task - change tok to text

1. Create new Python app for your computer inside one folder wey you go call `smart-timer` with one file wey you go call `app.py` and one Python virtual environment.

1. Install di Pip package for di speech services. Make sure say you dey install am from terminal wey di virtual environment don activate.

    ```sh
    pip install azure-cognitiveservices-speech
    ```

    > ⚠️ If you see dis error:
    >
    > ```output
    > ERROR: Could not find a version that satisfies the requirement azure-cognitiveservices-speech (from versions: none)
    > ERROR: No matching distribution found for azure-cognitiveservices-speech
    > ```
    >
    > You go need update Pip. Use dis command do am, then try install di package again.
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. Add di imports wey dey below to di `app.py` file:

    ```python
    import requests
    import time
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer
    ```

    Dis one go import some classes wey dem dey use to recognize tok.

1. Add di code wey dey below to declare some configuration:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'

    recognizer_config = SpeechConfig(subscription=speech_api_key,
                                     region=location,
                                     speech_recognition_language=language)
    ```

    Change `<key>` to di API key for your speech service. Change `<location>` to di location wey you use when you create di speech service resource.

    Change `<language>` to di locale name for di language wey you go dey tok, like `en-GB` for English, or `zn-HK` for Cantonese. You fit find list of di languages wey dem support and di locale names for di [Language and voice support documentation for Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    Dis configuration go dey use to create `SpeechConfig` object wey go configure di speech services.

1. Add di code wey dey below to create speech recognizer:

    ```python
    recognizer = SpeechRecognizer(speech_config=recognizer_config)
    ```

1. Di speech recognizer dey run for background thread, dey listen for audio and dey change any tok wey dey inside am to text. You fit collect di text using callback function - na function wey you go define and pass to di recognizer. Anytime e detect tok, e go call di callback. Add di code wey dey below to define callback, and pass dis callback to di recognizer, plus define function wey go process di text, write am for console:

    ```python
    def process_text(text):
        print(text)

    def recognized(args):
        process_text(args.result.text)
    
    recognizer.recognized.connect(recognized)
    ```

1. Di recognizer no go start to dey listen until you start am yourself. Add di code wey dey below to start di recognition. E dey run for background, so your app go need infinite loop wey go dey sleep to keep di app dey run.

    ```python
    recognizer.start_continuous_recognition()

    while True:
        time.sleep(1)
    ```

1. Run dis app. Tok for your microphone and di audio wey dem change to text go show for di console.

    ```output
    (.venv) ➜  smart-timer python3 app.py
    Hello world.
    Welcome to IoT for beginners.
    ```

    Try different types of sentence, plus sentence wey words dey sound di same but get different meaning. For example, if you dey tok English, say 'I want to buy two bananas and an apple too', and notice how e go use di correct to, two and too based on di context of di word, no be just di sound.

> 💁 You fit find dis code for di [code-speech-to-text/virtual-iot-device](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/virtual-iot-device) folder.

😀 Your tok to text program don work well!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Disclaimer**:  
Dis dokyument don use AI transle-shon service [Co-op Translator](https://github.com/Azure/co-op-translator) do di transle-shon. Even as we dey try make am correct, abeg make you sabi say transle-shon wey machine do fit get mistake or no dey accurate well. Di original dokyument for im native language na di one wey you go take as di correct source. For important mata, e good make you use professional human transle-shon. We no go fit take blame for any misunderstanding or wrong interpretation wey fit happen because you use dis transle-shon.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->