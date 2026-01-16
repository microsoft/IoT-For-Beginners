<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "70e5a428b607cd5a9a4f422c2a4df03d",
  "translation_date": "2025-08-27T23:22:48+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/virtual-device-temp.md",
  "language_code": "cs"
}
-->
# Měření teploty - Virtuální IoT hardware

V této části lekce přidáte teplotní senzor do svého virtuálního IoT zařízení.

## Virtuální hardware

Virtuální IoT zařízení bude používat simulovaný senzor Grove Digital Humidity and Temperature. Tento přístup udržuje tento lab stejný jako při použití Raspberry Pi s fyzickým senzorem Grove DHT11.

Senzor kombinuje **teplotní senzor** a **senzor vlhkosti**, ale v tomto labu vás zajímá pouze komponenta teplotního senzoru. U fyzického IoT zařízení by teplotní senzor byl [termistor](https://wikipedia.org/wiki/Thermistor), který měří teplotu na základě změny odporu při změně teploty. Teplotní senzory jsou obvykle digitální senzory, které interně převádějí naměřený odpor na teplotu ve stupních Celsia (nebo Kelvina, nebo Fahrenheita).

### Přidání senzorů do CounterFit

Pro použití virtuálního senzoru vlhkosti a teploty je třeba přidat tyto dva senzory do aplikace CounterFit.

#### Úkol - přidání senzorů do CounterFit

Přidejte senzory vlhkosti a teploty do aplikace CounterFit.

1. Vytvořte novou Python aplikaci na svém počítači ve složce `temperature-sensor` s jediným souborem `app.py` a Python virtuálním prostředím, a přidejte CounterFit pip balíčky.

    > ⚠️ Můžete se odkázat na [instrukce pro vytvoření a nastavení CounterFit Python projektu v lekci 1, pokud je to potřeba](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Nainstalujte další Pip balíček pro instalaci CounterFit shim pro senzor DHT11. Ujistěte se, že instalaci provádíte z terminálu s aktivovaným virtuálním prostředím.

    ```sh
    pip install counterfit-shims-seeed-python-dht
    ```

1. Ujistěte se, že webová aplikace CounterFit běží.

1. Vytvořte senzor vlhkosti:

    1. V poli *Create sensor* v panelu *Sensors* rozbalte pole *Sensor type* a vyberte *Humidity*.

    1. Nechte *Units* nastavené na *Percentage*.

    1. Ujistěte se, že *Pin* je nastaven na *5*.

    1. Klikněte na tlačítko **Add** pro vytvoření senzoru vlhkosti na pinu 5.

    ![Nastavení senzoru vlhkosti](../../../../../translated_images/cs/counterfit-create-humidity-sensor.2750e27b6f30e09cf4e22101defd5252710717620816ab41ba688f91f757c49a.png)

    Senzor vlhkosti bude vytvořen a objeví se v seznamu senzorů.

    ![Vytvořený senzor vlhkosti](../../../../../translated_images/cs/counterfit-humidity-sensor.7b12f7f339e430cb26c8211d2dba4ef75261b353a01da0932698b5bebd693f27.png)

1. Vytvořte teplotní senzor:

    1. V poli *Create sensor* v panelu *Sensors* rozbalte pole *Sensor type* a vyberte *Temperature*.

    1. Nechte *Units* nastavené na *Celsius*.

    1. Ujistěte se, že *Pin* je nastaven na *6*.

    1. Klikněte na tlačítko **Add** pro vytvoření teplotního senzoru na pinu 6.

    ![Nastavení teplotního senzoru](../../../../../translated_images/cs/counterfit-create-temperature-sensor.199350ed34f7343d79dccbe95eaf6c11d2121f03d1c35ab9613b330c23f39b29.png)

    Teplotní senzor bude vytvořen a objeví se v seznamu senzorů.

    ![Vytvořený teplotní senzor](../../../../../translated_images/cs/counterfit-temperature-sensor.f0560236c96a9016bafce7f6f792476fe3367bc6941a1f7d5811d144d4bcbfff.png)

## Naprogramování aplikace pro teplotní senzor

Nyní můžete naprogramovat aplikaci pro teplotní senzor pomocí senzorů CounterFit.

### Úkol - naprogramování aplikace pro teplotní senzor

Naprogramujte aplikaci pro teplotní senzor.

1. Ujistěte se, že aplikace `temperature-sensor` je otevřená ve VS Code.

1. Otevřete soubor `app.py`.

1. Přidejte následující kód na začátek souboru `app.py` pro připojení aplikace k CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Přidejte následující kód do souboru `app.py` pro import potřebných knihoven:

    ```python
    import time
    from counterfit_shims_seeed_python_dht import DHT
    ```

    Příkaz `from seeed_dht import DHT` importuje třídu `DHT` pro interakci s virtuálním Grove teplotním senzorem pomocí shim z modulu `counterfit_shims_seeed_python_dht`.

1. Přidejte následující kód za výše uvedený kód pro vytvoření instance třídy, která spravuje virtuální senzor vlhkosti a teploty:

    ```python
    sensor = DHT("11", 5)
    ```

    Tento kód deklaruje instanci třídy `DHT`, která spravuje virtuální **D**igitální **H**umidity a **T**emperature senzor. První parametr říká kódu, že použitý senzor je virtuální senzor *DHT11*. Druhý parametr říká kódu, že senzor je připojen k portu `5`.

    > 💁 CounterFit simuluje tento kombinovaný senzor vlhkosti a teploty připojením ke dvěma senzorům: senzoru vlhkosti na pinu uvedeném při vytvoření třídy `DHT` a teplotnímu senzoru, který běží na dalším pinu. Pokud je senzor vlhkosti na pinu 5, shim očekává, že teplotní senzor bude na pinu 6.

1. Přidejte nekonečnou smyčku za výše uvedený kód pro čtení hodnoty teplotního senzoru a její výpis do konzole:

    ```python
    while True:
        _, temp = sensor.read()
        print(f'Temperature {temp}°C')
    ```

    Volání `sensor.read()` vrací dvojici hodnot vlhkosti a teploty. Potřebujete pouze hodnotu teploty, takže vlhkost je ignorována. Hodnota teploty je poté vypsána do konzole.

1. Přidejte na konec smyčky krátkou pauzu deset sekund, protože není nutné kontrolovat úroveň teploty neustále. Pauza snižuje spotřebu energie zařízení.

    ```python
    time.sleep(10)
    ```

1. Z terminálu ve VS Code s aktivovaným virtuálním prostředím spusťte následující příkaz pro spuštění vaší Python aplikace:

    ```sh
    python app.py
    ```

1. V aplikaci CounterFit změňte hodnotu teplotního senzoru, kterou bude aplikace číst. Můžete to udělat dvěma způsoby:

    * Zadejte číslo do pole *Value* pro teplotní senzor a poté klikněte na tlačítko **Set**. Číslo, které zadáte, bude hodnota vrácená senzorem.

    * Zaškrtněte políčko *Random* a zadejte hodnoty *Min* a *Max*, poté klikněte na tlačítko **Set**. Při každém čtení hodnoty senzoru se přečte náhodné číslo mezi *Min* a *Max*.

    Měli byste vidět hodnoty, které jste nastavili, objevující se v konzoli. Změňte *Value* nebo nastavení *Random*, abyste viděli změnu hodnoty.

    ```output
    (.venv) ➜  temperature-sensor python app.py
    Temperature 28.25°C
    Temperature 30.71°C
    Temperature 25.17°C
    ```

> 💁 Tento kód najdete ve složce [code-temperature/virtual-device](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/virtual-device).

😀 Vaše aplikace pro teplotní senzor byla úspěšně vytvořena!

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). Ačkoli se snažíme o přesnost, mějte prosím na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace se doporučuje profesionální lidský překlad. Neodpovídáme za žádná nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.