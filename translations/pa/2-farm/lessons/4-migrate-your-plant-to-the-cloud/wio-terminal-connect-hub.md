<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "28320305a35ea3bc59c41fe146a2e6ed",
  "translation_date": "2025-08-27T12:05:42+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/wio-terminal-connect-hub.md",
  "language_code": "pa"
}
-->
# ਆਪਣਾ IoT ਡਿਵਾਈਸ ਕਲਾਉਡ ਨਾਲ ਜੁੜੋ - Wio Terminal

ਇਸ ਪਾਠ ਦੇ ਇਸ ਹਿੱਸੇ ਵਿੱਚ, ਤੁਸੀਂ ਆਪਣੇ Wio Terminal ਨੂੰ ਆਪਣੇ IoT Hub ਨਾਲ ਜੋੜੋਗੇ, ਤਾਂ ਜੋ ਟੈਲੀਮੇਟਰੀ ਭੇਜ ਸਕੋ ਅਤੇ ਕਮਾਂਡ ਪ੍ਰਾਪਤ ਕਰ ਸਕੋ।

## ਆਪਣੇ ਡਿਵਾਈਸ ਨੂੰ IoT Hub ਨਾਲ ਜੋੜੋ

ਅਗਲਾ ਕਦਮ ਆਪਣੇ ਡਿਵਾਈਸ ਨੂੰ IoT Hub ਨਾਲ ਜੋੜਨਾ ਹੈ।

### ਟਾਸਕ - IoT Hub ਨਾਲ ਜੁੜੋ

1. VS Code ਵਿੱਚ `soil-moisture-sensor` ਪ੍ਰੋਜੈਕਟ ਖੋਲ੍ਹੋ।

1. `platformio.ini` ਫਾਈਲ ਖੋਲ੍ਹੋ। `knolleary/PubSubClient` ਲਾਇਬ੍ਰੇਰੀ ਡਿਪੈਂਡੈਂਸੀ ਹਟਾਓ। ਇਹ ਪਬਲਿਕ MQTT ਬ੍ਰੋਕਰ ਨਾਲ ਜੁੜਨ ਲਈ ਵਰਤੀ ਗਈ ਸੀ, ਅਤੇ IoT Hub ਨਾਲ ਜੁੜਨ ਲਈ ਲੋੜੀਂਦੀ ਨਹੀਂ ਹੈ।

1. ਹੇਠਾਂ ਦਿੱਤੀ ਲਾਇਬ੍ਰੇਰੀ ਡਿਪੈਂਡੈਂਸੀਜ਼ ਸ਼ਾਮਲ ਕਰੋ:

    ```ini
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    arduino-libraries/AzureIoTHub @ 1.6.0
    azure/AzureIoTUtility @ 1.6.1
    azure/AzureIoTProtocol_MQTT @ 1.6.0
    azure/AzureIoTProtocol_HTTP @ 1.6.0
    azure/AzureIoTSocket_WiFi @ 1.0.2
    ```

    `Seeed Arduino RTC` ਲਾਇਬ੍ਰੇਰੀ Wio Terminal ਵਿੱਚ ਰੀਅਲ-ਟਾਈਮ ਘੜੀ ਨਾਲ ਇੰਟਰੈਕਟ ਕਰਨ ਲਈ ਕੋਡ ਪ੍ਰਦਾਨ ਕਰਦੀ ਹੈ, ਜੋ ਸਮਾਂ ਟ੍ਰੈਕ ਕਰਨ ਲਈ ਵਰਤੀ ਜਾਂਦੀ ਹੈ। ਬਾਕੀ ਲਾਇਬ੍ਰੇਰੀਆਂ ਤੁਹਾਡੇ IoT ਡਿਵਾਈਸ ਨੂੰ IoT Hub ਨਾਲ ਜੁੜਨ ਦੀ ਆਗਿਆ ਦਿੰਦੀ ਹਨ।

1. `platformio.ini` ਫਾਈਲ ਦੇ ਤਲ ਵਿੱਚ ਹੇਠਾਂ ਦਿੱਤਾ ਸ਼ਾਮਲ ਕਰੋ:

    ```ini
    build_flags =
        -DDONT_USE_UPLOADTOBLOB
    ```

    ਇਹ ਇੱਕ ਕੰਪਾਇਲਰ ਫਲੈਗ ਸੈਟ ਕਰਦਾ ਹੈ ਜੋ Arduino IoT Hub ਕੋਡ ਨੂੰ ਕੰਪਾਇਲ ਕਰਨ ਸਮੇਂ ਲੋੜੀਂਦਾ ਹੈ।

