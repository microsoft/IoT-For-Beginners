<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "b2e0a965723082b068f735aec0faf3f6",
  "translation_date": "2025-08-28T13:36:26+00:00",
  "source_file": "3-transport/lessons/2-store-location-data/assignment.md",
  "language_code": "hr"
}
-->
# Istraživanje vezivanja funkcija

## Upute

Vezivanje funkcija omogućuje vašem kodu spremanje blobova u blob pohranu vraćanjem iz funkcije `main`. Azure Storage račun, kolekcija i ostali detalji konfiguriraju se u datoteci `function.json`.

Kada radite s Azureom ili drugim Microsoftovim tehnologijama, najbolji izvor informacija je [Microsoftova dokumentacija na docs.com](https://docs.microsoft.com/?WT.mc_id=academic-17441-jabenn). U ovom zadatku trebat ćete pročitati dokumentaciju o vezivanju za Azure Functions kako biste naučili kako postaviti izlazno vezivanje.

Neke stranice koje možete pogledati za početak su:

* [Azure Functions: koncepti okidača i vezivanja](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python)
* [Pregled vezivanja za Azure Blob pohranu u Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob?WT.mc_id=academic-17441-jabenn)
* [Izlazno vezivanje za Azure Blob pohranu u Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob-output?WT.mc_id=academic-17441-jabenn&tabs=python)

## Rubrika

| Kriterij | Primjerno | Zadovoljavajuće | Potrebno poboljšanje |
| -------- | --------- | --------------- | --------------------- |
| Konfiguracija izlaznog vezivanja za blob pohranu | Uspješno konfigurirano izlazno vezivanje, vraćen blob i pohranjen u blob pohranu | Uspješno konfigurirano izlazno vezivanje ili vraćen blob, ali nije uspješno pohranjen u blob pohranu | Nije uspjelo konfigurirati izlazno vezivanje |

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane čovjeka. Ne preuzimamo odgovornost za nesporazume ili pogrešna tumačenja koja mogu proizaći iz korištenja ovog prijevoda.