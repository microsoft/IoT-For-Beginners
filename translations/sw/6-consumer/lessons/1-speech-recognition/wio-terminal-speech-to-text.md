<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3f92edf2975175577174910caca4a389",
  "translation_date": "2025-08-27T21:27:56+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-speech-to-text.md",
  "language_code": "sw"
}
-->
# Hotuba kwa maandishi - Wio Terminal

Katika sehemu hii ya somo, utaandika msimbo wa kubadilisha hotuba katika sauti iliyorekodiwa kuwa maandishi kwa kutumia huduma ya hotuba.

## Tuma sauti kwa huduma ya hotuba

Sauti inaweza kutumwa kwa huduma ya hotuba kwa kutumia REST API. Ili kutumia huduma ya hotuba, kwanza unahitaji kuomba tokeni ya ufikiaji, kisha utumie tokeni hiyo kufikia REST API. Tokeni hizi za ufikiaji zinakwisha muda baada ya dakika 10, kwa hivyo msimbo wako unapaswa kuziomba mara kwa mara ili kuhakikisha zinabaki kuwa za kisasa.

### Kazi - pata tokeni ya ufikiaji

1. Fungua mradi wa `smart-timer` ikiwa haujafunguliwa tayari.

1. Ongeza maktaba zifuatazo za utegemezi kwenye faili ya `platformio.ini` ili kufikia WiFi na kushughulikia JSON:

    ```ini
    seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
    seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
    seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    bblanchon/ArduinoJson @ 6.17.3
    ```

