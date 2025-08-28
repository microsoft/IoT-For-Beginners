<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a202fa5889790a3777bfc33dd9f4b459",
  "translation_date": "2025-08-28T16:18:54+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-text-to-speech.md",
  "language_code": "uk"
}
-->
# Перетворення тексту в мову - Wio Terminal

У цій частині уроку ви перетворите текст у мову, щоб забезпечити голосовий зворотний зв'язок.

## Перетворення тексту в мову

SDK для мовних сервісів, який ви використовували в попередньому уроці для перетворення мови в текст, також можна використовувати для перетворення тексту назад у мову.

## Отримання списку голосів

При запиті мови потрібно вказати голос, який буде використовуватися, оскільки мова може генеруватися за допомогою різних голосів. Кожна мова підтримує різноманітні голоси, і ви можете отримати список підтримуваних голосів для кожної мови через SDK мовних сервісів. Тут вступають у гру обмеження мікроконтролерів — виклик для отримання списку голосів, підтримуваних сервісом перетворення тексту в мову, є JSON-документом розміром понад 77 КБ, що занадто багато для обробки Wio Terminal. На момент написання повний список містить 215 голосів, кожен з яких визначений JSON-документом, подібним до наступного:

```json
{
    "Name": "Microsoft Server Speech Text to Speech Voice (en-US, AriaNeural)",
    "DisplayName": "Aria",
    "LocalName": "Aria",
    "ShortName": "en-US-AriaNeural",
    "Gender": "Female",
    "Locale": "en-US",
    "StyleList": [
        "chat",
        "customerservice",
        "narration-professional",
        "newscast-casual",
        "newscast-formal",
        "cheerful",
        "empathetic"
    ],
    "SampleRateHertz": "24000",
    "VoiceType": "Neural",
    "Status": "GA"
}
```

Цей JSON стосується голосу **Aria**, який має кілька стилів голосу. Все, що потрібно для перетворення тексту в мову, — це коротке ім'я, `en-US-AriaNeural`.

Замість завантаження та декодування всього списку на вашому мікроконтролері, вам потрібно буде написати трохи безсерверного коду, щоб отримати список голосів для мови, яку ви використовуєте, і викликати це з вашого Wio Terminal. Ваш код може вибрати відповідний голос зі списку, наприклад, перший знайдений.

### Завдання - створення безсерверної функції для отримання списку голосів

1. Відкрийте ваш проєкт `smart-timer-trigger` у VS Code і відкрийте термінал, переконавшись, що віртуальне середовище активоване. Якщо ні, зупиніть і створіть термінал заново.

1. Відкрийте файл `local.settings.json` і додайте налаштування для ключа API мовного сервісу та його розташування:

    ```json
    "SPEECH_KEY": "<key>",
    "SPEECH_LOCATION": "<location>"
    ```

    Замініть `<key>` на ключ API для вашого ресурсу мовного сервісу. Замініть `<location>` на розташування, яке ви використовували при створенні ресурсу мовного сервісу.

1. Додайте новий HTTP-тригер до цього додатка під назвою `get-voices`, використовуючи наступну команду в терміналі VS Code у кореневій папці проєкту функцій:

    ```sh
    func new --name get-voices --template "HTTP trigger"
    ```

    Це створить HTTP-тригер під назвою `get-voices`.

1. Замініть вміст файлу `__init__.py` у папці `get-voices` наступним:

    ```python
    import json
    import os
    import requests
    
    import azure.functions as func
    
    def main(req: func.HttpRequest) -> func.HttpResponse:
        location = os.environ['SPEECH_LOCATION']
        speech_key = os.environ['SPEECH_KEY']
    
        req_body = req.get_json()
        language = req_body['language']
    
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/voices/list'
    
        headers = {
            'Ocp-Apim-Subscription-Key': speech_key
        }
    
        response = requests.get(url, headers=headers)
        voices_json = json.loads(response.text)
    
        voices = filter(lambda x: x['Locale'].lower() == language.lower(), voices_json)
        voices = map(lambda x: x['ShortName'], voices)
    
        return func.HttpResponse(json.dumps(list(voices)), status_code=200)
    ```

    Цей код виконує HTTP-запит до кінцевої точки для отримання голосів. Список голосів — це великий блок JSON із голосами для всіх мов, тому голоси для мови, переданої в тілі запиту, відфільтровуються, після чого коротке ім'я витягується і повертається у вигляді JSON-списку. Коротке ім'я — це значення, необхідне для перетворення тексту в мову, тому повертається лише це значення.

    > 💁 Ви можете змінити фільтр за потреби, щоб вибрати лише потрібні вам голоси.

    Це зменшує розмір даних із 77 КБ (на момент написання) до набагато меншого JSON-документа. Наприклад, для голосів США це 408 байтів.

