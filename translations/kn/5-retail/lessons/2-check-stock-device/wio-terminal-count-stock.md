<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0b2ae20b0fc8e73c9598dea937cac038",
  "translation_date": "2026-01-07T04:00:30+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-count-stock.md",
  "language_code": "kn"
}
-->
# ನಿಮ್ಮ IoT ಸಾಧನದಿಂದ ಸ್ಟಾಕ್ ಎಣಿಕೆ - Wio ಟರ್ಮಿನಲ್

ಭವಿಷ್ಯವಾಣಿಗಳ ಸಂಯೋಜನೆ ಮತ್ತು ಅವುಗಳ ಬೌಂಡಿಂಗ್ ಬಾಕ್ಸುಗಳನ್ನು ಬಳಸಿಕೊಂಡು ಚಿತ್ರದಲ್ಲಿ ಸ್ಟಾಕ್ ಅನ್ನು ಎಣಿಸಬಹುದು.

## ಸ್ಟಾಕ್ ಎಣಿಕೆ

![ಪ್ರತಿ ಕ್ಯಾನಿನ ಸುತ್ತಲೂ ಬೌಂಡಿಂಗ್ ಬಾಕ್ಸುಗಳೊಂದಿಗೆ ಟೊಮೆಟೊ ಪೇಸ್ಟ್ ನ 4 ಕ್ಯಾನ್ಗಳು](../../../../../translated_images/kn/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.jpg)

ಮೇಲಿನ ಚಿತ್ರದಲ್ಲಿ ತೋರಿಸಲಾದ ಬೌಂಡಿಂಗ್ ಬಾಕ್ಸುಗಳಿಗೆ ಸಣ್ಣ ಅತಿಕ್ರಮಣವಿದೆ. ಈ ಅತಿಕ್ರಮಣ ಬಹಳ ದೊಡ್ಡದಾದರೆ, ಬೌಂಡಿಂಗ್ ಬಾಕ್ಸುಗಳು ಅದೇ ವಸ್ತುವನ್ನು ಸೂಚಿಸುತ್ತವೆ. ವಸ್ತುಗಳನ್ನು ಸರಿಯಾಗಿ ಎಣಿಸಲು, ನೀವು ಬಹಳವಾದ ಅತಿಕ್ರಮಣ ಇರುವ ಬಾಕ್ಸುಗಳನ್ನು ನಿರ್ಲಕ್ಷಿಸಬೇಕು.

### ಕಾರ್ಯ - ಅತಿಕ್ರಮಣವನ್ನು ನಿರ್ಲಕ್ಷಿಸಿ ಸ್ಟಾಕ್ ಎಣಿಕೆ

1. ನಿಮ್ಮ `stock-counter` ಪ್ರोजೆಕ್ಟ್ ಈಗಾಗಲೇ ತೆರೆಯಲಾಗದಿದ್ದರೆ ತೆರೆಯಿರಿ.

1. `processPredictions` ಫಂಕ್ಷನ್‍ಗಿಂತ ಮೇಲ್ಭಾಗದಲ್ಲಿ ಕೆಳಗಿನ ಕೋಡ್ ಸೇರಿಸಿ:

    ```cpp
    const float overlap_threshold = 0.20f;
    ```

    ಇದು ಬೌಂಡಿಂಗ್ ಬಾಕ್ಸುಗಳನ್ನು ಒಂದೇ ವಸ್ತು ಎಂದು ಪರಿಗಣಿಸುವ ಮೊದಲು ಅನುಮತಿಸಲಾದ ಶೇ.ಅತಿಕ್ರಮಣವನ್ನು ವಿವರಿಸುತ್ತದೆ. 0.20 ಎಂದರೆ 20% ಅತಿಕ್ರಮಣವನ್ನು ಸೂಚಿಸುತ್ತದೆ.

