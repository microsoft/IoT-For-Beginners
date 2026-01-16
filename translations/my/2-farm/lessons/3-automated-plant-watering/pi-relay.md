<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "66b81165e60f8f169bd52a401b6a0f8b",
  "translation_date": "2025-08-28T18:16:42+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/pi-relay.md",
  "language_code": "my"
}
-->
# Relay ကိုထိန်းချုပ်ခြင်း - Raspberry Pi

ဒီသင်ခန်းစာအပိုင်းမှာ၊ သင်သည် Raspberry Pi တွင် မြေစိုထိုင်းဆန့်ကျင်ကိရိယာအပြင် relay တစ်ခုထပ်ထည့်ပြီး မြေစိုထိုင်းဆန့်ကျင်အဆင့်အပေါ်မူတည်၍ ထိန်းချုပ်ပါမည်။

## ဟာ့ဒ်ဝဲ

Raspberry Pi သည် relay တစ်ခုလိုအပ်ပါသည်။

သင်အသုံးပြုမည့် relay သည် [Grove relay](https://www.seeedstudio.com/Grove-Relay.html) ဖြစ်ပြီး၊ သာမန်အားဖြင့် ဖွင့်ထားသော relay (signal မပေးပို့သည့်အခါ output circuit သည် ဖွင့်ထားသည်) ဖြစ်ပြီး၊ အထိ 250V နှင့် 10A အထိ output circuit များကို ကိုင်တွယ်နိုင်သည်။

ဤသည်မှာ digital actuator ဖြစ်သောကြောင့် Grove Base Hat တွင် digital pin တစ်ခုနှင့် ချိတ်ဆက်ပါမည်။

### Relay ကိုချိတ်ဆက်ပါ

Grove relay ကို Raspberry Pi နှင့် ချိတ်ဆက်နိုင်ပါသည်။

#### လုပ်ငန်း

Relay ကိုချိတ်ဆက်ပါ။

![A grove relay](../../../../../translated_images/my/grove-relay.d426958ca210fbd0fb7983d7edc069d46c73a8b0a099d94797bd756f7b6bb6be.png)

1. Grove cable ၏ တစ်ဖက်အဆုံးကို relay ၏ socket တွင် ထည့်ပါ။ ၎င်းသည် တစ်ဖက်သာ ထည့်နိုင်ပါမည်။

2. Raspberry Pi ကို ပိတ်ထားပြီး၊ Grove cable ၏ အခြားဖက်အဆုံးကို Pi တွင် တပ်ထားသော Grove Base Hat ၏ **D5** ဟု အမှတ်အသားပြထားသော digital socket တွင် ချိတ်ဆက်ပါ။ ဤ socket သည် GPIO pin များအနီးရှိ socket များ၏ ဘယ်ဘက်မှ ဒုတိယဖြစ်သည်။ မြေစိုထိုင်းဆန့်ကျင်ကိရိယာကို **A0** socket တွင် ချိတ်ဆက်ထားပါ။

![The grove relay connected to the D5 socket, and the soil moisture sensor connected to the A0 socket](../../../../../translated_images/my/pi-relay-and-soil-moisture-sensor.02f3198975b8c53e69ec716cd2719ce117700bd1fc933eaf93476c103c57939b.png)

3. မြေစိုထိုင်းဆန့်ကျင်ကိရိယာကို မြေဆီလွှာထဲသို့ ထည့်ပါ၊ ယခင်သင်ခန်းစာမှ ထည့်ထားပြီးသားမဟုတ်လျှင်။

## Relay ကို programming ပြုလုပ်ပါ

ယခု Raspberry Pi ကို ချိတ်ဆက်ထားသော relay ကို အသုံးပြုရန် programming ပြုလုပ်နိုင်ပါသည်။

### လုပ်ငန်း

Device ကို programming ပြုလုပ်ပါ။

1. Pi ကို ဖွင့်ပြီး boot ပြုလုပ်ရန် စောင့်ပါ။

2. VS Code တွင် ယခင်သင်ခန်းစာမှ `soil-moisture-sensor` project ကို ဖွင့်ပါ၊ project ကို မဖွင့်ထားသေးလျှင် ဖွင့်ပါ။ သင်သည် ဤ project တွင် ထပ်ထည့်ရေးသားရမည်။

3. ရှိပြီးသား imports အောက်တွင် `app.py` ဖိုင်တွင် အောက်ပါ code ကို ထည့်ပါ။

    ```python
    from grove.grove_relay import GroveRelay
    ```

    ဤ statement သည် Grove Python libraries မှ `GroveRelay` ကို import ပြုလုပ်ပြီး Grove relay နှင့် အပြန်အလှန်ဆက်သွယ်ရန် အသုံးပြုသည်။

4. `ADC` class ကို ကြေညာထားသောနေရာအောက်တွင် အောက်ပါ code ကို ထည့်ပါ၊ ၎င်းသည် `GroveRelay` instance တစ်ခုကို ဖန်တီးသည်။

    ```python
    relay = GroveRelay(5)
    ```

    ဤသည်သည် relay ကို **D5** pin (သင် relay ကို ချိတ်ဆက်ထားသော digital pin) အသုံးပြု၍ ဖန်တီးသည်။

5. Relay သည် အလုပ်လုပ်နေကြောင်း စမ်းသပ်ရန်၊ `while True:` loop အတွင်း အောက်ပါ code ကို ထည့်ပါ။

    ```python
    relay.on()
    time.sleep(.5)
    relay.off()
    ```

    ဤ code သည် relay ကို ဖွင့်ပြီး 0.5 စက္ကန့် စောင့်ပြီး relay ကို ပြန်ပိတ်သည်။

6. Python app ကို run ပြုလုပ်ပါ။ Relay သည် 10 စက္ကန့်တိုင်း ဖွင့်ပြီး ပိတ်မည်၊ ဖွင့်ခြင်းနှင့် ပိတ်ခြင်းအကြား 0.5 စက္ကန့်နားသည်။ Relay ဖွင့်သောအခါ click အသံကြားရပြီး ပိတ်သောအခါ click အသံပြန်ကြားရမည်။ Relay ဖွင့်နေစဉ် Grove board ပေါ်ရှိ LED မီးလင်းပြီး ပိတ်သောအခါ မီးငြိမ်းမည်။

    ![The relay turning on and off](../../../../../images/relay-turn-on-off.gif)

## မြေစိုထိုင်းဆန့်ကျင်မှ relay ကိုထိန်းချုပ်ပါ

ယခု relay သည် အလုပ်လုပ်နေပြီး၊ relay ကို မြေစိုထိုင်းဆန့်ကျင် reading များအပေါ်မူတည်၍ ထိန်းချုပ်နိုင်ပါသည်။

### လုပ်ငန်း

Relay ကို ထိန်းချုပ်ပါ။

1. Relay ကို စမ်းသပ်ရန် ထည့်ထားသော code 3 လိုင်းကို ဖျက်ပါ။ ၎င်းနေရာတွင် အောက်ပါ code ကို ထည့်ပါ။

    ```python
    if soil_moisture > 450:
        print("Soil Moisture is too low, turning relay on.")
        relay.on()
    else:
        print("Soil Moisture is ok, turning relay off.")
        relay.off()
    ```

    ဤ code သည် မြေစိုထိုင်းဆန့်ကျင်ကိရိယာမှ မြေစိုထိုင်းဆန့်ကျင်အဆင့်ကို စစ်ဆေးသည်။ ၎င်းသည် 450 အထက်ရှိပါက relay ကို ဖွင့်ပြီး၊ 450 အောက်ရှိပါက relay ကို ပိတ်သည်။

    > 💁 Capacitive မြေစိုထိုင်းဆန့်ကျင်ကိရိယာသည် မြေစိုထိုင်းဆန့်ကျင်အဆင့်နိမ့်လျှင် မြေစိုထိုင်းမှုများပြီး၊ မြင့်လျှင် မြေစိုထိုင်းမှုနည်းသည်ကို မှတ်သားပါ။

2. Python app ကို run ပြုလုပ်ပါ။ Relay သည် မြေစိုထိုင်းဆန့်ကျင်အဆင့်ပေါ်မူတည်၍ ဖွင့်ပိတ်လုပ်ဆောင်မည်။ ခြောက်သွေ့သောမြေဆီလွှာတွင် စမ်းသပ်ပြီး၊ ရေထည့်ပါ။

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 ဤ code ကို [code-relay/pi](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/pi) folder တွင် ရှာနိုင်ပါသည်။

😀 သင်၏ မြေစိုထိုင်းဆန့်ကျင်ကိရိယာမှ relay ကို ထိန်းချုပ်သည့် program သည် အောင်မြင်ခဲ့ပါသည်!

---

**အကြောင်းကြားချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှုအတွက် ကြိုးစားနေသော်လည်း၊ အလိုအလျောက် ဘာသာပြန်မှုများတွင် အမှားများ သို့မဟုတ် မတိကျမှုများ ပါရှိနိုင်သည်ကို သတိပြုပါ။ မူရင်းဘာသာစကားဖြင့် ရေးသားထားသော စာရွက်စာတမ်းကို အာဏာရှိသော ရင်းမြစ်အဖြစ် သတ်မှတ်သင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူ့ဘာသာပြန်ပညာရှင်များမှ ပရော်ဖက်ရှင်နယ် ဘာသာပြန်မှုကို အကြံပြုပါသည်။ ဤဘာသာပြန်မှုကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော အလွဲအမှားများ သို့မဟုတ် အနားယူမှုများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။