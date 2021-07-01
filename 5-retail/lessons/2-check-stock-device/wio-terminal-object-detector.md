# Call your object detector from your IoT device - Wio Terminal

Once your object detector has been published, it can be used from your IoT device.

## Copy the image classifier project

The majority of your stock detector is the same as the image classifier you created in a previous lesson.

### Task - copy the image classifier project

1. Connect your ArduCam your Wio Terminal, following the steps from [lesson 2 of the manufacturing project](../../../4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md#task---connect-the-camera).

    You might also want to fix the camera in a single position, for example, by hanging the cable over a box or can, or fixing the camera to a box with double-sided tape.

1. Create a brand new Wio Terminal project using PlatformIO. Call this project `stock-counter`.

1. Replicate the steps from [lesson 2 of the manufacturing project](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) to capture images from the camera.

1. Replicate the steps from [lesson 2 of the manufacturing project](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) to call the image classifier. The majority of this code will be re-used to detect objects.

## Change the code from a classifier to an image detector

The code you used to classify images is very similar to the code to detect objects. The main difference is the URL that is called that you obtained from Custom Vision, and the results of the call.

### Task - change the code from a classifier to an image detector

1. Add the following include directive to the top of the `main.cpp` file:

    ```cpp
    #include <vector>
    ```

1. Rename the `classifyImage` function to `detectStock`, both the name of the function and the call in the `buttonPressed` function.

1. Above the `detectStock` function, declare a threshold to filter out any detections that have a low probability:

    ```cpp
    const float threshold = 0.3f;
    ```

    Unlike an image classifier that only returns one result per tag, the object detector will return multiple results, so any with a low probability need to be filtered out.

1. Above the `detectStock` function, declare a function to process the predictions:

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

    This takes a list of predictions and prints them to the serial monitor.

1. In the `detectStock` function, replace the contents of the `for` loop that loops through the predictions with the following:

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

    This loops through the predictions, comparing the probability to the threshold. All predictions that have a probability higher than the threshold are added to a `list` and passed to the `processPredictions` function.

1. Upload and run your code. Point the camera at objects on a shelf and press the C button. You will see the output in the serial monitor:

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

    > 💁 You may need to adjust the `threshold` to an appropriate value for your images.

    You will be able to see the image that was taken, and these values in the **Predictions** tab in Custom Vision.

    ![4 cans of tomato paste on a shelf with predictions for the 4 detections of 35.8%, 33.5%, 25.7% and 16.6%](../../../images/custom-vision-stock-prediction.png)

> 💁 You can find this code in the [code-detect/wio-terminal](code-detect/wio-terminal) folder.

😀 Your stock counter program was a success!
