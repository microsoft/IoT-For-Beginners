<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c0550b254b9ba2539baf1e6bb5fc05f8",
  "translation_date": "2025-10-11T12:23:18+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/virtual-device-speech-to-text.md",
  "language_code": "ta"
}
-->
# உரையை உரையாடல் மூலம் மாற்றுதல் - மெய்நிகர் IoT சாதனம்

இந்த பாடத்தின் இந்த பகுதியில், உங்கள் மைக்ரோஃபோனில் பிடிக்கப்பட்ட உரையை உரையாக மாற்றுவதற்கான குறியீட்டை எழுதுவீர்கள்.

## உரையை உரையாடல் மூலம் மாற்றுதல்

Windows, Linux மற்றும் macOS-ல், Speech Services Python SDK உங்கள் மைக்ரோஃபோனைக் கேட்டு, கண்டறியப்பட்ட எந்த உரையையும் உரையாக மாற்ற பயன்படுத்தலாம். இது தொடர்ந்து கேட்கும், ஒலியின் அளவுகளை கண்டறிந்து, உரை மாற்றத்திற்காக ஒலியை அனுப்பும், குறிப்பாக உரையின் ஒரு தொகுதி முடிவடையும் போது.

### பணிகள் - உரையை உரையாடல் மூலம் மாற்றுதல்

1. உங்கள் கணினியில் `smart-timer` என்ற கோப்பகத்தில் ஒரு புதிய Python பயன்பாட்டை உருவாக்கி, `app.py` என்ற ஒரு கோப்புடன் Python மெய்நிகர் சூழலை உருவாக்கவும்.

1. Speech Services-க்கு தேவையான Pip தொகுப்பை நிறுவவும். மெய்நிகர் சூழல் செயல்படுத்தப்பட்டுள்ள டெர்மினலில் இருந்து இதை நிறுவுகிறீர்கள் என்பதை உறுதிப்படுத்தவும்.

    ```sh
    pip install azure-cognitiveservices-speech
    ```

    > ⚠️ நீங்கள் கீழே உள்ள பிழையை சந்தித்தால்:
    >
    > ```output
    > ERROR: Could not find a version that satisfies the requirement azure-cognitiveservices-speech (from versions: none)
    > ERROR: No matching distribution found for azure-cognitiveservices-speech
    > ```
    >
    > நீங்கள் Pip-ஐ புதுப்பிக்க வேண்டும். இதை கீழே உள்ள கட்டளையைப் பயன்படுத்தி செய்யவும், பின்னர் தொகுப்பை மீண்டும் நிறுவ முயற்சிக்கவும்.
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. `app.py` கோப்பில் கீழே உள்ள imports-ஐ சேர்க்கவும்:

    ```python
    import requests
    import time
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer
    ```

    இது உரையை அடையாளம் காண பயன்படுத்தப்படும் சில வகுப்புகளை இறக்குமதி செய்கிறது.

