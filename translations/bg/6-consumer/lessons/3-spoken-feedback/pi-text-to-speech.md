<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "606f3af1c78e3741e48ce77c31cea626",
  "translation_date": "2025-08-28T09:03:39+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/pi-text-to-speech.md",
  "language_code": "bg"
}
-->
# Текст към реч - Raspberry Pi

В тази част от урока ще напишете код за преобразуване на текст в реч, използвайки услугата за реч.

## Преобразуване на текст в реч с помощта на услугата за реч

Текстът може да бъде изпратен до услугата за реч чрез REST API, за да се получи реч като аудио файл, който може да бъде възпроизведен на вашето IoT устройство. При заявка за реч трябва да предоставите гласа, който да се използва, тъй като речта може да бъде генерирана с различни гласове.

Всеки език поддържа набор от различни гласове, и можете да направите REST заявка към услугата за реч, за да получите списък с поддържаните гласове за всеки език.

### Задача - получаване на глас

1. Отворете проекта `smart-timer` в VS Code.

1. Добавете следния код над функцията `say`, за да заявите списък с гласове за даден език:

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

    Този код дефинира функция, наречена `get_voice`, която използва услугата за реч, за да получи списък с гласове. След това намира първия глас, който съответства на използвания език.

    Тази функция се извиква, за да съхрани първия глас, а името на гласа се отпечатва в конзолата. Този глас може да бъде заявен веднъж и стойността да се използва за всяко повикване за преобразуване на текст в реч.

    > 💁 Можете да получите пълния списък с поддържани гласове от [документацията за поддръжка на езици и гласове в Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). Ако искате да използвате конкретен глас, можете да премахнете тази функция и да зададете твърдо името на гласа от тази документация. Например:
    >
    > ```python
    > voice = 'hi-IN-SwaraNeural'
    > ```

### Задача - преобразуване на текст в реч

1. Под този код дефинирайте константа за аудио формата, който ще бъде извлечен от услугите за реч. Когато заявявате аудио, можете да го направите в различни формати.

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'
    ```

    Форматът, който можете да използвате, зависи от вашия хардуер. Ако получите грешки като `Invalid sample rate` при възпроизвеждане на аудиото, променете това на друга стойност. Можете да намерите списъка с поддържани стойности в [документацията за REST API за текст към реч в Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/rest-text-to-speech?WT.mc_id=academic-17441-jabenn#audio-outputs). Ще трябва да използвате аудио във формат `riff`, а стойностите, които да опитате, са `riff-16khz-16bit-mono-pcm`, `riff-24khz-16bit-mono-pcm` и `riff-48khz-16bit-mono-pcm`.

1. Под този код декларирайте функция, наречена `get_speech`, която ще преобразува текста в реч, използвайки REST API на услугата за реч:

    ```python
    def get_speech(text):
    ```

1. Във функцията `get_speech` дефинирайте URL адреса за извикване и заглавията за предаване:

    ```python
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    ```

    Това задава заглавията за използване на генериран токен за достъп, задава съдържанието като SSML и дефинира необходимия аудио формат.

1. Под този код дефинирайте SSML, който да бъде изпратен до REST API:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

    Този SSML задава езика и гласа, който да се използва, заедно с текста за преобразуване.

1. Накрая добавете код в тази функция, за да направите REST заявката и да върнете двоичните аудио данни:

    ```python
    response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    return io.BytesIO(response.content)
    ```

### Задача - възпроизвеждане на аудио

1. Под функцията `get_speech` дефинирайте нова функция за възпроизвеждане на аудиото, върнато от REST API заявката:

    ```python
    def play_speech(speech):
    ```

1. `speech`, предаден на тази функция, ще бъде двоичните аудио данни, върнати от REST API. Използвайте следния код, за да отворите това като wave файл и да го предадете на PyAudio за възпроизвеждане на аудиото:

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

    Този код използва PyAudio поток, подобно на заснемането на аудио. Разликата тук е, че потокът е зададен като изходен поток, а данните се четат от аудио данните и се предават на потока.

    Вместо твърдо задаване на детайлите на потока, като например честотата на семплиране, те се четат от аудио данните.

1. Заменете съдържанието на функцията `say` със следното:

    ```python
    speech = get_speech(text)
    play_speech(speech)
    ```

    Този код преобразува текста в реч като двоични аудио данни и възпроизвежда аудиото.

1. Стартирайте приложението и се уверете, че функцията на приложението също работи. Задайте няколко таймера и ще чуете гласов отговор, който казва, че вашият таймер е зададен, а след това друг гласов отговор, когато таймерът приключи.

    Ако получите грешки като `Invalid sample rate`, променете `playback_format`, както е описано по-горе.

> 💁 Можете да намерите този код в папката [code-spoken-response/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/pi).

😀 Вашата програма за таймер беше успешна!

---

**Отказ от отговорност**:  
Този документ е преведен с помощта на AI услуга за превод [Co-op Translator](https://github.com/Azure/co-op-translator). Въпреки че се стремим към точност, моля, имайте предвид, че автоматизираните преводи може да съдържат грешки или неточности. Оригиналният документ на неговия роден език трябва да се счита за авторитетен източник. За критична информация се препоръчва професионален човешки превод. Ние не носим отговорност за недоразумения или погрешни интерпретации, произтичащи от използването на този превод.