<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3ac42e284a7222c0e83d2d43231a364f",
  "translation_date": "2025-08-27T12:02:19+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/single-board-computer-connect-hub.md",
  "language_code": "bn"
}
-->
# আপনার IoT ডিভাইসকে ক্লাউডের সাথে সংযুক্ত করুন - ভার্চুয়াল IoT হার্ডওয়্যার এবং Raspberry Pi

এই পাঠের এই অংশে, আপনি আপনার ভার্চুয়াল IoT ডিভাইস বা Raspberry Pi-কে IoT Hub-এর সাথে সংযুক্ত করবেন, টেলিমেট্রি পাঠানোর এবং কমান্ড গ্রহণ করার জন্য।

## আপনার ডিভাইসকে IoT Hub-এর সাথে সংযুক্ত করুন

পরবর্তী ধাপটি হলো আপনার ডিভাইসকে IoT Hub-এর সাথে সংযুক্ত করা।

### কাজ - IoT Hub-এর সাথে সংযুক্ত করুন

1. VS Code-এ `soil-moisture-sensor` ফোল্ডারটি খুলুন। যদি আপনি ভার্চুয়াল IoT ডিভাইস ব্যবহার করেন, তবে নিশ্চিত করুন যে টার্মিনালে ভার্চুয়াল পরিবেশটি চালু রয়েছে।

1. কিছু অতিরিক্ত Pip প্যাকেজ ইনস্টল করুন:

    ```sh
    pip3 install azure-iot-device
    ```

    `azure-iot-device` হলো একটি লাইব্রেরি যা আপনার IoT Hub-এর সাথে যোগাযোগ করতে ব্যবহৃত হয়।

1. `app.py` ফাইলের শীর্ষে, বিদ্যমান ইমপোর্টগুলির নিচে নিম্নলিখিত ইমপোর্টগুলি যোগ করুন:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse
    ```

    এই কোডটি IoT Hub-এর সাথে যোগাযোগ করার জন্য SDK ইমপোর্ট করে।

1. `import paho.mqtt.client as mqtt` লাইনটি সরিয়ে ফেলুন কারণ এই লাইব্রেরি আর প্রয়োজন নেই। সমস্ত MQTT কোড, যার মধ্যে টপিক নাম, `mqtt_client` ব্যবহার করা কোড এবং `handle_command` অন্তর্ভুক্ত, সরিয়ে ফেলুন। `while True:` লুপটি রাখুন, শুধু এই লুপের `mqtt_client.publish` লাইনটি মুছে ফেলুন।

1. ইমপোর্ট স্টেটমেন্টগুলির নিচে নিম্নলিখিত কোড যোগ করুন:

    ```python
    connection_string = "<connection string>"
    ```

    `<connection string>`-এর জায়গায় এই পাঠের আগে ডিভাইসের জন্য প্রাপ্ত সংযোগ স্ট্রিংটি প্রতিস্থাপন করুন।

    > 💁 এটি সেরা পদ্ধতি নয়। সংযোগ স্ট্রিং কখনোই সোর্স কোডে সংরক্ষণ করা উচিত নয়, কারণ এটি সোর্স কোড কন্ট্রোলে চেক ইন করা যেতে পারে এবং যে কেউ এটি খুঁজে পেতে পারে। আমরা এখানে সরলতার জন্য এটি করছি। আদর্শভাবে, আপনি পরিবেশ ভেরিয়েবল এবং [`python-dotenv`](https://pypi.org/project/python-dotenv/) এর মতো একটি টুল ব্যবহার করবেন। আপনি এটি সম্পর্কে একটি আসন্ন পাঠে আরও শিখবেন।

1. এই কোডের নিচে, IoT Hub-এর সাথে যোগাযোগ করতে পারে এমন একটি ডিভাইস ক্লায়েন্ট অবজেক্ট তৈরি করতে এবং এটি সংযুক্ত করতে নিম্নলিখিত কোড যোগ করুন:

    ```python
    device_client = IoTHubDeviceClient.create_from_connection_string(connection_string)

    print('Connecting')
    device_client.connect()
    print('Connected')
    ```

1. এই কোডটি চালান। আপনি দেখতে পাবেন আপনার ডিভাইস সংযুক্ত হয়েছে।

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Connecting
    Connected
    Soil moisture: 379
    ```

## টেলিমেট্রি পাঠান

এখন আপনার ডিভাইস সংযুক্ত হয়েছে, আপনি MQTT ব্রোকারের পরিবর্তে IoT Hub-এ টেলিমেট্রি পাঠাতে পারেন।

### কাজ - টেলিমেট্রি পাঠান

