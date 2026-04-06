# កំណត់ម៉ោង - ឧបករណ៍ IoT វិជ្ជមាន និង Raspberry Pi

នៅក្នុងផ្នែកនេះនៃមេរៀន អ្នកនឹងហៅកូដ serverless របស់អ្នកដើម្បីយល់ពីសំលេងនិងកំណត់ម៉ោងនៅលើឧបករណ៍ IoT វិជ្ជមានរបស់អ្នក ឬ Raspberry Pi dựa trên kết quả.

## កំណត់ម៉ោង

អត្ថបទដែលត្រូវបានវិលត្រឡប់ពីការហៅសំលេងទៅអត្ថបទត្រូវតែត្រូវបានផ្ញើទៅកូដ serverless របស់អ្នកដើម្បីដំណើរការដោយ LUIS, រកបានចំនួនវិនាទីសម្រាប់ម៉ោង។ ចំនួនវិនាទីនេះអាចត្រូវបានប្រើដើម្បីកំណត់ម៉ោង។

ម៉ោងអាចត្រូវបានកំណត់ដោយប្រើថ្នាក់ Python `threading.Timer`។ ថ្នាក់នេះទទួលបានពេលពន្យាពេល និងមុខងារ ហើយបន្ទាប់ពីពេលពន្យាពេលមុខងារនេះត្រូវបានអនុវត្ត។

### ភារកិច្ច - ផ្ញើអត្ថបទទៅមុខងារ serverless

1. បើកគម្រោង `smart-timer` នៅក្នុង VS Code ហើយធានាថាបរិបទវីរុច đã được tải trong terminal ប្រសិនបើអ្នកកំពុងប្រើឧបករណ៍ IoT វិជ្ជមាន។

1. មុន `process_text` មុខងារ បង្កើតមុខងារដែលមានឈ្មោះ `get_timer_time` ដើម្បីហៅ REST endpoint ដែលអ្នកបានបង្កើត៖

    ```python
    def get_timer_time(text):
    ```
  
1. បន្ថែមកូដដូចខាងក្រោមទៅមុខងារនេះដើម្បីកំណត់ URL ដែលត្រូវហៅ៖

    ```python
    url = '<URL>'
    ```
  
    ប្ដូរ `<URL>` ជាមួយ URL នៃ REST endpoint របស់អ្នកដែលបានបង្កើតក្នុងមេរៀនមុននេះ ទៅលើកុំព្យូទ័រ​របស់អ្នក ឬនៅពពក។

1. បន្ថែមកូដដូចខាងក្រោមដើម្បីកំណត់អត្ថបទជាគុណលក្ខណៈមួយផ្ញើជាទ្រង់ទ្រាយ JSON ទៅការហៅ៖

    ```python
    body = {
        'text': text
    }
    
    response = requests.post(url, json=body)
    ```
  
1. ខាងក្រោមនេះ ទាញយក `seconds` ពី payload នៃការឆ្លើយតប ហើយត្រឡប់តម្លៃ 0 ប្រសិនបើការហៅបរាជ័យ៖

    ```python
    if response.status_code != 200:
        return 0
    
    payload = response.json()
    return payload['seconds']
    ```
  
    ការហៅ HTTP ជោគជ័យចេញកូដស្ថានភាពនៅលំដាប់ 200 ហើយកូដ serverless របស់អ្នកត្រឡប់ 200 ប្រសិនបើអត្ថបទត្រូវបានដំណើរការនិងទទួលស្គាល់ថាជាចេតនាកំណត់ម៉ោង។

### ភារកិច្ច - កំណត់ម៉ោងលើ thread ផ្ទៃខាងក្រោយ

1. បន្ថែមប្រកាសនាំចូលខាងក្រោមនៅលើបណ្ដាញឯកសារ ដើម្បីនាំចូលបណ្ណាល័យ threading នៃ Python:

    ```python
    import threading
    ```
  
1. មុន `process_text` មុខងារ បន្ថែមមុខងារមួយដើម្បីនិយាយចម្លើយ។ ពេលនេះវានឹងសរសេរទៅកុងសុល ប៉ុន្តេលើទីបន្ទាប់នៃមេរៀននេះ វានឹងនិយាយអត្ថបទ។

    ```python
    def say(text):
        print(text)
    ```
  
1. ខាងក្រោមនេះ បន្ថែមមុខងារដែលនឹងត្រូវបានហៅដោយម៉ោង ដើម្បីប្រកាសថាម៉ោងបានបញ្ចប់៖

    ```python
    def announce_timer(minutes, seconds):
        announcement = 'Times up on your '
        if minutes > 0:
            announcement += f'{minutes} minute '
        if seconds > 0:
            announcement += f'{seconds} second '
        announcement += 'timer.'
        say(announcement)
    ```
  
    មុខងារនេះទទួលចំនួននាទី និងវិនាទីសម្រាប់ម៉ោង ហើយបង្កើតប្រយោគមួយ ដើម្បីនិយាយថាម៉ោងបានបញ្ចប់។ វានឹងពិនិត្យចំនួននាទី និងវិនាទី ហើយរួមបញ្ចូលតែក្រុមម៉ោងដែលមានតម្លៃតែប៉ុណ្ណោះ។ ឧទាហរណ៍ ប្រសិនបើចំនួននាទីគឺ 0 នោះនឹងរួមបញ្ចូលតែវិនាទីនៅក្នុងសារ។ ប្រយោគនេះត្រូវបានផ្ញើទៅមុខងារ `say`។

