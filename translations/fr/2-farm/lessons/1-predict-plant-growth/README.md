# Prédire la croissance des plantes avec l'IoT

![Un aperçu illustré de cette leçon](../../../../../translated_images/fr/lesson-5.42b234299279d263.webp)

> Illustration par [Nitya Narasimhan](https://github.com/nitya). Cliquez sur l'image pour une version agrandie.

## Quiz avant la leçon

[Quiz avant la leçon](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/9)

## Introduction

Les plantes ont besoin de certains éléments pour pousser : de l'eau, du dioxyde de carbone, des nutriments, de la lumière et de la chaleur. Dans cette leçon, vous apprendrez à calculer les taux de croissance et de maturité des plantes en mesurant la température de l'air.

Dans cette leçon, nous aborderons :

* [L'agriculture numérique](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Pourquoi la température est-elle importante en agriculture ?](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Mesurer la température ambiante](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Les degrés-jours de croissance (GDD)](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Calculer les GDD à l'aide des données d'un capteur de température](../../../../../2-farm/lessons/1-predict-plant-growth)

## L'agriculture numérique

L'agriculture numérique transforme notre manière de cultiver, en utilisant des outils pour collecter, stocker et analyser les données agricoles. Nous vivons actuellement une période décrite comme la "Quatrième Révolution Industrielle" par le Forum Économique Mondial, et l'essor de l'agriculture numérique est qualifié de "Quatrième Révolution Agricole" ou "Agriculture 4.0".

> 🎓 Le terme "agriculture numérique" inclut également toute la "chaîne de valeur agricole", c'est-à-dire tout le parcours du champ à l'assiette. Cela inclut le suivi de la qualité des produits pendant leur transport et leur transformation, les systèmes d'entrepôt et de commerce électronique, voire des applications de location de tracteurs !

Ces changements permettent aux agriculteurs d'augmenter leurs rendements, d'utiliser moins d'engrais et de pesticides, et d'optimiser l'utilisation de l'eau. Bien que principalement utilisée dans les pays riches, les capteurs et autres dispositifs deviennent progressivement plus abordables, les rendant accessibles dans les pays en développement.

Quelques techniques rendues possibles par l'agriculture numérique :

* Mesure de la température - mesurer la température permet aux agriculteurs de prédire la croissance et la maturité des plantes.
* Arrosage automatisé - mesurer l'humidité du sol et activer les systèmes d'irrigation lorsque le sol est trop sec, plutôt que d'arroser à des horaires fixes. L'arrosage programmé peut entraîner un sous-arrosage pendant une période chaude et sèche, ou un sur-arrosage pendant la pluie. En arrosant uniquement lorsque le sol en a besoin, les agriculteurs peuvent optimiser leur consommation d'eau.
* Lutte contre les nuisibles - les agriculteurs peuvent utiliser des caméras sur des robots automatisés ou des drones pour détecter les nuisibles, puis appliquer des pesticides uniquement là où c'est nécessaire, réduisant ainsi la quantité de pesticides utilisée et limitant leur dispersion dans les ressources en eau locales.

✅ Faites des recherches. Quelles autres techniques sont utilisées pour améliorer les rendements agricoles ?

> 🎓 Le terme "agriculture de précision" désigne l'observation, la mesure et la réponse aux besoins des cultures à l'échelle d'un champ, voire d'une partie de champ. Cela inclut la mesure des niveaux d'eau, de nutriments et de nuisibles, et une réponse précise, comme l'arrosage d'une petite partie d'un champ.

## Pourquoi la température est-elle importante en agriculture ?

Lorsqu'on apprend sur les plantes, on enseigne souvent qu'elles ont besoin d'eau, de lumière, de dioxyde de carbone et de nutriments. Mais les plantes ont aussi besoin de chaleur pour pousser - c'est pourquoi elles fleurissent au printemps lorsque la température augmente, pourquoi les perce-neige ou jonquilles peuvent germer tôt après une courte période de chaleur, et pourquoi les serres et les tunnels chauffants sont si efficaces pour favoriser leur croissance.

> 🎓 Les tunnels chauffants et les serres ont une fonction similaire, mais avec une différence importante. Les tunnels chauffants sont chauffés artificiellement, ce qui permet aux agriculteurs de contrôler plus précisément les températures, tandis que les serres dépendent du soleil pour la chaleur et ne disposent généralement que de fenêtres ou d'autres ouvertures pour évacuer la chaleur.

Les plantes ont une température de base ou minimale, une température optimale et une température maximale, toutes basées sur les températures moyennes quotidiennes.

* Température de base - c'est la température moyenne quotidienne minimale nécessaire pour qu'une plante pousse.
* Température optimale - c'est la température moyenne quotidienne idéale pour obtenir la meilleure croissance.
* Température maximale - c'est la température maximale qu'une plante peut supporter. Au-delà, la plante arrête sa croissance pour tenter de conserver l'eau et de survivre.

> 💁 Ce sont des températures moyennes, calculées à partir des températures diurnes et nocturnes. Les plantes ont également besoin de températures différentes le jour et la nuit pour mieux photosynthétiser et économiser de l'énergie la nuit.

Chaque espèce de plante a des valeurs différentes pour sa température de base, optimale et maximale. C'est pourquoi certaines plantes prospèrent dans des pays chauds, et d'autres dans des pays froids.

✅ Faites des recherches. Pour les plantes que vous avez dans votre jardin, école ou parc local, pouvez-vous trouver leur température de base ?

![Un graphique montrant le taux de croissance augmentant avec la température, puis diminuant lorsque la température devient trop élevée](../../../../../translated_images/fr/plant-growth-temp-graph.c6d69c9478e6ca83.webp)

Le graphique ci-dessus montre un exemple de courbe de croissance en fonction de la température. Jusqu'à la température de base, il n'y a pas de croissance. Le taux de croissance augmente jusqu'à la température optimale, puis diminue après avoir atteint ce pic. À la température maximale, la croissance s'arrête.

La forme de ce graphique varie selon les espèces de plantes. Certaines ont une chute plus abrupte au-delà de la température optimale, d'autres ont une augmentation plus lente entre la température de base et la température optimale.

> 💁 Pour obtenir la meilleure croissance, un agriculteur doit connaître les trois valeurs de température et comprendre la forme des graphiques pour les plantes qu'il cultive.

Si un agriculteur peut contrôler la température, par exemple dans un tunnel chauffant commercial, il peut l'optimiser pour ses plantes. Un tunnel chauffant commercial cultivant des tomates, par exemple, maintiendra une température d'environ 25°C pendant la journée et 20°C la nuit pour une croissance rapide.

> 🍅 En combinant ces températures avec des lumières artificielles, des engrais et un contrôle des niveaux de CO
Ce code ouvre le fichier CSV, puis ajoute une nouvelle ligne à la fin. La ligne contient la date et l'heure actuelles formatées de manière lisible, suivies de la température reçue de l'appareil IoT. Les données sont stockées au [format ISO 8601](https://wikipedia.org/wiki/ISO_8601) avec le fuseau horaire, mais sans les microsecondes.

1. Exécutez ce code de la même manière qu'auparavant, en vous assurant que votre appareil IoT envoie des données. Un fichier CSV appelé `temperature.csv` sera créé dans le même dossier. Si vous l'ouvrez, vous verrez des dates/heures et des mesures de température :

    ```output
    date,temperature
    2021-04-19T17:21:36-07:00,25
    2021-04-19T17:31:36-07:00,24
    2021-04-19T17:41:36-07:00,25
    ```

1. Exécutez ce code pendant un certain temps pour capturer des données. Idéalement, vous devriez le faire fonctionner pendant une journée entière pour collecter suffisamment de données pour les calculs de GDD.

    
> 💁 Si vous utilisez un appareil IoT virtuel, cochez la case aléatoire et définissez une plage pour éviter d'obtenir la même température à chaque fois que la valeur de température est renvoyée.
    ![Cochez la case aléatoire et définissez une plage](../../../../../translated_images/fr/select-the-random-checkbox-and-set-a-range.32cf4bc7c12e797f.webp) 

    > 💁 Si vous souhaitez exécuter cela pendant une journée entière, vous devez vous assurer que l'ordinateur sur lequel votre code serveur s'exécute ne se mettra pas en veille, soit en modifiant vos paramètres d'alimentation, soit en exécutant quelque chose comme [ce script Python pour garder le système actif](https://github.com/jaqsparow/keep-system-active).
    
> 💁 Vous pouvez trouver ce code dans le dossier [code-server/temperature-sensor-server](../../../../../2-farm/lessons/1-predict-plant-growth/code-server/temperature-sensor-server).

### Tâche - calculer le GDD à l'aide des données stockées

Une fois que le serveur a capturé les données de température, le GDD pour une plante peut être calculé.

Les étapes pour le faire manuellement sont :

1. Trouvez la température de base pour la plante. Par exemple, pour les fraises, la température de base est de 10°C.

1. À partir du fichier `temperature.csv`, trouvez les températures les plus élevées et les plus basses de la journée.

1. Utilisez le calcul de GDD donné précédemment pour calculer le GDD.

Par exemple, si la température la plus élevée de la journée est de 25°C, et la plus basse est de 12°C :

![GDD = 25 + 12 divisé par 2, puis soustrayez 10 du résultat pour obtenir 8,5](../../../../../translated_images/fr/gdd-calculation-strawberries.59f57db94b22adb8.webp)

* 25 + 12 = 37
* 37 / 2 = 18,5
* 18,5 - 10 = 8,5

Ainsi, les fraises ont reçu **8,5** GDD. Les fraises ont besoin d'environ 250 GDD pour produire des fruits, donc il reste encore un peu de temps.

---

## 🚀 Défi

Les plantes ont besoin de plus que de la chaleur pour pousser. De quoi d'autre ont-elles besoin ?

Pour ces éléments, trouvez s'il existe des capteurs capables de les mesurer. Qu'en est-il des actionneurs pour contrôler ces niveaux ? Comment assembleriez-vous un ou plusieurs appareils IoT pour optimiser la croissance des plantes ?

## Quiz post-cours

[Quiz post-cours](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/10)

## Révision et auto-apprentissage

* Lisez davantage sur l'agriculture numérique sur la [page Wikipédia de l'agriculture numérique](https://wikipedia.org/wiki/Digital_agriculture). Lisez également sur l'agriculture de précision sur la [page Wikipédia de l'agriculture de précision](https://wikipedia.org/wiki/Precision_agriculture).
* Le calcul complet des degrés-jours de croissance est plus complexe que celui simplifié présenté ici. Lisez-en davantage sur l'équation plus complexe et sur la manière de gérer les températures inférieures au seuil sur la [page Wikipédia des degrés-jours de croissance](https://wikipedia.org/wiki/Growing_degree-day).
* La nourriture pourrait devenir rare à l'avenir si nous continuons à utiliser les mêmes méthodes agricoles. Apprenez-en davantage sur les techniques agricoles de haute technologie dans cette [vidéo sur les fermes high-tech du futur sur YouTube](https://www.youtube.com/watch?v=KIEOuKD9KX8).

## Devoir

[Visualisez les données GDD à l'aide d'un Jupyter Notebook](assignment.md)

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.