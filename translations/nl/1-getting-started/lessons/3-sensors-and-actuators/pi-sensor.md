<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "ea733bd0cdf2479e082373f765a08678",
  "translation_date": "2025-08-27T21:49:07+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/pi-sensor.md",
  "language_code": "nl"
}
-->
# Bouw een nachtlampje - Raspberry Pi

In dit deel van de les voeg je een lichtsensor toe aan je Raspberry Pi.

## Hardware

De sensor voor deze les is een **lichtsensor** die een [fotodiode](https://wikipedia.org/wiki/Photodiode) gebruikt om licht om te zetten in een elektrisch signaal. Dit is een analoge sensor die een geheel getal tussen 0 en 1.000 doorgeeft, wat een relatieve hoeveelheid licht aangeeft die niet overeenkomt met een standaard meeteenheid zoals [lux](https://wikipedia.org/wiki/Lux).

De lichtsensor is een externe Grove-sensor en moet worden aangesloten op de Grove Base hat op de Raspberry Pi.

### Sluit de lichtsensor aan

De Grove-lichtsensor die wordt gebruikt om de lichtniveaus te detecteren, moet worden aangesloten op de Raspberry Pi.

#### Taak - sluit de lichtsensor aan

Sluit de lichtsensor aan.

![Een Grove-lichtsensor](../../../../../translated_images/nl/grove-light-sensor.b8127b7c434e632d6bcdb57587a14e9ef69a268a22df95d08628f62b8fa5505c.png)

1. Steek één uiteinde van een Grove-kabel in de aansluiting op de lichtsensormodule. De kabel past maar op één manier.

1. Met de Raspberry Pi uitgeschakeld, sluit je het andere uiteinde van de Grove-kabel aan op de analoge aansluiting gemarkeerd met **A0** op de Grove Base hat die op de Pi is bevestigd. Deze aansluiting is de tweede van rechts, in de rij aansluitingen naast de GPIO-pinnen.

![De Grove-lichtsensor aangesloten op aansluiting A0](../../../../../translated_images/nl/pi-light-sensor.66cc1e31fa48cd7d5f23400d4b2119aa41508275cb7c778053a7923b4e972d7e.png)

## Programmeer de lichtsensor

Het apparaat kan nu worden geprogrammeerd met behulp van de Grove-lichtsensor.

### Taak - programmeer de lichtsensor

Programmeer het apparaat.

1. Zet de Pi aan en wacht tot deze is opgestart.

1. Open het nachtlampjesproject in VS Code dat je hebt gemaakt in het vorige deel van deze opdracht, ofwel direct op de Pi of via de Remote SSH-extensie.

1. Open het bestand `app.py` en verwijder alle code eruit.

1. Voeg de volgende code toe aan het bestand `app.py` om enkele vereiste bibliotheken te importeren:

    ```python
    import time
    from grove.grove_light_sensor_v1_2 import GroveLightSensor
    ```

    De `import time`-regel importeert de `time`-module die later in deze opdracht wordt gebruikt.

    De `from grove.grove_light_sensor_v1_2 import GroveLightSensor`-regel importeert de `GroveLightSensor` uit de Grove Python-bibliotheken. Deze bibliotheek bevat code om te communiceren met een Grove-lichtsensor en is tijdens de Pi-installatie globaal geïnstalleerd.

1. Voeg de volgende code toe na de bovenstaande code om een instantie te maken van de klasse die de lichtsensor beheert:

    ```python
    light_sensor = GroveLightSensor(0)
    ```

    De regel `light_sensor = GroveLightSensor(0)` maakt een instantie van de `GroveLightSensor`-klasse die is verbonden met pin **A0** - de analoge Grove-pin waarop de lichtsensor is aangesloten.

1. Voeg een oneindige lus toe na de bovenstaande code om de lichtsensorwaarde op te vragen en deze naar de console te printen:

    ```python
    while True:
        light = light_sensor.light
        print('Light level:', light)
    ```

    Dit zal het huidige lichtniveau lezen op een schaal van 0-1.023 met behulp van de `light`-eigenschap van de `GroveLightSensor`-klasse. Deze eigenschap leest de analoge waarde van de pin. Deze waarde wordt vervolgens naar de console geprint.

1. Voeg een korte pauze van één seconde toe aan het einde van de `loop`, omdat de lichtniveaus niet continu hoeven te worden gecontroleerd. Een pauze vermindert het energieverbruik van het apparaat.

    ```python
    time.sleep(1)
    ```

1. Voer vanuit de VS Code Terminal het volgende uit om je Python-app te starten:

    ```sh
    python3 app.py
    ```

    Lichtwaarden worden naar de console uitgegeven. Bedek en ontbloot de lichtsensor, en de waarden zullen veranderen:

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py 
    Light level: 634
    Light level: 634
    Light level: 634
    Light level: 230
    Light level: 104
    Light level: 290
    ```

> 💁 Je kunt deze code vinden in de map [code-sensor/pi](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/pi).

😀 Het toevoegen van een sensor aan je nachtlampjesprogramma is gelukt!

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor eventuele misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.