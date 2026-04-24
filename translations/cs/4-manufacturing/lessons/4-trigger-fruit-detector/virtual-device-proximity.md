# Detekce blízkosti - Virtuální IoT hardware

V této části lekce přidáte k vašemu virtuálnímu IoT zařízení senzor blízkosti a budete z něj číst vzdálenost.

## Hardware

Virtuální IoT zařízení bude používat simulovaný senzor vzdálenosti.

U fyzického IoT zařízení byste použili senzor s laserovým měřicím modulem pro detekci vzdálenosti.

### Přidání senzoru vzdálenosti do CounterFit

Pro použití virtuálního senzoru vzdálenosti je potřeba jej přidat do aplikace CounterFit.

#### Úkol - přidání senzoru vzdálenosti do CounterFit

Přidejte senzor vzdálenosti do aplikace CounterFit.

1. Otevřete kód `fruit-quality-detector` ve VS Code a ujistěte se, že je aktivováno virtuální prostředí.

1. Nainstalujte další balíček Pip, který přidá CounterFit shim, jenž dokáže komunikovat se senzory vzdálenosti simulací balíčku [rpi-vl53l0x Pip package](https://pypi.org/project/rpi-vl53l0x/), což je Python balíček pro práci s [VL53L0X senzorem vzdálenosti na principu měření doby letu](https://wiki.seeedstudio.com/Grove-Time_of_Flight_Distance_Sensor-VL53L0X/). Ujistěte se, že instalaci provádíte z terminálu s aktivovaným virtuálním prostředím.

    ```sh
    pip install counterfit-shims-rpi-vl53l0x
    ```

1. Ujistěte se, že webová aplikace CounterFit běží.

1. Vytvořte senzor vzdálenosti:

    1. V poli *Create sensor* v panelu *Sensors* rozbalte nabídku *Sensor type* a vyberte *Distance*.

    1. Nechte jednotky nastavené na `Millimeter`.

    1. Tento senzor je I²C senzor, proto nastavte adresu na `0x29`. Pokud byste použili fyzický senzor VL53L0X, byl by na tuto adresu pevně nastaven.

    1. Klikněte na tlačítko **Add** pro vytvoření senzoru vzdálenosti.

    ![Nastavení senzoru vzdálenosti](../../../../../translated_images/cs/counterfit-create-distance-sensor.967c9fb98f27888d.webp)

    Senzor vzdálenosti bude vytvořen a objeví se v seznamu senzorů.

    ![Vytvořený senzor vzdálenosti](../../../../../translated_images/cs/counterfit-distance-sensor.079eefeeea0b68af.webp)

## Naprogramování senzoru vzdálenosti

Virtuální IoT zařízení nyní může být naprogramováno pro použití simulovaného senzoru vzdálenosti.

### Úkol - naprogramování senzoru měření doby letu

1. V projektu `fruit-quality-detector` vytvořte nový soubor s názvem `distance-sensor.py`.

    > 💁 Jednoduchý způsob, jak simulovat více IoT zařízení, je vytvořit každé v jiném Python souboru a spustit je současně.

1. Zahajte připojení k CounterFit pomocí následujícího kódu:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Pod tento kód přidejte následující:

    ```python
    import time
    
    from counterfit_shims_rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    Tento kód importuje knihovnu shim pro senzor VL53L0X měřící dobu letu.

1. Pod tento kód přidejte následující kód pro přístup k senzoru:

    ```python
    distance_sensor = VL53L0X()
    distance_sensor.begin()
    ```

    Tento kód deklaruje senzor vzdálenosti a poté jej spustí.

1. Nakonec přidejte nekonečnou smyčku pro čtení vzdáleností:

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    Tento kód čeká, až bude hodnota připravena ke čtení ze senzoru, a poté ji vypíše do konzole.

1. Spusťte tento kód.

    > 💁 Nezapomeňte, že tento soubor se jmenuje `distance-sensor.py`! Ujistěte se, že jej spouštíte přes Python, ne `app.py`.

1. V konzoli uvidíte měření vzdálenosti. Změňte hodnotu v CounterFit, abyste viděli, jak se tato hodnota mění, nebo použijte náhodné hodnoty.

    ```output
    (.venv) ➜  fruit-quality-detector python distance-sensor.py 
    Distance = 37 mm
    Distance = 42 mm
    Distance = 29 mm
    ```

> 💁 Tento kód najdete ve složce [code-proximity/virtual-iot-device](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/virtual-iot-device).

😀 Program senzoru blízkosti byl úspěšný!

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). I když se snažíme o přesnost, mějte na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace doporučujeme profesionální lidský překlad. Neodpovídáme za žádná nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.