1. ខាងក្រោមនេះ បន្ថែមមុខងារ `create_timer` ដូចខាងក្រោមដើម្បីបង្កើតម៉ោង៖

    ```python
    def create_timer(total_seconds):
        minutes, seconds = divmod(total_seconds, 60)
        threading.Timer(total_seconds, announce_timer, args=[minutes, seconds]).start()
    ```
  
    មុខងារនេះទទួលចំនួនសរុបវិនាទីសម្រាប់ម៉ោងដែលនឹងត្រូវផ្ញើនៅក្នុងការបញ្ជា ហើយបំលែងវាទៅជានាទី និងវិនាទី។ បន្ទាប់មកវាបង្កើតនិងចាប់ផ្តើមអូបជេកម៉ោងមួយដោយប្រើចំនួនសរុបវិនាទី ផ្ញើទៅមុខងារ `announce_timer` និងបញ្ជីដែលមាននាទី និងវិនាទី។ នៅពេលម៉ោងផុតកំណត់ វានឹងហៅមុខងារ `announce_timer` ហើយផ្ញើមាតិកានៃបញ្ជីនេះជាពារ៉ាម៉ែត្រ - ដូច្នេះធាតុដំបូងក្នុងបញ្ជីត្រូវបានផ្ញើជាពារ៉ាម៉ែត្រនាទី និងធាតុទីពីរជាវិនាទី។

1. ចុងក្រោយមុខងារ `create_timer` បន្ថែមកូដមួយដើម្បីបង្កើតសារដែលនឹងនិយាយទៅអ្នកប្រើ ដើម្បីប្រកាសថាម៉ោងកំពុងចាប់ផ្តើម៖

    ```python
    announcement = ''
    if minutes > 0:
        announcement += f'{minutes} minute '
    if seconds > 0:
        announcement += f'{seconds} second '    
    announcement += 'timer started.'
    say(announcement)
    ```
  
    ម្តងទៀត វារួមបញ្ចូលតែក្រុមម៉ោងដែលមានតម្លៃ។ ប្រយោគនេះត្រូវបានផ្ញើទៅមុខងារ `say`។

1. បន្ថែមខាងចុងនៃមុខងារ `process_text` ដើម្បីទទួលពេលវេលាសម្រាប់ម៉ោងពីអត្ថបទ ហើយបង្កើតម៉ោង៖

    ```python
    seconds = get_timer_time(text)
    if seconds > 0:
        create_timer(seconds)
    ```
  
    ម៉ោងត្រូវបានបង្កើតតែបើចំនួនវិនាទីលើស 0។

1. បើករត់កម្មវិធី ហើយធានាថា function app កំពុងរត់ដែរ។ កំណត់ម៉ោងមួយចំនួន ហើយលទ្ធផលនឹងបង្ហាញការកំណត់ម៉ោង ហើយបង្ហាញពេលវាលេច:

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Set a two minute 27 second timer.
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```
  
> 💁 អ្នកអាចរកឃើញកូដនេះនៅក្នុងថត [code-timer/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/pi) ឬ [code-timer/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/virtual-iot-device)។

😀 កម្មវិធីម៉ោងរបស់អ្នកបានជោគជ័យ!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**ការបដិសេធ**៖  
ឯកសារនេះត្រូវបានបកប្រែដោយប្រើសេវាកម្មបកប្រែ AI [Co-op Translator](https://github.com/Azure/co-op-translator)។ ខណៈពេលដែលយើងខិតខំរក្សាការត្រឹមត្រូវ សូមយល់ថាការបកប្រែដោយស្វ័យប្រវត្តិនេះអាចមានកំហុស ឬខុសត្រូវបានចលាចល។ ឯកសារដើមក្នុងភាសាដើមគួរត្រូវបានគេពិចារណាថាជាទិន្នន័យផ្លូវការផ្ទាល់។ សម្រាប់ព័ត៌មានសំខាន់ៗ ការបកប្រែដោយអ្នកជំនាញមនុស្សត្រូវបានផ្តល់អនុសាសន៍។ យើងមិនទទួលខុសត្រូវចំពោះការយល់ប្លែក ឬការបកប្រែខុសរាល់ប្រភេទឡើយដែលកើតមានពីការប្រើប្រាស់ការបកប្រែនេះ។
<!-- CO-OP TRANSLATOR DISCLAIMER END -->