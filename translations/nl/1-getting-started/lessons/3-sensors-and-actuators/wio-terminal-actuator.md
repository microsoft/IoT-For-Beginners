<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "db44083b4dc6fb06eac83c4f16448940",
  "translation_date": "2025-08-27T21:54:14+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/wio-terminal-actuator.md",
  "language_code": "nl"
}
-->
# Bouw een nachtlampje - Wio Terminal

In dit deel van de les voeg je een LED toe aan je Wio Terminal en gebruik je deze om een nachtlampje te maken.

## Hardware

Het nachtlampje heeft nu een actuator nodig.

De actuator is een **LED**, een [lichtgevende diode](https://wikipedia.org/wiki/Lichtgevende_diode) die licht uitstraalt wanneer er stroom doorheen loopt. Dit is een digitale actuator met twee toestanden: aan en uit. Door een waarde van 1 te sturen, gaat de LED aan, en met een waarde van 0 gaat hij uit. Dit is een externe Grove-actuator die moet worden aangesloten op de Wio Terminal.

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

![Een Grove LED](../../../../../translated_images/grove-led.6c853be93f473cf2c439cfc74bb1064732b22251a83cedf66e62f783f9cc1a79.nl.png)

1. Kies je favoriete LED en steek de pootjes in de twee gaten op de LED-module.

    LEDs zijn lichtgevende diodes, en diodes zijn elektronische componenten die stroom slechts in één richting kunnen geleiden. Dit betekent dat de LED op de juiste manier moet worden aangesloten, anders werkt hij niet.

    Een van de pootjes van de LED is de positieve pin, de andere is de negatieve pin. De LED is niet perfect rond en is aan één kant iets platter. De iets plattere kant is de negatieve pin. Zorg ervoor dat het pootje aan de ronde kant is aangesloten op de socket gemarkeerd met **+** aan de buitenkant van de module, en de platte kant is aangesloten op de socket dichter bij het midden van de module.

1. De LED-module heeft een draaiknop waarmee je de helderheid kunt regelen. Draai deze helemaal omhoog door hem met een kleine kruiskopschroevendraaier zo ver mogelijk tegen de klok in te draaien.

1. Steek één uiteinde van een Grove-kabel in de socket op de LED-module. Deze past maar op één manier.

1. Zorg ervoor dat de Wio Terminal is losgekoppeld van je computer of andere stroombron, en sluit het andere uiteinde van de Grove-kabel aan op de rechter Grove-socket van de Wio Terminal, zoals je naar het scherm kijkt. Dit is de socket die het verst van de aan/uit-knop verwijderd is.

    > 💁 De rechter Grove-socket kan worden gebruikt met analoge of digitale sensoren en actuatoren. De linker socket is alleen voor I2C en digitale sensoren en actuatoren.

![De Grove LED aangesloten op de rechter socket](../../../../../translated_images/wio-led.265a1897e72d7f21.nl.png)

## Programmeer het nachtlampje

Het nachtlampje kan nu worden geprogrammeerd met behulp van de ingebouwde lichtsensor en de Grove LED.

### Taak - programmeer het nachtlampje

Programmeer het nachtlampje.

1. Open het nachtlampje-project in VS Code dat je hebt gemaakt in het vorige deel van deze opdracht.

1. Voeg de volgende regel toe onderaan de `setup`-functie:

    ```cpp
    pinMode(D0, OUTPUT);
    ```

    Deze regel configureert de pin die wordt gebruikt om te communiceren met de LED via de Grove-poort.

    De `D0`-pin is de digitale pin voor de rechter Grove-socket. Deze pin wordt ingesteld op `OUTPUT`, wat betekent dat hij is verbonden met een actuator en er gegevens naar de pin worden geschreven.

1. Voeg de volgende code direct vóór de `delay` in de `loop`-functie toe:

    ```cpp
    if (light < 300)
    {
        digitalWrite(D0, HIGH);
    }
    else
    {
        digitalWrite(D0, LOW);
    }
    ```

    Deze code controleert de `light`-waarde. Als deze minder is dan 300, wordt een `HIGH`-waarde naar de `D0`-digitale pin gestuurd. Deze `HIGH` is een waarde van 1, waardoor de LED aangaat. Als de lichtwaarde groter dan of gelijk aan 300 is, wordt een `LOW`-waarde van 0 naar de pin gestuurd, waardoor de LED uitgaat.

    > 💁 Bij het verzenden van digitale waarden naar actuatoren is een LOW-waarde 0V, en een HIGH-waarde is de maximale spanning voor het apparaat. Voor de Wio Terminal is de HIGH-spanning 3,3V.

1. Sluit de Wio Terminal opnieuw aan op je computer en upload de nieuwe code zoals je eerder hebt gedaan.

1. Open de Serial Monitor. Lichtwaarden worden naar de terminal gestuurd.

    ```output
    > Executing task: platformio device monitor <

    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Light value: 4
    Light value: 5
    Light value: 4
    Light value: 158
    Light value: 343
    Light value: 348
    Light value: 344
    ```

1. Bedek en ontbloot de lichtsensor. Merk op hoe de LED aangaat als het lichtniveau 300 of minder is, en uitgaat wanneer het lichtniveau groter dan 300 is.

![De LED aangesloten op de WIO die aan en uit gaat afhankelijk van het lichtniveau](../../../../../images/wio-running-assignment-1-1.gif)

> 💁 Je kunt deze code vinden in de [code-actuator/wio-terminal](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/wio-terminal) map.

😀 Je nachtlampje-programma is een succes!

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in de oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor eventuele misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.