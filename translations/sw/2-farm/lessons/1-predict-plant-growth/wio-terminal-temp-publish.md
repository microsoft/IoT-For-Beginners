<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "df28cd649cd892bcce034e064913b2f3",
  "translation_date": "2025-08-27T23:20:09+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp-publish.md",
  "language_code": "sw"
}
-->
# Chapisha joto - Wio Terminal

Katika sehemu hii ya somo, utachapisha thamani za joto zilizogunduliwa na Wio Terminal kupitia MQTT ili ziweze kutumika baadaye kuhesabu GDD.

## Chapisha joto

Baada ya kusoma joto, linaweza kuchapishwa kupitia MQTT kwa 'server' fulani ya msimbo ambayo itasoma thamani hizo na kuzihifadhi tayari kutumika kwa hesabu ya GDD. Microcontrollers hazisomi muda kutoka kwenye mtandao na kufuatilia muda kwa saa halisi moja kwa moja, kifaa kinahitaji kupangwa kufanya hivyo, kwa kudhani kina vifaa vinavyohitajika.

Ili kurahisisha mambo kwa somo hili, muda hautatumwa pamoja na data ya sensa, badala yake unaweza kuongezwa na msimbo wa server baadaye unapopokea ujumbe.

### Kazi

Panga kifaa kuchapisha data ya joto.

1. Fungua mradi wa `temperature-sensor` wa Wio Terminal

1. Rudia hatua ulizofanya katika somo la 4 kuunganishwa na MQTT na kutuma telemetry. Utatumia broker wa Mosquitto wa umma ule ule.

    Hatua za kufanya hivi ni:

    - Ongeza maktaba za Seeed WiFi na MQTT kwenye faili `.ini`
    - Ongeza faili ya usanidi na msimbo wa kuunganishwa na WiFi
    - Ongeza msimbo wa kuunganishwa na broker wa MQTT
    - Ongeza msimbo wa kuchapisha telemetry

    > ⚠️ Rejelea [maelekezo ya kuunganishwa na MQTT](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md) na [maelekezo ya kutuma telemetry](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md) kutoka somo la 4 ikiwa inahitajika.

1. Hakikisha `CLIENT_NAME` katika faili ya kichwa `config.h` inaakisi mradi huu:

    ```cpp
    const string CLIENT_NAME = ID + "temperature_sensor_client";
    ```

1. Kwa telemetry, badala ya kutuma thamani ya mwanga, tuma thamani ya joto iliyosomwa kutoka sensa ya DHT katika mali kwenye hati ya JSON inayoitwa `temperature` kwa kubadilisha kazi ya `loop` katika `main.cpp`:

    ```cpp
    float temp_hum_val[2] = {0};
    dht.readTempAndHumidity(temp_hum_val);

    DynamicJsonDocument doc(1024);
    doc["temperature"] = temp_hum_val[1];
    ```

1. Thamani ya joto haitaji kusomwa mara kwa mara - haitabadilika sana kwa muda mfupi, kwa hivyo weka `delay` katika kazi ya `loop` kuwa dakika 10:

    ```cpp
    delay(10 * 60 * 1000);
    ```

    > 💁 Kazi ya `delay` inachukua muda kwa millisekunde, kwa hivyo ili iwe rahisi kusoma thamani inapitishwa kama matokeo ya hesabu. 1,000ms katika sekunde, 60s katika dakika, kwa hivyo 10 x (60s katika dakika) x (1000ms katika sekunde) inatoa kuchelewesha kwa dakika 10.

1. Pakia hii kwenye Wio Terminal yako, na tumia serial monitor kuona joto likitumwa kwa broker wa MQTT.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"temperature":25}
    Sending telemetry {"temperature":25}
    ```

> 💁 Unaweza kupata msimbo huu katika folda ya [code-publish-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/wio-terminal).

😀 Umefanikiwa kuchapisha joto kama telemetry kutoka kwa kifaa chako.

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya kutafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafadhali fahamu kuwa tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuzingatiwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.