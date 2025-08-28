<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "28320305a35ea3bc59c41fe146a2e6ed",
  "translation_date": "2025-08-28T15:04:27+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/wio-terminal-connect-hub.md",
  "language_code": "sr"
}
-->
# Повежите ваш IoT уређај са облаком - Wio Terminal

У овом делу лекције, повезаћете ваш Wio Terminal са IoT Hub-ом, како бисте слали телеметрију и примали команде.

## Повежите ваш уређај са IoT Hub-ом

Следећи корак је повезивање вашег уређаја са IoT Hub-ом.

### Задатак - повезивање са IoT Hub-ом

1. Отворите пројекат `soil-moisture-sensor` у VS Code-у.

1. Отворите датотеку `platformio.ini`. Уклоните зависност од библиотеке `knolleary/PubSubClient`. Ова библиотека је коришћена за повезивање са јавним MQTT брокером, али није потребна за повезивање са IoT Hub-ом.

1. Додајте следеће зависности од библиотека:

    ```ini
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    arduino-libraries/AzureIoTHub @ 1.6.0
    azure/AzureIoTUtility @ 1.6.1
    azure/AzureIoTProtocol_MQTT @ 1.6.0
    azure/AzureIoTProtocol_HTTP @ 1.6.0
    azure/AzureIoTSocket_WiFi @ 1.0.2
    ```

    Библиотека `Seeed Arduino RTC` пружа код за интеракцију са реалним временским сатом у Wio Terminal-у, који се користи за праћење времена. Преостале библиотеке омогућавају вашем IoT уређају да се повеже са IoT Hub-ом.

1. Додајте следеће на крај датотеке `platformio.ini`:

    ```ini
    build_flags =
        -DDONT_USE_UPLOADTOBLOB
    ```

    Ово поставља заставицу компајлера која је потребна приликом компајлирања кода за Arduino IoT Hub.

1. Отворите заглавну датотеку `config.h`. Уклоните сва подешавања за MQTT и додајте следећу константу за стринг за повезивање уређаја:

    ```cpp
    // IoT Hub settings
    const char *CONNECTION_STRING = "<connection string>";
    ```

    Замените `<connection string>` стрингом за повезивање вашег уређаја који сте раније копирали.

