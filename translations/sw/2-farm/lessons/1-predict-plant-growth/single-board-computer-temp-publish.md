<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4efc74299e19f5d08f2f3f34451a11ba",
  "translation_date": "2025-08-27T23:21:20+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/single-board-computer-temp-publish.md",
  "language_code": "sw"
}
-->
# Chapisha joto - Vifaa vya Virtual IoT na Raspberry Pi

Katika sehemu hii ya somo, utachapisha thamani za joto zilizogunduliwa na Raspberry Pi au Kifaa cha Virtual IoT kupitia MQTT ili ziweze kutumika baadaye kuhesabu GDD.

## Chapisha joto

Baada ya kusoma joto, linaweza kuchapishwa kupitia MQTT kwa 'server' fulani ya msimbo ambayo itasoma thamani hizo na kuzihifadhi tayari kutumika kwa hesabu ya GDD.

### Kazi - chapisha joto

Programu kifaa ili kuchapisha data ya joto.

1. Fungua mradi wa programu ya `temperature-sensor` ikiwa haujafunguliwa tayari.

1. Rudia hatua ulizofanya katika somo la 4 kuunganishwa na MQTT na kutuma telemetry. Utatumia broker wa Mosquitto wa umma ule ule.

    Hatua za kufanya hivi ni:

    - Ongeza pakiti ya pip ya MQTT
    - Ongeza msimbo wa kuunganishwa na broker wa MQTT
    - Ongeza msimbo wa kuchapisha telemetry

    > ⚠️ Rejelea [maelekezo ya kuunganishwa na MQTT](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md) na [maelekezo ya kutuma telemetry](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md) kutoka somo la 4 ikiwa inahitajika.

1. Hakikisha `client_name` inaakisi jina la mradi huu:

    ```python
    client_name = id + 'temperature_sensor_client'
    ```

1. Kwa telemetry, badala ya kutuma thamani ya mwanga, tuma thamani ya joto iliyosomwa kutoka kwa sensa ya DHT katika mali kwenye hati ya JSON inayoitwa `temperature`:

    ```python
    _, temp = sensor.read()
    telemetry = json.dumps({'temperature' : temp})
    ```

1. Thamani ya joto haitaji kusomwa mara kwa mara - haitabadilika sana kwa muda mfupi, kwa hivyo weka `time.sleep` kwa dakika 10:

    ```cpp
    time.sleep(10 * 60);
    ```

    > 💁 Kazi ya `sleep` inachukua muda kwa sekunde, kwa hivyo ili iwe rahisi kusoma thamani inapitishwa kama matokeo ya hesabu. Sekunde 60 kwa dakika, kwa hivyo 10 x (sekunde 60 kwa dakika) inatoa muda wa kuchelewa wa dakika 10.

1. Endesha msimbo kwa njia ile ile ulivyoendesha msimbo kutoka sehemu ya awali ya kazi. Ikiwa unatumia kifaa cha Virtual IoT, hakikisha programu ya CounterFit inaendesha na sensa za unyevu na joto zimeundwa kwenye pini sahihi.

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py
    MQTT connected!
    Sending telemetry  {"temperature": 25}
    Sending telemetry  {"temperature": 25}
    ```

> 💁 Unaweza kupata msimbo huu katika folda ya [code-publish-temperature/virtual-device](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/virtual-device) au folda ya [code-publish-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/pi).

😀 Umefanikiwa kuchapisha joto kama telemetry kutoka kwa kifaa chako.

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya tafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuzingatiwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.