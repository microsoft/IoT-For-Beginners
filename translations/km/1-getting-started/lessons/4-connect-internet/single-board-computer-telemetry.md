# គ្រប់គ្រងពន្លឺរាត្រីរបស់អ្នកតាមអ៊ីនធឺណិត - ថេរ IoT ធម្មតា និង Raspberry Pi

នៅផ្នែកនេះនៃមេរៀន អ្នកនឹងផ្ញើទិន្នន័យទូទៅជាមួយកម្រិតពន្លឺពី Raspberry Pi របស់អ្នក ឬឧបករណ៍ IoT ធម្មតាទៅឲ្យ MQTT broker។

## បោះពុម្ពផ្សាយទិន្នន័យទូទាំង

ជំហានបន្ទាប់គឺបង្កើតឯកសារ JSON មានទិន្នន័យទូទាំងហើយផ្ញើវាទៅ MQTT broker។

### ការងារ

បោះពុម្ពផ្សាយទិន្នន័យទៅ MQTT broker។

1. បើកគម្រោង nightlight នៅក្នុង VS Code។

1. ប្រសិនបើអ្នកកំពុងប្រើឧបករណ៍ IoT ធម្មតា សូមប្រាកដថា terminal កំពុងដំណើរការបរិស្ថានធម្មតា។ ប្រសិនបើអ្នកប្រើ Raspberry Pi អ្នកមិនត្រូវប្រើបរិស្ថានធម្មតាបានទេ។

1. បន្ថែមការនាំចូលដូចខាងក្រោមនៅខាងលើឯកសារ `app.py`៖

    ```python
    import json
    ```

    បណ្ណាល័យ `json` ត្រូវបានប្រើសម្រាប់ចាក់បញ្ចូលទិន្នន័យទូទាំងជាឯកសារ JSON។

1. បន្ថែមខាងក្រោយពាក្យប្រកាស `client_name` ដូចខាងក្រោម៖

    ```python
    client_telemetry_topic = id + '/telemetry'
    ```

    `client_telemetry_topic` គឺជាប្រធាន MQTT ដែលឧបករណ៍នឹងបោះពុម្ពផ្សាយកម្រិតពន្លឺទៅ។

1. ជំនួសមាតិកានៃរង្វង់ `while True:` នៅចុងឯកសារដោយអ្វីដែលមានដូចខាងក្រោម៖

    ```python
    while True:
        light = light_sensor.light
        telemetry = json.dumps({'light' : light})

        print("Sending telemetry ", telemetry)
    
        mqtt_client.publish(client_telemetry_topic, telemetry)
    
        time.sleep(5)
    ```

    កូដនេះបន្ទុកកម្រិតពន្លឺជាឯកសារ JSON ហើយបោះពុម្ពផ្សាយវាទៅ MQTT broker។ បន្ទាប់មកវានឺងដើម្បីកាត់បន្ថយប្រេកង់នៃសារ។

1. ដំណើរការកូដ ដូចដែលអ្នកបានដំណើរការកូដពីផ្នែកមុននៃការងារ។ ប្រសិនបើអ្នកកំពុងប្រើឧបករណ៍ IoT ធម្មតា សូមប្រាកដថាកម្មវិធី CounterFit កំពុងដំណើរការ ហើយអូបសេនស័រ ពន្លឺ និង LED ត្រូវបានបង្កើតនៅលើខ្សែរភ្ជាប់ត្រឹមត្រូវ។

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Sending telemetry  {"light": 0}
    Sending telemetry  {"light": 0}
    ```

> 💁 អ្នកអាចរកកូដនេះនៅក្នុងថត [code-telemetry/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/virtual-device) ឬថត [code-telemetry/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/pi)។

😀 អ្នកបានផ្ញើទិន្នន័យទូទាំងពីឧបករណ៍របស់អ្នកដោយជោគជ័យ។

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**ការបដិសេធ**៖  
ឯកសារនេះត្រូវបានបកប្រែដោយប្រើសេវាកម្មបកប្រែ AI [Co-op Translator](https://github.com/Azure/co-op-translator)។ ខណៈពេលដែលយើងខំប្រឹងព្យាយាមរកភាពត្រឹមត្រូវ សូមយកចិត្តទុកដាក់ថាការបកប្រែដោយស្វ័យប្រវត្តិនេះអាចមានកំហុសឬការមិនត្រឹមត្រូវខ្លះៗ។ ឯកសារដើមនៅក្នុងភាសាមូលដ្ឋានគួរត្រូវបានពិចារណាថាជាអ្នកផ្តល់ព័ត៌មានដ៏មានសំខាន់។ សម្រាប់ព័ត៌មានសំខាន់ៗ សូមណែនាំឱ្យបកប្រែមនុស្សវិជ្ជាជីវៈ។ យើងមិនទទួលខុសត្រូវចំពោះការយល់ច្រឡំនិងការពិចារណាខុសៗដែលកើតឡើងពីការប្រើប្រាស់ការបកប្រែនេះឡើយ។
<!-- CO-OP TRANSLATOR DISCLAIMER END -->