1. `while True` লুপের ভিতরে, স্লিপের ঠিক আগে নিম্নলিখিত কোড যোগ করুন:

    ```python
    message = Message(json.dumps({ 'soil_moisture': soil_moisture }))
    device_client.send_message(message)
    ```

    এই কোডটি একটি IoT Hub `Message` তৈরি করে যা মাটির আর্দ্রতার রিডিংকে JSON স্ট্রিং হিসেবে ধারণ করে, তারপর এটি IoT Hub-এ ডিভাইস থেকে ক্লাউড মেসেজ হিসেবে পাঠায়।

## কমান্ড পরিচালনা করুন

আপনার ডিভাইসকে সার্ভার কোড থেকে একটি কমান্ড পরিচালনা করতে হবে যা রিলে নিয়ন্ত্রণ করে। এটি একটি ডাইরেক্ট মেথড রিকোয়েস্ট হিসেবে পাঠানো হয়।

## কাজ - একটি ডাইরেক্ট মেথড রিকোয়েস্ট পরিচালনা করুন

1. `while True` লুপের আগে নিম্নলিখিত কোড যোগ করুন:

    ```python
    def handle_method_request(request):
        print("Direct method received - ", request.name)
    
        if request.name == "relay_on":
            relay.on()
        elif request.name == "relay_off":
            relay.off()    
    ```

    এটি একটি মেথড, `handle_method_request`, সংজ্ঞায়িত করে যা IoT Hub দ্বারা একটি ডাইরেক্ট মেথড কল করা হলে ডাকা হবে। প্রতিটি ডাইরেক্ট মেথডের একটি নাম থাকে, এবং এই কোডটি `relay_on` নামক একটি মেথড আশা করে রিলে চালু করতে, এবং `relay_off` নামক একটি মেথড আশা করে রিলে বন্ধ করতে।

    > 💁 এটি একটি একক ডাইরেক্ট মেথড রিকোয়েস্টে বাস্তবায়িত হতে পারে, যেখানে রিলের কাঙ্ক্ষিত অবস্থাটি একটি পে-লোডে পাস করা হয় যা মেথড রিকোয়েস্টের সাথে পাস করা যায় এবং `request` অবজেক্ট থেকে পাওয়া যায়।

1. ডাইরেক্ট মেথডগুলির একটি রেসপন্স প্রয়োজন যা কলিং কোডকে জানায় যে এটি পরিচালিত হয়েছে। `handle_method_request` ফাংশনের শেষে নিম্নলিখিত কোড যোগ করুন যা রিকোয়েস্টের জন্য একটি রেসপন্স তৈরি করে:

    ```python
    method_response = MethodResponse.create_from_method_request(request, 200)
    device_client.send_method_response(method_response)
    ```

    এই কোডটি একটি HTTP স্ট্যাটাস কোড 200 সহ ডাইরেক্ট মেথড রিকোয়েস্টের জন্য একটি রেসপন্স পাঠায় এবং এটি IoT Hub-এ ফেরত পাঠায়।

1. এই ফাংশন সংজ্ঞার নিচে নিম্নলিখিত কোড যোগ করুন:

    ```python
    device_client.on_method_request_received = handle_method_request
    ```

    এই কোডটি IoT Hub ক্লায়েন্টকে বলে যে একটি ডাইরেক্ট মেথড কল করা হলে `handle_method_request` ফাংশনটি কল করতে।

> 💁 আপনি এই কোডটি [code/pi](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/pi) বা [code/virtual-device](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/virtual-device) ফোল্ডারে খুঁজে পেতে পারেন।

😀 আপনার মাটির আর্দ্রতা সেন্সর প্রোগ্রামটি IoT Hub-এর সাথে সংযুক্ত হয়েছে!

---

**অস্বীকৃতি**:  
এই নথিটি AI অনুবাদ পরিষেবা [Co-op Translator](https://github.com/Azure/co-op-translator) ব্যবহার করে অনুবাদ করা হয়েছে। আমরা যথাসাধ্য সঠিকতা নিশ্চিত করার চেষ্টা করি, তবে অনুগ্রহ করে মনে রাখবেন যে স্বয়ংক্রিয় অনুবাদে ত্রুটি বা অসঙ্গতি থাকতে পারে। মূল ভাষায় থাকা নথিটিকে প্রামাণিক উৎস হিসেবে বিবেচনা করা উচিত। গুরুত্বপূর্ণ তথ্যের জন্য, পেশাদার মানব অনুবাদ সুপারিশ করা হয়। এই অনুবাদ ব্যবহারের ফলে কোনো ভুল বোঝাবুঝি বা ভুল ব্যাখ্যা হলে আমরা দায়বদ্ধ থাকব না।