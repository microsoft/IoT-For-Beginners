<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "af249a24d4fe4f4de4806adbc3bc9d86",
  "translation_date": "2025-08-27T14:22:37+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-speech-to-text.md",
  "language_code": "bn"
}
-->
# স্পিচ টু টেক্সট - রাস্পবেরি পাই

এই পাঠের এই অংশে, আপনি কোড লিখবেন যা ক্যাপচার করা অডিওর স্পিচকে টেক্সটে রূপান্তর করবে স্পিচ সার্ভিস ব্যবহার করে।

## অডিও স্পিচ সার্ভিসে পাঠানো

অডিও স্পিচ সার্ভিসে REST API ব্যবহার করে পাঠানো যেতে পারে। স্পিচ সার্ভিস ব্যবহার করতে হলে প্রথমে একটি অ্যাক্সেস টোকেন অনুরোধ করতে হবে, তারপর সেই টোকেন ব্যবহার করে REST API-তে প্রবেশ করতে হবে। এই অ্যাক্সেস টোকেন ১০ মিনিট পরপর মেয়াদোত্তীর্ণ হয়ে যায়, তাই আপনার কোড নিয়মিতভাবে টোকেন অনুরোধ করবে যাতে এটি সবসময় আপডেট থাকে।

### কাজ - একটি অ্যাক্সেস টোকেন সংগ্রহ করা

1. আপনার পাই-তে `smart-timer` প্রজেক্টটি খুলুন।

1. `play_audio` ফাংশনটি সরিয়ে ফেলুন। এটি আর প্রয়োজন নেই কারণ আপনি চান না যে স্মার্ট টাইমার আপনার বলা কথাগুলো পুনরায় বলুক।

1. `app.py` ফাইলের শীর্ষে নিচের ইমপোর্টটি যোগ করুন:

    ```python
    import requests
    ```

1. `while True` লুপের উপরে নিচের কোডটি যোগ করুন স্পিচ সার্ভিসের জন্য কিছু সেটিংস ঘোষণা করতে:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'
    ```

    `<key>`-এর জায়গায় আপনার স্পিচ সার্ভিস রিসোর্সের API কী বসান। `<location>`-এর জায়গায় সেই অবস্থান বসান যা আপনি স্পিচ সার্ভিস রিসোর্স তৈরি করার সময় ব্যবহার করেছিলেন।

    `<language>`-এর জায়গায় সেই ভাষার লোকেল নাম বসান যা আপনি কথা বলার সময় ব্যবহার করবেন, যেমন `en-GB` ইংরেজির জন্য বা `zn-HK` ক্যান্টোনিজের জন্য। Microsoft ডক্সে [Language and voice support documentation](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text)-এ সমর্থিত ভাষা এবং তাদের লোকেল নামের তালিকা পাওয়া যাবে।

1. এর নিচে, একটি ফাংশন যোগ করুন অ্যাক্সেস টোকেন সংগ্রহ করার জন্য:

    ```python
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_api_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    এটি একটি টোকেন ইস্যু করার এন্ডপয়েন্টে কল করে, API কীকে একটি হেডার হিসেবে পাঠিয়ে। এই কলটি একটি অ্যাক্সেস টোকেন ফেরত দেয় যা স্পিচ সার্ভিসে কল করার জন্য ব্যবহার করা যেতে পারে।

1. এর নিচে, একটি ফাংশন ঘোষণা করুন যা REST API ব্যবহার করে ক্যাপচার করা অডিওর স্পিচকে টেক্সটে রূপান্তর করবে:

    ```python
    def convert_speech_to_text(buffer):
    ```

1. এই ফাংশনের ভিতরে, REST API URL এবং হেডার সেট আপ করুন:

    ```python
    url = f'https://{location}.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1'

    headers = {
        'Authorization': 'Bearer ' + get_access_token(),
        'Content-Type': f'audio/wav; codecs=audio/pcm; samplerate={rate}',
        'Accept': 'application/json;text/xml'
    }

    params = {
        'language': language
    }
    ```

    এটি স্পিচ সার্ভিস রিসোর্সের অবস্থান ব্যবহার করে একটি URL তৈরি করে। তারপর এটি হেডারগুলোতে `get_access_token` ফাংশন থেকে প্রাপ্ত অ্যাক্সেস টোকেন, অডিও ক্যাপচার করার সময় ব্যবহৃত স্যাম্পল রেট যোগ করে। শেষে এটি URL-এর সাথে কিছু প্যারামিটার সংজ্ঞায়িত করে যা অডিওর ভাষা ধারণ করে।

