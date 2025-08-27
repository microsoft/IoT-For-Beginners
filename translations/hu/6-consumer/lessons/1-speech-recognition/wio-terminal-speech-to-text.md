<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3f92edf2975175577174910caca4a389",
  "translation_date": "2025-08-27T21:28:27+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-speech-to-text.md",
  "language_code": "hu"
}
-->
# Beszéd szöveggé alakítása - Wio Terminal

Ebben a lecke részben kódot fogsz írni, amely a rögzített hangban lévő beszédet szöveggé alakítja a beszédfelismerő szolgáltatás segítségével.

## Küldd el a hangot a beszédfelismerő szolgáltatásnak

A hangot a REST API segítségével lehet elküldeni a beszédfelismerő szolgáltatásnak. A szolgáltatás használatához először hozzáférési tokent kell kérned, majd ezt a tokent használva érheted el a REST API-t. Ezek a hozzáférési tokenek 10 perc után lejárnak, ezért a kódodnak rendszeresen új tokent kell kérnie, hogy mindig naprakész legyen.

### Feladat - hozzáférési token kérése

1. Nyisd meg a `smart-timer` projektet, ha még nincs megnyitva.

1. Add hozzá a következő könyvtárfüggőségeket a `platformio.ini` fájlhoz a WiFi eléréséhez és a JSON kezeléséhez:

    ```ini
    seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
    seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
    seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    bblanchon/ArduinoJson @ 6.17.3
    ```

