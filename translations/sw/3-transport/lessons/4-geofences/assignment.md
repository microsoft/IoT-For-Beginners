<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5cb65a6ec4387ed177e145347e8e308e",
  "translation_date": "2025-08-27T21:48:31+00:00",
  "source_file": "3-transport/lessons/4-geofences/assignment.md",
  "language_code": "sw"
}
-->
# Tuma Arifa kwa Kutumia Twilio

## Maelekezo

Katika msimbo wako hadi sasa, umekuwa ukirekodi tu umbali hadi kwenye geofence. Katika kazi hii, utahitaji kuongeza arifa, iwe ni ujumbe wa maandishi au barua pepe, wakati viwianishi vya GPS viko ndani ya geofence.

Azure Functions ina chaguo nyingi za bindings, ikijumuisha huduma za wahusika wa tatu kama Twilio, jukwaa la mawasiliano.

* Jisajili kwa akaunti ya bure kwenye [Twilio.com](https://www.twilio.com)
* Soma nyaraka kuhusu kuunganisha Azure Functions na Twilio SMS kwenye [ukurasa wa Microsoft docs Twilio binding for Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-twilio?WT.mc_id=academic-17441-jabenn&tabs=python).
* Soma nyaraka kuhusu kuunganisha Azure Functions na Twilio SendGrid ili kutuma barua pepe kwenye [ukurasa wa Microsoft docs Azure Functions SendGrid bindings](https://docs.microsoft.com/azure/azure-functions/functions-bindings-sendgrid?WT.mc_id=academic-17441-jabenn&tabs=python).
* Ongeza binding kwenye programu yako ya Functions ili kupokea arifa kuhusu viwianishi vya GPS vilivyo ndani au nje ya geofence - si vyote viwili.

## Rubric

| Vigezo | Bora Kabisa | Inaridhisha | Inahitaji Kuboresha |
| ------- | ----------- | ----------- | ------------------- |
| Sanidi bindings za functions na pokea barua pepe au SMS | Aliweza kusanidi bindings za functions na kupokea barua pepe au SMS wakati viwianishi viko ndani au nje ya geofence, lakini si vyote viwili | Aliweza kusanidi bindings lakini hakuweza kutuma barua pepe au SMS, au aliweza kutuma tu wakati viwianishi vilikuwa ndani na nje | Hakuweza kusanidi bindings na kutuma barua pepe au SMS |

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya tafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuchukuliwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.