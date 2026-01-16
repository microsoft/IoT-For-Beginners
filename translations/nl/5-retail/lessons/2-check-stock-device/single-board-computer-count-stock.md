<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9c4320311c0f2c1884a6a21265d98a51",
  "translation_date": "2025-08-27T20:31:01+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/single-board-computer-count-stock.md",
  "language_code": "nl"
}
-->
# Tel voorraad met je IoT-apparaat - Virtuele IoT-hardware en Raspberry Pi

Een combinatie van de voorspellingen en hun begrenzingskaders kan worden gebruikt om voorraad in een afbeelding te tellen.

## Begrenzingskaders weergeven

Als een nuttige stap voor foutopsporing kun je niet alleen de begrenzingskaders afdrukken, maar ze ook tekenen op de afbeelding die op de schijf is opgeslagen wanneer een afbeelding is vastgelegd.

### Taak - begrenzingskaders afdrukken

1. Zorg ervoor dat het `stock-counter`-project is geopend in VS Code en dat de virtuele omgeving is geactiveerd als je een virtueel IoT-apparaat gebruikt.

1. Wijzig de `print`-instructie in de `for`-lus naar het volgende om de begrenzingskaders naar de console af te drukken:

    ```python
    print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%\t{prediction.bounding_box}')
    ```

