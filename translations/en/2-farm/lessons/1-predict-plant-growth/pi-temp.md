<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7678f7c67b97ee52d5727496dcd7d346",
  "translation_date": "2025-08-28T20:35:23+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/pi-temp.md",
  "language_code": "en"
}
-->
# Measure temperature - Raspberry Pi

In this part of the lesson, you will add a temperature sensor to your Raspberry Pi.

## Hardware

The sensor you'll use is a [DHT11 humidity and temperature sensor](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html), which combines two sensors in one package. This sensor is quite popular, and many commercially available sensors combine temperature, humidity, and sometimes atmospheric pressure. The temperature sensor component is a negative temperature coefficient (NTC) thermistor, meaning its resistance decreases as the temperature increases.

This is a digital sensor, so it has an onboard ADC that generates a digital signal containing the temperature and humidity data, which the microcontroller can read.

### Connect the temperature sensor

The Grove temperature sensor can be connected to the Raspberry Pi.

#### Task

Connect the temperature sensor.

![A grove temperature sensor](../../../../../translated_images/en/grove-dht11.07f8eafceee170043efbb53e1d15722bd4e00fbaa9ff74290b57e9f66eb82c17.png)

1. Insert one end of a Grove cable into the socket on the humidity and temperature sensor. It will only fit one way.

1. With the Raspberry Pi powered off, connect the other end of the Grove cable to the digital socket marked **D5** on the Grove Base hat attached to the Pi. This socket is the second from the left in the row of sockets next to the GPIO pins.

![The grove temperature sensor connected to socket A0](../../../../../translated_images/en/pi-temperature-sensor.3ff82fff672c8e565ef25a39d26d111de006b825a7e0867227ef4e7fbff8553c.png)

## Program the temperature sensor

The device can now be programmed to use the attached temperature sensor.

### Task

Program the device.

1. Power up the Pi and wait for it to boot.

1. Launch VS Code, either directly on the Pi or by connecting via the Remote SSH extension.

    > ⚠️ You can refer to [the instructions for setting up and launching VS Code in lesson 1 if needed](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md).

1. From the terminal, create a new folder in the `pi` user's home directory called `temperature-sensor`. Create a file in this folder called `app.py`:

    ```sh
    mkdir temperature-sensor
    cd temperature-sensor
    touch app.py
    ```

1. Open this folder in VS Code.

1. To use the temperature and humidity sensor, an additional Pip package needs to be installed. From the Terminal in VS Code, run the following command to install this Pip package on the Pi:

    ```sh
    pip3 install seeed-python-dht
    ```

1. Add the following code to the `app.py` file to import the required libraries:

    ```python
    import time
    from seeed_dht import DHT
    ```

    The `from seeed_dht import DHT` statement imports the `DHT` sensor class to interact with a Grove temperature sensor from the `seeed_dht` module.

1. Add the following code after the code above to create an instance of the class that manages the temperature sensor:

    ```python
    sensor = DHT("11", 5)
    ```

    This declares an instance of the `DHT` class that manages the **D**igital **H**umidity and **T**emperature sensor. The first parameter specifies that the sensor being used is the *DHT11* sensor—the library you are using supports other variants of this sensor. The second parameter specifies that the sensor is connected to digital port `D5` on the Grove base hat.

    > ✅ Remember, all the sockets have unique pin numbers. Pins 0, 2, 4, and 6 are analog pins, while pins 5, 16, 18, 22, 24, and 26 are digital pins.

1. Add an infinite loop after the code above to poll the temperature sensor value and print it to the console:

    ```python
    while True:
        _, temp = sensor.read()
        print(f'Temperature {temp}°C')
    ```

    The call to `sensor.read()` returns a tuple containing humidity and temperature. You only need the temperature value, so the humidity is ignored. The temperature value is then printed to the console.

1. Add a small sleep of ten seconds at the end of the `loop` since temperature levels don't need to be checked continuously. Adding a sleep reduces the device's power consumption.

    ```python
    time.sleep(10)
    ```

1. From the VS Code Terminal, run the following command to execute your Python app:

    ```sh
    python3 app.py
    ```

    You should see temperature values being output to the console. Use something to warm the sensor, such as pressing your thumb on it or using a fan, to observe the values change:

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py 
    Temperature 26°C
    Temperature 26°C
    Temperature 28°C
    Temperature 30°C
    Temperature 32°C
    ```

> 💁 You can find this code in the [code-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/pi) folder.

😀 Your temperature sensor program was a success!

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we aim for accuracy, please note that automated translations may include errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is advised. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.