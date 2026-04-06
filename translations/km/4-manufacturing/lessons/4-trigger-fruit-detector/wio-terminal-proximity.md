# ការស្វែងរកចំងាយជិត - Wio Terminal

នៅផ្នែកនេះនៃមេរៀន អ្នកនឹងបន្ថែមស៊ងស៊ន្សឺរ proximity ទៅកាន់ Wio Terminal របស់អ្នក ហើយអានចម្ងាយពីវា។

## ម៉ាស៊ីនភាគហ៊ុន

Wio Terminal ត្រូវការស៊ន្សឺរ proximity។

ស៊ន្សឺរដែលអ្នកនឹងប្រើគឺ [Grove Time of Flight distance sensor](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html)។ ស៊ន្សឺរនេះប្រើម៉ូឌុលវាស់ចម្ងាយដោយឡាស៊ែរ ដើម្បីរកមើលចម្ងាយ។ ស៊ន្សឺរនេះមានជួរពី 10mm ដល់ 2000mm (1cm - 2m) ហើយនឹងរាយការណ៍តម្លៃនៅក្នុងជួរនេះបានយ៉ាងត្រឹមត្រូវ ដោយចម្ងាយលើស 1000mm នឹងរាយការណ៍ជារូបិយវត្ថុ 8109mm។

ម៉ូឌុលកម្របឡាស៊ែរ មាននៅខាងក្រោយនៃស៊ន្សឺរ ផ្ទុយទៅនឹងចំហៀង Grove socket។

នេះគឺជាស៊ន្សឺរ I<sup>2</sup>C។

### ការតភ្ជាប់ស៊ន្សឺរតាមរយៈ time of flight

ស៊ន្សឺរ Grove time of flight អាចត្រូវបានភ្ជាប់ទៅកាន់ Wio Terminal។

#### បម្មការ - តភ្ជាប់ស៊ន្សឺរតាមរយៈ time of flight

តភ្ជាប់ស៊ន្សឺរតាមរយៈ time of flight។

![A grove time of flight sensor](../../../../../translated_images/km/grove-time-of-flight-sensor.d82ff2165bfded9f.webp)

1. ដាក់ចុងខាងមួយនៃខ្សែនិង Grove ចូលទៅក្នុងចំហៀងនៅលើស៊ន្សឺរតាមរយៈ time of flight។ វានឹងដំណើរការតែទៅតែម្តងប៉ុណ្ណោះ។

1. ជាមួយនឹងការដែល Wio Terminal បានផ្តល់អគ្គិសនីពីកុំព្យូទ័រឬប្រភពថាមពលផ្សេងទៀត ខ្សែនិង Grove ខាងមួយទៀតត្រូវតភ្ជាប់ទៅកាន់ចំហៀង Grove ខាងឆ្វេងនៅលើ Wio Terminal នៅពេលដែលអ្នកមើលទៅកាន់អេក្រង់។ នេះជាចំហៀងដែលនៅជិតប៊ូតុងថាមពល។ នេះគឺជាចំហៀងផ្ទុកឌីជីថល និង I<sup>2</sup>C ប្រភេទរួម។

![The grove time of flight sensor connected to the left hand socket](../../../../../translated_images/km/wio-time-of-flight-sensor.c4c182131d2ea73d.webp)

1. ឥឡូវនេះ អ្នកអាចភ្ជាប់ Wio Terminal ទៅកាន់កុំព្យូទ័ររបស់អ្នក។

## កម្មវិធីសម្រាប់ស៊ន្សឺរតាមរយៈ time of flight

ឥឡូវនេះ Wio Terminal អាចត្រូវបានកម្មវិធីដើម្បីប្រើស៊ន្សឺរតាមរយៈ time of flight ដែលភ្ជាប់នៅជាមួយ។

### បម្មការ - កម្មវិធីសម្រាប់ស៊ន្សឺរតាមរយៈ time of flight

1. បង្កើតគម្រោង Wio Terminal ថ្មីមួយ ដោយប្រើ PlatformIO ហៅគម្រោងនេះថា `distance-sensor`។ បន្ថែមកូដនៅក្នុងមុខងារ `setup` ដើម្បីកំណត់ច្រកស៊េរី។

1. បន្ថែមផ្នែកអាស្រ័យសមាសភាពសម្រាប់បណ្ណាល័យ Seeed Grove time of flight distance sensor ចូលក្នុងឯកសារ `platformio.ini` របស់គម្រោង៖

    ```ini
    lib_deps =
        seeed-studio/Grove Ranging sensor - VL53L0X @ ^1.1.1
    ```

