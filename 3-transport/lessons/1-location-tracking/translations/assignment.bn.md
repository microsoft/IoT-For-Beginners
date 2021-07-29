# অন্যান্য জিপিএস ডেটা পর্যালোচনা করা

## নির্দেশাবলী

আমাদের জিপিএস সেন্সর থেকে আসা NEMA বাক্যগুলিতে লোকেশন ছাড়াও অন্যান্য ডেটা রয়েছে। অতিরিক্ত ডেটা অনুসন্ধান করে  আইওটি ডিভাইসে তা ব্যবহার করি।

উদাহরণস্বরূপ - আমরা কী বর্তমান তারিখ এবং সময় পেতে পারি? আমরা যদি কোন মাইক্রোকন্ট্রোলার ব্যবহার করি, তবে  যেভাবে পূর্বের প্রজেক্টে এনটিপি সিগন্যাল ব্যবহার করেছি সেটাকে ব্যবহার করে জিপিএস ডেটা দ্বারা ঘড়ি সেট করা যাবে? আমরা কি উচ্চতা (সমুদ্রতল থেকে আমাদের উচ্চতা) বা বর্তমান গতি পেতে পারি?

If you are using a virtual IoT device, then you can get some of this data by sending NMEA sentences generated using tools [nmeagen.org](https://www.nmeagen.org).

আমরা যদি ভার্চুয়াল আইওটি ডিভাইস ব্যবহার করে থাকি, তবে NMEA sentences এর ডেটা [nmeagen.org](https://www.nmeagen.org) থেকে পেতে পারি।

## এসাইনমেন্ট মূল্যায়ন মানদন্ড

| ক্রাইটেরিয়া | দৃষ্টান্তমূলক (সর্বোত্তম) | পর্যাপ্ত (মাঝারি) | উন্নতি প্রয়োজন (নিম্নমান) |
| --------- | ------------------ | -------------- | -------------------- |
| আরো বেশি GPS data সংগ্রহ করা | টেলিমেট্রি হিসাবে বা আইওটি ডিভাইস সেট আপ এর মাধ্যমে আরো জিপিএস ডেটা পেতে এবং ব্যবহার করতে সক্ষম | আরো বেশি GPS data পেতে সক্ষম হলেও ব্যবহার করতে ব্যার্থ|আরো বেশি GPS data পেতে ব্যার্থ |