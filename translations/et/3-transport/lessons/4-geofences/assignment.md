<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5cb65a6ec4387ed177e145347e8e308e",
  "translation_date": "2025-10-11T11:56:40+00:00",
  "source_file": "3-transport/lessons/4-geofences/assignment.md",
  "language_code": "et"
}
-->
# Teavituste saatmine Twilio abil

## Juhised

Seni olete oma koodis lihtsalt loginud kaugust geopiirist. Selles ülesandes peate lisama teavituse, kas tekstisõnumi või e-kirja, kui GPS-koordinaadid asuvad geopiiri sees.

Azure Functions pakub mitmeid sidumisvõimalusi, sealhulgas kolmandate osapoolte teenustega nagu Twilio, mis on suhtlusplatvorm.

* Registreeruge tasuta kontole aadressil [Twilio.com](https://www.twilio.com)
* Lugege dokumentatsiooni Azure Functions'i sidumise kohta Twilio SMS-iga [Microsofti dokumentatsiooni lehelt Twilio binding for Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-twilio?WT.mc_id=academic-17441-jabenn&tabs=python).
* Lugege dokumentatsiooni Azure Functions'i sidumise kohta Twilio SendGridiga e-kirjade saatmiseks [Microsofti dokumentatsiooni lehelt Azure Functions SendGrid bindings](https://docs.microsoft.com/azure/azure-functions/functions-bindings-sendgrid?WT.mc_id=academic-17441-jabenn&tabs=python).
* Lisage sidumine oma Functions rakendusele, et saada teavitus GPS-koordinaatide kohta, mis asuvad kas geopiiri sees või väljas - mitte mõlemal juhul.

## Hindamiskriteeriumid

| Kriteerium | Silmapaistev | Piisav | Vajab parandamist |
| ---------- | ------------ | ------ | ----------------- |
| Funktsioonide sidumiste konfigureerimine ja e-kirja või SMS-i saamine | Oli võimeline konfigureerima funktsioonide sidumised ja saama e-kirja või SMS-i, kui koordinaadid olid geopiiri sees või väljas, kuid mitte mõlemal juhul | Oli võimeline sidumised konfigureerima, kuid ei suutnud e-kirja või SMS-i saata, või suutis saata ainult siis, kui koordinaadid olid nii sees kui ka väljas | Ei suutnud sidumisi konfigureerida ega e-kirja või SMS-i saata |

---

**Lahtiütlus**:  
See dokument on tõlgitud AI tõlketeenuse [Co-op Translator](https://github.com/Azure/co-op-translator) abil. Kuigi püüame tagada täpsust, palume arvestada, et automaatsed tõlked võivad sisaldada vigu või ebatäpsusi. Algne dokument selle algses keeles tuleks pidada autoriteetseks allikaks. Olulise teabe puhul soovitame kasutada professionaalset inimtõlget. Me ei vastuta selle tõlke kasutamisest tulenevate arusaamatuste või valesti tõlgenduste eest.