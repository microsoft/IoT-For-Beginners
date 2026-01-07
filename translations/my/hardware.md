<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3dce18fab38adf93ff30b8c221b1eec5",
  "translation_date": "2025-08-28T15:41:09+00:00",
  "source_file": "hardware.md",
  "language_code": "my"
}
-->
# ဟာ့ဒ်ဝဲ

IoT ရဲ့ **T** က **Things** ကိုဆိုလိုပြီး ကျွန်ုပ်တို့ပတ်ဝန်းကျင်နဲ့ အပြန်အလှန်ဆက်သွယ်နိုင်တဲ့ စက်ပစ္စည်းတွေကို ရည်ညွှန်းပါတယ်။ တစ်ခုချင်းစီသော ပရောဂျက်တွေဟာ ကျောင်းသားတွေနဲ့ ဝါသနာရှင်တွေ အလွယ်တကူ ရနိုင်တဲ့ အမှန်တကယ်ရှိတဲ့ ဟာ့ဒ်ဝဲပစ္စည်းတွေကို အခြေခံထားပါတယ်။ ကျွန်ုပ်တို့မှာ IoT ဟာ့ဒ်ဝဲကို အသုံးပြုဖို့ ရွေးချယ်စရာနှစ်ခုရှိပြီး၊ ဒါဟာ ကိုယ်ပိုင်စိတ်ကြိုက်၊ ပရိုဂရမ်မင်းဘာသာစကားနဲ့ ပတ်သက်တဲ့ အသိပညာ၊ သင်ယူရည်မှန်းချက်နဲ့ ရရှိနိုင်မှုအပေါ် မူတည်ပါတယ်။ ထို့အပြင် ဟာ့ဒ်ဝဲမရရှိသူများအတွက် သို့မဟုတ် ဝယ်ယူမှုမပြုမီ ပိုမိုလေ့လာလိုသူများအတွက် 'အတုဟာ့ဒ်ဝဲ' ဗားရှင်းကိုလည်း ပံ့ပိုးပေးထားပါတယ်။

> 💁 သင်တန်းများကို ပြီးမြောက်စေဖို့ IoT ဟာ့ဒ်ဝဲကို ဝယ်ယူရန် မလိုအပ်ပါဘူး။ အားလုံးကို အတု IoT ဟာ့ဒ်ဝဲနဲ့ ပြုလုပ်နိုင်ပါတယ်။

ရုပ်ပိုင်းဆိုင်ရာ ဟာ့ဒ်ဝဲအတွက် Arduino နဲ့ Raspberry Pi ဆိုပြီး ရွေးချယ်စရာနှစ်ခုရှိပါတယ်။ တစ်ခုချင်းစီမှာ အားသာချက်နဲ့ အားနည်းချက်တွေရှိပြီး၊ အစပိုင်းသင်ခန်းစာတစ်ခုမှာ အပြည့်အစုံ ဖော်ပြထားပါတယ်။ သင်ဟာ့ဒ်ဝဲပလက်ဖောင်းကို မရွေးချယ်ရသေးပါက [ပရောဂျက်တစ်ခု၏ ဒုတိယသင်ခန်းစာ](./1-getting-started/lessons/2-deeper-dive/README.md) ကို ပြန်လည်ကြည့်ရှုပြီး သင်လေ့လာလိုတဲ့ ဟာ့ဒ်ဝဲပလက်ဖောင်းကို ဆုံးဖြတ်နိုင်ပါတယ်။

သင်ခန်းစာနဲ့ လေ့ကျင့်ခန်းတွေကို လွယ်ကူစေဖို့ အထူးရွေးချယ်ထားတဲ့ ဟာ့ဒ်ဝဲပစ္စည်းတွေကို အသုံးပြုထားပါတယ်။ အခြားဟာ့ဒ်ဝဲတွေကို အသုံးပြုနိုင်ပေမယ့်၊ အချို့သော လေ့ကျင့်ခန်းတွေဟာ အပိုဆောင်းပစ္စည်းမပါဘဲ သင့်စက်ပေါ်မှာ အလုပ်မလုပ်နိုင်တာကို အာမခံမရပါဘူး။ ဥပမာအားဖြင့် Arduino စက်အများစုမှာ WiFi မပါဝင်ပါဘူး၊ ဒါကြောင့် ကောင်းမွန်တဲ့ Wio terminal ကို WiFi ပါဝင်တဲ့အတွက် ရွေးချယ်ထားတာဖြစ်ပါတယ်။

