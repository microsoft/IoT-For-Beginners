<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "28320305a35ea3bc59c41fe146a2e6ed",
  "translation_date": "2025-08-28T18:04:44+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/wio-terminal-connect-hub.md",
  "language_code": "uk"
}
-->
# Підключіть ваш IoT-пристрій до хмари - Wio Terminal

У цій частині уроку ви підключите ваш Wio Terminal до IoT Hub, щоб надсилати телеметрію та отримувати команди.

## Підключіть ваш пристрій до IoT Hub

Наступний крок — підключити ваш пристрій до IoT Hub.

### Завдання - підключення до IoT Hub

1. Відкрийте проект `soil-moisture-sensor` у VS Code.

1. Відкрийте файл `platformio.ini`. Видаліть залежність бібліотеки `knolleary/PubSubClient`. Вона використовувалася для підключення до загальнодоступного MQTT-брокера, але не потрібна для підключення до IoT Hub.

1. Додайте наступні залежності бібліотек:

    ```ini
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    arduino-libraries/AzureIoTHub @ 1.6.0
    azure/AzureIoTUtility @ 1.6.1
    azure/AzureIoTProtocol_MQTT @ 1.6.0
    azure/AzureIoTProtocol_HTTP @ 1.6.0
    azure/AzureIoTSocket_WiFi @ 1.0.2
    ```

    Бібліотека `Seeed Arduino RTC` надає код для взаємодії з реальним годинником у Wio Terminal, який використовується для відстеження часу. Решта бібліотек дозволяють вашому IoT-пристрою підключатися до IoT Hub.

1. Додайте наступне в кінці файлу `platformio.ini`:

    ```ini
    build_flags =
        -DDONT_USE_UPLOADTOBLOB
    ```

    Це встановлює прапорець компілятора, необхідний для компіляції коду Arduino IoT Hub.

1. Відкрийте заголовковий файл `config.h`. Видаліть усі налаштування MQTT і додайте наступну константу для рядка підключення пристрою:

    ```cpp
    // IoT Hub settings
    const char *CONNECTION_STRING = "<connection string>";
    ```

    Замініть `<connection string>` на рядок підключення для вашого пристрою, який ви скопіювали раніше.

