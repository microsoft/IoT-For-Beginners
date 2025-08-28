<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "ed0fbd6aed084bfba7d5e2f206968c50",
  "translation_date": "2025-08-28T11:44:24+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/assignment.md",
  "language_code": "sk"
}
-->
# Vytvorte efektívnejší zavlažovací cyklus

## Pokyny

Táto lekcia sa zaoberala ovládaním relé pomocou údajov zo senzora, pričom toto relé môže ovládať čerpadlo pre zavlažovací systém. Pre definovaný objem pôdy by malo spustenie čerpadla na pevne stanovený čas vždy mať rovnaký vplyv na vlhkosť pôdy. To znamená, že si môžete vytvoriť predstavu o tom, koľko sekúnd zavlažovania zodpovedá určitému poklesu hodnoty vlhkosti pôdy. Pomocou týchto údajov môžete vytvoriť kontrolovanejší zavlažovací systém.

V tejto úlohe vypočítate, ako dlho by malo čerpadlo bežať, aby sa dosiahlo konkrétne zvýšenie vlhkosti pôdy.

> ⚠️ Ak používate virtuálny IoT hardvér, môžete tento proces prejsť, ale výsledky simulujte manuálnym zvýšením hodnoty vlhkosti pôdy o pevne stanovené množstvo za sekundu, keď je relé zapnuté.

1. Začnite so suchou pôdou. Zmerajte vlhkosť pôdy.

1. Pridajte pevné množstvo vody, buď spustením čerpadla na 1 sekundu, alebo naliatím pevného množstva vody.

    > Čerpadlo by malo vždy pracovať konštantnou rýchlosťou, takže každú sekundu, keď čerpadlo beží, by malo dodávať rovnaké množstvo vody.

1. Počkajte, kým sa úroveň vlhkosti pôdy stabilizuje, a odčítajte hodnotu.

1. Tento proces zopakujte viackrát a vytvorte tabuľku výsledkov. Príklad takejto tabuľky je uvedený nižšie.

    | Celkový čas čerpadla | Vlhkosť pôdy | Pokles |
    | --- | --: | -: |
    | Suché | 643 |  0 |
    | 1s  | 621 | 22 |
    | 2s  | 601 | 20 |
    | 3s  | 579 | 22 |
    | 4s  | 560 | 19 |
    | 5s  | 539 | 21 |
    | 6s  | 521 | 18 |

1. Vypočítajte priemerné zvýšenie vlhkosti pôdy za sekundu zavlažovania. V uvedenom príklade každá sekunda zavlažovania znižuje hodnotu o priemerne 20,3.

1. Použite tieto údaje na zlepšenie efektivity vášho serverového kódu, pričom čerpadlo bude bežať potrebný čas na dosiahnutie požadovanej úrovne vlhkosti pôdy.

## Kritériá hodnotenia

| Kritérium | Vynikajúce | Dostatočné | Potrebuje zlepšenie |
| --------- | ---------- | ---------- | ------------------- |
| Zaznamenanie údajov o vlhkosti pôdy | Dokáže zaznamenať viacero hodnôt po pridaní pevného množstva vody | Dokáže zaznamenať niektoré hodnoty s pevným množstvom vody | Dokáže zaznamenať len jednu alebo dve hodnoty, alebo nedokáže použiť pevné množstvo vody |
| Kalibrácia serverového kódu | Dokáže vypočítať priemerný pokles hodnoty vlhkosti pôdy a aktualizovať serverový kód na jeho použitie | Dokáže vypočítať priemerný pokles, ale nedokáže aktualizovať serverový kód, alebo nedokáže správne vypočítať priemer, ale použije túto hodnotu na správnu aktualizáciu serverového kódu | Nedokáže vypočítať priemer ani aktualizovať serverový kód |

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby AI prekladu [Co-op Translator](https://github.com/Azure/co-op-translator). Aj keď sa snažíme o presnosť, prosím, berte na vedomie, že automatizované preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho rodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nie sme zodpovední za akékoľvek nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.