<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d620a470d9dd8614d99824832978360a",
  "translation_date": "2026-01-07T03:42:20+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/virtual-device-translate-speech.md",
  "language_code": "te"
}
-->
# వాయిస్‌ను అనువదించు - వర్చువల్ IoT డివైస్

పాఠంలోని ఈ భాగంలో, మీరు స్పీచ్ సర్వీస్ ఉపయోగించి మాట్లాడే మాటను టెక్స్ట్‌గా మార్చేటపుడు అనువదించే కోడ్ రాస్తారు, తరువాత ట్రాన్స్‌లేటర్ సర్వీస్ ఉపయోగించి టెక్స్ట్‌ను అనువదించి, ఆపై మాట్లాడే స్పందనను సృష్టిస్తారు.

## స్పీచ్ సర్వీస్ ఉపయోగించి వాయిస్‌ను అనువదించండి

స్పీచ్ సర్వీస్ ఆడియోని తీసుకుని అదే భాషలో టెక్స్ట్‌గా మాత్రమే కాకుండా, అవుట్పుట్‌ని ఇతర భాషలకు కూడా అనువదించగలదు.

### పని - స్పీచ్ సర్వీస్ ఉపయోగించి వాయిస్‌ను అనువదించండి

1. VS కోడ్‌లో `smart-timer` ప్రాజెక్ట్‌ని తెరవండి, మరియు టెర్మినల్‌లో వర్చువల్ ఎన్విరాన్మెంట్ లోడ్ అయినదా లేదో చూసుకోండి.

1. ఇప్పటికే ఉన్న ఇంపోర్ట్స్ క్రింద క్రింది ఇంపోర్ట్ స్టేట్మెంట్లను జోడించండి:

    ```python
    from azure.cognitiveservices import speech
    from azure.cognitiveservices.speech.translation import SpeechTranslationConfig, TranslationRecognizer
    import requests
    ```

    ఇది వాయిస్‌ను అనువదించడానికి ఉపయోగించే క్లాసులను మరియు తరువాత ఈ పాఠంలో ట్రాన్స్‌లేటర్ సర్వీస్‌కు కాల్ చేయడానికి ఉపయోగించే `requests` లైబ్రరీని ఇంపోర్ట్ చేస్తుంది.

