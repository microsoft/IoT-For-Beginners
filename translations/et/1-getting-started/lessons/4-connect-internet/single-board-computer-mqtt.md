<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "90fb93446e03c38f3c0e4009c2471906",
  "translation_date": "2025-10-11T11:23:17+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md",
  "language_code": "et"
}
-->
# Juhi oma öölampi Interneti kaudu - Virtuaalne IoT riistvara ja Raspberry Pi

IoT-seade tuleb programmeerida suhtlema *test.mosquitto.org*-iga, kasutades MQTT-d, et saata telemeetria väärtusi valgusanduri näitude põhjal ja vastu võtta käske LED-i juhtimiseks.

Selles õppetunni osas ühendate oma Raspberry Pi või virtuaalse IoT-seadme MQTT maakleriga.

## MQTT kliendipaketi installimine

Et suhelda MQTT maakleriga, peate installima MQTT teegi pip-paketi kas oma Pi-le või virtuaalsesse keskkonda, kui kasutate virtuaalset seadet.

### Ülesanne

Installige pip-pakett

1. Avage öölambi projekt VS Code'is.

1. Kui kasutate virtuaalset IoT-seadet, veenduge, et terminal töötab virtuaalses keskkonnas. Kui kasutate Raspberry Pi-d, siis virtuaalset keskkonda ei kasutata.

1. Käivitage järgmine käsk MQTT pip-paketi installimiseks:

    ```sh
    pip3 install paho-mqtt
    ```

## Seadme programmeerimine

Seade on valmis programmeerimiseks.

### Ülesanne

Kirjutage seadme kood.

1. Lisage järgmine import `app.py` faili algusesse:

    ```python
    import paho.mqtt.client as mqtt
    ```

   `paho.mqtt.client` teek võimaldab teie rakendusel suhelda MQTT kaudu.

1. Lisage järgmine kood pärast valgusanduri ja LED-i definitsioone:

    ```python
    id = '<ID>'

    client_name = id + 'nightlight_client'
    ```

   Asendage `<ID>` unikaalse ID-ga, mida kasutatakse selle seadme kliendi nimeks ja hiljem selle seadme avaldatavate ja tellitavate teemade jaoks. *test.mosquitto.org* maakler on avalik ja seda kasutavad paljud inimesed, sealhulgas teised õpilased, kes teevad seda ülesannet. Unikaalse MQTT kliendi nime ja teemanime kasutamine tagab, et teie kood ei lähe vastuollu kellegi teise omaga. Vajate seda ID-d ka hiljem, kui loote serveri koodi selle ülesande raames.

   > 💁 Võite kasutada veebisaiti nagu [GUIDGen](https://www.guidgen.com), et genereerida unikaalne ID.

   `client_name` on unikaalne nimi sellele MQTT kliendile maakleris.

1. Lisage järgmine kood selle uue koodi alla, et luua MQTT kliendi objekt ja ühendada MQTT maakleriga:

    ```python
    mqtt_client = mqtt.Client(client_name)
    mqtt_client.connect('test.mosquitto.org')
    
    mqtt_client.loop_start()

    print("MQTT connected!")
    ```

   See kood loob kliendi objekti, ühendab avaliku MQTT maakleriga ja käivitab töötlemislingi, mis töötab taustalõimes ja kuulab sõnumeid tellitud teemadel.

1. Käivitage kood samamoodi nagu käivitasite koodi ülesande eelmisest osast. Kui kasutate virtuaalset IoT-seadet, veenduge, et CounterFit rakendus töötab ja valgusandur ning LED on loodud õigetele pinidele.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Light level: 0
    Light level: 0
    ```

> 💁 Selle koodi leiate [code-mqtt/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/virtual-device) kaustast või [code-mqtt/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/pi) kaustast.

😀 Olete edukalt ühendanud oma seadme MQTT maakleriga.

---

**Lahtiütlus**:  
See dokument on tõlgitud AI tõlketeenuse [Co-op Translator](https://github.com/Azure/co-op-translator) abil. Kuigi püüame tagada täpsust, palume arvestada, et automaatsed tõlked võivad sisaldada vigu või ebatäpsusi. Algne dokument selle algses keeles tuleks pidada autoriteetseks allikaks. Olulise teabe puhul soovitame kasutada professionaalset inimtõlget. Me ei vastuta selle tõlke kasutamisest tulenevate arusaamatuste või valesti tõlgenduste eest.