# Zavolajte svoj detektor objektov z IoT zariadenia - Virtuálne IoT zariadenie a Raspberry Pi

Keď je váš detektor objektov publikovaný, môžete ho používať zo svojho IoT zariadenia.

## Skopírujte projekt klasifikátora obrázkov

Väčšina vášho detektora zásob je rovnaká ako klasifikátor obrázkov, ktorý ste vytvorili v predchádzajúcej lekcii.

### Úloha - skopírujte projekt klasifikátora obrázkov

1. Vytvorte priečinok s názvom `stock-counter` buď na svojom počítači, ak používate virtuálne IoT zariadenie, alebo na svojom Raspberry Pi. Ak používate virtuálne IoT zariadenie, uistite sa, že ste nastavili virtuálne prostredie.

1. Nastavte hardvér kamery.

    * Ak používate Raspberry Pi, budete musieť pripojiť PiCamera. Možno budete chcieť kameru upevniť do jednej polohy, napríklad zavesením kábla cez škatuľu alebo plechovku, alebo upevnením kamery na škatuľu pomocou obojstrannej pásky.
    * Ak používate virtuálne IoT zariadenie, budete musieť nainštalovať CounterFit a CounterFit PyCamera shim. Ak plánujete používať statické obrázky, zachyťte niekoľko obrázkov, ktoré váš detektor objektov ešte nevidel. Ak plánujete používať webovú kameru, uistite sa, že je umiestnená tak, aby videla zásoby, ktoré detegujete.

1. Zopakujte kroky z [lekcie 2 výrobného projektu](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) na zachytenie obrázkov z kamery.

1. Zopakujte kroky z [lekcie 2 výrobného projektu](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) na zavolanie klasifikátora obrázkov. Väčšina tohto kódu sa znovu použije na detekciu objektov.

## Zmeňte kód z klasifikátora na detektor obrázkov

Kód, ktorý ste použili na klasifikáciu obrázkov, je veľmi podobný kódu na detekciu objektov. Hlavný rozdiel je v metóde volanej na Custom Vision SDK a v výsledkoch volania.

### Úloha - zmeňte kód z klasifikátora na detektor obrázkov

1. Odstráňte tri riadky kódu, ktoré klasifikujú obrázok a spracovávajú predpovede:

    ```python
    results = predictor.classify_image(project_id, iteration_name, image)
    
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Odstráňte tieto tri riadky.

1. Pridajte nasledujúci kód na detekciu objektov na obrázku:

    ```python
    results = predictor.detect_image(project_id, iteration_name, image)

    threshold = 0.3
    
    predictions = list(prediction for prediction in results.predictions if prediction.probability > threshold)
    
    for prediction in predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Tento kód volá metódu `detect_image` na prediktore, aby spustil detektor objektov. Následne zhromažďuje všetky predpovede s pravdepodobnosťou nad prahovou hodnotou a vypisuje ich do konzoly.

    Na rozdiel od klasifikátora obrázkov, ktorý vracia iba jeden výsledok na značku, detektor objektov vráti viacero výsledkov, takže všetky s nízkou pravdepodobnosťou musia byť odfiltrované.

1. Spustite tento kód a zachytí obrázok, odošle ho do detektora objektov a vypíše detegované objekty. Ak používate virtuálne IoT zariadenie, uistite sa, že máte v CounterFit nastavený vhodný obrázok alebo je vybraná vaša webová kamera. Ak používate Raspberry Pi, uistite sa, že vaša kamera smeruje na objekty na poličke.

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   34.13%
    tomato paste:   33.95%
    tomato paste:   35.05%
    tomato paste:   32.80%
    ```

    > 💁 Možno budete musieť upraviť hodnotu `threshold` na vhodnú hodnotu pre vaše obrázky.

    Budete môcť vidieť obrázok, ktorý bol zachytený, a tieto hodnoty na karte **Predictions** v Custom Vision.

    ![4 plechovky paradajkového pretlaku na poličke s predpoveďami pre 4 detekcie: 35,8 %, 33,5 %, 25,7 % a 16,6 %](../../../../../translated_images/sk/custom-vision-stock-prediction.942266ab1bcca341.webp)

> 💁 Tento kód nájdete v priečinku [code-detect/pi](../../../../../5-retail/lessons/2-check-stock-device/code-detect/pi) alebo [code-detect/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-detect/virtual-iot-device).

😀 Váš program na počítanie zásob bol úspešný!

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby AI prekladu [Co-op Translator](https://github.com/Azure/co-op-translator). Aj keď sa snažíme o presnosť, prosím, berte na vedomie, že automatizované preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho pôvodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nenesieme zodpovednosť za akékoľvek nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.