1. Повезивање са IoT Hub-ом користи токен заснован на времену. То значи да IoT уређај мора знати тренутно време. За разлику од оперативних система као што су Windows, macOS или Linux, микроконтролери не синхронизују аутоматски тренутно време преко интернета. То значи да морате додати код за добијање тренутног времена са [NTP](https://wikipedia.org/wiki/Network_Time_Protocol) сервера. Када се време преузме, може се чувати у реалном временском сату у Wio Terminal-у, омогућавајући да се исправно време затражи касније, под условом да уређај не изгуби напајање. Додајте нову датотеку под називом `ntp.h` са следећим кодом:

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

    Детаљи овог кода су ван оквира ове лекције. Он дефинише функцију `initTime` која добија тренутно време са NTP сервера и користи га за подешавање сата на Wio Terminal-у.

1. Отворите датотеку `main.cpp` и уклоните сав MQTT код, укључујући заглавну датотеку `PubSubClient.h`, декларацију променљиве `PubSubClient`, методе `reconnectMQTTClient` и `createMQTTClient`, као и све позиве ових променљивих и метода. Ова датотека треба да садржи само код за повезивање на WiFi, добијање влажности земљишта и креирање JSON документа са тим подацима.

1. Додајте следеће `#include` директиве на врх датотеке `main.cpp` како бисте укључили заглавне датотеке за IoT Hub библиотеке и за подешавање времена:

    ```cpp
    #include <AzureIoTHub.h>
    #include <AzureIoTProtocol_MQTT.h>
    #include <iothubtransportmqtt.h>
    #include "ntp.h"
    ```

1. Додајте следећи позив на крај функције `setup` како бисте подесили тренутно време:

    ```cpp
    initTime();
    ```

1. Додајте следећу декларацију променљиве на врх датотеке, одмах испод директива за укључивање:

    ```cpp
    IOTHUB_DEVICE_CLIENT_LL_HANDLE _device_ll_handle;
    ```

    Ово декларише `IOTHUB_DEVICE_CLIENT_LL_HANDLE`, ручицу за повезивање са IoT Hub-ом.

1. Испод овога, додајте следећи код:

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

    Ово декларише функцију повратног позива која ће бити позвана када се статус повезивања са IoT Hub-ом промени, као што је повезивање или прекид везе. Статус се шаље на серијски порт.

1. Испод овога, додајте функцију за повезивање са IoT Hub-ом:

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

    Овај код иницијализује IoT Hub библиотеку, а затим креира везу користећи стринг за повезивање у заглавној датотеци `config.h`. Ова веза се заснива на MQTT-у. Ако веза не успе, то се шаље на серијски порт - ако то видите у излазу, проверите стринг за повезивање. На крају се поставља повратни позив за статус везе.

1. Позовите ову функцију у функцији `setup` испод позива функције `initTime`:

    ```cpp
    connectIoTHub();
    ```

1. Као и код MQTT клијента, овај код ради на једном ниту, па му је потребно време за обраду порука које шаље хабу и које хаб шаље њему. Додајте следеће на врх функције `loop` како бисте то омогућили:

    ```cpp
    IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
    ```

1. Компилирајте и отпремите овај код. Видећете повезивање у серијском монитору:

    ```output
    Connecting to WiFi..
    Connected!
    Fetched NTP epoch time is: 1619983687
    Sending telemetry {"soil_moisture":391}
    The device client is connected to iothub
    ```

    У излазу можете видети како се преузима NTP време, а затим како се клијент уређаја повезује. Може потрајати неколико секунди да се повежете, па можете видети влажност земљишта у излазу док се уређај повезује.

    > 💁 Можете конвертовати UNIX време за NTP у читљивију верзију користећи веб сајт као што је [unixtimestamp.com](https://www.unixtimestamp.com)

## Слање телеметрије

Сада када је ваш уређај повезан, можете слати телеметрију IoT Hub-у уместо MQTT брокеру.

### Задатак - слање телеметрије

1. Додајте следећу функцију изнад функције `setup`:

    ```cpp
    void sendTelemetry(const char *telemetry)
    {
        IOTHUB_MESSAGE_HANDLE message_handle = IoTHubMessage_CreateFromString(telemetry);
        IoTHubDeviceClient_LL_SendEventAsync(_device_ll_handle, message_handle, NULL, NULL);
        IoTHubMessage_Destroy(message_handle);
    }
    ```

    Овај код креира IoT Hub поруку из стринга који се прослеђује као параметар, шаље је хабу, а затим чисти објекат поруке.

1. Позовите овај код у функцији `loop`, одмах након линије где се телеметрија шаље на серијски порт:

    ```cpp
    sendTelemetry(telemetry.c_str());
    ```

## Обрада команди

Ваш уређај треба да обради команду са серверског кода за контролу релеја. Ово се шаље као захтев за директну методу.

## Задатак - обрада захтева за директну методу

1. Додајте следећи код пре функције `connectIoTHub`:

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

    Овај код дефинише функцију повратног позива коју IoT Hub библиотека може позвати када прими захтев за директну методу. Метода која се захтева шаље се у параметру `method_name`. Ова функција исписује позвану методу на серијски порт, а затим укључује или искључује релеј у зависности од имена методе.

    > 💁 Ово би могло бити имплементирано и у једној директној методи, прослеђујући жељено стање релеја у payload који се може проследити са захтевом за методу и доступан је из параметра `payload`.

1. Додајте следећи код на крај функције `directMethodCallback`:

    ```cpp
    char resultBuff[16];
    sprintf(resultBuff, "{\"Result\":\"\"}");
    *response_size = strlen(resultBuff);
    *response = (unsigned char *)malloc(*response_size);
    memcpy(*response, resultBuff, *response_size);

    return IOTHUB_CLIENT_OK;
    ```

    Захтеви за директне методе захтевају одговор, а одговор је у два дела - одговор као текст и код повратка. Овај код ће креирати резултат као следећи JSON документ:

    ```JSON
    {
        "Result": ""
    }
    ```

    Ово се затим копира у параметар `response`, а величина овог одговора се поставља у параметар `response_size`. Овај код затим враћа `IOTHUB_CLIENT_OK` како би показао да је метода успешно обрађена.

1. Повежите повратни позив додавањем следећег на крај функције `connectIoTHub`:

    ```cpp
    IoTHubClient_LL_SetDeviceMethodCallback(_device_ll_handle, directMethodCallback, NULL);
    ```

1. Функција `loop` ће позвати функцију `IoTHubDeviceClient_LL_DoWork` како би обрадила догађаје које шаље IoT Hub. Ово се позива само сваких 10 секунди због `delay`, што значи да се директне методе обрађују само сваких 10 секунди. Да би ово било ефикасније, 10-секундно кашњење може бити имплементирано као много краћих кашњења, позивајући `IoTHubDeviceClient_LL_DoWork` сваки пут. Да бисте то урадили, додајте следећи код изнад функције `loop`:

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

    Овај код ће се понављати, позивајући `IoTHubDeviceClient_LL_DoWork` и одлажући за 100ms сваки пут. То ће радити онолико пута колико је потребно да се одложи за време дато у параметру `delay_time`. То значи да уређај чека највише 100ms да обради захтеве за директне методе.

1. У функцији `loop`, уклоните позив функције `IoTHubDeviceClient_LL_DoWork`, и замените позив `delay(10000)` следећим како бисте позвали ову нову функцију:

    ```cpp
    work_delay(10000);
    ```

> 💁 Овај код можете пронаћи у фолдеру [code/wio-terminal](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/wio-terminal).

😀 Ваш програм за сензор влажности земљишта је повезан са вашим IoT Hub-ом!

---

**Одрицање од одговорности**:  
Овај документ је преведен коришћењем услуге за превођење помоћу вештачке интелигенције [Co-op Translator](https://github.com/Azure/co-op-translator). Иако се трудимо да обезбедимо тачност, молимо вас да имате у виду да аутоматски преводи могу садржати грешке или нетачности. Оригинални документ на његовом изворном језику треба сматрати ауторитативним извором. За критичне информације препоручује се професионални превод од стране људи. Не преузимамо одговорност за било каква погрешна тумачења или неспоразуме који могу настати услед коришћења овог превода.