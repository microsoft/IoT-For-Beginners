<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "022e21f8629b721424c1de25195fff67",
  "translation_date": "2025-08-28T19:12:44+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/assignment.md",
  "language_code": "lt"
}
-->
# Atsakas į klasifikacijos rezultatus

## Instrukcijos

Jūsų įrenginys klasifikavo vaizdus ir turi prognozių reikšmes. Jūsų įrenginys gali naudoti šią informaciją tam tikriems veiksmams atlikti – pavyzdžiui, siųsti ją į „IoT Hub“, kad kitos sistemos galėtų apdoroti, arba valdyti vykdiklį, pavyzdžiui, įjungti LED lemputę, kai vaisius yra neprinokęs.

Pridėkite kodą savo įrenginyje, kad jis reaguotų jūsų pasirinktu būdu – arba siųstų duomenis į „IoT Hub“, valdytų vykdiklį, arba derintų abu būdus ir siųstų duomenis į „IoT Hub“ kartu su serverless kodu, kuris nustato, ar vaisius yra prinokęs, ir siunčia atgal komandą vykdikliui valdyti.

## Vertinimo kriterijai

| Kriterijai | Puikiai | Pakankamai | Reikia tobulinti |
| ---------- | ------- | ---------- | ---------------- |
| Atsakas į prognozes | Gebėjo įgyvendinti atsaką į prognozes, kuris nuosekliai veikia su tokiomis pačiomis prognozių reikšmėmis. | Gebėjo įgyvendinti atsaką, kuris nepriklauso nuo prognozių, pavyzdžiui, tiesiog siunčiant neapdorotus duomenis į „IoT Hub“. | Nepavyko užprogramuoti įrenginio, kad jis reaguotų į prognozes. |

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant dirbtinio intelekto vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, atkreipiame dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama naudoti profesionalų žmogaus vertimą. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus aiškinimus, kylančius dėl šio vertimo naudojimo.