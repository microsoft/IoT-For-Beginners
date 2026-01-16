<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "e345843ccfeb7261d81500d19c64d476",
  "translation_date": "2025-08-28T16:59:35+00:00",
  "source_file": "3-transport/lessons/2-store-location-data/README.md",
  "language_code": "my"
}
-->
# Store location data

![A sketchnote overview of this lesson](../../../../../translated_images/my/lesson-12.ca7f53039712a3ec14ad6474d8445361c84adab643edc53fa6269b77895606bb.jpg)

> Sketchnote by [Nitya Narasimhan](https://github.com/nitya). Click the image for a larger version.

## Pre-lecture quiz

[Pre-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/23)

## အကျဉ်းချုပ်

ပြီးခဲ့တဲ့ သင်ခန်းစာမှာ GPS sensor ကို အသုံးပြုပြီး တည်နေရာဒေတာကို ဖမ်းယူနည်းကို သင်ယူခဲ့ပါတယ်။ ဒီဒေတာကို အသုံးပြုပြီး အစားအစာတင်ဆောင်ထားတဲ့ ထရပ်ကားရဲ့ တည်နေရာနဲ့ ခရီးစဉ်ကို မြင်သာအောင် ဖော်ပြဖို့အတွက် ဒေတာကို cloud-based IoT service ကို ပို့ပြီး တစ်နေရာရာမှာ သိမ်းဆည်းဖို့ လိုအပ်ပါတယ်။

ဒီသင်ခန်းစာမှာ IoT ဒေတာကို သိမ်းဆည်းနည်းများကို သင်ယူပြီး serverless code ကို အသုံးပြုပြီး IoT service မှ ဒေတာကို သိမ်းဆည်းနည်းကို လေ့လာပါမည်။

ဒီသင်ခန်းစာမှာ အောက်ပါအကြောင်းအရာများကို လေ့လာပါမည်-

* [Structured and unstructured data](../../../../../3-transport/lessons/2-store-location-data)
* [Send GPS data to an IoT Hub](../../../../../3-transport/lessons/2-store-location-data)
* [Hot, warm, and cold paths](../../../../../3-transport/lessons/2-store-location-data)
* [Handle GPS events using serverless code](../../../../../3-transport/lessons/2-store-location-data)
* [Azure Storage Accounts](../../../../../3-transport/lessons/2-store-location-data)
* [Connect your serverless code to storage](../../../../../3-transport/lessons/2-store-location-data)

## Structured and unstructured data

ကွန်ပျူတာစနစ်များသည် ဒေတာနှင့် ဆက်နွယ်နေပြီး ဒေတာသည် အမျိုးမျိုးသော ပုံစံများနှင့် အရွယ်အစားများရှိနိုင်သည်။ ဒေတာသည် တစ်ခုတည်းသော နံပါတ်များမှ စ၍ စာသားများ၊ ဗီဒီယိုများ၊ ပုံများနှင့် IoT ဒေတာများအထိ အမျိုးမျိုးရှိနိုင်သည်။ ဒေတာကို အများအားဖြင့် *structured* ဒေတာနှင့် *unstructured* ဒေတာဟူ၍ အမျိုးအစားနှစ်မျိုးအနက် တစ်ခုခုအဖြစ် ခွဲခြားနိုင်သည်။

* **Structured data** သည် အလွန်သေချာပြီး တင်းကျပ်သော ဖွဲ့စည်းမှုရှိသော ဒေတာဖြစ်ပြီး မပြောင်းလဲသော ဖွဲ့စည်းမှုကို လိုက်နာရသည်။ ဥပမာအားဖြင့် လူတစ်ဦး၏ အမည်၊ မွေးသက္ကရာဇ်နှင့် လိပ်စာတို့ပါဝင်သော ဒေတာ။

* **Unstructured data** သည် သေချာပြီး တင်းကျပ်သော ဖွဲ့စည်းမှုမရှိသော ဒေတာဖြစ်ပြီး ဖွဲ့စည်းမှုကို မကြာခဏ ပြောင်းလဲနိုင်သည်။ ဥပမာအားဖြင့် စာရွက်စာတမ်းများ၊ စာရေးထားသော စာရွက်စာတမ်းများ သို့မဟုတ် စာရင်းဇယားများ။

✅ သုတေသနလုပ်ပါ- Structured ဒေတာနှင့် Unstructured ဒေတာ၏ အခြားဥပမာများကို စဉ်းစားနိုင်ပါသလား။

> 💁 Semi-structured data ဆိုတာ Structured ဖြစ်ပေမယ့် အတိအကျသော စာရင်းဇယားများတွင် မထည့်နိုင်သော ဒေတာဖြစ်သည်။

IoT ဒေတာသည် အများအားဖြင့် Unstructured ဒေတာအဖြစ် သတ်မှတ်နိုင်သည်။

သင်သည် စိုက်ပျိုးရေးလုပ်ငန်းကြီးတစ်ခု၏ ယာဉ်အုပ်စုများတွင် IoT စက်ပစ္စည်းများ ထည့်သွင်းနေသည်ဟု စဉ်းစားပါ။ ယာဉ်အမျိုးအစားအလိုက် ကွဲပြားသော စက်ပစ္စည်းများကို အသုံးပြုလိုနိုင်ပါသည်။ ဥပမာအားဖြင့်-

* စိုက်ပျိုးရေးယာဉ်များ (ဥပမာ- ထရက်တာများ) အတွက် GPS ဒေတာကို အသုံးပြု၍ သင့်ယာဉ်များသည် သင့်လယ်ကွင်းများတွင် အလုပ်လုပ်နေကြောင်း သေချာစေပါသည်။
* အစားအစာကို ဂိုဒေါင်များသို့ ပို့ဆောင်နေသော ထရပ်ကားများအတွက် GPS ဒေတာအပြင် ယာဉ်မောင်း၏ လုံခြုံမှုကို သေချာစေရန် အရှိန်နှင့် အရှိန်မြှင့်ဒေတာများ၊ ယာဉ်မောင်း၏ အမည်နှင့် စတင်/ရပ်တန့်ဒေတာများကို အသုံးပြုပါသည်။
* အအေးခံထရပ်ကားများအတွက် အစားအစာများသည် အပူလွန်ကဲခြင်း သို့မဟုတ် အအေးလွန်ကဲခြင်းကြောင့် ပျက်စီးမသွားစေရန် အပူချိန်ဒေတာကို အသုံးပြုပါသည်။

ဒီဒေတာသည် အမြဲပြောင်းလဲနေပါသည်။ ဥပမာအားဖြင့် IoT စက်ပစ္စည်းသည် ထရပ်ကား၏ ကုန်းတင်တွင်ရှိနေပါက အအေးခံကုန်းတင်ကို အသုံးပြုသောအခါတွင်သာ အပူချိန်ဒေတာကို ပေးပို့နိုင်ပါသည်။

✅ IoT ဒေတာအခြားအမျိုးအစားများကို ဖမ်းယူနိုင်ပါသလား? ထရပ်ကားများ သယ်ဆောင်နိုင်သော အမျိုးမျိုးသော အလွှာများနှင့် ပြုပြင်ထိန်းသိမ်းမှုဒေတာများကို စဉ်းစားပါ။

ဒီဒေတာသည် ယာဉ်အမျိုးအစားအလိုက် ကွဲပြားနေပါသည်။ သို့သော် ဒေတာအားလုံးကို တစ်နေရာတည်းရှိ IoT service သို့ ပေးပို့ပြီး အမျိုးမျိုးသော ဖွဲ့စည်းမှုများနှင့် အလုပ်လုပ်နိုင်သော နည်းလမ်းဖြင့် သိမ်းဆည်းရန် လိုအပ်ပါသည်။

### SQL vs NoSQL storage

Database ဆိုတာ ဒေတာကို သိမ်းဆည်းပြီး ရှာဖွေနိုင်စေသော service များဖြစ်သည်။ Database များကို SQL နှင့် NoSQL ဟူ၍ အမျိုးအစားနှစ်မျိုးခွဲခြားနိုင်သည်။

#### SQL databases

ပထမဆုံး Database များသည် Relational Database Management Systems (RDBMS) သို့မဟုတ် Relational Database များဖြစ်သည်။ SQL Database များဟုလည်း သိထားကြသည်။ SQL Database များသည် Structured Query Language (SQL) ကို အသုံးပြုပြီး ဒေတာကို ထည့်သွင်း၊ ဖယ်ရှား၊ ပြင်ဆင် သို့မဟုတ် ရှာဖွေနိုင်သည်။ Database များတွင် schema - စာရင်းဇယားများနှင့် ဆက်နွယ်မှုများပါဝင်သော ဖွဲ့စည်းမှုတစ်ခုရှိသည်။ 

![A relational database with the ID of the User table relating to the user ID column of the purchases table, and the ID of the products table relating to the product ID of the purchases table](../../../../../translated_images/my/sql-database.be160f12bfccefd3.webp)

ဥပမာအားဖြင့် သင်သည် အသုံးပြုသူ၏ ကိုယ်ရေးအချက်အလက်များကို စာရင်းဇယားတစ်ခုတွင် သိမ်းဆည်းလိုပါက အသုံးပြုသူတစ်ဦးစီအတွက် ထူးခြားသော ID တစ်ခုရှိပြီး အမည်နှင့် လိပ်စာတို့ပါဝင်သော စာရင်းဇယားတစ်ခုတွင် ထည့်သွင်းထားသည်။ သင်သည် အသုံးပြုသူ၏ ဝယ်ယူမှုများကို သိမ်းဆည်းလိုပါက အသစ်သော စာရင်းဇယားတွင် အသုံးပြုသူ၏ ID ကို ထည့်သွင်းထားသော ကော်လံတစ်ခုရှိသည်။ 

SQL Database များသည် Structured ဒေတာကို သိမ်းဆည်းရန် အကောင်းဆုံးဖြစ်ပြီး schema ကို လိုက်နာရန် လိုအပ်သည်။

✅ SQL ကို မသုံးဖူးပါက [SQL page on Wikipedia](https://wikipedia.org/wiki/SQL) တွင် ဖတ်ရှုပါ။

Microsoft SQL Server, MySQL, PostgreSQL တို့သည် SQL Database များဖြစ်သည်။

✅ သုတေသနလုပ်ပါ- SQL Database များနှင့် ၎င်းတို့၏ စွမ်းဆောင်ရည်များကို ဖတ်ရှုပါ။

#### NoSQL database

NoSQL Database များသည် SQL Database များ၏ တင်းကျပ်သော ဖွဲ့စည်းမှုမရှိသောကြောင့် NoSQL ဟုခေါ်သည်။ Document Database များဟုလည်း သိထားကြသည်။

> 💁 NoSQL Database များသည် ၎င်းတို့၏ နာမည်နှင့် မညီဘဲ SQL ကို အသုံးပြုပြီး ဒေတာကို ရှာဖွေနိုင်စေသည်။

![Documents in folders in a NoSQL database](../../../../../translated_images/my/noqsl-database.62d24ccf5b73f60d35c245a8533f1c7147c0928e955b82cb290b2e184bb434df.png)

NoSQL Database များတွင် schema မရှိသောကြောင့် Unstructured ဒေတာကို သိမ်းဆည်းနိုင်သည်။ JSON document များကို အသုံးပြုပြီး သိမ်းဆည်းနိုင်သည်။ 

ဥပမာအားဖြင့် စိုက်ပျိုးရေးယာဉ်များမှ IoT ဒေတာကို သိမ်းဆည်းလိုပါက အချို့တွင် accelerometer နှင့် အရှိန်ဒေတာများပါဝင်နိုင်ပြီး အချို့တွင် ကုန်းတင်၏ အပူချိန်ဒေတာများပါဝင်နိုင်သည်။ 

Azure CosmosDB, MongoDB, CouchDB တို့သည် NoSQL Database များဖြစ်သည်။

✅ သုတေသနလုပ်ပါ- NoSQL Database များနှင့် ၎င်းတို့၏ စွမ်းဆောင်ရည်များကို ဖတ်ရှုပါ။

ဒီသင်ခန်းစာမှာ IoT ဒေတာကို သိမ်းဆည်းရန် NoSQL storage ကို အသုံးပြုပါမည်။

## Send GPS data to an IoT Hub

ပြီးခဲ့တဲ့ သင်ခန်းစာမှာ သင်သည် GPS sensor ကို အသုံးပြုပြီး GPS ဒေတာကို ဖမ်းယူခဲ့သည်။ Cloud-based IoT service တွင် ဒေတာကို သိမ်းဆည်းရန် IoT Hub သို့ ပေးပို့ရန် လိုအပ်သည်။

![Sending GPS telemetry from an IoT device to IoT Hub](../../../../../translated_images/my/gps-telemetry-iot-hub.8115335d51cd2c1285d20e9d1b18cf685e59a8e093e7797291ef173445af6f3d.png)

### Task - send GPS data to an IoT Hub

1. Free tier ကို အသုံးပြုပြီး IoT Hub အသစ်တစ်ခု ဖန်တီးပါ။

    > ⚠️ [Project 2, lesson 4](../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/README.md#create-an-iot-service-in-the-cloud) မှ IoT Hub ဖန်တီးနည်းကို လိုအပ်ပါက ပြန်လည်ကြည့်ပါ။

    Resource Group အသစ်တစ်ခု ဖန်တီးပါ။ Resource Group ကို `gps-sensor` ဟု အမည်ပေးပါ။ IoT Hub ကို `gps-sensor-<your name>` အဖြစ် ထူးခြားသော အမည်ပေးပါ။

    > 💁 Project 2 မှ IoT Hub ကို အသုံးပြုနေပါက ထပ်မံအသုံးပြုနိုင်သည်။ 

1. IoT Hub တွင် `gps-sensor` ဟု အမည်ပေးပြီး device အသစ်တစ်ခု ထည့်သွင်းပါ။ Device connection string ကို ရယူပါ။

1. Device code ကို update လုပ်ပြီး IoT Hub သို့ GPS ဒေတာကို ပေးပို့ပါ။

    > ⚠️ [Project 2, lesson 4](../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/README.md#connect-your-device-to-the-iot-service) မှ device ကို IoT service နှင့် ချိတ်ဆက်နည်းကို လိုအပ်ပါက ပြန်လည်ကြည့်ပါ။

1. GPS ဒေတာကို JSON format ဖြင့် ပေးပို့ပါ-

    ```json
    {
        "gps" :
        {
            "lat" : <latitude>,
            "lon" : <longitude>
        }
    }
    ```

1. GPS ဒေတာကို တစ်မိနစ်တစ်ကြိမ်ပေးပို့ပါ။

Wio Terminal ကို အသုံးပြုပါက လိုအပ်သော libraries အားလုံးကို ထည့်သွင်းပြီး NTP server ကို အသုံးပြုပြီး အချိန်ကို သတ်မှတ်ပါ။ 

```cpp
DynamicJsonDocument doc(1024);
doc["gps"]["lat"] = gps.location.lat();
doc["gps"]["lon"] = gps.location.lng();
```

Virtual IoT device ကို အသုံးပြုပါက virtual environment ကို အသုံးပြုပါ။

Raspberry Pi နှင့် Virtual IoT device နှစ်ခုစလုံးအတွက် ```python
message_json = { "gps" : { "lat":lat, "lon":lon } }
print("Sending telemetry", message_json)
message = Message(json.dumps(message_json))
``` ကို အသုံးပြုပါ။

> 💁 [code/wio-terminal](../../../../../3-transport/lessons/2-store-location-data/code/wio-terminal), [code/pi](../../../../../3-transport/lessons/2-store-location-data/code/pi) သို့မဟုတ် [code/virtual-device](../../../../../3-transport/lessons/2-store-location-data/code/virtual-device) folder တွင် code ကို ရှာနိုင်သည်။

Device code ကို run လုပ်ပြီး `az iot hub monitor-events` CLI command ကို အသုံးပြုပြီး IoT Hub သို့ message များရောက်ရှိနေကြောင်း သေချာပါ။

## Hot, warm, and cold paths

IoT device မှ cloud သို့ ဒေတာကို ပေးပို့သောအခါ ဒေတာအားလုံးကို real-time processing မလုပ်နိုင်ပါ။ 

### Hot path

Hot path သည် real-time သို့မဟုတ် near real-time processing လိုအပ်သော ဒေတာကို ရည်ညွှန်းသည်။ 

### Warm path

Warm path သည် ဒေတာကို အနည်းငယ်နောက်ကျပြီး process လုပ်နိုင်သည်။

### Cold path

Cold path သည် ရှေးဟောင်းဒေတာကို သိမ်းဆည်းပြီး အချိန်မရွေး process လုပ်နိုင်သည်။

✅ သင်ဖမ်းယူထားသော ဒေတာသည် hot, warm သို့မဟုတ် cold path ဒေတာဖြစ်ပါသလား?

## Handle GPS events using serverless code

IoT Hub သို့ ဒေတာရောက်ရှိပြီးနောက် serverless code ကို အသုံးပြုပြီး event များကို လိုက်နာနိုင်သည်။ 

![Sending GPS telemetry from an IoT device to IoT Hub, then to Azure Functions via an event hub trigger](../../../../../translated_images/my/gps-telemetry-iot-hub-functions.24d3fa5592455e9f4e2fe73856b40c3915a292b90263c31d652acfd976cfedd8.png)

### Task - handle GPS events using serverless code

1. Azure Functions CLI ကို အသုံးပြုပြီး Azure Functions app တစ်ခု ဖန်တီးပါ။ Python runtime ကို အသုံးပြုပါ။ Folder ကို `gps-trigger` ဟု အမည်ပေးပါ။ Virtual environment ကို ဖန်တီးပါ။
⚠️ သင်လိုအပ်ပါက [Azure Functions Project ကို project 2, lesson 5 မှ ဖန်တီးရန်အတွက် လမ်းညွှန်ချက်များ](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#create-a-serverless-application) ကို ကိုးကားနိုင်ပါသည်။
1. IoT Hub ရဲ့ Event Hub အဆင့်ဆင် endpoint ကို အသုံးပြုတဲ့ IoT Hub event trigger ကို ထည့်ပါ။

    > ⚠️ လိုအပ်ပါက [Project 2, Lesson 5 မှ IoT Hub event trigger တစ်ခုကို ဖန်တီးရန်အတွက် လမ်းညွှန်ချက်များ](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#create-an-iot-hub-event-trigger) ကို ရှာဖွေကြည့်နိုင်ပါသည်။

1. `local.settings.json` ဖိုင်တွင် Event Hub အဆင့်ဆင် endpoint connection string ကို သတ်မှတ်ပြီး၊ `function.json` ဖိုင်တွင် အဲဒီ entry အတွက် key ကို အသုံးပြုပါ။

1. Azurite app ကို ဒေသခံ storage emulator အဖြစ် အသုံးပြုပါ။

1. သင့် functions app ကို run လုပ်ပြီး GPS device မှ event များကို လက်ခံနေကြောင်း သေချာပါစေ။ သင့် IoT device ကိုလည်း run လုပ်ပြီး GPS data ပေးပို့နေကြောင်း သေချာပါစေ။

    ```output
    Python EventHub trigger processed an event: {"gps": {"lat": 47.73481, "lon": -122.25701}}
    ```

## Azure Storage Accounts

![Azure Storage logo](../../../../../translated_images/my/azure-storage-logo.605c0f602c640d482a80f1b35a2629a32d595711b7ab1d7ceea843250615ff32.png)

Azure Storage Accounts သည် အမျိုးမျိုးသောနည်းလမ်းများဖြင့် data ကို သိမ်းဆည်းနိုင်သော အထွေထွေ storage service ဖြစ်သည်။ Blob, queue, table, file အဖြစ် data ကို သိမ်းဆည်းနိုင်ပြီး တစ်ချိန်တည်းတွင် အားလုံးကို သိမ်းဆည်းနိုင်သည်။

### Blob storage

*Blob* ဆိုသည်မှာ binary large objects ကို ဆိုလိုသည်။ သို့သော် unstructured data အမျိုးအစားအားလုံးကို ဆိုလိုသော term ဖြစ်လာသည်။ JSON document များမှ image နှင့် movie ဖိုင်များအထိ data များကို blob storage တွင် သိမ်းဆည်းနိုင်သည်။ Blob storage တွင် *containers* ဆိုသော buckets ရှိပြီး၊ relational database တွင် tables များလို data ကို သိမ်းဆည်းနိုင်သည်။ Container များတွင် folder များရှိနိုင်ပြီး၊ folder တစ်ခုတွင် အခြား folder များပါရှိနိုင်သည်။ ဒါသည် သင့် computer hard disk တွင် file များကို သိမ်းဆည်းသည့် နည်းလမ်းနှင့် ဆင်တူသည်။

ဒီ lesson တွင် IoT data ကို သိမ်းဆည်းရန် blob storage ကို အသုံးပြုမည်။

✅ သုတေသနလုပ်ပါ: [Azure Blob Storage](https://docs.microsoft.com/azure/storage/blobs/storage-blobs-overview?WT.mc_id=academic-17441-jabenn) ကို ဖတ်ရှုပါ။

### Table storage

Table storage သည် semi-structured data ကို သိမ်းဆည်းရန် အထူးသင့်လျော်သည်။ Table storage သည် NoSQL database ဖြစ်ပြီး၊ အစပိုင်းတွင် table set များကို သတ်မှတ်ရန် မလိုအပ်ပါ။ သို့သော် data ကို table များတွင် သိမ်းဆည်းရန် အထူးဒီဇိုင်းလုပ်ထားသည်။

✅ သုတေသနလုပ်ပါ: [Azure Table Storage](https://docs.microsoft.com/azure/storage/tables/table-storage-overview?WT.mc_id=academic-17441-jabenn) ကို ဖတ်ရှုပါ။

### Queue storage

Queue storage သည် 64KB အရွယ်အစားရှိသော message များကို queue တွင် သိမ်းဆည်းနိုင်သည်။ Message များကို queue ရဲ့ နောက်ဆုံးတွင် ထည့်ပြီး၊ ရှေ့ဆုံးမှ ဖတ်နိုင်သည်။ Queue တွင် storage နေရာလုံလုံလောက်လောက်ရှိသ zolang message များကို အချိန်မရွေး သိမ်းဆည်းထားနိုင်သည်။ ဥပမာအားဖြင့် GPS data ကို process လုပ်ရန် monthly job တစ်ခု run လုပ်လိုပါက၊ တစ်လတစ်လ message များကို queue တွင် သိမ်းဆည်းပြီး၊ လကုန်တွင် message များအားလုံးကို process လုပ်နိုင်သည်။

✅ သုတေသနလုပ်ပါ: [Azure Queue Storage](https://docs.microsoft.com/azure/storage/queues/storage-queues-introduction?WT.mc_id=academic-17441-jabenn) ကို ဖတ်ရှုပါ။

### File storage

File storage သည် cloud တွင် file များကို သိမ်းဆည်းရန် ဖြစ်ပြီး၊ app များနှင့် device များသည် industry standard protocols အသုံးပြု၍ ချိတ်ဆက်နိုင်သည်။ File storage တွင် file များကို ရေးသားပြီး၊ PC သို့မဟုတ် Mac တွင် drive အဖြစ် mount လုပ်နိုင်သည်။

✅ သုတေသနလုပ်ပါ: [Azure File Storage](https://docs.microsoft.com/azure/storage/files/storage-files-introduction?WT.mc_id=academic-17441-jabenn) ကို ဖတ်ရှုပါ။

## Serverless code ကို storage နှင့် ချိတ်ဆက်ပါ

သင့် function app သည် IoT Hub မှ message များကို blob storage တွင် သိမ်းဆည်းရန် ချိတ်ဆက်ရန် လိုအပ်သည်။ ဒါကိုလုပ်နိုင်သောနည်းလမ်း ၂ မျိုးရှိသည်-

* Function code အတွင်းတွင် blob storage ကို Python SDK အသုံးပြု၍ data ကို blob အဖြစ်ရေးသားပါ။
* Output function binding ကို အသုံးပြု၍ function ရဲ့ return value ကို blob storage နှင့် bind လုပ်ပြီး၊ blob ကို auto save လုပ်ပါ။

ဒီ lesson တွင် Python SDK ကို အသုံးပြု၍ blob storage နှင့် အလုပ်လုပ်ပုံကို လေ့လာမည်။

![IoT device မှ GPS telemetry ကို IoT Hub သို့ ပို့ပြီး၊ Azure Functions မှ event hub trigger ဖြင့် blob storage တွင် သိမ်းဆည်းခြင်း](../../../../../translated_images/my/save-telemetry-to-storage-from-functions.ed3b1820980097f1.webp)

Data ကို JSON blob အဖြစ် သိမ်းဆည်းမည်၊ format သည် အောက်ပါအတိုင်းဖြစ်သည်-

```json
{
    "device_id": <device_id>,
    "timestamp" : <time>,
    "gps" :
    {
        "lat" : <latitude>,
        "lon" : <longitude>
    }
}
```

### Task - serverless code ကို storage နှင့် ချိတ်ဆက်ပါ

1. Azure Storage account တစ်ခု ဖန်တီးပါ။ `gps<your name>` ဆိုပြီး အမည်ပေးပါ။

    > ⚠️ လိုအပ်ပါက [Project 2, Lesson 5 မှ storage account ဖန်တီးရန် လမ်းညွှန်ချက်များ](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---create-the-cloud-resources) ကို ရှာဖွေကြည့်နိုင်ပါသည်။

    အရင် project မှ storage account ရှိနေပါက၊ ထပ်မံအသုံးပြုနိုင်ပါသည်။

    > 💁 ဒီ storage account ကို function app ကို later deploy လုပ်ရန် အသုံးပြုနိုင်ပါမည်။

1. Storage account ရဲ့ connection string ကို ရယူရန် အောက်ပါ command ကို run လုပ်ပါ-

    ```sh
    az storage account show-connection-string --output table \
                                              --name <storage_name>
    ```

    `<storage_name>` ကို သင့် storage account ရဲ့ အမည်ဖြင့် အစားထိုးပါ။

1. `local.settings.json` ဖိုင်တွင် storage account connection string အတွက် entry အသစ်ထည့်ပါ။ အမည်ကို `STORAGE_CONNECTION_STRING` ဟု သတ်မှတ်ပါ။

1. Azure storage Pip packages ကို install လုပ်ရန် `requirements.txt` ဖိုင်တွင် အောက်ပါကို ထည့်ပါ-

    ```sh
    azure-storage-blob
    ```

    Virtual environment တွင် packages များကို install လုပ်ပါ။

    > Error ရှိပါက၊ virtual environment တွင် Pip version ကို အောက်ပါ command ဖြင့် upgrade လုပ်ပြီး ထပ်မံကြိုးစားပါ-
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. `iot-hub-trigger` ရဲ့ `__init__.py` ဖိုင်တွင် အောက်ပါ import statements များကို ထည့်ပါ-

    ```python
    import json
    import os
    import uuid
    from azure.storage.blob import BlobServiceClient, PublicAccess
    ```

    `json` module သည် JSON ကို ဖတ်ရန်နှင့် ရေးရန် အသုံးပြုမည်၊ `os` module သည် connection string ကို ဖတ်ရန် အသုံးပြုမည်၊ `uuid` module သည် GPS reading အတွက် unique ID တစ်ခု generate လုပ်ရန် အသုံးပြုမည်။

    `azure.storage.blob` package သည် blob storage နှင့် အလုပ်လုပ်ရန် Python SDK ကို ပါဝင်သည်။

1. `main` method မတိုင်မီ အောက်ပါ helper function ကို ထည့်ပါ-

    ```python
    def get_or_create_container(name):
        connection_str = os.environ['STORAGE_CONNECTION_STRING']
        blob_service_client = BlobServiceClient.from_connection_string(connection_str)
    
        for container in blob_service_client.list_containers():
            if container.name == name:
                return blob_service_client.get_container_client(container.name)
        
        return blob_service_client.create_container(name, public_access=PublicAccess.Container)
    ```

    Python blob SDK တွင် container မရှိပါက ဖန်တီးရန် helper method မပါဝင်ပါ။ ဒီ code သည် `local.settings.json` ဖိုင် (cloud တွင် deploy လုပ်ပြီးနောက် Application Settings) မှ connection string ကို load လုပ်ပြီး၊ blob storage account နှင့် အလုပ်လုပ်ရန် `BlobServiceClient` class ကို ဖန်တီးသည်။ Container များကို loop လုပ်ပြီး provided name နှင့် ကိုက်ညီသော container ရှိပါက `ContainerClient` class ကို return ပြန်သည်။ မရှိပါက container ကို ဖန်တီးပြီး၊ client ကို return ပြန်သည်။

    Container အသစ်ကို ဖန်တီးသောအခါ public access ကို ခွင့်ပြုသည်။ ဒီအရာကို next lesson တွင် GPS data ကို map တွင် visualization ပြုလုပ်ရန် အသုံးပြုမည်။

1. Soil moisture code နှင့် မတူပုံစံဖြင့် event တစ်ခုစီကို သိမ်းဆည်းရန် `for event in events:` loop အတွင်း `logging` statement အောက်တွင် အောက်ပါ code ကို ထည့်ပါ-

    ```python
    device_id = event.iothub_metadata['connection-device-id']
    blob_name = f'{device_id}/{str(uuid.uuid1())}.json'
    ```

    ဒီ code သည် event metadata မှ device ID ကို ရယူပြီး၊ blob name ကို ဖန်တီးသည်။ Blobs များကို folder တွင် သိမ်းဆည်းနိုင်ပြီး၊ device ID ကို folder name အဖြစ် အသုံးပြုမည်။ Blob name သည် folder နှင့် document name ကို forward slashes ဖြင့် ခွဲထားသည်။ Document name သည် Python `uuid` module ကို အသုံးပြု၍ ဖန်တီးထားသော unique ID ဖြစ်ပြီး၊ file type သည် `json` ဖြစ်သည်။

    ဥပမာအားဖြင့် `gps-sensor` device ID အတွက် blob name သည် `gps-sensor/a9487ac2-b9cf-11eb-b5cd-1e00621e3648.json` ဖြစ်နိုင်သည်။

1. အောက်ပါ code ကို ထည့်ပါ-

    ```python
    container_client = get_or_create_container('gps-data')
    blob = container_client.get_blob_client(blob_name)
    ```

    ဒီ code သည် `get_or_create_container` helper class ကို အသုံးပြု၍ container client ကို ရယူပြီး၊ blob name ကို အသုံးပြု၍ blob client object ကို ရယူသည်။ Blob client များသည် ရှိပြီးသား blob များကို ရည်ညွှန်းနိုင်သလို၊ အသစ်ဖန်တီးသော blob ကိုလည်း ရည်ညွှန်းနိုင်သည်။

1. အောက်ပါ code ကို ထည့်ပါ-

    ```python
    event_body = json.loads(event.get_body().decode('utf-8'))
    blob_body = {
        'device_id' : device_id,
        'timestamp' : event.iothub_metadata['enqueuedtime'],
        'gps': event_body['gps']
    }
    ```

    ဒီ code သည် blob storage တွင် ရေးသားမည့် blob body ကို ဖန်တီးသည်။ JSON document ဖြစ်ပြီး၊ device ID, IoT Hub သို့ telemetry ပေးပို့သည့်အချိန်နှင့် telemetry မှ GPS coordinates များပါဝင်သည်။

    > 💁 Message ပေးပို့သည့်အချိန်ကို ရယူရန် message ရဲ့ enqueued time ကို အသုံးပြုရန် အရေးကြီးသည်။ Functions App မ run လုပ်နေပါက message များသည် hub တွင် အချိန်ကြာကြာ ရှိနေနိုင်သည်။

1. အောက်ပါ code ကို ထည့်ပါ-

    ```python
    logging.info(f'Writing blob to {blob_name} - {blob_body}')
    blob.upload_blob(json.dumps(blob_body).encode('utf-8'))
    ```

    ဒီ code သည် blob ရေးသားမည့်အကြောင်းနှင့် details များကို log လုပ်ပြီး၊ blob body ကို blob content အဖြစ် upload လုပ်သည်။

1. Functions app ကို run လုပ်ပါ။ GPS events အတွက် blob များရေးသားနေကြောင်း output တွင် တွေ့ရမည်-

    ```output
    [2021-05-21T01:31:14.325Z] Python EventHub trigger processed an event: {"gps": {"lat": 47.73092, "lon": -122.26206}}
    ...
    [2021-05-21T01:31:14.351Z] Writing blob to gps-sensor/4b6089fe-ba8d-11eb-bc7b-1e00621e3648.json - {'device_id': 'gps-sensor', 'timestamp': '2021-05-21T00:57:53.878Z', 'gps': {'lat': 47.73092, 'lon': -122.26206}}
    ```

    > 💁 IoT Hub event monitor ကို တစ်ချိန်တည်းတွင် run မလုပ်ပါနှင့်။

> 💁 ဒီ code ကို [code/functions](../../../../../3-transport/lessons/2-store-location-data/code/functions) folder တွင် ရှာနိုင်ပါသည်။

### Task - uploaded blobs ကို verify လုပ်ပါ

1. ဖန်တီးထားသော blob များကို ကြည့်ရန် [Azure Storage Explorer](https://azure.microsoft.com/features/storage-explorer/?WT.mc_id=academic-17441-jabenn) ကို အသုံးပြုနိုင်သည်။ ဒါမှမဟုတ် CLI မှ ကြည့်နိုင်သည်။

    1. CLI ကို အသုံးပြုရန် account key လိုအပ်သည်။ အောက်ပါ command ကို run လုပ်ပြီး key ကို ရယူပါ-

        ```sh
        az storage account keys list --output table \
                                     --account-name <storage_name>
        ```

        `<storage_name>` ကို storage account ရဲ့ အမည်ဖြင့် အစားထိုးပါ။

        `key1` ရဲ့ value ကို copy လုပ်ပါ။

    1. Container တွင်ရှိသော blob များကို list လုပ်ရန် အောက်ပါ command ကို run လုပ်ပါ-

        ```sh
        az storage blob list --container-name gps-data \
                             --output table \
                             --account-name <storage_name> \
                             --account-key <key1>
        ```

        `<storage_name>` ကို storage account ရဲ့ အမည်ဖြင့်၊ `<key1>` ကို `key1` ရဲ့ value ဖြင့် အစားထိုးပါ။

        Container တွင်ရှိသော blob များအားလုံးကို list လုပ်မည်-

        ```output
        Name                                                  Blob Type    Blob Tier    Length    Content Type              Last Modified              Snapshot
        ----------------------------------------------------  -----------  -----------  --------  ------------------------  -------------------------  ----------
        gps-sensor/1810d55e-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:27+00:00
        gps-sensor/18293e46-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:28+00:00
        gps-sensor/1844549c-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:28+00:00
        gps-sensor/1894d714-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:28+00:00
        ```

    1. Blob တစ်ခုကို download လုပ်ရန် အောက်ပါ command ကို run လုပ်ပါ-

        ```sh
        az storage blob download --container-name gps-data \
                                 --account-name <storage_name> \
                                 --account-key <key1> \
                                 --name <blob_name> \
                                 --file <file_name>
        ```

        `<storage_name>` ကို storage account ရဲ့ အမည်ဖြင့်၊ `<key1>` ကို `key1` ရဲ့ value ဖြင့် အစားထိုးပါ။

        `<blob_name>` ကို `Name` column မှ full name ဖြင့်၊ folder name ပါဝင်အောင် အစားထိုးပါ။ `<file_name>` ကို local file name အဖြစ် အစားထိုးပါ။

    Download လုပ်ပြီးနောက် JSON file ကို VS Code တွင် ဖွင့်ပါ။ GPS location details ပါဝင်သော blob ကို တွေ့ရမည်-

    ```json
    {"device_id": "gps-sensor", "timestamp": "2021-05-21T00:57:53.878Z", "gps": {"lat": 47.73092, "lon": -122.26206}}
    ```

### Task - Functions App ကို cloud တွင် deploy လုပ်ပါ

Function app သည် အလုပ်လုပ်နေပြီးဖြစ်သောကြောင့် cloud တွင် deploy လုပ်နိုင်ပါသည်။

1. Storage account ကို အသုံးပြု၍ Azure Functions app အသစ်တစ်ခု ဖန်တီးပါ။ `gps-sensor-` ဟု အမည်ပေးပြီး unique identifier တစ်ခု ထည့်ပါ။

    > ⚠️ လိုအပ်ပါက [Project 2, Lesson 5 မှ Functions app ဖန်တီးရန် လမ်းညွှန်ချက်များ](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---create-the-cloud-resources) ကို ရှာဖွေကြည့်နိုင်ပါသည်။

1. `IOT_HUB_CONNECTION_STRING` နှင့် `STORAGE_CONNECTION_STRING` values များကို Application Settings တွင် upload လုပ်ပါ။

    > ⚠️ လိုအပ်ပါက [Project 2, Lesson 5 မှ Application Settings upload လုပ်ရန် လမ်းညွှန်ချက်များ](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---upload-your-application-settings) ကို ရှာဖွေကြည့်နိုင်ပါသည်။

1. Local Functions app ကို cloud တွင် deploy လုပ်ပါ။
> ⚠️ သင့် Functions app ကို project 2, lesson 5 မှ deployment လုပ်ရန်အတွက် [အညွှန်းများ](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---deploy-your-functions-app-to-the-cloud) ကိုလိုအပ်ပါက ရှာဖွေကြည့်နိုင်ပါသည်။
---

## 🚀 စိန်ခေါ်မှု

GPS ဒေတာသည် အတိအကျမဖြစ်နိုင်သေးပါ၊ အထူးသဖြင့် တန်းနယ်များနှင့် အဆောက်အအုံမြင့်များရှိနေသောနေရာများတွင် တည်နေရာများသည် မီတာအနည်းငယ် (တစ်ခါတစ်ရံမှာ ပိုများနိုင်သည်) မှားနေနိုင်ပါသည်။

အာကာသလမ်းညွှန်စနစ်သည် ဤပြဿနာကို ဘယ်လိုဖြေရှင်းနိုင်မလဲ? သင့် sat-nav တွင် သင့်တည်နေရာကို ပိုမိုမှန်ကန်စွာခန့်မှန်းနိုင်ရန် ဘယ်လိုဒေတာများရှိနေလဲ?

## မိန့်ခွန်းပြီးနောက် မေးခွန်း

[မိန့်ခွန်းပြီးနောက် မေးခွန်း](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/24)

## ပြန်လည်သုံးသပ်ခြင်းနှင့် ကိုယ်တိုင်လေ့လာခြင်း

* Wikipedia ရှိ [Data model page](https://wikipedia.org/wiki/Data_model) တွင် structured data အကြောင်းကို ဖတ်ရှုပါ။
* Wikipedia ရှိ [Semi-structured data page](https://wikipedia.org/wiki/Semi-structured_data) တွင် semi-structured data အကြောင်းကို ဖတ်ရှုပါ။
* Wikipedia ရှိ [Unstructured data page](https://wikipedia.org/wiki/Unstructured_data) တွင် unstructured data အကြောင်းကို ဖတ်ရှုပါ။
* Azure Storage နှင့် အမျိုးမျိုးသော storage အမျိုးအစားများအကြောင်းကို [Azure Storage documentation](https://docs.microsoft.com/azure/storage/?WT.mc_id=academic-17441-jabenn) တွင် ပိုမိုလေ့လာပါ။

## လုပ်ငန်း

[Function bindings ကို စုံစမ်းလေ့လာပါ](assignment.md)

---

**အကြောင်းကြားချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှုအတွက် ကြိုးစားနေသော်လည်း၊ အလိုအလျောက် ဘာသာပြန်မှုများတွင် အမှားများ သို့မဟုတ် မမှန်ကန်မှုများ ပါဝင်နိုင်သည်ကို သတိပြုပါ။ မူရင်းဘာသာစကားဖြင့် ရေးသားထားသော စာရွက်စာတမ်းကို အာဏာတရားရှိသော ရင်းမြစ်အဖြစ် သတ်မှတ်သင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူ့ဘာသာပြန်ပညာရှင်များမှ ပရော်ဖက်ရှင်နယ် ဘာသာပြန်မှုကို အကြံပြုပါသည်။ ဤဘာသာပြန်မှုကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော အလွဲအလွတ်များ သို့မဟုတ် အနားလွဲမှုများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။