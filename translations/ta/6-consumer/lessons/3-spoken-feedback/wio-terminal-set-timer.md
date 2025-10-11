<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "012b69d57d898d670adf61304f42a137",
  "translation_date": "2025-10-11T12:09:22+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-set-timer.md",
  "language_code": "ta"
}
-->
# டைமர் அமைக்கவும் - Wio Terminal

இந்த பாடத்தின் இந்த பகுதியில், உங்கள் serverless code-ஐ அழைத்து பேச்சை புரிந்துகொண்டு, முடிவுகளின் அடிப்படையில் உங்கள் Wio Terminal-ல் ஒரு டைமரை அமைப்பீர்கள்.

## டைமர் அமைக்கவும்

Speech to text அழைப்பில் இருந்து வரும் உரை உங்கள் serverless code-க்கு அனுப்பப்பட வேண்டும், LUIS மூலம் செயலாக்கப்பட்டு டைமருக்கான விநாடிகளின் எண்ணிக்கையை பெற வேண்டும். இந்த விநாடிகளின் எண்ணிக்கையை டைமரை அமைக்க பயன்படுத்தலாம்.

Microcontrollers-க்கு Arduino-வில் பல threads-களை native-ஆக ஆதரிக்க முடியாது, எனவே Python அல்லது பிற உயர் நிலை மொழிகளில் காணப்படும் standard timer classes இல்லை. அதற்கு பதிலாக, `loop` செயல்பாட்டில் கழிந்த நேரத்தை அளந்து, நேரம் முடிந்ததும் செயல்பாடுகளை அழைக்கும் timer libraries-ஐ பயன்படுத்தலாம்.

### பணிகள் - உரையை serverless function-க்கு அனுப்பவும்

1. `smart-timer` திட்டத்தை VS Code-ல் திறக்கவும், அது ஏற்கனவே திறக்கப்படவில்லை என்றால்.

1. `config.h` header கோப்பை திறந்து, உங்கள் function app-க்கான URL-ஐ சேர்க்கவும்:

    ```cpp
    const char *TEXT_TO_TIMER_FUNCTION_URL = "<URL>";
    ```

    `<URL>`-ஐ உங்கள் function app-க்கான URL-ஆக மாற்றவும், இது கடந்த பாடத்தின் கடைசி படியில் நீங்கள் பெற்றது, உங்கள் local machine-ல் function app இயங்கும் IP முகவரியைச் சுட்டுகிறது.

1. `src` கோப்புறையில் ஒரு புதிய கோப்பை உருவாக்கி, அதற்கு `language_understanding.h` என்று பெயரிடவும். இது function app-க்கு அனுப்பப்பட்ட உரையை LUIS மூலம் விநாடிகளாக மாற்ற ஒரு class-ஐ வரையறுக்க பயன்படுத்தப்படும்.