1. ក្នុងឯកសារ `main.cpp` បន្ថែមខាងក្រោមនៃការបញ្ចូលបណ្ណាល័យដែលមានរួច ដើម្បីប្រកាសអនុគមន៍នៃ `Seeed_vl53l0x` ដែលប្រើសម្រាប់អន្តរកម្មជាមួយស៊ន្សឺរតាមរយៈ time of flight៖

    ```cpp
    #include "Seeed_vl53l0x.h"
    
    Seeed_vl53l0x VL53L0X;
    ```

1. បន្ថែមខាងក្រោមនៃមុខងារ `setup` ដើម្បីចាប់ផ្តើមស៊ន្សឺរ៖

    ```cpp
    VL53L0X.VL53L0X_common_init();
    VL53L0X.VL53L0X_high_accuracy_ranging_init();
    ```

1. ក្នុងមុខងារ `loop` អានតម្លៃមួយពីស៊ន្សឺរ៖

    ```cpp
    VL53L0X_RangingMeasurementData_t RangingMeasurementData;
    memset(&RangingMeasurementData, 0, sizeof(VL53L0X_RangingMeasurementData_t));

    VL53L0X.PerformSingleRangingMeasurement(&RangingMeasurementData);
    ```

    កូដនេះបង្កើតរចនាសម្ព័ន្ធទិន្នន័យមួយសម្រាប់អានទិន្នន័យបន្ទាប់មកបញ្ជូនវាទៅវិធីសាស្ត្រ `PerformSingleRangingMeasurement` ដែលវានឹងបំពេញជាមួយតម្លៃវាស់ចម្ងាយ។

1. ខាងក្រោមនោះ សរសេរចេញវិមាត្រចម្ងាយហើយពន្យារពេល 1 វិនាទី៖

    ```cpp
    Serial.print("Distance = ");
    Serial.print(RangingMeasurementData.RangeMilliMeter);
    Serial.println(" mm");

    delay(1000);
    ```

1. សង់ បញ្ចូល និងដំណើរការកូដនេះ។ អ្នកនឹងអាចមើលឃើញការវាស់ចម្ងាយជាមួយកម្មវិធីត следរមើលឃើញស៊េរី។ ដាក់វត្ថុជិតស៊ន្សឺរហើយអ្នកនឹងឃើញការវាស់ចម្ងាយ៖

    ```output
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    ម៉ូឌុលកម្របឡាស៊ែរ មាននៅខាងក្រោយនៃស៊ន្សឺរ ដូច្នេះទាក់ទាញប្រាកដប្រជា ដើម្បីប្រើម្ខាងត្រឹមត្រូវនៅពេលវាស់ចម្ងាយ។

    ![The rangefinder on the back of the time of flight sensor pointing at a banana](../../../../../translated_images/km/time-of-flight-banana.079921ad8b1496e4.webp)

> 💁 អ្នកអាចស្វែងរកកូដនេះនៅក្នុងថត [code-proximity/wio-terminal](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/wio-terminal)។

😀 កម្មវិធីស៊ន្សឺរ proximity របស់អ្នកបានជោគជ័យ!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**ការពន្យល់**៖  
ឯកសារនេះត្រូវបានបកប្រែដោយប្រើសេវាបកប្រែ AI [Co-op Translator](https://github.com/Azure/co-op-translator)។ ខណៈពេលយើងខិតខំរកភាពត្រឹមត្រូវ សូមយល់ដឹងថាការបកប្រែដោយស្វ័យប្រវត្តិអាចមានកំហុស ឬភាពខុសខាងច្រឡំនៅក្នុងខ្លះ។ ឯកសារដើមនៅក្នុងភាសាម្ដ្ឋាភាសាគួរត្រូវបានជាលទ្ធផលផ្លូវការជាដើម។ សម្រាប់ព័ត៌មានមានសារៈសំខាន់ មានការផ្ដល់អនុសាសន៍អោយបកប្រែដោយអ្នកជាសហការីជំនាញ។ យើងមិនទទួលខុសត្រូវចំពោះការយល់ច្រឡំនោះ ឬការបកប្រែខុសដែលកើតឡើងពីការប្រើប្រាស់បកប្រែនេះឡើយ។
<!-- CO-OP TRANSLATOR DISCLAIMER END -->