<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "e5896207b304ce1abaf065b8acc0cc79",
  "translation_date": "2025-08-27T20:59:50+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/single-board-computer-classify-image.md",
  "language_code": "hu"
}
-->
# Kép osztályozása - Virtuális IoT hardver és Raspberry Pi

A lecke ezen részében a kamerával rögzített képet a Custom Vision szolgáltatásnak küldöd el osztályozásra.

## Képek küldése a Custom Vision szolgáltatásnak

A Custom Vision szolgáltatás rendelkezik egy Python SDK-val, amelyet képek osztályozására használhatsz.

### Feladat - képek küldése a Custom Vision szolgáltatásnak

1. Nyisd meg a `fruit-quality-detector` mappát a VS Code-ban. Ha virtuális IoT eszközt használsz, győződj meg róla, hogy a virtuális környezet fut a terminálban.

1. A Custom Vision-hoz szükséges Python SDK elérhető egy Pip csomagként. Telepítsd a következő paranccsal:

    ```sh
    pip3 install azure-cognitiveservices-vision-customvision
    ```

1. Add hozzá a következő import utasításokat az `app.py` fájl tetejére:

    ```python
    from msrest.authentication import ApiKeyCredentials
    from azure.cognitiveservices.vision.customvision.prediction import CustomVisionPredictionClient
    ```

    Ezek a Custom Vision könyvtárak néhány modulját hozzák be: az egyiket az előrejelzési kulccsal való hitelesítéshez, a másikat pedig egy előrejelzési kliens osztály biztosításához, amely hívni tudja a Custom Vision-t.

1. Add hozzá a következő kódot a fájl végéhez:

    ```python
    prediction_url = '<prediction_url>'
    prediction_key = '<prediction key>'
    ```

    Cseréld ki a `<prediction_url>` helyére azt az URL-t, amelyet korábban a *Prediction URL* párbeszédablakból másoltál. Helyettesítsd a `<prediction key>` helyére az előrejelzési kulcsot, amelyet ugyanebből a párbeszédablakból másoltál.

1. Az előrejelzési URL, amelyet a *Prediction URL* párbeszédablak biztosított, közvetlen REST végpont hívására lett tervezve. A Python SDK az URL különböző részeit használja. Add hozzá a következő kódot, hogy az URL-t a szükséges részekre bontsd:

    ```python
    parts = prediction_url.split('/')
    endpoint = 'https://' + parts[2]
    project_id = parts[6]
    iteration_name = parts[9]
    ```

    Ez az URL-t bontja szét, kinyerve az `https://<location>.api.cognitive.microsoft.com` végpontot, a projektazonosítót és a közzétett iteráció nevét.

1. Hozz létre egy előrejelző objektumot az előrejelzés végrehajtásához a következő kóddal:

    ```python
    prediction_credentials = ApiKeyCredentials(in_headers={"Prediction-key": prediction_key})
    predictor = CustomVisionPredictionClient(endpoint, prediction_credentials)
    ```

    A `prediction_credentials` az előrejelzési kulcsot csomagolja be. Ezeket használják egy előrejelzési kliens objektum létrehozásához, amely az adott végpontra mutat.

1. Küldd el a képet a Custom Vision szolgáltatásnak a következő kóddal:

    ```python
    image.seek(0)
    results = predictor.classify_image(project_id, iteration_name, image)
    ```

    Ez visszatekeri a képet az elejére, majd elküldi az előrejelzési kliensnek.

1. Végül jelenítsd meg az eredményeket a következő kóddal:

    ```python
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Ez végigmegy az összes visszakapott előrejelzésen, és megjeleníti őket a terminálon. Az előrejelzések 0 és 1 közötti lebegőpontos számok, ahol 0 azt jelenti, hogy 0% az esélye a címkének való megfelelésre, míg 1 azt jelenti, hogy 100%.

    > 💁 A képosztályozók visszaadják az összes használt címke százalékos értékeit. Minden címkéhez tartozik egy valószínűség, hogy a kép megfelel-e annak a címkének.

1. Futtasd a kódodat, miközben a kamerád gyümölcsre irányul, vagy egy megfelelő képkészletre, vagy gyümölcsre, amely látható a webkamerádon, ha virtuális IoT hardvert használsz. Az eredményt a konzolban fogod látni:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

    Látni fogod a készített képet, és ezeket az értékeket a **Predictions** fülön a Custom Vision-ben.

    ![Egy banán a Custom Vision-ben, érettként 56,8%-ra, éretlenként 43,1%-ra becsülve](../../../../../translated_images/hu/custom-vision-banana-prediction.30cdff4e1d72db5d9a0be0193790a47c2b387da034e12dc1314dd57ca2131b59.png)

> 💁 Ezt a kódot megtalálod a [code-classify/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/pi) vagy [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/virtual-iot-device) mappában.

😀 A gyümölcsminőség-ellenőrző programod sikeres volt!

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.