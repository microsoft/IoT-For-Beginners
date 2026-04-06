# កំណត់ម៉ោងតុល្យ - Wio Terminal

នៅក្នុងផ្នែកនេះនៃមេរៀន អ្នកនឹងហៅកូដមិនមានម៉ាស៊ីនម៉ាស៊ីនរបស់អ្នកដើម្បីយល់អំពីសំឡេង និងកំណត់ម៉ោងតុល្យលើ Wio Terminal របស់អ្នកដោយផ្អែកលើលទ្ធផល។

## កំនត់ម៉ោងតុល្យ

អត្ថបទដែលត្រូវត្រឡប់មកពីការហៅសំឡេងទៅអត្ថបទត្រូវត្រូវផ្ញើទៅកូដមិនមានម៉ាស៊ីនម៉ាស៊ីនរបស់អ្នកសម្រាប់ដំណើរការ LUIS ដើម្បីទទួលបានចំនួនវិនាទីសម្រាប់ម៉ោងតុល្យ។ ចំនួនវិនាទីនេះអាចប្រើសម្រាប់កំណត់ម៉ោងតុល្យ។

Microcontrollers មិនមានការគាំទ្រដើម្បីមានព័ត៍មានច្រើននៃ​​ threads ក្នុង Arduino ដោយដើមទេ ដូច្នេះគ្មានថ្នាក់ម៉ោងតុល្យស្តង់ដារដូចដែលអ្នកអាចជួបនៅពេលបង្កើតកម្មវិធីនៅ Python ឬភាសាដទៃទៀតដែលមានកម្រិតខ្ពស់។ ជំនួសចំណុចនេះ អ្នកអាចប្រើបណ្ណាល័យម៉ោងតុល្យដែលធ្វើការដោយវាស់ពេលដែលបានកន្លងផុតក្នុងមុខងារ `loop` ហើយហៅមុខងារមានពេលវេលាបញ្ចប់។

### កិច្ចការជូន - ផ្ញើអត្ថបទទៅមុខងារមិនមានម៉ាស៊ីនម៉ាស៊ីន

1. បើកគម្រោង `smart-timer` ក្នុង VS Code ប្រសិនបើវាមិនទាន់បើក។

1. បើកឯកសារ header `config.h` ហើយបន្ថែម URL សម្រាប់កម្មវិធីមុខងាររបស់អ្នក៖

    ```cpp
    const char *TEXT_TO_TIMER_FUNCTION_URL = "<URL>";
    ```

    ជំនួស `<URL>` ជាមួយ URL របស់កម្មវិធីមុខងារដែលអ្នកបានទទួលនៅជំហានចុងក្រោយនៃមេរៀនចុងក្រោយ ដែលបញ្ជាក់ទៅកាន់អាសយដ្ឋាន IP របស់ម៉ាស៊ីនក្នុងតំបន់ដែលកំពុងរត់មុខងារនោះ។

1. បង្កើតឯកសារថ្មីមួយក្នុងថត `src` មានឈ្មោះ `language_understanding.h`។ នេះនឹងត្រូវបានប្រើសម្រាប់កំណត់ថ្នាក់មួយដើម្បីផ្ញើសំឡេងដែលត្រូវបានស្គាល់ទៅកម្មវិធីមុខងារ រួចបម្លែងទៅវិនាទីដោយការប្រើប្រាស់ LUIS។

