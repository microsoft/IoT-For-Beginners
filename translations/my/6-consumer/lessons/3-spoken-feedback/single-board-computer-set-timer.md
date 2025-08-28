<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "64ad4ddb4de81a18b7252e968f10b404",
  "translation_date": "2025-08-28T16:22:35+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/single-board-computer-set-timer.md",
  "language_code": "my"
}
-->
# အချိန်တစ်ခုကို သတ်မှတ်ပါ - Virtual IoT Hardware နှင့် Raspberry Pi

ဒီသင်ခန်းစာအပိုင်းမှာ သင်၏ serverless code ကိုခေါ်ပြီး စကားကိုနားလည်စေပြီး၊ ရလဒ်အပေါ်မူတည်၍ သင်၏ virtual IoT device သို့မဟုတ် Raspberry Pi တွင် အချိန်တစ်ခုကို သတ်မှတ်ပါမည်။

## အချိန်တစ်ခုကို သတ်မှတ်ပါ

Speech to text call မှ ပြန်လာသောစာသားကို သင်၏ serverless code သို့ ပို့ရန်လိုအပ်ပြီး၊ LUIS မှ အချိန်သတ်မှတ်ရန် seconds အရေအတွက်ကို ပြန်ပေးပါမည်။ ဒီ seconds အရေအတွက်ကို အသုံးပြု၍ timer ကို သတ်မှတ်နိုင်ပါသည်။

Timers ကို Python ရဲ့ `threading.Timer` class ကို အသုံးပြု၍ သတ်မှတ်နိုင်ပါသည်။ ဒီ class က အချိန်နှောင့်နှေးမှုနှင့် function တစ်ခုကို လိုအပ်ပြီး၊ အချိန်နှောင့်နှေးမှုပြီးလျှင် function ကို အလုပ်လုပ်စေပါသည်။

### အလုပ် - စာသားကို serverless function သို့ ပို့ပါ

1. VS Code မှာ `smart-timer` project ကို ဖွင့်ပြီး၊ virtual IoT device ကို အသုံးပြုနေပါက terminal မှာ virtual environment ကို load လုပ်ထားပါ။

1. `process_text` function အပေါ်တွင် `get_timer_time` ဟုခေါ်သော function တစ်ခုကို ကြေညာပြီး သင်ဖန်တီးထားသော REST endpoint ကို ခေါ်ပါ:

    ```python
    def get_timer_time(text):
    ```

1. ဒီ function မှာ ခေါ်ရန် URL ကို သတ်မှတ်ရန် အောက်ပါ code ကို ထည့်ပါ:

    ```python
    url = '<URL>'
    ```

    `<URL>` ကို သင်၏ REST endpoint URL ဖြင့် အစားထိုးပါ၊ သင်၏ကွန်ပျူတာတွင် သို့မဟုတ် cloud တွင် ဖန်တီးထားသော URL ဖြစ်သည်။

1. စာသားကို JSON property အဖြစ် call မှာ ပေးပို့ရန် အောက်ပါ code ကို ထည့်ပါ:

    ```python
    body = {
        'text': text
    }
    
    response = requests.post(url, json=body)
    ```

1. ဒီ code အောက်တွင် response payload မှ `seconds` ကို ရယူပြီး၊ call မအောင်မြင်ပါက 0 ကို ပြန်ပေးပါ:

    ```python
    if response.status_code != 200:
        return 0
    
    payload = response.json()
    return payload['seconds']
    ```

    အောင်မြင်သော HTTP calls တွင် 200 range status code ကို ပြန်ပေးပြီး၊ သင်၏ serverless code က စာသားကို process လုပ်ပြီး set timer intent အဖြစ် အသိအမှတ်ပြုပါက 200 ကို ပြန်ပေးပါသည်။

### အလုပ် - background thread မှာ timer ကို သတ်မှတ်ပါ

1. Python threading library ကို import လုပ်ရန် အောက်ပါ import statement ကို ဖိုင်၏ အပေါ်ဆုံးတွင် ထည့်ပါ:

    ```python
    import threading
    ```

1. `process_text` function အပေါ်တွင် response ကို ပြောရန် function တစ်ခုကို ထည့်ပါ။ အခုအချိန်မှာ console မှာသာရေးမည်ဖြစ်ပြီး၊ ဒီသင်ခန်းစာနောက်ပိုင်းမှာ text ကို ပြောမည်ဖြစ်သည်။

    ```python
    def say(text):
        print(text)
    ```

