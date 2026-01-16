<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "93d352de36526b8990e41dd538100324",
  "translation_date": "2025-08-28T16:28:25+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-microphone.md",
  "language_code": "my"
}
-->
# မိုက်ခရိုဖုန်းနှင့် စပီကာများကို Wio Terminal တွင် ပြင်ဆင်ခြင်း

ဒီသင်ခန်းစာအပိုင်းမှာ သင်၏ Wio Terminal တွင် စပီကာများကို ထည့်သွင်းမည်ဖြစ်သည်။ Wio Terminal တွင် မိုက်ခရိုဖုန်းတစ်ခု ရှိပြီးသားဖြစ်ပြီး၊ ၎င်းကို စကားပြောကို ဖမ်းယူရန် အသုံးပြုနိုင်သည်။

## ဟာ့ဒ်ဝဲ

Wio Terminal တွင် မိုက်ခရိုဖုန်းတစ်ခု ရှိပြီးသားဖြစ်ပြီး၊ ၎င်းကို အသံဖမ်းယူရန် အသုံးပြုနိုင်သည်။

![Wio Terminal တွင်ရှိသော မိုက်ခရိုဖုန်း](../../../../../translated_images/my/wio-mic.3f8c843dbe8ad917.webp)

စပီကာတစ်ခု ထည့်သွင်းရန်၊ [ReSpeaker 2-Mics Pi Hat](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) ကို အသုံးပြုနိုင်သည်။ ၎င်းသည် MEMS မိုက်ခရိုဖုန်း ၂ ခု၊ စပီကာ ချိတ်ဆက်ရာနှင့် နားကြပ်ဆက်တပ်ရာ ပါဝင်သော အပြင်ဘုတ်အဖွဲ့တစ်ခုဖြစ်သည်။

![ReSpeaker 2-Mics Pi Hat](../../../../../translated_images/my/respeaker.f5d19d1c6b14ab16.webp)

သင်သည် နားကြပ်၊ 3.5mm ဂျက်ပါသော စပီကာ၊ သို့မဟုတ် [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html) ကဲ့သို့ JST ချိတ်ဆက်မှုပါသော စပီကာတစ်ခု ထည့်သွင်းရန် လိုအပ်ပါမည်။

ReSpeaker 2-Mics Pi Hat ကို ချိတ်ဆက်ရန် 40 pin-to-pin (male-to-male jumper cables ဟုလည်း ခေါ်သည်) jumper cables လိုအပ်ပါမည်။