1. បន្ថែមខាងក្រោមនេះនៅលើសំពាធនៃឯកសារនេះ៖

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    ```

    នេះរួមបញ្ចូលឯកសារមេដឹកនាំមួយចំនួនដែលត្រូវការ។

1. កំណត់ថ្នាក់មួយដែលមានឈ្មោះ `LanguageUnderstanding` ហើយប្រកាសមេរៀនម៉ាស៊ីនមួយរបស់ថ្នាក់នេះ៖

    ```cpp
    class LanguageUnderstanding
    {
    public:
    private:
    };

    LanguageUnderstanding languageUnderstanding;
    ```

1. ដើម្បីហៅមុខងាររបស់អ្នក អ្នកត្រូវចាត់ថ្នាក់ WiFi client។ បន្ថែមខាងក្រោមទំហំ `private` នៃថ្នាក់៖

    ```cpp
    WiFiClient _client;
    ```

1. នៅក្នុងផ្នែក `public` ប្រកាសមុខងារ​មួយដែលមានឈ្មោះ `GetTimerDuration` ដើម្បីហៅមុខងារនេះ៖

    ```cpp
    int GetTimerDuration(String text)
    {
    }
    ```

1. នៅក្នុងមុខងារ `GetTimerDuration` បន្ថែមកូដខាងក្រោមដើម្បីបង្កើត JSON ដែលត្រូវផ្ញើទៅមុខងារ៖

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    នេះបម្លែងអត្ថបទដែលផ្ញើទៅមុខងារ `GetTimerDuration` ទៅជា JSON ដូចខាងក្រោម៖

    ```json
    {
        "text" : "<text>"
    }
    ```

    ដែល `<text>` គឺជាអត្ថបទដែលផ្ញើទៅមុខងារ។

1. ខាងក្រោមនេះ បន្ថែមកូដខាងក្រោមដើម្បីអនុវត្តការហៅកូនហ្វុងខ្នាត់មុខងារ៖

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_TIMER_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    នេះបង្កើតការស្នើសុំ POST ទៅមុខងារ ដោយផ្ញើ JSON body ហើយទទួលស្តាតកូដតបសំរាប់។

1. បន្ថែមកូដខាងក្រោមនេះនៅក្រោម៖

    ```cpp
    int seconds = 0;
    if (httpResponseCode == 200)
    {
        String result = httpClient.getString();
        Serial.println(result);

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, result.c_str());

        JsonObject obj = doc.as<JsonObject>();
        seconds = obj["seconds"].as<int>();
    }
    else
    {
        Serial.print("Failed to understand text - error ");
        Serial.println(httpResponseCode);
    }
    ```

    កូដនេះពិនិត្យស្ថានភាពតប។ ប្រសិនបើវាជា 200 (ជោគជ័យ) នោះចំនួនវិនាទីសម្រាប់ម៉ោងតុល្យត្រូវបានទាញពីខ្លឹមសារតបស្រាប់។ បើមិនដូច្នោះទេ កំហុសត្រូវបានបញ្ជូនទៅម៉ូនីទ័រតាម Serial ហើយចំនួនវិនាទីត្រូវបានកំណត់ជា 0។

1. បន្ថែមកូដខាងក្រោមនៅចុងមុខងារ​នេះដើម្បីបិទការតភ្ជាប់ HTTP ហើយបង្វិលតម្លៃចំនួនវិនាទី៖

    ```cpp
    httpClient.end();

    return seconds;
    ```

1. នៅឯកសារ `main.cpp` បញ្ចូល header ថ្មីនេះ៖

    ```cpp
    #include "speech_to_text.h"
    ```

1. នៅចុងមុខងារ `processAudio` ហៅមុខងារ `GetTimerDuration` ដើម្បីទទួលបានរយៈពេលម៉ោងតុល្យ៖

    ```cpp
    int total_seconds = languageUnderstanding.GetTimerDuration(text);
    ```

    នេះបម្លែងអត្ថបទពីការហៅទៅថ្នាក់ `SpeechToText` ទៅជាចំនួនវិនាទីសម្រាប់ម៉ោងតុល្យ។

### កិច្ចការជូន - កំណត់ម៉ោងតុល្យ

ចំនួនវិនាទីអាចប្រើសម្រាប់កំណត់ម៉ោងតុល្យ។

1. បន្ថែមការគាំទ្របណ្ណាល័យខាងក្រោមទៅឯកសារ `platformio.ini` ដើម្បីបញ្ចូលបណ្ណាល័យសម្រាប់កំណត់ម៉ោងតុល្យ៖

    ```ini
    contrem/arduino-timer @ 2.3.0
    ```

1. បន្ថែមបញ្ជាដើម្បីរួមបញ្ចូលបណ្ណាល័យនេះក្នុងឯកសារ `main.cpp`៖

    ```cpp
    #include <arduino-timer.h>
    ```

1. ខាងលើមុខងារ `processAudio` បញ្ចូលកូដខាងក្រោម៖

    ```cpp
    auto timer = timer_create_default();
    ```

    កូដនេះបានប្រកាសម៉ោងតុល្យមួយដែលមានឈ្មោះ `timer`។

1. ខាងក្រោមនេះ បន្ថែមកូដខាងក្រោម៖

    ```cpp
    void say(String text)
    {
        Serial.print("Saying ");
        Serial.println(text);
    }
    ```

    មុខងារ `say` នេះនឹងបម្លែងអត្ថបទទៅសំឡេងនៅពេលក្រោយ ប៉ុន្តែក្នុងពេលនេះ វានឹងសរសេរអត្ថបទដែលបានផ្ញើទៅម៉ូនីទ័រតាម Serial។

1. ខាងក្រោមមុខងារ `say`, បន្ថែមកូដខាងក្រោម៖

    ```cpp
    bool timerExpired(void *announcement)
    {
        say((char *)announcement);
        return false;
    }
    ```

    នេះជាមុខងារត្រឡប់ហៅរវល់នេះដែលនឹងត្រូវហៅពេលម៉ោងតុល្យផុតកំណត់។ វាត្រូវបានផ្ញើសារ​ដែលត្រូវនិយាយពេលម៉ោងតុល្យផុតកំណត់។ ម៉ោងតុល្យអាចធ្វើម្តងទៀត ហើយអាចគ្រប់គ្រងដោយតម្លៃត្រឡប់មុខងារនេះ - វាត្រឡប់ `false` ដើម្បីប្រាប់ម៉ោងតុល្យមិនត្រូវរត់ម្ដងទៀត។

1. បន្ថែមកូដខាងក្រោមនៅចុងមុខងារ `processAudio`៖

    ```cpp
    if (total_seconds == 0)
    {
        return;
    }

    int minutes = total_seconds / 60;
    int seconds = total_seconds % 60;
    ```

    កូដនេះពិនិត្យចំនួនវិនាទីសរុប បើវាជា 0 វានឹងត្រលប់ពីមុខងារដើម្បីមិនកំណត់ម៉ោងតុល្យ។ បន្ទាប់មកវាបម្លែងចំនួនវិនាទីសរុបទៅជាទីនាទី និងវិនាទី។

1. ខាងក្រោមកូដនេះ បន្ថែមកូដដូចខាងក្រោមដើម្បីបង្កើតសារ​និយាយពេលម៉ោងតុល្យចាប់ផ្តើម៖

    ```cpp
    String begin_message;
    if (minutes > 0)
    {
        begin_message += minutes;
        begin_message += " minute ";
    }
    if (seconds > 0)
    {
        begin_message += seconds;
        begin_message += " second ";
    }

    begin_message += "timer started.";
    ```

1. ខាងក្រោមនេះ បន្ថែមកូដស្រដៀងគ្នាដើម្បីបង្កើតសារនិយាយពេលម៉ោងតុល្យផុតកំណត់៖

    ```cpp
    String end_message("Times up on your ");
    if (minutes > 0)
    {
        end_message += minutes;
        end_message += " minute ";
    }
    if (seconds > 0)
    {
        end_message += seconds;
        end_message += " second ";
    }

    end_message += "timer.";
    ```

1. បន្ទាប់ពីនេះ និយាយសារ​ចាប់ផ្តើមម៉ោងតុល្យ៖

    ```cpp
    say(begin_message);
    ```

1. នៅចុងមុខងារនេះ ចាប់ផ្តើមម៉ោងតុល្យ៖

    ```cpp
    timer.in(total_seconds * 1000, timerExpired, (void *)(end_message.c_str()));
    ```

    នេះបង្ហួតម៉ោងតុល្យ។ ម៉ោងតុល្យត្រូវបានកំណត់ជាមิล្លីវិនាទី ដូច្នេះចំនួនវិនាទីសរុបត្រូវគុណ 1,000 ដើម្បីបម្លែងទៅមิล្លីវិនាទី។ មុខងារ `timerExpired` ត្រូវបានផ្ញើជា callback ហើយ `end_message` ត្រូវបានផ្ញើជាប៉ារ៉ាម៉ែត្រដើម្បីផ្ញើទៅ callback។ Callback នេះគ្រាន់តែទទួលតែអាគុយម៉ង់ `void *` ដូច្នេះខ្សែអក្សរត្រូវបានបម្លែងតាមតម្រូវការ។

1. ចុងក្រោយ ម៉ោងតុល្យត្រូវតែ *tick* ហើយវាត្រូវបានអនុវត្តនៅក្នុងមុខងារ `loop`។ បន្ថែមកូដខាងក្រោមនៅចុងមុខងារ `loop`៖

    ```cpp
    timer.tick();
    ```

1. សាងសង់កូដនេះ អាប់ឡូដទៅ Wio Terminal របស់អ្នក និងសាកល្បងតាមម៉ូនីទ័រតាម Serial។ នៅពេលឃើញ `Ready` នៅម៉ូនីទ័រតាម Serial ចុចប៊ូតុង C (នៅជាន់ខាងឆ្វេង បិតជិតស៊្វេចបើកបុង) ហើយនិយាយ។ សំឡេង ៤ វិនាទីនឹងត្រូវបានចាប់យក បម្លែងទៅអត្ថបទ ហើយផ្ញើទៅកម្មវិធីមុខងាររបស់អ្នក ហើយម៉ោងតុល្យនឹងត្រូវរៀបចំ។ សូមប្រាកដថាកម្មវិធីមុខងាររបស់អ្នកកំពុងរត់ក្នុងតំបន់។

    អ្នកនឹងឃើញពេលម៉ោងតុល្យចាប់ផ្តើម និងពេលវាចប់។

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Got access token.
    Ready.
    Starting recording...
    Finished recording
    Sending speech...
    Speech sent!
    {"RecognitionStatus":"Success","DisplayText":"Set a 2 minute and 27 second timer.","Offset":4700000,"Duration":35300000}
    Set a 2 minute and 27 second timer.
    {"seconds": 147}
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```

