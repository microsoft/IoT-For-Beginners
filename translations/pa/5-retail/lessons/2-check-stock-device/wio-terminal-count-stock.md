<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0b2ae20b0fc8e73c9598dea937cac038",
  "translation_date": "2025-08-27T09:56:11+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-count-stock.md",
  "language_code": "pa"
}
-->
# ਆਪਣੇ IoT ਡਿਵਾਈਸ ਤੋਂ ਸਟਾਕ ਗਿਣੋ - Wio Terminal

ਪੇਸ਼ਗੋਈਆਂ ਅਤੇ ਉਨ੍ਹਾਂ ਦੇ ਬਾਊਂਡਿੰਗ ਬਾਕਸਾਂ ਦੇ ਮਿਲਾਪ ਨਾਲ ਚਿੱਤਰ ਵਿੱਚ ਸਟਾਕ ਗਿਣਿਆ ਜਾ ਸਕਦਾ ਹੈ।

## ਸਟਾਕ ਗਿਣੋ

![ਟਮਾਟਰ ਪੇਸਟ ਦੇ 4 ਡੱਬੇ, ਹਰ ਡੱਬੇ ਦੇ ਆਲੇ-ਦੁਆਲੇ ਬਾਊਂਡਿੰਗ ਬਾਕਸ](../../../../../translated_images/pa/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.jpg)

ਉਪਰ ਦਿੱਤੇ ਚਿੱਤਰ ਵਿੱਚ, ਬਾਊਂਡਿੰਗ ਬਾਕਸਾਂ ਵਿੱਚ ਥੋੜ੍ਹਾ ਜਿਹਾ ਓਵਰਲੈਪ ਹੈ। ਜੇ ਇਹ ਓਵਰਲੈਪ ਕਾਫ਼ੀ ਵੱਧ ਹੋਵੇ, ਤਾਂ ਬਾਊਂਡਿੰਗ ਬਾਕਸ ਇੱਕੋ ਚੀਜ਼ ਨੂੰ ਦਰਸਾ ਸਕਦੇ ਹਨ। ਚੀਜ਼ਾਂ ਨੂੰ ਸਹੀ ਤਰੀਕੇ ਨਾਲ ਗਿਣਣ ਲਈ, ਤੁਹਾਨੂੰ ਉਹ ਬਾਕਸ ਨਜ਼ਰਅੰਦਾਜ਼ ਕਰਨੇ ਪੈਣਗੇ ਜਿਨ੍ਹਾਂ ਵਿੱਚ ਮਹੱਤਵਪੂਰਨ ਓਵਰਲੈਪ ਹੈ।

### ਕੰਮ - ਓਵਰਲੈਪ ਨੂੰ ਨਜ਼ਰਅੰਦਾਜ਼ ਕਰਦੇ ਹੋਏ ਸਟਾਕ ਗਿਣੋ

1. ਜੇ ਤੁਹਾਡਾ `stock-counter` ਪ੍ਰੋਜੈਕਟ ਖੁੱਲ੍ਹਿਆ ਨਹੀਂ ਹੈ, ਤਾਂ ਇਸਨੂੰ ਖੋਲ੍ਹੋ।

1. `processPredictions` ਫੰਕਸ਼ਨ ਤੋਂ ਉੱਪਰ ਹੇਠਾਂ ਦਿੱਤਾ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ:

    ```cpp
    const float overlap_threshold = 0.20f;
    ```

    ਇਹ ਉਸ ਪ੍ਰਤੀਸ਼ਤ ਓਵਰਲੈਪ ਨੂੰ ਪਰਿਭਾਸ਼ਿਤ ਕਰਦਾ ਹੈ ਜੋ ਬਾਊਂਡਿੰਗ ਬਾਕਸਾਂ ਨੂੰ ਇੱਕੋ ਚੀਜ਼ ਮੰਨਣ ਤੋਂ ਪਹਿਲਾਂ ਸਵੀਕਾਰ ਕੀਤਾ ਜਾ ਸਕਦਾ ਹੈ। 0.20 ਦਾ ਮਤਲਬ 20% ਓਵਰਲੈਪ ਹੈ।