1. Запустіть ваш додаток функцій локально. Потім ви можете викликати його за допомогою інструмента, такого як curl, так само, як ви тестували HTTP-тригер `text-to-timer`. Обов’язково передайте вашу мову у вигляді JSON-тела:

    ```json
    {
        "language":"<language>"
    }
    ```

    Замініть `<language>` на вашу мову, наприклад, `en-GB` або `zh-CN`.

> 💁 Ви можете знайти цей код у папці [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions).

### Завдання - отримання голосу з вашого Wio Terminal

1. Відкрийте проєкт `smart-timer` у VS Code, якщо він ще не відкритий.

1. Відкрийте файл заголовка `config.h` і додайте URL-адресу для вашого додатка функцій:

    ```cpp
    const char *GET_VOICES_FUNCTION_URL = "<URL>";
    ```

    Замініть `<URL>` на URL-адресу HTTP-тригера `get-voices` у вашому додатку функцій. Це буде те саме значення, що й для `TEXT_TO_TIMER_FUNCTION_URL`, за винятком того, що ім'я функції буде `get-voices` замість `text-to-timer`.

1. Створіть новий файл у папці `src` під назвою `text_to_speech.h`. У ньому буде визначено клас для перетворення тексту в мову.

1. Додайте наступні директиви включення на початок нового файлу `text_to_speech.h`:

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <Seeed_FS.h>
    #include <SD/Seeed_SD.h>
    #include <WiFiClient.h>
    #include <WiFiClientSecure.h>
    
    #include "config.h"
    #include "speech_to_text.h"
    ```

1. Додайте наступний код нижче, щоб оголосити клас `TextToSpeech`, а також екземпляр, який можна використовувати в решті програми:

    ```cpp
    class TextToSpeech
    {
    public:
    private:
    };
    
    TextToSpeech textToSpeech;
    ```

1. Щоб викликати ваш додаток функцій, потрібно оголосити WiFi-клієнт. Додайте наступне до розділу `private` класу:

    ```cpp
    WiFiClient _client;
    ```

1. У розділі `private` додайте поле для вибраного голосу:

    ```cpp
    String _voice;
    ```

1. У розділі `public` додайте функцію `init`, яка отримає перший голос:

    ```cpp
    void init()
    {
    }
    ```

1. Щоб отримати голоси, потрібно створити JSON-документ із мовою. Додайте наступний код до функції `init`, щоб створити цей JSON-документ:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;

    String body;
    serializeJson(doc, body);
    ```

1. Далі створіть `HTTPClient`, а потім використовуйте його для виклику додатка функцій, щоб отримати голоси, відправивши JSON-документ:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, GET_VOICES_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. Нижче цього додайте код для перевірки коду відповіді, і якщо це 200 (успіх), то витягніть список голосів, отримавши перший зі списку:

    ```cpp
    if (httpResponseCode == 200)
    {
        String result = httpClient.getString();
        Serial.println(result);

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, result.c_str());

        JsonArray obj = doc.as<JsonArray>();
        _voice = obj[0].as<String>();

        Serial.print("Using voice ");
        Serial.println(_voice);
    }
    else
    {
        Serial.print("Failed to get voices - error ");
        Serial.println(httpResponseCode);
    }
    ```

1. Після цього закрийте з'єднання HTTP-клієнта:

    ```cpp
    httpClient.end();
    ```

1. Відкрийте файл `main.cpp` і додайте наступну директиву включення на початку, щоб включити цей новий заголовковий файл:

    ```cpp
    #include "text_to_speech.h"
    ```

