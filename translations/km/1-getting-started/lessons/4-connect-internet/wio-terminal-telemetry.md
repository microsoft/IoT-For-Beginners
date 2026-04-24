# គ្រប់គ្រងប្រភពពន្លឺយប់របស់អ្នកតាមរយៈអ៊ីនធឺណិត - Wio Terminal

នៅផ្នែកនេះនៃមេរៀន អ្នកនឹងផ្ញើព័ត៌មានតែលេមីត្រីជាមួយកម្រិតពន្លឺពី Wio Terminal របស់អ្នកទៅកាន់ម៉ាស៊ីនមេ MQTT។

## តម្លើងបណ្ណាល័យ JSON សម្រាប់ Arduino

វិធីពេញនិយមមួយក្នុងការផ្ញើសារតាម MQTT គឺការប្រើ JSON។ មានបណ្ណាល័យ Arduino សម្រាប់ JSON ដែលធ្វើឲ្យការអាននិងសរសេរ​ឯកសារ JSON កាន់តែងាយស្រួល។

### ភារកិច្ច

តម្លើងបណ្ណាល័យ Arduino JSON។

1. បើកគម្រោង nightlight នៅក្នុង VS Code។

1. បន្ថែមខាងក្រោមនេះជាបន្ទាត់បន្ថែមទៅក្នុងបញ្ជី `lib_deps` នៅក្នុងឯកសារ `platformio.ini`៖

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    វានាំចូល [ArduinoJson](https://arduinojson.org) ដែលជាបណ្ណាល័យ JSON សម្រាប់ Arduino ។

## បោះពុម្ពផ្សាយព័ត៌មានតេលេមីត្រី

ជំហានបន្ទាប់គឺបង្កើតឯកសារ JSON មានព័ត៌មានតេលេមីត្រី ហើយផ្ញើវាទៅម៉ាស៊ីនមេ MQTT។

### ភារកិច្ច - បោះពុម្ពផ្សាយព័ត៌មានតេលេមីត្រី

បោះពុម្ពផ្សាយព័ត៌មានតេលេមីត្រីទៅម៉ាស៊ីនមេ MQTT។

1. បន្ថែមកូដខាងក្រោមទៅចុងឯកសារ `config.h` ដើម្បីកំណត់ឈ្មោះប្រធានបទតេលេមីត្រីសម្រាប់ម៉ាស៊ីនមេ MQTT៖

    ```cpp
    const string CLIENT_TELEMETRY_TOPIC = ID + "/telemetry";
    ```

    `CLIENT_TELEMETRY_TOPIC` ជាប្រធានបទដែលឧបករណ៍នឹងបោះពុម្ពផ្សាយកម្រិតពន្លឺទៅ។

1. បើកឯកសារ `main.cpp`

1. បន្ថែមការបញ្ជាក់ `#include` ខាងក្រោមនៅផ្នែកលើនៃឯកសារ៖

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. បន្ថែមកូដខាងក្រោមនៅក្នុងមុខងារ `loop` មុន `delay`៖

    ```cpp
    int light = analogRead(WIO_LIGHT);

    DynamicJsonDocument doc(1024);
    doc["light"] = light;

    string telemetry;
    serializeJson(doc, telemetry);

    Serial.print("Sending telemetry ");
    Serial.println(telemetry.c_str());

    client.publish(CLIENT_TELEMETRY_TOPIC.c_str(), telemetry.c_str());
    ```

    កូដនេះអានកម្រិតពន្លឺ និងបង្កើតឯកសារ JSON ដោយប្រើ ArduinoJson ដែលមានកម្រិតនេះ។ បន្ទាប់មកវាត្រូវបានបម្លែងទៅជាខ្សែអក្សរហើយបានបោះពុម្ពផ្សាយលើប្រធានបទ MQTT តេលេមីត្រីដោយអតិថិជន MQTT។

1. បញ្ចូលកូដទៅ Wio Terminal របស់អ្នក ហើយប្រើ Serial Monitor ដើម្បីមើលកម្រិតពន្លឺដែលកំពុងត្រូវបានផ្ញើទៅម៉ាស៊ីនមេ MQTT។

    ```output
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"light":652}
    Sending telemetry {"light":612}
    Sending telemetry {"light":583}
    ```

> 💁 អ្នកអាចស្វែងរកកូដនេះនៅក្នុងថត [code-telemetry/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/wio-terminal)។

😀 អ្នកបានផ្ញើព័ត៌មានតេលេមីត្រីពីឧបករណ៍របស់អ្នកដោយជោគជ័យ។

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**ការបដិសេធ**៖  
ឯកសារនេះត្រូវបានបកប្រែដោយប្រើសេវាបកប្រែ AI [Co-op Translator](https://github.com/Azure/co-op-translator)។ ខណៈពេលដែលយើងខិតខំប្រឹងប្រែងសម្រាប់ភាពត្រឹមត្រូវ សូមយល់ដឹងថាការបកប្រែដោយស្វ័យប្រវត្តិអាចមានកំហុសឬភាពមិនត្រឹមត្រូវ។ ឯកសារដើមនៅក្នុងភាសាមាតុភាសារបស់វាគួរត្រូវបានគិតថាជាផ្នែកដើមដែលមានសិទ្ធិពេញលេញ។ សម្រាប់ព័ត៌មានដែលចាំបាច់ខ្លាំង ការបកប្រែដោយមនុស្សជំនាញគឺត្រូវបានណែនាំ។ យើងមិនទទួលខុសត្រូវចំពោះការយល់ច្រឡំ ឬការបកអក្សរមិនត្រឹមត្រូវណាមួយដែលកើតឡើងពីការប្រើប្រាស់ការបកប្រែនេះទេ។
<!-- CO-OP TRANSLATOR DISCLAIMER END -->