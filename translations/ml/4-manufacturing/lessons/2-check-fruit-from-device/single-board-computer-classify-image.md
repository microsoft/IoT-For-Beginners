<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "e5896207b304ce1abaf065b8acc0cc79",
  "translation_date": "2026-01-07T06:50:41+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/single-board-computer-classify-image.md",
  "language_code": "ml"
}
-->
# ഒരു ചിത്രം വർഗ്ഗીકृत ചെയ്യുക - വേർച്വൽ ഐഒടി ഹാർഡ്‌വെയർ ಮತ್ತು റാസ്പ്ബെറി പൈ

പാഠത്തിന്റെ ഈ ഭാഗത്തിൽ, ക്യാമറയിലൂടെ പിടിച്ചെടുത്ത ചിത്രം Custom Vision സർവിസിലേക്ക് അയച്ച് അതിനെ വർഗ്ഗീകരിക്കും.

## Custom Vision-ലേക്ക് ചിത്രങ്ങൾ അയയ്ക്കുക

Custom Vision സർവിസിന് ചിത്രങ്ങൾ വർഗ്ഗീകരിക്കാൻ ഉപയോഗിക്കാവുന്ന Python SDK ഉണ്ട്.

### ടാസ്‌ക് - Custom Vision-ലേക്ക് ചിത്രങ്ങൾ അയയ്ക്കുക

1. VS Code-ൽ `fruit-quality-detector` ഫോൾഡർ തുറക്കുക. നിങ്ങൾ ഒരു വേർച്വൽ ഐഒടി ഉപകരണം ഉപയോഗിക്കുന്നെങ്കിൽ, ടെർമിനലിൽ വേർച്വൽ എൻവയോൺമെന്റ് പ്രവർത്തിക്കുന്നുണ്ടെന്ന് ഉറപ്പാക്കുക.

1. Custom Vision-ലേക്ക് ചിത്രങ്ങൾ അയയ്ക്കാൻ Python SDK Pip പാക്കേജായി ലഭ്യമാണ്. താഴെ കൊടുത്ത കമാൻഡ് ഉപയോഗിച്ച് ഇത് ഇൻസ്റ്റാൾ ചെയ്യുക:

    ```sh
    pip3 install azure-cognitiveservices-vision-customvision
    ```

1. `app.py` ഫയലിന്റെ മുകളിലുള്ള ഭാഗത്ത് താഴെ കാണിക്കുന്ന ഇറക്കുമതി പ്രസ്താവനകൾ (import statements) ചേർക്കുക:

    ```python
    from msrest.authentication import ApiKeyCredentials
    from azure.cognitiveservices.vision.customvision.prediction import CustomVisionPredictionClient
    ```

    ഇത് Custom Vision ലൈബ്രറിയിൽനിന്നും ചില മോഡ്യൂളുകൾ ഉൾക്കൊള്ളുന്നു, prediction കീ ഉപയോഗിച്ച് പ്രমাণീകരിക്കാൻ ഒന്ന്, Custom Vision കോളുകൾക്കായി prediction ക്ലയന്റ് ക്ലാസ് നൽകാൻ ഒന്ന്.

1. ഫയലിന്റെ അവസാനത്ത് താഴെ കാണിക്കുന്ന കോഡ് ചേർക്കുക:

    ```python
    prediction_url = '<prediction_url>'
    prediction_key = '<prediction key>'
    ```

    `<prediction_url>` പാതിയിൽ ഈ പാഠത്തിൽ മുമ്പ് *Prediction URL* സംവാദ പെട്ടി നിൽക്കുന്ന URL പകർത്തി പകർത്തിയതു കൊണ്ടു മാറ്റുക. `<prediction key>` പാതിയിൽ അതേ സംവാദ പെട്ടിയിൽ നിന്നുള്ള prediction കീ പകർത്തി മാറ്റുക.

1. *Prediction URL* സംവാദം നൽകിയ prediction URL നേരിട്ട് REST എന്റ്പോയിന്റ് കോളുകൾക്കായി രൂപകൽപ്പന ചെയ്തതാണ്. Python SDK URLയുടെ ഭാഗങ്ങളെ വിവിധ സ്ഥലങ്ങളിൽ ഉപയോഗിക്കുന്നു. ഈ ബഹുഭാഗമായ URL വേർതിരിക്കാൻ താഴെ കാണുന്ന കോഡ് ചേർക്കുക:

    ```python
    parts = prediction_url.split('/')
    endpoint = 'https://' + parts[2]
    project_id = parts[6]
    iteration_name = parts[9]
    ```

    ഇത് URL വിഭജിച്ച് `https://<location>.api.cognitive.microsoft.com` എന്ന എൻഡ് പോയിന്റ്, പ്രോജക്റ്റ് ഐഡി, പ്രസിദ്ധീകരിച്ച iteration ന്റെ പേര് എന്നിവ പകര്‍ത്തുന്നു.

