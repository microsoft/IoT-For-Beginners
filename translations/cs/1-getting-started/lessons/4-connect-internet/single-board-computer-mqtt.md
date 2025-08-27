<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "90fb93446e03c38f3c0e4009c2471906",
  "translation_date": "2025-08-27T22:14:50+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md",
  "language_code": "cs"
}
-->
# Ovládejte noční světlo přes internet - Virtuální IoT hardware a Raspberry Pi

IoT zařízení musí být naprogramováno tak, aby komunikovalo s *test.mosquitto.org* pomocí MQTT, odesílalo telemetrické hodnoty s údaji ze světelného senzoru a přijímalo příkazy k ovládání LED.

V této části lekce připojíte svůj Raspberry Pi nebo virtuální IoT zařízení k MQTT brokeru.

## Instalace balíčku MQTT klienta

Pro komunikaci s MQTT brokerem je potřeba nainstalovat knihovnu MQTT jako pip balíček, buď na vašem Raspberry Pi, nebo ve virtuálním prostředí, pokud používáte virtuální zařízení.

### Úkol

Nainstalujte pip balíček

1. Otevřete projekt nočního světla ve VS Code.

1. Pokud používáte virtuální IoT zařízení, ujistěte se, že terminál běží ve virtuálním prostředí. Pokud používáte Raspberry Pi, virtuální prostředí používat nebudete.

1. Spusťte následující příkaz pro instalaci MQTT pip balíčku:

    ```sh
    pip3 install paho-mqtt
    ```

## Naprogramujte zařízení

Zařízení je připraveno k programování.

### Úkol

Napište kód zařízení.

1. Přidejte následující import na začátek souboru `app.py`:

    ```python
    import paho.mqtt.client as mqtt
    ```

    Knihovna `paho.mqtt.client` umožňuje vaší aplikaci komunikovat přes MQTT.

1. Přidejte následující kód za definice světelného senzoru a LED:

    ```python
    id = '<ID>'

    client_name = id + 'nightlight_client'
    ```

    Nahraďte `<ID>` unikátním ID, které bude použito jako název tohoto klienta zařízení a později pro témata, která toto zařízení publikuje a odebírá. Broker *test.mosquitto.org* je veřejný a používá ho mnoho lidí, včetně dalších studentů pracujících na tomto úkolu. Mít unikátní název MQTT klienta a názvy témat zajistí, že váš kód nebude kolidovat s kódem někoho jiného. Toto ID budete také potřebovat při vytváření serverového kódu později v tomto úkolu.

    > 💁 Můžete použít webovou stránku jako [GUIDGen](https://www.guidgen.com) pro vygenerování unikátního ID.

    `client_name` je unikátní název tohoto MQTT klienta na brokeru.

1. Přidejte následující kód pod tento nový kód pro vytvoření objektu MQTT klienta a připojení k MQTT brokeru:

    ```python
    mqtt_client = mqtt.Client(client_name)
    mqtt_client.connect('test.mosquitto.org')
    
    mqtt_client.loop_start()

    print("MQTT connected!")
    ```

    Tento kód vytvoří objekt klienta, připojí se k veřejnému MQTT brokeru a spustí zpracovávací smyčku, která běží na pozadí ve vlákně a naslouchá zprávám na všech odebíraných tématech.

1. Spusťte kód stejným způsobem, jako jste spouštěli kód z předchozí části úkolu. Pokud používáte virtuální IoT zařízení, ujistěte se, že aplikace CounterFit běží a že světelný senzor a LED byly vytvořeny na správných pinech.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Light level: 0
    Light level: 0
    ```

> 💁 Tento kód najdete ve složce [code-mqtt/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/virtual-device) nebo [code-mqtt/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/pi).

😀 Úspěšně jste připojili své zařízení k MQTT brokeru.

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). I když se snažíme o přesnost, mějte prosím na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za závazný zdroj. Pro důležité informace doporučujeme profesionální lidský překlad. Neodpovídáme za žádná nedorozumění nebo nesprávné výklady vyplývající z použití tohoto překladu.