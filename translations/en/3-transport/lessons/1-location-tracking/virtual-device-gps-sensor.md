<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "64f18a8f8aaa1fef5e7320e0992d8b3a",
  "translation_date": "2025-08-28T19:38:46+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/virtual-device-gps-sensor.md",
  "language_code": "en"
}
-->
# Read GPS Data - Virtual IoT Hardware

In this part of the lesson, you will add a GPS sensor to your virtual IoT device and read values from it.

## Virtual Hardware

The virtual IoT device will use a simulated GPS sensor that communicates over UART via a serial port.

A physical GPS sensor typically has an antenna to receive radio signals from GPS satellites and converts these signals into GPS data. The virtual version simulates this by allowing you to set a latitude and longitude, send raw NMEA sentences, or upload a GPX file with multiple locations that can be returned sequentially.

> 🎓 NMEA sentences will be explained later in this lesson.

### Add the Sensor to CounterFit

To use a virtual GPS sensor, you need to add one to the CounterFit app.

#### Task - Add the Sensor to CounterFit

Add the GPS sensor to the CounterFit app.

1. Create a new Python app on your computer in a folder called `gps-sensor` with a single file named `app.py`, set up a Python virtual environment, and add the CounterFit pip packages.

    > ⚠️ You can refer to [the instructions for creating and setting up a CounterFit Python project in lesson 1 if needed](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Install an additional Pip package to add a CounterFit shim that can communicate with UART-based sensors over a serial connection. Ensure you are installing this from a terminal with the virtual environment activated.

    ```sh
    pip install counterfit-shims-serial
    ```

1. Make sure the CounterFit web app is running.

1. Create a GPS sensor:

    1. In the *Create sensor* box in the *Sensors* pane, open the *Sensor type* dropdown and select *UART GPS*.

    1. Leave the *Port* set to */dev/ttyAMA0*.

    1. Click the **Add** button to create the GPS sensor on port `/dev/ttyAMA0`.

    ![The GPS sensor settings](../../../../../translated_images/en/counterfit-create-gps-sensor.6385dc9357d85ad1d47b4abb2525e7651fd498917d25eefc5a72feab09eedc70.png)

    The GPS sensor will be created and appear in the sensors list.

    ![The GPS sensor created](../../../../../translated_images/en/counterfit-gps-sensor.3fbb15af0a5367566f2f11324ef5a6f30861cdf2b497071a5e002b7aa473550e.png)

## Program the GPS Sensor

The virtual IoT device can now be programmed to use the virtual GPS sensor.

### Task - Program the GPS Sensor

Program the GPS sensor app.

1. Make sure the `gps-sensor` app is open in VS Code.

1. Open the `app.py` file.

1. Add the following code to the top of `app.py` to connect the app to CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Add the following code below this to import some required libraries, including the library for the CounterFit serial port:

    ```python
    import time
    import counterfit_shims_serial
    
    serial = counterfit_shims_serial.Serial('/dev/ttyAMA0')
    ```

    This code imports the `serial` module from the `counterfit_shims_serial` Pip package. It then connects to the `/dev/ttyAMA0` serial port, which is the address of the serial port used by the virtual GPS sensor for its UART port.

1. Add the following code below this to read from the serial port and print the values to the console:

    ```python
    def print_gps_data(line):
        print(line.rstrip())
    
    while True:
        line = serial.readline().decode('utf-8')
    
        while len(line) > 0:
            print_gps_data(line)
            line = serial.readline().decode('utf-8')
    
        time.sleep(1)
    ```

    A function called `print_gps_data` is defined to print the line passed to it to the console.

    Next, the code enters an infinite loop, reading as many lines of text as it can from the serial port during each iteration. It calls the `print_gps_data` function for each line.

    After all the data has been read, the loop pauses for 1 second before trying again.

1. Run this code, ensuring you use a different terminal than the one running the CounterFit app, so the CounterFit app remains active.

1. From the CounterFit app, change the value of the GPS sensor. You can do this in one of the following ways:

    * Set the **Source** to `Lat/Lon`, and specify a latitude, longitude, and the number of satellites used to get the GPS fix. This value will be sent only once, so check the **Repeat** box to have the data repeat every second.

      ![The GPS sensor with lat lon selected](../../../../../translated_images/en/counterfit-gps-sensor-latlon.008c867d75464fbe7f84107cc57040df565ac07cb57d2f21db37d087d470197d.png)

    * Set the **Source** to `NMEA` and add some NMEA sentences into the text box. All these values will be sent, with a delay of 1 second before each new GGA (position fix) sentence can be read.

      ![The GPS sensor with NMEA sentences set](../../../../../translated_images/en/counterfit-gps-sensor-nmea.c62eea442171e17e19528b051b104cfcecdc9cd18db7bc72920f29821ae63f73.png)

      You can use a tool like [nmeagen.org](https://www.nmeagen.org) to generate these sentences by drawing on a map. These values will be sent only once, so check the **Repeat** box to have the data repeat one second after all sentences have been sent.

    * Set the **Source** to GPX file, and upload a GPX file with track locations. You can download GPX files from various popular mapping and hiking sites, such as [AllTrails](https://www.alltrails.com/). These files contain multiple GPS locations as a trail, and the GPS sensor will return each new location at 1-second intervals.

      ![The GPS sensor with a GPX file set](../../../../../translated_images/en/counterfit-gps-sensor-gpxfile.8310b063ce8a425ccc8ebeec8306aeac5e8e55207f007d52c6e1194432a70cd9.png)

      These values will be sent only once, so check the **Repeat** box to have the data repeat one second after all locations have been sent.

    Once you have configured the GPS settings, click the **Set** button to apply these values to the sensor.

1. You will see the raw output from the GPS sensor, which will look something like this:

    ```output
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    ```

> 💁 You can find this code in the [code-gps/virtual-device](../../../../../3-transport/lessons/1-location-tracking/code-gps/virtual-device) folder.

😀 Your GPS sensor program was a success!

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we aim for accuracy, please note that automated translations may include errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is advised. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.