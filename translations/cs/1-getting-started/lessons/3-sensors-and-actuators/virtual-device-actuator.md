# Vytvořte noční světlo - Virtuální IoT hardware

V této části lekce přidáte LED diodu do svého virtuálního IoT zařízení a použijete ji k vytvoření nočního světla.

## Virtuální hardware

Noční světlo potřebuje jeden akční člen, vytvořený v aplikaci CounterFit.

Akční člen je **LED dioda**. U fyzického IoT zařízení by to byla [světlo emitující dioda](https://wikipedia.org/wiki/Light-emitting_diode), která vyzařuje světlo, když jí prochází proud. Toto je digitální akční člen, který má 2 stavy: zapnuto a vypnuto. Poslání hodnoty 1 zapne LED diodu, a hodnoty 0 ji vypne.

Logika nočního světla v pseudokódu je:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### Přidání akčního členu do CounterFit

Pro použití virtuální LED diody ji musíte přidat do aplikace CounterFit.

#### Úkol - přidání akčního členu do CounterFit

Přidejte LED diodu do aplikace CounterFit.

1. Ujistěte se, že webová aplikace CounterFit běží z předchozí části tohoto úkolu. Pokud ne, spusťte ji a znovu přidejte světelný senzor.

1. Vytvořte LED diodu:

    1. V poli *Create actuator* v panelu *Actuator* rozbalte pole *Actuator type* a vyberte *LED*.

    1. Nastavte *Pin* na *5*.

    1. Vyberte tlačítko **Add** pro vytvoření LED diody na pinu 5.

    ![Nastavení LED diody](../../../../../translated_images/cs/counterfit-create-led.ba9db1c9b8c622a6.webp)

    LED dioda bude vytvořena a objeví se v seznamu akčních členů.

    ![Vytvořená LED dioda](../../../../../translated_images/cs/counterfit-led.c0ab02de6d256ad8.webp)

    Jakmile je LED dioda vytvořena, můžete změnit její barvu pomocí výběru *Color*. Vyberte tlačítko **Set** pro změnu barvy po jejím výběru.

### Naprogramování nočního světla

Noční světlo nyní může být naprogramováno pomocí světelného senzoru a LED diody v CounterFit.

#### Úkol - naprogramování nočního světla

Naprogramujte noční světlo.

1. Otevřete projekt nočního světla ve VS Code, který jste vytvořili v předchozí části tohoto úkolu. Pokud je to nutné, ukončete a znovu vytvořte terminál, aby běžel s použitím virtuálního prostředí.

1. Otevřete soubor `app.py`.

1. Přidejte následující kód do souboru `app.py` pro import požadované knihovny. Tento kód by měl být přidán na začátek, pod ostatní řádky `import`.

    ```python
    from counterfit_shims_grove.grove_led import GroveLed
    ```

    Příkaz `from counterfit_shims_grove.grove_led import GroveLed` importuje `GroveLed` z Python knihoven CounterFit Grove shim. Tato knihovna obsahuje kód pro interakci s LED diodou vytvořenou v aplikaci CounterFit.

1. Přidejte následující kód za deklaraci `light_sensor` pro vytvoření instance třídy, která spravuje LED diodu:

    ```python
    led = GroveLed(5)
    ```

    Řádek `led = GroveLed(5)` vytvoří instanci třídy `GroveLed`, která se připojuje k pinu **5** - CounterFit Grove pinu, ke kterému je LED dioda připojena.

1. Přidejte kontrolu uvnitř smyčky `while`, před `time.sleep`, pro kontrolu úrovní světla a zapnutí nebo vypnutí LED diody:

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    Tento kód kontroluje hodnotu `light`. Pokud je tato hodnota menší než 300, volá metodu `on` třídy `GroveLed`, která pošle digitální hodnotu 1 do LED diody, čímž ji zapne. Pokud je hodnota světla větší nebo rovna 300, volá metodu `off`, která pošle digitální hodnotu 0 do LED diody, čímž ji vypne.

    > 💁 Tento kód by měl být odsazen na stejnou úroveň jako řádek `print('Light level:', light)`, aby byl uvnitř smyčky while!

1. Z terminálu ve VS Code spusťte následující příkaz pro spuštění vaší Python aplikace:

    ```sh
    python3 app.py
    ```

    Hodnoty světla budou vypsány do konzole.

    ```output
    (.venv) ➜  GroveTest python3 app.py 
    Light level: 143
    Light level: 244
    Light level: 246
    Light level: 253
    ```

1. Změňte nastavení *Value* nebo *Random* pro změnu úrovně světla nad a pod 300. LED dioda se bude zapínat a vypínat.

![LED dioda v aplikaci CounterFit se zapíná a vypíná podle změn úrovně světla](../../../../../images/virtual-device-running-assignment-1-1.gif)

> 💁 Tento kód najdete ve složce [code-actuator/virtual-device](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/virtual-device).

😀 Program vašeho nočního světla byl úspěšný!

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). Ačkoli se snažíme o přesnost, mějte prosím na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace se doporučuje profesionální lidský překlad. Neodpovídáme za žádné nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.