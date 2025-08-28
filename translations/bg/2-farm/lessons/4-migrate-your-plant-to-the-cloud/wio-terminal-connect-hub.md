<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "28320305a35ea3bc59c41fe146a2e6ed",
  "translation_date": "2025-08-28T11:26:36+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/wio-terminal-connect-hub.md",
  "language_code": "bg"
}
-->
# Свържете вашето IoT устройство с облака - Wio Terminal

В тази част на урока ще свържете вашия Wio Terminal с вашия IoT Hub, за да изпращате телеметрия и да получавате команди.

## Свържете устройството си с IoT Hub

Следващата стъпка е да свържете устройството си с IoT Hub.

### Задача - свързване с IoT Hub

1. Отворете проекта `soil-moisture-sensor` във VS Code.

1. Отворете файла `platformio.ini`. Премахнете зависимостта от библиотеката `knolleary/PubSubClient`. Тя се използваше за свързване с публичен MQTT брокер и не е необходима за свързване с IoT Hub.

1. Добавете следните зависимости към библиотеката:

    ```ini
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    arduino-libraries/AzureIoTHub @ 1.6.0
    azure/AzureIoTUtility @ 1.6.1
    azure/AzureIoTProtocol_MQTT @ 1.6.0
    azure/AzureIoTProtocol_HTTP @ 1.6.0
    azure/AzureIoTSocket_WiFi @ 1.0.2
    ```

    Библиотеката `Seeed Arduino RTC` предоставя код за взаимодействие с реално-времевия часовник в Wio Terminal, който се използва за проследяване на времето. Останалите библиотеки позволяват вашето IoT устройство да се свърже с IoT Hub.

1. Добавете следното в края на файла `platformio.ini`:

    ```ini
    build_flags =
        -DDONT_USE_UPLOADTOBLOB
    ```

    Това задава флаг за компилатора, който е необходим при компилиране на кода за Arduino IoT Hub.

1. Отворете хедър файла `config.h`. Премахнете всички настройки за MQTT и добавете следната константа за връзковия низ на устройството:

    ```cpp
    // IoT Hub settings
    const char *CONNECTION_STRING = "<connection string>";
    ```

    Заменете `<connection string>` с връзковия низ за вашето устройство, който копирахте по-рано.

