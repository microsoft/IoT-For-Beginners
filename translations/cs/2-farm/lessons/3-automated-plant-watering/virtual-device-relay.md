<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f8f541ee945545017a51aaf309aa37c3",
  "translation_date": "2025-08-27T23:28:46+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/virtual-device-relay.md",
  "language_code": "cs"
}
-->
# Ovládání relé - Virtuální IoT zařízení

V této části lekce přidáte k vašemu virtuálnímu IoT zařízení relé, kromě senzoru vlhkosti půdy, a budete ho ovládat na základě úrovně vlhkosti půdy.

## Virtuální hardware

Virtuální IoT zařízení bude používat simulované Grove relé. To udržuje tento lab stejný jako při použití Raspberry Pi s fyzickým Grove relé.

U fyzického IoT zařízení by relé bylo normálně otevřené relé (to znamená, že výstupní obvod je otevřený nebo odpojený, pokud není reléti poslán signál). Takové relé může zvládnout výstupní obvody až do 250V a 10A.

### Přidání relé do CounterFit

Pro použití virtuálního relé je potřeba ho přidat do aplikace CounterFit.

#### Úkol

Přidejte relé do aplikace CounterFit.

1. Otevřete projekt `soil-moisture-sensor` z minulé lekce ve VS Code, pokud již není otevřený. Budete do tohoto projektu přidávat.

1. Ujistěte se, že webová aplikace CounterFit běží.

1. Vytvořte relé:

    1. V poli *Create actuator* v panelu *Actuators* rozbalte pole *Actuator type* a vyberte *Relay*.

    1. Nastavte *Pin* na *5*.

    1. Klikněte na tlačítko **Add**, abyste vytvořili relé na pinu 5.

    ![Nastavení relé](../../../../../translated_images/cs/counterfit-create-relay.fa7c40fd0f2f6afc33b35ea94fcb235085be4861e14e3fe6b9b7bcfc82d1c888.png)

    Relé bude vytvořeno a objeví se v seznamu aktuátorů.

    ![Vytvořené relé](../../../../../translated_images/cs/counterfit-relay.bbf74c1dbdc8b9acd983367fcbd06703a402aefef6af54ddb28e11307ba8a12c.png)

## Naprogramování relé

Aplikace senzoru vlhkosti půdy nyní může být naprogramována k použití virtuálního relé.

### Úkol

Naprogramujte virtuální zařízení.

1. Otevřete projekt `soil-moisture-sensor` z minulé lekce ve VS Code, pokud již není otevřený. Budete do tohoto projektu přidávat.

1. Přidejte následující kód do souboru `app.py` pod existující importy:

    ```python
    from counterfit_shims_grove.grove_relay import GroveRelay
    ```

    Tento příkaz importuje `GroveRelay` z knihoven Grove Python shim pro interakci s virtuálním Grove relé.

1. Přidejte následující kód pod deklaraci třídy `ADC`, abyste vytvořili instanci `GroveRelay`:

    ```python
    relay = GroveRelay(5)
    ```

    Tímto vytvoříte relé na pinu **5**, na který jste relé připojili.

1. Pro otestování, že relé funguje, přidejte následující kód do smyčky `while True:`:

    ```python
    relay.on()
    time.sleep(.5)
    relay.off()
    ```

    Kód zapne relé, počká 0,5 sekundy, a poté relé vypne.

1. Spusťte Python aplikaci. Relé se bude zapínat a vypínat každých 10 sekund, s půlsekundovou prodlevou mezi zapnutím a vypnutím. Uvidíte, jak se virtuální relé v aplikaci CounterFit zavírá a otevírá, když se relé zapíná a vypíná.

    ![Virtuální relé se zapíná a vypíná](../../../../../images/virtual-relay-turn-on-off.gif)

## Ovládání relé na základě vlhkosti půdy

Nyní, když relé funguje, může být ovládáno na základě odečtů vlhkosti půdy.

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

    Tento kód kontroluje úroveň vlhkosti půdy ze senzoru vlhkosti půdy. Pokud je nad 450, zapne relé, a pokud klesne pod 450, relé vypne.

    > 💁 Pamatujte, že kapacitní senzor vlhkosti půdy čte: čím nižší je úroveň vlhkosti půdy, tím více vlhkosti je v půdě, a naopak.

1. Spusťte Python aplikaci. Uvidíte, jak se relé zapíná nebo vypíná v závislosti na úrovních vlhkosti půdy. Změňte *Value* nebo *Random* nastavení senzoru vlhkosti půdy, abyste viděli změnu hodnoty.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 Tento kód najdete ve složce [code-relay/virtual-device](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/virtual-device).

😀 Vaše virtuální aplikace senzoru vlhkosti půdy ovládající relé byla úspěšná!

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). I když se snažíme o přesnost, mějte na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace se doporučuje profesionální lidský překlad. Nenese odpovědnost za žádné nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.