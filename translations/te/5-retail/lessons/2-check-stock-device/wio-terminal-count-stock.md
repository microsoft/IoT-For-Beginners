<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0b2ae20b0fc8e73c9598dea937cac038",
  "translation_date": "2026-01-07T03:59:11+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-count-stock.md",
  "language_code": "te"
}
-->
# మీ IoT పరికరం నుండి స్టాక్ ని లెక్కించండి - Wio టర్మినల్

పరిణామాలు మరియు వాటి బౌండింగ్ బాక్స్‌ల కలయికను ఉపయోగించి చిత్రంలో స్టాక్‌ను లెక్కించవచ్చు.

## స్టాక్ లెక్కించండి

![ప్రతి క్యాన్ చుట్టూ బౌండింగ్ బాక్స్‌లతో 4 టొమాటో పేస్ట్ క్యాన్లు](../../../../../translated_images/te/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.jpg)

పై చిత్రం లో చూపినట్లు, బౌండింగ్ బాక్స్‌లు స్వల్పంగా ఒప్పుకుంటున్నాయి. ఈ ఒప్పింపు చాలా ఎక్కువగా ఉన్నట్లయితే, బౌండింగ్ బాక్స్‌లు అదే వస్తువు అని సూచించవచ్చు. వస్తువులను సరైనంగా లెక్కించడానికి, మీరు గణనీయమైన ఒప్పింపుతో ఉన్న బాక్స్‌లను అనామకంగా తీసుకోవాలి.

### పనితీరు - ఒప్పింపును నిర్లక్ష్యం చేయడం ద్వారా స్టాక్ లెక్కించడం

1. మీ `stock-counter` ప్రాజెక్ట్ ఇప్పటికే తెరవనట్లయితే, దాన్ని తెరవండి.

1. `processPredictions` ఫంక్షన్ కింద, ఈ క్రింది కో드를 జోడించండి:

    ```cpp
    const float overlap_threshold = 0.20f;
    ```

    ఇది బౌండింగ్ బాక్స్‌లు అదే వస్తువులు అని పరిగణించడానికి అనుమతించే శాతం ఒప్పింపును నిర్వచిస్తుంది. 0.20 అంటే 20% ఒప్పింపు.

1. దీని క్రింద, మరియు `processPredictions` ఫంక్షన్ పై, రెండు చతురస్రాల మధ్య ఒప్పింపును లెక్కించే క్రింది కో드를 జోడించండి:

    ```cpp
    struct Point {
        float x, y;
    };

    struct Rect {
        Point topLeft, bottomRight;
    };

    float area(Rect rect)
    {
        return abs(rect.bottomRight.x - rect.topLeft.x) * abs(rect.bottomRight.y - rect.topLeft.y);
    }
     
    float overlappingArea(Rect rect1, Rect rect2)
    {
        float left = max(rect1.topLeft.x, rect2.topLeft.x);
        float right = min(rect1.bottomRight.x, rect2.bottomRight.x);
        float top = max(rect1.topLeft.y, rect2.topLeft.y);
        float bottom = min(rect1.bottomRight.y, rect2.bottomRight.y);
    
    
        if ( right > left && bottom > top )
        {
            return (right-left)*(bottom-top);
        }
        
        return 0.0f;
    }
    ```

    ఈ కోడ్ చిత్రం పై పాయింట్లను నిల్వ చేయడానికి `Point` స్ట్రక్ట్ ని నిర్వచిస్తుంది, మరియు ఎడమ పై నుండి కుడి కింద వరకు సమన్వయంతో ఒక చతురస్రం నిర్వచించడానికి `Rect` స్ట్రక్ట్‌ను నిర్వచిస్తుంది. తర్వాత ఇది పై ఎడమ మరియు కుడి కింద సమన్వయాల నుండి ఒక చతురస్రం ప్రాంతం లెక్కించే `area` ఫంక్షన్‌ను నిర్వచిస్తుంది.

    తరువాత, ఇది 2 చతురస్రాల ఒప్పుకొంటున్న ప్రాంతాన్ని లెక్కించే `overlappingArea` ఫంక్షన్‌ను నిర్వచిస్తుంది. వాటి ఒప్పింపు లేకపోతే, ఇది 0 ని తిరిగి ఇస్తుంది.