1. Підключення до IoT Hub використовує токен, заснований на часі. Це означає, що IoT-пристрій повинен знати поточний час. На відміну від операційних систем, таких як Windows, macOS або Linux, мікроконтролери не синхронізують поточний час через Інтернет автоматично. Це означає, що вам потрібно додати код для отримання поточного часу з [NTP](https://wikipedia.org/wiki/Network_Time_Protocol)-сервера. Після отримання часу його можна зберегти в реальному годиннику у Wio Terminal, що дозволяє запитувати правильний час пізніше, якщо пристрій не втратить живлення. Додайте новий файл під назвою `ntp.h` з наступним кодом:

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

    Деталі цього коду виходять за межі цього уроку. Він визначає функцію `initTime`, яка отримує поточний час із NTP-сервера та використовує його для встановлення годинника на Wio Terminal.

1. Відкрийте файл `main.cpp` і видаліть увесь код MQTT, включаючи заголовковий файл `PubSubClient.h`, оголошення змінної `PubSubClient`, методи `reconnectMQTTClient` і `createMQTTClient`, а також будь-які виклики цих змінних і методів. Цей файл повинен містити лише код для підключення до WiFi, отримання вологості ґрунту та створення JSON-документа з цими даними.

1. Додайте наступні директиви `#include` у верхній частині файлу `main.cpp`, щоб включити заголовкові файли для бібліотек IoT Hub і для встановлення часу:

    ```cpp
    #include <AzureIoTHub.h>
    #include <AzureIoTProtocol_MQTT.h>
    #include <iothubtransportmqtt.h>
    #include "ntp.h"
    ```

1. Додайте наступний виклик у кінці функції `setup`, щоб встановити поточний час:

    ```cpp
    initTime();
    ```

1. Додайте наступне оголошення змінної у верхній частині файлу, одразу під директивами include:

    ```cpp
    IOTHUB_DEVICE_CLIENT_LL_HANDLE _device_ll_handle;
    ```

    Це оголошує `IOTHUB_DEVICE_CLIENT_LL_HANDLE`, дескриптор для підключення до IoT Hub.

1. Нижче цього додайте наступний код:

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

    Це оголошує функцію зворотного виклику, яка буде викликана, коли підключення до IoT Hub змінить статус, наприклад, підключення або відключення. Статус буде надіслано на послідовний порт.

1. Нижче цього додайте функцію для підключення до IoT Hub:

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

    Цей код ініціалізує бібліотечний код IoT Hub, а потім створює підключення за допомогою рядка підключення у заголовковому файлі `config.h`. Це підключення базується на MQTT. Якщо підключення не вдається, це буде надіслано на послідовний порт — якщо ви бачите це у виводі, перевірте рядок підключення. Нарешті, налаштовується зворотний виклик статусу підключення.

1. Викличте цю функцію у функції `setup` нижче виклику `initTime`:

    ```cpp
    connectIoTHub();
    ```

1. Як і у випадку з клієнтом MQTT, цей код працює в одному потоці, тому йому потрібен час для обробки повідомлень, які надсилаються хабом і до хабу. Додайте наступне у верхній частині функції `loop`, щоб зробити це:

    ```cpp
    IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
    ```

1. Зберіть і завантажте цей код. Ви побачите підключення у послідовному моніторі:

    ```output
    Connecting to WiFi..
    Connected!
    Fetched NTP epoch time is: 1619983687
    Sending telemetry {"soil_moisture":391}
    The device client is connected to iothub
    ```

    У виводі ви можете побачити, як отримується час NTP, а потім клієнт пристрою підключається. Підключення може зайняти кілька секунд, тому ви можете побачити вологість ґрунту у виводі, поки пристрій підключається.

    > 💁 Ви можете конвертувати UNIX-час для NTP у більш читабельну версію, використовуючи веб-сайт, наприклад [unixtimestamp.com](https://www.unixtimestamp.com).

## Надсилання телеметрії

Тепер, коли ваш пристрій підключений, ви можете надсилати телеметрію до IoT Hub замість MQTT-брокера.

### Завдання - надсилання телеметрії

1. Додайте наступну функцію над функцією `setup`:

    ```cpp
    void sendTelemetry(const char *telemetry)
    {
        IOTHUB_MESSAGE_HANDLE message_handle = IoTHubMessage_CreateFromString(telemetry);
        IoTHubDeviceClient_LL_SendEventAsync(_device_ll_handle, message_handle, NULL, NULL);
        IoTHubMessage_Destroy(message_handle);
    }
    ```

    Цей код створює повідомлення IoT Hub із рядка, переданого як параметр, надсилає його до хабу, а потім очищає об'єкт повідомлення.

1. Викличте цей код у функції `loop`, одразу після рядка, де телеметрія надсилається на послідовний порт:

    ```cpp
    sendTelemetry(telemetry.c_str());
    ```

## Обробка команд

Ваш пристрій повинен обробляти команду від серверного коду для керування реле. Це надсилається як запит прямого методу.

## Завдання - обробка запиту прямого методу

1. Додайте наступний код перед функцією `connectIoTHub`:

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

    Цей код визначає метод зворотного виклику, який бібліотека IoT Hub може викликати, коли отримує запит прямого методу. Метод, який запитується, передається у параметрі `method_name`. Ця функція друкує викликаний метод на послідовний порт, а потім вмикає або вимикає реле залежно від назви методу.

    > 💁 Це також можна реалізувати в одному запиті прямого методу, передаючи бажаний стан реле у корисному навантаженні, яке можна передати із запитом методу та отримати з параметра `payload`.

1. Додайте наступний код у кінці функції `directMethodCallback`:

    ```cpp
    char resultBuff[16];
    sprintf(resultBuff, "{\"Result\":\"\"}");
    *response_size = strlen(resultBuff);
    *response = (unsigned char *)malloc(*response_size);
    memcpy(*response, resultBuff, *response_size);

    return IOTHUB_CLIENT_OK;
    ```

    Запити прямого методу потребують відповіді, і відповідь складається з двох частин — відповіді у вигляді тексту та коду повернення. Цей код створить результат у вигляді наступного JSON-документа:

    ```JSON
    {
        "Result": ""
    }
    ```

    Потім це копіюється у параметр `response`, а розмір цієї відповіді встановлюється у параметрі `response_size`. Цей код потім повертає `IOTHUB_CLIENT_OK`, щоб показати, що метод був оброблений правильно.

1. Підключіть зворотний виклик, додавши наступне у кінці функції `connectIoTHub`:

    ```cpp
    IoTHubClient_LL_SetDeviceMethodCallback(_device_ll_handle, directMethodCallback, NULL);
    ```

1. Функція `loop` викликатиме функцію `IoTHubDeviceClient_LL_DoWork` для обробки подій, надісланих IoT Hub. Це викликається лише кожні 10 секунд через `delay`, що означає, що прямі методи обробляються лише кожні 10 секунд. Щоб зробити це більш ефективним, затримку в 10 секунд можна реалізувати як багато коротших затримок, викликаючи `IoTHubDeviceClient_LL_DoWork` кожного разу. Для цього додайте наступний код над функцією `loop`:

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

    Цей код буде повторюватися, викликаючи `IoTHubDeviceClient_LL_DoWork` і затримуючи на 100 мс кожного разу. Він робитиме це стільки разів, скільки потрібно, щоб затримати на час, заданий у параметрі `delay_time`. Це означає, що пристрій чекає максимум 100 мс для обробки запитів прямого методу.

1. У функції `loop` видаліть виклик `IoTHubDeviceClient_LL_DoWork` і замініть виклик `delay(10000)` наступним, щоб викликати цю нову функцію:

    ```cpp
    work_delay(10000);
    ```

> 💁 Ви можете знайти цей код у папці [code/wio-terminal](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/wio-terminal).

😀 Ваша програма датчика вологості ґрунту підключена до вашого IoT Hub!

---

**Відмова від відповідальності**:  
Цей документ був перекладений за допомогою сервісу автоматичного перекладу [Co-op Translator](https://github.com/Azure/co-op-translator). Хоча ми прагнемо до точності, будь ласка, майте на увазі, що автоматичні переклади можуть містити помилки або неточності. Оригінальний документ на його рідній мові слід вважати авторитетним джерелом. Для критичної інформації рекомендується професійний людський переклад. Ми не несемо відповідальності за будь-які непорозуміння або неправильні тлумачення, що виникають внаслідок використання цього перекладу.