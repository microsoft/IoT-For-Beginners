<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d6faf0e8d3c2d6d20c0aef2a305dab18",
  "translation_date": "2025-08-28T17:11:46+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md",
  "language_code": "my"
}
-->
# အင်တာနက်မှ သင့်ညဉ့်မီးအိမ်ကို ထိန်းချုပ်ပါ - Wio Terminal

IoT စက်ပစ္စည်းကို *test.mosquitto.org* နှင့် MQTT ကို အသုံးပြု၍ ဆက်သွယ်ရန် ကုဒ်ရေးရန် လိုအပ်ပါသည်။ မီးအိမ်အလင်းအာရုံခံကိရိယာမှ Telemetry တန်ဖိုးများ ပေးပို့ရန်နှင့် LED ကို ထိန်းချုပ်ရန် အမိန့်များ လက်ခံရန် လိုအပ်ပါသည်။

ဒီသင်ခန်းစာအပိုင်းတွင် သင့် Wio Terminal ကို MQTT broker နှင့် ချိတ်ဆက်ပါမည်။

## WiFi နှင့် MQTT Arduino Libraries ကို ထည့်သွင်းပါ

MQTT broker နှင့် ဆက်သွယ်ရန် Wio Terminal ရှိ WiFi chip ကို အသုံးပြုရန် Arduino libraries အချို့ကို ထည့်သွင်းရန် လိုအပ်ပါသည်။ Arduino စက်ပစ္စည်းများအတွက် ဖွံ့ဖြိုးရေးလုပ်စဉ်တွင် အခမဲ့သုံးနိုင်သော ကုဒ်များပါဝင်သည့် libraries များစွာကို အသုံးပြုနိုင်ပါသည်။ Seeed သည် Wio Terminal အတွက် WiFi ဖြင့် ဆက်သွယ်နိုင်ရန် libraries များကို ထုတ်ဝေထားပါသည်။ MQTT broker များနှင့် ဆက်သွယ်ရန် အခြားဖွံ့ဖြိုးရေးသူများက ထုတ်ဝေထားသော libraries များကိုလည်း သင့်စက်ပစ္စည်းနှင့် အသုံးပြုမည်ဖြစ်သည်။

ဒီ libraries များကို PlatformIO ထဲသို့ အလိုအလျောက် တင်သွင်းပြီး သင့်စက်ပစ္စည်းအတွက် compile လုပ်နိုင်ပါသည်။ ဒီလိုနည်းဖြင့် Arduino libraries များသည် Arduino framework ကို ပံ့ပိုးသည့် စက်ပစ္စည်းများအားလုံးတွင် အလုပ်လုပ်နိုင်ပါသည်။ သို့သော် library တစ်ခုချင်းစီအတွက် လိုအပ်သော hardware ရှိရမည်ဖြစ်သည်။ Seeed WiFi libraries ကဲ့သို့သော libraries အချို့သည် သတ်မှတ်ထားသော hardware များအတွက်သာ ဖြစ်သည်။

Libraries များကို စနစ်တကျ ထည့်သွင်းပြီး compile လုပ်နိုင်သလို သီးခြားပရောဂျက်အတွင်းတွင်သာ ထည့်သွင်းနိုင်ပါသည်။ ဒီအလုပ်အတွက် libraries များကို ပရောဂျက်အတွင်း ထည့်သွင်းပါမည်။

