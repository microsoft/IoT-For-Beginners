<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9c4320311c0f2c1884a6a21265d98a51",
  "translation_date": "2025-08-28T10:50:48+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/single-board-computer-count-stock.md",
  "language_code": "ro"
}
-->
# Numără stocul de pe dispozitivul tău IoT - Hardware IoT Virtual și Raspberry Pi

O combinație între predicții și casetele de delimitare poate fi utilizată pentru a număra stocul dintr-o imagine.

## Afișează casetele de delimitare

Ca un pas util de depanare, poți nu doar să afișezi casetele de delimitare, ci și să le desenezi pe imaginea care a fost salvată pe disc atunci când o imagine a fost capturată.

### Sarcină - afișează casetele de delimitare

1. Asigură-te că proiectul `stock-counter` este deschis în VS Code și că mediul virtual este activat dacă folosești un dispozitiv IoT virtual.

1. Modifică instrucțiunea `print` din bucla `for` astfel încât să afișeze casetele de delimitare în consolă:

    ```python
    print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%\t{prediction.bounding_box}')
    ```

1. Rulează aplicația cu camera îndreptată spre stocul de pe un raft. Casetele de delimitare vor fi afișate în consolă, cu valorile pentru stânga, sus, lățime și înălțime între 0 și 1.

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   33.42%  {'additional_properties': {}, 'left': 0.3455171, 'top': 0.09916268, 'width': 0.14175442, 'height': 0.29405564}
    tomato paste:   34.41%  {'additional_properties': {}, 'left': 0.48283678, 'top': 0.10242918, 'width': 0.11782813, 'height': 0.27467814}
    tomato paste:   31.25%  {'additional_properties': {}, 'left': 0.4923783, 'top': 0.35007596, 'width': 0.13668466, 'height': 0.28304994}
    tomato paste:   31.05%  {'additional_properties': {}, 'left': 0.36416405, 'top': 0.37494493, 'width': 0.14024884, 'height': 0.26880276}
    ```

### Sarcină - desenează casetele de delimitare pe imagine

1. Pachetul Pip [Pillow](https://pypi.org/project/Pillow/) poate fi utilizat pentru a desena pe imagini. Instalează-l cu următoarea comandă:

    ```sh
    pip3 install pillow
    ```

    Dacă folosești un dispozitiv IoT virtual, asigură-te că rulezi această comandă din mediul virtual activat.

1. Adaugă următoarea instrucțiune de import în partea de sus a fișierului `app.py`:

    ```python
    from PIL import Image, ImageDraw, ImageColor
    ```

    Aceasta importă codul necesar pentru a edita imaginea.

1. Adaugă următorul cod la sfârșitul fișierului `app.py`:

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

    Acest cod deschide imaginea salvată anterior pentru editare. Apoi, parcurge predicțiile pentru a obține casetele de delimitare și calculează coordonata din dreapta jos folosind valorile casetelor de delimitare între 0 și 1. Acestea sunt apoi convertite în coordonate ale imaginii prin înmulțirea cu dimensiunea relevantă a imaginii. De exemplu, dacă valoarea pentru stânga este 0.5 pe o imagine de 600 pixeli lățime, aceasta va fi convertită la 300 (0.5 x 600 = 300).

    Fiecare casetă de delimitare este desenată pe imagine folosind o linie roșie. În final, imaginea editată este salvată, suprascriind imaginea originală.

1. Rulează aplicația cu camera îndreptată spre stocul de pe un raft. Vei vedea fișierul `image.jpg` în explorer-ul VS Code și vei putea să-l selectezi pentru a vedea casetele de delimitare.

    ![4 conserve de pastă de roșii cu casete de delimitare în jurul fiecărei conserve](../../../../../translated_images/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.ro.jpg)

## Numără stocul

În imaginea de mai sus, casetele de delimitare au o mică suprapunere. Dacă această suprapunere ar fi mult mai mare, casetele de delimitare ar putea indica același obiect. Pentru a număra obiectele corect, trebuie să ignori casetele cu o suprapunere semnificativă.

### Sarcină - numără stocul ignorând suprapunerile

1. Pachetul Pip [Shapely](https://pypi.org/project/Shapely/) poate fi utilizat pentru a calcula intersecția. Dacă folosești un Raspberry Pi, va trebui să instalezi mai întâi o dependență a bibliotecii:

    ```sh
    sudo apt install libgeos-dev
    ```

1. Instalează pachetul Pip Shapely:

    ```sh
    pip3 install shapely
    ```

    Dacă folosești un dispozitiv IoT virtual, asigură-te că rulezi această comandă din mediul virtual activat.

1. Adaugă următoarea instrucțiune de import în partea de sus a fișierului `app.py`:

    ```python
    from shapely.geometry import Polygon
    ```

    Aceasta importă codul necesar pentru a crea poligoane și a calcula suprapunerile.

1. Deasupra codului care desenează casetele de delimitare, adaugă următorul cod:

    ```python
    overlap_threshold = 0.20
    ```

    Acesta definește procentul de suprapunere permis înainte ca casetele de delimitare să fie considerate același obiect. 0.20 definește o suprapunere de 20%.

1. Pentru a calcula suprapunerea folosind Shapely, casetele de delimitare trebuie convertite în poligoane Shapely. Adaugă următoarea funcție pentru a face acest lucru:

    ```python
    def create_polygon(prediction):
        scale_left = prediction.bounding_box.left
        scale_top = prediction.bounding_box.top
        scale_right = prediction.bounding_box.left + prediction.bounding_box.width
        scale_bottom = prediction.bounding_box.top + prediction.bounding_box.height
    
        return Polygon([(scale_left, scale_top), (scale_right, scale_top), (scale_right, scale_bottom), (scale_left, scale_bottom)])
    ```

    Aceasta creează un poligon folosind caseta de delimitare a unei predicții.

1. Logica pentru eliminarea obiectelor suprapuse implică compararea tuturor casetelor de delimitare și, dacă oricare pereche de predicții are casete de delimitare care se suprapun mai mult decât pragul, una dintre predicții este ștearsă. Pentru a compara toate predicțiile, compari predicția 1 cu 2, 3, 4 etc., apoi 2 cu 3, 4 etc. Următorul cod face acest lucru:

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

    Suprapunerea este calculată folosind metoda Shapely `Polygon.intersection`, care returnează un poligon ce reprezintă suprapunerea. Suprafața este apoi calculată din acest poligon. Acest prag de suprapunere nu este o valoare absolută, ci trebuie să fie un procent din caseta de delimitare, astfel încât cea mai mică casetă de delimitare este găsită, iar pragul de suprapunere este utilizat pentru a calcula ce suprafață poate avea suprapunerea pentru a nu depăși procentul de suprapunere permis al celei mai mici casete de delimitare. Dacă suprapunerea depășește acest prag, predicția este marcată pentru ștergere.

    Odată ce o predicție a fost marcată pentru ștergere, nu mai trebuie verificată din nou, astfel încât bucla interioară se oprește pentru a verifica următoarea predicție. Nu poți șterge elemente dintr-o listă în timp ce o parcurgi, astfel încât casetele de delimitare care se suprapun mai mult decât pragul sunt adăugate în lista `to_delete`, apoi șterse la final.

    În final, numărul de stoc este afișat în consolă. Acesta ar putea fi apoi trimis către un serviciu IoT pentru a alerta dacă nivelurile de stoc sunt scăzute. Tot acest cod este înainte ca casetele de delimitare să fie desenate, astfel încât vei vedea predicțiile de stoc fără suprapuneri pe imaginile generate.

    > 💁 Aceasta este o metodă foarte simplistă de a elimina suprapunerile, eliminând doar prima dintr-o pereche suprapusă. Pentru codul de producție, ar trebui să adaugi mai multă logică aici, cum ar fi luarea în considerare a suprapunerilor între mai multe obiecte sau dacă o casetă de delimitare este conținută de alta.

1. Rulează aplicația cu camera îndreptată spre stocul de pe un raft. Rezultatul va indica numărul de casete de delimitare fără suprapuneri care depășesc pragul. Încearcă să ajustezi valoarea `overlap_threshold` pentru a vedea predicțiile ignorate.

> 💁 Poți găsi acest cod în folderul [code-count/pi](../../../../../5-retail/lessons/2-check-stock-device/code-count/pi) sau [code-count/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-count/virtual-iot-device).

😀 Programul tău de numărare a stocului a fost un succes!

---

**Declinare de responsabilitate**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să fiți conștienți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa natală ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm responsabilitatea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.