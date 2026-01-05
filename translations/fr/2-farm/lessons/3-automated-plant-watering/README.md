<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f7bb24ba53fb627ddb38a8b24a05e594",
  "translation_date": "2025-08-24T22:11:35+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/README.md",
  "language_code": "fr"
}
-->
# Arrosage automatisé des plantes

![Un aperçu en sketchnote de cette leçon](../../../../../translated_images/lesson-7.30b5f577d3cb8e031238751475cb519c7d6dbaea261b5df4643d086ffb2a03bb.fr.jpg)

> Sketchnote par [Nitya Narasimhan](https://github.com/nitya). Cliquez sur l'image pour une version agrandie.

Cette leçon a été enseignée dans le cadre de la série [IoT pour les débutants - Agriculture numérique, Projet 2](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) du [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn).

[![Arrosage automatisé des plantes alimenté par IoT](https://img.youtube.com/vi/g9FfZwv9R58/0.jpg)](https://youtu.be/g9FfZwv9R58)

## Quiz avant la leçon

[Quiz avant la leçon](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/13)

## Introduction

Dans la dernière leçon, vous avez appris à surveiller l'humidité du sol. Dans cette leçon, vous apprendrez à construire les composants principaux d'un système d'arrosage automatisé qui réagit à l'humidité du sol. Vous découvrirez également le concept de temporisation : comment les capteurs peuvent mettre du temps à répondre aux changements et comment les actionneurs peuvent prendre du temps pour modifier les propriétés mesurées par les capteurs.

Dans cette leçon, nous aborderons :

* [Contrôler des appareils à haute puissance avec un appareil IoT à faible puissance](../../../../../2-farm/lessons/3-automated-plant-watering)
* [Contrôler un relais](../../../../../2-farm/lessons/3-automated-plant-watering)
* [Contrôler votre plante via MQTT](../../../../../2-farm/lessons/3-automated-plant-watering)
* [Synchronisation des capteurs et des actionneurs](../../../../../2-farm/lessons/3-automated-plant-watering)
* [Ajouter une temporisation à votre serveur de contrôle des plantes](../../../../../2-farm/lessons/3-automated-plant-watering)

## Contrôler des appareils à haute puissance avec un appareil IoT à faible puissance

Les appareils IoT utilisent une basse tension. Bien que cela suffise pour les capteurs et les actionneurs à faible puissance comme les LED, cette tension est trop faible pour contrôler des équipements plus grands, tels qu'une pompe à eau utilisée pour l'irrigation. Même les petites pompes que vous pourriez utiliser pour des plantes d'intérieur consomment trop de courant pour un kit de développement IoT et risqueraient de griller la carte.

> 🎓 Le courant, mesuré en ampères (A), représente la quantité d'électricité circulant dans un circuit. La tension fournit la poussée, le courant indique combien est poussé. Vous pouvez en apprendre davantage sur le courant sur la [page Wikipédia sur le courant électrique](https://wikipedia.org/wiki/Electric_current).

La solution consiste à connecter une pompe à une alimentation externe et à utiliser un actionneur pour allumer la pompe, de la même manière que vous allumeriez une lumière. Il faut une très petite quantité d'énergie (sous forme d'énergie corporelle) pour que votre doigt actionne un interrupteur, ce qui connecte la lumière à l'électricité domestique fonctionnant à 110v/240v.

![Un interrupteur allume une lumière](../../../../../translated_images/light-switch.760317ad6ab8bd6d611da5352dfe9c73a94a0822ccec7df3c8bae35da18e1658.fr.png)

> 🎓 [L'électricité domestique](https://wikipedia.org/wiki/Mains_electricity) fait référence à l'électricité distribuée aux maisons et aux entreprises via des infrastructures nationales dans de nombreuses régions du monde.

✅ Les appareils IoT peuvent généralement fournir 3,3V ou 5V, avec moins de 1 ampère (1A) de courant. Comparez cela à l'électricité domestique, qui est le plus souvent à 230V (120V en Amérique du Nord et 100V au Japon), et peut alimenter des appareils consommant jusqu'à 30A.

Il existe plusieurs types d'actionneurs capables de réaliser cette tâche, y compris des dispositifs mécaniques que vous pouvez fixer à des interrupteurs existants pour imiter un doigt les actionnant. Le plus populaire est le relais.

### Relais

Un relais est un interrupteur électromécanique qui convertit un signal électrique en un mouvement mécanique permettant d'activer un interrupteur. Le cœur d'un relais est un électroaimant.

> 🎓 [Les électroaimants](https://wikipedia.org/wiki/Electromagnet) sont des aimants créés en faisant passer de l'électricité dans une bobine de fil. Lorsque l'électricité est activée, la bobine devient magnétisée. Lorsque l'électricité est coupée, la bobine perd son magnétisme.

![Lorsque le relais est activé, l'électroaimant crée un champ magnétique, activant l'interrupteur du circuit de sortie](../../../../../translated_images/relay-on.4db16a0fd6b66926.fr.png)

Dans un relais, un circuit de commande alimente l'électroaimant. Lorsque l'électroaimant est activé, il tire un levier qui déplace un interrupteur, fermant une paire de contacts et complétant un circuit de sortie.

![Lorsque le relais est désactivé, l'électroaimant ne crée pas de champ magnétique, désactivant l'interrupteur du circuit de sortie](../../../../../translated_images/relay-off.c34a178a2960fecd.fr.png)

Lorsque le circuit de commande est désactivé, l'électroaimant s'éteint, libérant le levier et ouvrant les contacts, désactivant le circuit de sortie. Les relais sont des actionneurs numériques : un signal élevé active le relais, un signal faible le désactive.

Le circuit de sortie peut être utilisé pour alimenter du matériel supplémentaire, comme un système d'irrigation. L'appareil IoT peut activer le relais, complétant le circuit de sortie qui alimente le système d'irrigation, et les plantes sont arrosées. L'appareil IoT peut ensuite désactiver le relais, coupant l'alimentation du système d'irrigation et arrêtant l'eau.

![Un relais activé, mettant en marche une pompe qui envoie de l'eau à une plante](../../../../../images/strawberry-pump.gif)

Dans la vidéo ci-dessus, un relais est activé. Une LED sur le relais s'allume pour indiquer qu'il est activé (certains modules de relais ont des LEDs pour indiquer si le relais est activé ou désactivé), et l'alimentation est envoyée à la pompe, la mettant en marche et pompant de l'eau vers une plante.

> 💁 Les relais peuvent également être utilisés pour basculer entre deux circuits de sortie au lieu d'en activer ou désactiver un. Lorsque le levier se déplace, il déplace un interrupteur qui complète un circuit de sortie différent, partageant généralement une connexion d'alimentation ou une connexion de masse commune.

✅ Faites des recherches : Il existe plusieurs types de relais, avec des différences telles que si le circuit de commande active ou désactive le relais lorsque l'alimentation est appliquée, ou la présence de plusieurs circuits de sortie. Renseignez-vous sur ces différents types.

Lorsque le levier se déplace, vous pouvez généralement entendre un clic bien défini lorsqu'il entre en contact avec l'électroaimant.

> 💁 Un relais peut être câblé de manière à ce que la connexion coupe en réalité l'alimentation du relais, désactivant le relais, ce qui envoie ensuite de l'alimentation au relais pour le réactiver, et ainsi de suite. Cela signifie que le relais cliquera très rapidement, produisant un bruit de bourdonnement. C'est ainsi que certains des premiers sonnettes électriques fonctionnaient.

### Puissance du relais

L'électroaimant n'a pas besoin de beaucoup de puissance pour s'activer et tirer le levier, il peut être contrôlé en utilisant la sortie 3,3V ou 5V d'un kit de développement IoT. Le circuit de sortie peut transporter beaucoup plus de puissance, selon le relais, y compris la tension domestique ou même des niveaux de puissance plus élevés pour une utilisation industrielle. Ainsi, un kit de développement IoT peut contrôler un système d'irrigation, allant d'une petite pompe pour une seule plante à un système industriel massif pour une ferme commerciale entière.

![Un relais Grove avec le circuit de commande, le circuit de sortie et le relais étiquetés](../../../../../translated_images/grove-relay-labelled.293e068f5c3c2a199bd7892f2661fdc9e10c920b535cfed317fbd6d1d4ae1168.fr.png)

L'image ci-dessus montre un relais Grove. Le circuit de commande se connecte à un appareil IoT et active ou désactive le relais en utilisant 3,3V ou 5V. Le circuit de sortie a deux bornes, l'une pouvant être l'alimentation ou la masse. Le circuit de sortie peut gérer jusqu'à 250V à 10A, suffisant pour une gamme d'appareils alimentés par le secteur. Vous pouvez trouver des relais capables de gérer des niveaux de puissance encore plus élevés.

![Une pompe câblée via un relais](../../../../../translated_images/pump-wired-to-relay.66c5cfc0d8918990.fr.png)

Dans l'image ci-dessus, l'alimentation est fournie à une pompe via un relais. Un fil rouge connecte la borne +5V d'une alimentation USB à une borne du circuit de sortie du relais, et un autre fil rouge connecte l'autre borne du circuit de sortie à la pompe. Un fil noir connecte la pompe à la masse de l'alimentation USB. Lorsque le relais s'active, il complète le circuit, envoyant 5V à la pompe et la mettant en marche.

## Contrôler un relais

Vous pouvez contrôler un relais depuis votre kit de développement IoT.

### Tâche - contrôler un relais

Suivez le guide correspondant pour contrôler un relais avec votre appareil IoT :

* [Arduino - Wio Terminal](wio-terminal-relay.md)
* [Ordinateur monocarte - Raspberry Pi](pi-relay.md)
* [Ordinateur monocarte - Appareil virtuel](virtual-device-relay.md)

## Contrôler votre plante via MQTT

Jusqu'à présent, votre relais est contrôlé directement par l'appareil IoT en fonction d'une seule lecture d'humidité du sol. Dans un système d'irrigation commercial, la logique de contrôle sera centralisée, permettant de prendre des décisions d'arrosage en utilisant les données de plusieurs capteurs et de modifier toute configuration en un seul endroit. Pour simuler cela, vous pouvez contrôler le relais via MQTT.

### Tâche - contrôler le relais via MQTT

1. Ajoutez les bibliothèques MQTT/pip nécessaires et le code à votre projet `soil-moisture-sensor` pour vous connecter à MQTT. Nommez l'ID client `soilmoisturesensor_client` précédé de votre ID.

    > ⚠️ Vous pouvez vous référer aux [instructions pour se connecter à MQTT dans le projet 1, leçon 4 si nécessaire](../../../1-getting-started/lessons/4-connect-internet/README.md#connect-your-iot-device-to-mqtt).

1. Ajoutez le code de l'appareil nécessaire pour envoyer des télémétries avec les paramètres d'humidité du sol. Pour le message de télémétrie, nommez la propriété `soil_moisture`.

    > ⚠️ Vous pouvez vous référer aux [instructions pour envoyer des télémétries à MQTT dans le projet 1, leçon 4 si nécessaire](../../../1-getting-started/lessons/4-connect-internet/README.md#send-telemetry-from-your-iot-device).

1. Créez un code serveur local pour s'abonner aux télémétries et envoyer une commande pour contrôler le relais dans un dossier appelé `soil-moisture-sensor-server`. Nommez la propriété dans le message de commande `relay_on`, et définissez l'ID client comme `soilmoisturesensor_server` précédé de votre ID. Gardez la même structure que le code serveur que vous avez écrit pour le projet 1, leçon 4, car vous ajouterez à ce code plus tard dans cette leçon.

    > ⚠️ Vous pouvez vous référer aux [instructions pour envoyer des télémétries à MQTT](../../../1-getting-started/lessons/4-connect-internet/README.md#write-the-server-code) et [envoyer des commandes via MQTT](../../../1-getting-started/lessons/4-connect-internet/README.md#send-commands-to-the-mqtt-broker) dans le projet 1, leçon 4 si nécessaire.

1. Ajoutez le code de l'appareil nécessaire pour contrôler le relais à partir des commandes reçues, en utilisant la propriété `relay_on` du message. Envoyez `true` pour `relay_on` si l'humidité du sol (`soil_moisture`) est supérieure à 450, sinon envoyez `false`, comme la logique que vous avez ajoutée pour l'appareil IoT précédemment.

    > ⚠️ Vous pouvez vous référer aux [instructions pour répondre aux commandes de MQTT dans le projet 1, leçon 4 si nécessaire](../../../1-getting-started/lessons/4-connect-internet/README.md#handle-commands-on-the-iot-device).

> 💁 Vous pouvez trouver ce code dans le dossier [code-mqtt](../../../../../2-farm/lessons/3-automated-plant-watering/code-mqtt).

Assurez-vous que le code fonctionne sur votre appareil et serveur local, et testez-le en modifiant les niveaux d'humidité du sol, soit en changeant les valeurs envoyées par le capteur virtuel, soit en modifiant les niveaux d'humidité du sol en ajoutant de l'eau ou en retirant le capteur du sol.

## Synchronisation des capteurs et des actionneurs

Dans la leçon 3, vous avez construit une veilleuse - une LED qui s'allume dès qu'un faible niveau de lumière est détecté par un capteur de lumière. Le capteur de lumière détectait instantanément un changement de niveau de lumière, et l'appareil pouvait répondre rapidement, uniquement limité par la durée du délai dans la fonction `loop` ou la boucle `while True:`. En tant que développeur IoT, vous ne pouvez pas toujours compter sur une boucle de rétroaction aussi rapide.

### Temporisation pour l'humidité du sol

Si vous avez suivi la dernière leçon sur l'humidité du sol en utilisant un capteur physique, vous avez peut-être remarqué qu'il fallait quelques secondes pour que la lecture de l'humidité du sol diminue après avoir arrosé votre plante. Cela n'est pas dû à la lenteur du capteur, mais au temps nécessaire pour que l'eau s'infiltre dans le sol.
💁 Si vous avez arrosé trop près du capteur, vous avez peut-être remarqué que la lecture a chuté rapidement, puis est remontée - cela est dû à l'eau près du capteur qui se diffuse dans le reste du sol, réduisant ainsi l'humidité du sol autour du capteur.
![Une mesure d'humidité du sol de 658 ne change pas pendant l'arrosage, elle ne descend qu'à 320 après l'arrosage lorsque l'eau a traversé le sol](../../../../../translated_images/soil-moisture-travel.a0e31af222cf1438.fr.png)

Dans le schéma ci-dessus, une lecture d'humidité du sol indique 658. La plante est arrosée, mais cette lecture ne change pas immédiatement, car l'eau n'a pas encore atteint le capteur. L'arrosage peut même se terminer avant que l'eau n'atteigne le capteur et que la valeur ne baisse pour refléter le nouveau niveau d'humidité.

Si vous écriviez un code pour contrôler un système d'irrigation via un relais basé sur les niveaux d'humidité du sol, vous devriez prendre ce délai en compte et intégrer une gestion plus intelligente du timing dans votre appareil IoT.

✅ Prenez un moment pour réfléchir à la manière dont vous pourriez gérer cela.

### Contrôler le timing des capteurs et des actionneurs

Imaginez que vous avez pour mission de construire un système d'irrigation pour une ferme. En fonction du type de sol, le niveau d'humidité idéal pour les plantes cultivées correspond à une lecture de tension analogique de 400-450.

Vous pourriez programmer l'appareil de la même manière qu'une veilleuse : tant que le capteur lit une valeur supérieure à 450, activez un relais pour allumer une pompe. Le problème est que l'eau met du temps à passer de la pompe, à travers le sol, jusqu'au capteur. Le capteur arrêtera l'eau lorsqu'il détectera un niveau de 450, mais le niveau d'eau continuera de baisser car l'eau pompée continue de s'infiltrer dans le sol. Le résultat final est un gaspillage d'eau et un risque de dommages aux racines.

✅ Rappelez-vous : trop d'eau peut être aussi néfaste pour les plantes que trop peu, et cela gaspille une ressource précieuse.

La meilleure solution est de comprendre qu'il y a un délai entre l'activation de l'actionneur et le changement de la propriété mesurée par le capteur. Cela signifie que non seulement le capteur doit attendre un moment avant de mesurer à nouveau la valeur, mais que l'actionneur doit également s'éteindre pendant un certain temps avant la prochaine mesure du capteur.

Combien de temps le relais doit-il rester activé à chaque fois ? Il vaut mieux pécher par excès de prudence et n'activer le relais que pour une courte durée, puis attendre que l'eau s'infiltre, avant de vérifier à nouveau les niveaux d'humidité. Après tout, vous pouvez toujours rallumer la pompe pour ajouter plus d'eau, mais vous ne pouvez pas retirer l'eau du sol.

> 💁 Ce type de contrôle du timing est très spécifique à l'appareil IoT que vous construisez, à la propriété que vous mesurez et aux capteurs et actionneurs utilisés.

![Un plant de fraise connecté à de l'eau via une pompe, avec la pompe connectée à un relais. Le relais et un capteur d'humidité du sol dans la plante sont tous deux connectés à un Raspberry Pi](../../../../../translated_images/strawberry-with-pump.b410fc72ac6aabad.fr.png)

Par exemple, j'ai un plant de fraise avec un capteur d'humidité du sol et une pompe contrôlée par un relais. J'ai observé que lorsque j'ajoute de l'eau, il faut environ 20 secondes pour que la lecture d'humidité du sol se stabilise. Cela signifie que je dois éteindre le relais et attendre 20 secondes avant de vérifier les niveaux d'humidité. Je préfère avoir trop peu d'eau que trop - je peux toujours rallumer la pompe, mais je ne peux pas retirer l'eau de la plante.

![Étape 1, prendre une mesure. Étape 2, ajouter de l'eau. Étape 3, attendre que l'eau s'infiltre dans le sol. Étape 4, reprendre une mesure](../../../../../translated_images/soil-moisture-delay.865f3fae206db01d.fr.png)

Cela signifie que le meilleur processus serait un cycle d'arrosage ressemblant à ceci :

* Allumer la pompe pendant 5 secondes  
* Attendre 20 secondes  
* Vérifier l'humidité du sol  
* Si le niveau est encore au-dessus de ce dont j'ai besoin, répéter les étapes ci-dessus  

5 secondes pourraient être trop longues pour la pompe, surtout si les niveaux d'humidité sont juste légèrement au-dessus du niveau requis. La meilleure façon de déterminer le timing à utiliser est de tester, puis d'ajuster en fonction des données du capteur, avec une boucle de rétroaction constante. Cela peut même conduire à un timing plus précis, comme allumer la pompe pendant 1 seconde pour chaque 100 au-dessus du niveau d'humidité requis, au lieu d'un temps fixe de 5 secondes.

✅ Faites des recherches : Y a-t-il d'autres considérations de timing ? La plante peut-elle être arrosée à tout moment lorsque l'humidité du sol est trop basse, ou y a-t-il des moments spécifiques de la journée qui sont bons ou mauvais pour arroser les plantes ?

> 💁 Les prévisions météorologiques peuvent également être prises en compte lors du contrôle des systèmes d'arrosage automatisés pour les cultures en extérieur. Si de la pluie est prévue, l'arrosage peut être suspendu jusqu'à ce que la pluie soit terminée. À ce moment-là, le sol peut être suffisamment humide pour ne pas nécessiter d'arrosage, ce qui est bien plus efficace que de gaspiller de l'eau en arrosant juste avant la pluie.

## Ajouter du timing à votre serveur de contrôle des plantes

Le code du serveur peut être modifié pour ajouter un contrôle autour du timing du cycle d'arrosage et attendre que les niveaux d'humidité du sol changent. La logique du serveur pour contrôler le timing du relais est la suivante :

1. Message de télémétrie reçu  
1. Vérifier le niveau d'humidité du sol  
1. Si tout va bien, ne rien faire. Si la lecture est trop élevée (ce qui signifie que l'humidité du sol est trop basse), alors :  
    1. Envoyer une commande pour activer le relais  
    1. Attendre 5 secondes  
    1. Envoyer une commande pour désactiver le relais  
    1. Attendre 20 secondes pour que les niveaux d'humidité du sol se stabilisent  

Le cycle d'arrosage, le processus allant de la réception du message de télémétrie à la préparation pour traiter à nouveau les niveaux d'humidité du sol, prend environ 25 secondes. Nous envoyons les niveaux d'humidité du sol toutes les 10 secondes, il y a donc un chevauchement où un message est reçu pendant que le serveur attend que les niveaux d'humidité du sol se stabilisent, ce qui pourrait démarrer un autre cycle d'arrosage.

Il existe deux options pour contourner ce problème :

* Modifier le code de l'appareil IoT pour n'envoyer la télémétrie qu'une fois par minute, de sorte que le cycle d'arrosage soit terminé avant l'envoi du message suivant  
* Se désabonner de la télémétrie pendant le cycle d'arrosage  

La première option n'est pas toujours une bonne solution pour les grandes exploitations agricoles. L'agriculteur pourrait vouloir capturer les niveaux d'humidité du sol pendant que le sol est arrosé pour une analyse ultérieure, par exemple pour être conscient du flux d'eau dans différentes zones de la ferme afin de guider un arrosage plus ciblé. La deuxième option est meilleure - le code ignore simplement la télémétrie lorsqu'il ne peut pas l'utiliser, mais la télémétrie est toujours disponible pour d'autres services qui pourraient s'y abonner.

> 💁 Les données IoT ne sont pas envoyées d'un seul appareil à un seul service, mais de nombreux appareils peuvent envoyer des données à un courtier, et de nombreux services peuvent écouter les données provenant du courtier. Par exemple, un service peut écouter les données d'humidité du sol et les stocker dans une base de données pour une analyse ultérieure. Un autre service peut également écouter la même télémétrie pour contrôler un système d'irrigation.

### Tâche - ajouter du timing à votre serveur de contrôle des plantes

Mettez à jour votre code serveur pour faire fonctionner le relais pendant 5 secondes, puis attendre 20 secondes.

1. Ouvrez le dossier `soil-moisture-sensor-server` dans VS Code s'il n'est pas déjà ouvert. Assurez-vous que l'environnement virtuel est activé.  

1. Ouvrez le fichier `app.py`  

1. Ajoutez le code suivant au fichier `app.py` sous les imports existants :  

    ```python
    import threading
    ```  

    Cette instruction importe `threading` des bibliothèques Python, ce qui permet à Python d'exécuter d'autres codes pendant l'attente.  

1. Ajoutez le code suivant avant la fonction `handle_telemetry` qui gère les messages de télémétrie reçus par le code serveur :  

    ```python
    water_time = 5
    wait_time = 20
    ```  

    Cela définit combien de temps le relais doit fonctionner (`water_time`), et combien de temps attendre ensuite pour vérifier l'humidité du sol (`wait_time`).  

1. Sous ce code, ajoutez le suivant :  

    ```python
    def send_relay_command(client, state):
        command = { 'relay_on' : state }
        print("Sending message:", command)
        client.publish(server_command_topic, json.dumps(command))
    ```  

    Ce code définit une fonction appelée `send_relay_command` qui envoie une commande via MQTT pour contrôler le relais. La télémétrie est créée sous forme de dictionnaire, puis convertie en chaîne JSON. La valeur passée dans `state` détermine si le relais doit être activé ou désactivé.  

1. Après la fonction `send_relay_code`, ajoutez le code suivant :  

    ```python
    def control_relay(client):
        print("Unsubscribing from telemetry")
        mqtt_client.unsubscribe(client_telemetry_topic)
    
        send_relay_command(client, True)
        time.sleep(water_time)
        send_relay_command(client, False)
    
        time.sleep(wait_time)
    
        print("Subscribing to telemetry")
        mqtt_client.subscribe(client_telemetry_topic)
    ```  

    Cela définit une fonction pour contrôler le relais en fonction du timing requis. Elle commence par se désabonner de la télémétrie afin que les messages d'humidité du sol ne soient pas traités pendant l'arrosage. Ensuite, elle envoie une commande pour activer le relais. Elle attend ensuite le `water_time` avant d'envoyer une commande pour désactiver le relais. Enfin, elle attend que les niveaux d'humidité du sol se stabilisent pendant `wait_time` secondes. Elle se réabonne ensuite à la télémétrie.  

1. Modifiez la fonction `handle_telemetry` comme suit :  

    ```python
    def handle_telemetry(client, userdata, message):
        payload = json.loads(message.payload.decode())
        print("Message received:", payload)
    
        if payload['soil_moisture'] > 450:
            threading.Thread(target=control_relay, args=(client,)).start()
    ```  

    Ce code vérifie le niveau d'humidité du sol. S'il est supérieur à 450, le sol a besoin d'eau, donc il appelle la fonction `control_relay`. Cette fonction est exécutée sur un thread séparé, fonctionnant en arrière-plan.  

1. Assurez-vous que votre appareil IoT fonctionne, puis exécutez ce code. Modifiez les niveaux d'humidité du sol et observez ce qui se passe avec le relais - il devrait s'allumer pendant 5 secondes, puis rester éteint pendant au moins 20 secondes, ne se rallumant que si les niveaux d'humidité du sol ne sont pas suffisants.  

    ```output
    (.venv) ➜  soil-moisture-sensor-server ✗ python app.py
    Message received: {'soil_moisture': 457}
    Unsubscribing from telemetry
    Sending message: {'relay_on': True}
    Sending message: {'relay_on': False}
    Subscribing to telemetry
    Message received: {'soil_moisture': 302}
    ```  

    Une bonne façon de tester cela dans un système d'irrigation simulé est d'utiliser du sol sec, puis de verser de l'eau manuellement pendant que le relais est activé, en arrêtant de verser lorsque le relais s'éteint.  

> 💁 Vous pouvez trouver ce code dans le dossier [code-timing](../../../../../2-farm/lessons/3-automated-plant-watering/code-timing).  

> 💁 Si vous souhaitez utiliser une pompe pour construire un véritable système d'irrigation, vous pouvez utiliser une [pompe à eau 6V](https://www.seeedstudio.com/6V-Mini-Water-Pump-p-1945.html) avec une [alimentation USB](https://www.adafruit.com/product/3628). Assurez-vous que l'alimentation vers ou depuis la pompe est connectée via le relais.  

---

## 🚀 Défi

Pouvez-vous penser à d'autres appareils IoT ou électriques qui ont un problème similaire où il faut un certain temps pour que les résultats de l'actionneur atteignent le capteur ? Vous en avez probablement quelques-uns chez vous ou à l'école.  

* Quelles propriétés mesurent-ils ?  
* Combien de temps faut-il pour que la propriété change après l'utilisation d'un actionneur ?  
* Est-il acceptable que la propriété dépasse la valeur requise ?  
* Comment peut-elle être ramenée à la valeur requise si nécessaire ?  

## Quiz post-lecture

[Quiz post-lecture](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/14)  

## Révision et auto-apprentissage

* Lisez-en davantage sur les relais, y compris leur utilisation historique dans les centraux téléphoniques, sur la [page Wikipédia des relais](https://wikipedia.org/wiki/Relay).  

## Devoir

[Construire un cycle d'arrosage plus efficace](assignment.md)  

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.