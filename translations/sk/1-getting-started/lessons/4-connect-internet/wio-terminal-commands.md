<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6754c915dae64ba70fcd5e52c37f3adf",
  "translation_date": "2025-08-28T10:10:16+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-commands.md",
  "language_code": "sk"
}
-->
# Ovládajte svoje nočné svetlo cez internet - Wio Terminal

V tejto časti lekcie sa naučíte, ako sa prihlásiť na odber príkazov odosielaných z MQTT brokera do vášho Wio Terminalu.

## Prihlásenie na odber príkazov

Ďalším krokom je prihlásiť sa na odber príkazov odosielaných z MQTT brokera a reagovať na ne.

### Úloha

Prihláste sa na odber príkazov.

1. Otvorte projekt nočného svetla vo VS Code.

1. Pridajte nasledujúci kód na koniec súboru `config.h`, aby ste definovali názov témy pre príkazy:

    ```cpp
    const string SERVER_COMMAND_TOPIC = ID + "/commands";
    ```

    `SERVER_COMMAND_TOPIC` je téma, na ktorú sa zariadenie prihlási, aby prijímalo príkazy pre LED.

1. Pridajte nasledujúci riadok na koniec funkcie `reconnectMQTTClient`, aby ste sa prihlásili na odber témy príkazov, keď sa MQTT klient znovu pripojí:

    ```cpp
    client.subscribe(SERVER_COMMAND_TOPIC.c_str());
    ```

1. Pridajte nasledujúci kód pod funkciu `reconnectMQTTClient`.

    ```cpp
    void clientCallback(char *topic, uint8_t *payload, unsigned int length)
    {
        char buff[length + 1];
        for (int i = 0; i < length; i++)
        {
            buff[i] = (char)payload[i];
        }
        buff[length] = '\0';
    
        Serial.print("Message received:");
        Serial.println(buff);
    
        DynamicJsonDocument doc(1024);
        deserializeJson(doc, buff);
        JsonObject obj = doc.as<JsonObject>();
    
        bool led_on = obj["led_on"];
    
        if (led_on)
            digitalWrite(D0, HIGH);
        else
            digitalWrite(D0, LOW);
    }
    ```

    Táto funkcia bude spätné volanie, ktoré MQTT klient zavolá, keď prijme správu zo servera.

    Správa je prijatá ako pole nesignovaných 8-bitových celých čísel, takže ju treba previesť na pole znakov, aby sa s ňou mohlo zaobchádzať ako s textom.

    Správa obsahuje JSON dokument, ktorý je dekódovaný pomocou knižnice ArduinoJson. Vlastnosť `led_on` z JSON dokumentu sa prečíta a v závislosti od jej hodnoty sa LED zapne alebo vypne.

1. Pridajte nasledujúci kód do funkcie `createMQTTClient`:

    ```cpp
    client.setCallback(clientCallback);
    ```

    Tento kód nastaví `clientCallback` ako spätné volanie, ktoré sa zavolá, keď MQTT broker odošle správu.

    > 💁 Handler `clientCallback` je volaný pre všetky témy, na ktoré ste prihlásení. Ak neskôr napíšete kód, ktorý počúva viacero tém, môžete získať tému, na ktorú bola správa odoslaná, z parametra `topic`, ktorý je odovzdaný do funkcie spätného volania.

1. Nahrajte kód do vášho Wio Terminalu a použite Serial Monitor na sledovanie úrovní svetla odosielaných do MQTT brokera.

1. Upravte úrovne svetla detekované vaším fyzickým alebo virtuálnym zariadením. Uvidíte správy prijímané a príkazy odosielané v termináli. Tiež uvidíte, ako sa LED zapína a vypína v závislosti od úrovne svetla.

> 💁 Tento kód nájdete v priečinku [code-commands/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/wio-terminal).

😀 Úspešne ste naprogramovali svoje zariadenie tak, aby reagovalo na príkazy z MQTT brokera.

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby AI prekladu [Co-op Translator](https://github.com/Azure/co-op-translator). Aj keď sa snažíme o presnosť, prosím, berte na vedomie, že automatizované preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho pôvodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nenesieme zodpovednosť za akékoľvek nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.