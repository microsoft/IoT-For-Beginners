<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "59263d094f20b302053888cd236880c3",
  "translation_date": "2025-08-27T23:23:57+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp.md",
  "language_code": "cs"
}
-->
# Měření teploty - Wio Terminal

V této části lekce přidáte k Wio Terminalu teplotní senzor a budete z něj číst hodnoty teploty.

## Hardware

Wio Terminal potřebuje teplotní senzor.

Senzor, který použijete, je [DHT11 senzor vlhkosti a teploty](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html), který kombinuje 2 senzory v jednom balení. Tento senzor je poměrně populární a existuje mnoho komerčně dostupných senzorů, které kombinují měření teploty, vlhkosti a někdy i atmosférického tlaku. Komponenta pro měření teploty je termistor s negativním teplotním koeficientem (NTC), což je termistor, jehož odpor klesá s rostoucí teplotou.

Jedná se o digitální senzor, takže má vestavěný ADC, který vytváří digitální signál obsahující data o teplotě a vlhkosti, která může mikrořadič číst.

### Připojení teplotního senzoru

Grove teplotní senzor lze připojit k digitálnímu portu Wio Terminalu.

#### Úkol - připojte teplotní senzor

Připojte teplotní senzor.

![Grove teplotní senzor](../../../../../translated_images/grove-dht11.07f8eafceee170043efbb53e1d15722bd4e00fbaa9ff74290b57e9f66eb82c17.cs.png)

1. Zasuňte jeden konec Grove kabelu do konektoru na senzoru vlhkosti a teploty. Kabel lze zasunout pouze jedním směrem.

1. S Wio Terminalem odpojeným od počítače nebo jiného zdroje napájení připojte druhý konec Grove kabelu do pravého Grove konektoru na Wio Terminalu, když se díváte na obrazovku. Jedná se o konektor nejdále od tlačítka napájení.

![Grove teplotní senzor připojený k pravému konektoru](../../../../../translated_images/wio-temperature-sensor.2934928f38c7f79a.cs.png)

## Naprogramování teplotního senzoru

Wio Terminal nyní může být naprogramován tak, aby používal připojený teplotní senzor.

### Úkol - naprogramujte teplotní senzor

Naprogramujte zařízení.

1. Vytvořte zcela nový projekt pro Wio Terminal pomocí PlatformIO. Nazvěte tento projekt `temperature-sensor`. Přidejte kód do funkce `setup` pro konfiguraci sériového portu.

    > ⚠️ Můžete se podívat na [instrukce pro vytvoření projektu v PlatformIO v projektu 1, lekci 1, pokud je to potřeba](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project).

1. Přidejte závislost na knihovnu Seeed Grove Humidity and Temperature sensor do souboru `platformio.ini` projektu:

    ```ini
    lib_deps =
        seeed-studio/Grove Temperature And Humidity Sensor @ 1.0.1
    ```

    > ⚠️ Můžete se podívat na [instrukce pro přidání knihoven do projektu v PlatformIO v projektu 1, lekci 4, pokud je to potřeba](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md#install-the-wifi-and-mqtt-arduino-libraries).

1. Přidejte následující direktivy `#include` na začátek souboru, pod existující `#include <Arduino.h>`:

    ```cpp
    #include <DHT.h>
    #include <SPI.h>
    ```

    Tyto direktivy importují soubory potřebné pro interakci se senzorem. Hlavičkový soubor `DHT.h` obsahuje kód pro samotný senzor a přidání hlavičkového souboru `SPI.h` zajistí, že kód potřebný pro komunikaci se senzorem bude zahrnut při kompilaci aplikace.

1. Před funkcí `setup` deklarujte senzor DHT:

    ```cpp
    DHT dht(D0, DHT11);
    ```

    Tímto deklarujete instanci třídy `DHT`, která spravuje **D**igitální **H**umidity a **T**emperature senzor. Tento senzor je připojen k portu `D0`, což je pravý Grove konektor na Wio Terminalu. Druhý parametr říká kódu, že použitý senzor je *DHT11* - knihovna, kterou používáte, podporuje i jiné varianty tohoto senzoru.

1. Ve funkci `setup` přidejte kód pro nastavení sériového připojení:

    ```cpp
    void setup()
    {
        Serial.begin(9600);
    
        while (!Serial)
            ; // Wait for Serial to be ready
    
        delay(1000);
    }
    ```

1. Na konci funkce `setup`, po posledním `delay`, přidejte volání pro spuštění senzoru DHT:

    ```cpp
    dht.begin();
    ```

1. Ve funkci `loop` přidejte kód pro volání senzoru a tisk teploty na sériový port:

    ```cpp
    void loop()
    {
        float temp_hum_val[2] = {0};
        dht.readTempAndHumidity(temp_hum_val);
        Serial.print("Temperature: ");
        Serial.print(temp_hum_val[1]);
        Serial.println ("°C");
    
        delay(10000);
    }
    ```

    Tento kód deklaruje prázdné pole o velikosti 2 floatů a předává ho volání `readTempAndHumidity` na instanci `DHT`. Toto volání naplní pole dvěma hodnotami - vlhkost se uloží do 0. položky pole (pamatujte, že v C++ jsou pole indexována od 0, takže 0. položka je 'první' položka pole) a teplota se uloží do 1. položky.

    Teplota se přečte z 1. položky pole a vytiskne na sériový port.

    > 🇺🇸 Teplota se čte v Celsiích. Pro Američany, pokud chcete převést tuto hodnotu na Fahrenheit, vydělte hodnotu v Celsiích 5, poté vynásobte 9 a přidejte 32. Například teplotní hodnota 20°C se převede na ((20/5)*9) + 32 = 68°F.

1. Zkompilujte a nahrajte kód do Wio Terminalu.

    > ⚠️ Můžete se podívat na [instrukce pro vytvoření projektu v PlatformIO v projektu 1, lekci 1, pokud je to potřeba](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app).

1. Po nahrání můžete sledovat teplotu pomocí sériového monitoru:

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Temperature: 25.00°C
    Temperature: 25.00°C
    Temperature: 25.00°C
    Temperature: 24.00°C
    ```

> 💁 Tento kód najdete ve složce [code-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/wio-terminal).

😀 Program pro váš teplotní senzor byl úspěšný!

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). I když se snažíme o přesnost, mějte prosím na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace doporučujeme profesionální lidský překlad. Neodpovídáme za žádná nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.