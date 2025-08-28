<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "606f3af1c78e3741e48ce77c31cea626",
  "translation_date": "2025-08-28T16:20:48+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/pi-text-to-speech.md",
  "language_code": "uk"
}
-->
# Текст у мовлення - Raspberry Pi

У цій частині уроку ви напишете код для перетворення тексту в мовлення за допомогою служби мовлення.

## Перетворення тексту в мовлення за допомогою служби мовлення

Текст можна надіслати до служби мовлення через REST API, щоб отримати мовлення у вигляді аудіофайлу, який можна відтворити на вашому IoT-пристрої. Під час запиту мовлення необхідно вказати голос, який буде використовуватися, оскільки мовлення може бути створене за допомогою різних голосів.

Кожна мова підтримує різноманітні голоси, і ви можете зробити REST-запит до служби мовлення, щоб отримати список підтримуваних голосів для кожної мови.

### Завдання - отримати голос

1. Відкрийте проєкт `smart-timer` у VS Code.

1. Додайте наступний код над функцією `say`, щоб запросити список голосів для певної мови:

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

    Цей код визначає функцію під назвою `get_voice`, яка використовує службу мовлення для отримання списку голосів. Потім він знаходить перший голос, який відповідає мові, що використовується.

    Ця функція викликається для збереження першого голосу, а назва голосу виводиться в консоль. Цей голос можна запросити один раз, і значення використовуватиметься для кожного виклику перетворення тексту в мовлення.

    > 💁 Ви можете отримати повний список підтримуваних голосів із [документації про підтримку мов і голосів на Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). Якщо ви хочете використовувати конкретний голос, то можете видалити цю функцію і жорстко закодувати голос, використовуючи назву голосу з цієї документації. Наприклад:
    >
    > ```python
    > voice = 'hi-IN-SwaraNeural'
    > ```

### Завдання - перетворення тексту в мовлення

1. Нижче визначте константу для аудіоформату, який буде отримано зі служби мовлення. Коли ви запитуєте аудіо, це можна зробити в різних форматах.

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'
    ```

    Формат, який ви можете використовувати, залежить від вашого обладнання. Якщо ви отримуєте помилки `Invalid sample rate` під час відтворення аудіо, змініть це на інше значення. Ви можете знайти список підтримуваних значень у [документації REST API для тексту в мовлення на Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/rest-text-to-speech?WT.mc_id=academic-17441-jabenn#audio-outputs). Вам потрібно використовувати аудіо у форматі `riff`, а значення для спроби — `riff-16khz-16bit-mono-pcm`, `riff-24khz-16bit-mono-pcm` і `riff-48khz-16bit-mono-pcm`.

1. Нижче цього оголосіть функцію під назвою `get_speech`, яка буде перетворювати текст у мовлення за допомогою REST API служби мовлення:

    ```python
    def get_speech(text):
    ```

1. У функції `get_speech` визначте URL для виклику та заголовки для передачі:

    ```python
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    ```

    Це встановлює заголовки для використання згенерованого токена доступу, задає вміст як SSML і визначає потрібний аудіоформат.

1. Нижче цього визначте SSML для надсилання до REST API:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

    Цей SSML задає мову та голос для використання, а також текст для перетворення.

1. Нарешті, додайте код у цю функцію для виконання REST-запиту та повернення двійкових аудіоданих:

    ```python
    response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    return io.BytesIO(response.content)
    ```

### Завдання - відтворення аудіо

1. Нижче функції `get_speech` визначте нову функцію для відтворення аудіо, отриманого в результаті виклику REST API:

    ```python
    def play_speech(speech):
    ```

1. `speech`, переданий до цієї функції, буде двійковими аудіоданими, отриманими з REST API. Використовуйте наступний код, щоб відкрити це як wave-файл і передати його до PyAudio для відтворення аудіо:

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

    Цей код використовує потік PyAudio, так само як і для захоплення аудіо. Різниця тут полягає в тому, що потік налаштований як вихідний, а дані читаються з аудіоданих і передаються до потоку.

    Замість жорсткого кодування деталей потоку, таких як частота дискретизації, вони читаються з аудіоданих.

1. Замініть вміст функції `say` наступним:

    ```python
    speech = get_speech(text)
    play_speech(speech)
    ```

    Цей код перетворює текст у мовлення як двійкові аудіодані та відтворює аудіо.

1. Запустіть додаток і переконайтеся, що функціональний додаток також працює. Встановіть кілька таймерів, і ви почуєте голосову відповідь, яка повідомляє, що ваш таймер встановлено, а потім ще одну голосову відповідь, коли таймер завершено.

    Якщо ви отримуєте помилки `Invalid sample rate`, змініть `playback_format`, як описано вище.

> 💁 Ви можете знайти цей код у папці [code-spoken-response/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/pi).

😀 Ваш додаток таймера був успішним!

---

**Відмова від відповідальності**:  
Цей документ був перекладений за допомогою сервісу автоматичного перекладу [Co-op Translator](https://github.com/Azure/co-op-translator). Хоча ми прагнемо до точності, будь ласка, майте на увазі, що автоматичні переклади можуть містити помилки або неточності. Оригінальний документ на його рідній мові слід вважати авторитетним джерелом. Для критичної інформації рекомендується професійний людський переклад. Ми не несемо відповідальності за будь-які непорозуміння або неправильні тлумачення, що виникають внаслідок використання цього перекладу.