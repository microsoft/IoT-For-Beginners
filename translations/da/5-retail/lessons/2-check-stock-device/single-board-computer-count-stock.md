<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9c4320311c0f2c1884a6a21265d98a51",
  "translation_date": "2025-08-27T22:18:53+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/single-board-computer-count-stock.md",
  "language_code": "da"
}
-->
# Tæl lager fra din IoT-enhed - Virtuel IoT-hardware og Raspberry Pi

En kombination af forudsigelserne og deres afgrænsningsbokse kan bruges til at tælle lager på et billede.

## Vis afgrænsningsbokse

Som et nyttigt fejlsøgningstrin kan du ikke kun udskrive afgrænsningsboksene, men også tegne dem på det billede, der blev gemt på disken, da et billede blev taget.

### Opgave - udskriv afgrænsningsboksene

1. Sørg for, at projektet `stock-counter` er åbent i VS Code, og at den virtuelle miljø er aktiveret, hvis du bruger en virtuel IoT-enhed.

1. Ændr `print`-sætningen i `for`-løkken til følgende for at udskrive afgrænsningsboksene til konsollen:

    ```python
    print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%\t{prediction.bounding_box}')
    ```

1. Kør appen med kameraet rettet mod noget lager på en hylde. Afgrænsningsboksene vil blive udskrevet til konsollen med venstre, top, bredde og højde værdier fra 0-1.

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   33.42%  {'additional_properties': {}, 'left': 0.3455171, 'top': 0.09916268, 'width': 0.14175442, 'height': 0.29405564}
    tomato paste:   34.41%  {'additional_properties': {}, 'left': 0.48283678, 'top': 0.10242918, 'width': 0.11782813, 'height': 0.27467814}
    tomato paste:   31.25%  {'additional_properties': {}, 'left': 0.4923783, 'top': 0.35007596, 'width': 0.13668466, 'height': 0.28304994}
    tomato paste:   31.05%  {'additional_properties': {}, 'left': 0.36416405, 'top': 0.37494493, 'width': 0.14024884, 'height': 0.26880276}
    ```

### Opgave - tegn afgrænsningsbokse på billedet

1. Pip-pakken [Pillow](https://pypi.org/project/Pillow/) kan bruges til at tegne på billeder. Installer denne med følgende kommando:

    ```sh
    pip3 install pillow
    ```

    Hvis du bruger en virtuel IoT-enhed, skal du sørge for at køre dette fra det aktiverede virtuelle miljø.

1. Tilføj følgende import-sætning øverst i filen `app.py`:

    ```python
    from PIL import Image, ImageDraw, ImageColor
    ```

    Dette importerer kode, der er nødvendig for at redigere billedet.

1. Tilføj følgende kode til slutningen af filen `app.py`:

    ```python
    with Image.open('image.jpg') as im:
        draw = ImageDraw.Draw(im)
    
        for prediction in predictions:
            scale_left = prediction.bounding_box.left
            scale_top = prediction.bounding_box.top
            scale_right = prediction.bounding_box.left + prediction.bounding_box.width
            scale_bottom = prediction.bounding_box.top + prediction.bounding_box.height
            
            left = scale_left * im.width
            top = scale_top * im.height
            right = scale_right * im.width
            bottom = scale_bottom * im.height
    
            draw.rectangle([left, top, right, bottom], outline=ImageColor.getrgb('red'), width=2)
    
        im.save('image.jpg')
    ```

    Denne kode åbner det billede, der tidligere blev gemt, for redigering. Den gennemløber derefter forudsigelserne, henter afgrænsningsboksene og beregner det nederste højre koordinat ved hjælp af afgrænsningsboksens værdier fra 0-1. Disse konverteres derefter til billedkoordinater ved at multiplicere med den relevante dimension af billedet. For eksempel, hvis venstre værdi var 0.5 på et billede, der var 600 pixels bredt, ville dette konvertere det til 300 (0.5 x 600 = 300).

    Hver afgrænsningsboks tegnes på billedet med en rød linje. Til sidst gemmes det redigerede billede, og det originale billede overskrives.

1. Kør appen med kameraet rettet mod noget lager på en hylde. Du vil se filen `image.jpg` i VS Code-udforskeren, og du vil kunne vælge den for at se afgrænsningsboksene.

    ![4 dåser tomatpuré med afgrænsningsbokse omkring hver dåse](../../../../../translated_images/da/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.jpg)

## Tæl lager

På billedet vist ovenfor har afgrænsningsboksene en lille overlapning. Hvis denne overlapning var meget større, kunne afgrænsningsboksene indikere det samme objekt. For at tælle objekterne korrekt skal du ignorere bokse med en betydelig overlapning.

### Opgave - tæl lager og ignorer overlapning

1. Pip-pakken [Shapely](https://pypi.org/project/Shapely/) kan bruges til at beregne overlapning. Hvis du bruger en Raspberry Pi, skal du først installere et bibliotek afhængighed:

    ```sh
    sudo apt install libgeos-dev
    ```

1. Installer Shapely Pip-pakken:

    ```sh
    pip3 install shapely
    ```

    Hvis du bruger en virtuel IoT-enhed, skal du sørge for at køre dette fra det aktiverede virtuelle miljø.

1. Tilføj følgende import-sætning øverst i filen `app.py`:

    ```python
    from shapely.geometry import Polygon
    ```

    Dette importerer kode, der er nødvendig for at oprette polygoner til beregning af overlapning.

1. Over koden, der tegner afgrænsningsboksene, tilføj følgende kode:

    ```python
    overlap_threshold = 0.20
    ```

    Dette definerer den procentvise overlapning, der er tilladt, før afgrænsningsboksene betragtes som det samme objekt. 0.20 definerer en 20% overlapning.

1. For at beregne overlapning ved hjælp af Shapely skal afgrænsningsboksene konverteres til Shapely-polygoner. Tilføj følgende funktion for at gøre dette:

    ```python
    def create_polygon(prediction):
        scale_left = prediction.bounding_box.left
        scale_top = prediction.bounding_box.top
        scale_right = prediction.bounding_box.left + prediction.bounding_box.width
        scale_bottom = prediction.bounding_box.top + prediction.bounding_box.height
    
        return Polygon([(scale_left, scale_top), (scale_right, scale_top), (scale_right, scale_bottom), (scale_left, scale_bottom)])
    ```

    Dette opretter en polygon ved hjælp af afgrænsningsboksen for en forudsigelse.

1. Logikken for at fjerne overlappende objekter indebærer at sammenligne alle afgrænsningsbokse, og hvis nogen par af forudsigelser har afgrænsningsbokse, der overlapper mere end tærsklen, slettes en af forudsigelserne. For at sammenligne alle forudsigelser sammenlignes forudsigelse 1 med 2, 3, 4 osv., derefter 2 med 3, 4 osv. Følgende kode gør dette:

    ```python
    to_delete = []

    for i in range(0, len(predictions)):
        polygon_1 = create_polygon(predictions[i])
    
        for j in range(i+1, len(predictions)):
            polygon_2 = create_polygon(predictions[j])
            overlap = polygon_1.intersection(polygon_2).area

            smallest_area = min(polygon_1.area, polygon_2.area)
    
            if overlap > (overlap_threshold * smallest_area):
                to_delete.append(predictions[i])
                break
    
    for d in to_delete:
        predictions.remove(d)

    print(f'Counted {len(predictions)} stock items')
    ```

    Overlapningen beregnes ved hjælp af Shapely-metoden `Polygon.intersection`, der returnerer en polygon, der har overlapningen. Arealet beregnes derefter fra denne polygon. Denne overlapningstærskel er ikke en absolut værdi, men skal være en procentdel af afgrænsningsboksen, så den mindste afgrænsningsboks findes, og overlapningstærsklen bruges til at beregne, hvilket areal overlapningen kan have for ikke at overskride procentdelen af overlapningstærsklen for den mindste afgrænsningsboks. Hvis overlapningen overstiger dette, markeres forudsigelsen til sletning.

    Når en forudsigelse er markeret til sletning, behøver den ikke at blive kontrolleret igen, så den indre løkke bryder ud for at kontrollere den næste forudsigelse. Du kan ikke slette elementer fra en liste, mens du itererer gennem den, så afgrænsningsboksene, der overlapper mere end tærsklen, tilføjes til listen `to_delete` og slettes derefter til sidst.

    Til sidst udskrives lageroptællingen til konsollen. Dette kunne derefter sendes til en IoT-tjeneste for at advare, hvis lagerbeholdningen er lav. Al denne kode er før afgrænsningsboksene tegnes, så du vil se lagerforudsigelser uden overlapninger på de genererede billeder.

    > 💁 Dette er en meget simpel måde at fjerne overlapninger på, hvor kun den første i et overlappende par fjernes. For produktionskode vil du sandsynligvis tilføje mere logik her, såsom at tage højde for overlapninger mellem flere objekter eller hvis en afgrænsningsboks er indeholdt i en anden.

1. Kør appen med kameraet rettet mod noget lager på en hylde. Outputtet vil indikere antallet af afgrænsningsbokse uden overlapninger, der overstiger tærsklen. Prøv at justere værdien `overlap_threshold` for at se forudsigelser blive ignoreret.

> 💁 Du kan finde denne kode i mappen [code-count/pi](../../../../../5-retail/lessons/2-check-stock-device/code-count/pi) eller [code-count/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-count/virtual-iot-device).

😀 Dit lageroptællingsprogram var en succes!

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi er ikke ansvarlige for eventuelle misforståelser eller fejltolkninger, der opstår som følge af brugen af denne oversættelse.