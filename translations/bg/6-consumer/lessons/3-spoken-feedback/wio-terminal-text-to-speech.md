<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a202fa5889790a3777bfc33dd9f4b459",
  "translation_date": "2025-08-28T09:01:52+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-text-to-speech.md",
  "language_code": "bg"
}
-->
# Преобразуване на текст в реч - Wio Terminal

В тази част от урока ще преобразувате текст в реч, за да предоставите гласова обратна връзка.

## Преобразуване на текст в реч

SDK за услуги за реч, който използвахте в предишния урок за преобразуване на реч в текст, може да се използва и за преобразуване на текст обратно в реч.

## Получаване на списък с гласове

Когато заявявате реч, трябва да посочите гласа, който да се използва, тъй като речта може да бъде генерирана с различни гласове. Всеки език поддържа набор от различни гласове, и можете да получите списъка с поддържаните гласове за всеки език чрез SDK за услуги за реч. Тук влизат в сила ограниченията на микроконтролерите - заявката за списъка с гласове, поддържани от услугите за преобразуване на текст в реч, връща JSON документ с размер над 77KB, което е твърде голямо, за да бъде обработено от Wio Terminal. Към момента на писане, пълният списък съдържа 215 гласа, всеки дефиниран чрез JSON документ като следния:

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

Този JSON е за гласа **Aria**, който има няколко стила на глас. Всичко, което е необходимо при преобразуване на текст в реч, е краткото име, `en-US-AriaNeural`.

Вместо да изтегляте и декодирате целия този списък на вашия микроконтролер, ще трябва да напишете още малко serverless код, за да извлечете списъка с гласове за езика, който използвате, и да го извикате от вашия Wio Terminal. Вашият код може след това да избере подходящ глас от списъка, например първия, който намери.

### Задача - създаване на serverless функция за получаване на списък с гласове

1. Отворете вашия проект `smart-timer-trigger` в VS Code и отворете терминала, като се уверите, че виртуалната среда е активирана. Ако не е, прекратете и създайте отново терминала.

1. Отворете файла `local.settings.json` и добавете настройки за API ключа и местоположението на услугата за реч:

    ```json
    "SPEECH_KEY": "<key>",
    "SPEECH_LOCATION": "<location>"
    ```

    Заменете `<key>` с API ключа за вашия ресурс за услуги за реч. Заменете `<location>` с местоположението, което сте използвали при създаването на ресурса за услуги за реч.

1. Добавете нов HTTP тригер към това приложение, наречен `get-voices`, като използвате следната команда в терминала на VS Code в основната папка на проекта за функции:

    ```sh
    func new --name get-voices --template "HTTP trigger"
    ```

    Това ще създаде HTTP тригер, наречен `get-voices`.

1. Заменете съдържанието на файла `__init__.py` в папката `get-voices` със следното:

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

    Този код прави HTTP заявка към крайна точка, за да получи гласовете. Списъкът с гласове е голям JSON блок с гласове за всички езици, така че гласовете за езика, подаден в тялото на заявката, се филтрират, след което краткото име се извлича и връща като JSON списък. Краткото име е стойността, необходима за преобразуване на текст в реч, така че само тази стойност се връща.

    > 💁 Можете да промените филтъра, ако е необходимо, за да изберете само гласовете, които искате.

    Това намалява размера на данните от 77KB (към момента на писане) до много по-малък JSON документ. Например, за гласове на САЩ това е 408 байта.

1. Стартирайте локално вашето приложение за функции. След това можете да го извикате с инструмент като curl по същия начин, по който тествахте HTTP тригера `text-to-timer`. Уверете се, че подавате вашия език като JSON тяло:

    ```json
    {
        "language":"<language>"
    }
    ```

    Заменете `<language>` с вашия език, например `en-GB` или `zh-CN`.

> 💁 Можете да намерите този код в папката [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions).

### Задача - извличане на гласа от вашия Wio Terminal

1. Отворете проекта `smart-timer` в VS Code, ако вече не е отворен.

