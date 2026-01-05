<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9dd7f645ad1c6f20b72fee512987f772",
  "translation_date": "2025-08-28T19:49:58+00:00",
  "source_file": "1-getting-started/lessons/2-deeper-dive/README.md",
  "language_code": "en"
}
-->
# A deeper dive into IoT

![A sketchnote overview of this lesson](../../../../../translated_images/lesson-2.324b0580d620c25e0a24fb7fddfc0b29a846dd4b82c08e7a9466d580ee78ce51.en.jpg)

> Sketchnote by [Nitya Narasimhan](https://github.com/nitya). Click the image for a larger version.

This lesson was part of the [Hello IoT series](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) from the [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). It was delivered in two videos: a 1-hour lesson and a 1-hour office hour session that explored the lesson in more detail and answered questions.

[![Lesson 2: A deeper dive into IoT](https://img.youtube.com/vi/t0SySWw3z9M/0.jpg)](https://youtu.be/t0SySWw3z9M)

[![Lesson 2: A deeper dive into IoT - Office hours](https://img.youtube.com/vi/tTZYf9EST1E/0.jpg)](https://youtu.be/tTZYf9EST1E)

> 🎥 Click the images above to watch the videos

## Pre-lecture quiz

[Pre-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/3)

## Introduction

This lesson takes a closer look at some of the concepts introduced in the previous lesson.

In this lesson, we’ll cover:

* [Components of an IoT application](../../../../../1-getting-started/lessons/2-deeper-dive)
* [Deeper dive into microcontrollers](../../../../../1-getting-started/lessons/2-deeper-dive)
* [Deeper dive into single-board computers](../../../../../1-getting-started/lessons/2-deeper-dive)

## Components of an IoT application

An IoT application consists of two main components: the *Internet* and the *thing*. Let’s explore these components in more detail.

### The Thing

![A Raspberry Pi 4](../../../../../translated_images/raspberry-pi-4.fd4590d308c3d456.en.jpg)

The **Thing** in IoT refers to a device that interacts with the physical world. These devices are typically small, affordable computers that operate at low speeds and consume minimal power. For example, they might be simple microcontrollers with kilobytes of RAM (compared to gigabytes in a PC), running at a few hundred megahertz (compared to gigahertz in a PC), and consuming so little power that they can run on batteries for weeks, months, or even years.

These devices interact with the physical world by using sensors to collect data from their surroundings or by controlling outputs or actuators to make physical changes. A classic example is a smart thermostat, which includes a temperature sensor, a way to set a desired temperature (like a dial or touchscreen), and a connection to a heating or cooling system. The thermostat detects when the room is too cold and activates the heating system.

![A diagram showing temperature and a dial as inputs to an IoT device, and control of a heater as an output](../../../../../translated_images/basic-thermostat.a923217fd1f37e5a6f3390396a65c22a387419ea2dd17e518ec24315ba6ae9a8.en.png)

There’s a wide variety of devices that can serve as IoT devices, ranging from specialized hardware that senses a single thing to general-purpose devices like your smartphone. For instance, a smartphone can use sensors to gather data about its environment and actuators to interact with the world—for example, using GPS to determine your location and a speaker to provide navigation instructions.

✅ Think about other systems around you that use sensors to gather data and make decisions. One example is the thermostat in an oven. Can you identify more?

### The Internet

The **Internet** component of an IoT application includes the applications that IoT devices connect to in order to send and receive data, as well as other applications that process this data and make decisions about what commands to send back to the IoT device’s actuators.

A common setup involves a cloud service that the IoT device connects to. This cloud service handles tasks like security, receiving messages from the IoT device, and sending messages back to it. The cloud service may also connect to other applications that process or store sensor data, or combine it with data from other systems to make decisions.

Not all IoT devices connect directly to the Internet via WiFi or wired connections. Some use mesh networking to communicate with each other over technologies like Bluetooth, connecting through a hub device that has Internet access.

For example, a smart thermostat might connect to a cloud service via home WiFi. The thermostat sends temperature data to the cloud service, which stores it in a database. The homeowner can then check current and past temperatures using a phone app. Another cloud service determines the desired temperature and sends commands back to the thermostat to control the heating system.

![A diagram showing temperature and a dial as inputs to an IoT device, the IoT device with 2-way communication to the cloud, which in turn has 2-way communication to a phone, and control of a heater as an output from the IoT device](../../../../../translated_images/mobile-controlled-thermostat.4a994010473d8d6a52ba68c67e5f02dc8928c717e93ca4b9bc55525aa75bbb60.en.png)

A more advanced version might use AI in the cloud, combining data from other IoT devices like occupancy sensors, as well as external data like weather forecasts and your calendar, to make smarter decisions about temperature settings. For instance, it could turn off the heating if your calendar shows you’re on vacation or adjust the temperature room by room based on usage patterns, learning over time to become more accurate.

![A diagram showing multiple temperature sensors and a dial as inputs to an IoT device, the IoT device with 2-way communication to the cloud, which in turn has 2-way communication to a phone, a calendar, and a weather service, and control of a heater as an output from the IoT device](../../../../../translated_images/smarter-thermostat.a75855f15d2d9e63.en.png)

✅ What other types of data could make an Internet-connected thermostat smarter?

### IoT on the Edge

Although the "I" in IoT stands for Internet, IoT devices don’t always need to connect to the Internet. In some cases, they connect to "edge" devices—gateway devices on a local network—allowing data to be processed locally without relying on an Internet connection. This can be faster when dealing with large amounts of data or a slow Internet connection, enables offline operation in places without Internet access (like ships or disaster zones), and helps maintain data privacy. Some devices even run cloud-developed processing code locally to make decisions without needing an Internet connection.

An example is a smart home device like an Apple HomePod, Amazon Alexa, or Google Home. These devices use AI models trained in the cloud but run locally to listen for a wake word. Once activated, they send your speech to the cloud for processing, but only for the duration of the interaction. Everything said before the wake word or after the device stops listening remains private and is not sent to the cloud.

✅ Think of other scenarios where privacy is critical, making edge processing preferable to cloud processing. Hint: Consider IoT devices with cameras or other imaging sensors.

### IoT Security

Security is a critical concern for any Internet-connected device. There’s an old joke that "the S in IoT stands for Security"—a play on the fact that there’s no "S" in IoT, implying it’s not secure.

IoT devices rely on cloud services, and their security is only as strong as the cloud service they connect to. If the cloud service is poorly secured, malicious data or viruses could compromise the IoT device. This can have serious real-world consequences, as IoT devices often control physical systems. For example, the [Stuxnet worm](https://wikipedia.org/wiki/Stuxnet) damaged centrifuges by manipulating their valves. Hackers have also exploited [weak security to access baby monitors](https://www.npr.org/sections/thetwo-way/2018/06/05/617196788/s-c-mom-says-baby-monitor-was-hacked-experts-say-many-devices-are-vulnerable) and other home surveillance devices.

> 💁 Some IoT and edge devices operate on networks completely isolated from the Internet to ensure privacy and security. This is known as [air-gapping](https://wikipedia.org/wiki/Air_gap_(networking)).

## Deeper dive into microcontrollers

In the previous lesson, we introduced microcontrollers. Let’s now explore them in greater detail.

### CPU

The CPU is the "brain" of the microcontroller. It runs your code and communicates with connected devices. CPUs can have one or more cores, which work together to execute instructions.

CPUs operate based on a clock that ticks millions or billions of times per second. Each tick, or cycle, synchronizes the CPU’s actions. During each cycle, the CPU can execute an instruction, such as retrieving data or performing a calculation. Faster clock cycles allow more instructions to be processed per second, making the CPU faster. CPU speeds are measured in [Hertz (Hz)](https://wikipedia.org/wiki/Hertz), where 1 Hz equals one cycle per second.

> 🎓 CPU speeds are often expressed in MHz or GHz. 1 MHz equals 1 million Hz, and 1 GHz equals 1 billion Hz.

> 💁 CPUs execute programs using the [fetch-decode-execute cycle](https://wikipedia.org/wiki/Instruction_cycle). Each cycle involves fetching an instruction from memory, decoding it, and executing it. Some instructions take multiple cycles to complete.

![The fetch decode execute cycles showing the fetch taking an instruction from the program stored in RAM, then decoding and executing it on a CPU](../../../../../translated_images/fetch-decode-execute.2fd6f150f6280392807f4475382319abd0cee0b90058e1735444d6baa6f2078c.en.png)

Microcontrollers have much lower clock speeds than PCs, laptops, or smartphones. For example, the Wio Terminal’s CPU runs at 120 MHz (120 million cycles per second).

✅ Most PCs or Macs have CPUs with multiple cores running at several GHz, meaning billions of cycles per second. Research your computer’s clock speed and compare it to the Wio Terminal’s speed.

Each clock cycle consumes power and generates heat. Faster cycles require more power and produce more heat. PCs use heat sinks and fans to prevent overheating, but microcontrollers often don’t need these because they run slower and cooler. PCs rely on mains power or large batteries, while microcontrollers can run for extended periods on small batteries. Some microcontrollers even have cores that operate at different speeds, switching to slower, low-power cores when demand is low to save energy.

> 💁 Some modern PCs and Macs use a mix of high-performance and low-power cores to optimize battery life and performance. For example, Apple’s M1 chip has 4 performance cores and 4 efficiency cores.

✅ Do some research: Read about CPUs in the [Wikipedia CPU article](https://wikipedia.org/wiki/Central_processing_unit).

#### Task

Explore the Wio Terminal.

If you’re using a Wio Terminal for these lessons, locate the CPU. Check the *Hardware Overview* section of the [Wio Terminal product page](https://www.seeedstudio.com/Wio-Terminal-p-4509.html) for an internal diagram, and try to spot the CPU through the clear plastic window on the back.

### Memory

Microcontrollers typically have two types of memory: program memory and random-access memory (RAM).

Program memory is non-volatile, meaning its contents persist even when the device is powered off. This memory stores your program code.

RAM, on the other hand, is used by the program while it’s running. It holds variables and data from peripherals. RAM is volatile, so its contents are lost when the device loses power, effectively resetting the program.
🎓 Program memory retains your code and remains intact even when the power is off.
> 🎓 RAM is used to run your program and is reset when there is no power

Like the CPU, the memory in a microcontroller is significantly smaller than that of a PC or Mac. A typical PC might have 8 Gigabytes (GB) of RAM, or 8,000,000,000 bytes, with each byte capable of storing a single letter or a number between 0-255. In contrast, a microcontroller typically has only Kilobytes (KB) of RAM, where a kilobyte equals 1,000 bytes. For example, the Wio Terminal mentioned earlier has 192KB of RAM, or 192,000 bytes—over 40,000 times less than the average PC!

The diagram below illustrates the size difference between 192KB and 8GB—the tiny dot in the center represents 192KB.

![A comparison between 192KB and 8GB - more than 40,000 times larger](../../../../../translated_images/ram-comparison.6beb73541b42ac6f.en.png)

Program storage is also much smaller than on a PC. While a typical PC might have a 500GB hard drive for program storage, a microcontroller might only have kilobytes or a few megabytes (MB) of storage (1MB equals 1,000KB, or 1,000,000 bytes). The Wio Terminal, for instance, has 4MB of program storage.

✅ Do a little research: How much RAM and storage does the computer you’re using to read this have? How does it compare to a microcontroller?

### Input/Output

Microcontrollers require input and output (I/O) connections to read data from sensors and send control signals to actuators. They typically include several general-purpose input/output (GPIO) pins. These pins can be configured in software as either input (to receive signals) or output (to send signals).

🧠⬅️ Input pins are used to read values from sensors.

🧠➡️ Output pins send instructions to actuators.

✅ You’ll learn more about this in a later lesson.

#### Task

Investigate the Wio Terminal.

If you’re using a Wio Terminal for these lessons, locate the GPIO pins. Check the *Pinout diagram* section on the [Wio Terminal product page](https://www.seeedstudio.com/Wio-Terminal-p-4509.html) to identify the pins. The Wio Terminal comes with a sticker for the back that labels the pin numbers—apply this now if you haven’t already.

### Physical size

Microcontrollers are generally small, with some being incredibly tiny. For example, the [Freescale Kinetis KL03 MCU](https://www.edn.com/tiny-arm-cortex-m0-based-mcu-shrinks-package/) is small enough to fit in the dimple of a golf ball. By comparison, the CPU in a PC can measure 40mm x 40mm, not including the heat sinks and fans required to prevent overheating. These components make the CPU significantly larger than a complete microcontroller. The Wio Terminal developer kit, which includes a microcontroller, case, screen, and various connections and components, is only slightly larger than a bare Intel i9 CPU—and much smaller than the CPU with its heat sink and fan!

| Device                          | Size                  |
| ------------------------------- | --------------------- |
| Freescale Kinetis KL03          | 1.6mm x 2mm x 1mm     |
| Wio Terminal                    | 72mm x 57mm x 12mm    |
| Intel i9 CPU, Heat sink and fan | 136mm x 145mm x 103mm |

### Frameworks and operating systems

Because of their limited speed and memory, microcontrollers don’t run operating systems (OS) in the traditional sense. Desktop operating systems like Windows, Linux, or macOS require significant memory and processing power to handle tasks that are unnecessary for microcontrollers. Microcontrollers are typically programmed to perform specific tasks, unlike general-purpose computers that support user interfaces, multimedia, document editing, gaming, and web browsing.

Programming a microcontroller without an OS requires tools to build code that the microcontroller can execute, using APIs to interact with peripherals. Since each microcontroller is unique, manufacturers often provide standard frameworks to simplify development. These frameworks allow you to write code that can run on any microcontroller supporting the framework.

Some microcontrollers can run an OS, often referred to as a real-time operating system (RTOS). RTOSes are lightweight and designed to handle real-time data exchange with peripherals. They offer features like:

* Multi-threading, enabling multiple blocks of code to run simultaneously on multiple cores or sequentially on a single core.
* Networking for secure Internet communication.
* Graphical user interface (GUI) components for devices with screens.

✅ Learn about different RTOSes: [Azure RTOS](https://azure.microsoft.com/services/rtos/?WT.mc_id=academic-17441-jabenn), [FreeRTOS](https://www.freertos.org), [Zephyr](https://www.zephyrproject.org).

#### Arduino

![The Arduino logo](../../../../../images/arduino-logo.svg)

[Arduino](https://www.arduino.cc) is one of the most popular microcontroller frameworks, especially among students, hobbyists, and makers. It’s an open-source electronics platform that combines software and hardware. Arduino-compatible boards can be purchased from Arduino or other manufacturers, and they are programmed using the Arduino framework.

Arduino programs are written in C or C++. These languages allow for compact, fast code—essential for constrained devices like microcontrollers. An Arduino program, called a sketch, consists of two main functions: `setup` and `loop`. When the board powers on, the `setup` function runs once, followed by the `loop` function, which runs repeatedly until the device is powered off.

The `setup` function is used for initialization tasks, such as connecting to WiFi or setting up input/output pins. The `loop` function contains the main processing logic, such as reading sensor data and sending it to the cloud. You can include delays in the loop to control how often it runs—for example, adding a 10-second delay to send sensor data every 10 seconds. This allows the microcontroller to sleep between loops, conserving power.

![An Arduino sketch running setup first, then running loop repeatedly](../../../../../translated_images/arduino-sketch.79590cb837ff7a7c6a68d1afda6cab83fd53d3bb1bd9a8bf2eaf8d693a4d3ea6.en.png)

✅ This program structure is called an *event loop* or *message loop*. It’s widely used in desktop applications running on OSes like Windows, macOS, or Linux. The `loop` listens for events, such as button presses or keyboard input, and responds accordingly. Learn more in this [article on the event loop](https://wikipedia.org/wiki/Event_loop).

Arduino provides standard libraries for interacting with microcontrollers and GPIO pins. These libraries abstract the hardware differences, so code written for one Arduino board can often be recompiled for another, as long as the pins and features are compatible. For example:

* The [`delay` function](https://www.arduino.cc/reference/en/language/functions/time/delay/) pauses the program for a specified time.
* The [`digitalRead` function](https://www.arduino.cc/reference/en/language/functions/digital-io/digitalread/) reads a `HIGH` or `LOW` value from a pin.

A large ecosystem of third-party Arduino libraries adds functionality, such as support for sensors, actuators, and cloud IoT services.

##### Task

Investigate the Wio Terminal.

If you’re using a Wio Terminal for these lessons, revisit the code you wrote in the previous lesson. Locate the `setup` and `loop` functions. Monitor the serial output to observe the `loop` function being called repeatedly. Add code to the `setup` function to write to the serial port, and confirm that this code runs only once per reboot. Reboot the device using the power switch to verify this behavior.

## Deeper dive into single-board computers

In the previous lesson, we introduced single-board computers. Let’s explore them further.

### Raspberry Pi

![The Raspberry Pi logo](../../../../../translated_images/raspberry-pi-logo.4efaa16605cee054.en.png)

The [Raspberry Pi Foundation](https://www.raspberrypi.org) is a UK-based charity founded in 2009 to promote computer science education, particularly in schools. As part of this mission, they developed the Raspberry Pi, a single-board computer. Raspberry Pis come in three variants: a full-size version, the smaller Pi Zero, and a compute module for embedding in IoT devices.

![A Raspberry Pi 4](../../../../../translated_images/raspberry-pi-4.fd4590d308c3d456.en.jpg)

The latest full-size model, the Raspberry Pi 4B, features a quad-core 1.5GHz CPU, 2, 4, or 8GB of RAM, gigabit Ethernet, WiFi, dual 4K HDMI ports, an audio/composite video output, USB ports (2 USB 2.0, 2 USB 3.0), 40 GPIO pins, a camera connector, and an SD card slot. It measures 88mm x 58mm x 19.5mm and is powered by a 3A USB-C supply. Prices start at $35, making it far cheaper than a PC or Mac.

> 💁 There’s also the Pi400, an all-in-one computer with a Pi4 built into a keyboard.

![A Raspberry Pi Zero](../../../../../translated_images/raspberry-pi-zero.f7a4133e1e7d54bb.en.jpg)

The Pi Zero is smaller and less powerful, with a single-core 1GHz CPU, 512MB of RAM, WiFi (in the Zero W model), a single HDMI port, a micro-USB port, 40 GPIO pins, a camera connector, and an SD card slot. It measures 65mm x 30mm x 5mm and consumes very little power. The Zero costs $5, while the Zero W with WiFi costs $10.

> 🎓 Both models use ARM processors, similar to those in microcontrollers, mobile phones, Microsoft Surface X, and Apple Silicon Macs, rather than the Intel/AMD x86 or x64 processors found in most PCs and Macs.

All Raspberry Pi models run Raspberry Pi OS, a version of Debian Linux. It’s available in a lite version (no desktop) for headless projects or a full version with a desktop environment, web browser, office tools, coding software, and games. Since Raspberry Pi OS is based on Debian Linux, you can install any Debian-compatible application built for ARM processors.

#### Task

Investigate the Raspberry Pi.

If you’re using a Raspberry Pi for these lessons, familiarize yourself with its hardware components.

* Learn about the processors on the [Raspberry Pi hardware documentation page](https://www.raspberrypi.org/documentation/hardware/raspberrypi/).
* Locate the GPIO pins and read about them in the [Raspberry Pi GPIO documentation](https://www.raspberrypi.org/documentation/hardware/raspberrypi/gpio/README.md). Use the [GPIO Pin Usage guide](https://www.raspberrypi.org/documentation/usage/gpio/README.md) to identify the pins on your Pi.

### Programming single-board computers

Single-board computers are full-fledged computers running a complete OS. This means you can use a wide variety of programming languages, frameworks, and tools, unlike microcontrollers, which depend on specific frameworks like Arduino. Most programming languages have libraries for accessing GPIO pins to interact with sensors and actuators.

✅ What programming languages do you know? Are they supported on Linux?

Python is the most popular language for IoT development on Raspberry Pi. The Pi has a vast ecosystem of hardware, most of which comes with Python libraries for easy integration. Many of these hardware components are designed as "hats" that connect to the Pi’s 40 GPIO pins. These hats add functionality, such as screens, sensors, remote-controlled cars, or adapters for standardized sensor cables.
### Use of single-board computers in professional IoT deployments

Single-board computers are used in professional IoT deployments, not just as development kits. They offer a powerful way to control hardware and handle complex tasks, such as running machine learning models. For instance, the [Raspberry Pi 4 compute module](https://www.raspberrypi.org/blog/raspberry-pi-compute-module-4/) delivers all the capabilities of a Raspberry Pi 4 but in a smaller and more affordable form factor, without most of the ports, and is designed to be integrated into custom hardware.

---

## 🚀 Challenge

The challenge in the previous lesson was to list as many IoT devices as you can find in your home, school, or workplace. For each device on your list, do you think it is built around microcontrollers, single-board computers, or perhaps a combination of both?

## Post-lecture quiz

[Post-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/4)

## Review & Self Study

* Read the [Arduino getting started guide](https://www.arduino.cc/en/Guide/Introduction) to learn more about the Arduino platform.
* Check out the [introduction to the Raspberry Pi 4](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/) to explore Raspberry Pis in greater detail.
* Dive deeper into some of the concepts and acronyms by reading the [What the FAQ are CPUs, MPUs, MCUs, and GPUs article in the Electrical Engineering Journal](https://www.eejournal.com/article/what-the-faq-are-cpus-mpus-mcus-and-gpus/).

✅ Use these resources, along with the cost information provided in the [hardware guide](../../../hardware.md), to decide which hardware platform you want to use—or whether you prefer to work with a virtual device.

## Assignment

[Compare and contrast microcontrollers and single-board computers](assignment.md)

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we aim for accuracy, please note that automated translations may include errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is advised. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.