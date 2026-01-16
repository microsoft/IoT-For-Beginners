<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2bf65f162bcebd35fbcba5fd245afac4",
  "translation_date": "2025-08-28T17:45:38+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/virtual-device-soil-moisture.md",
  "language_code": "my"
}
-->
# မြေစိုထိုင်းဆ - အွန်လိုင်း IoT ပစ္စည်း

ဒီသင်ခန်းစာအပိုင်းမှာ သင့်ရဲ့ အွန်လိုင်း IoT ပစ္စည်းမှာ မြေစိုထိုင်းဆ အာရုံခံကိရိယာတစ်ခု ထည့်သွင်းပြီး၊ အာရုံခံကိရိယာမှ တန်ဖိုးများကို ဖတ်ရှုမည်ဖြစ်သည်။

## အွန်လိုင်းပစ္စည်း

အွန်လိုင်း IoT ပစ္စည်းသည် Grove capacitive မြေစိုထိုင်းဆ အာရုံခံကိရိယာကို အတုဆန့်ကျင်မှုဖြင့် အသုံးပြုမည်ဖြစ်သည်။ ဒါက Raspberry Pi နှင့် Grove capacitive မြေစိုထိုင်းဆ အာရုံခံကိရိယာကို အသုံးပြုခြင်းနှင့် တူညီသော လက်တွေ့စမ်းသပ်မှုကို ထိန်းသိမ်းပေးသည်။

လက်တွေ့ IoT ပစ္စည်းတွင် မြေစိုထိုင်းဆ အာရုံခံကိရိယာသည် မြေစိုထိုင်းဆကို တိုင်းတာရန် မြေ၏ capacitance ကို သိရှိသော capacitive အာရုံခံကိရိယာဖြစ်သည်။ မြေစိုထိုင်းဆ ပမာဏများလာသည်နှင့်အမျှ voltage က ကျဆင်းသွားသည်။

ဒီကိရိယာသည် analog sensor ဖြစ်ပြီး၊ 10-bit ADC ကို အတုဆန့်ကျင်မှုဖြင့် အသုံးပြုကာ 1-1,023 အတွင်းရှိ တန်ဖိုးကို ဖော်ပြသည်။

### CounterFit တွင် မြေစိုထိုင်းဆ အာရုံခံကိရိယာ ထည့်သွင်းပါ

အွန်လိုင်း မြေစိုထိုင်းဆ အာရုံခံကိရိယာကို အသုံးပြုရန် CounterFit app တွင် ထည့်သွင်းရန် လိုအပ်သည်။

#### အလုပ် - CounterFit တွင် မြေစိုထိုင်းဆ အာရုံခံကိရိယာ ထည့်သွင်းပါ

CounterFit app တွင် မြေစိုထိုင်းဆ အာရုံခံကိရိယာ ထည့်သွင်းပါ။

1. သင့်ကွန်ပျူတာတွင် `soil-moisture-sensor` ဟုခေါ်သော folder တစ်ခုတွင် Python app အသစ်တစ်ခု ဖန်တီးပါ။ `app.py` ဟုခေါ်သော ဖိုင်တစ်ခုနှင့် Python virtual environment တစ်ခုပါရှိပြီး၊ CounterFit pip packages ကို ထည့်သွင်းပါ။

    > ⚠️ [သင်ခန်းစာ 1 တွင် CounterFit Python project ဖန်တီးခြင်းနှင့် စတင်ခြင်းဆိုင်ရာ လမ်းညွှန်ချက်များကို လိုအပ်ပါက ပြန်လည်ကြည့်ရှုနိုင်သည်](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md)။

1. CounterFit web app ကို run လုပ်ထားပါ။

1. မြေစိုထိုင်းဆ အာရုံခံကိရိယာကို ဖန်တီးပါ:

    1. *Sensors* pane တွင် *Create sensor* box တွင် *Sensor type* box ကို drop down လုပ်ပြီး *Soil Moisture* ကို ရွေးပါ။

    1. *Units* ကို *NoUnits* အတိုင်းထားပါ။

    1. *Pin* ကို *0* အတိုင်းထားပါ။

    1. **Add** ခလုတ်ကို ရွေးပြီး *Soil Moisture* sensor ကို Pin 0 တွင် ဖန်တီးပါ။

    ![မြေစိုထိုင်းဆ အာရုံခံကိရိယာ၏ settings](../../../../../translated_images/my/counterfit-create-soil-moisture-sensor.35266135a5e0ae68b29a684d7db0d2933a8098b2307d197f7c71577b724603aa.png)

    မြေစိုထိုင်းဆ အာရုံခံကိရိယာကို ဖန်တီးပြီး sensor list တွင် ပေါ်လာမည်။

    ![ဖန်တီးပြီးသော မြေစိုထိုင်းဆ အာရုံခံကိရိယာ](../../../../../translated_images/my/counterfit-soil-moisture-sensor.81742b2de0e9de60a3b3b9a2ff8ecc686d428eb6d71820f27a693be26e5aceee.png)

## မြေစိုထိုင်းဆ အာရုံခံ app ကို အစီအစဉ်ရေးဆွဲပါ

