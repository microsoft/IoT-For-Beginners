# ਆਪਣੇ IoT ਡਿਵਾਈਸ ਤੋਂ ਆਪਣੇ ਆਬਜੈਕਟ ਡਿਟੈਕਟਰ ਨੂੰ ਕਾਲ ਕਰੋ - Wio Terminal

ਜਦੋਂ ਤੁਹਾਡਾ ਆਬਜੈਕਟ ਡਿਟੈਕਟਰ ਪਬਲਿਸ਼ ਹੋ ਜਾਵੇ, ਤਾਂ ਇਸਨੂੰ ਤੁਹਾਡੇ IoT ਡਿਵਾਈਸ ਤੋਂ ਵਰਤਿਆ ਜਾ ਸਕਦਾ ਹੈ।

## ਇਮੇਜ ਕਲਾਸੀਫਾਇਰ ਪ੍ਰੋਜੈਕਟ ਕਾਪੀ ਕਰੋ

ਤੁਹਾਡਾ ਜ਼ਿਆਦਾਤਰ ਸਟਾਕ ਡਿਟੈਕਟਰ ਉਹੀ ਹੈ ਜੋ ਤੁਸੀਂ ਪਿਛਲੇ ਪਾਠ ਵਿੱਚ ਬਣਾਇਆ ਸੀ।

### ਟਾਸਕ - ਇਮੇਜ ਕਲਾਸੀਫਾਇਰ ਪ੍ਰੋਜੈਕਟ ਕਾਪੀ ਕਰੋ

