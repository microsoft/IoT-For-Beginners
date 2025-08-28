<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "28320305a35ea3bc59c41fe146a2e6ed",
  "translation_date": "2025-08-28T20:34:28+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/wio-terminal-connect-hub.md",
  "language_code": "en"
}
-->
# Connect your IoT device to the cloud - Wio Terminal

In this part of the lesson, you will connect your Wio Terminal to your IoT Hub to send telemetry data and receive commands.

## Connect your device to IoT Hub

The next step is to connect your device to IoT Hub.

### Task - Connect to IoT Hub

1. Open the `soil-moisture-sensor` project in VS Code.

1. Open the `platformio.ini` file. Remove the `knolleary/PubSubClient` library dependency. This library was used to connect to the public MQTT broker, but it is not required for connecting to IoT Hub.

1. Add the following library dependencies:

    ```ini
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    arduino-libraries/AzureIoTHub @ 1.6.0
    azure/AzureIoTUtility @ 1.6.1
    azure/AzureIoTProtocol_MQTT @ 1.6.0
    azure/AzureIoTProtocol_HTTP @ 1.6.0
    azure/AzureIoTSocket_WiFi @ 1.0.2
    ```

    The `Seeed Arduino RTC` library provides functionality to interact with the real-time clock in the Wio Terminal, which is used to keep track of time. The other libraries enable your IoT device to connect to IoT Hub.

1. Add the following line to the bottom of the `platformio.ini` file:

    ```ini
    build_flags =
        -DDONT_USE_UPLOADTOBLOB
    ```

    This sets a compiler flag required for compiling the Arduino IoT Hub code.

1. Open the `config.h` header file. Remove all the MQTT settings and add the following constant for the device connection string:

    ```cpp
    // IoT Hub settings
    const char *CONNECTION_STRING = "<connection string>";
    ```

    Replace `<connection string>` with the connection string for your device that you copied earlier.

1. The connection to IoT Hub uses a time-based token, which means the IoT device needs to know the current time. Unlike operating systems such as Windows, macOS, or Linux, microcontrollers don't automatically synchronize the current time over the Internet. Therefore, you need to add code to retrieve the current time from an [NTP](https://wikipedia.org/wiki/Network_Time_Protocol) server. Once the time is retrieved, it can be stored in the Wio Terminal's real-time clock, allowing the device to request the correct time later, as long as it doesn't lose power. Add a new file called `ntp.h` with the following code:

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

    The details of this code are beyond the scope of this lesson. It defines a function called `initTime` that retrieves the current time from an NTP server and sets the clock on the Wio Terminal.

1. Open the `main.cpp` file and remove all the MQTT-related code, including the `PubSubClient.h` header file, the declaration of the `PubSubClient` variable, the `reconnectMQTTClient` and `createMQTTClient` methods, and any calls to these variables and methods. This file should only contain code for connecting to WiFi, retrieving soil moisture data, and creating a JSON document with the data.

1. Add the following `#include` directives to the top of the `main.cpp` file to include header files for the IoT Hub libraries and for setting the time:

    ```cpp
    #include <AzureIoTHub.h>
    #include <AzureIoTProtocol_MQTT.h>
    #include <iothubtransportmqtt.h>
    #include "ntp.h"
    ```

1. Add the following call to the end of the `setup` function to set the current time:

    ```cpp
    initTime();
    ```

1. Add the following variable declaration to the top of the file, just below the include directives:

    ```cpp
    IOTHUB_DEVICE_CLIENT_LL_HANDLE _device_ll_handle;
    ```

    This declares an `IOTHUB_DEVICE_CLIENT_LL_HANDLE`, which is a handle for the connection to IoT Hub.

1. Below this, add the following code:

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

    This declares a callback function that will be triggered when the connection to IoT Hub changes status, such as connecting or disconnecting. The status will be printed to the serial port.

1. Below this, add a function to connect to IoT Hub:

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

    This code initializes the IoT Hub library, then creates a connection using the connection string from the `config.h` header file. The connection is based on MQTT. If the connection fails, the error will be printed to the serial port—check the connection string if you see this in the output. Finally, the connection status callback is set up.

1. Call this function in the `setup` function, below the call to `initTime`:

    ```cpp
    connectIoTHub();
    ```

