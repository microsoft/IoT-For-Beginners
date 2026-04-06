# Styr et relæ - Wio Terminal

I denne del af lektionen vil du tilføje et relæ til din Wio Terminal ud over jordfugtighedssensoren og styre det baseret på jordfugtighedsniveauet.

## Hardware

Wio Terminalen har brug for et relæ.

Det relæ, du skal bruge, er et [Grove-relæ](https://www.seeedstudio.com/Grove-Relay.html), et normalt åbent relæ (hvilket betyder, at udgangskredsløbet er åbent eller afbrudt, når der ikke sendes et signal til relæet), som kan håndtere udgangskredsløb op til 250V og 10A.

Dette er en digital aktuator, så den tilsluttes til digitale pins på Wio Terminalen. Den kombinerede analog/digital-port er allerede i brug med jordfugtighedssensoren, så denne tilsluttes til den anden port, som er en kombineret I2C- og digitalport.

### Tilslut relæet

Grove-relæet kan tilsluttes Wio Terminalens digitale port.

#### Opgave

Tilslut relæet.

![Et Grove-relæ](../../../../../translated_images/da/grove-relay.d426958ca210fbd0.webp)

1. Sæt den ene ende af et Grove-kabel i stikket på relæet. Det kan kun sættes i på én måde.

1. Med Wio Terminalen frakoblet din computer eller anden strømkilde, tilslut den anden ende af Grove-kablet til den venstre Grove-port på Wio Terminalen, når du ser på skærmen. Lad jordfugtighedssensoren være tilsluttet den højre port.

![Grove-relæet tilsluttet venstre port og jordfugtighedssensoren tilsluttet højre port](../../../../../translated_images/da/wio-relay-and-soil-moisture-sensor.ed722202d42babe0.webp)

1. Sæt jordfugtighedssensoren i jorden, hvis den ikke allerede er det fra den forrige lektion.

## Programmer relæet

Wio Terminalen kan nu programmeres til at bruge det tilsluttede relæ.

### Opgave

Programmer enheden.

1. Åbn projektet `soil-moisture-sensor` fra den sidste lektion i VS Code, hvis det ikke allerede er åbent. Du vil tilføje til dette projekt.

2. Der findes ikke et bibliotek til denne aktuator - det er en digital aktuator, der styres af et højt eller lavt signal. For at tænde den sender du et højt signal til pinnen (3,3V), og for at slukke sender du et lavt signal (0V). Dette kan gøres ved hjælp af den indbyggede Arduino-funktion [`digitalWrite`](https://www.arduino.cc/reference/en/language/functions/digital-io/digitalwrite/). Start med at tilføje følgende til bunden af `setup`-funktionen for at konfigurere den kombinerede I2C/digital-port som en output-pin til at sende spænding til relæet:

    ```cpp
    pinMode(PIN_WIRE_SCL, OUTPUT);
    ```

    `PIN_WIRE_SCL` er portnummeret for den kombinerede I2C/digital-port.

1. For at teste om relæet fungerer, tilføj følgende til `loop`-funktionen under den sidste `delay`:

    ```cpp
    digitalWrite(PIN_WIRE_SCL, HIGH);
    delay(500);
    digitalWrite(PIN_WIRE_SCL, LOW);
    ```

    Koden sender et højt signal til den pin, som relæet er tilsluttet, for at tænde det, venter 500ms (et halvt sekund), og sender derefter et lavt signal for at slukke det.

1. Byg og upload koden til Wio Terminalen.

1. Når koden er uploadet, vil relæet tænde og slukke hvert 10. sekund med et halvt sekunds forsinkelse mellem tænd og sluk. Du vil høre relæet klikke, når det tænder og slukker. En LED på Grove-boardet vil lyse, når relæet er tændt, og slukke, når relæet er slukket.

    ![Relæet tænder og slukker](../../../../../images/relay-turn-on-off.gif)

## Styr relæet ud fra jordfugtighed

Nu hvor relæet fungerer, kan det styres i forhold til aflæsninger fra jordfugtighedssensoren.

### Opgave

Styr relæet.

1. Slet de 3 linjer kode, du tilføjede for at teste relæet. Erstat dem med følgende kode:

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

    Denne kode tjekker jordfugtighedsniveauet fra jordfugtighedssensoren. Hvis det er over 450, tænder den relæet, og slukker det, når det går under 450.

    > 💁 Husk, at den kapacitive jordfugtighedssensor aflæser: Jo lavere jordfugtighedsniveau, desto mere fugt er der i jorden og omvendt.

1. Byg og upload koden til Wio Terminalen.

1. Overvåg enheden via den serielle monitor. Du vil se relæet tænde eller slukke afhængigt af jordfugtighedsniveauet. Prøv i tør jord, og tilsæt derefter vand.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 Du kan finde denne kode i mappen [code-relay/wio-terminal](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/wio-terminal).

😀 Dit program til at styre et relæ med en jordfugtighedssensor var en succes!

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi påtager os ikke ansvar for eventuelle misforståelser eller fejltolkninger, der måtte opstå som følge af brugen af denne oversættelse.