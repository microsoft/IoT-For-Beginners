<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "50151d9f9dce2801348a93880ef16d86",
  "translation_date": "2025-08-28T16:04:02+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/single-board-computer.md",
  "language_code": "my"
}
-->
# IoT Edge အခြေခံထားသော ပုံခွဲခြားစက်ကို အသုံးပြု၍ ပုံတစ်ပုံကို ခွဲခြားခြင်း - အတု IoT Hardware နှင့် Raspberry Pi

ဒီသင်ခန်းပိုင်းမှာ၊ သင်သည် IoT Edge စက်ပေါ်တွင် လည်ပတ်နေသော Image Classifier ကို အသုံးပြုမည်ဖြစ်သည်။

## IoT Edge Classifier ကို အသုံးပြုပါ

IoT စက်ကို IoT Edge Image Classifier ကို အသုံးပြုရန် ပြောင်းလဲနိုင်သည်။ Image Classifier အတွက် URL သည် `http://<IP address or name>/image` ဖြစ်ပြီး `<IP address or name>` ကို IoT Edge လည်ပတ်နေသော ကွန်ပျူတာ၏ IP လိပ်စာ သို့မဟုတ် host name ဖြင့် အစားထိုးပါ။

Custom Vision အတွက် Python library သည် cloud-hosted models တွင်သာ လည်ပတ်နိုင်ပြီး IoT Edge ပေါ်တွင် host လုပ်ထားသော models များတွင် မလည်ပတ်နိုင်ပါ။ ဒါကြောင့် REST API ကို အသုံးပြု၍ classifier ကို ခေါ်ရန် လိုအပ်ပါသည်။

### Task - IoT Edge Classifier ကို အသုံးပြုပါ

1. `fruit-quality-detector` project ကို VS Code မှာ ဖွင့်ပါ၊ project ကို မဖွင့်ထားသေးလျှင် ဖွင့်ပါ။ အတု IoT စက်ကို အသုံးပြုနေပါက virtual environment ကို active လုပ်ထားပါ။

1. `app.py` ဖိုင်ကို ဖွင့်ပြီး `azure.cognitiveservices.vision.customvision.prediction` နှင့် `msrest.authentication` မှ import statements များကို ဖျက်ပါ။

1. ဖိုင်၏ အပေါ်ပိုင်းတွင် အောက်ပါ import ကို ထည့်ပါ-

    ```python
    import requests
    ```

1. ပုံကို ဖိုင်ထဲသို့ သိမ်းပြီးနောက်ရှိ code အားလုံးကို `image_file.write(image.read())` မှာစပြီး ဖိုင်၏ အဆုံးအထိ ဖျက်ပါ။

1. ဖိုင်၏ အဆုံးတွင် အောက်ပါ code ကို ထည့်ပါ-

    ```python
    prediction_url = '<URL>'
    headers = {
        'Content-Type' : 'application/octet-stream'
    }
    image.seek(0)
    response = requests.post(prediction_url, headers=headers, data=image)
    results = response.json()
    
    for prediction in results['predictions']:
        print(f'{prediction["tagName"]}:\t{prediction["probability"] * 100:.2f}%')
    ```

    `<URL>` ကို သင့် classifier အတွက် URL ဖြင့် အစားထိုးပါ။

    ဒီ code သည် REST POST request ကို classifier သို့ ပို့ပြီး request body အနေဖြင့် ပုံကို ပေးပို့သည်။ ရလဒ်များသည် JSON အနေဖြင့် ပြန်လာပြီး၊ probability များကို print ထုတ်ရန် decode လုပ်သည်။

1. သင့် code ကို run လုပ်ပါ၊ သင့်ကင်မရာကို သစ်သီးများ သို့မဟုတ် သင့် webcam တွင် သင့်လျော်သော ပုံများ သို့မဟုတ် သစ်သီးများကို ဦးတည်ထားပါ။ console တွင် output ကို မြင်ရပါမည်-

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 ဒီ code ကို [code-classify/pi](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/pi) သို့မဟုတ် [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/virtual-iot-device) folder တွင် ရှာနိုင်ပါသည်။

😀 သင့်သစ်သီးအရည်အသွေးခွဲခြားစက်ပရိုဂရမ်သည် အောင်မြင်ခဲ့ပါသည်!

---

**အကြောင်းကြားချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှုအတွက် ကြိုးစားနေသော်လည်း၊ အလိုအလျောက် ဘာသာပြန်မှုများတွင် အမှားများ သို့မဟုတ် မမှန်ကန်မှုများ ပါဝင်နိုင်သည်ကို သတိပြုပါ။ မူရင်းစာရွက်စာတမ်းကို ၎င်း၏ မူလဘာသာစကားဖြင့် အာဏာတရားရှိသော အရင်းအမြစ်အဖြစ် သတ်မှတ်သင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူ့ဘာသာပြန်ပညာရှင်များမှ ပရော်ဖက်ရှင်နယ် ဘာသာပြန်မှုကို အကြံပြုပါသည်။ ဤဘာသာပြန်မှုကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော အလွဲအလွတ်များ သို့မဟုတ် အနားလွဲမှုများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။