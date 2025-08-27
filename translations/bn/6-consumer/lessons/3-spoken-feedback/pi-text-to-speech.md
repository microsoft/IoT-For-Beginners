<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "606f3af1c78e3741e48ce77c31cea626",
  "translation_date": "2025-08-27T13:53:01+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/pi-text-to-speech.md",
  "language_code": "bn"
}
-->
# টেক্সট থেকে স্পিচ - র‌্যাস্পবেরি পাই

এই পাঠের এই অংশে, আপনি স্পিচ সার্ভিস ব্যবহার করে টেক্সটকে স্পিচে রূপান্তর করার কোড লিখবেন।

## স্পিচ সার্ভিস ব্যবহার করে টেক্সটকে স্পিচে রূপান্তর করুন

টেক্সটকে স্পিচ সার্ভিসে REST API এর মাধ্যমে পাঠানো যেতে পারে, যা থেকে একটি অডিও ফাইল পাওয়া যাবে যা আপনার IoT ডিভাইসে প্লে করা যাবে। স্পিচের জন্য অনুরোধ করার সময়, আপনাকে ব্যবহৃত ভয়েসটি নির্ধারণ করতে হবে, কারণ বিভিন্ন ভয়েস ব্যবহার করে স্পিচ তৈরি করা সম্ভব।

প্রতিটি ভাষার জন্য বিভিন্ন ভয়েস সমর্থিত, এবং আপনি স্পিচ সার্ভিসে REST অনুরোধ পাঠিয়ে প্রতিটি ভাষার জন্য সমর্থিত ভয়েসগুলোর তালিকা পেতে পারেন।

### কাজ - একটি ভয়েস পান

1. VS Code-এ `smart-timer` প্রজেক্টটি খুলুন।

1. একটি ভাষার জন্য ভয়েসের তালিকা পাওয়ার জন্য `say` ফাংশনের উপরে নিচের কোডটি যোগ করুন:

    ```python
    def get_voice():
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/voices/list'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token()
        }
    
        response = requests.get(url, headers=headers)
        voices_json = json.loads(response.text)
    
        first_voice = next(x for x in voices_json if x['Locale'].lower() == language.lower() and x['VoiceType'] == 'Neural')
        return first_voice['ShortName']
    
    voice = get_voice()
    print(f'Using voice {voice}')
    ```

    এই কোডটি `get_voice` নামে একটি ফাংশন সংজ্ঞায়িত করে, যা স্পিচ সার্ভিস ব্যবহার করে ভয়েসের একটি তালিকা পায়। এটি তারপর ব্যবহৃত ভাষার সাথে মেলে এমন প্রথম ভয়েসটি খুঁজে বের করে।

    এই ফাংশনটি তারপর প্রথম ভয়েসটি সংরক্ষণ করতে এবং কনসোলে ভয়েসের নাম প্রিন্ট করতে ডাকা হয়। এই ভয়েসটি একবার অনুরোধ করা যেতে পারে এবং টেক্সটকে স্পিচে রূপান্তর করার প্রতিটি কলের জন্য এই মানটি ব্যবহার করা যেতে পারে।

    > 💁 আপনি Microsoft Docs-এ [Language and voice support documentation](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech) থেকে সমর্থিত ভয়েসগুলোর সম্পূর্ণ তালিকা পেতে পারেন। যদি আপনি একটি নির্দিষ্ট ভয়েস ব্যবহার করতে চান, তাহলে আপনি এই ফাংশনটি সরিয়ে দিয়ে ডকুমেন্টেশন থেকে ভয়েসের নামটি হার্ড কোড করতে পারেন। উদাহরণস্বরূপ:
    >
    > ```python
    > voice = 'hi-IN-SwaraNeural'
    > ```

### কাজ - টেক্সটকে স্পিচে রূপান্তর করুন

