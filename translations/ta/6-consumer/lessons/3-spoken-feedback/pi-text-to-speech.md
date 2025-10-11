<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "606f3af1c78e3741e48ce77c31cea626",
  "translation_date": "2025-10-11T12:08:53+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/pi-text-to-speech.md",
  "language_code": "ta"
}
-->
# உரையை பேச்சாக மாற்றுதல் - ராஸ்பெர்ரி பை

இந்த பாடத்தின் இந்த பகுதியில், உரையை பேச்சாக மாற்றுவதற்கான குறியீட்டை நீங்கள் எழுதுவீர்கள், பேச்சு சேவையைப் பயன்படுத்தி.

## பேச்சு சேவையைப் பயன்படுத்தி உரையை பேச்சாக மாற்றுதல்

உரையை REST API மூலம் பேச்சு சேவைக்கு அனுப்பி, IoT சாதனத்தில் மீண்டும் இயக்கக்கூடிய ஆடியோ கோப்பாக பேச்சை பெறலாம். பேச்சை கோரும்போது, பயன்படுத்த வேண்டிய குரலை வழங்க வேண்டும், ஏனெனில் பல்வேறு குரல்களைப் பயன்படுத்தி பேச்சு உருவாக்க முடியும்.

ஒவ்வொரு மொழியும் பல்வேறு குரல்களை ஆதரிக்கிறது, மேலும் ஒவ்வொரு மொழிக்குமான ஆதரிக்கப்படும் குரல்களின் பட்டியலைப் பெற பேச்சு சேவைக்கு REST கோரிக்கையைச் செய்யலாம்.

### பணிகள் - ஒரு குரலைப் பெறுதல்

1. VS Code-ல் `smart-timer` திட்டத்தைத் திறக்கவும்.

1. ஒரு மொழிக்கான குரல்களின் பட்டியலைக் கோர `say` செயல்பாட்டின் மேல் பின்வரும் குறியீட்டைச் சேர்க்கவும்:

    ```python
    def get_voice():
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/voices/list'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token()
        }
    
        response = requests.get(url, headers=headers)
        voices_json = json.loads(response.text)
    
        first_voice = next(x for x in voices_json if x['Locale'].lower() == language.lower() and x['VoiceType'] == 'Neural')
        return first_voice['ShortName']
    
    voice = get_voice()
    print(f'Using voice {voice}')
    ```

    இந்த குறியீடு `get_voice` எனப்படும் ஒரு செயல்பாட்டை வரையறுக்கிறது, இது பேச்சு சேவையைப் பயன்படுத்தி குரல்களின் பட்டியலைப் பெறுகிறது. பின்னர் பயன்படுத்தப்படும் மொழியைப் பொருந்தும் முதல் குரலை இது கண்டறிகிறது.

    இந்த செயல்பாடு பின்னர் அழைக்கப்பட்டு முதல் குரலை சேமிக்கிறது, மேலும் குரல் பெயர் கன்சோலில் அச்சிடப்படுகிறது. இந்த குரலை ஒருமுறை கோரிக்கையிடலாம், மேலும் உரையை பேச்சாக மாற்றுவதற்கான ஒவ்வொரு அழைப்பிற்கும் இந்த மதிப்பை பயன்படுத்தலாம்.

    > 💁 ஆதரிக்கப்படும் குரல்களின் முழு பட்டியலை [Microsoft Docs-ல் உள்ள மொழி மற்றும் குரல் ஆதரவு ஆவணத்தில்](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech) பெறலாம். நீங்கள் குறிப்பிட்ட ஒரு குரலைப் பயன்படுத்த விரும்பினால், இந்த செயல்பாட்டை நீக்கி, இந்த ஆவணத்தில் உள்ள குரல் பெயரை குரலாக கடினமாக குறியீட்டில் சேர்க்கலாம். உதாரணமாக:
    >
    > ```python
    > voice = 'hi-IN-SwaraNeural'
    > ```

### பணிகள் - உரையை பேச்சாக மாற்றுதல்

