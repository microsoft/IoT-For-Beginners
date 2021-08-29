# Introduction au IoT

![Voici un aperçu de cette leçon sous forme d'illustré](../../../../sketchnotes/lesson-1.jpg)

> Illustré par [Nitya Narasimhan](https://github.com/nitya). Cliquer sur l'image pour l'agrandir.

Cette leçon a été enseigné dans le cadre de [Hello IoT series](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) à partir de [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). Cette leçon a été enseigné en 2 vidéos - une leçon d'une heure et une autre heure pour approfondir les notions et répondre aux questions.

[![Leçon 1: Introduction aux IoT](https://img.youtube.com/vi/bVFfcYh6UBw/0.jpg)](https://youtu.be/bVFfcYh6UBw)

[![Leçon 1: Introduction aux IoT - Heures de bureau](https://img.youtube.com/vi/YI772q5v3yI/0.jpg)](https://youtu.be/YI772q5v3yI)

> 🎥 Cliquer sur les images ci-dessus pour regarder les vidéos.

## Questionnaire de pré-lecture

[Questionnaire de pré-lecture](https://brave-island-0b7c7f50f.azurestaticapps.net/quiz/1)

## Introduction

Cette leçon couvre certains sujets d'introduction à l'Internet des objets et vous permet de configure votre matériel.

Dans cette leçon nous couvrirons:

* [Qu'est-ce que l'Internet des objets?](#what-is-the-internet-of-things)
* [Appareils IoT](#iot-devices)
* [Configurer votre appareil](#set-up-your-device)
* [Les applications IoT](#applications-of-iot)
* [Exemples d'appareils IoT près de vous](#examples-of-iot-devices-you-may-have-around-you)

## Qu'est-ce que l'Internet des objets?

Le terme « Internet des objets » a été créer par [Kevin Ashton](https://wikipedia.org/wiki/Kevin_Ashton) en 1999 pour imager la connection entre le monde physique et l'Internet via des capteurs. Depuis, le terme est utilisé pour décrire n'importe quel appareil qui intéragit avec le monde physique alentour, soit en collectant des données via des capteurs ou en intéragissant avec le monde réel via des actionneurs (appareils qui ouvre un interrupteur ou allume un DEL), généralement connecté à d'autres appareils ou Internet.

> **Capteurs** collecte l'information du monde réel, tel que la vitesse, la température ou la localisation.
>
> **Actionneurs** convertit un signal électrique en interagissant avec le monde réel en déclencheant un interrupteur, allumant une DEL, jouant un son ou en envoyant un signal à un autre appareil, par exemple pour allimenter une prise de courant.

Les IoT en tant que domaine technologique ne se limite pas seulement aux appareils: il comprend des services basé sur les technologies infonuagique qui traite les données collecté par le capteur ou envoie une requête aux actionneurs connectés aux appareils IoT. Ce domaine inclut aussi des appareils n'ayant pas de connectivité Internet ou qui n'en ont pas besoin, souvent référé en tant qu'appareils de périphérie. Ces appareils sont en mesure de répondre et traiter les données collectés par les capteurs eux-mêmes, généralement à l'aide de modèle d'AI créé dans l'infrastrucutre infonuagique.

Le domaine des IoT est en pleine expansion. On estime qu'à la fin de 2020, 30 milliards de dispositifs IoT ont été déployés et connectés à Internet. Dans l'avenir, on estime que les appareils IoT collecteront près de 80 zettaoctets de données, soit 80 trillions de gigaoctets. C'est beaucoup de données!

![Voici un graphique montrant les objets connecté dans le temps, avec une tendance à la hausse passant de moins de 5 millairds en 2015 à plus de 30 milliards en 2025](../../../../images/connected-iot-devices.svg)

✅ Faites une petite recherche: Quel proportion des données générés par les objets connectés sont utilisé et quel proportion est gaspillé? Pourquoi y a-t-il autant de données ignorés?

Ces données sont la clé du succès des IoT. Pour être un développeur IoT à succès, il faut comprenedre quel données vous devez collecter, comment les collecter, comment prendre une décision par rapport à ces données et comment utiliser ces décision pour intéragir avec le monde physique au besoin.

## Appareils IoT

Le **T** dans IoT tiens pour **Things**- objet qui intéragit avec le monde physique soit en collectant des données des capteurs ou en intéragissant avec le monde réel via des actionneurs.

Les appareils destinés à la production ou à l'utilisation commercial tel que les dispositifs de suivi du conditionnment physique sont généralement fait sur mesure. Ils utilisent des circuits imprimés fait sur mesure, parfois même avec des processeurs fait sur mesure conçu pour rencontrés les spécificités d'une tâche particulière, qu'il s'agisse d'être suffisamment petit pour ttenir au poignet ou suffisamment robuste pour travailler dans de haute température, à forte contrainte ou à fortes vibrations.

<!--As a developer either learning about IoT or creating a device prototype, you'll need to start with a developer kit. These are general-purpose IoT devices designed for developers to use, often with features that you wouldn't have on a production device, such as a set of external pins to connect sensors or actuators to, hardware to support debugging, or additional resources that would add unnecessary cost when doing a large manufacturing run.-->
En tant que développeur, que vous soyez en train d'apprendre au sujet des objets connectés ou que soyez en train de créer un prototype, vous devez commencer avec un ensemble de développeur. Il s'agit d'appareils IoT à usage général conçus pour être utilisés par les développeurs, souvent dotés de fonctionnalités que vous n'auriez pas sur un appareil de production, telles qu'un ensemble de broches externes auxquelles connecter des capteurs ou des actionneurs, du matériel pour prendre en charge le débogage ou des ressources supplémentaires qui ajouteraient des coûts inutiles lors d'une grande production.

Ces ensembles de développement se divisent généralement en deux catégories : les microcontrôleurs et les ordinateurs monocartes. Ces derniers seront présentés ici, et nous entrerons dans les détails dans la prochaine leçon.

> 💁 Votre téléphone peut également être considéré comme un dispositif IoT polyvalent, avec des capteurs et des actionneurs intégrés, différentes applications utilisant les capteurs et les actionneurs de différentes manières avec différents services infonuagiques. Vous pouvez même trouver des tutoriels sur l'IoT qui utilisent une application de téléphone comme dispositif IoT.

### Microcontrôleurs

Un microcontrôleur (également appelé MCU, abréviation de "microcontroller unit") est un petit ordinateur composé de:

🧠 Une ou plusieurs unités centrales de traitement (CPU) - le "cerveau" du microcontrôleur qui exécute votre programme.

💾 Mémoire (RAM et mémoire de programme) - où sont stockés votre programme, vos données et vos variables.

🔌 Connexions d'entrée/sortie (E/S) programmables - pour communiquer avec des périphériques externes (objets connectés) tels que des capteurs et des actionneurs.

Les microcontrôleurs sont généralement des dispositifs informatiques peu coûteux, le prix moyen des microcontrôleurs utilisés dans le matériel personnalisé se situant autour de $0,50 USD, et certains dispositifs ne coûtant que $0,03 USD. Les kits de développement peuvent commencer à partir de $4 USD, les coûts augmentant au fur et à mesure que l'on ajoute des fonctionnalités. Le [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html), un ensemble de développement de microcontrôleur de [Seeed studios](https://www.seeedstudio.com) qui comprend des capteurs, des actionneurs, le WiFi et un écran, coûte environ $30 USD.

![Voici un Terminal Wio](../../../../images/wio-terminal.png)

> 💁 Lorsque vous recherchez des microcontrôleurs sur Internet, méfiez-vous de la recherche contenant le terme **MCU**, car vous obtiendrez de nombreux résultats concernant le Marvel Cinematic Universe, et non les microcontrôleurs.

Les microcontrôleurs sont conçus pour être programmés afin d'effectuer un nombre limité de tâches très spécifiques, plutôt que d'être des ordinateurs à usage général comme les PC ou les Mac. À l'exception de scénarios très spécifiques, vous ne pouvez pas connecter un écran, un clavier et une souris et les utiliser pour des tâches générales.

Les ensemble de développement de microcontrôleurs sont généralement livrés avec des capteurs et des actionneurs supplémentaires à bord. La plupart des cartes sont dotés d'une ou plusieurs DEL que vous pouvez programmer, ainsi que d'autres dispositifs tels que des connecteurs standard permettant d'ajouter d'autres capteurs ou actionneurs à l'aide d'écosystèmes de divers fabricants ou de capteurs intégrés (généralement les plus populaires comme les capteurs de température). Certains microcontrôleurs ont une connectivité sans fil intégrée, comme Bluetooth ou WiFi, ou ont des microcontrôleurs supplémentaires sur la carte pour ajouter cette connectivité.

> 💁 Les microcontrôleurs sont généralement programmé en C/C++.

### Ordinateur monocarte

<!--A single-board computer is a small computing device that has all the elements of a complete computer contained on a single small board. These are devices that have specifications close to a desktop or laptop PC or Mac, run a full operating system, but are small, use less power, and are substantially cheaper.-->
Un ordinateur monocarte est un petit ordinateur qui possède tous les éléments d'un ordinateur complet contenue dans un ordinateur de la grosseur d'une carte de crédit. Ces appareils, qui ont des spécifications similaires à celles d'un ordinateur de bureau ou d'un ordinateur portable Pc ou Mac, mais sont plus petit et utilisent moins de puissance en plus d'être substantiellement moins dispendieux.

![Voici un Raspberry Pi 4](../../../../images/raspberry-pi-4.jpg)

<!--The Raspberry Pi is one of the most popular single-board computers.-->
Le Raspberry Pi est un des ordinateurs monocarte les plus populaires.

<!-- Like a microcontroller, single-board computers have a CPU, memory and input/output pins, but they have additional features such as a graphics chip to allow you to connect monitors, audio outputs, and USB ports to connect keyboards mice and other standard USB devices like webcams or external storage. Programs are stored on SD cards or hard drives along with an operating system, instead of a memory chip built into the board. -->
Comme un microcontrôleur, les ordinateurs monocartes disposent d'une unité centrale, d'une mémoire et de broches d'entrée/sortie, mais ils possèdent des fonctionnalités supplémentaires telles qu'une puce graphique pour vous permettre de connecter des moniteurs, des sorties audio et des ports USB pour connecter des claviers, des souris et d'autres périphériques USB standard tels que des webcams ou un stockage externe. Les programmes sont stockés sur des cartes SD ou des disques durs avec un système d'exploitation, au lieu d'une puce mémoire intégrée à la carte.

> 🎓 Vous pouvez considérer un ordinateur monocarte comme une version plus petite et moins chère du PC ou du Mac sur lequel vous lisez ces lignes, avec l'ajout de broches GPIO (entrées/sorties à usage général) pour interagir avec des capteurs et des actionneurs.

Les ordinateurs monocartes sont des ordinateurs complets, qui peuvent donc être programmés dans n'importe quel langage. Les appareils IoT sont généralement programmés en Python.

### Choix de matériel pour le reste de la leçon

Toutes les leçons suivantes comprennent des tâches utilisant un dispositif IoT pour interagir avec le monde physique et communiquer avec le cloud. Chaque leçon prend en charge 3 choix de dispositifs - Arduino (à l'aide d'un terminal Wio de Seeed Studios), ou un ordinateur monocarte, soit un dispositif physique (un Raspberry Pi 4), soit un ordinateur monocarte virtuel fonctionnant sur votre PC ou Mac.

Vous pouvez vous renseigner sur le matériel nécessaire à la réalisation de toutes les missions dans le [guide matériel](../../../../hardware.md).

> 💁 Vous n'avez pas besoin d'acheter aucun matériel IoT pour compléter les tâches, vous pouvez utiliser un ordinateur monocarte virtuel.

Le matériel que vous choisissez dépend de ce que vous avez à votre disposition à la maison ou à l'école, et du langage de programmation que vous connaissez ou que vous envisagez d'apprendre. Les deux variantes matérielles utiliseront le même écosystème de capteurs, de sorte que si vous vous engagez dans une voie, vous pourrez passer à l'autre sans devoir remplacer la majeure partie de l'ensemble. L'ordinateur monocarte virtuel sera l'équivalent de l'apprentissage sur un Raspberry Pi, la plupart du code pouvant être transféré sur le Pi si vous obtenez finalement un dispositif et des capteurs.

### Ensemble de développement Arduino

<!-- If you are interested in learning microcontroller development, you can complete the assignments using an Arduino device. You will need a basic understanding of C/C++ programming, as the lessons will only teach code that is relevant to the Arduino framework, the sensors and actuators being used, and the libraries that interact with the cloud. -->
Si vous souhaitez apprendre le développement de microcontrôleurs, vous pouvez effectuer les tâches à l'aide d'un dispositif Arduino. Vous aurez besoin d'une compréhension de base de la programmation C/C++, car les leçons n'enseignent que le code qui est pertinent pour le cadre Arduino, les capteurs et les actionneurs utilisés, et les bibliothèques qui interagissent avec l'infrastructure infonuagique.

Les tâches utiliseront [Visual Studio Code](https://code.visualstudio.com/?WT.mc_id=academic-17441-jabenn) avec l'[extension PlatformIO pour le développement sur microcontrôleur](https://platformio.org). Vous pouvez aussi utiliser l'IDE Arduino si vous avez de l'expérience avec cet outil, car les instructions ne seront pas fournies.

### Ensemble de développement pour ordinateur monocarte

Si vous souhaitez apprendre le développement IoT à l'aide d'ordinateurs monocartes, vous pouvez réaliser les tâches à l'aide d'un Raspberry Pi, ou d'un dispositif virtuel fonctionnant sur votre PC ou votre Mac.

Vous devrez avoir des connaissances de base en programmation Python, car les leçons n'enseignent que le code pertinent pour les capteurs et les actionneurs utilisés, ainsi que les bibliothèques qui interagissent avec l'infrastructure infonuagique.

> 💁 Si vous souhaitez apprendre à coder en Python, consultez les deux séries de vidéos suivantes:
>
> * [Python pour débutant](https://channel9.msdn.com/Series/Intro-to-Python-Development?WT.mc_id=academic-17441-jabenn)
> * [Plus de python pour débutant](https://channel9.msdn.com/Series/More-Python-for-Beginners?WT.mc_id=academic-7372-jabenn)

Les tâches vont utiliser [Visual Studio Code](https://code.visualstudio.com/?WT.mc_id=academic-17441-jabenn).

Si vous utilisez un Raspberry Pi, vous pouvez soit faire fonctionner votre Pi en utilisant la version de bureau complète de Raspberry Pi OS, et faire tout le codage directement sur le Pi en utilisant [La version Raspberry Pi OS de Visual Studio Code](https://code.visualstudio.com/docs/setup/raspberry-pi?WT.mc_id=academic-17441-jabenn), ou faire fonctionner votre Pi comme un appareil sans tête et coder à partir de votre PC ou Mac en utilisant VS Code avec l'application [Extension SSH à distance](https://code.visualstudio.com/docs/remote/ssh?WT.mc_id=academic-17441-jabenn) qui vous permet de vous connecter à votre Pi et de modifier, déboguer et exécuter du code comme si vous codiez directement sur lui.

If you use the virtual device option, you will code directly on your computer. Instead of accessing sensors and actuators, you will use a tool to simulate this hardware providing sensor values that you can define, and showing the results of actuators on screen.

## Configurer votre dispositif

Avant de pouvoir commencer à programmer votre appareil IoT, vous devez effectuer une petite configuration. Suivez les instructions ci-dessous en fonction de l'appareil que vous utiliserez.

> 💁 Si vous n'avez pas encore d'appareil, référez-vous au [guide matériel](../../../../hardware.md) pour vous aider à choisir le dispositif que vous allez utiliser et du matériel supplémentaire que vous devez acheter. Vous n'avez pas besoin d'acheter du matériel, car tous les projets peuvent être exécutés sur du matériel virtuel.

Ces instructions comprennent des liens vers des sites Web tierce partie créés par les créateurs du matériel ou des outils que vous utiliserez. Cela permet de s'assurer que vous utilisez toujours les instructions les plus récentes pour les différents outils et matériels.

Utilisez le guide correspondant pour configurer votre appareil et réaliser un projet «Hello World». Ce sera la première étape de la création d'une veilleuse IoT au cours des 4 leçons de cette partie de mise en route.

* [Arduino - Wio Terminal](wio-terminal.md)
* [Ordinateur monocarte - Raspberry Pi](pi.md)
* [Ordinateur moncarte - Dispositif virtuel](virtual-device.md)

✅ Vous utiliserez VS Code pour les ordinateurs Arduino et Single-board. Si vous ne l'avez jamais utilisé auparavant, vous pouvez en apprendre davantage sur le [site Vs Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn)

## Applications IoT

L'internet des objets couvrent une grande partie des cas d'utilisation répartis en quelques grands groupes:

* IoT grand public
* IoT commercial
* IoT industriel
* IoT d'infrastructure

✅ Faites une petite recherche : Pour chacun des domaines décrits ci-dessous, trouvez un exemple concret qui n'est pas donné dans le texte.

### IoT grand public

Le terme IoT grand public fait référence aux appareils IoT que les consommateurs achèteront et utiliseront à la maison. Certains de ces appareils sont incroyablement utiles, comme les haut-parleurs intelligents, les systèmes de chauffage intelligents et les aspirateurs robotisés. D'autres sont d'une utilité discutable, comme les robinets à commande vocale qui ne peuvent pas être éteints car la commande vocale ne peut pas vous entendre par-dessus le bruit de l'eau qui coule.

Les dispositifs IoT grand public donnent aux gens les moyens d'en faire plus dans leur environnement, en particulier au milliard de personnes qui souffrent d'un handicap. Les aspirateurs robotisés peuvent fournir des sols propres aux personnes ayant des problèmes de mobilité qui ne peuvent pas passer l'aspirateur elles-mêmes, les fours à commande vocale permettent aux personnes ayant une vision ou un contrôle moteur limité de chauffer leurs fours avec leur seule voix, les moniteurs de santé peuvent permettre aux patients de surveiller eux-mêmes leurs maladies chroniques avec des mises à jour plus régulières et plus détaillées sur leur état. Ces appareils deviennent tellement omniprésents que même les jeunes enfants les utilisent dans leur vie quotidienne. Par exemple, les étudiants qui suivent une scolarité virtuelle pendant la pandémie de COVID règlent des minuteries sur des appareils domestiques intelligents pour suivre leurs travaux scolaires ou des alarmes pour leur rappeler les prochaines réunions de classe.

✅ Quels sont les dispositifs IoT grand public que vous avez sur vous ou dans votre maison ?

### Commercial IoT

L'IoT commercial couvre l'utilisation de l'IoT sur le lieu de travail. Dans un bureau, il peut y avoir des capteurs d'occupation et des détecteurs de mouvement pour gérer l'éclairage et le chauffage afin de ne les laisser éteints que lorsqu'ils ne sont pas nécessaires, ce qui réduit les coûts et les émissions de carbone. Dans une usine, les dispositifs IoT peuvent surveiller les risques pour la sécurité, comme les travailleurs qui ne portent pas de casque de sécurité ou le bruit qui a atteint des niveaux dangereux. Dans le commerce de détail, les dispositifs IoT peuvent mesurer la température des chambres froides, alertant le propriétaire du magasin si un réfrigérateur ou un congélateur se trouve en dehors de la plage de température requise, ou ils peuvent surveiller les articles en rayon pour indiquer aux employés de réapprovisionner les produits qui ont été vendus. Le secteur des transports s'appuie de plus en plus sur l'Internet des objets pour surveiller l'emplacement des véhicules, suivre le kilométrage sur route pour la tarification des usagers de la route, suivre les heures de conduite et le respect des pauses, ou avertir le personnel lorsqu'un véhicule s'approche d'un dépôt pour préparer le chargement ou le déchargement.

✅ Quels dispositifs commerciaux IoT avez-vous dans votre école ou sur votre lieu de travail ?

### IoT industriel (IIoT)

L'Internet des objets industriel, ou IIoT, est l'utilisation de dispositifs IoT pour contrôler et gérer des machines à grande échelle. Cela couvre un large éventail de cas d'utilisation, des usines à l'agriculture numérique.

Les usines utilisent les dispositifs IoT de nombreuses façons différentes. Les machines peuvent être surveillées à l'aide de plusieurs capteurs pour suivre des éléments comme la température, les vibrations et la vitesse de rotation. Ces données peuvent ensuite être surveillées pour permettre d'arrêter la machine si elle sort de certaines tolérances - elle fonctionne trop chaudement et est arrêtée par exemple. Ces données peuvent également être recueillies et analysées au fil du temps pour effectuer une maintenance prédictive, où les modèles d'IA examinent les données qui ont conduit à une panne et s'en servent pour prédire d'autres pannes avant qu'elles ne se produisent.

L'agriculture numérique est importante si l'on veut que la planète nourrisse la population croissante, en particulier pour les 2 milliards de personnes dans 500 millions de ménages qui survivent grâce à [l'agriculture de subsistance](https://wikipedia.org/wiki/Subsistence_agriculture). L'agriculture numérique peut aller de quelques capteurs sous les 10$ à des installations commerciales massives. Un agriculteur peut commencer par surveiller les températures et utiliser [jours de croissance](https://wikipedia.org/wiki/Growing_degree-day) pour prévoir quand une culture sera prête à être récoltée. Ils peuvent connecter la surveillance de l'humidité du sol à des systèmes d'arrosage automatisés pour donner à leurs plantes autant d'eau que nécessaire, mais pas plus, afin de s'assurer que leurs cultures ne se dessèchent pas sans gaspiller d'eau. Les agriculteurs vont même plus loin et utilisent des drones, des données satellitaires et l'IA pour surveiller la croissance des cultures, les maladies et la qualité des sols sur d'immenses étendues de terres agricoles.

✅ Quels autres dispositifs IoT pourraient aider les agriculteurs ?

### IoT d'infrastructure

L'IoT des infrastructures consiste à surveiller et à contrôler les infrastructures locales et mondiales que les gens utilisent tous les jours.

[Les villes connectées](https://wikipedia.org/wiki/Smart_city) sont des zones urbaines qui utilisent des dispositifs IoT pour recueillir des données sur la ville et les utiliser pour améliorer son fonctionnement. Ces villes sont généralement gérées par des collaborations entre les autorités locales, les universités et les entreprises locales, qui suivent et gèrent des éléments allant du transport au stationnement et à la pollution. Par exemple, à Copenhague, au Danemark, la pollution atmosphérique est importante pour les habitants. Elle est donc mesurée et les données sont utilisées pour fournir des informations sur les itinéraires de cyclisme et de jogging les plus propres.

[Les réseaux électriques intelligents](https://wikipedia.org/wiki/Smart_grid) permettent une meilleure analyse de la demande d'électricité en recueillant des données d'utilisation au niveau des foyers individuels. Ces données peuvent guider les décisions au niveau national, notamment en ce qui concerne la construction de nouvelles centrales électriques, et au niveau personnel en donnant aux utilisateurs un aperçu de la quantité d'énergie qu'ils consomment, du moment où ils la consomment, et même des suggestions sur la manière de réduire les coûts, par exemple en chargeant les voitures électriques la nuit.

✅ Si vous pouviez ajouter des dispositifs IoT pour mesurer quelque chose là où vous vivez, ce serait quoi ?

## Exemples de dispositifs IoT que vous pouvez avoir autour de vous

Vous seriez surpris du nombre d'appareils IoT que vous avez autour de vous. J'écris ces lignes depuis chez moi et j'ai les appareils suivants connectés à Internet et dotés de fonctionnalités intelligentes telles que le contrôle des applications, le contrôle vocal ou la possibilité de m'envoyer des données via mon téléphone :

* Plusieurs haut-parleurs intelligents
* Réfrigérateur, lave-vaisselle, four et micro-onde
* Moniteur d'électricité pour panneaux solaires
* Prises intelligentes
* Sonnette vidéo et caméras de sécurité
* Thermostat intelligent avec plusieurs capteurs d'ambiance intelligents
* Contrôleur de portes de garage
* Systèmes de divertissement à domicile et téléviseurs à commande vocale
* Lumières
* Suivi de conditionnement physique

Tous ces types d'appareils sont dotés de capteurs et/ou d'actionneurs et communiquent avec l'Internet. Je peux dire depuis mon téléphone si ma porte de garage est ouverte, et demander à mon enceinte intelligente de la fermer pour moi. Je peux même la programmer pour que, si elle est encore ouverte la nuit, elle se ferme automatiquement. Lorsque ma sonnette sonne, je peux voir depuis mon téléphone qui est là, où que je sois dans le monde, et lui parler via un haut-parleur et un microphone intégrés à la sonnette. Je peux surveiller ma glycémie, mon rythme cardiaque et mes habitudes de sommeil, en recherchant des modèles dans les données pour améliorer ma santé. Je peux contrôler mes lumières via l'infrastructure infonuagique, et rester dans le noir lorsque ma connexion Internet est coupée.

---

## 🚀 Défi

Dressez la liste du plus grand nombre possible de dispositifs IoT présents chez vous, à l'école ou sur votre lieu de travail - il y en a peut-être plus que vous ne le pensez !

## Questionnaire suivant la lecture

[Questionnaire suivant la lecture](https://brave-island-0b7c7f50f.azurestaticapps.net/quiz/2)

## Révision et études personnelles

Renseignez-vous sur les avantages et les défauts des projets IoT grand public. Consultez les sites d'actualités pour trouver des articles sur les cas où cela a mal tourné, comme les problèmes de confidentialité, les problèmes de matériel ou les problèmes causés par le manque de connectivité.

Quelques exemples:

* Consultez le compte Twitter **[Internet of Sh*t](https://twitter.com/internetofshit)** *(profanity warning)* pour quelques bons exemples d'échec de dispositif IoT.
* [c|net - My Apple Watch saved my life: 5 people share their stories](https://www.cnet.com/news/apple-watch-lifesaving-health-features-read-5-peoples-stories/)
* [c|net - ADT technician pleads guilty to spying on customer camera feeds for years](https://www.cnet.com/news/adt-home-security-technician-pleads-guilty-to-spying-on-customer-camera-feeds-for-years/) *(trigger warning - non-consensual voyeurism)*

## Tâche

[Rechercher un projet IoT](assignment.md)
