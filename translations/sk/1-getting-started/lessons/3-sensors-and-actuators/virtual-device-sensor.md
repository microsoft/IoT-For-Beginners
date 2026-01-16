<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "11f10c6760fb8202cf368422702fdf70",
  "translation_date": "2025-08-28T10:38:03+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/virtual-device-sensor.md",
  "language_code": "sk"
}
-->
# Vytvorte nočné svetlo - Virtuálny IoT hardvér

V tejto časti lekcie pridáte svetelný senzor do vášho virtuálneho IoT zariadenia.

## Virtuálny hardvér

Nočné svetlo potrebuje jeden senzor, ktorý sa vytvorí v aplikácii CounterFit.

Tento senzor je **svetelný senzor**. V prípade fyzického IoT zariadenia by to bol [fotodióda](https://wikipedia.org/wiki/Photodiode), ktorá premieňa svetlo na elektrický signál. Svetelné senzory sú analógové senzory, ktoré posielajú celočíselnú hodnotu indikujúcu relatívne množstvo svetla, ktoré sa neprekladá do žiadnej štandardnej jednotky merania, ako je napríklad [lux](https://wikipedia.org/wiki/Lux).

### Pridajte senzory do CounterFit

Na použitie virtuálneho svetelného senzora ho musíte pridať do aplikácie CounterFit.

#### Úloha - pridajte senzory do CounterFit

Pridajte svetelný senzor do aplikácie CounterFit.

1. Uistite sa, že webová aplikácia CounterFit beží z predchádzajúcej časti tejto úlohy. Ak nie, spustite ju.

1. Vytvorte svetelný senzor:

    1. V poli *Create sensor* v paneli *Sensors* rozbaľte pole *Sensor type* a vyberte *Light*.

    1. Nechajte *Units* nastavené na *NoUnits*.

    1. Uistite sa, že *Pin* je nastavený na *0*.

    1. Kliknite na tlačidlo **Add**, aby ste vytvorili svetelný senzor na pine 0.

    ![Nastavenia svetelného senzora](../../../../../translated_images/sk/counterfit-create-light-sensor.9f36a5e0d4458d8d554d54b34d2c806d56093d6e49fddcda2d20f6fef7f5cce1.png)

    Svetelný senzor bude vytvorený a zobrazí sa v zozname senzorov.

    ![Vytvorený svetelný senzor](../../../../../translated_images/sk/counterfit-light-sensor.5d0f5584df56b90f6b2561910d9cb20dfbd73eeff2177c238d38f4de54aefae1.png)

## Naprogramujte svetelný senzor

Zariadenie teraz môže byť naprogramované na použitie zabudovaného svetelného senzora.

### Úloha - naprogramujte svetelný senzor

Naprogramujte zariadenie.

1. Otvorte projekt nočného svetla vo VS Code, ktorý ste vytvorili v predchádzajúcej časti tejto úlohy. Ak je to potrebné, ukončite a znovu vytvorte terminál, aby ste sa uistili, že beží vo virtuálnom prostredí.

1. Otvorte súbor `app.py`.

1. Pridajte nasledujúci kód na začiatok súboru `app.py` spolu s ostatnými príkazmi `import`, aby ste importovali potrebné knižnice:

    ```python
    import time
    from counterfit_shims_grove.grove_light_sensor_v1_2 import GroveLightSensor
    ```

    Príkaz `import time` importuje modul Python `time`, ktorý bude použitý neskôr v tejto úlohe.

    Príkaz `from counterfit_shims_grove.grove_light_sensor_v1_2 import GroveLightSensor` importuje `GroveLightSensor` z Python knižníc CounterFit Grove shim. Táto knižnica obsahuje kód na interakciu so svetelným senzorom vytvoreným v aplikácii CounterFit.

1. Pridajte nasledujúci kód na koniec súboru, aby ste vytvorili inštancie tried, ktoré spravujú svetelný senzor:

    ```python
    light_sensor = GroveLightSensor(0)
    ```

    Riadok `light_sensor = GroveLightSensor(0)` vytvára inštanciu triedy `GroveLightSensor`, ktorá sa pripája na pin **0** - CounterFit Grove pin, ku ktorému je pripojený svetelný senzor.

1. Pridajte nekonečnú slučku po vyššie uvedenom kóde, aby ste získavali hodnotu svetelného senzora a vypisovali ju do konzoly:

    ```python
    while True:
        light = light_sensor.light
        print('Light level:', light)
    ```

    Tento kód číta aktuálnu úroveň svetla pomocou vlastnosti `light` triedy `GroveLightSensor`. Táto vlastnosť číta analógovú hodnotu z pinu. Táto hodnota sa potom vypíše do konzoly.

1. Na koniec slučky `while` pridajte krátku pauzu jednej sekundy, pretože úrovne svetla nie je potrebné kontrolovať nepretržite. Pauza znižuje spotrebu energie zariadenia.

    ```python
    time.sleep(1)
    ```

1. Z terminálu VS Code spustite nasledujúci príkaz na spustenie vašej Python aplikácie:

    ```sh
    python3 app.py
    ```

    Hodnoty svetla sa budú vypisovať do konzoly. Na začiatku bude táto hodnota 0.

1. V aplikácii CounterFit zmeňte hodnotu svetelného senzora, ktorú bude aplikácia čítať. Môžete to urobiť jedným z dvoch spôsobov:

    * Zadajte číslo do poľa *Value* pre svetelný senzor a potom kliknite na tlačidlo **Set**. Číslo, ktoré zadáte, bude hodnota vrátená senzorom.

    * Zaškrtnite políčko *Random* a zadajte hodnoty *Min* a *Max*, potom kliknite na tlačidlo **Set**. Pri každom čítaní hodnoty senzorom sa vráti náhodné číslo medzi *Min* a *Max*.

    Hodnoty, ktoré nastavíte, sa budú vypisovať do konzoly. Zmeňte nastavenia *Value* alebo *Random*, aby sa hodnota zmenila.

    ```output
    (.venv) ➜  GroveTest python3 app.py 
    Light level: 143
    Light level: 244
    Light level: 246
    Light level: 253
    ```

> 💁 Tento kód nájdete v priečinku [code-sensor/virtual-device](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/virtual-device).

😀 Vaša aplikácia nočného svetla bola úspešná!

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby AI prekladu [Co-op Translator](https://github.com/Azure/co-op-translator). Hoci sa snažíme o presnosť, prosím, berte na vedomie, že automatizované preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho rodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nenesieme zodpovednosť za akékoľvek nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.