1. Add hozzá a következő kódot a `config.h` fejlécfájlhoz:

    ```cpp
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    
    const char *SPEECH_API_KEY = "<API_KEY>";
    const char *SPEECH_LOCATION = "<LOCATION>";
    const char *LANGUAGE = "<LANGUAGE>";

    const char *TOKEN_URL = "https://%s.api.cognitive.microsoft.com/sts/v1.0/issuetoken";
    ```

    Cseréld ki a `<SSID>` és `<PASSWORD>` helyére a WiFi-hez tartozó megfelelő értékeket.

    Cseréld ki az `<API_KEY>` helyére a beszédfelismerő szolgáltatás erőforrásának API kulcsát. Az `<LOCATION>` helyére pedig azt a helyet, amelyet a beszédfelismerő szolgáltatás erőforrás létrehozásakor használtál.

    Az `<LANGUAGE>` helyére add meg annak a nyelvnek a helyi beállítását, amelyen beszélni fogsz, például `en-GB` angolhoz vagy `zn-HK` kantonihoz. A támogatott nyelvek és helyi beállítások listáját megtalálod a [Microsoft dokumentációjában a nyelv- és hangtámogatásról](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    A `TOKEN_URL` konstans a token kiadó URL-je hely nélkül. Ezt később kombináljuk a helyszínnel, hogy megkapjuk a teljes URL-t.

1. Ahogy a Custom Vision-hoz való csatlakozásnál, itt is HTTPS kapcsolatot kell használnod a token kiadó szolgáltatáshoz való csatlakozáshoz. Add hozzá a következő kódot a `config.h` végéhez:

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

    Ez ugyanaz a tanúsítvány, amelyet a Custom Vision-hoz való csatlakozáskor használtál.

1. Add hozzá a WiFi fejlécfájl és a config fejlécfájl beillesztését a `main.cpp` fájl tetejéhez:

    ```cpp
    #include <rpcWiFi.h>

    #include "config.h"
    ```

1. Adj hozzá kódot a WiFi-hez való csatlakozáshoz a `main.cpp` fájlban a `setup` függvény fölé:

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

1. Hívd meg ezt a függvényt a `setup` függvényben, miután a soros kapcsolat létrejött:

    ```cpp
    connectWiFi();
    ```

1. Hozz létre egy új fejlécfájlt a `src` mappában `speech_to_text.h` néven. Ebben a fejlécfájlban add hozzá a következő kódot:

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

    Ez tartalmazza a szükséges fejlécfájlokat egy HTTP kapcsolat létrehozásához, a konfigurációt és a `mic.h` fejlécfájlt, valamint definiál egy `SpeechToText` nevű osztályt, mielőtt deklarálná az osztály egy példányát, amelyet később használhatsz.

1. Add hozzá a következő két mezőt az osztály `private` szekciójához:

    ```cpp
    WiFiClientSecure _token_client;
    String _access_token;
    ```

    Az `_token_client` egy WiFi kliens, amely HTTPS-t használ, és a hozzáférési token megszerzésére szolgál. Ez a token azután az `_access_token` mezőben lesz tárolva.

1. Add hozzá a következő metódust az osztály `private` szekciójához:

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

    Ez a kód összeállítja a token kiadó API URL-jét a beszéderőforrás helyének felhasználásával. Ezután létrehoz egy `HTTPClient`-et a webkéréshez, amelyet úgy állít be, hogy a WiFi klienssel használja a token végpont tanúsítványát. Az API kulcsot fejlécben állítja be a híváshoz. Ezután POST kérést küld a tanúsítvány megszerzéséhez, és hiba esetén újrapróbálkozik. Végül visszaadja a hozzáférési tokent.

1. Add hozzá a következő metódust az osztály `public` szekciójához a hozzáférési token megszerzéséhez. Erre a későbbi leckékben lesz szükség a szöveg beszéddé alakításához.

    ```cpp
    String AccessToken()
    {
        return _access_token;
    }
    ```

1. Add hozzá az `init` metódust az osztály `public` szekciójához, amely beállítja a token klienst:

    ```cpp
    void init()
    {
        _token_client.setCACert(TOKEN_CERTIFICATE);
        _access_token = getAccessToken();
    }
    ```

    Ez beállítja a tanúsítványt a WiFi kliensen, majd megszerzi a hozzáférési tokent.

1. A `main.cpp` fájlban add hozzá ezt az új fejlécfájlt a beillesztési direktívákhoz:

    ```cpp
    #include "speech_to_text.h"
    ```

1. Inicializáld a `SpeechToText` osztályt a `setup` függvény végén, a `mic.init` hívás után, de mielőtt a `Ready` kiírásra kerülne a soros monitorra:

    ```cpp
    speechToText.init();
    ```

### Feladat - hang olvasása a flash memóriából

1. A lecke korábbi részében a hangot a flash memóriába rögzítetted. Ezt a hangot el kell küldeni a Beszédfelismerő REST API-nak, ezért ki kell olvasni a flash memóriából. Nem lehet egy memóriapufferbe betölteni, mert túl nagy lenne. Az `HTTPClient` osztály, amely REST hívásokat végez, képes adatokat streamelni egy Arduino Stream segítségével - egy olyan osztály, amely kis darabokban tud adatokat betölteni, és ezeket a darabokat egyenként küldi el a kérés részeként. Minden alkalommal, amikor meghívod a `read` metódust egy streamen, az visszaadja a következő adatblokkot. Egy Arduino stream hozható létre, amely képes olvasni a flash memóriából. Hozz létre egy új fájlt `flash_stream.h` néven a `src` mappában, és add hozzá a következő kódot:

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

    Ez deklarálja a `FlashStream` osztályt, amely az Arduino `Stream` osztályából származik. Ez egy absztrakt osztály - a származtatott osztályoknak néhány metódust implementálniuk kell, mielőtt az osztály példányosítható lenne, és ezek a metódusok ebben az osztályban vannak definiálva.

    ✅ További információ az Arduino Streamekről az [Arduino Stream dokumentációjában](https://www.arduino.cc/reference/en/language/functions/communication/stream/)

1. Add hozzá a következő mezőket az osztály `private` szekciójához:

    ```cpp
    size_t _pos;
    size_t _flash_address;
    const sfud_flash *_flash;

    byte _buffer[HTTP_TCP_BUFFER_SIZE];
    ```

    Ez definiál egy ideiglenes puffert az adatok tárolására, amelyeket a flash memóriából olvasott ki, valamint mezőket a jelenlegi pozíció tárolására az olvasás során, a flash memória aktuális címére, és a flash memória eszközére.

1. Az osztály `private` szekciójában add hozzá a következő metódust:

    ```cpp
    void populateBuffer()
    {
        sfud_read(_flash, _flash_address, HTTP_TCP_BUFFER_SIZE, _buffer);
        _flash_address += HTTP_TCP_BUFFER_SIZE;
        _pos = 0;
    }
    ```

    Ez a kód a flash memória aktuális címéről olvas, és az adatokat egy pufferbe tárolja. Ezután növeli a címet, így a következő hívás a memória következő blokkját olvassa. A puffer mérete az alapján van meghatározva, hogy mekkora a legnagyobb darab, amelyet az `HTTPClient` egyszerre küldhet a REST API-nak.

    > 💁 A flash memória törlését a szemcseméret alapján kell elvégezni, az olvasás viszont nem.

1. Az osztály `public` szekciójában adj hozzá egy konstruktort:

    ```cpp
    FlashStream()
    {
        _pos = 0;
        _flash_address = 0;
        _flash = sfud_get_device_table() + 0;
        
        populateBuffer();
    }
    ```

    Ez a konstruktor beállítja az összes mezőt, hogy a flash memória blokk elejéről kezdjen olvasni, és betölti az első adatblokkot a pufferbe.

1. Implementáld a `write` metódust. Ez a stream csak adatokat olvas, így ez nem csinál semmit, és 0-t ad vissza:

    ```cpp
    virtual size_t write(uint8_t val)
    {
        return 0;
    }
    ```

1. Implementáld a `peek` metódust. Ez visszaadja az aktuális pozíción lévő adatot anélkül, hogy a stream előrehaladna. A `peek` többszöri meghívása mindig ugyanazt az adatot adja vissza, amíg nem olvasol adatot a streamből.

    ```cpp
    virtual int peek()
    {
        return _buffer[_pos];
    }
    ```

1. Implementáld az `available` függvényt. Ez visszaadja, hogy hány bájt olvasható a streamből, vagy -1-et, ha a stream véget ért. Ebben az osztályban a maximálisan elérhető adat nem lehet nagyobb, mint az `HTTPClient` darabmérete. Ha több adat érhető el, mint a darabméret, akkor a darabméretet adja vissza. Ha kevesebb, akkor az elérhető adatot adja vissza. Ha az összes adatot streamelték, -1-et ad vissza.

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

1. Implementáld a `read` metódust, hogy visszaadja a következő bájtot a pufferből, növelve a pozíciót. Ha a pozíció meghaladja a puffer méretét, betölti a következő blokkot a flash memóriából a pufferbe, és visszaállítja a pozíciót.

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

1. A `speech_to_text.h` fejlécfájlban adj hozzá egy beillesztési direktívát ehhez az új fejlécfájlhoz:

    ```cpp
    #include "flash_stream.h"
    ```

### Feladat - a beszéd szöveggé alakítása

1. A beszéd szöveggé alakítható, ha a hangot elküldöd a Beszédfelismerő REST API-nak. Ez a REST API más tanúsítványt használ, mint a token kiadó, ezért add hozzá a következő kódot a `config.h` fejlécfájlhoz, hogy definiáld ezt a tanúsítványt:

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

1. Adj hozzá egy konstansot ehhez a fájlhoz a beszéd URL-jéhez hely nélkül. Ezt később kombináljuk a helyszínnel és a nyelvvel, hogy megkapjuk a teljes URL-t.

    ```cpp
    const char *SPEECH_URL = "https://%s.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1?language=%s";
    ```

1. A `speech_to_text.h` fejlécfájlban, a `SpeechToText` osztály `private` szekciójában definiálj egy mezőt egy WiFi klienshez, amely a beszéd tanúsítványt használja:

    ```cpp
    WiFiClientSecure _speech_client;
    ```

1. Az `init` metódusban állítsd be a tanúsítványt ezen a WiFi kliensen:

    ```cpp
    _speech_client.setCACert(SPEECH_CERTIFICATE);
    ```

1. Add hozzá a következő kódot a `SpeechToText` osztály `public` szekciójához, hogy definiálj egy metódust a beszéd szöveggé alakításához:

    ```cpp
    String convertSpeechToText()
    {
        
    }
    ```

1. Add hozzá a következő kódot ehhez a metódushoz, hogy létrehozz egy HTTP klienst a beszéd tanúsítvánnyal konfigurált WiFi klienssel, és a beszéd URL-jével, amely a helyszínnel és a nyelvvel van beállítva:

    ```cpp
    char url[128];
    sprintf(url, SPEECH_URL, SPEECH_LOCATION, LANGUAGE);

    HTTPClient httpClient;
    httpClient.begin(_speech_client, url);
    ```

1. Néhány fejlécet be kell állítani a kapcsolaton:

    ```cpp
    httpClient.addHeader("Authorization", String("Bearer ") + _access_token);
    httpClient.addHeader("Content-Type", String("audio/wav; codecs=audio/pcm; samplerate=") + String(RATE));
    httpClient.addHeader("Accept", "application/json;text/xml");
    ```

    Ez beállítja a fejlécet az engedélyezéshez a hozzáférési tokennel, az audio formátumhoz a mintavételi frekvenciával, és azt, hogy az ügyfél JSON formátumban várja az eredményt.

1. Ezután add hozzá a következő kódot a REST API hívás végrehajtásához:

    ```cpp
    Serial.println("Sending speech...");

    FlashStream stream;
    int httpResponseCode = httpClient.sendRequest("POST", &stream, BUFFER_SIZE);

    Serial.println("Speech sent!");
    ```

    Ez létrehoz egy `FlashStream`-et, és ezt használja az adatok streamelésére a REST API-nak.

1. Ezután add hozzá a következő kódot:

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

    Ez a kód ellenőrzi a válaszkódot.

    Ha 200, ami a siker kódja, akkor az eredményt lekéri, JSON-ból dekódolja, és a `DisplayText` tulajdonságot beállítja a `text` változóba. Ez az a tulajdonság, amelyben a beszéd szöveges változata visszatér.

    Ha a válaszkód 401, akkor a hozzáférési token lejárt (ezek a tokenek csak 10 percig érvényesek). Új hozzáférési tokent kér, és újra végrehajtja a hívást.

    Egyébként hibát küld a soros monitorra, és a `text` üres marad.

1. Add hozzá a következő kódot ennek a metódusnak a végéhez, hogy bezárd a HTTP klienst, és visszaadd a szöveget:

    ```cpp
    httpClient.end();

    return text;
    ```

1. A `main.cpp` fájlban hívd meg ezt az új `convertSpeechToText` metódust a `processAudio` függvényben, majd írd ki a beszédet a soros monitorra:

    ```cpp
    String text = speechToText.convertSpeechToText();
    Serial.println(text);
    ```

1. Fordítsd le ezt a kódot, töltsd fel a Wio Terminal eszközödre, és teszteld a soros monitoron keresztül. Amint a `Ready` megjelenik a soros monitoron, nyomd meg a C gombot (a bal oldali, legközelebb a bekapcsoló kapcsolóhoz), és beszélj. 4 másodpercnyi hangot rögzít, majd szöveggé alakítja.

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

> 💁 Ezt a kódot megtalálod a [code-speech-to-text/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/wio-terminal) mappában.

😀 A beszéd szöveggé alakító programod sikeres volt!

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.