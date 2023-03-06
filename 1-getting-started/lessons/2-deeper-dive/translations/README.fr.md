# Une meilleure immersion dans IoT

![Un aperçu de cette leçon sous forme de sketch](../../../sketchnotes/lesson-2.jpg)

> Sketchnote par [Nitya Narasimhan](https://github.com/nitya). Cliquez sur l'image pour l'agrandir.

Cette leçon a été dispensée dans le cadre de la [série Hello IoT](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) de [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). La leçon a été enseignée sous la forme de deux vidéos - une leçon d'une heure et une heure de bureau pour approfondir certaines parties de la leçon et répondre aux questions.

[![Leçon 2 : Une meilleure immersion dans l'IoT](https://img.youtube.com/vi/t0SySWw3z9M/0.jpg)](https://youtu.be/t0SySWw3z9M)

[![Leçon 2 : Une meilleure immersion dans l'IoT - Heures de bureau](https://img.youtube.com/vi/tTZYf9EST1E/0.jpg)](https://youtu.be/tTZYf9EST1E)

> 🎥 Cliquez sur les images ci-dessus pour regarder les vidéos

## Quiz préalable

[Quiz préalable](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/3)

## Introduction

Cette leçon approfondit certains des concepts abordés dans la dernière leçon.

Dans cette leçon, nous couvrirons :

* [Les composants d'une application IoT](#components-of-an-iot-application)
* [Approfondissement des microcontrôleurs](#deeper-dive-into-microcontrollers)
* [Approfondissement des ordinateurs monocartes](#deeper-dive-into-single-board-computers)

## Les composants d'une application IoT

Les deux composants d'une application IoT sont l' *Internet* et l' *objet* (the thing). Examinons ces deux composants de manière un peu plus détaillée.

### L'objet (The Thing)

![Une Raspberry Pi 4](../../../images/raspberry-pi-4.jpg)

La partie **Objet** (**Thing** en anglais) de l'IOT (Internet Of Thing) fait référence à un dispositif qui peut interagir avec le monde physique. Ces appareils sont généralement des ordinateurs de petite taille, peu coûteux, fonctionnant à faible vitesse et consommant peu d'énergie - par exemple, de simples microcontrôleurs dotés de kilooctets de RAM (par opposition aux gigaoctets d'un PC) et fonctionnant à seulement quelques centaines de mégahertz (par opposition aux gigahertz d'un PC), mais consommant parfois si peu d'énergie qu'ils peuvent fonctionner pendant des semaines, des mois, voire des années sur des piles.

Ces dispositifs interagissent avec le monde physique, soit en utilisant des capteurs pour recueillir des données sur leur environnement, soit en contrôlant des sorties ou des actionneurs pour apporter des changements physiques. L'exemple type est celui du thermostat intelligent, un appareil doté d'un capteur de température, d'un moyen de régler la température souhaitée (cadran ou écran tactile) et d'une connexion à un système de chauffage ou de refroidissement qui peut être activé lorsque la température détectée est en dehors de la plage souhaitée. Le capteur de température détecte que la pièce est trop froide et un actionneur met le chauffage en marche.

![Un diagramme montrant la température et un cadran comme entrées d'un dispositif IoT, et le contrôle d'un appareil de chauffage comme sortie.](../../../images/basic-thermostat.png)

Il existe un large éventail d'objets différents qui peuvent agir comme des dispositifs IoT, du matériel dédié qui détecte une seule chose, aux appareils à usage général, même votre smartphone ! Un smartphone peut utiliser des capteurs pour détecter le monde qui l'entoure et des actionneurs pour interagir avec ce monde, par exemple en utilisant un capteur GPS pour détecter votre position et un haut-parleur pour vous donner des instructions de navigation vers une destination.

✅ Pensez à d'autres systèmes que vous avez autour de vous et qui lisent les données d'un capteur et les utilisent pour prendre des décisions. Un exemple serait le thermostat d'un four. Pouvez-vous en trouver d'autres ?

### L'Internet

Le côté **Internet** d'une application IoT (Internet Of Thing) se compose d'applications auxquelles le dispositif IoT peut se connecter pour envoyer et recevoir des données, ainsi que d'autres applications qui peuvent traiter les données du dispositif IoT et aider à prendre des décisions sur les demandes à envoyer aux actionneurs du dispositif IoT.

Une configuration typique consisterait à avoir une sorte de service cloud auquel le dispositif IoT se connecte, et ce service cloud gèrerait des aspect comme la sécurité, ainsi que la réception et le renvoi de messages au dispositif IoT. Ce service cloud se connecte ensuite à d'autres applications qui peuvent traiter ou stocker les données des capteurs, ou utiliser ces données avec celles d'autres systèmes pour prendre des décisions.

Par ailleurs, les appareils ne se connectent pas toujours directement à l'internet via des connexions WiFi ou filaires. Certains appareils utilisent un réseau maillé pour communiquer entre eux par le biais de technologies telles que le Bluetooth, en se connectant via un hub qui dispose d'une connexion Internet.

Dans l'exemple d'un thermostat intelligent, le thermostat se connecterait via le WiFi domestique à un service en nuage s'éxecutant dans le cloud. Il enverrait les données de température à ce service en nuage, et de là, elles seraient écrites dans une sorte de base de données permettant au propriétaire de vérifier les températures actuelles et passées à l'aide d'une application téléphonique. Un autre service cloud saura quelle température le propriétaire souhaite et enverra des messages à l'appareil IoT via le service cloud pour demander au système de chauffage de s'allumer ou de s'éteindre.

![Un diagramme montrant la température et un cadran comme entrées d'un dispositif IoT, le dispositif IoT avec une communication bidirectionnelle vers le cloud, qui à son tour a une communication bidirectionnelle vers un téléphone, et le contrôle d'un chauffage comme sortie du dispositif IoT.](../../../images/mobile-controlled-thermostat.png)

Une version encore plus intelligente pourrait utiliser l'IA dans le cloud avec des données provenant d'autres capteurs connectés à d'autres appareils IoT, tels que des capteurs d'occupation qui détectent quelles pièces sont utilisées, ainsi que des données telles que la météo et même votre calendrier, pour prendre des décisions sur la façon de régler la température de manière intelligente. Par exemple, il pourrait éteindre votre chauffage s'il lit dans votre calendrier que vous êtes en vacances, ou éteindre le chauffage pièce par pièce en fonction des pièces que vous utilisez, apprenant des données pour être de plus en plus précis au fil du temps.

![Un diagramme montrant plusieurs capteurs de température et un cadran comme entrées d'un dispositif IoT, un dispositif IoT avec une communication bidirectionnelle vers le cloud, qui à son tour a une communication bidirectionnelle vers un téléphone, un calendrier et un service météorologique, et la commande d'un chauffage comme sortie du dispositif IoT.](../../../images/smarter-thermostat.png)

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

![Les cycles de recherche, de décodage et d'exécution montrant la recherche prenant une instruction du programme stocké en RAM, puis la décodant et l'exécutant sur un CPU.](../../../images/fetch-decode-execute.png)

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

! [Une comparaison entre 192KB et 8GB - plus de 40 000 fois plus grand](../../../images/ram-comparison.png)

Le stockage des programmes est également plus petit que dans un PC. Un PC typique peut avoir un disque dur de 500 Go pour le stockage des programmes, alors qu'un microcontrôleur peut n'avoir que des kilo-octets ou peut-être quelques méga-octets (Mo) de stockage (1 Mo correspond à 1 000 Ko, ou 1 000 000 d'octets). Le terminal Wio dispose de 4 Mo de mémoire de programme.

✅ Faites une petite recherche : De quelle quantité de mémoire vive et de stockage dispose l'ordinateur que vous utilisez pour lire ces lignes? Comment cela se compare-t-il à un microcontrôleur?

### Les entrée / Les sortie (Input/Output)