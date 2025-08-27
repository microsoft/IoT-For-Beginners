<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "012b69d57d898d670adf61304f42a137",
  "translation_date": "2025-08-27T21:14:33+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-set-timer.md",
  "language_code": "cs"
}
-->
# Nastavení časovače - Wio Terminal

V této části lekce zavoláte svůj serverless kód, abyste porozuměli řeči, a na základě výsledků nastavíte časovač na svém Wio Terminalu.

## Nastavení časovače

Text, který se vrátí z volání převodu řeči na text, je třeba odeslat do vašeho serverless kódu, aby jej zpracoval LUIS a vrátil počet sekund pro časovač. Tento počet sekund lze použít k nastavení časovače.

Mikrokontroléry nemají nativní podporu pro více vláken v Arduino, takže zde nejsou standardní třídy časovačů, jaké byste mohli najít při programování v Pythonu nebo jiných vyšších programovacích jazycích. Místo toho můžete použít knihovny časovačů, které fungují měřením uplynulého času ve funkci `loop` a voláním funkcí, když čas vyprší.

### Úkol - odeslání textu do serverless funkce

1. Otevřete projekt `smart-timer` ve VS Code, pokud již není otevřený.

1. Otevřete hlavičkový soubor `config.h` a přidejte URL pro vaši funkci:

    ```cpp
    const char *TEXT_TO_TIMER_FUNCTION_URL = "<URL>";
    ```

    Nahraďte `<URL>` URL adresou vaší funkce, kterou jste získali v posledním kroku předchozí lekce, a která ukazuje na IP adresu vašeho lokálního počítače, kde běží funkce.

1. Vytvořte nový soubor ve složce `src` s názvem `language_understanding.h`. Tento soubor bude použit k definování třídy, která odešle rozpoznanou řeč do vaší funkce a převede ji na sekundy pomocí LUIS.

