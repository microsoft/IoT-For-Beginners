<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "012b69d57d898d670adf61304f42a137",
  "translation_date": "2025-10-11T12:09:44+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-set-timer.md",
  "language_code": "et"
}
-->
# Seadista taimer - Wio Terminal

Selles õppetunni osas kutsud oma serverivaba koodi, et mõista kõnet, ja seadistad tulemuste põhjal taimeri oma Wio Terminalis.

## Taimeri seadistamine

Kõneteksti teisendamise kõnest tagastatud tekst tuleb saata serverivabale koodile, et LUIS seda töötleks ja tagastaks taimeri sekundite arvu. Seda sekundite arvu saab kasutada taimeri seadistamiseks.

Mikrokontrolleritel pole Arduino keskkonnas loomulikku mitme lõime tuge, seega pole standardseid taimeriklasse nagu Pythonis või teistes kõrgema taseme programmeerimiskeeltes. Selle asemel saab kasutada taimeri teeke, mis mõõdavad möödunud aega `loop` funktsioonis ja kutsuvad funktsioone, kui aeg on läbi.

### Ülesanne - teksti saatmine serverivabale funktsioonile

1. Ava `smart-timer` projekt VS Code'is, kui see pole juba avatud.

1. Ava `config.h` päisefail ja lisa oma funktsiooni rakenduse URL:

    ```cpp
    const char *TEXT_TO_TIMER_FUNCTION_URL = "<URL>";
    ```

    Asenda `<URL>` funktsiooni rakenduse URL-iga, mille sa said eelmise õppetunni viimases etapis, viidates sinu kohaliku masina IP-aadressile, kus funktsiooni rakendus töötab.

1. Loo `src` kausta uus fail nimega `language_understanding.h`. Seda kasutatakse klassi määratlemiseks, mis saadab tuvastatud kõne sinu funktsiooni rakendusele, et see teisendataks sekunditeks LUIS-i abil.

