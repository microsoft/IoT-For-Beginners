<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4cf1421420a6fab9ab4f2c391bd523b7",
  "translation_date": "2026-01-07T03:57:24+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-object-detector.md",
  "language_code": "te"
}
-->
# మీ IoT డివైస్ నుండి మీ ఆబ్జెక్ట్ డిటెక్టర్‌ను కాల్ చేయండి - Wio టర్మినల్

మీ ఆబ్జెక్ట్ డిటెక్టర్ ప్రచురించబడిన తర్వాత, అది మీ IoT డివైస్ నుండి ఉపయోగించవచ్చు.

## ఇమేజ్ క్లాసిఫైయర్ ప్రాజెక్టును కాపీ చేసుకోండి

మీ స్టాక్ డిటెక్టర్ యొక్క మెజారిటీ మీకు ముందు పాఠంలో మీరు సృష్టించిన ఇమేజ్ క్లాసిఫైయర్ తో ఒకటే ఉంటుంది.

### టాస్క్ - ఇమేజ్ క్లాసిఫైయర్ ప్రాజెక్టును కాపీ చేసుకోండి

1. [మాన్యుఫ్యాక్చరింగ్ ప్రాజెక్ట్ యొక్క పాఠం 2](../../../4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md#task---connect-the-camera) నుండి తీసుకున్న దశలను అనుసరించి మీ ArduCam ను మీ Wio టర్మినల్ కు కనెక్ట్ చేయండి.

    మీరు కెమెరాను ఒక స్థిర స్థితిలో సెట్ చేయాలని కూడా కోరుకోవచ్చు, ఉదాహరణకు, కేబుల్‌ను ఒక బాక్స్ లేదా క్యాన్ పై లేపడం లేదా కెమెరాను డబుల్-సైడెడ్ టేప్ తో బాక్స్ కి అద్దడం.

1. PlatformIO ఉపయోగించి కొత్త Wio టర్మినల్ ప్రాజెక్టును సృష్టించి, దీన్ని `stock-counter` అని పిలవండి.

1. కెమెరా నుండి చిత్రాలను క్యాప్చర్ చేయడానికి [మాన్యుఫ్యాక్చరింగ్ ప్రాజెక్ట్ యొక్క పాఠం 2](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) లోని దశలను ప్రతిరూపించండి.

1. ఇమేజ్ క్లాసిఫైయర్‌ను కాల్ చేయడానికి [మాన్యుఫ్యాక్చరింగ్ ప్రాజెక్ట్ యొక్క పీఠం 2](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) లోని దశలను ప్రతిరూపించండి. వస్తువులను గుర్తించడానికి ఈ కోడ్ లో ఎక్కువ భాగం మళ్ళీ ఉపయోగించబడుతుంది.

## క్లాసిఫైయర్ నుండి ఇమేజ్ డిటెక్టర్ గా కోడ్ మార్చండి

మీరు చిత్రాలను క్లాసిఫై చేయడానికి ఉపయోగించిన కోడ్ వస్తువులను గుర్తించడానికి ఉపయోగించే కోడ్‌కు చాలా సారూప్యం. ప్రధాన తేడా మీకు Custom Vision నుండి పొందిన URL మరియు కాల్ ఫలితాల్లో ఉంటుంది.

### టాస్క్ - కోడ్‌ను క్లాసిఫైయర్ నుండి ఇమేజ్ డిటెక్టర్‌గా మార్చడం

1. `main.cpp` ఫైల్ టాప్‌లో క్రింది ఇన్‌క్లూడ్ డైరెక్టివ్ ను చేర్చండి:

    ```cpp
    #include <vector>
    ```

1. `classifyImage` ఫంక్షన్ పేరును `detectStock` గా మార్చండి, ఫంక్షన్ పేరు మరియు `buttonPressed` ఫంక్షన్ లో దీనికి సంబంధించిన కాల్ మార్చండి.

1. `detectStock` ఫంక్షన్ ముందరి భాగంలో, తక్కువ కారణసంభావ్యత ఉన్న గుర్తింపులను వడపోసం చేయడానికి ఒక థ్రెషోల్డ్ ని ప్రకటించండి:

    ```cpp
    const float threshold = 0.3f;
    ```
  
    ఒక్క ట్యాగ్‌కు ఒక్క ఫలితం మాత్రమే ఇచ్చే ఇమేజ్ క్లాసిఫైయర్ కంటే వేరుగా, ఆబ్జెక్ట్ డిటెక్టర్ బహుళ ఫలితాలు ఇస్తుంది, కాబట్టి తక్కువ కారణసంభావ్యత ఉన్న ఫలితాలు వడపోసం చేయవలసి ఉంటుంది.

1. `detectStock` ఫంక్షన్ ముందరి భాగంలో, అనుమానాలను ప్రాసెస్ చేయడానికి ఒక ఫంక్షన్ ప్రకటించండి:

    ```cpp
    void processPredictions(std::vector<JsonVariant> &predictions)
    {
        for(JsonVariant prediction : predictions)
        {
            String tag = prediction["tagName"].as<String>();
            float probability = prediction["probability"].as<float>();
    
            char buff[32];
            sprintf(buff, "%s:\t%.2f%%", tag.c_str(), probability * 100.0);
            Serial.println(buff);
        }
    }
    ```
  
    ఇది ఒక అనుమానాల జాబితాను తీసుకొని, వాటిని సిరియల్ మానిటర్లో ప్రింట్ చేస్తుంది.

1. `detectStock` ఫంక్షన్‌లో, అనుమానాల్లో లూప్ చేస్తున్న `for` లూప్ యొక్క కంటెంట్‌ను క్రింది విధంగా మార్చండి:

    ```cpp
    std::vector<JsonVariant> passed_predictions;

    for(JsonVariant prediction : predictions) 
    {
        float probability = prediction["probability"].as<float>();
        if (probability > threshold)
        {
            passed_predictions.push_back(prediction);
        }
    }

    processPredictions(passed_predictions);
    ```
  
    ఇది అనుమానాలను లూప్ చేసి, కారణసంభావ్యతను థ్రెషోల్డ్‌తో పోల్చుతుంది. థ్రెషోల్డ్ కంటే ఎక్కువ కారణసంభావ్యత కలిగిన అన్ని అనుమానాలు ఒక `list` లోకి జోడించి, `processPredictions` ఫంక్షన్‌కు పంపబడతాయి.

1. మీ కోడ్ అప్‌లోడ్ చేసి రన్ చేయండి. కెమెరాను షెల్ఫ్ పై ఉన్న వస్తువులకు చూపించి C బటన్ నొక్కండి. మీరు సిరియల్ మానిటర్ లో అవుట్పుట్ చూసుకోగలరు:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 17416
    tomato paste:   35.84%
    tomato paste:   35.87%
    tomato paste:   34.11%
    tomato paste:   35.16%
    ```
  
    > 💁 మీ చిత్రాలకు సరిపోయే విధంగా `threshold` ను సర్దుబాటు చేయవలసి ఉండవచ్చు.

    మీరు తీసుకున్న చిత్రం అలాగే ఈ విలువలను Custom Vision లో **Predictions** ట్యాబ్ లో చూడగలరు.

    ![4 క్యాన్లు టమోటో పేస్ట్ షెల్ఫ్ పై, వాటి 35.8%, 33.5%, 25.7% మరియు 16.6% గుర్తింపులతో](../../../../../translated_images/te/custom-vision-stock-prediction.942266ab1bcca341.png)

> 💁 ఈ కోడ్‌ను మీరు [code-detect/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-detect/wio-terminal) ఫోల్డర్ లో కనుగొనవచ్చు.

😀 మీ స్టాక్ కౌంటర్ ప్రోగ్రామ్ విజయవంతమైంది!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**జార్జీకి**:  
ఈ పత్రాన్ని AI అనువాద సేవ అయిన [Co-op Translator](https://github.com/Azure/co-op-translator) ఉపయోగించి అనువదించబడింది. మేము సరైనదిగా ఉండేందుకు ప్రయత్నించినప్పటికీ, ఆటోమేటెడ్ అనువాదాలలో పొరపాట్లు లేదా తప్పిదాలు ఉండవచ్చు. దయచేసి, ప్రామాణిక మూలంగా స్థానిక భాషలో ఉన్న అసలు పత్రాన్ని పరిగణించండి. ముఖ్యమైన సమాచారానికి వృత్తిపరమైన మనుష్య అనువాదం సిఫార్సు చేయబడుతుంది. ఈ అనువాదం ఉపయోగించడంలో ఉన్న ఏవైనా అవగాహన లోపాలు లేదా తప్పుగా అర్థం చేసుకోవడాల కోసం మేము బాధ్యులు కావడం లేదని గమనించండి.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->