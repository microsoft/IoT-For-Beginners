<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "48ac21ec80329c930db7b84bd6b592ec",
  "translation_date": "2025-08-27T10:43:50+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/wio-terminal.md",
  "language_code": "pa"
}
-->
# IoT ਐਜ ਅਧਾਰਿਤ ਚਿੱਤਰ ਵਰਗੀਕਰਨ - Wio Terminal

ਇਸ ਪਾਠ ਦੇ ਇਸ ਹਿੱਸੇ ਵਿੱਚ, ਤੁਸੀਂ IoT ਐਜ ਡਿਵਾਈਸ 'ਤੇ ਚੱਲ ਰਹੇ ਚਿੱਤਰ ਵਰਗੀਕਰਨ ਨੂੰ ਵਰਤੋਂ ਵਿੱਚ ਲਿਆਓਗੇ।

## IoT ਐਜ ਵਰਗੀਕਰਨ ਦੀ ਵਰਤੋਂ ਕਰੋ

IoT ਡਿਵਾਈਸ ਨੂੰ IoT ਐਜ ਚਿੱਤਰ ਵਰਗੀਕਰਨ ਦੀ ਵਰਤੋਂ ਕਰਨ ਲਈ ਮੁੜ-ਨਿਰਦੇਸ਼ਿਤ ਕੀਤਾ ਜਾ ਸਕਦਾ ਹੈ। ਚਿੱਤਰ ਵਰਗੀਕਰਨ ਲਈ URL ਹੈ `http://<IP address or name>/image`, ਜਿੱਥੇ `<IP address or name>` ਨੂੰ IoT ਐਜ ਚਲਾ ਰਹੇ ਕੰਪਿਊਟਰ ਦੇ IP ਪਤਾ ਜਾਂ ਹੋਸਟ ਨਾਮ ਨਾਲ ਬਦਲੋ।

### ਕੰਮ - IoT ਐਜ ਵਰਗੀਕਰਨ ਦੀ ਵਰਤੋਂ ਕਰੋ

1. ਜੇ `fruit-quality-detector` ਐਪ ਪ੍ਰੋਜੈਕਟ ਖੁੱਲ੍ਹਾ ਨਹੀਂ ਹੈ, ਤਾਂ ਇਸਨੂੰ ਖੋਲ੍ਹੋ।

1. ਚਿੱਤਰ ਵਰਗੀਕਰਨ HTTP ਦੀ ਵਰਤੋਂ ਕਰਦੇ REST API ਵਜੋਂ ਚੱਲ ਰਿਹਾ ਹੈ, HTTPS ਦੀ ਨਹੀਂ, ਇਸ ਲਈ ਕਾਲ ਨੂੰ ਸਿਰਫ HTTP ਕਾਲਾਂ ਨਾਲ ਕੰਮ ਕਰਨ ਵਾਲੇ WiFi ਕਲਾਇੰਟ ਦੀ ਲੋੜ ਹੈ। ਇਸਦਾ ਮਤਲਬ ਹੈ ਕਿ ਸਰਟੀਫਿਕੇਟ ਦੀ ਲੋੜ ਨਹੀਂ ਹੈ। `config.h` ਫਾਈਲ ਵਿੱਚੋਂ `CERTIFICATE` ਨੂੰ ਹਟਾਓ।

1. `config.h` ਫਾਈਲ ਵਿੱਚ ਭਵਿੱਖਵਾਣੀ URL ਨੂੰ ਨਵੇਂ URL ਨਾਲ ਅਪਡੇਟ ਕਰਨ ਦੀ ਲੋੜ ਹੈ। ਤੁਸੀਂ `PREDICTION_KEY` ਨੂੰ ਵੀ ਹਟਾ ਸਕਦੇ ਹੋ ਕਿਉਂਕਿ ਇਸਦੀ ਲੋੜ ਨਹੀਂ ਹੈ।

    ```cpp
    const char *PREDICTION_URL = "<URL>";
    ```

    `<URL>` ਨੂੰ ਆਪਣੇ ਵਰਗੀਕਰਨ ਲਈ URL ਨਾਲ ਬਦਲੋ।

1. `main.cpp` ਵਿੱਚ, WiFi Client Secure ਲਈ ਸ਼ਾਮਲ ਕਰਨ ਵਾਲੇ ਨਿਰਦੇਸ਼ ਨੂੰ ਸਧਾਰਨ HTTP ਵਰਜਨ ਨਾਲ ਬਦਲੋ:

    ```cpp
    #include <WiFiClient.h>
    ```