သင်အခြေခံပစ္စည်းအပြင်၊ မြေသို့မဟုတ် အပင်အိုး၊ အသီးသို့မဟုတ် ဟင်းသီးဟင်းရွက်လို နည်းပညာမဆိုင်တဲ့ ပစ္စည်းအချို့လည်း လိုအပ်ပါမယ်။

## ကိရိယာများ ဝယ်ယူရန်

![Seeed Studios ရဲ့ လိုဂို](../../translated_images/seeed-logo.74732b6b482b6e8e.my.png)

Seeed Studios က သင်ဝယ်ယူရလွယ်ကူစေဖို့ အားလုံးကို အစုံအလင်ဖြင့် စီစဉ်ပေးထားပါတယ်။

### Arduino - Wio Terminal

**[Seeed နဲ့ Microsoft တို့မှ IoT စတင်သူများအတွက် - Wio Terminal Starter Kit](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)**

[![Wio Terminal ဟာ့ဒ်ဝဲ ကိရိယာ](../../translated_images/wio-hardware-kit.4c70c48b85e4283a.my.png)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)

### Raspberry Pi

**[Seeed နဲ့ Microsoft တို့မှ IoT စတင်သူများအတွက် - Raspberry Pi 4 Starter Kit](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)**

[![Raspberry Pi Terminal ဟာ့ဒ်ဝဲ ကိရိယာ](../../translated_images/pi-hardware-kit.26dbadaedb7dd44c73b0131d5d68ea29472ed0a9744f90d5866c6d82f2d16380.my.png)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)

## Arduino

Arduino အတွက် စက်ပစ္စည်းကုဒ်အားလုံးကို C++ ဖြင့်ရေးသားထားပါတယ်။ လေ့ကျင့်ခန်းအားလုံးကို ပြီးမြောက်စေဖို့ အောက်ပါအရာများ လိုအပ်ပါမယ်။

### Arduino ဟာ့ဒ်ဝဲ

* [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html)
* *ရွေးချယ်နိုင်သည်* - USB-C ကေဘယ်သို့မဟုတ် USB-A to USB-C အဒက်တာ။ Wio terminal မှာ USB-C ပေါက်ရှိပြီး USB-C to USB-A ကေဘယ်နဲ့အတူ လာပါတယ်။ သင့် PC သို့မဟုတ် Mac မှာ USB-C ပေါက်ပဲရှိရင် USB-C ကေဘယ် သို့မဟုတ် USB-A to USB-C အဒက်တာ လိုအပ်ပါမယ်။

### Arduino အထူး ဆင်ဆာများနှင့် အက်တူအေတာများ

ဒါတွေဟာ Wio terminal Arduino စက်နဲ့ သီးသန့်သုံးတဲ့အရာတွေဖြစ်ပြီး Raspberry Pi နဲ့ မသက်ဆိုင်ပါဘူး။

