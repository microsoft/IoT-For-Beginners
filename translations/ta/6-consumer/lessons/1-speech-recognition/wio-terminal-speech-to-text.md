<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3f92edf2975175577174910caca4a389",
  "translation_date": "2025-10-11T12:18:29+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-speech-to-text.md",
  "language_code": "ta"
}
-->
# பேச்சை உரையாக மாற்றுதல் - Wio Terminal

இந்த பாடத்தின் இந்த பகுதியில், நீங்கள் பேச்சை சேகரிக்கப்பட்ட ஆடியோவில் இருந்து உரையாக மாற்றுவதற்கான குறியீட்டை எழுதுவீர்கள், பேச்சை சேவை மூலம்.

## ஆடியோவை பேச்சை சேவைக்கு அனுப்புதல்

ஆடியோவை REST API மூலம் பேச்சை சேவைக்கு அனுப்பலாம். பேச்சை சேவையை பயன்படுத்த, முதலில் நீங்கள் அணுகல் டோக்கனை கோர வேண்டும், பின்னர் அந்த டோக்கனை REST API-யை அணுக பயன்படுத்த வேண்டும். இந்த அணுகல் டோக்கன்கள் 10 நிமிடங்களுக்கு பிறகு காலாவதியாகிவிடும், எனவே உங்கள் குறியீடு அவற்றை அடிக்கடி கோர வேண்டும், அவை எப்போதும் புதுப்பிக்கப்பட்டதாக இருக்க உறுதிப்படுத்த.

### பணிகள் - அணுகல் டோக்கனை பெறுதல்

1. `smart-timer` திட்டத்தை திறக்கவும், அது ஏற்கனவே திறக்கப்படவில்லை என்றால்.

1. WiFi-யை அணுகவும் JSON-ஐ கையாளவும் `platformio.ini` கோப்பில் பின்வரும் நூலக சார்புகளைச் சேர்க்கவும்:

    ```ini
    seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
    seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
    seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    bblanchon/ArduinoJson @ 6.17.3
    ```

1. `config.h` தலைப்பு கோப்பில் பின்வரும் குறியீட்டைச் சேர்க்கவும்:

    ```cpp
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    
    const char *SPEECH_API_KEY = "<API_KEY>";
    const char *SPEECH_LOCATION = "<LOCATION>";
    const char *LANGUAGE = "<LANGUAGE>";

    const char *TOKEN_URL = "https://%s.api.cognitive.microsoft.com/sts/v1.0/issuetoken";
    ```

    `<SSID>` மற்றும் `<PASSWORD>`-ஐ உங்கள் WiFi-க்கு தொடர்புடைய மதிப்புகளுடன் மாற்றவும்.

    `<API_KEY>`-ஐ உங்கள் பேச்சை சேவை வளத்தின் API விசையுடன் மாற்றவும். `<LOCATION>`-ஐ நீங்கள் பேச்சை சேவை வளத்தை உருவாக்கிய போது பயன்படுத்திய இடத்துடன் மாற்றவும்.

    `<LANGUAGE>`-ஐ நீங்கள் பேசும் மொழிக்கான இடப்பெயருடன் மாற்றவும், உதாரணமாக ஆங்கிலத்திற்கான `en-GB`, அல்லது காந்தோனீஸிற்கான `zn-HK`. ஆதரிக்கப்படும் மொழிகள் மற்றும் அவற்றின் இடப்பெயர்கள் பற்றிய பட்டியலை [Microsoft ஆவணங்களில் மொழி மற்றும் குரல் ஆதரவு ஆவணத்தில்](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) காணலாம்.

    `TOKEN_URL` மாறி என்பது இடத்தை இல்லாமல் டோக்கன் வழங்குநரின் URL ஆகும். இது பின்னர் முழு URL-ஐ பெற இடத்துடன் இணைக்கப்படும்.

1. Custom Vision-க்கு இணைப்பதுபோல, டோக்கன் வழங்கும் சேவைக்கு HTTPS இணைப்பைப் பயன்படுத்த வேண்டும். `config.h`-இன் இறுதியில் பின்வரும் குறியீட்டைச் சேர்க்கவும்:

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

    இது Custom Vision-க்கு இணைக்கும் போது நீங்கள் பயன்படுத்திய சான்றிதழே.

