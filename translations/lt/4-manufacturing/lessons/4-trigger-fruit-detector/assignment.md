<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1a85e50c33c38dcd2cde2a97d132f248",
  "translation_date": "2025-08-28T19:03:33+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/assignment.md",
  "language_code": "lt"
}
-->
# Sukurkite vaisių kokybės detektorių

## Instrukcijos

Sukurkite vaisių kokybės detektorių!

Panaudokite viską, ko išmokote iki šiol, ir sukurkite prototipinį vaisių kokybės detektorių. Naudokite dirbtinio intelekto modelį, veikiantį krašte, kad klasifikuotumėte vaizdus pagal artumą, saugokite klasifikacijos rezultatus saugykloje ir valdykite LED lemputę pagal vaisiaus prinokimo lygį.

Turėtumėte sugebėti tai sudėlioti naudodami kodą, kurį rašėte per visas ankstesnes pamokas.

## Vertinimo kriterijai

| Kriterijai | Puikiai | Pakankamai | Reikia patobulinti |
| ---------- | ------- | ---------- | ------------------- |
| Suaktyvinti visas paslaugas | Gebėjo sukonfigūruoti IoT Hub, Azure funkcijų programą ir Azure saugyklą | Gebėjo sukonfigūruoti IoT Hub, bet ne Azure funkcijų programą ar Azure saugyklą | Nepavyko sukonfigūruoti jokių internetinių IoT paslaugų |
| Stebėti artumą ir siųsti duomenis į IoT Hub, jei objektas yra arčiau nei nustatytas atstumas, bei suaktyvinti kamerą komanda | Gebėjo išmatuoti atstumą, išsiųsti pranešimą į IoT Hub, kai objektas yra pakankamai arti, ir išsiųsti komandą kamerai suaktyvinti | Gebėjo išmatuoti artumą ir išsiųsti duomenis į IoT Hub, bet nepavyko išsiųsti komandos kamerai | Nepavyko išmatuoti atstumo, išsiųsti pranešimo į IoT Hub ar suaktyvinti komandos |
| Užfiksuoti vaizdą, jį klasifikuoti ir išsiųsti rezultatus į IoT Hub | Gebėjo užfiksuoti vaizdą, jį klasifikuoti naudodamas krašto įrenginį ir išsiųsti rezultatus į IoT Hub | Gebėjo klasifikuoti vaizdą, bet ne naudodamas krašto įrenginį, arba nepavyko išsiųsti rezultatų į IoT Hub | Nepavyko klasifikuoti vaizdo |
| Įjungti arba išjungti LED lemputę pagal klasifikacijos rezultatus, naudojant komandą, išsiųstą į įrenginį | Gebėjo įjungti LED lemputę komanda, jei vaisius buvo neprinokęs | Gebėjo išsiųsti komandą į įrenginį, bet nepavyko valdyti LED lemputės | Nepavyko išsiųsti komandos LED lemputei valdyti |

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, atkreipkite dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama profesionali žmogaus vertimo paslauga. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius naudojant šį vertimą.