# Ovládanie relé - Virtuálny IoT hardvér

V tejto časti lekcie pridáte k svojmu virtuálnemu IoT zariadeniu relé, okrem senzora vlhkosti pôdy, a budete ho ovládať na základe úrovne vlhkosti pôdy.

## Virtuálny hardvér

Virtuálne IoT zariadenie bude používať simulované Grove relé. To umožňuje, aby tento lab zostal rovnaký ako pri použití Raspberry Pi s fyzickým Grove relé.

Pri fyzickom IoT zariadení by relé bolo normálne otvorené relé (čo znamená, že výstupný obvod je otvorený alebo odpojený, keď relé nedostáva žiadny signál). Takéto relé dokáže zvládnuť výstupné obvody až do 250V a 10A.

### Pridanie relé do CounterFit

Na použitie virtuálneho relé ho musíte pridať do aplikácie CounterFit.

#### Úloha

Pridajte relé do aplikácie CounterFit.

1. Otvorte projekt `soil-moisture-sensor` z poslednej lekcie vo VS Code, ak už nie je otvorený. Budete pridávať do tohto projektu.

1. Uistite sa, že webová aplikácia CounterFit beží.

1. Vytvorte relé:

    1. V poli *Create actuator* v paneli *Actuators* rozbaľte pole *Actuator type* a vyberte *Relay*.

    1. Nastavte *Pin* na *5*.

    1. Kliknite na tlačidlo **Add**, aby ste vytvorili relé na pine 5.

    ![Nastavenia relé](../../../../../translated_images/sk/counterfit-create-relay.fa7c40fd0f2f6afc.webp)

    Relé bude vytvorené a zobrazí sa v zozname aktuátorov.

    ![Vytvorené relé](../../../../../translated_images/sk/counterfit-relay.bbf74c1dbdc8b9ac.webp)

## Programovanie relé

Aplikácia senzora vlhkosti pôdy môže byť teraz naprogramovaná na použitie virtuálneho relé.

### Úloha

Napíšte program pre virtuálne zariadenie.

1. Otvorte projekt `soil-moisture-sensor` z poslednej lekcie vo VS Code, ak už nie je otvorený. Budete pridávať do tohto projektu.

1. Pridajte nasledujúci kód do súboru `app.py` pod existujúce importy:

    ```python
    from counterfit_shims_grove.grove_relay import GroveRelay
    ```

    Tento príkaz importuje `GroveRelay` z knižníc Grove Python shim na interakciu s virtuálnym Grove relé.

1. Pridajte nasledujúci kód pod deklaráciu triedy `ADC`, aby ste vytvorili inštanciu `GroveRelay`:

    ```python
    relay = GroveRelay(5)
    ```

    Týmto sa vytvorí relé na pine **5**, na ktorý ste relé pripojili.

1. Na otestovanie funkčnosti relé pridajte nasledujúci kód do slučky `while True:`:

    ```python
    relay.on()
    time.sleep(.5)
    relay.off()
    ```

    Kód zapne relé, počká 0,5 sekundy a potom relé vypne.

1. Spustite Python aplikáciu. Relé sa bude zapínať a vypínať každých 10 sekúnd, s polsekundovou prestávkou medzi zapnutím a vypnutím. Uvidíte, ako sa virtuálne relé v aplikácii CounterFit zatvára a otvára, keď sa relé zapína a vypína.

    ![Virtuálne relé sa zapína a vypína](../../../../../images/virtual-relay-turn-on-off.gif)

## Ovládanie relé na základe vlhkosti pôdy

Keď relé funguje, môže byť ovládané na základe údajov o vlhkosti pôdy.

### Úloha

Ovládajte relé.

1. Vymažte 3 riadky kódu, ktoré ste pridali na testovanie relé. Nahraďte ich nasledujúcim kódom:

    ```python
    if soil_moisture > 450:
        print("Soil Moisture is too low, turning relay on.")
        relay.on()
    else:
        print("Soil Moisture is ok, turning relay off.")
        relay.off()
    ```

    Tento kód kontroluje úroveň vlhkosti pôdy zo senzora vlhkosti pôdy. Ak je nad 450, zapne relé, a ak klesne pod 450, relé vypne.

    > 💁 Pamätajte, že kapacitný senzor vlhkosti pôdy číta hodnoty tak, že čím nižšia je úroveň vlhkosti pôdy, tým viac vlhkosti je v pôde, a naopak.

1. Spustite Python aplikáciu. Uvidíte, ako sa relé zapína alebo vypína v závislosti od úrovne vlhkosti pôdy. Zmeňte *Value* alebo *Random* nastavenia senzora vlhkosti pôdy, aby ste videli zmenu hodnoty.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 Tento kód nájdete v priečinku [code-relay/virtual-device](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/virtual-device).

😀 Vaša virtuálna aplikácia na ovládanie relé na základe senzora vlhkosti pôdy bola úspešná!

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby AI prekladu [Co-op Translator](https://github.com/Azure/co-op-translator). Hoci sa snažíme o presnosť, prosím, berte na vedomie, že automatizované preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho rodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nie sme zodpovední za žiadne nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.