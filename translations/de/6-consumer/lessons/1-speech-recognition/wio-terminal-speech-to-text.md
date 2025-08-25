<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3f92edf2975175577174910caca4a389",
  "translation_date": "2025-08-25T22:48:20+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-speech-to-text.md",
  "language_code": "de"
}
-->
# Sprache zu Text - Wio Terminal

In diesem Teil der Lektion schreiben Sie Code, um Sprache aus dem aufgenommenen Audio mithilfe des Sprachdienstes in Text umzuwandeln.

## Senden des Audios an den Sprachdienst

Das Audio kann über die REST-API an den Sprachdienst gesendet werden. Um den Sprachdienst zu nutzen, müssen Sie zunächst ein Zugriffstoken anfordern und dieses verwenden, um auf die REST-API zuzugreifen. Diese Zugriffstoken laufen nach 10 Minuten ab, daher sollte Ihr Code sie regelmäßig anfordern, um sicherzustellen, dass sie immer aktuell sind.

### Aufgabe - Zugriffstoken abrufen

1. Öffnen Sie das Projekt `smart-timer`, falls es noch nicht geöffnet ist.

1. Fügen Sie die folgenden Bibliotheksabhängigkeiten in die Datei `platformio.ini` ein, um auf WLAN zuzugreifen und JSON zu verarbeiten:

    ```ini
    seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
    seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
    seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    bblanchon/ArduinoJson @ 6.17.3
    ```

