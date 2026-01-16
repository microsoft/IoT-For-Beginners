<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "078ae664c7b686bf069545e9a5fc95b2",
  "translation_date": "2025-08-28T16:52:47+00:00",
  "source_file": "3-transport/lessons/4-geofences/README.md",
  "language_code": "my"
}
-->
# Geofences

![ဒီသင်ခန်းစာအတွက် Sketchnote အကျဉ်းချုပ်](../../../../../translated_images/my/lesson-14.63980c5150ae3c153e770fb71d044c1845dce79248d86bed9fc525adf3ede73c.jpg)

> Sketchnote by [Nitya Narasimhan](https://github.com/nitya)။ ပုံကိုနှိပ်ပြီး ပိုမိုကြီးမားသောဗားရှင်းကိုကြည့်ပါ။

ဤဗီဒီယိုတွင် geofences နှင့် Azure Maps တွင်၎င်းတို့ကိုအသုံးပြုနည်းအကြောင်းကို အကျဉ်းချုပ်ဖော်ပြထားပြီး၊ ဤသင်ခန်းစာတွင်လည်းဆွေးနွေးမည့်အကြောင်းအရာများပါဝင်သည်။

[![Microsoft Developer IoT show မှ Azure Maps ဖြင့် Geofencing](https://img.youtube.com/vi/nsrgYhaYNVY/0.jpg)](https://www.youtube.com/watch?v=nsrgYhaYNVY)

> 🎥 အထက်ပါပုံကိုနှိပ်ပြီး ဗီဒီယိုကိုကြည့်ပါ။

## သင်ခန်းစာမတိုင်မီမေးခွန်းများ

[သင်ခန်းစာမတိုင်မီမေးခွန်းများ](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/27)

## နိဒါန်း

နောက်ဆုံးသုံးသင်ခန်းစာများတွင်၊ သင်သည် IoT ကိုအသုံးပြု၍ သင့်လယ်ယာမှ ထွက်ကုန်များကို သယ်ဆောင်သည့် ထရပ်ကားများ၏ တည်နေရာကို ရှာဖွေခဲ့ပါသည်။ သင်သည် GPS ဒေတာကို ဖမ်းယူပြီး၊ cloud သို့ပို့၍ သိမ်းဆည်းကာ မြေပုံပေါ်တွင် မြင်နိုင်အောင် ပြသခဲ့ပါသည်။ သင့်ထုတ်လုပ်မှုဆိုင်ရာ supply chain ၏ ထိရောက်မှုကို တိုးမြှင့်ရန် နောက်ထပ်အဆင့်မှာ ထရပ်ကားသည် ပြုပြင်ထိန်းသိမ်းရေးစင်တာသို့ ရောက်ရှိမည့်အချိန်တွင် သတိပေးချက်ကို ရရှိရန်ဖြစ်သည်။ ထိုသို့ဖြင့် ထရပ်ကားရောက်ရှိပြီးချိန်တွင် လိုအပ်သော လုပ်သားများသည် forklift နှင့် အခြားပစ္စည်းများဖြင့် အသင့်ရှိနိုင်မည်ဖြစ်သည်။ ထိုနည်းဖြင့် အချိန်မီတင်ဆောင်ပြီး၊ ထရပ်ကားနှင့် ယာဉ်မောင်းအတွက် စောင့်ဆိုင်းချိန်အတွက် ပိုမိုကုန်ကျမှုမရှိစေရန် ကူညီနိုင်ပါသည်။

ဤသင်ခန်းစာတွင် သင်သည် geofences အကြောင်းကို သင်ယူမည်ဖြစ်ပြီး၊ ၎င်းသည် သတ်မှတ်ထားသော ပထဝီဧရိယာများဖြစ်ပြီး၊ ဥပမာအားဖြင့် ပြုပြင်ထိန်းသိမ်းရေးစင်တာ၏ ၂ ကီလိုမီတာအတွင်းရှိဧရိယာတစ်ခုနှင့်တူသည်။ သင်သည် GPS ကိုဧရိယာအတွင်းသို့ရောက်ရှိခြင်း သို့မဟုတ် ထွက်ခွာခြင်းကို စစ်ဆေးနိုင်မည်ဖြစ်သည်။

ဤသင်ခန်းစာတွင် ကျွန်ုပ်တို့ဆွေးနွေးမည့်အကြောင်းအရာများမှာ -

* [Geofences ဆိုတာဘာလဲ](../../../../../3-transport/lessons/4-geofences)
* [Geofence တစ်ခုကို သတ်မှတ်ခြင်း](../../../../../3-transport/lessons/4-geofences)
* [Geofence နှင့် တိုက်ဆိုင်စစ်ဆေးခြင်း](../../../../../3-transport/lessons/4-geofences)
* [Serverless Code မှ Geofences အသုံးပြုခြင်း](../../../../../3-transport/lessons/4-geofences)

> 🗑 ဤသည်မှာ ဤပရောဂျက်၏ နောက်ဆုံးသင်ခန်းစာဖြစ်သည်။ သင်ခန်းစာနှင့် လုပ်ငန်းတာဝန်ကို ပြီးဆုံးပြီးနောက် cloud services များကို ရှင်းလင်းရန် မမေ့ပါနှင့်။ သင်သည် လုပ်ငန်းတာဝန်ကို ပြီးမြောက်ရန် ၎င်းများလိုအပ်မည်ဖြစ်သောကြောင့် အရင်ဆုံး ၎င်းကို ပြီးမြောက်စေပါ။
>
> လိုအပ်ပါက [သင့်ပရောဂျက်ကို ရှင်းလင်းရန် လမ်းညွှန်ချက်](../../../clean-up.md) ကို ကိုးကားပါ။

## Geofences ဆိုတာဘာလဲ

Geofence ဆိုသည်မှာ အမှန်တကယ်ရှိသော ပထဝီဧရိယာတစ်ခုအတွက် အွန်လိုင်းနယ်နိမိတ်တစ်ခုဖြစ်သည်။ Geofences များသည် အချက်တစ်ခုနှင့် အချင်းဝက်ကို သတ်မှတ်ထားသော စက်ဝိုင်းများ (ဥပမာ - အဆောက်အဦးတစ်ခု၏ ၁၀၀ မီတာအကျယ်ရှိ စက်ဝိုင်း) သို့မဟုတ် ကျောင်းဇုန်၊ မြို့နယ်နယ်နိမိတ် သို့မဟုတ် တက္ကသိုလ် သို့မဟုတ် ရုံးစခန်းများကဲ့သို့သော ဧရိယာကို ဖုံးလွှမ်းထားသော ပေါ်လီဂွန်များဖြစ်နိုင်သည်။

![Microsoft ကုမ္ပဏီဆိုင်၏ စက်ဝိုင်း geofence နှင့် Microsoft အနောက် campus ၏ ပေါ်လီဂွန် geofence ကို ပြသထားသော ဥပမာများ](../../../../../translated_images/my/geofence-examples.172fbc534665769f6e1a1ddcf75e3b25183cd10354c80cc603ba44b635390e1a.png)

> 💁 သင်သည် geofences များကို အသုံးပြုခဲ့ပြီးသားဖြစ်နိုင်သည်၊ သို့သော် မသိခဲ့လောက်ပါ။ သင်သည် iOS reminders app သို့မဟုတ် Google Keep တွင် တည်နေရာအခြေပြု သတိပေးချက်တစ်ခုကို သတ်မှတ်ထားခဲ့ပါက၊ သင်သည် geofence တစ်ခုကို အသုံးပြုခဲ့သည်။ ဤ app များသည် သတ်မှတ်ထားသော တည်နေရာအပေါ်မူတည်၍ geofence တစ်ခုကို သတ်မှတ်ကာ သင့်ဖုန်းသည် geofence အတွင်းသို့ရောက်ရှိသောအခါ သတိပေးချက်ပေးမည်။

ယာဉ်တစ်စီးသည် geofence အတွင်း သို့မဟုတ် အပြင်တွင် ရှိနေသည်ကို သိလိုရန် အကြောင်းအမျိုးမျိုးရှိနိုင်သည် -

* **တင်ဆောင်ရန် ပြင်ဆင်မှု** - ယာဉ်တစ်စီးသည် နေရာသို့ရောက်ရှိကြောင်း သတိပေးချက်ရရှိခြင်းဖြင့် လုပ်သားများသည် ယာဉ်ကို အချိန်မီတင်ဆောင်နိုင်ရန် ပြင်ဆင်နိုင်သည်။ ၎င်းသည် ယာဉ်မောင်းတစ်ဦးအနေဖြင့် တစ်နေ့အတွင်း ပိုမိုပို့ဆောင်မှုများ ပြုလုပ်နိုင်စေပြီး စောင့်ဆိုင်းချိန်ကို လျှော့ချနိုင်သည်။
* **အခွန်လိုက်နာမှု** - နိုင်ငံအချို့ (ဥပမာ - နယူးဇီလန်) တွင်၊ diesel ယာဉ်များအတွက် လမ်းအခွန်ကို ယာဉ်၏အလေးချိန်နှင့်အညီ၊ အများပြည်သူလမ်းများပေါ်တွင်သာမောင်းနှင်မှုအပေါ်မူတည်၍ ကောက်ခံသည်။ Geofences များကို အသုံးပြုခြင်းဖြင့် အများပြည်သူလမ်းများပေါ်တွင် မောင်းနှင်သည့် ကီလိုမီတာများကို စစ်ဆေးနိုင်သည်။
* **ခိုးယူမှုကြည့်ရှုမှု** - ယာဉ်တစ်စီးသည် သတ်မှတ်ဧရိယာ (ဥပမာ - လယ်ယာ) အတွင်းသာ ရှိသင့်ပြီး၊ geofence အပြင်သို့ ထွက်သွားပါက၊ ၎င်းကို ခိုးယူထားနိုင်သည်။
* **တည်နေရာလိုက်နာမှု** - လုပ်ငန်းခွင်၊ လယ်ယာ သို့မဟုတ် စက်ရုံ၏ အချို့သောဧရိယာများသည် ယာဉ်အချို့အတွက် ဝင်ရောက်ခွင့်မရှိနိုင်ပါ။ ဥပမာအားဖြင့် ဓာတုအပင်အာဟာရနှင့် ပိုးသတ်ဆေးများ သယ်ဆောင်သည့် ယာဉ်များကို သဘာဝစိုက်ပျိုးမှုများရှိသည့် လယ်ယာများမှ ဝေးကွာစေရန်လိုအပ်သည်။ Geofence တစ်ခုကို ဝင်ရောက်ပါက ယာဉ်သည် လိုက်နာမှုအပြင်တွင် ရှိနေပြီး ယာဉ်မောင်းအား သတိပေးနိုင်သည်။

✅ Geofences များကို အသုံးပြုနိုင်သည့် အခြားနည်းလမ်းများကို သင်စဉ်းစားနိုင်ပါသလား?

Azure Maps သည် သင်သည် ယခင်သင်ခန်းစာတွင် GPS ဒေတာကို မြင်နိုင်အောင် ပြသရန် အသုံးပြုခဲ့သော ဝန်ဆောင်မှုဖြစ်ပြီး၊ geofences များကို သတ်မှတ်ကာ၊ တစ်ချက်သည် geofence အတွင်း သို့မဟုတ် အပြင်တွင် ရှိနေသည်ကို စစ်ဆေးနိုင်သည်။

## Geofence တစ်ခုကို သတ်မှတ်ခြင်း

Geofences များကို GeoJSON ကို အသုံးပြု၍ သတ်မှတ်သည်။ ၎င်းသည် ယခင်သင်ခန်းစာတွင် မြေပုံပေါ်တွင် ထည့်သွင်းထားသော အချက်များနှင့် တူသည်။ သို့သော် ဤအခါတွင် `Point` တန်ဖိုးများဖြင့် `FeatureCollection` မဟုတ်ဘဲ၊ `Polygon` ပါဝင်သော `FeatureCollection` ဖြစ်သည်။

```json
{
   "type": "FeatureCollection",
   "features": [
     {
       "type": "Feature",
       "geometry": {
         "type": "Polygon",
         "coordinates": [
           [
             [
               -122.13393688201903,
               47.63829579223815
             ],
             [
               -122.13389128446579,
               47.63782047131512
             ],
             [
               -122.13240802288054,
               47.63783312249837
             ],
             [
               -122.13238388299942,
               47.63829037035086
             ],
             [
               -122.13393688201903,
               47.63829579223815
             ]
           ]
         ]
       },
       "properties": {
         "geometryId": "1"
       }
     }
   ]
}
```

Polygon ၏ အချက်တစ်ခုစီကို longitude နှင့် latitude တန်ဖိုးများဖြင့် အစီအစဉ်တစ်ခုအဖြစ် သတ်မှတ်ထားပြီး၊ ၎င်းအချက်များကို `coordinates` အဖြစ် သတ်မှတ်ထားသည်။ ယခင်သင်ခန်းစာတွင် `Point` ၏ `coordinates` သည် latitude နှင့် longitude တန်ဖိုး ၂ ခုပါဝင်သည့် အစီအစဉ်တစ်ခုဖြစ်သည်။ Polygon ၏ `coordinates` သည် longitude နှင့် latitude တန်ဖိုး ၂ ခုပါဝင်သည့် အစီအစဉ်များပါဝင်သည့် အစီအစဉ်တစ်ခုဖြစ်သည်။

> 💁 GeoJSON သည် `latitude, longitude` မဟုတ်ဘဲ `longitude, latitude` ကို အသုံးပြုသည်ကို သတိပြုပါ။

Polygon ၏ coordinates အစီအစဉ်သည် polygon ၏ အချက်အရေအတွက်ထက် ၁ ခုပိုပါသည်။ ၎င်းသည် polygon ကို ပိတ်ရန် အစပွင့်နှင့် တူသော နောက်ဆုံးအချက်ကို ထည့်သွင်းထားခြင်းဖြစ်သည်။ ဥပမာအားဖြင့် စတုရန်းတစ်ခုအတွက် အချက် ၅ ခုရှိမည်။

![အချက်များပါရှိသော စတုရန်း](../../../../../translated_images/my/polygon-points.302193da381cb415.webp)

အထက်ပါပုံတွင် စတုရန်းတစ်ခုရှိသည်။ Polygon ၏ coordinates သည် 47,-122 တွင် အပေါ်ဘက်-ဘယ်ဘက်မှ စတင်ကာ 47,-121 သို့ ညာဘက်သို့ ရွှေ့ပြီး၊ 46,-121 သို့ အောက်ဘက်သို့ ရွှေ့ကာ၊ 46,-122 သို့ ဘယ်ဘက်သို့ ရွှေ့ပြီး၊ 47,-122 တွင် အစပွင့်သို့ ပြန်လာသည်။ ၎င်းသည် polygon ကို အချက် ၅ ခုဖြစ်စေသည် - အပေါ်ဘက်-ဘယ်ဘက်၊ အပေါ်ဘက်-ညာဘက်၊ အောက်ဘက်-ညာဘက်၊ အောက်ဘက်-ဘယ်ဘက်၊ ထို့နောက် အပေါ်ဘက်-ဘယ်ဘက်သို့ ပြန်လာသည်။

✅ သင့်အိမ် သို့မဟုတ် ကျောင်းပတ်လည်တွင် GeoJSON polygon တစ်ခုကို ဖန်တီးကြည့်ပါ။ [GeoJSON.io](https://geojson.io/) ကဲ့သို့သော ကိရိယာတစ်ခုကို အသုံးပြုပါ။

### လုပ်ငန်းတာဝန် - Geofence တစ်ခုကို သတ်မှတ်ပါ

Azure Maps တွင် geofence တစ်ခုကို အသုံးပြုရန်၊ ၎င်းကို အရင်ဆုံး သင့် Azure Maps အကောင့်သို့ upload လုပ်ရမည်။ Upload လုပ်ပြီးနောက်၊ geofence ကို စစ်ဆေးရန် အသုံးပြုနိုင်သော တစ်ခုတည်းသော ID ကို ရရှိမည်။ Azure Maps သို့ geofences များကို upload လုပ်ရန်၊ maps web API ကို အသုံးပြုရမည်။ [curl](https://curl.se) ဟုခေါ်သော ကိရိယာတစ်ခုကို အသုံးပြု၍ Azure Maps web API ကို ခေါ်နိုင်သည်။

> 🎓 Curl သည် web endpoint များကို တိုက်ရိုက်ခေါ်ဆိုရန် command line ကိရိယာတစ်ခုဖြစ်သည်။

1. Linux, macOS သို့မဟုတ် Windows 10 ၏ မကြာသေးမီဗားရှင်းကို အသုံးပြုနေပါက၊ သင်သည် curl ကို ရှိပြီးသားဖြစ်နိုင်သည်။ Terminal သို့မဟုတ် command line မှာ အောက်ပါ command ကို run လုပ်ပြီး စစ်ဆေးပါ -

    ```sh
    curl --version
    ```

    Curl ၏ version အချက်အလက်ကို မမြင်ရပါက၊ [curl downloads page](https://curl.se/download.html) မှာ install လုပ်ရန် လိုအပ်ပါမည်။

    > 💁 Postman ကို ကျွမ်းကျင်စွာအသုံးပြုနိုင်ပါက၊ ၎င်းကို အသုံးပြုနိုင်ပါသည်။

1. Polygon ပါဝင်သော GeoJSON ဖိုင်တစ်ခုကို ဖန်တီးပါ။ သင်၏ GPS sensor ကို အသုံးပြု၍ ဤ polygon ကို စစ်ဆေးမည်ဖြစ်သောကြောင့်၊ သင်၏လက်ရှိတည်နေရာပတ်လည်တွင် polygon တစ်ခုကို ဖန်တီးပါ။ အထက်ပါ GeoJSON ဥပမာကို လက်ဖြင့် ပြင်ဆင်ခြင်းဖြင့် သို့မဟုတ် [GeoJSON.io](https://geojson.io/) ကဲ့သို့သော ကိရိယာတစ်ခုကို အသုံးပြု၍ ဖန်တီးနိုင်သည်။

    GeoJSON သည် `FeatureCollection` တစ်ခုပါဝင်ရမည်၊ ၎င်းတွင် `geometry` အဖြစ် `Polygon` ပါဝင်သော `Feature` တစ်ခုပါဝင်ရမည်။

    သင်သည် **လည်းမဖြစ်မနေ** `geometry` element နှင့်တန်းတူ `properties` element တစ်ခုကို ထည့်ရမည်။ ၎င်းတွင် `geometryId` ပါဝင်ရမည် -

    ```json
    "properties": {
        "geometryId": "1"
    }
    ```

    [GeoJSON.io](https://geojson.io/) ကို အသုံးပြုပါက၊ JSON ဖိုင်ကို download လုပ်ပြီးနောက် သို့မဟုတ် app ၏ JSON editor တွင် `properties` element အတွင်း၎င်းကို လက်ဖြင့်ထည့်ရမည်။

    ဤ `geometryId` သည် ဤဖိုင်အတွင်း တစ်ခုတည်းသော ID ဖြစ်ရမည်။ Geofences များကို `FeatureCollection` ၏ `Features` အဖြစ် GeoJSON ဖိုင်တစ်ခုတွင် upload လုပ်နိုင်ပြီး၊ တစ်ခုစီတွင် မတူညီသော `geometryId` ရှိရမည်။ Polygon များသည် မတူညီသောဖိုင်မှ upload လုပ်သောအခါ `geometryId` တူနိုင်သည်။

1. ဤဖိုင်ကို `geofence.json` ဟု save လုပ်ပြီး၊ terminal သို့မဟုတ် console တွင် save လုပ်ထားသောနေရာသို့ သွားပါ။

1. Geofence ကို ဖန်တီးရန် အောက်ပါ curl command ကို run လုပ်ပါ -

    ```sh
    curl --request POST 'https://atlas.microsoft.com/mapData/upload?api-version=1.0&dataFormat=geojson&subscription-key=<subscription_key>' \
         --header 'Content-Type: application/json' \
         --include \
         --data @geofence.json
    ```

    URL တွင် `<subscription_key>` ကို သင့် Azure Maps အကောင့်၏ API key ဖြင့် အစားထိုးပါ။

    URL သည် `https://atlas.microsoft.com/mapData/upload` API ကို အသုံးပြု၍ map data ကို upload လုပ်ရန် အသုံးပြုသည်။ API ကို အချိန်ကြာလာသည်နှင့်အမျှ ပြောင်းလဲနိုင်သော်လည်း နောက်ဆက်တွဲလိုက်နာမှုကို ထိန်းသိမ်းရန် `api-version` parameter ကို ထည့်သွင်းထားသည်။ Upload လုပ်သော data format ကို `geojson` အဖြစ် သတ်မှတ်ထားသည်။

    ဤသည်သည် POST request ကို upload API သို့ run လုပ်ပြီး၊ `location` ဟုခေါ်သော header တစ်ခုပါဝင်သော response headers များကို ပြန်ပေးမည်။

    ```output
    content-type: application/json
    location: https://us.atlas.microsoft.com/mapData/operations/1560ced6-3a80-46f2-84b2-5b1531820eab?api-version=1.0
    x-ms-azuremaps-region: West US 2
    x-content-type-options: nosniff
    strict-transport-security: max-age=31536000; includeSubDomains
    x-cache: CONFIG_NOCACHE
    date: Sat, 22 May 2021 21:34:57 GMT
    content-length: 0
    ```

    > 🎓 Web endpoint တစ်ခုကို ခေါ်ဆိုသောအခါ၊ `?` ဖြင့် key-value pairs အဖြစ် parameter များကို ပေးပို့နိုင်သည်။ Key-value pairs များကို `&` ဖြင့် ခွဲထားသည်။

1. Azure Maps သည် ဤကို ချက်ချင်း process မလုပ်ပါ၊ ထို့ကြောင့် upload request ပြီးဆုံးထားသည်ကို `location` header တွင်ပေးထားသော URL ကို အသုံးပြု၍ စစ်ဆေးရမည်။ `location` URL
အထက်ပါပုံတွင် Microsoft ကုမ္ပဏီ၏တစ်စိတ်တစ်ပိုင်းကို geofence ဖြင့်ဖုံးအုပ်ထားသည်။ အနီရောင်လိုင်းသည် 520 လမ်းတလျှောက်တွင်မောင်းနှင်နေသောထရပ်ကားကိုပြသပြီး၊ GPS အချက်အလက်များကိုပြသရန်အဝိုင်းများပါရှိသည်။ အများစုမှာ 520 လမ်းတလျှောက်မှန်ကန်ပြီး၊ geofence အတွင်းမှမမှန်ကန်သောအချက်အလက်တစ်ခုရှိသည်။ ထိုအချက်အလက်သည်မှန်ကန်နိုင်မည်မဟုတ်ပါ - ထရပ်ကားသည် 520 မှ campus သို့ရုတ်တရက်လမ်းလွဲပြီး 520 သို့ပြန်သွားရန်လမ်းမရှိပါ။ geofence ကိုစစ်ဆေးသည့် code သည် geofence စမ်းသပ်မှုရလဒ်များကိုအသုံးပြုမီ ယခင်အချက်အလက်များကိုစဉ်းစားရန်လိုအပ်ပါသည်။

✅ GPS အချက်အလက်ကိုမှန်ကန်ဟုထင်နိုင်ရန်အတွက် စစ်ဆေးရန်လိုအပ်သောအချက်အလက်များကဘာများဖြစ်မည်နည်း?

### Task - geofence နှင့်အချက်အလက်များကိုစမ်းသပ်ပါ

1. Web API query အတွက် URL ကိုတည်ဆောက်ခြင်းဖြင့်စတင်ပါ။ format သည်အောက်ပါအတိုင်းဖြစ်သည်-

    ```output
    https://atlas.microsoft.com/spatial/geofence/json?api-version=1.0&deviceId=gps-sensor&subscription-key=<subscription-key>&udid=<UDID>&lat=<lat>&lon=<lon>
    ```

    `<subscription_key>` ကို Azure Maps အကောင့်၏ API key ဖြင့်အစားထိုးပါ။

    `<UDID>` ကို ယခင် task မှ geofence ၏ UDID ဖြင့်အစားထိုးပါ။

    `<lat>` နှင့် `<lon>` ကို စမ်းသပ်လိုသော latitude နှင့် longitude ဖြင့်အစားထိုးပါ။

    URL သည် `https://atlas.microsoft.com/spatial/geofence/json` API ကိုအသုံးပြု၍ GeoJSON ဖြင့်သတ်မှတ်ထားသော geofence ကို query လုပ်သည်။ API version `1.0` ကို target လုပ်သည်။ `deviceId` parameter သည်လိုအပ်ပြီး latitude နှင့် longitude ရရှိသော device အမည်ဖြစ်ရမည်။

    ပုံမှန် search buffer သည် 50m ဖြစ်ပြီး၊ `<distance>` ကို meter အနေနှင့် 0 မှ 500 အတွင်းသတ်မှတ်ခြင်းဖြင့် `searchBuffer=<distance>` parameter ကိုထည့်သွင်းခြင်းဖြင့်ပြောင်းလဲနိုင်သည်။

1. curl ကိုအသုံးပြု၍ GET request ကို URL သို့လုပ်ပါ-

    ```sh
    curl --request GET '<URL>'
    ```

    > 💁 Response code `BadRequest` ရရှိပါက၊ error သည်-
    >
    > ```output
    > Invalid GeoJSON: All feature properties should contain a geometryId, which is used for identifying the geofence.
    > ```
    >
    > သင့် GeoJSON တွင် `properties` section နှင့် `geometryId` မပါရှိပါ။ GeoJSON ကိုပြင်ဆင်ပြီး၊ အထက်ပါအဆင့်များကိုထပ်မံလုပ်ဆောင်၍ UDID အသစ်ရယူရန်လိုအပ်ပါသည်။

1. Response တွင် GeoJSON ကိုအသုံးပြု၍ geofence ကိုဖန်တီးသည့် polygon တစ်ခုစီအတွက် `geometries` စာရင်းပါရှိမည်။ Geometry တစ်ခုစီတွင် `distance`, `nearestLat` နှင့် `nearestLon` ဆိုသည့် 3 ခုသောအရေးပါသော field များပါရှိသည်။

    ```output
    {
        "geometries": [
            {
                "deviceId": "gps-sensor",
                "udId": "7c3776eb-da87-4c52-ae83-caadf980323a",
                "geometryId": "1",
                "distance": 999.0,
                "nearestLat": 47.645875,
                "nearestLon": -122.142713
            }
        ],
        "expiredGeofenceGeometryId": [],
        "invalidPeriodGeofenceGeometryId": []
    }
    ```

    * `nearestLat` နှင့် `nearestLon` သည် စမ်းသပ်နေသောနေရာနှင့်အနီးဆုံး geofence အနားရှိ latitude နှင့် longitude ဖြစ်သည်။

    * `distance` သည် စမ်းသပ်နေသောနေရာနှင့် geofence အနားရှိအနီးဆုံးနေရာအကြားအကွာအဝေးဖြစ်သည်။ အနုတ်ဂဏန်းများသည် geofence အတွင်းရှိကြောင်း၊ အပေါင်းဂဏန်းများသည် geofence အပြင်ရှိကြောင်းကိုဆိုလိုသည်။ ဤတန်ဖိုးသည် 50 (ပုံမှန် search buffer) ထက်နည်းမည်၊ သို့မဟုတ် 999 ဖြစ်မည်။

1. geofence အတွင်းနှင့်အပြင်ရှိနေရာများဖြင့်အကြိမ်ကြိမ်ထပ်မံစမ်းသပ်ပါ။

## Serverless code မှ geofence များကိုအသုံးပြုပါ

ယခုအခါ Functions app တွင် IoT Hub GPS အချက်အလက်များကို geofence နှင့်စမ်းသပ်ရန် trigger အသစ်တစ်ခုထည့်နိုင်ပါပြီ။

### Consumer groups

ယခင်သင်ခန်းစာများမှသတိရပါက၊ IoT Hub သည် hub သို့ရောက်ရှိပြီး processing မလုပ်ရသေးသောအချက်အလက်များကိုပြန်လည်ဖတ်ရှုနိုင်ပါသည်။ သို့သော် trigger များစွာချိတ်ဆက်ပါက ဘာဖြစ်မည်နည်း။ အဘယ်သို့ event များကို process ပြီးပြီဟုသိနိုင်မည်နည်း။

အဖြေမှာ မသိနိုင်ပါ! ထို့အတွက် event များကိုဖတ်ရှုရန် connection များစွာကိုသတ်မှတ်နိုင်ပြီး၊ event မဖတ်ရှုရသေးသော message များကို replay လုပ်နိုင်သည်။ ၎င်းတို့ကို *consumer groups* ဟုခေါ်သည်။ Endpoint သို့ချိတ်ဆက်သောအခါ၊ ချိတ်ဆက်လိုသော consumer group ကိုသတ်မှတ်နိုင်သည်။ Application ၏ component တစ်ခုစီသည်ကွဲပြားသော consumer group ကိုချိတ်ဆက်မည်။

![IoT Hub တစ်ခုတွင် 3 consumer groups သည် message တစ်ခုစီကို function apps 3 ခုသို့ဖြန့်ဝေသည်](../../../../../translated_images/my/consumer-groups.a3262e26fc27ba2092863678ad57af15c7223416e388a23f330c058cf4358630.png)

သီအိုရီအရ consumer group တစ်ခုစီတွင် application 5 ခုအထိချိတ်ဆက်နိုင်ပြီး၊ message ရောက်ရှိသောအခါ message များကိုလက်ခံရရှိမည်။ Restart လုပ်သောအခါ queued message များကိုမှန်ကန်စွာ process လုပ်ရန်၊ message များကို duplicate ဖြစ်ခြင်းမှရှောင်ရှားရန်၊ application တစ်ခုသာ consumer group တစ်ခုစီကို access လုပ်ရန်အကောင်းဆုံးနည်းလမ်းဖြစ်သည်။ ဥပမာအားဖြင့် Functions app ကို locally launch လုပ်ပြီး cloud တွင်လည်း run လုပ်ပါက၊ message များကို duplicate ဖြစ်စေပြီး storage account တွင် blob များကို duplicate ဖြစ်စေမည်။

IoT Hub trigger ၏ `function.json` ဖိုင်ကိုကြည့်ရှုပါက၊ event hub trigger binding section တွင် consumer group ကိုတွေ့ရမည်-

```json
"consumerGroup": "$Default"
```

IoT Hub တစ်ခုကိုဖန်တီးသောအခါ၊ `$Default` consumer group ကို default အနေဖြင့်ရရှိမည်။ အပို trigger တစ်ခုထည့်လိုပါက၊ consumer group အသစ်တစ်ခုကိုထည့်နိုင်သည်။

> 💁 ဤသင်ခန်းစာတွင် GPS အချက်အလက်များကိုသိုလှောင်ရန်အသုံးပြုသော function နှင့် geofence ကိုစမ်းသပ်ရန်အသုံးပြုသော function ကိုကွဲပြားစွာအသုံးပြုမည်။ ၎င်းသည် consumer groups ကိုအသုံးပြုပုံနှင့် code ကိုဖတ်ရှုရန်နှင့်နားလည်ရန်လွယ်ကူစေရန် code ကိုခွဲခြားထားပုံကိုပြသရန်ဖြစ်သည်။ Production application တွင်ဤအရာကို architect လုပ်ရန်နည်းလမ်းများစွာရှိသည် - function တစ်ခုတွင်နှစ်ခုစလုံးကိုထည့်ခြင်း၊ storage account တွင် trigger ကိုအသုံးပြု၍ geofence ကိုစစ်ဆေးရန် function ကို run လုပ်ခြင်း၊ သို့မဟုတ် function များစွာကိုအသုံးပြုခြင်း။ 'မှန်ကန်သောနည်းလမ်း' မရှိပါ၊ ၎င်းသည် application ၏အခြားအစိတ်အပိုင်းများနှင့်လိုအပ်ချက်များပေါ်မူတည်သည်။

### Task - consumer group အသစ်တစ်ခုဖန်တီးပါ

1. IoT Hub အတွက် `geofence` ဟုခေါ်သော consumer group အသစ်တစ်ခုဖန်တီးရန်အောက်ပါ command ကို run လုပ်ပါ-

    ```sh
    az iot hub consumer-group create --name geofence \
                                     --hub-name <hub_name>
    ```

    `<hub_name>` ကို IoT Hub အတွက်သင်အသုံးပြုသောအမည်ဖြင့်အစားထိုးပါ။

1. IoT Hub အတွက် consumer groups အားလုံးကိုကြည့်လိုပါက၊ အောက်ပါ command ကို run လုပ်ပါ-

    ```sh
    az iot hub consumer-group list --output table \
                                   --hub-name <hub_name>
    ```

    `<hub_name>` ကို IoT Hub အတွက်သင်အသုံးပြုသောအမည်ဖြင့်အစားထိုးပါ။ ၎င်းသည် consumer groups အားလုံးကိုစာရင်းပြုမည်။

    ```output
    Name      ResourceGroup
    --------  ---------------
    $Default  gps-sensor
    geofence  gps-sensor
    ```

> 💁 ယခင်သင်ခန်းစာတွင် IoT Hub event monitor ကို run လုပ်သောအခါ၊ ၎င်းသည် `$Default` consumer group ကိုချိတ်ဆက်ခဲ့သည်။ ထို့ကြောင့် event monitor နှင့် event trigger ကို run လုပ်၍မရပါ။ နှစ်ခုစလုံးကို run လုပ်လိုပါက၊ function apps အားလုံးအတွက်အခြား consumer groups များကိုအသုံးပြုနိုင်ပြီး၊ event monitor အတွက် `$Default` ကိုထားနိုင်သည်။

### Task - IoT Hub trigger အသစ်တစ်ခုဖန်တီးပါ

1. ယခင်သင်ခန်းစာတွင်ဖန်တီးထားသော `gps-trigger` function app တွင် IoT Hub event trigger အသစ်တစ်ခုထည့်ပါ။ ဤ function ကို `geofence-trigger` ဟုခေါ်ပါ။

    > ⚠️ [Project 2, Lesson 5 မှ IoT Hub event trigger ဖန်တီးရန်လမ်းညွှန်ချက်များကိုလိုအပ်ပါက](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#create-an-iot-hub-event-trigger) ကိုရည်ညွှန်းနိုင်သည်။

1. `function.json` ဖိုင်တွင် IoT Hub connection string ကို configure လုပ်ပါ။ `local.settings.json` သည် Function App တွင် trigger အားလုံးအတွက် shared ဖြစ်သည်။

1. `function.json` ဖိုင်တွင် `consumerGroup` ၏တန်ဖိုးကိုအသစ်ဖန်တီးထားသော `geofence` consumer group ကိုရည်ညွှန်းရန် update လုပ်ပါ-

    ```json
    "consumerGroup": "geofence"
    ```

1. Azure Maps အကောင့်၏ subscription key ကိုဤ trigger တွင်အသုံးပြုရန်လိုအပ်သဖြင့်၊ `local.settings.json` ဖိုင်တွင် `MAPS_KEY` ဟုခေါ်သော entry အသစ်တစ်ခုထည့်ပါ။

1. Functions App ကို run လုပ်၍ message များကိုချိတ်ဆက်ပြီး process လုပ်နေကြောင်းသေချာပါစေ။ ယခင်သင်ခန်းစာမှ `iot-hub-trigger` သည်လည်း run လုပ်ပြီး blob များကို storage သို့ upload လုပ်မည်။

    > Blob storage တွင် GPS အချက်အလက်များကို duplicate ဖြစ်ခြင်းမှရှောင်ရှားရန်၊ cloud တွင် run လုပ်နေသော Functions App ကိုရပ်တန့်နိုင်သည်။ ၎င်းကိုလုပ်ရန်အောက်ပါ command ကိုအသုံးပြုပါ-
    >
    > ```sh
    > az functionapp stop --resource-group gps-sensor \
    >                     --name <functions_app_name>
    > ```
    >
    > `<functions_app_name>` ကို Functions App အတွက်သင်အသုံးပြုသောအမည်ဖြင့်အစားထိုးပါ။
    >
    > နောက်ပိုင်းတွင် restart လုပ်လိုပါက အောက်ပါ command ကိုအသုံးပြုနိုင်သည်-
    >
    > ```sh
    > az functionapp start --resource-group gps-sensor \
    >                     --name <functions_app_name>
    > ```
    >
    > `<functions_app_name>` ကို Functions App အတွက်သင်အသုံးပြုသောအမည်ဖြင့်အစားထိုးပါ။

### Task - trigger မှ geofence ကိုစမ်းသပ်ပါ

ဤသင်ခန်းစာ၏အစပိုင်းတွင် geofence ကို query လုပ်၍ point တစ်ခုသည် geofence အတွင်းရှိသည်၊ အပြင်ရှိသည်ကိုစမ်းသပ်ခဲ့သည်။ trigger အတွင်းမှတူညီသော web request ကိုလုပ်နိုင်သည်။

1. geofence ကို query လုပ်ရန်၊ ၎င်း၏ UDID လိုအပ်သည်။ `local.settings.json` ဖိုင်တွင် `GEOFENCE_UDID` ဟုခေါ်သော entry အသစ်တစ်ခုကိုဤတန်ဖိုးဖြင့်ထည့်ပါ။

1. `geofence-trigger` trigger ၏ `__init__.py` ဖိုင်ကိုဖွင့်ပါ။

1. ဖိုင်၏အပေါ်ပိုင်းတွင်အောက်ပါ import ကိုထည့်ပါ-

    ```python
    import json
    import os
    import requests
    ```

    `requests` package သည် web API calls လုပ်ရန်ခွင့်ပြုသည်။ Azure Maps တွင် Python SDK မရှိသဖြင့် Python code မှအသုံးပြုရန် web API calls လုပ်ရန်လိုအပ်သည်။

1. `main` method ၏အစပိုင်းတွင် Maps subscription key ကိုရယူရန်အောက်ပါ 2 လိုင်းကိုထည့်ပါ-

    ```python
    maps_key = os.environ['MAPS_KEY']
    geofence_udid = os.environ['GEOFENCE_UDID']    
    ```

1. `for event in events` loop အတွင်းတွင် event တစ်ခုစီမှ latitude နှင့် longitude ကိုရယူရန်အောက်ပါ code ကိုထည့်ပါ-

    ```python
    event_body = json.loads(event.get_body().decode('utf-8'))
    lat = event_body['gps']['lat']
    lon = event_body['gps']['lon']
    ```

    ဤ code သည် event body မှ JSON ကို dictionary သို့ convert လုပ်ပြီး၊ `gps` field မှ `lat` နှင့် `lon` ကို extract လုပ်သည်။

1. `requests` ကိုအသုံးပြုသောအခါ၊ curl ဖြင့်လုပ်ခဲ့သည့်အတိုင်း URL ကိုတည်ဆောက်ရန်မလိုပါ။ URL အပိုင်းကိုသာအသုံးပြုပြီး၊ parameters ကို dictionary အနေနှင့် pass လုပ်နိုင်သည်။ call လုပ်ရန် URL ကိုသတ်မှတ်ပြီး parameters ကို configure လုပ်ရန်အောက်ပါ code ကိုထည့်ပါ-

    ```python
    url = 'https://atlas.microsoft.com/spatial/geofence/json'

    params = {
        'api-version': 1.0,
        'deviceId': 'gps-sensor',
        'subscription-key': maps_key,
        'udid' : geofence_udid,
        'lat' : lat,
        'lon' : lon
    }
    ```

    `params` dictionary တွင် web API ကို curl ဖြင့် call လုပ်သောအခါအသုံးပြုခဲ့သည့် key value pairs များနှင့်ကိုက်ညီမည်။

1. web API ကို call လုပ်ရန်အောက်ပါ code ကိုထည့်ပါ-

    ```python
    response = requests.get(url, params=params)
    response_body = json.loads(response.text)
    ```

    ဤ code သည် URL ကို parameters ဖြင့် call လုပ်ပြီး response object ကိုရယူသည်။

1. ဤ code အောက်တွင်အောက်ပါ code ကိုထည့်ပါ-

    ```python
    distance = response_body['geometries'][0]['distance']

    if distance == 999:
        logging.info('Point is outside geofence')
    elif distance > 0:
        logging.info(f'Point is just outside geofence by a distance of {distance}m')
    elif distance == -999:
        logging.info(f'Point is inside geofence')
    else:
        logging.info(f'Point is just inside geofence by a distance of {distance}m')
    ```

    ဤ code သည် geometry တစ်ခုကို assumption လုပ်ပြီး၊ geometry တစ်ခုမှ distance ကို extract လုပ်သည်။ ထို့နောက် distance အပေါ်မူတည်၍ log message များကို output လုပ်သည်။

1. ဤ code ကို run လုပ်ပါ။ GPS coordinates သည် geofence အတွင်းရှိသည်၊ အပြင်ရှိသည်ကို logging output တွင်မြင်ရမည်။ point သည် 50m အတွင်းရှိပါက distance ကိုမြင်ရမည်။ GPS sensor ၏နေရာအပေါ်မူတည်၍ geofence များကိုစမ်းသပ်ပါ၊ sensor ကိုရွှေ့ပါ (ဥပမာ WiFi tethering သို့မဟုတ် virtual IoT device တွင် coordinates များကိုပြောင်းခြင်း) distance ပြောင်းလဲမှုကိုကြည့်ပါ။

1. ပြင်ဆင်ပြီးပါက၊ cloud တွင် Functions app သို့ဤ code ကို deploy လုပ်ပါ။ Application Settings အသစ်ကို deploy လုပ်ရန်မမေ့ပါနှင့်။

    > ⚠️ [Project 2, Lesson 5 မှ Application Settings ကို upload လုပ်ရန်လမ်းညွှန်ချက်များကိုလိုအပ်ပါက](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---upload-your-application-settings) ကိုရည်ညွှန်းနိုင်သည်။

    > ⚠️ [Project 2, Lesson 5 မှ Functions app ကို cloud သို့ deploy လုပ်ရန်လမ်းညွှန်ချက်များကိုလိုအပ်ပါက](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---deploy-your-functions-app-to-the-cloud) ကိုရည်ညွှန်းနိုင်သည်။

> 💁 ဤ code ကို [code/functions](../../../../../3-transport/lessons/4-geofences/code/functions) folder တွင်တွေ့နိုင်သည်။

---

## 🚀 Challenge

ဤသင်ခန်းစာတွင် polygon တစ်ခုပါရှိသော GeoJSON ဖိုင်တစ်ခုကိုအသုံးပြု၍ geofence တစ်ခုကိုထည့်သွင်းခဲ့သည်။ `properties` section တွင် `geometryId` တန်ဖိုးများကွဲပြားစွာရှိပါက polygon များစွာပါရှိသော GeoJSON ဖိုင်ကို upload လုပ်နိုင်သည်။

Polygon များစွာပါရှိသော GeoJSON ဖိုင်ကို upload လုပ်ပြီး GPS coordinates သည်အနီးဆုံး polygon သို့မဟုတ်အတွင်းရှိသည်ကိုရှာဖွေရန် code ကိုပြင်ဆင်ပါ။

## Post-lecture quiz

[Post-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/28)

## Review & Self Study

* Geofences နှင့်၎င်းတို့၏အသုံးပြုမှုများအကြောင်း [Wikipedia ၏ Geofencing စာမျက်နှာ](https://en.wikipedia.org/wiki/Geo-fence) တွင်ဖတ်ရှုပါ။
* Azure Maps geofencing API အကြောင်း [Microsoft Azure Maps Spatial - Get Geofence documentation](https://docs.microsoft.com/rest/api/maps/spatial/getgeofence?WT.mc_id=academic-17441-jabenn) တွင်ဖတ်ရှုပါ။
* Consumer groups အကြောင်း [Features and terminology in Azure Event Hubs - Event consumers documentation on Microsoft docs](https://docs.microsoft.com/azure/event-hubs/event-hubs-features?WT.mc_id=academic-17441-jabenn#event-consumers) တွင်ဖတ်ရှုပါ။

## Assignment

[Twilio ကိုအသုံးပြု၍ notifications ပို့ပါ](assignment.md)

---

**အကြောင်းကြားချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှုအတွက် ကြိုးစားနေသော်လည်း၊ အလိုအလျောက် ဘာသာပြန်မှုများတွင် အမှားများ သို့မဟုတ် မတိကျမှုများ ပါဝင်နိုင်သည်ကို သတိပြုပါ။ မူရင်းဘာသာစကားဖြင့် ရေးသားထားသော စာရွက်စာတမ်းကို အာဏာရှိသော ရင်းမြစ်အဖြစ် သတ်မှတ်သင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူက ဘာသာပြန်မှု ဝန်ဆောင်မှုကို အသုံးပြုရန် အကြံပြုပါသည်။ ဤဘာသာပြန်မှုကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော အလွဲအလွဲအချော်များ သို့မဟုတ် အနားယူမှုမှားများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။