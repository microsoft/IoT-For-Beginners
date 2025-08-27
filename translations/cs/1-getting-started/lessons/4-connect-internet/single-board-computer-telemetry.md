<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1226517aae5f5b6f904434670394c688",
  "translation_date": "2025-08-27T22:13:07+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md",
  "language_code": "cs"
}
-->
# Ovládejte svůj noční světlo přes internet - Virtuální IoT zařízení a Raspberry Pi

V této části lekce budete odesílat telemetrii s úrovněmi světla z vašeho Raspberry Pi nebo virtuálního IoT zařízení do MQTT brokeru.

## Publikování telemetrie

Dalším krokem je vytvoření JSON dokumentu s telemetrií a jeho odeslání do MQTT brokeru.

### Úkol

Publikujte telemetrii do MQTT brokeru.

1. Otevřete projekt nočního světla ve VS Code.

1. Pokud používáte virtuální IoT zařízení, ujistěte se, že terminál běží ve virtuálním prostředí. Pokud používáte Raspberry Pi, nebudete používat virtuální prostředí.

1. Přidejte následující import na začátek souboru `app.py`:

    ```python
    import json
    ```

    Knihovna `json` se používá k zakódování telemetrie jako JSON dokumentu.

1. Přidejte následující po deklaraci `client_name`:

    ```python
    client_telemetry_topic = id + '/telemetry'
    ```

    `client_telemetry_topic` je MQTT téma, do kterého zařízení bude publikovat úrovně světla.

1. Nahraďte obsah smyčky `while True:` na konci souboru následujícím:

    ```python
    while True:
        light = light_sensor.light
        telemetry = json.dumps({'light' : light})

        print("Sending telemetry ", telemetry)
    
        mqtt_client.publish(client_telemetry_topic, telemetry)
    
        time.sleep(5)
    ```

    Tento kód zabalí úroveň světla do JSON dokumentu a publikuje ji do MQTT brokeru. Poté se uspí, aby se snížila frekvence odesílání zpráv.

1. Spusťte kód stejným způsobem, jako jste spouštěli kód z předchozí části úkolu. Pokud používáte virtuální IoT zařízení, ujistěte se, že aplikace CounterFit běží a že světelný senzor a LED byly vytvořeny na správných pinech.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Sending telemetry  {"light": 0}
    Sending telemetry  {"light": 0}
    ```

> 💁 Tento kód najdete ve složce [code-telemetry/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/virtual-device) nebo ve složce [code-telemetry/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/pi).

😀 Úspěšně jste odeslali telemetrii ze svého zařízení.

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). Ačkoli se snažíme o přesnost, mějte prosím na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace doporučujeme profesionální lidský překlad. Neodpovídáme za žádná nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.