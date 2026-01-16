<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f8f541ee945545017a51aaf309aa37c3",
  "translation_date": "2025-08-28T18:16:01+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/virtual-device-relay.md",
  "language_code": "my"
}
-->
# Relay ကိုထိန်းချုပ်ခြင်း - အွန်လိုင်း IoT Hardware

ဒီသင်ခန်းစာအပိုင်းမှာ သင့်ရဲ့ အွန်လိုင်း IoT စက်ပစ္စည်းမှာ မြေစိုထိုင်းဆဆင်ဆာအပြင် relay တစ်ခုကို ထည့်သွင်းပြီး မြေစိုထိုင်းဆအဆင့်အပေါ် မူတည်ပြီး ထိန်းချုပ်ပေးပါမည်။

## အွန်လိုင်း Hardware

အွန်လိုင်း IoT စက်ပစ္စည်းသည် Grove relay ကို အတုအယောင်အသုံးပြုပါမည်။ ဒါကြောင့် Raspberry Pi နှင့် Grove relay ကို သုံးသလိုပဲ ဒီလက်တွေ့လေ့ကျင့်ခန်းကို ဆက်လက်လုပ်ဆောင်နိုင်ပါသည်။

လက်တွေ့ IoT စက်ပစ္စည်းတွင် relay သည် normally-open relay (signal မပေးရင် circuit ပိတ်မထားဘဲ ဖွင့်ထားသော relay) ဖြစ်ပါမည်။ relay အမျိုးအစားများသည် 250V နှင့် 10A အထိ output circuit များကို ထိန်းချုပ်နိုင်ပါသည်။

### CounterFit တွင် relay ထည့်သွင်းခြင်း

အွန်လိုင်း relay ကို အသုံးပြုရန် CounterFit app တွင် ထည့်သွင်းရပါမည်။

#### လုပ်ဆောင်ရန်

CounterFit app တွင် relay ထည့်သွင်းပါ။

1. VS Code တွင် ယခင်သင်ခန်းစာမှ `soil-moisture-sensor` project ကို ဖွင့်ပါ။ (မဖွင့်ရသေးပါက ဖွင့်ပါ) သင်သည် ဒီ project ကို ဆက်လက်ပြင်ဆင်ပါမည်။

1. CounterFit web app ကို run လုပ်ထားပါ။

1. relay တစ်ခုကို ဖန်တီးပါ:

    1. *Actuators* panel တွင် *Create actuator* box ထဲမှ *Actuator type* ကို drop down လုပ်ပြီး *Relay* ကို ရွေးပါ။

    1. *Pin* ကို *5* သတ်မှတ်ပါ။

    1. **Add** ခလုတ်ကို နှိပ်ပြီး Pin 5 တွင် relay ကို ဖန်တီးပါ။

    ![Relay settings](../../../../../translated_images/my/counterfit-create-relay.fa7c40fd0f2f6afc33b35ea94fcb235085be4861e14e3fe6b9b7bcfc82d1c888.png)

    relay ကို ဖန်တီးပြီး actuators list တွင် ပြသပါမည်။

    ![Relay created](../../../../../translated_images/my/counterfit-relay.bbf74c1dbdc8b9acd983367fcbd06703a402aefef6af54ddb28e11307ba8a12c.png)

## Relay ကို Programming လုပ်ခြင်း

မြေစိုထိုင်းဆဆင်ဆာ app သည် relay ကို အသုံးပြုရန် programming လုပ်နိုင်ပါပြီ။

### လုပ်ဆောင်ရန်

အွန်လိုင်းစက်ပစ္စည်းကို programming လုပ်ပါ။

1. VS Code တွင် ယခင်သင်ခန်းစာမှ `soil-moisture-sensor` project ကို ဖွင့်ပါ။ (မဖွင့်ရသေးပါက ဖွင့်ပါ) သင်သည် ဒီ project ကို ဆက်လက်ပြင်ဆင်ပါမည်။

1. `app.py` ဖိုင်တွင် ရှိပြီးသား imports အောက်တွင် အောက်ပါ code ကို ထည့်ပါ:

    ```python
    from counterfit_shims_grove.grove_relay import GroveRelay
    ```

    ဒီ statement သည် Grove Python shim libraries မှ `GroveRelay` ကို import လုပ်ပြီး virtual Grove relay နှင့် အလုပ်လုပ်ရန် အသုံးပြုသည်။

