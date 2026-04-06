# ពាក្យបំពង់ទៅអក្សរ - Raspberry Pi

ក្នុងផ្នែកនេះនៃមេរៀន អ្នកនឹងសរសេរកូដដើម្បីបម្លែងសូរ្យក្នុងសំឡេងដែលបានចាប់ក្នុងការប្រសង្កេតទៅជាអក្សរដោយប្រើសេវាសូរ្យ។

## ផ្ញើសំឡេងទៅសេវាសូរ្យ

សំឡេងអាចត្រូវបានផ្ញើទៅសេវាសូរ្យដោយប្រើ REST API។ ដើម្បីប្រើសេវាសូរ្យ អ្នកត្រូវតែស្នើសុំ access token ជាជំហ៊ានដំបូង បន្ទាប់មកប្រើ token នោះដើម្បីចូលប្រើ REST API។ Access tokens ទាំងនេះនឹងផុតកំណត់បន្ទាប់ពី ១០ នាទី ពីដូចនេះកូដរបស់អ្នកគួរតែស្នើសុំជាប្រចាំដើម្បីធានាថាពួកវានៅតែទាន់សម័យ។

### ភារកិច្ច - ទទួលបាន access token

1. បើកគម្រោង `smart-timer` នៅលើ Pi របស់អ្នក។

1. លុបមុខងារ `play_audio` ទៅ។ នេះមិនចាំបាច់ទៀតទេ ព្រោះអ្នកមិនចង់ឲ្យ smart timer ថ្លែងតាមឡើងវិញនូវអ្វីដែលអ្នកបាននិយាយឡើយ។

1. បន្ថែម import ខាងក្រោមនៅលើកំពូលឯកសារ `app.py`៖

    ```python
    import requests
    ```

1. បន្ថែមកូដខាងក្រោមមុខ `while True` ដើម្បីប្រកាសការកំណត់ខ្លះសម្រាប់សេវាសូរ្យ៖

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'
    ```

    ប្ដូរ `<key>` ជា key API សម្រាប់ធនធានសេវាសូរ្យរបស់អ្នក។ ប្ដូរ `<location>` ជាទីតាំងដែលអ្នកប្រើពេលបង្កើតធនធានសេវាសូរ្យ។

    ប្ដូរ `<language>` ជាមុខភាសាសម្រាប់ភាសាដែលអ្នកនឹងនិយាយ ដូចជា `en-GB` សម្រាប់ភាសាអង់គ្លេស ឬ `zn-HK` សម្រាប់ភាសាកាន់តូន។ អ្នកអាចរកបញ្ជីភាសា និងឈ្មោះមុខភាសាដែលគាំទ្របាននៅក្នុង [ឯកសារគាំទ្រភាសា និងសំឡេងនៅលើ Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text)។

1. ក្រោមនេះ បន្ថែមមុខងារ ខាងក្រោមសម្រាប់ទទួលបាន access token៖

    ```python
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_api_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    នេះហៅ endpoint ចេញ token ដោយផ្ញើ key API ជា header។ ការហៅនេះនឹងត្រឡប់ access token ដែលអាចប្រើបានក្នុងការហៅសេវាសូរ្យ។

1. ក្រោមនេះ ប្រកាសមុខងារមួយ ដើម្បីបម្លែងសូរ្យក្នុងសំឡេងដែលបានចាប់ទៅជាអក្សរដោយប្រើ REST API៖

    ```python
    def convert_speech_to_text(buffer):
    ```

1. នៅក្នុងមុខងារនេះ កំណត់ URL និង header សម្រាប់ REST API៖

    ```python
    url = f'https://{location}.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1'

    headers = {
        'Authorization': 'Bearer ' + get_access_token(),
        'Content-Type': f'audio/wav; codecs=audio/pcm; samplerate={rate}',
        'Accept': 'application/json;text/xml'
    }

    params = {
        'language': language
    }
    ```

    វាសង់ URL ដោយប្រើទីតាំងរបស់ធនធានសេវាសូរ្យ។ បន្ទាប់មកវាបំពេញ header ជាមួយ access token ពីមុខងារ `get_access_token` ហើយបញ្ចូលអត្រាគំរូសម្រាប់ចាប់សំឡេង។ ចុងក្រោយ កំណត់ប៉ារ៉ាម៉ែត្រខ្លះសម្រាប់ភាសាក្នុងសំឡេង។

