<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "11f10c6760fb8202cf368422702fdf70",
  "translation_date": "2025-08-27T21:55:57+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/virtual-device-sensor.md",
  "language_code": "nl"
}
-->
# Bouw een nachtlampje - Virtuele IoT-hardware

In dit deel van de les voeg je een lichtsensor toe aan je virtuele IoT-apparaat.

## Virtuele hardware

Het nachtlampje heeft één sensor nodig, die wordt aangemaakt in de CounterFit-app.

De sensor is een **lichtsensor**. In een fysiek IoT-apparaat zou dit een [fotodiode](https://wikipedia.org/wiki/Photodiode) zijn die licht omzet in een elektrisch signaal. Lichtsensoren zijn analoge sensoren die een geheel getal doorgeven dat een relatieve hoeveelheid licht aangeeft. Dit getal is niet gekoppeld aan een standaard meeteenheid zoals [lux](https://wikipedia.org/wiki/Lux).

### Voeg de sensoren toe aan CounterFit

Om een virtuele lichtsensor te gebruiken, moet je deze toevoegen aan de CounterFit-app.

#### Taak - voeg de sensoren toe aan CounterFit

Voeg de lichtsensor toe aan de CounterFit-app.

1. Zorg ervoor dat de CounterFit-webapp draait vanuit het vorige deel van deze opdracht. Zo niet, start deze dan.

1. Maak een lichtsensor aan:

    1. In het vak *Create sensor* in het *Sensors*-paneel, open het dropdownmenu *Sensor type* en selecteer *Light*.

    1. Laat de *Units* ingesteld op *NoUnits*.

    1. Zorg ervoor dat de *Pin* is ingesteld op *0*.

    1. Selecteer de knop **Add** om de lichtsensor aan te maken op Pin 0.

    ![De instellingen van de lichtsensor](../../../../../translated_images/nl/counterfit-create-light-sensor.9f36a5e0d4458d8d554d54b34d2c806d56093d6e49fddcda2d20f6fef7f5cce1.png)

    De lichtsensor wordt aangemaakt en verschijnt in de sensorenlijst.

    ![De aangemaakte lichtsensor](../../../../../translated_images/nl/counterfit-light-sensor.5d0f5584df56b90f6b2561910d9cb20dfbd73eeff2177c238d38f4de54aefae1.png)

## Programmeer de lichtsensor

Het apparaat kan nu worden geprogrammeerd om de ingebouwde lichtsensor te gebruiken.

### Taak - programmeer de lichtsensor

Programmeur het apparaat.

1. Open het nachtlampjesproject in VS Code dat je hebt aangemaakt in het vorige deel van deze opdracht. Sluit en herstart de terminal indien nodig om ervoor te zorgen dat deze draait met de virtuele omgeving.

1. Open het bestand `app.py`.

1. Voeg de volgende code toe aan de bovenkant van het bestand `app.py` bij de andere `import`-verklaringen om enkele vereiste bibliotheken te importeren:

    ```python
    import time
    from counterfit_shims_grove.grove_light_sensor_v1_2 import GroveLightSensor
    ```

    De `import time`-verklaring importeert de Python-module `time`, die later in deze opdracht wordt gebruikt.

    De `from counterfit_shims_grove.grove_light_sensor_v1_2 import GroveLightSensor`-verklaring importeert de `GroveLightSensor` uit de CounterFit Grove shim Python-bibliotheken. Deze bibliotheek bevat code om te communiceren met een lichtsensor die is aangemaakt in de CounterFit-app.

1. Voeg de volgende code toe aan de onderkant van het bestand om instanties te maken van klassen die de lichtsensor beheren:

    ```python
    light_sensor = GroveLightSensor(0)
    ```

    De regel `light_sensor = GroveLightSensor(0)` maakt een instantie van de klasse `GroveLightSensor` die verbinding maakt met pin **0** - de CounterFit Grove-pin waaraan de lichtsensor is gekoppeld.

1. Voeg een oneindige lus toe na de bovenstaande code om de waarde van de lichtsensor op te vragen en deze naar de console te printen:

    ```python
    while True:
        light = light_sensor.light
        print('Light level:', light)
    ```

    Dit leest het huidige lichtniveau met behulp van de eigenschap `light` van de klasse `GroveLightSensor`. Deze eigenschap leest de analoge waarde van de pin. Deze waarde wordt vervolgens naar de console geprint.

1. Voeg een korte pauze van één seconde toe aan het einde van de `while`-lus, omdat de lichtniveaus niet continu hoeven te worden gecontroleerd. Een pauze vermindert het stroomverbruik van het apparaat.

    ```python
    time.sleep(1)
    ```

1. Voer vanuit de VS Code Terminal het volgende uit om je Python-app te starten:

    ```sh
    python3 app.py
    ```

    Lichtwaarden worden naar de console geprint. Aanvankelijk zal deze waarde 0 zijn.

1. Verander vanuit de CounterFit-app de waarde van de lichtsensor die door de app wordt gelezen. Dit kun je op twee manieren doen:

    * Voer een getal in het vak *Value* in voor de lichtsensor en selecteer vervolgens de knop **Set**. Het getal dat je invoert, wordt de waarde die door de sensor wordt geretourneerd.

    * Vink het selectievakje *Random* aan en voer een *Min*- en *Max*-waarde in. Selecteer vervolgens de knop **Set**. Elke keer dat de sensor een waarde leest, zal deze een willekeurig getal tussen *Min* en *Max* lezen.

    De waarden die je instelt, worden naar de console geprint. Verander de *Value* of de *Random*-instellingen om de waarde te laten veranderen.

    ```output
    (.venv) ➜  GroveTest python3 app.py 
    Light level: 143
    Light level: 244
    Light level: 246
    Light level: 253
    ```

> 💁 Je kunt deze code vinden in de map [code-sensor/virtual-device](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/virtual-device).

😀 Je nachtlampjesprogramma is een succes!

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor eventuele misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.