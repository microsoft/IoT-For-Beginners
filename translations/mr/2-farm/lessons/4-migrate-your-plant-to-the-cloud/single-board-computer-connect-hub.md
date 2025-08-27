<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3ac42e284a7222c0e83d2d43231a364f",
  "translation_date": "2025-08-27T12:02:39+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/single-board-computer-connect-hub.md",
  "language_code": "mr"
}
-->
# आपले IoT डिव्हाइस क्लाउडशी जोडा - व्हर्च्युअल IoT हार्डवेअर आणि रास्पबेरी पाय

या धड्याच्या या भागात, आपण आपले व्हर्च्युअल IoT डिव्हाइस किंवा रास्पबेरी पाय आपल्या IoT हबशी जोडाल, टेलिमेट्री पाठवण्यासाठी आणि आदेश प्राप्त करण्यासाठी.

## आपले डिव्हाइस IoT हबशी जोडा

पुढील पाऊल म्हणजे आपले डिव्हाइस IoT हबशी जोडणे.

### कार्य - IoT हबशी कनेक्ट करा

1. VS कोडमध्ये `soil-moisture-sensor` फोल्डर उघडा. जर आपण व्हर्च्युअल IoT डिव्हाइस वापरत असाल, तर टर्मिनलमध्ये व्हर्च्युअल वातावरण चालू असल्याची खात्री करा.

1. काही अतिरिक्त Pip पॅकेजेस इन्स्टॉल करा:

    ```sh
    pip3 install azure-iot-device
    ```

    `azure-iot-device` हे आपल्याला IoT हबशी संवाद साधण्यासाठी लागणारे लायब्ररी आहे.

1. खालील इम्पोर्ट्स `app.py` फाईलच्या शीर्षस्थानी, आधीच्या इम्पोर्ट्सच्या खाली जोडा:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse
    ```

    हा कोड IoT हबशी संवाद साधण्यासाठी आवश्यक SDK इम्पोर्ट करतो.

1. `import paho.mqtt.client as mqtt` ही ओळ काढून टाका कारण ही लायब्ररी आता आवश्यक नाही. MQTT कोड, टॉपिक नावे, `mqtt_client` वापरणारा सर्व कोड आणि `handle_command` काढून टाका. `while True:` लूप ठेवा, फक्त या लूपमधील `mqtt_client.publish` ओळ काढून टाका.

1. इम्पोर्ट स्टेटमेंट्सच्या खालील कोड जोडा:

    ```python
    connection_string = "<connection string>"
    ```

    `<connection string>` च्या जागी या धड्यात आधी मिळवलेली डिव्हाइस कनेक्शन स्ट्रिंग ठेवा.

    > 💁 हे सर्वोत्तम पद्धत नाही. कनेक्शन स्ट्रिंग्स कधीही सोर्स कोडमध्ये साठवू नयेत, कारण ते सोर्स कोड कंट्रोलमध्ये चेक इन होऊ शकतात आणि कोणालाही सापडू शकतात. येथे आपण सोपेपणासाठी असे करत आहोत. आदर्शतः, आपण पर्यावरणीय व्हेरिएबल्स आणि [`python-dotenv`](https://pypi.org/project/python-dotenv/) सारख्या साधनांचा वापर करावा. आपण याबद्दल पुढील धड्यात अधिक शिकाल.

1. या कोडखाली, IoT हबशी संवाद साधण्यासाठी डिव्हाइस क्लायंट ऑब्जेक्ट तयार करण्यासाठी आणि त्याला कनेक्ट करण्यासाठी खालील कोड जोडा:

    ```python
    device_client = IoTHubDeviceClient.create_from_connection_string(connection_string)

    print('Connecting')
    device_client.connect()
    print('Connected')
    ```

1. हा कोड चालवा. आपले डिव्हाइस कनेक्ट होईल.

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Connecting
    Connected
    Soil moisture: 379
    ```

## टेलिमेट्री पाठवा

आता आपले डिव्हाइस कनेक्ट झाले आहे, आपण MQTT ब्रोकर्सऐवजी IoT हबला टेलिमेट्री पाठवू शकता.

