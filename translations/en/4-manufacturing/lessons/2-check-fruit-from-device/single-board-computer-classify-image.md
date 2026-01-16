<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "e5896207b304ce1abaf065b8acc0cc79",
  "translation_date": "2025-08-28T19:12:53+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/single-board-computer-classify-image.md",
  "language_code": "en"
}
-->
# Classify an image - Virtual IoT Hardware and Raspberry Pi

In this part of the lesson, you will send the image captured by the camera to the Custom Vision service for classification.

## Send images to Custom Vision

The Custom Vision service provides a Python SDK that you can use to classify images.

### Task - Send images to Custom Vision

1. Open the `fruit-quality-detector` folder in VS Code. If you are using a virtual IoT device, ensure the virtual environment is active in the terminal.

1. The Python SDK for sending images to Custom Vision is available as a Pip package. Install it using the following command:

    ```sh
    pip3 install azure-cognitiveservices-vision-customvision
    ```

1. Add the following import statements at the top of the `app.py` file:

    ```python
    from msrest.authentication import ApiKeyCredentials
    from azure.cognitiveservices.vision.customvision.prediction import CustomVisionPredictionClient
    ```

    These modules from the Custom Vision libraries allow you to authenticate using the prediction key and provide a prediction client class to interact with Custom Vision.

1. Add the following code to the end of the file:

    ```python
    prediction_url = '<prediction_url>'
    prediction_key = '<prediction key>'
    ```

    Replace `<prediction_url>` with the URL you copied from the *Prediction URL* dialog earlier in this lesson. Replace `<prediction key>` with the prediction key you copied from the same dialog.

1. The prediction URL provided by the *Prediction URL* dialog is formatted for direct REST endpoint calls. The Python SDK uses different parts of this URL separately. Add the following code to extract the necessary components:

    ```python
    parts = prediction_url.split('/')
    endpoint = 'https://' + parts[2]
    project_id = parts[6]
    iteration_name = parts[9]
    ```

    This code splits the URL to extract the endpoint `https://<location>.api.cognitive.microsoft.com`, the project ID, and the name of the published iteration.

1. Create a predictor object to perform the prediction using the following code:

    ```python
    prediction_credentials = ApiKeyCredentials(in_headers={"Prediction-key": prediction_key})
    predictor = CustomVisionPredictionClient(endpoint, prediction_credentials)
    ```

    The `prediction_credentials` encapsulate the prediction key, which is then used to create a prediction client object pointing to the endpoint.

1. Send the image to Custom Vision using the following code:

    ```python
    image.seek(0)
    results = predictor.classify_image(project_id, iteration_name, image)
    ```

    This rewinds the image to the beginning and sends it to the prediction client.

1. Finally, display the results using the following code:

    ```python
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    This loops through all the returned predictions and displays them in the terminal. The probabilities are floating-point numbers between 0 and 1, where 0 represents a 0% chance of matching the tag, and 1 represents a 100% chance.

    > 💁 Image classifiers return probabilities for all tags used. Each tag will have a probability indicating how closely the image matches that tag.

1. Run your code with your camera pointed at some fruit, an appropriate image set, or visible fruit on your webcam if using virtual IoT hardware. You will see the output in the console:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

    You will also see the captured image and these values in the **Predictions** tab in Custom Vision.

    ![A banana in custom vision predicted ripe at 56.8% and unripe at 43.1%](../../../../../translated_images/en/custom-vision-banana-prediction.30cdff4e1d72db5d9a0be0193790a47c2b387da034e12dc1314dd57ca2131b59.png)

> 💁 You can find this code in the [code-classify/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/pi) or [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/virtual-iot-device) folder.

😀 Your fruit quality classifier program was a success!

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we aim for accuracy, please note that automated translations may include errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is advised. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.