1. Отворете заглавния файл `config.h` и добавете URL адреса за вашето приложение за функции:

    ```cpp
    const char *GET_VOICES_FUNCTION_URL = "<URL>";
    ```

    Заменете `<URL>` с URL адреса за HTTP тригера `get-voices` на вашето приложение за функции. Това ще бъде същото като стойността за `TEXT_TO_TIMER_FUNCTION_URL`, но с име на функция `get-voices` вместо `text-to-timer`.

1. Създайте нов файл в папката `src`, наречен `text_to_speech.h`. Той ще се използва за дефиниране на клас за преобразуване от текст в реч.

1. Добавете следните директиви за включване в началото на новия файл `text_to_speech.h`:

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

1. Добавете следния код под тях, за да декларирате класа `TextToSpeech`, заедно с екземпляр, който може да се използва в останалата част от приложението:

    ```cpp
    class TextToSpeech
    {
    public:
    private:
    };
    
    TextToSpeech textToSpeech;
    ```

1. За да извикате вашето приложение за функции, трябва да декларирате WiFi клиент. Добавете следното в частната секция на класа:

    ```cpp
    WiFiClient _client;
    ```

1. В частната секция добавете поле за избрания глас:

    ```cpp
    String _voice;
    ```

1. В публичната секция добавете функция `init`, която ще получи първия глас:

    ```cpp
    void init()
    {
    }
    ```

