# Matériel

Le **T** dans IoT signifie **Things** (Objets) et fait référence aux dispositifs qui interagissent avec le monde qui nous entoure. Chaque projet repose sur du matériel réel accessible aux étudiants et amateurs. Nous proposons deux choix de matériel IoT en fonction des préférences personnelles, des connaissances ou préférences en langage de programmation, des objectifs d'apprentissage et de la disponibilité. Une version de "matériel virtuel" est également disponible pour ceux qui n'ont pas accès au matériel ou qui souhaitent en apprendre davantage avant de s'engager dans un achat.

> 💁 Vous n'avez pas besoin d'acheter de matériel IoT pour réaliser les exercices. Vous pouvez tout faire en utilisant du matériel IoT virtuel.

Les choix de matériel physique sont Arduino ou Raspberry Pi. Chaque plateforme a ses avantages et inconvénients, qui sont abordés dans l'une des premières leçons. Si vous n'avez pas encore choisi une plateforme matérielle, vous pouvez consulter [la leçon deux du premier projet](./1-getting-started/lessons/2-deeper-dive/README.md) pour décider laquelle vous intéresse le plus.

Le matériel spécifique a été choisi pour réduire la complexité des leçons et des exercices. Bien que d'autres matériels puissent fonctionner, nous ne pouvons pas garantir que tous les exercices seront compatibles avec votre appareil sans matériel supplémentaire. Par exemple, de nombreux appareils Arduino n'ont pas de WiFi, ce qui est nécessaire pour se connecter au cloud - le terminal Wio a été choisi car il intègre le WiFi.

Vous aurez également besoin de quelques éléments non techniques, comme de la terre ou une plante en pot, ainsi que des fruits ou légumes.

## Acheter les kits

![Le logo de Seeed Studios](../../translated_images/fr/seeed-logo.74732b6b482b6e8e.webp)

Seeed Studios a gentiment mis à disposition tout le matériel sous forme de kits faciles à acheter :

### Arduino - Wio Terminal

**[IoT pour débutants avec Seeed et Microsoft - Kit de démarrage Wio Terminal](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)**

[![Le kit matériel Wio Terminal](../../translated_images/fr/wio-hardware-kit.4c70c48b85e4283a.webp)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)

### Raspberry Pi

**[IoT pour débutants avec Seeed et Microsoft - Kit de démarrage Raspberry Pi 4](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)**

[![Le kit matériel Raspberry Pi Terminal](../../translated_images/fr/pi-hardware-kit.26dbadaedb7dd44c.webp)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)

## Arduino

Tout le code pour les appareils Arduino est écrit en C++. Pour réaliser tous les exercices, vous aurez besoin des éléments suivants :

### Matériel Arduino

* [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html)
* *Optionnel* - Câble USB-C ou adaptateur USB-A vers USB-C. Le terminal Wio dispose d'un port USB-C et est livré avec un câble USB-C vers USB-A. Si votre PC ou Mac ne dispose que de ports USB-C, vous aurez besoin d'un câble USB-C ou d'un adaptateur USB-A vers USB-C.

### Capteurs et actionneurs spécifiques à Arduino

Ces éléments sont spécifiques à l'utilisation du terminal Wio Arduino et ne sont pas pertinents pour l'utilisation du Raspberry Pi.

