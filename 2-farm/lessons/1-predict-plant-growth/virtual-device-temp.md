# Measure temperature - Virtual IoT Hardware

In this part of the lesson, you will add a temperature sensor to your virtual IoT device.

## Virtual Hardware

The virtual IoT device will use a simulated Grove Digital Humidity and Temperature sensor. This keeps this lab the same as using a Raspberry Pi with a physical Grove DHT11 sensor.

The sensor combines a **temperature sensor** with a **humidity sensor**, but in this lab you are only interested in the temperature sensor component. In a physical IoT device, the temperature sensor would be a [thermistor](https://wikipedia.org/wiki/Thermistor) that measures temperature by sensing a change in resistance as temperature changes. Temperature sensors are usually digital sensors the internally convert the resistance measured into a temperature in degrees Celsius (or Kelvin, or Fahrenheit).

### Add the sensors to CounterFit

To use a virtual humidity and temperature sensor, you need to add the two sensors to the CounterFit app

#### Task - add the sensors to CounterFit

Add the humidity and temperature sensors to the CounterFit app.

1. Create a new Python app on your computer in a folder called `temperature-sensor` with a single file called `app.py` and a Python virtual environment, and add the CounterFit pip packages.

    > ⚠️ You can refer to [the instructions for creating and setting up a CounterFit Python project in lesson 1 if needed](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Install an additional Pip package to install a CounterFit shim for the DHT11 sensor. Make sure you are installing this from a terminal with the virtual environment activated.

    ```sh
    pip install counterfit-shims-seeed-python-dht
    ```

1. Make sure the CounterFit web app is running

1. Create a humidity sensor:

    1. In the *Create sensor* box in the *Sensors* pane, drop down the *Sensor type* box and select *Humidity*.

    1. Leave the *Units* set to *Percentage*

    1. Ensure the *Pin* is set to *5*

    1. Select the **Add** button to create the humidity sensor on Pin 5

    ![The humidity sensor settings](../../../images/counterfit-create-humidity-sensor.png)

    The humidity sensor will be created and appear in the sensors list.

    ![The humidity sensor created](../../../images/counterfit-humidity-sensor.png)

1. Create a temperature sensor:

    1. In the *Create sensor* box in the *Sensors* pane, drop down the *Sensor type* box and select *Temperature*.

    1. Leave the *Units* set to *Celsius*

    1. Ensure the *Pin* is set to *6*

    1. Select the **Add** button to create the temperature sensor on Pin 6

    ![The temperature sensor settings](../../../images/counterfit-create-temperature-sensor.png)

    The temperature sensor will be created and appear in the sensors list.

    ![The temperature sensor created](../../../images/counterfit-temperature-sensor.png)

## Program the temperature sensor app

The temperature sensor app can now be programmed using the CounterFit sensors.

### Task - program the temperature sensor app

Program the temperature sensor app.

1. Make sure the `temperature-sensor` app is open in VS Code

1. Open the `app.py` file

1. Add the following code to the top of `app.py` to connect the app to CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Add the following code to the `app.py` file to import the required libraries:

    ```python
    import time
    from counterfit_shims_seeed_python_dht import DHT
    ```

    The `from seeed_dht import DHT` statement imports the `DHT` sensor class to interact with a virtual Grove temperature sensor using a shim from the `counterfit_shims_seeed_python_dht` module.

1. Add the following code after the code above to create an instance of the class that manages the virtual humidity and temperature sensor:

    ```python
    sensor = DHT("11", 5)
    ```

    This declares an instance of the `DHT` class that manages the virtual **D**igital **H**umidity and **T**emperature sensor. The first parameter tells the code the sensor being used is a virtual *DHT11* sensor. The second parameter tells the code the sensor is connected to port `5`.

    > 💁 CounterFit simulates this combined humidity and temperature sensor by connecting to 2 sensors, a humidity sensor on the pin given when the `DHT` class is created, and a temperature sensor that runs on the next pin. If the humidity sensor is on pin 5, the shim expects the temperatures sensor to be on pin 6.

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

1. From the VS Code Terminal with an activated virtual environment, run the following to run your Python app:

    ```sh
    python app.py
    ```

1. From the CounterFit app, change the value of the temperature sensor that will be read by the app. You can do this in one of two ways:

    * Enter a number in the *Value* box for the temperature sensor, then select the **Set** button. The number you enter will be the value returned by the sensor.

    * Check the *Random* checkbox, and enter a *Min* and *Max* value, then select the **Set** button. Every time the sensor reads a value, it will read a random number between *Min* and *Max*.

    You should see the values you set appearing in the console. Change the *Value* or the *Random* settings to see the value change.

    ```output
    (.venv) ➜  temperature-sensor python app.py
    Temperature 28.25°C
    Temperature 30.71°C
    Temperature 25.17°C
    ```

> 💁 You can find this code in the [code-temperature/virtual-device](code-temperature/virtual-device) folder.

😀 Your temperature sensor program was a success!
