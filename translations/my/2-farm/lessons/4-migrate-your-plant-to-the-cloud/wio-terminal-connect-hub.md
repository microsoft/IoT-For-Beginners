<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "28320305a35ea3bc59c41fe146a2e6ed",
  "translation_date": "2025-08-28T18:05:16+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/wio-terminal-connect-hub.md",
  "language_code": "my"
}
-->
# သင့် IoT စက်ကို Cloud နှင့် ချိတ်ဆက်ပါ - Wio Terminal

ဒီသင်ခန်းပိုင်းမှာ သင့် Wio Terminal ကို IoT Hub နှင့် ချိတ်ဆက်ပြီး telemetry ပေးပို့ခြင်းနှင့် အမိန့်များကို လက်ခံပါမည်။

## သင့်စက်ကို IoT Hub နှင့် ချိတ်ဆက်ပါ

နောက်တစ်ဆင့်မှာ သင့်စက်ကို IoT Hub နှင့် ချိတ်ဆက်ရမည်ဖြစ်သည်။

### အလုပ်ပေးချက် - IoT Hub နှင့် ချိတ်ဆက်ပါ

1. VS Code မှာ `soil-moisture-sensor` project ကို ဖွင့်ပါ။

1. `platformio.ini` ဖိုင်ကို ဖွင့်ပါ။ `knolleary/PubSubClient` library dependency ကို ဖယ်ရှားပါ။ ဒီ library ကို public MQTT broker နှင့် ချိတ်ဆက်ရန် အသုံးပြုခဲ့ပြီး၊ IoT Hub နှင့် ချိတ်ဆက်ရန် မလိုအပ်ပါ။

1. အောက်ပါ library dependencies ကို ထည့်ပါ။

    ```ini
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    arduino-libraries/AzureIoTHub @ 1.6.0
    azure/AzureIoTUtility @ 1.6.1
    azure/AzureIoTProtocol_MQTT @ 1.6.0
    azure/AzureIoTProtocol_HTTP @ 1.6.0
    azure/AzureIoTSocket_WiFi @ 1.0.2
    ```

    `Seeed Arduino RTC` library သည် Wio Terminal ရှိ real-time clock ကို အသုံးပြုရန် code ပေးသည်။ ကျန်ရှိသော libraries များသည် သင့် IoT စက်ကို IoT Hub နှင့် ချိတ်ဆက်ရန် အခွင့်ပြုသည်။

1. `platformio.ini` ဖိုင်၏ အောက်ဆုံးတွင် အောက်ပါကို ထည့်ပါ။

    ```ini
    build_flags =
        -DDONT_USE_UPLOADTOBLOB
    ```

    Arduino IoT Hub code ကို compile လုပ်ရာတွင် လိုအပ်သော compiler flag ကို သတ်မှတ်သည်။

1. `config.h` header ဖိုင်ကို ဖွင့်ပါ။ MQTT settings အားလုံးကို ဖယ်ရှားပြီး device connection string အတွက် အောက်ပါ constant ကို ထည့်ပါ။

    ```cpp
    // IoT Hub settings
    const char *CONNECTION_STRING = "<connection string>";
    ```

    `<connection string>` ကို သင့်စက်အတွက် ယခင်က ကူးထားသော connection string ဖြင့် အစားထိုးပါ။

