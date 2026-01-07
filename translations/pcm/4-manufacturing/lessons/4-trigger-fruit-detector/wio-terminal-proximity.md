<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "288aebb0c59f7be1d2719b8f9660a313",
  "translation_date": "2025-11-18T18:59:54+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/wio-terminal-proximity.md",
  "language_code": "pcm"
}
-->
# Detect proximity - Wio Terminal

For dis part of di lesson, you go add proximity sensor to your Wio Terminal, and read di distance wey e dey measure.

## Hardware

Di Wio Terminal need one proximity sensor.

Di sensor wey you go use na [Grove Time of Flight distance sensor](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html). Dis sensor dey use laser ranging module to measure distance. E fit measure distance from 10mm to 2000mm (1cm - 2m), and e dey report di values for dat range well well, but if di distance pass 1000mm, e go report am as 8109mm.

Di laser rangefinder dey for di back of di sensor, di opposite side to di Grove socket.

Dis na I<sup>2</sup>C sensor.

### Connect di time of flight sensor

Di Grove time of flight sensor fit connect to di Wio Terminal.

#### Task - connect di time of flight sensor

Connect di time of flight sensor.

![A grove time of flight sensor](../../../../../translated_images/grove-time-of-flight-sensor.d82ff2165bfded9f485de54d8d07195a6270a602696825fca19f629ddfe94e86.pcm.png)

1. Put one end of di Grove cable inside di socket for di time of flight sensor. E go only fit enter one way.

1. Make sure say di Wio Terminal no dey connect to your computer or any power supply, then connect di other end of di Grove cable to di left-hand side Grove socket for di Wio Terminal as you dey look di screen. Dis socket dey near di power button. E be combined digital and I<sup>2</sup>C socket.

![Di grove time of flight sensor wey dem connect to di left hand socket](../../../../../translated_images/wio-time-of-flight-sensor.c4c182131d2ea73d.pcm.png)

1. Now, you fit connect di Wio Terminal to your computer.

## Program di time of flight sensor

Di Wio Terminal don ready to program make e use di time of flight sensor wey you connect.

### Task - program di time of flight sensor

1. Create new Wio Terminal project with PlatformIO. Name di project `distance-sensor`. Add code for di `setup` function to configure di serial port.

1. Add library dependency for di Seeed Grove time of flight distance sensor library to di project `platformio.ini` file:

    ```ini
    lib_deps =
        seeed-studio/Grove Ranging sensor - VL53L0X @ ^1.1.1
    ```

1. For `main.cpp`, add dis code under di existing include directives to declare one instance of di `Seeed_vl53l0x` class wey go interact with di time of flight sensor:

    ```cpp
    #include "Seeed_vl53l0x.h"
    
    Seeed_vl53l0x VL53L0X;
    ```

1. Add dis code to di bottom of di `setup` function to initialize di sensor:

    ```cpp
    VL53L0X.VL53L0X_common_init();
    VL53L0X.VL53L0X_high_accuracy_ranging_init();
    ```

1. For di `loop` function, read one value from di sensor:

    ```cpp
    VL53L0X_RangingMeasurementData_t RangingMeasurementData;
    memset(&RangingMeasurementData, 0, sizeof(VL53L0X_RangingMeasurementData_t));

    VL53L0X.PerformSingleRangingMeasurement(&RangingMeasurementData);
    ```

    Dis code dey initialize one data structure to read data inside, then e go pass am into di `PerformSingleRangingMeasurement` method wey go populate am with di distance measurement.

1. After dis one, write di distance measurement, then delay for 1 second:

    ```cpp
    Serial.print("Distance = ");
    Serial.print(RangingMeasurementData.RangeMilliMeter);
    Serial.println(" mm");

    delay(1000);
    ```

1. Build, upload and run dis code. You go fit see di distance measurements for di serial monitor. Put objects near di sensor and you go see di distance measurement:

    ```output
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    Di rangefinder dey for di back of di sensor, so make sure say you use di correct side when you dey measure distance.

    ![Di rangefinder for di back of di time of flight sensor wey dey point at one banana](../../../../../translated_images/time-of-flight-banana.079921ad8b1496e4.pcm.png)

> 💁 You fit find dis code for di [code-proximity/wio-terminal](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/wio-terminal) folder.

😀 Your proximity sensor program don work well!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Disclaimer**:  
Dis docu don use AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator) take translate am. Even though we dey try make e accurate, abeg no forget say automatic translation fit get mistake or no correct well. Di original docu for di language wey dem write am first na di main correct one. For important information, e good make una use professional human translation. We no go fit take blame for any misunderstanding or wrong interpretation wey fit happen because of dis translation.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->