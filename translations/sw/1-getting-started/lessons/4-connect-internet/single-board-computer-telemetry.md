<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1226517aae5f5b6f904434670394c688",
  "translation_date": "2025-08-27T22:12:49+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md",
  "language_code": "sw"
}
-->
# Dhibiti taa yako ya usiku kupitia Mtandao - Vifaa vya IoT vya Kawaida na Raspberry Pi

Katika sehemu hii ya somo, utatuma data ya telemetry na viwango vya mwanga kutoka kwa Raspberry Pi yako au kifaa cha IoT cha kawaida kwenda kwa broker wa MQTT.

## Tuma telemetry

Hatua inayofuata ni kuunda hati ya JSON yenye data ya telemetry na kuituma kwa broker wa MQTT.

### Kazi

Tuma telemetry kwa broker wa MQTT.

1. Fungua mradi wa taa ya usiku katika VS Code.

1. Ikiwa unatumia kifaa cha IoT cha kawaida, hakikisha terminal inaendesha mazingira ya kawaida. Ikiwa unatumia Raspberry Pi hautatumia mazingira ya kawaida.

1. Ongeza uingizaji ufuatao juu ya faili ya `app.py`:

    ```python
    import json
    ```

    Maktaba ya `json` inatumika kufunga data ya telemetry kama hati ya JSON.

1. Ongeza yafuatayo baada ya tamko la `client_name`:

    ```python
    client_telemetry_topic = id + '/telemetry'
    ```

    `client_telemetry_topic` ni mada ya MQTT ambayo kifaa kitachapisha viwango vya mwanga.

1. Badilisha yaliyomo ndani ya kitanzi cha `while True:` mwishoni mwa faili na yafuatayo:

    ```python
    while True:
        light = light_sensor.light
        telemetry = json.dumps({'light' : light})

        print("Sending telemetry ", telemetry)
    
        mqtt_client.publish(client_telemetry_topic, telemetry)
    
        time.sleep(5)
    ```

    Msimbo huu unafunga kiwango cha mwanga ndani ya hati ya JSON na kuichapisha kwa broker wa MQTT. Kisha unasubiri ili kupunguza marudio ya kutuma ujumbe.

1. Endesha msimbo kwa njia sawa na ulivyoendesha msimbo kutoka sehemu ya awali ya kazi. Ikiwa unatumia kifaa cha IoT cha kawaida, hakikisha programu ya CounterFit inaendesha na sensor ya mwanga na LED zimeundwa kwenye pini sahihi.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Sending telemetry  {"light": 0}
    Sending telemetry  {"light": 0}
    ```

> 💁 Unaweza kupata msimbo huu katika folda ya [code-telemetry/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/virtual-device) au folda ya [code-telemetry/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/pi).

😀 Umefanikiwa kutuma data ya telemetry kutoka kwa kifaa chako.

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya tafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuzingatiwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.