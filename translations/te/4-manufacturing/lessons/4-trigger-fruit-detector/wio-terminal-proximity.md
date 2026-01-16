<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "288aebb0c59f7be1d2719b8f9660a313",
  "translation_date": "2026-01-07T07:11:13+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/wio-terminal-proximity.md",
  "language_code": "te"
}
-->
# సమీపాన్ని గుర్తించండి - Wio టెర్మినల్

పాఠం ఈ భాగంలో, మీరు మీ Wio టెర్మినల్‌కు సమీప సెన్సార్‌ను జోడించబోతున్నారు, మరియు దాని నుండి దూరాన్ని చదవబోతున్నారు.

## హార్డ్వేర్

Wio టెర్మినల్‌కు సమీప సెన్సార్ అవసరం.

మీరు ఉపయోగించబోయే సెన్సార్ ఒక [Grove టైమ్ ఆఫ్ ఫ్లైట్ దూర సెన్సార్](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html). ఈ సెన్సార్ దూరాన్ని గుర్తించడానికి లేజర్ రేంజింగ్ మాడ్యూల్‌ను ఉపయోగిస్తుంది. ఈ సెన్సార్ పరిధి 10mm నుండి 2000mm (1cm - 2m) వరకు ఉంది, మరియు ఆ పరిధిలోని విలువలను చాల ఖచ్చితంగా తెలియజేస్తుంది, 1000mm పైగా ఉండే దూరాలను 8109mmగా తెలియజేస్తుంది.

లేజర్ రేంజర్ సెన్సార్ వెనుక భాగంలో ఉంటుంది, Grove సాకెట్‌కు వ్యతిరేకంగా ఉన్న వైపు.

ఇది ఒక I<sup>2</sup>C సెన్సార్.

### టైమ్ ఆఫ్ ఫ్లైట్ సెన్సార్ కనెక్ట్ చేయండి

Grove టైమ్ ఆఫ్ ఫ్లైట్ సెన్సార్‌ను Wio టెర్మినల్‌కి కనెక్ట్ చేయవచ్చు.

#### టాస్క్ - టైమ్ ఆఫ్ ఫ్లైట్ సెన్సార్ కనెక్ట్ చేయండి

టైమ్ ఆఫ్ ఫ్లైట్ సెన్సార్ కనెక్ట్ చేయండి.

![A grove time of flight sensor](../../../../../translated_images/te/grove-time-of-flight-sensor.d82ff2165bfded9f.png)

1. Grove కేబుల్ ఒక అంచుని టైమ్ ఆఫ్ ఫ్లైట్ సెన్సార్ సాకెట్‌లో ఇన్సర్ట్ చేయండి. ఇది ఒక దిశలో మాత్రమే పోతుంది.

1. Wio టెర్మినల్ మీ కంప్యూటర్ లేదా ఇతర విద్యుత్ సరఫరా నుండి తొలగించినప్పుడు, Grove కేబుల్ యొక్క మరొక అంచుని Wio టెర్మినల్ స్క్రీన్ చూస్తున్నప్పుడు ఎడమవైపు Grove సాకెట్‌లో కనెక్ట్ చేయండి. ఇది పవర్ బటన్ కు దగ్గరగా ఉన్న సాకెట్. ఇది డిజిటల్ మరియు I<sup>2</sup>C సాకెట్ కలిపి ఉంది.

![The grove time of flight sensor connected to the left hand socket](../../../../../translated_images/te/wio-time-of-flight-sensor.c4c182131d2ea73d.png)

1. ఇప్పుడు మీరు Wio టెర్మినల్‌ను మీ కంప్యూటర్‌కు కనెక్ట్ చేయవచ్చు.

## టైమ్ ఆఫ్ ఫ్లైట్ సెన్సార్ ప్రోగ्राम చేయండి

Wio టెర్మినల్ ఇప్పుడు కనెక్ట్ చేసిన టైమ్ ఆఫ్ ఫ్లైట్ సెన్సార్ ఉపయోగించడానికి ప్రోగ్రామ్ చేయవచ్చు.

### టాస్క్ - టైమ్ ఆఫ్ ఫ్లైట్ సెన్సార్ ప్రోగ్రామ్ చేయండి

1. PlatformIO ఉపయోగించి ఒక కొత్త Wio టెర్మినల్ ప్రాజెక్ట్ సృష్టించండి. ఈ ప్రాజెక్ట్‌కు `distance-sensor` అని పేరుదీయండి. `setup` ఫంక్షన్‌లో సీరియల్ పోర్ట్‌ను కాన్ఫిగర్ చేయడానికి కోడ్ జత చేయండి.

