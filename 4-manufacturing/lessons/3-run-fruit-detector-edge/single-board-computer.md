# Classify an image using an IoT Edge based image classifier - Virtual IoT Hardware and Raspberry Pi

In this part of the lesson, you will use the Image Classifier running on the IoT Edge device.

## Use the IoT Edge classifier

The IoT device can be re-directed to use the IoT Edge image classifier. The URL for the Image Classifier is `http://<IP address or name>/image`, replacing `<IP address or name>` with the IP address or host name of the computer running IoT Edge.

The Python library for Custom Vision only works with cloud-hosted models, not models hosted on IoT Edge. This means you will need to use the REST API to call the classifier.

### Task - use the IoT Edge classifier

1. Open the `fruit-quality-detector` project in VS Code if it is not already open. If you are using a virtual IoT device, then make sure the virtual environment is activated.

1. Open the `app.py` file, and remove the import statements from `azure.cognitiveservices.vision.customvision.prediction` and `msrest.authentication`.

1. Add the following import at the top of the file:

    ```python
    import requests
    ```

1. Delete all the code after the image is saved to a file, from `image_file.write(image.read())` to the end of the file.

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

    This code makes a REST POST request to the classifier, sending the image as the body of the request. The results come back as JSON, and this is decoded to print out the probabilities.

1. Run your code, with your camera pointing at some fruit, or an appropriate image set, or fruit visible on your webcam if using virtual IoT hardware. You will see the output in the console:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 You can find this code in the [code-classify/pi](code-classify/pi) or [code-classify/virtual-iot-device](code-classify/virtual-iot-device) folder.

😀 Your fruit quality classifier program was a success!