1. `config.h` ਹੈਡਰ ਫਾਈਲ ਖੋਲ੍ਹੋ। ਸਾਰੇ MQTT ਸੈਟਿੰਗਾਂ ਹਟਾਓ ਅਤੇ ਡਿਵਾਈਸ ਕਨੈਕਸ਼ਨ ਸਟ੍ਰਿੰਗ ਲਈ ਹੇਠਾਂ ਦਿੱਤਾ ਕਾਂਸਟੈਂਟ ਸ਼ਾਮਲ ਕਰੋ:

    ```cpp
    // IoT Hub settings
    const char *CONNECTION_STRING = "<connection string>";
    ```

    `<connection string>` ਨੂੰ ਆਪਣੇ ਡਿਵਾਈਸ ਲਈ ਕਾਪੀ ਕੀਤੀ ਕਨੈਕਸ਼ਨ ਸਟ੍ਰਿੰਗ ਨਾਲ ਬਦਲੋ।

1. IoT Hub ਨਾਲ ਕਨੈਕਸ਼ਨ ਟਾਈਮ-ਬੇਸਡ ਟੋਕਨ ਵਰਤਦਾ ਹੈ। ਇਸਦਾ ਮਤਲਬ ਹੈ ਕਿ IoT ਡਿਵਾਈਸ ਨੂੰ ਮੌਜੂਦਾ ਸਮਾਂ ਪਤਾ ਹੋਣਾ ਚਾਹੀਦਾ ਹੈ। Windows, macOS ਜਾਂ Linux ਵਰਗੇ ਓਪਰੇਟਿੰਗ ਸਿਸਟਮਾਂ ਦੇ ਵਿਰੁੱਧ, ਮਾਈਕਰੋਕੰਟਰੋਲਰ ਇੰਟਰਨੈਟ ਰਾਹੀਂ ਮੌਜੂਦਾ ਸਮਾਂ ਆਪਣੇ ਆਪ ਸਿੰਕਰੋਨਾਈਜ਼ ਨਹੀਂ ਕਰਦੇ। ਇਸਦਾ ਮਤਲਬ ਹੈ ਕਿ ਤੁਹਾਨੂੰ [NTP](https://wikipedia.org/wiki/Network_Time_Protocol) ਸਰਵਰ ਤੋਂ ਮੌਜੂਦਾ ਸਮਾਂ ਪ੍ਰਾਪਤ ਕਰਨ ਲਈ ਕੋਡ ਸ਼ਾਮਲ ਕਰਨ ਦੀ ਲੋੜ ਹੋਵੇਗੀ। ਜਦੋਂ ਸਮਾਂ ਪ੍ਰਾਪਤ ਕੀਤਾ ਜਾਂਦਾ ਹੈ, ਇਸਨੂੰ Wio Terminal ਵਿੱਚ ਰੀਅਲ-ਟਾਈਮ ਘੜੀ ਵਿੱਚ ਸਟੋਰ ਕੀਤਾ ਜਾ ਸਕਦਾ ਹੈ, ਜਿਸ ਨਾਲ ਸਹੀ ਸਮਾਂ ਬਾਅਦ ਵਿੱਚ ਮੰਗਿਆ ਜਾ ਸਕਦਾ ਹੈ, ਜੇਕਰ ਡਿਵਾਈਸ ਦੀ ਪਾਵਰ ਨਾ ਜਾਵੇ। `ntp.h` ਨਾਮ ਦੀ ਨਵੀਂ ਫਾਈਲ ਬਣਾਓ ਅਤੇ ਹੇਠਾਂ ਦਿੱਤਾ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ:

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

    ਇਸ ਕੋਡ ਦੇ ਵੇਰਵੇ ਇਸ ਪਾਠ ਦੇ ਦਾਇਰੇ ਤੋਂ ਬਾਹਰ ਹਨ। ਇਹ ਇੱਕ ਫੰਕਸ਼ਨ `initTime` ਨੂੰ ਪਰਿਭਾਸ਼ਿਤ ਕਰਦਾ ਹੈ ਜੋ NTP ਸਰਵਰ ਤੋਂ ਮੌਜੂਦਾ ਸਮਾਂ ਪ੍ਰਾਪਤ ਕਰਦਾ ਹੈ ਅਤੇ ਇਸਨੂੰ Wio Terminal ਦੀ ਘੜੀ 'ਤੇ ਸੈਟ ਕਰਨ ਲਈ ਵਰਤਦਾ ਹੈ।

1. `main.cpp` ਫਾਈਲ ਖੋਲ੍ਹੋ ਅਤੇ ਸਾਰੇ MQTT ਕੋਡ ਹਟਾਓ, ਜਿਸ ਵਿੱਚ `PubSubClient.h` ਹੈਡਰ ਫਾਈਲ, `PubSubClient` ਵੈਰੀਏਬਲ ਦੀ ਘੋਸ਼ਣਾ, `reconnectMQTTClient` ਅਤੇ `createMQTTClient` ਮੈਥਡ, ਅਤੇ ਇਨ੍ਹਾਂ ਵੈਰੀਏਬਲਾਂ ਅਤੇ ਮੈਥਡਾਂ ਨੂੰ ਕਾਲ ਕਰਨ ਵਾਲੇ ਕੋਈ ਵੀ ਕੋਡ ਸ਼ਾਮਲ ਹਨ। ਇਸ ਫਾਈਲ ਵਿੱਚ ਸਿਰਫ WiFi ਨਾਲ ਜੁੜਨ, ਮਿੱਟੀ ਦੀ ਨਮੀ ਪ੍ਰਾਪਤ ਕਰਨ ਅਤੇ ਇਸ ਨਾਲ JSON ਡੌਕੂਮੈਂਟ ਬਣਾਉਣ ਲਈ ਕੋਡ ਹੋਣਾ ਚਾਹੀਦਾ ਹੈ।

1. `main.cpp` ਫਾਈਲ ਦੇ ਉੱਪਰ ਹੇਠਾਂ ਦਿੱਤੇ `#include` ਡਾਇਰੈਕਟਿਵਜ਼ ਸ਼ਾਮਲ ਕਰੋ, ਤਾਂ ਜੋ IoT Hub ਲਾਇਬ੍ਰੇਰੀਆਂ ਅਤੇ ਸਮਾਂ ਸੈਟ ਕਰਨ ਲਈ ਹੈਡਰ ਫਾਈਲਾਂ ਸ਼ਾਮਲ ਕੀਤੀਆਂ ਜਾ ਸਕਣ:

    ```cpp
    #include <AzureIoTHub.h>
    #include <AzureIoTProtocol_MQTT.h>
    #include <iothubtransportmqtt.h>
    #include "ntp.h"
    ```

1. `setup` ਫੰਕਸ਼ਨ ਦੇ ਅੰਤ ਵਿੱਚ ਹੇਠਾਂ ਦਿੱਤਾ ਕਾਲ ਸ਼ਾਮਲ ਕਰੋ, ਤਾਂ ਜੋ ਮੌਜੂਦਾ ਸਮਾਂ ਸੈਟ ਕੀਤਾ ਜਾ ਸਕੇ:

    ```cpp
    initTime();
    ```

1. ਫਾਈਲ ਦੇ ਉੱਪਰ, `include` ਡਾਇਰੈਕਟਿਵਜ਼ ਦੇ ਥੱਲੇ ਹੇਠਾਂ ਦਿੱਤੀ ਵੈਰੀਏਬਲ ਘੋਸ਼ਣਾ ਸ਼ਾਮਲ ਕਰੋ:

    ```cpp
    IOTHUB_DEVICE_CLIENT_LL_HANDLE _device_ll_handle;
    ```

    ਇਹ ਇੱਕ `IOTHUB_DEVICE_CLIENT_LL_HANDLE` ਘੋਸ਼ਿਤ ਕਰਦਾ ਹੈ, ਜੋ IoT Hub ਨਾਲ ਕਨੈਕਸ਼ਨ ਲਈ ਇੱਕ ਹੈਂਡਲ ਹੈ।

1. ਇਸ ਦੇ ਥੱਲੇ ਹੇਠਾਂ ਦਿੱਤਾ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ:

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

    ਇਹ ਇੱਕ ਕਾਲਬੈਕ ਫੰਕਸ਼ਨ ਘੋਸ਼ਿਤ ਕਰਦਾ ਹੈ ਜੋ IoT Hub ਨਾਲ ਕਨੈਕਸ਼ਨ ਦੀ ਸਥਿਤੀ ਬਦਲਣ 'ਤੇ ਕਾਲ ਕੀਤਾ ਜਾਂਦਾ ਹੈ, ਜਿਵੇਂ ਕਿ ਕਨੈਕਟ ਹੋਣਾ ਜਾਂ ਡਿਸਕਨੈਕਟ ਹੋਣਾ। ਸਥਿਤੀ ਸੀਰੀਅਲ ਪੋਰਟ 'ਤੇ ਭੇਜੀ ਜਾਂਦੀ ਹੈ।

1. ਇਸ ਦੇ ਥੱਲੇ IoT Hub ਨਾਲ ਕਨੈਕਸ਼ਨ ਕਰਨ ਲਈ ਇੱਕ ਫੰਕਸ਼ਨ ਸ਼ਾਮਲ ਕਰੋ:

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

    ਇਹ IoT Hub ਲਾਇਬ੍ਰੇਰੀ ਕੋਡ ਨੂੰ ਸ਼ੁਰੂ ਕਰਦਾ ਹੈ, ਫਿਰ `config.h` ਹੈਡਰ ਫਾਈਲ ਵਿੱਚ ਕਨੈਕਸ਼ਨ ਸਟ੍ਰਿੰਗ ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਇੱਕ ਕਨੈਕਸ਼ਨ ਬਣਾਉਂਦਾ ਹੈ। ਇਹ ਕਨੈਕਸ਼ਨ MQTT 'ਤੇ ਅਧਾਰਿਤ ਹੈ। ਜੇਕਰ ਕਨੈਕਸ਼ਨ ਫੇਲ ਹੋ ਜਾਂਦਾ ਹੈ, ਤਾਂ ਇਹ ਸੀਰੀਅਲ ਪੋਰਟ 'ਤੇ ਭੇਜਿਆ ਜਾਂਦਾ ਹੈ - ਜੇਕਰ ਤੁਸੀਂ ਇਹ ਆਉਟਪੁੱਟ ਵਿੱਚ ਵੇਖਦੇ ਹੋ, ਤਾਂ ਕਨੈਕਸ਼ਨ ਸਟ੍ਰਿੰਗ ਦੀ ਜਾਂਚ ਕਰੋ। ਅੰਤ ਵਿੱਚ, ਕਨੈਕਸ਼ਨ ਸਥਿਤੀ ਕਾਲਬੈਕ ਸੈਟ ਕੀਤਾ ਜਾਂਦਾ ਹੈ।

1. ਇਸ ਫੰਕਸ਼ਨ ਨੂੰ `setup` ਫੰਕਸ਼ਨ ਵਿੱਚ `initTime` ਕਾਲ ਦੇ ਥੱਲੇ ਕਾਲ ਕਰੋ:

    ```cpp
    connectIoTHub();
    ```

1. MQTT ਕਲਾਇੰਟ ਦੀ ਤਰ੍ਹਾਂ, ਇਹ ਕੋਡ ਇੱਕ ਸਿੰਗਲ ਥ੍ਰੈਡ 'ਤੇ ਚਲਦਾ ਹੈ, ਇਸ ਲਈ ਹੱਬ ਦੁਆਰਾ ਭੇਜੇ ਗਏ ਸੁਨੇਹਿਆਂ ਨੂੰ ਪ੍ਰਕਿਰਿਆ ਕਰਨ ਲਈ ਸਮਾਂ ਦੀ ਲੋੜ ਹੁੰਦੀ ਹੈ, ਅਤੇ ਹੱਬ ਨੂੰ ਭੇਜੇ ਗਏ ਸੁਨੇਹਿਆਂ ਨੂੰ ਵੀ। `loop` ਫੰਕਸ਼ਨ ਦੇ ਉੱਪਰ ਹੇਠਾਂ ਦਿੱਤਾ ਸ਼ਾਮਲ ਕਰੋ:

    ```cpp
    IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
    ```

1. ਇਸ ਕੋਡ ਨੂੰ ਬਣਾਓ ਅਤੇ ਅਪਲੋਡ ਕਰੋ। ਤੁਸੀਂ ਸੀਰੀਅਲ ਮਾਨੀਟਰ ਵਿੱਚ ਕਨੈਕਸ਼ਨ ਵੇਖੋਗੇ:

    ```output
    Connecting to WiFi..
    Connected!
    Fetched NTP epoch time is: 1619983687
    Sending telemetry {"soil_moisture":391}
    The device client is connected to iothub
    ```

    ਆਉਟਪੁੱਟ ਵਿੱਚ ਤੁਸੀਂ NTP ਸਮਾਂ ਪ੍ਰਾਪਤ ਹੋਣ ਦੇ ਬਾਅਦ ਡਿਵਾਈਸ ਕਲਾਇੰਟ ਨੂੰ ਕਨੈਕਟ ਹੁੰਦੇ ਵੇਖ ਸਕਦੇ ਹੋ। ਕਨੈਕਟ ਕਰਨ ਵਿੱਚ ਕੁਝ ਸਕਿੰਟ ਲੱਗ ਸਕਦੇ ਹਨ, ਇਸ ਲਈ ਤੁਸੀਂ ਡਿਵਾਈਸ ਕਨੈਕਟ ਹੋਣ ਦੌਰਾਨ ਆਉਟਪੁੱਟ ਵਿੱਚ ਮਿੱਟੀ ਦੀ ਨਮੀ ਵੇਖ ਸਕਦੇ ਹੋ।

    > 💁 ਤੁਸੀਂ NTP ਲਈ UNIX ਸਮਾਂ ਨੂੰ ਇੱਕ ਵੱਧ ਪੜ੍ਹਨਯੋਗ ਵਰਜਨ ਵਿੱਚ [unixtimestamp.com](https://www.unixtimestamp.com) ਵਰਗੇ ਵੈਬਸਾਈਟ ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਬਦਲ ਸਕਦੇ ਹੋ।

## ਟੈਲੀਮੇਟਰੀ ਭੇਜੋ

ਹੁਣ ਤੁਹਾਡਾ ਡਿਵਾਈਸ ਜੁੜਿਆ ਹੋਇਆ ਹੈ, ਤੁਸੀਂ MQTT ਬ੍ਰੋਕਰ ਦੀ ਬਜਾਏ IoT Hub ਨੂੰ ਟੈਲੀਮੇਟਰੀ ਭੇਜ ਸਕਦੇ ਹੋ।

### ਟਾਸਕ - ਟੈਲੀਮੇਟਰੀ ਭੇਜੋ

1. `setup` ਫੰਕਸ਼ਨ ਦੇ ਉੱਪਰ ਹੇਠਾਂ ਦਿੱਤਾ ਫੰਕਸ਼ਨ ਸ਼ਾਮਲ ਕਰੋ:

    ```cpp
    void sendTelemetry(const char *telemetry)
    {
        IOTHUB_MESSAGE_HANDLE message_handle = IoTHubMessage_CreateFromString(telemetry);
        IoTHubDeviceClient_LL_SendEventAsync(_device_ll_handle, message_handle, NULL, NULL);
        IoTHubMessage_Destroy(message_handle);
    }
    ```

    ਇਹ ਕੋਡ ਇੱਕ ਸਟ੍ਰਿੰਗ ਤੋਂ IoT Hub ਸੁਨੇਹਾ ਬਣਾਉਂਦਾ ਹੈ ਜੋ ਪੈਰਾਮੀਟਰ ਵਜੋਂ ਪਾਸ ਕੀਤਾ ਜਾਂਦਾ ਹੈ, ਇਸਨੂੰ ਹੱਬ ਨੂੰ ਭੇਜਦਾ ਹੈ, ਫਿਰ ਸੁਨੇਹਾ ਆਬਜੈਕਟ ਨੂੰ ਸਾਫ ਕਰਦਾ ਹੈ।

1. ਇਸ ਕੋਡ ਨੂੰ `loop` ਫੰਕਸ਼ਨ ਵਿੱਚ ਕਾਲ ਕਰੋ, ਉਸ ਲਾਈਨ ਦੇ ਥੱਲੇ ਜਿੱਥੇ ਟੈਲੀਮੇਟਰੀ ਸੀਰੀਅਲ ਪੋਰਟ 'ਤੇ ਭੇਜੀ ਜਾਂਦੀ ਹੈ:

    ```cpp
    sendTelemetry(telemetry.c_str());
    ```

## ਕਮਾਂਡ ਸੰਭਾਲੋ

ਤੁਹਾਡੇ ਡਿਵਾਈਸ ਨੂੰ ਸਰਵਰ ਕੋਡ ਤੋਂ ਰੀਲੇ ਨੂੰ ਕੰਟਰੋਲ ਕਰਨ ਲਈ ਇੱਕ ਕਮਾਂਡ ਸੰਭਾਲਣ ਦੀ ਲੋੜ ਹੈ। ਇਹ ਇੱਕ ਡਾਇਰੈਕਟ ਮੈਥਡ ਰਿਕਵੈਸਟ ਵਜੋਂ ਭੇਜਿਆ ਜਾਂਦਾ ਹੈ।

## ਟਾਸਕ - ਡਾਇਰੈਕਟ ਮੈਥਡ ਰਿਕਵੈਸਟ ਸੰਭਾਲੋ

1. `connectIoTHub` ਫੰਕਸ਼ਨ ਤੋਂ ਪਹਿਲਾਂ ਹੇਠਾਂ ਦਿੱਤਾ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ:

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

    ਇਹ ਕੋਡ ਇੱਕ ਕਾਲਬੈਕ ਮੈਥਡ ਪਰਿਭਾਸ਼ਿਤ ਕਰਦਾ ਹੈ ਜੋ IoT Hub ਲਾਇਬ੍ਰੇਰੀ ਨੂੰ ਕਾਲ ਕਰ ਸਕਦਾ ਹੈ ਜਦੋਂ ਇਹ ਇੱਕ ਡਾਇਰੈਕਟ ਮੈਥਡ ਰਿਕਵੈਸਟ ਪ੍ਰਾਪਤ ਕਰਦਾ ਹੈ। ਮੈਥਡ ਜੋ ਰਿਕਵੈਸਟ ਕੀਤਾ ਜਾਂਦਾ ਹੈ `method_name` ਪੈਰਾਮੀਟਰ ਵਿੱਚ ਭੇਜਿਆ ਜਾਂਦਾ ਹੈ। ਇਹ ਫੰਕਸ਼ਨ ਸੀਰੀਅਲ ਪੋਰਟ 'ਤੇ ਕਾਲ ਕੀਤੇ ਗਏ ਮੈਥਡ ਨੂੰ ਪ੍ਰਿੰਟ ਕਰਦਾ ਹੈ, ਫਿਰ ਮੈਥਡ ਨਾਮ ਦੇ ਅਨੁਸਾਰ ਰੀਲੇ ਨੂੰ ਚਾਲੂ ਜਾਂ ਬੰਦ ਕਰਦਾ ਹੈ।

    > 💁 ਇਹ ਇੱਕ ਸਿੰਗਲ ਡਾਇਰੈਕਟ ਮੈਥਡ ਰਿਕਵੈਸਟ ਵਿੱਚ ਵੀ ਲਾਗੂ ਕੀਤਾ ਜਾ ਸਕਦਾ ਹੈ, ਜਿਸ ਵਿੱਚ ਰੀਲੇ ਦੀ ਚਾਹੀਦੀ ਸਥਿਤੀ ਨੂੰ ਪੇਲੋਡ ਵਿੱਚ ਪਾਸ ਕੀਤਾ ਜਾ ਸਕਦਾ ਹੈ ਜੋ ਮੈਥਡ ਰਿਕਵੈਸਟ ਨਾਲ ਪਾਸ ਕੀਤਾ ਜਾ ਸਕਦਾ ਹੈ ਅਤੇ `payload` ਪੈਰਾਮੀਟਰ ਤੋਂ ਉਪਲਬਧ ਹੋ ਸਕਦਾ ਹੈ।

1. `directMethodCallback` ਫੰਕਸ਼ਨ ਦੇ ਅੰਤ ਵਿੱਚ ਹੇਠਾਂ ਦਿੱਤਾ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ:

    ```cpp
    char resultBuff[16];
    sprintf(resultBuff, "{\"Result\":\"\"}");
    *response_size = strlen(resultBuff);
    *response = (unsigned char *)malloc(*response_size);
    memcpy(*response, resultBuff, *response_size);

    return IOTHUB_CLIENT_OK;
    ```

    ਡਾਇਰੈਕਟ ਮੈਥਡ ਰਿਕਵੈਸਟਾਂ ਨੂੰ ਇੱਕ ਜਵਾਬ ਦੀ ਲੋੜ ਹੁੰਦੀ ਹੈ, ਅਤੇ ਜਵਾਬ ਦੋ ਹਿੱਸਿਆਂ ਵਿੱਚ ਹੁੰਦਾ ਹੈ - ਇੱਕ ਟੈਕਸਟ ਵਜੋਂ ਜਵਾਬ, ਅਤੇ ਇੱਕ ਰਿਟਰਨ ਕੋਡ। ਇਹ ਕੋਡ ਹੇਠਾਂ ਦਿੱਤੇ JSON ਡੌਕੂਮੈਂਟ ਵਜੋਂ ਇੱਕ ਨਤੀਜਾ ਬਣਾਏਗਾ:

    ```JSON
    {
        "Result": ""
    }
    ```

    ਇਹ ਫਿਰ `response` ਪੈਰਾਮੀਟਰ ਵਿੱਚ ਕਾਪੀ ਕੀਤਾ ਜਾਂਦਾ ਹੈ, ਅਤੇ ਇਸ ਜਵਾਬ ਦਾ ਆਕਾਰ `response_size` ਪੈਰਾਮੀਟਰ ਵਿੱਚ ਸੈਟ ਕੀਤਾ ਜਾਂਦਾ ਹੈ। ਇਹ ਕੋਡ ਫਿਰ `IOTHUB_CLIENT_OK` ਰਿਟਰਨ ਕਰਦਾ ਹੈ, ਇਹ ਦਿਖਾਉਣ ਲਈ ਕਿ ਮੈਥਡ ਸਹੀ ਤਰੀਕੇ ਨਾਲ ਸੰਭਾਲਿਆ ਗਿਆ ਸੀ।

1. ਕਾਲਬੈਕ ਨੂੰ ਵਾਇਰ ਕਰਨ ਲਈ `connectIoTHub` ਫੰਕਸ਼ਨ ਦੇ ਅੰਤ ਵਿੱਚ ਹੇਠਾਂ ਦਿੱਤਾ ਸ਼ਾਮਲ ਕਰੋ:

    ```cpp
    IoTHubClient_LL_SetDeviceMethodCallback(_device_ll_handle, directMethodCallback, NULL);
    ```

1. `loop` ਫੰਕਸ਼ਨ `IoTHubDeviceClient_LL_DoWork` ਫੰਕਸ਼ਨ ਨੂੰ IoT Hub ਦੁਆਰਾ ਭੇਜੇ ਗਏ ਇਵੈਂਟਸ ਨੂੰ ਪ੍ਰਕਿਰਿਆ ਕਰਨ ਲਈ ਕਾਲ ਕਰੇਗਾ। ਇਹ ਸਿਰਫ 10 ਸਕਿੰਟ ਦੇ `delay` ਕਾਰਨ ਕਾਲ ਕੀਤਾ ਜਾਂਦਾ ਹੈ, ਜਿਸਦਾ ਮਤਲਬ ਹੈ ਕਿ ਡਾਇਰੈਕਟ ਮੈਥਡ ਸਿਰਫ ਹਰ 10 ਸਕਿੰਟ ਵਿੱਚ ਪ੍ਰਕਿਰਿਆ ਕੀਤੇ ਜਾਂਦੇ ਹਨ। ਇਸਨੂੰ ਵਧੇਰੇ ਕੁਸ਼ਲ ਬਣਾਉਣ ਲਈ, 10 ਸਕਿੰਟ ਦੇ `delay` ਨੂੰ ਕਈ ਛੋਟੇ `delay` ਵਜੋਂ ਲਾਗੂ ਕੀਤਾ ਜਾ ਸਕਦਾ ਹੈ, ਹਰ ਵਾਰ `IoTHubDeviceClient_LL_DoWork` ਨੂੰ ਕਾਲ ਕਰਦੇ ਹੋਏ। ਇਸਨੂੰ ਕਰਨ ਲਈ, `loop` ਫੰਕਸ਼ਨ ਦੇ ਉੱਪਰ ਹੇਠਾਂ ਦਿੱਤਾ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ:

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

    ਇਹ ਕੋਡ ਵਾਰ-ਵਾਰ ਲੂਪ ਕਰੇਗਾ, `IoTHubDeviceClient_LL_DoWork` ਨੂੰ ਕਾਲ ਕਰੇਗਾ ਅਤੇ ਹਰ ਵਾਰ 100ms ਲਈ `delay` ਕਰੇਗਾ। ਇਹ ਇਸਨੂੰ ਜਿੰਨਾ ਸਮਾਂ ਲੱਗੇਗਾ `delay_time` ਪੈਰਾਮੀਟਰ ਵਿੱਚ ਦਿੱਤੇ ਸਮੇਂ ਲਈ `delay` ਕਰਨ ਲਈ। ਇਸਦਾ ਮਤਲਬ ਹੈ ਕਿ ਡਿਵਾਈਸ ਡਾਇਰੈਕਟ ਮੈਥਡ ਰਿਕਵੈਸਟਾਂ ਨੂੰ ਪ੍ਰਕਿਰਿਆ ਕਰਨ ਲਈ ਵੱਧ ਤੋਂ ਵੱਧ 100ms ਦੀ ਉਡੀਕ ਕਰ ਰਿਹਾ ਹੈ।

1. `loop` ਫੰਕਸ਼ਨ ਵਿੱਚ, `IoTHubDeviceClient_LL_DoWork` ਨੂੰ ਕਾਲ ਕਰਨ ਵਾਲੀ ਲਾਈਨ ਹਟਾਓ, ਅਤੇ `delay(10000)` ਕਾਲ ਨੂੰ ਹੇਠਾਂ ਦਿੱਤੇ ਨਾਲ ਬਦਲੋ, ਤਾਂ ਜੋ ਇਹ ਨਵਾਂ ਫੰਕਸ਼ਨ ਕਾਲ ਕੀਤਾ ਜਾ ਸਕੇ:

    ```cpp
    work_delay(10000);
    ```

> 💁 ਤੁਸੀਂ ਇਹ ਕੋਡ [code/wio-terminal](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/wio-terminal) ਫੋਲਡਰ ਵਿੱਚ ਪਾ ਸਕਦੇ ਹੋ।

😀 ਤੁਹਾਡਾ ਮਿੱਟੀ ਦੀ ਨਮੀ ਸੈਂਸਰ ਪ੍ਰੋਗਰਾਮ ਤੁਹਾਡੇ IoT Hub ਨਾਲ ਜੁੜਿਆ ਹੋਇਆ ਹੈ!

---

**ਅਸਵੀਕਰਤਾ**:  
ਇਹ ਦਸਤਾਵੇਜ਼ AI ਅਨੁਵਾਦ ਸੇਵਾ [Co-op Translator](https://github.com/Azure/co-op-translator) ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਅਨੁਵਾਦ ਕੀਤਾ ਗਿਆ ਹੈ। ਜਦੋਂ ਕਿ ਅਸੀਂ ਸਹੀ ਹੋਣ ਦੀ ਕੋਸ਼ਿਸ਼ ਕਰਦੇ ਹਾਂ, ਕਿਰਪਾ ਕਰਕੇ ਧਿਆਨ ਦਿਓ ਕਿ ਸਵੈਚਾਲਿਤ ਅਨੁਵਾਦਾਂ ਵਿੱਚ ਗਲਤੀਆਂ ਜਾਂ ਅਸੁਚੱਜੇਪਣ ਹੋ ਸਕਦੇ ਹਨ। ਮੂਲ ਦਸਤਾਵੇਜ਼, ਜੋ ਇਸਦੀ ਮੂਲ ਭਾਸ਼ਾ ਵਿੱਚ ਹੈ, ਨੂੰ ਅਧਿਕਾਰਤ ਸਰੋਤ ਮੰਨਿਆ ਜਾਣਾ ਚਾਹੀਦਾ ਹੈ। ਮਹੱਤਵਪੂਰਨ ਜਾਣਕਾਰੀ ਲਈ, ਪੇਸ਼ੇਵਰ ਮਨੁੱਖੀ ਅਨੁਵਾਦ ਦੀ ਸਿਫਾਰਸ਼ ਕੀਤੀ ਜਾਂਦੀ ਹੈ। ਇਸ ਅਨੁਵਾਦ ਦੀ ਵਰਤੋਂ ਤੋਂ ਪੈਦਾ ਹੋਣ ਵਾਲੇ ਕਿਸੇ ਵੀ ਗਲਤਫਹਿਮੀ ਜਾਂ ਗਲਤ ਵਿਆਖਿਆ ਲਈ ਅਸੀਂ ਜ਼ਿੰਮੇਵਾਰ ਨਹੀਂ ਹਾਂ।