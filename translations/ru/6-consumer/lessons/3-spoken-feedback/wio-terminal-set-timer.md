<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "012b69d57d898d670adf61304f42a137",
  "translation_date": "2025-08-27T00:10:57+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-set-timer.md",
  "language_code": "ru"
}
-->
# Установить таймер - Wio Terminal

В этой части урока вы вызовете свой серверless-код для распознавания речи и установите таймер на Wio Terminal на основе полученных результатов.

## Установить таймер

Текст, возвращаемый вызовом преобразования речи в текст, необходимо отправить в ваш серверless-код для обработки с помощью LUIS, чтобы получить количество секунд для таймера. Это количество секунд можно использовать для установки таймера.

Микроконтроллеры не поддерживают многопоточность в Arduino, поэтому стандартные классы таймеров, как в Python или других языках высокого уровня, отсутствуют. Вместо этого можно использовать библиотеки таймеров, которые измеряют прошедшее время в функции `loop` и вызывают функции, когда время истекает.

### Задача - отправить текст в серверless-функцию

1. Откройте проект `smart-timer` в VS Code, если он еще не открыт.

1. Откройте заголовочный файл `config.h` и добавьте URL для вашего приложения-функции:

    ```cpp
    const char *TEXT_TO_TIMER_FUNCTION_URL = "<URL>";
    ```

    Замените `<URL>` на URL вашего приложения-функции, который вы получили на последнем шаге предыдущего урока, указав IP-адрес вашего локального компьютера, на котором работает приложение-функция.

1. Создайте новый файл в папке `src` с именем `language_understanding.h`. Этот файл будет использоваться для определения класса, который отправляет распознанную речь в ваше приложение-функцию для преобразования в секунды с помощью LUIS.

