<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "b2e0a965723082b068f735aec0faf3f6",
  "translation_date": "2025-08-27T15:04:44+00:00",
  "source_file": "3-transport/lessons/2-store-location-data/assignment.md",
  "language_code": "bn"
}
-->
# ফাংশন বাইন্ডিং তদন্ত করুন

## নির্দেশাবলী

ফাংশন বাইন্ডিং আপনার কোডকে `main` ফাংশন থেকে ব্লব রিটার্ন করে ব্লব স্টোরেজে সংরক্ষণ করতে সক্ষম করে। Azure Storage অ্যাকাউন্ট, সংগ্রহ এবং অন্যান্য বিবরণ `function.json` ফাইলে কনফিগার করা থাকে।

Azure বা অন্যান্য Microsoft প্রযুক্তি নিয়ে কাজ করার সময়, তথ্যের সেরা উৎস হল [Microsoft ডকুমেন্টেশন docs.com-এ](https://docs.microsoft.com/?WT.mc_id=academic-17441-jabenn)। এই অ্যাসাইনমেন্টে আপনাকে Azure Functions বাইন্ডিং ডকুমেন্টেশন পড়তে হবে এবং আউটপুট বাইন্ডিং সেটআপ করার পদ্ধতি বের করতে হবে।

শুরু করার জন্য কিছু পৃষ্ঠার লিঙ্ক:

* [Azure Functions ট্রিগার এবং বাইন্ডিং ধারণা](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python)
* [Azure Functions-এর জন্য Azure Blob স্টোরেজ বাইন্ডিং ওভারভিউ](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob?WT.mc_id=academic-17441-jabenn)
* [Azure Functions-এর জন্য Azure Blob স্টোরেজ আউটপুট বাইন্ডিং](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob-output?WT.mc_id=academic-17441-jabenn&tabs=python)

## মূল্যায়ন

| মানদণ্ড | চমৎকার | পর্যাপ্ত | উন্নতির প্রয়োজন |
| -------- | --------- | -------- | ----------------- |
| ব্লব স্টোরেজ আউটপুট বাইন্ডিং কনফিগার করা | আউটপুট বাইন্ডিং কনফিগার করতে, ব্লব রিটার্ন করতে এবং এটি সফলভাবে ব্লব স্টোরেজে সংরক্ষণ করতে সক্ষম হয়েছে | আউটপুট বাইন্ডিং কনফিগার করতে বা ব্লব রিটার্ন করতে সক্ষম হয়েছে, কিন্তু এটি ব্লব স্টোরেজে সফলভাবে সংরক্ষণ করতে পারেনি | আউটপুট বাইন্ডিং কনফিগার করতে ব্যর্থ হয়েছে |

---

**অস্বীকৃতি**:  
এই নথিটি AI অনুবাদ পরিষেবা [Co-op Translator](https://github.com/Azure/co-op-translator) ব্যবহার করে অনুবাদ করা হয়েছে। আমরা যথাসাধ্য সঠিকতা নিশ্চিত করার চেষ্টা করি, তবে অনুগ্রহ করে মনে রাখবেন যে স্বয়ংক্রিয় অনুবাদে ত্রুটি বা অসঙ্গতি থাকতে পারে। মূল ভাষায় থাকা নথিটিকে প্রামাণিক উৎস হিসেবে বিবেচনা করা উচিত। গুরুত্বপূর্ণ তথ্যের জন্য, পেশাদার মানব অনুবাদ সুপারিশ করা হয়। এই অনুবাদ ব্যবহারের ফলে কোনো ভুল বোঝাবুঝি বা ভুল ব্যাখ্যা হলে আমরা দায়বদ্ধ থাকব না।