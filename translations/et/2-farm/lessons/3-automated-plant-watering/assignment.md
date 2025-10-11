<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "ed0fbd6aed084bfba7d5e2f206968c50",
  "translation_date": "2025-10-11T12:47:22+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/assignment.md",
  "language_code": "et"
}
-->
# Ehita tõhusam kastmistsükkel

## Juhised

Selles õppetükis käsitleti, kuidas juhtida releed sensori andmete abil, kus relee omakorda juhib pumpa niisutussüsteemis. Kindla pinnasekoguse puhul peaks pumba käivitamine kindla aja jooksul alati avaldama sama mõju pinnase niiskusele. See tähendab, et saate aimu, kui palju sekundeid niisutamist vastab teatud pinnase niiskuse näidu langusele. Kasutades neid andmeid, saate luua paremini kontrollitud niisutussüsteemi.

Selles ülesandes arvutate, kui kaua pump peaks töötama, et saavutada konkreetne pinnase niiskuse tõus.

> ⚠️ Kui kasutate virtuaalset IoT-riistvara, saate selle protsessi läbi teha, kuid simuleerige tulemusi, suurendades pinnase niiskuse näitu käsitsi kindla koguse võrra iga sekundi kohta, mil relee on sisse lülitatud.

1. Alustage kuiva pinnasega. Mõõtke pinnase niiskust.

1. Lisage kindel kogus vett, kas pumba käivitamisega 1 sekundiks või valades kindla koguse vett.

    > Pump peaks alati töötama ühtlase kiirusega, nii et iga sekund, mil pump töötab, peaks see tarnima sama koguse vett.

1. Oodake, kuni pinnase niiskuse tase stabiliseerub, ja tehke mõõtmine.

1. Korrake seda mitu korda ja looge tulemuste tabel. Näide tabelist on toodud allpool.

    | Pumba koguaeg | Pinnase niiskus | Langus |
    | --- | --: | -: |
    | Kuiv | 643 |  0 |
    | 1s  | 621 | 22 |
    | 2s  | 601 | 20 |
    | 3s  | 579 | 22 |
    | 4s  | 560 | 19 |
    | 5s  | 539 | 21 |
    | 6s  | 521 | 18 |

1. Arvutage keskmine pinnase niiskuse tõus iga sekundi kohta, mil vett lisatakse. Ülaltoodud näites vähendab iga sekundi jooksul lisatud vesi näitu keskmiselt 20,3 võrra.

1. Kasutage neid andmeid, et parandada oma serverikoodi efektiivsust, käivitades pumpa vajaliku aja, et viia pinnase niiskus soovitud tasemele.

## Hindamiskriteeriumid

| Kriteerium | Silmapaistev | Piisav | Vajab parandamist |
| -------- | --------- | -------- | ----------------- |
| Pinnase niiskuse andmete kogumine | Suudab koguda mitu mõõtmist pärast kindlate veekoguste lisamist | Suudab koguda mõningaid mõõtmisi kindlate veekoguste lisamisega | Suudab koguda ainult ühe või kaks mõõtmist või ei suuda kasutada kindlaid veekoguseid |
| Serverikoodi kalibreerimine | Suudab arvutada keskmise pinnase niiskuse näidu languse ja uuendada serverikoodi selle kasutamiseks | Suudab arvutada keskmise languse, kuid ei suuda serverikoodi uuendada, või ei suuda õigesti arvutada keskmist, kuid kasutab seda väärtust serverikoodi õigeks uuendamiseks | Ei suuda arvutada keskmist ega uuendada serverikoodi |

---

**Lahtiütlus**:  
See dokument on tõlgitud AI tõlketeenuse [Co-op Translator](https://github.com/Azure/co-op-translator) abil. Kuigi püüame tagada täpsust, palume arvestada, et automaatsed tõlked võivad sisaldada vigu või ebatäpsusi. Algne dokument selle algses keeles tuleks pidada autoriteetseks allikaks. Olulise teabe puhul soovitame kasutada professionaalset inimtõlget. Me ei vastuta selle tõlke kasutamisest tulenevate arusaamatuste või valesti tõlgenduste eest.