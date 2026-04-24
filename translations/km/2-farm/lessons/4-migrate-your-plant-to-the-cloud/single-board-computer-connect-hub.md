# ភ្ជាប់ឧបករណ៍ IoT របស់អ្នកទៅមេឃ្ - សម្ភារៈ IoT Virtual និង Raspberry Pi

ក្នុងផ្នែកនេះនៃមេរៀន អ្នកនឹងភ្ជាប់ឧបករណ៍ IoT ឌីជីថលរបស់អ្នក ឬ Raspberry Pi ទៅឲ្យ IoT Hub របស់អ្នក ដើម្បីផ្ញើព័ត៌មាន telemetry និងទទួលការបញ្ជា។

## ភ្ជាប់ឧបករណ៍របស់អ្នកទៅ IoT Hub

ជំហានបន្ទាប់គឺភ្ជាប់ឧបករណ៍របស់អ្នកទៅ IoT Hub។

### ភារកិច្ច - ភ្ជាប់ទៅ IoT Hub

1. បើកថត `soil-moisture-sensor` នៅក្នុង VS Code។ ពិនិត្យឲ្យប្រាកដថាបរិនៅវេតិកនៅក្នុងterminal កំពុងដំណើរការបើអ្នកកំពុងប្រើឧបករណ៍ IoT វិចិត្រស័ព្ទ។

1. ដំឡើងបណ្ណាល័យ Pip ផ្សេងទៀត៖

    ```sh
    pip3 install azure-iot-device
    ```

    `azure-iot-device` គឺជាបណ្ណាល័យសម្រាប់ទំនាក់ទំនងជាមួយ IoT Hub របស់អ្នក។

1. បញ្ចូលការនាំចូលខាងក្រោមទៅកាន់ខាងលើនៃឯកសារ `app.py` ខាងក្រោមការនាំចូលដែលមានរួចហើយ៖

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse
    ```

    កូដនេះនាំចូល SDK សម្រាប់ទំនាក់ទំនងជាមួយ IoT Hub របស់អ្នក។

1. ដកស្រាយជួរដេក `import paho.mqtt.client as mqtt` ដោយសារតែបណ្ណាល័យនេះមិនត្រូវការ់ទៀតទេ។ ដកស្រាយកូដ MQTT ទាំងអស់ រួមមានឈ្មោះក្បាលមាតិកា ទាំងអស់នៃកូដដែលប្រើប្រាស់ `mqtt_client` និង `handle_command`។ ទុកឲ្យមានតែវគ្គលូប `while True:` ប៉ុណ្ណោះ ដកបន្ទាត់ `mqtt_client.publish` ចេញពីវគ្គនេះ។

1. បន្ថែមកូដខាងក្រោមក្រោមបន្ទាត់នាំចូល៖

    ```python
    connection_string = "<connection string>"
    ```

    ជំនួស `<connection string>` ជាមួយខ្សែសន្ទស្សន៏ដែលអ្នកបានទទួលសម្រាប់ឧបករណ៍នៅមុននេះក្នុងមេរៀន។

    > 💁 នេះមិនមែនជាប្រព័ន្ធល្អបំផុតទេ។ ខ្សែសន្ទស្សន៏គួរមិនត្រូវបានរក្សាទុកក្នុងកូដប្រភព ពីព្រោះវាអាចត្រូវបានត្រួតមើលដោយអ្នកណាមួយបាន។ យើងធ្វើបែបនេះដើម្បីស្រួល សូមប្រើអារម្មណ៍បរិស្ថានឬឧបករណ៍ដូចជា [`python-dotenv`](https://pypi.org/project/python-dotenv/)។ អ្នកនឹងរៀនបន្ថែមអំពីវានៅក្នុងមេរៀនក្រោយ។

1. ខាងក្រោមកូដនេះ បន្ថែមខាងក្រោមដើម្បីបង្កើតវត្ថុ device client ដែលអាចទំនាក់ទំនងជាមួយ IoT Hub ហើយភ្ជាប់វា៖

    ```python
    device_client = IoTHubDeviceClient.create_from_connection_string(connection_string)

    print('Connecting')
    device_client.connect()
    print('Connected')
    ```

1. រត់កូដនេះ។ អ្នកនឹងឃើញឧបករណ៍របស់អ្នកភ្ជាប់បាន។

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Connecting
    Connected
    Soil moisture: 379
    ```

## ផ្ញើ telemetry

ឥឡូវនេះឧបករណ៍របស់អ្នកបានភ្ជាប់ហើយ អ្នកអាចផ្ញើ telemetry ទៅ IoT Hub ជំនួសឲ្យ MQTT broker។

