<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cbb8c285bc64c5192fae3368fb5077d2",
  "translation_date": "2025-08-28T16:47:56+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/single-board-computer-gps-decode.md",
  "language_code": "my"
}
-->
# GPS ဒေတာကို ဖော်ထုတ်ခြင်း - Virtual IoT Hardware နှင့် Raspberry Pi

ဒီသင်ခန်းစာပိုင်းမှာတော့ Raspberry Pi သို့မဟုတ် Virtual IoT Device ကနေ GPS ဆင်ဆာမှ ဖတ်ရရှိတဲ့ NMEA မက်ဆေ့ဂျ်တွေကို ဖော်ထုတ်ပြီး latitude နဲ့ longitude ကို ထုတ်ယူပါမယ်။

## GPS ဒေတာကို ဖော်ထုတ်ခြင်း

Raw NMEA ဒေတာကို serial port ကနေ ဖတ်ပြီးတာနဲ့ open source NMEA library ကို အသုံးပြုပြီး ဖော်ထုတ်နိုင်ပါတယ်။

### တာဝန် - GPS ဒေတာကို ဖော်ထုတ်ပါ

ဒီဗိုင်းစကို GPS ဒေတာကို ဖော်ထုတ်နိုင်အောင် အစီအစဉ်ရေးပါ။

1. `gps-sensor` app project ကို ဖွင့်ထားမဟုတ်ရင် ဖွင့်ပါ။

1. `pynmea2` Pip package ကို install လုပ်ပါ။ ဒီ package မှာ NMEA မက်ဆေ့ဂျ်တွေကို ဖော်ထုတ်ဖို့အတွက် code ပါပါတယ်။

    ```sh
    pip3 install pynmea2
    ```

1. `app.py` ဖိုင်ထဲမှာ `pynmea2` module ကို import လုပ်ဖို့အတွက် အောက်ပါ code ကို imports မှာ ထည့်ပါ။

    ```python
    import pynmea2
    ```

1. `print_gps_data` function ရဲ့ အကြောင်းအရာကို အောက်ပါ code နဲ့ အစားထိုးပါ။

    ```python
    msg = pynmea2.parse(line)
    if msg.sentence_type == 'GGA':
        lat = pynmea2.dm_to_sd(msg.lat)
        lon = pynmea2.dm_to_sd(msg.lon)

        if msg.lat_dir == 'S':
            lat = lat * -1

        if msg.lon_dir == 'W':
            lon = lon * -1

        print(f'{lat},{lon} - from {msg.num_sats} satellites')
    ```

    ဒီ code က `pynmea2` library ကို အသုံးပြုပြီး UART serial port ကနေ ဖတ်ရရှိတဲ့ line ကို parse လုပ်ပါမယ်။

    မက်ဆေ့ဂျ်ရဲ့ sentence type က `GGA` ဖြစ်ရင်၊ ဒါဟာ position fix မက်ဆေ့ဂျ်ဖြစ်ပြီး process လုပ်ပါမယ်။ Latitude နဲ့ longitude တန်ဖိုးတွေကို မက်ဆေ့ဂျ်ထဲကနေ ဖတ်ပြီး NMEA `(d)ddmm.mmmm` format ကနေ decimal degrees ကို ပြောင်းပါမယ်။ ဒီ conversion ကို `dm_to_sd` function က လုပ်ဆောင်ပါမယ်။

    Latitude ရဲ့ direction ကို စစ်ဆေးပြီး latitude က south ဖြစ်ရင် တန်ဖိုးကို အနုတ်ဂဏန်းအဖြစ် ပြောင်းပါမယ်။ Longitude က west ဖြစ်ရင်လည်း အနုတ်ဂဏန်းအဖြစ် ပြောင်းပါမယ်။

    နောက်ဆုံးမှာ coordinates တွေကို console မှာ print လုပ်ပြီး၊ location ရဖို့ အသုံးပြုထားတဲ့ satellites အရေအတွက်ကိုလည်း ပြပါမယ်။

1. Code ကို run လုပ်ပါ။ Virtual IoT device ကို အသုံးပြုနေတယ်ဆိုရင် CounterFit app ကို run လုပ်ထားပြီး GPS ဒေတာကို ပေးပို့နေတဲ့အချိန်ဖြစ်ရမယ်။

    ```output
    pi@raspberrypi:~/gps-sensor $ python3 app.py 
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 ဒီ code ကို [code-gps-decode/virtual-device](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/virtual-device) folder မှာ သို့မဟုတ် [code-gps-decode/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/pi) folder မှာ ရှာနိုင်ပါတယ်။

😀 သင့်ရဲ့ GPS ဆင်ဆာအစီအစဉ်ဟာ ဒေတာဖော်ထုတ်မှုအောင်မြင်ခဲ့ပါပြီ!

---

**အကြောင်းကြားချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှန်ကန်မှုအတွက် ကြိုးစားနေသော်လည်း၊ အလိုအလျောက် ဘာသာပြန်ခြင်းတွင် အမှားများ သို့မဟုတ် မမှန်ကန်မှုများ ပါရှိနိုင်သည်ကို သတိပြုပါ။ မူရင်းဘာသာစကားဖြင့် ရေးသားထားသော စာရွက်စာတမ်းကို အာဏာရှိသော ရင်းမြစ်အဖြစ် သတ်မှတ်သင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူ့ဘာသာပြန်ပညာရှင်များမှ ပရော်ဖက်ရှင်နယ် ဘာသာပြန်ခြင်းကို အကြံပြုပါသည်။ ဤဘာသာပြန်ကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော အလွဲအလွတ်များ သို့မဟုတ် အနားလွဲမှုများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။