<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4fb20273d299dc8d07a8f06c9cd0cdd9",
  "translation_date": "2025-08-24T22:32:28+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/README.md",
  "language_code": "fr"
}
-->
C, prononcé *I-carré-C*, est un protocole multi-contrôleur et multi-périphérique, où chaque appareil connecté peut agir comme contrôleur ou périphérique en communiquant via le bus I

2</sup>C a des limites de vitesse, avec 3 modes différents fonctionnant à des vitesses fixes. Le plus rapide est le mode Haute Vitesse avec une vitesse maximale de 3,4 Mbps (mégabits par seconde), bien que très peu d'appareils prennent en charge cette vitesse. Par exemple, le Raspberry Pi est limité au mode rapide à 400 Kbps (kilobits par seconde). Le mode standard fonctionne à 100 Kbps.

> 💁 Si vous utilisez un Raspberry Pi avec un chapeau Grove Base comme matériel IoT, vous pourrez voir un certain nombre de prises I<sup>2</sup>C sur la carte que vous pouvez utiliser pour communiquer avec des capteurs I<sup>2</sup>C. Les capteurs analogiques Grove utilisent également I<sup>2</sup>C avec un ADC pour envoyer des valeurs analogiques sous forme de données numériques, donc le capteur de lumière que vous avez utilisé simulait une broche analogique, avec la valeur envoyée via I<sup>2</sup>C car le Raspberry Pi ne prend en charge que les broches numériques.

### Récepteur-transmetteur asynchrone universel (UART)

L’UART implique un circuit physique permettant à deux appareils de communiquer. Chaque appareil dispose de 2 broches de communication - transmission (Tx) et réception (Rx), avec la broche Tx du premier appareil connectée à la broche Rx du second, et la broche Tx du second appareil connectée à la broche Rx du premier. Cela permet d'envoyer des données dans les deux directions.

* L'appareil 1 transmet des données depuis sa broche Tx, qui sont reçues par l'appareil 2 sur sa broche Rx
* L'appareil 1 reçoit des données sur sa broche Rx transmises par l'appareil 2 depuis sa broche Tx

![UART avec la broche Tx d'une puce connectée à la broche Rx d'une autre, et vice versa](../../../../../translated_images/fr/uart.d0dbd3fb9e3728c6.webp)

> 🎓 Les données sont envoyées un bit à la fois, ce qui est connu sous le nom de communication *série*. La plupart des systèmes d'exploitation et des microcontrôleurs disposent de *ports série*, c'est-à-dire de connexions capables d'envoyer et de recevoir des données série accessibles à votre code.

Les appareils UART ont un [débit en bauds](https://wikipedia.org/wiki/Symbol_rate) (également appelé taux de symboles), qui est la vitesse à laquelle les données seront envoyées et reçues en bits par seconde. Un débit en bauds courant est de 9 600, ce qui signifie que 9 600 bits (0 et 1) de données sont envoyés chaque seconde.

L’UART utilise des bits de début et de fin - c’est-à-dire qu’il envoie un bit de début pour indiquer qu’il est sur le point d’envoyer un octet (8 bits) de données, puis un bit de fin après avoir envoyé les 8 bits.

La vitesse de l’UART dépend du matériel, mais même les implémentations les plus rapides ne dépassent pas 6,5 Mbps (mégabits par seconde, ou millions de bits, 0 ou 1, envoyés par seconde).

Vous pouvez utiliser l’UART via des broches GPIO - vous pouvez définir une broche comme Tx et une autre comme Rx, puis les connecter à un autre appareil.

> 💁 Si vous utilisez un Raspberry Pi avec un chapeau Grove Base comme matériel IoT, vous pourrez voir une prise UART sur la carte que vous pouvez utiliser pour communiquer avec des capteurs utilisant le protocole UART.

### Interface périphérique série (SPI)

Le SPI est conçu pour communiquer sur de courtes distances, par exemple sur un microcontrôleur pour dialoguer avec un périphérique de stockage tel qu'une mémoire flash. Il est basé sur un modèle contrôleur/périphérique avec un seul contrôleur (généralement le processeur de l'appareil IoT) interagissant avec plusieurs périphériques. Le contrôleur contrôle tout en sélectionnant un périphérique et en envoyant ou demandant des données.

> 💁 Comme pour I<sup>2</sup>C, les termes contrôleur et périphérique sont des changements récents, donc vous pourriez encore voir les anciens termes utilisés.

Les contrôleurs SPI utilisent 3 fils, ainsi qu’un fil supplémentaire par périphérique. Les périphériques utilisent 4 fils. Ces fils sont :

| Fil | Nom | Description |
| ---- | --------- | ----------- |
| COPI | Sortie du contrôleur, entrée du périphérique | Ce fil sert à envoyer des données du contrôleur au périphérique. |
| CIPO | Entrée du contrôleur, sortie du périphérique | Ce fil sert à envoyer des données du périphérique au contrôleur. |
| SCLK | Horloge série | Ce fil envoie un signal d'horloge à une vitesse définie par le contrôleur. |
| CS   | Sélection de puce | Le contrôleur dispose de plusieurs fils, un par périphérique, et chaque fil est connecté au fil CS du périphérique correspondant. |

