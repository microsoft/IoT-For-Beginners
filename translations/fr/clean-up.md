<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5a94fbab1ba737e9bd6cc6c64f114fa0",
  "translation_date": "2025-08-24T21:00:45+00:00",
  "source_file": "clean-up.md",
  "language_code": "fr"
}
-->
# Nettoyez votre projet

Une fois que vous avez terminé chaque projet, il est conseillé de supprimer vos ressources cloud.

Dans les leçons de chaque projet, vous avez peut-être créé certains des éléments suivants :

* Un groupe de ressources
* Un IoT Hub
* Des enregistrements de dispositifs IoT
* Un compte de stockage
* Une application Functions
* Un compte Azure Maps
* Un projet de vision personnalisée
* Un registre de conteneurs Azure
* Une ressource de services cognitifs

La plupart de ces ressources n'entraîneront aucun coût - soit elles sont entièrement gratuites, soit vous utilisez un niveau gratuit. Pour les services nécessitant un niveau payant, vous les avez utilisés à un niveau inclus dans l'allocation gratuite, ou ils ne coûteront que quelques centimes.

Même avec des coûts relativement faibles, il est préférable de supprimer ces ressources une fois que vous avez terminé. Par exemple, vous ne pouvez avoir qu'un seul IoT Hub utilisant le niveau gratuit, donc si vous souhaitez en créer un autre, vous devrez utiliser un niveau payant.

Tous vos services ont été créés à l'intérieur de groupes de ressources, ce qui facilite leur gestion. Vous pouvez supprimer le groupe de ressources, et tous les services contenus dans ce groupe seront supprimés en même temps.

Pour supprimer le groupe de ressources, exécutez la commande suivante dans votre terminal ou invite de commande :

```sh
az group delete --name <resource-group-name>
```

Remplacez `<resource-group-name>` par le nom du groupe de ressources qui vous intéresse.

Une confirmation apparaîtra :

```output
Are you sure you want to perform this operation? (y/n): 
```

Entrez `y` pour confirmer et supprimer le groupe de ressources.

La suppression de tous les services prendra un certain temps.

> 💁 Vous pouvez en savoir plus sur la suppression des groupes de ressources dans la [documentation sur la suppression des groupes de ressources et des ressources Azure Resource Manager sur Microsoft Docs](https://docs.microsoft.com/azure/azure-resource-manager/management/delete-resource-group?WT.mc_id=academic-17441-jabenn&tabs=azure-cli)

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction professionnelle réalisée par un humain. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.