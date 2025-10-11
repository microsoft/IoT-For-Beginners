<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3764e089adf2d5801272bc0895f8498b",
  "translation_date": "2025-10-11T11:38:49+00:00",
  "source_file": "4-manufacturing/README.md",
  "language_code": "et"
}
-->
# Tootmine ja töötlemine – IoT kasutamine toidu töötlemise parandamiseks

Kui toit jõuab keskusesse või töötlemistehasesse, ei saadeta seda alati otse supermarketitesse. Sageli läbib toit mitmeid töötlemisetappe, näiteks kvaliteedi järgi sorteerimist. See oli varem käsitsi tehtav protsess – see algas põllul, kus korjajad valisid ainult küpsed viljad, ja tehases liikusid viljad konveierilindil, kus töötajad eemaldasid käsitsi muljutud või riknenud viljad. Kuna olen ise kooliajal suvetööna maasikaid korjanud ja sorteerinud, võin kinnitada, et see pole just meeldiv töö.

Kaasaegsemad süsteemid kasutavad sorteerimiseks IoT-d. Ühed varasemad seadmed, nagu [Weco](https://wecotek.com) sorteerijad, kasutavad optilisi sensoreid, et tuvastada toodangu kvaliteeti, näiteks roheliste tomatite tagasilükkamiseks. Neid saab kasutada nii farmides saagikoristuse ajal kui ka töötlemistehastes.

Kuna tehisintellekt (AI) ja masinõpe (ML) arenevad, muutuvad need masinad veelgi arenenumaks, kasutades ML-mudeleid, mis on treenitud eristama vilju ja võõrkehi, nagu kivid, mustus või putukad. Neid mudeleid saab treenida ka viljade kvaliteedi tuvastamiseks, mitte ainult muljutud viljade, vaid ka haiguste või muude saagiprobleemide varajaseks avastamiseks.

> 🎓 Termin *ML mudel* viitab masinõppe tarkvara treenimise tulemile andmekogumi põhjal. Näiteks saab treenida ML-mudelit eristama küpseid ja tooreid tomateid ning seejärel kasutada mudelit uute piltide analüüsimiseks, et näha, kas tomatid on küpsed või mitte.

Nendes 4 õppetunnis õpid, kuidas treenida pildipõhiseid AI-mudeleid viljade kvaliteedi tuvastamiseks, kuidas neid IoT-seadmes kasutada ja kuidas neid käitada lokaalselt – see tähendab IoT-seadmes, mitte pilves.

> 💁 Nendes õppetundides kasutatakse mõningaid pilveressursse. Kui sa ei lõpeta kõiki selle projekti õppetunde, veendu, et [koristad oma projekti](../clean-up.md).

## Teemad

1. [Treeni viljade kvaliteedi tuvastajat](./lessons/1-train-fruit-detector/README.md)
1. [Kontrolli viljade kvaliteeti IoT-seadmest](./lessons/2-check-fruit-from-device/README.md)
1. [Käivita viljade tuvastaja lokaalselt](./lessons/3-run-fruit-detector-edge/README.md)
1. [Käivita viljade kvaliteedi tuvastamine sensorilt](./lessons/4-trigger-fruit-detector/README.md)

## Autorid

Kõik õppetunnid on kirjutatud ♥️ poolt [Jen Fox](https://github.com/jenfoxbot) ja [Jim Bennett](https://GitHub.com/JimBobBennett)

---

**Lahtiütlus**:  
See dokument on tõlgitud AI tõlketeenuse [Co-op Translator](https://github.com/Azure/co-op-translator) abil. Kuigi püüame tagada täpsust, palume arvestada, et automaatsed tõlked võivad sisaldada vigu või ebatäpsusi. Algne dokument selle algses keeles tuleks pidada autoriteetseks allikaks. Olulise teabe puhul soovitame kasutada professionaalset inimtõlget. Me ei vastuta selle tõlke kasutamisest tulenevate arusaamatuste või valesti tõlgenduste eest.