1. Fügen Sie den folgenden Code in die Header-Datei `config.h` ein:

    ```cpp
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    
    const char *SPEECH_API_KEY = "<API_KEY>";
    const char *SPEECH_LOCATION = "<LOCATION>";
    const char *LANGUAGE = "<LANGUAGE>";

    const char *TOKEN_URL = "https://%s.api.cognitive.microsoft.com/sts/v1.0/issuetoken";
    ```

    Ersetzen Sie `<SSID>` und `<PASSWORD>` durch die entsprechenden Werte für Ihr WLAN.

    Ersetzen Sie `<API_KEY>` durch den API-Schlüssel für Ihre Sprachdienstressource. Ersetzen Sie `<LOCATION>` durch den Standort, den Sie bei der Erstellung der Sprachdienstressource verwendet haben.

    Ersetzen Sie `<LANGUAGE>` durch den Gebietsschemanamen der Sprache, in der Sie sprechen werden, z. B. `en-GB` für Englisch oder `zn-HK` für Kantonesisch. Eine Liste der unterstützten Sprachen und ihrer Gebietsschemanamen finden Sie in der [Dokumentation zur Sprach- und Sprachunterstützung auf Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    Die Konstante `TOKEN_URL` ist die URL des Token-Ausstellers ohne Standort. Diese wird später mit dem Standort kombiniert, um die vollständige URL zu erhalten.

1. Genau wie bei der Verbindung zu Custom Vision müssen Sie eine HTTPS-Verbindung verwenden, um sich mit dem Token-Ausstellungsdienst zu verbinden. Fügen Sie am Ende von `config.h` den folgenden Code hinzu:

    ```cpp
    const char *TOKEN_CERTIFICATE =
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

    Dies ist dasselbe Zertifikat, das Sie bei der Verbindung zu Custom Vision verwendet haben.

1. Fügen Sie eine Include-Direktive für die WLAN-Header-Datei und die Konfigurations-Header-Datei oben in der Datei `main.cpp` hinzu:

    ```cpp
    #include <rpcWiFi.h>

    #include "config.h"
    ```

1. Fügen Sie Code hinzu, um eine Verbindung zu WLAN in `main.cpp` oberhalb der Funktion `setup` herzustellen:

    ```cpp
    void connectWiFi()
    {
        while (WiFi.status() != WL_CONNECTED)
        {
            Serial.println("Connecting to WiFi..");
            WiFi.begin(SSID, PASSWORD);
            delay(500);
        }
    
        Serial.println("Connected!");
    }
    ```

1. Rufen Sie diese Funktion aus der Funktion `setup` auf, nachdem die serielle Verbindung hergestellt wurde:

    ```cpp
    connectWiFi();
    ```

1. Erstellen Sie eine neue Header-Datei im Ordner `src` mit dem Namen `speech_to_text.h`. Fügen Sie in dieser Header-Datei den folgenden Code hinzu:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClientSecure.h>
    
    #include "config.h"
    #include "mic.h"
    
    class SpeechToText
    {
    public:

    private:

    };

    SpeechToText speechToText;
    ```

    Dies umfasst einige notwendige Header-Dateien für eine HTTP-Verbindung, Konfiguration und die Header-Datei `mic.h` und definiert eine Klasse namens `SpeechToText`, bevor eine Instanz dieser Klasse deklariert wird, die später verwendet werden kann.

1. Fügen Sie die folgenden 2 Felder in den Abschnitt `private` dieser Klasse ein:

    ```cpp
    WiFiClientSecure _token_client;
    String _access_token;
    ```

    Der `_token_client` ist ein WLAN-Client, der HTTPS verwendet und zum Abrufen des Zugriffstokens verwendet wird. Dieses Token wird dann in `_access_token` gespeichert.

1. Fügen Sie die folgende Methode in den Abschnitt `private` ein:

    ```cpp
    String getAccessToken()
    {
        char url[128];
        sprintf(url, TOKEN_URL, SPEECH_LOCATION);
    
        HTTPClient httpClient;
        httpClient.begin(_token_client, url);
    
        httpClient.addHeader("Ocp-Apim-Subscription-Key", SPEECH_API_KEY);
        int httpResultCode = httpClient.POST("{}");
    
        if (httpResultCode != 200)
        {
            Serial.println("Error getting access token, trying again...");
            delay(10000);
            return getAccessToken();
        }
    
        Serial.println("Got access token.");
        String result = httpClient.getString();
    
        httpClient.end();
    
        return result;
    }
    ```

    Dieser Code erstellt die URL für die Token-Aussteller-API basierend auf dem Standort der Sprachressource. Anschließend wird ein `HTTPClient` erstellt, um die Webanfrage zu stellen, wobei der WLAN-Client mit dem Zertifikat des Token-Endpunkts konfiguriert wird. Der API-Schlüssel wird als Header für den Aufruf festgelegt. Anschließend wird eine POST-Anfrage gestellt, um das Zertifikat abzurufen, wobei bei Fehlern erneut versucht wird. Schließlich wird das Zugriffstoken zurückgegeben.

1. Fügen Sie im Abschnitt `public` eine Methode hinzu, um das Zugriffstoken abzurufen. Dies wird in späteren Lektionen benötigt, um Text in Sprache umzuwandeln.

    ```cpp
    String AccessToken()
    {
        return _access_token;
    }
    ```

1. Fügen Sie im Abschnitt `public` eine `init`-Methode hinzu, die den Token-Client einrichtet:

    ```cpp
    void init()
    {
        _token_client.setCACert(TOKEN_CERTIFICATE);
        _access_token = getAccessToken();
    }
    ```

    Dies setzt das Zertifikat auf den WLAN-Client und ruft dann das Zugriffstoken ab.

1. Fügen Sie in `main.cpp` diese neue Header-Datei zu den Include-Direktiven hinzu:

    ```cpp
    #include "speech_to_text.h"
    ```

1. Initialisieren Sie die Klasse `SpeechToText` am Ende der Funktion `setup`, nach dem Aufruf von `mic.init`, aber bevor `Ready` auf dem seriellen Monitor ausgegeben wird:

    ```cpp
    speechToText.init();
    ```

### Aufgabe - Audio aus dem Flash-Speicher lesen

1. In einem früheren Teil dieser Lektion wurde das Audio im Flash-Speicher aufgezeichnet. Dieses Audio muss an die REST-API des Sprachdienstes gesendet werden, daher muss es aus dem Flash-Speicher gelesen werden. Es kann nicht in einen In-Memory-Puffer geladen werden, da es zu groß wäre. Die Klasse `HTTPClient`, die REST-Aufrufe ausführt, kann Daten mithilfe eines Arduino-Streams streamen - einer Klasse, die Daten in kleinen Blöcken laden und die Blöcke einzeln als Teil der Anfrage senden kann. Jedes Mal, wenn Sie `read` auf einem Stream aufrufen, wird der nächste Datenblock zurückgegeben. Ein Arduino-Stream kann erstellt werden, der aus dem Flash-Speicher lesen kann. Erstellen Sie eine neue Datei namens `flash_stream.h` im Ordner `src` und fügen Sie den folgenden Code hinzu:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <HTTPClient.h>
    #include <sfud.h>

    #include "config.h"
    
    class FlashStream : public Stream
    {
    public:
        virtual size_t write(uint8_t val)
        {    
        }
    
        virtual int available()
        {
        }
    
        virtual int read()
        {
        }
    
        virtual int peek()
        {
        }
    private:
    
    };
    ```

    Dies deklariert die Klasse `FlashStream`, die von der Arduino-Klasse `Stream` abgeleitet ist. Dies ist eine abstrakte Klasse - abgeleitete Klassen müssen einige Methoden implementieren, bevor die Klasse instanziiert werden kann, und diese Methoden sind in dieser Klasse definiert.

    ✅ Lesen Sie mehr über Arduino-Streams in der [Arduino Stream-Dokumentation](https://www.arduino.cc/reference/en/language/functions/communication/stream/)

1. Fügen Sie die folgenden Felder in den Abschnitt `private` ein:

    ```cpp
    size_t _pos;
    size_t _flash_address;
    const sfud_flash *_flash;

    byte _buffer[HTTP_TCP_BUFFER_SIZE];
    ```

    Dies definiert einen temporären Puffer zum Speichern von Daten, die aus dem Flash-Speicher gelesen wurden, sowie Felder zum Speichern der aktuellen Position beim Lesen aus dem Puffer, der aktuellen Adresse zum Lesen aus dem Flash-Speicher und des Flash-Speichergeräts.

1. Fügen Sie im Abschnitt `private` die folgende Methode hinzu:

    ```cpp
    void populateBuffer()
    {
        sfud_read(_flash, _flash_address, HTTP_TCP_BUFFER_SIZE, _buffer);
        _flash_address += HTTP_TCP_BUFFER_SIZE;
        _pos = 0;
    }
    ```

    Dieser Code liest aus dem Flash-Speicher an der aktuellen Adresse und speichert die Daten in einem Puffer. Anschließend wird die Adresse inkrementiert, sodass der nächste Aufruf den nächsten Speicherblock liest. Die Größe des Puffers basiert auf dem größten Block, den der `HTTPClient` gleichzeitig an die REST-API sendet.

    > 💁 Das Löschen des Flash-Speichers muss mit der Körnungsgröße erfolgen, das Lesen hingegen nicht.

1. Fügen Sie im Abschnitt `public` dieser Klasse einen Konstruktor hinzu:

    ```cpp
    FlashStream()
    {
        _pos = 0;
        _flash_address = 0;
        _flash = sfud_get_device_table() + 0;
        
        populateBuffer();
    }
    ```

    Dieser Konstruktor richtet alle Felder ein, um das Lesen vom Anfang des Flash-Speicherblocks zu starten, und lädt den ersten Datenblock in den Puffer.

1. Implementieren Sie die Methode `write`. Dieser Stream wird nur Daten lesen, daher kann diese Methode nichts tun und 0 zurückgeben:

    ```cpp
    virtual size_t write(uint8_t val)
    {
        return 0;
    }
    ```

1. Implementieren Sie die Methode `peek`. Diese gibt die Daten an der aktuellen Position zurück, ohne den Stream weiterzubewegen. Mehrmaliges Aufrufen von `peek` gibt immer dieselben Daten zurück, solange keine Daten aus dem Stream gelesen werden.

    ```cpp
    virtual int peek()
    {
        return _buffer[_pos];
    }
    ```

1. Implementieren Sie die Funktion `available`. Diese gibt zurück, wie viele Bytes aus dem Stream gelesen werden können, oder -1, wenn der Stream abgeschlossen ist. Für diese Klasse wird die maximale Verfügbarkeit nicht mehr als die Chunk-Größe des HTTP-Clients betragen. Wenn dieser Stream im HTTP-Client verwendet wird, ruft dieser die Funktion auf, um zu sehen, wie viele Daten verfügbar sind, und fordert dann so viele Daten an, um sie an die REST-API zu senden. Wir möchten, dass jeder Block nicht größer als die Chunk-Größe des HTTP-Clients ist. Wenn mehr verfügbar ist, wird die Chunk-Größe zurückgegeben. Wenn weniger verfügbar ist, wird die verfügbare Menge zurückgegeben. Sobald alle Daten gestreamt wurden, wird -1 zurückgegeben.

    ```cpp
    virtual int available()
    {
        int remaining = BUFFER_SIZE - ((_flash_address - HTTP_TCP_BUFFER_SIZE) + _pos);
        int bytes_available = min(HTTP_TCP_BUFFER_SIZE, remaining);

        if (bytes_available == 0)
        {
            bytes_available = -1;
        }

        return bytes_available;
    }
    ```

1. Implementieren Sie die Methode `read`, um das nächste Byte aus dem Puffer zurückzugeben und die Position zu inkrementieren. Wenn die Position die Größe des Puffers überschreitet, wird der Puffer mit dem nächsten Block aus dem Flash-Speicher gefüllt und die Position zurückgesetzt.

    ```cpp
    virtual int read()
    {
        int retVal = _buffer[_pos++];

        if (_pos == HTTP_TCP_BUFFER_SIZE)
        {
            populateBuffer();
        }

        return retVal;
    }
    ```

1. Fügen Sie in der Header-Datei `speech_to_text.h` eine Include-Direktive für diese neue Header-Datei hinzu:

    ```cpp
    #include "flash_stream.h"
    ```

### Aufgabe - Sprache in Text umwandeln

1. Die Sprache kann in Text umgewandelt werden, indem das Audio über eine REST-API an den Sprachdienst gesendet wird. Diese REST-API hat ein anderes Zertifikat als der Token-Aussteller, daher fügen Sie den folgenden Code in die Header-Datei `config.h` ein, um dieses Zertifikat zu definieren:

    ```cpp
    const char *SPEECH_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "MIIF8zCCBNugAwIBAgIQCq+mxcpjxFFB6jvh98dTFzANBgkqhkiG9w0BAQwFADBh\r\n"
        "MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\r\n"
        "d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBH\r\n"
        "MjAeFw0yMDA3MjkxMjMwMDBaFw0yNDA2MjcyMzU5NTlaMFkxCzAJBgNVBAYTAlVT\r\n"
        "MR4wHAYDVQQKExVNaWNyb3NvZnQgQ29ycG9yYXRpb24xKjAoBgNVBAMTIU1pY3Jv\r\n"
        "c29mdCBBenVyZSBUTFMgSXNzdWluZyBDQSAwMTCCAiIwDQYJKoZIhvcNAQEBBQAD\r\n"
        "ggIPADCCAgoCggIBAMedcDrkXufP7pxVm1FHLDNA9IjwHaMoaY8arqqZ4Gff4xyr\r\n"
        "RygnavXL7g12MPAx8Q6Dd9hfBzrfWxkF0Br2wIvlvkzW01naNVSkHp+OS3hL3W6n\r\n"
        "l/jYvZnVeJXjtsKYcXIf/6WtspcF5awlQ9LZJcjwaH7KoZuK+THpXCMtzD8XNVdm\r\n"
        "GW/JI0C/7U/E7evXn9XDio8SYkGSM63aLO5BtLCv092+1d4GGBSQYolRq+7Pd1kR\r\n"
        "EkWBPm0ywZ2Vb8GIS5DLrjelEkBnKCyy3B0yQud9dpVsiUeE7F5sY8Me96WVxQcb\r\n"
        "OyYdEY/j/9UpDlOG+vA+YgOvBhkKEjiqygVpP8EZoMMijephzg43b5Qi9r5UrvYo\r\n"
        "o19oR/8pf4HJNDPF0/FJwFVMW8PmCBLGstin3NE1+NeWTkGt0TzpHjgKyfaDP2tO\r\n"
        "4bCk1G7pP2kDFT7SYfc8xbgCkFQ2UCEXsaH/f5YmpLn4YPiNFCeeIida7xnfTvc4\r\n"
        "7IxyVccHHq1FzGygOqemrxEETKh8hvDR6eBdrBwmCHVgZrnAqnn93JtGyPLi6+cj\r\n"
        "WGVGtMZHwzVvX1HvSFG771sskcEjJxiQNQDQRWHEh3NxvNb7kFlAXnVdRkkvhjpR\r\n"
        "GchFhTAzqmwltdWhWDEyCMKC2x/mSZvZtlZGY+g37Y72qHzidwtyW7rBetZJAgMB\r\n"
        "AAGjggGtMIIBqTAdBgNVHQ4EFgQUDyBd16FXlduSzyvQx8J3BM5ygHYwHwYDVR0j\r\n"
        "BBgwFoAUTiJUIBiV5uNu5g/6+rkS7QYXjzkwDgYDVR0PAQH/BAQDAgGGMB0GA1Ud\r\n"
        "JQQWMBQGCCsGAQUFBwMBBggrBgEFBQcDAjASBgNVHRMBAf8ECDAGAQH/AgEAMHYG\r\n"
        "CCsGAQUFBwEBBGowaDAkBggrBgEFBQcwAYYYaHR0cDovL29jc3AuZGlnaWNlcnQu\r\n"
        "Y29tMEAGCCsGAQUFBzAChjRodHRwOi8vY2FjZXJ0cy5kaWdpY2VydC5jb20vRGln\r\n"
        "aUNlcnRHbG9iYWxSb290RzIuY3J0MHsGA1UdHwR0MHIwN6A1oDOGMWh0dHA6Ly9j\r\n"
        "cmwzLmRpZ2ljZXJ0LmNvbS9EaWdpQ2VydEdsb2JhbFJvb3RHMi5jcmwwN6A1oDOG\r\n"
        "MWh0dHA6Ly9jcmw0LmRpZ2ljZXJ0LmNvbS9EaWdpQ2VydEdsb2JhbFJvb3RHMi5j\r\n"
        "cmwwHQYDVR0gBBYwFDAIBgZngQwBAgEwCAYGZ4EMAQICMBAGCSsGAQQBgjcVAQQD\r\n"
        "AgEAMA0GCSqGSIb3DQEBDAUAA4IBAQAlFvNh7QgXVLAZSsNR2XRmIn9iS8OHFCBA\r\n"
        "WxKJoi8YYQafpMTkMqeuzoL3HWb1pYEipsDkhiMnrpfeYZEA7Lz7yqEEtfgHcEBs\r\n"
        "K9KcStQGGZRfmWU07hPXHnFz+5gTXqzCE2PBMlRgVUYJiA25mJPXfB00gDvGhtYa\r\n"
        "+mENwM9Bq1B9YYLyLjRtUz8cyGsdyTIG/bBM/Q9jcV8JGqMU/UjAdh1pFyTnnHEl\r\n"
        "Y59Npi7F87ZqYYJEHJM2LGD+le8VsHjgeWX2CJQko7klXvcizuZvUEDTjHaQcs2J\r\n"
        "+kPgfyMIOY1DMJ21NxOJ2xPRC/wAh/hzSBRVtoAnyuxtkZ4VjIOh\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

1. Fügen Sie eine Konstante in diese Datei für die Sprach-URL ohne Standort hinzu. Diese wird später mit dem Standort und der Sprache kombiniert, um die vollständige URL zu erhalten.

    ```cpp
    const char *SPEECH_URL = "https://%s.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1?language=%s";
    ```

1. Definieren Sie in der Header-Datei `speech_to_text.h` im Abschnitt `private` der Klasse `SpeechToText` ein Feld für einen WLAN-Client, der das Sprachzertifikat verwendet:

    ```cpp
    WiFiClientSecure _speech_client;
    ```

1. Setzen Sie in der Methode `init` das Zertifikat auf diesen WLAN-Client:

    ```cpp
    _speech_client.setCACert(SPEECH_CERTIFICATE);
    ```

1. Fügen Sie im Abschnitt `public` der Klasse `SpeechToText` die folgende Methode hinzu, um Sprache in Text umzuwandeln:

    ```cpp
    String convertSpeechToText()
    {
        
    }
    ```

1. Fügen Sie den folgenden Code in diese Methode ein, um einen HTTP-Client mit dem WLAN-Client zu erstellen, der mit dem Sprachzertifikat konfiguriert ist, und die Sprach-URL mit Standort und Sprache zu verwenden:

    ```cpp
    char url[128];
    sprintf(url, SPEECH_URL, SPEECH_LOCATION, LANGUAGE);

    HTTPClient httpClient;
    httpClient.begin(_speech_client, url);
    ```

1. Einige Header müssen auf der Verbindung gesetzt werden:

    ```cpp
    httpClient.addHeader("Authorization", String("Bearer ") + _access_token);
    httpClient.addHeader("Content-Type", String("audio/wav; codecs=audio/pcm; samplerate=") + String(RATE));
    httpClient.addHeader("Accept", "application/json;text/xml");
    ```

    Dies setzt Header für die Autorisierung mit dem Zugriffstoken, das Audioformat mit der Abtastrate und gibt an, dass der Client das Ergebnis als JSON erwartet.

1. Fügen Sie danach den folgenden Code hinzu, um den REST-API-Aufruf auszuführen:

    ```cpp
    Serial.println("Sending speech...");

    FlashStream stream;
    int httpResponseCode = httpClient.sendRequest("POST", &stream, BUFFER_SIZE);

    Serial.println("Speech sent!");
    ```

    Dies erstellt einen `FlashStream` und verwendet ihn, um Daten an die REST-API zu streamen.

1. Fügen Sie darunter den folgenden Code hinzu:

    ```cpp
    String text = "";

    if (httpResponseCode == 200)
    {
        String result = httpClient.getString();
        Serial.println(result);

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, result.c_str());

        JsonObject obj = doc.as<JsonObject>();
        text = obj["DisplayText"].as<String>();
    }
    else if (httpResponseCode == 401)
    {
        Serial.println("Access token expired, trying again with a new token");
        _access_token = getAccessToken();
        return convertSpeechToText();
    }
    else
    {
        Serial.print("Failed to convert text to speech - error ");
        Serial.println(httpResponseCode);
    }
    ```

    Dieser Code überprüft den Antwortcode.

    Wenn er 200 ist, der Code für Erfolg, wird das Ergebnis abgerufen, aus JSON dekodiert und die Eigenschaft `DisplayText` in die Variable `text` gesetzt. Dies ist die Eigenschaft, in der die Textversion der Sprache zurückgegeben wird.

    Wenn der Antwortcode 401 ist, ist das Zugriffstoken abgelaufen (diese Token sind nur 10 Minuten gültig). Ein neues Zugriffstoken wird angefordert und der Aufruf erneut ausgeführt.

    Andernfalls wird ein Fehler an den seriellen Monitor gesendet und `text` bleibt leer.

1. Fügen Sie den folgenden Code am Ende dieser Methode hinzu, um den HTTP-Client zu schließen und den Text zurückzugeben:

    ```cpp
    httpClient.end();

    return text;
    ```

1. Rufen Sie in `main.cpp` diese neue Methode `convertSpeechToText` in der Funktion `processAudio` auf und geben Sie die Sprache auf dem seriellen Monitor aus:

    ```cpp
    String text = speechToText.convertSpeechToText();
    Serial.println(text);
    ```

1. Bauen Sie diesen Code, laden Sie ihn auf Ihren Wio Terminal hoch und testen Sie ihn über den seriellen Monitor. Sobald Sie `Ready` im seriellen Monitor sehen, drücken Sie die C-Taste (die auf der linken Seite, am nächsten zum Netzschalter), und sprechen Sie. 4 Sekunden Audio werden aufgenommen und dann in Text umgewandelt.

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
    ```

> 💁 Sie finden diesen Code im Ordner [code-speech-to-text/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/wio-terminal).

😀 Ihr Programm zur Umwandlung von Sprache in Text war ein Erfolg!

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.