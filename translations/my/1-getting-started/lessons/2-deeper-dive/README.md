<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9dd7f645ad1c6f20b72fee512987f772",
  "translation_date": "2025-08-28T17:05:13+00:00",
  "source_file": "1-getting-started/lessons/2-deeper-dive/README.md",
  "language_code": "my"
}
-->
# IoT အကြောင်းပိုမိုနက်ရှိုင်းစွာလေ့လာခြင်း

![ဒီသင်ခန်းစာအတွက် Sketchnote အကျဉ်းချုပ်](../../../../../translated_images/my/lesson-2.324b0580d620c25e0a24fb7fddfc0b29a846dd4b82c08e7a9466d580ee78ce51.jpg)

> Sketchnote ကို [Nitya Narasimhan](https://github.com/nitya) မှရေးသားထားသည်။ ပုံကိုနှိပ်ပြီး ပိုမိုကြီးမားသောဗားရှင်းကိုကြည့်ပါ။

ဒီသင်ခန်းစာကို [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn) မှ [Hello IoT series](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) ၏ အစိတ်အပိုင်းအဖြစ် သင်ကြားခဲ့သည်။ သင်ခန်းစာကို ၁ နာရီကြာသင်ခန်းစာနှင့် ၁ နာရီကြာအခန်းဖွင့်ချိန်အဖြစ် သင်ခန်းစာ၏ အပိုင်းများကိုပိုမိုနက်ရှိုင်းစွာလေ့လာပြီး မေးခွန်းများကိုဖြေဆိုခြင်းအဖြစ် သင်ကြားခဲ့သည်။

[![သင်ခန်းစာ ၂: IoT အကြောင်းပိုမိုနက်ရှိုင်းစွာလေ့လာခြင်း](https://img.youtube.com/vi/t0SySWw3z9M/0.jpg)](https://youtu.be/t0SySWw3z9M)

[![သင်ခန်းစာ ၂: IoT အကြောင်းပိုမိုနက်ရှိုင်းစွာလေ့လာခြင်း - အခန်းဖွင့်ချိန်](https://img.youtube.com/vi/tTZYf9EST1E/0.jpg)](https://youtu.be/tTZYf9EST1E)

> 🎥 အထက်ပါပုံများကိုနှိပ်ပြီး ဗီဒီယိုများကိုကြည့်ပါ

## သင်ခန်းစာမတိုင်မီမေးခွန်း

[သင်ခန်းစာမတိုင်မီမေးခွန်း](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/3)

## အကျဉ်းချုပ်

ဒီသင်ခန်းစာမှာ ယခင်သင်ခန်းစာတွင်ဖော်ပြခဲ့သော အချို့သောအယူအဆများကိုပိုမိုနက်ရှိုင်းစွာလေ့လာပါမည်။

ဒီသင်ခန်းစာမှာ ကျွန်ုပ်တို့လေ့လာမည့်အကြောင်းအရာများမှာ:

* [IoT အက်ပလီကေးရှင်း၏အစိတ်အပိုင်းများ](../../../../../1-getting-started/lessons/2-deeper-dive)
* [Microcontrollers အကြောင်းပိုမိုနက်ရှိုင်းစွာလေ့လာခြင်း](../../../../../1-getting-started/lessons/2-deeper-dive)
* [Single-board computers အကြောင်းပိုမိုနက်ရှိုင်းစွာလေ့လာခြင်း](../../../../../1-getting-started/lessons/2-deeper-dive)

## IoT အက်ပလီကေးရှင်း၏အစိတ်အပိုင်းများ

IoT အက်ပလီကေးရှင်း၏အစိတ်အပိုင်းနှစ်ခုမှာ *အင်တာနက်* နှင့် *အရာဝတ္ထု* ဖြစ်သည်။ အခုဒီအစိတ်အပိုင်းနှစ်ခုကိုပိုမိုအသေးစိတ်လေ့လာကြည့်ရအောင်။

### အရာဝတ္ထု

![Raspberry Pi 4](../../../../../translated_images/my/raspberry-pi-4.fd4590d308c3d456.webp)

IoT ၏ **အရာဝတ္ထု** အပိုင်းသည် ရုပ်ပိုင်းဆိုင်ရာကမ္ဘာနှင့်အပြန်အလှန်ဆက်သွယ်နိုင်သော စက်ကိုဆိုလိုသည်။ ဒီစက်များသည် သေးငယ်ပြီး စျေးနှုန်းသက်သာသောကွန်ပျူတာများဖြစ်ပြီး အမြန်နှုန်းနည်းပြီး အားသုံးမှုနည်းပါသည်။ ဥပမာအားဖြင့် RAM ကီလိုဘိုက်များသာရှိသောရိုးရှင်းသော microcontrollers (PC တွင်ရှိသောဂီဂါဘိုက်များမဟုတ်)၊ PC တွင်ရှိသောဂီဂါဟတ်ဇ်များမဟုတ်ပဲ မီဂါဟတ်ဇ်အနည်းငယ်သာရှိသောအမြန်နှုန်းဖြင့် လည်ပတ်ပြီး ဘက်ထရီများဖြင့် ရက်ပေါင်းများစွာ၊ လများစွာ သို့မဟုတ် နှစ်များစွာအထိ လည်ပတ်နိုင်သောအားသုံးမှုနည်းသောစက်များဖြစ်သည်။

ဒီစက်များသည် ရုပ်ပိုင်းဆိုင်ရာကမ္ဘာနှင့်ဆက်သွယ်ပြီး အနီးအနားမှဒေတာများကို စနစ်တကျစုဆောင်းရန် sensor များကိုအသုံးပြုခြင်း သို့မဟုတ် actuator များကိုထိန်းချုပ်ခြင်းဖြင့် ရုပ်ပိုင်းဆိုင်ရာပြောင်းလဲမှုများကိုလုပ်ဆောင်ခြင်းဖြင့် ဆက်သွယ်သည်။ ဥပမာအားဖြင့် smart thermostat တစ်ခုသည် temperature sensor တစ်ခု၊ dial သို့မဟုတ် touchscreen ကဲ့သို့သော temperature ကိုသတ်မှတ်ရန်နည်းလမ်းတစ်ခုနှင့် အပူချိန်သည်လိုအပ်သောအကွာအဝေးအပြင်မှာရှိနေသောအခါ heating သို့မဟုတ် cooling system ကိုဖွင့်နိုင်သော connection တစ်ခုပါရှိသည်။ Temperature sensor သည် အခန်းအေးနေသည်ကို detect လုပ်ပြီး actuator သည် heating ကိုဖွင့်သည်။

![Temperature နှင့် dial ကို IoT စက်၏ input အဖြစ်ပြသပြီး heater ကိုထိန်းချုပ်သော output အဖြစ်ပြသသော diagram](../../../../../translated_images/my/basic-thermostat.a923217fd1f37e5a6f3390396a65c22a387419ea2dd17e518ec24315ba6ae9a8.png)

IoT စက်များအဖြစ် လုပ်ဆောင်နိုင်သောအရာဝတ္ထုများသည် အမျိုးအစားအများကြီးရှိပြီး တစ်ခုတည်းသောအရာကို detect လုပ်သော dedicated hardware မှ smartphone အထိပါဝင်သည်။ Smartphone တစ်လုံးသည် sensor များကိုအသုံးပြု၍ အနီးအနားကမ္ဘာကို detect လုပ်နိုင်ပြီး actuator များကိုအသုံးပြု၍ ကမ္ဘာနှင့်ဆက်သွယ်နိုင်သည် - ဥပမာအားဖြင့် GPS sensor ကိုအသုံးပြု၍ သင့်တည်နေရာကို detect လုပ်ခြင်းနှင့် speaker ကိုအသုံးပြု၍ သွားရောက်ရန်နေရာအတွက် navigation အညွှန်းများပေးခြင်း။

✅ Sensor မှဒေတာကိုဖတ်ပြီး ဆုံးဖြတ်ချက်များကိုလုပ်ဆောင်သော သင့်အနီးရှိအခြားစနစ်များကိုစဉ်းစားပါ။ ဥပမာတစ်ခုမှာ အိုးပေါ်ရှိ thermostat ဖြစ်သည်။ သင်ပိုမိုများစွာရှာဖွေနိုင်ပါသလား?

### အင်တာနက်

IoT အက်ပလီကေးရှင်း၏ **အင်တာနက်** အပိုင်းသည် IoT စက်သည် ဒေတာပို့ရန်နှင့်လက်ခံရန်ဆက်သွယ်နိုင်သောအက်ပလီကေးရှင်းများနှင့် IoT စက်မှဒေတာကို process လုပ်ရန်နှင့် IoT စက်၏ actuator များကိုပို့ရန် request များကိုလုပ်ဆောင်ရန်အက်ပလီကေးရှင်းများကိုပါဝင်သည်။

ပုံမှန် setup တစ်ခုမှာ IoT စက်သည်ဆက်သွယ်သော cloud service တစ်ခုရှိပြီး ဒီ cloud service သည် security ကဲ့သို့သောအရာများကို handle လုပ်ခြင်း၊ IoT စက်မှ message များကိုလက်ခံခြင်းနှင့် IoT စက်သို့ message များကိုပြန်ပို့ခြင်းတို့ကိုလုပ်ဆောင်သည်။ ဒီ cloud service သည် sensor data ကို process သို့မဟုတ် store လုပ်သောအခြားအက်ပလီကေးရှင်းများနှင့်ဆက်သွယ်ခြင်း သို့မဟုတ် အခြားစနစ်များမှဒေတာနှင့် sensor data ကိုအသုံးပြု၍ ဆုံးဖြတ်ချက်များကိုလုပ်ဆောင်ခြင်းတို့ကိုလုပ်ဆောင်သည်။

စက်များသည် WiFi သို့မဟုတ် wired connection များကိုအသုံးပြု၍ အင်တာနက်နှင့်တိုက်ရိုက်ဆက်သွယ်မည်မဟုတ်ပါ။ အချို့သောစက်များသည် mesh networking ကိုအသုံးပြု၍ Bluetooth ကဲ့သို့သောနည်းပညာများကိုအသုံးပြု၍ hub device တစ်ခုမှတဆင့် အင်တာနက် connection ရှိသောနေရာတွင်တစ်ဦးနှင့်တစ်ဦးဆက်သွယ်သည်။

Smart thermostat ၏ဥပမာတွင် thermostat သည် home WiFi ကိုအသုံးပြု၍ cloud service တစ်ခုနှင့်ဆက်သွယ်သည်။ အပူချိန်ဒေတာကို cloud service သို့ပို့ပြီး homeowner သည် phone app ကိုအသုံးပြု၍ လက်ရှိနှင့်အတိတ်အပူချိန်များကိုစစ်ဆေးနိုင်ရန် database တစ်ခုသို့ရေးသားသည်။ Cloud service တွင် homeowner သည်လိုအပ်သောအပူချိန်ကိုသိပြီး IoT စက်၏ actuator ကို heating system ကိုဖွင့်ရန် သို့မဟုတ်ပိတ်ရန်ပြောဆိုသော message များကို cloud service မှတဆင့် IoT စက်သို့ပြန်ပို့သည်။

![Temperature နှင့် dial ကို IoT စက်၏ input အဖြစ်ပြသပြီး IoT စက်သည် cloud နှင့် ၂ မျက်နှာတစ်ပြင်ဆက်သွယ်ခြင်း၊ cloud သည် phone နှင့် ၂ မျက်နှာတစ်ပြင်ဆက်သွယ်ခြင်း၊ heater ကိုထိန်းချုပ်သော output အဖြစ် IoT စက်မှပြသသော diagram](../../../../../translated_images/my/mobile-controlled-thermostat.4a994010473d8d6a52ba68c67e5f02dc8928c717e93ca4b9bc55525aa75bbb60.png)

ပိုမို smart ဖြစ်သော version တစ်ခုမှာ cloud တွင် AI ကိုအသုံးပြု၍ occupancy sensor ကဲ့သို့သော IoT စက်များနှင့်ဆက်သွယ်သော sensor များမှဒေတာများ၊ weather နှင့် calendar ကဲ့သို့သောဒေတာများကိုအသုံးပြု၍ temperature ကို smart ဖြစ်အောင်သတ်မှတ်ရန်ဆုံးဖြတ်ချက်များကိုလုပ်ဆောင်သည်။ ဥပမာအားဖြင့် calendar မှ vacation သွားနေသည်ကိုဖတ်ပြီး heating ကိုပိတ်နိုင်သည် သို့မဟုတ် သင့်အသုံးပြုသောအခန်းများပေါ်မူတည်၍ room by room အပူချိန်ကိုပိတ်နိုင်သည်။ ဒေတာမှတဆင့်ပိုမိုတိကျစွာလေ့လာနိုင်ရန်အချိန်ကြာလာသည်နှင့်အမျှပိုမိုတိုးတက်လာသည်။

![Temperature sensor များနှင့် dial ကို IoT စက်၏ input အဖြစ်ပြသပြီး IoT စက်သည် cloud နှင့် ၂ မျက်နှာတစ်ပြင်ဆက်သွယ်ခြင်း၊ cloud သည် phone, calendar နှင့် weather service နှင့် ၂ မျက်နှာတစ်ပြင်ဆက်သွယ်ခြင်း၊ heater ကိုထိန်းချုပ်သော output အဖြစ် IoT စက်မှပြသသော diagram](../../../../../translated_images/my/smarter-thermostat.a75855f15d2d9e63.webp)

✅ အင်တာနက်နှင့်ဆက်သွယ်သော thermostat ကိုပိုမို smart ဖြစ်အောင်လုပ်ဆောင်ရန်အခြားဒေတာများကူညီနိုင်မည်ကဲ့သို့ဖြစ်မည်ကိုစဉ်းစားပါ။

### Edge တွင် IoT

IoT ၏ I သည် အင်တာနက်ကိုဆိုလိုသော်လည်း ဒီစက်များသည် အင်တာနက်နှင့်ဆက်သွယ်ရန်မလိုအပ်ပါ။ အချို့သောအခါများတွင် စက်များသည် 'edge' စက်များ - သင့် local network တွင် run လုပ်သော gateway စက်များနှင့်ဆက်သွယ်နိုင်ပြီး ဒေတာကို အင်တာနက်မှတဆင့် call မလုပ်ဘဲ process လုပ်နိုင်သည်။ ဒေတာများများရှိသောအခါ သို့မဟုတ် အင်တာနက် connection နှေးသောအခါပိုမိုလျင်မြန်နိုင်သည်၊ အင်တာနက် connection မဖြစ်နိုင်သောနေရာတွင် offline အဖြစ် run လုပ်နိုင်သည် - ဥပမာအားဖြင့် သင်္ဘောပေါ်တွင် သို့မဟုတ် လူသားအကူအညီပေးရေးအရေးပေါ်အခြေအနေတွင် run လုပ်ခြင်း၊ ဒေတာကို private ဖြစ်အောင်ထားနိုင်သည်။ အချို့သောစက်များသည် cloud tools ကိုအသုံးပြု၍ ဖန်တီးထားသော processing code ကိုပါရှိပြီး ဒေတာကိုစုဆောင်းရန်နှင့် အင်တာနက် connection မလိုအပ်ဘဲ ဆုံးဖြတ်ချက်ကိုပြုလုပ်ရန် locally တွင် run လုပ်သည်။

ဥပမာတစ်ခုမှာ Apple HomePod, Amazon Alexa သို့မဟုတ် Google Home ကဲ့သို့သော smart home device ဖြစ်ပြီး cloud တွင် training လုပ်ထားသော AI models ကိုအသုံးပြု၍ သင့်အသံကိုနားထောင်သည်။ ဒီစက်များသည် စကားလုံး သို့မဟုတ် စကားစုတစ်ခုကိုပြောသောအခါ 'wake up' လုပ်ပြီး သင့်စကားကို process လုပ်ရန်အင်တာနက်မှတဆင့်ပို့သည်။ စက်သည် သင့်စကားတွင် pause တစ်ခု detect လုပ်သောအခါ သင့်စကားကိုပို့ခြင်းကိုရပ်သည်။ Wake word ဖြင့်စက်ကို wake up လုပ်သောအခါမပြောသောအရာအားလုံးနှင့် စက်သည်နားထောင်ရပ်သောအခါမပြောသောအရာအားလုံးသည် device provider သို့အင်တာနက်မှတဆင့်မပို့ပါ၊ ထို့ကြောင့် private ဖြစ်သည်။

✅ Privacy အရေးကြီးသောအခြေအနေများကိုစဉ်းစားပြီး ဒေတာကို cloud တွင်မလုပ်ဘဲ edge တွင် process လုပ်ခြင်းကပိုမိုကောင်းမည်ဖြစ်သည်။ အကြံပြုချက် - camera သို့မဟုတ် imaging device များပါရှိသော IoT စက်များကိုစဉ်းစားပါ။

### IoT Security

အင်တာနက် connection တစ်ခုရှိသောအခါ security သည်အရေးကြီးသောအချက်ဖြစ်သည်။ 'IoT တွင် S သည် Security ကိုဆိုလိုသည်' ဟုဆိုသောဟာသဟောင်းတစ်ခုရှိသည် - IoT တွင် 'S' မရှိပါ၊ security မရှိကြောင်းကိုဆိုလိုသည်။

IoT စက်များသည် cloud service တစ်ခုနှင့်ဆက်သွယ်ပြီး ထို့ကြောင့် security သည် cloud service ရဲ့ security အပေါ်မူတည်သည် - သင့် cloud service သည် စက်မည်သည့်စက်မဆိုဆက်သွယ်ခွင့်ပြုပါက malicious data ပို့ခြင်း သို့မဟုတ် virus တိုက်ခိုက်မှုများဖြစ်နိုင်သည်။ IoT စက်များသည်အခြားစက်များနှင့်ဆက်သွယ်ပြီး ထိန်းချုပ်သောကြောင့် ဒီအရာသည် အလွန်အရေးကြီးသောအကျိုးသက်ရောက်မှုများရှိနိုင်သည်။ ဥပမာအားဖြင့် [Stuxnet worm](https://wikipedia.org/wiki/Stuxnet) သည် centrifuge များရှိ valves များကို manipulate လုပ်ပြီး ပျက်စီးစေခဲ့သည်။ Hackers များသည် [security အားနည်းချက်များကိုအသုံးပြု၍ baby monitors](https://www.npr.org/sections/thetwo-way/2018/06/05/617196788/s-c-mom-says-baby-monitor-was-hacked-experts-say-many-devices-are-vulnerable) နှင့် အခြား home surveillance devices များကို access လုပ်ခဲ့သည်။

> 💁 IoT စက်များနှင့် edge စက်များသည် ဒေတာကို private ဖြစ်အောင်ထားရန်နှင့် security ရှိစေရန် အင်တာနက်မှလုံးဝခွဲထားသော network တွင် run လုပ်သည်။ ဒီအရာကို [air-gapping](https://wikipedia.org/wiki/Air_gap_(networking)) ဟုခေါ်သည်။

## Microcontrollers အကြောင်းပိုမိုနက်ရှိုင်းစွာလေ့လာခြင်း

ယခင်သင်ခန်းစာတွင် microcontrollers ကိုမိတ်ဆက်ခဲ့သည်။ အခုတော့ ဒီအကြောင်းပိုမိုနက်ရှိုင်းစွာလေ့လာကြည့်ရအောင်။

### CPU

CPU သည် microcontroller ၏ 'ဦးနှောက်' ဖြစ်သည်။ ၎င်းသည် သင့် code ကို run လုပ်ပြီး connected devices များမှဒေတာကိုပို့ရန်နှင့်လက်ခံရန်လုပ်ဆောင်နိုင်သော processor ဖြစ်သည်။ CPUs တွင် core တစ်ခု သို့မဟုတ် core အများအပြားပါရှိနိုင်သည် - အဓိကအားဖြင့် သင့် code ကို run လုပ်ရန်အတူတကွလုပ်ဆောင်နိုင်သော CPU များဖြစ်သည်။

CPUs သည် တစ်စက္ကန့်တွင် သန်းပေါင်းများ သို့မဟုတ် ဘီလီယံပေါင်းများအကြိမ် tick လုပ်သော clock ကိုအပေါ်မူတည်သည်။ Tick သို့မဟုတ် cycle တစ်ခုစီသည် CPU လုပ်ဆောင်နိုင်သော actions များကို synchronize လုပ်သည်။ Tick တစ်ခုစီတွင် CPU သည် program မှ instruction တစ်ခုကို retrieve လုပ်ခြင်း သို့မဟုတ် mathematical calculation တစ်ခုကိုလုပ်ဆောင်ခြင်းကဲ့သို့သော instruction တစ်ခုကို execute လုပ်နိုင်သည်။ ဒီ regular cycle သည် next instruction ကို process လုပ်မည့်အခါမတိုင်မီ အားလုံးကိုပြီးစီးစေရန်အထောက်အကူပြုသည်။

Clock cycle ပိုမြန်လျင် တစ်စက္ကန့်တွင် process လုပ်နိုင်သော instruction ပိုများပြီး CPU
> 🎓 အစီအစဉ်မှတ်ဉာဏ်သည် သင့်ကုဒ်ကို သိမ်းဆည်းထားပြီး လျှပ်စစ်မရှိသည့်အချိန်တွင်လည်း မပျောက်ဆုံးပါ။
🎓 RAM သည် သင့်ပရိုဂရမ်ကို အလုပ်လုပ်စေဖို့ အသုံးပြုပြီး လျှပ်စစ်မရှိတဲ့အခါမှာ ပြန်လည်သက်သာသွားပါသည်။

CPU နဲ့တူတူပဲ၊ microcontroller ရဲ့ memory ဟာ PC သို့မဟုတ် Mac ထက် အများကြီးသေးငယ်ပါတယ်။ ပုံမှန် PC တစ်ခုမှာ 8 Gigabytes (GB) RAM ရှိနိုင်ပြီး၊ 8,000,000,000 bytes ရှိပါတယ်။ Byte တစ်ခုမှာ အက္ခရာတစ်လုံး သို့မဟုတ် 0-255 အတွင်းက နံပါတ်တစ်ခုကို သိမ်းဆည်းဖို့ လုံလောက်တဲ့နေရာရှိပါတယ်။ Microcontroller တစ်ခုမှာတော့ RAM ရဲ့ Kilobytes (KB) ပမာဏသာရှိပြီး၊ kilobyte တစ်ခုမှာ 1,000 bytes ရှိပါတယ်။ အထက်မှာဖော်ပြထားတဲ့ Wio terminal မှာ 192KB RAM ရှိပြီး၊ 192,000 bytes ရှိပါတယ်။ ဒါဟာ ပုံမှန် PC တစ်ခုထက် 40,000 ဆလျော့နည်းပါတယ်။

အောက်မှာပါတဲ့ အကြမ်းဖျင်းပုံစံက 192KB နဲ့ 8GB ရဲ့ အရွယ်အစားကွာခြားမှုကို ပြထားပါတယ်။ အလယ်မှာပါတဲ့ သေးငယ်တဲ့ dot က 192KB ကို ကိုယ်စားပြုပါတယ်။

![192KB နဲ့ 8GB ရဲ့ အရွယ်အစားကွာခြားမှု - 40,000 ဆကြီး](../../../../../translated_images/my/ram-comparison.6beb73541b42ac6f.webp)

ပရိုဂရမ်ကို သိမ်းဆည်းဖို့နေရာလည်း PC ထက် သေးငယ်ပါတယ်။ ပုံမှန် PC တစ်ခုမှာ 500GB hard drive ရှိပြီး၊ microcontroller တစ်ခုမှာတော့ kilobytes သို့မဟုတ် megabytes (MB) အနည်းငယ်သာရှိနိုင်ပါတယ်။ (1MB = 1,000KB = 1,000,000 bytes) Wio terminal မှာ 4MB program storage ရှိပါတယ်။

✅ သင့်ရဲ့ computer ရဲ့ RAM နဲ့ storage ပမာဏကို ရှာဖွေကြည့်ပါ။ Microcontroller နဲ့ ဘယ်လိုကွာခြားလဲဆိုတာကို နှိုင်းယှဉ်ကြည့်ပါ။

### Input/Output

Microcontroller တွေဟာ sensor တွေကနေ data ကိုဖတ်ပြီး actuator တွေကို control signal ပို့ဖို့ input/output (I/O) connection တွေလိုအပ်ပါတယ်။ အများအားဖြင့် general-purpose input/output (GPIO) pins အတော်များများပါဝင်ပါတယ်။ ဒီ pins တွေကို software မှာ input (signal ကို လက်ခံ) သို့မဟုတ် output (signal ကို ပို့) အဖြစ် configure လုပ်နိုင်ပါတယ်။

🧠⬅️ Input pins တွေကို sensor တွေကနေ value ဖတ်ဖို့ အသုံးပြုပါတယ်။

🧠➡️ Output pins တွေ actuator တွေကို instruction ပို့ဖို့ အသုံးပြုပါတယ်။

✅ ဒီအကြောင်းကို နောက်ဆုံးပေါ်သင်ခန်းစာမှာ ပိုမိုလေ့လာနိုင်ပါမယ်။

#### Task

Wio Terminal ကို စူးစမ်းလေ့လာပါ။

ဒီသင်ခန်းစာတွေမှာ Wio Terminal ကို အသုံးပြုနေတယ်ဆိုရင်၊ GPIO pins တွေကို ရှာဖွေပါ။ [Wio Terminal product page](https://www.seeedstudio.com/Wio-Terminal-p-4509.html) ရဲ့ *Pinout diagram* အပိုင်းကို ရှာဖွေပြီး ဘယ် pins ဘယ်လိုအသုံးပြုရမလဲကို လေ့လာပါ။ Wio Terminal မှာ pin numbers ပါတဲ့ sticker တစ်ခုပါဝင်ပြီး၊ အဲဒီ sticker ကို device ရဲ့နောက်ဘက်မှာ တပ်ဆင်နိုင်ပါတယ်။ မတပ်ဆင်ရသေးရင် အခုတပ်ဆင်ပါ။

### Physical size

Microcontroller တွေဟာ အရွယ်အစားသေးငယ်ပါတယ်။ အနည်းဆုံး [Freescale Kinetis KL03 MCU](https://www.edn.com/tiny-arm-cortex-m0-based-mcu-shrinks-package/) က golf ball ရဲ့ dimple ထဲမှာတောင် ထည့်နိုင်အောင် သေးငယ်ပါတယ်။ PC ရဲ့ CPU တစ်ခုက 40mm x 40mm အရွယ်ရှိပြီး၊ CPU ကို အပူလွန်ကဲမှုမဖြစ်အောင် အေးစေဖို့ heat sinks နဲ့ fans တွေလိုအပ်ပါတယ်။ ဒါဟာ microcontroller တစ်ခုထက် အများကြီးကြီးမားပါတယ်။ Wio terminal developer kit မှာ microcontroller, case, screen နဲ့ connection တွေ၊ components တွေပါဝင်ပြီး၊ bare Intel i9 CPU ထက် အနည်းငယ်ကြီးမားပါတယ်။ ဒါပေမယ့် heat sink နဲ့ fan ပါတဲ့ CPU ထက် အများကြီးသေးငယ်ပါတယ်။

| Device                          | Size                  |
| ------------------------------- | --------------------- |
| Freescale Kinetis KL03          | 1.6mm x 2mm x 1mm     |
| Wio terminal                    | 72mm x 57mm x 12mm    |
| Intel i9 CPU, Heat sink and fan | 136mm x 145mm x 103mm |

### Frameworks and operating systems

Microcontroller တွေဟာ အမြန်နှုန်းနဲ့ memory size နည်းတဲ့အတွက် desktop OS မရနိုင်ပါဘူး။ Windows, Linux, macOS စတဲ့ OS တွေဟာ memory နဲ့ processing power အများကြီးလိုအပ်ပြီး၊ microcontroller တွေမှာ မလိုအပ်တဲ့ task တွေကို run ဖို့အတွက် ရည်ရွယ်ထားပါတယ်။ Microcontroller တွေဟာ အထူးသတ်မှတ်ထားတဲ့ task တစ်ခု သို့မဟုတ် task အနည်းငယ်ကို run ဖို့အတွက် program လုပ်ထားတာဖြစ်ပြီး၊ PC သို့မဟုတ် Mac တစ်ခုလို general-purpose computer မဟုတ်ပါဘူး။

OS မပါဘဲ microcontroller ကို program လုပ်ဖို့ tooling တစ်ခုလိုအပ်ပါတယ်။ ဒီ tooling က microcontroller run လို့ရအောင် code ကို build လုပ်ဖို့ API တွေကို အသုံးပြုနိုင်ပါတယ်။ Microcontroller တစ်ခုစီက မတူညီတဲ့အတွက်၊ ထုတ်လုပ်သူတွေက normally standard frameworks တွေကို support လုပ်ပြီး၊ framework ကို support လုပ်တဲ့ microcontroller တစ်ခုစီမှာ code ကို build လုပ်ဖို့ standard 'recipe' ကို follow လုပ်နိုင်ပါတယ်။

Microcontroller တွေကို OS အသုံးပြုပြီး program လုပ်နိုင်ပါတယ်။ ဒီ OS တွေကို real-time operating system (RTOS) လို့ခေါ်ပြီး၊ peripherals တွေကို real time မှာ data ပို့ပေးဖို့အတွက် design လုပ်ထားပါတယ်။ RTOS တွေဟာ အလွန်ပေါ့ပါးပြီး အောက်ပါ feature တွေကိုပေးစွမ်းပါတယ်။

* Multi-threading - code block အများကြီးကို တစ်ချိန်တည်းမှာ run လို့ရအောင်၊ သို့မဟုတ် core တစ်ခုမှာ အလှည့်ကျ run လို့ရအောင်လုပ်ပေးပါတယ်။
* Networking - အင်တာနက်ပေါ်မှာ securely ဆက်သွယ်နိုင်ပါတယ်။
* Graphical user interface (GUI) components - screen ပါတဲ့ device တွေမှာ user interface (UI) တည်ဆောက်ဖို့အတွက်။

✅ RTOS အမျိုးမျိုးကို လေ့လာပါ။ [Azure RTOS](https://azure.microsoft.com/services/rtos/?WT.mc_id=academic-17441-jabenn), [FreeRTOS](https://www.freertos.org), [Zephyr](https://www.zephyrproject.org)

#### Arduino

![Arduino logo](../../../../../images/arduino-logo.svg)

[Arduino](https://www.arduino.cc) ဟာ microcontroller framework တွေထဲမှာ အများဆုံးလူသုံးတဲ့ framework ဖြစ်ပြီး၊ ကျောင်းသားတွေ၊ hobbyist တွေ၊ maker တွေကြားမှာ အထူးလူကြိုက်များပါတယ်။ Arduino ဟာ software နဲ့ hardware ပေါင်းစပ်ထားတဲ့ open source electronics platform ဖြစ်ပါတယ်။ Arduino compatible boards တွေကို Arduino ကိုယ်တိုင် သို့မဟုတ် အခြားထုတ်လုပ်သူတွေကနေ ဝယ်ယူနိုင်ပြီး၊ Arduino framework ကို အသုံးပြုပြီး code ရေးနိုင်ပါတယ်။

Arduino boards တွေကို C သို့မဟုတ် C++ နဲ့ code ရေးပါတယ်။ C/C++ ကို အသုံးပြုခြင်းက code ကို အလွန်သေးငယ်စေပြီး၊ microcontroller တစ်ခုလို resource အကန့်အသတ်ရှိတဲ့ device မှာ အမြန် run လို့ရအောင်လုပ်ပေးပါတယ်။ Arduino application ရဲ့ အဓိကအပိုင်းကို sketch လို့ခေါ်ပြီး၊ C/C++ code ဖြစ်ပါတယ်။ Sketch မှာ `setup` နဲ့ `loop` ဆိုတဲ့ function 2 ခုပါဝင်ပါတယ်။ Board ကို start လုပ်တဲ့အခါ Arduino framework code က `setup` function ကို တစ်ကြိမ် run လုပ်ပြီး၊ `loop` function ကို အမြဲတမ်း run လုပ်နေပါတယ်၊ power ပိတ်တဲ့အချိန်အထိ။

`setup` function မှာ WiFi နဲ့ cloud services တွေကို connect လုပ်တာ၊ input/output pins တွေကို initialize လုပ်တာတွေကိုရေးနိုင်ပါတယ်။ `loop` function မှာ sensor ကနေ data ဖတ်ပြီး cloud ကို value ပို့တာတွေကိုရေးနိုင်ပါတယ်။ Loop တစ်ခုစီမှာ delay ထည့်သွင်းရပါမယ်၊ ဥပမာ sensor data ကို 10 စက္ကန့်တစ်ကြိမ်ပို့ချင်ရင် loop ရဲ့အဆုံးမှာ 10 စက္ကန့် delay ထည့်ပြီး၊ microcontroller ကို power save mode မှာထားပြီး၊ 10 စက္ကန့်အကြာမှာ loop ကို ပြန် run လုပ်နိုင်ပါတယ်။

![Arduino sketch - setup function ကို run လုပ်ပြီး၊ loop function ကို အမြဲတမ်း run လုပ်နေ](../../../../../translated_images/my/arduino-sketch.79590cb837ff7a7c6a68d1afda6cab83fd53d3bb1bd9a8bf2eaf8d693a4d3ea6.png)

✅ ဒီ program architecture ကို *event loop* သို့မဟုတ် *message loop* လို့ခေါ်ပါတယ်။ Desktop applications အများစုမှာ ဒီပုံစံကို အသုံးပြုထားပြီး၊ Windows, macOS, Linux OS တွေမှာ run လုပ်တဲ့ application တွေမှာ standard ဖြစ်ပါတယ်။ `loop` function က user interface components (button, keyboard) သို့မဟုတ် device တွေကနေ message တွေကို နားထောင်ပြီး၊ အဲဒီ message တွေကို တုံ့ပြန်ပါတယ်။ [event loop](https://wikipedia.org/wiki/Event_loop) အကြောင်းကို ဒီ article မှာ ပိုမိုဖတ်ရှုနိုင်ပါတယ်။

Arduino က microcontroller နဲ့ I/O pins တွေကို အသုံးပြုဖို့ standard libraries တွေကို ပေးထားပါတယ်။ Arduino code ကို board တစ်ခုမှာရေးပြီး၊ အခြား Arduino board တွေမှာ recompile လုပ်ပြီး run လို့ရပါတယ်၊ pins တွေတူပြီး board တွေက အတူတူ feature တွေ support လုပ်ရင်။

Arduino ecosystem မှာ third-party libraries အများကြီးရှိပြီး၊ sensor နဲ့ actuator တွေကို အသုံးပြုတာ၊ cloud IoT services တွေကို connect လုပ်တာတွေကို အလွယ်တကူလုပ်နိုင်ပါတယ်။

##### Task

Wio Terminal ကို စူးစမ်းလေ့လာပါ။

ဒီသင်ခန်းစာတွေမှာ Wio Terminal ကို အသုံးပြုနေတယ်ဆိုရင်၊ အရင်သင်ခန်းစာမှာရေးထားတဲ့ code ကို ပြန်ဖတ်ပါ။ `setup` နဲ့ `loop` function ကို ရှာဖွေပါ။ Loop function က serial output ကို အမြဲတမ်း monitor လုပ်နေတဲ့အကြောင်းကို သတိပြုပါ။ `setup` function မှာ serial port ကိုရေးဖို့ code ထည့်ပြီး၊ device ကို reboot လုပ်တိုင်း ဒီ code က တစ်ကြိမ်ပဲ run လုပ်တာကို သတိပြုပါ။ Side မှာရှိတဲ့ power switch ကို အသုံးပြုပြီး device ကို reboot လုပ်ပြီး၊ device reboot လုပ်တိုင်း `setup` function က run လုပ်တာကို ပြသပါ။

## Single-board computers အကြောင်းပိုမိုလေ့လာခြင်း

အရင်သင်ခန်းစာမှာ single-board computers ကို မိတ်ဆက်ပေးခဲ့ပါတယ်။ အခုတော့ အဲဒီအကြောင်းကို ပိုမိုနက်နက်ရှိုင်းရှိုင်းလေ့လာကြည့်ပါမယ်။

### Raspberry Pi

![Raspberry Pi logo](../../../../../translated_images/my/raspberry-pi-logo.4efaa16605cee054.webp)

[Raspberry Pi Foundation](https://www.raspberrypi.org) ဟာ UK မှ charity တစ်ခုဖြစ်ပြီး၊ 2009 ခုနှစ်မှာ ကျောင်းတွေရဲ့ computer science ပညာသင်ကြားမှုကို မြှင့်တင်ဖို့ ရည်ရွယ်ပြီး စတင်တည်ထောင်ခဲ့ပါတယ်။ ဒီရည်ရွယ်ချက်အတွက် Raspberry Pi ဆိုတဲ့ single-board computer ကို ဖန်တီးခဲ့ပါတယ်။ Raspberry Pi တွေဟာ full size version, Pi Zero, compute module ဆိုပြီး 3 မျိုးရှိပါတယ်။

![Raspberry Pi 4](../../../../../translated_images/my/raspberry-pi-4.fd4590d308c3d456.webp)

Raspberry Pi ရဲ့ နောက်ဆုံးပေါ် full size version က Raspberry Pi 4B ဖြစ်ပါတယ်။ Quad-core (4 core) CPU 1.5GHz, 2, 4, 8GB RAM, gigabit ethernet, WiFi, 2 HDMI ports (4k screen support), audio/composite video output port, USB ports (2 USB 2.0, 2 USB 3.0), 40 GPIO pins, camera connector, SD card slot ပါဝင်ပြီး၊ အရွယ်အစား 88mm x 58mm x 19.5mm ဖြစ်ပါတယ်။ USB-C power supply 3A အသုံးပြုပြီး၊ US$35 ကနေ စတင်ရောင်းချပါတယ်။

> 💁 Pi400 ဟာ keyboard ထဲမှာ Pi4 ကို ထည့်ထားတဲ့ all-in-one computer ဖြစ်ပါတယ်။

![Raspberry Pi Zero](../../../../../translated_images/my/raspberry-pi-zero.f7a4133e1e7d54bb.webp)

Pi Zero ဟာ ပိုသေးငယ်ပြီး၊ power နည်းပါတယ်။ Single-core 1GHz CPU, 512MB RAM, WiFi (Zero W model), single HDMI port, micro-USB port, 40 GPIO pins, camera connector, SD card slot ပါဝင်ပြီး၊ အရွယ်အစား 65mm x 30mm x 5mm ဖြစ်ပါတယ်။ Zero ဟာ US$5 ဖြစ်ပြီး၊ WiFi ပါတဲ့ Zero W version ဟာ US$10 ဖြစ်ပါတယ်။

> 🎓 CPU တွေဟာ ARM processor ဖြစ်ပြီး၊ PC/Mac တွေမှာတွေ့ရတဲ့ Intel/AMD x86/x64 processor မဟုတ်ပါဘူး။ ARM processor တွေဟာ microcontroller တွေ၊ mobile phone အများစု၊ Microsoft Surface X, Apple Silicon Mac တွေမှာ တွေ့ရပါတယ်။

Raspberry Pi တွေဟာ Debian Linux ရဲ့ version တစ်ခုဖြစ်တဲ့ Raspberry Pi OS ကို run လုပ်ပါတယ်။ Lite version (desktop မပါ) သို့မဟုတ် full version (desktop environment, web browser, office applications, coding tools, games) ရရှိနိုင်ပါတယ်။ Debian Linux ဖြစ်တဲ့အတွက် ARM processor အတွက် build လုပ်ထားတဲ့ Debian application/tool တွေကို install လုပ်နိုင်ပါတယ်။

#### Task

Raspberry Pi ကို စူးစမ်းလေ့လာပါ။

ဒီသင်ခန်းစာတွေမှာ Raspberry Pi ကို အသုံးပြုနေတယ်ဆိုရင်၊ board ရဲ့ hardware components တွေကို ဖတ်ရှုပါ။

* [Raspberry Pi hardware documentation page](https://www.raspberrypi.org/documentation/hardware/raspberrypi/) မှာ processor အကြောင်းကို ဖတ်ရှုပါ။ သင့် Pi မှာ အသုံးပြုထားတဲ့ processor ကို ရှာဖွေပါ။
* GPIO pins တွေကို ရှာဖွေပါ။ [Raspberry Pi GPIO documentation](https://www.raspberrypi.org/documentation/hardware/raspberrypi/gpio/README.md) ကို ဖတ်ရှုပါ။ [GPIO Pin Usage guide](https://www.raspberrypi.org/documentation/usage/gpio/README.md) ကို အသုံးပြုပြီး Pi ရဲ့ pins တွေကို သတ်မှတ်ပါ။

### Single-board computers ကို programming လုပ်ခြင်း

Single-board computers တွေဟာ full OS run လုပ်တဲ့ full computers ဖြစ်ပါတယ်။ ဒါကြောင့် programming languages, frameworks, tools အများကြီးကို အသုံးပြုနိုင်ပါတယ်။ Microcontroller တွေက Arduino framework support လုပ်တဲ့ board တွေကိုသာ အားထားရပါတယ်။ Programming languages အများစုမှာ GPIO pins ကို sensor/actuator တွေက data ပို့/လက်ခံဖို့ library တွေပါဝင်ပါတယ်။

✅ သင့်ရဲ့ Linux OS မှာ support လုပ်တဲ့ programming languages တွေကို ရှာဖွေပါ။

Raspberry Pi မှာ IoT applications တည်ဆောက်ဖို့အတွက် အများဆုံးအသုံးပြုတဲ့ programming language က Python ဖြစ်ပါတယ်။ Raspberry Pi အတွက် hardware ecosystem အကြီးအကျယ်ရှိပြီး၊ Python libraries အနေနဲ့ hardware တွေကို အသုံးပြုဖို့ code တွေပါဝင်ပါတယ်။ Hardware ecosystem တွေထဲမှာ 'hats' တွေပါဝင်ပြီး၊ Pi ရဲ့ 40 GPIO pins တွေကို socket တစ်ခုနဲ့ ချိတ်ဆက်ထားပါတယ်။ Hats တွေက screen, sensor, remote-controlled cars, standardized cable sensor adapter တွေကို ပေးစွမ်းပါတယ်။
### ပရော်ဖက်ရှင်နယ် IoT တပ်ဆင်မှုများတွင် Single-board Computers အသုံးပြုခြင်း

Single-board computers များကို ပရော်ဖက်ရှင်နယ် IoT တပ်ဆင်မှုများတွင် အသုံးပြုကြသည်။ Developer kits အဖြစ်သာမက၊ hardware ကိုထိန်းချုပ်ရန်နှင့် machine learning models များကို run လုပ်ရန်လိုအပ်သော အဆင့်မြင့်လုပ်ဆောင်မှုများကို run လုပ်နိုင်စွမ်းရှိသည်။ ဥပမာအားဖြင့် [Raspberry Pi 4 compute module](https://www.raspberrypi.org/blog/raspberry-pi-compute-module-4/) သည် Raspberry Pi 4 ၏ စွမ်းဆောင်ရည်အားလုံးကို ပေးစွမ်းနိုင်ပြီး၊ ပေါ့ပါးပြီး စျေးသက်သာသော ပုံစံဖြင့် port များအများစုမပါဝင်သော compact design ဖြစ်သည်။ ၎င်းကို custom hardware တွင် တပ်ဆင်ရန်အတွက် ဒီဇိုင်းထုတ်ထားသည်။

---

## 🚀 စိန်ခေါ်မှု

နောက်ဆုံးသင်ခန်းစာတွင် စိန်ခေါ်မှုမှာ သင့်အိမ်၊ ကျောင်း၊ သို့မဟုတ် အလုပ်နေရာတွင် ရှိသော IoT devices များကို အများဆုံး စာရင်းပြုစုရန်ဖြစ်သည်။ ဒီစာရင်းထဲမှာ device တစ်ခုချင်းစီအတွက်၊ ၎င်းတို့သည် microcontrollers, single-board computers, သို့မဟုတ် နှစ်မျိုးလုံးပေါင်းစပ်ထားသောအရာများဖြစ်မည်လို့ သင်ထင်ပါသလား?

## သင်ခန်းစာပြီးနောက် Quiz

[Post-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/4)

## ပြန်လည်သုံးသပ်ခြင်းနှင့် ကိုယ်တိုင်လေ့လာခြင်း

* Arduino platform အကြောင်းပိုမိုနားလည်ရန် [Arduino getting started guide](https://www.arduino.cc/en/Guide/Introduction) ကိုဖတ်ပါ။
* Raspberry Pi များအကြောင်းပိုမိုလေ့လာရန် [introduction to the Raspberry Pi 4](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/) ကိုဖတ်ပါ။
* [Electrical Engineering Journal](https://www.eejournal.com/article/what-the-faq-are-cpus-mpus-mcus-and-gpus/) တွင် CPUs, MPUs, MCUs, နှင့် GPUs အကြောင်း ရှင်းလင်းထားသော ဆောင်းပါးကိုဖတ်ပြီး အခြေခံအယူအဆများနှင့် အတိုကောက်များအကြောင်းပိုမိုလေ့လာပါ။

✅ ဒီလမ်းညွှန်များကို အသုံးပြုပြီး၊ [hardware guide](../../../hardware.md) တွင် ဖော်ပြထားသော link များကိုလိုက်၍ စျေးနှုန်းများကိုကြည့်ပါ။ သင်အသုံးပြုလိုသော hardware platform ကိုဆုံးဖြတ်ပါ၊ သို့မဟုတ် virtual device ကို အသုံးပြုရန် ရွေးချယ်ပါ။

## လုပ်ငန်းတာဝန်

[Compare and contrast microcontrollers and single-board computers](assignment.md)

---

**အကြောင်းကြားချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှုအတွက် ကြိုးစားနေပါသော်လည်း၊ အလိုအလျောက် ဘာသာပြန်မှုများတွင် အမှားများ သို့မဟုတ် မတိကျမှုများ ပါဝင်နိုင်သည်ကို သတိပြုပါ။ မူရင်းစာရွက်စာတမ်းကို ၎င်း၏ မူလဘာသာစကားဖြင့် အာဏာတရ အရင်းအမြစ်အဖြစ် ရှုလေ့လာသင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူ့ဘာသာပြန်ပညာရှင်များမှ ပရော်ဖက်ရှင်နယ် ဘာသာပြန်မှုကို အကြံပြုပါသည်။ ဤဘာသာပြန်မှုကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော အလွဲအလွတ်များ သို့မဟုတ် အနားလွဲမှုများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။