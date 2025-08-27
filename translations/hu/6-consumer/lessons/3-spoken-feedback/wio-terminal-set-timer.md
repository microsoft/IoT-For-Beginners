<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "012b69d57d898d670adf61304f42a137",
  "translation_date": "2025-08-27T21:14:10+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-set-timer.md",
  "language_code": "hu"
}
-->
# Állíts be egy időzítőt - Wio Terminal

Ebben a leckében a szerver nélküli kódodat fogod meghívni, hogy felismerje a beszédet, és az eredmények alapján beállítson egy időzítőt a Wio Terminal eszközön.

## Időzítő beállítása

A beszédfelismerésből visszakapott szöveget el kell küldeni a szerver nélküli kódodnak, hogy a LUIS feldolgozza, és visszaadja az időzítőhöz szükséges másodpercek számát. Ez a másodpercek száma felhasználható az időzítő beállításához.

A mikrokontrollerek nem támogatják natívan a több szálat az Arduino környezetben, így nincsenek standard időzítő osztályok, mint például Pythonban vagy más magas szintű nyelvekben. Ehelyett olyan időzítő könyvtárakat használhatsz, amelyek az `loop` függvényben eltelt időt mérik, és funkciókat hívnak meg, amikor az idő lejár.

### Feladat - küldd el a szöveget a szerver nélküli funkciónak

1. Nyisd meg a `smart-timer` projektet a VS Code-ban, ha még nincs megnyitva.

1. Nyisd meg a `config.h` fejlécfájlt, és add hozzá a funkció alkalmazás URL-jét:

    ```cpp
    const char *TEXT_TO_TIMER_FUNCTION_URL = "<URL>";
    ```

    Cseréld ki a `<URL>` helyére azt az URL-t, amelyet az előző lecke utolsó lépésében kaptál, és amely a helyi géped IP-címére mutat, ahol a funkció alkalmazás fut.

1. Hozz létre egy új fájlt a `src` mappában `language_understanding.h` néven. Ez a fájl egy osztályt fog definiálni, amely a felismert beszédet elküldi a funkció alkalmazásnak, hogy másodpercekké alakítsa át a LUIS segítségével.

