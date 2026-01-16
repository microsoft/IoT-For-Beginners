<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3dce18fab38adf93ff30b8c221b1eec5",
  "translation_date": "2026-01-07T01:22:30+00:00",
  "source_file": "hardware.md",
  "language_code": "te"
}
-->
# హార్డ్వేర్

IoT లో **T** అంటే **Things** అంటే మన చుట్టుపక్కల ప్రపంచంతో పరస్పరం చేసుకునే పరికరాలను సూచిస్తుంది. ప్రతి ప్రాజెక్ట్ విద్యార్థులు మరియు హాబీষ্ট్లకు అందుబాటులో ఉన్న వాస్తవ ప్రపంచ హార్డ్వేర్ ఆధారపడింది. వ్యక్తిగత అభిరుచులు, ప్రోగ్రామింగ్ భాష జ్ఞానం లేదా ఇష్టాల, అభ్యాస లక్ష్యాలు మరియు అందుబాటును బట్టి ఉపయోగించుకునేందుకు మాకు రెండు IoT హార్డ్వేర్ ఎంపికలు ఉన్నాయి. హార్డ్వేర్ అందుబాటులో లేకపోయేవారికి లేదా కొనుగోలు చేసే ముందు మరింత తెలుసుకోవాలని అనుకునేవారికి మేము 'వర్చువల్ హార్డ్వేర్' వెర్షన్ కూడా అందిస్తున్నాము.

> 💁 అసైన్మెంట్లను పూర్తి చేయడానికి మీరు ఎటువంటి IoT హార్డ్వేర్ కొనుగోలు చేయవలసిన అవసరం లేదు. మీరు వర్చువల్ IoT హార్డ్వేర్ ఉపయోగించి అన్నీ చేయవచ్చు.

భౌతిక హార్డ్వేర్ ఎంపికలు Arduino లేదా Raspberry Pi గా ఉన్నాయి. ప్రతి ప్లాట్‌ఫారమ్‌కు తన సొంత లాభాలు మరియు నష్టాలు ఉన్నాయి, ఇవన్నీ ప్రారంభ పాఠాలలో ఒకటిలో వివరించబడ్డాయి. మీరు ఇంకా హార్డ్వేర్ ప్లాట్‌ఫారమ్ గురించి నిర్ణయించుకోలేదు అయితే, మీరు ఏ హార్డ్వేర్ ప్లాట్‌ఫారమ్ నేర్చుకోవడంలో ఎక్కువ ఆసక్తి ఉన్నదో నిర్ణయించుకోవడానికి [మొదటి ప్రాజెక్ట్ రెండవ పాఠం](./1-getting-started/lessons/2-deeper-dive/README.md) నే సమీక్షించవచ్చు.

విషేషమైన హార్డ్వేర్ పాఠాలు మరియు అసైన్మెంట్ల సంక్లిష్టతను తగ్గించడానికి ఎంచుకోబడింది. మరింత హార్డ్వేర్ పనిచేయవచ్చు కానీ అదనపు హార్డ్వేర్ లేకుండా మీ పరికరం మీద అన్ని అసైన్మెంట్లు ఆపాదించబడతాయన్న గ్యారెంటీ మేము ఇవ్వలేము. ఉదాహరణకు, చాలా Arduino పరికరాలకు WiFi ఉండదు, క్లౌడ్ కు కనెక్ట్ కావడానికి అది అవసరం - Wio terminal ఎందుకంటే దానిలో WiFi అంతర్నిర్మితంగా ఉంది.

మీకు కొద్దిగా నాన్-టెక్నికల్ వస్తువులు కూడా అవసరం అవుతాయి, ఉదా: నేల లేదా ఒక పావురం, మరియు పండ్లు లేదా కూరగాయలు.

## కిట్స్ కొనడం

![The Seeed studios logo](../../translated_images/te/seeed-logo.74732b6b482b6e8e.png)

Seeed స్టూడియోస్ ఎంతో అనుకూలంగా అన్ని హార్డ్వేర్ సులభంగా కొనుగోలుకు కిట్స్ రూపంలో అందుబాటులో ఉంచింది:

### Arduino - Wio Terminal

**[IoT for beginners with Seeed and Microsoft - Wio Terminal Starter Kit](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)**

[![The Wio Terminal hardware kit](../../translated_images/te/wio-hardware-kit.4c70c48b85e4283a.png)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)

### Raspberry Pi

**[IoT for beginners with Seeed and Microsoft - Raspberry Pi 4 Starter Kit](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)**

[![The Raspberry Pi Terminal hardware kit](../../translated_images/te/pi-hardware-kit.26dbadaedb7dd44c.png)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)

## Arduino

Arduino కోసం అన్ని పరికర కోడ్ C++ లో ఉంటాయి. అన్ని అసైన్మెంట్లు పూర్తి చేయడానికి మీరు క్రిందివి అవసరం:

### Arduino హార్డ్వేర్

* [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html)
* *ఐచ్ఛిక* - USB-C కేబుల్ లేదా USB-A నుండి USB-C అడాప్టర్. Wio terminal కి USB-C పోర్ట్ ఉంటుంది మరియు USB-C నుండి USB-A కేబుల్ తో వస్తుంది. మీ PC లేదా Mac లో USB-C పోర్ట్లు మాత్రమే ఉన్నట్లయితే USB-C కేబుల్ లేదా USB-A నుండి USB-C అడాప్టర్ అవసరం.

### Arduino ప్రత్యేక సెన్సార్లు మరియు యాక్చ్యుయేటర్లు

ఇవి Wio terminal Arduino పరికరం ఉపయోగించడానికిగాను ప్రత్యేకంగా ఉంటాయి, Raspberry Pi ఉపయోగించడానికే పెట్టుకోదగినవి కాదు.

* [ArduCam Mini 2MP Plus - OV2640](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/)
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)
* [బ్రెడ్డ్బోర్డ్ జంపర్ వైర్లు](https://www.seeedstudio.com/Breadboard-Jumper-Wire-Pack-241mm-200mm-160mm-117m-p-234.html)
* 3.5mm జాక్ ఉన్న హెడ్‌ఫోన్స్ లేదా ఇతర స్పీకర్ లేదా ఈ క్రింద ప్రత్యేకంగా:
  * [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
* 16GB లేదా తక్కువ మైక్రోSD కార్డ్ మరియు మీ కంప్యూటర్‌లో మౌంట్ చేసుకునేందుకు కనెక్టర్, మీరు పరికరంతో లేకపోతే. **గమనిక** - Wio Terminal 16GB వరకు SD కార్డులకు మాత్రమే మద్దతు ఇస్తుంది, పెద్ద కెపాసిటీలు మద్దతు ఇవ్వదు.

## Raspberry Pi

Raspberry Pi కోసం పరికర కోడ్ Python లో ఉంటుంది. అన్ని అసైన్మెంట్లు పూర్తి చేయడానికి మీరు క్రిందివి అవసరం:

### Raspberry Pi హార్డ్వేర్

* [Raspberry Pi](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/)
  > 💁 Pi 2B మరియు అంతక్రితం వెర్షన్లు ఈ పాఠాలలోని అసైన్మెంట్లకు పనిచేస్తాయి. మీరు Pi పైనే VS Code నేరుగా నడపాలని ఉంటే Pi 4 మరియు కనీసం 2GB RAM కావాలి. మీరు Pi ని దూరంగా యాక్సెస్ చేయాలనుకుంటే ఏ Pi 2B మరియు పై వెర్షన్ సరిపోతుంది.
* మైక్రోSD కార్డ్ (Raspberry Pi కిట్స్ మైక్రోSD కార్డు తో వస్తాయి), మీ కంప్యూటర్‌లో మౌంట్ చేసుకునేందుకు కనెక్టర్ అవసరం ఉండవచ్చు.
* USB పవర్ సరఫరా (Raspberry Pi 4 కిట్స్ పవర్ సరఫరా తో అందుబాటులో ఉంటాయి). Raspberry Pi 4 కి USB-C పవర్ సరఫరా అవసరం, పాత పరికరాలకు మైక్రో USB పవర్ సరఫరా కావాలి.

### Raspberry Pi ప్రత్యేక సెన్సార్లు మరియు యాక్చ్యుయేటర్లు

ఇవి Raspberry Pi ఉపయోగించడానికిగాను ప్రత్యేకంగా ఉంటాయి, Arduino పరికరం పని కి కాదు.

* [Grove Pi base hat](https://www.seeedstudio.com/Grove-Base-Hat-for-Raspberry-Pi.html)
* [Raspberry Pi కెమెరా మాడ్యూల్](https://www.raspberrypi.org/products/camera-module-v2/)
* మైక్రోఫోన్ మరియు స్పీకర్:

  కిందివి (లేదా సమానమైనవి) ఉపయోగించండి:
  * ఏ USB మైక్రోఫోన్ మరియు ఏ USB స్పీకర్, లేదా 3.5mm జాక్ కేబుల్ ఉన్న స్పీకర్ లేదా HDMI ఆడియో అవుట్పుట్ నుండి స్పీకర్స్ ఉన్న మానిటర్ లేదా TV కి కనెక్ట్ అయితే
  * ఏ USB హెడ్‌సెట్ మైక్రోఫోన్ తో కూడినది
  * [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) మరియు
    * 3.5mm జాక్ కలిగిన హెడ్‌ఫోన్స్ లేదా ఇతర స్పీకర్, లేదా ఈ క్రింది JST స్పీకర్:
    * [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
  * [USB Speakerphone](https://www.amazon.com/USB-Speakerphone-Conference-Business-Microphones/dp/B07Q3D7F8S/ref=sr_1_1?dchild=1&keywords=m0&qid=1614647389&sr=8-1)
* [Grove లైట్ సెన్సర్](https://www.seeedstudio.com/Grove-Light-Sensor-v1-2-LS06-S-phototransistor.html)
* [Grove బటన్](https://www.seeedstudio.com/Grove-Button.html)

## సెన్సార్లు మరియు యాక్చ్యుయేటర్లు

మొత్తం అవసరమైన సెన్సార్లు మరియు యాక్చ్యుయేటర్లు Arduino మరియు Raspberry Pi లెర్నింగ్ పాథ్స్ రెండింటి కోసం ఉపయోగించబడతాయి:

* [Grove LED](https://www.seeedstudio.com/Grove-LED-Pack-p-4364.html) x 2
* [Grove సാനి మరియు ఉష్ణోగ్రత సెన్సర్](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html)
* [Grove కెపాసిటివ్ సోయిల్ మాయిశ్చర్ సెన్సర్](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html)
* [Grove రీలా](https://www.seeedstudio.com/Grove-Relay.html)
* [Grove GPS (Air530)](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html)
* [Grove టైం ఆఫ్ ఫ్లైట్ డిస్టాన్స్ సెన్సర్](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html)

## ఐచ్ఛిక హార్డ్వేర్

స్వయంచాలక జలపాతం పాఠాలు రీలా ఉపయోగించి పనిచేస్తాయి. ఐచ్ఛికంగా, మీరు ఈ రీలాను USB పవర్ తో నడిచే వాటర్ పంప్ కు కనెక్ట్ చేయవచ్చు, క్రింద ఇచ్చిన హార్డ్వేర్ ఉపయోగించి.

* [6V వాటర్ పంప్](https://www.seeedstudio.com/6V-Mini-Water-Pump-p-1945.html)
* [USB టెర్మినల్](https://www.adafruit.com/product/3628)
* సిలికోన్ పైపులు
* ఎరుపు మరియు నలుపు వైర్లు
* చిన్న ఫ్లాట్-హెడ్ స్క్రూడ్రైవర్

## వర్చువల్ హార్డ్వేర్

వర్చువల్ హార్డ్వేర్ మార్గం సెన్సార్లు మరియు యాక్చ్యుయేటర్లకు సిమ్యులేటర్లను అందిస్తుంది, Python లో అమలు చేయబడుతుంది. మీ హార్డ్వేర్ అందుబాటుపై ఆధారపడి, మీరు మీ సాధారణ అభివృద్ధి పరికరంలెక్క (Mac, PC) లేక Raspberry Pi మీద నడిపించి మీరు లేని హార్డ్వేర్ మాత్రమే సిమ్యులేట్ చేయవచ్చు. ఉదాహరణకు, మీరు Raspberry Pi కెమెరా మరియు Grove సెన్సార్లు లేనట్లయితే, Pi మీద వర్చువల్ డివైస్ కోడ్ నడిపించి Grove సెన్సార్లను సిమ్యులేట్ చేయవచ్చు, కానీ ఫిజికల్ కెమెరా ఉపయోగించవచ్చు.

వర్చువల్ హార్డ్వేర్ [CounterFit ప్రాజెక్ట్](https://github.com/CounterFit-IoT/CounterFit) ను ఉపయోగిస్తుంది.

ఈ పాఠాలను పూర్తి చేయడానికి మీరు వెబ్ కెమ్, మైక్రోఫోన్ మరియు స్పీకర్స్ లేదా హెడ్‌ఫోన్స్ వంటి ఆడియో అవుట్పుట్ ఉండాలి. ఇవి అంతర్గతంగా లేదా బాహ్యంగా ఉండవచ్చు, మరియు మీ ఆపరేటింగ్ సిస్టమ్‌తో పని చేయడానికి కష్టతరం లేకుండా అన్ని యాప్లికేషన్లకు అందుబాటులో ఉండాలి.

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**హర్దిక అధికారం**:  
ఈ పత్రాన్ని AI అనువాద సేవ [Co-op Translator](https://github.com/Azure/co-op-translator) ద్వారా అనువదించబడింది. మేము సరైనత కోసం ప్రయత్నిస్తున్నప్పటికీ, స్వయంకృత అనువాదాలలో తప్పులు లేదా అస్పష్టతలు ఉండవచ్చు. మౌలిక పత్రం దాని స్వదేశీ భాషలో నమ్మకమైన మూలమైన అనుకూలంగా చూడాలి. ముఖ్యమైన సమాచారం కోసం, వ్యావసాయక మానవ అనువాదాన్ని సలహా ఇస్తాము. ఈ అనువాదం వాడకంతో సృష్టమైన ఏవైనా అపార్థాలు లేదా తప్పుగా అర్థం చేసుకోవడంపై మేము బాధ్యత తప్పించుకోని వాణిజ్యులు కావాలి.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->