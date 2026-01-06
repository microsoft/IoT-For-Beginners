<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d6faf0e8d3c2d6d20c0aef2a305dab18",
  "translation_date": "2025-08-27T22:11:27+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md",
  "language_code": "sw"
}
-->
# Dhibiti taa yako ya usiku kupitia Mtandao - Wio Terminal

Kifaa cha IoT kinahitaji kuandikwa ili kuwasiliana na *test.mosquitto.org* kwa kutumia MQTT kutuma thamani za telemetry na kusoma sensa ya mwanga, na kupokea amri za kudhibiti LED.

Katika sehemu hii ya somo, utaunganisha Wio Terminal yako na broker ya MQTT.

## Sakinisha maktaba za WiFi na MQTT za Arduino

Ili kuwasiliana na broker ya MQTT, unahitaji kusakinisha maktaba za Arduino ili kutumia chip ya WiFi kwenye Wio Terminal, na kuwasiliana na MQTT. Unapokuwa unatengeneza kwa vifaa vya Arduino, unaweza kutumia anuwai ya maktaba zinazojumuisha msimbo wa chanzo wazi na kutekeleza uwezo mbalimbali. Seeed huchapisha maktaba kwa Wio Terminal inayoiwezesha kuwasiliana kupitia WiFi. Waendelezaji wengine wamechapisha maktaba za kuwasiliana na broker za MQTT, na utatumia hizi na kifaa chako.

Maktaba hizi zinatolewa kama msimbo wa chanzo ambao unaweza kuingizwa moja kwa moja kwenye PlatformIO na kuunganishwa kwa kifaa chako. Kwa njia hii, maktaba za Arduino zitafanya kazi kwenye kifaa chochote kinachounga mkono mfumo wa Arduino, mradi kifaa hicho kina vifaa maalum vinavyohitajika na maktaba hiyo. Baadhi ya maktaba, kama maktaba za Seeed WiFi, ni maalum kwa vifaa fulani.

Maktaba zinaweza kusakinishwa kimataifa na kuunganishwa ikiwa inahitajika, au kwenye mradi maalum. Kwa kazi hii, maktaba zitasakinishwa kwenye mradi.

