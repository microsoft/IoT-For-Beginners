<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "012b69d57d898d670adf61304f42a137",
  "translation_date": "2025-08-28T12:46:31+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-set-timer.md",
  "language_code": "sr"
}
-->
# Поставите тајмер - Wio Terminal

У овом делу лекције, позваћете свој серверлес код да разумете говор и поставите тајмер на вашем Wio Terminal-у на основу резултата.

## Поставите тајмер

Текст који се враћа из позива за претварање говора у текст треба да се пошаље вашем серверлес коду да га обради LUIS, враћајући број секунди за тајмер. Овај број секунди може се користити за постављање тајмера.

Микроконтролери немају природну подршку за више нити у Arduino-у, па не постоје стандардне класе за тајмере као што их можете наћи када програмирате у Python-у или другим језицима вишег нивоа. Уместо тога, можете користити библиотеке за тајмере које раде мерењем протеклог времена у функцији `loop` и позивањем функција када време истекне.

### Задатак - пошаљите текст серверлес функцији

1. Отворите пројекат `smart-timer` у VS Code-у ако већ није отворен.

1. Отворите хедер датотеку `config.h` и додајте URL за вашу функцију апликације:

    ```cpp
    const char *TEXT_TO_TIMER_FUNCTION_URL = "<URL>";
    ```

    Замените `<URL>` са URL-ом за вашу функцију апликације коју сте добили у последњем кораку претходне лекције, указујући на IP адресу вашег локалног рачунара који покреће функцију апликације.

1. Направите нову датотеку у фолдеру `src` под називом `language_understanding.h`. Ова датотека ће се користити за дефинисање класе која шаље препознати говор вашој функцији апликације да би се претворио у секунде користећи LUIS.

