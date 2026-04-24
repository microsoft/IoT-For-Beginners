# ਇੱਕ ਚਿੱਤਰ ਨੂੰ ਵਰਗਬੱਧ ਕਰੋ - ਵਰਚੁਅਲ IoT ਹਾਰਡਵੇਅਰ ਅਤੇ ਰਾਸਪਬੇਰੀ ਪਾਈ

ਇਸ ਪਾਠ ਦੇ ਇਸ ਹਿੱਸੇ ਵਿੱਚ, ਤੁਸੀਂ ਕੈਮਰੇ ਦੁਆਰਾ ਕੈਪਚਰ ਕੀਤੀ ਗਈ ਚਿੱਤਰ ਨੂੰ ਵਰਗਬੱਧ ਕਰਨ ਲਈ ਕਸਟਮ ਵਿਜ਼ਨ ਸੇਵਾ ਨੂੰ ਭੇਜੋਗੇ।

## ਚਿੱਤਰਾਂ ਨੂੰ ਕਸਟਮ ਵਿਜ਼ਨ ਨੂੰ ਭੇਜੋ

ਕਸਟਮ ਵਿਜ਼ਨ ਸੇਵਾ ਵਿੱਚ ਇੱਕ ਪਾਇਥਨ SDK ਹੈ ਜਿਸਦਾ ਇਸਤੇਮਾਲ ਚਿੱਤਰਾਂ ਨੂੰ ਵਰਗਬੱਧ ਕਰਨ ਲਈ ਕੀਤਾ ਜਾ ਸਕਦਾ ਹੈ।

### ਕੰਮ - ਚਿੱਤਰਾਂ ਨੂੰ ਕਸਟਮ ਵਿਜ਼ਨ ਨੂੰ ਭੇਜੋ

1. VS ਕੋਡ ਵਿੱਚ `fruit-quality-detector` ਫੋਲਡਰ ਖੋਲ੍ਹੋ। ਜੇ ਤੁਸੀਂ ਵਰਚੁਅਲ IoT ਡਿਵਾਈਸ ਵਰਤ ਰਹੇ ਹੋ, ਤਾਂ ਯਕੀਨੀ ਬਣਾਓ ਕਿ ਵਰਚੁਅਲ ਵਾਤਾਵਰਣ ਟਰਮੀਨਲ ਵਿੱਚ ਚੱਲ ਰਿਹਾ ਹੈ।

1. ਕਸਟਮ ਵਿਜ਼ਨ ਨੂੰ ਚਿੱਤਰ ਭੇਜਣ ਲਈ ਪਾਇਥਨ SDK ਇੱਕ Pip ਪੈਕੇਜ ਵਜੋਂ ਉਪਲਬਧ ਹੈ। ਇਸਨੂੰ ਹੇਠਾਂ ਦਿੱਤੇ ਕਮਾਂਡ ਨਾਲ ਇੰਸਟਾਲ ਕਰੋ:

    ```sh
    pip3 install azure-cognitiveservices-vision-customvision
    ```

1. `app.py` ਫਾਈਲ ਦੇ ਉੱਪਰ ਹੇਠਾਂ ਦਿੱਤੇ ਇੰਪੋਰਟ ਬਿਆਨ ਸ਼ਾਮਲ ਕਰੋ:

    ```python
    from msrest.authentication import ApiKeyCredentials
    from azure.cognitiveservices.vision.customvision.prediction import CustomVisionPredictionClient
    ```

    ਇਹ ਕਸਟਮ ਵਿਜ਼ਨ ਲਾਇਬ੍ਰੇਰੀਆਂ ਤੋਂ ਕੁਝ ਮੌਡੀਊਲ ਲਿਆਉਂਦਾ ਹੈ, ਇੱਕ ਪ੍ਰਡਿਕਸ਼ਨ ਕੀ ਨਾਲ ਪ੍ਰਮਾਣਿਕਤਾ ਕਰਨ ਲਈ, ਅਤੇ ਦੂਜਾ ਪ੍ਰਡਿਕਸ਼ਨ ਕਲਾਇੰਟ ਕਲਾਸ ਪ੍ਰਦਾਨ ਕਰਨ ਲਈ ਜੋ ਕਿ ਕਸਟਮ ਵਿਜ਼ਨ ਨੂੰ ਕਾਲ ਕਰ ਸਕਦਾ ਹੈ।

