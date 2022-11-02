# 센서 및 액추에이터(actuator)를 통한 물리적 환경과의 상호작용

![A sketchnote overview of this lesson](../../../sketchnotes/lesson-3.jpg)

> [Nitya Narasimhan](https://github.com/nitya) 의 스케치노트입니다. 이미지를 클릭하여 크게 보세요.

이 수업은 [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn) 에서 [Hello IoT series](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) 시리즈의 일부로 제공되었습니다. . 수업은 2개의 비디오로 진행되었습니다. 1시간의 수업과 1시간의 추가 공부 시간을 통해 수업의 내용을 더 깊이 파고들어 질문에 답하고자 합니다.

[![Lesson 3: Interact with the Physical World with Sensors and Actuators](https://img.youtube.com/vi/Lqalu1v6aF4/0.jpg)](https://youtu.be/Lqalu1v6aF4)

[![Lesson 3: Interact with the Physical World with Sensors and Actuators - Office hours](https://img.youtube.com/vi/qR3ekcMlLWA/0.jpg)](https://youtu.be/qR3ekcMlLWA)

> 🎥 동영상을 보려면 위의 이미지를 클릭하세요

## 강의 전 퀴즈

[강의 전 퀴즈](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/5)

## 소개

이 수업은 IoT 장치를 위한 두 가지 중요한 개념인 센서와 액추에이터를 소개한다. 당신은 또한 IoT 프로젝트에 광센서를 추가하고, 조도에 의해 제어되는 LED를 추가하여, 효과적으로 야간 조명을 구축할 수 있습니다.

이 수업에서는 다음을 다룹니다:

* [센서란 무엇인가?](#what-are-sensors)
* [센서를 사용해보자](#use-a-sensor)
* [센서의 종류](#sensor-types)
* [액추에이터란 무엇인가?](#what-are-actuators)
* [액추에이터를 사용해보자](#use-an-actuator)
* [액추에이터의 종류](#actuator-types)

## 센서란 무엇인가?

센서는 물리적 세계를 감지하는 하드웨어 장치입니다. 즉, 센서는 주변의 하나 이상의 속성을 측정하고 정보를 IoT 장치로 보냅니다. 센서는 대기 온도와 같은 자연적 특성부터 움직임과 같은 물리적 상호 작용까지, 측정할 수 있는 것이 매우 많아 방대한 범위의 장치를 포괄합니다.

일반적인 센서에는 다음이 포함됩니다.

- 온도 센서 - 공기 온도 또는 물에 담그는 곳의 온도를 감지합니다. 애호가들과 개발자들에게, 이것들은 종종 단일 센서에서 기압과 습도와 결합됩니다.
- 버튼 - 버튼을 눌렀을 때 신호가 감지됩니다.
- 광 센서 - 광도를 감지하고 특정 색상, 자외선, 적외선 또는 일반적인 가시광선일 수 있습니다.
- 카메라 - 사진을 찍거나 비디오를 스트리밍함으로써 세계의 시각적 표현을 감지합니다.
- 가속도계 - 여러 방향으로의 움직임을 감지합니다.
- 마이크 - 일반적인 소리 수준 또는 방향성 소리를 감지합니다.

✅ 생각해봅시다. 여러분의 휴대전화에는 어떤 센서가 있나요?

모든 센서는 감지하는 모든 것을 IoT 장치로 해석할 수 있는 전기 신호로 변환한다는 한 가지 공통점이 있습니다. 이 전기 신호가 어떻게 해석되는지는 IoT 장치와 통신하는 데 사용되는 통신 프로토콜뿐만 아니라 센서에 따라 다릅니다.

## 센서를 사용해보자

아래의 관련 안내에 따라 IoT 장치에 센서를 추가하십시오.

* [아두이노 - 와이오 터미널(Wio Terminal)](wio-terminal-sensor.md)
* [싱글보드 컴퓨터 - 라즈베리 파이](pi-sensor.md)
* [싱글보드 컴퓨터 - 가상기기](virtual-device-sensor.md)

## 센서의 종류

센서는 아날로그 센서 혹은 디지털 센서가 있습니다.

### 아날로그 센서

가장 기본적인 센서 중 하나는 아날로그 센서입니다. 이러한 센서는 IoT 장치로부터 전압을 공급받고, 센서 컴포넌트가 전압을 조정하며, 센서로부터 반환되는 전압을 측정하여 센서 값을 제공합니다.

> 🎓전압은 배터리의 양극 단자에서 음극 단자로 전기를 이동시키기 위해 한 장소에서 다른 장소로 얼마나 밀리는지를 측정하는 것입니다. 예를 들어, 표준 AA 배터리는 1.5V(V는 볼트 기호)이며, 양극 단자에서 음극 단자로 1.5V의 힘으로 전기를 밀어낼 수 있다. 다른 전기 하드웨어가 작동하려면 다른 전압이 필요합니다. 예를 들어 LED 캔은 2~3V 사이에서 켜지지만 100W 필라멘트 전구는 240V가 필요합니다. 전압에 대한 자세한 내용은 [Wikipedia 에서 Voltage 검색](https://wikipedia.org/wiki/Voltage) 시 확인 가능합니다.

이것의 한 예는 Potentiometer (포텐셔미터)입니다. 이것은 두 위치 사이에서 회전할 수 있고 센서가 회전을 측정하는 다이얼입니다.

![중간 지점에 설정된 potentiometer가 5V를 전송하여 3.8V를 반환합니다.](../../../images/potentiometer.png)

IoT 장치는 포텐셔미터에 5V와 같은 전압으로 전기 신호를 보냅니다. 포텐셔미터가 조정되면 반대쪽에서 나오는 전압이 바뀝니다. 앰프의 볼륨 조정기와 같이 0에서 [11](https://wikipedia.org/wiki/Up_to_eleven)로 이동하는 다이얼로 표시된 포텐셔미터가 있다고 가정해 봅시다. 포텐셔미터가 완전히 꺼진 위치(0)에 있으면 0V(0V)가 나옵니다. 최대 ON 위치(11)에 있으면 5V(5V)가 나옵니다.

> 🎓 이것은 지나치게 단순화된 것이며,  [Wikipedia에서 potentiometer 검색 시](https://wikipedia.org/wiki/Potentiometer) 포텐셔미터 및 가변 저항기에 대해 더 많은 정보를 얻을 수 있습니다..

센서에서 나오는 전압은 IoT 장치에 의해 읽혀지고, 그 장치는 그것에 반응할 수 있습니다. 센서에 따라 이 전압은 임의 값이거나 표준 장치에 매핑될 수 있습니다. 예를 들어, [서미스터](https://wikipedia.org/wiki/Thermistor) 에 기반한 아날로그 온도 센서는 온도에 따라 저항이 변화합니다. 출력 전압은 코드 계산을 통해 켈빈 단위로, 그에 따라 °C 또는 °F 단위로 변환될 수 있습니다.

✅ 센서가 전송된 전압보다 높은 전압을 반환할 경우(예: 외부 전원 공급 장치에서 나오는 전압) 어떻게 된다고 생각하십니까? 
⛔️ 호기심에 실험 해 보진 마십시오.

#### 아날로그에서 디지털로의 변환

IoT 장치는 디지털입니다. 아날로그 값으로는 작동할 수 없고 0과 1에서만 작동합니다. 즉, 아날로그 센서 값을 처리하기 전에 디지털 신호로 변환해야 합니다. 많은 IoT 장치들은 아날로그 입력을 디지털 값 표현으로 변환하는 아날로그-디지털 변환기(ADC)를 가지고 있습니다. 센서는 커넥터 보드를 통해 ADC와 함께 작동할 수도 있습니다. 예를 들어, 라즈베리 파이가 있는 씨드그로브 생태계에서 아날로그 센서는 파이의 GPIO 핀에 연결된 파이에 있는 'hat'의 특정 포트에 연결되며, 이 “hat”은 전압을 파이의 GPIO 핀에서 보낼 수 있는 디지털 신호로 변환하기 위한 ADC가 있습니다.

3.3V를 사용하고 1V의 값을 반환하는 IoT 장치에 연결된 아날로그 광 센서가 있다고 가정 해 봅시다. 이 1V는 디지털 세계에서 아무런 의미가 없기 때문에 변환이 필요합니다. 전압은 장치와 센서에 따라 스케일을 사용하여 아날로그 값으로 변환됩니다. 한 가지 예는 0에서 1,023까지의 값을 출력하는 씨드 그로브 광 센서입니다. 3.3V에서 작동하는 이 센서의 경우 1V 출력은 300입니다. IoT 기기는 300을 아날로그 값으로 처리할 수 없기 때문에 300을 Grove hat로 이진법으로 표현한 `0000000100101100`으로 변환됩니다. 그러면 이것은 IoT 장치에 의해 처리될 것 입니다.

✅ 2진법을 모르면 숫자가 0과 1로 어떻게 표현되는지 알아보기 위해 약간의 공부를 추천합니다. [BBC Bitesize introduction to binary lesson](https://www.bbc.co.uk/bitesize/guides/zwsbwmn/revision/1)는 이진법을 공부하기 좋은 곳입니다.

코딩의 관점에서 볼 때, 이 모든 것은 보통 센서와 함께 제공되는 라이브러리에 의해 처리되므로, 당신은 이 변환에 대해 스스로 걱정할 필요가 없습니다. Grove 광센서의 경우 파이썬 라이브러리를 사용하여 `light (빛)` 속성을 호출하거나 아두이노 라이브러리를 사용하여 `analogRead` 를 호출하여 300의 값을 얻을 수 있습니다.

### 디지털 센서

아날로그 센서와 같은 디지털 센서는 전압의 변화를 이용하여 주변 세계를 감지합니다. 차이점은 두 개의 상태만 측정하거나 내장된 ADC를 사용하여 디지털 신호를 출력한다는 것입니다. 디지털 센서는 커넥터 보드 또는 IoT 장치 자체에서 ADC를 사용할 필요성을 피하기 위해 점점 더 보편화되고 있습니다.

가장 간단한 디지털 센서는 버튼 또는 스위치입니다. 이것은 켜지거나 꺼지는 두 가지 상태의 센서입니다.

![A button is sent 5 volts. When not pressed it returns 0 volts, when pressed it returns 5 volts](../../../images/button.png)

Pins on IoT devices such as GPIO pins can measure this signal directly as a 0 or 1. If the voltage sent is the same as the voltage returned, the value read is 1, otherwise the value read is 0. There is no need to convert the signal, it can only be 1 or 0.

> 💁 Voltages are never exact especially as the components in a sensor will have some resistance, so there is usually a tolerance. For example, the GPIO pins on a Raspberry Pi work on 3.3V, and read a return signal above 1.8V as a 1, below 1.8V as 0.

* 3.3V goes into the button. The button is off so 0V comes out, giving a value of 0
* 3.3V goes into the button. The button is on so 3.3V comes out, giving a value of 1

More advanced digital sensors read analog values, then convert them using on-board ADCs to digital signals. For example, a digital temperature sensor will still use a thermocouple in the same way as an analog sensor, and will still measure the change in voltage caused by the resistance of the thermocouple at the current temperature. Instead of returning an analog value and relying on the device or connector board to convert to a digital signal, an ADC built into the sensor will convert the value and send it as a series of 0s and 1s to the IoT device. These 0s and 1s are sent in the same way as the digital signal for a button with 1 being full voltage and 0 being 0v.

![A digital temperature sensor converting an analog reading to binary data with 0 as 0 volts and 1 as 5 volts before sending it to an IoT device](../../../images/temperature-as-digital.png)

Sending digital data allows sensors to become more complex and send more detailed data, even encrypted data for secure sensors. One example is a camera. This is a sensor that captures an image and sends it as digital data containing that image, usually in a compressed format such as JPEG, to be read by the IoT device. It can even stream video by capturing images and sending either the complete image frame by frame or a compressed video stream.

## What are actuators?

Actuators are the opposite of sensors - they convert an electrical signal from your IoT device into an interaction with the physical world such as emitting light or sound, or moving a motor.

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
