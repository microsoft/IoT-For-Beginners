# Vérifier la qualité des fruits avec un appareil IoT

![Un aperçu illustré de cette leçon](../../../../../translated_images/fr/lesson-16.215daf18b00631fb.webp)

> Illustration par [Nitya Narasimhan](https://github.com/nitya). Cliquez sur l'image pour une version agrandie.

## Quiz avant la leçon

[Quiz avant la leçon](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/31)

## Introduction

Dans la dernière leçon, vous avez appris à propos des classificateurs d'images et comment les entraîner pour détecter les fruits de bonne ou mauvaise qualité. Pour utiliser ce classificateur d'images dans une application IoT, vous devez être capable de capturer une image à l'aide d'une caméra et d'envoyer cette image dans le cloud pour qu'elle soit classifiée.

Dans cette leçon, vous apprendrez à utiliser des capteurs de caméra avec un appareil IoT pour capturer une image. Vous apprendrez également à appeler le classificateur d'images depuis votre appareil IoT.

Dans cette leçon, nous aborderons :

* [Capteurs de caméra](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Capturer une image avec un appareil IoT](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Publier votre classificateur d'images](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Classer des images depuis votre appareil IoT](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Améliorer le modèle](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)

## Capteurs de caméra

Les capteurs de caméra, comme leur nom l'indique, sont des caméras que vous pouvez connecter à votre appareil IoT. Ils peuvent prendre des images fixes ou capturer des vidéos en streaming. Certains renvoient des données d'image brutes, tandis que d'autres compressent les données en fichiers image tels que JPEG ou PNG. En général, les caméras compatibles avec les appareils IoT sont beaucoup plus petites et de résolution inférieure à ce que vous pourriez utiliser habituellement, mais il existe des caméras haute résolution qui rivalisent avec les meilleurs téléphones. Vous pouvez également trouver des objectifs interchangeables, des configurations multi-caméras, des caméras thermiques infrarouges ou des caméras UV.

![La lumière d'une scène passe à travers une lentille et est focalisée sur un capteur CMOS](../../../../../translated_images/fr/cmos-sensor.75f9cd74decb1371.webp)

La plupart des capteurs de caméra utilisent des capteurs d'image où chaque pixel est une photodiode. Une lentille focalise l'image sur le capteur d'image, et des milliers ou millions de photodiodes détectent la lumière qui tombe sur chacune d'elles, enregistrant cela comme des données de pixels.

> 💁 Les lentilles inversent les images, et le capteur de la caméra retourne ensuite l'image dans le bon sens. C'est la même chose pour vos yeux : ce que vous voyez est détecté à l'envers à l'arrière de votre œil, et votre cerveau le corrige.

> 🎓 Le capteur d'image est connu sous le nom de capteur à pixels actifs (APS), et le type d'APS le plus populaire est un capteur CMOS (complementary metal-oxide semiconductor). Vous avez peut-être entendu parler du terme capteur CMOS pour désigner les capteurs de caméra.

Les capteurs de caméra sont des capteurs numériques, envoyant des données d'image sous forme numérique, généralement avec l'aide d'une bibliothèque qui gère la communication. Les caméras se connectent via des protocoles comme SPI pour leur permettre d'envoyer de grandes quantités de données - les images sont beaucoup plus volumineuses que des données simples comme celles d'un capteur de température.

✅ Quelles sont les limitations concernant la taille des images avec les appareils IoT ? Pensez aux contraintes, en particulier sur le matériel des microcontrôleurs.

## Capturer une image avec un appareil IoT

Vous pouvez utiliser votre appareil IoT pour capturer une image à classer.

### Tâche - capturer une image avec un appareil IoT

Suivez le guide correspondant pour capturer une image avec votre appareil IoT :

* [Arduino - Wio Terminal](wio-terminal-camera.md)
* [Ordinateur monocarte - Raspberry Pi](pi-camera.md)
* [Ordinateur monocarte - Appareil virtuel](virtual-device-camera.md)

## Publier votre classificateur d'images

Vous avez entraîné votre classificateur d'images dans la dernière leçon. Avant de pouvoir l'utiliser depuis votre appareil IoT, vous devez publier le modèle.

### Itérations du modèle

Lorsque votre modèle était en cours d'entraînement dans la dernière leçon, vous avez peut-être remarqué que l'onglet **Performance** affichait des itérations sur le côté. Lorsque vous avez entraîné le modèle pour la première fois, vous avez vu *Itération 1* en cours d'entraînement. Lorsque vous avez amélioré le modèle en utilisant les images de prédiction, vous avez vu *Itération 2* en cours d'entraînement.

Chaque fois que vous entraînez le modèle, vous obtenez une nouvelle itération. Cela permet de suivre les différentes versions de votre modèle entraînées sur différents ensembles de données. Lorsque vous effectuez un **Test rapide**, un menu déroulant vous permet de sélectionner l'itération, afin de comparer les résultats entre plusieurs itérations.

Lorsque vous êtes satisfait d'une itération, vous pouvez la publier pour qu'elle soit disponible pour des applications externes. Ainsi, vous pouvez avoir une version publiée utilisée par vos appareils, tout en travaillant sur une nouvelle version à travers plusieurs itérations, puis la publier une fois que vous en êtes satisfait.

### Tâche - publier une itération

Les itérations sont publiées depuis le portail Custom Vision.

1. Lancez le portail Custom Vision sur [CustomVision.ai](https://customvision.ai) et connectez-vous si ce n'est pas déjà fait. Ensuite, ouvrez votre projet `fruit-quality-detector`.

1. Sélectionnez l'onglet **Performance** dans les options en haut.

1. Sélectionnez la dernière itération dans la liste *Iterations* sur le côté.

1. Cliquez sur le bouton **Publish** pour l'itération.

    ![Le bouton publier](../../../../../translated_images/fr/custom-vision-publish-button.b7174e1977b0c33b.webp)

1. Dans la boîte de dialogue *Publish Model*, définissez la ressource *Prediction resource* sur la ressource `fruit-quality-detector-prediction` que vous avez créée dans la dernière leçon. Laissez le nom comme `Iteration2`, puis cliquez sur le bouton **Publish**.

1. Une fois publié, cliquez sur le bouton **Prediction URL**. Cela affichera les détails de l'API de prédiction, dont vous aurez besoin pour appeler le modèle depuis votre appareil IoT. La section inférieure est intitulée *If you have an image file*, et ce sont les détails que vous voulez. Copiez l'URL affichée, qui ressemblera à :

    ```output
    https://<location>.api.cognitive.microsoft.com/customvision/v3.0/Prediction/<id>/classify/iterations/Iteration2/image
    ```

    Où `<location>` sera l'emplacement que vous avez utilisé lors de la création de votre ressource Custom Vision, et `<id>` sera un long identifiant composé de lettres et de chiffres.

    Copiez également la valeur de la *Prediction-Key*. Il s'agit d'une clé sécurisée que vous devez transmettre lorsque vous appelez le modèle. Seules les applications qui transmettent cette clé sont autorisées à utiliser le modèle, toutes les autres applications sont rejetées.

    ![La boîte de dialogue de l'API de prédiction montrant l'URL et la clé](../../../../../translated_images/fr/custom-vision-prediction-key-endpoint.30c569ffd0338864.webp)

✅ Lorsqu'une nouvelle itération est publiée, elle aura un nom différent. Comment pensez-vous que vous pourriez changer l'itération utilisée par un appareil IoT ?

## Classer des images depuis votre appareil IoT

Vous pouvez maintenant utiliser ces détails de connexion pour appeler le classificateur d'images depuis votre appareil IoT.

### Tâche - classer des images depuis votre appareil IoT

Suivez le guide correspondant pour classer des images avec votre appareil IoT :

* [Arduino - Wio Terminal](wio-terminal-classify-image.md)
* [Ordinateur monocarte - Raspberry Pi/Appareil IoT virtuel](single-board-computer-classify-image.md)

## Améliorer le modèle

Vous pourriez constater que les résultats obtenus avec la caméra connectée à votre appareil IoT ne correspondent pas à vos attentes. Les prédictions ne sont pas toujours aussi précises qu'avec des images téléchargées depuis votre ordinateur. Cela s'explique par le fait que le modèle a été entraîné avec des données différentes de celles utilisées pour les prédictions.

Pour obtenir les meilleurs résultats avec un classificateur d'images, vous devez entraîner le modèle avec des images aussi similaires que possible à celles utilisées pour les prédictions. Par exemple, si vous avez utilisé l'appareil photo de votre téléphone pour capturer des images d'entraînement, la qualité, la netteté et les couleurs des images seront différentes de celles d'une caméra connectée à un appareil IoT.

![2 photos de bananes, une de basse résolution avec un mauvais éclairage prise par un appareil IoT, et une de haute résolution avec un bon éclairage prise par un téléphone](../../../../../translated_images/fr/banana-picture-compare.174df164dc326a42.webp)

Dans l'image ci-dessus, la photo de banane à gauche a été prise avec une caméra Raspberry Pi, tandis que celle de droite a été prise du même fruit au même endroit avec un iPhone. Il y a une différence notable de qualité : la photo de l'iPhone est plus nette, avec des couleurs plus vives et un meilleur contraste.

✅ Qu'est-ce qui pourrait encore causer des prédictions incorrectes pour les images capturées par votre appareil IoT ? Pensez à l'environnement dans lequel un appareil IoT pourrait être utilisé, et aux facteurs pouvant affecter l'image capturée.

Pour améliorer le modèle, vous pouvez le réentraîner en utilisant les images capturées par l'appareil IoT.

### Tâche - améliorer le modèle

1. Classez plusieurs images de fruits mûrs et non mûrs avec votre appareil IoT.

1. Dans le portail Custom Vision, réentraînez le modèle en utilisant les images dans l'onglet *Predictions*.

    > ⚠️ Vous pouvez vous référer [aux instructions pour réentraîner votre classificateur dans la leçon 1 si nécessaire](../1-train-fruit-detector/README.md#retrain-your-image-classifier).

1. Si vos images sont très différentes de celles utilisées initialement pour l'entraînement, vous pouvez supprimer toutes les images originales en les sélectionnant dans l'onglet *Training Images* et en cliquant sur le bouton **Delete**. Pour sélectionner une image, survolez-la avec votre curseur, une coche apparaîtra. Cliquez sur cette coche pour sélectionner ou désélectionner l'image.

1. Entraînez une nouvelle itération du modèle et publiez-la en suivant les étapes ci-dessus.

1. Mettez à jour l'URL de l'endpoint dans votre code, et relancez l'application.

1. Répétez ces étapes jusqu'à ce que vous soyez satisfait des résultats des prédictions.

---

## 🚀 Défi

Dans quelle mesure la résolution ou l'éclairage des images affecte-t-il les prédictions ?

Essayez de modifier la résolution des images dans le code de votre appareil et voyez si cela fait une différence dans la qualité des images. Essayez également de changer l'éclairage.

Si vous deviez créer un appareil de production à vendre à des fermes ou des usines, comment garantiriez-vous des résultats cohérents en permanence ?

## Quiz après la leçon

[Quiz après la leçon](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/32)

## Révision et auto-apprentissage

Vous avez entraîné votre modèle Custom Vision en utilisant le portail. Cela repose sur la disponibilité d'images - et dans le monde réel, il se peut que vous ne puissiez pas obtenir des données d'entraînement correspondant à ce que la caméra de votre appareil capture. Vous pouvez contourner ce problème en entraînant directement depuis votre appareil en utilisant l'API d'entraînement, pour entraîner un modèle avec des images capturées par votre appareil IoT.

* Lisez la documentation sur l'API d'entraînement dans le [guide de démarrage rapide du SDK Custom Vision](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/quickstarts/image-classification?WT.mc_id=academic-17441-jabenn&tabs=visual-studio&pivots=programming-language-python)

## Devoir

[Répondre aux résultats de classification](assignment.md)

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction professionnelle réalisée par un humain. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.