1. ਫਾਈਲ ਦੇ ਅੰਤ ਵਿੱਚ ਹੇਠਾਂ ਦਿੱਤਾ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ:

    ```python
    prediction_url = '<prediction_url>'
    prediction_key = '<prediction key>'
    ```

    `<prediction_url>` ਨੂੰ ਇਸ ਪਾਠ ਵਿੱਚ ਪਹਿਲਾਂ ਦਿੱਤੇ *Prediction URL* ਡਾਇਲਾਗ ਤੋਂ ਕਾਪੀ ਕੀਤੇ URL ਨਾਲ ਬਦਲੋ। `<prediction key>` ਨੂੰ ਉਸੇ ਡਾਇਲਾਗ ਤੋਂ ਕਾਪੀ ਕੀਤੀ ਪ੍ਰਡਿਕਸ਼ਨ ਕੀ ਨਾਲ ਬਦਲੋ।

1. *Prediction URL* ਡਾਇਲਾਗ ਦੁਆਰਾ ਪ੍ਰਦਾਨ ਕੀਤਾ ਗਿਆ ਪ੍ਰਡਿਕਸ਼ਨ URL ਸਿੱਧੇ REST ਐਂਡਪੌਇੰਟ ਨੂੰ ਕਾਲ ਕਰਨ ਲਈ ਤਿਆਰ ਕੀਤਾ ਗਿਆ ਹੈ। ਪਾਇਥਨ SDK URL ਦੇ ਵੱਖ-ਵੱਖ ਹਿੱਸਿਆਂ ਨੂੰ ਵੱਖਰੇ ਢੰਗ ਨਾਲ ਵਰਤਦਾ ਹੈ। ਇਸ URL ਨੂੰ ਲੋੜੀਂਦੇ ਹਿੱਸਿਆਂ ਵਿੱਚ ਵੰਡਣ ਲਈ ਹੇਠਾਂ ਦਿੱਤਾ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ:

    ```python
    parts = prediction_url.split('/')
    endpoint = 'https://' + parts[2]
    project_id = parts[6]
    iteration_name = parts[9]
    ```

    ਇਹ URL ਨੂੰ ਵੰਡਦਾ ਹੈ, `https://<location>.api.cognitive.microsoft.com` ਦੇ ਐਂਡਪੌਇੰਟ, ਪ੍ਰੋਜੈਕਟ ID, ਅਤੇ ਪ੍ਰਕਾਸ਼ਿਤ ਇਟਰੇਸ਼ਨ ਦੇ ਨਾਮ ਨੂੰ ਕੱਢਦਾ ਹੈ।

1. ਪ੍ਰਡਿਕਸ਼ਨ ਕਰਨ ਲਈ ਹੇਠਾਂ ਦਿੱਤੇ ਕੋਡ ਨਾਲ ਇੱਕ ਪ੍ਰਡਿਕਟਰ ਆਬਜੈਕਟ ਬਣਾਓ:

    ```python
    prediction_credentials = ApiKeyCredentials(in_headers={"Prediction-key": prediction_key})
    predictor = CustomVisionPredictionClient(endpoint, prediction_credentials)
    ```

    `prediction_credentials` ਪ੍ਰਡਿਕਸ਼ਨ ਕੀ ਨੂੰ ਲਪੇਟਦਾ ਹੈ। ਇਹ ਫਿਰ ਐਂਡਪੌਇੰਟ ਵੱਲ ਇਸ਼ਾਰਾ ਕਰਨ ਵਾਲੇ ਪ੍ਰਡਿਕਸ਼ਨ ਕਲਾਇੰਟ ਆਬਜੈਕਟ ਬਣਾਉਣ ਲਈ ਵਰਤੇ ਜਾਂਦੇ ਹਨ।

