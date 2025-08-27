<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "b2e0a965723082b068f735aec0faf3f6",
  "translation_date": "2025-08-27T21:57:44+00:00",
  "source_file": "3-transport/lessons/2-store-location-data/assignment.md",
  "language_code": "cs"
}
-->
# Prozkoumejte vazby funkcí

## Pokyny

Vazby funkcí umožňují vašemu kódu ukládat blob objekty do úložiště blobů tím, že je vrátíte z funkce `main`. Účet Azure Storage, kolekce a další podrobnosti jsou nakonfigurovány v souboru `function.json`.

Při práci s Azure nebo jinými technologiemi Microsoftu je nejlepším zdrojem informací [dokumentace Microsoftu na docs.com](https://docs.microsoft.com/?WT.mc_id=academic-17441-jabenn). V tomto úkolu budete muset přečíst dokumentaci k vazbám funkcí Azure, abyste zjistili, jak nastavit výstupní vazbu.

Některé stránky, které vám mohou pomoci začít, jsou:

* [Koncepty triggerů a vazeb funkcí Azure](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python)
* [Přehled vazeb úložiště blobů pro funkce Azure](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob?WT.mc_id=academic-17441-jabenn)
* [Výstupní vazba úložiště blobů pro funkce Azure](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob-output?WT.mc_id=academic-17441-jabenn&tabs=python)

## Hodnocení

| Kritéria | Vynikající | Přiměřené | Vyžaduje zlepšení |
| -------- | ---------- | --------- | ----------------- |
| Nastavení výstupní vazby úložiště blobů | Bylo možné nastavit výstupní vazbu, vrátit blob a úspěšně jej uložit do úložiště blobů | Bylo možné nastavit výstupní vazbu nebo vrátit blob, ale nebylo možné jej úspěšně uložit do úložiště blobů | Nebylo možné nastavit výstupní vazbu |

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). I když se snažíme o přesnost, mějte na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace se doporučuje profesionální lidský překlad. Neodpovídáme za žádné nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.