1. మీ స్మార్ట్ టైమర్‌కు 2 భాషలు సెట్ చేయబడ్డవి - LUIS శిక్షణకి ఉపయోగించిన సర్వర్ భాష (అదే భాష వినియోగదారునితో మాట్లాడటానికి మెసేజులు తయారుచేయడానికి కూడా వాడబడుతుంది), మరియు వినియోగదారు మాట్లాడే భాష. `language` వేరియబుల్‌ను వినియోగదారు మాట్లాడే భాషగా మార్చండి, మరియు `server_language` అనే కొత్త వేరియబుల్‌ను LUIS శిక్షణకి ఉపయోగించిన భాషకి కోసం జోడించండి:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    `<user language>` స్థానంలో మీరు మాట్లాడబోయే భాష యొక్క లోకేల్ పేరు రాయండి, ఉదాహరణకి ఫ్రెంచ్ కోసం `fr-FR`, కాన్టోనీస్ కోసం `zn-HK`.

    `<server language>` స్థానంలో LUIS శిక్షణకి ఉపయోగించిన భాష యొక్క లోకేల్ పేరు రాయండి.

    మైక్రోసాఫ్ట్ డాక్స్‌లోని [భాష మరియు వాయిస్ మద్దతు డాక్యుమెంట్](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text)లో మద్దతు ఉన్న భాషల మరియు వాటి లోకేల్ పేర్ల జాబితా కనుగొనవచ్చు.

    > 💁 మీరు బహుభాషలు మాట్లాడకపోతే, మీరు మీ ఇష్టభాష నుండి మీ ఇష్టమైన భాషకు అనువదించడానికి [Bing Translate](https://www.bing.com/translator) లేదా [Google Translate](https://translate.google.com) వంటి సర్వీస్ ఉపయోగించవచ్చు. ఈ సర్వీసులు అనువదించిన టెక్స్ట్ యొక్క ఆడియోను కూడా ప్లే చేయగలవు. అయితే, ఆడియోను వాయిస్ రికగ్నైజర్ కొంత భాగం వదలవచ్చు, కాబట్టి అనువదించిన టెక్స్ట్ ప్లే చేయడానికి అదనపు డివైస్ ఉపయోగించవలసి ఉండవచ్చు.
    >
    > ఉదాహరణకి, మీరు LUISని ఇంగ్లీష్‌లో శిక్షణ ఇచ్చి ఉంటే, కానీ వినియోగదారు భాషగా ఫ్రెంచ్ ఉపయోగిస్తే, Bing Translate ఉపయోగించి "set a 2 minute and 27 second timer" వాక్యాన్ని ఇంగ్లీష్ నుంచి ఫ్రెంచ్‌కు అనువదించి, **Listen translation** బటన్ ఉపయోగించి మీ మైక్రోఫోన్‌లో అనువాదాన్ని మాట్లాడించవచ్చు.
    >
    > ![Bing translateలో Listen translation బటన్](../../../../../translated_images/te/bing-translate.348aa796d6efe2a9.png)

1. `recognizer_config` మరియు `recognizer` డిక్లరేషన్లను క్రింద ఇవ్వబడిన రీతిగా మార్చండి:

    ```python
    translation_config = SpeechTranslationConfig(subscription=speech_api_key,
                                                 region=location,
                                                 speech_recognition_language=language,
                                                 target_languages=(language, server_language))
    
    recognizer = TranslationRecognizer(translation_config=translation_config)
    ```

    ఇది వినియోగదారు భాషలో మాట్లాడే మాటను గుర్తించడానికి అనువాద కాంఫిగరేషన్ సృష్టిస్తుంది, అలాగే వినియోగదారు మరియు సర్వర్ భాషలలో అనువాదాలను సృష్టిస్తుంది. ఆ తరువాత ఈ కాంఫిగ్ ఉపయోగించి అనువాద రికగ్నైజర్ - బహుభాషల్లో వాయిస్ గుర్తింపు అవుట్పుట్‌ను అనువదించగల స్పీచ్ రికగ్నైజర్ తయారుచేస్తుంది.

    > 💁 అసలైన భాషను `target_languages`లో పేర్కొనాలి, లేకపోతే మీరు ఏ అనువాదాలూ పొందరని గమనించండి.

1. `recognized` ఫంక్షన్‌ను నవీకరించండి, మరియు ఆ ఫంక్షన్ మొత్తం కాంటెంట్‌ను క్రింద ఇవ్వబడిన కోడ్‌తో మార్చండి:

    ```python
    if args.result.reason == speech.ResultReason.TranslatedSpeech:
        language_match = next(l for l in args.result.translations if server_language.lower().startswith(l.lower()))
        text = args.result.translations[language_match]
        if (len(text) > 0):
            print(f'Translated text: {text}')
    
            message = Message(json.dumps({ 'speech': text }))
            device_client.send_message(message)
    ```

    ఈ కోడ్‌ అనువాదం అయినందుకే గుర్తింపు ఈవెంట్ వెలుతుండదా అని తనిఖీ చేస్తుంది (ఈ ఈవెంట్ ఇతర సమయంలో కూడా వెలుతుంటుంది, ఉదాహరణకు మాట్లాడిన మాట గుర్తించబడితే కానీ అనువదించబడకపోతే). మాట్లాడిన మాట అనువదించబడితే, `args.result.translations` డిక్షనరీలో ఉన్న సర్వర్ భాషకు అనుగుణమైన అనువాదాన్ని కనుగొంటుంది.

    `args.result.translations` డిక్షనరీ లోకేల్ సెట్టింగ్‌లోని భాష భాగం ఆధారంగా కీ చేయబడుతుంది, మొత్తం సెట్టింగ్ ఆధారంగా కాదు. ఉదాహరణకు, మీరు `fr-FR` ఫ్రెంచ్‌కు అనువాదం కోరితే, డిక్షనరీలో `fr` అనే ఎంట్రీ ఉంటుంది, `fr-FR` కాదు.

    ఆ అనువదించిన టెక్స్ట్ ఆ తర్వాత IoT హబ్‌కు పంపబడుతుంది.

1. ఈ కోడ్‌ను నడిపించి అనువాదాలను పరీక్షించండి. మీ ఫంక్షన్ యాప్ నడుస్తోంది అని నిర్ధారించుకోండి, మరియు వినియోగదారు భాషలో టైమర్ కోరండి, మీరు ఆ భాష మాట్లాడి లేదా అనువాద యాప్ ఉపయోగించి చేయవచ్చు.

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    ```

## ట్రాన్స్‌లేటర్ సర్వీస్ ఉపయోగించి టెక్స్ట్‌ను అనువదించండి

స్పీచ్ సర్వీస్ టెక్స్ట్‌ను మళ్లీ మాట్లాడడం కోసం అనువదించుటను మద్దతు ఇవ్వదు, కాబట్టి మీరు ట్రాన్స్‌లేటర్ సర్వీస్ ద్వారా టెక్స్ట్‌ను అనువదించవచ్చు. ఈ సర్వీస్ REST API కలిగి ఉంటుంది, దీన్ని టెక్స్ట్ అనువదించడానికి ఉపయోగించవచ్చు.

### పని - ట్రాన్స్‌లేటర్ రిసోర్స్ ఉపయోగించి టెక్స్ట్‌ను అనువదించండి

1. `speech_api_key` క్రింద ట్రాన్స్‌లేటర్ API కీని జోడించండి:

    ```python
    translator_api_key = '<key>'
    ```

    `<key>` స్థానంలో మీ ట్రాన్స్‌లేటర్ సర్వీస్ రిసోర్స్ API కీ ఉన్నదాన్ని పెట్టండి.

1. `say` ఫంక్షన్ కింద, సర్వర్ భాష నుండి వినియోగదారు భాషకు టెక్స్ట్ అనువదించే `translate_text` ఫంక్షన్ నిర్వచించండి:

    ```python
    def translate_text(text):
    ```

1. ఈ ఫంక్షన్‌లో, REST API కాల్ కోసం URL మరియు హెడర్లను నిర్వచించండి:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    ఈ API URL ప్రత్యేక ప్రదేశానికి సంబంధించినది కాదు, ప్రదేశం హెడర్‌గా పంపబడుతుంది. API కీ నేరుగా ఉపయోగించబడుతుంది, అందుకే స్పీచ్ సర్వీస్ లాగానే టోకెన్ ఇష్యూ API నుండి యాక్సెస్ టోకెన్ పొందాల్సిన అవసరం లేదు.

1. దీనికి క్రింద కాల్ కోసం ప్యారామీటర్లు మరియు బాడీ నిర్వచించండి:

    ```python
    params = {
        'from': server_language,
        'to': language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` API కాల్‌కు పంపే ప్యారామీటర్లను నిర్వచిస్తుంది, `from` భాష నుండి `to` భాషకు అనువదించడానికి. ఈ కాల్ `from` భాషలో ఉన్న టెక్స్ట్‌ను `to` భాషలోకి అనువదిస్తుంది.

    `body` అనువదించవలసిన టెక్స్ట్‌ను కలిగి ఉంటుంది. ఇది అrrayగా ఉంటుంది, ఎందుకంటే ఒకే కాల్‌లో బహుళ టెక్స్ట్ బ్లాక్స్ అనువదించవచ్చు.

1. REST APIకి కాల్ చేసి ప్రతిస్పందన పొందండి:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    తిరిగి వచ్చే ప్రతిస్పందన JSON అrray లాగా ఉంటుంది, అందులో ఒక ఐటెం అనువాదాలను కలిగి ఉంటుంది. ఈ ఐటెం బాడీలో వచ్చిన అన్ని అంశాలకి అనువాదాల అrrayను కలిగి ఉంటుంది.

    ```json
    [
        {
            "translations": [
                {
                    "text": "Chronométrant votre minuterie de 2 minutes 27 secondes.",
                    "to": "fr"
                }
            ]
        }
    ]
    ```

1. అarrayలో మొదటి ఐటెం నుండి మొదటి అనువాదం నుంచి `text` ప్రాపర్టీని తిరిగి ఇవ్వండి:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. SSML సృష్టించే ముందు మాట్లాడే టెక్స్ట్‌ను అనువదించడానికి `say` ఫంక్షన్‌ను నవీకరించండి:

    ```python
    print('Original:', text)
    text = translate_text(text)
    print('Translated:', text)
    ```

    ఈ కోడ్ అసలు టెక్స్ట్ మరియు అనువదించిన టెక్స్ట్ రెండు కన్సోల్‌కు ప్రింట్ చేస్తుంది.

1. మీ కోడ్ నడిపించండి. మీ ఫంక్షన్ యాప్ నడుస్తోంది అని నిర్ధారించండి, మరియు వినియోగదారు భాషలో టైమర్ కోరండి, మీరు ఆ భాష మాట్లాడి లేదా అనువాద యాప్ ఉపయోగించి చేయవచ్చు.

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    Original: 2 minute 27 second timer started.
    Translated: 2 minute 27 seconde minute a commencé.
    Original: Times up on your 2 minute 27 second timer.
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

    > 💁 భిన్నమైన భాషల్లో ఒకే విషయం చెప్పే విధానం వలన, మీరు LUISకి ఇచ్చిన ఉదాహరణల కంటే కొంచెం భిన్నంగా అనువాదాలు వస్తాయేమో. అలాంటప్పుడు LUISలో మరికొన్ని ఉదాహరణలు జోడించి, మళ్లీ శిక్షణ తీసుకుని మోడల్‌ను రీస్‌పబ్లిష్ చేయండి.

> 💁 మీరు ఈ కోడ్‌ను [code/virtual-iot-device](../../../../../6-consumer/lessons/4-multiple-language-support/code/virtual-iot-device) ఫోల్డర్‌లో కనుగొనవచ్చు.

😀 మీ బహుభాషా టైమర్ ప్రోగ్రాం విజయవంతమైంది!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**అస్పష్టత**:  
ఈ దస్తావేజు [Co-op Translator](https://github.com/Azure/co-op-translator) అనే AI అనువాద సేవ ఉపయోగించి అనువదించబడింది. మా ప్రయత్నం సరైన అనువాదం అందించడం గానీ, స్వయంచాలక అనువాదంలో పొరపాట్లు లేదా తప్పుదోపులు ఉండొచ్చు. మూల భాషలో ఉన్న అసలు దస్తావేజును అధికారిక మూలం గా భావించాలని సూచించబడుతుంది. కీలక సమాచారం కోసం, నిపుణుల చేత ఇచ్చిన అనువాదం మంచిదైనది. ఈ అనువాదం వాడకం వలన జరిగిన ఏవైనా అవగాహన లో తప్పిదాలు లేదా దోషాలకు మేము బాధ్యత వహించము.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->