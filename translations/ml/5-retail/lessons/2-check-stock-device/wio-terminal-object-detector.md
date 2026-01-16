<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4cf1421420a6fab9ab4f2c391bd523b7",
  "translation_date": "2026-01-07T03:57:59+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-object-detector.md",
  "language_code": "ml"
}
-->
# നിങ്ങളുടെ IoT ഉപകരണത്തിൽ നിന്നുള്ള ഒബ്‌ജക്റ്റ് ഡിറ്റക്ടർ വിളിക്കുക - Wio ടെർമിനൽ

ഒരു തവണ നിങ്ങളുടെ ഒബ്‌ജക്റ്റ് ഡിറ്റക്ടർ പ്രസിദ്ധീകരിച്ചുകഴിഞ്ഞാൽ, അത് നിങ്ങളുടെ IoT ഉപകരണത്തിൽ നിന്ന് ഉപയോഗിക്കാൻ കഴിയും.

## ഇമേജ് ക്ലാസിഫയർ പ്രോജക്ട് പകർപ്പുചെയ്യുക

നിങ്ങളുടെ സ്റ്റോക്ക് ഡിറ്റക്ടറിന്റെ ഭൂരിഭാഗവും നിങ്ങൾ മുമ്പത്തെ പാഠത്തിൽ സൃഷ്ടിച്ച ഇമേജ് ക്ലാസിഫയറിനോട് സമാനമാണ്.

### ടാസ്‌ക് - ഇമേജ് ക്ലാസിഫയർ പ്രോജക്ട് പകർപ്പുചെയ്യുക

