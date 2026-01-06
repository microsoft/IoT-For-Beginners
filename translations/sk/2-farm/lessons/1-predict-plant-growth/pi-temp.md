<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7678f7c67b97ee52d5727496dcd7d346",
  "translation_date": "2025-08-28T11:27:14+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/pi-temp.md",
  "language_code": "sk"
}
-->
# Meranie teploty - Raspberry Pi

V tejto časti lekcie pridáte k svojmu Raspberry Pi teplotný senzor.

## Hardvér

Senzor, ktorý budete používať, je [DHT11 senzor vlhkosti a teploty](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html), ktorý kombinuje 2 senzory v jednom balení. Tento senzor je pomerne populárny a existuje množstvo komerčne dostupných senzorov, ktoré kombinujú meranie teploty, vlhkosti a niekedy aj atmosférického tlaku. Komponent na meranie teploty je termistor s negatívnym teplotným koeficientom (NTC), čo znamená, že jeho odpor klesá so zvyšujúcou sa teplotou.

Ide o digitálny senzor, ktorý má zabudovaný ADC (analógovo-digitálny prevodník), aby vytvoril digitálny signál obsahujúci údaje o teplote a vlhkosti, ktoré môže mikrokontrolér čítať.

### Pripojenie teplotného senzora

Grove teplotný senzor je možné pripojiť k Raspberry Pi.

#### Úloha

Pripojte teplotný senzor.

![Grove teplotný senzor](../../../../../translated_images/grove-dht11.07f8eafceee170043efbb53e1d15722bd4e00fbaa9ff74290b57e9f66eb82c17.sk.png)

1. Zasuňte jeden koniec Grove kábla do konektora na senzore vlhkosti a teploty. Kábel sa dá zasunúť iba jedným spôsobom.

1. Pri vypnutom Raspberry Pi pripojte druhý koniec Grove kábla do digitálneho konektora označeného **D5** na Grove Base hat pripojenom k Pi. Tento konektor je druhý zľava v rade konektorov vedľa GPIO pinov.

![Grove teplotný senzor pripojený k zásuvke A0](../../../../../translated_images/pi-temperature-sensor.3ff82fff672c8e56.sk.png)

## Naprogramovanie teplotného senzora

Zariadenie teraz môžete naprogramovať na používanie pripojeného teplotného senzora.

### Úloha

Naprogramujte zariadenie.

1. Zapnite Raspberry Pi a počkajte, kým sa spustí.

1. Spustite VS Code, buď priamo na Pi, alebo sa pripojte cez rozšírenie Remote SSH.

    > ⚠️ Ak potrebujete, môžete si pozrieť [pokyny na nastavenie a spustenie VS Code v lekcii 1](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md).

1. V termináli vytvorte nový priečinok v domovskom adresári používateľa `pi` s názvom `temperature-sensor`. V tomto priečinku vytvorte súbor s názvom `app.py`:

    ```sh
    mkdir temperature-sensor
    cd temperature-sensor
    touch app.py
    ```

1. Otvorte tento priečinok vo VS Code.

1. Na používanie senzora vlhkosti a teploty je potrebné nainštalovať ďalší balík Pip. V termináli vo VS Code spustite nasledujúci príkaz na inštaláciu tohto balíka na Pi:

    ```sh
    pip3 install seeed-python-dht
    ```

1. Do súboru `app.py` pridajte nasledujúci kód na importovanie potrebných knižníc:

    ```python
    import time
    from seeed_dht import DHT
    ```

    Príkaz `from seeed_dht import DHT` importuje triedu `DHT` na interakciu s Grove teplotným senzorom z modulu `seeed_dht`.

1. Po vyššie uvedenom kóde pridajte nasledujúci kód na vytvorenie inštancie triedy, ktorá spravuje teplotný senzor:

    ```python
    sensor = DHT("11", 5)
    ```

    Tento kód deklaruje inštanciu triedy `DHT`, ktorá spravuje **D**igitálny senzor **H**umidity a **T**emperature. Prvý parameter informuje kód, že používaný senzor je *DHT11* - knižnica, ktorú používate, podporuje aj iné varianty tohto senzora. Druhý parameter informuje kód, že senzor je pripojený k digitálnemu portu `D5` na Grove Base hat.

    > ✅ Pamätajte, že všetky konektory majú jedinečné čísla pinov. Piny 0, 2, 4 a 6 sú analógové piny, piny 5, 16, 18, 22, 24 a 26 sú digitálne piny.

1. Po vyššie uvedenom kóde pridajte nekonečný cyklus na čítanie hodnôt teplotného senzora a ich výpis do konzoly:

    ```python
    while True:
        _, temp = sensor.read()
        print(f'Temperature {temp}°C')
    ```

    Volanie `sensor.read()` vráti dvojicu hodnôt vlhkosti a teploty. Potrebujete iba hodnotu teploty, takže vlhkosť sa ignoruje. Hodnota teploty sa potom vypíše do konzoly.

1. Na koniec cyklu pridajte krátku pauzu desať sekúnd, pretože úroveň teploty nie je potrebné kontrolovať nepretržite. Pauza znižuje spotrebu energie zariadenia.

    ```python
    time.sleep(10)
    ```

1. V termináli vo VS Code spustite nasledujúci príkaz na spustenie vášho Python programu:

    ```sh
    python3 app.py
    ```

    Mali by ste vidieť, ako sa hodnoty teploty vypisujú do konzoly. Použite niečo na zahriatie senzora, napríklad priloženie palca na senzor alebo ventilátor, aby ste videli, ako sa hodnoty menia:

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py 
    Temperature 26°C
    Temperature 26°C
    Temperature 28°C
    Temperature 30°C
    Temperature 32°C
    ```

> 💁 Tento kód nájdete v priečinku [code-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/pi).

😀 Váš program na teplotný senzor bol úspešný!

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby AI prekladu [Co-op Translator](https://github.com/Azure/co-op-translator). Hoci sa snažíme o presnosť, prosím, berte na vedomie, že automatizované preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho pôvodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nie sme zodpovední za akékoľvek nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.