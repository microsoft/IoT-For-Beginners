<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2625af24587465c5547ae33d6cc000a5",
  "translation_date": "2025-08-27T10:32:13+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/README.md",
  "language_code": "bn"
}
-->
# আপনার ফল শনাক্তকারীকে এজে চালান

![এই পাঠের একটি স্কেচনোট ওভারভিউ](../../../../../translated_images/lesson-17.bc333c3c35ba8e42cce666cfffa82b915f787f455bd94e006aea2b6f2722421a.bn.jpg)

> স্কেচনোট করেছেন [নিত্যা নারাসিমহান](https://github.com/nitya)। বড় সংস্করণের জন্য ছবিতে ক্লিক করুন।

এই ভিডিওটি IoT ডিভাইসে ইমেজ ক্লাসিফায়ার চালানোর ওভারভিউ দেয়, যা এই পাঠে আলোচনা করা হয়েছে।

[![Azure IoT Edge-এ কাস্টম ভিশন AI](https://img.youtube.com/vi/_K5fqGLO8us/0.jpg)](https://www.youtube.com/watch?v=_K5fqGLO8us)

## লেকচারের আগে কুইজ

[লেকচারের আগে কুইজ](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/33)

## ভূমিকা

গত পাঠে আপনি আপনার ইমেজ ক্লাসিফায়ার ব্যবহার করে পাকা এবং কাঁচা ফল চিহ্নিত করেছিলেন, যেখানে IoT ডিভাইসের ক্যামেরা দ্বারা ধারণকৃত ছবি ইন্টারনেটের মাধ্যমে ক্লাউড সার্ভিসে পাঠানো হয়েছিল। এই প্রক্রিয়াগুলি সময়সাপেক্ষ, ব্যয়বহুল এবং আপনি যে ধরনের ইমেজ ডেটা ব্যবহার করছেন তার উপর নির্ভর করে গোপনীয়তার ঝুঁকি থাকতে পারে।

এই পাঠে আপনি শিখবেন কীভাবে এজে - অর্থাৎ ক্লাউডের পরিবর্তে আপনার নিজস্ব নেটওয়ার্কে চলমান IoT ডিভাইসে - মেশিন লার্নিং (ML) মডেল চালানো যায়। আপনি এজ কম্পিউটিং বনাম ক্লাউড কম্পিউটিংয়ের সুবিধা এবং অসুবিধাগুলি, আপনার AI মডেলকে এজে ডিপ্লয় করার পদ্ধতি এবং IoT ডিভাইস থেকে এটি অ্যাক্সেস করার উপায় শিখবেন।

এই পাঠে আমরা আলোচনা করব:

* [এজ কম্পিউটিং](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Azure IoT Edge](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [একটি IoT Edge ডিভাইস নিবন্ধন করুন](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [একটি IoT Edge ডিভাইস সেট আপ করুন](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [আপনার মডেল রপ্তানি করুন](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [ডিপ্লয়মেন্টের জন্য আপনার কন্টেইনার প্রস্তুত করুন](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [আপনার কন্টেইনার ডিপ্লয় করুন](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [আপনার IoT Edge ডিভাইস ব্যবহার করুন](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)

## এজ কম্পিউটিং

এজ কম্পিউটিং হল IoT ডেটা প্রক্রিয়াকরণ যতটা সম্ভব ডেটা উৎপন্ন হওয়ার কাছাকাছি কম্পিউটারে সম্পন্ন করা। এটি ক্লাউডে প্রক্রিয়াকরণের পরিবর্তে ক্লাউডের এজে - আপনার অভ্যন্তরীণ নেটওয়ার্কে স্থানান্তরিত হয়।

![একটি আর্কিটেকচার ডায়াগ্রাম যেখানে ক্লাউডে ইন্টারনেট সার্ভিস এবং একটি স্থানীয় নেটওয়ার্কে IoT ডিভাইস দেখানো হয়েছে](../../../../../translated_images/cloud-without-edge.b4da641f6022c95ed6b91fde8b5323abd2f94e0d52073ad54172ae8f5dac90e9.bn.png)

এখন পর্যন্ত পাঠে, আপনার ডিভাইসগুলি ডেটা সংগ্রহ এবং ক্লাউডে প্রেরণ করে বিশ্লেষণের জন্য, যেখানে সার্ভারলেস ফাংশন বা AI মডেল চালানো হয়।

![একটি আর্কিটেকচার ডায়াগ্রাম যেখানে স্থানীয় নেটওয়ার্কে IoT ডিভাইসগুলি এজ ডিভাইসের সাথে সংযুক্ত এবং সেই এজ ডিভাইসগুলি ক্লাউডের সাথে সংযুক্ত](../../../../../translated_images/cloud-with-edge.1e26462c62c126fe150bd15a5714ddf0be599f09bacbad08b85be02b76ea1ae1.bn.png)

এজ কম্পিউটিংয়ের মাধ্যমে কিছু ক্লাউড সার্ভিস ক্লাউড থেকে সরিয়ে IoT ডিভাইসের সাথে একই নেটওয়ার্কে চলমান কম্পিউটারে স্থানান্তরিত করা হয়, শুধুমাত্র প্রয়োজন হলে ক্লাউডের সাথে যোগাযোগ করা হয়। উদাহরণস্বরূপ, আপনি এজ ডিভাইসে AI মডেল চালিয়ে ফলের পাকা অবস্থার বিশ্লেষণ করতে পারেন এবং শুধুমাত্র বিশ্লেষণ ক্লাউডে পাঠাতে পারেন, যেমন পাকা এবং কাঁচা ফলের সংখ্যা।

✅ চিন্তা করুন: আপনি এখন পর্যন্ত যে IoT অ্যাপ্লিকেশনগুলি তৈরি করেছেন, সেগুলির কোন অংশগুলি এজে স্থানান্তরিত করা যেতে পারে?

### সুবিধাসমূহ

এজ কম্পিউটিংয়ের সুবিধাগুলি হল:

1. **গতি** - এজ কম্পিউটিং সময়-সংবেদনশীল ডেটার জন্য আদর্শ, কারণ কাজগুলি ডিভাইসের সাথে একই নেটওয়ার্কে সম্পন্ন হয়, ইন্টারনেটের মাধ্যমে কল করার পরিবর্তে। এটি উচ্চ গতির সক্ষম করে কারণ অভ্যন্তরীণ নেটওয়ার্কগুলি ইন্টারনেট সংযোগের চেয়ে উল্লেখযোগ্যভাবে দ্রুত গতিতে চলতে পারে এবং ডেটা অনেক কম দূরত্ব অতিক্রম করে।

    > 💁 যদিও ইন্টারনেট সংযোগের জন্য অপটিক্যাল কেবল ব্যবহার করা হয়, যা ডেটাকে আলোর গতিতে ভ্রমণ করতে দেয়, ডেটা ক্লাউড প্রোভাইডারদের কাছে পৌঁছাতে সময় নিতে পারে। উদাহরণস্বরূপ, যদি আপনি ইউরোপ থেকে মার্কিন যুক্তরাষ্ট্রে ক্লাউড সার্ভিসে ডেটা পাঠান, তবে এটি অপটিক্যাল কেবলে আটলান্টিক অতিক্রম করতে কমপক্ষে ২৮ মিলিসেকেন্ড সময় নেয়, এবং এটি ডেটাকে ট্রান্সআটলান্টিক কেবলে পৌঁছানো, বৈদ্যুতিক থেকে আলোর সংকেতে রূপান্তর এবং বিপরীত প্রক্রিয়ার সময় বাদ দিয়ে।

    এজ কম্পিউটিং কম নেটওয়ার্ক ট্রাফিক প্রয়োজন করে, যা ইন্টারনেট সংযোগের সীমিত ব্যান্ডউইথের কারণে কনজেশন থেকে ডেটা ধীর হওয়ার ঝুঁকি হ্রাস করে।

1. **দূরবর্তী অ্যাক্সেসযোগ্যতা** - এজ কম্পিউটিং সীমিত বা কোনো সংযোগ না থাকলে কাজ করে, অথবা সংযোগ অবিরত ব্যবহারের জন্য খুব ব্যয়বহুল। উদাহরণস্বরূপ, মানবিক দুর্যোগপূর্ণ এলাকায় যেখানে অবকাঠামো সীমিত, বা উন্নয়নশীল দেশগুলিতে।

1. **কম খরচ** - এজ ডিভাইসে ডেটা সংগ্রহ, সংরক্ষণ, বিশ্লেষণ এবং ক্রিয়াকলাপ ট্রিগার করা ক্লাউড সার্ভিসের ব্যবহার হ্রাস করে, যা IoT অ্যাপ্লিকেশনের সামগ্রিক খরচ কমাতে পারে। সম্প্রতি এজ কম্পিউটিংয়ের জন্য ডিজাইন করা ডিভাইসগুলির উত্থান ঘটেছে, যেমন [NVIDIA-এর Jetson Nano](https://developer.nvidia.com/embedded/jetson-nano-developer-kit)-এর মতো AI অ্যাক্সিলারেটর বোর্ড, যা US$100-এর কম খরচে GPU-ভিত্তিক হার্ডওয়্যার ব্যবহার করে AI ওয়ার্কলোড চালাতে পারে।

1. **গোপনীয়তা এবং নিরাপত্তা** - এজ কম্পিউটিংয়ের মাধ্যমে ডেটা আপনার নেটওয়ার্কে থাকে এবং ক্লাউডে আপলোড করা হয় না। এটি সংবেদনশীল এবং ব্যক্তিগতভাবে সনাক্তযোগ্য তথ্যের জন্য প্রায়ই পছন্দনীয়, বিশেষত কারণ ডেটা বিশ্লেষণের পরে সংরক্ষণ করার প্রয়োজন হয় না, যা ডেটা লিকের ঝুঁকি উল্লেখযোগ্যভাবে হ্রাস করে। উদাহরণস্বরূপ, চিকিৎসা ডেটা এবং নিরাপত্তা ক্যামেরার ফুটেজ।

1. **অসুরক্ষিত ডিভাইস পরিচালনা** - যদি আপনার ডিভাইসগুলিতে পরিচিত নিরাপত্তা ত্রুটি থাকে যা আপনি সরাসরি আপনার নেটওয়ার্ক বা ইন্টারনেটে সংযুক্ত করতে চান না, তবে আপনি সেগুলিকে একটি পৃথক নেটওয়ার্কে একটি গেটওয়ে IoT Edge ডিভাইসের সাথে সংযুক্ত করতে পারেন। এই এজ ডিভাইসটি তখন আপনার বিস্তৃত নেটওয়ার্ক বা ইন্টারনেটের সাথে সংযোগ রাখতে পারে এবং ডেটা প্রবাহ পরিচালনা করতে পারে।

1. **অসামঞ্জস্যপূর্ণ ডিভাইসের জন্য সমর্থন** - যদি আপনার ডিভাইসগুলি IoT Hub-এ সংযুক্ত হতে না পারে, উদাহরণস্বরূপ, ডিভাইসগুলি শুধুমাত্র HTTP সংযোগ ব্যবহার করে সংযুক্ত হতে পারে বা শুধুমাত্র ব্লুটুথের মাধ্যমে সংযোগ করতে পারে, আপনি একটি IoT Edge ডিভাইসকে গেটওয়ে ডিভাইস হিসাবে ব্যবহার করতে পারেন, যা IoT Hub-এ বার্তা ফরোয়ার্ড করে।

✅ কিছু গবেষণা করুন: এজ কম্পিউটিংয়ের আর কী কী সুবিধা থাকতে পারে?

### অসুবিধাসমূহ

এজ কম্পিউটিংয়ের কিছু অসুবিধা রয়েছে, যেখানে ক্লাউড একটি পছন্দনীয় বিকল্প হতে পারে:

1. **স্কেল এবং নমনীয়তা** - ক্লাউড কম্পিউটিং নেটওয়ার্ক এবং ডেটার চাহিদা অনুযায়ী রিয়েল-টাইমে সার্ভার এবং অন্যান্য রিসোর্স যোগ বা কমাতে পারে। আরও এজ কম্পিউটার যোগ করতে হলে ম্যানুয়ালি আরও ডিভাইস যোগ করতে হয়।

1. **বিশ্বাসযোগ্যতা এবং স্থিতিস্থাপকতা** - ক্লাউড কম্পিউটিং প্রায়ই একাধিক অবস্থানে একাধিক সার্ভার সরবরাহ করে রিডান্ডেন্সি এবং দুর্যোগ পুনরুদ্ধারের জন্য। এজে একই স্তরের রিডান্ডেন্সি পেতে বড় বিনিয়োগ এবং প্রচুর কনফিগারেশন কাজ প্রয়োজন।

1. **রক্ষণাবেক্ষণ** - ক্লাউড সার্ভিস প্রোভাইডাররা সিস্টেম রক্ষণাবেক্ষণ এবং আপডেট সরবরাহ করে।

✅ কিছু গবেষণা করুন: এজ কম্পিউটিংয়ের আর কী কী অসুবিধা থাকতে পারে?

অসুবিধাগুলি মূলত ক্লাউড ব্যবহারের সুবিধার বিপরীত - আপনাকে এই ডিভাইসগুলি নিজে তৈরি এবং পরিচালনা করতে হবে, ক্লাউড প্রোভাইডারদের দক্ষতা এবং স্কেলের উপর নির্ভর করার পরিবর্তে।

কিছু ঝুঁকি এজ কম্পিউটিংয়ের প্রকৃতির দ্বারা প্রশমিত হয়। উদাহরণস্বরূপ, যদি আপনার একটি এজ ডিভাইস একটি কারখানায় মেশিনারি থেকে ডেটা সংগ্রহ করে, তবে আপনাকে কিছু দুর্যোগ পুনরুদ্ধার পরিস্থিতি নিয়ে ভাবতে হবে না। যদি কারখানার বিদ্যুৎ চলে যায়, তবে এজ ডিভাইসের জন্য একটি ব্যাকআপ প্রয়োজন হয় না কারণ মেশিনগুলিও বিদ্যুৎবিহীন থাকবে।

IoT সিস্টেমের জন্য, আপনি প্রায়শই ক্লাউড এবং এজ কম্পিউটিংয়ের একটি মিশ্রণ চান, সিস্টেম, এর গ্রাহক এবং এর রক্ষণাবেক্ষণকারীদের প্রয়োজনের উপর ভিত্তি করে প্রতিটি পরিষেবা ব্যবহার করবেন।

## Azure IoT Edge

![Azure IoT Edge লোগো](../../../../../translated_images/azure-iot-edge-logo.c1c076749b5cba2e8755262fadc2f19ca1146b948d76990b1229199ac2292d79.bn.png)

Azure IoT Edge একটি পরিষেবা যা আপনাকে ক্লাউড থেকে কাজের চাপ এজে স্থানান্তর করতে সাহায্য করতে পারে। আপনি একটি ডিভাইসকে এজ ডিভাইস হিসাবে সেট আপ করেন এবং ক্লাউড থেকে সেই এজ ডিভাইসে কোড ডিপ্লয় করতে পারেন। এটি আপনাকে ক্লাউড এবং এজের ক্ষমতাগুলি মিশ্রিত করার অনুমতি দেয়।

> 🎓 *ওয়ার্কলোড* শব্দটি এমন কোনো পরিষেবার জন্য ব্যবহৃত হয় যা কোনো ধরনের কাজ করে, যেমন AI মডেল, অ্যাপ্লিকেশন বা সার্ভারলেস ফাংশন।

উদাহরণস্বরূপ, আপনি ক্লাউডে একটি ইমেজ ক্লাসিফায়ার প্রশিক্ষণ দিতে পারেন, তারপর ক্লাউড থেকে এটি একটি এজ ডিভাইসে ডিপ্লয় করতে পারেন। আপনার IoT ডিভাইস তখন ইন্টারনেটের মাধ্যমে ছবি পাঠানোর পরিবর্তে এজ ডিভাইসে ছবি পাঠায় ক্লাসিফিকেশনের জন্য। যদি আপনাকে মডেলের একটি নতুন সংস্করণ ডিপ্লয় করতে হয়, আপনি এটি ক্লাউডে প্রশিক্ষণ দিতে পারেন এবং IoT Edge ব্যবহার করে এজ ডিভাইসে নতুন সংস্করণটি আপডেট করতে পারেন।

> 🎓 IoT Edge-এ ডিপ্লয় করা সফটওয়্যারকে *মডিউল* বলা হয়। ডিফল্টভাবে IoT Edge IoT Hub-এর সাথে যোগাযোগকারী মডিউল চালায়, যেমন `edgeAgent` এবং `edgeHub` মডিউল। যখন আপনি একটি ইমেজ ক্লাসিফায়ার ডিপ্লয় করেন, এটি একটি অতিরিক্ত মডিউল হিসাবে ডিপ্লয় করা হয়।

IoT Edge IoT Hub-এ অন্তর্ভুক্ত, তাই আপনি IoT ডিভাইস পরিচালনার জন্য যে পরিষেবা ব্যবহার করবেন তা ব্যবহার করে এজ ডিভাইস পরিচালনা করতে পারেন, একই স্তরের নিরাপত্তার সাথে।

IoT Edge কোড চালায় *কন্টেইনার* থেকে - স্বয়ংসম্পূর্ণ অ্যাপ্লিকেশন যা আপনার কম্পিউটারে অন্যান্য অ্যাপ্লিকেশন থেকে আলাদাভাবে চালানো হয়। যখন আপনি একটি কন্টেইনার চালান, এটি আপনার কম্পিউটারের ভিতরে একটি পৃথক কম্পিউটারের মতো কাজ করে, যার নিজস্ব সফটওয়্যার, পরিষেবা এবং অ্যাপ্লিকেশন চালায়। বেশিরভাগ সময় কন্টেইনারগুলি আপনার কম্পিউটারে কিছু অ্যাক্সেস করতে পারে না যতক্ষণ না আপনি ইচ্ছাকৃতভাবে একটি ফোল্ডারের মতো কিছু শেয়ার করেন। কন্টেইনারটি তখন একটি ওপেন পোর্টের মাধ্যমে পরিষেবাগুলি উন্মুক্ত করে যা আপনি সংযোগ করতে বা আপনার নেটওয়ার্কে উন্মুক্ত করতে পারেন।

![একটি ওয়েব অনুরোধ একটি কন্টেইনারে পুনঃনির্দেশিত](../../../../../translated_images/container-web-browser.4ee81dd4f0d8838ce622b2a0d600b6a4322b5d4fe43159facd87b7b34f84d66a.bn.png)

উদাহরণস্বরূপ, আপনি একটি কন্টেইনারে একটি ওয়েবসাইট চালাতে পারেন পোর্ট ৮০-এ, যা ডিফল্ট HTTP পোর্ট, এবং তারপর এটি আপনার কম্পিউটারে পোর্ট ৮০-এও উন্মুক্ত করতে পারেন।

✅ কিছু গবেষণা করুন: কন্টেইনার এবং Docker বা Moby-এর মতো পরিষেবাগুলি সম্পর্কে পড়ুন।

আপনি Custom Vision ব্যবহার করে ইমেজ ক্লাসিফায়ার ডাউনলোড করতে পারেন এবং সেগুলিকে কন্টেইনার হিসাবে ডিপ্লয় করতে পারেন, হয় সরাসরি একটি ডিভাইসে চালিয়ে বা IoT Edge-এর মাধ্যমে ডিপ্লয় করে। একবার সেগুলি একটি কন্টেইনারে চালু হলে, সেগুলি একই REST API ব্যবহার করে অ্যাক্সেস করা যেতে পারে যা ক্লাউড সংস্করণের জন্য ব্যবহৃত হয়, তবে এন্ডপয়েন্টটি কন্টেইনার চালানো এজ ডিভাইসের দিকে নির্দেশ করে।

## একটি IoT Edge ডিভাইস নিবন্ধন করুন

IoT Edge ডিভাইস ব্যবহার করতে, এটি IoT Hub-এ নিবন্ধিত হতে হবে।

### কাজ - একটি IoT Edge ডিভাইস নিবন্ধন করুন

1. `fruit-quality-detector` রিসোর্স গ্রুপে একটি IoT Hub তৈরি করুন। এটিকে `fruit-quality-detector` ভিত্তিক একটি অনন্য নাম দিন।

1. আপনার IoT Hub-এ `fruit-quality-detector-edge` নামে একটি IoT Edge ডিভাইস নিবন্ধন করুন। এটি নিবন্ধনের জন্য কমান্ডটি একটি নন-এজ ডিভাইস নিবন্ধনের জন্য ব্যবহৃত কমান্ডের মতো, তবে আপনাকে `--edge-enabled` ফ্ল্যাগটি পাস করতে হবে।

    ```sh
    az iot hub device-identity create --edge-enabled \
                                      --device-id fruit-quality-detector-edge \
                                      --hub-name <hub_name>
    ```

    `<hub_name>`-এর জায়গায় আপনার IoT Hub-এর নাম দিন।

1. আপনার ডিভাইসের জন্য সংযোগ স্ট্রিং পেতে নিম্নলিখিত কমান্ডটি ব্যবহার করুন:

    ```sh
    az iot hub device-identity connection-string show --device-id fruit-quality-detector-edge \
                                                      --output table \
                                                      --hub-name <hub_name>
    ```

    `<hub_name>`-এর জায়গায় আপনার IoT Hub-এর নাম দিন।

    আউটপুটে প্রদর্শিত সংযোগ স্ট্রিংটি কপি করে রাখুন।

## একটি IoT Edge ডিভাইস সেট আপ করুন

একবার আপনি আপনার IoT Hub-এ এজ ডিভাইস নিবন্ধন তৈরি করলে, আপনি এজ ডিভাইস সেট আপ করতে পারেন।

### কাজ - IoT Edge Runtime ইনস্টল এবং শুরু করুন

**IoT Edge Runtime শুধুমাত্র Linux কন্টেইনার চালায়।** এটি Linux-এ চালানো যেতে পারে, অথবা Windows-এ Linux Virtual Machines ব্যবহার করে চালানো যেতে পারে।

* যদি আপনি একটি Raspberry Pi IoT ডিভাইস হিসাবে ব্যবহার করেন, তবে এটি একটি সমর্থিত Linux সংস্করণ চালায় এবং IoT Edge Runtime হোস্ট করতে পারে। [Microsoft ডকস-এ Linux-এর জন্য Azure IoT Edge ইনস্টল করার গাইড](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge?WT.mc_id=academic-17441-jabenn) অনুসরণ করে IoT Edge ইনস্টল করুন এবং সংযোগ স্ট্রিং সেট করুন।

    > 💁 মনে রাখবেন, Raspberry Pi OS হল Debian Linux-এর একটি ভেরিয়েন্ট।

* যদি আপনি Raspberry Pi ব্যবহার না করেন, তবে একটি Linux কম্পিউটার থাকে, আপনি IoT Edge Runtime চালাতে পারেন। [Microsoft ডকস-এ Linux-এর জন্য Azure IoT Edge ইনস্টল করার গাইড](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge?WT.mc_id=academic-17441-jabenn) অনুসরণ করে IoT Edge ইনস্টল করুন এবং সংযোগ স্ট্রিং সেট করুন।

* যদি আপনি Windows ব্যবহার করেন, আপনি একটি Linux Virtual Machine-এ IoT Edge Runtime ইনস্টল করতে পারেন। [Microsoft ডকস-এ Windows ডিভাইসে IoT Edge মডিউল ডিপ্লয় করার দ্রুত শুরু গাইডের IoT Edge Runtime ইনস্টল এবং শুরু করার অংশ](https://docs.microsoft.com/azure/iot-edge/quickstart?WT.mc_id=academic-17441-jab
1. [CustomVision.ai](https://customvision.ai) পোর্টালে যান এবং সাইন ইন করুন যদি এটি ইতিমধ্যে খোলা না থাকে। এরপর আপনার `fruit-quality-detector` প্রজেক্টটি খুলুন।

1. **Settings** বোতামটি (⚙ আইকন) নির্বাচন করুন।

1. *Domains* তালিকা থেকে *Food (compact)* নির্বাচন করুন।

1. *Export Capabilities* এর অধীনে নিশ্চিত করুন যে *Basic platforms (Tensorflow, CoreML, ONNX, ...)* নির্বাচন করা আছে।

1. Settings পৃষ্ঠার নিচে **Save Changes** নির্বাচন করুন।

1. **Train** বোতামটি ব্যবহার করে মডেলটি পুনরায় প্রশিক্ষণ দিন, *Quick training* নির্বাচন করুন।

### কাজ - আপনার মডেল রপ্তানি করুন

মডেলটি প্রশিক্ষিত হওয়ার পর, এটি একটি কন্টেইনার হিসেবে রপ্তানি করতে হবে।

1. **Performance** ট্যাবটি নির্বাচন করুন এবং আপনার সর্বশেষ iteration খুঁজুন যা compact domain ব্যবহার করে প্রশিক্ষিত হয়েছে।

1. উপরে **Export** বোতামটি নির্বাচন করুন।

1. **DockerFile** নির্বাচন করুন, তারপর আপনার edge ডিভাইসের সাথে মিলে এমন একটি সংস্করণ নির্বাচন করুন:

    * যদি আপনি IoT Edge একটি Linux কম্পিউটার, Windows কম্পিউটার বা Virtual Machine-এ চালান, তাহলে *Linux* সংস্করণটি নির্বাচন করুন।
    * যদি আপনি IoT Edge একটি Raspberry Pi-তে চালান, তাহলে *ARM (Raspberry Pi 3)* সংস্করণটি নির্বাচন করুন।

> 🎓 Docker হলো কন্টেইনার ব্যবস্থাপনার জন্য সবচেয়ে জনপ্রিয় টুলগুলোর একটি, এবং DockerFile হলো কন্টেইনার সেটআপ করার নির্দেশাবলীর একটি সেট।

1. **Export** নির্বাচন করুন যাতে Custom Vision প্রাসঙ্গিক ফাইল তৈরি করে, তারপর **Download** নির্বাচন করুন এবং সেগুলো একটি zip ফাইলে ডাউনলোড করুন।

1. ফাইলগুলো আপনার কম্পিউটারে সংরক্ষণ করুন এবং ফোল্ডারটি আনজিপ করুন।

## আপনার কন্টেইনার ডিপ্লয়মেন্টের জন্য প্রস্তুত করুন

![কন্টেইনার তৈরি হয়, তারপর একটি কন্টেইনার রেজিস্ট্রিতে পুশ করা হয়, তারপর IoT Edge ব্যবহার করে edge ডিভাইসে ডিপ্লয় করা হয়](../../../../../translated_images/container-edge-flow.c246050dd60ceefdb6ace026a4ce5c6aa4112bb5898ae23fbb2ab4be29ae3e1b.bn.png)

আপনার মডেল ডাউনলোড করার পর, এটি একটি কন্টেইনারে তৈরি করতে হবে, তারপর একটি কন্টেইনার রেজিস্ট্রিতে পুশ করতে হবে - একটি অনলাইন অবস্থান যেখানে আপনি কন্টেইনার সংরক্ষণ করতে পারেন। IoT Edge তারপর রেজিস্ট্রি থেকে কন্টেইনারটি ডাউনলোড করতে পারে এবং এটি আপনার ডিভাইসে পুশ করতে পারে।

![Azure Container Registry লোগো](../../../../../translated_images/azure-container-registry-logo.09494206991d4b295025ebff7d4e2900325e527a59184ffbc8464b6ab59654be.bn.png)

এই পাঠের জন্য আপনি যে কন্টেইনার রেজিস্ট্রি ব্যবহার করবেন তা হলো Azure Container Registry। এটি একটি ফ্রি সার্ভিস নয়, তাই অর্থ সাশ্রয়ের জন্য কাজ শেষ হলে নিশ্চিত করুন যে আপনি [আপনার প্রজেক্ট পরিষ্কার করুন](../../../clean-up.md)।

> 💁 Azure Container Registry ব্যবহারের খরচ দেখতে [Azure Container Registry মূল্য নির্ধারণ পৃষ্ঠা](https://azure.microsoft.com/pricing/details/container-registry/?WT.mc_id=academic-17441-jabenn) দেখুন।

### কাজ - Docker ইনস্টল করুন

ক্লাসিফায়ার তৈরি এবং ডিপ্লয় করতে, আপনাকে [Docker](https://www.docker.com/) ইনস্টল করতে হতে পারে।

আপনার কন্টেইনারটি এমন একটি ডিভাইস থেকে তৈরি করার পরিকল্পনা থাকলে যা IoT Edge ইনস্টল করা ডিভাইস থেকে আলাদা, তাহলে আপনাকে Docker ইনস্টল করতে হবে - IoT Edge ইনস্টল করার অংশ হিসেবে Docker ইতিমধ্যে ইনস্টল করা থাকে।

1. যদি আপনি Docker কন্টেইনারটি IoT Edge ডিভাইস থেকে আলাদা ডিভাইসে তৈরি করছেন, তাহলে [Docker ইনস্টল পৃষ্ঠা](https://www.docker.com/products/docker-desktop)-এর নির্দেশাবলী অনুসরণ করে Docker Desktop বা Docker engine ইনস্টল করুন। ইনস্টলেশনের পরে নিশ্চিত করুন এটি চালু আছে।

### কাজ - একটি কন্টেইনার রেজিস্ট্রি রিসোর্স তৈরি করুন

1. আপনার টার্মিনাল বা কমান্ড প্রম্পট থেকে নিম্নলিখিত কমান্ডটি চালান একটি Azure Container Registry রিসোর্স তৈরি করতে:

    ```sh
    az acr create --resource-group fruit-quality-detector \
                  --sku Basic \
                  --name <Container registry name>
    ```

    `<Container registry name>`-এর জায়গায় আপনার কন্টেইনার রেজিস্ট্রির জন্য একটি ইউনিক নাম দিন, শুধুমাত্র অক্ষর এবং সংখ্যা ব্যবহার করে। এটি `fruitqualitydetector` এর উপর ভিত্তি করে তৈরি করুন। এই নামটি কন্টেইনার রেজিস্ট্রিতে অ্যাক্সেস করার URL-এর অংশ হয়ে যায়, তাই এটি গ্লোবালি ইউনিক হতে হবে।

1. নিম্নলিখিত কমান্ডটি ব্যবহার করে Azure Container Registry-তে লগ ইন করুন:

    ```sh
    az acr login --name <Container registry name>
    ```

    `<Container registry name>`-এর জায়গায় আপনার কন্টেইনার রেজিস্ট্রির নাম দিন।

1. কন্টেইনার রেজিস্ট্রিকে অ্যাডমিন মোডে সেট করুন যাতে আপনি একটি পাসওয়ার্ড জেনারেট করতে পারেন, নিম্নলিখিত কমান্ডটি ব্যবহার করে:

    ```sh
    az acr update --admin-enabled true \
                 --name <Container registry name>
    ```

    `<Container registry name>`-এর জায়গায় আপনার কন্টেইনার রেজিস্ট্রির নাম দিন।

1. আপনার কন্টেইনার রেজিস্ট্রির জন্য পাসওয়ার্ড জেনারেট করুন নিম্নলিখিত কমান্ডটি ব্যবহার করে:

    ```sh
     az acr credential renew --password-name password \
                             --output table \
                             --name <Container registry name>
    ```

    `<Container registry name>`-এর জায়গায় আপনার কন্টেইনার রেজিস্ট্রির নাম দিন।

    `PASSWORD` এর মান কপি করে রাখুন, কারণ এটি পরে প্রয়োজন হবে।

### কাজ - আপনার কন্টেইনার তৈরি করুন

Custom Vision থেকে আপনি যা ডাউনলোড করেছেন তা হলো একটি DockerFile, যা কন্টেইনার কীভাবে তৈরি হবে তার নির্দেশাবলী ধারণ করে, এবং অ্যাপ্লিকেশন কোড যা কন্টেইনারের ভিতরে চালানো হবে আপনার Custom Vision মডেল হোস্ট করতে এবং একটি REST API কল করার জন্য। Docker ব্যবহার করে আপনি DockerFile থেকে একটি ট্যাগযুক্ত কন্টেইনার তৈরি করতে পারেন, তারপর এটি আপনার কন্টেইনার রেজিস্ট্রিতে পুশ করতে পারেন।

> 🎓 কন্টেইনারগুলোকে একটি ট্যাগ দেওয়া হয় যা তাদের নাম এবং সংস্করণ সংজ্ঞায়িত করে। যখন আপনাকে একটি কন্টেইনার আপডেট করতে হবে, তখন আপনি একই ট্যাগ ব্যবহার করে এটি তৈরি করতে পারেন কিন্তু একটি নতুন সংস্করণে।

1. আপনার টার্মিনাল বা কমান্ড প্রম্পট খুলুন এবং Custom Vision থেকে ডাউনলোড করা আনজিপ করা মডেলে নেভিগেট করুন।

1. নিম্নলিখিত কমান্ডটি চালান ইমেজ তৈরি এবং ট্যাগ করতে:

    ```sh
    docker build --platform <platform> -t <Container registry name>.azurecr.io/classifier:v1 .
    ```

    `<platform>`-এর জায়গায় সেই প্ল্যাটফর্মটি দিন যেখানে এই কন্টেইনারটি চলবে। যদি আপনি IoT Edge একটি Raspberry Pi-তে চালান, এটি `linux/armhf` সেট করুন, অন্যথায় এটি `linux/amd64` সেট করুন।

    > 💁 যদি আপনি এই কমান্ডটি IoT Edge চলমান ডিভাইস থেকে চালান, যেমন Raspberry Pi থেকে চালান, তাহলে `--platform <platform>` অংশটি বাদ দিতে পারেন কারণ এটি ডিফল্টভাবে বর্তমান প্ল্যাটফর্মে সেট হয়।

    `<Container registry name>`-এর জায়গায় আপনার কন্টেইনার রেজিস্ট্রির নাম দিন।

    > 💁 যদি আপনি Linux বা Raspberry Pi OS-এ চালান, তাহলে এই কমান্ডটি চালানোর জন্য আপনাকে `sudo` ব্যবহার করতে হতে পারে।

    Docker ইমেজ তৈরি করবে, প্রয়োজনীয় সমস্ত সফটওয়্যার কনফিগার করবে। ইমেজটি `classifier:v1` নামে ট্যাগ করা হবে।

    ```output
    ➜  d4ccc45da0bb478bad287128e1274c3c.DockerFile.Linux docker build --platform linux/amd64 -t  fruitqualitydetectorjimb.azurecr.io/classifier:v1 .
    [+] Building 102.4s (11/11) FINISHED
     => [internal] load build definition from Dockerfile
     => => transferring dockerfile: 131B
     => [internal] load .dockerignore
     => => transferring context: 2B
     => [internal] load metadata for docker.io/library/python:3.7-slim
     => [internal] load build context
     => => transferring context: 905B
     => [1/6] FROM docker.io/library/python:3.7-slim@sha256:b21b91c9618e951a8cbca5b696424fa5e820800a88b7e7afd66bba0441a764d6
     => => resolve docker.io/library/python:3.7-slim@sha256:b21b91c9618e951a8cbca5b696424fa5e820800a88b7e7afd66bba0441a764d6
     => => sha256:b4d181a07f8025e00e0cb28f1cc14613da2ce26450b80c54aea537fa93cf3bda 27.15MB / 27.15MB
     => => sha256:de8ecf497b753094723ccf9cea8a46076e7cb845f333df99a6f4f397c93c6ea9 2.77MB / 2.77MB
     => => sha256:707b80804672b7c5d8f21e37c8396f319151e1298d976186b4f3b76ead9f10c8 10.06MB / 10.06MB
     => => sha256:b21b91c9618e951a8cbca5b696424fa5e820800a88b7e7afd66bba0441a764d6 1.86kB / 1.86kB
     => => sha256:44073386687709c437586676b572ff45128ff1f1570153c2f727140d4a9accad 1.37kB / 1.37kB
     => => sha256:3d94f0f2ca798607808b771a7766f47ae62a26f820e871dd488baeccc69838d1 8.31kB / 8.31kB
     => => sha256:283715715396fd56d0e90355125fd4ec57b4f0773f306fcd5fa353b998beeb41 233B / 233B
     => => sha256:8353afd48f6b84c3603ea49d204bdcf2a1daada15f5d6cad9cc916e186610a9f 2.64MB / 2.64MB
     => => extracting sha256:b4d181a07f8025e00e0cb28f1cc14613da2ce26450b80c54aea537fa93cf3bda
     => => extracting sha256:de8ecf497b753094723ccf9cea8a46076e7cb845f333df99a6f4f397c93c6ea9
     => => extracting sha256:707b80804672b7c5d8f21e37c8396f319151e1298d976186b4f3b76ead9f10c8
     => => extracting sha256:283715715396fd56d0e90355125fd4ec57b4f0773f306fcd5fa353b998beeb41
     => => extracting sha256:8353afd48f6b84c3603ea49d204bdcf2a1daada15f5d6cad9cc916e186610a9f
     => [2/6] RUN pip install -U pip
     => [3/6] RUN pip install --no-cache-dir numpy~=1.17.5 tensorflow~=2.0.2 flask~=1.1.2 pillow~=7.2.0
     => [4/6] RUN pip install --no-cache-dir mscviplib==2.200731.16
     => [5/6] COPY app /app
     => [6/6] WORKDIR /app
     => exporting to image
     => => exporting layers
     => => writing image sha256:1846b6f134431f78507ba7c079358ed66d944c0e185ab53428276bd822400386
     => => naming to fruitqualitydetectorjimb.azurecr.io/classifier:v1
    ```

### কাজ - আপনার কন্টেইনার কন্টেইনার রেজিস্ট্রিতে পুশ করুন

1. নিম্নলিখিত কমান্ডটি ব্যবহার করে আপনার কন্টেইনারটি কন্টেইনার রেজিস্ট্রিতে পুশ করুন:

    ```sh
    docker push <Container registry name>.azurecr.io/classifier:v1
    ```

    `<Container registry name>`-এর জায়গায় আপনার কন্টেইনার রেজিস্ট্রির নাম দিন।

    > 💁 যদি আপনি Linux চালান, তাহলে এই কমান্ডটি চালানোর জন্য আপনাকে `sudo` ব্যবহার করতে হতে পারে।

    কন্টেইনারটি কন্টেইনার রেজিস্ট্রিতে পুশ করা হবে।

    ```output
    ➜  d4ccc45da0bb478bad287128e1274c3c.DockerFile.Linux docker push fruitqualitydetectorjimb.azurecr.io/classifier:v1
    The push refers to repository [fruitqualitydetectorjimb.azurecr.io/classifier]
    5f70bf18a086: Pushed 
    8a1ba9294a22: Pushed 
    56cf27184a76: Pushed 
    b32154f3f5dd: Pushed 
    36103e9a3104: Pushed 
    e2abb3cacca0: Pushed 
    4213fd357bbe: Pushed 
    7ea163ba4dce: Pushed 
    537313a13d90: Pushed 
    764055ebc9a7: Pushed 
    v1: digest: sha256:ea7894652e610de83a5a9e429618e763b8904284253f4fa0c9f65f0df3a5ded8 size: 2423
    ```

1. পুশটি যাচাই করতে, আপনি নিম্নলিখিত কমান্ডটি ব্যবহার করে আপনার রেজিস্ট্রিতে কন্টেইনারগুলোর তালিকা দেখতে পারেন:

    ```sh
    az acr repository list --output table \
                           --name <Container registry name> 
    ```

    `<Container registry name>`-এর জায়গায় আপনার কন্টেইনার রেজিস্ট্রির নাম দিন।

    ```output
    ➜  d4ccc45da0bb478bad287128e1274c3c.DockerFile.Linux az acr repository list --name fruitqualitydetectorjimb --output table
    Result
    ----------
    classifier
    ```

    আউটপুটে আপনার ক্লাসিফায়ারটি তালিকাভুক্ত দেখতে পাবেন।

## আপনার কন্টেইনার ডিপ্লয় করুন

আপনার কন্টেইনারটি এখন আপনার IoT Edge ডিভাইসে ডিপ্লয় করা যেতে পারে। ডিপ্লয় করতে আপনাকে একটি ডিপ্লয়মেন্ট ম্যানিফেস্ট তৈরি করতে হবে - একটি JSON ডকুমেন্ট যা edge ডিভাইসে ডিপ্লয় করা মডিউলগুলোর তালিকা ধারণ করে।

### কাজ - ডিপ্লয়মেন্ট ম্যানিফেস্ট তৈরি করুন

1. আপনার কম্পিউটারে কোথাও একটি নতুন ফাইল তৈরি করুন যার নাম `deployment.json`।

1. এই ফাইলটিতে নিম্নলিখিত যোগ করুন:

    ```json
    {
        "content": {
            "modulesContent": {
                "$edgeAgent": {
                    "properties.desired": {
                        "schemaVersion": "1.1",
                        "runtime": {
                            "type": "docker",
                            "settings": {
                                "minDockerVersion": "v1.25",
                                "loggingOptions": "",
                                "registryCredentials": {
                                    "ClassifierRegistry": {
                                        "username": "<Container registry name>",
                                        "password": "<Container registry password>",
                                        "address": "<Container registry name>.azurecr.io"
                                      }
                                }
                            }
                        },
                        "systemModules": {
                            "edgeAgent": {
                                "type": "docker",
                                "settings": {
                                    "image": "mcr.microsoft.com/azureiotedge-agent:1.1",
                                    "createOptions": "{}"
                                }
                            },
                            "edgeHub": {
                                "type": "docker",
                                "status": "running",
                                "restartPolicy": "always",
                                "settings": {
                                    "image": "mcr.microsoft.com/azureiotedge-hub:1.1",
                                    "createOptions": "{\"HostConfig\":{\"PortBindings\":{\"5671/tcp\":[{\"HostPort\":\"5671\"}],\"8883/tcp\":[{\"HostPort\":\"8883\"}],\"443/tcp\":[{\"HostPort\":\"443\"}]}}}"
                                }
                            }
                        },
                        "modules": {
                            "ImageClassifier": {
                                "version": "1.0",
                                "type": "docker",
                                "status": "running",
                                "restartPolicy": "always",
                                "settings": {
                                    "image": "<Container registry name>.azurecr.io/classifier:v1",
                                    "createOptions": "{\"ExposedPorts\": {\"80/tcp\": {}},\"HostConfig\": {\"PortBindings\": {\"80/tcp\": [{\"HostPort\": \"80\"}]}}}"
                                }
                            }
                        }
                    }
                },
                "$edgeHub": {
                    "properties.desired": {
                        "schemaVersion": "1.1",
                        "routes": {
                            "upstream": "FROM /messages/* INTO $upstream"
                        },
                        "storeAndForwardConfiguration": {
                            "timeToLiveSecs": 7200
                        }
                    }
                }
            }
        }
    }
    ```

    > 💁 আপনি এই ফাইলটি [code-deployment/deployment](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-deployment/deployment) ফোল্ডারে খুঁজে পেতে পারেন।

    `<Container registry name>`-এর তিনটি উদাহরণ প্রতিস্থাপন করুন আপনার কন্টেইনার রেজিস্ট্রির নাম দিয়ে। একটি `ImageClassifier` মডিউল সেকশনে, অন্য দুটি `registryCredentials` সেকশনে।

    `registryCredentials` সেকশনে `<Container registry password>`-এর জায়গায় আপনার কন্টেইনার রেজিস্ট্রির পাসওয়ার্ড দিন।

1. আপনার ডিপ্লয়মেন্ট ম্যানিফেস্ট ধারণকারী ফোল্ডার থেকে নিম্নলিখিত কমান্ডটি চালান:

    ```sh
    az iot edge set-modules --device-id fruit-quality-detector-edge \
                            --content deployment.json \
                            --hub-name <hub_name>
    ```

    `<hub_name>`-এর জায়গায় আপনার IoT Hub-এর নাম দিন।

    ইমেজ ক্লাসিফায়ার মডিউলটি আপনার edge ডিভাইসে ডিপ্লয় করা হবে।

### কাজ - ক্লাসিফায়ারটি চালু আছে কিনা যাচাই করুন

1. IoT Edge ডিভাইসে সংযোগ করুন:

    * যদি আপনি IoT Edge চালানোর জন্য একটি Raspberry Pi ব্যবহার করেন, তাহলে আপনার টার্মিনাল থেকে ssh ব্যবহার করে সংযোগ করুন অথবা VS Code-এ একটি রিমোট SSH সেশনের মাধ্যমে সংযোগ করুন।
    * যদি আপনি IoT Edge একটি Linux কন্টেইনারে Windows-এ চালান, তাহলে [সফল কনফিগারেশন যাচাই গাইড](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge-on-windows?WT.mc_id=academic-17441-jabenn&view=iotedge-2018-06&tabs=powershell#verify-successful-configuration)-এর ধাপগুলো অনুসরণ করুন IoT Edge ডিভাইসে সংযোগ করতে।
    * যদি আপনি IoT Edge একটি ভার্চুয়াল মেশিনে চালান, তাহলে VM তৈরি করার সময় সেট করা `adminUsername` এবং `password` ব্যবহার করে মেশিনে SSH করুন, এবং IP ঠিকানা বা DNS নাম ব্যবহার করুন:

        ```sh
        ssh <adminUsername>@<IP address>
        ```

        অথবা:

        ```sh
        ssh <adminUsername>@<DNS Name>
        ```

        প্রম্পট দেওয়া হলে আপনার পাসওয়ার্ড লিখুন।

1. সংযুক্ত হওয়ার পর, IoT Edge মডিউলগুলোর তালিকা পেতে নিম্নলিখিত কমান্ডটি চালান:

    ```sh
    iotedge list
    ```

    > 💁 এই কমান্ডটি চালানোর জন্য আপনাকে `sudo` ব্যবহার করতে হতে পারে।

    আপনি চলমান মডিউলগুলো দেখতে পাবেন:

    ```output
    jim@fruit-quality-detector-jimb:~$ iotedge list
    NAME             STATUS           DESCRIPTION      CONFIG
    ImageClassifier  running          Up 42 minutes    fruitqualitydetectorjimb.azurecr.io/classifier:v1
    edgeAgent        running          Up 42 minutes    mcr.microsoft.com/azureiotedge-agent:1.1
    edgeHub          running          Up 42 minutes    mcr.microsoft.com/azureiotedge-hub:1.1
    ```

1. Image classifier মডিউলের লগ চেক করতে নিম্নলিখিত কমান্ডটি চালান:

    ```sh
    iotedge logs ImageClassifier
    ```

    > 💁 এই কমান্ডটি চালানোর জন্য আপনাকে `sudo` ব্যবহার করতে হতে পারে।

    ```output
    jim@fruit-quality-detector-jimb:~$ iotedge logs ImageClassifier
    2021-07-05 20:30:15.387144: I tensorflow/core/platform/cpu_feature_guard.cc:142] Your CPU supports instructions that this TensorFlow binary was not compiled to use: AVX2 FMA
    2021-07-05 20:30:15.392185: I tensorflow/core/platform/profile_utils/cpu_utils.cc:94] CPU Frequency: 2394450000 Hz
    2021-07-05 20:30:15.392712: I tensorflow/compiler/xla/service/service.cc:168] XLA service 0x55ed9ac83470 executing computations on platform Host. Devices:
    2021-07-05 20:30:15.392806: I tensorflow/compiler/xla/service/service.cc:175]   StreamExecutor device (0): Host, Default Version
    Loading model...Success!
    Loading labels...2 found. Success!
     * Serving Flask app "app" (lazy loading)
     * Environment: production
       WARNING: This is a development server. Do not use it in a production deployment.
       Use a production WSGI server instead.
     * Debug mode: off
     * Running on http://0.0.0.0:80/ (Press CTRL+C to quit)
    ```

### কাজ - ইমেজ ক্লাসিফায়ার পরীক্ষা করুন

1. আপনি CURL ব্যবহার করে ইমেজ ক্লাসিফায়ার পরীক্ষা করতে পারেন IoT Edge এজেন্ট চালানো কম্পিউটারের IP ঠিকানা বা হোস্ট নাম ব্যবহার করে। IP ঠিকানা খুঁজুন:

    * যদি আপনি IoT Edge চালানো একই মেশিনে থাকেন, তাহলে হোস্ট নাম হিসেবে `localhost` ব্যবহার করতে পারেন।
    * যদি আপনি একটি VM ব্যবহার করেন, তাহলে VM-এর IP ঠিকানা বা DNS নাম ব্যবহার করতে পারেন।
    * অন্যথায় IoT Edge চালানো মেশিনের IP ঠিকানা পেতে পারেন:
      * Windows 10-এ, [আপনার IP ঠিকানা খুঁজুন গাইড](https://support.microsoft.com/windows/find-your-ip-address-f21a9bbc-c582-55cd-35e0-73431160a1b9?WT.mc_id=academic-17441-jabenn) অনুসরণ করুন।
      * macOS-এ, [Mac-এ আপনার IP ঠিকানা কীভাবে খুঁজে পাবেন গাইড](https://www.hellotech.com/guide/for/how-to-find-ip-address-on-mac) অনুসরণ করুন।
      * Linux-এ, [Linux-এ আপনার IP ঠিকানা কীভাবে খুঁজে পাবেন গাইড](https://opensource.com/article/18/5/how-find-ip-address-linux)-এর প্রাইভেট IP ঠিকানা খুঁজে পাওয়ার সেকশন অনুসরণ করুন।

1. আপনি একটি স্থানীয় ফাইল দিয়ে কন্টেইনার পরীক্ষা করতে নিম্নলিখিত curl কমান্ডটি চালাতে পারেন:

    ```sh
    curl --location \
         --request POST 'http://<IP address or name>/image' \
         --header 'Content-Type: image/png' \
         --data-binary '@<file_Name>' 
    ```

    `<IP address or name>`-এর জায়গায় IoT Edge চালানো কম্পিউটারের IP ঠিকানা বা হোস্ট নাম দিন। `<file_Name>`-এর জায়গায় পরীক্ষার জন্য ফাইলের নাম দিন।

    আউটপুটে আপনি পূর্বাভাসের ফলাফল দেখতে পাবেন:

    ```output
    {
        "created": "2021-07-05T21:44:39.573181",
        "id": "",
        "iteration": "",
        "predictions": [
            {
                "boundingBox": null,
                "probability": 0.9995615482330322,
                "tagId": "",
                "tagName": "ripe"
            },
            {
                "boundingBox": null,
                "probability": 0.0004384400090202689,
                "tagId": "",
                "tagName": "unripe"
            }
        ],
        "project": ""
    }
    ```

    > 💁 এখানে পূর্বাভাসের কী সরবরাহ করার প্রয়োজন নেই, কারণ এটি একটি Azure রিসোর্স ব্যবহার করছে না। পরিবর্তে নিরাপত্তা অভ্যন্তরীণ নেটওয়ার্কে অভ্যন্তরীণ নিরাপত্তার প্রয়োজনীয়তার উপর ভিত্তি করে কনফিগার করা হবে, একটি পাবলিক এন্ডপয়েন্ট এবং API কী-এর উপর নির্ভর না করে।

## আপনার IoT Edge ডিভাইস ব্যবহার করুন

এখন আপনার Image Classifier একটি IoT Edge ডিভাইসে ডিপ্লয় করা হয়েছে, আপনি এটি আপনার IoT ডিভাইস থেকে ব্যবহার করতে পারেন।

### কাজ - আপনার IoT Edge ডিভাইস ব্যবহার করুন

IoT Edge ক্লাসিফায়ার ব্যবহার করে ইমেজ ক্লাসিফাই করার জন্য প্রাসঙ্গিক গাইডটি অনুসরণ করুন:

* [Arduino - Wio Terminal](wio-terminal.md)
* [Single-board computer - Raspberry Pi/Virtual IoT device](single-board-computer.md)

### মডেল পুনঃপ্রশিক্ষণ

IoT Edge-এ ইমেজ ক্লাসিফায়ার চালানোর একটি অসুবিধা হলো এটি আপনার Custom Vision প্রজেক্টের সাথে সংযুক্ত নয়। Custom Vision-এ **Predictions** ট্যাবে আপনি Edge-ভিত্তিক ক্লাসিফায়ার ব্যবহার করে ক্লাসিফাই করা ইমেজ দেখতে পাবেন না।

এটি প্রত্যাশিত আচরণ - ইমেজ ক্লাউডে ক্লাসিফিকেশনের জন্য পাঠানো হয় না, তাই সেগুলো ক্লাউডে উপলব্ধ হবে না। IoT Edge ব্যবহারের একটি সুবিধা হলো গোপনীয়তা, নিশ্চিত করা যে ইমেজ আপনার নেটওয়ার্ক ছেড়ে যায় না, অন্যটি হলো অফলাইনে কাজ করার ক্ষমতা, তাই ডিভাইসের ইন্টারনেট সংযোগ না থাকলে ইমেজ আপলোডের উপর নির্ভর করতে হয় না। অসুবিধা হলো আপনার মডেল উন্নত করা - আপনাকে ইমেজ সংরক্ষণের অন্য একটি উপায় বাস্তবায়ন করতে হবে যা ম্যানুয়ালি পুনঃশ্রেণীবদ্ধ করা যেতে পারে ইমেজ ক্লাসিফায়ার উন্নত এবং পুনঃপ্রশিক্ষণ করার জন্য।

✅ ক্লাসিফায়ার পুনঃপ্রশিক্ষণের জন্য ইমেজ আপলোড করার উপায় নিয়ে ভাবুন।

---

## 🚀 চ্যালেঞ্জ

এজ ডিভাইসে AI মডেল চালানো ক্লাউডের তুলনায় দ্রুত হতে পারে - নেটওয়ার্ক হপ ছোট। আবার এটি ধীরও হতে পারে কারণ মডেল চালানোর হার্ডওয়্যার ক্লাউডের মতো শক্তিশালী নাও হতে পারে।

আপনার এজ ডিভাইসে কল ক্লাউডের তুলনায় দ্রুত নাকি ধীর তা পরীক্ষা করুন? পার্থক্যের কারণ বা পার্থক্যের অভাব ব্যাখ্যা করার জন্য চিন্তা করুন। এজে AI মডেল দ্রুত চালানোর উপায় নিয়ে গবেষণা করুন, বিশেষ হার্ডওয়্যার ব্যবহার করে।

## লেকচার-পরবর্তী কুইজ

[লেকচার-পরবর্তী কুইজ](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/34)

## পর্যালোচনা ও স্ব-অধ্যয়ন

* কন্টেইনার সম্পর্কে আরও পড়ুন [Wikipedia-র OS-level virtualization পৃষ্ঠা](https://wikipedia.org/wiki/OS-level_virtualization) থেকে।
* এজ কম্পিউটিং সম্পর্কে আরও জানুন, বিশেষ করে কীভাবে 5G এজ কম্পিউটিং প্রসারিত করতে সাহায্য করতে পারে, [NetworkWorld-এর "এজ কম্পিউটিং কী এবং কেন এটি গুরুত্বপূর্ণ?" প্রবন্ধে](https://www.networkworld.com/article/3224893/what-is-edge-computing-and-how-its-changing-the-network.html)।

* IoT Edge-এ AI পরিষেবা চালানোর বিষয়ে আরও জানুন Microsoft Channel9-এর [Learn Live-এর "শার্পেন ইউর AI এজ স্কিলস" পর্বে, যেখানে Azure IoT Edge ব্যবহার করে প্রি-বিল্ট AI পরিষেবার মাধ্যমে ভাষা সনাক্তকরণ শেখানো হয়েছে](https://channel9.msdn.com/Shows/Learn-Live/Sharpen-Your-AI-Edge-Skills-Episode-4-Learn-How-to-Use-Azure-IoT-Edge-on-a-Pre-Built-AI-Service-on-t?WT.mc_id=academic-17441-jabenn)।

## অ্যাসাইনমেন্ট

[এজ-এ অন্যান্য পরিষেবা চালান](assignment.md)

---

**অস্বীকৃতি**:  
এই নথিটি AI অনুবাদ পরিষেবা [Co-op Translator](https://github.com/Azure/co-op-translator) ব্যবহার করে অনুবাদ করা হয়েছে। আমরা যথাসম্ভব সঠিকতার জন্য চেষ্টা করি, তবে অনুগ্রহ করে মনে রাখবেন যে স্বয়ংক্রিয় অনুবাদে ত্রুটি বা অসঙ্গতি থাকতে পারে। মূল ভাষায় থাকা নথিটিকে প্রামাণিক উৎস হিসেবে বিবেচনা করা উচিত। গুরুত্বপূর্ণ তথ্যের জন্য, পেশাদার মানব অনুবাদ সুপারিশ করা হয়। এই অনুবাদ ব্যবহারের ফলে কোনো ভুল বোঝাবুঝি বা ভুল ব্যাখ্যা হলে আমরা তার জন্য দায়ী থাকব না।