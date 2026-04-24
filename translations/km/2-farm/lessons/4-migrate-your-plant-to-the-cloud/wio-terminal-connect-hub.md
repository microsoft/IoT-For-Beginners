# តភ្ជាប់ឧបករណ៍ IoT របស់អ្នកទៅកាន់ពពក - Wio Terminal

នៅផ្នែកនេះនៃមេរៀន អ្នកនឹងតភ្ជាប់ Wio Terminal របស់អ្នកទៅកាន់ IoT Hub ដើម្បីផ្ញើព័ត៌មាន telemetry និងទទួលការបញ្ជា។

## តភ្ជាប់ឧបករណ៍របស់អ្នកទៅ IoT Hub

ជំហានបន្ទាប់គឺតភ្ជាប់ឧបករណ៍របស់អ្នកទៅ IoT Hub។

### ការងារ - តភ្ជាប់ទៅ IoT Hub

1. បើកគម្រោង `soil-moisture-sensor` នៅក្នុង VS Code

1. បើកឯកសារ `platformio.ini`។ យកការពឹងផ្អែកលើបណ្ណាល័យ `knolleary/PubSubClient` ចេញ។ នេះត្រូវបានប្រើសម្រាប់តភ្ជាប់ទៅ broker MQTT សាធារណៈ ហើយមិនចាំបាច់ទេដើម្បីតភ្ជាប់ទៅ IoT Hub។

1. បន្ថែមការពឹងផ្អែកលើបណ្ណាល័យដូចខាងក្រោម៖

    ```ini
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    arduino-libraries/AzureIoTHub @ 1.6.0
    azure/AzureIoTUtility @ 1.6.1
    azure/AzureIoTProtocol_MQTT @ 1.6.0
    azure/AzureIoTProtocol_HTTP @ 1.6.0
    azure/AzureIoTSocket_WiFi @ 1.0.2
    ```

    បណ្ណាល័យ `Seeed Arduino RTC` ផ្តល់កូដដើម្បីអន្តរសកម្មជាមួយនឹងម៉ោងពិតនៅក្នុង Wio Terminal ដែលប្រើសម្រាប់តាមដានពេលវេលា។ បណ្ណាល័យដែលនៅសល់អនុញាតឲ្យឧបករណ៍ IoT របស់អ្នកតភ្ជាប់ទៅ IoT Hub។

1. បន្ថែមអ្វីខាងក្រោមទៅចុងឯកសារ `platformio.ini`៖

    ```ini
    build_flags =
        -DDONT_USE_UPLOADTOBLOB
    ```

    នេះកំណត់ស្លាកកូដដែលត្រូវការពេលកូដ Arduino IoT Hub ត្រូវបានបញ្ចូល។

1. បើកឯកសារ header `config.h`។ លុបការកំណត់ MQTT ទាំងអស់ចេញ ហើយបន្ថែមអចលនៈខាងក្រោមសម្រាប់ខ្សែផ្សារតភ្ជាប់ឧបករណ៍៖

    ```cpp
    // ការកំណត់ IoT Hub
    const char *CONNECTION_STRING = "<connection string>";
    ```

    ប្ដូរទៅ `<connection string>` ជាខ្សែផ្សារតភ្ជាប់សម្រាប់ឧបករណ៍របស់អ្នកដែលអ្នកបានចម្លងមុននេះ។

