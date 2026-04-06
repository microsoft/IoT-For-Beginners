# হার্ডওয়্যার

IoT-এ **T** মানে **থিংস** এবং এটি এমন ডিভাইসগুলিকে বোঝায় যা আমাদের চারপাশের জগতের সাথে যোগাযোগ করে। প্রতিটি প্রকল্প বাস্তব হার্ডওয়্যারের উপর ভিত্তি করে তৈরি, যা শিক্ষার্থী এবং শৌখিনদের জন্য সহজলভ্য। আমরা IoT হার্ডওয়্যারের দুটি বিকল্প সরবরাহ করেছি, যা ব্যক্তিগত পছন্দ, প্রোগ্রামিং ভাষার জ্ঞান বা পছন্দ, শেখার লক্ষ্য এবং প্রাপ্যতার উপর নির্ভর করে ব্যবহার করা যেতে পারে। যাদের কাছে হার্ডওয়্যার নেই বা কেনার আগে আরও শিখতে চান তাদের জন্য আমরা একটি 'ভার্চুয়াল হার্ডওয়্যার' সংস্করণও সরবরাহ করেছি।

> 💁 অ্যাসাইনমেন্ট সম্পন্ন করার জন্য আপনাকে কোনো IoT হার্ডওয়্যার কিনতে হবে না। আপনি সবকিছু ভার্চুয়াল IoT হার্ডওয়্যার ব্যবহার করেই করতে পারবেন।

শারীরিক হার্ডওয়্যারের বিকল্পগুলি হল Arduino বা Raspberry Pi। প্রতিটি প্ল্যাটফর্মের নিজস্ব সুবিধা এবং অসুবিধা রয়েছে, যা প্রাথমিক পাঠগুলির একটিতে আলোচনা করা হয়েছে। যদি আপনি এখনও হার্ডওয়্যার প্ল্যাটফর্ম নির্ধারণ না করে থাকেন, তবে [প্রথম প্রকল্পের দ্বিতীয় পাঠ](./1-getting-started/lessons/2-deeper-dive/README.md) পর্যালোচনা করে আপনি কোন প্ল্যাটফর্মটি শিখতে আগ্রহী তা নির্ধারণ করতে পারেন।

এই নির্দিষ্ট হার্ডওয়্যারটি পাঠ এবং অ্যাসাইনমেন্টগুলির জটিলতা কমানোর জন্য বেছে নেওয়া হয়েছে। যদিও অন্যান্য হার্ডওয়্যার কাজ করতে পারে, আমরা গ্যারান্টি দিতে পারি না যে আপনার ডিভাইসে অতিরিক্ত হার্ডওয়্যার ছাড়াই সমস্ত অ্যাসাইনমেন্ট সমর্থিত হবে। উদাহরণস্বরূপ, অনেক Arduino ডিভাইসে WiFi নেই, যা ক্লাউডের সাথে সংযোগ করার জন্য প্রয়োজন - Wio টার্মিনালটি বেছে নেওয়া হয়েছে কারণ এতে বিল্ট-ইন WiFi রয়েছে।

আপনার আরও কিছু অ-প্রযুক্তিগত আইটেমের প্রয়োজন হবে, যেমন মাটি বা একটি গাছের টব, এবং ফল বা সবজি।

## কিট কিনুন

![Seeed studios লোগো](../../translated_images/bn/seeed-logo.74732b6b482b6e8e.webp)

Seeed Studios খুবই সদয়ভাবে সমস্ত হার্ডওয়্যার সহজে কেনার কিট হিসেবে সরবরাহ করেছে:

### Arduino - Wio টার্মিনাল

**[Seeed এবং Microsoft-এর সাথে IoT শিক্ষার্থীদের জন্য - Wio টার্মিনাল স্টার্টার কিট](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)**

[![Wio টার্মিনাল হার্ডওয়্যার কিট](../../translated_images/bn/wio-hardware-kit.4c70c48b85e4283a.webp)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)

### Raspberry Pi

**[Seeed এবং Microsoft-এর সাথে IoT শিক্ষার্থীদের জন্য - Raspberry Pi 4 স্টার্টার কিট](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)**

[![Raspberry Pi টার্মিনাল হার্ডওয়্যার কিট](../../translated_images/bn/pi-hardware-kit.26dbadaedb7dd44c.webp)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)

## Arduino

Arduino-এর জন্য সমস্ত ডিভাইস কোড C++-এ লেখা। সমস্ত অ্যাসাইনমেন্ট সম্পন্ন করতে আপনার নিম্নলিখিত জিনিসগুলির প্রয়োজন হবে:

### Arduino হার্ডওয়্যার