1. Додајте следеће на врх ове датотеке:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    ```

    Ово укључује потребне хедер датотеке.

1. Дефинишите класу под називом `LanguageUnderstanding` и декларишите инстанцу ове класе:

    ```cpp
    class LanguageUnderstanding
    {
    public:
    private:
    };

    LanguageUnderstanding languageUnderstanding;
    ```

1. Да бисте позвали функцију апликације, потребно је да декларишете WiFi клијент. Додајте следеће у `private` секцију класе:

    ```cpp
    WiFiClient _client;
    ```

1. У `public` секцији, декларишите метод под називом `GetTimerDuration` за позивање функције апликације:

    ```cpp
    int GetTimerDuration(String text)
    {
    }
    ```

1. У методу `GetTimerDuration`, додајте следећи код за креирање JSON-а који ће се послати функцији апликације:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    Ово претвара текст прослеђен методу `GetTimerDuration` у следећи JSON:

    ```json
    {
        "text" : "<text>"
    }
    ```

    где је `<text>` текст прослеђен функцији.

1. Испод овога, додајте следећи код за позивање функције апликације:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_TIMER_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    Ово прави POST захтев функцији апликације, прослеђујући JSON тело и добијајући код одговора.

1. Додајте следећи код испод овога:

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

    Овај код проверава код одговора. Ако је 200 (успех), онда се број секунди за тајмер преузима из тела одговора. У супротном, грешка се шаље на серијски монитор, а број секунди се поставља на 0.

1. Додајте следећи код на крај овог метода да затворите HTTP везу и вратите број секунди:

    ```cpp
    httpClient.end();

    return seconds;
    ```

1. У датотеци `main.cpp`, укључите овај нови хедер:

    ```cpp
    #include "speech_to_text.h"
    ```

1. На крају функције `processAudio`, позовите метод `GetTimerDuration` да добијете трајање тајмера:

    ```cpp
    int total_seconds = languageUnderstanding.GetTimerDuration(text);
    ```

    Ово претвара текст из позива класи `SpeechToText` у број секунди за тајмер.

### Задатак - поставите тајмер

Број секунди може се користити за постављање тајмера.

1. Додајте следећу зависност библиотеке у датотеку `platformio.ini` да бисте додали библиотеку за постављање тајмера:

    ```ini
    contrem/arduino-timer @ 2.3.0
    ```

1. Додајте директиву за укључивање ове библиотеке у датотеку `main.cpp`:

    ```cpp
    #include <arduino-timer.h>
    ```

1. Изнад функције `processAudio`, додајте следећи код:

    ```cpp
    auto timer = timer_create_default();
    ```

    Овај код декларише тајмер под називом `timer`.

1. Испод овога, додајте следећи код:

    ```cpp
    void say(String text)
    {
        Serial.print("Saying ");
        Serial.println(text);
    }
    ```

    Ова функција `say` ће на крају претварати текст у говор, али за сада ће само писати прослеђени текст на серијски монитор.

1. Испод функције `say`, додајте следећи код:

    ```cpp
    bool timerExpired(void *announcement)
    {
        say((char *)announcement);
        return false;
    }
    ```

    Ово је функција повратног позива која ће се позвати када тајмер истекне. Прослеђује се порука која ће се изговорити када тајмер истекне. Тајмери могу да се понављају, а ово се контролише повратном вредношћу овог позива - враћа `false`, да би се тајмеру рекло да се не покреће поново.

1. Додајте следећи код на крај функције `processAudio`:

    ```cpp
    if (total_seconds == 0)
    {
        return;
    }

    int minutes = total_seconds / 60;
    int seconds = total_seconds % 60;
    ```

    Овај код проверава укупан број секунди, и ако је 0, враћа се из позива функције тако да се тајмери не постављају. Затим претвара укупан број секунди у минуте и секунде.

1. Испод овог кода, додајте следеће да креирате поруку која ће се изговорити када се тајмер покрене:

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

1. Испод овога, додајте сличан код да креирате поруку која ће се изговорити када тајмер истекне:

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

1. Након овога, изговорите поруку о покретању тајмера:

    ```cpp
    say(begin_message);
    ```

1. На крају ове функције, покрените тајмер:

    ```cpp
    timer.in(total_seconds * 1000, timerExpired, (void *)(end_message.c_str()));
    ```

    Ово покреће тајмер. Тајмер се поставља користећи милисекунде, па се укупан број секунди множи са 1,000 да би се претворио у милисекунде. Функција `timerExpired` се прослеђује као повратни позив, а `end_message` се прослеђује као аргумент који се прослеђује повратном позиву. Овај повратни позив прихвата само аргументе типа `void *`, па се стринг одговарајуће конвертује.

1. На крају, тајмер треба да *тиктака*, а то се ради у функцији `loop`. Додајте следећи код на крај функције `loop`:

    ```cpp
    timer.tick();
    ```

1. Изградите овај код, отпремите га на ваш Wio Terminal и тестирајте га преко серијског монитора. Када видите `Ready` на серијском монитору, притисните C дугме (оно са леве стране, најближе прекидачу за напајање), и говорите. 4 секунде аудио снимка ће бити снимљено, претворено у текст, затим послато вашој функцији апликације, и тајмер ће бити постављен. Уверите се да ваша функција апликације ради локално.

    Видећете када се тајмер покрене и када истекне.

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

> 💁 Овај код можете пронаћи у фолдеру [code-timer/wio-terminal](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/wio-terminal).

😀 Ваш програм за тајмер је био успешан!

---

**Одрицање од одговорности**:  
Овај документ је преведен коришћењем услуге за превођење помоћу вештачке интелигенције [Co-op Translator](https://github.com/Azure/co-op-translator). Иако настојимо да обезбедимо тачност, молимо вас да имате у виду да аутоматски преводи могу садржати грешке или нетачности. Оригинални документ на његовом изворном језику треба сматрати ауторитативним извором. За критичне информације препоручује се професионални превод од стране људи. Не преузимамо одговорност за било каква погрешна тумачења или неспоразуме који могу настати услед коришћења овог превода.