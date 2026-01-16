<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "70e5a428b607cd5a9a4f422c2a4df03d",
  "translation_date": "2025-08-28T11:33:59+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/virtual-device-temp.md",
  "language_code": "sk"
}
-->
# Meranie teploty - Virtuálny IoT hardvér

V tejto časti lekcie pridáte teplotný senzor k vášmu virtuálnemu IoT zariadeniu.

## Virtuálny hardvér

Virtuálne IoT zariadenie bude používať simulovaný Grove Digital Humidity and Temperature senzor. To umožňuje, aby tento lab zostal rovnaký ako pri použití Raspberry Pi s fyzickým Grove DHT11 senzorom.

Senzor kombinuje **teplotný senzor** s **senzorom vlhkosti**, ale v tomto labu sa zameriate iba na komponent teplotného senzora. Vo fyzickom IoT zariadení by teplotný senzor bol [termistor](https://wikipedia.org/wiki/Thermistor), ktorý meria teplotu na základe zmeny odporu pri zmene teploty. Teplotné senzory sú zvyčajne digitálne senzory, ktoré interne konvertujú nameraný odpor na teplotu v stupňoch Celzia (alebo Kelvina, alebo Fahrenheita).

### Pridanie senzorov do CounterFit

Na použitie virtuálneho senzora vlhkosti a teploty je potrebné pridať tieto dva senzory do aplikácie CounterFit.

#### Úloha - pridanie senzorov do CounterFit

Pridajte senzory vlhkosti a teploty do aplikácie CounterFit.

1. Vytvorte novú Python aplikáciu na vašom počítači v priečinku `temperature-sensor` s jediným súborom nazvaným `app.py` a Python virtuálnym prostredím, a pridajte CounterFit pip balíčky.

    > ⚠️ Môžete sa odvolať na [pokyny na vytvorenie a nastavenie CounterFit Python projektu v lekcii 1, ak je to potrebné](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Nainštalujte ďalší Pip balíček na inštaláciu CounterFit shim pre DHT11 senzor. Uistite sa, že inštalujete z terminálu s aktivovaným virtuálnym prostredím.

    ```sh
    pip install counterfit-shims-seeed-python-dht
    ```

1. Uistite sa, že webová aplikácia CounterFit je spustená.

1. Vytvorte senzor vlhkosti:

    1. V poli *Create sensor* v paneli *Sensors* rozbaľte pole *Sensor type* a vyberte *Humidity*.

    1. Nechajte *Units* nastavené na *Percentage*.

    1. Uistite sa, že *Pin* je nastavený na *5*.

    1. Kliknite na tlačidlo **Add**, aby ste vytvorili senzor vlhkosti na pine 5.

    ![Nastavenia senzora vlhkosti](../../../../../translated_images/sk/counterfit-create-humidity-sensor.2750e27b6f30e09cf4e22101defd5252710717620816ab41ba688f91f757c49a.png)

    Senzor vlhkosti bude vytvorený a zobrazí sa v zozname senzorov.

    ![Vytvorený senzor vlhkosti](../../../../../translated_images/sk/counterfit-humidity-sensor.7b12f7f339e430cb26c8211d2dba4ef75261b353a01da0932698b5bebd693f27.png)

1. Vytvorte teplotný senzor:

    1. V poli *Create sensor* v paneli *Sensors* rozbaľte pole *Sensor type* a vyberte *Temperature*.

    1. Nechajte *Units* nastavené na *Celsius*.

    1. Uistite sa, že *Pin* je nastavený na *6*.

    1. Kliknite na tlačidlo **Add**, aby ste vytvorili teplotný senzor na pine 6.

    ![Nastavenia teplotného senzora](../../../../../translated_images/sk/counterfit-create-temperature-sensor.199350ed34f7343d79dccbe95eaf6c11d2121f03d1c35ab9613b330c23f39b29.png)

    Teplotný senzor bude vytvorený a zobrazí sa v zozname senzorov.

    ![Vytvorený teplotný senzor](../../../../../translated_images/sk/counterfit-temperature-sensor.f0560236c96a9016bafce7f6f792476fe3367bc6941a1f7d5811d144d4bcbfff.png)

## Naprogramovanie aplikácie teplotného senzora

Aplikácia teplotného senzora môže byť teraz naprogramovaná pomocou senzorov CounterFit.

### Úloha - naprogramovanie aplikácie teplotného senzora

Naprogramujte aplikáciu teplotného senzora.

1. Uistite sa, že aplikácia `temperature-sensor` je otvorená vo VS Code.

1. Otvorte súbor `app.py`.

1. Pridajte nasledujúci kód na začiatok súboru `app.py`, aby ste pripojili aplikáciu k CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Pridajte nasledujúci kód do súboru `app.py`, aby ste importovali potrebné knižnice:

    ```python
    import time
    from counterfit_shims_seeed_python_dht import DHT
    ```

    Príkaz `from seeed_dht import DHT` importuje triedu `DHT` na interakciu s virtuálnym Grove teplotným senzorom pomocou shim z modulu `counterfit_shims_seeed_python_dht`.

1. Pridajte nasledujúci kód po vyššie uvedenom kóde na vytvorenie inštancie triedy, ktorá spravuje virtuálny senzor vlhkosti a teploty:

    ```python
    sensor = DHT("11", 5)
    ```

    Toto deklaruje inštanciu triedy `DHT`, ktorá spravuje virtuálny **D**igital **H**umidity a **T**emperature senzor. Prvý parameter informuje kód, že používaný senzor je virtuálny *DHT11* senzor. Druhý parameter informuje kód, že senzor je pripojený k portu `5`.

    > 💁 CounterFit simuluje tento kombinovaný senzor vlhkosti a teploty pripojením k 2 senzorom, senzor vlhkosti na pine uvedenom pri vytvorení triedy `DHT` a teplotný senzor, ktorý beží na nasledujúcom pine. Ak je senzor vlhkosti na pine 5, shim očakáva teplotný senzor na pine 6.

1. Pridajte nekonečnú slučku po vyššie uvedenom kóde na získanie hodnoty teplotného senzora a jej výpis do konzoly:

    ```python
    while True:
        _, temp = sensor.read()
        print(f'Temperature {temp}°C')
    ```

    Volanie `sensor.read()` vráti dvojicu hodnôt vlhkosti a teploty. Potrebujete iba hodnotu teploty, takže vlhkosť je ignorovaná. Hodnota teploty je potom vypísaná do konzoly.

1. Pridajte krátku pauzu desať sekúnd na koniec `loop`, pretože úrovne teploty nie je potrebné kontrolovať nepretržite. Pauza znižuje spotrebu energie zariadenia.

    ```python
    time.sleep(10)
    ```

1. Z terminálu VS Code s aktivovaným virtuálnym prostredím spustite nasledujúci príkaz na spustenie vašej Python aplikácie:

    ```sh
    python app.py
    ```

1. V aplikácii CounterFit zmeňte hodnotu teplotného senzora, ktorú aplikácia prečíta. Môžete to urobiť jedným z dvoch spôsobov:

    * Zadajte číslo do poľa *Value* pre teplotný senzor a potom kliknite na tlačidlo **Set**. Číslo, ktoré zadáte, bude hodnota vrátená senzorom.

    * Zaškrtnite políčko *Random* a zadajte hodnoty *Min* a *Max*, potom kliknite na tlačidlo **Set**. Pri každom čítaní hodnoty senzorom sa vráti náhodné číslo medzi *Min* a *Max*.

    Mali by ste vidieť hodnoty, ktoré ste nastavili, zobrazujúce sa v konzole. Zmeňte *Value* alebo nastavenia *Random*, aby ste videli zmenu hodnoty.

    ```output
    (.venv) ➜  temperature-sensor python app.py
    Temperature 28.25°C
    Temperature 30.71°C
    Temperature 25.17°C
    ```

> 💁 Tento kód nájdete v priečinku [code-temperature/virtual-device](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/virtual-device).

😀 Vaša aplikácia teplotného senzora bola úspešná!

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby na automatický preklad [Co-op Translator](https://github.com/Azure/co-op-translator). Aj keď sa snažíme o presnosť, upozorňujeme, že automatické preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho pôvodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre dôležité informácie sa odporúča profesionálny ľudský preklad. Nezodpovedáme za akékoľvek nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.