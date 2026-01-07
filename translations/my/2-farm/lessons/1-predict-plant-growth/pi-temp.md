<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7678f7c67b97ee52d5727496dcd7d346",
  "translation_date": "2025-08-28T18:06:12+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/pi-temp.md",
  "language_code": "my"
}
-->
# အပူချိန်တိုင်းတာခြင်း - Raspberry Pi

ဒီသင်ခန်းစာအပိုင်းမှာ သင့်ရဲ့ Raspberry Pi ကို အပူချိန်အာရုံခံကိရိယာတစ်ခု ထည့်သွင်းပေးပါမည်။

## ဟာ့ဒ်ဝဲ

သင်အသုံးပြုမည့်အာရုံခံကိရိယာမှာ [DHT11 အပူချိန်နှင့် စိုထိုင်းဆ](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html) အာရုံခံကိရိယာဖြစ်ပြီး၊ အာရုံခံကိရိယာ ၂ ခုကို တစ်ခုတည်းအထုပ်အတွင်းတွဲဖက်ထားသည်။ ဒါဟာ အလွန်လူကြိုက်များပြီး၊ အပူချိန်၊ စိုထိုင်းဆနှင့် တစ်ခါတစ်ရံ လေထုဖိအားကို တွဲဖက်ထားသော ကုန်သွယ်စျေးကွက်တွင်ရရှိနိုင်သော အာရုံခံကိရိယာများစွာရှိသည်။ အပူချိန်အာရုံခံကိရိယာအစိတ်အပိုင်းမှာ အပူချိန်မြင့်တက်လာသည်နှင့်အမျှ အားပြင်းအားနည်းသွားသော thermistor ဖြစ်သော negative temperature coefficient (NTC) thermistor ဖြစ်သည်။

ဒါဟာ ဒစ်ဂျစ်တယ်အာရုံခံကိရိယာဖြစ်ပြီး၊ အပူချိန်နှင့် စိုထိုင်းဆဒေတာကို microcontroller က ဖတ်နိုင်သော ဒစ်ဂျစ်တယ် signal ဖန်တီးရန် onboard ADC ပါရှိသည်။

### အပူချိန်အာရုံခံကိရိယာကို ချိတ်ဆက်ပါ

Grove အပူချိန်အာရုံခံကိရိယာကို Raspberry Pi နှင့် ချိတ်ဆက်နိုင်သည်။

#### လုပ်ဆောင်ရန်

အပူချိန်အာရုံခံကိရိယာကို ချိတ်ဆက်ပါ

![A grove temperature sensor](../../../../../translated_images/grove-dht11.07f8eafceee170043efbb53e1d15722bd4e00fbaa9ff74290b57e9f66eb82c17.my.png)

1. Grove cable တစ်ဖက်ကို စိုထိုင်းဆနှင့် အပူချိန်အာရုံခံကိရိယာ၏ socket တွင် ထည့်ပါ။ ၎င်းသည် တစ်ဖက်ဘက်သာ ထည့်နိုင်ပါသည်။

1. Raspberry Pi ကို ပိတ်ထားပြီး၊ Grove cable ၏ တစ်ဖက်ကို Pi တွင် တပ်ထားသော Grove Base hat ၏ **D5** ဟု အမှတ်အသားပြထားသော digital socket တွင် ချိတ်ဆက်ပါ။ ဒီ socket သည် GPIO pin အနီးရှိ socket အတန်းတွင် ဘယ်ဘက်မှ ဒုတိယဖြစ်သည်။

![The grove temperature sensor connected to socket A0](../../../../../translated_images/pi-temperature-sensor.3ff82fff672c8e56.my.png)

## အပူချိန်အာရုံခံကိရိယာကို အစီအစဉ်ရေးဆွဲပါ

အခုအခါမှာ အပူချိန်အာရုံခံကိရိယာကို အသုံးပြုရန် အစီအစဉ်ရေးဆွဲနိုင်ပါပြီ။

### လုပ်ဆောင်ရန်

ကိရိယာကို အစီအစဉ်ရေးဆွဲပါ။

1. Pi ကို ဖွင့်ပြီး boot ဖြစ်ရန် စောင့်ပါ

1. VS Code ကို Pi တွင် တိုက်ရိုက်ဖွင့်ပါ၊ သို့မဟုတ် Remote SSH extension ကို အသုံးပြု၍ ချိတ်ဆက်ပါ။

    > ⚠️ [သင်ခန်းစာ ၁ တွင် VS Code ကို စတင်အသုံးပြုရန် လမ်းညွှန်ချက်များကို လိုအပ်ပါက ပြန်လည်ကြည့်ရှုနိုင်သည်](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md)။

1. Terminal မှာ `pi` အသုံးပြုသူ၏ home directory တွင် `temperature-sensor` ဟုခေါ်သော folder အသစ်တစ်ခု ဖန်တီးပါ။ ဒီ folder တွင် `app.py` ဟုခေါ်သော ဖိုင်တစ်ခု ဖန်တီးပါ:

    ```sh
    mkdir temperature-sensor
    cd temperature-sensor
    touch app.py
    ```

1. ဒီ folder ကို VS Code တွင် ဖွင့်ပါ

1. အပူချိန်နှင့် စိုထိုင်းဆအာရုံခံကိရိယာကို အသုံးပြုရန်၊ ထပ်မံ Pip package တစ်ခုကို install လုပ်ရန်လိုအပ်သည်။ VS Code တွင် Terminal မှာ အောက်ပါ command ကို အသုံးပြု၍ Pi တွင် Pip package ကို install လုပ်ပါ:

    ```sh
    pip3 install seeed-python-dht
    ```

