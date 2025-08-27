<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a202fa5889790a3777bfc33dd9f4b459",
  "translation_date": "2025-08-27T00:13:31+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-text-to-speech.md",
  "language_code": "ru"
}
-->
# Текст в речь - Wio Terminal

В этой части урока вы преобразуете текст в речь, чтобы обеспечить голосовую обратную связь.

## Текст в речь

SDK сервисов речи, который вы использовали в прошлом уроке для преобразования речи в текст, также может быть использован для преобразования текста обратно в речь.

## Получение списка голосов

При запросе речи необходимо указать голос, который будет использоваться, так как речь может быть сгенерирована с использованием различных голосов. Каждый язык поддерживает множество голосов, и вы можете получить список поддерживаемых голосов для каждого языка через SDK сервисов речи. Здесь вступают в силу ограничения микроконтроллеров — вызов для получения списка голосов, поддерживаемых сервисами преобразования текста в речь, представляет собой JSON-документ размером более 77 КБ, что слишком много для обработки на Wio Terminal. На момент написания полный список содержит 215 голосов, каждый из которых представлен JSON-документом, подобным следующему:

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

Этот JSON относится к голосу **Aria**, который имеет несколько стилей. Все, что нужно для преобразования текста в речь, — это короткое имя, `en-US-AriaNeural`.

Вместо загрузки и декодирования всего списка на вашем микроконтроллере, вам нужно написать немного серверного кода, чтобы получить список голосов для используемого вами языка, и вызвать его с вашего Wio Terminal. Ваш код затем может выбрать подходящий голос из списка, например, первый найденный.

### Задача - создать серверную функцию для получения списка голосов

1. Откройте ваш проект `smart-timer-trigger` в VS Code и откройте терминал, убедившись, что виртуальная среда активирована. Если нет, завершите и создайте терминал заново.

1. Откройте файл `local.settings.json` и добавьте настройки для ключа API сервиса речи и его расположения:

    ```json
    "SPEECH_KEY": "<key>",
    "SPEECH_LOCATION": "<location>"
    ```

    Замените `<key>` на ключ API для вашего ресурса сервиса речи. Замените `<location>` на расположение, которое вы указали при создании ресурса сервиса речи.

1. Добавьте новый HTTP-триггер в это приложение под названием `get-voices`, используя следующую команду в терминале VS Code в корневой папке проекта приложения функций:

    ```sh
    func new --name get-voices --template "HTTP trigger"
    ```

    Это создаст HTTP-триггер под названием `get-voices`.

1. Замените содержимое файла `__init__.py` в папке `get-voices` следующим:

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

    Этот код выполняет HTTP-запрос к конечной точке для получения голосов. Список голосов представляет собой большой блок JSON с голосами для всех языков, поэтому голоса для языка, переданного в теле запроса, фильтруются, затем извлекается короткое имя и возвращается в виде JSON-списка. Короткое имя — это значение, необходимое для преобразования текста в речь, поэтому возвращается только оно.

    > 💁 Вы можете изменить фильтр по мере необходимости, чтобы выбрать только те голоса, которые вам нужны.

    Это уменьшает размер данных с 77 КБ (на момент написания) до гораздо меньшего JSON-документа. Например, для голосов США это 408 байт.

1. Запустите ваше приложение функций локально. Затем вы можете вызвать его с помощью инструмента, такого как curl, так же, как вы тестировали HTTP-триггер `text-to-timer`. Убедитесь, что вы передаете ваш язык в теле JSON:

    ```json
    {
        "language":"<language>"
    }
    ```

    Замените `<language>` на ваш язык, например, `en-GB` или `zh-CN`.

> 💁 Вы можете найти этот код в папке [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions).

### Задача - получить голос с вашего Wio Terminal

1. Откройте проект `smart-timer` в VS Code, если он еще не открыт.

1. Откройте заголовочный файл `config.h` и добавьте URL для вашего приложения функций:

    ```cpp
    const char *GET_VOICES_FUNCTION_URL = "<URL>";
    ```

    Замените `<URL>` на URL для HTTP-триггера `get-voices` вашего приложения функций. Это будет то же значение, что и для `TEXT_TO_TIMER_FUNCTION_URL`, за исключением имени функции `get-voices` вместо `text-to-timer`.

