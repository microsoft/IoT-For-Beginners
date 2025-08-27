<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "50151d9f9dce2801348a93880ef16d86",
  "translation_date": "2025-08-27T10:44:45+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/single-board-computer.md",
  "language_code": "pa"
}
-->
# IoT Edge ਦੇ ਆਧਾਰਿਤ ਚਿੱਤਰ ਵਰਗੀਕਰਨ - ਵਰਚੁਅਲ IoT ਹਾਰਡਵੇਅਰ ਅਤੇ ਰਾਸਪਬੈਰੀ ਪਾਈ

ਇਸ ਪਾਠ ਦੇ ਇਸ ਹਿੱਸੇ ਵਿੱਚ, ਤੁਸੀਂ IoT Edge ਡਿਵਾਈਸ 'ਤੇ ਚੱਲ ਰਹੇ ਚਿੱਤਰ ਵਰਗੀਕਰਨ ਨੂੰ ਵਰਤੋਂ ਵਿੱਚ ਲਿਆਓਗੇ।

## IoT Edge ਵਰਗੀਕਰਨ ਦੀ ਵਰਤੋਂ ਕਰੋ

IoT ਡਿਵਾਈਸ ਨੂੰ IoT Edge ਚਿੱਤਰ ਵਰਗੀਕਰਨ ਦੀ ਵਰਤੋਂ ਕਰਨ ਲਈ ਮੁੜ-ਨਿਰਦੇਸ਼ਿਤ ਕੀਤਾ ਜਾ ਸਕਦਾ ਹੈ। ਚਿੱਤਰ ਵਰਗੀਕਰਨ ਲਈ URL ਹੈ `http://<IP address or name>/image`, ਜਿੱਥੇ `<IP address or name>` ਨੂੰ IoT Edge ਚਲਾਉਣ ਵਾਲੇ ਕੰਪਿਊਟਰ ਦੇ IP ਪਤਾ ਜਾਂ ਹੋਸਟ ਨਾਮ ਨਾਲ ਬਦਲੋ।

Custom Vision ਲਈ Python ਲਾਇਬ੍ਰੇਰੀ ਸਿਰਫ ਕਲਾਉਡ-ਹੋਸਟ ਕੀਤੇ ਮਾਡਲਾਂ ਨਾਲ ਕੰਮ ਕਰਦੀ ਹੈ, IoT Edge 'ਤੇ ਹੋਸਟ ਕੀਤੇ ਮਾਡਲਾਂ ਨਾਲ ਨਹੀਂ। ਇਸਦਾ ਮਤਲਬ ਹੈ ਕਿ ਤੁਹਾਨੂੰ ਵਰਗੀਕਰਨ ਨੂੰ ਕਾਲ ਕਰਨ ਲਈ REST API ਦੀ ਵਰਤੋਂ ਕਰਨੀ ਪਵੇਗੀ।

### ਕੰਮ - IoT Edge ਵਰਗੀਕਰਨ ਦੀ ਵਰਤੋਂ ਕਰੋ

1. ਜੇ `fruit-quality-detector` ਪ੍ਰੋਜੈਕਟ VS Code ਵਿੱਚ ਖੁੱਲ੍ਹਾ ਨਹੀਂ ਹੈ, ਤਾਂ ਇਸਨੂੰ ਖੋਲ੍ਹੋ। ਜੇ ਤੁਸੀਂ ਵਰਚੁਅਲ IoT ਡਿਵਾਈਸ ਦੀ ਵਰਤੋਂ ਕਰ ਰਹੇ ਹੋ, ਤਾਂ ਯਕੀਨੀ ਬਣਾਓ ਕਿ ਵਰਚੁਅਲ ਵਾਤਾਵਰਣ ਐਕਟੀਵੇਟ ਹੈ।

1. `app.py` ਫਾਈਲ ਖੋਲ੍ਹੋ ਅਤੇ `azure.cognitiveservices.vision.customvision.prediction` ਅਤੇ `msrest.authentication` ਤੋਂ ਆਯਾਤ ਸਟੇਟਮੈਂਟ ਹਟਾਓ।

1. ਫਾਈਲ ਦੇ ਉੱਪਰ ਹਿੱਸੇ ਵਿੱਚ ਹੇਠਾਂ ਦਿੱਤਾ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ:

    ```python
    import requests
    ```

1. ਚਿੱਤਰ ਨੂੰ ਫਾਈਲ ਵਿੱਚ ਸੇਵ ਕਰਨ ਤੋਂ ਬਾਅਦ, `image_file.write(image.read())` ਤੋਂ ਫਾਈਲ ਦੇ ਅੰਤ ਤੱਕ ਸਾਰਾ ਕੋਡ ਹਟਾਓ।

