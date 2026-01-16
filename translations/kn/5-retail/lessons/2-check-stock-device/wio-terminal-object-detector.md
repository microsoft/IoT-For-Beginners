<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4cf1421420a6fab9ab4f2c391bd523b7",
  "translation_date": "2026-01-07T03:58:32+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-object-detector.md",
  "language_code": "kn"
}
-->
# ನಿಮ್ಮ ಐಒಟಿ ಸಾಧನದಿಂದ ನಿಮ್ಮ ವಸ್ತು ಪತ್ತೆಹಚ್ಚುವಿಕೆಯನ್ನು ಕರೆಮಾಡಿ - ವಿಯೋ ಟರ್ಮಿನಲ್

ನೀವು ನಿಮ್ಮ ವಸ್ತು ಪತ್ತೆಹಚ್ಚುವಿಕೆಯನ್ನು ಪ್ರಕಟಿಸಿದ ನಂತರ, ಅದನ್ನು ನಿಮ್ಮ ಐಒಟಿ ಸಾಧನದಿಂದ ಬಳಸಬಹುದು.

## ಚಿತ್ರ ವರ್ಗೀಕರಣ ಪ್ರಾಜೆಕ್ಟ್ ನಕಲಿಸಿ

ನಿಮ್ಮ ಸ್ಟಾಕ್ ಡಿಟೆಕ್ಟರ್‌ನ ಬಹುತೇಕ ಭಾಗವು ನೀವು ಹಿಂದಿನ ಪಾಠದಲ್ಲಿ ರಚಿಸಿದ ಚಿತ್ರ ವರ್ಗೀಕರಣಕಾರಸ್ಥಂತೆಯೇ ಇದೆ.

### ಕಾರ್ಯ - ಚಿತ್ರ ವರ್ಗೀಕರಣ ಪ್ರಾಜೆಕ್ಟ್ ನಕಲಿಸಿ

