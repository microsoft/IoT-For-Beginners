<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "ea733bd0cdf2479e082373f765a08678",
  "translation_date": "2025-08-27T22:08:21+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/pi-sensor.md",
  "language_code": "da"
}
-->
# Byg en natlampe - Raspberry Pi

I denne del af lektionen vil du tilføje en lyssensor til din Raspberry Pi.

## Hardware

Sensoren til denne lektion er en **lyssensor**, der bruger en [fotodiode](https://wikipedia.org/wiki/Photodiode) til at omdanne lys til et elektrisk signal. Dette er en analog sensor, der sender en heltalsværdi fra 0 til 1.000, som angiver en relativ mængde lys. Denne værdi svarer ikke til nogen standard måleenhed som f.eks. [lux](https://wikipedia.org/wiki/Lux).

Lyssensoren er en ekstern Grove-sensor og skal tilsluttes Grove Base-hatten på Raspberry Pi.

### Tilslut lyssensoren

Grove-lyssensoren, der bruges til at registrere lysniveauer, skal forbindes til Raspberry Pi.

#### Opgave - tilslut lyssensoren

Tilslut lyssensoren.

![En Grove-lyssensor](../../../../../translated_images/da/grove-light-sensor.b8127b7c434e632d6bcdb57587a14e9ef69a268a22df95d08628f62b8fa5505c.png)

1. Sæt den ene ende af et Grove-kabel i stikket på lyssensormodulet. Det kan kun sættes i på én måde.

1. Med Raspberry Pi slukket, tilslut den anden ende af Grove-kablet til det analoge stik mærket **A0** på Grove Base-hatten, der er tilsluttet Pi'en. Dette stik er det andet fra højre i rækken af stik ved siden af GPIO-pindene.

![Grove-lyssensoren tilsluttet stik A0](../../../../../translated_images/da/pi-light-sensor.66cc1e31fa48cd7d5f23400d4b2119aa41508275cb7c778053a7923b4e972d7e.png)

## Programmer lyssensoren

Enheden kan nu programmeres ved hjælp af Grove-lyssensoren.

### Opgave - programmer lyssensoren

Programmer enheden.

1. Tænd for Pi'en og vent, til den er startet op.

1. Åbn natlampeprojektet i VS Code, som du oprettede i den forrige del af denne opgave, enten direkte på Pi'en eller ved hjælp af Remote SSH-udvidelsen.

1. Åbn filen `app.py`, og fjern al eksisterende kode fra den.

1. Tilføj følgende kode til `app.py`-filen for at importere nogle nødvendige biblioteker:

    ```python
    import time
    from grove.grove_light_sensor_v1_2 import GroveLightSensor
    ```

    `import time`-sætningen importerer `time`-modulet, som vil blive brugt senere i denne opgave.

    `from grove.grove_light_sensor_v1_2 import GroveLightSensor`-sætningen importerer `GroveLightSensor` fra Grove Python-bibliotekerne. Dette bibliotek indeholder kode til at interagere med en Grove-lyssensor og blev installeret globalt under opsætningen af Pi'en.

1. Tilføj følgende kode efter ovenstående for at oprette en instans af klassen, der styrer lyssensoren:

    ```python
    light_sensor = GroveLightSensor(0)
    ```

    Linjen `light_sensor = GroveLightSensor(0)` opretter en instans af `GroveLightSensor`-klassen, der forbinder til pin **A0** - det analoge Grove-stik, som lyssensoren er tilsluttet.

1. Tilføj en uendelig løkke efter ovenstående kode for at aflæse lyssensorens værdi og udskrive den til konsollen:

    ```python
    while True:
        light = light_sensor.light
        print('Light level:', light)
    ```

    Dette vil aflæse det aktuelle lysniveau på en skala fra 0-1.023 ved hjælp af `light`-egenskaben i `GroveLightSensor`-klassen. Denne egenskab aflæser den analoge værdi fra stikket. Værdien udskrives derefter til konsollen.

1. Tilføj en kort pause på et sekund i slutningen af `loop`, da lysniveauerne ikke behøver at blive kontrolleret kontinuerligt. En pause reducerer enhedens strømforbrug.

    ```python
    time.sleep(1)
    ```

1. Fra VS Code-terminalen skal du køre følgende for at starte din Python-app:

    ```sh
    python3 app.py
    ```

    Lysværdier vil blive udskrevet til konsollen. Dæk og afdæk lyssensoren, og værdierne vil ændre sig:

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py 
    Light level: 634
    Light level: 634
    Light level: 634
    Light level: 230
    Light level: 104
    Light level: 290
    ```

> 💁 Du kan finde denne kode i [code-sensor/pi](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/pi)-mappen.

😀 Det var en succes at tilføje en sensor til dit natlampeprogram!

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi er ikke ansvarlige for eventuelle misforståelser eller fejltolkninger, der opstår som følge af brugen af denne oversættelse.