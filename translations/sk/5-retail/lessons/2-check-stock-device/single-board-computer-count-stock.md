<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9c4320311c0f2c1884a6a21265d98a51",
  "translation_date": "2025-08-28T10:50:15+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/single-board-computer-count-stock.md",
  "language_code": "sk"
}
-->
# Počítanie zásob z vášho IoT zariadenia - Virtuálny IoT hardvér a Raspberry Pi

Kombinácia predpovedí a ich ohraničujúcich rámčekov môže byť použitá na počítanie zásob na obrázku.

## Zobrazenie ohraničujúcich rámčekov

Ako užitočný krok pri ladení môžete nielen vypísať ohraničujúce rámčeky, ale tiež ich nakresliť na obrázok, ktorý bol uložený na disk pri zachytení obrázka.

### Úloha - vypísať ohraničujúce rámčeky

1. Uistite sa, že projekt `stock-counter` je otvorený vo VS Code a virtuálne prostredie je aktivované, ak používate virtuálne IoT zariadenie.

1. Zmeňte príkaz `print` v cykle `for` na nasledujúci, aby ste vypísali ohraničujúce rámčeky do konzoly:

    ```python
    print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%\t{prediction.bounding_box}')
    ```

1. Spustite aplikáciu s kamerou namierenou na nejaké zásoby na polici. Ohraničujúce rámčeky budú vypísané do konzoly s hodnotami ľavého, horného, šírky a výšky od 0 do 1.

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   33.42%  {'additional_properties': {}, 'left': 0.3455171, 'top': 0.09916268, 'width': 0.14175442, 'height': 0.29405564}
    tomato paste:   34.41%  {'additional_properties': {}, 'left': 0.48283678, 'top': 0.10242918, 'width': 0.11782813, 'height': 0.27467814}
    tomato paste:   31.25%  {'additional_properties': {}, 'left': 0.4923783, 'top': 0.35007596, 'width': 0.13668466, 'height': 0.28304994}
    tomato paste:   31.05%  {'additional_properties': {}, 'left': 0.36416405, 'top': 0.37494493, 'width': 0.14024884, 'height': 0.26880276}
    ```

### Úloha - nakresliť ohraničujúce rámčeky na obrázok

1. Balík Pip [Pillow](https://pypi.org/project/Pillow/) môže byť použitý na kreslenie na obrázky. Nainštalujte ho pomocou nasledujúceho príkazu:

    ```sh
    pip3 install pillow
    ```

    Ak používate virtuálne IoT zariadenie, uistite sa, že tento príkaz spúšťate z aktivovaného virtuálneho prostredia.

1. Pridajte nasledujúci import na začiatok súboru `app.py`:

    ```python
    from PIL import Image, ImageDraw, ImageColor
    ```

    Tento importuje kód potrebný na úpravu obrázka.

1. Pridajte nasledujúci kód na koniec súboru `app.py`:

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

    Tento kód otvorí obrázok, ktorý bol predtým uložený na úpravu. Potom prechádza predpovede, získava ohraničujúce rámčeky a vypočíta pravý dolný bod pomocou hodnôt ohraničujúceho rámčeka od 0 do 1. Tieto hodnoty sú potom konvertované na súradnice obrázka násobením príslušným rozmerom obrázka. Napríklad, ak hodnota ľavého bodu bola 0.5 na obrázku širokom 600 pixelov, konvertovalo by sa to na 300 (0.5 x 600 = 300).

    Každý ohraničujúci rámček je nakreslený na obrázok pomocou červenej čiary. Nakoniec je upravený obrázok uložený, čím sa prepíše pôvodný obrázok.

1. Spustite aplikáciu s kamerou namierenou na nejaké zásoby na polici. V prieskumníkovi VS Code uvidíte súbor `image.jpg` a budete ho môcť vybrať, aby ste videli ohraničujúce rámčeky.

    ![4 konzervy paradajkového pretlaku s ohraničujúcimi rámčekmi okolo každej konzervy](../../../../../translated_images/sk/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.jpg)

## Počítanie zásob

Na obrázku vyššie majú ohraničujúce rámčeky malý prekryv. Ak by tento prekryv bol oveľa väčší, ohraničujúce rámčeky by mohli označovať ten istý objekt. Aby ste správne spočítali objekty, musíte ignorovať rámčeky s významným prekryvom.

### Úloha - počítanie zásob ignorujúc prekryv

1. Balík Pip [Shapely](https://pypi.org/project/Shapely/) môže byť použitý na výpočet prieniku. Ak používate Raspberry Pi, budete musieť najskôr nainštalovať knižničnú závislosť:

    ```sh
    sudo apt install libgeos-dev
    ```

1. Nainštalujte balík Shapely pomocou Pip:

    ```sh
    pip3 install shapely
    ```

    Ak používate virtuálne IoT zariadenie, uistite sa, že tento príkaz spúšťate z aktivovaného virtuálneho prostredia.

1. Pridajte nasledujúci import na začiatok súboru `app.py`:

    ```python
    from shapely.geometry import Polygon
    ```

    Tento importuje kód potrebný na vytvorenie polygónov na výpočet prekryvu.

1. Nad kódom, ktorý kreslí ohraničujúce rámčeky, pridajte nasledujúci kód:

    ```python
    overlap_threshold = 0.20
    ```

    Tento definuje percentuálny prekryv, ktorý je povolený predtým, než sú ohraničujúce rámčeky považované za ten istý objekt. 0.20 definuje 20% prekryv.

1. Na výpočet prekryvu pomocou Shapely musia byť ohraničujúce rámčeky konvertované na polygóny Shapely. Pridajte nasledujúcu funkciu na vykonanie tejto konverzie:

    ```python
    def create_polygon(prediction):
        scale_left = prediction.bounding_box.left
        scale_top = prediction.bounding_box.top
        scale_right = prediction.bounding_box.left + prediction.bounding_box.width
        scale_bottom = prediction.bounding_box.top + prediction.bounding_box.height
    
        return Polygon([(scale_left, scale_top), (scale_right, scale_top), (scale_right, scale_bottom), (scale_left, scale_bottom)])
    ```

    Táto funkcia vytvára polygón pomocou ohraničujúceho rámčeka predpovede.

1. Logika na odstránenie prekryvajúcich sa objektov zahŕňa porovnanie všetkých ohraničujúcich rámčekov. Ak majú akékoľvek dvojice predpovedí ohraničujúce rámčeky, ktoré sa prekryvajú viac ako je prahová hodnota, jedna z predpovedí sa odstráni. Na porovnanie všetkých predpovedí porovnáte predpoveď 1 s 2, 3, 4, atď., potom 2 s 3, 4, atď. Nasledujúci kód to vykonáva:

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

    Prekryv sa vypočíta pomocou metódy Shapely `Polygon.intersection`, ktorá vráti polygón s prekryvom. Z tohto polygónu sa potom vypočíta plocha. Táto prahová hodnota prekryvu nie je absolútna hodnota, ale musí byť percentom ohraničujúceho rámčeka, takže sa nájde najmenší ohraničujúci rámček a prahová hodnota prekryvu sa použije na výpočet plochy, ktorú prekryv môže mať, aby neprekročil percentuálnu prahovú hodnotu prekryvu najmenšieho ohraničujúceho rámčeka. Ak prekryv túto hodnotu prekročí, predpoveď je označená na odstránenie.

    Keď je predpoveď označená na odstránenie, už ju netreba znova kontrolovať, takže vnútorný cyklus sa preruší, aby sa skontrolovala ďalšia predpoveď. Nemôžete odstraňovať položky zo zoznamu počas jeho iterácie, takže ohraničujúce rámčeky, ktoré sa prekryvajú viac ako je prahová hodnota, sú pridané do zoznamu `to_delete` a potom odstránené na konci.

    Nakoniec sa počet zásob vypíše do konzoly. Tento počet by mohol byť potom odoslaný do IoT služby na upozornenie, ak sú úrovne zásob nízke. Celý tento kód je pred kreslením ohraničujúcich rámčekov, takže na generovaných obrázkoch uvidíte predpovede zásob bez prekryvov.

    > 💁 Toto je veľmi jednoduchý spôsob odstránenia prekryvov, jednoducho odstránením prvého z dvojice prekryvajúcich sa objektov. Pre produkčný kód by ste chceli pridať viac logiky, ako napríklad zohľadnenie prekryvov medzi viacerými objektmi alebo ak je jeden ohraničujúci rámček obsiahnutý v inom.

1. Spustite aplikáciu s kamerou namierenou na nejaké zásoby na polici. Výstup bude indikovať počet ohraničujúcich rámčekov bez prekryvov, ktoré presahujú prahovú hodnotu. Skúste upraviť hodnotu `overlap_threshold`, aby ste videli ignorované predpovede.

> 💁 Tento kód nájdete v priečinku [code-count/pi](../../../../../5-retail/lessons/2-check-stock-device/code-count/pi) alebo [code-count/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-count/virtual-iot-device).

😀 Váš program na počítanie zásob bol úspešný!

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby AI prekladu [Co-op Translator](https://github.com/Azure/co-op-translator). Hoci sa snažíme o presnosť, prosím, berte na vedomie, že automatizované preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho rodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nie sme zodpovední za žiadne nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.