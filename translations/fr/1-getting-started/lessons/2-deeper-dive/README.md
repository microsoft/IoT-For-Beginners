# Une exploration approfondie de l'IoT

![Un aperçu en sketchnote de cette leçon](../../../../../translated_images/fr/lesson-2.324b0580d620c25e.webp)

> Sketchnote par [Nitya Narasimhan](https://github.com/nitya). Cliquez sur l'image pour une version agrandie.

Cette leçon a été enseignée dans le cadre de la série [Hello IoT](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) du [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). La leçon a été présentée en deux vidéos : une leçon d'une heure et une session de questions-réponses d'une heure approfondissant certains aspects de la leçon et répondant aux questions.

[![Leçon 2 : Une exploration approfondie de l'IoT](https://img.youtube.com/vi/t0SySWw3z9M/0.jpg)](https://youtu.be/t0SySWw3z9M)

[![Leçon 2 : Une exploration approfondie de l'IoT - Heures de bureau](https://img.youtube.com/vi/tTZYf9EST1E/0.jpg)](https://youtu.be/tTZYf9EST1E)

> 🎥 Cliquez sur les images ci-dessus pour regarder les vidéos

## Quiz avant la leçon

[Quiz avant la leçon](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/3)

## Introduction

Cette leçon explore plus en profondeur certains des concepts abordés dans la leçon précédente.

Dans cette leçon, nous couvrirons :

* [Les composants d'une application IoT](../../../../../1-getting-started/lessons/2-deeper-dive)
* [Exploration approfondie des microcontrôleurs](../../../../../1-getting-started/lessons/2-deeper-dive)
* [Exploration approfondie des ordinateurs monocarte](../../../../../1-getting-started/lessons/2-deeper-dive)

## Les composants d'une application IoT

Les deux composants d'une application IoT sont l'*Internet* et l'*objet*. Examinons ces deux composants plus en détail.

### L'objet

![Un Raspberry Pi 4](../../../../../translated_images/fr/raspberry-pi-4.fd4590d308c3d456.webp)

La partie **objet** de l'IoT fait référence à un appareil capable d'interagir avec le monde physique. Ces appareils sont généralement de petits ordinateurs peu coûteux, fonctionnant à faible vitesse et consommant peu d'énergie - par exemple, des microcontrôleurs simples avec quelques kilooctets de RAM (par opposition aux gigaoctets d'un PC) fonctionnant à seulement quelques centaines de mégahertz (par opposition aux gigahertz d'un PC), mais consommant parfois si peu d'énergie qu'ils peuvent fonctionner pendant des semaines, des mois, voire des années sur des batteries.

Ces appareils interagissent avec le monde physique, soit en utilisant des capteurs pour recueillir des données de leur environnement, soit en contrôlant des sorties ou des actionneurs pour effectuer des changements physiques. L'exemple typique est un thermostat intelligent - un appareil doté d'un capteur de température, d'un moyen de définir une température souhaitée comme un cadran ou un écran tactile, et d'une connexion à un système de chauffage ou de refroidissement qui peut être activé lorsque la température détectée est en dehors de la plage souhaitée. Le capteur de température détecte que la pièce est trop froide et un actionneur allume le chauffage.

![Un diagramme montrant la température et un cadran comme entrées d'un appareil IoT, et le contrôle d'un chauffage comme sortie](../../../../../translated_images/fr/basic-thermostat.a923217fd1f37e5a.webp)

Il existe une grande variété d'objets pouvant agir comme appareils IoT, allant du matériel dédié à la détection d'un seul élément à des appareils polyvalents, même votre smartphone ! Un smartphone peut utiliser des capteurs pour détecter le monde qui l'entoure et des actionneurs pour interagir avec celui-ci - par exemple, en utilisant un capteur GPS pour détecter votre position et un haut-parleur pour vous donner des instructions de navigation vers une destination.

✅ Pensez à d'autres systèmes autour de vous qui lisent des données à partir d'un capteur et les utilisent pour prendre des décisions. Un exemple serait le thermostat d'un four. Pouvez-vous en trouver d'autres ?

### L'Internet

La partie **Internet** d'une application IoT consiste en des applications auxquelles l'appareil IoT peut se connecter pour envoyer et recevoir des données, ainsi qu'à d'autres applications pouvant traiter les données de l'appareil IoT et aider à prendre des décisions sur les demandes à envoyer aux actionneurs de l'appareil IoT.

Un scénario typique serait d'avoir un service cloud auquel l'appareil IoT se connecte, et ce service cloud gère des aspects tels que la sécurité, ainsi que la réception des messages de l'appareil IoT et l'envoi de messages à l'appareil. Ce service cloud se connecterait ensuite à d'autres applications pouvant traiter ou stocker les données des capteurs, ou utiliser ces données avec celles d'autres systèmes pour prendre des décisions.

Les appareils ne se connectent pas toujours directement à Internet via WiFi ou des connexions filaires. Certains appareils utilisent des réseaux maillés pour communiquer entre eux via des technologies telles que le Bluetooth, en se connectant via un appareil central disposant d'une connexion Internet.

Dans l'exemple d'un thermostat intelligent, le thermostat se connecterait via le WiFi domestique à un service cloud. Il enverrait les données de température à ce service cloud, qui les écrirait ensuite dans une base de données permettant au propriétaire de vérifier les températures actuelles et passées via une application téléphonique. Un autre service dans le cloud saurait quelle température le propriétaire souhaite et enverrait des messages à l'appareil IoT via le service cloud pour indiquer au système de chauffage de s'allumer ou de s'éteindre.

![Un diagramme montrant la température et un cadran comme entrées d'un appareil IoT, l'appareil IoT avec une communication bidirectionnelle avec le cloud, qui à son tour a une communication bidirectionnelle avec un téléphone, et le contrôle d'un chauffage comme sortie de l'appareil IoT](../../../../../translated_images/fr/mobile-controlled-thermostat.4a994010473d8d6a.webp)

Une version encore plus intelligente pourrait utiliser l'IA dans le cloud avec des données provenant d'autres capteurs connectés à d'autres appareils IoT, tels que des capteurs de présence détectant les pièces utilisées, ainsi que des données telles que la météo et même votre calendrier, pour prendre des décisions sur la manière de régler la température de manière intelligente. Par exemple, elle pourrait éteindre votre chauffage si elle lit dans votre calendrier que vous êtes en vacances, ou éteindre le chauffage pièce par pièce en fonction des pièces que vous utilisez, apprenant des données pour devenir de plus en plus précise au fil du temps.

![Un diagramme montrant plusieurs capteurs de température et un cadran comme entrées d'un appareil IoT, l'appareil IoT avec une communication bidirectionnelle avec le cloud, qui à son tour a une communication bidirectionnelle avec un téléphone, un calendrier et un service météo, et le contrôle d'un chauffage comme sortie de l'appareil IoT](../../../../../translated_images/fr/smarter-thermostat.a75855f15d2d9e63.webp)

✅ Quelles autres données pourraient aider à rendre un thermostat connecté à Internet plus intelligent ?

### IoT à la périphérie

Bien que le "I" dans IoT signifie Internet, ces appareils n'ont pas toujours besoin de se connecter à Internet. Dans certains cas, les appareils peuvent se connecter à des appareils "edge" - des appareils passerelles fonctionnant sur votre réseau local, ce qui permet de traiter les données sans passer par Internet. Cela peut être plus rapide lorsque vous avez beaucoup de données ou une connexion Internet lente, cela permet de fonctionner hors ligne lorsque la connectivité Internet n'est pas possible, comme sur un navire ou dans une zone sinistrée lors d'une crise humanitaire, et cela permet de garder les données privées. Certains appareils contiendront du code de traitement créé à l'aide d'outils cloud et l'exécuteront localement pour collecter et répondre aux données sans utiliser une connexion Internet pour prendre une décision.

Un exemple de cela est un appareil domestique intelligent tel qu'un Apple HomePod, Amazon Alexa ou Google Home, qui écoutera votre voix à l'aide de modèles d'IA entraînés dans le cloud, mais fonctionnant localement sur l'appareil. Ces appareils s'activent lorsqu'un certain mot ou une certaine phrase est prononcé, et seulement alors envoient votre discours sur Internet pour traitement. L'appareil cesse d'envoyer le discours à un moment approprié, comme lorsqu'il détecte une pause dans votre discours. Tout ce que vous dites avant d'activer l'appareil avec le mot d'activation, et tout ce que vous dites après que l'appareil a cessé d'écouter, ne sera pas envoyé sur Internet au fournisseur de l'appareil, et restera donc privé.

✅ Pensez à d'autres scénarios où la confidentialité est importante, de sorte que le traitement des données serait mieux effectué à la périphérie plutôt que dans le cloud. Un indice : pensez aux appareils IoT équipés de caméras ou d'autres dispositifs d'imagerie.

### Sécurité de l'IoT

Avec toute connexion Internet, la sécurité est une considération importante. Il existe une vieille blague selon laquelle "le S dans IoT signifie Sécurité" - il n'y a pas de "S" dans IoT, ce qui implique qu'il n'est pas sécurisé.

Les appareils IoT se connectent à un service cloud, et sont donc aussi sécurisés que ce service cloud - si votre service cloud permet à n'importe quel appareil de se connecter, des données malveillantes peuvent être envoyées ou des attaques virales peuvent avoir lieu. Cela peut avoir des conséquences très réelles, car les appareils IoT interagissent et contrôlent d'autres appareils. Par exemple, le [ver Stuxnet](https://wikipedia.org/wiki/Stuxnet) a manipulé des vannes dans des centrifugeuses pour les endommager. Les hackers ont également profité de [failles de sécurité pour accéder à des moniteurs pour bébés](https://www.npr.org/sections/thetwo-way/2018/06/05/617196788/s-c-mom-says-baby-monitor-was-hacked-experts-say-many-devices-are-vulnerable) et à d'autres dispositifs de surveillance domestique.

> 💁 Parfois, les appareils IoT et les appareils edge fonctionnent sur un réseau complètement isolé d'Internet pour garder les données privées et sécurisées. Cela s'appelle le [air-gapping](https://wikipedia.org/wiki/Air_gap_(networking)).

## Exploration approfondie des microcontrôleurs

Dans la leçon précédente, nous avons introduit les microcontrôleurs. Examinons-les maintenant plus en détail.

### CPU

Le CPU est le "cerveau" du microcontrôleur. C'est le processeur qui exécute votre code et peut envoyer des données à et recevoir des données des appareils connectés. Les CPU peuvent contenir un ou plusieurs cœurs - essentiellement un ou plusieurs CPU pouvant travailler ensemble pour exécuter votre code.

Les CPU dépendent d'une horloge qui bat des millions ou des milliards de fois par seconde. Chaque battement, ou cycle, synchronise les actions que le CPU peut effectuer. À chaque battement, le CPU peut exécuter une instruction d'un programme, comme récupérer des données d'un appareil externe ou effectuer un calcul mathématique. Ce cycle régulier permet à toutes les actions d'être terminées avant que l'instruction suivante ne soit traitée.

Plus le cycle de l'horloge est rapide, plus d'instructions peuvent être traitées chaque seconde, et donc plus le CPU est rapide. Les vitesses des CPU sont mesurées en [Hertz (Hz)](https://wikipedia.org/wiki/Hertz), une unité standard où 1 Hz signifie un cycle ou battement d'horloge par seconde.

> 🎓 Les vitesses des CPU sont souvent exprimées en MHz ou GHz. 1MHz correspond à 1 million de Hz, 1GHz à 1 milliard de Hz.

> 💁 Les CPU exécutent des programmes en utilisant le [cycle de récupération-décodage-exécution](https://wikipedia.org/wiki/Instruction_cycle). À chaque battement d'horloge, le CPU récupère la prochaine instruction de la mémoire, la décode, puis l'exécute, par exemple en utilisant une unité logique arithmétique (ALU) pour additionner deux nombres. Certaines exécutions nécessitent plusieurs battements pour s'exécuter, donc le cycle suivant s'exécutera au battement suivant après que l'instruction soit terminée.

![Les cycles de récupération-décodage-exécution montrant la récupération d'une instruction du programme stocké dans la RAM, puis son décodage et son exécution sur un CPU](../../../../../translated_images/fr/fetch-decode-execute.2fd6f150f6280392.webp)

Les microcontrôleurs ont des vitesses d'horloge bien inférieures à celles des ordinateurs de bureau ou portables, ou même de la plupart des smartphones. Par exemple, le Wio Terminal a un CPU fonctionnant à 120MHz, soit 120 000 000 cycles par seconde.

✅ Un PC ou Mac moyen possède un CPU avec plusieurs cœurs fonctionnant à plusieurs GigaHertz, ce qui signifie que l'horloge bat des milliards de fois par seconde. Recherchez la vitesse d'horloge de votre ordinateur et comparez combien de fois elle est plus rapide que celle du Wio Terminal.

Chaque cycle d'horloge consomme de l'énergie et génère de la chaleur. Plus les battements sont rapides, plus la consommation d'énergie est élevée et plus la chaleur générée est importante. Les PC ont des dissipateurs thermiques et des ventilateurs pour évacuer la chaleur, sans lesquels ils surchaufferaient et s'éteindraient en quelques secondes. Les microcontrôleurs n'ont souvent ni l'un ni l'autre, car ils fonctionnent beaucoup plus froidement et donc beaucoup plus lentement. Les PC fonctionnent sur secteur ou sur de grandes batteries pendant quelques heures, tandis que les microcontrôleurs peuvent fonctionner pendant des jours, des mois, voire des années sur de petites batteries. Les microcontrôleurs peuvent également avoir des cœurs fonctionnant à des vitesses différentes, passant à des cœurs plus lents et à faible consommation lorsque la demande sur le CPU est faible pour réduire la consommation d'énergie.

> 💁 Certains PC et Mac adoptent le même mélange de cœurs rapides à haute puissance et de cœurs plus lents à faible puissance, basculant pour économiser la batterie. Par exemple, la puce M1 dans les derniers ordinateurs portables Apple peut basculer entre 4 cœurs de performance et 4 cœurs d'efficacité pour optimiser la durée de vie de la batterie ou la vitesse en fonction de la tâche exécutée.

✅ Faites quelques recherches : Lisez sur les CPU dans l'[article Wikipedia sur les CPU](https://wikipedia.org/wiki/Central_processing_unit)

#### Tâche

Explorez le Wio Terminal.

Si vous utilisez un Wio Terminal pour ces leçons, essayez de trouver le CPU. Trouvez la section *Aperçu matériel* de la [page produit du Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html) pour une image des composants internes, et essayez de localiser le CPU à travers la fenêtre en plastique transparent à l'arrière.

### Mémoire

Les microcontrôleurs ont généralement deux types de mémoire : la mémoire de programme et la mémoire vive (RAM).

La mémoire de programme est non volatile, ce qui signifie que tout ce qui y est écrit reste même lorsqu'il n'y a pas d'alimentation sur l'appareil. C'est la mémoire qui stocke le code de votre programme.

La RAM est la mémoire utilisée par le programme pour s'exécuter, contenant les variables allouées par votre programme et les données collectées à partir des périphériques. La RAM est volatile, lorsque l'alimentation est coupée, le contenu est perdu, ce qui réinitialise effectivement votre programme.
🎓 La mémoire programme stocke votre code et reste intacte même en cas de coupure de courant.
> 🎓 La RAM est utilisée pour exécuter votre programme et est réinitialisée en cas de coupure d'alimentation.

Comme pour le CPU, la mémoire d'un microcontrôleur est infiniment plus petite que celle d'un PC ou d'un Mac. Un PC typique peut avoir 8 Gigaoctets (Go) de RAM, soit 8 000 000 000 octets, chaque octet ayant suffisamment d'espace pour stocker une lettre ou un nombre de 0 à 255. Un microcontrôleur, en revanche, ne dispose que de quelques Kilooctets (Ko) de RAM, un kilooctet correspondant à 1 000 octets. Le terminal Wio mentionné ci-dessus possède 192 Ko de RAM, soit 192 000 octets - plus de 40 000 fois moins qu'un PC moyen !

Le schéma ci-dessous illustre la différence de taille relative entre 192 Ko et 8 Go - le petit point au centre représente 192 Ko.

![Une comparaison entre 192 Ko et 8 Go - plus de 40 000 fois plus grand](../../../../../translated_images/fr/ram-comparison.6beb73541b42ac6f.webp)

L'espace de stockage des programmes est également plus petit que celui d'un PC. Un PC typique peut avoir un disque dur de 500 Go pour le stockage des programmes, tandis qu'un microcontrôleur peut n'avoir que quelques kilooctets ou, au mieux, quelques mégaoctets (Mo) de stockage (1 Mo équivaut à 1 000 Ko, soit 1 000 000 octets). Le terminal Wio dispose de 4 Mo de stockage pour les programmes.

✅ Faites une petite recherche : Quelle quantité de RAM et de stockage possède l'ordinateur que vous utilisez actuellement ? Comment cela se compare-t-il à un microcontrôleur ?

### Entrée/Sortie

Les microcontrôleurs ont besoin de connexions d'entrée et de sortie (E/S) pour lire les données des capteurs et envoyer des signaux de commande aux actionneurs. Ils contiennent généralement un certain nombre de broches d'entrée/sortie à usage général (GPIO). Ces broches peuvent être configurées par logiciel pour être des entrées (c'est-à-dire qu'elles reçoivent un signal) ou des sorties (elles envoient un signal).

🧠⬅️ Les broches d'entrée sont utilisées pour lire les valeurs des capteurs.

🧠➡️ Les broches de sortie envoient des instructions aux actionneurs.

✅ Vous en apprendrez davantage à ce sujet dans une leçon ultérieure.

#### Tâche

Explorez le terminal Wio.

Si vous utilisez un terminal Wio pour ces leçons, localisez les broches GPIO. Consultez la section *Schéma des broches* de la [page produit du terminal Wio](https://www.seeedstudio.com/Wio-Terminal-p-4509.html) pour savoir quelles broches correspondent à quoi. Le terminal Wio est livré avec un autocollant que vous pouvez coller à l'arrière pour indiquer les numéros de broches, alors ajoutez-le maintenant si ce n'est pas déjà fait.

### Taille physique

Les microcontrôleurs sont généralement de petite taille, le plus petit, un [Freescale Kinetis KL03 MCU, étant suffisamment petit pour tenir dans le creux d'une balle de golf](https://www.edn.com/tiny-arm-cortex-m0-based-mcu-shrinks-package/). À titre de comparaison, le CPU d'un PC peut mesurer 40 mm x 40 mm, sans compter les dissipateurs thermiques et les ventilateurs nécessaires pour éviter la surchauffe, ce qui est nettement plus grand qu'un microcontrôleur complet. Le kit de développement du terminal Wio, avec un microcontrôleur, un boîtier, un écran et une gamme de connexions et de composants, n'est pas beaucoup plus grand qu'un processeur Intel i9 nu, et est nettement plus petit qu'un CPU avec dissipateur thermique et ventilateur !

| Appareil                         | Taille                |
| -------------------------------- | --------------------- |
| Freescale Kinetis KL03           | 1,6 mm x 2 mm x 1 mm  |
| Terminal Wio                     | 72 mm x 57 mm x 12 mm |
| Intel i9 CPU, dissipateur et ventilateur | 136 mm x 145 mm x 103 mm |

### Frameworks et systèmes d'exploitation

En raison de leur faible vitesse et de leur petite taille mémoire, les microcontrôleurs ne fonctionnent pas avec un système d'exploitation (OS) au sens classique du terme. Le système d'exploitation qui fait fonctionner votre ordinateur (Windows, Linux ou macOS) nécessite beaucoup de mémoire et de puissance de traitement pour exécuter des tâches totalement inutiles pour un microcontrôleur. Rappelez-vous que les microcontrôleurs sont généralement programmés pour effectuer une ou plusieurs tâches très spécifiques, contrairement à un ordinateur généraliste comme un PC ou un Mac qui doit prendre en charge une interface utilisateur, lire de la musique ou des films, fournir des outils pour écrire des documents ou du code, jouer à des jeux ou naviguer sur Internet.

Pour programmer un microcontrôleur sans OS, vous avez besoin d'outils permettant de construire votre code de manière à ce que le microcontrôleur puisse l'exécuter, en utilisant des API capables de communiquer avec les périphériques. Chaque microcontrôleur est différent, donc les fabricants prennent généralement en charge des frameworks standard qui vous permettent de suivre une "recette" standard pour construire votre code et le faire fonctionner sur n'importe quel microcontrôleur compatible avec ce framework.

Vous pouvez programmer des microcontrôleurs avec un OS - souvent appelé système d'exploitation en temps réel (RTOS), car ils sont conçus pour gérer l'envoi et la réception de données des périphériques en temps réel. Ces systèmes d'exploitation sont très légers et offrent des fonctionnalités telles que :

* Le multi-threading, permettant à votre code d'exécuter plusieurs blocs de code en même temps, soit sur plusieurs cœurs, soit en alternance sur un seul cœur.
* La mise en réseau pour permettre une communication sécurisée sur Internet.
* Des composants d'interface utilisateur graphique (GUI) pour créer des interfaces utilisateur (UI) sur des appareils dotés d'écrans.

✅ Renseignez-vous sur différents RTOS : [Azure RTOS](https://azure.microsoft.com/services/rtos/?WT.mc_id=academic-17441-jabenn), [FreeRTOS](https://www.freertos.org), [Zephyr](https://www.zephyrproject.org).

#### Arduino

![Le logo Arduino](../../../../../images/arduino-logo.svg)

[Arduino](https://www.arduino.cc) est probablement le framework de microcontrôleur le plus populaire, en particulier parmi les étudiants, les amateurs et les makers. Arduino est une plateforme électronique open source combinant matériel et logiciel. Vous pouvez acheter des cartes compatibles Arduino auprès d'Arduino eux-mêmes ou d'autres fabricants, puis coder en utilisant le framework Arduino.

Les cartes Arduino sont programmées en C ou C++. L'utilisation de C/C++ permet de compiler votre code de manière très compacte et rapide, ce qui est nécessaire sur un appareil contraint comme un microcontrôleur. Le cœur d'une application Arduino est appelé un sketch et est un code C/C++ avec 2 fonctions - `setup` et `loop`. Lorsque la carte démarre, le code du framework Arduino exécute la fonction `setup` une fois, puis exécute la fonction `loop` en continu jusqu'à ce que l'alimentation soit coupée.

Vous écririez votre code d'initialisation dans la fonction `setup`, comme la connexion au WiFi et aux services cloud ou l'initialisation des broches pour l'entrée et la sortie. Votre code de traitement serait ensuite placé dans la fonction `loop`, comme la lecture d'un capteur et l'envoi de la valeur au cloud. Vous incluriez normalement un délai dans chaque boucle, par exemple, si vous souhaitez envoyer des données de capteur toutes les 10 secondes, vous ajouteriez un délai de 10 secondes à la fin de la boucle pour que le microcontrôleur puisse dormir, économisant ainsi de l'énergie, puis exécuter la boucle à nouveau 10 secondes plus tard.

![Un sketch Arduino exécutant d'abord setup, puis loop en continu](../../../../../translated_images/fr/arduino-sketch.79590cb837ff7a7c.webp)

✅ Cette architecture de programme est connue sous le nom de *boucle d'événements* ou *boucle de messages*. De nombreuses applications utilisent ce modèle en arrière-plan, et c'est la norme pour la plupart des applications de bureau fonctionnant sur des OS comme Windows, macOS ou Linux. La fonction `loop` écoute les messages provenant de composants d'interface utilisateur tels que des boutons, ou d'appareils comme le clavier, et y répond. Vous pouvez en lire davantage dans cet [article sur la boucle d'événements](https://wikipedia.org/wiki/Event_loop).

Arduino fournit des bibliothèques standard pour interagir avec les microcontrôleurs et les broches d'E/S, avec différentes implémentations en coulisses pour fonctionner sur différents microcontrôleurs. Par exemple, la fonction [`delay`](https://www.arduino.cc/reference/en/language/functions/time/delay/) met le programme en pause pendant une période donnée, et la fonction [`digitalRead`](https://www.arduino.cc/reference/en/language/functions/digital-io/digitalread/) lit une valeur `HIGH` ou `LOW` à partir de la broche donnée, quelle que soit la carte sur laquelle le code est exécuté. Ces bibliothèques standard signifient que le code Arduino écrit pour une carte peut être recompilé pour toute autre carte Arduino et fonctionnera, à condition que les broches soient les mêmes et que les cartes prennent en charge les mêmes fonctionnalités.

Il existe un vaste écosystème de bibliothèques Arduino tierces qui vous permettent d'ajouter des fonctionnalités supplémentaires à vos projets Arduino, comme l'utilisation de capteurs et d'actionneurs ou la connexion à des services IoT dans le cloud.

##### Tâche

Explorez le terminal Wio.

Si vous utilisez un terminal Wio pour ces leçons, relisez le code que vous avez écrit dans la leçon précédente. Trouvez les fonctions `setup` et `loop`. Surveillez la sortie série pour voir la fonction `loop` être appelée de manière répétée. Essayez d'ajouter du code à la fonction `setup` pour écrire sur le port série et observez que ce code n'est appelé qu'une seule fois à chaque redémarrage. Essayez de redémarrer votre appareil avec l'interrupteur d'alimentation sur le côté pour montrer que ce code est appelé à chaque redémarrage de l'appareil.

## Approfondissement sur les ordinateurs monocartes

Dans la leçon précédente, nous avons introduit les ordinateurs monocartes. Regardons-les maintenant de plus près.

### Raspberry Pi

![Le logo Raspberry Pi](../../../../../translated_images/fr/raspberry-pi-logo.4efaa16605cee054.webp)

La [Raspberry Pi Foundation](https://www.raspberrypi.org) est une organisation caritative basée au Royaume-Uni, fondée en 2009 pour promouvoir l'étude de l'informatique, en particulier au niveau scolaire. Dans le cadre de cette mission, ils ont développé un ordinateur monocarte, appelé Raspberry Pi. Les Raspberry Pi sont actuellement disponibles en 3 variantes : une version pleine taille, le plus petit Pi Zero, et un module de calcul qui peut être intégré dans votre appareil IoT final.

![Un Raspberry Pi 4](../../../../../translated_images/fr/raspberry-pi-4.fd4590d308c3d456.webp)

La dernière version du Raspberry Pi pleine taille est le Raspberry Pi 4B. Il dispose d'un processeur quad-core (4 cœurs) fonctionnant à 1,5 GHz, de 2, 4 ou 8 Go de RAM, d'un port Ethernet gigabit, du WiFi, de 2 ports HDMI prenant en charge des écrans 4K, d'une sortie audio et vidéo composite, de ports USB (2 USB 2.0, 2 USB 3.0), de 40 broches GPIO, d'un connecteur pour module caméra Raspberry Pi, et d'un emplacement pour carte SD. Tout cela sur une carte de 88 mm x 58 mm x 19,5 mm, alimentée par un adaptateur USB-C de 3A. Ces cartes commencent à 35 USD, bien moins cher qu'un PC ou un Mac.

> 💁 Il existe également un Pi400, un ordinateur tout-en-un avec un Pi4 intégré dans un clavier.

![Un Raspberry Pi Zero](../../../../../translated_images/fr/raspberry-pi-zero.f7a4133e1e7d54bb.webp)

Le Pi Zero est beaucoup plus petit et moins puissant. Il dispose d'un processeur monocœur de 1 GHz, de 512 Mo de RAM, du WiFi (dans le modèle Zero W), d'un seul port HDMI, d'un port micro-USB, de 40 broches GPIO, d'un connecteur pour module caméra Raspberry Pi, et d'un emplacement pour carte SD. Il mesure 65 mm x 30 mm x 5 mm et consomme très peu d'énergie. Le Zero coûte 5 USD, et la version W avec WiFi coûte 10 USD.

> 🎓 Les processeurs des deux modèles sont des processeurs ARM, contrairement aux processeurs Intel/AMD x86 ou x64 que l'on trouve dans la plupart des PC et Mac. Ils sont similaires aux processeurs que l'on trouve dans certains microcontrôleurs, ainsi que dans presque tous les téléphones mobiles, le Microsoft Surface X, et les nouveaux Mac d'Apple basés sur Apple Silicon.

Toutes les variantes du Raspberry Pi fonctionnent avec une version de Debian Linux appelée Raspberry Pi OS. Celle-ci est disponible en version légère sans interface graphique, idéale pour les projets "headless" où un écran n'est pas nécessaire, ou en version complète avec un environnement de bureau complet, incluant un navigateur web, des applications bureautiques, des outils de codage et des jeux. Comme l'OS est une version de Debian Linux, vous pouvez installer n'importe quelle application ou outil fonctionnant sur Debian et conçu pour le processeur ARM du Pi.

#### Tâche

Explorez le Raspberry Pi.

Si vous utilisez un Raspberry Pi pour ces leçons, renseignez-vous sur les différents composants matériels de la carte.

* Vous pouvez trouver des détails sur les processeurs utilisés sur la [page de documentation matérielle du Raspberry Pi](https://www.raspberrypi.org/documentation/hardware/raspberrypi/). Lisez les informations sur le processeur utilisé dans le modèle de Pi que vous utilisez.
* Localisez les broches GPIO. Lisez-en davantage à leur sujet dans la [documentation GPIO du Raspberry Pi](https://www.raspberrypi.org/documentation/hardware/raspberrypi/gpio/README.md). Utilisez le [guide d'utilisation des broches GPIO](https://www.raspberrypi.org/documentation/usage/gpio/README.md) pour identifier les différentes broches de votre Pi.

### Programmation des ordinateurs monocartes

Les ordinateurs monocartes sont de véritables ordinateurs, fonctionnant avec un OS complet. Cela signifie qu'il existe une large gamme de langages de programmation, frameworks et outils que vous pouvez utiliser pour les coder, contrairement aux microcontrôleurs qui dépendent du support de la carte dans des frameworks comme Arduino. La plupart des langages de programmation disposent de bibliothèques permettant d'accéder aux broches GPIO pour envoyer et recevoir des données des capteurs et actionneurs.

✅ Quels langages de programmation connaissez-vous ? Sont-ils pris en charge sur Linux ?

Le langage de programmation le plus courant pour développer des applications IoT sur un Raspberry Pi est Python. Il existe un vaste écosystème de matériel conçu pour le Pi, et presque tous incluent le code nécessaire pour les utiliser sous forme de bibliothèques Python. Certains de ces écosystèmes sont basés sur des "hats" - ainsi nommés car ils se posent sur le Pi comme un chapeau et se connectent via un grand connecteur aux 40 broches GPIO. Ces hats offrent des capacités supplémentaires, comme des écrans, des capteurs, des voitures télécommandées, ou des adaptateurs permettant de brancher des capteurs avec des câbles standardisés.
### Utilisation des ordinateurs monocartes dans les déploiements IoT professionnels

Les ordinateurs monocartes sont utilisés dans les déploiements IoT professionnels, et pas seulement comme kits de développement. Ils peuvent offrir une solution puissante pour contrôler du matériel et exécuter des tâches complexes, comme l'exécution de modèles d'apprentissage automatique. Par exemple, il existe un [module de calcul Raspberry Pi 4](https://www.raspberrypi.org/blog/raspberry-pi-compute-module-4/) qui offre toute la puissance d'un Raspberry Pi 4, mais dans un format compact et moins coûteux, sans la plupart des ports, conçu pour être intégré dans du matériel personnalisé.

---

## 🚀 Défi

Le défi de la dernière leçon était de lister autant de dispositifs IoT que possible présents chez vous, à l'école ou sur votre lieu de travail. Pour chaque dispositif de cette liste, pensez-vous qu'ils sont basés sur des microcontrôleurs, des ordinateurs monocartes, ou même un mélange des deux ?

## Quiz après le cours

[Quiz après le cours](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/4)

## Révision et auto-apprentissage

* Lisez le [guide de démarrage Arduino](https://www.arduino.cc/en/Guide/Introduction) pour en savoir plus sur la plateforme Arduino.
* Lisez l’[introduction au Raspberry Pi 4](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/) pour en apprendre davantage sur les Raspberry Pi.
* Approfondissez certains concepts et acronymes dans l’article [What the FAQ are CPUs, MPUs, MCUs, and GPUs dans le Electrical Engineering Journal](https://www.eejournal.com/article/what-the-faq-are-cpus-mpus-mcus-and-gpus/).

✅ Utilisez ces guides, ainsi que les coûts indiqués en suivant les liens dans le [guide matériel](../../../hardware.md), pour décider de la plateforme matérielle que vous souhaitez utiliser, ou si vous préférez utiliser un dispositif virtuel.

## Devoir

[Comparer et contraster les microcontrôleurs et les ordinateurs monocartes](assignment.md)

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.