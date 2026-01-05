<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f74f4ccb61f00e5f7e9f49c3ed416e36",
  "translation_date": "2025-08-28T19:00:51+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/README.md",
  "language_code": "en"
}
-->
# Trigger fruit quality detection from a sensor

![A sketchnote overview of this lesson](../../../../../translated_images/lesson-18.92c32ed1d354caa5a54baa4032cf0b172d4655e8e326ad5d46c558a0def15365.en.jpg)

> Sketchnote by [Nitya Narasimhan](https://github.com/nitya). Click the image for a larger version.

## Pre-lecture quiz

[Pre-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/35)

## Introduction

An IoT application typically involves more than just a single device capturing data and sending it to the cloud. It often consists of multiple devices working together to collect data from the physical world using sensors, make decisions based on that data, and interact with the physical world through actuators or visualizations.

In this lesson, you will learn how to design complex IoT applications that incorporate multiple sensors, cloud services for data analysis and storage, and actuators for responses. Specifically, you'll explore how to prototype a fruit quality control system, including using proximity sensors to trigger the IoT application and understanding the architecture of this prototype.

In this lesson, we'll cover:

* [Architect complex IoT applications](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Design a fruit quality control system](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Trigger fruit quality checking from a sensor](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Data used for a fruit quality detector](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Using developer devices to simulate multiple IoT devices](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Moving to production](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)

> 🗑 This is the last lesson in this project, so after completing this lesson and the assignment, don't forget to clean up your cloud services. You will need the services to complete the assignment, so make sure to complete that first.
>
> Refer to [the clean up your project guide](../../../clean-up.md) if necessary for instructions on how to do this.

## Architect complex IoT applications

IoT applications consist of many components, including various devices and internet services.

IoT applications can be described as *things* (devices) sending data that generates *insights*. These *insights* lead to *actions* that improve a business or process. For example, an engine (the thing) sends temperature data. This data is analyzed to determine whether the engine is functioning properly (the insight). Based on this insight, the maintenance schedule for the engine is proactively adjusted (the action).

* Different devices collect different types of data.
* IoT services provide insights from this data, sometimes combining it with data from other sources.
* These insights drive actions, such as controlling actuators or visualizing data.

### Reference IoT architecture

![A reference IoT architecture](../../../../../translated_images/iot-reference-architecture.2278b98b55c6d4e89bde18eada3688d893861d43507641804dd2f9d3079cfaa0.en.png)

The diagram above illustrates a reference IoT architecture.

> 🎓 A *reference architecture* is a template you can use when designing new systems. In this case, if you were building a new IoT system, you could follow this reference architecture, substituting your own devices and services as needed.

* **Things** are devices that collect data from sensors, potentially interacting with edge services to interpret that data, such as image classifiers for image data. The devices send this data to an IoT service.
* **Insights** are derived from serverless applications or analytics performed on stored data.
* **Actions** include commands sent to devices or data visualizations that help humans make decisions.

![A reference IoT architecture](../../../../../translated_images/iot-reference-architecture-azure.0b8d2161af924cb18ae48a8558a19541cca47f27264851b5b7e56d7b8bb372ac.en.png)

The diagram above shows some of the components and services covered in these lessons and how they fit into a reference IoT architecture.

* **Things** - You've written device code to collect data from sensors and analyze images using Custom Vision, both in the cloud and on an edge device. This data was sent to IoT Hub.
* **Insights** - You've used Azure Functions to respond to messages sent to IoT Hub and stored data for later analysis in Azure Storage.
* **Actions** - You've controlled actuators based on decisions made in the cloud and commands sent to devices, and visualized data using Azure Maps.

✅ Think about other IoT devices you’ve used, such as smart home appliances. What are the things, insights, and actions involved in those devices and their software?

This pattern can be scaled up or down as needed, adding more devices and services.

### Data and security

When designing your system's architecture, you must always consider data and security.

* What data does your device send and receive?
* How should this data be secured and protected?
* How should access to the device and cloud service be controlled?

✅ Consider the data security of any IoT devices you own. How much of that data is personal and should be kept private, both during transmission and storage? What data should not be stored?

## Design a fruit quality control system

Let’s apply the concept of things, insights, and actions to design a larger end-to-end application for a fruit quality detector.

Imagine you’ve been tasked with building a fruit quality detector for a processing plant. Fruit moves along a conveyor belt system where employees currently check the fruit manually and remove any unripe fruit. To reduce costs, the plant owner wants an automated system.

✅ One trend with the rise of IoT (and technology in general) is that manual jobs are being replaced by machines. Research how many jobs are estimated to be lost to IoT and how many new jobs will be created to build IoT devices.

You need to create a system where fruit is detected as it arrives on the conveyor belt, photographed, and checked using an AI model running on the edge. The results are sent to the cloud for storage, and if the fruit is unripe, a notification is sent so it can be removed.

|   |   |
| - | - |
| **Things** | Detector for fruit arriving on the conveyor belt<br>Camera to photograph and classify the fruit<br>Edge device running the classifier<br>Device to notify of unripe fruit |
| **Insights** | Decide to check the ripeness of the fruit<br>Store the results of the ripeness classification<br>Determine if there is a need to alert about unripe fruit |
| **Actions** | Send a command to a device to photograph the fruit and check it with an image classifier<br>Send a command to a device to alert that the fruit is unripe |

### Prototyping your application

![A reference IoT architecture for fruit quality checking](../../../../../translated_images/iot-reference-architecture-fruit-quality.cc705f121c3b6fa71c800d9630935ac34bc08223a04601e35f41d5e9b5dd5207.en.png)

The diagram above shows a reference architecture for this prototype application.

* An IoT device with a proximity sensor detects the arrival of fruit and sends a message to the cloud.
* A serverless application in the cloud sends a command to another device to take a photograph and classify the image.
* An IoT device with a camera takes a picture and sends it to an image classifier running on the edge. The results are sent to the cloud.
* A serverless application in the cloud stores this information for later analysis to determine the percentage of unripe fruit. If the fruit is unripe, it sends a command to another IoT device to alert factory workers via an LED.

> 💁 This entire IoT application could be implemented as a single device with all the logic for image classification and LED control built in. It could use IoT Hub just to track the number of unripe fruits detected and configure the device. In this lesson, the application is expanded to demonstrate concepts for large-scale IoT systems.

For the prototype, you will implement all of this on a single device. If you are using a microcontroller, you will use a separate edge device to run the image classifier. You’ve already learned most of the skills needed to build this.

## Trigger fruit quality checking from a sensor

The IoT device needs a trigger to indicate when fruit is ready to be classified. One option is to measure when the fruit is at the correct location on the conveyor belt using a proximity sensor.

![Proximity sensors send laser beams to objects like bananas and time how long till the beam is bounced back](../../../../../translated_images/proximity-sensor.f5cd752c77fb62fe.en.png)

Proximity sensors measure the distance between the sensor and an object. They emit a beam of electromagnetic radiation, such as a laser or infrared light, and detect the radiation bouncing off the object. The time between the beam being sent and the signal bouncing back is used to calculate the distance.

> 💁 You’ve likely used proximity sensors without realizing it. For example, most smartphones turn off their screens when held to your ear during a call to prevent accidental touches. This works using a proximity sensor that detects an object close to the screen and disables touch functionality until the phone is a certain distance away.

### Task - trigger fruit quality detection from a distance sensor

Follow the relevant guide to use a proximity sensor to detect an object with your IoT device:

* [Arduino - Wio Terminal](wio-terminal-proximity.md)
* [Single-board computer - Raspberry Pi](pi-proximity.md)
* [Single-board computer - Virtual device](virtual-device-proximity.md)

## Data used for a fruit quality detector

The prototype fruit detector involves multiple components communicating with each other.

![The components communicating with each other](../../../../../translated_images/fruit-quality-detector-message-flow.adf2a65da8fd8741ac7af11361574de89adc126785d67606bb4d2ec00467e380.en.png)

* A proximity sensor measures the distance to a piece of fruit and sends this data to IoT Hub.
* A command to control the camera is sent from IoT Hub to the camera device.
* The results of the image classification are sent to IoT Hub.
* A command to control an LED to alert workers about unripe fruit is sent from IoT Hub to the device with the LED.

It’s important to define the structure of these messages before building the application.

> 💁 Many experienced developers have spent hours, days, or even weeks troubleshooting bugs caused by mismatches between the data being sent and what was expected.

For example, if you’re sending temperature data, how would you define the JSON? You could use a field called `temperature`, or the abbreviation `temp`.

```json
{
    "temperature": 20.7
}
```

compared to:

```json
{
    "temp": 20.7
}
```

You also need to consider units—should the temperature be in °C or °F? If a consumer device changes its display units, you must ensure the units sent to the cloud remain consistent.

✅ Research how unit problems caused the $125 million Mars Climate Orbiter to crash.

Consider the data being sent for the fruit quality detector. How would you define each message? Where would you analyze the data and decide what to send?

For example, triggering image classification using the proximity sensor. The IoT device measures the distance, but where is the decision made? Does the device decide the fruit is close enough and send a message to IoT Hub to trigger classification? Or does it send proximity measurements and let IoT Hub decide?

The answer depends on the use case. As an IoT developer, you need to understand the system you’re building, how it’s used, and the data being collected.

* If IoT Hub makes the decision, you need to send multiple distance measurements.
* Sending too many messages increases IoT Hub costs, bandwidth usage, and device processing time.
* If the device makes the decision, you need a way to configure it for fine-tuning.

## Using developer devices to simulate multiple IoT devices

To build your prototype, your IoT dev kit will need to act like multiple devices, sending telemetry and responding to commands.

### Simulating multiple IoT devices on a Raspberry Pi or virtual IoT hardware

When using a single-board computer like a Raspberry Pi, you can run multiple applications simultaneously. This allows you to simulate multiple IoT devices by creating separate applications for each 'IoT device.' For example, you can implement each device as a separate Python file and run them in different terminal sessions.
> 💁 Keep in mind that certain hardware may not function properly if accessed by multiple applications at the same time.
### Simulating multiple devices on a microcontroller

Microcontrollers make it more challenging to simulate multiple devices. Unlike single-board computers, you cannot run multiple applications simultaneously; instead, you need to include all the logic for all the separate IoT devices within a single application.

Here are some tips to simplify this process:

* Create one or more classes for each IoT device—for example, classes named `DistanceSensor`, `ClassifierCamera`, `LEDController`. Each class can have its own `setup` and `loop` methods, which are called by the main `setup` and `loop` functions.
* Manage commands in a centralized location and route them to the appropriate device class as needed.
* In the main `loop` function, you must account for the timing requirements of each device. For instance, if one device class needs to process every 10 seconds and another every 1 second, use a 1-second delay in your main `loop` function. Each `loop` call will execute the relevant code for the device that processes every second, while a counter can track the loops and trigger the other device's processing when the counter reaches 10 (resetting the counter afterward).

## Moving to production

The prototype will serve as the foundation for the final production system. Some key differences when transitioning to production include:

* Ruggedized components - using hardware designed to endure the noise, heat, vibration, and stress of a factory environment.
* Internal communications - some components will communicate directly, bypassing the cloud, and only send data to the cloud for storage. The method depends on the factory setup, either through direct communication or by running part of the IoT service on the edge using a gateway device.
* Configuration options - since each factory and use case is unique, the hardware must be configurable. For example, a proximity sensor might need to detect different types of fruit at varying distances. Instead of hardcoding the distance for classification triggers, you would want this to be configurable via the cloud, such as using a device twin.
* Automated fruit removal - rather than using an LED to indicate unripe fruit, automated devices could remove it.

✅ Do some research: What other ways might production devices differ from developer kits?

---

## 🚀 Challenge

In this lesson, you’ve learned some key concepts for architecting an IoT system. Reflect on the previous projects. How do they align with the reference architecture described above?

Choose one of the projects completed so far and design a more complex solution that integrates multiple capabilities beyond what was covered in the projects. Sketch the architecture and consider all the devices and services required.

For example: A vehicle tracking system that combines GPS with sensors to monitor factors like the temperature inside a refrigerated truck, engine on/off times, and driver identity. What devices are involved? What services are needed? What data is transmitted? What security and privacy considerations must be addressed?

## Post-lecture quiz

[Post-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/36)

## Review & Self Study

* Learn more about IoT architecture in the [Azure IoT reference architecture documentation on Microsoft Docs](https://docs.microsoft.com/azure/architecture/reference-architectures/iot?WT.mc_id=academic-17441-jabenn)
* Explore device twins in the [Understand and use device twins in IoT Hub documentation on Microsoft Docs](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-device-twins?WT.mc_id=academic-17441-jabenn)
* Read about OPC-UA, a machine-to-machine communication protocol used in industrial automation, on the [OPC-UA page on Wikipedia](https://wikipedia.org/wiki/OPC_Unified_Architecture)

## Assignment

[Build a fruit quality detector](assignment.md)

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we strive for accuracy, please note that automated translations may contain errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is recommended. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.