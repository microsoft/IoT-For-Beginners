<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2bf65f162bcebd35fbcba5fd245afac4",
  "translation_date": "2025-08-28T11:02:22+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/virtual-device-soil-moisture.md",
  "language_code": "sk"
}
-->
# Meranie vlhkosti pôdy - Virtuálny IoT hardvér

V tejto časti lekcie pridáte kapacitný senzor vlhkosti pôdy k vášmu virtuálnemu IoT zariadeniu a budete z neho čítať hodnoty.

## Virtuálny hardvér

Virtuálne IoT zariadenie bude používať simulovaný kapacitný senzor vlhkosti pôdy Grove. Týmto spôsobom zostáva tento laboratórny projekt rovnaký ako pri použití Raspberry Pi s fyzickým kapacitným senzorom vlhkosti pôdy Grove.

V prípade fyzického IoT zariadenia by senzor vlhkosti pôdy bol kapacitný senzor, ktorý meria vlhkosť pôdy detekovaním kapacity pôdy, vlastnosti, ktorá sa mení v závislosti od vlhkosti pôdy. Keď sa vlhkosť pôdy zvyšuje, napätie klesá.

Toto je analógový senzor, ktorý používa simulovaný 10-bitový ADC na hlásenie hodnoty od 1 do 1 023.

### Pridanie senzora vlhkosti pôdy do CounterFit

Na použitie virtuálneho senzora vlhkosti pôdy ho musíte pridať do aplikácie CounterFit.

#### Úloha - Pridanie senzora vlhkosti pôdy do CounterFit

Pridajte senzor vlhkosti pôdy do aplikácie CounterFit.

1. Vytvorte novú Python aplikáciu na vašom počítači v priečinku `soil-moisture-sensor` s jedným súborom nazvaným `app.py` a Python virtuálnym prostredím, a pridajte CounterFit pip balíčky.

    > ⚠️ Môžete sa odvolať na [pokyny na vytvorenie a nastavenie CounterFit Python projektu v lekcii 1, ak je to potrebné](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Uistite sa, že webová aplikácia CounterFit beží.

1. Vytvorte senzor vlhkosti pôdy:

    1. V poli *Create sensor* v paneli *Sensors* rozbaľte pole *Sensor type* a vyberte *Soil Moisture*.

    1. Nechajte *Units* nastavené na *NoUnits*.

    1. Uistite sa, že *Pin* je nastavený na *0*.

    1. Kliknite na tlačidlo **Add**, aby ste vytvorili senzor *Soil Moisture* na pine 0.

    ![Nastavenia senzora vlhkosti pôdy](../../../../../translated_images/sk/counterfit-create-soil-moisture-sensor.35266135a5e0ae68b29a684d7db0d2933a8098b2307d197f7c71577b724603aa.png)

    Senzor vlhkosti pôdy bude vytvorený a zobrazí sa v zozname senzorov.

    ![Vytvorený senzor vlhkosti pôdy](../../../../../translated_images/sk/counterfit-soil-moisture-sensor.81742b2de0e9de60a3b3b9a2ff8ecc686d428eb6d71820f27a693be26e5aceee.png)

## Naprogramovanie aplikácie senzora vlhkosti pôdy

Aplikácia senzora vlhkosti pôdy môže byť teraz naprogramovaná pomocou senzorov CounterFit.

### Úloha - naprogramovanie aplikácie senzora vlhkosti pôdy

Naprogramujte aplikáciu senzora vlhkosti pôdy.

1. Uistite sa, že aplikácia `soil-moisture-sensor` je otvorená vo VS Code.

1. Otvorte súbor `app.py`.

1. Pridajte nasledujúci kód na začiatok súboru `app.py`, aby ste pripojili aplikáciu k CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Pridajte nasledujúci kód do súboru `app.py`, aby ste importovali potrebné knižnice:

    ```python
    import time
    from counterfit_shims_grove.adc import ADC
    ```

    Príkaz `import time` importuje modul `time`, ktorý bude použitý neskôr v tejto úlohe.

    Príkaz `from counterfit_shims_grove.adc import ADC` importuje triedu `ADC`, ktorá umožňuje interakciu so simulovaným analógovo-digitálnym prevodníkom, ktorý sa môže pripojiť k senzoru CounterFit.

1. Pridajte nasledujúci kód pod tento, aby ste vytvorili inštanciu triedy `ADC`:

    ```python
    adc = ADC()
    ```

1. Pridajte nekonečnú slučku, ktorá číta hodnoty z ADC na pine 0 a zapisuje výsledok do konzoly. Táto slučka potom môže spať 10 sekúnd medzi čítaniami.

    ```python
    while True:
        soil_moisture = adc.read(0)
        print("Soil moisture:", soil_moisture)
    
        time.sleep(10)
    ```

1. V aplikácii CounterFit zmeňte hodnotu senzora vlhkosti pôdy, ktorú bude aplikácia čítať. Môžete to urobiť jedným z dvoch spôsobov:

    * Zadajte číslo do poľa *Value* pre senzor vlhkosti pôdy a potom kliknite na tlačidlo **Set**. Číslo, ktoré zadáte, bude hodnota vrátená senzorom.

    * Zaškrtnite políčko *Random* a zadajte hodnoty *Min* a *Max*, potom kliknite na tlačidlo **Set**. Pri každom čítaní hodnoty senzor vráti náhodné číslo medzi *Min* a *Max*.

1. Spustite Python aplikáciu. Uvidíte merania vlhkosti pôdy zapísané do konzoly. Zmeňte nastavenia *Value* alebo *Random*, aby ste videli zmenu hodnoty.

    ```output
    (.venv) ➜ soil-moisture-sensor $ python app.py 
    Soil moisture: 615
    Soil moisture: 612
    Soil moisture: 498
    Soil moisture: 493
    Soil moisture: 490
    Soil Moisture: 388
    ```

> 💁 Tento kód nájdete v priečinku [code/virtual-device](../../../../../2-farm/lessons/2-detect-soil-moisture/code/virtual-device).

😀 Vaša aplikácia senzora vlhkosti pôdy bola úspešná!

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby AI prekladu [Co-op Translator](https://github.com/Azure/co-op-translator). Hoci sa snažíme o presnosť, prosím, berte na vedomie, že automatizované preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho rodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nie sme zodpovední za žiadne nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.