<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "e5896207b304ce1abaf065b8acc0cc79",
  "translation_date": "2025-08-27T20:59:35+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/single-board-computer-classify-image.md",
  "language_code": "sw"
}
-->
# Tambua Picha - Vifaa vya IoT vya Kijumla na Raspberry Pi

Katika sehemu hii ya somo, utatuma picha iliyokamatwa na kamera kwa huduma ya Custom Vision ili kuitambua.

## Tuma picha kwa Custom Vision

Huduma ya Custom Vision ina Python SDK unayoweza kutumia kutambua picha.

### Kazi - tuma picha kwa Custom Vision

1. Fungua folda ya `fruit-quality-detector` katika VS Code. Ikiwa unatumia kifaa cha IoT cha kijumla, hakikisha mazingira ya kijumla yanafanya kazi kwenye terminal.

1. Python SDK ya kutuma picha kwa Custom Vision inapatikana kama kifurushi cha Pip. Isakinishe kwa amri ifuatayo:

    ```sh
    pip3 install azure-cognitiveservices-vision-customvision
    ```

1. Ongeza kauli za uingizaji zifuatazo juu ya faili ya `app.py`:

    ```python
    from msrest.authentication import ApiKeyCredentials
    from azure.cognitiveservices.vision.customvision.prediction import CustomVisionPredictionClient
    ```

    Hii inaleta baadhi ya moduli kutoka maktaba za Custom Vision, moja ya kuidhinisha kwa kutumia prediction key, na nyingine ya kutoa darasa la prediction client ambalo linaweza kuita Custom Vision.

1. Ongeza msimbo ufuatao mwishoni mwa faili:

    ```python
    prediction_url = '<prediction_url>'
    prediction_key = '<prediction key>'
    ```

    Badilisha `<prediction_url>` na URL uliyokopi kutoka kwenye dialog ya *Prediction URL* mapema katika somo hili. Badilisha `<prediction key>` na prediction key uliyokopi kutoka dialog hiyo hiyo.

1. URL ya prediction iliyotolewa na dialog ya *Prediction URL* imeundwa kutumika wakati wa kuita REST endpoint moja kwa moja. Python SDK hutumia sehemu za URL katika maeneo tofauti. Ongeza msimbo ufuatao ili kugawanya URL hii katika sehemu zinazohitajika:

    ```python
    parts = prediction_url.split('/')
    endpoint = 'https://' + parts[2]
    project_id = parts[6]
    iteration_name = parts[9]
    ```

    Hii inagawanya URL, ikitoa endpoint ya `https://<location>.api.cognitive.microsoft.com`, ID ya mradi, na jina la iteration iliyochapishwa.

1. Unda kitu cha predictor ili kufanya prediction kwa msimbo ufuatao:

    ```python
    prediction_credentials = ApiKeyCredentials(in_headers={"Prediction-key": prediction_key})
    predictor = CustomVisionPredictionClient(endpoint, prediction_credentials)
    ```

    `prediction_credentials` hufunga prediction key. Hizi kisha hutumika kuunda kitu cha prediction client kinachoelekeza kwenye endpoint.

1. Tuma picha kwa Custom Vision kwa kutumia msimbo ufuatao:

    ```python
    image.seek(0)
    results = predictor.classify_image(project_id, iteration_name, image)
    ```

    Hii inarudisha picha mwanzoni, kisha inaituma kwa prediction client.

1. Hatimaye, onyesha matokeo kwa msimbo ufuatao:

    ```python
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Hii itapitia predictions zote zilizorejeshwa na kuzionyesha kwenye terminal. Uwezekano uliorejeshwa ni namba za pointi za kuelea kutoka 0-1, ambapo 0 ni asilimia 0 ya kufanana na tag, na 1 ni asilimia 100 ya kufanana.

    > 💁 Watambuzi wa picha watarudisha asilimia kwa tag zote zilizotumika. Kila tag itakuwa na uwezekano kwamba picha inafanana na tag hiyo.

1. Endesha msimbo wako, ukiwa na kamera yako ikielekea kwenye matunda fulani, au seti sahihi ya picha, au matunda yanayoonekana kwenye webcam yako ikiwa unatumia vifaa vya IoT vya kijumla. Utaona matokeo kwenye console:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

    Utaweza kuona picha iliyopigwa, na maadili haya katika tab ya **Predictions** kwenye Custom Vision.

    ![Ndizi katika Custom Vision imetabiriwa kuwa imeiva kwa 56.8% na haijaiva kwa 43.1%](../../../../../translated_images/sw/custom-vision-banana-prediction.30cdff4e1d72db5d9a0be0193790a47c2b387da034e12dc1314dd57ca2131b59.png)

> 💁 Unaweza kupata msimbo huu katika folda ya [code-classify/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/pi) au [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/virtual-iot-device).

😀 Programu yako ya kutambua ubora wa matunda imefanikiwa!

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya tafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafadhali fahamu kuwa tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati asilia katika lugha yake ya awali inapaswa kuchukuliwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.