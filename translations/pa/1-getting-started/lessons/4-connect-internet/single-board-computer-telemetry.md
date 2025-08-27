<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1226517aae5f5b6f904434670394c688",
  "translation_date": "2025-08-27T12:20:12+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md",
  "language_code": "pa"
}
-->
# ਇੰਟਰਨੈਟ 'ਤੇ ਆਪਣੀ ਨਾਈਟਲਾਈਟ ਨੂੰ ਕੰਟਰੋਲ ਕਰੋ - ਵਰਚੁਅਲ IoT ਹਾਰਡਵੇਅਰ ਅਤੇ ਰਾਸਪਬੈਰੀ ਪਾਈ

ਇਸ ਪਾਠ ਦੇ ਇਸ ਹਿੱਸੇ ਵਿੱਚ, ਤੁਸੀਂ ਆਪਣੇ ਰਾਸਪਬੈਰੀ ਪਾਈ ਜਾਂ ਵਰਚੁਅਲ IoT ਡਿਵਾਈਸ ਤੋਂ ਲਾਈਟ ਲੈਵਲ ਦੇ ਟੈਲੀਮੇਟਰੀ ਨੂੰ MQTT ਬ੍ਰੋਕਰ ਨੂੰ ਭੇਜੋਗੇ।

## ਟੈਲੀਮੇਟਰੀ ਪ੍ਰਕਾਸ਼ਿਤ ਕਰੋ

ਅਗਲਾ ਕਦਮ ਟੈਲੀਮੇਟਰੀ ਨਾਲ ਇੱਕ JSON ਦਸਤਾਵੇਜ਼ ਬਣਾਉਣਾ ਅਤੇ ਇਸਨੂੰ MQTT ਬ੍ਰੋਕਰ ਨੂੰ ਭੇਜਣਾ ਹੈ।

### ਕੰਮ

ਟੈਲੀਮੇਟਰੀ ਨੂੰ MQTT ਬ੍ਰੋਕਰ 'ਤੇ ਪ੍ਰਕਾਸ਼ਿਤ ਕਰੋ।

1. VS Code ਵਿੱਚ ਨਾਈਟਲਾਈਟ ਪ੍ਰੋਜੈਕਟ ਖੋਲ੍ਹੋ।

1. ਜੇ ਤੁਸੀਂ ਵਰਚੁਅਲ IoT ਡਿਵਾਈਸ ਵਰਤ ਰਹੇ ਹੋ, ਤਾਂ ਯਕੀਨੀ ਬਣਾਓ ਕਿ ਟਰਮੀਨਲ ਵਰਚੁਅਲ ਵਾਤਾਵਰਣ ਚਲਾ ਰਿਹਾ ਹੈ। ਜੇ ਤੁਸੀਂ ਰਾਸਪਬੈਰੀ ਪਾਈ ਵਰਤ ਰਹੇ ਹੋ, ਤਾਂ ਤੁਸੀਂ ਵਰਚੁਅਲ ਵਾਤਾਵਰਣ ਦੀ ਵਰਤੋਂ ਨਹੀਂ ਕਰ ਰਹੇ ਹੋਵੋਗੇ।

1. `app.py` ਫਾਈਲ ਦੇ ਸ਼ੁਰੂ ਵਿੱਚ ਹੇਠਾਂ ਦਿੱਤਾ ਗਿਆ ਇਮਪੋਰਟ ਸ਼ਾਮਲ ਕਰੋ:

    ```python
    import json
    ```

    `json` ਲਾਇਬ੍ਰੇਰੀ ਟੈਲੀਮੇਟਰੀ ਨੂੰ JSON ਦਸਤਾਵੇਜ਼ ਵਜੋਂ ਐਨਕੋਡ ਕਰਨ ਲਈ ਵਰਤੀ ਜਾਂਦੀ ਹੈ।

1. `client_name` ਡਿਕਲੇਰੇਸ਼ਨ ਤੋਂ ਬਾਅਦ ਹੇਠਾਂ ਦਿੱਤਾ ਹੋਇਆ ਸ਼ਾਮਲ ਕਰੋ:

    ```python
    client_telemetry_topic = id + '/telemetry'
    ```

    `client_telemetry_topic` ਉਹ MQTT ਟਾਪਿਕ ਹੈ ਜਿਸ 'ਤੇ ਡਿਵਾਈਸ ਲਾਈਟ ਲੈਵਲ ਪ੍ਰਕਾਸ਼ਿਤ ਕਰੇਗਾ।

