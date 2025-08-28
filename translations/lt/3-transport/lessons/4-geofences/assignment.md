<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5cb65a6ec4387ed177e145347e8e308e",
  "translation_date": "2025-08-28T19:42:39+00:00",
  "source_file": "3-transport/lessons/4-geofences/assignment.md",
  "language_code": "lt"
}
-->
# Siųsti pranešimus naudojant Twilio

## Instrukcijos

Jūsų kode iki šiol buvo tik registruojamas atstumas iki geografinės zonos. Šioje užduotyje turėsite pridėti pranešimą – tai gali būti tekstinė žinutė arba el. laiškas – kai GPS koordinatės yra geografinėje zonoje.

Azure Functions turi daug galimybių susieti su kitomis paslaugomis, įskaitant trečiųjų šalių paslaugas, tokias kaip Twilio – komunikacijos platforma.

* Užsiregistruokite nemokamai [Twilio.com](https://www.twilio.com)
* Perskaitykite dokumentaciją apie Azure Functions susiejimą su Twilio SMS [Microsoft dokumentacijos puslapyje apie Twilio susiejimą su Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-twilio?WT.mc_id=academic-17441-jabenn&tabs=python).
* Perskaitykite dokumentaciją apie Azure Functions susiejimą su Twilio SendGrid el. laiškų siuntimui [Microsoft dokumentacijos puslapyje apie Azure Functions SendGrid susiejimą](https://docs.microsoft.com/azure/azure-functions/functions-bindings-sendgrid?WT.mc_id=academic-17441-jabenn&tabs=python).
* Pridėkite susiejimą prie savo Functions programos, kad gautumėte pranešimą apie GPS koordinatės buvimą geografinėje zonoje arba už jos ribų – bet ne abiem atvejais.

## Vertinimo kriterijai

| Kriterijai | Puikiai | Pakankamai | Reikia patobulinimų |
| ---------- | ------- | ---------- | ------------------- |
| Funkcijų susiejimo konfigūravimas ir el. laiško arba SMS gavimas | Gebėjo sukonfigūruoti funkcijų susiejimą ir gauti el. laišką arba SMS, kai koordinatės yra geografinėje zonoje arba už jos ribų, bet ne abiem atvejais | Gebėjo sukonfigūruoti susiejimą, bet nesugebėjo išsiųsti el. laiško arba SMS, arba sugebėjo siųsti tik tada, kai koordinatės buvo ir geografinėje zonoje, ir už jos ribų | Nesugebėjo sukonfigūruoti susiejimo ir išsiųsti el. laiško arba SMS |

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama profesionali žmogaus vertimo paslauga. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius naudojant šį vertimą.