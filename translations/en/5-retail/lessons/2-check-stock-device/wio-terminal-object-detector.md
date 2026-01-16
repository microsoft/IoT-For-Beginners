<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4cf1421420a6fab9ab4f2c391bd523b7",
  "translation_date": "2025-08-28T20:15:38+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-object-detector.md",
  "language_code": "en"
}
-->
# Call your object detector from your IoT device - Wio Terminal

Once your object detector has been published, you can use it with your IoT device.

## Copy the image classifier project

Most of your stock detector will be based on the image classifier you created in a previous lesson.

### Task - Copy the image classifier project

1. Connect your ArduCam to your Wio Terminal by following the steps in [lesson 2 of the manufacturing project](../../../4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md#task---connect-the-camera).

    You might also want to secure the camera in a fixed position, for example, by hanging the cable over a box or can, or attaching the camera to a box with double-sided tape.

1. Create a new Wio Terminal project using PlatformIO. Name this project `stock-counter`.

1. Follow the steps in [lesson 2 of the manufacturing project](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) to capture images from the camera.

1. Repeat the steps in [lesson 2 of the manufacturing project](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) to call the image classifier. Most of this code will be reused for object detection.

## Modify the code from a classifier to an object detector

The code used for classifying images is very similar to the code for detecting objects. The main difference lies in the URL provided by Custom Vision and the results returned from the call.

### Task - Modify the code from a classifier to an object detector

1. Add the following include directive at the top of the `main.cpp` file:

    ```cpp
    #include <vector>
    ```

1. Rename the `classifyImage` function to `detectStock`, updating both the function name and its call in the `buttonPressed` function.

1. Above the `detectStock` function, define a threshold to filter out detections with low probabilities:

    ```cpp
    const float threshold = 0.3f;
    ```

    Unlike an image classifier, which returns one result per tag, the object detector returns multiple results. Detections with low probabilities need to be filtered out.

1. Above the `detectStock` function, define a function to process the predictions:

    ```cpp
    void processPredictions(std::vector<JsonVariant> &predictions)
    {
        for(JsonVariant prediction : predictions)
        {
            String tag = prediction["tagName"].as<String>();
            float probability = prediction["probability"].as<float>();
    
            char buff[32];
            sprintf(buff, "%s:\t%.2f%%", tag.c_str(), probability * 100.0);
            Serial.println(buff);
        }
    }
    ```

    This function takes a list of predictions and prints them to the serial monitor.

1. In the `detectStock` function, replace the contents of the `for` loop that iterates through the predictions with the following:

    ```cpp
    std::vector<JsonVariant> passed_predictions;

    for(JsonVariant prediction : predictions) 
    {
        float probability = prediction["probability"].as<float>();
        if (probability > threshold)
        {
            passed_predictions.push_back(prediction);
        }
    }

    processPredictions(passed_predictions);
    ```

    This loop goes through the predictions, compares their probabilities to the threshold, and adds those with higher probabilities to a `list`. The `list` is then passed to the `processPredictions` function.

1. Upload and run your code. Point the camera at objects on a shelf and press the C button. The output will appear in the serial monitor:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 17416
    tomato paste:   35.84%
    tomato paste:   35.87%
    tomato paste:   34.11%
    tomato paste:   35.16%
    ```

    > 💁 You may need to adjust the `threshold` to suit your images.

    You will also be able to view the captured image and these values in the **Predictions** tab in Custom Vision.

    ![4 cans of tomato paste on a shelf with predictions for the 4 detections of 35.8%, 33.5%, 25.7% and 16.6%](../../../../../translated_images/en/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.png)

> 💁 You can find this code in the [code-detect/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-detect/wio-terminal) folder.

😀 Congratulations! Your stock counter program is working successfully!

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we aim for accuracy, please note that automated translations may include errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is advised. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.