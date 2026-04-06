# Spusťte svůj detektor objektů z vašeho IoT zařízení - Wio Terminal

Jakmile je váš detektor objektů publikován, můžete jej použít na svém IoT zařízení.

## Zkopírujte projekt klasifikátoru obrázků

Většina vašeho detektoru zásob je stejná jako klasifikátor obrázků, který jste vytvořili v předchozí lekci.

### Úkol - zkopírujte projekt klasifikátoru obrázků

1. Připojte svůj ArduCam k Wio Terminalu podle kroků z [lekce 2 výrobního projektu](../../../4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md#task---connect-the-camera).

    Možná budete chtít kameru upevnit do jedné polohy, například zavěšením kabelu přes krabici nebo plechovku, nebo připevněním kamery na krabici pomocí oboustranné pásky.

1. Vytvořte zcela nový projekt pro Wio Terminal pomocí PlatformIO. Tento projekt nazvěte `stock-counter`.

1. Zopakujte kroky z [lekce 2 výrobního projektu](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) pro zachycení obrázků z kamery.

1. Zopakujte kroky z [lekce 2 výrobního projektu](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) pro volání klasifikátoru obrázků. Většina tohoto kódu bude znovu použita pro detekci objektů.

## Změňte kód z klasifikátoru na detektor obrázků

Kód, který jste použili pro klasifikaci obrázků, je velmi podobný kódu pro detekci objektů. Hlavní rozdíl je v URL, které jste získali z Custom Vision, a ve výsledcích volání.

### Úkol - změňte kód z klasifikátoru na detektor obrázků

1. Přidejte následující direktivu `include` na začátek souboru `main.cpp`:

    ```cpp
    #include <vector>
    ```

1. Přejmenujte funkci `classifyImage` na `detectStock`, a to jak název funkce, tak volání ve funkci `buttonPressed`.

1. Nad funkci `detectStock` deklarujte práh pro filtrování detekcí s nízkou pravděpodobností:

    ```cpp
    const float threshold = 0.3f;
    ```

    Na rozdíl od klasifikátoru obrázků, který vrací pouze jeden výsledek na štítek, detektor objektů vrací více výsledků, takže je třeba filtrovat ty s nízkou pravděpodobností.

1. Nad funkci `detectStock` deklarujte funkci pro zpracování predikcí:

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

    Tato funkce vezme seznam predikcí a vypíše je do sériového monitoru.

1. Ve funkci `detectStock` nahraďte obsah smyčky `for`, která prochází predikce, následujícím:

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

    Tato smyčka prochází predikce a porovnává pravděpodobnost s prahem. Všechny predikce s pravděpodobností vyšší než práh jsou přidány do `list` a předány funkci `processPredictions`.

1. Nahrajte a spusťte svůj kód. Namiřte kameru na objekty na polici a stiskněte tlačítko C. Výstup uvidíte v sériovém monitoru:

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

    > 💁 Možná budete muset upravit hodnotu `threshold` na vhodnou hodnotu pro vaše obrázky.

    Budete moci vidět obrázek, který byl pořízen, a tyto hodnoty na kartě **Predictions** v Custom Vision.

    ![4 plechovky rajčatového protlaku na polici s predikcemi pro 4 detekce: 35,8 %, 33,5 %, 25,7 % a 16,6 %](../../../../../translated_images/cs/custom-vision-stock-prediction.942266ab1bcca341.webp)

> 💁 Tento kód najdete ve složce [code-detect/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-detect/wio-terminal).

😀 Váš program pro počítání zásob byl úspěšný!

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). I když se snažíme o co největší přesnost, mějte prosím na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za závazný zdroj. Pro důležité informace doporučujeme profesionální lidský překlad. Neodpovídáme za žádná nedorozumění nebo nesprávné výklady vyplývající z použití tohoto překladu.