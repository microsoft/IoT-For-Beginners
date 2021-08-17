# Investigate function bindings

## Instructions

Function bindings allow your code to save blobs to blob storage by returning them from the `main` function. The Azure Storage account, collection and other details are configured in the `function.json` file.

When working with Azure or other Microsoft technologies, the best source of information is [the Microsoft documentation at docs.com](https://docs.microsoft.com/?WT.mc_id=academic-17441-jabenn). In this assignment you will need to read the Azure Functions binding documentation to work out how to set up the output binding.

Some pages to look at to get started are:

* [Azure Functions triggers and bindings concepts](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python)
* [Azure Blob storage bindings for Azure Functions overview](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob?WT.mc_id=academic-17441-jabenn)
* [Azure Blob storage output binding for Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob-output?WT.mc_id=academic-17441-jabenn&tabs=python)

## Rubric

| Criteria | Exemplary | Adequate | Needs Improvement |
| -------- | --------- | -------- | ----------------- |
| Configure the blob storage output binding | Was able to configure the output binding, return the blob and have it stored in blob storage successfully | Was able to configure the output binding, or return the blob but was unable to have it stored in blob storage successfully |  Was unable to configure the output binding |
