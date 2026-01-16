<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "bbb5aa34221fe129dd3ce4d9ec33831a",
  "translation_date": "2026-01-07T03:37:56+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/pi-translate-speech.md",
  "language_code": "te"
}
-->
# Translate speech - Raspberry Pi

ఈ పాఠంలోని భాగంలో, మీరు అనువాదక సేవ ఉపయోగించి వచనం అనువదించడానికి కోడ్ రాయబోతున్నారు.

## అనువాదక సేవ ఉపయోగించి వచనాన్ని స్పీచ్‌గా మార్చడం

స్పీచ్ సేవ REST API నేరుగా అనువాదాలను మద్దతు ఇవ్వడం లేదు, మీరు స్పీచ్-టు-టెక్స్‌ట్ సేవ ద్వారా సృష్టించబడిన వచనాన్ని మరియు మాట్లాడిన స్పందన వచనాన్ని అనువదించడానికి అనువాదక సేవను ఉపయోగించవచ్చు. ఈ సేవకు REST API ఉంది దీనిని మీరు వచనాన్ని అనువదించడానికి ఉపయోగించవచ్చు.

### పని - వచనాన్ని అనువదించడానికి అనువాదక వనరును ఉపయోగించండి

1. మీ స్మార్ట్ టైమర్‌లో 2 భాషలు సెట్ చేయబడతాయి - LUIS ను శిక్షణ ఇచ్చేందుకు ఉపయోగించిన సర్వర్ భాష (అదే భాష వాడుకరి తో మాట్లాడేందుకు సందేశాలు నిర్మించడానికి కూడా ఉపయోగించబడుతుంది), మరియు వాడుకరి మాట్లాడే భాష. `language` మార్పిడిని వాడుకరి మాట్లాడే భాషగా నవీకరించండి, మరియు LUIS శిక్షణకు ఉపయోగించే భాష కోసం `server_language` అనే కొత్త మార్పిడిని జోడించండి:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    మీరు మాట్లాడబోయే భాషకు స్థానిక నామాన్ని `<user language>` స్థానంలో ప్రతిస్థాపించండి, ఉదాహరణకు ఫ్రెంచ్ కోసం `fr-FR` లేదా కంటోనీన్ కోసం `zn-HK`.

    LUIS శిక్షణకు ఉపయోగించిన భాషకు స్థానిక నామాన్ని `<server language>` స్థానంలో ఉంచండి.

    మద్దతు పొందిన భాషల మరియు వారి స్థానిక నామాల జాబితాను [Language and voice support documentation on Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text)లో చూడవచ్చు.

    > 💁 మీరు బహుభాషలలో మాట్లాడకపోతే, మీరు మీ ఇష్ట భాష నుండి ఇంకొక భాషకు అనువదించడానికి [Bing Translate](https://www.bing.com/translator) లేదా [Google Translate](https://translate.google.com) వంటి సేవను ఉపయోగించవచ్చు. ఈ సేవలు అనువదించిన వచనానికి ఆడియో కూడా ప్లే చేయవచ్చు.
    >
    > ఉదాహరణకు, మీరు LUIS ను ఇంగ్లీష్‌లో శిక్షణ ఇచ్చి ఉంటే, కానీ వాడుకరి భాషగా ఫ్రెంచ్‌ని ఉపయోగించాలని కోరుకుంటే, మీరు "set a 2 minute and 27 second timer" వంటి వాక్యాలను Bing Translate ఉపయోగించి ఇంగ్లీష్ నుండి ఫ్రెంచ్ కు అనువదించి, **Listen translation** బటన్ ఉపయోగించి మీ మైక్రోఫోన్‌లో అనువాదాన్ని చెప్పవచ్చు.
    >
    > ![The listen translation button on Bing translate](../../../../../translated_images/te/bing-translate.348aa796d6efe2a9.png)

1. `speech_api_key` కింద అనువాదక API కీని జోడించండి:

    ```python
    translator_api_key = '<key>'
    ```

    మీ అనువాదక సేవ వనరుకి API కీని `<key>` స్థానంలో ఉంచండి.

1. `say` ఫంక్షన్ అడుగుపై, సర్వర్ భాష నుండి వాడుకరి భాషకు వచనాన్ని అనువదించడానికి `translate_text` అనే ఫంక్షన్‌ను నిర్వచించండి:

    ```python
    def translate_text(text, from_language, to_language):
    ```

    ఈ ఫంక్షన్ కు from మరియు to భాషలను పంపాలి - అధ్యయనం సమయంలో వాడుకరి భాష నుండి సర్వర్ భాషకు మార్చడం అవసరం, మరియు మాట్లాడిన అభిప్రాయాన్ని అందించేటప్పుడు సర్వర్ భాష నుండి వాడుకరి భాషకు మార్చాలి.

1. ఈ ఫంక్షన్ లో REST API కాల్ కోసం URL మరియు హెడ్డర్లను నిర్వచించండి:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    ఈ API కి URL స్థానికంగా ప్రత్యేకం కాదు, స్థానికతను హెడర్ గా పంపాలి. API కీ నేరుగా ఉపయోగిస్తారు, కాబట్టి స్పీచ్ సేవ వంటివి టోకెన్ జారీదారు API నుండి టోకెన్ పొందాల్సిన అవసరం లేదు.

1. దీని కింద కాల్ కోసం పరామితులు మరియు బాడీని నిర్వచించండి:

    ```python
    params = {
        'from': from_language,
        'to': to_language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` API కాల్ కు పంపాల్సిన పరామితులను నిర్వచిస్తుంది, `from` మరియు `to` భాషలను పంపుతుంది. ఈ కాల్ `from` భాషలో ఉన్న వచనాన్ని `to` భాషకు అనువదిస్తుంది.

    `body` అనువదించవలసిన వచనాన్ని కలిగి ఉంటుంది. ఇది ఒక అర్రే, ఎందుకంటే ఒకే కాల్ లో బహుళ వచన భాగాలను అనువదించొచ్చు.

1. REST API కాల్‌ను చేయండి, మరియు స్పందన పొందండి:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    వచ్చిన స్పందన JSON అర్రే, దీనిలో ఒక ఐటం ఉంటుంది ఇది అనువాదాలను కలిగి ఉంటుంది. ఈ ఐటమ్ బాడీలోని అన్ని అంశాల అనువాదాల కోసం అర్రే కలిగి ఉంటుంది.

    ```json
    [
        {
            "translations": [
                {
                    "text": "Set a 2 minute 27 second timer.",
                    "to": "en"
                }
            ]
        }
    ]
    ```

1. అర్రేలో మొదటి అంశం యొక్క మొదటి అనువాదం నుండి `text` ప్రాపర్టీని తిరిగి ఇవ్వండి:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. `while True` లూప్ ను మార్చి `convert_speech_to_text` కాల్ నుండి వచ్చే వచనాన్ని వాడుకరి భాష నుండి సర్వర్ భాషకు అనువదించండి:

    ```python
    if len(text) > 0:
        print('Original:', text)
        text = translate_text(text, language, server_language)
        print('Translated:', text)

        message = Message(json.dumps({ 'speech': text }))
        device_client.send_message(message)
    ```

    ఈ కోడ్ మౌలిక మరియు అనువదించిన వచనాలను కన్సోల్ లో ప్రింట్ చేస్తుంది.

1. `say` ఫంక్షన్ ను నవీకరించండి వాడుకరి భాష నుండి సర్వర్ భాషకు అనువదించిన వచనాన్ని మాట్లాడేందుకు:

    ```python
    def say(text):
        print('Original:', text)
        text = translate_text(text, server_language, language)
        print('Translated:', text)
        speech = get_speech(text)
        play_speech(speech)
    ```

    ఈ కోడ్ కూడా మౌలిక మరియు అనువదించిన వచనాలను కన్సోల్ లో ప్రింట్ చేస్తుంది.

1. మీ కోడ్‌ను అమలు చేయండి. మీ ఫంక్షన్ యాప్ నడుస్తుందో లేదో నిర్ధారించుకోండి, వాడుకరి భాషలో టైమర్ కోరండి, లేదా మీరు ఆ భాషలో మాట్లాడండి లేదా అనువాద యాప్ ఉపయోగించండి.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py
    Connecting
    Connected
    Using voice fr-FR-DeniseNeural
    Original: Définir une minuterie de 2 minutes et 27 secondes.
    Translated: Set a timer of 2 minutes and 27 seconds.
    Original: 2 minute 27 second timer started.
    Translated: 2 minute 27 seconde minute a commencé.
    Original: Times up on your 2 minute 27 second timer.
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

    > 💁 భాషలలో ఒకే విషయం చెప్పే విధానం వేరువేరుగా ఉండటం వల్ల, మీరు LUISకు ఇచ్చిన ఉదాహరణలతో కొంత భిన్నంగా ఉన్న అనువాదాలను పొందవచ్చు. ఈ పరిస్థితిలో, LUISకి మరిన్ని ఉదాహరణలు జోడించి, మళ్లీ శిక్షణ ఇచ్చి మోడల్ ను పబ్లిష్ చేయండి.

> 💁 ఈ కోడ్‌ను మీరు [code/pi](../../../../../6-consumer/lessons/4-multiple-language-support/code/pi) ఫోల్డర్‌లో కనుగొనవచ్చు.

😀 మీ బహుభాషా టైమర్ ప్రోగ్రామ్ విజయవంతమైంది!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**అస్పష్టతతో కూడుకున్న ప్రకటన**:
ఈ పత్రాన్ని AI అనuvadana సేవ [Co-op Translator](https://github.com/Azure/co-op-translator) ఉపయోగించి అనువదించబడింది. మేము ఖచ్చితత్వానికి యత్నించినప్పటికీ, ఆటోమేటెడ్ అనువాదాల్లో తప్పులు లేదా అపరిశుద్ధతలు ఉండవచ్చును. అసలు పత్రం దాని స్వదేశ భాషలో అధికారిక మూలంగా పరిగణించాలి. కీలకమైన సమాచారానికి, ప్రొఫెషనల్ మానవ అనువాదాన్ని సూచిస్తాము. ఈ అనువాదం వాడకం వలన ఏదైనా అపార్థాలు లేదా తప్పుబాట్ల కోసం మేము బాధ్యత వహించము.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->