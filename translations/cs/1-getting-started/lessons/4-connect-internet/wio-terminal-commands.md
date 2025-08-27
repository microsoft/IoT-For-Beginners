<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6754c915dae64ba70fcd5e52c37f3adf",
  "translation_date": "2025-08-27T22:11:17+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-commands.md",
  "language_code": "cs"
}
-->
# Ovládejte svůj noční světlo přes internet - Wio Terminal

V této části lekce se naučíte, jak se přihlásit k odběru příkazů zasílaných z MQTT brokeru do vašeho Wio Terminalu.

## Přihlášení k odběru příkazů

Dalším krokem je přihlásit se k odběru příkazů zasílaných z MQTT brokeru a reagovat na ně.

### Úkol

Přihlaste se k odběru příkazů.

1. Otevřete projekt nočního světla ve VS Code.

1. Přidejte následující kód na konec souboru `config.h`, abyste definovali název tématu pro příkazy:

    ```cpp
    const string SERVER_COMMAND_TOPIC = ID + "/commands";
    ```

    `SERVER_COMMAND_TOPIC` je téma, ke kterému se zařízení přihlásí, aby přijímalo příkazy pro LED.

1. Přidejte následující řádek na konec funkce `reconnectMQTTClient`, aby se zařízení přihlásilo k odběru tématu příkazů při opětovném připojení MQTT klienta:

    ```cpp
    client.subscribe(SERVER_COMMAND_TOPIC.c_str());
    ```

1. Přidejte následující kód pod funkci `reconnectMQTTClient`.

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

    Tato funkce bude zpětné volání, které MQTT klient zavolá, když obdrží zprávu ze serveru.

    Zpráva je přijímána jako pole 8bitových neznačených celých čísel, takže je třeba ji převést na pole znaků, aby mohla být zpracována jako text.

    Zpráva obsahuje JSON dokument, který je dekódován pomocí knihovny ArduinoJson. Vlastnost `led_on` z JSON dokumentu je přečtena a v závislosti na její hodnotě se LED zapne nebo vypne.

1. Přidejte následující kód do funkce `createMQTTClient`:

    ```cpp
    client.setCallback(clientCallback);
    ```

    Tento kód nastaví `clientCallback` jako zpětné volání, které bude zavoláno, když MQTT broker odešle zprávu.

    > 💁 Zpětné volání `clientCallback` je voláno pro všechna témata, ke kterým jste přihlášeni. Pokud později napíšete kód, který poslouchá více témat, můžete získat téma, na které byla zpráva odeslána, z parametru `topic` předaného zpětnému volání.

1. Nahrajte kód do svého Wio Terminalu a použijte Serial Monitor, abyste viděli úrovně světla odesílané do MQTT brokeru.

1. Upravte úrovně světla detekované vaším fyzickým nebo virtuálním zařízením. Uvidíte zprávy, které jsou přijímány, a příkazy, které jsou odesílány v terminálu. Také uvidíte, jak se LED zapíná a vypíná v závislosti na úrovni světla.

> 💁 Tento kód najdete ve složce [code-commands/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/wio-terminal).

😀 Úspěšně jste naprogramovali své zařízení, aby reagovalo na příkazy z MQTT brokeru.

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). I když se snažíme o přesnost, mějte na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace doporučujeme profesionální lidský překlad. Neodpovídáme za žádná nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.