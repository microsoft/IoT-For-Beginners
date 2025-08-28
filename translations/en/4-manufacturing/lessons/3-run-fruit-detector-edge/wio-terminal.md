<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "48ac21ec80329c930db7b84bd6b592ec",
  "translation_date": "2025-08-28T19:08:12+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/wio-terminal.md",
  "language_code": "en"
}
-->
# Classify an image using an IoT Edge based image classifier - Wio Terminal

In this part of the lesson, you will use the Image Classifier running on the IoT Edge device.

## Use the IoT Edge classifier

The IoT device can be configured to use the IoT Edge image classifier. The URL for the Image Classifier is `http://<IP address or name>/image`, where `<IP address or name>` should be replaced with the IP address or host name of the computer running IoT Edge.

### Task - use the IoT Edge classifier

1. Open the `fruit-quality-detector` app project if it’s not already open.

1. The image classifier operates as a REST API using HTTP, not HTTPS, so the call must use a WiFi client that supports HTTP calls only. This means the certificate is not required. Remove the `CERTIFICATE` from the `config.h` file.

1. Update the prediction URL in the `config.h` file to the new URL. You can also remove the `PREDICTION_KEY` as it is not needed.

    ```cpp
    const char *PREDICTION_URL = "<URL>";
    ```

    Replace `<URL>` with the URL for your classifier.

1. In `main.cpp`, modify the include directive for the WiFi Client Secure to import the standard HTTP version:

    ```cpp
    #include <WiFiClient.h>
    ```

1. Update the declaration of `WiFiClient` to use the HTTP version:

    ```cpp
    WiFiClient client;
    ```

1. Locate the line that sets the certificate on the WiFi client. Remove the line `client.setCACert(CERTIFICATE);` from the `connectWiFi` function.

1. In the `classifyImage` function, delete the line `httpClient.addHeader("Prediction-Key", PREDICTION_KEY);` that sets the prediction key in the header.

1. Upload and run your code. Point the camera at a piece of fruit and press the C button. You will see the output in the serial monitor:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 You can find this code in the [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/wio-terminal) folder.

😀 Your fruit quality classifier program worked perfectly!

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we aim for accuracy, please note that automated translations may include errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is advised. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.