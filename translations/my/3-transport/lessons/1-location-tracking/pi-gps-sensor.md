<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3b2448c7ab4e9673e77e35a50c5e350d",
  "translation_date": "2025-08-28T16:45:45+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/pi-gps-sensor.md",
  "language_code": "my"
}
-->
# Raspberry Pi မှ GPS ဒေတာဖတ်ရန်

ဒီသင်ခန်းစာအပိုင်းမှာ၊ သင့်ရဲ့ Raspberry Pi မှာ GPS ဆင်ဆာတစ်ခုထည့်သွင်းပြီး၊ ဒေတာများကိုဖတ်ရှုမည်ဖြစ်သည်။

## ဟာ့ဒ်ဝဲ

Raspberry Pi အတွက် GPS ဆင်ဆာတစ်ခုလိုအပ်ပါသည်။

သင်အသုံးပြုမည့်ဆင်ဆာမှာ [Grove GPS Air530 sensor](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html) ဖြစ်သည်။ ဒီဆင်ဆာသည် မြန်နှုန်းမြင့်ပြီး တိကျသော GPS စနစ်များစွာနှင့် ချိတ်ဆက်နိုင်သည်။ ဆင်ဆာသည် အစိတ်အပိုင်း ၂ ခုဖြင့်ဖွဲ့စည်းထားပြီး၊ ဆင်ဆာ၏ အဓိကအီလက်ထရွန်းနစ်နှင့် အပြင်ဘက်အင်တင်နာ (သေးငယ်သောကြိုးဖြင့် ချိတ်ဆက်ထားသည်) တို့ဖြင့် ဂြိုဟ်တုမှ ရေဒီယိုလှိုင်းများကို ဖမ်းယူသည်။

ဒီဆင်ဆာသည် UART ဆင်ဆာဖြစ်ပြီး၊ GPS ဒေတာကို UART မှတဆင့်ပေးပို့သည်။

## GPS ဆင်ဆာကို ချိတ်ဆက်ပါ

Grove GPS ဆင်ဆာကို Raspberry Pi နှင့် ချိတ်ဆက်နိုင်ပါသည်။

### လုပ်ဆောင်ရန် - GPS ဆင်ဆာကို ချိတ်ဆက်ပါ

GPS ဆင်ဆာကို ချိတ်ဆက်ပါ။

![A grove GPS sensor](../../../../../translated_images/my/grove-gps-sensor.247943bf69b03f0d1820ef6ed10c587f9b650e8db55b936851c92412180bd3e2.png)

1. Grove ကေဘယ်လ်တစ်ဖက်ကို GPS ဆင်ဆာပေါ်ရှိ ဆော့ကက်ထဲသို့ ထည့်ပါ။ ၎င်းသည် တစ်ဖက်သာ အလွယ်တကူသွားပါမည်။

1. Raspberry Pi ကို မီးပိတ်ထားသောအခြေအနေတွင် Grove ကေဘယ်လ်၏ အခြားဖက်ကို Pi တွင်တပ်ဆင်ထားသော Grove Base Hat ပေါ်ရှိ **UART** ဟုအမှတ်အသားပြုထားသော UART ဆော့ကက်ထဲသို့ ချိတ်ဆက်ပါ။ ဒီဆော့ကက်သည် အလယ်တန်းတန်းတွင်ရှိပြီး SD Card slot အနီး၊ USB port နှင့် ethernet socket ၏ အခြားဖက်တွင်ရှိသည်။

    ![The grove GPS sensor connected to the UART socket](../../../../../translated_images/my/pi-gps-sensor.1f99ee2b2f6528915047ec78967bd362e0e4ee0ed594368a3837b9cf9cdaca64.png)

1. GPS ဆင်ဆာကို အင်တင်နာတပ်ဆင်ထားသောနေရာမှ မိုးကောင်းကင်ကို မြင်နိုင်သောနေရာတွင်ထားပါ - အကောင်းဆုံးအနေဖြင့် ပြတင်းပေါက်အနီး သို့မဟုတ် အပြင်ဘက်တွင်ထားပါ။ အင်တင်နာကို အတားအဆီးမရှိဘဲထားခြင်းဖြင့် သင့်ရဲ့အချက်အလက်ကို ပိုမိုရှင်းလင်းစွာရယူနိုင်သည်။

## GPS ဆင်ဆာကို အစီအစဉ်ရေးပါ

ယခု Raspberry Pi သည် ချိတ်ဆက်ထားသော GPS ဆင်ဆာကို အသုံးပြုရန် အစီအစဉ်ရေးနိုင်ပါသည်။

### လုပ်ဆောင်ရန် - GPS ဆင်ဆာကို အစီအစဉ်ရေးပါ

ဒီစက်ကို အစီအစဉ်ရေးပါ။

1. Pi ကို မီးဖွင့်ပြီး boot ပြုလုပ်ရန် စောင့်ပါ။

