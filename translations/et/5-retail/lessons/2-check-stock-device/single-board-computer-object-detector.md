# Kutsu oma objektidetektorit IoT-seadmest - Virtuaalne IoT-riistvara ja Raspberry Pi

Kui sinu objektidetektor on avaldatud, saab seda kasutada IoT-seadmest.

## Kopeeri pildiklassifitseerimise projekt

Enamik sinu laoseisu detektori koodist on sama, mis pildiklassifitseerija, mille lõid eelmises õppetükis.

### Ülesanne - kopeeri pildiklassifitseerimise projekt

1. Loo kaust nimega `stock-counter` kas oma arvutis, kui kasutad virtuaalset IoT-seadet, või Raspberry Pi-s. Kui kasutad virtuaalset IoT-seadet, veendu, et seadistad virtuaalse keskkonna.

1. Seadista kaamera riistvara.

    * Kui kasutad Raspberry Pi-d, pead paigaldama PiCamera. Võid kaamera fikseerida ühes asendis, näiteks riputades kaablit kasti või konservi kohale või kinnitades kaamera kasti külge kahepoolse teibiga.
    * Kui kasutad virtuaalset IoT-seadet, pead installima CounterFit ja CounterFit PyCamera shimi. Kui plaanid kasutada staatilisi pilte, tee mõned pildid, mida sinu objektidetektor pole veel näinud. Kui plaanid kasutada veebikaamerat, veendu, et see on paigutatud nii, et näeb tuvastatavat laoseisu.

1. Korda samme [tootmisprojekti 2. õppetükist](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device), et kaamerast pilte jäädvustada.

1. Korda samme [tootmisprojekti 2. õppetükist](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device), et kutsuda pildiklassifitseerijat. Enamik sellest koodist kasutatakse uuesti objektide tuvastamiseks.

## Muuda kood klassifitseerijast objektidetektoriks

Kood, mida kasutasid piltide klassifitseerimiseks, on väga sarnane koodile, mida kasutatakse objektide tuvastamiseks. Peamine erinevus on meetod, mida kutsutakse Custom Vision SDK-s, ja kõne tulemused.

### Ülesanne - muuda kood klassifitseerijast objektidetektoriks

1. Kustuta kolm koodirida, mis klassifitseerivad pildi ja töötlevad ennustusi:

    ```python
    results = predictor.classify_image(project_id, iteration_name, image)
    
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Eemalda need kolm rida.

1. Lisa järgmine kood, et tuvastada objekte pildil:

    ```python
    results = predictor.detect_image(project_id, iteration_name, image)

    threshold = 0.3
    
    predictions = list(prediction for prediction in results.predictions if prediction.probability > threshold)
    
    for prediction in predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    See kood kutsub `detect_image` meetodit prediktoril, et käivitada objektidetektor. Seejärel kogub kõik ennustused, mille tõenäosus ületab läve, ja prindib need konsooli.

    Erinevalt pildiklassifitseerijast, mis tagastab ainult ühe tulemuse iga sildi kohta, tagastab objektidetektor mitu tulemust, mistõttu tuleb madala tõenäosusega tulemused välja filtreerida.

1. Käivita see kood, mis jäädvustab pildi, saadab selle objektidetektorile ja prindib tuvastatud objektid. Kui kasutad virtuaalset IoT-seadet, veendu, et CounterFitis on seadistatud sobiv pilt või valitud veebikaamera. Kui kasutad Raspberry Pi-d, veendu, et kaamera on suunatud riiulil olevatele objektidele.

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   34.13%
    tomato paste:   33.95%
    tomato paste:   35.05%
    tomato paste:   32.80%
    ```

    > 💁 Võid vajadusel kohandada `threshold` väärtust, et see sobiks sinu piltidega.

    Saad vaadata tehtud pilti ja neid väärtusi **Predictions** vahekaardil Custom Visionis.

    ![4 tomatipasta purki riiulil koos ennustustega 35.8%, 33.5%, 25.7% ja 16.6%](../../../../../translated_images/et/custom-vision-stock-prediction.942266ab1bcca341.webp)

> 💁 Selle koodi leiad [code-detect/pi](../../../../../5-retail/lessons/2-check-stock-device/code-detect/pi) või [code-detect/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-detect/virtual-iot-device) kaustast.

😀 Sinu laoseisu loendamise programm oli edukas!

---

**Lahtiütlus**:  
See dokument on tõlgitud AI tõlketeenuse [Co-op Translator](https://github.com/Azure/co-op-translator) abil. Kuigi püüame tagada täpsust, palume arvestada, et automaatsed tõlked võivad sisaldada vigu või ebatäpsusi. Algne dokument selle algses keeles tuleks pidada autoriteetseks allikaks. Olulise teabe puhul soovitame kasutada professionaalset inimtõlget. Me ei vastuta selle tõlke kasutamisest tulenevate arusaamatuste või valesti tõlgenduste eest.