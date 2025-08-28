<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "701f4a4466f9309b6e1d863077df0c06",
  "translation_date": "2025-08-28T09:30:40+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/assignment.md",
  "language_code": "sk"
}
-->
# Vytvorte univerzálny prekladač

## Pokyny

Univerzálny prekladač je zariadenie, ktoré dokáže prekladať medzi viacerými jazykmi, umožňujúc ľuďom hovoriacim rôznymi jazykmi komunikovať. Použite to, čo ste sa naučili počas posledných lekcií, na vytvorenie univerzálneho prekladača pomocou 2 IoT zariadení.

> Ak nemáte 2 zariadenia, postupujte podľa krokov z predchádzajúcich lekcií na nastavenie virtuálneho IoT zariadenia ako jedného z IoT zariadení.

Mali by ste nakonfigurovať jedno zariadenie pre jeden jazyk a druhé pre iný. Každé zariadenie by malo prijímať reč, konvertovať ju na text, posielať ju druhému zariadeniu cez IoT Hub a Functions aplikáciu, potom ju preložiť a prehrávať preloženú reč.

> 💁 Tip: Pri odosielaní reči z jedného zariadenia na druhé, pošlite aj informáciu o jazyku, v ktorom je reč, aby bolo jednoduchšie ju preložiť. Môžete dokonca nechať každé zariadenie zaregistrovať sa pomocou IoT Hub a Functions aplikácie, pričom odovzdá jazyk, ktorý podporuje, aby sa uložil do Azure Storage. Potom môžete použiť Functions aplikáciu na vykonanie prekladov a odoslanie preloženého textu do IoT zariadenia.

## Hodnotiace kritériá

| Kritérium | Vynikajúce | Dostatočné | Vyžaduje zlepšenie |
| --------- | ---------- | ---------- | ------------------ |
| Vytvorenie univerzálneho prekladača | Podarilo sa vytvoriť univerzálny prekladač, ktorý konvertuje reč detekovanú jedným zariadením na reč prehrávanú druhým zariadením v inom jazyku | Podarilo sa rozbehnúť niektoré komponenty, ako napríklad zachytávanie reči alebo prekladanie, ale nepodarilo sa vytvoriť kompletné riešenie | Nepodarilo sa vytvoriť žiadnu časť funkčného univerzálneho prekladača |

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby AI prekladu [Co-op Translator](https://github.com/Azure/co-op-translator). Hoci sa snažíme o presnosť, prosím, berte na vedomie, že automatizované preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho pôvodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nie sme zodpovední za akékoľvek nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.