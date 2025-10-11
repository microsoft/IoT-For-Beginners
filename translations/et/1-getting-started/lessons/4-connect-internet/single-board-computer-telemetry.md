<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1226517aae5f5b6f904434670394c688",
  "translation_date": "2025-10-11T11:18:51+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md",
  "language_code": "et"
}
-->
# Juhi oma öölampi Interneti kaudu - Virtuaalne IoT-seade ja Raspberry Pi

Selles õppetunni osas saadad telemeetriat valgustasemetega oma Raspberry Pi või virtuaalse IoT-seadme kaudu MQTT brokerile.

## Telemeetria avaldamine

Järgmine samm on luua JSON-dokument telemeetriaga ja saata see MQTT brokerile.

### Ülesanne

Avalda telemeetria MQTT brokerile.

1. Ava öölambi projekt VS Code'is.

1. Kui kasutad virtuaalset IoT-seadet, veendu, et terminalis töötab virtuaalne keskkond. Kui kasutad Raspberry Pi-d, siis virtuaalset keskkonda ei kasutata.

1. Lisa järgmine import `app.py` faili algusesse:

    ```python
    import json
    ```

   `json` teeki kasutatakse telemeetria kodeerimiseks JSON-dokumendina.

1. Lisa järgmine pärast `client_name` deklaratsiooni:

    ```python
    client_telemetry_topic = id + '/telemetry'
    ```

   `client_telemetry_topic` on MQTT teema, kuhu seade avaldab valgustasemeid.

1. Asenda faili lõpus oleva `while True:` tsükli sisu järgmisega:

    ```python
    while True:
        light = light_sensor.light
        telemetry = json.dumps({'light' : light})

        print("Sending telemetry ", telemetry)
    
        mqtt_client.publish(client_telemetry_topic, telemetry)
    
        time.sleep(5)
    ```

   See kood pakib valgustaseme JSON-dokumenti ja avaldab selle MQTT brokerile. Seejärel tehakse paus, et vähendada sõnumite saatmise sagedust.

1. Käivita kood samamoodi nagu eelmises ülesande osas. Kui kasutad virtuaalset IoT-seadet, veendu, et CounterFit rakendus töötab ja valgusandur ning LED on õigetele pin'idele loodud.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Sending telemetry  {"light": 0}
    Sending telemetry  {"light": 0}
    ```

> 💁 Selle koodi leiad [code-telemetry/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/virtual-device) kaustast või [code-telemetry/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/pi) kaustast.

😀 Sa oled edukalt saatnud telemeetria oma seadmest.

---

**Lahtiütlus**:  
See dokument on tõlgitud AI tõlketeenuse [Co-op Translator](https://github.com/Azure/co-op-translator) abil. Kuigi püüame tagada täpsust, palume arvestada, et automaatsed tõlked võivad sisaldada vigu või ebatäpsusi. Algne dokument selle algses keeles tuleks pidada autoriteetseks allikaks. Olulise teabe puhul soovitame kasutada professionaalset inimtõlget. Me ei vastuta selle tõlke kasutamisest tulenevate arusaamatuste või valesti tõlgenduste eest.