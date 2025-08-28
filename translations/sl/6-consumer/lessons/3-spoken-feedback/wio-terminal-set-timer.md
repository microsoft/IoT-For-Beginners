<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "012b69d57d898d670adf61304f42a137",
  "translation_date": "2025-08-28T12:47:30+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-set-timer.md",
  "language_code": "sl"
}
-->
# Nastavitev časovnika - Wio Terminal

V tem delu lekcije boste poklicali svojo strežniško kodo, da prepoznate govor, in na podlagi rezultatov nastavili časovnik na svojem Wio Terminalu.

## Nastavitev časovnika

Besedilo, ki ga prejmete iz klica za pretvorbo govora v besedilo, je treba poslati vaši strežniški kodi, da ga obdela LUIS in vrne število sekund za časovnik. To število sekund lahko uporabite za nastavitev časovnika.

Mikrokrmilniki v Arduino okolju nimajo naravne podpore za večnitnost, zato ni standardnih razredov za časovnike, kot jih lahko najdete pri programiranju v Pythonu ali drugih višjenivojskih jezikih. Namesto tega lahko uporabite knjižnice za časovnike, ki delujejo tako, da merijo pretečen čas v funkciji `loop` in kličejo funkcije, ko čas poteče.

### Naloga - pošljite besedilo strežniški funkciji

1. Odprite projekt `smart-timer` v VS Code, če še ni odprt.

1. Odprite glavno datoteko `config.h` in dodajte URL za svojo funkcijsko aplikacijo:

    ```cpp
    const char *TEXT_TO_TIMER_FUNCTION_URL = "<URL>";
    ```

    Zamenjajte `<URL>` z URL-jem za svojo funkcijsko aplikacijo, ki ste ga pridobili v zadnjem koraku prejšnje lekcije, in kaže na IP-naslov vašega lokalnega računalnika, kjer se izvaja funkcijska aplikacija.

1. Ustvarite novo datoteko v mapi `src` z imenom `language_understanding.h`. Ta datoteka bo uporabljena za definiranje razreda, ki bo pošiljal prepoznan govor vaši funkcijski aplikaciji za pretvorbo v sekunde z uporabo LUIS.

