<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "012b69d57d898d670adf61304f42a137",
  "translation_date": "2025-08-25T22:36:38+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-set-timer.md",
  "language_code": "de"
}
-->
# Einen Timer einstellen - Wio Terminal

In diesem Teil der Lektion rufst du deinen serverlosen Code auf, um die Sprache zu verstehen, und stellst basierend auf den Ergebnissen einen Timer auf deinem Wio Terminal ein.

## Einen Timer einstellen

Der Text, der aus dem Sprach-zu-Text-Aufruf zurückkommt, muss an deinen serverlosen Code gesendet werden, damit er von LUIS verarbeitet wird. Dabei wird die Anzahl der Sekunden für den Timer zurückgegeben. Diese Sekundenanzahl kann verwendet werden, um einen Timer einzustellen.

Mikrocontroller unterstützen in Arduino standardmäßig keine Multithreading-Funktionen, daher gibt es keine Standard-Timer-Klassen wie in Python oder anderen höherwertigen Programmiersprachen. Stattdessen kannst du Timer-Bibliotheken verwenden, die die verstrichene Zeit in der `loop`-Funktion messen und Funktionen aufrufen, wenn die Zeit abgelaufen ist.

### Aufgabe - Den Text an die serverlose Funktion senden

1. Öffne das Projekt `smart-timer` in VS Code, falls es noch nicht geöffnet ist.

1. Öffne die Header-Datei `config.h` und füge die URL für deine Function App hinzu:

    ```cpp
    const char *TEXT_TO_TIMER_FUNCTION_URL = "<URL>";
    ```

    Ersetze `<URL>` durch die URL deiner Function App, die du im letzten Schritt der vorherigen Lektion erhalten hast. Diese sollte auf die IP-Adresse deines lokalen Rechners zeigen, auf dem die Function App läuft.

1. Erstelle eine neue Datei im Ordner `src` mit dem Namen `language_understanding.h`. Diese Datei wird verwendet, um eine Klasse zu definieren, die die erkannte Sprache an deine Function App sendet, um sie mit LUIS in Sekunden umzuwandeln.