1. ਇਸ ਤੋਂ ਹੇਠਾਂ, ਅਤੇ `processPredictions` ਫੰਕਸ਼ਨ ਤੋਂ ਉੱਪਰ, ਦੋ ਆਯਤਾਂ ਦੇ ਵਿਚਕਾਰ ਓਵਰਲੈਪ ਦੀ ਗਣਨਾ ਕਰਨ ਲਈ ਹੇਠਾਂ ਦਿੱਤਾ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ:

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

    ਇਹ ਕੋਡ ਇੱਕ `Point` ਸਟ੍ਰਕਚਰ ਨੂੰ ਚਿੱਤਰ ਵਿੱਚ ਬਿੰਦੂ ਸਟੋਰ ਕਰਨ ਲਈ ਪਰਿਭਾਸ਼ਿਤ ਕਰਦਾ ਹੈ, ਅਤੇ ਇੱਕ `Rect` ਸਟ੍ਰਕਚਰ ਨੂੰ ਇੱਕ ਆਯਤ ਨੂੰ ਉੱਤਰੀ-ਪੱਛਮੀ ਅਤੇ ਦੱਖਣੀ-ਪੂਰਬੀ ਕੋਆਰਡੀਨੇਟ ਨਾਲ ਪਰਿਭਾਸ਼ਿਤ ਕਰਨ ਲਈ। ਇਸ ਤੋਂ ਬਾਅਦ ਇਹ ਇੱਕ `area` ਫੰਕਸ਼ਨ ਪਰਿਭਾਸ਼ਿਤ ਕਰਦਾ ਹੈ ਜੋ ਉੱਤਰੀ-ਪੱਛਮੀ ਅਤੇ ਦੱਖਣੀ-ਪੂਰਬੀ ਕੋਆਰਡੀਨੇਟ ਤੋਂ ਆਯਤ ਦਾ ਖੇਤਰਫਲ ਕੱਢਦਾ ਹੈ।

    ਅਗਲੇ ਹਿੱਸੇ ਵਿੱਚ ਇਹ ਇੱਕ `overlappingArea` ਫੰਕਸ਼ਨ ਪਰਿਭਾਸ਼ਿਤ ਕਰਦਾ ਹੈ ਜੋ 2 ਆਯਤਾਂ ਦੇ ਓਵਰਲੈਪਿੰਗ ਖੇਤਰ ਦੀ ਗਣਨਾ ਕਰਦਾ ਹੈ। ਜੇ ਉਹ ਓਵਰਲੈਪ ਨਹੀਂ ਕਰਦੇ, ਤਾਂ ਇਹ 0 ਵਾਪਸ ਕਰਦਾ ਹੈ।

1. `overlappingArea` ਫੰਕਸ਼ਨ ਤੋਂ ਹੇਠਾਂ, ਇੱਕ ਫੰਕਸ਼ਨ ਘੋਸ਼ਿਤ ਕਰੋ ਜੋ ਬਾਊਂਡਿੰਗ ਬਾਕਸ ਨੂੰ `Rect` ਵਿੱਚ ਬਦਲਦਾ ਹੈ:

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

    ਇਹ ਆਬਜੈਕਟ ਡਿਟੈਕਟਰ ਤੋਂ ਇੱਕ ਪੇਸ਼ਗੋਈ ਲੈਂਦਾ ਹੈ, ਬਾਊਂਡਿੰਗ ਬਾਕਸ ਨੂੰ ਕੱਢਦਾ ਹੈ ਅਤੇ ਬਾਕਸ ਦੇ ਮੁੱਲਾਂ ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਇੱਕ ਆਯਤ ਪਰਿਭਾਸ਼ਿਤ ਕਰਦਾ ਹੈ। ਸੱਜਾ ਪਾਸਾ ਖੱਬੇ ਪਾਸੇ ਤੋਂ ਪਲੱਸ ਚੌੜਾਈ ਨਾਲ ਕੱਢਿਆ ਜਾਂਦਾ ਹੈ। ਹੇਠਾਂ ਵਾਲਾ ਹਿੱਸਾ ਉੱਪਰ ਤੋਂ ਪਲੱਸ ਉਚਾਈ ਨਾਲ ਕੱਢਿਆ ਜਾਂਦਾ ਹੈ।

