<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4fb20273d299dc8d07a8f06c9cd0cdd9",
  "translation_date": "2025-08-28T17:44:13+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/README.md",
  "language_code": "my"
}
-->
C ကို *I-squared-C* ဟုဖတ်ပြီး၊ multi-controller, multi-peripheral protocol တစ်ခုဖြစ်သည်။ ချိတ်ဆက်ထားသော device မည်သည့်ဟာမဆို controller သို့မဟုတ် peripheral အဖြစ်လုပ်ဆောင်နိုင်ပြီး၊ I²C bus (data ပေးပို့မှုအတွက် communication system) မှတစ်ဆင့် ဆက်သွယ်နိုင်သည်။ Data ကို addressed packets အဖြစ်ပေးပို့ပြီး၊ packet တစ်ခုစီတွင် ပေးပို့လိုသည့် connected device ၏ address ပါဝင်သည်။

> 💁 ယခင်က ဒီမော်ဒယ်ကို master/slave ဟုခေါ်ဆိုခဲ့ပြီး၊ သို့သော် slavery နှင့်ဆက်နွယ်မှုကြောင့် ယခုအခါမှာ terminology ကိုလွှဲပြောင်းနေပါသည်။ [Open Source Hardware Association သည် controller/peripheral ဟုသတ်မှတ်ထား](https://www.oshwa.org/a-resolution-to-redefine-spi-signal-names/) သော်လည်း၊ အဟောင်း terminology ကိုတွေ့နိုင်သေးသည်။

Devices တွင် I²C bus နှင့်ချိတ်ဆက်သည့်အခါ အသုံးပြုမည့် address ရှိပြီး၊ address သည် device တွင် hard coded ဖြစ်သည်။ ဥပမာအားဖြင့် Seeed မှ Grove sensor တစ်ခုစီတွင် တူညီသော address ရှိသည်။ light sensors အားလုံးတွင် တူညီသော address ရှိပြီး၊ buttons အားလုံးတွင် light sensor address နှင့်မတူသော address ရှိသည်။ အချို့သော devices တွင် jumper settings ပြောင်းခြင်း သို့မဟုတ် pins soldering ပြုလုပ်ခြင်းဖြင့် address ကိုပြောင်းနိုင်သည်။

I²C တွင် 2 ခုသော main wires နှင့် 2 ခုသော power wires ပါဝင်သည်:

| Wire | Name | Description |
| ---- | --------- | ----------- |
| SDA | Serial Data | ဒီ wire သည် devices များအကြား data ပေးပို့ရန်အသုံးပြုသည်။ |
| SCL | Serial Clock | ဒီ wire သည် controller သတ်မှတ်ထားသော rate ဖြင့် clock signal ပေးပို့သည်။ |
| VCC | Voltage common collector | Devices များအတွက် power supply ဖြစ်သည်။ ဒါသည် SDA နှင့် SCL wires များကို pull-up resistor ဖြင့် power ပေးသည်။ controller မရှိသောအခါ signal ကို off ပြုလုပ်သည်။ |
| GND | Ground | Electrical circuit အတွက် common ground ဖြစ်သည်။ |

![I2C bus တွင် SDA နှင့် SCL wires တွင် 3 ခုသော devices ချိတ်ဆက်ထားပြီး၊ common ground wire ကိုမျှဝေထားသည်](../../../../../translated_images/i2c.83da845dde02256bdd462dbe0d5145461416b74930571b89d1ae142841eeb584.my.png)

Data ပေးပို့ရန်အတွက်၊ device တစ်ခုသည် start condition ကို issue ပြုလုပ်ပြီး၊ data ပေးပို့ရန်အဆင်သင့်ဖြစ်ကြောင်းပြသသည်။ ထိုအခါ၌ controller အဖြစ်လုပ်ဆောင်မည်။ controller သည် ဆက်သွယ်လိုသည့် device ၏ address နှင့် data ကို read သို့မဟုတ် write ပြုလုပ်လိုကြောင်းပေးပို့မည်။ Data ပေးပို့ပြီးပါက၊ controller သည် stop condition ကိုပေးပို့ပြီး၊ data ပေးပို့မှုပြီးဆုံးကြောင်းပြသသည်။ ထို့နောက်၊ အခြား device တစ်ခုသည် controller အဖြစ်လုပ်ဆောင်ပြီး data ပေးပို့ သို့မဟုတ် လက်ခံနိုင်သည်။

2<sup>C</sup> တွင် အမြန်နှုန်းကန့်သတ်ချက်များရှိပြီး၊ အမြန်နှုန်းသတ်မှတ်ထားသော အခြေအနေ 3 မျိုးရှိသည်။ အမြန်ဆုံးအခြေအနေမှာ High Speed mode ဖြစ်ပြီး အမြန်နှုန်း 3.4Mbps (megabits per second) အထိရောက်နိုင်သည်။ သို့သော် အဲဒီအမြန်နှုန်းကို ထောက်ပံ့နိုင်သော စက်များမှာ အနည်းငယ်သာရှိသည်။ ဥပမာ Raspberry Pi သည် fast mode တွင် 400Kbps (kilobits per second) အမြန်နှုန်းဖြင့် ကန့်သတ်ထားသည်။ Standard mode သည် 100Kbps အမြန်နှုန်းဖြင့် လည်ပတ်သည်။

> 💁 သင်၏ IoT hardware အဖြစ် Raspberry Pi နှင့် Grove Base hat ကို အသုံးပြုပါက၊ သင်သည် I<sup>2</sup>C sensors နှင့် ဆက်သွယ်ရန် အသုံးပြုနိုင်သော I<sup>2</sup>C sockets များကို board ပေါ်တွင် တွေ့နိုင်ပါမည်။ Analog Grove sensors များသည် ADC ကို အသုံးပြု၍ analog values များကို digital data အဖြစ်ပို့ပေးသောကြောင့်၊ သင်အသုံးပြုခဲ့သော light sensor သည် analog pin ကို simulation လုပ်ပြီး၊ Raspberry Pi သည် digital pins ကိုသာ ထောက်ပံ့နိုင်သောကြောင့် value ကို I<sup>2</sup>C မှတဆင့် ပို့ပေးခဲ့သည်။

### Universal asynchronous receiver-transmitter (UART)

UART သည် စက် 2 စက်အကြား ဆက်သွယ်မှုကို ခွင့်ပြုသော physical circuitry ဖြစ်သည်။ စက်တစ်ခုစီတွင် ဆက်သွယ်မှု pins 2 ခုရှိပြီး - transmit (Tx) နှင့် receive (Rx) ဖြစ်သည်။ ပထမစက်၏ Tx pin ကို ဒုတိယစက်၏ Rx pin နှင့် ချိတ်ဆက်ပြီး၊ ဒုတိယစက်၏ Tx pin ကို ပထမစက်၏ Rx pin နှင့် ချိတ်ဆက်ထားသည်။ ဤအခြေအနေသည် ဒေတာကို နှစ်ဖက် Direction မှ ပို့ပေးနိုင်စေသည်။

* စက် 1 သည် ၎င်း၏ Tx pin မှ ဒေတာကို ပို့ပြီး၊ ဒုတိယစက်၏ Rx pin မှ လက်ခံသည်။
* စက် 1 သည် ၎င်း၏ Rx pin မှ ဒုတိယစက်၏ Tx pin မှ ပို့သော ဒေတာကို လက်ခံသည်။

![UART with the Tx pin on one chip connected to the Rx pin on another, and vice versa](../../../../../translated_images/uart.d0dbd3fb9e3728c6.my.png)

> 🎓 ဒေတာကို တစ်ဘစ်စီ ပို့ပေးပြီး၊ ၎င်းကို *serial* communication ဟုခေါ်သည်။ အများစုသော operating systems နှင့် microcontrollers တွင် *serial ports* ရှိပြီး၊ ၎င်းသည် serial data ကို ပို့ပေးနိုင်သော connection များကို သင်၏ code မှ အသုံးပြုနိုင်သည်။

UART devices တွင် [baud rate](https://wikipedia.org/wiki/Symbol_rate) (Symbol rate ဟုလည်းခေါ်သည်) ရှိပြီး၊ ဒေတာကို တစ်စက္ကန့်လျှင် ဘစ်များဖြင့် ပို့ပေးရန်နှင့် လက်ခံရန် အမြန်နှုန်းကို သတ်မှတ်သည်။ အများဆုံး baud rate သည် 9,600 ဖြစ်ပြီး၊ ဒါဟာ တစ်စက္ကန့်လျှင် 9,600 ဘစ် (0s နှင့် 1s) ကို ပို့ပေးသည်။

UART သည် start နှင့် stop bits ကို အသုံးပြုသည် - ၎င်းသည် byte (8 bits) ဒေတာကို ပို့ရန်မပြုမီ start bit ကို ပို့ပြီး၊ 8 bits ပို့ပြီးလျှင် stop bit ကို ပို့သည်။

UART အမြန်နှုန်းသည် hardware ပေါ်မူတည်ပြီး၊ အမြန်ဆုံး implementation များသည် 6.5 Mbps (megabits per second, သို့မဟုတ် တစ်စက္ကန့်လျှင် ဘစ်များ သန်းချီပို့ပေးနိုင်သည်) ကို မကျော်လွန်ပါ။

သင်သည် UART ကို GPIO pins မှတဆင့် အသုံးပြုနိုင်သည် - pin တစ်ခုကို Tx အဖြစ် သတ်မှတ်ပြီး၊ pin တစ်ခုကို Rx အဖြစ် သတ်မှတ်ကာ၊ ၎င်းတို့ကို အခြားစက်နှင့် ချိတ်ဆက်နိုင်သည်။

> 💁 သင်၏ IoT hardware အဖြစ် Raspberry Pi နှင့် Grove Base hat ကို အသုံးပြုပါက၊ သင်သည် UART protocol ကို အသုံးပြုသော sensors များနှင့် ဆက်သွယ်ရန် UART socket ကို board ပေါ်တွင် တွေ့နိုင်ပါမည်။

### Serial Peripheral Interface (SPI)

SPI သည် microcontroller တစ်ခုမှ storage device (ဥပမာ flash memory) တို့နှင့် ဆက်သွယ်ရန် အနီးကပ်အကွာအဝေးအတွင်း ဆက်သွယ်ရန်အတွက် ဒီဇိုင်းထုတ်ထားသည်။ ၎င်းသည် controller/peripheral model အပေါ် အခြေခံထားပြီး၊ controller တစ်ခု (အများအားဖြင့် IoT device ၏ processor) သည် peripherals များစွာနှင့် ဆက်သွယ်သည်။ controller သည် peripheral တစ်ခုကို ရွေးချယ်ပြီး၊ ဒေတာကို ပို့ပေးခြင်း သို့မဟုတ် တောင်းဆိုခြင်းဖြင့် အားလုံးကို ထိန်းချုပ်သည်။

> 💁 I<sup>2</sup>C နှင့် တူသည့် controller နှင့် peripheral ဆိုသည့် term များသည် မကြာသေးမီက ပြောင်းလဲထားသောကြောင့်၊ အဟောင်း term များကို သင်တွေ့နိုင်ပါသည်။

SPI controllers တွင် 3 wires ရှိပြီး၊ peripheral တစ်ခုစီအတွက် 1 extra wire ရှိသည်။ Peripherals တွင် wires 4 ခုရှိသည်။ ဤ wires များမှာ -

| Wire | Name | Description |
| ---- | --------- | ----------- |
| COPI | Controller Output, Peripheral Input | controller မှ peripheral သို့ ဒေတာပို့ရန် wire |
| CIPO | Controller Input, peripheral Output | peripheral မှ controller သို့ ဒေတာပို့ရန် wire |
| SCLK | Serial Clock | controller မှ clock signal ပို့ရန် wire |
| CS   | Chip Select | controller တွင် peripherals တစ်ခုစီအတွက် wire များရှိပြီး၊ wire တစ်ခုစီသည် သက်ဆိုင် peripheral ၏ CS wire နှင့် ချိတ်ဆက်ထားသည်။ |

![SPI with on controller and two peripherals](../../../../../translated_images/spi.297431d6f98b386b.my.png)

CS wire သည် peripheral တစ်ခုစီကို တစ်ချိန်တည်းတွင် active ဖြစ်စေပြီး၊ COPI နှင့် CIPO wires မှတဆင့် ဆက်သွယ်သည်။ controller သည် peripheral ကို ပြောင်းလဲရန်လိုအပ်သောအခါ၊ လက်ရှိ active ဖြစ်နေသော peripheral ၏ CS wire ကို deactivate လုပ်ပြီး၊ နောက်တစ်ခုဆက်သွယ်လိုသော peripheral ၏ wire ကို activate လုပ်သည်။

SPI သည် *full-duplex* ဖြစ်ပြီး၊ controller သည် COPI နှင့် CIPO wires ကို အသုံးပြု၍ တစ်ချိန်တည်းတွင် တစ်ခုတည်းသော peripheral မှ ဒေတာကို ပို့ပေးနိုင်သည်နှင့် လက်ခံနိုင်သည်။ SPI သည် SCLK wire ပေါ်ရှိ clock signal ကို အသုံးပြု၍ devices များကို sync လုပ်ထားသောကြောင့်၊ UART မှတဆင့် တိုက်ရိုက်ပို့ခြင်းလိုအပ်သည့် start နှင့် stop bits မလိုအပ်ပါ။

SPI သည် အမြန်နှုန်းကန့်သတ်ချက်များမရှိဘဲ၊ implementation များသည် တစ်စက္ကန့်လျှင် megabytes များစွာကို ပို့ပေးနိုင်သည်။

IoT developer kits များသည် SPI ကို GPIO pins အချို့မှတဆင့် ထောက်ပံ့သည်။ ဥပမာ Raspberry Pi တွင် GPIO pins 19, 21, 23, 24 နှင့် 26 ကို SPI အတွက် အသုံးပြုနိုင်သည်။

### Wireless

အချို့သော sensors များသည် Bluetooth (အဓိကအားဖြင့် Bluetooth Low Energy, BLE), LoRaWAN (**Lo**ng **Ra**nge low power networking protocol), သို့မဟုတ် WiFi ကဲ့သို့သော wireless protocols များကို အသုံးပြု၍ ဆက်သွယ်နိုင်သည်။ ၎င်းတို့သည် IoT device နှင့် physical connection မရှိသော remote sensors များအတွက် ခွင့်ပြုသည်။

ဥပမာတစ်ခုမှာ စိုထိုင်းဆ sensors များဖြစ်သည်။ ၎င်းတို့သည် field အတွင်းရှိ စိုထိုင်းဆကို တိုင်းတာပြီး၊ LoRaWAN မှတဆင့် hub device သို့ ဒေတာကို ပို့ပေးသည်။ hub device သည် ဒေတာကို process လုပ်ခြင်း သို့မဟုတ် အင်တာနက်မှတဆင့် ပို့ပေးသည်။ ၎င်းသည် sensor ကို IoT device မှဝေးကွာစေပြီး၊ power consumption ကို လျှော့ချရန်နှင့် WiFi networks များ သို့မဟုတ် cables ရှည်များမလိုအပ်စေရန် အထောက်အကူပြုသည်။

BLE သည် fitness trackers ကဲ့သို့သော advanced sensors များအတွက် လူကြိုက်များသည်။ ၎င်းတို့သည် sensors များစွာကို ပေါင်းစပ်ပြီး၊ sensor data ကို BLE မှတဆင့် သင်၏ဖုန်းကဲ့သို့သော IoT device သို့ ပို့ပေးသည်။

✅ သင်၏ကိုယ်ပေါ်တွင်၊ အိမ်တွင် သို့မဟုတ် ကျောင်းတွင် bluetooth sensors များရှိပါသလား။ ၎င်းတို့တွင် အပူချိန် sensors, လူရှိမှု sensors, device trackers နှင့် fitness devices များ ပါဝင်နိုင်သည်။

စီးပွားရေးစက်များအတွက် ချိတ်ဆက်ရန် လူကြိုက်များသောနည်းလမ်းတစ်ခုမှာ Zigbee ဖြစ်သည်။ Zigbee သည် WiFi ကို အသုံးပြု၍ devices များအကြား mesh networks ဖွဲ့စည်းသည်။ device တစ်ခုစီသည် အနီးအနားရှိ devices များစွာနှင့် ချိတ်ဆက်ပြီး၊ ပိုမိုချိတ်ဆက်မှုများကို ဖွဲ့စည်းသည်။ device တစ်ခုသည် အင်တာနက်သို့ message ပို့လိုသောအခါ၊ အနီးဆုံး devices များသို့ ပို့ပြီး၊ ၎င်းတို့သည် အနီးအနားရှိ devices များသို့ ဆက်လက်ပို့ပေးသည်။ အဲဒီလို ဆက်လက်ပို့ပေးပြီး coordinator သို့ရောက်လျှင် အင်တာနက်သို့ ပို့နိုင်သည်။

> 🐝 Zigbee ဟုခေါ်သောအမည်သည် ပျားပျားများ၏ beehive သို့ပြန်လာပြီး waggle dance လုပ်သောအမည်မှ ဆင်းသက်လာသည်။

## မြေစိုထိုင်းဆအဆင့်များကို တိုင်းတာပါ

သင်သည် မြေစိုထိုင်းဆ sensor, IoT device, နှင့် အိမ်အပင် သို့မဟုတ် အနီးအနားရှိ မြေပြင်တစ်စက်ကို အသုံးပြု၍ မြေစိုထိုင်းဆအဆင့်ကို တိုင်းတာနိုင်သည်။

### Task - မြေစိုထိုင်းဆကို တိုင်းတာပါ

သင်၏ IoT device ကို အသုံးပြု၍ မြေစိုထိုင်းဆကို တိုင်းတာရန် သက်ဆိုင်သော လမ်းညွှန်ကို လိုက်နာပါ -

* [Arduino - Wio Terminal](wio-terminal-soil-moisture.md)
* [Single-board computer - Raspberry Pi](pi-soil-moisture.md)
* [Single-board computer - Virtual device](virtual-device-soil-moisture.md)

## Sensor calibration

Sensors များသည် resistance သို့မဟုတ် capacitance ကဲ့သို့သော electrical properties များကို တိုင်းတာခြင်းအပေါ် မူတည်သည်။

> 🎓 Resistance သည် ohms (Ω) ဖြင့် တိုင်းတာပြီး၊ လျှပ်စီးအားတစ်ခုသည် တစ်ခုခုမှ ဖြတ်သန်းသည့်အခါ၊ ၎င်းကို ဆန့်ကျင်မှုဘယ်လောက်ရှိသည်ကို ဖော်ပြသည်။ voltage ကို material တစ်ခုတွင် အသုံးပြုသောအခါ၊ current အရေအတွက်သည် material ၏ resistance အပေါ် မူတည်သည်။ [electrical resistance page on Wikipedia](https://wikipedia.org/wiki/Electrical_resistance_and_conductance) တွင် ပိုမိုဖတ်ရှုနိုင်သည်။

> 🎓 Capacitance သည် farads (F) ဖြင့် တိုင်းတာပြီး၊ component သို့မဟုတ် circuit တစ်ခုသည် လျှပ်စွမ်းအားကို စုဆောင်းထားနိုင်စွမ်းကို ဖော်ပြသည်။ [capacitance page on Wikipedia](https://wikipedia.org/wiki/Capacitance) တွင် capacitance အကြောင်း ပိုမိုဖတ်ရှုနိုင်သည်။

ဤတိုင်းတာမှုများသည် အမြဲတမ်း အသုံးဝင်မည်မဟုတ်ပါ - ဥပမာ temperature sensor တစ်ခုသည် 22.5KΩ အတိုင်းတာမှုကို ပေးခဲ့သည်ဟု စဉ်းစားပါ။ အဲဒီအတိုင်းတာမှုကို အသုံးဝင်သော unit သို့ ပြောင်းလဲရန် calibration လုပ်ရန်လိုအပ်သည် - ၎င်းသည် တိုင်းတာမှုများကို quantity တိုင်းတာမှုနှင့် ကိုက်ညီစေရန် ပြောင်းလဲခြင်းဖြစ်သည်။

အချို့သော sensors များသည် pre-calibrated ဖြစ်ပြီး၊ ဥပမာ သင်ပြီးခဲ့သော သင်ခန်းစာတွင် အသုံးပြုခဲ့သော temperature sensor သည် °C အတိုင်းတာ unit ဖြင့် temperature measurement ကို ပြန်ပေးနိုင်ရန် အဆင်သင့်ဖြစ်နေသည်။ စက်ရုံတွင် sensor ပထမဆုံးတစ်ခုကို ထုတ်လုပ်သောအခါ၊ အတိအကျ temperature များကို exposure လုပ်ပြီး၊ resistance ကို တိုင်းတာသည်။ ၎င်းကို resistance (Ω) unit မှ °C unit သို့ ပြောင်းလဲနိုင်သော calculation တစ်ခုကို ဖန်တီးရန် အသုံးပြုသည်။

> 💁 Resistance ကို temperature မှတွက်ရန် formula ကို [Steinhart–Hart equation](https://wikipedia.org/wiki/Steinhart–Hart_equation) ဟုခေါ်သည်။

### မြေစိုထိုင်းဆ sensor calibration

မြေစိုထိုင်းဆကို gravimetric သို့မဟုတ် volumetric water content ဖြင့် တိုင်းတာသည်။

* Gravimetric သည် မြေ၏ dry weight တစ် unit အတွင်းရှိ ရေ၏ weight ကို တိုင်းတာသည်။ ၎င်းကို dry soil တစ်ကီလိုဂရမ်လျှင် ရေတစ်ကီလိုဂရမ်အဖြစ် တိုင်းတာသည်။
* Volumetric သည် မြေ၏ dry volume တစ် unit အတွင်းရှိ ရေ၏ volume ကို တိုင်းတာသည်။ ၎င်းကို dry soil တစ် cubic metre လျှင် ရေတစ် cubic metre အဖြစ် တိုင်းတာသည်။

> 🇺🇸 အမေရိကန်များအတွက်၊ unit များ၏ consistency ကြောင့်၊ ၎င်းတို့ကို ကီလိုဂရမ်များအစား ပေါင်များဖြင့် သို့မဟုတ် cubic metres အစား cubic feet ဖြင့် တိုင်းတာနိုင်သည်။

မြေစိုထိုင်းဆ sensors များသည် electrical resistance သို့မဟုတ် capacitance ကို တိုင်းတာသည် - ၎င်းသည် မြေစိုထိုင်းဆအပေါ်သာမက မြေ၏အမျိုးအစားအပေါ်လည်း မူတည်သည်။ မြေတွင်ပါဝင်သော components များသည် electrical characteristics ကို ပြောင်းလဲနိုင်သည်။ ideal အနေဖြင့် sensors များကို calibration လုပ်သင့်သည် - ၎င်းသည် sensor မှ readings များကို သိပ္ပံနည်းကျနည်းလမ်းများဖြင့် ရရှိသော တိုင်းတာမှုများနှင့် နှိုင်းယှဉ်ခြင်းဖြစ်သည်။ ဥပမာ lab တစ်ခုသည် field တစ်ခု၏ gravimetric မြေစိုထိုင်းဆကို တစ်နှစ်လျှင် အချိန်အနည်းငယ်တွင် တိုင်းတာပြီး၊ ၎င်းတို့ကို sensor calibration အတွက် အသုံးပြုနိုင်သည်။

![A graph of voltage vs soil moisture content](../../../../../translated_images/soil-moisture-to-voltage.df86d80cda158700.my.png)

အထက်ပါ graph သည် sensor ကို calibration လုပ်ရန် ပြသထားသည်။ voltage ကို capture လုပ်ပြီး၊ lab မှတဆင့် moist weight နှင့် dry weight ကို နှိုင်းယှဉ်ခြင်းဖြင့် တိုင်းတာသည် (wet weight ကို တိုင်းတာပြီး၊ အိုးဗန်တွင်ခြောက်သွေ့ပြီး dry weight ကို တိုင်းတာသည်။) အချို့သော readings များကို capture လုပ်ပြီး၊ graph ပေါ်တွင် plot လုပ်ကာ၊ points များကို line တစ်ခုဖြင့် fit လုပ်သည်။ ဤ line ကို IoT device မှ sensor readings များကို အမှန်တကယ် မြေစိုထိုင်းဆ measurement သို့ ပြောင်းလဲရန် အသုံးပြုနိုင်သည်။

💁 Resistive မြေစိုထိုင်းဆ sensors များအတွက်၊ voltage သည် မြေစိုထိုင်းဆများလာသည်နှင့်အမျှ မြင့်တက်သည်။ Capacitive မြေစိုထိုင်းဆ sensors များအတွက်၊ voltage သည် မြေစိုထိုင်းဆများလာသည်နှင့်အမျှ ကျဆင်းသည်။ ထို့ကြောင့် graphs

---

**အကြောင်းကြားချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှန်ကန်မှုအတွက် ကြိုးစားနေသော်လည်း၊ အလိုအလျောက် ဘာသာပြန်မှုများတွင် အမှားများ သို့မဟုတ် မမှန်ကန်မှုများ ပါရှိနိုင်သည်ကို သတိပြုပါ။ မူရင်းဘာသာစကားဖြင့် ရေးသားထားသော စာရွက်စာတမ်းကို အာဏာတရ အရင်းအမြစ်အဖြစ် သတ်မှတ်သင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူ့ဘာသာပြန်ပညာရှင်များမှ ပရော်ဖက်ရှင်နယ် ဘာသာပြန်မှုကို အကြံပြုပါသည်။ ဤဘာသာပြန်မှုကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော အလွဲအလွတ်များ သို့မဟုတ် အနားလွဲမှုများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။