1. ಇದರ ಕೆಳಗೆ, ಮತ್ತು `processPredictions` ಫಂಕ್ಷನ್ ಮೇಲ್ಭಾಗದಲ್ಲಿ, ಎರಡು ಆಯತಗಳ ನಡುವಿನ ಅತಿಕ್ರಮಣವನ್ನು ಲೆಕ್ಕಹಾಕಲು ಕೆಳಗಿನ ಕೋಡ್ ಸೇರಿಸಿ:

    ```cpp
    struct Point {
        float x, y;
    };

    struct Rect {
        Point topLeft, bottomRight;
    };

    float area(Rect rect)
    {
        return abs(rect.bottomRight.x - rect.topLeft.x) * abs(rect.bottomRight.y - rect.topLeft.y);
    }
     
    float overlappingArea(Rect rect1, Rect rect2)
    {
        float left = max(rect1.topLeft.x, rect2.topLeft.x);
        float right = min(rect1.bottomRight.x, rect2.bottomRight.x);
        float top = max(rect1.topLeft.y, rect2.topLeft.y);
        float bottom = min(rect1.bottomRight.y, rect2.bottomRight.y);
    
    
        if ( right > left && bottom > top )
        {
            return (right-left)*(bottom-top);
        }
        
        return 0.0f;
    }
    ```

    ಈ ಕೋಡ್ ಚಿತ್ರದಲ್ಲಿನ ಬಿಂದುಗಳನ್ನು ಸಂಗ್ರಹಿಸಲು `Point` ಸ್ಟ್ರಕ್ ಅನ್ನು ಮತ್ತು ಮೇಲ್ಭಾಗ ಎಡ ಮತ್ತು ಕೆಳಭಾಗ ಬಲ ಸಹಕಾರಗಳನ್ನು ಬಳಸಿ ಆಯತವನ್ನು ವ್ಯಾಖ್ಯಾನಿಸಲು `Rect` ಸ್ಟ್ರಕ್ ಅನ್ನು ವೈಖ್ಯಾನಿಸುತ್ತದೆ. ನಂತರ ಇದು ಮೇಲ್ಭಾಗ ಎಡ ಮತ್ತು ಕೆಳಭಾಗ ಬಲ ಸಹಕಾರಗಳಿಂದ ಆಯತದ ವ್ಯಾಪ್ತಿಯನ್ನು ಲೆಕ್ಕಿಸುವ `area` ಫಂಕ್ಷನ್ ಅನ್ನು ವ್ಯಾಖ್ಯಾನಿಸುತ್ತದೆ.

    ಆದ ನಂತರ 2 ಆಯತಗಳ ಅತಿಕ್ರಮಿಸುವ ವಿಸ್ತೀರ್ಣವನ್ನು ಲೆಕ್ಕಿಸುವ `overlappingArea` ಫಂಕ್ಷನ್ ಅನ್ನು ವ್ಯಾಖ್ಯಾನಿಸುತ್ತದೆ. ಅವು ಅತಿಕ್ರಮಿಸದಿದ್ದರೆ, 0 ಅನ್ನು ಹಿಂತಿರುಗಿಸುತ್ತದೆ.

1. `overlappingArea` ಫಂಕ್ಷನ್ ಕೆಳಗೆ, ಬೌಂಡಿಂಗ್ ಬಾಕ್ಸನ್ನು `Rect` ಗೆ ಪರಿವರ್ತಿಸುವ ಫಂಕ್ಷನ್ ಅನ್ನು ಘೋಷಿಸಿ:

    ```cpp
    Rect rectFromBoundingBox(JsonVariant prediction)
    {
        JsonObject bounding_box = prediction["boundingBox"].as<JsonObject>();
    
        float left = bounding_box["left"].as<float>();
        float top = bounding_box["top"].as<float>();
        float width = bounding_box["width"].as<float>();
        float height = bounding_box["height"].as<float>();
    
        Point topLeft = {left, top};
        Point bottomRight = {left + width, top + height};
    
        return {topLeft, bottomRight};
    }
    ```

    ಇದು ವಸ್ತು ಗುರಿ ಮಾಡಿದ ಭವಿಷ್ಯವನ್ನು ಹೊಂದುತ್ತದೆ, ಬೌಂಡಿಂಗ್ ಬಾಕ್ಸ್ ಅನ್ನು ಹೊರತೆಗೆದುಕೊಳ್ಳುತ್ತದೆ ಮತ್ತು ಬೌಂಡಿಂಗ್ ಬಾಕ್ಸಿನ ಮೌಲ್ಯಗಳನ್ನು ಬಳಸಿ ಆಯತವನ್ನು ವ್ಯಾಖ್ಯಾನಿಸುತ್ತದೆ. ಬಲವು ಎಡ ಮತ್ತು ಅಗಲದ ಮೊತ್ತದಿಂದ ಲೆಕ್ಕಿಸಲಾಗುತ್ತದೆ. ಕೆಳಭಾಗವು ಮೇಲ್ಭಾಗ ಮತ್ತು ಎತ್ತರದ ಮೊತ್ತದಿಂದ ಲೆಕ್ಕಿಸಲಾಗುತ್ತದೆ.

