<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9095c61445c2bca7245ef9b59a186a11",
  "translation_date": "2025-08-28T16:56:27+00:00",
  "source_file": "3-transport/lessons/3-visualize-location-data/README.md",
  "language_code": "my"
}
-->
# တည်နေရာဒေတာကိုမြင်သာစေခြင်း

![ဒီသင်ခန်းစာအတွက် Sketchnote အကျဉ်းချုပ်](../../../../../translated_images/my/lesson-13.a259db1485021be7d7c72e90842fbe0ab977529e8684c179b5fb1ea75e92b3ef.jpg)

> Sketchnote by [Nitya Narasimhan](https://github.com/nitya)။ ပုံကိုနှိပ်ပြီး အကြီးစားဗားရှင်းကိုကြည့်ပါ။

ဒီဗီဒီယိုမှာ Azure Maps နှင့် IoT အကြောင်းကို အကျဉ်းချုပ်ဖော်ပြထားပြီး၊ ဒီသင်ခန်းစာမှာ လေ့လာမည့်အကြောင်းအရာများပါဝင်သည်။

[![Azure Maps - The Microsoft Azure Enterprise Location Platform](https://img.youtube.com/vi/P5i2GFTtb2s/0.jpg)](https://www.youtube.com/watch?v=P5i2GFTtb2s)

> 🎥 အထက်ပါပုံကိုနှိပ်ပြီး ဗီဒီယိုကိုကြည့်ပါ။

## သင်ခန်းစာမတိုင်မီမေးခွန်းများ

[သင်ခန်းစာမတိုင်မီမေးခွန်းများ](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/25)

## နိဒါန်း

ပြီးခဲ့သည့်သင်ခန်းစာတွင် သင်သည် sensor များမှ GPS ဒေတာကို serverless code အသုံးပြု၍ cloud storage container ထဲသို့ သိမ်းဆည်းပုံကို လေ့လာခဲ့ပါသည်။ ယခု သင်သည် အဆိုပါဒေတာများကို Azure map ပေါ်တွင် မြင်သာစေခြင်းကို လေ့လာမည်ဖြစ်သည်။ သင်သည် web page ပေါ်တွင် map တစ်ခုဖန်တီးပုံ၊ GeoJSON ဒေတာဖော်မတ်နှင့် GPS ဒေတာများကို map ပေါ်တွင် plot လုပ်ပုံကို လေ့လာမည်ဖြစ်သည်။

ဒီသင်ခန်းစာတွင် လေ့လာမည့်အကြောင်းအရာများမှာ -

* [ဒေတာမြင်သာစေခြင်းဆိုတာဘာလဲ](../../../../../3-transport/lessons/3-visualize-location-data)
* [Map ဝန်ဆောင်မှုများ](../../../../../3-transport/lessons/3-visualize-location-data)
* [Azure Maps resource တစ်ခုဖန်တီးခြင်း](../../../../../3-transport/lessons/3-visualize-location-data)
* [Web page ပေါ်တွင် map တစ်ခုပြသခြင်း](../../../../../3-transport/lessons/3-visualize-location-data)
* [GeoJSON ဖော်မတ်](../../../../../3-transport/lessons/3-visualize-location-data)
* [GeoJSON အသုံးပြု၍ GPS ဒေတာကို map ပေါ်တွင် plot လုပ်ခြင်း](../../../../../3-transport/lessons/3-visualize-location-data)

> 💁 ဒီသင်ခန်းစာတွင် HTML နှင့် JavaScript အနည်းငယ်ပါဝင်မည်ဖြစ်သည်။ HTML နှင့် JavaScript အသုံးပြု၍ web development လေ့လာလိုပါက [Web development for beginners](https://github.com/microsoft/Web-Dev-For-Beginners) ကိုကြည့်ပါ။

## ဒေတာမြင်သာစေခြင်းဆိုတာဘာလဲ

ဒေတာမြင်သာစေခြင်းဆိုတာ ဒေတာကို လူသားများအတွက် နားလည်ရလွယ်ကူစေရန် ပုံဖော်ပြသခြင်းဖြစ်သည်။ ဒါဟာ chart နှင့် graph များနှင့်သာမက၊ ဒေတာကို ပုံဖော်ပြသနိုင်သည့် နည်းလမ်းအားလုံးကို ရည်ညွှန်းသည်။ ဒေတာကို ပိုမိုနားလည်စေရန်သာမက၊ ဆုံးဖြတ်ချက်ချနိုင်စေရန်လည်း အထောက်အကူဖြစ်စေသည်။

ရိုးရှင်းသောဥပမာတစ်ခုအနေနှင့် - စိုက်ပျိုးရေးစီမံကိန်းတွင် သင်သည် မြေစိုထိုင်းဆဒေတာကို စုဆောင်းခဲ့သည်။ 2021 ခုနှစ် ဇွန်လ 1 ရက်နေ့တွင် တစ်နာရီခြားစီ စုဆောင်းထားသော မြေစိုထိုင်းဆဒေတာကို အောက်ပါအတိုင်းဖြစ်နိုင်သည် -

| Date             | Reading |
| ---------------- | ------: |
| 01/06/2021 00:00 |     257 |
| 01/06/2021 01:00 |     268 |
| 01/06/2021 02:00 |     295 |
| 01/06/2021 03:00 |     305 |
| 01/06/2021 04:00 |     325 |
| 01/06/2021 05:00 |     359 |
| 01/06/2021 06:00 |     398 |
| 01/06/2021 07:00 |     410 |
| 01/06/2021 08:00 |     429 |
| 01/06/2021 09:00 |     451 |
| 01/06/2021 10:00 |     460 |
| 01/06/2021 11:00 |     452 |
| 01/06/2021 12:00 |     420 |
| 01/06/2021 13:00 |     408 |
| 01/06/2021 14:00 |     431 |
| 01/06/2021 15:00 |     462 |
| 01/06/2021 16:00 |     432 |
| 01/06/2021 17:00 |     402 |
| 01/06/2021 18:00 |     387 |
| 01/06/2021 19:00 |     360 |
| 01/06/2021 20:00 |     358 |
| 01/06/2021 21:00 |     354 |
| 01/06/2021 22:00 |     356 |
| 01/06/2021 23:00 |     362 |

ဒီလိုဒေတာကို လူသားအနေနှင့် နားလည်ဖတ်ရှုရခက်နိုင်သည်။ ဒေတာကို ပထမဦးဆုံးမြင်သာစေခြင်းအနေနှင့် line chart တစ်ခုအဖြစ် plot လုပ်နိုင်သည် -

![အထက်ပါဒေတာ၏ line chart](../../../../../translated_images/my/chart-soil-moisture.fd6d9d0cdc0b5f75e78038ecb8945dfc84b38851359de99d84b16e3336d6d7c2.png)

ထို့နောက်၊ မြေစိုထိုင်းဆ reading 450 တွင် ရေချိန်စနစ်ကို ဖွင့်ထားသောအချိန်ကိုပြသသည့် လိုင်းတစ်ခုထည့်ခြင်းဖြင့် ပိုမိုမြင်သာစေနိုင်သည် -

![မြေစိုထိုင်းဆ reading 450 တွင် relay ဖွင့်ထားသော chart](../../../../../translated_images/my/chart-soil-moisture-relay.fbb391236d34a64d0abf1df396e9197e0a24df14150620b9cc820a64a55c9326.png)

ဒီ chart က မြေစိုထိုင်းဆအဆင့်များနှင့် ရေချိန်စနစ်ဖွင့်ထားသောအချိန်များကို အလွယ်တကူမြင်နိုင်စေသည်။

chart များသာမက၊ ဒေတာမြင်သာစေခြင်းအတွက် အခြားနည်းလမ်းများလည်းရှိသည်။ ဥပမာအားဖြင့် ရာသီဥတုကိုစောင့်ကြည့်သည့် IoT စက်ပစ္စည်းများသည် web app သို့မဟုတ် mobile app များတွင် ရာသီဥတုအခြေအနေများကို ပုံများဖြင့်ပြသနိုင်သည်။ ဥပမာအားဖြင့် မိုးအုံ့နေသောနေ့များအတွက် တိမ်ပုံ၊ မိုးရွာနေသောနေ့များအတွက် မိုးတိမ်ပုံစသည်ဖြင့်။ ဒေတာကိုမြင်သာစေခြင်းနည်းလမ်းများစွာရှိပြီး၊ အချို့ကတော့ အလေးအနက်ဖြင့်၊ အချို့ကတော့ ပျော်စရာဖြစ်သည်။

✅ သင်မြင်ဖူးသော ဒေတာမြင်သာစေခြင်းနည်းလမ်းများကိုစဉ်းစားပါ။ အဘယ်နည်းလမ်းများက ပိုမိုရှင်းလင်းပြီး အမြန်ဆုံးဆုံးဖြတ်ချက်ချနိုင်စေခဲ့ပါသလဲ။

အကောင်းဆုံးမြင်သာစေမှုများသည် လူသားများကို အမြန်ဆုံးဆုံးဖြတ်ချက်ချနိုင်စေသည်။ ဥပမာအားဖြင့် စက်မှုစက်ပစ္စည်းများမှ အမျိုးမျိုးသော reading များကိုပြသသည့် gauge များစွာရှိသောနံရံတစ်ခုသည် နားလည်ဖတ်ရှုရခက်နိုင်သည်။ သို့သော် တစ်ခုခုမှားယွင်းသွားသောအခါ အနီရောင်မီးလင်းနေသည်ကိုမြင်ရသည်မှာ လူသားများအတွက် အမြန်ဆုံးဆုံးဖြတ်ချက်ချနိုင်စေသည်။ 

GPS ဒေတာနှင့်ဆက်စပ်သောအခါ၊ အကောင်းဆုံးမြင်သာစေမှုမှာ map ပေါ်တွင် ဒေတာကို plot လုပ်ခြင်းဖြစ်နိုင်သည်။ ဥပမာအားဖြင့် ပို့ဆောင်ရေးယာဉ်များကိုပြသသည့် map တစ်ခုသည် processing plant တွင်အလုပ်လုပ်နေသူများကို ယာဉ်များရောက်ရှိမည့်အချိန်ကိုမြင်နိုင်စေသည်။ ထို့အပြင် ယာဉ်များ၏လက်ရှိတည်နေရာပုံများသာမက၊ ယာဉ်တွင်းပါဝင်သောအကြောင်းအရာများကိုလည်းပြသနိုင်ပါက၊ plant တွင်အလုပ်လုပ်နေသူများအတွက် အဆင်ပြေစေသည်။

## Map ဝန်ဆောင်မှုများ

Map များနှင့်အလုပ်လုပ်ခြင်းသည် စိတ်ဝင်စားဖွယ်ရာဖြစ်ပြီး၊ Bing Maps, Leaflet, Open Street Maps, Google Maps စသည်ဖြင့် ရွေးချယ်စရာများစွာရှိသည်။ ဒီသင်ခန်းစာတွင် သင်သည် [Azure Maps](https://azure.microsoft.com/services/azure-maps/?WT.mc_id=academic-17441-jabenn) နှင့် GPS ဒေတာကိုပြသပုံကို လေ့လာမည်ဖြစ်သည်။

![Azure Maps အမှတ်တံဆိပ်](../../../../../translated_images/my/azure-maps-logo.35d01dcfbd81fe6140e94257aaa1538f785a58c91576d14e0ebe7a2f6c694b99.png)

Azure Maps သည် "geospatial ဝန်ဆောင်မှုများနှင့် SDK များစုစည်းမှုဖြစ်ပြီး၊ နောက်ဆုံးပေါ် map ဒေတာများကို အသုံးပြု၍ web နှင့် mobile application များအတွက် ပထဝီဝင်အကြောင်းအရာများပေးစွမ်းသည်။" Developer များအတွက် လှပပြီး interactive ဖြစ်သော map များဖန်တီးရန် လိုအပ်သောကိရိယာများကိုပေးသည်။ 

✅ [mapping code samples](https://docs.microsoft.com/samples/browse?WT.mc_id=academic-17441-jabenn&products=azure-maps) များကိုစမ်းသပ်ကြည့်ပါ။

Azure Maps သည် blank canvas, tiles, satellite images, satellite images with roads superimposed, grayscale maps, shaded relief maps, night view maps, high contrast maps စသည်ဖြင့် map များကိုပြသနိုင်သည်။ [Azure Event Grid](https://azure.microsoft.com/services/event-grid/?WT.mc_id=academic-17441-jabenn) နှင့်ပေါင်းစပ်ခြင်းဖြင့် map များကို real-time update လုပ်နိုင်သည်။ map ၏ look နှင့် behavior ကို control လုပ်ရန် pinch, drag, click စသည်ဖြင့် event များကိုတုံ့ပြန်စေသော control များကို enable လုပ်နိုင်သည်။ map ၏ look ကို control လုပ်ရန် bubble, line, polygon, heat map စသည်ဖြင့် layer များထည့်နိုင်သည်။ map ၏ style ကိုရွေးချယ်ခြင်းသည် သင့်ရွေးချယ်သော SDK ပေါ်မူတည်သည်။

Azure Maps API များကို [REST API](https://docs.microsoft.com/javascript/api/azure-maps-rest/?WT.mc_id=academic-17441-jabenn&view=azure-maps-typescript-latest), [Web SDK](https://docs.microsoft.com/azure/azure-maps/how-to-use-map-control?WT.mc_id=academic-17441-jabenn), သို့မဟုတ် mobile app ဖန်တီးရန် [Android SDK](https://docs.microsoft.com/azure/azure-maps/how-to-use-android-map-control-library?WT.mc_id=academic-17441-jabenn&pivots=programming-language-java-android) တို့ကိုအသုံးပြု၍ ရယူနိုင်သည်။

ဒီသင်ခန်းစာတွင် သင်သည် Web SDK ကိုအသုံးပြု၍ map တစ်ခုဆွဲပြီး sensor ၏ GPS တည်နေရာလမ်းကြောင်းကိုပြသမည်ဖြစ်သည်။

## Azure Maps resource တစ်ခုဖန်တီးခြင်း

Azure Maps account တစ်ခုဖန်တီးရန် ပထမဦးဆုံးအဆင့်ဖြစ်သည်။

### Task - Azure Maps resource တစ်ခုဖန်တီးခြင်း

1. Terminal သို့မဟုတ် Command Prompt မှာ အောက်ပါ command ကို run လုပ်ပြီး `gps-sensor` resource group တွင် Azure Maps resource တစ်ခုဖန်တီးပါ -

    ```sh
    az maps account create --name gps-sensor \
                           --resource-group gps-sensor \
                           --accept-tos \
                           --sku S1
    ```

    ဤ command သည် `gps-sensor` ဟုခေါ်သော Azure Maps resource တစ်ခုဖန်တီးမည်ဖြစ်သည်။ အသုံးပြုထားသော tier သည် `S1` ဖြစ်ပြီး၊ အခမဲ့ call အရေအတွက်များစွာပါဝင်သော်လည်း၊ အခကြေးငွေ tier ဖြစ်သည်။

    > 💁 Azure Maps အသုံးပြုမှု၏ကုန်ကျစရိတ်ကိုကြည့်ရန် [Azure Maps pricing page](https://azure.microsoft.com/pricing/details/azure-maps/?WT.mc_id=academic-17441-jabenn) ကိုကြည့်ပါ။

1. maps resource အတွက် API key တစ်ခုလိုအပ်မည်။ အောက်ပါ command ကိုအသုံးပြု၍ key ကိုရယူပါ -

    ```sh
    az maps account keys list --name gps-sensor \
                              --resource-group gps-sensor \
                              --output table
    ```

    `PrimaryKey` အတန်း၏တန်ဖိုးကိုကူးယူထားပါ။

## Web page ပေါ်တွင် map တစ်ခုပြသခြင်း

ယခု သင်သည် map ကို web page ပေါ်တွင်ပြသရန် နောက်တစ်ဆင့်ကိုဆောင်ရွက်နိုင်ပါပြီ။ Web app သေးငယ်တစ်ခုအတွက် `html` ဖိုင်တစ်ခုသာအသုံးပြုမည်ဖြစ်သည်။ Production သို့မဟုတ်အဖွဲ့လိုက်ပတ်ဝန်းကျင်တွင် web app တွင်ပိုမိုစိတ်ဝင်စားဖွယ်အပိုင်းများပါဝင်နိုင်သည်။

### Task - Web page ပေါ်တွင် map တစ်ခုပြသခြင်း

1. သင့် local computer တွင် folder တစ်ခုတွင် `index.html` ဟုခေါ်သောဖိုင်တစ်ခုဖန်တီးပါ။ map ကိုထည့်ရန် HTML markup ထည့်ပါ -

    ```html
    <html>
    <head>
        <style>
            #myMap {
                width:100%;
                height:100%;
            }
        </style>
    </head>
    
    <body onload="init()">
        <div id="myMap"></div>
    </body>
    </html>
    ```

    map သည် `myMap` `div` တွင် load လုပ်မည်ဖြစ်သည်။ အချို့သော styles များသည် page ၏အကျယ်နှင့်အမြင့်ကိုဖြန့်ဝေစေသည်။

    > 🎓 `div` သည် web page ၏အပိုင်းတစ်ခုဖြစ်ပြီး၊ အမည်ပေး၍ style ပြုလုပ်နိုင်သည်။

1. `<head>` tag ဖွင့်ထားသောနေရာအောက်တွင် map display ကိုထိန်းချုပ်ရန် external style sheet တစ်ခုနှင့် map ၏ behavior ကိုစီမံရန် Web SDK မှ external script တစ်ခုထည့်ပါ -

    ```html
    <link rel="stylesheet" href="https://atlas.microsoft.com/sdk/javascript/mapcontrol/2/atlas.min.css" type="text/css" />
    <script src="https://atlas.microsoft.com/sdk/javascript/mapcontrol/2/atlas.min.js"></script>
    ```

    ဤ style sheet တွင် map ၏ look ကိုထိန်းချုပ်သည့် setting များပါဝင်ပြီး၊ script ဖိုင်တွင် map ကို load လုပ်ရန် code ပါဝင်သည်။ ဤ code ကိုထည့်ခြင်းသည် C++ header files ထည့်ခြင်း သို့မဟုတ် Python modules import လုပ်ခြင်းနှင့်ဆင်တူသည်။

1. အဆိုပါ script အောက်တွင် map ကိုစတင်ရန် script block တစ်ခုထည့်ပါ။

    ```javascript
    <script type='text/javascript'>
        function init() {
            var map = new atlas.Map('myMap', {
                center: [-122.26473, 47.73444],
                zoom: 12,
                authOptions: {
                    authType: "subscriptionKey",
                    subscriptionKey: "<subscription_key>",

                }
            });
        }
    </script>
    ```

    `<subscription_key>` ကို သင့် Azure Maps account အတွက် API key ဖြင့်အစားထိုးပါ။

    သင့် `index.html` ဖိုင်ကို web browser တွင်ဖွင့်ပါက၊ Seattle မြို့ကိုအခြေခံထားသော map တစ်ခုကိုမြင်ရမည်ဖြစ်သည်။

    ![Washington State, USA တွင်ရှိသော Seattle မြို့ကိုပြသသည့် map](../../../../../translated_images/my/map-image.8fb2c53eb23ef39c1c0a4410a5282e879b3b452b707eb066ff04c5488d3d72b7.png)

    ✅ zoom နှင့် center parameters ကိုစမ်းသပ်ပြီး map display ကိုပြောင်းလဲကြည့်ပါ။ သင့်ဒေတာ၏ latitude နှင့် longitude ကိုအညွှန်းပြု၍ center ကိုပြောင်းလဲနိုင်သည်။

> 💁 Web app များကို locally အလုပ်လုပ်ရန်ပိုမိုကောင်းမွန်သောနည်းလမ်းမှာ [http-server](https://www.npmjs.com/package/http-server) ကို install လုပ်ခြင်းဖြစ်သည်။ [node.js](https://nodejs.org/) နှင့် [npm](https://www.npmjs.com/) ကို install လုပ်ထားရန်လိုအပ်သည်။ အဆိုပါ tools များကို install လုပ်ပြီးနောက်၊ သင့် `index.html` ဖိုင်ရှိနေရာသို့သွားပြီး `http-server` ဟုရိုက်ပါ။ Web app သည် local webserver [http://127.0.0.1:8080/](http://127.0.0.1:8080/) တွင်ဖွင့်လှစ်မည်ဖြစ်သည်။

## GeoJSON ဖော်မတ်

ယခု သင့် web app သည် map ကိုပြသထားပြီးဖြစ်သောကြောင့်၊ သင့် storage account မှ GPS ဒေတာကိုထုတ်ယူပြီး map ပေါ်တွင် marker layer အဖြစ်ပြသရန်လိုအပ်သည်။ ထိုလုပ်ဆောင်မှုမပြုမီ၊ Azure Maps အတွက်လိုအပ်သော [GeoJSON](https://wikipedia.org/wiki/GeoJSON) ဖော်မတ်ကိုကြည့်ပါ။

[GeoJSON](https://geojson.org/) သည် geographic-specific ဒေတာကိုကိုင်တွယ်ရန်အထူး
✅ Azure Maps သည် GeoJSON စံပုံစံကို ပံ့ပိုးပေးပြီး [အဆင့်မြှင့်ထားသော အင်္ဂါရပ်များ](https://docs.microsoft.com/azure/azure-maps/extend-geojson?WT.mc_id=academic-17441-jabenn) ကိုလည်း ပံ့ပိုးပေးပါသည်။ ဥပမာအားဖြင့် စက်ဝိုင်းများနှင့် အခြားဂျီဩမက်ထရီများကို ရေးဆွဲနိုင်ခြင်း။

## GeoJSON ကို အသုံးပြု၍ မြေပုံပေါ်တွင် GPS ဒေတာကို ဖော်ပြခြင်း

ယခင်သင်ခန်းစာတွင် တည်ဆောက်ထားသော storage မှ ဒေတာကို အသုံးပြုရန် အဆင်သင့်ဖြစ်ပါပြီ။ သတိပေးချက်အနေနှင့် ဒေတာသည် blob storage တွင် ဖိုင်အများအပြားအနေဖြင့် သိမ်းဆည်းထားပြီး Azure Maps သုံးနိုင်ရန် ဖိုင်များကို ပြန်လည်ရယူပြီး parse လုပ်ရန် လိုအပ်ပါသည်။

### Task - storage ကို ဝက်ဘ်ပေ့ချ်မှ ဝင်ရောက်အသုံးပြုနိုင်ရန် ပြင်ဆင်ခြင်း

သင်၏ storage ကို ခေါ်ယူပြီး ဒေတာကို ရယူရန် ကြိုးစားပါက browser console တွင် error များပေါ်လာနိုင်သည်။ ဒါဟာ storage တွင် [CORS](https://developer.mozilla.org/docs/Web/HTTP/CORS) ကို ပြင်ဆင်ရန် လိုအပ်သောကြောင့်ဖြစ်ပြီး အပြင်ဘက်ဝက်ဘ်အက်ပ်များမှ ဒေတာကို ဖတ်ရှုနိုင်ရန် ခွင့်ပြုချက်များကို သတ်မှတ်ရန် လိုအပ်ပါသည်။

> 🎓 CORS သည် "Cross-Origin Resource Sharing" ကို ဆိုလိုပြီး အထူးသဖြင့် Azure တွင် လုံခြုံရေးအတွက် ထည့်သွင်းသတ်မှတ်ရန် လိုအပ်ပါသည်။ သင်မမျှော်လင့်ထားသော site များမှ သင်၏ဒေတာကို ဝင်ရောက်အသုံးပြုခြင်းကို တားဆီးပေးပါသည်။

1. CORS ကို enable လုပ်ရန် အောက်ပါ command ကို run လုပ်ပါ။

    ```sh
    az storage cors add --methods GET \
                        --origins "*" \
                        --services b \
                        --account-name <storage_name> \
                        --account-key <key1>
    ```

    `<storage_name>` ကို သင်၏ storage account အမည်ဖြင့် အစားထိုးပါ။ `<key1>` ကို သင်၏ storage account အတွက် account key ဖြင့် အစားထိုးပါ။

    ဤ command သည် website မည်သည့်အရာမဆို (wildcard `*` သည် မည်သည့် site မဆိုကို ဆိုလိုသည်) သင်၏ storage account မှ *GET* request (ဒေတာရယူခြင်း) ပြုလုပ်နိုင်ရန် ခွင့်ပြုသည်။ `--services b` သည် ဤ setting ကို blob များအတွက်သာ အသုံးပြုရန် ဆိုလိုသည်။

### Task - storage မှ GPS ဒေတာကို load လုပ်ခြင်း

1. `init` function ၏ အကြောင်းအရာအားလုံးကို အောက်ပါ code ဖြင့် အစားထိုးပါ။

    ```javascript
    fetch("https://<storage_name>.blob.core.windows.net/gps-data/?restype=container&comp=list")
        .then(response => response.text())
        .then(str => new window.DOMParser().parseFromString(str, "text/xml"))
        .then(xml => {
            let blobList = Array.from(xml.querySelectorAll("Url"));
                blobList.forEach(async blobUrl => {
                    loadJSON(blobUrl.innerHTML)                
        });
    })
    .then( response => {
        map = new atlas.Map('myMap', {
            center: [-122.26473, 47.73444],
            zoom: 14,
            authOptions: {
                authType: "subscriptionKey",
                subscriptionKey: "<subscription_key>",
    
            }
        });
        map.events.add('ready', function () {
            var source = new atlas.source.DataSource();
            map.sources.add(source);
            map.layers.add(new atlas.layer.BubbleLayer(source));
            source.add(features);
        })
    })
    ```

    `<storage_name>` ကို သင်၏ storage account အမည်ဖြင့် အစားထိုးပါ။ `<subscription_key>` ကို သင်၏ Azure Maps account အတွက် API key ဖြင့် အစားထိုးပါ။

    ဤနေရာတွင် အရာများစွာဖြစ်ပျက်နေပါသည်။ ပထမဦးဆုံး code သည် သင်၏ blob container မှ GPS ဒေတာကို သင်၏ storage account အမည်ဖြင့် တည်ဆောက်ထားသော URL endpoint ကို အသုံးပြု၍ fetch လုပ်ပါသည်။ ဤ URL သည် `gps-data` မှ retrieve လုပ်ပြီး resource type သည် container (`restype=container`) ဖြစ်ကြောင်း ဖော်ပြသည်။ ထို့နောက် blob များ၏ URL ကို ပြန်လည်ရယူနိုင်သည်။

    > 💁 ဤ URL ကို သင်၏ browser တွင် ထည့်သွင်းပြီး container တွင်ရှိသော blob များ၏ အသေးစိတ်ကို ကြည့်ရှုနိုင်ပါသည်။ အရာအားလုံးတွင် `Url` property ပါရှိပြီး blob ၏ အကြောင်းအရာကို ကြည့်ရှုနိုင်ရန် browser တွင် load လုပ်နိုင်ပါသည်။

    ထို့နောက် code သည် blob တစ်ခုချင်းစီကို load လုပ်ပြီး `loadJSON` function ကို ခေါ်ယူပါသည်။ ဤ function ကို နောက်တစ်ဆင့်တွင် ဖန်တီးမည်ဖြစ်သည်။ ထို့နောက် map control ကို ဖန်တီးပြီး `ready` event ကို code ထည့်သွင်းပါသည်။ ဤ event သည် map ကို ဝက်ဘ်ပေ့ချ်တွင် ဖော်ပြသောအခါ ခေါ်ယူသည်။

    ready event သည် Azure Maps data source ကို ဖန်တီးသည်။ ဤ data source သည် GeoJSON ဒေတာကို later တွင် populate လုပ်မည်ဖြစ်သည်။ ထို့နောက် data source ကို bubble layer ဖန်တီးရန် အသုံးပြုသည်။ ဤသည်မှာ GeoJSON တွင်ရှိသော point တစ်ခုချင်းစီ၏ ဗဟိုတွင် စက်ဝိုင်းများကို မြေပုံပေါ်တွင် ဖော်ပြခြင်းဖြစ်သည်။

1. `init` function အောက်တွင် script block တွင် `loadJSON` function ကို ထည့်သွင်းပါ။

    ```javascript
    var map, features;

    function loadJSON(file) {
        var xhr = new XMLHttpRequest();
        features = [];
        xhr.onreadystatechange = function () {
            if (xhr.readyState === XMLHttpRequest.DONE) {
                if (xhr.status === 200) {
                    gps = JSON.parse(xhr.responseText)
                    features.push(
                        new atlas.data.Feature(new atlas.data.Point([parseFloat(gps.gps.lon), parseFloat(gps.gps.lat)]))
                    )
                }
            }
        };
        xhr.open("GET", file, true);
        xhr.send();
    }    
    ```

    ဤ function သည် fetch routine မှ JSON ဒေတာကို parse လုပ်ရန် ခေါ်ယူပြီး longitude နှင့် latitude coordinates အဖြစ် GeoJSON အနေဖြင့် ဖတ်ရှုနိုင်ရန် ပြောင်းလဲပါသည်။  
    parse လုပ်ပြီးနောက် ဒေတာကို GeoJSON `Feature` အနေဖြင့် သတ်မှတ်ပါသည်။ map ကို initialize လုပ်ပြီး သင်၏ဒေတာ plotting လုပ်နေသော လမ်းကြောင်းပေါ်တွင် စက်ဝိုင်းများ ပေါ်လာမည်ဖြစ်သည်။

1. HTML page ကို သင်၏ browser တွင် load လုပ်ပါ။ map ကို load လုပ်ပြီး storage မှ GPS ဒေတာအားလုံးကို load လုပ်ပြီး မြေပုံပေါ်တွင် plot လုပ်ပါမည်။

    ![Seattle အနီးရှိ Saint Edward State Park ၏ မြေပုံ၊ ပန်းခြံ၏ အနားကို လမ်းကြောင်းအဖြစ် ဖော်ပြထားသော စက်ဝိုင်းများ](../../../../../translated_images/my/map-path.896832e72dc696ffe20650e4051027d4855442d955f93fdbb80bb417ca8a406f.png)

> 💁 ဤ code ကို [code](../../../../../3-transport/lessons/3-visualize-location-data/code) folder တွင် ရှာဖွေနိုင်ပါသည်။

---

## 🚀 စိန်ခေါ်မှု

Static ဒေတာကို marker အဖြစ် မြေပုံပေါ်တွင် ဖော်ပြနိုင်ခြင်းက လှပပါသည်။ သင်၏ web app ကို အဆင့်မြှင့်တင်ပြီး marker များ၏ လမ်းကြောင်းကို အချိန်နှင့်အမျှ animation ဖြင့် ဖော်ပြနိုင်ပါသလား။ timestamped json ဖိုင်များကို အသုံးပြုပါ။ maps တွင် animation အသုံးပြုခြင်းအတွက် [နမူနာများ](https://azuremapscodesamples.azurewebsites.net/) ရှာဖွေကြည့်ပါ။

## Post-lecture quiz

[Post-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/26)

## Review & Self Study

Azure Maps သည် IoT devices များနှင့် အလုပ်လုပ်ရန် အထူးအသုံးဝင်ပါသည်။

* [Microsoft docs တွင် Azure Maps documentation](https://docs.microsoft.com/azure/azure-maps/tutorial-iot-hub-maps?WT.mc_id=academic-17441-jabenn) တွင် အသုံးပြုမှုများကို ရှာဖွေပါ။
* [Microsoft Learn တွင် Azure Maps self-guided learning module](https://docs.microsoft.com/learn/modules/create-your-first-app-with-azure-maps/?WT.mc_id=academic-17441-jabenn) ကို အသုံးပြု၍ map making နှင့် waypoints အကြောင်းကို နက်နက်ရှိုင်းရှိုင်း လေ့လာပါ။

## Assignment

[Deploy your app](assignment.md)

---

**အကြောင်းကြားချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှုအတွက် ကြိုးစားနေသော်လည်း၊ အလိုအလျောက် ဘာသာပြန်မှုများတွင် အမှားများ သို့မဟုတ် မတိကျမှုများ ပါဝင်နိုင်သည်ကို သတိပြုပါ။ မူရင်းဘာသာစကားဖြင့် ရေးသားထားသော စာရွက်စာတမ်းကို အာဏာတရ အရင်းအမြစ်အဖြစ် သတ်မှတ်သင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူ့ဘာသာပြန်ပညာရှင်များမှ ပရော်ဖက်ရှင်နယ် ဘာသာပြန်မှုကို အကြံပြုပါသည်။ ဤဘာသာပြန်မှုကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော အလွဲအလွတ်များ သို့မဟုတ် အနားယူမှားမှုများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။