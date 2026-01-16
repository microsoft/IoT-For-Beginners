<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "e5896207b304ce1abaf065b8acc0cc79",
  "translation_date": "2025-10-11T11:48:21+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/single-board-computer-classify-image.md",
  "language_code": "et"
}
-->
# Klassifitseeri pilt - Virtuaalne IoT riistvara ja Raspberry Pi

Selles õppetunni osas saadad kaameraga tehtud pildi Custom Vision teenusele, et see klassifitseerida.

## Piltide saatmine Custom Vision teenusele

Custom Vision teenusel on Python SDK, mida saab kasutada piltide klassifitseerimiseks.

### Ülesanne - piltide saatmine Custom Vision teenusele

1. Ava `fruit-quality-detector` kaust VS Code'is. Kui kasutad virtuaalset IoT seadet, veendu, et virtuaalne keskkond töötab terminalis.

1. Python SDK piltide saatmiseks Custom Vision teenusele on saadaval Pip paketina. Paigalda see järgmise käsuga:

    ```sh
    pip3 install azure-cognitiveservices-vision-customvision
    ```

1. Lisa järgmised import-lauseid `app.py` faili algusesse:

    ```python
    from msrest.authentication import ApiKeyCredentials
    from azure.cognitiveservices.vision.customvision.prediction import CustomVisionPredictionClient
    ```

    See toob sisse mõned moodulid Custom Vision teekidest: ühe autentimiseks ennustusvõtmega ja teise ennustusklientide klassi jaoks, mis saab Custom Vision teenust kutsuda.

1. Lisa järgmine kood faili lõppu:

    ```python
    prediction_url = '<prediction_url>'
    prediction_key = '<prediction key>'
    ```

    Asenda `<prediction_url>` URL-iga, mille kopeerisid varem *Prediction URL* dialoogist. Asenda `<prediction key>` ennustusvõtmega, mille kopeerisid samast dialoogist.

1. Ennustus-URL, mille *Prediction URL* dialoog pakkus, on mõeldud REST-lõpppunkti otsekutsumiseks. Python SDK kasutab URL-i osi erinevates kohtades. Lisa järgmine kood, et jagada URL vajalikeks osadeks:

    ```python
    parts = prediction_url.split('/')
    endpoint = 'https://' + parts[2]
    project_id = parts[6]
    iteration_name = parts[9]
    ```

    See jagab URL-i, eraldades `https://<location>.api.cognitive.microsoft.com` lõpp-punkti, projekti ID ja avaldatud iteratsiooni nime.

1. Loo ennustaja objekt, et teha ennustus järgmise koodiga:

    ```python
    prediction_credentials = ApiKeyCredentials(in_headers={"Prediction-key": prediction_key})
    predictor = CustomVisionPredictionClient(endpoint, prediction_credentials)
    ```

    `prediction_credentials` kasutab ennustusvõtit. Neid kasutatakse ennustusklientide objekti loomiseks, mis osutab lõpp-punktile.

1. Saada pilt Custom Vision teenusele järgmise koodiga:

    ```python
    image.seek(0)
    results = predictor.classify_image(project_id, iteration_name, image)
    ```

    See kerib pildi tagasi algusesse ja saadab selle ennustusklientidele.

1. Lõpuks näita tulemusi järgmise koodiga:

    ```python
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    See käib läbi kõik tagastatud ennustused ja kuvab need terminalis. Tagastatud tõenäosused on ujukomaarvud vahemikus 0-1, kus 0 tähendab 0% tõenäosust, et pilt vastab sildile, ja 1 tähendab 100% tõenäosust.

    > 💁 Pildiklassifikaatorid tagastavad protsendid kõigi kasutatud siltide kohta. Iga sildi puhul on tõenäosus, et pilt vastab sellele sildile.

1. Käivita oma kood, suunates kaamera mõnele puuviljale, sobivale pildikomplektile või puuviljale, mis on nähtav veebikaameral, kui kasutad virtuaalset IoT riistvara. Näed väljundit konsoolis:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

    Saad näha tehtud pilti ja neid väärtusi **Predictions** vahekaardil Custom Vision teenuses.

    ![Banaan Custom Vision teenuses, ennustatud küps 56.8% ja toore 43.1%](../../../../../translated_images/et/custom-vision-banana-prediction.30cdff4e1d72db5d9a0be0193790a47c2b387da034e12dc1314dd57ca2131b59.png)

> 💁 Selle koodi leiad [code-classify/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/pi) või [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/virtual-iot-device) kaustast.

😀 Sinu puuvilja kvaliteedi klassifikaatori programm oli edukas!

---

**Lahtiütlus**:  
See dokument on tõlgitud AI tõlketeenuse [Co-op Translator](https://github.com/Azure/co-op-translator) abil. Kuigi püüame tagada täpsust, palume arvestada, et automaatsed tõlked võivad sisaldada vigu või ebatäpsusi. Algne dokument selle algses keeles tuleks pidada autoriteetseks allikaks. Olulise teabe puhul soovitame kasutada professionaalset inimtõlget. Me ei vastuta selle tõlke kasutamisest tulenevate arusaamatuste või valesti tõlgenduste eest.