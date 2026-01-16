<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "66b81165e60f8f169bd52a401b6a0f8b",
  "translation_date": "2025-08-27T21:13:51+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/pi-relay.md",
  "language_code": "nl"
}
-->
# Een relais bedienen - Raspberry Pi

In dit deel van de les voeg je een relais toe aan je Raspberry Pi, naast de bodemvochtigheidssensor, en bedien je het relais op basis van het bodemvochtigheidsniveau.

## Hardware

De Raspberry Pi heeft een relais nodig.

Het relais dat je gebruikt is een [Grove relais](https://www.seeedstudio.com/Grove-Relay.html), een normaal-open relais (wat betekent dat het uitgangscircuit open of losgekoppeld is wanneer er geen signaal naar het relais wordt gestuurd) dat uitgangscircuits tot 250V en 10A aankan.

Dit is een digitale actuator, dus het wordt aangesloten op een digitale pin op de Grove Base Hat.

### Verbind het relais

Het Grove relais kan worden aangesloten op de Raspberry Pi.

#### Taak

Verbind het relais.

![Een Grove relais](../../../../../translated_images/nl/grove-relay.d426958ca210fbd0fb7983d7edc069d46c73a8b0a099d94797bd756f7b6bb6be.png)

1. Steek één uiteinde van een Grove-kabel in de aansluiting op het relais. Het past maar op één manier.

1. Schakel de Raspberry Pi uit en verbind het andere uiteinde van de Grove-kabel met de digitale aansluiting gemarkeerd als **D5** op de Grove Base Hat die aan de Pi is bevestigd. Deze aansluiting is de tweede van links, op de rij aansluitingen naast de GPIO-pinnen. Laat de bodemvochtigheidssensor aangesloten op de **A0**-aansluiting.

![Het Grove relais aangesloten op de D5-aansluiting en de bodemvochtigheidssensor aangesloten op de A0-aansluiting](../../../../../translated_images/nl/pi-relay-and-soil-moisture-sensor.02f3198975b8c53e69ec716cd2719ce117700bd1fc933eaf93476c103c57939b.png)

1. Steek de bodemvochtigheidssensor in de grond, als dit nog niet is gedaan in de vorige les.

## Programmeer het relais

De Raspberry Pi kan nu worden geprogrammeerd om het aangesloten relais te gebruiken.

### Taak

Programmeur het apparaat.

1. Zet de Pi aan en wacht tot deze is opgestart.

1. Open het `soil-moisture-sensor`-project van de vorige les in VS Code als het nog niet is geopend. Je gaat dit project uitbreiden.

1. Voeg de volgende code toe aan het `app.py`-bestand onder de bestaande imports:

    ```python
    from grove.grove_relay import GroveRelay
    ```

    Deze instructie importeert de `GroveRelay` uit de Grove Python-bibliotheken om te communiceren met het Grove relais.

1. Voeg de volgende code toe onder de declaratie van de `ADC`-klasse om een `GroveRelay`-instantie te maken:

    ```python
    relay = GroveRelay(5)
    ```

    Dit maakt een relais aan dat gebruikmaakt van pin **D5**, de digitale pin waarop je het relais hebt aangesloten.

1. Om te testen of het relais werkt, voeg je het volgende toe aan de `while True:`-lus:

    ```python
    relay.on()
    time.sleep(.5)
    relay.off()
    ```

    De code schakelt het relais in, wacht 0,5 seconden en schakelt het relais vervolgens uit.

1. Voer de Python-app uit. Het relais schakelt elke 10 seconden in en uit, met een halve seconde vertraging tussen het in- en uitschakelen. Je hoort het relais klikken bij het in- en uitschakelen. Een LED op de Grove-board licht op wanneer het relais aan staat en gaat uit wanneer het relais uit staat.

    ![Het relais schakelt in en uit](../../../../../images/relay-turn-on-off.gif)

## Bedien het relais op basis van bodemvochtigheid

Nu het relais werkt, kan het worden bediend op basis van de metingen van de bodemvochtigheidssensor.

### Taak

Bedien het relais.

1. Verwijder de 3 regels code die je hebt toegevoegd om het relais te testen. Vervang ze door de volgende code:

    ```python
    if soil_moisture > 450:
        print("Soil Moisture is too low, turning relay on.")
        relay.on()
    else:
        print("Soil Moisture is ok, turning relay off.")
        relay.off()
    ```

    Deze code controleert het bodemvochtigheidsniveau van de bodemvochtigheidssensor. Als het niveau boven de 450 is, schakelt het relais in, en schakelt het uit wanneer het onder de 450 komt.

    > 💁 Onthoud dat de capacitieve bodemvochtigheidssensor leest: hoe lager het bodemvochtigheidsniveau, hoe meer vocht er in de grond zit, en vice versa.

1. Voer de Python-app uit. Je ziet het relais in- of uitschakelen afhankelijk van het bodemvochtigheidsniveau. Probeer het in droge grond en voeg vervolgens water toe.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 Je kunt deze code vinden in de map [code-relay/pi](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/pi).

😀 Je programma om een bodemvochtigheidssensor een relais te laten bedienen is een succes!

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.