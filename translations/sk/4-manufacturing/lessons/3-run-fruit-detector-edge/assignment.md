<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cc7ad255517f5f618f9c8899e6ff6783",
  "translation_date": "2025-08-28T08:36:33+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/assignment.md",
  "language_code": "sk"
}
-->
# Spustenie iných služieb na okraji

## Pokyny

Na okraji sa dajú spúšťať nielen klasifikátory obrázkov, ale čokoľvek, čo je možné zabaliť do kontajnera, môže byť nasadené na zariadenie IoT Edge. Bezserverový kód, ktorý beží ako Azure Functions, napríklad spúšťače, ktoré ste vytvorili v predchádzajúcich lekciách, môže byť spustený v kontajneroch, a teda aj na IoT Edge.

Vyberte si jednu z predchádzajúcich lekcií a skúste spustiť aplikáciu Azure Functions v kontajneri IoT Edge. Návod, ktorý ukazuje, ako to urobiť s iným projektom aplikácie Functions, nájdete v [Tutoriál: Nasadenie Azure Functions ako modulov IoT Edge na Microsoft docs](https://docs.microsoft.com/azure/iot-edge/tutorial-deploy-function?WT.mc_id=academic-17441-jabenn&view=iotedge-2020-11).

## Kritériá hodnotenia

| Kritérium | Vynikajúce | Dostatočné | Potrebuje zlepšenie |
| --------- | ---------- | ---------- | ------------------- |
| Nasadenie aplikácie Azure Functions na IoT Edge | Podarilo sa nasadiť aplikáciu Azure Functions na IoT Edge a použiť ju so zariadením IoT na spustenie spúšťača z IoT dát | Podarilo sa nasadiť aplikáciu Functions na IoT Edge, ale nepodarilo sa spustiť spúšťač | Nepodarilo sa nasadiť aplikáciu Functions na IoT Edge |

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby na automatický preklad [Co-op Translator](https://github.com/Azure/co-op-translator). Hoci sa snažíme o presnosť, upozorňujeme, že automatické preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho pôvodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nenesieme zodpovednosť za akékoľvek nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.