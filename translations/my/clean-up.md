<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5a94fbab1ba737e9bd6cc6c64f114fa0",
  "translation_date": "2025-08-28T15:43:35+00:00",
  "source_file": "clean-up.md",
  "language_code": "my"
}
-->
# သင့်ပရောဂျက်ကို ရှင်းလင်းပါ

ပရောဂျက်တစ်ခုစီကို ပြီးမြောက်ပြီးနောက်၊ cloud resources များကို ဖျက်ပစ်ခြင်းက အကောင်းဆုံးဖြစ်ပါသည်။

ပရောဂျက်တစ်ခုစီအတွက် သင်လေ့လာသည့် သင်ခန်းစာများတွင် အောက်ပါအရာများကို ဖန်တီးထားနိုင်ပါသည်-

* Resource Group
* IoT Hub
* IoT device စာရင်းသွင်းမှုများ
* Storage Account
* Functions App
* Azure Maps account
* Custom vision project
* Azure Container Registry
* Cognitive services resource

အများစုသော resources များသည် ကုန်ကျစရိတ်မရှိပါ - အခမဲ့ဖြစ်ခြင်း သို့မဟုတ် အခမဲ့အဆင့်ကို အသုံးပြုနေခြင်းဖြစ်ပါသည်။ အခပေးအဆင့်လိုအပ်သော services များအတွက်လည်း သင်သည် အခမဲ့အလွှာတွင် ပါဝင်သောအဆင့်ကို အသုံးပြုနေမည်ဖြစ်ပြီး၊ သို့မဟုတ် အနည်းငယ်သော ကုန်ကျစရိတ်သာရှိမည်ဖြစ်သည်။

ကုန်ကျစရိတ်နည်းနည်းရှိသော်လည်း၊ အလုပ်ပြီးဆုံးသောအခါတွင် resources များကို ဖျက်ပစ်ခြင်းက တန်ဖိုးရှိပါသည်။ ဥပမာအားဖြင့် သင်သည် အခမဲ့အဆင့်ကို အသုံးပြုသော IoT Hub တစ်ခုသာ ရှိနိုင်ပါသည်၊ ထို့ကြောင့် အသစ်တစ်ခုဖန်တီးလိုပါက အခပေးအဆင့်ကို အသုံးပြုရမည်ဖြစ်သည်။

သင့် services အားလုံးကို Resource Groups အတွင်း ဖန်တီးထားပြီး၊ ၎င်းသည် စီမံခန့်ခွဲရန် ပိုမိုလွယ်ကူစေပါသည်။ Resource Group ကို ဖျက်ပစ်ခြင်းဖြင့်၊ ၎င်း Resource Group အတွင်းရှိ services အားလုံးကိုလည်း ဖျက်ပစ်နိုင်ပါသည်။

Resource Group ကို ဖျက်ရန်၊ terminal သို့မဟုတ် command prompt တွင် အောက်ပါ command ကို run လုပ်ပါ-

```sh
az group delete --name <resource-group-name>
```

`<resource-group-name>` ကို သင့်စိတ်ဝင်စားသော Resource Group အမည်ဖြင့် အစားထိုးပါ။

အတည်ပြုချက်တစ်ခု ပေါ်လာမည်-

```output
Are you sure you want to perform this operation? (y/n): 
```

`y` ကို ရိုက်ထည့်ပြီး Resource Group ကို ဖျက်ရန် အတည်ပြုပါ။

services အားလုံးကို ဖျက်ရန် အချိန်အနည်းငယ်ကြာမည်။

> 💁 Resource Groups ဖျက်ခြင်းနှင့် ပတ်သက်သော အချက်အလက်များကို [Microsoft Docs တွင်ရှိသော Azure Resource Manager resource group နှင့် resource deletion documentation](https://docs.microsoft.com/azure/azure-resource-manager/management/delete-resource-group?WT.mc_id=academic-17441-jabenn&tabs=azure-cli) တွင် ဖတ်ရှုနိုင်ပါသည်။

---

**အကြောင်းကြားချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှုအတွက် ကြိုးစားနေသော်လည်း၊ အလိုအလျောက် ဘာသာပြန်မှုများတွင် အမှားများ သို့မဟုတ် မမှန်ကန်မှုများ ပါဝင်နိုင်သည်ကို သတိပြုပါ။ မူရင်းစာရွက်စာတမ်းကို ၎င်း၏ မူရင်းဘာသာစကားဖြင့် အာဏာတရားရှိသော အရင်းအမြစ်အဖြစ် ရှုလေ့ရှိသင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူ့ဘာသာပြန်ပညာရှင်များမှ ပရော်ဖက်ရှင်နယ် ဘာသာပြန်မှုကို အကြံပြုပါသည်။ ဤဘာသာပြန်မှုကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော အလွဲအလွတ်များ သို့မဟုတ် အနားလွဲမှုများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။