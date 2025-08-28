<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4bcc29fe2b65e56eada83d2476279227",
  "translation_date": "2025-08-28T17:13:24+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md",
  "language_code": "uk"
}
-->
# Керуйте нічником через Інтернет - Wio Terminal

У цій частині уроку ви будете надсилати телеметрію з рівнями освітлення з вашого Wio Terminal до брокера MQTT.

## Встановіть бібліотеки JSON для Arduino

Популярний спосіб надсилання повідомлень через MQTT — використання JSON. Існує бібліотека Arduino для JSON, яка спрощує читання та запис JSON-документів.

### Завдання

Встановіть бібліотеку Arduino JSON.

1. Відкрийте проєкт нічника у VS Code.

1. Додайте наступний рядок до списку `lib_deps` у файлі `platformio.ini`:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    Це імпортує [ArduinoJson](https://arduinojson.org), бібліотеку JSON для Arduino.

## Публікація телеметрії

Наступний крок — створити JSON-документ із телеметрією та надіслати його до брокера MQTT.

### Завдання - публікація телеметрії

Опублікуйте телеметрію до брокера MQTT.

1. Додайте наступний код у кінець файлу `config.h`, щоб визначити назву теми телеметрії для брокера MQTT:

    ```cpp
    const string CLIENT_TELEMETRY_TOPIC = ID + "/telemetry";
    ```

    `CLIENT_TELEMETRY_TOPIC` — це тема, до якої пристрій буде публікувати рівні освітлення.

1. Відкрийте файл `main.cpp`.

1. Додайте наступну директиву `#include` на початок файлу:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. Додайте наступний код у функцію `loop`, безпосередньо перед `delay`:

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

    Цей код зчитує рівень освітлення, створює JSON-документ за допомогою ArduinoJson, що містить цей рівень. Потім він серіалізується у рядок і публікується в темі телеметрії MQTT клієнтом MQTT.

1. Завантажте код на ваш Wio Terminal і використовуйте Серійний Монітор, щоб побачити рівні освітлення, які надсилаються до брокера MQTT.

    ```output
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"light":652}
    Sending telemetry {"light":612}
    Sending telemetry {"light":583}
    ```

> 💁 Ви можете знайти цей код у папці [code-telemetry/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/wio-terminal).

😀 Ви успішно надіслали телеметрію з вашого пристрою.

---

**Відмова від відповідальності**:  
Цей документ був перекладений за допомогою сервісу автоматичного перекладу [Co-op Translator](https://github.com/Azure/co-op-translator). Хоча ми прагнемо до точності, будь ласка, майте на увазі, що автоматичні переклади можуть містити помилки або неточності. Оригінальний документ на його рідній мові слід вважати авторитетним джерелом. Для критичної інформації рекомендується професійний людський переклад. Ми не несемо відповідальності за будь-які непорозуміння або неправильні тлумачення, що виникають внаслідок використання цього перекладу.