<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "701f4a4466f9309b6e1d863077df0c06",
  "translation_date": "2025-10-11T12:16:44+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/assignment.md",
  "language_code": "et"
}
-->
# Ehita universaalne tõlkija

## Juhised

Universaalne tõlkija on seade, mis suudab tõlkida mitme keele vahel, võimaldades erinevaid keeli rääkivatel inimestel omavahel suhelda. Kasuta viimaste tundide jooksul õpitut, et ehitada universaalne tõlkija, kasutades kahte IoT-seadet.

> Kui sul pole kahte seadet, järgi eelmiste tundide samme, et seadistada virtuaalne IoT-seade ühe IoT-seadmena.

Sa peaksid seadistama ühe seadme ühe keele jaoks ja teise teise keele jaoks. Iga seade peaks aktsepteerima kõnet, teisendama selle tekstiks, saatma selle teisele seadmele IoT Hubi ja Functions rakenduse kaudu, seejärel tõlkima ja esitama tõlgitud kõne.

> 💁 Näpunäide: Kui saadad kõne ühelt seadmelt teisele, saada ka keel, milles see on, et tõlkimine oleks lihtsam. Võid isegi lasta igal seadmel registreeruda IoT Hubi ja Functions rakenduse kaudu, edastades toetatava keele, mis salvestatakse Azure Storage'is. Seejärel saad kasutada Functions rakendust tõlkimiseks, saates tõlgitud teksti IoT-seadmele.

## Hindamiskriteeriumid

| Kriteerium | Näidislik | Piisav | Vajab parandamist |
| ---------- | --------- | ------ | ----------------- |
| Universaalse tõlkija loomine | Suutis ehitada universaalse tõlkija, mis teisendab ühe seadme tuvastatud kõne teise seadme poolt esitatavaks kõneks teises keeles | Suutis mõne komponendi tööle panna, näiteks kõne salvestamise või tõlkimise, kuid ei suutnud luua terviklikku lahendust | Ei suutnud luua ühtegi töötavat universaalse tõlkija osa |

---

**Lahtiütlus**:  
See dokument on tõlgitud AI tõlketeenuse [Co-op Translator](https://github.com/Azure/co-op-translator) abil. Kuigi püüame tagada täpsust, palume arvestada, et automaatsed tõlked võivad sisaldada vigu või ebatäpsusi. Algne dokument selle algses keeles tuleks pidada autoriteetseks allikaks. Olulise teabe puhul soovitame kasutada professionaalset inimtõlget. Me ei vastuta selle tõlke kasutamisest tulenevate arusaamatuste või valesti tõlgenduste eest.