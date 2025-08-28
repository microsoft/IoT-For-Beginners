<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3ac42e284a7222c0e83d2d43231a364f",
  "translation_date": "2025-08-27T22:04:21+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/single-board-computer-connect-hub.md",
  "language_code": "tl"
}
-->
# Ikonekta ang iyong IoT device sa cloud - Virtual IoT Hardware at Raspberry Pi

Sa bahaging ito ng aralin, ikokonekta mo ang iyong virtual IoT device o Raspberry Pi sa iyong IoT Hub upang magpadala ng telemetry at tumanggap ng mga utos.

## Ikonekta ang iyong device sa IoT Hub

Ang susunod na hakbang ay ikonekta ang iyong device sa IoT Hub.

### Gawain - ikonekta sa IoT Hub

1. Buksan ang folder na `soil-moisture-sensor` sa VS Code. Siguraduhing tumatakbo ang virtual environment sa terminal kung gumagamit ka ng virtual IoT device.

1. Mag-install ng ilang karagdagang Pip packages:

    ```sh
    pip3 install azure-iot-device
    ```

    Ang `azure-iot-device` ay isang library para makipag-ugnayan sa iyong IoT Hub.

1. Idagdag ang sumusunod na imports sa itaas ng file na `app.py`, sa ibaba ng mga umiiral na imports:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse
    ```

    Ang code na ito ay nag-i-import ng SDK para makipag-ugnayan sa iyong IoT Hub.

1. Alisin ang linyang `import paho.mqtt.client as mqtt` dahil hindi na kailangan ang library na ito. Alisin ang lahat ng MQTT code kabilang ang mga pangalan ng topic, lahat ng code na gumagamit ng `mqtt_client` at ang `handle_command`. Panatilihin ang `while True:` loop, ngunit tanggalin ang linyang `mqtt_client.publish` mula sa loop na ito.

1. Idagdag ang sumusunod na code sa ibaba ng mga import statements:

    ```python
    connection_string = "<connection string>"
    ```

    Palitan ang `<connection string>` ng connection string na nakuha mo para sa device kanina sa araling ito.

    > 💁 Hindi ito ang pinakamahusay na kasanayan. Ang mga connection string ay hindi dapat itago sa source code, dahil maaaring ma-check in ito sa source code control at makita ng kahit sino. Ginagawa natin ito dito para sa layunin ng pagiging simple. Sa ideal na sitwasyon, dapat kang gumamit ng isang bagay tulad ng environment variable at isang tool tulad ng [`python-dotenv`](https://pypi.org/project/python-dotenv/). Matututuhan mo pa ito sa susunod na aralin.

1. Sa ibaba ng code na ito, idagdag ang sumusunod upang lumikha ng isang device client object na maaaring makipag-ugnayan sa IoT Hub, at ikonekta ito:

    ```python
    device_client = IoTHubDeviceClient.create_from_connection_string(connection_string)

    print('Connecting')
    device_client.connect()
    print('Connected')
    ```

1. Patakbuhin ang code na ito. Makikita mong nakakonekta ang iyong device.

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Connecting
    Connected
    Soil moisture: 379
    ```

## Magpadala ng telemetry

Ngayon na nakakonekta na ang iyong device, maaari kang magpadala ng telemetry sa IoT Hub sa halip na sa MQTT broker.

### Gawain - magpadala ng telemetry

1. Idagdag ang sumusunod na code sa loob ng `while True` loop, bago ang sleep:

    ```python
    message = Message(json.dumps({ 'soil_moisture': soil_moisture }))
    device_client.send_message(message)
    ```

    Ang code na ito ay lumilikha ng isang IoT Hub `Message` na naglalaman ng soil moisture reading bilang isang JSON string, pagkatapos ay ipinapadala ito sa IoT Hub bilang isang device-to-cloud message.

## Mag-handle ng mga utos

Kailangang mag-handle ng iyong device ng isang utos mula sa server code upang kontrolin ang relay. Ang utos na ito ay ipinapadala bilang isang direct method request.

## Gawain - mag-handle ng direct method request

1. Idagdag ang sumusunod na code bago ang `while True` loop:

    ```python
    def handle_method_request(request):
        print("Direct method received - ", request.name)
    
        if request.name == "relay_on":
            relay.on()
        elif request.name == "relay_off":
            relay.off()    
    ```

    Ang code na ito ay nagde-define ng isang method, `handle_method_request`, na tatawagin kapag may direct method na tinawag ng IoT Hub. Ang bawat direct method ay may pangalan, at inaasahan ng code na ito ang isang method na tinatawag na `relay_on` upang i-on ang relay, at `relay_off` upang i-off ito.

    > 💁 Maaari rin itong ipatupad sa isang solong direct method request, na ipinapasa ang nais na estado ng relay sa isang payload na maaaring ipasa kasama ng method request at makukuha mula sa `request` object.

1. Ang mga direct method ay nangangailangan ng response upang ipaalam sa tumatawag na code na na-handle na ang mga ito. Idagdag ang sumusunod na code sa dulo ng function na `handle_method_request` upang lumikha ng response sa request:

    ```python
    method_response = MethodResponse.create_from_method_request(request, 200)
    device_client.send_method_response(method_response)
    ```

    Ang code na ito ay nagpapadala ng response sa direct method request na may HTTP status code na 200, at ipinapadala ito pabalik sa IoT Hub.

1. Idagdag ang sumusunod na code sa ibaba ng definition ng function na ito:

    ```python
    device_client.on_method_request_received = handle_method_request
    ```

    Ang code na ito ay nagsasabi sa IoT Hub client na tawagin ang function na `handle_method_request` kapag may direct method na tinawag.

> 💁 Makikita mo ang code na ito sa [code/pi](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/pi) o [code/virtual-device](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/virtual-device) folder.

😀 Ang iyong soil moisture sensor program ay nakakonekta na sa iyong IoT Hub!

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na dulot ng paggamit ng pagsasaling ito.