1. ಭವಿಷ್ಯಗಳನ್ನು ಪರಸ್ಪರ ಹೋಲಿಸಬೇಕು, ಮತ್ತು ಎರಡು ಭವಿಷ್ಯಗಳ ಅತಿಕ್ರಮಣವು ತಜ್ಞಕವರಿಗಿಂತ ಹೆಚ್ಚಿನದಾಗಿದ್ದರೆ, ಅವುಗಳಲ್ಲಿ ಒಬ್ಬನನ್ನು ಅಳಿಸಲು ಆಗಬೇಕು. ಅತಿಕ್ರಮಣ ತಜ್ಞಕವು ಶೇ.ರಾಶಿಯಾಗಿದೆ, ಆದ್ದರಿಂದ ಅತಿ ಚಿಕ್ಕ ಬೌಂಡಿಂಗ್ ಬಾಕ್ಸಿನ ವಿಸ್ತೀರ್ಣಕ್ಕೆ ಗುಣಿಸಲು ಅಗತ್ಯವಿದೆ ಎದೆಕ್ಕೆ, ಅರವತ್ತೇ ಇತರ ಪ್ರಶಸ್ತಿಯಲ್ಲ, ಬೌಂಡಿಂಗ್ ಬಾಕ್ಸ್‍ನ ಶೇ.ರಾಶಿಯನ್ನು ತಪ್ಪಿಸಲು. ಪ್ರಾರಂಭಿಸಿ `processPredictions` ಫಂಕ್ಷನ್ ನಲ್ಲಿ ಅದರ ವಿಷಯದ ಅಳಿಸುವ ಮೂಲಕ.

