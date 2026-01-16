<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9c4320311c0f2c1884a6a21265d98a51",
  "translation_date": "2025-08-27T20:30:33+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/single-board-computer-count-stock.md",
  "language_code": "fi"
}
-->
# Laske varasto IoT-laitteellasi - Virtuaalinen IoT-laitteisto ja Raspberry Pi

Ennusteiden ja niiden rajauslaatikoiden yhdistelmää voidaan käyttää laskemaan varastoa kuvasta.

## Näytä rajauslaatikot

Hyödyllisenä virheenkorjausvaiheena voit paitsi tulostaa rajauslaatikot, myös piirtää ne kuvaan, joka tallennettiin levylle kuvan kaappaamisen yhteydessä.

### Tehtävä - tulosta rajauslaatikot

1. Varmista, että `stock-counter`-projekti on auki VS Codessa ja että virtuaalinen ympäristö on aktivoitu, jos käytät virtuaalista IoT-laitetta.

1. Muuta `for`-silmukan `print`-lausetta seuraavasti, jotta rajauslaatikot tulostetaan konsoliin:

    ```python
    print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%\t{prediction.bounding_box}')
    ```

1. Suorita sovellus niin, että kamera osoittaa hyllyllä olevaan varastoon. Rajauslaatikot tulostetaan konsoliin, ja niissä näkyvät vasen, ylä, leveys ja korkeus arvot välillä 0-1.

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   33.42%  {'additional_properties': {}, 'left': 0.3455171, 'top': 0.09916268, 'width': 0.14175442, 'height': 0.29405564}
    tomato paste:   34.41%  {'additional_properties': {}, 'left': 0.48283678, 'top': 0.10242918, 'width': 0.11782813, 'height': 0.27467814}
    tomato paste:   31.25%  {'additional_properties': {}, 'left': 0.4923783, 'top': 0.35007596, 'width': 0.13668466, 'height': 0.28304994}
    tomato paste:   31.05%  {'additional_properties': {}, 'left': 0.36416405, 'top': 0.37494493, 'width': 0.14024884, 'height': 0.26880276}
    ```

### Tehtävä - piirrä rajauslaatikot kuvaan

1. Pip-pakettia [Pillow](https://pypi.org/project/Pillow/) voidaan käyttää piirtämiseen kuviin. Asenna se seuraavalla komennolla:

    ```sh
    pip3 install pillow
    ```

    Jos käytät virtuaalista IoT-laitetta, varmista, että suoritat tämän aktivoidussa virtuaalisessa ympäristössä.

1. Lisää seuraava import-lausunto `app.py`-tiedoston alkuun:

    ```python
    from PIL import Image, ImageDraw, ImageColor
    ```

    Tämä tuo mukaan koodin, joka tarvitaan kuvan muokkaamiseen.

1. Lisää seuraava koodi `app.py`-tiedoston loppuun:

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

    Tämä koodi avaa aiemmin tallennetun kuvan muokkausta varten. Se käy läpi ennusteet, hakee rajauslaatikot ja laskee oikean alakulman koordinaatit rajauslaatikon arvojen perusteella (0-1). Nämä arvot muunnetaan kuvan koordinaateiksi kertomalla kuvan vastaavalla ulottuvuudella. Esimerkiksi, jos vasen arvo on 0.5 kuvassa, joka on 600 pikseliä leveä, se muunnetaan arvoon 300 (0.5 x 600 = 300).

    Jokainen rajauslaatikko piirretään kuvaan punaisella viivalla. Lopuksi muokattu kuva tallennetaan alkuperäisen kuvan päälle.

1. Suorita sovellus niin, että kamera osoittaa hyllyllä olevaan varastoon. Näet `image.jpg`-tiedoston VS Coden tiedostoselaimessa ja voit avata sen nähdäksesi rajauslaatikot.

    ![4 tomaattipyre-purkkia, joiden ympärillä on rajauslaatikot](../../../../../translated_images/fi/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.jpg)

## Laske varasto

Yllä olevassa kuvassa rajauslaatikot ovat hieman päällekkäin. Jos tämä päällekkäisyys olisi paljon suurempi, rajauslaatikot voisivat viitata samaan objektiin. Jotta objektit lasketaan oikein, sinun täytyy jättää huomioimatta laatikot, joissa on merkittävä päällekkäisyys.

### Tehtävä - laske varasto huomioimatta päällekkäisyyttä

1. Pip-pakettia [Shapely](https://pypi.org/project/Shapely/) voidaan käyttää leikkauspisteiden laskemiseen. Jos käytät Raspberry Pi:tä, sinun täytyy ensin asentaa kirjastoriippuvuus:

    ```sh
    sudo apt install libgeos-dev
    ```

1. Asenna Shapely Pip-paketti:

    ```sh
    pip3 install shapely
    ```

    Jos käytät virtuaalista IoT-laitetta, varmista, että suoritat tämän aktivoidussa virtuaalisessa ympäristössä.

1. Lisää seuraava import-lausunto `app.py`-tiedoston alkuun:

    ```python
    from shapely.geometry import Polygon
    ```

    Tämä tuo mukaan koodin, joka tarvitaan monikulmioiden luomiseen päällekkäisyyden laskemiseksi.

1. Lisää seuraava koodi rajauslaatikoiden piirtämistä edeltävään kohtaan:

    ```python
    overlap_threshold = 0.20
    ```

    Tämä määrittää sallitun päällekkäisyysprosentin, ennen kuin rajauslaatikot katsotaan samaksi objektiksi. 0.20 tarkoittaa 20 %:n päällekkäisyyttä.

1. Jotta Shapelyä voidaan käyttää päällekkäisyyden laskemiseen, rajauslaatikot täytyy muuntaa Shapely-monikulmioiksi. Lisää seuraava funktio tätä varten:

    ```python
    def create_polygon(prediction):
        scale_left = prediction.bounding_box.left
        scale_top = prediction.bounding_box.top
        scale_right = prediction.bounding_box.left + prediction.bounding_box.width
        scale_bottom = prediction.bounding_box.top + prediction.bounding_box.height
    
        return Polygon([(scale_left, scale_top), (scale_right, scale_top), (scale_right, scale_bottom), (scale_left, scale_bottom)])
    ```

    Tämä luo monikulmion ennusteen rajauslaatikon perusteella.

1. Päällekkäisten objektien poistamisen logiikka sisältää kaikkien rajauslaatikoiden vertailun. Jos mitkä tahansa ennusteparit sisältävät rajauslaatikot, joiden päällekkäisyys ylittää kynnyksen, yksi ennusteista poistetaan. Vertailu tehdään seuraavasti: ennuste 1 verrataan ennusteisiin 2, 3, 4 jne., sitten ennuste 2 verrataan ennusteisiin 3, 4 jne. Seuraava koodi tekee tämän:

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

    Päällekkäisyys lasketaan Shapelyn `Polygon.intersection`-menetelmällä, joka palauttaa päällekkäisyyden muodostaman monikulmion. Tämän monikulmion pinta-ala lasketaan. Päällekkäisyyskynnys ei ole absoluuttinen arvo, vaan sen täytyy olla prosenttiosuus rajauslaatikosta, joten pienin rajauslaatikko etsitään, ja päällekkäisyyskynnystä käytetään laskemaan, kuinka suuri alue päällekkäisyys voi olla ylittämättä pienimmän rajauslaatikon prosenttiosuuskynnystä. Jos päällekkäisyys ylittää tämän, ennuste merkitään poistettavaksi.

    Kun ennuste on merkitty poistettavaksi, sitä ei tarvitse enää tarkistaa, joten sisempi silmukka keskeytetään ja siirrytään seuraavaan ennusteeseen. Et voi poistaa kohteita listasta sen läpikäynnin aikana, joten rajauslaatikot, joiden päällekkäisyys ylittää kynnyksen, lisätään `to_delete`-listaan ja poistetaan lopuksi.

    Lopuksi varaston määrä tulostetaan konsoliin. Tämä voitaisiin lähettää IoT-palveluun, joka hälyttää, jos varastotaso on alhainen. Kaikki tämä koodi suoritetaan ennen rajauslaatikoiden piirtämistä, joten näet päällekkäisyydettömät varastoennusteet luoduissa kuvissa.

    > 💁 Tämä on hyvin yksinkertainen tapa poistaa päällekkäisyydet, poistamalla vain ensimmäinen päällekkäisessä parissa. Tuotantokoodissa haluaisit lisätä enemmän logiikkaa, kuten huomioida useiden objektien päällekkäisyydet tai tilanteet, joissa yksi rajauslaatikko sisältyy toiseen.

1. Suorita sovellus niin, että kamera osoittaa hyllyllä olevaan varastoon. Tulosteessa näkyy rajauslaatikoiden määrä, joissa päällekkäisyys ei ylitä kynnystä. Kokeile säätää `overlap_threshold`-arvoa nähdäksesi, miten ennusteita jätetään huomiotta.

> 💁 Löydät tämän koodin [code-count/pi](../../../../../5-retail/lessons/2-check-stock-device/code-count/pi)- tai [code-count/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-count/virtual-iot-device)-kansiosta.

😀 Varastonlaskentaohjelmasi oli menestys!

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäistä asiakirjaa sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.