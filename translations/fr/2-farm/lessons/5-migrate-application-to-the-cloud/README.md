# Migrer la logique de votre application vers le cloud

![Un aperçu en sketchnote de cette leçon](../../../../../translated_images/fr/lesson-9.dfe99c8e891f48e1.webp)

> Sketchnote par [Nitya Narasimhan](https://github.com/nitya). Cliquez sur l'image pour une version agrandie.

Cette leçon a été enseignée dans le cadre du [Projet IoT pour débutants 2 - Série Agriculture numérique](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) du [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn).

[![Contrôlez votre appareil IoT avec du code sans serveur](https://img.youtube.com/vi/VVZDcs5u1_I/0.jpg)](https://youtu.be/VVZDcs5u1_I)

## Quiz avant la leçon

[Quiz avant la leçon](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/17)

## Introduction

Dans la dernière leçon, vous avez appris à connecter votre système de surveillance de l'humidité du sol des plantes et de contrôle de relais à un service IoT basé sur le cloud. L'étape suivante consiste à déplacer le code serveur qui contrôle le timing du relais vers le cloud. Dans cette leçon, vous apprendrez à le faire en utilisant des fonctions sans serveur.

Dans cette leçon, nous couvrirons :

* [Qu'est-ce que le sans serveur ?](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Créer une application sans serveur](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Créer un déclencheur d'événement IoT Hub](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Envoyer des requêtes de méthode directe depuis du code sans serveur](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Déployer votre code sans serveur dans le cloud](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)

## Qu'est-ce que le sans serveur ?

Le sans serveur, ou informatique sans serveur, consiste à créer de petits blocs de code qui s'exécutent dans le cloud en réponse à différents types d'événements. Lorsque l'événement se produit, votre code est exécuté et reçoit des données sur l'événement. Ces événements peuvent provenir de nombreuses sources, notamment des requêtes web, des messages placés dans une file d'attente, des modifications de données dans une base de données ou des messages envoyés à un service IoT par des appareils IoT.

![Des événements envoyés d'un service IoT à un service sans serveur, tous traités simultanément par plusieurs fonctions exécutées](../../../../../translated_images/fr/iot-messages-to-serverless.0194da1cc0732bb7.webp)

> 💁 Si vous avez déjà utilisé des déclencheurs de base de données, vous pouvez considérer cela comme similaire : du code déclenché par un événement tel que l'insertion d'une ligne.

![Lorsque de nombreux événements sont envoyés en même temps, le service sans serveur s'adapte pour les traiter tous simultanément](../../../../../translated_images/fr/serverless-scaling.f8c769adf0413fd1.webp)

Votre code est exécuté uniquement lorsque l'événement se produit, il n'est pas actif à d'autres moments. L'événement se produit, votre code est chargé et exécuté. Cela rend le sans serveur très évolutif : si de nombreux événements se produisent en même temps, le fournisseur de cloud peut exécuter votre fonction autant de fois que nécessaire simultanément sur les serveurs disponibles. L'inconvénient est que si vous devez partager des informations entre les événements, vous devez les enregistrer quelque part, comme dans une base de données, plutôt que de les stocker en mémoire.

Votre code est écrit sous forme de fonction qui prend les détails de l'événement en paramètre. Vous pouvez utiliser une large gamme de langages de programmation pour écrire ces fonctions sans serveur.

> 🎓 Le sans serveur est également appelé "Fonctions en tant que service" (FaaS) car chaque déclencheur d'événement est implémenté comme une fonction dans le code.

Malgré son nom, le sans serveur utilise en réalité des serveurs. Ce nom est dû au fait que, en tant que développeur, vous ne vous souciez pas des serveurs nécessaires pour exécuter votre code, tout ce qui vous importe est que votre code soit exécuté en réponse à un événement. Le fournisseur de cloud dispose d'un *runtime* sans serveur qui gère l'allocation des serveurs, le réseau, le stockage, le CPU, la mémoire et tout ce qui est nécessaire pour exécuter votre code. Ce modèle signifie que vous ne payez pas par serveur pour le service, car il n'y a pas de serveur. À la place, vous payez pour le temps d'exécution de votre code et la quantité de mémoire utilisée.

> 💰 Le sans serveur est l'un des moyens les moins chers d'exécuter du code dans le cloud. Par exemple, au moment de la rédaction, un fournisseur de cloud permet à toutes vos fonctions sans serveur de s'exécuter un total combiné de 1 000 000 fois par mois avant de commencer à vous facturer, et après cela, il facture 0,20 USD pour chaque 1 000 000 exécutions. Lorsque votre code n'est pas en cours d'exécution, vous ne payez rien.

En tant que développeur IoT, le modèle sans serveur est idéal. Vous pouvez écrire une fonction qui est appelée en réponse aux messages envoyés par n'importe quel appareil IoT connecté à votre service IoT hébergé dans le cloud. Votre code gérera tous les messages envoyés, mais ne sera exécuté que lorsque cela est nécessaire.

✅ Revenez au code que vous avez écrit en tant que serveur écoutant les messages via MQTT. Comment cela pourrait-il fonctionner dans le cloud en utilisant le sans serveur ? Comment pensez-vous que le code pourrait être modifié pour prendre en charge l'informatique sans serveur ?

> 💁 Le modèle sans serveur s'étend à d'autres services cloud en plus de l'exécution de code. Par exemple, des bases de données sans serveur sont disponibles dans le cloud en utilisant un modèle de tarification sans serveur où vous payez par requête effectuée contre la base de données, comme une requête ou une insertion, généralement avec une tarification basée sur la quantité de travail nécessaire pour traiter la requête. Par exemple, une simple sélection d'une ligne contre une clé primaire coûtera moins cher qu'une opération complexe joignant plusieurs tables et retournant des milliers de lignes.

## Créer une application sans serveur

Le service d'informatique sans serveur de Microsoft s'appelle Azure Functions.

![Le logo Azure Functions](../../../../../translated_images/fr/azure-functions-logo.1cfc8e3204c9c44a.webp)

La courte vidéo ci-dessous donne un aperçu d'Azure Functions.

[![Vidéo d'aperçu d'Azure Functions](https://img.youtube.com/vi/8-jz5f_JyEQ/0.jpg)](https://www.youtube.com/watch?v=8-jz5f_JyEQ)

> 🎥 Cliquez sur l'image ci-dessus pour regarder une vidéo.

✅ Prenez un moment pour faire des recherches et lire l'aperçu d'Azure Functions dans la [documentation Microsoft Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-overview?WT.mc_id=academic-17441-jabenn).

Pour écrire des fonctions Azure, vous commencez par une application Azure Functions dans le langage de votre choix. Azure Functions prend en charge Python, JavaScript, TypeScript, C#, F#, Java et Powershell. Dans cette leçon, vous apprendrez à écrire une application Azure Functions en Python.

> 💁 Azure Functions prend également en charge des gestionnaires personnalisés, ce qui vous permet d'écrire vos fonctions dans n'importe quel langage qui prend en charge les requêtes HTTP, y compris des langages plus anciens comme COBOL.

Les applications de fonctions se composent d'un ou plusieurs *déclencheurs* - des fonctions qui répondent à des événements. Vous pouvez avoir plusieurs déclencheurs dans une application de fonctions, tous partageant une configuration commune. Par exemple, dans le fichier de configuration de votre application de fonctions, vous pouvez avoir les détails de connexion de votre IoT Hub, et toutes les fonctions de l'application peuvent utiliser cela pour se connecter et écouter les événements.

### Tâche - installer les outils Azure Functions

> Au moment de la rédaction, les outils de code Azure Functions ne fonctionnent pas entièrement sur Apple Silicon avec des projets Python. Vous devrez utiliser un Mac basé sur Intel, un PC Windows ou un PC Linux à la place.

Une grande fonctionnalité d'Azure Functions est que vous pouvez les exécuter localement. Le même runtime utilisé dans le cloud peut être exécuté sur votre ordinateur, vous permettant d'écrire du code qui répond aux messages IoT et de l'exécuter localement. Vous pouvez même déboguer votre code pendant que les événements sont traités. Une fois que vous êtes satisfait de votre code, il peut être déployé dans le cloud.

Les outils Azure Functions sont disponibles sous forme de CLI, connu sous le nom d'Azure Functions Core Tools.

1. Installez les outils Azure Functions Core Tools en suivant les instructions de la [documentation Azure Functions Core Tools](https://docs.microsoft.com/azure/azure-functions/functions-run-local?WT.mc_id=academic-17441-jabenn).

1. Installez l'extension Azure Functions pour VS Code. Cette extension fournit un support pour la création, le débogage et le déploiement des fonctions Azure. Consultez la [documentation de l'extension Azure Functions](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-azuretools.vscode-azurefunctions) pour les instructions sur l'installation de cette extension dans VS Code.

Lorsque vous déployez votre application Azure Functions dans le cloud, elle doit utiliser une petite quantité de stockage cloud pour stocker des éléments tels que les fichiers d'application et les fichiers journaux. Lorsque vous exécutez votre application de fonctions localement, vous devez toujours vous connecter au stockage cloud, mais au lieu d'utiliser un stockage cloud réel, vous pouvez utiliser un émulateur de stockage appelé [Azurite](https://github.com/Azure/Azurite). Celui-ci fonctionne localement mais agit comme un stockage cloud.

> 🎓 Dans Azure, le stockage utilisé par Azure Functions est un compte de stockage Azure. Ces comptes peuvent stocker des fichiers, des blobs, des données dans des tables ou des données dans des files d'attente. Vous pouvez partager un compte de stockage entre plusieurs applications, comme une application de fonctions et une application web.

1. Azurite est une application Node.js, vous devrez donc installer Node.js. Vous pouvez trouver les instructions de téléchargement et d'installation sur le [site web Node.js](https://nodejs.org/). Si vous utilisez un Mac, vous pouvez également l'installer via [Homebrew](https://formulae.brew.sh/formula/node).

1. Installez Azurite en utilisant la commande suivante (`npm` est un outil installé avec Node.js) :

    ```sh
    npm install -g azurite
    ```

1. Créez un dossier appelé `azurite` pour qu'Azurite puisse l'utiliser pour stocker des données :

    ```sh
    mkdir azurite
    ```

1. Exécutez Azurite en lui passant ce nouveau dossier :

    ```sh
    azurite --location azurite
    ```

    L'émulateur de stockage Azurite se lancera et sera prêt à être connecté au runtime local des fonctions.

    ```output
    ➜  ~ azurite --location azurite  
    Azurite Blob service is starting at http://127.0.0.1:10000
    Azurite Blob service is successfully listening at http://127.0.0.1:10000
    Azurite Queue service is starting at http://127.0.0.1:10001
    Azurite Queue service is successfully listening at http://127.0.0.1:10001
    Azurite Table service is starting at http://127.0.0.1:10002
    Azurite Table service is successfully listening at http://127.0.0.1:10002
    ```

### Tâche - créer un projet Azure Functions

Le CLI Azure Functions peut être utilisé pour créer une nouvelle application de fonctions.

1. Créez un dossier pour votre application de fonctions et naviguez dedans. Appelez-le `soil-moisture-trigger`.

    ```sh
    mkdir soil-moisture-trigger
    cd soil-moisture-trigger
    ```

1. Créez un environnement virtuel Python à l'intérieur de ce dossier :

    ```sh
    python3 -m venv .venv
    ```

1. Activez l'environnement virtuel :

    * Sur Windows :
        * Si vous utilisez l'invite de commande ou l'invite de commande via Windows Terminal, exécutez :

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * Si vous utilisez PowerShell, exécutez :

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

    * Sur macOS ou Linux, exécutez :

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 Ces commandes doivent être exécutées depuis le même emplacement où vous avez exécuté la commande pour créer l'environnement virtuel. Vous n'aurez jamais besoin de naviguer dans le dossier `.venv`, vous devez toujours exécuter la commande d'activation et toute commande pour installer des packages ou exécuter du code depuis le dossier où vous étiez lorsque vous avez créé l'environnement virtuel.

1. Exécutez la commande suivante pour créer une application de fonctions dans ce dossier :

    ```sh
    func init --worker-runtime python soil-moisture-trigger
    ```

    Cela créera trois fichiers dans le dossier actuel :

    * `host.json` - ce document JSON contient les paramètres de votre application de fonctions. Vous n'aurez pas besoin de modifier ces paramètres.
    * `local.settings.json` - ce document JSON contient les paramètres que votre application utiliserait lorsqu'elle s'exécute localement, comme les chaînes de connexion pour votre IoT Hub. Ces paramètres sont uniquement locaux et ne doivent pas être ajoutés au contrôle de code source. Lorsque vous déployez l'application dans le cloud, ces paramètres ne sont pas déployés, à la place vos paramètres sont chargés à partir des paramètres de l'application. Cela sera abordé plus tard dans cette leçon.
    * `requirements.txt` - il s'agit d'un [fichier de dépendances Pip](https://pip.pypa.io/en/stable/user_guide/#requirements-files) qui contient les packages Pip nécessaires pour exécuter votre application de fonctions.

1. Le fichier `local.settings.json` contient un paramètre pour le compte de stockage que l'application de fonctions utilisera. Par défaut, ce paramètre est vide et doit être défini. Pour se connecter à l'émulateur de stockage local Azurite, définissez cette valeur comme suit :

    ```json
    "AzureWebJobsStorage": "UseDevelopmentStorage=true",
    ```

1. Installez les packages Pip nécessaires en utilisant le fichier de dépendances :

    ```sh
    pip install -r requirements.txt
    ```

    > 💁 Les packages Pip nécessaires doivent être dans ce fichier, afin que lorsque l'application de fonctions est déployée dans le cloud, le runtime puisse s'assurer qu'il installe les bons packages.

1. Pour tester que tout fonctionne correctement, vous pouvez démarrer le runtime des fonctions. Exécutez la commande suivante pour le faire :

    ```sh
    func start
    ```

    Vous verrez le runtime démarrer et signaler qu'il n'a trouvé aucune fonction de travail (déclencheurs).

    ```output
    (.venv) ➜  soil-moisture-trigger func start
    Found Python version 3.9.1 (python3).
    
    Azure Functions Core Tools
    Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    Function Runtime Version: 3.0.15417.0
    
    [2021-05-05T01:24:46.795Z] No job functions found.
    ```
> ⚠️ Si vous recevez une notification de pare-feu, accordez l'accès car l'application `func` doit pouvoir lire et écrire sur votre réseau.
> ⚠️ Si vous utilisez macOS, il peut y avoir des avertissements dans la sortie :
>
> ```output
    > (.venv) ➜  soil-moisture-trigger func start
    > Found Python version 3.9.1 (python3).
    >
    > Azure Functions Core Tools
    > Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    > Function Runtime Version: 3.0.15417.0
    >
    > [2021-06-16T08:18:28.315Z] Cannot create directory for shared memory usage: /dev/shm/AzureFunctions
    > [2021-06-16T08:18:28.316Z] System.IO.FileSystem: Access to the path '/dev/shm/AzureFunctions' is denied. Operation not permitted.
    > [2021-06-16T08:18:30.361Z] No job functions found.
    > ```
>
> Vous pouvez les ignorer tant que l'application Functions démarre correctement et liste les fonctions en cours d'exécution. Comme mentionné dans [cette question sur le Microsoft Docs Q&A](https://docs.microsoft.com/answers/questions/396617/azure-functions-core-tools-error-osx-devshmazurefu.html?WT.mc_id=academic-17441-jabenn), cela peut être ignoré.

1. Arrêtez l'application Functions en appuyant sur `ctrl+c`.

1. Ouvrez le dossier actuel dans VS Code, soit en ouvrant VS Code puis ce dossier, soit en exécutant la commande suivante :

    ```sh
    code .
    ```

    VS Code détectera votre projet Functions et affichera une notification indiquant :

    ```output
    Detected an Azure Functions Project in folder "soil-moisture-trigger" that may have been created outside of
    VS Code. Initialize for optimal use with VS Code?
    ```

    ![La notification](../../../../../translated_images/fr/vscode-azure-functions-init-notification.bd19b49229963edb.webp)

    Sélectionnez **Oui** dans cette notification.

1. Assurez-vous que l'environnement virtuel Python est actif dans le terminal de VS Code. Terminez-le et redémarrez-le si nécessaire.

## Créer un déclencheur d'événement IoT Hub

L'application Functions est l'enveloppe de votre code serverless. Pour répondre aux événements IoT Hub, vous pouvez ajouter un déclencheur IoT Hub à cette application. Ce déclencheur doit se connecter au flux de messages envoyés au IoT Hub et y répondre. Pour obtenir ce flux de messages, votre déclencheur doit se connecter au *point de terminaison compatible Event Hub* du IoT Hub.

IoT Hub repose sur un autre service Azure appelé Azure Event Hubs. Event Hubs est un service qui permet d'envoyer et de recevoir des messages, et IoT Hub étend cela en ajoutant des fonctionnalités pour les appareils IoT. La manière de se connecter pour lire les messages du IoT Hub est la même que si vous utilisiez Event Hubs.

✅ Faites des recherches : Lisez l'aperçu des Event Hubs dans la [documentation Azure Event Hubs](https://docs.microsoft.com/azure/event-hubs/event-hubs-about?WT.mc_id=academic-17441-jabenn). Comment les fonctionnalités de base se comparent-elles à celles du IoT Hub ?

Pour qu'un appareil IoT se connecte au IoT Hub, il doit utiliser une clé secrète qui garantit que seuls les appareils autorisés peuvent se connecter. Il en va de même pour la connexion pour lire les messages : votre code aura besoin d'une chaîne de connexion contenant une clé secrète ainsi que les détails du IoT Hub.

> 💁 La chaîne de connexion par défaut que vous obtenez dispose des permissions **iothubowner**, ce qui donne à tout code qui l'utilise des permissions complètes sur le IoT Hub. Idéalement, vous devriez vous connecter avec le niveau de permissions le plus bas nécessaire. Cela sera abordé dans la prochaine leçon.

Une fois que votre déclencheur est connecté, le code à l'intérieur de la fonction sera appelé pour chaque message envoyé au IoT Hub, quel que soit l'appareil qui l'a envoyé. Le déclencheur recevra le message en tant que paramètre.

### Tâche - Obtenir la chaîne de connexion du point de terminaison compatible Event Hub

1. Depuis le terminal de VS Code, exécutez la commande suivante pour obtenir la chaîne de connexion du point de terminaison compatible Event Hub du IoT Hub :

    ```sh
    az iot hub connection-string show --default-eventhub \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    Remplacez `<hub_name>` par le nom que vous avez utilisé pour votre IoT Hub.

1. Dans VS Code, ouvrez le fichier `local.settings.json`. Ajoutez la valeur suivante dans la section `Values` :

    ```json
    "IOT_HUB_CONNECTION_STRING": "<connection string>"
    ```

    Remplacez `<connection string>` par la valeur obtenue à l'étape précédente. Vous devrez ajouter une virgule après la ligne précédente pour que ce soit un JSON valide.

### Tâche - Créer un déclencheur d'événement

Vous êtes maintenant prêt à créer le déclencheur d'événement.

1. Depuis le terminal de VS Code, exécutez la commande suivante depuis le dossier `soil-moisture-trigger` :

    ```sh
    func new --name iot-hub-trigger --template "Azure Event Hub trigger"
    ```

    Cela crée une nouvelle fonction appelée `iot-hub-trigger`. Le déclencheur se connectera au point de terminaison compatible Event Hub du IoT Hub, vous permettant d'utiliser un déclencheur Event Hub. Il n'existe pas de déclencheur spécifique pour IoT Hub.

Cela créera un dossier dans le dossier `soil-moisture-trigger` appelé `iot-hub-trigger`, qui contiendra cette fonction. Ce dossier contiendra les fichiers suivants :

* `__init__.py` - il s'agit du fichier de code Python contenant le déclencheur, en utilisant la convention de nommage standard des fichiers Python pour transformer ce dossier en module Python.

    Ce fichier contiendra le code suivant :

    ```python
    import logging

    import azure.functions as func


    def main(event: func.EventHubEvent):
        logging.info('Python EventHub trigger processed an event: %s',
                    event.get_body().decode('utf-8'))
    ```

    Le cœur du déclencheur est la fonction `main`. C'est cette fonction qui est appelée avec les événements provenant du IoT Hub. Cette fonction a un paramètre appelé `event` qui contient un `EventHubEvent`. Chaque fois qu'un message est envoyé au IoT Hub, cette fonction est appelée en passant ce message comme `event`, ainsi que des propriétés similaires aux annotations vues dans la leçon précédente.

    Le cœur de cette fonction consigne l'événement.

* `function.json` - ce fichier contient la configuration du déclencheur. La configuration principale se trouve dans une section appelée `bindings`. Un binding est le terme utilisé pour désigner une connexion entre Azure Functions et d'autres services Azure. Cette fonction a un binding d'entrée vers un Event Hub - elle se connecte à un Event Hub et reçoit des données.

    > 💁 Vous pouvez également avoir des bindings de sortie pour que la sortie d'une fonction soit envoyée à un autre service. Par exemple, vous pourriez ajouter un binding de sortie vers une base de données et renvoyer l'événement IoT Hub depuis la fonction, et il serait automatiquement inséré dans la base de données.

    ✅ Faites des recherches : Lisez à propos des bindings dans la [documentation sur les concepts de déclencheurs et bindings Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python).

    La section `bindings` inclut la configuration du binding. Les valeurs importantes sont :

  * `"type": "eventHubTrigger"` - cela indique à la fonction qu'elle doit écouter les événements d'un Event Hub
  * `"name": "events"` - c'est le nom du paramètre à utiliser pour les événements Event Hub. Cela correspond au nom du paramètre dans la fonction `main` du code Python.
  * `"direction": "in"` - il s'agit d'un binding d'entrée, les données de l'Event Hub entrent dans la fonction
  * `"connection": ""` - cela définit le nom du paramètre à lire pour obtenir la chaîne de connexion. Lors de l'exécution locale, ce paramètre sera lu depuis le fichier `local.settings.json`.

    > 💁 La chaîne de connexion ne peut pas être stockée dans le fichier `function.json`, elle doit être lue depuis les paramètres. Cela permet d'éviter d'exposer accidentellement votre chaîne de connexion.

1. En raison [d'un bug dans le modèle Azure Functions](https://github.com/Azure/azure-functions-templates/issues/1250), le fichier `function.json` contient une valeur incorrecte pour le champ `cardinality`. Mettez à jour ce champ de `many` à `one` :

    ```json
    "cardinality": "one",
    ```

1. Mettez à jour la valeur de `"connection"` dans le fichier `function.json` pour pointer vers la nouvelle valeur ajoutée dans le fichier `local.settings.json` :

    ```json
    "connection": "IOT_HUB_CONNECTION_STRING",
    ```

    > 💁 Rappelez-vous - cela doit pointer vers le paramètre, et non contenir la chaîne de connexion réelle.

1. La chaîne de connexion contient la valeur `eventHubName`, donc la valeur correspondante dans le fichier `function.json` doit être vidée. Mettez à jour cette valeur pour qu'elle soit une chaîne vide :

    ```json
    "eventHubName": "",
    ```

### Tâche - Exécuter le déclencheur d'événement

1. Assurez-vous que le moniteur d'événements IoT Hub n'est pas en cours d'exécution. Si celui-ci fonctionne en même temps que l'application Functions, l'application Functions ne pourra pas se connecter et consommer les événements.

    > 💁 Plusieurs applications peuvent se connecter aux points de terminaison IoT Hub en utilisant différents *groupes de consommateurs*. Ceux-ci seront abordés dans une leçon ultérieure.

1. Pour exécuter l'application Functions, exécutez la commande suivante depuis le terminal de VS Code :

    ```sh
    func start
    ```

    L'application Functions démarrera et découvrira la fonction `iot-hub-trigger`. Elle traitera ensuite tous les événements déjà envoyés au IoT Hub au cours des dernières 24 heures.

    ```output
    (.venv) ➜  soil-moisture-trigger func start
    Found Python version 3.9.1 (python3).
    
    Azure Functions Core Tools
    Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    Function Runtime Version: 3.0.15417.0
    
    Functions:
    
            iot-hub-trigger: eventHubTrigger
    
    For detailed output, run func with --verbose flag.
    [2021-05-05T02:44:07.517Z] Worker process started and initialized.
    [2021-05-05T02:44:09.202Z] Executing 'Functions.iot-hub-trigger' (Reason='(null)', Id=802803a5-eae9-4401-a1f4-176631456ce4)
    [2021-05-05T02:44:09.205Z] Trigger Details: PartitionId: 0, Offset: 1011240-1011632, EnqueueTimeUtc: 2021-05-04T19:04:04.2030000Z-2021-05-04T19:04:04.3900000Z, SequenceNumber: 2546-2547, Count: 2
    [2021-05-05T02:44:09.352Z] Python EventHub trigger processed an event: {"soil_moisture":628}
    [2021-05-05T02:44:09.354Z] Python EventHub trigger processed an event: {"soil_moisture":624}
    [2021-05-05T02:44:09.395Z] Executed 'Functions.iot-hub-trigger' (Succeeded, Id=802803a5-eae9-4401-a1f4-176631456ce4, Duration=245ms)
    ```

    Chaque appel à la fonction sera entouré par un bloc `Executing 'Functions.iot-hub-trigger'`/`Executed 'Functions.iot-hub-trigger'` dans la sortie, ce qui vous permettra de voir combien de messages ont été traités dans chaque appel de fonction.

1. Assurez-vous que votre appareil IoT est en cours d'exécution. Vous verrez de nouveaux messages d'humidité du sol apparaître dans l'application Functions.

1. Arrêtez et redémarrez l'application Functions. Vous verrez qu'elle ne traitera pas les messages précédents à nouveau, mais uniquement les nouveaux messages.

> 💁 VS Code prend également en charge le débogage de vos fonctions. Vous pouvez définir des points d'arrêt en cliquant sur la bordure au début de chaque ligne de code, ou en plaçant le curseur sur une ligne de code et en sélectionnant *Exécuter -> Basculer le point d'arrêt*, ou en appuyant sur `F9`. Vous pouvez lancer le débogueur en sélectionnant *Exécuter -> Démarrer le débogage*, en appuyant sur `F5`, ou en sélectionnant le volet *Exécuter et déboguer* et en cliquant sur le bouton **Démarrer le débogage**. Cela vous permettra de voir les détails des événements traités.

#### Dépannage

* Si vous obtenez l'erreur suivante :

    ```output
    The listener for function 'Functions.iot-hub-trigger' was unable to start. Microsoft.WindowsAzure.Storage: Connection refused. System.Net.Http: Connection refused. System.Private.CoreLib: Connection refused.
    ```

    Vérifiez qu'Azurite est en cours d'exécution et que vous avez défini `AzureWebJobsStorage` dans le fichier `local.settings.json` sur `UseDevelopmentStorage=true`.

* Si vous obtenez l'erreur suivante :

    ```output
    System.Private.CoreLib: Exception while executing function: Functions.iot-hub-trigger. System.Private.CoreLib: Result: Failure Exception: AttributeError: 'list' object has no attribute 'get_body'
    ```

    Vérifiez que vous avez défini `cardinality` dans le fichier `function.json` sur `one`.

* Si vous obtenez l'erreur suivante :

    ```output
    Azure.Messaging.EventHubs: The path to an Event Hub may be specified as part of the connection string or as a separate value, but not both.  Please verify that your connection string does not have the `EntityPath` token if you are passing an explicit Event Hub name. (Parameter 'connectionString').
    ```

    Vérifiez que vous avez défini `eventHubName` dans le fichier `function.json` sur une chaîne vide.

## Envoyer des requêtes de méthode directe depuis un code serverless

Jusqu'à présent, votre application Functions écoute les messages du IoT Hub en utilisant le point de terminaison compatible Event Hub. Vous devez maintenant envoyer des commandes à l'appareil IoT. Cela se fait en utilisant une connexion différente au IoT Hub via le *Registry Manager*. Le Registry Manager est un outil qui vous permet de voir quels appareils sont enregistrés auprès du IoT Hub et de communiquer avec ces appareils en envoyant des messages cloud-to-device, des requêtes de méthode directe ou en mettant à jour le jumeau de l'appareil. Vous pouvez également l'utiliser pour enregistrer, mettre à jour ou supprimer des appareils IoT du IoT Hub.

Pour se connecter au Registry Manager, vous avez besoin d'une chaîne de connexion.

### Tâche - Obtenir la chaîne de connexion du Registry Manager

1. Pour obtenir la chaîne de connexion, exécutez la commande suivante :

    ```sh
    az iot hub connection-string show --policy-name service \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    Remplacez `<hub_name>` par le nom que vous avez utilisé pour votre IoT Hub.

    La chaîne de connexion est demandée pour la politique *ServiceConnect* en utilisant le paramètre `--policy-name service`. Lorsque vous demandez une chaîne de connexion, vous pouvez spécifier les permissions que cette chaîne de connexion autorisera. La politique ServiceConnect permet à votre code de se connecter et d'envoyer des messages aux appareils IoT.

    ✅ Faites des recherches : Lisez à propos des différentes politiques dans la [documentation sur les permissions IoT Hub](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-security#iot-hub-permissions?WT.mc_id=academic-17441-jabenn)

1. Dans VS Code, ouvrez le fichier `local.settings.json`. Ajoutez la valeur suivante dans la section `Values` :

    ```json
    "REGISTRY_MANAGER_CONNECTION_STRING": "<connection string>"
    ```

    Remplacez `<connection string>` par la valeur obtenue à l'étape précédente. Vous devrez ajouter une virgule après la ligne précédente pour que ce soit un JSON valide.

### Tâche - Envoyer une requête de méthode directe à un appareil

1. Le SDK pour le Registry Manager est disponible via un package Pip. Ajoutez la ligne suivante au fichier `requirements.txt` pour ajouter la dépendance à ce package :

    ```sh
    azure-iot-hub
    ```

1. Assurez-vous que le terminal de VS Code a l'environnement virtuel activé, et exécutez la commande suivante pour installer les packages Pip :

    ```sh
    pip install -r requirements.txt
    ```

1. Ajoutez les imports suivants au fichier `__init__.py` :

    ```python
    import json
    import os
    from azure.iot.hub import IoTHubRegistryManager
    from azure.iot.hub.models import CloudToDeviceMethod
    ```

    Cela importe certaines bibliothèques système, ainsi que les bibliothèques pour interagir avec le Registry Manager et envoyer des requêtes de méthode directe.

1. Supprimez le code à l'intérieur de la méthode `main`, mais conservez la méthode elle-même.

1. Dans la méthode `main`, ajoutez le code suivant :

    ```python
    body = json.loads(event.get_body().decode('utf-8'))
    device_id = event.iothub_metadata['connection-device-id']

    logging.info(f'Received message: {body} from {device_id}')
    ```

    Ce code extrait le corps de l'événement qui contient le message JSON envoyé par l'appareil IoT.

    Il récupère ensuite l'ID de l'appareil à partir des annotations passées avec le message. Le corps de l'événement contient le message envoyé en tant que télémétrie, et le dictionnaire `iothub_metadata` contient des propriétés définies par le IoT Hub, telles que l'ID de l'appareil expéditeur et l'heure d'envoi du message.

    Ces informations sont ensuite consignées. Vous verrez cette journalisation dans le terminal lorsque vous exécuterez l'application Function localement.

1. En dessous, ajoutez le code suivant :

    ```python
    soil_moisture = body['soil_moisture']

    if soil_moisture > 450:
        direct_method = CloudToDeviceMethod(method_name='relay_on', payload='{}')
    else:
        direct_method = CloudToDeviceMethod(method_name='relay_off', payload='{}')
    ```

    Ce code récupère l'humidité du sol à partir du message. Ensuite, en fonction de la valeur, il crée une classe d'assistance pour la requête de méthode directe pour les méthodes `relay_on` ou `relay_off`. La requête de méthode ne nécessite pas de charge utile, donc un document JSON vide est envoyé.

1. En dessous, ajoutez le code suivant :

    ```python
    logging.info(f'Sending direct method request for {direct_method.method_name} for device {device_id}')

    registry_manager_connection_string = os.environ['REGISTRY_MANAGER_CONNECTION_STRING']
    registry_manager = IoTHubRegistryManager(registry_manager_connection_string)
    ```
Ce code charge la variable `REGISTRY_MANAGER_CONNECTION_STRING` depuis le fichier `local.settings.json`. Les valeurs de ce fichier sont disponibles en tant que variables d'environnement, et elles peuvent être lues à l'aide de la fonction `os.environ`, une fonction qui retourne un dictionnaire contenant toutes les variables d'environnement.

> 💁 Lorsque ce code est déployé dans le cloud, les valeurs du fichier `local.settings.json` seront définies comme *Paramètres d'Application*, et elles pourront être lues à partir des variables d'environnement.

Le code crée ensuite une instance de la classe utilitaire Registry Manager en utilisant la chaîne de connexion.

1. Ajoutez le code suivant juste en dessous :

    ```python
    registry_manager.invoke_device_method(device_id, direct_method)

    logging.info('Direct method request sent!')
    ```

    Ce code indique au gestionnaire de registre d'envoyer une requête de méthode directe à l'appareil qui a envoyé la télémétrie.

    > 💁 Dans les versions de l'application que vous avez créées dans les leçons précédentes en utilisant MQTT, les commandes de contrôle du relais étaient envoyées à tous les appareils. Le code supposait que vous n'aviez qu'un seul appareil. Cette version du code envoie la requête de méthode à un seul appareil, ce qui fonctionne si vous avez plusieurs configurations de capteurs d'humidité et de relais, en envoyant la bonne requête de méthode directe au bon appareil.

1. Exécutez l'application Functions et assurez-vous que votre appareil IoT envoie des données. Vous verrez les messages être traités et les requêtes de méthode directe envoyées. Déplacez le capteur d'humidité du sol à l'intérieur et à l'extérieur du sol pour voir les valeurs changer et le relais s'allumer et s'éteindre.

> 💁 Vous pouvez trouver ce code dans le dossier [code/functions](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud/code/functions).

## Déployez votre code serverless dans le cloud

Votre code fonctionne maintenant localement, donc l'étape suivante consiste à déployer l'application Functions dans le cloud.

### Tâche - créer les ressources cloud

Votre application Functions doit être déployée dans une ressource Functions App dans Azure, située dans le groupe de ressources que vous avez créé pour votre IoT Hub. Vous aurez également besoin d'un compte de stockage créé dans Azure pour remplacer celui émulé localement.

1. Exécutez la commande suivante pour créer un compte de stockage :

    ```sh
    az storage account create --resource-group soil-moisture-sensor \
                              --sku Standard_LRS \
                              --name <storage_name> 
    ```

    Remplacez `<storage_name>` par un nom pour votre compte de stockage. Ce nom doit être unique au niveau mondial, car il fait partie de l'URL utilisée pour accéder au compte de stockage. Vous ne pouvez utiliser que des lettres minuscules et des chiffres pour ce nom, sans autres caractères, et il est limité à 24 caractères. Utilisez quelque chose comme `sms` et ajoutez un identifiant unique à la fin, comme des mots aléatoires ou votre nom.

    L'option `--sku Standard_LRS` sélectionne le niveau de tarification, en choisissant le compte général le moins cher. Il n'y a pas de niveau gratuit pour le stockage, et vous payez pour ce que vous utilisez. Les coûts sont relativement faibles, avec le stockage le plus cher à moins de 0,05 USD par mois par gigaoctet stocké.

    ✅ Consultez les tarifs sur la [page de tarification des comptes de stockage Azure](https://azure.microsoft.com/pricing/details/storage/?WT.mc_id=academic-17441-jabenn).

1. Exécutez la commande suivante pour créer une application Functions :

    ```sh
    az functionapp create --resource-group soil-moisture-sensor \
                          --runtime python \
                          --functions-version 3 \
                          --os-type Linux \
                          --consumption-plan-location <location> \
                          --storage-account <storage_name> \
                          --name <functions_app_name>
    ```

    Remplacez `<location>` par l'emplacement que vous avez utilisé lors de la création du groupe de ressources dans la leçon précédente.

    Remplacez `<storage_name>` par le nom du compte de stockage que vous avez créé à l'étape précédente.

    Remplacez `<functions_app_name>` par un nom unique pour votre application Functions. Ce nom doit être unique au niveau mondial, car il fait partie d'une URL qui peut être utilisée pour accéder à l'application Functions. Utilisez quelque chose comme `soil-moisture-sensor-` et ajoutez un identifiant unique à la fin, comme des mots aléatoires ou votre nom.

    L'option `--functions-version 3` définit la version d'Azure Functions à utiliser. La version 3 est la dernière version.

    L'option `--os-type Linux` indique au runtime Functions d'utiliser Linux comme système d'exploitation pour héberger ces fonctions. Les fonctions peuvent être hébergées sur Linux ou Windows, selon le langage de programmation utilisé. Les applications Python ne sont prises en charge que sur Linux.

### Tâche - téléchargez vos paramètres d'application

Lorsque vous avez développé votre application Functions, vous avez stocké certains paramètres dans le fichier `local.settings.json` pour les chaînes de connexion de votre IoT Hub. Ces paramètres doivent être écrits dans les Paramètres d'Application de votre application Functions dans Azure afin qu'ils puissent être utilisés par votre code.

> 🎓 Le fichier `local.settings.json` est uniquement destiné aux paramètres de développement local, et il ne doit pas être ajouté au contrôle de version, comme GitHub. Lorsqu'il est déployé dans le cloud, les Paramètres d'Application sont utilisés. Les Paramètres d'Application sont des paires clé/valeur hébergées dans le cloud et sont lues à partir des variables d'environnement soit dans votre code, soit par le runtime lors de la connexion de votre code à IoT Hub.

1. Exécutez la commande suivante pour définir le paramètre `IOT_HUB_CONNECTION_STRING` dans les Paramètres d'Application de l'application Functions :

    ```sh
    az functionapp config appsettings set --resource-group soil-moisture-sensor \
                                          --name <functions_app_name> \
                                          --settings "IOT_HUB_CONNECTION_STRING=<connection string>"
    ```

    Remplacez `<functions_app_name>` par le nom que vous avez utilisé pour votre application Functions.

    Remplacez `<connection string>` par la valeur de `IOT_HUB_CONNECTION_STRING` de votre fichier `local.settings.json`.

1. Répétez l'étape ci-dessus, mais définissez la valeur de `REGISTRY_MANAGER_CONNECTION_STRING` sur la valeur correspondante de votre fichier `local.settings.json`.

Lorsque vous exécutez ces commandes, elles afficheront également une liste de tous les Paramètres d'Application pour l'application Functions. Vous pouvez utiliser cela pour vérifier que vos valeurs sont correctement définies.

> 💁 Vous verrez une valeur déjà définie pour `AzureWebJobsStorage`. Dans votre fichier `local.settings.json`, cela était défini sur une valeur pour utiliser l'émulateur de stockage local. Lorsque vous avez créé l'application Functions, vous avez passé le compte de stockage en paramètre, et cela est automatiquement défini dans ce paramètre.

### Tâche - déployez votre application Functions dans le cloud

Maintenant que l'application Functions est prête, votre code peut être déployé.

1. Exécutez la commande suivante depuis le terminal de VS Code pour publier votre application Functions :

    ```sh
    func azure functionapp publish <functions_app_name>
    ```

    Remplacez `<functions_app_name>` par le nom que vous avez utilisé pour votre application Functions.

Le code sera empaqueté et envoyé à l'application Functions, où il sera déployé et démarré. Il y aura beaucoup de sorties dans la console, se terminant par une confirmation du déploiement et une liste des fonctions déployées. Dans ce cas, la liste ne contiendra que le déclencheur.

```output
Deployment successful.
Remote build succeeded!
Syncing triggers...
Functions in soil-moisture-sensor:
    iot-hub-trigger - [eventHubTrigger]
```

Assurez-vous que votre appareil IoT est en cours d'exécution. Modifiez les niveaux d'humidité en ajustant l'humidité du sol ou en déplaçant le capteur à l'intérieur et à l'extérieur du sol. Vous verrez le relais s'allumer et s'éteindre en fonction des changements d'humidité du sol.

---

## 🚀 Défi

Dans la leçon précédente, vous avez géré le timing pour le relais en vous désabonnant des messages MQTT pendant que le relais était activé, et pendant un court moment après qu'il ait été désactivé. Vous ne pouvez pas utiliser cette méthode ici - vous ne pouvez pas désactiver votre déclencheur IoT Hub.

Réfléchissez à différentes façons de gérer cela dans votre application Functions.

## Quiz post-lecture

[Quiz post-lecture](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/18)

## Revue & Auto-apprentissage

* Lisez sur le calcul serverless sur la [page Serverless Computing de Wikipédia](https://wikipedia.org/wiki/Serverless_computing).
* Lisez sur l'utilisation du serverless dans Azure, y compris d'autres exemples, dans le [billet de blog Azure "Go serverless for your IoT needs"](https://azure.microsoft.com/blog/go-serverless-for-your-iot-needs/?WT.mc_id=academic-17441-jabenn).
* Apprenez-en plus sur Azure Functions sur la [chaîne YouTube Azure Functions](https://www.youtube.com/c/AzureFunctions).

## Devoir

[Ajoutez un contrôle manuel du relais](assignment.md)

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction professionnelle réalisée par un humain. Nous ne sommes pas responsables des malentendus ou des interprétations erronées résultant de l'utilisation de cette traduction.