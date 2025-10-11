<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1a85e50c33c38dcd2cde2a97d132f248",
  "translation_date": "2025-10-11T11:53:44+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/assignment.md",
  "language_code": "et"
}
-->
# Ehita puuviljade kvaliteedi detektor

## Juhised

Ehita puuviljade kvaliteedi detektor!

Kasuta kõike, mida oled seni õppinud, et luua prototüüp puuviljade kvaliteedi detektorist. Käivita pildi klassifitseerimine lähedusanduri abil, kasutades serval töötavat AI-mudelit, salvesta klassifitseerimise tulemused andmehoidlasse ja juhi LED-tuld puuvilja küpsuse alusel.

Sa peaksid suutma selle kokku panna, kasutades koodi, mida oled seni kõigis õppetundides kirjutanud.

## Hindamiskriteeriumid

| Kriteerium | Näidislik | Piisav | Vajab parandamist |
| ---------- | --------- | ------ | ----------------- |
| Kõigi teenuste seadistamine | Suutis seadistada IoT Hubi, Azure Functions rakenduse ja Azure Storage'i | Suutis seadistada IoT Hubi, kuid mitte Azure Functions rakendust või Azure Storage'i | Ei suutnud seadistada ühtegi IoT-teenust |
| Lähedust jälgida ja saata andmed IoT Hubi, kui objekt on määratud kaugusest lähemal, ning käivitada kaamera käsu abil | Suutis mõõta kaugust ja saata sõnumi IoT Hubi, kui objekt oli piisavalt lähedal, ning saata käsu kaamera käivitamiseks | Suutis mõõta lähedust ja saata andmed IoT Hubi, kuid ei suutnud saata käsku kaamerale | Ei suutnud mõõta kaugust ega saata sõnumit IoT Hubi või käivitada käsku |
| Pildi jäädvustamine, klassifitseerimine ja tulemuste saatmine IoT Hubi | Suutis jäädvustada pildi, klassifitseerida selle servaseadme abil ja saata tulemused IoT Hubi | Suutis pildi klassifitseerida, kuid mitte servaseadme abil, või ei suutnud saata tulemusi IoT Hubi | Ei suutnud pilti klassifitseerida |
| LED-tule sisse- või väljalülitamine klassifitseerimise tulemuste alusel, kasutades seadmele saadetud käsku | Suutis LED-tule käsu abil sisse lülitada, kui puuvili oli toore | Suutis saata käsu seadmele, kuid ei suutnud LED-tuld juhtida | Ei suutnud saata käsku LED-tule juhtimiseks |

---

**Lahtiütlus**:  
See dokument on tõlgitud AI tõlketeenuse [Co-op Translator](https://github.com/Azure/co-op-translator) abil. Kuigi püüame tagada täpsust, palume arvestada, et automaatsed tõlked võivad sisaldada vigu või ebatäpsusi. Algne dokument selle algses keeles tuleks pidada autoriteetseks allikaks. Olulise teabe puhul soovitame kasutada professionaalset inimtõlget. Me ei vastuta selle tõlke kasutamisest tulenevate arusaamatuste või valesti tõlgenduste eest.