1. Ongeza msimbo ufuatao kwenye faili ya kichwa `config.h`:

    ```cpp
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    
    const char *SPEECH_API_KEY = "<API_KEY>";
    const char *SPEECH_LOCATION = "<LOCATION>";
    const char *LANGUAGE = "<LANGUAGE>";

    const char *TOKEN_URL = "https://%s.api.cognitive.microsoft.com/sts/v1.0/issuetoken";
    ```

    Badilisha `<SSID>` na `<PASSWORD>` na maelezo husika ya WiFi yako.

    Badilisha `<API_KEY>` na ufunguo wa API wa rasilimali yako ya huduma ya hotuba. Badilisha `<LOCATION>` na eneo ulilotumia ulipounda rasilimali ya huduma ya hotuba.

    Badilisha `<LANGUAGE>` na jina la lugha unayozungumza, kwa mfano `en-GB` kwa Kiingereza, au `zn-HK` kwa Kantonese. Unaweza kupata orodha ya lugha zinazoungwa mkono na majina yao ya eneo katika [Nyaraka za msaada wa lugha na sauti kwenye Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    Konstanti ya `TOKEN_URL` ni URL ya mtoaji wa tokeni bila eneo. Hii itachanganywa na eneo baadaye ili kupata URL kamili.

1. Kama vile kuunganishwa na Custom Vision, utahitaji kutumia muunganisho wa HTTPS kuunganishwa na huduma ya utoaji wa tokeni. Mwisho wa `config.h`, ongeza msimbo ufuatao:

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

    Hii ni cheti sawa ulichotumia ulipounganishwa na Custom Vision.

1. Ongeza maelekezo ya kujumuisha faili ya kichwa ya WiFi na faili ya kichwa ya usanidi juu ya faili ya `main.cpp`:

    ```cpp
    #include <rpcWiFi.h>

    #include "config.h"
    ```

1. Ongeza msimbo wa kuunganishwa na WiFi katika `main.cpp` juu ya kazi ya `setup`:

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

1. Piga kazi hii kutoka kwa kazi ya `setup` baada ya muunganisho wa serial kuanzishwa:

    ```cpp
    connectWiFi();
    ```

1. Unda faili mpya ya kichwa katika folda ya `src` inayoitwa `speech_to_text.h`. Katika faili hii ya kichwa, ongeza msimbo ufuatao:

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

    Hii inajumuisha baadhi ya faili muhimu za kichwa kwa muunganisho wa HTTP, usanidi na faili ya kichwa ya `mic.h`, na inafafanua darasa linaloitwa `SpeechToText`, kabla ya kutangaza mfano wa darasa hilo ambalo linaweza kutumika baadaye.

1. Ongeza sehemu zifuatazo 2 kwenye sehemu ya `private` ya darasa hili:

    ```cpp
    WiFiClientSecure _token_client;
    String _access_token;
    ```

    `_token_client` ni Mteja wa WiFi anayefanya kazi na HTTPS na utatumika kupata tokeni ya ufikiaji. Tokeni hii kisha itahifadhiwa katika `_access_token`.

1. Ongeza njia ifuatayo kwenye sehemu ya `private`:

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

    Msimbo huu unajenga URL kwa API ya mtoaji wa tokeni kwa kutumia eneo la rasilimali ya hotuba. Kisha inaunda `HTTPClient` kufanya ombi la wavuti, ikiweka ili kutumia mteja wa WiFi uliosanidiwa na cheti cha mwisho wa tokeni. Inaweka ufunguo wa API kama kichwa cha ombi. Kisha inafanya ombi la POST kupata cheti, ikijaribu tena ikiwa kuna makosa yoyote. Hatimaye tokeni ya ufikiaji inarejeshwa.

1. Kwa sehemu ya `public`, ongeza njia ya kupata tokeni ya ufikiaji. Hii itahitajika katika masomo ya baadaye kubadilisha maandishi kuwa hotuba.

    ```cpp
    String AccessToken()
    {
        return _access_token;
    }
    ```

1. Kwa sehemu ya `public`, ongeza njia ya `init` inayoseti mteja wa tokeni:

    ```cpp
    void init()
    {
        _token_client.setCACert(TOKEN_CERTIFICATE);
        _access_token = getAccessToken();
    }
    ```

    Hii inaweka cheti kwenye mteja wa WiFi, kisha inapata tokeni ya ufikiaji.

1. Katika `main.cpp`, ongeza faili hii mpya ya kichwa kwenye maelekezo ya kujumuisha:

    ```cpp
    #include "speech_to_text.h"
    ```

1. Anzisha darasa la `SpeechToText` mwishoni mwa kazi ya `setup`, baada ya `mic.init` lakini kabla ya `Ready` kuandikwa kwenye monitor ya serial:

    ```cpp
    speechToText.init();
    ```

### Kazi - soma sauti kutoka kwa kumbukumbu ya flash

1. Katika sehemu ya awali ya somo hili, sauti ilirekodiwa kwenye kumbukumbu ya flash. Sauti hii itahitaji kutumwa kwa REST API ya Huduma ya Hotuba, kwa hivyo inahitaji kusomwa kutoka kwa kumbukumbu ya flash. Haiwezi kupakiwa kwenye buffer ya ndani ya kumbukumbu kwani itakuwa kubwa sana. Darasa la `HTTPClient` linalofanya miito ya REST linaweza kutiririsha data kwa kutumia Arduino Stream - darasa linaloweza kupakia data kwa vipande vidogo, kutuma vipande hivyo kimoja kimoja kama sehemu ya ombi. Kila wakati unapopiga `read` kwenye stream inarejesha kipande kinachofuata cha data. Stream ya Arduino inaweza kuundwa inayoweza kusoma kutoka kwa kumbukumbu ya flash. Unda faili mpya inayoitwa `flash_stream.h` katika folda ya `src`, na ongeza msimbo ufuatao:

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

    Hii inatangaza darasa la `FlashStream`, linalotokana na darasa la Arduino `Stream`. Hili ni darasa la dhahania - madarasa yanayotokana lazima yatekeleze njia chache kabla ya darasa kuweza kuanzishwa, na njia hizi zimetekelezwa katika darasa hili.

    ✅ Soma zaidi kuhusu Streams za Arduino katika [Nyaraka za Stream za Arduino](https://www.arduino.cc/reference/en/language/functions/communication/stream/)

1. Ongeza sehemu zifuatazo kwenye sehemu ya `private`:

    ```cpp
    size_t _pos;
    size_t _flash_address;
    const sfud_flash *_flash;

    byte _buffer[HTTP_TCP_BUFFER_SIZE];
    ```

    Hii inafafanua buffer ya muda ya kuhifadhi data iliyosomwa kutoka kwa kumbukumbu ya flash, pamoja na sehemu za kuhifadhi nafasi ya sasa wakati wa kusoma kutoka kwa buffer, anwani ya sasa ya kusoma kutoka kwa kumbukumbu ya flash, na kifaa cha kumbukumbu ya flash.

1. Katika sehemu ya `private`, ongeza njia ifuatayo:

    ```cpp
    void populateBuffer()
    {
        sfud_read(_flash, _flash_address, HTTP_TCP_BUFFER_SIZE, _buffer);
        _flash_address += HTTP_TCP_BUFFER_SIZE;
        _pos = 0;
    }
    ```

    Msimbo huu unasoma kutoka kwa kumbukumbu ya flash kwenye anwani ya sasa na kuhifadhi data kwenye buffer. Kisha inaongeza anwani, kwa hivyo ombi linalofuata linasoma kipande kinachofuata cha kumbukumbu. Buffer imepangwa kulingana na kipande kikubwa zaidi ambacho `HTTPClient` kitapeleka kwa REST API kwa wakati mmoja.

    > 💁 Kufuta kumbukumbu ya flash lazima kufanywe kwa kutumia saizi ya nafaka, kusoma kwa upande mwingine hakuhitaji.

1. Katika sehemu ya `public` ya darasa hili, ongeza constructor:

    ```cpp
    FlashStream()
    {
        _pos = 0;
        _flash_address = 0;
        _flash = sfud_get_device_table() + 0;
        
        populateBuffer();
    }
    ```

    Constructor hii inaseti sehemu zote kuanza kusoma kutoka mwanzo wa block ya kumbukumbu ya flash, na kupakia kipande cha kwanza cha data kwenye buffer.

1. Tekeleza njia ya `write`. Stream hii itasoma tu data, kwa hivyo hii inaweza kufanya chochote na kurudisha 0:

    ```cpp
    virtual size_t write(uint8_t val)
    {
        return 0;
    }
    ```

1. Tekeleza njia ya `peek`. Hii inarejesha data kwenye nafasi ya sasa bila kusogeza stream mbele. Kupiga `peek` mara nyingi kutarejesha data ile ile mradi hakuna data inayosomwa kutoka kwa stream.

    ```cpp
    virtual int peek()
    {
        return _buffer[_pos];
    }
    ```

1. Tekeleza kazi ya `available`. Hii inarejesha ni byte ngapi zinaweza kusomwa kutoka kwa stream, au -1 ikiwa stream imekamilika. Kwa darasa hili, kiwango cha juu kinachopatikana hakitakuwa zaidi ya saizi ya kipande cha `HTTPClient`. Wakati stream hii inatumiwa katika mteja wa HTTP inaita kazi hii kuona ni data ngapi inapatikana, kisha inaomba data hiyo kutumwa kwa REST API. Hatutaki kila kipande kuwa zaidi ya saizi ya kipande cha mteja wa HTTP, kwa hivyo ikiwa zaidi ya hiyo inapatikana, saizi ya kipande inarejeshwa. Ikiwa ni kidogo, basi kinachopatikana kinarejeshwa. Mara data yote imetiririshwa, -1 inarejeshwa.

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

1. Tekeleza njia ya `read` ili kurejesha byte inayofuata kutoka kwa buffer, ikiongeza nafasi. Ikiwa nafasi inazidi saizi ya buffer, inajaza buffer na block inayofuata kutoka kwa kumbukumbu ya flash na kuweka upya nafasi.

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

1. Katika faili ya kichwa ya `speech_to_text.h`, ongeza maelekezo ya kujumuisha faili hii mpya ya kichwa:

    ```cpp
    #include "flash_stream.h"
    ```

### Kazi - badilisha hotuba kuwa maandishi

1. Hotuba inaweza kubadilishwa kuwa maandishi kwa kutuma sauti kwa Huduma ya Hotuba kupitia REST API. REST API hii ina cheti tofauti na mtoaji wa tokeni, kwa hivyo ongeza msimbo ufuatao kwenye faili ya kichwa ya `config.h` ili kufafanua cheti hiki:

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

1. Ongeza konstanti kwenye faili hii kwa URL ya hotuba bila eneo. Hii itachanganywa na eneo na lugha baadaye ili kupata URL kamili.

    ```cpp
    const char *SPEECH_URL = "https://%s.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1?language=%s";
    ```

1. Katika faili ya kichwa ya `speech_to_text.h`, katika sehemu ya `private` ya darasa la `SpeechToText`, fafanua sehemu ya Mteja wa WiFi inayotumia cheti cha hotuba:

    ```cpp
    WiFiClientSecure _speech_client;
    ```

1. Katika njia ya `init`, weka cheti kwenye Mteja wa WiFi:

    ```cpp
    _speech_client.setCACert(SPEECH_CERTIFICATE);
    ```

1. Ongeza msimbo ufuatao kwenye sehemu ya `public` ya darasa la `SpeechToText` ili kufafanua njia ya kubadilisha hotuba kuwa maandishi:

    ```cpp
    String convertSpeechToText()
    {
        
    }
    ```

1. Ongeza msimbo ufuatao kwenye njia hii ili kuunda mteja wa HTTP kwa kutumia mteja wa WiFi uliosanidiwa na cheti cha hotuba, na kutumia URL ya hotuba iliyowekwa na eneo na lugha:

    ```cpp
    char url[128];
    sprintf(url, SPEECH_URL, SPEECH_LOCATION, LANGUAGE);

    HTTPClient httpClient;
    httpClient.begin(_speech_client, url);
    ```

1. Baadhi ya vichwa vinahitaji kuwekwa kwenye muunganisho:

    ```cpp
    httpClient.addHeader("Authorization", String("Bearer ") + _access_token);
    httpClient.addHeader("Content-Type", String("audio/wav; codecs=audio/pcm; samplerate=") + String(RATE));
    httpClient.addHeader("Accept", "application/json;text/xml");
    ```

    Hii inaweka vichwa kwa idhini kwa kutumia tokeni ya ufikiaji, muundo wa sauti kwa kutumia kiwango cha sampuli, na inaweka kwamba mteja anatarajia matokeo kama JSON.

1. Baada ya hii, ongeza msimbo ufuatao kufanya ombi la REST API:

    ```cpp
    Serial.println("Sending speech...");

    FlashStream stream;
    int httpResponseCode = httpClient.sendRequest("POST", &stream, BUFFER_SIZE);

    Serial.println("Speech sent!");
    ```

    Hii inaunda `FlashStream` na kuitumia kutiririsha data kwa REST API.

1. Chini ya hii, ongeza msimbo ufuatao:

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

    Msimbo huu unakagua msimbo wa majibu.

    Ikiwa ni 200, msimbo wa mafanikio, basi matokeo yanapatikana, yanatolewa kutoka JSON, na mali ya `DisplayText` inawekwa kwenye variable ya `text`. Hii ni mali ambayo toleo la maandishi la hotuba linarejeshwa.

    Ikiwa msimbo wa majibu ni 401, basi tokeni ya ufikiaji imekwisha muda (tokeni hizi hudumu kwa dakika 10 tu). Tokeni mpya ya ufikiaji inaombwa, na ombi linafanywa tena.

    Vinginevyo, kosa linatumwa kwa monitor ya serial, na `text` inaachwa tupu.

1. Ongeza msimbo ufuatao mwishoni mwa njia hii ili kufunga mteja wa HTTP na kurudisha maandishi:

    ```cpp
    httpClient.end();

    return text;
    ```

1. Katika `main.cpp` piga njia mpya ya `convertSpeechToText` katika kazi ya `processAudio`, kisha andika hotuba kwenye monitor ya serial:

    ```cpp
    String text = speechToText.convertSpeechToText();
    Serial.println(text);
    ```

1. Jenga msimbo huu, upakie kwenye Wio Terminal yako na ujaribu kupitia monitor ya serial. Mara tu unapoona `Ready` kwenye monitor ya serial, bonyeza kitufe cha C (kile kilicho upande wa kushoto, karibu na swichi ya nguvu), na zungumza. Sekunde 4 za sauti zitarekodiwa, kisha zitabadilishwa kuwa maandishi.

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

> 💁 Unaweza kupata msimbo huu katika folda ya [code-speech-to-text/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/wio-terminal).

😀 Programu yako ya kubadilisha hotuba kuwa maandishi imefanikiwa!

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya kutafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafadhali fahamu kuwa tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuzingatiwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.