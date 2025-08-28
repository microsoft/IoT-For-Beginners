<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "012b69d57d898d670adf61304f42a137",
  "translation_date": "2025-08-28T09:04:30+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-set-timer.md",
  "language_code": "ro"
}
-->
# Setează un cronometru - Wio Terminal

În această parte a lecției, vei apela codul tău serverless pentru a înțelege vorbirea și vei seta un cronometru pe Wio Terminal pe baza rezultatelor.

## Setează un cronometru

Textul care este returnat din apelul de conversie vorbire-la-text trebuie trimis către codul tău serverless pentru a fi procesat de LUIS, obținând astfel numărul de secunde pentru cronometru. Acest număr de secunde poate fi folosit pentru a seta un cronometru.

Microcontrolerele nu au suport nativ pentru fire multiple în Arduino, așa că nu există clase standard pentru cronometre, cum ai putea găsi atunci când programezi în Python sau alte limbaje de nivel înalt. În schimb, poți folosi biblioteci pentru cronometre care funcționează prin măsurarea timpului scurs în funcția `loop` și apelarea funcțiilor atunci când timpul expiră.

### Sarcină - trimite textul către funcția serverless

1. Deschide proiectul `smart-timer` în VS Code dacă nu este deja deschis.

1. Deschide fișierul header `config.h` și adaugă URL-ul pentru aplicația ta de funcții:

    ```cpp
    const char *TEXT_TO_TIMER_FUNCTION_URL = "<URL>";
    ```

    Înlocuiește `<URL>` cu URL-ul aplicației tale de funcții pe care l-ai obținut în ultimul pas al lecției anterioare, indicând adresa IP a mașinii tale locale care rulează aplicația de funcții.

1. Creează un fișier nou în folderul `src` numit `language_understanding.h`. Acesta va fi folosit pentru a defini o clasă care trimite vorbirea recunoscută către aplicația ta de funcții pentru a fi convertită în secunde folosind LUIS.