### कार्य - टेलिमेट्री पाठवा

1. `while True` लूपच्या आत, `sleep` च्या आधी खालील कोड जोडा:

    ```python
    message = Message(json.dumps({ 'soil_moisture': soil_moisture }))
    device_client.send_message(message)
    ```

    हा कोड IoT हबसाठी JSON स्ट्रिंग स्वरूपात मातीतील ओलसरतेचे वाचन असलेला `Message` तयार करतो आणि डिव्हाइस-टू-क्लाउड संदेश म्हणून IoT हबला पाठवतो.

## आदेश हाताळा

आपल्या डिव्हाइसला रिले नियंत्रित करण्यासाठी सर्व्हर कोडकडून आदेश हाताळण्याची आवश्यकता आहे. हे थेट पद्धतीच्या विनंतीद्वारे पाठवले जाते.

## कार्य - थेट पद्धतीची विनंती हाताळा

1. `while True` लूपच्या आधी खालील कोड जोडा:

    ```python
    def handle_method_request(request):
        print("Direct method received - ", request.name)
    
        if request.name == "relay_on":
            relay.on()
        elif request.name == "relay_off":
            relay.off()    
    ```

    हा कोड `handle_method_request` नावाची पद्धत परिभाषित करतो, जी IoT हबद्वारे थेट पद्धत कॉल केल्यावर कॉल केली जाईल. प्रत्येक थेट पद्धतीला एक नाव असते, आणि हा कोड `relay_on` नावाच्या पद्धतीची अपेक्षा करतो रिले चालू करण्यासाठी, आणि `relay_off` रिले बंद करण्यासाठी.

    > 💁 हे एका थेट पद्धतीच्या विनंतीमध्ये देखील अंमलात आणले जाऊ शकते, रिलेची इच्छित स्थिती पेलोडमध्ये पास करून, जी पद्धतीच्या विनंतीसह पास केली जाऊ शकते आणि `request` ऑब्जेक्टमधून उपलब्ध होऊ शकते.

1. थेट पद्धतींना कॉलिंग कोडला सांगण्यासाठी प्रतिसादाची आवश्यकता असते की त्यांना हाताळले गेले आहे. `handle_method_request` फंक्शनच्या शेवटी खालील कोड जोडा:

    ```python
    method_response = MethodResponse.create_from_method_request(request, 200)
    device_client.send_method_response(method_response)
    ```

    हा कोड थेट पद्धतीच्या विनंतीला HTTP स्थिती कोड 200 सह प्रतिसाद पाठवतो आणि IoT हबला परत पाठवतो.

1. या फंक्शनच्या परिभाषेनंतर खालील कोड जोडा:

    ```python
    device_client.on_method_request_received = handle_method_request
    ```

    हा कोड IoT हब क्लायंटला सांगतो की थेट पद्धत कॉल केल्यावर `handle_method_request` फंक्शन कॉल करावे.

> 💁 हा कोड [code/pi](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/pi) किंवा [code/virtual-device](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/virtual-device) फोल्डरमध्ये सापडू शकतो.

😀 आपला मातीतील ओलसरता सेन्सर प्रोग्राम IoT हबशी कनेक्ट झाला आहे!

---

**अस्वीकरण**:  
हा दस्तऐवज AI भाषांतर सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) वापरून भाषांतरित करण्यात आला आहे. आम्ही अचूकतेसाठी प्रयत्नशील असलो तरी कृपया लक्षात ठेवा की स्वयंचलित भाषांतरांमध्ये त्रुटी किंवा अचूकतेचा अभाव असू शकतो. मूळ भाषेतील दस्तऐवज हा अधिकृत स्रोत मानला जावा. महत्त्वाच्या माहितीसाठी व्यावसायिक मानवी भाषांतराची शिफारस केली जाते. या भाषांतराचा वापर करून निर्माण होणाऱ्या कोणत्याही गैरसमज किंवा चुकीच्या अर्थासाठी आम्ही जबाबदार राहणार नाही.