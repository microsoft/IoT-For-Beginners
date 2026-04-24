# বক্তৃতা অনুবাদ করুন - ভার্চুয়াল IoT ডিভাইস

এই পাঠের এই অংশে, আপনি বক্তৃতা পরিষেবা ব্যবহার করে বক্তৃতাকে টেক্সটে রূপান্তর করার সময় অনুবাদ করার কোড লিখবেন, তারপর অনুবাদক পরিষেবা ব্যবহার করে টেক্সট অনুবাদ করবেন এবং একটি কথিত প্রতিক্রিয়া তৈরি করবেন।

## বক্তৃতা পরিষেবা ব্যবহার করে বক্তৃতা অনুবাদ করুন

বক্তৃতা পরিষেবা বক্তৃতাকে টেক্সটে রূপান্তর করতে পারে শুধুমাত্র একই ভাষায় নয়, বরং আউটপুটকে অন্যান্য ভাষায়ও অনুবাদ করতে পারে।

### কাজ - বক্তৃতা পরিষেবা ব্যবহার করে বক্তৃতা অনুবাদ করুন

1. VS Code-এ `smart-timer` প্রকল্পটি খুলুন এবং নিশ্চিত করুন যে ভার্চুয়াল পরিবেশটি টার্মিনালে লোড হয়েছে।

1. বিদ্যমান ইমপোর্টগুলির নিচে নিম্নলিখিত ইমপোর্ট বিবৃতিগুলি যোগ করুন:

    ```python
    from azure.cognitiveservices import speech
    from azure.cognitiveservices.speech.translation import SpeechTranslationConfig, TranslationRecognizer
    import requests
    ```

    এটি বক্তৃতা অনুবাদ করতে ব্যবহৃত ক্লাসগুলি এবং একটি `requests` লাইব্রেরি আমদানি করে যা এই পাঠে পরে অনুবাদক পরিষেবায় কল করতে ব্যবহৃত হবে।