> 💁 អ្នកអាចស្វែងរកកូដនេះនៅក្នុងថត [code-timer/wio-terminal](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/wio-terminal) ។

😀 កម្មវិធីម៉ោងតុល្យរបស់អ្នកបានជោគជ័យ!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**ការបដិសេធ**៖  
ឯកសារនេះត្រូវបានបកប្រែដោយប្រើសេវាកម្មបកប្រែ AI [Co-op Translator](https://github.com/Azure/co-op-translator)។ ទោះយើងខ្ញុំមានការខិតខំសម្រាប់ភាពត្រឹមត្រូវ​ សូមជ្រាបថា ការបកប្រែដោយដំណើរការស្វ័យប្រវត្តិប៉ុន្មានអាចមានកំហុស ឬ ភាពមិនត្រឹមត្រូវខ្លះៗ។ ឯកសារដើមជាភាសាដើមគួរត្រូវបានគិតថាជាទិន្នន័យផ្លូវការដោយសុពលភាព។ សម្រាប់ព័ត៌មានសំខាន់ៗ ការបកប្រែដោយមនុស្សជំនាញត្រូវបានណែនាំ។ យើងខ្ញុំមិនទទួលភារកិច្ចចំពោះការយល់ច្រឡំ ឬ ការបកប្រែខុសពីការប្រើប្រាស់ការបកប្រែនេះឡើយ។
<!-- CO-OP TRANSLATOR DISCLAIMER END -->