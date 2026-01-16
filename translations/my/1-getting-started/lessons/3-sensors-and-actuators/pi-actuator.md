<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4db8a3879a53490513571df2f6cf7641",
  "translation_date": "2025-08-28T17:27:34+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/pi-actuator.md",
  "language_code": "my"
}
-->
# Raspberry Pi ဖြင့် ညဉ့်မီးတစ်ခု တည်ဆောက်ခြင်း

ဒီသင်ခန်းစာအပိုင်းမှာ Raspberry Pi တွင် LED တစ်ခု ထည့်သွင်းပြီး ညဉ့်မီးတစ်ခု ဖန်တီးပါမည်။

## ဟာ့ဒ်ဝဲ

အခု ညဉ့်မီးအတွက် actuator တစ်ခုလိုအပ်ပါသည်။

ဒီ actuator က **LED** ဖြစ်ပြီး [အလင်းထုတ်ပေးသော ဒိုင်အိုဒ်](https://wikipedia.org/wiki/Light-emitting_diode) တစ်ခုဖြစ်သည်။ LED သည် လက်ရှိအားဖြင့် အလင်းထုတ်ပေးသော ဒစ်ဂျစ်တယ် actuator ဖြစ်ပြီး ၂ မျိုးအခြေအနေရှိသည်။ အလင်းဖွင့်ခြင်းနှင့် အလင်းပိတ်ခြင်း။ 1 ကို ပေးပို့ပါက LED ဖွင့်မည်၊ 0 ကို ပေးပို့ပါက LED ပိတ်မည်။ LED သည် Grove actuator အပြင်ပစ္စည်းဖြစ်ပြီး Raspberry Pi တွင်ရှိသော Grove Base hat တွင် ချိတ်ဆက်ရန်လိုအပ်သည်။

ညဉ့်မီး၏ logic ကို pseudo-code အနေနှင့် ရေးထားသည်မှာ -

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### LED ကို ချိတ်ဆက်ပါ

Grove LED သည် module အနေနှင့် ရရှိနိုင်ပြီး အရောင်ရွေးချယ်နိုင်သော LEDs ပါဝင်သည်။

#### အလုပ် - LED ကို ချိတ်ဆက်ပါ

LED ကို ချိတ်ဆက်ပါ။

![A grove LED](../../../../../translated_images/my/grove-led.6c853be93f473cf2c439cfc74bb1064732b22251a83cedf66e62f783f9cc1a79.png)

1. သင်နှစ်သက်သော LED ကို ရွေးချယ်ပြီး LED module တွင်ရှိသော အပေါက် ၂ ခုထဲသို့ ချိတ်ဆက်ပါ။

    LEDs သည် အလင်းထုတ်ပေးသော ဒိုင်အိုဒ်များဖြစ်ပြီး ဒိုင်အိုဒ်များသည် လက်ရှိကို တစ်ဖက်သို့သာ သယ်ဆောင်နိုင်သော အီလက်ထရောနစ်ပစ္စည်းများဖြစ်သည်။ ဒါကြောင့် LED ကို မှန်ကန်သောဘက်မှ ချိတ်ဆက်ရန်လိုအပ်သည်၊ မဟုတ်ပါက အလုပ်မလုပ်နိုင်ပါ။

    LED ၏ ခြေတစ်ခုသည် positive pin ဖြစ်ပြီး၊ တစ်ခြေသည် negative pin ဖြစ်သည်။ LED သည် အပြည့်အဝ မပတ်လည်ဘဲ ဘက်တစ်ဖက်မှာ အနည်းငယ်ပြားနေသည်။ အနည်းငယ်ပြားနေသောဘက်သည် negative pin ဖြစ်သည်။ LED ကို module တွင် ချိတ်ဆက်သောအခါ၊ rounded ဘက်ရှိ pin ကို module ၏ အပြင်ဘက်တွင် **+** အမှတ်အသားရှိသော socket တွင် ချိတ်ဆက်ပြီး၊ ပြားနေသောဘက်ကို module ၏ အလယ်ဘက်တွင်ရှိသော socket တွင် ချိတ်ဆက်ပါ။

1. LED module တွင် brightness ကို ထိန်းချုပ်နိုင်သော spin button တစ်ခုရှိသည်။ စတင်ရန်အတွက် anti-clockwise အပြင်ဘက်သို့ အပြည့်အဝလှည့်ပြီး brightness ကို အမြင့်ဆုံးထားပါ။ ဤအလုပ်ကို လက်ဖက်ရိုက်ခေါင်းသုံးပြီး ပြုလုပ်ပါ။

1. Grove cable ၏ တစ်ဖက်အဆုံးကို LED module တွင်ရှိသော socket ထဲသို့ ထည့်ပါ။ ၎င်းသည် တစ်ဖက်ဘက်မှသာ ထည့်နိုင်ပါမည်။

1. Raspberry Pi ကို power ပိတ်ထားပြီး Grove cable ၏ တစ်ဖက်အဆုံးကို Pi တွင်ရှိသော Grove Base hat ၏ **D5** အမှတ်အသားရှိ digital socket တွင် ချိတ်ဆက်ပါ။ ဤ socket သည် GPIO pins အနီးတွင်ရှိသော sockets အတန်း၏ ဘယ်ဘက်မှ ဒုတိယ socket ဖြစ်သည်။

![The grove LED connected to socket D5](../../../../../translated_images/my/pi-led.97f1d474981dc35d1c7996c7b17de355d3d0a6bc9606d79fa5f89df933415122.png)

## ညဉ့်မီးကို အစီအစဉ်ရေးပါ

အခု Grove light sensor နှင့် Grove LED ကို အသုံးပြု၍ ညဉ့်မီးကို အစီအစဉ်ရေးနိုင်ပါပြီ။

### အလုပ် - ညဉ့်မီးကို အစီအစဉ်ရေးပါ

ညဉ့်မီးကို အစီအစဉ်ရေးပါ။

1. Pi ကို power ဖွင့်ပြီး boot ဖြစ်ရန် စောင့်ပါ။

1. VS Code တွင် သင်၏ project ကို ဖွင့်ပါ။ ၎င်းသည် Pi တွင် တိုက်ရိုက် run ဖြစ်နေခြင်းဖြစ်စေ၊ Remote SSH extension ကို အသုံးပြု၍ ချိတ်ဆက်ထားခြင်းဖြစ်စေ။

1. `app.py` ဖိုင်တွင် လိုအပ်သော library ကို import ပြုလုပ်ရန် အောက်ပါ code ကို ထည့်ပါ။ ၎င်းကို အခြား `import` လိုင်းများ၏ အောက်တွင် ထည့်သွင်းပါ။

    ```python
    from grove.grove_led import GroveLed
    ```

    `from grove.grove_led import GroveLed` statement သည် Grove Python libraries မှ `GroveLed` ကို import ပြုလုပ်သည်။ ဤ library တွင် Grove LED နှင့် ဆက်သွယ်ရန် code ပါဝင်သည်။

1. `light_sensor` အတည်ပြုချက်၏ အောက်တွင် LED ကို စီမံခန့်ခွဲသော class ၏ instance တစ်ခု ဖန်တီးရန် အောက်ပါ code ကို ထည့်ပါ။

    ```python
    led = GroveLed(5)
    ```

    `led = GroveLed(5)` လိုင်းသည် **D5** pin တွင် ချိတ်ဆက်ထားသော GroveLed class ၏ instance တစ်ခုကို ဖန်တီးသည်။ ဤ pin သည် LED ချိတ်ဆက်ထားသော digital Grove pin ဖြစ်သည်။

    > 💁 socket တစ်ခုစီတွင် unique pin နံပါတ်များရှိသည်။ Pins 0, 2, 4, နှင့် 6 သည် analog pins ဖြစ်ပြီး၊ pins 5, 16, 18, 22, 24, နှင့် 26 သည် digital pins ဖြစ်သည်။

1. `while` loop အတွင်း၊ `time.sleep` မတိုင်မီ အလင်းအဆင့်များကို စစ်ဆေးပြီး LED ကို ဖွင့်/ပိတ်ရန် အောက်ပါ code ကို ထည့်ပါ။

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    ဤ code သည် `light` အတန်ဖိုးကို စစ်ဆေးသည်။ ၎င်းသည် 300 ထက် နည်းပါက GroveLed class ၏ `on` method ကို ခေါ်ပြီး LED ကို ဖွင့်ရန် digital value 1 ကို ပေးပို့သည်။ အလင်းအတန်ဖိုးသည် 300 သို့မဟုတ် 300 ထက် များပါက `off` method ကို ခေါ်ပြီး LED ကို ပိတ်ရန် digital value 0 ကို ပေးပို့သည်။

    > 💁 ဤ code ကို `print('Light level:', light)` လိုင်းနှင့် တန်းတူအဆင့်ထားပြီး while loop အတွင်းတွင် ရှိရန်လိုအပ်သည်။

    > 💁 actuator များသို့ digital value ပေးပို့သောအခါ၊ 0 value သည် 0V ဖြစ်ပြီး၊ 1 value သည် device ၏ အမြင့်ဆုံး voltage ဖြစ်သည်။ Raspberry Pi နှင့် Grove sensors/actuators တွင် 1 voltage သည် 3.3V ဖြစ်သည်။

1. VS Code Terminal မှ Python app ကို run ပြုလုပ်ရန် အောက်ပါ command ကို run ပြုလုပ်ပါ။

    ```sh
    python3 app.py
    ```

    အလင်းအတန်ဖိုးများကို console တွင် output ပြုလုပ်မည်။

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py 
    Light level: 634
    Light level: 634
    Light level: 634
    Light level: 230
    Light level: 104
    Light level: 290
    ```

1. အလင်း sensor ကို ဖုံးထားပြီး ဖုံးမထားပါ။ အလင်းအတန်ဖိုးသည် 300 သို့မဟုတ် 300 ထက် နည်းပါက LED သည် ဖွင့်မည်၊ အလင်းအတန်ဖိုးသည် 300 ထက် များပါက LED သည် ပိတ်မည်။

    > 💁 LED မဖွင့်ပါက၊ ၎င်းကို မှန်ကန်သောဘက်မှ ချိတ်ဆက်ထားကြောင်း၊ spin button ကို အပြည့်အဝဖွင့်ထားကြောင်း စစ်ဆေးပါ။

![The LED connected to the Pi turning on and off as the light level changes](../../../../../images/pi-running-assignment-1-1.gif)

> 💁 ဤ code ကို [code-actuator/pi](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/pi) folder တွင် ရှာနိုင်ပါသည်။

😀 သင်၏ ညဉ့်မီးအစီအစဉ် အောင်မြင်ခဲ့ပါပြီ!

---

**အကြောင်းကြားချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှုအတွက် ကြိုးစားနေသော်လည်း၊ အလိုအလျောက် ဘာသာပြန်ခြင်းတွင် အမှားများ သို့မဟုတ် မတိကျမှုများ ပါရှိနိုင်သည်ကို သတိပြုပါ။ မူရင်းစာရွက်စာတမ်းကို ၎င်း၏ မူရင်းဘာသာစကားဖြင့် အာဏာတရားရှိသော အရင်းအမြစ်အဖြစ် ရှုလေ့လာသင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူ့ဘာသာပြန်ပညာရှင်များကို အသုံးပြုရန် အကြံပြုပါသည်။ ဤဘာသာပြန်ကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော အလွဲအလွတ်များ သို့မဟုတ် အနားယူမှားမှုများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။