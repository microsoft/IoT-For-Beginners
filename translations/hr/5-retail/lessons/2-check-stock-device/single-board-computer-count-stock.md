<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9c4320311c0f2c1884a6a21265d98a51",
  "translation_date": "2025-08-28T14:29:21+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/single-board-computer-count-stock.md",
  "language_code": "hr"
}
-->
# Brojanje zaliha s vašeg IoT uređaja - Virtualni IoT hardver i Raspberry Pi

Kombinacija predikcija i njihovih okvira može se koristiti za brojanje zaliha na slici.

## Prikaz okvira

Kao korak za otklanjanje pogrešaka, možete ne samo ispisati okvire, već ih i nacrtati na slici koja je spremljena na disk kada je slika snimljena.

### Zadatak - ispis okvira

1. Provjerite je li projekt `stock-counter` otvoren u VS Code-u i je li virtualno okruženje aktivirano ako koristite virtualni IoT uređaj.

1. Promijenite naredbu `print` u petlji `for` u sljedeće kako biste ispisali okvire u konzolu:

    ```python
    print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%\t{prediction.bounding_box}')
    ```

1. Pokrenite aplikaciju s kamerom usmjerenom prema zalihama na polici. Okviri će biti ispisani u konzolu s vrijednostima za lijevo, vrh, širinu i visinu od 0-1.

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   33.42%  {'additional_properties': {}, 'left': 0.3455171, 'top': 0.09916268, 'width': 0.14175442, 'height': 0.29405564}
    tomato paste:   34.41%  {'additional_properties': {}, 'left': 0.48283678, 'top': 0.10242918, 'width': 0.11782813, 'height': 0.27467814}
    tomato paste:   31.25%  {'additional_properties': {}, 'left': 0.4923783, 'top': 0.35007596, 'width': 0.13668466, 'height': 0.28304994}
    tomato paste:   31.05%  {'additional_properties': {}, 'left': 0.36416405, 'top': 0.37494493, 'width': 0.14024884, 'height': 0.26880276}
    ```

### Zadatak - crtanje okvira na slici

1. Pip paket [Pillow](https://pypi.org/project/Pillow/) može se koristiti za crtanje na slikama. Instalirajte ga sljedećom naredbom:

    ```sh
    pip3 install pillow
    ```

    Ako koristite virtualni IoT uređaj, provjerite je li ovo pokrenuto unutar aktiviranog virtualnog okruženja.

1. Dodajte sljedeću naredbu za uvoz na vrh datoteke `app.py`:

    ```python
    from PIL import Image, ImageDraw, ImageColor
    ```

    Ovo uvozi kod potreban za uređivanje slike.

1. Dodajte sljedeći kod na kraj datoteke `app.py`:

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

    Ovaj kod otvara sliku koja je ranije spremljena za uređivanje. Zatim prolazi kroz predikcije, dobiva okvire i izračunava donju desnu koordinatu koristeći vrijednosti okvira od 0-1. Te se vrijednosti zatim pretvaraju u koordinate slike množenjem s odgovarajućom dimenzijom slike. Na primjer, ako je vrijednost lijevo 0.5 na slici koja je široka 600 piksela, to bi se pretvorilo u 300 (0.5 x 600 = 300).

    Svaki okvir se crta na slici crvenom linijom. Na kraju se uređena slika sprema, prepisujući originalnu sliku.

1. Pokrenite aplikaciju s kamerom usmjerenom prema zalihama na polici. Vidjet ćete datoteku `image.jpg` u pregledniku VS Code-a i moći ćete je odabrati kako biste vidjeli okvire.

    ![4 konzerve paste od rajčice s okvirima oko svake konzerve](../../../../../translated_images/hr/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.webp)

## Brojanje zaliha

Na slici prikazanoj iznad, okviri se malo preklapaju. Ako bi ovo preklapanje bilo mnogo veće, okviri bi mogli označavati isti objekt. Da biste ispravno izbrojali objekte, trebate ignorirati okvire s značajnim preklapanjem.

### Zadatak - brojanje zaliha ignorirajući preklapanje

1. Pip paket [Shapely](https://pypi.org/project/Shapely/) može se koristiti za izračunavanje presjeka. Ako koristite Raspberry Pi, prvo ćete morati instalirati biblioteku ovisnosti:

    ```sh
    sudo apt install libgeos-dev
    ```

1. Instalirajte Shapely Pip paket:

    ```sh
    pip3 install shapely
    ```

    Ako koristite virtualni IoT uređaj, provjerite je li ovo pokrenuto unutar aktiviranog virtualnog okruženja.

1. Dodajte sljedeću naredbu za uvoz na vrh datoteke `app.py`:

    ```python
    from shapely.geometry import Polygon
    ```

    Ovo uvozi kod potreban za stvaranje poligona za izračunavanje preklapanja.

1. Iznad koda koji crta okvire, dodajte sljedeći kod:

    ```python
    overlap_threshold = 0.20
    ```

    Ovo definira postotak preklapanja koji je dopušten prije nego što se okviri smatraju istim objektom. 0.20 definira 20% preklapanja.

1. Za izračunavanje preklapanja pomoću Shapely-a, okviri se moraju pretvoriti u Shapely poligone. Dodajte sljedeću funkciju za to:

    ```python
    def create_polygon(prediction):
        scale_left = prediction.bounding_box.left
        scale_top = prediction.bounding_box.top
        scale_right = prediction.bounding_box.left + prediction.bounding_box.width
        scale_bottom = prediction.bounding_box.top + prediction.bounding_box.height
    
        return Polygon([(scale_left, scale_top), (scale_right, scale_top), (scale_right, scale_bottom), (scale_left, scale_bottom)])
    ```

    Ovo stvara poligon koristeći okvir predikcije.

1. Logika za uklanjanje preklapajućih objekata uključuje usporedbu svih okvira, a ako bilo koji par predikcija ima okvire koji se preklapaju više od praga, jedna od predikcija se briše. Za usporedbu svih predikcija, uspoređujete predikciju 1 s 2, 3, 4 itd., zatim 2 s 3, 4 itd. Sljedeći kod to radi:

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

    Preklapanje se izračunava pomoću Shapely metode `Polygon.intersection` koja vraća poligon koji ima preklapanje. Površina se zatim izračunava iz tog poligona. Ovaj prag preklapanja nije apsolutna vrijednost, već mora biti postotak okvira, pa se pronalazi najmanji okvir, a prag preklapanja se koristi za izračunavanje površine preklapanja koja ne smije premašiti postotak preklapanja najmanjeg okvira. Ako preklapanje premašuje ovo, predikcija se označava za brisanje.

    Kada je predikcija označena za brisanje, ne treba je ponovno provjeravati, pa se unutarnja petlja prekida kako bi provjerila sljedeću predikciju. Ne možete brisati stavke s popisa dok iterirate kroz njega, pa se okviri koji se preklapaju više od praga dodaju na popis `to_delete`, a zatim brišu na kraju.

    Na kraju se broj zaliha ispisuje u konzolu. Ovo bi se zatim moglo poslati IoT usluzi kako bi se upozorilo ako su razine zaliha niske. Sav ovaj kod je prije crtanja okvira, tako da ćete vidjeti predikcije zaliha bez preklapanja na generiranim slikama.

    > 💁 Ovo je vrlo jednostavan način uklanjanja preklapanja, samo se uklanja prvi u paru koji se preklapa. Za produkcijski kod, ovdje biste željeli dodati više logike, poput razmatranja preklapanja između više objekata ili ako je jedan okvir sadržan unutar drugog.

1. Pokrenite aplikaciju s kamerom usmjerenom prema zalihama na polici. Izlaz će pokazati broj okvira bez preklapanja koji premašuju prag. Pokušajte prilagoditi vrijednost `overlap_threshold` kako biste vidjeli ignorirane predikcije.

> 💁 Ovaj kod možete pronaći u mapi [code-count/pi](../../../../../5-retail/lessons/2-check-stock-device/code-count/pi) ili [code-count/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-count/virtual-iot-device).

😀 Vaš program za brojanje zaliha bio je uspješan!

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane ljudskog prevoditelja. Ne preuzimamo odgovornost za bilo kakve nesporazume ili pogrešne interpretacije koje proizlaze iz korištenja ovog prijevoda.