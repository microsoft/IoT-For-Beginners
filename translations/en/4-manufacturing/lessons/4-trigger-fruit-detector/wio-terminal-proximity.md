<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "288aebb0c59f7be1d2719b8f9660a313",
  "translation_date": "2025-08-28T19:03:00+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/wio-terminal-proximity.md",
  "language_code": "en"
}
-->
# Detect proximity - Wio Terminal

In this part of the lesson, you will add a proximity sensor to your Wio Terminal and read distance measurements from it.

## Hardware

The Wio Terminal requires a proximity sensor.

The sensor you'll use is a [Grove Time of Flight distance sensor](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html). This sensor uses a laser ranging module to measure distance. It has a range of 10mm to 2000mm (1cm - 2m) and provides fairly accurate readings within this range. Distances above 1000mm are reported as 8109mm.

The laser rangefinder is located on the back of the sensor, opposite the Grove socket.

This is an I2C sensor.

### Connect the time of flight sensor

The Grove time of flight sensor can be connected to the Wio Terminal.

#### Task - connect the time of flight sensor

Connect the time of flight sensor.

![A grove time of flight sensor](../../../../../translated_images/grove-time-of-flight-sensor.d82ff2165bfded9f485de54d8d07195a6270a602696825fca19f629ddfe94e86.en.png)

1. Insert one end of a Grove cable into the socket on the time of flight sensor. It will only fit one way.

2. With the Wio Terminal disconnected from your computer or other power source, connect the other end of the Grove cable to the left-hand Grove socket on the Wio Terminal as you face the screen. This socket is closest to the power button. It is a combined digital and I2C socket.

![The grove time of flight sensor connected to the left-hand socket](../../../../../translated_images/wio-time-of-flight-sensor.c4c182131d2ea73d.en.png)

3. You can now connect the Wio Terminal to your computer.

## Program the time of flight sensor

The Wio Terminal can now be programmed to use the attached time of flight sensor.

### Task - program the time of flight sensor

1. Create a new Wio Terminal project using PlatformIO. Name this project `distance-sensor`. Add code in the `setup` function to configure the serial port.

2. Add a library dependency for the Seeed Grove time of flight distance sensor library to the project's `platformio.ini` file:

    ```ini
    lib_deps =
        seeed-studio/Grove Ranging sensor - VL53L0X @ ^1.1.1
    ```

3. In `main.cpp`, add the following below the existing include directives to declare an instance of the `Seeed_vl53l0x` class to interact with the time of flight sensor:

    ```cpp
    #include "Seeed_vl53l0x.h"
    
    Seeed_vl53l0x VL53L0X;
    ```

4. Add the following to the bottom of the `setup` function to initialize the sensor:

    ```cpp
    VL53L0X.VL53L0X_common_init();
    VL53L0X.VL53L0X_high_accuracy_ranging_init();
    ```

5. In the `loop` function, read a value from the sensor:

    ```cpp
    VL53L0X_RangingMeasurementData_t RangingMeasurementData;
    memset(&RangingMeasurementData, 0, sizeof(VL53L0X_RangingMeasurementData_t));

    VL53L0X.PerformSingleRangingMeasurement(&RangingMeasurementData);
    ```

    This code initializes a data structure to store the data, then passes it into the `PerformSingleRangingMeasurement` method, which populates it with the distance measurement.

6. Below this, write out the distance measurement, then delay for 1 second:

    ```cpp
    Serial.print("Distance = ");
    Serial.print(RangingMeasurementData.RangeMilliMeter);
    Serial.println(" mm");

    delay(1000);
    ```

7. Build, upload, and run this code. You will be able to see distance measurements in the serial monitor. Place objects near the sensor, and you will see the distance measurement:

    ```output
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    The rangefinder is located on the back of the sensor, so ensure you use the correct side when measuring distance.

    ![The rangefinder on the back of the time of flight sensor pointing at a banana](../../../../../translated_images/time-of-flight-banana.079921ad8b1496e4.en.png)

> 💁 You can find this code in the [code-proximity/wio-terminal](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/wio-terminal) folder.

😀 Your proximity sensor program was a success!

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we aim for accuracy, please note that automated translations may include errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is advised. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.