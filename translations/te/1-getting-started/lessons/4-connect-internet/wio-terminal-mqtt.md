<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d6faf0e8d3c2d6d20c0aef2a305dab18",
  "translation_date": "2026-01-07T02:17:21+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md",
  "language_code": "te"
}
-->
# ఇంటర్నెట్ ద్వారా మీ నైట్‌లైట్‌ను నియంత్రించండి - Wio Terminal

IoT డివైస్‌ను *test.mosquitto.org* తో MQTT ఉపయోగించి టెలిమెట్రీ విలువలను లైట్ సెన్సార్ చదవడం ద్వారా పంపడానికి, మరియు LED ను నియంత్రించడానికి ఆదేశాలను స్వీకరించడానికి కోడ్ చేయాలి.

ఈ పాఠంలో, మీరు మీ Wio Terminal ను MQTT బ్రోకర్‌కు కనెక్ట్ చేస్తారు.

## WiFi మరియు MQTT Arduino లైబ్రరీలను ఇన్‌స్టాల్ చేయండి

MQTT బ్రోకర్‌తో కమ్యూనికేట్ చేయడానికి, మీరు Wio Terminal లో WiFi చిప్‌ను ఉపయోగించేందుకు మరియు MQTT తో కమ్యూనికేట్ చేయడానికి కొన్ని Arduino లైబ్రరీల‌ను ఇన్‌స్టాల్ చేయాల్సి ఉంటుంది. Arduino డివైసుల కోసం అభివృద్ధి చేస్తున్నప్పుడు, మీరు అనేక రకాల లైబ్రరీలను ఉపయోగించవచ్చు, అవి ఓపెన్-సోర్స్ కోడ్ కలిగి ఉండి విస్తృత శ్రేణి ఫంక్షనాలిటీని అమలు చేస్తాయి. Seeed Wio Terminal కోసం WiFi ద్వారా కమ్యూనికేట్ చేయడానికి లైబ్రరీలు విడుదల చేస్తుంది. MQTT బ్రోకర్లతో కమ్యూనికేట్ చేయడానికి ఇతర డెవలపర్లు లైబ్రరీలను అందించారు, మీరు అవి మీ డివైస్‌తో ఉపయోగిస్తారు.

ఈ లైబ్రరీలు సోర్స్ కోడ్‌గా ఉంటాయి, వీటిని PlatformIO లో ఆటోమేటిక్‌గా ఇంపోర్ట్ చేసి మీ డివైస్ కోసం కంపైల్ చేయవచ్చు. ఈ విధంగా Arduino లైబ్రరీలు, ఆ లైబ్రరీ అవసరం ఉన్న ప్రత్యేక హార్డ్‌వేర్ ఉన్న ఏదైనా డివైస్‌లో పని చేస్తాయి. Seeed WiFi లైబ్రరీలు కొన్ని ప్రత్యేక హార్డ్వేర్‌కు మాత్రమే ఉపయోగపడతాయి.

లైబ్రరీలను గ్లోబల్‌గా లేదా నిర్దిష్ట ప్రాజెక్టులో ఇన్‌స్టాల్ చేసి కంపైల్ చేయవచ్చు. ఈ అసైన్మెంట్ కోసం, లైబ్రరీలు ప్రాజెక్టులో ఇన్‌స్టాల్ చేయబడతాయి.

