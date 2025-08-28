<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "28320305a35ea3bc59c41fe146a2e6ed",
  "translation_date": "2025-08-27T22:05:53+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/wio-terminal-connect-hub.md",
  "language_code": "tl"
}
-->
# Ikonekta ang iyong IoT device sa cloud - Wio Terminal

Sa bahaging ito ng aralin, ikokonekta mo ang iyong Wio Terminal sa iyong IoT Hub upang magpadala ng telemetry at tumanggap ng mga utos.

## Ikonekta ang iyong device sa IoT Hub

Ang susunod na hakbang ay ikonekta ang iyong device sa IoT Hub.

### Gawain - ikonekta sa IoT Hub

1. Buksan ang proyekto na `soil-moisture-sensor` sa VS Code.

1. Buksan ang file na `platformio.ini`. Tanggalin ang dependency ng library na `knolleary/PubSubClient`. Ginamit ito upang kumonekta sa pampublikong MQTT broker, ngunit hindi na ito kailangan upang kumonekta sa IoT Hub.

1. Idagdag ang mga sumusunod na dependency ng library:

    ```ini
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    arduino-libraries/AzureIoTHub @ 1.6.0
    azure/AzureIoTUtility @ 1.6.1
    azure/AzureIoTProtocol_MQTT @ 1.6.0
    azure/AzureIoTProtocol_HTTP @ 1.6.0
    azure/AzureIoTSocket_WiFi @ 1.0.2
    ```

    Ang library na `Seeed Arduino RTC` ay nagbibigay ng code upang makipag-ugnayan sa real-time clock sa Wio Terminal, na ginagamit upang subaybayan ang oras. Ang natitirang mga library ay nagpapahintulot sa iyong IoT device na kumonekta sa IoT Hub.

1. Idagdag ang sumusunod sa ibaba ng file na `platformio.ini`:

    ```ini
    build_flags =
        -DDONT_USE_UPLOADTOBLOB
    ```

    Itinatakda nito ang isang compiler flag na kinakailangan kapag kino-compile ang Arduino IoT Hub code.

1. Buksan ang header file na `config.h`. Tanggalin ang lahat ng mga setting ng MQTT at idagdag ang sumusunod na constant para sa device connection string:

    ```cpp
    // IoT Hub settings
    const char *CONNECTION_STRING = "<connection string>";
    ```

    Palitan ang `<connection string>` ng connection string para sa iyong device na kinopya mo kanina.

