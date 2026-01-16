<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f8f541ee945545017a51aaf309aa37c3",
  "translation_date": "2025-08-28T20:43:38+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/virtual-device-relay.md",
  "language_code": "en"
}
-->
# Control a Relay - Virtual IoT Hardware

In this part of the lesson, you will add a relay to your virtual IoT device alongside the soil moisture sensor and control it based on the soil moisture level.

## Virtual Hardware

The virtual IoT device will use a simulated Grove relay. This ensures the lab remains consistent with using a Raspberry Pi and a physical Grove relay.

In a physical IoT device, the relay would typically be a normally-open relay (meaning the output circuit is open, or disconnected, when no signal is sent to the relay). Such a relay can handle output circuits up to 250V and 10A.

### Add the Relay to CounterFit

To use a virtual relay, you need to add it to the CounterFit app.

#### Task

Add the relay to the CounterFit app.

1. Open the `soil-moisture-sensor` project from the previous lesson in VS Code if it’s not already open. You will be adding to this project.

1. Ensure the CounterFit web app is running.

1. Create a relay:

    1. In the *Create actuator* box in the *Actuators* pane, open the *Actuator type* dropdown and select *Relay*.

    1. Set the *Pin* to *5*.

    1. Click the **Add** button to create the relay on Pin 5.

    ![The relay settings](../../../../../translated_images/en/counterfit-create-relay.fa7c40fd0f2f6afc33b35ea94fcb235085be4861e14e3fe6b9b7bcfc82d1c888.png)

    The relay will be created and will appear in the actuators list.

    ![The relay created](../../../../../translated_images/en/counterfit-relay.bbf74c1dbdc8b9acd983367fcbd06703a402aefef6af54ddb28e11307ba8a12c.png)

## Program the Relay

The soil moisture sensor app can now be programmed to use the virtual relay.

### Task

Program the virtual device.

1. Open the `soil-moisture-sensor` project from the previous lesson in VS Code if it’s not already open. You will be adding to this project.

1. Add the following code to the `app.py` file below the existing imports:

    ```python
    from counterfit_shims_grove.grove_relay import GroveRelay
    ```

    This statement imports the `GroveRelay` from the Grove Python shim libraries to interact with the virtual Grove relay.

1. Add the following code below the declaration of the `ADC` class to create a `GroveRelay` instance:

    ```python
    relay = GroveRelay(5)
    ```

    This creates a relay using pin **5**, the same pin you connected the relay to.

1. To test if the relay is working, add the following code to the `while True:` loop:

    ```python
    relay.on()
    time.sleep(.5)
    relay.off()
    ```

    This code turns the relay on, waits 0.5 seconds, and then turns it off.

1. Run the Python app. The relay will turn on and off every 10 seconds, with a half-second delay between turning on and off. You will see the virtual relay in the CounterFit app close and open as the relay is turned on and off.

    ![The virtual relay turning on and off](../../../../../images/virtual-relay-turn-on-off.gif)

## Control the Relay Based on Soil Moisture

Now that the relay is working, it can be controlled in response to soil moisture readings.

### Task

Control the relay.

1. Delete the 3 lines of code you added to test the relay. Replace them with the following code:

    ```python
    if soil_moisture > 450:
        print("Soil Moisture is too low, turning relay on.")
        relay.on()
    else:
        print("Soil Moisture is ok, turning relay off.")
        relay.off()
    ```

    This code checks the soil moisture level from the soil moisture sensor. If the level is above 450, it turns on the relay. If it drops below 450, it turns the relay off.

    > 💁 Remember, the capacitive soil moisture sensor works such that the lower the soil moisture level, the more moisture there is in the soil, and vice versa.

1. Run the Python app. You will see the relay turn on or off depending on the soil moisture levels. Adjust the *Value* or the *Random* settings for the soil moisture sensor to observe the changes.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 You can find this code in the [code-relay/virtual-device](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/virtual-device) folder.

😀 Congratulations! Your virtual soil moisture sensor successfully controls a relay!

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we aim for accuracy, please note that automated translations may include errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is advised. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.