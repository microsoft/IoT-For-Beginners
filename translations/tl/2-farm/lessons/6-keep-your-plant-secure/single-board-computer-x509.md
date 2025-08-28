<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9aea84bcc7520222b0e1c50469d62d6a",
  "translation_date": "2025-08-28T01:30:09+00:00",
  "source_file": "2-farm/lessons/6-keep-your-plant-secure/single-board-computer-x509.md",
  "language_code": "tl"
}
-->
# Gamitin ang X.509 certificate sa iyong device code - Virtual IoT Hardware at Raspberry Pi

Sa bahaging ito ng aralin, ikokonekta mo ang iyong virtual na IoT device o Raspberry Pi sa iyong IoT Hub gamit ang X.509 certificate.

## Ikonekta ang iyong device sa IoT Hub

Ang susunod na hakbang ay ikonekta ang iyong device sa IoT Hub gamit ang X.509 certificates.

### Gawain - ikonekta sa IoT Hub

1. Kopyahin ang key at certificate files sa folder na naglalaman ng iyong IoT device code. Kung gumagamit ka ng Raspberry Pi sa pamamagitan ng VS Code Remote SSH at ginawa ang mga keys sa iyong PC o Mac, maaari mong i-drag at i-drop ang mga files sa explorer sa VS Code upang makopya ang mga ito.

1. Buksan ang `app.py` file.

1. Upang kumonekta gamit ang X.509 certificate, kakailanganin mo ang host name ng IoT Hub, at ang X.509 certificate. Magsimula sa pamamagitan ng paglikha ng isang variable na naglalaman ng host name sa pamamagitan ng pagdaragdag ng sumusunod na code bago likhain ang device client:

    ```python
    host_name = "<host_name>"
    ```

    Palitan ang `<host_name>` ng host name ng iyong IoT Hub. Makukuha mo ito mula sa seksyong `HostName` sa `connection_string`. Ito ang magiging pangalan ng iyong IoT Hub, na nagtatapos sa `.azure-devices.net`.

1. Sa ibaba nito, magdeklara ng isang variable na may device ID:

    ```python
    device_id = "soil-moisture-sensor-x509"
    ```

1. Kakailanganin mo ng instance ng `X509` class na naglalaman ng X.509 files. Idagdag ang `X509` sa listahan ng mga klase na ini-import mula sa `azure.iot.device` module:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse, X509
    ```

1. Gumawa ng instance ng `X509` class gamit ang iyong certificate at key files sa pamamagitan ng pagdaragdag ng code na ito sa ibaba ng deklarasyon ng `host_name`:

    ```python
    x509 = X509("./soil-moisture-sensor-x509-cert.pem", "./soil-moisture-sensor-x509-key.pem")
    ```

    Ito ay lilikha ng `X509` class gamit ang `soil-moisture-sensor-x509-cert.pem` at `soil-moisture-sensor-x509-key.pem` files na ginawa kanina.

1. Palitan ang linya ng code na lumilikha ng `device_client` mula sa connection string, gamit ang sumusunod:

    ```python
    device_client = IoTHubDeviceClient.create_from_x509_certificate(x509, host_name, device_id)
    ```

    Ito ay magkokonekta gamit ang X.509 certificate sa halip na connection string.

1. Tanggalin ang linya na may `connection_string` variable.

1. Patakbuhin ang iyong code. Subaybayan ang mga mensaheng ipinapadala sa IoT Hub, at magpadala ng direct method requests tulad ng dati. Makikita mo ang device na kumokonekta at nagpapadala ng soil moisture readings, pati na rin ang pagtanggap ng direct method requests.

> 💁 Makikita mo ang code na ito sa [code/pi](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/pi) o [code/virtual-device](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/virtual-device) folder.

😀 Ang iyong soil moisture sensor program ay nakakonekta na sa iyong IoT Hub gamit ang X.509 certificate!

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na dulot ng paggamit ng pagsasaling ito.