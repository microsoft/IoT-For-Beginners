# Anticiper la croissance de ses plantes avec l'IoT

![Un apperçu de cette leçon](../../../../sketchnotes/lesson-5.jpg)

> Illustré par [Nitya Narasimhan](https://github.com/nitya). Click the image for a larger version.

## Questionnaire de prélecture

[Questionnaire de prélecture](https://thankful-pond-0eba8f10f.1.azurestaticapps.net/quiz/9)

## Introduction

Les plantes ont besoin de certaines choses pour pousser : de l'eau, du dioxyde de carbone, des nutriments, de la lumière et de la chaleur. Dans cette leçon, vous apprendrez à calculer les taux de croissance et de maturité des plantes en mesurant la température de l'air.

Dans cette leçon, nous allons couvrir :

* [Agriculture digitale](#agriculture-digitale)
* [L'importance de la température dans l'agriculture](#l'importance-de-la-température-dans-l'agriculture)
* [La mesure de la température ambiante](#la-mesure-de-la-température-ambiante)
* [Degrés jours de croissance (DJC)](#degrés-jours-de-croissance)
* [Calcul du DJC à l'aide de données de senseurs](#calcul-du-DJC-à-l'aide-de-données-de-senseurs)

## Agriculture digitale

L'agriculture numérique transforme notre façon de cultiver, en utilisant des outils pour collecter, stocker et analyser les données issues de l'agriculture. Nous sommes actuellement dans une période décrite comme la "quatrième révolution industrielle" par le Forum économique mondial, et l'essor de l'agriculture numérique a été qualifié de "quatrième révolution agricole", ou "agriculture 4.0".

> 🎓 Le terme "agriculture numérique" englobe également l'ensemble de la "chaîne de valeur agricole", c'est-à-dire tout le parcours de la ferme à la table. Cela inclut le suivi de la qualité des produits lors de leur expédition et de leur transformation, les systèmes d'entreposage et de commerce électronique, et même les applications de location de tracteurs !

Ces changements permettent aux agriculteurs d'augmenter leurs rendements, d'utiliser moins d'engrais et de pesticides et d'arroser plus efficacement. Bien qu'ils soient principalement utilisés dans les pays riches, le prix des capteurs et autres dispositifs diminue lentement, ce qui les rend plus accessibles dans les pays en développement.

Certaines techniques rendues possibles par l'agriculture numérique sont :

* Mesure de la température - la mesure de la température permet aux agriculteurs de prévoir la croissance et la maturité des plantes.
* L'arrosage automatisé - il s'agit de mesurer l'humidité du sol et de mettre en marche les systèmes d'irrigation lorsque le sol est trop sec, plutôt que de procéder à un arrosage programmé. L'arrosage programmé peut conduire à un arrosage insuffisant des cultures pendant une période chaude et sèche, ou à un arrosage excessif en cas de pluie. En n'arrosant que lorsque le sol en a besoin, les agriculteurs peuvent optimiser leur utilisation de l'eau.
* Lutte contre les ravageurs - les agriculteurs peuvent utiliser des caméras sur des robots ou des drones automatisés pour vérifier la présence de ravageurs, puis appliquer des pesticides uniquement là où c'est nécessaire, ce qui réduit la quantité de pesticides utilisés et le ruissellement des pesticides dans les réserves d'eau locales.

✅ Faites des recherches. Quelles autres techniques sont utilisées pour améliorer les rendements agricoles ?

> 🎓 Le terme "agriculture de précision" est utilisé pour définir l'observation, la mesure et l'intervention sur les cultures par champ, ou même sur certaines parties d'un champ. Il s'agit notamment de mesurer les niveaux d'eau, de nutriments et de parasites et de réagir avec précision, par exemple en n'arrosant qu'une petite partie du champ.

## L'importance de la température dans l'agriculture

Lorsqu'ils étudient les plantes, la plupart des élèves apprennent qu'elles ont besoin d'eau, de lumière, de dioxyde de carbone (CO<sub>2</sub>) et de nutriments. Les plantes ont également besoin de chaleur pour se développer - c'est pourquoi les plantes fleurissent au printemps lorsque la température augmente, pourquoi les perce-neige ou les jonquilles peuvent germer tôt en raison d'une courte période de chaleur, et pourquoi les serres sont si efficaces pour faire pousser les plantes.

> 🎓 Les serres et les serres chaudes font un travail similaire, mais avec une différence importante. Les serres chaudes sont chauffées artificiellement et permettent aux agriculteurs de contrôler les températures avec plus de précision. Les serres dépendent du soleil pour la chaleur et le seul moyen de contrôle est généralement l'ouverture de fenêtres ou d'autres ouvertures pour laisser sortir la chaleur.

Les plantes ont une température de base ou minimale, une température optimale et une température maximale, toutes basées sur les températures moyennes quotidiennes.

* Température de base - il s'agit de la température moyenne quotidienne minimale nécessaire à la croissance d'une plante.
* Température optimale - il s'agit de la meilleure température moyenne quotidienne pour obtenir la meilleure croissance.
* Température maximale - Il s'agit de la température maximale qu'une plante peut supporter. Au-dessus de cette température, la plante interrompt sa croissance afin de conserver l'eau et de rester en vie.

> 💁 Il s'agit de températures moyennes, calculées sur la base des températures quotidiennes et nocturnes. Les plantes ont également besoin de températures différentes le jour et la nuit pour leur permettre de réaliser une photosynthèse plus efficace et d'économiser de l'énergie la nuit.

Chaque espèce de plante a des valeurs différentes pour sa base, son optimum et son maximum. C'est pourquoi certaines plantes prospèrent dans les pays chauds, et d'autres dans les pays plus froids.

✅ Faites des recherches. Pour toutes les plantes que vous avez dans votre jardin, à l'école ou dans un parc local, voyez si vous pouvez trouver la température de base.

![Un graphique montrant que le taux de croissance augmente lorsque la température augmente, puis diminue lorsque la température devient trop élevée.](../../../../images/plant-growth-temp-graph.png)

Le graphique ci-dessus montre un exemple de taux de croissance en fonction de la température. Jusqu'à la température de base, il n'y a pas de croissance. Le taux de croissance augmente jusqu'à la température optimale, puis chute après avoir atteint ce pic. À la température maximale, la croissance s'arrête.

La forme de ce graphique varie d'une espèce végétale à l'autre. Certaines ont des chutes plus marquées au-dessus de l'optimum, d'autres ont des augmentations plus lentes de la base à l'optimum.

> 💁 Pour qu'un agriculteur obtienne la meilleure croissance, il devra connaître les trois valeurs de température et comprendre la forme des graphiques pour les plantes qu'il cultive.

Si un agriculteur a le contrôle de la température, par exemple dans une serre commerciale, il peut optimiser la croissance de ses plantes. Dans une serre commerciale où l'on cultive des tomates, par exemple, la température sera réglée à environ 25°C le jour et 20°C la nuit pour obtenir la croissance la plus rapide.

> 🍅 En combinant ces températures avec des lumières artificielles, des engrais et des niveaux de CO<sub>2</sub> contrôlés, les producteurs commerciaux peuvent cultiver et récolter toute l'année.

## La-mesure-de-la-température-ambiante

Les capteurs de température peuvent être utilisés avec les appareils IoT pour mesurer la température ambiante.

### Tâche - Mesure de la température

Suivez le guide correspondant pour surveiller les températures à l'aide de votre dispositif IoT :

* [Arduino - Wio Terminal](wio-terminal-temp.fr.md)
* [Single-board computer - Raspberry Pi](pi-temp.fr.md)
* [Single-board computer - Virtual device](virtual-device-temp.fr.md)

## Degrés-jours de croissance

Les degrés-jours de croissance (également appelés unités de degrés de croissance) sont un moyen de mesurer la croissance des plantes en fonction de la température. En supposant qu'une plante dispose de suffisamment d'eau, de nutriments et de CO<sub>2</sub>, la température détermine le taux de croissance.

Les degrés-jours de croissance, ou DJC, sont calculés par jour comme la température moyenne en Celsius pour un jour au-dessus de la température de base des plantes. Chaque plante a besoin d'un certain nombre de DJC pour croître, fleurir ou produire et faire mûrir une récolte. Plus le nombre de DJC par jour est élevé, plus la croissance de la plante est rapide.

> 🇺🇸 Pour les Américains, les degrés-jours de croissance peuvent également être calculés en Fahrenheit. 5 DJC<sup>C</sup> (degrés-jours de croissance en Celsius) sont l'équivalent de 9 DJC<sup>F</sup> (degrés-jours de croissance en Fahrenheit).

La formule complète du DJC est un peu compliquée, mais il existe une équation simplifiée qui est souvent utilisée comme une bonne approximation :

![DJC = T max + T min divisé par 2, total - T base](../../../../images/gdd-calculation.png)

* **DJC** - c'est le nombre de degrés-jours de croissance
* **T<sub>max</sub>** - il s'agit de la température maximale quotidienne en degrés Celsius
* **T<sub>min</sub>** - il s'agit de la température minimale quotidienne en degrés Celsius
* **T<sub>base</sub>** - c'est la température de base des plantes en degrés Celsius

> 💁 Il existe certaines variations impliquant T<sub>max</sub> au delà de 30°C ou T<sub>min</sub> en deça T<sub>base</sub>, mais nous ignorerons ces cas dans le contexte de ce cours.

### Exemple - Maïs 🌽

Selon la variété, le maïs a besoin de 800 à 2 700 DJC pour arriver à maturité, avec une température de base de 10°C.

Le premier jour au-dessus de la température de base, les températures suivantes ont été mesurées :

| Mesures     | Temp °C |
| :---------- | :-----: |
| Maximum     | 16      |
| Minimum     | 12      |

En ajoutant ces chiffres à notre calcul :

* T<sub>max</sub> = 16
* T<sub>min</sub> = 12
* T<sub>base</sub> = 10

Ce qui donne un résultat de:

![DJC = 16 + 12 divisé par 2, total moins 10, résultant à 4](../../../../images/gdd-calculation-corn.png)

Le maïs a reçu 4 DJC ce jour-là. Dans l'hypothèse d'une variété de maïs qui a besoin de 800 jours DJC pour arriver à maturité, il lui faudra encore 796 DJC pour atteindre la maturité.

✅ Faites des recherches. Pour toutes les plantes que vous avez dans votre jardin, à l'école ou dans un parc local, voyez si vous pouvez trouver le nombre de DJC requis pour atteindre la maturité ou produire des récoltes.

## Calcul du DJC à l'aide de données de senseurs

Les plantes ne poussent pas à dates fixes - par exemple, vous ne pouvez pas planter une graine et savoir que la plante portera des fruits exactement 100 jours plus tard. Au lieu de cela, en tant qu'agriculteur, vous pouvez avoir une idée approximative du temps que prend une plante pour pousser, puis vous vérifiez quotidiennement quand les cultures sont prêtes.

Cela a un impact considérable sur la main-d'œuvre d'une grande exploitation, et l'agriculteur risque de manquer des cultures qui sont prêtes plus tôt que prévu. En mesurant les températures, l'agriculteur peut calculer le DJC qu'une plante a reçu, ce qui lui permet de ne vérifier que les cultures proches de la maturité attendue.

En recueillant des données de température à l'aide d'un dispositif IoT, un agriculteur peut être automatiquement informé lorsque les plantes sont proches de la maturité. Une architecture typique pour cela consiste à faire en sorte que les dispositifs IoT mesurent la température, puis publient ces données de télémétrie sur Internet en utilisant quelque chose comme MQTT. Le code du serveur écoute ensuite ces données et les enregistre quelque part, par exemple dans une base de données. Cela signifie que les données peuvent être analysées ultérieurement, par exemple une tâche nocturne pour calculer le DJC de la journée, totaliser le DJC de chaque culture jusqu'à présent et alerter si une plante est proche de la maturité.

![Les données télémétriques sont envoyées à un serveur, puis enregistrées dans une base de données.](../../../../images/save-telemetry-database.png)

Le code serveur peut également augmenter les données en ajoutant des informations supplémentaires. Par exemple, le dispositif IoT peut publier un identifiant pour indiquer de quel dispositif il s'agit, et le code du serveur peut l'utiliser pour rechercher l'emplacement du dispositif et les cultures qu'il surveille. Il peut également ajouter des données de base comme l'heure actuelle, car certains dispositifs IoT ne disposent pas du matériel nécessaire pour suivre l'heure exacte, ou nécessitent un code supplémentaire pour lire l'heure actuelle sur Internet.

✅ Pourquoi pensez-vous que des champs différents peuvent avoir des températures différentes ?

### Tâche - publier des informations sur la température

Suivez le guide correspondant pour publier les données de température sur MQTT à l'aide de votre dispositif IoT afin de pouvoir les analyser ultérieurement :

* [Arduino - Terminal Wio](wio-terminal-temp-publish.fr.md)
* [Ordinateur monocarte - Raspberry Pi/Dispositif IoT virtuel](single-board-computer-temp-publish.fr.md)

### Tâche - capturer et stocker les informations sur la température

Une fois que le dispositif IoT publie la télémétrie, le code du serveur peut être écrit pour s'abonner à ces données et les stocker. Plutôt que de les enregistrer dans une base de données, le code serveur les enregistrera dans un fichier CSV (Comma Separated Values). Les fichiers CSV stockent les données sous forme de lignes de valeurs en texte, chaque valeur étant séparée par une virgule, et chaque enregistrement sur une nouvelle ligne. Ils constituent un moyen pratique, lisible par l'homme et bien supporté d'enregistrer des données dans un fichier.

Le fichier CSV aura deux colonnes - *date* et *température*. La colonne *date* est définie comme la date et l'heure actuelles de réception du message par le serveur, la colonne *température* provient du message de télémétrie.

1. Répétez les étapes de la leçon 4 pour créer un code serveur permettant de s'abonner à la télémétrie. Vous n'avez pas besoin d'ajouter du code pour publier des commandes.

    Les étapes à suivre sont les suivantes :

    * Configurer et activer un environnement virtuel Python

    * Installer la librairie pip paho-mqtt

    * Écrire le code pour écouter les messages MQTT publiés sur le sujet de télémétrie

      > ⚠️ Vous pouvez vous référer [aux instructions de la leçon 4 pour créer une application Python pour recevoir la télémétrie si nécessaire](../../../../1-getting-started/lessons/4-connect-internet/README.md#receive-telemetry-from-the-mqtt-broker).

     Nommez le dossier pour ce projet `temperature-sensor-server`.

1. Assurez vous que `client_name` corresponde à ce projet:

    ```cpp
    client_name = id + 'temperature_sensor_server'
    ```

1. Ajoutez les importations suivantes en haut du fichier, en dessous des importations existantes :

    ```python
    from os import path
    import csv
    from datetime import datetime
    ```

    Ceci importe une bibliothèque pour lire les fichiers, une bibliothèque pour interagir avec les fichiers CSV, et une bibliothèque pour aider avec les dates et les heures.

1. Ajoutez le code suivant avant la fonction `handle_telemetry`:

    ```python
    temperature_file_name = 'temperature.csv'
    fieldnames = ['date', 'temperature']
    
    if not path.exists(temperature_file_name):
        with open(temperature_file_name, mode='w') as csv_file:
            writer = csv.DictWriter(csv_file, fieldnames=fieldnames)
            writer.writeheader()
    ```

    Ce code déclare quelques constantes pour le nom du fichier à écrire, et le nom des en-têtes de colonne pour le fichier CSV. La première ligne d'un fichier CSV contient traditionnellement des en-têtes de colonne séparés par des virgules.

    Le code vérifie ensuite si le fichier CSV existe déjà. S'il n'existe pas, il est créé avec les en-têtes de colonne sur la première ligne.

1. Ajoutez le code suivant à la fin de la fonction `handle_telemetry`:

    ```python
    with open(temperature_file_name, mode='a') as temperature_file:        
        temperature_writer = csv.DictWriter(temperature_file, fieldnames=fieldnames)
        temperature_writer.writerow({'date' : datetime.now().astimezone().replace(microsecond=0).isoformat(), 'temperature' : payload['temperature']})
    ```

    Ce code ouvre le fichier CSV, puis ajoute une nouvelle ligne à la fin. La ligne comporte les données et l'heure actuelles formatées dans un format lisible par l'homme, suivies de la température reçue du dispositif IoT. Les données sont stockées au [format ISO 8601] (https://wikipedia.org/wiki/ISO_8601) avec le fuseau horaire, mais sans les microsecondes.

1. Exécutez ce code de la même manière que précédemment, en vous assurant que votre dispositif IoT envoie des données. Un fichier CSV appelé `temperature.csv` sera créé dans le même dossier. Si vous le visualisez, vous verrez les dates/heures et les mesures de température :

    ```output
    date,temperature
    2021-04-19T17:21:36-07:00,25
    2021-04-19T17:31:36-07:00,24
    2021-04-19T17:41:36-07:00,25
    ```

1. Exécutez ce code pendant un certain temps pour capturer les données. Idéalement, vous devriez l'exécuter pendant une journée entière afin de recueillir suffisamment de données pour les calculs de DJC.

    > 💁 Si vous utilisez le "Virtual IoT Device", cochez la case aléatoire et définissez une plage pour éviter d'obtenir la même température à chaque fois que la valeur de température est renvoyée.
    ![Cochez la case aléatoire et définissez une plage](../../../../images/select-the-random-checkbox-and-set-a-range.png)  

    > 💁 Si vous souhaitez exécuter ce programme pendant toute une journée, vous devez vous assurer que l'ordinateur sur lequel votre code serveur est exécuté ne se mettra pas en veille, soit en modifiant vos paramètres d'alimentation, soit en exécutant un programme tel que [ceci maintient le système actif](https://github.com/jaqsparow/keep-system-active).
    
> 💁 Vous pouvez trouver ce code dans le dossier [code-server/temperature-sensor-server](../code-server/temperature-sensor-server).

### Tâche - calculer le DJC en utilisant les données stockées

Une fois que le serveur a saisi les données de température, le DJC d'une usine peut être calculé.

Les étapes à suivre pour effectuer cette opération manuellement sont les suivantes :

1. Trouvez la température de base de la plante. Par exemple, pour les fraises, la température de base est de 10°C.

1. A partir du fichier `temperature.csv`, trouvez les températures les plus hautes et les plus basses de la journée.

1. Utilisez le calcul du DJC donné précédemment pour calculer le DJC

Par exemple, si la température la plus élevée de la journée est de 25°C, et la plus basse de 12°C :

![DJC = 25 + 12 divisé par 2, enlever 10 du résultat, donnant 8.5](../../../../images/gdd-calculation-strawberries.png)

* 25 + 12 = 37
* 37 / 2 = 18.5
* 18.5 - 10 = 8.5

Les fraises ont donc reçu **8,5** DJC. Les fraises ont besoin d'environ 250 DJC pour porter des fruits, donc il y a encore du chemin à faire.

---

## 🚀 Défi

Les plantes ont besoin de plus que de la chaleur pour pousser. Quelles autres choses sont nécessaires ?

Pour ceux-ci, cherchez s'il existe des capteurs qui peuvent les mesurer. Et des actionneurs pour contrôler ces niveaux ? Comment assembleriez-vous un ou plusieurs dispositifs IoT pour optimiser la croissance des plantes ?

## Questionnaire Post-lecture

[Questionnaire Post-lecture](https://thankful-pond-0eba8f10f.1.azurestaticapps.net/quiz/10)

## Révision et apprentissage autodidacte

* Pour en savoir plus sur l'agriculture numérique, consultez la page [Digital Agriculture Wikipedia](https://wikipedia.org/wiki/Digital_agriculture). Pour en savoir plus sur l'agriculture de précision, consultez la page [Precision Agriculture Wikipedia](https://wikipedia.org/wiki/Precision_agriculture).
* Le calcul complet des degrés-jours de croissance est plus compliqué que le calcul simplifié présenté ici. Pour en savoir plus sur l'équation plus compliquée et sur la manière de traiter les températures inférieures à la ligne de base, consultez la page [Degrés-jours de croissance sur Wikipédia](https://wikipedia.org/wiki/Growing_degree-day).
* La nourriture pourrait se faire rare à l'avenir, même si nous utilisons toujours les mêmes méthodes agricoles. Pour en savoir plus sur les techniques agricoles de haute technologie, regardez cette vidéo [Hi-Tech Farms of Future sur YouTube](https://www.youtube.com/watch?v=KIEOuKD9KX8).

## Devoir

[Visualiser les données DJC à l'aide d'un Jupyter Notebook](assignment.fr.md)