1. Přidejte následující na začátek tohoto souboru:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    ```

    To zahrnuje potřebné hlavičkové soubory.

1. Definujte třídu s názvem `LanguageUnderstanding` a deklarujte instanci této třídy:

    ```cpp
    class LanguageUnderstanding
    {
    public:
    private:
    };

    LanguageUnderstanding languageUnderstanding;
    ```

1. Pro volání vaší funkce je třeba deklarovat WiFi klienta. Přidejte následující do sekce `private` třídy:

    ```cpp
    WiFiClient _client;
    ```

1. V sekci `public` deklarujte metodu s názvem `GetTimerDuration` pro volání funkce:

    ```cpp
    int GetTimerDuration(String text)
    {
    }
    ```

1. V metodě `GetTimerDuration` přidejte následující kód pro sestavení JSON, který bude odeslán do funkce:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    Tento kód převede text předaný metodě `GetTimerDuration` na následující JSON:

    ```json
    {
        "text" : "<text>"
    }
    ```

    kde `<text>` je text předaný funkci.

1. Pod tímto kódem přidejte následující kód pro volání funkce:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_TIMER_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    Tento kód provede POST požadavek na funkci, předá JSON tělo a získá kód odpovědi.

1. Přidejte následující kód pod tento blok:

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

    Tento kód zkontroluje kód odpovědi. Pokud je 200 (úspěch), pak se počet sekund pro časovač získá z těla odpovědi. Jinak se do sériového monitoru odešle chyba a počet sekund se nastaví na 0.

1. Přidejte následující kód na konec této metody pro uzavření HTTP připojení a vrácení počtu sekund:

    ```cpp
    httpClient.end();

    return seconds;
    ```

1. V souboru `main.cpp` zahrňte tento nový hlavičkový soubor:

    ```cpp
    #include "speech_to_text.h"
    ```

1. Na konci funkce `processAudio` zavolejte metodu `GetTimerDuration`, abyste získali dobu trvání časovače:

    ```cpp
    int total_seconds = languageUnderstanding.GetTimerDuration(text);
    ```

    Tento kód převede text z volání třídy `SpeechToText` na počet sekund pro časovač.

### Úkol - nastavení časovače

Počet sekund lze použít k nastavení časovače.

1. Přidejte následující závislost knihovny do souboru `platformio.ini`, abyste přidali knihovnu pro nastavení časovače:

    ```ini
    contrem/arduino-timer @ 2.3.0
    ```

1. Přidejte direktivu pro zahrnutí této knihovny do souboru `main.cpp`:

    ```cpp
    #include <arduino-timer.h>
    ```

1. Nad funkcí `processAudio` přidejte následující kód:

    ```cpp
    auto timer = timer_create_default();
    ```

    Tento kód deklaruje časovač s názvem `timer`.

1. Pod tímto kódem přidejte následující:

    ```cpp
    void say(String text)
    {
        Serial.print("Saying ");
        Serial.println(text);
    }
    ```

    Tato funkce `say` nakonec převede text na řeč, ale prozatím pouze zapíše předaný text do sériového monitoru.

1. Pod funkcí `say` přidejte následující kód:

    ```cpp
    bool timerExpired(void *announcement)
    {
        say((char *)announcement);
        return false;
    }
    ```

    Toto je zpětně volaná funkce, která bude volána, když časovač vyprší. Je jí předána zpráva, která se má říct, když časovač vyprší. Časovače se mohou opakovat, a to lze ovládat návratovou hodnotou této funkce - zde vrací `false`, aby časovač neběžel znovu.

1. Přidejte následující kód na konec funkce `processAudio`:

    ```cpp
    if (total_seconds == 0)
    {
        return;
    }

    int minutes = total_seconds / 60;
    int seconds = total_seconds % 60;
    ```

    Tento kód zkontroluje celkový počet sekund, a pokud je 0, vrátí se z funkce, aby se žádné časovače nenastavily. Poté převede celkový počet sekund na minuty a sekundy.

1. Pod tento kód přidejte následující pro vytvoření zprávy, která se má říct při spuštění časovače:

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

1. Pod tento kód přidejte podobný kód pro vytvoření zprávy, která se má říct, když časovač vyprší:

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

1. Poté řekněte zprávu o spuštění časovače:

    ```cpp
    say(begin_message);
    ```

1. Na konci této funkce spusťte časovač:

    ```cpp
    timer.in(total_seconds * 1000, timerExpired, (void *)(end_message.c_str()));
    ```

    Tento kód spustí časovač. Časovač je nastaven pomocí milisekund, takže celkový počet sekund je vynásoben 1 000 pro převod na milisekundy. Funkce `timerExpired` je předána jako zpětně volaná funkce a `end_message` je předána jako argument pro zpětné volání. Toto zpětné volání přijímá pouze argumenty typu `void *`, takže řetězec je odpovídajícím způsobem převeden.

1. Nakonec je třeba, aby časovač "tiknul", což se provádí ve funkci `loop`. Přidejte následující kód na konec funkce `loop`:

    ```cpp
    timer.tick();
    ```

1. Sestavte tento kód, nahrajte jej do svého Wio Terminalu a otestujte jej prostřednictvím sériového monitoru. Jakmile uvidíte `Ready` v sériovém monitoru, stiskněte tlačítko C (to vlevo, nejblíže k vypínači) a mluvte. 4 sekundy zvuku budou zachyceny, převedeny na text, poté odeslány do vaší funkce a časovač bude nastaven. Ujistěte se, že vaše funkce běží lokálně.

    Uvidíte, kdy časovač začne a kdy skončí.

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

> 💁 Tento kód najdete ve složce [code-timer/wio-terminal](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/wio-terminal).

😀 Váš program časovače byl úspěšný!

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). I když se snažíme o přesnost, mějte na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace se doporučuje profesionální lidský překlad. Nenese odpovědnost za žádné nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.