1. Add hozzá a következőket a fájl tetejéhez:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    ```

    Ez néhány szükséges fejlécfájlt tartalmaz.

1. Definiálj egy `LanguageUnderstanding` nevű osztályt, és deklarálj egy példányt ebből az osztályból:

    ```cpp
    class LanguageUnderstanding
    {
    public:
    private:
    };

    LanguageUnderstanding languageUnderstanding;
    ```

1. A funkció alkalmazás meghívásához deklarálj egy WiFi klienst. Add hozzá a következőt az osztály `private` szekciójához:

    ```cpp
    WiFiClient _client;
    ```

1. Az `public` szekcióban deklarálj egy `GetTimerDuration` nevű metódust, amely meghívja a funkció alkalmazást:

    ```cpp
    int GetTimerDuration(String text)
    {
    }
    ```

1. Az `GetTimerDuration` metódusban add hozzá a következő kódot, amely létrehozza a JSON-t, amit elküldesz a funkció alkalmazásnak:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    Ez a kód a metódusnak átadott szöveget a következő JSON formátumba alakítja:

    ```json
    {
        "text" : "<text>"
    }
    ```

    ahol `<text>` az átadott szöveg.

1. Ez alatt add hozzá a következő kódot, amely meghívja a funkció alkalmazást:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_TIMER_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    Ez egy POST kérést küld a funkció alkalmazásnak, átadva a JSON törzset, és visszakapja a válaszkódot.

1. Add hozzá a következő kódot ez alatt:

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

    Ez a kód ellenőrzi a válaszkódot. Ha az 200 (sikeres), akkor az időzítőhöz szükséges másodpercek száma kinyerésre kerül a válasz törzséből. Ellenkező esetben egy hibaüzenet kerül a soros monitorra, és a másodpercek száma 0-ra áll.

1. Add hozzá a következő kódot a metódus végéhez, amely lezárja a HTTP kapcsolatot, és visszaadja a másodpercek számát:

    ```cpp
    httpClient.end();

    return seconds;
    ```

1. A `main.cpp` fájlban illeszd be az új fejlécet:

    ```cpp
    #include "speech_to_text.h"
    ```

1. A `processAudio` függvény végén hívd meg a `GetTimerDuration` metódust, hogy megkapd az időzítő időtartamát:

    ```cpp
    int total_seconds = languageUnderstanding.GetTimerDuration(text);
    ```

    Ez a kód a `SpeechToText` osztályból származó szöveget másodpercekké alakítja az időzítő számára.

### Feladat - időzítő beállítása

A másodpercek száma felhasználható egy időzítő beállításához.

1. Add hozzá a következő könyvtárfüggőséget a `platformio.ini` fájlhoz, hogy egy időzítő könyvtárat adj hozzá:

    ```ini
    contrem/arduino-timer @ 2.3.0
    ```

1. Add hozzá egy include direktívát ehhez a könyvtárhoz a `main.cpp` fájlban:

    ```cpp
    #include <arduino-timer.h>
    ```

1. A `processAudio` függvény felett add hozzá a következő kódot:

    ```cpp
    auto timer = timer_create_default();
    ```

    Ez a kód egy `timer` nevű időzítőt deklarál.

1. Ez alatt add hozzá a következő kódot:

    ```cpp
    void say(String text)
    {
        Serial.print("Saying ");
        Serial.println(text);
    }
    ```

    Ez a `say` függvény végül szöveget fog beszéddé alakítani, de egyelőre csak a soros monitorra írja ki az átadott szöveget.

1. A `say` függvény alatt add hozzá a következő kódot:

    ```cpp
    bool timerExpired(void *announcement)
    {
        say((char *)announcement);
        return false;
    }
    ```

    Ez egy visszahívási függvény, amely akkor kerül meghívásra, amikor egy időzítő lejár. Egy üzenetet kap, amit lejáratkor ki kell mondani. Az időzítők ismételhetők, és ezt a visszatérési érték szabályozza - itt `false`-t ad vissza, hogy az időzítő ne fusson újra.

1. Add hozzá a következő kódot a `processAudio` függvény végéhez:

    ```cpp
    if (total_seconds == 0)
    {
        return;
    }

    int minutes = total_seconds / 60;
    int seconds = total_seconds % 60;
    ```

    Ez a kód ellenőrzi az összes másodpercet, és ha az 0, visszatér a függvényből, így nem állít be időzítőt. Ezután az összes másodpercet percekké és másodpercekké alakítja.

1. Ez alatt add hozzá a következőt, hogy létrehozz egy üzenetet, amit az időzítő indításakor kell kimondani:

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

1. Ez alatt add hozzá hasonló kódot, hogy létrehozz egy üzenetet, amit az időzítő lejáratakor kell kimondani:

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

1. Ezután mondd ki az időzítő indítási üzenetét:

    ```cpp
    say(begin_message);
    ```

1. A függvény végén indítsd el az időzítőt:

    ```cpp
    timer.in(total_seconds * 1000, timerExpired, (void *)(end_message.c_str()));
    ```

    Ez elindítja az időzítőt. Az időzítőt milliszekundumokban kell beállítani, így az összes másodpercet 1,000-rel szorozzuk, hogy milliszekundumokká alakítsuk. A `timerExpired` függvény kerül átadásra visszahívásként, és az `end_message` kerül átadásra argumentumként a visszahívásnak. Ez a visszahívás csak `void *` típusú argumentumokat fogad, így a szöveg megfelelően kerül átalakításra.

1. Végül az időzítőnek *tickelnie* kell, és ezt a `loop` függvény végén kell megtenni. Add hozzá a következő kódot a `loop` függvény végéhez:

    ```cpp
    timer.tick();
    ```

1. Fordítsd le a kódot, töltsd fel a Wio Terminal eszközre, és teszteld a soros monitoron keresztül. Amint a soros monitorban megjelenik a `Ready`, nyomd meg a C gombot (a bal oldali gombot, amely a legközelebb van a bekapcsoló kapcsolóhoz), és beszélj. 4 másodpercnyi hangot rögzít, szöveggé alakít, majd elküldi a funkció alkalmazásnak, és beállít egy időzítőt. Győződj meg róla, hogy a funkció alkalmazás helyileg fut.

    Látni fogod, mikor indul el az időzítő, és mikor jár le.

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

> 💁 Ezt a kódot megtalálhatod a [code-timer/wio-terminal](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/wio-terminal) mappában.

😀 Az időzítő programod sikeres volt!

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.