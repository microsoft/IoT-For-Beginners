<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3f92edf2975175577174910caca4a389",
  "translation_date": "2025-08-26T07:25:21+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-speech-to-text.md",
  "language_code": "pl"
}
-->
# Rozpoznawanie mowy na tekst - Wio Terminal

W tej części lekcji napiszesz kod, który przekształci mowę z przechwyconego dźwięku na tekst za pomocą usługi rozpoznawania mowy.

## Wysyłanie dźwięku do usługi rozpoznawania mowy

Dźwięk można przesłać do usługi rozpoznawania mowy za pomocą REST API. Aby korzystać z tej usługi, najpierw musisz uzyskać token dostępu, a następnie użyć go do dostępu do REST API. Tokeny dostępu wygasają po 10 minutach, więc Twój kod powinien regularnie je odświeżać, aby zawsze były aktualne.

### Zadanie - uzyskanie tokenu dostępu

1. Otwórz projekt `smart-timer`, jeśli nie jest jeszcze otwarty.

1. Dodaj następujące zależności bibliotek do pliku `platformio.ini`, aby uzyskać dostęp do WiFi i obsługiwać JSON:

    ```ini
    seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
    seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
    seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    bblanchon/ArduinoJson @ 6.17.3
    ```

1. Dodaj następujący kod do pliku nagłówkowego `config.h`:

    ```cpp
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    
    const char *SPEECH_API_KEY = "<API_KEY>";
    const char *SPEECH_LOCATION = "<LOCATION>";
    const char *LANGUAGE = "<LANGUAGE>";

    const char *TOKEN_URL = "https://%s.api.cognitive.microsoft.com/sts/v1.0/issuetoken";
    ```

    Zamień `<SSID>` i `<PASSWORD>` na odpowiednie wartości dla Twojej sieci WiFi.

    Zamień `<API_KEY>` na klucz API dla Twojego zasobu usługi rozpoznawania mowy. Zamień `<LOCATION>` na lokalizację, którą wybrałeś podczas tworzenia zasobu usługi rozpoznawania mowy.

    Zamień `<LANGUAGE>` na nazwę lokalizacji języka, w którym będziesz mówić, na przykład `en-GB` dla angielskiego lub `zn-HK` dla kantońskiego. Listę obsługiwanych języków i ich nazw lokalizacji znajdziesz w [dokumentacji wsparcia językowego i głosowego na stronie Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    Stała `TOKEN_URL` to adres URL wydawcy tokenów bez lokalizacji. Lokalizacja zostanie dodana później, aby uzyskać pełny adres URL.

1. Podobnie jak w przypadku połączenia z Custom Vision, musisz użyć połączenia HTTPS, aby połączyć się z usługą wydawania tokenów. Na końcu pliku `config.h` dodaj następujący kod:

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

    Jest to ten sam certyfikat, którego używałeś podczas łączenia się z Custom Vision.

1. Dodaj dyrektywę include dla pliku nagłówkowego WiFi oraz pliku nagłówkowego config na początku pliku `main.cpp`:

    ```cpp
    #include <rpcWiFi.h>

    #include "config.h"
    ```

1. Dodaj kod do połączenia z WiFi w pliku `main.cpp` powyżej funkcji `setup`:

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

1. Wywołaj tę funkcję w funkcji `setup` po ustanowieniu połączenia szeregowego:

    ```cpp
    connectWiFi();
    ```

1. Utwórz nowy plik nagłówkowy w folderze `src` o nazwie `speech_to_text.h`. W tym pliku nagłówkowym dodaj następujący kod:

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

    Zawiera to niezbędne pliki nagłówkowe dla połączenia HTTP, konfiguracji oraz plik nagłówkowy `mic.h`, a także definiuje klasę `SpeechToText`, zanim zadeklaruje instancję tej klasy, która będzie używana później.

1. Dodaj następujące dwa pola do sekcji `private` tej klasy:

    ```cpp
    WiFiClientSecure _token_client;
    String _access_token;
    ```

    `_token_client` to klient WiFi używający HTTPS, który będzie używany do uzyskania tokenu dostępu. Token ten zostanie następnie zapisany w `_access_token`.

1. Dodaj następującą metodę do sekcji `private`:

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

    Kod ten buduje adres URL dla API wydawcy tokenów, używając lokalizacji zasobu mowy. Następnie tworzy `HTTPClient`, aby wykonać żądanie sieciowe, konfigurując je do użycia klienta WiFi z certyfikatem punktów końcowych tokenów. Ustawia klucz API jako nagłówek dla wywołania. Następnie wykonuje żądanie POST, aby uzyskać certyfikat, ponawiając próbę w przypadku błędów. Na końcu zwracany jest token dostępu.

1. W sekcji `public` dodaj metodę do uzyskania tokenu dostępu. Będzie ona potrzebna w późniejszych lekcjach do konwersji tekstu na mowę.

    ```cpp
    String AccessToken()
    {
        return _access_token;
    }
    ```

1. W sekcji `public` dodaj metodę `init`, która konfiguruje klienta tokenów:

    ```cpp
    void init()
    {
        _token_client.setCACert(TOKEN_CERTIFICATE);
        _access_token = getAccessToken();
    }
    ```

    Ustawia to certyfikat na kliencie WiFi, a następnie uzyskuje token dostępu.

1. W pliku `main.cpp` dodaj ten nowy plik nagłówkowy do dyrektyw include:

    ```cpp
    #include "speech_to_text.h"
    ```

1. Zainicjalizuj klasę `SpeechToText` na końcu funkcji `setup`, po wywołaniu `mic.init`, ale przed zapisaniem `Ready` do monitora szeregowego:

    ```cpp
    speechToText.init();
    ```

### Zadanie - odczyt dźwięku z pamięci flash

1. W wcześniejszej części tej lekcji dźwięk został nagrany do pamięci flash. Ten dźwięk będzie musiał zostać przesłany do REST API usługi rozpoznawania mowy, więc musi zostać odczytany z pamięci flash. Nie można go załadować do bufora w pamięci, ponieważ byłby zbyt duży. Klasa `HTTPClient`, która wykonuje wywołania REST, może przesyłać dane za pomocą strumienia Arduino - klasy, która może ładować dane w małych kawałkach, przesyłając je jeden po drugim jako część żądania. Za każdym razem, gdy wywołasz `read` na strumieniu, zwraca on następny blok danych. Można utworzyć strumień Arduino, który będzie odczytywał dane z pamięci flash. Utwórz nowy plik o nazwie `flash_stream.h` w folderze `src` i dodaj do niego następujący kod:

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

    Deklaruje to klasę `FlashStream`, dziedziczącą po klasie `Stream` Arduino. Jest to klasa abstrakcyjna - klasy pochodne muszą zaimplementować kilka metod, zanim klasa będzie mogła zostać zainicjalizowana, a te metody są zdefiniowane w tej klasie.

    ✅ Więcej o strumieniach Arduino przeczytasz w [dokumentacji Arduino Stream](https://www.arduino.cc/reference/en/language/functions/communication/stream/)

1. Dodaj następujące pola do sekcji `private`:

    ```cpp
    size_t _pos;
    size_t _flash_address;
    const sfud_flash *_flash;

    byte _buffer[HTTP_TCP_BUFFER_SIZE];
    ```

    Definiuje to tymczasowy bufor do przechowywania danych odczytanych z pamięci flash, wraz z polami do przechowywania bieżącej pozycji podczas odczytu z bufora, bieżącego adresu do odczytu z pamięci flash oraz urządzenia pamięci flash.

1. W sekcji `private` dodaj następującą metodę:

    ```cpp
    void populateBuffer()
    {
        sfud_read(_flash, _flash_address, HTTP_TCP_BUFFER_SIZE, _buffer);
        _flash_address += HTTP_TCP_BUFFER_SIZE;
        _pos = 0;
    }
    ```

    Kod ten odczytuje dane z pamięci flash pod bieżącym adresem i zapisuje je w buforze. Następnie zwiększa adres, aby kolejne wywołanie odczytało następny blok pamięci. Bufor jest rozmiarowany na podstawie największego kawałka, który `HTTPClient` wyśle do REST API jednorazowo.

    > 💁 Wymazywanie pamięci flash musi być wykonywane przy użyciu rozmiaru ziarna, natomiast odczyt nie.

1. W sekcji `public` tej klasy dodaj konstruktor:

    ```cpp
    FlashStream()
    {
        _pos = 0;
        _flash_address = 0;
        _flash = sfud_get_device_table() + 0;
        
        populateBuffer();
    }
    ```

    Konstruktor ten ustawia wszystkie pola, aby rozpocząć odczyt od początku bloku pamięci flash, i ładuje pierwszy kawałek danych do bufora.

1. Zaimplementuj metodę `write`. Ten strumień będzie tylko odczytywał dane, więc może nic nie robić i zwracać 0:

    ```cpp
    virtual size_t write(uint8_t val)
    {
        return 0;
    }
    ```

1. Zaimplementuj metodę `peek`. Zwraca ona dane w bieżącej pozycji bez przesuwania strumienia. Wywołanie `peek` wielokrotnie zawsze zwróci te same dane, o ile żadne dane nie zostaną odczytane ze strumienia.

    ```cpp
    virtual int peek()
    {
        return _buffer[_pos];
    }
    ```

1. Zaimplementuj funkcję `available`. Zwraca ona, ile bajtów można odczytać ze strumienia, lub -1, jeśli strumień jest zakończony. W tej klasie maksymalna dostępna ilość danych nie będzie większa niż rozmiar kawałka klienta HTTP. Gdy ten strumień jest używany w kliencie HTTP, wywołuje on tę funkcję, aby sprawdzić, ile danych jest dostępnych, a następnie żąda tej ilości danych do wysłania do REST API. Nie chcemy, aby każdy kawałek był większy niż rozmiar kawałka klienta HTTP, więc jeśli dostępne jest więcej, zwracany jest rozmiar kawałka. Jeśli mniej, zwracana jest dostępna ilość. Po przesłaniu wszystkich danych zwracane jest -1.

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

1. Zaimplementuj metodę `read`, aby zwrócić następny bajt z bufora, zwiększając pozycję. Jeśli pozycja przekroczy rozmiar bufora, bufor zostaje wypełniony następnym blokiem z pamięci flash, a pozycja zostaje zresetowana.

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

1. W pliku nagłówkowym `speech_to_text.h` dodaj dyrektywę include dla tego nowego pliku nagłówkowego:

    ```cpp
    #include "flash_stream.h"
    ```

### Zadanie - konwersja mowy na tekst

1. Mowę można przekształcić na tekst, przesyłając dźwięk do usługi rozpoznawania mowy za pomocą REST API. REST API ma inny certyfikat niż wydawca tokenów, więc dodaj następujący kod do pliku nagłówkowego `config.h`, aby zdefiniować ten certyfikat:

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

1. Dodaj stałą do tego pliku dla adresu URL usługi mowy bez lokalizacji. Lokalizacja i język zostaną dodane później, aby uzyskać pełny adres URL.

    ```cpp
    const char *SPEECH_URL = "https://%s.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1?language=%s";
    ```

1. W pliku nagłówkowym `speech_to_text.h`, w sekcji `private` klasy `SpeechToText`, zdefiniuj pole dla klienta WiFi używającego certyfikatu usługi mowy:

    ```cpp
    WiFiClientSecure _speech_client;
    ```

1. W metodzie `init` ustaw certyfikat na tym kliencie WiFi:

    ```cpp
    _speech_client.setCACert(SPEECH_CERTIFICATE);
    ```

1. Dodaj następujący kod do sekcji `public` klasy `SpeechToText`, aby zdefiniować metodę konwersji mowy na tekst:

    ```cpp
    String convertSpeechToText()
    {
        
    }
    ```

1. Dodaj następujący kod do tej metody, aby utworzyć klienta HTTP używającego klienta WiFi skonfigurowanego z certyfikatem usługi mowy oraz używającego adresu URL usługi mowy ustawionego z lokalizacją i językiem:

    ```cpp
    char url[128];
    sprintf(url, SPEECH_URL, SPEECH_LOCATION, LANGUAGE);

    HTTPClient httpClient;
    httpClient.begin(_speech_client, url);
    ```

1. Na połączeniu należy ustawić kilka nagłówków:

    ```cpp
    httpClient.addHeader("Authorization", String("Bearer ") + _access_token);
    httpClient.addHeader("Content-Type", String("audio/wav; codecs=audio/pcm; samplerate=") + String(RATE));
    httpClient.addHeader("Accept", "application/json;text/xml");
    ```

    Ustawia to nagłówki dla autoryzacji za pomocą tokenu dostępu, formatu audio za pomocą częstotliwości próbkowania oraz ustawia, że klient oczekuje wyniku w formacie JSON.

1. Po tym dodaj następujący kod, aby wykonać wywołanie REST API:

    ```cpp
    Serial.println("Sending speech...");

    FlashStream stream;
    int httpResponseCode = httpClient.sendRequest("POST", &stream, BUFFER_SIZE);

    Serial.println("Speech sent!");
    ```

    Tworzy to `FlashStream` i używa go do przesyłania danych do REST API.

1. Poniżej tego dodaj następujący kod:

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

    Kod ten sprawdza kod odpowiedzi.

    Jeśli jest to 200, kod dla sukcesu, wynik jest pobierany, dekodowany z JSON, a właściwość `DisplayText` jest ustawiana w zmiennej `text`. Jest to właściwość, w której zwracana jest tekstowa wersja mowy.

    Jeśli kod odpowiedzi to 401, token dostępu wygasł (te tokeny są ważne tylko przez 10 minut). Żądany jest nowy token dostępu, a wywołanie jest wykonywane ponownie.

    W przeciwnym razie błąd jest wysyłany do monitora szeregowego, a `text` pozostaje pusty.

1. Dodaj następujący kod na końcu tej metody, aby zamknąć klienta HTTP i zwrócić tekst:

    ```cpp
    httpClient.end();

    return text;
    ```

1. W pliku `main.cpp` wywołaj nową metodę `convertSpeechToText` w funkcji `processAudio`, a następnie zaloguj mowę do monitora szeregowego:

    ```cpp
    String text = speechToText.convertSpeechToText();
    Serial.println(text);
    ```

1. Zbuduj ten kod, wgraj go na swój Wio Terminal i przetestuj przez monitor szeregowy. Gdy zobaczysz `Ready` w monitorze szeregowym, naciśnij przycisk C (ten po lewej stronie, najbliżej przełącznika zasilania) i mów. 4 sekundy dźwięku zostaną przechwycone, a następnie przekształcone na tekst.

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

> 💁 Kod ten znajdziesz w folderze [code-speech-to-text/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/wio-terminal).

😀 Twój program rozpoznawania mowy na tekst zakończył się sukcesem!

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby zapewnić poprawność tłumaczenia, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za autorytatywne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z korzystania z tego tłumaczenia.