<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c677667095f6133eee418c7e53615d05",
  "translation_date": "2025-08-28T16:06:36+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/pi-camera.md",
  "language_code": "my"
}
-->
# ရုပ်ပုံတစ်ပုံကိုဖမ်းယူခြင်း - Raspberry Pi

ဒီသင်ခန်းစာအပိုင်းမှာ၊ သင့်ရဲ့ Raspberry Pi မှာ ကင်မရာဆင်ဆာတစ်ခုထည့်ပြီး၊ ရုပ်ပုံတွေကိုဖတ်ယူပါမယ်။

## ဟာ့ဒ်ဝဲ

Raspberry Pi ကို ကင်မရာတစ်ခုလိုအပ်ပါတယ်။

သင်အသုံးပြုမယ့်ကင်မရာက [Raspberry Pi Camera Module](https://www.raspberrypi.org/products/camera-module-v2/) ဖြစ်ပါတယ်။ ဒီကင်မရာကို Raspberry Pi အတွက်ထုတ်လုပ်ထားပြီး Pi ရဲ့အထူး connector မှတဆင့်ချိတ်ဆက်နိုင်ပါတယ်။

> 💁 ဒီကင်မရာက [Camera Serial Interface, Mobile Industry Processor Interface Alliance](https://wikipedia.org/wiki/Camera_Serial_Interface) မှထုတ်လုပ်ထားတဲ့ MIPI-CSI protocol ကိုအသုံးပြုပါတယ်။ ဒါဟာ ရုပ်ပုံတွေကိုပို့ရန်အတွက်အထူး protocol ဖြစ်ပါတယ်။

## ကင်မရာကိုချိတ်ဆက်ပါ

ကင်မရာကို Raspberry Pi နဲ့ ribbon cable တစ်ခုကိုအသုံးပြုပြီးချိတ်ဆက်နိုင်ပါတယ်။

### အလုပ် - ကင်မရာကိုချိတ်ဆက်ပါ

![A Raspberry Pi Camera](../../../../../translated_images/my/pi-camera-module.4278753c31bd6e757aa2b858be97d72049f71616278cefe4fb5abb485b40a078.png)

1. Pi ကိုပိတ်ပါ။

1. ကင်မရာနဲ့လာတဲ့ ribbon cable ကို ကင်မရာနဲ့ချိတ်ဆက်ပါ။ ဒါလုပ်ဖို့အတွက် holder ရဲ့ အနက်ရောင်ပလပ်စတစ် clip ကိုအနည်းငယ်ဆွဲထုတ်ပြီး cable ကို socket ထဲကို slide လုပ်ပါ။ Blue side က lens ကိုမကြည့်ဘဲ၊ metal pin strips က lens ကိုကြည့်နေတဲ့အနေအထားဖြစ်ရပါမယ်။ Cable ကိုအပြည့်အဝထည့်ပြီးရင် အနက်ရောင် clip ကိုပြန် push လုပ်ပါ။

    [Raspberry Pi Getting Started with the Camera module documentation](https://projects.raspberrypi.org/en/projects/getting-started-with-picamera/2) မှာ clip ကိုဘယ်လိုဖွင့်ပြီး cable ကိုထည့်ရမယ်ဆိုတာ animation အနေနဲ့တွေ့နိုင်ပါတယ်။

    ![The ribbon cable inserted into the camera module](../../../../../translated_images/my/pi-camera-ribbon-cable.0bf82acd251611c21ac616f082849413e2b322a261d0e4f8fec344248083b07e.png)

1. Grove Base Hat ကို Pi မှာဖယ်ရှားပါ။

1. Ribbon cable ကို Grove Base Hat ရဲ့ camera slot မှတဆင့်ဖြတ်ပါ။ Cable ရဲ့ blue side က **A0**, **A1** စတဲ့ analog ports ကိုကြည့်နေတဲ့အနေအထားဖြစ်ရပါမယ်။

    ![The ribbon cable passing through the grove base hat](../../../../../translated_images/my/grove-base-hat-ribbon-cable.501fed202fcf73b11b2b68f6d246189f7d15d3e4423c572ddee79d77b4632b47.png)

1. Ribbon cable ကို Pi ရဲ့ camera port မှာထည့်ပါ။ အနက်ရောင် clip ကိုပြန်ဆွဲထုတ်ပြီး cable ကိုထည့်ပါ၊ ပြီးရင် clip ကိုပြန် push လုပ်ပါ။ Cable ရဲ့ blue side က USB နဲ့ ethernet ports ကိုကြည့်နေတဲ့အနေအထားဖြစ်ရပါမယ်။

    ![The ribbon cable connected to the camera socket on the Pi](../../../../../translated_images/my/pi-camera-socket-ribbon-cable.a18309920b11800911082ed7aa6fb28e6d9be3a022e4079ff990016cae3fca10.png)

1. Grove Base Hat ကိုပြန်တပ်ပါ။

## ကင်မရာကိုပရိုဂရမ်ရေးပါ

Raspberry Pi ကို [PiCamera](https://pypi.org/project/picamera/) Python library ကိုအသုံးပြုပြီး ကင်မရာကိုအသုံးပြုနိုင်ပါတယ်။

### အလုပ် - legacy camera mode ကို enable လုပ်ပါ

Raspberry Pi OS Bullseye ထွက်ရှိလာတာနဲ့အတူ OS နဲ့လာတဲ့ camera software ကပြောင်းလဲသွားပါတယ်၊ ဒါကြောင့် PiCamera က default အနေဖြင့်မအလုပ်လုပ်တော့ပါဘူး။ PiCamera2 ဆိုတဲ့အစားထိုး software တစ်ခုကိုဖွံ့ဖြိုးနေပါတယ်၊ ဒါပေမယ့် အခုအချိန်မှာအသုံးပြုဖို့မပြင်ဆင်ရသေးပါဘူး။

အခုအချိန်မှာ Pi ကို legacy camera mode မှာထားပြီး PiCamera ကိုအလုပ်လုပ်စေနိုင်ပါတယ်။ Camera socket က default အနေဖြင့် disable ဖြစ်နေပါတယ်၊ ဒါပေမယ့် legacy camera software ကိုဖွင့်လိုက်တာနဲ့ socket ကိုအလိုအလျောက် enable ဖြစ်သွားပါမယ်။

1. Pi ကိုဖွင့်ပြီး boot ဖြစ်အောင်စောင့်ပါ။

1. VS Code ကို Pi မှာတိုက်ရိုက်ဖွင့်ပါ၊ ဒါမှမဟုတ် Remote SSH extension ကိုအသုံးပြုပြီးချိတ်ဆက်ပါ။

1. Terminal မှာအောက်ပါ command တွေကို run လုပ်ပါ။

    ```sh
    sudo raspi-config nonint do_legacy 0
    sudo reboot
    ```

    ဒီ command က legacy camera software ကို enable လုပ်ပြီး Pi ကို reboot လုပ်ပါမယ်။

1. Pi ကို reboot ဖြစ်အောင်စောင့်ပြီး VS Code ကိုပြန်ဖွင့်ပါ။

### အလုပ် - ကင်မရာကိုပရိုဂရမ်ရေးပါ

Device ကိုပရိုဂရမ်ရေးပါ။

1. Terminal မှာ `pi` user ရဲ့ home directory မှာ `fruit-quality-detector` ဆိုတဲ့ folder တစ်ခုဖန်တီးပါ။ ဒီ folder မှာ `app.py` ဆိုတဲ့ file တစ်ခုဖန်တီးပါ။

1. Folder ကို VS Code မှာဖွင့်ပါ။

1. ကင်မရာနဲ့အပြန်အလှန်လုပ်ဆောင်ဖို့ PiCamera Python library ကိုအသုံးပြုနိုင်ပါတယ်။ Pip package ကိုအောက်ပါ command နဲ့ install လုပ်ပါ။

    ```sh
    pip3 install picamera
    ```

1. `app.py` file မှာအောက်ပါ code ကိုထည့်ပါ။

    ```python
    import io
    import time
    from picamera import PiCamera
    ```

    ဒီ code ကလိုအပ်တဲ့ library တွေကို import လုပ်ပြီး `PiCamera` library ကိုပါထည့်ထားပါတယ်။

1. ကင်မရာကို initialize လုပ်ဖို့အောက်ပါ code ကိုထည့်ပါ။

    ```python
    camera = PiCamera()
    camera.resolution = (640, 480)
    camera.rotation = 0
    
    time.sleep(2)
    ```

    ဒီ code က PiCamera object တစ်ခုကိုဖန်တီးပြီး resolution ကို 640x480 အဖြစ်သတ်မှတ်ထားပါတယ်။ Resolution ပိုမြင့်တဲ့အတိုင်း (3280x2464 အထိ) support လုပ်ပေမယ့် image classifier က resolution သေးတဲ့ရုပ်ပုံ (227x227) တွေမှာအလုပ်လုပ်တာကြောင့် resolution ပိုကြီးတဲ့ရုပ်ပုံတွေကို capture လုပ်ဖို့မလိုအပ်ပါဘူး။

    `camera.rotation = 0` ဆိုတဲ့ line ကရုပ်ပုံရဲ့ rotation ကိုသတ်မှတ်ပါတယ်။ Ribbon cable က ကင်မရာရဲ့အောက်ဘက်ကိုဝင်လာပေမယ့် ကင်မရာကို item ကို classify လုပ်ဖို့အဆင်ပြေစေဖို့လှည့်ထားရင် rotation ကိုလိုအပ်တဲ့အတိုင်းပြောင်းနိုင်ပါတယ်။

    ![The camera hanging down over a drink can](../../../../../translated_images/my/pi-camera-upside-down.5376961ba31459883362124152ad6b823d5ac5fc14e85f317e22903bd681c2b6.png)

    ဥပမာ၊ ribbon cable ကိုအပေါ်ဘက်မှာထားပြီး ကင်မရာကိုအောက်ဘက်ကိုလှည့်ထားရင် rotation ကို 180 အဖြစ်သတ်မှတ်ပါ။

    ```python
    camera.rotation = 180
    ```

    ကင်မရာကိုစတင်ဖို့အချိန်အနည်းငယ်လိုအပ်တာကြောင့် `time.sleep(2)` ကိုထည့်ထားပါတယ်။

1. ရုပ်ပုံကို binary data အနေနဲ့ capture လုပ်ဖို့အောက်ပါ code ကိုထည့်ပါ။

    ```python
    image = io.BytesIO()
    camera.capture(image, 'jpeg')
    image.seek(0)
    ```

    ဒီ code က binary data ကိုသိမ်းဆည်းဖို့ `BytesIO` object တစ်ခုကိုဖန်တီးပါတယ်။ ရုပ်ပုံကို JPEG file အနေနဲ့ကင်မရာမှဖတ်ပြီး ဒီ object မှာသိမ်းဆည်းပါတယ်။ ဒီ object မှာ data ရဲ့ position indicator ရှိပြီး data ကိုအဆုံးထိရေးနိုင်ဖို့အတွက် `image.seek(0)` line က position ကိုအစမှပြန်ရွှေ့ပါတယ်။

1. ရုပ်ပုံကို file အနေနဲ့သိမ်းဆည်းဖို့အောက်ပါ code ကိုထည့်ပါ။

    ```python
    with open('image.jpg', 'wb') as image_file:
        image_file.write(image.read())
    ```

    ဒီ code က `image.jpg` ဆိုတဲ့ file ကိုဖွင့်ပြီး `BytesIO` object မှာရှိတဲ့ data ကိုဖတ်ပြီး file ထဲကိုရေးပါတယ်။

    > 💁 ရုပ်ပုံကို `BytesIO` object အစား file ထဲကိုတိုက်ရိုက် capture လုပ်နိုင်ပါတယ်။ `camera.capture` call မှာ file name ကိုပေးရုံပါပဲ။ ဒီသင်ခန်းစာမှာ `BytesIO` object ကိုအသုံးပြုတာက image classifier ကိုရုပ်ပုံကိုပို့ဖို့အတွက်ပါ။

1. ကင်မရာကိုတစ်ခုခုကိုရိုက်ဖို့ point လုပ်ပြီး code ကို run လုပ်ပါ။

1. ရုပ်ပုံတစ်ပုံကို capture လုပ်ပြီး `image.jpg` အနေနဲ့ current folder မှာသိမ်းဆည်းပါမယ်။ VS Code explorer မှာ file ကိုတွေ့နိုင်ပါမယ်။ File ကိုရွေးပြီးရုပ်ပုံကိုကြည့်ပါ။ Rotation လိုအပ်ရင် `camera.rotation = 0` line ကို update လုပ်ပြီးရုပ်ပုံကိုပြန်ရိုက်ပါ။

> 💁 ဒီ code ကို [code-camera/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/pi) folder မှာတွေ့နိုင်ပါတယ်။

😀 သင့်ရဲ့ကင်မရာပရိုဂရမ်ရေးခြင်းအောင်မြင်ခဲ့ပါပြီ!

---

**အကြောင်းကြားချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှုအတွက် ကြိုးစားနေသော်လည်း၊ အလိုအလျောက် ဘာသာပြန်မှုများတွင် အမှားများ သို့မဟုတ် မတိကျမှုများ ပါဝင်နိုင်သည်ကို သတိပြုပါ။ မူရင်းစာရွက်စာတမ်းကို ၎င်း၏ မူလဘာသာစကားဖြင့် အာဏာတရားရှိသော အရင်းအမြစ်အဖြစ် သတ်မှတ်သင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူက ဘာသာပြန်မှုကို အသုံးပြုရန် အကြံပြုပါသည်။ ဤဘာသာပြန်မှုကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော အလွဲအလွတ်များ သို့မဟုတ် အနားယူမှုများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။