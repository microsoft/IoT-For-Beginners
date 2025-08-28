<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "34010c663d96d5f419eda6ac2366a78d",
  "translation_date": "2025-08-28T11:18:23+00:00",
  "source_file": "2-farm/lessons/6-keep-your-plant-secure/assignment.md",
  "language_code": "sk"
}
-->
# Vytvorte nové IoT zariadenie

## Pokyny

Počas posledných 6 lekcií ste sa naučili o digitálnom poľnohospodárstve a o tom, ako používať IoT zariadenia na zhromažďovanie údajov na predpovedanie rastu rastlín a automatizáciu zavlažovania na základe údajov o vlhkosti pôdy.

Využite to, čo ste sa naučili, na vytvorenie nového IoT zariadenia pomocou senzora a aktuátora podľa vášho výberu. Posielajte telemetriu do IoT Hubu a použite ju na ovládanie aktuátora prostredníctvom bezserverového kódu. Môžete použiť senzor a aktuátor, ktoré ste už použili v tomto alebo predchádzajúcom projekte, alebo ak máte iný hardvér, vyskúšajte niečo nové.

## Hodnotiace kritériá

| Kritérium | Vynikajúce | Dostatočné | Vyžaduje zlepšenie |
| --------- | ---------- | ---------- | ------------------ |
| Naprogramovať IoT zariadenie na použitie senzora a aktuátora | Naprogramované IoT zariadenie, ktoré funguje so senzorom a aktuátorom | Naprogramované IoT zariadenie, ktoré funguje so senzorom alebo aktuátorom | Nebolo možné naprogramovať IoT zariadenie na použitie senzora alebo aktuátora |
| Pripojiť IoT zariadenie k IoT Hubu | Podarilo sa nasadiť IoT Hub, posielať do neho telemetriu a prijímať príkazy | Podarilo sa nasadiť IoT Hub a buď posielať telemetriu, alebo prijímať príkazy | Nebolo možné nasadiť IoT Hub a komunikovať s ním z IoT zariadenia |
| Ovládať aktuátor pomocou bezserverového kódu | Podarilo sa nasadiť Azure Function na ovládanie zariadenia spusteného telemetrickými udalosťami | Podarilo sa nasadiť Azure Function spustenú telemetrickými udalosťami, ale nebolo možné ovládať aktuátor | Nebolo možné nasadiť Azure Function |

---

**Zrieknutie sa zodpovednosti**:  
Tento dokument bol preložený pomocou služby AI prekladu [Co-op Translator](https://github.com/Azure/co-op-translator). Aj keď sa snažíme o presnosť, prosím, berte na vedomie, že automatizované preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho rodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nenesieme zodpovednosť za akékoľvek nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.