<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4efc74299e19f5d08f2f3f34451a11ba",
  "translation_date": "2025-08-28T11:33:12+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/single-board-computer-temp-publish.md",
  "language_code": "sk"
}
-->
# Publikovanie teploty - Virtuálny IoT hardvér a Raspberry Pi

V tejto časti lekcie budete publikovať hodnoty teploty zistené Raspberry Pi alebo Virtuálnym IoT zariadením cez MQTT, aby mohli byť neskôr použité na výpočet GDD.

## Publikovanie teploty

Keď je teplota odčítaná, môže byť publikovaná cez MQTT do nejakého 'serverového' kódu, ktorý tieto hodnoty prečíta a uloží ich, aby mohli byť použité na výpočet GDD.

### Úloha - publikovanie teploty

Naprogramujte zariadenie na publikovanie údajov o teplote.

1. Otvorte projekt aplikácie `temperature-sensor`, ak už nie je otvorený.

1. Opakujte kroky, ktoré ste vykonali v lekcii 4 na pripojenie k MQTT a odosielanie telemetrie. Budete používať rovnaký verejný Mosquitto broker.

    Kroky sú nasledovné:

    - Pridajte balík pip pre MQTT
    - Pridajte kód na pripojenie k MQTT brokeru
    - Pridajte kód na publikovanie telemetrie

    > ⚠️ Pozrite si [pokyny na pripojenie k MQTT](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md) a [pokyny na odosielanie telemetrie](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md) z lekcie 4, ak je to potrebné.

1. Uistite sa, že `client_name` odráža názov tohto projektu:

    ```python
    client_name = id + 'temperature_sensor_client'
    ```

1. Pre telemetriu, namiesto odosielania hodnoty svetla, odošlite hodnotu teploty odčítanú zo senzora DHT ako vlastnosť v JSON dokumente nazvanú `temperature`:

    ```python
    _, temp = sensor.read()
    telemetry = json.dumps({'temperature' : temp})
    ```

1. Hodnotu teploty nie je potrebné odčítavať veľmi často - nebude sa výrazne meniť v krátkom čase, preto nastavte `time.sleep` na 10 minút:

    ```cpp
    time.sleep(10 * 60);
    ```

    > 💁 Funkcia `sleep` berie čas v sekundách, takže pre jednoduchšie čítanie je hodnota odovzdaná ako výsledok výpočtu. 60 sekúnd v minúte, takže 10 x (60 sekúnd v minúte) dáva 10-minútové oneskorenie.

1. Spustite kód rovnakým spôsobom, ako ste spustili kód z predchádzajúcej časti úlohy. Ak používate virtuálne IoT zariadenie, uistite sa, že aplikácia CounterFit je spustená a senzory vlhkosti a teploty boli vytvorené na správnych pinoch.

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py
    MQTT connected!
    Sending telemetry  {"temperature": 25}
    Sending telemetry  {"temperature": 25}
    ```

> 💁 Tento kód nájdete v priečinku [code-publish-temperature/virtual-device](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/virtual-device) alebo v priečinku [code-publish-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/pi).

😀 Úspešne ste publikovali teplotu ako telemetriu zo svojho zariadenia.

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby AI prekladu [Co-op Translator](https://github.com/Azure/co-op-translator). Hoci sa snažíme o presnosť, prosím, berte na vedomie, že automatizované preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho pôvodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nenesieme zodpovednosť za akékoľvek nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.