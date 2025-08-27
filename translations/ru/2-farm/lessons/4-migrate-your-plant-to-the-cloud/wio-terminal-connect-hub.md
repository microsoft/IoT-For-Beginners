<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "28320305a35ea3bc59c41fe146a2e6ed",
  "translation_date": "2025-08-26T23:00:30+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/wio-terminal-connect-hub.md",
  "language_code": "ru"
}
-->
# Подключите ваше IoT-устройство к облаку - Wio Terminal

В этой части урока вы подключите ваш Wio Terminal к IoT Hub, чтобы отправлять телеметрию и получать команды.

## Подключение устройства к IoT Hub

Следующий шаг — подключить ваше устройство к IoT Hub.

### Задача - подключение к IoT Hub

1. Откройте проект `soil-moisture-sensor` в VS Code.

1. Откройте файл `platformio.ini`. Удалите зависимость библиотеки `knolleary/PubSubClient`. Она использовалась для подключения к публичному MQTT-брокеру, но не нужна для подключения к IoT Hub.

1. Добавьте следующие зависимости библиотек:

    ```ini
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    arduino-libraries/AzureIoTHub @ 1.6.0
    azure/AzureIoTUtility @ 1.6.1
    azure/AzureIoTProtocol_MQTT @ 1.6.0
    azure/AzureIoTProtocol_HTTP @ 1.6.0
    azure/AzureIoTSocket_WiFi @ 1.0.2
    ```

    Библиотека `Seeed Arduino RTC` предоставляет код для взаимодействия с часами реального времени в Wio Terminal, которые используются для отслеживания времени. Остальные библиотеки позволяют вашему IoT-устройству подключаться к IoT Hub.

1. Добавьте следующее в конец файла `platformio.ini`:

    ```ini
    build_flags =
        -DDONT_USE_UPLOADTOBLOB
    ```

    Это устанавливает флаг компилятора, необходимый при компиляции кода Arduino IoT Hub.

1. Откройте заголовочный файл `config.h`. Удалите все настройки MQTT и добавьте следующую константу для строки подключения устройства:

    ```cpp
    // IoT Hub settings
    const char *CONNECTION_STRING = "<connection string>";
    ```

    Замените `<connection string>` на строку подключения вашего устройства, которую вы скопировали ранее.

