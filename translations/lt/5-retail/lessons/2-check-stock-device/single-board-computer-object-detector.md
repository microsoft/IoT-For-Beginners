<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a3fdfec1d1e2cb645ea11c2930b51299",
  "translation_date": "2025-08-28T20:18:00+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/single-board-computer-object-detector.md",
  "language_code": "lt"
}
-->
# Paleiskite savo objektų detektorių iš IoT įrenginio - Virtuali IoT aparatinė įranga ir Raspberry Pi

Kai jūsų objektų detektorius bus paskelbtas, jį bus galima naudoti iš jūsų IoT įrenginio.

## Nukopijuokite vaizdų klasifikatoriaus projektą

Didžioji dalis jūsų atsargų detektoriaus yra tokia pati kaip vaizdų klasifikatorius, kurį sukūrėte ankstesnėje pamokoje.

### Užduotis - nukopijuokite vaizdų klasifikatoriaus projektą

1. Sukurkite aplanką, pavadintą `stock-counter`, savo kompiuteryje, jei naudojate virtualų IoT įrenginį, arba savo Raspberry Pi. Jei naudojate virtualų IoT įrenginį, įsitikinkite, kad nustatėte virtualią aplinką.

1. Paruoškite kameros aparatinę įrangą.

    * Jei naudojate Raspberry Pi, turėsite prijungti PiCamera. Taip pat galite norėti pritvirtinti kamerą vienoje padėtyje, pavyzdžiui, pakabindami kabelį virš dėžutės ar skardinės arba pritvirtindami kamerą prie dėžutės su dvipuse lipnia juosta.
    * Jei naudojate virtualų IoT įrenginį, turėsite įdiegti CounterFit ir CounterFit PyCamera shim. Jei ketinate naudoti statinius vaizdus, užfiksuokite keletą vaizdų, kurių jūsų objektų detektorius dar nematė. Jei ketinate naudoti savo internetinę kamerą, įsitikinkite, kad ji yra tokioje padėtyje, kuri leidžia matyti aptinkamas atsargas.

1. Pakartokite veiksmus iš [gamybos projekto 2 pamokos](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device), kad užfiksuotumėte vaizdus iš kameros.

1. Pakartokite veiksmus iš [gamybos projekto 2 pamokos](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device), kad iškviestumėte vaizdų klasifikatorių. Didžioji dalis šio kodo bus panaudota objektų aptikimui.

## Pakeiskite kodą iš klasifikatoriaus į vaizdų detektorių

Kodas, kurį naudojote vaizdų klasifikavimui, yra labai panašus į kodą, skirtą objektų aptikimui. Pagrindinis skirtumas yra metodas, naudojamas Custom Vision SDK, ir skambučio rezultatai.

### Užduotis - pakeiskite kodą iš klasifikatoriaus į vaizdų detektorių

1. Ištrinkite tris kodo eilutes, kurios klasifikuoja vaizdą ir apdoroja prognozes:

    ```python
    results = predictor.classify_image(project_id, iteration_name, image)
    
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Pašalinkite šias tris eilutes.

1. Pridėkite šį kodą, kad aptiktumėte objektus vaizde:

    ```python
    results = predictor.detect_image(project_id, iteration_name, image)

    threshold = 0.3
    
    predictions = list(prediction for prediction in results.predictions if prediction.probability > threshold)
    
    for prediction in predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Šis kodas iškviečia `detect_image` metodą iš prognozuotojo, kad paleistų objektų detektorių. Tada jis surenka visas prognozes, kurių tikimybė viršija nustatytą ribą, ir išspausdina jas konsolėje.

    Skirtingai nuo vaizdų klasifikatoriaus, kuris grąžina tik vieną rezultatą kiekvienai žymai, objektų detektorius grąžins kelis rezultatus, todėl reikia atmesti tuos, kurių tikimybė yra maža.

1. Paleiskite šį kodą, ir jis užfiksuos vaizdą, išsiųs jį objektų detektoriui ir išspausdins aptiktus objektus. Jei naudojate virtualų IoT įrenginį, įsitikinkite, kad CounterFit yra nustatytas tinkamas vaizdas arba pasirinkta internetinė kamera. Jei naudojate Raspberry Pi, įsitikinkite, kad jūsų kamera nukreipta į lentynoje esančius objektus.

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   34.13%
    tomato paste:   33.95%
    tomato paste:   35.05%
    tomato paste:   32.80%
    ```

    > 💁 Gali prireikti sureguliuoti `threshold` reikšmę, kad ji atitiktų jūsų vaizdus.

    Galėsite matyti užfiksuotą vaizdą ir šias reikšmes **Predictions** skirtuke Custom Vision.

    ![4 pomidorų pastos skardinės lentynoje su prognozėmis apie 4 aptikimus: 35.8%, 33.5%, 25.7% ir 16.6%](../../../../../translated_images/lt/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.png)

> 💁 Šį kodą galite rasti [code-detect/pi](../../../../../5-retail/lessons/2-check-stock-device/code-detect/pi) arba [code-detect/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-detect/virtual-iot-device) aplankuose.

😀 Jūsų atsargų skaičiavimo programa buvo sėkminga!

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Dėl svarbios informacijos rekomenduojama profesionali žmogaus vertimo paslauga. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius naudojant šį vertimą.