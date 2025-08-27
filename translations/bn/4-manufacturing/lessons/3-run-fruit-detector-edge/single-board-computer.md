<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "50151d9f9dce2801348a93880ef16d86",
  "translation_date": "2025-08-27T10:44:07+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/single-board-computer.md",
  "language_code": "bn"
}
-->
# IoT Edge ভিত্তিক ইমেজ ক্লাসিফায়ার ব্যবহার করে একটি ছবি শ্রেণীবদ্ধ করুন - ভার্চুয়াল IoT হার্ডওয়্যার এবং রাস্পবেরি পাই

এই পাঠের অংশে, আপনি IoT Edge ডিভাইসে চলমান ইমেজ ক্লাসিফায়ার ব্যবহার করবেন।

## IoT Edge ক্লাসিফায়ার ব্যবহার করুন

IoT ডিভাইসটি IoT Edge ইমেজ ক্লাসিফায়ার ব্যবহার করার জন্য পুনঃনির্দেশিত করা যেতে পারে। ইমেজ ক্লাসিফায়ারের URL হলো `http://<IP address or name>/image`, যেখানে `<IP address or name>` এর জায়গায় IoT Edge চালানো কম্পিউটারের IP ঠিকানা বা হোস্ট নাম বসাতে হবে।

Custom Vision এর জন্য Python লাইব্রেরি শুধুমাত্র ক্লাউড-হোস্টেড মডেলের সাথে কাজ করে, IoT Edge-এ হোস্ট করা মডেলের সাথে নয়। এর মানে হলো আপনাকে REST API ব্যবহার করে ক্লাসিফায়ার কল করতে হবে।

### কাজ - IoT Edge ক্লাসিফায়ার ব্যবহার করুন

1. যদি `fruit-quality-detector` প্রকল্পটি VS Code-এ ইতিমধ্যে খোলা না থাকে, তাহলে এটি খুলুন। যদি আপনি ভার্চুয়াল IoT ডিভাইস ব্যবহার করেন, তাহলে নিশ্চিত করুন যে ভার্চুয়াল পরিবেশটি সক্রিয় রয়েছে।

1. `app.py` ফাইলটি খুলুন এবং `azure.cognitiveservices.vision.customvision.prediction` এবং `msrest.authentication` থেকে আমদানি করা স্টেটমেন্টগুলো মুছে ফেলুন।

1. ফাইলের শীর্ষে নিম্নলিখিত আমদানি যোগ করুন:

    ```python
    import requests
    ```

1. ছবিটি একটি ফাইলে সংরক্ষণ করার পর থেকে `image_file.write(image.read())` থেকে ফাইলের শেষ পর্যন্ত সমস্ত কোড মুছে ফেলুন।

1. ফাইলের শেষে নিম্নলিখিত কোড যোগ করুন:

    ```python
    prediction_url = '<URL>'
    headers = {
        'Content-Type' : 'application/octet-stream'
    }
    image.seek(0)
    response = requests.post(prediction_url, headers=headers, data=image)
    results = response.json()
    
    for prediction in results['predictions']:
        print(f'{prediction["tagName"]}:\t{prediction["probability"] * 100:.2f}%')
    ```

    `<URL>` এর জায়গায় আপনার ক্লাসিফায়ারের URL বসান।

    এই কোডটি ক্লাসিফায়ারে একটি REST POST অনুরোধ পাঠায়, যেখানে ছবিটি অনুরোধের বডি হিসেবে পাঠানো হয়। ফলাফল JSON আকারে ফিরে আসে, এবং এটি ডিকোড করে সম্ভাব্যতা প্রিন্ট করা হয়।

1. আপনার কোড চালান, আপনার ক্যামেরা কিছু ফলের দিকে নির্দেশ করে, অথবা একটি উপযুক্ত ইমেজ সেট ব্যবহার করে, অথবা যদি ভার্চুয়াল IoT হার্ডওয়্যার ব্যবহার করেন তাহলে আপনার ওয়েবক্যামে ফল দৃশ্যমান থাকে। আপনি কনসোলে আউটপুট দেখতে পাবেন:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 আপনি এই কোডটি [code-classify/pi](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/pi) অথবা [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/virtual-iot-device) ফোল্ডারে খুঁজে পেতে পারেন।

😀 আপনার ফলের গুণমান ক্লাসিফায়ার প্রোগ্রাম সফল হয়েছে!

---

**অস্বীকৃতি**:  
এই নথিটি AI অনুবাদ পরিষেবা [Co-op Translator](https://github.com/Azure/co-op-translator) ব্যবহার করে অনুবাদ করা হয়েছে। আমরা যথাসম্ভব সঠিক অনুবাদ প্রদানের চেষ্টা করি, তবে অনুগ্রহ করে মনে রাখবেন যে স্বয়ংক্রিয় অনুবাদে ত্রুটি বা অসঙ্গতি থাকতে পারে। মূল ভাষায় থাকা নথিটিকে প্রামাণিক উৎস হিসেবে বিবেচনা করা উচিত। গুরুত্বপূর্ণ তথ্যের ক্ষেত্রে, পেশাদার মানব অনুবাদ সুপারিশ করা হয়। এই অনুবাদ ব্যবহারের ফলে কোনো ভুল বোঝাবুঝি বা ভুল ব্যাখ্যা হলে আমরা তার জন্য দায়ী থাকব না।