1. `main.cpp` கோப்பின் மேல் பகுதியில் WiFi தலைப்பு கோப்பிற்கும் config தலைப்பு கோப்பிற்கும் ஒரு சேர்க்கையைச் சேர்க்கவும்:

    ```cpp
    #include <rpcWiFi.h>

    #include "config.h"
    ```

1. `setup` செயல்பாட்டிற்கு மேலே `main.cpp`-இல் WiFi-க்கு இணைக்க குறியீட்டைச் சேர்க்கவும்:

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

1. சீரியல் இணைப்பு நிறுவப்பட்ட பிறகு `setup` செயல்பாட்டில் இந்த செயல்பாட்டை அழைக்கவும்:

    ```cpp
    connectWiFi();
    ```

1. `src` கோப்பகத்தில் `speech_to_text.h` என்ற புதிய தலைப்பு கோப்பை உருவாக்கவும். இந்த தலைப்பு கோப்பில் பின்வரும் குறியீட்டைச் சேர்க்கவும்:

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

    இது HTTP இணைப்பிற்கான சில தேவையான தலைப்பு கோப்புகளை, கட்டமைப்பை மற்றும் `mic.h` தலைப்பு கோப்பை சேர்க்கிறது, மேலும் `SpeechToText` என்ற வகுப்பை வரையறுக்கிறது, பின்னர் பின்னர் பயன்படுத்தக்கூடிய அந்த வகுப்பின் ஒரு உதாரணத்தை அறிவிக்கிறது.

1. இந்த வகுப்பின் `private` பிரிவில் பின்வரும் 2 புலங்களைச் சேர்க்கவும்:

    ```cpp
    WiFiClientSecure _token_client;
    String _access_token;
    ```

    `_token_client` என்பது HTTPS-ஐ பயன்படுத்தும் WiFi Client ஆகும், இது அணுகல் டோக்கனைப் பெற பயன்படுத்தப்படும். இந்த டோக்கன் பின்னர் `_access_token`-இல் சேமிக்கப்படும்.

1. `private` பிரிவில் பின்வரும் முறைசெயல்பாட்டைச் சேர்க்கவும்:

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

    இந்த குறியீடு பேச்சை வளத்தின் இடத்தைப் பயன்படுத்தி டோக்கன் வழங்குநர் API-க்கான URL-ஐ உருவாக்குகிறது. பின்னர் ஒரு `HTTPClient` உருவாக்கி வலை கோரிக்கையைச் செய்கிறது, WiFi கிளையண்டை டோக்கன் முடிவுகளின் சான்றிதழுடன் அமைக்கிறது. API விசையை அழைப்புக்கான தலைப்பாக அமைக்கிறது. பின்னர் சான்றிதழைப் பெற POST கோரிக்கையைச் செய்கிறது, எந்தவொரு பிழைகளையும் பெறும்போது மீண்டும் முயற்சிக்கிறது. இறுதியாக அணுகல் டோக்கன் திருப்பப்படுகிறது.

1. `public` பிரிவில், அணுகல் டோக்கனைப் பெற ஒரு முறைசெயல்பாட்டைச் சேர்க்கவும். இது உரையை பேச்சாக மாற்றுவதற்கான பின்னர் பாடங்களில் தேவைப்படும்.

    ```cpp
    String AccessToken()
    {
        return _access_token;
    }
    ```

1. `public` பிரிவில், டோக்கன் கிளையண்டை அமைக்கும் ஒரு `init` முறைசெயல்பாட்டைச் சேர்க்கவும்:

    ```cpp
    void init()
    {
        _token_client.setCACert(TOKEN_CERTIFICATE);
        _access_token = getAccessToken();
    }
    ```

    இது WiFi கிளையண்டில் சான்றிதழை அமைக்கிறது, பின்னர் அணுகல் டோக்கனைப் பெறுகிறது.

