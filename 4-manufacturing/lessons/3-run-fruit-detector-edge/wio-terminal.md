# Classify an image using an IoT Edge based image classifier - Wio Terminal

In this part of the lesson, you will use the Image Classifier running on the IoT Edge device.

## Use the IoT Edge classifier

The IoT device can be re-directed to use the IoT Edge image classifier. The URL for the Image Classifier is `http://<IP address or name>/image`, replacing `<IP address or name>` with the IP address or host name of the computer running IoT Edge.

### Task - use the IoT Edge classifier

1. Open the `fruit-quality-detector` app project if it's not already open.

1. The image classifier is running as a REST API using HTTP, not HTTPS, so the call needs to use a WiFi client that works with HTTP calls only. This means the certificate is not needed. Delete the `CERTIFICATE` from the `config.h` file.

1. The prediction URL in the `config.h` file needs to be updated to the new URL. You can also delete the `PREDICTION_KEY` as this is not needed.

    ```cpp
    const char *PREDICTION_URL = "<URL>";
    ```

    Replace `<URL>` with the URL for your classifier.

1. In `main.cpp`, change the include directive for the WiFi Client Secure to import the standard HTTP version:

    ```cpp
    #include <WiFiClient.h>
    ```

1. Change the declaration of `WiFiClient` to be the HTTP version:

    ```cpp
    WiFiClient client;
    ```

1. Select the line that sets the certificate on the WiFi client. Remove the line `client.setCACert(CERTIFICATE);` from the `connectWiFi` function.

1. In the `classifyImage` function, remove the `httpClient.addHeader("Prediction-Key", PREDICTION_KEY);` line that sets the prediction key in the header.

1. Upload and run your code. Point the camera at some fruit and press the C button. You will see the output in the serial monitor:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 You can find this code in the [code-classify/wio-terminal](code-classify/wio-terminal) folder.

😀 Your fruit quality classifier program was a success!
