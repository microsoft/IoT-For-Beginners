<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "90fb93446e03c38f3c0e4009c2471906",
  "translation_date": "2025-08-27T21:46:34+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md",
  "language_code": "nl"
}
-->
# Beheer je nachtlampje via het internet - Virtuele IoT-hardware en Raspberry Pi

Het IoT-apparaat moet worden geprogrammeerd om te communiceren met *test.mosquitto.org* via MQTT. Het apparaat stuurt telemetriegegevens met de lichtsensorwaarden en ontvangt opdrachten om de LED te bedienen.

In dit deel van de les verbind je je Raspberry Pi of virtuele IoT-apparaat met een MQTT-broker.

## Installeer het MQTT-clientpakket

Om te communiceren met de MQTT-broker, moet je een MQTT-bibliotheek pip-pakket installeren, ofwel op je Raspberry Pi, of in je virtuele omgeving als je een virtueel apparaat gebruikt.

### Taak

Installeer het pip-pakket

1. Open het nachtlampjesproject in VS Code.

1. Als je een virtueel IoT-apparaat gebruikt, zorg er dan voor dat de terminal de virtuele omgeving uitvoert. Als je een Raspberry Pi gebruikt, werk je niet met een virtuele omgeving.

1. Voer de volgende opdracht uit om het MQTT pip-pakket te installeren:

    ```sh
    pip3 install paho-mqtt
    ```

## Programmeer het apparaat

Het apparaat is klaar om geprogrammeerd te worden.

### Taak

Schrijf de apparaatcode.

1. Voeg de volgende import toe aan de bovenkant van het bestand `app.py`:

    ```python
    import paho.mqtt.client as mqtt
    ```

    De bibliotheek `paho.mqtt.client` stelt je app in staat om via MQTT te communiceren.

1. Voeg de volgende code toe na de definities van de lichtsensor en LED:

    ```python
    id = '<ID>'

    client_name = id + 'nightlight_client'
    ```

    Vervang `<ID>` door een unieke ID die zal worden gebruikt als de naam van deze apparaatclient, en later voor de onderwerpen waarop dit apparaat publiceert en zich abonneert. De *test.mosquitto.org* broker is openbaar en wordt door veel mensen gebruikt, waaronder andere studenten die aan deze opdracht werken. Het hebben van een unieke MQTT-clientnaam en onderwerpnamen zorgt ervoor dat je code niet in conflict komt met die van anderen. Je hebt deze ID ook nodig wanneer je later in deze opdracht de servercode maakt.

    > 💁 Je kunt een website zoals [GUIDGen](https://www.guidgen.com) gebruiken om een unieke ID te genereren.

    De `client_name` is een unieke naam voor deze MQTT-client op de broker.

1. Voeg de volgende code toe onder deze nieuwe code om een MQTT-clientobject te maken en verbinding te maken met de MQTT-broker:

    ```python
    mqtt_client = mqtt.Client(client_name)
    mqtt_client.connect('test.mosquitto.org')
    
    mqtt_client.loop_start()

    print("MQTT connected!")
    ```

    Deze code maakt het clientobject, maakt verbinding met de openbare MQTT-broker, en start een verwerkingslus die in een achtergrondthread berichten beluistert op alle geabonneerde onderwerpen.

1. Voer de code uit op dezelfde manier als je de code uit het vorige deel van de opdracht uitvoerde. Als je een virtueel IoT-apparaat gebruikt, zorg er dan voor dat de CounterFit-app actief is en dat de lichtsensor en LED zijn aangemaakt op de juiste pinnen.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Light level: 0
    Light level: 0
    ```

> 💁 Je kunt deze code vinden in de map [code-mqtt/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/virtual-device) of de map [code-mqtt/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/pi).

😀 Je hebt je apparaat met succes verbonden met een MQTT-broker.

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.