1. ក្រោមនេះ បន្ថែមកូដដើម្បីហៅ REST API ហើយទទួលអក្សរត្រឡប់មក៖

    ```python
    response = requests.post(url, headers=headers, params=params, data=buffer)
    response_json = response.json()

    if response_json['RecognitionStatus'] == 'Success':
        return response_json['DisplayText']
    else:
        return ''
    ```

    នេះហៅ URL ហើយដកស្រង់តម្លៃ JSON ដែលត្រូវតបតាម។ តម្លៃ `RecognitionStatus` នៅក្នុងការតបឆ្លើយបង្ហាញថាការហៅអាចដកសូរ្យទៅជាអក្សរបានដោយជោគជ័យឬទេ ហើយបើតម្លៃគឺ `Success` អក្សរនឹងត្រូវបានត្រលប់ពីមុខងារ ប្រសិនបើមិនដូច្នោះ វានឹងត្រលប់ជាខ្សែអក្សរពីរ។

1. លើស្រទាប់ `while True:` ប្រកាសមុខងារមួយចុះសម្រាប់ដំណើរការអក្សរដែលត្រូវបានត្រលប់ពីសេវាសេរ្យទៅអក្សរ។ មុខងារនេះ នឹងបោះពុម្ពអក្សរនៅកុងសូលជាផ្លូវការ។

    ```python
    def process_text(text):
        print(text)
    ```

1. ចុងក្រោយ ប្ដូរការហៅ `play_audio` នៅក្នុង `while True` ជាមួយការហៅមុខងារ `convert_speech_to_text` ហើយផ្ញើអក្សរទៅមុខងារ `process_text`៖

    ```python
    text = convert_speech_to_text(buffer)
    process_text(text)
    ```

1. ប្រតិបត្តិការ​កូដ។ ចុចប៊ូតុង ហើយនិយាយចូលទៅក្នុងមីក្រូហ្វូន។ បញ្ចេញប៊ូតុងនៅពេលអ្នកបានបញ្ចប់ ហើយសំឡេងនឹងត្រូវបានបម្លែងទៅជាអក្សរនិងបោះពុម្ពនៅកុងសូល។

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Hello world.
    Welcome to IoT for beginners.
    ```

    សាកល្បងប្រភេទប្រយោគផ្សេងៗ ជាមួយប្រយោគដែលពាក្យមានសំឡេងដូចគ្នា ប៉ុន្តែមានអត្ថន័យខុសៗគ្នា។ ឧទាហរណ៍ ប្រសិនបើអ្នកនិយាយភាសាអង់គ្លេស សូមនិយាយថា 'I want to buy two bananas and an apple too' ហើយសង្កេតមើលថាវានឹងប្រើ to, two និង too បានត្រឹមត្រូវដោយផ្អែកលើ context នៃពាក្យ មិនមែនត្រឹមតែសំឡេងទេ។

> 💁 អ្នកអាចរកមើលកូដនេះនៅក្នុងថត [code-speech-to-text/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/pi)។

😀 ប្រសិនបើកម្មវិធី speech to text របស់អ្នកបានជោគជ័យ!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**ការបដិសេធ**៖  
ឯកសារនេះត្រូវបានបកប្រែដោយប្រើសេវាបកប្រែ AI [Co-op Translator](https://github.com/Azure/co-op-translator)។ ខណៈពេលដែលយើងខិតខំសម្រាប់ភាពត្រឹមត្រូវ សូមយល់ឲ្យដឹងថា ការបកប្រែដោយស្វ័យប្រវត្តិអាចមានកំហុស ឬភាពមិនត្រឹមត្រូវ។ ឯកសារដើមក្នុងភាសាបុរាណរបស់វាគួរត្រូវបានគេកត់សម្គាល់ជាផ្លូវការជាដំណើរមូលដ្ឋាន។ សម្រាប់ព័ត៌មានសំខាន់ៗ យើងណែនាំឲ្យប្រើការបកប្រែដោយមនុស្សជំនាញវិជ្ជាជីវៈ។ យើងមិនទទួលខុសត្រូវចំពោះការយល់ច្រឡំ ឬការបកប្រែខុសៗដែលកើតឡើងពីការប្រើប្រាស់ការបកប្រែនេះឡើយ។
<!-- CO-OP TRANSLATOR DISCLAIMER END -->