<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "32a1f23e7834fbe7715da8c4ebb450b9",
  "translation_date": "2025-08-25T21:00:09+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-classify-image.md",
  "language_code": "de"
}
-->
# Klassifizieren eines Bildes - Wio Terminal

In diesem Abschnitt der Lektion senden Sie das von der Kamera aufgenommene Bild an den Custom Vision-Dienst, um es zu klassifizieren.

## Klassifizieren eines Bildes

Der Custom Vision-Dienst verfügt über eine REST-API, die Sie vom Wio Terminal aus aufrufen können, um Bilder zu klassifizieren. Diese REST-API wird über eine HTTPS-Verbindung - eine sichere HTTP-Verbindung - aufgerufen.

Beim Interagieren mit HTTPS-Endpunkten muss der Client-Code das öffentliche Schlüsselzertifikat vom Server anfordern, auf den zugegriffen wird, und dieses verwenden, um den gesendeten Datenverkehr zu verschlüsseln. Ihr Webbrowser erledigt dies automatisch, Mikrocontroller jedoch nicht. Sie müssen dieses Zertifikat manuell anfordern und verwenden, um eine sichere Verbindung zur REST-API herzustellen. Diese Zertifikate ändern sich nicht, sodass sie einmalig in Ihrer Anwendung fest codiert werden können.

Diese Zertifikate enthalten öffentliche Schlüssel und müssen nicht geheim gehalten werden. Sie können sie in Ihrem Quellcode verwenden und öffentlich auf Plattformen wie GitHub teilen.

### Aufgabe - SSL-Client einrichten

1. Öffnen Sie das Projekt der App `fruit-quality-detector`, falls es noch nicht geöffnet ist.

