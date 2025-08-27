<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c527ce85d69b1a3875366ec61cbed8aa",
  "translation_date": "2025-08-27T22:13:39+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-commands.md",
  "language_code": "cs"
}
-->
# Ovládejte noční světlo přes internet - Virtuální IoT hardware a Raspberry Pi

V této části lekce se naučíte, jak se přihlásit k odběru příkazů odesílaných z MQTT brokeru do vašeho Raspberry Pi nebo virtuálního IoT zařízení.

## Přihlášení k odběru příkazů

Dalším krokem je přihlásit se k odběru příkazů odesílaných z MQTT brokeru a reagovat na ně.

### Úkol

Přihlaste se k odběru příkazů.

1. Otevřete projekt nočního světla ve VS Code.

1. Pokud používáte virtuální IoT zařízení, ujistěte se, že terminál běží ve virtuálním prostředí. Pokud používáte Raspberry Pi, virtuální prostředí používat nebudete.

1. Přidejte následující kód za definice `client_telemetry_topic`:

    ```python
    server_command_topic = id + '/commands'
    ```

    `server_command_topic` je MQTT téma, na které se zařízení přihlásí k odběru, aby přijímalo příkazy pro LED.

1. Přidejte následující kód těsně nad hlavní smyčku, za řádek `mqtt_client.loop_start()`:

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

    Tento kód definuje funkci `handle_command`, která čte zprávu jako JSON dokument a hledá hodnotu vlastnosti `led_on`. Pokud je nastavena na `True`, LED se zapne, jinak se vypne.

    MQTT klient se přihlásí k odběru tématu, na které server bude odesílat zprávy, a nastaví funkci `handle_command`, která se zavolá při přijetí zprávy.

    > 💁 Obsluha `on_message` je volána pro všechna témata, ke kterým jste přihlášeni. Pokud později napíšete kód, který naslouchá více tématům, můžete získat téma, na které byla zpráva odeslána, z objektu `message` předaného do obslužné funkce.

1. Spusťte kód stejným způsobem, jako jste spustili kód z předchozí části úkolu. Pokud používáte virtuální IoT zařízení, ujistěte se, že aplikace CounterFit běží a že světelný senzor a LED byly vytvořeny na správných pinech.

1. Upravte úroveň světla detekovanou vaším fyzickým nebo virtuálním zařízením. Zprávy, které jsou přijímány, a příkazy, které jsou odesílány, budou zapsány do terminálu. LED se také zapne a vypne v závislosti na úrovni světla.

> 💁 Tento kód najdete ve složce [code-commands/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/virtual-device) nebo ve složce [code-commands/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/pi).

😀 Úspěšně jste naprogramovali své zařízení tak, aby reagovalo na příkazy z MQTT brokeru.

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). Ačkoli se snažíme o přesnost, mějte prosím na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za závazný zdroj. Pro důležité informace doporučujeme profesionální lidský překlad. Neodpovídáme za žádná nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.