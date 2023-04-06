# Interagir avec le monde physique à l'aide de capteurs et d'actionneurs

![Un aperçu de cette leçon sous forme de sketchnote](../../../sketchnotes/lesson-3.jpg)

> Sketchnote de [Nitya Narasimhan](https://github.com/nitya). Cliquez sur l'image pour l'agrandir.

Cette leçon a été enseignée dans le cadre de la [série Hello IoT](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) du [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). La leçon a été enseignée sous forme de deux vidéos - une leçon d'une heure et une heure de bureau pour approfondir certaines parties de la leçon et répondre aux questions.

[![Leçon 3 : Interagir avec le monde physique à l'aide de capteurs et d'actionneurs](https://img.youtube.com/vi/Lqalu1v6aF4/0.jpg)](https://youtu.be/Lqalu1v6aF4)

[![Leçon 3 : Interagir avec le monde physique à l'aide de capteurs et d'actionneurs - Heures de bureau](https://img.youtube.com/vi/qR3ekcMlLWA/0.jpg)](https://youtu.be/qR3ekcMlLWA)

> 🎥 Cliquez sur les images ci-dessus pour visionner les vidéos

## Quiz préalable

[Quiz préalable](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/5)

## Introduction

Cette leçon présente deux concepts importants pour votre appareil IoT : les capteurs et les actionneurs. Vous les mettrez également en pratique en ajoutant un capteur de lumière à votre projet IoT, puis en ajoutant une LED contrôlée par les niveaux de lumière, ce qui vous permettra de développer une veilleuse.

Dans cette leçon, nous aborderons les points suivants

* [What are sensors?](#what-are-sensors)
* [Use a sensor](#use-a-sensor)
* [Sensor types](#sensor-types)
* [What are actuators?](#what-are-actuators)
* [Use an actuator](#use-an-actuator)
* [Actuator types](#actuator-types)

## Qu'est-ce qu'un capteur ?

Les capteurs sont des dispositifs matériels qui détectent le monde physique, c'est-à-dire qu'ils mesurent une ou plusieurs propriétés autour d'eux et envoient l'information à un dispositif IdO. Les capteurs couvrent une vaste gamme d'appareils car il y a beaucoup de choses qui peuvent être mesurées, des propriétés naturelles telles que la température de l'air aux interactions physiques telles que le mouvement.

Les capteurs les plus courants sont les suivants :

* Capteurs de température - ils détectent la température de l'air ou la température de ce dans quoi ils sont immergés. Pour les amateurs et les développeurs, ces capteurs sont souvent combinés avec la pression atmosphérique et l'humidité dans un seul capteur.
* Boutons - ils détectent le moment où ils ont été pressés.
* Capteurs de lumière : ils détectent les niveaux de lumière et peuvent concerner des couleurs spécifiques, la lumière UV, la lumière IR ou la lumière visible en général.
* Les caméras : elles détectent une représentation visuelle du monde en prenant une photo ou en diffusant une vidéo.
* Accéléromètres : ils détectent les mouvements dans plusieurs directions.
* Microphones - ils détectent les sons, qu'il s'agisse de niveaux sonores généraux ou de sons directionnels.

✅ Faites des recherches. Quels sont les capteurs de votre téléphone ?

Tous les capteurs ont un point commun : ils convertissent ce qu'ils détectent en un signal électrique qui peut être interprété par un appareil IoT. La manière dont ce signal électrique est interprété dépend du capteur, ainsi que du protocole de communication utilisé pour communiquer avec l'appareil IoT.

## Utiliser un capteur

Suivez le guide approprié ci-dessous pour ajouter un capteur à votre appareil IoT :

* [Arduino - Terminal Wio](wio-terminal-sensor.md)
* [Ordinateur monocarte - Raspberry Pi](pi-sensor.md)
* [Ordinateur monocarte - Dispositif virtuel](virtual-device-sensor.md)

## Types de capteurs

### Capteurs analogiques

Les capteurs analogiques comptent parmi les capteurs les plus élémentaires. Ces capteurs reçoivent une tension de l'appareil IoT, les composants du capteur ajustent cette tension et la tension renvoyée par le capteur est mesurée pour donner la valeur du capteur.

> 🎓 La tension ("Voltage" en anglais) est une mesure de la force exercée pour déplacer l'électricité d'un endroit à un autre, par exemple de la borne positive d'une pile à la borne négative. Par exemple, une pile AA standard a une tension de 1,5V (V est le symbole des volts) et peut pousser l'électricité avec une force de 1,5V de sa borne positive à sa borne négative. Par exemple, une LED peut s'allumer avec une tension de 2 à 3V, alors qu'une ampoule à filament de 100W nécessite une tension de 240V. Pour en savoir plus sur la tension, consultez la [page sur la tension sur Wikipédia](https://wikipedia.org/wiki/Voltage).

Le potentiomètre en est un exemple. Il s'agit d'un cadran que l'on peut faire tourner entre deux positions et dont le capteur mesure la rotation.

![Un potentiomètre réglé sur un point médian reçoit 5 volts et renvoie 3,8 volts](../../../images/potentiometer.png).

L'appareil IoT envoie un signal électrique au potentiomètre à une tension, par exemple 5 volts (5V). Lorsque le potentiomètre est ajusté, il modifie la tension qui sort de l'autre côté. Imaginez que vous ayez un potentiomètre étiqueté comme un cadran qui va de 0 à [11](https://wikipedia.org/wiki/Up_to_eleven), comme le bouton de volume d'un amplificateur. Lorsque le potentiomètre est en position complètement désactivée (0), 0V (0 volt) sort. Lorsqu'il est en position d'activation totale (11), 5V (5 volts) sont émis.

> 🎓 Il s'agit d'une simplification excessive, et vous pouvez en savoir plus sur les potentiomètres et les résistances variables sur la [page Wikipédia sur les potentiomètres](https://wikipedia.org/wiki/Potentiometer).

La tension qui sort du capteur est alors lue par l'appareil IoT, qui peut alors y répondre. Selon le capteur, cette tension peut être une valeur arbitraire ou correspondre à une unité standard. Par exemple, un capteur de température analogique basé sur une [thermistance](https://wikipedia.org/wiki/Thermistor) modifie sa résistance en fonction de la température. La tension de sortie peut alors être convertie en température en Kelvin, et donc en °C ou °F, par des calculs en code.

✅ Que pensez-vous qu'il se passe si le capteur renvoie une tension plus élevée que celle qui a été envoyée (par exemple en provenance d'une alimentation externe)? ⛔️ NE TESTEZ PAS cela.

#### Conversion analogique-numérique (CAN)

Les appareils IoT sont numériques - ils ne peuvent pas fonctionner avec des valeurs analogiques, ils ne fonctionnent qu'avec des 0 et des 1. Cela signifie que les valeurs analogiques des capteurs doivent être converties en un signal numérique avant de pouvoir être traitées. De nombreux appareils IoT sont équipés de convertisseurs analogique-numérique (CAN) ou analog-to-digital converters (ADCs) en anglais pour convertir les entrées analogiques en représentations numériques de leur valeur. Les capteurs peuvent également fonctionner avec des convertisseurs analogiques-numériques par l'intermédiaire d'une carte de connexion. Par exemple, dans l'écosystème Seeed Grove avec un Raspberry Pi, les capteurs analogiques se connectent à des ports spécifiques sur un 'chapeau' ('hat' en anglais) qui se trouve sur le Pi connecté aux broches GPIO du Pi, et ce chapeau a un CAN pour convertir la tension en un signal numérique qui peut être envoyé hors des broches GPIO du Pi.

Imaginez que vous ayez un capteur de lumière analogique connecté à un dispositif IoT qui utilise 3,3 V et renvoie une valeur de 1 V. Cette valeur de 1 V ne signifie rien dans le monde numérique et doit donc être convertie. Cette valeur de 1V ne signifie rien dans le monde numérique et doit donc être convertie. La tension sera convertie en valeur analogique à l'aide d'une échelle qui dépend de l'appareil et du capteur. Le capteur de lumière Seeed Grove, par exemple, émet des valeurs comprises entre 0 et 1 023. Pour ce capteur fonctionnant à 3,3 V, une sortie de 1 V correspondrait à une valeur de 300. Un appareil IoT ne peut pas traiter 300 comme une valeur analogique, donc la valeur serait convertie en `0000000100101100`, la représentation binaire de 300 par le chapeau Grove. Cette valeur serait ensuite traitée par l'appareil IoT.

✅ Si vous ne connaissez pas le binaire, faites quelques recherches pour apprendre comment les nombres sont représentés par des 0 et des 1. La [leçon d'introduction au binaire de BBC Bitesize](https://www.bbc.co.uk/bitesize/guides/zwsbwmn/revision/1) est un excellent point de départ.

Du point de vue du codage, tout cela est généralement géré par les bibliothèques fournies avec les capteurs, de sorte que vous n'avez pas à vous préoccuper de cette conversion vous-même. Pour le capteur de lumière Grove, vous devez utiliser la bibliothèque Python et appeler la propriété `light`, ou utiliser la bibliothèque Arduino et appeler `analogRead` pour obtenir une valeur de 300.

### Capteurs numériques

Les capteurs numériques, comme les capteurs analogiques, détectent le monde qui les entoure en utilisant les changements de tension électrique. La différence est qu'ils émettent un signal numérique, soit en mesurant seulement deux états, soit en utilisant un CAN intégré. Les capteurs numériques sont de plus en plus courants pour éviter d'avoir à utiliser un CAN, que ce soit sur une carte de connexion ou sur l'appareil IoT lui-même.

Le capteur numérique le plus simple est un bouton ou un interrupteur. Il s'agit d'un capteur à deux états, marche ou arrêt.

![Un bouton reçoit 5 volts. Lorsqu'il n'est pas enfoncé, il renvoie 0 volt, lorsqu'il est enfoncé, il renvoie 5 volts.](../../../images/button.png)

Les broches des appareils IoT, telles que les broches GPIO, peuvent mesurer ce signal directement sous la forme d'un 0 ou d'un 1. Si la tension envoyée est la même que la tension renvoyée, la valeur lue est 1, sinon la valeur lue est 0. Il n'est pas nécessaire de convertir le signal, il ne peut être que 1 ou 0.

> 💁 Les tensions ne sont jamais exactes, en particulier parce que les composants d'un capteur ont une certaine résistance, et il y a donc généralement une tolérance. Par exemple, les broches GPIO d'un Raspberry Pi fonctionnent sur 3,3 V et lisent un signal de retour supérieur à 1,8 V comme un 1, inférieur à 1,8 V comme un 0..

* 3,3 V entrent dans le bouton. Le bouton étant éteint, 0V en sort, ce qui donne une valeur de 0
* 3,3 V entrent dans le bouton. Le bouton est allumé, donc 3,3V sort, ce qui donne une valeur de 1

Les capteurs numériques plus avancés lisent les valeurs analogiques, puis les convertissent en signaux numériques à l'aide de convertisseurs analogiques/numériques embarqués. Par exemple, un capteur de température numérique utilise toujours un thermocouple de la même manière qu'un capteur analogique et mesure toujours la variation de tension causée par la résistance du thermocouple à la température actuelle. Au lieu de renvoyer une valeur analogique et de compter sur l'appareil ou la carte de connexion pour la convertir en un signal numérique, un CAN intégré au capteur convertira la valeur et l'enverra sous la forme d'une série de 0 et de 1 à l'appareil IoT. Ces 0 et 1 sont envoyés de la même manière que le signal numérique d'un bouton, 1 étant la pleine tension et 0 étant 0v.

![Un capteur de température numérique convertissant une lecture analogique en données binaires avec 0 comme 0 volt et 1 comme 5 volts avant de l'envoyer à un dispositif IoT.](../../../images/temperature-as-digital.png)

L'envoi de données numériques permet aux capteurs de devenir plus complexes et d'envoyer des données plus détaillées, voire des données cryptées pour les capteurs sécurisés. L'appareil photo en est un exemple. Il s'agit d'un capteur qui capture une image et l'envoie sous forme de données numériques contenant cette image, généralement dans un format compressé tel que JPEG, pour qu'elle soit lue par l'appareil IoT. Il peut même diffuser de la vidéo en capturant des images et en envoyant soit l'image complète image par image, soit un flux vidéo compressé.

## Qu'est-ce qu'un actionneur ?

Les actionneurs sont l'opposé des capteurs : ils convertissent un signal électrique provenant de votre appareil IoT en une interaction avec le monde physique, par exemple en émettant une lumière ou un son, ou en faisant bouger un moteur.

Some common actuators include:

* LED - these emit light when turned on
* Speaker - these emit sound based on the signal sent to them, from a basic buzzer to an audio speaker that can play music
* Stepper motor - these convert a signal into a defined amount of rotation, such as turning a dial 90°
* Relay - these are switches that can be turned on or off by an electrical signal. They allow a small voltage from an IoT device to turn on larger voltages.
* Screens - these are more complex actuators and show information on a multi-segment display. Screens vary from simple LED displays to high-resolution video monitors.

✅ Do some research. What actuators does your phone have?

## Use an actuator

Follow the relevant guide below to add an actuator to your IoT device, controlled by the sensor, to build an IoT nightlight. It will gather light levels from the light sensor, and use an actuator in the form of an LED to emit light when the detected light level is too low.

![A flow chart of the assignment showing light levels being read and checked, and the LED begin controlled](../../../images/assignment-1-flow.png)

* [Arduino - Wio Terminal](wio-terminal-actuator.md)
* [Single-board computer - Raspberry Pi](pi-actuator.md)
* [Single-board computer - Virtual device](virtual-device-actuator.md)

## Actuator types

Like sensors, actuators are either analog or digital.

### Analog actuators

Analog actuators take an analog signal and convert it into some kind of interaction, where the interaction changes based off the voltage supplied.

One example is a dimmable light, such as the ones you might have in your house. The amount of voltage supplied to the light determines how bright it is.

![A light dimmed at a low voltage and brighter at a higher voltage](../../../images/dimmable-light.png)

Like with sensors, the actual IoT device works on digital signals, not analog. This means to send an analog signal, the IoT device needs a digital to analog converter (DAC), either on the IoT device directly, or on a connector board. This will convert the 0s and 1s from the IoT device to an analog voltage that the actuator can use.

✅ What do you think happens if the IoT device sends a higher voltage than the actuator can handle?
⛔️ DO NOT test this out.

#### Pulse-Width Modulation

Another option for converting digital signals from an IoT device to an analog signal is pulse-width modulation. This involves sending lots of short digital pulses that act as if it was an analog signal.

For example, you can use PWM to control the speed of a motor.

Imagine you are controlling a motor with a 5V supply. You send a short pulse to your motor, switching the voltage to high (5V) for two hundredths of a second (0.02s). In that time your motor can rotate one tenth of a rotation, or 36°. The signal then pauses for two hundredths of a second (0.02s), sending a low signal (0V). Each cycle of on then off lasts 0.04s. The cycle then repeats.

![Pule width modulation rotation of a motor at 150 RPM](../../../images/pwm-motor-150rpm.png)

This means in one second you have 25 5V pulses of 0.02s that rotate the motor, each followed by 0.02s pause of 0V not rotating the motor. Each pulse rotates the motor one tenth of a rotation, meaning the motor completes 2.5 rotations per second. You've used a digital signal to rotate the motor at 2.5 rotations per second, or 150 [revolutions per minute](https://wikipedia.org/wiki/Revolutions_per_minute) (a non-standard measure of rotational velocity).

```output
25 pulses per second x 0.1 rotations per pulse = 2.5 rotations per second
2.5 rotations per second x 60 seconds in a minute = 150rpm
```

> 🎓 When a PWM signal is on for half the time, and off for half it is referred to as a [50% duty cycle](https://wikipedia.org/wiki/Duty_cycle). Duty cycles are measured as the percentage time the signal is in the on state compared to the off state.

![Pule width modulation rotation of a motor at 75 RPM](../../../images/pwm-motor-75rpm.png)

You can change the motor speed by changing the size of the pulses. For example, with the same motor you can keep the same cycle time of 0.04s, with the on pulse halved to 0.01s, and the off pulse increasing to 0.03s. You have the same number of pulses per second (25), but each on pulse is half the length. A half length pulse only turns the motor one twentieth of a rotation, and at 25 pulses a second will complete 1.25 rotations per second or 75rpm. By changing the pulse speed of a digital signal you've halved the speed of an analog motor.

```output
25 pulses per second x 0.05 rotations per pulse = 1.25 rotations per second
1.25 rotations per second x 60 seconds in a minute = 75rpm
```

✅ How would you keep the motor rotation smooth, especially at low speeds? Would you use a small number of long pulses with long pauses or lots of very short pulses with very short pauses?

> 💁 Some sensors also use PWM to convert analog signals to digital signals.

> 🎓 You can read more on pulse-width modulation on the [pulse-width modulation page on Wikipedia](https://wikipedia.org/wiki/Pulse-width_modulation).

### Digital actuators

Digital actuators, like digital sensors, either have two states controlled by a high or low voltage or have a DAC built in so can convert a digital signal to an analog one.

One simple digital actuator is an LED. When a device sends a digital signal of 1, a high voltage is sent that lights the LED. When a digital signal of 0 is sent, the voltage drops to 0V and the LED turns off.

![A LED is off at 0 volts and on at 5V](../../../images/led.png)

✅ What other simple 2-state actuators can you think of? One example is a solenoid, which is an electromagnet that can be activated to do things like move a door bolt locking/unlocking a door.

More advanced digital actuators, such as screens require the digital data to be sent in certain formats. They usually come with libraries that make it easier to send the correct data to control them.

---

## 🚀 Challenge

The challenge in the last two lessons was to list as many IoT devices as you can that are in your home, school or workplace and decide if they are built around microcontrollers or single-board computers, or even a mixture of both.

For every device you listed, what sensors and actuators are they connected to? What is the purpose of each sensor and actuator connected to these devices?

## Post-lecture quiz

[Post-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/6)

## Review & Self Study

* Read up on electricity and circuits on [ThingLearn](http://thinglearn.jenlooper.com/curriculum/).
* Read about the different types of temperature sensors on the [Seeed Studios Temperature Sensors guide](https://www.seeedstudio.com/blog/2019/10/14/temperature-sensors-for-arduino-projects/)
* Read about LEDs on the [Wikipedia LED page](https://wikipedia.org/wiki/Light-emitting_diode)

## Assignment

[Research sensors and actuators](assignment.md)