1. Öffnen Sie die Header-Datei `config.h` und fügen Sie Folgendes hinzu:

    ```cpp
    const char *CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "MIIF8zCCBNugAwIBAgIQAueRcfuAIek/4tmDg0xQwDANBgkqhkiG9w0BAQwFADBh\r\n"
        "MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\r\n"
        "d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBH\r\n"
        "MjAeFw0yMDA3MjkxMjMwMDBaFw0yNDA2MjcyMzU5NTlaMFkxCzAJBgNVBAYTAlVT\r\n"
        "MR4wHAYDVQQKExVNaWNyb3NvZnQgQ29ycG9yYXRpb24xKjAoBgNVBAMTIU1pY3Jv\r\n"
        "c29mdCBBenVyZSBUTFMgSXNzdWluZyBDQSAwNjCCAiIwDQYJKoZIhvcNAQEBBQAD\r\n"
        "ggIPADCCAgoCggIBALVGARl56bx3KBUSGuPc4H5uoNFkFH4e7pvTCxRi4j/+z+Xb\r\n"
        "wjEz+5CipDOqjx9/jWjskL5dk7PaQkzItidsAAnDCW1leZBOIi68Lff1bjTeZgMY\r\n"
        "iwdRd3Y39b/lcGpiuP2d23W95YHkMMT8IlWosYIX0f4kYb62rphyfnAjYb/4Od99\r\n"
        "ThnhlAxGtfvSbXcBVIKCYfZgqRvV+5lReUnd1aNjRYVzPOoifgSx2fRyy1+pO1Uz\r\n"
        "aMMNnIOE71bVYW0A1hr19w7kOb0KkJXoALTDDj1ukUEDqQuBfBxReL5mXiu1O7WG\r\n"
        "0vltg0VZ/SZzctBsdBlx1BkmWYBW261KZgBivrql5ELTKKd8qgtHcLQA5fl6JB0Q\r\n"
        "gs5XDaWehN86Gps5JW8ArjGtjcWAIP+X8CQaWfaCnuRm6Bk/03PQWhgdi84qwA0s\r\n"
        "sRfFJwHUPTNSnE8EiGVk2frt0u8PG1pwSQsFuNJfcYIHEv1vOzP7uEOuDydsmCjh\r\n"
        "lxuoK2n5/2aVR3BMTu+p4+gl8alXoBycyLmj3J/PUgqD8SL5fTCUegGsdia/Sa60\r\n"
        "N2oV7vQ17wjMN+LXa2rjj/b4ZlZgXVojDmAjDwIRdDUujQu0RVsJqFLMzSIHpp2C\r\n"
        "Zp7mIoLrySay2YYBu7SiNwL95X6He2kS8eefBBHjzwW/9FxGqry57i71c2cDAgMB\r\n"
        "AAGjggGtMIIBqTAdBgNVHQ4EFgQU1cFnOsKjnfR3UltZEjgp5lVou6UwHwYDVR0j\r\n"
        "BBgwFoAUTiJUIBiV5uNu5g/6+rkS7QYXjzkwDgYDVR0PAQH/BAQDAgGGMB0GA1Ud\r\n"
        "JQQWMBQGCCsGAQUFBwMBBggrBgEFBQcDAjASBgNVHRMBAf8ECDAGAQH/AgEAMHYG\r\n"
        "CCsGAQUFBwEBBGowaDAkBggrBgEFBQcwAYYYaHR0cDovL29jc3AuZGlnaWNlcnQu\r\n"
        "Y29tMEAGCCsGAQUFBzAChjRodHRwOi8vY2FjZXJ0cy5kaWdpY2VydC5jb20vRGln\r\n"
        "aUNlcnRHbG9iYWxSb290RzIuY3J0MHsGA1UdHwR0MHIwN6A1oDOGMWh0dHA6Ly9j\r\n"
        "cmwzLmRpZ2ljZXJ0LmNvbS9EaWdpQ2VydEdsb2JhbFJvb3RHMi5jcmwwN6A1oDOG\r\n"
        "MWh0dHA6Ly9jcmw0LmRpZ2ljZXJ0LmNvbS9EaWdpQ2VydEdsb2JhbFJvb3RHMi5j\r\n"
        "cmwwHQYDVR0gBBYwFDAIBgZngQwBAgEwCAYGZ4EMAQICMBAGCSsGAQQBgjcVAQQD\r\n"
        "AgEAMA0GCSqGSIb3DQEBDAUAA4IBAQB2oWc93fB8esci/8esixj++N22meiGDjgF\r\n"
        "+rA2LUK5IOQOgcUSTGKSqF9lYfAxPjrqPjDCUPHCURv+26ad5P/BYtXtbmtxJWu+\r\n"
        "cS5BhMDPPeG3oPZwXRHBJFAkY4O4AF7RIAAUW6EzDflUoDHKv83zOiPfYGcpHc9s\r\n"
        "kxAInCedk7QSgXvMARjjOqdakor21DTmNIUotxo8kHv5hwRlGhBJwps6fEVi1Bt0\r\n"
        "trpM/3wYxlr473WSPUFZPgP1j519kLpWOJ8z09wxay+Br29irPcBYv0GMXlHqThy\r\n"
        "8y4m/HyTQeI2IMvMrQnwqPpY+rLIXyviI2vLoI+4xKE4Rn38ZZ8m\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

    Dies ist das *Microsoft Azure DigiCert Global Root G2-Zertifikat* - eines der Zertifikate, die weltweit von vielen Azure-Diensten verwendet werden.

    > 💁 Um zu sehen, dass dies das zu verwendende Zertifikat ist, führen Sie den folgenden Befehl auf macOS oder Linux aus. Wenn Sie Windows verwenden, können Sie diesen Befehl mit dem [Windows Subsystem for Linux (WSL)](https://docs.microsoft.com/windows/wsl/?WT.mc_id=academic-17441-jabenn) ausführen:
    >
    > ```sh
    > openssl s_client -showcerts -verify 5 -connect api.cognitive.microsoft.com:443
    > ```
    >
    > Die Ausgabe listet das DigiCert Global Root G2-Zertifikat auf.

1. Öffnen Sie `main.cpp` und fügen Sie die folgende Include-Direktive hinzu:

    ```cpp
    #include <WiFiClientSecure.h>
    ```

1. Deklarieren Sie unter den Include-Direktiven eine Instanz von `WifiClientSecure`:

    ```cpp
    WiFiClientSecure client;
    ```

    Diese Klasse enthält Code, um mit Web-Endpunkten über HTTPS zu kommunizieren.

1. Legen Sie in der Methode `connectWiFi` fest, dass `WifiClientSecure` das DigiCert Global Root G2-Zertifikat verwenden soll:

    ```cpp
    client.setCACert(CERTIFICATE);
    ```

### Aufgabe - Bild klassifizieren

1. Fügen Sie der Liste `lib_deps` in der Datei `platformio.ini` die folgende zusätzliche Zeile hinzu:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    Dies importiert [ArduinoJson](https://arduinojson.org), eine Arduino-JSON-Bibliothek, die verwendet wird, um die JSON-Antwort der REST-API zu dekodieren.

1. Fügen Sie in `config.h` Konstanten für die Vorhersage-URL und den Schlüssel des Custom Vision-Dienstes hinzu:

    ```cpp
    const char *PREDICTION_URL = "<PREDICTION_URL>";
    const char *PREDICTION_KEY = "<PREDICTION_KEY>";
    ```

    Ersetzen Sie `<PREDICTION_URL>` durch die Vorhersage-URL von Custom Vision. Ersetzen Sie `<PREDICTION_KEY>` durch den Vorhersageschlüssel.

1. Fügen Sie in `main.cpp` eine Include-Direktive für die ArduinoJson-Bibliothek hinzu:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. Fügen Sie die folgende Funktion in `main.cpp` oberhalb der Funktion `buttonPressed` hinzu:

    ```cpp
    void classifyImage(byte *buffer, uint32_t length)
    {
        HTTPClient httpClient;
        httpClient.begin(client, PREDICTION_URL);
        httpClient.addHeader("Content-Type", "application/octet-stream");
        httpClient.addHeader("Prediction-Key", PREDICTION_KEY);
    
        int httpResponseCode = httpClient.POST(buffer, length);
    
        if (httpResponseCode == 200)
        {
            String result = httpClient.getString();
    
            DynamicJsonDocument doc(1024);
            deserializeJson(doc, result.c_str());
    
            JsonObject obj = doc.as<JsonObject>();
            JsonArray predictions = obj["predictions"].as<JsonArray>();
    
            for(JsonVariant prediction : predictions) 
            {
                String tag = prediction["tagName"].as<String>();
                float probability = prediction["probability"].as<float>();
    
                char buff[32];
                sprintf(buff, "%s:\t%.2f%%", tag.c_str(), probability * 100.0);
                Serial.println(buff);
            }
        }
    
        httpClient.end();
    }
    ```

    Dieser Code beginnt mit der Deklaration eines `HTTPClient` - einer Klasse, die Methoden zum Interagieren mit REST-APIs enthält. Anschließend verbindet er den Client mit der Vorhersage-URL unter Verwendung der `WiFiClientSecure`-Instanz, die mit dem öffentlichen Schlüssel von Azure eingerichtet wurde.

    Sobald die Verbindung hergestellt ist, sendet er Header - Informationen über die bevorstehende Anfrage, die gegen die REST-API gestellt wird. Der Header `Content-Type` gibt an, dass der API-Aufruf rohe Binärdaten sendet, und der Header `Prediction-Key` übermittelt den Custom Vision-Vorhersageschlüssel.

    Anschließend wird eine POST-Anfrage an den HTTP-Client gesendet, wobei ein Byte-Array hochgeladen wird. Dieses enthält das JPEG-Bild, das von der Kamera aufgenommen wurde, wenn diese Funktion aufgerufen wird.

    > 💁 POST-Anfragen dienen dazu, Daten zu senden und eine Antwort zu erhalten. Es gibt andere Anfragearten wie GET-Anfragen, die Daten abrufen. GET-Anfragen werden von Ihrem Webbrowser verwendet, um Webseiten zu laden.

    Die POST-Anfrage gibt einen Antwortstatuscode zurück. Diese sind gut definierte Werte, wobei 200 **OK** bedeutet - die POST-Anfrage war erfolgreich.

    > 💁 Sie können alle Antwortstatuscodes auf der [Liste der HTTP-Statuscodes-Seite auf Wikipedia](https://wikipedia.org/wiki/List_of_HTTP_status_codes) einsehen.

    Wenn ein 200 zurückgegeben wird, wird das Ergebnis vom HTTP-Client gelesen. Dies ist eine Textantwort der REST-API mit den Ergebnissen der Vorhersage als JSON-Dokument. Das JSON hat folgendes Format:

    ```jSON
    {
        "id":"45d614d3-7d6f-47e9-8fa2-04f237366a16",
        "project":"135607e5-efac-4855-8afb-c93af3380531",
        "iteration":"04f1c1fa-11ec-4e59-bb23-4c7aca353665",
        "created":"2021-06-10T17:58:58.959Z",
        "predictions":[
            {
                "probability":0.5582016,
                "tagId":"05a432ea-9718-4098-b14f-5f0688149d64",
                "tagName":"ripe"
            },
            {
                "probability":0.44179836,
                "tagId":"bb091037-16e5-418e-a9ea-31c6a2920f17",
                "tagName":"unripe"
            }
        ]
    }
    ```

    Der wichtige Teil hier ist das `predictions`-Array. Dieses enthält die Vorhersagen, mit einem Eintrag für jedes Tag, der den Tag-Namen und die Wahrscheinlichkeit enthält. Die zurückgegebenen Wahrscheinlichkeiten sind Gleitkommazahlen von 0-1, wobei 0 einer 0%-Chance entspricht, das Tag zu treffen, und 1 einer 100%-Chance.

    > 💁 Bildklassifikatoren geben die Prozentsätze für alle verwendeten Tags zurück. Jedes Tag hat eine Wahrscheinlichkeit, dass das Bild diesem Tag entspricht.

    Dieses JSON wird dekodiert, und die Wahrscheinlichkeiten für jedes Tag werden an den seriellen Monitor gesendet.

1. Ersetzen Sie in der Funktion `buttonPressed` entweder den Code, der auf die SD-Karte speichert, durch einen Aufruf von `classifyImage`, oder fügen Sie ihn nach dem Schreiben des Bildes hinzu, aber **vor** dem Löschen des Puffers:

    ```cpp
    classifyImage(buffer, length);
    ```

    > 💁 Wenn Sie den Code ersetzen, der auf die SD-Karte speichert, können Sie Ihren Code bereinigen, indem Sie die Funktionen `setupSDCard` und `saveToSDCard` entfernen.

1. Laden Sie Ihren Code hoch und führen Sie ihn aus. Richten Sie die Kamera auf ein Stück Obst und drücken Sie die C-Taste. Sie sehen die Ausgabe im seriellen Monitor:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

    Sie können das aufgenommene Bild und diese Werte im **Predictions**-Tab in Custom Vision sehen.

    ![Eine Banane in Custom Vision, vorhergesagt als reif mit 56,8% und unreif mit 43,1%](../../../../../translated_images/de/custom-vision-banana-prediction.30cdff4e1d72db5d9a0be0193790a47c2b387da034e12dc1314dd57ca2131b59.png)

> 💁 Sie finden diesen Code im Ordner [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/wio-terminal).

😀 Ihr Programm zur Klassifikation der Obstqualität war ein Erfolg!

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.