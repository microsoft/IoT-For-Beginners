<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "e5896207b304ce1abaf065b8acc0cc79",
  "translation_date": "2025-08-27T21:00:06+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/single-board-computer-classify-image.md",
  "language_code": "cs"
}
-->
# Klasifikace obrázku - Virtuální IoT hardware a Raspberry Pi

V této části lekce pošlete obrázek zachycený kamerou do služby Custom Vision, aby byl klasifikován.

## Odeslání obrázků do Custom Vision

Služba Custom Vision má Python SDK, které můžete použít ke klasifikaci obrázků.

### Úkol - odeslání obrázků do Custom Vision

1. Otevřete složku `fruit-quality-detector` ve VS Code. Pokud používáte virtuální IoT zařízení, ujistěte se, že virtuální prostředí běží v terminálu.

1. Python SDK pro odesílání obrázků do Custom Vision je dostupné jako balíček Pip. Nainstalujte ho pomocí následujícího příkazu:

    ```sh
    pip3 install azure-cognitiveservices-vision-customvision
    ```

1. Přidejte následující importy na začátek souboru `app.py`:

    ```python
    from msrest.authentication import ApiKeyCredentials
    from azure.cognitiveservices.vision.customvision.prediction import CustomVisionPredictionClient
    ```

    Tyto moduly z knihoven Custom Vision umožňují autentizaci pomocí predikčního klíče a poskytují klientskou třídu pro volání Custom Vision.

1. Přidejte následující kód na konec souboru:

    ```python
    prediction_url = '<prediction_url>'
    prediction_key = '<prediction key>'
    ```

    Nahraďte `<prediction_url>` URL adresou, kterou jste zkopírovali z dialogu *Prediction URL* dříve v této lekci. Nahraďte `<prediction key>` predikčním klíčem, který jste zkopírovali ze stejného dialogu.

1. URL adresa predikce, kterou poskytl dialog *Prediction URL*, je navržena pro přímé volání REST endpointu. Python SDK používá části této URL na různých místech. Přidejte následující kód, který rozloží tuto URL na potřebné části:

    ```python
    parts = prediction_url.split('/')
    endpoint = 'https://' + parts[2]
    project_id = parts[6]
    iteration_name = parts[9]
    ```

    Tento kód rozloží URL, extrahuje endpoint `https://<location>.api.cognitive.microsoft.com`, ID projektu a název publikované iterace.

1. Vytvořte objekt prediktoru pro provedení predikce pomocí následujícího kódu:

    ```python
    prediction_credentials = ApiKeyCredentials(in_headers={"Prediction-key": prediction_key})
    predictor = CustomVisionPredictionClient(endpoint, prediction_credentials)
    ```

    `prediction_credentials` obalí predikční klíč. Tyto údaje se pak použijí k vytvoření klientského objektu predikce, který ukazuje na endpoint.

1. Odešlete obrázek do Custom Vision pomocí následujícího kódu:

    ```python
    image.seek(0)
    results = predictor.classify_image(project_id, iteration_name, image)
    ```

    Tento kód vrátí obrázek na začátek a odešle ho klientovi predikce.

1. Nakonec zobrazte výsledky pomocí následujícího kódu:

    ```python
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Tento kód projde všechny vrácené predikce a zobrazí je v terminálu. Pravděpodobnosti jsou vráceny jako desetinná čísla od 0 do 1, kde 0 znamená 0% šanci na shodu s tagem a 1 znamená 100% šanci.

    > 💁 Klasifikátory obrázků vrátí procenta pro všechny tagy, které byly použity. Každý tag bude mít pravděpodobnost, že obrázek odpovídá danému tagu.

1. Spusťte svůj kód, s kamerou namířenou na nějaké ovoce, nebo na vhodnou sadu obrázků, nebo na ovoce viditelné na vaší webkameře, pokud používáte virtuální IoT hardware. Výstup uvidíte v konzoli:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

    Budete schopni vidět obrázek, který byl pořízen, a tyto hodnoty na záložce **Predictions** v Custom Vision.

    ![Banán v Custom Vision předpovězený jako zralý na 56,8 % a nezralý na 43,1 %](../../../../../translated_images/cs/custom-vision-banana-prediction.30cdff4e1d72db5d9a0be0193790a47c2b387da034e12dc1314dd57ca2131b59.png)

> 💁 Tento kód najdete ve složce [code-classify/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/pi) nebo [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/virtual-iot-device).

😀 Váš program pro klasifikaci kvality ovoce byl úspěšný!

---

**Upozornění**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). I když se snažíme o co největší přesnost, mějte prosím na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za závazný zdroj. Pro kritické informace doporučujeme profesionální lidský překlad. Neodpovídáme za jakékoli nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.