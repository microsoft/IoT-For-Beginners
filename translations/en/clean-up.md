<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5a94fbab1ba737e9bd6cc6c64f114fa0",
  "translation_date": "2025-08-28T18:56:45+00:00",
  "source_file": "clean-up.md",
  "language_code": "en"
}
-->
# Clean up your project

After completing each project, it's a good practice to delete your cloud resources.

During the lessons for each project, you may have created some of the following:

* A Resource Group
* An IoT Hub
* IoT device registrations
* A Storage Account
* A Functions App
* An Azure Maps account
* A custom vision project
* An Azure Container Registry
* A cognitive services resource

Most of these resources won't incur any costs—they're either completely free or you're using a free tier. For services that require a paid tier, you would have been using them at a level covered by the free allowance or costing only a few cents.

Even though the costs are relatively low, it's still a good idea to delete these resources once you're finished. For example, you can only have one IoT Hub on the free tier, so if you want to create another, you'll need to switch to a paid tier.

All your services were created within Resource Groups, which makes management easier. You can delete the Resource Group, and all the services within it will be deleted as well.

To delete the Resource Group, run the following command in your terminal or command prompt:

```sh
az group delete --name <resource-group-name>
```

Replace `<resource-group-name>` with the name of the Resource Group you want to delete.

You'll see a confirmation prompt:

```output
Are you sure you want to perform this operation? (y/n): 
```

Type `y` to confirm and delete the Resource Group.

It may take some time to delete all the services.

> 💁 You can find more information about deleting resource groups in the [Azure Resource Manager resource group and resource deletion documentation on Microsoft Docs](https://docs.microsoft.com/azure/azure-resource-manager/management/delete-resource-group?WT.mc_id=academic-17441-jabenn&tabs=azure-cli)

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we aim for accuracy, please note that automated translations may include errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is advised. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.