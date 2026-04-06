# Zavolajte svoj detektor objektov z IoT zariadenia - Wio Terminal

Keď je váš detektor objektov publikovaný, môžete ho používať zo svojho IoT zariadenia.

## Skopírujte projekt klasifikátora obrázkov

Väčšina vášho detektora zásob je rovnaká ako klasifikátor obrázkov, ktorý ste vytvorili v predchádzajúcej lekcii.

### Úloha - skopírujte projekt klasifikátora obrázkov

1. Pripojte svoju ArduCam k Wio Terminalu podľa krokov z [lekcie 2 výrobného projektu](../../../4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md#task---connect-the-camera).

    Môžete tiež upevniť kameru do jednej polohy, napríklad zavesením kábla cez krabicu alebo plechovku, alebo pripevnením kamery na krabicu pomocou obojstrannej lepiacej pásky.

1. Vytvorte úplne nový projekt pre Wio Terminal pomocou PlatformIO. Nazvite tento projekt `stock-counter`.

1. Zopakujte kroky z [lekcie 2 výrobného projektu](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) na zachytenie obrázkov z kamery.

1. Zopakujte kroky z [lekcie 2 výrobného projektu](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) na zavolanie klasifikátora obrázkov. Väčšina tohto kódu bude znovu použitá na detekciu objektov.

## Zmeňte kód z klasifikátora na detektor obrázkov

Kód, ktorý ste použili na klasifikáciu obrázkov, je veľmi podobný kódu na detekciu objektov. Hlavný rozdiel je v URL, ktoré ste získali z Custom Vision, a výsledkoch volania.

### Úloha - zmeňte kód z klasifikátora na detektor obrázkov

1. Pridajte nasledujúci direktív na začiatok súboru `main.cpp`:

    ```cpp
    #include <vector>
    ```

1. Premenujte funkciu `classifyImage` na `detectStock`, a to ako názov funkcie, tak aj volanie vo funkcii `buttonPressed`.

1. Nad funkciou `detectStock` deklarujte prahovú hodnotu na filtrovanie detekcií s nízkou pravdepodobnosťou:

    ```cpp
    const float threshold = 0.3f;
    ```

    Na rozdiel od klasifikátora obrázkov, ktorý vracia iba jeden výsledok na značku, detektor objektov vráti viacero výsledkov, takže tie s nízkou pravdepodobnosťou je potrebné filtrovať.

1. Nad funkciou `detectStock` deklarujte funkciu na spracovanie predikcií:

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

    Táto funkcia vezme zoznam predikcií a vytlačí ich do sériového monitora.

1. Vo funkcii `detectStock` nahraďte obsah cyklu `for`, ktorý prechádza predikciami, nasledujúcim:

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

    Tento cyklus prechádza predikciami a porovnáva pravdepodobnosť s prahovou hodnotou. Všetky predikcie s pravdepodobnosťou vyššou ako prahová hodnota sa pridajú do zoznamu a odovzdajú funkcii `processPredictions`.

1. Nahrajte a spustite svoj kód. Namierte kameru na objekty na poličke a stlačte tlačidlo C. Výstup uvidíte v sériovom monitore:

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

    > 💁 Možno budete musieť upraviť hodnotu `threshold` na vhodnú hodnotu pre vaše obrázky.

    Budete môcť vidieť obrázok, ktorý bol zachytený, a tieto hodnoty na karte **Predictions** v Custom Vision.

    ![4 plechovky paradajkového pretlaku na poličke s predikciami pre 4 detekcie: 35.8%, 33.5%, 25.7% a 16.6%](../../../../../translated_images/sk/custom-vision-stock-prediction.942266ab1bcca341.webp)

> 💁 Tento kód nájdete v priečinku [code-detect/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-detect/wio-terminal).

😀 Váš program na počítanie zásob bol úspešný!

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby AI prekladu [Co-op Translator](https://github.com/Azure/co-op-translator). Hoci sa snažíme o presnosť, prosím, berte na vedomie, že automatizované preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho rodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nie sme zodpovední za akékoľvek nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.