* [Wio টার্মিনাল](https://www.seeedstudio.com/Wio-Terminal-p-4509.html)
* *ঐচ্ছিক* - USB-C কেবল বা USB-A থেকে USB-C অ্যাডাপ্টার। Wio টার্মিনালে একটি USB-C পোর্ট রয়েছে এবং এটি একটি USB-C থেকে USB-A কেবলের সাথে আসে। যদি আপনার পিসি বা ম্যাক-এ শুধুমাত্র USB-C পোর্ট থাকে, তবে আপনার একটি USB-C কেবল বা একটি USB-A থেকে USB-C অ্যাডাপ্টার প্রয়োজন হবে।

### Arduino নির্দিষ্ট সেন্সর এবং অ্যাকচুয়েটর

এগুলি Wio টার্মিনাল Arduino ডিভাইস ব্যবহারের জন্য নির্দিষ্ট এবং Raspberry Pi ব্যবহারের জন্য প্রাসঙ্গিক নয়।

* [ArduCam Mini 2MP Plus - OV2640](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/)
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)
* [ব্রেডবোর্ড জাম্পার তার](https://www.seeedstudio.com/Breadboard-Jumper-Wire-Pack-241mm-200mm-160mm-117m-p-234.html)
* হেডফোন বা ৩.৫ মিমি জ্যাক সহ অন্য কোনো স্পিকার, অথবা একটি JST স্পিকার যেমন:
  * [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
* ১৬ জিবি বা তার কম ক্ষমতার microSD কার্ড, এবং একটি সংযোগকারী যা আপনার কম্পিউটারে SD কার্ড ব্যবহার করতে দেয় যদি এটি বিল্ট-ইন না থাকে। **NOTE** - Wio টার্মিনাল শুধুমাত্র ১৬ জিবি পর্যন্ত SD কার্ড সমর্থন করে, এর বেশি ক্ষমতা সমর্থন করে না।

## Raspberry Pi

Raspberry Pi-এর জন্য সমস্ত ডিভাইস কোড Python-এ লেখা। সমস্ত অ্যাসাইনমেন্ট সম্পন্ন করতে আপনার নিম্নলিখিত জিনিসগুলির প্রয়োজন হবে:

### Raspberry Pi হার্ডওয়্যার

* [Raspberry Pi](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/)
  > 💁 Pi 2B এবং তার পরবর্তী সংস্করণগুলি এই পাঠগুলির অ্যাসাইনমেন্টগুলির সাথে কাজ করবে। যদি আপনি সরাসরি Pi-তে VS Code চালানোর পরিকল্পনা করেন, তবে ২ জিবি বা তার বেশি RAM সহ একটি Pi 4 প্রয়োজন। যদি আপনি Pi-তে দূরবর্তীভাবে অ্যাক্সেস করতে চান, তবে Pi 2B এবং তার পরবর্তী সংস্করণগুলি কাজ করবে।
* microSD কার্ড (আপনি এমন Raspberry Pi কিট পেতে পারেন যা microSD কার্ড সহ আসে), এবং একটি সংযোগকারী যা আপনার কম্পিউটারে SD কার্ড ব্যবহার করতে দেয় যদি এটি বিল্ট-ইন না থাকে।
* USB পাওয়ার সাপ্লাই (আপনি এমন Raspberry Pi 4 কিট পেতে পারেন যা পাওয়ার সাপ্লাই সহ আসে)। যদি আপনি Raspberry Pi 4 ব্যবহার করেন তবে একটি USB-C পাওয়ার সাপ্লাই প্রয়োজন, পূর্ববর্তী ডিভাইসগুলির জন্য একটি মাইক্রো-USB পাওয়ার সাপ্লাই প্রয়োজন।

### Raspberry Pi নির্দিষ্ট সেন্সর এবং অ্যাকচুয়েটর

এগুলি Raspberry Pi ব্যবহারের জন্য নির্দিষ্ট এবং Arduino ডিভাইস ব্যবহারের জন্য প্রাসঙ্গিক নয়।

* [Grove Pi বেস হ্যাট](https://www.seeedstudio.com/Grove-Base-Hat-for-Raspberry-Pi.html)
* [Raspberry Pi ক্যামেরা মডিউল](https://www.raspberrypi.org/products/camera-module-v2/)
* মাইক্রোফোন এবং স্পিকার:

  নিম্নলিখিতগুলির মধ্যে একটি ব্যবহার করুন (বা সমতুল্য):
  * যেকোনো USB মাইক্রোফোন এবং যেকোনো USB স্পিকার, অথবা ৩.৫ মিমি জ্যাক কেবল সহ স্পিকার, অথবা HDMI অডিও আউটপুট ব্যবহার করুন যদি আপনার Raspberry Pi একটি স্পিকার সহ মনিটর বা টিভির সাথে সংযুক্ত থাকে
  * বিল্ট-ইন মাইক্রোফোন সহ যেকোনো USB হেডসেট
  * [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) সহ
    * হেডফোন বা ৩.৫ মিমি জ্যাক সহ অন্য কোনো স্পিকার, অথবা একটি JST স্পিকার যেমন:
    * [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
  * [USB স্পিকারফোন](https://www.amazon.com/USB-Speakerphone-Conference-Business-Microphones/dp/B07Q3D7F8S/ref=sr_1_1?dchild=1&keywords=m0&qid=1614647389&sr=8-1)
* [Grove লাইট সেন্সর](https://www.seeedstudio.com/Grove-Light-Sensor-v1-2-LS06-S-phototransistor.html)
* [Grove বোতাম](https://www.seeedstudio.com/Grove-Button.html)

## সেন্সর এবং অ্যাকচুয়েটর

অধিকাংশ সেন্সর এবং অ্যাকচুয়েটর Arduino এবং Raspberry Pi উভয় শেখার পথেই ব্যবহৃত হয়:

* [Grove LED](https://www.seeedstudio.com/Grove-LED-Pack-p-4364.html) x 2
* [Grove আর্দ্রতা এবং তাপমাত্রা সেন্সর](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html)
* [Grove ক্যাপাসিটিভ মাটি আর্দ্রতা সেন্সর](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html)
* [Grove রিলে](https://www.seeedstudio.com/Grove-Relay.html)
* [Grove GPS (Air530)](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html)
* [Grove টাইম অফ ফ্লাইট ডিস্ট্যান্স সেন্সর](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html)

## ঐচ্ছিক হার্ডওয়্যার

স্বয়ংক্রিয় জল দেওয়ার পাঠগুলি একটি রিলে ব্যবহার করে কাজ করে। একটি বিকল্প হিসাবে, আপনি এই রিলেকে একটি USB দ্বারা চালিত জল পাম্পের সাথে সংযুক্ত করতে পারেন, যা নিচের হার্ডওয়্যার ব্যবহার করে করা যেতে পারে:

* [6V জল পাম্প](https://www.seeedstudio.com/6V-Mini-Water-Pump-p-1945.html)
* [USB টার্মিনাল](https://www.adafruit.com/product/3628)
* সিলিকন পাইপ
* লাল এবং কালো তার
* ছোট ফ্ল্যাট-হেড স্ক্রু ড্রাইভার

## ভার্চুয়াল হার্ডওয়্যার

ভার্চুয়াল হার্ডওয়্যার পদ্ধতিটি সেন্সর এবং অ্যাকচুয়েটরের জন্য সিমুলেটর সরবরাহ করবে, যা Python-এ বাস্তবায়িত। আপনার হার্ডওয়্যারের প্রাপ্যতার উপর নির্ভর করে, আপনি এটি আপনার সাধারণ ডেভেলপমেন্ট ডিভাইসে (যেমন Mac, PC) চালাতে পারেন, অথবা এটি Raspberry Pi-তে চালাতে পারেন এবং শুধুমাত্র সেই হার্ডওয়্যার সিমুলেট করতে পারেন যা আপনার কাছে নেই। উদাহরণস্বরূপ, যদি আপনার কাছে Raspberry Pi ক্যামেরা থাকে কিন্তু Grove সেন্সর না থাকে, তবে আপনি আপনার Pi-তে ভার্চুয়াল ডিভাইস কোড চালাতে পারবেন এবং Grove সেন্সর সিমুলেট করতে পারবেন, কিন্তু একটি বাস্তব ক্যামেরা ব্যবহার করতে পারবেন।

ভার্চুয়াল হার্ডওয়্যার [CounterFit প্রকল্প](https://github.com/CounterFit-IoT/CounterFit) ব্যবহার করবে।

এই পাঠগুলি সম্পন্ন করতে আপনার একটি ওয়েব ক্যাম, মাইক্রোফোন এবং অডিও আউটপুট (যেমন স্পিকার বা হেডফোন) প্রয়োজন হবে। এগুলি বিল্ট-ইন বা বাহ্যিক হতে পারে এবং আপনার অপারেটিং সিস্টেমের সাথে কাজ করার জন্য কনফিগার করা থাকতে হবে এবং সমস্ত অ্যাপ্লিকেশন থেকে ব্যবহারের জন্য উপলব্ধ থাকতে হবে।

---

**অস্বীকৃতি**:  
এই নথিটি AI অনুবাদ পরিষেবা [Co-op Translator](https://github.com/Azure/co-op-translator) ব্যবহার করে অনুবাদ করা হয়েছে। আমরা যথাসম্ভব সঠিকতার জন্য চেষ্টা করি, তবে অনুগ্রহ করে মনে রাখবেন যে স্বয়ংক্রিয় অনুবাদে ত্রুটি বা অসঙ্গতি থাকতে পারে। মূল ভাষায় থাকা নথিটিকে প্রামাণিক উৎস হিসেবে বিবেচনা করা উচিত। গুরুত্বপূর্ণ তথ্যের জন্য, পেশাদার মানব অনুবাদ সুপারিশ করা হয়। এই অনুবাদ ব্যবহারের ফলে কোনো ভুল বোঝাবুঝি বা ভুল ব্যাখ্যা হলে আমরা তার জন্য দায়ী থাকব না।