1. ਫਾਈਲ ਦੇ ਅੰਤ ਵਿੱਚ `while True:` ਲੂਪ ਦੀ ਸਮੱਗਰੀ ਨੂੰ ਹੇਠਾਂ ਦਿੱਤੇ ਨਾਲ ਬਦਲੋ:

    ```python
    while True:
        light = light_sensor.light
        telemetry = json.dumps({'light' : light})

        print("Sending telemetry ", telemetry)
    
        mqtt_client.publish(client_telemetry_topic, telemetry)
    
        time.sleep(5)
    ```

    ਇਹ ਕੋਡ ਲਾਈਟ ਲੈਵਲ ਨੂੰ ਇੱਕ JSON ਦਸਤਾਵੇਜ਼ ਵਿੱਚ ਪੈਕ ਕਰਦਾ ਹੈ ਅਤੇ ਇਸਨੂੰ MQTT ਬ੍ਰੋਕਰ 'ਤੇ ਪ੍ਰਕਾਸ਼ਿਤ ਕਰਦਾ ਹੈ। ਇਹ ਫਿਰ ਸੁਨੇਹੇ ਭੇਜਣ ਦੀ ਆਵ੍ਰਿਤੀ ਨੂੰ ਘਟਾਉਣ ਲਈ ਸੌਂਦਾ ਹੈ।

1. ਕੋਡ ਨੂੰ ਉਸੇ ਤਰੀਕੇ ਨਾਲ ਚਲਾਓ ਜਿਵੇਂ ਤੁਸੀਂ ਅਸਾਈਨਮੈਂਟ ਦੇ ਪਿਛਲੇ ਹਿੱਸੇ ਤੋਂ ਕੋਡ ਚਲਾਇਆ ਸੀ। ਜੇ ਤੁਸੀਂ ਵਰਚੁਅਲ IoT ਡਿਵਾਈਸ ਵਰਤ ਰਹੇ ਹੋ, ਤਾਂ ਯਕੀਨੀ ਬਣਾਓ ਕਿ CounterFit ਐਪ ਚੱਲ ਰਹੀ ਹੈ ਅਤੇ ਲਾਈਟ ਸੈਂਸਰ ਅਤੇ LED ਸਹੀ ਪਿੰਸ 'ਤੇ ਬਣਾਏ ਗਏ ਹਨ।

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Sending telemetry  {"light": 0}
    Sending telemetry  {"light": 0}
    ```

> 💁 ਤੁਸੀਂ ਇਹ ਕੋਡ [code-telemetry/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/virtual-device) ਫੋਲਡਰ ਜਾਂ [code-telemetry/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/pi) ਫੋਲਡਰ ਵਿੱਚ ਲੱਭ ਸਕਦੇ ਹੋ।

😀 ਤੁਸੀਂ ਸਫਲਤਾਪੂਰਵਕ ਆਪਣੇ ਡਿਵਾਈਸ ਤੋਂ ਟੈਲੀਮੇਟਰੀ ਭੇਜ ਦਿੱਤੀ ਹੈ।

---

**ਅਸਵੀਕਾਰਨਾ**:  
ਇਹ ਦਸਤਾਵੇਜ਼ AI ਅਨੁਵਾਦ ਸੇਵਾ [Co-op Translator](https://github.com/Azure/co-op-translator) ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਅਨੁਵਾਦ ਕੀਤਾ ਗਿਆ ਹੈ। ਜਦੋਂ ਕਿ ਅਸੀਂ ਸਹੀ ਹੋਣ ਦੀ ਕੋਸ਼ਿਸ਼ ਕਰਦੇ ਹਾਂ, ਕਿਰਪਾ ਕਰਕੇ ਧਿਆਨ ਦਿਓ ਕਿ ਸਵੈਚਾਲਿਤ ਅਨੁਵਾਦਾਂ ਵਿੱਚ ਗਲਤੀਆਂ ਜਾਂ ਅਸੁਚੱਜੇਪਣ ਹੋ ਸਕਦੇ ਹਨ। ਮੂਲ ਦਸਤਾਵੇਜ਼, ਜੋ ਇਸਦੀ ਮੂਲ ਭਾਸ਼ਾ ਵਿੱਚ ਹੈ, ਨੂੰ ਅਧਿਕਾਰਤ ਸਰੋਤ ਮੰਨਿਆ ਜਾਣਾ ਚਾਹੀਦਾ ਹੈ। ਮਹੱਤਵਪੂਰਨ ਜਾਣਕਾਰੀ ਲਈ, ਪੇਸ਼ੇਵਰ ਮਨੁੱਖੀ ਅਨੁਵਾਦ ਦੀ ਸਿਫਾਰਸ਼ ਕੀਤੀ ਜਾਂਦੀ ਹੈ। ਇਸ ਅਨੁਵਾਦ ਦੀ ਵਰਤੋਂ ਤੋਂ ਪੈਦਾ ਹੋਣ ਵਾਲੇ ਕਿਸੇ ਵੀ ਗਲਤਫਹਿਮੀ ਜਾਂ ਗਲਤ ਵਿਆਖਿਆ ਲਈ ਅਸੀਂ ਜ਼ਿੰਮੇਵਾਰ ਨਹੀਂ ਹਾਂ।