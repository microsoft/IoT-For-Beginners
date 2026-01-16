<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4d8e7a066d75b625e7a979c14157041d",
  "translation_date": "2025-08-28T18:01:34+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/README.md",
  "language_code": "my"
}
-->
# မင်းရဲ့ အပင်ကို Cloud သို့ ပြောင်းရွှေ့ပါ

![ဒီသင်ခန်းစာအတွက် Sketchnote အကျဉ်းချုပ်](../../../../../translated_images/my/lesson-8.3f21f3c11159e6a0a376351973ea5724d5de68fa23b4288853a174bed9ac48c3.jpg)

> Sketchnote ကို [Nitya Narasimhan](https://github.com/nitya) မှရေးသားထားသည်။ ပုံကို နှိပ်ပြီး ပိုကြီးမားသော ဗားရှင်းကို ကြည့်ပါ။

ဒီသင်ခန်းစာကို [IoT for Beginners Project 2 - Digital Agriculture series](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) ၏ အစိတ်အပိုင်းတစ်ခုအဖြစ် [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn) မှ သင်ကြားခဲ့သည်။

[![Azure IoT Hub ဖြင့် မင်းရဲ့ စက်ကို Cloud သို့ ချိတ်ဆက်ပါ](https://img.youtube.com/vi/bNxjopXkhvk/0.jpg)](https://youtu.be/bNxjopXkhvk)

## သင်ခန်းစာမတိုင်မီ စစ်ဆေးမှု

[သင်ခန်းစာမတိုင်မီ စစ်ဆေးမှု](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/15)

## နိဒါန်း

ပြီးခဲ့သည့် သင်ခန်းစာတွင် မင်းရဲ့ အပင်ကို MQTT broker တစ်ခုနှင့် ချိတ်ဆက်ပြီး၊ တစ်ခုခုသော server code မှ relay ကို ထိန်းချုပ်ပုံကို သင်ကြားခဲ့ပါသည်။ ဒီဟာက အိမ်တွင်းရှိ တစ်ပင်တည်းအတွက် သို့မဟုတ် စီးပွားဖြစ် လယ်ယာများအတွက် အသုံးပြုသော အင်တာနက်ချိတ်ဆက်ထားသော ရေချိုးစနစ်၏ အခြေခံအဆင့်ဖြစ်သည်။

IoT စက်က public MQTT broker တစ်ခုနှင့် ဆက်သွယ်ခဲ့သည်။ ဒါဟာ အခြေခံအယူအဆကို သင်ကြားရန် အကောင်းဆုံးနည်းလမ်းဖြစ်သော်လည်း၊ ယုံကြည်စိတ်ချမှုနှင့် လုံခြုံမှုအရ အကောင်းဆုံးနည်းလမ်းမဟုတ်ပါ။ ဒီသင်ခန်းစာမှာ မင်း cloud နဲ့ public cloud services တွေက ပေးတဲ့ IoT စွမ်းရည်တွေကို လေ့လာရမှာဖြစ်ပြီး၊ public MQTT broker မှ cloud service တစ်ခုသို့ မင်းရဲ့ အပင်ကို ပြောင်းရွှေ့ပုံကိုလည်း သင်ကြားပါမည်။

ဒီသင်ခန်းစာမှာ ကျွန်တော်တို့ လေ့လာမည့်အကြောင်းအရာများမှာ -

* [Cloud ဆိုတာဘာလဲ?](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Cloud subscription တစ်ခု ဖန်တီးပါ](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Cloud IoT services](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Cloud တွင် IoT service တစ်ခု ဖန်တီးပါ](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [IoT Hub နှင့် ဆက်သွယ်ပါ](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [မင်းရဲ့ စက်ကို IoT service နှင့် ချိတ်ဆက်ပါ](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)

## Cloud ဆိုတာဘာလဲ?

Cloud မတိုင်မီမှာ၊ ကုမ္ပဏီတစ်ခုက သူတို့ရဲ့ ဝန်ဆောင်မှုများ (ဥပမာ database သို့မဟုတ် ဖိုင်သိုလှောင်မှု) ကို ဝန်ထမ်းများ သို့မဟုတ် ပြည်သူများအတွက် ပေးချင်လျှင်၊ data center တစ်ခုကို တည်ဆောက်ပြီး လည်ပတ်ရမည်ဖြစ်သည်။ ဒါဟာ ကွန်ပျူတာအနည်းငယ်ပါဝင်တဲ့ အခန်းတစ်ခန်းမှ စ၍၊ ကွန်ပျူတာများစွာပါဝင်တဲ့ အဆောက်အဦးတစ်ခုအထိ ကွဲပြားနိုင်သည်။ ကုမ္ပဏီက အောက်ပါအရာများအားလုံးကို စီမံခန့်ခွဲရမည် -

* ကွန်ပျူတာများ ဝယ်ယူခြင်း
* Hardware ပြုပြင်ထိန်းသိမ်းမှု
* လျှပ်စစ်နှင့် အအေးပေးစနစ်
* Network
* လုံခြုံရေး (အဆောက်အဦးနှင့် software လုံခြုံရေးအပါအဝင်)
* Software တပ်ဆင်ခြင်းနှင့် အပ်ဒိတ်လုပ်ခြင်း

ဒါဟာ အလွန်စျေးကြီးပြီး၊ ကျွမ်းကျင်သူများစွာ လိုအပ်သလို၊ လိုအပ်သောအခါ အလျင်အမြန် ပြောင်းလဲရန် ခက်ခဲစေသည်။ ဥပမာအားဖြင့်၊ အွန်လိုင်းဆိုင်တစ်ခုက ပျော်ရွှင်စရာ ရာသီအတွက် ကြိုတင်ပြင်ဆင်ရန် လိုအပ်ပါက၊ hardware အသစ်များ ဝယ်ယူပြီး၊ အဆင့်ဆင့် ပြင်ဆင်ရမည်ဖြစ်သည်။ ရာသီကုန်ပြီး အရောင်းကျဆင်းသွားသောအခါ၊ အဲဒီ hardware တွေဟာ အလုပ်မလုပ်ဘဲ အချိန်လွန်နေမည်။

✅ မင်းထင်တာက ဒီနည်းလမ်းက ကုမ္ပဏီတွေကို အလျင်အမြန် ရွေ့လျားနိုင်စေမလား? အွန်လိုင်းအဝတ်အစားရောင်းသူတစ်ဦးဟာ ရုတ်တရက် လူကြိုက်များလာရင်၊ သူတို့ရဲ့ စက်ရုပ်စွမ်းရည်ကို အလျင်အမြန် တိုးမြှင့်နိုင်မလား?

### တစ်ယောက်ယောက်ရဲ့ ကွန်ပျူတာ

Cloud ကို "တစ်ယောက်ယောက်ရဲ့ ကွန်ပျူတာ" လို့ ရယ်စရာအနေနဲ့ ခေါ်ကြသည်။ အစပိုင်းအယူအဆက ရိုးရှင်းသည် - မင်းရဲ့ ကွန်ပျူတာကို ဝယ်မယ့်အစား တစ်ယောက်ယောက်ရဲ့ ကွန်ပျူတာကို ငှားပါ။ Cloud computing provider တစ်ခုက data center ကြီးများကို စီမံခန့်ခွဲမည်။ သူတို့က hardware ဝယ်ယူခြင်း၊ power နှင့် cooling စနစ်များ စီမံခြင်း၊ network စီမံခြင်း၊ လုံခြုံရေး စီမံခြင်း၊ software အပ်ဒိတ်များ စီမံခြင်း စသည်တို့ကို တာဝန်ယူမည်။ Customer အနေနဲ့ မင်းက လိုအပ်သလောက် ကွန်ပျူတာများကို ငှားပြီး၊ လိုအပ်သောအခါ တိုးမြှင့်နိုင်သည်။ 

![Microsoft cloud data center](../../../../../translated_images/my/azure-region-existing.73f704604f2aa6cb9b5a49ed40e93d4fd81ae3f4e6af4a8ca504023902832f56.png)
![Microsoft cloud data center planned expansion](../../../../../translated_images/my/azure-region-planned-expansion.a5074a1e8af74f156a73552d502429e5b126ea5019274d767ecb4b9afdad442b.png)

ဒီ data center တွေဟာ စတုရန်းကီလိုမီတာများစွာ ကျယ်ဝန်းနိုင်သည်။ အထက်ပါပုံတွေက Microsoft cloud data center တစ်ခုမှာ ရှိပြီး၊ စတင်အရွယ်အစားနှင့် အချဲ့အရွယ်အစားကို ပြသထားသည်။ 

> 💁 ဒီ data center တွေဟာ လျှပ်စစ်ဓာတ်အား အလွန်များစွာ လိုအပ်သောကြောင့်၊ တစ်ချို့မှာ သူတို့ရဲ့ လျှပ်စစ်ဓာတ်အားပေးစက်တွေကိုပင် တည်ဆောက်ထားရသည်။ Cloud provider တွေက သဘာဝပတ်ဝန်းကျင်အပေါ် သက်ရောက်မှုကို လျှော့ချရန် ကြိုးစားကြသည်။ [Azure sustainability site](https://azure.microsoft.com/global-infrastructure/sustainability/?WT.mc_id=academic-17441-jabenn) မှာ ပိုမိုသိရှိနိုင်ပါတယ်။

✅ သုတေသနလုပ်ပါ - [Microsoft Azure](https://azure.microsoft.com/?WT.mc_id=academic-17441-jabenn) သို့မဟုတ် [Google GCP](https://cloud.google.com) တို့လို major cloud တွေမှာ data center ဘယ်လောက်ရှိသလဲ၊ ဘယ်နေရာတွေမှာရှိသလဲဆိုတာ ဖတ်ရှုပါ။

Cloud ကို အသုံးပြုခြင်းက ကုန်ကျစရိတ်ကို လျှော့ချပြီး၊ ကုမ္ပဏီတွေကို သူတို့ရဲ့ အဓိကလုပ်ငန်းများအပေါ် အာရုံစိုက်နိုင်စေသည်။ Cloud provider တွေက အစုလိုက်အပြုံလိုက် ဝယ်ယူမှုများနှင့် စွမ်းရည်တိုးတက်မှုများကို အသုံးချပြီး၊ စျေးနှုန်းကို လျှော့ချနိုင်သည်။

### Microsoft Azure

Azure ဟာ Microsoft ရဲ့ developer cloud ဖြစ်ပြီး၊ ဒီသင်ခန်းစာတွေမှာ မင်းအသုံးပြုမည့် cloud ဖြစ်ပါတယ်။ အောက်ပါဗီဒီယိုက Azure အကြောင်း အကျဉ်းချုပ်ကို ဖော်ပြထားပါတယ် -

[![Azure အကြောင်းဗီဒီယို](../../../../../translated_images/my/what-is-azure-video-thumbnail.20174db09e03bbb8.webp)](https://www.microsoft.com/videoplayer/embed/RE4Ibng?WT.mc_id=academic-17441-jabenn)

## Cloud subscription တစ်ခု ဖန်တီးပါ

Cloud service တွေကို အသုံးပြုရန် မင်းအနေနဲ့ cloud provider တစ်ခုနှင့် subscription တစ်ခု လိုအပ်ပါမည်။ Microsoft Azure subscription တစ်ခုကို ဒီသင်ခန်းစာအတွက် စတင်ဖွင့်ပါမည်။

> 💁 မင်းရဲ့ ကျောင်းကနေ ဒီသင်ခန်းစာတွေကို သင်ကြားနေတယ်ဆိုရင်၊ Azure subscription ရှိပြီးဖြစ်နိုင်ပါတယ်။ မင်းရဲ့ ဆရာ/ဆရာမကို စစ်ဆေးပါ။

Azure subscription တွေမှာ အခမဲ့အမျိုးအစားနှစ်မျိုးရှိပါတယ် -

* **Azure for Students** - ကျောင်းသားများအတွက် ဒီ subscription ဟာ 18 နှစ်အထက် ကျောင်းသားများအတွက် ဖြစ်ပါတယ်။ Credit card မလိုအပ်ပါဘူး၊ ကျောင်းအီးမေးလ်လိပ်စာကို အသုံးပြု၍ ကျောင်းသားအဖြစ် အတည်ပြုရပါမည်။ 

* **Azure free subscription** - ကျောင်းသားမဟုတ်သူများအတွက် ဖြစ်ပါတယ်။ Credit card လိုအပ်သော်လည်း၊ စစ်ဆေးရန်အတွက်သာ အသုံးပြုသည်။

> 💁 Microsoft မှ 18 နှစ်အောက် ကျောင်းသားများအတွက် Azure for Students Starter subscription ကို ပေးထားသော်လည်း၊ IoT service မပါဝင်ပါ။

### Task - အခမဲ့ cloud subscription တစ်ခု စတင်ပါ

18 နှစ်အထက် ကျောင်းသားများအတွက် Azure for Students subscription ကို စတင်နိုင်ပါတယ်။ 

* GitHub student developer pack မှတဆင့် [education.github.com/pack](https://education.github.com/pack) တွင် စတင်ပါ။
* သို့မဟုတ် [azure.microsoft.com/free/students](https://azure.microsoft.com/free/students/?WT.mc_id=academic-17441-jabenn) တွင် တိုက်ရိုက် စတင်ပါ။

> ⚠️ မင်းရဲ့ ကျောင်းအီးမေးလ်လိပ်စာကို အသိအမှတ်ပြုမထားပါက၊ [ဒီ repo တွင် issue တင်ပါ](https://github.com/Microsoft/IoT-For-Beginners/issues)။

ကျောင်းသားမဟုတ်သူများအတွက် -

* [azure.microsoft.com/free](https://azure.microsoft.com/free/?WT.mc_id=academic-17441-jabenn) တွင် Azure Free Subscription ကို စတင်ပါ။

## Cloud IoT services

Public test MQTT broker ကို သင်ကြားရန် အကောင်းဆုံးနည်းလမ်းဖြစ်သော်လည်း၊ စီးပွားဖြစ်အတွက် အခက်အခဲများရှိသည် -

* ယုံကြည်စိတ်ချမှု - အခမဲ့ဝန်ဆောင်မှုဖြစ်ပြီး၊ မည်သည့်အချိန်တွင်မဆို ပိတ်သိမ်းနိုင်သည်
* လုံခြုံမှု - Public ဖြစ်သောကြောင့်၊ မည်သူမဆို မင်းရဲ့ data ကို ကြည့်နိုင်သည်
* စွမ်းဆောင်ရည် - စမ်းသပ်သည့် message အနည်းငယ်အတွက်သာ ရည်ရွယ်ထားသည်
* စက်တွေ့ရှိမှု - ချိတ်ဆက်ထားသော စက်များကို သိရှိရန် နည်းလမ်းမရှိပါ

Cloud IoT services တွေက ဒီပြဿနာတွေကို ဖြေရှင်းပေးနိုင်ပါတယ်။ Cloud provider တွေက reliability အတွက် အလွန်ကြိုးစားပြီး၊ လုံခြုံမှုကို အခြေခံထားသည်။ 

> 💁 Cloud IoT service တွေဟာ အခမဲ့ဗားရှင်းများကိုလည်း ပေးထားပါတယ်။

IoT စက်တွေဟာ device SDK သို့မဟုတ် MQTT/HTTP တို့ကို အသုံးပြု၍ Cloud service တွေကို ချိတ်ဆက်နိုင်ပါတယ်။ Device SDK က အလွယ်ဆုံးနည်းလမ်းဖြစ်ပြီး၊ လုံခြုံမှုနှင့် topic management ကို handle လုပ်ပေးသည်။

![Devices connect to a service using a device SDK. Server code also connects to the service via an SDK](../../../../../translated_images/my/iot-service-connectivity.7e873847921a5d6fd60d0ba3a943210194518cee0d4e362476624316443275c3.png)

စက်တွေဟာ Cloud service ကို အသုံးပြုပြီး၊ အခြား application components တွေနဲ့ ဆက်သွယ်နိုင်ပါတယ်။

![Devices without a valid secret key cannot connect to the IoT service](../../../../../translated_images/my/iot-service-allowed-denied-connection.818b0063ac213fb84204a7229303764d9b467ca430fb822b4ac2fca267d56726.png)

Cloud IoT service တွေဟာ device တွေကို pre-register လုပ်ထားခြင်း သို့မဟုတ် secret key/certificate တွေကို အသုံးပြု၍ လုံခြုံမှုကို အာမခံပေးသည်။

✅ သုတေသနလုပ်ပါ - Open IoT service တွေမှာ မည်သူမဆို ချိတ်ဆက်နိုင်ရင် ဘယ်လို downside တွေရှိမလဲ? Hackers တွေက အဲဒီအခွင့်အရေးကို ဘယ်လို အသုံးချကြသလဲ?
💁 IoT ဝန်ဆောင်မှုများတွင် ထပ်ဆင့်စွမ်းဆောင်ရည်များကိုလည်း အကောင်အထည်ဖော်ထားပြီး၊ cloud ပံ့ပိုးသူများတွင် ဝန်ဆောင်မှုနှင့် ချိတ်ဆက်နိုင်သော ထပ်ဆင့်ဝန်ဆောင်မှုများနှင့် အက်ပ်လီကေးရှင်းများလည်း ရှိပါသည်။ ဥပမာအားဖြင့်၊ စက်ပစ္စည်းအားလုံးမှ ပေးပို့လာသော တယ်လီမက်ထရီမက်ဆေ့များကို ဒေတာဘေ့စ်တစ်ခုတွင် သိမ်းဆည်းလိုပါက၊ cloud ပံ့ပိုးသူ၏ configuration tool တွင် ဝန်ဆောင်မှုကို ဒေတာဘေ့စ်နှင့် ချိတ်ဆက်ပြီး ဒေတာကို စီးဆင်းစေရန် အချို့သော ခလုတ်များသာ နှိပ်ရမည်ဖြစ်သည်။
## ကောင်းကင်ပေါ်တွင် IoT ဝန်ဆောင်မှုတစ်ခု ဖန်တီးခြင်း

အခုတော့ သင်မှာ Azure subscription ရှိပြီးဖြစ်တာကြောင့် IoT ဝန်ဆောင်မှုတစ်ခုအတွက် စာရင်းသွင်းနိုင်ပါပြီ။ Microsoft မှပေးသော IoT ဝန်ဆောင်မှုကို Azure IoT Hub ဟုခေါ်သည်။

![Azure IoT Hub အမှတ်တံဆိပ်](../../../../../translated_images/my/azure-iot-hub-logo.28a19de76d0a1932464d858f7558712bcdace3e5ec69c434d482ed7ce41c3a26.png)

အောက်ပါဗီဒီယိုသည် Azure IoT Hub အကြောင်းကို အကျဉ်းချုပ်ဖော်ပြထားသည်။

[![Azure IoT Hub အကြောင်းအရာဗီဒီယို](https://img.youtube.com/vi/smuZaZZXKsU/0.jpg)](https://www.youtube.com/watch?v=smuZaZZXKsU)

> 🎥 ဗီဒီယိုကြည့်ရန် အထက်ပါပုံကို နှိပ်ပါ

✅ ခဏနားပြီး [Microsoft IoT Hub documentation](https://docs.microsoft.com/azure/iot-hub/about-iot-hub?WT.mc_id=academic-17441-jabenn) တွင် IoT Hub အကြောင်းအရာကို ဖတ်ရှုလေ့လာပါ။

Azure တွင် ရရှိနိုင်သော cloud ဝန်ဆောင်မှုများကို web-based portal သို့မဟုတ် command-line interface (CLI) မှတစ်ဆင့် ပြင်ဆင်နိုင်သည်။ ဒီအလုပ်မှာတော့ CLI ကို အသုံးပြုမည်ဖြစ်သည်။

### အလုပ် - Azure CLI ကို ထည့်သွင်းပါ

Azure CLI ကို အသုံးပြုရန်အတွက် သင်၏ PC သို့မဟုတ် Mac တွင် အရင်ဆုံး ထည့်သွင်းရမည်ဖြစ်သည်။

1. [Azure CLI documentation](https://docs.microsoft.com/cli/azure/install-azure-cli?WT.mc_id=academic-17441-jabenn) တွင်ပါရှိသော လမ်းညွှန်ချက်များကို လိုက်နာပြီး CLI ကို ထည့်သွင်းပါ။

1. Azure CLI သည် Azure ဝန်ဆောင်မှုအမျိုးမျိုးကို စီမံခန့်ခွဲရန် လုပ်ဆောင်ချက်များကို ထည့်သွင်းပေးသော extension များစွာကို ပံ့ပိုးပေးသည်။ အောက်ပါ command ကို သင်၏ command line သို့မဟုတ် terminal မှာ run လိုက်ပြီး IoT extension ကို ထည့်သွင်းပါ။

    ```sh
    az extension add --name azure-iot
    ```

1. Azure CLI မှ သင်၏ Azure subscription သို့ log in ပြုလုပ်ရန် အောက်ပါ command ကို သင်၏ command line သို့မဟုတ် terminal မှာ run လုပ်ပါ။

    ```sh
    az login
    ```

    သင်၏ default browser တွင် web page တစ်ခု ဖွင့်လှစ်မည်ဖြစ်သည်။ သင်၏ Azure subscription အတွက် အသုံးပြုသော account ဖြင့် log in ပြုလုပ်ပါ။ Log in ပြီးလျှင် browser tab ကို ပိတ်နိုင်ပါသည်။

1. သင်မှာ school subscription တစ်ခုနှင့် သင်၏ကိုယ်ပိုင် Azure for Students subscription တို့လိုမျိုး subscription အမျိုးမျိုးရှိပါက သင်အသုံးပြုလိုသော subscription ကို ရွေးချယ်ရမည်ဖြစ်သည်။ သင်ရရှိနိုင်သော subscription အားလုံးကို ဖော်ပြရန် အောက်ပါ command ကို run လုပ်ပါ။

    ```sh
    az account list --output table
    ```

    Output တွင် subscription တစ်ခုစီ၏ `SubscriptionId` နှင့်အတူ အမည်ကို တွေ့ရမည်။

    ```output
    ➜  ~ az account list --output table
    Name                    CloudName    SubscriptionId                        State    IsDefault
    ----------------------  -----------  ------------------------------------  -------  -----------
    School-subscription     AzureCloud   cb30cde9-814a-42f0-a111-754cb788e4e1  Enabled  True
    Azure for Students      AzureCloud   fa51c31b-162c-4599-add6-781def2e1fbf  Enabled  False
    ```

    သင်အသုံးပြုလိုသော subscription ကို ရွေးချယ်ရန် အောက်ပါ command ကို အသုံးပြုပါ။

    ```sh
    az account set --subscription <SubscriptionId>
    ```

    `<SubscriptionId>` ကို သင်အသုံးပြုလိုသော subscription Id ဖြင့် အစားထိုးပါ။ ဒီ command ကို run လုပ်ပြီးနောက် သင်၏ accounts ကို ပြန်လည်ဖော်ပြပါ။ သင်ရွေးချယ်ထားသော subscription အတွက် `IsDefault` ကော်လံတွင် `True` ဟု ဖော်ပြထားမည်ဖြစ်သည်။

### အလုပ် - resource group တစ်ခု ဖန်တီးပါ

Azure ဝန်ဆောင်မှုများ (ဥပမာ - IoT Hub instances, virtual machines, databases, AI services) ကို **resources** ဟုခေါ်သည်။ Resource တစ်ခုစီသည် **Resource Group** (resource အများအပြားကို logical group တစ်ခုအဖြစ် စုစည်းထားသောအရာ) အတွင်းတွင် ရှိရမည်။

> 💁 Resource group များကို အသုံးပြုခြင်းဖြင့် ဝန်ဆောင်မှုများစွာကို တစ်ပြိုင်တည်း စီမံခန့်ခွဲနိုင်သည်။ ဥပမာအားဖြင့် ဒီ project အတွက် သင်၏သင်ခန်းစာအားလုံး ပြီးဆုံးသွားသောအခါ resource group ကို ဖျက်လိုက်ရုံဖြင့် အတွင်းရှိ resource အားလုံးကို အလိုအလျောက် ဖျက်သိမ်းနိုင်သည်။

1. Azure data center များသည် ကမ္ဘာတစ်ဝှမ်းတွင် ရှိပြီး region အလိုက် ခွဲထားသည်။ Azure resource သို့မဟုတ် resource group တစ်ခု ဖန်တီးသောအခါ သင်ဖန်တီးလိုသောနေရာကို သတ်မှတ်ရမည်။ နေရာများစာရင်းကို ရယူရန် အောက်ပါ command ကို run လုပ်ပါ။

    ```sh
    az account list-locations --output table
    ```

    နေရာများစာရင်းကို တွေ့ရမည်။ ဒီစာရင်းသည် ရှည်လျားမည်ဖြစ်သည်။

    > 💁 ဒီစာရင်းရေးစဉ်အချိန်တွင် 65 နေရာများကို deploy ပြုလုပ်နိုင်ပါသည်။

    ```output
        ➜  ~ az account list-locations --output table
    DisplayName               Name                 RegionalDisplayName
    ------------------------  -------------------  -------------------------------------
    East US                   eastus               (US) East US
    East US 2                 eastus2              (US) East US 2
    South Central US          southcentralus       (US) South Central US
    ...
    ```

    သင်နီးစပ်ဆုံးသော region ၏ `Name` ကော်လံမှ တန်ဖိုးကို မှတ်သားပါ။ [Azure geographies page](https://azure.microsoft.com/global-infrastructure/geographies/?WT.mc_id=academic-17441-jabenn) တွင် region များကို မြေပုံပေါ်တွင် တွေ့နိုင်ပါသည်။

1. `soil-moisture-sensor` ဟုခေါ်သော resource group တစ်ခု ဖန်တီးရန် အောက်ပါ command ကို run လုပ်ပါ။ Resource group အမည်များသည် သင်၏ subscription အတွင်းတွင် ထူးခြားရမည်ဖြစ်သည်။

    ```sh
    az group create --name soil-moisture-sensor \
                    --location <location>
    ```

    `<location>` ကို သင်ရွေးချယ်ထားသောနေရာဖြင့် အစားထိုးပါ။

### အလုပ် - IoT Hub တစ်ခု ဖန်တီးပါ

အခုတော့ သင်၏ resource group အတွင်း IoT Hub resource တစ်ခု ဖန်တီးနိုင်ပါပြီ။

1. IoT Hub resource ကို ဖန်တီးရန် အောက်ပါ command ကို အသုံးပြုပါ။

    ```sh
    az iot hub create --resource-group soil-moisture-sensor \
                      --sku F1 \
                      --partition-count 2 \
                      --name <hub_name>
    ```

    `<hub_name>` ကို သင်၏ hub အတွက် အမည်ဖြင့် အစားထိုးပါ။ ဒီအမည်သည် ကမ္ဘာတစ်ဝှမ်းတွင် ထူးခြားရမည်ဖြစ်သည် - အခြားသူတစ်ဦးမှ ဖန်တီးထားသော IoT Hub တစ်ခုမှ ဒီအမည်ကို မရှိရပါ။ ဒီအမည်ကို hub ကိုညွှန်းသော URL တွင် အသုံးပြုမည်ဖြစ်သည်။ `soil-moisture-sensor-` ဟုစပြီး ထူးခြားသော identifier (ဥပမာ - စကားလုံးတစ်ချို့ သို့မဟုတ် သင်၏နာမည်) ကို ထည့်ပါ။

    `--sku F1` option သည် free tier ကို အသုံးပြုရန် ပြောသည်။ Free tier သည် တစ်နေ့လျှင် 8,000 messages ကို ပံ့ပိုးပေးပြီး အခြား tier များ၏ အင်္ဂါရပ်များအများစုကို ပါဝင်စေသည်။

    > 🎓 Azure ဝန်ဆောင်မှုများ၏ စျေးနှုန်းအဆင့်များကို tiers ဟုခေါ်သည်။ Tier တစ်ခုစီတွင် ကုန်ကျစရိတ်ကွာခြားမှုနှင့် အင်္ဂါရပ်များ သို့မဟုတ် ဒေတာပမာဏများ ကွာခြားမှုရှိသည်။

    > 💁 စျေးနှုန်းအကြောင်းပိုမိုလေ့လာလိုပါက [Azure IoT Hub pricing guide](https://azure.microsoft.com/pricing/details/iot-hub/?WT.mc_id=academic-17441-jabenn) ကို ကြည့်ပါ။

    `--partition-count 2` option သည် IoT Hub ပံ့ပိုးပေးသော ဒေတာစီးကြောင်းအရေအတွက်ကို သတ်မှတ်သည်။ Partition များသည် IoT Hub သို့ data ရေးသားခြင်းနှင့် ဖတ်ရှုခြင်းများအတွက် data blocking ကို လျှော့ချပေးသည်။ Partition များသည် ဒီသင်ခန်းစာများ၏ အကျုံးအတွင်းမရှိသော်လည်း free tier IoT Hub တစ်ခု ဖန်တီးရန် ဒီတန်ဖိုးကို သတ်မှတ်ရမည်။

    > 💁 Subscription တစ်ခုလျှင် free tier IoT Hub တစ်ခုသာ ရှိနိုင်သည်။

IoT Hub ကို ဖန်တီးမည်ဖြစ်သည်။ ဒီလုပ်ငန်းစဉ်ကို ပြီးစီးရန် မိနစ်အနည်းငယ်ကြာနိုင်သည်။

## IoT Hub နှင့် ဆက်သွယ်ပါ

ယခင်သင်ခန်းစာတွင် သင်သည် MQTT ကို အသုံးပြုကာ ခေါင်းစဉ်အမျိုးမျိုးပေါ်တွင် message များကို ပို့ပေးခဲ့သည်။ IoT Hub တွင်တော့ device နှင့် Hub အကြား ဆက်သွယ်ရန် သတ်မှတ်ထားသော နည်းလမ်းအမျိုးမျိုး ရှိသည်။

> 💁 IoT Hub နှင့် သင်၏ device အကြား ဆက်သွယ်မှုသည် MQTT, HTTPS သို့မဟုတ် AMQP ကို အသုံးပြုနိုင်သည်။

* Device to cloud (D2C) messages - device မှ IoT Hub သို့ ပို့သော message များဖြစ်သည်။ ဥပမာ - telemetry data များ။ Application code မှ message များကို IoT Hub မှ ဖတ်ရှုနိုင်သည်။

    > 🎓 IoT Hub သည် [Event Hubs](https://docs.microsoft.com/azure/event-hubs/?WT.mc_id=academic-17441-jabenn) ဟုခေါ်သော Azure ဝန်ဆောင်မှုကို အသုံးပြုသည်။ Hub သို့ ပို့သော message များကို ဖတ်ရန် code ရေးသားသောအခါ event ဟုခေါ်သည်။

* Cloud to device (C2D) messages - application code မှ IoT Hub ကိုဖြတ်ပြီး IoT device သို့ ပို့သော message များဖြစ်သည်။

* Direct method requests - application code မှ IoT Hub ကိုဖြတ်ပြီး IoT device သို့ actuator တစ်ခုကို ထိန်းချုပ်ရန် တောင်းဆိုမှု message များပို့သည်။ ဒီ message များသည် response တစ်ခုလိုအပ်သည်။

* Device twins - JSON document များဖြစ်ပြီး device နှင့် IoT Hub အကြား synchronization ပြုလုပ်ထားသည်။ Device ၏ settings သို့မဟုတ် properties များကို သိမ်းဆည်းရန် အသုံးပြုသည်။

IoT Hub သည် message များနှင့် direct method requests များကို သတ်မှတ်ထားသော အချိန်ကာလအတွင်း (default အနေဖြင့် တစ်ရက်) သိမ်းဆည်းထားနိုင်သည်။ Device သို့မဟုတ် application code သည် reconnect ပြုလုပ်သောအခါ message များကို ပြန်လည်ရယူနိုင်သည်။

✅ လေ့လာပါ - [Device-to-cloud communications guidance](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-d2c-guidance?WT.mc_id=academic-17441-jabenn) နှင့် [Cloud-to-device communications guidance](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-c2d-guidance?WT.mc_id=academic-17441-jabenn) ကို ဖတ်ပါ။

## သင်၏ device ကို IoT ဝန်ဆောင်မှုနှင့် ချိတ်ဆက်ပါ

Hub ကို ဖန်တီးပြီးနောက် သင်၏ IoT device သည် hub နှင့် ချိတ်ဆက်နိုင်ပါပြီ။ Register လုပ်ထားသော device များသာ ဝန်ဆောင်မှုနှင့် ချိတ်ဆက်နိုင်သည်။ Device ကို register ပြုလုပ်ပြီးနောက် connection string ကို ရယူနိုင်သည်။

> 🎓 Connection string သည် ဝန်ဆောင်မှုများနှင့် ချိတ်ဆက်ရန် အသုံးပြုသော text တစ်ခုဖြစ်သည်။

> ⚠️ Connection string များကို လုံခြုံစွာ သိမ်းဆည်းပါ! 

### အလုပ် - သင်၏ IoT device ကို register ပြုလုပ်ပါ

IoT Hub တွင် IoT device ကို Azure CLI အသုံးပြု၍ register ပြုလုပ်နိုင်သည်။

1. အောက်ပါ command ကို run လုပ်ပါ။

    ```sh
    az iot hub device-identity create --device-id soil-moisture-sensor \
                                      --hub-name <hub_name>
    ```

    `<hub_name>` ကို သင်၏ IoT Hub အမည်ဖြင့် အစားထိုးပါ။

1. Connection string ကို ရယူရန် အောက်ပါ command ကို run လုပ်ပါ။

    ```sh
    az iot hub device-identity connection-string show --device-id soil-moisture-sensor \
                                                      --output table \
                                                      --hub-name <hub_name>
    ```

    `<hub_name>` ကို သင်၏ IoT Hub အမည်ဖြင့် အစားထိုးပါ။

1. Output တွင် ဖော်ပြထားသော connection string ကို သိမ်းဆည်းပါ။

### အလုပ် - သင်၏ IoT device ကို cloud နှင့် ချိတ်ဆက်ပါ

အောက်ပါလမ်းညွှန်ချက်များကို လိုက်နာပါ။

* [Arduino - Wio Terminal](wio-terminal-connect-hub.md)
* [Single-board computer - Raspberry Pi/Virtual IoT device](single-board-computer-connect-hub.md)

### အလုပ် - event များကို စောင့်ကြည့်ပါ

IoT device မှ ပေးပို့သော message များကို Azure CLI အသုံးပြု၍ စောင့်ကြည့်နိုင်သည်။

1. IoT device ကို run လုပ်ပြီး soil moisture telemetry values ပေးပို့ပါ။

1. အောက်ပါ command ကို run လုပ်ပါ။

    ```sh
    az iot hub monitor-events --hub-name <hub_name>
    ```

    `<hub_name>` ကို သင်၏ IoT Hub အမည်ဖြင့် အစားထိုးပါ။

    Console output တွင် IoT device မှ ပေးပို့သော message များကို တွေ့ရမည်။

    ```output
    Starting event monitor, use ctrl-c to stop...
    {
        "event": {
            "origin": "soil-moisture-sensor",
            "module": "",
            "interface": "",
            "component": "",
            "payload": "{\"soil_moisture\": 376}"
        }
    },
    {
        "event": {
            "origin": "soil-moisture-sensor",
            "module": "",
            "interface": "",
            "component": "",
            "payload": "{\"soil_moisture\": 381}"
        }
    }
    ```

    `payload` ၏ အကြောင်းအရာသည် IoT device မှ ပေးပို့သော message နှင့် ကိုက်ညီမည်။

    > Apple Silicon အသုံးပြုသူများအတွက် `az iot` extension သည် အပြည့်အဝ အလုပ်မလုပ်သေးပါ။ Apple Silicon device အသုံးပြုပါက [Azure IoT Tools for Visual Studio Code](https://docs.microsoft.com/en-us/azure/iot-hub/iot-hub-vscode-iot-toolkit-cloud-device-messaging) ကို အသုံးပြုပါ။

1. Message များတွင် timestamp အပါအဝင် properties များစွာ ပါဝင်သည်။ အားလုံးကို ကြည့်ရန် အောက်ပါ command ကို run လုပ်ပါ။

    ```sh
    az iot hub monitor-events --properties anno --hub-name <hub_name>
    ```

    `<hub_name>` ကို သင်၏ IoT Hub အမည်ဖြင့် အစားထိုးပါ။

    Console output တွင် IoT device မှ ပေးပို့သော message များကို တွေ့ရမည်။

    ```output
    Starting event monitor, use ctrl-c to stop...
    {
        "event": {
            "origin": "soil-moisture-sensor",
            "module": "",
            "interface": "",
            "component": "",
            "properties": {},
            "annotations": {
                "iothub-connection-device-id": "soil-moisture-sensor",
                "iothub-connection-auth-method": "{\"scope\":\"device\",\"type\":\"sas\",\"issuer\":\"iothub\",\"acceptingIpFilterRule\":null}",
                "iothub-connection-auth-generation-id": "637553997165220462",
                "iothub-enqueuedtime": 1619976150288,
                "iothub-message-source": "Telemetry",
                "x-opt-sequence-number": 1379,
                "x-opt-offset": "550576",
                "x-opt-enqueued-time": 1619976150277
            },
            "payload": "{\"soil_moisture\": 381}"
        }
    }
    ```

    Time value များသည် [UNIX time](https://wikipedia.org/wiki/Unix_time) ဖြစ်သည်။

    Event monitor ကို ပြီးဆုံးပါက ထွက်ပါ။

### အလုပ် - သင်၏ IoT device ကို ထိန်းချုပ်ပါ

Azure CLI ကို အသုံးပြု၍ IoT device တွင် direct methods ကို ခေါ်နိုင်သည်။

1. IoT device တွင် `relay_on` method ကို invoke ပြုလုပ်ရန် အောက်ပါ command ကို run လုပ်ပါ။

    ```sh
    az iot hub invoke-device-method --device-id soil-moisture-sensor \
                                    --method-name relay_on \
                                    --method-payload '{}' \
                                    --hub-name <hub_name>
    ```

    `
<hub_name>
` with the name you used for your IoT Hub.

ဒီဟာက `method-name` ဆိုတဲ့နည်းလမ်းအမည်အတွက် direct method request ကိုပို့ပါတယ်။ Direct methods တွေဟာ နည်းလမ်းအတွက် data ပါဝင်တဲ့ payload ကိုယူနိုင်ပြီး၊ ဒီ payload ကို JSON အနေနဲ့ `method-payload` parameter မှာ သတ်မှတ်နိုင်ပါတယ်။

သင့် IoT device မှ relay အဖွင့်ပြီး၊ အတူတူ output ကိုတွေ့ရပါမယ်။

```output
    Direct method received -  relay_on
    ```

1. အထက်ပါအဆင့်ကို ထပ်လုပ်ပါ၊ ဒါပေမယ့် `--method-name` ကို `relay_off` အဖြစ်သတ်မှတ်ပါ။ သင့် IoT device မှ relay အပိတ်ပြီး၊ အတူတူ output ကိုတွေ့ရပါမယ်။

---

## 🚀 စိန်ခေါ်မှု

IoT Hub ရဲ့ အခမဲ့ tier က တစ်နေ့ကို 8,000 messages ပေးပါတယ်။ သင်ရေးထားတဲ့ code က တစ်စက္ကန့် 10 စက္ကန့်တိုင်း telemetry messages ပို့ပါတယ်။ တစ်စက္ကန့် 10 စက္ကန့်တိုင်း message တစ်ခုဆိုရင် တစ်နေ့မှာ message ဘယ်နှစ်ခုပို့မလဲ?

မြေစိုထိုင်းမှုတိုင်းတာမှုတွေကို ဘယ်နှစ်ခါပို့သင့်လဲဆိုတာကို စဉ်းစားပါ။ အခမဲ့ tier အတွင်းမှာနေပြီး၊ လိုအပ်သလိုစစ်ဆေးနိုင်ဖို့၊ အလွန်မပို့ရအောင် သင့် code ကို ဘယ်လိုပြောင်းလဲနိုင်မလဲ? ဒုတိယ device တစ်ခုထပ်ထည့်ချင်ရင် ဘာလုပ်ရမလဲ?

## Post-lecture quiz

[Post-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/16)

## ပြန်လည်သုံးသပ်ခြင်းနှင့် ကိုယ်တိုင်လေ့လာခြင်း

IoT Hub SDK ဟာ Arduino နဲ့ Python အတွက် open source ဖြစ်ပါတယ်။ GitHub မှာရှိတဲ့ code repos တွေမှာ IoT Hub ရဲ့ feature အမျိုးမျိုးနဲ့အလုပ်လုပ်ပုံကို ပြသထားတဲ့ နမူနာတွေရှိပါတယ်။

* သင် Wio Terminal ကိုသုံးနေတယ်ဆိုရင် [GitHub မှာရှိတဲ့ Arduino နမူနာတွေ](https://github.com/Azure/azure-iot-pal-arduino/tree/master/pal/samples) ကိုကြည့်ပါ။
* သင် Raspberry Pi သို့မဟုတ် Virtual device ကိုသုံးနေတယ်ဆိုရင် [GitHub မှာရှိတဲ့ Python နမူနာတွေ](https://github.com/Azure/azure-iot-sdk-python/tree/master/azure-iot-hub/samples) ကိုကြည့်ပါ။

## လုပ်ငန်းတာဝန်

[Cloud services အကြောင်းလေ့လာပါ](assignment.md)

---

**ဝက်ဘ်ဆိုက်မှတ်ချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှန်ကန်မှုအတွက် ကြိုးစားနေပါသော်လည်း၊ အလိုအလျောက်ဘာသာပြန်မှုများတွင် အမှားများ သို့မဟုတ် မတိကျမှုများ ပါဝင်နိုင်သည်ကို ကျေးဇူးပြု၍ သတိပြုပါ။ မူရင်းစာရွက်စာတမ်းကို ၎င်း၏ မူလဘာသာစကားဖြင့် အာဏာတည်သောရင်းမြစ်အဖြစ် သတ်မှတ်သင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် ပရော်ဖက်ရှင်နယ် လူသားဘာသာပြန်မှုကို အကြံပြုပါသည်။ ဤဘာသာပြန်မှုကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော နားလည်မှုမှားများ သို့မဟုတ် အဓိပ္ပါယ်မှားများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။