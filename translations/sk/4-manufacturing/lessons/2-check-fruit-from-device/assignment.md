# Reagovanie na výsledky klasifikácie

## Pokyny

Vaše zariadenie klasifikovalo obrázky a má hodnoty predpovedí. Toto zariadenie môže tieto informácie využiť na vykonanie nejakej akcie - môže ich odoslať do IoT Hubu na spracovanie inými systémami, alebo môže ovládať akčný člen, napríklad rozsvietiť LED diódu, keď je ovocie nezrelé.

Pridajte do svojho zariadenia kód, ktorý bude reagovať podľa vášho výberu - buď odošlite údaje do IoT Hubu, ovládajte akčný člen, alebo skombinujte oboje a odošlite údaje do IoT Hubu spolu s bezserverovým kódom, ktorý určí, či je ovocie zrelé alebo nie, a pošle späť príkaz na ovládanie akčného člena.

## Kritériá hodnotenia

| Kritérium | Vynikajúce | Dostatočné | Potrebuje zlepšenie |
| --------- | ---------- | ---------- | ------------------- |
| Reakcia na predpovede | Bol schopný implementovať reakciu na predpovede, ktorá konzistentne funguje s predpoveďami rovnakej hodnoty. | Bol schopný implementovať reakciu, ktorá nie je závislá od predpovedí, napríklad len odoslanie surových údajov do IoT Hubu. | Nebol schopný naprogramovať zariadenie tak, aby reagovalo na predpovede. |

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby AI prekladu [Co-op Translator](https://github.com/Azure/co-op-translator). Aj keď sa snažíme o presnosť, prosím, berte na vedomie, že automatizované preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho pôvodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nenesieme zodpovednosť za akékoľvek nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.