<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "71b5040e0b3472f1c0949c9b55f224c0",
  "translation_date": "2025-08-28T17:09:07+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/README.md",
  "language_code": "my"
}
-->
# သင့်စက်ကိုအင်တာနက်နှင့်ချိတ်ဆက်ပါ

![ဒီသင်ခန်းစာ၏အကျဉ်းချုပ်ကိုဖော်ပြသော Sketchnote](../../../../../translated_images/lesson-4.7344e074ea68fa545fd320b12dce36d72dd62d28c3b4596cb26cf315f434b98f.my.jpg)

> Sketchnote ကို [Nitya Narasimhan](https://github.com/nitya) မှရေးသားထားသည်။ ပုံကိုနှိပ်ပြီး ပိုမိုကြီးမားသောဗားရှင်းကိုကြည့်ပါ။

ဒီသင်ခန်းစာကို [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn) မှ [Hello IoT series](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) ၏အပိုင်းတစ်ခုအဖြစ်သင်ကြားခဲ့သည်။ သင်ခန်းစာကို ၂ မိနစ်စာဗီဒီယိုနှင့် ၁ နာရီစာအခန်းအချိန်အဖြစ် သင်ခန်းစာ၏အပိုင်းများကိုပိုမိုနက်နက်ရှိုင်းရှိုင်းလေ့လာပြီးမေးခွန်းများကိုဖြေဆိုရန်အတွက်သင်ကြားခဲ့သည်။

[![သင်ခန်းစာ ၄: သင့်စက်ကိုအင်တာနက်နှင့်ချိတ်ဆက်ပါ](https://img.youtube.com/vi/O4dd172mZhs/0.jpg)](https://youtu.be/O4dd172mZhs)

[![သင်ခန်းစာ ၄: သင့်စက်ကိုအင်တာနက်နှင့်ချိတ်ဆက်ပါ - အခန်းအချိန်](https://img.youtube.com/vi/j-cVCzRDE2Q/0.jpg)](https://youtu.be/j-cVCzRDE2Q)

> 🎥 အထက်ပါပုံများကိုနှိပ်ပြီးဗီဒီယိုများကိုကြည့်ပါ

## သင်ခန်းစာမတိုင်မီမေးခွန်း

[သင်ခန်းစာမတိုင်မီမေးခွန်း](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/7)

## အကျဉ်းချုပ်

IoT (အရာဝတ္ထုအင်တာနက်) တွင် **I** သည် **Internet** ကိုဆိုလိုသည် - စက်များနှင့်ချိတ်ဆက်မှုများကိုအင်တာနက်ကနေထောက်ပံ့ပေးပြီး IoT စက်များ၏အင်္ဂါရပ်များကိုဖန်တီးပေးသည်။ ဥပမာအားဖြင့် စက်တွင်ချိတ်ဆက်ထားသော sensor များမှတိုင်းတာမှုများကိုစုဆောင်းခြင်း၊ actuator များကိုထိန်းချုပ်ရန် message များပို့ခြင်းစသည်တို့ဖြစ်သည်။ IoT စက်များသည် 通常တစ်ခုတည်းသော cloud IoT service နှင့်ချိတ်ဆက်ပြီး standard communication protocol ကိုအသုံးပြုသည်။ အဆိုပါ service သည် AI service များမှစ၍ သင့်ဒေတာအပေါ် smart ဆုံးဖြတ်ချက်များကိုလုပ်ဆောင်ရန်၊ control သို့မဟုတ် reporting အတွက် web app များအထိ IoT application ၏အခြားအစိတ်အပိုင်းများနှင့်ချိတ်ဆက်ထားသည်။

> 🎓 Sensor များမှစုဆောင်းပြီး cloud သို့ပို့သောဒေတာကို telemetry ဟုခေါ်သည်။

IoT စက်များသည် cloud မှ message များကိုလက်ခံနိုင်သည်။ message များတွင် command များပါဝင်တတ်သည် - အတွင်းပိုင်းတွင် (ဥပမာ firmware ကိုပြန်လည်စတင်ခြင်း သို့မဟုတ် update လုပ်ခြင်း) သို့မဟုတ် actuator ကိုအသုံးပြုခြင်း (ဥပမာ မီးလင်းခြင်း) တစ်ခုခုလုပ်ဆောင်ရန်အညွှန်းများဖြစ်သည်။

ဒီသင်ခန်းစာတွင် IoT စက်များသည် cloud နှင့်ချိတ်ဆက်ရန်အသုံးပြုနိုင်သော communication protocol များနှင့် ပို့ပေးနိုင်သည့် ဒေတာအမျိုးအစားများကိုမိတ်ဆက်ပေးမည်ဖြစ်သည်။ သင်သည် LED control logic ကို 'server' code သို့ပြောင်းပြီး locally တွင် run လုပ်ခြင်းဖြင့် Internet control ကိုသင့် nightlight တွင်ထည့်သွင်းနိုင်မည်ဖြစ်သည်။

ဒီသင်ခန်းစာတွင် ကျွန်ုပ်တို့ဖော်ပြမည့်အကြောင်းအရာများမှာ -

* [Communication protocols](../../../../../1-getting-started/lessons/4-connect-internet)
* [Message Queueing Telemetry Transport (MQTT)](../../../../../1-getting-started/lessons/4-connect-internet)
* [Telemetry](../../../../../1-getting-started/lessons/4-connect-internet)
* [Commands](../../../../../1-getting-started/lessons/4-connect-internet)

## Communication protocols

IoT စက်များသည်အင်တာနက်နှင့်ဆက်သွယ်ရန်အသုံးပြုသော communication protocol များစွာရှိသည်။ အများဆုံးအသုံးပြုသော protocol များသည် publish/subscribe messaging ကို broker တစ်ခုခုမှတစ်ဆင့်အခြေခံထားသည်။ IoT စက်များသည် broker နှင့်ချိတ်ဆက်ပြီး telemetry ကို publish လုပ်ပြီး command များကို subscribe လုပ်သည်။ cloud service များသည် broker နှင့်ချိတ်ဆက်ပြီး telemetry message များအားလုံးကို subscribe လုပ်ပြီး command များကိုတစ်ခုတည်းသောစက်များ သို့မဟုတ် စက်အုပ်စုများသို့ publish လုပ်သည်။

![IoT စက်များသည် broker နှင့်ချိတ်ဆက်ပြီး telemetry ကို publish လုပ်ပြီး command များကို subscribe လုပ်သည်။ Cloud service များသည် broker နှင့်ချိတ်ဆက်ပြီး telemetry message များအားလုံးကို subscribe လုပ်ပြီး command များကိုတိကျသောစက်များသို့ပို့သည်။](../../../../../translated_images/pub-sub.7c7ed43fe9fd15d4.my.png)

MQTT သည် IoT စက်များအတွက်အများဆုံးအသုံးပြုသော communication protocol ဖြစ်ပြီး ဒီသင်ခန်းစာတွင်ဖော်ပြထားသည်။ အခြား protocol များတွင် AMQP နှင့် HTTP/HTTPS ပါဝင်သည်။

## Message Queueing Telemetry Transport (MQTT)

[MQTT](http://mqtt.org) သည် စက်များအကြား message များပို့ရန်အလွန်ပေါ့ပါးသော open standard messaging protocol ဖြစ်သည်။ ၎င်းကို ၁၉၉၉ ခုနှစ်တွင် ရေနံပိုက်လိုင်းများကိုစောင့်ကြည့်ရန်ဒီဇိုင်းထုတ်ခဲ့ပြီး ၁၅ နှစ်အကြာ IBM မှ open standard အဖြစ်ထုတ်ပြန်ခဲ့သည်။

MQTT တွင် broker တစ်ခုနှင့် client များစွာရှိသည်။ Client များအားလုံးသည် broker နှင့်ချိတ်ဆက်ပြီး broker သည် message များကိုသက်ဆိုင်ရာ client များသို့ပို့သည်။ Message များကို named topics အသုံးပြု၍ route လုပ်သည်၊ တစ်ခုတည်းသော client သို့တိုက်ရိုက်ပို့ခြင်းမဟုတ်ပါ။ Client တစ်ခုသည် topic တစ်ခုသို့ publish လုပ်နိုင်ပြီး အဆိုပါ topic ကို subscribe လုပ်ထားသော client များအားလုံးသည် message ကိုလက်ခံရရှိမည်ဖြစ်သည်။

![IoT စက်သည် /telemetry topic တွင် telemetry ကို publish လုပ်ပြီး cloud service သည်အဆိုပါ topic ကို subscribe လုပ်သည်](../../../../../translated_images/mqtt.cbf7f21d9adc3e17548b359444cc11bb4bf2010543e32ece9a47becf54438c23.my.png)

✅ သုတေသနလုပ်ပါ။ IoT စက်များများစွာရှိပါက သင့် MQTT broker သည် message များအားလုံးကို handle လုပ်နိုင်ရန်ဘယ်လိုလုပ်ဆောင်နိုင်မည်လဲ?

### သင့် IoT စက်ကို MQTT နှင့်ချိတ်ဆက်ပါ

Internet control ကိုသင့် nightlight တွင်ထည့်သွင်းရန်ပထမအဆင့်မှာ MQTT broker နှင့်ချိတ်ဆက်ခြင်းဖြစ်သည်။

#### Task

သင့်စက်ကို MQTT broker နှင့်ချိတ်ဆက်ပါ။

ဒီသင်ခန်းစာ၏ဒီအပိုင်းတွင် သင့် IoT nightlight ကိုအင်တာနက်နှင့်ချိတ်ဆက်ပြီး remote control လုပ်နိုင်ရန်လုပ်ဆောင်မည်။ ဒီသင်ခန်းစာ၏နောက်ပိုင်းတွင် သင့် IoT စက်သည် light level ကို public MQTT broker သို့ telemetry message တစ်ခုအဖြစ်ပို့ပြီး သင်ရေးမည့် server code မှ message ကိုလက်ခံမည်။ အဆိုပါ code သည် light level ကိုစစ်ဆေးပြီး LED ကိုဖွင့်ရန် သို့မဟုတ်ပိတ်ရန် command message တစ်ခုကိုစက်သို့ပြန်ပို့မည်။

ဒီလို setup တစ်ခု၏အမှန်တကယ်အသုံးပြုမှုကတော့ stadium ကဲ့သို့မီးများစွာရှိသောနေရာတွင် မီးများကိုဖွင့်ရန်ဆုံးဖြတ်မီ light sensor များစွာမှဒေတာကိုစုဆောင်းရန်ဖြစ်နိုင်သည်။ Sensor တစ်ခုသာတိမ်တိုက် သို့မဟုတ်ငှက်များကြောင့်အလင်းမရရှိခဲ့သော်လည်း အခြား sensor များကလုံလောက်သောအလင်းကို detect လုပ်နိုင်ပါက မီးများကိုဖွင့်ခြင်းကိုတားဆီးနိုင်သည်။

✅ Sensor များစွာမှဒေတာကိုစစ်ဆေးပြီး command များပို့ရန်လိုအပ်သောအခြေအနေများဘာတွေလဲ?

ဒီ assignment ၏အပိုင်းတစ်ခုအဖြစ် MQTT broker တစ်ခုကို setup လုပ်ရန်အခက်အခဲများကိုမဖြစ်စေဘဲ သင်သည် [Eclipse Mosquitto](https://www.mosquitto.org) ကို run လုပ်ထားသော public test server ကိုအသုံးပြုနိုင်သည်။ ဒီ test broker သည် [test.mosquitto.org](https://test.mosquitto.org) တွင် public အဖြစ်ရရှိနိုင်ပြီး account setup လုပ်ရန်မလိုအပ်ပါ၊ MQTT client များနှင့် server များကိုစမ်းသပ်ရန်အတွက်အလွန်ကောင်းမွန်သော tool ဖြစ်သည်။

> 💁 ဒီ test broker သည် public ဖြစ်ပြီး secure မဟုတ်ပါ။ သင် publish လုပ်သောအရာကိုမည်သူမဆိုနားထောင်နိုင်သောကြောင့် private data များနှင့်အသုံးမပြုသင့်ပါ။

![Light level များကိုဖတ်ပြီးစစ်ဆေးခြင်းနှင့် LED ကိုထိန်းချုပ်ခြင်းကိုဖော်ပြသော assignment ၏ flow chart](../../../../../translated_images/assignment-1-internet-flow.3256feab5f052fd273bf4e331157c574c2c3fa42e479836fc9c3586f41db35a5.my.png)

သင့်စက်ကို MQTT broker နှင့်ချိတ်ဆက်ရန်အောက်ပါအဆင့်ကိုလိုက်နာပါ -

* [Arduino - Wio Terminal](wio-terminal-mqtt.md)
* [Single-board computer - Raspberry Pi/Virtual IoT device](single-board-computer-mqtt.md)

### MQTT ကိုနက်နက်ရှိုင်းရှိုင်းလေ့လာပါ

Topic များတွင် hierarchy ရှိနိုင်ပြီး client များသည် wildcard များကိုအသုံးပြု၍ hierarchy ၏အဆင့်များကို subscribe လုပ်နိုင်သည်။ ဥပမာအားဖြင့် temperature telemetry message များကို `/telemetry/temperature` topic သို့ပို့ပြီး humidity message များကို `/telemetry/humidity` topic သို့ပို့နိုင်သည်၊ ထို့နောက် cloud app တွင် `/telemetry/*` topic ကို subscribe လုပ်ပြီး temperature နှင့် humidity telemetry message များနှစ်ခုလုံးကိုလက်ခံနိုင်သည်။

Message များကို quality of service (QoS) ဖြင့်ပို့နိုင်ပြီး message ရရှိရန်အာမခံချက်ကိုသတ်မှတ်သည်။

* အများဆုံးတစ်ကြိမ် - message ကိုတစ်ကြိမ်သာပို့ပြီး client နှင့် broker သည် delivery ကိုအတည်ပြုရန်အပိုဆောင်ရွက်မှုများမလုပ်ပါ (fire and forget)။
* အနည်းဆုံးတစ်ကြိမ် - sender မှ acknowledgement ရရှိသည်အထိ message ကိုကြိမ်များစွာပြန်လည်ကြိုးစားပို့သည် (acknowledged delivery)။
* တိကျစွာတစ်ကြိမ် - sender နှင့် receiver သည် message တစ်ခုသာရရှိရန်အာမခံရန် two-level handshake ကိုလုပ်ဆောင်သည် (assured delivery)။

✅ Assured delivery message ကို fire and forget message အစားအသုံးပြုရန်လိုအပ်သောအခြေအနေများဘာတွေလဲ?

MQTT တွင် Message Queueing ဟုအမည်ပေးထားသော်လည်း အမှန်တကယ် message queue မထောက်ပံ့ပါ။ Client တစ်ခု disconnect ဖြစ်ပြီး reconnect ဖြစ်ပါက disconnect ဖြစ်စဉ်တွင်ပို့ထားသော message များကိုလက်ခံမည်မဟုတ်ပါ၊ QoS process ကိုအသုံးပြု၍ process လုပ်ရန် client သည် message များကိုစတင်ထားသောအခြေအနေများမှလွဲ၍သာလျှင် message များကိုလက်ခံနိုင်သည်။ Message များတွင် retained flag ကို set လုပ်နိုင်သည်။ Flag ကို set လုပ်ထားပါက MQTT broker သည် topic တစ်ခုတွင် flag ဖြင့်ပို့ထားသောနောက်ဆုံး message ကိုသိမ်းဆည်းထားပြီး topic ကိုနောက်ပိုင်း subscribe လုပ်သော client များအားလုံးသို့ပို့မည်။ ဒီနည်းဖြင့် client များသည်နောက်ဆုံး message ကိုအမြဲရရှိမည်။

MQTT သည် message များအကြားကြာချိန်များကြီးမားသောအခါ connection သက်တမ်းရှိမရှိစစ်ဆေးရန် keep alive function ကိုထောက်ပံ့သည်။

> 🦟 [Eclipse Foundation မှ Mosquitto](https://mosquitto.org) သည် MQTT ကိုစမ်းသပ်ရန်သင့်ကိုယ်တိုင် run လုပ်နိုင်သော free MQTT broker တစ်ခုနှင့် သင့် code ကိုစမ်းသပ်ရန်အသုံးပြုနိုင်သော public MQTT broker တစ်ခုကို [test.mosquitto.org](https://test.mosquitto.org) တွင် host လုပ်ထားသည်။

MQTT connection များသည် public နှင့် open ဖြစ်နိုင်သည်၊ သို့မဟုတ် username နှင့် password သို့မဟုတ် certificates ကိုအသုံးပြု၍ encrypted နှင့် secured ဖြစ်နိုင်သည်။

> 💁 MQTT သည် HTTP နှင့်တူသော underlying network protocol ဖြစ်သော TCP/IP ကိုအသုံးပြု၍ဆက်သွယ်သည်၊ သို့သော် port ကွဲပြားသည်။ MQTT ကို websockets ဖြင့်အသုံးပြု၍ browser တွင် run လုပ်နေသော web app များနှင့်ဆက်သွယ်နိုင်သည်၊ သို့မဟုတ် firewall သို့မဟုတ်အခြား networking rule များက standard MQTT connection များကို block လုပ်သောအခြေအနေများတွင်အသုံးပြုနိုင်သည်။

## Telemetry

Telemetry ဆိုသောစကားလုံးသည် "ဝေးကွာသောနေရာတွင်တိုင်းတာခြင်း" ဟုဆိုလိုသောဂရိအမြစ်များမှဆင်းသက်လာသည်။ Telemetry သည် sensor များမှဒေတာကိုစုဆောင်းပြီး cloud သို့ပို့ခြင်းဖြစ်သည်။

> 💁 Telemetry device များ၏အစောဆုံးတစ်ခုကို ၁၈၇၄ ခုနှစ်တွင် ပြင်သစ်တွင်တီထွင်ခဲ့ပြီး Mont Blanc မှ Paris သို့ real-time ရာသီဥတုနှင့်နှင်းအနက်ကိုပို့ခဲ့သည်။ ၎င်းသည် wireless technologies မရရှိနိုင်သည့်အချိန်တွင် physical wires ကိုအသုံးပြုခဲ့သည်။

Lesson 1 မှ smart thermostat ၏ဥပမာကိုပြန်လည်ကြည့်ပါ။

![အခန်း sensor များစွာကိုအသုံးပြုသော Internet ချိတ်ဆက်ထားသော thermostat](../../../../../translated_images/telemetry.21e5d8b97649d2eb.my.png)

Thermostat တွင် temperature sensor များရှိပြီး telemetry ကိုစုဆောင်းသည်။ ၎င်းတွင် built-in temperature sensor တစ်ခုရှိနိုင်ပြီး wireless protocol တစ်ခုဖြစ်သော [Bluetooth Low Energy](https://wikipedia.org/wiki/Bluetooth_Low_Energy) (BLE) ကိုအသုံးပြု၍ external temperature sensor များစွာနှင့်ချိတ်ဆက်နိုင်သည်။

၎င်းသည်ပို့ပေးနိုင်သော telemetry data ၏ဥပမာမှာ -

| Name | Value | Description |
| ---- | ----- | ----------- |
| `thermostat_temperature` | 18°C | Thermostat ၏ built-in temperature sensor မှတိုင်းတာထားသောအပူချိန် |
| `livingroom_temperature` | 19°C | Remote temperature sensor တစ်ခုမှတိုင်းတာထားသောအပူချိန်၊ အခန်းကိုသတ်မှတ်ရန် `livingroom` ဟုအမည်ပေးထားသည် |
| `bedroom_temperature` | 21°C | Remote temperature sensor တစ်ခုမှတိုင်းတာထားသောအပူချိန်၊ အခန်းကိုသတ်မှတ်ရန် `bedroom` ဟုအမည်ပေးထားသည် |

Cloud service သည်ဤ telemetry data ကိုအသုံးပြု၍ heating ကိုထိန်းချုပ်ရန်ပို့ရန် command များအပေါ်ဆုံးဖြတ်ချက်များကိုလုပ်ဆောင်နိုင်သည်။

### သင့် IoT စက်မှ telemetry ပို့ပါ

Internet control ကိုသင့် nightlight တွင်ထည့်သွင်းရန်နောက်ထပ်အဆင့်မှာ telemetry topic တွင် MQTT broker သို့ light level telemetry ကိုပို့ခြင်းဖြစ်သည်။

#### Task - သင့် IoT စက်မှ telemetry ပို့ပါ

Light level telemetry ကို MQTT broker သို့ပို့ပါ။

ဒေတာကို JSON အဖြစ် encode လုပ်ပြီးပို့သည် - JavaScript Object Notation ၏အတိုကောက်ဖြစ်ပြီး key/value pair များကိုအသုံးပြု၍ text အဖြစ်ဒေတာကို encode လုပ်ရန် standard ဖြစ်သည်။

✅ JSON ကိုမကြုံဖူးပါက [JSON.org documentation](https://www.json.org/) တွင်ပိုမိုလေ့လာနိုင်သည်။

သင့်စက်မှ MQTT broker သို့ telemetry ပို့ရန်အောက်ပါအဆင့်ကိုလိုက်နာပါ -

* [Arduino - Wio Terminal](wio-terminal-telemetry.md)
* [Single-board computer - Raspberry Pi/Virtual IoT device](single-board-computer-
💁 သင့်အကြိုက်ဆုံး Python IDE သို့မဟုတ် editor ကို သုံးနိုင်ပါတယ်၊ သို့သော် ဒီသင်ခန်းစာတွေမှာ VS Code ကို အခြေခံပြီး လမ်းညွှန်ချက်တွေ ပေးမှာ ဖြစ်ပါတယ်။
1. VS Code Pylance extension ကို install လုပ်ပါ။ ဒါဟာ Python programming language ကို support ပေးတဲ့ VS Code အတွက် extension တစ်ခုဖြစ်ပါတယ်။ ဒီ extension ကို VS Code မှာ install လုပ်နည်းအတွက် [Pylance extension documentation](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) ကိုကြည့်ပါ။

#### Python virtual environment ကို configure လုပ်ပါ

Python ရဲ့ အားသာချက်တစ်ခုက [pip packages](https://pypi.org) တွေကို install လုပ်နိုင်ခြင်းဖြစ်ပါတယ်။ Pip packages တွေက အခြားသူများရေးသားပြီး အင်တာနက်ပေါ်မှာ publish လုပ်ထားတဲ့ code packages တွေဖြစ်ပါတယ်။ Command တစ်ခုနဲ့ pip package ကို computer မှာ install လုပ်ပြီး code မှာအသုံးပြုနိုင်ပါတယ်။ MQTT ကိုအသုံးပြုဖို့ pip package တစ်ခုကို install လုပ်မှာဖြစ်ပါတယ်။

ပုံမှန်အားဖြင့် package တစ်ခုကို install လုပ်တဲ့အခါမှာ computer တစ်ခုလုံးမှာအသုံးပြုနိုင်ပါတယ်။ ဒါက version conflicts ဖြစ်စေတတ်ပါတယ်။ ဥပမာ application တစ်ခုက package version တစ်ခုကိုလိုအပ်ပြီး အခြား application အတွက် version အသစ်ကို install လုပ်တဲ့အခါမှာ error ဖြစ်နိုင်ပါတယ်။ ဒီပြဿနာကိုရှောင်ရှားဖို့ [Python virtual environment](https://docs.python.org/3/library/venv.html) ကိုအသုံးပြုနိုင်ပါတယ်။ Virtual environment က Python ရဲ့ copy တစ်ခုကို folder တစ်ခုထဲမှာထားပြီး pip packages တွေကို folder ထဲမှာပဲ install လုပ်ပါတယ်။

##### Task - Python virtual environment ကို configure လုပ်ပါ

Python virtual environment ကို configure လုပ်ပြီး MQTT pip packages တွေကို install လုပ်ပါ။

1. Terminal သို့မဟုတ် command line မှာ အောက်ပါ command ကို run လုပ်ပြီး directory အသစ်တစ်ခုကိုဖန်တီးပြီး navigate လုပ်ပါ:

    ```sh
    mkdir nightlight-server
    cd nightlight-server
    ```

1. `.venv` folder ထဲမှာ virtual environment တစ်ခုကိုဖန်တီးဖို့ အောက်ပါ command ကို run လုပ်ပါ:

    ```sh
    python3 -m venv .venv
    ```

    > 💁 Python 2 ကို install လုပ်ထားပြီး Python 3 ကိုလည်း install လုပ်ထားတဲ့အခါမှာ `python3` ကို explicitly call လုပ်ဖို့လိုအပ်ပါတယ်။ Python 2 install လုပ်ထားရင် `python` ကို call လုပ်တဲ့အခါ Python 2 ကိုအသုံးပြုနိုင်ပါတယ်။

1. Virtual environment ကို activate လုပ်ပါ:

    * Windows မှာ:
        * Command Prompt သို့မဟုတ် Windows Terminal မှာ Command Prompt ကိုအသုံးပြုနေပါက အောက်ပါ command ကို run လုပ်ပါ:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * PowerShell ကိုအသုံးပြုနေပါက အောက်ပါ command ကို run လုပ်ပါ:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

    * macOS သို့မဟုတ် Linux မှာ အောက်ပါ command ကို run လုပ်ပါ:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 ဒီ commands တွေကို virtual environment ကိုဖန်တီးတဲ့နေရာမှာပဲ run လုပ်ပါ။ `.venv` folder ထဲကို navigate လုပ်ဖို့မလိုအပ်ပါဘူး။ Activate command နဲ့ package install လုပ်တဲ့ commands တွေကို virtual environment ဖန်တီးတဲ့ folder မှာပဲ run လုပ်ပါ။

1. Virtual environment ကို activate လုပ်ပြီးရင် default `python` command က virtual environment ဖန်တီးတဲ့ Python version ကို run လုပ်ပါမယ်။ Version ကိုစစ်ဖို့ အောက်ပါ command ကို run လုပ်ပါ:

    ```sh
    python --version
    ```

    Output က အောက်ပါအတိုင်းဖြစ်နိုင်ပါတယ်:

    ```output
    (.venv) ➜  nightlight-server python --version
    Python 3.9.1
    ```

    > 💁 Python version က မတူနိုင်ပါတယ်။ Version 3.6 သို့မဟုတ်အထက်ရှိရင် အဆင်ပြေပါတယ်။ မရှိရင် folder ကို delete လုပ်ပြီး Python ရဲ့ version အသစ်ကို install လုပ်ပါ။

1. [Paho-MQTT](https://pypi.org/project/paho-mqtt/) ဆိုတဲ့ popular MQTT library ကို install လုပ်ဖို့ အောက်ပါ commands ကို run လုပ်ပါ:

    ```sh
    pip install paho-mqtt
    ```

    Pip package က virtual environment ထဲမှာပဲ install လုပ်မှာဖြစ်ပြီး အပြင်မှာအသုံးပြုလို့မရပါဘူး။

#### Server code ကိုရေးပါ

Python language ကိုအသုံးပြုပြီး server code ကိုရေးပါ။

##### Task - Server code ကိုရေးပါ

Server code ကိုရေးပါ။

1. Virtual environment ထဲမှာ terminal သို့မဟုတ် command line မှာ အောက်ပါ command ကို run လုပ်ပြီး `app.py` ဆိုတဲ့ Python file ကိုဖန်တီးပါ:

    * Windows မှာ run လုပ်ပါ:

        ```cmd
        type nul > app.py
        ```

    * macOS သို့မဟုတ် Linux မှာ run လုပ်ပါ:

        ```cmd
        touch app.py
        ```

1. Current folder ကို VS Code မှာ open လုပ်ပါ:

    ```sh
    code .
    ```

1. VS Code launch လုပ်တဲ့အခါ Python virtual environment ကို activate လုပ်ပါမယ်။ Status bar ရဲ့အောက်ခြေမှာပြပါမယ်:

    ![VS Code showing the selected virtual environment](../../../../../translated_images/vscode-virtual-env.8ba42e04c3d533cf.my.png)

1. VS Code Terminal က already running ဖြစ်နေတဲ့အခါ virtual environment activate မဖြစ်နိုင်ပါဘူး။ Terminal ကို **Kill the active terminal instance** button ကိုအသုံးပြုပြီးပိတ်ပါ:

    ![VS Code Kill the active terminal instance button](../../../../../translated_images/vscode-kill-terminal.1cc4de7c6f25ee08.my.png)

1. VS Code Terminal အသစ်ကို *Terminal -> New Terminal* ကိုရွေးချယ်ပါ သို့မဟုတ် `` CTRL+` `` ကိုနှိပ်ပါ။ Terminal အသစ်က virtual environment ကို load လုပ်ပါမယ်။ Prompt မှာ virtual environment (`.venv`) ရဲ့နာမည်ကိုလည်းပြပါမယ်:

    ```output
    ➜  nightlight-server source .venv/bin/activate
    (.venv) ➜  nightlight 
    ```

1. VS Code explorer မှ `app.py` file ကို open လုပ်ပြီး အောက်ပါ code ကိုထည့်ပါ:

    ```python
    import json
    import time
    
    import paho.mqtt.client as mqtt
    
    id = '<ID>'
    
    client_telemetry_topic = id + '/telemetry'
    client_name = id + 'nightlight_server'
    
    mqtt_client = mqtt.Client(client_name)
    mqtt_client.connect('test.mosquitto.org')
    
    mqtt_client.loop_start()
    
    def handle_telemetry(client, userdata, message):
        payload = json.loads(message.payload.decode())
        print("Message received:", payload)
    
    mqtt_client.subscribe(client_telemetry_topic)
    mqtt_client.on_message = handle_telemetry
    
    while True:
        time.sleep(2)
    ```

    Line 6 မှာ `<ID>` ကို device code ဖန်တီးတဲ့အခါအသုံးပြုတဲ့ unique ID နဲ့အစားထိုးပါ။

    ⚠️ ဒီ ID ဟာ device မှာအသုံးပြုတဲ့ ID နဲ့တူရမယ်။ မတူရင် server code က subscription သို့မဟုတ် publish လုပ်တဲ့ topic မှာမရောက်ပါဘူး။

    ဒီ code က unique name ရဲ့ MQTT client ကိုဖန်တီးပြီး *test.mosquitto.org* broker ကို connect လုပ်ပါတယ်။ Background thread မှာ messages တွေကို listen လုပ်တဲ့ processing loop ကိုစတင်ပါတယ်။

    Client က telemetry topic မှာ messages တွေကို subscribe လုပ်ပြီး message ရောက်တဲ့အခါမှာ function တစ်ခုကို call လုပ်ပါတယ်။ Telemetry message ရောက်တဲ့အခါ `handle_telemetry` function ကို call လုပ်ပြီး console မှာ message ကို print လုပ်ပါတယ်။

    နောက်ဆုံးမှာ infinite loop တစ်ခုက application ကို run လုပ်နေစေပါတယ်။ MQTT client က background thread မှာ messages တွေကို listen လုပ်နေပြီး main application run လုပ်နေသ zolang as application run လုပ်နေပါတယ်။

1. VS Code terminal မှာ Python app ကို run လုပ်ဖို့ အောက်ပါ command ကို run လုပ်ပါ:

    ```sh
    python app.py
    ```

    App က IoT device မှ messages တွေကို listen လုပ်ပါမယ်။

1. Device ကို run လုပ်ပြီး telemetry messages တွေကိုပို့ပါ။ Physical device သို့မဟုတ် virtual device ရဲ့ light levels ကို adjust လုပ်ပါ။ Messages တွေကို terminal မှာ print လုပ်ပါမယ်:

    ```output
    (.venv) ➜  nightlight-server python app.py
    Message received: {'light': 0}
    Message received: {'light': 400}
    ```

    Nightlight virtual environment ထဲမှာရှိတဲ့ app.py file ကို run လုပ်ထားရမယ်။ Nightlight-server virtual environment ထဲမှာရှိတဲ့ app.py file က messages တွေကို receive လုပ်နိုင်ဖို့အတွက်ပါ။

> 💁 ဒီ code ကို [code-server/server](../../../../../1-getting-started/lessons/4-connect-internet/code-server/server) folder မှာတွေ့နိုင်ပါတယ်။

### Telemetry ကိုဘယ်နှစ်ကြိမ်ပို့သင့်လဲ?

Telemetry ကိုဘယ်နှစ်ကြိမ် measure လုပ်ပြီး data ကိုပို့သင့်လဲဆိုတာအရေးကြီးပါတယ်။ အဖြေက - အခြေအနေအပေါ်မူတည်ပါတယ်။ Measurement frequency ပိုများရင် data changes ကိုပိုမြန်မြန်တုံ့ပြန်နိုင်ပေမယ့် power, bandwidth, data volume, cloud resources စတာတွေကိုပိုအသုံးပြုရပါတယ်။ Measurement frequency ကို balance လုပ်ဖို့လိုပါတယ်။

Thermostat အတွက်တော့ အချိန်အနည်းငယ်တစ်ကြိမ် measure လုပ်တာလုံလောက်ပါတယ်။ Temperature မကြာခဏမပြောင်းလဲလို့ပါ။ တစ်နေ့တစ်ကြိမ်ပဲ measure လုပ်ရင်တော့ နေ့ဘက်မှာ temperature ပြောင်းလဲမှုကိုမသိနိုင်ပါဘူး။ တစ်စက္ကန့်တစ်ကြိမ် measure လုပ်ရင်တော့ data duplication များပြီး bandwidth နဲ့ power ကိုအလွန်အကျွံအသုံးပြုနိုင်ပါတယ်။

Factory machinery monitoring အတွက်တော့ တစ်စက္ကန့်မှာအကြိမ်များများ measure လုပ်ဖို့လိုအပ်နိုင်ပါတယ်။ Machinery fail ဖြစ်ရင် အလွန်ကြီးမားတဲ့ဆိုးကျိုးတွေဖြစ်နိုင်လို့ bandwidth ကိုအလွန်အကျွံအသုံးပြုရင်တောင် measurement accuracy ကိုအရေးထားရပါတယ်။

> 💁 ဒီအခြေအနေမှာ edge device ကိုအသုံးပြုပြီး telemetry ကို process လုပ်ဖို့စဉ်းစားနိုင်ပါတယ်။

### Connectivity ပျောက်ဆုံးမှု

Internet connection မရရှိတဲ့အခါ IoT device က data ကိုပျောက်ဆုံးသွားသင့်လား၊ connectivity ပြန်ရရှိတဲ့အခါထိ data ကိုသိမ်းထားသင့်လားဆိုတာအရေးကြီးပါတယ်။

Thermostat အတွက်တော့ data ကိုပျောက်ဆုံးသွားနိုင်ပါတယ်။ အခု temperature measurement ကသာအရေးကြီးပါတယ်။

Machinery monitoring အတွက်တော့ data ကိုသိမ်းထားသင့်ပါတယ်။ Trend analysis သို့မဟုတ် anomaly detection အတွက် data အားလုံးကိုလိုအပ်နိုင်ပါတယ်။

IoT device designers တွေက Internet outage ဖြစ်တဲ့အခါ device ကိုအသုံးပြုနိုင်ဖို့စဉ်းစားသင့်ပါတယ်။ Smart thermostat က cloud service မရရှိတဲ့အခါမှာတောင် heating control ကိုအနည်းငယ်လုပ်နိုင်ဖို့လိုပါတယ်။

[![Underground မှာ cell reception မရှိလို့ upgrade လုပ်တဲ့အခါ bricked ဖြစ်သွားတဲ့ Ferrari](../../../../../translated_images/bricked-car.dc38f8efadc6c59d76211f981a521efb300939283dee468f79503aae3ec67615.my.png)](https://twitter.com/internetofshit/status/1315736960082808832)

MQTT က loss of connectivity ကို handle လုပ်ဖို့ device နဲ့ server code က message delivery ကို ensure လုပ်ဖို့လိုပါတယ်။ Reply topic မှာ reply messages တွေကိုပို့ဖို့လိုအပ်ပါတယ်။ Message မရောက်ရင် queue ထဲမှာထားပြီးနောက်ပိုင်း replay လုပ်နိုင်ဖို့လိုပါတယ်။

## Commands

Commands ဆိုတာ cloud က device ကိုပို့တဲ့ message တွေဖြစ်ပြီး device ကိုတစ်ခုခုလုပ်ဖို့အမိန့်ပေးပါတယ်။ အများအားဖြင့် actuator ကို output ပေးဖို့အမိန့်ပေးတာဖြစ်ပါတယ်။ Device ကို reboot လုပ်ဖို့ သို့မဟုတ် telemetry data ပိုပေးဖို့အမိန့်ပေးနိုင်ပါတယ်။

![Internet connected thermostat receiving a command to turn on the heating](../../../../../translated_images/commands.d6c06bbbb3a02cce95f2831a1c331daf6dedd4e470c4aa2b0ae54f332016e504.my.png)

Thermostat က cloud service ကနေ heating ကိုဖွင့်ဖို့ command ကိုရရှိနိုင်ပါတယ်။ Sensor data အပေါ်မူတည်ပြီး cloud service က heating ကိုဖွင့်ဖို့ဆုံးဖြတ်နိုင်ပါတယ်။

### MQTT broker ကို command ပို့ပါ

Internet controlled nightlight အတွက် server code က IoT device ကို light control လုပ်ဖို့ command ပို့ပါမယ်။

1. Server code ကို VS Code မှာ open လုပ်ပါ

1. `client_telemetry_topic` ကို define လုပ်တဲ့နေရာမှာ အောက်ပါ line ကိုထည့်ပါ:

    ```python
    server_command_topic = id + '/commands'
    ```

1. `handle_telemetry` function ရဲ့အဆုံးမှာ အောက်ပါ code ကိုထည့်ပါ:

    ```python
    command = { 'led_on' : payload['light'] < 300 }
    print("Sending message:", command)
    
    client.publish(server_command_topic, json.dumps(command))
    ```

    ဒီ code က command topic ကို JSON message ပို့ပါတယ်။ Light level 300 ထက်နည်းရင် `led_on` ကို true ပို့ပြီး LED ကိုဖွင့်ဖို့အမိန့်ပေးပါတယ်။

1. Code ကိုအရင်လို run လုပ်ပါ

1. Physical device သို့မဟုတ် virtual device ရဲ့ light levels ကို adjust လုပ်ပါ။ Messages တွေကို terminal မှာ print လုပ်ပြီး commands တွေကိုပို့ပါမယ်:

    ```output
    (.venv) ➜  nightlight-server python app.py
    Message received: {'light': 0}
    Sending message: {'led_on': True}
    Message received: {'light': 400}
    Sending message: {'led_on': False}
    ```

> 💁 Telemetry နဲ့ commands ကို single topic တစ်ခုစီမှာပို့ပါတယ်။ Devices များစွာရဲ့ telemetry messages တွေကို single telemetry topic မှာပေါင်းစည်းပြီး commands messages တွေကို single commands topic မှာပေါင်းစည်းပါတယ်။ Specific device ကို command ပို့ဖို့ unique device id နဲ့ topics များစွာကိုအသုံးပြုနိုင်ပါတယ်။

> 💁 ဒီ code ကို [code-commands/server](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/server) folder မှာတွေ့နိုင်ပါတယ်။

### IoT device မှာ commands ကို handle လုပ်ပါ

Server ကနေ commands ပို့ပြီးရင် IoT device မှာ code ထည့်ပြီး LED ကို control လုပ်ပါ။

MQTT broker မှာ commands ကို listen လုပ်ဖို့အောက်ပါ steps တွေကိုလိုက်နာပါ:

* [Arduino - Wio Terminal](wio-terminal-commands.md)
* [Single-board computer - Raspberry Pi/Virtual IoT device](single-board-computer-commands.md)

Code ကိုရေးပြီး run လုပ်ပြီးရင် light levels ကိုပြောင်းလဲပါ။ Server နဲ့ device ရဲ့ output ကိုကြည့်ပြီး LED ရဲ့ပြောင်းလဲမှုကိုကြည့်ပါ။

### Connectivity ပျောက်ဆုံးမှု

Cloud service က offline ဖြစ်နေတဲ့ IoT device ကို command ပို့ဖို့လိုအပ်တဲ့အခါမှာဘာလုပ်သင့်လဲ? အဖြေက - အခြေအနေအပေါ်မူတည်ပါတယ်။

Command အသစ်က command အဟောင်းကို override လုပ်နိုင်ရင် command အဟောင်းကိုပျောက်ဆုံးသွားနိုင်ပါတယ်။ Cloud service က heating ကိုဖွင့်ဖို့ command ပို့ပြီးနောက် heating ကိုပိတ်ဖို့ command ပို့ရင် heating ကိုဖွင့်ဖို့ command ကိုပျောက်ဆုံးသွားနိုင်ပါတယ်။

Commands တွေကို sequence အတိုင်း process လုပ်ဖို့လိုအပ်ရင် connectivity ပြန်ရရှိတဲ့အခါမှာ sequence အတိုင်းပို့ဖို့လိုပါတယ်။

✅ Device သို့မဟုတ် server code က MQTT မှာ commands တွေကို sequence အတိုင်းပို့ပြီး handle လုပ်ဖို့ဘယ်လို ensure လုပ်နိုင်မလဲ?

---

## 🚀 Challenge

နောက်ဆုံးသုံးခုသော lessons တွေမှာ သင့်အိမ်၊ ကျောင်း သို့မဟုတ်အလုပ်နေရာမှာရှိတဲ့ IoT devices တွေကို list လုပ်ပြီး microcontrollers သို့မဟုတ် single-board computers အပေါ်မူတည်ပြီး sensor နဲ့ actuator တွေကိုအသုံးပြုနည်းကိုစဉ်းစားပါ။
ဒီစက်ပစ္စည်းတွေကို သုံးပြီး သူတို့ပို့နေတဲ့ သတင်းစကားတွေ၊ သို့မဟုတ် လက်ခံနေတဲ့ သတင်းစကားတွေကို စဉ်းစားကြည့်ပါ။ သူတို့က ဘယ်လို telemetry ပို့နေမလဲ။ သူတို့ ဘယ်လို သတင်းစကားတွေ သို့မဟုတ် အမိန့်တွေ လက်ခံနိုင်မလဲ။ သူတို့ လုံခြုံတယ်လို့ သင်ထင်ပါသလား။

## မျှဝေပြီးနောက် စစ်ဆေးမေးခွန်း

[မျှဝေပြီးနောက် စစ်ဆေးမေးခွန်း](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/8)

## ပြန်လည်သုံးသပ်ခြင်းနှင့် ကိုယ်တိုင်လေ့လာခြင်း

[MQTT Wikipedia စာမျက်နှာ](https://wikipedia.org/wiki/MQTT) တွင် MQTT အကြောင်း ပိုမိုဖတ်ရှုပါ။

[Mosquitto](https://www.mosquitto.org) ကို သုံးပြီး MQTT broker ကို ကိုယ်တိုင် စမ်းသပ်လုပ်ဆောင်ကြည့်ပါ၊ ထို့နောက် သင့် IoT စက်ပစ္စည်းနှင့် server code မှာ ချိတ်ဆက်ကြည့်ပါ။

> 💁 အကြံပြုချက် - Mosquitto က ပုံမှန်အားဖြင့် anonymous connections (username နဲ့ password မလိုဘဲ ချိတ်ဆက်ခြင်း) မခွင့်ပြုဘူး၊ နောက်ထပ် Mosquitto ရှိတဲ့ ကွန်ပျူတာအပြင်ဘက်ကနေ ချိတ်ဆက်တာလည်း မခွင့်ပြုဘူး။
> ဒီအရာကို [`mosquitto.conf` config file](https://www.mosquitto.org/man/mosquitto-conf-5.html) နဲ့ အောက်ပါအတိုင်း ပြင်ဆင်နိုင်ပါတယ်။
>
> ```sh
> listener 1883 0.0.0.0
> allow_anonymous true
> ```

## လုပ်ငန်းတာဝန်

[MQTT ကို အခြားဆက်သွယ်ရေး ပရိုတိုကောများနှင့် နှိုင်းယှဉ်ပါ](assignment.md)

---

**အကြောင်းကြားချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှုအတွက် ကြိုးစားနေသော်လည်း၊ အလိုအလျောက် ဘာသာပြန်မှုများတွင် အမှားများ သို့မဟုတ် မတိကျမှုများ ပါဝင်နိုင်သည်ကို သတိပြုပါ။ မူရင်းစာရွက်စာတမ်းကို ၎င်း၏ မူရင်းဘာသာစကားဖြင့် အာဏာတရားရှိသော အရင်းအမြစ်အဖြစ် ရှုလေ့လာသင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူက ဘာသာပြန်မှု ဝန်ဆောင်မှုကို အသုံးပြုရန် အကြံပြုပါသည်။ ဤဘာသာပြန်မှုကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော အလွဲအလွတ်များ သို့မဟုတ် အနားလွဲမှုများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။