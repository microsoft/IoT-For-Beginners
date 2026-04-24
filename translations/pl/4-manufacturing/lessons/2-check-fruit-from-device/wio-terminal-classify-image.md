# Klasyfikacja obrazu - Wio Terminal

W tej części lekcji wyślesz obraz uchwycony przez kamerę do usługi Custom Vision, aby go sklasyfikować.

## Klasyfikacja obrazu

Usługa Custom Vision udostępnia interfejs REST API, który można wywołać z poziomu Wio Terminal, aby klasyfikować obrazy. Ten interfejs REST API jest dostępny przez połączenie HTTPS - bezpieczne połączenie HTTP.

Podczas korzystania z punktów końcowych HTTPS, kod klienta musi zażądać certyfikatu klucza publicznego od serwera, z którym się łączy, i użyć go do szyfrowania przesyłanych danych. Twoja przeglądarka internetowa robi to automatycznie, ale mikrokontrolery tego nie robią. Musisz ręcznie zażądać tego certyfikatu i użyć go do utworzenia bezpiecznego połączenia z REST API. Certyfikaty te nie zmieniają się, więc po ich uzyskaniu można je zakodować na stałe w aplikacji.

Certyfikaty te zawierają klucze publiczne i nie muszą być przechowywane w sposób bezpieczny. Możesz ich używać w swoim kodzie źródłowym i udostępniać je publicznie, na przykład na GitHubie.

### Zadanie - konfiguracja klienta SSL

1. Otwórz projekt aplikacji `fruit-quality-detector`, jeśli nie jest jeszcze otwarty.

1. Otwórz plik nagłówkowy `config.h` i dodaj następujący kod:

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

    Jest to *Microsoft Azure DigiCert Global Root G2 certificate* - jeden z certyfikatów używanych globalnie przez wiele usług Azure.

    > 💁 Aby zobaczyć, że jest to właściwy certyfikat, uruchom następujące polecenie na macOS lub Linux. Jeśli używasz systemu Windows, możesz uruchomić to polecenie za pomocą [Windows Subsystem for Linux (WSL)](https://docs.microsoft.com/windows/wsl/?WT.mc_id=academic-17441-jabenn):
    >
    > ```sh
    > openssl s_client -showcerts -verify 5 -connect api.cognitive.microsoft.com:443
    > ```
    >
    > Wynik wyświetli certyfikat DigiCert Global Root G2.

1. Otwórz `main.cpp` i dodaj następującą dyrektywę include:

    ```cpp
    #include <WiFiClientSecure.h>
    ```

1. Poniżej dyrektyw include zadeklaruj instancję `WifiClientSecure`:

    ```cpp
    WiFiClientSecure client;
    ```

    Ta klasa zawiera kod do komunikacji z punktami końcowymi sieciowymi przez HTTPS.

1. W metodzie `connectWiFi` ustaw `WiFiClientSecure`, aby używał certyfikatu DigiCert Global Root G2:

    ```cpp
    client.setCACert(CERTIFICATE);
    ```

### Zadanie - klasyfikacja obrazu

1. Dodaj następującą linię do listy `lib_deps` w pliku `platformio.ini`:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    Importuje to bibliotekę [ArduinoJson](https://arduinojson.org), bibliotekę JSON dla Arduino, która będzie używana do dekodowania odpowiedzi JSON z REST API.

1. W pliku `config.h` dodaj stałe dla adresu URL predykcji i klucza z usługi Custom Vision:

    ```cpp
    const char *PREDICTION_URL = "<PREDICTION_URL>";
    const char *PREDICTION_KEY = "<PREDICTION_KEY>";
    ```

    Zamień `<PREDICTION_URL>` na adres URL predykcji z Custom Vision. Zamień `<PREDICTION_KEY>` na klucz predykcji.

1. W pliku `main.cpp` dodaj dyrektywę include dla biblioteki ArduinoJson:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. Dodaj następującą funkcję do `main.cpp`, powyżej funkcji `buttonPressed`.

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

    Kod zaczyna się od zadeklarowania `HTTPClient` - klasy zawierającej metody do interakcji z REST API. Następnie łączy klienta z adresem URL predykcji za pomocą instancji `WiFiClientSecure`, która została skonfigurowana z kluczem publicznym Azure.

    Po nawiązaniu połączenia wysyłane są nagłówki - informacje o nadchodzącym żądaniu do REST API. Nagłówek `Content-Type` wskazuje, że wywołanie API wyśle surowe dane binarne, a nagłówek `Prediction-Key` przekazuje klucz predykcji Custom Vision.

    Następnie do klienta HTTP wysyłane jest żądanie POST, przesyłające tablicę bajtów. Tablica ta zawiera obraz JPEG uchwycony przez kamerę w momencie wywołania tej funkcji.

    > 💁 Żądania POST służą do przesyłania danych i uzyskiwania odpowiedzi. Istnieją inne typy żądań, takie jak żądania GET, które służą do pobierania danych. Żądania GET są używane przez przeglądarki internetowe do ładowania stron internetowych.

    Żądanie POST zwraca kod statusu odpowiedzi. Są to dobrze zdefiniowane wartości, gdzie 200 oznacza **OK** - żądanie POST zakończyło się sukcesem.

    > 💁 Wszystkie kody statusu odpowiedzi można znaleźć na stronie [List of HTTP status codes na Wikipedii](https://wikipedia.org/wiki/List_of_HTTP_status_codes)

    Jeśli zwrócony zostanie kod 200, wynik jest odczytywany z klienta HTTP. Jest to odpowiedź tekstowa z REST API zawierająca wyniki predykcji w formacie JSON. JSON ma następujący format:

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

    Najważniejszą częścią jest tablica `predictions`. Zawiera ona predykcje, z jednym wpisem dla każdej etykiety, zawierającym nazwę etykiety i prawdopodobieństwo. Zwracane prawdopodobieństwa to liczby zmiennoprzecinkowe od 0 do 1, gdzie 0 oznacza 0% szans na dopasowanie do etykiety, a 1 oznacza 100% szans.

    > 💁 Klasyfikatory obrazów zwracają procenty dla wszystkich użytych etykiet. Każda etykieta będzie miała prawdopodobieństwo, że obraz pasuje do tej etykiety.

    JSON jest dekodowany, a prawdopodobieństwa dla każdej etykiety są wysyłane do monitora szeregowego.

1. W funkcji `buttonPressed` zastąp kod zapisujący na kartę SD wywołaniem `classifyImage`, lub dodaj go po zapisaniu obrazu, ale **przed** usunięciem bufora:

    ```cpp
    classifyImage(buffer, length);
    ```

    > 💁 Jeśli zastąpisz kod zapisujący na kartę SD, możesz wyczyścić swój kod, usuwając funkcje `setupSDCard` i `saveToSDCard`.

1. Wgraj i uruchom swój kod. Skieruj kamerę na jakiś owoc i naciśnij przycisk C. Zobaczysz wynik w monitorze szeregowym:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

    Będziesz mógł zobaczyć obraz, który został zrobiony, oraz te wartości na karcie **Predictions** w Custom Vision.

    ![Banana w Custom Vision przewidziany jako dojrzały w 56,8% i niedojrzały w 43,1%](../../../../../translated_images/pl/custom-vision-banana-prediction.30cdff4e1d72db5d.webp)

> 💁 Kod ten znajdziesz w folderze [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/wio-terminal).

😀 Twój program klasyfikujący jakość owoców zakończył się sukcesem!

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby tłumaczenie było precyzyjne, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za autorytatywne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.