1. За да получите гласовете, трябва да се изпрати JSON документ към приложението за функции с езика. Добавете следния код към функцията `init`, за да създадете този JSON документ:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;

    String body;
    serializeJson(doc, body);
    ```

1. След това създайте `HTTPClient` и го използвайте, за да извикате приложението за функции, като изпратите JSON документа:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, GET_VOICES_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. Под това добавете код за проверка на кода на отговора и ако е 200 (успех), извлечете списъка с гласове, като вземете първия от списъка:

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

1. След това прекратете връзката на HTTP клиента:

    ```cpp
    httpClient.end();
    ```

1. Отворете файла `main.cpp` и добавете следната директива за включване в началото, за да включите този нов заглавен файл:

    ```cpp
    #include "text_to_speech.h"
    ```

1. Във функцията `setup`, под извикването на `speechToText.init();`, добавете следното, за да инициализирате класа `TextToSpeech`:

    ```cpp
    textToSpeech.init();
    ```

1. Компилирайте този код, качете го на вашия Wio Terminal и го тествайте през серийния монитор. Уверете се, че вашето приложение за функции работи.

    Ще видите списъка с наличните гласове, върнат от приложението за функции, заедно с избрания глас.

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

## Преобразуване на текст в реч

След като имате глас за използване, той може да се използва за преобразуване на текст в реч. Същите ограничения за паметта при гласовете важат и при преобразуване на реч в текст, така че ще трябва да запишете речта на SD карта, за да бъде възпроизведена през ReSpeaker.

> 💁 В по-ранни уроци от този проект използвахте флаш памет за съхранение на реч, записана от микрофона. Този урок използва SD карта, тъй като е по-лесно да се възпроизвежда аудио от нея с помощта на библиотеките за аудио на Seeed.

Има и друго ограничение, което трябва да се вземе предвид - наличните аудио данни от услугата за реч и форматите, които Wio Terminal поддържа. За разлика от пълноценните компютри, аудио библиотеките за микроконтролери могат да бъдат много ограничени в аудио форматите, които поддържат. Например, библиотеката Seeed Arduino Audio, която може да възпроизвежда звук през ReSpeaker, поддържа само аудио със скорост на семплиране 44.1KHz. Услугите за реч на Azure могат да предоставят аудио в няколко формата, но нито един от тях не използва тази скорост на семплиране - те предоставят само 8KHz, 16KHz, 24KHz и 48KHz. Това означава, че аудиото трябва да бъде пре-семплирано до 44.1KHz, което изисква повече ресурси, отколкото Wio Terminal има, особено памет.

Когато е необходимо да се манипулират данни като тези, често е по-добре да се използва serverless код, особено ако данните се извличат чрез уеб заявка. Wio Terminal може да извика serverless функция, като подаде текста за преобразуване, а serverless функцията може както да извика услугата за реч, за да преобразува текста в реч, така и да пре-семплира аудиото до необходимата скорост на семплиране. След това тя може да върне аудиото във формата, който Wio Terminal изисква, за да бъде съхранено на SD картата и възпроизведено през ReSpeaker.

### Задача - създаване на serverless функция за преобразуване на текст в реч

1. Отворете вашия проект `smart-timer-trigger` в VS Code и отворете терминала, като се уверите, че виртуалната среда е активирана. Ако не е, прекратете и създайте отново терминала.

1. Добавете нов HTTP тригер към това приложение, наречен `text-to-speech`, като използвате следната команда в терминала на VS Code в основната папка на проекта за функции:

    ```sh
    func new --name text-to-speech --template "HTTP trigger"
    ```

    Това ще създаде HTTP тригер, наречен `text-to-speech`.

1. Пакетът Pip [librosa](https://librosa.org) има функции за пре-семплиране на аудио, така че го добавете към файла `requirements.txt`:

    ```sh
    librosa
    ```

    След като го добавите, инсталирайте пакетите Pip, като използвате следната команда в терминала на VS Code:

    ```sh
    pip install -r requirements.txt
    ```

    > ⚠️ Ако използвате Linux, включително Raspberry Pi OS, може да се наложи да инсталирате `libsndfile` със следната команда:
    >
    > ```sh
    > sudo apt update
    > sudo apt install libsndfile1-dev
    > ```

1. За да преобразувате текст в реч, не можете да използвате директно API ключа за реч, вместо това трябва да заявите токен за достъп, като използвате API ключа за удостоверяване на заявката за токен за достъп. Отворете файла `__init__.py` от папката `text-to-speech` и заменете целия код в него със следното:

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

    Това дефинира константи за местоположението и ключа за реч, които ще бъдат прочетени от настройките. След това дефинира функцията `get_access_token`, която ще извлече токен за достъп за услугата за реч.

1. Под този код добавете следното:

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

    Това дефинира HTTP тригера, който преобразува текста в реч. Той извлича текста за преобразуване, езика и гласа от JSON тялото, изпратено към заявката, създава SSML за заявка на реч, след което извиква съответния REST API, удостоверявайки се с токена за достъп. Тази REST API заявка връща аудиото, кодирано като 16-битово, 48KHz моно WAV файл, дефинирано от стойността на `playback_format`, която се изпраща към REST API заявката.

    След това аудиото се пре-семплира от `librosa` от скорост на семплиране 48KHz до скорост на семплиране 44.1KHz, след което това аудио се записва в двоичен буфер, който след това се връща.

1. Стартирайте локално вашето приложение за функции или го разположете в облака. След това можете да го извикате с инструмент като curl по същия начин, по който тествахте HTTP тригера `text-to-timer`. Уверете се, че подавате езика, гласа и текста като JSON тяло:

    ```json
    {
        "language": "<language>",
        "voice": "<voice>",
        "text": "<text>"
    }
    ```

    Заменете `<language>` с вашия език, например `en-GB` или `zh-CN`. Заменете `<voice>` с гласа, който искате да използвате. Заменете `<text>` с текста, който искате да преобразувате в реч. Можете да запазите изхода в файл и да го възпроизведете с всеки аудио плейър, който може да възпроизвежда WAV файлове.

    Например, за да преобразувате "Hello" в реч, използвайки американски английски с гласа Jenny Neural, с локално работещо приложение за функции, можете да използвате следната команда curl:

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

    Това ще запази аудиото в `hello.wav` в текущата директория.

> 💁 Можете да намерите този код в папката [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions).

### Задача - извличане на речта от вашия Wio Terminal

1. Отворете проекта `smart-timer` в VS Code, ако вече не е отворен.

1. Отворете заглавния файл `config.h` и добавете URL адреса за вашето приложение за функции:

    ```cpp
    const char *TEXT_TO_SPEECH_FUNCTION_URL = "<URL>";
    ```

    Заменете `<URL>` с URL адреса за HTTP тригера `text-to-speech` на вашето приложение за функции. Това ще бъде същото като стойността за `TEXT_TO_TIMER_FUNCTION_URL`, но с име на функция `text-to-speech` вместо `text-to-timer`.

1. Отворете заглавния файл `text_to_speech.h` и добавете следния метод в публичната секция на класа `TextToSpeech`:

    ```cpp
    void convertTextToSpeech(String text)
    {
    }
    ```

1. Към метода `convertTextToSpeech` добавете следния код, за да създадете JSON за изпращане към приложението за функции:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;
    doc["voice"] = _voice;
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    Това записва езика, гласа и текста в JSON документа, след което го сериализира в низ.

1. Под това добавете следния код, за да извикате приложението за функции:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_SPEECH_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    Това създава HTTPClient, след което прави POST заявка, използвайки JSON документа към HTTP тригера за преобразуване на текст в реч.

1. Ако заявката е успешна, суровите двоични данни, върнати от извикването на приложението за функции, могат да бъдат записани във файл на SD картата. Добавете следния код, за да направите това:

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

    Този код проверява отговора и ако е 200 (успех), двоичните данни се записват във файл в корена на SD картата, наречен `SPEECH.WAV`.

1. В края на този метод затворете HTTP връзката:

    ```cpp
    httpClient.end();
    ```

1. Текстът, който трябва да бъде изговорен, вече може да бъде преобразуван в аудио. Във файла `main.cpp` добавете следния ред в края на функцията `say`, за да преобразувате текста за изговаряне в аудио:
```cpp
    textToSpeech.convertTextToSpeech(text);
    ```

### Задача - възпроизвеждане на аудио от вашия Wio Terminal

**Очаквайте скоро**

## Деплойване на вашето приложение с функции в облака

Причината да стартирате приложението с функции локално е, че `librosa` Pip пакетът на Linux има зависимост от библиотека, която не е инсталирана по подразбиране и ще трябва да бъде инсталирана, преди приложението с функции да може да работи. Приложенията с функции са безсървърни - няма сървъри, които можете да управлявате сами, така че няма начин да инсталирате тази библиотека предварително.

Начинът да направите това е вместо това да деплойнете вашето приложение с функции, използвайки Docker контейнер. Този контейнер се деплойва от облака, когато е необходимо да се стартира нов екземпляр на вашето приложение с функции (например когато търсенето надвишава наличните ресурси или ако приложението с функции не е използвано известно време и е затворено).

Можете да намерите инструкции за създаване на приложение с функции и деплойване чрез Docker в [документацията за създаване на функция на Linux с помощта на персонализиран контейнер на Microsoft Docs](https://docs.microsoft.com/azure/azure-functions/functions-create-function-linux-custom-image?WT.mc_id=academic-17441-jabenn&tabs=bash%2Cazurecli&pivots=programming-language-python).

След като това бъде деплойнато, можете да прехвърлите вашия Wio Terminal код, за да достъпите тази функция:

1. Добавете сертификата на Azure Functions към `config.h`:

    ```cpp
    const char *FUNCTIONS_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "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\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

1. Променете всички включвания на `<WiFiClient.h>` на `<WiFiClientSecure.h>`.

1. Променете всички полета `WiFiClient` на `WiFiClientSecure`.

1. Във всеки клас, който има поле `WiFiClientSecure`, добавете конструктор и задайте сертификата в този конструктор:

    ```cpp
    _client.setCACert(FUNCTIONS_CERTIFICATE);
    ```

---

**Отказ от отговорност**:  
Този документ е преведен с помощта на AI услуга за превод [Co-op Translator](https://github.com/Azure/co-op-translator). Въпреки че се стремим към точност, моля, имайте предвид, че автоматизираните преводи може да съдържат грешки или неточности. Оригиналният документ на неговия роден език трябва да се счита за авторитетен източник. За критична информация се препоръчва професионален човешки превод. Ние не носим отговорност за недоразумения или погрешни интерпретации, произтичащи от използването на този превод.