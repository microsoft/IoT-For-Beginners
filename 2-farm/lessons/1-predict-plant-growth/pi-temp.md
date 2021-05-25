# Measure temperature - Raspberry Pi

In this part of the lesson, you will add a temperature sensor to your Raspberry Pi.

## Hardware

The sensor you'll use is a [DHT11 humidity and temperature sensor](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html), combining 2 sensors in one package. This is fairly popular, with a number of commercially available sensors combining temperature, humidity and sometimes atmospheric pressure. The temperature sensor component is a negative temperature coefficient (NTC) thermistor, a thermistor where the resistance decreases as the temperature increases.

This is a digital sensor, so has an onboard ADC to create a digital signal containing the temperature and humidity data that the microcontroller can read.

### Connect the temperature sensor

The Grove temperature sensor can be connected to the Raspberry Pi.

#### Task

Connect the temperature sensor

![A grove temperature sensor](../../../images/grove-dht11.png)

1. Insert one end of a Grove cable into the socket on the humidity and temperature sensor. It will only go in one way round.

1. With the Raspberry Pi powered off, connect the other end of the Grove cable to the digital socket marked **D5** on the Grove Base hat attached to the Pi. This socket is the second from the left, on the row of sockets next to the GPIO pins.

![The grove temperature sensor connected to socket A0](../../../images/pi-temperature-sensor.png)

## Program the temperature sensor

The device can now be programmed to use the attached temperature sensor.

### Task

Program the device.

1. Power up the Pi and wait for it to boot

1. Launch VS Code, either directly on the Pi, or connect via the Remote SSH extension.

    > ⚠️ You can refer to [the instructions for setting up and launch VS Code in lesson 1 if needed](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md).

1. From the terminal, create a new folder in the `pi` users home directory called `temperature-sensor`. Create a file in this folder called `app.py`:

    ```sh
    mkdir temperature-sensor
    cd temperature-sensor
    touch app.py
    ```

1. Open this folder in VS Code

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

    This declares an instance of the `DHT` class that manages the **D**igital **H**umidity and **T**emperature sensor. The first parameter tells the code the sensor being used is the *DHT11* sensor - the library you are using supports other variants of this sensor. The second parameter tells the code the sensor is connected to digital port `D5` on the Grove base hat.

    > ✅ Remember, all the sockets have unique pin numbers. Pins 0, 2, 4, and 6 are analog pins, pins 5, 16, 18, 22, 24, and 26 are digital pins.

1. Add an infinite loop after the code above to poll the temperature sensor value and print it to the console:

    ```python
    while True:
        _, temp = sensor.read()
        print(f'Temperature {temp}°C')
    ```

    The call to `sensor.read()` returns a tuple of humidity and temperature. You only need the temperature value, so the humidity is ignored. The temperature value is then printed to the console.

1. Add a small sleep of ten seconds at the end of the `loop` as the temperature levels don't need to be checked continuously. A sleep reduces the power consumption of the device.

    ```python
    time.sleep(10)
    ```

1. From the VS Code Terminal, run the following to run your Python app:

    ```sh
    python3 app.py
    ```

    You should see temperature values being output to the console. Use something to warm the sensor, such as pressing your thumb on it, or using a fan to see the values change:

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py 
    Temperature 26°C
    Temperature 26°C
    Temperature 28°C
    Temperature 30°C
    Temperature 32°C
    ```

> 💁 You can find this code in the [code-temperature/pi](code-temperature/pi) folder.

😀 Your temperature sensor program was a success!
