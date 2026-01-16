<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0b2ae20b0fc8e73c9598dea937cac038",
  "translation_date": "2026-01-07T03:59:49+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-count-stock.md",
  "language_code": "ml"
}
-->
# നിങ്ങളുടെ IoT ഡിവൈസിൽ നിന്ന് സ്റ്റോക്ക് എണ്ണുക - Wio ടെർമിനൽ

പ്രക്ഷേപണംകളും അവയുടെ ബൗണ്ടിംഗ് ബോക്സുകളും സംയോജിപ്പിച്ച് ചിത്രത്തിൽ സ്റ്റോക്ക് എണ്ണാൻ ഉപയോഗിക്കാം.

## സ്റ്റോക്ക് എണ്ണുക

![4 ക്യാൻ ബൗണ്ടിംഗ് ബോക്സുകളോടെ ടമാടോ പാസ്റ്റ്](../../../../../translated_images/ml/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.jpg)

മുകളിൽ കാണിച്ച ചിത്രത്തിൽ, ബൗണ്ടിംഗ് ബോക്സുകൾക്ക് ചെറിയ ഒവർലാപ് ഉണ്ട്. ഈ ഒവർലാപ് വളരെ വലിയതായിരുന്നെങ്കിൽ, ബൗണ്ടിംഗ് ബോക്സുകൾ ഒരേ വസ്തുവിനെ സൂചിപ്പിക്കാം. വസ്തുക്കൾ ശരിയായി എണ്ണാൻ, ഗണ്യമായ ഒവർലാപ്പുള്ള ബോക്സുകൾ അവഗണിക്കേണ്ടതുണ്ട്.

### തൊഴിൽ - ഒവർലാപ്പ് അവഗണിച്ച് സ്റ്റോക്ക് എണ്ണുക

1. നിങ്ങളുടെ `stock-counter` പ്രോജക്ട് തുറക്കുക, അത് തുറന്നിട്ടില്ലെങ്കിൽ.

1. `processPredictions` ഫังก്ഷന്റെ മുകളിൽ താഴെ കൊടുത്തിരിക്കുന്ന കോഡ് ചേർക്കുക:

    ```cpp
    const float overlap_threshold = 0.20f;
    ```

    ഇത് ബൗണ്ടിംഗ് ബോക്സുകൾ ഒരേ വസ്തുവായെന്നു കണക്കാക്കുന്നതിന് മുമ്പ് അനുവദിച്ചിരിക്കുന്ന ശതമാനം ഒവർലാപ്പിനെ നിർവചിക്കുന്നു. 0.20 എന്നത് 20% ഒവർലാപ്പ് ആണ്.

1. ഇതിനു താഴെ, `processPredictions` ഫังก്ഷന്റെ മുകളിൽ, രണ്ട് റെക്റ്റങ്ങളും തമ്മിലുള്ള ഒവർലാപ്പ് കണക്കാക്കാൻ കോഡ് ചേർക്കുക:

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

    ഈ കോഡ് ചിത്രത്തിലെ പോയിന്റുകൾ സൂക്ഷിക്കാൻ `Point` സ്ട്രക്ചറും, ഇടതു മുകളിൽ നിന്നും വലതു താഴേക്ക് നിർവചിക്കുന്ന റെക്റ്റാങ്ഗിൾ നിർവഹിക്കുന്ന `Rect` സ്ട്രക്ചറും നിർവചിക്കുന്നു. തുടർന്ന്, ഇടതു മുകളിൽ നിന്നും വലതു താഴേക്ക് ലഭിക്കുന്ന കോർഡിനേറ്റുകൾ ഉപയോഗിച്ച് ഒരു റെക്റ്റാങ്ഗിളിന്റെ വിസ്തൃതിയ കണക്കാക്കുന്ന `area` ഫങ്ഷനും നിർവചിക്കുന്നു.

    ശേഷം, 2 റെക്റ്റങ്ങളുടെയും ഒവർലാപ്പിംഗ് ഏരിയ കണക്കാക്കുന്ന `overlappingArea` ഫംഗ്ഷൻ നിർവചിക്കുന്നു. ഒവർലാപ്പ് ഇല്ലാത്തപ്പോഴെന്നാൽ 0 നൽകുന്നു.