1. Свързването с IoT Hub използва токен, базиран на време. Това означава, че IoT устройството трябва да знае текущото време. За разлика от операционни системи като Windows, macOS или Linux, микроконтролерите не синхронизират автоматично текущото време през интернет. Това означава, че трябва да добавите код за получаване на текущото време от [NTP](https://wikipedia.org/wiki/Network_Time_Protocol) сървър. След като времето бъде получено, то може да се съхрани в реално-времевия часовник на Wio Terminal, което позволява правилното време да бъде заявено по-късно, при условие че устройството не загуби захранване. Добавете нов файл, наречен `ntp.h`, със следния код:

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

    Подробностите за този код са извън обхвата на този урок. Той дефинира функция, наречена `initTime`, която получава текущото време от NTP сървър и го използва за настройка на часовника на Wio Terminal.

1. Отворете файла `main.cpp` и премахнете целия код за MQTT, включително хедър файла `PubSubClient.h`, декларацията на променливата `PubSubClient`, методите `reconnectMQTTClient` и `createMQTTClient`, както и всички извиквания към тези променливи и методи. Този файл трябва да съдържа само код за свързване с WiFi, получаване на данни за влажността на почвата и създаване на JSON документ с тях.

1. Добавете следните директиви `#include` в началото на файла `main.cpp`, за да включите хедър файлове за библиотеките на IoT Hub и за настройка на времето:

    ```cpp
    #include <AzureIoTHub.h>
    #include <AzureIoTProtocol_MQTT.h>
    #include <iothubtransportmqtt.h>
    #include "ntp.h"
    ```

1. Добавете следното извикване в края на функцията `setup`, за да зададете текущото време:

    ```cpp
    initTime();
    ```

1. Добавете следната декларация на променлива в началото на файла, точно под директивите за включване:

    ```cpp
    IOTHUB_DEVICE_CLIENT_LL_HANDLE _device_ll_handle;
    ```

    Това декларира `IOTHUB_DEVICE_CLIENT_LL_HANDLE`, манипулатор за връзка с IoT Hub.

1. Под това добавете следния код:

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

    Това декларира функция за обратен повик, която ще бъде извикана, когато връзката с IoT Hub промени състоянието си, като например свързване или прекъсване. Състоянието се изпраща към серийния порт.

1. Под това добавете функция за свързване с IoT Hub:

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

    Този код инициализира библиотечния код на IoT Hub, след което създава връзка, използвайки връзковия низ в хедър файла `config.h`. Тази връзка е базирана на MQTT. Ако връзката се провали, това се изпраща към серийния порт - ако видите това в изхода, проверете връзковия низ. Накрая се настройва функцията за обратен повик за състоянието на връзката.

1. Извикайте тази функция във функцията `setup` под извикването на `initTime`:

    ```cpp
    connectIoTHub();
    ```

1. Подобно на MQTT клиента, този код работи на един поток, така че се нуждае от време за обработка на съобщенията, изпратени от хъба и към хъба. Добавете следното в началото на функцията `loop`, за да направите това:

    ```cpp
    IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
    ```

1. Компилирайте и качете този код. Ще видите връзката в серийния монитор:

    ```output
    Connecting to WiFi..
    Connected!
    Fetched NTP epoch time is: 1619983687
    Sending telemetry {"soil_moisture":391}
    The device client is connected to iothub
    ```

    В изхода можете да видите как се извлича времето от NTP, последвано от свързването на клиентското устройство. Може да отнеме няколко секунди за свързване, така че може да видите данните за влажността на почвата в изхода, докато устройството се свързва.

    > 💁 Можете да конвертирате UNIX времето от NTP в по-четим формат, използвайки уебсайт като [unixtimestamp.com](https://www.unixtimestamp.com)

## Изпращане на телеметрия

Сега, когато устройството ви е свързано, можете да изпращате телеметрия към IoT Hub вместо към MQTT брокера.

### Задача - изпращане на телеметрия

1. Добавете следната функция над функцията `setup`:

    ```cpp
    void sendTelemetry(const char *telemetry)
    {
        IOTHUB_MESSAGE_HANDLE message_handle = IoTHubMessage_CreateFromString(telemetry);
        IoTHubDeviceClient_LL_SendEventAsync(_device_ll_handle, message_handle, NULL, NULL);
        IoTHubMessage_Destroy(message_handle);
    }
    ```

    Този код създава съобщение за IoT Hub от низ, предаден като параметър, изпраща го към хъба и след това освобождава обекта на съобщението.

1. Извикайте този код във функцията `loop`, точно след реда, където телеметрията се изпраща към серийния порт:

    ```cpp
    sendTelemetry(telemetry.c_str());
    ```

## Обработка на команди

Вашето устройство трябва да обработва команда от сървърния код за управление на релето. Това се изпраща като заявка за директен метод.

## Задача - обработка на заявка за директен метод

1. Добавете следния код преди функцията `connectIoTHub`:

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

    Този код дефинира функция за обратен повик, която библиотеката на IoT Hub може да извика, когато получи заявка за директен метод. Методът, който се заявява, се изпраща в параметъра `method_name`. Тази функция отпечатва извикания метод към серийния порт, след което включва или изключва релето в зависимост от името на метода.

    > 💁 Това може също да бъде реализирано в един директен метод, като се предаде желаното състояние на релето в полезен товар, който може да бъде предаден със заявката за метод и достъпен от параметъра `payload`.

1. Добавете следния код в края на функцията `directMethodCallback`:

    ```cpp
    char resultBuff[16];
    sprintf(resultBuff, "{\"Result\":\"\"}");
    *response_size = strlen(resultBuff);
    *response = (unsigned char *)malloc(*response_size);
    memcpy(*response, resultBuff, *response_size);

    return IOTHUB_CLIENT_OK;
    ```

    Заявките за директни методи изискват отговор, който се състои от две части - отговор като текст и код за връщане. Този код ще създаде резултат като следния JSON документ:

    ```JSON
    {
        "Result": ""
    }
    ```

    Това след това се копира в параметъра `response`, а размерът на този отговор се задава в параметъра `response_size`. Този код след това връща `IOTHUB_CLIENT_OK`, за да покаже, че методът е обработен правилно.

1. Свържете функцията за обратен повик, като добавите следното в края на функцията `connectIoTHub`:

    ```cpp
    IoTHubClient_LL_SetDeviceMethodCallback(_device_ll_handle, directMethodCallback, NULL);
    ```

1. Функцията `loop` ще извиква функцията `IoTHubDeviceClient_LL_DoWork`, за да обработва събития, изпратени от IoT Hub. Това се извиква само на всеки 10 секунди заради `delay`, което означава, че директните методи се обработват само на всеки 10 секунди. За да направите това по-ефективно, 10-секундното забавяне може да бъде реализирано като множество по-кратки забавяния, като се извиква `IoTHubDeviceClient_LL_DoWork` всеки път. За да направите това, добавете следния код над функцията `loop`:

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

    Този код ще се изпълнява многократно, като извиква `IoTHubDeviceClient_LL_DoWork` и забавя за 100ms всеки път. Това ще се прави толкова пъти, колкото е необходимо, за да се забави за времето, дадено в параметъра `delay_time`. Това означава, че устройството чака най-много 100ms, за да обработи заявки за директни методи.

1. Във функцията `loop` премахнете извикването на `IoTHubDeviceClient_LL_DoWork` и заменете извикването на `delay(10000)` със следното, за да извикате тази нова функция:

    ```cpp
    work_delay(10000);
    ```

> 💁 Можете да намерите този код в папката [code/wio-terminal](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/wio-terminal).

😀 Вашата програма за сензор за влажност на почвата е свързана с вашия IoT Hub!

---

**Отказ от отговорност**:  
Този документ е преведен с помощта на AI услуга за превод [Co-op Translator](https://github.com/Azure/co-op-translator). Въпреки че се стремим към точност, моля, имайте предвид, че автоматизираните преводи може да съдържат грешки или неточности. Оригиналният документ на неговия роден език трябва да се счита за авторитетен източник. За критична информация се препоръчва професионален човешки превод. Ние не носим отговорност за недоразумения или погрешни интерпретации, произтичащи от използването на този превод.