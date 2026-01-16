<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "11f10c6760fb8202cf368422702fdf70",
  "translation_date": "2025-08-27T22:33:37+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/virtual-device-sensor.md",
  "language_code": "cs"
}
-->
# Vytvořte noční světlo - Virtuální IoT hardware

V této části lekce přidáte světelný senzor do svého virtuálního IoT zařízení.

## Virtuální hardware

Noční světlo potřebuje jeden senzor, který vytvoříte v aplikaci CounterFit.

Tímto senzorem je **světelný senzor**. U fyzického IoT zařízení by to byla [fotodioda](https://wikipedia.org/wiki/Photodiode), která převádí světlo na elektrický signál. Světelné senzory jsou analogové senzory, které posílají celočíselnou hodnotu označující relativní množství světla. Tato hodnota není vázána na žádnou standardní jednotku měření, jako je například [lux](https://wikipedia.org/wiki/Lux).

### Přidejte senzory do CounterFit

Pro použití virtuálního světelného senzoru je třeba jej přidat do aplikace CounterFit.

#### Úkol - přidejte senzory do CounterFit

Přidejte světelný senzor do aplikace CounterFit.

1. Ujistěte se, že webová aplikace CounterFit běží z předchozí části tohoto úkolu. Pokud neběží, spusťte ji.

1. Vytvořte světelný senzor:

    1. V poli *Create sensor* v panelu *Sensors* rozbalte pole *Sensor type* a vyberte *Light*.

    1. Nechte *Units* nastavené na *NoUnits*.

    1. Ujistěte se, že *Pin* je nastaven na *0*.

    1. Klikněte na tlačítko **Add**, abyste vytvořili světelný senzor na pinu 0.

    ![Nastavení světelného senzoru](../../../../../translated_images/cs/counterfit-create-light-sensor.9f36a5e0d4458d8d554d54b34d2c806d56093d6e49fddcda2d20f6fef7f5cce1.png)

    Světelný senzor bude vytvořen a objeví se v seznamu senzorů.

    ![Vytvořený světelný senzor](../../../../../translated_images/cs/counterfit-light-sensor.5d0f5584df56b90f6b2561910d9cb20dfbd73eeff2177c238d38f4de54aefae1.png)

## Naprogramujte světelný senzor

Zařízení nyní může být naprogramováno tak, aby používalo vestavěný světelný senzor.

### Úkol - naprogramujte světelný senzor

Naprogramujte zařízení.

1. Otevřete projekt nočního světla ve VS Code, který jste vytvořili v předchozí části tohoto úkolu. Pokud je to nutné, ukončete a znovu vytvořte terminál, aby běžel s použitím virtuálního prostředí.

1. Otevřete soubor `app.py`.

1. Přidejte následující kód na začátek souboru `app.py` k ostatním příkazům `import`, abyste připojili potřebné knihovny:

    ```python
    import time
    from counterfit_shims_grove.grove_light_sensor_v1_2 import GroveLightSensor
    ```

    Příkaz `import time` importuje modul `time` z Pythonu, který bude použit později v tomto úkolu.

    Příkaz `from counterfit_shims_grove.grove_light_sensor_v1_2 import GroveLightSensor` importuje `GroveLightSensor` z knihoven CounterFit Grove shim pro Python. Tato knihovna obsahuje kód pro interakci se světelným senzorem vytvořeným v aplikaci CounterFit.

1. Přidejte následující kód na konec souboru, abyste vytvořili instance tříd, které spravují světelný senzor:

    ```python
    light_sensor = GroveLightSensor(0)
    ```

    Řádek `light_sensor = GroveLightSensor(0)` vytvoří instanci třídy `GroveLightSensor`, která se připojí k pinu **0** - CounterFit Grove pinu, ke kterému je připojen světelný senzor.

1. Přidejte nekonečnou smyčku za výše uvedený kód, která bude číst hodnotu světelného senzoru a vypisovat ji do konzole:

    ```python
    while True:
        light = light_sensor.light
        print('Light level:', light)
    ```

    Tento kód přečte aktuální úroveň světla pomocí vlastnosti `light` třídy `GroveLightSensor`. Tato vlastnost čte analogovou hodnotu z pinu. Tato hodnota je poté vypsána do konzole.

1. Přidejte na konec smyčky `while` krátkou pauzu o délce jedné sekundy, protože úroveň světla není třeba kontrolovat nepřetržitě. Pauza snižuje spotřebu energie zařízení.

    ```python
    time.sleep(1)
    ```

1. V terminálu VS Code spusťte následující příkaz pro spuštění vaší Python aplikace:

    ```sh
    python3 app.py
    ```

    Hodnoty světla budou vypsány do konzole. Zpočátku bude tato hodnota 0.

1. V aplikaci CounterFit změňte hodnotu světelného senzoru, kterou aplikace přečte. Můžete to udělat jedním ze dvou způsobů:

    * Zadejte číslo do pole *Value* pro světelný senzor a poté klikněte na tlačítko **Set**. Číslo, které zadáte, bude hodnota vrácená senzorem.

    * Zaškrtněte políčko *Random* a zadejte hodnoty *Min* a *Max*, poté klikněte na tlačítko **Set**. Při každém čtení hodnoty senzoru bude přečteno náhodné číslo mezi *Min* a *Max*.

    Hodnoty, které nastavíte, budou vypsány do konzole. Změňte *Value* nebo nastavení *Random*, aby se hodnota měnila.

    ```output
    (.venv) ➜  GroveTest python3 app.py 
    Light level: 143
    Light level: 244
    Light level: 246
    Light level: 253
    ```

> 💁 Tento kód najdete ve složce [code-sensor/virtual-device](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/virtual-device).

😀 Program vašeho nočního světla byl úspěšný!

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby AI pro překlady [Co-op Translator](https://github.com/Azure/co-op-translator). Ačkoli se snažíme o přesnost, mějte prosím na paměti, že automatizované překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace se doporučuje profesionální lidský překlad. Neodpovídáme za žádná nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.