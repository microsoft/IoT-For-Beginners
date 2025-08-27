<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3ac42e284a7222c0e83d2d43231a364f",
  "translation_date": "2025-08-27T12:03:00+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/single-board-computer-connect-hub.md",
  "language_code": "ne"
}
-->
# आफ्नो IoT उपकरणलाई क्लाउडसँग जडान गर्नुहोस् - भर्चुअल IoT हार्डवेयर र Raspberry Pi

यस पाठको यस भागमा, तपाईं आफ्नो भर्चुअल IoT उपकरण वा Raspberry Pi लाई IoT Hubसँग जडान गर्नुहुनेछ, टेलिमेट्री पठाउन र आदेशहरू प्राप्त गर्न।

## आफ्नो उपकरणलाई IoT Hubसँग जडान गर्नुहोस्

अर्को चरण भनेको आफ्नो उपकरणलाई IoT Hubसँग जडान गर्नु हो।

### कार्य - IoT Hubसँग जडान गर्नुहोस्

1. VS Code मा `soil-moisture-sensor` फोल्डर खोल्नुहोस्। यदि तपाईं भर्चुअल IoT उपकरण प्रयोग गर्दै हुनुहुन्छ भने टर्मिनलमा भर्चुअल वातावरण चलिरहेको छ भनेर सुनिश्चित गर्नुहोस्।

1. केही अतिरिक्त Pip प्याकेजहरू स्थापना गर्नुहोस्:

    ```sh
    pip3 install azure-iot-device
    ```

    `azure-iot-device` तपाईंको IoT Hubसँग संवाद गर्नको लागि पुस्तकालय हो।

1. `app.py` फाइलको माथि, पहिले नै भएका आयातहरू तल निम्न आयातहरू थप्नुहोस्:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse
    ```

    यो कोडले तपाईंको IoT Hubसँग संवाद गर्नको लागि SDK आयात गर्दछ।

1. `import paho.mqtt.client as mqtt` लाइन हटाउनुहोस् किनकि यो पुस्तकालय अब आवश्यक छैन। MQTT कोड, टपिक नामहरू, `mqtt_client` प्रयोग गर्ने सबै कोड र `handle_command` हटाउनुहोस्। `while True:` लूप राख्नुहोस्, तर यस लूपबाट `mqtt_client.publish` लाइन हटाउनुहोस्।

1. आयात कथनहरू तल निम्न कोड थप्नुहोस्:

    ```python
    connection_string = "<connection string>"
    ```

    `<connection string>` लाई यस पाठको पहिले तपाईंले उपकरणको लागि प्राप्त गरेको जडान स्ट्रिङले प्रतिस्थापन गर्नुहोस्।

    > 💁 यो उत्तम अभ्यास होइन। जडान स्ट्रिङहरू कहिल्यै स्रोत कोडमा भण्डारण गर्नु हुँदैन, किनकि यसलाई स्रोत कोड नियन्त्रणमा जाँच गर्न सकिन्छ र जो कोहीले फेला पार्न सक्छ। हामी यहाँ सरलताको लागि यो गर्दैछौं। आदर्श रूपमा तपाईंले वातावरण चर र [`python-dotenv`](https://pypi.org/project/python-dotenv/) जस्ता उपकरण प्रयोग गर्नुपर्छ। तपाईं यसबारे आगामी पाठमा थप जान्नुहुनेछ।

1. यस कोडको तल, IoT Hubसँग संवाद गर्न सक्ने उपकरण क्लाइन्ट वस्तु सिर्जना गर्न र यसलाई जडान गर्न निम्न कोड थप्नुहोस्:

    ```python
    device_client = IoTHubDeviceClient.create_from_connection_string(connection_string)

    print('Connecting')
    device_client.connect()
    print('Connected')
    ```

1. यो कोड चलाउनुहोस्। तपाईंको उपकरण जडान भएको देख्नुहुनेछ।

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Connecting
    Connected
    Soil moisture: 379
    ```

## टेलिमेट्री पठाउनुहोस्

अब तपाईंको उपकरण जडान भइसकेको छ, तपाईं MQTT ब्रोकरको सट्टा IoT Hubमा टेलिमेट्री पठाउन सक्नुहुन्छ।