✅ Unaweza kujifunza zaidi kuhusu usimamizi wa maktaba na jinsi ya kutafuta na kusakinisha maktaba katika [hati za maktaba za PlatformIO](https://docs.platformio.org/en/latest/librarymanager/index.html).

### Kazi - sakinisha maktaba za WiFi na MQTT za Arduino

Sakinisha maktaba za Arduino.

1. Fungua mradi wa nightlight kwenye VS Code.

1. Ongeza yafuatayo mwishoni mwa faili ya `platformio.ini`:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
        seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
        seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    ```

    Hii inaingiza maktaba za Seeed WiFi. Sintaksia ya `@ <number>` inarejelea namba maalum ya toleo la maktaba.

    > 💁 Unaweza kuondoa `@ <number>` ili kutumia toleo jipya zaidi la maktaba kila wakati, lakini hakuna uhakika kwamba matoleo ya baadaye yatafanya kazi na msimbo ulio hapa chini. Msimbo hapa umejaribiwa na toleo hili la maktaba.

    Hii ndiyo yote unayohitaji kufanya ili kuongeza maktaba. Wakati ujao PlatformIO itakapojenga mradi, itapakua msimbo wa chanzo wa maktaba hizi na kuziunganisha kwenye mradi wako.

1. Ongeza yafuatayo kwenye `lib_deps`:

    ```ini
    knolleary/PubSubClient @ 2.8
    ```

    Hii inaingiza [PubSubClient](https://github.com/knolleary/pubsubclient), mteja wa MQTT wa Arduino.

## Unganisha na WiFi

Sasa Wio Terminal inaweza kuunganishwa na WiFi.

### Kazi - unganisha na WiFi

Unganisha Wio Terminal na WiFi.

1. Unda faili mpya kwenye folda ya `src` inayoitwa `config.h`. Unaweza kufanya hivi kwa kuchagua folda ya `src`, au faili ya `main.cpp` ndani yake, na kuchagua kitufe cha **New file** kutoka kwa explorer. Kitufe hiki kinaonekana tu wakati mshale wako uko juu ya explorer.

    ![Kitufe cha faili mpya](../../../../../translated_images/vscode-new-file-button.182702340fe6723c.sw.png)

1. Ongeza msimbo ufuatao kwenye faili hii ili kufafanua constants za maelezo ya WiFi yako:

    ```cpp
    #pragma once

    #include <string>
    
    using namespace std;
    
    // WiFi credentials
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    ```

    Badilisha `<SSID>` na SSID ya WiFi yako. Badilisha `<PASSWORD>` na nenosiri la WiFi yako.

1. Fungua faili ya `main.cpp`.

1. Ongeza maagizo ya `#include` yafuatayo juu ya faili:

    ```cpp
    #include <PubSubClient.h>
    #include <rpcWiFi.h>
    #include <SPI.h>
    
    #include "config.h"
    ```

    Hii inaingiza faili za kichwa za maktaba ulizoongeza awali, pamoja na faili ya kichwa ya config. Faili hizi za kichwa zinahitajika ili kuambia PlatformIO kuleta msimbo kutoka kwa maktaba. Bila kuingiza faili hizi za kichwa waziwazi, baadhi ya msimbo hautaunganishwa na utapata makosa ya compiler.

1. Ongeza msimbo ufuatao juu ya kazi ya `setup`:

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

    Msimbo huu unazunguka wakati kifaa hakijaunganishwa na WiFi, na kujaribu kuunganishwa kwa kutumia SSID na nenosiri kutoka kwa faili ya kichwa ya config.

1. Ongeza mwito wa kazi hii chini ya kazi ya `setup`, baada ya pini kusanidiwa.

    ```cpp
    connectWiFi();
    ```

1. Pakia msimbo huu kwenye kifaa chako ili kuangalia kama muunganisho wa WiFi unafanya kazi. Unapaswa kuona hili kwenye monitor ya serial.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    ```

## Unganisha na MQTT

Mara Wio Terminal inapounganishwa na WiFi, inaweza kuunganishwa na broker ya MQTT.

### Kazi - unganisha na MQTT

Unganisha na broker ya MQTT.

1. Ongeza msimbo ufuatao chini ya faili ya `config.h` ili kufafanua maelezo ya muunganisho kwa broker ya MQTT:

    ```cpp
    // MQTT settings
    const string ID = "<ID>";
    
    const string BROKER = "test.mosquitto.org";
    const string CLIENT_NAME = ID + "nightlight_client";
    ```

    Badilisha `<ID>` na ID ya kipekee ambayo itatumika kama jina la mteja wa kifaa hiki, na baadaye kwa mada ambazo kifaa hiki kinachapisha na kujiunga nazo. Broker ya *test.mosquitto.org* ni ya umma na inatumiwa na watu wengi, ikiwa ni pamoja na wanafunzi wengine wanaofanya kazi kupitia kazi hii. Kuwa na jina la kipekee la mteja wa MQTT na majina ya mada huhakikisha msimbo wako hautagongana na wa mtu mwingine. Utahitaji pia ID hii unapounda msimbo wa seva baadaye katika kazi hii.

    > 💁 Unaweza kutumia tovuti kama [GUIDGen](https://www.guidgen.com) kutengeneza ID ya kipekee.

    `BROKER` ni URL ya broker ya MQTT.

    `CLIENT_NAME` ni jina la kipekee kwa mteja wa MQTT kwenye broker.

1. Fungua faili ya `main.cpp`, na ongeza msimbo ufuatao chini ya kazi ya `connectWiFi` na juu ya kazi ya `setup`:

    ```cpp
    WiFiClient wioClient;
    PubSubClient client(wioClient);
    ```

    Msimbo huu unaunda mteja wa WiFi kwa kutumia maktaba za WiFi za Wio Terminal na kuutumia kuunda mteja wa MQTT.

1. Chini ya msimbo huu, ongeza yafuatayo:

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

    Kazi hii inajaribu muunganisho na broker ya MQTT na kuunganisha tena ikiwa haijaunganishwa. Inazunguka wakati wote haijaunganishwa na inajaribu kuunganishwa kwa kutumia jina la kipekee la mteja lililofafanuliwa kwenye faili ya kichwa ya config.

    Ikiwa muunganisho unashindwa, inajaribu tena baada ya sekunde 5.

1. Ongeza msimbo ufuatao chini ya kazi ya `reconnectMQTTClient`:

    ```cpp
    void createMQTTClient()
    {
        client.setServer(BROKER.c_str(), 1883);
        reconnectMQTTClient();
    }
    ```

    Msimbo huu unaseti broker ya MQTT kwa mteja, pamoja na kusanidi callback wakati ujumbe unapokelewa. Kisha inajaribu kuunganishwa na broker.

1. Piga mwito wa kazi ya `createMQTTClient` kwenye kazi ya `setup` baada ya WiFi kuunganishwa.

1. Badilisha kazi nzima ya `loop` na yafuatayo:

    ```cpp
    void loop()
    {
        reconnectMQTTClient();
        client.loop();
    
        delay(2000);
    }
    ```

    Msimbo huu unaanza kwa kuunganisha tena na broker ya MQTT. Muunganisho huu unaweza kuvunjika kwa urahisi, kwa hivyo ni vyema kuangalia mara kwa mara na kuunganisha tena ikiwa inahitajika. Kisha inaita njia ya `loop` kwenye mteja wa MQTT ili kushughulikia ujumbe wowote unaokuja kwenye mada iliyosajiliwa. Programu hii ni ya thread moja, kwa hivyo ujumbe hauwezi kupokelewa kwenye thread ya nyuma, kwa hivyo muda kwenye thread kuu unahitaji kutengwa kwa kushughulikia ujumbe wowote unaosubiri kwenye muunganisho wa mtandao.

    Hatimaye, kuchelewesha kwa sekunde 2 kunahakikisha viwango vya mwanga havitumwi mara nyingi sana na kupunguza matumizi ya nguvu ya kifaa.

1. Pakia msimbo kwenye Wio Terminal yako, na tumia Serial Monitor kuona kifaa kikijiunga na WiFi na MQTT.

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

> 💁 Unaweza kupata msimbo huu katika [code-mqtt/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal) folda.

😀 Umefanikiwa kuunganisha kifaa chako na broker ya MQTT.

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya kutafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafadhali fahamu kuwa tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati asilia katika lugha yake ya awali inapaswa kuzingatiwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.