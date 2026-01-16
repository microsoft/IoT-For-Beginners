<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4d8e7a066d75b625e7a979c14157041d",
  "translation_date": "2025-08-24T22:44:01+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/README.md",
  "language_code": "fr"
}
-->
# Migrez votre plante vers le cloud

![Un aperçu illustré de cette leçon](../../../../../translated_images/fr/lesson-8.3f21f3c11159e6a0a376351973ea5724d5de68fa23b4288853a174bed9ac48c3.jpg)

> Illustration par [Nitya Narasimhan](https://github.com/nitya). Cliquez sur l'image pour une version agrandie.

Cette leçon a été enseignée dans le cadre de la série [IoT for Beginners Project 2 - Digital Agriculture](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) du [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn).

[![Connectez votre appareil au cloud avec Azure IoT Hub](https://img.youtube.com/vi/bNxjopXkhvk/0.jpg)](https://youtu.be/bNxjopXkhvk)

## Quiz avant la leçon

[Quiz avant la leçon](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/15)

## Introduction

Dans la dernière leçon, vous avez appris à connecter votre plante à un broker MQTT et à contrôler un relais à partir d'un code serveur exécuté localement. Cela constitue le cœur d'un système d'arrosage automatisé connecté à Internet, utilisé aussi bien pour des plantes individuelles à domicile que pour des exploitations agricoles commerciales.

L'appareil IoT communiquait avec un broker MQTT public pour illustrer les principes, mais ce n'est ni la méthode la plus fiable ni la plus sécurisée. Dans cette leçon, vous découvrirez le cloud et les capacités IoT offertes par les services cloud publics. Vous apprendrez également à migrer votre plante vers l'un de ces services cloud à partir du broker MQTT public.

Dans cette leçon, nous aborderons :

* [Qu'est-ce que le cloud ?](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Créer un abonnement cloud](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Services IoT dans le cloud](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Créer un service IoT dans le cloud](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Communiquer avec IoT Hub](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Connecter votre appareil au service IoT](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)

## Qu'est-ce que le cloud ?

Avant l'arrivée du cloud, lorsqu'une entreprise souhaitait fournir des services à ses employés (comme des bases de données ou du stockage de fichiers) ou au public (comme des sites web), elle devait construire et gérer un centre de données. Cela pouvait aller d'une simple salle avec quelques ordinateurs à un bâtiment entier rempli de machines. L'entreprise devait tout gérer, y compris :

* L'achat des ordinateurs
* La maintenance du matériel
* L'alimentation électrique et le refroidissement
* Le réseau
* La sécurité, tant pour le bâtiment que pour les logiciels sur les ordinateurs
* L'installation et les mises à jour des logiciels

Cela pouvait être très coûteux, nécessiter une large gamme de compétences et être très lent à adapter en cas de besoin. Par exemple, si une boutique en ligne devait se préparer pour une saison de fêtes chargée, elle devait planifier des mois à l'avance pour acheter du matériel supplémentaire, le configurer, installer les logiciels nécessaires, etc. Une fois la saison terminée et les ventes redescendues, les ordinateurs achetés restaient inutilisés jusqu'à la prochaine période de forte activité.

✅ Pensez-vous que cela permettrait aux entreprises d'agir rapidement ? Si un détaillant de vêtements en ligne devenait soudainement populaire parce qu'une célébrité portait ses vêtements, pourrait-il augmenter rapidement sa puissance de calcul pour gérer l'afflux soudain de commandes ?

### L'ordinateur de quelqu'un d'autre

Le cloud est souvent décrit avec humour comme "l'ordinateur de quelqu'un d'autre". L'idée initiale était simple : au lieu d'acheter des ordinateurs, vous louez ceux de quelqu'un d'autre. Un fournisseur de cloud computing gère d'immenses centres de données. Il s'occupe de tout : achat et installation du matériel, gestion de l'alimentation et du refroidissement, réseau, sécurité des bâtiments, mises à jour matérielles et logicielles, etc. En tant que client, vous louez les ordinateurs dont vous avez besoin, en augmentant la location lorsque la demande augmente, et en la réduisant lorsque la demande diminue. Ces centres de données cloud sont répartis dans le monde entier.

![Un centre de données cloud Microsoft](../../../../../translated_images/fr/azure-region-existing.73f704604f2aa6cb9b5a49ed40e93d4fd81ae3f4e6af4a8ca504023902832f56.png)
![Une expansion planifiée d'un centre de données cloud Microsoft](../../../../../translated_images/fr/azure-region-planned-expansion.a5074a1e8af74f156a73552d502429e5b126ea5019274d767ecb4b9afdad442b.png)

Ces centres de données peuvent couvrir plusieurs kilomètres carrés. Les images ci-dessus montrent un centre de données cloud Microsoft il y a quelques années, ainsi qu'une expansion planifiée. La zone dégagée pour l'expansion couvre plus de 5 kilomètres carrés.

> 💁 Ces centres de données nécessitent tellement d'énergie que certains ont leurs propres centrales électriques. En raison de leur taille et des investissements réalisés par les fournisseurs de cloud, ils sont généralement très respectueux de l'environnement. Ils sont plus efficaces que de nombreux petits centres de données, fonctionnent principalement avec des énergies renouvelables, et les fournisseurs de cloud travaillent dur pour réduire les déchets, limiter l'utilisation de l'eau et replanter des forêts pour compenser celles abattues pour construire les centres. Vous pouvez en savoir plus sur les efforts de durabilité d'un fournisseur de cloud sur le [site de durabilité Azure](https://azure.microsoft.com/global-infrastructure/sustainability/?WT.mc_id=academic-17441-jabenn).

✅ Faites des recherches : Consultez les principaux clouds comme [Azure de Microsoft](https://azure.microsoft.com/?WT.mc_id=academic-17441-jabenn) ou [GCP de Google](https://cloud.google.com). Combien de centres de données possèdent-ils et où sont-ils situés dans le monde ?

L'utilisation du cloud permet aux entreprises de réduire leurs coûts et de se concentrer sur leur cœur de métier, en laissant l'expertise en cloud computing au fournisseur. Les entreprises n'ont plus besoin de louer ou d'acheter des espaces de centres de données, de payer différents fournisseurs pour la connectivité et l'énergie, ou d'employer des experts. Elles peuvent simplement payer une facture mensuelle au fournisseur de cloud pour que tout soit pris en charge.

Le fournisseur de cloud peut alors utiliser des économies d'échelle pour réduire les coûts, acheter des ordinateurs en gros à des prix plus bas, investir dans des outils pour réduire leur charge de maintenance, et même concevoir et fabriquer leur propre matériel pour améliorer leur offre cloud.

### Microsoft Azure

Azure est le cloud pour développeurs de Microsoft, et c'est le cloud que vous utiliserez dans ces leçons. La vidéo ci-dessous donne un aperçu rapide d'Azure :

[![Vidéo d'introduction à Azure](../../../../../translated_images/fr/what-is-azure-video-thumbnail.20174db09e03bbb8.webp)](https://www.microsoft.com/videoplayer/embed/RE4Ibng?WT.mc_id=academic-17441-jabenn)

## Créer un abonnement cloud

Pour utiliser des services dans le cloud, vous devez vous inscrire à un abonnement auprès d'un fournisseur de cloud. Dans cette leçon, vous allez vous inscrire à un abonnement Microsoft Azure. Si vous avez déjà un abonnement Azure, vous pouvez passer cette tâche. Les détails de l'abonnement décrits ici sont corrects au moment de la rédaction, mais peuvent changer.

> 💁 Si vous accédez à ces leçons via votre école, vous avez peut-être déjà un abonnement Azure disponible. Vérifiez auprès de votre enseignant.

Il existe deux types d'abonnements gratuits Azure auxquels vous pouvez vous inscrire :

* **Azure pour les étudiants** - Cet abonnement est conçu pour les étudiants de 18 ans et plus. Vous n'avez pas besoin de carte de crédit pour vous inscrire, et vous utilisez votre adresse e-mail scolaire pour valider que vous êtes étudiant. Lorsque vous vous inscrivez, vous recevez 100 $ US à dépenser sur les ressources cloud, ainsi que des services gratuits, y compris une version gratuite d'un service IoT. Cela dure 12 mois, et vous pouvez renouveler chaque année tant que vous restez étudiant.

* **Abonnement gratuit Azure** - Cet abonnement est destiné à toute personne qui n'est pas étudiant. Vous aurez besoin d'une carte de crédit pour vous inscrire, mais votre carte ne sera pas débitée, elle est simplement utilisée pour vérifier que vous êtes une vraie personne et non un robot. Vous recevez 200 $ de crédit à utiliser dans les 30 premiers jours sur n'importe quel service, ainsi que des niveaux gratuits de services Azure. Une fois votre crédit épuisé, votre carte ne sera pas débitée sauf si vous convertissez en abonnement à la consommation.

> 💁 Microsoft propose un abonnement Azure pour les étudiants Starter pour les étudiants de moins de 18 ans, mais au moment de la rédaction, il ne prend pas en charge les services IoT.

### Tâche - s'inscrire à un abonnement cloud gratuit

Si vous êtes étudiant âgé de 18 ans ou plus, vous pouvez vous inscrire à un abonnement Azure pour les étudiants. Vous devrez valider avec une adresse e-mail scolaire. Vous pouvez le faire de deux manières :

* Inscrivez-vous au pack développeur étudiant GitHub à [education.github.com/pack](https://education.github.com/pack). Cela vous donne accès à une gamme d'outils et d'offres, y compris GitHub et Microsoft Azure. Une fois inscrit au pack développeur, vous pouvez activer l'offre Azure pour les étudiants.

* Inscrivez-vous directement à un compte Azure pour les étudiants sur [azure.microsoft.com/free/students](https://azure.microsoft.com/free/students/?WT.mc_id=academic-17441-jabenn).

> ⚠️ Si votre adresse e-mail scolaire n'est pas reconnue, ouvrez une [issue dans ce dépôt](https://github.com/Microsoft/IoT-For-Beginners/issues) et nous verrons si elle peut être ajoutée à la liste autorisée Azure pour les étudiants.

Si vous n'êtes pas étudiant ou si vous n'avez pas d'adresse e-mail scolaire valide, vous pouvez vous inscrire à un abonnement gratuit Azure.

* Inscrivez-vous à un abonnement gratuit Azure sur [azure.microsoft.com/free](https://azure.microsoft.com/free/?WT.mc_id=academic-17441-jabenn)

## Services IoT dans le cloud

Le broker MQTT public que vous avez utilisé est un excellent outil pour apprendre, mais il présente plusieurs inconvénients pour une utilisation commerciale :

* Fiabilité - c'est un service gratuit sans garanties, qui peut être désactivé à tout moment
* Sécurité - il est public, donc n'importe qui pourrait écouter vos données ou envoyer des commandes pour contrôler votre matériel
* Performance - il est conçu pour un petit nombre de messages de test, donc il ne pourrait pas gérer un grand volume de messages
* Découverte - il n'y a aucun moyen de savoir quels appareils sont connectés

Les services IoT dans le cloud résolvent ces problèmes. Ils sont maintenus par de grands fournisseurs de cloud qui investissent massivement dans la fiabilité et sont prêts à résoudre tout problème qui pourrait survenir. Ils intègrent la sécurité pour empêcher les pirates de lire vos données ou d'envoyer des commandes malveillantes. Ils offrent également des performances élevées, capables de gérer des millions de messages chaque jour, en tirant parti du cloud pour s'adapter aux besoins.

> 💁 Bien que ces avantages aient un coût mensuel, la plupart des fournisseurs de cloud proposent une version gratuite de leur service IoT avec un nombre limité de messages par jour ou d'appareils pouvant se connecter. Cette version gratuite est généralement plus que suffisante pour qu'un développeur apprenne à utiliser le service. Dans cette leçon, vous utiliserez une version gratuite.

Les appareils IoT se connectent à un service cloud soit en utilisant un SDK pour appareils (une bibliothèque qui fournit du code pour travailler avec les fonctionnalités du service), soit directement via un protocole de communication tel que MQTT ou HTTP. Le SDK pour appareils est généralement la voie la plus simple, car il gère tout pour vous, comme les sujets à publier ou à souscrire, et la gestion de la sécurité.

![Les appareils se connectent à un service en utilisant un SDK pour appareils. Le code serveur se connecte également au service via un SDK](../../../../../translated_images/fr/iot-service-connectivity.7e873847921a5d6fd60d0ba3a943210194518cee0d4e362476624316443275c3.png)

Votre appareil communique ensuite avec d'autres parties de votre application via ce service - de manière similaire à la façon dont vous avez envoyé des données et reçu des commandes via MQTT. Cela se fait généralement en utilisant un SDK pour services ou une bibliothèque similaire. Les messages proviennent de votre appareil vers le service, où d'autres composants de votre application peuvent les lire, et des messages peuvent ensuite être renvoyés à votre appareil.

![Les appareils sans clé secrète valide ne peuvent pas se connecter au service IoT](../../../../../translated_images/fr/iot-service-allowed-denied-connection.818b0063ac213fb84204a7229303764d9b467ca430fb822b4ac2fca267d56726.png)

Ces services mettent en œuvre la sécurité en connaissant tous les appareils qui peuvent se connecter et envoyer des données, soit en enregistrant les appareils à l'avance, soit en leur fournissant des clés secrètes ou des certificats qu'ils peuvent utiliser pour s'enregistrer eux-mêmes lors de leur première connexion. Les appareils inconnus ne peuvent pas se connecter ; s'ils essaient, le service rejette la connexion et ignore les messages envoyés par eux.

✅ Faites des recherches : Quels sont les inconvénients d'avoir un service IoT ouvert où n'importe quel appareil ou code peut se connecter ? Pouvez-vous trouver des exemples spécifiques de pirates exploitant cette situation ?

D'autres composants de votre application peuvent se connecter au service IoT, obtenir des informations sur tous les appareils connectés ou enregistrés, et communiquer directement avec eux, soit individuellement, soit en masse.
💁 Les services IoT implémentent également des fonctionnalités supplémentaires, et les fournisseurs de cloud proposent des services et applications supplémentaires qui peuvent être connectés au service. Par exemple, si vous souhaitez stocker tous les messages de télémétrie envoyés par tous les appareils dans une base de données, il suffit généralement de quelques clics dans l'outil de configuration du fournisseur de cloud pour connecter le service à une base de données et y transférer les données.
## Créer un service IoT dans le cloud

Maintenant que vous avez un abonnement Azure, vous pouvez vous inscrire à un service IoT. Le service IoT de Microsoft s'appelle Azure IoT Hub.

![Le logo Azure IoT Hub](../../../../../translated_images/fr/azure-iot-hub-logo.28a19de76d0a1932464d858f7558712bcdace3e5ec69c434d482ed7ce41c3a26.png)

La vidéo ci-dessous donne un aperçu rapide d'Azure IoT Hub :

[![Vidéo d'aperçu d'Azure IoT Hub](https://img.youtube.com/vi/smuZaZZXKsU/0.jpg)](https://www.youtube.com/watch?v=smuZaZZXKsU)

> 🎥 Cliquez sur l'image ci-dessus pour regarder la vidéo

✅ Prenez un moment pour faire des recherches et lire l'aperçu d'IoT Hub dans la [documentation Microsoft IoT Hub](https://docs.microsoft.com/azure/iot-hub/about-iot-hub?WT.mc_id=academic-17441-jabenn).

Les services cloud disponibles dans Azure peuvent être configurés via un portail web ou une interface en ligne de commande (CLI). Pour cette tâche, vous utiliserez la CLI.

### Tâche - installer Azure CLI

Pour utiliser Azure CLI, vous devez d'abord l'installer sur votre PC ou Mac.

1. Suivez les instructions dans la [documentation Azure CLI](https://docs.microsoft.com/cli/azure/install-azure-cli?WT.mc_id=academic-17441-jabenn) pour installer la CLI.

1. Azure CLI prend en charge plusieurs extensions qui ajoutent des fonctionnalités pour gérer une large gamme de services Azure. Installez l'extension IoT en exécutant la commande suivante depuis votre ligne de commande ou terminal :

    ```sh
    az extension add --name azure-iot
    ```

1. Depuis votre ligne de commande ou terminal, exécutez la commande suivante pour vous connecter à votre abonnement Azure via Azure CLI.

    ```sh
    az login
    ```

    Une page web sera lancée dans votre navigateur par défaut. Connectez-vous en utilisant le compte que vous avez utilisé pour vous inscrire à votre abonnement Azure. Une fois connecté, vous pouvez fermer l'onglet du navigateur.

1. Si vous avez plusieurs abonnements Azure, comme un abonnement fourni par votre école et votre propre abonnement Azure pour les étudiants, vous devrez sélectionner celui que vous souhaitez utiliser. Exécutez la commande suivante pour lister tous les abonnements auxquels vous avez accès :

    ```sh
    az account list --output table
    ```

    Dans la sortie, vous verrez le nom de chaque abonnement ainsi que son `SubscriptionId`.

    ```output
    ➜  ~ az account list --output table
    Name                    CloudName    SubscriptionId                        State    IsDefault
    ----------------------  -----------  ------------------------------------  -------  -----------
    School-subscription     AzureCloud   cb30cde9-814a-42f0-a111-754cb788e4e1  Enabled  True
    Azure for Students      AzureCloud   fa51c31b-162c-4599-add6-781def2e1fbf  Enabled  False
    ```

    Pour sélectionner l'abonnement que vous souhaitez utiliser, utilisez la commande suivante :

    ```sh
    az account set --subscription <SubscriptionId>
    ```

    Remplacez `<SubscriptionId>` par l'Id de l'abonnement que vous souhaitez utiliser. Après avoir exécuté cette commande, réexécutez la commande pour lister vos comptes. Vous verrez que la colonne `IsDefault` sera marquée comme `True` pour l'abonnement que vous venez de définir.

### Tâche - créer un groupe de ressources

Les services Azure, tels que les instances IoT Hub, les machines virtuelles, les bases de données ou les services d'IA, sont appelés **ressources**. Chaque ressource doit appartenir à un **groupe de ressources**, un regroupement logique d'une ou plusieurs ressources.

> 💁 Utiliser des groupes de ressources permet de gérer plusieurs services à la fois. Par exemple, une fois que vous avez terminé toutes les leçons de ce projet, vous pouvez supprimer le groupe de ressources, et toutes les ressources qu'il contient seront supprimées automatiquement.

1. Il existe plusieurs centres de données Azure dans le monde, répartis en régions. Lorsque vous créez une ressource ou un groupe de ressources Azure, vous devez spécifier où vous souhaitez qu'il soit créé. Exécutez la commande suivante pour obtenir la liste des emplacements :

    ```sh
    az account list-locations --output table
    ```

    Vous verrez une liste d'emplacements. Cette liste sera longue.

    > 💁 Au moment de la rédaction, il y a 65 emplacements où vous pouvez déployer.

    ```output
        ➜  ~ az account list-locations --output table
    DisplayName               Name                 RegionalDisplayName
    ------------------------  -------------------  -------------------------------------
    East US                   eastus               (US) East US
    East US 2                 eastus2              (US) East US 2
    South Central US          southcentralus       (US) South Central US
    ...
    ```

    Notez la valeur de la colonne `Name` de la région la plus proche de vous. Vous pouvez trouver les régions sur une carte sur la [page des géographies Azure](https://azure.microsoft.com/global-infrastructure/geographies/?WT.mc_id=academic-17441-jabenn).

1. Exécutez la commande suivante pour créer un groupe de ressources appelé `soil-moisture-sensor`. Les noms des groupes de ressources doivent être uniques dans votre abonnement.

    ```sh
    az group create --name soil-moisture-sensor \
                    --location <location>
    ```

    Remplacez `<location>` par l'emplacement que vous avez sélectionné à l'étape précédente.

### Tâche - créer un IoT Hub

Vous pouvez maintenant créer une ressource IoT Hub dans votre groupe de ressources.

1. Utilisez la commande suivante pour créer votre ressource IoT Hub :

    ```sh
    az iot hub create --resource-group soil-moisture-sensor \
                      --sku F1 \
                      --partition-count 2 \
                      --name <hub_name>
    ```

    Remplacez `<hub_name>` par un nom pour votre hub. Ce nom doit être globalement unique - aucun autre IoT Hub créé par quelqu'un d'autre ne peut avoir le même nom. Ce nom est utilisé dans une URL qui pointe vers le hub, donc il doit être unique. Utilisez quelque chose comme `soil-moisture-sensor-` et ajoutez un identifiant unique à la fin, comme des mots aléatoires ou votre nom.

    L'option `--sku F1` indique qu'il faut utiliser un niveau gratuit. Le niveau gratuit prend en charge 8 000 messages par jour ainsi que la plupart des fonctionnalités des niveaux payants.

    > 🎓 Les différents niveaux de tarification des services Azure sont appelés tiers. Chaque tier a un coût différent et offre différentes fonctionnalités ou volumes de données.

    > 💁 Si vous souhaitez en savoir plus sur les prix, vous pouvez consulter le [guide des prix Azure IoT Hub](https://azure.microsoft.com/pricing/details/iot-hub/?WT.mc_id=academic-17441-jabenn).

    L'option `--partition-count 2` définit combien de flux de données le IoT Hub prend en charge. Plus de partitions réduisent les blocages de données lorsque plusieurs éléments lisent et écrivent depuis le IoT Hub. Les partitions sont hors du cadre de ces leçons, mais cette valeur doit être définie pour créer un IoT Hub de niveau gratuit.

    > 💁 Vous ne pouvez avoir qu'un seul IoT Hub de niveau gratuit par abonnement.

Le IoT Hub sera créé. Cela peut prendre une minute ou deux pour se terminer.

## Communiquer avec IoT Hub

Dans la leçon précédente, vous avez utilisé MQTT et envoyé des messages sur différents topics, avec des topics ayant des objectifs différents. Plutôt que d'envoyer des messages sur différents topics, IoT Hub propose plusieurs façons définies pour que l'appareil communique avec le Hub, ou pour que le Hub communique avec l'appareil.

> 💁 En coulisses, cette communication entre IoT Hub et votre appareil peut utiliser MQTT, HTTPS ou AMQP.

* Messages de l'appareil vers le cloud (D2C) - ce sont des messages envoyés d'un appareil à IoT Hub, tels que des données de télémétrie. Ils peuvent ensuite être lus depuis IoT Hub par votre code d'application.

    > 🎓 En coulisses, IoT Hub utilise un service Azure appelé [Event Hubs](https://docs.microsoft.com/azure/event-hubs/?WT.mc_id=academic-17441-jabenn). Lorsque vous écrivez du code pour lire les messages envoyés au hub, ceux-ci sont souvent appelés événements.

* Messages du cloud vers l'appareil (C2D) - ce sont des messages envoyés depuis le code d'application, via un IoT Hub, à un appareil IoT.

* Requêtes de méthode directe - ce sont des messages envoyés depuis le code d'application via un IoT Hub à un appareil IoT pour demander à l'appareil de faire quelque chose, comme contrôler un actionneur. Ces messages nécessitent une réponse pour que votre code d'application puisse savoir s'ils ont été traités avec succès.

* Jumeaux d'appareils - ce sont des documents JSON synchronisés entre l'appareil et IoT Hub, et sont utilisés pour stocker des paramètres ou d'autres propriétés soit signalées par l'appareil, soit devant être définies sur l'appareil (appelées souhaitées) par IoT Hub.

IoT Hub peut stocker des messages et des requêtes de méthode directe pendant une période configurable (par défaut un jour), donc si un appareil ou un code d'application perd la connexion, il peut toujours récupérer les messages envoyés pendant qu'il était hors ligne après sa reconnexion. Les jumeaux d'appareils sont conservés en permanence dans IoT Hub, donc à tout moment un appareil peut se reconnecter et obtenir le dernier jumeau d'appareil.

✅ Faites des recherches : Lisez-en davantage sur ces types de messages dans les [directives de communication de l'appareil vers le cloud](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-d2c-guidance?WT.mc_id=academic-17441-jabenn), et les [directives de communication du cloud vers l'appareil](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-c2d-guidance?WT.mc_id=academic-17441-jabenn) dans la documentation IoT Hub.

## Connecter votre appareil au service IoT

Une fois le hub créé, votre appareil IoT peut s'y connecter. Seuls les appareils enregistrés peuvent se connecter à un service, donc vous devrez d'abord enregistrer votre appareil. Lors de l'enregistrement, vous pouvez obtenir une chaîne de connexion que l'appareil peut utiliser pour se connecter. Cette chaîne de connexion est spécifique à l'appareil et contient des informations sur IoT Hub, l'appareil, et une clé secrète qui permettra à cet appareil de se connecter.

> 🎓 Une chaîne de connexion est un terme générique pour un morceau de texte contenant des détails de connexion. Elles sont utilisées lors de la connexion à des IoT Hubs, des bases de données et de nombreux autres services. Elles contiennent généralement un identifiant pour le service, tel qu'une URL, et des informations de sécurité comme une clé secrète. Elles sont transmises aux SDK pour se connecter au service.

> ⚠️ Les chaînes de connexion doivent être conservées en sécurité ! La sécurité sera abordée plus en détail dans une leçon future.

### Tâche - enregistrer votre appareil IoT

L'appareil IoT peut être enregistré auprès de votre IoT Hub en utilisant Azure CLI.

1. Exécutez la commande suivante pour enregistrer un appareil :

    ```sh
    az iot hub device-identity create --device-id soil-moisture-sensor \
                                      --hub-name <hub_name>
    ```

    Remplacez `<hub_name>` par le nom que vous avez utilisé pour votre IoT Hub.

    Cela créera un appareil avec un ID de `soil-moisture-sensor`.

1. Lorsque votre appareil IoT se connecte à votre IoT Hub en utilisant le SDK, il doit utiliser une chaîne de connexion qui donne l'URL du hub, ainsi qu'une clé secrète. Exécutez la commande suivante pour obtenir la chaîne de connexion :

    ```sh
    az iot hub device-identity connection-string show --device-id soil-moisture-sensor \
                                                      --output table \
                                                      --hub-name <hub_name>
    ```

    Remplacez `<hub_name>` par le nom que vous avez utilisé pour votre IoT Hub.

1. Conservez la chaîne de connexion affichée dans la sortie car vous en aurez besoin plus tard.

### Tâche - connecter votre appareil IoT au cloud

Suivez le guide correspondant pour connecter votre appareil IoT au cloud :

* [Arduino - Wio Terminal](wio-terminal-connect-hub.md)
* [Ordinateur monocarte - Raspberry Pi/Appareil IoT virtuel](single-board-computer-connect-hub.md)

### Tâche - surveiller les événements

Pour l'instant, vous ne mettrez pas à jour votre code serveur. Vous pouvez utiliser Azure CLI pour surveiller les événements provenant de votre appareil IoT.

1. Assurez-vous que votre appareil IoT fonctionne et envoie des valeurs de télémétrie de l'humidité du sol.

1. Exécutez la commande suivante dans votre invite de commande ou terminal pour surveiller les messages envoyés à votre IoT Hub :

    ```sh
    az iot hub monitor-events --hub-name <hub_name>
    ```

    Remplacez `<hub_name>` par le nom que vous avez utilisé pour votre IoT Hub.

    Vous verrez des messages apparaître dans la sortie de la console au fur et à mesure qu'ils sont envoyés par votre appareil IoT.

    ```output
    Starting event monitor, use ctrl-c to stop...
    {
        "event": {
            "origin": "soil-moisture-sensor",
            "module": "",
            "interface": "",
            "component": "",
            "payload": "{\"soil_moisture\": 376}"
        }
    },
    {
        "event": {
            "origin": "soil-moisture-sensor",
            "module": "",
            "interface": "",
            "component": "",
            "payload": "{\"soil_moisture\": 381}"
        }
    }
    ```

    Le contenu du `payload` correspondra au message envoyé par votre appareil IoT.

    > Au moment de la rédaction, l'extension `az iot` ne fonctionne pas entièrement sur Apple Silicon. Si vous utilisez un appareil Apple Silicon, vous devrez surveiller les messages d'une autre manière, comme en utilisant les [outils Azure IoT pour Visual Studio Code](https://docs.microsoft.com/en-us/azure/iot-hub/iot-hub-vscode-iot-toolkit-cloud-device-messaging).

1. Ces messages ont un certain nombre de propriétés attachées automatiquement, telles que l'horodatage auquel ils ont été envoyés. Ces propriétés sont appelées *annotations*. Pour afficher toutes les annotations de message, utilisez la commande suivante :

    ```sh
    az iot hub monitor-events --properties anno --hub-name <hub_name>
    ```

    Remplacez `<hub_name>` par le nom que vous avez utilisé pour votre IoT Hub.

    Vous verrez des messages apparaître dans la sortie de la console au fur et à mesure qu'ils sont envoyés par votre appareil IoT.

    ```output
    Starting event monitor, use ctrl-c to stop...
    {
        "event": {
            "origin": "soil-moisture-sensor",
            "module": "",
            "interface": "",
            "component": "",
            "properties": {},
            "annotations": {
                "iothub-connection-device-id": "soil-moisture-sensor",
                "iothub-connection-auth-method": "{\"scope\":\"device\",\"type\":\"sas\",\"issuer\":\"iothub\",\"acceptingIpFilterRule\":null}",
                "iothub-connection-auth-generation-id": "637553997165220462",
                "iothub-enqueuedtime": 1619976150288,
                "iothub-message-source": "Telemetry",
                "x-opt-sequence-number": 1379,
                "x-opt-offset": "550576",
                "x-opt-enqueued-time": 1619976150277
            },
            "payload": "{\"soil_moisture\": 381}"
        }
    }
    ```

    Les valeurs temporelles dans les annotations sont en [temps UNIX](https://wikipedia.org/wiki/Unix_time), représentant le nombre de secondes depuis minuit le 1<sup>er</sup> janvier 1970.

    Quittez le moniteur d'événements lorsque vous avez terminé.

### Tâche - contrôler votre appareil IoT

Vous pouvez également utiliser Azure CLI pour appeler des méthodes directes sur votre appareil IoT.

1. Exécutez la commande suivante dans votre invite de commande ou terminal pour invoquer la méthode `relay_on` sur l'appareil IoT :

    ```sh
    az iot hub invoke-device-method --device-id soil-moisture-sensor \
                                    --method-name relay_on \
                                    --method-payload '{}' \
                                    --hub-name <hub_name>
    ```

    Remplacez `
<hub_name>
` avec le nom que vous avez utilisé pour votre IoT Hub.

    Cela envoie une requête de méthode directe pour la méthode spécifiée par `method-name`. Les méthodes directes peuvent inclure une charge utile contenant des données pour la méthode, et cela peut être spécifié dans le paramètre `method-payload` sous forme de JSON.

    Vous verrez le relais s'allumer, ainsi que la sortie correspondante de votre appareil IoT :

    ```output
    Direct method received -  relay_on
    ```

1. Répétez l'étape ci-dessus, mais définissez `--method-name` sur `relay_off`. Vous verrez le relais s'éteindre et la sortie correspondante de l'appareil IoT.

---

## 🚀 Défi

Le niveau gratuit de IoT Hub permet d'envoyer 8 000 messages par jour. Le code que vous avez écrit envoie des messages de télémétrie toutes les 10 secondes. Combien de messages par jour cela représente-t-il si un message est envoyé toutes les 10 secondes ?

Réfléchissez à la fréquence à laquelle les mesures d'humidité du sol devraient être envoyées. Comment pouvez-vous modifier votre code pour rester dans les limites du niveau gratuit tout en vérifiant aussi souvent que nécessaire, mais pas trop souvent ? Et si vous vouliez ajouter un deuxième appareil ?

## Quiz après la leçon

[Quiz après la leçon](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/16)

## Révision & Étude personnelle

Le SDK IoT Hub est open source pour Arduino et Python. Dans les dépôts de code sur GitHub, il existe plusieurs exemples montrant comment travailler avec différentes fonctionnalités de IoT Hub.

* Si vous utilisez un Wio Terminal, consultez les [exemples Arduino sur GitHub](https://github.com/Azure/azure-iot-pal-arduino/tree/master/pal/samples)
* Si vous utilisez un Raspberry Pi ou un appareil virtuel, consultez les [exemples Python sur GitHub](https://github.com/Azure/azure-iot-sdk-python/tree/master/azure-iot-hub/samples)

## Devoir

[Apprenez-en plus sur les services cloud](assignment.md)

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de faire appel à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.