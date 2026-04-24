# Vérifier le stock depuis un appareil IoT

![Un aperçu illustré de cette leçon](../../../../../translated_images/fr/lesson-20.0211df9551a8abb3.webp)

> Illustration par [Nitya Narasimhan](https://github.com/nitya). Cliquez sur l'image pour une version agrandie.

## Quiz avant la leçon

[Quiz avant la leçon](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/39)

## Introduction

Dans la leçon précédente, vous avez appris les différentes utilisations de la détection d'objets dans le commerce de détail. Vous avez également appris à entraîner un détecteur d'objets pour identifier le stock. Dans cette leçon, vous apprendrez à utiliser votre détecteur d'objets depuis votre appareil IoT pour compter le stock.

Dans cette leçon, nous aborderons :

* [Comptage de stock](../../../../../5-retail/lessons/2-check-stock-device)
* [Appeler votre détecteur d'objets depuis votre appareil IoT](../../../../../5-retail/lessons/2-check-stock-device)
* [Boîtes englobantes](../../../../../5-retail/lessons/2-check-stock-device)
* [Réentraîner le modèle](../../../../../5-retail/lessons/2-check-stock-device)
* [Compter le stock](../../../../../5-retail/lessons/2-check-stock-device)

> 🗑 C'est la dernière leçon de ce projet, donc après avoir terminé cette leçon et l'exercice, n'oubliez pas de nettoyer vos services cloud. Vous aurez besoin des services pour terminer l'exercice, alors assurez-vous de le faire en premier.
>
> Consultez [le guide de nettoyage de votre projet](../../../clean-up.md) si nécessaire pour des instructions sur la façon de procéder.

## Comptage de stock

Les détecteurs d'objets peuvent être utilisés pour vérifier le stock, soit en comptant les articles, soit en s'assurant que les articles sont à leur place. Des appareils IoT équipés de caméras peuvent être déployés dans tout le magasin pour surveiller le stock, en commençant par les zones stratégiques où le réapprovisionnement est crucial, comme les endroits où sont stockés des articles de grande valeur en petites quantités.

Par exemple, si une caméra pointe vers une étagère pouvant contenir 8 boîtes de concentré de tomate, et qu'un détecteur d'objets n'en détecte que 7, cela signifie qu'une boîte manque et doit être réapprovisionnée.

![7 boîtes de concentré de tomate sur une étagère, 4 sur la rangée du haut, 3 en bas](../../../../../translated_images/fr/stock-7-cans-tomato-paste.f86059cc573d7bec.webp)

Dans l'image ci-dessus, un détecteur d'objets a détecté 7 boîtes de concentré de tomate sur une étagère pouvant en contenir 8. Non seulement l'appareil IoT peut envoyer une notification pour signaler le besoin de réapprovisionnement, mais il peut également indiquer l'emplacement de l'article manquant, une donnée importante si vous utilisez des robots pour réapprovisionner les étagères.

> 💁 Selon le magasin et la popularité de l'article, un réapprovisionnement ne serait probablement pas nécessaire si une seule boîte manque. Vous devrez concevoir un algorithme qui détermine quand réapprovisionner en fonction de vos produits, de vos clients et d'autres critères.

✅ Dans quels autres scénarios pourriez-vous combiner la détection d'objets et les robots ?

Parfois, le mauvais stock peut se retrouver sur les étagères. Cela peut être dû à une erreur humaine lors du réapprovisionnement ou à des clients changeant d'avis et remettant un article dans le premier espace disponible. Lorsque cela concerne un article non périssable comme des conserves, c'est une simple gêne. Mais si cela concerne un article périssable comme des produits surgelés ou réfrigérés, cela peut signifier que le produit ne peut plus être vendu, car il pourrait être impossible de savoir combien de temps l'article est resté hors du congélateur.

La détection d'objets peut être utilisée pour détecter des articles inattendus, alertant à nouveau un humain ou un robot pour remettre l'article à sa place dès qu'il est détecté.

![Une boîte de maïs miniature mal placée sur l'étagère de concentré de tomate](../../../../../translated_images/fr/stock-rogue-corn.be1f3ada8c457854.webp)

Dans l'image ci-dessus, une boîte de maïs miniature a été placée sur l'étagère à côté du concentré de tomate. Le détecteur d'objets a détecté cela, permettant à l'appareil IoT de notifier un humain ou un robot pour remettre la boîte à son emplacement correct.

## Appeler votre détecteur d'objets depuis votre appareil IoT

Le détecteur d'objets que vous avez entraîné dans la leçon précédente peut être appelé depuis votre appareil IoT.

### Tâche - publier une itération de votre détecteur d'objets

Les itérations sont publiées depuis le portail Custom Vision.

1. Lancez le portail Custom Vision à [CustomVision.ai](https://customvision.ai) et connectez-vous si ce n'est pas déjà fait. Ensuite, ouvrez votre projet `stock-detector`.

1. Sélectionnez l'onglet **Performance** dans les options en haut.

1. Sélectionnez la dernière itération dans la liste des *Iterations* sur le côté.

1. Cliquez sur le bouton **Publish** pour l'itération.

    ![Le bouton publier](../../../../../translated_images/fr/custom-vision-object-detector-publish-button.34ee379fc650ccb9.webp)

1. Dans la boîte de dialogue *Publish Model*, définissez la ressource *Prediction resource* sur la ressource `stock-detector-prediction` que vous avez créée dans la leçon précédente. Laissez le nom comme `Iteration2`, puis cliquez sur le bouton **Publish**.

1. Une fois publié, cliquez sur le bouton **Prediction URL**. Cela affichera les détails de l'API de prédiction, et vous en aurez besoin pour appeler le modèle depuis votre appareil IoT. La section inférieure est intitulée *If you have an image file*, et ce sont les détails que vous voulez. Copiez l'URL affichée, qui ressemblera à :

    ```output
    https://<location>.api.cognitive.microsoft.com/customvision/v3.0/Prediction/<id>/detect/iterations/Iteration2/image
    ```

    Où `<location>` sera l'emplacement que vous avez utilisé lors de la création de votre ressource Custom Vision, et `<id>` sera un long identifiant composé de lettres et de chiffres.

    Copiez également la valeur de la clé *Prediction-Key*. C'est une clé sécurisée que vous devez transmettre lorsque vous appelez le modèle. Seules les applications qui transmettent cette clé sont autorisées à utiliser le modèle, toutes les autres applications sont rejetées.

    ![La boîte de dialogue de l'API de prédiction montrant l'URL et la clé](../../../../../translated_images/fr/custom-vision-prediction-key-endpoint.30c569ffd0338864.webp)

✅ Lorsqu'une nouvelle itération est publiée, elle aura un nom différent. Comment pensez-vous que vous pourriez changer l'itération utilisée par un appareil IoT ?

### Tâche - appeler votre détecteur d'objets depuis votre appareil IoT

Suivez le guide correspondant ci-dessous pour utiliser le détecteur d'objets depuis votre appareil IoT :

* [Arduino - Wio Terminal](wio-terminal-object-detector.md)
* [Ordinateur monocarte - Raspberry Pi/Appareil virtuel](single-board-computer-object-detector.md)

## Boîtes englobantes

Lorsque vous utilisez le détecteur d'objets, vous obtenez non seulement les objets détectés avec leurs étiquettes et probabilités, mais aussi les boîtes englobantes des objets. Ces boîtes définissent où le détecteur d'objets a détecté l'objet avec la probabilité donnée.

> 💁 Une boîte englobante est une boîte qui définit la zone contenant l'objet détecté, une boîte qui délimite l'objet.

Les résultats d'une prédiction dans l'onglet **Predictions** de Custom Vision affichent les boîtes englobantes dessinées sur l'image envoyée pour la prédiction.

![4 boîtes de concentré de tomate sur une étagère avec des prédictions pour les 4 détections de 35,8 %, 33,5 %, 25,7 % et 16,6 %](../../../../../translated_images/fr/custom-vision-stock-prediction.942266ab1bcca341.webp)

Dans l'image ci-dessus, 4 boîtes de concentré de tomate ont été détectées. Dans les résultats, un carré rouge est superposé pour chaque objet détecté dans l'image, indiquant la boîte englobante pour l'image.

✅ Ouvrez les prédictions dans Custom Vision et examinez les boîtes englobantes.

Les boîtes englobantes sont définies par 4 valeurs : haut, gauche, hauteur et largeur. Ces valeurs sont sur une échelle de 0 à 1, représentant les positions en pourcentage de la taille de l'image. L'origine (la position 0,0) est le coin supérieur gauche de l'image, donc la valeur *haut* est la distance depuis le haut, et le bas de la boîte englobante est le haut plus la hauteur.

![Une boîte englobante autour d'une boîte de concentré de tomate](../../../../../translated_images/fr/bounding-box.1420a7ea0d3d15f7.webp)

L'image ci-dessus mesure 600 pixels de large et 800 pixels de haut. La boîte englobante commence à 320 pixels du haut, ce qui donne une coordonnée *haut* de 0,4 (800 x 0,4 = 320). Depuis la gauche, la boîte englobante commence à 240 pixels, ce qui donne une coordonnée *gauche* de 0,4 (600 x 0,4 = 240). La hauteur de la boîte englobante est de 240 pixels, ce qui donne une valeur de hauteur de 0,3 (800 x 0,3 = 240). La largeur de la boîte englobante est de 120 pixels, ce qui donne une valeur de largeur de 0,2 (600 x 0,2 = 120).

| Coordonnée | Valeur |
| ---------- | -----: |
| Haut       | 0,4    |
| Gauche     | 0,4    |
| Hauteur    | 0,3    |
| Largeur    | 0,2    |

Utiliser des valeurs en pourcentage de 0 à 1 signifie que, quelle que soit la taille de l'image, la boîte englobante commence à 0,4 de la largeur et de la hauteur, et mesure 0,3 de la hauteur et 0,2 de la largeur.

Vous pouvez utiliser les boîtes englobantes combinées aux probabilités pour évaluer la précision d'une détection. Par exemple, un détecteur d'objets peut détecter plusieurs objets qui se chevauchent, par exemple en détectant une boîte à l'intérieur d'une autre. Votre code pourrait examiner les boîtes englobantes, comprendre que cela est impossible, et ignorer tout objet ayant un chevauchement significatif avec d'autres objets.

![Deux boîtes englobantes se chevauchant autour d'une boîte de concentré de tomate](../../../../../translated_images/fr/overlap-object-detection.d431e03cae75072a.webp)

Dans l'exemple ci-dessus, une boîte englobante indique une boîte de concentré de tomate prédite à 78,3 %. Une seconde boîte englobante est légèrement plus petite et se trouve à l'intérieur de la première avec une probabilité de 64,3 %. Votre code peut vérifier les boîtes englobantes, constater qu'elles se chevauchent complètement, et ignorer la probabilité la plus basse, car il est impossible qu'une boîte soit à l'intérieur d'une autre.

✅ Pouvez-vous penser à une situation où il serait valide de détecter un objet à l'intérieur d'un autre ?

## Réentraîner le modèle

Comme pour le classificateur d'images, vous pouvez réentraîner votre modèle en utilisant les données capturées par votre appareil IoT. Utiliser ces données du monde réel garantira que votre modèle fonctionne bien lorsqu'il est utilisé depuis votre appareil IoT.

Contrairement au classificateur d'images, vous ne pouvez pas simplement étiqueter une image. Vous devez examiner chaque boîte englobante détectée par le modèle. Si la boîte est autour du mauvais objet, elle doit être supprimée. Si elle est mal positionnée, elle doit être ajustée.

### Tâche - réentraîner le modèle

1. Assurez-vous d'avoir capturé une gamme d'images à l'aide de votre appareil IoT.

1. Depuis l'onglet **Predictions**, sélectionnez une image. Vous verrez des boîtes rouges indiquant les boîtes englobantes des objets détectés.

1. Passez en revue chaque boîte englobante. Sélectionnez-la d'abord, et vous verrez une fenêtre contextuelle montrant l'étiquette. Utilisez les poignées sur les coins de la boîte englobante pour ajuster la taille si nécessaire. Si l'étiquette est incorrecte, supprimez-la avec le bouton **X** et ajoutez la bonne étiquette. Si la boîte englobante ne contient pas d'objet, supprimez-la avec le bouton corbeille.

1. Fermez l'éditeur une fois terminé, et l'image passera de l'onglet **Predictions** à l'onglet **Training Images**. Répétez le processus pour toutes les prédictions.

1. Utilisez le bouton **Train** pour réentraîner votre modèle. Une fois qu'il est entraîné, publiez l'itération et mettez à jour votre appareil IoT pour utiliser l'URL de la nouvelle itération.

1. Redéployez votre code et testez votre appareil IoT.

## Compter le stock

En combinant le nombre d'objets détectés et les boîtes englobantes, vous pouvez compter le stock sur une étagère.

### Tâche - compter le stock

Suivez le guide correspondant ci-dessous pour compter le stock en utilisant les résultats du détecteur d'objets depuis votre appareil IoT :

* [Arduino - Wio Terminal](wio-terminal-count-stock.md)
* [Ordinateur monocarte - Raspberry Pi/Appareil virtuel](single-board-computer-count-stock.md)

---

## 🚀 Défi

Pouvez-vous détecter un stock incorrect ? Entraînez votre modèle sur plusieurs objets, puis mettez à jour votre application pour vous alerter si le mauvais stock est détecté.

Peut-être allez-vous encore plus loin et détectez des articles côte à côte sur la même étagère, et voyez si quelque chose a été mal placé en définissant des limites sur les boîtes englobantes.

## Quiz après la leçon

[Quiz après la leçon](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/40)

## Révision & Auto-apprentissage

* Apprenez-en davantage sur la façon d'architecturer un système de détection de stock de bout en bout à partir du [guide de modèle de détection de rupture de stock en périphérie sur Microsoft Docs](https://docs.microsoft.com/hybrid/app-solutions/pattern-out-of-stock-at-edge?WT.mc_id=academic-17441-jabenn)
* Découvrez d'autres façons de construire des solutions de commerce de détail de bout en bout en combinant une gamme de services IoT et cloud en regardant cette [vidéo YouTube "Behind the scenes of a retail solution - Hands On!"](https://www.youtube.com/watch?v=m3Pc300x2Mw).

## Exercice

[Utilisez votre détecteur d'objets en périphérie](assignment.md)

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction professionnelle réalisée par un humain. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.