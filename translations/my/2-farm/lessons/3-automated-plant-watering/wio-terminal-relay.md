<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f3c5d8afa2ef6a0b425ef8ff20615cb4",
  "translation_date": "2025-08-28T18:17:20+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/wio-terminal-relay.md",
  "language_code": "my"
}
-->
# Relay ကိုထိန်းချုပ်ခြင်း - Wio Terminal

ဒီသင်ခန်းပိုင်းမှာ သင့် Wio Terminal မှာ relay ကို soil moisture sensor နဲ့အတူထပ်ထည့်ပြီး၊ relay ကို soil moisture အဆင့်အတိုင်း ထိန်းချုပ်ပါမယ်။

## Hardware

Wio Terminal အတွက် relay တစ်ခုလိုအပ်ပါတယ်။

သင်အသုံးပြုမယ့် relay က [Grove relay](https://www.seeedstudio.com/Grove-Relay.html) ဖြစ်ပြီး၊ relay ကို signal မပို့တဲ့အချိန် output circuit က disconnect ဖြစ်နေတဲ့ normally-open relay ဖြစ်ပါတယ်။ ဒီ relay က 250V နဲ့ 10A အထိ output circuit ကို handle လုပ်နိုင်ပါတယ်။

ဒီဟာက digital actuator ဖြစ်တဲ့အတွက် Wio Terminal ရဲ့ digital pins တွေကို ချိတ်ဆက်ပါတယ်။ Analog/digital port ကို soil moisture sensor နဲ့အသုံးပြုပြီးသားဖြစ်တဲ့အတွက် relay ကို အခြား port (combined I²C/digital port) မှာ ချိတ်ဆက်ပါမယ်။

### Relay ကိုချိတ်ဆက်ခြင်း

Grove relay ကို Wio Terminal ရဲ့ digital port မှာ ချိတ်ဆက်နိုင်ပါတယ်။

#### Task

Relay ကိုချိတ်ဆက်ပါ။

![A grove relay](../../../../../translated_images/my/grove-relay.d426958ca210fbd0fb7983d7edc069d46c73a8b0a099d94797bd756f7b6bb6be.png)

1. Grove cable ရဲ့ တစ်ဖက်အဆုံးကို relay ရဲ့ socket မှာ ထည့်ပါ။ ဒီ cable ကို တစ်ဖက်ဘက်သာ ထည့်နိုင်ပါတယ်။

1. Wio Terminal ကို computer သို့မဟုတ် အခြား power supply မှာ ချိတ်ဆက်ထားမရှိတဲ့အချိန်မှာ Grove cable ရဲ့ အခြားဖက်အဆုံးကို Wio Terminal ရဲ့ screen ကိုကြည့်တဲ့အခါ ဘယ်ဘက် Grove socket မှာ ချိတ်ဆက်ပါ။ Soil moisture sensor ကိုညာဘက် socket မှာ ချိတ်ဆက်ထားပါ။

![The grove relay connected to the left-hand socket, and the soil moisture sensor connected to the right hand socket](../../../../../translated_images/my/wio-relay-and-soil-moisture-sensor.ed722202d42babe0.webp)

1. Soil moisture sensor ကို မြေထဲမှာ ထည့်ပါ၊ အရင်သင်ခန်းမှာ ထည့်ထားပြီးသားမဟုတ်ရင်။

## Relay ကို programming လုပ်ခြင်း

Wio Terminal ကို relay ကိုအသုံးပြုဖို့ programming လုပ်နိုင်ပါပြီ။

### Task

Device ကို programming လုပ်ပါ။

1. VS Code မှာ အရင်သင်ခန်းရဲ့ `soil-moisture-sensor` project ကို ဖွင့်ပါ၊ project ကို ဖွင့်ထားမရှိရင်။ ဒီ project ကို ဆက်လက်ပြင်ဆင်ပါမယ်။

2. ဒီ actuator အတွက် library မရှိပါဘူး - relay က high signal သို့မဟုတ် low signal နဲ့ ထိန်းချုပ်နိုင်တဲ့ digital actuator ဖြစ်ပါတယ်။ Relay ကိုဖွင့်ဖို့ pin ကို high signal (3.3V) ပို့ရမယ်၊ ပိတ်ဖို့ low signal (0V) ပို့ရမယ်။ Arduino ရဲ့ [`digitalWrite`](https://www.arduino.cc/reference/en/language/functions/digital-io/digitalwrite/) function ကို အသုံးပြုနိုင်ပါတယ်။ `setup` function ရဲ့ အောက်ဆုံးမှာ ```cpp
    pinMode(PIN_WIRE_SCL, OUTPUT);
    ``` ကို ထည့်ပြီး combined I²C/digital port ကို output pin အဖြစ် setup လုပ်ပါ။

    `PIN_WIRE_SCL` က combined I²C/digital port ရဲ့ port number ဖြစ်ပါတယ်။

1. Relay က အလုပ်လုပ်နေမလား စမ်းဖို့ `loop` function ရဲ့ နောက်ဆုံး `delay` အောက်မှာ ```cpp
    digitalWrite(PIN_WIRE_SCL, HIGH);
    delay(500);
    digitalWrite(PIN_WIRE_SCL, LOW);
    ``` ကို ထည့်ပါ။

    ဒီ code က relay ချိတ်ဆက်ထားတဲ့ pin ကို high signal ပို့ပြီး relay ကိုဖွင့်ပါတယ်၊ 500ms (တစ်ဝက်စက္ကန့်) စောင့်ပြီး relay ကိုပိတ်ဖို့ low signal ပို့ပါတယ်။

1. Code ကို build လုပ်ပြီး Wio Terminal မှာ upload လုပ်ပါ။

1. Upload လုပ်ပြီးရင် relay က 10 စက္ကန့်တိုင်း ဖွင့်ပြီး ပိတ်ပါမယ်၊ ဖွင့်ပြီး ပိတ်တဲ့အချိန်မှာ တစ်ဝက်စက္ကန့် delay ရှိပါမယ်။ Relay က click ဖွင့်ပြီး click ပိတ်သံကို ကြားရပါမယ်။ Relay ဖွင့်တဲ့အချိန် Grove board ရဲ့ LED ကလင်းပြီး ပိတ်တဲ့အချိန်မှာ LED ကပျောက်ပါမယ်။

    ![The relay turning on and off](../../../../../images/relay-turn-on-off.gif)

## Soil moisture sensor နဲ့ relay ကိုထိန်းချုပ်ခြင်း

Relay က အလုပ်လုပ်နေပြီးသားဖြစ်တဲ့အတွက် relay ကို soil moisture readings အတိုင်း ထိန်းချုပ်နိုင်ပါပြီ။

### Task

Relay ကိုထိန်းချုပ်ပါ။

1. Relay ကိုစမ်းဖို့ထည့်ထားတဲ့ code 3 လိုင်းကို ဖျက်ပါ။ အဲဒီနေရာမှာ ```cpp
    if (soil_moisture > 450)
    {
        Serial.println("Soil Moisture is too low, turning relay on.");
        digitalWrite(PIN_WIRE_SCL, HIGH);
    }
    else
    {
        Serial.println("Soil Moisture is ok, turning relay off.");
        digitalWrite(PIN_WIRE_SCL, LOW);
    }
    ``` ကို ထည့်ပါ။

    ဒီ code က soil moisture sensor ရဲ့ soil moisture level ကိုစစ်ပါတယ်။ 450 အထက်ရှိရင် relay ကိုဖွင့်ပြီး 450 အောက်ရှိရင် relay ကိုပိတ်ပါတယ်။

    > 💁 Capacitive soil moisture sensor က မြေထဲမှာ ရေများလျှင် soil moisture level က နည်းပြီး၊ ရေနည်းလျှင် level ကများတယ်ဆိုတာကို သတိထားပါ။

1. Code ကို build လုပ်ပြီး Wio Terminal မှာ upload လုပ်ပါ။

1. Serial monitor မှာ device ကိုကြည့်ပါ။ Relay က soil moisture level အတိုင်း ဖွင့်သို့မဟုတ် ပိတ်ပါမယ်။ မြေခြောက်တဲ့နေရာမှာစမ်းပြီး ရေထည့်ပါ။

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 ဒီ code ကို [code-relay/wio-terminal](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/wio-terminal) folder မှာ ရှာနိုင်ပါတယ်။

😀 သင့်ရဲ့ soil moisture sensor နဲ့ relay ကိုထိန်းချုပ်တဲ့ program အောင်မြင်ပါပြီ!

---

**အကြောင်းကြားချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှုအတွက် ကြိုးစားနေသော်လည်း၊ အလိုအလျောက် ဘာသာပြန်ခြင်းတွင် အမှားများ သို့မဟုတ် မတိကျမှုများ ပါဝင်နိုင်သည်ကို သတိပြုပါ။ မူရင်းဘာသာစကားဖြင့် ရေးသားထားသော စာရွက်စာတမ်းကို အာဏာတရ အရင်းအမြစ်အဖြစ် သတ်မှတ်သင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူက ဘာသာပြန်ခြင်းကို အကြံပြုပါသည်။ ဤဘာသာပြန်ကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော အလွဲအလွဲအချော်များ သို့မဟုတ် အနားလွဲမှုများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။