1. Adaugă următoarele la începutul acestui fișier:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    ```

    Acest lucru include câteva fișiere header necesare.

1. Definește o clasă numită `LanguageUnderstanding` și declară o instanță a acestei clase:

    ```cpp
    class LanguageUnderstanding
    {
    public:
    private:
    };

    LanguageUnderstanding languageUnderstanding;
    ```

1. Pentru a apela aplicația de funcții, trebuie să declari un client WiFi. Adaugă următoarele în secțiunea `private` a clasei:

    ```cpp
    WiFiClient _client;
    ```

1. În secțiunea `public`, declară o metodă numită `GetTimerDuration` pentru a apela aplicația de funcții:

    ```cpp
    int GetTimerDuration(String text)
    {
    }
    ```

1. În metoda `GetTimerDuration`, adaugă următorul cod pentru a construi JSON-ul care va fi trimis către aplicația de funcții:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    Acest lucru convertește textul transmis metodei `GetTimerDuration` în următorul JSON:

    ```json
    {
        "text" : "<text>"
    }
    ```

    unde `<text>` este textul transmis funcției.

1. Sub acest cod, adaugă următorul cod pentru a face apelul către aplicația de funcții:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_TIMER_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    Acest lucru face o cerere POST către aplicația de funcții, transmițând corpul JSON și obținând codul de răspuns.

1. Adaugă următorul cod sub acesta:

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

    Acest cod verifică codul de răspuns. Dacă este 200 (succes), atunci numărul de secunde pentru cronometru este preluat din corpul răspunsului. În caz contrar, o eroare este trimisă către monitorul serial, iar numărul de secunde este setat la 0.

1. Adaugă următorul cod la sfârșitul acestei metode pentru a închide conexiunea HTTP și a returna numărul de secunde:

    ```cpp
    httpClient.end();

    return seconds;
    ```

1. În fișierul `main.cpp`, include acest nou header:

    ```cpp
    #include "speech_to_text.h"
    ```

1. La sfârșitul funcției `processAudio`, apelează metoda `GetTimerDuration` pentru a obține durata cronometrului:

    ```cpp
    int total_seconds = languageUnderstanding.GetTimerDuration(text);
    ```

    Acest lucru convertește textul din apelul către clasa `SpeechToText` în numărul de secunde pentru cronometru.

### Sarcină - setează un cronometru

Numărul de secunde poate fi folosit pentru a seta un cronometru.

1. Adaugă următoarea dependență de bibliotecă în fișierul `platformio.ini` pentru a adăuga o bibliotecă pentru setarea unui cronometru:

    ```ini
    contrem/arduino-timer @ 2.3.0
    ```

1. Adaugă o directivă include pentru această bibliotecă în fișierul `main.cpp`:

    ```cpp
    #include <arduino-timer.h>
    ```

1. Deasupra funcției `processAudio`, adaugă următorul cod:

    ```cpp
    auto timer = timer_create_default();
    ```

    Acest cod declară un cronometru numit `timer`.

1. Sub acesta, adaugă următorul cod:

    ```cpp
    void say(String text)
    {
        Serial.print("Saying ");
        Serial.println(text);
    }
    ```

    Această funcție `say` va converti în cele din urmă textul în vorbire, dar pentru moment va scrie doar textul transmis pe monitorul serial.

1. Sub funcția `say`, adaugă următorul cod:

    ```cpp
    bool timerExpired(void *announcement)
    {
        say((char *)announcement);
        return false;
    }
    ```

    Aceasta este o funcție de callback care va fi apelată atunci când un cronometru expiră. Este transmis un mesaj care va fi afișat când cronometru expiră. Cronometrele pot fi repetate, iar acest lucru poate fi controlat prin valoarea returnată a acestui callback - acesta returnează `false`, pentru a indica faptul că cronometrul nu trebuie să ruleze din nou.

1. Adaugă următorul cod la sfârșitul funcției `processAudio`:

    ```cpp
    if (total_seconds == 0)
    {
        return;
    }

    int minutes = total_seconds / 60;
    int seconds = total_seconds % 60;
    ```

    Acest cod verifică numărul total de secunde, iar dacă este 0, se întoarce din apelul funcției, astfel încât să nu fie setate cronometre. Apoi convertește numărul total de secunde în minute și secunde.

1. Sub acest cod, adaugă următorul cod pentru a crea un mesaj care să fie afișat când cronometru este pornit:

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

1. Sub acesta, adaugă un cod similar pentru a crea un mesaj care să fie afișat când cronometru expiră:

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

1. După aceasta, afișează mesajul de pornire a cronometrului:

    ```cpp
    say(begin_message);
    ```

1. La sfârșitul acestei funcții, pornește cronometrul:

    ```cpp
    timer.in(total_seconds * 1000, timerExpired, (void *)(end_message.c_str()));
    ```

    Acest lucru declanșează cronometrul. Cronometrul este setat folosind milisecunde, așa că numărul total de secunde este înmulțit cu 1.000 pentru a fi convertit în milisecunde. Funcția `timerExpired` este transmisă ca callback, iar `end_message` este transmis ca argument pentru callback. Acest callback acceptă doar argumente de tip `void *`, așa că șirul este convertit corespunzător.

1. În cele din urmă, cronometrul trebuie să *ticăie*, iar acest lucru se face în funcția `loop`. Adaugă următorul cod la sfârșitul funcției `loop`:

    ```cpp
    timer.tick();
    ```

1. Construiește acest cod, încarcă-l pe Wio Terminal și testează-l prin monitorul serial. Odată ce vezi `Ready` în monitorul serial, apasă butonul C (cel din partea stângă, cel mai aproape de comutatorul de alimentare) și vorbește. Vor fi capturate 4 secunde de audio, convertite în text, apoi trimise către aplicația ta de funcții, iar un cronometru va fi setat. Asigură-te că aplicația ta de funcții rulează local.

    Vei vedea când cronometru începe și când se termină.

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

> 💁 Poți găsi acest cod în folderul [code-timer/wio-terminal](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/wio-terminal).

😀 Programul tău pentru cronometru a fost un succes!

---

**Declinare de responsabilitate**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să rețineți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa natală ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist. Nu ne asumăm responsabilitatea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.