1. `ADC` class ကို ကြေညာထားသောနေရာအောက်တွင် အောက်ပါ code ကို ထည့်ပါ:

    ```python
    relay = GroveRelay(5)
    ```

    relay ကို Pin **5** တွင် ဖန်တီးသည်။ (သင် relay ကို ချိတ်ဆက်ထားသော pin)

1. relay အလုပ်လုပ်မှုကို စမ်းသပ်ရန် `while True:` loop အတွင်း အောက်ပါ code ကို ထည့်ပါ:

    ```python
    relay.on()
    time.sleep(.5)
    relay.off()
    ```

    ဒီ code သည် relay ကို ဖွင့်ပြီး 0.5 စက္ကန့်စောင့်ပြီး relay ကို ပြန်ပိတ်သည်။

1. Python app ကို run လုပ်ပါ။ relay သည် 10 စက္ကန့်တိုင်း ဖွင့်ပြီး ပိတ်ပါမည်။ relay ဖွင့်ပိတ်မှုကို CounterFit app တွင် မြင်ရပါမည်။

    ![Virtual relay turning on and off](../../../../../images/virtual-relay-turn-on-off.gif)

## မြေစိုထိုင်းဆအပေါ်မူတည်၍ relay ကို ထိန်းချုပ်ခြင်း

relay အလုပ်လုပ်နေပြီဆိုတော့ relay ကို မြေစိုထိုင်းဆအဆင့်အပေါ်မူတည်၍ ထိန်းချုပ်နိုင်ပါပြီ။

### လုပ်ဆောင်ရန်

relay ကို ထိန်းချုပ်ပါ။

1. relay စမ်းသပ်ရန် ထည့်ထားသော code ၃ ကြောင်းကို ဖျက်ပါ။ အစား အောက်ပါ code ကို ထည့်ပါ:

    ```python
    if soil_moisture > 450:
        print("Soil Moisture is too low, turning relay on.")
        relay.on()
    else:
        print("Soil Moisture is ok, turning relay off.")
        relay.off()
    ```

    ဒီ code သည် မြေစိုထိုင်းဆဆင်ဆာမှ မြေစိုထိုင်းဆအဆင့်ကို စစ်ဆေးသည်။ 450 ထက် မြင့်ပါက relay ကို ဖွင့်ပြီး 450 ထက် နိမ့်ပါက relay ကို ပိတ်သည်။

    > 💁 Capacitive မြေစိုထိုင်းဆဆင်ဆာသည် မြေစိုထိုင်းဆအဆင့်နိမ့်လျှင် မြေစိုထိုင်းဆများပြီး မြင့်လျှင် မြေစိုထိုင်းဆနည်းသည်။

1. Python app ကို run လုပ်ပါ။ relay သည် မြေစိုထိုင်းဆအဆင့်အပေါ်မူတည်၍ ဖွင့်ပိတ်လုပ်ဆောင်ပါမည်။ မြေစိုထိုင်းဆဆင်ဆာ၏ *Value* သို့မဟုတ် *Random* ကို ပြောင်းလဲပြီး အဆင့်ပြောင်းလဲမှုကို ကြည့်ပါ။

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 ဒီ code ကို [code-relay/virtual-device](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/virtual-device) folder တွင် ရှာနိုင်ပါသည်။

😀 သင်၏ အွန်လိုင်းမြေစိုထိုင်းဆဆင်ဆာနှင့် relay ထိန်းချုပ်မှုအစီအစဉ်အောင်မြင်ပါပြီ!

---

**ဝက်ဘ်ဆိုက်မှတ်ချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှန်ကန်မှုအတွက် ကြိုးစားနေပါသော်လည်း၊ အလိုအလျောက်ဘာသာပြန်ဆိုမှုများတွင် အမှားများ သို့မဟုတ် မတိကျမှုများ ပါဝင်နိုင်သည်ကို ကျေးဇူးပြု၍ သတိပြုပါ။ မူရင်းစာရွက်စာတမ်းကို ၎င်း၏ မူလဘာသာစကားဖြင့် အာဏာတည်သောရင်းမြစ်အဖြစ် သတ်မှတ်သင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူ့ဘာသာပြန်ပညာရှင်များမှ ပြန်ဆိုမှုကို အကြံပြုပါသည်။ ဤဘာသာပြန်ကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော နားလည်မှုမှားများ သို့မဟုတ် အဓိပ္ပာယ်မှားများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။