* [ArduCam Mini 2MP Plus - OV2640](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/)
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)
* [Fils de connexion pour breadboard](https://www.seeedstudio.com/Breadboard-Jumper-Wire-Pack-241mm-200mm-160mm-117m-p-234.html)
* Casque ou autre haut-parleur avec une prise jack 3,5 mm, ou un haut-parleur JST tel que :
  * [Haut-parleur mono fermé - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
* Carte microSD de 16 Go ou moins, ainsi qu'un connecteur pour utiliser la carte SD avec votre ordinateur si vous n'en avez pas un intégré. **NOTE** - le terminal Wio ne prend en charge que les cartes SD jusqu'à 16 Go, il ne prend pas en charge des capacités supérieures.

## Raspberry Pi

Tout le code pour les appareils Raspberry Pi est écrit en Python. Pour réaliser tous les exercices, vous aurez besoin des éléments suivants :

### Matériel Raspberry Pi

* [Raspberry Pi](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/)
  > 💁 Les versions à partir du Pi 2B devraient fonctionner avec les exercices de ces leçons. Si vous prévoyez d'exécuter VS Code directement sur le Pi, un Pi 4 avec 2 Go ou plus de RAM est nécessaire. Si vous accédez au Pi à distance, tout Pi 2B ou supérieur fonctionnera.
* Carte microSD (Vous pouvez obtenir des kits Raspberry Pi qui incluent une carte microSD), ainsi qu'un connecteur pour utiliser la carte SD avec votre ordinateur si vous n'en avez pas un intégré.
* Alimentation USB (Vous pouvez obtenir des kits Raspberry Pi 4 qui incluent une alimentation). Si vous utilisez un Raspberry Pi 4, vous aurez besoin d'une alimentation USB-C, les appareils plus anciens nécessitent une alimentation micro-USB.

### Capteurs et actionneurs spécifiques au Raspberry Pi

Ces éléments sont spécifiques à l'utilisation du Raspberry Pi et ne sont pas pertinents pour l'utilisation de l'appareil Arduino.

* [Chapeau de base Grove Pi](https://www.seeedstudio.com/Grove-Base-Hat-for-Raspberry-Pi.html)
* [Module caméra Raspberry Pi](https://www.raspberrypi.org/products/camera-module-v2/)
* Microphone et haut-parleur :

  Utilisez l'un des éléments suivants (ou équivalent) :
  * Tout microphone USB avec tout haut-parleur USB, ou haut-parleur avec un câble jack 3,5 mm, ou sortie audio HDMI si votre Raspberry Pi est connecté à un moniteur ou une TV avec haut-parleurs
  * Tout casque USB avec microphone intégré
  * [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) avec
    * Casque ou autre haut-parleur avec une prise jack 3,5 mm, ou un haut-parleur JST tel que :
    * [Haut-parleur mono fermé - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
  * [Haut-parleur USB pour conférence](https://www.amazon.com/USB-Speakerphone-Conference-Business-Microphones/dp/B07Q3D7F8S/ref=sr_1_1?dchild=1&keywords=m0&qid=1614647389&sr=8-1)
* [Capteur de lumière Grove](https://www.seeedstudio.com/Grove-Light-Sensor-v1-2-LS06-S-phototransistor.html)
* [Bouton Grove](https://www.seeedstudio.com/Grove-Button.html)

## Capteurs et actionneurs

La plupart des capteurs et actionneurs nécessaires sont utilisés à la fois par les parcours d'apprentissage Arduino et Raspberry Pi :

* [LED Grove](https://www.seeedstudio.com/Grove-LED-Pack-p-4364.html) x 2
* [Capteur d'humidité et de température Grove](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html)
* [Capteur capacitif d'humidité du sol Grove](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html)
* [Relais Grove](https://www.seeedstudio.com/Grove-Relay.html)
* [GPS Grove (Air530)](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html)
* [Capteur de distance Time of Flight Grove](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html)

## Matériel optionnel

Les leçons sur l'arrosage automatisé fonctionnent avec un relais. En option, vous pouvez connecter ce relais à une pompe à eau alimentée par USB en utilisant le matériel ci-dessous.

* [Pompe à eau 6V](https://www.seeedstudio.com/6V-Mini-Water-Pump-p-1945.html)
* [Terminal USB](https://www.adafruit.com/product/3628)
* Tuyaux en silicone
* Fils rouge et noir
* Petit tournevis plat

## Matériel virtuel

La voie du matériel virtuel propose des simulateurs pour les capteurs et actionneurs, implémentés en Python. Selon la disponibilité de votre matériel, vous pouvez exécuter cela sur votre appareil de développement habituel, comme un Mac, un PC, ou sur un Raspberry Pi et simuler uniquement le matériel que vous n'avez pas. Par exemple, si vous avez la caméra Raspberry Pi mais pas les capteurs Grove, vous pourrez exécuter le code de l'appareil virtuel sur votre Pi et simuler les capteurs Grove, tout en utilisant une caméra physique.

Le matériel virtuel utilisera le projet [CounterFit](https://github.com/CounterFit-IoT/CounterFit).

Pour compléter ces leçons, vous devrez disposer d'une webcam, d'un microphone et d'une sortie audio comme des haut-parleurs ou un casque. Ces éléments peuvent être intégrés ou externes, et doivent être configurés pour fonctionner avec votre système d'exploitation et être disponibles pour toutes les applications.

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.