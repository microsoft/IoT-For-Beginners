<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9c640f93263fd9adbfda920739e09feb",
  "translation_date": "2025-08-28T17:26:53+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/virtual-device-actuator.md",
  "language_code": "my"
}
-->
# ညအလင်းမီးတိုင် - အိမ်တွင်း IoT စက်ကိရိယာ

ဒီသင်ခန်းစာအပိုင်းမှာ သင်၏ အိမ်တွင်း IoT စက်ကိရိယာတွင် LED တစ်ခုထည့်ပြီး ညအလင်းမီးတိုင်တစ်ခုဖန်တီးပါမည်။

## အိမ်တွင်း စက်ကိရိယာ

ညအလင်းမီးတိုင်အတွက် CounterFit app မှာ actuator တစ်ခုလိုအပ်ပါသည်။

ဒီ actuator က **LED** ဖြစ်ပါတယ်။ အကောင်အထည်ရှိ IoT စက်ကိရိယာမှာ [အလင်းထုတ်ပေးသော diode](https://wikipedia.org/wiki/Light-emitting_diode) တစ်ခုဖြစ်ပြီး လျှပ်စီးစီးဆင်းလာတဲ့အခါ အလင်းထုတ်ပေးပါသည်။ ဒါက digital actuator ဖြစ်ပြီး ၂ မျိုးအခြေအနေရှိပါတယ် - ဖွင့်ထားခြင်းနှင့် ပိတ်ထားခြင်း။ 1 ကိုပို့လိုက်ရင် LED ဖွင့်မည်၊ 0 ကိုပို့လိုက်ရင် LED ပိတ်မည်။

ညအလင်းမီးတိုင် logic ကို pseudo-code အနေနဲ့ရေးထားတာက:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### CounterFit မှာ actuator ထည့်သွင်းပါ

Virtual LED ကိုအသုံးပြုရန် CounterFit app မှာ ထည့်သွင်းဖို့လိုအပ်ပါတယ်။

#### အလုပ် - CounterFit မှာ actuator ထည့်သွင်းပါ

CounterFit app မှာ LED ကိုထည့်သွင်းပါ။

1. အရင်အပိုင်းမှာလုပ်ခဲ့တဲ့အတိုင်း CounterFit web app ကို run လုပ်ထားပါ။ မလုပ်ထားရင် start လုပ်ပြီး light sensor ကိုပြန်ထည့်ပါ။

1. LED တစ်ခုဖန်တီးပါ:

    1. *Actuator* pane ရဲ့ *Create actuator* box မှာ *Actuator type* box ကို drop down လုပ်ပြီး *LED* ကိုရွေးပါ။

    1. *Pin* ကို *5* အဖြစ်သတ်မှတ်ပါ။

    1. **Add** button ကိုရွေးပြီး Pin 5 မှာ LED ကိုဖန်တီးပါ။

    ![LED settings](../../../../../translated_images/my/counterfit-create-led.ba9db1c9b8c622a635d6dfae5cdc4e70c2b250635bd4f0601c6cf0bd22b7ba46.png)

    LED ကိုဖန်တီးပြီး actuators list မှာပေါ်လာပါမည်။

    ![LED created](../../../../../translated_images/my/counterfit-led.c0ab02de6d256ad84d9bad4d67a7faa709f0ea83e410cfe9b5561ef0cef30b1c.png)

    LED ဖန်တီးပြီးရင် *Color* picker ကိုအသုံးပြုပြီး အရောင်ပြောင်းနိုင်ပါတယ်။ **Set** button ကိုရွေးပြီး အရောင်ပြောင်းပါ။

### ညအလင်းမီးတိုင်ကို programming လုပ်ပါ

အခု CounterFit light sensor နဲ့ LED ကိုအသုံးပြုပြီး ညအလင်းမီးတိုင်ကို programming လုပ်နိုင်ပါပြီ။

#### အလုပ် - ညအလင်းမီးတိုင်ကို programming လုပ်ပါ

ညအလင်းမီးတိုင်ကို programming လုပ်ပါ။

1. အရင်အပိုင်းမှာဖန်တီးထားတဲ့ nightlight project ကို VS Code မှာဖွင့်ပါ။ terminal ကို kill လုပ်ပြီး virtual environment ကိုအသုံးပြုဖို့ ပြန်ဖန်တီးပါ။

1. `app.py` ဖိုင်ကိုဖွင့်ပါ။

1. `app.py` ဖိုင်ရဲ့ အပေါ်ပိုင်းမှာလိုအပ်တဲ့ library ကို import လုပ်ဖို့ အောက်ပါ code ကိုထည့်ပါ။

    ```python
    from counterfit_shims_grove.grove_led import GroveLed
    ```

    `from counterfit_shims_grove.grove_led import GroveLed` ဆိုတဲ့ statement က CounterFit Grove shim Python libraries မှ `GroveLed` ကို import လုပ်ပါတယ်။ ဒီ library မှာ CounterFit app မှာဖန်တီးထားတဲ့ LED နဲ့အလုပ်လုပ်ဖို့ code ပါဝင်ပါတယ်။

1. `light_sensor` declaration အောက်မှာ LED ကိုစီမံခန့်ခွဲတဲ့ class ရဲ့ instance တစ်ခုဖန်တီးဖို့ အောက်ပါ code ကိုထည့်ပါ:

    ```python
    led = GroveLed(5)
    ```

    `led = GroveLed(5)` ဆိုတဲ့ line က **5** pin နဲ့ချိတ်ဆက်ထားတဲ့ `GroveLed` class ရဲ့ instance တစ်ခုကိုဖန်တီးပါတယ်။

1. `while` loop ရဲ့အတွင်းမှာ light level ကိုစစ်ဆေးပြီး LED ကိုဖွင့်/ပိတ်ဖို့ အောက်ပါ code ကိုထည့်ပါ:

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    ဒီ code က `light` value ကိုစစ်ဆေးပါတယ်။ 300 ထက်နည်းရင် `GroveLed` class ရဲ့ `on` method ကိုခေါ်ပြီး LED ကိုဖွင့်ပါမည်။ 300 ထက်ကြီးရင် `off` method ကိုခေါ်ပြီး LED ကိုပိတ်ပါမည်။

    > 💁 ဒီ code ကို `print('Light level:', light)` line ရဲ့ level နဲ့တူအောင် indent လုပ်ပါ၊ `while` loop အတွင်းမှာရှိဖို့လိုအပ်ပါတယ်။

1. VS Code Terminal မှာ အောက်ပါ command ကို run လုပ်ပြီး Python app ကို run လုပ်ပါ:

    ```sh
    python3 app.py
    ```

    Light values ကို console မှာ output လုပ်ပါမည်။

    ```output
    (.venv) ➜  GroveTest python3 app.py 
    Light level: 143
    Light level: 244
    Light level: 246
    Light level: 253
    ```

1. *Value* သို့မဟုတ် *Random* settings ကိုပြောင်းပြီး light level ကို 300 ထက်အောက်/အပေါ် ပြောင်းပါ။ LED က ဖွင့်/ပိတ်ပါမည်။

![CounterFit app မှာ LED က light level ပြောင်းသလို ဖွင့်/ပိတ်နေသည်](../../../../../images/virtual-device-running-assignment-1-1.gif)

> 💁 ဒီ code ကို [code-actuator/virtual-device](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/virtual-device) folder မှာတွေ့နိုင်ပါတယ်။

😀 သင်၏ ညအလင်းမီးတိုင် program အောင်မြင်ခဲ့ပါပြီ!

---

**ဝက်ဘ်ဆိုက်မှတ်ချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှန်ကန်မှုအတွက် ကြိုးစားနေပါသော်လည်း၊ အလိုအလျောက်ဘာသာပြန်မှုများတွင် အမှားများ သို့မဟုတ် မတိကျမှုများ ပါဝင်နိုင်သည်ကို ကျေးဇူးပြု၍ သတိပြုပါ။ မူရင်းစာရွက်စာတမ်းကို ၎င်း၏ မူလဘာသာစကားဖြင့် အာဏာတည်သောရင်းမြစ်အဖြစ် သတ်မှတ်သင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူ့ဘာသာပြန်ပညာရှင်များမှ အတည်ပြုထားသော ဘာသာပြန်မှုကို အသုံးပြုရန် အကြံပြုပါသည်။ ဤဘာသာပြန်မှုကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော နားလည်မှုမှားများ သို့မဟုတ် အဓိပ္ပာယ်မှားများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။