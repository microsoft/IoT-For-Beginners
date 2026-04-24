# បកប្រែសំឡេង - ឧបករណ៍ IoT វើឌួល

នៅផ្នែកនេះនៃមេរៀន អ្នកនឹងសរសេរកូដ ដើម្បីបកប្រែសំឡេងពេលបម្លែងទៅជាអក្សរដោយប្រើសេវាសំឡេង បន្ទាប់មកបកប្រែអក្សរដោយប្រើសេវាដែលមានឈ្មោះថា Translator មុននឹងបង្កើតចម្លើយដែលផ្តល់ជាសំឡេង។

## ប្រើសេវាសំឡេងដើម្បីបកប្រែសំឡេង

សេវាសំឡេងអាចទទួលបានសំឡេង ហើយមិនត្រឹមតែបម្លែងទៅជាអក្សរដែរនៅក្នុងភាសាដូចគ្នាប៉ុណ្ណោះ ទេក៏អាចបកប្រែផលបញ្ចេញទៅជาทាសាផ្សេងទៀតបានផងដែរ។

### ភារកិច្ច - ប្រើសេវាសំឡេងដើម្បីបកប្រែសំឡេង

1. បើកគម្រោង `smart-timer` នៅក្នុង VS Code ហើយប្រាកដថាបរិវេណវើឌួលត្រូវបានផ្ទុកក្នុងរបារថែមីនាល់។

1. បន្ថែមបញ្ជាចូល (import) ខាងក្រោមដែលមានរួចហើយ៖

    ```python
    from azure.cognitiveservices import speech
    from azure.cognitiveservices.speech.translation import SpeechTranslationConfig, TranslationRecognizer
    import requests
    ```

    នេះនាំចូលថ្នាក់ដែលប្រើសម្រាប់បកប្រែសំឡេង និងបណ្ណាល័យ `requests` ដែលនឹងប្រើសម្រាប់ហៅទៅសេវាកម្ម Translator នៅពេលបន្តនៅក្នុងមេរៀននេះ។

