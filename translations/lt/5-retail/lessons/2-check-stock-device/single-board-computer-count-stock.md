<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9c4320311c0f2c1884a6a21265d98a51",
  "translation_date": "2025-08-28T20:16:25+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/single-board-computer-count-stock.md",
  "language_code": "lt"
}
-->
# Skaičiuokite atsargas iš savo IoT įrenginio - Virtuali IoT aparatinė įranga ir Raspberry Pi

Prognozių ir jų ribinių dėžių derinys gali būti naudojamas atsargoms paveikslėlyje suskaičiuoti.

## Rodykite ribines dėžes

Kaip naudingą derinimo žingsnį, galite ne tik atspausdinti ribines dėžes, bet ir nupiešti jas ant paveikslėlio, kuris buvo išsaugotas diske, kai buvo užfiksuotas vaizdas.

### Užduotis - atspausdinkite ribines dėžes

1. Įsitikinkite, kad projektas `stock-counter` yra atidarytas VS Code, ir virtuali aplinka yra aktyvuota, jei naudojate virtualų IoT įrenginį.

1. Pakeiskite `print` sakinį `for` cikle į šį, kad ribinės dėžės būtų atspausdintos konsolėje:

    ```python
    print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%\t{prediction.bounding_box}')
    ```

1. Paleiskite programą, nukreipdami kamerą į lentynoje esančias atsargas. Ribinės dėžės bus atspausdintos konsolėje su kairės, viršaus, pločio ir aukščio reikšmėmis nuo 0 iki 1.

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   33.42%  {'additional_properties': {}, 'left': 0.3455171, 'top': 0.09916268, 'width': 0.14175442, 'height': 0.29405564}
    tomato paste:   34.41%  {'additional_properties': {}, 'left': 0.48283678, 'top': 0.10242918, 'width': 0.11782813, 'height': 0.27467814}
    tomato paste:   31.25%  {'additional_properties': {}, 'left': 0.4923783, 'top': 0.35007596, 'width': 0.13668466, 'height': 0.28304994}
    tomato paste:   31.05%  {'additional_properties': {}, 'left': 0.36416405, 'top': 0.37494493, 'width': 0.14024884, 'height': 0.26880276}
    ```

### Užduotis - nupieškite ribines dėžes ant paveikslėlio

1. Pip paketas [Pillow](https://pypi.org/project/Pillow/) gali būti naudojamas piešti ant paveikslėlių. Įdiekite jį naudodami šią komandą:

    ```sh
    pip3 install pillow
    ```

    Jei naudojate virtualų IoT įrenginį, įsitikinkite, kad tai vykdote aktyvuotoje virtualioje aplinkoje.

1. Pridėkite šį importavimo sakinį į `app.py` failo viršų:

    ```python
    from PIL import Image, ImageDraw, ImageColor
    ```

    Tai importuoja kodą, reikalingą paveikslėliui redaguoti.

1. Pridėkite šį kodą į `app.py` failo pabaigą:

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

    Šis kodas atidaro anksčiau išsaugotą paveikslėlį redagavimui. Tada jis pereina per prognozes, gaudamas ribines dėžes, ir apskaičiuoja apatinį dešinįjį koordinatą, naudodamas ribinių dėžių reikšmes nuo 0 iki 1. Šios reikšmės konvertuojamos į paveikslėlio koordinates, padauginant iš atitinkamo paveikslėlio matmens. Pavyzdžiui, jei kairės reikšmė yra 0.5 paveikslėlyje, kurio plotis yra 600 pikselių, tai būtų konvertuojama į 300 (0.5 x 600 = 300).

    Kiekviena ribinė dėžė nupiešiama ant paveikslėlio naudojant raudoną liniją. Galiausiai redaguotas paveikslėlis išsaugomas, perrašant originalų paveikslėlį.

1. Paleiskite programą, nukreipdami kamerą į lentynoje esančias atsargas. VS Code naršyklėje pamatysite failą `image.jpg`, ir galėsite jį pasirinkti, kad pamatytumėte ribines dėžes.

    ![4 pomidorų pastos skardinės su ribinėmis dėžėmis aplink kiekvieną skardinę](../../../../../translated_images/lt/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.jpg)

## Skaičiuokite atsargas

Paveikslėlyje, parodytame aukščiau, ribinės dėžės šiek tiek persidengia. Jei šis persidengimas būtų daug didesnis, ribinės dėžės galėtų nurodyti tą patį objektą. Norint teisingai suskaičiuoti objektus, reikia ignoruoti dėžes su reikšmingu persidengimu.

### Užduotis - skaičiuokite atsargas ignoruodami persidengimą

1. Pip paketas [Shapely](https://pypi.org/project/Shapely/) gali būti naudojamas sankirtai apskaičiuoti. Jei naudojate Raspberry Pi, pirmiausia turėsite įdiegti bibliotekos priklausomybę:

    ```sh
    sudo apt install libgeos-dev
    ```

1. Įdiekite Shapely Pip paketą:

    ```sh
    pip3 install shapely
    ```

    Jei naudojate virtualų IoT įrenginį, įsitikinkite, kad tai vykdote aktyvuotoje virtualioje aplinkoje.

1. Pridėkite šį importavimo sakinį į `app.py` failo viršų:

    ```python
    from shapely.geometry import Polygon
    ```

    Tai importuoja kodą, reikalingą sukurti daugiakampius persidengimui apskaičiuoti.

1. Virš kodo, kuris piešia ribines dėžes, pridėkite šį kodą:

    ```python
    overlap_threshold = 0.20
    ```

    Tai apibrėžia leistiną persidengimo procentą, po kurio ribinės dėžės laikomos tuo pačiu objektu. 0.20 reiškia 20% persidengimą.

1. Norint apskaičiuoti persidengimą naudojant Shapely, ribinės dėžės turi būti konvertuotos į Shapely daugiakampius. Pridėkite šią funkciją, kad tai atliktumėte:

    ```python
    def create_polygon(prediction):
        scale_left = prediction.bounding_box.left
        scale_top = prediction.bounding_box.top
        scale_right = prediction.bounding_box.left + prediction.bounding_box.width
        scale_bottom = prediction.bounding_box.top + prediction.bounding_box.height
    
        return Polygon([(scale_left, scale_top), (scale_right, scale_top), (scale_right, scale_bottom), (scale_left, scale_bottom)])
    ```

    Tai sukuria daugiakampį, naudodamas prognozės ribinę dėžę.

1. Logika, skirta pašalinti persidengiančius objektus, apima visų ribinių dėžių palyginimą. Jei bet kuri pora prognozių turi ribines dėžes, kurios persidengia daugiau nei nustatyta riba, viena iš prognozių pašalinama. Norint palyginti visas prognozes, reikia palyginti prognozę 1 su 2, 3, 4 ir t. t., tada 2 su 3, 4 ir t. t. Šis kodas tai atlieka:

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

    Persidengimas apskaičiuojamas naudojant Shapely metodą `Polygon.intersection`, kuris grąžina daugiakampį su persidengimu. Plotas apskaičiuojamas iš šio daugiakampio. Ši persidengimo riba nėra absoliuti reikšmė, bet turi būti procentas ribinės dėžės, todėl randama mažiausia ribinė dėžė, ir persidengimo riba naudojama apskaičiuoti, koks plotas gali būti, kad neviršytų mažiausios ribinės dėžės persidengimo procento. Jei persidengimas viršija šią ribą, prognozė pažymima ištrynimui.

    Kai prognozė pažymėta ištrynimui, jos nebereikia tikrinti, todėl vidinis ciklas nutraukiamas, kad būtų tikrinama kita prognozė. Negalite ištrinti elementų iš sąrašo, kol per jį iteruojate, todėl ribinės dėžės, kurios persidengia daugiau nei nustatyta riba, pridedamos prie sąrašo `to_delete`, o tada ištrinamos pabaigoje.

    Galiausiai atsargų skaičius atspausdinamas konsolėje. Tai galėtų būti siunčiama į IoT paslaugą, kad būtų pranešta, jei atsargų lygis yra žemas. Visa ši logika yra prieš ribinių dėžių piešimą, todėl sugeneruotuose paveikslėliuose matysite prognozes be persidengimų.

    > 💁 Tai labai paprastas būdas pašalinti persidengimus, tiesiog pašalinant pirmąjį iš persidengiančios poros. Produkciniame kode norėtumėte pridėti daugiau logikos, pavyzdžiui, atsižvelgti į persidengimus tarp kelių objektų arba jei viena ribinė dėžė yra kitoje.

1. Paleiskite programą, nukreipdami kamerą į lentynoje esančias atsargas. Rezultatas parodys ribinių dėžių, kurios neviršija persidengimo ribos, skaičių. Pabandykite pakeisti `overlap_threshold` reikšmę, kad pamatytumėte, kaip prognozės ignoruojamos.

> 💁 Šį kodą galite rasti aplanke [code-count/pi](../../../../../5-retail/lessons/2-check-stock-device/code-count/pi) arba [code-count/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-count/virtual-iot-device).

😀 Jūsų atsargų skaičiavimo programa buvo sėkminga!

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama naudoti profesionalų žmogaus vertimą. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius dėl šio vertimo naudojimo.