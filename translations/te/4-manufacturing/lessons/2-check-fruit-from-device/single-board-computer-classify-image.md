<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "e5896207b304ce1abaf065b8acc0cc79",
  "translation_date": "2026-01-07T06:50:11+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/single-board-computer-classify-image.md",
  "language_code": "te"
}
-->
# ఒక ఇమేజ్‌ను వర్గీకరించండి - వర్చువల్ IoT హార్డ్‌వేర్ మరియు రెస్ప్బెర్రీ పై

దీనిలో మీరు కెమెరాతో సేకరించిన ఇమేజ్‌ని Custom Vision సేవకు పంపించి దానిని వర్గీకరించాలని చేస్తారు.

## Custom Vision కు ఇమేజ్లు పంపించండి

Custom Vision సేవకు Python SDK ఉంది, దీన్ని మీరు ఇమేజ్లను వర్గీకరించడానికి ఉపయోగించవచ్చు.

### పనులు - Custom Vision కు ఇమేజ్లు పంపండి

1. VS Codeలో `fruit-quality-detector` ఫోల్డర్‌ను తెరవండి. మీరు వర్చువల్ IoT పరికరం ఉపయోగిస్తుంటే, టెర్మినల్‌లో వర్చువల్ ఎన్విరాన్‌మెంట్ నడుస్తుందని నిర్ధారించుకోండి.

1. Custom Visionకు ఇమేజ్లు పంపడానికి Python SDKను Pip ప్యాకేజీగా పొందుపరచవచ్చు. కింది కమాండ్‌తో దీన్ని ఇన్‌స్టాల్ చేయండి:

    ```sh
    pip3 install azure-cognitiveservices-vision-customvision
    ```

1. `app.py` ఫైల్ టాప్‌లో కింది ఇంపోర్ట్ స్టేట్‌మెంట్లను జోడించండి:

    ```python
    from msrest.authentication import ApiKeyCredentials
    from azure.cognitiveservices.vision.customvision.prediction import CustomVisionPredictionClient
    ```

    ఇది Custom Vision లైబ్రరీల నుండి కొన్ని మాడ్యూల్స్‌ని తీసుకొస్తుంది, ఒకటి prediction keyతో ఆటోమెంట్ చేసుకోడానికి, మరొకటి Custom Visionను కాల్ చేయగల prediction క్లయింట్ క్లాస్ అందిస్తుంది.

1. ఫైల్ చివర కింది కోడ్‌ను జోడించండి:

    ```python
    prediction_url = '<prediction_url>'
    prediction_key = '<prediction key>'
    ```

    `<prediction_url>`ను మీరు ఈ పాఠంలో మునుపుగా *Prediction URL* డైలాగ్ నుండి కాపీ చేసుకున్న URL తో మార్చండి. `<prediction key>`ని అదే డైలాగ్ నుండి కాపీ చేసుకున్న prediction keyతో మార్చండి.

1. *Prediction URL* డైలాగ్ అందించిన prediction URL సాదారణంగా REST ఎండ్‌పాయింట్ ని నేరుగా పిలవడానికి ఉపయోగిస్తారు. Python SDK URLలోని భాగాలను వేరుగా ఉపయోగిస్తుంది. కింది కోడ్‌తో ఈ URLని అవసరమైన భాగాలుగా విడగొట్టండి:

    ```python
    parts = prediction_url.split('/')
    endpoint = 'https://' + parts[2]
    project_id = parts[6]
    iteration_name = parts[9]
    ```

    ఇది URLని విడగొట్టి, `https://<location>.api.cognitive.microsoft.com` ఎండ్‌పాయింట్, ప్రాజెక్ట్ ID, ప్రచురించిన iteration పేరు తీసుకుంటుంది.

