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