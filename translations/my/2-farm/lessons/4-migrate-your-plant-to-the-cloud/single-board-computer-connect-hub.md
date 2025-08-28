<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3ac42e284a7222c0e83d2d43231a364f",
  "translation_date": "2025-08-28T18:03:57+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/single-board-computer-connect-hub.md",
  "language_code": "my"
}
-->
# သင့် IoT စက်ကို Cloud နှင့် ချိတ်ဆက်ပါ - Virtual IoT Hardware နှင့် Raspberry Pi

ဒီသင်ခန်းစာအပိုင်းမှာ သင့် Virtual IoT စက် သို့မဟုတ် Raspberry Pi ကို IoT Hub နှင့် ချိတ်ဆက်ပြီး telemetry ပေးပို့ခြင်းနှင့် အမိန့်များကို လက်ခံပါမည်။

## သင့်စက်ကို IoT Hub နှင့် ချိတ်ဆက်ပါ

နောက်တစ်ဆင့်မှာ သင့်စက်ကို IoT Hub နှင့် ချိတ်ဆက်ရမည်ဖြစ်သည်။

### လုပ်ဆောင်ရန် - IoT Hub နှင့် ချိတ်ဆက်ပါ

1. VS Code တွင် `soil-moisture-sensor` ဖိုလ်ဒါကို ဖွင့်ပါ။ သင် Virtual IoT စက်ကို အသုံးပြုနေပါက terminal တွင် virtual environment ကို run လုပ်ထားကြောင်း သေချာစေပါ။

1. အောက်ပါ Pip packages များကို ထည့်သွင်းပါ-

    ```sh
    pip3 install azure-iot-device
    ```

    `azure-iot-device` သည် သင့် IoT Hub နှင့် ဆက်သွယ်ရန် အသုံးပြုသော library ဖြစ်သည်။

1. `app.py` ဖိုင်၏ အပေါ်ပိုင်းတွင် ရှိပြီးသား imports အောက်တွင် အောက်ပါ imports များကို ထည့်ပါ-

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse
    ```

    ဒီ code သည် သင့် IoT Hub နှင့် ဆက်သွယ်ရန် အသုံးပြုသော SDK ကို import လုပ်သည်။

1. `import paho.mqtt.client as mqtt` ကို ဖယ်ရှားပါ၊ ဒီ library သည် မလိုအပ်တော့ပါ။ MQTT topic အမည်များအပါအဝင် MQTT code အားလုံးကို ဖယ်ရှားပါ၊ `mqtt_client` နှင့် `handle_command` ကို အသုံးပြုသော code များကိုလည်း ဖယ်ရှားပါ။ သို့သော် `while True:` loop ကို ထားရှိထားပြီး loop အတွင်းရှိ `mqtt_client.publish` ကို ဖယ်ရှားပါ။

1. Import statements အောက်တွင် အောက်ပါ code ကို ထည့်ပါ-

    ```python
    connection_string = "<connection string>"
    ```

    `<connection string>` ကို သင်ဒီသင်ခန်းစာ၏ အရင်ပိုင်းတွင် ရယူထားသော device connection string ဖြင့် အစားထိုးပါ။

    > 💁 ဒီနည်းလမ်းသည် အကောင်းဆုံးနည်းလမ်းမဟုတ်ပါ။ Connection strings များကို source code အတွင်း သိမ်းဆည်းထားသင့်မဟုတ်ပါ၊ အခြားသူများက source code control မှတစ်ဆင့် ရှာဖွေနိုင်ပါသည်။ ဒီနေရာမှာ ရိုးရှင်းစွာအတွက်သာ ဒီနည်းလမ်းကို အသုံးပြုထားပါသည်။ အကောင်းဆုံးနည်းလမ်းအနေဖြင့် environment variable တစ်ခုနှင့် [`python-dotenv`](https://pypi.org/project/python-dotenv/) ကဲ့သို့သော tool ကို အသုံးပြုသင့်သည်။ သင်သည် ဒီအကြောင်းကို နောက်ထပ်သင်ခန်းစာတွင် လေ့လာမည်ဖြစ်သည်။

1. အောက်ပါ code ကို ထည့်ပါ၊ ဒါဟာ IoT Hub နှင့် ဆက်သွယ်နိုင်သော device client object တစ်ခုကို ဖန်တီးပြီး ချိတ်ဆက်ပါမည်-

    ```python
    device_client = IoTHubDeviceClient.create_from_connection_string(connection_string)

    print('Connecting')
    device_client.connect()
    print('Connected')
    ```

1. ဒီ code ကို run လုပ်ပါ။ သင့်စက်သည် ချိတ်ဆက်ထားကြောင်း တွေ့ရမည်။

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Connecting
    Connected
    Soil moisture: 379
    ```