✅ Library များကို စီမံခန့်ခွဲနည်းနှင့် ထည့်သွင်းနည်းများကို [PlatformIO library documentation](https://docs.platformio.org/en/latest/librarymanager/index.html) တွင် ပိုမိုလေ့လာနိုင်ပါသည်။

### လုပ်ငန်း - WiFi နှင့် MQTT Arduino libraries ကို ထည့်သွင်းပါ

Arduino libraries များကို ထည့်သွင်းပါ။

1. VS Code တွင် nightlight ပရောဂျက်ကို ဖွင့်ပါ။

1. `platformio.ini` ဖိုင်၏ အဆုံးတွင် အောက်ပါအတိုင်း ထည့်သွင်းပါ။

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
        seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
        seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    ```

    ဒီကနေ Seeed WiFi libraries များကို တင်သွင်းပါသည်။ `@ <number>` သည် library ၏ သတ်မှတ်ထားသော ဗားရှင်းနံပါတ်ကို ဆိုလိုသည်။

    > 💁 `@ <number>` ကို ဖယ်ရှားပြီး library များ၏ နောက်ဆုံးဗားရှင်းကို အမြဲအသုံးပြုနိုင်သော်လည်း နောက်ဆုံးဗားရှင်းများသည် အောက်ပါကုဒ်နှင့် အလုပ်လုပ်မည်ဆိုသော အာမခံချက်မရှိပါ။ ဒီကုဒ်ကို library ၏ ဤဗားရှင်းနှင့် စမ်းသပ်ပြီးဖြစ်သည်။

    Library များကို ထည့်သွင်းရန် လိုအပ်သည့် အရာအားလုံးသည် ဤအပိုင်းဖြစ်သည်။ PlatformIO သည် ပရောဂျက်ကို build လုပ်သည့်အခါ library များ၏ source code ကို ဒေါင်းလုပ်ဆွဲပြီး သင့်ပရောဂျက်အတွင်း compile လုပ်ပါမည်။

1. `lib_deps` တွင် အောက်ပါအတိုင်း ထည့်သွင်းပါ။

    ```ini
    knolleary/PubSubClient @ 2.8
    ```

    ဒီကနေ [PubSubClient](https://github.com/knolleary/pubsubclient) ကို တင်သွင်းပါသည်။ ၎င်းသည် Arduino MQTT client တစ်ခုဖြစ်သည်။

## WiFi နှင့် ချိတ်ဆက်ပါ

ယခု Wio Terminal ကို WiFi နှင့် ချိတ်ဆက်နိုင်ပါပြီ။

### လုပ်ငန်း - WiFi နှင့် ချိတ်ဆက်ပါ

Wio Terminal ကို WiFi နှင့် ချိတ်ဆက်ပါ။

1. `src` ဖိုလ်ဒါအတွင်း `config.h` ဟုခေါ်သော ဖိုင်အသစ်တစ်ခု ဖန်တီးပါ။ ၎င်းကို `src` ဖိုလ်ဒါကို ရွေးချယ်ခြင်းဖြင့် သို့မဟုတ် `main.cpp` ဖိုင်အတွင်းမှ **New file** ခလုတ်ကို ရွေးချယ်ခြင်းဖြင့် ပြုလုပ်နိုင်ပါသည်။ 

    ![The new file button](../../../../../translated_images/vscode-new-file-button.182702340fe6723c.my.png)

1. WiFi အချက်အလက်များအတွက် constants များကို သတ်မှတ်ရန် အောက်ပါကုဒ်ကို ထည့်သွင်းပါ။

    ```cpp
    #pragma once

    #include <string>
    
    using namespace std;
    
    // WiFi credentials
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    ```

    `<SSID>` ကို သင့် WiFi ၏ SSID ဖြင့် အစားထိုးပါ။ `<PASSWORD>` ကို သင့် WiFi စကားဝှက်ဖြင့် အစားထိုးပါ။

1. `main.cpp` ဖိုင်ကို ဖွင့်ပါ။

1. ဖိုင်၏ အပေါ်ဆုံးတွင် အောက်ပါ `#include` directives များကို ထည့်သွင်းပါ။

    ```cpp
    #include <PubSubClient.h>
    #include <rpcWiFi.h>
    #include <SPI.h>
    
    #include "config.h"
    ```

    ဒီ header ဖိုင်များသည် ယခင်ထည့်သွင်းထားသော libraries များမှ ကုဒ်များကို PlatformIO သို့ ဆွဲယူရန် လိုအပ်ပါသည်။ 

1. `setup` function အထက်တွင် အောက်ပါကုဒ်ကို ထည့်သွင်းပါ။

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

    ဒီကုဒ်သည် စက်ပစ္စည်းသည် WiFi နှင့် မချိတ်ဆက်မီ loop လုပ်ပြီး SSID နှင့် စကားဝှက်ကို အသုံးပြု၍ ချိတ်ဆက်ရန် ကြိုးစားပါသည်။

1. `setup` function ၏ အောက်ဆုံးတွင် pins များကို configure ပြီးနောက် ဤ function ကို ခေါ်ပါ။

    ```cpp
    connectWiFi();
    ```

1. WiFi ချိတ်ဆက်မှု အလုပ်လုပ်မှုကို စစ်ဆေးရန် ကုဒ်ကို သင့်စက်ပစ္စည်းသို့ upload လုပ်ပါ။ Serial monitor တွင် အောက်ပါအတိုင်း မြင်ရမည်ဖြစ်သည်။

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    ```

## MQTT နှင့် ချိတ်ဆက်ပါ

Wio Terminal သည် WiFi နှင့် ချိတ်ဆက်ပြီးနောက် MQTT broker နှင့် ချိတ်ဆက်နိုင်ပါသည်။

### လုပ်ငန်း - MQTT နှင့် ချိတ်ဆက်ပါ

MQTT broker နှင့် ချိတ်ဆက်ပါ။

1. MQTT broker ၏ ချိတ်ဆက်မှုအသေးစိတ်ကို သတ်မှတ်ရန် `config.h` ဖိုင်၏ အဆုံးတွင် အောက်ပါကုဒ်ကို ထည့်သွင်းပါ။

    ```cpp
    // MQTT settings
    const string ID = "<ID>";
    
    const string BROKER = "test.mosquitto.org";
    const string CLIENT_NAME = ID + "nightlight_client";
    ```

    `<ID>` ကို သင့်စက်ပစ္စည်း client ၏ အထူး ID ဖြင့် အစားထိုးပါ။ 

    > 💁 [GUIDGen](https://www.guidgen.com) ကဲ့သို့သော ဝဘ်ဆိုဒ်ကို အသုံးပြု၍ အထူး ID တစ်ခုကို ဖန်တီးနိုင်ပါသည်။

    `BROKER` သည် MQTT broker ၏ URL ဖြစ်သည်။

    `CLIENT_NAME` သည် broker ပေါ်တွင် MQTT client ၏ အထူးအမည်ဖြစ်သည်။

1. `main.cpp` ဖိုင်ကို ဖွင့်ပြီး `connectWiFi` function ၏ အောက်တွင် အောက်ပါကုဒ်ကို ထည့်သွင်းပါ။

    ```cpp
    WiFiClient wioClient;
    PubSubClient client(wioClient);
    ```

    ဒီကုဒ်သည် Wio Terminal WiFi libraries ကို အသုံးပြု၍ WiFi client တစ်ခု ဖန်တီးပြီး MQTT client တစ်ခု ဖန်တီးပါသည်။

1. အထက်ပါကုဒ်အောက်တွင် အောက်ပါကုဒ်ကို ထည့်သွင်းပါ။

    ```cpp
    void reconnectMQTTClient()
    {
        while (!client.connected())
        {
            Serial.print("Attempting MQTT connection...");
    
            if (client.connect(CLIENT_NAME.c_str()))
            {
                Serial.println("connected");
            }
            else
            {
                Serial.print("Retying in 5 seconds - failed, rc=");
                Serial.println(client.state());
                
                delay(5000);
            }
        }
    }
    ```

    ဒီ function သည် MQTT broker နှင့် ချိတ်ဆက်မှုကို စစ်ဆေးပြီး ချိတ်ဆက်မရပါက ပြန်လည်ချိတ်ဆက်ရန် ကြိုးစားပါသည်။

1. `reconnectMQTTClient` function ၏ အောက်တွင် အောက်ပါကုဒ်ကို ထည့်သွင်းပါ။

    ```cpp
    void createMQTTClient()
    {
        client.setServer(BROKER.c_str(), 1883);
        reconnectMQTTClient();
    }
    ```

    ဒီကုဒ်သည် MQTT broker ကို client အတွက် သတ်မှတ်ပြီး message လက်ခံသည့် callback ကို သတ်မှတ်ပါသည်။

1. WiFi ချိတ်ဆက်ပြီးနောက် `setup` function အတွင်း `createMQTTClient` function ကို ခေါ်ပါ။

1. `loop` function အား အောက်ပါအတိုင်း အစားထိုးပါ။

    ```cpp
    void loop()
    {
        reconnectMQTTClient();
        client.loop();
    
        delay(2000);
    }
    ```

    ဒီကုဒ်သည် MQTT broker နှင့် ချိတ်ဆက်မှုကို စစ်ဆေးပြီး လိုအပ်ပါက ပြန်လည်ချိတ်ဆက်ပါသည်။

1. ကုဒ်ကို Wio Terminal သို့ upload လုပ်ပြီး Serial Monitor ကို အသုံးပြု၍ WiFi နှင့် MQTT ချိတ်ဆက်မှုကို ကြည့်ရှုပါ။

    ```output
    > Executing task: platformio device monitor <
    
    source /Users/jimbennett/GitHub/IoT-For-Beginners/1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal/nightlight/.venv/bin/activate
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    ```

> 💁 ဒီကုဒ်ကို [code-mqtt/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal) ဖိုလ်ဒါတွင် ရှာနိုင်ပါသည်။

😀 သင့်စက်ပစ္စည်းကို MQTT broker နှင့် အောင်မြင်စွာ ချိတ်ဆက်ပြီးပါပြီ!

---

**အကြောင်းကြားချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှုအတွက် ကြိုးစားနေသော်လည်း၊ အလိုအလျောက် ဘာသာပြန်မှုများတွင် အမှားများ သို့မဟုတ် မတိကျမှုများ ပါဝင်နိုင်သည်ကို သတိပြုပါ။ မူရင်းစာရွက်စာတမ်းကို ၎င်း၏ မူရင်းဘာသာစကားဖြင့် အာဏာတရားရှိသော အရင်းအမြစ်အဖြစ် သတ်မှတ်သင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူ့ဘာသာပြန်ပညာရှင်များမှ ပရော်ဖက်ရှင်နယ် ဘာသာပြန်မှုကို အကြံပြုပါသည်။ ဤဘာသာပြန်မှုကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော အလွဲအလွတ်များ သို့မဟုတ် အနားလွဲမှုများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။