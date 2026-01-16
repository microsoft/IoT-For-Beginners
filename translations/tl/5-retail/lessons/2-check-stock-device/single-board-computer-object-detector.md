<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a3fdfec1d1e2cb645ea11c2930b51299",
  "translation_date": "2025-08-27T20:40:01+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/single-board-computer-object-detector.md",
  "language_code": "tl"
}
-->
# Tawagin ang iyong object detector mula sa iyong IoT device - Virtual IoT Hardware at Raspberry Pi

Kapag na-publish na ang iyong object detector, maaari na itong gamitin mula sa iyong IoT device.

## Kopyahin ang proyekto ng image classifier

Ang karamihan sa iyong stock detector ay pareho sa image classifier na ginawa mo sa nakaraang aralin.

### Gawain - kopyahin ang proyekto ng image classifier

1. Gumawa ng folder na tinatawag na `stock-counter` sa iyong computer kung gumagamit ka ng virtual IoT device, o sa iyong Raspberry Pi. Kung gumagamit ka ng virtual IoT device, siguraduhing mag-set up ng virtual environment.

1. I-set up ang hardware ng camera.

    * Kung gumagamit ka ng Raspberry Pi, kakailanganin mong ikabit ang PiCamera. Maaaring gusto mo ring ayusin ang camera sa isang posisyon, halimbawa, sa pamamagitan ng pagbitin ng cable sa ibabaw ng kahon o lata, o pagdikit ng camera sa isang kahon gamit ang double-sided tape.
    * Kung gumagamit ka ng virtual IoT device, kakailanganin mong i-install ang CounterFit at ang CounterFit PyCamera shim. Kung gagamit ka ng still images, kumuha ng mga larawan na hindi pa nakikita ng iyong object detector. Kung gagamit ka ng web cam, siguraduhing nakaposisyon ito nang maayos upang makita ang stock na iyong dini-detect.

1. Ulitin ang mga hakbang mula sa [aralin 2 ng manufacturing project](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) upang kumuha ng mga larawan mula sa camera.

1. Ulitin ang mga hakbang mula sa [aralin 2 ng manufacturing project](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) upang tawagin ang image classifier. Ang karamihan sa code na ito ay muling gagamitin upang mag-detect ng mga object.

## Baguhin ang code mula sa classifier patungo sa image detector

Ang code na ginamit mo upang mag-classify ng mga larawan ay halos pareho sa code para mag-detect ng mga object. Ang pangunahing pagkakaiba ay ang method na tinatawag sa Custom Vision SDK, at ang resulta ng tawag.

### Gawain - baguhin ang code mula sa classifier patungo sa image detector

1. Tanggalin ang tatlong linya ng code na nagka-classify ng larawan at nagpo-proseso ng mga prediction:

    ```python
    results = predictor.classify_image(project_id, iteration_name, image)
    
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Tanggalin ang tatlong linyang ito.

1. Idagdag ang sumusunod na code upang mag-detect ng mga object sa larawan:

    ```python
    results = predictor.detect_image(project_id, iteration_name, image)

    threshold = 0.3
    
    predictions = list(prediction for prediction in results.predictions if prediction.probability > threshold)
    
    for prediction in predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Ang code na ito ay tumatawag sa `detect_image` method sa predictor upang patakbuhin ang object detector. Kinokolekta nito ang lahat ng prediction na may probability na mas mataas sa threshold, at ipinapakita ang mga ito sa console.

    Hindi tulad ng image classifier na nagbibigay lamang ng isang resulta bawat tag, ang object detector ay nagbibigay ng maraming resulta, kaya kailangang i-filter ang mga may mababang probability.

1. Patakbuhin ang code na ito at ito ay kukuha ng larawan, ipadadala ito sa object detector, at ipapakita ang mga detected object. Kung gumagamit ka ng virtual IoT device, siguraduhing may angkop na larawan na naka-set sa CounterFit, o ang iyong web cam ay naka-select. Kung gumagamit ka ng Raspberry Pi, siguraduhing nakatutok ang iyong camera sa mga object sa isang shelf.

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   34.13%
    tomato paste:   33.95%
    tomato paste:   35.05%
    tomato paste:   32.80%
    ```

    > 💁 Maaaring kailanganin mong i-adjust ang `threshold` sa angkop na halaga para sa iyong mga larawan.

    Makikita mo ang larawang kinuha, at ang mga value na ito sa **Predictions** tab sa Custom Vision.

    ![4 na lata ng tomato paste sa isang shelf na may mga prediction para sa 4 na detection na 35.8%, 33.5%, 25.7% at 16.6%](../../../../../translated_images/tl/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.png)

> 💁 Makikita mo ang code na ito sa [code-detect/pi](../../../../../5-retail/lessons/2-check-stock-device/code-detect/pi) o [code-detect/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-detect/virtual-iot-device) folder.

😀 Tagumpay ang iyong stock counter program!

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na maaaring magmula sa paggamit ng pagsasaling ito.