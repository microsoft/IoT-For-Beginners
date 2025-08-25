<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3f92edf2975175577174910caca4a389",
  "translation_date": "2025-08-25T17:56:01+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-speech-to-text.md",
  "language_code": "it"
}
-->
# Da voce a testo - Wio Terminal

In questa parte della lezione, scriverai il codice per convertire la voce registrata nell'audio catturato in testo utilizzando il servizio di riconoscimento vocale.

## Invia l'audio al servizio di riconoscimento vocale

L'audio può essere inviato al servizio di riconoscimento vocale utilizzando l'API REST. Per utilizzare il servizio, devi prima richiedere un token di accesso e poi utilizzare quel token per accedere all'API REST. Questi token di accesso scadono dopo 10 minuti, quindi il tuo codice dovrebbe richiederli regolarmente per garantire che siano sempre aggiornati.

### Attività - ottenere un token di accesso

1. Apri il progetto `smart-timer` se non è già aperto.

1. Aggiungi le seguenti dipendenze di libreria al file `platformio.ini` per accedere al WiFi e gestire JSON:

    ```ini
    seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
    seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
    seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    bblanchon/ArduinoJson @ 6.17.3
    ```

1. Aggiungi il seguente codice al file di intestazione `config.h`:

    ```cpp
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    
    const char *SPEECH_API_KEY = "<API_KEY>";
    const char *SPEECH_LOCATION = "<LOCATION>";
    const char *LANGUAGE = "<LANGUAGE>";

    const char *TOKEN_URL = "https://%s.api.cognitive.microsoft.com/sts/v1.0/issuetoken";
    ```

    Sostituisci `<SSID>` e `<PASSWORD>` con i valori pertinenti per il tuo WiFi.

    Sostituisci `<API_KEY>` con la chiave API per la tua risorsa del servizio di riconoscimento vocale. Sostituisci `<LOCATION>` con la posizione che hai utilizzato quando hai creato la risorsa del servizio di riconoscimento vocale.

    Sostituisci `<LANGUAGE>` con il nome della lingua che utilizzerai, ad esempio `en-GB` per l'inglese o `zn-HK` per il cantonese. Puoi trovare un elenco delle lingue supportate e dei loro nomi locali nella [documentazione sul supporto delle lingue e delle voci su Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    La costante `TOKEN_URL` è l'URL dell'emittente del token senza la posizione. Questo sarà combinato con la posizione successivamente per ottenere l'URL completo.

1. Come per la connessione a Custom Vision, dovrai utilizzare una connessione HTTPS per connetterti al servizio di emissione dei token. Alla fine di `config.h`, aggiungi il seguente codice:

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

    Questo è lo stesso certificato che hai utilizzato per connetterti a Custom Vision.

1. Aggiungi un'inclusione per il file di intestazione WiFi e il file di configurazione all'inizio del file `main.cpp`:

    ```cpp
    #include <rpcWiFi.h>

    #include "config.h"
    ```

1. Aggiungi il codice per connetterti al WiFi in `main.cpp` sopra la funzione `setup`:

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

1. Chiama questa funzione dalla funzione `setup` dopo che la connessione seriale è stata stabilita:

    ```cpp
    connectWiFi();
    ```

1. Crea un nuovo file di intestazione nella cartella `src` chiamato `speech_to_text.h`. In questo file di intestazione, aggiungi il seguente codice:

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

    Questo include alcuni file di intestazione necessari per una connessione HTTP, la configurazione e il file di intestazione `mic.h`, e definisce una classe chiamata `SpeechToText`, prima di dichiarare un'istanza di questa classe che può essere utilizzata successivamente.

1. Aggiungi i seguenti 2 campi alla sezione `private` di questa classe:

    ```cpp
    WiFiClientSecure _token_client;
    String _access_token;
    ```

    `_token_client` è un WiFi Client che utilizza HTTPS e sarà utilizzato per ottenere il token di accesso. Questo token sarà poi memorizzato in `_access_token`.

1. Aggiungi il seguente metodo alla sezione `private`:

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

    Questo codice costruisce l'URL per l'API dell'emittente del token utilizzando la posizione della risorsa vocale. Quindi crea un `HTTPClient` per effettuare la richiesta web, configurandolo per utilizzare il client WiFi configurato con il certificato degli endpoint del token. Imposta la chiave API come intestazione per la chiamata. Effettua quindi una richiesta POST per ottenere il certificato, riprovando in caso di errori. Infine, il token di accesso viene restituito.

1. Nella sezione `public`, aggiungi un metodo per ottenere il token di accesso. Questo sarà necessario nelle lezioni successive per convertire il testo in voce.

    ```cpp
    String AccessToken()
    {
        return _access_token;
    }
    ```

