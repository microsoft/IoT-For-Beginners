<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "da6ae0a795cf06be33d23ca5b8493fc8",
  "translation_date": "2025-08-28T16:47:13+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-sensor.md",
  "language_code": "my"
}
-->
# GPS ဒေတာဖတ်ရန် - Wio Terminal

ဒီသင်ခန်းစာအပိုင်းမှာ၊ သင့် Wio Terminal တွင် GPS ဆင်ဆာတစ်ခုထည့်ပြီး၊ ဒေတာများကိုဖတ်မည်ဖြစ်သည်။

## ဟာ့ဒ်ဝဲ

Wio Terminal သည် GPS ဆင်ဆာတစ်ခုလိုအပ်သည်။

သင်အသုံးပြုမည့်ဆင်ဆာမှာ [Grove GPS Air530 sensor](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html) ဖြစ်သည်။ ဒီဆင်ဆာသည် GPS စနစ်အမျိုးမျိုးနှင့် ချိတ်ဆက်နိုင်ပြီး မြန်ဆန်ပြီး တိကျသော ဒေတာများကို ရယူနိုင်သည်။ ဆင်ဆာသည် အစိတ်အပိုင်း ၂ ခုဖြင့် ဖွဲ့စည်းထားပြီး - ဆင်ဆာ၏ အဓိကအီလက်ထရွန်းနစ်အစိတ်အပိုင်းနှင့် အင်တင်နာတစ်ခုကို ပါးလွှာသောဝါယာကြိုးဖြင့် ချိတ်ဆက်ထားသည်။ အင်တင်နာသည် ဂြိုလ်တုမှ ရေဒီယိုလှိုင်းများကို ဖမ်းဆီးရန်အတွက် အသုံးပြုသည်။

ဒီဆင်ဆာသည် UART ဆင်ဆာဖြစ်ပြီး၊ GPS ဒေတာကို UART မှတဆင့် ပေးပို့သည်။

### GPS ဆင်ဆာကို ချိတ်ဆက်ပါ

Grove GPS ဆင်ဆာကို Wio Terminal နှင့် ချိတ်ဆက်နိုင်သည်။

#### လုပ်ငန်းစဉ် - GPS ဆင်ဆာကို ချိတ်ဆက်ပါ

GPS ဆင်ဆာကို ချိတ်ဆက်ပါ။

![A grove GPS sensor](../../../../../translated_images/grove-gps-sensor.247943bf69b03f0d1820ef6ed10c587f9b650e8db55b936851c92412180bd3e2.my.png)

1. Grove ကေဘယ်တစ်ခု၏ တစ်ဖက်အဆုံးကို GPS ဆင်ဆာရှိ ဆော့ကက်ထဲသို့ ထည့်ပါ။ ၎င်းသည် တစ်ဖက်ဘက်သာ အလွယ်တကူ ထည့်နိုင်ပါမည်။

1. Wio Terminal ကို သင့်ကွန်ပျူတာ သို့မဟုတ် အခြားပါဝါထောက်ပံ့မှုမှ ဖြုတ်ထားပြီးဖြစ်ပါက၊ Grove ကေဘယ်၏ အခြားဖက်အဆုံးကို Wio Terminal ၏ ဘယ်ဖက်ရှိ Grove ဆော့ကက် (မော်နီတာကိုကြည့်နေစဉ်) တွင် ချိတ်ဆက်ပါ။ ၎င်းသည် ပါဝါခလုတ်အနီးရှိ ဆော့ကက်ဖြစ်သည်။

    ![The grove GPS sensor connected to the left hand socket](../../../../../translated_images/wio-gps-sensor.19fd52b81ce58095.my.png)

