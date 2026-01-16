<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "288aebb0c59f7be1d2719b8f9660a313",
  "translation_date": "2025-08-28T08:26:56+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/wio-terminal-proximity.md",
  "language_code": "sk"
}
-->
# Detekcia blízkosti - Wio Terminal

V tejto časti lekcie pridáte k Wio Terminalu senzor blízkosti a budete z neho čítať vzdialenosť.

## Hardvér

Wio Terminal potrebuje senzor blízkosti.

Senzor, ktorý použijete, je [Grove Time of Flight distance sensor](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html). Tento senzor používa laserový modul na meranie vzdialenosti. Má rozsah od 10mm do 2000mm (1cm - 2m) a hodnoty v tomto rozsahu hlási pomerne presne, pričom vzdialenosti nad 1000mm hlási ako 8109mm.

Laserový diaľkomer sa nachádza na zadnej strane senzora, na opačnej strane ako Grove konektor.

Toto je I²C senzor.

### Pripojenie senzora Time of Flight

Grove Time of Flight senzor je možné pripojiť k Wio Terminalu.

#### Úloha - pripojenie senzora Time of Flight

Pripojte senzor Time of Flight.

![Grove Time of Flight senzor](../../../../../translated_images/sk/grove-time-of-flight-sensor.d82ff2165bfded9f485de54d8d07195a6270a602696825fca19f629ddfe94e86.png)

1. Zasuňte jeden koniec Grove kábla do konektora na senzore Time of Flight. Kábel sa dá zasunúť iba jedným spôsobom.

1. Keď je Wio Terminal odpojený od vášho počítača alebo iného zdroja napájania, pripojte druhý koniec Grove kábla do ľavého Grove konektora na Wio Terminale, keď sa pozeráte na obrazovku. Tento konektor je najbližšie k tlačidlu napájania. Ide o kombinovaný digitálny a I²C konektor.

![Grove Time of Flight senzor pripojený k ľavému konektoru](../../../../../translated_images/sk/wio-time-of-flight-sensor.c4c182131d2ea73d.webp)

1. Teraz môžete pripojiť Wio Terminal k vášmu počítaču.

## Naprogramovanie senzora Time of Flight

Wio Terminal je teraz pripravený na programovanie, aby mohol používať pripojený senzor Time of Flight.

### Úloha - naprogramovanie senzora Time of Flight

1. Vytvorte úplne nový projekt pre Wio Terminal pomocou PlatformIO. Nazvite tento projekt `distance-sensor`. Pridajte kód do funkcie `setup` na konfiguráciu sériového portu.

1. Pridajte závislosť knižnice pre Seeed Grove Time of Flight distance sensor do súboru `platformio.ini` projektu:

    ```ini
    lib_deps =
        seeed-studio/Grove Ranging sensor - VL53L0X @ ^1.1.1
    ```

1. V `main.cpp` pridajte nasledujúci kód pod existujúce direktívy `include`, aby ste deklarovali inštanciu triedy `Seeed_vl53l0x` na interakciu so senzorom Time of Flight:

    ```cpp
    #include "Seeed_vl53l0x.h"
    
    Seeed_vl53l0x VL53L0X;
    ```

1. Pridajte nasledujúci kód na koniec funkcie `setup`, aby ste inicializovali senzor:

    ```cpp
    VL53L0X.VL53L0X_common_init();
    VL53L0X.VL53L0X_high_accuracy_ranging_init();
    ```

1. Vo funkcii `loop` prečítajte hodnotu zo senzora:

    ```cpp
    VL53L0X_RangingMeasurementData_t RangingMeasurementData;
    memset(&RangingMeasurementData, 0, sizeof(VL53L0X_RangingMeasurementData_t));

    VL53L0X.PerformSingleRangingMeasurement(&RangingMeasurementData);
    ```

    Tento kód inicializuje dátovú štruktúru na čítanie údajov, potom ju odovzdá metóde `PerformSingleRangingMeasurement`, kde bude naplnená nameranou vzdialenosťou.

1. Pod týmto kódom vypíšte nameranú vzdialenosť a potom pridajte oneskorenie 1 sekundu:

    ```cpp
    Serial.print("Distance = ");
    Serial.print(RangingMeasurementData.RangeMilliMeter);
    Serial.println(" mm");

    delay(1000);
    ```

1. Zostavte, nahrajte a spustite tento kód. Budete môcť vidieť namerané vzdialenosti v sériovom monitore. Umiestnite objekty blízko senzora a uvidíte nameranú vzdialenosť:

    ```output
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    Diaľkomer sa nachádza na zadnej strane senzora, takže pri meraní vzdialenosti používajte správnu stranu.

    ![Diaľkomer na zadnej strane senzora Time of Flight smerujúci na banán](../../../../../translated_images/sk/time-of-flight-banana.079921ad8b1496e4.webp)

> 💁 Tento kód nájdete v priečinku [code-proximity/wio-terminal](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/wio-terminal).

😀 Program pre váš senzor blízkosti bol úspešný!

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby na automatický preklad [Co-op Translator](https://github.com/Azure/co-op-translator). Hoci sa snažíme o presnosť, upozorňujeme, že automatické preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho pôvodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre dôležité informácie odporúčame profesionálny ľudský preklad. Nezodpovedáme za žiadne nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.