1. IoT Hub နှင့် ချိတ်ဆက်မှုသည် အချိန်အခြေခံ token ကို အသုံးပြုသည်။ ဒါကြောင့် IoT စက်သည် လက်ရှိအချိန်ကို သိရန် လိုအပ်သည်။ Windows, macOS, Linux ကဲ့သို့သော operating systems များက အင်တာနက်မှ အချိန်ကို အလိုအလျောက် synchronize လုပ်ပေးသလို မဟုတ်ပါ။ ဒါကြောင့် [NTP](https://wikipedia.org/wiki/Network_Time_Protocol) server မှ အချိန်ကို ရယူရန် code ထည့်ရန် လိုအပ်ပါမည်။ အချိန်ရယူပြီးနောက် Wio Terminal ရှိ real-time clock တွင် သိမ်းဆည်းနိုင်ပြီး၊ စက်သည် မီးပျက်သွားခြင်းမရှိပါက နောက်တစ်ကြိမ် အချိန်ကို တောင်းယူနိုင်ပါမည်။ `ntp.h` ဟုခေါ်သော ဖိုင်အသစ်တစ်ခုကို ဖန်တီးပြီး အောက်ပါ code ကို ထည့်ပါ။

    ```cpp
    #pragma once
    
    #include "DateTime.h"
    #include <time.h>
    #include "samd/NTPClientAz.h"
    #include <sys/time.h>

    static void initTime()
    {
        WiFiUDP _udp;
        time_t epochTime = (time_t)-1;
        NTPClientAz ntpClient;

        ntpClient.begin();

        while (true)
        {
            epochTime = ntpClient.getEpochTime("0.pool.ntp.org");

            if (epochTime == (time_t)-1)
            {
                Serial.println("Fetching NTP epoch time failed! Waiting 2 seconds to retry.");
                delay(2000);
            }
            else
            {
                Serial.print("Fetched NTP epoch time is: ");

                char buff[32];
                sprintf(buff, "%.f", difftime(epochTime, (time_t)0));
                Serial.println(buff);
                break;
            }
        }

        ntpClient.end();

        struct timeval tv;
        tv.tv_sec = epochTime;
        tv.tv_usec = 0;

        settimeofday(&tv, NULL);
    }
    ```

    ဒီ code ၏ အသေးစိတ်ကို ဒီသင်ခန်းပိုင်းတွင် မဖော်ပြပါ။ ဒါဟာ `initTime` ဟုခေါ်သော function ကို သတ်မှတ်ပြီး၊ NTP server မှ လက်ရှိအချိန်ကို ရယူကာ Wio Terminal ရှိ clock ကို သတ်မှတ်ပေးသည်။

1. `main.cpp` ဖိုင်ကို ဖွင့်ပြီး MQTT code အားလုံးကို ဖယ်ရှားပါ။ `PubSubClient.h` header ဖိုင်၊ `PubSubClient` variable ကို ကြေညာထားမှု၊ `reconnectMQTTClient` နှင့် `createMQTTClient` methods၊ နှင့် ဒီ variables နှင့် methods ကို ခေါ်ထားသော code များကို ဖယ်ရှားပါ။ ဒီဖိုင်မှာ WiFi နှင့် ချိတ်ဆက်ခြင်း၊ soil moisture ကို ရယူခြင်း၊ JSON document တစ်ခု ဖန်တီးခြင်းအတွက် code များသာ ပါဝင်ရမည်။

1. IoT Hub libraries နှင့် အချိန်ကို သတ်မှတ်ရန် header files များကို ထည့်ရန် အောက်ပါ `#include` directives ကို `main.cpp` ဖိုင်၏ အပေါ်ဆုံးတွင် ထည့်ပါ။

    ```cpp
    #include <AzureIoTHub.h>
    #include <AzureIoTProtocol_MQTT.h>
    #include <iothubtransportmqtt.h>
    #include "ntp.h"
    ```

1. လက်ရှိအချိန်ကို သတ်မှတ်ရန် `setup` function ၏ အဆုံးတွင် အောက်ပါ call ကို ထည့်ပါ။

    ```cpp
    initTime();
    ```

1. ဖိုင်၏ အပေါ်ဆုံးတွင် include directives အောက်တွင် အောက်ပါ variable ကို ကြေညာပါ။

    ```cpp
    IOTHUB_DEVICE_CLIENT_LL_HANDLE _device_ll_handle;
    ```

    ဒီဟာ IoT Hub နှင့် ချိတ်ဆက်မှုအတွက် handle တစ်ခုဖြစ်သော `IOTHUB_DEVICE_CLIENT_LL_HANDLE` ကို ကြေညာသည်။

1. ဒီအောက်တွင် အောက်ပါ code ကို ထည့်ပါ။

    ```cpp
    static void connectionStatusCallback(IOTHUB_CLIENT_CONNECTION_STATUS result, IOTHUB_CLIENT_CONNECTION_STATUS_REASON reason, void *user_context)
    {
        if (result == IOTHUB_CLIENT_CONNECTION_AUTHENTICATED)
        {
            Serial.println("The device client is connected to iothub");
        }
        else
        {
            Serial.println("The device client has been disconnected");
        }
    }
    ```

    IoT Hub နှင့် ချိတ်ဆက်မှု status ပြောင်းလဲမှုများ (ချိတ်ဆက်ခြင်း၊ ချိတ်ဆက်မရခြင်း) ဖြစ်ပေါ်သောအခါ serial port သို့ status ကို ပေးပို့ရန် callback function ကို ကြေညာသည်။

1. ဒီအောက်တွင် IoT Hub နှင့် ချိတ်ဆက်ရန် function တစ်ခုကို ထည့်ပါ။

    ```cpp
    void connectIoTHub()
    {
        IoTHub_Init();
    
        _device_ll_handle = IoTHubDeviceClient_LL_CreateFromConnectionString(CONNECTION_STRING, MQTT_Protocol);
        
        if (_device_ll_handle == NULL)
        {
            Serial.println("Failure creating Iothub device. Hint: Check your connection string.");
            return;
        }
    
        IoTHubDeviceClient_LL_SetConnectionStatusCallback(_device_ll_handle, connectionStatusCallback, NULL);
    }
    ```

    ဒီ code သည် IoT Hub library code ကို initialize လုပ်ပြီး၊ `config.h` header ဖိုင်ရှိ connection string ကို အသုံးပြုကာ connection တစ်ခုကို ဖန်တီးသည်။ ဒီ connection သည် MQTT အခြေခံဖြစ်သည်။ connection မအောင်မြင်ပါက serial port သို့ error message ကို ပေးပို့သည် - output တွင် error message တွေ့ပါက connection string ကို စစ်ဆေးပါ။ နောက်ဆုံးတွင် connection status callback ကို setup လုပ်သည်။

1. ဒီ function ကို `setup` function တွင် `initTime` ကို ခေါ်ပြီးနောက် ခေါ်ပါ။

    ```cpp
    connectIoTHub();
    ```

1. MQTT client ကဲ့သို့ပင် ဒီ code သည် single thread ပေါ်တွင် run လုပ်ပြီး hub မှ ပေးပို့သော messages များနှင့် hub သို့ ပေးပို့သော messages များကို process လုပ်ရန် အချိန်လိုအပ်သည်။ `loop` function ၏ အပေါ်ဆုံးတွင် အောက်ပါ code ကို ထည့်ပါ။

    ```cpp
    IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
    ```

1. ဒီ code ကို build လုပ်ပြီး upload လုပ်ပါ။ serial monitor တွင် connection ကို တွေ့ရပါမည်။

    ```output
    Connecting to WiFi..
    Connected!
    Fetched NTP epoch time is: 1619983687
    Sending telemetry {"soil_moisture":391}
    The device client is connected to iothub
    ```

    Output တွင် NTP time ကို fetch လုပ်ခြင်းနှင့် device client ချိတ်ဆက်ခြင်းကို တွေ့ရပါမည်။ ချိတ်ဆက်ရန် စက္ကန့်အနည်းငယ် ကြာနိုင်ပြီး၊ စက်သည် ချိတ်ဆက်နေစဉ် output တွင် soil moisture ကို တွေ့နိုင်ပါသည်။

    > 💁 NTP မှ UNIX time ကို ပိုဖတ်ရှင်းနိုင်သော format သို့ ပြောင်းရန် [unixtimestamp.com](https://www.unixtimestamp.com) ကဲ့သို့သော website ကို အသုံးပြုနိုင်သည်။

## Telemetry ပေးပို့ပါ

စက်သည် IoT Hub နှင့် ချိတ်ဆက်ပြီးနောက်၊ MQTT broker အစား IoT Hub သို့ telemetry ပေးပို့နိုင်ပါသည်။

### အလုပ်ပေးချက် - telemetry ပေးပို့ပါ

1. `setup` function အပေါ်တွင် အောက်ပါ function ကို ထည့်ပါ။

    ```cpp
    void sendTelemetry(const char *telemetry)
    {
        IOTHUB_MESSAGE_HANDLE message_handle = IoTHubMessage_CreateFromString(telemetry);
        IoTHubDeviceClient_LL_SendEventAsync(_device_ll_handle, message_handle, NULL, NULL);
        IoTHubMessage_Destroy(message_handle);
    }
    ```

    ဒီ code သည် parameter အနေနှင့် string တစ်ခုကို လက်ခံကာ IoT Hub message တစ်ခုကို ဖန်တီးပြီး hub သို့ ပေးပို့ကာ၊ message object ကို cleanup လုပ်သည်။

1. Telemetry ကို serial port သို့ ပေးပို့သော line အပြီး `loop` function တွင် ဒီ code ကို ခေါ်ပါ။

    ```cpp
    sendTelemetry(telemetry.c_str());
    ```

## Command များကို လက်ခံပါ

သင့်စက်သည် relay ကို ထိန်းချုပ်ရန် server code မှ ပေးပို့သော command ကို လက်ခံရန် လိုအပ်သည်။ ဒီဟာ direct method request အနေနှင့် ပေးပို့သည်။

## အလုပ်ပေးချက် - direct method request ကို လက်ခံပါ

1. `connectIoTHub` function မတိုင်မီ အောက်ပါ code ကို ထည့်ပါ။

    ```cpp
    int directMethodCallback(const char *method_name, const unsigned char *payload, size_t size, unsigned char **response, size_t *response_size, void *userContextCallback)
    {
        Serial.printf("Direct method received %s\r\n", method_name);
    
        if (strcmp(method_name, "relay_on") == 0)
        {
            digitalWrite(PIN_WIRE_SCL, HIGH);
        }
        else if (strcmp(method_name, "relay_off") == 0)
        {
            digitalWrite(PIN_WIRE_SCL, LOW);
        }
    }
    ```

    ဒီ code သည် IoT Hub library မှ direct method request ရရှိသောအခါ ခေါ်နိုင်သော callback method ကို သတ်မှတ်သည်။ `method_name` parameter တွင် request သည့် method ကို ပေးပို့သည်။ ဒီ function သည် serial port တွင် method ကို print လုပ်ပြီး၊ method name အပေါ်မူတည်ကာ relay ကို ဖွင့်ခြင်း သို့မဟုတ် ပိတ်ခြင်းကို ပြုလုပ်သည်။

    > 💁 relay ၏ အခြေအနေကို payload အနေနှင့် method request နှင့်အတူ ပေးပို့ကာ `payload` parameter မှ ရယူနိုင်သော single direct method request အနေနှင့်လည်း ဒီကို အကောင်အထည်ဖော်နိုင်သည်။

1. `directMethodCallback` function ၏ အဆုံးတွင် အောက်ပါ code ကို ထည့်ပါ။

    ```cpp
    char resultBuff[16];
    sprintf(resultBuff, "{\"Result\":\"\"}");
    *response_size = strlen(resultBuff);
    *response = (unsigned char *)malloc(*response_size);
    memcpy(*response, resultBuff, *response_size);

    return IOTHUB_CLIENT_OK;
    ```

    Direct method requests သည် response တစ်ခုလိုအပ်ပြီး၊ response သည် text response နှင့် return code အပိုင်းနှစ်ခုပါဝင်သည်။ ဒီ code သည် အောက်ပါ JSON document အနေနှင့် result တစ်ခုကို ဖန်တီးသည်။

    ```JSON
    {
        "Result": ""
    }
    ```

    ဒီ JSON document ကို `response` parameter တွင် copy လုပ်ကာ၊ `response_size` parameter တွင် response size ကို သတ်မှတ်သည်။ method ကို မှန်ကန်စွာ handle လုပ်သည်ကို ပြသရန် `IOTHUB_CLIENT_OK` ကို return ပြုလုပ်သည်။

1. Callback ကို setup လုပ်ရန် `connectIoTHub` function ၏ အဆုံးတွင် အောက်ပါ code ကို ထည့်ပါ။

    ```cpp
    IoTHubClient_LL_SetDeviceMethodCallback(_device_ll_handle, directMethodCallback, NULL);
    ```

1. `loop` function သည် IoT Hub မှ ပေးပို့သော events များကို process လုပ်ရန် `IoTHubDeviceClient_LL_DoWork` function ကို ခေါ်ပါမည်။ ဒီဟာ `delay` ကြောင့် 10 စက္ကန့်တစ်ကြိမ်သာ ခေါ်သည်။ ဒါကြောင့် direct methods များကို 10 စက္ကန့်တစ်ကြိမ်သာ process လုပ်သည်။ ဒီကို ပိုထိရောက်စေရန် 10 စက္ကန့် delay ကို အနည်းငယ်သော delay များအဖြစ် ပြုလုပ်ကာ၊ အချိန်တိုင်း `IoTHubDeviceClient_LL_DoWork` ကို ခေါ်နိုင်သည်။ ဒီအတွက် `loop` function မတိုင်မီ အောက်ပါ code ကို ထည့်ပါ။

    ```cpp
    void work_delay(int delay_time)
    {
        int current = 0;
        do
        {
            IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
            delay(100);
            current += 100;
        } while (current < delay_time);
    }
    ```

    ဒီ code သည် repeatedly loop လုပ်ကာ `IoTHubDeviceClient_LL_DoWork` ကို ခေါ်ပြီး၊ တစ်ကြိမ်လျှင် 100ms အချိန်ပေးသည်။ `delay_time` parameter တွင် ပေးထားသော အချိန်အတိုင်း delay ပြုလုပ်ရန် လိုအပ်သလောက် loop လုပ်သည်။ ဒါကြောင့် direct method requests များကို process လုပ်ရန် အများဆုံး 100ms စောင့်ရမည်။

1. `loop` function တွင် `IoTHubDeviceClient_LL_DoWork` ကို ခေါ်ထားမှုကို ဖယ်ရှားပြီး၊ `delay(10000)` call ကို အောက်ပါ code ဖြင့် အစားထိုးပါ။

    ```cpp
    work_delay(10000);
    ```

> 💁 ဒီ code ကို [code/wio-terminal](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/wio-terminal) folder တွင် ရှာနိုင်သည်။

😀 သင့် soil moisture sensor program သည် IoT Hub နှင့် ချိတ်ဆက်ပြီးပါပြီ!

---

**အကြောင်းကြားချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှုအတွက် ကြိုးစားနေသော်လည်း၊ အလိုအလျောက် ဘာသာပြန်ခြင်းတွင် အမှားများ သို့မဟုတ် မတိကျမှုများ ပါရှိနိုင်သည်ကို သတိပြုပါ။ မူရင်းဘာသာစကားဖြင့် ရေးသားထားသော စာရွက်စာတမ်းကို အာဏာတရ အရင်းအမြစ်အဖြစ် သတ်မှတ်သင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူ့ဘာသာပြန်ပညာရှင်များမှ ပရော်ဖက်ရှင်နယ် ဘာသာပြန်ခြင်းကို အကြံပြုပါသည်။ ဤဘာသာပြန်ကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော အလွဲအလွဲအချော်များ သို့မဟုတ် အနားလွဲမှုများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။