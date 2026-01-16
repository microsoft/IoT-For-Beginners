<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2bf65f162bcebd35fbcba5fd245afac4",
  "translation_date": "2025-08-27T22:27:30+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/virtual-device-soil-moisture.md",
  "language_code": "da"
}
-->
# Mål jordfugtighed - Virtuel IoT-hardware

I denne del af lektionen vil du tilføje en kapacitiv jordfugtighedssensor til din virtuelle IoT-enhed og læse værdier fra den.

## Virtuel hardware

Den virtuelle IoT-enhed vil bruge en simuleret Grove kapacitiv jordfugtighedssensor. Dette gør denne øvelse identisk med at bruge en Raspberry Pi med en fysisk Grove kapacitiv jordfugtighedssensor.

På en fysisk IoT-enhed ville jordfugtighedssensoren være en kapacitiv sensor, der måler jordfugtighed ved at registrere jordens kapacitans, en egenskab der ændrer sig, når jordens fugtighed ændrer sig. Når jordfugtigheden stiger, falder spændingen.

Dette er en analog sensor, så den bruger en simuleret 10-bit ADC til at rapportere en værdi fra 1-1.023.

### Tilføj jordfugtighedssensoren til CounterFit

For at bruge en virtuel jordfugtighedssensor skal du tilføje den til CounterFit-appen.

#### Opgave - Tilføj jordfugtighedssensoren til CounterFit

Tilføj jordfugtighedssensoren til CounterFit-appen.

1. Opret en ny Python-app på din computer i en mappe kaldet `soil-moisture-sensor` med en enkelt fil kaldet `app.py` og et Python-virtuelt miljø, og tilføj CounterFit pip-pakkerne.

    > ⚠️ Du kan henvise til [instruktionerne for at oprette og opsætte et CounterFit Python-projekt i lektion 1, hvis det er nødvendigt](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Sørg for, at CounterFit-webappen kører.

1. Opret en jordfugtighedssensor:

    1. I *Create sensor*-boksen i *Sensors*-panelet, rul ned i *Sensor type*-boksen og vælg *Soil Moisture*.

    1. Lad *Units* være indstillet til *NoUnits*.

    1. Sørg for, at *Pin* er indstillet til *0*.

    1. Vælg knappen **Add** for at oprette *Soil Moisture*-sensoren på Pin 0.

    ![Indstillinger for jordfugtighedssensoren](../../../../../translated_images/da/counterfit-create-soil-moisture-sensor.35266135a5e0ae68b29a684d7db0d2933a8098b2307d197f7c71577b724603aa.png)

    Jordfugtighedssensoren vil blive oprettet og vises i sensorlisten.

    ![Den oprettede jordfugtighedssensor](../../../../../translated_images/da/counterfit-soil-moisture-sensor.81742b2de0e9de60a3b3b9a2ff8ecc686d428eb6d71820f27a693be26e5aceee.png)

## Programmer jordfugtighedssensor-appen

Jordfugtighedssensor-appen kan nu programmeres ved hjælp af CounterFit-sensorer.

### Opgave - Programmer jordfugtighedssensor-appen

Programmer jordfugtighedssensor-appen.

1. Sørg for, at `soil-moisture-sensor`-appen er åben i VS Code.

1. Åbn filen `app.py`.

1. Tilføj følgende kode øverst i `app.py` for at forbinde appen til CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Tilføj følgende kode til filen `app.py` for at importere nogle nødvendige biblioteker:

    ```python
    import time
    from counterfit_shims_grove.adc import ADC
    ```

    `import time`-sætningen importerer `time`-modulet, som vil blive brugt senere i denne opgave.

    `from counterfit_shims_grove.adc import ADC`-sætningen importerer `ADC`-klassen for at interagere med en virtuel analog-til-digital-konverter, der kan forbindes til en CounterFit-sensor.

1. Tilføj følgende kode nedenfor for at oprette en instans af `ADC`-klassen:

    ```python
    adc = ADC()
    ```

1. Tilføj en uendelig løkke, der læser fra denne ADC på pin 0 og skriver resultatet til konsollen. Denne løkke kan derefter sove i 10 sekunder mellem aflæsninger.

    ```python
    while True:
        soil_moisture = adc.read(0)
        print("Soil moisture:", soil_moisture)
    
        time.sleep(10)
    ```

1. Fra CounterFit-appen skal du ændre værdien af jordfugtighedssensoren, som vil blive læst af appen. Du kan gøre dette på to måder:

    * Indtast et tal i *Value*-boksen for jordfugtighedssensoren, og vælg derefter knappen **Set**. Det tal, du indtaster, vil være den værdi, sensoren returnerer.

    * Marker *Random*-afkrydsningsfeltet, og indtast en *Min*- og *Max*-værdi, og vælg derefter knappen **Set**. Hver gang sensoren læser en værdi, vil den læse et tilfældigt tal mellem *Min* og *Max*.

1. Kør Python-appen. Du vil se jordfugtighedsmålingerne skrevet til konsollen. Ændr *Value*- eller *Random*-indstillingerne for at se værdien ændre sig.

    ```output
    (.venv) ➜ soil-moisture-sensor $ python app.py 
    Soil moisture: 615
    Soil moisture: 612
    Soil moisture: 498
    Soil moisture: 493
    Soil moisture: 490
    Soil Moisture: 388
    ```

> 💁 Du kan finde denne kode i [code/virtual-device](../../../../../2-farm/lessons/2-detect-soil-moisture/code/virtual-device)-mappen.

😀 Dit jordfugtighedssensorprogram var en succes!

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi er ikke ansvarlige for eventuelle misforståelser eller fejltolkninger, der måtte opstå som følge af brugen af denne oversættelse.