1. `main.cpp`-இல், இந்த புதிய தலைப்பு கோப்பை சேர்க்கவும்:

    ```cpp
    #include "speech_to_text.h"
    ```

1. `setup` செயல்பாட்டின் இறுதியில், `mic.init` அழைப்புக்குப் பிறகு ஆனால் சீரியல் மானிட்டரில் `Ready` எழுதுவதற்கு முன் `SpeechToText` வகுப்பை ஆரம்பிக்கவும்:

    ```cpp
    speechToText.init();
    ```

### பணிகள் - ஃப்ளாஷ் நினைவகத்திலிருந்து ஆடியோவைப் படிக்கவும்

1. இந்த பாடத்தின் முந்தைய பகுதியில், ஆடியோ ஃப்ளாஷ் நினைவகத்தில் பதிவு செய்யப்பட்டது. இந்த ஆடியோ Speech Services REST API-க்கு அனுப்பப்பட வேண்டும், எனவே இது ஃப்ளாஷ் நினைவகத்திலிருந்து படிக்கப்பட வேண்டும். இது நினைவகத்தில் உள்ள ஒரு இடைநிலை பஃபரில் ஏற்றப்பட முடியாது, ஏனெனில் இது மிகவும் பெரியதாக இருக்கும். REST அழைப்புகளைச் செய்யும் `HTTPClient` வகுப்பு ஒரு Arduino Stream-ஐப் பயன்படுத்தி தரவுகளை ஸ்ட்ரீம் செய்ய முடியும் - இது சிறிய துண்டுகளில் தரவுகளை ஏற்ற முடியும், கோரிக்கையின் ஒரு பகுதியாக ஒவ்வொரு முறையும் ஒரு துண்டை அனுப்புகிறது. ஒவ்வொரு முறையும் நீங்கள் ஸ்ட்ரீமில் `read` அழைக்கும்போது, ​​அடுத்த தரவுத் தொகுதியைத் திருப்புகிறது. ஃப்ளாஷ் நினைவகத்திலிருந்து படிக்க முடியும் Arduino ஸ்ட்ரீம் உருவாக்கலாம். `src` கோப்பகத்தில் `flash_stream.h` என்ற புதிய கோப்பை உருவாக்கி, அதில் பின்வரும் குறியீட்டைச் சேர்க்கவும்:

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

    இது Arduino `Stream` வகுப்பிலிருந்து பெறப்பட்ட `FlashStream` வகுப்பை அறிவிக்கிறது. இது ஒரு அப்ஸ்ட்ராக்ட் வகுப்பு - பெறப்பட்ட வகுப்புகள் சில முறைகளை செயல்படுத்த வேண்டும், பின்னர் வகுப்பை உருவாக்க முடியும், மேலும் இந்த முறைகள் இந்த வகுப்பில் வரையறுக்கப்பட்டுள்ளன.

    ✅ Arduino ஸ்ட்ரீம்கள் பற்றிய மேலும் அறிய [Arduino Stream ஆவணத்தில்](https://www.arduino.cc/reference/en/language/functions/communication/stream/)

1. `private` பிரிவில் பின்வரும் புலங்களைச் சேர்க்கவும்:

    ```cpp
    size_t _pos;
    size_t _flash_address;
    const sfud_flash *_flash;

    byte _buffer[HTTP_TCP_BUFFER_SIZE];
    ```

    இது ஃப்ளாஷ் நினைவகத்திலிருந்து படிக்கப்படும் தரவத்தை சேமிக்க தற்காலிக பஃபரை வரையறுக்கிறது, பஃபரில் படிக்கும் போது தற்போதைய நிலையை, ஃப்ளாஷ் நினைவகத்திலிருந்து படிக்க தற்போதைய முகவரியை மற்றும் ஃப்ளாஷ் நினைவக சாதனத்தைச் சேர்க்கிறது.

1. `private` பிரிவில் பின்வரும் முறைசெயல்பாட்டைச் சேர்க்கவும்:

    ```cpp
    void populateBuffer()
    {
        sfud_read(_flash, _flash_address, HTTP_TCP_BUFFER_SIZE, _buffer);
        _flash_address += HTTP_TCP_BUFFER_SIZE;
        _pos = 0;
    }
    ```

    இந்த குறியீடு ஃப்ளாஷ் நினைவகத்தில் தற்போதைய முகவரியில் இருந்து படிக்கிறது மற்றும் தரவுகளை பஃபரில் சேமிக்கிறது. பின்னர் முகவரியை அதிகரிக்கிறது, எனவே அடுத்த அழைப்பு ஞாபகத்தின் அடுத்த தொகுதியை படிக்கிறது. பஃபர் HTTPClient REST API-க்கு ஒரே நேரத்தில் அனுப்பும் மிகப்பெரிய துண்டின் அளவை அடிப்படையாகக் கொண்டது.

    > 💁 ஃப்ளாஷ் நினைவகத்தை அழிப்பது தானிய அளவைப் பயன்படுத்தி செய்ய வேண்டும், படிக்கும்போது அவ்வாறு தேவையில்லை.

1. இந்த வகுப்பின் `public` பிரிவில் ஒரு கட்டமைப்பாளரைச் சேர்க்கவும்:

    ```cpp
    FlashStream()
    {
        _pos = 0;
        _flash_address = 0;
        _flash = sfud_get_device_table() + 0;
        
        populateBuffer();
    }
    ```

    இந்த கட்டமைப்பாளர் ஃப்ளாஷ் நினைவக தொகுதியின் தொடக்கத்தில் இருந்து படிக்க தொடங்க அனைத்து புலங்களையும் அமைக்கிறது, மேலும் பஃபரில் முதல் துண்டு தரவுகளை ஏற்றுகிறது.

1. `write` முறையை செயல்படுத்தவும். இந்த ஸ்ட்ரீம் தரவுகளை மட்டும் படிக்கும், எனவே இது எதுவும் செய்யாமல் 0-ஐ திருப்பலாம்:

    ```cpp
    virtual size_t write(uint8_t val)
    {
        return 0;
    }
    ```

1. `peek` முறையை செயல்படுத்தவும். இது ஸ்ட்ரீமில் நகராமல் தற்போதைய நிலையின் தரவுகளை திருப்புகிறது. ஸ்ட்ரீமில் எந்தவொரு தரவையும் படிக்காமல் `peek` பலமுறை அழைக்கும்போது, ​​அதே தரவுகளை திருப்பும்.

    ```cpp
    virtual int peek()
    {
        return _buffer[_pos];
    }
    ```

1. `available` செயல்பாட்டை செயல்படுத்தவும். இது ஸ்ட்ரீமில் இருந்து எத்தனை பைட்களை படிக்க முடியும் என்பதை திருப்புகிறது, அல்லது ஸ்ட்ரீம் முடிந்தால் -1 திருப்புகிறது. இந்த வகுப்பிற்கான அதிகபட்சம் HTTPClient-ன் துண்டு அளவை விட அதிகமாக இருக்காது. இந்த ஸ்ட்ரீம் HTTP கிளையண்டில் பயன்படுத்தப்படும் போது, ​​அது எவ்வளவு தரவுகள் கிடைக்கின்றன என்பதைப் பார்க்க இந்த செயல்பாட்டை அழைக்கிறது, பின்னர் REST API-க்கு அனுப்ப அந்த அளவு தரவுகளை கோருகிறது. ஒவ்வொரு துண்டும் HTTP கிளையண்டின் துண்டு அளவை விட அதிகமாக இருக்கக்கூடாது, எனவே அதிகமாக கிடைக்குமானால், துண்டு அளவு திருப்பப்படுகிறது. குறைவாக இருந்தால், கிடைக்கக்கூடிய அளவு திருப்பப்படுகிறது. அனைத்து தரவுகளும் ஸ்ட்ரீம் செய்யப்பட்ட பிறகு, -1 திருப்பப்படுகிறது.

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

1. பஃபரில் இருந்து அடுத்த பைட்டை திருப்ப `read` முறையை செயல்படுத்தவும், நிலையை அதிகரிக்கவும். நிலை பஃபரின் அளவை மீறினால், ஃப்ளாஷ் நினைவகத்திலிருந்து அடுத்த தொகுதியை பஃபரில் நிரப்புகிறது மற்றும் நிலையை மீட்டமைக்கிறது.

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

1. `speech_to_text.h` தலைப்பு கோப்பில், இந்த புதிய தலைப்பு கோப்பிற்கான ஒரு சேர்க்கையைச் சேர்க்கவும்:

    ```cpp
    #include "flash_stream.h"
    ```

### பணிகள் - பேச்சை உரையாக மாற்றுதல்

1. பேச்சை REST API மூலம் Speech Service-க்கு அனுப்புவதன் மூலம் உரையாக மாற்றலாம். இந்த REST API-க்கு டோக்கன் வழங்குநருக்கு மாறுபட்ட சான்றிதழ் உள்ளது, எனவே இந்த சான்றிதழை வரையறுக்க `config.h` தலைப்பு கோப்பில் பின்வரும் குறியீட்டைச் சேர்க்கவும்:

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

1. இந்த கோப்பில் இடத்தை இல்லாமல் பேச்சு URL-க்கான ஒரு மாறியைச் சேர்க்கவும். இது இடத்துடன் மொழியை இணைத்து முழு URL-ஐ பெறப்படும்.

    ```cpp
    const char *SPEECH_URL = "https://%s.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1?language=%s";
    ```

1. `speech_to_text.h` தலைப்பு கோப்பில், `SpeechToText` வகுப்பின் `private` பிரிவில் பேச்சு சான்றிதழைப் பயன்படுத்தும் WiFi Client-க்கான ஒரு புலத்தை வரையறுக்கவும்:

    ```cpp
    WiFiClientSecure _speech_client;
    ```

1. `init` முறையில், இந்த WiFi Client-ல் சான்றிதழை அமைக்கவும்:

    ```cpp
    _speech_client.setCACert(SPEECH_CERTIFICATE);
    ```

1. `SpeechToText` வகுப்பின் `public` பிரிவில் பேச்சை உரையாக மாற்ற ஒரு முறைசெயல்பாட்டை வரையறுக்க பின்வரும் குறியீட்டைச் சேர்க்கவும்:

    ```cpp
    String convertSpeechToText()
    {
        
    }
    ```

1. இந்த முறையில் பின்வரும் குறியீட்டைச் சேர்க்கவும், பேச்சு சான்றிதழுடன் உள்ள WiFi Client-ஐப் பயன்படுத்தி HTTP கிளையண்டை உருவாக்கவும், மற்றும் இடத்துடன் மொழியை அமைத்த URL-ஐப் பயன்படுத்தவும்:

    ```cpp
    char url[128];
    sprintf(url, SPEECH_URL, SPEECH_LOCATION, LANGUAGE);

    HTTPClient httpClient;
    httpClient.begin(_speech_client, url);
    ```

1. இணைப்பில் சில தலைப்புகளை அமைக்க வேண்டும்:

    ```cpp
    httpClient.addHeader("Authorization", String("Bearer ") + _access_token);
    httpClient.addHeader("Content-Type", String("audio/wav; codecs=audio/pcm; samplerate=") + String(RATE));
    httpClient.addHeader("Accept", "application/json;text/xml");
    ```

    இது அணுகல் டோக்கனைப் பயன்படுத்தி அங்கீகாரத்திற்கான தலைப்புகளை அமைக்கிறது, சாம்பிள் வீதத்தைப் பயன்படுத்தி ஆடியோ வடிவத்தை அமைக்கிறது, மற்றும் கிளையண்ட் முடிவை JSON ஆக எதிர்பார்க்கிறது.

1. இதற்குப் பிறகு, REST API அழைப்பைச் செய்ய பின்வரும் குறியீட்டைச் சேர்க்கவும்:

    ```cpp
    Serial.println("Sending speech...");

    FlashStream stream;
    int httpResponseCode = httpClient.sendRequest("POST", &stream, BUFFER_SIZE);

    Serial.println("Speech sent!");
    ```

    இது ஒரு `FlashStream` உருவாக்கி REST API-க்கு தரவுகளை ஸ்ட்ரீம் செய்ய பயன்படுத்துகிறது.

1. இதற்கு கீழே பின்வரும் குறியீட்டைச் சேர்க்கவும்:

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

    இந்த குறியீடு பதிலளிப்பு குறியீட்டைச் சரிபார்க்கிறது.

    இது 200 என்ற வெற்றிக்குறியீடு இருந்தால், முடிவு JSON-இல் இருந்து மீட்கப்படுகிறது, டிகோட் செய்யப்படுகிறது, மற்றும் `DisplayText` சொத்து `text` மாறியில் அமைக்கப்படுகிறது. பேச்சின் உரை பதிப்பு திருப்பப்படும் சொத்து இதுவே.

    பதிலளிப்பு குறியீடு 401 என்றால், அணுகல் டோக்கன் காலாவதியாகிவிட்டது (இந்த டோக்கன்கள் 10 நிமிடங்கள் மட்டுமே நீடிக்கும்). புதிய அணுகல் டோக்கன் கோரப்படுகிறது, மற்றும் அழைப்பு மீண்டும் செய்யப்படுகிறது.

    இல்லையெனில், ஒரு பிழை சீரியல் மானிட்டரில் அனுப்பப்படுகிறது, மற்றும் `text` வெறுமையாக விடப்படுகிறது.

1. இந்த முறையின் இறுதியில் HTTP கிளையண்டை மூடவும் மற்றும் உரையை திருப்பவும்:

    ```cpp
    httpClient.end();

    return text;
    ```

1. `main.cpp`-இல், இந்த புதிய `convertSpeechToText` முறையை `processAudio` செயல்பாட்டில் அழைக்கவும், பின்னர் பேச்சை சீரியல் மானிட்டரில் பதிவு செய்யவும்:

    ```cpp
    String text = speechToText.convertSpeechToText();
    Serial.println(text);
    ```

1. இந்த குறியீட்டை உருவாக்கி, அதை உங்கள் Wio Terminal-க்கு பதிவேற்றவும், மற்றும் சீரியல் மானிட்டர் மூலம் சோதிக்கவும். சீரியல் மானிட்டரில் `Ready` என்பதைப் பார்க்கும் போது, ​​C பொத்தானை அழுத்தவும் (இது இடது பக்கத்தில், மின்சார சுவிட்சிற்கு அருகில் உள்ளது), மற்றும் பேசவும். 4 விநாடிகள் ஆடியோ பதிவு செய்யப்படும், பின்னர் உரையாக மாற்றப்படும்.

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

> 💁 இந்த குறியீட்டை [code-speech-to-text/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/wio-terminal) கோப்பகத்தில் காணலாம்.

😀 உங்கள் பேச்சை உரையாக மாற்றும் திட்டம் வெற்றிகரமாக முடிந்தது!

---

**குறிப்பு**:  
இந்த ஆவணம் [Co-op Translator](https://github.com/Azure/co-op-translator) என்ற AI மொழிபெயர்ப்பு சேவையைப் பயன்படுத்தி மொழிபெயர்க்கப்பட்டுள்ளது. நாங்கள் துல்லியத்திற்காக முயற்சிக்கின்றோம், ஆனால் தானியக்க மொழிபெயர்ப்புகளில் பிழைகள் அல்லது தவறான தகவல்கள் இருக்கக்கூடும் என்பதை தயவுசெய்து கவனத்தில் கொள்ளுங்கள். அதன் தாய்மொழியில் உள்ள மூல ஆவணம் அதிகாரப்பூர்வ ஆதாரமாக கருதப்பட வேண்டும். முக்கியமான தகவல்களுக்கு, தொழில்முறை மனித மொழிபெயர்ப்பு பரிந்துரைக்கப்படுகிறது. இந்த மொழிபெயர்ப்பைப் பயன்படுத்துவதால் ஏற்படும் எந்த தவறான புரிதல்கள் அல்லது தவறான விளக்கங்களுக்கு நாங்கள் பொறுப்பல்ல.