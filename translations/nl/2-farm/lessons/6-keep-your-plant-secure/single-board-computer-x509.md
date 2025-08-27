<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9aea84bcc7520222b0e1c50469d62d6a",
  "translation_date": "2025-08-27T21:38:44+00:00",
  "source_file": "2-farm/lessons/6-keep-your-plant-secure/single-board-computer-x509.md",
  "language_code": "nl"
}
-->
# Gebruik het X.509-certificaat in je apparaatcode - Virtuele IoT-hardware en Raspberry Pi

In dit deel van de les verbind je je virtuele IoT-apparaat of Raspberry Pi met je IoT Hub met behulp van het X.509-certificaat.

## Verbind je apparaat met IoT Hub

De volgende stap is om je apparaat te verbinden met IoT Hub met behulp van de X.509-certificaten.

### Taak - verbinden met IoT Hub

1. Kopieer de sleutel- en certificaatbestanden naar de map waarin je IoT-apparaatcode staat. Als je een Raspberry Pi gebruikt via VS Code Remote SSH en de sleutels op je pc of Mac hebt aangemaakt, kun je de bestanden naar de verkenner in VS Code slepen en neerzetten om ze te kopiëren.

1. Open het bestand `app.py`.

1. Om verbinding te maken met een X.509-certificaat, heb je de hostnaam van de IoT Hub en het X.509-certificaat nodig. Begin met het maken van een variabele die de hostnaam bevat door de volgende code toe te voegen voordat de apparaatclient wordt aangemaakt:

    ```python
    host_name = "<host_name>"
    ```

    Vervang `<host_name>` door de hostnaam van je IoT Hub. Je kunt deze vinden in de sectie `HostName` in de `connection_string`. Dit zal de naam van je IoT Hub zijn, eindigend op `.azure-devices.net`.

1. Verklaar hieronder een variabele met de apparaat-ID:

    ```python
    device_id = "soil-moisture-sensor-x509"
    ```

1. Je hebt een instantie van de `X509`-klasse nodig die de X.509-bestanden bevat. Voeg `X509` toe aan de lijst van klassen die worden geïmporteerd uit de module `azure.iot.device`:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse, X509
    ```

1. Maak een instantie van de `X509`-klasse met behulp van je certificaat- en sleutelbestanden door deze code toe te voegen onder de declaratie van `host_name`:

    ```python
    x509 = X509("./soil-moisture-sensor-x509-cert.pem", "./soil-moisture-sensor-x509-key.pem")
    ```

    Dit zal de `X509`-klasse maken met behulp van de bestanden `soil-moisture-sensor-x509-cert.pem` en `soil-moisture-sensor-x509-key.pem` die eerder zijn aangemaakt.

1. Vervang de regel code die de `device_client` aanmaakt vanuit een verbindingsreeks door het volgende:

    ```python
    device_client = IoTHubDeviceClient.create_from_x509_certificate(x509, host_name, device_id)
    ```

    Dit zal verbinding maken met behulp van het X.509-certificaat in plaats van een verbindingsreeks.

1. Verwijder de regel met de variabele `connection_string`.

1. Voer je code uit. Monitor de berichten die naar IoT Hub worden verzonden en stuur directe methodeverzoeken zoals eerder. Je zult zien dat het apparaat verbinding maakt en metingen van bodemvocht verzendt, evenals directe methodeverzoeken ontvangt.

> 💁 Je kunt deze code vinden in de map [code/pi](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/pi) of [code/virtual-device](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/virtual-device).

😀 Je programma voor de bodemvochtsensor is verbonden met je IoT Hub met behulp van een X.509-certificaat!

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in de oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.