1. `app.py` ဖိုင်တွင် လိုအပ်သော library များကို import လုပ်ရန် အောက်ပါ code ကို ထည့်ပါ:

    ```python
    import time
    from seeed_dht import DHT
    ```

    `from seeed_dht import DHT` ဟုရေးထားသော statement သည် `seeed_dht` module မှ Grove အပူချိန်အာရုံခံကိရိယာနှင့် ဆက်သွယ်ရန် `DHT` sensor class ကို import လုပ်သည်။

1. အပူချိန်အာရုံခံကိရိယာကို စီမံခန့်ခွဲသော class ၏ instance တစ်ခု ဖန်တီးရန် အပေါ်ရှိ code အပြီးတွင် အောက်ပါ code ကို ထည့်ပါ:

    ```python
    sensor = DHT("11", 5)
    ```

    ဒီဟာသည် **D**igital **H**umidity နှင့် **T**emperature sensor ကို စီမံခန့်ခွဲသော `DHT` class ၏ instance ကို ဖော်ပြသည်။ ပထမ parameter သည် အသုံးပြုနေသော sensor သည် *DHT11* sensor ဖြစ်ကြောင်းကို code ကို ပြောပြသည် - သင်အသုံးပြုနေသော library သည် ဒီ sensor ၏ အခြား variant များကိုလည်း ပံ့ပိုးသည်။ ဒုတိယ parameter သည် sensor သည် Grove base hat ၏ digital port `D5` တွင် ချိတ်ဆက်ထားသည်ဟု code ကို ပြောပြသည်။

    > ✅ သတိပြုပါ၊ socket အားလုံးတွင် ထူးခြားသော pin နံပါတ်များရှိသည်။ Pin 0, 2, 4, နှင့် 6 သည် analog pin များဖြစ်ပြီး၊ pin 5, 16, 18, 22, 24, နှင့် 26 သည် digital pin များဖြစ်သည်။

1. အပေါ်ရှိ code အပြီးတွင် အပူချိန် sensor တန်ဖိုးကို poll လုပ်ပြီး console တွင် print လုပ်ရန် အဆုံးမရှိသော loop တစ်ခု ထည့်ပါ:

    ```python
    while True:
        _, temp = sensor.read()
        print(f'Temperature {temp}°C')
    ```

    `sensor.read()` ကို ခေါ်ဆိုခြင်းသည် စိုထိုင်းဆနှင့် အပူချိန်၏ tuple ကို ပြန်လည်ပေးသည်။ သင့်အတွက် အပူချိန်တန်ဖိုးသာ လိုအပ်သောကြောင့် စိုထိုင်းဆကို မသုံးပါ။ အပူချိန်တန်ဖိုးကို console တွင် print လုပ်သည်။

1. loop ၏ အဆုံးတွင် ၁၀ စက္ကန့်အနည်းငယ် sleep ထည့်ပါ၊ အပူချိန်အဆင့်များကို အဆက်မပြတ်စစ်ဆေးရန် မလိုအပ်ပါ။ sleep လုပ်ခြင်းသည် ကိရိယာ၏ လျှပ်စစ်စွမ်းအင်သုံးစွဲမှုကို လျှော့ချပေးသည်။

    ```python
    time.sleep(10)
    ```

1. VS Code Terminal မှာ အောက်ပါ command ကို အသုံးပြု၍ သင့် Python app ကို run လုပ်ပါ:

    ```sh
    python3 app.py
    ```

    သင် console တွင် အပူချိန်တန်ဖိုးများကို output ဖြစ်နေသည်ကို တွေ့ရပါမည်။ sensor ကို ပူစေရန် သင့်လက်မကို sensor ပေါ်တွင် ဖိထားခြင်း၊ သို့မဟုတ် fan အသုံးပြုခြင်းကဲ့သို့သော အရာများကို အသုံးပြု၍ တန်ဖိုးများပြောင်းလဲမှုကို ကြည့်ပါ:

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py 
    Temperature 26°C
    Temperature 26°C
    Temperature 28°C
    Temperature 30°C
    Temperature 32°C
    ```

> 💁 ဒီ code ကို [code-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/pi) folder တွင် ရှာဖွေနိုင်ပါသည်။

😀 သင့်ရဲ့ အပူချိန် sensor အစီအစဉ်အောင်မြင်ခဲ့ပါပြီ!

---

**အကြောင်းကြားချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှုအတွက် ကြိုးစားနေသော်လည်း၊ အလိုအလျောက် ဘာသာပြန်ခြင်းတွင် အမှားများ သို့မဟုတ် မတိကျမှုများ ပါရှိနိုင်သည်ကို သတိပြုပါ။ မူရင်းဘာသာစကားဖြင့် ရေးသားထားသော စာရွက်စာတမ်းကို အာဏာရှိသော ရင်းမြစ်အဖြစ် သတ်မှတ်သင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူ့ဘာသာပြန်ပညာရှင်များမှ ပရော်ဖက်ရှင်နယ် ဘာသာပြန်ခြင်းကို အကြံပြုပါသည်။ ဤဘာသာပြန်ကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော အလွဲအမှားများ သို့မဟုတ် အနားလွဲမှုများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။