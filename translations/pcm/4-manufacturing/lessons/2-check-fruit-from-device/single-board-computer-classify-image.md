<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "e5896207b304ce1abaf065b8acc0cc79",
  "translation_date": "2025-11-18T18:56:20+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/single-board-computer-classify-image.md",
  "language_code": "pcm"
}
-->
# Classify image - Virtual IoT Hardware and Raspberry Pi

For dis part of di lesson, you go send di image wey di camera capture go Custom Vision service to classify am.

## Send images go Custom Vision

Di Custom Vision service get Python SDK wey you fit use to classify images.

### Task - send images go Custom Vision

1. Open di `fruit-quality-detector` folder for VS Code. If you dey use virtual IoT device, make sure say di virtual environment dey run for di terminal.

1. Di Python SDK wey dey send images go Custom Vision dey available as Pip package. Install am with dis command:

    ```sh
    pip3 install azure-cognitiveservices-vision-customvision
    ```

1. Add dis import statements for di top of di `app.py` file:

    ```python
    from msrest.authentication import ApiKeyCredentials
    from azure.cognitiveservices.vision.customvision.prediction import CustomVisionPredictionClient
    ```

    Dis one go bring some modules from di Custom Vision libraries, one to authenticate with di prediction key, and one to provide prediction client class wey fit call Custom Vision.

1. Add dis code for di end of di file:

    ```python
    prediction_url = '<prediction_url>'
    prediction_key = '<prediction key>'
    ```

    Change `<prediction_url>` to di URL wey you copy from di *Prediction URL* dialog before for dis lesson. Change `<prediction key>` to di prediction key wey you copy from di same dialog.

1. Di prediction URL wey di *Prediction URL* dialog provide dey designed to use when you dey call di REST endpoint directly. Di Python SDK dey use parts of di URL for different places. Add dis code to break di URL into di parts wey dem need:

    ```python
    parts = prediction_url.split('/')
    endpoint = 'https://' + parts[2]
    project_id = parts[6]
    iteration_name = parts[9]
    ```

    Dis one go split di URL, extract di endpoint of `https://<location>.api.cognitive.microsoft.com`, di project ID, and di name of di published iteration.

1. Create predictor object to do di prediction with dis code:

    ```python
    prediction_credentials = ApiKeyCredentials(in_headers={"Prediction-key": prediction_key})
    predictor = CustomVisionPredictionClient(endpoint, prediction_credentials)
    ```

    Di `prediction_credentials` dey wrap di prediction key. Dem go use am to create prediction client object wey dey point to di endpoint.

1. Send di image go Custom Vision with dis code:

    ```python
    image.seek(0)
    results = predictor.classify_image(project_id, iteration_name, image)
    ```

    Dis one go rewind di image back to di start, then send am go di prediction client.

1. Finally, show di results with dis code:

    ```python
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Dis one go loop through all di predictions wey dem return and show dem for di terminal. Di probabilities wey dem return na floating point numbers from 0-1, wey 0 mean 0% chance say e match di tag, and 1 mean 100% chance.

    > 💁 Image classifiers go return di percentages for all di tags wey dem use. Each tag go get probability say di image match di tag.

1. Run your code, make your camera dey point to some fruit, or image set wey dey appropriate, or fruit wey dey visible for your webcam if you dey use virtual IoT hardware. You go see di output for di console:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

    You go fit see di image wey dem take, and dis values for di **Predictions** tab for Custom Vision.

    ![Banana for custom vision wey dem predict ripe at 56.8% and unripe at 43.1%](../../../../../translated_images/custom-vision-banana-prediction.30cdff4e1d72db5d9a0be0193790a47c2b387da034e12dc1314dd57ca2131b59.pcm.png)

> 💁 You fit find dis code for di [code-classify/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/pi) or [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/virtual-iot-device) folder.

😀 Your fruit quality classifier program work well!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Disclaimer**:  
Dis dokyument don translate wit AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). Even though we dey try make am accurate, abeg sabi say machine translation fit get mistake or no dey correct well. Di original dokyument for im native language na di main source wey you go fit trust. For important information, e good make professional human translator check am. We no go fit take blame for any misunderstanding or wrong interpretation wey fit happen because you use dis translation.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->