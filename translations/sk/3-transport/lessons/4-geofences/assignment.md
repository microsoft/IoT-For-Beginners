<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5cb65a6ec4387ed177e145347e8e308e",
  "translation_date": "2025-08-28T09:46:23+00:00",
  "source_file": "3-transport/lessons/4-geofences/assignment.md",
  "language_code": "sk"
}
-->
# Posielanie notifikácií pomocou Twilio

## Pokyny

Doteraz ste vo svojom kóde len zaznamenávali vzdialenosť od geozóny. V tejto úlohe budete musieť pridať notifikáciu, buď textovú správu alebo e-mail, keď sa GPS súradnice nachádzajú vo vnútri geozóny.

Azure Functions ponúka mnoho možností pre väzby, vrátane integrácie s externými službami, ako je Twilio, komunikačná platforma.

* Zaregistrujte si bezplatný účet na [Twilio.com](https://www.twilio.com)
* Prečítajte si dokumentáciu o väzbe Azure Functions na Twilio SMS na stránke [Microsoft docs Twilio binding for Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-twilio?WT.mc_id=academic-17441-jabenn&tabs=python).
* Prečítajte si dokumentáciu o väzbe Azure Functions na Twilio SendGrid na odosielanie e-mailov na stránke [Microsoft docs Azure Functions SendGrid bindings](https://docs.microsoft.com/azure/azure-functions/functions-bindings-sendgrid?WT.mc_id=academic-17441-jabenn&tabs=python).
* Pridajte väzbu do svojej aplikácie Functions, aby ste boli notifikovaní o GPS súradniciach buď vo vnútri alebo mimo geozóny - nie oboje.

## Hodnotiace kritériá

| Kritérium | Vynikajúce | Dostatočné | Vyžaduje zlepšenie |
| --------- | ---------- | ---------- | ------------------ |
| Konfigurácia väzieb funkcií a prijatie e-mailu alebo SMS | Podarilo sa nakonfigurovať väzby funkcií a prijímať e-mail alebo SMS, keď sú súradnice vo vnútri alebo mimo geozóny, ale nie oboje | Podarilo sa nakonfigurovať väzby, ale nepodarilo sa odoslať e-mail alebo SMS, alebo sa podarilo odoslať len v prípade, že sú súradnice vo vnútri aj mimo geozóny | Nepodarilo sa nakonfigurovať väzby a odoslať e-mail alebo SMS |

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby AI prekladu [Co-op Translator](https://github.com/Azure/co-op-translator). Aj keď sa snažíme o presnosť, upozorňujeme, že automatizované preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho pôvodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nezodpovedáme za akékoľvek nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.