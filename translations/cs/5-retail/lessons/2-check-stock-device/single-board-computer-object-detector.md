<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a3fdfec1d1e2cb645ea11c2930b51299",
  "translation_date": "2025-08-27T22:47:22+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/single-board-computer-object-detector.md",
  "language_code": "cs"
}
-->
# Zavolejte detektor objektů ze svého IoT zařízení - Virtuální IoT hardware a Raspberry Pi

Jakmile je váš detektor objektů publikován, může být použit z vašeho IoT zařízení.

## Zkopírujte projekt klasifikátoru obrázků

Většina vašeho detektoru zásob je stejná jako klasifikátor obrázků, který jste vytvořili v předchozí lekci.

### Úkol - zkopírujte projekt klasifikátoru obrázků

1. Vytvořte složku nazvanou `stock-counter` buď na svém počítači, pokud používáte virtuální IoT zařízení, nebo na svém Raspberry Pi. Pokud používáte virtuální IoT zařízení, ujistěte se, že jste nastavili virtuální prostředí.

1. Nastavte hardware kamery.

    * Pokud používáte Raspberry Pi, budete muset připojit PiCamera. Můžete také chtít kameru upevnit na jedno místo, například zavěšením kabelu přes krabici nebo plechovku, nebo připevněním kamery na krabici pomocí oboustranné lepicí pásky.
    * Pokud používáte virtuální IoT zařízení, budete muset nainstalovat CounterFit a CounterFit PyCamera shim. Pokud budete používat statické obrázky, zachyťte některé obrázky, které váš detektor objektů ještě neviděl. Pokud budete používat webovou kameru, ujistěte se, že je umístěna tak, aby viděla zásoby, které detekujete.

1. Zopakujte kroky z [lekce 2 výrobního projektu](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) pro zachycení obrázků z kamery.

1. Zopakujte kroky z [lekce 2 výrobního projektu](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) pro volání klasifikátoru obrázků. Většina tohoto kódu bude znovu použita pro detekci objektů.

## Změňte kód z klasifikátoru na detektor obrázků

Kód, který jste použili pro klasifikaci obrázků, je velmi podobný kódu pro detekci objektů. Hlavní rozdíl je v metodě volané na Custom Vision SDK a výsledcích volání.

### Úkol - změňte kód z klasifikátoru na detektor obrázků

1. Smažte tři řádky kódu, které klasifikují obrázek a zpracovávají předpovědi:

    ```python
    results = predictor.classify_image(project_id, iteration_name, image)
    
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Odstraňte tyto tři řádky.

1. Přidejte následující kód pro detekci objektů na obrázku:

    ```python
    results = predictor.detect_image(project_id, iteration_name, image)

    threshold = 0.3
    
    predictions = list(prediction for prediction in results.predictions if prediction.probability > threshold)
    
    for prediction in predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Tento kód volá metodu `detect_image` na prediktoru, aby spustil detektor objektů. Poté shromáždí všechny předpovědi s pravděpodobností nad prahovou hodnotou a vypíše je do konzole.

    Na rozdíl od klasifikátoru obrázků, který vrací pouze jeden výsledek na štítek, detektor objektů vrátí více výsledků, takže je třeba filtrovat ty s nízkou pravděpodobností.

1. Spusťte tento kód, který zachytí obrázek, odešle ho do detektoru objektů a vypíše detekované objekty. Pokud používáte virtuální IoT zařízení, ujistěte se, že máte v CounterFit nastavený vhodný obrázek nebo je vybrána vaše webová kamera. Pokud používáte Raspberry Pi, ujistěte se, že vaše kamera míří na objekty na polici.

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   34.13%
    tomato paste:   33.95%
    tomato paste:   35.05%
    tomato paste:   32.80%
    ```

    > 💁 Možná budete muset upravit `threshold` na vhodnou hodnotu pro vaše obrázky.

    Budete schopni vidět obrázek, který byl pořízen, a tyto hodnoty na záložce **Predictions** v Custom Vision.

    ![4 plechovky rajčatového protlaku na polici s předpověďmi pro 4 detekce: 35,8 %, 33,5 %, 25,7 % a 16,6 %](../../../../../translated_images/cs/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.png)

> 💁 Tento kód najdete ve složce [code-detect/pi](../../../../../5-retail/lessons/2-check-stock-device/code-detect/pi) nebo [code-detect/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-detect/virtual-iot-device).

😀 Váš program pro počítání zásob byl úspěšný!

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). I když se snažíme o co největší přesnost, mějte prosím na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za závazný zdroj. Pro důležité informace doporučujeme profesionální lidský překlad. Neodpovídáme za žádná nedorozumění nebo nesprávné výklady vyplývající z použití tohoto překladu.