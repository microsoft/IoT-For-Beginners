<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c527ce85d69b1a3875366ec61cbed8aa",
  "translation_date": "2025-08-28T10:13:22+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-commands.md",
  "language_code": "sk"
}
-->
# Ovládajte svoje nočné svetlo cez internet - Virtuálny IoT hardvér a Raspberry Pi

V tejto časti lekcie sa naučíte, ako sa prihlásiť na odber príkazov odoslaných z MQTT brokeru na váš Raspberry Pi alebo virtuálne IoT zariadenie.

## Prihlásenie na odber príkazov

Ďalším krokom je prihlásenie na odber príkazov odoslaných z MQTT brokeru a reagovanie na ne.

### Úloha

Prihláste sa na odber príkazov.

1. Otvorte projekt nočného svetla vo VS Code.

1. Ak používate virtuálne IoT zariadenie, uistite sa, že terminál beží vo virtuálnom prostredí. Ak používate Raspberry Pi, virtuálne prostredie nebudete používať.

1. Pridajte nasledujúci kód po definíciách `client_telemetry_topic`:

    ```python
    server_command_topic = id + '/commands'
    ```

    `server_command_topic` je MQTT téma, na ktorú sa zariadenie prihlási, aby prijímalo príkazy pre LED.

1. Pridajte nasledujúci kód tesne nad hlavný cyklus, po riadku `mqtt_client.loop_start()`:

    ```python
    def handle_command(client, userdata, message):
        payload = json.loads(message.payload.decode())
        print("Message received:", payload)
    
        if payload['led_on']:
            led.on()
        else:
            led.off()
    
    mqtt_client.subscribe(server_command_topic)
    mqtt_client.on_message = handle_command
    ```

    Tento kód definuje funkciu `handle_command`, ktorá číta správu ako JSON dokument a hľadá hodnotu vlastnosti `led_on`. Ak je nastavená na `True`, LED sa zapne, inak sa vypne.

    MQTT klient sa prihlási na tému, na ktorú server bude odosielať správy, a nastaví funkciu `handle_command`, ktorá sa zavolá, keď sa prijme správa.

    > 💁 Handler `on_message` sa volá pre všetky témy, na ktoré ste prihlásení. Ak neskôr napíšete kód, ktorý počúva viaceré témy, môžete získať tému, na ktorú bola správa odoslaná, z objektu `message`, ktorý sa odovzdáva funkcii handlera.

1. Spustite kód rovnakým spôsobom, ako ste spustili kód z predchádzajúcej časti úlohy. Ak používate virtuálne IoT zariadenie, uistite sa, že aplikácia CounterFit beží a svetelný senzor a LED sú vytvorené na správnych pinoch.

1. Nastavte úroveň svetla detekovanú vaším fyzickým alebo virtuálnym zariadením. Správy, ktoré sa prijímajú, a príkazy, ktoré sa odosielajú, budú zapísané do terminálu. LED sa tiež zapne a vypne v závislosti od úrovne svetla.

> 💁 Tento kód nájdete v priečinku [code-commands/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/virtual-device) alebo v priečinku [code-commands/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/pi).

😀 Úspešne ste naprogramovali svoje zariadenie tak, aby reagovalo na príkazy z MQTT brokeru.

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby AI prekladu [Co-op Translator](https://github.com/Azure/co-op-translator). Hoci sa snažíme o presnosť, prosím, berte na vedomie, že automatizované preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho pôvodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nenesieme zodpovednosť za akékoľvek nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.