1. `WiFiClient` ਦੀ ਘੋਸ਼ਣਾ ਨੂੰ HTTP ਵਰਜਨ ਵਿੱਚ ਬਦਲੋ:

    ```cpp
    WiFiClient client;
    ```

1. WiFi ਕਲਾਇੰਟ 'ਤੇ ਸਰਟੀਫਿਕੇਟ ਸੈੱਟ ਕਰਨ ਵਾਲੀ ਲਾਈਨ ਚੁਣੋ। `connectWiFi` ਫੰਕਸ਼ਨ ਵਿੱਚੋਂ `client.setCACert(CERTIFICATE);` ਲਾਈਨ ਨੂੰ ਹਟਾਓ।

1. `classifyImage` ਫੰਕਸ਼ਨ ਵਿੱਚੋਂ, ਹੈਡਰ ਵਿੱਚ ਭਵਿੱਖਵਾਣੀ ਕੁੰਜੀ ਸੈੱਟ ਕਰਨ ਵਾਲੀ ਲਾਈਨ `httpClient.addHeader("Prediction-Key", PREDICTION_KEY);` ਨੂੰ ਹਟਾਓ।

1. ਆਪਣਾ ਕੋਡ ਅਪਲੋਡ ਕਰੋ ਅਤੇ ਚਲਾਓ। ਕੈਮਰੇ ਨੂੰ ਕੁਝ ਫਲਾਂ ਵੱਲ ਮੋੜੋ ਅਤੇ C ਬਟਨ ਦਬਾਓ। ਤੁਸੀਂ ਸੀਰੀਅਲ ਮਾਨੀਟਰ ਵਿੱਚ ਆਉਟਪੁੱਟ ਦੇਖੋਗੇ:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 ਤੁਸੀਂ ਇਹ ਕੋਡ [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/wio-terminal) ਫੋਲਡਰ ਵਿੱਚ ਲੱਭ ਸਕਦੇ ਹੋ।

😀 ਤੁਹਾਡਾ ਫਲ ਗੁਣਵੱਤਾ ਵਰਗੀਕਰਨ ਪ੍ਰੋਗਰਾਮ ਸਫਲ ਰਿਹਾ!

---

**ਅਸਵੀਕਰਤੀ**:  
ਇਹ ਦਸਤਾਵੇਜ਼ AI ਅਨੁਵਾਦ ਸੇਵਾ [Co-op Translator](https://github.com/Azure/co-op-translator) ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਅਨੁਵਾਦ ਕੀਤਾ ਗਿਆ ਹੈ। ਜਦੋਂ ਕਿ ਅਸੀਂ ਸਹੀ ਹੋਣ ਦੀ ਕੋਸ਼ਿਸ਼ ਕਰਦੇ ਹਾਂ, ਕਿਰਪਾ ਕਰਕੇ ਧਿਆਨ ਦਿਓ ਕਿ ਸਵੈਚਾਲਿਤ ਅਨੁਵਾਦਾਂ ਵਿੱਚ ਗਲਤੀਆਂ ਜਾਂ ਅਸੁਚੱਜੇਪਣ ਹੋ ਸਕਦੇ ਹਨ। ਮੂਲ ਦਸਤਾਵੇਜ਼, ਜੋ ਇਸਦੀ ਮੂਲ ਭਾਸ਼ਾ ਵਿੱਚ ਹੈ, ਨੂੰ ਅਧਿਕਾਰਤ ਸਰੋਤ ਮੰਨਿਆ ਜਾਣਾ ਚਾਹੀਦਾ ਹੈ। ਮਹੱਤਵਪੂਰਨ ਜਾਣਕਾਰੀ ਲਈ, ਪੇਸ਼ੇਵਰ ਮਨੁੱਖੀ ਅਨੁਵਾਦ ਦੀ ਸਿਫਾਰਸ਼ ਕੀਤੀ ਜਾਂਦੀ ਹੈ। ਇਸ ਅਨੁਵਾਦ ਦੀ ਵਰਤੋਂ ਤੋਂ ਪੈਦਾ ਹੋਣ ਵਾਲੇ ਕਿਸੇ ਵੀ ਗਲਤਫਹਿਮੀ ਜਾਂ ਗਲਤ ਵਿਆਖਿਆ ਲਈ ਅਸੀਂ ਜ਼ਿੰਮੇਵਾਰ ਨਹੀਂ ਹਾਂ।