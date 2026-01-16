<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9c4320311c0f2c1884a6a21265d98a51",
  "translation_date": "2025-08-27T22:44:14+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/single-board-computer-count-stock.md",
  "language_code": "sw"
}
-->
# Hesabu hisa kutoka kwa kifaa chako cha IoT - Vifaa vya IoT vya Kijanja na Raspberry Pi

Mchanganyiko wa utabiri na masanduku yao ya mipaka unaweza kutumika kuhesabu hisa kwenye picha.

## Onyesha masanduku ya mipaka

Kama hatua ya kusaidia kutatua matatizo, unaweza si tu kuchapisha masanduku ya mipaka, lakini pia kuyachora kwenye picha iliyohifadhiwa kwenye diski wakati picha ilipokamatwa.

### Kazi - chapisha masanduku ya mipaka

1. Hakikisha mradi wa `stock-counter` umefunguliwa kwenye VS Code, na mazingira halisi yamewashwa ikiwa unatumia kifaa cha IoT cha kijanja.

1. Badilisha kauli ya `print` kwenye kitanzi cha `for` kuwa ifuatayo ili kuchapisha masanduku ya mipaka kwenye koni:

    ```python
    print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%\t{prediction.bounding_box}')
    ```

1. Endesha programu na kamera ikielekezwa kwenye hisa kwenye rafu. Masanduku ya mipaka yatachapishwa kwenye koni, na maadili ya kushoto, juu, upana na urefu kutoka 0-1.

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   33.42%  {'additional_properties': {}, 'left': 0.3455171, 'top': 0.09916268, 'width': 0.14175442, 'height': 0.29405564}
    tomato paste:   34.41%  {'additional_properties': {}, 'left': 0.48283678, 'top': 0.10242918, 'width': 0.11782813, 'height': 0.27467814}
    tomato paste:   31.25%  {'additional_properties': {}, 'left': 0.4923783, 'top': 0.35007596, 'width': 0.13668466, 'height': 0.28304994}
    tomato paste:   31.05%  {'additional_properties': {}, 'left': 0.36416405, 'top': 0.37494493, 'width': 0.14024884, 'height': 0.26880276}
    ```

### Kazi - chora masanduku ya mipaka kwenye picha

1. Kifurushi cha Pip [Pillow](https://pypi.org/project/Pillow/) kinaweza kutumika kuchora kwenye picha. Sakinisha kwa amri ifuatayo:

    ```sh
    pip3 install pillow
    ```

    Ikiwa unatumia kifaa cha IoT cha kijanja, hakikisha unaendesha hii kutoka ndani ya mazingira halisi yaliyoamilishwa.

1. Ongeza kauli ifuatayo ya uingizaji mwanzoni mwa faili ya `app.py`:

    ```python
    from PIL import Image, ImageDraw, ImageColor
    ```

    Hii inaingiza msimbo unaohitajika kuhariri picha.

1. Ongeza msimbo ufuatao mwishoni mwa faili ya `app.py`:

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

    Msimbo huu unafungua picha iliyohifadhiwa awali kwa ajili ya kuhariri. Kisha unapitia utabiri ukipata masanduku ya mipaka, na unakokotoa kuratibu ya chini kulia ukitumia maadili ya masanduku ya mipaka kutoka 0-1. Haya yanabadilishwa kuwa kuratibu za picha kwa kuzidisha na kipimo husika cha picha. Kwa mfano, ikiwa thamani ya kushoto ilikuwa 0.5 kwenye picha yenye upana wa pikseli 600, hii ingebadilishwa kuwa 300 (0.5 x 600 = 300).

    Kila sanduku la mipaka linachorwa kwenye picha kwa kutumia mstari mwekundu. Hatimaye picha iliyohaririwa inahifadhiwa, ikifunika picha ya awali.

1. Endesha programu na kamera ikielekezwa kwenye hisa kwenye rafu. Utaona faili ya `image.jpg` kwenye kivinjari cha VS Code, na utaweza kuichagua ili kuona masanduku ya mipaka.

    ![Mikebe 4 ya tomato paste na masanduku ya mipaka kuzunguka kila moja](../../../../../translated_images/sw/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.webp)

## Hesabu hisa

Kwenye picha iliyoonyeshwa hapo juu, masanduku ya mipaka yana mgongano mdogo. Ikiwa mgongano huu ungekuwa mkubwa zaidi, basi masanduku ya mipaka yanaweza kuonyesha kitu kimoja. Ili kuhesabu vitu kwa usahihi, unahitaji kupuuza masanduku yenye mgongano mkubwa.

### Kazi - hesabu hisa ukipuuza mgongano

1. Kifurushi cha Pip [Shapely](https://pypi.org/project/Shapely/) kinaweza kutumika kukokotoa mgongano. Ikiwa unatumia Raspberry Pi, utahitaji kusakinisha tegemezi la maktaba kwanza:

    ```sh
    sudo apt install libgeos-dev
    ```

1. Sakinisha kifurushi cha Shapely cha Pip:

    ```sh
    pip3 install shapely
    ```

    Ikiwa unatumia kifaa cha IoT cha kijanja, hakikisha unaendesha hii kutoka ndani ya mazingira halisi yaliyoamilishwa.

1. Ongeza kauli ifuatayo ya uingizaji mwanzoni mwa faili ya `app.py`:

    ```python
    from shapely.geometry import Polygon
    ```

    Hii inaingiza msimbo unaohitajika kuunda poligoni ili kukokotoa mgongano.

1. Juu ya msimbo unaochora masanduku ya mipaka, ongeza msimbo ufuatao:

    ```python
    overlap_threshold = 0.20
    ```

    Hii inafafanua asilimia ya mgongano inayoruhusiwa kabla ya masanduku ya mipaka kuchukuliwa kuwa kitu kimoja. 0.20 inafafanua mgongano wa 20%.

1. Ili kukokotoa mgongano kwa kutumia Shapely, masanduku ya mipaka yanahitaji kubadilishwa kuwa poligoni za Shapely. Ongeza kazi ifuatayo kufanya hivyo:

    ```python
    def create_polygon(prediction):
        scale_left = prediction.bounding_box.left
        scale_top = prediction.bounding_box.top
        scale_right = prediction.bounding_box.left + prediction.bounding_box.width
        scale_bottom = prediction.bounding_box.top + prediction.bounding_box.height
    
        return Polygon([(scale_left, scale_top), (scale_right, scale_top), (scale_right, scale_bottom), (scale_left, scale_bottom)])
    ```

    Hii inaunda poligoni kwa kutumia sanduku la mipaka la utabiri.

1. Mantiki ya kuondoa vitu vinavyogongana inahusisha kulinganisha masanduku yote ya mipaka na ikiwa jozi yoyote ya utabiri ina masanduku ya mipaka yanayogongana zaidi ya kizingiti, futa moja ya utabiri. Ili kulinganisha utabiri wote, unalinganisha utabiri wa 1 na 2, 3, 4, nk., kisha 2 na 3, 4, nk. Msimbo ufuatao unafanya hivi:

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

    Mgongano unakokotolewa kwa kutumia njia ya Shapely `Polygon.intersection` inayorejesha poligoni yenye mgongano. Eneo linakokotolewa kutoka kwa poligoni hii. Kizingiti cha mgongano si thamani kamili, bali kinahitaji kuwa asilimia ya sanduku la mipaka, hivyo sanduku la mipaka dogo zaidi linapatikana, na kizingiti cha mgongano kinatumika kukokotoa eneo ambalo mgongano hauwezi kuzidi asilimia ya kizingiti cha mgongano cha sanduku dogo zaidi. Ikiwa mgongano unazidi hili, utabiri unawekwa alama ya kufutwa.

    Mara utabiri unapowekwa alama ya kufutwa hauhitaji kuchunguzwa tena, hivyo kitanzi cha ndani kinavunjika ili kuchunguza utabiri unaofuata. Huwezi kufuta vitu kutoka kwenye orodha wakati unazunguka kupitia orodha hiyo, hivyo masanduku ya mipaka yanayogongana zaidi ya kizingiti yanaongezwa kwenye orodha ya `to_delete`, kisha kufutwa mwishoni.

    Hatimaye idadi ya hisa inachapishwa kwenye koni. Hii inaweza kisha kutumwa kwa huduma ya IoT ili kutoa tahadhari ikiwa viwango vya hisa viko chini. Msimbo huu wote uko kabla ya masanduku ya mipaka kuchorwa, hivyo utaona utabiri wa hisa bila migongano kwenye picha zinazozalishwa.

    > 💁 Hii ni njia rahisi sana ya kuondoa migongano, kwa kufuta tu moja ya jozi inayogongana. Kwa msimbo wa uzalishaji, ungetaka kuweka mantiki zaidi hapa, kama vile kuzingatia migongano kati ya vitu vingi, au ikiwa sanduku moja la mipaka limejumuishwa na jingine.

1. Endesha programu na kamera ikielekezwa kwenye hisa kwenye rafu. Matokeo yataonyesha idadi ya masanduku ya mipaka bila migongano inayozidi kizingiti. Jaribu kurekebisha thamani ya `overlap_threshold` ili kuona utabiri ukipuuzwa.

> 💁 Unaweza kupata msimbo huu kwenye folda ya [code-count/pi](../../../../../5-retail/lessons/2-check-stock-device/code-count/pi) au [code-count/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-count/virtual-iot-device).

😀 Programu yako ya kuhesabu hisa imefanikiwa!

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya tafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuchukuliwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.