<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "28320305a35ea3bc59c41fe146a2e6ed",
  "translation_date": "2025-10-11T12:28:57+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/wio-terminal-connect-hub.md",
  "language_code": "ta"
}
-->
# உங்கள் IoT சாதனத்தை மேகத்துடன் இணைக்கவும் - Wio Terminal

இந்த பாடத்தின் இந்த பகுதியில், உங்கள் Wio Terminal ஐ உங்கள் IoT Hub உடன் இணைத்து, டெலிமெட்ரி அனுப்பவும் கட்டளைகளைப் பெறவும் செய்யலாம்.

## உங்கள் சாதனத்தை IoT Hub உடன் இணைக்கவும்

அடுத்த படியாக, உங்கள் சாதனத்தை IoT Hub உடன் இணைக்க வேண்டும்.

### பணிகள் - IoT Hub உடன் இணைக்கவும்

1. `soil-moisture-sensor` திட்டத்தை VS Code இல் திறக்கவும்.

2. `platformio.ini` கோப்பை திறக்கவும். `knolleary/PubSubClient` நூலக சார்பை அகற்றவும். இது பொது MQTT ப்ரோக்கருடன் இணைக்க பயன்படுத்தப்பட்டது, ஆனால் IoT Hub உடன் இணைக்க இது தேவையில்லை.

3. பின்வரும் நூலக சார்புகளைச் சேர்க்கவும்:

    ```ini
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    arduino-libraries/AzureIoTHub @ 1.6.0
    azure/AzureIoTUtility @ 1.6.1
    azure/AzureIoTProtocol_MQTT @ 1.6.0
    azure/AzureIoTProtocol_HTTP @ 1.6.0
    azure/AzureIoTSocket_WiFi @ 1.0.2
    ```
  
   `Seeed Arduino RTC` நூலகம் Wio Terminal இல் நேரத்தை கண்காணிக்க பயன்படுத்தப்படும் ஒரு நேரம் சார்ந்த கடிகாரத்துடன் தொடர்பு கொள்ள குறியீட்டை வழங்குகிறது. மீதமுள்ள நூலகங்கள் உங்கள் IoT சாதனத்தை IoT Hub உடன் இணைக்க அனுமதிக்கின்றன.

4. `platformio.ini` கோப்பின் கீழே பின்வரும் வரிகளைச் சேர்க்கவும்:

    ```ini
    build_flags =
        -DDONT_USE_UPLOADTOBLOB
    ```
  
   இது Arduino IoT Hub குறியீட்டை தொகுக்கும்போது தேவைப்படும் தொகுப்பாளர் கொடியை அமைக்கிறது.

5. `config.h` தலைப்பு கோப்பை திறக்கவும். அனைத்து MQTT அமைப்புகளையும் அகற்றி, சாதன இணைப்பு சரத்தின் பின்வரும் மாறியைச் சேர்க்கவும்:

    ```cpp
    // IoT Hub settings
    const char *CONNECTION_STRING = "<connection string>";
    ```
  
   `<connection string>` ஐ முன்பு நீங்கள் நகலெடுத்த உங்கள் சாதனத்தின் இணைப்பு சரத்துடன் மாற்றவும்.

