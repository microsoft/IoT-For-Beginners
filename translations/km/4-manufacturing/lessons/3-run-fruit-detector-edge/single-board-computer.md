# ចាត់ថ្នាក់រូបភាពដោយប្រើកម្មវិធីចាត់ថ្នាក់រូបភាព IoT Edge - សម្ភារៈ IoT មេគុណ និង Raspberry Pi

នៅផ្នែកនេះនៃមេរៀន អ្នកនឹងប្រើកម្មវិធីចាត់ថ្នាក់រូបភាពដែលរត់លើឧបករណ៍ IoT Edge។

## ប្រើកម្មវិធីចាត់ថ្នាក់ IoT Edge

ឧបករណ៍ IoT អាចត្រូវបានប្តូរទិសដៅទៅប្រើកម្មវិធីចាត់ថ្នាក់រូបភាព IoT Edge។ URL សម្រាប់កម្មវិធីចាត់ថ្នាក់រូបភាពគឺ `http://<IP address or name>/image` ដោយជំនួស `<IP address or name>` ជា អាសយដ្ឋាន IP ឬឈ្មោះម៉ាស៊ីនកំពុងបើក IoT Edge។

បណ្ណាល័យ Python សម្រាប់ Custom Vision ធ្វើការលើម៉ូដែលដែលបានផ្ទុកនៅលើពពក ប៉ុន្តិនៅមិនទាន់លើម៉ូដែលដែលបានផ្ទុកនៅលើ IoT Edge។ នេះមានន័យថាអ្នកត្រូវការប្រើ REST API ដើម្បីហៅកម្មវិធីចាត់ថ្នាក់នេះ។

### អង្គការ - ប្រើកម្មវិធីចាត់ថ្នាក់ IoT Edge

1. បើកគម្រោង `fruit-quality-detector` នៅក្នុង VS Code ប្រសិនបើមិនទាន់បើក។ ប្រសិនបើអ្នកកំពុងប្រើឧបករណ៍ IoT មេគុណ សូមប្រាកដថាបរិស្ថានមេគុណត្រូវបានបើកប្រើ។

1. បើកឯកសារ `app.py` ហើយលុបបញ្ចូលពី `azure.cognitiveservices.vision.customvision.prediction` និង `msrest.authentication`។

1. បន្ថែមការនាំចូលដូចខាងក្រោមនៅលើក្បាលឯកសារ៖

    ```python
    import requests
    ```

1. លុបកូដទាំងអស់បន្ទាប់ពីរូបភាពត្រូវបានរក្សាទុកទៅឯកសារ ចាប់ពី `image_file.write(image.read())` ជានូវចុងឯកសារ។

1. បន្ថែមកូដដូចខាងក្រោមនៅចុងឯកសារ៖

    ```python
    prediction_url = '<URL>'
    headers = {
        'Content-Type' : 'application/octet-stream'
    }
    image.seek(0)
    response = requests.post(prediction_url, headers=headers, data=image)
    results = response.json()
    
    for prediction in results['predictions']:
        print(f'{prediction["tagName"]}:\t{prediction["probability"] * 100:.2f}%')
    ```

    ជំនួស `<URL>` ជា URL សម្រាប់កម្មវិធីចាត់ថ្នាក់រូបភាពរបស់អ្នក។

    កូដនេះធ្វើការស្នើសុំ REST POST ទៅកម្មវិធីចាត់ថ្នាក់ បញ្ជូនរូបភាពជាផ្នែករាងកាយនៅក្នុងសំណើ។ លទ្ធផលត្រូវបានត្រឡប់មកជាឯកសារ JSON ហើយវាត្រូវបានបកប្រែដើម្បីបង្ហាញអត្រាបានសមាហរណភាព។

1. ប្រតិបត្តិកម្មធ្វើន័យរបស់អ្នក ដោយកាម៉េរ៉ាអ្នកច្របញ្ជាក់ទៅលើផ្លែឈើមួយចំនួន ឬកញ្ចប់រូបភាពសមរម្យ ឬផ្លែឈើដែលត្រូវបានមើលឃើញលើកាឡូម៉េកវែបបើអ្នកប្រើឧបករណ៍ IoT មេគុណ។ អ្នកនឹងឃើញលទ្ធផលនៅកុងសូល៖

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 អ្នកអាចស្វែងរកកូដនេះនៅថត [code-classify/pi](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/pi) ឬ [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/virtual-iot-device)។

😀 កម្មវិធីចាត់ថ្នាក់គុណភាពផ្លែឈើរបស់អ្នកបានជោគជ័យ!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**ការបដិសេធ**៖  
ឯកសារនេះត្រូវបានបកប្រែដោយប្រើសេវាកម្មបកប្រែ AI [Co-op Translator](https://github.com/Azure/co-op-translator)។ ខណៈពេលដែលយើងខិតខំប្រឹងប្រែងដើម្បីមានភាពត្រឹមត្រូវ សូមយោលព្រមថាការបកប្រែដោយស្វ័យប្រវត្តិអាចមានកំហុសឬភាពមិនត្រឹមត្រូវ។ ឯកសារដើមក្នុងភាសាមាតុភូមិគួរត្រូវបានគិតថាជា ប្រភពផ្លូវការជាចម្បង។ សម្រាប់ព័ត៌មានសំខាន់ៗ ត្រូវបានផ្តល់អនុសាសន៍ឲ្យប្រើការបកប្រែដោយមនុស្សដែលជាអ្នកវិជ្ជាជីវៈ។ យើងមិនទទួលខុសត្រូវចំពោះកការយល់ច្រឡំ ឬការបកស្រាយខុសពីការប្រើប្រាស់ការបកប្រែនេះឡើយ។
<!-- CO-OP TRANSLATOR DISCLAIMER END -->