✅ మీరు లైబ్రరీ నిర్వహణ మరియు లైబ్రరీలను ఎలా కనుగొనాలి, ఇన్‌స్టాల్ చేయాలి అనే విషయం [PlatformIO లైబ్రరీ డాక్యుమెంటేషన్](https://docs.platformio.org/en/latest/librarymanager/index.html) లో మరింత నేర్చుకోవచ్చు.

### టాస్క్ - WiFi మరియు MQTT Arduino లైబ్రరీలను ఇన్‌స్టాల్ చేయండి

Arduino లైబ్రరీలను ఇన్‌స్టాల్ చేయండి.

1. VS Code లో నైట్‌లైట్ ప్రాజెక్ట్‌ను తెరవండి.

1. `platformio.ini` ఫైల్ చివరికి క్రింది కోడ్ జోడించండి:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
        seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
        seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    ```

    ఇది Seeed WiFi లైబ్రరీలను ఇంపోర్ట్ చేస్తుంది. `@ <number>` సింటాక్స్ లైబ్రరీ యొక్క నిర్దిష్ట వెర్షన్ నంబర్‌ను సూచిస్తుంది.

    > 💁 మీరు `@ <number>` తొలగించి లైబ్రరీల తాజా వెర్షన్లను ఎప్పుడూ ఉపయోగించుకోవచ్చు, కానీ ఈ కింద ఇచ్చిన కోడ్ తో బహుశా ఆ తరువాతి వెర్షన్లు పనిచేయకపోవచ్చు. ఇక్కడ ఇచ్చిన కోడ్ ఈ వెర్షన్ తో పరీక్షించబడింది.

    లైబ్రరీలను జోడించడానికి ఇది సరిపోతుంది. తదుపరి PlatformIO ప్రాజెక్ట్‌ను బిల్డ్ చేసినప్పుడు ఈ లైబ్రరీల సోర్స్ కోడ్ డౌన్లోడ్ చేసి ప్రాజెక్టుకు కంపైల్ చేస్తుంది.

1. `lib_deps` కి క్రింది కోడ్ జోడించండి:

    ```ini
    knolleary/PubSubClient @ 2.8
    ```

    ఇది [PubSubClient](https://github.com/knolleary/pubsubclient) అనే Arduino MQTT క్లయింట్ని ఇంపోర్ట్ చేస్తుంది.

## WiFi కి కనెక్ట్ అవ్వండి

Wio Terminal ఇప్పుడు WiFi కి కనెక్ట్ అవ్వచ్చు.

### టాస్క్ - WiFi కి కనెక్ట్ అవ్వండి

Wio Terminal ను WiFi కి కనెక్ట్ చేయండి.

1. `src` ఫోల్డర్ లో `config.h` అనే కొత్త ఫైల్ క్రియేట్ చేయండి. మీరు `src` ఫోల్డర్ లేదా దంతొ లో ఉన్న `main.cpp` ఫైల్ ఎంచుకొని ఎక్స్‌ప్లోరర్ నుండి **New file** బటన్ క్లిక్ చేయవచ్చు. ఇది కర్సర్ ఎక్స్‌ప్లోరర్ పై ఉండగానే కనిపిస్తుంది.

    ![The new file button](../../../../../translated_images/te/vscode-new-file-button.182702340fe6723c.png)

1. మీ WiFi క్రెడెన్షియల్స్ కోసం కాంస్టెంట్లను నిర్వచించడానికి ఈ ఫైల్ లో క్రింది కోడ్ జోడించండి:

    ```cpp
    #pragma once

    #include <string>
    
    using namespace std;
    
    // వైఫై స్ధిరాంకాలు
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    ```

    `<SSID>` స్థానంలో మీ WiFi SSID ని, `<PASSWORD>` స్థానంలో మీ WiFi పాస్‌వర్డ్ను 넣ండి.

1. `main.cpp` ఫైల్ తెరవండి

1. ఈ క్రింది `#include` డైరెక్టివ్‌లను ఫైల్ టాప్ కు జోడించండి:

    ```cpp
    #include <PubSubClient.h>
    #include <rpcWiFi.h>
    #include <SPI.h>
    
    #include "config.h"
    ```

    ఇది మీరు ముందుగా జోడించిన లైబ్రరీల కోసం మరియు config హెడ్డర్ ఫైల్ కోసం హెడ్డర్ ఫైల్స్ ను ఇంపోర్ట్ చేస్తుంది. PlatformIO కి ఈ లైబ్రరీల కోడ్ తీసుకురావడానికి ఇవి అవసరం. వీలైనన్ని హెడ్డర్ ఫైల్స్ లేకుండా కొన్ని కోడ్‌లను కంపైల్ చేయదు, అప్పుడు కంపైలర్ లో లోపాలు వస్తాయి.

1. `setup` ఫంక్షన్ కింద క్రింది కోడ్ జోడించండి:

    ```cpp
    void connectWiFi()
    {
        while (WiFi.status() != WL_CONNECTED)
        {
            Serial.println("Connecting to WiFi..");
            WiFi.begin(SSID, PASSWORD);
            delay(500);
        }
    
        Serial.println("Connected!");
    }
    ```

    ఇది డివైస్ WiFi కి కనెక్ట్ కాకపోయే వరకు లూప్ అవుతుంది, మరియు config హెడ్డర్ ఫైల్ నుంచి SSID మరియు పాస్‌వర్డ్ తో కనెక్ట్ అవ్వడానికి ప్రయత్నిస్తుంది.

1. ఈ ఫంక్షన్‌ను `setup` ఫంక్షన్ చివర, పిన్‌లను కాన్ఫిగర్ చేసిన తర్వాత కాల్ చేయండి.

    ```cpp
    connectWiFi();
    ```

1. WiFi కనెక్షన్ పని చేస్తుందో లేదో పరీక్షించడానికి ఈ కోడ్‌ను డివైస్‌కు అప్‌లోడ్ చేయండి. సీరియల్ మానిటర్ లో మీరు ఇది చూడవచ్చు.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    ```

## MQTT కి కనెక్ట్ అవ్వండి

Wio Terminal WiFi కి కనెక్ట్ అయిన తర్వాత, అది MQTT బ్రోకర్‌కు కనెక్ట్ అవ్వవచ్చు.

### టాస్క్ - MQTT కి కనెక్ట్ అవ్వండి

MQTT బ్రోకర్‌కు కనెక్ట్ చేయండి.

1. MQTT బ్రోకర్ కనెక్షన్ వివరాలు కోసం క్రింద కోడ్‌ను `config.h` ఫైల్ చివర జోడించండి:

    ```cpp
    // MQTT సెట్టింగులు
    const string ID = "<ID>";
    
    const string BROKER = "test.mosquitto.org";
    const string CLIENT_NAME = ID + "nightlight_client";
    ```

    `<ID>` స్థానంలో ఈ డివైస్ క్లయింట్‌కు ఉపయోగించే ప్రత్యేక ID ని పూరించండి, మరియు ఈ IDతోనే ఈ డివైస్ ప్రచురించే మరియు సబ్‌స్క్రయిబ్ చేసే టాపిǷల పేర్లను ఇస్తారు. *test.mosquitto.org* బ్రోకర్ పబ్లిక్‌గా అందుబాటులో ఉంది, చాలా మంది ఉపయోగిస్తారు, ఇతర విద్యార్థులు కూడా ఈ అసైన్‌మెంట్ ద్వారా పని చేస్తున్నారు. ప్రత్యేక MQTT క్లయింట్ పేరు మరియు టాపి పేర్లను ఉండటం ద్వారా మీ కోడ్ ఇతరుల కోడ్‌తో కొడుకుటం నివారిస్తుంది. మీరు ఈ IDని సర్వర్ కోడ్ తయారు చేస్తున్నప్పుడు కూడా ఉపయోగించాల్సి ఉంటుంది.

    > 💁 మీరు [GUIDGen](https://www.guidgen.com) వంటి వెబ్‌సైట్ ఉపయోగించి ప్రత్యేక ID కోరుకోవచ్చు.

    `BROKER` MQTT బ్రోకర్ యొక్క URL.

    `CLIENT_NAME` బ్రోకర్ పై ఈ MQTT క్లయింట్ కు ప్రత్యేకమైన పేరు.

1. `main.cpp` ఫైల్ తెరవండి, మరియు `connectWiFi` ఫంక్షన్ కింద, `setup` ఫంక్షన్ పై క్రింది కోడ్ జోడించండి:

    ```cpp
    WiFiClient wioClient;
    PubSubClient client(wioClient);
    ```

    ఈ కోడ్ Wio Terminal WiFi లైబ్రరీలు ఉపయోగించి WiFi క్లయింట్ సృష్టిస్తుంది మరియు దీన్ని ఉపయోగించి MQTT క్లయింట్ సృష్టిస్తుంది.

1. ఈ కోడ్‌ కింద క్రింది కోడ్ జతచేయండి:

    ```cpp
    void reconnectMQTTClient()
    {
        while (!client.connected())
        {
            Serial.print("Attempting MQTT connection...");
    
            if (client.connect(CLIENT_NAME.c_str()))
            {
                Serial.println("connected");
            }
            else
            {
                Serial.print("Retying in 5 seconds - failed, rc=");
                Serial.println(client.state());
                
                delay(5000);
            }
        }
    }
    ```

    ఈ ఫంక్షన్ MQTT బ్రోకర్ కనెక్షన్ టెస్టు చేస్తుంది మరియు కనెక్ట్ కాలేదు అయితే మళ్లీ కనెక్ట్ అవుతుంది. ఇది కనెక్ట్ కాకపోవడంతో పాటు ప్రయత్నిస్తూ ఉంటుంది, మరియు config హెడ్డర్ ఫైల్‌లో ఉన్న ప్రత్యేక క్లయింట్ పేరును ఉపయోగించి కనెక్ట్ అవుతుంది.

    కనెక్ట్ కాలేకపోతే, 5 సెకన్ల తర్వాత మళ్లీ ప్రయత్నిస్తుంది.

1. `reconnectMQTTClient` ఫంక్షన్ కింద క్రింది కోడ్ జతచేయండి:

    ```cpp
    void createMQTTClient()
    {
        client.setServer(BROKER.c_str(), 1883);
        reconnectMQTTClient();
    }
    ```

    ఈ కోడ్ MQTT బ్రోకర్ సెట్ చేస్తుంది, అలాగే సందేశం వచ్చినప్పుడు కాల్‌బ్యాక్ సెట్ చేస్తుంది. ఆపై బ్రోకర్ కు కనెక్ట్ కావడానికి ప్రయత్నిస్తుంది.

1. WiFi కనెక్టయిన తర్వాత `setup` ఫంక్షన్‌లో `createMQTTClient` ఫంక్షన్‌ను కాల్ చేయండి.

1. మొత్తం `loop` ఫంక్షన్‌ను క్రింద ఇచ్చిన కోడ్‌తో మార్చండి:

    ```cpp
    void loop()
    {
        reconnectMQTTClient();
        client.loop();
    
        delay(2000);
    }
    ```

    ఈ కోడ్ MQTT బ్రోకర్‌ను మళ్ళీ కనెక్ట్ చేస్తుంది. ఈ కనెక్షన్లు సులభంగా బద్దలవొచ్చు, కాబట్టి తరచుగా దగ్గరగా చూస్తూ అవసరమైతే మళ్లీ కనెక్ట్ అవ్వడం మేలు. ఆపై MQTT క్లయింట్ లోని `loop` పద్ధతిని పిలుస్తుంది, దీని వల్ల సబ్‌స్క్రైబ్ అయిన టాపిక్ పై వచ్చే సందేశాలను ప్రాసెస్ చేస్తుంది. ఈ యాప్ సింగిల్- త్రెడ్ గా ఉంటుంది కాబట్టి బ్యాక్‌గ్రౌండ్ త్రెడ్ లో సందేశాలు స్వీకరించలేరు, అందుచేత ప్రధాన త్రెడ్ కు సందేశ ప్రాసెసింగ్ కోసం సమయం కేటాయించాలి.

    చివరగా, 2 సెకన్ల ఆలస్యం ఉండటం వలన లైట్ స్థాయిలను ఎక్కువ సార్లు పంపకుండా చేస్తుంది మరియు డివైస్ యొక్క విద్యుత్ వినియోగం తగ్గిస్తుంది.

1. కోడ్‌ను మీ Wio Terminal కు అప్‌లోడ్ చేసి, సీరియల్ మానిటర్ ద్వారా డివైస్ WiFi మరియు MQTTకి కనెక్ట్ అవుతున్నదాన్ని చూడండి.

    ```output
    > Executing task: platformio device monitor <
    
    source /Users/jimbennett/GitHub/IoT-For-Beginners/1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal/nightlight/.venv/bin/activate
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    ```

> 💁 మీరు ఈ కోడ్‌ను [code-mqtt/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal) ఫోల్డర్ లో కనుగొనవచ్చు.

😀 మీరు విజయవంతంగా మీ డివైస్ ను MQTT బ్రోకర్‌కు కనెక్ట్ చేసారు.

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**త్యాగపత్రం**:
ఈ డాక్యుమెంట్ AI అనువాద సేవ [Co-op Translator](https://github.com/Azure/co-op-translator) ఉపయోగించి అనువదించబడింది. మేము ఖచ్చితత్వం కోసం ప్రయత్నించినప్పటికీ, స్వయంచాలక అనువాదాలలో పొరపాట్లు లేదా లోపాలు ఉండవచ్చు. స్థానిక భాషలో ఉన్న మూల డాక్యుమెంట్‌ను అధికారపు మూలంగా పరిగణించాలి. మిగులు సమాచారానికి, ప్రొఫెషనల్ మానవ అనువాదం సూచించబడుతుంది. ఈ అనువాదాన్ని ఉపయోగించడం వల్ల ఏవైనా తప్పుదోవలు లేదా తప్పుదెగ్గులు వస్తే మేము బాధ్యులు కము.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->