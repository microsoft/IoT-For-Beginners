<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "b2e0a965723082b068f735aec0faf3f6",
  "translation_date": "2025-08-27T21:57:33+00:00",
  "source_file": "3-transport/lessons/2-store-location-data/assignment.md",
  "language_code": "hu"
}
-->
# Vizsgálja meg a függvénykötéseket

## Útmutató

A függvénykötések lehetővé teszik, hogy a kódja blobokat mentsen a blobtárhelyre azáltal, hogy azokat a `main` függvényből adja vissza. Az Azure Storage-fiók, a gyűjtemény és egyéb részletek a `function.json` fájlban vannak konfigurálva.

Amikor az Azure-ral vagy más Microsoft-technológiákkal dolgozik, a legjobb információforrás [a Microsoft dokumentációja a docs.com oldalon](https://docs.microsoft.com/?WT.mc_id=academic-17441-jabenn). Ebben a feladatban el kell olvasnia az Azure Functions kötési dokumentációját, hogy megtudja, hogyan állíthatja be a kimeneti kötést.

Néhány oldal, amelyeket érdemes megnézni a kezdéshez:

* [Azure Functions trigger- és kötési koncepciók](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python)
* [Azure Blob Storage kötés áttekintése az Azure Functions számára](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob?WT.mc_id=academic-17441-jabenn)
* [Azure Blob Storage kimeneti kötés az Azure Functions számára](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob-output?WT.mc_id=academic-17441-jabenn&tabs=python)

## Értékelési szempontok

| Kritérium | Kiváló | Megfelelő | Fejlesztésre szorul |
| --------- | ------- | --------- | ------------------- |
| A blobtárhely kimeneti kötésének konfigurálása | Sikerült konfigurálni a kimeneti kötést, visszaadni a blobot, és azt sikeresen elmenteni a blobtárhelyre | Sikerült konfigurálni a kimeneti kötést, vagy visszaadni a blobot, de nem sikerült azt elmenteni a blobtárhelyre | Nem sikerült konfigurálni a kimeneti kötést |

---

**Felelősségkizárás**:  
Ez a dokumentum az [Co-op Translator](https://github.com/Azure/co-op-translator) AI fordítási szolgáltatás segítségével készült. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt a professzionális, emberi fordítás igénybevétele. Nem vállalunk felelősséget a fordítás használatából eredő félreértésekért vagy téves értelmezésekért.