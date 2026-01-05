<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "e345843ccfeb7261d81500d19c64d476",
  "translation_date": "2025-08-25T01:03:00+00:00",
  "source_file": "3-transport/lessons/2-store-location-data/README.md",
  "language_code": "fr"
}
-->
# Stocker des données de localisation

![Un aperçu en sketchnote de cette leçon](../../../../../translated_images/lesson-12.ca7f53039712a3ec14ad6474d8445361c84adab643edc53fa6269b77895606bb.fr.jpg)

> Sketchnote par [Nitya Narasimhan](https://github.com/nitya). Cliquez sur l'image pour une version agrandie.

## Quiz avant la leçon

[Quiz avant la leçon](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/23)

## Introduction

Dans la dernière leçon, vous avez appris à utiliser un capteur GPS pour capturer des données de localisation. Pour utiliser ces données afin de visualiser la position d'un camion chargé de nourriture et son trajet, elles doivent être envoyées à un service IoT dans le cloud, puis stockées quelque part.

Dans cette leçon, vous apprendrez les différentes façons de stocker des données IoT et comment stocker ces données à partir de votre service IoT en utilisant du code sans serveur.

Dans cette leçon, nous aborderons :

* [Données structurées et non structurées](../../../../../3-transport/lessons/2-store-location-data)
* [Envoyer des données GPS à un IoT Hub](../../../../../3-transport/lessons/2-store-location-data)
* [Chemins chauds, tièdes et froids](../../../../../3-transport/lessons/2-store-location-data)
* [Gérer les événements GPS avec du code sans serveur](../../../../../3-transport/lessons/2-store-location-data)
* [Comptes de stockage Azure](../../../../../3-transport/lessons/2-store-location-data)
* [Connecter votre code sans serveur au stockage](../../../../../3-transport/lessons/2-store-location-data)

## Données structurées et non structurées

Les systèmes informatiques traitent des données, et ces données peuvent prendre toutes sortes de formes et de tailles. Elles peuvent varier de simples nombres à de grandes quantités de texte, en passant par des vidéos, des images et des données IoT. Les données peuvent généralement être classées dans l'une des deux catégories : *données structurées* et *données non structurées*.

* **Données structurées** : Ce sont des données avec une structure bien définie et rigide qui ne change pas, et qui sont généralement organisées en tableaux avec des relations. Un exemple serait les informations personnelles d'une personne, comme son nom, sa date de naissance et son adresse.

* **Données non structurées** : Ce sont des données sans structure bien définie et rigide, y compris des données dont la structure peut changer fréquemment. Un exemple serait des documents tels que des textes écrits ou des feuilles de calcul.

✅ Faites des recherches : Pouvez-vous penser à d'autres exemples de données structurées et non structurées ?

> 💁 Il existe également des données semi-structurées qui sont structurées mais ne s'intègrent pas dans des tableaux fixes.

Les données IoT sont généralement considérées comme des données non structurées.

Imaginez que vous ajoutiez des dispositifs IoT à une flotte de véhicules pour une grande exploitation agricole commerciale. Vous pourriez vouloir utiliser différents dispositifs pour différents types de véhicules. Par exemple :

* Pour les véhicules agricoles comme les tracteurs, vous souhaitez des données GPS pour vous assurer qu'ils travaillent sur les bons champs.
* Pour les camions de livraison transportant de la nourriture vers des entrepôts, vous souhaitez des données GPS ainsi que des données de vitesse et d'accélération pour garantir que le conducteur conduit en toute sécurité, ainsi que des données d'identité et de démarrage/arrêt pour garantir la conformité avec les lois locales sur les heures de travail.
* Pour les camions frigorifiques, vous souhaitez également des données de température pour garantir que la nourriture ne devient ni trop chaude ni trop froide, afin d'éviter qu'elle ne se détériore pendant le transport.

Ces données peuvent changer constamment. Par exemple, si le dispositif IoT est dans la cabine d'un camion, les données qu'il envoie peuvent changer en fonction de la remorque, par exemple en envoyant uniquement des données de température lorsqu'une remorque frigorifique est utilisée.

✅ Quelles autres données IoT pourraient être capturées ? Pensez aux types de charges que les camions peuvent transporter, ainsi qu'aux données de maintenance.

Ces données varient d'un véhicule à l'autre, mais elles sont toutes envoyées au même service IoT pour traitement. Le service IoT doit être capable de traiter ces données non structurées, en les stockant de manière à permettre leur recherche ou leur analyse, tout en s'adaptant aux différentes structures de ces données.

### Stockage SQL vs NoSQL

Les bases de données sont des services qui permettent de stocker et de interroger des données. Les bases de données existent en deux types : SQL et NoSQL.

#### Bases de données SQL

Les premières bases de données étaient des systèmes de gestion de bases de données relationnelles (RDBMS), ou bases de données relationnelles. Elles sont également connues sous le nom de bases de données SQL en raison du langage de requête structuré (SQL) utilisé pour interagir avec elles afin d'ajouter, supprimer, mettre à jour ou interroger des données. Ces bases de données consistent en un schéma - un ensemble bien défini de tableaux de données, similaire à une feuille de calcul. Chaque tableau possède plusieurs colonnes nommées. Lorsque vous insérez des données, vous ajoutez une ligne au tableau, en mettant des valeurs dans chacune des colonnes. Cela maintient les données dans une structure très rigide - bien que vous puissiez laisser des colonnes vides, si vous souhaitez ajouter une nouvelle colonne, vous devez le faire sur la base de données, en remplissant les valeurs pour les lignes existantes. Ces bases de données sont relationnelles - c'est-à-dire qu'un tableau peut avoir une relation avec un autre.

![Une base de données relationnelle où l'ID du tableau Utilisateur est lié à la colonne ID utilisateur du tableau Achats, et l'ID du tableau Produits est lié à l'ID produit du tableau Achats](../../../../../translated_images/sql-database.be160f12bfccefd3.fr.png)

Par exemple, si vous stockiez les informations personnelles d'un utilisateur dans un tableau, vous auriez un ID unique interne par utilisateur utilisé dans une ligne d'un tableau contenant le nom et l'adresse de l'utilisateur. Si vous souhaitiez ensuite stocker d'autres détails sur cet utilisateur, comme ses achats, dans un autre tableau, vous auriez une colonne dans le nouveau tableau pour l'ID de cet utilisateur. Lorsque vous recherchez un utilisateur, vous pouvez utiliser son ID pour obtenir ses informations personnelles dans un tableau, et ses achats dans un autre.

Les bases de données SQL sont idéales pour stocker des données structurées et pour garantir que les données correspondent à votre schéma.

✅ Si vous n'avez jamais utilisé SQL auparavant, prenez un moment pour lire à ce sujet sur la [page SQL de Wikipédia](https://wikipedia.org/wiki/SQL).

Quelques bases de données SQL bien connues sont Microsoft SQL Server, MySQL et PostgreSQL.

✅ Faites des recherches : Renseignez-vous sur certaines de ces bases de données SQL et leurs capacités.

#### Bases de données NoSQL

Les bases de données NoSQL sont appelées NoSQL car elles n'ont pas la même structure rigide que les bases de données SQL. Elles sont également connues sous le nom de bases de données documentaires car elles peuvent stocker des données non structurées telles que des documents.

> 💁 Malgré leur nom, certaines bases de données NoSQL permettent d'utiliser SQL pour interroger les données.

![Documents dans des dossiers dans une base de données NoSQL](../../../../../translated_images/noqsl-database.62d24ccf5b73f60d35c245a8533f1c7147c0928e955b82cb290b2e184bb434df.fr.png)

Les bases de données NoSQL n'ont pas de schéma prédéfini qui limite la manière dont les données sont stockées. Vous pouvez insérer des données non structurées, généralement sous forme de documents JSON. Ces documents peuvent être organisés en dossiers, similaires aux fichiers sur votre ordinateur. Chaque document peut avoir des champs différents des autres documents - par exemple, si vous stockiez des données IoT provenant de vos véhicules agricoles, certains pourraient avoir des champs pour les données d'accéléromètre et de vitesse, d'autres pourraient avoir des champs pour la température dans la remorque. Si vous ajoutiez un nouveau type de camion, comme un camion avec des balances intégrées pour suivre le poids des produits transportés, alors votre dispositif IoT pourrait ajouter ce nouveau champ et il pourrait être stocké sans aucun changement à la base de données.

Quelques bases de données NoSQL bien connues incluent Azure CosmosDB, MongoDB et CouchDB.

✅ Faites des recherches : Renseignez-vous sur certaines de ces bases de données NoSQL et leurs capacités.

Dans cette leçon, vous utiliserez un stockage NoSQL pour stocker des données IoT.

## Envoyer des données GPS à un IoT Hub

Dans la dernière leçon, vous avez capturé des données GPS à partir d'un capteur GPS connecté à votre dispositif IoT. Pour stocker ces données IoT dans le cloud, vous devez les envoyer à un service IoT. Une fois de plus, vous utiliserez Azure IoT Hub, le même service IoT cloud que vous avez utilisé dans le projet précédent.

![Envoi de télémétrie GPS d'un dispositif IoT à IoT Hub](../../../../../translated_images/gps-telemetry-iot-hub.8115335d51cd2c1285d20e9d1b18cf685e59a8e093e7797291ef173445af6f3d.fr.png)

### Tâche - envoyer des données GPS à un IoT Hub

1. Créez un nouveau IoT Hub en utilisant le niveau gratuit.

    > ⚠️ Vous pouvez vous référer aux [instructions pour créer un IoT Hub du projet 2, leçon 4](../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/README.md#create-an-iot-service-in-the-cloud) si nécessaire.

    N'oubliez pas de créer un nouveau groupe de ressources. Nommez le nouveau groupe de ressources `gps-sensor`, et le nouveau IoT Hub avec un nom unique basé sur `gps-sensor`, comme `gps-sensor-<votre nom>`.

    > 💁 Si vous avez encore votre IoT Hub du projet précédent, vous pouvez le réutiliser. N'oubliez pas d'utiliser le nom de ce IoT Hub et le groupe de ressources dans lequel il se trouve lors de la création d'autres services.

1. Ajoutez un nouveau dispositif au IoT Hub. Appelez ce dispositif `gps-sensor`. Récupérez la chaîne de connexion pour le dispositif.

1. Mettez à jour le code de votre dispositif pour envoyer les données GPS au nouveau IoT Hub en utilisant la chaîne de connexion du dispositif obtenue à l'étape précédente.

    > ⚠️ Vous pouvez vous référer aux [instructions pour connecter votre dispositif à un IoT du projet 2, leçon 4](../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/README.md#connect-your-device-to-the-iot-service) si nécessaire.

1. Lorsque vous envoyez les données GPS, faites-le sous forme de JSON dans le format suivant :

    ```json
    {
        "gps" :
        {
            "lat" : <latitude>,
            "lon" : <longitude>
        }
    }
    ```

1. Envoyez les données GPS toutes les minutes pour ne pas dépasser votre allocation quotidienne de messages.

Si vous utilisez le Wio Terminal, n'oubliez pas d'ajouter toutes les bibliothèques nécessaires et de régler l'heure en utilisant un serveur NTP. Votre code devra également s'assurer qu'il a lu toutes les données du port série avant d'envoyer la localisation GPS, en utilisant le code existant de la dernière leçon. Utilisez le code suivant pour construire le document JSON :

```cpp
DynamicJsonDocument doc(1024);
doc["gps"]["lat"] = gps.location.lat();
doc["gps"]["lon"] = gps.location.lng();
```

Si vous utilisez un dispositif IoT virtuel, n'oubliez pas d'installer toutes les bibliothèques nécessaires en utilisant un environnement virtuel.

Pour le Raspberry Pi et le dispositif IoT virtuel, utilisez le code existant de la dernière leçon pour obtenir les valeurs de latitude et de longitude, puis envoyez-les dans le format JSON correct avec le code suivant :

```python
message_json = { "gps" : { "lat":lat, "lon":lon } }
print("Sending telemetry", message_json)
message = Message(json.dumps(message_json))
```

> 💁 Vous pouvez trouver ce code dans le dossier [code/wio-terminal](../../../../../3-transport/lessons/2-store-location-data/code/wio-terminal), [code/pi](../../../../../3-transport/lessons/2-store-location-data/code/pi) ou [code/virtual-device](../../../../../3-transport/lessons/2-store-location-data/code/virtual-device).

Exécutez le code de votre dispositif et assurez-vous que les messages arrivent dans IoT Hub en utilisant la commande CLI `az iot hub monitor-events`.

## Chemins chauds, tièdes et froids

Les données qui circulent d'un dispositif IoT vers le cloud ne sont pas toujours traitées en temps réel. Certaines données nécessitent un traitement en temps réel, d'autres peuvent être traitées peu de temps après, et d'autres encore peuvent être traitées beaucoup plus tard. Le flux de données vers différents services qui les traitent à différents moments est appelé chemins chauds, tièdes et froids.

### Chemin chaud

Le chemin chaud fait référence aux données qui doivent être traitées en temps réel ou presque. Vous utiliseriez les données du chemin chaud pour des alertes, comme recevoir une notification qu'un véhicule approche d'un dépôt ou que la température dans un camion frigorifique est trop élevée.

Pour utiliser les données du chemin chaud, votre code répondrait aux événements dès qu'ils sont reçus par vos services cloud.

### Chemin tiède

Le chemin tiède fait référence aux données qui peuvent être traitées peu de temps après leur réception, par exemple pour des rapports ou des analyses à court terme. Vous utiliseriez les données du chemin tiède pour des rapports quotidiens sur le kilométrage des véhicules, en utilisant les données recueillies la veille.

Les données du chemin tiède sont stockées dès leur réception par le service cloud dans un type de stockage qui peut être rapidement accessible.

### Chemin froid

Le chemin froid fait référence aux données historiques, stockées à long terme pour être traitées lorsque nécessaire. Par exemple, vous pourriez utiliser le chemin froid pour obtenir des rapports annuels sur le kilométrage des véhicules ou effectuer des analyses sur les itinéraires afin de trouver le trajet le plus optimal pour réduire les coûts de carburant.

Les données du chemin froid sont stockées dans des entrepôts de données - des bases de données conçues pour stocker de grandes quantités de données qui ne changeront jamais et qui peuvent être interrogées rapidement et facilement. Vous auriez normalement une tâche régulière dans votre application cloud qui s'exécuterait à un moment régulier chaque jour, semaine ou mois pour déplacer les données du stockage du chemin tiède vers l'entrepôt de données.

✅ Pensez aux données que vous avez capturées jusqu'à présent dans ces leçons. S'agit-il de données du chemin chaud, tiède ou froid ?

## Gérer les événements GPS avec du code sans serveur

Une fois que les données arrivent dans votre IoT Hub, vous pouvez écrire du code sans serveur pour écouter les événements publiés sur le point de terminaison compatible Event-Hub. Il s'agit du chemin tiède - ces données seront stockées et utilisées dans la prochaine leçon pour établir un rapport sur le trajet.

![Envoi de télémétrie GPS d'un dispositif IoT à IoT Hub, puis à Azure Functions via un déclencheur Event Hub](../../../../../translated_images/gps-telemetry-iot-hub-functions.24d3fa5592455e9f4e2fe73856b40c3915a292b90263c31d652acfd976cfedd8.fr.png)

### Tâche - gérer les événements GPS avec du code sans serveur

1. Créez une application Azure Functions en utilisant l'interface CLI Azure Functions. Utilisez l'environnement d'exécution Python et créez-la dans un dossier appelé `gps-trigger`, en utilisant le même nom pour le projet de l'application Functions. Assurez-vous de créer un environnement virtuel pour cela.
> ⚠️ Vous pouvez consulter les [instructions pour créer un projet Azure Functions à partir du projet 2, leçon 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#create-a-serverless-application) si nécessaire.
1. Ajoutez un déclencheur d'événement IoT Hub qui utilise le point de terminaison compatible Event Hub de l'IoT Hub.

    > ⚠️ Vous pouvez consulter les [instructions pour créer un déclencheur d'événement IoT Hub à partir du projet 2, leçon 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#create-an-iot-hub-event-trigger) si nécessaire.

1. Définissez la chaîne de connexion du point de terminaison compatible Event Hub dans le fichier `local.settings.json`, et utilisez la clé pour cette entrée dans le fichier `function.json`.

1. Utilisez l'application Azurite comme émulateur de stockage local.

1. Exécutez votre application de fonctions pour vérifier qu'elle reçoit des événements de votre appareil GPS. Assurez-vous que votre appareil IoT fonctionne également et envoie des données GPS.

    ```output
    Python EventHub trigger processed an event: {"gps": {"lat": 47.73481, "lon": -122.25701}}
    ```

## Comptes de stockage Azure

![Le logo Azure Storage](../../../../../translated_images/azure-storage-logo.605c0f602c640d482a80f1b35a2629a32d595711b7ab1d7ceea843250615ff32.fr.png)

Les comptes de stockage Azure sont un service de stockage polyvalent qui peut stocker des données de différentes manières. Vous pouvez stocker des données sous forme de blobs, dans des files d'attente, dans des tables ou sous forme de fichiers, et tout cela simultanément.

### Stockage Blob

Le mot *Blob* signifie objets binaires volumineux, mais il est devenu le terme pour désigner toute donnée non structurée. Vous pouvez stocker n'importe quelle donnée dans le stockage blob, des documents JSON contenant des données IoT aux fichiers image et vidéo. Le stockage blob repose sur le concept de *conteneurs*, des répertoires nommés où vous pouvez stocker des données, similaires aux tables dans une base de données relationnelle. Ces conteneurs peuvent contenir un ou plusieurs dossiers pour stocker des blobs, et chaque dossier peut contenir d'autres dossiers, comme les fichiers sont stockés sur le disque dur de votre ordinateur.

Vous utiliserez le stockage blob dans cette leçon pour stocker des données IoT.

✅ Faites des recherches : Lisez sur le [stockage Blob Azure](https://docs.microsoft.com/azure/storage/blobs/storage-blobs-overview?WT.mc_id=academic-17441-jabenn)

### Stockage Table

Le stockage table vous permet de stocker des données semi-structurées. Le stockage table est en réalité une base de données NoSQL, donc il ne nécessite pas un ensemble défini de tables à l'avance, mais il est conçu pour stocker des données dans une ou plusieurs tables, avec des clés uniques pour définir chaque ligne.

✅ Faites des recherches : Lisez sur le [stockage Table Azure](https://docs.microsoft.com/azure/storage/tables/table-storage-overview?WT.mc_id=academic-17441-jabenn)

### Stockage File d'attente

Le stockage file d'attente vous permet de stocker des messages de taille maximale de 64 Ko dans une file d'attente. Vous pouvez ajouter des messages à l'arrière de la file d'attente et les lire à l'avant. Les files d'attente stockent les messages indéfiniment tant qu'il reste de l'espace de stockage, ce qui permet de conserver les messages à long terme, puis de les lire lorsque nécessaire. Par exemple, si vous souhaitez exécuter une tâche mensuelle pour traiter des données GPS, vous pouvez les ajouter à une file d'attente chaque jour pendant un mois, puis à la fin du mois, traiter tous les messages de la file d'attente.

✅ Faites des recherches : Lisez sur le [stockage File d'attente Azure](https://docs.microsoft.com/azure/storage/queues/storage-queues-introduction?WT.mc_id=academic-17441-jabenn)

### Stockage Fichier

Le stockage fichier consiste à stocker des fichiers dans le cloud, et toutes les applications ou appareils peuvent se connecter en utilisant des protocoles standards de l'industrie. Vous pouvez écrire des fichiers dans le stockage fichier, puis le monter comme un disque sur votre PC ou Mac.

✅ Faites des recherches : Lisez sur le [stockage Fichier Azure](https://docs.microsoft.com/azure/storage/files/storage-files-introduction?WT.mc_id=academic-17441-jabenn)

## Connectez votre code sans serveur au stockage

Votre application de fonctions doit maintenant se connecter au stockage blob pour stocker les messages provenant de l'IoT Hub. Il existe deux façons de le faire :

* À l'intérieur du code de la fonction, connectez-vous au stockage blob en utilisant le SDK Python pour le stockage blob et écrivez les données sous forme de blobs.
* Utilisez une liaison de fonction de sortie pour lier la valeur de retour de la fonction au stockage blob et enregistrer automatiquement le blob.

Dans cette leçon, vous utiliserez le SDK Python pour voir comment interagir avec le stockage blob.

![Envoi de télémétrie GPS depuis un appareil IoT vers IoT Hub, puis vers Azure Functions via un déclencheur Event Hub, puis enregistrement dans le stockage blob](../../../../../translated_images/save-telemetry-to-storage-from-functions.ed3b1820980097f1.fr.png)

Les données seront enregistrées sous forme de blob JSON avec le format suivant :

```json
{
    "device_id": <device_id>,
    "timestamp" : <time>,
    "gps" :
    {
        "lat" : <latitude>,
        "lon" : <longitude>
    }
}
```

### Tâche - Connectez votre code sans serveur au stockage

1. Créez un compte de stockage Azure. Nommez-le quelque chose comme `gps<votre nom>`.

    > ⚠️ Vous pouvez consulter les [instructions pour créer un compte de stockage à partir du projet 2, leçon 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---create-the-cloud-resources) si nécessaire.

    Si vous avez encore un compte de stockage du projet précédent, vous pouvez le réutiliser.

    > 💁 Vous pourrez utiliser le même compte de stockage pour déployer votre application Azure Functions plus tard dans cette leçon.

1. Exécutez la commande suivante pour obtenir la chaîne de connexion du compte de stockage :

    ```sh
    az storage account show-connection-string --output table \
                                              --name <storage_name>
    ```

    Remplacez `<storage_name>` par le nom du compte de stockage que vous avez créé à l'étape précédente.

1. Ajoutez une nouvelle entrée au fichier `local.settings.json` pour la chaîne de connexion de votre compte de stockage, en utilisant la valeur de l'étape précédente. Nommez-la `STORAGE_CONNECTION_STRING`.

1. Ajoutez ce qui suit au fichier `requirements.txt` pour installer les packages Pip de stockage Azure :

    ```sh
    azure-storage-blob
    ```

    Installez les packages de ce fichier dans votre environnement virtuel.

    > Si vous obtenez une erreur, mettez à jour votre version de Pip dans votre environnement virtuel avec la commande suivante, puis réessayez :
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. Dans le fichier `__init__.py` pour le `iot-hub-trigger`, ajoutez les instructions d'importation suivantes :

    ```python
    import json
    import os
    import uuid
    from azure.storage.blob import BlobServiceClient, PublicAccess
    ```

    Le module système `json` sera utilisé pour lire et écrire des JSON, le module système `os` sera utilisé pour lire la chaîne de connexion, le module système `uuid` sera utilisé pour générer un identifiant unique pour la lecture GPS.

    Le package `azure.storage.blob` contient le SDK Python pour travailler avec le stockage blob.

1. Avant la méthode `main`, ajoutez la fonction d'assistance suivante :

    ```python
    def get_or_create_container(name):
        connection_str = os.environ['STORAGE_CONNECTION_STRING']
        blob_service_client = BlobServiceClient.from_connection_string(connection_str)
    
        for container in blob_service_client.list_containers():
            if container.name == name:
                return blob_service_client.get_container_client(container.name)
        
        return blob_service_client.create_container(name, public_access=PublicAccess.Container)
    ```

    Le SDK blob Python n'a pas de méthode d'assistance pour créer un conteneur s'il n'existe pas. Ce code chargera la chaîne de connexion du fichier `local.settings.json` (ou des paramètres d'application une fois déployé dans le cloud), puis créera une classe `BlobServiceClient` à partir de celle-ci pour interagir avec le compte de stockage blob. Il boucle ensuite à travers tous les conteneurs du compte de stockage blob, en cherchant un avec le nom fourni - s'il en trouve un, il retournera une classe `ContainerClient` qui peut interagir avec le conteneur pour créer des blobs. S'il n'en trouve pas, le conteneur est créé et le client pour le nouveau conteneur est retourné.

    Lorsque le nouveau conteneur est créé, un accès public est accordé pour interroger les blobs dans le conteneur. Cela sera utilisé dans la prochaine leçon pour visualiser les données GPS sur une carte.

1. Contrairement à l'humidité du sol, avec ce code, nous voulons enregistrer chaque événement, alors ajoutez le code suivant à l'intérieur de la boucle `for event in events:` dans la fonction `main`, sous l'instruction `logging` :

    ```python
    device_id = event.iothub_metadata['connection-device-id']
    blob_name = f'{device_id}/{str(uuid.uuid1())}.json'
    ```

    Ce code récupère l'identifiant de l'appareil à partir des métadonnées de l'événement, puis l'utilise pour créer un nom de blob. Les blobs peuvent être stockés dans des dossiers, et l'identifiant de l'appareil sera utilisé pour le nom du dossier, donc chaque appareil aura tous ses événements GPS dans un seul dossier. Le nom du blob est ce dossier, suivi d'un nom de document, séparé par des barres obliques, similaire aux chemins Linux et macOS (similaire à Windows également, mais Windows utilise des barres obliques inverses). Le nom du document est un identifiant unique généré à l'aide du module Python `uuid`, avec le type de fichier `json`.

    Par exemple, pour l'identifiant de l'appareil `gps-sensor`, le nom du blob pourrait être `gps-sensor/a9487ac2-b9cf-11eb-b5cd-1e00621e3648.json`.

1. Ajoutez le code suivant en dessous :

    ```python
    container_client = get_or_create_container('gps-data')
    blob = container_client.get_blob_client(blob_name)
    ```

    Ce code obtient le client du conteneur en utilisant la classe d'assistance `get_or_create_container`, puis obtient un objet client de blob en utilisant le nom du blob. Ces clients de blob peuvent se référer à des blobs existants, ou comme dans ce cas, à un nouveau blob.

1. Ajoutez le code suivant après cela :

    ```python
    event_body = json.loads(event.get_body().decode('utf-8'))
    blob_body = {
        'device_id' : device_id,
        'timestamp' : event.iothub_metadata['enqueuedtime'],
        'gps': event_body['gps']
    }
    ```

    Cela construit le corps du blob qui sera écrit dans le stockage blob. Il s'agit d'un document JSON contenant l'identifiant de l'appareil, l'heure à laquelle la télémétrie a été envoyée à IoT Hub, et les coordonnées GPS de la télémétrie.

    > 💁 Il est important d'utiliser l'heure d'envoi du message plutôt que l'heure actuelle pour obtenir l'heure à laquelle le message a été envoyé. Il pourrait rester sur le hub pendant un certain temps avant d'être récupéré si l'application Functions n'est pas en cours d'exécution.

1. Ajoutez ce qui suit sous ce code :

    ```python
    logging.info(f'Writing blob to {blob_name} - {blob_body}')
    blob.upload_blob(json.dumps(blob_body).encode('utf-8'))
    ```

    Ce code journalise qu'un blob est sur le point d'être écrit avec ses détails, puis télécharge le corps du blob comme contenu du nouveau blob.

1. Exécutez l'application Functions. Vous verrez des blobs être écrits pour tous les événements GPS dans la sortie :

    ```output
    [2021-05-21T01:31:14.325Z] Python EventHub trigger processed an event: {"gps": {"lat": 47.73092, "lon": -122.26206}}
    ...
    [2021-05-21T01:31:14.351Z] Writing blob to gps-sensor/4b6089fe-ba8d-11eb-bc7b-1e00621e3648.json - {'device_id': 'gps-sensor', 'timestamp': '2021-05-21T00:57:53.878Z', 'gps': {'lat': 47.73092, 'lon': -122.26206}}
    ```

    > 💁 Assurez-vous de ne pas exécuter le moniteur d'événements IoT Hub en même temps.

> 💁 Vous pouvez trouver ce code dans le dossier [code/functions](../../../../../3-transport/lessons/2-store-location-data/code/functions).

### Tâche - Vérifiez les blobs téléchargés

1. Pour visualiser les blobs créés, vous pouvez utiliser soit [Azure Storage Explorer](https://azure.microsoft.com/features/storage-explorer/?WT.mc_id=academic-17441-jabenn), un outil gratuit qui vous permet de visualiser et gérer vos comptes de stockage, soit via la CLI.

    1. Pour utiliser la CLI, vous aurez d'abord besoin d'une clé de compte. Exécutez la commande suivante pour obtenir cette clé :

        ```sh
        az storage account keys list --output table \
                                     --account-name <storage_name>
        ```

        Remplacez `<storage_name>` par le nom du compte de stockage.

        Copiez la valeur de `key1`.

    1. Exécutez la commande suivante pour lister les blobs dans le conteneur :

        ```sh
        az storage blob list --container-name gps-data \
                             --output table \
                             --account-name <storage_name> \
                             --account-key <key1>
        ```

        Remplacez `<storage_name>` par le nom du compte de stockage, et `<key1>` par la valeur de `key1` que vous avez copiée à l'étape précédente.

        Cela listera tous les blobs dans le conteneur :

        ```output
        Name                                                  Blob Type    Blob Tier    Length    Content Type              Last Modified              Snapshot
        ----------------------------------------------------  -----------  -----------  --------  ------------------------  -------------------------  ----------
        gps-sensor/1810d55e-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:27+00:00
        gps-sensor/18293e46-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:28+00:00
        gps-sensor/1844549c-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:28+00:00
        gps-sensor/1894d714-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:28+00:00
        ```

    1. Téléchargez l'un des blobs en utilisant la commande suivante :

        ```sh
        az storage blob download --container-name gps-data \
                                 --account-name <storage_name> \
                                 --account-key <key1> \
                                 --name <blob_name> \
                                 --file <file_name>
        ```

        Remplacez `<storage_name>` par le nom du compte de stockage, et `<key1>` par la valeur de `key1` que vous avez copiée à l'étape précédente.

        Remplacez `<blob_name>` par le nom complet de la colonne `Name` de la sortie de l'étape précédente, y compris le nom du dossier. Remplacez `<file_name>` par le nom d'un fichier local pour enregistrer le blob.

    Une fois téléchargé, vous pouvez ouvrir le fichier JSON dans VS Code, et vous verrez le blob contenant les détails de localisation GPS :

    ```json
    {"device_id": "gps-sensor", "timestamp": "2021-05-21T00:57:53.878Z", "gps": {"lat": 47.73092, "lon": -122.26206}}
    ```

### Tâche - Déployez votre application Functions dans le cloud

Maintenant que votre application Functions fonctionne, vous pouvez la déployer dans le cloud.

1. Créez une nouvelle application Azure Functions, en utilisant le compte de stockage que vous avez créé précédemment. Nommez-la quelque chose comme `gps-sensor-` et ajoutez un identifiant unique à la fin, comme quelques mots aléatoires ou votre nom.

    > ⚠️ Vous pouvez consulter les [instructions pour créer une application Functions à partir du projet 2, leçon 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---create-the-cloud-resources) si nécessaire.

1. Téléchargez les valeurs `IOT_HUB_CONNECTION_STRING` et `STORAGE_CONNECTION_STRING` dans les paramètres d'application.

    > ⚠️ Vous pouvez consulter les [instructions pour télécharger les paramètres d'application à partir du projet 2, leçon 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---upload-your-application-settings) si nécessaire.

1. Déployez votre application Functions locale dans le cloud.
> ⚠️ Vous pouvez consulter les [instructions pour déployer votre application Functions à partir du projet 2, leçon 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---deploy-your-functions-app-to-the-cloud) si nécessaire.
## 🚀 Défi

Les données GPS ne sont pas parfaitement précises, et les emplacements détectés peuvent être décalés de quelques mètres, voire plus, en particulier dans les tunnels et les zones avec de hauts bâtiments.

Réfléchissez à la manière dont la navigation par satellite pourrait surmonter ce problème. Quelles données votre système de navigation possède-t-il qui pourraient lui permettre de mieux prédire votre position ?

## Quiz après le cours

[Quiz après le cours](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/24)

## Révision et auto-apprentissage

* Lisez à propos des données structurées sur la [page Modèle de données sur Wikipédia](https://wikipedia.org/wiki/Data_model)
* Lisez à propos des données semi-structurées sur la [page Données semi-structurées sur Wikipédia](https://wikipedia.org/wiki/Semi-structured_data)
* Lisez à propos des données non structurées sur la [page Données non structurées sur Wikipédia](https://wikipedia.org/wiki/Unstructured_data)
* Apprenez-en davantage sur Azure Storage et les différents types de stockage dans la [documentation Azure Storage](https://docs.microsoft.com/azure/storage/?WT.mc_id=academic-17441-jabenn)

## Devoir

[Explorez les liaisons de fonctions](assignment.md)

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de faire appel à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.