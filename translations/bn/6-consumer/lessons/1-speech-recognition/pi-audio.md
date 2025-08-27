<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0ac0afcfb40cb5970ef4cb74f01c32e9",
  "translation_date": "2025-08-27T14:00:41+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-audio.md",
  "language_code": "bn"
}
-->
# অডিও রেকর্ড করুন - র‌্যাস্পবেরি পাই

এই পাঠের এই অংশে, আপনি র‌্যাস্পবেরি পাই-এ অডিও রেকর্ড করার জন্য কোড লিখবেন। একটি বোতামের মাধ্যমে অডিও রেকর্ডিং নিয়ন্ত্রণ করা হবে।

## হার্ডওয়্যার

র‌্যাস্পবেরি পাই-এ অডিও রেকর্ডিং নিয়ন্ত্রণের জন্য একটি বোতাম প্রয়োজন।

আপনি যে বোতামটি ব্যবহার করবেন তা হলো একটি গ্রোভ বোতাম। এটি একটি ডিজিটাল সেন্সর যা একটি সংকেত চালু বা বন্ধ করে। এই বোতামগুলো এমনভাবে কনফিগার করা যায় যাতে বোতাম চাপলে একটি উচ্চ সংকেত পাঠায় এবং না চাপলে নিম্ন সংকেত পাঠায়, অথবা উল্টোটা।

যদি আপনি মাইক্রোফোন হিসেবে ReSpeaker 2-Mics Pi HAT ব্যবহার করেন, তাহলে বোতাম সংযোগ করার প্রয়োজন নেই কারণ এই HAT-এ একটি বোতাম ইতিমধ্যেই সংযুক্ত থাকে। পরবর্তী অংশে যান।

### বোতাম সংযোগ করুন

বোতামটি গ্রোভ বেস হ্যাটের সাথে সংযুক্ত করা যেতে পারে।

#### কাজ - বোতাম সংযোগ করুন

![একটি গ্রোভ বোতাম](../../../../../translated_images/grove-button.a70cfbb809a8563681003250cf5b06d68cdcc68624f9e2f493d5a534ae2da1e5.bn.png)

1. গ্রোভ কেবলের এক প্রান্ত বোতাম মডিউলের সকেটে প্রবেশ করান। এটি শুধুমাত্র একটি নির্দিষ্ট দিকেই প্রবেশ করবে।

1. র‌্যাস্পবেরি পাই বন্ধ অবস্থায়, গ্রোভ কেবলের অন্য প্রান্তটি পাই-এর সাথে সংযুক্ত গ্রোভ বেস হ্যাটের **D5** চিহ্নিত ডিজিটাল সকেটে সংযুক্ত করুন। এই সকেটটি GPIO পিনের পাশে থাকা সকেটের সারির বাম দিক থেকে দ্বিতীয়।

![গ্রোভ বোতাম D5 সকেটে সংযুক্ত](../../../../../translated_images/pi-button.c7a1a4f55943341ce1baf1057658e9a205804d4131d258e820c93f951df0abf3.bn.png)

## অডিও রেকর্ড করুন

আপনি মাইক্রোফোন থেকে পাইথন কোড ব্যবহার করে অডিও রেকর্ড করতে পারেন।

### কাজ - অডিও রেকর্ড করুন

1. পাই চালু করুন এবং এটি বুট হওয়ার জন্য অপেক্ষা করুন।

1. ভিএস কোড চালু করুন, হয় সরাসরি পাই-এ, অথবা রিমোট SSH এক্সটেনশনের মাধ্যমে সংযোগ করে।

1. PyAudio Pip প্যাকেজে অডিও রেকর্ড এবং প্লেব্যাক করার ফাংশন রয়েছে। এই প্যাকেজটি কিছু অডিও লাইব্রেরির উপর নির্ভর করে যা প্রথমে ইনস্টল করতে হবে। টার্মিনালে নিম্নলিখিত কমান্ডগুলো চালান:

    ```sh
    sudo apt update
    sudo apt install libportaudio0 libportaudio2 libportaudiocpp0 portaudio19-dev libasound2-plugins --yes 
    ```

1. PyAudio Pip প্যাকেজ ইনস্টল করুন।

    ```sh
    pip3 install pyaudio
    ```

1. `smart-timer` নামে একটি নতুন ফোল্ডার তৈরি করুন এবং এই ফোল্ডারে `app.py` নামে একটি ফাইল যোগ করুন।

1. এই ফাইলের উপরে নিম্নলিখিত ইমপোর্টগুলো যোগ করুন:

    ```python
    import io
    import pyaudio
    import time
    import wave
    
    from grove.factory import Factory
    ```

    এটি `pyaudio` মডিউল, ওয়েভ ফাইল পরিচালনার জন্য কিছু স্ট্যান্ডার্ড পাইথন মডিউল, এবং `grove.factory` মডিউল থেকে একটি বোতাম ক্লাস তৈরি করার জন্য `Factory` ইমপোর্ট করে।