1. ម៉ាស៊ីនម៉ោងឆ្លាតនឹងមានភាសា 2 កំណត់ - ភាសារបស់ម៉ាស៊ីនមេដែលបានប្រើសម្រាប់បណ្តុះបណ្តាល LUIS (ភាសាដូចគ្នានេះត្រូវបានប្រើដើម្បីកសាងសារ​សម្រាប់និយាយទៅអ្នកប្រើ) ហើយភាសាដែលអ្នកប្រើនិយាយ។ បញ្ចូលអថេរ `language` ដើម្បីកំណត់ភាសាដែលនឹងត្រូវនិយាយដោយអ្នកប្រើ ហើយបន្ថែមអថេរថ្មីមួយឈ្មោះ `server_language` សម្រាប់ភាសាដែលប្រើបណ្តុះបណ្តាល LUIS៖

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    ជំនួស `<user language>` ជាមួយឈ្មោះភាសារបស់ភាសាដែលអ្នកនឹងនិយាយ នៅឧទាហរណ៍ `fr-FR` សម្រាប់ភាសាបារាំង ឬ `zn-HK` សម្រាប់ភាសាកាន់តូនីស៍។

    ជំនួស `<server language>` ជាមួយឈ្មោះភាសារបស់ភាសាដែលបានប្រើបណ្តុះបណ្តាល LUIS។

    អ្នកអាចស្វែងរកបញ្ជីនៃភាសាដែលគាំទ្រ និងឈ្មោះភាសានៅក្នុងឯកសារគាំទ្រភាសា និងសំឡេងលើMicrosoft docs [Language and voice support documentation on Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text)។

    > 💁 ប្រសិនបើអ្នកមិននិយាយភាសាច្រើន អ្នកអាចប្រើសេវាដូចជា [Bing Translate](https://www.bing.com/translator) ឬ [Google Translate](https://translate.google.com) ដើម្បីបកប្រែពីភាសាដែលអ្នកចូលចិត្តទៅភាសាដែលអ្នកចង់បាន។ សេវាកម្មទាំងនេះអាចបញ្ចេញសំឡេងនៃអត្ថបទដែលបានបកប្រែ។ សូមយល់ថា ពេលប្រើស្គាល់សំឡេង អ្នកស្គាល់សំឡេងអាចមិនចាប់យកសំឡេងបញ្ចេញពីឧបករណ៍របស់អ្នកបានទាំងស្រុង។ ដូច្នេះ អ្នកអាចត្រូវការប្រើឧបករណ៍បន្ថែមក្រៅពីសំឡេងបញ្ចេញ។

    > ឧទាហរណ៍ ប្រសិនបើអ្នកបណ្តុះបណ្តាល LUIS ជាភាសាអង់គ្លេស ប៉ុន្តាចង់ប្រើភាសាបារាំងជាភាសារបស់អ្នកប្រើ អ្នកអាចបកប្រែអត្ថបទដូចជា "set a 2 minute and 27 second timer" ពីភាសាអង់គ្លេសទៅភាសាបារាំង តាមរយៈ Bing Translate ហើយប្រើប៊ូតុង **Listen translation** ដើម្បីនិយាយសំឡេងចូលទៅក្នុងម៉ាញ៉េក្រូហ្វូនរបស់អ្នក។

    > ![ប៊ូតុងស្ដាប់ការបកប្រែលើ Bing translate](../../../../../translated_images/km/bing-translate.348aa796d6efe2a9.webp)

1. ជំនួសសេចក្ដីប្រកាស `recognizer_config` និង `recognizer` ជាមួយខាងក្រោម៖

    ```python
    translation_config = SpeechTranslationConfig(subscription=speech_api_key,
                                                 region=location,
                                                 speech_recognition_language=language,
                                                 target_languages=(language, server_language))
    
    recognizer = TranslationRecognizer(translation_config=translation_config)
    ```

    នេះបង្កើតបរិបទបកប្រែដើម្បីស្គាល់សំឡេងនៅក្នុងភាសាអ្នកប្រើ និងបង្កើតការបកប្រែជាភាសាអ្នកប្រើ និងភាសាម៉ាស៊ីនមេ។ បន្ទាប់មកប្រើបរិបទនេះ ដើម្បីបង្កើតម្ចាស់ស្គាល់សំឡេងបកប្រែ - ម្ចាស់ស្គាល់សំឡេងដែលអាចបកប្រែផលបញ្ចេញពីការស្គាល់សំឡេងទៅភាសាច្រើន។

    > 💁 ភាសាដើមត្រូវបានកំណត់ក្នុង `target_languages` ដូច្នេះអ្នកមិនបានទទួលការបកប្រែអ្វីទេ។

1. ប្រែប្រួលមុខងារ `recognized` ដោយជំនួសមាតិកាទាំងមូលនៃមុខងារជាមួយខាងក្រោម៖

    ```python
    if args.result.reason == speech.ResultReason.TranslatedSpeech:
        language_match = next(l for l in args.result.translations if server_language.lower().startswith(l.lower()))
        text = args.result.translations[language_match]
        if (len(text) > 0):
            print(f'Translated text: {text}')
    
            message = Message(json.dumps({ 'speech': text }))
            device_client.send_message(message)
    ```

    កូដនេះពិនិត្យមើលថា ព្រឹត្តិការណ៍ recognized ត្រូវបានបញ្ចេញ ពីព្រោះសំឡេងត្រូវបានបកប្រែ (ព្រឹត្តិការណ៍នេះអាចបញ្ចេញនៅពេលផ្សេងៗ ដូចជា ពេលសម្ដីត្រូវបានស្គាល់ ប៉ុន្តែមិនត្រូវបានបកប្រែ)។ ប្រសិនបើសំឡេងត្រូវបានបកប្រែ វានឹងស្វែងរកការបកប្រែក្នុង `args.result.translations` ដែលសម្រូវនឹងភាសាម៉ាស៊ីនមេ។

    ភាសាក្នុង `args.result.translations` ត្រូវបានកំណត់តាមផ្នែកភាសានៃការកំណត់ប្រភេទ ភាគរយមិនគិតតាមសរុបនៃការកំណត់ប្រភេទទេ។ ឧទាហរណ៍ ប្រសិនបើអ្នកស្នើសុំការបកប្រែទៅ `fr-FR` សម្រាប់ភាសាបារាំង វានឹងមានធាតុសម្រាប់ `fr` មិនមែន `fr-FR` ទេ។

    អត្ថបទដែលបានបកប្រែក្រោយមកត្រូវបានផ្ញើទៅ IoT Hub។

1. ចាប់ផ្តើមកូដនេះ ដើម្បីសាកល្បងការបកប្រែ។ ប្រាកដថា function app របស់អ្នកកំពុងដំណើរការ ហើយស្នើសុំម៉ោងតាមភាសាអ្នកប្រើ ដោយនិយាយភាសានោះផ្ទាល់ ឬប្រើកម្មវិធីបកប្រែ។

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    ```

## បកប្រែអត្ថបទដោយប្រើសេវាកម្ម Translator

សេវាសំឡេងមិនគាំទ្រការបកប្រែអត្ថបទវិលត្រឡប់ទៅជាសំឡេងវិញទេ ជំនួសវាអ្នកអាចប្រើសេវា Translator ដើម្បីបកប្រែអត្ថបទ។ សេវានេះមាន REST API ដែលអ្នកអាចប្រើសម្រាប់បកប្រែអត្ថបទ។

### ភារកិច្ច - ប្រើធនធាន translator ដើម្បីបកប្រែអត្ថបទ

1. បន្ថែម key API translator នៅខាងក្រោម `speech_api_key`:

    ```python
    translator_api_key = '<key>'
    ```

    ជំនួស `<key>` ជាមួយ key API សម្រាប់ធនធានសេវាអូសិច Translator របស់អ្នក។

1. ខាងលើមុខងារ `say` សរសេរមុខងារ `translate_text` ដែលនឹងបកប្រែអត្ថបទពីភាសាម៉ាស៊ីនមេទៅភាសាអ្នកប្រើ៖

    ```python
    def translate_text(text):
    ```

1. នៅក្នុងមុខងារនេះ កំណត់ URL និង headers សម្រាប់ហៅ REST API៖

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    URL សម្រាប់ API នេះមិនខ្ចីជតិសម្រាប់ទីកន្លែងណាមួយទេ ទេ ត្រូវបញ្ជាក់ទីកន្លែងជាក្បាលសំណើ។ API key ត្រូវបានប្រើដោយផ្ទាល់ ដូច្នេះ មិនចាំបាច់ទទួលបាន access token ពី token issuer API ដូចសេវាសំឡេង ។

1. ខាងក្រោមនេះកំណត់ parameters និង body សម្រាប់ពាក់ព័ន្ធ៖

    ```python
    params = {
        'from': server_language,
        'to': language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` កំណត់ប៉ារ៉ាម៉ែត្រ សម្រាប់ផ្ញើទៅ API ហៅពីភាសា និងទៅភាសា ។ ការហៅនេះនឹងបកប្រែអត្ថបទពីភាសា `from` ទៅភាសា `to`។

    `body` មានអត្ថបទដែលត្រូវបកប្រែ។ វាជាអារេ ខណៈកំណត់អត្ថបទច្រើនអាចបកប្រែបានក្នុងការហៅមួយនេះ។

1. ហៅ REST API ហើយទទួលបានចម្លើយ៖

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    ចម្លើយដែលត្រូវបានត្រឡប់មកវិញ គឺជា JSON array ដែលមានធាតុមួយដែលមានការបកប្រែ។ ធាតុនេះមានអារេសម្រាប់ការបកប្រែសម្រាប់ធាតុទាំងអស់ដែលបានផ្ញើក្នុង body។

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

1. ត្រឡប់មកលទ្ធផល `test` ពីការបកប្រែដំបូងក្នុងធាតុដំបូងនៃអារេ៖

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. បន្ទាប់មុខងារ `say` ដើម្បីបកប្រែអត្ថបទនឹងនិយាយ មុនពេលផលិត SSML៖

    ```python
    print('Original:', text)
    text = translate_text(text)
    print('Translated:', text)
    ```

    កូដនេះ ក៏បោះពុម្ពនូវអត្ថបទដើម និងអត្ថបទបកប្រែទៅកាន់ console ផងដែរ។

1. ដំណើរការកូដរបស់អ្នក។ ប្រាកដថា function app របស់អ្នកកំពុងដំណើរការ ហើយស្នើសុំម៉ោងនៅភាសាអ្នកប្រើ ដោយនិយាយភាសានោះផ្ទាល់ ឬប្រើកម្មវិធីបកប្រែ។

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

    > 💁 ដូចជា វិធីនិយាយរបស់មនុស្សនៅភាសាផ្សេងៗគ្នាខុសគ្នា អ្នកប្រហែលជានឹងបានការបកប្រែខុសប្លែកពីឧទាហរណ៍ដែលអ្នកផ្តល់ឲ្យ LUIS។ ប្រសិនបើបែបនេះ សូមបន្ថែមឧទាហរណ៍មួយចំនួនទៀតទៅ LUIS បណ្តុះបណ្តាលឡើងវិញ ហើយចេញផ្សាយម៉ូឌែលម្តងទៀត។

> 💁 អ្នកអាចស្វែងរកកូដនេះនៅក្នុងថត [code/virtual-iot-device](../../../../../6-consumer/lessons/4-multiple-language-support/code/virtual-iot-device)។

😀 កម្មវិធីម៉ោងច្រើនភាសារបស់អ្នកបានជោគជ័យ!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**ការបដិសេធ**:  
ឯកសារនេះត្រូវបានបកប្រែដោយប្រើសេវាបកប្រែ AI [Co-op Translator](https://github.com/Azure/co-op-translator)។ ខណៈពេលយើងខំប្រឹងសម្រាប់ការពិតប្រាកដ សូមយល់ដឹងថាការបកប្រែដោយស្វ័យប្រវត្តិអាចមានកំហុស ឬចំណុចដែលមិនត្រឹមត្រូវ។ ឯកសារដើមជាភាសាដើម គួរត្រូវបានរាប់បញ្ចូលជាផ្នែកដ៏សំខាន់ជាមូលដ្ឋាន។ សម្រាប់ព័ត៌មានសំខាន់ៗ សូមផ្ដល់អាទិភាពការបកប្រែដោយមនុស្សជំនាញវិជ្ជាជីវៈ។ យើងមិនទទួលខុសត្រូវចំពោះការយល់ច្រឡំ ឬការបកប្រែខុសពីការប្រើប្រាស់ការបកប្រែនេះឡើយ។
<!-- CO-OP TRANSLATOR DISCLAIMER END -->