1. `overlappingArea` ഫംഗ്ഷനിനു താഴെ, ഒരു ബൗണ്ടിംഗ് ബോക്‌സിനെ `Rect` ആയി പരിവർത്തനം ചെയ്യാനുള്ള ഫംഗ്ഷൻ പ്രഖ്യാപിക്കുക:

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

    ഇത് ഒബ്ജക്റ്റ് ഡിറ്റക്റ്ററിൽ നിന്നും ഒരു പ്രവചനമെടുത്ത് ബൗണ്ടിംഗ് ബോക്സിനെ പുറത്തെടുത്ത് ബോക്സിൽ ഉള്ള മൂല്യങ്ങൾ ഉപയോഗിച്ച് ഒരു റെക്റ്റാങ്കിൾ നിർവചിക്കുന്നു. വലത് ഭാഗം ഇടതു ഭാഗത്തെയും വീതിയും കൂട്ടിയാണു കണക്കാക്കുന്നത്. താഴെ ഭാഗം മുകൾ ഭാഗത്തെയും ഉയരവും കൂട്ടിച്ചേർക്കുന്നതാണ്.

1. പ്രവചനങ്ങളെ തമ്മിൽ താരതമ്യം ചെയ്യേണ്ടതാണ്, 2 പ്രവചനങ്ങൾക്ക് ഒരു പരിധിയിൽ കൂടുതലുള്ള ഒവർലാപ്പുണ്ടെങ്കിൽ, ഒരുകാര്യവും നീക്കം ചെയ്യേണ്ടതുണ്ട്. ഒവർലാപ്പ് പരിധി ശതമാനം ആകുന്നത് കൊണ്ടു, ഏറ്റവും ചെറിയ ബൗണ്ടിംഗ് ബോക്സിന്റെ വിസ്തൃതിയുമായി ഗുണിച്ചുണ്ടാക്കേണ്ടതാണ്, ഒവർലാപ്പ് വിസ്തൃതിയുടെ ശതമാനം അതിനേക്കാൾ കൂടുതലാണെന്ന് പരിശോധിക്കാൻ, മുഴുവൻ ചിത്രത്തിന്റെ ശതമാനം അല്ല. ആദ്യം `processPredictions` ഫംഗ്ഷന്റെ ഉള്ളടക്കം മായ്ക്കുക.

1. ശൂന്യമായ `processPredictions` ഫംഗ്ഷനിൽ താഴെ കൊടുത്തത് ചേർക്കുക:

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

    ഈ കോഡ് ഒവർലാപ്പ് ഇല്ലാത്ത പ്രവചനങ്ങൾ സൂക്ഷിക്കാൻ ഒരു വെക്ടർ പ്രഖ്യാപിക്കുന്നു. തുടർന്ന് എല്ലാ പ്രവചനങ്ങളിലും ലൂപ്പ് നടത്തിയും, ബൗണ്ടിംഗ് ബോക്സിൽ നിന്നും `Rect` നിർമ്മിക്കുന്നു.

    തുടർന്ന്, ബാക്കി ഉള്ള പ്രവചനങ്ങളിൽ, നിലവിലെ പ്രവചനത്തിനു ശേഷം നിന്നുള്ള വരികൾ മുതൽ മാത്രമുളള ലൂപ് നടത്തുന്നു. ഇതോടെ ഒരു പ്രവചനത്തെ മറ്റൊന്നുമായി ഒരിക്കൽ മാത്രം താരതമ്യം ചെയ്യുന്നു - 1, 2 താരതമ്യം ചെയ്തു കഴിഞ്ഞാൽ 2, 1 താരതമ്യം ആവശ്യമില്ല, 2, 3, 4 മുതലായവ മാത്രം.

    പ്രവചന കൂട്ടുകെട്ടുകളിൽ ഓരോ യുദ്ധങ്ങളുടെ ഒവർലാപ്പ് വിസ്തൃതി കണക്കാക്കി, ഏറ്റവും ചെറിയ ബൗണ്ടിംഗ് ബോക്സിന്റെ വിസ്തൃതിയുമായുള്ള ശതമാനം ഒതി പരിധിയേത് മൂലമുള്ള പരീക്ഷണം നടത്തുന്നു. അതു കഴിഞ്ഞ് പ്രസക്തമായ പ്രവചനങ്ങൾ `passed_predictions` ശേഖരത്തിലേക്ക് ചേർക്കുന്നു.

    > 💁 ഇതൊരു വളരെ ലളിതമായ സഹായമാണ് ഒവർലാപ്പ് നീക്കം ചെയ്യാൻ, ഒവർലാപ്പുള്ള ജോടിയിൽ ആദ്യം കാണുന്ന прогноз തന്നെയാണ് നീക്കം செய்வത്. ഉത്പാദന കോഡിൽ, നല്ല ലൂഹങ്ങൾ ഉൾപ്പെടുത്തേണ്ടതാണ്, ഉദാ: പല വസ്തുക്കളുടെ ഒവർലാപ്പുകളും പരിഗണിക്കുക, അല്ലെങ്കിൽ ഒരു ബൗണ്ടിംഗ് ബോക്സ് മറ്റേതോയിൽ ഉൾപ്പെട്ടിരിക്കുന്നുവെങ്കിൽ.

