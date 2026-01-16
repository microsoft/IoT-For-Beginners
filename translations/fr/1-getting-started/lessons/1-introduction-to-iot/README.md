<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9bae08314d8487cb76ddf3d8797e1544",
  "translation_date": "2025-08-24T23:28:14+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/README.md",
  "language_code": "fr"
}
-->
# Introduction à l'IoT

![Un aperçu illustré de cette leçon](../../../../../translated_images/fr/lesson-1.2606670fa61ee904687da5d6fa4e726639d524d064c895117da1b95b9ff6251d.jpg)

> Illustration par [Nitya Narasimhan](https://github.com/nitya). Cliquez sur l'image pour une version agrandie.

Cette leçon a été enseignée dans le cadre de la série [Hello IoT](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) du [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). Elle a été divisée en deux vidéos : une leçon d'une heure et une session de questions-réponses d'une heure approfondissant certains aspects de la leçon.

[![Leçon 1 : Introduction à l'IoT](https://img.youtube.com/vi/bVFfcYh6UBw/0.jpg)](https://youtu.be/bVFfcYh6UBw)

[![Leçon 1 : Introduction à l'IoT - Session de questions-réponses](https://img.youtube.com/vi/YI772q5v3yI/0.jpg)](https://youtu.be/YI772q5v3yI)

> 🎥 Cliquez sur les images ci-dessus pour regarder les vidéos

## Quiz avant la leçon

[Quiz avant la leçon](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/1)

## Introduction

Cette leçon aborde certains concepts introductifs autour de l'Internet des Objets (IoT) et vous guide dans la configuration de votre matériel.

Dans cette leçon, nous couvrirons :

* [Qu'est-ce que l'Internet des Objets ?](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Les appareils IoT](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Configurer votre appareil](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Applications de l'IoT](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Exemples d'appareils IoT autour de vous](../../../../../1-getting-started/lessons/1-introduction-to-iot)

## Qu'est-ce que l'Internet des Objets ?

Le terme "Internet des Objets" a été inventé par [Kevin Ashton](https://wikipedia.org/wiki/Kevin_Ashton) en 1999 pour désigner la connexion d'Internet au monde physique via des capteurs. Depuis, ce terme est utilisé pour décrire tout appareil interagissant avec le monde physique, soit en collectant des données via des capteurs, soit en fournissant des interactions physiques via des actionneurs (des dispositifs qui effectuent des actions comme allumer un interrupteur ou une LED), généralement connectés à d'autres appareils ou à Internet.

> **Les capteurs** collectent des informations du monde, comme mesurer la vitesse, la température ou la localisation.
>
> **Les actionneurs** transforment des signaux électriques en interactions physiques, comme déclencher un interrupteur, allumer des lumières, émettre des sons ou envoyer des signaux de contrôle à d'autres matériels, par exemple pour activer une prise électrique.

L'IoT en tant que domaine technologique ne se limite pas aux appareils. Il inclut également des services basés sur le cloud capables de traiter les données des capteurs ou d'envoyer des commandes aux actionneurs connectés. Il englobe aussi des appareils qui n'ont pas ou n'ont pas besoin de connexion Internet, souvent appelés appareils en périphérie (edge devices). Ces appareils peuvent traiter et répondre aux données des capteurs eux-mêmes, généralement à l'aide de modèles d'IA entraînés dans le cloud.

L'IoT est un domaine technologique en pleine croissance. On estime qu'à la fin de 2020, 30 milliards d'appareils IoT étaient déployés et connectés à Internet. À l'horizon 2025, on prévoit que les appareils IoT collecteront près de 80 zettaoctets de données, soit 80 trillions de gigaoctets. Cela représente une quantité énorme de données !

![Un graphique montrant l'évolution des appareils IoT actifs au fil du temps, avec une tendance à la hausse passant de moins de 5 milliards en 2015 à plus de 30 milliards en 2025](../../../../../images/connected-iot-devices.svg)

✅ Faites une petite recherche : Quelle proportion des données générées par les appareils IoT est réellement utilisée, et combien est gaspillée ? Pourquoi tant de données sont-elles ignorées ?

Ces données sont la clé du succès de l'IoT. Pour devenir un développeur IoT compétent, vous devez comprendre quelles données collecter, comment les collecter, comment prendre des décisions basées sur ces données, et comment utiliser ces décisions pour interagir avec le monde physique si nécessaire.

## Les appareils IoT

Le **T** dans IoT signifie **Things** (Objets) - des appareils qui interagissent avec le monde physique autour d'eux, soit en collectant des données via des capteurs, soit en fournissant des interactions physiques via des actionneurs.

Les appareils destinés à un usage commercial ou industriel, comme les trackers de fitness pour les consommateurs ou les contrôleurs de machines industrielles, sont généralement fabriqués sur mesure. Ils utilisent des cartes électroniques spécifiques, voire des processeurs personnalisés, conçus pour répondre aux besoins d'une tâche particulière, qu'il s'agisse d'être suffisamment petits pour tenir sur un poignet ou suffisamment robustes pour fonctionner dans un environnement de haute température, de stress ou de vibrations.

En tant que développeur apprenant l'IoT ou créant un prototype d'appareil, vous commencerez avec un kit de développement. Ce sont des appareils IoT polyvalents conçus pour les développeurs, souvent avec des fonctionnalités que vous ne retrouveriez pas sur un appareil de production, comme des broches externes pour connecter des capteurs ou des actionneurs, du matériel pour le débogage ou des ressources supplémentaires qui augmenteraient inutilement le coût lors d'une production en série.

Ces kits de développement se divisent généralement en deux catégories : les microcontrôleurs et les ordinateurs monocartes. Ces concepts seront introduits ici, et nous les approfondirons dans la prochaine leçon.

> 💁 Votre téléphone peut également être considéré comme un appareil IoT polyvalent, avec des capteurs et des actionneurs intégrés, utilisés de différentes manières par différentes applications avec divers services cloud. Vous pouvez même trouver des tutoriels IoT utilisant une application mobile comme appareil IoT.

### Microcontrôleurs

Un microcontrôleur (souvent appelé MCU, pour microcontroller unit) est un petit ordinateur composé de :

🧠 Un ou plusieurs processeurs centraux (CPU) - le "cerveau" du microcontrôleur qui exécute votre programme

💾 Mémoire (RAM et mémoire programme) - où sont stockés votre programme, vos données et vos variables

🔌 Connexions d'entrée/sortie (I/O) programmables - pour communiquer avec des périphériques externes (appareils connectés) comme des capteurs et des actionneurs

Les microcontrôleurs sont généralement des dispositifs informatiques à faible coût, avec des prix moyens pour ceux utilisés dans le matériel personnalisé tombant à environ 0,50 USD, et certains appareils coûtant aussi peu que 0,03 USD. Les kits de développement peuvent commencer à partir de 4 USD, avec des coûts augmentant à mesure que vous ajoutez des fonctionnalités. Le [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html), un kit de développement de microcontrôleur de [Seeed studios](https://www.seeedstudio.com) doté de capteurs, d'actionneurs, du WiFi et d'un écran, coûte environ 30 USD.

![Un Wio Terminal](../../../../../translated_images/fr/wio-terminal.b8299ee16587db9a.webp)

> 💁 Lorsque vous recherchez des microcontrôleurs sur Internet, méfiez-vous du terme **MCU**, car il renverra de nombreux résultats sur l'univers cinématographique Marvel (Marvel Cinematic Universe), et non sur les microcontrôleurs.

Les microcontrôleurs sont conçus pour être programmés pour effectuer un nombre limité de tâches très spécifiques, plutôt que d'être des ordinateurs polyvalents comme les PC ou les Mac. Sauf dans des scénarios très spécifiques, vous ne pouvez pas connecter un écran, un clavier et une souris pour les utiliser pour des tâches générales.

Les kits de développement de microcontrôleurs sont généralement équipés de capteurs et d'actionneurs supplémentaires intégrés. La plupart des cartes auront une ou plusieurs LED programmables, ainsi que d'autres dispositifs comme des connecteurs standard pour ajouter des capteurs ou actionneurs supplémentaires via divers écosystèmes de fabricants ou des capteurs intégrés (généralement les plus populaires, comme les capteurs de température). Certains microcontrôleurs disposent d'une connectivité sans fil intégrée, comme le Bluetooth ou le WiFi, ou possèdent des microcontrôleurs supplémentaires sur la carte pour ajouter cette connectivité.

> 💁 Les microcontrôleurs sont généralement programmés en C/C++.

### Ordinateurs monocartes

Un ordinateur monocarte est un petit dispositif informatique qui contient tous les éléments d'un ordinateur complet sur une seule carte. Ces appareils ont des spécifications proches d'un PC ou d'un Mac, exécutent un système d'exploitation complet, mais sont plus petits, consomment moins d'énergie et sont beaucoup moins chers.

![Un Raspberry Pi 4](../../../../../translated_images/fr/raspberry-pi-4.fd4590d308c3d456.webp)

Le Raspberry Pi est l'un des ordinateurs monocartes les plus populaires.

Comme un microcontrôleur, les ordinateurs monocartes ont un processeur, de la mémoire et des broches d'entrée/sortie, mais ils disposent de fonctionnalités supplémentaires comme une puce graphique pour connecter des écrans, des sorties audio et des ports USB pour connecter des claviers, des souris et d'autres périphériques USB standard comme des webcams ou des disques externes. Les programmes sont stockés sur des cartes SD ou des disques durs avec un système d'exploitation, au lieu d'une puce mémoire intégrée à la carte.

> 🎓 Vous pouvez considérer un ordinateur monocarte comme une version plus petite et moins chère du PC ou du Mac que vous utilisez actuellement, avec l'ajout de broches GPIO (entrée/sortie polyvalente) pour interagir avec des capteurs et des actionneurs.

Les ordinateurs monocartes sont des ordinateurs complets, ils peuvent donc être programmés dans n'importe quel langage. Les appareils IoT sont généralement programmés en Python.

### Choix du matériel pour les prochaines leçons

Toutes les leçons suivantes incluent des exercices utilisant un appareil IoT pour interagir avec le monde physique et communiquer avec le cloud. Chaque leçon prend en charge trois choix d'appareils : Arduino (en utilisant un Wio Terminal de Seeed Studios), ou un ordinateur monocarte, soit un appareil physique (un Raspberry Pi 4), soit un ordinateur monocarte virtuel fonctionnant sur votre PC ou Mac.

Vous pouvez consulter les besoins matériels pour réaliser tous les exercices dans le [guide matériel](../../../hardware.md).

> 💁 Vous n'avez pas besoin d'acheter de matériel IoT pour réaliser les exercices, vous pouvez tout faire en utilisant un ordinateur monocarte virtuel.

Le choix du matériel dépend de ce que vous avez à disposition chez vous ou dans votre école, et du langage de programmation que vous connaissez ou souhaitez apprendre. Les deux variantes matérielles utiliseront le même écosystème de capteurs, donc si vous commencez avec l'une, vous pourrez passer à l'autre sans avoir à remplacer la plupart des composants. L'ordinateur monocarte virtuel sera équivalent à un apprentissage sur un Raspberry Pi, avec la plupart du code transférable sur un Pi si vous en obtenez un plus tard.

### Kit de développement Arduino

Si vous souhaitez apprendre le développement de microcontrôleurs, vous pouvez réaliser les exercices avec un appareil Arduino. Vous aurez besoin d'une compréhension de base de la programmation en C/C++, car les leçons n'enseigneront que le code pertinent pour le framework Arduino, les capteurs et actionneurs utilisés, ainsi que les bibliothèques interagissant avec le cloud.

Les exercices utiliseront [Visual Studio Code](https://code.visualstudio.com/?WT.mc_id=academic-17441-jabenn) avec l'extension [PlatformIO pour le développement de microcontrôleurs](https://platformio.org). Vous pouvez également utiliser l'IDE Arduino si vous êtes déjà familier avec cet outil, mais des instructions ne seront pas fournies.

### Kit de développement pour ordinateur monocarte

Si vous souhaitez apprendre le développement IoT avec des ordinateurs monocartes, vous pouvez réaliser les exercices avec un Raspberry Pi ou un appareil virtuel fonctionnant sur votre PC ou Mac.

Vous aurez besoin d'une compréhension de base de la programmation en Python, car les leçons n'enseigneront que le code pertinent pour les capteurs et actionneurs utilisés, ainsi que les bibliothèques interagissant avec le cloud.

> 💁 Si vous souhaitez apprendre à coder en Python, consultez les deux séries vidéo suivantes :
>
> * [Python pour les débutants](https://channel9.msdn.com/Series/Intro-to-Python-Development?WT.mc_id=academic-17441-jabenn)
> * [Plus de Python pour les débutants](https://channel9.msdn.com/Series/More-Python-for-Beginners?WT.mc_id=academic-7372-jabenn)

Les exercices utiliseront [Visual Studio Code](https://code.visualstudio.com/?WT.mc_id=academic-17441-jabenn).

Si vous utilisez un Raspberry Pi, vous pouvez soit exécuter votre Pi avec la version complète de Raspberry Pi OS et coder directement dessus en utilisant [la version Raspberry Pi OS de VS Code](https://code.visualstudio.com/docs/setup/raspberry-pi?WT.mc_id=academic-17441-jabenn), soit utiliser votre Pi comme un appareil sans écran et coder depuis votre PC ou Mac en utilisant VS Code avec l'extension [Remote SSH](https://code.visualstudio.com/docs/remote/ssh?WT.mc_id=academic-17441-jabenn), qui vous permet de vous connecter à votre Pi et d'éditer, déboguer et exécuter du code comme si vous codiez directement dessus.

Si vous optez pour l'option virtuelle, vous coderez directement sur votre ordinateur. Au lieu d'accéder à des capteurs et actionneurs réels, vous utiliserez un outil pour simuler ce matériel, en définissant les valeurs des capteurs et en affichant les résultats des actionneurs à l'écran.

## Configurer votre appareil

Avant de commencer à programmer votre appareil IoT, vous devrez effectuer une petite configuration. Suivez les instructions pertinentes ci-dessous en fonction de l'appareil que vous utiliserez.
💁 Si vous n'avez pas encore d'appareil, consultez le [guide matériel](../../../hardware.md) pour vous aider à choisir l'appareil que vous allez utiliser et déterminer le matériel supplémentaire à acheter. Vous n'êtes pas obligé d'acheter du matériel, car tous les projets peuvent être exécutés sur du matériel virtuel.
Ces instructions incluent des liens vers des sites web tiers des créateurs du matériel ou des outils que vous utiliserez. Cela garantit que vous disposez toujours des instructions les plus récentes pour les différents outils et matériels.

Suivez le guide correspondant pour configurer votre appareil et réaliser un projet "Hello World". Ce sera la première étape pour créer une veilleuse IoT au cours des 4 leçons de cette partie d'introduction.

* [Arduino - Wio Terminal](wio-terminal.md)
* [Ordinateur monocarte - Raspberry Pi](pi.md)
* [Ordinateur monocarte - Appareil virtuel](virtual-device.md)

✅ Vous utiliserez VS Code à la fois pour Arduino et les ordinateurs monocartes. Si vous ne l'avez jamais utilisé auparavant, lisez-en davantage sur le [site de VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn).

## Applications de l'IoT

L'IoT couvre un large éventail de cas d'utilisation, répartis en quelques grandes catégories :

* IoT pour les consommateurs
* IoT commercial
* IoT industriel
* IoT pour les infrastructures

✅ Faites quelques recherches : Pour chacune des catégories décrites ci-dessous, trouvez un exemple concret qui n'est pas mentionné dans le texte.

### IoT pour les consommateurs

L'IoT pour les consommateurs désigne les appareils IoT que les particuliers achètent et utilisent à la maison. Certains de ces appareils sont incroyablement utiles, comme les enceintes intelligentes, les systèmes de chauffage intelligents et les aspirateurs robots. D'autres sont plus discutables quant à leur utilité, comme les robinets contrôlés par la voix qui deviennent inutilisables lorsque la commande vocale ne peut pas vous entendre à cause du bruit de l'eau qui coule.

Les appareils IoT pour les consommateurs permettent aux gens de faire plus dans leur environnement, en particulier pour le milliard de personnes vivant avec un handicap. Les aspirateurs robots peuvent offrir des sols propres aux personnes ayant des problèmes de mobilité qui ne peuvent pas passer l'aspirateur elles-mêmes, les fours contrôlés par la voix permettent aux personnes ayant une vision limitée ou des problèmes de motricité de chauffer leur four uniquement avec leur voix, et les moniteurs de santé permettent aux patients de surveiller eux-mêmes des maladies chroniques avec des mises à jour plus régulières et détaillées sur leur état. Ces appareils deviennent si omniprésents que même les jeunes enfants les utilisent dans leur vie quotidienne, par exemple, les élèves suivant des cours virtuels pendant la pandémie de COVID qui utilisent des minuteurs sur des appareils domestiques intelligents pour suivre leur travail scolaire ou des alarmes pour leur rappeler les réunions de classe à venir.

✅ Quels appareils IoT pour les consommateurs avez-vous sur vous ou chez vous ?

### IoT commercial

L'IoT commercial concerne l'utilisation de l'IoT sur le lieu de travail. Dans un bureau, il peut y avoir des capteurs de présence et des détecteurs de mouvement pour gérer l'éclairage et le chauffage, afin de n'allumer les lumières et le chauffage que lorsque c'est nécessaire, réduisant ainsi les coûts et les émissions de carbone. Dans une usine, les appareils IoT peuvent surveiller les dangers pour la sécurité, comme les travailleurs ne portant pas de casques ou les niveaux sonores devenant dangereux. Dans le commerce de détail, les appareils IoT peuvent mesurer la température des chambres froides, alertant le propriétaire du magasin si un réfrigérateur ou un congélateur dépasse la plage de température requise, ou surveiller les articles sur les étagères pour diriger les employés à réapprovisionner les produits vendus. L'industrie du transport s'appuie de plus en plus sur l'IoT pour surveiller la localisation des véhicules, suivre le kilométrage pour la tarification routière, vérifier la conformité des heures de conduite et des pauses, ou notifier le personnel lorsqu'un véhicule approche d'un dépôt pour préparer le chargement ou le déchargement.

✅ Quels appareils IoT commerciaux avez-vous dans votre école ou sur votre lieu de travail ?

### IoT industriel (IIoT)

L'IoT industriel, ou IIoT, désigne l'utilisation d'appareils IoT pour contrôler et gérer des machines à grande échelle. Cela couvre un large éventail de cas d'utilisation, allant des usines à l'agriculture numérique.

Les usines utilisent des appareils IoT de nombreuses manières différentes. Les machines peuvent être surveillées avec plusieurs capteurs pour suivre des paramètres tels que la température, les vibrations et la vitesse de rotation. Ces données peuvent ensuite être surveillées pour permettre l'arrêt de la machine si elle dépasse certaines tolérances - par exemple, si elle surchauffe, elle est arrêtée. Ces données peuvent également être collectées et analysées au fil du temps pour effectuer une maintenance prédictive, où des modèles d'IA examinent les données précédant une panne et les utilisent pour prédire d'autres pannes avant qu'elles ne se produisent.

L'agriculture numérique est essentielle pour nourrir une population mondiale croissante, en particulier pour les 2 milliards de personnes dans 500 millions de foyers qui vivent de [l'agriculture de subsistance](https://wikipedia.org/wiki/Subsistence_agriculture). L'agriculture numérique peut aller de capteurs coûtant quelques dollars à des installations commerciales massives. Un agriculteur peut commencer par surveiller les températures et utiliser les [degrés-jours de croissance](https://wikipedia.org/wiki/Growing_degree-day) pour prédire quand une culture sera prête à être récoltée. Il peut connecter des capteurs d'humidité du sol à des systèmes d'arrosage automatisés pour donner à ses plantes autant d'eau que nécessaire, mais pas plus, afin de s'assurer que ses cultures ne se dessèchent pas sans gaspiller d'eau. Certains agriculteurs vont encore plus loin en utilisant des drones, des données satellites et l'IA pour surveiller la croissance des cultures, les maladies et la qualité du sol sur de vastes zones agricoles.

✅ Quels autres appareils IoT pourraient aider les agriculteurs ?

### IoT pour les infrastructures

L'IoT pour les infrastructures consiste à surveiller et contrôler les infrastructures locales et mondiales que les gens utilisent au quotidien.

[Les villes intelligentes](https://wikipedia.org/wiki/Smart_city) sont des zones urbaines qui utilisent des appareils IoT pour collecter des données sur la ville et les utiliser pour améliorer son fonctionnement. Ces villes sont généralement gérées en collaboration entre les gouvernements locaux, les universités et les entreprises locales, en suivant et en gérant des aspects variés comme les transports, le stationnement et la pollution. Par exemple, à Copenhague, au Danemark, la pollution de l'air est importante pour les habitants locaux, elle est donc mesurée et les données sont utilisées pour fournir des informations sur les itinéraires de jogging et de vélo les plus propres.

[Les réseaux électriques intelligents](https://wikipedia.org/wiki/Smart_grid) permettent une meilleure analyse de la demande énergétique en collectant des données d'utilisation au niveau des foyers individuels. Ces données peuvent guider les décisions à l'échelle nationale, comme l'emplacement de nouvelles centrales électriques, et à l'échelle personnelle, en fournissant aux utilisateurs des informations sur leur consommation d'énergie, les moments où ils consomment le plus, et même des suggestions pour réduire les coûts, comme recharger les voitures électriques la nuit.

✅ Si vous pouviez ajouter des appareils IoT pour mesurer quelque chose là où vous vivez, que mesureriez-vous ?

## Exemples d'appareils IoT que vous pourriez avoir autour de vous

Vous seriez surpris de voir combien d'appareils IoT vous entourent. J'écris ceci depuis chez moi et j'ai les appareils suivants connectés à Internet avec des fonctionnalités intelligentes telles que le contrôle via une application, le contrôle vocal ou la capacité d'envoyer des données sur mon téléphone :

* Plusieurs enceintes intelligentes
* Réfrigérateur, lave-vaisselle, four et micro-ondes
* Moniteur d'électricité pour panneaux solaires
* Prises intelligentes
* Sonnette vidéo et caméras de sécurité
* Thermostat intelligent avec plusieurs capteurs intelligents pour les pièces
* Ouvre-porte de garage
* Systèmes de divertissement à domicile et téléviseurs contrôlés par la voix
* Éclairages
* Traqueurs de fitness et de santé

Tous ces types d'appareils ont des capteurs et/ou des actionneurs et communiquent avec Internet. Je peux savoir depuis mon téléphone si ma porte de garage est ouverte et demander à mon enceinte intelligente de la fermer pour moi. Je peux même la programmer pour qu'elle se ferme automatiquement si elle est encore ouverte la nuit. Quand ma sonnette retentit, je peux voir depuis mon téléphone qui est là, où que je sois dans le monde, et leur parler via un haut-parleur et un microphone intégrés à la sonnette. Je peux surveiller ma glycémie, mon rythme cardiaque et mes cycles de sommeil, en recherchant des tendances dans les données pour améliorer ma santé. Je peux contrôler mes lumières via le cloud et rester dans le noir lorsque ma connexion Internet tombe en panne.

---

## 🚀 Défi

Listez autant d'appareils IoT que vous pouvez trouver chez vous, à l'école ou sur votre lieu de travail - il y en a peut-être plus que vous ne le pensez !

## Quiz post-cours

[Quiz post-cours](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/2)

## Révision et auto-apprentissage

Renseignez-vous sur les avantages et les échecs des projets IoT pour les consommateurs. Consultez les sites d'actualités pour des articles sur les moments où cela a mal tourné, comme des problèmes de confidentialité, des problèmes matériels ou des problèmes causés par un manque de connectivité.

Quelques exemples :

* Consultez le compte Twitter **[Internet of Sh*t](https://twitter.com/internetofshit)** *(avertissement : langage grossier)* pour de bons exemples d'échecs liés à l'IoT pour les consommateurs.
* [c|net - Mon Apple Watch m'a sauvé la vie : 5 personnes partagent leurs histoires](https://www.cnet.com/news/apple-watch-lifesaving-health-features-read-5-peoples-stories/)
* [c|net - Un technicien ADT plaide coupable d'avoir espionné les flux des caméras des clients pendant des années](https://www.cnet.com/news/adt-home-security-technician-pleads-guilty-to-spying-on-customer-camera-feeds-for-years/) *(avertissement : voyeurisme non consenti)*

## Devoir

[Enquêtez sur un projet IoT](assignment.md)

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.