> 💁 သင် soldering လုပ်ရန် အဆင်ပြေပါက [40 Pin Raspberry Pi Hat Adapter Board For Wio Terminal](https://www.seeedstudio.com/40-Pin-Raspberry-Pi-Hat-Adapter-Board-For-Wio-Terminal-p-4730.html) ကို အသုံးပြု၍ ReSpeaker ကို ချိတ်ဆက်နိုင်ပါသည်။

သင်သည် အသံကို ဒေါင်းလုဒ်လုပ်ရန်နှင့် ပြန်ဖွင့်ရန် SD ကတ်တစ်ခု လိုအပ်ပါမည်။ Wio Terminal သည် 16GB အထိသာ ပံ့ပိုးနိုင်ပြီး၊ FAT32 သို့မဟုတ် exFAT အဖြစ် format လုပ်ထားရမည်။

### အလုပ် - ReSpeaker Pi Hat ကို ချိတ်ဆက်ခြင်း

1. Wio Terminal ကို ပိတ်ထားပြီး၊ jumper cables နှင့် Wio Terminal ရှေ့ဘက်ရှိ GPIO sockets ကို အသုံးပြု၍ ReSpeaker 2-Mics Pi Hat ကို Wio Terminal နှင့် ချိတ်ဆက်ပါ။

    pin များကို အောက်ပါအတိုင်း ချိတ်ဆက်ရမည်။

    ![pin diagram](../../../../../translated_images/my/wio-respeaker-wiring-0.767f80aa65081038.webp)

1. ReSpeaker နှင့် Wio Terminal ကို GPIO sockets များ အပေါ်ဘက်ကို မျက်နှာမူထားပြီး၊ ဘယ်ဘက်ခြမ်းတွင်ထားပါ။

1. ReSpeaker ရှိ GPIO socket အပေါ်ဘက် ဘယ်ဘက်မှ စတင်၍ jumper cable တစ်ခုကို ReSpeaker ရှိ socket အပေါ်ဘက် ဘယ်ဘက်မှ Wio Terminal ရှိ socket အပေါ်ဘက် ဘယ်ဘက်သို့ ချိတ်ဆက်ပါ။

1. ဘယ်ဘက်ခြမ်းရှိ GPIO sockets အပေါ်မှ အောက်သို့ တစ်ခုချင်းစီ ချိတ်ဆက်ပါ။ pin များကို ခိုင်ခိုင်မာမာ ထည့်ထားပါ။

    ![ReSpeaker နှင့် Wio Terminal ရှိ ဘယ်ဘက် pin များကို ချိတ်ဆက်ထားသောပုံ](../../../../../translated_images/my/wio-respeaker-wiring-1.8d894727f2ba2400.webp)

    ![ReSpeaker နှင့် Wio Terminal ရှိ ဘယ်ဘက် pin များကို ချိတ်ဆက်ထားသောပုံ](../../../../../translated_images/my/wio-respeaker-wiring-2.329e1cbd306e754f.webp)

    > 💁 jumper cables များကို ribbon အဖြစ် ချိတ်ဆက်ထားပါက၊ အတူတူထားပါ - cables များကို အစီအစဉ်တကျ ချိတ်ဆက်ထားသည်ကို အတည်ပြုရန် လွယ်ကူစေသည်။

1. ReSpeaker နှင့် Wio Terminal ရှိ ညာဘက် GPIO sockets များကို အသုံးပြု၍ အတူတူလုပ်ဆောင်ပါ။ ဤ cables များသည် ရှိပြီးသား cables များကို ပတ်သွားရမည်။

    ![ReSpeaker နှင့် Wio Terminal ရှိ ညာဘက် pin များကို ချိတ်ဆက်ထားသောပုံ](../../../../../translated_images/my/wio-respeaker-wiring-3.75b0be447e2fa930.webp)

    ![ReSpeaker နှင့် Wio Terminal ရှိ ညာဘက် pin များကို ချိတ်ဆက်ထားသောပုံ](../../../../../translated_images/my/wio-respeaker-wiring-4.aa9cd434d8779437.webp)

    > 💁 jumper cables များကို ribbon အဖြစ် ချိတ်ဆက်ထားပါက၊ ribbon နှစ်ခုအဖြစ် ခွဲထားပါ။ ရှိပြီးသား cables များ၏ နှစ်ဖက်သို့ တစ်ခုစီ ပတ်သွားပါ။

    > 💁 pin များကို block အဖြစ် တစ်စုတစ်စည်းထားရန် sticky tape ကို အသုံးပြုနိုင်သည်။ cables များအားလုံး ချိတ်ဆက်နေစဉ် pin များ မထွက်စေရန် ကူညီပေးသည်။
    >
    > ![sticky tape ဖြင့် pin များကို တစ်စုတစ်စည်းထားသောပုံ](../../../../../translated_images/my/wio-respeaker-wiring-5.af117c20acf622f3.webp)

1. သင်သည် စပီကာတစ်ခု ထည့်သွင်းရန် လိုအပ်ပါမည်။

    * JST cable ပါသော စပီကာကို အသုံးပြုပါက၊ ReSpeaker ရှိ JST port သို့ ချိတ်ဆက်ပါ။

      ![JST cable ဖြင့် ReSpeaker သို့ ချိတ်ဆက်ထားသော စပီကာ](../../../../../translated_images/my/respeaker-jst-speaker.a441d177809df945.webp)

    * 3.5mm ဂျက်ပါသော စပီကာ သို့မဟုတ် နားကြပ်ကို အသုံးပြုပါက၊ 3.5mm ဂျက် socket သို့ ထည့်ပါ။

      ![3.5mm ဂျက် socket ဖြင့် ReSpeaker သို့ ချိတ်ဆက်ထားသော စပီကာ](../../../../../translated_images/my/respeaker-35mm-speaker.ad79ef4f128c7751.webp)

### အလုပ် - SD ကတ်ကို ပြင်ဆင်ခြင်း

1. SD ကတ်ကို သင်၏ကွန်ပျူတာနှင့် ချိတ်ဆက်ပါ၊ SD ကတ် slot မရှိပါက အပြင်ဘက် reader ကို အသုံးပြုပါ။

1. သင်၏ကွန်ပျူတာတွင် သင့်တော်သော tool ကို အသုံးပြု၍ SD ကတ်ကို FAT32 သို့မဟုတ် exFAT file system ဖြင့် format လုပ်ပါ။

1. SD ကတ်ကို Wio Terminal ရှိ power button အောက်ဘက်၊ ဘယ်ဘက်ခြမ်းရှိ SD ကတ် slot ထဲသို့ ထည့်ပါ။ SD ကတ်ကို အပြည့်အဝ push လုပ်ပြီး click ဖြစ်အောင် ထည့်ရမည် - သင်သည် tool သို့မဟုတ် အခြား SD ကတ်တစ်ခုကို အသုံးပြု၍ push လုပ်ရန် လိုအပ်နိုင်သည်။

    ![SD ကတ်ကို power switch အောက်ရှိ SD ကတ် slot ထဲသို့ ထည့်နေသောပုံ](../../../../../translated_images/my/wio-sd-card.acdcbe322fa4ee7f.webp)

    > 💁 SD ကတ်ကို ထုတ်ရန်၊ အနည်းငယ် push လုပ်ရမည်၊ ထုတ်လွှတ်မည်။ flat-head screwdriver သို့မဟုတ် အခြား SD ကတ်ကဲ့သို့ tool တစ်ခုလိုအပ်နိုင်သည်။

---

**အကြောင်းကြားချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှုအတွက် ကြိုးစားနေသော်လည်း၊ အလိုအလျောက် ဘာသာပြန်ခြင်းတွင် အမှားများ သို့မဟုတ် မတိကျမှုများ ပါဝင်နိုင်သည်ကို သတိပြုပါ။ မူရင်းဘာသာစကားဖြင့် ရေးသားထားသော စာရွက်စာတမ်းကို အာဏာတရ အရင်းအမြစ်အဖြစ် သတ်မှတ်သင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူက ဘာသာပြန်ခြင်းကို အကြံပြုပါသည်။ ဤဘာသာပြန်ကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော အလွဲအမှားများ သို့မဟုတ် အနားယူမှုများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။