1. ਪੇਸ਼ਗੋਈਆਂ ਨੂੰ ਇੱਕ ਦੂਜੇ ਨਾਲ ਤੁਲਨਾ ਕਰਨ ਦੀ ਲੋੜ ਹੈ, ਅਤੇ ਜੇ 2 ਪੇਸ਼ਗੋਈਆਂ ਵਿੱਚ ਓਵਰਲੈਪ ਥ੍ਰੈਸ਼ਹੋਲਡ ਤੋਂ ਵੱਧ ਹੈ, ਤਾਂ ਉਨ੍ਹਾਂ ਵਿੱਚੋਂ ਇੱਕ ਨੂੰ ਹਟਾਉਣਾ ਪਵੇਗਾ। ਓਵਰਲੈਪ ਥ੍ਰੈਸ਼ਹੋਲਡ ਇੱਕ ਪ੍ਰਤੀਸ਼ਤ ਹੈ, ਇਸ ਲਈ ਇਸਨੂੰ ਸਭ ਤੋਂ ਛੋਟੇ ਬਾਊਂਡਿੰਗ ਬਾਕਸ ਦੇ ਆਕਾਰ ਨਾਲ ਗੁਣਾ ਕਰਨ ਦੀ ਲੋੜ ਹੈ ਤਾਂ ਜੋ ਇਹ ਜਾਂਚਿਆ ਜਾ ਸਕੇ ਕਿ ਓਵਰਲੈਪ ਦਿੱਤੇ ਪ੍ਰਤੀਸ਼ਤ ਤੋਂ ਵੱਧ ਹੈ ਜਾਂ ਨਹੀਂ। `processPredictions` ਫੰਕਸ਼ਨ ਦੀ ਸਮੱਗਰੀ ਨੂੰ ਮਿਟਾਓ।

