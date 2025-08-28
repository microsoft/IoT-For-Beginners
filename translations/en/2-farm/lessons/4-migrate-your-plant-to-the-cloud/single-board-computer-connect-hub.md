<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3ac42e284a7222c0e83d2d43231a364f",
  "translation_date": "2025-08-28T20:33:39+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/single-board-computer-connect-hub.md",
  "language_code": "en"
}
-->
# Connect your IoT device to the cloud - Virtual IoT Hardware and Raspberry Pi

In this part of the lesson, you will connect your virtual IoT device or Raspberry Pi to your IoT Hub to send telemetry data and receive commands.

## Connect your device to IoT Hub

The next step is to connect your device to the IoT Hub.

### Task - Connect to IoT Hub

1. Open the `soil-moisture-sensor` folder in VS Code. If you are using a virtual IoT device, ensure the virtual environment is running in the terminal.

1. Install some additional Pip packages:

    ```sh
    pip3 install azure-iot-device
    ```

    `azure-iot-device` is a library used to communicate with your IoT Hub.

1. Add the following imports to the top of the `app.py` file, just below the existing imports:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse
    ```

    This code imports the SDK needed to communicate with your IoT Hub.

1. Remove the `import paho.mqtt.client as mqtt` line, as this library is no longer required. Delete all the MQTT-related code, including the topic names, any code that uses `mqtt_client`, and the `handle_command` function. Keep the `while True:` loop, but remove the `mqtt_client.publish` line from this loop.

1. Add the following code below the import statements:

    ```python
    connection_string = "<connection string>"
    ```

    Replace `<connection string>` with the connection string you retrieved for the device earlier in this lesson.

    > 💁 This is not a best practice. Connection strings should never be stored in source code, as they can be checked into source control and accessed by others. We are doing this here for simplicity. Ideally, you should use something like an environment variable and a tool like [`python-dotenv`](https://pypi.org/project/python-dotenv/). You will learn more about this in a future lesson.

1. Below this code, add the following to create a device client object that can communicate with the IoT Hub and connect it:

    ```python
    device_client = IoTHubDeviceClient.create_from_connection_string(connection_string)

    print('Connecting')
    device_client.connect()
    print('Connected')
    ```

1. Run this code. You will see your device connect.

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Connecting
    Connected
    Soil moisture: 379
    ```

## Send telemetry

Now that your device is connected, you can send telemetry data to the IoT Hub instead of the MQTT broker.

### Task - Send telemetry

1. Add the following code inside the `while True` loop, just before the sleep statement:

    ```python
    message = Message(json.dumps({ 'soil_moisture': soil_moisture }))
    device_client.send_message(message)
    ```

    This code creates an IoT Hub `Message` containing the soil moisture reading as a JSON string, then sends it to the IoT Hub as a device-to-cloud message.

## Handle commands

Your device needs to handle commands from the server code to control the relay. These commands are sent as direct method requests.

### Task - Handle a direct method request

1. Add the following code before the `while True` loop:

    ```python
    def handle_method_request(request):
        print("Direct method received - ", request.name)
    
        if request.name == "relay_on":
            relay.on()
        elif request.name == "relay_off":
            relay.off()    
    ```

    This defines a method, `handle_method_request`, which will be called when a direct method is invoked by the IoT Hub. Each direct method has a name, and this code expects a method called `relay_on` to turn the relay on, and `relay_off` to turn the relay off.

    > 💁 This could also be implemented as a single direct method request, passing the desired state of the relay in a payload that can be included with the method request and accessed from the `request` object.

1. Direct methods require a response to indicate that they have been handled. Add the following code at the end of the `handle_method_request` function to create a response to the request:

    ```python
    method_response = MethodResponse.create_from_method_request(request, 200)
    device_client.send_method_response(method_response)
    ```

    This code sends a response to the direct method request with an HTTP status code of 200 and sends it back to the IoT Hub.

1. Add the following code below this function definition:

    ```python
    device_client.on_method_request_received = handle_method_request
    ```

    This code tells the IoT Hub client to call the `handle_method_request` function whenever a direct method is invoked.

> 💁 You can find this code in the [code/pi](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/pi) or [code/virtual-device](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/virtual-device) folder.

😀 Your soil moisture sensor program is now connected to your IoT Hub!

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we aim for accuracy, please note that automated translations may include errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is advised. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.