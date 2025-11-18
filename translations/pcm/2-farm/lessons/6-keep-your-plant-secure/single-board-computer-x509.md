<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9aea84bcc7520222b0e1c50469d62d6a",
  "translation_date": "2025-11-18T19:45:55+00:00",
  "source_file": "2-farm/lessons/6-keep-your-plant-secure/single-board-computer-x509.md",
  "language_code": "pcm"
}
-->
# Use di X.509 certificate for your device code - Virtual IoT Hardware and Raspberry Pi

For dis part of di lesson, you go connect your virtual IoT device or Raspberry Pi to your IoT Hub wit di X.509 certificate.

## Connect your device to IoT Hub

Di next step na to connect your device to IoT Hub wit di X.509 certificates.

### Task - connect to IoT Hub

1. Copy di key and certificate files go di folder wey get your IoT device code. If you dey use Raspberry Pi through VS Code Remote SSH and you create di keys for your PC or Mac, you fit drag and drop di files enter di explorer for VS Code to copy dem.

1. Open di `app.py` file

1. To connect wit X.509 certificate, you go need di host name of di IoT Hub, and di X.509 certificate. Start by creating one variable wey go hold di host name by adding dis code before you create di device client:

    ```python
    host_name = "<host_name>"
    ```

    Replace `<host_name>` wit di host name of your IoT Hub. You fit find am for di `HostName` section inside di `connection_string`. E go be di name of your IoT Hub, wey go end wit `.azure-devices.net`

1. Under dis one, declare one variable wey go hold di device ID:

    ```python
    device_id = "soil-moisture-sensor-x509"
    ```

1. You go need one instance of di `X509` class wey go hold di X.509 files. Add `X509` to di list of classes wey you dey import from di `azure.iot.device` module:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse, X509
    ```

1. Create one `X509` class instance wey go use your certificate and key files by adding dis code under di `host_name` declaration:

    ```python
    x509 = X509("./soil-moisture-sensor-x509-cert.pem", "./soil-moisture-sensor-x509-key.pem")
    ```

    Dis one go create di `X509` class using di `soil-moisture-sensor-x509-cert.pem` and `soil-moisture-sensor-x509-key.pem` files wey you don create before.

1. Replace di line of code wey dey create di `device_client` from connection string, wit dis one:

    ```python
    device_client = IoTHubDeviceClient.create_from_x509_certificate(x509, host_name, device_id)
    ```

    Dis one go connect using di X.509 certificate instead of connection string.
    
1. Delete di line wey get `connection_string` variable.

1. Run your code. Dey monitor di messages wey di device dey send go IoT Hub, and dey send direct method requests like before. You go see say di device don connect and e dey send soil moisture readings, plus e dey receive direct method requests.

> 💁 You fit find dis code for di [code/pi](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/pi) or [code/virtual-device](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/virtual-device) folder.

😀 Your soil moisture sensor program don connect to your IoT Hub wit X.509 certificate!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Disclaimer**:  
Dis dokyument don use AI transle-shon service [Co-op Translator](https://github.com/Azure/co-op-translator) do di transle-shon. Even as we dey try make am accurate, abeg make you sabi say transle-shon wey machine do fit get mistake or no dey correct well. Di original dokyument for di language wey dem take write am first na di one wey you go take as di correct source. For important mata, e good make you use professional human transle-shon. We no go fit take blame for any misunderstanding or wrong interpretation wey fit happen because you use dis transle-shon.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->