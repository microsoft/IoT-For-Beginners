<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "012b69d57d898d670adf61304f42a137",
  "translation_date": "2025-08-28T09:05:10+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-set-timer.md",
  "language_code": "bg"
}
-->
# Настройване на таймер - Wio Terminal

В тази част от урока ще извикате вашия serverless код, за да разпознаете речта, и ще настроите таймер на вашия Wio Terminal въз основа на резултатите.

## Настройване на таймер

Текстът, който се връща от преобразуването на реч в текст, трябва да бъде изпратен към вашия serverless код, за да бъде обработен от LUIS, който ще върне броя секунди за таймера. Този брой секунди може да се използва за настройване на таймер.

Микроконтролерите нямат вградена поддръжка за множество нишки в Arduino, така че няма стандартни класове за таймери, както може да срещнете при програмиране на Python или други езици от по-високо ниво. Вместо това можете да използвате библиотеки за таймери, които работят чрез измерване на изминалото време във функцията `loop` и извикване на функции, когато времето изтече.

### Задача - изпратете текста към serverless функцията

1. Отворете проекта `smart-timer` във VS Code, ако вече не е отворен.

1. Отворете хедър файла `config.h` и добавете URL адреса за вашето приложение:

    ```cpp
    const char *TEXT_TO_TIMER_FUNCTION_URL = "<URL>";
    ```

    Заменете `<URL>` с URL адреса на вашето приложение, който получихте в последната стъпка от предишния урок, сочещ към IP адреса на вашата локална машина, на която работи приложението.

1. Създайте нов файл в папката `src`, наречен `language_understanding.h`. Този файл ще се използва за дефиниране на клас, който ще изпраща разпознатата реч към вашето приложение, за да бъде преобразувана в секунди чрез LUIS.

1. Добавете следното в началото на този файл:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    ```

    Това включва необходимите хедър файлове.

1. Дефинирайте клас, наречен `LanguageUnderstanding`, и декларирайте инстанция на този клас:

    ```cpp
    class LanguageUnderstanding
    {
    public:
    private:
    };

    LanguageUnderstanding languageUnderstanding;
    ```

1. За да извикате вашето приложение, трябва да декларирате WiFi клиент. Добавете следното в секцията `private` на класа:

    ```cpp
    WiFiClient _client;
    ```

1. В секцията `public` декларирайте метод, наречен `GetTimerDuration`, за да извикате приложението:

    ```cpp
    int GetTimerDuration(String text)
    {
    }
    ```

1. В метода `GetTimerDuration` добавете следния код, за да създадете JSON, който ще бъде изпратен към приложението:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    Това преобразува текста, предаден на метода `GetTimerDuration`, в следния JSON:

    ```json
    {
        "text" : "<text>"
    }
    ```

    където `<text>` е текстът, предаден на функцията.

1. Под това добавете следния код, за да извършите извикването към приложението:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_TIMER_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    Това прави POST заявка към приложението, като предава JSON тялото и получава кода на отговора.

1. Добавете следния код под това:

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

    Този код проверява кода на отговора. Ако е 200 (успех), броят секунди за таймера се извлича от тялото на отговора. В противен случай се изпраща грешка към серийния монитор и броят секунди се задава на 0.

1. Добавете следния код в края на този метод, за да затворите HTTP връзката и да върнете броя секунди:

    ```cpp
    httpClient.end();

    return seconds;
    ```

1. Във файла `main.cpp` включете този нов хедър:

    ```cpp
    #include "speech_to_text.h"
    ```

1. В края на функцията `processAudio` извикайте метода `GetTimerDuration`, за да получите продължителността на таймера:

    ```cpp
    int total_seconds = languageUnderstanding.GetTimerDuration(text);
    ```

    Това преобразува текста от извикването към класа `SpeechToText` в броя секунди за таймера.

### Задача - настройване на таймер

Броят секунди може да се използва за настройване на таймер.

1. Добавете следната зависимост към файла `platformio.ini`, за да добавите библиотека за настройване на таймер:

    ```ini
    contrem/arduino-timer @ 2.3.0
    ```

1. Добавете директива за включване на тази библиотека във файла `main.cpp`:

    ```cpp
    #include <arduino-timer.h>
    ```

1. Над функцията `processAudio` добавете следния код:

    ```cpp
    auto timer = timer_create_default();
    ```

    Този код декларира таймер, наречен `timer`.

1. Под това добавете следния код:

    ```cpp
    void say(String text)
    {
        Serial.print("Saying ");
        Serial.println(text);
    }
    ```

    Тази функция `say` в крайна сметка ще преобразува текст в реч, но засега просто ще записва предадения текст в серийния монитор.

1. Под функцията `say` добавете следния код:

    ```cpp
    bool timerExpired(void *announcement)
    {
        say((char *)announcement);
        return false;
    }
    ```

    Това е функция за обратно извикване, която ще се извиква, когато таймерът изтече. Тя получава съобщение, което да се каже, когато таймерът изтече. Таймерите могат да се повтарят, а това се контролира от стойността, която връща тази функция - тук тя връща `false`, за да укаже, че таймерът не трябва да се изпълнява отново.

1. Добавете следния код в края на функцията `processAudio`:

    ```cpp
    if (total_seconds == 0)
    {
        return;
    }

    int minutes = total_seconds / 60;
    int seconds = total_seconds % 60;
    ```

    Този код проверява общия брой секунди и ако е 0, връща от функцията, така че да не се настройват таймери. След това преобразува общия брой секунди в минути и секунди.

1. Под този код добавете следното, за да създадете съобщение, което да се каже, когато таймерът започне:

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

1. Под това добавете подобен код, за да създадете съобщение, което да се каже, когато таймерът изтече:

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

1. След това кажете съобщението за стартиране на таймера:

    ```cpp
    say(begin_message);
    ```

1. В края на тази функция стартирайте таймера:

    ```cpp
    timer.in(total_seconds * 1000, timerExpired, (void *)(end_message.c_str()));
    ```

    Това задейства таймера. Таймерът се настройва с помощта на милисекунди, така че общият брой секунди се умножава по 1,000, за да се преобразува в милисекунди. Функцията `timerExpired` се предава като обратно извикване, а `end_message` се предава като аргумент към обратното извикване. Това обратно извикване приема само аргументи от тип `void *`, така че низът се преобразува съответно.

1. Накрая, таймерът трябва да "тиктака", и това се прави във функцията `loop`. Добавете следния код в края на функцията `loop`:

    ```cpp
    timer.tick();
    ```

1. Създайте този код, качете го на вашия Wio Terminal и го тествайте чрез серийния монитор. След като видите `Ready` в серийния монитор, натиснете бутон C (този от лявата страна, най-близо до превключвателя за захранване) и говорете. Ще бъдат записани 4 секунди аудио, преобразувани в текст, след това изпратени към вашето приложение, и ще бъде настроен таймер. Уверете се, че вашето приложение работи локално.

    Ще видите кога таймерът започва и кога приключва.

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

> 💁 Можете да намерите този код в папката [code-timer/wio-terminal](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/wio-terminal).

😀 Вашата програма за таймер беше успешна!

---

**Отказ от отговорност**:  
Този документ е преведен с помощта на AI услуга за превод [Co-op Translator](https://github.com/Azure/co-op-translator). Въпреки че се стремим към точност, моля, имайте предвид, че автоматизираните преводи може да съдържат грешки или неточности. Оригиналният документ на неговия роден език трябва да се счита за авторитетен източник. За критична информация се препоръчва професионален човешки превод. Ние не носим отговорност за каквито и да е недоразумения или погрешни интерпретации, произтичащи от използването на този превод.