1. சில கட்டமைப்புகளை அறிவிக்க கீழே உள்ள குறியீட்டை சேர்க்கவும்:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'

    recognizer_config = SpeechConfig(subscription=speech_api_key,
                                     region=location,
                                     speech_recognition_language=language)
    ```

    `<key>` ஐ உங்கள் Speech Service API key-யுடன் மாற்றவும். `<location>` ஐ Speech Service resource உருவாக்கிய இடத்துடன் மாற்றவும்.

    `<language>` ஐ நீங்கள் பேசும் மொழிக்கான locale பெயருடன் மாற்றவும், உதாரணமாக ஆங்கிலத்திற்கான `en-GB`, அல்லது காந்தோனீஸிற்கான `zn-HK`. Microsoft Docs-ல் உள்ள [மொழி மற்றும் குரல் ஆதரவு ஆவணத்தில்](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) ஆதரவு மொழிகள் மற்றும் அவற்றின் locale பெயர்களின் பட்டியலை காணலாம்.

    இந்த கட்டமைப்பு `SpeechConfig` பொருளை உருவாக்க பயன்படுத்தப்படும், இது Speech Services-ஐ கட்டமைக்க உதவும்.

1. ஒரு Speech Recognizer உருவாக்க கீழே உள்ள குறியீட்டை சேர்க்கவும்:

    ```python
    recognizer = SpeechRecognizer(speech_config=recognizer_config)
    ```

1. Speech Recognizer பின்னணி திரையில் இயங்கும், ஒலியை கேட்டு, அதில் உள்ள உரையை உரையாக மாற்றும். உரையை பெற நீங்கள் callback function-ஐ பயன்படுத்தலாம் - recognizer-க்கு நீங்கள் வரையறுத்து வழங்கும் ஒரு செயல்பாடு. ஒவ்வொரு முறையும் உரை கண்டறியப்படும் போது callback அழைக்கப்படும். callback-ஐ வரையறுக்கவும், recognizer-க்கு இதை வழங்கவும், மேலும் உரையை செயல்படுத்த ஒரு செயல்பாட்டை வரையறுக்கவும், அதை console-ல் எழுதவும்:

    ```python
    def process_text(text):
        print(text)

    def recognized(args):
        process_text(args.result.text)
    
    recognizer.recognized.connect(recognized)
    ```

1. Recognizer கேட்க தொடங்கும் போது மட்டுமே செயல்படும். Recognition-ஐ தொடங்க கீழே உள்ள குறியீட்டை சேர்க்கவும். இது பின்னணி திரையில் இயங்கும், எனவே உங்கள் பயன்பாட்டில் ஒரு முடிவில்லாத loop மற்றும் sleep தேவைப்படும், பயன்பாட்டை இயக்க வைத்திருக்க.

    ```python
    recognizer.start_continuous_recognition()

    while True:
        time.sleep(1)
    ```

1. இந்த பயன்பாட்டை இயக்கவும். உங்கள் மைக்ரோஃபோனில் பேசவும், உரையாக மாற்றப்பட்ட ஒலி console-ல் வெளியிடப்படும்.

    ```output
    (.venv) ➜  smart-timer python3 app.py
    Hello world.
    Welcome to IoT for beginners.
    ```

    வெவ்வேறு வகையான வாக்கியங்களை முயற்சிக்கவும், மேலும் ஒரே ஒலியைக் கொண்ட ஆனால் வேறுபட்ட அர்த்தங்களை கொண்ட வாக்கியங்களை முயற்சிக்கவும். உதாரணமாக, நீங்கள் ஆங்கிலத்தில் பேசினால், 'I want to buy two bananas and an apple too' என்று சொல்லவும், மற்றும் அது "to", "two" மற்றும் "too"-ஐ அதன் ஒலியைக் கொண்டே அல்ல, அதன் சூழலின் அடிப்படையில் சரியாக பயன்படுத்துவது எப்படி என்பதை கவனிக்கவும்.

> 💁 இந்த குறியீட்டை [code-speech-to-text/virtual-iot-device](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/virtual-iot-device) கோப்பகத்தில் காணலாம்.

😀 உங்கள் உரையை உரையாடல் மூலம் மாற்றும் செயலி வெற்றிகரமாக முடிந்தது!

---

**குறிப்பு**:  
இந்த ஆவணம் [Co-op Translator](https://github.com/Azure/co-op-translator) என்ற AI மொழிபெயர்ப்பு சேவையை பயன்படுத்தி மொழிபெயர்க்கப்பட்டுள்ளது. நாங்கள் துல்லியத்திற்காக முயற்சிக்கின்றோம், ஆனால் தானியங்கி மொழிபெயர்ப்புகளில் பிழைகள் அல்லது தவறான தகவல்கள் இருக்கக்கூடும் என்பதை தயவுசெய்து கவனத்தில் கொள்ளுங்கள். அதன் தாய்மொழியில் உள்ள மூல ஆவணம் அதிகாரப்பூர்வ ஆதாரமாக கருதப்பட வேண்டும். முக்கியமான தகவல்களுக்கு, தொழில்முறை மனித மொழிபெயர்ப்பு பரிந்துரைக்கப்படுகிறது. இந்த மொழிபெயர்ப்பைப் பயன்படுத்துவதால் ஏற்படும் எந்த தவறான புரிதல்கள் அல்லது தவறான விளக்கங்களுக்கு நாங்கள் பொறுப்பல்ல.