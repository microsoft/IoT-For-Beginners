<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4bcc29fe2b65e56eada83d2476279227",
  "translation_date": "2025-10-11T11:20:10+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md",
  "language_code": "et"
}
-->
# Juhi oma öölampi Interneti kaudu - Wio Terminal

Selles õppetunni osas saadad telemeetriat Wio Terminali valguse tasemetega MQTT brokerile.

## Paigalda JSON Arduino teegid

Populaarne viis sõnumite saatmiseks MQTT kaudu on kasutada JSON-i. Arduino jaoks on olemas JSON-teek, mis muudab JSON-dokumentide lugemise ja kirjutamise lihtsamaks.

### Ülesanne

Paigalda Arduino JSON teek.

1. Ava öölambi projekt VS Code'is.

1. Lisa järgmine rida `lib_deps` loendisse `platformio.ini` failis:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    See impordib [ArduinoJson](https://arduinojson.org), Arduino JSON teegi.

## Telemeetria avaldamine

Järgmine samm on luua telemeetria jaoks JSON-dokument ja saata see MQTT brokerile.

### Ülesanne - telemeetria avaldamine

Avalda telemeetria MQTT brokerile.

1. Lisa järgmine kood `config.h` faili lõppu, et määratleda telemeetria teema nimi MQTT brokeri jaoks:

    ```cpp
    const string CLIENT_TELEMETRY_TOPIC = ID + "/telemetry";
    ```

    `CLIENT_TELEMETRY_TOPIC` on teema, kuhu seade avaldab valguse tasemed.

1. Ava `main.cpp` fail.

1. Lisa järgmine `#include` direktiiv faili algusesse:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. Lisa järgmine kood `loop` funktsiooni sisse, vahetult enne `delay`:

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

    See kood loeb valguse taseme, loob ArduinoJson-i abil JSON-dokumendi, mis sisaldab seda taset. Seejärel serialiseeritakse see stringiks ja avaldatakse telemeetria MQTT teemas MQTT kliendi poolt.

1. Laadi kood oma Wio Terminali ja kasuta Serial Monitori, et näha, kuidas valguse tasemed saadetakse MQTT brokerile.

    ```output
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"light":652}
    Sending telemetry {"light":612}
    Sending telemetry {"light":583}
    ```

> 💁 Selle koodi leiad [code-telemetry/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/wio-terminal) kaustast.

😀 Sa oled edukalt saatnud telemeetria oma seadmest.

---

**Lahtiütlus**:  
See dokument on tõlgitud AI tõlketeenuse [Co-op Translator](https://github.com/Azure/co-op-translator) abil. Kuigi püüame tagada täpsust, palume arvestada, et automaatsed tõlked võivad sisaldada vigu või ebatäpsusi. Algne dokument selle algses keeles tuleks pidada autoriteetseks allikaks. Olulise teabe puhul soovitame kasutada professionaalset inimtõlget. Me ei vastuta selle tõlke kasutamisest tulenevate arusaamatuste või valesti tõlgenduste eest.