1. Nella sezione `public`, aggiungi un metodo `init` che configura il client del token:

    ```cpp
    void init()
    {
        _token_client.setCACert(TOKEN_CERTIFICATE);
        _access_token = getAccessToken();
    }
    ```

    Questo imposta il certificato sul client WiFi, quindi ottiene il token di accesso.

1. In `main.cpp`, aggiungi questo nuovo file di intestazione alle direttive di inclusione:

    ```cpp
    #include "speech_to_text.h"
    ```

1. Inizializza la classe `SpeechToText` alla fine della funzione `setup`, dopo la chiamata a `mic.init` ma prima che `Ready` venga scritto sul monitor seriale:

    ```cpp
    speechToText.init();
    ```

### Attività - leggere l'audio dalla memoria flash

1. In una parte precedente di questa lezione, l'audio è stato registrato nella memoria flash. Questo audio dovrà essere inviato all'API REST del servizio di riconoscimento vocale, quindi deve essere letto dalla memoria flash. Non può essere caricato in un buffer in memoria poiché sarebbe troppo grande. La classe `HTTPClient` che effettua le chiamate REST può trasmettere dati utilizzando uno Stream di Arduino - una classe che può caricare dati in piccoli blocchi, inviando i blocchi uno alla volta come parte della richiesta. Ogni volta che chiami `read` su uno stream, restituisce il prossimo blocco di dati. Può essere creato uno stream di Arduino che legge dalla memoria flash. Crea un nuovo file chiamato `flash_stream.h` nella cartella `src` e aggiungi il seguente codice:

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

    Questo dichiara la classe `FlashStream`, derivata dalla classe `Stream` di Arduino. Questa è una classe astratta - le classi derivate devono implementare alcuni metodi prima che la classe possa essere istanziata, e questi metodi sono definiti in questa classe.

    ✅ Leggi di più sugli Stream di Arduino nella [documentazione sugli Stream di Arduino](https://www.arduino.cc/reference/en/language/functions/communication/stream/)

1. Aggiungi i seguenti campi alla sezione `private`:

    ```cpp
    size_t _pos;
    size_t _flash_address;
    const sfud_flash *_flash;

    byte _buffer[HTTP_TCP_BUFFER_SIZE];
    ```

    Questo definisce un buffer temporaneo per memorizzare i dati letti dalla memoria flash, insieme ai campi per memorizzare la posizione corrente durante la lettura dal buffer, l'indirizzo corrente per leggere dalla memoria flash e il dispositivo di memoria flash.

1. Nella sezione `private`, aggiungi il seguente metodo:

    ```cpp
    void populateBuffer()
    {
        sfud_read(_flash, _flash_address, HTTP_TCP_BUFFER_SIZE, _buffer);
        _flash_address += HTTP_TCP_BUFFER_SIZE;
        _pos = 0;
    }
    ```

    Questo codice legge dalla memoria flash all'indirizzo corrente e memorizza i dati in un buffer. Incrementa quindi l'indirizzo, in modo che la prossima chiamata legga il prossimo blocco di memoria. Il buffer è dimensionato in base al blocco più grande che il `HTTPClient` invierà all'API REST in una sola volta.

    > 💁 La cancellazione della memoria flash deve essere effettuata utilizzando la dimensione del grano, mentre la lettura non ha questa limitazione.

1. Nella sezione `public` di questa classe, aggiungi un costruttore:

    ```cpp
    FlashStream()
    {
        _pos = 0;
        _flash_address = 0;
        _flash = sfud_get_device_table() + 0;
        
        populateBuffer();
    }
    ```

    Questo costruttore configura tutti i campi per iniziare a leggere dall'inizio del blocco di memoria flash e carica il primo blocco di dati nel buffer.

1. Implementa il metodo `write`. Questo stream leggerà solo dati, quindi può non fare nulla e restituire 0:

    ```cpp
    virtual size_t write(uint8_t val)
    {
        return 0;
    }
    ```

1. Implementa il metodo `peek`. Questo restituisce i dati alla posizione corrente senza spostare lo stream. Chiamare `peek` più volte restituirà sempre gli stessi dati finché non vengono letti dati dallo stream.

    ```cpp
    virtual int peek()
    {
        return _buffer[_pos];
    }
    ```

1. Implementa la funzione `available`. Questa restituisce quanti byte possono essere letti dallo stream, o -1 se lo stream è completo. Per questa classe, il massimo disponibile non sarà mai superiore alla dimensione del blocco del client HTTP. Quando questo stream viene utilizzato nel client HTTP, chiama questa funzione per vedere quanti dati sono disponibili, quindi richiede quella quantità di dati da inviare all'API REST. Non vogliamo che ogni blocco sia più grande della dimensione del blocco del client HTTP, quindi se è disponibile più di quello, viene restituita la dimensione del blocco. Se meno, viene restituito ciò che è disponibile. Una volta che tutti i dati sono stati trasmessi, viene restituito -1.

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

1. Implementa il metodo `read` per restituire il prossimo byte dal buffer, incrementando la posizione. Se la posizione supera la dimensione del buffer, il buffer viene popolato con il prossimo blocco dalla memoria flash e la posizione viene reimpostata.

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

1. Nel file di intestazione `speech_to_text.h`, aggiungi una direttiva di inclusione per questo nuovo file di intestazione:

    ```cpp
    #include "flash_stream.h"
    ```

### Attività - convertire la voce in testo

1. La voce può essere convertita in testo inviando l'audio al servizio di riconoscimento vocale tramite un'API REST. Questa API REST ha un certificato diverso rispetto all'emittente del token, quindi aggiungi il seguente codice al file di intestazione `config.h` per definire questo certificato:

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

1. Aggiungi una costante a questo file per l'URL del servizio vocale senza la posizione. Questo sarà combinato con la posizione e la lingua successivamente per ottenere l'URL completo.

    ```cpp
    const char *SPEECH_URL = "https://%s.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1?language=%s";
    ```

1. Nel file di intestazione `speech_to_text.h`, nella sezione `private` della classe `SpeechToText`, definisci un campo per un WiFi Client utilizzando il certificato del servizio vocale:

    ```cpp
    WiFiClientSecure _speech_client;
    ```

1. Nel metodo `init`, imposta il certificato su questo WiFi Client:

    ```cpp
    _speech_client.setCACert(SPEECH_CERTIFICATE);
    ```

1. Aggiungi il seguente codice alla sezione `public` della classe `SpeechToText` per definire un metodo per convertire la voce in testo:

    ```cpp
    String convertSpeechToText()
    {
        
    }
    ```

1. Aggiungi il seguente codice a questo metodo per creare un client HTTP utilizzando il WiFi Client configurato con il certificato del servizio vocale e utilizzando l'URL del servizio vocale impostato con la posizione e la lingua:

    ```cpp
    char url[128];
    sprintf(url, SPEECH_URL, SPEECH_LOCATION, LANGUAGE);

    HTTPClient httpClient;
    httpClient.begin(_speech_client, url);
    ```

1. Alcune intestazioni devono essere impostate sulla connessione:

    ```cpp
    httpClient.addHeader("Authorization", String("Bearer ") + _access_token);
    httpClient.addHeader("Content-Type", String("audio/wav; codecs=audio/pcm; samplerate=") + String(RATE));
    httpClient.addHeader("Accept", "application/json;text/xml");
    ```

    Questo imposta le intestazioni per l'autorizzazione utilizzando il token di accesso, il formato audio utilizzando la frequenza di campionamento e imposta che il client si aspetta il risultato come JSON.

1. Dopo questo, aggiungi il seguente codice per effettuare la chiamata all'API REST:

    ```cpp
    Serial.println("Sending speech...");

    FlashStream stream;
    int httpResponseCode = httpClient.sendRequest("POST", &stream, BUFFER_SIZE);

    Serial.println("Speech sent!");
    ```

    Questo crea un `FlashStream` e lo utilizza per trasmettere dati all'API REST.

1. Sotto questo, aggiungi il seguente codice:

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

    Questo codice controlla il codice di risposta.

    Se è 200, il codice per il successo, allora il risultato viene recuperato, decodificato da JSON e la proprietà `DisplayText` viene impostata nella variabile `text`. Questa è la proprietà in cui viene restituita la versione testuale della voce.

    Se il codice di risposta è 401, allora il token di accesso è scaduto (questi token durano solo 10 minuti). Viene richiesto un nuovo token di accesso e la chiamata viene effettuata di nuovo.

    Altrimenti, viene inviato un errore al monitor seriale e `text` rimane vuoto.

1. Aggiungi il seguente codice alla fine di questo metodo per chiudere il client HTTP e restituire il testo:

    ```cpp
    httpClient.end();

    return text;
    ```

1. In `main.cpp`, chiama questo nuovo metodo `convertSpeechToText` nella funzione `processAudio`, quindi registra la voce sul monitor seriale:

    ```cpp
    String text = speechToText.convertSpeechToText();
    Serial.println(text);
    ```

1. Compila questo codice, caricalo sul tuo Wio Terminal e testalo attraverso il monitor seriale. Una volta che vedi `Ready` nel monitor seriale, premi il pulsante C (quello sul lato sinistro, più vicino all'interruttore di alimentazione) e parla. Verranno catturati 4 secondi di audio, poi convertiti in testo.

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

> 💁 Puoi trovare questo codice nella cartella [code-speech-to-text/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/wio-terminal).

😀 Il tuo programma di conversione da voce a testo è stato un successo!

**Disclaimer**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di tenere presente che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.