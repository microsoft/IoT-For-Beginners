# Control a relay - Wio Terminal

In this part of the lesson, you will add a relay to your Wio Terminal in addition to the soil moisture sensor, and control it based off the soil moisture level.

## Hardware

The Wio Terminal needs a relay.

The relay you'll use is a [Grove relay](https://www.seeedstudio.com/Grove-Relay.html), a normally-open relay (meaning the output circuit is open, or disconnected when there is no signal sent to the relay) that can handle output circuits up to 250V and 10A.

This is a digital actuator, so connects to digital pins on the Wio Terminal. The combined analog/digital port is already in use with the soil moisture sensor, so this plugs into the other port, which is a combined I<sub>2</sub>C and digital port.

### Connect the relay

The Grove relay can be connected to the Wio Terminals digital port.

#### Task

Connect the relay.

![A grove relay](../../../images/grove-relay.png)

1. Insert one end of a Grove cable into the socket on the relay. It will only go in one way round.

1. With the Wio Terminal disconnected from your computer or other power supply, connect the other end of the Grove cable to the left-hand side Grove socket on the Wio Terminal as you look at the screen. Leave the soil moisture sensor connected to the right-hand socket.

![The grove relay connected to the left-hand socket, and the soil moisture sensor connected to the right hand socket](../../../images/wio-relay-and-soil-moisture-sensor.png)

1. Insert the soil moisture sensor into soil, if it isn't already from the previous lesson.

## Program the relay

The Wio Terminal can now be programmed to use the attached relay.

### Task

Program the device.

1. Open the `soil-moisture-sensor` project from the last lesson in VS Code if it's not already open. You will be adding to this project.

1. There isn't a library for this actuator - it's a digital actuator controlled by a high or low signal. To turn it on, you send a high signal to the pin (3.3V), turn turn it off you send a low signal (0V). You can do this using the built-in Arduino [`digitalWrite`](https://www.arduino.cc/reference/en/language/functions/digital-io/digitalwrite/) function. Start by adding the following to the bottom of the `setup` function to setup the combined I<sub>2</sub>C/digital port as an output pin to send a voltage to the relay:

    ```cpp
    pinMode(PIN_WIRE_SCL, OUTPUT);
    ```

    `PIN_WIRE_SCL` is the port number for the combined I<sub>2</sub>C/digital port.

1. To test the relay is working, add the following to the `loop` function, below the final `delay`:

    ```cpp
    digitalWrite(PIN_WIRE_SCL, HIGH);
    delay(500);
    digitalWrite(PIN_WIRE_SCL, LOW);
    ```

    The code writes a high signal to the pin that the relay is connected to to turn it on, waits 500ms (half a second), then writes a low signal to turn the relay off.

1. Build and upload the code to the Wio Terminal.

1. Once uploaded, the relay will turn on and off every 10 seconds, with a half second delay between turning on and off. You will hear the relay click on then click off. An LED on the Grove board will light when the relay is on, then go out when the relay is off.

    ![The relay turning on and off](../../../images/relay-turn-on-off.gif)

## Control the relay from soil moisture

Now that the relay is working, it can be controlled in response to soil moisture readings.

### Task

Control the relay.

1. Delete the 3 lines of code that you added to test the relay. Replace them with the following code:

    ```cpp
    if (soil_moisture > 450)
    {
        Serial.println("Soil Moisture is too low, turning relay on.");
        digitalWrite(PIN_WIRE_SCL, HIGH);
    }
    else
    {
        Serial.println("Soil Moisture is ok, turning relay off.");
        digitalWrite(PIN_WIRE_SCL, LOW);
    }
    ```

    This code checks the soil moisture level from the soil moisture sensor. If it is above 450, it turns on the relay, and turns it off when it goes below 450.

    > 💁 Remember the capacitive soil moisture sensor reads the lower the soil moisture level, the more moisture there is in the soil and vice versa.

1. Build and upload the code to the Wio Terminal.

1. Monitor the device via the serial monitor. You will see the relay turn on or off depending on the soil moisture level. Try in dry soil, then add water.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 You can find this code in the [code-relay/wio-terminal](code-relay/wio-terminal) folder.

😀 Your soil moisture sensor controlling a relay program was a success!
