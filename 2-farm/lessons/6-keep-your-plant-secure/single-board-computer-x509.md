# Use the X.509 certificate in your device code - Virtual IoT Hardware and Raspberry Pi

In this part of the lesson, you will connect your virtual IoT device or Raspberry Pi to your IoT Hub using the X.509 certificate.

## Connect your device to IoT Hub

The next step is to connect your device to IoT Hub using the X.509 certificates.

### Task - connect to IoT Hub

1. Copy the key and certificate files to the folder containing your IoT device code. If you are using a Raspberry Pi through VS Code Remote SSH and created the keys on your PC or Mac, you can drag and drop the files into the explorer in VS Code to copy them.

1. Open the `app.py` file

1. To connect using an X.509 certificate, you will need the host name of the IoT Hub, and the X.509 certificate. Start by creating a variable containing the host name by adding the following code before the device client is created:

    ```python
    host_name = "<host_name>"
    ```

    Replace `<host_name>` with your IoT Hub's host name. You can get this from the `HostName` section in the `connection_string`. It will be the name of your IoT Hub, ending with `.azure-devices.net`

1. Below this, declare a variable with the device ID:

    ```python
    device_id = "soil-moisture-sensor-x509"
    ```

1. You will need an instance of the `X509` class containing the X.509 files. Add `X509` to the list of classes imported from the `azure.iot.device` module:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse, X509
    ```

1. Create an `X509` class instance using your certificate and key files by adding this code below the `host_name` declaration:

    ```python
    x509 = X509("./soil-moisture-sensor-x509-cert.pem", "./soil-moisture-sensor-x509-key.pem")
    ```

    This will create the `X509` class using the `soil-moisture-sensor-x509-cert.pem` and `soil-moisture-sensor-x509-key.pem` files created earlier.

1. Replace the line of code that creates the `device_client` from a connection string, with the following:

    ```python
    device_client = IoTHubDeviceClient.create_from_x509_certificate(x509, host_name, device_id)
    ```

    This will connect using the X.509 certificate instead of a connection string.

1, RUn your code. Monitor the messages sent to IoT Hub, and send direct method requests as before. You will see the device connecting and sending soil moisture readings, as well as receiving direct method requests.

> 💁 You can find this code in the [code/pi](code/pi) or [code/virtual-device](code/virtual-device) folder.

😀 Your soil moisture sensor program is connected to your IoT Hub using an X.509 certificate!
