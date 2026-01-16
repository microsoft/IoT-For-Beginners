<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "ea733bd0cdf2479e082373f765a08678",
  "translation_date": "2025-08-27T22:31:21+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/pi-sensor.md",
  "language_code": "cs"
}
-->
# Vytvořte noční světlo - Raspberry Pi

V této části lekce přidáte k Raspberry Pi světelný senzor.

## Hardware

Senzor pro tuto lekci je **světelný senzor**, který využívá [fotodiodu](https://wikipedia.org/wiki/Photodiode) k převodu světla na elektrický signál. Jedná se o analogový senzor, který posílá celočíselnou hodnotu od 0 do 1 000, což indikuje relativní množství světla, které neodpovídá žádné standardní jednotce měření, jako je například [lux](https://wikipedia.org/wiki/Lux).

Světelný senzor je externí Grove senzor a musí být připojen k Grove Base hat na Raspberry Pi.

### Připojte světelný senzor

Grove světelný senzor, který se používá k detekci úrovní světla, musí být připojen k Raspberry Pi.

#### Úkol - připojte světelný senzor

Připojte světelný senzor.

![Grove světelný senzor](../../../../../translated_images/cs/grove-light-sensor.b8127b7c434e632d6bcdb57587a14e9ef69a268a22df95d08628f62b8fa5505c.png)

1. Zasuňte jeden konec Grove kabelu do konektoru na modulu světelného senzoru. Kabel lze zasunout pouze jedním způsobem.

1. S vypnutým Raspberry Pi připojte druhý konec Grove kabelu do analogového konektoru označeného **A0** na Grove Base hat připojeném k Pi. Tento konektor je druhý zprava v řadě konektorů vedle GPIO pinů.

![Grove světelný senzor připojený ke konektoru A0](../../../../../translated_images/cs/pi-light-sensor.66cc1e31fa48cd7d5f23400d4b2119aa41508275cb7c778053a7923b4e972d7e.png)

## Naprogramujte světelný senzor

Zařízení nyní může být naprogramováno pomocí Grove světelného senzoru.

### Úkol - naprogramujte světelný senzor

Naprogramujte zařízení.

1. Zapněte Raspberry Pi a počkejte, až se spustí.

1. Otevřete projekt nočního světla ve VS Code, který jste vytvořili v předchozí části tohoto úkolu, buď přímo na Pi, nebo pomocí rozšíření Remote SSH.

1. Otevřete soubor `app.py` a odstraňte z něj veškerý kód.

1. Přidejte následující kód do souboru `app.py` pro import potřebných knihoven:

    ```python
    import time
    from grove.grove_light_sensor_v1_2 import GroveLightSensor
    ```

    Příkaz `import time` importuje modul `time`, který bude použit později v tomto úkolu.

    Příkaz `from grove.grove_light_sensor_v1_2 import GroveLightSensor` importuje `GroveLightSensor` z Grove Python knihoven. Tato knihovna obsahuje kód pro interakci s Grove světelným senzorem a byla nainstalována globálně během nastavení Pi.

1. Přidejte následující kód za výše uvedený kód pro vytvoření instance třídy, která spravuje světelný senzor:

    ```python
    light_sensor = GroveLightSensor(0)
    ```

    Řádek `light_sensor = GroveLightSensor(0)` vytvoří instanci třídy `GroveLightSensor`, která se připojuje k pinu **A0** - analogovému Grove pinu, ke kterému je světelný senzor připojen.

1. Přidejte nekonečnou smyčku za výše uvedený kód pro dotazování hodnoty světelného senzoru a její výpis do konzole:

    ```python
    while True:
        light = light_sensor.light
        print('Light level:', light)
    ```

    Tento kód přečte aktuální úroveň světla na stupnici 0-1 023 pomocí vlastnosti `light` třídy `GroveLightSensor`. Tato vlastnost čte analogovou hodnotu z pinu. Tato hodnota je poté vypsána do konzole.

1. Přidejte na konec `loop` krátkou pauzu o délce jedné sekundy, protože úrovně světla není třeba kontrolovat nepřetržitě. Pauza snižuje spotřebu energie zařízení.

    ```python
    time.sleep(1)
    ```

1. Z terminálu ve VS Code spusťte následující příkaz pro spuštění vašeho Python programu:

    ```sh
    python3 app.py
    ```

    Hodnoty světla budou vypsány do konzole. Zakryjte a odkryjte světelný senzor a hodnoty se změní:

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py 
    Light level: 634
    Light level: 634
    Light level: 634
    Light level: 230
    Light level: 104
    Light level: 290
    ```

> 💁 Tento kód najdete ve složce [code-sensor/pi](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/pi).

😀 Přidání senzoru do vašeho programu nočního světla bylo úspěšné!

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). I když se snažíme o přesnost, mějte prosím na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace doporučujeme profesionální lidský překlad. Neodpovídáme za žádné nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.