1. Создайте новый файл в папке `src` под названием `text_to_speech.h`. Этот файл будет использоваться для определения класса, который преобразует текст в речь.

1. Добавьте следующие директивы include в начало нового файла `text_to_speech.h`:

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

1. Добавьте следующий код ниже, чтобы объявить класс `TextToSpeech`, а также экземпляр, который можно использовать в остальной части приложения:

    ```cpp
    class TextToSpeech
    {
    public:
    private:
    };
    
    TextToSpeech textToSpeech;
    ```

1. Чтобы вызвать ваше приложение функций, вам нужно объявить WiFi-клиент. Добавьте следующее в секцию `private` класса:

    ```cpp
    WiFiClient _client;
    ```

1. В секции `private` добавьте поле для выбранного голоса:

    ```cpp
    String _voice;
    ```

1. В секции `public` добавьте функцию `init`, которая будет получать первый голос:

    ```cpp
    void init()
    {
    }
    ```

1. Чтобы получить голоса, необходимо отправить JSON-документ в приложение функций с указанием языка. Добавьте следующий код в функцию `init`, чтобы создать этот JSON-документ:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;

    String body;
    serializeJson(doc, body);
    ```

1. Затем создайте `HTTPClient`, а затем используйте его для вызова приложения функций, отправляя JSON-документ:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, GET_VOICES_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. Ниже добавьте код для проверки кода ответа, и если это 200 (успех), то извлеките список голосов, получая первый из списка:

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

1. После этого завершите соединение HTTP-клиента:

    ```cpp
    httpClient.end();
    ```

1. Откройте файл `main.cpp` и добавьте следующую директиву include в начало, чтобы включить этот новый заголовочный файл:

    ```cpp
    #include "text_to_speech.h"
    ```

1. В функции `setup`, под вызовом `speechToText.init();`, добавьте следующее для инициализации класса `TextToSpeech`:

    ```cpp
    textToSpeech.init();
    ```

1. Соберите этот код, загрузите его на ваш Wio Terminal и протестируйте через монитор последовательного порта. Убедитесь, что ваше приложение функций запущено.

    Вы увидите список доступных голосов, возвращенных из приложения функций, вместе с выбранным голосом.

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

## Преобразование текста в речь

Как только у вас есть голос для использования, его можно использовать для преобразования текста в речь. Те же ограничения памяти, что и для голосов, также применимы при преобразовании текста в речь, поэтому вам нужно будет записать речь на SD-карту, чтобы воспроизвести ее через ReSpeaker.

> 💁 В предыдущих уроках этого проекта вы использовали флэш-память для хранения речи, записанной с микрофона. В этом уроке используется SD-карта, так как с ней проще воспроизводить аудио, используя библиотеки Seeed.

Также есть еще одно ограничение, которое нужно учитывать — доступные аудиоданные от сервиса речи и форматы, которые поддерживает Wio Terminal. В отличие от полноценных компьютеров, аудиобиблиотеки для микроконтроллеров могут быть очень ограничены в поддерживаемых аудиоформатах. Например, библиотека Seeed Arduino Audio, которая может воспроизводить звук через ReSpeaker, поддерживает только аудио с частотой дискретизации 44.1 кГц. Сервисы речи Azure могут предоставлять аудио в нескольких форматах, но ни один из них не использует эту частоту дискретизации, они предоставляют только 8 кГц, 16 кГц, 24 кГц и 48 кГц. Это означает, что аудио нужно пересэмплировать до 44.1 кГц, что потребует больше ресурсов, чем есть у Wio Terminal, особенно памяти.

Когда требуется манипулировать данными такого рода, часто лучше использовать серверный код, особенно если данные получены через веб-запрос. Wio Terminal может вызвать серверную функцию, передав текст для преобразования, а серверная функция может как вызвать сервис речи для преобразования текста в речь, так и пересэмплировать аудио до нужной частоты дискретизации. Затем она может вернуть аудио в формате, который нужен Wio Terminal, чтобы сохранить его на SD-карте и воспроизвести через ReSpeaker.

### Задача - создать серверную функцию для преобразования текста в речь

1. Откройте ваш проект `smart-timer-trigger` в VS Code и откройте терминал, убедившись, что виртуальная среда активирована. Если нет, завершите и создайте терминал заново.

1. Добавьте новый HTTP-триггер в это приложение под названием `text-to-speech`, используя следующую команду в терминале VS Code в корневой папке проекта приложения функций:

    ```sh
    func new --name text-to-speech --template "HTTP trigger"
    ```

    Это создаст HTTP-триггер под названием `text-to-speech`.

1. Пакет Pip [librosa](https://librosa.org) содержит функции для пересэмплирования аудио, поэтому добавьте его в файл `requirements.txt`:

    ```sh
    librosa
    ```

    После этого установите пакеты Pip, используя следующую команду в терминале VS Code:

    ```sh
    pip install -r requirements.txt
    ```

    > ⚠️ Если вы используете Linux, включая Raspberry Pi OS, вам может понадобиться установить `libsndfile` с помощью следующей команды:
    >
    > ```sh
    > sudo apt update
    > sudo apt install libsndfile1-dev
    > ```

1. Для преобразования текста в речь вы не можете использовать ключ API сервиса речи напрямую, вместо этого вам нужно запросить токен доступа, используя ключ API для аутентификации запроса токена доступа. Откройте файл `__init__.py` из папки `text-to-speech` и замените весь код в нем следующим:

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

    Это определяет константы для расположения и ключа речи, которые будут считаны из настроек. Затем определяется функция `get_access_token`, которая будет получать токен доступа для сервиса речи.

1. Ниже этого кода добавьте следующее:

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

    Это определяет HTTP-триггер, который преобразует текст в речь. Он извлекает текст для преобразования, язык и голос из JSON-тела, переданного в запросе, создает SSML для запроса речи, затем вызывает соответствующий REST API, аутентифицируясь с помощью токена доступа. Этот вызов REST API возвращает аудио, закодированное как моно WAV-файл с частотой дискретизации 48 кГц и 16-битной глубиной, определенной значением `playback_format`, которое отправляется в вызов REST API.

    Затем это аудио пересэмплируется с помощью `librosa` с частоты дискретизации 48 кГц до частоты 44.1 кГц, затем это аудио сохраняется в двоичный буфер, который затем возвращается.

1. Запустите ваше приложение функций локально или разверните его в облаке. Затем вы можете вызвать его с помощью инструмента, такого как curl, так же, как вы тестировали HTTP-триггер `text-to-timer`. Убедитесь, что вы передаете язык, голос и текст в теле JSON:

    ```json
    {
        "language": "<language>",
        "voice": "<voice>",
        "text": "<text>"
    }
    ```

    Замените `<language>` на ваш язык, например, `en-GB` или `zh-CN`. Замените `<voice>` на голос, который вы хотите использовать. Замените `<text>` на текст, который вы хотите преобразовать в речь. Вы можете сохранить вывод в файл и воспроизвести его с помощью любого аудиоплеера, который поддерживает WAV-файлы.

    Например, чтобы преобразовать "Hello" в речь, используя английский язык США с голосом Jenny Neural, при локальном запуске приложения функций, вы можете использовать следующую команду curl:

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

    Это сохранит аудио в `hello.wav` в текущем каталоге.

> 💁 Вы можете найти этот код в папке [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions).

### Задача - получить речь с вашего Wio Terminal

1. Откройте проект `smart-timer` в VS Code, если он еще не открыт.

1. Откройте заголовочный файл `config.h` и добавьте URL для вашего приложения функций:

    ```cpp
    const char *TEXT_TO_SPEECH_FUNCTION_URL = "<URL>";
    ```

    Замените `<URL>` на URL для HTTP-триггера `text-to-speech` вашего приложения функций. Это будет то же значение, что и для `TEXT_TO_TIMER_FUNCTION_URL`, за исключением имени функции `text-to-speech` вместо `text-to-timer`.

1. Откройте заголовочный файл `text_to_speech.h` и добавьте следующий метод в секцию `public` класса `TextToSpeech`:

    ```cpp
    void convertTextToSpeech(String text)
    {
    }
    ```

1. В метод `convertTextToSpeech` добавьте следующий код для создания JSON, который будет отправлен в приложение функций:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;
    doc["voice"] = _voice;
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    Это записывает язык, голос и текст в JSON-документ, затем сериализует его в строку.

1. Ниже этого добавьте следующий код для вызова приложения функций:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_SPEECH_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    Это создает HTTPClient, затем выполняет POST-запрос с использованием JSON-документа к HTTP-триггеру `text-to-speech`.

1. Если вызов успешен, необработанные двоичные данные, возвращенные из вызова приложения функций, могут быть записаны в файл на SD-карте. Добавьте следующий код для выполнения этого:

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

    Этот код проверяет ответ, и если это 200 (успех), двоичные данные записываются в файл в корне SD-карты под названием `SPEECH.WAV`.

1. В конце этого метода закройте HTTP-соединение:

    ```cpp
    httpClient.end();
    ```

1. Теперь текст, который нужно произнести, можно преобразовать в аудио. В файле `main.cpp` добавьте следующую строку в конец функции `say`, чтобы преобразовать текст для произнесения в аудио:
```cpp
    textToSpeech.convertTextToSpeech(text);
    ```

### Задача - воспроизведение аудио на вашем Wio Terminal

**Скоро будет доступно**

## Развертывание вашего приложения функций в облаке

Причина запуска приложения функций локально заключается в том, что пакет `librosa` для Python на Linux имеет зависимость от библиотеки, которая не установлена по умолчанию и должна быть установлена перед запуском приложения функций. Приложения функций являются серверлесс-решениями - у вас нет серверов, которыми вы можете управлять самостоятельно, поэтому нет возможности заранее установить эту библиотеку.

Для этого необходимо развернуть ваше приложение функций с использованием Docker-контейнера. Этот контейнер разворачивается в облаке всякий раз, когда требуется запустить новый экземпляр вашего приложения функций (например, когда спрос превышает доступные ресурсы или если приложение функций не использовалось какое-то время и было закрыто).

Инструкции по настройке приложения функций и развертыванию через Docker можно найти в [документации Microsoft Docs о создании функции на Linux с использованием пользовательского контейнера](https://docs.microsoft.com/azure/azure-functions/functions-create-function-linux-custom-image?WT.mc_id=academic-17441-jabenn&tabs=bash%2Cazurecli&pivots=programming-language-python).

После развертывания вы можете адаптировать код вашего Wio Terminal для доступа к этой функции:

1. Добавьте сертификат Azure Functions в `config.h`:

    ```cpp
    const char *FUNCTIONS_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "MIIFWjCCBEKgAwIBAgIQDxSWXyAgaZlP1ceseIlB4jANBgkqhkiG9w0BAQsFADBa\r\n"
        "MQswCQYDVQQGEwJJRTESMBAGA1UEChMJQmFsdGltb3JlMRMwEQYDVQQLEwpDeWJl\r\n"
        "clRydXN0MSIwIAYDVQQDExlCYWx0aW1vcmUgQ3liZXJUcnVzdCBSb290MB4XDTIw\r\n"
        "MDcyMTIzMDAwMFoXDTI0MTAwODA3MDAwMFowTzELMAkGA1UEBhMCVVMxHjAcBgNV\r\n"
        "BAoTFU1pY3Jvc29mdCBDb3Jwb3JhdGlvbjEgMB4GA1UEAxMXTWljcm9zb2Z0IFJT\r\n"
        "QSBUTFMgQ0EgMDEwggIiMA0GCSqGSIb3DQEBAQUAA4ICDwAwggIKAoICAQCqYnfP\r\n"
        "mmOyBoTzkDb0mfMUUavqlQo7Rgb9EUEf/lsGWMk4bgj8T0RIzTqk970eouKVuL5R\r\n"
        "IMW/snBjXXgMQ8ApzWRJCZbar879BV8rKpHoAW4uGJssnNABf2n17j9TiFy6BWy+\r\n"
        "IhVnFILyLNK+W2M3zK9gheiWa2uACKhuvgCca5Vw/OQYErEdG7LBEzFnMzTmJcli\r\n"
        "W1iCdXby/vI/OxbfqkKD4zJtm45DJvC9Dh+hpzqvLMiK5uo/+aXSJY+SqhoIEpz+\r\n"
        "rErHw+uAlKuHFtEjSeeku8eR3+Z5ND9BSqc6JtLqb0bjOHPm5dSRrgt4nnil75bj\r\n"
        "c9j3lWXpBb9PXP9Sp/nPCK+nTQmZwHGjUnqlO9ebAVQD47ZisFonnDAmjrZNVqEX\r\n"
        "F3p7laEHrFMxttYuD81BdOzxAbL9Rb/8MeFGQjE2Qx65qgVfhH+RsYuuD9dUw/3w\r\n"
        "ZAhq05yO6nk07AM9c+AbNtRoEcdZcLCHfMDcbkXKNs5DJncCqXAN6LhXVERCw/us\r\n"
        "G2MmCMLSIx9/kwt8bwhUmitOXc6fpT7SmFvRAtvxg84wUkg4Y/Gx++0j0z6StSeN\r\n"
        "0EJz150jaHG6WV4HUqaWTb98Tm90IgXAU4AW2GBOlzFPiU5IY9jt+eXC2Q6yC/Zp\r\n"
        "TL1LAcnL3Qa/OgLrHN0wiw1KFGD51WRPQ0Sh7QIDAQABo4IBJTCCASEwHQYDVR0O\r\n"
        "BBYEFLV2DDARzseSQk1Mx1wsyKkM6AtkMB8GA1UdIwQYMBaAFOWdWTCCR1jMrPoI\r\n"
        "VDaGezq1BE3wMA4GA1UdDwEB/wQEAwIBhjAdBgNVHSUEFjAUBggrBgEFBQcDAQYI\r\n"
        "KwYBBQUHAwIwEgYDVR0TAQH/BAgwBgEB/wIBADA0BggrBgEFBQcBAQQoMCYwJAYI\r\n"
        "KwYBBQUHMAGGGGh0dHA6Ly9vY3NwLmRpZ2ljZXJ0LmNvbTA6BgNVHR8EMzAxMC+g\r\n"
        "LaArhilodHRwOi8vY3JsMy5kaWdpY2VydC5jb20vT21uaXJvb3QyMDI1LmNybDAq\r\n"
        "BgNVHSAEIzAhMAgGBmeBDAECATAIBgZngQwBAgIwCwYJKwYBBAGCNyoBMA0GCSqG\r\n"
        "SIb3DQEBCwUAA4IBAQCfK76SZ1vae4qt6P+dTQUO7bYNFUHR5hXcA2D59CJWnEj5\r\n"
        "na7aKzyowKvQupW4yMH9fGNxtsh6iJswRqOOfZYC4/giBO/gNsBvwr8uDW7t1nYo\r\n"
        "DYGHPpvnpxCM2mYfQFHq576/TmeYu1RZY29C4w8xYBlkAA8mDJfRhMCmehk7cN5F\r\n"
        "JtyWRj2cZj/hOoI45TYDBChXpOlLZKIYiG1giY16vhCRi6zmPzEwv+tk156N6cGS\r\n"
        "Vm44jTQ/rs1sa0JSYjzUaYngoFdZC4OfxnIkQvUIA4TOFmPzNPEFdjcZsgbeEz4T\r\n"
        "cGHTBPK4R28F44qIMCtHRV55VMX53ev6P3hRddJb\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

1. Замените все включения `
<WiFiClient.h>` на `<WiFiClientSecure.h>`.

1. Замените все поля `WiFiClient` на `WiFiClientSecure`.

1. В каждом классе, который содержит поле `WiFiClientSecure`, добавьте конструктор и установите сертификат в этом конструкторе:

    ```cpp
    _client.setCACert(FUNCTIONS_CERTIFICATE);
    ```

---

**Отказ от ответственности**:  
Этот документ был переведен с помощью сервиса автоматического перевода [Co-op Translator](https://github.com/Azure/co-op-translator). Несмотря на наши усилия обеспечить точность, автоматические переводы могут содержать ошибки или неточности. Оригинальный документ на его исходном языке следует считать авторитетным источником. Для получения критически важной информации рекомендуется профессиональный перевод человеком. Мы не несем ответственности за любые недоразумения или неправильные интерпретации, возникшие в результате использования данного перевода.