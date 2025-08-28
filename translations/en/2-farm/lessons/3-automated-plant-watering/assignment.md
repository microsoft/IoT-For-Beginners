<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "ed0fbd6aed084bfba7d5e2f206968c50",
  "translation_date": "2025-08-28T20:45:15+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/assignment.md",
  "language_code": "en"
}
-->
# Build a more efficient watering cycle

## Instructions

This lesson explained how to control a relay using sensor data, which can then control a pump for an irrigation system. For a specific area of soil, running a pump for a fixed amount of time should consistently affect the soil moisture in the same way. This allows you to estimate how many seconds of irrigation correspond to a specific change in soil moisture levels. Using this information, you can create a more precise irrigation system.

For this assignment, you will calculate how long the pump should run to achieve a desired increase in soil moisture.

> ⚠️ If you are using virtual IoT hardware, you can follow this process but simulate the results by manually increasing the soil moisture reading by a fixed amount for each second the relay is active.

1. Start with dry soil and measure the soil moisture level.

1. Add a fixed amount of water, either by running the pump for 1 second or by pouring a specific quantity of water.

    > The pump should always operate at a consistent rate, so every second it runs, it should deliver the same amount of water.

1. Wait for the soil moisture level to stabilize, then take a reading.

1. Repeat this process several times and create a table of results. An example table is shown below:

    | Total Pump time | Soil Moisture | Decrease |
    | --- | --: | -: |
    | Dry | 643 |  0 |
    | 1s  | 621 | 22 |
    | 2s  | 601 | 20 |
    | 3s  | 579 | 22 |
    | 4s  | 560 | 19 |
    | 5s  | 539 | 21 |
    | 6s  | 521 | 18 |

1. Calculate the average increase in soil moisture per second of water. In the example above, each second of water decreases the reading by an average of 20.3.

1. Use this data to optimize your server code, ensuring the pump runs for the exact amount of time needed to achieve the desired soil moisture level.

## Rubric

| Criteria | Exemplary | Adequate | Needs Improvement |
| -------- | --------- | -------- | ----------------- |
| Capture soil moisture data | Successfully captures multiple readings after adding fixed amounts of water | Captures some readings with fixed amounts of water | Captures only one or two readings, or struggles to use fixed amounts of water |
| Calibrate the server code | Accurately calculates the average decrease in soil moisture and updates the server code accordingly | Calculates the average decrease but cannot update the server code, or calculates the average incorrectly but uses it to update the server code correctly | Fails to calculate the average or update the server code |

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we aim for accuracy, please note that automated translations may include errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is advised. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.