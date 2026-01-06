<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9d4d00a47d5d0f3e6ce42c0d1020064a",
  "translation_date": "2025-08-27T22:48:44+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/pi-soil-moisture.md",
  "language_code": "cs"
}
-->
# Měření vlhkosti půdy - Raspberry Pi

V této části lekce přidáte kapacitní senzor vlhkosti půdy k Raspberry Pi a budete z něj číst hodnoty.

## Hardware

Raspberry Pi potřebuje kapacitní senzor vlhkosti půdy.

Senzor, který budete používat, je [Kapacitní senzor vlhkosti půdy](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html), který měří vlhkost půdy detekcí kapacity půdy, což je vlastnost, která se mění s vlhkostí půdy. Jak se vlhkost půdy zvyšuje, napětí klesá.

Jedná se o analogový senzor, který používá analogový pin a 10bitový ADC v Grove Base Hat na Raspberry Pi k převodu napětí na digitální signál v rozsahu 1-1 023. Tento signál je poté odeslán přes I2C pomocí GPIO pinů na Raspberry Pi.

### Připojení senzoru vlhkosti půdy

Senzor vlhkosti půdy Grove lze připojit k Raspberry Pi.

#### Úkol - připojení senzoru vlhkosti půdy

Připojte senzor vlhkosti půdy.

![Senzor vlhkosti půdy Grove](../../../../../translated_images/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78be5cc5a07839385fd6718857f31b5bf5ad3d0c73c83b2f0ef.cs.png)

1. Zasuňte jeden konec kabelu Grove do konektoru na senzoru vlhkosti půdy. Kabel lze zasunout pouze jedním směrem.

1. S vypnutým Raspberry Pi připojte druhý konec kabelu Grove do analogového konektoru označeného **A0** na Grove Base Hat připojeném k Raspberry Pi. Tento konektor je druhý zprava v řadě konektorů vedle GPIO pinů.

![Senzor vlhkosti půdy Grove připojený do konektoru A0](../../../../../translated_images/pi-soil-moisture-sensor.fdd7eb2393792cf6739cacf1985d9f55beda16d372f30d0b5a51d586f978a870.cs.png)

1. Zasuňte senzor vlhkosti půdy do půdy. Senzor má "nejvyšší poziční čáru" - bílou čáru přes senzor. Zasuňte senzor až k této čáře, ale ne dál.

![Senzor vlhkosti půdy Grove v půdě](../../../../../translated_images/soil-moisture-sensor-in-soil.bfad91002bda5e96.cs.png)

## Programování senzoru vlhkosti půdy

Raspberry Pi nyní může být naprogramováno pro použití připojeného senzoru vlhkosti půdy.

### Úkol - programování senzoru vlhkosti půdy

Naprogramujte zařízení.

1. Zapněte Raspberry Pi a počkejte, až se spustí.

1. Spusťte VS Code, buď přímo na Raspberry Pi, nebo se připojte pomocí rozšíření Remote SSH.

    > ⚠️ Můžete se podívat na [instrukce pro nastavení a spuštění VS Code v nightlight - lekce 1, pokud je to potřeba](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md).

1. Z terminálu vytvořte novou složku v domovském adresáři uživatele `pi` s názvem `soil-moisture-sensor`. V této složce vytvořte soubor s názvem `app.py`.

1. Otevřete tuto složku ve VS Code.

1. Přidejte následující kód do souboru `app.py` pro import potřebných knihoven:

    ```python
    import time
    from grove.adc import ADC
    ```

    Příkaz `import time` importuje modul `time`, který bude použit později v tomto úkolu.

    Příkaz `from grove.adc import ADC` importuje `ADC` z knihoven Grove Python. Tato knihovna obsahuje kód pro interakci s analogově-digitálním převodníkem na Pi Base Hat a čtení napětí z analogových senzorů.

1. Přidejte následující kód pod tento pro vytvoření instance třídy `ADC`:

    ```python
    adc = ADC()
    ```

1. Přidejte nekonečnou smyčku, která čte z tohoto ADC na pinu A0 a zapisuje výsledek do konzole. Tato smyčka může poté mezi čteními spát po dobu 10 sekund.

    ```python
    while True:
        soil_moisture = adc.read(0)
        print("Soil moisture:", soil_moisture)

        time.sleep(10)
    ```

1. Spusťte Python aplikaci. Uvidíte měření vlhkosti půdy zapsaná do konzole. Přidejte vodu do půdy nebo vyjměte senzor z půdy a sledujte, jak se hodnota mění.

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Soil moisture: 615
    Soil moisture: 612
    Soil moisture: 498
    Soil moisture: 493
    Soil moisture: 490
    Soil Moisture: 388
    ```

    V příkladu výstupu výše můžete vidět, jak napětí klesá, když se přidá voda.

> 💁 Tento kód najdete ve složce [code/pi](../../../../../2-farm/lessons/2-detect-soil-moisture/code/pi).

😀 Program senzoru vlhkosti půdy byl úspěšný!

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). I když se snažíme o přesnost, mějte prosím na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro kritické informace doporučujeme profesionální lidský překlad. Neodpovídáme za žádná nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.