1. ಖಾಲಿ `processPredictions` ಫಂಕ್ಷನ್ ಗೆ ಕೆಳಗಿನ ಕೋಡ್ ಸೇರಿಸಿ:

    ```cpp
    std::vector<JsonVariant> passed_predictions;

    for (int i = 0; i < predictions.size(); ++i)
    {
        Rect prediction_1_rect = rectFromBoundingBox(predictions[i]);
        float prediction_1_area = area(prediction_1_rect);
        bool passed = true;

        for (int j = i + 1; j < predictions.size(); ++j)
        {
            Rect prediction_2_rect = rectFromBoundingBox(predictions[j]);
            float prediction_2_area = area(prediction_2_rect);

            float overlap = overlappingArea(prediction_1_rect, prediction_2_rect);
            float smallest_area = min(prediction_1_area, prediction_2_area);

            if (overlap > (overlap_threshold * smallest_area))
            {
                passed = false;
                break;
            }
        }

        if (passed)
        {
            passed_predictions.push_back(predictions[i]);
        }
    }
    ```

    ಈ ಕೋಡ್ ಅತಿಕ್ರಮಿಸದ ಭವಿಷ್ಯಗಳನ್ನು ಸಂಗ್ರಹಿಸಲು ವೆಕ್ಟರ್ ಒಂದನ್ನು ಘೋಷಿಸುತ್ತದೆ. ನಂತರ ಎಲ್ಲಾ ಭವಿಷ್ಯಗಳಲ್ಲಿ ಲೂಪ್ ಮಾಡಿ, ಬೌಂಡಿಂಗ್ ಬಾಕ್ಸ್ ನಿಂದ `Rect` ರಚಿಸುತ್ತವೆ.

    ನಂತರ ಈ ಕೋಡ್ ಉಳಿದ ಭವಿಷ್ಯಗಳ ಮೇಲೆ ಲೂಪ್ ಮಾಡುತ್ತದೆ, ಪ್ರಸ್ತುತ ಭವಿಷ್ಯದ ನಂತರದ ಒಂದರಿಂದ ಪ್ರಾರಂಭಿಸಿ. ಇದು ಭವಿಷ್ಯಗಳನ್ನು ಒಂದು ಬಾರಿ ಮಾತ್ರ ಹೋಲಿಸಲು ನಿಲ್ಲಿಸುತ್ತದೆ - 1 ಮತ್ತು 2 ಒಡೆಸಿದ ನಂತರ, 2ನ್ನು 1ರೊಂದಿಗೆ ಹೋಲಿಸುವ ಅಗತ್ಯವಿಲ್ಲ, 3,4 ಇತ್ಯಾದಿಗಳೊಂದಿಗೆ ಮಾತ್ರ ಆಗುತ್ತದೆ.

    ಪ್ರತಿ ಜೋಡಿ ಭವಿಷ್ಯಗಳಿಗಾಗಿ ಅತಿಕ್ರಮಿಸುವ ವಿಸ್ತೀರ್ಣ ಲೆಕ್ಕಿಸಲಾಗುತ್ತದೆ. ಇದು ಸಣ್ಣ ಅಯತದ ವಿಸ್ತೀರ್ಣಕ್ಕೆ ಹೋಲಿಸಲಾಗುತ್ತದೆ - ಅತಿ ಕಡಿಮೆ ಬೌಂಡಿಂಗ್ ಬಾಕ್ಸ್‍ನ ಶೇ.ರಾಶಿಯನ್ನು ಮೀರಿಸಿದರೆ, ಆ ಭವಿಷ್ಯವನ್ನು ಪಾಸ್ ಆಗದೆ ಎಣಿಸಲಾಗುತ್ತದೆ. ಎಲ್ಲಾ ಅತಿಕ್ರಮಣಗಳನ್ನು ಹೋಲಿಸಿ ನಂತರ, ಭವಿಷ್ಯವು ಪರಿಶೀಲನೆಯನ್ನು ಪಾಸಾದರೆ, ಅದನ್ನು `passed_predictions` ಸಂಗ್ರಹಕ್ಕೆ ಸೇರಿಸಲಾಗುತ್ತದೆ.

    > 💁 ಇದು ಅತಿಕ್ರಮಣಗಳನ್ನು ತೆಗೆದುಹಾಕಲು ಒಂದು ಅತ್ಯಂತ ಸರಳ ವಿಧಾನ, ಅತಿಕ್ರಮಣದ ಜೋಡಿಯಲ್ಲಿ ಮೊದಲ ಭವಿಷ್ಯವನ್ನು ತೆಗೆದುಹಾಕುವುದು ಮಾತ್ರ. ಉತ્પાદನಾ ಕೋಡ್ ನಲ್ಲಿ, ನೀವು ಬಹು ವಸ್ತುಗಳ ನಡುವಿನ ಅತಿಕ್ರಮಣಗಳನ್ನು ಪರಿಗಣಿಸುವಂತಹ ಅಥವಾ ಒಂದು ಬೌಂಡಿಂಗ್ ಬಾಕ್ಸ್ ಮತ್ತೊಂದರಲ್ಲಿ ಒಳಗೊಂಡಿರುವಂತಹ ಹೆಚ್ಚು ತರ್ಕವನ್ನು ಸೇರಿಸುವುದು ಉಪಯುಕ್ತ.

1. ಇದರಲ್ಲಿ, ಪಾಸ್ ಆದ ಭವಿಷ್ಯಗಳ ವಿವರಗಳನ್ನು ಸರಣಿ ಮಾನಿಟರ್ ಗೆ ಕಳುಹಿಸಲು ಕೆಳಗಿನ ಕೋಡ್ ಸೇರಿಸಿ:

    ```cpp
    for(JsonVariant prediction : passed_predictions)
    {
        String boundingBox = prediction["boundingBox"].as<String>();
        String tag = prediction["tagName"].as<String>();
        float probability = prediction["probability"].as<float>();

        char buff[32];
        sprintf(buff, "%s:\t%.2f%%\t%s", tag.c_str(), probability * 100.0, boundingBox.c_str());
        Serial.println(buff);
    }
    ```

    ಈ ಕೋಡ್ ಪಾಸ್ ಆದ ಭವಿಷ್ಯಗಳ ಮೂಲಕ ಲೂಪ್ ಮಾಡಿ ಅವುಗಳ ವಿವರಗಳನ್ನು ಸರಣಿ ಮಾನಿಟರ್ ಗೆ ಮುದ್ರಿಸುತ್ತದೆ.

