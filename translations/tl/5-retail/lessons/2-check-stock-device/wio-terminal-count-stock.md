<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0b2ae20b0fc8e73c9598dea937cac038",
  "translation_date": "2025-08-27T20:44:14+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-count-stock.md",
  "language_code": "tl"
}
-->
# Bilangin ang stock mula sa iyong IoT device - Wio Terminal

Ang kombinasyon ng mga prediksyon at kanilang bounding boxes ay maaaring gamitin upang bilangin ang stock sa isang imahe.

## Bilangin ang stock

![4 na lata ng tomato paste na may bounding boxes sa paligid ng bawat lata](../../../../../translated_images/tl/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.webp)

Sa imahe na ipinakita sa itaas, ang mga bounding boxes ay may kaunting overlap. Kung mas malaki ang overlap, maaaring ipahiwatig ng mga bounding boxes na ito ay iisang bagay. Upang mabilang nang tama ang mga bagay, kailangan mong huwag pansinin ang mga kahon na may malaking overlap.

### Gawain - bilangin ang stock na hindi isinasaalang-alang ang overlap

1. Buksan ang iyong proyekto na `stock-counter` kung hindi pa ito nakabukas.

1. Sa itaas ng function na `processPredictions`, idagdag ang sumusunod na code:

    ```cpp
    const float overlap_threshold = 0.20f;
    ```

    Tinutukoy nito ang porsyento ng overlap na pinapayagan bago ituring na iisang bagay ang mga bounding boxes. Ang 0.20 ay tumutukoy sa 20% overlap.

1. Sa ibaba nito, at sa itaas ng function na `processPredictions`, idagdag ang sumusunod na code upang kalkulahin ang overlap sa pagitan ng dalawang parihaba:

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

    Ang code na ito ay tumutukoy sa isang `Point` struct upang mag-imbak ng mga punto sa imahe, at isang `Rect` struct upang tukuyin ang isang parihaba gamit ang isang top left at bottom right na coordinate. Pagkatapos, tinutukoy nito ang isang `area` function na kinakalkula ang lugar ng isang parihaba mula sa top left at bottom right na coordinate.

    Susunod, tinutukoy nito ang isang `overlappingArea` function na kinakalkula ang overlapping area ng 2 parihaba. Kung hindi sila nag-o-overlap, nagbabalik ito ng 0.

1. Sa ibaba ng function na `overlappingArea`, magdeklara ng isang function upang i-convert ang isang bounding box sa isang `Rect`:

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

    Kinukuha nito ang isang prediksyon mula sa object detector, kinukuha ang bounding box at ginagamit ang mga halaga sa bounding box upang tukuyin ang isang parihaba. Ang kanang bahagi ay kinakalkula mula sa kaliwa kasama ang lapad. Ang ibaba ay kinakalkula bilang taas kasama ang taas.

1. Kailangang ihambing ang mga prediksyon sa isa't isa, at kung ang 2 prediksyon ay may overlap na higit sa threshold, kailangang tanggalin ang isa sa mga ito. Ang overlap threshold ay isang porsyento, kaya kailangang i-multiply ito sa laki ng pinakamaliit na bounding box upang suriin kung ang overlap ay lumampas sa ibinigay na porsyento ng bounding box, hindi ang ibinigay na porsyento ng buong imahe. Simulan sa pamamagitan ng pagtanggal ng nilalaman ng function na `processPredictions`.

1. Idagdag ang sumusunod sa walang laman na function na `processPredictions`:

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

    Ang code na ito ay nagdedeklara ng isang vector upang mag-imbak ng mga prediksyon na walang overlap. Pagkatapos ay inuulit nito ang lahat ng prediksyon, lumilikha ng isang `Rect` mula sa bounding box.

    Susunod, inuulit ng code na ito ang natitirang mga prediksyon, simula sa isa pagkatapos ng kasalukuyang prediksyon. Pinipigilan nito ang mga prediksyon na maihambing nang higit sa isang beses - kapag ang 1 at 2 ay naihambing na, hindi na kailangang ihambing ang 2 sa 1, kundi sa 3, 4, at iba pa.

    Para sa bawat pares ng prediksyon, kinakalkula ang overlapping area. Pagkatapos ay inihahambing ito sa lugar ng pinakamaliit na bounding box - kung ang overlap ay lumampas sa threshold na porsyento ng pinakamaliit na bounding box, ang prediksyon ay minamarkahan bilang hindi pumasa. Kung pagkatapos ng paghahambing ng lahat ng overlap, ang prediksyon ay pumasa sa mga pagsusuri, idinadagdag ito sa koleksyon ng `passed_predictions`.

    > 💁 Napaka-simpleng paraan ito upang alisin ang mga overlap, basta't tinatanggal ang una sa isang pares na nag-o-overlap. Para sa production code, mas maraming lohika ang nais mong idagdag dito, tulad ng pagsasaalang-alang sa mga overlap sa pagitan ng maraming bagay, o kung ang isang bounding box ay nasa loob ng isa pa.

1. Pagkatapos nito, idagdag ang sumusunod na code upang ipadala ang mga detalye ng mga prediksyon na pumasa sa serial monitor:

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

    Ang code na ito ay inuulit ang mga prediksyon na pumasa at iniimprenta ang kanilang mga detalye sa serial monitor.

1. Sa ibaba nito, magdagdag ng code upang i-print ang bilang ng mga nabilang na item sa serial monitor:

    ```cpp
    Serial.print("Counted ");
    Serial.print(passed_predictions.size());
    Serial.println(" stock items.");
    ```

    Maaari itong ipadala sa isang IoT service upang magbigay ng alerto kung mababa na ang antas ng stock.

1. I-upload at patakbuhin ang iyong code. Itutok ang camera sa mga bagay sa isang istante at pindutin ang C button. Subukang ayusin ang halaga ng `overlap_threshold` upang makita ang mga prediksyon na hindi pinapansin.

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

> 💁 Maaari mong mahanap ang code na ito sa [code-count/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-count/wio-terminal) na folder.

😀 Tagumpay ang iyong stock counter program!

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na maaaring magmula sa paggamit ng pagsasaling ito.