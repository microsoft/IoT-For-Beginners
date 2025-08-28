<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "b2e0a965723082b068f735aec0faf3f6",
  "translation_date": "2025-08-28T09:57:13+00:00",
  "source_file": "3-transport/lessons/2-store-location-data/assignment.md",
  "language_code": "ro"
}
-->
# Investigați legăturile funcțiilor

## Instrucțiuni

Legăturile funcțiilor permit codului dvs. să salveze blob-uri în stocarea de tip blob prin returnarea acestora din funcția `main`. Contul Azure Storage, colecția și alte detalii sunt configurate în fișierul `function.json`.

Când lucrați cu Azure sau alte tehnologii Microsoft, cea mai bună sursă de informații este [documentația Microsoft la docs.com](https://docs.microsoft.com/?WT.mc_id=academic-17441-jabenn). În această sarcină, va trebui să citiți documentația despre legăturile funcțiilor Azure pentru a înțelege cum să configurați legătura de ieșire.

Câteva pagini pe care să le consultați pentru a începe sunt:

* [Concepte despre declanșatori și legături în Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python)
* [Prezentare generală a legăturilor pentru stocarea de tip blob în Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob?WT.mc_id=academic-17441-jabenn)
* [Legătura de ieșire pentru stocarea de tip blob în Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob-output?WT.mc_id=academic-17441-jabenn&tabs=python)

## Criterii de evaluare

| Criteriu | Exemplară | Adecvată | Necesită îmbunătățiri |
| -------- | --------- | -------- | --------------------- |
| Configurarea legăturii de ieșire pentru stocarea de tip blob | A reușit să configureze legătura de ieșire, să returneze blob-ul și să îl stocheze cu succes în stocarea de tip blob | A reușit să configureze legătura de ieșire sau să returneze blob-ul, dar nu a reușit să îl stocheze cu succes în stocarea de tip blob | Nu a reușit să configureze legătura de ieșire |

---

**Declinare de responsabilitate**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să rețineți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa natală ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm responsabilitatea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.