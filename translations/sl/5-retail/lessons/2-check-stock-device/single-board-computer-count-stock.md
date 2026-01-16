<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9c4320311c0f2c1884a6a21265d98a51",
  "translation_date": "2025-08-28T14:29:46+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/single-board-computer-count-stock.md",
  "language_code": "sl"
}
-->
# Štetje zalog z vašo IoT napravo - Virtualna IoT strojna oprema in Raspberry Pi

Kombinacija napovedi in njihovih okvirjev (bounding boxes) se lahko uporabi za štetje zalog na sliki.

## Prikaz okvirjev (bounding boxes)

Kot korak za odpravljanje napak lahko ne samo izpišete okvirje, temveč jih tudi narišete na sliko, ki je bila shranjena na disk, ko je bila slika zajeta.

### Naloga - izpis okvirjev

1. Prepričajte se, da je projekt `stock-counter` odprt v VS Code in da je virtualno okolje aktivirano, če uporabljate virtualno IoT napravo.

1. Spremenite ukaz `print` v zanki `for` v naslednjega, da izpišete okvirje v konzolo:

    ```python
    print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%\t{prediction.bounding_box}')
    ```

1. Zaženite aplikacijo s kamero, usmerjeno na nekaj zalog na polici. Okvirji bodo izpisani v konzolo z vrednostmi za levo, zgornjo, širino in višino v razponu od 0 do 1.

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   33.42%  {'additional_properties': {}, 'left': 0.3455171, 'top': 0.09916268, 'width': 0.14175442, 'height': 0.29405564}
    tomato paste:   34.41%  {'additional_properties': {}, 'left': 0.48283678, 'top': 0.10242918, 'width': 0.11782813, 'height': 0.27467814}
    tomato paste:   31.25%  {'additional_properties': {}, 'left': 0.4923783, 'top': 0.35007596, 'width': 0.13668466, 'height': 0.28304994}
    tomato paste:   31.05%  {'additional_properties': {}, 'left': 0.36416405, 'top': 0.37494493, 'width': 0.14024884, 'height': 0.26880276}
    ```

### Naloga - risanje okvirjev na sliko

1. Paket Pip [Pillow](https://pypi.org/project/Pillow/) se lahko uporabi za risanje na slikah. Namestite ga z naslednjim ukazom:

    ```sh
    pip3 install pillow
    ```

    Če uporabljate virtualno IoT napravo, poskrbite, da to zaženete znotraj aktiviranega virtualnega okolja.

1. Dodajte naslednji ukaz za uvoz na vrh datoteke `app.py`:

    ```python
    from PIL import Image, ImageDraw, ImageColor
    ```

    Ta ukaz uvozi kodo, potrebno za urejanje slike.

1. Dodajte naslednjo kodo na konec datoteke `app.py`:

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

    Ta koda odpre prej shranjeno sliko za urejanje. Nato prehodi skozi napovedi, pridobi okvirje in izračuna spodnjo desno koordinato z uporabo vrednosti okvirja od 0 do 1. Te vrednosti se nato pretvorijo v koordinate slike z množenjem z ustrezno dimenzijo slike. Na primer, če je leva vrednost 0,5 na sliki, ki je široka 600 slikovnih pik, se to pretvori v 300 (0,5 x 600 = 300).

    Vsak okvir je narisan na sliko z rdečo črto. Na koncu se urejena slika shrani, pri čemer prepiše izvirno sliko.

1. Zaženite aplikacijo s kamero, usmerjeno na nekaj zalog na polici. Videli boste datoteko `image.jpg` v raziskovalcu VS Code in jo boste lahko izbrali za ogled okvirjev.

    ![4 pločevinke paradižnikove paste z okvirji okoli vsake pločevinke](../../../../../translated_images/sl/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.webp)

## Štetje zalog

Na zgornji sliki imajo okvirji majhno prekrivanje. Če bi bilo to prekrivanje veliko večje, bi okvirji lahko nakazovali isti predmet. Da bi pravilno prešteli predmete, morate ignorirati okvirje z znatnim prekrivanjem.

### Naloga - štetje zalog z ignoriranjem prekrivanja

1. Paket Pip [Shapely](https://pypi.org/project/Shapely/) se lahko uporabi za izračun preseka. Če uporabljate Raspberry Pi, boste morali najprej namestiti knjižnično odvisnost:

    ```sh
    sudo apt install libgeos-dev
    ```

1. Namestite paket Shapely:

    ```sh
    pip3 install shapely
    ```

    Če uporabljate virtualno IoT napravo, poskrbite, da to zaženete znotraj aktiviranega virtualnega okolja.

1. Dodajte naslednji ukaz za uvoz na vrh datoteke `app.py`:

    ```python
    from shapely.geometry import Polygon
    ```

    Ta ukaz uvozi kodo, potrebno za ustvarjanje poligonov za izračun prekrivanja.

1. Nad kodo, ki riše okvirje, dodajte naslednjo kodo:

    ```python
    overlap_threshold = 0.20
    ```

    Ta določa odstotek prekrivanja, ki je dovoljen, preden se okvirji štejejo za isti predmet. 0,20 določa 20-odstotno prekrivanje.

1. Za izračun prekrivanja z uporabo Shapely je treba okvirje pretvoriti v poligone Shapely. Dodajte naslednjo funkcijo za to:

    ```python
    def create_polygon(prediction):
        scale_left = prediction.bounding_box.left
        scale_top = prediction.bounding_box.top
        scale_right = prediction.bounding_box.left + prediction.bounding_box.width
        scale_bottom = prediction.bounding_box.top + prediction.bounding_box.height
    
        return Polygon([(scale_left, scale_top), (scale_right, scale_top), (scale_right, scale_bottom), (scale_left, scale_bottom)])
    ```

    Ta funkcija ustvari poligon z uporabo okvirja napovedi.

1. Logika za odstranjevanje prekrivajočih se predmetov vključuje primerjavo vseh okvirjev, in če ima kateri koli par napovedi okvirje, ki se prekrivajo več kot prag, izbrišite eno od napovedi. Za primerjavo vseh napovedi primerjate napoved 1 z 2, 3, 4 itd., nato 2 z 3, 4 itd. Naslednja koda to naredi:

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

    Prekrivanje se izračuna z metodo Shapely `Polygon.intersection`, ki vrne poligon, ki predstavlja prekrivanje. Površina se nato izračuna iz tega poligona. Ta prag prekrivanja ni absolutna vrednost, temveč mora biti odstotek okvirja, zato se najde najmanjši okvir, in prag prekrivanja se uporabi za izračun, kolikšna površina prekrivanja je dovoljena, da ne preseže odstotnega praga prekrivanja najmanjšega okvirja. Če prekrivanje preseže to vrednost, se napoved označi za izbris.

    Ko je napoved označena za izbris, je ni treba ponovno preverjati, zato se notranja zanka prekine, da preveri naslednjo napoved. Elementov iz seznama ni mogoče brisati med iteracijo, zato se okvirji, ki se prekrivajo več kot prag, dodajo na seznam `to_delete`, nato pa izbrišejo na koncu.

    Na koncu se število zalog izpiše v konzolo. To bi se nato lahko poslalo IoT storitvi za opozarjanje, če so zaloge nizke. Vsa ta koda je pred risanjem okvirjev, zato boste na ustvarjenih slikah videli napovedi zalog brez prekrivanj.

    > 💁 To je zelo preprost način za odstranjevanje prekrivanj, saj se odstrani le prvi v paru prekrivajočih se okvirjev. Za produkcijsko kodo bi želeli dodati več logike, kot je upoštevanje prekrivanj med več predmeti ali če je en okvir v celoti vsebovan v drugem.

1. Zaženite aplikacijo s kamero, usmerjeno na nekaj zalog na polici. Izhod bo pokazal število okvirjev brez prekrivanj, ki presegajo prag. Poskusite prilagoditi vrednost `overlap_threshold`, da vidite, kako se napovedi ignorirajo.

> 💁 To kodo lahko najdete v mapi [code-count/pi](../../../../../5-retail/lessons/2-check-stock-device/code-count/pi) ali [code-count/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-count/virtual-iot-device).

😀 Vaš program za štetje zalog je bil uspešen!

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem maternem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna napačna razumevanja ali napačne interpretacije, ki bi nastale zaradi uporabe tega prevoda.