1. GPS ဆင်ဆာတွင် LED ၂ ခုရှိသည် - အပြာရောင် LED သည် ဒေတာပေးပို့သောအခါတွင် လင်းပွင့်ပြီး၊ အစိမ်းရောင် LED သည် ဂြိုဟ်တုမှ ဒေတာရရှိသောအခါ တစ်စက္ကန့်တစ်ကြိမ် လင်းပွင့်သည်။ Pi ကို မီးဖွင့်သောအခါ အပြာရောင် LED လင်းပွင့်နေကြောင်း သေချာပါစေ။ မိနစ်အနည်းငယ်အကြာတွင် အစိမ်းရောင် LED လင်းပွင့်ပါမည် - မဟုတ်ပါက အင်တင်နာ၏နေရာကို ပြောင်းလဲရန် လိုအပ်နိုင်သည်။

1. VS Code ကို Pi ပေါ်တွင် တိုက်ရိုက်ဖွင့်ပါ၊ သို့မဟုတ် Remote SSH extension ဖြင့် ချိတ်ဆက်ပါ။

    > ⚠️ [VS Code ကို စတင်တပ်ဆင်ခြင်းနှင့် ဖွင့်ခြင်းအတွက် သင်ခန်းစာ ၁ တွင် ရှင်းပြထားသော လမ်းညွှန်ချက်များကို ပြန်လည်ကြည့်ရှုနိုင်ပါသည်](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md)။

1. Bluetooth ကို ပံ့ပိုးသော Raspberry Pi ၏ နောက်ဆုံးဗားရှင်းများတွင် Bluetooth သုံးသော serial port နှင့် Grove UART port သုံးသော serial port အကြား ပဋိပက္ခရှိသည်။ ၎င်းကို ဖြေရှင်းရန် အောက်ပါအတိုင်းလုပ်ဆောင်ပါ:

    1. VS Code terminal မှ `/boot/config.txt` ဖိုင်ကို `nano` ဖြင့် ပြင်ဆင်ပါ။ `nano` သည် terminal text editor တစ်ခုဖြစ်ပြီး အောက်ပါ command ကို အသုံးပြုပါ:

        ```sh
        sudo nano /boot/config.txt
        ```

        > ဒီဖိုင်ကို VS Code မှတဆင့် မပြင်နိုင်ပါ၊ အကြီးတန်းအခွင့်အာဏာ (`sudo` permissions) ဖြင့်သာ ပြင်နိုင်ပါသည်။ VS Code သည် ဒီအခွင့်အာဏာဖြင့် မလုပ်ဆောင်ပါ။

    1. Cursor key များကို အသုံးပြု၍ ဖိုင်၏ အဆုံးသို့သွားပါ။ အောက်ပါ code ကို ကူးယူပြီး ဖိုင်၏ အဆုံးတွင် ထည့်ပါ:

        ```ini
        dtoverlay=pi3-miniuart-bt
        dtoverlay=pi3-disable-bt
        enable_uart=1
        ```

        သင့်စက်အတွက် သင့်လျော်သော keyboard shortcut များဖြင့် paste လုပ်နိုင်ပါသည် (`Ctrl+v` Windows, Linux, Raspberry Pi OS တွင်၊ `Cmd+v` macOS တွင်)။

    1. ဒီဖိုင်ကို သိမ်းပြီး nano မှ ထွက်ရန် `Ctrl+x` ကိုနှိပ်ပါ။ ပြင်ဆင်ထားသော buffer ကို သိမ်းမည်လားဟု မေးလျှင် `y` ကိုနှိပ်ပြီး၊ `/boot/config.txt` ကို overwrite လုပ်ရန် အတည်ပြုရန် `enter` ကိုနှိပ်ပါ။

        > မှားယွင်းမှုရှိပါက သိမ်းမလုပ်ဘဲ ထွက်နိုင်ပြီး၊ အဆင့်များကို ထပ်မံလုပ်ဆောင်နိုင်ပါသည်။

    1. `/boot/cmdline.txt` ဖိုင်ကို nano ဖြင့် ပြင်ဆင်ပါ၊ အောက်ပါ command ကို အသုံးပြုပါ:

        ```sh
        sudo nano /boot/cmdline.txt
        ```

    1. ဒီဖိုင်တွင် key/value pair များစွာရှိပြီး၊ space ဖြင့် ခွဲထားသည်။ `console` ဟု အမည်ပေးထားသော key အတွက် key/value pair များကို ဖယ်ရှားပါ။ ၎င်းသည် အောက်ပါအတိုင်းဖြစ်နိုင်ပါသည်:

        ```output
        console=serial0,115200 console=tty1 
        ```

        Cursor key များကို အသုံးပြု၍ entry များသို့သွားပြီး၊ `del` သို့မဟုတ် `backspace` key များဖြင့် ဖျက်ပါ။

        ဥပမာအားဖြင့်၊ သင့်ရဲ့မူရင်းဖိုင်သည် အောက်ပါအတိုင်းဖြစ်ပါက:

        ```output
        console=serial0,115200 console=tty1 root=PARTUUID=058e2867-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait
        ```

        အသစ်ပြင်ဆင်ထားသောဗားရှင်းမှာ:

        ```output
        root=PARTUUID=058e2867-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait
        ```

    1. အထက်ပါအဆင့်များကို လိုက်နာပြီး ဖိုင်ကို သိမ်းပြီး nano မှ ထွက်ပါ။

    1. သင့် Pi ကို ပြန်လည်စတင်ပါ၊ Pi ပြန်လည်စတင်ပြီးနောက် VS Code တွင် ပြန်လည်ချိတ်ဆက်ပါ။

