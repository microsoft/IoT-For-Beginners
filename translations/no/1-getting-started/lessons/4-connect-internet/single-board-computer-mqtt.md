<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "90fb93446e03c38f3c0e4009c2471906",
  "translation_date": "2025-08-27T21:53:37+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md",
  "language_code": "no"
}
-->
# Kontroller nattlampen din over Internett - Virtuell IoT-maskinvare og Raspberry Pi

IoT-enheten må kodes for å kommunisere med *test.mosquitto.org* ved hjelp av MQTT for å sende telemetridata med lysensoravlesninger, og motta kommandoer for å kontrollere LED-en.

I denne delen av leksjonen skal du koble din Raspberry Pi eller virtuelle IoT-enhet til en MQTT-broker.

## Installer MQTT-klientpakken

For å kommunisere med MQTT-brokeren må du installere en MQTT-bibliotekpakke via pip, enten på din Pi eller i ditt virtuelle miljø hvis du bruker en virtuell enhet.

### Oppgave

Installer pip-pakken

1. Åpne nattlampe-prosjektet i VS Code.

1. Hvis du bruker en virtuell IoT-enhet, sørg for at terminalen kjører det virtuelle miljøet. Hvis du bruker en Raspberry Pi, vil du ikke bruke et virtuelt miljø.

1. Kjør følgende kommando for å installere MQTT-pakken via pip:

    ```sh
    pip3 install paho-mqtt
    ```

## Kode enheten

Enheten er klar til å kodes.

### Oppgave

Skriv kode for enheten.

1. Legg til følgende import øverst i `app.py`-filen:

    ```python
    import paho.mqtt.client as mqtt
    ```

    Biblioteket `paho.mqtt.client` lar appen din kommunisere via MQTT.

1. Legg til følgende kode etter definisjonene av lysensoren og LED-en:

    ```python
    id = '<ID>'

    client_name = id + 'nightlight_client'
    ```

    Erstatt `<ID>` med en unik ID som vil bli brukt som navnet på denne enhetsklienten, og senere for emnene som denne enheten publiserer og abonnerer på. Broker *test.mosquitto.org* er offentlig og brukes av mange mennesker, inkludert andre studenter som jobber med denne oppgaven. Å ha et unikt MQTT-klientnavn og emnenavn sikrer at koden din ikke kolliderer med andres. Du vil også trenge denne ID-en når du lager serverkoden senere i oppgaven.

    > 💁 Du kan bruke en nettside som [GUIDGen](https://www.guidgen.com) for å generere en unik ID.

    `client_name` er et unikt navn for denne MQTT-klienten på brokeren.

1. Legg til følgende kode under denne nye koden for å opprette et MQTT-klientobjekt og koble til MQTT-brokeren:

    ```python
    mqtt_client = mqtt.Client(client_name)
    mqtt_client.connect('test.mosquitto.org')
    
    mqtt_client.loop_start()

    print("MQTT connected!")
    ```

    Denne koden oppretter klientobjektet, kobler til den offentlige MQTT-brokeren, og starter en behandlingssløyfe som kjører i en bakgrunnstråd og lytter etter meldinger på alle abonnerte emner.

1. Kjør koden på samme måte som du kjørte koden fra forrige del av oppgaven. Hvis du bruker en virtuell IoT-enhet, må du sørge for at CounterFit-appen kjører og at lysensoren og LED-en er opprettet på de riktige pinnene.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Light level: 0
    Light level: 0
    ```

> 💁 Du finner denne koden i mappen [code-mqtt/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/virtual-device) eller mappen [code-mqtt/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/pi).

😀 Du har koblet enheten din til en MQTT-broker med suksess.

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.