1. ਫਾਈਲ ਦੇ ਅੰਤ ਵਿੱਚ ਹੇਠਾਂ ਦਿੱਤਾ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ:

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

    `<URL>` ਨੂੰ ਆਪਣੇ ਵਰਗੀਕਰਨ ਲਈ URL ਨਾਲ ਬਦਲੋ।

    ਇਹ ਕੋਡ ਵਰਗੀਕਰਨ ਨੂੰ REST POST ਬੇਨਤੀ ਭੇਜਦਾ ਹੈ, ਜਿਸ ਵਿੱਚ ਚਿੱਤਰ ਨੂੰ ਬੇਨਤੀ ਦੇ ਬਾਡੀ ਵਜੋਂ ਭੇਜਿਆ ਜਾਂਦਾ ਹੈ। ਨਤੀਜੇ JSON ਦੇ ਰੂਪ ਵਿੱਚ ਵਾਪਸ ਆਉਂਦੇ ਹਨ, ਅਤੇ ਇਹ ਡਿਕੋਡ ਕਰਕੇ ਸੰਭਾਵਨਾਵਾਂ ਪ੍ਰਿੰਟ ਕਰਦਾ ਹੈ।

1. ਆਪਣਾ ਕੋਡ ਚਲਾਓ, ਆਪਣੇ ਕੈਮਰੇ ਨੂੰ ਕੁਝ ਫਲਾਂ ਵੱਲ ਇਸ਼ਾਰਾ ਕਰਦੇ ਹੋਏ, ਜਾਂ ਉਚਿਤ ਚਿੱਤਰ ਸੈੱਟ, ਜਾਂ ਜੇ ਤੁਸੀਂ ਵਰਚੁਅਲ IoT ਹਾਰਡਵੇਅਰ ਦੀ ਵਰਤੋਂ ਕਰ ਰਹੇ ਹੋ ਤਾਂ ਆਪਣੇ ਵੈਬਕੈਮ 'ਤੇ ਦਿਖਾਈ ਦੇ ਰਹੇ ਫਲਾਂ ਵੱਲ। ਤੁਸੀਂ ਕਨਸੋਲ ਵਿੱਚ ਆਉਟਪੁੱਟ ਦੇਖੋਗੇ:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 ਤੁਸੀਂ ਇਹ ਕੋਡ [code-classify/pi](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/pi) ਜਾਂ [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/virtual-iot-device) ਫੋਲਡਰ ਵਿੱਚ ਲੱਭ ਸਕਦੇ ਹੋ।

😀 ਤੁਹਾਡਾ ਫਲ ਗੁਣਵੱਤਾ ਵਰਗੀਕਰਨ ਪ੍ਰੋਗਰਾਮ ਸਫਲ ਰਿਹਾ!

---

**ਅਸਵੀਕਰਤੀ**:  
ਇਹ ਦਸਤਾਵੇਜ਼ AI ਅਨੁਵਾਦ ਸੇਵਾ [Co-op Translator](https://github.com/Azure/co-op-translator) ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਅਨੁਵਾਦ ਕੀਤਾ ਗਿਆ ਹੈ। ਜਦੋਂ ਕਿ ਅਸੀਂ ਸਹੀ ਹੋਣ ਦੀ ਕੋਸ਼ਿਸ਼ ਕਰਦੇ ਹਾਂ, ਕਿਰਪਾ ਕਰਕੇ ਧਿਆਨ ਦਿਓ ਕਿ ਸਵੈਚਾਲਿਤ ਅਨੁਵਾਦਾਂ ਵਿੱਚ ਗਲਤੀਆਂ ਜਾਂ ਅਸੁਚੀਤਤਾਵਾਂ ਹੋ ਸਕਦੀਆਂ ਹਨ। ਮੂਲ ਦਸਤਾਵੇਜ਼, ਜੋ ਇਸਦੀ ਮੂਲ ਭਾਸ਼ਾ ਵਿੱਚ ਹੈ, ਨੂੰ ਅਧਿਕਾਰਤ ਸਰੋਤ ਮੰਨਿਆ ਜਾਣਾ ਚਾਹੀਦਾ ਹੈ। ਮਹੱਤਵਪੂਰਨ ਜਾਣਕਾਰੀ ਲਈ, ਪੇਸ਼ੇਵਰ ਮਨੁੱਖੀ ਅਨੁਵਾਦ ਦੀ ਸਿਫਾਰਸ਼ ਕੀਤੀ ਜਾਂਦੀ ਹੈ। ਇਸ ਅਨੁਵਾਦ ਦੀ ਵਰਤੋਂ ਤੋਂ ਪੈਦਾ ਹੋਣ ਵਾਲੇ ਕਿਸੇ ਵੀ ਗਲਤਫਹਿਮੀ ਜਾਂ ਗਲਤ ਵਿਆਖਿਆ ਲਈ ਅਸੀਂ ਜ਼ਿੰਮੇਵਾਰ ਨਹੀਂ ਹਾਂ।