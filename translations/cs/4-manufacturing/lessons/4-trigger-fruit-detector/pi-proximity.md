<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6145a1d791731c8a9d0afd0a1bae5108",
  "translation_date": "2025-08-27T20:43:23+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/pi-proximity.md",
  "language_code": "cs"
}
-->
# Detekce blízkosti - Raspberry Pi

V této části lekce přidáte k Raspberry Pi senzor blízkosti a budete z něj číst vzdálenost.

## Hardware

Raspberry Pi potřebuje senzor blízkosti.

Senzor, který použijete, je [Grove Time of Flight distance sensor](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html). Tento senzor využívá laserový měřicí modul k detekci vzdálenosti. Má rozsah od 10 mm do 2000 mm (1 cm - 2 m) a v tomto rozsahu poskytuje poměrně přesné hodnoty, přičemž vzdálenosti nad 1000 mm jsou hlášeny jako 8109 mm.

Laserový dálkoměr se nachází na zadní straně senzoru, na opačné straně než konektor Grove.

Toto je I²C senzor.

### Připojení senzoru Time of Flight

Senzor Grove Time of Flight lze připojit k Raspberry Pi.

#### Úkol - připojte senzor Time of Flight

Připojte senzor Time of Flight.

![Senzor Grove Time of Flight](../../../../../translated_images/cs/grove-time-of-flight-sensor.d82ff2165bfded9f485de54d8d07195a6270a602696825fca19f629ddfe94e86.png)

1. Zasuňte jeden konec Grove kabelu do konektoru na senzoru Time of Flight. Kabel lze zasunout pouze jedním způsobem.

1. S vypnutým Raspberry Pi připojte druhý konec Grove kabelu do jednoho z I²C konektorů označených **I²C** na Grove Base hat připojeném k Pi. Tyto konektory se nacházejí na spodní řadě, na opačné straně než GPIO piny a vedle slotu pro kamerový kabel.

![Senzor Grove Time of Flight připojený k I²C konektoru](../../../../../translated_images/cs/pi-time-of-flight-sensor.58c8dc04eb3bfb57.webp)

## Naprogramování senzoru Time of Flight

Nyní můžete Raspberry Pi naprogramovat tak, aby používalo připojený senzor Time of Flight.

### Úkol - naprogramujte senzor Time of Flight

Naprogramujte zařízení.

1. Zapněte Raspberry Pi a počkejte, až se spustí.

1. Otevřete kód `fruit-quality-detector` ve VS Code, buď přímo na Pi, nebo se připojte pomocí rozšíření Remote SSH.

1. Nainstalujte balíček rpi-vl53l0x pomocí Pip. Tento Python balíček umožňuje komunikaci se senzorem vzdálenosti VL53L0X. Nainstalujte jej pomocí tohoto příkazu:

    ```sh
    pip install rpi-vl53l0x
    ```

1. Vytvořte v tomto projektu nový soubor s názvem `distance-sensor.py`.

    > 💁 Jednoduchý způsob, jak simulovat více IoT zařízení, je vytvořit pro každé zařízení samostatný Python soubor a spustit je současně.

1. Do tohoto souboru přidejte následující kód:

    ```python
    import time
    
    from grove.i2c import Bus
    from rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    Tento kód importuje knihovnu Grove I²C bus a knihovnu senzoru pro základní hardware zabudovaný do senzoru Grove Time of Flight.

1. Pod tento kód přidejte následující kód pro přístup k senzoru:

    ```python
    distance_sensor = VL53L0X(bus = Bus().bus)
    distance_sensor.begin()    
    ```

    Tento kód deklaruje senzor vzdálenosti pomocí Grove I²C bus a poté senzor spustí.

1. Nakonec přidejte nekonečnou smyčku pro čtení vzdáleností:

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    Tento kód čeká, až bude hodnota připravena k přečtení ze senzoru, a poté ji vypíše do konzole.

1. Spusťte tento kód.

    > 💁 Nezapomeňte, že tento soubor se jmenuje `distance-sensor.py`! Ujistěte se, že jej spouštíte pomocí Pythonu, ne `app.py`.

1. V konzoli se začnou objevovat měření vzdálenosti. Umístěte objekty blízko senzoru a uvidíte měření vzdálenosti:

    ```output
    pi@raspberrypi:~/fruit-quality-detector $ python3 distance_sensor.py 
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    Dálkoměr se nachází na zadní straně senzoru, takže při měření vzdálenosti používejte správnou stranu.

    ![Dálkoměr na zadní straně senzoru Time of Flight mířící na banán](../../../../../translated_images/cs/time-of-flight-banana.079921ad8b1496e4.webp)

> 💁 Tento kód najdete ve složce [code-proximity/pi](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/pi).

😀 Program senzoru blízkosti byl úspěšný!

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). Ačkoli se snažíme o přesnost, mějte prosím na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace se doporučuje profesionální lidský překlad. Neodpovídáme za žádná nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.