![SPI avec un contrôleur et deux périphériques](../../../../../translated_images/fr/spi.297431d6f98b386b.webp)

Le fil CS est utilisé pour activer un périphérique à la fois, en communiquant via les fils COPI et CIPO. Lorsque le contrôleur doit changer de périphérique, il désactive le fil CS connecté au périphérique actuellement actif, puis active le fil connecté au périphérique avec lequel il souhaite communiquer ensuite.

Le SPI est *full-duplex*, ce qui signifie que le contrôleur peut envoyer et recevoir des données en même temps depuis le même périphérique en utilisant les fils COPI et CIPO. Le SPI utilise un signal d'horloge sur le fil SCLK pour synchroniser les appareils, donc contrairement à l'envoi direct via UART, il n'a pas besoin de bits de début et de fin.

Il n'y a pas de limites de vitesse définies pour le SPI, les implémentations pouvant souvent transmettre plusieurs mégaoctets de données par seconde.

Les kits de développement IoT prennent souvent en charge le SPI via certaines des broches GPIO. Par exemple, sur un Raspberry Pi, vous pouvez utiliser les broches GPIO 19, 21, 23, 24 et 26 pour le SPI.

### Sans fil

Certains capteurs peuvent communiquer via des protocoles sans fil standard, tels que Bluetooth (principalement Bluetooth Low Energy, ou BLE), LoRaWAN (un protocole réseau basse consommation à **Lo**ngue **Ra**nge), ou WiFi. Cela permet d'utiliser des capteurs distants non connectés physiquement à un appareil IoT.

Un exemple est celui des capteurs d'humidité du sol commerciaux. Ces capteurs mesurent l'humidité du sol dans un champ, puis envoient les données via LoRaWAN à un appareil central, qui traite les données ou les envoie sur Internet. Cela permet au capteur d'être éloigné de l'appareil IoT qui gère les données, réduisant ainsi la consommation d'énergie et le besoin de grands réseaux WiFi ou de longs câbles.

Le BLE est populaire pour les capteurs avancés tels que les trackers de fitness portés au poignet. Ces appareils combinent plusieurs capteurs et envoient les données des capteurs à un appareil IoT, comme votre téléphone, via BLE.

✅ Avez-vous des capteurs Bluetooth sur vous, dans votre maison ou dans votre école ? Ceux-ci pourraient inclure des capteurs de température, des capteurs de présence, des traceurs d'appareils et des dispositifs de fitness.

Une méthode populaire pour connecter des appareils commerciaux est Zigbee. Zigbee utilise le WiFi pour former des réseaux maillés entre les appareils, où chaque appareil se connecte à autant d'appareils voisins que possible, formant un grand nombre de connexions comme une toile d'araignée. Lorsqu'un appareil souhaite envoyer un message sur Internet, il peut l'envoyer aux appareils les plus proches, qui le transmettent ensuite à d'autres appareils voisins, et ainsi de suite, jusqu'à ce qu'il atteigne un coordinateur et puisse être envoyé sur Internet.

> 🐝 Le nom Zigbee fait référence à la danse en zigzag des abeilles après leur retour à la ruche.

## Mesurer les niveaux d'humidité dans le sol

Vous pouvez mesurer le niveau d'humidité dans le sol à l'aide d'un capteur d'humidité du sol, d'un appareil IoT et d'une plante d'intérieur ou d'un morceau de sol à proximité.

### Tâche - mesurer l'humidité du sol

Suivez le guide correspondant pour mesurer l'humidité du sol à l'aide de votre appareil IoT :

* [Arduino - Wio Terminal](wio-terminal-soil-moisture.md)
* [Ordinateur monocarte - Raspberry Pi](pi-soil-moisture.md)
* [Ordinateur monocarte - Appareil virtuel](virtual-device-soil-moisture.md)

## Calibration des capteurs

Les capteurs reposent sur la mesure de propriétés électriques telles que la résistance ou la capacitance.

