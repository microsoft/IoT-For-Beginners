<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7966848a1f870e4c42edb4db67b13c57",
  "translation_date": "2025-08-27T13:59:32+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/virtual-device-text-to-speech.md",
  "language_code": "bn"
}
-->
# টেক্সট থেকে স্পিচ - ভার্চুয়াল IoT ডিভাইস

এই পাঠের এই অংশে, আপনি কোড লিখবেন যা টেক্সটকে স্পিচে রূপান্তর করবে স্পিচ সার্ভিস ব্যবহার করে।

## টেক্সটকে স্পিচে রূপান্তর করুন

স্পিচ সার্ভিস SDK, যা আপনি আগের পাঠে টেক্সটকে স্পিচে রূপান্তর করতে ব্যবহার করেছিলেন, সেটি টেক্সটকে আবার স্পিচে রূপান্তর করতে ব্যবহার করা যেতে পারে। স্পিচের জন্য অনুরোধ করার সময়, আপনাকে ব্যবহার করার জন্য একটি ভয়েস প্রদান করতে হবে কারণ বিভিন্ন ভয়েস ব্যবহার করে স্পিচ তৈরি করা যেতে পারে।

প্রতিটি ভাষা বিভিন্ন ভয়েস সমর্থন করে, এবং আপনি স্পিচ সার্ভিস SDK থেকে প্রতিটি ভাষার জন্য সমর্থিত ভয়েসের তালিকা পেতে পারেন।

### কাজ - টেক্সটকে স্পিচে রূপান্তর করুন

1. VS Code-এ `smart-timer` প্রজেক্টটি খুলুন এবং নিশ্চিত করুন যে ভার্চুয়াল এনভায়রনমেন্ট টার্মিনালে লোড হয়েছে।

1. `azure.cognitiveservices.speech` প্যাকেজ থেকে `SpeechSynthesizer` ইমপোর্ট করুন এবং এটি বিদ্যমান ইমপোর্টে যোগ করুন:

    ```python
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer, SpeechSynthesizer
    ```

1. `say` ফাংশনের উপরে একটি স্পিচ কনফিগারেশন তৈরি করুন যা স্পিচ সিন্থেসাইজারের সাথে ব্যবহার করা হবে:

    ```python
    speech_config = SpeechConfig(subscription=speech_api_key,
                                 region=location)
    speech_config.speech_synthesis_language = language
    speech_synthesizer = SpeechSynthesizer(speech_config=speech_config)
    ```

    এটি সেই একই API কী, লোকেশন এবং ভাষা ব্যবহার করে যা রিকগনাইজারের জন্য ব্যবহৃত হয়েছিল।

1. এর নিচে, একটি ভয়েস পাওয়ার জন্য এবং সেটি স্পিচ কনফিগে সেট করার জন্য নিচের কোড যোগ করুন:

    ```python
    voices = speech_synthesizer.get_voices_async().get().voices
    first_voice = next(x for x in voices if x.locale.lower() == language.lower())
    speech_config.speech_synthesis_voice_name = first_voice.short_name
    ```

    এটি সমস্ত উপলব্ধ ভয়েসের একটি তালিকা পুনরুদ্ধার করে, তারপর ব্যবহৃত ভাষার সাথে মিলে যাওয়া প্রথম ভয়েসটি খুঁজে বের করে।

    > 💁 আপনি Microsoft Docs-এর [Language and voice support documentation](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech) থেকে সমর্থিত ভয়েসের সম্পূর্ণ তালিকা পেতে পারেন। যদি আপনি একটি নির্দিষ্ট ভয়েস ব্যবহার করতে চান, তাহলে আপনি এই ফাংশনটি সরিয়ে দিতে পারেন এবং ডকুমেন্টেশন থেকে ভয়েস নামটি হার্ড কোড করতে পারেন। উদাহরণস্বরূপ:
    >
    > ```python
    > speech_config.speech_synthesis_voice_name = 'hi-IN-SwaraNeural'
    > ```

1. `say` ফাংশনের বিষয়বস্তু আপডেট করুন যাতে প্রতিক্রিয়ার জন্য SSML তৈরি করা যায়:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{first_voice.short_name}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

1. এর নিচে, স্পিচ রিকগনিশন বন্ধ করুন, SSML বলুন, তারপর রিকগনিশন আবার শুরু করুন:

    ```python
    recognizer.stop_continuous_recognition()
    speech_synthesizer.speak_ssml(ssml)
    recognizer.start_continuous_recognition()
    ```

    টেক্সট বলা হলে রিকগনিশন বন্ধ করা হয় যাতে টাইমার শুরু হওয়ার ঘোষণা শনাক্ত না হয়, LUIS-এ পাঠানো না হয় এবং সম্ভবত নতুন টাইমার সেট করার অনুরোধ হিসেবে ব্যাখ্যা না করা হয়।

    > 💁 আপনি এটি পরীক্ষা করতে পারেন রিকগনিশন বন্ধ এবং পুনরায় শুরু করার লাইনগুলো মন্তব্য করে। একটি টাইমার সেট করুন, এবং আপনি দেখতে পারেন যে ঘোষণা একটি নতুন টাইমার সেট করে, যা একটি নতুন ঘোষণা সৃষ্টি করে, এবং এভাবে চিরকাল চলতে থাকে!

1. অ্যাপটি চালান এবং নিশ্চিত করুন যে ফাংশন অ্যাপটিও চালু রয়েছে। কিছু টাইমার সেট করুন, এবং আপনি শুনবেন একটি কথিত প্রতিক্রিয়া যা বলবে যে আপনার টাইমার সেট করা হয়েছে, তারপর টাইমার সম্পূর্ণ হলে আরেকটি কথিত প্রতিক্রিয়া শুনবেন।

> 💁 আপনি এই কোডটি [code-spoken-response/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/virtual-iot-device) ফোল্ডারে খুঁজে পেতে পারেন।

😀 আপনার টাইমার প্রোগ্রাম সফল হয়েছে!

---

**অস্বীকৃতি**:  
এই নথিটি AI অনুবাদ পরিষেবা [Co-op Translator](https://github.com/Azure/co-op-translator) ব্যবহার করে অনুবাদ করা হয়েছে। আমরা যথাসম্ভব সঠিক অনুবাদ প্রদানের চেষ্টা করি, তবে অনুগ্রহ করে মনে রাখবেন যে স্বয়ংক্রিয় অনুবাদে ত্রুটি বা অসঙ্গতি থাকতে পারে। মূল ভাষায় থাকা নথিটিকে প্রামাণিক উৎস হিসেবে বিবেচনা করা উচিত। গুরুত্বপূর্ণ তথ্যের জন্য, পেশাদার মানব অনুবাদ সুপারিশ করা হয়। এই অনুবাদ ব্যবহারের ফলে কোনো ভুল বোঝাবুঝি বা ভুল ব্যাখ্যা হলে আমরা দায়বদ্ধ থাকব না।