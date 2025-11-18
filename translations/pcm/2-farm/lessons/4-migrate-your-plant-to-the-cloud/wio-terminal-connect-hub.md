<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "28320305a35ea3bc59c41fe146a2e6ed",
  "translation_date": "2025-11-18T19:34:32+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/wio-terminal-connect-hub.md",
  "language_code": "pcm"
}
-->
# Connect your IoT device to di cloud - Wio Terminal

For dis part of di lesson, you go connect your Wio Terminal to your IoT Hub, so e fit dey send telemetry and receive commands.

## Connect your device to IoT Hub

Di next step na to connect your device to IoT Hub.

### Task - connect to IoT Hub

1. Open di `soil-moisture-sensor` project for VS Code.

1. Open di `platformio.ini` file. Comot di `knolleary/PubSubClient` library dependency. Dem bin use am to connect to di public MQTT broker, but e no dey needed to connect to IoT Hub.

1. Add di following library dependencies:

    ```ini
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    arduino-libraries/AzureIoTHub @ 1.6.0
    azure/AzureIoTUtility @ 1.6.1
    azure/AzureIoTProtocol_MQTT @ 1.6.0
    azure/AzureIoTProtocol_HTTP @ 1.6.0
    azure/AzureIoTSocket_WiFi @ 1.0.2
    ```

   Di `Seeed Arduino RTC` library dey provide code to interact with di real-time clock wey dey Wio Terminal, wey dem dey use track time. Di remaining libraries go allow your IoT device connect to IoT Hub.

1. Add di following to di bottom of di `platformio.ini` file:

    ```ini
    build_flags =
        -DDONT_USE_UPLOADTOBLOB
    ```

   Dis one go set compiler flag wey dem need when dem dey compile di Arduino IoT Hub code.

1. Open di `config.h` header file. Comot all di MQTT settings and add di following constant for di device connection string:

    ```cpp
    // IoT Hub settings
    const char *CONNECTION_STRING = "<connection string>";
    ```

   Replace `<connection string>` with di connection string for your device wey you copy before.

