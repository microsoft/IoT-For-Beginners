# Trigger fruit quality detection from a sensor

Add a sketchnote if possible/appropriate

![Embed a video here if available](video-url)

## Pre-lecture quiz

[Pre-lecture quiz](https://brave-island-0b7c7f50f.azurestaticapps.net/quiz/35)

## Introduction

An IoT application is not just a single device capturing data and sending it to the cloud, it is more often that not multiple devices all working together to capture data from the physical world using sensors, make decisions based off that data, and interacting back with the physical world via actuators or visualizations.

In this lesson you will learn more about architecting complex IoT applications, incorporating multiple sensors, multiple cloud services to analyze and store data, and showing a response via an actuator. You will piece together a more advanced fruit quality tracking system.

In this lesson we'll cover:

* [Architect complex IoT applications](#architect-complex-iot-applications)
* [Design a fruit quality control system](#design-a-fruit-quality-control-system)
* [Trigger fruit quality checking from a sensor](#trigger-fruit-quality-checking-from-a-sensor)
* [Store fruit quality data](#store-fruit-quality-data)
* [Control feedback via an actuator](#control-feedback-via-an-actuator)

## Architect complex IoT applications

IoT applications are made up of many components. This includes a variety of things, and a variety of internet services.

IoT applications can be described as *things* (devices) sending data that generates *insights*. These *insights* generate *actions* to improve a business or process. An example is an engine (the thing) sending temperature data. This data is used to evaluate whether the engine is performing as expected (the insight). The insight is used to proactively prioritize the maintenance schedule for the engine (the action).

* Different things gather different pieces of data.
* IoT services give insights over that data, sometimes augmenting it with data from additional sources.
* These insights drive actions, including controlling actuators in devices, or visualizing data.

![A reference iot architecture](../../../images/iot-reference-architecture.png)

***A reference iot architecture. LED by abderraouf omara / Microcontroller by Template - all from the [Noun Project](https://thenounproject.com)***

The diagram above shows some of the components and services covered so far in these lessons and how the link together.

* **Things** are devices that gather data from sensors, maybe interacting with edge services to interpret that data, such as image classifiers to interpret image data. You've written device code to capture data from sensors, and analyse images using Custom Vision running both in the cloud and on an edge device.
* The data from the devices is sent to an IoT service, and from there on to other services to generate insights. You've sent IoT data to Azure IoT Hub.
* **Insights** come from serverless applications, or from analytics run on stored data. So far you've used Azure Functions to respond to messages sent to an IoT Hub, and stored data for later analysis in Azure Storage.
* **Actions** can be commands send to devices, or visualization of data allowing humans to make decisions. You've controlled actuators based on decisions made in the cloud and commands sent to the devices, and you've visualized data using Azure Maps.

✅ Think about other IoT devices you have used, such as smart home appliances. What are the things, insights and actions involved in that device and it's software?

This pattern can be scaled out as large or small as you need, adding more devices and more services.

## Design a fruit quality control system

Lets now take this idea of things, insights, and actions and apply it to our fruit quality detector to design a larger end-to-end application.

Imagine you have been given the task of building a fruit quality detector to be used in a processing plant. Fruit travels on a conveyer belt system where currently employees spend time checking the fruit by hand and removing any unripe fruit as it arrives. To reduce costs, the plant owner wants an automated system.

✅ One of the trends with the rise of IoT (and technology in general) is that low-skill jobs are being replaced by machines. Do some research: How many jobs are estimated to be lost to IoT? How many new jobs will be created building IoT devices?

You need to build a system where fruit is detected as it arrives on the conveyer belt, it is then photographed and checked using an AI model running on the edge. The results are then sent to the cloud to be stored, and if the fruit is unripe a notification is given so the unripe fruit can be removed.

|   |   |
| - | - |
| **Things** | Detector for fruit arriving on the conveyor belt<br>Camera to photograph and classify the fruit<br>Edge device running the classifier<br>Device to notify of unripe fruit |
| **Insights** | Decide to check the ripeness of the fruit<br>Store the results of the ripeness classification<br>Determine if there is a need to alert about unripe fruit |
| **Actions** | Send a command to a device to photograph the fruit and check it with an image classifier<br>Send a command to a device to alert that the fruit is unripe |

### Prototyping your application

![A reference iot architecture for fruit quality checking](../../../images/iot-reference-architecture-fruit-quality.png)

***A reference iot architecture for fruit quality checking. LED by abderraouf omara / Microcontroller by Template - all from the [Noun Project](https://thenounproject.com)***

The diagram above shows a reference architecture for this prototype application.

* An IoT device with a proximity sensor detects the arrival of fruit. This sends a message to the cloud to say fruit has been detected.
* A serverless application in the cloud sends a command to another device to take a photograph and classify the image.
* An IoT device with a camera takes a picture and sends it to an image classifier running on the edge. The results are then sent to the cloud.
* A serverless application in the cloud stores this information to be analyzed later to see what percentage of fruit is unripe. If the fruit is unripe it sends a command to another iot device to alert factory workers there is unripe fruit via an LED.

For the prototype, you will implement all of this on a single device. If you are using a microcontroller then you will use a separate edge device to run the image classifier. You have already learned most of the things you will need to be able to build this.

### Moving to production

The prototype will form the basis of your final production system. The differences when you move to production would be:

* Ruggedized components - using hardware designed to withstand the noise, heat, vibration and stress of a factory.
* Using internal communications - some of the components would communicate directly avoiding the hop to the cloud, only sending data to the cloud to be stored. How this is done depends on the factory setup.
* Automated fruit removal - instead of an LED to alert that fruit is unripe, automated devices would remove it.

## Trigger fruit quality checking from a sensor

The IoT device needs some kind of trigger to indicate when fruit is ready to be classified. One trigger for this would be to measure when the fruit is at the right location on the conveyor belt my measuring the distance to a sensor.

![Proximity sensors send laser beams to objects like bananas and time how long till the beam is bounced back](../../../images/proximity-sensor.png)

***A reference iot architecture for fruit quality checking. Bananas by abderraouf omara / stop watch by Ziyad Al junaidi - all from the [Noun Project](https://thenounproject.com)***

Proximity sensors can be used to measure the distance from the sensor to an object. They usually transmit a beam of electromagnetic radiation such as a laser beam or infra-red light, then detect the radiation bouncing off an object. The time between the laser beam being sent and the signal bouncing back can be used to calculate the distance to the sensor.

> 💁 You have probably used proximity sensors without even knowing about it. Most smartphone will turn the screen off when you hold them to your ear to stop you accidentally ending a call with your earlobe, and this works using a proximity sensor, detecting an object close to the screen during a call and disabling the touch capabilities until the phone is a certain distance away.

### Task - trigger fruit quality detection from a distance sensor

Work through the relevant guide to use a proximity sensor to detect an object using your IoT device:

* [Arduino - Wio Terminal](wio-terminal-proximity.md)
* [Single-board computer - Raspberry Pi](pi-proximity.md)
* [Single-board computer - Virtual device](virtual-device-proximity.md)

## Store fruit quality data

## Design a fruit quality control system

![A reference iot architecture for fruit quality checking](../../../images/iot-reference-architecture-fruit-quality.png)

***A reference iot architecture for fruit quality checking. LED by abderraouf omara / Microcontroller by Template - all from the [Noun Project](https://thenounproject.com)***

## Trigger fruit quality checking from a sensor

### Task - trigger fruit quality detection from a distance sensor

## Store fruit quality data

## Control feedback via an actuator

---

## 🚀 Challenge

## Post-lecture quiz

[Post-lecture quiz](https://brave-island-0b7c7f50f.azurestaticapps.net/quiz/36)

## Review & Self Study

* Read more about IoT architecture on the [Azure IoT reference architecture documentation on Microsoft docs](https://docs.microsoft.com/azure/architecture/reference-architectures/iot?WT.mc_id=academic-17441-jabenn)
* Read about OPC-UA, a machine to machine communication protocol used in industrial automation on the [OPC-UA page on Wikipedia](https://wikipedia.org/wiki/OPC_Unified_Architecture)

## Assignment

[](assignment.md)
