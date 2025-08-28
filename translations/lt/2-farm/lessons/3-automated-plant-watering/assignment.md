<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "ed0fbd6aed084bfba7d5e2f206968c50",
  "translation_date": "2025-08-28T20:45:27+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/assignment.md",
  "language_code": "lt"
}
-->
# Sukurkite efektyvesnį laistymo ciklą

## Instrukcijos

Šioje pamokoje buvo aptarta, kaip valdyti relę naudojant jutiklio duomenis, o ta relė galėtų valdyti siurblį drėkinimo sistemai. Tam tikram dirvožemio kiekiui siurblio veikimas nustatytą laiką turėtų visada turėti tą patį poveikį dirvožemio drėgmei. Tai reiškia, kad galite apytiksliai nustatyti, kiek sekundžių drėkinimo atitinka tam tikrą dirvožemio drėgmės sumažėjimą. Naudodami šiuos duomenis galite sukurti labiau kontroliuojamą drėkinimo sistemą.

Šiai užduočiai turėsite apskaičiuoti, kiek laiko siurblys turėtų veikti, kad pasiektumėte tam tikrą dirvožemio drėgmės padidėjimą.

> ⚠️ Jei naudojate virtualią IoT įrangą, galite atlikti šį procesą, tačiau simuliuokite rezultatus rankiniu būdu padidindami dirvožemio drėgmės rodmenis fiksuotu kiekiu per sekundę, kai relė yra įjungta.

1. Pradėkite nuo sauso dirvožemio. Išmatuokite dirvožemio drėgmę.

1. Įpilkite fiksuotą vandens kiekį, arba paleisdami siurblį 1 sekundę, arba įpildami fiksuotą kiekį vandens.

    > Siurblys visada turėtų veikti pastoviu greičiu, todėl kiekvieną sekundę, kai siurblys veikia, jis turėtų tiekti tą patį vandens kiekį.

1. Palaukite, kol dirvožemio drėgmės lygis stabilizuosis, ir atlikite matavimą.

1. Pakartokite šį procesą kelis kartus ir sudarykite rezultatų lentelę. Pavyzdys pateiktas žemiau.

    | Bendras siurblio veikimo laikas | Dirvožemio drėgmė | Sumažėjimas |
    | --- | --: | -: |
    | Sausas | 643 |  0 |
    | 1s  | 621 | 22 |
    | 2s  | 601 | 20 |
    | 3s  | 579 | 22 |
    | 4s  | 560 | 19 |
    | 5s  | 539 | 21 |
    | 6s  | 521 | 18 |

1. Apskaičiuokite vidutinį dirvožemio drėgmės padidėjimą per sekundę vandens. Aukščiau pateiktame pavyzdyje kiekviena sekundė vandens sumažina rodmenį vidutiniškai 20,3.

1. Naudokite šiuos duomenis, kad pagerintumėte serverio kodo efektyvumą, paleisdami siurblį reikiamą laiką, kad dirvožemio drėgmė pasiektų norimą lygį.

## Vertinimo kriterijai

| Kriterijai | Puikiai | Pakankamai | Reikia patobulinimų |
| -------- | --------- | -------- | ----------------- |
| Dirvožemio drėgmės duomenų fiksavimas | Geba užfiksuoti kelis rodmenis po fiksuoto vandens kiekio pridėjimo | Geba užfiksuoti keletą rodmenų su fiksuotu vandens kiekiu | Geba užfiksuoti tik vieną ar du rodmenis arba negali naudoti fiksuoto vandens kiekio |
| Serverio kodo kalibravimas | Geba apskaičiuoti vidutinį dirvožemio drėgmės sumažėjimą ir atnaujinti serverio kodą, kad jis tai naudotų | Geba apskaičiuoti vidutinį sumažėjimą, bet negali atnaujinti serverio kodo, arba negali teisingai apskaičiuoti vidurkio, bet naudoja šią vertę teisingai atnaujindamas serverio kodą | Negali apskaičiuoti vidurkio arba atnaujinti serverio kodo |

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama profesionali žmogaus vertimo paslauga. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius naudojant šį vertimą.