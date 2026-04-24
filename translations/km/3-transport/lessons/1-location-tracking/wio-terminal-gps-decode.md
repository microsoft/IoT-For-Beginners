# ដកស្រង់ទិន្នន័យ GPS - Wio Terminal

នៅផ្នែកនេះនៃមេរៀន អ្នកនឹងដកស្រង់សារពីប្រភេទ NMEA ដែលបានអានពីឧបករណ៍អាប់ឌែនសញ្ញា GPS ដោយ Wio Terminal ហើយដកយកទិសដៅរយៈទទឹងបច្ចុប្បន្ននិងរយៈបណ្ដោយ។

## ដកស្រង់ទិន្នន័យ GPS

បន្ទាប់ពីទិន្នន័យ NMEA ចុងក្រោយត្រូវបានអានពីរបារសេរី វាអាចត្រូវបានដកស្រង់ដោយប្រើបណ្ណាល័យ NMEA ដ៏ចំហ។

### បេសកកម្ម - ដកស្រង់ទិន្នន័យ GPS

ប្រើប្រាស់កម្មវិធីដើម្បីដកស្រង់ទិន្នន័យ GPS។

1. បើកម៉ាស្សាជាកម្មវិធី `gps-sensor` ប្រសិនបើវាមិនត្រូវបានបើករួចហើយ

1. បន្ថែមការជាប់ទាក់ទងបណ្ណាល័យសម្រាប់បណ្ណាល័យ [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus) ទៅក្នុងឯកសារ `platformio.ini` នៃគម្រោង។ បណ្ណាល័យនេះមានកូដសម្រាប់ដកស្រង់ទិន្នន័យ NMEA។

    ```ini
    lib_deps =
        mikalhart/TinyGPSPlus @ 1.0.2
    ```

1. នៅក្នុងឯកសារ `main.cpp` បន្ថែមបញ្ជាលើសម្រាប់បណ្ណាល័យ TinyGPSPlus៖

    ```cpp
    #include <TinyGPS++.h>
    ```

1. ក្រោមការប្រកាស `Serial3` ប្រកាសវត្ថុ TinyGPSPlus មួយសម្រាប់ដំណើរការវាខ្សែ NMEA៖

    ```cpp
    TinyGPSPlus gps;
    ```

1. ផ្លាស់ប្ដូរគន្លងនៅមុខងារ `printGPSData` ទៅដូចកម្មវិធីខាងក្រោម៖

    ```cpp
    if (gps.encode(Serial3.read()))
    {
        if (gps.location.isValid())
        {
            Serial.print(gps.location.lat(), 6);
            Serial.print(F(","));
            Serial.print(gps.location.lng(), 6);
            Serial.print(" - from ");
            Serial.print(gps.satellites.value());
            Serial.println(" satellites");
        }
    }
    ```

    កូដនេះអានតួអក្សរបន្ទាប់ពីលុបចេញពីផតថល UART ហៅទៅកាន់កម្មវិធីដកស្រង់ NMEA ដែលមានឈ្មោះ `gps`។ បន្ទាប់ពីអានតួអក្សរមួយៗ វានឹងត្រួតពិនិត្យមើលថាតើកម្មវិធីដកស្រង់អានប្រយោគដែលត្រឹមត្រូវ ឬទេ ហើយបន្ទាប់មកត្រួតពិនិត្យមើលថាតើវាអានទីតាំងដែលត្រឹមត្រូវ ឬអត់។ ប្រសិនបើទីតាំងត្រឹមត្រូវ វានឹងផ្ញើទៅកាន់ម៉ូនីទ័រសេរី ដោយមានចំនួនផ្កាយសតាតែលាដែលបានរួមចំណែកក្នុងការកំណត់ទីតាំងនេះផងដែរ។

1. សង់និងផ្ទុកកូដទៅកាន់ Wio Terminal។

1. បន្ទាប់ពីបានផ្ទុករួច អ្នកអាចត្រួតពិនិត្យទិន្នន័យទីតាំង GPS ដោយប្រើម៉ូនីទ័រសេរីបាន។

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 អ្នកអាចរក្គកូដនេះបាននៅក្នុងថត [code-gps-decode/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/wio-terminal)។

😀 កម្មវិធីឧបករណ៍សង្ឃឹម GPS របស់អ្នកជាមួយការដកស្រង់ទិន្នន័យបានជោគជ័យ!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**ការបដិសេធ**:  
ឯកសារនេះត្រូវបានបកប្រែដោយប្រើសេវាកម្មបកប្រែ AI [Co-op Translator](https://github.com/Azure/co-op-translator)។ ខណៈពេលយើងខិតខំរកភាពត្រឹមត្រូវ សូមជ្រាបថាការបកប្រែដោយស្វ័យប្រវត្តិក្នុងមួយចំនួនអាចមានកំហុស ឬភាពមិនត្រឹមត្រូវ។ ឯកសារដើមដែលមានជាភាសាដើមគួរត្រូវបានគិតជាធនធានមានអាជ្ញាសិទ្ធិសម្រាប់ព័ត៌មាន។ សម្រាប់ព័ត៌មានសំខាន់ៗ សូមណែនាំឲ្យប្រើការបកប្រែដោយមនុស្សដែលមានជំនាញ។ យើងមិនទទួលខុសត្រូវចំពោះការយល់ច្រឡំ ឬការបកប្រែខុស បង្កឡើងពីការប្រើប្រាស់ការបកប្រែនេះទេ។
<!-- CO-OP TRANSLATOR DISCLAIMER END -->