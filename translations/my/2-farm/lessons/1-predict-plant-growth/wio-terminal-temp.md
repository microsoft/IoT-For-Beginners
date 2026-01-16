<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "59263d094f20b302053888cd236880c3",
  "translation_date": "2025-08-28T18:12:04+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp.md",
  "language_code": "my"
}
-->
# အပူချိန်တိုင်းတာခြင်း - Wio Terminal

ဒီသင်ခန်းစာအပိုင်းမှာ သင့် Wio Terminal ကို အပူချိန်အာရုံခံကိရိယာတစ်ခု ထည့်သွင်းပြီး၊ အပူချိန်တန်ဖိုးများကို ဖတ်ရှုမည်ဖြစ်သည်။

## ဟာ့ဒ်ဝဲ

Wio Terminal အတွက် အပူချိန်အာရုံခံကိရိယာလိုအပ်သည်။

သင်အသုံးပြုမည့်အာရုံခံကိရိယာမှာ [DHT11 အပူချိန်နှင့် စိုထိုင်းဆ](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html) အာရုံခံကိရိယာဖြစ်ပြီး၊ အာရုံခံကိရိယာ ၂ ခုကို တစ်ခုတည်းအထုပ်ထဲတွင် ပေါင်းစပ်ထားသည်။ ၎င်းသည် အလွန်လူကြိုက်များပြီး၊ အပူချိန်၊ စိုထိုင်းဆနှင့် တစ်ခါတစ်ရံ လေထုဖိအားကို ပေါင်းစပ်ထားသော ကိရိယာများကို ကုန်သွယ်စျေးကွက်တွင် ရရှိနိုင်သည်။ အပူချိန်အာရုံခံကိရိယာအစိတ်အပိုင်းမှာ အပူချိန်တက်လာသည်နှင့်အမျှ အားပြတ်မှုလျော့ကျသည့် NTC (Negative Temperature Coefficient) thermistor ဖြစ်သည်။

ဤသည်မှာ ဒစ်ဂျစ်တယ်အာရုံခံကိရိယာဖြစ်ပြီး၊ အပူချိန်နှင့် စိုထိုင်းဆဒေတာပါဝင်သော ဒစ်ဂျစ်တယ် signal ကို microcontroller ဖတ်ရှုနိုင်ရန် onboard ADC ပါရှိသည်။

### အပူချိန်အာရုံခံကိရိယာကို ချိတ်ဆက်ပါ

Grove အပူချိန်အာရုံခံကိရိယာကို Wio Terminal ၏ ဒစ်ဂျစ်တယ်ပေါက်တွင် ချိတ်ဆက်နိုင်သည်။

#### လုပ်ငန်း - အပူချိန်အာရုံခံကိရိယာကို ချိတ်ဆက်ပါ

အပူချိန်အာရုံခံကိရိယာကို ချိတ်ဆက်ပါ။

![A grove temperature sensor](../../../../../translated_images/my/grove-dht11.07f8eafceee170043efbb53e1d15722bd4e00fbaa9ff74290b57e9f66eb82c17.png)

1. Grove cable ၏ တစ်ဖက်အဆုံးကို စိုထိုင်းဆနှင့် အပူချိန်အာရုံခံကိရိယာ၏ socket တွင် ထည့်ပါ။ ၎င်းသည် တစ်ဖက်ဘက်သာ ထည့်နိုင်ပါမည်။

1. Wio Terminal ကို သင့်ကွန်ပျူတာ သို့မဟုတ် အခြား power supply မှ ချိတ်ဆက်ထားခြင်းမရှိဘဲ၊ Grove cable ၏ အခြားဖက်အဆုံးကို Wio Terminal ၏ screen ကိုကြည့်နေသောအခါ ညာဘက် Grove socket တွင် ချိတ်ဆက်ပါ။ ၎င်းသည် power button မှ အဝေးဆုံးရှိ socket ဖြစ်သည်။

![The grove temperature sensor connected to the right hand socket](../../../../../translated_images/my/wio-temperature-sensor.2934928f38c7f79a.webp)

## အပူချိန်အာရုံခံကိရိယာကို အစီအစဉ်ရေးဆွဲပါ

Wio Terminal ကို ယခုချိတ်ဆက်ထားသော အပူချိန်အာရုံခံကိရိယာကို အသုံးပြုရန် အစီအစဉ်ရေးဆွဲနိုင်ပါပြီ။

### လုပ်ငန်း - အပူချိန်အာရုံခံကိရိယာကို အစီအစဉ်ရေးဆွဲပါ

Device ကို အစီအစဉ်ရေးဆွဲပါ။

1. PlatformIO ကို အသုံးပြု၍ Wio Terminal project အသစ်တစ်ခု ဖန်တီးပါ။ ဤ project ကို `temperature-sensor` ဟု အမည်ပေးပါ။ `setup` function တွင် serial port ကို configure လုပ်ရန် code ထည့်ပါ။

    > ⚠️ [Project 1, Lesson 1 တွင် PlatformIO project ဖန်တီးရန် လမ်းညွှန်ချက်များကို လိုအပ်ပါက ပြန်လည်ကြည့်ရှုနိုင်သည်](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project)။

