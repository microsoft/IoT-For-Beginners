<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9c4320311c0f2c1884a6a21265d98a51",
  "translation_date": "2026-01-07T04:01:20+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/single-board-computer-count-stock.md",
  "language_code": "te"
}
-->
# మీ IoT పరికరంనుండి స్టాక్ లెక్కించండి - వర్చువల్ IoT హార్డ్‌వేర్ మరియు రాస్ప్బెరీ పై

భవిష్యవాణుల మరియు వాటి బౌండింగ్ బాక్స్‌ల కలపడం ద్వారా చిత్రం లోని స్టాక్‌ను లెక్కించవచ్చు.

## బౌండింగ్ బాక్స్‌లు చూపించండి

సహాయక డీబగ్గింగ్ దశగా మీరు కేవలం బౌండింగ్ బాక్స్‌లను ముద్రించడమే కాక, చిత్రం పైన కూడా వాటిని రేఖింప చేయవచ్చు, ఇది చిత్రాన్ని క్యాప్చర్ చేసినప్పుడు డిస్క్ కు వ్రాయబడింది.

### పని - బౌండింగ్ బాక్స్‌లను ముద్రించండి

1. `stock-counter` ప్రాజెక్ట్ VS కోడ్ లో తెరిచి ఉండి, మీరు వర్చువల్ IoT పరికరం ఉపయోగిస్తుంటే వర్చువల్ ఎన్విరాన్మెంట్ యాక్టివేట్ చేయబడిందని నిర్ధారించండి.

1. కింద ఇచ్చిన విధంగా `for` లూప్ లోని `print` స్టేట్‌మెంట్‌ను మార్చండి, అలా చేస్తే బౌండింగ్ బాక్స్‌లు కన్సోల్‌లో ప్రింట్ అవుతాయి:

    ```python
    print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%\t{prediction.bounding_box}')
    ```

