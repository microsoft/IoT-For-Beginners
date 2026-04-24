# Ovládání relé - Raspberry Pi

V této části lekce přidáte k Raspberry Pi relé, kromě senzoru vlhkosti půdy, a budete jej ovládat na základě úrovně vlhkosti půdy.

## Hardware

Raspberry Pi potřebuje relé.

Relé, které použijete, je [Grove relé](https://www.seeedstudio.com/Grove-Relay.html), běžně otevřené relé (to znamená, že výstupní obvod je otevřený nebo odpojený, pokud není do relé odeslán signál), které zvládne výstupní obvody až do 250V a 10A.

Jedná se o digitální akční člen, takže se připojuje k digitálnímu pinu na Grove Base Hat.

### Připojení relé

Grove relé lze připojit k Raspberry Pi.

#### Úkol

Připojte relé.

![Grove relé](../../../../../translated_images/cs/grove-relay.d426958ca210fbd0.webp)

1. Zasuňte jeden konec Grove kabelu do konektoru na relé. Kabel lze zasunout pouze jedním způsobem.

1. S vypnutým Raspberry Pi připojte druhý konec Grove kabelu do digitálního konektoru označeného **D5** na Grove Base Hat připojeném k Pi. Tento konektor je druhý zleva v řadě konektorů vedle GPIO pinů. Senzor vlhkosti půdy ponechte připojený ke konektoru **A0**.

![Grove relé připojené ke konektoru D5 a senzor vlhkosti půdy připojený ke konektoru A0](../../../../../translated_images/cs/pi-relay-and-soil-moisture-sensor.02f3198975b8c53e.webp)

1. Zasuňte senzor vlhkosti půdy do půdy, pokud tam již není z předchozí lekce.

## Naprogramování relé

Raspberry Pi nyní může být naprogramováno pro použití připojeného relé.

### Úkol

Naprogramujte zařízení.

1. Zapněte Pi a počkejte, až se spustí.

1. Otevřete projekt `soil-moisture-sensor` z minulé lekce ve VS Code, pokud již není otevřený. Budete do tohoto projektu přidávat.

1. Přidejte následující kód do souboru `app.py` pod stávající importy:

    ```python
    from grove.grove_relay import GroveRelay
    ```

    Tento příkaz importuje `GroveRelay` z knihoven Grove Python pro interakci s Grove relé.

1. Přidejte následující kód pod deklaraci třídy `ADC` pro vytvoření instance `GroveRelay`:

    ```python
    relay = GroveRelay(5)
    ```

    Tím se vytvoří relé na pinu **D5**, digitálním pinu, ke kterému jste relé připojili.

1. Pro otestování, zda relé funguje, přidejte následující kód do smyčky `while True:`:

    ```python
    relay.on()
    time.sleep(.5)
    relay.off()
    ```

    Tento kód zapne relé, počká 0,5 sekundy, a poté relé vypne.

1. Spusťte Python aplikaci. Relé se bude zapínat a vypínat každých 10 sekund, s půlsekundovým zpožděním mezi zapnutím a vypnutím. Uslyšíte cvaknutí relé při zapnutí a vypnutí. LED dioda na Grove desce se rozsvítí, když je relé zapnuté, a zhasne, když je vypnuté.

    ![Relé se zapíná a vypíná](../../../../../images/relay-turn-on-off.gif)

## Ovládání relé na základě vlhkosti půdy

Nyní, když relé funguje, může být ovládáno na základě hodnot vlhkosti půdy.

### Úkol

Ovládejte relé.

1. Smažte 3 řádky kódu, které jste přidali pro testování relé. Nahraďte je následujícím kódem:

    ```python
    if soil_moisture > 450:
        print("Soil Moisture is too low, turning relay on.")
        relay.on()
    else:
        print("Soil Moisture is ok, turning relay off.")
        relay.off()
    ```

    Tento kód kontroluje úroveň vlhkosti půdy ze senzoru vlhkosti půdy. Pokud je hodnota vyšší než 450, relé se zapne, a vypne se, když hodnota klesne pod 450.

    > 💁 Pamatujte, že kapacitní senzor vlhkosti půdy čte: čím nižší je úroveň vlhkosti půdy, tím více vlhkosti je v půdě, a naopak.

1. Spusťte Python aplikaci. Uvidíte, jak se relé zapíná nebo vypíná v závislosti na úrovni vlhkosti půdy. Vyzkoušejte v suché půdě, poté přidejte vodu.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 Tento kód najdete ve složce [code-relay/pi](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/pi).

😀 Program pro ovládání relé senzorem vlhkosti půdy byl úspěšný!

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). Přestože se snažíme o přesnost, mějte prosím na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace doporučujeme profesionální lidský překlad. Neodpovídáme za žádná nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.