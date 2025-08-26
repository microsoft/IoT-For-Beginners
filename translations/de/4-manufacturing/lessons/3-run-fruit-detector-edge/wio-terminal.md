<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "48ac21ec80329c930db7b84bd6b592ec",
  "translation_date": "2025-08-25T21:09:05+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/wio-terminal.md",
  "language_code": "de"
}
-->
# Klassifizieren eines Bildes mit einem IoT-Edge-basierten Bildklassifikator - Wio Terminal

In diesem Teil der Lektion verwenden Sie den Bildklassifikator, der auf dem IoT-Edge-Gerät läuft.

## Verwenden des IoT-Edge-Klassifikators

Das IoT-Gerät kann so umgeleitet werden, dass es den IoT-Edge-Bildklassifikator verwendet. Die URL für den Bildklassifikator lautet `http://<IP-Adresse oder Name>/image`, wobei `<IP-Adresse oder Name>` durch die IP-Adresse oder den Hostnamen des Computers ersetzt wird, auf dem IoT Edge läuft.

### Aufgabe - Verwenden des IoT-Edge-Klassifikators

1. Öffnen Sie das Projekt der App `fruit-quality-detector`, falls es noch nicht geöffnet ist.

1. Der Bildklassifikator läuft als REST-API über HTTP, nicht HTTPS, daher muss der Aufruf einen WiFi-Client verwenden, der nur mit HTTP-Aufrufen funktioniert. Das bedeutet, dass das Zertifikat nicht benötigt wird. Löschen Sie das `CERTIFICATE` aus der Datei `config.h`.

1. Die Vorhersage-URL in der Datei `config.h` muss auf die neue URL aktualisiert werden. Sie können auch den `PREDICTION_KEY` löschen, da dieser nicht benötigt wird.

    ```cpp
    const char *PREDICTION_URL = "<URL>";
    ```

    Ersetzen Sie `<URL>` durch die URL Ihres Klassifikators.

1. Ändern Sie in `main.cpp` die Include-Direktive für den WiFi Client Secure, um die Standard-HTTP-Version zu importieren:

    ```cpp
    #include <WiFiClient.h>
    ```

1. Ändern Sie die Deklaration von `WiFiClient`, um die HTTP-Version zu verwenden:

    ```cpp
    WiFiClient client;
    ```

1. Wählen Sie die Zeile aus, die das Zertifikat auf dem WiFi-Client setzt. Entfernen Sie die Zeile `client.setCACert(CERTIFICATE);` aus der Funktion `connectWiFi`.

1. Entfernen Sie in der Funktion `classifyImage` die Zeile `httpClient.addHeader("Prediction-Key", PREDICTION_KEY);`, die den Vorhersageschlüssel im Header setzt.

1. Laden Sie Ihren Code hoch und führen Sie ihn aus. Richten Sie die Kamera auf ein Stück Obst und drücken Sie die C-Taste. Sie sehen die Ausgabe im seriellen Monitor:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 Sie finden diesen Code im Ordner [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/wio-terminal).

😀 Ihr Programm zur Klassifizierung der Obstqualität war ein Erfolg!

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.