1. క్యామెరా ఒక షెల్ఫ్ లోని స్టాక్ పైన ఉన్నప్పుడు యాప్ ను రన్ చేయండి. బౌండింగ్ బాక్స్‌లు కన్సోల్ లో ముద్రింపబడతాయి, వాటి లెఫ్ట్, టాప్, వెడల్పు మరియు ఎత్తు విలువలు 0-1 మధ్య ఉంటాయి.

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   33.42%  {'additional_properties': {}, 'left': 0.3455171, 'top': 0.09916268, 'width': 0.14175442, 'height': 0.29405564}
    tomato paste:   34.41%  {'additional_properties': {}, 'left': 0.48283678, 'top': 0.10242918, 'width': 0.11782813, 'height': 0.27467814}
    tomato paste:   31.25%  {'additional_properties': {}, 'left': 0.4923783, 'top': 0.35007596, 'width': 0.13668466, 'height': 0.28304994}
    tomato paste:   31.05%  {'additional_properties': {}, 'left': 0.36416405, 'top': 0.37494493, 'width': 0.14024884, 'height': 0.26880276}
    ```

### పని - బౌండింగ్ బాక్స్‌లను చిత్రంపై గీయండి

1. చిత్రాలపై గీయడానికి [Pillow](https://pypi.org/project/Pillow/) పిప్ ప్యాకేజీ ఉపయోగించవచ్చు. దీన్ని ఈ కింది కమాండ్ తో ఇన్స్టాల్ చేయండి:

    ```sh
    pip3 install pillow
    ```

    మీరు వర్చువల్ IoT పరికరం వాడుతున్నట్లయితే, యాక్టివేట్ చేసిన వర్చువల్ ఎన్విరాన్మెంట్ లోనే ఈ కమాండ్ నడపండి.

1. `app.py` ఫైల్ టాప్ వద్ద కింది ఇంపోర్ట్ స్టేట్‌మెంట్‌ని జోడించండి:

    ```python
    from PIL import Image, ImageDraw, ImageColor
    ```

    ఇది చిత్రాన్ని ఎడిట్ చేయడానికి అవసరమైన కోడ్‌ను ఇంపోర్ట్ చేస్తుంది.

1. `app.py` ఫైల్ చివర కిందివి జోడించండి:

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

    ఇది ముందుగా సేవ్ చేసిన చిత్రాన్ని ఎడిట్ చేయడానికి ఓపెన్ చేస్తుంది. తర్వాత భవిష్యవాణులలోని బౌండింగ్ బాక్స్‌లను తీసుకొని 0-1 విలువల ఆధారంగా కుడి దిగువ కోఆర్డినేట్‌ను గణిస్తుంది. ఆ తర్వాత వాటిని చిత్ర పరిమాణాల ఆధారంగా సముచిత కోఆర్డినేట్లుగా మార్చుతుంది. ఉదాహరణకు, ఎడమ విలువ 0.5 ఉంటే, 600 పిక్సెల్ వెడల్పుని కలిగిన చిత్రంలో ఇది 300 గా మారుతుంది (0.5 x 600 = 300).

    ప్రతి బౌండింగ్ బాక్స్ ను ఎరుపు లైన్ తో చిత్రంలో గీయబడుతుంది. చివరగా ఎడిట్ చేసిన చిత్రం సేవ్ చేసి మూల చిత్రాన్ని మారుస్తుంది.

1. క్యామెరాను షెల్ఫ్ లోని స్టాక్ పైన ఉంచి యాప్ నడపండి. VS కోడ్ ఎక్స్ప్లోరర్ లో `image.jpg` ఫైల్ కనపడుతుంది, దానిని ఎంచుకొని బౌండింగ్ బాక్స్‌లను చూడవచ్చు.

    ![4 cans of tomato paste with bounding boxes around each can](../../../../../translated_images/te/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.jpg)

## స్టాక్ లెక్కించండి

పై చిత్రంలో, బౌండింగ్ బాక్స్‌ల కొద్దిగా ఓవర్‌ల్యాప్ ఉంది. ఈ ఓవర్‌ల్యాప్ ఎక్కువైతే, బాక్స్‌లు ఒకే వస్తువును సూచించవచ్చు. వస్తువులను సరిగా లెక్కించడానికి, గమనించదగ్గ ఓవర్‌ల్యాప్ ఉన్న బాక్స్‌లను మినహాయించాలి.

### పని - ఓవర్‌ల్యాప్‌ను ఉളిపి స్టాక్ లెక్కించండి

1. ట్రూపు లెక్కించడానికి [Shapely](https://pypi.org/project/Shapely/) పిప్ ప్యాకేజీ ఉపయోగించవచ్చు. మీరు రాస్ప్బెరీ పై ఉపయోగిస్తుంటే ముందుగా లైబ్రరీ డిపెండెన్సీ ఇన్స్టాల్ చేయాలి:

    ```sh
    sudo apt install libgeos-dev
    ```

1. Shapely పిప్ ప్యాకేజీని ఇన్స్టాల్ చేయండి:

    ```sh
    pip3 install shapely
    ```

    వర్చువల్ IoT పరికరం వాడుతున్నట్లయితే, యాక్టివేట్ అయిన వర్చువల్ ఎన్విరాన్మెంట్ లోనే ఇది నడపండి.

1. `app.py` ఫైల్ టాప్ వద్ద కింది ఇంపోర్ట్ స్టేట్‌మెంట్ జోడించండి:

    ```python
    from shapely.geometry import Polygon
    ```

    ఇది ఓవర్ల్యాప్ గణించడానికి పొలిగాన్లు సృష్టించడానికి అవసరమైన కోడ్‌ను తీసుకురాదు.

1. బౌండింగ్ బాక్స్‌లను గీయే కోడ్ కి పూర్వం క్రిందివి జోడించండి:

    ```python
    overlap_threshold = 0.20
    ```

    ఇది బౌండింగ్ బాక్స్‌లు ఒకే వస్తువుగా పరిగణించడానికి అనుమతించబడిన ఓవర్ల్యాప్ శాతం నిర్వచిస్తుంది. 0.20 అంటే 20% ఓవర్ల్యాప్.

1. Shapely ఉపయోగించి ఓవర్ల్యాప్ లెక్కించడానికి బౌండింగ్ బాక్స్‌లు Shapely పొలిగాన్లుగా మార్చాలి. ఇది చేయడానికి కింది ఫంక్షన్ జోడించండి:

    ```python
    def create_polygon(prediction):
        scale_left = prediction.bounding_box.left
        scale_top = prediction.bounding_box.top
        scale_right = prediction.bounding_box.left + prediction.bounding_box.width
        scale_bottom = prediction.bounding_box.top + prediction.bounding_box.height
    
        return Polygon([(scale_left, scale_top), (scale_right, scale_top), (scale_right, scale_bottom), (scale_left, scale_bottom)])
    ```

    ఇది ఒక భవిష్యవాణు బౌండింగ్ బాక్స్ ఉపయోగించి పొలిగాన్ సృష్టిస్తుంది.

1. ఓవర్ల్యాప్ ఉన్న వస్తువులను తొలగించే విధానం అన్ని బాక్స్‌లను పోల్చడం, అప్పుడు ఓవర్ల్యాప్ సరిహద్దును మించితే వాటిలో ఒకటి తొలగించడం. సర్వ భవిష్యవాణులని పోల్చడానికి, మొదట 1 వ prediction ను 2,3,4తో పోల్చి, ఆ తర్వాత 2 వ prediction 3,4తో తులన చేయడం జరుగుతుంది. ఇలా చేస్తూ కింది కోడ్ ఉంటది:

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

    ఓవర్ల్యాప్ Shapely `Polygon.intersection` పద్ధతి ఉపయోగించి లెక్కించబడుతుంది. అది ఓవర్ల్యాప్ ఉన్న పొలిగాన్ ని ఇస్తుంది. ఆ పొలిగాన్ యొక్క ఏరియా లెక్కించబడుతుంది. ఈ ఓవర్ల్యాప్ పరిమితి ఖచ్చితమైన విలువ కాకుండా శాతం. కాబట్టి చిన్న బౌండింగ్ బాక్స్ కనుగొని, ఓవర్ల్యాప్ పరిమితి ఈ చిన్న బాక్స్ ఓవర్ల్యాప్ పరిమితినీ మించనప్పుడు ఏరియా ఎంత ఉండాలో లెక్కిస్తుంది. ఓవర్ల్యాప్ ఇది మించితే prediction తొలగింపుకు మార్క్ చేయబడుతుంది.

    ఒక prediction తొలగింపుకు మార్కయిన తరువాత మళ్లీ తనిఖీ చేయాల్సిన అవసరం లేదు, కాబట్టి లోపలి లూప్ బ్రేక్ అవుతుంది తదుపరి prediction ని తనిఖీ చేయడానికి. మీరు ఐటంస్ ను లిస్ట్ ని తిరుగుతూ తొలగించలేరు, అందువల్ల ఓవర్ల్యాప్ ఎక్కువ ఉన్న బాక్స్‌లు `to_delete` జాబితాలో చేర్చబడి, తరువాత చివరలో తొలగించబడతాయి.

    తరువాత స్టాక్ కౌంట్ కన్సోల్‌లో ప్రింట్ అవుతుంది. దీన్ని తక్కువ స్టాక్ స్థాయిలను అలర్ట్ చేసే IoT సర్వీస్ కి పంపవచ్చు. ఈ కోడ్ బౌండింగ్ బాక్స్ గీయే ముందు ఉంది, కాబట్టి మీరు ఓవర్ల్యాప్ లేని prediction లను చూడగలరు గనుక జనరేట్ అయిన చిత్రాల్లో.

    > 💁 ఇది ఓవర్ల్యాప్‌ను తొలగించే అత్యంత సరళమైన విధానం, ఓవర్లాప్ జంటలో మొదటిదే తీసివేయడం. ప్రొడక్షన్ కోడ్ కోసం, మీరు ఇక్కడ మరింత తర్కాన్ని జోడించాలని కోరుకుంటారు, ఉదాహరణకు బహుళ వస్తువుల మధ్య ఓవర్ల్యాప్‌లను పరిగణించటం, లేదా ఒక బాక్స్ మరొకదిలో ఉండటం వంటి పరిస్థితులు.

1. క్యామెరాని షెల్ఫ్ పై ఉన్న కొన్ని స్టాక్ పైన ఉంచి యాప్ నడపండి. ఔట్‌పుట్ ఓవర్లాప్‌లతో కూడిన బౌండింగ్ బాక్స్‌లు లెక్కించిన పరిమితి దాటిన వాటి సంఖ్యను చూపుతుంది. `overlap_threshold` విలువను సర్దుబాటు చేసి prediction ఎవరూ అర్ధం కావడం నివారించండి.

> 💁 ఈ కోడ్‌ను [code-count/pi](../../../../../5-retail/lessons/2-check-stock-device/code-count/pi) లేదా [code-count/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-count/virtual-iot-device) ఫోల్డర్‌లలో కనుగొనవచ్చు.

😀 మీ స్టాక్ కౌంటర్ ప్రోగ్రామ్ విజయవంతమైంది!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**అస్పష్టత**:
ఈ డాక్యుమెంట్‌ను AI అనువాద సేవ [Co-op Translator](https://github.com/Azure/co-op-translator) ఉపయోగించి అనువదించబడింది. మేము సరైనదిగా ఉంచేందుకు ప్రయత్నిస్తున్నప్పటికీ, ఆటోమేటెడ్ అనువాదాల్లో పొరపాట్లు లేదా తప్పులు ఉండొచ్చు. అసలు డాక్యుమెంట్ దాని స్థానిక భాషలో ఉన్నది ప్రామాణిక మూలం గా పరిగణించాలి. సంక్షిప్త సమాచారం కోసం, వృత్తిపరమైన మానవ అనువాదం సూచించబడుతుంది. ఈ అనువాదం వాడకం వల్ల కలిగే ఏదైనా అవగాహన తప్పుదోవ లేదా అర్థం తప్పిచేతపాటు కోసం మేము బాధ్యులు కారు.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->