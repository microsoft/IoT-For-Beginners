<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "012b69d57d898d670adf61304f42a137",
  "translation_date": "2025-08-28T12:46:59+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-set-timer.md",
  "language_code": "hr"
}
-->
# Postavite mjerač vremena - Wio Terminal

U ovom dijelu lekcije pozvat ćete svoj serverless kod kako biste razumjeli govor i postavili mjerač vremena na svom Wio Terminalu na temelju rezultata.

## Postavite mjerač vremena

Tekst koji se vraća iz poziva za pretvaranje govora u tekst treba poslati vašem serverless kodu kako bi ga obradio LUIS, koji će vratiti broj sekundi za mjerač vremena. Ovaj broj sekundi može se koristiti za postavljanje mjerača vremena.

Mikrokontroleri nemaju ugrađenu podršku za višestruke niti u Arduino okruženju, pa ne postoje standardne klase za mjerače vremena kao što ih možete pronaći u Pythonu ili drugim jezicima višeg nivoa. Umjesto toga, možete koristiti biblioteke za mjerače vremena koje rade mjerenjem proteklog vremena u funkciji `loop` i pozivanjem funkcija kada vrijeme istekne.

### Zadatak - pošaljite tekst serverless funkciji

1. Otvorite projekt `smart-timer` u VS Code-u ako već nije otvoren.

1. Otvorite datoteku zaglavlja `config.h` i dodajte URL za svoju funkcijsku aplikaciju:

    ```cpp
    const char *TEXT_TO_TIMER_FUNCTION_URL = "<URL>";
    ```

    Zamijenite `<URL>` s URL-om za vašu funkcijsku aplikaciju koji ste dobili u posljednjem koraku prethodne lekcije, ukazujući na IP adresu vašeg lokalnog računala na kojem se pokreće funkcijska aplikacija.

1. Kreirajte novu datoteku u mapi `src` pod nazivom `language_understanding.h`. Ova datoteka će se koristiti za definiranje klase koja će slati prepoznati govor vašoj funkcijskoj aplikaciji kako bi se pretvorio u sekunde pomoću LUIS-a.