1. ਖਾਲੀ `processPredictions` ਫੰਕਸ਼ਨ ਵਿੱਚ ਹੇਠਾਂ ਦਿੱਤਾ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ:

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

    ਇਹ ਕੋਡ ਉਹ ਪੇਸ਼ਗੋਈਆਂ ਸਟੋਰ ਕਰਨ ਲਈ ਇੱਕ ਵੈਕਟਰ ਘੋਸ਼ਿਤ ਕਰਦਾ ਹੈ ਜੋ ਓਵਰਲੈਪ ਨਹੀਂ ਕਰਦੀਆਂ। ਇਹ ਫਿਰ ਸਾਰੀਆਂ ਪੇਸ਼ਗੋਈਆਂ ਵਿੱਚ ਲੂਪ ਕਰਦਾ ਹੈ, ਬਾਊਂਡਿੰਗ ਬਾਕਸ ਤੋਂ ਇੱਕ `Rect` ਬਣਾਉਂਦਾ ਹੈ।

    ਅਗਲੇ ਹਿੱਸੇ ਵਿੱਚ ਇਹ ਬਾਕੀ ਪੇਸ਼ਗੋਈਆਂ ਵਿੱਚ ਲੂਪ ਕਰਦਾ ਹੈ, ਮੌਜੂਦਾ ਪੇਸ਼ਗੋਈ ਤੋਂ ਬਾਅਦ ਵਾਲੀ ਤੋਂ ਸ਼ੁਰੂ ਕਰਦਾ ਹੈ। ਇਹ ਪੇਸ਼ਗੋਈਆਂ ਨੂੰ ਵਾਰ-ਵਾਰ ਤੁਲਨਾ ਕਰਨ ਤੋਂ ਰੋਕਦਾ ਹੈ - ਜਦੋਂ 1 ਅਤੇ 2 ਦੀ ਤੁਲਨਾ ਹੋ ਗਈ, ਤਾਂ 2 ਨੂੰ 1 ਨਾਲ ਮੁੜ ਤੁਲਨਾ ਕਰਨ ਦੀ ਲੋੜ ਨਹੀਂ ਹੈ, ਸਿਰਫ 3, 4 ਆਦਿ ਨਾਲ।

    ਹਰ ਜੋੜੇ ਦੀ ਪੇਸ਼ਗੋਈਆਂ ਲਈ ਓਵਰਲੈਪਿੰਗ ਖੇਤਰ ਦੀ ਗਣਨਾ ਕੀਤੀ ਜਾਂਦੀ ਹੈ। ਇਸਨੂੰ ਫਿਰ ਸਭ ਤੋਂ ਛੋਟੇ ਬਾਊਂਡਿੰਗ ਬਾਕਸ ਦੇ ਖੇਤਰ ਨਾਲ ਤੁਲਨਾ ਕੀਤੀ ਜਾਂਦੀ ਹੈ - ਜੇ ਓਵਰਲੈਪ ਬਾਊਂਡਿੰਗ ਬਾਕਸ ਦੇ ਦਿੱਤੇ ਪ੍ਰਤੀਸ਼ਤ ਤੋਂ ਵੱਧ ਹੈ, ਤਾਂ ਪੇਸ਼ਗੋਈ ਨੂੰ ਪਾਸ ਨਹੀਂ ਮੰਨਿਆ ਜਾਂਦਾ। ਜੇ ਸਾਰੀਆਂ ਓਵਰਲੈਪ ਦੀ ਤੁਲਨਾ ਕਰਨ ਤੋਂ ਬਾਅਦ, ਪੇਸ਼ਗੋਈ ਜਾਂਚਾਂ ਪਾਸ ਕਰਦੀ ਹੈ, ਤਾਂ ਇਸਨੂੰ `passed_predictions` ਕਲੈਕਸ਼ਨ ਵਿੱਚ ਸ਼ਾਮਲ ਕੀਤਾ ਜਾਂਦਾ ਹੈ।

    > 💁 ਇਹ ਓਵਰਲੈਪ ਨੂੰ ਹਟਾਉਣ ਦਾ ਬਹੁਤ ਸਧਾਰਨ ਤਰੀਕਾ ਹੈ, ਸਿਰਫ ਓਵਰਲੈਪਿੰਗ ਜੋੜੇ ਵਿੱਚੋਂ ਪਹਿਲੇ ਨੂੰ ਹਟਾਉਣਾ। ਪ੍ਰੋਡਕਸ਼ਨ ਕੋਡ ਲਈ, ਤੁਹਾਨੂੰ ਇੱਥੇ ਹੋਰ ਤਰਕ ਸ਼ਾਮਲ ਕਰਨ ਦੀ ਲੋੜ ਹੋਵੇਗੀ, ਜਿਵੇਂ ਕਿ ਕਈ ਚੀਜ਼ਾਂ ਦੇ ਓਵਰਲੈਪ ਨੂੰ ਧਿਆਨ ਵਿੱਚ ਰੱਖਣਾ, ਜਾਂ ਜੇਕਰ ਇੱਕ ਬਾਊਂਡਿੰਗ ਬਾਕਸ ਦੂਜੇ ਵਿੱਚ ਸ਼ਾਮਲ ਹੈ।

1. ਇਸ ਤੋਂ ਬਾਅਦ, ਪਾਸ ਕੀਤੀਆਂ ਪੇਸ਼ਗੋਈਆਂ ਦੇ ਵੇਰਵੇ ਸੀਰੀਅਲ ਮਾਨੀਟਰ 'ਤੇ ਭੇਜਣ ਲਈ ਹੇਠਾਂ ਦਿੱਤਾ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ:

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

    ਇਹ ਕੋਡ ਪਾਸ ਕੀਤੀਆਂ ਪੇਸ਼ਗੋਈਆਂ ਵਿੱਚ ਲੂਪ ਕਰਦਾ ਹੈ ਅਤੇ ਉਨ੍ਹਾਂ ਦੇ ਵੇਰਵੇ ਸੀਰੀਅਲ ਮਾਨੀਟਰ 'ਤੇ ਪ੍ਰਿੰਟ ਕਰਦਾ ਹੈ।

