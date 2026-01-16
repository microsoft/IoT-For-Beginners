<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9c4320311c0f2c1884a6a21265d98a51",
  "translation_date": "2025-08-27T20:45:35+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/single-board-computer-count-stock.md",
  "language_code": "tl"
}
-->
# Bilangin ang stock mula sa iyong IoT device - Virtual IoT Hardware at Raspberry Pi

Ang kombinasyon ng mga prediksyon at kanilang bounding boxes ay maaaring gamitin upang bilangin ang stock sa isang imahe.

## Ipakita ang bounding boxes

Bilang isang kapaki-pakinabang na hakbang sa pag-debug, hindi mo lang maaaring i-print ang bounding boxes, kundi maaari mo ring iguhit ang mga ito sa imahe na isinulat sa disk kapag ang isang imahe ay nakunan.

### Gawain - i-print ang bounding boxes

1. Siguraduhing bukas ang proyekto na `stock-counter` sa VS Code, at ang virtual environment ay naka-activate kung gumagamit ka ng virtual IoT device.

1. Palitan ang `print` statement sa `for` loop ng sumusunod upang i-print ang bounding boxes sa console:

    ```python
    print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%\t{prediction.bounding_box}')
    ```

1. Patakbuhin ang app habang nakatutok ang camera sa ilang stock sa isang istante. Ang bounding boxes ay ipapakita sa console, na may mga halaga ng left, top, width, at height mula 0-1.

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   33.42%  {'additional_properties': {}, 'left': 0.3455171, 'top': 0.09916268, 'width': 0.14175442, 'height': 0.29405564}
    tomato paste:   34.41%  {'additional_properties': {}, 'left': 0.48283678, 'top': 0.10242918, 'width': 0.11782813, 'height': 0.27467814}
    tomato paste:   31.25%  {'additional_properties': {}, 'left': 0.4923783, 'top': 0.35007596, 'width': 0.13668466, 'height': 0.28304994}
    tomato paste:   31.05%  {'additional_properties': {}, 'left': 0.36416405, 'top': 0.37494493, 'width': 0.14024884, 'height': 0.26880276}
    ```

### Gawain - iguhit ang bounding boxes sa imahe

1. Ang Pip package [Pillow](https://pypi.org/project/Pillow/) ay maaaring gamitin upang iguhit sa mga imahe. I-install ito gamit ang sumusunod na command:

    ```sh
    pip3 install pillow
    ```

    Kung gumagamit ka ng virtual IoT device, siguraduhing patakbuhin ito mula sa loob ng naka-activate na virtual environment.

1. Idagdag ang sumusunod na import statement sa itaas ng `app.py` file:

    ```python
    from PIL import Image, ImageDraw, ImageColor
    ```

    Ina-import nito ang code na kailangan upang i-edit ang imahe.

1. Idagdag ang sumusunod na code sa dulo ng `app.py` file:

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

    Binubuksan ng code na ito ang imahe na na-save kanina para sa pag-edit. Pagkatapos ay ini-loop nito ang mga prediksyon upang makuha ang bounding boxes, at kinakalkula ang bottom right coordinate gamit ang mga halaga ng bounding box mula 0-1. Ang mga ito ay kino-convert sa image coordinates sa pamamagitan ng pag-multiply sa kaukulang sukat ng imahe. Halimbawa, kung ang left value ay 0.5 sa isang imahe na may lapad na 600 pixels, ito ay iko-convert sa 300 (0.5 x 600 = 300).

    Ang bawat bounding box ay iginuguhit sa imahe gamit ang pulang linya. Sa huli, ang na-edit na imahe ay sine-save, pinapalitan ang orihinal na imahe.

1. Patakbuhin ang app habang nakatutok ang camera sa ilang stock sa isang istante. Makikita mo ang `image.jpg` file sa VS Code explorer, at maaari mo itong piliin upang makita ang bounding boxes.

    ![4 lata ng tomato paste na may bounding boxes sa paligid ng bawat lata](../../../../../translated_images/tl/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.webp)

## Bilangin ang stock

Sa imahe na ipinakita sa itaas, ang bounding boxes ay may kaunting overlap. Kung ang overlap na ito ay mas malaki, maaaring ipahiwatig ng bounding boxes na pareho ang object. Upang mabilang nang tama ang mga object, kailangan mong huwag pansinin ang mga kahon na may malaking overlap.

### Gawain - bilangin ang stock na hindi isinasaalang-alang ang overlap

1. Ang Pip package [Shapely](https://pypi.org/project/Shapely/) ay maaaring gamitin upang kalkulahin ang intersection. Kung gumagamit ka ng Raspberry Pi, kailangan mong mag-install muna ng library dependency:

    ```sh
    sudo apt install libgeos-dev
    ```

1. I-install ang Shapely Pip package:

    ```sh
    pip3 install shapely
    ```

    Kung gumagamit ka ng virtual IoT device, siguraduhing patakbuhin ito mula sa loob ng naka-activate na virtual environment.

1. Idagdag ang sumusunod na import statement sa itaas ng `app.py` file:

    ```python
    from shapely.geometry import Polygon
    ```

    Ina-import nito ang code na kailangan upang lumikha ng polygons para kalkulahin ang overlap.

1. Sa itaas ng code na gumuguhit ng bounding boxes, idagdag ang sumusunod na code:

    ```python
    overlap_threshold = 0.20
    ```

    Tinutukoy nito ang percentage overlap na pinapayagan bago ang bounding boxes ay ituring na pareho ang object. Ang 0.20 ay tumutukoy sa 20% overlap.

1. Upang kalkulahin ang overlap gamit ang Shapely, kailangang i-convert ang bounding boxes sa Shapely polygons. Idagdag ang sumusunod na function upang gawin ito:

    ```python
    def create_polygon(prediction):
        scale_left = prediction.bounding_box.left
        scale_top = prediction.bounding_box.top
        scale_right = prediction.bounding_box.left + prediction.bounding_box.width
        scale_bottom = prediction.bounding_box.top + prediction.bounding_box.height
    
        return Polygon([(scale_left, scale_top), (scale_right, scale_top), (scale_right, scale_bottom), (scale_left, scale_bottom)])
    ```

    Lumilikha ito ng polygon gamit ang bounding box ng isang prediksyon.

1. Ang lohika para sa pag-aalis ng overlapping objects ay kinabibilangan ng paghahambing ng lahat ng bounding boxes, at kung ang anumang pares ng prediksyon ay may bounding boxes na nag-o-overlap nang higit sa threshold, tanggalin ang isa sa mga prediksyon. Upang ihambing ang lahat ng prediksyon, ihahambing mo ang prediksyon 1 sa 2, 3, 4, at iba pa, pagkatapos ay 2 sa 3, 4, at iba pa. Ang sumusunod na code ay gumagawa nito:

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

    Ang overlap ay kinakalkula gamit ang Shapely `Polygon.intersection` method na nagbabalik ng polygon na may overlap. Ang area ay kinakalkula mula sa polygon na ito. Ang overlap threshold ay hindi isang absolute value, ngunit kailangang maging percentage ng bounding box, kaya ang pinakamaliit na bounding box ay hinahanap, at ang overlap threshold ay ginagamit upang kalkulahin kung anong area ang overlap na hindi lalampas sa percentage overlap threshold ng pinakamaliit na bounding box. Kung ang overlap ay lumampas dito, ang prediksyon ay minamarkahan para sa pagtanggal.

    Kapag ang isang prediksyon ay minarkahan para sa pagtanggal, hindi na ito kailangang suriin muli, kaya ang inner loop ay nagbe-break upang suriin ang susunod na prediksyon. Hindi mo maaaring tanggalin ang mga item mula sa isang list habang ini-iterate ito, kaya ang mga bounding boxes na nag-o-overlap nang higit sa threshold ay idinadagdag sa `to_delete` list, pagkatapos ay tinatanggal sa dulo.

    Sa huli, ang bilang ng stock ay ipinapakita sa console. Maaari itong ipadala sa isang IoT service upang magbigay ng alerto kung mababa ang stock levels. Ang lahat ng code na ito ay bago iguhit ang bounding boxes, kaya makikita mo ang mga prediksyon ng stock na walang overlaps sa mga na-generate na imahe.

    > 💁 Ito ay isang napaka-simpleng paraan upang alisin ang overlaps, na tinatanggal lang ang una sa isang overlapping pair. Para sa production code, mas maraming lohika ang dapat ilagay dito, tulad ng pagsasaalang-alang sa overlaps sa pagitan ng maraming object, o kung ang isang bounding box ay nasa loob ng isa pa.

1. Patakbuhin ang app habang nakatutok ang camera sa ilang stock sa isang istante. Ang output ay magpapakita ng bilang ng bounding boxes na walang overlaps na lumampas sa threshold. Subukang baguhin ang halaga ng `overlap_threshold` upang makita ang mga prediksyon na hindi isinasaalang-alang.

> 💁 Makikita mo ang code na ito sa [code-count/pi](../../../../../5-retail/lessons/2-check-stock-device/code-count/pi) o [code-count/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-count/virtual-iot-device) folder.

😀 Tagumpay ang iyong stock counter program!

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na dulot ng paggamit ng pagsasaling ito.