<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0d55caa8c23d73635b7559102cd17b8a",
  "translation_date": "2026-01-07T05:02:19+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/wio-terminal-soil-moisture.md",
  "language_code": "te"
}
-->
# నేల తేమ కొలవండి - Wio టెర్మినల్

పాఠం యొక్క ఈ భాగంలో, మీరు మీ Wio టెర్మినల్‌కు ఒక కెపాసిటివ్ నేల తేమ సెన్సార్‌ను జోడించి, దాని నుండి విలువలను చదివిస్తారు.

## హార్డ్వేర్

Wio టెర్మినల్‌కు కెపాసిటివ్ నేల తేమ సెన్సార్ అవసరం.

మీరు ఉపయోగించబోయే సెన్సార్ ఒక [Capacitive Soil Moisture Sensor](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html), ఇది నేల తేమను నేల కెపాసిటెన్స్‌ను గుర్తించడం ద్వారా కొలుస్తుంది, ఇది నేల తేమ మార్పుతో పాటు మారే లక్షణం. నేల తేమ పెరిగే కొద్దీ వోల్టేజ్ తగ్గుతుంది.

ఇది ఒక యానలాగ్ సెన్సార్, కాబట్టి ఇది Wio టెర్మినల్‌పై అలనపడిన పిన్లతో కనెక్ట్ అవుతుంది, లోపలి ADC ను ఉపయోగించి 0-1,023 మధ్య విలువను సృష్టిస్తుంది.

### నేల తేమ సెన్సార్ కనెక్ట్ చేయండి

Grove నేల తేమ సెన్సార్‌ను Wio టెర్మినల్ యొక్క కన్ఫిగర్ చేయదగిన యానలాగ్/డిజిటల్ పోర్ట్‌కు కనెక్ట్ చేయవచ్చు.

#### టాస్క్ - నేల తేమ సెన్సార్ కనెక్ట్ చేయండి

నేల తేమ సెన్సార్‌ను కనెక్ట్ చేయండి.

![A grove soil moisture sensor](../../../../../translated_images/te/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78b.png)

1. Grove కేబుల్ యొక్క ఒక చివరను నేల తేమ సెన్సార్‌లోని సాకెట్‌లో ఇన్సర్ట్ చేయండి. ఇది ఒక్క దిశలో మాత్రమే ప్రవేశిస్తుంది.

1. Wio టెర్మినల్ ను మీ కంప్యూటర్ లేదా ఇతర పవర్ సరఫరా నుండి డిసి కనెక్ట్ చేసిన తర్వాత, Grove కేబుల్ యొక్క మర друга చివరను Wio టెర్మినల్ స్క్రీన్‌ను చూస్తున్నప్పుడు ఆ వలపు వైపు Grove సాకెట్‌కు కనెక్ట్ చేయండి. ఇది పవర్ బటన్ నుండి అత్యంత దూరమైన సాకెట్.

![The grove soil moisture sensor connected to the right hand socket](../../../../../translated_images/te/wio-soil-moisture-sensor.46919b61c3f6cb74.png)

1. నేల తేమ సెన్సార్‌ను నేలలో ఇన్సర్ట్ చేయండి. దీనికి 'అత్యధిక స్థానం లైన్' ఉంది - సెన్సార్ మీద తెల్లని రేఖ. ఈ రేఖ దాటకే సెన్సార్‌ని నురకండి.

![The grove soil moisture sensor in soil](../../../../../translated_images/te/soil-moisture-sensor-in-soil.bfad91002bda5e96.png)

1. ఇప్పుడు మీరు Wio టెర్మినల్‌ను మీ కంప్యూటర్‌కు కనెక్ట్ చేయవచ్చు.

## నేల తేమ సెన్సార్ కోసం ప్రోగ్రాం చేయండి

ఇప్పుడు Wio టెర్మినల్‌ని కనెక్ట్ చేసిన నేల తేమ సెన్సార్ ఉపయోగించడానికి ప్రోగ్రాం చేయవచ్చు.

### టాస్క్ - నేల తేమ సెన్సార్ ప్రోగ్రాం చేయండి

డివైస్‌ని ప్రోగ్రామ్ చేయండి.