1. ನಿಮ್ಮ ArduCam ಅನ್ನು ನಿಮ್ಮ Wio Terminal ಗೆ ಸಂಪರ್ಕಿಸಿ, [ನಿರ್ಮಾಣ ಪ್ರಾಜೆಕ್ಟಿನ ಪಾಠ 2](../../../4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md#task---connect-the-camera)ರ ಹೆಜ್ಜೆಗಳನ್ನು ಅನುಸರಿಸಿ.

    ನೀವು ಕ್ಯಾಮೆರಾವನ್ನು ಒಂದೇ ಸ್ಥಿತಿಯಲ್ಲಿ ಜೋಡಿಸಲು ಬಯಸಬಹುದು, ಉದಾಹರಣೆಗೆ, ಕೇಬಲ್ ಅನ್ನು ಬಾಕ್ಸ್ ಅಥವಾ ಕ್ಯಾನ್ ಮೇಲಿನ ಕಗ್ಗತ್ತಲು ಮಾಡಿಕೊಂಡು ಅಥವಾ ಡಬಲ್-ಸೈಡೆಡ್ ಟೇಪ್ ಬಳಸಿ ಕ್ಯಾಮೆರಾಗೆ ಜೋಡಿಸುವ ಮೂಲಕ.

1. PlatformIO ಬಳಸಿ ಹೊಸ Wio Terminal ಪ್ರಾಜೆಕ್ಟ್ ರಚಿಸಿ. ಈ ಪ್ರಾಜೆಕ್ಟ್ ಅನ್ನು `stock-counter` ಎಂದು ಕರೆಯಿರಿ.

1. [ನಿರ್ಮಾಣ ಪ್ರಾಜೆಕ್ಟಿನ ಪಾಠ 2](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) ಯ ಹೆಜ್ಜೆಗಳನ್ನು ಅನುರೂಪಿಸಿ ಕ್ಯಾಮೆರೆಯಿಂದ ಚಿತ್ರಗಳನ್ನು ಸೆರೆಹಿಡಿಯಿರಿ.

1. [ನಿರ್ಮಾಣ ಪ್ರಾಜೆಕ್ಟಿನ ಪಾಠ 2](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) ಯ ಹೆಜ್ಜೆಗಳನ್ನು ಅನುಸರಿಸಿ ಚಿತ್ರ ವರ್ಗೀಕರಣಕಾರವನ್ನು ಕರೆಮಾಡಿ. ಬಹಳಷ್ಟು ಈ ಕೋಡ್ ಅನ್ನು ವಸ್ತುಗಳನ್ನು ಪತ್ತೆಮಾಡಲು ಪುನಃ ಉಪಯೋಗಿಸಲಾಗುವುದು.

## ವರ್ಗೀಕರಣಕಾರದಿಂದ ಚಿತ್ರ ಪತ್ತೆಹಚ್ಚುವಿಕೆಗೆ ಕೋಡ್ ಬದಲಾಯಿಸಿ

ನೀವು ಚಿತ್ರಗಳನ್ನು ವರ್ಗೀಕರಿಸಲು ಬಳಸಿದ ಕೋಡ್ ವಸ್ತುಗಳನ್ನು ಪತ್ತೆಹಚ್ಚುವಿಕೆಗೆ ಬಳಸಿದ ಕೋಡಿಗೆ ಬಹಳ ಸಮಾನವಾಗಿದೆ. ಮುಖ್ಯ ವ್ಯತ್ಯಾಸವೆಂದರೆ ನೀವು Custom Vision ನಿಂದ ಪಡೆದ URL ಅನ್ನು ಕರೆಮಾಡುವುದು ಮತ್ತು ಕರೆ ಫಲಿತಾಂಶಗಳು.

### ಕಾರ್ಯ - ವರ್ಗೀಕರಣಕಾರದಿಂದ ಚಿತ್ರ ಪತ್ತೆಹಚ್ಚುವಿಕೆಗೆ ಕೋಡ್ ಬದಲಾಯಿಸಿ

1. `main.cpp` ಫೈಲ್ ಮೇಲ್ಭಾಗದಲ್ಲಿ ಕೆಳಗಿನ include ನಿರ್ದೇಶನವನ್ನು ಸೇರಿಸಿ:

    ```cpp
    #include <vector>
    ```

1. `classifyImage` ಫಂಕ್ಷನ್ ಹೆಸರು `detectStock` ಎಂದಾಗಿ ಬದಲಿಸಿ, ಫಂಕ್ಷನ್ ಹೆಸರು ಮತ್ತು `buttonPressed` ಫಂಕ್ಷನ್ ನಲ್ಲಿ ಕರೆ ಎರಡೂ.

1. `detectStock` ಫಂಕ್ಷನ್ ಮೇಲ್ಭಾಗದಲ್ಲಿ ಕಡಿಮೆ ಸಂಭವನೀಯತೆ ಇರುವ ಪತ್ತೆಗಳನ್ನು ಫಿಲ್ಟರ್ ಮಾಡಲು ಥ್ರೆಶೋಲ್ಡ್ ಅನ್ನು ಘೋಷಿಸಿ:

    ```cpp
    const float threshold = 0.3f;
    ```

    ಒಂದು ಚಿತ್ರ ವರ್ಗೀಕರಣಕಾರ ಒಂದೇ ಟ್ಯಾಗ್ ಗೆ ಒಂದು ಫಲಿತಾಂಶವನ್ನು ಮಾತ್ರ ನೀಡುತ್ತದೆ, ಆದರೆ ವಸ್ತು ಪತ್ತೆಹಚ್ಚುವಿಕೆಯಿಂದ ಹಲವಾರು ಫಲಿತಾಂಶಗಳಿರುತ್ತವೆ, ಆದ್ದರಿಂದ ಕಡಿಮೆ ಸಾಧ್ಯತೆಗಳಿರುವವುಗಳನ್ನು ಫಿಲ್ಟರ್ ಮಾಡಬೇಕು.

1. `detectStock` ಫಂಕ್ಷನ್ ಮೇಲ್ಭಾಗದಲ್ಲಿ, ಭವಿಷ್ಯವಾಣಿಗಳನ್ನು ಪ್ರಕ್ರಿಯೆಗೊಳಿಸುವ ಫಂಕ್ಷನ್ ಅನ್ನು ಘೋಷಿಸಿ:

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

    ಇದು ಭವಿಷ್ಯವಾಣಿ ಪಟ್ಟಿಯನ್ನು ತೆಗೆದುಕೊಂಡು ಅವನ್ನು ಸೀರಿಯಲ್ ಮಾನಿಟರ್‌ನಲ್ಲಿ ಮುದ್ರಿಸುತ್ತದೆ.

1. `detectStock` ಫಂಕ್ಷನ್ ನಲ್ಲಿ ಭವಿಷ್ಯವಾಣಿಗಳನ್ನು ಲೂಪ್ ಮಾಡುವ `for` ಲೂಪ್ ಒಳಗಿನ ವಿಷಯವನ್ನು ಕೆಳಗಿನಂತೆ ಬದಲಿಸಿ:

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

    ಇದು ಭವಿಷ್ಯವಾಣಿಗಳನ್ನು ಲೂಪ್ ಮಾಡುತ್ತದೆ, ಸಾಧ್ಯತೆಯನ್ನು ಥ್ರೆಶೋಲ್ಡ್‌ಗೆ ಹೋಲಿಸಿ. ಥ್ರೆಶೋಲ್ಡ್ ನಿಂತು ಹೆಚ್ಚು ಸಾಧ್ಯತೆ ಇರುವ ಎಲ್ಲಾ ಭವಿಷ್ಯವಾಣಿಗಳನ್ನು `list` ಗೆ ಸೇರಿಸಿ ಮತ್ತು `processPredictions` ಫಂಕ್ಷನ್‌ಗೆ ನೀಡುತ್ತದೆ.

1. ನಿಮ್ಮ ಕೋಡ್ ಅನ್ನು ಅಪ್ಲೋಡ್ ಮಾಡಿ ಮತ್ತು ಚಾಲನೆ ಮಾಡಿ. ಕ್ಯಾಮೆರಾವನ್ನು ಶೆಲ್ಫ್ ಮೇಲಿನ ವಸ್ತುಗಳ ಕಡೆ ಮಾಡಿಸಿ ಮತ್ತು C ಬಟನ್ ಒತ್ತಿ. ಸೀರಿಯಲ್ ಮಾನಿಟರ್ ನಲ್ಲಿ ಔಟ್‌ಪುಟ್ ಕಾಣಿಸಲಿದೆ:

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

    > 💁 ನಿಮ್ಮ ಚಿತ್ರಗಳಿಗೆ ಯೋಗ್ಯವಾದ ಮೌಲ್ಯಕ್ಕೆ `threshold` ಅನ್ನು ಹೊಂದಿಸುವ ಅಗತ್ಯವಿರಬಹುದು.

    ತೆಗೆದ ಚಿತ್ರದ ಮತ್ತು ಈ ಮೌಲ್ಯಗಳನ್ನೂ ನೀವು Custom Vision ನಲ್ಲಿ **Predictions** ಟ್ಯಾಬ್ ನಲ್ಲಿ ನೋಡಬಲ್ಲಿರಿ.

    ![4 cans of tomato paste on a shelf with predictions for the 4 detections of 35.8%, 33.5%, 25.7% and 16.6%](../../../../../translated_images/kn/custom-vision-stock-prediction.942266ab1bcca341.png)

> 💁 ಈ ಕೋಡ್ ಅನ್ನು ನೀವು [code-detect/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-detect/wio-terminal) ಫೋಲ್ಡರ್‌ನಲ್ಲಿ ಕಾಣಬಹುದು.

😀 ನಿಮ್ಮ ಸ್ಟಾಕ್ ಕೌಂಟರ್ ಪ್ರೋಗ್ರಾಂ ಯಶಸ್ವಿಯಾಯಿತು!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**ವಿಚಾವಣಾ ಘೋಷಣೆ**:  
ಈ ದಾಖಲೆ [ಕೊ-ಓಪ್ ಟ್ರಾನ್ಸ್‌ಲೇಟರ್](https://github.com/Azure/co-op-translator) ಎಂಬ ಎಐ ಅನುವಾದ ಸೇವೆಯನ್ನು ಉಪಯೋಗಿಸಿ ಅನುವಾದಿಸಲಾಗಿದೆ. ನಾವು ಶುದ್ಧತೆಯನ್ನುವುದು ಪ್ರಯತ್ನಿಸುವಾಗ, ಸ್ವಯಂಚಾಲಿತ ಅನುವಾದಗಳಲ್ಲಿ ದೋಷಗಳು ಅಥವಾ ಅಸತ್ಯತೆಗಳು ಇರಬಹುದೆಂದು ಗಮನದಲ್ಲಿಡಿ. ಮೂಲ ಭಾಷೆಯ ಅಸಲಿ ದಾಖಲೆ ಅಧಿಕಾರಿಕ ಮೂಲವಾಗಿ ಪರಿಗಣಿಸಬೇಕಾಗುತ್ತದೆ. ಅತ್ಯಂತ ಮಹತ್ವಪೂರ್ಣ ಮಾಹಿತಿಗಾಗಿ ವೃತ್ತಿಪರ ಮನುಷ್ಯ ಅನುವಾದವನ್ನು ಶಿಫಾರಸು ಮಾಡಲಾಗುತ್ತದೆ. ಈ ಅನುವಾದದ ಬಳಕೆಯಿಂದ ಉಂಟಾಗುವ ಯಾವುದೇ ತಪ್ಪು ಅರ್ಥಪಾಡುಗಳಿಗೆ ನಾವು ಹೊಣೆಗಾರರಾಗುವುದಿಲ್ಲ.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->