<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f3c5d8afa2ef6a0b425ef8ff20615cb4",
  "translation_date": "2025-08-27T23:30:27+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/wio-terminal-relay.md",
  "language_code": "cs"
}
-->
# Ovládání relé - Wio Terminal

V této části lekce přidáte k Wio Terminalu relé kromě senzoru vlhkosti půdy a budete jej ovládat na základě úrovně vlhkosti půdy.

## Hardware

Wio Terminal potřebuje relé.

Použité relé je [Grove relé](https://www.seeedstudio.com/Grove-Relay.html), běžně otevřené relé (to znamená, že výstupní obvod je otevřený nebo odpojený, pokud není reléti poslán signál), které zvládne výstupní obvody až do 250V a 10A.

Jedná se o digitální akční člen, takže se připojuje k digitálním pinům na Wio Terminalu. Kombinovaný analogový/digitální port je již používán senzorem vlhkosti půdy, takže toto relé se připojuje do druhého portu, který je kombinovaný I2C a digitální port.

### Připojení relé

Grove relé lze připojit k digitálnímu portu Wio Terminalu.

#### Úkol

Připojte relé.

![Grove relé](../../../../../translated_images/grove-relay.d426958ca210fbd0fb7983d7edc069d46c73a8b0a099d94797bd756f7b6bb6be.cs.png)

1. Zasuňte jeden konec Grove kabelu do zásuvky na relé. Kabel lze zasunout pouze jedním způsobem.

1. S Wio Terminalem odpojeným od počítače nebo jiného zdroje napájení připojte druhý konec Grove kabelu do levé zásuvky Grove na Wio Terminalu, pokud se díváte na obrazovku. Senzor vlhkosti půdy ponechte připojený k pravé zásuvce.

![Grove relé připojené k levé zásuvce a senzor vlhkosti půdy připojený k pravé zásuvce](../../../../../translated_images/wio-relay-and-soil-moisture-sensor.ed722202d42babe0.cs.png)

1. Zasuňte senzor vlhkosti půdy do půdy, pokud tam již není z předchozí lekce.

## Naprogramování relé

Nyní lze Wio Terminal naprogramovat tak, aby používal připojené relé.

### Úkol

Naprogramujte zařízení.

1. Otevřete projekt `soil-moisture-sensor` z minulé lekce ve VS Code, pokud již není otevřený. Budete do něj přidávat další kód.

2. Pro tento akční člen neexistuje knihovna - jedná se o digitální akční člen ovládaný vysokým nebo nízkým signálem. Pro zapnutí pošlete na pin vysoký signál (3,3V), pro vypnutí nízký signál (0V). To lze provést pomocí vestavěné funkce Arduino [`digitalWrite`](https://www.arduino.cc/reference/en/language/functions/digital-io/digitalwrite/). Začněte přidáním následujícího kódu na konec funkce `setup`, abyste nastavili kombinovaný I2C/digitální port jako výstupní pin pro odesílání napětí do relé:

    ```cpp
    pinMode(PIN_WIRE_SCL, OUTPUT);
    ```

    `PIN_WIRE_SCL` je číslo portu pro kombinovaný I2C/digitální port.

1. Pro otestování, zda relé funguje, přidejte následující kód do funkce `loop`, pod poslední `delay`:

    ```cpp
    digitalWrite(PIN_WIRE_SCL, HIGH);
    delay(500);
    digitalWrite(PIN_WIRE_SCL, LOW);
    ```

    Tento kód pošle na pin připojený k relé vysoký signál, čímž relé zapne, počká 500 ms (půl sekundy) a poté pošle nízký signál, čímž relé vypne.

1. Sestavte a nahrajte kód do Wio Terminalu.

1. Po nahrání se relé bude zapínat a vypínat každých 10 sekund, s půlsekundovým zpožděním mezi zapnutím a vypnutím. Uslyšíte cvaknutí relé při zapnutí a vypnutí. LED dioda na desce Grove se rozsvítí, když je relé zapnuté, a zhasne, když je vypnuté.

    ![Relé se zapíná a vypíná](../../../../../images/relay-turn-on-off.gif)

## Ovládání relé na základě vlhkosti půdy

Nyní, když relé funguje, může být ovládáno na základě hodnot vlhkosti půdy.

### Úkol

Ovládejte relé.

1. Smažte 3 řádky kódu, které jste přidali pro testování relé. Nahraďte je následujícím kódem:

    ```cpp
    if (soil_moisture > 450)
    {
        Serial.println("Soil Moisture is too low, turning relay on.");
        digitalWrite(PIN_WIRE_SCL, HIGH);
    }
    else
    {
        Serial.println("Soil Moisture is ok, turning relay off.");
        digitalWrite(PIN_WIRE_SCL, LOW);
    }
    ```

    Tento kód kontroluje úroveň vlhkosti půdy ze senzoru vlhkosti půdy. Pokud je hodnota vyšší než 450, relé se zapne, a pokud je nižší než 450, relé se vypne.

    > 💁 Pamatujte, že kapacitní senzor vlhkosti půdy čte nižší hodnoty při vyšší vlhkosti půdy a vyšší hodnoty při nižší vlhkosti.

1. Sestavte a nahrajte kód do Wio Terminalu.

1. Sledujte zařízení přes sériový monitor. Uvidíte, jak se relé zapíná nebo vypíná v závislosti na úrovni vlhkosti půdy. Vyzkoušejte v suché půdě a poté přidejte vodu.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 Tento kód najdete ve složce [code-relay/wio-terminal](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/wio-terminal).

😀 Program pro ovládání relé senzorem vlhkosti půdy byl úspěšný!

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). I když se snažíme o přesnost, mějte prosím na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace doporučujeme profesionální lidský překlad. Neodpovídáme za žádná nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.