1. Подключение к IoT Hub использует токен, основанный на времени. Это означает, что IoT-устройство должно знать текущее время. В отличие от операционных систем, таких как Windows, macOS или Linux, микроконтроллеры не синхронизируют текущее время автоматически через Интернет. Это значит, что вам нужно добавить код для получения текущего времени с сервера [NTP](https://wikipedia.org/wiki/Network_Time_Protocol). После получения времени оно может быть сохранено в часах реального времени в Wio Terminal, что позволит запрашивать правильное время позже, если устройство не потеряет питание. Добавьте новый файл с именем `ntp.h` со следующим кодом:

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

    Детали этого кода выходят за рамки данного урока. Он определяет функцию `initTime`, которая получает текущее время с сервера NTP и использует его для установки часов на Wio Terminal.

1. Откройте файл `main.cpp` и удалите весь код MQTT, включая заголовочный файл `PubSubClient.h`, объявление переменной `PubSubClient`, методы `reconnectMQTTClient` и `createMQTTClient`, а также любые вызовы этих переменных и методов. Этот файл должен содержать только код для подключения к WiFi, получения данных о влажности почвы и создания JSON-документа с этими данными.

1. Добавьте следующие директивы `#include` в начало файла `main.cpp`, чтобы включить заголовочные файлы для библиотек IoT Hub и для установки времени:

    ```cpp
    #include <AzureIoTHub.h>
    #include <AzureIoTProtocol_MQTT.h>
    #include <iothubtransportmqtt.h>
    #include "ntp.h"
    ```

1. Добавьте следующий вызов в конец функции `setup` для установки текущего времени:

    ```cpp
    initTime();
    ```

1. Добавьте следующее объявление переменной в начало файла, сразу под директивами include:

    ```cpp
    IOTHUB_DEVICE_CLIENT_LL_HANDLE _device_ll_handle;
    ```

    Это объявляет `IOTHUB_DEVICE_CLIENT_LL_HANDLE`, дескриптор подключения к IoT Hub.

1. Ниже этого добавьте следующий код:

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

    Это объявляет функцию обратного вызова, которая будет вызываться при изменении статуса подключения к IoT Hub, например, при подключении или отключении. Статус отправляется на последовательный порт.

1. Ниже этого добавьте функцию для подключения к IoT Hub:

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

    Этот код инициализирует библиотечный код IoT Hub, затем создает подключение, используя строку подключения из заголовочного файла `config.h`. Это подключение основано на MQTT. Если подключение не удается, информация об этом отправляется на последовательный порт — если вы видите это в выводе, проверьте строку подключения. Наконец, устанавливается обратный вызов статуса подключения.

1. Вызовите эту функцию в функции `setup` ниже вызова `initTime`:

    ```cpp
    connectIoTHub();
    ```

1. Как и в случае с клиентом MQTT, этот код работает в одном потоке, поэтому ему нужно время для обработки сообщений, отправляемых хабом и в хаб. Добавьте следующее в начало функции `loop`, чтобы это сделать:

    ```cpp
    IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
    ```

1. Соберите и загрузите этот код. Вы увидите подключение в монитор последовательного порта:

    ```output
    Connecting to WiFi..
    Connected!
    Fetched NTP epoch time is: 1619983687
    Sending telemetry {"soil_moisture":391}
    The device client is connected to iothub
    ```

    В выводе вы можете увидеть, как запрашивается время NTP, а затем устройство подключается к клиенту. Подключение может занять несколько секунд, поэтому вы можете увидеть данные о влажности почвы в выводе, пока устройство подключается.

    > 💁 Вы можете преобразовать UNIX-время для NTP в более читаемый формат, используя веб-сайт, например [unixtimestamp.com](https://www.unixtimestamp.com).

## Отправка телеметрии

Теперь, когда ваше устройство подключено, вы можете отправлять телеметрию в IoT Hub вместо MQTT-брокера.

### Задача - отправка телеметрии

1. Добавьте следующую функцию выше функции `setup`:

    ```cpp
    void sendTelemetry(const char *telemetry)
    {
        IOTHUB_MESSAGE_HANDLE message_handle = IoTHubMessage_CreateFromString(telemetry);
        IoTHubDeviceClient_LL_SendEventAsync(_device_ll_handle, message_handle, NULL, NULL);
        IoTHubMessage_Destroy(message_handle);
    }
    ```

    Этот код создает сообщение IoT Hub из строки, переданной в качестве параметра, отправляет его в хаб, а затем очищает объект сообщения.

1. Вызовите этот код в функции `loop`, сразу после строки, где телеметрия отправляется на последовательный порт:

    ```cpp
    sendTelemetry(telemetry.c_str());
    ```

## Обработка команд

Ваше устройство должно обрабатывать команды от серверного кода для управления реле. Это отправляется как запрос метода.

### Задача - обработка запроса метода

1. Добавьте следующий код перед функцией `connectIoTHub`:

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

    Этот код определяет метод обратного вызова, который библиотека IoT Hub может вызывать при получении запроса метода. Метод, который запрашивается, передается в параметре `method_name`. Эта функция выводит название метода на последовательный порт, а затем включает или выключает реле в зависимости от названия метода.

    > 💁 Это также можно реализовать в одном запросе метода, передавая желаемое состояние реле в полезной нагрузке, которая может быть передана с запросом метода и доступна из параметра `payload`.

1. Добавьте следующий код в конец функции `directMethodCallback`:

    ```cpp
    char resultBuff[16];
    sprintf(resultBuff, "{\"Result\":\"\"}");
    *response_size = strlen(resultBuff);
    *response = (unsigned char *)malloc(*response_size);
    memcpy(*response, resultBuff, *response_size);

    return IOTHUB_CLIENT_OK;
    ```

    Запросы метода требуют ответа, и ответ состоит из двух частей — текстового ответа и кода возврата. Этот код создаст результат в виде следующего JSON-документа:

    ```JSON
    {
        "Result": ""
    }
    ```

    Затем он копируется в параметр `response`, а размер этого ответа устанавливается в параметре `response_size`. Этот код затем возвращает `IOTHUB_CLIENT_OK`, чтобы показать, что метод был обработан корректно.

1. Настройте обратный вызов, добавив следующее в конец функции `connectIoTHub`:

    ```cpp
    IoTHubClient_LL_SetDeviceMethodCallback(_device_ll_handle, directMethodCallback, NULL);
    ```

1. Функция `loop` будет вызывать функцию `IoTHubDeviceClient_LL_DoWork` для обработки событий, отправленных IoT Hub. Это вызывается только каждые 10 секунд из-за `delay`, что означает, что методы обрабатываются только каждые 10 секунд. Чтобы сделать это более эффективно, задержку в 10 секунд можно реализовать как множество коротких задержек, вызывая `IoTHubDeviceClient_LL_DoWork` каждый раз. Для этого добавьте следующий код выше функции `loop`:

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

    Этот код будет повторяться, вызывая `IoTHubDeviceClient_LL_DoWork` и задерживаясь на 100 мс каждый раз. Он будет делать это столько раз, сколько нужно, чтобы задержаться на указанное время в параметре `delay_time`. Это означает, что устройство ждет максимум 100 мс для обработки запросов метода.

1. В функции `loop` удалите вызов `IoTHubDeviceClient_LL_DoWork` и замените вызов `delay(10000)` следующим, чтобы вызвать эту новую функцию:

    ```cpp
    work_delay(10000);
    ```

> 💁 Вы можете найти этот код в папке [code/wio-terminal](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/wio-terminal).

😀 Ваше приложение датчика влажности почвы подключено к вашему IoT Hub!

---

**Отказ от ответственности**:  
Этот документ был переведен с помощью сервиса автоматического перевода [Co-op Translator](https://github.com/Azure/co-op-translator). Хотя мы стремимся к точности, пожалуйста, имейте в виду, что автоматические переводы могут содержать ошибки или неточности. Оригинальный документ на его родном языке следует считать авторитетным источником. Для получения критически важной информации рекомендуется профессиональный перевод человеком. Мы не несем ответственности за любые недоразумения или неправильные интерпретации, возникшие в результате использования данного перевода.