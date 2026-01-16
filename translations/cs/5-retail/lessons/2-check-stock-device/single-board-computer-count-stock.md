<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9c4320311c0f2c1884a6a21265d98a51",
  "translation_date": "2025-08-27T22:45:04+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/single-board-computer-count-stock.md",
  "language_code": "cs"
}
-->
# Počítání zásob z vašeho IoT zařízení - Virtuální IoT hardware a Raspberry Pi

Kombinace predikcí a jejich ohraničujících rámečků může být použita k počítání zásob na obrázku.

## Zobrazení ohraničujících rámečků

Jako užitečný krok při ladění můžete nejen vytisknout ohraničující rámečky, ale také je nakreslit na obrázek, který byl uložen na disk při zachycení snímku.

### Úkol - vytiskněte ohraničující rámečky

1. Ujistěte se, že projekt `stock-counter` je otevřený ve VS Code a že je aktivováno virtuální prostředí, pokud používáte virtuální IoT zařízení.

1. Změňte příkaz `print` v cyklu `for` na následující, aby se ohraničující rámečky vytiskly do konzole:

    ```python
    print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%\t{prediction.bounding_box}')
    ```

1. Spusťte aplikaci s kamerou namířenou na nějaké zásoby na polici. Ohraničující rámečky budou vytištěny do konzole s hodnotami left, top, width a height v rozmezí 0-1.

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   33.42%  {'additional_properties': {}, 'left': 0.3455171, 'top': 0.09916268, 'width': 0.14175442, 'height': 0.29405564}
    tomato paste:   34.41%  {'additional_properties': {}, 'left': 0.48283678, 'top': 0.10242918, 'width': 0.11782813, 'height': 0.27467814}
    tomato paste:   31.25%  {'additional_properties': {}, 'left': 0.4923783, 'top': 0.35007596, 'width': 0.13668466, 'height': 0.28304994}
    tomato paste:   31.05%  {'additional_properties': {}, 'left': 0.36416405, 'top': 0.37494493, 'width': 0.14024884, 'height': 0.26880276}
    ```

### Úkol - nakreslete ohraničující rámečky na obrázek

1. Balíček Pip [Pillow](https://pypi.org/project/Pillow/) lze použít k úpravě obrázků. Nainstalujte jej pomocí následujícího příkazu:

    ```sh
    pip3 install pillow
    ```

    Pokud používáte virtuální IoT zařízení, ujistěte se, že tento příkaz spouštíte v aktivovaném virtuálním prostředí.

1. Přidejte následující import na začátek souboru `app.py`:

    ```python
    from PIL import Image, ImageDraw, ImageColor
    ```

    Tento import načte kód potřebný k úpravě obrázku.

1. Přidejte následující kód na konec souboru `app.py`:

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

    Tento kód otevře obrázek, který byl dříve uložen, pro úpravy. Poté prochází predikce, získává ohraničující rámečky a vypočítává pravý dolní roh pomocí hodnot ohraničujícího rámečku v rozmezí 0-1. Tyto hodnoty jsou poté převedeny na souřadnice obrázku vynásobením příslušným rozměrem obrázku. Například pokud hodnota left byla 0.5 na obrázku širokém 600 pixelů, převedlo by se to na 300 (0.5 x 600 = 300).

    Každý ohraničující rámeček je nakreslen na obrázek červenou čarou. Nakonec je upravený obrázek uložen, přepisující původní obrázek.

1. Spusťte aplikaci s kamerou namířenou na nějaké zásoby na polici. V průzkumníku VS Code uvidíte soubor `image.jpg` a budete jej moci otevřít a zobrazit ohraničující rámečky.

    ![4 plechovky rajčatového protlaku s ohraničujícími rámečky kolem každé plechovky](../../../../../translated_images/cs/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.jpg)

## Počítání zásob

Na výše uvedeném obrázku mají ohraničující rámečky malý překryv. Pokud by tento překryv byl mnohem větší, mohly by ohraničující rámečky označovat stejný objekt. Aby bylo možné správně spočítat objekty, je třeba ignorovat rámečky s významným překryvem.

### Úkol - počítání zásob s ignorováním překryvu

1. Balíček Pip [Shapely](https://pypi.org/project/Shapely/) lze použít k výpočtu průniku. Pokud používáte Raspberry Pi, budete muset nejprve nainstalovat knihovní závislost:

    ```sh
    sudo apt install libgeos-dev
    ```

1. Nainstalujte balíček Shapely pomocí Pip:

    ```sh
    pip3 install shapely
    ```

    Pokud používáte virtuální IoT zařízení, ujistěte se, že tento příkaz spouštíte v aktivovaném virtuálním prostředí.

1. Přidejte následující import na začátek souboru `app.py`:

    ```python
    from shapely.geometry import Polygon
    ```

    Tento import načte kód potřebný k vytvoření polygonů pro výpočet překryvu.

1. Nad kód, který kreslí ohraničující rámečky, přidejte následující kód:

    ```python
    overlap_threshold = 0.20
    ```

    Tento kód definuje procento překryvu, které je povoleno, než jsou ohraničující rámečky považovány za stejný objekt. 0.20 definuje 20% překryv.

1. Aby bylo možné vypočítat překryv pomocí Shapely, je třeba ohraničující rámečky převést na polygony Shapely. Přidejte následující funkci, která to provede:

    ```python
    def create_polygon(prediction):
        scale_left = prediction.bounding_box.left
        scale_top = prediction.bounding_box.top
        scale_right = prediction.bounding_box.left + prediction.bounding_box.width
        scale_bottom = prediction.bounding_box.top + prediction.bounding_box.height
    
        return Polygon([(scale_left, scale_top), (scale_right, scale_top), (scale_right, scale_bottom), (scale_left, scale_bottom)])
    ```

    Tato funkce vytvoří polygon pomocí ohraničujícího rámečku predikce.

1. Logika pro odstranění překrývajících se objektů zahrnuje porovnání všech ohraničujících rámečků. Pokud se jakékoliv dvojice predikcí překrývají více než je povolený práh, jedna z predikcí se odstraní. Pro porovnání všech predikcí porovnáte predikci 1 s 2, 3, 4 atd., poté 2 s 3, 4 atd. Následující kód to provádí:

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

    Překryv se vypočítá pomocí metody Shapely `Polygon.intersection`, která vrací polygon s překryvem. Z tohoto polygonu se poté vypočítá plocha. Tento práh překryvu není absolutní hodnota, ale musí být procentem ohraničujícího rámečku, takže se najde nejmenší ohraničující rámeček a práh překryvu se použije k výpočtu plochy, kterou může překryv mít, aby nepřekročil procentuální práh překryvu nejmenšího ohraničujícího rámečku. Pokud překryv tento práh překročí, predikce je označena k odstranění.

    Jakmile je predikce označena k odstranění, není třeba ji znovu kontrolovat, takže vnitřní smyčka se přeruší a přejde na další predikci. Nemůžete mazat položky ze seznamu během jeho iterace, takže ohraničující rámečky, které překračují práh překryvu, jsou přidány do seznamu `to_delete` a poté na konci odstraněny.

    Nakonec se počet zásob vytiskne do konzole. Tento počet by pak mohl být odeslán do IoT služby, aby upozornil na nízké zásoby. Veškerý tento kód je před kreslením ohraničujících rámečků, takže na vygenerovaných obrázcích uvidíte predikce zásob bez překryvů.

    > 💁 Toto je velmi jednoduchý způsob, jak odstranit překryvy, pouze odstraněním prvního z překrývající se dvojice. Pro produkční kód byste chtěli přidat více logiky, například zohlednit překryvy mezi více objekty nebo pokud je jeden ohraničující rámeček obsažen v jiném.

1. Spusťte aplikaci s kamerou namířenou na nějaké zásoby na polici. Výstup bude indikovat počet ohraničujících rámečků bez překryvů, které překračují práh. Zkuste upravit hodnotu `overlap_threshold`, abyste viděli, jak jsou predikce ignorovány.

> 💁 Tento kód najdete ve složce [code-count/pi](../../../../../5-retail/lessons/2-check-stock-device/code-count/pi) nebo [code-count/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-count/virtual-iot-device).

😀 Váš program na počítání zásob byl úspěšný!

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). Ačkoli se snažíme o přesnost, mějte na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace doporučujeme profesionální lidský překlad. Neodpovídáme za žádná nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.