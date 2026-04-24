# আপনার অ্যাপ্লিকেশন লজিক ক্লাউডে স্থানান্তর করুন

![এই পাঠের একটি স্কেচনোট ওভারভিউ](../../../../../translated_images/bn/lesson-9.dfe99c8e891f48e1.webp)

> স্কেচনোট: [নিত্য নারাসিমহান](https://github.com/nitya)। বড় সংস্করণের জন্য ছবিতে ক্লিক করুন।

এই পাঠটি [IoT for Beginners Project 2 - Digital Agriculture series](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) এর অংশ হিসেবে [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn) থেকে শেখানো হয়েছিল।

[![আপনার IoT ডিভাইসকে সার্ভারলেস কোড দিয়ে নিয়ন্ত্রণ করুন](https://img.youtube.com/vi/VVZDcs5u1_I/0.jpg)](https://youtu.be/VVZDcs5u1_I)

## লেকচারের আগে কুইজ

[লেকচারের আগে কুইজ](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/17)

## ভূমিকা

পূর্ববর্তী পাঠে, আপনি শিখেছেন কীভাবে আপনার গাছের মাটির আর্দ্রতা পর্যবেক্ষণ এবং রিলে নিয়ন্ত্রণকে একটি ক্লাউড-ভিত্তিক IoT পরিষেবার সাথে সংযুক্ত করবেন। পরবর্তী ধাপটি হলো রিলের সময় নির্ধারণ নিয়ন্ত্রণকারী সার্ভার কোডটি ক্লাউডে স্থানান্তর করা। এই পাঠে, আপনি শিখবেন কীভাবে সার্ভারলেস ফাংশন ব্যবহার করে এটি করবেন।

এই পাঠে আমরা আলোচনা করব:

* [সার্ভারলেস কী?](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [একটি সার্ভারলেস অ্যাপ্লিকেশন তৈরি করুন](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [একটি IoT হাব ইভেন্ট ট্রিগার তৈরি করুন](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [সার্ভারলেস কোড থেকে সরাসরি মেথড রিকোয়েস্ট পাঠান](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [আপনার সার্ভারলেস কোড ক্লাউডে ডিপ্লয় করুন](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)

## সার্ভারলেস কী?

সার্ভারলেস, বা সার্ভারলেস কম্পিউটিং, এমন একটি পদ্ধতি যেখানে ছোট কোড ব্লক তৈরি করা হয় যা বিভিন্ন ইভেন্টের প্রতিক্রিয়ায় ক্লাউডে চালানো হয়। যখন ইভেন্ট ঘটে, তখন আপনার কোড চালানো হয় এবং ইভেন্ট সম্পর্কিত ডেটা পাস করা হয়। এই ইভেন্টগুলো বিভিন্ন উৎস থেকে আসতে পারে, যেমন ওয়েব রিকোয়েস্ট, একটি কিউতে বার্তা, ডাটাবেসে ডেটা পরিবর্তন, বা IoT ডিভাইস থেকে IoT পরিষেবায় পাঠানো বার্তা।

![IoT পরিষেবা থেকে সার্ভারলেস পরিষেবায় বার্তা পাঠানো হচ্ছে, যা একাধিক ফাংশন দ্বারা একসাথে প্রক্রিয়াকৃত হচ্ছে](../../../../../translated_images/bn/iot-messages-to-serverless.0194da1cc0732bb7.webp)

> 💁 যদি আপনি আগে ডাটাবেস ট্রিগার ব্যবহার করে থাকেন, তাহলে এটি একই রকম মনে হবে, যেখানে কোড একটি ইভেন্টের (যেমন একটি সারি যোগ করা) দ্বারা ট্রিগার হয়।

![যখন একই সময়ে অনেক ইভেন্ট পাঠানো হয়, সার্ভারলেস পরিষেবা স্কেল আপ করে এবং সেগুলো একসাথে চালায়](../../../../../translated_images/bn/serverless-scaling.f8c769adf0413fd1.webp)

আপনার কোড কেবল তখনই চালানো হয় যখন ইভেন্ট ঘটে; অন্য সময় এটি সক্রিয় থাকে না। ইভেন্ট ঘটে, আপনার কোড লোড হয় এবং চালানো হয়। এটি সার্ভারলেসকে অত্যন্ত স্কেলযোগ্য করে তোলে - যদি একই সময়ে অনেক ইভেন্ট ঘটে, ক্লাউড প্রদানকারী আপনার ফাংশন যতবার প্রয়োজন ততবার চালাতে পারে, তাদের উপলব্ধ সার্ভারগুলোতে। এর একটি অসুবিধা হলো, যদি ইভেন্টগুলোর মধ্যে তথ্য শেয়ার করতে হয়, তাহলে এটি মেমোরিতে সংরক্ষণ করার পরিবর্তে একটি ডাটাবেসে সংরক্ষণ করতে হবে।

আপনার কোড একটি ফাংশন হিসেবে লেখা হয় যা ইভেন্ট সম্পর্কিত বিবরণ প্যারামিটার হিসেবে গ্রহণ করে। এই সার্ভারলেস ফাংশন লেখার জন্য আপনি বিভিন্ন প্রোগ্রামিং ভাষা ব্যবহার করতে পারেন।

> 🎓 সার্ভারলেসকে কখনও কখনও ফাংশন অ্যাজ এ সার্ভিস (FaaS) বলা হয়, কারণ প্রতিটি ইভেন্ট ট্রিগার কোডে একটি ফাংশন হিসেবে বাস্তবায়িত হয়।

নামের বিপরীতে, সার্ভারলেস আসলে সার্ভার ব্যবহার করে। নামটি এসেছে কারণ একজন ডেভেলপার হিসেবে আপনাকে সার্ভার নিয়ে চিন্তা করতে হয় না; আপনাকে কেবল চিন্তা করতে হয় যে আপনার কোডটি একটি ইভেন্টের প্রতিক্রিয়ায় চালানো হচ্ছে। ক্লাউড প্রদানকারীর একটি সার্ভারলেস *রানটাইম* রয়েছে যা সার্ভার বরাদ্দ, নেটওয়ার্কিং, স্টোরেজ, CPU, মেমোরি এবং আপনার কোড চালানোর জন্য প্রয়োজনীয় অন্যান্য সবকিছু পরিচালনা করে। এই মডেলে আপনি সার্ভারের জন্য অর্থ প্রদান করেন না; বরং আপনি আপনার কোড চালানোর সময় এবং ব্যবহৃত মেমোরির জন্য অর্থ প্রদান করেন।

> 💰 সার্ভারলেস ক্লাউডে কোড চালানোর সবচেয়ে সাশ্রয়ী উপায়গুলোর একটি। উদাহরণস্বরূপ, লেখার সময়, একটি ক্লাউড প্রদানকারী প্রতি মাসে আপনার সমস্ত সার্ভারলেস ফাংশন এক মিলিয়ন বার চালানোর অনুমতি দেয় বিনামূল্যে, এবং এর পরে প্রতি এক মিলিয়ন এক্সিকিউশনের জন্য US$0.20 চার্জ করে। যখন আপনার কোড চালানো হয় না, তখন আপনি কোনো অর্থ প্রদান করেন না।

একজন IoT ডেভেলপার হিসেবে, সার্ভারলেস মডেলটি আদর্শ। আপনি একটি ফাংশন লিখতে পারেন যা আপনার ক্লাউড-হোস্টেড IoT পরিষেবার সাথে সংযুক্ত যেকোনো IoT ডিভাইস থেকে পাঠানো বার্তার প্রতিক্রিয়ায় চালানো হয়। আপনার কোড সমস্ত বার্তা পরিচালনা করবে, তবে কেবল প্রয়োজন হলে চালানো হবে।

✅ আপনি যে কোডটি MQTT বার্তার জন্য সার্ভার কোড হিসেবে লিখেছিলেন, সেটি ক্লাউডে কীভাবে সার্ভারলেস হিসেবে চালানো যেতে পারে তা ভেবে দেখুন। সার্ভারলেস কম্পিউটিং সমর্থন করার জন্য কোডটি কীভাবে পরিবর্তন করা যেতে পারে বলে আপনি মনে করেন?

> 💁 সার্ভারলেস মডেলটি কোড চালানোর বাইরেও অন্যান্য ক্লাউড পরিষেবাগুলোর দিকে এগিয়ে যাচ্ছে। উদাহরণস্বরূপ, ক্লাউডে সার্ভারলেস ডাটাবেস পাওয়া যায়, যেখানে আপনি প্রতি অনুরোধের ভিত্তিতে অর্থ প্রদান করেন, যেমন একটি কুইরি বা ইনসার্ট। সাধারণত, এটি কতটা কাজ করতে হয় তার উপর ভিত্তি করে মূল্য নির্ধারণ করা হয়। উদাহরণস্বরূপ, একটি প্রাইমারি কী-এর বিরুদ্ধে একটি সারি নির্বাচন করা একটি জটিল অপারেশনের চেয়ে কম খরচ হবে যা অনেক টেবিল যোগ করে এবং হাজার হাজার সারি ফেরত দেয়।

## একটি সার্ভারলেস অ্যাপ্লিকেশন তৈরি করুন

মাইক্রোসফটের সার্ভারলেস কম্পিউটিং পরিষেবাটি Azure Functions নামে পরিচিত।

![Azure Functions লোগো](../../../../../translated_images/bn/azure-functions-logo.1cfc8e3204c9c44a.webp)

নিচের সংক্ষিপ্ত ভিডিওতে Azure Functions-এর একটি ওভারভিউ রয়েছে:

[![Azure Functions ওভারভিউ ভিডিও](https://img.youtube.com/vi/8-jz5f_JyEQ/0.jpg)](https://www.youtube.com/watch?v=8-jz5f_JyEQ)

> 🎥 উপরের ছবিতে ক্লিক করে ভিডিওটি দেখুন

✅ কিছু সময় নিয়ে Azure Functions-এর ওভারভিউ পড়ুন [Microsoft Azure Functions ডকুমেন্টেশনে](https://docs.microsoft.com/azure/azure-functions/functions-overview?WT.mc_id=academic-17441-jabenn)।

Azure Functions লেখার জন্য, আপনাকে আপনার পছন্দের ভাষায় একটি Azure Functions অ্যাপ দিয়ে শুরু করতে হবে। Azure Functions ডিফল্টভাবে Python, JavaScript, TypeScript, C#, F#, Java এবং Powershell সমর্থন করে। এই পাঠে, আপনি Python-এ একটি Azure Functions অ্যাপ লিখতে শিখবেন।

> 💁 Azure Functions কাস্টম হ্যান্ডলারও সমর্থন করে, তাই আপনি যেকোনো ভাষায় ফাংশন লিখতে পারেন যা HTTP রিকোয়েস্ট সমর্থন করে, এমনকি COBOL-এর মতো পুরনো ভাষায়ও।

Functions অ্যাপগুলো এক বা একাধিক *ট্রিগার* নিয়ে গঠিত - ফাংশনগুলো ইভেন্টের প্রতিক্রিয়ায় কাজ করে। একটি Functions অ্যাপে একাধিক ট্রিগার থাকতে পারে, যা সাধারণ কনফিগারেশন শেয়ার করে। উদাহরণস্বরূপ, আপনার Functions অ্যাপের কনফিগারেশন ফাইলে আপনার IoT হাবের সংযোগ বিবরণ থাকতে পারে, এবং অ্যাপের সমস্ত ফাংশন এটি ব্যবহার করে সংযোগ করতে এবং ইভেন্ট শোনার জন্য ব্যবহার করতে পারে।

### কাজ - Azure Functions টুলিং ইনস্টল করুন

> লেখার সময়, Azure Functions কোড টুলগুলো Apple Silicon-এ Python প্রকল্পের জন্য পুরোপুরি কাজ করছে না। আপনাকে একটি Intel-ভিত্তিক Mac, Windows PC, বা Linux PC ব্যবহার করতে হবে।

Azure Functions-এর একটি চমৎকার বৈশিষ্ট্য হলো আপনি এটি লোকালভাবে চালাতে পারেন। ক্লাউডে ব্যবহৃত একই রানটাইম আপনার কম্পিউটারে চালানো যায়, যা আপনাকে IoT বার্তার প্রতিক্রিয়ায় কোড লিখতে এবং লোকালভাবে চালাতে দেয়। আপনি এমনকি ইভেন্ট পরিচালনার সময় আপনার কোড ডিবাগ করতে পারেন। একবার আপনি আপনার কোড নিয়ে সন্তুষ্ট হলে, এটি ক্লাউডে ডিপ্লয় করা যেতে পারে।

Azure Functions টুলিং CLI হিসেবে উপলব্ধ, যা Azure Functions Core Tools নামে পরিচিত।

1. Azure Functions Core Tools ইনস্টল করুন [Azure Functions Core Tools ডকুমেন্টেশনের](https://docs.microsoft.com/azure/azure-functions/functions-run-local?WT.mc_id=academic-17441-jabenn) নির্দেশাবলী অনুসরণ করে।

1. VS Code-এর জন্য Azure Functions এক্সটেনশন ইনস্টল করুন। এই এক্সটেনশনটি Azure Functions তৈরি, ডিবাগ এবং ডিপ্লয়ের জন্য সমর্থন প্রদান করে। [Azure Functions এক্সটেনশন ডকুমেন্টেশনে](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-azuretools.vscode-azurefunctions) এই এক্সটেনশনটি VS Code-এ ইনস্টল করার নির্দেশাবলী দেখুন।

Azure Functions অ্যাপটি ক্লাউডে ডিপ্লয় করার সময়, এটি অ্যাপ্লিকেশন ফাইল এবং লগ ফাইলের মতো কিছু সংরক্ষণ করার জন্য একটি ছোট পরিমাণ ক্লাউড স্টোরেজ ব্যবহার করতে হবে। যখন আপনি আপনার Functions অ্যাপ লোকালভাবে চালান, তখনও আপনাকে ক্লাউড স্টোরেজের সাথে সংযুক্ত থাকতে হবে, তবে প্রকৃত ক্লাউড স্টোরেজ ব্যবহার করার পরিবর্তে, আপনি [Azurite](https://github.com/Azure/Azurite) নামে একটি স্টোরেজ এমুলেটর ব্যবহার করতে পারেন। এটি লোকালভাবে চালায় কিন্তু ক্লাউড স্টোরেজের মতো কাজ করে।

> 🎓 Azure-এ, Azure Functions যে স্টোরেজ ব্যবহার করে তা হলো একটি Azure Storage Account। এই অ্যাকাউন্টগুলো ফাইল, ব্লব, টেবিলের ডেটা বা কিউয়ের ডেটা সংরক্ষণ করতে পারে। আপনি একাধিক অ্যাপের মধ্যে একটি স্টোরেজ অ্যাকাউন্ট শেয়ার করতে পারেন, যেমন একটি Functions অ্যাপ এবং একটি ওয়েব অ্যাপ।

1. Azurite একটি Node.js অ্যাপ, তাই আপনাকে Node.js ইনস্টল করতে হবে। [Node.js ওয়েবসাইটে](https://nodejs.org/) ডাউনলোড এবং ইনস্টলেশনের নির্দেশাবলী পাওয়া যাবে। যদি আপনি Mac ব্যবহার করেন, তবে আপনি এটি [Homebrew](https://formulae.brew.sh/formula/node) থেকেও ইনস্টল করতে পারেন।

1. Azurite ইনস্টল করুন নিম্নলিখিত কমান্ড ব্যবহার করে (`npm` হলো একটি টুল যা Node.js ইনস্টল করার সময় ইনস্টল হয়):

    ```sh
    npm install -g azurite
    ```

1. Azurite-এর জন্য একটি ফোল্ডার তৈরি করুন যেখানে এটি ডেটা সংরক্ষণ করবে:

    ```sh
    mkdir azurite
    ```

1. Azurite চালান, এই নতুন ফোল্ডারটি পাস করে:

    ```sh
    azurite --location azurite
    ```

    Azurite স্টোরেজ এমুলেটর চালু হবে এবং লোকাল Functions রানটাইমের সাথে সংযোগের জন্য প্রস্তুত থাকবে।

    ```output
    ➜  ~ azurite --location azurite  
    Azurite Blob service is starting at http://127.0.0.1:10000
    Azurite Blob service is successfully listening at http://127.0.0.1:10000
    Azurite Queue service is starting at http://127.0.0.1:10001
    Azurite Queue service is successfully listening at http://127.0.0.1:10001
    Azurite Table service is starting at http://127.0.0.1:10002
    Azurite Table service is successfully listening at http://127.0.0.1:10002
    ```

### কাজ - একটি Azure Functions প্রকল্প তৈরি করুন

Azure Functions CLI ব্যবহার করে একটি নতুন Functions অ্যাপ তৈরি করা যায়।

1. আপনার Functions অ্যাপের জন্য একটি ফোল্ডার তৈরি করুন এবং এতে যান। এটি `soil-moisture-trigger` নামে রাখুন:

    ```sh
    mkdir soil-moisture-trigger
    cd soil-moisture-trigger
    ```

1. এই ফোল্ডারের ভিতরে একটি Python ভার্চুয়াল এনভায়রনমেন্ট তৈরি করুন:

    ```sh
    python3 -m venv .venv
    ```

1. ভার্চুয়াল এনভায়রনমেন্ট সক্রিয় করুন:

    * Windows-এ:
        * যদি আপনি Command Prompt বা Windows Terminal-এর মাধ্যমে Command Prompt ব্যবহার করেন, তাহলে চালান:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * যদি আপনি PowerShell ব্যবহার করেন, তাহলে চালান:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

    * macOS বা Linux-এ, চালান:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 এই কমান্ডগুলো সেই অবস্থান থেকে চালানো উচিত যেখানে আপনি ভার্চুয়াল এনভায়রনমেন্ট তৈরি করেছিলেন। `.venv` ফোল্ডারে কখনও প্রবেশ করার প্রয়োজন নেই; আপনাকে সর্বদা সক্রিয় কমান্ড এবং প্যাকেজ ইনস্টল বা কোড চালানোর কমান্ড সেই ফোল্ডার থেকে চালাতে হবে যেখানে আপনি ভার্চুয়াল এনভায়রনমেন্ট তৈরি করেছিলেন।

1. এই ফোল্ডারে একটি Functions অ্যাপ তৈরি করতে নিম্নলিখিত কমান্ড চালান:

    ```sh
    func init --worker-runtime python soil-moisture-trigger
    ```

    এটি বর্তমান ফোল্ডারের ভিতরে তিনটি ফাইল তৈরি করবে:

    * `host.json` - এই JSON ডকুমেন্টটি আপনার Functions অ্যাপের সেটিংস ধারণ করে। আপনাকে এই সেটিংস পরিবর্তন করতে হবে না।
    * `local.settings.json` - এই JSON ডকুমেন্টটি আপনার অ্যাপ লোকালভাবে চালানোর সময় ব্যবহৃত সেটিংস ধারণ করে, যেমন আপনার IoT হাবের জন্য সংযোগ স্ট্রিং। এই সেটিংস কেবল লোকাল এবং সোর্স কোড কন্ট্রোলে যোগ করা উচিত নয়। যখন অ্যাপটি ক্লাউডে ডিপ্লয় করা হয়, তখন এই সেটিংস ডিপ্লয় করা হয় না; পরিবর্তে আপনার সেটিংস অ্যাপ্লিকেশন সেটিংস থেকে লোড করা হয়। এটি এই পাঠে পরে আলোচনা করা হবে।
    * `requirements.txt` - এটি একটি [Pip requirements ফাইল](https://pip.pypa.io/en/stable/user_guide/#requirements-files) যা Functions অ্যাপ চালানোর জন্য প্রয়োজনীয় Pip প্যাকেজগুলো ধারণ করে।

1. `local.settings.json` ফাইলটি Functions অ্যাপ যে স্টোরেজ অ্যাকাউন্ট ব্যবহার করবে তার জন্য একটি সেটিং ধারণ করে। এটি ডিফল্টভাবে খালি থাকে, তাই এটি সেট করতে হবে। Azurite লোকাল স্টোরেজ এমুলেটরের সাথে সংযোগ করতে, এই মানটি নিম্নলিখিতভাবে সেট করুন:

    ```json
    "AzureWebJobsStorage": "UseDevelopmentStorage=true",
    ```

1. প্রয়োজনীয় Pip প্যাকেজগুলো requirements ফাইল ব্যবহার করে ইনস্টল করুন:

    ```sh
    pip install -r requirements.txt
    ```

    > 💁 প্রয়োজনীয় Pip প্যাকেজগুলো এই ফাইলে থাকতে হবে, যাতে Functions অ্যাপ ক্লাউডে ডিপ্লয় করার সময় রানটাইম সঠিক প্যাকেজ ইনস্টল করতে পারে।

1. সবকিছু সঠিকভাবে কাজ করছে কিনা তা পরীক্ষা করতে, আপনি Functions রানটাইম শুরু করতে পারেন। এটি করতে নিম্নলিখিত কমান্ড চালান:

    ```sh
    func start
    ```

    আপনি দেখবেন যে রানটাইম শুরু হয়েছে এবং এটি কোনো জব ফাংশন (ট্রিগার) খুঁজে পায়নি বলে রিপোর্ট করছে।

    ```output
    (.venv) ➜  soil-moisture-trigger func start
    Found Python version 3.9.1 (python3).
    
    Azure Functions Core Tools
    Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    Function Runtime Version: 3.0.15417.0
    
    [2021-05-05T01:24:46.795Z] No job functions found.
    ```
> ⚠️ যদি আপনি একটি ফায়ারওয়াল বিজ্ঞপ্তি পান, অনুমতি দিন কারণ `func` অ্যাপ্লিকেশনটি আপনার নেটওয়ার্কে পড়া এবং লেখা সক্ষম হওয়া প্রয়োজন।
> ⚠️ যদি আপনি macOS ব্যবহার করেন, আউটপুটে সতর্কবার্তা থাকতে পারে:
>
> ```output
    > (.venv) ➜  soil-moisture-trigger func start
    > Found Python version 3.9.1 (python3).
    >
    > Azure Functions Core Tools
    > Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    > Function Runtime Version: 3.0.15417.0
    >
    > [2021-06-16T08:18:28.315Z] Cannot create directory for shared memory usage: /dev/shm/AzureFunctions
    > [2021-06-16T08:18:28.316Z] System.IO.FileSystem: Access to the path '/dev/shm/AzureFunctions' is denied. Operation not permitted.
    > [2021-06-16T08:18:30.361Z] No job functions found.
    > ```
>
> যতক্ষণ না Functions অ্যাপ সঠিকভাবে শুরু হয় এবং চলমান ফাংশনগুলি তালিকাভুক্ত হয়, আপনি এই সতর্কবার্তাগুলি উপেক্ষা করতে পারেন। [Microsoft Docs Q&A-তে এই প্রশ্নে](https://docs.microsoft.com/answers/questions/396617/azure-functions-core-tools-error-osx-devshmazurefu.html?WT.mc_id=academic-17441-jabenn) উল্লেখ করা হয়েছে যে এটি উপেক্ষা করা যেতে পারে।

1. `ctrl+c` চাপ দিয়ে Functions অ্যাপ বন্ধ করুন।

1. বর্তমান ফোল্ডারটি VS Code-এ খুলুন। এটি VS Code খুলে তারপর ফোল্ডারটি খুলে বা নিচের কমান্ডটি চালিয়ে করতে পারেন:

    ```sh
    code .
    ```

    VS Code আপনার Functions প্রজেক্ট সনাক্ত করবে এবং একটি নোটিফিকেশন দেখাবে:

    ```output
    Detected an Azure Functions Project in folder "soil-moisture-trigger" that may have been created outside of
    VS Code. Initialize for optimal use with VS Code?
    ```

    ![নোটিফিকেশন](../../../../../translated_images/bn/vscode-azure-functions-init-notification.bd19b49229963edb.webp)

    এই নোটিফিকেশন থেকে **Yes** নির্বাচন করুন।

1. নিশ্চিত করুন যে VS Code টার্মিনালে Python ভার্চুয়াল এনভায়রনমেন্ট চালু রয়েছে। প্রয়োজনে এটি বন্ধ করে পুনরায় চালু করুন।

## একটি IoT Hub ইভেন্ট ট্রিগার তৈরি করুন

Functions অ্যাপটি আপনার সার্ভারলেস কোডের শেল। IoT Hub ইভেন্টগুলিতে সাড়া দিতে, আপনি এই অ্যাপে একটি IoT Hub ট্রিগার যোগ করতে পারেন। এই ট্রিগারটি IoT Hub-এ পাঠানো বার্তাগুলির স্ট্রিমের সাথে সংযোগ স্থাপন করে এবং সেগুলিতে সাড়া দেয়। এই বার্তাগুলির স্ট্রিম পেতে, আপনার ট্রিগারকে IoT Hub-এর *ইভেন্ট হাব কম্প্যাটিবল এন্ডপয়েন্ট*-এর সাথে সংযোগ স্থাপন করতে হবে।

IoT Hub একটি Azure পরিষেবা Azure Event Hubs-এর উপর ভিত্তি করে তৈরি। Event Hubs একটি পরিষেবা যা বার্তা পাঠানো এবং গ্রহণ করার অনুমতি দেয়, এবং IoT Hub এটিকে IoT ডিভাইসগুলির জন্য অতিরিক্ত বৈশিষ্ট্য যোগ করে বাড়িয়ে তোলে। IoT Hub থেকে বার্তা পড়ার জন্য সংযোগ করার পদ্ধতি Event Hubs ব্যবহারের মতোই।

✅ কিছু গবেষণা করুন: [Azure Event Hubs ডকুমেন্টেশনে](https://docs.microsoft.com/azure/event-hubs/event-hubs-about?WT.mc_id=academic-17441-jabenn) Event Hubs-এর ওভারভিউ পড়ুন। এর মৌলিক বৈশিষ্ট্যগুলি IoT Hub-এর সাথে কীভাবে তুলনা করা যায়?

একটি IoT ডিভাইসকে IoT Hub-এ সংযোগ করতে হলে একটি সিক্রেট কী ব্যবহার করতে হয় যা নিশ্চিত করে যে শুধুমাত্র অনুমোদিত ডিভাইসগুলি সংযোগ করতে পারে। বার্তা পড়ার জন্য সংযোগ করার ক্ষেত্রেও একই নিয়ম প্রযোজ্য, আপনার কোডে একটি সংযোগ স্ট্রিং প্রয়োজন যা একটি সিক্রেট কী এবং IoT Hub-এর বিবরণ ধারণ করে।

> 💁 ডিফল্ট সংযোগ স্ট্রিং-এ **iothubowner** অনুমতি থাকে, যা এটি ব্যবহারকারী যেকোন কোডকে IoT Hub-এ পূর্ণ অনুমতি দেয়। আদর্শভাবে, আপনাকে প্রয়োজনীয় সর্বনিম্ন অনুমতি দিয়ে সংযোগ করতে হবে। এটি পরবর্তী পাঠে আলোচনা করা হবে।

আপনার ট্রিগার সংযুক্ত হওয়ার পরে, IoT Hub-এ পাঠানো প্রতিটি বার্তার জন্য ফাংশনের ভিতরের কোডটি চালানো হবে, যেকোন ডিভাইস বার্তাটি পাঠিয়েছে তা নির্বিশেষে। বার্তাটি একটি প্যারামিটার হিসাবে ট্রিগারে পাস করা হবে।

### কাজ - Event Hub কম্প্যাটিবল এন্ডপয়েন্ট সংযোগ স্ট্রিং পান

1. VS Code টার্মিনাল থেকে নিচের কমান্ডটি চালান IoT Hub-এর Event Hub কম্প্যাটিবল এন্ডপয়েন্টের সংযোগ স্ট্রিং পেতে:

    ```sh
    az iot hub connection-string show --default-eventhub \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    `<hub_name>`-এর জায়গায় আপনার IoT Hub-এর নাম দিন।

1. VS Code-এ `local.settings.json` ফাইলটি খুলুন। `Values` সেকশনের মধ্যে নিচের অতিরিক্ত মানটি যোগ করুন:

    ```json
    "IOT_HUB_CONNECTION_STRING": "<connection string>"
    ```

    `<connection string>`-এর জায়গায় আগের ধাপে প্রাপ্ত মানটি দিন। এটি বৈধ JSON করতে উপরের লাইনের পরে একটি কমা যোগ করতে হবে।

### কাজ - একটি ইভেন্ট ট্রিগার তৈরি করুন

আপনি এখন ইভেন্ট ট্রিগার তৈরি করতে প্রস্তুত।

1. VS Code টার্মিনাল থেকে `soil-moisture-trigger` ফোল্ডারের ভিতরে নিচের কমান্ডটি চালান:

    ```sh
    func new --name iot-hub-trigger --template "Azure Event Hub trigger"
    ```

    এটি একটি নতুন Function তৈরি করবে যার নাম হবে `iot-hub-trigger`। ট্রিগারটি IoT Hub-এর Event Hub কম্প্যাটিবল এন্ডপয়েন্টের সাথে সংযোগ করবে, তাই আপনি একটি Event Hub ট্রিগার ব্যবহার করতে পারেন। নির্দিষ্ট কোনো IoT Hub ট্রিগার নেই।

এটি `soil-moisture-trigger` ফোল্ডারের ভিতরে একটি ফোল্ডার তৈরি করবে যার নাম হবে `iot-hub-trigger`, যা এই ফাংশনটি ধারণ করবে। এই ফোল্ডারের ভিতরে নিম্নলিখিত ফাইলগুলি থাকবে:

* `__init__.py` - এটি Python কোড ফাইল যা ট্রিগার ধারণ করে। এটি একটি Python মডিউল হিসেবে ফোল্ডারটিকে চিহ্নিত করতে স্ট্যান্ডার্ড Python ফাইল নামকরণ কনভেনশন ব্যবহার করে।

    এই ফাইলটি নিচের কোডটি ধারণ করবে:

    ```python
    import logging

    import azure.functions as func


    def main(event: func.EventHubEvent):
        logging.info('Python EventHub trigger processed an event: %s',
                    event.get_body().decode('utf-8'))
    ```

    ট্রিগারের মূল অংশটি হল `main` ফাংশন। IoT Hub থেকে ইভেন্ট পাওয়ার সাথে সাথে এই ফাংশনটি ডাকা হয়। এই ফাংশনের একটি প্যারামিটার `event` রয়েছে যা একটি `EventHubEvent` ধারণ করে। IoT Hub-এ বার্তা পাঠানোর প্রতিবার, এই ফাংশনটি বার্তাটি `event` হিসেবে পাস করে ডাকা হয়, এবং বার্তার সাথে প্রোপার্টিগুলি থাকে যা আপনি আগের পাঠে অ্যানোটেশনে দেখেছেন।

    এই ফাংশনের মূল অংশটি ইভেন্টটি লগ করে।

* `function.json` - এটি ট্রিগারের কনফিগারেশন ধারণ করে। মূল কনফিগারেশনটি `bindings` নামে একটি সেকশনে থাকে। একটি binding হল Azure Functions এবং অন্যান্য Azure পরিষেবাগুলির মধ্যে সংযোগের জন্য ব্যবহৃত শব্দ। এই ফাংশনের একটি ইনপুট binding রয়েছে একটি Event Hub-এর সাথে - এটি Event Hub-এর সাথে সংযোগ করে এবং ডেটা গ্রহণ করে।

    > 💁 আপনি আউটপুট binding-ও রাখতে পারেন যাতে ফাংশনের আউটপুট অন্য কোনো পরিষেবায় পাঠানো যায়। উদাহরণস্বরূপ, আপনি একটি ডাটাবেসে আউটপুট binding যোগ করতে পারেন এবং ফাংশন থেকে IoT Hub ইভেন্টটি ফেরত দিতে পারেন, এবং এটি স্বয়ংক্রিয়ভাবে ডাটাবেসে যোগ করা হবে।

    ✅ কিছু গবেষণা করুন: [Azure Functions triggers and bindings concepts ডকুমেন্টেশনে](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python) bindings সম্পর্কে পড়ুন।

    `bindings` সেকশনে binding-এর কনফিগারেশন অন্তর্ভুক্ত থাকে। গুরুত্বপূর্ণ মানগুলি হল:

  * `"type": "eventHubTrigger"` - এটি ফাংশনকে বলে যে এটি Event Hub থেকে ইভেন্ট শুনতে হবে
  * `"name": "events"` - এটি Event Hub ইভেন্টগুলির জন্য ব্যবহৃত প্যারামিটার নাম। এটি Python কোডে `main` ফাংশনের প্যারামিটার নামের সাথে মেলে।
  * `"direction": "in"` - এটি একটি ইনপুট binding, Event Hub থেকে ডেটা ফাংশনে আসে
  * `"connection": ""` - এটি সংযোগ স্ট্রিং পড়ার জন্য সেটিংসের নাম সংজ্ঞায়িত করে। স্থানীয়ভাবে চালানোর সময়, এটি `local.settings.json` ফাইল থেকে এই সেটিং পড়বে।

    > 💁 সংযোগ স্ট্রিং `function.json` ফাইলে সংরক্ষণ করা যাবে না, এটি সেটিংস থেকে পড়তে হবে। এটি আপনার সংযোগ স্ট্রিংটি দুর্ঘটনাক্রমে প্রকাশ হওয়া থেকে রোধ করার জন্য।

1. [Azure Functions টেমপ্লেটে একটি বাগের কারণে](https://github.com/Azure/azure-functions-templates/issues/1250), `function.json` ফাইলে `cardinality` ফিল্ডের একটি ভুল মান রয়েছে। এই ফিল্ডটি `many` থেকে `one`-এ আপডেট করুন:

    ```json
    "cardinality": "one",
    ```

1. `function.json` ফাইলে `"connection"`-এর মানটি আপডেট করুন যাতে এটি `local.settings.json` ফাইলে যোগ করা নতুন মানের দিকে নির্দেশ করে:

    ```json
    "connection": "IOT_HUB_CONNECTION_STRING",
    ```

    > 💁 মনে রাখবেন - এটি সেটিংসের দিকে নির্দেশ করতে হবে, প্রকৃত সংযোগ স্ট্রিং ধারণ করতে হবে না।

1. সংযোগ স্ট্রিং-এ `eventHubName` মানটি রয়েছে, তাই `function.json` ফাইলে এর জন্য মানটি খালি করতে হবে। এই মানটি একটি খালি স্ট্রিং-এ আপডেট করুন:

    ```json
    "eventHubName": "",
    ```

### কাজ - ইভেন্ট ট্রিগার চালান

1. নিশ্চিত করুন যে আপনি IoT Hub ইভেন্ট মনিটর চালাচ্ছেন না। Functions অ্যাপ চালানোর সময় এটি চালু থাকলে, Functions অ্যাপ সংযোগ করতে এবং ইভেন্ট গ্রহণ করতে পারবে না।

    > 💁 একাধিক অ্যাপ IoT Hub এন্ডপয়েন্টে বিভিন্ন *consumer groups* ব্যবহার করে সংযোগ করতে পারে। এটি একটি পরবর্তী পাঠে আলোচনা করা হবে।

1. Functions অ্যাপ চালানোর জন্য, VS Code টার্মিনাল থেকে নিচের কমান্ডটি চালান:

    ```sh
    func start
    ```

    Functions অ্যাপটি চালু হবে এবং `iot-hub-trigger` ফাংশনটি আবিষ্কার করবে। এটি IoT Hub-এ গত এক দিনে পাঠানো যেকোন ইভেন্ট প্রক্রিয়া করবে।

    ```output
    (.venv) ➜  soil-moisture-trigger func start
    Found Python version 3.9.1 (python3).
    
    Azure Functions Core Tools
    Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    Function Runtime Version: 3.0.15417.0
    
    Functions:
    
            iot-hub-trigger: eventHubTrigger
    
    For detailed output, run func with --verbose flag.
    [2021-05-05T02:44:07.517Z] Worker process started and initialized.
    [2021-05-05T02:44:09.202Z] Executing 'Functions.iot-hub-trigger' (Reason='(null)', Id=802803a5-eae9-4401-a1f4-176631456ce4)
    [2021-05-05T02:44:09.205Z] Trigger Details: PartitionId: 0, Offset: 1011240-1011632, EnqueueTimeUtc: 2021-05-04T19:04:04.2030000Z-2021-05-04T19:04:04.3900000Z, SequenceNumber: 2546-2547, Count: 2
    [2021-05-05T02:44:09.352Z] Python EventHub trigger processed an event: {"soil_moisture":628}
    [2021-05-05T02:44:09.354Z] Python EventHub trigger processed an event: {"soil_moisture":624}
    [2021-05-05T02:44:09.395Z] Executed 'Functions.iot-hub-trigger' (Succeeded, Id=802803a5-eae9-4401-a1f4-176631456ce4, Duration=245ms)
    ```

    প্রতিটি ফাংশন কল `Executing 'Functions.iot-hub-trigger'`/`Executed 'Functions.iot-hub-trigger'` ব্লকের মধ্যে থাকবে, যাতে আপনি প্রতিটি ফাংশন কলে কতগুলি বার্তা প্রক্রিয়া হয়েছে তা দেখতে পারেন।

1. নিশ্চিত করুন যে আপনার IoT ডিভাইস চালু রয়েছে। আপনি Functions অ্যাপে নতুন soil moisture বার্তা দেখতে পাবেন।

1. Functions অ্যাপ বন্ধ করুন এবং পুনরায় চালু করুন। আপনি দেখবেন যে এটি পূর্ববর্তী বার্তাগুলি পুনরায় প্রক্রিয়া করবে না, এটি শুধুমাত্র নতুন বার্তাগুলি প্রক্রিয়া করবে।

> 💁 VS Code আপনার Functions ডিবাগ করতেও সমর্থন করে। আপনি প্রতিটি কোড লাইনের শুরুতে বর্ডারে ক্লিক করে ব্রেক পয়েন্ট সেট করতে পারেন, অথবা কোড লাইনে কার্সর রেখে *Run -> Toggle breakpoint* নির্বাচন করতে পারেন, অথবা `F9` চাপতে পারেন। আপনি *Run -> Start debugging* নির্বাচন করে, `F5` চাপ দিয়ে, অথবা *Run and debug* প্যান থেকে **Start debugging** বোতামটি নির্বাচন করে ডিবাগার চালু করতে পারেন। এটি করে আপনি প্রক্রিয়াকৃত ইভেন্টগুলির বিস্তারিত দেখতে পারবেন।

#### সমস্যা সমাধান

* যদি আপনি নিচের ত্রুটি পান:

    ```output
    The listener for function 'Functions.iot-hub-trigger' was unable to start. Microsoft.WindowsAzure.Storage: Connection refused. System.Net.Http: Connection refused. System.Private.CoreLib: Connection refused.
    ```

    নিশ্চিত করুন যে Azurite চালু রয়েছে এবং আপনি `local.settings.json` ফাইলে `AzureWebJobsStorage`-এ `UseDevelopmentStorage=true` সেট করেছেন।

* যদি আপনি নিচের ত্রুটি পান:

    ```output
    System.Private.CoreLib: Exception while executing function: Functions.iot-hub-trigger. System.Private.CoreLib: Result: Failure Exception: AttributeError: 'list' object has no attribute 'get_body'
    ```

    নিশ্চিত করুন যে আপনি `function.json` ফাইলে `cardinality`-কে `one`-এ সেট করেছেন।

* যদি আপনি নিচের ত্রুটি পান:

    ```output
    Azure.Messaging.EventHubs: The path to an Event Hub may be specified as part of the connection string or as a separate value, but not both.  Please verify that your connection string does not have the `EntityPath` token if you are passing an explicit Event Hub name. (Parameter 'connectionString').
    ```

    নিশ্চিত করুন যে আপনি `function.json` ফাইলে `eventHubName`-কে একটি খালি স্ট্রিং-এ সেট করেছেন।

## সার্ভারলেস কোড থেকে সরাসরি মেথড রিকোয়েস্ট পাঠান

এখন পর্যন্ত আপনার Functions অ্যাপ IoT Hub থেকে Event Hub কম্প্যাটিবল এন্ডপয়েন্ট ব্যবহার করে বার্তা শুনছে। এখন আপনাকে IoT ডিভাইসে কমান্ড পাঠাতে হবে। এটি IoT Hub-এ একটি ভিন্ন সংযোগ ব্যবহার করে *Registry Manager*-এর মাধ্যমে করা হয়। Registry Manager একটি টুল যা আপনাকে IoT Hub-এ নিবন্ধিত ডিভাইসগুলি দেখতে এবং সেই ডিভাইসগুলির সাথে ক্লাউড থেকে ডিভাইসে বার্তা পাঠানো, সরাসরি মেথড রিকোয়েস্ট পাঠানো বা ডিভাইস টুইন আপডেট করার মাধ্যমে যোগাযোগ করতে দেয়। এটি IoT Hub থেকে ডিভাইস নিবন্ধন, আপডেট বা মুছে ফেলতেও ব্যবহার করা যায়।

Registry Manager-এ সংযোগ করতে, আপনাকে একটি সংযোগ স্ট্রিং প্রয়োজন।

### কাজ - Registry Manager সংযোগ স্ট্রিং পান

1. সংযোগ স্ট্রিং পেতে, নিচের কমান্ডটি চালান:

    ```sh
    az iot hub connection-string show --policy-name service \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    `<hub_name>`-এর জায়গায় আপনার IoT Hub-এর নাম দিন।

    সংযোগ স্ট্রিংটি *ServiceConnect* পলিসির জন্য অনুরোধ করা হয় `--policy-name service` প্যারামিটার ব্যবহার করে। যখন আপনি একটি সংযোগ স্ট্রিং অনুরোধ করেন, আপনি নির্দিষ্ট করতে পারেন যে এই সংযোগ স্ট্রিংটি কী অনুমতি দেবে। ServiceConnect পলিসি আপনার কোডকে IoT ডিভাইসগুলিতে বার্তা পাঠানোর অনুমতি দেয়।

    ✅ কিছু গবেষণা করুন: [IoT Hub permissions ডকুমেন্টেশনে](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-security#iot-hub-permissions?WT.mc_id=academic-17441-jabenn) বিভিন্ন পলিসি সম্পর্কে পড়ুন।

1. VS Code-এ `local.settings.json` ফাইলটি খুলুন। `Values` সেকশনের মধ্যে নিচের অতিরিক্ত মানটি যোগ করুন:

    ```json
    "REGISTRY_MANAGER_CONNECTION_STRING": "<connection string>"
    ```

    `<connection string>`-এর জায়গায় আগের ধাপে প্রাপ্ত মানটি দিন। এটি বৈধ JSON করতে উপরের লাইনের পরে একটি কমা যোগ করতে হবে।

### কাজ - একটি ডিভাইসে সরাসরি মেথড রিকোয়েস্ট পাঠান

1. Registry Manager-এর SDK একটি Pip প্যাকেজের মাধ্যমে উপলব্ধ। `requirements.txt` ফাইলে নিচের লাইনটি যোগ করুন এই প্যাকেজের উপর নির্ভরতা যোগ করতে:

    ```sh
    azure-iot-hub
    ```

1. নিশ্চিত করুন যে VS Code টার্মিনালে ভার্চুয়াল এনভায়রনমেন্ট সক্রিয় রয়েছে, এবং Pip প্যাকেজগুলি ইনস্টল করতে নিচের কমান্ডটি চালান:

    ```sh
    pip install -r requirements.txt
    ```

1. `__init__.py` ফাইলে নিচের ইমপোর্টগুলি যোগ করুন:

    ```python
    import json
    import os
    from azure.iot.hub import IoTHubRegistryManager
    from azure.iot.hub.models import CloudToDeviceMethod
    ```

    এটি কিছু সিস্টেম লাইব্রেরি, Registry Manager-এর সাথে ইন্টারঅ্যাক্ট করার লাইব্রেরি এবং সরাসরি মেথড রিকোয়েস্ট পাঠানোর লাইব্রেরি ইমপোর্ট করে।

1. `main` মেথডের ভিতরের কোডটি সরিয়ে ফেলুন, তবে মেথডটি রেখে দিন।

1. `main` মেথডে নিচের কোডটি যোগ করুন:

    ```python
    body = json.loads(event.get_body().decode('utf-8'))
    device_id = event.iothub_metadata['connection-device-id']

    logging.info(f'Received message: {body} from {device_id}')
    ```

    এই কোডটি ইভেন্টের বডি থেকে IoT ডিভাইস দ্বারা পাঠানো JSON বার্তাটি বের করে।

    এটি বার্তার সাথে পাঠানো অ্যানোটেশন থেকে ডিভাইস আইডি পায়। ইভেন্টের বডি টেলিমেট্রি হিসেবে পাঠানো বার্তাটি ধারণ করে, এবং `iothub_metadata` ডিকশনারি IoT Hub দ্বারা সেট করা প্রোপার্টি যেমন বার্তা প্রেরণকারী ডিভাইসের আইডি এবং বার্তা প্রেরণের সময় ধারণ করে।

    এই তথ্যটি লগ করা হয়। Functions অ্যাপটি স্থানীয়ভাবে চালানোর সময় আপনি এই লগিংটি টার্মিনালে দেখতে পাবেন।

1. এর নিচে নিচের কোডটি যোগ করুন:

    ```python
    soil_moisture = body['soil_moisture']

    if soil_moisture > 450:
        direct_method = CloudToDeviceMethod(method_name='relay_on', payload='{}')
    else:
        direct_method = CloudToDeviceMethod(method_name='relay_off', payload='{}')
    ```

    এই কোডটি বার্তা থেকে soil moisture বের করে। এটি তারপর soil moisture চেক করে এবং মানের উপর ভিত্তি করে `relay_on` বা `relay_off` সরাসরি মেথড রিকোয়েস্টের জন্য একটি হেল্পার ক্লাস তৈরি করে। মেথড রিকোয়েস্টে কোনো payload প্রয়োজন হয় না, তাই একটি খালি JSON ডকুমেন্ট পাঠানো হয়।

1. এর নিচে নিচের কোডটি যোগ করুন:

    ```python
    logging.info(f'Sending direct method request for {direct_method.method_name} for device {device_id}')

    registry_manager_connection_string = os.environ['REGISTRY_MANAGER_CONNECTION_STRING']
    registry_manager = IoTHubRegistryManager(registry_manager_connection_string)
    ```
এই কোডটি `local.settings.json` ফাইল থেকে `REGISTRY_MANAGER_CONNECTION_STRING` লোড করে। এই ফাইলের মানগুলো পরিবেশ ভেরিয়েবল হিসেবে উপলব্ধ হয় এবং সেগুলো `os.environ` ফাংশন ব্যবহার করে পড়া যায়, যা সমস্ত পরিবেশ ভেরিয়েবলের একটি ডিকশনারি প্রদান করে।

> 💁 যখন এই কোডটি ক্লাউডে ডিপ্লয় করা হয়, তখন `local.settings.json` ফাইলের মানগুলো *Application Settings* হিসেবে সেট করা হয় এবং সেগুলো পরিবেশ ভেরিয়েবল থেকে পড়া যায়।

এরপর কোডটি সংযোগ স্ট্রিং ব্যবহার করে Registry Manager হেল্পার ক্লাসের একটি ইনস্ট্যান্স তৈরি করে।

1. এর নিচে নিচের কোডটি যোগ করুন:

    ```python
    registry_manager.invoke_device_method(device_id, direct_method)

    logging.info('Direct method request sent!')
    ```

    এই কোডটি রেজিস্ট্রি ম্যানেজারকে টেলিমেট্রি পাঠানো ডিভাইসটিতে সরাসরি মেথড রিকোয়েস্ট পাঠাতে বলে।

    > 💁 পূর্ববর্তী পাঠে তৈরি করা অ্যাপের সংস্করণগুলোতে, যেখানে MQTT ব্যবহার করা হয়েছিল, রিলে নিয়ন্ত্রণ কমান্ডগুলো সব ডিভাইসে পাঠানো হতো। কোডটি ধরে নিত যে আপনার কেবল একটি ডিভাইস আছে। এই সংস্করণটি একটি নির্দিষ্ট ডিভাইসে মেথড রিকোয়েস্ট পাঠায়, তাই এটি একাধিক ময়েশ্চার সেন্সর এবং রিলে সেটআপ থাকলেও কাজ করবে, সঠিক ডিভাইসে সঠিক মেথড রিকোয়েস্ট পাঠাবে।

1. Functions অ্যাপ চালান এবং নিশ্চিত করুন যে আপনার IoT ডিভাইস ডেটা পাঠাচ্ছে। আপনি বার্তাগুলো প্রক্রিয়াকৃত হতে এবং সরাসরি মেথড রিকোয়েস্ট পাঠানো হতে দেখবেন। মাটির ভেজা সেন্সরটি মাটির ভিতরে এবং বাইরে সরান এবং দেখুন মানগুলো পরিবর্তিত হচ্ছে এবং রিলে চালু ও বন্ধ হচ্ছে।

> 💁 আপনি এই কোডটি [code/functions](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud/code/functions) ফোল্ডারে খুঁজে পেতে পারেন।

## আপনার সার্ভারলেস কোড ক্লাউডে ডিপ্লয় করুন

আপনার কোড এখন লোকালভাবে কাজ করছে, তাই পরবর্তী ধাপ হলো Functions অ্যাপটি ক্লাউডে ডিপ্লয় করা।

### টাস্ক - ক্লাউড রিসোর্স তৈরি করুন

আপনার Functions অ্যাপটি Azure-এ একটি Functions App রিসোর্সে ডিপ্লয় করতে হবে, যা আপনার IoT Hub-এর জন্য তৈরি করা Resource Group-এর ভিতরে থাকবে। এছাড়াও, Azure-এ একটি Storage Account তৈরি করতে হবে লোকাল এমুলেটেড স্টোরেজটি প্রতিস্থাপন করার জন্য।

1. একটি স্টোরেজ অ্যাকাউন্ট তৈরি করতে নিচের কমান্ডটি চালান:

    ```sh
    az storage account create --resource-group soil-moisture-sensor \
                              --sku Standard_LRS \
                              --name <storage_name> 
    ```

    `<storage_name>`-এর জায়গায় আপনার স্টোরেজ অ্যাকাউন্টের জন্য একটি নাম দিন। এটি গ্লোবালি ইউনিক হতে হবে কারণ এটি স্টোরেজ অ্যাকাউন্ট অ্যাক্সেস করার জন্য ব্যবহৃত URL-এর অংশ গঠন করে। এই নামের জন্য কেবল ছোট হাতের অক্ষর এবং সংখ্যা ব্যবহার করা যাবে, অন্য কোনো ক্যারেক্টার নয়, এবং এটি ২৪ ক্যারেক্টারে সীমাবদ্ধ। উদাহরণস্বরূপ, `sms` ব্যবহার করুন এবং শেষে একটি ইউনিক আইডেন্টিফায়ার যোগ করুন, যেমন কিছু র‍্যান্ডম শব্দ বা আপনার নাম।

    `--sku Standard_LRS` প্রাইসিং টিয়ার নির্বাচন করে, যা সর্বনিম্ন খরচের জেনারেল-পারপাস অ্যাকাউন্ট নির্বাচন করে। স্টোরেজের কোনো ফ্রি টিয়ার নেই, এবং আপনি যা ব্যবহার করেন তার জন্যই খরচ হয়। খরচ তুলনামূলকভাবে কম, সবচেয়ে ব্যয়বহুল স্টোরেজ প্রতি গিগাবাইট সংরক্ষণের জন্য মাসে ০.০৫ মার্কিন ডলারের কম।

    ✅ [Azure Storage Account pricing page](https://azure.microsoft.com/pricing/details/storage/?WT.mc_id=academic-17441-jabenn)-এ প্রাইসিং সম্পর্কে পড়ুন।

1. একটি Function App তৈরি করতে নিচের কমান্ডটি চালান:

    ```sh
    az functionapp create --resource-group soil-moisture-sensor \
                          --runtime python \
                          --functions-version 3 \
                          --os-type Linux \
                          --consumption-plan-location <location> \
                          --storage-account <storage_name> \
                          --name <functions_app_name>
    ```

    `<location>`-এর জায়গায় পূর্ববর্তী পাঠে Resource Group তৈরি করার সময় ব্যবহৃত অবস্থানটি দিন।

    `<storage_name>`-এর জায়গায় পূর্ববর্তী ধাপে তৈরি করা স্টোরেজ অ্যাকাউন্টের নাম দিন।

    `<functions_app_name>`-এর জায়গায় আপনার Functions App-এর জন্য একটি ইউনিক নাম দিন। এটি গ্লোবালি ইউনিক হতে হবে কারণ এটি Functions App অ্যাক্সেস করার জন্য ব্যবহৃত URL-এর অংশ গঠন করে। উদাহরণস্বরূপ, `soil-moisture-sensor-` ব্যবহার করুন এবং শেষে একটি ইউনিক আইডেন্টিফায়ার যোগ করুন, যেমন কিছু র‍্যান্ডম শব্দ বা আপনার নাম।

    `--functions-version 3` অপশনটি Azure Functions-এর সংস্করণ নির্ধারণ করে। সংস্করণ ৩ হলো সর্বশেষ সংস্করণ।

    `--os-type Linux` Functions রানটাইমকে এই ফাংশনগুলো হোস্ট করার জন্য Linux ব্যবহার করতে বলে। Functions Linux বা Windows-এ হোস্ট করা যেতে পারে, ব্যবহৃত প্রোগ্রামিং ভাষার উপর নির্ভর করে। Python অ্যাপ কেবল Linux-এ সমর্থিত।

### টাস্ক - আপনার অ্যাপ্লিকেশন সেটিংস আপলোড করুন

আপনার Functions App ডেভেলপ করার সময়, আপনি IoT Hub-এর জন্য সংযোগ স্ট্রিং সংরক্ষণ করতে `local.settings.json` ফাইলে কিছু সেটিংস সংরক্ষণ করেছিলেন। এগুলো Azure-এ আপনার Function App-এর Application Settings-এ লিখতে হবে যাতে আপনার কোড এগুলো ব্যবহার করতে পারে।

> 🎓 `local.settings.json` ফাইলটি কেবল লোকাল ডেভেলপমেন্ট সেটিংসের জন্য, এবং এগুলো সোর্স কোড কন্ট্রোলে (যেমন GitHub) চেক-ইন করা উচিত নয়। ক্লাউডে ডিপ্লয় করার সময়, Application Settings ব্যবহার করা হয়। Application Settings হলো ক্লাউডে হোস্ট করা কী/ভ্যালু পেয়ার, যা পরিবেশ ভেরিয়েবল থেকে আপনার কোডে বা রানটাইমে পড়া হয় যখন আপনার কোড IoT Hub-এর সাথে সংযুক্ত হয়।

1. Functions App-এর Application Settings-এ `IOT_HUB_CONNECTION_STRING` সেটিং সেট করতে নিচের কমান্ডটি চালান:

    ```sh
    az functionapp config appsettings set --resource-group soil-moisture-sensor \
                                          --name <functions_app_name> \
                                          --settings "IOT_HUB_CONNECTION_STRING=<connection string>"
    ```

    `<functions_app_name>`-এর জায়গায় আপনার Functions App-এর জন্য ব্যবহৃত নাম দিন।

    `<connection string>`-এর জায়গায় আপনার `local.settings.json` ফাইল থেকে `IOT_HUB_CONNECTION_STRING`-এর মান দিন।

1. উপরের ধাপটি পুনরাবৃত্তি করুন, তবে `REGISTRY_MANAGER_CONNECTION_STRING`-এর মান `local.settings.json` ফাইল থেকে সংশ্লিষ্ট মান দিয়ে সেট করুন।

এই কমান্ডগুলো চালানোর সময়, এগুলো ফাংশন অ্যাপের সমস্ত Application Settings-এর একটি তালিকা আউটপুট করবে। আপনি এটি ব্যবহার করে নিশ্চিত করতে পারেন যে আপনার মানগুলো সঠিকভাবে সেট করা হয়েছে।

> 💁 আপনি `AzureWebJobsStorage`-এর জন্য একটি মান ইতিমধ্যে সেট করা দেখতে পাবেন। আপনার `local.settings.json` ফাইলে এটি লোকাল স্টোরেজ এমুলেটর ব্যবহার করার জন্য একটি মানে সেট করা হয়েছিল। যখন আপনি Functions App তৈরি করেন, তখন স্টোরেজ অ্যাকাউন্ট একটি প্যারামিটার হিসেবে পাস করা হয়, এবং এটি স্বয়ংক্রিয়ভাবে এই সেটিংয়ে সেট হয়।

### টাস্ক - আপনার Functions App ক্লাউডে ডিপ্লয় করুন

এখন Functions App প্রস্তুত, আপনার কোড ডিপ্লয় করা যেতে পারে।

1. VS Code টার্মিনাল থেকে নিচের কমান্ডটি চালান আপনার Functions App প্রকাশ করতে:

    ```sh
    func azure functionapp publish <functions_app_name>
    ```

    `<functions_app_name>`-এর জায়গায় আপনার Functions App-এর জন্য ব্যবহৃত নাম দিন।

কোডটি প্যাকেজ করা হবে এবং Functions App-এ পাঠানো হবে, যেখানে এটি ডিপ্লয় এবং শুরু হবে। প্রচুর কনসোল আউটপুট থাকবে, যা ডিপ্লয়মেন্টের নিশ্চিতকরণ এবং ডিপ্লয় করা ফাংশনের একটি তালিকা দিয়ে শেষ হবে। এই ক্ষেত্রে তালিকায় কেবল ট্রিগার থাকবে।

```output
Deployment successful.
Remote build succeeded!
Syncing triggers...
Functions in soil-moisture-sensor:
    iot-hub-trigger - [eventHubTrigger]
```

আপনার IoT ডিভাইস চালু রাখুন। মাটির আর্দ্রতার মাত্রা পরিবর্তন করুন মাটির ভেজা সেন্সরটি সরিয়ে বা মাটির ভিতরে-বাইরে সরিয়ে। আপনি দেখতে পাবেন মাটির আর্দ্রতার পরিবর্তনের সাথে সাথে রিলে চালু এবং বন্ধ হচ্ছে।

---

## 🚀 চ্যালেঞ্জ

পূর্ববর্তী পাঠে, আপনি রিলে টাইমিং পরিচালনা করেছিলেন MQTT বার্তা থেকে আনসাবস্ক্রাইব করে যখন রিলে চালু ছিল এবং এটি বন্ধ হওয়ার পর কিছু সময়ের জন্য। এখানে আপনি এই পদ্ধতি ব্যবহার করতে পারবেন না - আপনি আপনার IoT Hub ট্রিগার আনসাবস্ক্রাইব করতে পারবেন না।

আপনার Functions App-এ এটি পরিচালনার জন্য বিভিন্ন উপায় নিয়ে ভাবুন।

## পোস্ট-লেকচার কুইজ

[পোস্ট-লেকচার কুইজ](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/18)

## রিভিউ এবং সেলফ স্টাডি

* [Serverless Computing page on Wikipedia](https://wikipedia.org/wiki/Serverless_computing)-এ সার্ভারলেস কম্পিউটিং সম্পর্কে পড়ুন।
* Azure-এ সার্ভারলেস ব্যবহার এবং আরও কিছু উদাহরণ সম্পর্কে পড়ুন [Go serverless for your IoT needs Azure blog post](https://azure.microsoft.com/blog/go-serverless-for-your-iot-needs/?WT.mc_id=academic-17441-jabenn)।
* Azure Functions সম্পর্কে আরও জানুন [Azure Functions YouTube channel](https://www.youtube.com/c/AzureFunctions)-এ।

## অ্যাসাইনমেন্ট

[ম্যানুয়াল রিলে নিয়ন্ত্রণ যোগ করুন](assignment.md)

---

**অস্বীকৃতি**:  
এই নথিটি AI অনুবাদ পরিষেবা [Co-op Translator](https://github.com/Azure/co-op-translator) ব্যবহার করে অনুবাদ করা হয়েছে। আমরা যথাসাধ্য সঠিকতা নিশ্চিত করার চেষ্টা করি, তবে অনুগ্রহ করে মনে রাখবেন যে স্বয়ংক্রিয় অনুবাদে ত্রুটি বা অসঙ্গতি থাকতে পারে। মূল ভাষায় থাকা নথিটিকে প্রামাণিক উৎস হিসেবে বিবেচনা করা উচিত। গুরুত্বপূর্ণ তথ্যের জন্য, পেশাদার মানব অনুবাদ সুপারিশ করা হয়। এই অনুবাদ ব্যবহারের ফলে কোনো ভুল বোঝাবুঝি বা ভুল ব্যাখ্যা হলে আমরা দায়বদ্ধ থাকব না।