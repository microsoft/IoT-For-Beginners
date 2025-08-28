<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4bcc29fe2b65e56eada83d2476279227",
  "translation_date": "2025-08-28T13:53:06+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md",
  "language_code": "sr"
}
-->
# Контролишите своје ноћно светло преко интернета - Wio Terminal

У овом делу лекције, слаћете телеметрију са нивоима светлости са вашег Wio Terminal-а на MQTT брокер.

## Инсталирајте JSON Arduino библиотеке

Популаран начин за слање порука преко MQTT-а је коришћење JSON-а. Постоји Arduino библиотека за JSON која олакшава читање и писање JSON докумената.

### Задатак

Инсталирајте Arduino JSON библиотеку.

1. Отворите пројекат ноћног светла у VS Code-у.

1. Додајте следећу линију у `lib_deps` листу у `platformio.ini` фајлу:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    Ово увози [ArduinoJson](https://arduinojson.org), Arduino JSON библиотеку.

## Објавите телеметрију

Следећи корак је креирање JSON документа са телеметријом и његово слање на MQTT брокер.

### Задатак - објавите телеметрију

Објавите телеметрију на MQTT брокер.

1. Додајте следећи код на крај `config.h` фајла да дефинишете назив теме за телеметрију на MQTT брокеру:

    ```cpp
    const string CLIENT_TELEMETRY_TOPIC = ID + "/telemetry";
    ```

    `CLIENT_TELEMETRY_TOPIC` је тема на коју ће уређај објављивати нивое светлости.

1. Отворите `main.cpp` фајл.

1. Додајте следећу `#include` директиву на врх фајла:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. Додајте следећи код унутар `loop` функције, непосредно пре `delay`:

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

    Овај код чита ниво светлости и креира JSON документ користећи ArduinoJson који садржи овај ниво. Затим се овај документ серијализује у стринг и објављује на телеметријској MQTT теми преко MQTT клијента.

1. Отпремите код на ваш Wio Terminal и користите Serial Monitor да видите нивое светлости који се шаљу на MQTT брокер.

    ```output
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"light":652}
    Sending telemetry {"light":612}
    Sending telemetry {"light":583}
    ```

> 💁 Овај код можете пронаћи у [code-telemetry/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/wio-terminal) фасцикли.

😀 Успешно сте послали телеметрију са вашег уређаја.

---

**Одрицање од одговорности**:  
Овај документ је преведен коришћењем услуге за превођење помоћу вештачке интелигенције [Co-op Translator](https://github.com/Azure/co-op-translator). Иако се трудимо да обезбедимо тачност, молимо вас да имате у виду да аутоматски преводи могу садржати грешке или нетачности. Оригинални документ на његовом изворном језику треба сматрати меродавним извором. За критичне информације препоручује се професионални превод од стране људи. Не преузимамо одговорност за било каква погрешна тумачења или неспоразуме који могу настати услед коришћења овог превода.