<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "b2e0a965723082b068f735aec0faf3f6",
  "translation_date": "2025-08-28T19:49:31+00:00",
  "source_file": "3-transport/lessons/2-store-location-data/assignment.md",
  "language_code": "lt"
}
-->
# Ištirkite funkcijų susiejimus

## Instrukcijos

Funkcijų susiejimai leidžia jūsų kodui išsaugoti blob'us blob saugykloje, grąžinant juos iš `main` funkcijos. Azure saugyklos paskyra, kolekcija ir kitos detalės yra konfigūruojamos `function.json` faile.

Dirbant su Azure ar kitomis Microsoft technologijomis, geriausias informacijos šaltinis yra [Microsoft dokumentacija docs.com](https://docs.microsoft.com/?WT.mc_id=academic-17441-jabenn). Šioje užduotyje jums reikės perskaityti Azure Functions susiejimų dokumentaciją, kad suprastumėte, kaip nustatyti išvesties susiejimą.

Kai kurie puslapiai, kuriuos verta peržiūrėti pradžiai:

* [Azure Functions trigeriai ir susiejimų koncepcijos](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python)
* [Azure Blob saugyklos susiejimai Azure Functions apžvalga](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob?WT.mc_id=academic-17441-jabenn)
* [Azure Blob saugyklos išvesties susiejimas Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob-output?WT.mc_id=academic-17441-jabenn&tabs=python)

## Vertinimo kriterijai

| Kriterijai | Puikiai | Pakankamai | Reikia patobulinimų |
| ---------- | ------- | ---------- | ------------------- |
| Blob saugyklos išvesties susiejimo konfigūravimas | Gebėjo sukonfigūruoti išvesties susiejimą, grąžinti blob'ą ir sėkmingai jį išsaugoti blob saugykloje | Gebėjo sukonfigūruoti išvesties susiejimą arba grąžinti blob'ą, bet nesugebėjo sėkmingai jį išsaugoti blob saugykloje | Nepavyko sukonfigūruoti išvesties susiejimo |

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama profesionali žmogaus vertimo paslauga. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius dėl šio vertimo naudojimo.