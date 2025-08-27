<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9aea84bcc7520222b0e1c50469d62d6a",
  "translation_date": "2025-08-27T23:07:06+00:00",
  "source_file": "2-farm/lessons/6-keep-your-plant-secure/single-board-computer-x509.md",
  "language_code": "cs"
}
-->
# Použití certifikátu X.509 ve vašem zařízení - Virtuální IoT hardware a Raspberry Pi

V této části lekce připojíte své virtuální IoT zařízení nebo Raspberry Pi k IoT Hubu pomocí certifikátu X.509.

## Připojení zařízení k IoT Hubu

Dalším krokem je připojení vašeho zařízení k IoT Hubu pomocí certifikátů X.509.

### Úkol - připojení k IoT Hubu

1. Zkopírujte soubory s klíčem a certifikátem do složky obsahující kód vašeho IoT zařízení. Pokud používáte Raspberry Pi přes VS Code Remote SSH a klíče jste vytvořili na svém PC nebo Macu, můžete soubory přetáhnout do průzkumníka ve VS Code a tím je zkopírovat.

1. Otevřete soubor `app.py`.

1. Pro připojení pomocí certifikátu X.509 budete potřebovat název hostitele IoT Hubu a certifikát X.509. Začněte vytvořením proměnné obsahující název hostitele přidáním následujícího kódu před vytvoření klienta zařízení:

    ```python
    host_name = "<host_name>"
    ```

    Nahraďte `<host_name>` názvem hostitele vašeho IoT Hubu. Tento název najdete v sekci `HostName` v `connection_string`. Bude to název vašeho IoT Hubu končící na `.azure-devices.net`.

1. Pod tímto kódem deklarujte proměnnou s ID zařízení:

    ```python
    device_id = "soil-moisture-sensor-x509"
    ```

1. Budete potřebovat instanci třídy `X509`, která obsahuje soubory certifikátu X.509. Přidejte `X509` do seznamu tříd importovaných z modulu `azure.iot.device`:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse, X509
    ```

1. Vytvořte instanci třídy `X509` pomocí vašich souborů certifikátu a klíče přidáním tohoto kódu pod deklaraci `host_name`:

    ```python
    x509 = X509("./soil-moisture-sensor-x509-cert.pem", "./soil-moisture-sensor-x509-key.pem")
    ```

    Tímto vytvoříte třídu `X509` pomocí souborů `soil-moisture-sensor-x509-cert.pem` a `soil-moisture-sensor-x509-key.pem`, které jste vytvořili dříve.

1. Nahraďte řádek kódu, který vytváří `device_client` z připojovacího řetězce, následujícím:

    ```python
    device_client = IoTHubDeviceClient.create_from_x509_certificate(x509, host_name, device_id)
    ```

    Tímto se připojíte pomocí certifikátu X.509 namísto připojovacího řetězce.

1. Smažte řádek s proměnnou `connection_string`.

1. Spusťte svůj kód. Sledujte zprávy odesílané do IoT Hubu a posílejte požadavky na přímé metody jako dříve. Uvidíte, že se zařízení připojuje, odesílá údaje o vlhkosti půdy a přijímá požadavky na přímé metody.

> 💁 Tento kód najdete ve složce [code/pi](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/pi) nebo [code/virtual-device](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/virtual-device).

😀 Váš program pro senzor vlhkosti půdy je připojen k vašemu IoT Hubu pomocí certifikátu X.509!

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). Ačkoli se snažíme o přesnost, mějte prosím na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace doporučujeme profesionální lidský překlad. Neodpovídáme za žádné nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.