<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0d55caa8c23d73635b7559102cd17b8a",
  "translation_date": "2025-08-27T22:29:10+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/wio-terminal-soil-moisture.md",
  "language_code": "no"
}
-->
# Mål jordfuktighet - Wio Terminal

I denne delen av leksjonen skal du legge til en kapasitansbasert jordfuktighetssensor til din Wio Terminal og lese verdier fra den.

## Maskinvare

Wio Terminal trenger en kapasitansbasert jordfuktighetssensor.

Sensoren du skal bruke er en [Kapasitansbasert jordfuktighetssensor](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html), som måler jordfuktighet ved å oppdage jordens kapasitans, en egenskap som endrer seg når jordfuktigheten endres. Når jordfuktigheten øker, synker spenningen.

Dette er en analog sensor, så den kobles til analoge pinner på Wio Terminal, og bruker en innebygd ADC for å generere en verdi fra 0-1 023.

### Koble til jordfuktighetssensoren

Grove jordfuktighetssensoren kan kobles til Wio Terminals konfigurerbare analog/digital-port.

#### Oppgave - koble til jordfuktighetssensoren

Koble til jordfuktighetssensoren.

![En Grove jordfuktighetssensor](../../../../../translated_images/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78be5cc5a07839385fd6718857f31b5bf5ad3d0c73c83b2f0ef.no.png)

1. Sett den ene enden av en Grove-kabel inn i kontakten på jordfuktighetssensoren. Den kan bare settes inn på én måte.

1. Med Wio Terminal frakoblet fra datamaskinen eller annen strømkilde, koble den andre enden av Grove-kabelen til den høyre Grove-kontakten på Wio Terminal når du ser på skjermen. Dette er kontakten lengst unna strømknappen.

![Grove jordfuktighetssensor koblet til høyre kontakt](../../../../../translated_images/wio-soil-moisture-sensor.46919b61c3f6cb74.no.png)

1. Sett jordfuktighetssensoren inn i jorden. Den har en "høyeste posisjonslinje" - en hvit linje på tvers av sensoren. Sett sensoren inn opp til, men ikke forbi, denne linjen.

![Grove jordfuktighetssensor i jord](../../../../../translated_images/soil-moisture-sensor-in-soil.bfad91002bda5e96.no.png)

1. Du kan nå koble Wio Terminal til datamaskinen din.

## Programmer jordfuktighetssensoren

Wio Terminal kan nå programmeres til å bruke den tilkoblede jordfuktighetssensoren.

### Oppgave - programmer jordfuktighetssensoren

Programmer enheten.

1. Opprett et helt nytt Wio Terminal-prosjekt ved hjelp av PlatformIO. Kall dette prosjektet `soil-moisture-sensor`. Legg til kode i `setup`-funksjonen for å konfigurere seriellporten.

    > ⚠️ Du kan se [instruksjonene for å opprette et PlatformIO-prosjekt i prosjekt 1, leksjon 1 hvis nødvendig](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project).

1. Det finnes ikke et bibliotek for denne sensoren, men du kan lese fra den analoge pinnen ved å bruke den innebygde Arduino-funksjonen [`analogRead`](https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/). Start med å konfigurere den analoge pinnen som inngang slik at verdier kan leses fra den ved å legge til følgende i `setup`-funksjonen.

    ```cpp
    pinMode(A0, INPUT);
    ```

    Dette setter `A0`-pinnen, den kombinerte analog/digital-pinnen, som en inngangspinne som spenning kan leses fra.

1. Legg til følgende i `loop`-funksjonen for å lese spenningen fra denne pinnen:

    ```cpp
    int soil_moisture = analogRead(A0);
    ```

1. Under denne koden, legg til følgende kode for å skrive ut verdien til seriellporten:

    ```cpp
    Serial.print("Soil Moisture: ");
    Serial.println(soil_moisture);
    ```

1. Til slutt, legg til en forsinkelse på 10 sekunder på slutten:

    ```cpp
    delay(10000);
    ```

1. Bygg og last opp koden til Wio Terminal.

    > ⚠️ Du kan se [instruksjonene for å opprette et PlatformIO-prosjekt i prosjekt 1, leksjon 1 hvis nødvendig](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app).

1. Når koden er lastet opp, kan du overvåke jordfuktigheten ved hjelp av seriell monitor. Tilsett litt vann i jorden, eller fjern sensoren fra jorden, og se verdien endre seg.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Soil Moisture: 526
    Soil Moisture: 529
    Soil Moisture: 521
    Soil Moisture: 494
    Soil Moisture: 454
    Soil Moisture: 456
    Soil Moisture: 395
    Soil Moisture: 388
    Soil Moisture: 394
    Soil Moisture: 391
    ```

    I eksempelet over kan du se spenningen synke når vann tilsettes.

> 💁 Du finner denne koden i [code/wio-terminal](../../../../../2-farm/lessons/2-detect-soil-moisture/code/wio-terminal)-mappen.

😀 Programmet for jordfuktighetssensoren din var en suksess!

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.