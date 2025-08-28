<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "606f3af1c78e3741e48ce77c31cea626",
  "translation_date": "2025-08-27T23:19:43+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/pi-text-to-speech.md",
  "language_code": "tl"
}
-->
# Text to speech - Raspberry Pi

Sa bahaging ito ng aralin, magsusulat ka ng code upang i-convert ang text sa speech gamit ang speech service.

## I-convert ang text sa speech gamit ang speech service

Ang text ay maaaring ipadala sa speech service gamit ang REST API upang makakuha ng audio file na maaaring i-play sa iyong IoT device. Kapag humihiling ng speech, kailangan mong tukuyin ang boses na gagamitin dahil ang speech ay maaaring mabuo gamit ang iba't ibang boses.

Ang bawat wika ay sumusuporta sa iba't ibang uri ng boses, at maaari kang gumawa ng REST request sa speech service upang makuha ang listahan ng mga suportadong boses para sa bawat wika.

### Gawain - kumuha ng boses

1. Buksan ang proyekto na `smart-timer` sa VS Code.

1. Idagdag ang sumusunod na code sa itaas ng `say` function upang humiling ng listahan ng mga boses para sa isang wika:

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

    Ang code na ito ay nagtatakda ng isang function na tinatawag na `get_voice` na gumagamit ng speech service upang makuha ang listahan ng mga boses. Pagkatapos nito, hahanapin ang unang boses na tumutugma sa wika na ginagamit.

    Ang function na ito ay tatawagin upang i-store ang unang boses, at ang pangalan ng boses ay ipapakita sa console. Ang boses na ito ay maaaring hilingin nang isang beses at ang halaga ay maaaring gamitin para sa bawat tawag upang i-convert ang text sa speech.

    > 💁 Maaari mong makuha ang buong listahan ng mga suportadong boses mula sa [Language and voice support documentation on Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). Kung nais mong gumamit ng partikular na boses, maaari mong alisin ang function na ito at direktang ilagay ang pangalan ng boses mula sa dokumentasyong ito. Halimbawa:
    >
    > ```python
    > voice = 'hi-IN-SwaraNeural'
    > ```

### Gawain - i-convert ang text sa speech

1. Sa ibaba nito, magtakda ng constant para sa audio format na kukunin mula sa speech services. Kapag humihiling ng audio, maaari itong gawin sa iba't ibang format.

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'
    ```

    Ang format na maaari mong gamitin ay nakadepende sa iyong hardware. Kung makakakuha ka ng `Invalid sample rate` errors kapag pinapatugtog ang audio, palitan ito ng ibang halaga. Maaari mong makita ang listahan ng mga suportadong halaga sa [Text to speech REST API documentation on Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/rest-text-to-speech?WT.mc_id=academic-17441-jabenn#audio-outputs). Kailangan mong gumamit ng `riff` format audio, at ang mga halagang maaaring subukan ay `riff-16khz-16bit-mono-pcm`, `riff-24khz-16bit-mono-pcm`, at `riff-48khz-16bit-mono-pcm`.

1. Sa ibaba nito, magdeklara ng function na tinatawag na `get_speech` na magko-convert ng text sa speech gamit ang speech service REST API:

    ```python
    def get_speech(text):
    ```

1. Sa loob ng `get_speech` function, tukuyin ang URL na tatawagin at ang headers na ipapasa:

    ```python
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    ```

    Itinatakda nito ang headers upang gumamit ng generated access token, itinatakda ang content sa SSML, at tinutukoy ang audio format na kailangan.

1. Sa ibaba nito, tukuyin ang SSML na ipapadala sa REST API:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

    Ang SSML na ito ay nagtatakda ng wika at boses na gagamitin, kasama ang text na iko-convert.

1. Sa wakas, magdagdag ng code sa function na ito upang gumawa ng REST request at ibalik ang binary audio data:

    ```python
    response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    return io.BytesIO(response.content)
    ```

### Gawain - i-play ang audio

1. Sa ibaba ng `get_speech` function, magtakda ng bagong function upang i-play ang audio na ibinalik ng REST API call:

    ```python
    def play_speech(speech):
    ```

1. Ang `speech` na ipinasa sa function na ito ay ang binary audio data na ibinalik mula sa REST API. Gamitin ang sumusunod na code upang buksan ito bilang wave file at ipasa ito sa PyAudio upang i-play ang audio:

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

    Ang code na ito ay gumagamit ng PyAudio stream, katulad ng pagkuha ng audio. Ang pagkakaiba dito ay ang stream ay itinakda bilang output stream, at ang data ay binabasa mula sa audio data at ipinapasa sa stream.

    Sa halip na direktang itakda ang mga detalye ng stream tulad ng sample rate, ito ay binabasa mula sa audio data.

1. Palitan ang nilalaman ng `say` function ng sumusunod:

    ```python
    speech = get_speech(text)
    play_speech(speech)
    ```

    Ang code na ito ay nagko-convert ng text sa speech bilang binary audio data, at pinapatugtog ang audio.

1. Patakbuhin ang app, at tiyaking tumatakbo rin ang function app. Mag-set ng ilang timers, at maririnig mo ang isang spoken response na nagsasabing ang iyong timer ay na-set, at isa pang spoken response kapag natapos na ang timer.

    Kung makakakuha ka ng `Invalid sample rate` errors, palitan ang `playback_format` tulad ng inilarawan sa itaas.

> 💁 Maaari mong makita ang code na ito sa [code-spoken-response/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/pi) folder.

😀 Tagumpay ang iyong timer program!

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na maaaring magmula sa paggamit ng pagsasaling ito.