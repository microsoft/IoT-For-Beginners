# Kontrollere et relé - Wio Terminal

I denne delen av leksjonen skal du legge til et relé på din Wio Terminal i tillegg til jordfuktighetssensoren, og styre det basert på jordfuktighetsnivået.

## Maskinvare

Wio Terminal trenger et relé.

Reléet du skal bruke er et [Grove-relé](https://www.seeedstudio.com/Grove-Relay.html), et normalt åpent relé (som betyr at utgangskretsen er åpen, eller frakoblet når det ikke sendes signal til reléet) som kan håndtere utgangskretser opptil 250V og 10A.

Dette er en digital aktuator, så den kobles til digitale pinner på Wio Terminal. Den kombinerte analog/digital-porten er allerede i bruk med jordfuktighetssensoren, så denne kobles til den andre porten, som er en kombinert I2C- og digitalport.

### Koble til reléet

Grove-reléet kan kobles til Wio Terminals digitale port.

#### Oppgave

Koble til reléet.

![Et Grove-relé](../../../../../translated_images/no/grove-relay.d426958ca210fbd0.webp)

1. Sett den ene enden av en Grove-kabel inn i kontakten på reléet. Den vil kun gå inn på én måte.

1. Med Wio Terminal frakoblet fra datamaskinen eller annen strømkilde, koble den andre enden av Grove-kabelen til venstre Grove-kontakt på Wio Terminal når du ser på skjermen. La jordfuktighetssensoren være koblet til den høyre kontakten.

![Grove-reléet koblet til venstre kontakt, og jordfuktighetssensoren koblet til høyre kontakt](../../../../../translated_images/no/wio-relay-and-soil-moisture-sensor.ed722202d42babe0.webp)

1. Sett jordfuktighetssensoren i jorden, hvis den ikke allerede er satt inn fra forrige leksjon.

## Programmer reléet

Wio Terminal kan nå programmeres til å bruke det tilkoblede reléet.

### Oppgave

Programmer enheten.

1. Åpne `soil-moisture-sensor`-prosjektet fra forrige leksjon i VS Code hvis det ikke allerede er åpent. Du vil legge til dette prosjektet.

2. Det finnes ikke et bibliotek for denne aktuatoren - det er en digital aktuator som styres av et høyt eller lavt signal. For å slå den på, sender du et høyt signal til pinnen (3.3V), for å slå den av sender du et lavt signal (0V). Du kan gjøre dette ved å bruke den innebygde Arduino-funksjonen [`digitalWrite`](https://www.arduino.cc/reference/en/language/functions/digital-io/digitalwrite/). Start med å legge til følgende nederst i `setup`-funksjonen for å sette opp den kombinerte I2C/digital-porten som en utgangspinne for å sende spenning til reléet:

    ```cpp
    pinMode(PIN_WIRE_SCL, OUTPUT);
    ```

    `PIN_WIRE_SCL` er portnummeret for den kombinerte I2C/digital-porten.

1. For å teste at reléet fungerer, legg til følgende i `loop`-funksjonen, under den siste `delay`:

    ```cpp
    digitalWrite(PIN_WIRE_SCL, HIGH);
    delay(500);
    digitalWrite(PIN_WIRE_SCL, LOW);
    ```

    Koden sender et høyt signal til pinnen som reléet er koblet til for å slå det på, venter 500ms (et halvt sekund), og sender deretter et lavt signal for å slå reléet av.

1. Bygg og last opp koden til Wio Terminal.

1. Når koden er lastet opp, vil reléet slå seg av og på hvert 10. sekund, med et halvt sekunds forsinkelse mellom av og på. Du vil høre reléet klikke på og deretter klikke av. En LED på Grove-kortet vil lyse når reléet er på, og slukke når reléet er av.

    ![Reléet slår seg av og på](../../../../../images/relay-turn-on-off.gif)

## Kontrollere reléet basert på jordfuktighet

Nå som reléet fungerer, kan det styres basert på jordfuktighetsmålinger.

### Oppgave

Kontroller reléet.

1. Slett de 3 linjene med kode som du la til for å teste reléet. Erstatt dem med følgende kode:

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

    Denne koden sjekker jordfuktighetsnivået fra jordfuktighetssensoren. Hvis det er over 450, slår den på reléet, og slår det av når det går under 450.

    > 💁 Husk at den kapasitive jordfuktighetssensoren leser lavere verdier jo mer fuktighet det er i jorden, og høyere verdier jo tørrere jorden er.

1. Bygg og last opp koden til Wio Terminal.

1. Overvåk enheten via seriell monitor. Du vil se reléet slå seg av eller på avhengig av jordfuktighetsnivået. Prøv i tørr jord, og tilsett deretter vann.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 Du finner denne koden i [code-relay/wio-terminal](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/wio-terminal)-mappen.

😀 Programmet ditt for å kontrollere et relé basert på jordfuktighetssensoren var en suksess!

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.