1. এর নিচে, একটি গ্রোভ বোতাম তৈরি করার জন্য কোড যোগ করুন।

    যদি আপনি ReSpeaker 2-Mics Pi HAT ব্যবহার করেন, তাহলে নিম্নলিখিত কোড ব্যবহার করুন:

    ```python
    # The button on the ReSpeaker 2-Mics Pi HAT
    button = Factory.getButton("GPIO-LOW", 17)
    ```

    এটি **D17** পোর্টে একটি বোতাম তৈরি করে, যেখানে ReSpeaker 2-Mics Pi HAT-এর বোতাম সংযুক্ত থাকে। এই বোতামটি চাপলে নিম্ন সংকেত পাঠানোর জন্য সেট করা হয়েছে।

    যদি আপনি ReSpeaker 2-Mics Pi HAT ব্যবহার না করেন এবং গ্রোভ বোতাম বেস হ্যাটে সংযুক্ত করেন, তাহলে এই কোড ব্যবহার করুন।

    ```python
    button = Factory.getButton("GPIO-HIGH", 5)
    ```

    এটি **D5** পোর্টে একটি বোতাম তৈরি করে যা চাপলে উচ্চ সংকেত পাঠানোর জন্য সেট করা হয়েছে।

1. এর নিচে, অডিও পরিচালনার জন্য PyAudio ক্লাসের একটি ইনস্ট্যান্স তৈরি করুন:

    ```python
    audio = pyaudio.PyAudio()
    ```

1. মাইক্রোফোন এবং স্পিকারের জন্য হার্ডওয়্যার কার্ড নম্বর ঘোষণা করুন। এটি সেই নম্বর যা আপনি এই পাঠের আগে `arecord -l` এবং `aplay -l` চালিয়ে পেয়েছিলেন।

    ```python
    microphone_card_number = <microphone card number>
    speaker_card_number = <speaker card number>
    ```

    `<microphone card number>`-এর জায়গায় আপনার মাইক্রোফোনের কার্ড নম্বর বসান।

    `<speaker card number>`-এর জায়গায় আপনার স্পিকারের কার্ড নম্বর বসান, যা আপনি `alsa.conf` ফাইলে সেট করেছিলেন।

1. এর নিচে, অডিও রেকর্ড এবং প্লেব্যাকের জন্য স্যাম্পল রেট ঘোষণা করুন। আপনি যে হার্ডওয়্যার ব্যবহার করছেন তার উপর নির্ভর করে এটি পরিবর্তন করতে হতে পারে।

    ```python
    rate = 48000 #48KHz
    ```

    যদি পরে এই কোড চালানোর সময় স্যাম্পল রেট সংক্রান্ত ত্রুটি পান, তাহলে এই মানটি `44100` বা `16000`-এ পরিবর্তন করুন। মান যত বেশি হবে, শব্দের গুণমান তত ভালো হবে।

1. এর নিচে, `capture_audio` নামে একটি নতুন ফাংশন তৈরি করুন। এটি মাইক্রোফোন থেকে অডিও রেকর্ড করার জন্য ডাকা হবে:

    ```python
    def capture_audio():
    ```

