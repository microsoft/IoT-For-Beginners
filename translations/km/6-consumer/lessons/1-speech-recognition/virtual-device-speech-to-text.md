# ថ្លែកស្បែកទៅជាអត្ថបទ - ឧបករណ៍ IoT ពិតប្រាកដ

នៅផ្នែកនេះនៃមេរៀន អ្នកនឹងសរសេរកូដដើម្បីបម្លែងស្បែកដែលបានចាប់ពីមីក្រូហ្វូនរបស់អ្នកទៅជាអត្ថបទដោយប្រើសេវាស្បែក។

## បម្លែងស្បែកទៅជាអត្ថបទ

នៅលើ Windows, Linux, និង macOS អ្នកអាចប្រើប្រាស់ Python SDK សម្រាប់សេវាស្បែក ដើម្បីស្ដាប់ពីមីក្រូហ្វូនរបស់អ្នក ហើយបម្លែងស្បែកណាមួយដែលកើតមានទៅជាអត្ថបទ។ វានឹងស្ដាប់ជាបន្តបន្ទាប់ កំណត់កម្រិតសម្លេង ហើយផ្ញើស្បែកសម្រាប់បម្លែងទៅជាអត្ថបទពេលកម្រិតសម្លេងថយចុះ ដូចជាក្នុងចុងប្លុកស្បែកមួយ។

### ភារកិច្ច - បម្លែងស្បែកទៅជាអត្ថបទ

1. បង្កើតកម្មវិធី Python ថ្មីលើកុំព្យូទ័ររបស់អ្នកក្នុងថតឯកសារមួយឈ្មោះ `smart-timer` ជាមួយឯកសារតែមួយឈ្មោះ `app.py` និងបរិយាកាស Python ក្លឹបស៊ើវ។

1. ដំឡើងកញ្ចប់ Pip សម្រាប់សេវាស្បែក។ សូមប្រាកដថាអ្នកកំពុងដំឡើងពីកុងសូលដែលបានបើកបរិយាកាស Python វីរុលហើយ។

    ```sh
    pip install azure-cognitiveservices-speech
    ```

    > ⚠️ ប្រសិនបើអ្នកបានប្រទះកំហុសដូចខាងក្រោម៖
    >
    > ```output
    > ERROR: Could not find a version that satisfies the requirement azure-cognitiveservices-speech (from versions: none)
    > ERROR: No matching distribution found for azure-cognitiveservices-speech
    > ```
    >
    > អ្នកត្រូវតែធ្វើការអាប់ដេត Pip។ សូមអនុវត្តបញ្ជារខាងក្រោម ហើយសាកល្បងដំឡើងកញ្ចប់ម្ដងទៀត
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. បន្ថែមការ​អ៊ីមពួតខាងក្រោមទៅឯកសារ `app.py`៖

    ```python
    import requests
    import time
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer
    ```

    នេះនាំចូលថ្នាក់ខ្លះដែលប្រើសម្រាប់ការទទួលស្គាល់ស្បែក។

