<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c24b6e4d90501c9199f2ceb6a648a337",
  "translation_date": "2025-08-28T17:54:07+00:00",
  "source_file": "2-farm/lessons/5-migrate-application-to-the-cloud/assignment.md",
  "language_code": "my"
}
-->
# လက်စွဲဖြင့် Relay ကိုထိန်းချုပ်ရန် ထည့်သွင်းပါ

## လမ်းညွှန်ချက်များ

Serverless ကုဒ်များကို HTTP တောင်းဆိုမှုများအပါအဝင် အမျိုးမျိုးသောအရာများမှ စတင်နိုင်သည်။ HTTP triggers များကို အသုံးပြု၍ Relay ထိန်းချုပ်မှုကို လက်စွဲဖြင့် override ပြုလုပ်နိုင်ပြီး၊ တစ်စုံတစ်ယောက်က Web တောင်းဆိုမှုမှတဆင့် Relay ကို ဖွင့်ရန် သို့မဟုတ် ပိတ်ရန် ခွင့်ပြုနိုင်သည်။

ဤအလုပ်မှာ သင်သည် Relay ကို ဖွင့်ရန်နှင့် ပိတ်ရန် HTTP triggers နှစ်ခုကို Functions App တွင် ထည့်သွင်းရမည်ဖြစ်ပြီး၊ ဒီသင်ခန်းစာမှ သင်လေ့လာခဲ့သောအရာများကို အသုံးပြု၍ စက်ပစ္စည်းသို့ command များပို့ရန် ပြုလုပ်ရမည်ဖြစ်သည်။

အချို့သော အကြံပြုချက်များ -

* သင်၏ ရှိပြီးသား Functions App တွင် HTTP trigger တစ်ခု ထည့်သွင်းရန် အောက်ပါ command ကို အသုံးပြုနိုင်သည် -

    ```sh
    func new --name <trigger name> --template "HTTP trigger"
    ```

    `<trigger name>` ကို သင့် HTTP trigger အတွက် နာမည်ဖြင့် အစားထိုးပါ။ `relay_on` နှင့် `relay_off` ကဲ့သို့သော နာမည်များကို အသုံးပြုပါ။

* HTTP triggers တွင် access control ရှိနိုင်သည်။ ပုံမှန်အားဖြင့်၊ function-specific API key ကို URL နှင့်အတူ ပေးပို့ရန် လိုအပ်သည်။ ဤအလုပ်အတွက်၊ အဆိုပါ ကန့်သတ်ချက်ကို ဖယ်ရှားနိုင်ပြီး၊ မည်သူမဆို function ကို run လုပ်နိုင်သည်။ ဤအတွက် HTTP triggers အတွက် `function.json` ဖိုင်ရှိ `authLevel` setting ကို အောက်ပါအတိုင်း update ပြုလုပ်ပါ -

    ```json
    "authLevel": "anonymous"
    ```

    > 💁 ဤ access control အကြောင်းကို [Function access keys documentation](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn#authorization-keys) တွင် ပိုမိုဖတ်ရှုနိုင်သည်။

* HTTP triggers များသည် ပုံမှန်အားဖြင့် GET နှင့် POST တောင်းဆိုမှုများကို ပံ့ပိုးပေးသည်။ ထို့ကြောင့် သင်၏ Web browser ကို အသုံးပြု၍ သို့မဟုတ် GET တောင်းဆိုမှုများကို လွယ်ကူစွာ ပြုလုပ်နိုင်သည်။

    သင်၏ Functions App ကို ဒေသတွင် run လုပ်သောအခါ၊ trigger ၏ URL ကို တွေ့ရမည် -

    ```output
    Functions:

        relay_off: [GET,POST] http://localhost:7071/api/relay_off

        relay_on: [GET,POST] http://localhost:7071/api/relay_on

        iot-hub-trigger: eventHubTrigger
    ```

    URL ကို သင့် browser တွင် paste ပြုလုပ်ပြီး `return` ကို နှိပ်ပါ၊ သို့မဟုတ် terminal window တွင် VS Code မှာရှိသော link ကို `Ctrl+click` (`Cmd+click` macOS တွင်) နှိပ်၍ သင့် default browser တွင် ဖွင့်ပါ။ ဤသည်သည် trigger ကို run လုပ်မည်ဖြစ်သည်။

    > 💁 URL တွင် `/api` ပါရှိနေသည်ကို သတိပြုပါ - HTTP triggers များသည် ပုံမှန်အားဖြင့် `api` subdomain တွင်ရှိသည်။

* Functions App ကို deploy ပြုလုပ်သောအခါ၊ HTTP trigger URL သည် အောက်ပါအတိုင်းဖြစ်မည် -

    `https://<functions app name>.azurewebsites.net/api/<trigger name>`

    ဤတွင် `<functions app name>` သည် သင့် Functions App ၏ နာမည်ဖြစ်ပြီး၊ `<trigger name>` သည် သင့် trigger ၏ နာမည်ဖြစ်သည်။

## အကဲဖြတ်စံနှုန်း

| စံနှုန်း | ထူးချွန်သော | လုံလောက်သော | တိုးတက်မှုလိုအပ်သော |
| -------- | ------------ | ------------ | ------------------- |
| HTTP triggers ဖန်တီးခြင်း | Relay ကို ဖွင့်ရန်နှင့် ပိတ်ရန် triggers နှစ်ခုကို သင့်လျော်သော နာမည်များဖြင့် ဖန်တီးနိုင်ခဲ့သည် | Trigger တစ်ခုကို သင့်လျော်သော နာမည်ဖြင့် ဖန်တီးနိုင်ခဲ့သည် | မည်သည့် trigger ကိုမျှ ဖန်တီးနိုင်ခြင်းမရှိခဲ့ပါ |
| HTTP triggers မှ Relay ကို ထိန်းချုပ်ခြင်း | Triggers နှစ်ခုစလုံးကို IoT Hub နှင့် ချိတ်ဆက်ပြီး Relay ကို သင့်တော်စွာ ထိန်းချုပ်နိုင်ခဲ့သည် | Trigger တစ်ခုကို IoT Hub နှင့် ချိတ်ဆက်ပြီး Relay ကို သင့်တော်စွာ ထိန်းချုပ်နိုင်ခဲ့သည် | Triggers များကို IoT Hub နှင့် ချိတ်ဆက်နိုင်ခြင်းမရှိခဲ့ပါ |

---

**အကြောင်းကြားချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှုအတွက် ကြိုးစားနေသော်လည်း၊ အလိုအလျောက် ဘာသာပြန်မှုများတွင် အမှားများ သို့မဟုတ် မတိကျမှုများ ပါရှိနိုင်သည်ကို သတိပြုပါ။ မူရင်းဘာသာစကားဖြင့် ရေးသားထားသော စာရွက်စာတမ်းကို အာဏာတရ အရင်းအမြစ်အဖြစ် သတ်မှတ်သင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူ့ဘာသာပြန်ပညာရှင်များမှ ပရော်ဖက်ရှင်နယ် ဘာသာပြန်မှုကို အကြံပြုပါသည်။ ဤဘာသာပြန်မှုကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော အလွဲအမှားများ သို့မဟုတ် အနားလွဲမှုများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။