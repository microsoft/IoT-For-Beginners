<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5a7262a0c48dfacdfe1ff91b20bf16fd",
  "translation_date": "2025-10-11T12:13:28+00:00",
  "source_file": "6-consumer/lessons/2-language-understanding/assignment.md",
  "language_code": "et"
}
-->
# Tühista taimer

## Juhised

Selles õppetükis oled seni õpetanud mudelit taimeri seadistamise mõistmiseks. Teine kasulik funktsioon on taimeri tühistamine - näiteks võib juhtuda, et leib on valmis ja saab ahjust välja võtta enne, kui taimer aegub.

Lisa oma LUIS rakendusse uus kavatsus taimeri tühistamiseks. Selle jaoks ei ole vaja mingeid entiteete, kuid on vaja mõningaid näitelauseid. Käsitle seda oma serverivabas koodis, kui see on peamine kavatsus, logides, et kavatsus tuvastati, ja tagastades sobiva vastuse.

## Hindamiskriteeriumid

| Kriteerium | Näidislik | Piisav | Vajab parandamist |
| ---------- | --------- | ------ | ----------------- |
| Lisa taimeri tühistamise kavatsus LUIS rakendusse | Kavatsus lisati ja mudel treeniti edukalt | Kavatsus lisati, kuid mudelit ei treenitud | Kavatsust ei õnnestunud lisada ega mudelit treenida |
| Käsitle kavatsust serverivabas rakenduses | Kavatsus tuvastati peamise kavatsusena ja logiti | Kavatsus tuvastati peamise kavatsusena | Kavatsust ei õnnestunud tuvastada peamise kavatsusena |

---

**Lahtiütlus**:  
See dokument on tõlgitud AI tõlketeenuse [Co-op Translator](https://github.com/Azure/co-op-translator) abil. Kuigi püüame tagada täpsust, palume arvestada, et automaatsed tõlked võivad sisaldada vigu või ebatäpsusi. Algne dokument selle algses keeles tuleks pidada autoriteetseks allikaks. Olulise teabe puhul soovitame kasutada professionaalset inimtõlget. Me ei vastuta selle tõlke kasutamisest tulenevate arusaamatuste või valesti tõlgenduste eest.