<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4db8a3879a53490513571df2f6cf7641",
  "translation_date": "2025-08-27T21:53:24+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/pi-actuator.md",
  "language_code": "nl"
}
-->
# Bouw een nachtlampje - Raspberry Pi

In dit deel van de les voeg je een LED toe aan je Raspberry Pi en gebruik je deze om een nachtlampje te maken.

## Hardware

Het nachtlampje heeft nu een actuator nodig.

De actuator is een **LED**, een [lichtgevende diode](https://wikipedia.org/wiki/Lichtgevende_diode) die licht uitstraalt wanneer er stroom doorheen loopt. Dit is een digitale actuator met twee toestanden: aan en uit. Het sturen van een waarde van 1 schakelt de LED in, en 0 schakelt deze uit. De LED is een externe Grove-actuator en moet worden aangesloten op de Grove Base Hat op de Raspberry Pi.

De logica van het nachtlampje in pseudocode is:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### Sluit de LED aan

De Grove LED wordt geleverd als een module met een selectie van LEDs, zodat je de kleur kunt kiezen.

#### Taak - sluit de LED aan

Sluit de LED aan.

![Een Grove LED](../../../../../translated_images/nl/grove-led.6c853be93f473cf2c439cfc74bb1064732b22251a83cedf66e62f783f9cc1a79.png)

1. Kies je favoriete LED en steek de pootjes in de twee gaten op de LED-module.

    LEDs zijn lichtgevende diodes, en diodes zijn elektronische componenten die stroom slechts in één richting kunnen geleiden. Dit betekent dat de LED op de juiste manier moet worden aangesloten, anders werkt deze niet.

    Een van de pootjes van de LED is de positieve pin, de andere is de negatieve pin. De LED is niet perfect rond en is aan één kant iets platter. De iets plattere kant is de negatieve pin. Wanneer je de LED op de module aansluit, zorg er dan voor dat het pootje aan de ronde kant is aangesloten op de socket gemarkeerd met **+** aan de buitenkant van de module, en de platte kant is aangesloten op de socket dichter bij het midden van de module.

1. De LED-module heeft een draaiknop waarmee je de helderheid kunt regelen. Draai deze helemaal open door hem met een kleine kruiskopschroevendraaier zo ver mogelijk tegen de klok in te draaien.

1. Steek één uiteinde van een Grove-kabel in de socket op de LED-module. Deze past maar op één manier.

1. Schakel de Raspberry Pi uit en sluit het andere uiteinde van de Grove-kabel aan op de digitale socket gemarkeerd met **D5** op de Grove Base Hat die op de Pi is aangesloten. Deze socket is de tweede van links, in de rij sockets naast de GPIO-pinnen.

![De Grove LED aangesloten op socket D5](../../../../../translated_images/nl/pi-led.97f1d474981dc35d1c7996c7b17de355d3d0a6bc9606d79fa5f89df933415122.png)

## Programmeer het nachtlampje

Het nachtlampje kan nu worden geprogrammeerd met behulp van de Grove-lichtsensor en de Grove LED.

### Taak - programmeer het nachtlampje

Programmeur het nachtlampje.

1. Zet de Pi aan en wacht tot deze is opgestart.

1. Open het nachtlampjesproject in VS Code dat je in het vorige deel van deze opdracht hebt gemaakt, ofwel rechtstreeks op de Pi of via de Remote SSH-extensie.

1. Voeg de volgende code toe aan het bestand `app.py` om een vereiste bibliotheek te importeren. Dit moet bovenaan worden toegevoegd, onder de andere `import`-regels.

    ```python
    from grove.grove_led import GroveLed
    ```

    De regel `from grove.grove_led import GroveLed` importeert de `GroveLed` uit de Grove Python-bibliotheken. Deze bibliotheek bevat code om te communiceren met een Grove LED.

1. Voeg de volgende code toe na de `light_sensor`-declaratie om een instantie te maken van de klasse die de LED beheert:

    ```python
    led = GroveLed(5)
    ```

    De regel `led = GroveLed(5)` maakt een instantie van de `GroveLed`-klasse die verbinding maakt met pin **D5** - de digitale Grove-pin waarop de LED is aangesloten.

    > 💁 Alle sockets hebben unieke pinnummers. Pinnen 0, 2, 4 en 6 zijn analoge pinnen, pinnen 5, 16, 18, 22, 24 en 26 zijn digitale pinnen.

1. Voeg een controle toe binnen de `while`-lus, en vóór de `time.sleep`, om de lichtniveaus te controleren en de LED in of uit te schakelen:

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    Deze code controleert de waarde van `light`. Als deze minder is dan 300, roept het de `on`-methode van de `GroveLed`-klasse aan, die een digitale waarde van 1 naar de LED stuurt, waardoor deze wordt ingeschakeld. Als de lichtwaarde groter dan of gelijk aan 300 is, roept het de `off`-methode aan, die een digitale waarde van 0 stuurt, waardoor de LED wordt uitgeschakeld.

    > 💁 Deze code moet op hetzelfde inspringniveau staan als de regel `print('Light level:', light)` om binnen de while-lus te staan!

    > 💁 Bij het sturen van digitale waarden naar actuatoren is een waarde van 0 gelijk aan 0V, en een waarde van 1 is de maximale spanning voor het apparaat. Voor de Raspberry Pi met Grove-sensoren en -actuatoren is de spanning bij 1 gelijk aan 3,3V.

1. Voer vanuit de VS Code Terminal het volgende uit om je Python-app te starten:

    ```sh
    python3 app.py
    ```

    Lichtwaarden worden naar de console geschreven.

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py 
    Light level: 634
    Light level: 634
    Light level: 634
    Light level: 230
    Light level: 104
    Light level: 290
    ```

1. Bedek en ontbloot de lichtsensor. Merk op hoe de LED oplicht als het lichtniveau 300 of lager is, en uitgaat wanneer het lichtniveau hoger is dan 300.

    > 💁 Als de LED niet aangaat, controleer dan of deze op de juiste manier is aangesloten en of de draaiknop volledig open staat.

![De LED aangesloten op de Pi die aan- en uitgaat afhankelijk van het lichtniveau](../../../../../images/pi-running-assignment-1-1.gif)

> 💁 Je kunt deze code vinden in de map [code-actuator/pi](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/pi).

😀 Je nachtlampjesprogramma is een succes!

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in de oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.