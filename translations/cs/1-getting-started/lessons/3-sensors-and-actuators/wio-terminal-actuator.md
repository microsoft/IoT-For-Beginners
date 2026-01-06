<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "db44083b4dc6fb06eac83c4f16448940",
  "translation_date": "2025-08-27T22:32:28+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/wio-terminal-actuator.md",
  "language_code": "cs"
}
-->
# Vytvořte noční světlo - Wio Terminal

V této části lekce přidáte k Wio Terminal LED diodu a použijete ji k vytvoření nočního světla.

## Hardware

Noční světlo nyní potřebuje akční člen.

Akčním členem je **LED**, [svítivá dioda](https://wikipedia.org/wiki/Light-emitting_diode), která vydává světlo, když jí prochází proud. Jedná se o digitální akční člen, který má dva stavy: zapnuto a vypnuto. Odesláním hodnoty 1 se LED zapne, hodnotou 0 se vypne. Jedná se o externí Grove akční člen, který je třeba připojit k Wio Terminal.

Logika nočního světla v pseudokódu je:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### Připojte LED

Grove LED je dodávána jako modul s výběrem LED diod, což vám umožňuje zvolit si barvu.

#### Úkol - připojte LED

Připojte LED.

![Grove LED](../../../../../translated_images/grove-led.6c853be93f473cf2c439cfc74bb1064732b22251a83cedf66e62f783f9cc1a79.cs.png)

1. Vyberte si svou oblíbenou LED a vložte její nožičky do dvou otvorů na modulu LED.

    LED diody jsou svítivé diody a diody jsou elektronické součástky, které mohou vést proud pouze jedním směrem. To znamená, že LED musí být připojena správným způsobem, jinak nebude fungovat.

    Jedna z nožiček LED je kladný pin, druhá je záporný pin. LED není dokonale kulatá a na jedné straně je mírně plošší. Mírně plošší strana je záporný pin. Když připojujete LED k modulu, ujistěte se, že pin na zaoblené straně je připojen k zásuvce označené **+** na vnější straně modulu, a plošší strana je připojena k zásuvce blíže ke středu modulu.

1. Modul LED má otočný knoflík, který umožňuje ovládat jas. Nejprve jej otočte úplně nahoru otáčením proti směru hodinových ručiček, dokud to půjde, pomocí malého křížového šroubováku.

1. Zasuňte jeden konec Grove kabelu do zásuvky na modulu LED. Půjde to pouze jedním směrem.

1. S Wio Terminal odpojeným od počítače nebo jiného zdroje napájení připojte druhý konec Grove kabelu k pravé Grove zásuvce na Wio Terminal, když se díváte na obrazovku. Jedná se o zásuvku nejdále od tlačítka napájení.

    > 💁 Pravá Grove zásuvka může být použita s analogovými nebo digitálními senzory a akčními členy. Levá zásuvka je pouze pro digitální senzory a akční členy.

![Grove LED připojená k pravé zásuvce](../../../../../translated_images/wio-led.265a1897e72d7f21.cs.png)

## Naprogramujte noční světlo

Noční světlo nyní může být naprogramováno pomocí vestavěného světelného senzoru a Grove LED.

### Úkol - naprogramujte noční světlo

Naprogramujte noční světlo.

1. Otevřete projekt nočního světla ve VS Code, který jste vytvořili v předchozí části tohoto úkolu.

1. Přidejte následující řádek na konec funkce `setup`:

    ```cpp
    pinMode(D0, OUTPUT);
    ```

    Tento řádek konfiguruje pin používaný ke komunikaci s LED přes Grove port.

    Pin `D0` je digitální pin pro pravou Grove zásuvku. Tento pin je nastaven na `OUTPUT`, což znamená, že je připojen k akčnímu členu a data budou na pin zapisována.

1. Přidejte následující kód těsně před `delay` ve funkci loop:

    ```cpp
    if (light < 300)
    {
        digitalWrite(D0, HIGH);
    }
    else
    {
        digitalWrite(D0, LOW);
    }
    ```

    Tento kód kontroluje hodnotu `light`. Pokud je tato hodnota menší než 300, odešle hodnotu `HIGH` na digitální pin `D0`. Tato hodnota `HIGH` je hodnota 1, která zapne LED. Pokud je hodnota světla větší nebo rovna 300, odešle se hodnota `LOW` (0), která LED vypne.

    > 💁 Při odesílání digitálních hodnot akčním členům je hodnota LOW 0V a hodnota HIGH je maximální napětí pro zařízení. Pro Wio Terminal je napětí HIGH 3,3V.

1. Znovu připojte Wio Terminal k počítači a nahrajte nový kód, jak jste to udělali dříve.

1. Připojte Serial Monitor. Hodnoty světla budou vypisovány do terminálu.

    ```output
    > Executing task: platformio device monitor <

    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Light value: 4
    Light value: 5
    Light value: 4
    Light value: 158
    Light value: 343
    Light value: 348
    Light value: 344
    ```

1. Zakryjte a odkryjte světelný senzor. Všimněte si, jak se LED rozsvítí, pokud je úroveň světla 300 nebo méně, a zhasne, když je úroveň světla větší než 300.

![LED připojená k WIO se rozsvěcuje a zhasíná podle změn úrovně světla](../../../../../images/wio-running-assignment-1-1.gif)

> 💁 Tento kód najdete ve složce [code-actuator/wio-terminal](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/wio-terminal).

😀 Váš program pro noční světlo byl úspěšný!

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). I když se snažíme o přesnost, mějte prosím na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace se doporučuje profesionální lidský překlad. Neodpovídáme za žádná nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.