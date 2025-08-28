<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "701f4a4466f9309b6e1d863077df0c06",
  "translation_date": "2025-08-28T19:34:21+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/assignment.md",
  "language_code": "lt"
}
-->
# Sukurkite universalų vertėją

## Instrukcijos

Universalus vertėjas yra įrenginys, galintis versti tarp kelių kalbų, leidžiantis žmonėms, kalbantiems skirtingomis kalbomis, bendrauti. Pasinaudokite tuo, ką išmokote per pastarąsias pamokas, kad sukurtumėte universalų vertėją naudodami 2 IoT įrenginius.

> Jei neturite 2 įrenginių, vadovaukitės ankstesnių pamokų žingsniais, kad sukurtumėte virtualų IoT įrenginį kaip vieną iš IoT įrenginių.

Turėtumėte sukonfigūruoti vieną įrenginį vienai kalbai, o kitą – kitai. Kiekvienas įrenginys turėtų priimti kalbą, paversti ją tekstu, išsiųsti kitam įrenginiui per IoT Hub ir Functions programėlę, tada išversti ir atkurti išverstą kalbą.

> 💁 Patarimas: Siųsdami kalbą iš vieno įrenginio į kitą, taip pat nurodykite, kokia kalba ji yra, kad būtų lengviau išversti. Galite netgi leisti kiekvienam įrenginiui užsiregistruoti naudojant IoT Hub ir Functions programėlę, perduodant palaikomą kalbą, kuri būtų saugoma Azure Storage. Tuomet galite naudoti Functions programėlę vertimams atlikti ir išverstą tekstą siųsti į IoT įrenginį.

## Vertinimo kriterijai

| Kriterijai | Puikiai | Pakankamai | Reikia patobulinimų |
| ---------- | ------- | ---------- | ------------------- |
| Sukurti universalų vertėją | Sukūrė universalų vertėją, kuris paverčia vieno įrenginio aptiktą kalbą į kito įrenginio atkuriamą kalbą kita kalba | Sukūrė kai kurias dalis, pvz., kalbos fiksavimą ar vertimą, bet nepavyko sukurti pilno sprendimo nuo pradžios iki galo | Nepavyko sukurti jokių veikiančių universalaus vertėjo dalių |

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant dirbtinio intelekto vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, atkreipiame dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama naudoti profesionalų žmogaus vertimą. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus aiškinimus, kylančius dėl šio vertimo naudojimo.