1. Füge am Anfang dieser Datei Folgendes hinzu:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    ```

    Dies bindet einige benötigte Header-Dateien ein.

1. Definiere eine Klasse namens `LanguageUnderstanding` und deklariere eine Instanz dieser Klasse:

    ```cpp
    class LanguageUnderstanding
    {
    public:
    private:
    };

    LanguageUnderstanding languageUnderstanding;
    ```

1. Um deine Function App aufzurufen, musst du einen WiFi-Client deklarieren. Füge Folgendes in den `private`-Bereich der Klasse ein:

    ```cpp
    WiFiClient _client;
    ```

1. Deklariere im `public`-Bereich eine Methode namens `GetTimerDuration`, um die Function App aufzurufen:

    ```cpp
    int GetTimerDuration(String text)
    {
    }
    ```

1. Füge in der Methode `GetTimerDuration` den folgenden Code hinzu, um das JSON zu erstellen, das an die Function App gesendet wird:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    Dies wandelt den an die Methode `GetTimerDuration` übergebenen Text in folgendes JSON um:

    ```json
    {
        "text" : "<text>"
    }
    ```

    wobei `<text>` der an die Funktion übergebene Text ist.

1. Füge darunter den folgenden Code hinzu, um den Aufruf der Function App durchzuführen:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_TIMER_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    Dies führt eine POST-Anfrage an die Function App aus, übergibt den JSON-Body und erhält den Antwortcode.

1. Füge den folgenden Code darunter hinzu:

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

    Dieser Code überprüft den Antwortcode. Wenn er 200 (Erfolg) ist, wird die Anzahl der Sekunden für den Timer aus dem Antwort-Body abgerufen. Andernfalls wird ein Fehler im seriellen Monitor ausgegeben und die Sekundenanzahl auf 0 gesetzt.

1. Füge am Ende dieser Methode den folgenden Code hinzu, um die HTTP-Verbindung zu schließen und die Sekundenanzahl zurückzugeben:

    ```cpp
    httpClient.end();

    return seconds;
    ```

1. Binde in der Datei `main.cpp` diese neue Header-Datei ein:

    ```cpp
    #include "speech_to_text.h"
    ```

1. Rufe am Ende der Funktion `processAudio` die Methode `GetTimerDuration` auf, um die Timer-Dauer zu erhalten:

    ```cpp
    int total_seconds = languageUnderstanding.GetTimerDuration(text);
    ```

    Dies wandelt den Text aus dem Aufruf der Klasse `SpeechToText` in die Anzahl der Sekunden für den Timer um.

### Aufgabe - Einen Timer einstellen

Die Anzahl der Sekunden kann verwendet werden, um einen Timer einzustellen.

1. Füge die folgende Bibliotheksabhängigkeit zur Datei `platformio.ini` hinzu, um eine Bibliothek für den Timer hinzuzufügen:

    ```ini
    contrem/arduino-timer @ 2.3.0
    ```

1. Füge eine Include-Direktive für diese Bibliothek in die Datei `main.cpp` ein:

    ```cpp
    #include <arduino-timer.h>
    ```

1. Füge oberhalb der Funktion `processAudio` den folgenden Code hinzu:

    ```cpp
    auto timer = timer_create_default();
    ```

    Dieser Code deklariert einen Timer namens `timer`.

1. Füge darunter den folgenden Code hinzu:

    ```cpp
    void say(String text)
    {
        Serial.print("Saying ");
        Serial.println(text);
    }
    ```

    Diese Funktion `say` wird später Text in Sprache umwandeln, schreibt aber vorerst nur den übergebenen Text in den seriellen Monitor.

1. Füge unterhalb der Funktion `say` den folgenden Code hinzu:

    ```cpp
    bool timerExpired(void *announcement)
    {
        say((char *)announcement);
        return false;
    }
    ```

    Dies ist eine Callback-Funktion, die aufgerufen wird, wenn ein Timer abläuft. Sie erhält eine Nachricht, die beim Ablauf des Timers ausgegeben wird. Timer können wiederholt werden, was durch den Rückgabewert dieser Callback-Funktion gesteuert wird - hier wird `false` zurückgegeben, um den Timer nicht erneut auszuführen.

1. Füge am Ende der Funktion `processAudio` den folgenden Code hinzu:

    ```cpp
    if (total_seconds == 0)
    {
        return;
    }

    int minutes = total_seconds / 60;
    int seconds = total_seconds % 60;
    ```

    Dieser Code überprüft die Gesamtanzahl der Sekunden. Wenn sie 0 beträgt, wird die Funktion beendet, sodass keine Timer gesetzt werden. Anschließend wird die Gesamtanzahl der Sekunden in Minuten und Sekunden umgerechnet.

1. Füge unter diesem Code Folgendes hinzu, um eine Nachricht zu erstellen, die beim Start des Timers ausgegeben wird:

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

1. Füge darunter ähnlichen Code hinzu, um eine Nachricht zu erstellen, die beim Ablauf des Timers ausgegeben wird:

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

1. Gib nach diesem Code die Startnachricht des Timers aus:

    ```cpp
    say(begin_message);
    ```

1. Starte am Ende dieser Funktion den Timer:

    ```cpp
    timer.in(total_seconds * 1000, timerExpired, (void *)(end_message.c_str()));
    ```

    Dies löst den Timer aus. Der Timer wird in Millisekunden eingestellt, daher wird die Gesamtanzahl der Sekunden mit 1.000 multipliziert, um sie in Millisekunden umzuwandeln. Die Funktion `timerExpired` wird als Callback übergeben, und die `end_message` wird als Argument an den Callback übergeben. Dieser Callback akzeptiert nur `void *`-Argumente, daher wird der String entsprechend konvertiert.

1. Schließlich muss der Timer *ticken*, was in der Funktion `loop` geschieht. Füge am Ende der Funktion `loop` den folgenden Code hinzu:

    ```cpp
    timer.tick();
    ```

1. Baue diesen Code, lade ihn auf dein Wio Terminal hoch und teste ihn über den seriellen Monitor. Sobald du `Ready` im seriellen Monitor siehst, drücke die C-Taste (die linke Taste, die sich am nächsten zum Netzschalter befindet) und sprich. 4 Sekunden Audio werden aufgenommen, in Text umgewandelt, an deine Function App gesendet und ein Timer wird eingestellt. Stelle sicher, dass deine Function App lokal läuft.

    Du wirst sehen, wann der Timer startet und wann er endet.

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

> 💁 Du findest diesen Code im Ordner [code-timer/wio-terminal](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/wio-terminal).

😀 Dein Timer-Programm war ein Erfolg!

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.