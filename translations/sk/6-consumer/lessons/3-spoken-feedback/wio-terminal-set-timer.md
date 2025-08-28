<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "012b69d57d898d670adf61304f42a137",
  "translation_date": "2025-08-28T09:03:59+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-set-timer.md",
  "language_code": "sk"
}
-->
# Nastavenie časovača - Wio Terminal

V tejto časti lekcie zavoláte svoj serverless kód na rozpoznanie reči a nastavíte časovač na vašom Wio Terminal na základe výsledkov.

## Nastavenie časovača

Text, ktorý sa vráti z volania prevodu reči na text, je potrebné poslať do vášho serverless kódu, aby ho spracoval LUIS a vrátil počet sekúnd pre časovač. Tento počet sekúnd sa potom použije na nastavenie časovača.

Mikrokontroléry nemajú natívnu podporu pre viacvláknové spracovanie v Arduino, takže neexistujú štandardné triedy časovačov, ako by ste mohli nájsť pri programovaní v Pythone alebo iných vyšších programovacích jazykoch. Namiesto toho môžete použiť knižnice časovačov, ktoré fungujú na základe merania uplynutého času vo funkcii `loop` a volania funkcií, keď čas vyprší.

### Úloha - odoslanie textu do serverless funkcie

1. Otvorte projekt `smart-timer` vo VS Code, ak ešte nie je otvorený.

1. Otvorte hlavičkový súbor `config.h` a pridajte URL adresu pre vašu funkciu:

    ```cpp
    const char *TEXT_TO_TIMER_FUNCTION_URL = "<URL>";
    ```

    Nahraďte `<URL>` URL adresou vašej funkcie, ktorú ste získali v poslednom kroku predchádzajúcej lekcie, ukazujúcou na IP adresu vášho lokálneho počítača, na ktorom beží funkcia.

1. Vytvorte nový súbor v priečinku `src` s názvom `language_understanding.h`. Tento súbor bude použitý na definovanie triedy, ktorá odošle rozpoznanú reč do vašej funkcie na konverziu na sekundy pomocou LUIS.

