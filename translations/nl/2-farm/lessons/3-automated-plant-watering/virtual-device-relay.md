<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f8f541ee945545017a51aaf309aa37c3",
  "translation_date": "2025-08-27T21:14:35+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/virtual-device-relay.md",
  "language_code": "nl"
}
-->
# Een relais bedienen - Virtuele IoT-hardware

In dit deel van de les voeg je een relais toe aan je virtuele IoT-apparaat, naast de bodemvochtigheidssensor, en bedien je het op basis van het bodemvochtigheidsniveau.

## Virtuele hardware

Het virtuele IoT-apparaat zal een gesimuleerd Grove-relais gebruiken. Dit zorgt ervoor dat deze oefening hetzelfde blijft als het gebruik van een Raspberry Pi met een fysiek Grove-relais.

Bij een fysiek IoT-apparaat zou het relais een normaal open relais zijn (wat betekent dat het uitgangscircuit open of losgekoppeld is wanneer er geen signaal naar het relais wordt gestuurd). Een dergelijk relais kan uitgangscircuits tot 250V en 10A aan.

### Voeg het relais toe aan CounterFit

Om een virtueel relais te gebruiken, moet je het toevoegen aan de CounterFit-app.

#### Taak

Voeg het relais toe aan de CounterFit-app.

1. Open het project `soil-moisture-sensor` van de vorige les in VS Code als het nog niet geopend is. Je gaat dit project uitbreiden.

1. Zorg ervoor dat de CounterFit-webapp actief is.

1. Maak een relais aan:

    1. In het vak *Create actuator* in het *Actuators*-paneel, open de vervolgkeuzelijst *Actuator type* en selecteer *Relay*.

    1. Stel de *Pin* in op *5*.

    1. Selecteer de knop **Add** om het relais op Pin 5 aan te maken.

    ![De relaisinstellingen](../../../../../translated_images/nl/counterfit-create-relay.fa7c40fd0f2f6afc33b35ea94fcb235085be4861e14e3fe6b9b7bcfc82d1c888.png)

    Het relais wordt aangemaakt en verschijnt in de lijst met actuatoren.

    ![Het aangemaakte relais](../../../../../translated_images/nl/counterfit-relay.bbf74c1dbdc8b9acd983367fcbd06703a402aefef6af54ddb28e11307ba8a12c.png)

## Programmeer het relais

De app voor de bodemvochtigheidssensor kan nu worden geprogrammeerd om het virtuele relais te gebruiken.

### Taak

Programmeur het virtuele apparaat.

1. Open het project `soil-moisture-sensor` van de vorige les in VS Code als het nog niet geopend is. Je gaat dit project uitbreiden.

1. Voeg de volgende code toe aan het bestand `app.py` onder de bestaande imports:

    ```python
    from counterfit_shims_grove.grove_relay import GroveRelay
    ```

    Deze instructie importeert de `GroveRelay` uit de Grove Python-shim-bibliotheken om te communiceren met het virtuele Grove-relais.

1. Voeg de volgende code toe onder de declaratie van de `ADC`-klasse om een instantie van `GroveRelay` te maken:

    ```python
    relay = GroveRelay(5)
    ```

    Dit maakt een relais aan op pin **5**, de pin waaraan je het relais hebt gekoppeld.

1. Om te testen of het relais werkt, voeg je het volgende toe aan de `while True:`-lus:

    ```python
    relay.on()
    time.sleep(.5)
    relay.off()
    ```

    De code schakelt het relais in, wacht 0,5 seconden en schakelt het relais vervolgens uit.

1. Voer de Python-app uit. Het relais schakelt elke 10 seconden in en uit, met een halve seconde vertraging tussen het in- en uitschakelen. Je ziet het virtuele relais in de CounterFit-app sluiten en openen terwijl het relais wordt in- en uitgeschakeld.

    ![Het virtuele relais schakelt in en uit](../../../../../images/virtual-relay-turn-on-off.gif)

## Bedienen van het relais op basis van bodemvochtigheid

Nu het relais werkt, kan het worden bediend op basis van de metingen van de bodemvochtigheid.

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

    Deze code controleert het bodemvochtigheidsniveau van de bodemvochtigheidssensor. Als het boven 450 is, schakelt het het relais in, en als het onder 450 is, schakelt het het relais uit.

    > 💁 Onthoud dat de capacitieve bodemvochtigheidssensor een lagere waarde geeft naarmate er meer vocht in de grond zit, en vice versa.

1. Voer de Python-app uit. Je ziet het relais in- of uitschakelen afhankelijk van de bodemvochtigheidsniveaus. Verander de *Value* of de *Random*-instellingen van de bodemvochtigheidssensor om de waarde te zien veranderen.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 Je kunt deze code vinden in de map [code-relay/virtual-device](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/virtual-device).

😀 Je programma om een virtuele bodemvochtigheidssensor een relais te laten bedienen is geslaagd!

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor kritieke informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.