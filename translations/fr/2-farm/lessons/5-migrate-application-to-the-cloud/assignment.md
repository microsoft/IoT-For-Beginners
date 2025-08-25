<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c24b6e4d90501c9199f2ceb6a648a337",
  "translation_date": "2025-08-24T22:27:53+00:00",
  "source_file": "2-farm/lessons/5-migrate-application-to-the-cloud/assignment.md",
  "language_code": "fr"
}
-->
# Ajouter un contrôle manuel du relais

## Instructions

Le code sans serveur peut être déclenché par de nombreux éléments, y compris des requêtes HTTP. Vous pouvez utiliser des déclencheurs HTTP pour ajouter une commande manuelle à votre contrôle de relais, permettant à quelqu'un d'allumer ou d'éteindre le relais via une requête web.

Pour cet exercice, vous devez ajouter deux déclencheurs HTTP à votre Functions App pour allumer et éteindre le relais, en réutilisant ce que vous avez appris dans cette leçon pour envoyer des commandes à l'appareil.

Quelques conseils :

* Vous pouvez ajouter un déclencheur HTTP à votre Functions App existante avec la commande suivante :

    ```sh
    func new --name <trigger name> --template "HTTP trigger"
    ```

    Remplacez `<trigger name>` par le nom de votre déclencheur HTTP. Utilisez quelque chose comme `relay_on` et `relay_off`.

* Les déclencheurs HTTP peuvent avoir un contrôle d'accès. Par défaut, ils nécessitent qu'une clé API spécifique à la fonction soit transmise avec l'URL pour s'exécuter. Pour cet exercice, vous pouvez supprimer cette restriction afin que n'importe qui puisse exécuter la fonction. Pour ce faire, mettez à jour le paramètre `authLevel` dans le fichier `function.json` des déclencheurs HTTP avec la valeur suivante :

    ```json
    "authLevel": "anonymous"
    ```

    > 💁 Vous pouvez en savoir plus sur ce contrôle d'accès dans la [documentation sur les clés d'accès des fonctions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn#authorization-keys).

* Par défaut, les déclencheurs HTTP prennent en charge les requêtes GET et POST. Cela signifie que vous pouvez les appeler en utilisant votre navigateur web - les navigateurs web effectuent des requêtes GET.

    Lorsque vous exécutez votre Functions App localement, vous verrez l'URL du déclencheur :

    ```output
    Functions:

        relay_off: [GET,POST] http://localhost:7071/api/relay_off

        relay_on: [GET,POST] http://localhost:7071/api/relay_on

        iot-hub-trigger: eventHubTrigger
    ```

    Collez l'URL dans votre navigateur et appuyez sur `Entrée`, ou `Ctrl+clic` (`Cmd+clic` sur macOS) sur le lien dans la fenêtre du terminal dans VS Code pour l'ouvrir dans votre navigateur par défaut. Cela exécutera le déclencheur.

    > 💁 Remarquez que l'URL contient `/api` - les déclencheurs HTTP se trouvent par défaut dans le sous-domaine `api`.

* Lorsque vous déployez la Functions App, l'URL du déclencheur HTTP sera :

    `https://<functions app name>.azurewebsites.net/api/<trigger name>`

    Où `<functions app name>` est le nom de votre Functions App, et `<trigger name>` est le nom de votre déclencheur.

## Grille d'évaluation

| Critères | Exemplaire | Adéquat | À améliorer |
| -------- | ---------- | ------- | ----------- |
| Créer des déclencheurs HTTP | A créé 2 déclencheurs pour allumer et éteindre le relais, avec des noms appropriés | A créé un déclencheur avec un nom approprié | N'a pas réussi à créer de déclencheurs |
| Contrôler le relais à partir des déclencheurs HTTP | A réussi à connecter les deux déclencheurs à IoT Hub et à contrôler le relais correctement | A réussi à connecter un déclencheur à IoT Hub et à contrôler le relais correctement | N'a pas réussi à connecter les déclencheurs à IoT Hub |

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction professionnelle réalisée par un humain. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.