1. У функції `setup`, під викликом `speechToText.init();`, додайте наступне, щоб ініціалізувати клас `TextToSpeech`:

    ```cpp
    textToSpeech.init();
    ```

1. Зберіть цей код, завантажте його на ваш Wio Terminal і протестуйте через серійний монітор. Переконайтеся, що ваш додаток функцій працює.

    Ви побачите список доступних голосів, повернутих із додатка функцій, разом із вибраним голосом.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Got access token.
    ["en-US-JennyNeural", "en-US-JennyMultilingualNeural", "en-US-GuyNeural", "en-US-AriaNeural", "en-US-AmberNeural", "en-US-AnaNeural", "en-US-AshleyNeural", "en-US-BrandonNeural", "en-US-ChristopherNeural", "en-US-CoraNeural", "en-US-ElizabethNeural", "en-US-EricNeural", "en-US-JacobNeural", "en-US-MichelleNeural", "en-US-MonicaNeural", "en-US-AriaRUS", "en-US-BenjaminRUS", "en-US-GuyRUS", "en-US-ZiraRUS"]
    Using voice en-US-JennyNeural
    Ready.
    ```

## Перетворення тексту в мову

Як тільки у вас є голос для використання, його можна використовувати для перетворення тексту в мову. Ті ж обмеження пам’яті для голосів також застосовуються при перетворенні мови в текст, тому вам потрібно буде записати мову на SD-карту, щоб її можна було відтворити через ReSpeaker.

> 💁 У попередніх уроках цього проєкту ви використовували флеш-пам’ять для зберігання мови, захопленої мікрофоном. У цьому уроці використовується SD-карта, оскільки з неї легше відтворювати аудіо за допомогою бібліотек Seeed Audio.

Також є ще одне обмеження, яке потрібно врахувати, — доступні аудіодані від мовного сервісу та формати, які підтримує Wio Terminal. На відміну від повноцінних комп’ютерів, аудіобібліотеки для мікроконтролерів можуть бути дуже обмеженими у форматах аудіо, які вони підтримують. Наприклад, бібліотека Seeed Arduino Audio, яка може відтворювати звук через ReSpeaker, підтримує лише аудіо з частотою дискретизації 44,1 кГц. Мовні сервіси Azure можуть надавати аудіо в кількох форматах, але жоден із них не використовує цю частоту дискретизації, вони надають лише 8 кГц, 16 кГц, 24 кГц і 48 кГц. Це означає, що аудіо потрібно перетворити до 44,1 кГц, що потребує більше ресурсів, ніж має Wio Terminal, особливо пам’яті.

Коли потрібно маніпулювати такими даними, краще використовувати безсерверний код, особливо якщо дані отримуються через веб-запит. Wio Terminal може викликати безсерверну функцію, передаючи текст для перетворення, а безсерверна функція може як викликати мовний сервіс для перетворення тексту в мову, так і перетворити аудіо до потрібної частоти дискретизації. Потім вона може повернути аудіо у формі, необхідній Wio Terminal, щоб зберегти його на SD-карті та відтворити через ReSpeaker.

### Завдання - створення безсерверної функції для перетворення тексту в мову

1. Відкрийте ваш проєкт `smart-timer-trigger` у VS Code і відкрийте термінал, переконавшись, що віртуальне середовище активоване. Якщо ні, зупиніть і створіть термінал заново.

1. Додайте новий HTTP-тригер до цього додатка під назвою `text-to-speech`, використовуючи наступну команду в терміналі VS Code у кореневій папці проєкту функцій:

    ```sh
    func new --name text-to-speech --template "HTTP trigger"
    ```

    Це створить HTTP-тригер під назвою `text-to-speech`.

1. Пакет Pip [librosa](https://librosa.org) має функції для перетворення частоти дискретизації аудіо, тому додайте його до файлу `requirements.txt`:

    ```sh
    librosa
    ```

    Після цього встановіть пакети Pip, використовуючи наступну команду в терміналі VS Code:

    ```sh
    pip install -r requirements.txt
    ```

    > ⚠️ Якщо ви використовуєте Linux, включаючи Raspberry Pi OS, можливо, вам потрібно буде встановити `libsndfile` за допомогою наступної команди:
    >
    > ```sh
    > sudo apt update
    > sudo apt install libsndfile1-dev
    > ```

1. Для перетворення тексту в мову ви не можете використовувати ключ API мовного сервісу безпосередньо, натомість вам потрібно запросити токен доступу, використовуючи ключ API для автентифікації запиту токена доступу. Відкрийте файл `__init__.py` із папки `text-to-speech` і замініть увесь код у ньому наступним:

    ```python
    import io
    import os
    import requests
    
    import librosa
    import soundfile as sf
    import azure.functions as func
    
    location = os.environ['SPEECH_LOCATION']
    speech_key = os.environ['SPEECH_KEY']
    
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    Це визначає константи для розташування та мовного ключа, які будуть зчитуватися з налаштувань. Потім визначається функція `get_access_token`, яка отримує токен доступу для мовного сервісу.

