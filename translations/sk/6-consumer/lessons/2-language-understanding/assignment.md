<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5a7262a0c48dfacdfe1ff91b20bf16fd",
  "translation_date": "2025-08-28T08:56:01+00:00",
  "source_file": "6-consumer/lessons/2-language-understanding/assignment.md",
  "language_code": "sk"
}
-->
# Zrušiť časovač

## Pokyny

Doteraz ste v tejto lekcii vytrénovali model na pochopenie nastavenia časovača. Ďalšou užitočnou funkciou je zrušenie časovača - napríklad ak je váš chlieb hotový a môže byť vybraný z rúry pred uplynutím časovača.

Pridajte nový zámer do vašej LUIS aplikácie na zrušenie časovača. Nebude potrebovať žiadne entity, ale bude potrebovať niekoľko príkladových viet. Spracujte to vo vašom serverless kóde, ak je to hlavný zámer, zaznamenajte, že zámer bol rozpoznaný, a vráťte vhodnú odpoveď.

## Hodnotiace kritériá

| Kritérium | Vynikajúce | Dostatočné | Vyžaduje zlepšenie |
| --------- | ---------- | ---------- | ------------------ |
| Pridanie zámeru na zrušenie časovača do LUIS aplikácie | Podarilo sa pridať zámer a vytrénovať model | Podarilo sa pridať zámer, ale nie vytrénovať model | Nepodarilo sa pridať zámer a vytrénovať model |
| Spracovanie zámeru v serverless aplikácii | Podarilo sa rozpoznať zámer ako hlavný zámer a zaznamenať ho | Podarilo sa rozpoznať zámer ako hlavný zámer | Nepodarilo sa rozpoznať zámer ako hlavný zámer |

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby na automatický preklad [Co-op Translator](https://github.com/Azure/co-op-translator). Hoci sa snažíme o presnosť, upozorňujeme, že automatické preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho pôvodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nenesieme zodpovednosť za akékoľvek nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.