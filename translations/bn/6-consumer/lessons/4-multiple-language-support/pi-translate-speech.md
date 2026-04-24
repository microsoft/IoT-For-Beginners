# স্পিচ অনুবাদ - রাস্পবেরি পাই

এই পাঠের এই অংশে, আপনি অনুবাদক সার্ভিস ব্যবহার করে টেক্সট অনুবাদ করার কোড লিখবেন।

## অনুবাদক সার্ভিস ব্যবহার করে টেক্সটকে স্পিচে রূপান্তর করুন

স্পিচ সার্ভিস REST API সরাসরি অনুবাদ সমর্থন করে না, তবে আপনি স্পিচ টু টেক্সট সার্ভিস দ্বারা তৈরি টেক্সট এবং কথোপকথনের টেক্সট অনুবাদ করতে অনুবাদক সার্ভিস ব্যবহার করতে পারেন। এই সার্ভিসে REST API রয়েছে যা আপনি টেক্সট অনুবাদ করতে ব্যবহার করতে পারেন।

### কাজ - অনুবাদক রিসোর্স ব্যবহার করে টেক্সট অনুবাদ করুন

1. আপনার স্মার্ট টাইমারে ২টি ভাষা সেট করা থাকবে - সার্ভারের ভাষা যা LUIS প্রশিক্ষণের জন্য ব্যবহার করা হয়েছে (এই একই ভাষা ব্যবহার করে ব্যবহারকারীর সাথে কথা বলার বার্তা তৈরি করা হয়), এবং ব্যবহারকারীর কথোপকথনের ভাষা। `language` ভ্যারিয়েবলটি ব্যবহারকারীর কথোপকথনের ভাষা হিসেবে আপডেট করুন এবং একটি নতুন ভ্যারিয়েবল `server_language` যোগ করুন যা LUIS প্রশিক্ষণের জন্য ব্যবহৃত ভাষা নির্দেশ করবে:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    `<user language>` এর জায়গায় সেই ভাষার লোকেল নাম দিন যা আপনি ব্যবহার করবেন, যেমন `fr-FR` ফ্রেঞ্চের জন্য, অথবা `zn-HK` ক্যান্টোনিজের জন্য।

    `<server language>` এর জায়গায় সেই লোকেল নাম দিন যা LUIS প্রশিক্ষণের জন্য ব্যবহৃত হয়েছে।

    Microsoft ডকুমেন্টেশনে [Language and voice support](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) এ সমর্থিত ভাষা এবং তাদের লোকেল নামের তালিকা পাওয়া যাবে।

    > 💁 যদি আপনি একাধিক ভাষায় কথা বলতে না পারেন, তাহলে [Bing Translate](https://www.bing.com/translator) বা [Google Translate](https://translate.google.com) এর মতো সার্ভিস ব্যবহার করে আপনার পছন্দের ভাষা থেকে অন্য ভাষায় অনুবাদ করতে পারেন। এই সার্ভিসগুলো অনুবাদিত টেক্সটের অডিও প্লে করতে পারে।
    >
    > উদাহরণস্বরূপ, যদি আপনি ইংরেজিতে LUIS প্রশিক্ষণ দেন, কিন্তু ব্যবহারকারী ভাষা হিসেবে ফ্রেঞ্চ ব্যবহার করতে চান, তাহলে Bing Translate ব্যবহার করে "set a 2 minute and 27 second timer" বাক্যটি ইংরেজি থেকে ফ্রেঞ্চে অনুবাদ করতে পারেন, তারপর **Listen translation** বাটন ব্যবহার করে অনুবাদটি আপনার মাইক্রোফোনে বলতে পারেন।
    >
    > ![Bing Translate এ Listen translation বাটন](../../../../../translated_images/bn/bing-translate.348aa796d6efe2a9.webp)

1. `speech_api_key` এর নিচে অনুবাদক API কী যোগ করুন:

    ```python
    translator_api_key = '<key>'
    ```

    `<key>` এর জায়গায় আপনার অনুবাদক সার্ভিস রিসোর্সের API কী দিন।

1. `say` ফাংশনের উপরে একটি `translate_text` ফাংশন সংজ্ঞায়িত করুন যা সার্ভার ভাষা থেকে ব্যবহারকারীর ভাষায় টেক্সট অনুবাদ করবে:

    ```python
    def translate_text(text, from_language, to_language):
    ```

    এই ফাংশনে `from` এবং `to` ভাষা পাস করা হয় - আপনার অ্যাপকে ব্যবহারকারীর ভাষা থেকে সার্ভার ভাষায় স্পিচ চিনতে এবং সার্ভার ভাষা থেকে ব্যবহারকারীর ভাষায় কথোপকথন প্রদান করতে রূপান্তর করতে হবে।

1. এই ফাংশনের ভিতরে REST API কলের জন্য URL এবং হেডার সংজ্ঞায়িত করুন:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    এই API এর URL লোকেশন নির্দিষ্ট নয়, বরং লোকেশনটি হেডার হিসেবে পাস করা হয়। API কী সরাসরি ব্যবহার করা হয়, তাই স্পিচ সার্ভিসের মতো টোকেন ইস্যু API থেকে অ্যাক্সেস টোকেন পাওয়ার প্রয়োজন নেই।

1. এর নিচে কলের জন্য প্যারামিটার এবং বডি সংজ্ঞায়িত করুন:

    ```python
    params = {
        'from': from_language,
        'to': to_language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` API কলের প্যারামিটার সংজ্ঞায়িত করে, যেখানে `from` এবং `to` ভাষা পাস করা হয়। এই কল `from` ভাষার টেক্সটকে `to` ভাষায় অনুবাদ করবে।

    `body` অনুবাদ করার টেক্সট ধারণ করে। এটি একটি অ্যারে, কারণ একই কলের মাধ্যমে একাধিক টেক্সট ব্লক অনুবাদ করা যায়।

1. REST API কল করুন এবং রেসপন্স পান:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    ফিরে আসা রেসপন্সটি একটি JSON অ্যারে, যেখানে একটি আইটেম থাকে যা অনুবাদগুলো ধারণ করে। এই আইটেমে বডিতে পাস করা সমস্ত আইটেমের অনুবাদের জন্য একটি অ্যারে থাকে।

    ```json
    [
        {
            "translations": [
                {
                    "text": "Set a 2 minute 27 second timer.",
                    "to": "en"
                }
            ]
        }
    ]
    ```

1. অ্যারের প্রথম আইটেম থেকে প্রথম অনুবাদের `text` প্রপার্টি রিটার্ন করুন:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. `while True` লুপ আপডেট করুন যাতে ব্যবহারকারীর ভাষা থেকে সার্ভার ভাষায় `convert_speech_to_text` কলের টেক্সট অনুবাদ করা যায়:

    ```python
    if len(text) > 0:
        print('Original:', text)
        text = translate_text(text, language, server_language)
        print('Translated:', text)

        message = Message(json.dumps({ 'speech': text }))
        device_client.send_message(message)
    ```

    এই কোডটি মূল এবং অনুবাদিত টেক্সট কনসোলে প্রিন্ট করে।

1. `say` ফাংশন আপডেট করুন যাতে সার্ভার ভাষা থেকে ব্যবহারকারীর ভাষায় বলার টেক্সট অনুবাদ করা যায়:

    ```python
    def say(text):
        print('Original:', text)
        text = translate_text(text, server_language, language)
        print('Translated:', text)
        speech = get_speech(text)
        play_speech(speech)
    ```

    এই কোডটি মূল এবং অনুবাদিত টেক্সট কনসোলে প্রিন্ট করে।

1. আপনার কোড চালান। নিশ্চিত করুন যে আপনার ফাংশন অ্যাপ চালু আছে এবং ব্যবহারকারীর ভাষায় একটি টাইমার অনুরোধ করুন, হয় নিজে সেই ভাষায় কথা বলে অথবা একটি অনুবাদ অ্যাপ ব্যবহার করে।

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py
    Connecting
    Connected
    Using voice fr-FR-DeniseNeural
    Original: Définir une minuterie de 2 minutes et 27 secondes.
    Translated: Set a timer of 2 minutes and 27 seconds.
    Original: 2 minute 27 second timer started.
    Translated: 2 minute 27 seconde minute a commencé.
    Original: Times up on your 2 minute 27 second timer.
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

    > 💁 বিভিন্ন ভাষায় কিছু বলার ভিন্ন উপায় থাকার কারণে, আপনি এমন অনুবাদ পেতে পারেন যা LUIS-এ দেওয়া উদাহরণগুলোর থেকে সামান্য ভিন্ন। যদি এমন হয়, তাহলে LUIS-এ আরও উদাহরণ যোগ করুন, পুনরায় প্রশিক্ষণ দিন এবং মডেলটি পুনরায় প্রকাশ করুন।

> 💁 আপনি এই কোডটি [code/pi](../../../../../6-consumer/lessons/4-multiple-language-support/code/pi) ফোল্ডারে খুঁজে পেতে পারেন।

😀 আপনার বহুভাষিক টাইমার প্রোগ্রাম সফল হয়েছে!

---

**অস্বীকৃতি**:  
এই নথিটি AI অনুবাদ পরিষেবা [Co-op Translator](https://github.com/Azure/co-op-translator) ব্যবহার করে অনুবাদ করা হয়েছে। আমরা যথাসম্ভব সঠিক অনুবাদ প্রদানের চেষ্টা করি, তবে অনুগ্রহ করে মনে রাখবেন যে স্বয়ংক্রিয় অনুবাদে ত্রুটি বা অসঙ্গতি থাকতে পারে। মূল ভাষায় থাকা নথিটিকে প্রামাণিক উৎস হিসেবে বিবেচনা করা উচিত। গুরুত্বপূর্ণ তথ্যের জন্য, পেশাদার মানব অনুবাদ সুপারিশ করা হয়। এই অনুবাদ ব্যবহারের ফলে কোনো ভুল বোঝাবুঝি বা ভুল ব্যাখ্যা হলে আমরা তার জন্য দায়ী থাকব না।