1. আপনার স্মার্ট টাইমারে ২টি ভাষা সেট করা থাকবে - সার্ভারের ভাষা যা LUIS প্রশিক্ষণের জন্য ব্যবহৃত হয়েছিল (একই ভাষা ব্যবহারকারীর সাথে কথা বলার বার্তা তৈরি করতে ব্যবহৃত হয়), এবং ব্যবহারকারীর দ্বারা কথিত ভাষা। `language` ভেরিয়েবলটি আপডেট করুন যাতে এটি ব্যবহারকারীর দ্বারা কথিত ভাষা হয় এবং LUIS প্রশিক্ষণের জন্য ব্যবহৃত ভাষার জন্য `server_language` নামে একটি নতুন ভেরিয়েবল যোগ করুন:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    `<user language>`-এর জায়গায় সেই ভাষার লোকেল নাম দিন যা আপনি কথা বলবেন, যেমন `fr-FR` ফ্রেঞ্চের জন্য বা `zn-HK` ক্যান্টোনিজের জন্য।

    `<server language>`-এর জায়গায় LUIS প্রশিক্ষণের জন্য ব্যবহৃত ভাষার লোকেল নাম দিন।

    Microsoft ডকুমেন্টেশনে [Language and voice support](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) এ সমর্থিত ভাষা এবং তাদের লোকেল নামের একটি তালিকা খুঁজে পেতে পারেন।

    > 💁 যদি আপনি একাধিক ভাষায় কথা বলতে না পারেন, তবে আপনি [Bing Translate](https://www.bing.com/translator) বা [Google Translate](https://translate.google.com) এর মতো একটি পরিষেবা ব্যবহার করতে পারেন আপনার পছন্দের ভাষা থেকে অন্য ভাষায় অনুবাদ করতে। এই পরিষেবাগুলি অনুবাদিত টেক্সটের অডিও প্লে করতে পারে। মনে রাখবেন যে বক্তৃতা শনাক্তকারী আপনার ডিভাইস থেকে কিছু অডিও আউটপুট উপেক্ষা করবে, তাই আপনাকে অনুবাদিত টেক্সট প্লে করতে একটি অতিরিক্ত ডিভাইস ব্যবহার করতে হতে পারে।
    >
    > উদাহরণস্বরূপ, যদি আপনি ইংরেজিতে LUIS প্রশিক্ষণ দেন, কিন্তু ব্যবহারকারীর ভাষা হিসেবে ফ্রেঞ্চ ব্যবহার করতে চান, আপনি Bing Translate ব্যবহার করে "set a 2 minute and 27 second timer" এর মতো বাক্য ইংরেজি থেকে ফ্রেঞ্চে অনুবাদ করতে পারেন, তারপর **Listen translation** বোতামটি ব্যবহার করে অনুবাদটি আপনার মাইক্রোফোনে বলুন।
    >
    > ![Bing Translate-এ Listen translation বোতাম](../../../../../translated_images/bn/bing-translate.348aa796d6efe2a9.webp)

1. `recognizer_config` এবং `recognizer` ঘোষণাগুলি নিম্নলিখিত দিয়ে প্রতিস্থাপন করুন:

    ```python
    translation_config = SpeechTranslationConfig(subscription=speech_api_key,
                                                 region=location,
                                                 speech_recognition_language=language,
                                                 target_languages=(language, server_language))
    
    recognizer = TranslationRecognizer(translation_config=translation_config)
    ```

    এটি একটি অনুবাদ কনফিগ তৈরি করে যা ব্যবহারকারীর ভাষায় বক্তৃতা শনাক্ত করে এবং ব্যবহারকারী এবং সার্ভারের ভাষায় অনুবাদ তৈরি করে। তারপর এটি এই কনফিগ ব্যবহার করে একটি অনুবাদ শনাক্তকারী তৈরি করে - একটি বক্তৃতা শনাক্তকারী যা বক্তৃতা শনাক্তকরণের আউটপুটকে একাধিক ভাষায় অনুবাদ করতে পারে।

    > 💁 মূল ভাষাটি `target_languages`-এ নির্দিষ্ট করতে হবে, অন্যথায় আপনি কোনও অনুবাদ পাবেন না।

1. `recognized` ফাংশনটি আপডেট করুন, ফাংশনের পুরো বিষয়বস্তু নিম্নলিখিত দিয়ে প্রতিস্থাপন করুন:

    ```python
    if args.result.reason == speech.ResultReason.TranslatedSpeech:
        language_match = next(l for l in args.result.translations if server_language.lower().startswith(l.lower()))
        text = args.result.translations[language_match]
        if (len(text) > 0):
            print(f'Translated text: {text}')
    
            message = Message(json.dumps({ 'speech': text }))
            device_client.send_message(message)
    ```

    এই কোডটি পরীক্ষা করে দেখে যে বক্তৃতা অনুবাদ হওয়ার কারণে কি `recognized` ইভেন্টটি চালু হয়েছে (এই ইভেন্টটি অন্য সময়ও চালু হতে পারে, যেমন যখন বক্তৃতা শনাক্ত করা হয় কিন্তু অনুবাদ করা হয় না)। যদি বক্তৃতা অনুবাদ করা হয়, এটি `args.result.translations` ডিকশনারিতে সার্ভারের ভাষার সাথে মিলে যাওয়া অনুবাদটি খুঁজে পায়।

    `args.result.translations` ডিকশনারি লোকেল সেটিংয়ের পুরো অংশ নয়, ভাষার অংশ দ্বারা কীড হয়। উদাহরণস্বরূপ, যদি আপনি ফ্রেঞ্চের জন্য `fr-FR`-এ অনুবাদ অনুরোধ করেন, ডিকশনারিতে `fr`-এর জন্য একটি এন্ট্রি থাকবে, `fr-FR` নয়।

    অনুবাদিত টেক্সটটি IoT Hub-এ পাঠানো হয়।

1. এই কোডটি চালান এবং অনুবাদগুলি পরীক্ষা করুন। নিশ্চিত করুন যে আপনার ফাংশন অ্যাপটি চালু রয়েছে এবং ব্যবহারকারীর ভাষায় একটি টাইমার অনুরোধ করুন, হয় নিজে সেই ভাষায় কথা বলে, অথবা একটি অনুবাদ অ্যাপ ব্যবহার করে।

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    ```

## অনুবাদক পরিষেবা ব্যবহার করে টেক্সট অনুবাদ করুন

বক্তৃতা পরিষেবা টেক্সটকে পুনরায় বক্তৃতায় অনুবাদ করার সমর্থন দেয় না, পরিবর্তে আপনি অনুবাদক পরিষেবা ব্যবহার করতে পারেন টেক্সট অনুবাদ করতে। এই পরিষেবার একটি REST API রয়েছে যা আপনি টেক্সট অনুবাদ করতে ব্যবহার করতে পারেন।

### কাজ - অনুবাদক রিসোর্স ব্যবহার করে টেক্সট অনুবাদ করুন

1. `speech_api_key`-এর নিচে অনুবাদক API কী যোগ করুন:

    ```python
    translator_api_key = '<key>'
    ```

    `<key>`-এর জায়গায় আপনার অনুবাদক পরিষেবা রিসোর্সের API কী দিন।

1. `say` ফাংশনের উপরে একটি `translate_text` ফাংশন সংজ্ঞায়িত করুন যা সার্ভারের ভাষা থেকে ব্যবহারকারীর ভাষায় টেক্সট অনুবাদ করবে:

    ```python
    def translate_text(text):
    ```

1. এই ফাংশনের ভিতরে REST API কলের জন্য URL এবং হেডারগুলি সংজ্ঞায়িত করুন:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    এই API-এর URL অবস্থান নির্দিষ্ট নয়, পরিবর্তে অবস্থানটি একটি হেডার হিসাবে পাস করা হয়। API কী সরাসরি ব্যবহার করা হয়, তাই বক্তৃতা পরিষেবার মতো টোকেন ইস্যুয়ার API থেকে একটি অ্যাক্সেস টোকেন পাওয়ার প্রয়োজন নেই।

1. এর নিচে কলের জন্য প্যারামিটার এবং বডি সংজ্ঞায়িত করুন:

    ```python
    params = {
        'from': server_language,
        'to': language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` API কলের প্যারামিটারগুলি সংজ্ঞায়িত করে, `from` এবং `to` ভাষাগুলি পাস করে। এই কলটি `from` ভাষার টেক্সটকে `to` ভাষায় অনুবাদ করবে।

    `body` অনুবাদ করার জন্য টেক্সট ধারণ করে। এটি একটি অ্যারে, কারণ একই কলের মধ্যে একাধিক টেক্সট ব্লক অনুবাদ করা যেতে পারে।

1. REST API-তে কল করুন এবং প্রতিক্রিয়া পান:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    ফিরে আসা প্রতিক্রিয়াটি একটি JSON অ্যারে, যার একটি আইটেম রয়েছে যা অনুবাদগুলি ধারণ করে। এই আইটেমটির একটি অ্যারে রয়েছে বডিতে পাস করা সমস্ত আইটেমের অনুবাদের জন্য।

    ```json
    [
        {
            "translations": [
                {
                    "text": "Chronométrant votre minuterie de 2 minutes 27 secondes.",
                    "to": "fr"
                }
            ]
        }
    ]
    ```

1. অ্যারের প্রথম আইটেম থেকে প্রথম অনুবাদের `text` প্রপার্টি ফেরত দিন:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. SSML তৈরি করার আগে `say` ফাংশনটি বলার টেক্সট অনুবাদ করতে আপডেট করুন:

    ```python
    print('Original:', text)
    text = translate_text(text)
    print('Translated:', text)
    ```

    এই কোডটি মূল এবং অনুবাদিত টেক্সটটি কনসোলে প্রিন্ট করে।

1. আপনার কোড চালান। নিশ্চিত করুন যে আপনার ফাংশন অ্যাপটি চালু রয়েছে এবং ব্যবহারকারীর ভাষায় একটি টাইমার অনুরোধ করুন, হয় নিজে সেই ভাষায় কথা বলে, অথবা একটি অনুবাদ অ্যাপ ব্যবহার করে।

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    Original: 2 minute 27 second timer started.
    Translated: 2 minute 27 seconde minute a commencé.
    Original: Times up on your 2 minute 27 second timer.
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

    > 💁 বিভিন্ন ভাষায় কিছু বলার বিভিন্ন উপায়ের কারণে, আপনি এমন অনুবাদ পেতে পারেন যা LUIS-এ দেওয়া উদাহরণগুলির থেকে সামান্য আলাদা। যদি এমন হয়, LUIS-এ আরও উদাহরণ যোগ করুন, পুনরায় প্রশিক্ষণ দিন এবং তারপর মডেলটি পুনরায় প্রকাশ করুন।

> 💁 আপনি এই কোডটি [code/virtual-iot-device](../../../../../6-consumer/lessons/4-multiple-language-support/code/virtual-iot-device) ফোল্ডারে খুঁজে পেতে পারেন।

😀 আপনার বহুভাষিক টাইমার প্রোগ্রামটি সফল হয়েছে!

---

**অস্বীকৃতি**:  
এই নথিটি AI অনুবাদ পরিষেবা [Co-op Translator](https://github.com/Azure/co-op-translator) ব্যবহার করে অনুবাদ করা হয়েছে। আমরা যথাসম্ভব সঠিকতার জন্য চেষ্টা করি, তবে অনুগ্রহ করে মনে রাখবেন যে স্বয়ংক্রিয় অনুবাদে ত্রুটি বা অসঙ্গতি থাকতে পারে। মূল ভাষায় থাকা নথিটিকে প্রামাণিক উৎস হিসেবে বিবেচনা করা উচিত। গুরুত্বপূর্ণ তথ্যের জন্য, পেশাদার মানব অনুবাদ সুপারিশ করা হয়। এই অনুবাদ ব্যবহারের ফলে কোনো ভুল বোঝাবুঝি বা ভুল ব্যাখ্যা হলে আমরা দায়ী থাকব না।