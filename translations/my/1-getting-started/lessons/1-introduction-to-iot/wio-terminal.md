<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a4f0c166010e31fd7b6ca20bc88dec6d",
  "translation_date": "2025-08-28T17:21:29+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md",
  "language_code": "my"
}
-->
# Wio Terminal

[Seeed Studios မှ Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html) သည် Arduino-compatible microcontroller တစ်ခုဖြစ်ပြီး WiFi နှင့် sensor များ၊ actuator များပါဝင်သည့်အပြင် [Grove](https://www.seeedstudio.com/category/Grove-c-1003.html) ဟုခေါ်သော hardware ecosystem ကို အသုံးပြု၍ sensor များနှင့် actuator များကို ထပ်မံထည့်သွင်းနိုင်သော port များပါရှိသည်။

![Seeed Studios Wio Terminal](../../../../../translated_images/wio-terminal.b8299ee16587db9a.my.png)

## Setup

Wio Terminal ကို အသုံးပြုရန်အတွက် သင့်ကွန်ပျူတာတွင် အခမဲ့ software များကို ထည့်သွင်းရန်လိုအပ်ပါသည်။ WiFi သို့ ချိတ်ဆက်နိုင်ရန်အတွက် Wio Terminal firmware ကို update လုပ်ရန်လည်း လိုအပ်ပါသည်။

### Task - setup

လိုအပ်သော software များကို ထည့်သွင်းပြီး firmware ကို update လုပ်ပါ။

1. Visual Studio Code (VS Code) ကို ထည့်သွင်းပါ။ သင့် device code ကို C/C++ ဖြင့် ရေးသားရန် အသုံးပြုမည့် editor ဖြစ်ပါသည်။ VS Code ကို ထည့်သွင်းရန်အတွက် [VS Code documentation](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) ကို ရည်ညွှန်းပါ။

    > 💁 Arduino development အတွက် နောက်ထပ် လူကြိုက်များသော IDE တစ်ခုမှာ [Arduino IDE](https://www.arduino.cc/en/software) ဖြစ်ပါသည်။ သင်ဤ tool ကို ရင်းနှီးပြီးသားဖြစ်ပါက VS Code နှင့် PlatformIO အစား အသုံးပြုနိုင်ပါသည်။ သို့သော် သင်ခန်းစာများတွင် VS Code ကို အသုံးပြုခြင်းအပေါ် အခြေခံထားသော လမ်းညွှန်ချက်များကို ပေးပါမည်။

1. VS Code PlatformIO extension ကို ထည့်သွင်းပါ။ ဤ extension သည် VS Code အတွက် C/C++ ဖြင့် microcontroller များကို programming လုပ်ရန် အထောက်အကူပြုသော extension ဖြစ်ပါသည်။ VS Code တွင် ဤ extension ကို ထည့်သွင်းရန်အတွက် [PlatformIO extension documentation](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=platformio.platformio-ide) ကို ရည်ညွှန်းပါ။ ဤ extension သည် Microsoft C/C++ extension ကို အလိုအလျောက် ထည့်သွင်းပြီး C နှင့် C++ code များနှင့် အလုပ်လုပ်ရန်လိုအပ်ပါသည်။

1. Wio Terminal ကို သင့်ကွန်ပျူတာနှင့် ချိတ်ဆက်ပါ။ Wio Terminal တွင် အောက်ခြေတွင် USB-C port တစ်ခုရှိပြီး သင့်ကွန်ပျူတာ၏ USB port နှင့် ချိတ်ဆက်ရန်လိုအပ်ပါသည်။ Wio Terminal တွင် USB-C to USB-A cable ပါဝင်ပြီး သင့်ကွန်ပျူတာတွင် USB-C port များသာရှိပါက USB-C cable သို့မဟုတ် USB-A to USB-C adapter တစ်ခုလိုအပ်ပါသည်။

1. [Wio Terminal Wiki WiFi Overview documentation](https://wiki.seeedstudio.com/Wio-Terminal-Network-Overview/) တွင် ရှိသော လမ်းညွှန်ချက်များကို လိုက်နာပြီး Wio Terminal ကို setup လုပ်ကာ firmware ကို update လုပ်ပါ။

## Hello world

Programming language သို့မဟုတ် နည်းပညာအသစ်တစ်ခုကို စတင်အသုံးပြုသောအခါ "Hello World" application တစ်ခုကို ဖန်တီးခြင်းသည် ရိုးရာဖြစ်ပါသည်။ ဤ application သည် `"Hello World"` စာသားကို output ပြုလုပ်ပြီး tool များအားလုံးကို မှန်ကန်စွာ configure လုပ်ထားကြောင်း ပြသပါသည်။

Wio Terminal အတွက် Hello World app သည် Visual Studio Code ကို PlatformIO ဖြင့် microcontroller development အတွက် မှန်ကန်စွာ ထည့်သွင်းထားကြောင်း သေချာစေပါသည်။

### Create a PlatformIO project

ပထမဆုံးအဆင့်မှာ Wio Terminal အတွက် configure လုပ်ထားသော PlatformIO project တစ်ခုကို ဖန်တီးပါ။

#### Task - create a PlatformIO project

PlatformIO project ကို ဖန်တီးပါ။

1. Wio Terminal ကို သင့်ကွန်ပျူတာနှင့် ချိတ်ဆက်ပါ။

1. VS Code ကို ဖွင့်ပါ။

1. PlatformIO icon သည် ဘေး menu bar တွင် ရှိပါမည်။

    ![Platform IO menu option](../../../../../translated_images/vscode-platformio-menu.297be26b9733e5c4.my.png)

    ဤ menu item ကို ရွေးချယ်ပြီး *PIO Home -> Open* ကို ရွေးပါ။

    ![Platform IO open option](../../../../../translated_images/vscode-platformio-home-open.3f9a41bfd3f4da1c.my.png)

1. Welcome screen မှ **+ New Project** ခလုတ်ကို ရွေးချယ်ပါ။

    ![New project button](../../../../../translated_images/vscode-platformio-welcome-new-button.ba6fc8a4c7b78cc8.my.png)

1. *Project Wizard* တွင် project ကို configure လုပ်ပါ။

    1. သင့် project ကို `nightlight` ဟု အမည်ပေးပါ။

    1. *Board* dropdown မှ `WIO` ဟု ရိုက်ထည့်ကာ board များကို filter လုပ်ပြီး *Seeeduino Wio Terminal* ကို ရွေးပါ။

    1. *Framework* ကို *Arduino* အဖြစ်ထားပါ။

    1. *Use default location* checkbox ကို check လုပ်ထားပါ၊ သို့မဟုတ် uncheck လုပ်ပြီး သင့် project အတွက် location တစ်ခုကို ရွေးပါ။

    1. **Finish** ခလုတ်ကို ရွေးပါ။

    ![Completed project wizard](../../../../../translated_images/vscode-platformio-nightlight-project-wizard.5c64db4da6037420.my.png)

    PlatformIO သည် Wio Terminal အတွက် code ကို compile လုပ်ရန်လိုအပ်သော components များကို download လုပ်ပြီး သင့် project ကို ဖန်တီးပါမည်။ ဤလုပ်ငန်းစဉ်သည် မိနစ်အနည်းငယ်ကြာနိုင်ပါသည်။

### Investigate the PlatformIO project

VS Code explorer တွင် PlatformIO wizard ဖန်တီးထားသော file များနှင့် folder များကို ပြသပါမည်။

#### Folders

* `.pio` - ဤ folder တွင် PlatformIO အတွက် libraries သို့မဟုတ် compiled code ကဲ့သို့သော ယာယီ data များပါရှိသည်။ ဖျက်လိုက်ပါက အလိုအလျောက် ပြန်ဖန်တီးမည်ဖြစ်ပြီး GitHub ကဲ့သို့သော site များတွင် project ကို share လုပ်သောအခါ source code control တွင် ထည့်သွင်းရန် မလိုအပ်ပါ။
* `.vscode` - ဤ folder တွင် PlatformIO နှင့် VS Code အတွက် configuration များပါရှိသည်။ ဖျက်လိုက်ပါက အလိုအလျောက် ပြန်ဖန်တီးမည်ဖြစ်ပြီး GitHub ကဲ့သို့သော site များတွင် project ကို share လုပ်သောအခါ source code control တွင် ထည့်သွင်းရန် မလိုအပ်ပါ။
* `include` - ဤ folder သည် သင့် code တွင် ထည့်သွင်းထားသော libraries များအတွက် external header file များအတွက် ဖြစ်သည်။ ဤသင်ခန်းစာများတွင် folder ကို အသုံးမပြုပါ။
* `lib` - ဤ folder သည် သင့် code မှ ခေါ်ယူလိုသော external libraries များအတွက် ဖြစ်သည်။ ဤသင်ခန်းစာများတွင် folder ကို အသုံးမပြုပါ။
* `src` - ဤ folder တွင် သင့် application အတွက် main source code ပါရှိသည်။ အစပိုင်းတွင် `main.cpp` file တစ်ခုသာ ပါရှိမည်။
* `test` - ဤ folder သည် သင့် code အတွက် unit tests များကို ထည့်သွင်းရန်အတွက် ဖြစ်သည်။

#### Files

* `main.cpp` - `src` folder တွင်ပါရှိသော ဤ file သည် သင့် application အတွက် entry point ဖြစ်သည်။ ဤ file ကို ဖွင့်ပါက အောက်ပါ code ပါရှိမည်။

    ```cpp
    #include <Arduino.h>
    
    void setup() {
      // put your setup code here, to run once:
    }
    
    void loop() {
      // put your main code here, to run repeatedly:
    }
    ```

    Device စတင်လုပ်ဆောင်သောအခါ Arduino framework သည် `setup` function ကို တစ်ကြိမ် run လုပ်ပြီး `loop` function ကို device ပိတ်သွားသည်အထိ ထပ်တလဲလဲ run လုပ်ပါမည်။

* `.gitignore` - ဤ file တွင် GitHub ကဲ့သို့သော repository တွင် code ကို upload လုပ်သောအခါ git source code control တွင် မထည့်သွင်းရန် files နှင့် directories များကို ဖော်ပြထားသည်။

* `platformio.ini` - ဤ file တွင် သင့် device နှင့် app အတွက် configuration ပါရှိသည်။ ဤ file ကို ဖွင့်ပါက အောက်ပါ code ပါရှိမည်။

    ```ini
    [env:seeed_wio_terminal]
    platform = atmelsam
    board = seeed_wio_terminal
    framework = arduino
    ```

    `[env:seeed_wio_terminal]` section တွင် Wio Terminal အတွက် configuration ပါရှိသည်။ သင့် code ကို multiple boards အတွက် compile လုပ်နိုင်ရန် multiple `env` section များကို ထည့်သွင်းနိုင်ပါသည်။

    အခြား value များသည် project wizard မှ configuration နှင့် ကိုက်ညီပါသည်။

  * `platform = atmelsam` သည် Wio Terminal အသုံးပြုသော hardware ကို သတ်မှတ်သည် (ATSAMD51-based microcontroller)
  * `board = seeed_wio_terminal` သည် microcontroller board အမျိုးအစားကို သတ်မှတ်သည် (Wio Terminal)
  * `framework = arduino` သည် project သည် Arduino framework ကို အသုံးပြုနေသည်ကို သတ်မှတ်သည်။

### Write the Hello World app

Hello World app ကို ရေးသားရန် အဆင်သင့်ဖြစ်ပါပြီ။

#### Task - write the Hello World app

Hello World app ကို ရေးသားပါ။

1. VS Code တွင် `main.cpp` file ကို ဖွင့်ပါ။

1. Code ကို အောက်ပါအတိုင်း ပြောင်းလဲပါ။

    ```cpp
    #include <Arduino.h>

    void setup()
    {
        Serial.begin(9600);

        while (!Serial)
            ; // Wait for Serial to be ready
    
        delay(1000);
    }
    
    void loop()
    {
        Serial.println("Hello World");
        delay(5000);
    }
    ```

    `setup` function သည် serial port (ဤကိစ္စတွင် USB port) နှင့် ချိတ်ဆက်မှုကို initialize လုပ်ပါသည်။ `9600` parameter သည် [baud rate](https://wikipedia.org/wiki/Symbol_rate) (Symbol rate ဟုလည်းခေါ်သည်) သို့မဟုတ် serial port မှတဆင့် data ပို့ပေးမည့်အမြန်နှုန်းကို သတ်မှတ်သည်။ ဤ setting သည် တစ်စက္ကန့်လျှင် 9,600 bits (0s နှင့် 1s) ပို့ပေးသည်ကို ဆိုလိုသည်။ ထို့နောက် serial port အဆင်သင့်ဖြစ်ရန် စောင့်ပါသည်။

    `loop` function သည် `Hello World!` စာသားကို serial port သို့ ပို့ပေးပြီး newline character ကို ထည့်သွင်းပါသည်။ ထို့နောက် 5,000 milliseconds (5 seconds) အိပ်စက်ပါသည်။ `loop` function ပြီးဆုံးသောအခါ device ပိတ်သွားသည်အထိ ထပ်တလဲလဲ run လုပ်ပါမည်။

1. Wio Terminal ကို upload mode သို့ ပြောင်းပါ။ Device သို့ code အသစ် upload လုပ်သောအခါတိုင်း ဤလုပ်ငန်းစဉ်ကို ပြုလုပ်ရန်လိုအပ်ပါသည်။

    1. Power switch ကို အလျင်အမြန် နှစ်ကြိမ် ဆွဲချပါ - switch သည် အစအနေအတိုင်း ပြန်တက်ပါမည်။

    1. USB port ၏ ညာဘက်တွင်ရှိသော blue status LED ကို စစ်ဆေးပါ။ LED သည် pulsing ဖြစ်ရမည်။
    
    [![Wio Terminal ကို upload mode သို့ ပြောင်းရန် ဗီဒီယို](https://img.youtube.com/vi/LeKU_7zLRrQ/0.jpg)](https://youtu.be/LeKU_7zLRrQ)
    
    ဤလုပ်ငန်းစဉ်ကို ပြုလုပ်ပုံကို ပြသထားသော ဗီဒီယိုကို ကြည့်ရန် အထက်ပါပုံကို click လုပ်ပါ။

1. Code ကို build လုပ်ပြီး Wio Terminal သို့ upload လုပ်ပါ။

    1. VS Code command palette ကို ဖွင့်ပါ။

    1. `PlatformIO Upload` ဟု ရိုက်ထည့်ကာ upload option ကို ရှာပြီး *PlatformIO: Upload* ကို ရွေးပါ။

        ![PlatformIO upload option in command palette](../../../../../translated_images/vscode-platformio-upload-command-palette.9e0f49cf80d1f1c3.my.png)

        PlatformIO သည် upload လုပ်ရန်အလိုအလျောက် code ကို build လုပ်ပါမည်။

    1. Code ကို compile လုပ်ပြီး Wio Terminal သို့ upload လုပ်ပါမည်။

        > 💁 macOS အသုံးပြုပါက *DISK NOT EJECTED PROPERLY* ဟု notification တစ်ခု ပေါ်လာနိုင်ပါသည်။ ဤ notification သည် flashing လုပ်ငန်းစဉ်၏ အစိတ်အပိုင်းအဖြစ် drive အနေဖြင့် mount လုပ်ထားသော Wio Terminal ကို compiled code ရေးသားသောအခါ disconnect လုပ်သွားသောကြောင့် ဖြစ်သည်။ ဤ notification ကို လုံးဝလျစ်လျူရှုနိုင်ပါသည်။

    ⚠️ Upload port မရရှိနိုင်ကြောင်း error ပေါ်လာပါက Wio Terminal ကို သင့်ကွန်ပျူတာနှင့် ချိတ်ဆက်ထားပြီး screen ၏ ဘယ်ဘက်တွင်ရှိသော switch ကို အသုံးပြု၍ ဖွင့်ထားကြောင်း သေချာပါစေ။ Upload mode သို့ ပြောင်းထားရန် လိုအပ်ပါသည်။ အောက်ခြေတွင်ရှိသော အစိမ်းရောင်အလင်းသည် ဖွင့်ထားရမည်၊ blue light သည် pulsing ဖြစ်ရမည်။ Error ရှိနေပါက power switch ကို အလျင်အမြန် နှစ်ကြိမ် ဆွဲချပြီး upload mode သို့ ပြောင်းကာ upload ကို ထပ်မံကြိုးစားပါ။

PlatformIO တွင် Serial Monitor တစ်ခုရှိပြီး Wio Terminal မှ USB cable ဖြင့် ပို့ပေးသော data ကို စောင့်ကြည့်နိုင်သည်။ ဤသည်သည် `Serial.println("Hello World");` command မှ ပို့ပေးသော data ကို စောင့်ကြည့်ရန် အထောက်အကူပြုသည်။

1. VS Code command palette ကို ဖွင့်ပါ။

1. `PlatformIO Serial` ဟု ရိုက်ထည့်ကာ Serial Monitor option ကို ရှာပြီး *PlatformIO: Serial Monitor* ကို ရွေးပါ။

    ![PlatformIO Serial Monitor option in command palette](../../../../../translated_images/vscode-platformio-serial-monitor-command-palette.b348ec841b8a1c14.my.png)

    Terminal အသစ်တစ်ခု ဖွင့်ပြီး serial port မှ ပို့ပေးသော data ကို ဤ terminal တွင် stream လုပ်ပါမည်။

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Hello World
    Hello World
    ```

    `Hello World` သည် serial monitor တွင် 5 စက္ကန့်တိုင်း print လုပ်ပါမည်။

> 💁 ဤ code ကို [code/wio-terminal](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/wio-terminal) folder တွင် ရှာနိုင်ပါသည်။

😀 သင့် 'Hello World' program အောင်မြင်ခဲ့ပါပြီ!

---

**အကြောင်းကြားချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှုအတွက် ကြိုးစားနေသော်လည်း၊ အလိုအလျောက် ဘာသာပြန်မှုများတွင် အမှားများ သို့မဟုတ် မတိကျမှုများ ပါဝင်နိုင်သည်ကို သတိပြုပါ။ မူရင်းဘာသာစကားဖြင့် ရေးသားထားသော စာရွက်စာတမ်းကို အာဏာရှိသော ရင်းမြစ်အဖြစ် သတ်မှတ်သင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူ့ဘာသာပြန်ပညာရှင်များမှ ပရော်ဖက်ရှင်နယ် ဘာသာပြန်မှုကို အကြံပြုပါသည်။ ဤဘာသာပြန်မှုကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော အလွဲအလွတ်များ သို့မဟုတ် အနားယူမှားမှုများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။