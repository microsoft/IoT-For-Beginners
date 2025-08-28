<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "b2e0a965723082b068f735aec0faf3f6",
  "translation_date": "2025-08-28T17:01:16+00:00",
  "source_file": "3-transport/lessons/2-store-location-data/assignment.md",
  "language_code": "my"
}
-->
# ဖင်ရှင်ဘိုင်ဒင်းများကို စစ်ဆေးခြင်း

## လမ်းညွှန်ချက်များ

ဖင်ရှင်ဘိုင်ဒင်းများသည် `main` ဖင်ရှင်မှ ပြန်ပေးသောအရာများကို blob storage တွင် သိမ်းဆည်းရန် သင့်ကုဒ်ကို ခွင့်ပြုသည်။ Azure Storage အကောင့်၊ collection နှင့် အခြားအသေးစိတ်အချက်အလက်များကို `function.json` ဖိုင်တွင် ပြင်ဆင်ထားသည်။

Azure သို့မဟုတ် အခြား Microsoft နည်းပညာများနှင့် အလုပ်လုပ်စဉ်တွင် အကောင်းဆုံး အချက်အလက်ရရှိနိုင်သောနေရာမှာ [Microsoft documentation at docs.com](https://docs.microsoft.com/?WT.mc_id=academic-17441-jabenn) ဖြစ်သည်။ ဒီအလုပ်မှာ သင်သည် Azure Functions binding documentation ကို ဖတ်ရှုပြီး output binding ကို စနစ်တကျ ပြင်ဆင်ပုံကို လေ့လာရမည်ဖြစ်သည်။

စတင်ဖတ်ရှုရန် သင့်တော်သော စာမျက်နှာများမှာ -

* [Azure Functions triggers and bindings concepts](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python)
* [Azure Blob storage bindings for Azure Functions overview](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob?WT.mc_id=academic-17441-jabenn)
* [Azure Blob storage output binding for Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob-output?WT.mc_id=academic-17441-jabenn&tabs=python)

## အကဲဖြတ်စံနှုန်း

| စံနှုန်း | ထူးချွန် | လုံလောက် | တိုးတက်မှုလိုအပ် |
| -------- | --------- | -------- | ----------------- |
| blob storage output binding ကို ပြင်ဆင်ခြင်း | output binding ကို ပြင်ဆင်နိုင်ပြီး blob ကို ပြန်ပေးပြီး blob storage တွင် အောင်မြင်စွာ သိမ်းဆည်းနိုင်ခဲ့သည် | output binding ကို ပြင်ဆင်နိုင်ခဲ့သို့မဟုတ် blob ကို ပြန်ပေးနိုင်ခဲ့သော်လည်း blob storage တွင် အောင်မြင်စွာ သိမ်းဆည်းနိုင်ခြင်း မရှိခဲ့ | output binding ကို ပြင်ဆင်နိုင်ခြင်း မရှိခဲ့ |

---

**အကြောင်းကြားချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှုအတွက် ကြိုးစားနေသော်လည်း၊ အလိုအလျောက် ဘာသာပြန်ခြင်းတွင် အမှားများ သို့မဟုတ် မမှန်ကန်မှုများ ပါဝင်နိုင်သည်ကို သတိပြုပါ။ မူရင်းစာရွက်စာတမ်းကို ၎င်း၏ မူရင်းဘာသာစကားဖြင့် အာဏာတရားရှိသော အရင်းအမြစ်အဖြစ် သတ်မှတ်သင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူ့ဘာသာပြန်ပညာရှင်များမှ ပရော်ဖက်ရှင်နယ် ဘာသာပြန်ခြင်းကို အကြံပြုပါသည်။ ဤဘာသာပြန်ကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော အလွဲအလွတ်များ သို့မဟုတ် အနားလွဲမှုများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။