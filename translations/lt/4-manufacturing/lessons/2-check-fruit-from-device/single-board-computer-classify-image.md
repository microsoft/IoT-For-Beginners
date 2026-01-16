<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "e5896207b304ce1abaf065b8acc0cc79",
  "translation_date": "2025-08-28T19:13:02+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/single-board-computer-classify-image.md",
  "language_code": "lt"
}
-->
# Klasifikuokite vaizdą - Virtuali IoT įranga ir Raspberry Pi

Šioje pamokos dalyje siųsite kamerą užfiksuotą vaizdą į „Custom Vision“ paslaugą, kad jis būtų klasifikuotas.

## Siųskite vaizdus į „Custom Vision“

„Custom Vision“ paslauga turi Python SDK, kurį galite naudoti vaizdų klasifikavimui.

### Užduotis - siųsti vaizdus į „Custom Vision“

1. Atidarykite aplanką `fruit-quality-detector` VS Code programoje. Jei naudojate virtualų IoT įrenginį, įsitikinkite, kad virtuali aplinka veikia terminale.

1. Python SDK, skirtas vaizdų siuntimui į „Custom Vision“, yra prieinamas kaip Pip paketas. Įdiekite jį naudodami šią komandą:

    ```sh
    pip3 install azure-cognitiveservices-vision-customvision
    ```

1. Pridėkite šiuos importavimo teiginius failo `app.py` viršuje:

    ```python
    from msrest.authentication import ApiKeyCredentials
    from azure.cognitiveservices.vision.customvision.prediction import CustomVisionPredictionClient
    ```

    Tai įtraukia kai kuriuos modulius iš „Custom Vision“ bibliotekų: vieną autentifikacijai su prognozavimo raktu, o kitą - prognozavimo klientų klasės, kuri gali skambinti „Custom Vision“, teikimui.

1. Pridėkite šį kodą failo pabaigoje:

    ```python
    prediction_url = '<prediction_url>'
    prediction_key = '<prediction key>'
    ```

    Pakeiskite `<prediction_url>` URL adresu, kurį nukopijavote iš *Prediction URL* dialogo anksčiau šioje pamokoje. Pakeiskite `<prediction key>` prognozavimo raktu, kurį nukopijavote iš to paties dialogo.

1. Prognozavimo URL, kurį pateikė *Prediction URL* dialogas, yra skirtas naudoti tiesiogiai skambinant REST galutiniam taškui. Python SDK naudoja dalis URL skirtingose vietose. Pridėkite šį kodą, kad suskaidytumėte šį URL į reikalingas dalis:

    ```python
    parts = prediction_url.split('/')
    endpoint = 'https://' + parts[2]
    project_id = parts[6]
    iteration_name = parts[9]
    ```

    Tai suskaido URL, išskirdamas galutinį tašką `https://<location>.api.cognitive.microsoft.com`, projekto ID ir paskelbtos iteracijos pavadinimą.

1. Sukurkite prognozavimo objektą, kad atliktumėte prognozę naudodami šį kodą:

    ```python
    prediction_credentials = ApiKeyCredentials(in_headers={"Prediction-key": prediction_key})
    predictor = CustomVisionPredictionClient(endpoint, prediction_credentials)
    ```

    `prediction_credentials` apgaubia prognozavimo raktą. Jie naudojami prognozavimo klientų objekto, nukreipto į galutinį tašką, sukūrimui.

1. Siųskite vaizdą į „Custom Vision“ naudodami šį kodą:

    ```python
    image.seek(0)
    results = predictor.classify_image(project_id, iteration_name, image)
    ```

    Tai grąžina vaizdą į pradžią, tada siunčia jį prognozavimo klientui.

1. Galiausiai, parodykite rezultatus naudodami šį kodą:

    ```python
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Tai pereis per visas grąžintas prognozes ir parodys jas terminale. Grąžintos tikimybės yra slankiojo kablelio skaičiai nuo 0 iki 1, kur 0 reiškia 0% tikimybę atitikti žymą, o 1 reiškia 100% tikimybę.

    > 💁 Vaizdų klasifikatoriai grąžins procentus visoms žymoms, kurios buvo naudojamos. Kiekviena žyma turės tikimybę, kad vaizdas atitinka tą žymą.

1. Paleiskite savo kodą, nukreipdami kamerą į vaisius, tinkamą vaizdų rinkinį arba vaisius, matomus jūsų internetinėje kameroje, jei naudojate virtualią IoT įrangą. Rezultatus pamatysite konsolėje:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

    Galėsite matyti užfiksuotą vaizdą ir šias reikšmes **Predictions** skirtuke „Custom Vision“.

    ![Bananas „Custom Vision“ klasifikuotas kaip prinokęs su 56.8% tikimybe ir neprinokęs su 43.1% tikimybe](../../../../../translated_images/lt/custom-vision-banana-prediction.30cdff4e1d72db5d9a0be0193790a47c2b387da034e12dc1314dd57ca2131b59.png)

> 💁 Šį kodą galite rasti aplanke [code-classify/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/pi) arba [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/virtual-iot-device).

😀 Jūsų vaisių kokybės klasifikavimo programa buvo sėkminga!

---

**Atsakomybės atsisakymas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama profesionali žmogaus vertimo paslauga. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius naudojant šį vertimą.