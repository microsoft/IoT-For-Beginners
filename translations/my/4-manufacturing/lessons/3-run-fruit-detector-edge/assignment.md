<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cc7ad255517f5f618f9c8899e6ff6783",
  "translation_date": "2025-08-28T16:03:40+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/assignment.md",
  "language_code": "my"
}
-->
# အခြားဝန်ဆောင်မှုများကို အနားမှာ အလုပ်လုပ်စေပါ

## လမ်းညွှန်ချက်များ

ရုပ်ပုံခွဲခြားသူများကိုသာမက အနားမှာ အလုပ်လုပ်စေနိုင်ပါတယ်၊ container အဖြစ်ထုပ်ပိုးနိုင်သမျှအရာအားလုံးကို IoT Edge device တွေမှာ တင်နိုင်ပါတယ်။ Azure Functions အနေနဲ့ အလုပ်လုပ်တဲ့ serverless code တွေ၊ သင်မူလသင်ခန်းစာတွေမှာ ဖန်တီးထားတဲ့ triggers တွေလိုမျိုး container တွေထဲမှာ အလုပ်လုပ်နိုင်ပြီး၊ ထို့ကြောင့် IoT Edge မှာလည်း အလုပ်လုပ်နိုင်ပါတယ်။

မူလသင်ခန်းစာတစ်ခုကို ရွေးပြီး Azure Functions app ကို IoT Edge container မှာ အလုပ်လုပ်စေဖို့ ကြိုးစားပါ။ Microsoft docs မှာ [Tutorial: Deploy Azure Functions as IoT Edge modules](https://docs.microsoft.com/azure/iot-edge/tutorial-deploy-function?WT.mc_id=academic-17441-jabenn&view=iotedge-2020-11) ကို အသုံးပြုပြီး Functions app project တစ်ခုကို IoT Edge မှာ deploy လုပ်နည်းကို ပြသထားတဲ့ လမ်းညွှန်ကို ရှာနိုင်ပါတယ်။

## အဆင့်သတ်မှတ်ချက်

| အချက်အလက် | ထူးချွန် | လုံလောက် | တိုးတက်မှုလိုအပ် |
| -------- | --------- | -------- | ----------------- |
| Azure Functions app ကို IoT Edge မှာ တင်ဆောင်ခြင်း | Azure Functions app ကို IoT Edge မှာ တင်ဆောင်ပြီး IoT device နဲ့ IoT data ကနေ trigger ကို အလုပ်လုပ်စေနိုင်ခဲ့ | Functions App ကို IoT Edge မှာ တင်ဆောင်နိုင်ခဲ့ပေမယ့် trigger ကို အလုပ်လုပ်စေမရခဲ့ | Functions App ကို IoT Edge မှာ တင်ဆောင်မရခဲ့ |

---

**အကြောင်းကြားချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှုအတွက် ကြိုးစားနေသော်လည်း၊ အလိုအလျောက် ဘာသာပြန်ခြင်းတွင် အမှားများ သို့မဟုတ် မတိကျမှုများ ပါဝင်နိုင်သည်ကို ကျေးဇူးပြု၍ သိရှိထားပါ။ မူရင်းဘာသာစကားဖြင့် ရေးသားထားသော စာရွက်စာတမ်းကို အာဏာရှိသော ရင်းမြစ်အဖြစ် သတ်မှတ်သင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူ့ဘာသာပြန်ပညာရှင်များမှ ပရော်ဖက်ရှင်နယ် ဘာသာပြန်ခြင်းကို အကြံပြုပါသည်။ ဤဘာသာပြန်ကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော အလွဲအလွတ်များ သို့မဟုတ် အနားလွဲမှုများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။