## Telemetry ပေးပို့ပါ

သင့်စက်သည် IoT Hub နှင့် ချိတ်ဆက်ပြီးဖြစ်သောကြောင့် MQTT broker အစား IoT Hub သို့ telemetry ပေးပို့နိုင်ပါသည်။

### လုပ်ဆောင်ရန် - Telemetry ပေးပို့ပါ

1. `while True` loop အတွင်း sleep မလုပ်မီ အောက်ပါ code ကို ထည့်ပါ-

    ```python
    message = Message(json.dumps({ 'soil_moisture': soil_moisture }))
    device_client.send_message(message)
    ```

    ဒီ code သည် IoT Hub `Message` တစ်ခုကို ဖန်တီးပြီး JSON string အဖြစ် soil moisture reading ကို ထည့်သွင်းပြီး IoT Hub သို့ device-to-cloud message အဖြစ် ပေးပို့သည်။

## အမိန့်များကို လက်ခံပါ

သင့်စက်သည် relay ကို ထိန်းချုပ်ရန် server code မှ ပေးပို့သော အမိန့်ကို လက်ခံရမည်။ ဒီအမိန့်ကို direct method request အဖြစ် ပေးပို့သည်။

### လုပ်ဆောင်ရန် - Direct Method Request ကို လက်ခံပါ

1. `while True` loop မတိုင်မီ အောက်ပါ code ကို ထည့်ပါ-

    ```python
    def handle_method_request(request):
        print("Direct method received - ", request.name)
    
        if request.name == "relay_on":
            relay.on()
        elif request.name == "relay_off":
            relay.off()    
    ```

    ဒီ code သည် `handle_method_request` ဟုခေါ်သော method တစ်ခုကို သတ်မှတ်သည်။ IoT Hub မှ direct method တစ်ခုခေါ်သည့်အခါ ဒီ method ကို ခေါ်မည်ဖြစ်သည်။ Relay ကို ဖွင့်ရန် `relay_on` ဟုခေါ်သော method နှင့် relay ကို ပိတ်ရန် `relay_off` ဟုခေါ်သော method ကို ဒီ code မှာ မျှော်မှန်းထားသည်။

    > 💁 ဒီအမိန့်ကို တစ်ခုတည်းသော direct method request အဖြစ်လည်း အကောင်အထည်ဖော်နိုင်သည်၊ relay ၏ လိုအပ်သော အခြေအနေကို payload အဖြစ် ပေးပို့ပြီး `request` object မှ ရယူနိုင်သည်။

1. Direct methods များသည် အမိန့်ကို လက်ခံပြီးဖြစ်ကြောင်း ပြန်လည်အသိပေးရန် response တစ်ခုလိုအပ်သည်။ `handle_method_request` function ၏ အဆုံးတွင် အောက်ပါ code ကို ထည့်ပါ-

    ```python
    method_response = MethodResponse.create_from_method_request(request, 200)
    device_client.send_method_response(method_response)
    ```

    ဒီ code သည် direct method request ကို HTTP status code 200 ဖြင့် response ပေးပြီး IoT Hub သို့ ပြန်ပို့သည်။

1. ဒီ function သတ်မှတ်ချက်အောက်တွင် အောက်ပါ code ကို ထည့်ပါ-

    ```python
    device_client.on_method_request_received = handle_method_request
    ```

    ဒီ code သည် IoT Hub client ကို direct method တစ်ခုခေါ်သည့်အခါ `handle_method_request` function ကို ခေါ်ရန် ပြောသည်။

> 💁 ဒီ code ကို [code/pi](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/pi) သို့မဟုတ် [code/virtual-device](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/virtual-device) ဖိုလ်ဒါတွင် ရှာနိုင်ပါသည်။

😀 သင့် soil moisture sensor program သည် IoT Hub နှင့် ချိတ်ဆက်ပြီးဖြစ်ပါပြီ!

---

**အကြောင်းကြားချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှုအတွက် ကြိုးစားနေသော်လည်း၊ အလိုအလျောက် ဘာသာပြန်မှုများတွင် အမှားများ သို့မဟုတ် မတိကျမှုများ ပါဝင်နိုင်သည်ကို သတိပြုပါ။ မူရင်းဘာသာစကားဖြင့် ရေးသားထားသော စာရွက်စာတမ်းကို အာဏာတရ အရင်းအမြစ်အဖြစ် ရှုယူသင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူက ဘာသာပြန်မှု ဝန်ဆောင်မှုကို အသုံးပြုရန် အကြံပြုပါသည်။ ဤဘာသာပြန်မှုကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော အလွဲအလွတ်များ သို့မဟုတ် အနားလွဲမှုများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။