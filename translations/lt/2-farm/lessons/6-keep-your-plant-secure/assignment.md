<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "34010c663d96d5f419eda6ac2366a78d",
  "translation_date": "2025-08-28T20:30:21+00:00",
  "source_file": "2-farm/lessons/6-keep-your-plant-secure/assignment.md",
  "language_code": "lt"
}
-->
# Sukurkite naują IoT įrenginį

## Instrukcijos

Per pastarąsias 6 pamokas sužinojote apie skaitmeninę žemdirbystę ir kaip naudoti IoT įrenginius duomenų rinkimui, siekiant prognozuoti augalų augimą bei automatizuoti laistymą pagal dirvožemio drėgmės rodmenis.

Pasinaudokite įgytomis žiniomis ir sukurkite naują IoT įrenginį, naudodami pasirinktą jutiklį ir pavarą. Siųskite telemetrijos duomenis į IoT Hub ir naudokite juos pavaros valdymui per serverio be kodo sprendimus. Galite naudoti jutiklį ir pavarą, kuriuos jau naudojote šiame ar ankstesniame projekte, arba, jei turite kitą techninę įrangą, išbandykite ką nors naujo.

## Vertinimo kriterijai

| Kriterijai | Puikiai | Pakankamai | Reikia tobulinti |
| ---------- | ------- | ---------- | ---------------- |
| Užprogramuoti IoT įrenginį, kad jis naudotų jutiklį ir pavarą | Užprogramuotas IoT įrenginys, kuris veikia su jutikliu ir pavara | Užprogramuotas IoT įrenginys, kuris veikia su jutikliu arba pavara | Nepavyko užprogramuoti IoT įrenginio, kad jis naudotų jutiklį ar pavarą |
| Prijungti IoT įrenginį prie IoT Hub | Pavyko sukurti IoT Hub, siųsti telemetrijos duomenis ir gauti komandas | Pavyko sukurti IoT Hub ir arba siųsti telemetrijos duomenis, arba gauti komandas | Nepavyko sukurti IoT Hub ir komunikuoti su juo iš IoT įrenginio |
| Valdyti pavarą naudojant serverio be kodo sprendimus | Pavyko sukurti Azure Function, kuri valdo įrenginį, aktyvuojama telemetrijos įvykių | Pavyko sukurti Azure Function, aktyvuojamą telemetrijos įvykių, bet nepavyko valdyti pavaros | Nepavyko sukurti Azure Function |

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama naudoti profesionalų žmogaus vertimą. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius dėl šio vertimo naudojimo.