1. ਹੇਠਾਂ ਦਿੱਤੇ ਕੋਡ ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਚਿੱਤਰ ਨੂੰ ਕਸਟਮ ਵਿਜ਼ਨ ਨੂੰ ਭੇਜੋ:

    ```python
    image.seek(0)
    results = predictor.classify_image(project_id, iteration_name, image)
    ```

    ਇਹ ਚਿੱਤਰ ਨੂੰ ਮੁੜ ਸ਼ੁਰੂ ਤੋਂ ਰਿਵਾਇੰਡ ਕਰਦਾ ਹੈ, ਫਿਰ ਇਸਨੂੰ ਪ੍ਰਡਿਕਸ਼ਨ ਕਲਾਇੰਟ ਨੂੰ ਭੇਜਦਾ ਹੈ।

1. ਆਖਰ ਵਿੱਚ, ਹੇਠਾਂ ਦਿੱਤੇ ਕੋਡ ਨਾਲ ਨਤੀਜੇ ਦਿਖਾਓ:

    ```python
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    ਇਹ ਸਾਰੇ ਪ੍ਰਡਿਕਸ਼ਨ ਜੋ ਵਾਪਸ ਕੀਤੇ ਗਏ ਹਨ, ਉਨ੍ਹਾਂ ਵਿੱਚ ਲੂਪ ਕਰੇਗਾ ਅਤੇ ਉਨ੍ਹਾਂ ਨੂੰ ਟਰਮੀਨਲ 'ਤੇ ਦਿਖਾਵੇਗਾ। ਵਾਪਸ ਕੀਤੇ ਗਏ ਸੰਭਾਵਨਾਵਾਂ 0-1 ਤੱਕ ਦੇ ਫਲੋਟਿੰਗ ਪੌਇੰਟ ਨੰਬਰ ਹੁੰਦੇ ਹਨ, ਜਿੱਥੇ 0 ਦਾ ਮਤਲਬ 0% ਮੌਕਾ ਹੈ ਕਿ ਟੈਗ ਨਾਲ ਮੇਲ ਖਾਂਦਾ ਹੈ, ਅਤੇ 1 ਦਾ ਮਤਲਬ 100% ਮੌਕਾ ਹੈ।

    > 💁 ਚਿੱਤਰ ਵਰਗਬੱਧ ਕਰਨ ਵਾਲੇ ਸਾਰੇ ਟੈਗਾਂ ਲਈ ਪ੍ਰਤੀਸ਼ਤ ਵਾਪਸ ਕਰਦੇ ਹਨ ਜੋ ਵਰਤੇ ਗਏ ਹਨ। ਹਰ ਟੈਗ ਲਈ ਇੱਕ ਸੰਭਾਵਨਾ ਹੋਵੇਗੀ ਕਿ ਚਿੱਤਰ ਉਸ ਟੈਗ ਨਾਲ ਮੇਲ ਖਾਂਦਾ ਹੈ।

1. ਆਪਣਾ ਕੋਡ ਚਲਾਓ, ਆਪਣੇ ਕੈਮਰੇ ਨੂੰ ਕੁਝ ਫਲਾਂ ਵੱਲ ਇਸ਼ਾਰਾ ਕਰਦੇ ਹੋਏ, ਜਾਂ ਇੱਕ ਉਚਿਤ ਚਿੱਤਰ ਸੈੱਟ, ਜਾਂ ਜੇ ਤੁਸੀਂ ਵਰਚੁਅਲ IoT ਹਾਰਡਵੇਅਰ ਵਰਤ ਰਹੇ ਹੋ ਤਾਂ ਆਪਣੇ ਵੈਬਕੈਮ 'ਤੇ ਦਿਖਣ ਵਾਲੇ ਫਲਾਂ ਵੱਲ। ਤੁਸੀਂ ਕਨਸੋਲ ਵਿੱਚ ਆਉਟਪੁੱਟ ਦੇਖੋਗੇ:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

    ਤੁਸੀਂ ਲਿਆ ਗਿਆ ਚਿੱਤਰ ਦੇਖ ਸਕੋਗੇ, ਅਤੇ ਇਹ ਮੁੱਲ **Predictions** ਟੈਬ ਵਿੱਚ ਕਸਟਮ ਵਿਜ਼ਨ ਵਿੱਚ ਵੇਖ ਸਕਦੇ ਹੋ।

    ![ਕਸਟਮ ਵਿਜ਼ਨ ਵਿੱਚ ਇੱਕ ਕੇਲਾ 56.8% ਪੱਕਾ ਅਤੇ 43.1% ਕੱਚਾ ਪੇਸ਼ਗੋਈ ਕੀਤੀ ਗਈ](../../../../../translated_images/pa/custom-vision-banana-prediction.30cdff4e1d72db5d.webp)

> 💁 ਤੁਸੀਂ ਇਹ ਕੋਡ [code-classify/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/pi) ਜਾਂ [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/virtual-iot-device) ਫੋਲਡਰ ਵਿੱਚ ਲੱਭ ਸਕਦੇ ਹੋ।

😀 ਤੁਹਾਡਾ ਫਲ ਗੁਣਵੱਤਾ ਵਰਗਬੱਧ ਕਰਨ ਵਾਲਾ ਪ੍ਰੋਗਰਾਮ ਸਫਲ ਰਿਹਾ!

---

**ਅਸਵੀਕਰਤੀ**:  
ਇਹ ਦਸਤਾਵੇਜ਼ AI ਅਨੁਵਾਦ ਸੇਵਾ [Co-op Translator](https://github.com/Azure/co-op-translator) ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਅਨੁਵਾਦ ਕੀਤਾ ਗਿਆ ਹੈ। ਜਦੋਂ ਕਿ ਅਸੀਂ ਸਹੀ ਹੋਣ ਦੀ ਕੋਸ਼ਿਸ਼ ਕਰਦੇ ਹਾਂ, ਕਿਰਪਾ ਕਰਕੇ ਧਿਆਨ ਦਿਓ ਕਿ ਸਵੈਚਾਲਿਤ ਅਨੁਵਾਦਾਂ ਵਿੱਚ ਗਲਤੀਆਂ ਜਾਂ ਅਸੁਚੱਜੇਪਣ ਹੋ ਸਕਦੇ ਹਨ। ਮੂਲ ਦਸਤਾਵੇਜ਼ ਨੂੰ ਇਸਦੀ ਮੂਲ ਭਾਸ਼ਾ ਵਿੱਚ ਅਧਿਕਾਰਤ ਸਰੋਤ ਮੰਨਿਆ ਜਾਣਾ ਚਾਹੀਦਾ ਹੈ। ਮਹੱਤਵਪੂਰਨ ਜਾਣਕਾਰੀ ਲਈ, ਪੇਸ਼ੇਵਰ ਮਨੁੱਖੀ ਅਨੁਵਾਦ ਦੀ ਸਿਫਾਰਸ਼ ਕੀਤੀ ਜਾਂਦੀ ਹੈ। ਇਸ ਅਨੁਵਾਦ ਦੀ ਵਰਤੋਂ ਤੋਂ ਪੈਦਾ ਹੋਣ ਵਾਲੇ ਕਿਸੇ ਵੀ ਗਲਤਫਹਿਮੀ ਜਾਂ ਗਲਤ ਵਿਆਖਿਆ ਲਈ ਅਸੀਂ ਜ਼ਿੰਮੇਵਾਰ ਨਹੀਂ ਹਾਂ।