1. Lisa faili algusesse järgmine:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    ```

    See sisaldab vajalikke päisefaile.

1. Määra klass nimega `LanguageUnderstanding` ja deklareeri selle klassi eksemplar:

    ```cpp
    class LanguageUnderstanding
    {
    public:
    private:
    };

    LanguageUnderstanding languageUnderstanding;
    ```

1. Funktsiooni rakenduse kutsumiseks pead deklareerima WiFi kliendi. Lisa järgmine klassi `private` sektsiooni:

    ```cpp
    WiFiClient _client;
    ```

1. `public` sektsiooni lisa meetod nimega `GetTimerDuration`, et kutsuda funktsiooni rakendust:

    ```cpp
    int GetTimerDuration(String text)
    {
    }
    ```

1. `GetTimerDuration` meetodis lisa järgmine kood JSON-i koostamiseks, mida funktsiooni rakendusele saata:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    See teisendab `GetTimerDuration` meetodile edastatud teksti järgmisesse JSON-i:

    ```json
    {
        "text" : "<text>"
    }
    ```

    kus `<text>` on meetodile edastatud tekst.

1. Selle alla lisa järgmine kood funktsiooni rakenduse kutsumiseks:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_TIMER_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    See teeb POST-päringu funktsiooni rakendusele, edastades JSON-i keha ja saades vastuse koodi.

1. Lisa sellele alla järgmine kood:

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

    See kood kontrollib vastuse koodi. Kui see on 200 (õnnestumine), siis sekundite arv taimeri jaoks saadakse vastuse kehast. Vastasel juhul saadetakse veateade seeriamonitorile ja sekundite arv määratakse 0-ks.

1. Lisa meetodi lõppu järgmine kood, et sulgeda HTTP-ühendus ja tagastada sekundite arv:

    ```cpp
    httpClient.end();

    return seconds;
    ```

1. `main.cpp` failis lisa selle uue päise kaasamine:

    ```cpp
    #include "speech_to_text.h"
    ```

1. `processAudio` funktsiooni lõpus kutsu `GetTimerDuration` meetodit, et saada taimeri kestus:

    ```cpp
    int total_seconds = languageUnderstanding.GetTimerDuration(text);
    ```

    See teisendab `SpeechToText` klassi kõne kõnest saadud teksti taimeri sekundite arvuks.

### Ülesanne - taimeri seadistamine

Sekundite arvu saab kasutada taimeri seadistamiseks.

1. Lisa `platformio.ini` faili järgmine teegi sõltuvus, et lisada taimeri seadistamise teek:

    ```ini
    contrem/arduino-timer @ 2.3.0
    ```

1. Lisa `main.cpp` faili selle teegi kaasamise direktiiv:

    ```cpp
    #include <arduino-timer.h>
    ```

1. `processAudio` funktsiooni kohal lisa järgmine kood:

    ```cpp
    auto timer = timer_create_default();
    ```

    See kood deklareerib taimeri nimega `timer`.

1. Selle alla lisa järgmine kood:

    ```cpp
    void say(String text)
    {
        Serial.print("Saying ");
        Serial.println(text);
    }
    ```

    See `say` funktsioon teisendab lõpuks teksti kõneks, kuid praegu kirjutab see edastatud teksti lihtsalt seeriamonitorile.

1. `say` funktsiooni alla lisa järgmine kood:

    ```cpp
    bool timerExpired(void *announcement)
    {
        say((char *)announcement);
        return false;
    }
    ```

    See on tagasikutse funktsioon, mida kutsutakse, kui taimer aegub. Sellele edastatakse sõnum, mida öelda, kui taimer aegub. Taimerid võivad korduda, ja seda saab kontrollida tagasikutse tagastusväärtusega - see tagastab `false`, et öelda taimerile, et see ei käivitu uuesti.

1. Lisa `processAudio` funktsiooni lõppu järgmine kood:

    ```cpp
    if (total_seconds == 0)
    {
        return;
    }

    int minutes = total_seconds / 60;
    int seconds = total_seconds % 60;
    ```

    See kood kontrollib sekundite koguarvu ja kui see on 0, väljub funktsiooni kutsest, et taimerit ei seadistataks. Seejärel teisendab see sekundite koguarvu minutiteks ja sekunditeks.

1. Selle koodi alla lisa järgmine, et luua sõnum, mida öelda, kui taimer käivitub:

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

1. Selle alla lisa sarnane kood, et luua sõnum, mida öelda, kui taimer aegub:

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

1. Pärast seda ütle taimeri käivitamise sõnum:

    ```cpp
    say(begin_message);
    ```

1. Funktsiooni lõpus käivita taimer:

    ```cpp
    timer.in(total_seconds * 1000, timerExpired, (void *)(end_message.c_str()));
    ```

    See käivitab taimeri. Taimer seadistatakse millisekundites, seega sekundite koguarv korrutatakse 1,000-ga, et teisendada millisekunditeks. `timerExpired` funktsioon edastatakse tagasikutseks ja `end_message` edastatakse argumendina tagasikutsele. See tagasikutse võtab ainult `void *` argumente, seega string teisendatakse vastavalt.

1. Lõpuks peab taimer *tiksuma*, ja seda tehakse `loop` funktsioonis. Lisa järgmine kood `loop` funktsiooni lõppu:

    ```cpp
    timer.tick();
    ```

1. Koosta see kood, laadi see oma Wio Terminali ja testi seda seeriamonitori kaudu. Kui näed seeriamonitoris `Ready`, vajuta C nuppu (vasakpoolne nupp, mis on kõige lähemal toitelülitile) ja räägi. 4 sekundit heli salvestatakse, teisendatakse tekstiks, saadetakse sinu funktsiooni rakendusele ja taimer seadistatakse. Veendu, et sinu funktsiooni rakendus töötab kohalikult.

    Näed, millal taimer käivitub ja millal see lõppeb.

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

> 💁 Selle koodi leiad [code-timer/wio-terminal](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/wio-terminal) kaustast.

😀 Sinu taimeriprogramm oli edukas!

---

**Lahtiütlus**:  
See dokument on tõlgitud AI tõlketeenuse [Co-op Translator](https://github.com/Azure/co-op-translator) abil. Kuigi püüame tagada täpsust, palume arvestada, et automaatsed tõlked võivad sisaldada vigu või ebatäpsusi. Algne dokument selle algses keeles tuleks pidada autoriteetseks allikaks. Olulise teabe puhul soovitame kasutada professionaalset inimtõlget. Me ei vastuta selle tõlke kasutamisest tulenevate arusaamatuste või valesti tõlgenduste eest.