1. ਆਪਣੇ ArduCam ਨੂੰ Wio Terminal ਨਾਲ ਜੁੜੋ, [ਮੈਨੂਫੈਕਚਰਿੰਗ ਪ੍ਰੋਜੈਕਟ ਦੇ ਪਾਠ 2](../../../4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md#task---connect-the-camera) ਵਿੱਚ ਦਿੱਤੇ ਕਦਮਾਂ ਦੀ ਪਾਲਣਾ ਕਰਦੇ ਹੋਏ।

    ਤੁਸੀਂ ਕੈਮਰੇ ਨੂੰ ਇੱਕ ਸਥਿਰ ਸਥਿਤੀ ਵਿੱਚ ਫਿਕਸ ਕਰਨਾ ਚਾਹੁੰਦੇ ਹੋ, ਉਦਾਹਰਣ ਲਈ, ਕੇਬਲ ਨੂੰ ਡੱਬੇ ਜਾਂ ਕੈਨ ਦੇ ਉੱਪਰ ਲਟਕਾ ਕੇ, ਜਾਂ ਕੈਮਰੇ ਨੂੰ ਡੱਬੇ ਨਾਲ ਡਬਲ-ਸਾਈਡ ਟੇਪ ਨਾਲ ਫਿਕਸ ਕਰਕੇ।

1. PlatformIO ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਇੱਕ ਨਵਾਂ Wio Terminal ਪ੍ਰੋਜੈਕਟ ਬਣਾਓ। ਇਸ ਪ੍ਰੋਜੈਕਟ ਨੂੰ `stock-counter` ਨਾਮ ਦਿਓ।

1. [ਮੈਨੂਫੈਕਚਰਿੰਗ ਪ੍ਰੋਜੈਕਟ ਦੇ ਪਾਠ 2](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) ਵਿੱਚ ਦਿੱਤੇ ਕਦਮਾਂ ਨੂੰ ਦੁਹਰਾਓ ਤਾਂ ਜੋ ਕੈਮਰੇ ਤੋਂ ਚਿੱਤਰ ਕੈਪਚਰ ਕੀਤੇ ਜਾ ਸਕਣ।

1. [ਮੈਨੂਫੈਕਚਰਿੰਗ ਪ੍ਰੋਜੈਕਟ ਦੇ ਪਾਠ 2](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) ਵਿੱਚ ਦਿੱਤੇ ਕਦਮਾਂ ਨੂੰ ਦੁਹਰਾਓ ਤਾਂ ਜੋ ਇਮੇਜ ਕਲਾਸੀਫਾਇਰ ਨੂੰ ਕਾਲ ਕੀਤਾ ਜਾ ਸਕੇ। ਇਸ ਕੋਡ ਦਾ ਜ਼ਿਆਦਾਤਰ ਹਿੱਸਾ ਆਬਜੈਕਟਸ ਦੀ ਪਛਾਣ ਕਰਨ ਲਈ ਦੁਬਾਰਾ ਵਰਤਿਆ ਜਾਵੇਗਾ।

## ਕੋਡ ਨੂੰ ਕਲਾਸੀਫਾਇਰ ਤੋਂ ਇਮੇਜ ਡਿਟੈਕਟਰ ਵਿੱਚ ਬਦਲੋ

ਤੁਹਾਡੇ ਦੁਆਰਾ ਚਿੱਤਰਾਂ ਨੂੰ ਕਲਾਸੀਫਾਈ ਕਰਨ ਲਈ ਵਰਤਿਆ ਗਿਆ ਕੋਡ ਆਬਜੈਕਟਸ ਦੀ ਪਛਾਣ ਕਰਨ ਵਾਲੇ ਕੋਡ ਦੇ ਬਹੁਤ ਹੀ ਨਜ਼ਦੀਕ ਹੈ। ਮੁੱਖ ਅੰਤਰ Custom Vision ਤੋਂ ਪ੍ਰਾਪਤ ਕੀਤੇ URL ਅਤੇ ਕਾਲ ਦੇ ਨਤੀਜੇ ਹਨ।

### ਟਾਸਕ - ਕੋਡ ਨੂੰ ਕਲਾਸੀਫਾਇਰ ਤੋਂ ਇਮੇਜ ਡਿਟੈਕਟਰ ਵਿੱਚ ਬਦਲੋ

1. `main.cpp` ਫਾਈਲ ਦੇ ਉੱਪਰ ਹਿੱਸੇ ਵਿੱਚ ਹੇਠਾਂ ਦਿੱਤੇ ਸ਼ਾਮਲ ਕਰਨ ਵਾਲੇ ਡਾਇਰੈਕਟਿਵ ਨੂੰ ਸ਼ਾਮਲ ਕਰੋ:

    ```cpp
    #include <vector>
    ```

1. `classifyImage` ਫੰਕਸ਼ਨ ਦਾ ਨਾਮ `detectStock` ਵਿੱਚ ਬਦਲੋ, ਫੰਕਸ਼ਨ ਦੇ ਨਾਮ ਅਤੇ `buttonPressed` ਫੰਕਸ਼ਨ ਵਿੱਚ ਕਾਲ ਦੋਵਾਂ।

1. `detectStock` ਫੰਕਸ਼ਨ ਦੇ ਉੱਪਰ ਇੱਕ ਥ੍ਰੈਸ਼ਹੋਲਡ ਡਿਕਲੇਅਰ ਕਰੋ ਤਾਂ ਜੋ ਉਹ ਡਿਟੈਕਸ਼ਨ ਫਿਲਟਰ ਕੀਤੇ ਜਾ ਸਕਣ ਜਿਨ੍ਹਾਂ ਦੀ ਸੰਭਾਵਨਾ ਘੱਟ ਹੈ:

    ```cpp
    const float threshold = 0.3f;
    ```

    ਇੱਕ ਇਮੇਜ ਕਲਾਸੀਫਾਇਰ ਜੋ ਸਿਰਫ਼ ਇੱਕ ਟੈਗ ਪ੍ਰਤੀ ਇੱਕ ਨਤੀਜਾ ਵਾਪਸ ਕਰਦਾ ਹੈ, ਦੇ ਉਲਟ, ਆਬਜੈਕਟ ਡਿਟੈਕਟਰ ਕਈ ਨਤੀਜੇ ਵਾਪਸ ਕਰੇਗਾ, ਇਸ ਲਈ ਜਿਨ੍ਹਾਂ ਦੀ ਸੰਭਾਵਨਾ ਘੱਟ ਹੈ ਉਹਨਾਂ ਨੂੰ ਫਿਲਟਰ ਕਰਨ ਦੀ ਲੋੜ ਹੈ।

1. `detectStock` ਫੰਕਸ਼ਨ ਦੇ ਉੱਪਰ, ਪ੍ਰਡਿਕਸ਼ਨ ਨੂੰ ਪ੍ਰੋਸੈਸ ਕਰਨ ਲਈ ਇੱਕ ਫੰਕਸ਼ਨ ਡਿਕਲੇਅਰ ਕਰੋ:

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

    ਇਹ ਪ੍ਰਡਿਕਸ਼ਨ ਦੀ ਸੂਚੀ ਲੈਂਦਾ ਹੈ ਅਤੇ ਇਸਨੂੰ ਸੀਰੀਅਲ ਮਾਨੀਟਰ 'ਤੇ ਪ੍ਰਿੰਟ ਕਰਦਾ ਹੈ।

1. `detectStock` ਫੰਕਸ਼ਨ ਵਿੱਚ, ਪ੍ਰਡਿਕਸ਼ਨ ਦੇ ਦੁਹਰਾਏ ਜਾਣ ਵਾਲੇ ਲੂਪ ਦੇ ਸਮੱਗਰੀ ਨੂੰ ਹੇਠਾਂ ਦਿੱਤੇ ਨਾਲ ਬਦਲੋ:

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

    ਇਹ ਪ੍ਰਡਿਕਸ਼ਨ ਦੇ ਦੁਹਰਾਏ ਜਾਣ ਵਾਲੇ ਲੂਪ ਵਿੱਚ, ਸੰਭਾਵਨਾ ਨੂੰ ਥ੍ਰੈਸ਼ਹੋਲਡ ਨਾਲ ਤੁਲਨਾ ਕਰਦਾ ਹੈ। ਸਾਰੀਆਂ ਪ੍ਰਡਿਕਸ਼ਨ ਜਿਨ੍ਹਾਂ ਦੀ ਸੰਭਾਵਨਾ ਥ੍ਰੈਸ਼ਹੋਲਡ ਤੋਂ ਵੱਧ ਹੈ, ਉਹਨਾਂ ਨੂੰ ਇੱਕ `list` ਵਿੱਚ ਸ਼ਾਮਲ ਕੀਤਾ ਜਾਂਦਾ ਹੈ ਅਤੇ `processPredictions` ਫੰਕਸ਼ਨ ਨੂੰ ਭੇਜਿਆ ਜਾਂਦਾ ਹੈ।

1. ਆਪਣਾ ਕੋਡ ਅਪਲੋਡ ਅਤੇ ਚਲਾਓ। ਕੈਮਰੇ ਨੂੰ ਸ਼ੈਲਫ਼ 'ਤੇ ਆਬਜੈਕਟਸ ਵੱਲ ਇਸ਼ਾਰਾ ਕਰੋ ਅਤੇ C ਬਟਨ ਦਬਾਓ। ਤੁਸੀਂ ਸੀਰੀਅਲ ਮਾਨੀਟਰ ਵਿੱਚ ਨਤੀਜੇ ਦੇਖ ਸਕਦੇ ਹੋ:

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

    > 💁 ਤੁਸੀਂ ਆਪਣੀਆਂ ਚਿੱਤਰਾਂ ਲਈ `threshold` ਨੂੰ ਇੱਕ ਉਚਿਤ ਮੁੱਲ ਵਿੱਚ ਸਹੀ ਕਰਨ ਦੀ ਲੋੜ ਪੈ ਸਕਦੀ ਹੈ।

    ਤੁਸੀਂ ਲਿਆ ਗਿਆ ਚਿੱਤਰ ਅਤੇ ਇਹ ਮੁੱਲ **Predictions** ਟੈਬ ਵਿੱਚ Custom Vision ਵਿੱਚ ਦੇਖ ਸਕਦੇ ਹੋ।

    ![ਸ਼ੈਲਫ਼ 'ਤੇ ਟਮਾਟਰ ਪੇਸਟ ਦੇ 4 ਕੈਨ, ਜਿਨ੍ਹਾਂ ਦੀ ਪਛਾਣ 35.8%, 33.5%, 25.7% ਅਤੇ 16.6% ਹੈ](../../../../../translated_images/pa/custom-vision-stock-prediction.942266ab1bcca341.webp)

> 💁 ਤੁਸੀਂ ਇਹ ਕੋਡ [code-detect/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-detect/wio-terminal) ਫੋਲਡਰ ਵਿੱਚ ਲੱਭ ਸਕਦੇ ਹੋ।

😀 ਤੁਹਾਡਾ ਸਟਾਕ ਕਾਊਂਟਰ ਪ੍ਰੋਗਰਾਮ ਸਫਲ ਰਿਹਾ!

---

**ਅਸਵੀਕਰਤਾ**:  
ਇਹ ਦਸਤਾਵੇਜ਼ AI ਅਨੁਵਾਦ ਸੇਵਾ [Co-op Translator](https://github.com/Azure/co-op-translator) ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਅਨੁਵਾਦ ਕੀਤਾ ਗਿਆ ਹੈ। ਜਦੋਂ ਕਿ ਅਸੀਂ ਸਹੀ ਹੋਣ ਦਾ ਯਤਨ ਕਰਦੇ ਹਾਂ, ਕਿਰਪਾ ਕਰਕੇ ਧਿਆਨ ਦਿਓ ਕਿ ਸਵੈਚਾਲਿਤ ਅਨੁਵਾਦਾਂ ਵਿੱਚ ਗਲਤੀਆਂ ਜਾਂ ਅਸੁੱਤੀਆਂ ਹੋ ਸਕਦੀਆਂ ਹਨ। ਇਸ ਦੀ ਮੂਲ ਭਾਸ਼ਾ ਵਿੱਚ ਮੌਜੂਦ ਮੂਲ ਦਸਤਾਵੇਜ਼ ਨੂੰ ਅਧਿਕਾਰਤ ਸਰੋਤ ਮੰਨਿਆ ਜਾਣਾ ਚਾਹੀਦਾ ਹੈ। ਮਹੱਤਵਪੂਰਨ ਜਾਣਕਾਰੀ ਲਈ, ਪੇਸ਼ੇਵਰ ਮਨੁੱਖੀ ਅਨੁਵਾਦ ਦੀ ਸਿਫਾਰਸ਼ ਕੀਤੀ ਜਾਂਦੀ ਹੈ। ਇਸ ਅਨੁਵਾਦ ਦੇ ਪ੍ਰਯੋਗ ਤੋਂ ਪੈਦਾ ਹੋਣ ਵਾਲੇ ਕਿਸੇ ਵੀ ਗਲਤਫਹਿਮੀ ਜਾਂ ਗਲਤ ਵਿਆਖਿਆ ਲਈ ਅਸੀਂ ਜ਼ਿੰਮੇਵਾਰ ਨਹੀਂ ਹਾਂ।  