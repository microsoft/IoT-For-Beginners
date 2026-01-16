<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2bf65f162bcebd35fbcba5fd245afac4",
  "translation_date": "2025-08-27T22:54:26+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/virtual-device-soil-moisture.md",
  "language_code": "cs"
}
-->
# Měření vlhkosti půdy - Virtuální IoT hardware

V této části lekce přidáte kapacitní senzor vlhkosti půdy k vašemu virtuálnímu IoT zařízení a budete z něj číst hodnoty.

## Virtuální hardware

Virtuální IoT zařízení bude používat simulovaný kapacitní senzor vlhkosti půdy Grove. Tento přístup udržuje tento lab stejný jako při použití Raspberry Pi s fyzickým kapacitním senzorem vlhkosti půdy Grove.

U fyzického IoT zařízení by senzor vlhkosti půdy byl kapacitní senzor, který měří vlhkost půdy detekcí kapacity půdy, což je vlastnost, která se mění s vlhkostí půdy. Jak vlhkost půdy roste, napětí klesá.

Jedná se o analogový senzor, který používá simulovaný 10bitový ADC k reportování hodnoty v rozmezí 1–1 023.

### Přidání senzoru vlhkosti půdy do CounterFit

Pro použití virtuálního senzoru vlhkosti půdy je třeba jej přidat do aplikace CounterFit.

#### Úkol - Přidání senzoru vlhkosti půdy do CounterFit

Přidejte senzor vlhkosti půdy do aplikace CounterFit.

1. Vytvořte novou Python aplikaci na svém počítači ve složce `soil-moisture-sensor` s jediným souborem `app.py` a Python virtuálním prostředím, a přidejte CounterFit pip balíčky.

    > ⚠️ Můžete se odkázat na [instrukce pro vytvoření a nastavení CounterFit Python projektu v lekci 1, pokud je to potřeba](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Ujistěte se, že webová aplikace CounterFit běží.

1. Vytvořte senzor vlhkosti půdy:

    1. V poli *Create sensor* v panelu *Sensors* rozbalte pole *Sensor type* a vyberte *Soil Moisture*.

    1. Nechte *Units* nastavené na *NoUnits*.

    1. Ujistěte se, že *Pin* je nastaven na *0*.

    1. Klikněte na tlačítko **Add** pro vytvoření senzoru *Soil Moisture* na pinu 0.

    ![Nastavení senzoru vlhkosti půdy](../../../../../translated_images/cs/counterfit-create-soil-moisture-sensor.35266135a5e0ae68b29a684d7db0d2933a8098b2307d197f7c71577b724603aa.png)

    Senzor vlhkosti půdy bude vytvořen a objeví se v seznamu senzorů.

    ![Vytvořený senzor vlhkosti půdy](../../../../../translated_images/cs/counterfit-soil-moisture-sensor.81742b2de0e9de60a3b3b9a2ff8ecc686d428eb6d71820f27a693be26e5aceee.png)

## Naprogramování aplikace senzoru vlhkosti půdy

Aplikace senzoru vlhkosti půdy nyní může být naprogramována pomocí senzorů CounterFit.

### Úkol - Naprogramování aplikace senzoru vlhkosti půdy

Naprogramujte aplikaci senzoru vlhkosti půdy.

1. Ujistěte se, že aplikace `soil-moisture-sensor` je otevřená ve VS Code.

1. Otevřete soubor `app.py`.

1. Přidejte následující kód na začátek souboru `app.py` pro připojení aplikace k CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Přidejte následující kód do souboru `app.py` pro import potřebných knihoven:

    ```python
    import time
    from counterfit_shims_grove.adc import ADC
    ```

    Příkaz `import time` importuje modul `time`, který bude použit později v tomto úkolu.

    Příkaz `from counterfit_shims_grove.adc import ADC` importuje třídu `ADC` pro interakci se simulovaným analogově-digitálním převodníkem, který se může připojit k senzoru CounterFit.

1. Přidejte následující kód pod tento blok pro vytvoření instance třídy `ADC`:

    ```python
    adc = ADC()
    ```

1. Přidejte nekonečnou smyčku, která čte hodnoty z ADC na pinu 0 a zapisuje výsledek do konzole. Tato smyčka pak může mezi čteními spát po dobu 10 sekund.

    ```python
    while True:
        soil_moisture = adc.read(0)
        print("Soil moisture:", soil_moisture)
    
        time.sleep(10)
    ```

1. V aplikaci CounterFit změňte hodnotu senzoru vlhkosti půdy, kterou bude aplikace číst. Můžete to udělat jedním ze dvou způsobů:

    * Zadejte číslo do pole *Value* senzoru vlhkosti půdy a poté klikněte na tlačítko **Set**. Číslo, které zadáte, bude hodnota vrácená senzorem.

    * Zaškrtněte políčko *Random* a zadejte hodnoty *Min* a *Max*, poté klikněte na tlačítko **Set**. Při každém čtení hodnoty senzoru se přečte náhodné číslo mezi *Min* a *Max*.

1. Spusťte Python aplikaci. Uvidíte měření vlhkosti půdy zapsaná do konzole. Změňte hodnotu *Value* nebo nastavení *Random*, abyste viděli změnu hodnoty.

    ```output
    (.venv) ➜ soil-moisture-sensor $ python app.py 
    Soil moisture: 615
    Soil moisture: 612
    Soil moisture: 498
    Soil moisture: 493
    Soil moisture: 490
    Soil Moisture: 388
    ```

> 💁 Tento kód najdete ve složce [code/virtual-device](../../../../../2-farm/lessons/2-detect-soil-moisture/code/virtual-device).

😀 Program senzoru vlhkosti půdy byl úspěšný!

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). Ačkoli se snažíme o přesnost, mějte prosím na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace doporučujeme profesionální lidský překlad. Neodpovídáme za žádné nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.