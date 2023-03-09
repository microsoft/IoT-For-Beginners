# Une meilleure immersion dans l'IoT

![Un aperçu de cette leçon sous forme de sketch](../../../../sketchnotes/lesson-2.jpg)

> Sketchnote par [Nitya Narasimhan](https://github.com/nitya). Cliquez sur l'image pour l'agrandir.

Cette leçon a été dispensée dans le cadre de la [série Hello IoT](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) de [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). La leçon a été dispensée sous forme de deux vidéos - une leçon d'une heure et une heure aux heures de bureau pour approfondir certaines parties de la leçon et répondre aux questions.

[![Leçon 2 : Une meilleure immersion dans l'IoT](https://img.youtube.com/vi/t0SySWw3z9M/0.jpg)](https://youtu.be/t0SySWw3z9M)

[![Leçon 2 : Une meilleure immersion dans l'IoT - Heures de bureau](https://img.youtube.com/vi/tTZYf9EST1E/0.jpg)](https://youtu.be/tTZYf9EST1E)

> 🎥 Cliquez sur les images ci-dessus pour regarder les vidéos

## Quiz préalable

[Quiz préalable](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/3)

## Introduction

Cette leçon approfondit certains des concepts abordés dans la dernière leçon.

Dans cette leçon, nous couvrirons :

* [Les composants d'une application IoT](#les-composants-d'une-application-iot)
* [Approfondissement des microcontrôleurs](#approfondissement-des-microcontrôleurs)
* [Approfondissement des ordinateurs monocartes](#approfondissement-des-ordinateurs-monocartes)

## Les composants d'une application IoT

Les deux composants d'une application IoT sont l' *Internet* et l' *objet* (the thing). Examinons ces deux composants de manière un peu plus détaillée.

### L'objet (The Thing)

![Une Raspberry Pi 4](../../../../images/raspberry-pi-4.jpg)

La partie **Objet** (**Thing** en anglais) de l'IOT (Internet Of Thing) fait référence à un dispositif qui peut interagir avec le monde physique. Ces appareils sont généralement des ordinateurs de petite taille, peu coûteux, fonctionnant à faible vitesse et consommant peu d'énergie - par exemple, de simples microcontrôleurs dotés de kilooctets de RAM (par opposition aux gigaoctets d'un PC) et fonctionnant à seulement quelques centaines de mégahertz (par opposition aux gigahertz d'un PC), mais consommant parfois si peu d'énergie qu'ils peuvent fonctionner pendant des semaines, des mois, voire des années sur des piles.

Ces dispositifs interagissent avec le monde physique, soit en utilisant des capteurs pour recueillir des données sur leur environnement, soit en contrôlant des sorties ou des actionneurs pour apporter des changements physiques. L'exemple type est celui du thermostat intelligent, un appareil doté d'un capteur de température, d'un moyen de régler la température souhaitée (cadran ou écran tactile) et d'une connexion à un système de chauffage ou de refroidissement qui peut être activé lorsque la température détectée est en dehors de la plage souhaitée. Le capteur de température détecte que la pièce est trop froide et un actionneur met le chauffage en marche.

![Un diagramme montrant la température et un cadran comme entrées d'un dispositif IoT, et le contrôle d'un appareil de chauffage comme sortie.](../../../../images/basic-thermostat.png)

Il existe un large éventail d'objets différents qui peuvent agir comme des dispositifs IoT, du matériel dédié qui détecte une seule chose, aux appareils à usage général, même votre smartphone ! Un smartphone peut utiliser des capteurs pour détecter le monde qui l'entoure et des actionneurs pour interagir avec ce monde, par exemple en utilisant un capteur GPS pour détecter votre position et un haut-parleur pour vous donner des instructions de navigation vers une destination.

✅ Pensez à d'autres systèmes que vous avez autour de vous et qui lisent les données d'un capteur et les utilisent pour prendre des décisions. Un exemple serait le thermostat d'un four. Pouvez-vous en trouver d'autres ?

### L'Internet

Le côté **Internet** d'une application IoT (Internet Of Thing) se compose d'applications auxquelles le dispositif IoT peut se connecter pour envoyer et recevoir des données, ainsi que d'autres applications qui peuvent traiter les données du dispositif IoT et aider à prendre des décisions sur les demandes à envoyer aux actionneurs du dispositif IoT.

Une configuration typique consisterait à avoir une sorte de service cloud auquel le dispositif IoT se connecte, et ce service cloud gèrerait des aspect comme la sécurité, ainsi que la réception et le renvoi de messages au dispositif IoT. Ce service cloud se connecte ensuite à d'autres applications qui peuvent traiter ou stocker les données des capteurs, ou utiliser ces données avec celles d'autres systèmes pour prendre des décisions.

Par ailleurs, les appareils ne se connectent pas toujours directement à l'internet via des connexions WiFi ou filaires. Certains appareils utilisent un réseau maillé pour communiquer entre eux par le biais de technologies telles que le Bluetooth, en se connectant via un hub qui dispose d'une connexion Internet.

Dans l'exemple d'un thermostat intelligent, le thermostat se connecterait via le WiFi domestique à un service en nuage s'éxecutant dans le cloud. Il enverrait les données de température à ce service en nuage, et de là, elles seraient écrites dans une sorte de base de données permettant au propriétaire de vérifier les températures actuelles et passées à l'aide d'une application téléphonique. Un autre service cloud saura quelle température le propriétaire souhaite et enverra des messages à l'appareil IoT via le service cloud pour demander au système de chauffage de s'allumer ou de s'éteindre.

![Un diagramme montrant la température et un cadran comme entrées d'un dispositif IoT, le dispositif IoT avec une communication bidirectionnelle vers le cloud, qui à son tour a une communication bidirectionnelle vers un téléphone, et le contrôle d'un chauffage comme sortie du dispositif IoT.](../../../../images/mobile-controlled-thermostat.png)

Une version encore plus intelligente pourrait utiliser l'IA dans le cloud avec des données provenant d'autres capteurs connectés à d'autres appareils IoT, tels que des capteurs d'occupation qui détectent quelles pièces sont utilisées, ainsi que des données telles que la météo et même votre calendrier, pour prendre des décisions sur la façon de régler la température de manière intelligente. Par exemple, il pourrait éteindre votre chauffage s'il lit dans votre calendrier que vous êtes en vacances, ou éteindre le chauffage pièce par pièce en fonction des pièces que vous utilisez, apprenant des données pour être de plus en plus précis au fil du temps.

![Un diagramme montrant plusieurs capteurs de température et un cadran comme entrées d'un dispositif IoT, un dispositif IoT avec une communication bidirectionnelle vers le cloud, qui à son tour a une communication bidirectionnelle vers un téléphone, un calendrier et un service météorologique, et la commande d'un chauffage comme sortie du dispositif IoT.](../../../../images/smarter-thermostat.png)

✅ Quelles autres données pourraient contribuer à rendre un thermostat connecté à Internet plus intelligent ?

### IoT on the Edge

Bien que le "I" dans IoT soit l'abréviation d'Internet, ces dispositifs n'ont pas besoin de se connecter à l'Internet. Dans certains cas, les appareils peuvent se connecter à des appareils 'périphériques', c'est-à-dire des appareils représentant des passerelles qui fonctionnent sur votre réseau local, ce qui signifie que vous pouvez traiter des données sans passer par l'Internet. Cela peut être plus rapide lorsque vous avez beaucoup de données ou une connexion Internet lente, cela vous permet de fonctionner hors ligne lorsque la connectivité Internet n'est pas possible, comme sur un navire ou dans une zone sinistrée pour répondre à une crise humanitaire, et cela vous permet de garder les données privées. Certains appareils contiendront un code de traitement créé à l'aide d'outils en nuage et l'exécuteront localement pour recueillir des données et y répondre sans utiliser de connexion Internet pour prendre une décision.

Il s'agit par exemple d'un appareil domestique intelligent tel que le HomePod d'Apple, l'Alexa d'Amazon ou le Google Home, qui écoutera votre voix à l'aide de modèles d'IA formés dans le nuage, mais exécutés localement sur l'appareil. Ces appareils 's'activent' lorsqu'un certain mot ou une certaine phrase est prononcé(e) et n'envoient qu'après celà votre voix sur Internet pour la traiter. L'appareil cessera d'envoyer la parole à un moment approprié, par exemple lorsqu'il détectera une pause dans votre discours. Tout ce que vous dites avant de réveiller l'appareil avec le mot de réveil, et tout ce que vous dites après que l'appareil a cessé d'écouter, ne sera pas envoyé via internet au fournisseur de l'appareil, et sera donc privé.

✅ Pensez à d'autres scénarios dans lesquels la confidentialité est importante, de sorte que le traitement des données serait mieux fait à la périphérie plutôt que dans le cloud. À titre d'indication - pensez aux appareils IoT dotés de caméras ou d'autres dispositifs d'imagerie.

### La sécurité dans l'IoT

Avec toute connexion Internet, la sécurité est une considération importante. Une vieille plaisanterie dit que 'le S de IoT signifie sécurité' - il n'y a pas de 'S' dans IoT, ce qui implique qu'il n'est pas sécurisé.

Les appareils IoT se connectent à un service cloud et sont donc aussi sécuriés que ce dernier. Si votre service cloud permet à n'importe quel appareil de se connecter, des données malveillantes peuvent être envoyées ou des attaques virales peuvent avoir lieu. Cela peut avoir des conséquences très concrètes dans la mesure où les dispositifs IoT interagissent et contrôlent d'autres dispositifs. Par exemple, le [ver Stuxnet](https://wikipedia.org/wiki/Stuxnet) a manipulé les valves des centrifugeuses pour les endommager. Des pirates ont également profité d'une [sécurité insuffisante pour accéder à des moniteurs pour bébé](https://www.npr.org/sections/thetwo-way/2018/06/05/617196788/s-c-mom-says-baby-monitor-was-hacked-experts-say-many-devices-are-vulnerable) et à d'autres dispositifs de surveillance domestique.

> 💁 Parfois, les appareils IoT et les périphériques fonctionnent sur un réseau complètement isolé d'Internet afin de préserver la confidentialité et la sécurité des données. C'est ce qu'on appelle l'[air-gapping](https://wikipedia.org/wiki/Air_gap_(networking)).

## Approfondissement des microcontrôleurs

Dans la dernière leçon, nous avons présenté les microcontrôleurs. Nous allons maintenant approfondir cette technologie.

### Le processeur (CPU)

Le processeur est le 'cerveau' du microcontrôleur. C'est le processeur qui exécute votre code et qui peut envoyer et recevoir des données de n'importe quel appareil connecté. Les CPU peuvent contenir un ou plusieurs noyaux - essentiellement un ou plusieurs CPU qui peuvent travailler ensemble pour exécuter votre code.

Les processeurs s'appuient sur une horloge qui ticote plusieurs millions ou milliards de fois par seconde. Chaque tic, ou cycle, synchronise les actions que l'unité centrale peut entreprendre. À chaque tic, l'unité centrale peut exécuter une instruction d'un programme, par exemple pour récupérer des données d'un périphérique externe ou effectuer un calcul mathématique. Ce cycle régulier permet de terminer toutes les actions avant de traiter l'instruction suivante.

Plus le cycle d'horloge est rapide, plus le nombre d'instructions pouvant être traitées chaque seconde est important, et donc plus le CPU est rapide. Les vitesses des processeurs sont mesurées en [Hertz (Hz)](https://wikipedia.org/wiki/Hertz), une unité standard où 1 Hz signifie un cycle ou un tic d'horloge par seconde.

> 🎓 Les vitesses des processeurs sont souvent indiquées en MHz ou en GHz. 1MHz correspond à 1 million de Hz, 1GHz à 1 milliard de Hz.

> 💁 Les CPU exécutent des programmes en utilisant le [cycle de récupération-décodage-exécution](https://wikipedia.org/wiki/Instruction_cycle). Pour chaque tic d'horloge, le CPU va chercher l'instruction suivante dans la mémoire, la décode, puis l'exécute, par exemple en utilisant une unité arithmétique et logique (UAL) pour additionner 2 nombres. Certaines exécutions prennent plusieurs ticks pour être exécutées, le cycle suivant sera donc exécuté au prochain tick après la fin de l'instruction.

![Les cycles de recherche, de décodage et d'exécution montrant la recherche prenant une instruction du programme stocké en RAM, puis la décodant et l'exécutant sur un CPU.](../../../../images/fetch-decode-execute.png)

Les microcontrôleurs ont des vitesses d'horloge beaucoup plus faibles que les ordinateurs de bureau ou portables, ou même que la plupart des smartphones. Le terminal Wio, par exemple, possède un processeur qui fonctionne à 120 MHz, soit 120 000 000 de cycles par seconde.

✅ Un PC ou un Mac moyen possède une unité centrale avec plusieurs cœurs fonctionnant à plusieurs GigaHertz, ce qui signifie que l'horloge tique des milliards de fois par seconde. Recherchez la vitesse d'horloge de votre ordinateur et comparez combien de fois il est plus rapide que le terminal Wio.

Chaque cycle d'horloge consomme de l'énergie et génère de la chaleur. Plus les tic-tac sont rapides, plus la consommation d'énergie et la production de chaleur sont importantes. Les PC sont équipés de dissipateurs thermiques et de ventilateurs pour évacuer la chaleur, sans quoi ils surchaufferaient et s'arrêteraient en quelques secondes. Les microcontrôleurs n'ont souvent ni l'un ni l'autre, car ils sont beaucoup plus froids et donc beaucoup plus lents. Les PC fonctionnent sur le secteur ou sur de grosses batteries pendant quelques heures, alors que les microcontrôleurs peuvent fonctionner pendant des jours, des mois, voire des années sur de petites batteries. Les microcontrôleurs peuvent également avoir des cœurs qui fonctionnent à des vitesses différentes, passant à des cœurs plus lents et de faible puissance lorsque la demande de l'unité centrale est faible afin de réduire la consommation d'énergie.

> 💁 Certains PC et Mac adoptent le même mélange de cœurs rapides à haute puissance et de cœurs plus lents à faible puissance, en basculant pour économiser la batterie. Par exemple, la puce M1 des derniers ordinateurs portables d'Apple peut basculer entre 4 cœurs de performance et 4 cœurs d'efficacité pour optimiser la durée de vie de la batterie ou la vitesse en fonction de la tâche exécutée.

✅ Faites un peu de recherche : Renseignez-vous sur les processeurs sur le site [Wikipedia CPU article](https://wikipedia.org/wiki/Central_processing_unit)

#### Tâche

Examinez le terminal Wio.

Si vous utilisez un terminal Wio pour ces leçons, essayez de trouver l'unité centrale. Consultez la section *Vue d'ensemble du matériel* de la [page produit du terminal Wio](https://www.seeedstudio.com/Wio-Terminal-p-4509.html) pour obtenir une image des composants internes, et essayez de trouver l'unité centrale à travers la fenêtre en plastique transparent située à l'arrière.

### Mémoire

Les microcontrôleurs disposent généralement de deux types de mémoire : la mémoire de programme et la mémoire vive (RAM).

La mémoire de programme est non volatile, ce qui signifie que tout ce qui y est écrit est conservé lorsque l'appareil n'est pas alimenté. C'est la mémoire qui stocke votre code de programme.

La RAM est la mémoire utilisée par le programme pour s'exécuter, contenant les variables allouées par votre programme et les données recueillies auprès des périphériques. La RAM est volatile, lorsque l'alimentation est coupée, son contenu est perdu, ce qui a pour effet de réinitialiser votre programme.

> 🎓 La mémoire de programme stocke votre code et se conserve lorsqu'il n'y a pas d'alimentation.

> 🎓 La mémoire vive est utilisée pour exécuter votre programme et est réinitialisée lorsqu'il n'y a pas d'alimentation.

Comme pour l'unité centrale, la mémoire d'un microcontrôleur est plusieurs fois plus petite que celle d'un PC ou d'un Mac. Un PC typique peut avoir 8 gigaoctets (Go) de RAM, ou 8 000 000 000 d'octets, chaque octet étant suffisant pour stocker une seule lettre ou un nombre de 0 à 255. Un microcontrôleur n'aurait que des kilo-octets (Ko) de RAM, un kilo-octet étant égal à 1 000 octets. Le terminal Wio mentionné ci-dessus possède 192 Ko de RAM, soit 192 000 octets - plus de 40 000 fois moins qu'un PC moyen!

Le diagramme ci-dessous montre la différence de taille relative entre 192KB et 8GB - le petit point au centre représente 192KB.

! [Une comparaison entre 192KB et 8GB - plus de 40 000 fois plus grand](../../../../images/ram-comparison.png)

Le stockage des programmes est également plus petit que dans un PC. Un PC typique peut avoir un disque dur de 500 Go pour le stockage des programmes, alors qu'un microcontrôleur peut n'avoir que des kilo-octets ou peut-être quelques méga-octets (Mo) de stockage (1 Mo correspond à 1 000 Ko, ou 1 000 000 d'octets). Le terminal Wio dispose de 4 Mo de mémoire de programme.

✅ Faites une petite recherche : De quelle quantité de mémoire vive et de stockage dispose l'ordinateur que vous utilisez pour lire ces lignes? Comment cela se compare-t-il à un microcontrôleur?

### Les entrée / Les sortie (Input/Output)

Les microcontrôleurs ont besoin de connexions d'entrée et de sortie (E/S) pour lire les données des capteurs et envoyer des signaux de commande aux actionneurs. Ils contiennent généralement un certain nombre de broches d'entrée/sortie à usage général ('general-purpose input/output' ou GPIO en anglais). Ces broches peuvent être configurées par logiciel pour être des entrées (c'est-à-dire qu'elles reçoivent un signal) ou des sorties (elles envoient un signal).

🧠⬅️ Les broches d'entrée sont utilisées pour lire les valeurs des capteurs.

🧠➡️ Les broches de sortie envoient des instructions aux actionneurs.

Vous en apprendrez plus à ce sujet dans une prochaine leçon.

#### Tâche

Examinez le terminal Wio.

Si vous utilisez un terminal Wio pour ces leçons, trouvez les broches GPIO. Trouvez la section *Pinout diagram* de la [page produit du terminal Wio](https://www.seeedstudio.com/Wio-Terminal-p-4509.html) pour savoir à quoi correspondent les broches. Le terminal Wio est livré avec un autocollant que vous pouvez apposer à l'arrière avec les numéros de broches, alors ajoutez-le maintenant si vous ne l'avez pas encore fait.

### Taille physique

Les microcontrôleurs sont généralement de petite taille, le plus petit étant un [Freescale Kinetis KL03 MCU est assez petit pour tenir dans la cavité d'une balle de golf](https://www.edn.com/tiny-arm-cortex-m0-based-mcu-shrinks-package/). L'unité centrale d'un PC peut mesurer 40 mm x 40 mm, sans compter les dissipateurs thermiques et les ventilateurs nécessaires pour que l'unité centrale puisse fonctionner pendant plus de quelques secondes sans surchauffe, ce qui est nettement plus grand qu'un microcontrôleur complet. Le kit de développement du terminal Wio, qui comprend un microcontrôleur, un boîtier, un écran et une série de connexions et de composants, n'est pas beaucoup plus grand qu'un processeur Intel i9 nu, et beaucoup plus petit qu'un processeur avec un dissipateur thermique et un ventilateur!

| Appareil                        | Taille                |
| ------------------------------- | --------------------- |
| Freescale Kinetis KL03          | 1.6mm x 2mm x 1mm     |
| Terminal Wio                    | 72mm x 57mm x 12mm    |
| Processeur Intel i9, dissipateur de chaleur et ventilateur | 136mm x 145mm x 103mm |

### Frameworks et systèmes d'exploitation

En raison de leur faible vitesse et de la taille de leur mémoire, les microcontrôleurs n'utilisent pas de système d'exploitation (OS) au sens bureautique du terme. Le système d'exploitation qui fait fonctionner votre ordinateur (Windows, Linux ou macOS) a besoin de beaucoup de mémoire et de puissance de traitement pour exécuter des tâches qui sont totalement inutiles pour un microcontrôleur. N'oubliez pas que les microcontrôleurs sont généralement programmés pour exécuter une ou plusieurs tâches très spécifiques, contrairement à un ordinateur à usage général comme un PC ou un Mac qui doit prendre en charge une interface utilisateur, lire de la musique ou des films, fournir des outils pour écrire des documents ou du code, jouer à des jeux ou naviguer sur l'internet.

Pour programmer un microcontrôleur sans système d'exploitation, vous avez besoin d'un outil qui vous permette de construire votre code de manière à ce que le microcontrôleur puisse fonctionner, en utilisant des API qui peuvent communiquer avec tous les périphériques. Chaque microcontrôleur étant différent, les fabricants prennent normalement en charge des frameworks standards qui vous permettent de suivre une 'recette' standard pour créer votre code et le faire fonctionner sur n'importe quel microcontrôleur qui prend en charge ce framework.

Vous pouvez programmer les microcontrôleurs à l'aide d'un système d'exploitation - souvent appelé système d'exploitation en temps réel ('real-time operating system' ou RTOS en anglais), car il est conçu pour gérer l'envoi de données vers et depuis des périphériques en temps réel. Ces systèmes d'exploitation sont très légers et offrent des fonctionnalités telles que :

* Le multithreading, qui permet à votre code d'exécuter plus d'un bloc de code en même temps, soit sur plusieurs cœurs, soit en se relayant sur un cœur.
* la mise en réseau, qui permet de communiquer en toute sécurité sur l'internet
* des composants d'interface utilisateur graphique (GUI) pour construire des interfaces utilisateur (UI) sur des appareils dotés d'écrans.

✅ Renseignez-vous sur les différents RTOS : [Azure RTOS](https://azure.microsoft.com/services/rtos/?WT.mc_id=academic-17441-jabenn), [FreeRTOS](https://www.freertos.org), [Zephyr](https://www.zephyrproject.org)

#### Arduino

![Le logo Arduino](../../../../images/arduino-logo.svg)

[Arduino](https://www.arduino.cc) est probablement le microcontrôleur le plus populaire, en particulier parmi les étudiants, les amateurs et les créateurs. Arduino est une plateforme électronique open source combinant logiciel et matériel. Vous pouvez acheter des cartes compatibles Arduino auprès d'Arduino ou d'autres fabricants, puis coder à l'aide de la structure Arduino.

Les cartes Arduino sont codées en C ou en C++. L'utilisation de C/C++ permet de compiler un code très petit et de l'exécuter rapidement, ce qui est nécessaire sur un dispositif contraignant tel qu'un microcontrôleur. Le cœur d'une application Arduino est appelé sketch et est un code C/C++ avec 2 fonctions - `setup` et `loop`. Lorsque la carte démarre, le code du framework Arduino exécute la fonction `setup` une fois, puis il exécute la fonction `loop` encore et encore, l'exécutant continuellement jusqu'à ce que l'alimentation soit coupée.

Vous écrirez votre code d'installation dans la fonction `setup`, comme la connexion aux services WiFi et cloud ou l'initialisation des broches pour l'entrée et la sortie. Votre code de boucle contiendrait alors le code de traitement, comme la lecture d'un capteur et l'envoi de la valeur au nuage. Vous devez normalement inclure un délai dans chaque boucle, par exemple, si vous voulez que les données du capteur soient envoyées toutes les 10 secondes, vous devez ajouter un délai de 10 secondes à la fin de la boucle pour que le microcontrôleur puisse dormir, économisant ainsi de l'énergie, puis exécuter la boucle à nouveau lorsque cela est nécessaire 10 secondes plus tard.

![Un croquis d'arduino exécutant d'abord la fonction setup, puis exécutant la fonction loop à plusieurs reprises](../../../../images/arduino-sketch.png)

✅ Cette architecture de programme est connue sous le nom de *boucle d'événements* ou *boucle de messages*. De nombreuses applications l'utilisent en arrière plan et c'est la norme pour la plupart des applications de bureau qui fonctionnent sur des systèmes d'exploitation comme Windows, macOS ou Linux. La `boucle` ('loop') écoute les messages provenant des composants de l'interface utilisateur tels que les boutons, ou des périphériques tels que le clavier, et y répond. Pour en savoir plus, consultez cet [article sur la boucle d'événements](https://wikipedia.org/wiki/Event_loop).

Arduino fournit des bibliothèques standard pour interagir avec les microcontrôleurs et les broches d'I/O (Entrée/Sorties), avec différentes implémentations en arrière plan pour fonctionner sur différents microcontrôleurs. Par exemple, la [fonction `delay`](https://www.arduino.cc/reference/en/language/functions/time/delay/) met le programme en pause pendant une période donnée, la [fonction `digitalRead`](https://www.arduino.cc/reference/en/language/functions/digital-io/digitalread/) lit une valeur `HIGH` ou `LOW` sur la broche donnée, quelle que soit la carte sur laquelle le code est exécuté. Ces bibliothèques standard signifient que le code Arduino écrit pour une carte peut être recompilé pour n'importe quelle autre carte Arduino et fonctionnera, en supposant que les broches sont les mêmes et que les cartes supportent les mêmes fonctionnalités.

Il existe un vaste écosystème de bibliothèques Arduino tierces qui vous permettent d'ajouter des fonctionnalités supplémentaires à vos projets Arduino, telles que l'utilisation de capteurs et d'actionneurs ou la connexion à des services cloud IoT.

##### Tâche

Étudiez le terminal Wio.

Si vous utilisez un terminal Wio pour ces leçons, relisez le code que vous avez écrit dans la dernière leçon. Trouvez les fonctions `setup` et `loop`. Surveillez la sortie série pour voir si la fonction loop est appelée de façon répétée. Essayez d'ajouter du code à la fonction `setup` pour écrire sur le port série et observez que ce code n'est appelé qu'une seule fois à chaque redémarrage. Essayez de redémarrer votre appareil avec l'interrupteur d'alimentation sur le côté pour montrer que ce code est appelé à chaque redémarrage de l'appareil.

## Approfondissement des ordinateurs monocartes

Dans la dernière leçon, nous avons présenté les ordinateurs monocartes. Nous allons maintenant les étudier plus en détail.

### Raspberry Pi

![Le logo Raspberry Pi](../../../../images/raspberry-pi-logo.png)

La [Raspberry Pi Foundation](https://www.raspberrypi.org) est une organisation caritative britannique fondée en 2009 pour promouvoir l'étude de l'informatique, en particulier dans les écoles. Dans le cadre de cette mission, elle a développé un ordinateur monocarte, appelé Raspberry Pi. Les Raspberry Pis sont actuellement disponibles en trois variantes : une version pleine grandeur, le Pi Zero, plus petit, et un module de calcul qui peut être intégré dans votre appareil IoT final.

![Un Raspberry Pi 4](../../../../images/raspberry-pi-4.jpg)

La dernière itération du Raspberry Pi grandeur nature est le Raspberry Pi 4B. Il dispose d'un processeur quadricœur (4 cœurs) cadencé à 1,5 GHz, de 2, 4 ou 8 Go de RAM, d'un réseau Ethernet gigabit, du WiFi, de 2 ports HDMI supportant les écrans 4k, d'un port de sortie audio et vidéo composite, de ports USB (2 USB 2.0, 2 USB 3.0), de 40 broches GPIO, d'un connecteur pour un module caméra Raspberry Pi, et d'un emplacement pour carte SD. Le tout sur une carte de 88 mm x 58 mm x 19,5 mm, alimentée par une alimentation USB-C de 3A. Ces cartes sont proposées à partir de 35 dollars, bien moins chères qu'un PC ou un Mac.

> 💁 Il existe également un ordinateur tout-en-un Pi400 avec un Pi4 intégré dans un clavier.

![Un Raspberry Pi Zero](../../../../images/raspberry-pi-zero.jpg)

Le Pi Zero est beaucoup plus petit et moins puissant. Il dispose d'un processeur à cœur unique de 1 GHz, de 512 Mo de RAM, du WiFi (dans le modèle Zero W), d'un port HDMI unique, d'un port micro-USB, de 40 broches GPIO, d'un connecteur pour un module caméra Raspberry Pi et d'un emplacement pour carte SD. Il mesure 65 mm x 30 mm x 5 mm et consomme très peu d'énergie. Le Zero coûte 5 dollars, la version W avec WiFi 10 dollars.

> 🎓 Les processeurs de ces deux appareils sont des processeurs ARM, par opposition aux processeurs Intel/AMD x86 ou x64 que l'on trouve dans la plupart des PC et des Mac. Ces processeurs sont similaires à ceux que l'on trouve dans certains microcontrôleurs, ainsi que dans presque tous les téléphones portables, la Surface X de Microsoft et les nouveaux Mac d'Apple basés sur le silicium.

Toutes les variantes du Raspberry Pi utilisent une version de Debian Linux appelée Raspberry Pi OS. Cette version est disponible en version allégée sans bureau, ce qui est parfait pour les projets 'headless' où vous n'avez pas besoin d'écran, ou en version complète avec un environnement de bureau complet, avec un navigateur web, des applications de bureau, des outils de codage et des jeux. Le système d'exploitation étant une version de Debian Linux, vous pouvez installer n'importe quelle application ou outil fonctionnant sous Debian et conçu pour le processeur ARM du Pi.

#### Tâche

Étudiez le Raspberry Pi.

Si vous utilisez un Raspberry Pi pour ces leçons, renseignez-vous sur les différents composants matériels de la carte.

* Vous pouvez trouver des détails sur les processeurs utilisés sur la [page de documentation sur le matériel du Raspberry Pi](https://www.raspberrypi.org/documentation/hardware/raspberrypi/). Renseignez-vous sur le processeur utilisé dans le Pi que vous utilisez.
* Localisez les broches GPIO. Pour en savoir plus, consultez la [documentation GPIO du Raspberry Pi](https://www.raspberrypi.org/documentation/hardware/raspberrypi/gpio/README.md). Utilisez le [Guide d'utilisation des broches GPIO](https://www.raspberrypi.org/documentation/usage/gpio/README.md) pour identifier les différentes broches de votre Pi.

### Programmation d'ordinateurs monocartes

Les ordinateurs monocartes sont des ordinateurs à part entière, dotés d'un système d'exploitation complet. Cela signifie qu'il existe un large éventail de langages de programmation, de cadres et d'outils que vous pouvez utiliser pour les coder, contrairement aux microcontrôleurs qui dépendent de la prise en charge de la carte dans des cadres tels qu'Arduino. La plupart des langages de programmation disposent de bibliothèques qui peuvent accéder aux broches GPIO pour envoyer et recevoir des données de capteurs et d'actionneurs.

✅ Quels sont les langages de programmation qui vous sont familiers? Sont-ils pris en charge par Linux?

Le langage de programmation le plus courant pour créer des applications IoT sur un Raspberry Pi est Python. Il existe un vaste écosystème de matériel conçu pour le Pi, et presque tous incluent le code nécessaire à leur utilisation sous forme de bibliothèques Python. Certains de ces écosystèmes sont basés sur des `chapeaux` (ou `hat` en anglais), ainsi appelés parce qu'ils se placent sur le Pi comme un chapeau et se connectent aux 40 broches GPIO à l'aide d'une grande prise. Ces chapeaux offrent des fonctionnalités supplémentaires, telles que des écrans, des capteurs, des voitures télécommandées ou des adaptateurs permettant de brancher des capteurs à l'aide de câbles standardisés.

### Utilisation d'ordinateurs monocartes dans les déploiements professionnels de l'IoT

Les ordinateurs monocartes sont utilisés pour les déploiements IoT professionnels, et pas seulement comme kits de développement. Ils peuvent constituer un moyen puissant de contrôler le matériel et d'exécuter des tâches complexes telles que l'exécution de modèles d'apprentissage automatique. Par exemple, il existe un [module de calcul Raspberry Pi 4 ](https://www.raspberrypi.org/blog/raspberry-pi-compute-module-4/) qui offre toute la puissance d'un Raspberry Pi 4, mais dans un format compact et moins cher, sans la plupart des ports, conçu pour être installé dans du matériel personnalisé.

---

## 🚀 Défi

Le défi de la dernière leçon consistait à dresser une liste du plus grand nombre possible d'appareils IoT présents chez vous, à l'école ou sur votre lieu de travail. Pour chaque appareil de cette liste, pensez-vous qu'ils sont construits autour de microcontrôleurs ou d'ordinateurs monocartes, ou même d'un mélange des deux ?

## Quiz de validation des connaissances

[Quiz de validation des connaissances](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/4)

## Révision et auto-apprentissage

* Lire le [Guide de démarrage Arduino](https://www.arduino.cc/en/Guide/Introduction) pour en savoir plus sur la plateforme Arduino.
* Lire [l'introduction au Raspberry Pi 4](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/) pour en savoir plus sur les Raspberry Pis.
* Apprenez-en plus sur certains concepts et acronymes dans l'article [What the FAQ are CPUs, MPUs, MCUs, and GPUs article in the Electrical Engineering Journal](https://www.eejournal.com/article/what-the-faq-are-cpus-mpus-mcus-and-gpus/).

✅ Utilisez ces guides, ainsi que les coûts indiqués en suivant les liens dans le [guide du matériel](../../../../hardware.md) pour décider de la plate-forme matérielle que vous souhaitez utiliser, ou si vous préférez utiliser un dispositif virtuel.

## Affectation

[Comparez les microcontrôleurs et les ordinateurs monocartes](assignment.fr.md)
