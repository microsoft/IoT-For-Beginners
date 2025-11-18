<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "50151d9f9dce2801348a93880ef16d86",
  "translation_date": "2025-11-18T18:49:16+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/single-board-computer.md",
  "language_code": "pcm"
}
-->
# Classify one image wit IoT Edge image classifier - Virtual IoT Hardware and Raspberry Pi

For dis part of di lesson, you go use di Image Classifier wey dey run for IoT Edge device.

## Use di IoT Edge classifier

Di IoT device fit redirect am to use di IoT Edge image classifier. Di URL for di Image Classifier na `http://<IP address or name>/image`, replace `<IP address or name>` wit di IP address or host name of di computer wey dey run IoT Edge.

Di Python library for Custom Vision dey work only wit models wey dey cloud, e no dey work wit models wey dey IoT Edge. Dis one mean say you go need use di REST API to call di classifier.

### Task - use di IoT Edge classifier

1. Open di `fruit-quality-detector` project for VS Code if e never open. If you dey use virtual IoT device, make sure say di virtual environment don activate.

1. Open di `app.py` file, and commot di import statements from `azure.cognitiveservices.vision.customvision.prediction` and `msrest.authentication`.

1. Add dis import for di top of di file:

    ```python
    import requests
    ```

1. Delete all di code after di image don save for file, from `image_file.write(image.read())` go reach di end of di file.

1. Add dis code for di end of di file:

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

    Replace `<URL>` wit di URL for your classifier.

    Dis code go make REST POST request to di classifier, e go send di image as di body of di request. Di results go come back as JSON, and e go decode am to show di probabilities.

1. Run your code, make your camera dey point to some fruit, or use correct image set, or fruit wey dey visible for your webcam if you dey use virtual IoT hardware. You go see di output for di console:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 You fit find dis code for di [code-classify/pi](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/pi) or [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/virtual-iot-device) folder.

😀 Your fruit quality classifier program don work well!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Disclaimer**:  
Dis dokyument don use AI transle-shon service [Co-op Translator](https://github.com/Azure/co-op-translator) do di transle-shon. Even as we dey try make am correct, abeg make you sabi say machine transle-shon fit get mistake or no dey accurate well. Di original dokyument for im native language na di one wey you go take as di correct source. For important mata, e good make you use professional human transle-shon. We no go fit take blame for any misunderstanding or wrong interpretation wey fit happen because you use dis transle-shon.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->