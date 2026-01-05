<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "e9ee00eb5fc55922a73762acc542166b",
  "translation_date": "2025-08-28T20:05:28+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/README.md",
  "language_code": "en"
}
-->
# Interact with the physical world using sensors and actuators

![A sketchnote overview of this lesson](../../../../../translated_images/lesson-3.cc3b7b4cd646de598698cce043c0393fd62ef42bac2eaf60e61272cd844250f4.en.jpg)

> Sketchnote by [Nitya Narasimhan](https://github.com/nitya). Click the image for a larger version.

This lesson was part of the [Hello IoT series](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) from the [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). It was delivered in two videos: a 1-hour lesson and a 1-hour office hour session that explored the lesson in more detail and answered questions.

[![Lesson 3: Interact with the Physical World with Sensors and Actuators](https://img.youtube.com/vi/Lqalu1v6aF4/0.jpg)](https://youtu.be/Lqalu1v6aF4)

[![Lesson 3: Interact with the Physical World with Sensors and Actuators - Office hours](https://img.youtube.com/vi/qR3ekcMlLWA/0.jpg)](https://youtu.be/qR3ekcMlLWA)

> 🎥 Click the images above to watch the videos

## Pre-lecture quiz

[Pre-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/5)

## Introduction

This lesson introduces two key components of IoT devices: sensors and actuators. You'll get hands-on experience with both by adding a light sensor to your IoT project and then incorporating an LED that reacts to light levels, effectively creating a nightlight.

In this lesson, we'll cover:

* [What are sensors?](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Use a sensor](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Sensor types](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [What are actuators?](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Use an actuator](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Actuator types](../../../../../1-getting-started/lessons/3-sensors-and-actuators)

## What are sensors?

Sensors are hardware devices that detect and measure properties of the physical world, sending this information to an IoT device. They can measure a wide range of things, from environmental factors like air temperature to physical interactions like movement.

Common types of sensors include:

* Temperature sensors - measure air temperature or the temperature of objects they are in contact with. These are often combined with air pressure and humidity sensors for hobbyist and developer use.
* Buttons - detect when they are pressed.
* Light sensors - measure light levels, including specific colors, UV light, IR light, or general visible light.
* Cameras - capture visual data by taking photos or streaming video.
* Accelerometers - measure movement in multiple directions.
* Microphones - detect sound, either general sound levels or directional sound.

✅ Research the sensors in your phone. What can it measure?

All sensors share a common trait: they convert what they detect into an electrical signal that can be interpreted by an IoT device. The way this signal is interpreted depends on the sensor and the communication protocol used.

## Use a sensor

Follow the appropriate guide below to add a sensor to your IoT device:

* [Arduino - Wio Terminal](wio-terminal-sensor.md)
* [Single-board computer - Raspberry Pi](pi-sensor.md)
* [Single-board computer - Virtual device](virtual-device-sensor.md)

## Sensor types

Sensors can be classified as either analog or digital.

### Analog sensors

Analog sensors are among the simplest types. They receive a voltage from the IoT device, adjust this voltage based on their components, and return a modified voltage that represents the sensor's reading.

> 🎓 Voltage measures the force that moves electricity from one point to another, such as from the positive terminal of a battery to the negative terminal. For example, a standard AA battery is 1.5V (volts) and can push electricity with a force of 1.5V. Different devices require different voltages to operate. For instance, an LED can light up with 2-3V, while a 100W filament bulb needs 240V. Learn more about voltage on the [Voltage page on Wikipedia](https://wikipedia.org/wiki/Voltage).

A potentiometer is an example of an analog sensor. It’s a dial that can be rotated between two positions, and the sensor measures the rotation.

![A potentiometer set to a mid point being sent 5 volts returning 3.8 volts](../../../../../translated_images/potentiometer.35a348b9ce22f6ec.en.png)

The IoT device sends an electrical signal to the potentiometer, such as 5 volts (5V). As the potentiometer is adjusted, it changes the voltage that comes out. For example, if the potentiometer is set to the "off" position, 0V will come out. If it’s set to the "on" position, 5V will come out.

> 🎓 This is a simplified explanation. Learn more about potentiometers on the [potentiometer Wikipedia page](https://wikipedia.org/wiki/Potentiometer).

The voltage returned by the sensor is read by the IoT device, which can then respond accordingly. For example, an analog temperature sensor based on a [thermistor](https://wikipedia.org/wiki/Thermistor) changes its resistance based on temperature. The output voltage can be converted into a temperature value in Kelvin, Celsius, or Fahrenheit using code.

✅ What happens if the sensor returns a higher voltage than was sent (e.g., from an external power source)? ⛔️ DO NOT test this.

#### Analog to digital conversion

IoT devices are digital—they only work with 0s and 1s. Analog sensor values must be converted to digital signals before they can be processed. Many IoT devices have analog-to-digital converters (ADCs) for this purpose. Sensors can also use ADCs via connector boards. For example, in the Seeed Grove ecosystem, analog sensors connect to specific ports on a "hat" attached to a Raspberry Pi. This hat has an ADC that converts the voltage into a digital signal.

Imagine an analog light sensor connected to an IoT device running at 3.3V, returning a value of 1V. This 1V needs to be converted into a digital value. For example, the Seeed Grove light sensor outputs values from 0 to 1,023. At 3.3V, a 1V output would correspond to a value of 300. The IoT device would then convert this value into binary, such as `0000000100101100`.

✅ If you’re unfamiliar with binary, research how numbers are represented using 0s and 1s. The [BBC Bitesize introduction to binary lesson](https://www.bbc.co.uk/bitesize/guides/zwsbwmn/revision/1) is a great starting point.

From a coding perspective, libraries provided with sensors handle this conversion. For example, the Grove light sensor’s Python library lets you call the `light` property, or the Arduino library lets you use `analogRead` to get a value like 300.

### Digital sensors

Digital sensors also detect changes in electrical voltage but output a digital signal. They either measure two states or use a built-in ADC. Digital sensors are increasingly common because they eliminate the need for external ADCs.

The simplest digital sensor is a button or switch, which has two states: on or off.

![A button is sent 5 volts. When not pressed it returns 0 volts, when pressed it returns 5 volts](../../../../../translated_images/button.eadb560b77ac45e56f523d9d8876e40444f63b419e33eb820082d461fa79490b.en.png)

IoT devices can directly measure this signal as 0 or 1. If the voltage sent matches the voltage returned, the value is 1; otherwise, it’s 0.

> 💁 Voltages are rarely exact due to resistance in components, so there’s usually a tolerance. For example, Raspberry Pi GPIO pins work on 3.3V and interpret signals above 1.8V as 1 and below 1.8V as 0.

* 3.3V goes into the button. The button is off, so 0V comes out, giving a value of 0.
* 3.3V goes into the button. The button is on, so 3.3V comes out, giving a value of 1.

More advanced digital sensors measure analog values and convert them to digital signals using built-in ADCs. For example, a digital temperature sensor uses a thermocouple to measure voltage changes caused by temperature. Instead of returning an analog value, it converts the reading to digital data and sends it to the IoT device.

![A digital temperature sensor converting an analog reading to binary data with 0 as 0 volts and 1 as 5 volts before sending it to an IoT device](../../../../../translated_images/temperature-as-digital.85004491b977bae1.en.png)

Digital sensors can send more detailed or even encrypted data. For example, a camera captures images and sends them as digital data, often in a compressed format like JPEG. It can also stream video by sending frames or compressed video streams.

## What are actuators?

Actuators are the opposite of sensors—they convert electrical signals from an IoT device into physical actions, such as emitting light or sound or moving a motor.

Common types of actuators include:

* LED - emits light when turned on.
* Speaker - produces sound, ranging from simple buzzers to audio speakers that play music.
* Stepper motor - rotates a specific amount, such as turning a dial 90°.
* Relay - acts as a switch controlled by an electrical signal, allowing a small voltage to control larger voltages.
* Screens - display information, ranging from simple LED displays to high-resolution monitors.

✅ Research the actuators in your phone. What can it do?

## Use an actuator

Follow the appropriate guide below to add an actuator to your IoT device. You'll use a sensor to control an actuator, creating an IoT nightlight that turns on an LED when light levels are too low.

![A flow chart of the assignment showing light levels being read and checked, and the LED begin controlled](../../../../../translated_images/assignment-1-flow.7552a51acb1a5ec858dca6e855cdbb44206434006df8ba3799a25afcdab1665d.en.png)

* [Arduino - Wio Terminal](wio-terminal-actuator.md)
* [Single-board computer - Raspberry Pi](pi-actuator.md)
* [Single-board computer - Virtual device](virtual-device-actuator.md)

## Actuator types

Like sensors, actuators can be analog or digital.

### Analog actuators

Analog actuators take an analog signal and convert it into a physical action, with the action varying based on the voltage supplied.

One example is a dimmable light, where the brightness depends on the voltage provided.
![A light dimmed at a low voltage and brighter at a higher voltage](../../../../../translated_images/dimmable-light.9ceffeb195dec1a849da718b2d71b32c35171ff7dfea9c07bbf82646a67acf6b.en.png)

Just like with sensors, IoT devices operate using digital signals, not analog. To send an analog signal, the IoT device requires a digital-to-analog converter (DAC), which can either be built into the IoT device itself or included on a connector board. This converter transforms the 0s and 1s from the IoT device into an analog voltage that the actuator can use.

✅ What do you think would happen if the IoT device sends a voltage higher than what the actuator can handle?  
⛔️ DO NOT test this out.

#### Pulse-Width Modulation

Another way to convert digital signals from an IoT device into an analog signal is through pulse-width modulation (PWM). This method involves sending a series of rapid digital pulses that mimic an analog signal.

For instance, PWM can be used to control the speed of a motor.

Imagine controlling a motor powered by a 5V supply. You send a short pulse to the motor, switching the voltage to high (5V) for 0.02 seconds. During this time, the motor rotates one-tenth of a turn, or 36°. The signal then pauses for 0.02 seconds, sending a low signal (0V). Each on-off cycle lasts 0.04 seconds, and the cycle repeats.

![Pulse width modulation rotation of a motor at 150 RPM](../../../../../translated_images/pwm-motor-150rpm.83347ac04ca38482.en.png)

This means that in one second, you send 25 pulses of 5V, each lasting 0.02 seconds, causing the motor to rotate. Each pulse is followed by a 0.02-second pause at 0V, during which the motor does not rotate. Since each pulse rotates the motor by one-tenth of a turn, the motor completes 2.5 rotations per second. Using a digital signal, you've made the motor rotate at 2.5 rotations per second, or 150 [revolutions per minute](https://wikipedia.org/wiki/Revolutions_per_minute) (a common measure of rotational speed).

```output
25 pulses per second x 0.1 rotations per pulse = 2.5 rotations per second
2.5 rotations per second x 60 seconds in a minute = 150rpm
```

> 🎓 When a PWM signal is on for half the time and off for the other half, it is called a [50% duty cycle](https://wikipedia.org/wiki/Duty_cycle). Duty cycles are expressed as the percentage of time the signal is in the "on" state compared to the "off" state.

![Pulse width modulation rotation of a motor at 75 RPM](../../../../../translated_images/pwm-motor-75rpm.a5e4c939934b6e14.en.png)

You can adjust the motor speed by changing the duration of the pulses. For example, using the same motor, you can keep the cycle time at 0.04 seconds but reduce the "on" pulse to 0.01 seconds and increase the "off" pulse to 0.03 seconds. This results in the same number of pulses per second (25), but each "on" pulse is half as long. A shorter pulse rotates the motor by one-twentieth of a turn, and at 25 pulses per second, the motor completes 1.25 rotations per second, or 75 RPM. By modifying the pulse duration of a digital signal, you've halved the speed of an analog motor.

```output
25 pulses per second x 0.05 rotations per pulse = 1.25 rotations per second
1.25 rotations per second x 60 seconds in a minute = 75rpm
```

✅ How would you ensure the motor rotates smoothly, especially at low speeds? Would you use a small number of long pulses with long pauses, or many very short pulses with very short pauses?

> 💁 Some sensors also use PWM to convert analog signals into digital signals.

> 🎓 You can learn more about pulse-width modulation on the [pulse-width modulation page on Wikipedia](https://wikipedia.org/wiki/Pulse-width_modulation).

### Digital actuators

Digital actuators, like digital sensors, either have two states controlled by a high or low voltage or include a built-in DAC to convert a digital signal into an analog one.

A simple example of a digital actuator is an LED. When the device sends a digital signal of 1, a high voltage is applied, lighting up the LED. When the device sends a digital signal of 0, the voltage drops to 0V, and the LED turns off.

![An LED is off at 0 volts and on at 5V](../../../../../translated_images/led.ec6d94f66676a174ad06d9fa9ea49c2ee89beb18b312d5c6476467c66375b07f.en.png)

✅ Can you think of other simple two-state actuators? One example is a solenoid, which is an electromagnet that can be activated to perform tasks like moving a door bolt to lock or unlock a door.

More advanced digital actuators, such as screens, require digital data to be sent in specific formats. These actuators often come with libraries that simplify the process of sending the correct data to control them.

---

## 🚀 Challenge

In the last two lessons, the challenge was to list as many IoT devices as you could find in your home, school, or workplace and determine whether they are built around microcontrollers, single-board computers, or a combination of both.

For each device you listed, identify the sensors and actuators it is connected to. What is the purpose of each sensor and actuator in these devices?

## Post-lecture quiz

[Post-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/6)

## Review & Self Study

* Learn about electricity and circuits on [ThingLearn](http://thinglearn.jenlooper.com/curriculum/).  
* Explore the different types of temperature sensors in the [Seeed Studios Temperature Sensors guide](https://www.seeedstudio.com/blog/2019/10/14/temperature-sensors-for-arduino-projects/).  
* Read about LEDs on the [Wikipedia LED page](https://wikipedia.org/wiki/Light-emitting_diode).  

## Assignment

[Research sensors and actuators](assignment.md)  

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we aim for accuracy, please note that automated translations may include errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is advised. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.