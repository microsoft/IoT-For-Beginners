# Déclencher la détection de la qualité des fruits à partir d'un capteur

![Un aperçu en sketchnote de cette leçon](../../../../../translated_images/fr/lesson-18.92c32ed1d354caa5.webp)

> Sketchnote par [Nitya Narasimhan](https://github.com/nitya). Cliquez sur l'image pour une version agrandie.

## Quiz avant la leçon

[Quiz avant la leçon](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/35)

## Introduction

Une application IoT ne se limite pas à un seul appareil capturant des données et les envoyant au cloud. Elle implique souvent plusieurs appareils travaillant ensemble pour capturer des données du monde physique via des capteurs, prendre des décisions basées sur ces données, et interagir avec le monde physique via des actionneurs ou des visualisations.

Dans cette leçon, vous apprendrez à concevoir des applications IoT complexes, en intégrant plusieurs capteurs, plusieurs services cloud pour analyser et stocker les données, et en affichant une réponse via un actionneur. Vous apprendrez à concevoir un prototype de système de contrôle de la qualité des fruits, notamment en utilisant des capteurs de proximité pour déclencher l'application IoT, et à comprendre l'architecture de ce prototype.

Dans cette leçon, nous aborderons :

* [Concevoir des applications IoT complexes](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Concevoir un système de contrôle de la qualité des fruits](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Déclencher la vérification de la qualité des fruits à partir d'un capteur](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Données utilisées pour un détecteur de qualité des fruits](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Utiliser des appareils de développement pour simuler plusieurs appareils IoT](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Passer à la production](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)

> 🗑 C'est la dernière leçon de ce projet, donc après avoir terminé cette leçon et l'exercice, n'oubliez pas de nettoyer vos services cloud. Vous aurez besoin des services pour terminer l'exercice, alors assurez-vous de le faire en premier.
>
> Consultez [le guide de nettoyage de votre projet](../../../clean-up.md) si nécessaire pour des instructions sur la façon de procéder.

## Concevoir des applications IoT complexes

Les applications IoT sont composées de nombreux éléments, y compris une variété de dispositifs et de services internet.

Les applications IoT peuvent être décrites comme des *objets* (appareils) envoyant des données qui génèrent des *informations*. Ces *informations* entraînent des *actions* pour améliorer une entreprise ou un processus. Par exemple, un moteur (l'objet) envoie des données de température. Ces données sont utilisées pour évaluer si le moteur fonctionne comme prévu (l'information). L'information est utilisée pour prioriser de manière proactive le calendrier de maintenance du moteur (l'action).

* Différents objets collectent différentes données.
* Les services IoT fournissent des informations sur ces données, parfois en les complétant avec des données provenant de sources supplémentaires.
* Ces informations entraînent des actions, notamment le contrôle des actionneurs dans les appareils ou la visualisation des données.

### Architecture IoT de référence

![Une architecture IoT de référence](../../../../../translated_images/fr/iot-reference-architecture.2278b98b55c6d4e8.webp)

Le diagramme ci-dessus montre une architecture IoT de référence.

> 🎓 Une *architecture de référence* est un exemple d'architecture que vous pouvez utiliser comme modèle lors de la conception de nouveaux systèmes. Dans ce cas, si vous construisez un nouveau système IoT, vous pouvez suivre l'architecture de référence, en substituant vos propres appareils et services là où cela est approprié.

* **Objets** : ce sont des appareils qui collectent des données à partir de capteurs, interagissant peut-être avec des services en périphérie pour interpréter ces données, comme des classificateurs d'images pour interpréter des données d'image. Les données des appareils sont envoyées à un service IoT.
* **Informations** : elles proviennent d'applications sans serveur ou d'analyses effectuées sur des données stockées.
* **Actions** : elles peuvent être des commandes envoyées aux appareils ou des visualisations de données permettant aux humains de prendre des décisions.

![Une architecture IoT de référence](../../../../../translated_images/fr/iot-reference-architecture-azure.0b8d2161af924cb1.webp)

Le diagramme ci-dessus montre certains des composants et services abordés jusqu'à présent dans ces leçons et comment ils s'articulent dans une architecture IoT de référence.

* **Objets** : vous avez écrit du code pour capturer des données à partir de capteurs et analyser des images à l'aide de Custom Vision, exécuté à la fois dans le cloud et sur un appareil en périphérie. Ces données ont été envoyées à IoT Hub.
* **Informations** : vous avez utilisé Azure Functions pour répondre aux messages envoyés à un IoT Hub et stocké des données pour une analyse ultérieure dans Azure Storage.
* **Actions** : vous avez contrôlé des actionneurs en fonction des décisions prises dans le cloud et des commandes envoyées aux appareils, et vous avez visualisé des données à l'aide d'Azure Maps.

✅ Réfléchissez à d'autres appareils IoT que vous avez utilisés, comme des appareils électroménagers intelligents. Quels sont les objets, les informations et les actions impliqués dans cet appareil et son logiciel ?

Ce modèle peut être étendu à une échelle aussi grande ou petite que nécessaire, en ajoutant davantage d'appareils et de services.

### Données et sécurité

Lorsque vous définissez l'architecture de votre système, vous devez constamment prendre en compte les données et la sécurité.

* Quelles données votre appareil envoie-t-il et reçoit-il ?
* Comment ces données doivent-elles être sécurisées et protégées ?
* Comment l'accès à l'appareil et au service cloud doit-il être contrôlé ?

✅ Réfléchissez à la sécurité des données des appareils IoT que vous possédez. Combien de ces données sont personnelles et doivent rester privées, à la fois en transit et lorsqu'elles sont stockées ? Quelles données ne devraient pas être stockées ?

## Concevoir un système de contrôle de la qualité des fruits

Prenons maintenant cette idée d'objets, d'informations et d'actions et appliquons-la à notre détecteur de qualité des fruits pour concevoir une application de bout en bout plus large.

Imaginez que vous avez reçu la tâche de construire un détecteur de qualité des fruits à utiliser dans une usine de traitement. Les fruits circulent sur un système de tapis roulant où, actuellement, des employés passent du temps à vérifier les fruits à la main et à retirer les fruits non mûrs à leur arrivée. Pour réduire les coûts, le propriétaire de l'usine souhaite un système automatisé.

✅ L'un des phénomènes liés à la montée de l'IoT (et de la technologie en général) est que les emplois manuels sont remplacés par des machines. Faites des recherches : Combien d'emplois sont estimés être perdus à cause de l'IoT ? Combien de nouveaux emplois seront créés pour construire des appareils IoT ?

Vous devez construire un système où les fruits sont détectés à leur arrivée sur le tapis roulant, ils sont ensuite photographiés et vérifiés à l'aide d'un modèle d'IA exécuté en périphérie. Les résultats sont ensuite envoyés au cloud pour être stockés, et si le fruit est non mûr, une notification est donnée pour que le fruit non mûr puisse être retiré.

|   |   |
| - | - |
| **Objets** | Détecteur pour les fruits arrivant sur le tapis roulant<br>Caméra pour photographier et classifier les fruits<br>Appareil en périphérie exécutant le classificateur<br>Appareil pour notifier les fruits non mûrs |
| **Informations** | Décider de vérifier la maturité des fruits<br>Stocker les résultats de la classification de maturité<br>Déterminer s'il est nécessaire d'alerter sur les fruits non mûrs |
| **Actions** | Envoyer une commande à un appareil pour photographier les fruits et les vérifier avec un classificateur d'images<br>Envoyer une commande à un appareil pour alerter que les fruits sont non mûrs |

### Prototyper votre application

![Une architecture IoT de référence pour la vérification de la qualité des fruits](../../../../../translated_images/fr/iot-reference-architecture-fruit-quality.cc705f121c3b6fa7.webp)

Le diagramme ci-dessus montre une architecture de référence pour cette application prototype.

* Un appareil IoT avec un capteur de proximité détecte l'arrivée des fruits. Cela envoie un message au cloud pour indiquer que des fruits ont été détectés.
* Une application sans serveur dans le cloud envoie une commande à un autre appareil pour prendre une photo et classifier l'image.
* Un appareil IoT avec une caméra prend une photo et l'envoie à un classificateur d'images exécuté en périphérie. Les résultats sont ensuite envoyés au cloud.
* Une application sans serveur dans le cloud stocke ces informations pour être analysées ultérieurement afin de voir quel pourcentage de fruits est non mûr. Si le fruit est non mûr, elle envoie une commande à un autre appareil IoT pour alerter les ouvriers de l'usine via une LED.

> 💁 Cette application IoT entière pourrait être mise en œuvre comme un seul appareil, avec toute la logique pour démarrer la classification d'image et contrôler la LED intégrée. Elle pourrait utiliser un IoT Hub uniquement pour suivre le nombre de fruits non mûrs détectés et configurer l'appareil. Dans cette leçon, elle est étendue pour démontrer les concepts des applications IoT à grande échelle.

Pour le prototype, vous implémenterez tout cela sur un seul appareil. Si vous utilisez un microcontrôleur, vous utiliserez un appareil en périphérie séparé pour exécuter le classificateur d'images. Vous avez déjà appris la plupart des éléments nécessaires pour construire cela.

## Déclencher la vérification de la qualité des fruits à partir d'un capteur

L'appareil IoT a besoin d'un déclencheur pour indiquer quand les fruits sont prêts à être classifiés. Un déclencheur pour cela serait de mesurer quand le fruit est à la bonne position sur le tapis roulant en mesurant la distance par rapport à un capteur.

![Les capteurs de proximité envoient des faisceaux laser vers des objets comme des bananes et mesurent le temps avant que le faisceau ne soit réfléchi](../../../../../translated_images/fr/proximity-sensor.f5cd752c77fb62fe.webp)

Les capteurs de proximité peuvent être utilisés pour mesurer la distance entre le capteur et un objet. Ils transmettent généralement un faisceau de rayonnement électromagnétique, tel qu'un faisceau laser ou une lumière infrarouge, puis détectent le rayonnement réfléchi par un objet. Le temps écoulé entre l'envoi du faisceau laser et le signal réfléchi peut être utilisé pour calculer la distance par rapport au capteur.

> 💁 Vous avez probablement utilisé des capteurs de proximité sans même le savoir. La plupart des smartphones éteignent l'écran lorsque vous les tenez contre votre oreille pour éviter de raccrocher accidentellement avec votre lobe d'oreille. Cela fonctionne grâce à un capteur de proximité, qui détecte un objet proche de l'écran pendant un appel et désactive les capacités tactiles jusqu'à ce que le téléphone soit à une certaine distance.

### Tâche - déclencher la détection de la qualité des fruits à partir d'un capteur de distance

Suivez le guide correspondant pour utiliser un capteur de proximité afin de détecter un objet avec votre appareil IoT :

* [Arduino - Wio Terminal](wio-terminal-proximity.md)
* [Ordinateur monocarte - Raspberry Pi](pi-proximity.md)
* [Ordinateur monocarte - Appareil virtuel](virtual-device-proximity.md)

## Données utilisées pour un détecteur de qualité des fruits

Le détecteur de fruits prototype comporte plusieurs composants qui communiquent entre eux.

![Les composants communiquent entre eux](../../../../../translated_images/fr/fruit-quality-detector-message-flow.adf2a65da8fd8741.webp)

* Un capteur de proximité mesurant la distance par rapport à un fruit et envoyant cela à IoT Hub
* La commande pour contrôler la caméra provenant de IoT Hub vers l'appareil caméra
* Les résultats de la classification d'image envoyés à IoT Hub
* La commande pour contrôler une LED afin d'alerter lorsque le fruit est non mûr, envoyée de IoT Hub à l'appareil avec la LED

Il est utile de définir la structure de ces messages à l'avance, avant de construire l'application.

> 💁 Presque tous les développeurs expérimentés ont, à un moment donné de leur carrière, passé des heures, des jours ou même des semaines à traquer des bugs causés par des différences entre les données envoyées et celles attendues.

Par exemple - si vous envoyez des informations sur la température, comment définiriez-vous le JSON ? Vous pourriez avoir un champ appelé `temperature`, ou utiliser l'abréviation courante `temp`.

```json
{
    "temperature": 20.7
}
```

par rapport à :

```json
{
    "temp": 20.7
}
```

Vous devez également prendre en compte les unités - la température est-elle en °C ou en °F ? Si vous mesurez la température avec un appareil grand public et que l'utilisateur change les unités d'affichage, vous devez vous assurer que les unités envoyées au cloud restent cohérentes.

✅ Faites des recherches : Comment des problèmes d'unités ont-ils causé le crash du Mars Climate Orbiter de 125 millions de dollars ?

Réfléchissez aux données envoyées pour le détecteur de qualité des fruits. Comment définiriez-vous chaque message ? Où analyseriez-vous les données et prendriez-vous des décisions sur les données à envoyer ?

Par exemple - déclencher la classification d'image à l'aide du capteur de proximité. L'appareil IoT mesure la distance, mais où la décision est-elle prise ? L'appareil décide-t-il que le fruit est suffisamment proche et envoie un message pour dire à IoT Hub de déclencher la classification ? Ou envoie-t-il des mesures de proximité et laisse IoT Hub décider ?

La réponse à ces questions est - cela dépend. Chaque cas d'utilisation est différent, c'est pourquoi, en tant que développeur IoT, vous devez comprendre le système que vous construisez, comment il est utilisé et les données détectées.

* Si la décision est prise par IoT Hub, vous devez envoyer plusieurs mesures de distance.
* Si vous envoyez trop de messages, cela augmente le coût de IoT Hub et la quantité de bande passante nécessaire à vos appareils IoT (surtout dans une usine avec des millions d'appareils). Cela peut également ralentir votre appareil.
* Si vous prenez la décision sur l'appareil, vous devrez fournir un moyen de configurer l'appareil pour affiner la machine.

## Utiliser des appareils de développement pour simuler plusieurs appareils IoT

Pour construire votre prototype, vous aurez besoin que votre kit de développement IoT agisse comme plusieurs appareils, envoyant des télémétries et répondant à des commandes.

### Simuler plusieurs appareils IoT sur un Raspberry Pi ou un matériel IoT virtuel

Lorsque vous utilisez un ordinateur monocarte comme un Raspberry Pi, vous pouvez exécuter plusieurs applications à la fois. Cela signifie que vous pouvez simuler plusieurs appareils IoT en créant plusieurs applications, une par 'appareil IoT'. Par exemple, vous pouvez implémenter chaque appareil comme un fichier Python séparé et les exécuter dans différentes sessions terminal.
> 💁 Sachez que certains matériels ne fonctionneront pas s'ils sont utilisés simultanément par plusieurs applications.
### Simulation de plusieurs appareils sur un microcontrôleur

Les microcontrôleurs sont plus complexes à utiliser pour simuler plusieurs appareils. Contrairement aux ordinateurs monocartes, vous ne pouvez pas exécuter plusieurs applications simultanément. Vous devez inclure toute la logique pour tous les appareils IoT distincts dans une seule application.

Quelques suggestions pour simplifier ce processus :

* Créez une ou plusieurs classes par appareil IoT - par exemple des classes appelées `DistanceSensor`, `ClassifierCamera`, `LEDController`. Chacune peut avoir ses propres méthodes `setup` et `loop` appelées par les fonctions principales `setup` et `loop`.
* Gérez les commandes dans un seul endroit et dirigez-les vers la classe d'appareil concernée selon les besoins.
* Dans la fonction principale `loop`, vous devrez prendre en compte le timing de chaque appareil différent. Par exemple, si vous avez une classe d'appareil qui doit traiter toutes les 10 secondes et une autre qui doit traiter toutes les secondes, alors dans votre fonction principale `loop`, utilisez un délai d'une seconde. Chaque appel de `loop` déclenche le code pertinent pour l'appareil qui doit traiter chaque seconde, et utilisez un compteur pour compter chaque boucle, en traitant l'autre appareil lorsque le compteur atteint 10 (en réinitialisant le compteur ensuite).

## Passage à la production

Le prototype servira de base à un système de production final. Certaines différences lorsque vous passez à la production incluraient :

* Composants robustes - utilisation de matériel conçu pour résister au bruit, à la chaleur, aux vibrations et au stress d'une usine.
* Communications internes - certains composants communiqueraient directement, évitant le passage par le cloud, et n'envoyant des données au cloud que pour être stockées. La manière dont cela est fait dépend de la configuration de l'usine, soit par des communications directes, soit en exécutant une partie du service IoT en périphérie à l'aide d'un appareil passerelle.
* Options de configuration - chaque usine et cas d'utilisation est différent, donc le matériel devrait être configurable. Par exemple, le capteur de proximité pourrait devoir détecter différents fruits à différentes distances. Plutôt que de coder en dur la distance pour déclencher la classification, vous voudriez que cela soit configurable via le cloud, par exemple en utilisant un jumeau numérique.
* Retrait automatisé des fruits - au lieu d'utiliser une LED pour signaler qu'un fruit est non mûr, des appareils automatisés le retireraient.

✅ Faites des recherches : De quelles autres manières les appareils de production différeraient-ils des kits de développement ?

---

## 🚀 Défi

Dans cette leçon, vous avez appris certains concepts nécessaires pour concevoir un système IoT. Repensez aux projets précédents. Comment s'intègrent-ils dans l'architecture de référence présentée ci-dessus ?

Choisissez l'un des projets réalisés jusqu'à présent et réfléchissez à la conception d'une solution plus complexe réunissant plusieurs fonctionnalités au-delà de ce qui a été couvert dans les projets. Dessinez l'architecture et réfléchissez à tous les appareils et services dont vous auriez besoin.

Par exemple - un dispositif de suivi de véhicule qui combine GPS avec des capteurs pour surveiller des éléments comme les températures dans un camion réfrigéré, les temps de marche et d'arrêt du moteur, et l'identité du conducteur. Quels sont les appareils impliqués, les services utilisés, les données transmises, ainsi que les considérations de sécurité et de confidentialité ?

## Quiz post-lecture

[Quiz post-lecture](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/36)

## Révision et étude personnelle

* Lisez davantage sur l'architecture IoT dans la [documentation sur l'architecture de référence IoT Azure sur Microsoft docs](https://docs.microsoft.com/azure/architecture/reference-architectures/iot?WT.mc_id=academic-17441-jabenn)
* Lisez davantage sur les jumeaux numériques dans la [documentation sur la compréhension et l'utilisation des jumeaux numériques dans IoT Hub sur Microsoft docs](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-device-twins?WT.mc_id=academic-17441-jabenn)
* Lisez sur OPC-UA, un protocole de communication machine à machine utilisé dans l'automatisation industrielle, sur la [page OPC-UA de Wikipédia](https://wikipedia.org/wiki/OPC_Unified_Architecture)

## Devoir

[Construisez un détecteur de qualité des fruits](assignment.md)

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction professionnelle réalisée par un humain. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.