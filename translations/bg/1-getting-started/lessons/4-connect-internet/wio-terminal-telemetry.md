<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4bcc29fe2b65e56eada83d2476279227",
  "translation_date": "2025-08-28T10:14:28+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md",
  "language_code": "bg"
}
-->
# Контролирайте нощната си лампа през Интернет - Wio Terminal

В тази част от урока ще изпращате телеметрия с нива на светлина от вашия Wio Terminal към MQTT брокера.

## Инсталирайте JSON библиотеките за Arduino

Популярен начин за изпращане на съобщения през MQTT е използването на JSON. Съществува библиотека за Arduino, която улеснява четенето и писането на JSON документи.

### Задача

Инсталирайте JSON библиотеката за Arduino.

1. Отворете проекта за нощна лампа в VS Code.

1. Добавете следния ред като допълнителен към списъка `lib_deps` в файла `platformio.ini`:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    Това импортира [ArduinoJson](https://arduinojson.org), библиотека за JSON за Arduino.

## Публикувайте телеметрия

Следващата стъпка е да създадете JSON документ с телеметрия и да го изпратите към MQTT брокера.

### Задача - публикуване на телеметрия

Публикувайте телеметрия към MQTT брокера.

1. Добавете следния код в долната част на файла `config.h`, за да дефинирате името на темата за телеметрия за MQTT брокера:

    ```cpp
    const string CLIENT_TELEMETRY_TOPIC = ID + "/telemetry";
    ```

    `CLIENT_TELEMETRY_TOPIC` е темата, в която устройството ще публикува нивата на светлина.

1. Отворете файла `main.cpp`.

1. Добавете следната директива `#include` в горната част на файла:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. Добавете следния код вътре във функцията `loop`, точно преди `delay`:

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

    Този код чете нивото на светлина и създава JSON документ, използвайки ArduinoJson, който съдържа това ниво. След това документът се сериализира в низ и се публикува в темата за телеметрия на MQTT чрез MQTT клиента.

1. Качете кода на вашия Wio Terminal и използвайте Serial Monitor, за да видите нивата на светлина, които се изпращат към MQTT брокера.

    ```output
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"light":652}
    Sending telemetry {"light":612}
    Sending telemetry {"light":583}
    ```

> 💁 Можете да намерите този код в папката [code-telemetry/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/wio-terminal).

😀 Успешно изпратихте телеметрия от вашето устройство.

---

**Отказ от отговорност**:  
Този документ е преведен с помощта на AI услуга за превод [Co-op Translator](https://github.com/Azure/co-op-translator). Въпреки че се стремим към точност, моля, имайте предвид, че автоматизираните преводи може да съдържат грешки или неточности. Оригиналният документ на неговия роден език трябва да се счита за авторитетен източник. За критична информация се препоръчва професионален човешки превод. Ние не носим отговорност за каквито и да е недоразумения или погрешни интерпретации, произтичащи от използването на този превод.