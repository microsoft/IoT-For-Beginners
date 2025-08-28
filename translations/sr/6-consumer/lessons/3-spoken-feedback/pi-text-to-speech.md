<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "606f3af1c78e3741e48ce77c31cea626",
  "translation_date": "2025-08-28T12:45:24+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/pi-text-to-speech.md",
  "language_code": "sr"
}
-->
# Претварање текста у говор - Raspberry Pi

У овом делу лекције, написаћете код за претварање текста у говор користећи услугу за говор.

## Претварање текста у говор помоћу услуге за говор

Текст се може послати услузи за говор преко REST API-ја како би се добио говор у облику аудио фајла који се може репродуковати на вашем IoT уређају. Приликом захтева за говор, потребно је навести глас који ће се користити, јер се говор може генерисати помоћу различитих гласова.

Сваки језик подржава низ различитих гласова, а можете послати REST захтев услузи за говор како бисте добили листу подржаних гласова за сваки језик.

### Задатак - добијање гласа

1. Отворите пројекат `smart-timer` у VS Code-у.

1. Додајте следећи код изнад функције `say` како бисте затражили листу гласова за одређени језик:

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

    Овај код дефинише функцију под називом `get_voice` која користи услугу за говор да би добила листу гласова. Затим проналази први глас који одговара језику који се користи.

    Ова функција се затим позива како би се сачувао први глас, а име гласа се исписује у конзолу. Овај глас се може затражити једном, а вредност се може користити за сваки позив за претварање текста у говор.

    > 💁 Комплетну листу подржаних гласова можете пронаћи у [документацији о подршци за језике и гласове на Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). Ако желите да користите одређени глас, можете уклонити ову функцију и директно унети име гласа из ове документације. На пример:
    >
    > ```python
    > voice = 'hi-IN-SwaraNeural'
    > ```

### Задатак - претварање текста у говор

1. Испод овога, дефинишите константу за аудио формат који ће се преузети из услуга за говор. Када захтевате аудио, можете га добити у различитим форматима.

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'
    ```

    Формат који можете користити зависи од вашег хардвера. Ако добијете грешке `Invalid sample rate` приликом репродукције аудио записа, промените ово на другу вредност. Листу подржаних вредности можете пронаћи у [документацији о REST API-ју за текст у говор на Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/rest-text-to-speech?WT.mc_id=academic-17441-jabenn#audio-outputs). Потребно је да користите аудио у `riff` формату, а вредности које можете испробати су `riff-16khz-16bit-mono-pcm`, `riff-24khz-16bit-mono-pcm` и `riff-48khz-16bit-mono-pcm`.

1. Испод овога, декларишите функцију под називом `get_speech` која ће претварати текст у говор користећи REST API услуге за говор:

    ```python
    def get_speech(text):
    ```

1. Унутар функције `get_speech`, дефинишите URL који ће се позвати и хедере који ће се проследити:

    ```python
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    ```

    Ово поставља хедере за коришћење генерисаног access token-а, дефинише садржај као SSML и одређује потребан аудио формат.

1. Испод овога, дефинишите SSML који ће се послати REST API-ју:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

    Овај SSML поставља језик и глас који ће се користити, заједно са текстом који ће се претворити.

1. На крају, додајте код у овој функцији који ће направити REST захтев и вратити бинарне аудио податке:

    ```python
    response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    return io.BytesIO(response.content)
    ```

### Задатак - репродукција аудио записа

1. Испод функције `get_speech`, дефинишите нову функцију за репродукцију аудио записа који је враћен из REST API позива:

    ```python
    def play_speech(speech):
    ```

1. Променљива `speech` која се прослеђује овој функцији биће бинарни аудио подаци враћени из REST API-ја. Користите следећи код да отворите ово као wave фајл и проследите га PyAudio-у за репродукцију:

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

    Овај код користи PyAudio stream, исто као и за снимање звука. Разлика је у томе што је stream овде подешен као излазни stream, а подаци се читају из аудио података и шаљу у stream.

    Уместо да се детаљи о stream-у, као што је sample rate, тврдо кодирају, они се читају из аудио података.

1. Замените садржај функције `say` следећим:

    ```python
    speech = get_speech(text)
    play_speech(speech)
    ```

    Овај код претвара текст у говор као бинарне аудио податке и репродукује аудио.

1. Покрените апликацију и уверите се да је функцијска апликација такође покренута. Подесите неке тајмере и чућете гласовни одговор који каже да је ваш тајмер подешен, а затим још један гласовни одговор када тајмер истекне.

    Ако добијете грешке `Invalid sample rate`, промените `playback_format` као што је горе описано.

> 💁 Овај код можете пронаћи у [code-spoken-response/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/pi) фасцикли.

😀 Ваш програм за тајмер је био успешан!

---

**Одрицање од одговорности**:  
Овај документ је преведен коришћењем услуге за превођење помоћу вештачке интелигенције [Co-op Translator](https://github.com/Azure/co-op-translator). Иако се трудимо да обезбедимо тачност, молимо вас да имате у виду да аутоматски преводи могу садржати грешке или нетачности. Оригинални документ на његовом изворном језику треба сматрати ауторитативним извором. За критичне информације препоручује се професионални превод од стране људи. Не преузимамо одговорност за било каква погрешна тумачења или неспоразуме који могу настати услед коришћења овог превода.