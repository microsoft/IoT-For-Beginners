<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "71b5040e0b3472f1c0949c9b55f224c0",
  "translation_date": "2025-08-24T23:03:37+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/README.md",
  "language_code": "fr"
}
-->
# Connectez votre appareil à Internet

![Un aperçu illustré de cette leçon](../../../../../translated_images/lesson-4.7344e074ea68fa545fd320b12dce36d72dd62d28c3b4596cb26cf315f434b98f.fr.jpg)

> Illustration par [Nitya Narasimhan](https://github.com/nitya). Cliquez sur l'image pour une version agrandie.

Cette leçon a été enseignée dans le cadre de la série [Hello IoT](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) du [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). Elle a été divisée en deux vidéos : une leçon d'une heure et une session de questions-réponses d'une heure approfondissant certains aspects de la leçon.

[![Leçon 4 : Connectez votre appareil à Internet](https://img.youtube.com/vi/O4dd172mZhs/0.jpg)](https://youtu.be/O4dd172mZhs)

[![Leçon 4 : Connectez votre appareil à Internet - Session de questions-réponses](https://img.youtube.com/vi/j-cVCzRDE2Q/0.jpg)](https://youtu.be/j-cVCzRDE2Q)

> 🎥 Cliquez sur les images ci-dessus pour regarder les vidéos

## Quiz avant la leçon

[Quiz avant la leçon](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/7)

## Introduction

Le **I** dans IoT signifie **Internet** - la connectivité au cloud et les services qui permettent de nombreuses fonctionnalités des appareils IoT, comme la collecte de mesures des capteurs connectés à l'appareil ou l'envoi de messages pour contrôler les actionneurs. Les appareils IoT se connectent généralement à un service cloud IoT unique en utilisant un protocole de communication standard, et ce service est relié au reste de votre application IoT, qu'il s'agisse de services d'IA pour prendre des décisions intelligentes à partir de vos données ou d'applications web pour le contrôle ou les rapports.

> 🎓 Les données collectées par les capteurs et envoyées au cloud sont appelées télémétrie.

Les appareils IoT peuvent recevoir des messages du cloud. Ces messages contiennent souvent des commandes - c'est-à-dire des instructions pour effectuer une action, soit en interne (comme redémarrer ou mettre à jour le firmware), soit en utilisant un actionneur (comme allumer une lumière).

Cette leçon introduit certains des protocoles de communication que les appareils IoT peuvent utiliser pour se connecter au cloud, ainsi que les types de données qu'ils peuvent envoyer ou recevoir. Vous aurez également l'occasion de les manipuler, en ajoutant un contrôle via Internet à votre veilleuse et en déplaçant la logique de contrôle de la LED vers un code "serveur" exécuté localement.

Dans cette leçon, nous aborderons :

* [Protocoles de communication](../../../../../1-getting-started/lessons/4-connect-internet)
* [Message Queueing Telemetry Transport (MQTT)](../../../../../1-getting-started/lessons/4-connect-internet)
* [Télémétrie](../../../../../1-getting-started/lessons/4-connect-internet)
* [Commandes](../../../../../1-getting-started/lessons/4-connect-internet)

## Protocoles de communication

Il existe plusieurs protocoles de communication populaires utilisés par les appareils IoT pour communiquer avec Internet. Les plus courants reposent sur la messagerie de type publication/abonnement via un courtier. Les appareils IoT se connectent au courtier pour publier des données de télémétrie et s'abonner aux commandes. Les services cloud se connectent également au courtier pour s'abonner à tous les messages de télémétrie et publier des commandes, soit pour des appareils spécifiques, soit pour des groupes d'appareils.

![Les appareils IoT se connectent à un courtier pour publier des données de télémétrie et s'abonner aux commandes. Les services cloud se connectent au courtier pour s'abonner à toutes les données de télémétrie et envoyer des commandes à des appareils spécifiques.](../../../../../translated_images/pub-sub.7c7ed43fe9fd15d4.fr.png)

MQTT est le protocole de communication le plus populaire pour les appareils IoT et sera abordé dans cette leçon. D'autres protocoles incluent AMQP et HTTP/HTTPS.

## Message Queueing Telemetry Transport (MQTT)

[MQTT](http://mqtt.org) est un protocole de messagerie léger et ouvert qui permet d'envoyer des messages entre appareils. Il a été conçu en 1999 pour surveiller des pipelines pétroliers, avant d'être publié comme standard ouvert 15 ans plus tard par IBM.

MQTT fonctionne avec un courtier unique et plusieurs clients. Tous les clients se connectent au courtier, qui achemine les messages vers les clients concernés. Les messages sont acheminés à l'aide de sujets nommés, plutôt que d'être envoyés directement à un client individuel. Un client peut publier sur un sujet, et tous les clients abonnés à ce sujet recevront le message.

![Un appareil IoT publiant des données de télémétrie sur le sujet /telemetry, et le service cloud s'abonnant à ce sujet](../../../../../translated_images/mqtt.cbf7f21d9adc3e17548b359444cc11bb4bf2010543e32ece9a47becf54438c23.fr.png)

✅ Faites des recherches. Si vous avez de nombreux appareils IoT, comment pouvez-vous vous assurer que votre courtier MQTT peut gérer tous les messages ?

### Connectez votre appareil IoT à MQTT

La première étape pour ajouter un contrôle via Internet à votre veilleuse consiste à la connecter à un courtier MQTT.

#### Tâche

Connectez votre appareil à un courtier MQTT.

Dans cette partie de la leçon, vous connecterez votre veilleuse IoT à Internet pour permettre un contrôle à distance. Plus tard dans cette leçon, votre appareil IoT enverra un message de télémétrie via MQTT à un courtier MQTT public avec le niveau de lumière, où il sera récupéré par un code serveur que vous écrirez. Ce code vérifiera le niveau de lumière et enverra un message de commande à l'appareil pour lui indiquer d'allumer ou d'éteindre la LED.

Un cas d'utilisation réel pour une telle configuration pourrait être de collecter des données provenant de plusieurs capteurs de lumière avant de décider d'allumer les lumières dans un endroit comportant de nombreuses lumières, comme un stade. Cela pourrait empêcher les lumières de s'allumer si un seul capteur est couvert par des nuages ou un oiseau, mais que les autres capteurs détectent suffisamment de lumière.

✅ Quels autres scénarios nécessiteraient l'évaluation des données de plusieurs capteurs avant d'envoyer des commandes ?

Plutôt que de gérer les complexités de la configuration d'un courtier MQTT dans le cadre de cet exercice, vous pouvez utiliser un serveur de test public qui exécute [Eclipse Mosquitto](https://www.mosquitto.org), un courtier MQTT open-source. Ce courtier de test est disponible publiquement à [test.mosquitto.org](https://test.mosquitto.org) et ne nécessite pas de compte, ce qui en fait un excellent outil pour tester des clients et serveurs MQTT.

> 💁 Ce courtier de test est public et non sécurisé. N'importe qui pourrait écouter ce que vous publiez, il ne doit donc pas être utilisé pour des données devant rester privées.

![Un diagramme de flux de l'exercice montrant les niveaux de lumière mesurés et vérifiés, et la LED contrôlée](../../../../../translated_images/assignment-1-internet-flow.3256feab5f052fd273bf4e331157c574c2c3fa42e479836fc9c3586f41db35a5.fr.png)

Suivez l'étape correspondante ci-dessous pour connecter votre appareil au courtier MQTT :

* [Arduino - Wio Terminal](wio-terminal-mqtt.md)
* [Ordinateur monocarte - Raspberry Pi/Appareil IoT virtuel](single-board-computer-mqtt.md)

### Une exploration approfondie de MQTT

Les sujets peuvent avoir une hiérarchie, et les clients peuvent s'abonner à différents niveaux de la hiérarchie en utilisant des caractères génériques. Par exemple, vous pouvez envoyer des messages de télémétrie de température au sujet `/telemetry/temperature` et des messages d'humidité au sujet `/telemetry/humidity`, puis dans votre application cloud, vous abonner au sujet `/telemetry/*` pour recevoir à la fois les messages de température et d'humidité.

Les messages peuvent être envoyés avec une qualité de service (QoS), qui détermine la garantie de réception du message.

* Au plus une fois - le message est envoyé une seule fois et ni le client ni le courtier ne prennent de mesures supplémentaires pour accuser réception (envoi sans garantie).
* Au moins une fois - le message est réessayé plusieurs fois par l'expéditeur jusqu'à ce qu'un accusé de réception soit reçu (livraison garantie).
* Une seule fois - l'expéditeur et le destinataire effectuent une double vérification pour garantir qu'une seule copie du message est reçue (livraison assurée).

✅ Quels scénarios pourraient nécessiter un message avec livraison assurée plutôt qu'un envoi sans garantie ?

Bien que le nom inclue "Message Queueing" (MQ dans MQTT), il ne prend en réalité pas en charge les files d'attente de messages. Cela signifie que si un client se déconnecte, puis se reconnecte, il ne recevra pas les messages envoyés pendant la déconnexion, sauf pour ceux qu'il avait déjà commencé à traiter via le processus QoS. Les messages peuvent avoir un indicateur de rétention. Si cet indicateur est activé, le courtier MQTT stockera le dernier message envoyé sur un sujet avec cet indicateur et l'enverra à tout client qui s'abonne ultérieurement à ce sujet. Ainsi, les clients recevront toujours le dernier message.

MQTT prend également en charge une fonction de maintien en vie qui vérifie si la connexion est toujours active pendant de longues périodes sans messages.

> 🦟 [Mosquitto de la Fondation Eclipse](https://mosquitto.org) propose un courtier MQTT gratuit que vous pouvez exécuter vous-même pour expérimenter avec MQTT, ainsi qu'un courtier MQTT public que vous pouvez utiliser pour tester votre code, hébergé sur [test.mosquitto.org](https://test.mosquitto.org).

Les connexions MQTT peuvent être publiques et ouvertes, ou chiffrées et sécurisées à l'aide de noms d'utilisateur et de mots de passe, ou de certificats.

> 💁 MQTT communique via TCP/IP, le même protocole réseau sous-jacent que HTTP, mais sur un port différent. Vous pouvez également utiliser MQTT via des websockets pour communiquer avec des applications web exécutées dans un navigateur, ou dans des situations où des pare-feu ou d'autres règles réseau bloquent les connexions MQTT standard.

## Télémétrie

Le mot télémétrie est dérivé de racines grecques signifiant mesurer à distance. La télémétrie consiste à collecter des données à partir de capteurs et à les envoyer au cloud.

> 💁 L'un des premiers dispositifs de télémétrie a été inventé en France en 1874 et envoyait en temps réel des données météorologiques et des hauteurs de neige du Mont Blanc à Paris. Il utilisait des fils physiques, car les technologies sans fil n'étaient pas encore disponibles.

Reprenons l'exemple du thermostat intelligent de la leçon 1.

![Un thermostat connecté à Internet utilisant plusieurs capteurs de pièce](../../../../../translated_images/telemetry.21e5d8b97649d2eb.fr.png)

Le thermostat dispose de capteurs de température pour collecter des données de télémétrie. Il aurait probablement un capteur de température intégré et pourrait se connecter à plusieurs capteurs de température externes via un protocole sans fil tel que [Bluetooth Low Energy](https://wikipedia.org/wiki/Bluetooth_Low_Energy) (BLE).

Un exemple de données de télémétrie qu'il pourrait envoyer serait :

| Nom | Valeur | Description |
| ---- | ----- | ----------- |
| `thermostat_temperature` | 18°C | La température mesurée par le capteur de température intégré au thermostat |
| `livingroom_temperature` | 19°C | La température mesurée par un capteur de température distant nommé `livingroom` pour identifier la pièce où il se trouve |
| `bedroom_temperature` | 21°C | La température mesurée par un capteur de température distant nommé `bedroom` pour identifier la pièce où il se trouve |

Le service cloud peut ensuite utiliser ces données de télémétrie pour prendre des décisions sur les commandes à envoyer pour contrôler le chauffage.

### Envoyer des données de télémétrie depuis votre appareil IoT

La prochaine étape pour ajouter un contrôle via Internet à votre veilleuse consiste à envoyer les données de niveau de lumière au courtier MQTT sur un sujet de télémétrie.

#### Tâche - envoyer des données de télémétrie depuis votre appareil IoT

Envoyez les données de niveau de lumière au courtier MQTT.

Les données sont envoyées encodées en JSON - abréviation de JavaScript Object Notation, un standard pour encoder des données en texte à l'aide de paires clé/valeur.

✅ Si vous ne connaissez pas JSON, vous pouvez en apprendre davantage sur la [documentation JSON.org](https://www.json.org/).

Suivez l'étape correspondante ci-dessous pour envoyer des données de télémétrie depuis votre appareil au courtier MQTT :

* [Arduino - Wio Terminal](wio-terminal-telemetry.md)
* [Ordinateur monocarte - Raspberry Pi/Appareil IoT virtuel](single-board-computer-telemetry.md)

### Recevoir des données de télémétrie depuis le courtier MQTT

Il ne sert à rien d'envoyer des données de télémétrie si rien ne les écoute. Les données de niveau de lumière nécessitent un programme pour les traiter. Ce code "serveur" est le type de code que vous déploierez sur un service cloud dans le cadre d'une application IoT plus large, mais ici, vous allez exécuter ce code localement sur votre ordinateur (ou sur votre Pi si vous codez directement dessus). Le code serveur est une application Python qui écoute les messages de télémétrie via MQTT avec les niveaux de lumière. Plus tard dans cette leçon, vous le ferez répondre avec un message de commande contenant des instructions pour allumer ou éteindre la LED.

✅ Faites des recherches : Que se passe-t-il pour les messages MQTT s'il n'y a aucun récepteur ?

#### Installer Python et VS Code

Si vous n'avez pas Python et VS Code installés localement, vous devrez les installer pour coder le serveur. Si vous utilisez un appareil IoT virtuel ou travaillez sur votre Raspberry Pi, vous pouvez ignorer cette étape, car ils devraient déjà être installés et configurés.

##### Tâche - installer Python et VS Code

Installez Python et VS Code.

1. Installez Python. Consultez la [page de téléchargement de Python](https://www.python.org/downloads/) pour obtenir des instructions sur l'installation de la dernière version de Python.

1. Installez Visual Studio Code (VS Code). C'est l'éditeur que vous utiliserez pour écrire le code de votre appareil virtuel en Python. Consultez la [documentation de VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) pour obtenir des instructions sur l'installation de VS Code.
💁 Vous êtes libre d'utiliser n'importe quel IDE ou éditeur Python pour ces leçons si vous avez un outil préféré, mais les leçons fourniront des instructions basées sur l'utilisation de VS Code.
1. Installez l'extension Pylance pour VS Code. Il s'agit d'une extension pour VS Code qui fournit un support pour le langage Python. Consultez la [documentation de l'extension Pylance](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) pour les instructions d'installation dans VS Code.

#### Configurer un environnement virtuel Python

L'une des fonctionnalités puissantes de Python est la possibilité d'installer des [packages pip](https://pypi.org) - ce sont des packages de code écrits par d'autres personnes et publiés sur Internet. Vous pouvez installer un package pip sur votre ordinateur avec une seule commande, puis utiliser ce package dans votre code. Vous utiliserez pip pour installer un package permettant de communiquer via MQTT.

Par défaut, lorsque vous installez un package, il est disponible partout sur votre ordinateur, ce qui peut entraîner des problèmes de versions de packages - par exemple, une application dépendant d'une version d'un package qui ne fonctionne plus lorsque vous installez une nouvelle version pour une autre application. Pour contourner ce problème, vous pouvez utiliser un [environnement virtuel Python](https://docs.python.org/3/library/venv.html), qui est essentiellement une copie de Python dans un dossier dédié. Lorsque vous installez des packages pip, ils sont installés uniquement dans ce dossier.

##### Tâche - configurer un environnement virtuel Python

Configurez un environnement virtuel Python et installez les packages pip MQTT.

1. Depuis votre terminal ou ligne de commande, exécutez les commandes suivantes à l'emplacement de votre choix pour créer et naviguer vers un nouveau répertoire :

    ```sh
    mkdir nightlight-server
    cd nightlight-server
    ```

1. Exécutez ensuite la commande suivante pour créer un environnement virtuel dans le dossier `.venv` :

    ```sh
    python3 -m venv .venv
    ```

    > 💁 Vous devez explicitement appeler `python3` pour créer l'environnement virtuel, au cas où Python 2 serait également installé sur votre machine. Si Python 2 est installé, appeler `python` utilisera Python 2 au lieu de Python 3.

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

    > 💁 Ces commandes doivent être exécutées depuis le même emplacement où vous avez exécuté la commande pour créer l'environnement virtuel. Vous n'aurez jamais besoin de naviguer dans le dossier `.venv`, vous devez toujours exécuter la commande d'activation et toutes les commandes pour installer des packages ou exécuter du code depuis le dossier où vous avez créé l'environnement virtuel.

1. Une fois l'environnement virtuel activé, la commande `python` par défaut exécutera la version de Python utilisée pour créer l'environnement virtuel. Exécutez la commande suivante pour vérifier la version :

    ```sh
    python --version
    ```

    La sortie sera similaire à ceci :

    ```output
    (.venv) ➜  nightlight-server python --version
    Python 3.9.1
    ```

    > 💁 Votre version de Python peut être différente - tant qu'elle est en version 3.6 ou supérieure, c'est bon. Sinon, supprimez ce dossier, installez une version plus récente de Python et réessayez.

1. Exécutez les commandes suivantes pour installer le package pip pour [Paho-MQTT](https://pypi.org/project/paho-mqtt/), une bibliothèque MQTT populaire.

    ```sh
    pip install paho-mqtt
    ```

    Ce package pip sera uniquement installé dans l'environnement virtuel et ne sera pas disponible en dehors de celui-ci.

#### Écrire le code du serveur

Le code du serveur peut maintenant être écrit en Python.

##### Tâche - écrire le code du serveur

Écrivez le code du serveur.

1. Depuis votre terminal ou ligne de commande, exécutez la commande suivante à l'intérieur de l'environnement virtuel pour créer un fichier Python nommé `app.py` :

    * Sur Windows, exécutez :

        ```cmd
        type nul > app.py
        ```

    * Sur macOS ou Linux, exécutez :

        ```cmd
        touch app.py
        ```

1. Ouvrez le dossier actuel dans VS Code :

    ```sh
    code .
    ```

1. Lorsque VS Code se lance, il activera l'environnement virtuel Python. Cela sera indiqué dans la barre d'état en bas :

    ![VS Code montrant l'environnement virtuel sélectionné](../../../../../translated_images/vscode-virtual-env.8ba42e04c3d533cf.fr.png)

1. Si le terminal de VS Code est déjà ouvert au démarrage de VS Code, l'environnement virtuel ne sera pas activé dans celui-ci. Le plus simple est de fermer le terminal en utilisant le bouton **Kill the active terminal instance** :

    ![Bouton de fermeture du terminal actif dans VS Code](../../../../../translated_images/vscode-kill-terminal.1cc4de7c6f25ee08.fr.png)

1. Lancez un nouveau terminal VS Code en sélectionnant *Terminal -> New Terminal*, ou en appuyant sur `` CTRL+` ``. Le nouveau terminal chargera l'environnement virtuel, avec l'appel à l'activation apparaissant dans le terminal. Le nom de l'environnement virtuel (`.venv`) sera également dans l'invite :

    ```output
    ➜  nightlight-server source .venv/bin/activate
    (.venv) ➜  nightlight 
    ```

1. Ouvrez le fichier `app.py` depuis l'explorateur de VS Code et ajoutez le code suivant :

    ```python
    import json
    import time
    
    import paho.mqtt.client as mqtt
    
    id = '<ID>'
    
    client_telemetry_topic = id + '/telemetry'
    client_name = id + 'nightlight_server'
    
    mqtt_client = mqtt.Client(client_name)
    mqtt_client.connect('test.mosquitto.org')
    
    mqtt_client.loop_start()
    
    def handle_telemetry(client, userdata, message):
        payload = json.loads(message.payload.decode())
        print("Message received:", payload)
    
    mqtt_client.subscribe(client_telemetry_topic)
    mqtt_client.on_message = handle_telemetry
    
    while True:
        time.sleep(2)
    ```

    Remplacez `<ID>` à la ligne 6 par l'ID unique que vous avez utilisé lors de la création du code de votre appareil.

    ⚠️ Cet **ID doit** être le même que celui utilisé sur votre appareil, sinon le code du serveur ne s'abonnera pas ou ne publiera pas sur le bon sujet.

    Ce code crée un client MQTT avec un nom unique et se connecte au broker *test.mosquitto.org*. Il démarre ensuite une boucle de traitement qui s'exécute en arrière-plan pour écouter les messages sur tous les sujets abonnés.

    Le client s'abonne ensuite aux messages sur le sujet de télémétrie et définit une fonction appelée lorsqu'un message est reçu. Lorsqu'un message de télémétrie est reçu, la fonction `handle_telemetry` est appelée, affichant le message reçu dans la console.

    Enfin, une boucle infinie maintient l'application en cours d'exécution. Le client MQTT écoute les messages en arrière-plan et fonctionne tant que l'application principale est en cours d'exécution.

1. Depuis le terminal de VS Code, exécutez la commande suivante pour lancer votre application Python :

    ```sh
    python app.py
    ```

    L'application commencera à écouter les messages de l'appareil IoT.

1. Assurez-vous que votre appareil fonctionne et envoie des messages de télémétrie. Ajustez les niveaux de lumière détectés par votre appareil physique ou virtuel. Les messages reçus seront affichés dans le terminal.

    ```output
    (.venv) ➜  nightlight-server python app.py
    Message received: {'light': 0}
    Message received: {'light': 400}
    ```

    Le fichier app.py dans l'environnement virtuel nightlight doit être en cours d'exécution pour que le fichier app.py dans l'environnement virtuel nightlight-server puisse recevoir les messages envoyés.

> 💁 Vous pouvez trouver ce code dans le dossier [code-server/server](../../../../../1-getting-started/lessons/4-connect-internet/code-server/server).

### À quelle fréquence envoyer la télémétrie ?

Une considération importante avec la télémétrie est la fréquence à laquelle mesurer et envoyer les données. La réponse est : cela dépend. Si vous mesurez souvent, vous pouvez réagir plus rapidement aux changements, mais vous consommez plus d'énergie, plus de bande passante, générez plus de données et avez besoin de plus de ressources cloud pour les traiter. Vous devez mesurer suffisamment souvent, mais pas trop.

Pour un thermostat, mesurer toutes les quelques minutes est probablement suffisant, car les températures ne changent pas si souvent. Si vous ne mesurez qu'une fois par jour, vous pourriez chauffer votre maison pour des températures nocturnes en plein milieu d'une journée ensoleillée, tandis que si vous mesurez chaque seconde, vous aurez des milliers de mesures de température inutiles qui consommeront la vitesse et la bande passante Internet des utilisateurs (un problème pour ceux ayant des forfaits limités), utiliseront plus d'énergie, ce qui peut poser problème pour des appareils alimentés par batterie comme des capteurs distants, et augmenteront le coût des ressources cloud nécessaires pour les traiter et les stocker.

Si vous surveillez des données autour d'une machine dans une usine qui, en cas de panne, pourrait causer des dommages catastrophiques et des pertes de revenus de plusieurs millions de dollars, alors mesurer plusieurs fois par seconde pourrait être nécessaire. Il vaut mieux gaspiller de la bande passante que manquer une télémétrie indiquant qu'une machine doit être arrêtée et réparée avant de se casser.

> 💁 Dans ce cas, vous pourriez envisager d'utiliser un appareil en périphérie pour traiter d'abord la télémétrie afin de réduire la dépendance à Internet.

### Perte de connectivité

Les connexions Internet peuvent être peu fiables, avec des pannes fréquentes. Que doit faire un appareil IoT dans ces circonstances - doit-il perdre les données ou les stocker jusqu'à ce que la connectivité soit rétablie ? Encore une fois, la réponse est : cela dépend.

Pour un thermostat, les données peuvent probablement être perdues dès qu'une nouvelle mesure de température est prise. Le système de chauffage ne se soucie pas qu'il faisait 20,5°C il y a 20 minutes si la température est maintenant de 19°C, c'est la température actuelle qui détermine si le chauffage doit être allumé ou éteint.

Pour des machines, vous pourriez vouloir conserver les données, surtout si elles sont utilisées pour détecter des tendances. Certains modèles d'apprentissage automatique peuvent détecter des anomalies dans des flux de données en examinant les données sur une période définie (comme la dernière heure) et en repérant des données anormales. Cela est souvent utilisé pour la maintenance prédictive, en recherchant des indications qu'une panne pourrait survenir bientôt afin de pouvoir réparer ou remplacer avant que cela ne se produise. Vous pourriez vouloir que chaque bit de télémétrie d'une machine soit envoyé pour qu'il puisse être traité pour la détection d'anomalies. Une fois que l'appareil IoT peut se reconnecter, il enverra toute la télémétrie générée pendant la panne Internet.

Les concepteurs d'appareils IoT devraient également envisager si l'appareil IoT peut être utilisé pendant une panne Internet ou une perte de signal due à l'emplacement. Un thermostat intelligent devrait pouvoir prendre des décisions limitées pour contrôler le chauffage s'il ne peut pas envoyer de télémétrie au cloud en raison d'une panne.

[![Cette Ferrari est devenue inutilisable parce que quelqu'un a essayé de la mettre à jour sous terre où il n'y a pas de réception cellulaire](../../../../../translated_images/bricked-car.dc38f8efadc6c59d76211f981a521efb300939283dee468f79503aae3ec67615.fr.png)](https://twitter.com/internetofshit/status/1315736960082808832)

Pour que MQTT gère une perte de connectivité, le code de l'appareil et du serveur devra être responsable de garantir la livraison des messages si nécessaire, par exemple en exigeant que tous les messages envoyés soient confirmés par des messages supplémentaires sur un sujet de réponse, et si ce n'est pas le cas, ils sont mis en file d'attente manuellement pour être rejoués plus tard.

## Commandes

Les commandes sont des messages envoyés par le cloud à un appareil, lui demandant de faire quelque chose. La plupart du temps, cela implique de donner une sorte de sortie via un actionneur, mais cela peut être une instruction pour l'appareil lui-même, comme redémarrer ou collecter des données supplémentaires de télémétrie et les renvoyer en réponse à la commande.

![Un thermostat connecté à Internet recevant une commande pour allumer le chauffage](../../../../../translated_images/commands.d6c06bbbb3a02cce95f2831a1c331daf6dedd4e470c4aa2b0ae54f332016e504.fr.png)

Un thermostat pourrait recevoir une commande du cloud pour allumer le chauffage. Sur la base des données de télémétrie de tous les capteurs, si le service cloud a décidé que le chauffage doit être allumé, il envoie la commande correspondante.

### Envoyer des commandes au broker MQTT

L'étape suivante pour notre veilleuse contrôlée par Internet est que le code du serveur envoie une commande à l'appareil IoT pour contrôler la lumière en fonction des niveaux de lumière détectés.

1. Ouvrez le code du serveur dans VS Code.

1. Ajoutez la ligne suivante après la déclaration de `client_telemetry_topic` pour définir le sujet auquel envoyer les commandes :

    ```python
    server_command_topic = id + '/commands'
    ```

1. Ajoutez le code suivant à la fin de la fonction `handle_telemetry` :

    ```python
    command = { 'led_on' : payload['light'] < 300 }
    print("Sending message:", command)
    
    client.publish(server_command_topic, json.dumps(command))
    ```

    Cela envoie un message JSON au sujet des commandes avec la valeur de `led_on` définie sur true ou false en fonction de si la lumière est inférieure à 300 ou non. Si la lumière est inférieure à 300, true est envoyé pour demander à l'appareil d'allumer la LED.

1. Exécutez le code comme précédemment.

1. Ajustez les niveaux de lumière détectés par votre appareil physique ou virtuel. Les messages reçus et les commandes envoyées seront affichés dans le terminal :

    ```output
    (.venv) ➜  nightlight-server python app.py
    Message received: {'light': 0}
    Sending message: {'led_on': True}
    Message received: {'light': 400}
    Sending message: {'led_on': False}
    ```

> 💁 La télémétrie et les commandes sont envoyées sur un seul sujet chacun. Cela signifie que la télémétrie de plusieurs appareils apparaîtra sur le même sujet de télémétrie, et les commandes pour plusieurs appareils apparaîtront sur le même sujet de commandes. Si vous vouliez envoyer une commande à un appareil spécifique, vous pourriez utiliser plusieurs sujets, nommés avec un identifiant unique d'appareil, comme `/commands/device1`, `/commands/device2`. De cette façon, un appareil peut écouter uniquement les messages qui lui sont destinés.

> 💁 Vous pouvez trouver ce code dans le dossier [code-commands/server](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/server).

### Gérer les commandes sur l'appareil IoT

Maintenant que des commandes sont envoyées depuis le serveur, vous pouvez ajouter du code à l'appareil IoT pour les gérer et contrôler la LED.

Suivez l'étape pertinente ci-dessous pour écouter les commandes du broker MQTT :

* [Arduino - Wio Terminal](wio-terminal-commands.md)
* [Ordinateur monocarte - Raspberry Pi/Appareil IoT virtuel](single-board-computer-commands.md)

Une fois ce code écrit et exécuté, expérimentez en modifiant les niveaux de lumière. Observez la sortie du serveur et de l'appareil, et regardez la LED lorsque vous changez les niveaux de lumière.

### Perte de connectivité

Que doit faire un service cloud s'il doit envoyer une commande à un appareil IoT hors ligne ? Encore une fois, la réponse est : cela dépend.

Si la dernière commande remplace une précédente, alors les précédentes peuvent probablement être ignorées. Si un service cloud envoie une commande pour allumer le chauffage, puis une commande pour l'éteindre, alors la commande d'allumage peut être ignorée et ne pas être renvoyée.

Si les commandes doivent être traitées dans l'ordre, comme déplacer un bras robotique vers le haut, puis fermer une pince, elles doivent être envoyées dans l'ordre une fois la connectivité rétablie.

✅ Comment le code de l'appareil ou du serveur pourrait-il garantir que les commandes sont toujours envoyées et traitées dans l'ordre via MQTT si nécessaire ?

---

## 🚀 Défi

Le défi des trois dernières leçons était de lister autant d'appareils IoT que possible dans votre maison, école ou lieu de travail, et de décider s'ils sont construits autour de microcontrôleurs ou d'ordinateurs monocartes, ou même d'un mélange des deux, et de réfléchir aux capteurs et actionneurs qu'ils utilisent.
Pour ces appareils, réfléchissez aux messages qu'ils pourraient envoyer ou recevoir. Quelle télémétrie envoient-ils ? Quels messages ou commandes pourraient-ils recevoir ? Pensez-vous qu'ils sont sécurisés ?

## Quiz après le cours

[Quiz après le cours](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/8)

## Révision et étude personnelle

Lisez davantage sur MQTT sur la [page Wikipédia de MQTT](https://wikipedia.org/wiki/MQTT).

Essayez de faire fonctionner un broker MQTT vous-même en utilisant [Mosquitto](https://www.mosquitto.org) et connectez-vous à celui-ci depuis votre appareil IoT et votre code serveur.

> 💁 Conseil - par défaut, Mosquitto n'autorise pas les connexions anonymes (c'est-à-dire sans nom d'utilisateur et mot de passe), et n'autorise pas les connexions depuis l'extérieur de l'ordinateur sur lequel il fonctionne.  
> Vous pouvez résoudre cela avec un fichier de configuration [`mosquitto.conf`](https://www.mosquitto.org/man/mosquitto-conf-5.html) contenant ce qui suit :  
>
> ```sh
> listener 1883 0.0.0.0
> allow_anonymous true
> ```

## Devoir

[Comparer et contraster MQTT avec d'autres protocoles de communication](assignment.md)

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de faire appel à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.