1. ការតភ្ជាប់ទៅ IoT Hub ប្រើ token ដែលផ្អែកលើពេលវេលា។ នេះមានន័យថាឧបករណ៍ IoT ត្រូវការដឹងពេលវេលាបច្ចុប្បន្ន។ ខុសពីប្រព័ន្ធប្រតិបត្តិការដូចជា Windows, macOS ឬ Linux, មីក្រូកុងត្រូលឡើងដោយស្វ័យប្រវត្តិមិនត្រូវបាន đồng bộ ពេលវេលាបច្ចុប្បន្នតាមអ៊ីនធឺណិតទេ។ នេះមានន័យថាអ្នកត្រូវបន្ថែមកូដដើម្បីទទួលបានពេលវេលាបច្ចុប្បន្នពីម៉ាស៊ីនបម្រើ [NTP](https://wikipedia.org/wiki/Network_Time_Protocol)។ បន្ទាប់ពីទទួលបានពេលវេលា វានឹងអាចរក្សាទុកនៅម៉ោងពិតនៅក្នុង Wio Terminal ដែលអនុញ្ញាតឲ្យសំណើពេលវេលាត្រឹមត្រូវនៅថ្ងៃក្រោយបាន ដោយផ្អែកលើថាឧបករណ៍មិនបាត់បង់ថាមពល។ បន្ថែមឯកសារថ្មីដែលមានឈ្មោះ `ntp.h` ជាមួយកូដដូចខាងក្រោម៖

    ```cpp
    #pragma once
    
    #include "DateTime.h"
    #include <time.h>
    #include "samd/NTPClientAz.h"
    #include <sys/time.h>

    static void initTime()
    {
        WiFiUDP _udp;
        time_t epochTime = (time_t)-1;
        NTPClientAz ntpClient;

        ntpClient.begin();

        while (true)
        {
            epochTime = ntpClient.getEpochTime("0.pool.ntp.org");

            if (epochTime == (time_t)-1)
            {
                Serial.println("Fetching NTP epoch time failed! Waiting 2 seconds to retry.");
                delay(2000);
            }
            else
            {
                Serial.print("Fetched NTP epoch time is: ");

                char buff[32];
                sprintf(buff, "%.f", difftime(epochTime, (time_t)0));
                Serial.println(buff);
                break;
            }
        }

        ntpClient.end();

        struct timeval tv;
        tv.tv_sec = epochTime;
        tv.tv_usec = 0;

        settimeofday(&tv, NULL);
    }
    ```

    ព័ត៌មានលម្អិតនៃកូដនេះកន្លងពីវិសាលភាពនៃមេរៀននេះ។ វាដាក់ពាក្យបញ្ជាទៅនូវមុខងារមួយឈ្មោះ `initTime` ដែលទទួលពេលវេលាបច្ចុប្បន្នពីម៉ាស៊ីនបម្រើ NTP ហើយប្រើវាដើម្បីកំណត់ម៉ោងលើ Wio Terminal។

1. បើកឯកសារ `main.cpp` ហើយលុបកូដ MQTT ទាំងអស់ រួមទាំងឯកសារ header `PubSubClient.h`, ការបញ្ជាក់អថេរ `PubSubClient`, វិធីសាស្ត្រ `reconnectMQTTClient` និង `createMQTTClient`, និងការហៅទៅអថេរ និងវិធីសាស្ត្រទាំងនេះ។ ឯកសារនេះគួរតែមានកូដសម្រាប់តភ្ជាប់ WiFi, ទទួលសំណើរជាតិដី និងបង្កើតឯកសារ JSON ពីវា ប៉ុណ្ណោះ។

1. បន្ថែមនូវការបញ្ជាក់ `#include` ខាងលើឯកសារ `main.cpp` ដើម្បីបញ្ចូលបណ្ណាល័យ IoT Hub និងការកំណត់ពេលវេលា៖

    ```cpp
    #include <AzureIoTHub.h>
    #include <AzureIoTProtocol_MQTT.h>
    #include <iothubtransportmqtt.h>
    #include "ntp.h"
    ```

1. បន្ថែមការហៅខាងក្រោមចុងមុខងារ `setup` ដើម្បីកំណត់ពេលវេលាបច្ចុប្បន្ន៖

    ```cpp
    initTime();
    ```

1. បន្ថែមការបញ្ជាក់អថេរខាងលើឯកសារ ក្រោមការបញ្ចូល `#include`៖

    ```cpp
    IOTHUB_DEVICE_CLIENT_LL_HANDLE _device_ll_handle;
    ```

    នេះបញ្ជាក់អថេរ `IOTHUB_DEVICE_CLIENT_LL_HANDLE` ដែលជាឈរជាប់ទៅកាន់ការតភ្ជាប់ទៅ IoT Hub។

1. ក្រោមនេះ បន្ថែមកូដដូចខាងក្រោម៖

    ```cpp
    static void connectionStatusCallback(IOTHUB_CLIENT_CONNECTION_STATUS result, IOTHUB_CLIENT_CONNECTION_STATUS_REASON reason, void *user_context)
    {
        if (result == IOTHUB_CLIENT_CONNECTION_AUTHENTICATED)
        {
            Serial.println("The device client is connected to iothub");
        }
        else
        {
            Serial.println("The device client has been disconnected");
        }
    }
    ```

    នេះបញ្ជាក់មុខងារត្រឡប់ប្រតិកម្មមួយដែលនឹងត្រូវហៅពេលកម្រិតស្ថានភាពនៃការតភ្ជាប់ទៅ IoT Hub ផ្លាស់ប្ដូរ ដូចជាការតភ្ជាប់ឬដាច់ការតភ្ជាប់។ ស្ថានភាពនេះត្រូវបានផ្ញើទៅច្រកស៊េរី។

1. ក្រោមនេះ បន្ថែមមុខងារមួយសម្រាប់តភ្ជាប់ទៅ IoT Hub៖

    ```cpp
    void connectIoTHub()
    {
        IoTHub_Init();
    
        _device_ll_handle = IoTHubDeviceClient_LL_CreateFromConnectionString(CONNECTION_STRING, MQTT_Protocol);
        
        if (_device_ll_handle == NULL)
        {
            Serial.println("Failure creating Iothub device. Hint: Check your connection string.");
            return;
        }
    
        IoTHubDeviceClient_LL_SetConnectionStatusCallback(_device_ll_handle, connectionStatusCallback, NULL);
    }
    ```

    កូដនេះចាប់ផ្តើមបណ្ណាល័យ IoT Hub រួចបង្កើតការតភ្ជាប់ដោយប្រើខ្សែផ្សារតភ្ជាប់នៅក្នុងឯកសារ header `config.h`។ ការតភ្ជាប់នេះផ្អែកលើ MQTT។ បើការតភ្ជាប់បរាជ័យ នេះនឹងត្រូវផ្ញើទៅច្រកស៊េរី - ប្រសិនបើអ្នកឃើញនេះនៅក្នុងលទ្ធផល សូមពិនិត្យខ្សែផ្សារតភ្ជាប់។ ចុងក្រោយ ការត្រឡប់ប្រតិកម្មស្ថានភាពត្រូវបានកំណត់។

1. ហៅមុខងារនេះនៅក្នុងមុខងារ `setup` ខាងក្រោមការហៅ `initTime`៖

    ```cpp
    connectIoTHub();
    ```

1. ដូចគ្នា និងកម្រិត MQTT client កូដនេះរត់នៅលើខ្សែទិន្នន័យតែមួយ ដូច្នេះត្រូវការពេលវេលាគ្រប់គ្រាន់សម្រាប់ដំណើរការសារ របស់ hub ផ្ញើ និងទទួល។ បន្ថែមខាងក្រោមទៅខាងលើមុខងារ `loop` ដើម្បីធ្វើដូចនេះ៖

    ```cpp
    IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
    ```

1. បង្កើត និងផ្ទុកឡើងកូដនេះ។ អ្នកនឹងឃើញការតភ្ជាប់នៅក្នុងមន្រ្តីមើលស៊េរី៖

    ```output
    Connecting to WiFi..
    Connected!
    Fetched NTP epoch time is: 1619983687
    Sending telemetry {"soil_moisture":391}
    The device client is connected to iothub
    ```

    នៅក្នុងលទ្ធផល អ្នកអាចឃើញពេលវេលា NTP ត្រូវបានយកមក តាមក្រោយដោយការតភ្ជាប់ឧបករណ៍ client។ វាអាចប្រើពេលប៉ុន្មានវិនាទីដើម្បីតភ្ជាប់ ដូច្នេះអ្នកអាចឃើញជាតិដីក្នុងលទ្ធផល ខណៈពេលឧបករណ៍កំពុងតភ្ជាប់។

    > 💁 អ្នកអាចបម្លែងពេលវេលា UNIX សម្រាប់ NTP ទៅជាចំលងអាចអានបានជាងនេះដោយប្រើវេបសាយដូចជា [unixtimestamp.com](https://www.unixtimestamp.com)

## ផ្ញើ telemetry

ឥឡូវនេះឧបករណ៍របស់អ្នកត្រូវបានតភ្ជាប់ អ្នកអាចផ្ញើ telemetry ទៅ IoT Hub ជំនួស broker MQTT។

### ការងារ - ផ្ញើ telemetry

1. បន្ថែមមុខងារខាងលើមុខងារ `setup`៖

    ```cpp
    void sendTelemetry(const char *telemetry)
    {
        IOTHUB_MESSAGE_HANDLE message_handle = IoTHubMessage_CreateFromString(telemetry);
        IoTHubDeviceClient_LL_SendEventAsync(_device_ll_handle, message_handle, NULL, NULL);
        IoTHubMessage_Destroy(message_handle);
    }
    ```

    កូដនេះបង្កើតសារពីខ្សែអក្សរដែលផ្ទេរជាពារ៉ាម៉ែត្រ បញ្ជូនទៅ hub បន្ទាប់លុបវត្ថុសារនោះ។

1. ហៅកូដនេះនៅក្នុងមុខងារ `loop` ខាងក្រោមជួរដែលផ្ញើ telemetry ទៅច្រកស៊េរី៖

    ```cpp
    sendTelemetry(telemetry.c_str());
    ```

## គ្រប់គ្រងការបញ្ជា

ឧបករណ៍របស់អ្នកត្រូវតែគ្រប់គ្រងការបញ្ជាមួយពីកូដម៉ាស៊ីនបម្រើ ដើម្បីគ្រប់គ្រង relay។ នេះត្រូវបានផ្ញើជាការស្នើសុំមុខងារ និងទទួលបានដោយផ្ទាល់។

## ការងារ - គ្រប់គ្រងការស្នើសុំមុខងារផ្ទាល់

1. បន្ថែមកូដខាងក្រោមមុនមុខងារ `connectIoTHub`៖

    ```cpp
    int directMethodCallback(const char *method_name, const unsigned char *payload, size_t size, unsigned char **response, size_t *response_size, void *userContextCallback)
    {
        Serial.printf("Direct method received %s\r\n", method_name);
    
        if (strcmp(method_name, "relay_on") == 0)
        {
            digitalWrite(PIN_WIRE_SCL, HIGH);
        }
        else if (strcmp(method_name, "relay_off") == 0)
        {
            digitalWrite(PIN_WIRE_SCL, LOW);
        }
    }
    ```

    កូដនេះកំណត់មុខងារត្រឡប់ប្រតិកម្មដែលបណ្ណាល័យ IoT Hub អាចហៅពេលវាទទួលបានសំណើសុំមុខងារផ្ទាល់។ មុខងារដែលត្រូវរកសូនឹងត្រូវផ្ញើក្នុងប៉ារ៉ាម៉ែត្រ `method_name`។ មុខងារនេះព្រីនមុខងារដែលត្រូវហៅទៅច្រកស៊េរី ហើយបិទឬបើក relay ដោយផ្អែកលើឈ្មោះមុខងារ។

    > 💁 នេះក៏អាចអនុវត្តបានជាការស្នើសុំមុខងារផ្ទាល់តែមួយ ដោយផ្ញើស្ថានភាព relay ដែលចង់បានក្នុងគ្រាប់Payload ដែលអាចផ្ញើជាមួយសំណើនិងអាចប្រើបានពីប៉ារ៉ាម៉ែត្រ `payload`។

1. បន្ថែមកូដខាងក្រោមចុងមុខងារ `directMethodCallback`៖

    ```cpp
    char resultBuff[16];
    sprintf(resultBuff, "{\"Result\":\"\"}");
    *response_size = strlen(resultBuff);
    *response = (unsigned char *)malloc(*response_size);
    memcpy(*response, resultBuff, *response_size);

    return IOTHUB_CLIENT_OK;
    ```

    សំណើសុំមុខងារផ្ទាល់ត្រូវការឆ្លើយតប ហើយការឆ្លើយតបមានពីរផ្នែក - ជាអត្ថបទផ្តល់ចម្លើយ និងកូដបញ្ជូនត្រឡប់។ កូដនេះនឹងបង្កើតលទ្ធផលជាឯកសារ JSON ដូចខាងក្រោម៖

    ```JSON
    {
        "Result": ""
    }
    ```

    នេះបន្ទាប់ត្រូវបានចម្លងទៅប៉ារ៉ាម៉ែត្រ `response` ហើយទំហំនេះត្រូវបានកំណត់នៅប៉ារ៉ាម៉ែត្រ `response_size`។ កូដនេះប្រគល់តម្លៃ `IOTHUB_CLIENT_OK` ដើម្បីបង្ហាញថាមុខងារត្រូវបានគ្រប់គ្រងបានត្រឹមត្រូវ។

1. ភ្ជាប់ callback ដោយបន្ថែមខាងក្រោមចុងមុខងារ `connectIoTHub`៖

    ```cpp
    IoTHubClient_LL_SetDeviceMethodCallback(_device_ll_handle, directMethodCallback, NULL);
    ```

1. មុខងារ `loop` នឹងហៅមុខងារ `IoTHubDeviceClient_LL_DoWork` ដើម្បីដំណើរការការកើតហេតុដែលផ្ញើដោយ IoT Hub។ នេះមានកំណត់ហៅរៀងរាល់ ១០ វិនាទីដោយសារពេលយឺត `delay` ដែលមានន័យថាមុខងារផ្ទាល់ត្រូវបានដំណើរការរៀងរាល់ ១០ វិនាទីទេ។ ដើម្បីធ្វើឲ្យមានប្រសិទ្ធភាពល្អជាងនេះ អ្នកអាចអនុវត្តពេលយឺត ១០ វិនាទីជា ពេលយឺតខ្លីជាច្រើន ដែលហៅ `IoTHubDeviceClient_LL_DoWork` រៀងរាល់ដង។ សូមបន្ថែមកូដខាងក្រោមមុនមុខងារ `loop`៖

    ```cpp
    void work_delay(int delay_time)
    {
        int current = 0;
        do
        {
            IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
            delay(100);
            current += 100;
        } while (current < delay_time);
    }
    ```

    កូដនេះនឹងរត់ច្រើនដង ដើម្បីហៅ `IoTHubDeviceClient_LL_DoWork` ហើយពន្លឿនដល់ ១០០ms រៀងរាល់ដង។ វានឹងធ្វើបែបនេះប៉ុន្មានដងដើម្បីពន្លឿនរហូតដល់ចំនួនពេលដែលបានផ្តល់នៅប៉ារ៉ាម៉ែត្រ `delay_time`។ នេះមានន័យថាឧបករណ៍រង់ចាំកម្រិតអតិបរមា ១០០ms ដើម្បីដំណើរការការស្នើសុំមុខងារផ្ទាល់។

1. ក្នុងមុខងារ `loop` លុបការហៅទៅ `IoTHubDeviceClient_LL_DoWork` ហើយប្តូរ `delay(10000)` ជាកូដខាងក្រោមដើម្បីហៅមុខងារថ្មីនេះ៖

    ```cpp
    work_delay(10000);
    ```

> 💁 អ្នកអាចស្វែងរកកូដនេះនៅក្នុងថត [code/wio-terminal](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/wio-terminal)។

😀 កម្មវិធីឧបករណ៍ចាប់សំណើរសំណល់ជាតិដីរបស់អ្នកត្រូវបានផ្ទៀងទៅកាន់ IoT Hub របស់អ្នកហើយ!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**ការបដិសេធ**៖  
ឯកសារនេះត្រូវបានបកប្រែក្នុងការប្រើប្រាស់សេវាកម្មបកប្រែអេไអាយ [Co-op Translator](https://github.com/Azure/co-op-translator)។ ខណៈពេលយើងខិតខំសំរាប់ភាពត្រឹមត្រូវ សូមយល់ឲ្យបានច្បាស់ថាការបកប្រែដោយស្វ័យប្រវត្តិនេះអាចមានកំហុស ឬភាពមិនត្រឹមរបស់វា។ ឯកសារដើមភាសាទីបាក់បណ្តុះត្រូវត្រូវបានគិតថាជាប្រភពដែលមានសុពលភាពត្រឹមត្រូវ។ សម្រាប់ព័ត៌មានសំខាន់ៗ ដំណើរការបកប្រែដោយមនុស្សជំនាញត្រូវបានណែនាំឲ្យប្រើ។ យើងមិនទទួលខុសត្រូវចំពោះការយល់ច្រឡំ ឬការបកស្រាយខុសៗដែលកើតឡើងពីការប្រើប្រាស់ការបកប្រែនេះឡើយ។
<!-- CO-OP TRANSLATOR DISCLAIMER END -->