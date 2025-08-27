<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3ac42e284a7222c0e83d2d43231a364f",
  "translation_date": "2025-08-27T23:12:51+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/single-board-computer-connect-hub.md",
  "language_code": "cs"
}
-->
# Připojte své IoT zařízení ke cloudu - Virtuální IoT hardware a Raspberry Pi

V této části lekce připojíte své virtuální IoT zařízení nebo Raspberry Pi k IoT Hubu, abyste mohli odesílat telemetrii a přijímat příkazy.

## Připojte své zařízení k IoT Hubu

Dalším krokem je připojení vašeho zařízení k IoT Hubu.

### Úkol - připojení k IoT Hubu

1. Otevřete složku `soil-moisture-sensor` ve VS Code. Ujistěte se, že virtuální prostředí běží v terminálu, pokud používáte virtuální IoT zařízení.

1. Nainstalujte několik dalších balíčků pomocí Pip:

    ```sh
    pip3 install azure-iot-device
    ```

    `azure-iot-device` je knihovna pro komunikaci s vaším IoT Hubem.

1. Přidejte následující importy na začátek souboru `app.py`, pod stávající importy:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse
    ```

    Tento kód importuje SDK pro komunikaci s vaším IoT Hubem.

1. Odstraňte řádek `import paho.mqtt.client as mqtt`, protože tato knihovna již není potřeba. Odstraňte veškerý kód MQTT včetně názvů témat, veškerý kód, který používá `mqtt_client`, a funkci `handle_command`. Zachovejte smyčku `while True:`, pouze odstraňte řádek `mqtt_client.publish` z této smyčky.

1. Přidejte následující kód pod importy:

    ```python
    connection_string = "<connection string>"
    ```

    Nahraďte `<connection string>` připojovacím řetězcem, který jste získali pro zařízení dříve v této lekci.

    > 💁 Toto není nejlepší praxe. Připojovací řetězce by nikdy neměly být ukládány do zdrojového kódu, protože mohou být zkontrolovány do systému správy zdrojového kódu a nalezeny kýmkoliv. Děláme to zde kvůli jednoduchosti. Ideálně byste měli použít něco jako proměnné prostředí a nástroj jako [`python-dotenv`](https://pypi.org/project/python-dotenv/). Více se o tom dozvíte v nadcházející lekci.

1. Pod tento kód přidejte následující, abyste vytvořili objekt klienta zařízení, který může komunikovat s IoT Hubem, a připojte ho:

    ```python
    device_client = IoTHubDeviceClient.create_from_connection_string(connection_string)

    print('Connecting')
    device_client.connect()
    print('Connected')
    ```

1. Spusťte tento kód. Uvidíte, že se vaše zařízení připojí.

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Connecting
    Connected
    Soil moisture: 379
    ```

## Odesílání telemetrie

Nyní, když je vaše zařízení připojeno, můžete odesílat telemetrii do IoT Hubu místo MQTT brokeru.

### Úkol - odesílání telemetrie

1. Přidejte následující kód do smyčky `while True`, těsně před příkaz `sleep`:

    ```python
    message = Message(json.dumps({ 'soil_moisture': soil_moisture }))
    device_client.send_message(message)
    ```

    Tento kód vytvoří IoT Hub `Message`, která obsahuje hodnotu vlhkosti půdy jako JSON řetězec, a odešle ji do IoT Hubu jako zprávu z zařízení do cloudu.

## Zpracování příkazů

Vaše zařízení musí zpracovat příkaz ze serverového kódu pro ovládání relé. Tento příkaz je odeslán jako požadavek na přímou metodu.

## Úkol - zpracování požadavku na přímou metodu

1. Přidejte následující kód před smyčku `while True`:

    ```python
    def handle_method_request(request):
        print("Direct method received - ", request.name)
    
        if request.name == "relay_on":
            relay.on()
        elif request.name == "relay_off":
            relay.off()    
    ```

    Tento kód definuje metodu `handle_method_request`, která bude volána, když IoT Hub zavolá přímou metodu. Každá přímá metoda má název, a tento kód očekává metodu nazvanou `relay_on` pro zapnutí relé a `relay_off` pro vypnutí relé.

    > 💁 Toto by také mohlo být implementováno v jedné přímé metodě, která by předávala požadovaný stav relé v payloadu, který může být předán s požadavkem na metodu a dostupný z objektu `request`.

1. Přímé metody vyžadují odpověď, která informuje volající kód, že byly zpracovány. Přidejte následující kód na konec funkce `handle_method_request`, abyste vytvořili odpověď na požadavek:

    ```python
    method_response = MethodResponse.create_from_method_request(request, 200)
    device_client.send_method_response(method_response)
    ```

    Tento kód odešle odpověď na požadavek přímé metody s HTTP status kódem 200 a odešle ji zpět do IoT Hubu.

1. Přidejte následující kód pod definici této funkce:

    ```python
    device_client.on_method_request_received = handle_method_request
    ```

    Tento kód říká klientovi IoT Hubu, aby volal funkci `handle_method_request`, když je zavolána přímá metoda.

> 💁 Tento kód najdete ve složce [code/pi](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/pi) nebo [code/virtual-device](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/virtual-device).

😀 Váš program senzoru vlhkosti půdy je připojen k vašemu IoT Hubu!

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). I když se snažíme o přesnost, mějte na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace se doporučuje profesionální lidský překlad. Neodpovídáme za žádná nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.