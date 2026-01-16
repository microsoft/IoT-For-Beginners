<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a3fdfec1d1e2cb645ea11c2930b51299",
  "translation_date": "2025-08-28T20:17:47+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/single-board-computer-object-detector.md",
  "language_code": "en"
}
-->
# Call your object detector from your IoT device - Virtual IoT Hardware and Raspberry Pi

Once your object detector has been published, it can be used from your IoT device.

## Copy the image classifier project

Most of your stock detector will be based on the image classifier you created in a previous lesson.

### Task - Copy the image classifier project

1. Create a folder called `stock-counter` either on your computer if you are using a virtual IoT device, or on your Raspberry Pi. If you are using a virtual IoT device, make sure you set up a virtual environment.

1. Set up the camera hardware.

    * If you are using a Raspberry Pi, you will need to attach the PiCamera. You might also want to secure the camera in a fixed position, for example, by hanging the cable over a box or can, or attaching the camera to a box with double-sided tape.
    * If you are using a virtual IoT device, you will need to install CounterFit and the CounterFit PyCamera shim. If you plan to use still images, capture some images that your object detector hasn’t seen yet. If you plan to use your webcam, make sure it is positioned to clearly view the stock you are detecting.

1. Follow the steps from [lesson 2 of the manufacturing project](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) to capture images from the camera.

1. Follow the steps from [lesson 2 of the manufacturing project](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) to call the image classifier. Most of this code will be reused to detect objects.

## Change the code from a classifier to an image detector

The code you used to classify images is very similar to the code used to detect objects. The main difference lies in the method called on the Custom Vision SDK and the results of the call.

### Task - Change the code from a classifier to an image detector

1. Delete the three lines of code that classify the image and process the predictions:

    ```python
    results = predictor.classify_image(project_id, iteration_name, image)
    
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Remove these three lines.

1. Add the following code to detect objects in the image:

    ```python
    results = predictor.detect_image(project_id, iteration_name, image)

    threshold = 0.3
    
    predictions = list(prediction for prediction in results.predictions if prediction.probability > threshold)
    
    for prediction in predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    This code calls the `detect_image` method on the predictor to run the object detector. It then gathers all the predictions with a probability above a threshold and prints them to the console.

    Unlike an image classifier that only returns one result per tag, the object detector will return multiple results. Therefore, any predictions with a low probability need to be filtered out.

1. Run this code, and it will capture an image, send it to the object detector, and print out the detected objects. If you are using a virtual IoT device, ensure you have an appropriate image set in CounterFit, or that your webcam is selected. If you are using a Raspberry Pi, make sure your camera is pointing at objects on a shelf.

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   34.13%
    tomato paste:   33.95%
    tomato paste:   35.05%
    tomato paste:   32.80%
    ```

    > 💁 You may need to adjust the `threshold` to a suitable value for your images.

    You will be able to see the image that was taken and these values in the **Predictions** tab in Custom Vision.

    ![4 cans of tomato paste on a shelf with predictions for the 4 detections of 35.8%, 33.5%, 25.7% and 16.6%](../../../../../translated_images/en/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.png)

> 💁 You can find this code in the [code-detect/pi](../../../../../5-retail/lessons/2-check-stock-device/code-detect/pi) or [code-detect/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-detect/virtual-iot-device) folder.

😀 Your stock counter program was a success!

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we strive for accuracy, please note that automated translations may contain errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is recommended. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.