1. Di connection to IoT Hub dey use time-based token. Dis mean say di IoT device need sabi di current time. Unlike operating systems like Windows, macOS or Linux, microcontrollers no dey automatically synchronize di current time over di Internet. Dis mean say you go need add code to get di current time from one [NTP](https://wikipedia.org/wiki/Network_Time_Protocol) server. Once di time don dey retrieved, e fit dey stored for di real-time clock wey dey Wio Terminal, so di correct time fit dey requested later, as long as di device no lose power. Add new file wey you go call `ntp.h` with di following code:

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

   Di details of dis code no dey inside di scope of dis lesson. E dey define one function wey dem call `initTime` wey go get di current time from one NTP server and use am set di clock wey dey Wio Terminal.

1. Open di `main.cpp` file and comot all di MQTT code, including di `PubSubClient.h` header file, di declaration of di `PubSubClient` variable, di `reconnectMQTTClient` and `createMQTTClient` methods, and any calls to dis variables and methods. Dis file suppose only contain code to connect to WiFi, get di soil moisture and create JSON document with am.

1. Add di following `#include` directives to di top of di `main.cpp` file to include header files for di IoT Hub libraries, and for setting di time:

    ```cpp
    #include <AzureIoTHub.h>
    #include <AzureIoTProtocol_MQTT.h>
    #include <iothubtransportmqtt.h>
    #include "ntp.h"
    ```

1. Add di following call to di end of di `setup` function to set di current time:

    ```cpp
    initTime();
    ```

1. Add di following variable declaration to di top of di file, just below di include directives:

    ```cpp
    IOTHUB_DEVICE_CLIENT_LL_HANDLE _device_ll_handle;
    ```

   Dis one dey declare `IOTHUB_DEVICE_CLIENT_LL_HANDLE`, wey be handle to di connection to di IoT Hub.

1. Below dis one, add di following code:

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

   Dis one dey declare callback function wey dem go call when di connection to di IoT Hub change status, like when e connect or disconnect. Di status go dey sent to di serial port.

1. Below dis one, add function to connect to IoT Hub:

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

   Dis code dey initialize di IoT Hub library code, then e go create connection using di connection string wey dey `config.h` header file. Dis connection dey based on MQTT. If di connection fail, e go send am to di serial port - if you see dis for di output, check di connection string. Finally, di connection status callback go dey set up.

1. Call dis function for di `setup` function below di call to `initTime`:

    ```cpp
    connectIoTHub();
    ```

1. Just like di MQTT client, dis code dey run for one single thread so e need time to process messages wey di hub dey send, and messages wey di hub dey receive. Add di following to di top of di `loop` function to do dis:

    ```cpp
    IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
    ```

1. Build and upload dis code. You go see di connection for di serial monitor:

    ```output
    Connecting to WiFi..
    Connected!
    Fetched NTP epoch time is: 1619983687
    Sending telemetry {"soil_moisture":391}
    The device client is connected to iothub
    ```

   For di output, you go see di NTP time wey dem dey fetch, followed by di device client wey dey connect. E fit take few seconds to connect, so you fit see di soil moisture for di output while di device dey connect.

   > 💁 You fit convert di UNIX time for di NTP to di one wey you fit read well well using website like [unixtimestamp.com](https://www.unixtimestamp.com)

## Send telemetry

Now wey your device don connect, you fit send telemetry to di IoT Hub instead of di MQTT broker.

### Task - send telemetry

1. Add di following function above di `setup` function:

    ```cpp
    void sendTelemetry(const char *telemetry)
    {
        IOTHUB_MESSAGE_HANDLE message_handle = IoTHubMessage_CreateFromString(telemetry);
        IoTHubDeviceClient_LL_SendEventAsync(_device_ll_handle, message_handle, NULL, NULL);
        IoTHubMessage_Destroy(message_handle);
    }
    ```

   Dis code dey create IoT Hub message from string wey dem pass as parameter, send am to di hub, then e go clean di message object.

1. Call dis code for di `loop` function, just after di line wey di telemetry dey sent to di serial port:

    ```cpp
    sendTelemetry(telemetry.c_str());
    ```

## Handle commands

Your device need handle command from di server code to control di relay. Dis one dey sent as direct method request.

## Task - handle direct method request

1. Add di following code before di `connectIoTHub` function:

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

   Dis code dey define callback method wey di IoT Hub library fit call when e receive direct method request. Di method wey dem request dey sent for di `method_name` parameter. Dis function go print di method wey dem call to di serial port, then e go turn di relay on or off depending on di method name.

   > 💁 You fit also implement dis one for one single direct method request, pass di desired state of di relay for payload wey dem fit pass with di method request and dey available from di `payload` parameter.

1. Add di following code to di end of di `directMethodCallback` function:

    ```cpp
    char resultBuff[16];
    sprintf(resultBuff, "{\"Result\":\"\"}");
    *response_size = strlen(resultBuff);
    *response = (unsigned char *)malloc(*response_size);
    memcpy(*response, resultBuff, *response_size);

    return IOTHUB_CLIENT_OK;
    ```

   Direct method requests dey need response, and di response dey two parts - response as text, and return code. Dis code go create result as di following JSON document:

    ```JSON
    {
        "Result": ""
    }
    ```

   Dis one go then copy am into di `response` parameter, and di size of dis response go dey set for di `response_size` parameter. Dis code go then return `IOTHUB_CLIENT_OK` to show say di method handle well.

1. Wire up di callback by adding di following to di end of di `connectIoTHub` function:

    ```cpp
    IoTHubClient_LL_SetDeviceMethodCallback(_device_ll_handle, directMethodCallback, NULL);
    ```

1. Di `loop` function go call di `IoTHubDeviceClient_LL_DoWork` function to process events wey IoT Hub dey send. Dis one dey only called every 10 seconds because of di `delay`, meaning direct methods dey only process every 10 seconds. To make dis one more efficient, di 10 seconds delay fit dey implemented as many shorter delays, dey call `IoTHubDeviceClient_LL_DoWork` each time. To do dis, add di following code above di `loop` function:

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

   Dis code go dey loop repeatedly, dey call `IoTHubDeviceClient_LL_DoWork` and dey delay for 100ms each time. E go do dis as many times as dem need to delay for di amount of time wey dem give for di `delay_time` parameter. Dis mean say di device dey wait at most 100ms to process direct method requests.

1. For di `loop` function, comot di call to `IoTHubDeviceClient_LL_DoWork`, and replace di `delay(10000)` call with di following to call dis new function:

    ```cpp
    work_delay(10000);
    ```

> 💁 You fit find dis code for di [code/wio-terminal](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/wio-terminal) folder.

😀 Your soil moisture sensor program don connect to your IoT Hub!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Disclaimer**:  
Dis dokyument don use AI transle-shon service [Co-op Translator](https://github.com/Azure/co-op-translator) do di transle-shon. Even as we dey try make am correct, abeg sabi say transle-shon wey machine do fit get mistake or no dey accurate. Di original dokyument for im native language na di one wey you go take as di correct source. For important mata, e good make professional human transle-shon dey use. We no go fit take blame for any misunderstanding or wrong interpretation wey fit happen because you use dis transle-shon.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->