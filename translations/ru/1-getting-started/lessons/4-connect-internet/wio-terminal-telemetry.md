<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4bcc29fe2b65e56eada83d2476279227",
  "translation_date": "2025-08-26T23:17:26+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md",
  "language_code": "ru"
}
-->
# Управляйте ночником через Интернет - Wio Terminal

В этой части урока вы будете отправлять телеметрию с уровнями освещенности с вашего Wio Terminal на MQTT-брокер.

## Установите библиотеки JSON для Arduino

Популярный способ отправки сообщений через MQTT — использование JSON. Существует библиотека Arduino для JSON, которая упрощает чтение и запись JSON-документов.

### Задание

Установите библиотеку Arduino JSON.

1. Откройте проект ночника в VS Code.

1. Добавьте следующую строку в список `lib_deps` в файле `platformio.ini`:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    Это подключает [ArduinoJson](https://arduinojson.org), библиотеку JSON для Arduino.

## Публикация телеметрии

Следующий шаг — создать JSON-документ с телеметрией и отправить его на MQTT-брокер.

### Задание - публикация телеметрии

Опубликуйте телеметрию на MQTT-брокере.

1. Добавьте следующий код в конец файла `config.h`, чтобы определить имя темы телеметрии для MQTT-брокера:

    ```cpp
    const string CLIENT_TELEMETRY_TOPIC = ID + "/telemetry";
    ```

    `CLIENT_TELEMETRY_TOPIC` — это тема, в которую устройство будет публиковать данные об уровнях освещенности.

1. Откройте файл `main.cpp`.

1. Добавьте следующую директиву `#include` в начало файла:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. Добавьте следующий код в функцию `loop`, прямо перед `delay`:

    ```cpp
    int light = analogRead(WIO_LIGHT);

    DynamicJsonDocument doc(1024);
    doc["light"] = light;

    string telemetry;
    serializeJson(doc, telemetry);

    Serial.print("Sending telemetry ");
    Serial.println(telemetry.c_str());

    client.publish(CLIENT_TELEMETRY_TOPIC.c_str(), telemetry.c_str());
    ```

    Этот код считывает уровень освещенности, создает JSON-документ с использованием ArduinoJson, содержащий этот уровень. Затем он сериализуется в строку и публикуется в теме телеметрии MQTT с помощью клиента MQTT.

1. Загрузите код на ваш Wio Terminal и используйте Serial Monitor, чтобы увидеть, как уровни освещенности отправляются на MQTT-брокер.

    ```output
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"light":652}
    Sending telemetry {"light":612}
    Sending telemetry {"light":583}
    ```

> 💁 Вы можете найти этот код в папке [code-telemetry/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/wio-terminal).

😀 Вы успешно отправили телеметрию с вашего устройства.

---

**Отказ от ответственности**:  
Этот документ был переведен с помощью сервиса автоматического перевода [Co-op Translator](https://github.com/Azure/co-op-translator). Несмотря на наши усилия обеспечить точность, автоматические переводы могут содержать ошибки или неточности. Оригинальный документ на его родном языке следует считать авторитетным источником. Для получения критически важной информации рекомендуется профессиональный перевод человеком. Мы не несем ответственности за любые недоразумения или неправильные интерпретации, возникающие в результате использования данного перевода.