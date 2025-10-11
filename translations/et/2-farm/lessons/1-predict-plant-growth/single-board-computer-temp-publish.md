<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4efc74299e19f5d08f2f3f34451a11ba",
  "translation_date": "2025-10-11T12:34:27+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/single-board-computer-temp-publish.md",
  "language_code": "et"
}
-->
# Temperatuuri avaldamine - Virtuaalne IoT riistvara ja Raspberry Pi

Selles õppetunni osas avaldate Raspberry Pi või virtuaalse IoT seadme tuvastatud temperatuuri väärtused MQTT kaudu, et neid hiljem kasutada GDD arvutamiseks.

## Temperatuuri avaldamine

Kui temperatuur on loetud, saab selle MQTT kaudu avaldada mõnele "serveri" koodile, mis loeb väärtused ja salvestab need GDD arvutamiseks.

### Ülesanne - temperatuuri avaldamine

Programmeerige seade temperatuuriandmete avaldamiseks.

1. Avage `temperature-sensor` rakenduse projekt, kui see pole juba avatud.

1. Korrake 4. õppetunnis tehtud samme, et ühenduda MQTT-ga ja saata telemeetriat. Kasutate sama avalikku Mosquitto brokerit.

    Sammud selleks on:

    - Lisage MQTT pip pakett
    - Lisage kood MQTT brokeriga ühenduse loomiseks
    - Lisage kood telemeetria avaldamiseks

    > ⚠️ Vaadake vajadusel [juhiseid MQTT-ga ühenduse loomiseks](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md) ja [juhiseid telemeetria saatmiseks](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md) 4. õppetunnist.

1. Veenduge, et `client_name` kajastaks selle projekti nime:

    ```python
    client_name = id + 'temperature_sensor_client'
    ```

1. Telemeetria jaoks saatke valgusväärtuse asemel DHT sensori poolt loetud temperatuuri väärtus JSON dokumendi omaduses nimega `temperature`:

    ```python
    _, temp = sensor.read()
    telemetry = json.dumps({'temperature' : temp})
    ```

1. Temperatuuri väärtust ei ole vaja väga tihti lugeda - see ei muutu lühikese aja jooksul palju, seega seadke `time.sleep` 10 minutiks:

    ```cpp
    time.sleep(10 * 60);
    ```

    > 💁 Funktsioon `sleep` võtab aja sekundites, seega lihtsuse huvides edastatakse väärtus arvutuse tulemusena. 60 sekundit minutis, seega 10 x (60 sekundit minutis) annab 10-minutilise viivituse.

1. Käivitage kood samamoodi nagu käivitasite koodi eelmises ülesande osas. Kui kasutate virtuaalset IoT seadet, veenduge, et CounterFit rakendus töötab ja niiskuse ning temperatuuri sensorid on loodud õigetele pinidele.

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py
    MQTT connected!
    Sending telemetry  {"temperature": 25}
    Sending telemetry  {"temperature": 25}
    ```

> 💁 Selle koodi leiate [code-publish-temperature/virtual-device](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/virtual-device) kaustast või [code-publish-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/pi) kaustast.

😀 Olete edukalt avaldanud temperatuuri telemeetria oma seadmest.

---

**Lahtiütlus**:  
See dokument on tõlgitud AI tõlketeenuse [Co-op Translator](https://github.com/Azure/co-op-translator) abil. Kuigi püüame tagada täpsust, palume arvestada, et automaatsed tõlked võivad sisaldada vigu või ebatäpsusi. Algne dokument selle algses keeles tuleks pidada autoriteetseks allikaks. Olulise teabe puhul soovitame kasutada professionaalset inimtõlget. Me ei vastuta selle tõlke kasutamisest tulenevate arusaamatuste või valesti tõlgenduste eest.