1. നിങ്ങളുടെ ArduCam നിങ്ങളുടെ Wio ടെർമിനലിൽ ബന്ധിപ്പിക്കുക, [മാനുഫാക്ചറിംഗിൻറെ പാഠം 2](../../../4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md#task---connect-the-camera) ലെ പടികൾ പാലിച്ച്.

    നിങ്ങൾക്ക് ക്യാമറ ഒരു സ്ഥലത്ത് നിശ്ചിതമാക്കി വയ്ക്കാനാവാം, ഉദാഹരണത്തിന്, കേബിള്‍ ഒരു ബോക്സിന് അല്ലെങ്കിൽ കാനിന മുകളിൽ തൂക്കിയിട്ട്, അല്ലെങ്കില്‍ ക്യാമറ രണ്ടുവശം ടേപ്പ് ഉപയോഗിച്ച് ഒരു ബോക്സില്‍ മുറുക്കി നിർത്തുന്നതിലൂടെ.

1. PlatformIO ഉപയോഗിച്ച് ഒരു പുതിയ Wio ടെർമിനൽ പ്രോജക്ട് സൃഷ്ടിക്കുക. ഈ പ്രോജക്ടിന് `stock-counter` എന്നും പേര് നല്‍കുക.

1. ക്യാമറയിൽ നിന്ന് ചിത്രങ്ങൾ പകര്‍ത്താൻ [മാനുഫാക്ചറിംഗിൻറെ പാഠം 2](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) ലെ പടികൾ പുനരാവർത്തിക്കുക.

1. ഇമേജ് ക്ലാസിഫയറിനെ വിളിക്കാൻ [മാനുഫാക്ചറിംഗിൻറെ പാഠം 2](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) ലെ പടികൾ പുനരാവർത്തിക്കുക. ഒബ്‌ജക്റ്റുകൾ തിരിച്ചറിയാൻ ഭൂരിഭാഗം കോഡ് വീണ്ടും ഉപയോഗിക്കും.

## കോഡ് ക്ലാസിഫയറിൽ നിന്ന് ഇമേജ് ഡിറ്റക്ടറായി മാറ്റുക

നിങ്ങൾ ചിത്രങ്ങൾ ക്ലാസിഫൈ ചെയ്ത കോഡ് ഒബ്‌ജക്റ്റുകൾ കണ്ടെത്താനുള്ള കോഡിനോട് വളരെ സമാനമാണ്. പ്രധാന വ്യത്യാസം Custom Vision-ൽ നിന്നു ലഭിച്ച URL-ഉം കോളിന്റെ ഫലവും ആണ്.

### ടാസ്‌ക് - കോഡ് ക്ലാസിഫയറിൽ നിന്ന് ഇമേജ് ഡിറ്റക്ടറായി മാറുക

1. `main.cpp` ഫയലിന്റെ മുകളിൽ താഴെയുള്ള ഇൻക്ലൂഡ് നിർദ്ദേശം ചേർക്കുക:

    ```cpp
    #include <vector>
    ```

1. `classifyImage` ഫംഗ്ഷൻ പേരിനെ `detectStock` ആയി മാറ്റുക, ഫംഗ്ഷന്റെ പേരും `buttonPressed` ഫംഗ‍ഷനിൽ ഉണ്ടായ کالും.

1. `detectStock` ഫംഗ്ഷനിന് മുകളിൽ, probability കുറഞ്ഞ ഡിറ്റക്ഷനുകൾ ഫിൽട്ടർ ചെയ്യാൻ ഒരു ത്രെഷോൾഡ് പ്രഖ്യാപിക്കുക:

    ```cpp
    const float threshold = 0.3f;
    ```

    ഒരു ടാഗിന് ഓരോ ഫലം മാത്രമാണ് നൽകുന്ന ഇമേജ് ക്ലാസിഫയറിനോട് വ്യത്യസ്തമായി, ഒബ്‌ജക്റ്റ് ഡിറ്റക്ടർ പല ഫലങ്ങളും നൽകും; അതിനാൽ കുറഞ്ഞ probability ഉള്ളവ ഫിൽട്ടർ ചെയ്യണം.

1. `detectStock` ഫംഗ്ഷനിന് മുകളിൽ, പ്രവചനങ്ങൾ പ്രോസസ്സുചെയ്യാൻ ഒരു ഫംഗ്ഷൻ പ്രഖ്യാപിക്കുക:

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

    ഇത് പ്രവചനങ്ങളുടെ പട്ടിക എടുത്ത് അവ സീരിയൽ മോണിറ്ററിൽ പ്രിന്റ് ചെയ്യുന്നു.

1. `detectStock` ഫംഗ്ഷനിലുണ്ടായ പ്രവചനങ്ങളുടെ ലാത്തിൽ ലൂപ്പിനുള്ള ഉള്ളടക്കം താഴെ പറയുന്നവയിലേക്ക് മാറ്റുക:

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

    ഇത് probability-നെ ത്രെഷോൾഡുമായി താരതമ്യം ചെയ്യ며 പ്രവചനങ്ങൾ പരിശോധിക്കുന്നു. ത്രെഷോൾഡിനേക്കാൾ probability കൂടിയ എല്ലാ പ്രവചനങ്ങളും `list`-ലാക്കി `processPredictions` ഫംഗ്ഷനിലേക്ക് അയയ്ക്കുന്നു.

1. നിങ്ങളുടെ കോഡ് അപ്‌ലോഡ് ചെയ്ത് പ്രവർത്തിപ്പിക്കുക. ക്യാമറയെ ഒരു ഷെൽഫിലെ ഒബ്‌ജക്റ്റുകളെ ലക്ഷ്യമിട്ടു C ബട്ടൺ മുട്ടുക. സീരിയൽ മോണിറ്ററിൽ ഔട്ട്പുട്ട് കാണാം:

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

    > 💁 നിങ്ങളുടെ ചിത്രങ്ങൾക്ക് അനുയോജ്യമായ മൂല്യം സെറ്റ് ചെയ്യാൻ `threshold` ക്രമീകരിക്കേണ്ടതായി വരാം.

    എടുത്ത ചിത്രം, ഈ മൂല്യങ്ങൾ എന്നിവ Custom Vision-ലുള്ള **Predictions** ടാബിൽ കാണാൻ സാധിക്കും.

    ![ഷെൽഫിലെ 4 ടൊമാറ്റോ പേസ്റ്റ് കാൻസുകൾ, നിരീക്ഷണത്തിനുള്ള പ്രവചനങ്ങൾ: 35.8%, 33.5%, 25.7%, 16.6%](../../../../../translated_images/ml/custom-vision-stock-prediction.942266ab1bcca341.png)

> 💁 ഈ കോഡ് [code-detect/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-detect/wio-terminal) ഫോൾഡറിൽ ലഭ്യമാണ്.

😀 നിങ്ങളുടെ സ്റ്റോക്ക് കൗണ്ടർ പ്രോഗ്രാം വിജയിപ്പിച്ചു!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**അസുരക്ഷാ കുറിപ്പ്**:
ഈ രേഖ AI വിവര്‍ത്തന സേവനം [Co-op Translator](https://github.com/Azure/co-op-translator) ഉപയോഗിച്ച് വിവര്‍ത്തനം ചെയ്‌തതാണ്. ഞങ്ങള്‍ ശരിയായ വിവര്‍ത്തനത്തിനായി പരിശ്രമിച്ചിട്ടുണ്ടെങ്കിലും, യാന്ത്രിക വിവര്‍ത്തനങ്ങളില്‍ പിഴവുകളും അസാധുതകളും ഉണ്ടാകാമെന്ന് कृപയുമായി ശ്രദ്ധിക്കുക. യഥാര്‍ത്ഥ രേഖ അതിൻ്റെ മാതൃഭാഷയിലാണ് ഔദ്യോഗിക ഉറവിടമായി കണക്കാക്കേണ്ടത്. ഗുരുതരമായ വിവരങ്ങള്‍ക്കായി, പ്രൊഫഷണൽ മനുഷ്യ വിവര്‍ത്തനം ശുപാർശ ചെയ്യപ്പെടുന്നു. ഈ വിവര്‍ത്തനത്തിന്റെ ഉപയോഗത്തിൽ നിന്ന് ഉളവാകുന്ന ഏതെങ്കിലും തെറ്റിദ്ധാരണകൾക്കോ ദുർവ്യാഖ്യാനങ്ങൾക്കോ ഞങ്ങൾ ഉത്തരവാദികളല്ല.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->