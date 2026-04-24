# একটি ছবি শ্রেণীবদ্ধ করুন - ভার্চুয়াল IoT হার্ডওয়্যার এবং রাস্পবেরি পাই

এই পাঠের এই অংশে, আপনি ক্যামেরা দ্বারা ধারণ করা ছবিটি শ্রেণীবদ্ধ করার জন্য Custom Vision পরিষেবাতে পাঠাবেন।

## Custom Vision-এ ছবি পাঠান

Custom Vision পরিষেবার একটি পাইথন SDK রয়েছে যা আপনি ছবি শ্রেণীবদ্ধ করতে ব্যবহার করতে পারেন।

### কাজ - Custom Vision-এ ছবি পাঠান

1. VS Code-এ `fruit-quality-detector` ফোল্ডারটি খুলুন। যদি আপনি একটি ভার্চুয়াল IoT ডিভাইস ব্যবহার করেন, নিশ্চিত করুন যে টার্মিনালে ভার্চুয়াল এনভায়রনমেন্টটি চালু রয়েছে।

1. Custom Vision-এ ছবি পাঠানোর জন্য পাইথন SDK একটি Pip প্যাকেজ হিসেবে উপলব্ধ। এটি নিম্নলিখিত কমান্ড দিয়ে ইনস্টল করুন:

    ```sh
    pip3 install azure-cognitiveservices-vision-customvision
    ```

1. `app.py` ফাইলের শীর্ষে নিম্নলিখিত ইমপোর্ট স্টেটমেন্টগুলো যোগ করুন:

    ```python
    from msrest.authentication import ApiKeyCredentials
    from azure.cognitiveservices.vision.customvision.prediction import CustomVisionPredictionClient
    ```

    এটি Custom Vision লাইব্রেরি থেকে কিছু মডিউল নিয়ে আসে, একটি প্রেডিকশন কী দিয়ে প্রমাণীকরণের জন্য এবং একটি প্রেডিকশন ক্লায়েন্ট ক্লাস সরবরাহ করার জন্য যা Custom Vision-এ কল করতে পারে।

1. ফাইলের শেষে নিম্নলিখিত কোড যোগ করুন:

    ```python
    prediction_url = '<prediction_url>'
    prediction_key = '<prediction key>'
    ```

    `<prediction_url>`-এর জায়গায় এই পাঠের আগের অংশে *Prediction URL* ডায়ালগ থেকে কপি করা URL বসান। `<prediction key>`-এর জায়গায় একই ডায়ালগ থেকে কপি করা প্রেডিকশন কী বসান।

1. *Prediction URL* ডায়ালগ দ্বারা সরবরাহিত প্রেডিকশন URL সরাসরি REST এন্ডপয়েন্ট কল করার জন্য ডিজাইন করা হয়েছে। পাইথন SDK URL-এর বিভিন্ন অংশ বিভিন্ন স্থানে ব্যবহার করে। এই URL-টি প্রয়োজনীয় অংশে ভাগ করার জন্য নিম্নলিখিত কোড যোগ করুন:

    ```python
    parts = prediction_url.split('/')
    endpoint = 'https://' + parts[2]
    project_id = parts[6]
    iteration_name = parts[9]
    ```

    এটি URL-টি ভাগ করে, `https://<location>.api.cognitive.microsoft.com` এন্ডপয়েন্ট, প্রজেক্ট আইডি এবং প্রকাশিত ইটারেশনের নাম বের করে।

1. প্রেডিকশন করার জন্য একটি প্রেডিক্টর অবজেক্ট তৈরি করুন নিম্নলিখিত কোড দিয়ে:

    ```python
    prediction_credentials = ApiKeyCredentials(in_headers={"Prediction-key": prediction_key})
    predictor = CustomVisionPredictionClient(endpoint, prediction_credentials)
    ```

    `prediction_credentials` প্রেডিকশন কী মোড়ায়। এগুলো পরে এন্ডপয়েন্ট নির্দেশ করে একটি প্রেডিকশন ক্লায়েন্ট অবজেক্ট তৈরি করতে ব্যবহৃত হয়।

1. নিম্নলিখিত কোড ব্যবহার করে ছবিটি Custom Vision-এ পাঠান:

    ```python
    image.seek(0)
    results = predictor.classify_image(project_id, iteration_name, image)
    ```

    এটি ছবিটিকে শুরুতে রিওয়াইন্ড করে, তারপর এটি প্রেডিকশন ক্লায়েন্টে পাঠায়।

1. অবশেষে, নিম্নলিখিত কোড দিয়ে ফলাফল দেখান:

    ```python
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    এটি সমস্ত প্রেডিকশনগুলোর মধ্য দিয়ে লুপ করবে এবং সেগুলো টার্মিনালে দেখাবে। ফেরত পাওয়া সম্ভাবনাগুলো 0-1 এর মধ্যে ভাসমান বিন্দু সংখ্যা, যেখানে 0 মানে 0% সম্ভাবনা এবং 1 মানে 100% সম্ভাবনা।

    > 💁 ইমেজ ক্লাসিফায়ারগুলো ব্যবহৃত সমস্ত ট্যাগের জন্য শতাংশ ফেরত দেবে। প্রতিটি ট্যাগের একটি সম্ভাবনা থাকবে যে ছবিটি সেই ট্যাগের সাথে মেলে।

1. আপনার কোড চালান, ক্যামেরা ফলের দিকে নির্দেশ করে রাখুন, অথবা একটি উপযুক্ত ছবির সেট ব্যবহার করুন, অথবা ভার্চুয়াল IoT হার্ডওয়্যার ব্যবহার করলে ওয়েবক্যামে দৃশ্যমান ফল। আপনি কনসোলে আউটপুট দেখতে পাবেন:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

    আপনি তোলা ছবিটি দেখতে পারবেন এবং এই মানগুলো Custom Vision-এর **Predictions** ট্যাবে দেখতে পারবেন।

    ![Custom Vision-এ একটি কলা, 56.8% পাকা এবং 43.1% কাঁচা হিসেবে প্রেডিক্ট করা হয়েছে](../../../../../translated_images/bn/custom-vision-banana-prediction.30cdff4e1d72db5d.webp)

> 💁 আপনি এই কোডটি [code-classify/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/pi) অথবা [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/virtual-iot-device) ফোল্ডারে খুঁজে পেতে পারেন।

😀 আপনার ফলের গুণমান শ্রেণীবদ্ধকরণ প্রোগ্রামটি সফল হয়েছে!

---

**অস্বীকৃতি**:  
এই নথিটি AI অনুবাদ পরিষেবা [Co-op Translator](https://github.com/Azure/co-op-translator) ব্যবহার করে অনুবাদ করা হয়েছে। আমরা যথাসাধ্য সঠিকতা নিশ্চিত করার চেষ্টা করি, তবে অনুগ্রহ করে মনে রাখবেন যে স্বয়ংক্রিয় অনুবাদে ত্রুটি বা অসঙ্গতি থাকতে পারে। মূল ভাষায় থাকা নথিটিকে প্রামাণিক উৎস হিসেবে বিবেচনা করা উচিত। গুরুত্বপূর্ণ তথ্যের জন্য, পেশাদার মানব অনুবাদ সুপারিশ করা হয়। এই অনুবাদ ব্যবহারের ফলে কোনো ভুল বোঝাবুঝি বা ভুল ব্যাখ্যা হলে আমরা দায়বদ্ধ থাকব না।