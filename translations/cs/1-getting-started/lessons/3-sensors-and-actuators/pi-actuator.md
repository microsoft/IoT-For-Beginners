# Vytvořte noční světlo - Raspberry Pi

V této části lekce přidáte LED diodu k vašemu Raspberry Pi a použijete ji k vytvoření nočního světla.

## Hardware

Noční světlo nyní potřebuje akční člen.

Akčním členem je **LED**, [světelná dioda](https://wikipedia.org/wiki/Light-emitting_diode), která vyzařuje světlo, když jí prochází proud. Jedná se o digitální akční člen, který má dva stavy: zapnuto a vypnuto. Poslání hodnoty 1 zapne LED, zatímco hodnota 0 ji vypne. LED je externí Grove akční člen, který je třeba připojit k Grove Base hat na Raspberry Pi.

Logika nočního světla v pseudokódu je:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### Připojte LED

Grove LED je dodávána jako modul s výběrem LED diod, což vám umožňuje zvolit barvu.

#### Úkol - připojte LED

Připojte LED.

![Grove LED](../../../../../translated_images/cs/grove-led.6c853be93f473cf2.webp)

1. Vyberte svou oblíbenou LED diodu a vložte její nožičky do dvou otvorů na modulu LED.

    LED diody jsou světelné diody a diody jsou elektronické součástky, které mohou přenášet proud pouze jedním směrem. To znamená, že LED musí být připojena správným směrem, jinak nebude fungovat.

    Jedna z nožiček LED je kladný pin, druhá je záporný pin. LED není dokonale kulatá a na jedné straně je mírně plošší. Mírně plošší strana je záporný pin. Když připojujete LED k modulu, ujistěte se, že pin u zaoblené strany je připojen k zásuvce označené **+** na vnější straně modulu, a plošší strana je připojena k zásuvce blíže ke středu modulu.

1. Modul LED má otočný knoflík, který umožňuje ovládat jas. Na začátku jej otočte úplně nahoru proti směru hodinových ručiček pomocí malého křížového šroubováku.

1. Vložte jeden konec Grove kabelu do zásuvky na modulu LED. Kabel lze vložit pouze jedním směrem.

1. S vypnutým Raspberry Pi připojte druhý konec Grove kabelu k digitální zásuvce označené **D5** na Grove Base hat připojeném k Pi. Tato zásuvka je druhá zleva v řadě zásuvek vedle GPIO pinů.

![Grove LED připojená k zásuvce D5](../../../../../translated_images/cs/pi-led.97f1d474981dc35d.webp)

## Naprogramujte noční světlo

Noční světlo nyní může být naprogramováno pomocí Grove světelného senzoru a Grove LED.

### Úkol - naprogramujte noční světlo

Naprogramujte noční světlo.

1. Zapněte Pi a počkejte, až se spustí.

1. Otevřete projekt nočního světla ve VS Code, který jste vytvořili v předchozí části tohoto úkolu, buď přímo na Pi, nebo připojením pomocí rozšíření Remote SSH.

1. Přidejte následující kód do souboru `app.py`, abyste importovali požadovanou knihovnu. Tento kód by měl být přidán na začátek, pod ostatní řádky `import`.

    ```python
    from grove.grove_led import GroveLed
    ```

    Příkaz `from grove.grove_led import GroveLed` importuje `GroveLed` z Grove Python knihoven. Tato knihovna obsahuje kód pro interakci s Grove LED.

1. Přidejte následující kód za deklaraci `light_sensor`, abyste vytvořili instanci třídy, která spravuje LED:

    ```python
    led = GroveLed(5)
    ```

    Řádek `led = GroveLed(5)` vytvoří instanci třídy `GroveLed`, která se připojuje k pinu **D5** - digitálnímu Grove pinu, ke kterému je LED připojena.

    > 💁 Všechny zásuvky mají unikátní čísla pinů. Piny 0, 2, 4 a 6 jsou analogové piny, piny 5, 16, 18, 22, 24 a 26 jsou digitální piny.

1. Přidejte kontrolu uvnitř smyčky `while` a před `time.sleep`, která kontroluje úroveň světla a zapíná nebo vypíná LED:

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    Tento kód kontroluje hodnotu `light`. Pokud je tato hodnota menší než 300, volá metodu `on` třídy `GroveLed`, která posílá digitální hodnotu 1 do LED, čímž ji zapne. Pokud je hodnota světla větší nebo rovna 300, volá metodu `off`, která posílá digitální hodnotu 0 do LED, čímž ji vypne.

    > 💁 Tento kód by měl být odsazen na stejnou úroveň jako řádek `print('Light level:', light)`, aby byl uvnitř smyčky while!

    > 💁 Při posílání digitálních hodnot do akčních členů je hodnota 0 rovna 0V a hodnota 1 je maximální napětí pro zařízení. Pro Raspberry Pi s Grove senzory a akčními členy je napětí 1 rovno 3.3V.

1. Z terminálu ve VS Code spusťte následující příkaz, abyste spustili svou Python aplikaci:

    ```sh
    python3 app.py
    ```

    Hodnoty světla budou vypsány do konzole.

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py 
    Light level: 634
    Light level: 634
    Light level: 634
    Light level: 230
    Light level: 104
    Light level: 290
    ```

1. Zakryjte a odkryjte světelný senzor. Všimněte si, jak se LED rozsvítí, pokud je úroveň světla 300 nebo méně, a zhasne, když je úroveň světla větší než 300.

    > 💁 Pokud se LED nerozsvítí, ujistěte se, že je připojena správným směrem a otočný knoflík je nastaven na plné zapnutí.

![LED připojená k Pi se rozsvěcuje a zhasíná podle změn úrovně světla](../../../../../images/pi-running-assignment-1-1.gif)

> 💁 Tento kód najdete ve složce [code-actuator/pi](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/pi).

😀 Program vašeho nočního světla byl úspěšný!

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). I když se snažíme o přesnost, mějte prosím na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace doporučujeme profesionální lidský překlad. Neodpovídáme za žádná nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.