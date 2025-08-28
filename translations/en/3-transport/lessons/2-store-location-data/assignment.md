<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "b2e0a965723082b068f735aec0faf3f6",
  "translation_date": "2025-08-28T19:49:25+00:00",
  "source_file": "3-transport/lessons/2-store-location-data/assignment.md",
  "language_code": "en"
}
-->
# Investigate function bindings

## Instructions

Function bindings enable your code to save blobs to blob storage by returning them from the `main` function. The Azure Storage account, collection, and other details are set up in the `function.json` file.

When working with Azure or other Microsoft technologies, the best source of information is [the Microsoft documentation at docs.com](https://docs.microsoft.com/?WT.mc_id=academic-17441-jabenn). For this assignment, you will need to review the Azure Functions binding documentation to learn how to configure the output binding.

Some useful pages to get started include:

* [Azure Functions triggers and bindings concepts](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python)
* [Azure Blob storage bindings for Azure Functions overview](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob?WT.mc_id=academic-17441-jabenn)
* [Azure Blob storage output binding for Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob-output?WT.mc_id=academic-17441-jabenn&tabs=python)

## Rubric

| Criteria | Exemplary | Adequate | Needs Improvement |
| -------- | --------- | -------- | ----------------- |
| Configure the blob storage output binding | Successfully configured the output binding, returned the blob, and stored it in blob storage | Configured the output binding or returned the blob, but was unable to store it in blob storage | Unable to configure the output binding |

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we aim for accuracy, please note that automated translations may include errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is advised. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.