6. IoT Hub உடன் இணைப்பு நேர அடிப்படையிலான டோக்கனைப் பயன்படுத்துகிறது. இதன் பொருள் IoT சாதனம் தற்போதைய நேரத்தை அறிந்திருக்க வேண்டும். Windows, macOS அல்லது Linux போன்ற இயக்க முறைமைகளுக்கு மாறாக, மைக்ரோகண்ட்ரோலர்கள் தானாகவே இணையத்தின் மூலம் தற்போதைய நேரத்தை ஒத்திசைக்காது. எனவே, [NTP](https://wikipedia.org/wiki/Network_Time_Protocol) சர்வரில் இருந்து தற்போதைய நேரத்தைப் பெற குறியீட்டைச் சேர்க்க வேண்டும். நேரத்தைப் பெற்ற பிறகு, Wio Terminal இல் ஒரு நேரம் சார்ந்த கடிகாரத்தில் சேமிக்கலாம், சாதனம் மின்சாரம் இழக்காத வரை பின்னர் சரியான நேரத்தை கோர அனுமதிக்கிறது. `ntp.h` என்ற புதிய கோப்பை பின்வரும் குறியீட்டுடன் சேர்க்கவும்:

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
  
   இந்த குறியீட்டின் விவரங்கள் இந்த பாடத்தின் வரம்புக்கு வெளியே உள்ளது. இது `initTime` என்ற ஒரு செயல்பாட்டை வரையறுக்கிறது, இது NTP சர்வரில் இருந்து தற்போதைய நேரத்தைப் பெறுகிறது மற்றும் Wio Terminal இல் கடிகாரத்தை அமைக்கிறது.

7. `main.cpp` கோப்பை திறந்து அனைத்து MQTT குறியீட்டையும் அகற்றவும், அதில் `PubSubClient.h` தலைப்பு கோப்பு, `PubSubClient` மாறியின் அறிவிப்பு, `reconnectMQTTClient` மற்றும் `createMQTTClient` முறைகள் மற்றும் இந்த மாறிகள் மற்றும் முறைகளுக்கு எந்த அழைப்புகளும் சேர்க்கப்பட்டுள்ளன. இந்த கோப்பில் WiFi உடன் இணைக்க, மண் ஈரப்பதம் பெற மற்றும் அதில் JSON ஆவணத்தை உருவாக்க மட்டுமே குறியீடு இருக்க வேண்டும்.

8. IoT Hub நூலக தலைப்பு கோப்புகளையும் நேரத்தை அமைக்கவும் பின்வரும் `#include` இயக்கங்களை `main.cpp` கோப்பின் மேல் சேர்க்கவும்:

    ```cpp
    #include <AzureIoTHub.h>
    #include <AzureIoTProtocol_MQTT.h>
    #include <iothubtransportmqtt.h>
    #include "ntp.h"
    ```
  
9. தற்போதைய நேரத்தை அமைக்க `setup` செயல்பாட்டின் இறுதியில் பின்வரும் அழைப்பைச் சேர்க்கவும்:

    ```cpp
    initTime();
    ```
  
10. கோப்பின் மேல், `include` இயக்கங்களின் கீழே பின்வரும் மாறி அறிவிப்பைச் சேர்க்கவும்:

    ```cpp
    IOTHUB_DEVICE_CLIENT_LL_HANDLE _device_ll_handle;
    ```
  
   இது `IOTHUB_DEVICE_CLIENT_LL_HANDLE` ஐ அறிவிக்கிறது, இது IoT Hub உடன் ஒரு இணைப்புக்கான கைப்பிடி ஆகும்.

11. இதன் கீழே பின்வரும் குறியீட்டைச் சேர்க்கவும்:

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
  
   இது IoT Hub உடன் இணைப்பின் நிலை மாறும்போது அழைக்கப்படும் ஒரு callback செயல்பாட்டை அறிவிக்கிறது, உதாரணமாக இணைப்பது அல்லது துண்டிக்கப்படுவது போன்றவை. நிலை தொடர்ச்சி சீரியல் போர்டுக்கு அனுப்பப்படும்.

12. இதன் கீழே, IoT Hub உடன் இணைக்க ஒரு செயல்பாட்டைச் சேர்க்கவும்:

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
  
   இந்த குறியீடு IoT Hub நூலக குறியீட்டை ஆரம்பிக்கிறது, பின்னர் `config.h` தலைப்பு கோப்பில் உள்ள இணைப்பு சரத்தைப் பயன்படுத்தி ஒரு இணைப்பை உருவாக்குகிறது. இந்த இணைப்பு MQTT அடிப்படையில் உள்ளது. இணைப்பு தோல்வியடைந்தால், இது சீரியல் போர்டுக்கு அனுப்பப்படும் - நீங்கள் வெளியீட்டில் இதைப் பார்த்தால், இணைப்பு சரத்தை சரிபார்க்கவும். இறுதியாக, இணைப்பு நிலை callback அமைக்கப்படுகிறது.

13. இந்த செயல்பாட்டை `setup` செயல்பாட்டில் `initTime` அழைப்பின் கீழே அழைக்கவும்:

    ```cpp
    connectIoTHub();
    ```
  
14. MQTT கிளையண்ட் போலவே, இந்த குறியீடும் ஒற்றை திரையில் இயங்குகிறது, எனவே ஹப் அனுப்பும் மற்றும் ஹப்பிற்கு அனுப்பப்படும் செய்திகளை செயலாக்க நேரம் தேவை. இதைச் செய்ய, பின்வரும் குறியீட்டை `loop` செயல்பாட்டின் மேல் சேர்க்கவும்:

    ```cpp
    IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
    ```
  
15. இந்த குறியீட்டை உருவாக்கி பதிவேற்றவும். நீங்கள் சீரியல் மானிட்டரில் இணைப்பைக் காணலாம்:

    ```output
    Connecting to WiFi..
    Connected!
    Fetched NTP epoch time is: 1619983687
    Sending telemetry {"soil_moisture":391}
    The device client is connected to iothub
    ```
  
   வெளியீட்டில், NTP நேரம் பெறப்படுவதைப் பின்பற்றியவுடன் சாதன கிளையண்ட் இணைக்கப்படுவதை நீங்கள் காணலாம். இணைக்க சில விநாடிகள் ஆகலாம், எனவே சாதனம் இணைக்கும்போது வெளியீட்டில் மண் ஈரப்பதம் காணலாம்.

   > 💁 NTP க்கான யுனிக்ஸ் நேரத்தை [unixtimestamp.com](https://www.unixtimestamp.com) போன்ற ஒரு இணையதளத்தைப் பயன்படுத்தி மேலும் வாசிக்கக்கூடிய வடிவமாக மாற்றலாம்.

## டெலிமெட்ரி அனுப்பவும்

இப்போது உங்கள் சாதனம் இணைக்கப்பட்டுள்ளது, நீங்கள் MQTT ப்ரோக்கருக்கு பதிலாக IoT Hub க்கு டெலிமெட்ரி அனுப்பலாம்.

### பணிகள் - டெலிமெட்ரி அனுப்பவும்

1. `setup` செயல்பாட்டுக்கு மேலே பின்வரும் செயல்பாட்டைச் சேர்க்கவும்:

    ```cpp
    void sendTelemetry(const char *telemetry)
    {
        IOTHUB_MESSAGE_HANDLE message_handle = IoTHubMessage_CreateFromString(telemetry);
        IoTHubDeviceClient_LL_SendEventAsync(_device_ll_handle, message_handle, NULL, NULL);
        IoTHubMessage_Destroy(message_handle);
    }
    ```
  
   இந்த குறியீடு ஒரு சரம் மூலம் IoT Hub செய்தியை உருவாக்கி, அதை ஹப்பிற்கு அனுப்பி, பின்னர் செய்தி பொருளை சுத்தம் செய்கிறது.

2. இந்த குறியீட்டை `loop` செயல்பாட்டில், டெலிமெட்ரி சீரியல் போர்டுக்கு அனுப்பப்படும் வரியின் பிறகு அழைக்கவும்:

    ```cpp
    sendTelemetry(telemetry.c_str());
    ```
  

## கட்டளைகளை கையாளவும்

உங்கள் சாதனம் ரிலேவை கட்டுப்படுத்த சர்வர் குறியீட்டிலிருந்து ஒரு கட்டளையை கையாள வேண்டும். இது நேரடி முறை கோரிக்கையாக அனுப்பப்படுகிறது.

### பணிகள் - நேரடி முறை கோரிக்கையை கையாளவும்

1. `connectIoTHub` செயல்பாட்டுக்கு முன் பின்வரும் குறியீட்டைச் சேர்க்கவும்:

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
  
   இந்த குறியீடு IoT Hub நூலகம் நேரடி முறை கோரிக்கையைப் பெறும் போது அழைக்கக்கூடிய ஒரு callback முறையை வரையறுக்கிறது. கோரப்படும் முறை `method_name` அளவுருவில் அனுப்பப்படும். இந்த செயல்பாடு சீரியல் போர்டுக்கு அழைக்கப்பட்ட முறையை அச்சிடுகிறது, பின்னர் முறை பெயரின் அடிப்படையில் ரிலேவை ஆன் அல்லது ஆஃப் செய்கிறது.

   > 💁 இதை ஒரு தனி நேரடி முறை கோரிக்கையாகவும் செயல்படுத்தலாம், ரிலேவின் விரும்பிய நிலையை ஒரு payload இல் அனுப்பி, முறை கோரிக்கையுடன் அனுப்பி, `payload` அளவுருவிலிருந்து கிடைக்கக்கூடியதாகவும் செய்யலாம்.

2. `directMethodCallback` செயல்பாட்டின் இறுதியில் பின்வரும் குறியீட்டைச் சேர்க்கவும்:

    ```cpp
    char resultBuff[16];
    sprintf(resultBuff, "{\"Result\":\"\"}");
    *response_size = strlen(resultBuff);
    *response = (unsigned char *)malloc(*response_size);
    memcpy(*response, resultBuff, *response_size);

    return IOTHUB_CLIENT_OK;
    ```
  
   நேரடி முறை கோரிக்கைகளுக்கு ஒரு பதில் தேவை, மேலும் பதில் இரண்டு பகுதிகளாக இருக்கும் - உரையாகவும், திரும்பும் குறியீடாகவும். இந்த குறியீடு பின்வரும் JSON ஆவணமாக ஒரு முடிவை உருவாக்கும்:

    ```JSON
    {
        "Result": ""
    }
    ```
  
   இது பின்னர் `response` அளவுருவில் நகலெடுக்கப்படும், மேலும் இந்த பதிலின் அளவு `response_size` அளவுருவில் அமைக்கப்படும். இந்த குறியீடு முறை சரியாக கையாளப்பட்டது என்பதை காட்ட `IOTHUB_CLIENT_OK` ஐ திருப்பும்.

3. இந்த callback ஐ இணைக்க, `connectIoTHub` செயல்பாட்டின் இறுதியில் பின்வரும் குறியீட்டைச் சேர்க்கவும்:

    ```cpp
    IoTHubClient_LL_SetDeviceMethodCallback(_device_ll_handle, directMethodCallback, NULL);
    ```
  
4. `loop` செயல்பாடு IoT Hub அனுப்பும் நிகழ்வுகளை செயலாக்க `IoTHubDeviceClient_LL_DoWork` செயல்பாட்டை அழைக்கும். இது `delay` காரணமாக ஒவ்வொரு 10 விநாடிகளுக்கும் மட்டுமே அழைக்கப்படுகிறது, அதாவது நேரடி முறைகள் ஒவ்வொரு 10 விநாடிகளுக்கும் மட்டுமே செயலாக்கப்படும். இதை மேலும் திறமையாகச் செய்ய, 10 விநாடி தாமதத்தை பல குறுகிய தாமதங்களாக செயல்படுத்தலாம், ஒவ்வொரு முறையும் `IoTHubDeviceClient_LL_DoWork` ஐ அழைக்கலாம். இதைச் செய்ய, பின்வரும் குறியீட்டை `loop` செயல்பாட்டின் மேல் சேர்க்கவும்:

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
  
   இந்த குறியீடு மீண்டும் மீண்டும் மடங்காமல் செயல்படுகிறது, ஒவ்வொரு முறையும் `IoTHubDeviceClient_LL_DoWork` ஐ அழைத்து, ஒவ்வொரு முறையும் 100ms தாமதமாகிறது. இது `delay_time` அளவுருவில் கொடுக்கப்பட்ட நேர அளவுக்கு தாமதிக்க தேவையான அளவுக்கு இதைச் செய்கிறது. இதன் பொருள், சாதனம் நேரடி முறை கோரிக்கைகளை செயலாக்க அதிகபட்சம் 100ms காத்திருக்கிறது.

5. `loop` செயல்பாட்டில், `IoTHubDeviceClient_LL_DoWork` அழைப்பை அகற்றி, `delay(10000)` அழைப்பை பின்வருமாறு மாற்றவும்:

    ```cpp
    work_delay(10000);
    ```
  
> 💁 இந்த குறியீட்டை [code/wio-terminal](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/wio-terminal) கோப்புறையில் காணலாம்.

😀 உங்கள் மண் ஈரப்பதம் சென்சார் திட்டம் உங்கள் IoT Hub உடன் இணைக்கப்பட்டுள்ளது!

---

**குறிப்பு**:  
இந்த ஆவணம் [Co-op Translator](https://github.com/Azure/co-op-translator) என்ற AI மொழிபெயர்ப்பு சேவையைப் பயன்படுத்தி மொழிபெயர்க்கப்பட்டுள்ளது. நாங்கள் துல்லியத்திற்காக முயற்சிக்கின்றோம், ஆனால் தானியங்கி மொழிபெயர்ப்புகளில் பிழைகள் அல்லது தவறான தகவல்கள் இருக்கக்கூடும் என்பதை கவனத்தில் கொள்ளவும். அதன் தாய்மொழியில் உள்ள மூல ஆவணம் அதிகாரப்பூர்வ ஆதாரமாக கருதப்பட வேண்டும். முக்கியமான தகவல்களுக்கு, தொழில்முறை மனித மொழிபெயர்ப்பு பரிந்துரைக்கப்படுகிறது. இந்த மொழிபெயர்ப்பைப் பயன்படுத்துவதால் ஏற்படும் எந்த தவறான புரிதல்கள் அல்லது தவறான விளக்கங்களுக்கு நாங்கள் பொறுப்பல்ல.