1. এর নিচে, স্পিচ সার্ভিস থেকে প্রাপ্ত অডিও ফরম্যাটের জন্য একটি কনস্ট্যান্ট সংজ্ঞায়িত করুন। অডিও অনুরোধ করার সময়, এটি বিভিন্ন ফরম্যাটে করা যেতে পারে।

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'
    ```

    আপনি যে ফরম্যাটটি ব্যবহার করতে পারেন তা আপনার হার্ডওয়্যারের উপর নির্ভর করে। যদি অডিও প্লে করার সময় `Invalid sample rate` ত্রুটি পান, তাহলে এটি অন্য মানে পরিবর্তন করুন। Microsoft Docs-এ [Text to speech REST API documentation](https://docs.microsoft.com/azure/cognitive-services/speech-service/rest-text-to-speech?WT.mc_id=academic-17441-jabenn#audio-outputs) এ সমর্থিত মানগুলোর তালিকা পেতে পারেন। আপনাকে `riff` ফরম্যাটের অডিও ব্যবহার করতে হবে, এবং চেষ্টা করার জন্য মানগুলো হলো `riff-16khz-16bit-mono-pcm`, `riff-24khz-16bit-mono-pcm` এবং `riff-48khz-16bit-mono-pcm`।

1. এর নিচে, `get_speech` নামে একটি ফাংশন ঘোষণা করুন, যা স্পিচ সার্ভিস REST API ব্যবহার করে টেক্সটকে স্পিচে রূপান্তর করবে:

    ```python
    def get_speech(text):
    ```

1. `get_speech` ফাংশনে, কল করার জন্য URL এবং পাস করার জন্য হেডারগুলো সংজ্ঞায়িত করুন:

    ```python
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    ```

    এটি একটি জেনারেটেড অ্যাক্সেস টোকেন ব্যবহার করতে, কন্টেন্টকে SSML হিসেবে সেট করতে এবং প্রয়োজনীয় অডিও ফরম্যাট নির্ধারণ করতে হেডারগুলো সেট করে।

1. এর নিচে, REST API-তে পাঠানোর জন্য SSML সংজ্ঞায়িত করুন:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

    এই SSML ভাষা এবং ব্যবহৃত ভয়েস নির্ধারণ করে, পাশাপাশি রূপান্তর করার জন্য টেক্সট নির্ধারণ করে।

1. শেষ পর্যন্ত, এই ফাংশনে REST অনুরোধ করার এবং বাইনারি অডিও ডেটা ফেরত দেওয়ার কোড যোগ করুন:

    ```python
    response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    return io.BytesIO(response.content)
    ```

### কাজ - অডিও প্লে করুন

1. `get_speech` ফাংশনের নিচে, REST API কল থেকে প্রাপ্ত অডিও প্লে করার জন্য একটি নতুন ফাংশন সংজ্ঞায়িত করুন:

    ```python
    def play_speech(speech):
    ```

1. এই ফাংশনে পাস করা `speech` হবে REST API থেকে ফেরত প্রাপ্ত বাইনারি অডিও ডেটা। এটি একটি ওয়েভ ফাইল হিসেবে খুলতে এবং PyAudio ব্যবহার করে অডিও প্লে করতে নিচের কোডটি ব্যবহার করুন:

    ```python
    def play_speech(speech):
        with wave.open(speech, 'rb') as wave_file:
            stream = audio.open(format=audio.get_format_from_width(wave_file.getsampwidth()),
                                channels=wave_file.getnchannels(),
                                rate=wave_file.getframerate(),
                                output_device_index=speaker_card_number,
                                output=True)

            data = wave_file.readframes(4096)

            while len(data) > 0:
                stream.write(data)
                data = wave_file.readframes(4096)

            stream.stop_stream()
            stream.close()
    ```

    এই কোডটি একটি PyAudio স্ট্রিম ব্যবহার করে, যা অডিও ক্যাপচার করার মতোই। পার্থক্য হলো এখানে স্ট্রিমটি আউটপুট স্ট্রিম হিসেবে সেট করা হয়েছে, এবং অডিও ডেটা থেকে ডেটা পড়া হয় এবং স্ট্রিমে পাঠানো হয়।

    স্ট্রিমের বিবরণ যেমন স্যাম্পল রেট হার্ড কোড করার পরিবর্তে, এটি অডিও ডেটা থেকে পড়া হয়।

1. `say` ফাংশনের বিষয়বস্তু নিচের কোড দিয়ে প্রতিস্থাপন করুন:

    ```python
    speech = get_speech(text)
    play_speech(speech)
    ```

    এই কোডটি টেক্সটকে বাইনারি অডিও ডেটা হিসেবে স্পিচে রূপান্তর করে এবং অডিও প্লে করে।

1. অ্যাপটি চালান এবং নিশ্চিত করুন যে ফাংশন অ্যাপটিও চালু রয়েছে। কিছু টাইমার সেট করুন, এবং আপনি শুনবেন যে আপনার টাইমার সেট হয়েছে বলে একটি কথোপকথন প্রতিক্রিয়া দিচ্ছে, তারপর টাইমার সম্পূর্ণ হলে আরেকটি কথোপকথন প্রতিক্রিয়া শোনা যাবে।

    যদি আপনি `Invalid sample rate` ত্রুটি পান, তাহলে উপরে বর্ণিত অনুযায়ী `playback_format` পরিবর্তন করুন।

> 💁 আপনি এই কোডটি [code-spoken-response/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/pi) ফোল্ডারে খুঁজে পেতে পারেন।

😀 আপনার টাইমার প্রোগ্রাম সফল হয়েছে!

---

**অস্বীকৃতি**:  
এই নথিটি AI অনুবাদ পরিষেবা [Co-op Translator](https://github.com/Azure/co-op-translator) ব্যবহার করে অনুবাদ করা হয়েছে। আমরা যথাসম্ভব সঠিক অনুবাদ প্রদানের চেষ্টা করি, তবে অনুগ্রহ করে মনে রাখবেন যে স্বয়ংক্রিয় অনুবাদে ত্রুটি বা অসঙ্গতি থাকতে পারে। মূল ভাষায় থাকা নথিটিকে প্রামাণিক উৎস হিসেবে বিবেচনা করা উচিত। গুরুত্বপূর্ণ তথ্যের জন্য, পেশাদার মানব অনুবাদ সুপারিশ করা হয়। এই অনুবাদ ব্যবহারের ফলে কোনো ভুল বোঝাবুঝি বা ভুল ব্যাখ্যা হলে আমরা দায়বদ্ধ থাকব না।