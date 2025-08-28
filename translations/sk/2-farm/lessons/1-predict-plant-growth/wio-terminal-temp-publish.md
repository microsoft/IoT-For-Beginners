<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "df28cd649cd892bcce034e064913b2f3",
  "translation_date": "2025-08-28T11:31:54+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp-publish.md",
  "language_code": "sk"
}
-->
# Publikovanie teploty - Wio Terminal

V tejto časti lekcie budete publikovať hodnoty teploty zistené pomocou Wio Terminal cez MQTT, aby mohli byť neskôr použité na výpočet GDD.

## Publikovanie teploty

Keď je teplota odčítaná, môže byť publikovaná cez MQTT na nejaký 'serverový' kód, ktorý tieto hodnoty prečíta a uloží ich, aby mohli byť použité na výpočet GDD. Mikrokontroléry neodčítavajú čas z internetu a nesledujú čas pomocou reálneho časového hodín automaticky, zariadenie musí byť naprogramované na túto úlohu, za predpokladu, že má potrebný hardvér.

Aby sme veci v tejto lekcii zjednodušili, čas nebude posielaný spolu s údajmi zo senzora, namiesto toho ho môže pridať serverový kód neskôr, keď prijme správy.

### Úloha

Naprogramujte zariadenie na publikovanie údajov o teplote.

1. Otvorte projekt `temperature-sensor` pre Wio Terminal.

1. Opakujte kroky, ktoré ste vykonali v lekcii 4 na pripojenie k MQTT a odosielanie telemetrie. Budete používať rovnaký verejný Mosquitto broker.

    Kroky sú nasledovné:

    - Pridajte knižnice Seeed WiFi a MQTT do súboru `.ini`
    - Pridajte konfiguračný súbor a kód na pripojenie k WiFi
    - Pridajte kód na pripojenie k MQTT brokeru
    - Pridajte kód na publikovanie telemetrie

    > ⚠️ Pozrite si [pokyny na pripojenie k MQTT](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md) a [pokyny na odosielanie telemetrie](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md) z lekcie 4, ak je to potrebné.

1. Uistite sa, že `CLIENT_NAME` v hlavičkovom súbore `config.h` odráža tento projekt:

    ```cpp
    const string CLIENT_NAME = ID + "temperature_sensor_client";
    ```

1. Pre telemetriu, namiesto odosielania hodnoty svetla, odošlite hodnotu teploty odčítanú zo senzora DHT ako vlastnosť v JSON dokumente nazvanú `temperature` zmenou funkcie `loop` v `main.cpp`:

    ```cpp
    float temp_hum_val[2] = {0};
    dht.readTempAndHumidity(temp_hum_val);

    DynamicJsonDocument doc(1024);
    doc["temperature"] = temp_hum_val[1];
    ```

1. Hodnota teploty nemusí byť odčítaná veľmi často - nebude sa meniť výrazne v krátkom čase, preto nastavte `delay` vo funkcii `loop` na 10 minút:

    ```cpp
    delay(10 * 60 * 1000);
    ```

    > 💁 Funkcia `delay` berie čas v milisekundách, takže aby bolo jednoduchšie čítať hodnotu, je odovzdaná ako výsledok výpočtu. 1 000 ms v sekunde, 60 s v minúte, takže 10 x (60 s v minúte) x (1000 ms v sekunde) dáva 10-minútové oneskorenie.

1. Nahrajte toto na váš Wio Terminal a použite sériový monitor na sledovanie odosielania teploty na MQTT broker.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"temperature":25}
    Sending telemetry {"temperature":25}
    ```

> 💁 Tento kód nájdete v priečinku [code-publish-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/wio-terminal).

😀 Úspešne ste publikovali teplotu ako telemetriu zo svojho zariadenia.

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby AI prekladu [Co-op Translator](https://github.com/Azure/co-op-translator). Hoci sa snažíme o presnosť, prosím, berte na vedomie, že automatizované preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho pôvodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nie sme zodpovední za žiadne nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.