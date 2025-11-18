<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5a94fbab1ba737e9bd6cc6c64f114fa0",
  "translation_date": "2025-11-18T18:23:42+00:00",
  "source_file": "clean-up.md",
  "language_code": "pcm"
}
-->
# Clean up your project

Wen you don finish each project, e good make you delete your cloud resources.

For di lessons wey dey each project, you fit don create some of dis ones:

* Resource Group
* IoT Hub
* IoT device registrations
* Storage Account
* Functions App
* Azure Maps account
* Custom vision project
* Azure Container Registry
* Cognitive services resource

Most of dis resources no go cost you money - either dem dey completely free, or you dey use di free tier. For di services wey need paid tier, you go dey use dem for level wey dey inside di free allowance, or e go just cost small money.

Even though di cost no too high, e still good make you delete dis resources wen you don finish. For example, you fit only get one IoT Hub wey dey use di free tier, so if you wan create another one, you go need use di paid tier.

All di services wey you create dey inside Resource Groups, and dis one dey make am easy to manage. You fit delete di Resource Group, and all di services wey dey inside di Resource Group go delete join.

To delete di Resource Group, run dis command for your terminal or command prompt:

```sh
az group delete --name <resource-group-name>
```

Change `<resource-group-name>` to di name of di Resource Group wey you wan delete.

You go see confirmation:

```output
Are you sure you want to perform this operation? (y/n): 
```

Type `y` to confirm and delete di Resource Group.

E go take small time to delete all di services.

> 💁 You fit read more about how to delete resource groups for di [Azure Resource Manager resource group and resource deletion documentation for Microsoft Docs](https://docs.microsoft.com/azure/azure-resource-manager/management/delete-resource-group?WT.mc_id=academic-17441-jabenn&tabs=azure-cli)

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Disclaimer**:  
Dis document don use AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator) take translate am. Even though we dey try make e accurate, abeg sabi say automated translations fit get mistake or no correct well. Di original document for di native language na di main correct source. For important information, e good make una use professional human translation. We no go fit take blame for any misunderstanding or wrong interpretation wey fit happen because of dis translation.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->