<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9aea84bcc7520222b0e1c50469d62d6a",
  "translation_date": "2025-08-27T22:38:47+00:00",
  "source_file": "2-farm/lessons/6-keep-your-plant-secure/single-board-computer-x509.md",
  "language_code": "da"
}
-->
# Brug X.509-certifikatet i din enhedskode - Virtuel IoT-hardware og Raspberry Pi

I denne del af lektionen vil du forbinde din virtuelle IoT-enhed eller Raspberry Pi til din IoT Hub ved hjælp af X.509-certifikatet.

## Forbind din enhed til IoT Hub

Det næste skridt er at forbinde din enhed til IoT Hub ved hjælp af X.509-certifikater.

### Opgave - forbind til IoT Hub

1. Kopiér nøgle- og certifikatfilerne til mappen, der indeholder din IoT-enhedskode. Hvis du bruger en Raspberry Pi via VS Code Remote SSH og har oprettet nøglerne på din PC eller Mac, kan du trække og slippe filerne ind i explorer i VS Code for at kopiere dem.

1. Åbn filen `app.py`.

1. For at forbinde ved hjælp af et X.509-certifikat skal du bruge værtsnavnet på IoT Hub og X.509-certifikatet. Start med at oprette en variabel, der indeholder værtsnavnet, ved at tilføje følgende kode før enhedsklienten oprettes:

    ```python
    host_name = "<host_name>"
    ```

    Erstat `<host_name>` med værtsnavnet på din IoT Hub. Du kan finde dette i sektionen `HostName` i `connection_string`. Det vil være navnet på din IoT Hub, som slutter med `.azure-devices.net`.

1. Under dette skal du erklære en variabel med enheds-ID'et:

    ```python
    device_id = "soil-moisture-sensor-x509"
    ```

1. Du skal bruge en instans af klassen `X509`, der indeholder X.509-filerne. Tilføj `X509` til listen over klasser, der importeres fra modulet `azure.iot.device`:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse, X509
    ```

1. Opret en instans af klassen `X509` ved hjælp af dine certifikat- og nøglefiler ved at tilføje denne kode under erklæringen af `host_name`:

    ```python
    x509 = X509("./soil-moisture-sensor-x509-cert.pem", "./soil-moisture-sensor-x509-key.pem")
    ```

    Dette vil oprette klassen `X509` ved hjælp af filerne `soil-moisture-sensor-x509-cert.pem` og `soil-moisture-sensor-x509-key.pem`, som blev oprettet tidligere.

1. Erstat linjen med kode, der opretter `device_client` fra en forbindelsesstreng, med følgende:

    ```python
    device_client = IoTHubDeviceClient.create_from_x509_certificate(x509, host_name, device_id)
    ```

    Dette vil forbinde ved hjælp af X.509-certifikatet i stedet for en forbindelsesstreng.

1. Slet linjen med variablen `connection_string`.

1. Kør din kode. Overvåg de beskeder, der sendes til IoT Hub, og send direkte metodeanmodninger som før. Du vil se enheden forbinde og sende målinger af jordfugtighed samt modtage direkte metodeanmodninger.

> 💁 Du kan finde denne kode i mappen [code/pi](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/pi) eller [code/virtual-device](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/virtual-device).

😀 Dit program til jordfugtighedssensoren er nu forbundet til din IoT Hub ved hjælp af et X.509-certifikat!

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi påtager os ikke ansvar for eventuelle misforståelser eller fejltolkninger, der opstår som følge af brugen af denne oversættelse.