1. இதற்கு கீழே, பேச்சு சேவைகளில் இருந்து பெறப்படும் ஆடியோ வடிவத்திற்கான ஒரு மாறியை வரையறுக்கவும். நீங்கள் ஆடியோவை கோரும்போது, பல்வேறு வடிவங்களில் அதைச் செய்யலாம்.

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'
    ```

    நீங்கள் பயன்படுத்தக்கூடிய வடிவம் உங்கள் ஹார்ட்வேரில் निर्भरமாக இருக்கும். நீங்கள் ஆடியோவை இயக்கும்போது `Invalid sample rate` பிழைகள் கிடைத்தால், இதை வேறு மதிப்பாக மாற்றவும். ஆதரிக்கப்படும் மதிப்புகளின் பட்டியலை [Microsoft Docs-ல் உள்ள Text to speech REST API ஆவணத்தில்](https://docs.microsoft.com/azure/cognitive-services/speech-service/rest-text-to-speech?WT.mc_id=academic-17441-jabenn#audio-outputs) காணலாம். நீங்கள் `riff` வடிவ ஆடியோவைப் பயன்படுத்த வேண்டும், மேலும் முயற்சிக்க வேண்டிய மதிப்புகள் `riff-16khz-16bit-mono-pcm`, `riff-24khz-16bit-mono-pcm` மற்றும் `riff-48khz-16bit-mono-pcm`.

1. இதற்கு கீழே, பேச்சு சேவையின் REST API-யைப் பயன்படுத்தி உரையை பேச்சாக மாற்றும் `get_speech` எனப்படும் ஒரு செயல்பாட்டை வரையறுக்கவும்:

    ```python
    def get_speech(text):
    ```

1. `get_speech` செயல்பாட்டில், அழைக்க வேண்டிய URL மற்றும் அனுப்ப வேண்டிய தலைப்புகளை வரையறுக்கவும்:

    ```python
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    ```

    இது உருவாக்கப்பட்ட அணுகல் டோக்கனைப் பயன்படுத்த தலைப்புகளை அமைக்கிறது, உள்ளடக்கத்தை SSML ஆக அமைக்கிறது மற்றும் தேவையான ஆடியோ வடிவத்தை வரையறுக்கிறது.

1. இதற்கு கீழே, REST API-க்கு அனுப்ப வேண்டிய SSML-ஐ வரையறுக்கவும்:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

    இந்த SSML மொழி மற்றும் பயன்படுத்த வேண்டிய குரலை அமைக்கிறது, மேலும் மாற்ற வேண்டிய உரையை சேர்க்கிறது.

1. இறுதியாக, REST கோரிக்கையைச் செய்யவும், பைனரி ஆடியோ தரவுகளைத் திருப்பவும் இந்த செயல்பாட்டில் குறியீட்டைச் சேர்க்கவும்:

    ```python
    response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    return io.BytesIO(response.content)
    ```

### பணிகள் - ஆடியோவை இயக்குதல்

1. `get_speech` செயல்பாட்டின் கீழே, REST API அழைப்பால் திருப்பப்பட்ட ஆடியோவை இயக்க புதிய செயல்பாட்டை வரையறுக்கவும்:

    ```python
    def play_speech(speech):
    ```

1. இந்த செயல்பாட்டிற்கு அனுப்பப்படும் `speech` என்பது REST API மூலம் திருப்பப்பட்ட பைனரி ஆடியோ தரவாக இருக்கும். இதை ஒரு wave கோப்பாகத் திறக்கவும், மேலும் PyAudio-க்கு அனுப்பி ஆடியோவை இயக்க பின்வரும் குறியீட்டை பயன்படுத்தவும்:

    ```python
    def play_speech(speech):
        with wave.open(speech, 'rb') as wave_file:
            stream = audio.open(format=audio.get_format_from_width(wave_file.getsampwidth()),
                                channels=wave_file.getnchannels(),
                                rate=wave_file.getframerate(),
                                output_device_index=speaker_card_number,
                                output=True)

            data = wave_file.readframes(4096)

            while len(data) > 0:
                stream.write(data)
                data = wave_file.readframes(4096)

            stream.stop_stream()
            stream.close()
    ```

    இந்த குறியீடு PyAudio ஸ்ட்ரீமைப் பயன்படுத்துகிறது, ஆடியோவைப் பிடிப்பதற்கான ஸ்ட்ரீமைப் போலவே. இங்கு வேறுபாடு என்னவென்றால் ஸ்ட்ரீம் output ஸ்ட்ரீமாக அமைக்கப்படுகிறது, மேலும் ஆடியோ தரவிலிருந்து தரவுகள் வாசிக்கப்பட்டு ஸ்ட்ரீமுக்கு அனுப்பப்படுகிறது.

    ஸ்ட்ரீமின் விவரங்களை (உதாரணமாக, sample rate) கடினமாக குறியீட்டில் சேர்க்காமல், இது ஆடியோ தரவிலிருந்து வாசிக்கப்படுகிறது.

1. `say` செயல்பாட்டின் உள்ளடக்கத்தை பின்வரும் குறியீட்டுடன் மாற்றவும்:

    ```python
    speech = get_speech(text)
    play_speech(speech)
    ```

    இந்த குறியீடு உரையை பைனரி ஆடியோ தரவாக மாற்றுகிறது, மேலும் ஆடியோவை இயக்குகிறது.

1. செயலியை இயக்கவும், செயலி செயல்பாட்டும் இயக்கப்படுவதை உறுதிப்படுத்தவும். சில டைமர்களை அமைக்கவும், மேலும் உங்கள் டைமர் அமைக்கப்பட்டதாகவும், பின்னர் டைமர் முடிந்ததும் மற்றொரு பேச்சு பதிலாகவும் நீங்கள் கேட்பீர்கள்.

    நீங்கள் `Invalid sample rate` பிழைகளைப் பெறினால், மேலே விவரிக்கப்பட்ட `playback_format`-ஐ மாற்றவும்.

> 💁 இந்த குறியீட்டை [code-spoken-response/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/pi) கோப்புறையில் காணலாம்.

😀 உங்கள் டைமர் செயலி வெற்றிகரமாக முடிந்தது!

---

**குறிப்பு**:  
இந்த ஆவணம் [Co-op Translator](https://github.com/Azure/co-op-translator) என்ற AI மொழிபெயர்ப்பு சேவையைப் பயன்படுத்தி மொழிபெயர்க்கப்பட்டுள்ளது. நாங்கள் துல்லியத்திற்காக முயற்சிக்கின்றோம், ஆனால் தானியங்கி மொழிபெயர்ப்புகளில் பிழைகள் அல்லது தவறான தகவல்கள் இருக்கக்கூடும் என்பதை கவனத்தில் கொள்ளவும். அதன் தாய்மொழியில் உள்ள மூல ஆவணம் அதிகாரப்பூர்வ ஆதாரமாக கருதப்பட வேண்டும். முக்கியமான தகவல்களுக்கு, தொழில்முறை மனித மொழிபெயர்ப்பு பரிந்துரைக்கப்படுகிறது. இந்த மொழிபெயர்ப்பைப் பயன்படுத்துவதால் ஏற்படும் எந்த தவறான புரிதல்கள் அல்லது தவறான விளக்கங்களுக்கு நாங்கள் பொறுப்பல்ல.