1. បន្ថែមកូដខាងក្រោមដើម្បីប្រកាសការកំណត់ម្ដងទៀត៖

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'

    recognizer_config = SpeechConfig(subscription=speech_api_key,
                                     region=location,
                                     speech_recognition_language=language)
    ```

    ផ្លាស់ទី `<key>` ជាមួយកូដ API សម្រាប់សេវាស្បែករបស់អ្នក។ ផ្លាស់ទី `<location>` ជាមួយទីតាំងដែលអ្នកបានប្រើពេលបង្កើតធនធានសេវាស្បែក។

    ផ្លាស់ទី `<language>` ជាមួយស្ទីលភាសាសម្រាប់ភាសាដែលអ្នកនឹងនិយាយ អោយម៉ាកឧទាហរណ៍ `en-GB` សម្រាប់ភាសាអង់គ្លេស ឬ `zn-HK` សម្រាប់ភាសាកានតូនីស។ អ្នកអាចរកមើលបញ្ជីភាសាដែលគាំទ្រ និងឈ្មោះស្ទីលភាសា នៅក្នុង [ឯកសារគាំទ្រភាសា និងសំឡេងលើ Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) ។

    ការកំណត់នេះត្រូវបានប្រើដើម្បីបង្កើតអុបជេក `SpeechConfig` ដែលត្រូវបានប្រើសម្រាប់កំណត់សេវាស្បែក។

1. បន្ថែមកូដខាងក្រោមដើម្បីបង្កើតម្ចាស់ស្គាល់ស្បែក៖

    ```python
    recognizer = SpeechRecognizer(speech_config=recognizer_config)
    ```

1. ម្ចាស់ស្គាល់ស្បែកហើយដំណើរការលើប្រមុខសណ្ឋានខាងក្រោយ ស្ដាប់សំឡេង ហើយបម្លែងស្បែកណាមួយនៅក្នុងវាទៅជាអត្ថបទ។ អ្នកអាចយកអត្ថបទដោយប្រើមុខងារត្រឡប់មកវិញ - មុខងារដែលអ្នកកំណត់ ហើយផ្ទេរតទៅម្ចាស់ស្គាល់។ រៀងរាល់ពេលដែលមានស្បែកត្រូវបានរកឃើញ ត្រឡប់មកវិញនឹងត្រូវបានហៅ។ បន្ថែមកូដខាងក្រោមដើម្បីកំណត់មុខងារត្រឡប់មកវិញ និងផ្ទេរតទៅម្ចាស់ស្គាល់។ ព្រមទាំងកំណត់មុខងារដើម្បីដំណើរការអត្ថបទ ហើយបោះពុម្ពក្នុងកុងសូល៖

    ```python
    def process_text(text):
        print(text)

    def recognized(args):
        process_text(args.result.text)
    
    recognizer.recognized.connect(recognized)
    ```

1. ម្ចាស់ស្គាល់ធ្វើការស្តាប់គឺត្រឹមពេលដែលអ្នកចាប់ផ្តើមវាផ្ទាល់។ បន្ថែមកូដខាងក្រោមដើម្បីចាប់ផ្តើមការដំណើរការ។ វាដំណើរការជាក្រោមខាងក្រោយ ដូច្នេះកម្មវិធីរបស់អ្នកត្រូវការលូបអននិច្ចដែលដេក ដើម្បីរក្សាកម្មវិធីក្នុងសកម្មភាព។

    ```python
    recognizer.start_continuous_recognition()

    while True:
        time.sleep(1)
    ```

1. បង្កើតកម្មវិធីនេះ។ និយាយចូលក្នុងមីក្រូហ្វូនរបស់អ្នក ហើយសំឡេងដែលបានបម្លែងទៅជាអត្ថបទនឹងត្រូវបង្ហាញក្នុងកុងសូល។

    ```output
    (.venv) ➜  smart-timer python3 app.py
    Hello world.
    Welcome to IoT for beginners.
    ```

    សាកល្បងប្រភេទប្រយោគផ្សេងៗ រួមមានប្រយោគដែលពាក្យសំឡេងដូចគ្នានៅតែមិនមានន័យដូចគ្នា។ ឧទាហរណ៍ ប្រសិនបើអ្នកនិយាយភាសាអង់គ្លេស សូមនិយាយ 'I want to buy two bananas and an apple too' ហើយមើលថាវានឹងប្រើ to, two និង too ត្រឹមត្រូវដូចមូលដ្ឋាននៃបរិបទពាក្យ មិនមែនតែសំឡេងរបស់វាទេ។

> 💁 អ្នកអាចរកកូដនេះបាននៅក្នុងថត [code-speech-to-text/virtual-iot-device](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/virtual-iot-device) ។

😀 កម្មវិធីស្បែកទៅជាអត្ថបទរបស់អ្នកបានជោគជ័យ!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**ការបដិសេធ**ៈ  
ឯកសារនេះបានបកប្រែដោយប្រើសេវាកម្មបកប្រែ AI [Co-op Translator](https://github.com/Azure/co-op-translator)។ ខណៈពេលយើងខិតខំដល់ភាពត្រឹមត្រូវ សូមយល់ឲ្យដឹងថាការបកប្រែដោយស្វ័យប្រវត្តិអាចមានកំហុស ឬភាពមិនត្រឹមត្រូវខ្លះ។ ឯកសារដើមក្នុងភាសាដើមគួរត្រូវបានពិចារណាថាជា ឯកសារដែលមានសិទ្ធិពិត។ សម្រាប់ព័ត៌មានសំខាន់ ការបកប្រែដោយមនុស្សជំនាញត្រូវបានណែនាំ។ យើងមិនទទួលខុសត្រូវចំពោះការយល់ច្រឡំ ឬការបកអក្សរខុសពីការប្រើប្រាស់ការបកប្រែនេះឡើយ។
<!-- CO-OP TRANSLATOR DISCLAIMER END -->