1. ਇਸ ਤੋਂ ਹੇਠਾਂ, ਗਿਣੇ ਗਏ ਆਈਟਮਾਂ ਦੀ ਗਿਣਤੀ ਸੀਰੀਅਲ ਮਾਨੀਟਰ 'ਤੇ ਪ੍ਰਿੰਟ ਕਰਨ ਲਈ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ:

    ```cpp
    Serial.print("Counted ");
    Serial.print(passed_predictions.size());
    Serial.println(" stock items.");
    ```

    ਇਹ ਫਿਰ IoT ਸੇਵਾ ਨੂੰ ਭੇਜਿਆ ਜਾ ਸਕਦਾ ਹੈ ਜੇ ਸਟਾਕ ਪੱਧਰ ਘੱਟ ਹਨ ਤਾਂ ਸੂਚਿਤ ਕਰਨ ਲਈ।

1. ਆਪਣਾ ਕੋਡ ਅੱਪਲੋਡ ਕਰੋ ਅਤੇ ਚਲਾਓ। ਕੈਮਰੇ ਨੂੰ ਸ਼ੈਲਫ਼ 'ਤੇ ਚੀਜ਼ਾਂ ਵੱਲ ਮੋੜੋ ਅਤੇ C ਬਟਨ ਦਬਾਓ। `overlap_threshold` ਮੁੱਲ ਨੂੰ ਸੈਟ ਕਰਕੇ ਦੇਖੋ ਕਿ ਕਿਵੇਂ ਪੇਸ਼ਗੋਈਆਂ ਨੂੰ ਨਜ਼ਰਅੰਦਾਜ਼ ਕੀਤਾ ਜਾਂਦਾ ਹੈ।

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

> 💁 ਤੁਸੀਂ ਇਹ ਕੋਡ [code-count/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-count/wio-terminal) ਫੋਲਡਰ ਵਿੱਚ ਲੱਭ ਸਕਦੇ ਹੋ।

😀 ਤੁਹਾਡਾ ਸਟਾਕ ਕਾਊਂਟਰ ਪ੍ਰੋਗਰਾਮ ਸਫਲ ਰਿਹਾ!

---

**ਅਸਵੀਕਾਰਨਾ**:  
ਇਹ ਦਸਤਾਵੇਜ਼ AI ਅਨੁਵਾਦ ਸੇਵਾ [Co-op Translator](https://github.com/Azure/co-op-translator) ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਅਨੁਵਾਦ ਕੀਤਾ ਗਿਆ ਹੈ। ਜਦੋਂ ਕਿ ਅਸੀਂ ਸਹੀਤਾ ਲਈ ਯਤਨਸ਼ੀਲ ਹਾਂ, ਕਿਰਪਾ ਕਰਕੇ ਧਿਆਨ ਦਿਓ ਕਿ ਸਵੈਚਾਲਿਤ ਅਨੁਵਾਦਾਂ ਵਿੱਚ ਗਲਤੀਆਂ ਜਾਂ ਅਸੁਚੀਤਤਾਵਾਂ ਹੋ ਸਕਦੀਆਂ ਹਨ। ਮੂਲ ਦਸਤਾਵੇਜ਼ ਨੂੰ ਇਸਦੀ ਮੂਲ ਭਾਸ਼ਾ ਵਿੱਚ ਅਧਿਕਾਰਤ ਸਰੋਤ ਮੰਨਿਆ ਜਾਣਾ ਚਾਹੀਦਾ ਹੈ। ਮਹੱਤਵਪੂਰਨ ਜਾਣਕਾਰੀ ਲਈ, ਪੇਸ਼ੇਵਰ ਮਨੁੱਖੀ ਅਨੁਵਾਦ ਦੀ ਸਿਫਾਰਸ਼ ਕੀਤੀ ਜਾਂਦੀ ਹੈ। ਇਸ ਅਨੁਵਾਦ ਦੀ ਵਰਤੋਂ ਤੋਂ ਪੈਦਾ ਹੋਣ ਵਾਲੇ ਕਿਸੇ ਵੀ ਗਲਤਫਹਿਮੀ ਜਾਂ ਗਲਤ ਵਿਆਖਿਆ ਲਈ ਅਸੀਂ ਜ਼ਿੰਮੇਵਾਰ ਨਹੀਂ ਹਾਂ।