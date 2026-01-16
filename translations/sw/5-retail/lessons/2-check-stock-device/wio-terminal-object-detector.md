<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4cf1421420a6fab9ab4f2c391bd523b7",
  "translation_date": "2025-08-27T22:43:30+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-object-detector.md",
  "language_code": "sw"
}
-->
# Piga Kichunguzi Chako cha Vitu Kutoka Kifaa Chako cha IoT - Wio Terminal

Baada ya kuchapisha kichunguzi chako cha vitu, unaweza kukitumia kutoka kwenye kifaa chako cha IoT.

## Nakili Mradi wa Kichunguzi cha Picha

Sehemu kubwa ya kichunguzi chako cha hisa ni sawa na kichunguzi cha picha ulichounda katika somo la awali.

### Kazi - nakili mradi wa kichunguzi cha picha

1. Unganisha ArduCam yako na Wio Terminal yako, ukifuata hatua kutoka [somo la 2 la mradi wa utengenezaji](../../../4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md#task---connect-the-camera).

   Unaweza pia kutaka kurekebisha kamera katika nafasi moja, kwa mfano, kwa kuning'iniza kebo juu ya sanduku au kopo, au kuifunga kamera kwenye sanduku kwa kutumia mkanda wa pande mbili.

1. Unda mradi mpya wa Wio Terminal ukitumia PlatformIO. Ita mradi huu `stock-counter`.

1. Rudia hatua kutoka [somo la 2 la mradi wa utengenezaji](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) ili kunasa picha kutoka kwenye kamera.

1. Rudia hatua kutoka [somo la 2 la mradi wa utengenezaji](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) ili kuita kichunguzi cha picha. Sehemu kubwa ya msimbo huu itatumika tena kugundua vitu.

## Badilisha Msimbo Kutoka Kichunguzi cha Picha Hadi Kichunguzi cha Vitu

Msimbo uliotumia kuainisha picha unafanana sana na msimbo wa kugundua vitu. Tofauti kuu ni URL inayotumika ambayo uliipata kutoka Custom Vision, na matokeo ya mwito huo.

### Kazi - badilisha msimbo kutoka kichunguzi cha picha hadi kichunguzi cha vitu

1. Ongeza agizo lifuatalo la kujumuisha juu ya faili ya `main.cpp`:

    ```cpp
    #include <vector>
    ```

1. Badilisha jina la kazi `classifyImage` kuwa `detectStock`, jina la kazi na mwito wake katika kazi ya `buttonPressed`.

1. Juu ya kazi ya `detectStock`, tangaza kizingiti cha kuchuja matokeo yoyote yenye uwezekano mdogo:

    ```cpp
    const float threshold = 0.3f;
    ```

    Tofauti na kichunguzi cha picha ambacho kinarejesha matokeo moja tu kwa kila lebo, kichunguzi cha vitu kitarudisha matokeo mengi, hivyo yoyote yenye uwezekano mdogo yanapaswa kuchujwa.

1. Juu ya kazi ya `detectStock`, tangaza kazi ya kushughulikia utabiri:

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

    Hii inachukua orodha ya utabiri na kuyachapisha kwenye mfuatiliaji wa serial.

1. Katika kazi ya `detectStock`, badilisha yaliyomo kwenye kitanzi cha `for` kinachopitia utabiri kwa yafuatayo:

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

    Hii inapitia utabiri, ikilinganishwa uwezekano na kizingiti. Utabiri wote wenye uwezekano wa juu kuliko kizingiti huongezwa kwenye `list` na kupitishwa kwa kazi ya `processPredictions`.

1. Pakia na endesha msimbo wako. Elekeza kamera kwenye vitu vilivyoko kwenye rafu na bonyeza kitufe cha C. Utaona matokeo kwenye mfuatiliaji wa serial:

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

    > 💁 Unaweza kuhitaji kurekebisha `threshold` hadi thamani inayofaa kwa picha zako.

    Utaweza kuona picha iliyopigwa, na maadili haya kwenye kichupo cha **Predictions** katika Custom Vision.

    ![Kopo 4 za tomato paste kwenye rafu na utabiri wa 4 wenye asilimia 35.8%, 33.5%, 25.7% na 16.6%](../../../../../translated_images/sw/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.png)

> 💁 Unaweza kupata msimbo huu kwenye folda ya [code-detect/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-detect/wio-terminal).

😀 Programu yako ya kuhesabu hisa imefanikiwa!

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya tafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kwa usahihi, tafadhali fahamu kuwa tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuzingatiwa kama chanzo cha mamlaka. Kwa taarifa muhimu, inashauriwa kutumia tafsiri ya kitaalamu ya binadamu. Hatutawajibika kwa maelewano mabaya au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.