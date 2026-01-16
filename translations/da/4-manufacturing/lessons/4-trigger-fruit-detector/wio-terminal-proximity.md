<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "288aebb0c59f7be1d2719b8f9660a313",
  "translation_date": "2025-08-27T20:31:49+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/wio-terminal-proximity.md",
  "language_code": "da"
}
-->
# Registrer nærhed - Wio Terminal

I denne del af lektionen vil du tilføje en nærhedssensor til din Wio Terminal og aflæse afstand fra den.

## Hardware

Wio Terminalen har brug for en nærhedssensor.

Sensoren, du vil bruge, er en [Grove Time of Flight afstandssensor](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html). Denne sensor bruger et laserafstandsmåler-modul til at registrere afstand. Sensoren har en rækkevidde fra 10mm til 2000mm (1cm - 2m) og rapporterer værdier inden for dette område ret præcist, med afstande over 1000mm rapporteret som 8109mm.

Laserafstandsmåleren sidder på bagsiden af sensoren, den modsatte side af Grove-stikket.

Dette er en I2C-sensor.

### Tilslut Time of Flight-sensoren

Grove Time of Flight-sensoren kan tilsluttes Wio Terminalen.

#### Opgave - tilslut Time of Flight-sensoren

Tilslut Time of Flight-sensoren.

![En Grove Time of Flight-sensor](../../../../../translated_images/da/grove-time-of-flight-sensor.d82ff2165bfded9f485de54d8d07195a6270a602696825fca19f629ddfe94e86.png)

1. Sæt den ene ende af et Grove-kabel i stikket på Time of Flight-sensoren. Det kan kun sættes i på én måde.

1. Med Wio Terminalen frakoblet din computer eller anden strømkilde, tilslut den anden ende af Grove-kablet til det venstre Grove-stik på Wio Terminalen, når du ser på skærmen. Dette er stikket tættest på tænd/sluk-knappen. Dette er et kombineret digitalt og I2C-stik.

![Grove Time of Flight-sensoren tilsluttet det venstre stik](../../../../../translated_images/da/wio-time-of-flight-sensor.c4c182131d2ea73d.webp)

1. Du kan nu tilslutte Wio Terminalen til din computer.

## Programmer Time of Flight-sensoren

Wio Terminalen kan nu programmeres til at bruge den tilsluttede Time of Flight-sensor.

### Opgave - programmer Time of Flight-sensoren

1. Opret et helt nyt Wio Terminal-projekt ved hjælp af PlatformIO. Kald dette projekt `distance-sensor`. Tilføj kode i `setup`-funktionen for at konfigurere den serielle port.

1. Tilføj en biblioteksafhængighed for Seeed Grove Time of Flight afstandssensorbiblioteket til projektets `platformio.ini`-fil:

    ```ini
    lib_deps =
        seeed-studio/Grove Ranging sensor - VL53L0X @ ^1.1.1
    ```

1. I `main.cpp` skal du tilføje følgende under de eksisterende include-direktiver for at erklære en instans af `Seeed_vl53l0x`-klassen til at interagere med Time of Flight-sensoren:

    ```cpp
    #include "Seeed_vl53l0x.h"
    
    Seeed_vl53l0x VL53L0X;
    ```

1. Tilføj følgende nederst i `setup`-funktionen for at initialisere sensoren:

    ```cpp
    VL53L0X.VL53L0X_common_init();
    VL53L0X.VL53L0X_high_accuracy_ranging_init();
    ```

1. I `loop`-funktionen skal du aflæse en værdi fra sensoren:

    ```cpp
    VL53L0X_RangingMeasurementData_t RangingMeasurementData;
    memset(&RangingMeasurementData, 0, sizeof(VL53L0X_RangingMeasurementData_t));

    VL53L0X.PerformSingleRangingMeasurement(&RangingMeasurementData);
    ```

    Denne kode initialiserer en datastruktur til at læse data ind i og sender den derefter til metoden `PerformSingleRangingMeasurement`, hvor den vil blive udfyldt med afstandsmålingen.

1. Skriv derefter afstandsmålingen ud og forsink i 1 sekund:

    ```cpp
    Serial.print("Distance = ");
    Serial.print(RangingMeasurementData.RangeMilliMeter);
    Serial.println(" mm");

    delay(1000);
    ```

1. Byg, upload og kør denne kode. Du vil kunne se afstandsmålinger med den serielle monitor. Placer objekter nær sensoren, og du vil se afstandsmålingen:

    ```output
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    Afstandsmåleren sidder på bagsiden af sensoren, så sørg for at bruge den korrekte side, når du måler afstand.

    ![Afstandsmåleren på bagsiden af Time of Flight-sensoren peger på en banan](../../../../../translated_images/da/time-of-flight-banana.079921ad8b1496e4.webp)

> 💁 Du kan finde denne kode i [code-proximity/wio-terminal](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/wio-terminal)-mappen.

😀 Dit program til nærhedssensoren var en succes!

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på at opnå nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi påtager os ikke ansvar for eventuelle misforståelser eller fejltolkninger, der måtte opstå som følge af brugen af denne oversættelse.