1. Similar to the MQTT client, this code runs on a single thread and requires time to process messages sent by and to the hub. Add the following to the top of the `loop` function to handle this:

    ```cpp
    IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
    ```

1. Build and upload the code. You will see the connection status in the serial monitor:

    ```output
    Connecting to WiFi..
    Connected!
    Fetched NTP epoch time is: 1619983687
    Sending telemetry {"soil_moisture":391}
    The device client is connected to iothub
    ```

    In the output, you will see the NTP time being fetched, followed by the device client connecting. It may take a few seconds to connect, so you might see soil moisture data in the output while the device is still connecting.

    > 💁 You can convert the UNIX time from the NTP server into a more readable format using a website like [unixtimestamp.com](https://www.unixtimestamp.com).

## Send telemetry

Now that your device is connected, you can send telemetry data to IoT Hub instead of the MQTT broker.

### Task - Send telemetry

1. Add the following function above the `setup` function:

    ```cpp
    void sendTelemetry(const char *telemetry)
    {
        IOTHUB_MESSAGE_HANDLE message_handle = IoTHubMessage_CreateFromString(telemetry);
        IoTHubDeviceClient_LL_SendEventAsync(_device_ll_handle, message_handle, NULL, NULL);
        IoTHubMessage_Destroy(message_handle);
    }
    ```

    This code creates an IoT Hub message from a string passed as a parameter, sends it to the hub, and then cleans up the message object.

1. Call this function in the `loop` function, just after the line where telemetry data is sent to the serial port:

    ```cpp
    sendTelemetry(telemetry.c_str());
    ```

## Handle commands

Your device needs to handle commands from the server code to control the relay. These commands are sent as direct method requests.

### Task - Handle a direct method request

1. Add the following code before the `connectIoTHub` function:

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

    This code defines a callback function that the IoT Hub library can call when it receives a direct method request. The requested method is passed in the `method_name` parameter. This function prints the method name to the serial port and turns the relay on or off based on the method name.

    > 💁 This could also be implemented using a single direct method request, where the desired relay state is passed in a payload available from the `payload` parameter.

1. Add the following code to the end of the `directMethodCallback` function:

    ```cpp
    char resultBuff[16];
    sprintf(resultBuff, "{\"Result\":\"\"}");
    *response_size = strlen(resultBuff);
    *response = (unsigned char *)malloc(*response_size);
    memcpy(*response, resultBuff, *response_size);

    return IOTHUB_CLIENT_OK;
    ```

    Direct method requests require a response, which consists of two parts: a response message and a return code. This code creates a result in the form of the following JSON document:

    ```JSON
    {
        "Result": ""
    }
    ```

    The result is copied into the `response` parameter, and the size of the response is set in the `response_size` parameter. The function then returns `IOTHUB_CLIENT_OK` to indicate that the method was handled successfully.

1. Wire up the callback by adding the following line to the end of the `connectIoTHub` function:

    ```cpp
    IoTHubClient_LL_SetDeviceMethodCallback(_device_ll_handle, directMethodCallback, NULL);
    ```

1. The `loop` function calls the `IoTHubDeviceClient_LL_DoWork` function to process events sent by IoT Hub. Currently, this is only called every 10 seconds due to the `delay`, meaning direct methods are processed only every 10 seconds. To make this more efficient, the 10-second delay can be implemented as multiple shorter delays, calling `IoTHubDeviceClient_LL_DoWork` each time. Add the following code above the `loop` function:

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

    This code loops repeatedly, calling `IoTHubDeviceClient_LL_DoWork` and delaying for 100ms each time. It repeats this process as many times as needed to achieve the delay specified in the `delay_time` parameter. This ensures the device waits no longer than 100ms to process direct method requests.

1. In the `loop` function, remove the call to `IoTHubDeviceClient_LL_DoWork` and replace the `delay(10000)` call with the following line to use the new function:

    ```cpp
    work_delay(10000);
    ```

> 💁 You can find this code in the [code/wio-terminal](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/wio-terminal) folder.

😀 Your soil moisture sensor program is now connected to your IoT Hub!

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we aim for accuracy, please note that automated translations may include errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is advised. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.