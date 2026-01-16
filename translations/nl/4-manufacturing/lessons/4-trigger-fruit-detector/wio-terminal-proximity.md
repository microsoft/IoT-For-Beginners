<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "288aebb0c59f7be1d2719b8f9660a313",
  "translation_date": "2025-08-27T20:57:11+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/wio-terminal-proximity.md",
  "language_code": "nl"
}
-->
# Detecteer nabijheid - Wio Terminal

In dit deel van de les voeg je een nabijheidssensor toe aan je Wio Terminal en lees je de afstand ervan af.

## Hardware

De Wio Terminal heeft een nabijheidssensor nodig.

De sensor die je gaat gebruiken is een [Grove Time of Flight afstandssensor](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html). Deze sensor gebruikt een laserafstandsmodule om afstanden te detecteren. De sensor heeft een bereik van 10mm tot 2000mm (1cm - 2m) en rapporteert waarden binnen dat bereik vrij nauwkeurig, waarbij afstanden boven 1000mm worden gerapporteerd als 8109mm.

De laserafstandsmeter bevindt zich aan de achterkant van de sensor, tegenover de Grove-aansluiting.

Dit is een I²C-sensor.

### Verbind de Time of Flight-sensor

De Grove Time of Flight-sensor kan worden aangesloten op de Wio Terminal.

#### Taak - verbind de Time of Flight-sensor

Verbind de Time of Flight-sensor.

![Een Grove Time of Flight-sensor](../../../../../translated_images/nl/grove-time-of-flight-sensor.d82ff2165bfded9f485de54d8d07195a6270a602696825fca19f629ddfe94e86.png)

1. Steek één uiteinde van een Grove-kabel in de aansluiting op de Time of Flight-sensor. De kabel past maar op één manier.

1. Terwijl de Wio Terminal is losgekoppeld van je computer of andere stroombron, verbind je het andere uiteinde van de Grove-kabel met de linker Grove-aansluiting op de Wio Terminal, zoals je naar het scherm kijkt. Dit is de aansluiting die het dichtst bij de aan/uit-knop zit. Dit is een gecombineerde digitale en I²C-aansluiting.

![De Grove Time of Flight-sensor verbonden met de linker aansluiting](../../../../../translated_images/nl/wio-time-of-flight-sensor.c4c182131d2ea73d.webp)

1. Je kunt nu de Wio Terminal aansluiten op je computer.

## Programmeer de Time of Flight-sensor

De Wio Terminal kan nu worden geprogrammeerd om de aangesloten Time of Flight-sensor te gebruiken.

### Taak - programmeer de Time of Flight-sensor

1. Maak een gloednieuw Wio Terminal-project met PlatformIO. Noem dit project `distance-sensor`. Voeg code toe in de `setup`-functie om de seriële poort te configureren.

1. Voeg een bibliotheekafhankelijkheid toe voor de Seeed Grove Time of Flight-afstandssensorbibliotheek aan het `platformio.ini`-bestand van het project:

    ```ini
    lib_deps =
        seeed-studio/Grove Ranging sensor - VL53L0X @ ^1.1.1
    ```

1. Voeg in `main.cpp` het volgende toe onder de bestaande include-directieven om een instantie van de `Seeed_vl53l0x`-klasse te declareren om met de Time of Flight-sensor te communiceren:

    ```cpp
    #include "Seeed_vl53l0x.h"
    
    Seeed_vl53l0x VL53L0X;
    ```

1. Voeg het volgende toe aan de onderkant van de `setup`-functie om de sensor te initialiseren:

    ```cpp
    VL53L0X.VL53L0X_common_init();
    VL53L0X.VL53L0X_high_accuracy_ranging_init();
    ```

1. Lees in de `loop`-functie een waarde van de sensor:

    ```cpp
    VL53L0X_RangingMeasurementData_t RangingMeasurementData;
    memset(&RangingMeasurementData, 0, sizeof(VL53L0X_RangingMeasurementData_t));

    VL53L0X.PerformSingleRangingMeasurement(&RangingMeasurementData);
    ```

    Deze code initialiseert een datastructuur om gegevens in te lezen en geeft deze door aan de `PerformSingleRangingMeasurement`-methode, waar deze wordt gevuld met de afstandsmeting.

1. Schrijf hieronder de afstandsmeting uit en wacht vervolgens 1 seconde:

    ```cpp
    Serial.print("Distance = ");
    Serial.print(RangingMeasurementData.RangeMilliMeter);
    Serial.println(" mm");

    delay(1000);
    ```

1. Bouw, upload en voer deze code uit. Je kunt afstandsmetingen zien met de seriële monitor. Plaats objecten dicht bij de sensor en je zult de afstandsmeting zien:

    ```output
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    De afstandsmeter bevindt zich aan de achterkant van de sensor, dus zorg ervoor dat je de juiste kant gebruikt bij het meten van afstanden.

    ![De afstandsmeter aan de achterkant van de Time of Flight-sensor gericht op een banaan](../../../../../translated_images/nl/time-of-flight-banana.079921ad8b1496e4.webp)

> 💁 Je kunt deze code vinden in de [code-proximity/wio-terminal](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/wio-terminal) map.

😀 Je programma voor de nabijheidssensor is een succes!

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor eventuele misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.