1. GPS ဆင်ဆာကို အင်တင်နာတပ်ဆင်ထားသောနေရာသည် ကောင်းကင်ကို မြင်နိုင်သောနေရာတွင်ထားပါ - အကောင်းဆုံးအနေဖြင့် ပြတင်းပေါက်အနီး သို့မဟုတ် အပြင်ဘက်တွင်ထားပါ။ အင်တင်နာကို အတားအဆီးမရှိသောနေရာတွင်ထားခြင်းဖြင့် သင့်အတွက် ပိုမိုကောင်းမွန်သော သင်္ကေတကို ရယူနိုင်ပါမည်။

1. ယခု Wio Terminal ကို သင့်ကွန်ပျူတာနှင့် ချိတ်ဆက်နိုင်ပါပြီ။

1. GPS ဆင်ဆာတွင် LED ၂ ခုရှိသည် - ဒေတာပေးပို့နေစဉ် လင်းပွင့်သော အပြာရောင် LED တစ်ခုနှင့် ဂြိုလ်တုမှ ဒေတာလက်ခံနေစဉ် တစ်စက္ကန့်တစ်ကြိမ် လင်းပွင့်သော အစိမ်းရောင် LED တစ်ခု။ Wio Terminal ကို ဖွင့်လိုက်သောအခါ အပြာရောင် LED လင်းပွင့်နေကြောင်း သေချာပါ။ မိနစ်အနည်းငယ်အကြာတွင် အစိမ်းရောင် LED လင်းပွင့်ပါမည် - မဟုတ်ပါက အင်တင်နာ၏နေရာကို ပြောင်းရန် လိုအပ်နိုင်ပါသည်။

## GPS ဆင်ဆာကို ပရိုဂရမ်ရေးရန်

ယခု Wio Terminal ကို GPS ဆင်ဆာနှင့် အသုံးပြုရန် ပရိုဂရမ်ရေးနိုင်ပါပြီ။

### လုပ်ငန်းစဉ် - GPS ဆင်ဆာကို ပရိုဂရမ်ရေးပါ

စက်ကို ပရိုဂရမ်ရေးပါ။

1. PlatformIO ကို အသုံးပြု၍ Wio Terminal စီမံကိန်းအသစ်တစ်ခု ဖန်တီးပါ။ ဒီစီမံကိန်းကို `gps-sensor` ဟု အမည်ပေးပါ။ `setup` ဖောင်ရှင်းတွင် serial port ကို ပြင်ဆင်ရန် ကုဒ်ထည့်ပါ။

1. `main.cpp` ဖိုင်၏ အပေါ်ဆုံးတွင် အောက်ပါ include directive ကို ထည့်ပါ။ ၎င်းသည် UART အတွက် ဘယ်ဖက်ရှိ Grove ဆော့ကက်ကို ပြင်ဆင်ရန် လိုအပ်သော header ဖိုင်ကို ထည့်သွင်းသည်။

    ```cpp
    #include <wiring_private.h>
    ```

1. ထို့နောက်၊ UART port နှင့် serial port ချိတ်ဆက်မှုကို ကြေငြာရန် အောက်ပါကုဒ်တစ်ကြောင်းကို ထည့်ပါ။

    ```cpp
    static Uart Serial3(&sercom3, PIN_WIRE_SCL, PIN_WIRE_SDA, SERCOM_RX_PAD_1, UART_TX_PAD_0);
    ```

1. Internal signal handlers အချို့ကို ဒီ serial port သို့ redirect လုပ်ရန် ကုဒ်တစ်ချို့ ထည့်ရန် လိုအပ်သည်။ `Serial3` ကြေငြာချက်အောက်တွင် အောက်ပါကုဒ်ကို ထည့်ပါ။

    ```cpp
    void SERCOM3_0_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_1_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_2_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_3_Handler()
    {
        Serial3.IrqHandler();
    }
    ```

1. `setup` ဖောင်ရှင်းတွင် `Serial` port ကို ပြင်ဆင်ထားသောနေရာအောက်တွင်၊ UART serial port ကို အောက်ပါကုဒ်ဖြင့် ပြင်ဆင်ပါ။

    ```cpp
    Serial3.begin(9600);

    while (!Serial3)
        ; // Wait for Serial3 to be ready

    delay(1000);
    ```

