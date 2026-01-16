<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9c640f93263fd9adbfda920739e09feb",
  "translation_date": "2025-08-27T21:54:58+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/virtual-device-actuator.md",
  "language_code": "nl"
}
-->
# Bouw een nachtlampje - Virtuele IoT-hardware

In dit deel van de les voeg je een LED toe aan je virtuele IoT-apparaat en gebruik je deze om een nachtlampje te maken.

## Virtuele hardware

Het nachtlampje heeft één actuator nodig, die wordt aangemaakt in de CounterFit-app.

De actuator is een **LED**. In een fysiek IoT-apparaat zou dit een [lichtemitterende diode](https://wikipedia.org/wiki/Light-emitting_diode) zijn die licht uitstraalt wanneer er stroom doorheen loopt. Dit is een digitale actuator met twee toestanden: aan en uit. Het sturen van een waarde van 1 schakelt de LED in, en 0 schakelt deze uit.

De logica van het nachtlampje in pseudocode is:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### Voeg de actuator toe aan CounterFit

Om een virtuele LED te gebruiken, moet je deze toevoegen aan de CounterFit-app.

#### Taak - voeg de actuator toe aan CounterFit

Voeg de LED toe aan de CounterFit-app.

1. Zorg ervoor dat de CounterFit-webapp draait vanuit het vorige deel van deze opdracht. Zo niet, start deze dan opnieuw en voeg de lichtsensor opnieuw toe.

1. Maak een LED aan:

    1. In het *Create actuator*-vak in het *Actuator*-paneel, open het dropdownmenu van het *Actuator type*-veld en selecteer *LED*.

    1. Stel de *Pin* in op *5*.

    1. Selecteer de knop **Add** om de LED op Pin 5 aan te maken.

    ![De LED-instellingen](../../../../../translated_images/nl/counterfit-create-led.ba9db1c9b8c622a635d6dfae5cdc4e70c2b250635bd4f0601c6cf0bd22b7ba46.png)

    De LED wordt aangemaakt en verschijnt in de lijst met actuatoren.

    ![De aangemaakte LED](../../../../../translated_images/nl/counterfit-led.c0ab02de6d256ad84d9bad4d67a7faa709f0ea83e410cfe9b5561ef0cef30b1c.png)

    Zodra de LED is aangemaakt, kun je de kleur wijzigen met de *Color*-kiezer. Selecteer de knop **Set** om de kleur te wijzigen nadat je deze hebt geselecteerd.

### Programmeer het nachtlampje

Het nachtlampje kan nu worden geprogrammeerd met behulp van de CounterFit-lichtsensor en LED.

#### Taak - programmeer het nachtlampje

Programmeer het nachtlampje.

1. Open het nachtlampjesproject in VS Code dat je hebt aangemaakt in het vorige deel van deze opdracht. Sluit en herstart de terminal om ervoor te zorgen dat deze draait met de virtuele omgeving indien nodig.

1. Open het bestand `app.py`.

1. Voeg de volgende code toe aan het bestand `app.py` om een vereiste bibliotheek te importeren. Dit moet bovenaan worden toegevoegd, onder de andere `import`-regels.

    ```python
    from counterfit_shims_grove.grove_led import GroveLed
    ```

    De regel `from counterfit_shims_grove.grove_led import GroveLed` importeert de `GroveLed` uit de CounterFit Grove shim Python-bibliotheken. Deze bibliotheek bevat code om te communiceren met een LED die is aangemaakt in de CounterFit-app.

1. Voeg de volgende code toe na de `light_sensor`-declaratie om een instantie van de klasse te maken die de LED beheert:

    ```python
    led = GroveLed(5)
    ```

    De regel `led = GroveLed(5)` maakt een instantie van de `GroveLed`-klasse die verbinding maakt met pin **5** - de CounterFit Grove-pin waaraan de LED is gekoppeld.

1. Voeg een controle toe binnen de `while`-lus, en vóór de `time.sleep`, om de lichtniveaus te controleren en de LED in of uit te schakelen:

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    Deze code controleert de waarde van `light`. Als deze minder is dan 300, roept het de `on`-methode van de `GroveLed`-klasse aan, die een digitale waarde van 1 naar de LED stuurt, waardoor deze wordt ingeschakeld. Als de lichtwaarde groter dan of gelijk aan 300 is, roept het de `off`-methode aan, die een digitale waarde van 0 stuurt, waardoor de LED wordt uitgeschakeld.

    > 💁 Deze code moet worden ingesprongen op hetzelfde niveau als de regel `print('Light level:', light)` om binnen de while-lus te staan!

1. Voer vanuit de VS Code Terminal het volgende uit om je Python-app te starten:

    ```sh
    python3 app.py
    ```

    Lichtwaarden worden naar de console geschreven.

    ```output
    (.venv) ➜  GroveTest python3 app.py 
    Light level: 143
    Light level: 244
    Light level: 246
    Light level: 253
    ```

1. Wijzig de *Value*- of *Random*-instellingen om het lichtniveau boven en onder 300 te variëren. De LED zal in- en uitschakelen.

![De LED in de CounterFit-app schakelt in en uit naarmate het lichtniveau verandert](../../../../../images/virtual-device-running-assignment-1-1.gif)

> 💁 Je kunt deze code vinden in de map [code-actuator/virtual-device](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/virtual-device).

😀 Je nachtlampjesprogramma is een succes!

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in de oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor eventuele misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.