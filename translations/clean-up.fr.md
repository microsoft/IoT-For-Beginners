# Nettoyez votre projet

Après avoir terminé chaque projet, il est bon de supprimer vos ressources cloud.

Dans les leçons de chaque projet, vous avez peut-être créé certains des éléments suivants:

* Un groupe de ressources
* Un hub IoT
* Des enregistrements d'appareils IoT
* Un compte de stockage
* Une application de fonctions
* Un compte Azure Maps
* Un projet de vision sur mesure
* Un registre de conteneurs Azure
* Une ressource de services cognitifs

La plupart de ces ressources n'auront aucun coût - soit elles sont entièrement gratuites, soit vous utilisez un plan gratuit. Pour les services qui nécessitent un plan payant, vous les auriez utilisés à un niveau inclus dans l'allocation gratuite, ou ne coûterait que quelques centimes.

Même avec des coûts relativement bas, cela vaut la peine de supprimer ces ressources lorsque vous avez terminé. Vous ne pouvez avoir qu'un seul hub IoT utilisant le plan gratuit par exemple, donc si vous souhaitez en créer un autre, vous devrez utiliser un plan payant.

Tous vos services ont été créés dans des groupes de ressources, ce qui facilite leur gestion. Vous pouvez supprimer le groupe de ressources et tous les services de ce groupe de ressources seront également supprimés.

Pour supprimer le groupe de ressources, exécutez la commande suivante dans votre terminal ou invite de commande:

```sh
az group delete --name <resource-group-name>
```

Remplacez `<resource-group-name>` par le nom du groupe de ressources qui vous est propre.

Une confirmation apparaîtra:

```output
Are you sure you want to perform this operation? (y/n): 
```

Entrez `y` pour confirmer et supprimer le groupe de ressources.

Il faudra un certain temps pour supprimer tous les services.

> 💁 Vous pouvez en savoir plus sur la suppression des groupes de ressources dans la [documentation sur la suppression des groupes de ressources et des ressources Azure Resource Manager sur Microsoft Docs](https://docs.microsoft.com/azure/azure-resource-manager/management/delete-resource-group?WT.mc_id=academic-17441-jabenn&tabs=azure-cli)
