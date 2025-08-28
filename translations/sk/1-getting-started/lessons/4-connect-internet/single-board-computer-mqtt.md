<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "90fb93446e03c38f3c0e4009c2471906",
  "translation_date": "2025-08-28T10:14:41+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md",
  "language_code": "sk"
}
-->
# Ovládajte svoje nočné svetlo cez internet - Virtuálny IoT hardvér a Raspberry Pi

IoT zariadenie musí byť naprogramované tak, aby komunikovalo s *test.mosquitto.org* pomocou MQTT na odosielanie telemetrických hodnôt zo snímača svetla a prijímanie príkazov na ovládanie LED diódy.

V tejto časti lekcie pripojíte svoj Raspberry Pi alebo virtuálne IoT zariadenie k MQTT brokerovi.

## Inštalácia balíka MQTT klienta

Na komunikáciu s MQTT brokerom je potrebné nainštalovať knižnicu MQTT cez pip, buď na vašom Raspberry Pi, alebo vo virtuálnom prostredí, ak používate virtuálne zariadenie.

### Úloha

Nainštalujte pip balík

1. Otvorte projekt nočného svetla vo VS Code.

1. Ak používate virtuálne IoT zariadenie, uistite sa, že terminál beží vo virtuálnom prostredí. Ak používate Raspberry Pi, virtuálne prostredie používať nebudete.

1. Spustite nasledujúci príkaz na inštaláciu MQTT pip balíka:

    ```sh
    pip3 install paho-mqtt
    ```

## Naprogramujte zariadenie

Zariadenie je pripravené na programovanie.

### Úloha

Napíšte kód pre zariadenie.

1. Pridajte nasledujúci import na začiatok súboru `app.py`:

    ```python
    import paho.mqtt.client as mqtt
    ```

    Knižnica `paho.mqtt.client` umožňuje vašej aplikácii komunikovať cez MQTT.

1. Pridajte nasledujúci kód za definície snímača svetla a LED diódy:

    ```python
    id = '<ID>'

    client_name = id + 'nightlight_client'
    ```

    Nahraďte `<ID>` jedinečným ID, ktoré bude použité ako názov tohto klienta zariadenia a neskôr pre témy, ktoré toto zariadenie publikuje a odoberá. Broker *test.mosquitto.org* je verejný a používa ho veľa ľudí, vrátane iných študentov pracujúcich na tejto úlohe. Použitie jedinečného názvu MQTT klienta a názvov tém zabezpečí, že váš kód nebude kolidovať s kódom niekoho iného. Toto ID budete potrebovať aj pri vytváraní serverového kódu neskôr v tejto úlohe.

    > 💁 Môžete použiť webovú stránku ako [GUIDGen](https://www.guidgen.com) na vygenerovanie jedinečného ID.

    `client_name` je jedinečný názov pre tohto MQTT klienta na brokeri.

1. Pridajte nasledujúci kód pod tento nový kód na vytvorenie objektu MQTT klienta a pripojenie k MQTT brokerovi:

    ```python
    mqtt_client = mqtt.Client(client_name)
    mqtt_client.connect('test.mosquitto.org')
    
    mqtt_client.loop_start()

    print("MQTT connected!")
    ```

    Tento kód vytvára objekt klienta, pripája sa k verejnému MQTT brokerovi a spúšťa spracovávaciu slučku, ktorá beží na pozadí v samostatnom vlákne a počúva správy na všetkých odoberaných témach.

1. Spustite kód rovnakým spôsobom, ako ste spustili kód z predchádzajúcej časti úlohy. Ak používate virtuálne IoT zariadenie, uistite sa, že aplikácia CounterFit beží a že snímač svetla a LED dióda boli vytvorené na správnych pinoch.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Light level: 0
    Light level: 0
    ```

> 💁 Tento kód nájdete v priečinku [code-mqtt/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/virtual-device) alebo v priečinku [code-mqtt/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/pi).

😀 Úspešne ste pripojili svoje zariadenie k MQTT brokerovi.

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby AI prekladu [Co-op Translator](https://github.com/Azure/co-op-translator). Aj keď sa snažíme o presnosť, prosím, berte na vedomie, že automatizované preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho rodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nenesieme zodpovednosť za akékoľvek nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.