1. ဒီကုဒ်အောက်တွင် `setup` ဖောင်ရှင်းတွင် Grove pin ကို serial port နှင့် ချိတ်ဆက်ရန် အောက်ပါကုဒ်ကို ထည့်ပါ။

    ```cpp
    pinPeripheral(PIN_WIRE_SCL, PIO_SERCOM_ALT);
    ```

1. `loop` ဖောင်ရှင်းမတိုင်မီ အောက်ပါဖောင်ရှင်းကို ထည့်ပါ၊ GPS ဒေတာကို serial monitor သို့ ပေးပို့ရန် အသုံးပြုပါမည်။

    ```cpp
    void printGPSData()
    {
        Serial.println(Serial3.readStringUntil('\n'));
    }
    ```

1. `loop` ဖောင်ရှင်းတွင် UART serial port မှ ဖတ်ပြီး serial monitor သို့ output ပေးရန် အောက်ပါကုဒ်ကို ထည့်ပါ။

    ```cpp
    while (Serial3.available() > 0)
    {
        printGPSData();
    }
    
    delay(1000);
    ```

    ဒီကုဒ်သည် UART serial port မှ ဖတ်သည်။ `readStringUntil` ဖောင်ရှင်းသည် terminator အက္ခရာ (ဒီအခါတွင် new line) အထိ ဖတ်သည်။ ၎င်းသည် တစ်ကြောင်းစာလုံးစုံသော NMEA စာကြောင်းကို ဖတ်မည်ဖြစ်သည် (NMEA စာကြောင်းများသည် new line အက္ခရာဖြင့် အဆုံးသတ်သည်။) UART serial port မှ ဒေတာများကို ဖတ်နိုင်သမျှ ဖတ်ပြီး၊ `printGPSData` ဖောင်ရှင်းမှတဆင့် serial monitor သို့ ပေးပို့သည်။ ဖတ်နိုင်သော ဒေတာမရှိတော့ပါက၊ `loop` သည် ၁ စက္ကန့် (၁,၀၀၀ms) ခေတ္တရပ်နေသည်။

1. ကုဒ်ကို Wio Terminal သို့ Build နှင့် Upload လုပ်ပါ။

1. Upload ပြီးပါက၊ serial monitor ကို အသုံးပြု၍ GPS ဒေတာကို ကြည့်နိုင်ပါသည်။

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GPGSA,A,1,,,,,,,,,,,,,,,*1E
    $BDGSA,A,1,,,,,,,,,,,,,,,*0F
    $GPGSV,1,1,00*79
    $BDGSV,1,1,00*68
    ```

> 💁 ဒီကုဒ်ကို [code-gps/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps/wio-terminal) ဖိုလ်ဒါတွင် ရှာနိုင်ပါသည်။

😀 သင့် GPS ဆင်ဆာပရိုဂရမ်အောင်မြင်ခဲ့ပါပြီ!

---

**အကြောင်းကြားချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှုအတွက် ကြိုးစားနေသော်လည်း၊ အလိုအလျောက် ဘာသာပြန်မှုများတွင် အမှားများ သို့မဟုတ် မတိကျမှုများ ပါဝင်နိုင်သည်ကို သတိပြုပါ။ မူရင်းဘာသာစကားဖြင့် ရေးသားထားသော စာရွက်စာတမ်းကို အာဏာတရ အရင်းအမြစ်အဖြစ် သတ်မှတ်သင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူ့ဘာသာပြန်ပညာရှင်များမှ ပရော်ဖက်ရှင်နယ် ဘာသာပြန်မှုကို အကြံပြုပါသည်။ ဤဘာသာပြန်မှုကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော အလွဲအလွတ်များ သို့မဟုတ် အနားယူမှုမှားများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။