<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "24dc783a600e20251211987b36370e93",
  "translation_date": "2025-08-27T10:41:49+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/vm-iotedge.md",
  "language_code": "bn"
}
-->
# IoT Edge চালানোর জন্য একটি ভার্চুয়াল মেশিন তৈরি করুন

Azure-এ, আপনি একটি ভার্চুয়াল মেশিন তৈরি করতে পারেন - এটি ক্লাউডে একটি কম্পিউটার যা আপনি আপনার ইচ্ছামতো কনফিগার করতে পারেন এবং এতে আপনার নিজস্ব সফটওয়্যার চালাতে পারেন।

> 💁 ভার্চুয়াল মেশিন সম্পর্কে আরও জানতে, [Wikipedia-এর Virtual Machine পৃষ্ঠাটি](https://wikipedia.org/wiki/Virtual_machine) পড়ুন।

## কাজ - একটি IoT Edge ভার্চুয়াল মেশিন সেট আপ করুন

1. Azure IoT Edge পূর্বেই ইনস্টল করা একটি VM তৈরি করতে নিচের কমান্ডটি চালান:

    ```sh
    az deployment group create \
                --resource-group fruit-quality-detector \
                --template-uri https://raw.githubusercontent.com/Azure/iotedge-vm-deploy/1.2.0/edgeDeploy.json \
                --parameters dnsLabelPrefix=<vm_name> \
                --parameters adminUsername=<username> \
                --parameters deviceConnectionString="<connection_string>" \
                --parameters authenticationType=password \
                --parameters adminPasswordOrKey="<password>"
    ```

    `<vm_name>`-এর জায়গায় এই ভার্চুয়াল মেশিনের জন্য একটি নাম দিন। এটি বিশ্বব্যাপী ইউনিক হতে হবে, তাই `fruit-quality-detector-vm-` এর শেষে আপনার নাম বা অন্য কোনো মান যোগ করুন।

    `<username>` এবং `<password>`-এর জায়গায় VM-এ লগইন করার জন্য একটি ইউজারনেম এবং পাসওয়ার্ড দিন। এগুলো তুলনামূলকভাবে নিরাপদ হতে হবে, তাই admin/password ব্যবহার করা যাবে না।

    `<connection_string>`-এর জায়গায় আপনার `fruit-quality-detector-edge` IoT Edge ডিভাইসের কানেকশন স্ট্রিং দিন।

    এটি একটি `DS1 v2` ভার্চুয়াল মেশিন হিসেবে কনফিগার করা VM তৈরি করবে। এই ক্যাটাগরিগুলি মেশিনের ক্ষমতা এবং খরচ নির্দেশ করে। এই VM-এ 1 CPU এবং 3.5GB RAM রয়েছে।

    > 💰 এই VM-গুলির বর্তমান মূল্য [Azure Virtual Machine pricing guide](https://azure.microsoft.com/pricing/details/virtual-machines/linux/?WT.mc_id=academic-17441-jabenn)-এ দেখতে পারেন।

    VM তৈরি হয়ে গেলে, IoT Edge runtime স্বয়ংক্রিয়ভাবে ইনস্টল হবে এবং এটি আপনার IoT Hub-এর সাথে `fruit-quality-detector-edge` ডিভাইস হিসেবে সংযুক্ত হবে।

1. ইমেজ ক্লাসিফায়ার কল করার জন্য VM-এর IP ঠিকানা বা DNS নাম প্রয়োজন হবে। এটি পেতে নিচের কমান্ডটি চালান:

    ```sh
    az vm list --resource-group fruit-quality-detector \
               --output table \
               --show-details
    ```

    `PublicIps` ফিল্ড বা `Fqdns` ফিল্ডের একটি কপি নিন।

1. VM-গুলি অর্থ ব্যয় করে। লেখার সময়, একটি DS1 VM-এর খরচ প্রায় $0.06 প্রতি ঘণ্টা। খরচ কমানোর জন্য, আপনি যখন VM ব্যবহার করছেন না তখন এটি বন্ধ করে দিন এবং প্রকল্প শেষ হলে এটি মুছে ফেলুন।

    আপনি আপনার VM-কে প্রতিদিন একটি নির্দিষ্ট সময়ে স্বয়ংক্রিয়ভাবে বন্ধ করার জন্য কনফিগার করতে পারেন। এটি করলে আপনি যদি বন্ধ করতে ভুলে যান, তাহলে স্বয়ংক্রিয় বন্ধ হওয়া পর্যন্ত সময়ের জন্যই বিল করা হবে। এটি সেট করতে নিচের কমান্ডটি ব্যবহার করুন:

    ```sh
    az vm auto-shutdown --resource-group fruit-quality-detector \
                        --name <vm_name> \
                        --time <shutdown_time_utc>
    ```

    `<vm_name>`-এর জায়গায় আপনার ভার্চুয়াল মেশিনের নাম দিন।

    `<shutdown_time_utc>`-এর জায়গায় UTC সময় দিন যখন আপনি VM বন্ধ করতে চান। এটি 4 ডিজিটে HHMM হিসেবে দিতে হবে। উদাহরণস্বরূপ, যদি আপনি UTC-তে মধ্যরাতে বন্ধ করতে চান, তাহলে এটি `0000` হবে। USA-এর পশ্চিম উপকূলে সন্ধ্যা ৭:৩০PM-এর জন্য, আপনি `0230` ব্যবহার করবেন (USA পশ্চিম উপকূলে সন্ধ্যা ৭:৩০PM UTC-তে ২:৩০AM)।

1. আপনার ইমেজ ক্লাসিফায়ার এই এজ ডিভাইসে চলবে, যা পোর্ট 80-এ (স্ট্যান্ডার্ড HTTP পোর্ট) শুনবে। ডিফল্টভাবে, ভার্চুয়াল মেশিনগুলিতে ইনবাউন্ড পোর্ট ব্লক করা থাকে, তাই আপনাকে পোর্ট 80 সক্রিয় করতে হবে। পোর্টগুলি নেটওয়ার্ক সিকিউরিটি গ্রুপে সক্রিয় করা হয়, তাই প্রথমে আপনার VM-এর নেটওয়ার্ক সিকিউরিটি গ্রুপের নাম জানতে হবে, যা আপনি নিচের কমান্ডটি চালিয়ে খুঁজে পেতে পারেন:

    ```sh
    az network nsg list --resource-group fruit-quality-detector \
                        --output table
    ```

    `Name` ফিল্ডের মানটি কপি করুন।

1. নেটওয়ার্ক সিকিউরিটি গ্রুপে পোর্ট 80 খুলতে একটি নিয়ম যোগ করার জন্য নিচের কমান্ডটি চালান:

    ```sh
    az network nsg rule create \
                        --resource-group fruit-quality-detector \
                        --name Port_80 \
                        --protocol tcp \
                        --priority 1010 \
                        --destination-port-range 80 \
                        --nsg-name <nsg name>
    ```

    `<nsg name>`-এর জায়গায় আগের ধাপ থেকে নেটওয়ার্ক সিকিউরিটি গ্রুপের নাম দিন।

### কাজ - খরচ কমানোর জন্য আপনার VM পরিচালনা করুন

1. যখন আপনি আপনার VM ব্যবহার করছেন না, তখন এটি বন্ধ করে দিন। VM বন্ধ করতে নিচের কমান্ডটি ব্যবহার করুন:

    ```sh
    az vm deallocate --resource-group fruit-quality-detector \
                     --name <vm_name>
    ```

    `<vm_name>`-এর জায়গায় আপনার ভার্চুয়াল মেশিনের নাম দিন।

    > 💁 `az vm stop` নামে একটি কমান্ড রয়েছে যা VM বন্ধ করবে, কিন্তু এটি কম্পিউটারটি আপনার জন্য বরাদ্দ রাখে, তাই এটি এখনও চালু আছে বলে খরচ হয়।

1. VM পুনরায় চালু করতে নিচের কমান্ডটি ব্যবহার করুন:

    ```sh
    az vm start --resource-group fruit-quality-detector \
                --name <vm_name>
    ```

    `<vm_name>`-এর জায়গায় আপনার ভার্চুয়াল মেশিনের নাম দিন।

---

**অস্বীকৃতি**:  
এই নথিটি AI অনুবাদ পরিষেবা [Co-op Translator](https://github.com/Azure/co-op-translator) ব্যবহার করে অনুবাদ করা হয়েছে। আমরা যথাসম্ভব সঠিক অনুবাদের চেষ্টা করি, তবে অনুগ্রহ করে মনে রাখবেন যে স্বয়ংক্রিয় অনুবাদে ত্রুটি বা অসঙ্গতি থাকতে পারে। নথিটির মূল ভাষায় লেখা সংস্করণটিকেই প্রামাণিক উৎস হিসেবে বিবেচনা করা উচিত। গুরুত্বপূর্ণ তথ্যের জন্য, পেশাদার মানব অনুবাদ ব্যবহার করার পরামর্শ দেওয়া হচ্ছে। এই অনুবাদ ব্যবহারের ফলে সৃষ্ট কোনো ভুল বোঝাবুঝি বা ভুল ব্যাখ্যার জন্য আমরা দায়ী নই।