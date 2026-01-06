<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f3c5d8afa2ef6a0b425ef8ff20615cb4",
  "translation_date": "2025-08-27T21:13:05+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/wio-terminal-relay.md",
  "language_code": "nl"
}
-->
# Een relais bedienen - Wio Terminal

In dit deel van de les voeg je een relais toe aan je Wio Terminal, naast de bodemvochtigheidssensor, en bedien je het relais op basis van het bodemvochtigheidsniveau.

## Hardware

De Wio Terminal heeft een relais nodig.

Het relais dat je gebruikt is een [Grove relais](https://www.seeedstudio.com/Grove-Relay.html), een normaal open relais (wat betekent dat het uitgangscircuit open of losgekoppeld is wanneer er geen signaal naar het relais wordt gestuurd) dat uitgangscircuits tot 250V en 10A aankan.

Dit is een digitale actuator, dus het wordt aangesloten op digitale pinnen van de Wio Terminal. De gecombineerde analoge/digitale poort is al in gebruik met de bodemvochtigheidssensor, dus dit relais wordt aangesloten op de andere poort, die een gecombineerde I²C- en digitale poort is.

### Verbind het relais

Het Grove relais kan worden aangesloten op de digitale poort van de Wio Terminal.

#### Taak

Verbind het relais.

![Een Grove relais](../../../../../translated_images/grove-relay.d426958ca210fbd0fb7983d7edc069d46c73a8b0a099d94797bd756f7b6bb6be.nl.png)

1. Steek één uiteinde van een Grove-kabel in de aansluiting op het relais. Het past maar op één manier.

1. Koppel de Wio Terminal los van je computer of andere stroombron en verbind het andere uiteinde van de Grove-kabel met de linker Grove-aansluiting op de Wio Terminal (als je naar het scherm kijkt). Laat de bodemvochtigheidssensor aangesloten op de rechteraansluiting.

![Het Grove relais aangesloten op de linker aansluiting, en de bodemvochtigheidssensor aangesloten op de rechteraansluiting](../../../../../translated_images/wio-relay-and-soil-moisture-sensor.ed722202d42babe0.nl.png)

1. Steek de bodemvochtigheidssensor in de grond, als dit nog niet is gedaan in de vorige les.

## Programmeer het relais

De Wio Terminal kan nu worden geprogrammeerd om het aangesloten relais te gebruiken.

### Taak

Programmeur het apparaat.

1. Open het `soil-moisture-sensor`-project van de vorige les in VS Code als het nog niet open is. Je gaat dit project uitbreiden.

2. Er is geen bibliotheek voor deze actuator - het is een digitale actuator die wordt bediend door een hoog of laag signaal. Om het relais in te schakelen, stuur je een hoog signaal naar de pin (3,3V), en om het uit te schakelen stuur je een laag signaal (0V). Dit kun je doen met de ingebouwde Arduino-functie [`digitalWrite`](https://www.arduino.cc/reference/en/language/functions/digital-io/digitalwrite/). Voeg eerst het volgende toe aan het einde van de `setup`-functie om de gecombineerde I²C/digitale poort in te stellen als een uitgangspin om een spanning naar het relais te sturen:

    ```cpp
    pinMode(PIN_WIRE_SCL, OUTPUT);
    ```

    `PIN_WIRE_SCL` is het poortnummer voor de gecombineerde I²C/digitale poort.

1. Om te testen of het relais werkt, voeg je het volgende toe aan de `loop`-functie, onder de laatste `delay`:

    ```cpp
    digitalWrite(PIN_WIRE_SCL, HIGH);
    delay(500);
    digitalWrite(PIN_WIRE_SCL, LOW);
    ```

    De code stuurt een hoog signaal naar de pin waaraan het relais is verbonden om het in te schakelen, wacht 500ms (een halve seconde), en stuurt vervolgens een laag signaal om het relais uit te schakelen.

1. Bouw en upload de code naar de Wio Terminal.

1. Zodra de code is geüpload, schakelt het relais elke 10 seconden in en uit, met een halve seconde vertraging tussen het in- en uitschakelen. Je hoort het relais klikken bij het in- en uitschakelen. Een LED op de Grove-printplaat gaat branden wanneer het relais is ingeschakeld en gaat uit wanneer het relais is uitgeschakeld.

    ![Het relais schakelt in en uit](../../../../../images/relay-turn-on-off.gif)

## Bedien het relais op basis van bodemvochtigheid

Nu het relais werkt, kan het worden bediend op basis van de metingen van de bodemvochtigheidssensor.

### Taak

Bedien het relais.

1. Verwijder de 3 regels code die je hebt toegevoegd om het relais te testen. Vervang ze door de volgende code:

    ```cpp
    if (soil_moisture > 450)
    {
        Serial.println("Soil Moisture is too low, turning relay on.");
        digitalWrite(PIN_WIRE_SCL, HIGH);
    }
    else
    {
        Serial.println("Soil Moisture is ok, turning relay off.");
        digitalWrite(PIN_WIRE_SCL, LOW);
    }
    ```

    Deze code controleert het bodemvochtigheidsniveau van de bodemvochtigheidssensor. Als het niveau boven de 450 is, schakelt het relais in, en als het onder de 450 komt, schakelt het relais uit.

    > 💁 Onthoud dat de capacitieve bodemvochtigheidssensor een lagere waarde geeft naarmate er meer vocht in de grond zit, en een hogere waarde bij minder vocht.

1. Bouw en upload de code naar de Wio Terminal.

1. Monitor het apparaat via de seriële monitor. Je ziet het relais in- of uitschakelen afhankelijk van het bodemvochtigheidsniveau. Probeer het in droge grond en voeg vervolgens water toe.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 Je kunt deze code vinden in de map [code-relay/wio-terminal](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/wio-terminal).

😀 Je programma om een bodemvochtigheidssensor een relais te laten bedienen is een succes!

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.