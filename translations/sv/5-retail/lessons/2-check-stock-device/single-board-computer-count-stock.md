<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9c4320311c0f2c1884a6a21265d98a51",
  "translation_date": "2025-08-27T22:18:33+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/single-board-computer-count-stock.md",
  "language_code": "sv"
}
-->
# Räkna lager från din IoT-enhet - Virtuell IoT-hårdvara och Raspberry Pi

En kombination av förutsägelser och deras begränsningsramar kan användas för att räkna lager i en bild.

## Visa begränsningsramar

Som ett användbart felsökningssteg kan du inte bara skriva ut begränsningsramarna, utan också rita dem på bilden som sparades på disk när en bild togs.

### Uppgift - skriv ut begränsningsramarna

1. Se till att projektet `stock-counter` är öppet i VS Code och att den virtuella miljön är aktiverad om du använder en virtuell IoT-enhet.

1. Ändra `print`-satsen i `for`-loopen till följande för att skriva ut begränsningsramarna till konsolen:

    ```python
    print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%\t{prediction.bounding_box}')
    ```

1. Kör appen med kameran riktad mot några varor på en hylla. Begränsningsramarna kommer att skrivas ut till konsolen, med värden för vänster, topp, bredd och höjd från 0-1.

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   33.42%  {'additional_properties': {}, 'left': 0.3455171, 'top': 0.09916268, 'width': 0.14175442, 'height': 0.29405564}
    tomato paste:   34.41%  {'additional_properties': {}, 'left': 0.48283678, 'top': 0.10242918, 'width': 0.11782813, 'height': 0.27467814}
    tomato paste:   31.25%  {'additional_properties': {}, 'left': 0.4923783, 'top': 0.35007596, 'width': 0.13668466, 'height': 0.28304994}
    tomato paste:   31.05%  {'additional_properties': {}, 'left': 0.36416405, 'top': 0.37494493, 'width': 0.14024884, 'height': 0.26880276}
    ```

### Uppgift - rita begränsningsramar på bilden

1. Pip-paketet [Pillow](https://pypi.org/project/Pillow/) kan användas för att rita på bilder. Installera detta med följande kommando:

    ```sh
    pip3 install pillow
    ```

    Om du använder en virtuell IoT-enhet, se till att köra detta från den aktiverade virtuella miljön.

1. Lägg till följande import-sats högst upp i filen `app.py`:

    ```python
    from PIL import Image, ImageDraw, ImageColor
    ```

    Detta importerar kod som behövs för att redigera bilden.

1. Lägg till följande kod i slutet av filen `app.py`:

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

    Denna kod öppnar bilden som sparades tidigare för redigering. Den loopar sedan genom förutsägelserna och hämtar begränsningsramarna, och beräknar den nedre högra koordinaten med hjälp av begränsningsramvärdena från 0-1. Dessa konverteras sedan till bildkoordinater genom att multiplicera med bildens relevanta dimension. Till exempel, om vänstervärdet var 0.5 på en bild som var 600 pixlar bred, skulle detta konverteras till 300 (0.5 x 600 = 300).

    Varje begränsningsram ritas på bilden med en röd linje. Slutligen sparas den redigerade bilden och ersätter den ursprungliga bilden.

1. Kör appen med kameran riktad mot några varor på en hylla. Du kommer att se filen `image.jpg` i VS Code Explorer, och du kommer att kunna välja den för att se begränsningsramarna.

    ![4 burkar tomatpuré med begränsningsramar runt varje burk](../../../../../translated_images/sv/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.webp)

## Räkna lager

I bilden ovan har begränsningsramarna en liten överlappning. Om denna överlappning var mycket större, kan begränsningsramarna indikera samma objekt. För att räkna objekten korrekt måste du ignorera ramar med en betydande överlappning.

### Uppgift - räkna lager och ignorera överlappning

1. Pip-paketet [Shapely](https://pypi.org/project/Shapely/) kan användas för att beräkna överlappning. Om du använder en Raspberry Pi måste du först installera ett biblioteksberoende:

    ```sh
    sudo apt install libgeos-dev
    ```

1. Installera Shapely Pip-paketet:

    ```sh
    pip3 install shapely
    ```

    Om du använder en virtuell IoT-enhet, se till att köra detta från den aktiverade virtuella miljön.

1. Lägg till följande import-sats högst upp i filen `app.py`:

    ```python
    from shapely.geometry import Polygon
    ```

    Detta importerar kod som behövs för att skapa polygoner för att beräkna överlappning.

1. Ovanför koden som ritar begränsningsramarna, lägg till följande kod:

    ```python
    overlap_threshold = 0.20
    ```

    Detta definierar den procentuella överlappning som tillåts innan begränsningsramarna anses vara samma objekt. 0.20 definierar en 20% överlappning.

1. För att beräkna överlappning med Shapely måste begränsningsramarna konverteras till Shapely-polygoner. Lägg till följande funktion för att göra detta:

    ```python
    def create_polygon(prediction):
        scale_left = prediction.bounding_box.left
        scale_top = prediction.bounding_box.top
        scale_right = prediction.bounding_box.left + prediction.bounding_box.width
        scale_bottom = prediction.bounding_box.top + prediction.bounding_box.height
    
        return Polygon([(scale_left, scale_top), (scale_right, scale_top), (scale_right, scale_bottom), (scale_left, scale_bottom)])
    ```

    Detta skapar en polygon med hjälp av begränsningsramen för en förutsägelse.

1. Logiken för att ta bort överlappande objekt innebär att jämföra alla begränsningsramar, och om några par av förutsägelser har begränsningsramar som överlappar mer än tröskelvärdet, ta bort en av förutsägelserna. För att jämföra alla förutsägelser jämför du förutsägelse 1 med 2, 3, 4, etc., sedan 2 med 3, 4, etc. Följande kod gör detta:

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

    Överlappningen beräknas med hjälp av Shapely-metoden `Polygon.intersection` som returnerar en polygon med överlappningen. Arean beräknas sedan från denna polygon. Denna överlappningströskel är inte ett absolut värde, utan måste vara en procentandel av begränsningsramen, så den minsta begränsningsramen hittas, och överlappningströskeln används för att beräkna vilken area överlappningen kan ha för att inte överskrida procentandelströskeln för den minsta begränsningsramen. Om överlappningen överskrider detta markeras förutsägelsen för borttagning.

    När en förutsägelse har markerats för borttagning behöver den inte kontrolleras igen, så den inre loopen bryts för att kontrollera nästa förutsägelse. Du kan inte ta bort objekt från en lista medan du itererar genom den, så begränsningsramarna som överlappar mer än tröskelvärdet läggs till i listan `to_delete`, och tas sedan bort i slutet.

    Slutligen skrivs lagerantalet ut till konsolen. Detta kan sedan skickas till en IoT-tjänst för att varna om lagernivåerna är låga. All denna kod är innan begränsningsramarna ritas, så du kommer att se lagerförutsägelser utan överlappningar på de genererade bilderna.

    > 💁 Detta är ett mycket enkelt sätt att ta bort överlappningar, där endast den första i ett överlappande par tas bort. För produktionskod skulle du vilja lägga till mer logik här, såsom att överväga överlappningar mellan flera objekt, eller om en begränsningsram är helt innesluten av en annan.

1. Kör appen med kameran riktad mot några varor på en hylla. Utdata kommer att indikera antalet begränsningsramar utan överlappningar som överskrider tröskelvärdet. Prova att justera värdet `overlap_threshold` för att se förutsägelser som ignoreras.

> 💁 Du kan hitta denna kod i mappen [code-count/pi](../../../../../5-retail/lessons/2-check-stock-device/code-count/pi) eller [code-count/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-count/virtual-iot-device).

😀 Ditt lagerräknarprogram blev en framgång!

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör det noteras att automatiserade översättningar kan innehålla fel eller brister. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.