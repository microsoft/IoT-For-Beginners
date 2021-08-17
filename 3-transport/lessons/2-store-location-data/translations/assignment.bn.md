# ফাংশন বাইন্ডিং পর্যালোচনা

## নির্দেশাবলী

ফাংশন বাইন্ডিংগুলি মূলত আমাদের কোডগুলিকে `main` ফাংশন থেকে রিটার্ন করে ব্লব স্টোরেজে সংরক্ষণ করার সুযোগ দেয়। Azure স্টোরেজ অ্যাকাউন্ট এবং অন্যান্য বিবরণ `function.json` ফাইলে কনফিগার করা আছে।

Azure বা অন্যান্য Microsoft প্রযুক্তির সাথে কাজ করার সময়, তথ্যের সর্বোত্তম উৎস হল [docs.com এ Microsoft ডকুমেন্টেশনগুলো](https://docs.microsoft.com/?WT.mc_id=academic-17441-jabenn) । এই অ্যাসাইনমেন্টে আমাদেরকে আউটপুট বাইন্ডিং কিভাবে সেটআপ করতে হবে তা জানতে Azure Functions বাইন্ডিং ডকুমেন্টেশন পড়তে হবে।

কাজের আগে কিছু রিসোর্স  দেখে নেয়া যেতে পারেঃ

* [Azure Functions triggers and bindings concepts](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?tabs=python&WT.mc_id=academic-17441-jabenn)
* [Azure Blob storage bindings for Azure Functions overview](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob?WT.mc_id=academic-17441-jabenn)
* [Azure Blob storage output binding for Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob-output?tabs=python&WT.mc_id=academic-17441-jabenn)

## এসাইনমেন্ট মূল্যায়ন মানদন্ড

| ক্রাইটেরিয়া | দৃষ্টান্তমূলক (সর্বোত্তম) | পর্যাপ্ত (মাঝারি) | উন্নতি প্রয়োজন (নিম্নমান) |
| --------- | ------------------ | -------------- | -------------------- |
| ব্লব স্টোরেজ আউটপুট বাইন্ডিং কনফিগার করা | আউটপুট বাইন্ডিং কনফিগার করতে সক্ষম হয়েছিল, যেখানে ব্লবটি রিটার্ন এবং সফলভাবে ব্লব স্টোরেজে সংরক্ষণ হয়েছিলো | আউটপুট বাইন্ডিং কনফিগার করতে বা ব্লবটি রিটার্ন করতে সক্ষম হয়েছিল কিন্তু ব্লব স্টোরেজে সংরক্ষণ করতে পারেনি| আউটপুট বাইন্ডিং কনফিগার করতে ব্যার্থ |
