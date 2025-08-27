<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5a94fbab1ba737e9bd6cc6c64f114fa0",
  "translation_date": "2025-08-27T20:33:13+00:00",
  "source_file": "clean-up.md",
  "language_code": "hu"
}
-->
# Tisztítsd meg a projektedet

Miután befejeztél egy projektet, érdemes törölni a felhőalapú erőforrásokat.

Az egyes projektek leckéiben valószínűleg létrehoztál néhányat az alábbiak közül:

* Egy erőforráscsoportot
* Egy IoT Hubot
* IoT eszközregisztrációkat
* Egy tárfiókot
* Egy Functions Appot
* Egy Azure Maps fiókot
* Egy egyedi látás projektet
* Egy Azure Container Registryt
* Egy kognitív szolgáltatások erőforrást

Ezek közül a legtöbb erőforrás nem jár költséggel – vagy teljesen ingyenesek, vagy az ingyenes szintet használod. Azoknál a szolgáltatásoknál, amelyek fizetős szintet igényelnek, valószínűleg olyan szinten használtad őket, amely az ingyenes keretbe tartozik, vagy csak néhány centbe kerül.

Még a viszonylag alacsony költségek mellett is érdemes törölni ezeket az erőforrásokat, amikor végeztél. Például csak egy IoT Hubot használhatsz az ingyenes szinten, így ha egy másikat szeretnél létrehozni, fizetős szintet kell használnod.

Minden szolgáltatásodat erőforráscsoportokban hoztad létre, ami megkönnyíti a kezelést. Törölheted az erőforráscsoportot, és az abban lévő összes szolgáltatás vele együtt törlődik.

Az erőforráscsoport törléséhez futtasd az alábbi parancsot a terminálodban vagy parancssorodban:

```sh
az group delete --name <resource-group-name>
```

Cseréld ki `<resource-group-name>`-t az általad érintett erőforráscsoport nevére.

Egy megerősítés fog megjelenni:

```output
Are you sure you want to perform this operation? (y/n): 
```

Írd be, hogy `y`, hogy megerősítsd és töröld az erőforráscsoportot.

Eltarthat egy ideig, amíg az összes szolgáltatás törlődik.

> 💁 További információt az erőforráscsoportok törléséről az [Azure Resource Manager erőforráscsoport és erőforrás törlés dokumentációjában találhatsz a Microsoft Docs oldalán](https://docs.microsoft.com/azure/azure-resource-manager/management/delete-resource-group?WT.mc_id=academic-17441-jabenn&tabs=azure-cli).

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.