1. ప్రాజెక్టుల `platformio.ini` ఫైల్‌లో Seeed Grove టైమ్ ఆఫ్ ఫ్లైట్ దూర సెన్సార్ లైబ్రరీకి లైబ్రరీ డిపెండెన్సీ జత చేయండి:

    ```ini
    lib_deps =
        seeed-studio/Grove Ranging sensor - VL53L0X @ ^1.1.1
    ```

1. `main.cpp` లో, టైమ్ ఆఫ్ ఫ్లైట్ సెన్సార్‌తో అంతరంగ చర్య చేయడానికి `Seeed_vl53l0x` క్లాస్ యొక్క ఒక ఇన్స్టెన్స్‌ని డిక్లేర్ చేయడానికి క్రింద ఇవ్వబడిన కోడ్‌ను_INCLUDED డైరెక్టివ్స్ తర్వాత జత చేయండి:

    ```cpp
    #include "Seeed_vl53l0x.h"
    
    Seeed_vl53l0x VL53L0X;
    ```

1. సెన్సార్ ప్రారంభించడానికి క్రింద ఇచ్చిన కోడ్‌ను `setup` ఫంక్షన్ చివరకు జత చేయండి:

    ```cpp
    VL53L0X.VL53L0X_common_init();
    VL53L0X.VL53L0X_high_accuracy_ranging_init();
    ```

1. `loop` ఫంక్షన్‌లో సెన్సార్ నుండి ఒక విలువ చదవండి:

    ```cpp
    VL53L0X_RangingMeasurementData_t RangingMeasurementData;
    memset(&RangingMeasurementData, 0, sizeof(VL53L0X_RangingMeasurementData_t));

    VL53L0X.PerformSingleRangingMeasurement(&RangingMeasurementData);
    ```

    ఈ కోడ్ ఒక డేటా స్ట్రక్చర్‌ను ప్రారంభించి, దానిలో డేటా చదవడానికి `PerformSingleRangingMeasurement` మెథడ్‌కు పంపుతుంది, అక్కడ దూరాన్ని కొలిచే మాపు పూరించబడుతుంది.

1. దీని దిగువ, దూరం కొలవడం వ్రాయండి, తరువాత 1 సెకను విరామం చేయండి:

    ```cpp
    Serial.print("Distance = ");
    Serial.print(RangingMeasurementData.RangeMilliMeter);
    Serial.println(" mm");

    delay(1000);
    ```

1. ఈ కోడ్‌ను కంబైల్ చేసి, అప్లోడ్ చేసి, అమలు చేయండి. సీరియల్ మానిటర్‌లో దూర కొలతలను చూడగలరా. సెన్సార్ వెచ్చని వస్తువులను ఉంచండి మరియు మీరు దూర కొలతను చూడగలరు:

    ```output
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    రేంజర్ సెన్సార్ వెనుక భాగంలో ఉన్నందున, దూరం కొలవేటప్పుడు సరైన వైపు ఉపయోగించండి.

    ![The rangefinder on the back of the time of flight sensor pointing at a banana](../../../../../translated_images/te/time-of-flight-banana.079921ad8b1496e4.png)

> 💁 మీరు ఈ కోడ్‌ను [code-proximity/wio-terminal](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/wio-terminal) ఫోల్డర్‌లో కనుగొనవచ్చు.

😀 మీ సమీప సెన్సార్ ప్రోగ్రాం విజయవంతమైంది!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**అస్పష్టత**:
ఈ పత్రం AI అనువాద సేవ అయిన [Co-op Translator](https://github.com/Azure/co-op-translator) ఉపయోగించి అనువదించబడింది. మేము ఖచ్చితత్వాన్ని లక్ష్యంగా పెట్టుకున్నప్పటికీ, ఆటోమేటెడ్ అనువాదాల్లో పొరపాట్లు లేదా తప్పులు ఉండొచ్చు అని దయచేసి గమనించండి. మౌలిక పత్రం ఆ స్వభావ భాషలోనే పరిపూర్ణమైన మరియు అధికారిక మూలంగా పరిగణించాలి. ముఖ్యమైన సమాచారం కోసం, నిపుణుల చేతి అనువాదం చేయించుకోవడమే ఉత్తమం. ఈ అనువాదం వాడకంవల్ల కలిగే ఏ పనిభ్రాంతులు లేదా అపర్థాలు కోసం మేము బాధ్యులు కావడంలేదు.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->