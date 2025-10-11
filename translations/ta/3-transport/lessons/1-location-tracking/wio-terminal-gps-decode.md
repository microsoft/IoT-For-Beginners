<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "fbbcf96a9b63ccd661db98bbf854bb06",
  "translation_date": "2025-10-11T12:00:30+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-decode.md",
  "language_code": "ta"
}
-->
# GPS தரவுகளை டிகோடு செய்யுங்கள் - Wio Terminal

இந்த பாடத்தின் இந்த பகுதியில், Wio Terminal மூலம் GPS சென்சாரில் இருந்து வாசிக்கப்பட்ட NMEA செய்திகளை டிகோடு செய்து, அகல மற்றும் நீள கோடிகளை எடுக்கப் போகிறீர்கள்.

## GPS தரவுகளை டிகோடு செய்யுங்கள்

சீரியல் போர்ட்டில் இருந்து மூல NMEA தரவுகளை வாசித்த பிறகு, திறந்த மூல NMEA நூலகத்தைப் பயன்படுத்தி அதை டிகோடு செய்யலாம்.

### பணிகள் - GPS தரவுகளை டிகோடு செய்யுங்கள்

சாதனத்தை GPS தரவுகளை டிகோடு செய்ய நிரலிடுங்கள்.

1. `gps-sensor` ஆப் திட்டத்தை திறக்கவும், அது ஏற்கனவே திறக்கப்படவில்லை என்றால்.

1. TinyGPSPlus நூலகத்திற்கான [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus) நூலகத்தை திட்டத்தின் `platformio.ini` கோப்பில் நூலக சார்பாக சேர்க்கவும். இந்த நூலகத்தில் NMEA தரவுகளை டிகோடு செய்ய குறியீடு உள்ளது.

    ```ini
    lib_deps =
        mikalhart/TinyGPSPlus @ 1.0.2
    ```

1. `main.cpp` கோப்பில், TinyGPSPlus நூலகத்திற்கான ஒரு சேர்க்கும் இயக்கத்தைச் சேர்க்கவும்:

    ```cpp
    #include <TinyGPS++.h>
    ```

1. `Serial3` அறிவிப்பின் கீழ், NMEA வாக்கியங்களை செயலாக்க TinyGPSPlus பொருளை அறிவிக்கவும்:

    ```cpp
    TinyGPSPlus gps;
    ```

1. `printGPSData` செயல்பாட்டின் உள்ளடக்கத்தை பின்வரும் முறையில் மாற்றவும்:

    ```cpp
    if (gps.encode(Serial3.read()))
    {
        if (gps.location.isValid())
        {
            Serial.print(gps.location.lat(), 6);
            Serial.print(F(","));
            Serial.print(gps.location.lng(), 6);
            Serial.print(" - from ");
            Serial.print(gps.satellites.value());
            Serial.println(" satellites");
        }
    }
    ```

    இந்த குறியீடு UART சீரியல் போர்ட்டில் இருந்து அடுத்த எழுத்தை `gps` NMEA டிகோடருக்குள் வாசிக்கிறது. ஒவ்வொரு எழுத்துக்குப் பிறகும், டிகோடர் ஒரு செல்லுபடியாகும் வாக்கியத்தை வாசித்ததா என்பதைச் சரிபார்க்கும், பின்னர் செல்லுபடியாகும் இடத்தை வாசித்ததா என்பதைச் சரிபார்க்கும். இடம் செல்லுபடியாக இருந்தால், அது சீரியல் மானிட்டருக்கு அனுப்பப்படும், இந்த நிலையை சரிசெய்ய உதவிய செயற்கைக்கோள்களின் எண்ணிக்கையுடன்.

1. குறியீட்டை Wio Terminal-க்கு கட்டமைத்து பதிவேற்றவும்.

1. பதிவேற்றப்பட்ட பிறகு, சீரியல் மானிட்டரைப் பயன்படுத்தி GPS இடம் தரவுகளை கண்காணிக்கலாம்.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 இந்த குறியீட்டை [code-gps-decode/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/wio-terminal) கோப்பகத்தில் காணலாம்.

😀 உங்கள் GPS சென்சார் நிரல் தரவுகளை டிகோடு செய்வதில் வெற்றியடைந்தது!

---

**குறிப்பு**:  
இந்த ஆவணம் [Co-op Translator](https://github.com/Azure/co-op-translator) என்ற AI மொழிபெயர்ப்பு சேவையை பயன்படுத்தி மொழிபெயர்க்கப்பட்டுள்ளது. எங்கள் தரச்சிறப்பிற்காக முயற்சி செய்தாலும், தானியங்கி மொழிபெயர்ப்புகளில் பிழைகள் அல்லது தவறுகள் இருக்கக்கூடும் என்பதை கவனத்தில் கொள்ளவும். அதன் தாய்மொழியில் உள்ள மூல ஆவணம் அதிகாரப்பூர்வ ஆதாரமாக கருதப்பட வேண்டும். முக்கியமான தகவல்களுக்கு, தொழில்முறை மனித மொழிபெயர்ப்பு பரிந்துரைக்கப்படுகிறது. இந்த மொழிபெயர்ப்பைப் பயன்படுத்துவதால் ஏற்படும் எந்த தவறான புரிதல்கள் அல்லது தவறான விளக்கங்களுக்கு நாங்கள் பொறுப்பல்ல.