1. Добавьте следующее в начало этого файла:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    ```

    Это включает необходимые заголовочные файлы.

1. Определите класс с именем `LanguageUnderstanding` и объявите экземпляр этого класса:

    ```cpp
    class LanguageUnderstanding
    {
    public:
    private:
    };

    LanguageUnderstanding languageUnderstanding;
    ```

1. Для вызова вашего приложения-функции необходимо объявить WiFi-клиент. Добавьте следующее в секцию `private` класса:

    ```cpp
    WiFiClient _client;
    ```

1. В секции `public` объявите метод с именем `GetTimerDuration` для вызова приложения-функции:

    ```cpp
    int GetTimerDuration(String text)
    {
    }
    ```

1. В методе `GetTimerDuration` добавьте следующий код для создания JSON, который будет отправлен в приложение-функцию:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    Это преобразует текст, переданный в метод `GetTimerDuration`, в следующий JSON:

    ```json
    {
        "text" : "<text>"
    }
    ```

    где `<text>` — это текст, переданный функции.

1. Ниже добавьте следующий код для вызова приложения-функции:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_TIMER_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    Это выполняет POST-запрос к приложению-функции, передавая JSON-тело и получая код ответа.

1. Добавьте следующий код ниже:

    ```cpp
    int seconds = 0;
    if (httpResponseCode == 200)
    {
        String result = httpClient.getString();
        Serial.println(result);

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, result.c_str());

        JsonObject obj = doc.as<JsonObject>();
        seconds = obj["seconds"].as<int>();
    }
    else
    {
        Serial.print("Failed to understand text - error ");
        Serial.println(httpResponseCode);
    }
    ```

    Этот код проверяет код ответа. Если он равен 200 (успех), то количество секунд для таймера извлекается из тела ответа. В противном случае ошибка отправляется в монитор последовательного порта, а количество секунд устанавливается в 0.

1. Добавьте следующий код в конец этого метода для закрытия HTTP-соединения и возврата количества секунд:

    ```cpp
    httpClient.end();

    return seconds;
    ```

1. В файле `main.cpp` включите этот новый заголовочный файл:

    ```cpp
    #include "speech_to_text.h"
    ```

1. В конце функции `processAudio` вызовите метод `GetTimerDuration`, чтобы получить длительность таймера:

    ```cpp
    int total_seconds = languageUnderstanding.GetTimerDuration(text);
    ```

    Это преобразует текст из вызова класса `SpeechToText` в количество секунд для таймера.

### Задача - установить таймер

Количество секунд можно использовать для установки таймера.

1. Добавьте следующую зависимость библиотеки в файл `platformio.ini`, чтобы подключить библиотеку для установки таймера:

    ```ini
    contrem/arduino-timer @ 2.3.0
    ```

1. Добавьте директиву include для этой библиотеки в файл `main.cpp`:

    ```cpp
    #include <arduino-timer.h>
    ```

1. Над функцией `processAudio` добавьте следующий код:

    ```cpp
    auto timer = timer_create_default();
    ```

    Этот код объявляет таймер с именем `timer`.

1. Ниже добавьте следующий код:

    ```cpp
    void say(String text)
    {
        Serial.print("Saying ");
        Serial.println(text);
    }
    ```

    Эта функция `say` в будущем будет преобразовывать текст в речь, но пока она просто выводит переданный текст в монитор последовательного порта.

1. Ниже функции `say` добавьте следующий код:

    ```cpp
    bool timerExpired(void *announcement)
    {
        say((char *)announcement);
        return false;
    }
    ```

    Это функция обратного вызова, которая будет вызываться, когда таймер истечет. Ей передается сообщение, которое нужно озвучить при истечении таймера. Таймеры могут повторяться, и это можно контролировать с помощью возвращаемого значения этой функции обратного вызова — возвращается `false`, чтобы указать таймеру не запускаться снова.

1. Добавьте следующий код в конец функции `processAudio`:

    ```cpp
    if (total_seconds == 0)
    {
        return;
    }

    int minutes = total_seconds / 60;
    int seconds = total_seconds % 60;
    ```

    Этот код проверяет общее количество секунд, и если оно равно 0, возвращается из вызова функции, чтобы таймеры не устанавливались. Затем общее количество секунд преобразуется в минуты и секунды.

1. Ниже этого кода добавьте следующий код для создания сообщения, которое будет озвучено при запуске таймера:

    ```cpp
    String begin_message;
    if (minutes > 0)
    {
        begin_message += minutes;
        begin_message += " minute ";
    }
    if (seconds > 0)
    {
        begin_message += seconds;
        begin_message += " second ";
    }

    begin_message += "timer started.";
    ```

1. Ниже этого добавьте аналогичный код для создания сообщения, которое будет озвучено при истечении таймера:

    ```cpp
    String end_message("Times up on your ");
    if (minutes > 0)
    {
        end_message += minutes;
        end_message += " minute ";
    }
    if (seconds > 0)
    {
        end_message += seconds;
        end_message += " second ";
    }

    end_message += "timer.";
    ```

1. После этого озвучьте сообщение о запуске таймера:

    ```cpp
    say(begin_message);
    ```

1. В конце этой функции запустите таймер:

    ```cpp
    timer.in(total_seconds * 1000, timerExpired, (void *)(end_message.c_str()));
    ```

    Это запускает таймер. Таймер устанавливается в миллисекундах, поэтому общее количество секунд умножается на 1,000 для преобразования в миллисекунды. Функция `timerExpired` передается как обратный вызов, а `end_message` передается как аргумент для обратного вызова. Этот обратный вызов принимает только аргументы типа `void *`, поэтому строка преобразуется соответствующим образом.

1. Наконец, таймер должен *тикать*, и это делается в функции `loop`. Добавьте следующий код в конец функции `loop`:

    ```cpp
    timer.tick();
    ```

1. Соберите этот код, загрузите его на ваш Wio Terminal и протестируйте через монитор последовательного порта. Как только вы увидите `Ready` в мониторе последовательного порта, нажмите кнопку C (ту, что слева, ближе к переключателю питания) и говорите. Будет захвачено 4 секунды аудио, преобразовано в текст, затем отправлено в ваше приложение-функцию, и таймер будет установлен. Убедитесь, что ваше приложение-функция работает локально.

    Вы увидите, когда таймер начнется и когда он закончится.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Got access token.
    Ready.
    Starting recording...
    Finished recording
    Sending speech...
    Speech sent!
    {"RecognitionStatus":"Success","DisplayText":"Set a 2 minute and 27 second timer.","Offset":4700000,"Duration":35300000}
    Set a 2 minute and 27 second timer.
    {"seconds": 147}
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```

> 💁 Вы можете найти этот код в папке [code-timer/wio-terminal](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/wio-terminal).

😀 Ваше приложение таймера успешно работает!

---

**Отказ от ответственности**:  
Этот документ был переведен с помощью сервиса автоматического перевода [Co-op Translator](https://github.com/Azure/co-op-translator). Несмотря на наши усилия по обеспечению точности, пожалуйста, учитывайте, что автоматические переводы могут содержать ошибки или неточности. Оригинальный документ на его родном языке следует считать авторитетным источником. Для получения критически важной информации рекомендуется профессиональный перевод человеком. Мы не несем ответственности за любые недоразумения или неправильные интерпретации, возникшие в результате использования данного перевода.