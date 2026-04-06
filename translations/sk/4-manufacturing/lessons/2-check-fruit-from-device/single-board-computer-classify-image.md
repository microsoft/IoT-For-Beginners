# Klasifikácia obrázka - Virtuálny IoT hardvér a Raspberry Pi

V tejto časti lekcie pošlete obrázok zachytený kamerou do služby Custom Vision na jeho klasifikáciu.

## Odoslanie obrázkov do služby Custom Vision

Služba Custom Vision má Python SDK, ktoré môžete použiť na klasifikáciu obrázkov.

### Úloha - odoslanie obrázkov do služby Custom Vision

1. Otvorte priečinok `fruit-quality-detector` vo VS Code. Ak používate virtuálne IoT zariadenie, uistite sa, že virtuálne prostredie beží v termináli.

1. Python SDK na odosielanie obrázkov do služby Custom Vision je dostupné ako balíček Pip. Nainštalujte ho pomocou nasledujúceho príkazu:

    ```sh
    pip3 install azure-cognitiveservices-vision-customvision
    ```

1. Pridajte nasledujúce importy na začiatok súboru `app.py`:

    ```python
    from msrest.authentication import ApiKeyCredentials
    from azure.cognitiveservices.vision.customvision.prediction import CustomVisionPredictionClient
    ```

    Týmto sa načítajú niektoré moduly z knižníc Custom Vision, jeden na autentifikáciu pomocou predikčného kľúča a druhý na poskytnutie triedy klienta predikcie, ktorá môže volať službu Custom Vision.

1. Pridajte nasledujúci kód na koniec súboru:

    ```python
    prediction_url = '<prediction_url>'
    prediction_key = '<prediction key>'
    ```

    Nahraďte `<prediction_url>` URL adresou, ktorú ste skopírovali z dialógu *Prediction URL* skôr v tejto lekcii. Nahraďte `<prediction key>` predikčným kľúčom, ktorý ste skopírovali z rovnakého dialógu.

1. Predikčná URL adresa, ktorú poskytol dialóg *Prediction URL*, je navrhnutá na použitie pri priamom volaní REST endpointu. Python SDK používa časti tejto URL adresy na rôznych miestach. Pridajte nasledujúci kód na rozdelenie tejto URL adresy na potrebné časti:

    ```python
    parts = prediction_url.split('/')
    endpoint = 'https://' + parts[2]
    project_id = parts[6]
    iteration_name = parts[9]
    ```

    Tento kód rozdelí URL adresu a extrahuje endpoint `https://<location>.api.cognitive.microsoft.com`, ID projektu a názov publikovanej iterácie.

1. Vytvorte objekt prediktora na vykonanie predikcie pomocou nasledujúceho kódu:

    ```python
    prediction_credentials = ApiKeyCredentials(in_headers={"Prediction-key": prediction_key})
    predictor = CustomVisionPredictionClient(endpoint, prediction_credentials)
    ```

    `prediction_credentials` obalí predikčný kľúč. Tieto údaje sa potom použijú na vytvorenie objektu klienta predikcie, ktorý ukazuje na endpoint.

1. Pošlite obrázok do služby Custom Vision pomocou nasledujúceho kódu:

    ```python
    image.seek(0)
    results = predictor.classify_image(project_id, iteration_name, image)
    ```

    Tento kód vráti obrázok na začiatok a potom ho odošle klientovi predikcie.

1. Nakoniec zobrazte výsledky pomocou nasledujúceho kódu:

    ```python
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Tento kód prejde všetky predikcie, ktoré boli vrátené, a zobrazí ich v termináli. Pravdepodobnosti, ktoré sa vrátia, sú desatinné čísla od 0 do 1, kde 0 znamená 0% šancu na zhodu so značkou a 1 znamená 100% šancu.

    > 💁 Klasifikátory obrázkov vrátia percentá pre všetky značky, ktoré boli použité. Každá značka bude mať pravdepodobnosť, že obrázok zodpovedá tejto značke.

1. Spustite svoj kód, pričom kameru nasmerujte na nejaké ovocie, vhodnú sadu obrázkov alebo ovocie viditeľné na vašej webkamere, ak používate virtuálny IoT hardvér. Výstup uvidíte v konzole:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

    Budete môcť vidieť obrázok, ktorý bol zachytený, a tieto hodnoty na karte **Predictions** v službe Custom Vision.

    ![Banán v službe Custom Vision predikovaný ako zrelý na 56,8 % a nezrelý na 43,1 %](../../../../../translated_images/sk/custom-vision-banana-prediction.30cdff4e1d72db5d.webp)

> 💁 Tento kód nájdete v priečinku [code-classify/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/pi) alebo [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/virtual-iot-device).

😀 Váš program na klasifikáciu kvality ovocia bol úspešný!

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby AI prekladu [Co-op Translator](https://github.com/Azure/co-op-translator). Hoci sa snažíme o presnosť, prosím, berte na vedomie, že automatizované preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho rodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nie sme zodpovední za akékoľvek nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.