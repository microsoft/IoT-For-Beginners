<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "fbbcf96a9b63ccd661db98bbf854bb06",
  "translation_date": "2025-08-28T16:46:38+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-decode.md",
  "language_code": "my"
}
-->
# GPS ဒေတာကို ဖော်ထုတ်ခြင်း - Wio Terminal

ဒီသင်ခန်းပိုင်းမှာ Wio Terminal မှ GPS ဆင်ဆာကနေဖတ်ထားတဲ့ NMEA မက်ဆေ့ချ်တွေကို ဖော်ထုတ်ပြီး latitude နဲ့ longitude ကို ရယူပါမယ်။

## GPS ဒေတာကို ဖော်ထုတ်ခြင်း

Serial port ကနေ raw NMEA ဒေတာကို ဖတ်ပြီးရင် open source NMEA library ကို အသုံးပြုပြီး ဖော်ထုတ်နိုင်ပါတယ်။

### အလုပ် - GPS ဒေတာကို ဖော်ထုတ်ခြင်း

GPS ဒေတာကို ဖော်ထုတ်ဖို့ device ကို programming လုပ်ပါ။

1. `gps-sensor` app project ကို မဖွင့်ထားရင် ဖွင့်ပါ။

1. Project ရဲ့ `platformio.ini` ဖိုင်မှာ [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus) library အတွက် library dependency ကို ထည့်ပါ။ ဒီ library မှာ NMEA ဒေတာကို ဖော်ထုတ်ဖို့ code ပါပါတယ်။

    ```ini
    lib_deps =
        mikalhart/TinyGPSPlus @ 1.0.2
    ```

1. `main.cpp` မှာ TinyGPSPlus library အတွက် include directive ကို ထည့်ပါ:

    ```cpp
    #include <TinyGPS++.h>
    ```

1. `Serial3` ရဲ့ ကြေညာချက်အောက်မှာ TinyGPSPlus object ကို NMEA sentences ကို process လုပ်ဖို့ ကြေညာပါ:

    ```cpp
    TinyGPSPlus gps;
    ```

1. `printGPSData` function ရဲ့ အကြောင်းအရာကို အောက်ပါအတိုင်း ပြောင်းပါ:

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

    ဒီ code က UART serial port ကနေ character တစ်ခုချင်းစီကို `gps` NMEA decoder ထဲကို ဖတ်ပါတယ်။ Character တစ်ခုချင်းစီဖတ်ပြီးရင် decoder က valid sentence ဖတ်ထားမထား စစ်ဆေးပြီး valid location ဖတ်ထားမထားကို စစ်ဆေးပါမယ်။ Location valid ဖြစ်ရင် serial monitor ကို satellites အရေအတွက်နဲ့ location data ကို ပို့ပါမယ်။

1. Code ကို build လုပ်ပြီး Wio Terminal ထဲကို upload လုပ်ပါ။

1. Upload ပြီးရင် serial monitor ကို အသုံးပြုပြီး GPS location data ကို ကြည့်နိုင်ပါမယ်။

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 ဒီ code ကို [code-gps-decode/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/wio-terminal) folder မှာ ရှာနိုင်ပါတယ်။

😀 GPS sensor program နဲ့ data decoding အောင်မြင်ပါတယ်!

---

**အကြောင်းကြားချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှုအတွက် ကြိုးစားနေသော်လည်း၊ အလိုအလျောက် ဘာသာပြန်မှုများတွင် အမှားများ သို့မဟုတ် မမှန်ကန်မှုများ ပါဝင်နိုင်သည်ကို သတိပြုပါ။ မူရင်းစာရွက်စာတမ်းကို ၎င်း၏ မူရင်းဘာသာစကားဖြင့် အာဏာတရားရှိသော အရင်းအမြစ်အဖြစ် သတ်မှတ်သင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူက ဘာသာပြန်မှု ဝန်ဆောင်မှုကို အသုံးပြုရန် အကြံပြုပါသည်။ ဤဘာသာပြန်မှုကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော အလွဲအလွတ်များ သို့မဟုတ် အနားယူမှုများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။