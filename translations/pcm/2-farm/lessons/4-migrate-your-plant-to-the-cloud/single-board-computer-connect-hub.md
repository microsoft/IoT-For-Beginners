<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3ac42e284a7222c0e83d2d43231a364f",
  "translation_date": "2025-11-18T19:36:41+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/single-board-computer-connect-hub.md",
  "language_code": "pcm"
}
-->
# Connect your IoT device to di cloud - Virtual IoT Hardware and Raspberry Pi

For dis part of di lesson, you go connect your virtual IoT device or Raspberry Pi to your IoT Hub, so e fit dey send telemetry and receive commands.

## Connect your device to IoT Hub

Di next step na to connect your device to IoT Hub.

### Task - connect to IoT Hub

1. Open di `soil-moisture-sensor` folder for VS Code. Make sure say di virtual environment dey run for di terminal if you dey use virtual IoT device.

1. Install some extra Pip packages:

    ```sh
    pip3 install azure-iot-device
    ```

    `azure-iot-device` na library wey go help you communicate with your IoT Hub.

1. Add di imports wey dey below to di top of di `app.py` file, under di imports wey dey already:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse
    ```

    Dis code go import di SDK wey go help you communicate with your IoT Hub.

1. Remove di `import paho.mqtt.client as mqtt` line because we no need dis library again. Remove all di MQTT code including di topic names, all di code wey dey use `mqtt_client` and di `handle_command`. Make sure say you keep di `while True:` loop, just delete di `mqtt_client.publish` line wey dey inside dis loop.

1. Add di code wey dey below under di import statements:

    ```python
    connection_string = "<connection string>"
    ```

    Replace `<connection string>` with di connection string wey you collect for di device earlier for dis lesson.

    > 💁 Dis no be di best way to do am. Connection strings no suppose dey inside source code because e fit enter source code control and anybody fit see am. We dey do am like dis for now to make am simple. Normally, you suppose use something like environment variable and tool like [`python-dotenv`](https://pypi.org/project/python-dotenv/). You go learn more about dis one for di next lesson.

1. Under dis code, add di code wey dey below to create device client object wey fit communicate with IoT Hub, and connect am:

    ```python
    device_client = IoTHubDeviceClient.create_from_connection_string(connection_string)

    print('Connecting')
    device_client.connect()
    print('Connected')
    ```

1. Run dis code. You go see say your device don connect.

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Connecting
    Connected
    Soil moisture: 379
    ```

## Send telemetry

Now wey your device don connect, you fit dey send telemetry go IoT Hub instead of di MQTT broker.

### Task - send telemetry

1. Add di code wey dey below inside di `while True` loop, just before di sleep:

    ```python
    message = Message(json.dumps({ 'soil_moisture': soil_moisture }))
    device_client.send_message(message)
    ```

    Dis code go create IoT Hub `Message` wey get di soil moisture reading as JSON string, then e go send am go IoT Hub as device to cloud message.

## Handle commands

Your device need to handle command wey di server code go send to control di relay. Dis one dey sent as direct method request.

## Task - handle a direct method request

1. Add di code wey dey below before di `while True` loop:

    ```python
    def handle_method_request(request):
        print("Direct method received - ", request.name)
    
        if request.name == "relay_on":
            relay.on()
        elif request.name == "relay_off":
            relay.off()    
    ```

    Dis one dey define method, `handle_method_request`, wey go run when direct method dey called by IoT Hub. Each direct method get name, and dis code dey expect method wey dem call `relay_on` to turn di relay on, and `relay_off` to turn di relay off.

    > 💁 You fit also do dis one for one direct method request, by passing di state wey you want for di relay inside payload wey fit dey passed with di method request and dey available from di `request` object.

1. Direct methods need response to show di calling code say dem don handle am. Add di code wey dey below for di end of di `handle_method_request` function to create response for di request:

    ```python
    method_response = MethodResponse.create_from_method_request(request, 200)
    device_client.send_method_response(method_response)
    ```

    Dis code dey send response to di direct method request with HTTP status code of 200, and e go send am back to IoT Hub.

1. Add di code wey dey below under dis function definition:

    ```python
    device_client.on_method_request_received = handle_method_request
    ```

    Dis code dey tell di IoT Hub client to call di `handle_method_request` function when direct method dey called.

> 💁 You fit find dis code for di [code/pi](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/pi) or [code/virtual-device](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/virtual-device) folder.

😀 Your soil moisture sensor program don connect to your IoT Hub!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Disclaimer**:  
Dis dokyument don use AI transleto service [Co-op Translator](https://github.com/Azure/co-op-translator) do di translation. Even as we dey try make am accurate, abeg sabi say machine translation fit get mistake or no dey correct well. Di original dokyument wey dey for im native language na di main source wey you go trust. For important mata, e good make professional human transleto check am. We no go fit take blame for any misunderstanding or wrong interpretation wey fit happen because you use dis translation.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->