# Styr en relæ - Raspberry Pi

I denne del af lektionen vil du tilføje et relæ til din Raspberry Pi ud over jordfugtighedssensoren og styre det baseret på jordfugtighedsniveauet.

## Hardware

Raspberry Pi'en har brug for et relæ.

Det relæ, du vil bruge, er et [Grove-relæ](https://www.seeedstudio.com/Grove-Relay.html), et normalt åbent relæ (hvilket betyder, at udgangskredsløbet er åbent eller afbrudt, når der ikke sendes et signal til relæet), som kan håndtere udgangskredsløb op til 250V og 10A.

Dette er en digital aktuator, så det forbindes til en digital pin på Grove Base Hat.

### Tilslut relæet

Grove-relæet kan tilsluttes Raspberry Pi'en.

#### Opgave

Tilslut relæet.

![Et Grove-relæ](../../../../../translated_images/da/grove-relay.d426958ca210fbd0.webp)

1. Sæt den ene ende af et Grove-kabel i stikket på relæet. Det kan kun sættes i på én måde.

1. Med Raspberry Pi'en slukket, tilslut den anden ende af Grove-kablet til det digitale stik markeret **D5** på Grove Base Hat, der er tilsluttet Pi'en. Dette stik er det andet fra venstre på rækken af stik ved siden af GPIO-pinnene. Lad jordfugtighedssensoren være tilsluttet **A0**-stikket.

![Grove-relæet tilsluttet D5-stikket og jordfugtighedssensoren tilsluttet A0-stikket](../../../../../translated_images/da/pi-relay-and-soil-moisture-sensor.02f3198975b8c53e.webp)

1. Sæt jordfugtighedssensoren i jorden, hvis den ikke allerede er det fra den forrige lektion.

## Programmer relæet

Raspberry Pi'en kan nu programmeres til at bruge det tilsluttede relæ.

### Opgave

Programmer enheden.

1. Tænd for Pi'en og vent, indtil den er startet op.

1. Åbn `soil-moisture-sensor`-projektet fra den sidste lektion i VS Code, hvis det ikke allerede er åbent. Du vil tilføje til dette projekt.

1. Tilføj følgende kode til `app.py`-filen under de eksisterende imports:

    ```python
    from grove.grove_relay import GroveRelay
    ```

    Denne erklæring importerer `GroveRelay` fra Grove Python-bibliotekerne for at interagere med Grove-relæet.

1. Tilføj følgende kode under deklarationen af `ADC`-klassen for at oprette en `GroveRelay`-instans:

    ```python
    relay = GroveRelay(5)
    ```

    Dette opretter et relæ ved hjælp af pin **D5**, den digitale pin, du tilsluttede relæet til.

1. For at teste, om relæet fungerer, tilføj følgende til `while True:`-løkken:

    ```python
    relay.on()
    time.sleep(.5)
    relay.off()
    ```

    Koden tænder relæet, venter 0,5 sekunder og slukker derefter relæet.

1. Kør Python-appen. Relæet vil tænde og slukke hvert 10. sekund med en halv sekunds forsinkelse mellem tænding og slukning. Du vil høre relæet klikke, når det tænder og slukker. En LED på Grove-boardet vil lyse, når relæet er tændt, og slukke, når relæet er slukket.

    ![Relæet tænder og slukker](../../../../../images/relay-turn-on-off.gif)

## Styr relæet baseret på jordfugtighed

Nu hvor relæet fungerer, kan det styres som reaktion på aflæsninger fra jordfugtighedssensoren.

### Opgave

Styr relæet.

1. Slet de 3 linjer kode, du tilføjede for at teste relæet. Erstat dem med følgende kode:

    ```python
    if soil_moisture > 450:
        print("Soil Moisture is too low, turning relay on.")
        relay.on()
    else:
        print("Soil Moisture is ok, turning relay off.")
        relay.off()
    ```

    Denne kode tjekker jordfugtighedsniveauet fra jordfugtighedssensoren. Hvis det er over 450, tænder det relæet, og slukker det, når det går under 450.

    > 💁 Husk, at den kapacitive jordfugtighedssensor aflæser: Jo lavere jordfugtighedsniveau, jo mere fugt er der i jorden og omvendt.

1. Kør Python-appen. Du vil se relæet tænde eller slukke afhængigt af jordfugtighedsniveauet. Prøv i tør jord, og tilsæt derefter vand.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 Du kan finde denne kode i [code-relay/pi](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/pi)-mappen.

😀 Dit program til styring af relæet baseret på jordfugtighedssensoren var en succes!

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på at opnå nøjagtighed, skal det bemærkes, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi påtager os ikke ansvar for eventuelle misforståelser eller fejltolkninger, der måtte opstå som følge af brugen af denne oversættelse.