1. PlatformIO ఉపయోగించి క్రొత్త Wio టెర్మినల్ ప్రాజెక్ట్ సృష్టించండి. ఈ ప్రాజెక్ట్ యొక్క పేరు `soil-moisture-sensor`. సీరియల్ పోర్ట్ ను కాన్ఫిగర్ చేయడానికి `setup` ఫంక్షన్‌లో కోడ్ చేర్చండి.

    > ⚠️ అవసరమైతే [project 1, lesson 1లో PlatformIO ప్రాజెక్ట్ ఎలా సృష్టించాలో ఉన్న సూచనలను చూడండి](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project).

1. ఈ సెన్సార్ కోసం ప్రత్యేక లైబ్రరీ లేదు, కానీ మీరు Arduino లో ఉన్న [`analogRead`](https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/) ఫంక్షన్ ఉపయోగించి యానలాగ్ పిన్ నుండి చదవవచ్చు. మొదట `setup` ఫంక్షన్‌లో యానలాగ్ పిన్‌ను ఇన్పుట్‌గా కాన్ఫిగర్ చేయండి కింద ఇవ్వబడిన కోడ్ తో:

    ```cpp
    pinMode(A0, INPUT);
    ```

    ఇది `A0` పిన్ - కాంబైన్డ్ యానలాగ్/డిజిటల్ పిన్ - ను వోల్టేజ్ చదవదగిన ఇన్పుట్ పిన్‌గా సెట్ చేస్తుంది.

1. ఈ పిన్ నుండి వోల్టేజ్ చదవడానికి `loop` ఫంక్షన్‌లో కిందివి చేర్చండి:

    ```cpp
    int soil_moisture = analogRead(A0);
    ```

1. ఈ కోడ్ క్రింద, విలువను సీరియల్ పోర్ట్ లో ప్రింట్ చేయడానికి కిందివి చేర్చండి:

    ```cpp
    Serial.print("Soil Moisture: ");
    Serial.println(soil_moisture);
    ```

1. చివరిగా 10 సెకన్ల డిలే జోడించండి:

    ```cpp
    delay(10000);
    ```

1. కోడ్‌ను కంపైల్ చేసి Wio టెర్మినల్‌కు అప్లోడ్ చేయండి.

    > ⚠️ అవసరమైతే [project 1, lesson 1లో PlatformIO ప్రాజెక్ట్ ఎలా సృష్టించాలో ఉన్న సూచనలను చూడండి](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app).

1. అప్లోడ్ అయిన తర్వాత, సీరియల్ మానిటర్ ఉపయోగించి నేల తేమను పరిశీలించవచ్చు. నేలకి కొంత నీరు పోసి లేదా సెన్సార్‌ను నేలనుండి తీసివేస్తే విలువ మారుతుంది చూడండి.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Soil Moisture: 526
    Soil Moisture: 529
    Soil Moisture: 521
    Soil Moisture: 494
    Soil Moisture: 454
    Soil Moisture: 456
    Soil Moisture: 395
    Soil Moisture: 388
    Soil Moisture: 394
    Soil Moisture: 391
    ```

    పై ఉదాహరణ అవుట్పుట్ లో, నీరు పోసినప్పుడు వోల్టేజ్ తగ్గడం ప్రతిభిస్తుంది.

> 💁 మీరు ఈ కోడ్‌ను [code/wio-terminal](../../../../../2-farm/lessons/2-detect-soil-moisture/code/wio-terminal) ఫోల్డర్లో కనుగొనవచ్చు.

😀 మీ నేల తేమ సెన్సార్ ప్రోగ్రాం విజయం సాధించింది!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**సమాచారం**:
ఈ డాక్యుమెంట్‌ను AI అనువాద సేవ [Co-op Translator](https://github.com/Azure/co-op-translator) ఉపయోగించి అనువదించబడింది. మేము ఖచ్చితత్వానికి ప్రయత్నించినప్పటికీ, ఆటోమేటెడ్ అనువాదాల్లో పొరబాట్లు లేదా తప్పిదాలు ఉండవచ్చును. మూల డాక్యుమెంట్ దాని స్థానిక భాషలో అధికారం కలిగిన మూలంగా పరిగణించాలి. కీలక సమాచారం కోసం, నిపుణుల చేత మానవ అనువాదాన్ని సలహా ఇస్తాము. ఈ అనువాదం వలన కలిగే ఏవైనా అవగాహన లోపాలు లేదా తప్ప فهمలు పట్ల మేము బాధ్యత వహించము.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->