1. Na vrh te datoteke dodajte naslednje:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    ```

    To vključuje nekaj potrebnih glavičnih datotek.

1. Definirajte razred z imenom `LanguageUnderstanding` in deklarirajte primerek tega razreda:

    ```cpp
    class LanguageUnderstanding
    {
    public:
    private:
    };

    LanguageUnderstanding languageUnderstanding;
    ```

1. Za klic funkcijske aplikacije morate deklarirati WiFi odjemalca. Dodajte naslednje v zasebni del razreda:

    ```cpp
    WiFiClient _client;
    ```

1. V javnem delu razreda deklarirajte metodo z imenom `GetTimerDuration` za klic funkcijske aplikacije:

    ```cpp
    int GetTimerDuration(String text)
    {
    }
    ```

1. V metodi `GetTimerDuration` dodajte naslednjo kodo za sestavo JSON-a, ki bo poslan funkcijski aplikaciji:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    To pretvori besedilo, posredovano metodi `GetTimerDuration`, v naslednji JSON:

    ```json
    {
        "text" : "<text>"
    }
    ```

    kjer je `<text>` besedilo, posredovano funkciji.

1. Pod tem dodajte naslednjo kodo za klic funkcijske aplikacije:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_TIMER_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    To naredi POST zahtevo funkcijski aplikaciji, posreduje JSON telo in pridobi odzivno kodo.

1. Dodajte naslednjo kodo pod to:

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

    Ta koda preveri odzivno kodo. Če je 200 (uspeh), se število sekund za časovnik pridobi iz odzivnega telesa. V nasprotnem primeru se napaka pošlje na serijski monitor in število sekund se nastavi na 0.

1. Na konec te metode dodajte naslednjo kodo za zaprtje HTTP povezave in vrnitev števila sekund:

    ```cpp
    httpClient.end();

    return seconds;
    ```

1. V datoteki `main.cpp` vključite to novo glavično datoteko:

    ```cpp
    #include "speech_to_text.h"
    ```

1. Na koncu funkcije `processAudio` pokličite metodo `GetTimerDuration`, da pridobite trajanje časovnika:

    ```cpp
    int total_seconds = languageUnderstanding.GetTimerDuration(text);
    ```

    To pretvori besedilo iz klica razreda `SpeechToText` v število sekund za časovnik.

### Naloga - nastavitev časovnika

Število sekund lahko uporabite za nastavitev časovnika.

1. Dodajte naslednjo odvisnost knjižnice v datoteko `platformio.ini`, da dodate knjižnico za nastavitev časovnika:

    ```ini
    contrem/arduino-timer @ 2.3.0
    ```

1. Dodajte direktivo za vključitev te knjižnice v datoteko `main.cpp`:

    ```cpp
    #include <arduino-timer.h>
    ```

1. Nad funkcijo `processAudio` dodajte naslednjo kodo:

    ```cpp
    auto timer = timer_create_default();
    ```

    Ta koda deklarira časovnik z imenom `timer`.

1. Pod to dodajte naslednjo kodo:

    ```cpp
    void say(String text)
    {
        Serial.print("Saying ");
        Serial.println(text);
    }
    ```

    Funkcija `say` bo na koncu pretvorila besedilo v govor, trenutno pa bo samo zapisala posredovano besedilo na serijski monitor.

1. Pod funkcijo `say` dodajte naslednjo kodo:

    ```cpp
    bool timerExpired(void *announcement)
    {
        say((char *)announcement);
        return false;
    }
    ```

    To je povratna funkcija, ki bo poklicana, ko časovnik poteče. Posreduje se sporočilo, ki ga je treba izgovoriti, ko časovnik poteče. Časovniki se lahko ponavljajo, kar je nadzorovano z vrnjeno vrednostjo te povratne funkcije - ta vrne `false`, kar pomeni, da se časovnik ne bo ponovno zagnal.

1. Na konec funkcije `processAudio` dodajte naslednjo kodo:

    ```cpp
    if (total_seconds == 0)
    {
        return;
    }

    int minutes = total_seconds / 60;
    int seconds = total_seconds % 60;
    ```

    Ta koda preveri skupno število sekund in, če je 0, vrne iz klica funkcije, tako da časovniki niso nastavljeni. Nato pretvori skupno število sekund v minute in sekunde.

1. Pod to kodo dodajte naslednje za ustvarjanje sporočila, ki ga je treba izgovoriti, ko se časovnik zažene:

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

1. Pod to dodajte podobno kodo za ustvarjanje sporočila, ki ga je treba izgovoriti, ko časovnik poteče:

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

1. Po tem izgovorite sporočilo o začetku časovnika:

    ```cpp
    say(begin_message);
    ```

1. Na koncu te funkcije zaženite časovnik:

    ```cpp
    timer.in(total_seconds * 1000, timerExpired, (void *)(end_message.c_str()));
    ```

    To sproži časovnik. Časovnik je nastavljen z uporabo milisekund, zato se skupno število sekund pomnoži z 1.000 za pretvorbo v milisekunde. Funkcija `timerExpired` je posredovana kot povratni klic, argument `end_message` pa je posredovan za prenos povratnemu klicu. Ta povratni klic sprejema samo argumente tipa `void *`, zato je niz ustrezno pretvorjen.

1. Na koncu funkcije `loop` dodajte naslednjo kodo:

    ```cpp
    timer.tick();
    ```

1. Sestavite to kodo, naložite jo na svoj Wio Terminal in jo preizkusite prek serijskega monitorja. Ko vidite `Ready` na serijskem monitorju, pritisnite gumb C (tisti na levi strani, najbližje stikalu za vklop) in govorite. 4 sekunde zvoka bodo zajete, pretvorjene v besedilo, nato poslane vaši funkcijski aplikaciji, in časovnik bo nastavljen. Prepričajte se, da se vaša funkcijska aplikacija izvaja lokalno.

    Videli boste, kdaj se časovnik začne in kdaj se konča.

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

> 💁 To kodo lahko najdete v mapi [code-timer/wio-terminal](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/wio-terminal).

😀 Vaš program za časovnik je bil uspešen!

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve AI za prevajanje [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem izvirnem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna nesporazumevanja ali napačne razlage, ki bi nastale zaradi uporabe tega prevoda.