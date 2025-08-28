<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3764e089adf2d5801272bc0895f8498b",
  "translation_date": "2025-08-28T08:15:15+00:00",
  "source_file": "4-manufacturing/README.md",
  "language_code": "sk"
}
-->
# Výroba a spracovanie - využitie IoT na zlepšenie spracovania potravín

Keď potraviny dorazia do centrálneho skladu alebo spracovateľského závodu, nie vždy sú okamžite odoslané do supermarketov. Často prechádzajú viacerými spracovateľskými krokmi, ako je triedenie podľa kvality. Tento proces býval manuálny – začínal na poli, kde zberači zbierali iba zrelé ovocie, a potom vo fabrike ovocie putovalo na dopravnom páse, kde zamestnanci ručne odstraňovali poškodené alebo zhnité plody. Keďže som počas školy brigádoval pri zbere a triedení jahôd, môžem potvrdiť, že to nie je práve zábavná práca.

Moderné systémy sa spoliehajú na IoT pri triedení. Niektoré z prvých zariadení, ako triediče od [Weco](https://wecotek.com), používajú optické senzory na detekciu kvality plodín, napríklad na odmietnutie zelených paradajok. Tieto zariadenia môžu byť nasadené priamo na farmách v zberačoch alebo v spracovateľských závodoch.

S pokrokom v oblasti umelej inteligencie (AI) a strojového učenia (ML) sa tieto stroje môžu stať ešte pokročilejšími, využívajúc modely ML trénované na rozlišovanie medzi ovocím a cudzími predmetmi, ako sú kamene, špina alebo hmyz. Tieto modely môžu byť tiež trénované na detekciu kvality ovocia, nielen poškodeného ovocia, ale aj na včasné odhalenie chorôb alebo iných problémov s plodinami.

> 🎓 Termín *ML model* označuje výstup z trénovania softvéru strojového učenia na súbore dát. Napríklad môžete vytrénovať ML model na rozlišovanie medzi zrelými a nezrelými paradajkami a potom použiť model na nové obrázky, aby ste zistili, či sú paradajky zrelé alebo nie.

V týchto 4 lekciách sa naučíte, ako trénovať AI modely založené na obrazoch na detekciu kvality ovocia, ako ich používať na IoT zariadení a ako ich spúšťať na okraji siete – teda na IoT zariadení namiesto v cloude.

> 💁 Tieto lekcie budú využívať niektoré cloudové zdroje. Ak neukončíte všetky lekcie v tomto projekte, nezabudnite [vyčistiť svoj projekt](../clean-up.md).

## Témy

1. [Vytrénujte detektor kvality ovocia](./lessons/1-train-fruit-detector/README.md)
1. [Skontrolujte kvalitu ovocia z IoT zariadenia](./lessons/2-check-fruit-from-device/README.md)
1. [Spustite svoj detektor ovocia na okraji siete](./lessons/3-run-fruit-detector-edge/README.md)
1. [Spustite detekciu kvality ovocia zo senzora](./lessons/4-trigger-fruit-detector/README.md)

## Kredity

Všetky lekcie boli napísané s ♥️ od [Jen Fox](https://github.com/jenfoxbot) a [Jim Bennett](https://GitHub.com/JimBobBennett)

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby na automatický preklad [Co-op Translator](https://github.com/Azure/co-op-translator). Aj keď sa snažíme o presnosť, upozorňujeme, že automatické preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho pôvodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nezodpovedáme za akékoľvek nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.