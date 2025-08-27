<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "90fb93446e03c38f3c0e4009c2471906",
  "translation_date": "2025-08-27T21:53:24+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md",
  "language_code": "da"
}
-->
# Styr din natlampe over internettet - Virtuel IoT-hardware og Raspberry Pi

IoT-enheden skal kodes til at kommunikere med *test.mosquitto.org* ved hjælp af MQTT for at sende telemetridata med lysfølerens aflæsninger og modtage kommandoer til at styre LED'en.

I denne del af lektionen vil du forbinde din Raspberry Pi eller virtuelle IoT-enhed til en MQTT-broker.

## Installer MQTT-klientpakken

For at kommunikere med MQTT-brokeren skal du installere en MQTT-biblioteks-pip-pakke enten på din Pi eller i dit virtuelle miljø, hvis du bruger en virtuel enhed.

### Opgave

Installer pip-pakken

1. Åbn natlampeprojektet i VS Code.

1. Hvis du bruger en virtuel IoT-enhed, skal du sikre dig, at terminalen kører det virtuelle miljø. Hvis du bruger en Raspberry Pi, vil du ikke bruge et virtuelt miljø.

1. Kør følgende kommando for at installere MQTT-pip-pakken:

    ```sh
    pip3 install paho-mqtt
    ```

## Kod enheden

Enheden er klar til at blive kodet.

### Opgave

Skriv enhedens kode.

1. Tilføj følgende import øverst i `app.py`-filen:

    ```python
    import paho.mqtt.client as mqtt
    ```

    Biblioteket `paho.mqtt.client` gør det muligt for din app at kommunikere via MQTT.

1. Tilføj følgende kode efter definitionerne af lysføleren og LED'en:

    ```python
    id = '<ID>'

    client_name = id + 'nightlight_client'
    ```

    Erstat `<ID>` med en unik ID, der vil blive brugt som navnet på denne enhedsklient og senere til de emner, som denne enhed publicerer og abonnerer på. Brokeren *test.mosquitto.org* er offentlig og bruges af mange mennesker, inklusive andre studerende, der arbejder med denne opgave. At have et unikt MQTT-klientnavn og emnenavne sikrer, at din kode ikke konflikter med andres. Du vil også få brug for denne ID, når du opretter serverkoden senere i denne opgave.

    > 💁 Du kan bruge en hjemmeside som [GUIDGen](https://www.guidgen.com) til at generere en unik ID.

    `client_name` er et unikt navn for denne MQTT-klient på brokeren.

1. Tilføj følgende kode under denne nye kode for at oprette et MQTT-klientobjekt og forbinde til MQTT-brokeren:

    ```python
    mqtt_client = mqtt.Client(client_name)
    mqtt_client.connect('test.mosquitto.org')
    
    mqtt_client.loop_start()

    print("MQTT connected!")
    ```

    Denne kode opretter klientobjektet, forbinder til den offentlige MQTT-broker og starter en behandlingssløjfe, der kører i en baggrundstråd og lytter efter meddelelser på alle abonnerede emner.

1. Kør koden på samme måde, som du kørte koden fra den forrige del af opgaven. Hvis du bruger en virtuel IoT-enhed, skal du sikre dig, at CounterFit-appen kører, og at lysføleren og LED'en er oprettet på de korrekte pins.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Light level: 0
    Light level: 0
    ```

> 💁 Du kan finde denne kode i mappen [code-mqtt/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/virtual-device) eller mappen [code-mqtt/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/pi).

😀 Du har med succes forbundet din enhed til en MQTT-broker.

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på at sikre nøjagtighed, skal det bemærkes, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi påtager os ikke ansvar for eventuelle misforståelser eller fejltolkninger, der måtte opstå som følge af brugen af denne oversættelse.