1. Voer de app uit met de camera gericht op wat voorraad op een plank. De begrenzingskaders worden naar de console afgedrukt, met waarden voor links, boven, breedte en hoogte van 0-1.

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   33.42%  {'additional_properties': {}, 'left': 0.3455171, 'top': 0.09916268, 'width': 0.14175442, 'height': 0.29405564}
    tomato paste:   34.41%  {'additional_properties': {}, 'left': 0.48283678, 'top': 0.10242918, 'width': 0.11782813, 'height': 0.27467814}
    tomato paste:   31.25%  {'additional_properties': {}, 'left': 0.4923783, 'top': 0.35007596, 'width': 0.13668466, 'height': 0.28304994}
    tomato paste:   31.05%  {'additional_properties': {}, 'left': 0.36416405, 'top': 0.37494493, 'width': 0.14024884, 'height': 0.26880276}
    ```

### Taak - begrenzingskaders tekenen op de afbeelding

1. Het Pip-pakket [Pillow](https://pypi.org/project/Pillow/) kan worden gebruikt om op afbeeldingen te tekenen. Installeer dit met het volgende commando:

    ```sh
    pip3 install pillow
    ```

    Als je een virtueel IoT-apparaat gebruikt, zorg er dan voor dat je dit uitvoert vanuit de geactiveerde virtuele omgeving.

1. Voeg de volgende importinstructie toe aan de bovenkant van het bestand `app.py`:

    ```python
    from PIL import Image, ImageDraw, ImageColor
    ```

    Dit importeert de code die nodig is om de afbeelding te bewerken.

1. Voeg de volgende code toe aan het einde van het bestand `app.py`:

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

    Deze code opent de afbeelding die eerder is opgeslagen voor bewerking. Vervolgens doorloopt het de voorspellingen, haalt de begrenzingskaders op en berekent de rechterondercoördinaat met behulp van de begrenzingskaderwaarden van 0-1. Deze worden vervolgens omgezet naar afbeeldingscoördinaten door te vermenigvuldigen met de relevante afmeting van de afbeelding. Bijvoorbeeld, als de linkerwaarde 0.5 was op een afbeelding die 600 pixels breed was, zou dit worden omgezet naar 300 (0.5 x 600 = 300).

    Elk begrenzingskader wordt met een rode lijn op de afbeelding getekend. Ten slotte wordt de bewerkte afbeelding opgeslagen, waarbij de originele afbeelding wordt overschreven.

1. Voer de app uit met de camera gericht op wat voorraad op een plank. Je zult het bestand `image.jpg` zien in de VS Code-verkenner, en je kunt het selecteren om de begrenzingskaders te bekijken.

    ![4 blikken tomatenpuree met begrenzingskaders rond elk blik](../../../../../translated_images/nl/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.webp)

## Voorraad tellen

In de afbeelding hierboven hebben de begrenzingskaders een kleine overlap. Als deze overlap veel groter was, zouden de begrenzingskaders mogelijk hetzelfde object aangeven. Om de objecten correct te tellen, moet je kaders met een significante overlap negeren.

### Taak - voorraad tellen met negeren van overlap

1. Het Pip-pakket [Shapely](https://pypi.org/project/Shapely/) kan worden gebruikt om de intersectie te berekenen. Als je een Raspberry Pi gebruikt, moet je eerst een bibliotheekafhankelijkheid installeren:

    ```sh
    sudo apt install libgeos-dev
    ```

1. Installeer het Shapely Pip-pakket:

    ```sh
    pip3 install shapely
    ```

    Als je een virtueel IoT-apparaat gebruikt, zorg er dan voor dat je dit uitvoert vanuit de geactiveerde virtuele omgeving.

1. Voeg de volgende importinstructie toe aan de bovenkant van het bestand `app.py`:

    ```python
    from shapely.geometry import Polygon
    ```

    Dit importeert de code die nodig is om polygonen te maken om overlap te berekenen.

1. Voeg boven de code die de begrenzingskaders tekent de volgende code toe:

    ```python
    overlap_threshold = 0.20
    ```

    Dit definieert het percentage overlap dat is toegestaan voordat de begrenzingskaders als hetzelfde object worden beschouwd. 0.20 definieert een overlap van 20%.

1. Om overlap te berekenen met Shapely, moeten de begrenzingskaders worden omgezet in Shapely-polygonen. Voeg de volgende functie toe om dit te doen:

    ```python
    def create_polygon(prediction):
        scale_left = prediction.bounding_box.left
        scale_top = prediction.bounding_box.top
        scale_right = prediction.bounding_box.left + prediction.bounding_box.width
        scale_bottom = prediction.bounding_box.top + prediction.bounding_box.height
    
        return Polygon([(scale_left, scale_top), (scale_right, scale_top), (scale_right, scale_bottom), (scale_left, scale_bottom)])
    ```

    Deze functie maakt een polygoon met behulp van het begrenzingskader van een voorspelling.

1. De logica voor het verwijderen van overlappende objecten omvat het vergelijken van alle begrenzingskaders. Als een paar voorspellingen begrenzingskaders heeft die meer dan de drempel overlappen, wordt een van de voorspellingen verwijderd. Om alle voorspellingen te vergelijken, vergelijk je voorspelling 1 met 2, 3, 4, enz., vervolgens 2 met 3, 4, enz. De volgende code doet dit:

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

    De overlap wordt berekend met behulp van de Shapely-methode `Polygon.intersection`, die een polygoon retourneert met de overlap. Het gebied wordt vervolgens berekend vanuit deze polygoon. Deze overlappendrempel is geen absolute waarde, maar moet een percentage zijn van het begrenzingskader. Daarom wordt het kleinste begrenzingskader gevonden, en de overlappendrempel wordt gebruikt om te berekenen welk gebied de overlap kan hebben om niet het percentage overlappendrempel van het kleinste begrenzingskader te overschrijden. Als de overlap dit overschrijdt, wordt de voorspelling gemarkeerd voor verwijdering.

    Zodra een voorspelling is gemarkeerd voor verwijdering, hoeft deze niet opnieuw te worden gecontroleerd, dus de interne lus breekt af om de volgende voorspelling te controleren. Je kunt geen items uit een lijst verwijderen terwijl je er doorheen iterereert, dus de begrenzingskaders die meer dan de drempel overlappen, worden toegevoegd aan de lijst `to_delete` en vervolgens aan het einde verwijderd.

    Ten slotte wordt het aantal voorraad naar de console afgedrukt. Dit kan vervolgens worden verzonden naar een IoT-service om te waarschuwen als de voorraadniveaus laag zijn. Al deze code bevindt zich vóór het tekenen van de begrenzingskaders, zodat je de voorraadvoorspellingen zonder overlap kunt zien op de gegenereerde afbeeldingen.

    > 💁 Dit is een zeer eenvoudige manier om overlap te verwijderen, waarbij alleen de eerste in een overlappend paar wordt verwijderd. Voor productiecode zou je hier meer logica willen toevoegen, zoals het overwegen van de overlap tussen meerdere objecten, of als één begrenzingskader volledig wordt ingesloten door een ander.

1. Voer de app uit met de camera gericht op wat voorraad op een plank. De uitvoer geeft het aantal begrenzingskaders aan zonder overlap die de drempel overschrijdt. Probeer de waarde van `overlap_threshold` aan te passen om te zien dat voorspellingen worden genegeerd.

> 💁 Je kunt deze code vinden in de map [code-count/pi](../../../../../5-retail/lessons/2-check-stock-device/code-count/pi) of [code-count/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-count/virtual-iot-device).

😀 Je voorraadtelprogramma was een succes!

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we ons best doen voor nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor kritieke informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor eventuele misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.