1. ဒီအောက်တွင် timer ပြီးဆုံးသည်ဟု ကြေညာရန် timer မှ ခေါ်မည့် function တစ်ခုကို ထည့်ပါ:

    ```python
    def announce_timer(minutes, seconds):
        announcement = 'Times up on your '
        if minutes > 0:
            announcement += f'{minutes} minute '
        if seconds > 0:
            announcement += f'{seconds} second '
        announcement += 'timer.'
        say(announcement)
    ```

    ဒီ function က timer အတွက် minutes နှင့် seconds အရေအတွက်ကို ယူပြီး timer ပြီးဆုံးသည်ဟု ပြောမည့် စာကြောင်းတစ်ခုကို ဖန်တီးပါသည်။ minutes နှင့် seconds အရေအတွက်ကို စစ်ဆေးပြီး၊ အရေအတွက်ရှိသော time unit ကိုသာ message တွင် ထည့်ပါသည်။ ဥပမာအားဖြင့် minutes အရေအတွက် 0 ဖြစ်ပါက seconds ကိုသာ message တွင် ထည့်ပါသည်။ ဒီစာကြောင်းကို `say` function သို့ ပို့ပါသည်။

1. ဒီအောက်တွင် timer တစ်ခုကို ဖန်တီးရန် `create_timer` function ကို ထည့်ပါ:

    ```python
    def create_timer(total_seconds):
        minutes, seconds = divmod(total_seconds, 60)
        threading.Timer(total_seconds, announce_timer, args=[minutes, seconds]).start()
    ```

    ဒီ function က command မှ timer အတွက် seconds အရေအတွက်ကို ယူပြီး minutes နှင့် seconds သို့ ပြောင်းပါသည်။ ထို့နောက် timer object တစ်ခုကို seconds အရေအတွက်နှင့် `announce_timer` function ကို အသုံးပြု၍ ဖန်တီးပြီး စတင်ပါသည်။ timer ပြီးဆုံးသည့်အခါ `announce_timer` function ကို ခေါ်ပြီး list ၏ content ကို parameters အဖြစ် ပေးပို့ပါသည် - list ၏ ပထမ item ကို `minutes` parameter အဖြစ်၊ ဒုတိယ item ကို `seconds` parameter အဖြစ် ပေးပို့ပါသည်။

1. `create_timer` function ၏ အဆုံးတွင် timer စတင်သည်ဟု အသုံးပြုသူအား ကြေညာရန် message တစ်ခုကို ဖန်တီးရန် code ကို ထည့်ပါ:

    ```python
    announcement = ''
    if minutes > 0:
        announcement += f'{minutes} minute '
    if seconds > 0:
        announcement += f'{seconds} second '    
    announcement += 'timer started.'
    say(announcement)
    ```

    ထပ်မံ၍ time unit အရေအတွက်ရှိသော unit ကိုသာ message တွင် ထည့်ပါသည်။ ဒီစာကြောင်းကို `say` function သို့ ပို့ပါသည်။

1. `process_text` function ၏ အဆုံးတွင် timer အတွက် seconds အရေအတွက်ကို text မှ ရယူပြီး timer ကို ဖန်တီးရန် အောက်ပါ code ကို ထည့်ပါ:

    ```python
    seconds = get_timer_time(text)
    if seconds > 0:
        create_timer(seconds)
    ```

    seconds အရေအတွက် 0 ထက် ကြီးပါက timer ကိုသာ ဖန်တီးပါသည်။

1. app ကို run လုပ်ပြီး၊ function app ကိုလည်း run လုပ်ပါ။ timer များကို သတ်မှတ်ပြီး၊ output မှာ timer သတ်မှတ်ခြင်းနှင့် timer ပြီးဆုံးသည့်အခါ output ကို ပြပါမည်:

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Set a two minute 27 second timer.
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```

> 💁 ဒီ code ကို [code-timer/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/pi) သို့မဟုတ် [code-timer/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/virtual-iot-device) folder တွင် ရှာနိုင်ပါသည်။

😀 သင်၏ timer program အောင်မြင်ခဲ့ပါသည်!

---

**အကြောင်းကြားချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှုအတွက် ကြိုးစားနေသော်လည်း၊ အလိုအလျောက် ဘာသာပြန်ခြင်းတွင် အမှားများ သို့မဟုတ် မတိကျမှုများ ပါဝင်နိုင်သည်ကို သတိပြုပါ။ မူရင်းဘာသာစကားဖြင့် ရေးသားထားသော စာရွက်စာတမ်းကို အာဏာရှိသော ရင်းမြစ်အဖြစ် သတ်မှတ်သင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူ့ဘာသာပြန်ပညာရှင်များမှ ပရော်ဖက်ရှင်နယ် ဘာသာပြန်ခြင်းကို အကြံပြုပါသည်။ ဤဘာသာပြန်ကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော အလွဲအလွဲအချော်များ သို့မဟုတ် အနားလွဲမှုများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။