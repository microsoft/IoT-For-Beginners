<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9aea84bcc7520222b0e1c50469d62d6a",
  "translation_date": "2025-08-27T22:38:59+00:00",
  "source_file": "2-farm/lessons/6-keep-your-plant-secure/single-board-computer-x509.md",
  "language_code": "no"
}
-->
# Bruk X.509-sertifikatet i enhetskoden din - Virtuell IoT-maskinvare og Raspberry Pi

I denne delen av leksjonen skal du koble din virtuelle IoT-enhet eller Raspberry Pi til IoT Hub ved hjelp av X.509-sertifikatet.

## Koble enheten din til IoT Hub

Neste steg er å koble enheten din til IoT Hub ved hjelp av X.509-sertifikater.

### Oppgave - koble til IoT Hub

1. Kopier nøkkel- og sertifikatfilene til mappen som inneholder IoT-enhetskoden din. Hvis du bruker en Raspberry Pi via VS Code Remote SSH og har opprettet nøklene på PC-en eller Mac-en din, kan du dra og slippe filene inn i utforskeren i VS Code for å kopiere dem.

1. Åpne `app.py`-filen.

1. For å koble til med et X.509-sertifikat, trenger du vertsnavnet til IoT Hub og X.509-sertifikatet. Start med å opprette en variabel som inneholder vertsnavnet ved å legge til følgende kode før enhetsklienten opprettes:

    ```python
    host_name = "<host_name>"
    ```

    Erstatt `<host_name>` med vertsnavnet til IoT Hub. Du finner dette i `HostName`-delen av `connection_string`. Det vil være navnet på IoT Hub, som slutter med `.azure-devices.net`.

1. Under dette, deklarer en variabel med enhets-ID:

    ```python
    device_id = "soil-moisture-sensor-x509"
    ```

1. Du trenger en instans av `X509`-klassen som inneholder X.509-filene. Legg til `X509` i listen over klasser importert fra `azure.iot.device`-modulen:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse, X509
    ```

1. Opprett en instans av `X509`-klassen ved å bruke sertifikat- og nøkkelfilene dine ved å legge til denne koden under deklarasjonen av `host_name`:

    ```python
    x509 = X509("./soil-moisture-sensor-x509-cert.pem", "./soil-moisture-sensor-x509-key.pem")
    ```

    Dette vil opprette `X509`-klassen ved hjelp av filene `soil-moisture-sensor-x509-cert.pem` og `soil-moisture-sensor-x509-key.pem` som ble opprettet tidligere.

1. Erstatt linjen med kode som oppretter `device_client` fra en tilkoblingsstreng med følgende:

    ```python
    device_client = IoTHubDeviceClient.create_from_x509_certificate(x509, host_name, device_id)
    ```

    Dette vil koble til ved hjelp av X.509-sertifikatet i stedet for en tilkoblingsstreng.

1. Slett linjen med `connection_string`-variabelen.

1. Kjør koden din. Overvåk meldingene som sendes til IoT Hub, og send direkte metodeforespørsler som før. Du vil se enheten koble til og sende jordfuktighetsavlesninger, samt motta direkte metodeforespørsler.

> 💁 Du finner denne koden i [code/pi](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/pi) eller [code/virtual-device](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/virtual-device)-mappen.

😀 Jordfuktighetssensorprogrammet ditt er nå koblet til IoT Hub ved hjelp av et X.509-sertifikat!

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.