1. prediction చేయడానికి predictor ఆబ్జెక్ట్‌ను క్రింది కోడ్‌తో సృష్టించండి:

    ```python
    prediction_credentials = ApiKeyCredentials(in_headers={"Prediction-key": prediction_key})
    predictor = CustomVisionPredictionClient(endpoint, prediction_credentials)
    ```

    `prediction_credentials` prediction keyని చుట్టేస్తుంది. అవి ఎండ్‌పాయింట్‌కు సూచించునట్లు prediction client ఆబ్జెక్ట్ సృష్టించడానికి ఉపయోగిస్తారు.

1. కింది కోడ్‌తో ఇమేజ్‌ను Custom Visionకు పంపండి:

    ```python
    image.seek(0)
    results = predictor.classify_image(project_id, iteration_name, image)
    ```

    ఇది ఇమేజ్‌ను మొదటి నుంచి తిరిగి సెట్ చేసి prediction clientకు పంపిస్తుంది.

1. చివరగా, కింది కోడ్‌తో ఫలితాలను చూపించండి:

    ```python
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    ఇది తిరిగి వచ్చిన అన్ని predictions మీద లూప్ చేస్తూ వాటిని టెర్మినల్‌లో చూపిస్తుంది. probabilities 0 నుంచి 1 మధ్య ఫ్లోటింగ్ పాయింట్ సంఖ్యలు, 0 అంటే ట్యాగ్‌తో సరిపోయే అవకాశం 0%, 1 అంటే 100%.

    > 💁 ఇమేజ్ క్లాసిఫాయర్లు అన్ని వాడిన ట్యాగ్‌ల కోసం శాతం విలువలు ఇస్తాయి. ప్రతి ట్యాగ్‌కు ఆ ఇమేజ్ ఆ ట్యాగ్‌కు సరిపోయే అవకాశం ఉంటుంది.

1. మీ కోడ్‌ను నడపండి, మీ కెమెరాను ఏదైనా ఫలం లేదా సరిగ్గా ఉన్న ఇమేజ్ సెట్ దిశగా తీసుకుని చూడండి, లేదా వర్చువల్ IoT హార్డ్‌వేర్ వాడితే உங்கள் వెబ్‌క్యామ్‌లో కనిపించే ఫలం. కన్సోల్‌లో అవుట్‌పుట్ చూసెయ్యొచ్చు:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

    మీరు తీసుకున్న ఇమేజ్ మరియు ఈ విలువలను Custom Visionలో **Predictions** ట్యాబ్‌లో చూడవచ్చు.

    ![Custom Visionలో అరుపుగా 56.8% గా మరియు అరుపుగా లేని వాటి 43.1% గా అంచనా వేయబడిన అరటి](../../../../../translated_images/te/custom-vision-banana-prediction.30cdff4e1d72db5d.png)

> 💁 మీరు ఈ కోడ్‌ను [code-classify/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/pi) లేదా [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/virtual-iot-device) ఫోల్డర్లలో చూడొచ్చు.

😀 మీ ఫలం నాణ్యత క్లాసిఫయర్ ప్రోగ్రాం విజయవంతం అయ్యింది!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**తప్పింపు మనోగతం**:  
ఈ పత్రం AI అనuvadana సేవ [Co-op Translator](https://github.com/Azure/co-op-translator) ఉపయోగించి అనువదించబడింది. మేము ఖచ్చితత్వానికి ప్రయత్నించుతుంటే, యంత్ర అనuvadana లో లోపాలు లేదా అసమర్థతలు ఉండవచ్చు. మూల పత్రం తన స్వదేశీ భాషలో అధికారిక ప్రమాణం గా తీసుకోవాలి. ముఖ్యమైన సమాచారానికి, వృత్తిపరమైన మానవ అనuvadana సూచించబడుతుంది. ఈ అనuvadana ఉపయోగం ద్వారా ఏర్పడిన ఏవైనా అపార్థాలు లేదా తప్పుదోవలు కోసం మేము బాధ్యత వహించమం.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->