1. Pridajte na začiatok tohto súboru nasledujúci kód:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    ```

    Tento kód obsahuje potrebné hlavičkové súbory.

1. Definujte triedu s názvom `LanguageUnderstanding` a deklarujte inštanciu tejto triedy:

    ```cpp
    class LanguageUnderstanding
    {
    public:
    private:
    };

    LanguageUnderstanding languageUnderstanding;
    ```

1. Na volanie vašej funkcie je potrebné deklarovať WiFi klienta. Pridajte nasledujúci kód do sekcie `private` triedy:

    ```cpp
    WiFiClient _client;
    ```

1. V sekcii `public` deklarujte metódu s názvom `GetTimerDuration` na volanie funkcie:

    ```cpp
    int GetTimerDuration(String text)
    {
    }
    ```

1. V metóde `GetTimerDuration` pridajte nasledujúci kód na vytvorenie JSON, ktorý sa odošle do funkcie:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    Tento kód konvertuje text odovzdaný do metódy `GetTimerDuration` na nasledujúci JSON:

    ```json
    {
        "text" : "<text>"
    }
    ```

    kde `<text>` je text odovzdaný do funkcie.

1. Pod týmto kódom pridajte nasledujúci kód na volanie funkcie:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_TIMER_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    Tento kód vykoná POST požiadavku na funkciu, odosiela JSON telo a získava kód odpovede.

1. Pridajte nasledujúci kód pod tento:

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

    Tento kód kontroluje kód odpovede. Ak je 200 (úspech), počet sekúnd pre časovač sa získa z tela odpovede. V opačnom prípade sa do sériového monitora odošle chyba a počet sekúnd sa nastaví na 0.

1. Pridajte nasledujúci kód na koniec tejto metódy na uzavretie HTTP pripojenia a vrátenie počtu sekúnd:

    ```cpp
    httpClient.end();

    return seconds;
    ```

1. V súbore `main.cpp` zahrňte tento nový hlavičkový súbor:

    ```cpp
    #include "speech_to_text.h"
    ```

1. Na konci funkcie `processAudio` zavolajte metódu `GetTimerDuration` na získanie trvania časovača:

    ```cpp
    int total_seconds = languageUnderstanding.GetTimerDuration(text);
    ```

    Tento kód konvertuje text z volania triedy `SpeechToText` na počet sekúnd pre časovač.

### Úloha - nastavenie časovača

Počet sekúnd sa môže použiť na nastavenie časovača.

1. Pridajte nasledujúcu závislosť knižnice do súboru `platformio.ini`, aby ste pridali knižnicu na nastavenie časovača:

    ```ini
    contrem/arduino-timer @ 2.3.0
    ```

1. Pridajte direktívu `include` pre túto knižnicu do súboru `main.cpp`:

    ```cpp
    #include <arduino-timer.h>
    ```

1. Nad funkciu `processAudio` pridajte nasledujúci kód:

    ```cpp
    auto timer = timer_create_default();
    ```

    Tento kód deklaruje časovač s názvom `timer`.

1. Pod tento kód pridajte nasledujúci kód:

    ```cpp
    void say(String text)
    {
        Serial.print("Saying ");
        Serial.println(text);
    }
    ```

    Táto funkcia `say` nakoniec prevedie text na reč, ale zatiaľ len zapíše odovzdaný text do sériového monitora.

1. Pod funkciu `say` pridajte nasledujúci kód:

    ```cpp
    bool timerExpired(void *announcement)
    {
        say((char *)announcement);
        return false;
    }
    ```

    Toto je spätná volacia funkcia, ktorá sa zavolá, keď časovač vyprší. Funkcia dostane správu, ktorú má oznámiť, keď časovač vyprší. Časovače môžu byť opakované, čo sa riadi návratovou hodnotou tejto funkcie - táto funkcia vráti `false`, aby časovač nebežal znova.

1. Pridajte nasledujúci kód na koniec funkcie `processAudio`:

    ```cpp
    if (total_seconds == 0)
    {
        return;
    }

    int minutes = total_seconds / 60;
    int seconds = total_seconds % 60;
    ```

    Tento kód kontroluje celkový počet sekúnd a ak je 0, vráti sa z funkcie, aby sa žiadne časovače nenastavili. Potom konvertuje celkový počet sekúnd na minúty a sekundy.

1. Pod tento kód pridajte nasledujúci kód na vytvorenie správy, ktorá sa oznámi, keď sa časovač spustí:

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

1. Pod tento kód pridajte podobný kód na vytvorenie správy, ktorá sa oznámi, keď časovač vyprší:

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

1. Po tomto kóde oznámte správu o spustení časovača:

    ```cpp
    say(begin_message);
    ```

1. Na konci tejto funkcie spustite časovač:

    ```cpp
    timer.in(total_seconds * 1000, timerExpired, (void *)(end_message.c_str()));
    ```

    Tento kód spustí časovač. Časovač je nastavený v milisekundách, takže celkový počet sekúnd sa vynásobí 1 000 na konverziu na milisekundy. Funkcia `timerExpired` je odovzdaná ako spätná volacia funkcia a `end_message` je odovzdaná ako argument pre spätnú volaciu funkciu. Táto funkcia prijíma iba argumenty typu `void *`, takže reťazec je vhodne konvertovaný.

1. Nakoniec je potrebné, aby časovač *tikotal*, a to sa vykonáva vo funkcii `loop`. Pridajte nasledujúci kód na koniec funkcie `loop`:

    ```cpp
    timer.tick();
    ```

1. Zostavte tento kód, nahrajte ho do vášho Wio Terminal a otestujte ho cez sériový monitor. Keď uvidíte `Ready` v sériovom monitore, stlačte tlačidlo C (to na ľavej strane, najbližšie k vypínaču) a hovorte. 4 sekundy zvuku sa zachytia, prevedú na text, potom sa odošlú do vašej funkcie a nastaví sa časovač. Uistite sa, že vaša funkcia beží lokálne.

    Uvidíte, kedy sa časovač spustí a kedy skončí.

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

> 💁 Tento kód nájdete v priečinku [code-timer/wio-terminal](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/wio-terminal).

😀 Váš program časovača bol úspešný!

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby na automatický preklad [Co-op Translator](https://github.com/Azure/co-op-translator). Hoci sa snažíme o presnosť, upozorňujeme, že automatické preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho pôvodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre dôležité informácie odporúčame profesionálny ľudský preklad. Nezodpovedáme za žiadne nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.