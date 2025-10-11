<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c527ce85d69b1a3875366ec61cbed8aa",
  "translation_date": "2025-10-11T11:20:30+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-commands.md",
  "language_code": "et"
}
-->
# Juhi oma öölampi Interneti kaudu - Virtuaalne IoT riistvara ja Raspberry Pi

Selles õppetunni osas tellid käske, mis saadetakse MQTT brokerilt sinu Raspberry Pi-le või virtuaalsele IoT seadmele.

## Käskude tellimine

Järgmine samm on tellida käske, mis saadetakse MQTT brokerilt, ja neile vastata.

### Ülesanne

Telli käsud.

1. Ava öölambi projekt VS Code'is.

1. Kui kasutad virtuaalset IoT seadet, veendu, et terminalis töötab virtuaalne keskkond. Kui kasutad Raspberry Pi-d, siis virtuaalset keskkonda ei kasutata.

1. Lisa järgmine kood pärast `client_telemetry_topic` määratlusi:

    ```python
    server_command_topic = id + '/commands'
    ```

   `server_command_topic` on MQTT teema, millele seade tellib LED käskude vastuvõtmiseks.

1. Lisa järgmine kood vahetult enne põhitsüklit, pärast `mqtt_client.loop_start()` rida:

    ```python
    def handle_command(client, userdata, message):
        payload = json.loads(message.payload.decode())
        print("Message received:", payload)
    
        if payload['led_on']:
            led.on()
        else:
            led.off()
    
    mqtt_client.subscribe(server_command_topic)
    mqtt_client.on_message = handle_command
    ```

   See kood määratleb funktsiooni `handle_command`, mis loeb sõnumi JSON dokumendina ja otsib `led_on` omaduse väärtust. Kui see on määratud `True`, lülitatakse LED sisse, vastasel juhul lülitatakse see välja.

   MQTT klient tellib teema, millele server saadab sõnumeid, ja määrab funktsiooni `handle_command`, mida kutsutakse, kui sõnum vastu võetakse.

   > 💁 `on_message` käsitleja kutsutakse kõigi tellitud teemade puhul. Kui hiljem kirjutad koodi, mis kuulab mitut teemat, saad sõnumi objekti kaudu, mis edastatakse käsitleja funktsioonile, teada, millisele teemale sõnum saadeti.

1. Käivita kood samamoodi nagu eelmise ülesande osa kood. Kui kasutad virtuaalset IoT seadet, veendu, et CounterFit rakendus töötab ja valgusandur ning LED on loodud õigetele pinidele.

1. Kohanda füüsilise või virtuaalse seadme tuvastatud valguse taset. Terminalis kuvatakse vastuvõetud sõnumid ja saadetud käsud. LED lülitatakse sisse ja välja sõltuvalt valguse tasemest.

> 💁 Selle koodi leiad [code-commands/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/virtual-device) kaustast või [code-commands/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/pi) kaustast.

😀 Oled edukalt kodeerinud oma seadme reageerima MQTT brokerilt saadetud käskudele.

---

**Lahtiütlus**:  
See dokument on tõlgitud AI tõlketeenuse [Co-op Translator](https://github.com/Azure/co-op-translator) abil. Kuigi püüame tagada täpsust, palume arvestada, et automaatsed tõlked võivad sisaldada vigu või ebatäpsusi. Algne dokument selle algses keeles tuleks pidada autoriteetseks allikaks. Olulise teabe puhul soovitame kasutada professionaalset inimtõlget. Me ei vastuta selle tõlke kasutamisest tulenevate arusaamatuste või valesti tõlgenduste eest.