<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5a94fbab1ba737e9bd6cc6c64f114fa0",
  "translation_date": "2025-08-28T08:12:48+00:00",
  "source_file": "clean-up.md",
  "language_code": "sk"
}
-->
# Vyčistite svoj projekt

Po dokončení každého projektu je dobré odstrániť vaše cloudové zdroje.

V lekciách pre každý projekt ste mohli vytvoriť niektoré z nasledujúcich:

* Skupinu zdrojov
* IoT Hub
* Registrácie IoT zariadení
* Účet úložiska
* Aplikáciu Functions
* Účet Azure Maps
* Projekt vlastného rozpoznávania obrazu
* Azure Container Registry
* Zdroje kognitívnych služieb

Väčšina týchto zdrojov nebude mať žiadne náklady – buď sú úplne zadarmo, alebo používate bezplatnú úroveň. Pre služby, ktoré vyžadujú platenú úroveň, ste ich pravdepodobne používali na úrovni zahrnutej v bezplatnom limite, alebo vás budú stáť len pár centov.

Aj napriek relatívne nízkym nákladom sa oplatí tieto zdroje po dokončení odstrániť. Napríklad môžete mať iba jeden IoT Hub využívajúci bezplatnú úroveň, takže ak chcete vytvoriť ďalší, budete musieť použiť platenú úroveň.

Všetky vaše služby boli vytvorené v rámci skupín zdrojov, čo uľahčuje ich správu. Môžete odstrániť celú skupinu zdrojov a všetky služby v tejto skupine budú odstránené spolu s ňou.

Na odstránenie skupiny zdrojov spustite nasledujúci príkaz vo vašom termináli alebo príkazovom riadku:

```sh
az group delete --name <resource-group-name>
```

Nahraďte `<resource-group-name>` názvom skupiny zdrojov, o ktorú máte záujem.

Zobrazí sa potvrdenie:

```output
Are you sure you want to perform this operation? (y/n): 
```

Zadajte `y` na potvrdenie a odstránenie skupiny zdrojov.

Odstránenie všetkých služieb bude chvíľu trvať.

> 💁 Viac o odstraňovaní skupín zdrojov si môžete prečítať v [dokumentácii o odstraňovaní skupín a zdrojov Azure Resource Manager na Microsoft Docs](https://docs.microsoft.com/azure/azure-resource-manager/management/delete-resource-group?WT.mc_id=academic-17441-jabenn&tabs=azure-cli)

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby na automatický preklad [Co-op Translator](https://github.com/Azure/co-op-translator). Aj keď sa snažíme o presnosť, upozorňujeme, že automatické preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho pôvodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre dôležité informácie sa odporúča profesionálny ľudský preklad. Nezodpovedáme za akékoľvek nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.