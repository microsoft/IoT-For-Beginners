<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1226517aae5f5b6f904434670394c688",
  "translation_date": "2025-08-28T10:12:47+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md",
  "language_code": "sk"
}
-->
# Ovládajte svoje nočné svetlo cez internet - Virtuálny IoT hardvér a Raspberry Pi

V tejto časti lekcie budete odosielať telemetriu s úrovňami svetla z vášho Raspberry Pi alebo virtuálneho IoT zariadenia do MQTT brokera.

## Publikovanie telemetrie

Ďalším krokom je vytvoriť JSON dokument s telemetriou a odoslať ho do MQTT brokera.

### Úloha

Publikujte telemetriu do MQTT brokera.

1. Otvorte projekt nočného svetla vo VS Code.

1. Ak používate virtuálne IoT zariadenie, uistite sa, že terminál beží vo virtuálnom prostredí. Ak používate Raspberry Pi, virtuálne prostredie nebudete používať.

1. Pridajte nasledujúci import na začiatok súboru `app.py`:

    ```python
    import json
    ```

    Knižnica `json` sa používa na zakódovanie telemetrie ako JSON dokumentu.

1. Pridajte nasledujúci kód za deklaráciu `client_name`:

    ```python
    client_telemetry_topic = id + '/telemetry'
    ```

    Premenná `client_telemetry_topic` je MQTT téma, do ktorej zariadenie bude publikovať úrovne svetla.

1. Nahraďte obsah cyklu `while True:` na konci súboru nasledujúcim kódom:

    ```python
    while True:
        light = light_sensor.light
        telemetry = json.dumps({'light' : light})

        print("Sending telemetry ", telemetry)
    
        mqtt_client.publish(client_telemetry_topic, telemetry)
    
        time.sleep(5)
    ```

    Tento kód zabalí úroveň svetla do JSON dokumentu a publikuje ho do MQTT brokera. Potom sa program uspí, aby sa znížila frekvencia odosielania správ.

1. Spustite kód rovnakým spôsobom, ako ste spúšťali kód z predchádzajúcej časti zadania. Ak používate virtuálne IoT zariadenie, uistite sa, že aplikácia CounterFit beží a že svetelný senzor a LED boli vytvorené na správnych pinoch.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Sending telemetry  {"light": 0}
    Sending telemetry  {"light": 0}
    ```

> 💁 Tento kód nájdete v priečinku [code-telemetry/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/virtual-device) alebo v priečinku [code-telemetry/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/pi).

😀 Úspešne ste odoslali telemetriu zo svojho zariadenia.

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby AI prekladu [Co-op Translator](https://github.com/Azure/co-op-translator). Aj keď sa snažíme o presnosť, prosím, berte na vedomie, že automatizované preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho pôvodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nenesieme zodpovednosť za akékoľvek nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.