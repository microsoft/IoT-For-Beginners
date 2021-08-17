# Clean up your project

After you complete each project, it is good to delete your cloud resources.

In the lessons for each project, you may have created some of the following:

* A Resource Group
* An IoT Hub
* IoT device registrations
* A Storage Account
* A Functions App
* An Azure Maps account
* A custom vision project
* An Azure Container Registry
* A cognitive services resource

Most of these resources will have no cost - either they are completely free, or you are using a free tier. For services that require a paid tier, you would have been using them at a level that is included in the free allowance, or will only cost a few cents.

Even with the relatively low costs, it's worth deleting these resources when you are done. You can only have one IoT Hub using the free tier for example, so if you want to create another you will need to use a paid tier.

All your services were created inside Resource Groups, and this makes it easier to manage. You can delete the Resource Group, and all the services in that Resource Group will be deleted along with it.

To delete the Resource Group, run the following command in your terminal or command prompt:

```sh
az group delete --name <resource-group-name>
```

Replace `<resource-group-name>` with the name of the Resource Group you are interested in.

A confirmation will appear:

```output
Are you sure you want to perform this operation? (y/n): 
```

Enter `y` to confirm and delete the Resource Group.

It will take a while to delete all the services.

> 💁 You can read more about deleting resource groups on the [Azure Resource Manager resource group and resource deletion documentation on Microsoft Docs](https://docs.microsoft.com/azure/azure-resource-manager/management/delete-resource-group?WT.mc_id=academic-17441-jabenn&tabs=azure-cli)