1. ಇದರ ಕೆಳಗೆ, ಎಣಿಸಿದ ವಸ್ತುಗಳ ಸಂಖ್ಯೆಯನ್ನು ಸರಣಿ ಮಾನಿಟರ್ ಗೆ ಮುದ್ರಿಸುವ ಕೋಡ್ ಸೇರಿಸಿ:

    ```cpp
    Serial.print("Counted ");
    Serial.print(passed_predictions.size());
    Serial.println(" stock items.");
    ```

    ಇದನ್ನು ನಂತರ ಸ್ಟಾಕ್ ಮಟ್ಟಗಳು ಕಡಿಮೆಯಾಗಿದ್ದರೆ ಎಚ್ಚರಿಸಲು IoT ಸೇವೆಗೆ ಕಳುಹಿಸಲಾಗಬಹುದು.

1. ನಿಮ್ಮ ಕೋಡ್ ಅನ್ನು ಅಪ್‌ಲೋಡ್ ಮಾಡಿ ಮತ್ತು ಚಲಾಯಿಸಿ. ಕ್ಯಾಮೆರಾ ಮೂಲಕ ಶೆಲ್ಫ್上的 ವಸ್ತುಗಳ ಕಡೆಗೆ ತಿರುಗಿಸಿ ಮತ್ತು C ಬಟನ್ ಒತ್ತಿ. ಭವಿಷ್ಯಗಳನ್ನು ನಿರ್ಲಕ್ಷಿಸುವಂತೆ ನೋಡಲು `overlap_threshold` ಮೌಲ್ಯವನ್ನು ಹೊಂದಿಸಿ.

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 17416
    tomato paste:   35.84%  {"left":0.395631,"top":0.215897,"width":0.180768,"height":0.359364}
    tomato paste:   35.87%  {"left":0.378554,"top":0.583012,"width":0.14824,"height":0.359382}
    tomato paste:   34.11%  {"left":0.699024,"top":0.592617,"width":0.124411,"height":0.350456}
    tomato paste:   35.16%  {"left":0.513006,"top":0.647853,"width":0.187472,"height":0.325817}
    Counted 4 stock items.
    ```

> 💁 ನೀವು ಈ ಕೋಡ್ ಅನ್ನು [code-count/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-count/wio-terminal) ಫೋಲ್ಡರ್ ನಲ್ಲಿ ಕಂಡುಹಿಡಿಯಬಹುದು.

😀 ನಿಮ್ಮ ಸ್ಟಾಕ್ কাউಂಟರ್ ಪ್ರೋಗ್ರಾಂ ಯಶಸ್ವಿಯಾಯಿತು!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**ತಯ್ಯಾರಿ**:  
ಈ ನಕ್ಷೆ AI ಅನುವಾದ ಸೇವೆ [Co-op Translator](https://github.com/Azure/co-op-translator) ಬಳಸಿ ಅನುವಾದಿಸಲಾಗಿದೆ. ನಾವು ನಿಖರತೆಯನ್ನು ಸಾಧಿಸಲು ಪ್ರಯತ್ನಿಸುತ್ತಿದ್ದರೂ, ಸ್ವಯಂಚಾಲಿತ ಅನುವಾದಗಳಲ್ಲಿ ತಪ್ಪುಗಳು ಅಥವಾ ಅಸೂಕ್ಷ್ಮತೆಗಳು ಇರಬಹುದು ಎಂದು ತಿಳಿದುಕೊಳ್ಳಿ. ಮೂಲ ದಾಖಲೆ ಅದರ ಮಾತೃಭಾಷೆಯಲ್ಲಿ ಅಧಿಕೃತ ಮೂಲವಾಗಿ ಪರಿಗಣಿಸಬೇಕು. ಪ್ರಮುಖ ಮಾಹಿತಿಗಾಗಿ ವೃತ್ತಿಪರ ಮಾನವ ಅನುವಾದವನ್ನು ಶಿಫಾರಸು ಮಾಡಲಾಗುತ್ತದೆ. ಈ ಅನುವಾದವನ್ನು ಬಳಸುವ ಮೂಲಕ ಉಂಟಾದ ಯಾವುದೇ ವೇದಿಕೆಗಳು ಅಥವಾ ತಪ್ಪು ವಿವರಣೆಗಳಿಗೆ ನಾವು ಜವಾಬ್ದಾರಿಯಲ್ಲ.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->