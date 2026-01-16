<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2bf65f162bcebd35fbcba5fd245afac4",
  "translation_date": "2025-08-27T21:27:09+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/virtual-device-soil-moisture.md",
  "language_code": "nl"
}
-->
# Meet bodemvochtigheid - Virtuele IoT-hardware

In dit deel van de les voeg je een capacitieve bodemvochtigheidssensor toe aan je virtuele IoT-apparaat en lees je waarden ervan uit.

## Virtuele hardware

Het virtuele IoT-apparaat zal gebruik maken van een gesimuleerde Grove capacitieve bodemvochtigheidssensor. Dit zorgt ervoor dat deze labopdracht hetzelfde blijft als het gebruik van een Raspberry Pi met een fysieke Grove capacitieve bodemvochtigheidssensor.

Bij een fysiek IoT-apparaat zou de bodemvochtigheidssensor een capacitieve sensor zijn die bodemvochtigheid meet door de capaciteit van de bodem te detecteren, een eigenschap die verandert naarmate de bodemvochtigheid verandert. Naarmate de bodemvochtigheid toeneemt, neemt de spanning af.

Dit is een analoge sensor en maakt gebruik van een gesimuleerde 10-bits ADC om een waarde van 1-1.023 te rapporteren.

### Voeg de bodemvochtigheidssensor toe aan CounterFit

Om een virtuele bodemvochtigheidssensor te gebruiken, moet je deze toevoegen aan de CounterFit-app.

#### Taak - Voeg de bodemvochtigheidssensor toe aan CounterFit

Voeg de bodemvochtigheidssensor toe aan de CounterFit-app.

1. Maak een nieuwe Python-app op je computer in een map genaamd `soil-moisture-sensor` met een enkel bestand genaamd `app.py` en een Python virtuele omgeving, en voeg de CounterFit pip-pakketten toe.

    > ⚠️ Je kunt [de instructies voor het maken en instellen van een CounterFit Python-project in les 1 raadplegen indien nodig](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Zorg ervoor dat de CounterFit-webapp actief is.

1. Maak een bodemvochtigheidssensor:

    1. In het *Create sensor*-vak in het *Sensors*-paneel, open het dropdownmenu *Sensor type* en selecteer *Soil Moisture*.

    1. Laat de *Units* ingesteld op *NoUnits*.

    1. Zorg ervoor dat de *Pin* is ingesteld op *0*.

    1. Selecteer de knop **Add** om de *Soil Moisture*-sensor op Pin 0 te maken.

    ![De instellingen van de bodemvochtigheidssensor](../../../../../translated_images/nl/counterfit-create-soil-moisture-sensor.35266135a5e0ae68b29a684d7db0d2933a8098b2307d197f7c71577b724603aa.png)

    De bodemvochtigheidssensor wordt aangemaakt en verschijnt in de sensorenlijst.

    ![De aangemaakte bodemvochtigheidssensor](../../../../../translated_images/nl/counterfit-soil-moisture-sensor.81742b2de0e9de60a3b3b9a2ff8ecc686d428eb6d71820f27a693be26e5aceee.png)

## Programmeer de bodemvochtigheidssensor-app

De bodemvochtigheidssensor-app kan nu worden geprogrammeerd met behulp van de CounterFit-sensoren.

### Taak - Programmeer de bodemvochtigheidssensor-app

Programmeer de bodemvochtigheidssensor-app.

1. Zorg ervoor dat de `soil-moisture-sensor`-app geopend is in VS Code.

1. Open het bestand `app.py`.

1. Voeg de volgende code toe aan de bovenkant van `app.py` om de app te verbinden met CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Voeg de volgende code toe aan het bestand `app.py` om enkele vereiste bibliotheken te importeren:

    ```python
    import time
    from counterfit_shims_grove.adc import ADC
    ```

    De `import time`-verklaring importeert de `time`-module die later in deze opdracht zal worden gebruikt.

    De `from counterfit_shims_grove.adc import ADC`-verklaring importeert de `ADC`-klasse om te communiceren met een virtuele analoog-naar-digitaal converter die kan worden verbonden met een CounterFit-sensor.

1. Voeg de volgende code hieronder toe om een instantie van de `ADC`-klasse te maken:

    ```python
    adc = ADC()
    ```

1. Voeg een oneindige lus toe die waarden leest van deze ADC op pin 0 en het resultaat naar de console schrijft. Deze lus kan vervolgens 10 seconden pauzeren tussen de metingen.

    ```python
    while True:
        soil_moisture = adc.read(0)
        print("Soil moisture:", soil_moisture)
    
        time.sleep(10)
    ```

1. Verander vanuit de CounterFit-app de waarde van de bodemvochtigheidssensor die door de app wordt gelezen. Je kunt dit op twee manieren doen:

    * Voer een getal in het *Value*-vak van de bodemvochtigheidssensor in en selecteer de knop **Set**. Het getal dat je invoert zal de waarde zijn die door de sensor wordt geretourneerd.

    * Vink het *Random*-selectievakje aan en voer een *Min*- en *Max*-waarde in, en selecteer vervolgens de knop **Set**. Elke keer dat de sensor een waarde leest, zal deze een willekeurig getal tussen *Min* en *Max* lezen.

1. Voer de Python-app uit. Je zult de bodemvochtigheidsmetingen naar de console zien geschreven worden. Verander de *Value*- of *Random*-instellingen om de waarde te zien veranderen.

    ```output
    (.venv) ➜ soil-moisture-sensor $ python app.py 
    Soil moisture: 615
    Soil moisture: 612
    Soil moisture: 498
    Soil moisture: 493
    Soil moisture: 490
    Soil Moisture: 388
    ```

> 💁 Je kunt deze code vinden in de [code/virtual-device](../../../../../2-farm/lessons/2-detect-soil-moisture/code/virtual-device)-map.

😀 Je bodemvochtigheidssensorprogramma was een succes!

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor eventuele misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.