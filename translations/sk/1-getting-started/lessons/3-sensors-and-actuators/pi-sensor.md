# Vytvorte nočné svetlo - Raspberry Pi

V tejto časti lekcie pridáte k Raspberry Pi svetelný senzor.

## Hardvér

Senzor pre túto lekciu je **svetelný senzor**, ktorý používa [fotodiódu](https://wikipedia.org/wiki/Photodiode) na konverziu svetla na elektrický signál. Ide o analógový senzor, ktorý posiela celočíselnú hodnotu od 0 do 1 000, čo indikuje relatívne množstvo svetla, ktoré nie je mapované na žiadnu štandardnú jednotku merania, ako je napríklad [lux](https://wikipedia.org/wiki/Lux).

Svetelný senzor je externý Grove senzor a musí byť pripojený k Grove Base hat na Raspberry Pi.

### Pripojenie svetelného senzora

Grove svetelný senzor, ktorý sa používa na detekciu úrovní svetla, musí byť pripojený k Raspberry Pi.

#### Úloha - pripojenie svetelného senzora

Pripojte svetelný senzor.

![Grove svetelný senzor](../../../../../translated_images/sk/grove-light-sensor.b8127b7c434e632d.webp)

1. Zasuňte jeden koniec Grove kábla do zásuvky na module svetelného senzora. Kábel sa dá zasunúť iba jedným spôsobom.

1. Pri vypnutom Raspberry Pi pripojte druhý koniec Grove kábla do analógovej zásuvky označenej **A0** na Grove Base hat pripojenom k Pi. Táto zásuvka je druhá sprava v rade zásuviek vedľa GPIO pinov.

![Grove svetelný senzor pripojený k zásuvke A0](../../../../../translated_images/sk/pi-light-sensor.66cc1e31fa48cd7d.webp)

## Naprogramovanie svetelného senzora

Zariadenie teraz môže byť naprogramované pomocou Grove svetelného senzora.

### Úloha - naprogramovanie svetelného senzora

Naprogramujte zariadenie.

1. Zapnite Pi a počkajte, kým sa spustí.

1. Otvorte projekt nočného svetla vo VS Code, ktorý ste vytvorili v predchádzajúcej časti tejto úlohy, buď priamo na Pi, alebo pomocou rozšírenia Remote SSH.

1. Otvorte súbor `app.py` a odstráňte z neho všetok kód.

1. Pridajte nasledujúci kód do súboru `app.py` na importovanie potrebných knižníc:

    ```python
    import time
    from grove.grove_light_sensor_v1_2 import GroveLightSensor
    ```

    Príkaz `import time` importuje modul `time`, ktorý bude použitý neskôr v tejto úlohe.

    Príkaz `from grove.grove_light_sensor_v1_2 import GroveLightSensor` importuje `GroveLightSensor` z Grove Python knižníc. Táto knižnica obsahuje kód na interakciu s Grove svetelným senzorom a bola nainštalovaná globálne počas nastavenia Pi.

1. Pridajte nasledujúci kód po vyššie uvedenom kóde na vytvorenie inštancie triedy, ktorá spravuje svetelný senzor:

    ```python
    light_sensor = GroveLightSensor(0)
    ```

    Riadok `light_sensor = GroveLightSensor(0)` vytvára inštanciu triedy `GroveLightSensor`, ktorá sa pripája k pinu **A0** - analógovému Grove pinu, ku ktorému je pripojený svetelný senzor.

1. Pridajte nekonečnú slučku po vyššie uvedenom kóde na čítanie hodnoty svetelného senzora a jej výpis do konzoly:

    ```python
    while True:
        light = light_sensor.light
        print('Light level:', light)
    ```

    Táto slučka bude čítať aktuálnu úroveň svetla na škále od 0 do 1 023 pomocou vlastnosti `light` triedy `GroveLightSensor`. Táto vlastnosť číta analógovú hodnotu z pinu. Táto hodnota sa potom vypíše do konzoly.

1. Pridajte krátku pauzu jednej sekundy na konci `loop`, pretože úrovne svetla nie je potrebné kontrolovať nepretržite. Pauza znižuje spotrebu energie zariadenia.

    ```python
    time.sleep(1)
    ```

1. Z terminálu VS Code spustite nasledujúci príkaz na spustenie vašej Python aplikácie:

    ```sh
    python3 app.py
    ```

    Hodnoty svetla sa budú vypisovať do konzoly. Zakryte a odkryte svetelný senzor a hodnoty sa zmenia:

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py 
    Light level: 634
    Light level: 634
    Light level: 634
    Light level: 230
    Light level: 104
    Light level: 290
    ```

> 💁 Tento kód nájdete v priečinku [code-sensor/pi](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/pi).

😀 Pridanie senzora do vášho programu nočného svetla bolo úspešné!

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby na automatický preklad [Co-op Translator](https://github.com/Azure/co-op-translator). Aj keď sa snažíme o presnosť, upozorňujeme, že automatické preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho pôvodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre dôležité informácie sa odporúča profesionálny ľudský preklad. Nezodpovedáme za akékoľvek nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.