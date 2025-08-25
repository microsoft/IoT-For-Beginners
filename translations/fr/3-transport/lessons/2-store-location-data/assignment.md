<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "b2e0a965723082b068f735aec0faf3f6",
  "translation_date": "2025-08-25T01:07:28+00:00",
  "source_file": "3-transport/lessons/2-store-location-data/assignment.md",
  "language_code": "fr"
}
-->
# Examiner les liaisons de fonctions

## Instructions

Les liaisons de fonctions permettent à votre code d'enregistrer des blobs dans le stockage blob en les retournant depuis la fonction `main`. Le compte de stockage Azure, la collection et d'autres détails sont configurés dans le fichier `function.json`.

Lorsque vous travaillez avec Azure ou d'autres technologies Microsoft, la meilleure source d'information est [la documentation Microsoft sur docs.com](https://docs.microsoft.com/?WT.mc_id=academic-17441-jabenn). Dans cet exercice, vous devrez lire la documentation sur les liaisons des Azure Functions pour comprendre comment configurer la liaison de sortie.

Quelques pages à consulter pour commencer :

* [Concepts des déclencheurs et liaisons des Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python)
* [Vue d'ensemble des liaisons de stockage Blob pour Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob?WT.mc_id=academic-17441-jabenn)
* [Liaison de sortie de stockage Blob pour Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob-output?WT.mc_id=academic-17441-jabenn&tabs=python)

## Grille d'évaluation

| Critères | Exemplaire | Adéquat | À améliorer |
| -------- | ---------- | ------- | ----------- |
| Configurer la liaison de sortie du stockage blob | A réussi à configurer la liaison de sortie, à retourner le blob et à le stocker avec succès dans le stockage blob | A réussi à configurer la liaison de sortie ou à retourner le blob, mais n'a pas pu le stocker avec succès dans le stockage blob | N'a pas réussi à configurer la liaison de sortie |

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.