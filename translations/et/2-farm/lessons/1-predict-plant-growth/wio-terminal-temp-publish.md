<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "df28cd649cd892bcce034e064913b2f3",
  "translation_date": "2025-10-11T12:33:38+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp-publish.md",
  "language_code": "et"
}
-->
# Temperatuuri avaldamine - Wio Terminal

Selles õppetunni osas avaldate Wio Terminali tuvastatud temperatuuri väärtused MQTT kaudu, et neid saaks hiljem kasutada GDD arvutamiseks.

## Temperatuuri avaldamine

Kui temperatuur on loetud, saab selle MQTT kaudu avaldada mingile 'serveri' koodile, mis loeb väärtused ja salvestab need, et neid saaks GDD arvutamiseks kasutada. Mikrokontrollerid ei loe aega internetist ega jälgi aega reaalaja kellaga automaatselt, seade tuleb selleks programmeerida, eeldades, et sellel on vajalik riistvara.

Selle õppetunni lihtsustamiseks ei saadeta sensorite andmetega aega, selle asemel saab serveri kood selle hiljem sõnumite vastuvõtmisel lisada.

### Ülesanne

Programmeerige seade temperatuuriandmete avaldamiseks.

1. Avage `temperature-sensor` Wio Terminali projekt.

1. Korrake 4. õppetunnis tehtud samme, et ühenduda MQTT-ga ja saata telemeetriat. Kasutate sama avalikku Mosquitto brokerit.

    Sammud selleks on:

    - Lisage `.ini` faili Seeed WiFi ja MQTT teegid.
    - Lisage konfiguratsioonifail ja kood WiFi-ga ühendamiseks.
    - Lisage kood MQTT brokeriga ühendamiseks.
    - Lisage kood telemeetria avaldamiseks.

    > ⚠️ Vaadake vajadusel [juhiseid MQTT-ga ühendamiseks](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md) ja [juhiseid telemeetria saatmiseks](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md) 4. õppetunnist.

1. Veenduge, et `CLIENT_NAME` konfiguratsioonifailis `config.h` kajastaks seda projekti:

    ```cpp
    const string CLIENT_NAME = ID + "temperature_sensor_client";
    ```

1. Telemeetria jaoks, valguse väärtuse saatmise asemel, saatke DHT sensori poolt loetud temperatuuri väärtus JSON dokumendi omaduses nimega `temperature`, muutes `loop` funktsiooni failis `main.cpp`:

    ```cpp
    float temp_hum_val[2] = {0};
    dht.readTempAndHumidity(temp_hum_val);

    DynamicJsonDocument doc(1024);
    doc["temperature"] = temp_hum_val[1];
    ```

1. Temperatuuri väärtust ei ole vaja väga tihti lugeda - see ei muutu lühikese aja jooksul palju, seega seadke `loop` funktsiooni `delay` väärtuseks 10 minutit:

    ```cpp
    delay(10 * 60 * 1000);
    ```

    > 💁 `delay` funktsioon võtab aja millisekundites, seega lihtsustamiseks edastatakse väärtus arvutuse tulemusena. 1,000ms sekundis, 60s minutis, seega 10 x (60s minutis) x (1000ms sekundis) annab 10-minutilise viivituse.

1. Laadige see oma Wio Terminali ja kasutage seeria monitori, et näha, kuidas temperatuur saadetakse MQTT brokerile.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"temperature":25}
    Sending telemetry {"temperature":25}
    ```

> 💁 Selle koodi leiate kaustast [code-publish-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/wio-terminal).

😀 Olete edukalt avaldanud temperatuuri telemeetria oma seadmest.

---

**Lahtiütlus**:  
See dokument on tõlgitud AI tõlketeenuse [Co-op Translator](https://github.com/Azure/co-op-translator) abil. Kuigi püüame tagada täpsust, palume arvestada, et automaatsed tõlked võivad sisaldada vigu või ebatäpsusi. Algne dokument selle algses keeles tuleks pidada autoriteetseks allikaks. Olulise teabe puhul soovitame kasutada professionaalset inimtõlget. Me ei vastuta selle tõlke kasutamisest tulenevate arusaamatuste või valesti tõlgenduste eest.