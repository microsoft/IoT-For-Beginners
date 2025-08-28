<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "012b69d57d898d670adf61304f42a137",
  "translation_date": "2025-08-28T16:21:33+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-set-timer.md",
  "language_code": "uk"
}
-->
# Встановлення таймера - Wio Terminal

У цій частині уроку ви викличете свій безсерверний код для розпізнавання мовлення та встановите таймер на Wio Terminal на основі отриманих результатів.

## Встановлення таймера

Текст, який повертається після виклику функції перетворення мовлення в текст, потрібно надіслати до вашого безсерверного коду для обробки через LUIS, щоб отримати кількість секунд для таймера. Ця кількість секунд може бути використана для встановлення таймера.

Мікроконтролери не мають вбудованої підтримки багатопоточності в Arduino, тому стандартні класи таймерів, які можна знайти в Python або інших мовах високого рівня, недоступні. Натомість можна використовувати бібліотеки таймерів, які працюють шляхом вимірювання часу, що минув, у функції `loop`, і викликають функції, коли час закінчується.

### Завдання - надіслати текст до безсерверної функції

1. Відкрийте проект `smart-timer` у VS Code, якщо він ще не відкритий.

1. Відкрийте заголовковий файл `config.h` і додайте URL-адресу для вашого додатку функцій:

    ```cpp
    const char *TEXT_TO_TIMER_FUNCTION_URL = "<URL>";
    ```

    Замініть `<URL>` на URL-адресу вашого додатку функцій, яку ви отримали на останньому кроці попереднього уроку, вказуючи IP-адресу вашого локального комп'ютера, на якому працює додаток функцій.

1. Створіть новий файл у папці `src` під назвою `language_understanding.h`. У цьому файлі буде визначено клас для надсилання розпізнаного мовлення до вашого додатку функцій для перетворення в секунди за допомогою LUIS.