1. Ang koneksyon sa IoT Hub ay gumagamit ng time-based token. Nangangahulugan ito na ang IoT device ay kailangang malaman ang kasalukuyang oras. Hindi tulad ng mga operating system tulad ng Windows, macOS, o Linux, ang mga microcontroller ay hindi awtomatikong nagsi-synchronize ng kasalukuyang oras sa Internet. Nangangahulugan ito na kailangan mong magdagdag ng code upang makuha ang kasalukuyang oras mula sa isang [NTP](https://wikipedia.org/wiki/Network_Time_Protocol) server. Kapag nakuha na ang oras, maaari itong itago sa isang real-time clock sa Wio Terminal, na nagpapahintulot na hilingin ang tamang oras sa ibang pagkakataon, basta't hindi mawalan ng kuryente ang device. Magdagdag ng bagong file na tinatawag na `ntp.h` na may sumusunod na code:

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

    Ang mga detalye ng code na ito ay labas sa saklaw ng aralin. Nagde-define ito ng isang function na tinatawag na `initTime` na kumukuha ng kasalukuyang oras mula sa isang NTP server at ginagamit ito upang itakda ang orasan sa Wio Terminal.

1. Buksan ang file na `main.cpp` at tanggalin ang lahat ng code ng MQTT, kabilang ang header file na `PubSubClient.h`, ang deklarasyon ng variable na `PubSubClient`, ang mga method na `reconnectMQTTClient` at `createMQTTClient`, at anumang tawag sa mga variable at method na ito. Ang file na ito ay dapat lamang maglaman ng code upang kumonekta sa WiFi, makuha ang soil moisture, at lumikha ng JSON document mula rito.

1. Idagdag ang sumusunod na `#include` directives sa itaas ng file na `main.cpp` upang isama ang mga header file para sa IoT Hub libraries, at para sa pagtatakda ng oras:

    ```cpp
    #include <AzureIoTHub.h>
    #include <AzureIoTProtocol_MQTT.h>
    #include <iothubtransportmqtt.h>
    #include "ntp.h"
    ```

1. Idagdag ang sumusunod na tawag sa dulo ng function na `setup` upang itakda ang kasalukuyang oras:

    ```cpp
    initTime();
    ```

1. Idagdag ang sumusunod na deklarasyon ng variable sa itaas ng file, sa ibaba lamang ng mga include directives:

    ```cpp
    IOTHUB_DEVICE_CLIENT_LL_HANDLE _device_ll_handle;
    ```

    Nagde-declare ito ng `IOTHUB_DEVICE_CLIENT_LL_HANDLE`, isang handle sa koneksyon sa IoT Hub.

1. Sa ibaba nito, idagdag ang sumusunod na code:

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

    Nagde-declare ito ng callback function na tatawagin kapag nagbago ang status ng koneksyon sa IoT Hub, tulad ng pagkonekta o pagdiskonekta. Ang status ay ipinapadala sa serial port.

1. Sa ibaba nito, magdagdag ng function upang kumonekta sa IoT Hub:

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

    Ang code na ito ay nag-i-initialize ng IoT Hub library code, pagkatapos ay lumilikha ng koneksyon gamit ang connection string sa header file na `config.h`. Ang koneksyon na ito ay batay sa MQTT. Kung nabigo ang koneksyon, ipinapadala ito sa serial port - kung makikita mo ito sa output, suriin ang connection string. Sa wakas, ang callback ng status ng koneksyon ay na-set up.

1. Tawagin ang function na ito sa function na `setup` sa ibaba ng tawag sa `initTime`:

    ```cpp
    connectIoTHub();
    ```

1. Tulad ng sa MQTT client, ang code na ito ay tumatakbo sa isang solong thread kaya nangangailangan ng oras upang iproseso ang mga mensaheng ipinadala ng hub, at ipinadala sa hub. Idagdag ang sumusunod sa itaas ng function na `loop` upang gawin ito:

    ```cpp
    IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
    ```

1. I-build at i-upload ang code na ito. Makikita mo ang koneksyon sa serial monitor:

    ```output
    Connecting to WiFi..
    Connected!
    Fetched NTP epoch time is: 1619983687
    Sending telemetry {"soil_moisture":391}
    The device client is connected to iothub
    ```

    Sa output, makikita mo ang NTP time na kinukuha, kasunod ng device client na kumokonekta. Maaaring tumagal ng ilang segundo upang kumonekta, kaya maaaring makita mo ang soil moisture sa output habang kumokonekta ang device.

    > 💁 Maaari mong i-convert ang UNIX time para sa NTP sa mas nababasang bersyon gamit ang isang website tulad ng [unixtimestamp.com](https://www.unixtimestamp.com)

## Magpadala ng telemetry

Ngayon na ang iyong device ay nakakonekta, maaari kang magpadala ng telemetry sa IoT Hub sa halip na sa MQTT broker.

### Gawain - magpadala ng telemetry

1. Idagdag ang sumusunod na function sa itaas ng function na `setup`:

    ```cpp
    void sendTelemetry(const char *telemetry)
    {
        IOTHUB_MESSAGE_HANDLE message_handle = IoTHubMessage_CreateFromString(telemetry);
        IoTHubDeviceClient_LL_SendEventAsync(_device_ll_handle, message_handle, NULL, NULL);
        IoTHubMessage_Destroy(message_handle);
    }
    ```

    Ang code na ito ay lumilikha ng IoT Hub message mula sa isang string na ipinasa bilang parameter, ipinapadala ito sa hub, pagkatapos ay nililinis ang message object.

1. Tawagin ang code na ito sa function na `loop`, pagkatapos lamang ng linya kung saan ipinapadala ang telemetry sa serial port:

    ```cpp
    sendTelemetry(telemetry.c_str());
    ```

## Mag-handle ng mga utos

Ang iyong device ay kailangang mag-handle ng utos mula sa server code upang kontrolin ang relay. Ito ay ipinapadala bilang isang direktang method request.

## Gawain - mag-handle ng direktang method request

1. Idagdag ang sumusunod na code bago ang function na `connectIoTHub`:

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

    Ang code na ito ay nagde-define ng callback method na maaaring tawagin ng IoT Hub library kapag nakatanggap ito ng direktang method request. Ang method na hiniling ay ipinapadala sa parameter na `method_name`. Ang function na ito ay nagpi-print ng method na tinawag sa serial port, pagkatapos ay binubuksan o pinapatay ang relay depende sa pangalan ng method.

    > 💁 Maaari rin itong ipatupad sa isang solong direktang method request, na ipinapasa ang nais na estado ng relay sa isang payload na maaaring ipasa sa method request at magagamit mula sa parameter na `payload`.

1. Idagdag ang sumusunod na code sa dulo ng function na `directMethodCallback`:

    ```cpp
    char resultBuff[16];
    sprintf(resultBuff, "{\"Result\":\"\"}");
    *response_size = strlen(resultBuff);
    *response = (unsigned char *)malloc(*response_size);
    memcpy(*response, resultBuff, *response_size);

    return IOTHUB_CLIENT_OK;
    ```

    Ang direktang method requests ay nangangailangan ng response, at ang response ay nasa dalawang bahagi - isang response bilang text, at isang return code. Ang code na ito ay lilikha ng resulta bilang sumusunod na JSON document:

    ```JSON
    {
        "Result": ""
    }
    ```

    Ito ay pagkatapos kinokopya sa parameter na `response`, at ang laki ng response na ito ay itinatakda sa parameter na `response_size`. Ang code na ito ay pagkatapos nagre-return ng `IOTHUB_CLIENT_OK` upang ipakita na ang method ay na-handle nang tama.

1. I-wire up ang callback sa pamamagitan ng pagdaragdag ng sumusunod sa dulo ng function na `connectIoTHub`:

    ```cpp
    IoTHubClient_LL_SetDeviceMethodCallback(_device_ll_handle, directMethodCallback, NULL);
    ```

1. Ang function na `loop` ay tatawag sa function na `IoTHubDeviceClient_LL_DoWork` upang iproseso ang mga event na ipinadala ng IoT Hub. Ito ay tinatawag lamang tuwing 10 segundo dahil sa `delay`, nangangahulugan na ang direktang methods ay napoproseso lamang tuwing 10 segundo. Upang gawing mas epektibo ito, ang 10 segundong delay ay maaaring ipatupad bilang maraming mas maikling delay, na tinatawag ang `IoTHubDeviceClient_LL_DoWork` sa bawat pagkakataon. Upang gawin ito, idagdag ang sumusunod na code sa itaas ng function na `loop`:

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

    Ang code na ito ay mag-loop nang paulit-ulit, tinatawag ang `IoTHubDeviceClient_LL_DoWork` at nagde-delay ng 100ms sa bawat pagkakataon. Gagawin nito ito nang maraming beses hangga't kinakailangan upang mag-delay para sa dami ng oras na ibinigay sa parameter na `delay_time`. Nangangahulugan ito na ang device ay naghihintay ng pinakamataas na 100ms upang iproseso ang direktang method requests.

1. Sa function na `loop`, tanggalin ang tawag sa `IoTHubDeviceClient_LL_DoWork`, at palitan ang tawag na `delay(10000)` ng sumusunod upang tawagin ang bagong function na ito:

    ```cpp
    work_delay(10000);
    ```

> 💁 Makikita mo ang code na ito sa [code/wio-terminal](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/wio-terminal) folder.

😀 Ang iyong soil moisture sensor program ay nakakonekta na sa iyong IoT Hub!

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na maaaring magmula sa paggamit ng pagsasaling ito.