1. കീഴെ കാണുന്ന കോഡുപയോഗിച്ച് prediction നടത്താൻ predictor ഒബ്ജെക്റ്റ് സൃഷ്ടിക്കുക:

    ```python
    prediction_credentials = ApiKeyCredentials(in_headers={"Prediction-key": prediction_key})
    predictor = CustomVisionPredictionClient(endpoint, prediction_credentials)
    ```

    `prediction_credentials` prediction കീ അടിക്കുന്ന ഒരു റാപ്പറാണ്. ഇത് prediction ക്ലയന്റ് ഒബ്ജെക്റ്റ് സൃഷ്ടിക്കാൻ, എൻഡ് പോയിന്റ് സൂചിപ്പിച്ച് ഉപയോഗിക്കുന്നു.

1. താഴെ കൊടുത്ത കോഡുപയോഗിച്ച് ചിത്രം custom vision-ലേക്ക് അയക്കുക:

    ```python
    image.seek(0)
    results = predictor.classify_image(project_id, iteration_name, image)
    ```

    ചിത്രം തുടക്കത്തിലേക്ക് തിരികെ തിരിക്കുന്നു, ശേഷം prediction ക്ലയന്റിന് അയക്കുന്നു.

1. ഒടുവിൽ, താഴെ കൊടുത്ത കോഡുപയോഗിച്ച് ഫലങ്ങൾ കാണിക്കുക:

    ```python
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    ഈ കോഡ് തിരികെ ലഭിച്ച എല്ലാ പ്രവചനങ്ങളും തരം മാറി ടെർമിനലിൽ കാണിക്കും. ലഭിക്കുന്ന സാധ്യതകൾ അടങ്ങിയ ഫോോട്ടിങ്പോയിന്റ് നമ്പറുകൾ 0 മുതൽ 1 വരെ ആയിരിക്കും; 0 എന്നത്ടാറ്റാഗുമായി പൊരുത്തപ്പെടാനുള്ള 0% സാധ്യത, 1 എന്നത് 100% സാധ്യത എന്നാണ് സൂചിപ്പിക്കുന്നത്.

    > 💁 ചിത്രം വർഗ്ഗീകരണ-പ്രവർത്തനങ്ങൾ ഉപയോഗിച്ച ടാഗുകളിൽ ചെയ്താൽ ആ ടാഗിന്റെ ശതമാനങ്ങൾ തിരികെ നൽകും. ഓരോ ടാഗിനും ചിത്രത്തിന് ആ ടാഗുമായി പൊരുത്തപ്പെടാനുള്ള സാധ്യത ലഭിക്കും.

1. നിങ്ങളുടെ ക്യാമറ പഴം അല്ലെങ്കിൽ അനുയോജ്യമായ ചിത്രസെറ്റ്, അല്ലെങ്കിൽ വേർച്വൽ ഐഒടി ഹാർഡ്‌വെയർ ഉപയോഗിക്കുമ്പോൾ വെബ്ക്യാമിൽ പഴം കാണിക്കുന്ന വിധം പരിപ്രേക്ഷ്യത്തിലേക്ക് സൂചന നൽകുക. നിങ്ങള്ക്ക് ആവശ്യമുള്ള ഔട്ട്‌പുട്ട് കൺസോളിൽ കാണാം:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

    നിങ്ങൾ എടുത്ത ചിത്രവും ഇവയും Custom Vision-ലെ **Predictions** ടാബിൽ കാണാം.

    ![Custom Vision-ൽ പുരോഗമനത്തോടെ 56.8% പാകപ്പെട്ടതും 43.1% പാചകം ചെയ്യാത്തതുമായ ഒരു വാഴപ്പഴം](../../../../../translated_images/ml/custom-vision-banana-prediction.30cdff4e1d72db5d.png)

> 💁 ഈ കോഡ് നിങ്ങള്ക്ക് [code-classify/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/pi) അല്ലെങ്കിൽ [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/virtual-iot-device) ഫോൾഡറുകളിൽ ലഭ്യമാണ്.

😀 നിങ്ങളുടെ പഴം ഗുണമേൻമ വർഗ്ഗീകരണ പ്രോഗ്രാം വിജയകരമായി നടന്നു!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**അസൂയിപ്പ്**:  
ഈ ഡോക്യുമെന്റ് AI വിവർത്തന സേവനമായ [Co-op Translator](https://github.com/Azure/co-op-translator) ഉപയോഗിച്ച് വിവർത്തനം ചെയ്തതാണ്. ഞങ്ങൾ കൃത്യതയ്ക്കായി പരിശ്രമിക്കുന്നുവെങ്കിലും, ഓട്ടോമേറ്റഡ് വിവർത്തനങ്ങളിൽ പിശകുകൾ അല്ലെങ്കിൽ തെറ്റുകൾ ഉണ്ടാകാമെന്ന് ദയവായി അറിയുക. സ്വന്തം ഭാഷയിലെ യഥാർത്ഥ ഡോക്യുമെന്റ് എന്നതാണ് സત્તാധികാരമുള്ള ഉറവിടം. പ്രധാന വിവരങ്ങൾക്ക്, പ്രൊഫഷണൽ മനുഷ്യ വിവർത്തനം നിർദ്ദേശിക്കുന്നു. ഇതിലെ വിവർത്തന ഉപയോഗത്തിൽ നിന്നുണ്ടാകാവുന്ന തെറ്റിദ്ധാരണകൾക്കും ശരിയായി മനസിലാക്കാത്തതിനും ഞങ്ങൾ ഉത്തരവാദിത്വമെടുക്കുന്നില്ല.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->