1. `overlappingArea` ఫంక్షన్ క్రింద, ఒక బౌండింగ్ బాక్సును `Rect` గా మార్చడానికి క్రింది ఫంక్షన్‌ను ప్రకటించండి:

    ```cpp
    Rect rectFromBoundingBox(JsonVariant prediction)
    {
        JsonObject bounding_box = prediction["boundingBox"].as<JsonObject>();
    
        float left = bounding_box["left"].as<float>();
        float top = bounding_box["top"].as<float>();
        float width = bounding_box["width"].as<float>();
        float height = bounding_box["height"].as<float>();
    
        Point topLeft = {left, top};
        Point bottomRight = {left + width, top + height};
    
        return {topLeft, bottomRight};
    }
    ```

    ఇది వస్తువు గుర్తింపు నుండి ఒక పరిణామాన్ని తీసుకొని, బౌండింగ్ బాక్సును పొందుతుంది మరియు బౌండింగ్ బాక్స్ విలువలను ఉపయోగించి ఒక చతురస్రాన్ని నిర్వచిస్తుంది. కుడె వైపు ఎడమ + వెడల్పుతో లెక్కించబడుతుంది. దిగువ వైపు పై + ఎత్తుతో లెక్కించబడుతుంది.

1. పరిణామాలను ఒకదానితో మరొకటి సరిపోల్చాలి, మరియు 2 పరిణామాల మధ్య ఒప్పింపు హద్దును మించి ఉంటే, వాటిలో ఒకదాన్ని తొలగించాలి. ఒప్పింపు హద్దు శాతం కాబట్టి, అది सबसे చిన్న బౌండింగ్ బాక్స్ పరిమాణంతో గుణించి చూడాలి, తద్వారా ఒప్పింపు బౌండింగ్ బాక్స్ యొక్క ఇచ్చిన శాతం మించి ఉందా అని తనిఖీ చేయబడుతుంది, మొత్తం చిత్ర శాతం కాదు. `processPredictions` ఫంక్షన్ యొక్క కంటెంట్‌ను తొలగించడం మొదలుపెట్టండి.

1. ఖాళీ ఉన్న `processPredictions` ఫంక్షన్‌కు క్రింది కోడ్ జోడించండి:

    ```cpp
    std::vector<JsonVariant> passed_predictions;

    for (int i = 0; i < predictions.size(); ++i)
    {
        Rect prediction_1_rect = rectFromBoundingBox(predictions[i]);
        float prediction_1_area = area(prediction_1_rect);
        bool passed = true;

        for (int j = i + 1; j < predictions.size(); ++j)
        {
            Rect prediction_2_rect = rectFromBoundingBox(predictions[j]);
            float prediction_2_area = area(prediction_2_rect);

            float overlap = overlappingArea(prediction_1_rect, prediction_2_rect);
            float smallest_area = min(prediction_1_area, prediction_2_area);

            if (overlap > (overlap_threshold * smallest_area))
            {
                passed = false;
                break;
            }
        }

        if (passed)
        {
            passed_predictions.push_back(predictions[i]);
        }
    }
    ```

    ఈ కోడ్ ఒప్పించని పరిణామాలను నిల్వ చేయడానికి ఒక వెక్టర్‌ను ప్రకటిస్తుంది. తర్వాత అది అన్ని పరిణామాల్లో లూప్ చేసి, బౌండింగ్ బాక్స్ నుండి `Rect` సృష్టిస్తుంది.

    తర్వాత ఈ కోడ్ మిగిలిన పరిణామాలలో, ప్రస్తుత పరిణామం తర్వాత మొదలుకుని, లూప్ చేస్తుంది. ఇది పరిణామాలను ఒక దాని తర్వాత మరల తులన చేయకుండా ఆపుతుంది - ఒకసారి 1 మరియు 2 సరిపోల్చబడి ఉంటే, 2 ని 1తో పునఃస атмосферా అవసరం లేదు, కేవలం 3, 4తో మాత్రమే సరిపోల్చాలి.

    ప్రతి పరిణామ జత కోసం, ఒప్పుకున్న భాగాన్ని లెక్కిస్తుంది. అది తర్వాత చిన్న బౌండింగ్ బాక్స్ యొక్క ప్రాంతంతో పోల్చబడుతుంది - ఒప్పింపు చిన్న బౌండింగ్ బాక్స్ యొక్క హద్దు శాతాన్ని మించితే, పరిణామం గడపలేదు అని గుర్తించబడుతుంది. అన్ని ఒప్పింపులను పోల్చిన తర్వాత, పరిణామం పాస్ అయితే `passed_predictions` కలెక్షన్లో జోడించబడుతుంది.

    > 💁 ఇది చాలా సరళమైన విధానం, ఒప్పింపులను తొలగించడానికి, ఒక ఒప్పింపు జతలో మొదటిది తీసివేయడం మాత్రమే. ప్రొడక్షన్ కోడ్ కోసం, మీరు ఇక్కడ మరింత లాజిక్ 넣ాలి, ఉదాహరణకు, అనేక వస్తువుల మధ్య ఒప్పింపులను పరిగణలోనికి తీసుకోవడం లేదా ఒక బౌండింగ్ బాక్స్ మరొకటి చేత కవరైనట్లయితే.

