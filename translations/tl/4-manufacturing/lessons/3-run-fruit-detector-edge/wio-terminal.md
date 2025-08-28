<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "48ac21ec80329c930db7b84bd6b592ec",
  "translation_date": "2025-08-27T22:57:02+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/wio-terminal.md",
  "language_code": "tl"
}
-->
# Mag-classify ng imahe gamit ang IoT Edge na image classifier - Wio Terminal

Sa bahaging ito ng aralin, gagamitin mo ang Image Classifier na tumatakbo sa IoT Edge device.

## Gamitin ang IoT Edge classifier

Ang IoT device ay maaaring i-redirect upang gamitin ang IoT Edge image classifier. Ang URL para sa Image Classifier ay `http://<IP address o pangalan>/image`, palitan ang `<IP address o pangalan>` ng IP address o host name ng computer na tumatakbo sa IoT Edge.

### Gawain - gamitin ang IoT Edge classifier

1. Buksan ang proyekto ng `fruit-quality-detector` app kung hindi pa ito bukas.

1. Ang image classifier ay tumatakbo bilang isang REST API gamit ang HTTP, hindi HTTPS, kaya ang tawag ay kailangang gumamit ng WiFi client na gumagana lamang sa HTTP calls. Nangangahulugan ito na hindi kailangan ang sertipiko. Tanggalin ang `CERTIFICATE` mula sa file na `config.h`.

1. Ang prediction URL sa file na `config.h` ay kailangang i-update sa bagong URL. Maaari mo ring tanggalin ang `PREDICTION_KEY` dahil hindi na ito kailangan.

    ```cpp
    const char *PREDICTION_URL = "<URL>";
    ```

    Palitan ang `<URL>` ng URL para sa iyong classifier.

1. Sa `main.cpp`, baguhin ang include directive para sa WiFi Client Secure upang i-import ang standard na bersyon ng HTTP:

    ```cpp
    #include <WiFiClient.h>
    ```

1. Baguhin ang deklarasyon ng `WiFiClient` upang maging bersyon ng HTTP:

    ```cpp
    WiFiClient client;
    ```

1. Piliin ang linya na nagse-set ng sertipiko sa WiFi client. Tanggalin ang linya na `client.setCACert(CERTIFICATE);` mula sa function na `connectWiFi`.

1. Sa function na `classifyImage`, tanggalin ang linya na `httpClient.addHeader("Prediction-Key", PREDICTION_KEY);` na nagse-set ng prediction key sa header.

1. I-upload at patakbuhin ang iyong code. Itutok ang camera sa ilang prutas at pindutin ang C button. Makikita mo ang output sa serial monitor:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 Matatagpuan mo ang code na ito sa [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/wio-terminal) folder.

😀 Tagumpay ang iyong fruit quality classifier program!

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, pakitandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na dulot ng paggamit ng pagsasaling ito.