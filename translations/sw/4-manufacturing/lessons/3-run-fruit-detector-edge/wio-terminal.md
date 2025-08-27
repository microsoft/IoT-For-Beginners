<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "48ac21ec80329c930db7b84bd6b592ec",
  "translation_date": "2025-08-27T20:52:03+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/wio-terminal.md",
  "language_code": "sw"
}
-->
# Tambua picha ukitumia kionyesha picha cha IoT Edge - Wio Terminal

Katika sehemu hii ya somo, utatumia Kionyesha Picha kinachoendesha kwenye kifaa cha IoT Edge.

## Tumia kionyesha picha cha IoT Edge

Kifaa cha IoT kinaweza kuelekezwa kutumia kionyesha picha cha IoT Edge. URL ya Kionyesha Picha ni `http://<IP address or name>/image`, ukibadilisha `<IP address or name>` na anwani ya IP au jina la mwenyeji wa kompyuta inayoendesha IoT Edge.

### Kazi - tumia kionyesha picha cha IoT Edge

1. Fungua mradi wa programu ya `fruit-quality-detector` ikiwa haujafunguliwa tayari.

1. Kionyesha picha kinaendesha kama REST API kwa kutumia HTTP, si HTTPS, kwa hivyo simu inahitaji kutumia mteja wa WiFi anayefanya kazi na simu za HTTP pekee. Hii inamaanisha cheti hakihitajiki. Futa `CERTIFICATE` kutoka kwenye faili ya `config.h`.

1. URL ya utabiri katika faili ya `config.h` inahitaji kusasishwa na URL mpya. Unaweza pia kufuta `PREDICTION_KEY` kwani hii haitahitajika.

    ```cpp
    const char *PREDICTION_URL = "<URL>";
    ```

    Badilisha `<URL>` na URL ya kionyesha picha chako.

1. Katika `main.cpp`, badilisha agizo la kujumuisha kwa WiFi Client Secure ili kuingiza toleo la kawaida la HTTP:

    ```cpp
    #include <WiFiClient.h>
    ```

1. Badilisha tamko la `WiFiClient` kuwa toleo la HTTP:

    ```cpp
    WiFiClient client;
    ```

1. Chagua mstari unaoweka cheti kwenye mteja wa WiFi. Ondoa mstari `client.setCACert(CERTIFICATE);` kutoka kwenye kazi ya `connectWiFi`.

1. Katika kazi ya `classifyImage`, ondoa mstari `httpClient.addHeader("Prediction-Key", PREDICTION_KEY);` unaoweka ufunguo wa utabiri kwenye kichwa.

1. Pakia na endesha msimbo wako. Elekeza kamera kwenye tunda fulani na bonyeza kitufe cha C. Utaona matokeo kwenye mfuatiliaji wa serial:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 Unaweza kupata msimbo huu kwenye folda ya [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/wio-terminal).

😀 Programu yako ya kutambua ubora wa matunda imefanikiwa!

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya kutafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafadhali fahamu kuwa tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuzingatiwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.