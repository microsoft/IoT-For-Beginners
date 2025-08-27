<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c527ce85d69b1a3875366ec61cbed8aa",
  "translation_date": "2025-08-27T22:13:15+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-commands.md",
  "language_code": "sw"
}
-->
# Dhibiti taa yako ya usiku kupitia Mtandao - Vifaa vya IoT vya Kijumlishi na Raspberry Pi

Katika sehemu hii ya somo, utajiandikisha kupokea amri zinazotumwa kutoka kwa MQTT broker kwenda kwa Raspberry Pi yako au kifaa chako cha IoT cha kijumlishi.

## Jiandikishe kwa amri

Hatua inayofuata ni kujiandikisha kupokea amri zinazotumwa kutoka kwa MQTT broker na kujibu amri hizo.

### Kazi

Jiandikishe kupokea amri.

1. Fungua mradi wa taa ya usiku kwenye VS Code.

1. Ikiwa unatumia kifaa cha IoT cha kijumlishi, hakikisha terminal inatumia mazingira ya kijumlishi. Ikiwa unatumia Raspberry Pi, hautatumia mazingira ya kijumlishi.

1. Ongeza msimbo ufuatao baada ya ufafanuzi wa `client_telemetry_topic`:

    ```python
    server_command_topic = id + '/commands'
    ```

    `server_command_topic` ni mada ya MQTT ambayo kifaa kitaandikisha ili kupokea amri za LED.

1. Ongeza msimbo ufuatao juu ya kitanzi kikuu, baada ya mstari wa `mqtt_client.loop_start()`:

    ```python
    def handle_command(client, userdata, message):
        payload = json.loads(message.payload.decode())
        print("Message received:", payload)
    
        if payload['led_on']:
            led.on()
        else:
            led.off()
    
    mqtt_client.subscribe(server_command_topic)
    mqtt_client.on_message = handle_command
    ```

    Msimbo huu unafafanua kazi, `handle_command`, inayosoma ujumbe kama hati ya JSON na kutafuta thamani ya mali ya `led_on`. Ikiwa imewekwa kuwa `True`, LED inawashwa, vinginevyo inazimwa.

    Mteja wa MQTT hujiandikisha kwenye mada ambayo seva itatuma ujumbe na huweka kazi ya `handle_command` kuitwa wakati ujumbe unapokelewa.

    > 💁 Kipangaji cha `on_message` huita kwa mada zote zilizoandikishwa. Ikiwa baadaye utaandika msimbo unaosikiliza mada nyingi, unaweza kupata mada ambayo ujumbe ulitumwa kutoka kwa kitu cha `message` kilichopitishwa kwa kazi ya kipangaji.

1. Endesha msimbo kwa njia ile ile kama ulivyoendesha msimbo kutoka sehemu ya awali ya kazi. Ikiwa unatumia kifaa cha IoT cha kijumlishi, hakikisha programu ya CounterFit inaendesha na sensor ya mwanga na LED zimeundwa kwenye pini sahihi.

1. Rekebisha viwango vya mwanga vinavyogunduliwa na kifaa chako halisi au cha kijumlishi. Ujumbe unaopokelewa na amri zinazotumwa zitaandikwa kwenye terminal. LED pia itawashwa na kuzimwa kulingana na kiwango cha mwanga.

> 💁 Unaweza kupata msimbo huu kwenye folda ya [code-commands/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/virtual-device) au folda ya [code-commands/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/pi).

😀 Umefanikiwa kuandika msimbo wa kifaa chako ili kujibu amri kutoka kwa MQTT broker.

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya kutafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafadhali fahamu kuwa tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuzingatiwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.