1. এর নিচে, REST API-তে কল করার এবং টেক্সট ফেরত পাওয়ার জন্য নিচের কোডটি যোগ করুন:

    ```python
    response = requests.post(url, headers=headers, params=params, data=buffer)
    response_json = response.json()

    if response_json['RecognitionStatus'] == 'Success':
        return response_json['DisplayText']
    else:
        return ''
    ```

    এটি URL-এ কল করে এবং রেসপন্সে আসা JSON মানটি ডিকোড করে। রেসপন্সে থাকা `RecognitionStatus` মানটি নির্দেশ করে যে কলটি সফলভাবে স্পিচকে টেক্সটে রূপান্তর করতে পেরেছে কিনা, এবং যদি এটি `Success` হয় তাহলে ফাংশন থেকে টেক্সট ফেরত দেওয়া হয়, অন্যথায় একটি খালি স্ট্রিং ফেরত দেওয়া হয়।

1. `while True:` লুপের উপরে একটি ফাংশন সংজ্ঞায়িত করুন যা স্পিচ টু টেক্সট সার্ভিস থেকে ফেরত পাওয়া টেক্সট প্রক্রিয়া করবে। এই ফাংশনটি আপাতত কনসোলে টেক্সটটি প্রিন্ট করবে।

    ```python
    def process_text(text):
        print(text)
    ```

1. শেষে `while True` লুপে `play_audio`-তে কল করার পরিবর্তে `convert_speech_to_text` ফাংশনে কল করুন, এবং টেক্সটটি `process_text` ফাংশনে পাঠান:

    ```python
    text = convert_speech_to_text(buffer)
    process_text(text)
    ```

1. কোডটি চালান। বোতামটি চাপুন এবং মাইক্রোফোনে কথা বলুন। কাজ শেষ হলে বোতামটি ছেড়ে দিন, এবং অডিওটি টেক্সটে রূপান্তরিত হয়ে কনসোলে প্রিন্ট হবে।

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Hello world.
    Welcome to IoT for beginners.
    ```

    বিভিন্ন ধরনের বাক্য চেষ্টা করুন, সাথে এমন বাক্য যেখানে শব্দগুলো একই রকম শোনায় কিন্তু তাদের অর্থ ভিন্ন। উদাহরণস্বরূপ, যদি আপনি ইংরেজিতে কথা বলছেন, বলুন 'I want to buy two bananas and an apple too', এবং লক্ষ্য করুন কিভাবে এটি সঠিক to, two এবং too ব্যবহার করে শব্দের প্রসঙ্গ অনুযায়ী, শুধুমাত্র শব্দের ধ্বনি নয়।

> 💁 আপনি এই কোডটি [code-speech-to-text/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/pi) ফোল্ডারে খুঁজে পেতে পারেন।

😀 আপনার স্পিচ টু টেক্সট প্রোগ্রাম সফল হয়েছে!

---

**অস্বীকৃতি**:  
এই নথিটি AI অনুবাদ পরিষেবা [Co-op Translator](https://github.com/Azure/co-op-translator) ব্যবহার করে অনুবাদ করা হয়েছে। আমরা যথাসাধ্য সঠিকতার জন্য চেষ্টা করি, তবে অনুগ্রহ করে মনে রাখবেন যে স্বয়ংক্রিয় অনুবাদে ত্রুটি বা অসঙ্গতি থাকতে পারে। মূল ভাষায় থাকা নথিটিকে প্রামাণিক উৎস হিসেবে বিবেচনা করা উচিত। গুরুত্বপূর্ণ তথ্যের জন্য, পেশাদার মানব অনুবাদ সুপারিশ করা হয়। এই অনুবাদ ব্যবহারের ফলে কোনো ভুল বোঝাবুঝি বা ভুল ব্যাখ্যা হলে আমরা দায়বদ্ধ থাকব না।