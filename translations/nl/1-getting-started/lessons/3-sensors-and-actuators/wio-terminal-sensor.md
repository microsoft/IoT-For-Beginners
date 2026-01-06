<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7f4ad0ef54f248b85b92187c94cf9dcb",
  "translation_date": "2025-08-27T21:56:41+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/wio-terminal-sensor.md",
  "language_code": "nl"
}
-->
# Een sensor toevoegen - Wio Terminal

In dit deel van de les ga je de lichtsensor op je Wio Terminal gebruiken.

## Hardware

De sensor voor deze les is een **lichtsensor** die een [fotodiode](https://wikipedia.org/wiki/Photodiode) gebruikt om licht om te zetten in een elektrisch signaal. Dit is een analoge sensor die een geheel getal van 0 tot 1.023 doorgeeft, wat een relatieve hoeveelheid licht aangeeft. Dit wordt niet omgerekend naar een standaard meeteenheid zoals [lux](https://wikipedia.org/wiki/Lux).

De lichtsensor is ingebouwd in de Wio Terminal en is zichtbaar door het doorzichtige plastic venster aan de achterkant.

![De lichtsensor aan de achterkant van de Wio Terminal](../../../../../translated_images/wio-light-sensor.b1f529f3c95f5165.nl.png)

## Programmeer de lichtsensor

Het apparaat kan nu worden geprogrammeerd om de ingebouwde lichtsensor te gebruiken.

### Taak

Programmeur het apparaat.

1. Open het nightlight-project in VS Code dat je in het vorige deel van deze opdracht hebt gemaakt.

1. Voeg de volgende regel toe aan het einde van de `setup`-functie:

    ```cpp
    pinMode(WIO_LIGHT, INPUT);
    ```

    Deze regel configureert de pinnen die worden gebruikt om te communiceren met de sensorhardware.

    De `WIO_LIGHT`-pin is het nummer van de GPIO-pin die is verbonden met de ingebouwde lichtsensor. Deze pin is ingesteld op `INPUT`, wat betekent dat hij is verbonden met een sensor en dat gegevens van de pin worden gelezen.

1. Verwijder de inhoud van de `loop`-functie.

1. Voeg de volgende code toe aan de nu lege `loop`-functie.

    ```cpp
    int light = analogRead(WIO_LIGHT);
    Serial.print("Light value: ");
    Serial.println(light);
    ```

    Deze code leest een analoge waarde van de `WIO_LIGHT`-pin. Dit leest een waarde van 0-1.023 van de ingebouwde lichtsensor. Deze waarde wordt vervolgens naar de seriële poort gestuurd, zodat je deze kunt lezen in de Serial Monitor wanneer deze code wordt uitgevoerd. `Serial.print` schrijft de tekst zonder een nieuwe regel aan het einde, dus elke regel begint met `Light value:` en eindigt met de daadwerkelijke lichtwaarde.

1. Voeg een kleine vertraging van één seconde (1.000 ms) toe aan het einde van de `loop`, omdat de lichtniveaus niet continu hoeven te worden gecontroleerd. Een vertraging vermindert het stroomverbruik van het apparaat.

    ```cpp
    delay(1000);
    ```

1. Sluit de Wio Terminal opnieuw aan op je computer en upload de nieuwe code zoals je eerder hebt gedaan.

1. Open de Serial Monitor. Lichtwaarden worden naar de terminal gestuurd. Bedek en ontbloot de lichtsensor aan de achterkant van de Wio Terminal, en de waarden zullen veranderen.

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

> 💁 Je kunt deze code vinden in de map [code-sensor/wio-terminal](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/wio-terminal).

😀 Het toevoegen van een sensor aan je nightlight-programma is gelukt!

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we ons best doen om nauwkeurigheid te garanderen, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in de oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.