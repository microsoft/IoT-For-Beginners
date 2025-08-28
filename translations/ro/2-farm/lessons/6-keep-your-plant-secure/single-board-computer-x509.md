<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9aea84bcc7520222b0e1c50469d62d6a",
  "translation_date": "2025-08-28T11:17:54+00:00",
  "source_file": "2-farm/lessons/6-keep-your-plant-secure/single-board-computer-x509.md",
  "language_code": "ro"
}
-->
# Utilizați certificatul X.509 în codul dispozitivului - Hardware IoT Virtual și Raspberry Pi

În această parte a lecției, veți conecta dispozitivul IoT virtual sau Raspberry Pi la IoT Hub utilizând certificatul X.509.

## Conectați dispozitivul la IoT Hub

Următorul pas este să conectați dispozitivul la IoT Hub utilizând certificatele X.509.

### Sarcină - conectați-vă la IoT Hub

1. Copiați fișierele cheie și certificat în folderul care conține codul dispozitivului IoT. Dacă utilizați un Raspberry Pi prin VS Code Remote SSH și ați creat cheile pe PC sau Mac, puteți trage și plasa fișierele în explorer-ul din VS Code pentru a le copia.

1. Deschideți fișierul `app.py`.

1. Pentru a vă conecta utilizând un certificat X.509, veți avea nevoie de numele gazdei IoT Hub și de certificatul X.509. Începeți prin a crea o variabilă care conține numele gazdei, adăugând următorul cod înainte de crearea clientului dispozitivului:

    ```python
    host_name = "<host_name>"
    ```

    Înlocuiți `<host_name>` cu numele gazdei IoT Hub. Puteți obține acest lucru din secțiunea `HostName` din `connection_string`. Va fi numele IoT Hub-ului dvs., terminându-se cu `.azure-devices.net`.

1. Sub acest cod, declarați o variabilă cu ID-ul dispozitivului:

    ```python
    device_id = "soil-moisture-sensor-x509"
    ```

1. Veți avea nevoie de o instanță a clasei `X509` care conține fișierele X.509. Adăugați `X509` la lista de clase importate din modulul `azure.iot.device`:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse, X509
    ```

1. Creați o instanță a clasei `X509` utilizând fișierele certificatului și cheii, adăugând acest cod sub declarația `host_name`:

    ```python
    x509 = X509("./soil-moisture-sensor-x509-cert.pem", "./soil-moisture-sensor-x509-key.pem")
    ```

    Acest lucru va crea clasa `X509` utilizând fișierele `soil-moisture-sensor-x509-cert.pem` și `soil-moisture-sensor-x509-key.pem` create anterior.

1. Înlocuiți linia de cod care creează `device_client` dintr-un connection string cu următorul cod:

    ```python
    device_client = IoTHubDeviceClient.create_from_x509_certificate(x509, host_name, device_id)
    ```

    Acest lucru va permite conectarea utilizând certificatul X.509 în loc de connection string.
    
1. Ștergeți linia cu variabila `connection_string`.

1. Rulați codul. Monitorizați mesajele trimise către IoT Hub și trimiteți cereri de metode directe ca înainte. Veți vedea dispozitivul conectându-se și trimițând citiri ale umidității solului, precum și primind cereri de metode directe.

> 💁 Puteți găsi acest cod în folderul [code/pi](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/pi) sau [code/virtual-device](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/virtual-device).

😀 Programul senzorului de umiditate a solului este conectat la IoT Hub utilizând un certificat X.509!

---

**Declinare de responsabilitate**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să rețineți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa maternă ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist. Nu ne asumăm responsabilitatea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.