### कार्य - टेलिमेट्री पठाउनुहोस्

1. `while True` लूप भित्र, सुत्नुअघि निम्न कोड थप्नुहोस्:

    ```python
    message = Message(json.dumps({ 'soil_moisture': soil_moisture }))
    device_client.send_message(message)
    ```

    यो कोडले माटोको चिस्यानको रिडिङलाई JSON स्ट्रिङको रूपमा समावेश गर्ने IoT Hub `Message` सिर्जना गर्दछ, त्यसपछि यसलाई उपकरणबाट क्लाउड सन्देशको रूपमा IoT Hubमा पठाउँछ।

## आदेशहरू ह्यान्डल गर्नुहोस्

तपाईंको उपकरणले रिले नियन्त्रण गर्न सर्वर कोडबाट आदेश ह्यान्डल गर्न आवश्यक छ। यो प्रत्यक्ष विधि अनुरोधको रूपमा पठाइन्छ।

## कार्य - प्रत्यक्ष विधि अनुरोध ह्यान्डल गर्नुहोस्

1. `while True` लूप अघि निम्न कोड थप्नुहोस्:

    ```python
    def handle_method_request(request):
        print("Direct method received - ", request.name)
    
        if request.name == "relay_on":
            relay.on()
        elif request.name == "relay_off":
            relay.off()    
    ```

    यो `handle_method_request` नामको विधि परिभाषित गर्दछ, जुन IoT Hubद्वारा प्रत्यक्ष विधि बोलाउँदा कल गरिनेछ। प्रत्येक प्रत्यक्ष विधिको नाम हुन्छ, र यो कोडले रिले अन गर्न `relay_on` र रिले अफ गर्न `relay_off` नामको विधि अपेक्षा गर्दछ।

    > 💁 यो एकल प्रत्यक्ष विधि अनुरोधमा पनि कार्यान्वयन गर्न सकिन्छ, रिलेको इच्छित अवस्था अनुरोधको साथ पठाउन सकिने पेलोडमा पास गरेर, जुन `request` वस्तुबाट उपलब्ध हुन्छ।

1. प्रत्यक्ष विधिले कल गर्ने कोडलाई यो ह्यान्डल गरिएको छ भनेर बताउन प्रतिक्रिया आवश्यक छ। `handle_method_request` कार्यको अन्त्यमा निम्न कोड थप्नुहोस्:

    ```python
    method_response = MethodResponse.create_from_method_request(request, 200)
    device_client.send_method_response(method_response)
    ```

    यो कोडले प्रत्यक्ष विधि अनुरोधलाई HTTP स्थिति कोड 200 सहित प्रतिक्रिया पठाउँछ, र यसलाई IoT Hubमा फर्काउँछ।

1. यो कार्य परिभाषाको तल निम्न कोड थप्नुहोस्:

    ```python
    device_client.on_method_request_received = handle_method_request
    ```

    यो कोडले IoT Hub क्लाइन्टलाई प्रत्यक्ष विधि बोलाउँदा `handle_method_request` कार्य कल गर्न भन्छ।

> 💁 तपाईं यो कोड [code/pi](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/pi) वा [code/virtual-device](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/virtual-device) फोल्डरमा फेला पार्न सक्नुहुन्छ।

😀 तपाईंको माटोको चिस्यान सेन्सर कार्यक्रम IoT Hubसँग जडान भएको छ!

---

**अस्वीकरण**:  
यो दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) प्रयोग गरेर अनुवाद गरिएको छ। हामी शुद्धताको लागि प्रयास गर्छौं, तर कृपया ध्यान दिनुहोस् कि स्वचालित अनुवादमा त्रुटिहरू वा अशुद्धताहरू हुन सक्छ। यसको मूल भाषा मा रहेको मूल दस्तावेज़लाई आधिकारिक स्रोत मानिनुपर्छ। महत्वपूर्ण जानकारीको लागि, व्यावसायिक मानव अनुवाद सिफारिस गरिन्छ। यस अनुवादको प्रयोगबाट उत्पन्न हुने कुनै पनि गलतफहमी वा गलत व्याख्याको लागि हामी जिम्मेवार हुने छैनौं।