1. இந்த கோப்பின் மேல் பின்வருவதைச் சேர்க்கவும்:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    ```

    இது தேவையான header கோப்புகளை உள்ளடக்குகிறது.

1. `LanguageUnderstanding` என்ற ஒரு class-ஐ வரையறுக்கவும், மற்றும் இந்த class-இன் ஒரு instance-ஐ அறிவிக்கவும்:

    ```cpp
    class LanguageUnderstanding
    {
    public:
    private:
    };

    LanguageUnderstanding languageUnderstanding;
    ```

1. உங்கள் functions app-ஐ அழைக்க, WiFi client-ஐ அறிவிக்க வேண்டும். Class-இன் `private` பிரிவில் பின்வருவதைச் சேர்க்கவும்:

    ```cpp
    WiFiClient _client;
    ```

1. `public` பிரிவில், functions app-ஐ அழைக்க `GetTimerDuration` என்ற ஒரு method-ஐ அறிவிக்கவும்:

    ```cpp
    int GetTimerDuration(String text)
    {
    }
    ```

1. `GetTimerDuration` method-இல், functions app-க்கு அனுப்ப JSON-ஐ உருவாக்க பின்வருவதைச் சேர்க்கவும்:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    இது `GetTimerDuration` method-க்கு அனுப்பப்பட்ட உரையை பின்வரும் JSON-ஆக மாற்றுகிறது:

    ```json
    {
        "text" : "<text>"
    }
    ```

    இங்கு `<text>` என்பது function-க்கு அனுப்பப்பட்ட உரையாகும்.

1. இதற்கு கீழே, functions app அழைப்பை செய்ய பின்வருவதைச் சேர்க்கவும்:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_TIMER_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    இது JSON body-ஐ அனுப்பி, response code-ஐ பெற POST request-ஐ செய்கிறது.

1. இதற்கு கீழே பின்வருவதைச் சேர்க்கவும்:

    ```cpp
    int seconds = 0;
    if (httpResponseCode == 200)
    {
        String result = httpClient.getString();
        Serial.println(result);

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, result.c_str());

        JsonObject obj = doc.as<JsonObject>();
        seconds = obj["seconds"].as<int>();
    }
    else
    {
        Serial.print("Failed to understand text - error ");
        Serial.println(httpResponseCode);
    }
    ```

    இந்த code response code-ஐ சரிபார்க்கிறது. இது 200 (வெற்றி) என்றால், response body-இல் இருந்து டைமருக்கான விநாடிகளின் எண்ணிக்கை பெறப்படுகிறது. இல்லையெனில், serial monitor-க்கு ஒரு பிழை அனுப்பப்படுகிறது, மற்றும் விநாடிகளின் எண்ணிக்கை 0-ஆக அமைக்கப்படுகிறது.

1. இந்த method-இன் இறுதியில் HTTP இணைப்பை மூடவும், மற்றும் விநாடிகளின் எண்ணிக்கையை திருப்பவும்:

    ```cpp
    httpClient.end();

    return seconds;
    ```

1. `main.cpp` கோப்பில், இந்த புதிய header-ஐ சேர்க்கவும்:

    ```cpp
    #include "speech_to_text.h"
    ```

1. `processAudio` function-இன் இறுதியில், `GetTimerDuration` method-ஐ அழைத்து டைமர் கால அளவை பெறவும்:

    ```cpp
    int total_seconds = languageUnderstanding.GetTimerDuration(text);
    ```

    இது `SpeechToText` class-இன் அழைப்பில் இருந்து உரையை டைமருக்கான விநாடிகளின் எண்ணிக்கையாக மாற்றுகிறது.

### பணிகள் - டைமரை அமைக்கவும்

விநாடிகளின் எண்ணிக்கையை டைமரை அமைக்க பயன்படுத்தலாம்.

1. `platformio.ini` கோப்பில் பின்வரும் library dependency-ஐ சேர்க்கவும்:

    ```ini
    contrem/arduino-timer @ 2.3.0
    ```

1. இந்த library-க்கு ஒரு include directive-ஐ `main.cpp` கோப்பில் சேர்க்கவும்:

    ```cpp
    #include <arduino-timer.h>
    ```

1. `processAudio` function-க்கு மேலே பின்வருவதைச் சேர்க்கவும்:

    ```cpp
    auto timer = timer_create_default();
    ```

    இந்த code `timer` என்ற ஒரு டைமரை அறிவிக்கிறது.

1. இதற்கு கீழே பின்வருவதைச் சேர்க்கவும்:

    ```cpp
    void say(String text)
    {
        Serial.print("Saying ");
        Serial.println(text);
    }
    ```

    இந்த `say` function உரையை பேச்சாக மாற்றும், ஆனால் தற்போது அது serial monitor-க்கு அனுப்பப்படும்.

1. `say` function-க்கு கீழே பின்வருவதைச் சேர்க்கவும்:

    ```cpp
    bool timerExpired(void *announcement)
    {
        say((char *)announcement);
        return false;
    }
    ```

    இது ஒரு callback function ஆகும், இது டைமர் முடிவடைந்தபோது அழைக்கப்படும். டைமர் முடிவடைந்தபோது சொல்ல ஒரு செய்தி அனுப்பப்படுகிறது. டைமர்கள் மீண்டும் இயக்கப்படலாம், மற்றும் இந்த callback-இன் return value மூலம் இது கட்டுப்படுத்தப்படுகிறது - இது `false`-ஐ திருப்புகிறது, டைமரை மீண்டும் இயக்க வேண்டாம் என்று கூற.

1. `processAudio` function-இன் இறுதியில் பின்வருவதைச் சேர்க்கவும்:

    ```cpp
    if (total_seconds == 0)
    {
        return;
    }

    int minutes = total_seconds / 60;
    int seconds = total_seconds % 60;
    ```

    இந்த code மொத்த விநாடிகளின் எண்ணிக்கையை சரிபார்க்கிறது, மற்றும் அது 0 என்றால், function call-இல் இருந்து திரும்புகிறது, எனவே எந்த டைமர்களும் அமைக்கப்படவில்லை. பின்னர் மொத்த விநாடிகளின் எண்ணிக்கையை நிமிடங்கள் மற்றும் விநாடிகளாக மாற்றுகிறது.

1. இந்த code-க்கு கீழே, டைமர் தொடங்கும்போது சொல்ல ஒரு செய்தியை உருவாக்க பின்வருவதைச் சேர்க்கவும்:

    ```cpp
    String begin_message;
    if (minutes > 0)
    {
        begin_message += minutes;
        begin_message += " minute ";
    }
    if (seconds > 0)
    {
        begin_message += seconds;
        begin_message += " second ";
    }

    begin_message += "timer started.";
    ```

1. இதற்கு கீழே, டைமர் முடிவடைந்தபோது சொல்ல ஒரு செய்தியை உருவாக்க பின்வருவதைச் சேர்க்கவும்:

    ```cpp
    String end_message("Times up on your ");
    if (minutes > 0)
    {
        end_message += minutes;
        end_message += " minute ";
    }
    if (seconds > 0)
    {
        end_message += seconds;
        end_message += " second ";
    }

    end_message += "timer.";
    ```

1. இதற்குப் பிறகு, டைமர் தொடங்கிய செய்தியைச் சொல்லவும்:

    ```cpp
    say(begin_message);
    ```

1. இந்த function-இன் இறுதியில், டைமரை தொடங்கவும்:

    ```cpp
    timer.in(total_seconds * 1000, timerExpired, (void *)(end_message.c_str()));
    ```

    இது டைமரை இயக்குகிறது. டைமர் milliseconds-ஐ பயன்படுத்தி அமைக்கப்படுகிறது, எனவே மொத்த விநாடிகளின் எண்ணிக்கை 1,000-ஆல் பெருக்கப்பட்டு milliseconds-ஆக மாற்றப்படுகிறது. `timerExpired` function callback-ஆக அனுப்பப்படுகிறது, மற்றும் callback-க்கு அனுப்ப ஒரு argument-ஆக `end_message` அனுப்பப்படுகிறது. இந்த callback `void *` arguments மட்டுமே எடுக்கிறது, எனவே string சரியாக மாற்றப்படுகிறது.

1. இறுதியாக, டைமர் *tick* செய்ய வேண்டும், இது `loop` function-இல் செய்யப்படுகிறது. `loop` function-இன் இறுதியில் பின்வருவதைச் சேர்க்கவும்:

    ```cpp
    timer.tick();
    ```

1. இந்த code-ஐ உருவாக்கி, உங்கள் Wio Terminal-க்கு upload செய்து, serial monitor மூலம் அதை சோதிக்கவும். Serial monitor-ல் `Ready` என்பதைப் பார்க்கும் போது, C button (power switch-க்கு அருகிலுள்ள இடது பக்கம் உள்ளது) அழுத்தி, பேசவும். 4 விநாடிகள் audio capture செய்யப்படும், உரையாக மாற்றப்படும், பின்னர் உங்கள் function app-க்கு அனுப்பப்படும், மற்றும் ஒரு டைமர் அமைக்கப்படும். உங்கள் function app local-ஆக இயங்குகிறது என்பதை உறுதிப்படுத்தவும்.

    டைமர் தொடங்கும் போது, மற்றும் முடிவடையும் போது நீங்கள் காண்பீர்கள்.

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
    {"seconds": 147}
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```