1. Project ၏ `platformio.ini` ဖိုင်တွင် Seeed Grove Humidity and Temperature sensor library အတွက် library dependency ကို ထည့်ပါ။

    ```ini
    lib_deps =
        seeed-studio/Grove Temperature And Humidity Sensor @ 1.0.1
    ```

    > ⚠️ [Project 1, Lesson 4 တွင် PlatformIO project တွင် libraries ထည့်ရန် လမ်းညွှန်ချက်များကို လိုအပ်ပါက ပြန်လည်ကြည့်ရှုနိုင်သည်](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md#install-the-wifi-and-mqtt-arduino-libraries)။

1. ရှိပြီးသား `#include <Arduino.h>` အောက်တွင် အောက်ပါ `#include` directives များကို ထည့်ပါ။

    ```cpp
    #include <DHT.h>
    #include <SPI.h>
    ```

    ဤသည်မှာ sensor နှင့် ဆက်သွယ်ရန် လိုအပ်သော ဖိုင်များကို import လုပ်သည်။ `DHT.h` header file တွင် sensor ကို အသုံးပြုရန် code ပါရှိပြီး၊ `SPI.h` header ကို ထည့်သွင်းခြင်းဖြင့် app ကို compile လုပ်သောအခါ sensor နှင့် ဆက်သွယ်ရန် လိုအပ်သော code ကို link လုပ်ပေးသည်။

1. `setup` function မတိုင်မီ DHT sensor ကို ကြေညာပါ။

    ```cpp
    DHT dht(D0, DHT11);
    ```

    ဤသည်မှာ **D**igital **H**umidity နှင့် **T**emperature sensor ကို စီမံခန့်ခွဲရန် `DHT` class ၏ instance တစ်ခုကို ကြေညာသည်။ ၎င်းသည် Wio Terminal ၏ ညာဘက် Grove socket ဖြစ်သော port `D0` တွင် ချိတ်ဆက်ထားသည်။ ဒုတိယ parameter သည် အသုံးပြုနေသော sensor သည် *DHT11* sensor ဖြစ်ကြောင်း code ကို ပြောပြသည် - သင်အသုံးပြုနေသော library သည် sensor ၏ အခြား variant များကိုလည်း ပံ့ပိုးသည်။

1. `setup` function တွင် serial connection ကို set up လုပ်ရန် code ထည့်ပါ။

    ```cpp
    void setup()
    {
        Serial.begin(9600);
    
        while (!Serial)
            ; // Wait for Serial to be ready
    
        delay(1000);
    }
    ```

1. `setup` function ၏ နောက်ဆုံး `delay` အပြီးတွင် DHT sensor ကို စတင်ရန် call ထည့်ပါ။

    ```cpp
    dht.begin();
    ```

1. `loop` function တွင် sensor ကို call လုပ်ပြီး serial port တွင် အပူချိန်ကို print လုပ်ရန် code ထည့်ပါ။

    ```cpp
    void loop()
    {
        float temp_hum_val[2] = {0};
        dht.readTempAndHumidity(temp_hum_val);
        Serial.print("Temperature: ");
        Serial.print(temp_hum_val[1]);
        Serial.println ("°C");
    
        delay(10000);
    }
    ```

    ဤ code သည် float 2 ခုပါဝင်သော အလွတ် array တစ်ခုကို ကြေညာပြီး၊ ၎င်းကို `DHT` instance တွင် `readTempAndHumidity` ကို call လုပ်သောအခါ pass လုပ်သည်။ ဤ call သည် array ကို 2 values ဖြင့် populate လုပ်သည် - humidity သည် array ၏ 0th item (C++ arrays သည် 0-based ဖြစ်သောကြောင့် 0th item သည် array ၏ 'ပထမ' item ဖြစ်သည်) တွင်သွားပြီး၊ အပူချိန်သည် 1st item တွင်သွားသည်။

    အပူချိန်ကို array ၏ 1st item မှ ဖတ်ပြီး၊ serial port တွင် print လုပ်သည်။

    > 🇺🇸 အပူချိန်ကို Celsius ဖြင့် ဖတ်သည်။ အမေရိကန်များအတွက်၊ ဤ Celsius တန်ဖိုးကို Fahrenheit သို့ ပြောင်းရန် Celsius တန်ဖိုးကို 5 ဖြင့်စားပြီး၊ 9 ဖြင့်မြှောက်ပြီး၊ 32 ကိုထည့်ပါ။ ဥပမာအားဖြင့် 20°C အပူချိန်ဖတ်ရှုမှုသည် ((20/5)*9) + 32 = 68°F ဖြစ်သည်။

1. Code ကို build လုပ်ပြီး Wio Terminal သို့ upload လုပ်ပါ။

    > ⚠️ [Project 1, Lesson 1 တွင် PlatformIO project ဖန်တီးရန် လမ်းညွှန်ချက်များကို လိုအပ်ပါက ပြန်လည်ကြည့်ရှုနိုင်သည်](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app)။

1. Upload လုပ်ပြီးပါက serial monitor ကို အသုံးပြု၍ အပူချိန်ကို ကြည့်ရှုနိုင်သည်။

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Temperature: 25.00°C
    Temperature: 25.00°C
    Temperature: 25.00°C
    Temperature: 24.00°C
    ```

> 💁 ဤ code ကို [code-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/wio-terminal) folder တွင် ရှာနိုင်သည်။

😀 သင့်အပူချိန်အာရုံခံကိရိယာအစီအစဉ်အောင်မြင်ခဲ့ပါပြီ!

---

**အကြောင်းကြားချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှုအတွက် ကြိုးစားနေသော်လည်း၊ အလိုအလျောက် ဘာသာပြန်မှုများတွင် အမှားများ သို့မဟုတ် မမှန်ကန်မှုများ ပါဝင်နိုင်သည်ကို သတိပြုပါ။ မူရင်းစာရွက်စာတမ်းကို ၎င်း၏ မူရင်းဘာသာစကားဖြင့် အာဏာတရားရှိသော အရင်းအမြစ်အဖြစ် ရှုလေ့လာသင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူက ဘာသာပြန်မှု ဝန်ဆောင်မှုကို အသုံးပြုရန် အကြံပြုပါသည်။ ဤဘာသာပြန်မှုကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော အလွဲအလွတ်များ သို့မဟုတ် အနားလွဲမှုများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။