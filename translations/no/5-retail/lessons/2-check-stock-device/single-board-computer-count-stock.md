<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9c4320311c0f2c1884a6a21265d98a51",
  "translation_date": "2025-08-27T22:19:14+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/single-board-computer-count-stock.md",
  "language_code": "no"
}
-->
# Tell lagerbeholdning fra IoT-enheten din - Virtuell IoT-maskinvare og Raspberry Pi

En kombinasjon av prediksjonene og deres avgrensningsbokser kan brukes til å telle lagerbeholdning i et bilde.

## Vis avgrensningsbokser

Som et nyttig feilsøkingssteg kan du ikke bare skrive ut avgrensningsboksene, men også tegne dem på bildet som ble lagret på disk da et bilde ble tatt.

### Oppgave - skriv ut avgrensningsboksene

1. Sørg for at prosjektet `stock-counter` er åpnet i VS Code, og at det virtuelle miljøet er aktivert hvis du bruker en virtuell IoT-enhet.

1. Endre `print`-setningen i `for`-løkken til følgende for å skrive ut avgrensningsboksene til konsollen:

    ```python
    print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%\t{prediction.bounding_box}')
    ```

1. Kjør appen med kameraet rettet mot noe lager på en hylle. Avgrensningsboksene vil bli skrevet ut til konsollen, med venstre, topp, bredde og høyde verdier fra 0-1.

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   33.42%  {'additional_properties': {}, 'left': 0.3455171, 'top': 0.09916268, 'width': 0.14175442, 'height': 0.29405564}
    tomato paste:   34.41%  {'additional_properties': {}, 'left': 0.48283678, 'top': 0.10242918, 'width': 0.11782813, 'height': 0.27467814}
    tomato paste:   31.25%  {'additional_properties': {}, 'left': 0.4923783, 'top': 0.35007596, 'width': 0.13668466, 'height': 0.28304994}
    tomato paste:   31.05%  {'additional_properties': {}, 'left': 0.36416405, 'top': 0.37494493, 'width': 0.14024884, 'height': 0.26880276}
    ```

### Oppgave - tegn avgrensningsboksene på bildet

1. Pip-pakken [Pillow](https://pypi.org/project/Pillow/) kan brukes til å tegne på bilder. Installer denne med følgende kommando:

    ```sh
    pip3 install pillow
    ```

    Hvis du bruker en virtuell IoT-enhet, sørg for å kjøre dette fra det aktiverte virtuelle miljøet.

1. Legg til følgende import-setning øverst i `app.py`-filen:

    ```python
    from PIL import Image, ImageDraw, ImageColor
    ```

    Dette importerer kode som trengs for å redigere bildet.

1. Legg til følgende kode på slutten av `app.py`-filen:

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

    Denne koden åpner bildet som ble lagret tidligere for redigering. Den går deretter gjennom prediksjonene, henter avgrensningsboksene, og beregner koordinatet nederst til høyre ved hjelp av verdiene fra avgrensningsboksene fra 0-1. Disse konverteres deretter til bildepiksler ved å multiplisere med den relevante dimensjonen til bildet. For eksempel, hvis venstre verdi var 0.5 på et bilde som var 600 piksler bredt, ville dette bli konvertert til 300 (0.5 x 600 = 300).

    Hver avgrensningsboks tegnes på bildet med en rød linje. Til slutt lagres det redigerte bildet, og det originale bildet overskrives.

1. Kjør appen med kameraet rettet mot noe lager på en hylle. Du vil se filen `image.jpg` i VS Code explorer, og du vil kunne velge den for å se avgrensningsboksene.

    ![4 bokser med tomatpuré med avgrensningsbokser rundt hver boks](../../../../../translated_images/no/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.jpg)

## Tell lagerbeholdning

I bildet vist ovenfor har avgrensningsboksene en liten overlapping. Hvis denne overlappingen var mye større, kan avgrensningsboksene indikere det samme objektet. For å telle objektene riktig, må du ignorere bokser med betydelig overlapping.

### Oppgave - tell lagerbeholdning og ignorer overlapping

1. Pip-pakken [Shapely](https://pypi.org/project/Shapely/) kan brukes til å beregne overlapping. Hvis du bruker en Raspberry Pi, må du først installere et bibliotekavhengighet:

    ```sh
    sudo apt install libgeos-dev
    ```

1. Installer Shapely Pip-pakken:

    ```sh
    pip3 install shapely
    ```

    Hvis du bruker en virtuell IoT-enhet, sørg for å kjøre dette fra det aktiverte virtuelle miljøet.

1. Legg til følgende import-setning øverst i `app.py`-filen:

    ```python
    from shapely.geometry import Polygon
    ```

    Dette importerer kode som trengs for å lage polygoner for å beregne overlapping.

1. Over koden som tegner avgrensningsboksene, legg til følgende kode:

    ```python
    overlap_threshold = 0.20
    ```

    Dette definerer prosentandelen overlapping som er tillatt før avgrensningsboksene anses som det samme objektet. 0.20 definerer en 20% overlapping.

1. For å beregne overlapping ved hjelp av Shapely, må avgrensningsboksene konverteres til Shapely-polygoner. Legg til følgende funksjon for å gjøre dette:

    ```python
    def create_polygon(prediction):
        scale_left = prediction.bounding_box.left
        scale_top = prediction.bounding_box.top
        scale_right = prediction.bounding_box.left + prediction.bounding_box.width
        scale_bottom = prediction.bounding_box.top + prediction.bounding_box.height
    
        return Polygon([(scale_left, scale_top), (scale_right, scale_top), (scale_right, scale_bottom), (scale_left, scale_bottom)])
    ```

    Dette lager et polygon ved hjelp av avgrensningsboksen til en prediksjon.

1. Logikken for å fjerne overlappende objekter innebærer å sammenligne alle avgrensningsboksene, og hvis noen par av prediksjoner har avgrensningsbokser som overlapper mer enn terskelen, slettes en av prediksjonene. For å sammenligne alle prediksjonene, sammenligner du prediksjon 1 med 2, 3, 4, osv., deretter 2 med 3, 4, osv. Følgende kode gjør dette:

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

    Overlappingen beregnes ved hjelp av Shapely-metoden `Polygon.intersection` som returnerer et polygon som har overlappingen. Arealet beregnes deretter fra dette polygonet. Denne overlappingsterskelen er ikke en absolutt verdi, men må være en prosentandel av avgrensningsboksen, så den minste avgrensningsboksen finnes, og overlappingsterskelen brukes til å beregne hvilket areal overlappingen kan ha for ikke å overskride prosentandelen overlappingsterskelen til den minste avgrensningsboksen. Hvis overlappingen overskrider dette, blir prediksjonen markert for sletting.

    Når en prediksjon er markert for sletting, trenger den ikke å bli sjekket igjen, så den indre løkken bryter ut for å sjekke neste prediksjon. Du kan ikke slette elementer fra en liste mens du itererer gjennom den, så avgrensningsboksene som overlapper mer enn terskelen legges til i listen `to_delete`, og slettes deretter til slutt.

    Til slutt skrives lagerbeholdningen ut til konsollen. Dette kan deretter sendes til en IoT-tjeneste for å varsle hvis lagerbeholdningen er lav. All denne koden er før avgrensningsboksene tegnes, så du vil se lagerprediksjonene uten overlappinger på de genererte bildene.

    > 💁 Dette er en veldig enkel måte å fjerne overlappinger på, ved bare å fjerne den første i et overlappende par. For produksjonskode vil du sannsynligvis legge til mer logikk her, som å vurdere overlappinger mellom flere objekter, eller hvis en avgrensningsboks er inneholdt av en annen.

1. Kjør appen med kameraet rettet mot noe lager på en hylle. Utdataene vil indikere antall avgrensningsbokser uten overlappinger som overskrider terskelen. Prøv å justere verdien `overlap_threshold` for å se prediksjoner bli ignorert.

> 💁 Du finner denne koden i mappen [code-count/pi](../../../../../5-retail/lessons/2-check-stock-device/code-count/pi) eller [code-count/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-count/virtual-iot-device).

😀 Programmet ditt for telling av lagerbeholdning var en suksess!

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.