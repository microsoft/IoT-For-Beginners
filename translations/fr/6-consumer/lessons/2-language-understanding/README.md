<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6f4ba69d77f16c4a5110623a96a215c3",
  "translation_date": "2025-08-24T23:59:50+00:00",
  "source_file": "6-consumer/lessons/2-language-understanding/README.md",
  "language_code": "fr"
}
-->
# Comprendre le langage

![Un aperçu en sketchnote de cette leçon](../../../../../translated_images/fr/lesson-22.6148ea28500d9e00c396aaa2649935fb6641362c8f03d8e5e90a676977ab01dd.jpg)

> Sketchnote par [Nitya Narasimhan](https://github.com/nitya). Cliquez sur l'image pour une version agrandie.

## Quiz avant la leçon

[Quiz avant la leçon](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/43)

## Introduction

Dans la dernière leçon, vous avez converti la parole en texte. Pour utiliser cela afin de programmer un minuteur intelligent, votre code devra comprendre ce qui a été dit. Vous pourriez supposer que l'utilisateur prononcera une phrase fixe, comme "Régler un minuteur de 3 minutes", et analyser cette expression pour déterminer la durée du minuteur. Cependant, ce n'est pas très convivial. Si un utilisateur disait "Régler un minuteur pour 3 minutes", vous ou moi comprendrions ce qu'il veut dire, mais votre code ne le comprendrait pas, car il s'attendrait à une phrase fixe.

C'est là que la compréhension du langage entre en jeu, en utilisant des modèles d'IA pour interpréter le texte et renvoyer les détails nécessaires, par exemple en étant capable de comprendre à la fois "Régler un minuteur de 3 minutes" et "Régler un minuteur pour 3 minutes", et en déduisant qu'un minuteur est requis pour 3 minutes.

Dans cette leçon, vous apprendrez à propos des modèles de compréhension du langage, comment les créer, les entraîner et les utiliser dans votre code.

Dans cette leçon, nous aborderons :

* [Compréhension du langage](../../../../../6-consumer/lessons/2-language-understanding)
* [Créer un modèle de compréhension du langage](../../../../../6-consumer/lessons/2-language-understanding)
* [Intentions et entités](../../../../../6-consumer/lessons/2-language-understanding)
* [Utiliser le modèle de compréhension du langage](../../../../../6-consumer/lessons/2-language-understanding)

## Compréhension du langage

Les humains utilisent le langage pour communiquer depuis des centaines de milliers d'années. Nous communiquons avec des mots, des sons ou des actions et comprenons ce qui est dit, non seulement le sens des mots, des sons ou des actions, mais aussi leur contexte. Nous comprenons la sincérité et le sarcasme, permettant aux mêmes mots de signifier des choses différentes selon le ton de notre voix.

✅ Réfléchissez à certaines des conversations que vous avez eues récemment. Quelle partie de la conversation serait difficile à comprendre pour un ordinateur parce qu'elle nécessite du contexte ?

La compréhension du langage, également appelée compréhension du langage naturel, fait partie d'un domaine de l'intelligence artificielle appelé traitement du langage naturel (ou NLP), et concerne la compréhension de la lecture, en essayant de comprendre les détails des mots ou des phrases. Si vous utilisez un assistant vocal comme Alexa ou Siri, vous avez utilisé des services de compréhension du langage. Ce sont les services d'IA en coulisses qui transforment "Alexa, joue le dernier album de Taylor Swift" en ma fille dansant dans le salon sur ses chansons préférées.

> 💁 Les ordinateurs, malgré tous leurs progrès, ont encore un long chemin à parcourir pour vraiment comprendre le texte. Lorsque nous parlons de compréhension du langage avec les ordinateurs, nous ne parlons pas de quelque chose d'aussi avancé que la communication humaine, mais plutôt de prendre quelques mots et d'extraire des détails clés.

En tant qu'humains, nous comprenons le langage sans vraiment y réfléchir. Si je demandais à un autre humain de "jouer le dernier album de Taylor Swift", il saurait instinctivement ce que je veux dire. Pour un ordinateur, c'est plus difficile. Il devrait prendre les mots, convertis de la parole en texte, et déterminer les éléments suivants :

* De la musique doit être jouée
* La musique est de l'artiste Taylor Swift
* La musique spécifique est un album entier composé de plusieurs morceaux dans un ordre précis
* Taylor Swift a de nombreux albums, donc ils doivent être triés par ordre chronologique et le plus récemment publié est celui requis

✅ Pensez à d'autres phrases que vous avez prononcées en faisant des demandes, comme commander un café ou demander à un membre de votre famille de vous passer quelque chose. Essayez de les décomposer en éléments d'information qu'un ordinateur devrait extraire pour comprendre la phrase.

Les modèles de compréhension du langage sont des modèles d'IA entraînés à extraire certains détails du langage, puis entraînés pour des tâches spécifiques en utilisant l'apprentissage par transfert, de la même manière que vous avez entraîné un modèle de vision personnalisée en utilisant un petit ensemble d'images. Vous pouvez prendre un modèle, puis l'entraîner en utilisant le texte que vous voulez qu'il comprenne.

## Créer un modèle de compréhension du langage

![Le logo LUIS](../../../../../translated_images/fr/luis-logo.5cb4f3e88c020ee6df4f614e8831f4a4b6809a7247bf52085fb48d629ef9be52.png)

Vous pouvez créer des modèles de compréhension du langage en utilisant LUIS, un service de compréhension du langage de Microsoft qui fait partie des Cognitive Services.

### Tâche - créer une ressource d'auteur

Pour utiliser LUIS, vous devez créer une ressource d'auteur.

1. Utilisez la commande suivante pour créer une ressource d'auteur dans votre groupe de ressources `smart-timer` :

    ```python
    az cognitiveservices account create --name smart-timer-luis-authoring \
                                        --resource-group smart-timer \
                                        --kind LUIS.Authoring \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Remplacez `<location>` par l'emplacement que vous avez utilisé lors de la création du groupe de ressources.

    > ⚠️ LUIS n'est pas disponible dans toutes les régions, donc si vous obtenez l'erreur suivante :
    >
    > ```output
    > InvalidApiSetId: The account type 'LUIS.Authoring' is either invalid or unavailable in given region.
    > ```
    >
    > choisissez une autre région.

    Cela créera une ressource d'auteur LUIS gratuite.

### Tâche - créer une application de compréhension du langage

1. Ouvrez le portail LUIS à [luis.ai](https://luis.ai?WT.mc_id=academic-17441-jabenn) dans votre navigateur, et connectez-vous avec le même compte que vous avez utilisé pour Azure.

1. Suivez les instructions dans la boîte de dialogue pour sélectionner votre abonnement Azure, puis sélectionnez la ressource `smart-timer-luis-authoring` que vous venez de créer.

1. Dans la liste *Applications de conversation*, sélectionnez le bouton **Nouvelle application** pour créer une nouvelle application. Nommez la nouvelle application `smart-timer`, et définissez la *Culture* sur votre langue.

    > 💁 Il y a un champ pour une ressource de prédiction. Vous pouvez créer une deuxième ressource uniquement pour la prédiction, mais la ressource d'auteur gratuite permet 1 000 prédictions par mois, ce qui devrait suffire pour le développement, donc vous pouvez laisser ce champ vide.

1. Lisez le guide qui apparaît une fois que vous avez créé l'application pour comprendre les étapes nécessaires pour entraîner le modèle de compréhension du langage. Fermez ce guide lorsque vous avez terminé.

## Intentions et entités

La compréhension du langage repose sur les *intentions* et les *entités*. Les intentions représentent ce que les mots veulent dire, par exemple jouer de la musique, régler un minuteur ou commander de la nourriture. Les entités représentent ce à quoi l'intention fait référence, comme l'album, la durée du minuteur ou le type de nourriture. Chaque phrase interprétée par le modèle doit avoir au moins une intention, et éventuellement une ou plusieurs entités.

Quelques exemples :

| Phrase                                              | Intention         | Entités                                    |
| --------------------------------------------------- | ----------------- | ------------------------------------------ |
| "Joue le dernier album de Taylor Swift"             | *jouer de la musique* | *le dernier album de Taylor Swift*         |
| "Régler un minuteur de 3 minutes"                   | *régler un minuteur* | *3 minutes*                                |
| "Annuler mon minuteur"                              | *annuler un minuteur* | Aucune                                     |
| "Commander 3 grandes pizzas à l'ananas et une salade césar" | *commander de la nourriture* | *3 grandes pizzas à l'ananas*, *salade césar* |

✅ Avec les phrases auxquelles vous avez réfléchi plus tôt, quelle serait l'intention et quelles seraient les entités dans ces phrases ?

Pour entraîner LUIS, vous commencez par définir les entités. Celles-ci peuvent être une liste fixe de termes ou apprises à partir du texte. Par exemple, vous pourriez fournir une liste fixe des aliments disponibles sur votre menu, avec des variations (ou synonymes) de chaque mot, comme *aubergine* et *eggplant* comme variations de *aubergine*. LUIS dispose également d'entités préconstruites qui peuvent être utilisées, comme les nombres et les lieux.

Pour régler un minuteur, vous pourriez avoir une entité utilisant les entités de nombres préconstruites pour le temps, et une autre pour les unités, comme les minutes et les secondes. Chaque unité aurait plusieurs variations pour couvrir les formes singulières et plurielles - comme minute et minutes.

Une fois les entités définies, vous créez des intentions. Celles-ci sont apprises par le modèle en fonction des phrases d'exemple que vous fournissez (appelées énoncés). Par exemple, pour une intention *régler un minuteur*, vous pourriez fournir les phrases suivantes :

* `régler un minuteur de 1 seconde`
* `régler un minuteur pour 1 minute et 12 secondes`
* `régler un minuteur pour 3 minutes`
* `régler un minuteur de 9 minutes et 30 secondes`

Vous indiquez ensuite à LUIS quelles parties de ces phrases correspondent aux entités :

![La phrase régler un minuteur pour 1 minute et 12 secondes décomposée en entités](../../../../../translated_images/fr/sentence-as-intent-entities.301401696f992259.webp)

La phrase `régler un minuteur pour 1 minute et 12 secondes` a l'intention `régler un minuteur`. Elle contient également 2 entités avec 2 valeurs chacune :

|            | temps | unité   |
| ---------- | ----- | ------- |
| 1 minute   | 1     | minute  |
| 12 secondes | 12    | seconde |

Pour entraîner un bon modèle, vous avez besoin d'une gamme de phrases d'exemple différentes pour couvrir les nombreuses façons dont quelqu'un pourrait demander la même chose.

> 💁 Comme pour tout modèle d'IA, plus vous utilisez de données et plus ces données sont précises pour l'entraînement, meilleur sera le modèle.

✅ Pensez aux différentes façons dont vous pourriez demander la même chose et attendre qu'un humain comprenne.

### Tâche - ajouter des entités aux modèles de compréhension du langage

Pour le minuteur, vous devez ajouter 2 entités - une pour l'unité de temps (minutes ou secondes), et une pour le nombre de minutes ou de secondes.

Vous pouvez trouver des instructions pour utiliser le portail LUIS dans la documentation [Quickstart : Créer votre application dans le portail LUIS sur Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/luis/luis-get-started-create-app?WT.mc_id=academic-17441-jabenn).

1. Depuis le portail LUIS, sélectionnez l'onglet *Entités* et ajoutez l'entité préconstruite *nombre* en sélectionnant le bouton **Ajouter une entité préconstruite**, puis en sélectionnant *nombre* dans la liste.

1. Créez une nouvelle entité pour l'unité de temps en utilisant le bouton **Créer**. Nommez l'entité `unité de temps` et définissez le type sur *Liste*. Ajoutez des valeurs pour `minute` et `seconde` à la liste des *Valeurs normalisées*, en ajoutant les formes singulières et plurielles à la liste des *Synonymes*. Appuyez sur `Entrée` après avoir ajouté chaque synonyme pour l'ajouter à la liste.

    | Valeur normalisée | Synonymes        |
    | ----------------- | ---------------- |
    | minute            | minute, minutes |
    | seconde           | seconde, secondes |

### Tâche - ajouter des intentions aux modèles de compréhension du langage

1. Depuis l'onglet *Intentions*, sélectionnez le bouton **Créer** pour créer une nouvelle intention. Nommez cette intention `régler un minuteur`.

1. Dans les exemples, entrez différentes façons de régler un minuteur en utilisant à la fois les minutes, les secondes et une combinaison de minutes et de secondes. Les exemples pourraient être :

    * `régler un minuteur de 1 seconde`
    * `régler un minuteur de 4 minutes`
    * `régler un minuteur de quatre minutes et six secondes`
    * `régler un minuteur de 9 minutes et 30 secondes`
    * `régler un minuteur pour 1 minute et 12 secondes`
    * `régler un minuteur pour 3 minutes`
    * `régler un minuteur pour 3 minutes et 1 seconde`
    * `régler un minuteur pour trois minutes et une seconde`
    * `régler un minuteur pour 1 minute et 1 seconde`
    * `régler un minuteur pour 30 secondes`
    * `régler un minuteur pour 1 seconde`

    Mélangez les nombres en mots et en chiffres pour que le modèle apprenne à gérer les deux.

1. À mesure que vous entrez chaque exemple, LUIS commencera à détecter les entités et soulignera et étiquettera celles qu'il trouve.

    ![Les exemples avec les nombres et les unités de temps soulignés par LUIS](../../../../../translated_images/fr/luis-intent-examples.25716580b2d2723cf1bafdf277d015c7f046d8cfa20f27bddf3a0873ec45fab7.png)

### Tâche - entraîner et tester le modèle

1. Une fois les entités et les intentions configurées, vous pouvez entraîner le modèle en utilisant le bouton **Entraîner** dans le menu supérieur. Sélectionnez ce bouton, et le modèle devrait s'entraîner en quelques secondes. Le bouton sera grisé pendant l'entraînement, et sera réactivé une fois terminé.

1. Sélectionnez le bouton **Tester** dans le menu supérieur pour tester le modèle de compréhension du langage. Entrez un texte tel que `régler un minuteur pour 5 minutes et 4 secondes` et appuyez sur Entrée. La phrase apparaîtra dans une boîte sous la zone de texte dans laquelle vous l'avez tapée, et en dessous, vous verrez l'*intention principale*, ou l'intention détectée avec la probabilité la plus élevée. Cela devrait être `régler un minuteur`. Le nom de l'intention sera suivi de la probabilité que l'intention détectée soit la bonne.

1. Sélectionnez l'option **Inspecter** pour voir une analyse des résultats. Vous verrez l'intention principale avec son pourcentage de probabilité, ainsi que des listes des entités détectées.

1. Fermez le volet *Tester* lorsque vous avez terminé les tests.

### Tâche - publier le modèle

Pour utiliser ce modèle dans le code, vous devez le publier. Lors de la publication depuis LUIS, vous pouvez publier dans un environnement de test ou dans un environnement de production pour une version complète. Dans cette leçon, un environnement de test est suffisant.

1. Depuis le portail LUIS, sélectionnez le bouton **Publier** dans le menu supérieur.

1. Assurez-vous que *Slot de test* est sélectionné, puis cliquez sur **Terminé**. Vous verrez une notification lorsque l'application est publiée.

1. Vous pouvez tester cela en utilisant curl. Pour construire la commande curl, vous avez besoin de trois valeurs : l'endpoint, l'ID de l'application (App ID) et une clé API. Ces informations peuvent être consultées dans l'onglet **GÉRER** qui peut être sélectionné dans le menu supérieur.

    1. Depuis la section *Paramètres*, copiez l'App ID
1. Dans la section *Ressources Azure*, sélectionnez *Ressource d'auteur*, et copiez la *Clé principale* et l'*URL de point de terminaison*.

1. Exécutez la commande curl suivante dans votre invite de commande ou terminal :

    ```sh
    curl "<endpoint url>/luis/prediction/v3.0/apps/<app id>/slots/staging/predict" \
          --request GET \
          --get \
          --data "subscription-key=<primary key>" \
          --data "verbose=false" \
          --data "show-all-intents=true" \
          --data-urlencode "query=<sentence>"
    ```

    Remplacez `<endpoint url>` par l'URL de point de terminaison de la section *Ressources Azure*.

    Remplacez `<app id>` par l'ID de l'application de la section *Paramètres*.

    Remplacez `<primary key>` par la Clé principale de la section *Ressources Azure*.

    Remplacez `<sentence>` par la phrase que vous souhaitez tester.

1. La sortie de cet appel sera un document JSON détaillant la requête, l'intention principale, et une liste d'entités classées par type.

    ```JSON
    {
        "query": "set a timer for 45 minutes and 12 seconds",
        "prediction": {
            "topIntent": "set timer",
            "intents": {
                "set timer": {
                    "score": 0.97031575
                },
                "None": {
                    "score": 0.02205793
                }
            },
            "entities": {
                "number": [
                    45,
                    12
                ],
                "time-unit": [
                    [
                        "minute"
                    ],
                    [
                        "second"
                    ]
                ]
            }
        }
    }
    ```

    Le JSON ci-dessus provient d'une requête avec `définir un minuteur pour 45 minutes et 12 secondes` :

    * L'intention principale était `définir minuteur` avec une probabilité de 97 %.
    * Deux entités *nombre* ont été détectées : `45` et `12`.
    * Deux entités *unité de temps* ont été détectées : `minute` et `seconde`.

## Utiliser le modèle de compréhension du langage

Une fois publié, le modèle LUIS peut être appelé depuis du code. Dans les leçons précédentes, vous avez utilisé un IoT Hub pour gérer la communication avec les services cloud, envoyer des télémétries et écouter des commandes. Cela est très asynchrone - une fois la télémétrie envoyée, votre code n'attend pas de réponse, et si le service cloud est hors ligne, vous ne le sauriez pas.

Pour un minuteur intelligent, nous voulons une réponse immédiate, afin de pouvoir informer l'utilisateur qu'un minuteur est défini ou l'alerter que les services cloud sont indisponibles. Pour ce faire, notre appareil IoT appellera directement un point de terminaison web, au lieu de dépendre d'un IoT Hub.

Plutôt que d'appeler LUIS depuis l'appareil IoT, vous pouvez utiliser du code sans serveur avec un type de déclencheur différent - un déclencheur HTTP. Cela permet à votre application de fonction d'écouter les requêtes REST et d'y répondre. Cette fonction sera un point de terminaison REST que votre appareil pourra appeler.

> 💁 Bien que vous puissiez appeler LUIS directement depuis votre appareil IoT, il est préférable d'utiliser quelque chose comme du code sans serveur. Ainsi, lorsque vous souhaitez changer l'application LUIS que vous appelez, par exemple lorsque vous entraînez un meilleur modèle ou un modèle dans une langue différente, vous n'avez qu'à mettre à jour votre code cloud, sans avoir à redéployer le code sur potentiellement des milliers ou des millions d'appareils IoT.

### Tâche - créer une application de fonctions sans serveur

1. Créez une application de fonctions Azure appelée `smart-timer-trigger`, et ouvrez-la dans VS Code.

1. Ajoutez un déclencheur HTTP à cette application appelé `speech-trigger` en utilisant la commande suivante depuis le terminal de VS Code :

    ```sh
    func new --name text-to-timer --template "HTTP trigger"
    ```

    Cela créera un déclencheur HTTP appelé `text-to-timer`.

1. Testez le déclencheur HTTP en exécutant l'application de fonctions. Lorsqu'elle s'exécute, vous verrez le point de terminaison listé dans la sortie :

    ```output
    Functions:
    
            text-to-timer: [GET,POST] http://localhost:7071/api/text-to-timer
    ```

    Testez cela en chargeant l'URL [http://localhost:7071/api/text-to-timer](http://localhost:7071/api/text-to-timer) dans votre navigateur.

    ```output
    This HTTP triggered function executed successfully. Pass a name in the query string or in the request body for a personalized response.
    ```

### Tâche - utiliser le modèle de compréhension du langage

1. Le SDK pour LUIS est disponible via un package Pip. Ajoutez la ligne suivante au fichier `requirements.txt` pour ajouter la dépendance à ce package :

    ```sh
    azure-cognitiveservices-language-luis
    ```

1. Assurez-vous que le terminal de VS Code a l'environnement virtuel activé, et exécutez la commande suivante pour installer les packages Pip :

    ```sh
    pip install -r requirements.txt
    ```

    > 💁 Si vous rencontrez des erreurs, vous devrez peut-être mettre à jour pip avec la commande suivante :
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. Ajoutez de nouvelles entrées au fichier `local.settings.json` pour votre clé API LUIS, l'URL de point de terminaison, et l'ID de l'application depuis l'onglet **GÉRER** du portail LUIS :

    ```JSON
    "LUIS_KEY": "<primary key>",
    "LUIS_ENDPOINT_URL": "<endpoint url>",
    "LUIS_APP_ID": "<app id>"
    ```

    Remplacez `<endpoint url>` par l'URL de point de terminaison de la section *Ressources Azure* de l'onglet **GÉRER**. Cela sera `https://<location>.api.cognitive.microsoft.com/`.

    Remplacez `<app id>` par l'ID de l'application de la section *Paramètres* de l'onglet **GÉRER**.

    Remplacez `<primary key>` par la Clé principale de la section *Ressources Azure* de l'onglet **GÉRER**.

1. Ajoutez les imports suivants au fichier `__init__.py` :

    ```python
    import json
    import os
    from azure.cognitiveservices.language.luis.runtime import LUISRuntimeClient
    from msrest.authentication import CognitiveServicesCredentials
    ```

    Cela importe certaines bibliothèques système, ainsi que les bibliothèques pour interagir avec LUIS.

1. Supprimez le contenu de la méthode `main`, et ajoutez le code suivant :

    ```python
    luis_key = os.environ['LUIS_KEY']
    endpoint_url = os.environ['LUIS_ENDPOINT_URL']
    app_id = os.environ['LUIS_APP_ID']
    
    credentials = CognitiveServicesCredentials(luis_key)
    client = LUISRuntimeClient(endpoint=endpoint_url, credentials=credentials)
    ```

    Cela charge les valeurs que vous avez ajoutées au fichier `local.settings.json` pour votre application LUIS, crée un objet de crédentiels avec votre clé API, puis crée un objet client LUIS pour interagir avec votre application LUIS.

1. Ce déclencheur HTTP sera appelé en passant le texte à comprendre sous forme de JSON, avec le texte dans une propriété appelée `text`. Le code suivant extrait la valeur du corps de la requête HTTP et l'enregistre dans la console. Ajoutez ce code à la fonction `main` :

    ```python
    req_body = req.get_json()
    text = req_body['text']
    logging.info(f'Request - {text}')
    ```

1. Les prédictions sont demandées à LUIS en envoyant une requête de prédiction - un document JSON contenant le texte à prédire. Créez cela avec le code suivant :

    ```python
    prediction_request = { 'query' : text }
    ```

1. Cette requête peut ensuite être envoyée à LUIS, en utilisant l'emplacement de staging où votre application a été publiée :

    ```python
    prediction_response = client.prediction.get_slot_prediction(app_id, 'Staging', prediction_request)
    ```

1. La réponse de prédiction contient l'intention principale - l'intention avec le score de prédiction le plus élevé, ainsi que les entités. Si l'intention principale est `définir minuteur`, alors les entités peuvent être lues pour obtenir le temps nécessaire au minuteur :

    ```python
    if prediction_response.prediction.top_intent == 'set timer':
        numbers = prediction_response.prediction.entities['number']
        time_units = prediction_response.prediction.entities['time unit']
        total_seconds = 0
    ```

    Les entités `nombre` seront un tableau de nombres. Par exemple, si vous dites *"Définir un minuteur de quatre minutes et 17 secondes."*, alors le tableau `nombre` contiendra 2 entiers - 4 et 17.

    Les entités `unité de temps` seront un tableau de tableaux de chaînes, avec chaque unité de temps comme un tableau de chaînes à l'intérieur du tableau. Par exemple, si vous dites *"Définir un minuteur de quatre minutes et 17 secondes."*, alors le tableau `unité de temps` contiendra 2 tableaux avec une seule valeur chacun - `['minute']` et `['seconde']`.

    La version JSON de ces entités pour *"Définir un minuteur de quatre minutes et 17 secondes."* est :

    ```json
    {
        "number": [4, 17],
        "time unit": [
            ["minute"],
            ["second"]
        ]
    }
    ```

    Ce code définit également un compteur pour le temps total du minuteur en secondes. Cela sera rempli par les valeurs des entités.

1. Les entités ne sont pas liées, mais nous pouvons faire certaines hypothèses à leur sujet. Elles seront dans l'ordre parlé, donc la position dans le tableau peut être utilisée pour déterminer quel nombre correspond à quelle unité de temps. Par exemple :

    * *"Définir un minuteur de 30 secondes"* - cela aura un seul nombre, `30`, et une seule unité de temps, `seconde`, donc le nombre unique correspondra à l'unité de temps unique.
    * *"Définir un minuteur de 2 minutes et 30 secondes"* - cela aura deux nombres, `2` et `30`, et deux unités de temps, `minute` et `seconde`, donc le premier nombre sera pour la première unité de temps (2 minutes), et le deuxième nombre pour la deuxième unité de temps (30 secondes).

    Le code suivant obtient le nombre d'éléments dans les entités `nombre`, et utilise cela pour extraire le premier élément de chaque tableau, puis le deuxième, et ainsi de suite. Ajoutez cela à l'intérieur du bloc `if`.

    ```python
    for i in range(0, len(numbers)):
        number = numbers[i]
        time_unit = time_units[i][0]
    ```

    Pour *"Définir un minuteur de quatre minutes et 17 secondes."*, cela bouclera deux fois, donnant les valeurs suivantes :

    | compteur de boucle | `nombre` | `unité de temps` |
    | ------------------: | -------: | ---------------- |
    | 0                   | 4        | minute           |
    | 1                   | 17       | seconde          |

1. À l'intérieur de cette boucle, utilisez le nombre et l'unité de temps pour calculer le temps total du minuteur, en ajoutant 60 secondes pour chaque minute, et le nombre de secondes pour les secondes.

    ```python
    if time_unit == 'minute':
        total_seconds += number * 60
    else:
        total_seconds += number
    ```

1. En dehors de cette boucle à travers les entités, enregistrez le temps total du minuteur :

    ```python
    logging.info(f'Timer required for {total_seconds} seconds')
    ```

1. Le nombre de secondes doit être retourné par la fonction comme une réponse HTTP. À la fin du bloc `if`, ajoutez ce qui suit :

    ```python
    payload = {
        'seconds': total_seconds
    }
    return func.HttpResponse(json.dumps(payload), status_code=200)
    ```

    Ce code crée une charge utile contenant le nombre total de secondes pour le minuteur, la convertit en une chaîne JSON et la retourne comme un résultat HTTP avec un code de statut 200, ce qui signifie que l'appel a réussi.

1. Enfin, en dehors du bloc `if`, gérez le cas où l'intention n'a pas été reconnue en retournant un code d'erreur :

    ```python
    return func.HttpResponse(status_code=404)
    ```

    404 est le code de statut pour *non trouvé*.

1. Exécutez l'application de fonctions et testez-la en utilisant curl.

    ```sh
    curl --request POST 'http://localhost:7071/api/text-to-timer' \
         --header 'Content-Type: application/json' \
         --include \
         --data '{"text":"<text>"}'
    ```

    Remplacez `<text>` par le texte de votre requête, par exemple `définir un minuteur de 2 minutes et 27 secondes`.

    Vous verrez la sortie suivante de l'application de fonctions :

    ```output
    Functions:

            text-to-timer: [GET,POST] http://localhost:7071/api/text-to-timer
    
    For detailed output, run func with --verbose flag.
    [2021-06-26T19:45:14.502Z] Worker process started and initialized.
    [2021-06-26T19:45:19.338Z] Host lock lease acquired by instance ID '000000000000000000000000951CAE4E'.
    [2021-06-26T19:45:52.059Z] Executing 'Functions.text-to-timer' (Reason='This function was programmatically called via the host APIs.', Id=f68bfb90-30e4-47a5-99da-126b66218e81)
    [2021-06-26T19:45:53.577Z] Timer required for 147 seconds
    [2021-06-26T19:45:53.746Z] Executed 'Functions.text-to-timer' (Succeeded, Id=f68bfb90-30e4-47a5-99da-126b66218e81, Duration=1750ms)
    ```

    L'appel à curl retournera ce qui suit :

    ```output
    HTTP/1.1 200 OK
    Date: Tue, 29 Jun 2021 01:14:11 GMT
    Content-Type: text/plain; charset=utf-8
    Server: Kestrel
    Transfer-Encoding: chunked
    
    {"seconds": 147}
    ```

    Le nombre de secondes pour le minuteur est dans la valeur `"seconds"`.

> 💁 Vous pouvez trouver ce code dans le dossier [code/functions](../../../../../6-consumer/lessons/2-language-understanding/code/functions).

### Tâche - rendre votre fonction accessible à votre appareil IoT

1. Pour que votre appareil IoT appelle votre point de terminaison REST, il devra connaître l'URL. Lorsque vous y avez accédé plus tôt, vous avez utilisé `localhost`, qui est un raccourci pour accéder aux points de terminaison REST sur votre machine locale. Pour permettre à votre appareil IoT d'y accéder, vous devez soit publier dans le cloud, soit obtenir votre adresse IP pour y accéder localement.

    > ⚠️ Si vous utilisez un Wio Terminal, il est plus facile d'exécuter l'application de fonctions localement, car il y aura une dépendance à des bibliothèques qui signifie que vous ne pouvez pas déployer l'application de fonctions de la même manière que vous l'avez fait auparavant. Exécutez l'application de fonctions localement et accédez-y via l'adresse IP de votre ordinateur. Si vous souhaitez la déployer dans le cloud, des informations seront fournies dans une leçon ultérieure sur la manière de le faire.

    * Publiez l'application de fonctions - suivez les instructions des leçons précédentes pour publier votre application de fonctions dans le cloud. Une fois publiée, l'URL sera `https://<APP_NAME>.azurewebsites.net/api/text-to-timer`, où `<APP_NAME>` sera le nom de votre application de fonctions. Assurez-vous également de publier vos paramètres locaux.

      Lorsqu'on travaille avec des déclencheurs HTTP, ils sont sécurisés par défaut avec une clé d'application de fonctions. Pour obtenir cette clé, exécutez la commande suivante :

      ```sh
      az functionapp keys list --resource-group smart-timer \
                               --name <APP_NAME>                               
      ```

      Copiez la valeur de l'entrée `default` de la section `functionKeys`.

      ```output
      {
        "functionKeys": {
          "default": "sQO1LQaeK9N1qYD6SXeb/TctCmwQEkToLJU6Dw8TthNeUH8VA45hlA=="
        },
        "masterKey": "RSKOAIlyvvQEQt9dfpabJT018scaLpQu9p1poHIMCxx5LYrIQZyQ/g==",
        "systemKeys": {}
      }
      ```

      Cette clé devra être ajoutée comme paramètre de requête à l'URL, donc l'URL finale sera `https://<APP_NAME>.azurewebsites.net/api/text-to-timer?code=<FUNCTION_KEY>`, où `<APP_NAME>` sera le nom de votre application de fonctions, et `<FUNCTION_KEY>` sera votre clé de fonction par défaut.

      > 💁 Vous pouvez changer le type d'autorisation du déclencheur HTTP en utilisant le paramètre `authlevel` dans le fichier `function.json`. Vous pouvez en savoir plus à ce sujet dans la [section de configuration de la documentation sur les déclencheurs HTTP des fonctions Azure sur Microsoft docs](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn&tabs=python#configuration).

    * Exécutez l'application de fonctions localement, et accédez-y en utilisant l'adresse IP - vous pouvez obtenir l'adresse IP de votre ordinateur sur votre réseau local, et l'utiliser pour construire l'URL.

      Trouvez votre adresse IP :

      * Sur Windows 10, suivez le guide [trouver votre adresse IP](https://support.microsoft.com/windows/find-your-ip-address-f21a9bbc-c582-55cd-35e0-73431160a1b9?WT.mc_id=academic-17441-jabenn).
      * Sur macOS, suivez le guide [comment trouver votre adresse IP sur un Mac](https://www.hellotech.com/guide/for/how-to-find-ip-address-on-mac).
      * Sur Linux, suivez la section sur la recherche de votre adresse IP privée dans le guide [comment trouver votre adresse IP sous Linux](https://opensource.com/article/18/5/how-find-ip-address-linux).

      Une fois que vous avez votre adresse IP, vous pourrez accéder à la fonction à `http://`.

:7071/api/text-to-timer`, où `<IP_ADDRESS>` correspond à votre adresse IP, par exemple `http://192.168.1.10:7071/api/text-to-timer`.

      > 💁 Notez que cela utilise le port 7071, donc après l'adresse IP, vous devrez ajouter `:7071`.

      > 💁 Cela ne fonctionnera que si votre appareil IoT est sur le même réseau que votre ordinateur.

1. Testez le point de terminaison en y accédant à l'aide de curl.

---

## 🚀 Défi

Il existe de nombreuses façons de demander la même chose, comme régler un minuteur. Réfléchissez à différentes manières de le faire et utilisez-les comme exemples dans votre application LUIS. Testez-les pour voir dans quelle mesure votre modèle peut gérer plusieurs façons de demander un minuteur.

## Quiz après le cours

[Quiz après le cours](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/44)

## Révision et auto-apprentissage

* Lisez-en davantage sur LUIS et ses capacités sur la [page de documentation de Language Understanding (LUIS) sur Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/luis/?WT.mc_id=academic-17441-jabenn)
* Apprenez-en plus sur la compréhension du langage sur la [page de compréhension du langage naturel sur Wikipédia](https://wikipedia.org/wiki/Natural-language_understanding)
* Consultez plus d'informations sur les déclencheurs HTTP dans la [documentation des déclencheurs HTTP d'Azure Functions sur Microsoft docs](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn&tabs=python)

## Devoir

[Annuler le minuteur](assignment.md)

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de faire appel à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.