1. এই ফাংশনের ভিতরে, অডিও রেকর্ড করার জন্য নিম্নলিখিত কোড যোগ করুন:

    ```python
    stream = audio.open(format = pyaudio.paInt16,
                        rate = rate,
                        channels = 1, 
                        input_device_index = microphone_card_number,
                        input = True,
                        frames_per_buffer = 4096)

    frames = []

    while button.is_pressed():
        frames.append(stream.read(4096))

    stream.stop_stream()
    stream.close()
    ```

    এই কোডটি PyAudio অবজেক্ট ব্যবহার করে একটি অডিও ইনপুট স্ট্রিম খুলবে। এই স্ট্রিমটি মাইক্রোফোন থেকে 16KHz-এ অডিও রেকর্ড করবে, যা 4096 বাইটের বাফারে ধারণ করা হবে।

    কোডটি গ্রোভ বোতাম চাপা থাকা অবস্থায় লুপ করবে এবং প্রতিবার 4096 বাইটের বাফারগুলো একটি অ্যারেতে পড়বে।

    > 💁 `open` মেথডে পাস করা অপশনগুলো সম্পর্কে আরও জানতে [PyAudio ডকুমেন্টেশন](https://people.csail.mit.edu/hubert/pyaudio/docs/) দেখুন।

    বোতাম ছেড়ে দিলে, স্ট্রিমটি বন্ধ হয়ে যাবে।

1. এই ফাংশনের শেষে নিম্নলিখিত কোড যোগ করুন:

    ```python
    wav_buffer = io.BytesIO()
    with wave.open(wav_buffer, 'wb') as wavefile:
        wavefile.setnchannels(1)
        wavefile.setsampwidth(audio.get_sample_size(pyaudio.paInt16))
        wavefile.setframerate(rate)
        wavefile.writeframes(b''.join(frames))
        wav_buffer.seek(0)

    return wav_buffer
    ```

    এই কোডটি একটি বাইনারি বাফার তৈরি করে এবং সমস্ত রেকর্ড করা অডিও একটি [WAV ফাইল](https://wikipedia.org/wiki/WAV) হিসেবে এতে লিখে। এটি একটি স্ট্যান্ডার্ড পদ্ধতি যা আনকমপ্রেসড অডিও একটি ফাইলে লেখার জন্য ব্যবহৃত হয়। এই বাফারটি পরে রিটার্ন করা হয়।

1. অডিও বাফার প্লেব্যাক করার জন্য `play_audio` ফাংশনটি যোগ করুন:

    ```python
    def play_audio(buffer):
        stream = audio.open(format = pyaudio.paInt16,
                            rate = rate,
                            channels = 1,
                            output_device_index = speaker_card_number,
                            output = True)
    
        with wave.open(buffer, 'rb') as wf:
            data = wf.readframes(4096)
    
            while len(data) > 0:
                stream.write(data)
                data = wf.readframes(4096)
    
            stream.close()
    ```

    এই ফাংশনটি একটি আউটপুট স্ট্রিম খুলবে, যা অডিও প্লেব্যাকের জন্য ব্যবহৃত হবে। এটি ইনপুট স্ট্রিমের মতো একই সেটিংস ব্যবহার করে। বাফারটি একটি ওয়েভ ফাইল হিসেবে খোলা হয় এবং 4096 বাইটের চাঙ্কে আউটপুট স্ট্রিমে লেখা হয়, যা অডিও প্লে করে। এরপর স্ট্রিমটি বন্ধ হয়ে যায়।

1. `capture_audio` ফাংশনের নিচে নিম্নলিখিত কোড যোগ করুন যা বোতাম চাপা পর্যন্ত লুপ করবে। বোতাম চাপলে অডিও রেকর্ড হবে এবং পরে প্লে হবে।

    ```python
    while True:
        while not button.is_pressed():
            time.sleep(.1)
        
        buffer = capture_audio()
        play_audio(buffer)
    ```

1. কোডটি চালান। বোতাম চাপুন এবং মাইক্রোফোনে কথা বলুন। কাজ শেষ হলে বোতাম ছেড়ে দিন, এবং আপনি রেকর্ডিং শুনতে পাবেন।

    PyAudio ইনস্ট্যান্স তৈরি করার সময় আপনি কিছু ALSA ত্রুটি পেতে পারেন। এটি পাই-এর অডিও ডিভাইসের কনফিগারেশনের কারণে যা আপনার কাছে নেই। এই ত্রুটিগুলো উপেক্ষা করতে পারেন।

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.front
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.rear
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.center_lfe
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.side
    ```

    যদি আপনি নিম্নলিখিত ত্রুটি পান:

    ```output
    OSError: [Errno -9997] Invalid sample rate
    ```

    তাহলে `rate`-কে 44100 বা 16000-এ পরিবর্তন করুন।

> 💁 আপনি এই কোডটি [code-record/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-record/pi) ফোল্ডারে খুঁজে পেতে পারেন।

😀 আপনার অডিও রেকর্ডিং প্রোগ্রাম সফল হয়েছে!

---

**অস্বীকৃতি**:  
এই নথিটি AI অনুবাদ পরিষেবা [Co-op Translator](https://github.com/Azure/co-op-translator) ব্যবহার করে অনুবাদ করা হয়েছে। আমরা যথাসম্ভব সঠিকতার জন্য চেষ্টা করি, তবে অনুগ্রহ করে মনে রাখবেন যে স্বয়ংক্রিয় অনুবাদে ত্রুটি বা অসঙ্গতি থাকতে পারে। মূল ভাষায় থাকা নথিটিকে প্রামাণিক উৎস হিসেবে বিবেচনা করা উচিত। গুরুত্বপূর্ণ তথ্যের জন্য, পেশাদার মানব অনুবাদ সুপারিশ করা হয়। এই অনুবাদ ব্যবহারের ফলে কোনো ভুল বোঝাবুঝি বা ভুল ব্যাখ্যা হলে আমরা দায়বদ্ধ থাকব না।