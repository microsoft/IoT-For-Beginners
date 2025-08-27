<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "90fb93446e03c38f3c0e4009c2471906",
  "translation_date": "2025-08-27T22:14:22+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md",
  "language_code": "sw"
}
-->
# Dhibiti taa yako ya usiku kupitia Mtandao - Vifaa vya IoT vya Kijumlishi na Raspberry Pi

Kifaa cha IoT kinahitaji kuandikwa msimbo ili kuwasiliana na *test.mosquitto.org* kwa kutumia MQTT kutuma thamani za telemetry na kusoma kutoka kwa kihisi mwanga, na kupokea amri za kudhibiti LED.

Katika sehemu hii ya somo, utaunganisha Raspberry Pi yako au kifaa cha IoT cha kijumlishi na broker wa MQTT.

## Sakinisha kifurushi cha mteja wa MQTT

Ili kuwasiliana na broker wa MQTT, unahitaji kusakinisha maktaba ya MQTT kupitia kifurushi cha pip, iwe kwenye Pi yako au katika mazingira ya kijumlishi ikiwa unatumia kifaa cha kijumlishi.

### Kazi

Sakinisha kifurushi cha pip

1. Fungua mradi wa taa ya usiku katika VS Code.

1. Ikiwa unatumia kifaa cha IoT cha kijumlishi, hakikisha terminal inatumia mazingira ya kijumlishi. Ikiwa unatumia Raspberry Pi, hautatumia mazingira ya kijumlishi.

1. Endesha amri ifuatayo kusakinisha kifurushi cha pip cha MQTT:

    ```sh
    pip3 install paho-mqtt
    ```

## Andika msimbo wa kifaa

Kifaa kiko tayari kuandikwa msimbo.

### Kazi

Andika msimbo wa kifaa.

1. Ongeza uingizaji ufuatao juu ya faili ya `app.py`:

    ```python
    import paho.mqtt.client as mqtt
    ```

    Maktaba ya `paho.mqtt.client` inaruhusu programu yako kuwasiliana kupitia MQTT.

1. Ongeza msimbo ufuatao baada ya ufafanuzi wa kihisi mwanga na LED:

    ```python
    id = '<ID>'

    client_name = id + 'nightlight_client'
    ```

    Badilisha `<ID>` na kitambulisho cha kipekee ambacho kitakuwa jina la mteja wa kifaa hiki, na baadaye kwa mada ambazo kifaa hiki kitachapisha na kujiandikisha. Broker wa *test.mosquitto.org* ni wa umma na unatumika na watu wengi, ikiwa ni pamoja na wanafunzi wengine wanaofanya kazi kwenye kazi hii. Kuwa na jina la kipekee la mteja wa MQTT na majina ya mada huhakikisha msimbo wako hautagongana na wa mtu mwingine yeyote. Utahitaji pia kitambulisho hiki unapounda msimbo wa seva baadaye katika kazi hii.

    > 💁 Unaweza kutumia tovuti kama [GUIDGen](https://www.guidgen.com) kuzalisha kitambulisho cha kipekee.

    `client_name` ni jina la kipekee kwa mteja huyu wa MQTT kwenye broker.

1. Ongeza msimbo ufuatao chini ya msimbo huu mpya ili kuunda kitu cha mteja wa MQTT na kuunganisha na broker wa MQTT:

    ```python
    mqtt_client = mqtt.Client(client_name)
    mqtt_client.connect('test.mosquitto.org')
    
    mqtt_client.loop_start()

    print("MQTT connected!")
    ```

    Msimbo huu huunda kitu cha mteja, huunganisha na broker wa MQTT wa umma, na huanzisha mchakato wa kitanzi unaoendesha kwenye uzi wa nyuma kusikiliza ujumbe kwenye mada yoyote iliyosajiliwa.

1. Endesha msimbo kwa njia ile ile kama ulivyoendesha msimbo kutoka sehemu ya awali ya kazi. Ikiwa unatumia kifaa cha IoT cha kijumlishi, hakikisha programu ya CounterFit inaendesha na kihisi mwanga na LED vimeundwa kwenye pini sahihi.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Light level: 0
    Light level: 0
    ```

> 💁 Unaweza kupata msimbo huu katika folda ya [code-mqtt/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/virtual-device) au folda ya [code-mqtt/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/pi).

😀 Umefanikiwa kuunganisha kifaa chako na broker wa MQTT.

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya tafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafadhali fahamu kuwa tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuzingatiwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.