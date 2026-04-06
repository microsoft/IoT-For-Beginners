# Mål jordfugtighed - Raspberry Pi

I denne del af lektionen vil du tilføje en kapacitiv jordfugtighedssensor til din Raspberry Pi og aflæse værdier fra den.

## Hardware

Raspberry Pi'en har brug for en kapacitiv jordfugtighedssensor.

Den sensor, du skal bruge, er en [Kapacitiv Jordfugtighedssensor](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html), der måler jordfugtighed ved at registrere jordens kapacitans, en egenskab der ændrer sig, når jordens fugtighed ændrer sig. Når jordfugtigheden stiger, falder spændingen.

Dette er en analog sensor, så den bruger en analog pin og den 10-bit ADC i Grove Base Hat på Pi'en til at konvertere spændingen til et digitalt signal fra 1-1.023. Dette sendes derefter via I²C gennem GPIO-pins på Pi'en.

### Tilslut jordfugtighedssensoren

Grove jordfugtighedssensoren kan tilsluttes Raspberry Pi'en.

#### Opgave - tilslut jordfugtighedssensoren

Tilslut jordfugtighedssensoren.

![En Grove jordfugtighedssensor](../../../../../translated_images/da/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78b.webp)

1. Sæt den ene ende af et Grove-kabel i stikket på jordfugtighedssensoren. Det kan kun sættes i på én måde.

1. Med Raspberry Pi'en slukket, tilslut den anden ende af Grove-kablet til det analoge stik mærket **A0** på Grove Base Hat, der er tilsluttet Pi'en. Dette stik er det næstsidste til højre i rækken af stik ved siden af GPIO-pins.

![Grove jordfugtighedssensor tilsluttet A0-stikket](../../../../../translated_images/da/pi-soil-moisture-sensor.fdd7eb2393792cf6.webp)

1. Sæt jordfugtighedssensoren i jorden. Den har en 'højeste positionslinje' - en hvid linje på tværs af sensoren. Sæt sensoren i jorden op til, men ikke over, denne linje.

![Grove jordfugtighedssensor i jord](../../../../../translated_images/da/soil-moisture-sensor-in-soil.bfad91002bda5e96.webp)

## Programmer jordfugtighedssensoren

Raspberry Pi'en kan nu programmeres til at bruge den tilsluttede jordfugtighedssensor.

### Opgave - programmer jordfugtighedssensoren

Programmer enheden.

1. Tænd for Pi'en og vent, til den er startet op.

1. Start VS Code, enten direkte på Pi'en eller ved at forbinde via Remote SSH-udvidelsen.

    > ⚠️ Du kan finde [instruktionerne til opsætning og start af VS Code i nightlight - lektion 1, hvis nødvendigt](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md).

1. Fra terminalen skal du oprette en ny mappe i `pi`-brugerens hjemmemappe kaldet `soil-moisture-sensor`. Opret en fil i denne mappe kaldet `app.py`.

1. Åbn denne mappe i VS Code.

1. Tilføj følgende kode til filen `app.py` for at importere nogle nødvendige biblioteker:

    ```python
    import time
    from grove.adc import ADC
    ```

    `import time`-sætningen importerer `time`-modulet, som vil blive brugt senere i denne opgave.

    `from grove.adc import ADC`-sætningen importerer `ADC` fra Grove Python-bibliotekerne. Dette bibliotek indeholder kode til at interagere med den analoge-til-digitale konverter på Pi Base Hat og aflæse spændinger fra analoge sensorer.

1. Tilføj følgende kode nedenfor for at oprette en instans af `ADC`-klassen:

    ```python
    adc = ADC()
    ```

1. Tilføj en uendelig løkke, der aflæser fra denne ADC på A0-pinnen og skriver resultatet til konsollen. Denne løkke kan derefter sove i 10 sekunder mellem aflæsninger.

    ```python
    while True:
        soil_moisture = adc.read(0)
        print("Soil moisture:", soil_moisture)

        time.sleep(10)
    ```

1. Kør Python-appen. Du vil se jordfugtighedsmålingerne skrevet til konsollen. Tilføj noget vand til jorden, eller fjern sensoren fra jorden, og se værdien ændre sig.

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Soil moisture: 615
    Soil moisture: 612
    Soil moisture: 498
    Soil moisture: 493
    Soil moisture: 490
    Soil Moisture: 388
    ```

    I det viste eksempeloutput kan du se spændingen falde, når der tilføjes vand.

> 💁 Du kan finde denne kode i [code/pi](../../../../../2-farm/lessons/2-detect-soil-moisture/code/pi)-mappen.

😀 Dit program til jordfugtighedssensoren var en succes!

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi påtager os intet ansvar for misforståelser eller fejltolkninger, der måtte opstå som følge af brugen af denne oversættelse.