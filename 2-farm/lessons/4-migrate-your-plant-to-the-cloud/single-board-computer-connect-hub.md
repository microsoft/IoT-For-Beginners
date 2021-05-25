# Connect your IoT device to the cloud - Virtual IoT Hardware and Raspberry Pi

In this part of the lesson, you will connect your virtual IoT device or Raspberry Pi to your IoT Hub, to send telemetry and receive commands.

## Connect your device to IoT Hub

The next step is to connect your device to IoT Hub.

### Task - connect to IoT Hub

1. Open the `soil-moisture-sensor` folder in VS Code. Make sure the virtual environment is running in the terminal if you are using a virtual IoT device.

1. Install some additional Pip packages:

    ```sh
    pip3 install azure-iot-device
    ```

    `azure-iot-device` is a library to communicate with your IoT Hub.

1. Add the following imports to the top of the `app.py` file, below the existing imports:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse
    ```

    This code imports the SDK to communicate with your IoT Hub.

1. Remove the `import paho.mqtt.client as mqtt` line as this library is no longer needed. Remove all the MQTT code including the topic names, all code that uses `mqtt_client` and the `handle_command`. Keep the `while True:` loop, just delete the `mqtt_client.publish` line form this loop.

1. Add the following code below the import statements:

    ```python
    connection_string = "<connection string>"
    ```

    Replace `<connection string>` with the connection string you retrieved for the device earlier in this lesson.

    > 💁 This is not best practice. Connection strings should never be stored in source code, as this can be checked into source code control and found by anyone. We are doing this here for the sake of simplicity. Ideally you should use something like an environment variable and a tool like [`python-dotenv`](https://pypi.org/project/python-dotenv/). You will learn more about this in an upcoming lesson.

1. Below this code, add the following to create a device client object that can communicate with IoT Hub, and connect it:

    ```python
    device_client = IoTHubDeviceClient.create_from_connection_string(connection_string)

    print("Connecting")
    device_client.connect()
    print("Connected")
    ```

1. Run this code. You will see your device connect.

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Connecting
    Connected
    Soil moisture: 379
    ```

## Send telemetry

Now that your device is connected, you can send telemetry to the IoT Hub instead of the MQTT broker.

### Task - send telemetry

1. Add the following code inside the `while True` loop, just before the sleep:

    ```python
    message = Message(json.dumps({ "soil_moisture": soil_moisture }))
    device_client.send_message(message)
    ```

    This code creates an IoT Hub `Message` containing the soil moisture reading as a JSON string, then sends this to the IoT Hub as a device to cloud message.

## Handle commands

Your device needs to handle a command from the server code to control the relay. This is sent as a direct method request.

## Task - handle a direct method request

1. Add the following code before the `while True` loop:

    ```python
    def handle_method_request(request):
        print("Direct method received - ", request.name)
    
        if request.name == "relay_on":
            relay.on()
        elif request.name == "relay_off":
            relay.off()    
    ```

    This defines a method, `handle_method_request`, that will be called when a direct method is called by the IoT Hub. Each direct method has a name, and this code expects a method called `relay_on` to turn the relay on, and `relay_off` to turn the relay off.

    > 💁 This could also be implemented in a single direct method request, passing the desired state of the relay in a payload that can be passed with the method request and available from the `request` object.

1. Direct methods require a response to tell the calling code that they have been handled. Add the following code at the end of the `handle_method_request` function to create a response to the request:

    ```python
    method_response = MethodResponse.create_from_method_request(request, 200)
    device_client.send_method_response(method_response)
    ```

    This code sends a response to the direct method request with an HTTP status code of 200, and sends this back to the IoT Hub.

1. Add the following code below this function definition:

    ```python
    device_client.on_method_request_received = handle_method_request
    ```

    This code tells the IoT Hub client to call the `handle_method_request` function when a direct method is called.

> 💁 You can find this code in the [code/pi](code/pi) or [code/virtual-device](code/virtual-device) folder.

😀 Your soil moisture sensor program is connected to your IoT Hub!
