# Měření vlhkosti půdy - Wio Terminal

V této části lekce přidáte kapacitní senzor vlhkosti půdy k vašemu Wio Terminalu a budete z něj číst hodnoty.

## Hardware

Wio Terminal potřebuje kapacitní senzor vlhkosti půdy.

Senzor, který budete používat, je [Kapacitní senzor vlhkosti půdy](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html), který měří vlhkost půdy detekcí kapacity půdy, vlastnosti, která se mění s vlhkostí půdy. Jak se vlhkost půdy zvyšuje, napětí klesá.

Jedná se o analogový senzor, který se připojuje k analogovým pinům na Wio Terminalu, přičemž využívá vestavěný ADC k vytvoření hodnoty od 0 do 1 023.

### Připojení senzoru vlhkosti půdy

Grove senzor vlhkosti půdy lze připojit k konfigurovatelnému analogovému/digitálnímu portu Wio Terminalu.

#### Úkol - připojte senzor vlhkosti půdy

Připojte senzor vlhkosti půdy.

![Grove senzor vlhkosti půdy](../../../../../translated_images/cs/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78b.webp)

1. Zasuňte jeden konec Grove kabelu do konektoru na senzoru vlhkosti půdy. Kabel lze zasunout pouze jedním způsobem.

1. S odpojeným Wio Terminalem od počítače nebo jiného zdroje napájení připojte druhý konec Grove kabelu do pravého Grove konektoru na Wio Terminalu, když se díváte na obrazovku. Jedná se o konektor nejdále od tlačítka napájení.

![Grove senzor vlhkosti půdy připojený k pravému konektoru](../../../../../translated_images/cs/wio-soil-moisture-sensor.46919b61c3f6cb74.webp)

1. Zasuňte senzor vlhkosti půdy do půdy. Senzor má „nejvyšší poziční čáru“ – bílou čáru přes senzor. Zasuňte senzor až k této čáře, ale ne dál.

![Grove senzor vlhkosti půdy v půdě](../../../../../translated_images/cs/soil-moisture-sensor-in-soil.bfad91002bda5e96.webp)

1. Nyní můžete připojit Wio Terminal k vašemu počítači.

## Naprogramování senzoru vlhkosti půdy

Wio Terminal nyní může být naprogramován pro použití připojeného senzoru vlhkosti půdy.

### Úkol - naprogramujte senzor vlhkosti půdy

Naprogramujte zařízení.

1. Vytvořte zcela nový projekt pro Wio Terminal pomocí PlatformIO. Nazvěte tento projekt `soil-moisture-sensor`. Přidejte kód do funkce `setup` pro konfiguraci sériového portu.

    > ⚠️ Můžete se podívat na [instrukce pro vytvoření projektu PlatformIO v projektu 1, lekci 1, pokud je to potřeba](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project).

1. Pro tento senzor neexistuje knihovna, místo toho můžete číst z analogového pinu pomocí vestavěné funkce Arduino [`analogRead`](https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/). Začněte konfigurací analogového pinu pro vstup, aby bylo možné z něj číst hodnoty, přidáním následujícího do funkce `setup`.

    ```cpp
    pinMode(A0, INPUT);
    ```

    Tím nastavíte pin `A0`, kombinovaný analogový/digitální pin, jako vstupní pin, ze kterého lze číst napětí.

1. Přidejte následující do funkce `loop` pro čtení napětí z tohoto pinu:

    ```cpp
    int soil_moisture = analogRead(A0);
    ```

1. Pod tento kód přidejte následující kód pro tisk hodnoty na sériový port:

    ```cpp
    Serial.print("Soil Moisture: ");
    Serial.println(soil_moisture);
    ```

1. Nakonec přidejte na konec zpoždění 10 sekund:

    ```cpp
    delay(10000);
    ```

1. Sestavte a nahrajte kód do Wio Terminalu.

    > ⚠️ Můžete se podívat na [instrukce pro vytvoření projektu PlatformIO v projektu 1, lekci 1, pokud je to potřeba](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app).

1. Po nahrání můžete sledovat vlhkost půdy pomocí sériového monitoru. Přidejte trochu vody do půdy nebo vyjměte senzor z půdy a sledujte, jak se hodnota mění.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Soil Moisture: 526
    Soil Moisture: 529
    Soil Moisture: 521
    Soil Moisture: 494
    Soil Moisture: 454
    Soil Moisture: 456
    Soil Moisture: 395
    Soil Moisture: 388
    Soil Moisture: 394
    Soil Moisture: 391
    ```

    V příkladu výstupu výše můžete vidět, jak napětí klesá, když je přidána voda.

> 💁 Tento kód najdete ve složce [code/wio-terminal](../../../../../2-farm/lessons/2-detect-soil-moisture/code/wio-terminal).

😀 Program senzoru vlhkosti půdy byl úspěšný!

---

**Upozornění**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). I když se snažíme o přesnost, mějte prosím na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za závazný zdroj. Pro důležité informace se doporučuje profesionální lidský překlad. Nezodpovídáme za jakékoli nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.