1. తర్వాత, పాస్ అయిన పరిణామాల వివరాలను సీరియల్ మానిటర్‌కు పంపడానికి క్రింది కోడ్ జోడించండి:

    ```cpp
    for(JsonVariant prediction : passed_predictions)
    {
        String boundingBox = prediction["boundingBox"].as<String>();
        String tag = prediction["tagName"].as<String>();
        float probability = prediction["probability"].as<float>();

        char buff[32];
        sprintf(buff, "%s:\t%.2f%%\t%s", tag.c_str(), probability * 100.0, boundingBox.c_str());
        Serial.println(buff);
    }
    ```

    ఈ కోడ్ పాస్ అయిన పరిణామాలను లూప్ చేసి వాటి వివరాలను సీరియల్ మానిటర్‌లో ప్రింట్ చేస్తుంది.

1. దీని క్రింద, లెక్కించిన ఐటెమ్‌ల సంఖ్యను సీరియల్ మానిటర్‌లో ప్రింట్ చేయడానికి క్రింది కోడ్ జోడించండి:

    ```cpp
    Serial.print("Counted ");
    Serial.print(passed_predictions.size());
    Serial.println(" stock items.");
    ```

    తరువాత ఇది స్టాక్ స్థాయిలు తక్కువగా ఉన్నప్పుడు హెచ్చరిక ఇవ్వడానికి IoT సేవకు పంపవచ్చు.

1. మీ కోడ్‌ను అప్లోడ్ చేసి నడిపించండి. కెమెరాను శెల్ఫ్ పై వస్తువులపై ఉంచి C బటన్‌ను నొక్కండి. `overlap_threshold` విలువను సర్దుబాటు చేసి, పరిణామాలు నిర్లక్ష్యం చేయబడుతున్నాయా చూడండి.

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 17416
    tomato paste:   35.84%  {"left":0.395631,"top":0.215897,"width":0.180768,"height":0.359364}
    tomato paste:   35.87%  {"left":0.378554,"top":0.583012,"width":0.14824,"height":0.359382}
    tomato paste:   34.11%  {"left":0.699024,"top":0.592617,"width":0.124411,"height":0.350456}
    tomato paste:   35.16%  {"left":0.513006,"top":0.647853,"width":0.187472,"height":0.325817}
    Counted 4 stock items.
    ```

> 💁 మీరు ఈ కోడ్ ని [code-count/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-count/wio-terminal) ఫోల్డర్‌లో చూడవచ్చు.

😀 మీ స్టాక్ కౌంటర్ ప్రోగ్రామ్ విజయవంతమైంది!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**విమర్శన**:
ఈ దస్త్రాన్ని AI అనువాద సేవ [Co-op Translator](https://github.com/Azure/co-op-translator) ఉపయోగించి అనువదించబడింది. మేము ఖచ్చితత్వానికి కృషి చేస్తూ ఉంటాము, కానీ ఆటోమేటెడ్ అనువాదాల్లో పొరపాట్లు లేదా అస్పష్టతలు ఉండొచ్చు. మూల దస్త్రం స్థానిక భాషలోని అధికారం కలిగిన మూలంగా పరిగణించాలి. కీలక సమాచారం కోసం ప్రొఫెషనల్ మానవ అనువాదాన్ని సూచించబడుతుంది. ఈ అనువాదం వాడకం వల్ల కలిగే ఏవైనా తప్పుదోషాలు లేదా తప్పు అర్థం చేసుకోవడాలకు మేము బాధ్యత వహించము.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->