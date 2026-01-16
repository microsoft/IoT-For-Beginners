<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7678f7c67b97ee52d5727496dcd7d346",
  "translation_date": "2025-08-27T23:15:35+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/pi-temp.md",
  "language_code": "cs"
}
-->
# Měření teploty - Raspberry Pi

V této části lekce přidáte k Raspberry Pi teplotní senzor.

## Hardware

Senzor, který použijete, je [DHT11 senzor vlhkosti a teploty](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html), který kombinuje 2 senzory v jednom balení. Tento senzor je poměrně populární a existuje mnoho komerčně dostupných senzorů, které kombinují měření teploty, vlhkosti a někdy i atmosférického tlaku. Komponenta pro měření teploty je termistor s negativním teplotním koeficientem (NTC), což je termistor, jehož odpor klesá s rostoucí teplotou.

Jedná se o digitální senzor, který má vestavěný ADC (analogově-digitální převodník) pro vytvoření digitálního signálu obsahujícího data o teplotě a vlhkosti, která může mikrořadič číst.

### Připojení teplotního senzoru

Teplotní senzor Grove lze připojit k Raspberry Pi.

#### Úkol

Připojte teplotní senzor.

![Teplotní senzor Grove](../../../../../translated_images/cs/grove-dht11.07f8eafceee170043efbb53e1d15722bd4e00fbaa9ff74290b57e9f66eb82c17.png)

1. Zasuňte jeden konec kabelu Grove do konektoru na senzoru vlhkosti a teploty. Kabel lze zasunout pouze jedním směrem.

1. S vypnutým Raspberry Pi připojte druhý konec kabelu Grove do digitálního konektoru označeného **D5** na Grove Base hat připojeném k Pi. Tento konektor je druhý zleva v řadě konektorů vedle GPIO pinů.

![Teplotní senzor Grove připojený ke konektoru A0](../../../../../translated_images/cs/pi-temperature-sensor.3ff82fff672c8e565ef25a39d26d111de006b825a7e0867227ef4e7fbff8553c.png)

## Naprogramování teplotního senzoru

Zařízení nyní může být naprogramováno pro použití připojeného teplotního senzoru.

### Úkol

Naprogramujte zařízení.

1. Zapněte Pi a počkejte, až se spustí.

1. Spusťte VS Code, buď přímo na Pi, nebo se připojte pomocí rozšíření Remote SSH.

    > ⚠️ Pokud potřebujete, můžete se podívat na [instrukce pro nastavení a spuštění VS Code v lekci 1](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md).

1. Z terminálu vytvořte novou složku v domovském adresáři uživatele `pi` s názvem `temperature-sensor`. V této složce vytvořte soubor s názvem `app.py`:

    ```sh
    mkdir temperature-sensor
    cd temperature-sensor
    touch app.py
    ```

1. Otevřete tuto složku ve VS Code.

1. Pro použití senzoru vlhkosti a teploty je třeba nainstalovat další balíček Pip. Z terminálu ve VS Code spusťte následující příkaz pro instalaci tohoto balíčku na Pi:

    ```sh
    pip3 install seeed-python-dht
    ```

1. Přidejte následující kód do souboru `app.py` pro import potřebných knihoven:

    ```python
    import time
    from seeed_dht import DHT
    ```

    Příkaz `from seeed_dht import DHT` importuje třídu `DHT` pro interakci se senzorem teploty Grove z modulu `seeed_dht`.

1. Přidejte následující kód za výše uvedený kód pro vytvoření instance třídy, která spravuje teplotní senzor:

    ```python
    sensor = DHT("11", 5)
    ```

    Tento kód deklaruje instanci třídy `DHT`, která spravuje **D**igitální **H**umidity a **T**emperature senzor. První parametr říká kódu, že použitý senzor je *DHT11* - knihovna, kterou používáte, podporuje i jiné varianty tohoto senzoru. Druhý parametr říká kódu, že senzor je připojen k digitálnímu portu `D5` na Grove Base hat.

    > ✅ Pamatujte, že všechny konektory mají unikátní čísla pinů. Piny 0, 2, 4 a 6 jsou analogové piny, piny 5, 16, 18, 22, 24 a 26 jsou digitální piny.

1. Přidejte nekonečnou smyčku za výše uvedený kód pro čtení hodnoty teplotního senzoru a její výpis do konzole:

    ```python
    while True:
        _, temp = sensor.read()
        print(f'Temperature {temp}°C')
    ```

    Volání `sensor.read()` vrací dvojici hodnot vlhkosti a teploty. Potřebujete pouze hodnotu teploty, takže vlhkost je ignorována. Hodnota teploty je poté vypsána do konzole.

1. Přidejte krátkou pauzu deset sekund na konci `loop`, protože úroveň teploty není třeba kontrolovat nepřetržitě. Pauza snižuje spotřebu energie zařízení.

    ```python
    time.sleep(10)
    ```

1. Z terminálu ve VS Code spusťte následující příkaz pro spuštění vaší Python aplikace:

    ```sh
    python3 app.py
    ```

    Měli byste vidět hodnoty teploty vypisované do konzole. Použijte něco k zahřátí senzoru, například přitisknutí palce na něj nebo použití ventilátoru, abyste viděli změny hodnot:

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py 
    Temperature 26°C
    Temperature 26°C
    Temperature 28°C
    Temperature 30°C
    Temperature 32°C
    ```

> 💁 Tento kód najdete ve složce [code-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/pi).

😀 Vaše programování teplotního senzoru bylo úspěšné!

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). Ačkoli se snažíme o přesnost, mějte na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace se doporučuje profesionální lidský překlad. Neodpovídáme za žádné nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.