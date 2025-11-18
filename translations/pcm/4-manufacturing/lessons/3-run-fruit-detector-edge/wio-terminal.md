<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "48ac21ec80329c930db7b84bd6b592ec",
  "translation_date": "2025-11-18T18:50:05+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/wio-terminal.md",
  "language_code": "pcm"
}
-->
# Classify image wit IoT Edge based image classifier - Wio Terminal

For dis part of di lesson, you go use di Image Classifier wey dey run for di IoT Edge device.

## Use di IoT Edge classifier

Di IoT device fit redirect to use di IoT Edge image classifier. Di URL for di Image Classifier na `http://<IP address or name>/image`, replace `<IP address or name>` wit di IP address or host name of di computer wey dey run IoT Edge.

### Task - use di IoT Edge classifier

1. Open di `fruit-quality-detector` app project if e never open before.

1. Di image classifier dey run as REST API wey dey use HTTP, no be HTTPS, so di call go need use WiFi client wey fit work wit only HTTP calls. Dis one mean say certificate no dey needed. Delete di `CERTIFICATE` from di `config.h` file.

1. Di prediction URL for di `config.h` file go need update to di new URL. You fit also delete di `PREDICTION_KEY` because e no dey needed.

    ```cpp
    const char *PREDICTION_URL = "<URL>";
    ```

    Replace `<URL>` wit di URL for your classifier.

1. For `main.cpp`, change di include directive for di WiFi Client Secure to import di standard HTTP version:

    ```cpp
    #include <WiFiClient.h>
    ```

1. Change di declaration of `WiFiClient` to di HTTP version:

    ```cpp
    WiFiClient client;
    ```

1. Find di line wey set di certificate for di WiFi client. Remove di line `client.setCACert(CERTIFICATE);` from di `connectWiFi` function.

1. For di `classifyImage` function, remove di `httpClient.addHeader("Prediction-Key", PREDICTION_KEY);` line wey dey set di prediction key for di header.

1. Upload and run your code. Point di camera go some fruit and press di C button. You go see di output for di serial monitor:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 You fit find dis code for di [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/wio-terminal) folder.

😀 Your fruit quality classifier program don work well!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Disclaimer**:  
Dis dokyument don translate wit AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). Even as we dey try make am accurate, abeg sabi say machine translation fit get mistake or no dey correct well. Di original dokyument for im native language na di main source wey you go fit trust. For important mata, e good make professional human translator check am. We no go fit take blame for any misunderstanding or wrong interpretation wey fit happen because you use dis translation.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->