* [ArduCam Mini 2MP Plus - OV2640](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/)
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)
* [Breadboard Jumper Wires](https://www.seeedstudio.com/Breadboard-Jumper-Wire-Pack-241mm-200mm-160mm-117m-p-234.html)
* 3.5mm ဂျက်ပါသော နားကြပ် သို့မဟုတ် စပီကာ၊ သို့မဟုတ် JST စပီကာ:
  * [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
* 16GB သို့မဟုတ် အနည်းငယ်သာရှိတဲ့ microSD Card၊ သင့်ကွန်ပျူတာမှာ SD card အသုံးပြုဖို့ ကိရိယာမပါရင် အဆင်ပြေစေမယ့် ကွန်နက်တာပါ လိုအပ်ပါမယ်။ **မှတ်ချက်** - Wio Terminal က 16GB ထက်မကျော်တဲ့ SD card တွေကိုပဲ ပံ့ပိုးပါတယ်။

## Raspberry Pi

Raspberry Pi အတွက် စက်ပစ္စည်းကုဒ်အားလုံးကို Python ဖြင့်ရေးသားထားပါတယ်။ လေ့ကျင့်ခန်းအားလုံးကို ပြီးမြောက်စေဖို့ အောက်ပါအရာများ လိုအပ်ပါမယ်။

### Raspberry Pi ဟာ့ဒ်ဝဲ

* [Raspberry Pi](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/)
  > 💁 Pi 2B နှင့်အထက် ဗားရှင်းများသည် သင်ခန်းစာများတွင် အသုံးပြုနိုင်ပါမည်။ VS Code ကို Pi ပေါ်မှာ တိုက်ရိုက်အသုံးပြုမည်ဆိုပါက Pi 4 (2GB RAM သို့မဟုတ် အထက်) လိုအပ်ပါမည်။ Pi ကို အဝေးမှ အသုံးပြုမည်ဆိုပါက Pi 2B နှင့်အထက် မည်သည့်ဗားရှင်းမဆို အလုပ်လုပ်ပါမည်။
* microSD Card (Raspberry Pi kits တွေမှာ microSD Card ပါဝင်တဲ့အခါလည်း ရနိုင်ပါတယ်)၊ သင့်ကွန်ပျူတာမှာ SD card အသုံးပြုဖို့ ကိရိယာမပါရင် အဆင်ပြေစေမယ့် ကွန်နက်တာပါ လိုအပ်ပါမယ်။
* USB ပါဝါထောက်ပံ့မှု (Raspberry Pi 4 kits တွေမှာ ပါဝါထောက်ပံ့မှုပါဝင်တဲ့အခါလည်း ရနိုင်ပါတယ်)။ Raspberry Pi 4 ကို အသုံးပြုမည်ဆိုပါက USB-C ပါဝါထောက်ပံ့မှု လိုအပ်ပါမည်၊ ယခင်စက်များအတွက် micro-USB ပါဝါထောက်ပံ့မှု လိုအပ်ပါမည်။

### Raspberry Pi အထူး ဆင်ဆာများနှင့် အက်တူအေတာများ

ဒါတွေဟာ Raspberry Pi နဲ့ သီးသန့်သုံးတဲ့အရာတွေဖြစ်ပြီး Arduino စက်နဲ့ မသက်ဆိုင်ပါဘူး။

* [Grove Pi base hat](https://www.seeedstudio.com/Grove-Base-Hat-for-Raspberry-Pi.html)
* [Raspberry Pi Camera module](https://www.raspberrypi.org/products/camera-module-v2/)
* မိုက်ခရိုဖုန်းနှင့် စပီကာ:

  အောက်ပါအရာများ (သို့မဟုတ်) တူညီသောအရာများကို အသုံးပြုနိုင်ပါသည်:
  * USB မိုက်ခရိုဖုန်းနှင့် USB စပီကာ၊ သို့မဟုတ် 3.5mm ဂျက်ပါသော စပီကာ၊ သို့မဟုတ် Raspberry Pi ကို စပီကာပါသော မော်နီတာ သို့မဟုတ် တီဗီနဲ့ ချိတ်ဆက်ထားပါက HDMI အသံထွက်ကို အသုံးပြုနိုင်ပါသည်။
  * မိုက်ခရိုဖုန်းပါသော USB နားကြပ်
  * [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) နှင့်
    * 3.5mm ဂျက်ပါသော နားကြပ် သို့မဟုတ် JST စပီကာ:
    * [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
  * [USB Speakerphone](https://www.amazon.com/USB-Speakerphone-Conference-Business-Microphones/dp/B07Q3D7F8S/ref=sr_1_1?dchild=1&keywords=m0&qid=1614647389&sr=8-1)
* [Grove Light sensor](https://www.seeedstudio.com/Grove-Light-Sensor-v1-2-LS06-S-phototransistor.html)
* [Grove button](https://www.seeedstudio.com/Grove-Button.html)

## ဆင်ဆာများနှင့် အက်တူအေတာများ

အများစုသော ဆင်ဆာများနှင့် အက်တူအေတာများကို Arduino နဲ့ Raspberry Pi သင်ခန်းစာလမ်းကြောင်းနှစ်ခုလုံးမှာ အသုံးပြုထားပါတယ်:

* [Grove LED](https://www.seeedstudio.com/Grove-LED-Pack-p-4364.html) x 2
* [Grove humidity and temperature sensor](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html)
* [Grove capacitive soil moisture sensor](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html)
* [Grove relay](https://www.seeedstudio.com/Grove-Relay.html)
* [Grove GPS (Air530)](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html)
* [Grove Time of flight Distance Sensor](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html)

## ရွေးချယ်စရာ ဟာ့ဒ်ဝဲ

ရေချိုးစနစ်ကို အလိုအလျောက်လုပ်ဆောင်တဲ့ သင်ခန်းစာတွေဟာ relay ကို အသုံးပြုထားပါတယ်။ ရွေးချယ်စရာအနေနဲ့ အောက်ပါ ဟာ့ဒ်ဝဲတွေကို အသုံးပြုပြီး USB ပါဝါနဲ့ အလုပ်လုပ်တဲ့ ရေစုပ်စက်ကို ချိတ်ဆက်နိုင်ပါတယ်။

* [6V water pump](https://www.seeedstudio.com/6V-Mini-Water-Pump-p-1945.html)
* [USB terminal](https://www.adafruit.com/product/3628)
* ဆီလီကွန်ပိုက်များ
* အနီရောင်နှင့် အနက်ရောင်ဝါယာများ
* သေးငယ်သော Flat-head ပတ်တီး

## အတုဟာ့ဒ်ဝဲ

အတုဟာ့ဒ်ဝဲလမ်းကြောင်းက ဆင်ဆာနဲ့ အက်တူအေတာများအတွက် Python ဖြင့် ရေးသားထားတဲ့ အတုစနစ်များကို ပံ့ပိုးပေးပါမယ်။ သင့်မှာ ရရှိနိုင်တဲ့ ဟာ့ဒ်ဝဲပေါ်မူတည်ပြီး၊ သင့်ရိုးရိုးဖွံ့ဖြိုးရေးစက် (Mac, PC) သို့မဟုတ် Raspberry Pi ပေါ်မှာ အတုစနစ်ကို အလုပ်လုပ်စေနိုင်ပါတယ်။ ဥပမာအားဖြင့် Raspberry Pi ကင်မရာရှိပြီး Grove ဆင်ဆာမရှိပါက၊ သင့် Pi ပေါ်မှာ အတုစနစ်ကို အလုပ်လုပ်စေပြီး Grove ဆင်ဆာတွေကို အတုလုပ်နိုင်ပါတယ်၊ ဒါပေမယ့် အမှန်တကယ် ကင်မရာကို အသုံးပြုနိုင်ပါတယ်။

အတုဟာ့ဒ်ဝဲဟာ [CounterFit project](https://github.com/CounterFit-IoT/CounterFit) ကို အသုံးပြုပါမယ်။

ဒီသင်ခန်းစာတွေကို ပြီးမြောက်စေဖို့၊ web cam, မိုက်ခရိုဖုန်းနဲ့ အသံထွက်ပစ္စည်း (နားကြပ် သို့မဟုတ် စပီကာ) လိုအပ်ပါမယ်။ ဒါတွေဟာ အတွင်းပိုင်း သို့မဟုတ် အပြင်ပိုင်းဖြစ်နိုင်ပြီး၊ သင့်စနစ်မှာ အလုပ်လုပ်ဖို့ အဆင်ပြေစေဖို့ ပြင်ဆင်ထားရပါမယ်။

---

**အကြောင်းကြားချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှုအတွက် ကြိုးစားနေသော်လည်း၊ အလိုအလျောက် ဘာသာပြန်မှုများတွင် အမှားများ သို့မဟုတ် မမှန်ကန်မှုများ ပါဝင်နိုင်သည်ကို သတိပြုပါ။ မူရင်းစာရွက်စာတမ်းကို ၎င်း၏ မူလဘာသာစကားဖြင့် အာဏာတရားရှိသောအရင်းအမြစ်အဖြစ် ရှုလေ့လာသင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူ့ဘာသာပြန်ပညာရှင်များမှ ပရော်ဖက်ရှင်နယ် ဘာသာပြန်မှုကို အကြံပြုပါသည်။ ဤဘာသာပြန်မှုကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော အလွဲအလွတ်များ သို့မဟုတ် အနားယူမှုများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။