1. Додайте наступне до верхньої частини цього файлу:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    ```

    Це включає необхідні заголовкові файли.

1. Визначте клас під назвою `LanguageUnderstanding` і оголосіть екземпляр цього класу:

    ```cpp
    class LanguageUnderstanding
    {
    public:
    private:
    };

    LanguageUnderstanding languageUnderstanding;
    ```

1. Для виклику вашого додатку функцій потрібно оголосити WiFi-клієнт. Додайте наступне до секції `private` класу:

    ```cpp
    WiFiClient _client;
    ```

1. У секції `public` оголосіть метод під назвою `GetTimerDuration` для виклику додатку функцій:

    ```cpp
    int GetTimerDuration(String text)
    {
    }
    ```

1. У методі `GetTimerDuration` додайте наступний код для створення JSON, який буде надіслано до додатку функцій:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    Це перетворює текст, переданий до методу `GetTimerDuration`, у наступний JSON:

    ```json
    {
        "text" : "<text>"
    }
    ```

    де `<text>` — це текст, переданий до функції.

1. Нижче цього додайте наступний код для виклику додатку функцій:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_TIMER_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    Це робить POST-запит до додатку функцій, передаючи JSON-тіло і отримуючи код відповіді.

1. Додайте наступний код нижче цього:

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

    Цей код перевіряє код відповіді. Якщо це 200 (успіх), то кількість секунд для таймера отримується з тіла відповіді. В іншому випадку помилка надсилається до серійного монітора, а кількість секунд встановлюється на 0.

1. Додайте наступний код до кінця цього методу для закриття HTTP-з'єднання і повернення кількості секунд:

    ```cpp
    httpClient.end();

    return seconds;
    ```

1. У файлі `main.cpp` включіть цей новий заголовковий файл:

    ```cpp
    #include "speech_to_text.h"
    ```

1. У кінці функції `processAudio` викличте метод `GetTimerDuration`, щоб отримати тривалість таймера:

    ```cpp
    int total_seconds = languageUnderstanding.GetTimerDuration(text);
    ```

    Це перетворює текст із виклику класу `SpeechToText` у кількість секунд для таймера.

### Завдання - встановлення таймера

Кількість секунд може бути використана для встановлення таймера.

1. Додайте наступну залежність бібліотеки до файлу `platformio.ini`, щоб додати бібліотеку для встановлення таймера:

    ```ini
    contrem/arduino-timer @ 2.3.0
    ```

1. Додайте директиву включення для цієї бібліотеки до файлу `main.cpp`:

    ```cpp
    #include <arduino-timer.h>
    ```

1. Над функцією `processAudio` додайте наступний код:

    ```cpp
    auto timer = timer_create_default();
    ```

    Цей код оголошує таймер під назвою `timer`.

1. Нижче цього додайте наступний код:

    ```cpp
    void say(String text)
    {
        Serial.print("Saying ");
        Serial.println(text);
    }
    ```

    Ця функція `say` згодом перетворюватиме текст у мовлення, але наразі вона просто записує переданий текст до серійного монітора.

1. Нижче функції `say` додайте наступний код:

    ```cpp
    bool timerExpired(void *announcement)
    {
        say((char *)announcement);
        return false;
    }
    ```

    Це функція зворотного виклику, яка буде викликана, коли таймер закінчиться. Їй передається повідомлення, яке потрібно озвучити, коли таймер закінчиться. Таймери можуть повторюватися, і це можна контролювати через значення, яке повертає ця функція зворотного виклику — тут повертається `false`, щоб повідомити таймеру не запускатися знову.

1. Додайте наступний код до кінця функції `processAudio`:

    ```cpp
    if (total_seconds == 0)
    {
        return;
    }

    int minutes = total_seconds / 60;
    int seconds = total_seconds % 60;
    ```

    Цей код перевіряє загальну кількість секунд, і якщо вона дорівнює 0, виходить із виклику функції, щоб таймери не встановлювалися. Потім він перетворює загальну кількість секунд у хвилини і секунди.

1. Нижче цього коду додайте наступне для створення повідомлення, яке буде озвучено при запуску таймера:

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

1. Нижче цього додайте схожий код для створення повідомлення, яке буде озвучено, коли таймер закінчиться:

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

1. Після цього озвучте повідомлення про запуск таймера:

    ```cpp
    say(begin_message);
    ```

1. У кінці цієї функції запустіть таймер:

    ```cpp
    timer.in(total_seconds * 1000, timerExpired, (void *)(end_message.c_str()));
    ```

    Це запускає таймер. Таймер встановлюється у мілісекундах, тому загальна кількість секунд множиться на 1,000 для перетворення у мілісекунди. Функція `timerExpired` передається як зворотний виклик, а `end_message` передається як аргумент для зворотного виклику. Цей зворотний виклик приймає лише аргументи типу `void *`, тому рядок перетворюється відповідним чином.

1. Нарешті, таймер має *тікати*, і це робиться у функції `loop`. Додайте наступний код до кінця функції `loop`:

    ```cpp
    timer.tick();
    ```

1. Зберіть цей код, завантажте його на ваш Wio Terminal і протестуйте через серійний монітор. Як тільки ви побачите `Ready` у серійному моніторі, натисніть кнопку C (ту, що зліва, найближче до перемикача живлення) і говоріть. 4 секунди аудіо будуть записані, перетворені у текст, потім надіслані до вашого додатку функцій, і таймер буде встановлений. Переконайтеся, що ваш додаток функцій працює локально.

    Ви побачите, коли таймер запуститься і коли він закінчиться.

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

> 💁 Ви можете знайти цей код у папці [code-timer/wio-terminal](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/wio-terminal).

😀 Ваш таймер успішно працює!

---

**Відмова від відповідальності**:  
Цей документ був перекладений за допомогою сервісу автоматичного перекладу [Co-op Translator](https://github.com/Azure/co-op-translator). Хоча ми прагнемо до точності, будь ласка, майте на увазі, що автоматичні переклади можуть містити помилки або неточності. Оригінальний документ на його рідній мові слід вважати авторитетним джерелом. Для критично важливої інформації рекомендується професійний людський переклад. Ми не несемо відповідальності за будь-які непорозуміння або неправильні тлумачення, що виникають внаслідок використання цього перекладу.