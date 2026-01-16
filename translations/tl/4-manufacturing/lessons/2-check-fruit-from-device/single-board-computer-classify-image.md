<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "e5896207b304ce1abaf065b8acc0cc79",
  "translation_date": "2025-08-27T21:01:02+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/single-board-computer-classify-image.md",
  "language_code": "tl"
}
-->
# Iklasipika ang isang imahe - Virtual na IoT Hardware at Raspberry Pi

Sa bahaging ito ng aralin, ipapadala mo ang imahe na kinunan ng camera sa Custom Vision service upang iklasipika ito.

## Magpadala ng mga imahe sa Custom Vision

Ang Custom Vision service ay may Python SDK na magagamit mo upang iklasipika ang mga imahe.

### Gawain - magpadala ng mga imahe sa Custom Vision

1. Buksan ang folder na `fruit-quality-detector` sa VS Code. Kung gumagamit ka ng virtual na IoT device, tiyaking tumatakbo ang virtual environment sa terminal.

1. Ang Python SDK para magpadala ng mga imahe sa Custom Vision ay magagamit bilang isang Pip package. I-install ito gamit ang sumusunod na utos:

    ```sh
    pip3 install azure-cognitiveservices-vision-customvision
    ```

1. Idagdag ang mga sumusunod na import statements sa itaas ng file na `app.py`:

    ```python
    from msrest.authentication import ApiKeyCredentials
    from azure.cognitiveservices.vision.customvision.prediction import CustomVisionPredictionClient
    ```

    Dinadala nito ang ilang modules mula sa Custom Vision libraries, isa para mag-authenticate gamit ang prediction key, at isa para magbigay ng prediction client class na maaaring tumawag sa Custom Vision.

1. Idagdag ang sumusunod na code sa dulo ng file:

    ```python
    prediction_url = '<prediction_url>'
    prediction_key = '<prediction key>'
    ```

    Palitan ang `<prediction_url>` ng URL na kinopya mo mula sa *Prediction URL* dialog kanina sa aralin. Palitan ang `<prediction key>` ng prediction key na kinopya mo mula sa parehong dialog.

1. Ang prediction URL na ibinigay ng *Prediction URL* dialog ay idinisenyo upang magamit kapag direktang tumatawag sa REST endpoint. Ginagamit ng Python SDK ang mga bahagi ng URL sa iba't ibang lugar. Idagdag ang sumusunod na code upang hatiin ang URL sa mga bahagi na kinakailangan:

    ```python
    parts = prediction_url.split('/')
    endpoint = 'https://' + parts[2]
    project_id = parts[6]
    iteration_name = parts[9]
    ```

    Hinahati nito ang URL, kinukuha ang endpoint na `https://<location>.api.cognitive.microsoft.com`, ang project ID, at ang pangalan ng published iteration.

1. Gumawa ng predictor object upang magsagawa ng prediction gamit ang sumusunod na code:

    ```python
    prediction_credentials = ApiKeyCredentials(in_headers={"Prediction-key": prediction_key})
    predictor = CustomVisionPredictionClient(endpoint, prediction_credentials)
    ```

    Ang `prediction_credentials` ay bumabalot sa prediction key. Ginagamit ang mga ito upang gumawa ng prediction client object na tumuturo sa endpoint.

1. Ipadala ang imahe sa Custom Vision gamit ang sumusunod na code:

    ```python
    image.seek(0)
    results = predictor.classify_image(project_id, iteration_name, image)
    ```

    Ibinabalik nito ang imahe sa simula, pagkatapos ay ipinapadala ito sa prediction client.

1. Sa wakas, ipakita ang mga resulta gamit ang sumusunod na code:

    ```python
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Iikot ito sa lahat ng predictions na naibalik at ipapakita ang mga ito sa terminal. Ang mga probabilities na naibalik ay floating point numbers mula 0-1, kung saan ang 0 ay nangangahulugang 0% na posibilidad na tumugma sa tag, at ang 1 ay nangangahulugang 100% na posibilidad.

    > 💁 Ang mga image classifiers ay magbabalik ng mga porsyento para sa lahat ng tags na ginamit. Ang bawat tag ay magkakaroon ng probability na ang imahe ay tumutugma sa tag na iyon.

1. Patakbuhin ang iyong code, na nakatutok ang iyong camera sa ilang prutas, o isang angkop na set ng imahe, o prutas na nakikita sa iyong webcam kung gumagamit ng virtual na IoT hardware. Makikita mo ang output sa console:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

    Makikita mo ang imahe na kinunan, at ang mga values na ito sa **Predictions** tab sa Custom Vision.

    ![Isang saging sa custom vision na na-predict na hinog sa 56.8% at hilaw sa 43.1%](../../../../../translated_images/tl/custom-vision-banana-prediction.30cdff4e1d72db5d9a0be0193790a47c2b387da034e12dc1314dd57ca2131b59.png)

> 💁 Matatagpuan mo ang code na ito sa folder na [code-classify/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/pi) o [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/virtual-iot-device).

😀 Tagumpay ang iyong programa sa pagklasipika ng kalidad ng prutas!

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, pakitandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na dulot ng paggamit ng pagsasaling ito.