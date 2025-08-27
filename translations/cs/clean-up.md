<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5a94fbab1ba737e9bd6cc6c64f114fa0",
  "translation_date": "2025-08-27T20:33:24+00:00",
  "source_file": "clean-up.md",
  "language_code": "cs"
}
-->
# Vyčištění vašeho projektu

Po dokončení každého projektu je dobré smazat vaše cloudové zdroje.

V lekcích pro každý projekt jste mohli vytvořit některé z následujících:

* Skupina prostředků
* IoT Hub
* Registrace IoT zařízení
* Účet úložiště
* Aplikace Functions
* Účet Azure Maps
* Projekt Custom Vision
* Registr Azure Container
* Zdroje kognitivních služeb

Většina těchto zdrojů nebude mít žádné náklady – buď jsou zcela zdarma, nebo používáte bezplatnou úroveň. U služeb, které vyžadují placenou úroveň, jste je pravděpodobně používali na úrovni zahrnuté v bezplatném limitu, nebo vás stály jen pár centů.

I přes relativně nízké náklady se vyplatí tyto zdroje po dokončení smazat. Například můžete mít pouze jeden IoT Hub využívající bezplatnou úroveň, takže pokud chcete vytvořit další, budete muset použít placenou úroveň.

Všechny vaše služby byly vytvořeny uvnitř skupin prostředků, což usnadňuje jejich správu. Můžete smazat celou skupinu prostředků, a tím se smažou všechny služby v této skupině.

Pro smazání skupiny prostředků spusťte následující příkaz ve svém terminálu nebo příkazovém řádku:

```sh
az group delete --name <resource-group-name>
```

Nahraďte `<resource-group-name>` názvem skupiny prostředků, o kterou máte zájem.

Zobrazí se potvrzení:

```output
Are you sure you want to perform this operation? (y/n): 
```

Zadejte `y` pro potvrzení a smazání skupiny prostředků.

Smazání všech služeb bude chvíli trvat.

> 💁 Více informací o mazání skupin prostředků si můžete přečíst v [dokumentaci Azure Resource Manager o mazání skupin prostředků a zdrojů na Microsoft Docs](https://docs.microsoft.com/azure/azure-resource-manager/management/delete-resource-group?WT.mc_id=academic-17441-jabenn&tabs=azure-cli)

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). Ačkoli se snažíme o přesnost, mějte na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace doporučujeme profesionální lidský překlad. Neodpovídáme za žádná nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.