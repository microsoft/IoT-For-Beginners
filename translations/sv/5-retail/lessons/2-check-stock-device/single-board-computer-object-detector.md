<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a3fdfec1d1e2cb645ea11c2930b51299",
  "translation_date": "2025-08-27T22:20:41+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/single-board-computer-object-detector.md",
  "language_code": "sv"
}
-->
# Anropa din objektdetektor från din IoT-enhet - Virtuell IoT-hårdvara och Raspberry Pi

När din objektdetektor har publicerats kan den användas från din IoT-enhet.

## Kopiera bildklassificeringsprojektet

Majoriteten av din lagerdetektor är densamma som bildklassificeraren du skapade i en tidigare lektion.

### Uppgift - kopiera bildklassificeringsprojektet

1. Skapa en mapp som heter `stock-counter` antingen på din dator om du använder en virtuell IoT-enhet, eller på din Raspberry Pi. Om du använder en virtuell IoT-enhet, se till att du ställer in en virtuell miljö.

1. Ställ in kamerahårdvaran.

    * Om du använder en Raspberry Pi behöver du montera PiCamera. Du kanske också vill fixera kameran i en fast position, till exempel genom att hänga kabeln över en låda eller burk, eller fästa kameran på en låda med dubbelhäftande tejp.
    * Om du använder en virtuell IoT-enhet behöver du installera CounterFit och CounterFit PyCamera shim. Om du ska använda stillbilder, fånga några bilder som din objektdetektor inte har sett tidigare. Om du ska använda din webbkamera, se till att den är placerad så att den kan se det lager du försöker detektera.

1. Replikera stegen från [lektion 2 i tillverkningsprojektet](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) för att fånga bilder från kameran.

1. Replikera stegen från [lektion 2 i tillverkningsprojektet](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) för att anropa bildklassificeraren. Majoriteten av denna kod kommer att återanvändas för att detektera objekt.

## Ändra koden från en klassificerare till en objektdetektor

Koden du använde för att klassificera bilder är mycket lik koden för att detektera objekt. Den största skillnaden är metoden som anropas på Custom Vision SDK och resultaten av anropet.

### Uppgift - ändra koden från en klassificerare till en objektdetektor

1. Ta bort de tre raderna kod som klassificerar bilden och bearbetar förutsägelserna:

    ```python
    results = predictor.classify_image(project_id, iteration_name, image)
    
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Ta bort dessa tre rader.

1. Lägg till följande kod för att detektera objekt i bilden:

    ```python
    results = predictor.detect_image(project_id, iteration_name, image)

    threshold = 0.3
    
    predictions = list(prediction for prediction in results.predictions if prediction.probability > threshold)
    
    for prediction in predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Denna kod anropar metoden `detect_image` på prediktorn för att köra objektdetektorn. Den samlar sedan alla förutsägelser med en sannolikhet över en tröskel och skriver ut dem i konsolen.

    Till skillnad från en bildklassificerare som bara returnerar ett resultat per tag, kommer objektdetektorn att returnera flera resultat, så alla med låg sannolikhet måste filtreras bort.

1. Kör denna kod och den kommer att fånga en bild, skicka den till objektdetektorn och skriva ut de detekterade objekten. Om du använder en virtuell IoT-enhet, se till att du har en lämplig bild inställd i CounterFit, eller att din webbkamera är vald. Om du använder en Raspberry Pi, se till att din kamera pekar mot objekt på en hylla.

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   34.13%
    tomato paste:   33.95%
    tomato paste:   35.05%
    tomato paste:   32.80%
    ```

    > 💁 Du kan behöva justera `threshold` till ett lämpligt värde för dina bilder.

    Du kommer att kunna se bilden som togs och dessa värden i fliken **Predictions** i Custom Vision.

    ![4 burkar tomatpuré på en hylla med förutsägelser för de 4 detektionerna på 35.8%, 33.5%, 25.7% och 16.6%](../../../../../translated_images/sv/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.png)

> 💁 Du kan hitta denna kod i mappen [code-detect/pi](../../../../../5-retail/lessons/2-check-stock-device/code-detect/pi) eller [code-detect/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-detect/virtual-iot-device).

😀 Ditt lagerhanteringsprogram blev en framgång!

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, vänligen notera att automatiska översättningar kan innehålla fel eller felaktigheter. Det ursprungliga dokumentet på sitt originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.