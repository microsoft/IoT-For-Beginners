<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9aea84bcc7520222b0e1c50469d62d6a",
  "translation_date": "2025-10-11T12:43:36+00:00",
  "source_file": "2-farm/lessons/6-keep-your-plant-secure/single-board-computer-x509.md",
  "language_code": "et"
}
-->
# Kasuta X.509 sertifikaati oma seadme koodis - Virtuaalne IoT riistvara ja Raspberry Pi

Selles õppetunni osas ühendad oma virtuaalse IoT seadme või Raspberry Pi IoT Hubiga, kasutades X.509 sertifikaati.

## Ühenda oma seade IoT Hubiga

Järgmine samm on ühendada oma seade IoT Hubiga, kasutades X.509 sertifikaate.

### Ülesanne - ühendamine IoT Hubiga

1. Kopeeri võtme- ja sertifikaadifailid kausta, kus asub sinu IoT seadme kood. Kui kasutad Raspberry Pi-d läbi VS Code Remote SSH ja lõid võtmed oma PC-s või Macis, saad failid VS Code'i explorerisse lohistades kopeerida.

1. Ava `app.py` fail.

1. X.509 sertifikaadi abil ühendamiseks vajad IoT Hubi hostinime ja X.509 sertifikaati. Alusta, luues muutuja, mis sisaldab hostinime, lisades järgmise koodi enne seadme kliendi loomist:

    ```python
    host_name = "<host_name>"
    ```

    Asenda `<host_name>` oma IoT Hubi hostinimega. Selle leiad `connection_string` sektsioonist `HostName` alt. See on sinu IoT Hubi nimi, mis lõpeb `.azure-devices.net`.

1. Deklareeri selle all muutuja seadme ID-ga:

    ```python
    device_id = "soil-moisture-sensor-x509"
    ```

1. Sul on vaja `X509` klassi instantsi, mis sisaldab X.509 faile. Lisa `X509` klass `azure.iot.device` moodulist imporditud klasside nimekirja:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse, X509
    ```

1. Loo `X509` klassi instants, kasutades oma sertifikaadi- ja võtmefaile, lisades selle koodi hostinime deklaratsiooni alla:

    ```python
    x509 = X509("./soil-moisture-sensor-x509-cert.pem", "./soil-moisture-sensor-x509-key.pem")
    ```

    See loob `X509` klassi, kasutades varem loodud faile `soil-moisture-sensor-x509-cert.pem` ja `soil-moisture-sensor-x509-key.pem`.

1. Asenda koodirida, mis loob `device_client` ühenduse stringi abil, järgmisega:

    ```python
    device_client = IoTHubDeviceClient.create_from_x509_certificate(x509, host_name, device_id)
    ```

    See ühendab X.509 sertifikaadi abil, mitte ühenduse stringi kaudu.

1. Kustuta rida, kus on `connection_string` muutuja.

1. Käivita oma kood. Jälgi IoT Hubile saadetud sõnumeid ja saada otsemeetodi päringuid nagu varem. Näed, kuidas seade ühendub ja saadab mulla niiskuse näite, samuti võtab vastu otsemeetodi päringuid.

> 💁 Selle koodi leiad [code/pi](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/pi) või [code/virtual-device](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/virtual-device) kaustast.

😀 Sinu mulla niiskuse sensori programm on ühendatud IoT Hubiga, kasutades X.509 sertifikaati!

---

**Lahtiütlus**:  
See dokument on tõlgitud AI tõlketeenuse [Co-op Translator](https://github.com/Azure/co-op-translator) abil. Kuigi püüame tagada täpsust, palume arvestada, et automaatsed tõlked võivad sisaldada vigu või ebatäpsusi. Algne dokument selle algses keeles tuleks pidada autoriteetseks allikaks. Olulise teabe puhul soovitame kasutada professionaalset inimtõlget. Me ei vastuta selle tõlke kasutamisest tulenevate arusaamatuste või valesti tõlgenduste eest.