> 🎓 La résistance, mesurée en ohms (Ω), est la quantité d'opposition au courant électrique traversant un matériau. Lorsqu'une tension est appliquée à un matériau, la quantité de courant qui le traverse dépend de la résistance du matériau. Vous pouvez en savoir plus sur la [page Wikipédia sur la résistance électrique](https://wikipedia.org/wiki/Electrical_resistance_and_conductance).

> 🎓 La capacitance, mesurée en farads (F), est la capacité d'un composant ou d'un circuit à collecter et stocker de l'énergie électrique. Vous pouvez en savoir plus sur la capacitance sur la [page Wikipédia sur la capacitance](https://wikipedia.org/wiki/Capacitance).

Ces mesures ne sont pas toujours utiles - imaginez un capteur de température qui vous donne une mesure de 22,5 kΩ ! Au lieu de cela, la valeur mesurée doit être convertie en une unité utile en étant calibrée - c'est-à-dire en faisant correspondre les valeurs mesurées à la quantité mesurée pour permettre de nouvelles conversions dans la bonne unité.

Certains capteurs sont pré-calibrés. Par exemple, le capteur de température que vous avez utilisé dans la dernière leçon était déjà calibré pour renvoyer une mesure de température en °C. En usine, le premier capteur créé serait exposé à une gamme de températures connues et la résistance mesurée. Cela serait ensuite utilisé pour construire un calcul permettant de convertir la valeur mesurée en Ω (l'unité de résistance) en °C.

> 💁 La formule pour calculer la résistance à partir de la température s'appelle l'[équation de Steinhart–Hart](https://wikipedia.org/wiki/Steinhart–Hart_equation).

### Calibration du capteur d'humidité du sol

L'humidité du sol est mesurée en utilisant la teneur en eau gravimétrique ou volumétrique.

* La gravimétrique est le poids de l'eau dans une unité de poids de sol mesurée, exprimée en kilogrammes d'eau par kilogramme de sol sec
* La volumétrique est le volume d'eau dans une unité de volume de sol mesurée, exprimée en mètres cubes d'eau par mètres cubes de sol sec

> 🇺🇸 Pour les Américains, en raison de la cohérence des unités, ces mesures peuvent être exprimées en livres au lieu de kilogrammes ou en pieds cubes au lieu de mètres cubes.

Les capteurs d'humidité du sol mesurent la résistance ou la capacitance électrique - cela varie non seulement en fonction de l'humidité du sol, mais aussi du type de sol, car les composants du sol peuvent modifier ses caractéristiques électriques. Idéalement, les capteurs devraient être calibrés - c'est-à-dire en prenant des lectures du capteur et en les comparant à des mesures obtenues par une méthode plus scientifique. Par exemple, un laboratoire peut calculer l'humidité gravimétrique du sol à l'aide d'échantillons d'un champ spécifique prélevés plusieurs fois par an, et ces chiffres peuvent être utilisés pour calibrer le capteur, en faisant correspondre la lecture du capteur à l'humidité gravimétrique du sol.

![Un graphique de la tension par rapport à la teneur en humidité du sol](../../../../../translated_images/fr/soil-moisture-to-voltage.df86d80cda158700.webp)

Le graphique ci-dessus montre comment calibrer un capteur. La tension est capturée pour un échantillon de sol qui est ensuite mesuré en laboratoire en comparant le poids humide au poids sec (en mesurant le poids humide, puis en le séchant dans un four et en mesurant le poids sec). Une fois quelques lectures effectuées, elles peuvent être tracées sur un graphique et une ligne ajustée aux points. Cette ligne peut ensuite être utilisée pour convertir les lectures du capteur d'humidité du sol prises par un appareil IoT en mesures réelles d'humidité du sol.

💁 Pour les capteurs d'humidité du sol résistifs, la tension augmente à mesure que l'humidité du sol augmente. Pour les capteurs d'humidité du sol capacitifs, la tension diminue à mesure que l'humidité du sol augmente, donc les graphiques pour ces derniers auraient une pente descendante, et non ascendante.

![Une valeur d'humidité du sol interpolée à partir du graphique](../../../../../translated_images/fr/soil-moisture-to-voltage-with-reading.681cb3e1f8b68caf.webp)

Le graphique ci-dessus montre une lecture de tension d'un capteur d'humidité du sol, et en suivant cette lecture jusqu'à la ligne sur le graphique, l'humidité réelle du sol peut être calculée.

Cette approche signifie que l'agriculteur n'a besoin d'obtenir que quelques mesures de laboratoire pour un champ, puis il peut utiliser des appareils IoT pour mesurer l'humidité du sol - accélérant considérablement le temps nécessaire pour effectuer des mesures.

---

## 🚀 Défi

Les capteurs d'humidité du sol résistifs et capacitifs présentent un certain nombre de différences. Quelles sont ces différences, et quel type (le cas échéant) est le meilleur pour un agriculteur ? Cette réponse change-t-elle entre les pays en développement et les pays développés ?

## Quiz post-cours

[Quiz post-cours](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/12)

## Révision et auto-apprentissage

Renseignez-vous sur le matériel et les protocoles utilisés par les capteurs et les actionneurs :

* [Page Wikipédia sur les GPIO](https://wikipedia.org/wiki/General-purpose_input/output)
* [Page Wikipédia sur l’UART](https://wikipedia.org/wiki/Universal_asynchronous_receiver-transmitter)
* [Page Wikipédia sur le SPI](https://wikipedia.org/wiki/Serial_Peripheral_Interface)
* [Page Wikipédia sur I<sup>2</sup>C](https://wikipedia.org/wiki/I²C)
* [Page Wikipédia sur Zigbee](https://wikipedia.org/wiki/Zigbee)

## Devoir

[Calibrez votre capteur](assignment.md)

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.