> 💁 இந்த code-ஐ [code-timer/wio-terminal](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/wio-terminal) கோப்புறையில் காணலாம்.

😀 உங்கள் டைமர் திட்டம் வெற்றிகரமாக முடிந்தது!

---

**குறிப்பு**:  
இந்த ஆவணம் [Co-op Translator](https://github.com/Azure/co-op-translator) என்ற AI மொழிபெயர்ப்பு சேவையைப் பயன்படுத்தி மொழிபெயர்க்கப்பட்டுள்ளது. நாங்கள் துல்லியத்திற்காக முயற்சிக்கின்றோம், ஆனால் தானியக்க மொழிபெயர்ப்புகளில் பிழைகள் அல்லது தவறான தகவல்கள் இருக்கக்கூடும் என்பதை தயவுசெய்து கவனத்தில் கொள்ளுங்கள். அதன் தாய்மொழியில் உள்ள மூல ஆவணம் அதிகாரப்பூர்வ ஆதாரமாக கருதப்பட வேண்டும். முக்கியமான தகவல்களுக்கு, தொழில்முறை மனித மொழிபெயர்ப்பு பரிந்துரைக்கப்படுகிறது. இந்த மொழிபெயர்ப்பைப் பயன்படுத்துவதால் ஏற்படும் எந்த தவறான புரிதல்கள் அல்லது தவறான விளக்கங்களுக்கு நாங்கள் பொறுப்பல்ல.