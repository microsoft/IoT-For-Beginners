<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1a85e50c33c38dcd2cde2a97d132f248",
  "translation_date": "2025-08-28T08:27:47+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/assignment.md",
  "language_code": "sk"
}
-->
# Vytvorte detektor kvality ovocia

## Pokyny

Vytvorte detektor kvality ovocia!

Využite všetko, čo ste sa doteraz naučili, a vytvorte prototyp detektora kvality ovocia. Spustite klasifikáciu obrázkov na základe blízkosti pomocou AI modelu bežiaceho na okraji, uložte výsledky klasifikácie do úložiska a ovládajte LED diódu na základe zrelosti ovocia.

Mali by ste byť schopní zostaviť toto riešenie pomocou kódu, ktorý ste napísali vo všetkých doterajších lekciách.

## Hodnotiace kritériá

| Kritérium | Vynikajúce | Dostatočné | Potrebuje zlepšenie |
| --------- | ---------- | ---------- | ------------------- |
| Nastavenie všetkých služieb | Podarilo sa nastaviť IoT Hub, aplikáciu Azure Functions a Azure Storage | Podarilo sa nastaviť IoT Hub, ale nie aplikáciu Azure Functions alebo Azure Storage | Nepodarilo sa nastaviť žiadne internetové IoT služby |
| Monitorovanie blízkosti a odosielanie údajov do IoT Hub, ak je objekt bližšie ako preddefinovaná vzdialenosť, a spustenie kamery príkazom | Podarilo sa zmerať vzdialenosť, odoslať správu do IoT Hub, keď bol objekt dostatočne blízko, a poslať príkaz na spustenie kamery | Podarilo sa zmerať blízkosť a odoslať údaje do IoT Hub, ale nepodarilo sa poslať príkaz na spustenie kamery | Nepodarilo sa zmerať vzdialenosť, odoslať správu do IoT Hub ani spustiť príkaz |
| Zachytenie obrázka, jeho klasifikácia a odoslanie výsledkov do IoT Hub | Podarilo sa zachytiť obrázok, klasifikovať ho pomocou edge zariadenia a odoslať výsledky do IoT Hub | Podarilo sa klasifikovať obrázok, ale nie pomocou edge zariadenia, alebo sa nepodarilo odoslať výsledky do IoT Hub | Nepodarilo sa klasifikovať obrázok |
| Zapnutie alebo vypnutie LED diódy na základe výsledkov klasifikácie pomocou príkazu odoslaného zariadeniu | Podarilo sa zapnúť LED diódu príkazom, ak bolo ovocie nezrelé | Podarilo sa odoslať príkaz zariadeniu, ale nepodarilo sa ovládať LED diódu | Nepodarilo sa odoslať príkaz na ovládanie LED diódy |

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby na automatický preklad [Co-op Translator](https://github.com/Azure/co-op-translator). Hoci sa snažíme o presnosť, upozorňujeme, že automatické preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho pôvodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nenesieme zodpovednosť za akékoľvek nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.