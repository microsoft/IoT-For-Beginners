<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4cf1421420a6fab9ab4f2c391bd523b7",
  "translation_date": "2025-08-27T20:46:32+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-object-detector.md",
  "language_code": "tl"
}
-->
# Tawagin ang iyong object detector mula sa iyong IoT device - Wio Terminal

Kapag na-publish na ang iyong object detector, maaari na itong gamitin mula sa iyong IoT device.

## Kopyahin ang proyekto ng image classifier

Ang karamihan sa iyong stock detector ay pareho sa image classifier na ginawa mo sa nakaraang aralin.

### Gawain - kopyahin ang proyekto ng image classifier

1. Ikonekta ang iyong ArduCam sa iyong Wio Terminal, sundan ang mga hakbang mula sa [aralin 2 ng manufacturing project](../../../4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md#task---connect-the-camera).

    Maaari mo ring ayusin ang camera sa isang posisyon, halimbawa, sa pamamagitan ng pagbitin ng cable sa ibabaw ng kahon o lata, o pagdikit ng camera sa kahon gamit ang double-sided tape.

1. Gumawa ng bagong proyekto para sa Wio Terminal gamit ang PlatformIO. Tawagin ang proyektong ito na `stock-counter`.

1. Ulitin ang mga hakbang mula sa [aralin 2 ng manufacturing project](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) upang kumuha ng mga larawan mula sa camera.

1. Ulitin ang mga hakbang mula sa [aralin 2 ng manufacturing project](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) upang tawagin ang image classifier. Ang karamihan sa code na ito ay muling gagamitin upang mag-detect ng mga object.

## Baguhin ang code mula sa classifier patungo sa image detector

Ang code na ginamit mo upang mag-classify ng mga larawan ay halos pareho sa code para mag-detect ng mga object. Ang pangunahing pagkakaiba ay ang URL na tinatawag na nakuha mo mula sa Custom Vision, at ang resulta ng tawag.

### Gawain - baguhin ang code mula sa classifier patungo sa image detector

1. Idagdag ang sumusunod na include directive sa itaas ng file na `main.cpp`:

    ```cpp
    #include <vector>
    ```

1. Palitan ang pangalan ng function na `classifyImage` sa `detectStock`, parehong pangalan ng function at ang tawag sa `buttonPressed` function.

1. Sa itaas ng function na `detectStock`, magdeklara ng threshold upang i-filter ang anumang detections na may mababang probability:

    ```cpp
    const float threshold = 0.3f;
    ```

    Hindi tulad ng image classifier na nagbabalik lamang ng isang resulta bawat tag, ang object detector ay magbabalik ng maraming resulta, kaya ang anumang may mababang probability ay kailangang i-filter.

1. Sa itaas ng function na `detectStock`, magdeklara ng function upang iproseso ang mga predictions:

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

    Kinukuha nito ang listahan ng mga predictions at ipinapakita ang mga ito sa serial monitor.

1. Sa function na `detectStock`, palitan ang nilalaman ng `for` loop na nag-loop sa mga predictions gamit ang sumusunod:

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

    Ang loop na ito ay nagko-compare ng probability sa threshold. Lahat ng predictions na may probability na mas mataas sa threshold ay idinadagdag sa isang `list` at ipinapasa sa function na `processPredictions`.

1. I-upload at patakbuhin ang iyong code. Itutok ang camera sa mga object sa isang shelf at pindutin ang C button. Makikita mo ang output sa serial monitor:

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

    > 💁 Maaaring kailanganin mong ayusin ang `threshold` sa naaangkop na halaga para sa iyong mga larawan.

    Makikita mo ang larawan na kinuha, at ang mga value na ito sa **Predictions** tab sa Custom Vision.

    ![4 na lata ng tomato paste sa isang shelf na may predictions para sa 4 na detections na 35.8%, 33.5%, 25.7% at 16.6%](../../../../../translated_images/tl/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.png)

> 💁 Makikita mo ang code na ito sa [code-detect/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-detect/wio-terminal) folder.

😀 Tagumpay ang iyong stock counter program!

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na maaaring magmula sa paggamit ng pagsasaling ito.