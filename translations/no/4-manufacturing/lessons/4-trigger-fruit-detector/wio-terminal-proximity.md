<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "288aebb0c59f7be1d2719b8f9660a313",
  "translation_date": "2025-08-27T20:32:02+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/wio-terminal-proximity.md",
  "language_code": "no"
}
-->
# Oppdag nærhet - Wio Terminal

I denne delen av leksjonen skal du legge til en nærhetssensor på Wio Terminal og lese avstand fra den.

## Maskinvare

Wio Terminal trenger en nærhetssensor.

Sensoren du skal bruke er en [Grove Time of Flight-avstandssensor](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html). Denne sensoren bruker en laseravstandsmåler for å oppdage avstand. Sensoren har et måleområde fra 10 mm til 2000 mm (1 cm - 2 m) og rapporterer verdier innenfor dette området med god nøyaktighet. Avstander over 1000 mm rapporteres som 8109 mm.

Laseravstandsmåleren er på baksiden av sensoren, motsatt side av Grove-kontakten.

Dette er en I2C-sensor.

### Koble til Time of Flight-sensoren

Grove Time of Flight-sensoren kan kobles til Wio Terminal.

#### Oppgave - koble til Time of Flight-sensoren

Koble til Time of Flight-sensoren.

![En Grove Time of Flight-sensor](../../../../../translated_images/no/grove-time-of-flight-sensor.d82ff2165bfded9f485de54d8d07195a6270a602696825fca19f629ddfe94e86.png)

1. Sett den ene enden av en Grove-kabel inn i kontakten på Time of Flight-sensoren. Den kan bare settes inn på én måte.

1. Med Wio Terminal frakoblet fra datamaskinen eller annen strømkilde, koble den andre enden av Grove-kabelen til den venstre Grove-kontakten på Wio Terminal når du ser på skjermen. Dette er kontakten nærmest strømknappen. Dette er en kombinert digital og I2C-kontakt.

![Grove Time of Flight-sensor koblet til venstre kontakt](../../../../../translated_images/no/wio-time-of-flight-sensor.c4c182131d2ea73d.webp)

1. Du kan nå koble Wio Terminal til datamaskinen din.

## Programmer Time of Flight-sensoren

Wio Terminal kan nå programmeres til å bruke den tilkoblede Time of Flight-sensoren.

### Oppgave - programmer Time of Flight-sensoren

1. Opprett et helt nytt Wio Terminal-prosjekt ved hjelp av PlatformIO. Kall dette prosjektet `distance-sensor`. Legg til kode i `setup`-funksjonen for å konfigurere seriellporten.

1. Legg til et bibliotekavhengighet for Seeed Grove Time of Flight-avstandssensorbiblioteket i prosjektets `platformio.ini`-fil:

    ```ini
    lib_deps =
        seeed-studio/Grove Ranging sensor - VL53L0X @ ^1.1.1
    ```

1. I `main.cpp`, legg til følgende under de eksisterende include-direktivene for å erklære en instans av `Seeed_vl53l0x`-klassen for å samhandle med Time of Flight-sensoren:

    ```cpp
    #include "Seeed_vl53l0x.h"
    
    Seeed_vl53l0x VL53L0X;
    ```

1. Legg til følgende nederst i `setup`-funksjonen for å initialisere sensoren:

    ```cpp
    VL53L0X.VL53L0X_common_init();
    VL53L0X.VL53L0X_high_accuracy_ranging_init();
    ```

1. I `loop`-funksjonen, les en verdi fra sensoren:

    ```cpp
    VL53L0X_RangingMeasurementData_t RangingMeasurementData;
    memset(&RangingMeasurementData, 0, sizeof(VL53L0X_RangingMeasurementData_t));

    VL53L0X.PerformSingleRangingMeasurement(&RangingMeasurementData);
    ```

    Denne koden initialiserer en datastruktur for å lese data inn i, og sender den deretter til `PerformSingleRangingMeasurement`-metoden, hvor den fylles med avstandsmålingen.

1. Under dette, skriv ut avstandsmålingen og vent deretter i 1 sekund:

    ```cpp
    Serial.print("Distance = ");
    Serial.print(RangingMeasurementData.RangeMilliMeter);
    Serial.println(" mm");

    delay(1000);
    ```

1. Bygg, last opp og kjør denne koden. Du vil kunne se avstandsmålinger i den serielle monitoren. Plasser objekter nær sensoren, og du vil se avstandsmålingen:

    ```output
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    Avstandsmåleren er på baksiden av sensoren, så sørg for at du bruker riktig side når du måler avstand.

    ![Avstandsmåleren på baksiden av Time of Flight-sensoren peker på en banan](../../../../../translated_images/no/time-of-flight-banana.079921ad8b1496e4.webp)

> 💁 Du finner denne koden i [code-proximity/wio-terminal](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/wio-terminal)-mappen.

😀 Programmet for nærhetssensoren din var en suksess!

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for eventuelle misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.