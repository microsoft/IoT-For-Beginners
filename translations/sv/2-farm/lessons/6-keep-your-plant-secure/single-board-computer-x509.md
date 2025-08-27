<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9aea84bcc7520222b0e1c50469d62d6a",
  "translation_date": "2025-08-27T22:38:36+00:00",
  "source_file": "2-farm/lessons/6-keep-your-plant-secure/single-board-computer-x509.md",
  "language_code": "sv"
}
-->
# Använd X.509-certifikatet i din enhetskod - Virtuell IoT-hårdvara och Raspberry Pi

I den här delen av lektionen kommer du att ansluta din virtuella IoT-enhet eller Raspberry Pi till din IoT Hub med hjälp av X.509-certifikatet.

## Anslut din enhet till IoT Hub

Nästa steg är att ansluta din enhet till IoT Hub med hjälp av X.509-certifikat.

### Uppgift - anslut till IoT Hub

1. Kopiera nyckel- och certifikatfilerna till mappen som innehåller din IoT-enhetskod. Om du använder en Raspberry Pi via VS Code Remote SSH och skapade nycklarna på din PC eller Mac, kan du dra och släppa filerna i utforskaren i VS Code för att kopiera dem.

1. Öppna filen `app.py`

1. För att ansluta med ett X.509-certifikat behöver du värdnamnet för IoT Hub och X.509-certifikatet. Börja med att skapa en variabel som innehåller värdnamnet genom att lägga till följande kod innan enhetsklienten skapas:

    ```python
    host_name = "<host_name>"
    ```

    Ersätt `<host_name>` med värdnamnet för din IoT Hub. Du kan hitta detta i avsnittet `HostName` i `connection_string`. Det kommer att vara namnet på din IoT Hub, som slutar med `.azure-devices.net`

1. Deklarera en variabel med enhets-ID nedanför detta:

    ```python
    device_id = "soil-moisture-sensor-x509"
    ```

1. Du behöver en instans av klassen `X509` som innehåller X.509-filerna. Lägg till `X509` i listan över klasser som importeras från modulen `azure.iot.device`:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse, X509
    ```

1. Skapa en instans av klassen `X509` med hjälp av dina certifikat- och nyckelfiler genom att lägga till denna kod under deklarationen av `host_name`:

    ```python
    x509 = X509("./soil-moisture-sensor-x509-cert.pem", "./soil-moisture-sensor-x509-key.pem")
    ```

    Detta skapar klassen `X509` med hjälp av filerna `soil-moisture-sensor-x509-cert.pem` och `soil-moisture-sensor-x509-key.pem` som skapades tidigare.

1. Ersätt raden med kod som skapar `device_client` från en anslutningssträng med följande:

    ```python
    device_client = IoTHubDeviceClient.create_from_x509_certificate(x509, host_name, device_id)
    ```

    Detta kommer att ansluta med hjälp av X.509-certifikatet istället för en anslutningssträng.
    
1. Ta bort raden med variabeln `connection_string`.

1. Kör din kod. Övervaka meddelandena som skickas till IoT Hub och skicka direkta metodförfrågningar som tidigare. Du kommer att se att enheten ansluter och skickar avläsningar av jordfuktighet, samt tar emot direkta metodförfrågningar.

> 💁 Du kan hitta denna kod i mappen [code/pi](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/pi) eller [code/virtual-device](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/virtual-device).

😀 Ditt program för jordfuktighetssensorn är nu anslutet till din IoT Hub med hjälp av ett X.509-certifikat!

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör det noteras att automatiserade översättningar kan innehålla fel eller brister. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som kan uppstå vid användning av denna översättning.