အခု မြေစိုထိုင်းဆ အာရုံခံ app ကို CounterFit sensors အသုံးပြုကာ အစီအစဉ်ရေးဆွဲနိုင်ပါပြီ။

### အလုပ် - မြေစိုထိုင်းဆ အာရုံခံ app ကို အစီအစဉ်ရေးဆွဲပါ

မြေစိုထိုင်းဆ အာရုံခံ app ကို အစီအစဉ်ရေးဆွဲပါ။

1. `soil-moisture-sensor` app ကို VS Code တွင် ဖွင့်ထားပါ။

1. `app.py` ဖိုင်ကို ဖွင့်ပါ။

1. CounterFit နှင့် app ကို ချိတ်ဆက်ရန် `app.py` ဖိုင်၏ အပေါ်ပိုင်းတွင် အောက်ပါ code ကို ထည့်ပါ:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. လိုအပ်သော libraries များကို import လုပ်ရန် အောက်ပါ code ကို `app.py` ဖိုင်တွင် ထည့်ပါ:

    ```python
    import time
    from counterfit_shims_grove.adc import ADC
    ```

    `import time` statement သည် `time` module ကို import လုပ်ပြီး၊ ဒီ assignment တွင် နောက်ပိုင်းတွင် အသုံးပြုမည်ဖြစ်သည်။

    `from counterfit_shims_grove.adc import ADC` statement သည် CounterFit sensor နှင့် ချိတ်ဆက်နိုင်သော virtual analog to digital converter ကို အသုံးပြုရန် `ADC` class ကို import လုပ်သည်။

1. `ADC` class ၏ instance တစ်ခု ဖန်တီးရန် အောက်ပါ code ကို ထည့်ပါ:

    ```python
    adc = ADC()
    ```

1. Pin 0 တွင် ADC မှ ဖတ်ရှုပြီး၊ console တွင် ရလဒ်ကို ရေးသားမည့် infinite loop တစ်ခု ထည့်ပါ။ ဒီ loop သည် ဖတ်ရှုမှုများအကြား 10 စက္ကန့်အနားယူနိုင်သည်။

    ```python
    while True:
        soil_moisture = adc.read(0)
        print("Soil moisture:", soil_moisture)
    
        time.sleep(10)
    ```

1. CounterFit app မှ မြေစိုထိုင်းဆ sensor ၏ တန်ဖိုးကို app မှ ဖတ်ရှုမည့်အခါ ပြောင်းလဲနိုင်သည်။ ဒါကို အောက်ပါနည်းလမ်းနှစ်ခုဖြင့် ပြုလုပ်နိုင်သည်:

    * မြေစိုထိုင်းဆ sensor ၏ *Value* box တွင် နံပါတ်တစ်ခု ထည့်ပြီး **Set** ခလုတ်ကို ရွေးပါ။ သင်ထည့်သော နံပါတ်သည် sensor မှ ပြန်လည်ပေးသော တန်ဖိုးဖြစ်မည်။

    * *Random* checkbox ကို အမှန်ခြစ်ပြီး၊ *Min* နှင့် *Max* တန်ဖိုးများ ထည့်ပါ၊ ထို့နောက် **Set** ခလုတ်ကို ရွေးပါ။ sensor မှ တန်ဖိုးကို ဖတ်ရှုသောအခါ *Min* နှင့် *Max* အကြားရှိ အလွတ်နံပါတ်တစ်ခုကို ဖတ်မည်။

1. Python app ကို run လုပ်ပါ။ မြေစိုထိုင်းဆ တိုင်းတာမှုများကို console တွင် တွေ့မြင်ရမည်။ *Value* သို့မဟုတ် *Random* settings ကို ပြောင်းလဲပြီး တန်ဖိုးပြောင်းလဲမှုကို ကြည့်ပါ။

    ```output
    (.venv) ➜ soil-moisture-sensor $ python app.py 
    Soil moisture: 615
    Soil moisture: 612
    Soil moisture: 498
    Soil moisture: 493
    Soil moisture: 490
    Soil Moisture: 388
    ```

> 💁 ဒီ code ကို [code/virtual-device](../../../../../2-farm/lessons/2-detect-soil-moisture/code/virtual-device) folder တွင် ရှာဖွေနိုင်သည်။

😀 သင့်ရဲ့ မြေစိုထိုင်းဆ အာရုံခံ app အောင်မြင်ခဲ့ပါပြီ!

---

**အကြောင်းကြားချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှုအတွက် ကြိုးစားနေသော်လည်း၊ အလိုအလျောက် ဘာသာပြန်ခြင်းတွင် အမှားများ သို့မဟုတ် မတိကျမှုများ ပါဝင်နိုင်သည်ကို သတိပြုပါ။ မူရင်းစာရွက်စာတမ်းကို ၎င်း၏ မူရင်းဘာသာစကားဖြင့် အာဏာတရားရှိသော အရင်းအမြစ်အဖြစ် သတ်မှတ်သင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူ့ဘာသာပြန်ပညာရှင်များမှ ပရော်ဖက်ရှင်နယ် ဘာသာပြန်ခြင်းကို အကြံပြုပါသည်။ ဤဘာသာပြန်ကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော အလွဲအလွဲအချော်များ သို့မဟုတ် အနားလွဲမှုများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။