1. ഇതിനു ശേഷം, `passed_predictions` ന്റെ വിശദാംശങ്ങൾ സീരിയൽ മോണിറ്ററിലേക്ക് അയയ്ക്കാനുള്ള കോഡ് ചേർക്കുക:

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

    ഈ കോഡ് `passed_predictions` വഴി ലൂപ്പ് ചെയ്ത് അവയുടെ വിവരം സീരിയൽ മോണിറ്ററിലേക്ക് പ്രിന്റ് ചെയ്യുന്നു.

1. ഇതിനു താഴെ, എണ്ണിയ വസ്തുക്കളുടെ എണ്ണം സീരിയൽ മോണിറ്ററില്‍ പ്രിന്റ് ചെയ്യാനുള്ള കോഡ് ചേർക്കുക:

    ```cpp
    Serial.print("Counted ");
    Serial.print(passed_predictions.size());
    Serial.println(" stock items.");
    ```

    ഇത് പിന്നീട് സ്റ്റോക്ക് നില കുറവാണെങ്കിൽ അറിയിപ്പ് നൽകാൻ IoT സർവീസിലേക്ക് അയയ്ക്കാവുന്നതാണ്.

1. നിങ്ങളുടെ കോഡ് അപ്‌ലോഡ് ചെയ്ത് പ്രവർത്തിപ്പിക്കുക. ക്യാമറ ഷെല്ഫിലുള്ള വസ്തുക്കൾവിലേക്ക് കുറിച്ച് C ബട്ടൺ ഒതുക്കുക. `overlap_threshold` മൂല്യം ക്രമീകരിച്ച് പ്രവചനങ്ങൾ അവഗണിക്കപ്പെടുന്നത് അവബോധിക്കുക.

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

> 💁 ഈ കോഡ് നിങ്ങൾക്ക് [code-count/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-count/wio-terminal) ഫോൾഡറിൽ ലഭ്യമാണ്.

😀 നിങ്ങളുടെ സ്റ്റോക്ക് കൗണ്ടർ പ്രോഗ്രാം വിജയകരമായി പൂർത്തിയായിരിക്കുന്നു!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**ഇതു സംബന്ധിച്ച പരാമർശം**:  
ഈ ഡോക്യുമെന്റ് AI വിവർത്തന സേവനായ [Co-op Translator](https://github.com/Azure/co-op-translator) ഉപയോഗിച്ച് വിവർത്തനം ചെയ്തതാണ്. നാം ശരിയായ വിവർത്തനത്തിന് ശ്രമിക്കുന്നതിനാൽ, സ്വയം പ്രവര്‍ത്തിക്കുന്ന വിവർത്തനങ്ങളിൽ പിശകുകൾ ഉണ്ടാകാൻ സാധ്യതയുണ്ടെന്ന് ദയവായി ശ്രദ്ധിക്കുക. പ്രാഥമിക ഭാഷയിലുള്ള ഒറിജിനൽ ഡോക്യുമെന്റ് ആണ് മാനദണ്ഡരൂപമുള്ള അവലംബം. നിർണായക വിവരങ്ങൾക്ക് പ്രൊഫഷണൽ മനുഷ്യ വിവർത്തനം നിർണായകമാണ്. ഈ വിവർത്തനത്തിന്റെ ഉപയോഗം മൂലം ഉദ്ഭവിക്കുന്ന കുഴപ്പങ്ങൾക്കും തെറ്റ് വ്യാഖ്യാനങ്ങൾക്കും ഞങ്ങൾ ഉത്തരവാദികളല്ല.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->