1. Dodajte sljedeće na vrh ove datoteke:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    ```

    Ovo uključuje potrebne datoteke zaglavlja.

1. Definirajte klasu pod nazivom `LanguageUnderstanding` i deklarirajte instancu ove klase:

    ```cpp
    class LanguageUnderstanding
    {
    public:
    private:
    };

    LanguageUnderstanding languageUnderstanding;
    ```

1. Za pozivanje funkcijske aplikacije trebate deklarirati WiFi klijent. Dodajte sljedeće u privatni dio klase:

    ```cpp
    WiFiClient _client;
    ```

1. U javnom dijelu klase deklarirajte metodu pod nazivom `GetTimerDuration` za pozivanje funkcijske aplikacije:

    ```cpp
    int GetTimerDuration(String text)
    {
    }
    ```

1. U metodi `GetTimerDuration` dodajte sljedeći kod za izradu JSON-a koji će se poslati funkcijskoj aplikaciji:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    Ovo pretvara tekst proslijeđen metodi `GetTimerDuration` u sljedeći JSON:

    ```json
    {
        "text" : "<text>"
    }
    ```

    gdje je `<text>` tekst proslijeđen funkciji.

1. Ispod ovoga dodajte sljedeći kod za pozivanje funkcijske aplikacije:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_TIMER_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    Ovo šalje POST zahtjev funkcijskoj aplikaciji, prosljeđujući JSON tijelo i dobivajući odgovor.

1. Dodajte sljedeći kod ispod ovoga:

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

    Ovaj kod provjerava kod odgovora. Ako je 200 (uspjeh), tada se broj sekundi za mjerač vremena dohvaća iz tijela odgovora. Inače, greška se šalje na serijski monitor, a broj sekundi postavlja se na 0.

1. Dodajte sljedeći kod na kraj ove metode kako biste zatvorili HTTP vezu i vratili broj sekundi:

    ```cpp
    httpClient.end();

    return seconds;
    ```

1. U datoteci `main.cpp` uključite ovo novo zaglavlje:

    ```cpp
    #include "speech_to_text.h"
    ```

1. Na kraju funkcije `processAudio` pozovite metodu `GetTimerDuration` kako biste dobili trajanje mjerača vremena:

    ```cpp
    int total_seconds = languageUnderstanding.GetTimerDuration(text);
    ```

    Ovo pretvara tekst iz poziva klasi `SpeechToText` u broj sekundi za mjerač vremena.

### Zadatak - postavite mjerač vremena

Broj sekundi može se koristiti za postavljanje mjerača vremena.

1. Dodajte sljedeću ovisnost biblioteke u datoteku `platformio.ini` kako biste dodali biblioteku za postavljanje mjerača vremena:

    ```ini
    contrem/arduino-timer @ 2.3.0
    ```

1. Dodajte direktivu za uključivanje ove biblioteke u datoteku `main.cpp`:

    ```cpp
    #include <arduino-timer.h>
    ```

1. Iznad funkcije `processAudio` dodajte sljedeći kod:

    ```cpp
    auto timer = timer_create_default();
    ```

    Ovaj kod deklarira mjerač vremena pod nazivom `timer`.

1. Ispod ovoga dodajte sljedeći kod:

    ```cpp
    void say(String text)
    {
        Serial.print("Saying ");
        Serial.println(text);
    }
    ```

    Ova funkcija `say` će na kraju pretvarati tekst u govor, ali za sada će samo ispisivati proslijeđeni tekst na serijski monitor.

1. Ispod funkcije `say` dodajte sljedeći kod:

    ```cpp
    bool timerExpired(void *announcement)
    {
        say((char *)announcement);
        return false;
    }
    ```

    Ovo je funkcija povratnog poziva koja će se pozvati kada mjerač vremena istekne. Prosljeđuje se poruka koja će se izgovoriti kada mjerač vremena istekne. Mjerači vremena mogu se ponavljati, a to se kontrolira povratnom vrijednošću ove funkcije povratnog poziva - ovdje vraća `false`, što znači da se mjerač vremena neće ponovno pokrenuti.

1. Dodajte sljedeći kod na kraj funkcije `processAudio`:

    ```cpp
    if (total_seconds == 0)
    {
        return;
    }

    int minutes = total_seconds / 60;
    int seconds = total_seconds % 60;
    ```

    Ovaj kod provjerava ukupan broj sekundi, i ako je 0, vraća se iz funkcijskog poziva kako se ne bi postavili mjerači vremena. Zatim pretvara ukupan broj sekundi u minute i sekunde.

1. Ispod ovog koda dodajte sljedeće kako biste stvorili poruku koja će se izgovoriti kada mjerač vremena započne:

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

1. Ispod ovoga dodajte sličan kod za stvaranje poruke koja će se izgovoriti kada mjerač vremena istekne:

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

1. Nakon ovoga, izgovorite poruku o pokretanju mjerača vremena:

    ```cpp
    say(begin_message);
    ```

1. Na kraju ove funkcije pokrenite mjerač vremena:

    ```cpp
    timer.in(total_seconds * 1000, timerExpired, (void *)(end_message.c_str()));
    ```

    Ovo pokreće mjerač vremena. Mjerač vremena postavlja se u milisekundama, pa se ukupan broj sekundi množi s 1.000 kako bi se pretvorio u milisekunde. Funkcija `timerExpired` prosljeđuje se kao povratni poziv, a `end_message` se prosljeđuje kao argument za povratni poziv. Ova funkcija povratnog poziva prihvaća samo argumente tipa `void *`, pa se string odgovarajuće pretvara.

1. Na kraju, mjerač vremena treba *otkucavati*, a to se radi u funkciji `loop`. Dodajte sljedeći kod na kraj funkcije `loop`:

    ```cpp
    timer.tick();
    ```

1. Sastavite ovaj kod, prenesite ga na svoj Wio Terminal i testirajte ga putem serijskog monitora. Kada vidite `Ready` na serijskom monitoru, pritisnite tipku C (onu na lijevoj strani, najbližu prekidaču za napajanje) i govorite. Snimit će se 4 sekunde zvuka, pretvoriti u tekst, poslati vašoj funkcijskoj aplikaciji i postaviti mjerač vremena. Provjerite radi li vaša funkcijska aplikacija lokalno.

    Vidjet ćete kada mjerač vremena započne i kada završi.

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

> 💁 Ovaj kod možete pronaći u mapi [code-timer/wio-terminal](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/wio-terminal).

😀 Vaš program za mjerač vremena bio je uspješan!

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati mjerodavnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane čovjeka. Ne preuzimamo odgovornost za nesporazume ili pogrešna tumačenja koja mogu proizaći iz korištenja ovog prijevoda.