### ភារកិច្ច - ផ្ញើ telemetry

1. បន្ថែមកូដខាងក្រោមនៅក្នុងវគ្គ `while True` មុនពេលរាត្រីងliegen:

    ```python
    message = Message(json.dumps({ 'soil_moisture': soil_moisture }))
    device_client.send_message(message)
    ```

    កូដនេះបង្កើតសារ IoT Hub `Message` ដែលមានការអានសំណើមខ្សោយដីជា string JSON ហើយបញ្ជូនវាទៅ IoT Hub ជាសារឧបករណ៍ទៅមេឃ្។

## គ្រប់គ្រងបញ្ជា

ឧបករណ៍របស់អ្នកត្រូវការគ្រប់គ្រងបញ្ជាជាប់ពីកូដម៉ាស៊ីនមេសម្រាប់គ្រប់គ្រង relay។ នេះត្រូវបានផ្ញើជារបទបញ្ជាត្រឡប់ដោយបន្ទាត់។

## ភារកិច្ច - គ្រប់គ្រងបញ្ជាត្រឡប់ដោយបន្ទាត់

1. បន្ថែមកូដខាងក្រោមមុនវគ្គ `while True`៖

    ```python
    def handle_method_request(request):
        print("Direct method received - ", request.name)
    
        if request.name == "relay_on":
            relay.on()
        elif request.name == "relay_off":
            relay.off()    
    ```

    នេះកំណត់កិច្ចការមួយ `handle_method_request` ដែលនឹងត្រូវហៅពេលដែលមានការraw direct method ត្រូវបានហៅដោយ IoT Hub។ direct method នីមួយៗមានឈ្មោះ ហើយកូដនេះរំពឹងថាមាន method ខាងក្រោម `relay_on` ដើម្បីបើក relay និង `relay_off` ដើម្បីបិទ relay។

    > 💁 វាក៏អាចអនុវត្តក្នុង direct method តែមួយបានផង ដោយផ្ញើស្ថានភាពដែលចង់បានរបស់ relay ក្នុង payload ដែលអាចផ្ញើជាមួយការស្នើសុំ method ហើយអាចទទួលបានពីវត្ថុ `request`។

1. direct methods ត្រូវការឆ្លើយតប ឲ្យអោយកូដហៅដឹងថាត្រូវបានដំណើរការហើយ។ បន្ថែមកូដខាងក្រោមនៅចុង `handle_method_request` ដើម្បីបង្កើតការឆ្លើយតបសម្រាប់ស្នើសុំ៖

    ```python
    method_response = MethodResponse.create_from_method_request(request, 200)
    device_client.send_method_response(method_response)
    ```

    កូដនេះផ្ញើការឆ្លើយតបទៅសំណើ direct method ជាមួយកូដ HTTP 200 ហើយផ្ញើវាលើវិញទៅ IoT Hub។

1. បន្ថែមកូដខាងក្រោមក្រោមកំណត់មុខងារ​នេះ៖

    ```python
    device_client.on_method_request_received = handle_method_request
    ```

    កូដនេះប្រាប់ឲ្យ IoT Hub client ហៅមុខងារ `handle_method_request` នៅពេលដែល direct method ត្រូវបានហៅ។

> 💁 អ្នកអាចស្វែងរកកូដនេះនៅក្នុងថត [code/pi](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/pi) ឬ [code/virtual-device](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/virtual-device)។

😀 ព្រីក្រោមសំណើមខ្សោយដីរបស់អ្នកបានភ្ជាប់ទៅ IoT Hub របស់អ្នកហើយ!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**ការបដិសេធ**៖  
ឯកសារនេះត្រូវបានបកប្រែដោយប្រើសេវាកម្មបកប្រែ AI [Co-op Translator](https://github.com/Azure/co-op-translator)។ ខណៈពេលដែលយើងខិតខំសំរាប់ភាពជាប់ចិត្ត ក៏សូមយល់ដឹងថាការបកប្រែដោយស្វ័យប្រវត្តិនោះអាចមានកំហុស ឬការមិនត្រឹមត្រូវ។ ឯកសារដើមនៅភាសាតិចត្រូវបានគេចាត់ទុកជាផ្លូវការជាចម្បង។ សំរាប់ព័ត៌មានសំខាន់ហើយការបកប្រែដោយមនុស្សវិជ្ជាជីវៈគួរត្រូវបានផ្តល់អាទិភាព។ យើងមិនទទួលខុសត្រូវចំពោះការយល់ច្រឡំ ឬការបកស្រាយខុសដែលកើតមានពីការប្រើប្រាស់ការបកប្រែនេះឡើយ។
<!-- CO-OP TRANSLATOR DISCLAIMER END -->