1. Terminal မှ `pi` အသုံးပြုသူ၏ home directory တွင် `gps-sensor` ဟု folder အသစ်တစ်ခုဖန်တီးပါ။ ဒီ folder တွင် `app.py` ဟု ဖိုင်တစ်ခုဖန်တီးပါ။

1. ဒီ folder ကို VS Code တွင် ဖွင့်ပါ။

1. GPS module သည် UART ဒေတာကို serial port မှတဆင့် ပေးပို့သည်။ Python code မှ serial port နှင့် ဆက်သွယ်ရန် `pyserial` Pip package ကို install လုပ်ပါ:

    ```sh
    pip3 install pyserial
    ```

1. `app.py` ဖိုင်တွင် အောက်ပါ code ကို ထည့်ပါ:

    ```python
    import time
    import serial
    
    serial = serial.Serial('/dev/ttyAMA0', 9600, timeout=1)
    serial.reset_input_buffer()
    serial.flush()
    
    def print_gps_data(line):
        print(line.rstrip())
    
    while True:
        line = serial.readline().decode('utf-8')
    
        while len(line) > 0:
            print_gps_data(line)
            line = serial.readline().decode('utf-8')
    
        time.sleep(1)
    ```

    ဒီ code သည် `pyserial` Pip package မှ `serial` module ကို import လုပ်သည်။ ထို့နောက် Grove Pi Base Hat ၏ UART port အတွက် serial port ၏ လိပ်စာဖြစ်သော `/dev/ttyAMA0` သို့ ချိတ်ဆက်သည်။ ထို့နောက် serial connection တွင် ရှိသော ဒေတာများကို ရှင်းလင်းသည်။

    ထို့နောက် `print_gps_data` ဟုခေါ်သော function တစ်ခုကို သတ်မှတ်ပြီး၊ ၎င်းသို့ ပေးပို့သော line ကို console တွင် print လုပ်သည်။

    ထို့နောက် code သည် အဆုံးမရှိ loop တစ်ခုဖြင့် serial port မှ text line များကို ဖတ်ပြီး၊ တစ်ခုချင်းစီအတွက် `print_gps_data` function ကို ခေါ်သည်။

    ဒေတာအားလုံးကို ဖတ်ပြီးနောက် loop သည် ၁ စက္ကန့်အထိ sleep လုပ်ပြီး၊ ထို့နောက် ထပ်မံကြိုးစားသည်။

1. ဒီ code ကို run လုပ်ပါ။ သင် GPS ဆင်ဆာမှ raw output ကို အောက်ပါအတိုင်းတွေ့ရမည်:

    ```output
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GPGSA,A,1,,,,,,,,,,,,,,,*1E
    $BDGSA,A,1,,,,,,,,,,,,,,,*0F
    $GPGSV,1,1,00*79
    $BDGSV,1,1,00*68
    ```

    > သင့် code ကို ရပ်ပြီး ပြန်စတင်သောအခါ အောက်ပါ error များထဲမှ တစ်ခုခုရရှိပါက၊ သင့် while loop တွင် `try - except` block ထည့်ပါ။

      ```output
      UnicodeDecodeError: 'utf-8' codec can't decode byte 0x93 in position 0: invalid start byte
      UnicodeDecodeError: 'utf-8' codec can't decode byte 0xf1 in position 0: invalid continuation byte
      ```

    ```python
    while True:
        try:
            line = serial.readline().decode('utf-8')
              
            while len(line) > 0:
                print_gps_data()
                line = serial.readline().decode('utf-8')
      
        # There's a random chance the first byte being read is part way through a character.
        # Read another full line and continue.

        except UnicodeDecodeError:
            line = serial.readline().decode('utf-8')

    time.sleep(1)
    ```

> 💁 ဒီ code ကို [code-gps/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps/pi) folder တွင် ရှာဖွေနိုင်ပါသည်။

😀 သင့်ရဲ့ GPS ဆင်ဆာအစီအစဉ်အောင်မြင်ပါပြီ!

---

**အကြောင်းကြားချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှုအတွက် ကြိုးစားနေသော်လည်း၊ အလိုအလျောက် ဘာသာပြန်မှုများတွင် အမှားများ သို့မဟုတ် မတိကျမှုများ ပါရှိနိုင်သည်ကို သတိပြုပါ။ မူရင်းဘာသာစကားဖြင့် ရေးသားထားသော စာရွက်စာတမ်းကို အာဏာတရ အရင်းအမြစ်အဖြစ် သတ်မှတ်သင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူ့ဘာသာပြန်ပညာရှင်များမှ ပရော်ဖက်ရှင်နယ် ဘာသာပြန်မှုကို အကြံပြုပါသည်။ ဤဘာသာပြန်မှုကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော အလွဲအမှားများ သို့မဟုတ် အနားလွဲမှုများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။