<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "50151d9f9dce2801348a93880ef16d86",
  "translation_date": "2025-08-28T19:07:47+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/single-board-computer.md",
  "language_code": "en"
}
-->
# Classify an image using an IoT Edge-based image classifier - Virtual IoT Hardware and Raspberry Pi

In this part of the lesson, you will use the Image Classifier running on the IoT Edge device.

## Use the IoT Edge classifier

The IoT device can be configured to use the IoT Edge image classifier. The URL for the Image Classifier is `http://<IP address or name>/image`, where `<IP address or name>` should be replaced with the IP address or host name of the computer running IoT Edge.

The Python library for Custom Vision only supports cloud-hosted models, not models hosted on IoT Edge. Therefore, you will need to use the REST API to interact with the classifier.

### Task - use the IoT Edge classifier

1. Open the `fruit-quality-detector` project in VS Code if it is not already open. If you are using a virtual IoT device, ensure the virtual environment is activated.

1. Open the `app.py` file, and remove the import statements from `azure.cognitiveservices.vision.customvision.prediction` and `msrest.authentication`.

1. Add the following import at the top of the file:

    ```python
    import requests
    ```

1. Delete all the code after the image is saved to a file, starting from `image_file.write(image.read())` to the end of the file.

1. Add the following code to the end of the file:

    ```python
    prediction_url = '<URL>'
    headers = {
        'Content-Type' : 'application/octet-stream'
    }
    image.seek(0)
    response = requests.post(prediction_url, headers=headers, data=image)
    results = response.json()
    
    for prediction in results['predictions']:
        print(f'{prediction["tagName"]}:\t{prediction["probability"] * 100:.2f}%')
    ```

    Replace `<URL>` with the URL for your classifier.

    This code sends a REST POST request to the classifier, with the image included as the body of the request. The response is returned as JSON, which is then decoded to display the probabilities.

1. Run your code, pointing your camera at some fruit, using an appropriate image set, or ensuring fruit is visible on your webcam if you are using virtual IoT hardware. The output will appear in the console:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 You can find this code in the [code-classify/pi](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/pi) or [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/virtual-iot-device) folder.

😀 Your fruit quality classifier program worked successfully!

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we aim for accuracy, please note that automated translations may include errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is advised. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.