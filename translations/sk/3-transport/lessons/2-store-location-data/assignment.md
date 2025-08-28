<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "b2e0a965723082b068f735aec0faf3f6",
  "translation_date": "2025-08-28T09:57:03+00:00",
  "source_file": "3-transport/lessons/2-store-location-data/assignment.md",
  "language_code": "sk"
}
-->
# Preskúmajte väzby funkcií

## Pokyny

Väzby funkcií umožňujú vášmu kódu ukladať blob objekty do úložiska blobov tým, že ich vrátite z funkcie `main`. Účet Azure Storage, kolekcia a ďalšie podrobnosti sú nakonfigurované v súbore `function.json`.

Pri práci s Azure alebo inými technológiami od Microsoftu je najlepším zdrojom informácií [dokumentácia Microsoftu na stránke docs.com](https://docs.microsoft.com/?WT.mc_id=academic-17441-jabenn). V tejto úlohe budete musieť preštudovať dokumentáciu o väzbách Azure Functions, aby ste zistili, ako nastaviť výstupnú väzbu.

Niektoré stránky, ktoré vám pomôžu začať, sú:

* [Koncepty spúšťačov a väzieb Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python)
* [Prehľad väzieb úložiska blobov pre Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob?WT.mc_id=academic-17441-jabenn)
* [Výstupná väzba úložiska blobov pre Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob-output?WT.mc_id=academic-17441-jabenn&tabs=python)

## Kritériá hodnotenia

| Kritérium | Vynikajúce | Dostatočné | Potrebuje zlepšenie |
| --------- | ---------- | ---------- | ------------------- |
| Nastavenie výstupnej väzby úložiska blobov | Podarilo sa nastaviť výstupnú väzbu, vrátiť blob a úspešne ho uložiť do úložiska blobov | Podarilo sa nastaviť výstupnú väzbu alebo vrátiť blob, ale nepodarilo sa ho úspešne uložiť do úložiska blobov | Nepodarilo sa nastaviť výstupnú väzbu |

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby AI prekladu [Co-op Translator](https://github.com/Azure/co-op-translator). Hoci sa snažíme o presnosť, prosím, berte na vedomie, že automatizované preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho rodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nenesieme zodpovednosť za akékoľvek nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.