<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "32a1f23e7834fbe7715da8c4ebb450b9",
  "translation_date": "2025-08-25T16:32:10+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-classify-image.md",
  "language_code": "it"
}
-->
# Classificare un'immagine - Wio Terminal

In questa parte della lezione, invierai l'immagine catturata dalla fotocamera al servizio Custom Vision per classificarla.

## Classificare un'immagine

Il servizio Custom Vision dispone di un'API REST che puoi chiamare dal Wio Terminal per classificare le immagini. Questa API REST è accessibile tramite una connessione HTTPS - una connessione HTTP sicura.

Quando interagisci con endpoint HTTPS, il codice client deve richiedere il certificato della chiave pubblica dal server a cui si sta accedendo e utilizzarlo per crittografare il traffico inviato. Il tuo browser web lo fa automaticamente, ma i microcontrollori no. Dovrai richiedere manualmente questo certificato e usarlo per creare una connessione sicura all'API REST. Questi certificati non cambiano, quindi una volta ottenuto un certificato, può essere codificato direttamente nella tua applicazione.

Questi certificati contengono chiavi pubbliche e non devono essere mantenuti segreti. Puoi usarli nel tuo codice sorgente e condividerli pubblicamente su piattaforme come GitHub.

### Attività - configurare un client SSL

1. Apri il progetto dell'app `fruit-quality-detector` se non è già aperto.

1. Apri il file di intestazione `config.h` e aggiungi quanto segue:

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

    Questo è il *Microsoft Azure DigiCert Global Root G2 certificate* - uno dei certificati utilizzati da molti servizi Azure a livello globale.

    > 💁 Per verificare che questo sia il certificato da utilizzare, esegui il seguente comando su macOS o Linux. Se stai usando Windows, puoi eseguire questo comando utilizzando il [Windows Subsystem for Linux (WSL)](https://docs.microsoft.com/windows/wsl/?WT.mc_id=academic-17441-jabenn):
    >
    > ```sh
    > openssl s_client -showcerts -verify 5 -connect api.cognitive.microsoft.com:443
    > ```
    >
    > L'output elencherà il certificato DigiCert Global Root G2.

1. Apri `main.cpp` e aggiungi la seguente direttiva di inclusione:

    ```cpp
    #include <WiFiClientSecure.h>
    ```

1. Sotto le direttive di inclusione, dichiara un'istanza di `WifiClientSecure`:

    ```cpp
    WiFiClientSecure client;
    ```

    Questa classe contiene il codice per comunicare con gli endpoint web tramite HTTPS.

1. Nel metodo `connectWiFi`, configura il WiFiClientSecure per utilizzare il certificato DigiCert Global Root G2:

    ```cpp
    client.setCACert(CERTIFICATE);
    ```

### Attività - classificare un'immagine

1. Aggiungi la seguente riga aggiuntiva alla lista `lib_deps` nel file `platformio.ini`:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    Questo importa [ArduinoJson](https://arduinojson.org), una libreria JSON per Arduino, che verrà utilizzata per decodificare la risposta JSON dall'API REST.

1. In `config.h`, aggiungi costanti per l'URL di previsione e la chiave del servizio Custom Vision:

    ```cpp
    const char *PREDICTION_URL = "<PREDICTION_URL>";
    const char *PREDICTION_KEY = "<PREDICTION_KEY>";
    ```

    Sostituisci `<PREDICTION_URL>` con l'URL di previsione di Custom Vision. Sostituisci `<PREDICTION_KEY>` con la chiave di previsione.

1. In `main.cpp`, aggiungi una direttiva di inclusione per la libreria ArduinoJson:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. Aggiungi la seguente funzione a `main.cpp`, sopra la funzione `buttonPressed`.

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

    Questo codice inizia dichiarando un `HTTPClient` - una classe che contiene metodi per interagire con le API REST. Successivamente, collega il client all'URL di previsione utilizzando l'istanza `WiFiClientSecure` configurata con la chiave pubblica di Azure.

    Una volta connesso, invia gli header - informazioni sulla richiesta che verrà effettuata contro l'API REST. L'header `Content-Type` indica che la chiamata API invierà dati binari grezzi, mentre l'header `Prediction-Key` passa la chiave di previsione di Custom Vision.

    Successivamente, viene effettuata una richiesta POST al client HTTP, caricando un array di byte. Questo conterrà l'immagine JPEG catturata dalla fotocamera quando questa funzione viene chiamata.

    > 💁 Le richieste POST servono per inviare dati e ottenere una risposta. Esistono altri tipi di richieste, come le richieste GET, che recuperano dati. Le richieste GET vengono utilizzate dal tuo browser web per caricare pagine web.

    La richiesta POST restituisce un codice di stato della risposta. Questi sono valori ben definiti, con 200 che significa **OK** - la richiesta POST è stata completata con successo.

    > 💁 Puoi vedere tutti i codici di stato della risposta nella [pagina Lista dei codici di stato HTTP su Wikipedia](https://wikipedia.org/wiki/List_of_HTTP_status_codes)

    Se viene restituito un 200, il risultato viene letto dal client HTTP. Questa è una risposta testuale dall'API REST con i risultati della previsione come documento JSON. Il JSON ha il seguente formato:

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

    La parte importante qui è l'array `predictions`. Questo contiene le previsioni, con una voce per ogni tag che include il nome del tag e la probabilità. Le probabilità restituite sono numeri in virgola mobile da 0 a 1, con 0 che rappresenta una probabilità dello 0% di corrispondenza con il tag e 1 che rappresenta una probabilità del 100%.

    > 💁 I classificatori di immagini restituiscono le percentuali per tutti i tag utilizzati. Ogni tag avrà una probabilità che l'immagine corrisponda a quel tag.

    Questo JSON viene decodificato e le probabilità per ogni tag vengono inviate al monitor seriale.

1. Nella funzione `buttonPressed`, sostituisci il codice che salva sulla scheda SD con una chiamata a `classifyImage`, oppure aggiungilo dopo che l'immagine è stata scritta, ma **prima** che il buffer venga eliminato:

    ```cpp
    classifyImage(buffer, length);
    ```

    > 💁 Se sostituisci il codice che salva sulla scheda SD, puoi semplificare il tuo codice rimuovendo le funzioni `setupSDCard` e `saveToSDCard`.

1. Carica ed esegui il tuo codice. Punta la fotocamera verso della frutta e premi il pulsante C. Vedrai l'output nel monitor seriale:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

    Sarai in grado di vedere l'immagine catturata e questi valori nella scheda **Predictions** in Custom Vision.

    ![Una banana in Custom Vision prevista matura al 56.8% e acerba al 43.1%](../../../../../translated_images/it/custom-vision-banana-prediction.30cdff4e1d72db5d9a0be0193790a47c2b387da034e12dc1314dd57ca2131b59.png)

> 💁 Puoi trovare questo codice nella cartella [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/wio-terminal).

😀 Il tuo programma per classificare la qualità della frutta è stato un successo!

**Disclaimer**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.