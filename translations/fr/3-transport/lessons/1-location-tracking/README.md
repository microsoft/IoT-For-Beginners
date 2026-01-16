<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "52ed2bd997d08040f79a1a6ef2bac958",
  "translation_date": "2025-08-25T00:48:42+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/README.md",
  "language_code": "fr"
}
-->
# Suivi de localisation

![Un aperçu en sketchnote de cette leçon](../../../../../translated_images/fr/lesson-11.9fddbac4b664c6d50ab7ac9bb32f1fc3f945f03760e72f7f43938073762fb017.jpg)

> Sketchnote par [Nitya Narasimhan](https://github.com/nitya). Cliquez sur l'image pour une version agrandie.

## Quiz avant la leçon

[Quiz avant la leçon](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/21)

## Introduction

Le processus principal pour acheminer des aliments d'un agriculteur à un consommateur implique le chargement de caisses de produits sur des camions, des navires, des avions ou d'autres véhicules de transport commercial, et la livraison des aliments à un endroit donné - soit directement à un client, soit à un centre ou entrepôt pour traitement. L'ensemble du processus de bout en bout, de la ferme au consommateur, fait partie d'un processus appelé la *chaîne d'approvisionnement*. La vidéo ci-dessous de la W. P. Carey School of Business de l'Université d'État de l'Arizona explique en détail le concept de chaîne d'approvisionnement et sa gestion.

[![Qu'est-ce que la gestion de la chaîne d'approvisionnement ? Une vidéo de la W. P. Carey School of Business de l'Université d'État de l'Arizona](https://img.youtube.com/vi/Mi1QBxVjZAw/0.jpg)](https://www.youtube.com/watch?v=Mi1QBxVjZAw)

> 🎥 Cliquez sur l'image ci-dessus pour regarder la vidéo

L'ajout de dispositifs IoT peut considérablement améliorer votre chaîne d'approvisionnement, vous permettant de gérer où se trouvent les articles, de mieux planifier le transport et la manutention des marchandises, et de réagir plus rapidement aux problèmes.

Lors de la gestion d'une flotte de véhicules tels que des camions, il est utile de savoir où se trouve chaque véhicule à un moment donné. Les véhicules peuvent être équipés de capteurs GPS qui envoient leur localisation à des systèmes IoT, permettant aux propriétaires de localiser précisément leur position, de voir l'itinéraire qu'ils ont emprunté et de savoir quand ils arriveront à destination. La plupart des véhicules fonctionnent hors de la couverture WiFi, ils utilisent donc des réseaux cellulaires pour envoyer ce type de données. Parfois, le capteur GPS est intégré à des dispositifs IoT plus complexes tels que des journaux électroniques. Ces dispositifs suivent la durée de transit d'un camion pour garantir que les conducteurs respectent les lois locales sur les heures de travail.

Dans cette leçon, vous apprendrez à suivre la localisation d'un véhicule à l'aide d'un capteur GPS (Système de Positionnement Global).

Dans cette leçon, nous aborderons :

* [Véhicules connectés](../../../../../3-transport/lessons/1-location-tracking)
* [Coordonnées géospatiales](../../../../../3-transport/lessons/1-location-tracking)
* [Systèmes de Positionnement Global (GPS)](../../../../../3-transport/lessons/1-location-tracking)
* [Lire les données des capteurs GPS](../../../../../3-transport/lessons/1-location-tracking)
* [Données GPS NMEA](../../../../../3-transport/lessons/1-location-tracking)
* [Décoder les données des capteurs GPS](../../../../../3-transport/lessons/1-location-tracking)

## Véhicules connectés

L'IoT transforme la manière dont les marchandises sont transportées en créant des flottes de *véhicules connectés*. Ces véhicules sont reliés à des systèmes informatiques centraux qui rapportent des informations sur leur localisation et d'autres données de capteurs. Avoir une flotte de véhicules connectés offre de nombreux avantages :

* Suivi de localisation - vous pouvez localiser précisément où se trouve un véhicule à tout moment, ce qui vous permet de :

  * Recevoir des alertes lorsqu'un véhicule est sur le point d'arriver à destination pour préparer une équipe au déchargement
  * Localiser des véhicules volés
  * Combiner les données de localisation et d'itinéraire avec les problèmes de circulation pour permettre de rediriger les véhicules en cours de trajet
  * Être en conformité avec les taxes. Certains pays facturent les véhicules en fonction du kilométrage parcouru sur les routes publiques (comme les [RUC de Nouvelle-Zélande](https://www.nzta.govt.nz/vehicles/licensing-rego/road-user-charges/)), donc savoir quand un véhicule est sur des routes publiques par rapport à des routes privées facilite le calcul des taxes dues.
  * Savoir où envoyer des équipes de maintenance en cas de panne

* Télémétrie du conducteur - pouvoir s'assurer que les conducteurs respectent les limites de vitesse, prennent les virages à des vitesses appropriées, freinent tôt et efficacement, et conduisent en toute sécurité. Les véhicules connectés peuvent également être équipés de caméras pour enregistrer les incidents. Cela peut être lié à l'assurance, offrant des tarifs réduits pour les bons conducteurs.

* Conformité des heures de conduite - garantir que les conducteurs ne conduisent que pendant les heures légalement autorisées en fonction des moments où ils allument et éteignent le moteur.

Ces avantages peuvent être combinés - par exemple, en combinant la conformité des heures de conduite avec le suivi de localisation pour rediriger les conducteurs s'ils ne peuvent pas atteindre leur destination dans les heures de conduite autorisées. Ils peuvent également être combinés avec d'autres télémétries spécifiques au véhicule, telles que les données de température des camions frigorifiques, permettant de rediriger les véhicules si leur itinéraire actuel signifie que les marchandises ne peuvent pas être maintenues à la bonne température.

> 🎓 La logistique est le processus de transport des marchandises d'un endroit à un autre, comme d'une ferme à un supermarché via un ou plusieurs entrepôts. Un agriculteur emballe des caisses de tomates qui sont chargées sur un camion, livrées à un entrepôt central, puis mises sur un deuxième camion qui peut contenir un mélange de différents types de produits, ensuite livrés à un supermarché.

Le composant principal du suivi des véhicules est le GPS - des capteurs capables de localiser leur position n'importe où sur Terre. Dans cette leçon, vous apprendrez à utiliser un capteur GPS, en commençant par comprendre comment définir une localisation sur Terre.

## Coordonnées géospatiales

Les coordonnées géospatiales sont utilisées pour définir des points à la surface de la Terre, de manière similaire à la façon dont les coordonnées peuvent être utilisées pour dessiner un pixel sur un écran d'ordinateur ou positionner des points dans une broderie. Pour un point unique, vous avez une paire de coordonnées. Par exemple, le campus de Microsoft à Redmond, Washington, USA est situé à 47.6423109, -122.1390293.

### Latitude et longitude

La Terre est une sphère - un cercle tridimensionnel. En raison de cela, les points sont définis en la divisant en 360 degrés, comme la géométrie des cercles. La latitude mesure le nombre de degrés du nord au sud, la longitude mesure le nombre de degrés d'est en ouest.

> 💁 Personne ne sait vraiment pourquoi les cercles sont divisés en 360 degrés. La [page sur le degré (angle) sur Wikipédia](https://wikipedia.org/wiki/Degree_(angle)) couvre certaines des raisons possibles.

![Lignes de latitude allant de 90° au pôle Nord, 45° à mi-chemin entre le pôle Nord et l'équateur, 0° à l'équateur, -45° à mi-chemin entre l'équateur et le pôle Sud, et -90° au pôle Sud](../../../../../translated_images/fr/latitude-lines.11d8d91dfb2014a57437272d7db7fd6607243098e8685f06e0c5f1ec984cb7eb.png)

La latitude est mesurée à l'aide de lignes qui entourent la Terre et sont parallèles à l'équateur, divisant les hémisphères Nord et Sud en 90° chacun. L'équateur est à 0°, le pôle Nord est à 90°, également connu sous le nom de 90° Nord, et le pôle Sud est à -90°, ou 90° Sud.

La longitude est mesurée comme le nombre de degrés mesurés d'est en ouest. L'origine 0° de la longitude est appelée le *méridien de Greenwich*, et a été définie en 1884 comme une ligne allant du pôle Nord au pôle Sud qui passe par l'[Observatoire royal britannique de Greenwich, Angleterre](https://wikipedia.org/wiki/Royal_Observatory,_Greenwich).

![Lignes de longitude allant de -180° à l'ouest du méridien de Greenwich, à 0° sur le méridien de Greenwich, à 180° à l'est du méridien de Greenwich](../../../../../translated_images/fr/longitude-meridians.ab4ef1c91c064586b0185a3c8d39e585903696c6a7d28c098a93a629cddb5d20.png)

> 🎓 Un méridien est une ligne imaginaire droite qui va du pôle Nord au pôle Sud, formant un demi-cercle.

Pour mesurer la longitude d'un point, vous mesurez le nombre de degrés autour de l'équateur depuis le méridien de Greenwich jusqu'à un méridien qui passe par ce point. La longitude va de -180°, ou 180° Ouest, à 0° au méridien de Greenwich, jusqu'à 180°, ou 180° Est. 180° et -180° désignent le même point, l'antiméridien ou le 180e méridien. C'est un méridien situé à l'opposé du méridien de Greenwich.

> 💁 L'antiméridien ne doit pas être confondu avec la ligne de changement de date internationale, qui est approximativement au même endroit, mais n'est pas une ligne droite et varie pour s'adapter aux frontières géopolitiques.

✅ Faites des recherches : Essayez de trouver la latitude et la longitude de votre emplacement actuel.

### Degrés, minutes et secondes vs degrés décimaux

Traditionnellement, les mesures des degrés de latitude et de longitude étaient effectuées en utilisant la numérotation sexagésimale, ou base-60, un système de numérotation utilisé par les anciens Babyloniens qui ont effectué les premières mesures et enregistrements du temps et de la distance. Vous utilisez probablement la numérotation sexagésimale tous les jours sans même vous en rendre compte - en divisant les heures en 60 minutes et les minutes en 60 secondes.

La longitude et la latitude sont mesurées en degrés, minutes et secondes, avec une minute correspondant à 1/60 d'un degré, et une seconde correspondant à 1/60 d'une minute.

Par exemple, à l'équateur :

* 1° de latitude équivaut à **111,3 kilomètres**
* 1 minute de latitude équivaut à 111,3/60 = **1,855 kilomètres**
* 1 seconde de latitude équivaut à 1,855/60 = **0,031 kilomètres**

Le symbole pour une minute est une apostrophe, pour une seconde c'est une double apostrophe. Par exemple, 2 degrés, 17 minutes et 43 secondes seraient écrits comme 2°17'43". Les fractions de secondes sont données sous forme décimale, par exemple une demi-seconde est 0°0'0.5".

Les ordinateurs ne fonctionnent pas en base-60, donc ces coordonnées sont données sous forme de degrés décimaux lorsqu'on utilise des données GPS dans la plupart des systèmes informatiques. Par exemple, 2°17'43" correspond à 2,295277. Le symbole du degré est généralement omis.

Les coordonnées d'un point sont toujours données sous la forme `latitude, longitude`, donc l'exemple précédent du campus de Microsoft à 47.6423109,-122.117198 a :

* Une latitude de 47.6423109 (47.6423109 degrés au nord de l'équateur)
* Une longitude de -122.1390293 (122.1390293 degrés à l'ouest du méridien de Greenwich).

![Le campus de Microsoft à 47.6423109,-122.117198](../../../../../translated_images/fr/microsoft-gps-location-world.a321d481b010f6adfcca139b2ba0adc53b79f58a540495b8e2ce7f779ea64bfe.png)

## Systèmes de Positionnement Global (GPS)

Les systèmes GPS utilisent plusieurs satellites en orbite autour de la Terre pour localiser votre position. Vous avez probablement utilisé des systèmes GPS sans même vous en rendre compte - pour trouver votre position sur une application de cartographie sur votre téléphone comme Apple Maps ou Google Maps, pour voir où se trouve votre trajet dans une application de covoiturage comme Uber ou Lyft, ou en utilisant la navigation par satellite (sat-nav) dans votre voiture.

> 🎓 Les satellites dans la "navigation par satellite" sont des satellites GPS !

Les systèmes GPS fonctionnent en ayant un certain nombre de satellites qui envoient un signal avec la position actuelle de chaque satellite et une horodatage précis. Ces signaux sont envoyés par ondes radio et détectés par une antenne dans le capteur GPS. Un capteur GPS détecte ces signaux et, en utilisant l'heure actuelle, mesure combien de temps il a fallu pour que le signal atteigne le capteur depuis le satellite. Étant donné que la vitesse des ondes radio est constante, le capteur GPS peut utiliser l'horodatage envoyé pour calculer à quelle distance le capteur se trouve du satellite. En combinant les données d'au moins 3 satellites avec les positions envoyées, le capteur GPS est capable de localiser sa position sur Terre.

> 💁 Les capteurs GPS ont besoin d'antennes pour détecter les ondes radio. Les antennes intégrées aux camions et voitures équipés de GPS embarqué sont positionnées pour obtenir un bon signal, généralement sur le pare-brise ou le toit. Si vous utilisez un système GPS séparé, comme un smartphone ou un dispositif IoT, vous devez vous assurer que l'antenne intégrée au système GPS ou au téléphone a une vue dégagée du ciel, comme être montée sur votre pare-brise.

![En connaissant la distance entre le capteur et plusieurs satellites, la localisation peut être calculée](../../../../../translated_images/fr/gps-satellites.04acf1148fe25fbf1586bc2e8ba698e8d79b79a50c36824b38417dd13372b90f.png)

Les satellites GPS tournent autour de la Terre, et ne sont pas à un point fixe au-dessus du capteur, donc les données de localisation incluent l'altitude au-dessus du niveau de la mer ainsi que la latitude et la longitude.

Le GPS avait autrefois des limitations de précision imposées par l'armée américaine, limitant la précision à environ 5 mètres. Cette limitation a été supprimée en 2000, permettant une précision de 30 centimètres. Obtenir cette précision n'est pas toujours possible en raison des interférences avec les signaux.

✅ Si vous avez un smartphone, lancez l'application de cartographie et voyez à quel point votre localisation est précise. Il peut falloir un court laps de temps pour que votre téléphone détecte plusieurs satellites afin d'obtenir une localisation plus précise.
💁 Les satellites contiennent des horloges atomiques d'une précision incroyable, mais elles dérivent de 38 microsecondes (0,0000038 secondes) par jour par rapport aux horloges atomiques sur Terre, en raison du ralentissement du temps à mesure que la vitesse augmente, comme prédit par les théories de la relativité restreinte et générale d'Einstein - les satellites se déplacent plus rapidement que la rotation de la Terre. Cette dérive a été utilisée pour prouver les prédictions de la relativité restreinte et générale, et doit être prise en compte dans la conception des systèmes GPS. Littéralement, le temps s'écoule plus lentement sur un satellite GPS.
Les systèmes GPS ont été développés et déployés par plusieurs pays et unions politiques, notamment les États-Unis, la Russie, le Japon, l'Inde, l'UE et la Chine. Les capteurs GPS modernes peuvent se connecter à la plupart de ces systèmes pour obtenir des positions plus rapides et plus précises.

> 🎓 Les groupes de satellites dans chaque déploiement sont appelés constellations.

## Lire les données d'un capteur GPS

La plupart des capteurs GPS envoient des données GPS via UART.

> ⚠️ UART a été abordé dans [projet 2, leçon 2](../../../2-farm/lessons/2-detect-soil-moisture/README.md#universal-asynchronous-receiver-transmitter-uart). Consultez cette leçon si nécessaire.

Vous pouvez utiliser un capteur GPS sur votre appareil IoT pour obtenir des données GPS.

### Tâche - connecter un capteur GPS et lire les données GPS

Suivez le guide correspondant pour lire les données GPS à l'aide de votre appareil IoT :

* [Arduino - Wio Terminal](wio-terminal-gps-sensor.md)
* [Ordinateur monocarte - Raspberry Pi](pi-gps-sensor.md)
* [Ordinateur monocarte - Appareil virtuel](virtual-device-gps-sensor.md)

## Données GPS NMEA

Lorsque vous avez exécuté votre code, vous avez peut-être vu ce qui pourrait sembler être du charabia dans la sortie. Il s'agit en réalité de données GPS standard, et tout cela a une signification.

Les capteurs GPS produisent des données en utilisant des messages NMEA, selon la norme NMEA 0183. NMEA est un acronyme pour la [National Marine Electronics Association](https://www.nmea.org), une organisation commerciale basée aux États-Unis qui établit des normes pour la communication entre les appareils électroniques marins.

> 💁 Cette norme est propriétaire et coûte au moins 2 000 USD, mais suffisamment d'informations à son sujet sont dans le domaine public pour que la majeure partie de la norme ait été rétro-conçue et puisse être utilisée dans des codes open source ou non commerciaux.

Ces messages sont basés sur du texte. Chaque message est une *phrase* qui commence par un caractère `$`, suivi de 2 caractères indiquant la source du message (par exemple GP pour le système GPS des États-Unis, GN pour GLONASS, le système GPS russe), et de 3 caractères indiquant le type de message. Le reste du message est constitué de champs séparés par des virgules, se terminant par un caractère de nouvelle ligne.

Voici quelques types de messages qui peuvent être reçus :

| Type | Description |
| ---- | ----------- |
| GGA | Données de position GPS, incluant la latitude, la longitude et l'altitude du capteur GPS, ainsi que le nombre de satellites en vue pour calculer cette position. |
| ZDA | La date et l'heure actuelles, y compris le fuseau horaire local |
| GSV | Détails des satellites en vue - définis comme les satellites dont le capteur GPS peut détecter les signaux |

> 💁 Les données GPS incluent des horodatages, ce qui permet à votre appareil IoT d'obtenir l'heure si nécessaire à partir d'un capteur GPS, plutôt que de dépendre d'un serveur NTP ou d'une horloge temps réel interne.

Le message GGA inclut la position actuelle au format `(dd)dmm.mmmm`, ainsi qu'un caractère unique pour indiquer la direction. Le `d` dans le format représente les degrés, le `m` les minutes, avec les secondes exprimées en décimales de minutes. Par exemple, 2°17'43" correspondrait à 217.716666667 - 2 degrés, 17.716666667 minutes.

Le caractère de direction peut être `N` ou `S` pour la latitude pour indiquer le nord ou le sud, et `E` ou `W` pour la longitude pour indiquer l'est ou l'ouest. Par exemple, une latitude de 2°17'43" aurait un caractère de direction `N`, -2°17'43" aurait un caractère de direction `S`.

Par exemple - la phrase NMEA `$GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67`

* La partie latitude est `4738.538654,N`, ce qui se convertit en 47.6423109 en degrés décimaux. `4738.538654` correspond à 47.6423109, et la direction est `N` (nord), donc c'est une latitude positive.

* La partie longitude est `12208.341758,W`, ce qui se convertit en -122.1390293 en degrés décimaux. `12208.341758` correspond à 122.1390293°, et la direction est `W` (ouest), donc c'est une longitude négative.

## Décoder les données d'un capteur GPS

Plutôt que d'utiliser les données brutes NMEA, il est préférable de les décoder dans un format plus utile. Il existe de nombreuses bibliothèques open source que vous pouvez utiliser pour extraire des données utiles des messages NMEA bruts.

### Tâche - décoder les données d'un capteur GPS

Suivez le guide correspondant pour décoder les données d'un capteur GPS à l'aide de votre appareil IoT :

* [Arduino - Wio Terminal](wio-terminal-gps-decode.md)
* [Ordinateur monocarte - Raspberry Pi/Appareil IoT virtuel](single-board-computer-gps-decode.md)

---

## 🚀 Défi

Écrivez votre propre décodeur NMEA ! Plutôt que de vous appuyer sur des bibliothèques tierces pour décoder les phrases NMEA, pouvez-vous écrire votre propre décodeur pour extraire la latitude et la longitude des phrases NMEA ?

## Quiz post-lecture

[Quiz post-lecture](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/22)

## Révision et auto-apprentissage

* Lisez davantage sur les coordonnées géospatiales sur la [page du système de coordonnées géographiques sur Wikipédia](https://wikipedia.org/wiki/Geographic_coordinate_system).
* Renseignez-vous sur les méridiens d'origine sur d'autres corps célestes que la Terre sur la [page des méridiens d'origine sur Wikipédia](https://wikipedia.org/wiki/Prime_meridian#Prime_meridian_on_other_planetary_bodies).
* Faites des recherches sur les différents systèmes GPS des divers gouvernements et unions politiques du monde, tels que l'UE, le Japon, la Russie, l'Inde et les États-Unis.

## Devoir

[Explorer d'autres données GPS](assignment.md)

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.