1. Нижче цього коду додайте наступне:

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'

    def main(req: func.HttpRequest) -> func.HttpResponse:
        req_body = req.get_json()
        language = req_body['language']
        voice = req_body['voice']
        text = req_body['text']
    
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    
        ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
        ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
        ssml += text
        ssml += '</voice>'
        ssml += '</speak>'
    
        response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    
        raw_audio, sample_rate = librosa.load(io.BytesIO(response.content), sr=48000)
        resampled = librosa.resample(raw_audio, sample_rate, 44100)
        
        output_buffer = io.BytesIO()
        sf.write(output_buffer, resampled, 44100, 'PCM_16', format='wav')
        output_buffer.seek(0)
    
        return func.HttpResponse(output_buffer.read(), status_code=200)
    ```

    Це визначає HTTP-тригер, який перетворює текст у мову. Він витягує текст для перетворення, мову та голос із JSON-тела, надісланого в запиті, створює SSML для запиту мови, а потім викликає відповідний REST API, автентифікуючи за допомогою токена доступу. Цей виклик REST API повертає аудіо, закодоване як 16-бітний, 48 кГц моно WAV-файл, визначений значенням `playback_format`, яке надсилається у виклик REST API.

    Потім це аудіо перетворюється за допомогою `librosa` з частоти дискретизації 48 кГц на частоту 44,1 кГц, після чого це аудіо зберігається у двійковий буфер, який потім повертається.

1. Запустіть ваш додаток функцій локально або розгорніть його в хмарі. Потім ви можете викликати його за допомогою інструмента, такого як curl, так само, як ви тестували HTTP-тригер `text-to-timer`. Обов’язково передайте мову, голос і текст у вигляді JSON-тела:

    ```json
    {
        "language": "<language>",
        "voice": "<voice>",
        "text": "<text>"
    }
    ```

    Замініть `<language>` на вашу мову, наприклад, `en-GB` або `zh-CN`. Замініть `<voice>` на голос, який ви хочете використовувати. Замініть `<text>` на текст, який ви хочете перетворити в мову. Ви можете зберегти результат у файл і відтворити його за допомогою будь-якого аудіоплеєра, який може відтворювати WAV-файли.

    Наприклад, щоб перетворити "Hello" у мову, використовуючи англійську мову США з голосом Jenny Neural, із додатком функцій, що працює локально, ви можете використати наступну команду curl:

    ```sh
    curl -X GET 'http://localhost:7071/api/text-to-speech' \
         -H 'Content-Type: application/json' \
         -o hello.wav \
         -d '{
           "language":"en-US",
           "voice": "en-US-JennyNeural",
           "text": "Hello"
         }'
    ```

    Це збереже аудіо у файл `hello.wav` у поточній директорії.

> 💁 Ви можете знайти цей код у папці [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions).

### Завдання - отримання мови з вашого Wio Terminal

1. Відкрийте проєкт `smart-timer` у VS Code, якщо він ще не відкритий.

1. Відкрийте файл заголовка `config.h` і додайте URL-адресу для вашого додатка функцій:

    ```cpp
    const char *TEXT_TO_SPEECH_FUNCTION_URL = "<URL>";
    ```

    Замініть `<URL>` на URL-адресу HTTP-тригера `text-to-speech` у вашому додатку функцій. Це буде те саме значення, що й для `TEXT_TO_TIMER_FUNCTION_URL`, за винятком того, що ім'я функції буде `text-to-speech` замість `text-to-timer`.

1. Відкрийте файл заголовка `text_to_speech.h` і додайте наступний метод до розділу `public` класу `TextToSpeech`:

    ```cpp
    void convertTextToSpeech(String text)
    {
    }
    ```

1. У методі `convertTextToSpeech` додайте наступний код для створення JSON, який буде відправлено до додатка функцій:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;
    doc["voice"] = _voice;
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    Це записує мову, голос і текст у JSON-документ, а потім серіалізує його в рядок.

1. Нижче цього додайте наступний код для виклику додатка функцій:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_SPEECH_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    Це створює HTTPClient, а потім виконує POST-запит із JSON-документом до HTTP-тригера `text-to-speech`.

1. Якщо виклик успішний, сирі двійкові дані, повернуті з виклику додатка функцій, можна передати у файл на SD-карті. Додайте наступний код для цього:

    ```cpp
    if (httpResponseCode == 200)
    {            
        File wav_file = SD.open("SPEECH.WAV", FILE_WRITE);
        httpClient.writeToStream(&wav_file);
        wav_file.close();
    }
    else
    {
        Serial.print("Failed to get speech - error ");
        Serial.println(httpResponseCode);
    }
    ```

    Цей код перевіряє відповідь, і якщо це 200 (успіх), двійкові дані передаються у файл у корені SD-карти під назвою `SPEECH.WAV`.

1. Наприкінці цього методу закрийте HTTP-з'єднання:

    ```cpp
    httpClient.end();
    ```

1. Тепер текст, який потрібно озвучити, можна перетворити в аудіо. У файлі `main.cpp` додайте наступний рядок у кінець функції `say`, щоб перетворити текст для озвучення в аудіо:
```cpp
    textToSpeech.convertTextToSpeech(text);
    ```

### Завдання - відтворення аудіо на вашому Wio Terminal

**Незабаром**

## Розгортання вашого функціонального додатку в хмарі

Причина запуску функціонального додатку локально полягає в тому, що пакет `librosa` для Pip на Linux має залежність від бібліотеки, яка за замовчуванням не встановлена, і її потрібно встановити перед тим, як функціональний додаток зможе працювати. Функціональні додатки є безсерверними - немає серверів, які ви можете керувати самостійно, тому немає способу встановити цю бібліотеку заздалегідь.

Рішенням є розгортання вашого функціонального додатку за допомогою Docker-контейнера. Цей контейнер розгортається хмарою щоразу, коли потрібно запустити новий екземпляр вашого функціонального додатку (наприклад, коли попит перевищує доступні ресурси або якщо функціональний додаток не використовувався деякий час і був закритий).

Інструкції щодо налаштування функціонального додатку та розгортання через Docker можна знайти в [документації зі створення функції на Linux за допомогою власного контейнера на Microsoft Docs](https://docs.microsoft.com/azure/azure-functions/functions-create-function-linux-custom-image?WT.mc_id=academic-17441-jabenn&tabs=bash%2Cazurecli&pivots=programming-language-python).

Після того, як це буде розгорнуто, ви зможете перенести код вашого Wio Terminal для доступу до цієї функції:

1. Додайте сертифікат Azure Functions до `config.h`:

    ```cpp
    const char *FUNCTIONS_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "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\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

1. Змініть всі включення `
<WiFiClient.h>` на `<WiFiClientSecure.h>`.

1. Змініть всі поля `WiFiClient` на `WiFiClientSecure`.

1. У кожному класі, який має поле `WiFiClientSecure`, додайте конструктор і встановіть сертифікат у цьому конструкторі:

    ```cpp
    _client.setCACert(FUNCTIONS_CERTIFICATE);
    ```

---

**Відмова від відповідальності**:  
Цей документ був перекладений за допомогою сервісу автоматичного перекладу [Co-op Translator](https://github.com/Azure/co-op-translator). Хоча ми прагнемо до точності, зверніть увагу, що автоматичні переклади можуть містити помилки або неточності. Оригінальний документ на його рідній мові слід вважати авторитетним джерелом. Для критичної інформації рекомендується професійний людський переклад. Ми не несемо відповідальності за будь-які непорозуміння або неправильні тлумачення, що виникають внаслідок використання цього перекладу.