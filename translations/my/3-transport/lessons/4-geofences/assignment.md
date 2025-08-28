<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5cb65a6ec4387ed177e145347e8e308e",
  "translation_date": "2025-08-28T16:54:42+00:00",
  "source_file": "3-transport/lessons/4-geofences/assignment.md",
  "language_code": "my"
}
-->
# Twilio ကို အသုံးပြု၍ အကြောင်းကြားစာများ ပို့ခြင်း

## လုပ်ဆောင်ရန်ညွှန်ကြားချက်များ

သင့်ရဲ့ code မှာ ယခင်အချိန်အထိ geofence အထဲမှာရှိတဲ့ အကွာအဝေးကိုသာ log လုပ်ထားပါတယ်။ ဒီအလုပ်မှာတော့ GPS အနည်းငယ် geofence အတွင်းရှိတဲ့အခါမှာ text message သို့မဟုတ် email တစ်ခုကို ပို့ရန် အကြောင်းကြားစာတစ်ခု ထည့်သွင်းရပါမယ်။

Azure Functions မှာ bindings အမျိုးမျိုးရှိပြီး Twilio ကဲ့သို့သော အဆင့်မြင့် third-party services တွေကိုပါ အသုံးပြုနိုင်ပါတယ်။

* [Twilio.com](https://www.twilio.com) မှာ အခမဲ့ account တစ်ခုကို စာရင်းသွင်းပါ။
* Azure Functions ကို Twilio SMS နဲ့ bind လုပ်ပုံကို [Microsoft docs Twilio binding for Azure Functions page](https://docs.microsoft.com/azure/azure-functions/functions-bindings-twilio?WT.mc_id=academic-17441-jabenn&tabs=python) မှာ ဖတ်ရှုပါ။
* Azure Functions ကို Twilio SendGrid နဲ့ bind လုပ်ပြီး email ပို့ပုံကို [Microsoft docs Azure Functions SendGrid bindings page](https://docs.microsoft.com/azure/azure-functions/functions-bindings-sendgrid?WT.mc_id=academic-17441-jabenn&tabs=python) မှာ ဖတ်ရှုပါ။
* Functions app ကို bind လုပ်ပြီး GPS coordinates အနည်းငယ် geofence အတွင်း သို့မဟုတ် အပြင်မှာရှိတဲ့အခါမှာသာ notification ရရှိအောင်လုပ်ပါ - နှစ်ခုလုံးမဟုတ်ပါ။

## အဆင့်သတ်မှတ်ချက်

| အဆင့်သတ်မှတ်ချက် | ထူးချွန် | လုံလောက် | တိုးတက်မှုလိုအပ် |
| ----------------- | -------- | -------- | ---------------- |
| Functions bindings ကို configure လုပ်ပြီး email သို့မဟုတ် SMS ရရှိခြင်း | Functions bindings ကို configure လုပ်ပြီး geofence အတွင်း သို့မဟုတ် အပြင်မှာရှိတဲ့အခါ email သို့မဟုတ် SMS ရရှိနိုင်ခဲ့သည်၊ နှစ်ခုလုံးမဟုတ် | Bindings ကို configure လုပ်နိုင်ခဲ့ပေမယ့် email သို့မဟုတ် SMS ပို့နိုင်ခြင်းမရှိ၊ သို့မဟုတ် coordinates နှစ်ခုလုံးအတွင်းနှင့် အပြင်မှာရှိတဲ့အခါပို့နိုင်ခဲ့သည် | Bindings ကို configure လုပ်၍ email သို့မဟုတ် SMS ပို့နိုင်ခြင်းမရှိ |

---

**အကြောင်းကြားချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှုအတွက် ကြိုးစားနေသော်လည်း၊ အလိုအလျောက် ဘာသာပြန်မှုများတွင် အမှားများ သို့မဟုတ် မတိကျမှုများ ပါဝင်နိုင်သည်ကို သတိပြုပါ။ မူရင်းဘာသာစကားဖြင့် ရေးသားထားသော စာရွက်စာတမ်းကို အာဏာရှိသော ရင်းမြစ်အဖြစ် သတ်မှတ်သင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူ့ဘာသာပြန်ပညာရှင်များမှ ပရော်ဖက်ရှင်နယ် ဘာသာပြန်မှုကို အကြံပြုပါသည်။ ဤဘာသာပြန်မှုကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော အလွဲအမှားများ သို့မဟုတ် အနားယူမှုများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။